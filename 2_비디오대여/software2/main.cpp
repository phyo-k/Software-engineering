//����Ʈ����̵���������� ��ȿ��_201923220 2�� ������Ʈ: ���� �뿩 ���α׷�  2020/11/01 ����
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Person {// �� Ŭ����
public:
	friend ostream& operator<<(ostream& os, Person& ps) {// �� ���� ���
		os << ps.name << "\t" << ps.phone << "\t" << ps.address << "\t";
		return os;
	}
	friend class Run;
private:
	string name;      // �̸�
	string phone;     // ��ȭ��ȣ
	string address;   // �ּ�
};
class Video { // ���� Ŭ����
public:
	friend class Run;
	Video() {
		count = 0;
	}
	bool Rent(Person* ps) { //�뿩 - ��, ���� ��ȯ bool ���
		if (person.size() < count) {
			person.push_back(ps);
			return true; // �뿩
		}
		return false; // �뿩x
	}
	bool Return(Person* ps) {//�ݳ�
		vector<Person*>::iterator it;
		for (it = person.begin(); it != person.end(); it++) {
			if (*it == ps) {
				person.erase(it);
				return true; //�ݳ�
			}
		}
		return false; // �ݳ�x
	}
	friend ostream& operator<<(ostream& os, Video& vd) { // ���� ���� ���
		os << vd.title << "\t" << vd.director << "\t" << vd.production << "\t" << vd.genre << "\t";
		os << vd.count - vd.person.size() << "/" << vd.count << "\t";
		return os;
	}
private:
	string title;        // ���� ����
	string director;     // ����
	string production;    // ���ۻ�
	string genre;        //�帣
	size_t count;        // ��ü ����  size_t: ���� ū ����� ���� �� �ִ� unsigned ������ Ÿ��
	vector<Person*> person; // �뿩 �� ���
};

