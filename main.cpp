#include "GLtable.h"

int main()
{
	//����һ���ַ�������
	char s[30];

	//��ֵ
	cin >> s;

	char* c = s;

	//���������
	GLNode* g = CreateGL(c);

	//��������
	DispGL(g);
	cout << endl;

	//��������
	cout << "�������Ϊ��" << GLLength(g) << endl;

	//���������
	cout << "��������Ϊ��" << GLDepth(g) << endl;

	//���ٹ����
	DestroyGL(g);
}