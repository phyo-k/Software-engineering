//����Ʈ����̵���������� ��ȿ��_201923220 1�� ������Ʈ: ��ȭ��ȣ�� �����  2020/09/26 ����
#include <iostream>
#include <string>

using namespace std;

void explainBook();//���α׷� ���� �� �ȳ���
void showMenu();//�޴�����
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

void phoneBook::printBook() //��µǴ� ��ȭ��ȣ ����
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
	cout << " �� ���α׷��� �����ϱ⿡ �ռ� ������ �ȳ��� �ϰڽ��ϴ�." << endl;
	cout << " �� ���α׷��� ������ �� ���� ���� ����ó�� �߰��ϼ���." << endl;
	cout << " �� ��ȭ��ȣ �Է½� ���ڿ� '-'�� �Է��ϼ���. ����� �� �ʿ� �����ϴ�." << endl;
	cout << " �� ����ó ������ 2�� �̻��� ����ó�� �־�� �մϴ�." << endl;
	cout << " �� ���� �Է� �� ������ ������ ���α׷� �۵��� ������ �߻��ϴ� '\'�� ���� ���� ���ڷ� �Է��ϼ���" << endl;
}

void showMenu() {
	cout << "==================================================================" << endl;
	cout << "[ ��ȭ��ȣ�� ]" << endl;
	cout << endl;
	cout << "1. ����ó �߰�" << endl;
	cout << "2. ����ó �˻�" << endl;
	cout << "3. ����ó ����" << endl;
	cout << "4. ����ó ���" << endl;
	cout << "5.����" << endl;
	cout << "���ڸ� �����ϼ���: ";
}

template<class T> void List<T>::AddbySorted(const T& el) {//����ó �߰�
	Node<T>* temp = new Node<T>;//�� ��� �����Ѵ�
	Node<T>* pt = head; //�߰��Ǿ�� �� �κ��� �˷��ִ� ��ġ
	temp->book = el;

	//1)��尡 ������� �� ��忡 ù ���� �߰�
	if (head == NULL) {
		head = temp;
		temp->prev = NULL;
		temp->next = NULL;
		cout << "����ó�� ����Ǿ����ϴ�." << endl;
	}
	//2)book�� ������ ����ִ� ����� ��
	else {
		while (el.m_name > pt->book.m_name) { //�̸� Ž��- �߰� �Ǵ� ��ġ�� ã���ִ� ����
			if (pt->next == NULL)//���������� ���� �����.
				break;
			pt = pt->next;// ���� ������ Ž���Ѵ�.
		}
		//_1. ó�� �κп� �߰� �ȴٸ�
		if (pt == head) {
			head = temp;
			pt->prev = temp;
			temp->prev = NULL; //ó���� �߰��Ǿ��� ������ �� �κ��� NULL
			temp->next = pt;
		}
		//_2. ������ �κп� �߰� �ȴٸ�
		else if (pt->next == NULL) {
			pt->next = temp;
			temp->prev = pt;
			temp->next = NULL;
		}
		//_3. �߰� �κп� �߰� �ȴٸ�
		else {
			pt->prev->next = temp; //temp ����� �ڸ� ����
			temp->prev = pt->prev; //temp�� �� ��带 pt�� �������� ����Ŵ
			temp->next = pt; //temp�� ������ pt����
			pt->prev = temp; //pt�� �� ��带 temp�� ����
		}
		cout << "����ó�� ����Ǿ����ϴ�." << endl;
	}
}

template<class T>void List<T>::SearchData(const string &name){//����ó �˻�
	Node<T>* point = head;
	
	if (point == NULL) //�����Ͱ� ������ ��ȯ�Ѵ�
		return;
	while (point != NULL) {// �ӽ� �������� �ּҰ��� NULL�� �� ������ �ݺ�
		if (point->book.m_name == name) {//�Է� ���� ������ ��µȴ�.
			cout << point->book.m_name << "�� ����ó �����Դϴ�." << endl;
			cout << "�̸�: " << point->book.m_name << endl;
			cout << "��ȭ��ȣ: " << point->book.m_num << endl;
			cout << "����: " << point->book.m_age << endl;
			cout << "�޸�: " << point->book.m_memo << endl;
		}
			point = point->next;
	}
}