class Run {// ���� Ŭ����
public:
	Run() {// ���� �б�
		int cnt;
		char str[100];
		// �� ���� �б�
		ifstream personFile("PersonList.txt");
		if (!personFile.fail()) {
			personFile.getline(str, 100);
			cnt = atoi(str); //�� ���� �ϳ��� cnt�� ��ȯ
			for (int i = 0; i < cnt; i++) {
				Person ps;
				personFile.getline(str, 100); ps.name = str;
				personFile.getline(str, 100); ps.address = str;
				personFile.getline(str, 100); ps.phone = str;
				m_person.push_back(ps);//�ϳ��� �� ���� ����
			}
			personFile.close();
		}
		// ���� ���� �б�
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
		// �뿩 ���� �б�
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
	~Run() { // �Ҹ��� - ���� ����
		// �� ���� ����
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
		// ���� ������ ����
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
		// �뿩 ���� ����
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
	void AddPerson() { // �� �߰�
		Person ps;
		char str[100];
		cin.sync();
		cout << "����Ϸ��� ���� ������ �Է��ϼ���" << endl;
		cout << " "; cin.getline(str, 100);
		cout << "�̸�: "; cin.getline(str, 100); ps.name = str; //cin�� ����Լ��̸� ������� �����Ͽ� ���ڿ��� ������ �� ����
		cout << "��ȭ��ȣ: "; cin.getline(str, 100); ps.phone = str;
		cout << "�ּ�: "; cin.getline(str, 100); ps.address = str;
		m_person.push_back(ps);
		cout << "���� �߰��Ǿ����ϴ�." << endl;
		system("pause");
	}
	void AddVideo() { // ���� �߰�
		char str[100];
		Video vd;
		cin.sync();
		cout << "�߰��Ϸ��� ������ ������ �Է��ϼ���" << endl;
		cout << " "; cin.getline(str, 100);
		cout << "����: "; cin.getline(str, 100); vd.title = str;
		cout << "����: "; cin.getline(str, 100); vd.director = str;
		cout << "���ۻ�: "; cin.getline(str, 100); vd.production = str;
		cout << "�帣: "; cin.getline(str, 100); vd.genre = str;
		cout << "����: "; cin >> vd.count;
		m_dvd.push_back(vd);
		cout << "������ �߰��Ǿ����ϴ�." << endl;
		system("pause");
	}
	void FindPerson() { // �� �˻�
		char name[100];
		cin.sync();
		cout << "�˻��Ϸ��� �� �̸��� �Է��ϼ���" << endl;
		cout << " "; cin.getline(name, 100);
		cout << "�̸� : "; cin.getline(name, 100);
		Person* ps = findPerson(name);
		if (ps) {
			cout << name << " ���� �����մϴ�." << endl;
			cout << "----------------------------------------------------------" << endl;
			cout << "�̸�: " << ps->name << endl;
			cout << "��ȭ��ȣ: " << ps->phone << endl;
			cout << "�ּ�: " << ps->address << endl;
		}
		else
			cout << "�����ϴ�" << name << " ���� �����ϴ�." << endl;
		system("pause");
	}
	void FindVideo() { // ���� �˻�
		char title[100];
		cin.sync();
		cout << "�˻��Ϸ��� ���� ������ �Է��ϼ���." << endl;
		cout << " "; cin.getline(title, 100);
		cout << "���� ���� : "; cin.getline(title, 100);
		Video* vd = findVideo(title);
		if (vd) {
			cout << title << " ������ �����մϴ�." << endl;
			cout << "-----------------------------------------------------------" << endl;
			cout << "����: " << vd->title << endl;
			cout << "����: " << vd->director << endl;
			cout << "���ۻ�: " << vd->production << endl;
			cout << "�帣: " << vd->genre << endl;
			cout << "����: " << vd->count << endl;
		}
		else
			cout << "�����ϴ�" << title << " �ٴٿ��� �����ϴ�." << endl;
		system("pause");
	}
	void Rental() { // �뿩 Ȯ��
		char name[100];
		char title[100];
		char str[5];
		cin.sync();
		cout << "�뿩�� �����մϴ�." << endl;
		cout << " "; cin.getline(str, 5);
		cout << "�� �̸� : "; cin.getline(name, 100);
		Person* ps = findPerson(name);
		if (ps) {
			cout << "���� ���� : "; cin.getline(title, 100);
			Video* vd = findVideo(title);
			if (vd) {
				if (vd->Rent(ps))
					cout << "�뿩�Ǿ����ϴ�." << endl;
				else
					cout << "�Է��� ������ ��� �����ϴ�." << endl;
			}
			else cout << "�������� �ʴ� �����Դϴ�." << endl;
		}
		else
			cout << "�������� �ʴ� ���Դϴ�." << endl;
		system("pause");
	}
	void Return() {// �ݳ�
		char name[100];
		char title[100];
		char str[5];
		cin.sync();
		cout << "�ݳ��� �����մϴ�." << endl;
		cout << " "; cin.getline(str, 100);
		cout << "�� �̸� : ";
		cin.getline(name, 100);
		Person* ps = findPerson(name);
		if (ps) {
			cout << "���� ���� : "; cin.getline(title, 100);
			Video* vd = findVideo(title);
			if (vd) {
				if (vd->Return(ps))
					cout << "�ݳ��Ǿ����ϴ�." << endl;
				else
					cout << "�Է��� ������ ��� �����ϴ�." << endl;
			}
			else
				cout << "�������� �ʴ� �����Դϴ�." << endl;
		}
		else
			cout << "�������� �ʴ� ���Դϴ�." << endl;
		system("pause");
	}
	void PersonList() {// �� ��� ���
		cout << "=============================================================" << endl;
		cout << "�� ��\t��  ȭ  ��  ȣ\t��  ��" << endl;
		cout << "-------------------------------------------------------------" << endl;
		if (m_person.size() == 0)
			cout << "��ϵ� ���� �����ϴ�." << endl;
		for (size_t i = 0; i < m_person.size(); i++)
			cout << m_person[i] << endl;
		cout << "=============================================================" << endl;
		system("pause");
	}
	void VideoList() {// ���� ��� ���
		cout << "=============================================================" << endl;
		cout << "��  �� \t��   ��\t ���ۻ� \t�帣\t���/��ü����" << endl;
		cout << "-------------------------------------------------------------" << endl;
		if (m_dvd.size() == 0)
			cout << "��ϵ� ������ �����ϴ�." << endl;
		for (size_t i = 0; i < m_dvd.size(); i++)
			cout << m_dvd[i] << endl;
		cout << "=============================================================" << endl;
		system("pause");
	}
	void RentList() {// �뿩 ��� ���
		cout << "=============================================================" << endl;
		cout << "���� ����\t�뿩��\t��ȭ��ȣ" << endl;
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
	vector<Person> m_person;      // �� ���
	vector<Video> m_dvd;      // ���� ���

	Person* findPerson(string name) { // �� ã��(����)
		for (size_t i = 0; i < m_person.size(); i++) {
			if (m_person[i].name == name)
				return &m_person[i];
		}
		return NULL;
	}
	Video* findVideo(string title) {// ���� ã��(����)
		for (size_t i = 0; i < m_dvd.size(); i++) {
			if (m_dvd[i].title == title)
				return &m_dvd[i];
		}
		return NULL;
	}
};

void MenuTitle(const char* c) {
	system("cls");
	cout << "[�� �� �� �� �� �� �� �� �� �� �� ��.]" << endl;
	cout << c << endl;
}
int InputMenu(int x) {
	int num;
	while (true) {
		cin >> num;
		if (0 >= num && num <= x)
			break;
		else {
			cout << "�߸� �Է��Ͽ����ϴ�. 0~5���� ���ڸ� �Է��ϼ���." << endl;
			break;
		}
	}
	return num;
}

int main() {
	int num;
	Run run;

	while (true) {
		MenuTitle("����>>");
		cout << "1. ��   ����" << endl;
		cout << "2. ���� ����" << endl;
		cout << "3. ���� �뿩" << endl;
		cout << "4. ���� �ݳ�" << endl;
		cout << "5. �뿩   ��Ȳ" << endl;
		cout << "0. ����" << endl;
		cout << "> ";
		num = InputMenu(5);

		switch (num) {
		case 1:
			MenuTitle("����>> ������>");
			cout << "1. ����" << endl;
			cout << "2. ���˻�" << endl;
			cout << "3. �����" << endl;
			cout << "0. ��������.." << endl;
			cout << "> ";
			num = InputMenu(3);
			switch (num) {
			case 1:
				MenuTitle("����>> ������>> ����>");
				run.AddPerson();
				break;
			case 2:
				MenuTitle("����>> ������>> ���˻�>");
				run.FindPerson();
				break;
			case 3:
				MenuTitle("����>> ������>> �����>");
				run.PersonList();
				break;
			case 0:
				break;
			}
			break;
		case 2:
			MenuTitle("����>> ��������> ");
			cout << "1. �������" << endl;
			cout << "2. �����˻�" << endl;
			cout << "3. �������" << endl;
			cout << "0. ��������.." << endl;
			cout << "> ";
			num = InputMenu(3);
			switch (num) {
			case 1:
				MenuTitle("����>> ��������>> �������>");
				run.AddVideo();
				break;
			case 2:
				MenuTitle("����>> ��������>> �����˻�>");
				run.FindVideo();
				break;
			case 3:
				MenuTitle("����>> ��������>> �������>");
				run.VideoList();
				break;
			case 0:
				break;
			}
			break;
		case 3:
			MenuTitle("����>> �����뿩>");
			run.Rental();
			break;
		case 4:
			MenuTitle("����>> �����ݳ�>");
			run.Return();
			break;
		case 5:
			MenuTitle("����>> �뿩��Ȳ>");
			run.RentList();
			break;
		case 0:
			return 0;
		}
	}
	return 0;
}