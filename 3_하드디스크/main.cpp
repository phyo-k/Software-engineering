#include <fstream>
#include <iostream>
#include <malloc.h>
#include "Funcions.h"

using namespace std;

void Init(); //MB �޸� ���� �Լ�
void Menu();//�޴��Լ�
void Read();//������ �б�
void Write();//������ ����
void Erase();//������ �����

int  main() {
	int num;//�޴� ����
	int rdNum;//�б� ��ȣ
	int wtNum;//���� ��ȣ
	char wt;//�� ������
	int delNum;//���� ��ȣ
	string answer;//���Ῡ��

	Init();
	PSN = (char*)malloc(sizeof(char) * megabytes);
	cout << "-------------- �޸� �۵� --------------" << endl;
	while (true) {
		Menu();
		cout << "�޴� �Է�>> "; cin >> num;
		if (num > 3) {
			cout << "�߸� �Է��߽��ϴ�. 0~3�� �Է��ϼ���." << endl;
			continue;
		}
		switch (num) {
		case 1:
			Read(); //���� ������ ������ �б�
			break;
		case 2:
			Write(); //���� ������ ������ ����
			break;
		case 3:
			Erase();//��� ������ ������ �����
			break;
		case 0:
			cout << "������ �����Ͻðڽ��ϱ�?(��/�ƴϿ�)>> "; cin >> answer;
			if (answer == "��")
				exit(1);
			else if (answer == "�ƴϿ�")
				continue;
			else {
				cout << "�� / �ƴϿ��� �Է��ϼ���." << endl;
				continue;
			}
			cout << endl;
		}
	}
	free(PSN);
	return 0;
}
