#ifndef _PERSON_H_
#define _PERSON_H_

#include<string>

class Person {
public:
	Person():numOfFace(-1), name(""),number(""), number2(""), email(""), address(""){}
	Person(int nof, std::string n, std::string num, std::string num2, std::string em, std::string ad, std::string re):
		numOfFace(nof), name(n), number(num), number2(num2), email(em), address(ad), remarks(re) {}
private:
	int numOfFace;//头像的编号
	std::string name;
	std::string number;
	std::string number2;
	std::string email;
	std::string address;
	std::string remarks;//联系人备注
	friend class Function;
	//比较函数，用于vector变量排序
	friend bool compare(Person& p1, Person& p2);
};

#endif