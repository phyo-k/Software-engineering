//소프트웨어미디어융합전공 김효정_201923220 2차 프로젝트: 비디오 대여 프로그램  2020/11/01 제출
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Person {// 고객 클래스
public:
	friend ostream& operator<<(ostream& os, Person& ps) {// 고객 정보 출력
		os << ps.name << "\t" << ps.phone << "\t" << ps.address << "\t";
		return os;
	}
	friend class Run;
private:
	string name;      // 이름
	string phone;     // 전화번호
	string address;   // 주소
};
class Video { // 비디오 클래스
public:
	friend class Run;
	Video() {
		count = 0;
	}
	bool Rent(Person* ps) { //대여 - 참, 거짓 반환 bool 사용
		if (person.size() < count) {
			person.push_back(ps);
			return true; // 대여
		}
		return false; // 대여x
	}
	bool Return(Person* ps) {//반납
		vector<Person*>::iterator it;
		for (it = person.begin(); it != person.end(); it++) {
			if (*it == ps) {
				person.erase(it);
				return true; //반납
			}
		}
		return false; // 반납x
	}
	friend ostream& operator<<(ostream& os, Video& vd) { // 비디오 정보 출력
		os << vd.title << "\t" << vd.director << "\t" << vd.production << "\t" << vd.genre << "\t";
		os << vd.count - vd.person.size() << "/" << vd.count << "\t";
		return os;
	}
private:
	string title;        // 비디오 제목
	string director;     // 감독
	string production;    // 제작사
	string genre;        //장르
	size_t count;        // 전체 수량  size_t: 가장 큰 사이즈를 담을 수 있는 unsigned 데이터 타입
	vector<Person*> person; // 대여 고객 목록
};

