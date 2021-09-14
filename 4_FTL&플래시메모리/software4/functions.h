#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h> //malloc, free �Լ� ����
#include <string.h>
using namespace std;

int megabytes;
int sector = megabytes / 512; //���� ����
int block = sector / 32; //��� ����
int* PSN = NULL;
int* PBN = NULL;
//int count;//���͸��� �б� Ƚ��
//ifstream inFile("checking.txt");
//ofstream outFile("checking.txt");

void Init() {
	cout << "�����Ϸ��� �޸� �뷮(MB)�� �Է��ϼ���>> ";
	cin >> megabytes;
	cout << "int������ ������ �Է� �����մϴ�. ���� �ڿ����� �Է��ϼ���." << endl;
	cout << 4*megabytes << "MB �÷��� �޸𸮸� �����մϴ�." << endl;
	megabytes = 1048576 * megabytes;//MB = 1024*1024 (KB->MB) && int�� 4b
	if (megabytes == 0) {
		cout << "�� �޸𸮸� �����Ͽ� ���α׷��� �۵����� �ʽ��ϴ�. 1�̻��� ���ڸ� �Է��ϼ���." << endl;
		exit(0);
	}
}
void Select() {
	cout << "=========================================" << endl;
	cout << "1. ���͸���" << endl;
	cout << "2. ��ϸ���" << endl;
	cout << "0. ����" << endl;
	cout << "=========================================" << endl;
}
void Menu() {
	cout << "=========================================" << endl;
	cout << "1. ������ �б�" << endl;
	cout << "2. ������ ����" << endl;
	cout << "3. ������ �����" << endl;
	cout << "4. ���� ���̺� ���" << endl;
	cout << "0. ����" << endl;
	cout << "=========================================" << endl;
}

//���͸��� ������ �б�; ����=512B->int�� 4����Ʈ�� �� ���ʹ� 128����Ʈ
void Flash_read() {
	int rdNum_S;
	cout << "���� �������� ��ȣ�� �Է��ϼ���>> "; cin >> rdNum_S;
	
	if (rdNum_S == 0) {
		if (PSN[0]<0)
			cout << "�����Ͱ� �������� �ʽ��ϴ�." << endl;
		else {
			cout << "0��° �����ʹ� " << PSN[0] << "�Դϴ�." << endl;
			cout << "����Ʈ ��: " << _msize(PSN) << " " << "����Ʈ,  �迭 ����: " << _msize(PSN) / sizeof(PSN) << "��" << endl;
		}
	}
	else {
		rdNum_S *= 128;
		for (int j = rdNum_S; j < megabytes; j++) {
			if (rdNum_S == j) {
				cout << j << "��° �����ʹ� " << PSN[j] << "�Դϴ�." << endl;
				cout << "����Ʈ ��" << _msize(PSN) << " " << "�迭 ����" << _msize(PSN) / sizeof(PSN) << endl;
				break;
			}
		}
	}
	cout << endl;
}

//���͸��� ������ ����; ����=512B->int�� 128B
void Flash_write() {
	int i = 0;  int wtNum_S = 0; int wt_S;
	cout << "������ �����͸� �Է��ϼ���." << endl;
	cout << "�� ��°>> ";  cin >> wtNum_S;
	cout << "�� ������>> "; cin >> wt_S;
		if (wtNum_S == 0) {
			for (int l = 0; l < 128; l++)
				PSN[l] = wt_S;
			cout << "write(" << wtNum_S << ", '" << wt_S << "') �� ����Ǿ����ϴ�." << endl;
		}
		else {
			wtNum_S *= 128;
			for (i = 128; i < megabytes; i++) {//�� ����
				if (wtNum_S == i) {
					for (i = wtNum_S; i < (wtNum_S + 128); i++)
						PSN[i] = wt_S;
					break;
				}
			}
			cout << "write(" << wtNum_S << ", '" << wt_S << "') �� ����Ǿ����ϴ�." << endl;
		}
}

