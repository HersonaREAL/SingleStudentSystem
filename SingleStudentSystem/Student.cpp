#include"pch.h"
#include"Student.h"
#include"SingleStudentSystem.h"


Head Management::LoadData(CString filename)
{
	//��ȡ����
	fstream fp;
	fp.open(filename);
	//ͳ���ļ�����
	int count = 0;
	while (!fp.eof())
	{
		char line[512];
		fp.getline(line, 512, '\n');
		count++;
	}
	theApp.HD->ListNum = count;//��¼��������������ͷ��

	//ʹ�ļ�ָ�뷵��ͷλ��
	fp.clear();
	fp.seekg(0);

	//���ļ����ݶ�������
	List tp = theApp.HD;//��ʱ����
	for (int i = 0; i < theApp.HD->ListNum; i++) {
		//�½�����
		List temp = new Node;
		tp->Next = temp;
		temp->Next = NULL;
		tp = temp;
	}
	for (tp = theApp.HD->Next; tp != NULL; tp = tp->Next) {
		//д��
		fp >> tp->Stu.ID >> tp->Stu.Name >> tp->Stu.Sex >> tp->Stu.Math >> tp->Stu.CPP;
	}

	return theApp.HD;
}

void Management::DeleteALL(Head H) {
	//ɾ�������е�����
	List tempbefore, tempafter;
	tempbefore = H->Next;
	tempafter = H->Next->Next;
	for (int i = 0; i < H->ListNum; i++) {
		delete tempbefore;
		if (i != H->ListNum - 1) {//ָ���ƶ������һ������delete����next��ָ����Ҫ�ж�
			tempbefore = tempafter;
			tempafter = tempafter->Next;
		}
		else
			tempbefore = tempafter;
	}
	theApp.HD->Next = NULL;//��ԭȫ������ͷ
}