template<class T>void List<T>::Delete(const string& name) {
	Node<T>* key = head;
	if (key == NULL) //�����Ͱ� ������ ��ȯ�Ѵ�
		return;
	while (key != NULL) {
		if (key->book.m_name == name) { //�̸� ã��
			if (key == head) { //�� �� ��带 ����� ���
				head = key->next;
				key->next->prev = NULL;
				delete key;
				break;
			}
			else if (key->next == NULL) { //������ ��带 ����� ���
				key->prev->next = NULL;
				delete key;
				break;
			}
			else {//�߰� ��带 �����ϴ� ���
				key->prev->next = key->next;
				key->next->prev = key->prev;
				delete key;
				break;
			}
		}
		key = key->next;
	}
}

template<class T> void List<T>::PrintList() {//����ó ���
	Node<T>* printPt = head;

	if (printPt == NULL)
		return;
	else { //�����Ͱ� �ϳ� �̻� ����ִٸ�
		while (printPt != NULL) {
			printPt->book.printBook(); //�����͸� ����ϸ�
			printPt = printPt->next; //���� �������� ���� �θ���
		}
	}
}

void main()
{
	List<phoneBook> Book;//��ȭ��ȣ�� ���Ḯ��Ʈ ����
	string addName;//�߰� ����ó �̸�
	string addNum;//�߰� ����ó ��ȭ��ȣ
	int addAge = 0;//�߰� ����ó ����
	string addMemo;//�߰� ����ó �޸�
	string searchName;//�˻��� ����ó �̸�
	string delName;//���� ����ó �̸�
	string answer;//���α׷� ���� �� ��/�ƴϿ�

	explainBook();
	cout << "[ ���� ]" << endl;
	Book.AddbySorted(phoneBook("ȫ�浿", "010-0000-0000", 21, "���÷� ����� ����ó�Դϴ�."));
	Book.PrintList();
	while (true) {
		showMenu();
		int num = 0;
		cin >> num;
		cout << endl;
		switch (num) {
		case 1:
			cout << "--------------------------------------------------------------" << endl;
			cout << "����ó�� �߰��մϴ�." << endl;
			cout << "�̸�: ";
			cin >> addName;
			cout << "��ȭ��ȣ: ";
			cin >> addNum;
			cout << "����: ";
			cin >> addAge;
			cout<<"�޸�: ";
			cin >> addMemo;
			Book.AddbySorted(phoneBook(addName, addNum, addAge, addMemo));
			break;
		case 2:
			cout << "--------------------------------------------------------------" << endl;
			cout << "�̸����� ����ó�� �˻��մϴ�. �̸��� �Է��ϼ���." << endl;
			cout << "���̸�: ";
			cin >> searchName;
			Book.SearchData(searchName);
			cout << "�˻��� ��Ĩ�ϴ�." << endl;
			break;
		case 3:
			cout << "--------------------------------------------------------------" << endl;
			cout << "������ ����ó�� �̸��� �Է��ϼ���: ";
			cin >> delName;
			Book.Delete(delName);
			cout << "����ó�� �����Ǿ����ϴ�." << endl;
			break;
		case 4:
			cout << "--------------------------------------------------------------" << endl;
			cout << "����� ��ȭ��ȣ���Դϴ�." << endl;
			cout << "  [ �̸� ]  [ ��ȭ��ȣ ]  [ ���� ]            [ �޸� ]" << endl;
			Book.PrintList();
			cout << endl;
			cout << "��ȭ��ȣ ����� �Ϸ�Ǿ����ϴ�." << endl;
			break;
		default:
			cout << "�߸� �Է��Ͽ����ϴ�." << endl;
			break;
		}
		if (num == 5) {
			cout << "-----------------------------------------------" << endl;
			cout << "���α׷��� �����Ͻðڽ��ϱ�?" << endl;
			cout << "(��/�ƴϿ�)�� �Է��ϼ���." << endl;
			cout << "�� ";
			cin >> answer;
			if (answer == "��") {
				cout << "��ȭ��ȣ�� ���α׷��� �����մϴ�." << endl;
				break;
			}
			else if (answer == "�ƴϿ�")
				continue;
			else
				cout << "�߸� �Է��Ͽ����ϴ�. ��/�ƴϿ��� �Է��ϼ���." << endl;
		}
	}
}