# FamilyTree

I wrote this program in C ++ on Visual Studio 2017, starting with a blank project. I used iostream for input and output and fstream for saving and loading trees. Instead of using vector, I chose to write a dynamic array myself. I used HxD hex editor to look for errors in the files.
In the program, "family trees" are weighted graphs implemented through a list of neighbors. The program allows for addition, subtraction (removal of common members) and comparison of trees, saving them to and loading them from files and more.

Thus large constructs consisting of multiple family trees can be created and managed using this program.

# How to use

The program works with an array of trees numbered from 0. In order to execute a command on a tree you need to enter its number(treeID).
(S/E) = (Space/Enter)

Relations are as followed and cap sensitive:

	Father
	Mother
	Son
	Daughter
	Brother
	Sister
	HalfBrother
	HalfSister
	Wife
	Husband
	ExWife
	ExHusband

List of commands:

 	"quit" - close the program
	
	"addTree" (S/E) TreeName (S/E) - Adds a tree to the array
	
	"rename" (S/E) TreeID (S/E) NewName (S/E) - Renames a tree
	
	"load" (S/E) TreeID (S/E) - Loads a tree based on its name
	
	"save" (S/E) TreeID (S/E) - Saves a tree based on its name
	
	"addPerson" (S/E) TreeID (S/E) BirthDay (S/E) BirthMonth (S/E) BirthYear (S/E) PersonSex (S/E) - Add a person to a tree with treeID with a birthday on BirthDay.BirthMonth.BirthYear and sex (PersonSex) 0 = Male 1 = Female
	
	"addPersonWP" (S/E) TreeID (S/E) BirthDay (S/E) BirthMonth (S/E) BirthYear (S/E) PersonSex (S/E) FatherID (S/E) MotherID - The same as addPerson but adds father and motherbased on their IDs
	
	"addRelation" (S/E) TreeID (S/E) FirstRelativeName (S/E) Relation  (S/E) SecondRelativeName - Adds a relation betwean two members based on their full names
	
	"addRelationID" (S/E) TreeID (S/E) FirstRelativeID (S/E) Relation  (S/E) SecondRelativeID - Same as addElation but based on ID
	
	"findID" (S/E) TreeID (S/E) SoughtPersonName (S/E) - Prints the ID of a person with the given name
	
	"equate"  (S/E) FirstTreeID (S/E) SecondTreeID - Enter the IDs of two trees, the first one becomes equal to the second one
	
	"combine"  (S/E) FirstTreeID (S/E) SecondTreeID - Enter the IDs of two trees, the first one becomes equal to the combinatio of the two
	
	"subtract"  (S/E) FirstTreeID (S/E) SecondTreeID - Enter the IDs of two trees, the members that are present in both trees are removed from the first tree
	
	"removePerson" (S/E) TreeID (S/E) Name - Remove person with the given name
	
	"removePersonID" (S/E) TreeID (S/E) Name - Remove person with the given ID
	
	"removeRelation" (S/E) TreeID (S/E) FirstName  (S/E) SecondName - Remove the relation betwean the people with the given names if they have one
	
	"removeRelationID" (S/E) TreeID (S/E) FirstName  (S/E) SecondName - Same as removeRelation but with IDs instead
	
	"printRelatives" (S/E) TreeID (S/E) PersonID - Print the relatives the person with the given ID in the console
	
	"printMember" (S/E) TreeID (S/E) PersonID - Print the personal data of a member on the console
