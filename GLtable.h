#pragma once
#include <iostream>
using namespace std;

typedef char ElemType;

typedef struct lnode
{
	int tag;						//������ͱ�ʶ
	union
	{
		ElemType data;				//���ԭ��ֵ
		struct lnode* sublist;		//ָ���ӱ��ָ��
	}val;
	struct lnode* link;				//ָ����һ��Ԫ��
}GLNode;

GLNode* CreateGL(char*& s);				//�����������ʽ�洢
void DestroyGL(GLNode*& g);				//���ٹ����
void DispGL(GLNode* g);					//��������
int GLLength(GLNode* g);				//������ĳ���
int GLDepth(GLNode* g);					//����������

GLNode* CreateGL(char*& s)				//�����������ʽ�洢
{
	GLNode* g;
	char ch = *s++;							//ȡһ���ַ�
	if (ch != '\0')							//��sδɨ����
	{
		g = (GLNode*)malloc(sizeof(GLNode));//����һ���½��
		if (ch == '(')						//��ǰ�ַ�Ϊ'('ʱ
		{
			g->tag = 1;						//�½����Ϊ��ͷ�������
			g->val.sublist = CreateGL(s);		//�ݹ鹹���ֱ����ӵ���ͷ���
		}
		else if (ch == ')')
			g = NULL;						//����')'�ַ���g��Ϊ��
		else								//Ϊԭ���ַ�
		{
			g->tag = 0;
			g->val.data = ch;
		}
	}
	else									//sɨ����,g��Ϊ��
		g = NULL;
	ch = *s++;								//ȡ��һ���ַ�
	if (g != NULL)							//sδɨ���꣬���������ֵܽ��
		if (ch == ',')						//��ǰ�ַ�Ϊ','
			g->link = CreateGL(s);			//�ݹ鹹���ֵܽ��
		else								//û���ֵ���,���ֵ�ָ����ΪNULL
			g->link = NULL;
	return g;
}

void DestroyGL(GLNode*& g)				//���ٹ����
{
	if (g->tag == 1)
	{
		GLNode* g1, * g2;
		g1 = g->val.sublist;					//g1ָ������ĵ�һ��Ԫ��
		while (g1 != NULL)						//��������Ԫ��
		{
			if (g1->tag == 0)					//��Ϊԭ�ӽ��
			{
				g2 = g1->link;					//g2��ʱ�����ֵܽ��
				free(g1);						//�ͷ�g1��ָ��ԭ�ӽ��
				g1 = g2;						//g1ָ�����ֵܽ��
			}
			else								//��Ϊ�ֱ�
			{
				g2 = g1->link;					//g2��ʱ�����ֵܽ��
				DestroyGL(g1);					//�ݹ��ͷ�g1��ָ�ֱ�Ŀռ�
				g1 = g2;						//g1ָ�����ֵܽ��
			}
		}
	}
	free(g);								//�ͷ�ͷ���ռ�
}

void DispGL(GLNode* g)					//��������
{
	if (g != NULL)							//��Ϊ���ж�
	{
		if (g->tag == 0)					//g��Ԫ��Ϊԭ��ʱ
			cout << g->val.data;
		else
		{
			cout << "(";					//���'('
			if (g->val.sublist == NULL)		//Ϊ�ձ�ʱ
				cout << "#";
			else							//��Ϊ�ձ�ʱ
				DispGL(g->val.sublist);		//�ݹ�����ֱ�
			cout << ")";					//���')'
		}
		if (g->link != NULL)
		{
			cout << ",";
			DispGL(g->link);				//�ݹ�����ֱ�
		}
	}
}

int GLLength(GLNode* g)					//������ĳ���
{
	if (g->tag == 0)						//��Ϊ�����ʱ���س���Ϊ-1
		return -1;
	int n = 0;								//�ۼ�Ԫ�ظ�������ʼֵΪ0
	GLNode* g1;
	g1 = g->val.sublist;					//g1ָ������ĵ�һ��Ԫ��
	while (g1 != NULL)						//ɨ������Ԫ��
	{
		n++;								//Ԫ�ظ���+1
		g1 = g1->link;
	}

	return n;								//����Ԫ�ظ���
}

int GLDepth(GLNode* g)					//����������
{
	GLNode* g1;
	int maxd = 0, dep;
	if (g->tag == 0)
		return 0;							//Ϊԭ��ʱ����0
	g1 = g->val.sublist;					//g1ָ���һ��Ԫ��
	if (g1 == NULL)							//Ϊ�ձ�ʱ����1
	{
		return 1;
	}
	while (g1 != NULL)						//��������ÿһ��Ԫ��
	{
		if (g1->tag == 1)					//Ԫ��Ϊ�ֱ�����
		{
			dep = GLDepth(g1);				//�ݹ��������ֱ�����
			if (dep > maxd)					//maxdΪͬһ����ֱ�����ȵ����ֵ
				maxd = dep;
		}
		g1 = g1->link;						//ʹg1ָ����һ��Ԫ��
	}

	return maxd + 1;
}