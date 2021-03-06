#include"Tree.h"
#include"Person.h"
#include"Help.h"
#include<fstream>


Tree::Tree() :
	numPeople(0)
{
	treeName = new char[strLen("Unnamed") + 1];
	strCopy(treeName, "Unnamed");
}

Tree::Tree(const char *Name):
	numPeople(0)
{
	treeName = new char[strLen(Name) + 1];
	strCopy(treeName, Name);
}

Tree::Tree(const Tree& other) :
	numPeople(other.numPeople)
{
	treeName = new char[strLen(other.treeName) + 1];
	strCopy(treeName, other.treeName);
	people = other.people;
	relatives = other.relatives;
	relations = other.relations;
}

Tree& Tree::operator= (const Tree& other)
{
	if (this != &other)
	{
		rename(other.treeName);
		numPeople = other.numPeople;
		people = other.people;
		relatives = other.relatives;
		relations = other.relations;
	}
	return *this;
}

Tree::~Tree()
{
	delete[] treeName;
}



Tree Tree::operator+ (const Tree& other)//
{
	Tree result(mergeStr(treeName, other.treeName));	//The tree resulting from the addition
	unsigned *newId = new unsigned[other.numPeople];   //The indexes members of the II tree will have in result
	
	unsigned idCounter = numPeople;
	for (unsigned i = 0, j; i < other.numPeople; ++i)	//Searches for people present in both trees and gives them the same index in result
	{
		for (j = 0; j < numPeople; ++j)
		{
			if (other.people[i] == people[j])
			{
				newId[i] = j;
				break;
			}
		}
		if (j >= numPeople)
			newId[i] = ++idCounter;
	}
	result.numPeople = idCounter;	//The number of members the resulting tree has

	result.people.resize(result.numPeople);
	result.people = people;   //Adds the members of the I tree to the resulting tree
	for (unsigned i=0; i < other.numPeople; ++i)   //Adds the members of the II tree to the resulting tree
	{
		if (newId[i] >= numPeople)
			result.people.push(other.people[i]);
	}

	result.relatives.resize(result.numPeople);
	result.relations.resize(result.numPeople);
	result.relatives = relatives;
	result.relations = relations;
	
	for (unsigned i=0; i < other.numPeople; ++i)   //Adds the relatives from the II tree
	{
		if (newId[i] >= numPeople)   //If the member is found in the II tree but not in the I
		{
			result.relatives.push(other.relatives[i]);
			result.relations.push(other.relations[i]);
		}
		else   //If he's found in both
		{
			for (unsigned j = 0; j < other.people[i].numRel; ++j)   //Adds the number of relatives from the II to the number in the I
			{
				if(newId[other.relatives[i][j]] > numPeople)
					++result.people[newId[i]].numRel;
			}
			
			result.relatives[newId[i]].resize(result.people[newId[i]].numRel);
			result.relations[newId[i]].resize(result.people[newId[i]].numRel);

			result.relatives[newId[i]] = relatives[newId[i]];
			result.relations[newId[i]] = relations[newId[i]];
			result.relatives[newId[i]] += other.relatives[i];   //The relatives from the II tree
			result.relations[newId[i]] += other.relations[i];
		}
	}

	delete[]newId;
	return result;
}

Tree& Tree::operator+=(const Tree& other) 
{
	unsigned *newId = new unsigned[other.numPeople];   //The indexes people from II tree will have in I tree

	unsigned idCounter = numPeople;  
	for (unsigned i = 0, j; i < other.numPeople; ++i)	//Searches for people present in both trees and gives them the same index in I
	{
		for (j = 0; j < numPeople; ++j)
		{
			if (other.people[i] == people[j])
			{
				newId[i] = j;
				break;
			}
		}
		if (j >= numPeople)
			newId[i] = idCounter++;
	}

	people.resize(idCounter);
	for (unsigned i = 0; i < other.numPeople; ++i)   //Adds the member personal data of II tree to I tree
	{
		if (newId[i] >= numPeople)
			people.push(other.people[i]);
	}

	relatives.resize(idCounter);
	relations.resize(idCounter);
	for (unsigned i = 0; i < other.numPeople; ++i)   //Merges the relative data
	{
		if (newId[i] >= numPeople)
		{
			relatives.push(other.relatives[i]);
			for (unsigned j = 0; j < other.people[i].numRel; ++j)
				relatives[newId[i]][j] = newId[ relatives[newId[i]][j] ];
			relations.push(other.relations[i]);
		}
		else   //If the member is present in both trees
		{
			for (unsigned j = 0; j < other.people[i].numRel; ++j)   //Adds the number of relatives from the II to the number in the I
			{
				if (newId[other.relatives[i][j]] >= numPeople)
					++people[newId[i]].numRel;
			}
			relatives[newId[i]].resize(people[newId[i]].numRel);
			relations[newId[i]].resize(people[newId[i]].numRel);
			for (unsigned j = 0; j < other.people[i].numRel; ++j)
			{
				relatives[newId[i]][j + people[newId[i]].numRel - other.people[i].numRel] = newId[other.relatives[i][j]];
				relations[newId[i]][j + people[newId[i]].numRel - other.people[i].numRel] = other.relations[i][j];
			}
		}
	}

	delete[]newId;
	numPeople = idCounter;	//Number of members in I tree
	return *this;
}

