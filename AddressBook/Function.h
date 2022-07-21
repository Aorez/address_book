#ifndef FUNCTION_H
#define FUNCTION_H

#include<string>

class Function {
public:
	int add(int sn, std::string n,std::string num, std::string num2 = "", std::string em = "", std::string ad = "", std::string re = "");
	int modify(int index, int sn, std::string n, std::string num, std::string num2 = "", std::string em = "", std::string ad = "", std::string re = "");
	bool detach(int index);
	std::string display(int index,int x);
	int search(std::string dataToSearch);
	void clear();
	void dataImport();
	void dataExport();
	void test();//���Գ���ʱʹ��
	int searchInTop(std::string nameToSearch);//���ö���ϵ���н�������
};

#endif