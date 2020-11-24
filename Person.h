#pragma once
#include<fstream>

class Person
{
private:
	char *name;
	unsigned numRel; //Number of close relatives - mother, father, brother, sister, wife/husband, child, ex-wife/husband
	unsigned char day, month;	//Birth
	short year;
	bool sex;   //0 e мъж
public:
	Person();
	Person(const char* Name, const unsigned char Day, const unsigned char Monthay, const short Year, const bool Sex);
	//
	Person& operator=(const Person &other);
	~Person();

	bool operator==(const Person &other)const;
	
	void save(std::ofstream &file)const;//
	void load(std::ifstream &file);
	void rename(const char* newName);
	void print()const;


	friend class Tree;
};