Tree& Tree::operator-= (const Tree& other)
{
	for (unsigned i = 0; i < numPeople; ++i)
	{
		for (unsigned j = 0; j < other.numPeople; ++j)
		{
			if (people[i] == other.people[j])
			{
				removePerson(i);
				--i;
				break;
			}
		}
	}
	return *this;
}



void Tree::rename(const char* newName)
{
	delete[] treeName;
	treeName = new char[strLen(newName) + 1];
	strCopy(treeName, newName);
}

unsigned Tree::findId(const char* name, const short year, const unsigned char month, const unsigned char day)const
{
	//Person sought(name, day, month, year,)
	for (unsigned i = 0; i < numPeople; ++i)
	{
		if (strComp(name, people[i].name) && (year == people[i].year || !year || !people[i].year) && (month == people[i].month || !month || !people[i].month) && (day == people[i].day || !day || people[i].day))
			return i;
	}
	return Nobody;
}

unsigned Tree::findOldestAncestor(const unsigned &id, const bool &sex)const
{
	for (unsigned i = 0; i < people[id].numRel; ++i)
	{
		if (relations[id][i] == Son && people[ relatives[id][i] ].sex == sex)
			return findOldestAncestor(relatives[id][i], sex);
	}
	return id;
}

unsigned Tree::findCommonAncestor(const unsigned firstId, const unsigned secondId)const
{
	Array<char> visited(numPeople);		//if a member is visited twice he's a common ancestor
	for (unsigned i = 0; i < numPeople; ++i)
		visited[i] = 0;
	commonAncestorRec(firstId, visited);
	commonAncestorRec(secondId, visited);

	unsigned oldestId = Nobody;
	short oldestBday = SHRT_MAX;
	for (unsigned i = 0; i < numPeople; ++i)
	{
		if (visited[i] == 2 && people[i].year<oldestBday)
		{
			oldestBday = people[i].year;
			oldestId = i;
		}
	}
	return oldestId;
}

void Tree::saveTree()const
{
	char* fileName = mergeStr(treeName, ".people");  
	std::ofstream peopleFile(fileName, std::ios::binary);
	delete[] fileName;

	peopleFile.write(reinterpret_cast<char*>(&numPeople), sizeof(numPeople));
	for (unsigned i = 0; i < numPeople; ++i)
		people[i].save(peopleFile);
	peopleFile.close();

	fileName = mergeStr(treeName, ".relatives");
	std::ofstream  relativeFile(fileName, std::ios::binary);
	delete[] fileName;
	fileName = mergeStr(treeName, ".relations");
	std::ofstream relationFile(fileName, std::ios::binary);
	delete[] fileName;

	/*relativeFile.write((char*)&numPeople, sizeof(numPeople));
	relationFile.write((char*)&numPeople, sizeof(numPeople));*/
	for (unsigned i = 0; i < numPeople; ++i)
	{		
		//relativeFile.write((char*)&people[i].numRel, sizeof(people[i].numRel));
		for (unsigned j = 0; j < people[i].numRel; ++j)
			relativeFile.write(reinterpret_cast<char*>(&relatives[i][j]), sizeof(relatives[i][j]));

		//relationFile.write((char*)&people[i].numRel, sizeof(people[i].numRel));
		for (unsigned j = 0; j < people[i].numRel; ++j)
			relationFile.write(reinterpret_cast<char*>(&relations[i][j]), sizeof(relations[i][j]));
	}
	relativeFile.close();
	relationFile.close();
}

