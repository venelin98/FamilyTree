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
	Array<Person> people;  //The data for each member
	Array<Array<unsigned>> relatives;   //The relatives of each member
	Array<Array<Relation>> relations;   //The type of relation each member has with his relatives
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
	bool loadTree();
	void addPerson(const char *name, const short year, const unsigned char month, const unsigned char day, const bool sex, const unsigned father = Nobody, const unsigned mother = Nobody);
	bool addRelation(const char* firstName, const Relation, const char* secondName);   //Adds a new relation or edits an old one. 0 - failure 1 - success
	bool addRelation(const unsigned firstId, const Relation, const unsigned secondId, bool opposite=0);   //0 - failure 1 - success
	void removePerson(const unsigned id);   //Removes a member and the last one takes his ID
	void removePerson(const char* personName, const short year = 0, const unsigned char month = 0, const unsigned char day = 0);
	void removeRelation(const unsigned firstId, const unsigned secondId);
	void removeRelation(const char* firstName, const char* secondName);

	void printRel(const unsigned id)const; //Prints out close relatives
	void printMember(const unsigned id)const;
	void printAncestors(const unsigned id)const;
	void printCommonAncesto(const unsigned id)const;

	unsigned gNumP()const;
	
	//Search, ect.	
};