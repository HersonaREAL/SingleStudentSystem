#include"pch.h"
#include"Student.h"
#include"SingleStudentSystem.h"


Head Management::LoadData(CString filename)
{
	//读取数据
	fstream fp;
	fp.open(filename);
	//统计文件行数
	int count = 0;
	while (!fp.eof())
	{
		char line[512];
		fp.getline(line, 512, '\n');
		count++;
	}
	theApp.HD->ListNum = count;//记录链表数（除链表头）

	//使文件指针返回头位置
	fp.clear();
	fp.seekg(0);

	//把文件数据读入链表
	List tp = theApp.HD;//临时变量
	for (int i = 0; i < theApp.HD->ListNum; i++) {
		//新建链表
		List temp = new Node;
		tp->Next = temp;
		temp->Next = NULL;
		tp = temp;
	}
	for (tp = theApp.HD->Next; tp != NULL; tp = tp->Next) {
		//写入
		fp >> tp->Stu.ID >> tp->Stu.Name >> tp->Stu.Sex >> tp->Stu.Math >> tp->Stu.CPP;
	}

	return theApp.HD;
}

void Management::DeleteALL(Head H) {
	//删除链表中的数据
	List tempbefore, tempafter;
	tempbefore = H->Next;
	tempafter = H->Next->Next;
	for (int i = 0; i < H->ListNum; i++) {
		delete tempbefore;
		if (i != H->ListNum - 1) {//指针移动到最后一个链表，delete掉后next无指向，需要判断
			tempbefore = tempafter;
			tempafter = tempafter->Next;
		}
		else
			tempbefore = tempafter;
	}
	theApp.HD->Next = NULL;//复原全局链表头
}