bool Tree::loadTree()
{
	char*  fileName = mergeStr(treeName, ".people");//c
	std::ifstream peopleFile(fileName, std::ios::binary);
	delete[] fileName;
	if (peopleFile.peek() == std::char_traits<char>::eof())
	{
		peopleFile.close();
		return 0;
	}

	peopleFile.read(reinterpret_cast<char*>(&numPeople), sizeof(numPeople));
	people.resize(numPeople);
	for (unsigned i = 0; i < numPeople; ++i)
		people[i].load(peopleFile);
	people.sNum(numPeople);
	peopleFile.close();

	fileName = mergeStr(treeName, ".relatives");
	std::ifstream  relativeFile(fileName, std::ios::binary);
	delete[] fileName;
	fileName = mergeStr(treeName, ".relations");
	std::ifstream  relationFile(fileName, std::ios::binary);
	delete[] fileName;

	relatives.resize(numPeople);
	relations.resize(numPeople);
	for (unsigned i = 0; i < numPeople; ++i)
	{
		relatives[i].resize(people[i].numRel);
		for (unsigned j = 0; j < people[i].numRel; ++j)
			relativeFile.read(reinterpret_cast<char*>(&relatives[i][j]), sizeof(relatives[i][j]));
		relatives[i].sNum(people[i].numRel);

		relations[i].resize(people[i].numRel);
		for (unsigned j = 0; j < people[i].numRel; ++j)
			relationFile.read(reinterpret_cast<char*>(&relations[i][j]), sizeof(relations[i][j]));
		relations[i].sNum(people[i].numRel);
	}
	relatives.sNum(numPeople);
	relations.sNum(numPeople);
	relativeFile.close();
	relationFile.close();
	return 1;
}

void Tree::addPerson(const char *name, const short year, const unsigned char month, const unsigned char day, const bool sex, const unsigned father, const unsigned mother)
{
	Person newPerson(name, day, month, year, sex);
	people.push(newPerson);
	Array<unsigned> newRelative;
	relatives.push(newRelative);
	Array<Relation> newRelation;
	relations.push(newRelation);
	++numPeople;
	addRelation(father, Father, numPeople - 1);
	addRelation(mother, Mother, numPeople - 1);
}

bool Tree::addRelation(const char* firstName, const Relation type, const char* secondName)
{

	return addRelation(findId(firstName), type, findId(secondName));
}

bool Tree::addRelation(const unsigned firstId, const Relation type, const unsigned secondId, bool opposite)//
{
	if (firstId == Nobody || firstId >= numPeople || secondId == Nobody || secondId >= numPeople || type == Invalid)
		return 0;

	unsigned i = 0;
	for (; i < people[firstId].numRel; ++i)	  //If they are already relatives
	{
		if (relatives[firstId][i] == secondId)
		{
			relations[firstId][i] = type;
			break;
		}
	}
	if (i >= people[firstId].numRel)
	{
		relatives[firstId].push(secondId);
		relations[firstId].push(type);
		++people[firstId].numRel;
	}

	if (!opposite)
	{
		if (!people[secondId].sex)
		{
			switch (type)
			{
			case Father:
			case Mother:
				addRelation(secondId, Son, firstId, 1);
				break;
			case Son:
			case Daughter:
				addRelation(secondId, Father, firstId, 1);
				break;
			case Brother:
			case Sister:
				addRelation(secondId, Brother, firstId, 1);
				break;
			case HalfBrother:
			case HalfSister:
				addRelation(secondId, HalfBrother, firstId, 1);
				break;
			case Wife:
				addRelation(secondId, Husband, firstId, 1);
				break;
			case ExWife:
				addRelation(secondId, ExHusband, firstId, 1);
				break;
			}
		}
		else
		{
			switch (type)
			{
			case Father:
			case Mother:
				addRelation(secondId, Daughter, firstId, 1);
				break;
			case Son:
			case Daughter:
				addRelation(secondId, Mother, firstId, 1);
				break;
			case Brother:
			case Sister:
				addRelation(secondId, Sister, firstId, 1);
				break;
			case HalfBrother:
			case HalfSister:
				addRelation(secondId, HalfSister, firstId, 1);
				break;
			case Husband:
				addRelation(secondId, Wife, firstId, 1);
				break;
			case ExHusband:
				addRelation(secondId, ExWife, firstId, 1);
				break;
			}
		}
	}
	return 1;
}

