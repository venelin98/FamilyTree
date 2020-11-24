#include"Help.h"
#include"Tree.h"

unsigned strLen(const char* str)
{
	unsigned len = 0;
	for (; str[len] != '\0'; ++len)
		;
	return len;
}	

void strCopy(char *to, const char* from)
{
	unsigned i = 0;
	for (; from[i] != '\0'; ++i)
		to[i] = from[i];
	to[i] = '\0';
}

bool strComp(const char* first, const char* second)
{
	for (unsigned i = 0; first[i] != '\0' || second[i] != '\0'; ++i)
	{
		if (first[i] != second[i])
			return 0;
	}
	return 1;
}

char* mergeStr(const char* first, const char* second) //Create new string from 2 existing and return it
{
	char *result = new char[strLen(first) + strLen(second) + 1];
	unsigned j = 0;
	for (unsigned i = 0; first[i] != '\0'; ++i, ++j)
		result[j] = first[i];
	for (unsigned i = 0; second[i] != '\0'; ++i, ++j)
		result[j] = second[i];
	result[j] = '\0';
	return result;
}

Relation strToRel(const char* str)
{
	if (strComp(str, "Father"))
		return Father;
	else if (strComp(str, "Mother"))
		return Mother;
	else if (strComp(str, "Son"))
		return Son;
	else if (strComp(str, "Daughter"))
		return Daughter;
	else if (strComp(str, "Brother"))
		return Brother;
	else if (strComp(str, "Sister"))
		return Sister;
	else if (strComp(str, "HalfBrother"))
		return HalfBrother;
	else if (strComp(str, "HalfSister"))
		return HalfSister;
	else if (strComp(str, "Wife"))
		return Wife;
	else if (strComp(str, "Husband"))
		return Husband;
	else if (strComp(str, "ExWife"))
		return ExWife;
	else if (strComp(str, "ExHusband"))
		return ExHusband;
	return Invalid;
}