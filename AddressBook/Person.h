#ifndef _PERSON_H_
#define _PERSON_H_

#include<string>

class Person {
public:
	Person():numOfFace(-1), name(""),number(""), number2(""), email(""), address(""){}
	Person(int nof, std::string n, std::string num, std::string num2, std::string em, std::string ad, std::string re):
		numOfFace(nof), name(n), number(num), number2(num2), email(em), address(ad), remarks(re) {}
private:
	int numOfFace;//ͷ��ı��
	std::string name;
	std::string number;
	std::string number2;
	std::string email;
	std::string address;
	std::string remarks;//��ϵ�˱�ע
	friend class Function;
	//�ȽϺ���������vector��������
	friend bool compare(Person& p1, Person& p2);
};

#endif