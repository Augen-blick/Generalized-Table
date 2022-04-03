#pragma once
#include <iostream>
using namespace std;

typedef char ElemType;

typedef struct lnode
{
	int tag;						//结点类型标识
	union
	{
		ElemType data;				//存放原子值
		struct lnode* sublist;		//指向子表的指针
	}val;
	struct lnode* link;				//指向下一个元素
}GLNode;

GLNode* CreateGL(char*& s);				//建立广义表链式存储
void DestroyGL(GLNode*& g);				//销毁广义表
void DispGL(GLNode* g);					//输出广义表
int GLLength(GLNode* g);				//求广义表的长度
int GLDepth(GLNode* g);					//求广义表的深度

GLNode* CreateGL(char*& s)				//建立广义表链式存储
{
	GLNode* g;
	char ch = *s++;							//取一个字符
	if (ch != '\0')							//若s未扫描完
	{
		g = (GLNode*)malloc(sizeof(GLNode));//创建一个新结点
		if (ch == '(')						//当前字符为'('时
		{
			g->tag = 1;						//新结点作为表头结点或表结点
			g->val.sublist = CreateGL(s);		//递归构造字表并链接到表头结点
		}
		else if (ch == ')')
			g = NULL;						//遇到')'字符，g置为空
		else								//为原子字符
		{
			g->tag = 0;
			g->val.data = ch;
		}
	}
	else									//s扫描完,g置为空
		g = NULL;
	ch = *s++;								//取下一个字符
	if (g != NULL)							//s未扫描完，继续构造兄弟结点
		if (ch == ',')						//当前字符为','
			g->link = CreateGL(s);			//递归构造兄弟结点
		else								//没有兄弟了,将兄弟指针置为NULL
			g->link = NULL;
	return g;
}

void DestroyGL(GLNode*& g)				//销毁广义表
{
	if (g->tag == 1)
	{
		GLNode* g1, * g2;
		g1 = g->val.sublist;					//g1指向广义表的第一个元素
		while (g1 != NULL)						//遍历所有元素
		{
			if (g1->tag == 0)					//若为原子结点
			{
				g2 = g1->link;					//g2临时保存兄弟结点
				free(g1);						//释放g1所指的原子结点
				g1 = g2;						//g1指向后继兄弟结点
			}
			else								//若为字表
			{
				g2 = g1->link;					//g2临时保存兄弟结点
				DestroyGL(g1);					//递归释放g1所指字表的空间
				g1 = g2;						//g1指向后继兄弟结点
			}
		}
	}
	free(g);								//释放头结点空间
}

void DispGL(GLNode* g)					//输出广义表
{
	if (g != NULL)							//表不为空判断
	{
		if (g->tag == 0)					//g的元素为原子时
			cout << g->val.data;
		else
		{
			cout << "(";					//输出'('
			if (g->val.sublist == NULL)		//为空表时
				cout << "#";
			else							//不为空表时
				DispGL(g->val.sublist);		//递归输出字表
			cout << ")";					//输出')'
		}
		if (g->link != NULL)
		{
			cout << ",";
			DispGL(g->link);				//递归输出字表
		}
	}
}

int GLLength(GLNode* g)					//求广义表的长度
{
	if (g->tag == 0)						//不为广义表时返回长度为-1
		return -1;
	int n = 0;								//累计元素个数，初始值为0
	GLNode* g1;
	g1 = g->val.sublist;					//g1指向广义表的第一个元素
	while (g1 != NULL)						//扫描所有元素
	{
		n++;								//元素个数+1
		g1 = g1->link;
	}

	return n;								//返回元素个数
}

int GLDepth(GLNode* g)					//求广义表的深度
{
	GLNode* g1;
	int maxd = 0, dep;
	if (g->tag == 0)
		return 0;							//为原子时返回0
	g1 = g->val.sublist;					//g1指向第一个元素
	if (g1 == NULL)							//为空表时返回1
	{
		return 1;
	}
	while (g1 != NULL)						//遍历表中每一个元素
	{
		if (g1->tag == 1)					//元素为字表的情况
		{
			dep = GLDepth(g1);				//递归调用求出字表的深度
			if (dep > maxd)					//maxd为同一层的字表中深度的最大值
				maxd = dep;
		}
		g1 = g1->link;						//使g1指向下一个元素
	}

	return maxd + 1;
}