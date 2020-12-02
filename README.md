# FamilyTree

The program works with an array of trees numbered from 0. In order do execute a command on a tree you need to enter its number(treeID).
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
	
	"rename" (S/E) treeID (S/E) NewName (S/E) - Renames a tree
	
	"load" (S/E) treeID (S/E) - Loads a tree based on its name
	
	"save" (S/E) treeID (S/E) - Saves a tree based on its name
	
	"addPerson" (S/E) treeID (S/E) BirthDay (S/E) BirthMonth (S/E) BirthYear (S/E) PersonSex (S/E) - Add a person to a tree with treeID with a birthday on BirthDay.BirthMonth.BirthYear and sex (PersonSex) 0 = Male 1 = Female
	
	"addPersonWP" (S/E) treeID (S/E) BirthDay (S/E) BirthMonth (S/E) BirthYear (S/E) PersonSex (S/E) FatherID (S/E) MotherID - The same as addPerson but adds father and motherbased on their IDs
	
	"addRelation" (S/E) FirstRelativeName (S/E) Relation  (S/E) SecondRelativeName - Adds a relation betwean two members based on their full names
	"addRelationID",    
	"findID",           
	"equate",           
	"combine",          
	"substract",        
	"removePerson",     
	"removePersonID",  
	"removeRelation",   
	"removeRelationID"
	"addTree" (S/E) TreeName (S/E) - Adds a tree to the array
	
	"printRelatives",  
	"printMember"
