//소프트웨어미디어융합전공 김효정_201923220 1차 프로젝트: 전화번호부 만들기  2020/09/26 제출
#include <iostream>
#include <string>

using namespace std;

void explainBook();//프로그램 시작 전 안내말
void showMenu();//메뉴선택
class phoneBook {
public:
	phoneBook(string name = "empty", string num = "empty", int age = 0, string memo = "empty");
	void printBook();

	string m_name;
	string m_num;
	int m_age;
	string m_memo;
};

template<class T>
class Node {
public:
	Node()
	{
		next = prev = NULL;
	}
	Node(const T& el, Node* n = NULL, Node* p = NULL) {
		book = el;
		next = n;
		prev = p;
	}
	T book;
	Node* next, * prev;
};

template<class T>
class List {
public:
	List()
	{
		head = NULL;
	}
	~List()
	{
		for (Node<T>* p = NULL; p != NULL; )
		{
			p = head->next;
			delete head;
			head = p;
		}
	}
	void AddbySorted(const T& el);
	void SearchData(const string &name);
	void Delete(const string& name);
	void PrintList();

private:
	Node<T>* head;
};

phoneBook::phoneBook(string name, string num, int age, string memo)
{
	m_name = name;
	m_num = num;
	m_age = age;
	m_memo = memo;
}

void phoneBook::printBook() //출력되는 전화번호 정보
{
	cout.width(10);
	cout << m_name;
	cout.width(15);
	cout << m_num;
	cout.width(5);
	cout << m_age;
	cout.width(30);
	cout << m_memo << endl;
}

void explainBook() {
	cout << " ※ 프로그램을 시작하기에 앞서 간단한 안내를 하겠습니다." << endl;
	cout << " ※ 프로그램을 시작한 후 제일 먼저 연락처를 추가하세요." << endl;
	cout << " ※ 전화번호 입력시 숫자와 '-'를 입력하세요. 띄어쓰기는 할 필요 없습니다." << endl;
	cout << " ※ 연락처 삭제는 2개 이상의 연락처가 있어야 합니다." << endl;
	cout << " ※ 정보 입력 시 공백을 넣으면 프로그램 작동에 에러가 발생하니 '\'와 같이 구분 문자로 입력하세요" << endl;
}

void showMenu() {
	cout << "==================================================================" << endl;
	cout << "[ 전화번호부 ]" << endl;
	cout << endl;
	cout << "1. 연락처 추가" << endl;
	cout << "2. 연락처 검색" << endl;
	cout << "3. 연락처 삭제" << endl;
	cout << "4. 연락처 출력" << endl;
	cout << "5.종료" << endl;
	cout << "숫자를 선택하세요: ";
}

template<class T> void List<T>::AddbySorted(const T& el) {//연락처 추가
	Node<T>* temp = new Node<T>;//새 노드 생성한다
	Node<T>* pt = head; //추가되어야 할 부분을 알려주는 위치
	temp->book = el;

	//1)노드가 비어있을 때 노드에 첫 내용 추가
	if (head == NULL) {
		head = temp;
		temp->prev = NULL;
		temp->next = NULL;
		cout << "연락처가 저장되었습니다." << endl;
	}
	//2)book에 정보가 들어있는 노드일 때
	else {
		while (el.m_name > pt->book.m_name) { //이름 탐색- 추가 되는 위치를 찾아주는 역할
			if (pt->next == NULL)//마지막까지 가면 멈춘다.
				break;
			pt = pt->next;// 다음 정보로 탐색한다.
		}
		//_1. 처음 부분에 추가 된다면
		if (pt == head) {
			head = temp;
			pt->prev = temp;
			temp->prev = NULL; //처음에 추가되었기 때문에 앞 부분은 NULL
			temp->next = pt;
		}
		//_2. 마지막 부분에 추가 된다면
		else if (pt->next == NULL) {
			pt->next = temp;
			temp->prev = pt;
			temp->next = NULL;
		}
		//_3. 중간 부분에 추가 된다면
		else {
			pt->prev->next = temp; //temp 노드의 자리 지정
			temp->prev = pt->prev; //temp의 전 노드를 pt의 전전노드로 가리킴
			temp->next = pt; //temp의 다음은 pt노드로
			pt->prev = temp; //pt의 전 노드를 temp로 지정
		}
		cout << "연락처가 저장되었습니다." << endl;
	}
}

