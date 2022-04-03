#include "GLtable.h"

int main()
{
	//定义一个字符型数组
	char s[30];

	//赋值
	cin >> s;

	char* c = s;

	//创建广义表
	GLNode* g = CreateGL(c);

	//输出广义表
	DispGL(g);
	cout << endl;

	//求广义表长度
	cout << "广义表长度为：" << GLLength(g) << endl;

	//求广义表深度
	cout << "广义表深度为：" << GLDepth(g) << endl;

	//销毁广义表
	DestroyGL(g);
}