void Tree::removeRelation(const char* firstName, const char* secondName)
{
	removeRelation(findId(firstName), findId(secondName));
}

void Tree::removePerson(const unsigned id)
{
	unsigned relId;   //Íoìåð íà òåêóùèÿ ðîäíèíàòà
	for (unsigned i = 0; i < people[id].numRel; ++i)	//Ïðåìàõâàò ñå âðúçêèòå íà ÷ëåíà çà ïðåìàõâàíå
	{
		relId = relatives[id][i];
		for (unsigned j = 0; j < people[relId].numRel; ++j)
		{
			if (relatives[relId][j] == id)
			{
				relatives[relId].remove(j);
				relations[relId].remove(j);
				break;
			}
		}
		--people[relId].numRel;
	}
	for (unsigned i = 0; i < people[numPeople - 2].numRel; ++i)	//Ïîñëåäíèÿò ÷ëåí âçåìà íîìåðà íà ïðåìàõíàòèÿ
	{
		relId = relatives[numPeople - 1][i];
		for (unsigned j = 0; j < people[relId].numRel; ++j)
		{
			if (relatives[relId][j] == numPeople - 1)
			{
				relatives[relId][j] = id;
				break;
			}
		}
	}
	relatives.remove(id);
	relations.remove(id);
	people.remove(id);
	--numPeople;
}

void Tree::removePerson(const char* personName, const short year, const unsigned char month, const unsigned char day)
{
	removePerson(findId(personName, year, month, day));
}

void Tree::removeRelation(const unsigned firstId, const unsigned secondId)
{
	for (unsigned i = 0; i < people[firstId].numRel; ++i)
	{
		if (relatives[firstId][i] == secondId)
		{
			relatives[firstId].remove(i);
			relations[firstId].remove(i);
			--people[firstId].numRel;
			break;
		}
	}
	for (unsigned i = 0; i < people[secondId].numRel; ++i)
	{
		if (relatives[secondId][i] == firstId)
		{
			relatives[secondId].remove(i);
			relations[secondId].remove(i);
			--people[secondId].numRel;
			break;
		}
	}
}



void Tree::printRel(const unsigned id)const
{
	if (people[id].numRel == 0)
	{
		std::cout << "No relatives";
		return;
	}

	unsigned relId;
	std::cout <<people[id].name<< "'s relatives:\n";
	for (unsigned i = 0; i < people[id].numRel; ++i)
	{
		relId = relatives[id][i];
		std::cout << people[relId].name << " - ";

		switch (relations[id][i])
		{
		case Father:
		case Mother:
			std::cout << (people[relId].sex ? "daughter\n" : "son\n");
			break;
		case Son:
		case Daughter:
			std::cout << (people[relId].sex ? "mother\n" : "father\n");
			break;	
		case Brother:
		case Sister:
			std::cout << (people[relId].sex ? "sister\n" : "brother\n");
			break;
		case HalfBrother:
		case HalfSister:
			std::cout << (people[relId].sex ? "half sister\n" : "half brother\n");
			break;
		case Husband:
			std::cout << "wife\n";
			break;
		case Wife:
			std::cout << "husband\n";
			break;
		case ExHusband:
			std::cout << "ex-wife\n";
			break;
		case ExWife:
			std::cout << "ex-husband\n";
			break;
		}
	}
	std::cout << "\n";
}

void Tree::printMember(const unsigned id)const
{
	people[id].print();
}

void Tree::printOldestAncestors(const unsigned id)const
{
	people[findOldestAncestor(id)].print();
	people[findOldestAncestor(id, 1)].print();
}



unsigned Tree::gNumP()const
{
	return numPeople;
}



void Tree::commonAncestorRec(const unsigned &id, const Array<char> &visited)const
{
	for (unsigned i = 0; i < people[id].numRel; ++i)
	{
		if (relations[id][i] == Son)
		{
			++visited[relatives[id][i]];
			commonAncestorRec(relatives[id][i], visited);
		}
	}
}
