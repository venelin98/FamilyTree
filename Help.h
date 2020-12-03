#pragma once

enum Relation : char;

unsigned strLen(const char* str);
void strCopy(char *to, const char* from);
bool strComp(const char* firts, const char* second);	//0 - diffrent 1 - same
char* mergeStr(const char* first, const char* second);
Relation strToRel(const char* str);