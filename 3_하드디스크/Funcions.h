#pragma once
#include<iostream>
#include<fstream>
#include <stdio.h>
#include <string.h>
using namespace std;

int megabytes;
int sector = megabytes / 512; //���� ����
int block = sector / 32; //��� ����
char* PSN, temp[1];
ifstream inFile("checking.txt");
ofstream outFile("checking.txt");

//�޸� ���� �Լ�
void Init() {
	cout << "�����Ϸ��� �޸� �뷮(MB)�� �Է��ϼ���>> ";
	cin >> megabytes;
	cout << megabytes << "MB �÷��� �޸𸮸� �����մϴ�." << endl;
	megabytes = 1024 * 1024 * megabytes;//MB = 1024*1024 (KB->MB)
}

void Menu() {
	cout << "===================================" << endl;
	cout << "1. ������ �б�" << endl;
	cout << "2. ������ ����" << endl;
	cout << "3. ������ �����" << endl;
	cout << "0. ����" << endl;
	cout << "===================================" << endl;
}

//������ �б�; ����=512B
void Read() {
	int rdNum;
	cout << "���� �������� ��ȣ�� �Է��ϼ���>> "; cin >> rdNum;
	for (int i = 0; i < sector; i+=512) {
		cout << "�����͸� �а� �ֽ��ϴ�." << endl;
		if (rdNum == 0)
			cout << "0��° �����ʹ� " << PSN[i] << "�Դϴ�." << endl;
		else {
			rdNum *= 512;
			if (rdNum == i) {
				cout << i << "��° �����ʹ� " << PSN[i] << "�Դϴ�." << endl;
			}
		}
	}
	cout << "����Ʈ ��" << _msize(PSN) << " " << "�迭 ����" << _msize(PSN)/sizeof(PSN) << endl;
	cout << endl;
	while (!inFile.eof()) {
		inFile.getline(PSN, _msize(PSN));
		cout << "������: " << PSN << "�� �о����ϴ�" << endl;
		break;
	}
	inFile.close();
}

//������ ����; ����=512B
void Write() {
	int wtNum = 0;
	cout << "������ �����͸� �Է��ϼ���." << endl;
	cout << "�� ��°>> ";  cin >> wtNum;
	cout << "�� ������>> "; cin >> PSN;
	for (int j = 0; j < sector; j+=512) {//�� ����
		if(wtNum==0)
			cout << "write(0, '" << PSN << "') �� ����Ǿ����ϴ�." << endl;
		else {
			wtNum *= 512;
			if (wtNum == j) {
				cout << "write(" << wtNum << ", '" << PSN << "') �� ����Ǿ����ϴ�." << endl;
				break;
			}
		}
	}
	cout << "�����Ͱ� �߰��Ǿ����ϴ�." << endl;
	for (int i = 0; i < _msize(PSN); i++) {
		outFile << PSN << endl;
	}
	outFile.close();
}

//������ �����; 1��� = 32���� = 16,384B
void Erase() {
	int delNum;
	cout << "������� �����͸� �Է��ϼ���." << endl;
	cout << "�� ��°>> "; cin >> delNum;
	cout << delNum << "��° �����͸� ����ϴ�." << endl;
	for (int i = 0; i < block; i+=16384) {
		if (delNum == 0) {
			for (int j = 0; j < 16384; j++) {
				delete& PSN[i];
			}
			cout << "�ش� ������ ����� �������ϴ�." << endl;
		}
		else {
			delNum *= 16384;
			if (delNum == i) {
				for (int k = delNum; k < (delNum *= 16384); k++) {
					delete& PSN[k];
					cout << "�ش� ������ ����� �������ϴ�." << endl;
				}
			}
		}
	}
	cout << "����Ʈ ��" << _msize(PSN) << endl;
}