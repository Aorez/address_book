#include"pch.h"

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>

#include"Function.h"
#include"Person.h"

int numOfFace = -1;
std::string name;
std::string number;
std::string number2;
std::string email;
std::string address;
std::string remarks;

int R = 102, G = 171, B = 243;
COLORREF staticColor = RGB(R, G, B);
bool hasModified;
int staticIndex;
bool hasAdded;
std::vector<Person> addressBook;
bool loginCancal;
CFont tipsFont;
HICON dialogIcon;
bool isModifying;
bool isReseting;

//账户信息变量
bool isNewUser;//是否新用户判断变量
int numOfPicture = 156;//头像编号
int numberOfFace;//头像编号
std::string password;//密码
int rememberPassword;//是否记住密码
int securityQuestion;//第几个密保问题
std::string answerOfsecurityQuestion;//密保问题答案
std::vector<std::string> topArray;//置顶联系人姓名序列

//在主程序中定义，防止重复定义，用extern声明

int Function::add(int nof, std::string n, std::string num, std::string num2, std::string em, std::string ad, std::string re) {
	Function f;
	//搜索姓名和联系电话是否重复，若重复则返回-1，
	//不重复则添加联系人，并进行排序，返回其在vector变量中的下标
	if (f.search(n) == -1 && f.search(num) == -1) {
		Person p(nof, n, num, num2, em, ad, re);
		addressBook.push_back(p);
		sort(addressBook.begin(), addressBook.end(), compare);
		return f.search(n);
	}
	else return -1;
}

//参数中index为待修改的联系人的下标，其余均为联系人信息
int Function::modify(int index, int nof, std::string n, std::string num, std::string num2, std::string em, std::string ad, std::string re) {
	Function f;
	//在修改之前进行判断，如果姓名参数 n 在联系人中不存在或者存在的是待修改的联系人本身，
	//则不会导致冲突，可以修改，修改之后进行排序，并返回新下标值，
	//反之则不能修改，返回-1
	if (f.search(n) == -1 || addressBook[index].name == n) {
		if (f.search(num) == -1 || addressBook[index].number == num) {
			if (f.search(num2) == -1 || addressBook[index].number2 == num2) {
				int a = f.searchInTop(addressBook[index].name);
				if (a == -1) {

				}
				else {
					topArray[a] = n;
				}
				addressBook[index].numOfFace = nof;
				addressBook[index].name = n;
				addressBook[index].number = num;
				addressBook[index].number2 = num2;
				addressBook[index].email = em;
				addressBook[index].address = ad;
				addressBook[index].remarks = re;
				sort(addressBook.begin(), addressBook.end(), compare);
				return f.search(n);
			}
		}
	}
	return -1;
	
}

//删除对应下标的联系人
bool Function::detach(int index) {
	Function f;
	std::string nameToDetach = f.display(index, 1);

	//在置顶联系人中进行查找，如果存在，则同时删除
	int indexInTopArray = f.searchInTop(nameToDetach);
	if (indexInTopArray == -1) {

	}
	else {
		topArray.erase(topArray.begin() + indexInTopArray);
	}

	//备份已删除的联系人信息
	numOfFace = atoi(f.display(index, 0).c_str());
	name = f.display(index, 1);
	number = f.display(index, 2);
	number2 = f.display(index, 3);
	email = f.display(index, 4);
	address = f.display(index, 5);
	remarks = f.display(index, 6);
	addressBook.erase(std::begin(addressBook) + index);
	return true;
}

//按照参数 x 的值展示参数下标 index 联系人中的对应信息
std::string Function::display(int index, int x) {
	//因为“Person”类中的“numOfFace”变量为“int”类型，
	//为了和函数返回值同步，将其转为“string”类型再返回
	if (index >= 0) {
		switch (x) {
		case 0:return std::to_string(addressBook[index].numOfFace);
		case 1:return addressBook[index].name;
		case 2:return addressBook[index].number;
		case 3:return addressBook[index].number2;
		case 4:return addressBook[index].email;
		case 5:return addressBook[index].address;
		case 6:return addressBook[index].remarks;
		}
	}
	return "";
}

//根据“string”参数进行搜索，返回下标值
int Function::search(std::string dataToSearch) {
	if (dataToSearch == "") return -2;
	int length = addressBook.size();
	bool isExisted = false;
	int index = 0;
	//函数设定搜索参数为联系人姓名、联系电话1和联系电话2
	for (index = 0; index < length; index++) {
		if (addressBook[index].name == dataToSearch || addressBook[index].number == dataToSearch || addressBook[index].number2 == dataToSearch || addressBook[index].email == dataToSearch || addressBook[index].address == dataToSearch || addressBook[index].remarks == dataToSearch) {
			isExisted = true;
			break;
		}
	}
	if (isExisted) {
		return index;
	}
	else return -1;
}

int Function::searchInTop(std::string nameToSearch) {
	int length = topArray.size();
	int index = 0;
	for (index = 0; index < length; index++) {
		if (topArray[index] == nameToSearch) {
			return index;
		}
	}
	return -1;
}

void Function::clear() {
	addressBook.clear();
	topArray.clear();
	return;
}

