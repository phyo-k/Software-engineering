#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h> //malloc, free 함수 선언
#include <string.h>
using namespace std;

int megabytes;
int sector = megabytes / 512; //섹터 개수
int block = sector / 32; //블록 개수
int* PSN = NULL;
int* PBN = NULL;
//int count;//섹터매핑 읽기 횟수
//ifstream inFile("checking.txt");
//ofstream outFile("checking.txt");

void Init() {
	cout << "설정하려는 메모리 용량(MB)을 입력하세요>> ";
	cin >> megabytes;
	cout << "int형으로 정수만 입력 가능합니다. 양의 자연수로 입력하세요." << endl;
	cout << 4*megabytes << "MB 플래시 메모리를 생성합니다." << endl;
	megabytes = 1048576 * megabytes;//MB = 1024*1024 (KB->MB) && int는 4b
	if (megabytes == 0) {
		cout << "빈 메모리를 설정하여 프로그램이 작동하지 않습니다. 1이상의 숫자를 입력하세요." << endl;
		exit(0);
	}
}
void Select() {
	cout << "=========================================" << endl;
	cout << "1. 섹터매핑" << endl;
	cout << "2. 블록매핑" << endl;
	cout << "0. 종료" << endl;
	cout << "=========================================" << endl;
}
void Menu() {
	cout << "=========================================" << endl;
	cout << "1. 데이터 읽기" << endl;
	cout << "2. 데이터 쓰기" << endl;
	cout << "3. 데이터 지우기" << endl;
	cout << "4. 매핑 테이블 출력" << endl;
	cout << "0. 종료" << endl;
	cout << "=========================================" << endl;
}

//섹터매핑 데이터 읽기; 섹터=512B->int형 4바이트의 한 섹터는 128바이트
void Flash_read() {
	int rdNum_S;
	cout << "읽을 데이터의 번호를 입력하세요>> "; cin >> rdNum_S;
	
	if (rdNum_S == 0) {
		if (PSN[0]<0)
			cout << "데이터가 존재하지 않습니다." << endl;
		else {
			cout << "0번째 데이터는 " << PSN[0] << "입니다." << endl;
			cout << "바이트 수: " << _msize(PSN) << " " << "바이트,  배열 개수: " << _msize(PSN) / sizeof(PSN) << "개" << endl;
		}
	}
	else {
		rdNum_S *= 128;
		for (int j = rdNum_S; j < megabytes; j++) {
			if (rdNum_S == j) {
				cout << j << "번째 데이터는 " << PSN[j] << "입니다." << endl;
				cout << "바이트 수" << _msize(PSN) << " " << "배열 개수" << _msize(PSN) / sizeof(PSN) << endl;
				break;
			}
		}
	}
	cout << endl;
}

//섹터매핑 데이터 쓰기; 섹터=512B->int는 128B
void Flash_write() {
	int i = 0;  int wtNum_S = 0; int wt_S;
	cout << "쓰려는 데이터를 입력하세요." << endl;
	cout << "몇 번째>> ";  cin >> wtNum_S;
	cout << "쓸 데이터>> "; cin >> wt_S;
		if (wtNum_S == 0) {
			for (int l = 0; l < 128; l++)
				PSN[l] = wt_S;
			cout << "write(" << wtNum_S << ", '" << wt_S << "') 가 저장되었습니다." << endl;
		}
		else {
			wtNum_S *= 128;
			for (i = 128; i < megabytes; i++) {//한 섹터
				if (wtNum_S == i) {
					for (i = wtNum_S; i < (wtNum_S + 128); i++)
						PSN[i] = wt_S;
					break;
				}
			}
			cout << "write(" << wtNum_S << ", '" << wt_S << "') 가 저장되었습니다." << endl;
		}
}

