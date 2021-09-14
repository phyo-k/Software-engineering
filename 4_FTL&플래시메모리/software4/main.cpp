#include <fstream>
#include <iostream>
#include <malloc.h>
#include "functions.h"

using namespace std;

void Init(); //섹터매핑 MB 메모리 생성 함수
void Select();//매핑 방법 선택 함수
void Menu();//메뉴함수
void Flash_read();//섹터 매핑 데이터 읽기
void Flash_write();//섹터 매핑 데이터 쓰기
void Flash_erase();//섹터 매핑 데이터 지우기
void Print_table_s();//섹터 매핑테이블 출력
void FTL_read();//블록 매핑 데이터 읽기
void FTL_write();//블록 매핑 데이터 쓰기
void FTL_erase();//블록 매핑 데이터 지우기
void Print_table_b();//블록 매핑 테이블 출력

int  main() {
	int num1, num2;//메뉴 고르기
	string answer;//종료여부

	cout << "-------------- 메모리 작동 --------------" << endl;

	while (true) {
		Select();
		cout << "매핑방법 선택>> "; cin >> num1;
		if (num1 > 2) {
			cout << "잘못 입력했습니다. 0~2를 입력하세요." << endl;
			continue;
		}
		switch (num1) {
		case 1:
			Init();
			PSN = (int*)malloc(sizeof(int) * megabytes);
			while(true) {
				Menu();
				cout << "기능 선택>> "; cin >> num2;
				if (num2 > 4) {
					cout << "잘못 입력했습니다. 0~4를 입력하세요." << endl;
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
					cout << "실행을 종료하시겠습니까?(예/아니오)>> "; cin >> answer;
					if (answer == "예")
						exit(1);
					else if (answer == "아니오")
						continue;
					else {
						cout << "예 / 아니오로 입력하세요." << endl;
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
				cout << "기능 선택>> "; cin >> num2;
				if (num2 > 4) {
					cout << "잘못 입력했습니다. 0~3을 입력하세요." << endl;
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
					cout << "실행을 종료하시겠습니까?(예/아니오)>> "; cin >> answer;
					if (answer == "예")
						exit(1);
					else if (answer == "아니오")
						continue;
					else {
						cout << "예 / 아니오로 입력하세요." << endl;
						continue;
					}
					cout << endl;
				}
			}
			break;
		case 0:
			cout << "실행을 종료하시겠습니까?(예/아니오)>> "; cin >> answer;
			if (answer == "예")
				exit(1);
			else if (answer == "아니오")
				continue;
			else {
				cout << "예 / 아니오로 입력하세요." << endl;
				continue;
			}
			cout << endl;
		}
	}
	for (int x = 0; x < megabytes; x++)
		delete &PSN[x];//메모리 해제

	for (int x = 0; x < megabytes; x++)
		delete& PBN[x];//메모리 해제

	return 0;
}