void Function::dataImport() {

	//导入文件内第一行的账户信息
	std::ifstream ifs;
	ifs.open("AddressBook", std::ios::in);
	std::string linesInFile;
	getline(ifs, linesInFile);
	int sizeOfLines = linesInFile.size();
	//账户信息暂存变量
	std::string stringIsNewUser = "";
	std::string stringNumberOfFace = "";
	std::string stringRememberPassword = "";
	std::string stringSecurityQuestion = "";
	//导入第几个信息
	int importOrder = 1;
	//密码初始化置空
	password = "";
	for (int i = 0; i < sizeOfLines; i++) {
		//文件中各个信息之间用‘#’分隔开
		if (linesInFile[i] == '#') {
			importOrder++;
			continue;
			
		}
		//导入对应的第几个信息
		switch (importOrder) {
		case 1:stringIsNewUser += linesInFile[i]; break;
		case 2:stringNumberOfFace += linesInFile[i]; break;
		case 3:password += linesInFile[i]; break;
		case 4:stringRememberPassword += linesInFile[i]; break;
		case 5:stringSecurityQuestion += linesInFile[i]; break;
		case 6:answerOfsecurityQuestion += linesInFile[i]; break;
		}
	}
	//账户信息保存到全局变量
	if (stringIsNewUser == "1") isNewUser = true;
	else if (stringIsNewUser == "0") isNewUser = false;
	rememberPassword = atoi(stringRememberPassword.c_str());
	numberOfFace = atoi(stringNumberOfFace.c_str());
	securityQuestion = atoi(stringSecurityQuestion.c_str());

	//文件内第二行保存置顶联系人
	getline(ifs, linesInFile);
	sizeOfLines = linesInFile.size();
	std::string stringTopArray = "";
	for (int i = 0; i < sizeOfLines; i++) {
		if (linesInFile[i] == '#') {
			topArray.push_back(stringTopArray);
			stringTopArray = "";
			continue;
		}
		stringTopArray += linesInFile[i];
	}

	//导入联系人信息
	//每个联系人都有七个数据
	const int sizeOfPersonArray = 7;
	std::string personArray[sizeOfPersonArray] = { "","","","","","","" };
	//一行一个联系人
	while (!ifs.eof()) {
		getline(ifs, linesInFile);
		sizeOfLines = linesInFile.size();
		//'#'分隔符下标
		int indexOfSeparator = 0;
		//将文件内的一行信息暂存到数组中
		for (int i = 0; i < sizeOfPersonArray; i++) {
			for (; indexOfSeparator < sizeOfLines; indexOfSeparator++) {
				if (linesInFile[indexOfSeparator] == '#') {
					break;
				}
				else personArray[i] += linesInFile[indexOfSeparator];
			}
			indexOfSeparator++;
		}
		//定义联系人对象，并“push”进全局vector变量中
		Person p(atoi(personArray[0].c_str()), personArray[1], personArray[2], personArray[3], personArray[4], personArray[5], personArray[6]);
		addressBook.push_back(p);
		//暂存数组置空，为下一次循环做准备
		for (int i = 0; i < sizeOfPersonArray; i++) {
			personArray[i] = "";
		}
	}

	ifs.close();
	//排序
	sort(addressBook.begin(), addressBook.end(), compare);
	return;
}

void Function::dataExport() {
	
	//账户信息导出为一行
	std::ofstream ofs;
	ofs.open("AddressBook", std::ios::out);
	std::string linesInFile;
	//如果是新用户则导出默认账户信息到文件中
	if (isNewUser) {
		std::string stringIsNewUser = "1";
		linesInFile = stringIsNewUser + "#156##0#2#";
	}
	//不是新用户，则导出全局变量中的账户信息
	else {
		std::string stringIsNewUser = "0";
		std::string stringNumberOfFace = std::to_string(numberOfFace);
		std::string stringRememberPassword = std::to_string(rememberPassword);
		std::string stringSecurityQuestion = std::to_string(securityQuestion);
		linesInFile = stringIsNewUser + "#" + stringNumberOfFace + "#" + password + "#" + stringRememberPassword + "#" + stringSecurityQuestion + "#" + answerOfsecurityQuestion;
	}
	ofs << linesInFile << '\n';

	//置顶联系人姓名导出为一行
	int size = topArray.size();
	linesInFile = "";
	for (int i = 0; i < size; i++) {
		linesInFile += topArray[i] + "#";
	}
	ofs << linesInFile;

	//联系人信息导出
	//一行一个联系人
	size = addressBook.size();
	for (int i = 0; i < size; i++) {
		linesInFile = std::to_string(addressBook[i].numOfFace) + "#" + addressBook[i].name + "#" + addressBook[i].number + "#" + addressBook[i].number2 + "#" + addressBook[i].email + "#" + addressBook[i].address + "#" + addressBook[i].remarks;
		ofs << '\n' << linesInFile;
		linesInFile = "";
	}

	ofs.close();
	return;
}

void Function::test() {
	std::ifstream ifs;
	ifs.open("datatest.txt", std::ios::in);
	std::ofstream ofs;
	ofs.open("AddressBook.txt", std::ios::out);
	std::string linesInFile;
	std::string newLines;
	std::string istr;
	std::string stringFaceIndex;
	int faceIndex = 156;
	for (int i = 0; !ifs.eof(); i++) {
		getline(ifs, linesInFile);
		istr = std::to_string(i);
		if (faceIndex > 243) faceIndex -= 87;
		stringFaceIndex = std::to_string(faceIndex);
		faceIndex++;
		newLines = stringFaceIndex + "#" + linesInFile + "#" + istr + "#" + istr + "#" + istr + "@#" + linesInFile + "家#" + "无";
		ofs << newLines << '\n';
		linesInFile = "";
	}
	ifs.close();
	ofs.close();
}