//섹터매핑 데이터 지우기; 1블록 = 32섹터 = 16,384B ->1MB기준 64개 블록
void Flash_erase() {
	int k = 0; int delNum_S;
	cout << "지우려는 데이터를 입력하세요." << endl;
	cout << "몇 번째>> "; cin >> delNum_S;
	cout << delNum_S << "번째 데이터를 지웁니다." << endl;
	if (delNum_S == 0) {
		for (int l = 0; l < 4096; l++)
			delete &PSN[k];
	}
	else {
		delNum_S *= 4096;
		for (k = 4096; k < megabytes; k++) {//4096바이트*4(데이터타입)=한 블록(16384)
			if (delNum_S == k) {
				for (k = delNum_S; k < (delNum_S +4096); k++) {
					delete &PSN[k];
				}
			}
		}
	}
	cout << "해당 데이터 블록을 지웠습니다." << endl;
	cout << "바이트 수" << _msize(PSN) << endl;
}
//섹터매핑 테이블 출력
void Print_table_s() {
	cout << "섹터 매핑 테이블을 출력합니다." << endl;
	for (int i = 1; i < megabytes; i++) {
		if (PSN[i] < 0)
			cout << "/ ";
		else 
			cout << PSN[i] << " ";
		if (i % 10 == 0)
			cout << endl;
	}
}
//블록매핑 데이터 읽기
void FTL_read() {
	int rdNum_B;
	cout << "읽을 데이터의 번호를 입력하세요>> "; cin >> rdNum_B;

	if (rdNum_B == 0) {
		if (PBN[0] < 0)
			cout << "데이터가 존재하지 않습니다." << endl;
		else {
			cout << "0번째 데이터는 " << PBN[0] << "입니다." << endl;
			cout << "바이트 수: " << _msize(PBN) << " " << "바이트,  배열 개수: " << _msize(PBN) / sizeof(PBN) << "개" << endl;
		}
	}
	else {
		rdNum_B *= 4096;
		for (int j = rdNum_B; j < megabytes; j++) {
			if (rdNum_B == j) {
				cout << j << "번째 데이터는 " << PBN[j] << "입니다." << endl;
				cout << "바이트 수" << _msize(PBN) << " " << "배열 개수" << _msize(PBN) / sizeof(PBN) << endl;
				break;
			}
		}
	}
	cout << endl;
}
//블록매핑 데이터 쓰기 -> megabytes/512/32 = sector/32 = 총 블록 개수 //1MB기준으로 64블록 한 섹터=한 블록
void FTL_write() {
	int i = 0;  int wtNum_B; int wt_B;
	int wtNum_LBN; int wt_PBN;
	cout << "쓰려는 데이터를 입력하세요." << endl;
	cout << "몇 번째>> ";  cin >> wtNum_B;
	cout << "쓸 데이터>> "; cin >> wt_B;
	wtNum_LBN = wtNum_B / block;
	wt_PBN = wtNum_B % block;
	int l = 0;
	if (wtNum_LBN == 0) {//0번 블록
		for (l = 0; l < 4096; l++)//한 블록은 32섹터, 한 섹터는 512바이트(int는 4바이트므로 128로 계산)
			if (wt_PBN == l) {
				for(l=wt_PBN; l<l+128;l++)
					PBN[l] = wt_PBN;
			}
		cout << "write(" << wtNum_LBN << ", '" << wt_PBN << "') 가 저장되었습니다." << endl;
	}
	else {
		wtNum_B *= 4096;
		for (i = 4096; i < megabytes; i++) {//한 섹터
			if (wtNum_LBN == i) {
				for (i = wt_PBN; i < i+128; i++)
					PBN[i] = wt_PBN;
				break;
			}
		}
		cout << "write(" << wtNum_B << ", '" << wt_B << "') 가 저장되었습니다." << endl;
	}
}
//블록매핑 데이터 지우기
void FTL_erase() {
	int k = 0; int delNum_B;
	cout << "지우려는 데이터를 입력하세요." << endl;
	cout << "몇 번째>> "; cin >> delNum_B;
	cout << delNum_B << "번째 데이터를 지웁니다." << endl;
	if (delNum_B == 0) {
		for (int l = 0; l < 4096; l++)
			delete& PBN[k];
	}
	else {
		delNum_B *= 4096;
		for (k = 4096; k < megabytes; k++) {//4096바이트*4(데이터타입)=한 블록(16384)
			if (delNum_B == k) {
				for (k = delNum_B; k < (delNum_B + 4096); k++) {
					delete& PBN[k];
				}
			}
		}
	}
	cout << "해당 데이터 블록을 지웠습니다." << endl;
	cout << "바이트 수" << _msize(PSN) << endl;
}
//블록 매핑 데이터 출력
void Print_table_b() {
	cout << "블록 매핑 테이블을 출력합니다." << endl;
	for (int i = 1; i < megabytes; i++) {
		if (PBN[i] < 0)
			cout << "/ ";
		else
			cout << PBN[i] << " ";
		if (i % 10 == 0)
			cout << endl;
	}
}