class Run {// 관리 클래스
public:
	Run() {// 파일 읽기
		int cnt;
		char str[100];
		// 고객 정보 읽기
		ifstream personFile("PersonList.txt");
		if (!personFile.fail()) {
			personFile.getline(str, 100);
			cnt = atoi(str); //고객 더미 하나를 cnt로 변환
			for (int i = 0; i < cnt; i++) {
				Person ps;
				personFile.getline(str, 100); ps.name = str;
				personFile.getline(str, 100); ps.address = str;
				personFile.getline(str, 100); ps.phone = str;
				m_person.push_back(ps);//하나의 고객 더미 날림
			}
			personFile.close();
		}
		// 비디오 정보 읽기
		ifstream videoFile("VideoList.txt");
		if (!videoFile.fail()) {
			videoFile.getline(str, 100);
			cnt = atoi(str);
			for (int i = 0; i < cnt; i++) {
				Video vd;
				videoFile.getline(str, 100); vd.title = str;
				videoFile.getline(str, 100); vd.director = str;
				videoFile.getline(str, 100); vd.production = str;
				videoFile.getline(str, 100); vd.genre = str;
				videoFile.getline(str, 100); vd.count = atoi(str);
				m_dvd.push_back(vd);
			}
			videoFile.close();
		}
		// 대여 정보 읽기
		ifstream rentFile("RentalList.txt");
		if (!rentFile.fail()) {
			char title[100], name[100];
			rentFile.getline(str, 100);
			cnt = atoi(str);
			for (int i = 0; i < cnt; i++) {
				rentFile.getline(name, 100);
				rentFile.getline(title, 100);
				Person* ps = findPerson(name);
				Video* vd = findVideo(title);
				if (ps && vd)
					vd->Rent(ps);
			}
			rentFile.close();
		}
	}
	~Run() { // 소멸자 - 파일 저장
		// 고객 정보 저장
		ofstream personFile("PersonList.txt");
		if (!personFile.fail()) {
			personFile << m_person.size() << endl;
			for (size_t i = 0; i < m_person.size(); i++) {
				personFile << m_person[i].name << endl;
				personFile << m_person[i].address << endl;
				personFile << m_person[i].phone << endl;
			}
			personFile.close();
		}
		// 비디오 데이터 저장
		ofstream videoFile("VideoList.txt");
		if (!videoFile.fail()) {
			videoFile << m_dvd.size() << endl;
			for (size_t i = 0; i < m_dvd.size(); i++) {
				videoFile << m_dvd[i].title << endl;
				videoFile << m_dvd[i].director << endl;
				videoFile << m_dvd[i].production << endl;
				videoFile << m_dvd[i].genre << endl;
				videoFile << m_dvd[i].count << endl;
			}
			videoFile.close();
		}
		// 대여 정보 저장
		ofstream rentFile("RentalList.txt");
		if (!rentFile.fail()) {
			int cnT = 0;
			for (size_t i = 0; i < m_dvd.size(); i++) {
				cnT += m_dvd[i].person.size();
			}
			rentFile << cnT << endl;
			for (size_t i = 0; i < m_dvd.size(); i++) {
				for (size_t j = 0; j < m_dvd[i].person.size(); j++) {
					rentFile << m_dvd[i].title << endl;
					rentFile << m_dvd[i].person[j]->name << endl;
				}
			}
			rentFile.close();
		}
	}
	void AddPerson() { // 고객 추가
		Person ps;
		char str[100];
		cin.sync();
		cout << "등록하려는 고객의 정보를 입력하세요" << endl;
		cout << " "; cin.getline(str, 100);
		cout << "이름: "; cin.getline(str, 100); ps.name = str; //cin의 멤버함수이며 띄어쓰기까지 포함하여 문자열로 저장할 수 있음
		cout << "전화번호: "; cin.getline(str, 100); ps.phone = str;
		cout << "주소: "; cin.getline(str, 100); ps.address = str;
		m_person.push_back(ps);
		cout << "고객이 추가되었습니다." << endl;
		system("pause");
	}
	void AddVideo() { // 비디오 추가
		char str[100];
		Video vd;
		cin.sync();
		cout << "추가하려는 비디오의 정보를 입력하세요" << endl;
		cout << " "; cin.getline(str, 100);
		cout << "제목: "; cin.getline(str, 100); vd.title = str;
		cout << "감독: "; cin.getline(str, 100); vd.director = str;
		cout << "제작사: "; cin.getline(str, 100); vd.production = str;
		cout << "장르: "; cin.getline(str, 100); vd.genre = str;
		cout << "수량: "; cin >> vd.count;
		m_dvd.push_back(vd);
		cout << "비디오가 추가되었습니다." << endl;
		system("pause");
	}
	void FindPerson() { // 고객 검색
		char name[100];
		cin.sync();
		cout << "검색하려는 고객 이름을 입력하세요" << endl;
		cout << " "; cin.getline(name, 100);
		cout << "이름 : "; cin.getline(name, 100);
		Person* ps = findPerson(name);
		if (ps) {
			cout << name << " 고객이 존재합니다." << endl;
			cout << "----------------------------------------------------------" << endl;
			cout << "이름: " << ps->name << endl;
			cout << "전화번호: " << ps->phone << endl;
			cout << "주소: " << ps->address << endl;
		}
		else
			cout << "존재하는" << name << " 고객이 없습니다." << endl;
		system("pause");
	}
	void FindVideo() { // 비디오 검색
		char title[100];
		cin.sync();
		cout << "검색하려는 비디오 제목을 입력하세요." << endl;
		cout << " "; cin.getline(title, 100);
		cout << "비디오 제목 : "; cin.getline(title, 100);
		Video* vd = findVideo(title);
		if (vd) {
			cout << title << " 비디오가 존재합니다." << endl;
			cout << "-----------------------------------------------------------" << endl;
			cout << "제목: " << vd->title << endl;
			cout << "감독: " << vd->director << endl;
			cout << "제작사: " << vd->production << endl;
			cout << "장르: " << vd->genre << endl;
			cout << "수량: " << vd->count << endl;
		}
		else
			cout << "존재하는" << title << " 바다오가 없습니다." << endl;
		system("pause");
	}
	void Rental() { // 대여 확인
		char name[100];
		char title[100];
		char str[5];
		cin.sync();
		cout << "대여를 시작합니다." << endl;
		cout << " "; cin.getline(str, 5);
		cout << "고객 이름 : "; cin.getline(name, 100);
		Person* ps = findPerson(name);
		if (ps) {
			cout << "비디오 제목 : "; cin.getline(title, 100);
			Video* vd = findVideo(title);
			if (vd) {
				if (vd->Rent(ps))
					cout << "대여되었습니다." << endl;
				else
					cout << "입력한 비디오의 재고가 없습니다." << endl;
			}
			else cout << "존재하지 않는 비디오입니다." << endl;
		}
		else
			cout << "존재하지 않는 고객입니다." << endl;
		system("pause");
	}
	void Return() {// 반납
		char name[100];
		char title[100];
		char str[5];
		cin.sync();
		cout << "반납을 진행합니다." << endl;
		cout << " "; cin.getline(str, 100);
		cout << "고객 이름 : ";
		cin.getline(name, 100);
		Person* ps = findPerson(name);
		if (ps) {
			cout << "비디오 제목 : "; cin.getline(title, 100);
			Video* vd = findVideo(title);
			if (vd) {
				if (vd->Return(ps))
					cout << "반납되었습니다." << endl;
				else
					cout << "입력한 비디오의 재고가 없습니다." << endl;
			}
			else
				cout << "존재하지 않는 비디오입니다." << endl;
		}
		else
			cout << "존재하지 않는 고객입니다." << endl;
		system("pause");
	}
	void PersonList() {// 고객 목록 출력
		cout << "=============================================================" << endl;
		cout << "이 름\t전  화  번  호\t주  소" << endl;
		cout << "-------------------------------------------------------------" << endl;
		if (m_person.size() == 0)
			cout << "등록된 고객이 없습니다." << endl;
		for (size_t i = 0; i < m_person.size(); i++)
			cout << m_person[i] << endl;
		cout << "=============================================================" << endl;
		system("pause");
	}
	void VideoList() {// 비디오 목록 출력
		cout << "=============================================================" << endl;
		cout << "제  목 \t감   독\t 제작사 \t장르\t재고/전체수량" << endl;
		cout << "-------------------------------------------------------------" << endl;
		if (m_dvd.size() == 0)
			cout << "등록된 비디오가 없습니다." << endl;
		for (size_t i = 0; i < m_dvd.size(); i++)
			cout << m_dvd[i] << endl;
		cout << "=============================================================" << endl;
		system("pause");
	}
	void RentList() {// 대여 목록 출력
		cout << "=============================================================" << endl;
		cout << "비디오 제목\t대여자\t전화번호" << endl;
		cout << "-------------------------------------------------------------" << endl;
		for (size_t i = 0; i < m_dvd.size(); i++) {
			for (size_t k = 0; k < m_dvd[i].person.size(); k++) {
				cout << m_dvd[i].title << "\t";
				cout << m_dvd[i].person[k]->name << "\t";
				cout << m_dvd[i].person[k]->phone << endl;
			}
		}
		cout << "=============================================================" << endl;
		system("pause");
	}
private:
	vector<Person> m_person;      // 고객 목록
	vector<Video> m_dvd;      // 비디오 목록

