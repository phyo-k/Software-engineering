#include <fstream>
#include <iostream>
#include <malloc.h>
#include "functions.h"

using namespace std;

void Init(); //���͸��� MB �޸� ���� �Լ�
void Select();//���� ��� ���� �Լ�
void Menu();//�޴��Լ�
void Flash_read();//���� ���� ������ �б�
void Flash_write();//���� ���� ������ ����
void Flash_erase();//���� ���� ������ �����
void Print_table_s();//���� �������̺� ���
void FTL_read();//��� ���� ������ �б�
void FTL_write();//��� ���� ������ ����
void FTL_erase();//��� ���� ������ �����
void Print_table_b();//��� ���� ���̺� ���

int  main() {
	int num1, num2;//�޴� ����
	string answer;//���Ῡ��

	cout << "-------------- �޸� �۵� --------------" << endl;

	while (true) {
		Select();
		cout << "���ι�� ����>> "; cin >> num1;
		if (num1 > 2) {
			cout << "�߸� �Է��߽��ϴ�. 0~2�� �Է��ϼ���." << endl;
			continue;
		}
		switch (num1) {
		case 1:
			Init();
			PSN = (int*)malloc(sizeof(int) * megabytes);
			while(true) {
				Menu();
				cout << "��� ����>> "; cin >> num2;
				if (num2 > 4) {
					cout << "�߸� �Է��߽��ϴ�. 0~4�� �Է��ϼ���." << endl;
					continue;
				}
				switch (num2) {
				case 1:
					Flash_read();
					break;
				case 2:
					Flash_write();
					break;
				case 3:
					Flash_erase();
					break;
				case 4:
					Print_table_s();
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
			break;
		case 2:
			Init();
			PBN = (int*)malloc(sizeof(int) * megabytes);
			while (true) {
				Menu();
				cout << "��� ����>> "; cin >> num2;
				if (num2 > 4) {
					cout << "�߸� �Է��߽��ϴ�. 0~3�� �Է��ϼ���." << endl;
					continue;
				}
				switch (num2) {
				case 1:
					FTL_read();
					break;
				case 2:
					FTL_write();
					break;
				case 3:
					FTL_erase();
					break;
				case 4:
					Print_table_b();
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
	for (int x = 0; x < megabytes; x++)
		delete &PSN[x];//�޸� ����

	for (int x = 0; x < megabytes; x++)
		delete& PBN[x];//�޸� ����

	return 0;
}