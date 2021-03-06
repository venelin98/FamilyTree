#include"Person.h"
#include"Help.h"
#include<iostream>

Person::Person():
	name(nullptr),
	numRel(0),
	day(0),
	month(0),
	year(0),
	sex(0)
{}

Person::Person(const char* Name, const unsigned char Day, const unsigned char Month, const short Year, const bool Sex) :
	numRel(0),
	day(Day),
	month(Month),
	year(Year),
	sex(Sex)
{
	name = new char[strLen(Name) + 1];
	strCopy(name, Name);
}


Person& Person::operator=(const Person &other)
{
	if (&other!=this)
	{
		rename(other.name);
		numRel = other.numRel;
		sex = other.sex;
		day = other.day;
		month = other.month;
		year = other.year;
	}
	return *this;
}

Person::~Person()
{
	delete[] name;
}
	

bool Person::operator==(const Person &other)const
{
	return strComp(name, other.name) && sex == other.sex && (day == other.day || !day || !other.day) && (month == other.month || !month || !other.month) && (year == other.year || !year || !other.year);
}


void Person::save(std::ofstream &file)const
{
	//
	char nameLen = strLen(name);
	file.write(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
	file.write(name, nameLen * sizeof(*name));
	file.write(reinterpret_cast<char*>(&numRel), sizeof(numRel));
	file.write(reinterpret_cast<char*>(&sex), sizeof(sex));
	file.write(reinterpret_cast<char*>(&day), sizeof(day));
	file.write(reinterpret_cast<char*>(&month), sizeof(month));
	file.write(reinterpret_cast<char*>(&year), sizeof(year));
}

void Person::load(std::ifstream &file)
{
	char nameLen;
	file.read((char*)&nameLen, sizeof(nameLen));

	name = new char[nameLen + 1];
	file.read(name, nameLen * sizeof(*name));
	name[nameLen] = '\0';

	file.read(reinterpret_cast<char*>(&numRel), sizeof(numRel));
	file.read(reinterpret_cast<char*>(&sex), sizeof(sex));
	file.read(reinterpret_cast<char*>(&day), sizeof(day));
	file.read(reinterpret_cast<char*>(&month), sizeof(month));
	file.read(reinterpret_cast<char*>(&year), sizeof(year));
}

void Person::rename(const char* newName)
{
	delete[] name;
	name = new char[strLen(newName) + 1];
	strCopy(name, newName);
}

void Person::print()const
{
	std::cout << name << "\nBirthday: " << (int)day << "." << (int)month << "." << year << "\nSex: ";
	if (sex)
		std::cout << "Female\n\n";
	else
		std::cout << "Male\n\n";
}
