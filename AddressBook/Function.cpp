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

//�˻���Ϣ����
bool isNewUser;//�Ƿ����û��жϱ���
int numOfPicture = 156;//ͷ����
int numberOfFace;//ͷ����
std::string password;//����
int rememberPassword;//�Ƿ��ס����
int securityQuestion;//�ڼ����ܱ�����
std::string answerOfsecurityQuestion;//�ܱ������
std::vector<std::string> topArray;//�ö���ϵ����������

//���������ж��壬��ֹ�ظ����壬��extern����

int Function::add(int nof, std::string n, std::string num, std::string num2, std::string em, std::string ad, std::string re) {
	Function f;
	//������������ϵ�绰�Ƿ��ظ������ظ��򷵻�-1��
	//���ظ��������ϵ�ˣ����������򣬷�������vector�����е��±�
	if (f.search(n) == -1 && f.search(num) == -1) {
		Person p(nof, n, num, num2, em, ad, re);
		addressBook.push_back(p);
		sort(addressBook.begin(), addressBook.end(), compare);
		return f.search(n);
	}
	else return -1;
}

//������indexΪ���޸ĵ���ϵ�˵��±꣬�����Ϊ��ϵ����Ϣ
int Function::modify(int index, int nof, std::string n, std::string num, std::string num2, std::string em, std::string ad, std::string re) {
	Function f;
	//���޸�֮ǰ�����жϣ������������ n ����ϵ���в����ڻ��ߴ��ڵ��Ǵ��޸ĵ���ϵ�˱���
	//�򲻻ᵼ�³�ͻ�������޸ģ��޸�֮��������򣬲��������±�ֵ��
	//��֮�����޸ģ�����-1
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

//ɾ����Ӧ�±����ϵ��
bool Function::detach(int index) {
	Function f;
	std::string nameToDetach = f.display(index, 1);

	//���ö���ϵ���н��в��ң�������ڣ���ͬʱɾ��
	int indexInTopArray = f.searchInTop(nameToDetach);
	if (indexInTopArray == -1) {

	}
	else {
		topArray.erase(topArray.begin() + indexInTopArray);
	}

	//������ɾ������ϵ����Ϣ
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

//���ղ��� x ��ֵչʾ�����±� index ��ϵ���еĶ�Ӧ��Ϣ
std::string Function::display(int index, int x) {
	//��Ϊ��Person�����еġ�numOfFace������Ϊ��int�����ͣ�
	//Ϊ�˺ͺ�������ֵͬ��������תΪ��string�������ٷ���
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

//���ݡ�string���������������������±�ֵ
int Function::search(std::string dataToSearch) {
	if (dataToSearch == "") return -2;
	int length = addressBook.size();
	bool isExisted = false;
	int index = 0;
	//�����趨��������Ϊ��ϵ����������ϵ�绰1����ϵ�绰2
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

	//�����ļ��ڵ�һ�е��˻���Ϣ
	std::ifstream ifs;
	ifs.open("AddressBook", std::ios::in);
	std::string linesInFile;
	getline(ifs, linesInFile);
	int sizeOfLines = linesInFile.size();
	//�˻���Ϣ�ݴ����
	std::string stringIsNewUser = "";
	std::string stringNumberOfFace = "";
	std::string stringRememberPassword = "";
	std::string stringSecurityQuestion = "";
	//����ڼ�����Ϣ
	int importOrder = 1;
	//�����ʼ���ÿ�
	password = "";
	for (int i = 0; i < sizeOfLines; i++) {
		//�ļ��и�����Ϣ֮���á�#���ָ���
		if (linesInFile[i] == '#') {
			importOrder++;
			continue;
			
		}
		//�����Ӧ�ĵڼ�����Ϣ
		switch (importOrder) {
		case 1:stringIsNewUser += linesInFile[i]; break;
		case 2:stringNumberOfFace += linesInFile[i]; break;
		case 3:password += linesInFile[i]; break;
		case 4:stringRememberPassword += linesInFile[i]; break;
		case 5:stringSecurityQuestion += linesInFile[i]; break;
		case 6:answerOfsecurityQuestion += linesInFile[i]; break;
		}
	}
	//�˻���Ϣ���浽ȫ�ֱ���
	if (stringIsNewUser == "1") isNewUser = true;
	else if (stringIsNewUser == "0") isNewUser = false;
	rememberPassword = atoi(stringRememberPassword.c_str());
	numberOfFace = atoi(stringNumberOfFace.c_str());
	securityQuestion = atoi(stringSecurityQuestion.c_str());

	//�ļ��ڵڶ��б����ö���ϵ��
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

	//������ϵ����Ϣ
	//ÿ����ϵ�˶����߸�����
	const int sizeOfPersonArray = 7;
	std::string personArray[sizeOfPersonArray] = { "","","","","","","" };
	//һ��һ����ϵ��
	while (!ifs.eof()) {
		getline(ifs, linesInFile);
		sizeOfLines = linesInFile.size();
		//'#'�ָ����±�
		int indexOfSeparator = 0;
		//���ļ��ڵ�һ����Ϣ�ݴ浽������
		for (int i = 0; i < sizeOfPersonArray; i++) {
			for (; indexOfSeparator < sizeOfLines; indexOfSeparator++) {
				if (linesInFile[indexOfSeparator] == '#') {
					break;
				}
				else personArray[i] += linesInFile[indexOfSeparator];
			}
			indexOfSeparator++;
		}
		//������ϵ�˶��󣬲���push����ȫ��vector������
		Person p(atoi(personArray[0].c_str()), personArray[1], personArray[2], personArray[3], personArray[4], personArray[5], personArray[6]);
		addressBook.push_back(p);
		//�ݴ������ÿգ�Ϊ��һ��ѭ����׼��
		for (int i = 0; i < sizeOfPersonArray; i++) {
			personArray[i] = "";
		}
	}

	ifs.close();
	//����
	sort(addressBook.begin(), addressBook.end(), compare);
	return;
}

void Function::dataExport() {
	
	//�˻���Ϣ����Ϊһ��
	std::ofstream ofs;
	ofs.open("AddressBook", std::ios::out);
	std::string linesInFile;
	//��������û��򵼳�Ĭ���˻���Ϣ���ļ���
	if (isNewUser) {
		std::string stringIsNewUser = "1";
		linesInFile = stringIsNewUser + "#156##0#2#";
	}
	//�������û����򵼳�ȫ�ֱ����е��˻���Ϣ
	else {
		std::string stringIsNewUser = "0";
		std::string stringNumberOfFace = std::to_string(numberOfFace);
		std::string stringRememberPassword = std::to_string(rememberPassword);
		std::string stringSecurityQuestion = std::to_string(securityQuestion);
		linesInFile = stringIsNewUser + "#" + stringNumberOfFace + "#" + password + "#" + stringRememberPassword + "#" + stringSecurityQuestion + "#" + answerOfsecurityQuestion;
	}
	ofs << linesInFile << '\n';

	//�ö���ϵ����������Ϊһ��
	int size = topArray.size();
	linesInFile = "";
	for (int i = 0; i < size; i++) {
		linesInFile += topArray[i] + "#";
	}
	ofs << linesInFile;

	//��ϵ����Ϣ����
	//һ��һ����ϵ��
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
		newLines = stringFaceIndex + "#" + linesInFile + "#" + istr + "#" + istr + "#" + istr + "@#" + linesInFile + "��#" + "��";
		ofs << newLines << '\n';
		linesInFile = "";
	}
	ifs.close();
	ofs.close();
}