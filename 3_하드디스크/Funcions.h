#pragma once
#include<iostream>
#include<fstream>
#include <stdio.h>
#include <string.h>
using namespace std;

int megabytes;
int sector = megabytes / 512; //섹터 개수
int block = sector / 32; //블록 개수
char* PSN, temp[1];
ifstream inFile("checking.txt");
ofstream outFile("checking.txt");

//메모리 설정 함수
void Init() {
	cout << "설정하려는 메모리 용량(MB)을 입력하세요>> ";
	cin >> megabytes;
	cout << megabytes << "MB 플래시 메모리를 생성합니다." << endl;
	megabytes = 1024 * 1024 * megabytes;//MB = 1024*1024 (KB->MB)
}

void Menu() {
	cout << "===================================" << endl;
	cout << "1. 데이터 읽기" << endl;
	cout << "2. 데이터 쓰기" << endl;
	cout << "3. 데이터 지우기" << endl;
	cout << "0. 종료" << endl;
	cout << "===================================" << endl;
}

//데이터 읽기; 섹터=512B
void Read() {
	int rdNum;
	cout << "읽을 데이터의 번호를 입력하세요>> "; cin >> rdNum;
	for (int i = 0; i < sector; i+=512) {
		cout << "데이터를 읽고 있습니다." << endl;
		if (rdNum == 0)
			cout << "0번째 데이터는 " << PSN[i] << "입니다." << endl;
		else {
			rdNum *= 512;
			if (rdNum == i) {
				cout << i << "번째 데이터는 " << PSN[i] << "입니다." << endl;
			}
		}
	}
	cout << "바이트 수" << _msize(PSN) << " " << "배열 개수" << _msize(PSN)/sizeof(PSN) << endl;
	cout << endl;
	while (!inFile.eof()) {
		inFile.getline(PSN, _msize(PSN));
		cout << "데이터: " << PSN << "를 읽었습니다" << endl;
		break;
	}
	inFile.close();
}

//데이터 쓰기; 섹터=512B
void Write() {
	int wtNum = 0;
	cout << "쓰려는 데이터를 입력하세요." << endl;
	cout << "몇 번째>> ";  cin >> wtNum;
	cout << "쓸 데이터>> "; cin >> PSN;
	for (int j = 0; j < sector; j+=512) {//한 섹터
		if(wtNum==0)
			cout << "write(0, '" << PSN << "') 가 저장되었습니다." << endl;
		else {
			wtNum *= 512;
			if (wtNum == j) {
				cout << "write(" << wtNum << ", '" << PSN << "') 가 저장되었습니다." << endl;
				break;
			}
		}
	}
	cout << "데이터가 추가되었습니다." << endl;
	for (int i = 0; i < _msize(PSN); i++) {
		outFile << PSN << endl;
	}
	outFile.close();
}

//데이터 지우기; 1블록 = 32섹터 = 16,384B
void Erase() {
	int delNum;
	cout << "지우려는 데이터를 입력하세요." << endl;
	cout << "몇 번째>> "; cin >> delNum;
	cout << delNum << "번째 데이터를 지웁니다." << endl;
	for (int i = 0; i < block; i+=16384) {
		if (delNum == 0) {
			for (int j = 0; j < 16384; j++) {
				delete& PSN[i];
			}
			cout << "해당 데이터 블록을 지웠습니다." << endl;
		}
		else {
			delNum *= 16384;
			if (delNum == i) {
				for (int k = delNum; k < (delNum *= 16384); k++) {
					delete& PSN[k];
					cout << "해당 데이터 블록을 지웠습니다." << endl;
				}
			}
		}
	}
	cout << "바이트 수" << _msize(PSN) << endl;
}