template<class T>void List<T>::SearchData(const string &name){//연락처 검색
	Node<T>* point = head;
	
	if (point == NULL) //데이터가 없으면 반환한다
		return;
	while (point != NULL) {// 임시 포인터의 주소값이 NULL이 될 때까지 반복
		if (point->book.m_name == name) {//입력 값이 같으면 출력된다.
			cout << point->book.m_name << "의 연락처 정보입니다." << endl;
			cout << "이름: " << point->book.m_name << endl;
			cout << "전화번호: " << point->book.m_num << endl;
			cout << "나이: " << point->book.m_age << endl;
			cout << "메모: " << point->book.m_memo << endl;
		}
			point = point->next;
	}
}

template<class T>void List<T>::Delete(const string& name) {
	Node<T>* key = head;
	if (key == NULL) //데이터가 없으면 반환한다
		return;
	while (key != NULL) {
		if (key->book.m_name == name) { //이름 찾기
			if (key == head) { //맨 앞 노드를 지우는 경우
				head = key->next;
				key->next->prev = NULL;
				delete key;
				break;
			}
			else if (key->next == NULL) { //마지막 노드를 지우는 경우
				key->prev->next = NULL;
				delete key;
				break;
			}
			else {//중간 노드를 삭제하는 경우
				key->prev->next = key->next;
				key->next->prev = key->prev;
				delete key;
				break;
			}
		}
		key = key->next;
	}
}

template<class T> void List<T>::PrintList() {//연락처 출력
	Node<T>* printPt = head;

	if (printPt == NULL)
		return;
	else { //데이터가 하나 이상 들어있다면
		while (printPt != NULL) {
			printPt->book.printBook(); //데이터를 출력하며
			printPt = printPt->next; //다음 포인터의 값을 부른다
		}
	}
}

void main()
{
	List<phoneBook> Book;//전화번호부 연결리스트 생성
	string addName;//추가 연락처 이름
	string addNum;//추가 연락처 전화번호
	int addAge = 0;//추가 연락처 나이
	string addMemo;//추가 연락처 메모
	string searchName;//검색할 연락처 이름
	string delName;//지울 연락처 이름
	string answer;//프로그램 종료 시 예/아니오

	explainBook();
	cout << "[ 예시 ]" << endl;
	Book.AddbySorted(phoneBook("홍길동", "010-0000-0000", 21, "예시로 저장된 연락처입니다."));
	Book.PrintList();
	while (true) {
		showMenu();
		int num = 0;
		cin >> num;
		cout << endl;
		switch (num) {
		case 1:
			cout << "--------------------------------------------------------------" << endl;
			cout << "연락처를 추가합니다." << endl;
			cout << "이름: ";
			cin >> addName;
			cout << "전화번호: ";
			cin >> addNum;
			cout << "나이: ";
			cin >> addAge;
			cout<<"메모: ";
			cin >> addMemo;
			Book.AddbySorted(phoneBook(addName, addNum, addAge, addMemo));
			break;
		case 2:
			cout << "--------------------------------------------------------------" << endl;
			cout << "이름으로 연락처를 검색합니다. 이름을 입력하세요." << endl;
			cout << "▶이름: ";
			cin >> searchName;
			Book.SearchData(searchName);
			cout << "검색을 마칩니다." << endl;
			break;
		case 3:
			cout << "--------------------------------------------------------------" << endl;
			cout << "삭제할 연락처의 이름을 입력하세요: ";
			cin >> delName;
			Book.Delete(delName);
			cout << "연락처가 삭제되었습니다." << endl;
			break;
		case 4:
			cout << "--------------------------------------------------------------" << endl;
			cout << "저장된 전화번호부입니다." << endl;
			cout << "  [ 이름 ]  [ 전화번호 ]  [ 나이 ]            [ 메모 ]" << endl;
			Book.PrintList();
			cout << endl;
			cout << "전화번호 출력이 완료되었습니다." << endl;
			break;
		default:
			cout << "잘못 입력하였습니다." << endl;
			break;
		}
		if (num == 5) {
			cout << "-----------------------------------------------" << endl;
			cout << "프로그램을 종료하시겠습니까?" << endl;
			cout << "(예/아니오)로 입력하세요." << endl;
			cout << "▶ ";
			cin >> answer;
			if (answer == "예") {
				cout << "전화번호부 프로그램을 종료합니다." << endl;
				break;
			}
			else if (answer == "아니오")
				continue;
			else
				cout << "잘못 입력하였습니다. 예/아니오로 입력하세요." << endl;
		}
	}
}