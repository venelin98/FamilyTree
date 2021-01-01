#include<iostream>
#include"Tree.h"
#include"Help.h"

int main()
{
	/*Tree test1("Dechkovi");	//addTree Dechkovi addTree Karamanovi load 0 load 1 (to work with these example trees)
	Tree test2("Karamanovi");
	
	test1.addPerson("Rumen", 1968, 8, 9, 0);
	test1.addPerson("Nadejda", 1972, 12, 15, 1);
	test1.addRelation(0, Husband, 1);
	test1.addPerson("Venelin", 1998, 6, 9, 0, 0, 1);
	test1.addPerson("Vasil", 2001, 1, 16, 0, 0, 1);
	test1.addRelation(2, Brother, 3);
	test1.addPerson("Maria-Veronika", 2009, 9, 3, 1, 0, 1);
	test1.addRelation(2, Brother, 4);
	test1.addRelation(3, Brother, 4);

	test2.addPerson("Vasil Dimitrov", 1941, 5, 18, 0);
	test2.addPerson("Maria", 0, 0, 0, 1);
	test2.addRelation(0, Husband, 1);
	test2.addPerson("Dimitar", 0, 0, 0, 0, 0, 1);
	test2.addPerson("Nadejda", 1972, 12, 15, 1, 0, 1);
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
	short i; //Number of the entered command
	const short numCom = 23;
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
		"subtract",			//11
		"removePerson",     //12
		"removePersonID",   //13
		"removeRelation",   //14
		"removeRelationID", //15
		"addTree",          //16
		"prtRelatives",		//17
		"prtMember",		//18
		"prtAncestors",		//19
		"chooseTree",		//20
		"prtCommonAncestor",//21
		"prtOldestAncestors"//22
	};
	
	unsigned curTree = 0,	//Currently selected tree ID
		id, secondId;		//Indexes
	Tree *newTree;
	char name[128], secondName[128];
	unsigned char day, month;
	short year;
	bool sex;
	unsigned father, mother;

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
			std::cout << "Enter new name\n\n";
			std::cin >> name;
			trees[curTree].rename(name);
			break;
		case 2:			//load
			if (!trees[curTree].loadTree())
				std::cout << "File doesnt exist or is empty.\n\n";
			break;
		case 3:			//save
			trees[curTree].saveTree();
			break;
		case 4:			//addPerson
			std::cin >> name >> day >> month >> year >> sex;
			trees[curTree].addPerson(name, year, month, day, sex);
			break;
		case 5:			//addPersonWP
			std::cin >> name >> day >> month >> year >> sex >> father >> mother;
			trees[curTree].addPerson(name, year, month, day, sex, father, mother);
			break;
		case 6:			//addRelation
			std::cin >> name >> input >> secondName;
			while (!strToRel(input))
			{
				std::cout << "Invalid Relation, try again!\n";
				std::cin >> input;
			}
			if(!trees[curTree].addRelation(name, strToRel(input), secondName))
				std::cout << "Failure! One or both of the relatives don't exist.\n\n";
			break;
		case 7:			//addRelationID
			std::cin >> id >> input >> secondId;
			while (!strToRel(input))
			{
				std::cout << "Invalid Relation, try again!\n";
				std::cin >> input;
			}
			if(trees[curTree].addRelation(id, strToRel(input), secondId))
				std::cout << "Failure! One or both of the relatives don't exist.\n\n";
			break;
		case 8:			//findID
			std::cin >> name;
			id = trees[curTree].findId(name);
			if (id == Nobody)
				std::cout << "No such person in tree " << curTree <<"\n\n";
			else
					std::cout << id << "\n\n";
			break;
		case 9:			//equate
			std::cin >> id >> secondId;
			trees[id] = trees[secondId];
			break;
		case 10:		//combine
			std::cin >> id >> secondId;
			trees[id] += trees[secondId];
			break;
		case 11:		//subtract
			std::cin >> id >> secondId;
			trees[id] -= trees[secondId];
			break;
		case 12:		//removePerson
			std::cin >> name;
			if (trees[curTree].findId(name) != Nobody)
				trees[curTree].removePerson(name);
			else
				std::cout << "No such member!\n\n";
			break;
		case 13:		//removePersonID
			std::cin >> id;
			if (trees[curTree].gNumP() > id)
				trees[curTree].removePerson(id);
			else
				std::cout << "No such member!\n\n";
			break;
		case 14:		//removeRelation
			std::cin >> name >> secondName;
			if (trees[curTree].gNumP() > trees[curTree].findId(name) && trees[curTree].gNumP() > trees[curTree].findId(secondName))
				trees[curTree].removeRelation(name, secondName);
			else
				std::cout << "No such member!\n\n";
			break;
		case 15:		//removeRelationID
			std::cin >> id >> secondId;
			if (trees[curTree].gNumP() > id && trees[curTree].gNumP() > secondId)
				trees[curTree].removeRelation(id, secondId);
			else
				std::cout << "No such member\n\n";
			break;
		case 16:		//addTree
			std::cin >> name;
			newTree = new Tree(name);
			trees.push(*newTree);
			delete newTree;
			break;
		case 17:		//printRelatives
			std::cin >> id;
			if (id < trees[curTree].gNumP())
				trees[curTree].printRel(id);
			else
				std::cout << "No such member\n\n";
			break;
		case 18:		//printMember
			std::cin >> id;
			if (id < trees[curTree].gNumP())
				trees[curTree].printMember(id);
			else
				std::cout << "No such member\n\n";
			break;
		case 19:		//printAncestors
			std::cin >> id;
			/*if (id < trees[curTree].gNumP())
				trees[curTree].printAncestors(id);
			else
				std::cout << "No such member\n\n";*/
			break;
		case 20:		//chooseTree
			std::cout << "Enter tree ID\n\n";
			std::cin >> id;
			if (id < trees.gNum())
				curTree = id;
			else
				std::cout << "No such tree\n\n";
			break;
		case 21:		//prtCommonAncestor
			std::cin >> id >> secondId;
			if (id < trees[curTree].gNumP() || secondId < trees[curTree].gNumP())
				trees[curTree].printMember(trees[curTree].findCommonAncestor(id, secondId));
			else
				std::cout << "No such member\n\n";
			break;
		case 22:		//prtOldestAncestors
			std::cin >> id;
			if (id < trees[curTree].gNumP())
				trees[curTree].printOldestAncestors(id);
			else
				std::cout << "No such member\n\n";
			break;
		}

	} while (!quit);

	return 0;
}