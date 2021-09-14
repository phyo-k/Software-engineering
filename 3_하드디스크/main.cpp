#include <fstream>
#include <iostream>
#include <malloc.h>
#include "Funcions.h"

using namespace std;

void Init(); //MB 메모리 생성 함수
void Menu();//메뉴함수
void Read();//데이터 읽기
void Write();//데이터 쓰기
void Erase();//데이터 지우기

int  main() {
	int num;//메뉴 고르기
	int rdNum;//읽기 번호
	int wtNum;//쓰기 번호
	char wt;//쓸 데이터
	int delNum;//지울 번호
	string answer;//종료여부

	Init();
	PSN = (char*)malloc(sizeof(char) * megabytes);
	cout << "-------------- 메모리 작동 --------------" << endl;
	while (true) {
		Menu();
		cout << "메뉴 입력>> "; cin >> num;
		if (num > 3) {
			cout << "잘못 입력했습니다. 0~3을 입력하세요." << endl;
			continue;
		}
		switch (num) {
		case 1:
			Read(); //섹터 단위로 데이터 읽기
			break;
		case 2:
			Write(); //섹터 단위로 데이터 쓰기
			break;
		case 3:
			Erase();//블록 단위로 데이터 지우기
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
	free(PSN);
	return 0;
}
