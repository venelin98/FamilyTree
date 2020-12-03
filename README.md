# FamilyTree

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

How to use - input one of the following commands:

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
	
	***TO DO***
	
	"subtract"  (S/E) FirstTreeID (S/E) SecondTreeID - Enter the IDs of two trees, the members that are present in both trees are removed from the first tree
	
	"removePerson", 
	"removePersonID",  
	"removeRelation",   
	"removeRelationID"
	"printRelatives",  
	"printMember"