//���͸��� ������ �����; 1��� = 32���� = 16,384B ->1MB���� 64�� ���
void Flash_erase() {
	int k = 0; int delNum_S;
	cout << "������� �����͸� �Է��ϼ���." << endl;
	cout << "�� ��°>> "; cin >> delNum_S;
	cout << delNum_S << "��° �����͸� ����ϴ�." << endl;
	if (delNum_S == 0) {
		for (int l = 0; l < 4096; l++)
			delete &PSN[k];
	}
	else {
		delNum_S *= 4096;
		for (k = 4096; k < megabytes; k++) {//4096����Ʈ*4(������Ÿ��)=�� ���(16384)
			if (delNum_S == k) {
				for (k = delNum_S; k < (delNum_S +4096); k++) {
					delete &PSN[k];
				}
			}
		}
	}
	cout << "�ش� ������ ����� �������ϴ�." << endl;
	cout << "����Ʈ ��" << _msize(PSN) << endl;
}
//���͸��� ���̺� ���
void Print_table_s() {
	cout << "���� ���� ���̺��� ����մϴ�." << endl;
	for (int i = 1; i < megabytes; i++) {
		if (PSN[i] < 0)
			cout << "/ ";
		else 
			cout << PSN[i] << " ";
		if (i % 10 == 0)
			cout << endl;
	}
}
//��ϸ��� ������ �б�
void FTL_read() {
	int rdNum_B;
	cout << "���� �������� ��ȣ�� �Է��ϼ���>> "; cin >> rdNum_B;

	if (rdNum_B == 0) {
		if (PBN[0] < 0)
			cout << "�����Ͱ� �������� �ʽ��ϴ�." << endl;
		else {
			cout << "0��° �����ʹ� " << PBN[0] << "�Դϴ�." << endl;
			cout << "����Ʈ ��: " << _msize(PBN) << " " << "����Ʈ,  �迭 ����: " << _msize(PBN) / sizeof(PBN) << "��" << endl;
		}
	}
	else {
		rdNum_B *= 4096;
		for (int j = rdNum_B; j < megabytes; j++) {
			if (rdNum_B == j) {
				cout << j << "��° �����ʹ� " << PBN[j] << "�Դϴ�." << endl;
				cout << "����Ʈ ��" << _msize(PBN) << " " << "�迭 ����" << _msize(PBN) / sizeof(PBN) << endl;
				break;
			}
		}
	}
	cout << endl;
}
//��ϸ��� ������ ���� -> megabytes/512/32 = sector/32 = �� ��� ���� //1MB�������� 64��� �� ����=�� ���
void FTL_write() {
	int i = 0;  int wtNum_B; int wt_B;
	int wtNum_LBN; int wt_PBN;
	cout << "������ �����͸� �Է��ϼ���." << endl;
	cout << "�� ��°>> ";  cin >> wtNum_B;
	cout << "�� ������>> "; cin >> wt_B;
	wtNum_LBN = wtNum_B / block;
	wt_PBN = wtNum_B % block;
	int l = 0;
	if (wtNum_LBN == 0) {//0�� ���
		for (l = 0; l < 4096; l++)//�� ����� 32����, �� ���ʹ� 512����Ʈ(int�� 4����Ʈ�Ƿ� 128�� ���)
			if (wt_PBN == l) {
				for(l=wt_PBN; l<l+128;l++)
					PBN[l] = wt_PBN;
			}
		cout << "write(" << wtNum_LBN << ", '" << wt_PBN << "') �� ����Ǿ����ϴ�." << endl;
	}
	else {
		wtNum_B *= 4096;
		for (i = 4096; i < megabytes; i++) {//�� ����
			if (wtNum_LBN == i) {
				for (i = wt_PBN; i < i+128; i++)
					PBN[i] = wt_PBN;
				break;
			}
		}
		cout << "write(" << wtNum_B << ", '" << wt_B << "') �� ����Ǿ����ϴ�." << endl;
	}
}
//��ϸ��� ������ �����
void FTL_erase() {
	int k = 0; int delNum_B;
	cout << "������� �����͸� �Է��ϼ���." << endl;
	cout << "�� ��°>> "; cin >> delNum_B;
	cout << delNum_B << "��° �����͸� ����ϴ�." << endl;
	if (delNum_B == 0) {
		for (int l = 0; l < 4096; l++)
			delete& PBN[k];
	}
	else {
		delNum_B *= 4096;
		for (k = 4096; k < megabytes; k++) {//4096����Ʈ*4(������Ÿ��)=�� ���(16384)
			if (delNum_B == k) {
				for (k = delNum_B; k < (delNum_B + 4096); k++) {
					delete& PBN[k];
				}
			}
		}
	}
	cout << "�ش� ������ ����� �������ϴ�." << endl;
	cout << "����Ʈ ��" << _msize(PSN) << endl;
}
//��� ���� ������ ���
void Print_table_b() {
	cout << "��� ���� ���̺��� ����մϴ�." << endl;
	for (int i = 1; i < megabytes; i++) {
		if (PBN[i] < 0)
			cout << "/ ";
		else
			cout << PBN[i] << " ";
		if (i % 10 == 0)
			cout << endl;
	}
}