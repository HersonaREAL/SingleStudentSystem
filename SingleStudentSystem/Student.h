#pragma once
#include<iostream>
#include <atlstr.h>
#include<fstream>
#include<cstring>
using namespace std;
struct Student
{
	char Name[32];
	char ID[10];
	char Sex[6];
	char Math[5];
	char CPP[5];
};

typedef struct Node* List;
typedef struct Node* Head;
struct Node
{
	int ListNum;
	Student Stu;
	List Next = NULL;
};

class Management
{
public:
	Head LoadData(CString filename);//¶ÁÈ¡Êý¾Ý
	void DeleteALL(Head HD);
};

#pragma once