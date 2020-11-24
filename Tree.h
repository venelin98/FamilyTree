#pragma once
#include<iostream>
#include"Array.h"

class Person;

enum Relation : char
{
	Invalid = 0,
	Father,
	Mother,
	Son,
	Daughter,
	Brother,
	Sister,
	HalfBrother,
	HalfSister,
	Wife,
	Husband,
	ExWife,
	ExHusband
};

const unsigned Nobody = UINT_MAX; //���� ����� �� ���� �����e� �� ����� �� ������/�����

class Tree
{
private:
	char *treeName;
	unsigned numPeople;
	Array<Person> people;  //������� �� ����� ����
	Array<Array<unsigned>> relatives;   //��������� �� ����� ����
	Array<Array<Relation>> relations;   //����������� ������ ����� ��� ����� ���� � ��������� ��
public:
	Tree();
	Tree(const char *Name);
	Tree(const Tree&);
	Tree& operator= (const Tree& other);
	~Tree();

	

	Tree operator+ (const Tree& other);
	Tree operator- (const Tree& other);
	Tree& operator+= (const Tree& other);
	Tree& operator-= (const Tree& other);

	void rename(const char* newName);
	unsigned findId(const char*, const short year=0, const unsigned char month=0, const unsigned char day=0)const;
	void saveTree()const;//
	void loadTree();//
	void addPerson(const char *name, const short year, const unsigned char month, const unsigned char day, const bool sex, const unsigned father = Nobody, const unsigned mother = Nobody);
	void addRelation(const char* firstName, const Relation, const char* secondName);   //������ ���� ������ ��� ������� ������������
	void addRelation(const unsigned firstId, const Relation, const unsigned secondId, bool opposite=0);
	void removePerson(const unsigned id);   //�������� ���� � ��������� ����� ������ ��
	void removePerson(const char* personName); 
	void removeRelation(const unsigned firstId, const unsigned secondId);
	void removeRelation(const char* firstName, const char* secondName);
	void printRel(const unsigned id)const; //Prints out close relatives
	void printMember(const unsigned id)const;

	unsigned gNumP()const;
	
	//Search, ect.	
};