	Person* findPerson(string name) { // 고객 찾기(내부)
		for (size_t i = 0; i < m_person.size(); i++) {
			if (m_person[i].name == name)
				return &m_person[i];
		}
		return NULL;
	}
	Video* findVideo(string title) {// 비디오 찾기(내부)
		for (size_t i = 0; i < m_dvd.size(); i++) {
			if (m_dvd[i].title == title)
				return &m_dvd[i];
		}
		return NULL;
	}
};

void MenuTitle(const char* c) {
	system("cls");
	cout << "[비 디 오 대 여 프 로 그 램 입 니 다.]" << endl;
	cout << c << endl;
}
int InputMenu(int x) {
	int num;
	while (true) {
		cin >> num;
		if (0 >= num && num <= x)
			break;
		else {
			cout << "잘못 입력하였습니다. 0~5까지 숫자를 입력하세요." << endl;
			break;
		}
	}
	return num;
}

int main() {
	int num;
	Run run;

	while (true) {
		MenuTitle("시작>>");
		cout << "1. 고객   관리" << endl;
		cout << "2. 비디오 관리" << endl;
		cout << "3. 비디오 대여" << endl;
		cout << "4. 비디오 반납" << endl;
		cout << "5. 대여   현황" << endl;
		cout << "0. 종료" << endl;
		cout << "> ";
		num = InputMenu(5);

		switch (num) {
		case 1:
			MenuTitle("시작>> 고객관리>");
			cout << "1. 가입" << endl;
			cout << "2. 고객검색" << endl;
			cout << "3. 고객목록" << endl;
			cout << "0. 시작으로.." << endl;
			cout << "> ";
			num = InputMenu(3);
			switch (num) {
			case 1:
				MenuTitle("시작>> 고객관리>> 가입>");
				run.AddPerson();
				break;
			case 2:
				MenuTitle("시작>> 고객관리>> 고객검색>");
				run.FindPerson();
				break;
			case 3:
				MenuTitle("시작>> 고객관리>> 고객목록>");
				run.PersonList();
				break;
			case 0:
				break;
			}
			break;
		case 2:
			MenuTitle("시작>> 비디오관리> ");
			cout << "1. 비디오등록" << endl;
			cout << "2. 비디오검색" << endl;
			cout << "3. 비디오목록" << endl;
			cout << "0. 시작으로.." << endl;
			cout << "> ";
			num = InputMenu(3);
			switch (num) {
			case 1:
				MenuTitle("시작>> 비디오관리>> 비디오등록>");
				run.AddVideo();
				break;
			case 2:
				MenuTitle("시작>> 비디오관리>> 비디오검색>");
				run.FindVideo();
				break;
			case 3:
				MenuTitle("시작>> 비디오관리>> 비디오목록>");
				run.VideoList();
				break;
			case 0:
				break;
			}
			break;
		case 3:
			MenuTitle("시작>> 비디오대여>");
			run.Rental();
			break;
		case 4:
			MenuTitle("시작>> 비디오반납>");
			run.Return();
			break;
		case 5:
			MenuTitle("시작>> 대여현황>");
			run.RentList();
			break;
		case 0:
			return 0;
		}
	}
	return 0;
}