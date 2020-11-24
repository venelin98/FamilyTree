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

const unsigned Nobody = UINT_MAX; //Този номер ще бъде запазeн за липса на връзка/човек

class Tree
{
private:
	char *treeName;
	unsigned numPeople;
	Array<Person> people;  //Данните за всеки член
	Array<Array<unsigned>> relatives;   //Роднините на всеки член
	Array<Array<Relation>> relations;   //Роднинските връзки които има всеки член с роднините си
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
	void addRelation(const char* firstName, const Relation, const char* secondName);   //Добавя нова връзка или променя съществуваща
	void addRelation(const unsigned firstId, const Relation, const unsigned secondId, bool opposite=0);
	void removePerson(const unsigned id);   //Премахва член и последния взема номера му
	void removePerson(const char* personName); 
	void removeRelation(const unsigned firstId, const unsigned secondId);
	void removeRelation(const char* firstName, const char* secondName);
	void printRel(const unsigned id)const; //Prints out close relatives
	void printMember(const unsigned id)const;

	unsigned gNumP()const;
	
	//Search, ect.	
};