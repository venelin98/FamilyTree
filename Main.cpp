#include<iostream>
#include"Tree.h"
#include"Help.h"

int main()
{
	/*Tree test1("Dechkovi");	Create two trees with 1 common member to test on
	Tree test2("Karamanovi");
	
	test1.addPerson("Rumen", 0, 8, 1968, 0);
	test1.addPerson("Nadejda", 15, 12, 1972, 1);
	test1.addRelation(0, Husband, 1);
	test1.addPerson("Venelin", 9, 6, 1998, 0, 0, 1);
	test1.addPerson("Vasil", 16, 1, 2001, 0, 0, 1);
	test1.addRelation(2, Brother, 3);
	test1.addPerson("Maria-Veronika", 3, 11, 2009, 1, 0, 1);
	test1.addRelation(2, Brother, 4);
	test1.addRelation(3, Brother, 4);

	test2.addPerson("Vasil", 18, 5, 1941, 0);
	test2.addPerson("Maria", 0, 0, 0, 1);
	test2.addRelation(0, Husband, 1);
	test2.addPerson("Dimitar", 0, 0, 0, 0, 0, 1);
	test2.addPerson("Nadejda", 15, 12, 1972, 1, 0, 1);
	test2.addRelation(2, Brother, 3);
	test2.addPerson("Branimira", 0, 0, 0, 1);
	test2.addRelation(2, Husband, 4);
	test2.addPerson("Ioan", 0, 0, 0, 0, 2, 4);
	test2.addPerson("Rumiana", 0, 0, 0, 1, 2, 4);
	test2.addRelation(5, Brother, 6);

	test1.saveTree();
	test2.saveTree();*/


	Array<Tree> trees;
	
	bool quit=0;
	char input[128];
	short i; //Number of entered command
	const short numCom = 19;
	const char* const commandList[] =
	{
		"quit",             //0
		"rename",           //1
		"load",             //2
		"save",             //3
		"addPerson",        //4
		"addPersonWP",      //5   Adds a person and connects him to his parents, by their number
		"addRelation",      //6   Adds a relation between two people input by name
		"addRelationID",    //7   -||- by number
		"findID",           //8   
		"equate",           //9   Enter the number of two trees, the second becomes equal to the first
		"combine",          //10 
		"subtract",        //11
		"removePerson",     //12
		"removePersonID",   //13
		"removeRelation",   //14
		"removeRelationID", //15
		"addTree",          //16
		"printRelatives",   //17
		"printMember",      //18
	};
	
	unsigned j, q;
	Tree *newTree;
	char firstName[128], secondName[128];
	do
	{
		std::cout << "Enter a command\n\n";
		std::cin >> input;
		for (i = 0; i < numCom; ++i)
		{
			if (strComp(input, commandList[i]))
				break;
		}

		switch (i)
		{
		default:
			std::cout << "Unknown command, try again\n\n";
			break;
		case 0:			//quit
			quit = 1;
			break;
		case 1:			//rename
			std::cout << "Enter tree ID\n\n";
			std::cin >> j;
			if (trees.gNum() > j)
			{
				std::cout << "Enter new name\n\n";
				std::cin >> input;
				trees[j].rename(input);
			}
			else
				std::cout << "No such tree\n\n";
			break;
		case 2:			//load
			std::cin >> j;
			if (trees.gNum() > j)
				trees[j].loadTree();
			else
				std::cout << "No such tree\n\n";
			break;
		case 3:			//save
			std::cin >> j;
			if (trees.gNum() > j)
				trees[j].saveTree();
			else
				std::cout << "No such tree\n\n";
			break;
		case 4:			//addPerson
			std::cin >> j;
			if (trees.gNum() > j)
			{
				unsigned char day, month;
				short year;
				bool sex;
				std::cin >> input >> day >> month >> year >> sex;
				trees[j].addPerson(input, year, month, day, sex);
			}
			else
				std::cout << "No such tree\n\n";
			break;
		case 5:			//addPersonWP
			std::cin >> j;
			if (trees.gNum() > j)
			{
				unsigned char day, month;
				short year;
				bool sex;
				unsigned father, mother;
				std::cin >> input >> day >> month >> year >> sex >> father >> mother;
				trees[j].addPerson(input, year, month, day, sex, father, mother);
			}
			else
				std::cout << "No such tree\n\n";
			break;
		case 6:			//addRelation
			std::cin >> j;
			if (trees.gNum() > j)
			{
				char rel[16];
				std::cin >> firstName >> rel >> secondName;
				while (!strToRel(rel))
				{
					std::cout << "Invalid Relation, try again!\n";
					std::cin >> rel;
				}
				if(!trees[j].addRelation(firstName, strToRel(rel), secondName))
					std::cout << "Failure! One or both of the relatives don't exist.\n\n";
			}
			else
				std::cout << "No such tree\n\n";
			break;
		case 7:			//addRelationID
			std::cin >> j;
			if (trees.gNum() > j)
			{
				unsigned firstId, secondId;
				char rel[16];
				std::cin >> firstId >> rel >> secondId;
				while (!strToRel(rel))
				{
					std::cout << "Invalid Relation, try again!\n";
					std::cin >> rel;
				}
				if(trees[j].addRelation(firstId, strToRel(rel), secondId))
					std::cout << "Failure! One or both of the relatives don't exist.\n\n";
			}
			else
				std::cout << "No such tree\n\n";
			break;
		case 8:			//findID
			std::cin >> j;
			if (trees.gNum() > j)
			{
				std::cin >> input;
				unsigned id = trees[j].findId(input);
				if (id == Nobody)
					std::cout << "No such person in tree " << j <<"\n\n";
				else
					std::cout << id << "\n\n";
			}
			else
				std::cout << "No such tree\n\n";
			break;
		case 9:			//equate
			std::cin >> j >> q;
			if (trees.gNum() > j && trees.gNum() > q)
				trees[j] = trees[q];
			else
				std::cout << "No such tree\n\n";
			break;
		case 10:		//combine
			std::cin >> j >> q;
			if (trees.gNum() > j && trees.gNum() > q)
				trees[j] += trees[q];
			else
				std::cout << "No such tree\n\n";
			break;
		case 11:		//subtract
			std::cin >> j >> q;
			if (trees.gNum() > j && trees.gNum() > q)
				trees[j] -= trees[q];
			else
				std::cout << "No such tree\n\n";
			break;
		case 12:		//removePerson
			std::cin >> j;
			if (trees.gNum() > j)
			{
				std::cin >> firstName;
				if (trees[j].findId(firstName) != Nobody)
					trees[j].removePerson(firstName);
				else
					std::cout << "No such member\n\n";
			}
			else
				std::cout << "No such tree\n\n";
			break;
		case 13:		//removePersonID
			std::cin >> j;
			if (trees.gNum() > j)
			{
				std::cin >> q;
				if (trees[j].gNumP() > q)
					trees[j].removePerson(q);
				else
					std::cout << "No such member\n\n";
			}
			else
				std::cout << "No such tree\n\n";
			break;
		case 14:		//removeRelation
			std::cin >> j;
			if (trees.gNum() > j)
			{
				std::cin >> firstName >> secondName;
				if (trees[j].gNumP() > trees[j].findId(firstName) && trees[j].gNumP() > trees[j].findId(secondName))
					trees[j].removeRelation(firstName, secondName);
				else
					std::cout << "No such member\n\n";
			}
			else
				std::cout << "No such tree\n\n";
			break;
		case 15:		//removeRelationID
			std::cin >> j;
			if (trees.gNum() > j)
			{
				unsigned g;
				std::cin >> q >> g;
				if (trees[j].gNumP() > q && trees[j].gNumP() > g)
					trees[j].removeRelation(q, g);
				else
					std::cout << "No such member\n\n";
			}
			else
				std::cout << "No such tree\n\n";
			break;
		case 16:		//addTree
			std::cin >> input;
			newTree = new Tree(input);
			trees.push(*newTree);
			delete newTree;
			break;
		case 17:		//printRelatives
			std::cin >> j;
			if (trees.gNum() > j)
			{
				std::cin >> q;
				if (trees[j].gNumP() > q)
					trees[j].printRel(q);
			}
			else
				std::cout << "No such tree\n\n";
			break;
		case 18:		//printMember
			std::cin >> j;
			if (trees.gNum() > j)
			{
				std::cin >> q;
				if (trees[j].gNumP() > q)
					trees[j].printMember(q);
			}
			else
				std::cout << "No such tree\n\n";
			break;
		}

	} while (!quit);

	return 0;
}
