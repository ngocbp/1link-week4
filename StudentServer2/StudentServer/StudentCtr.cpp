#include "StudentCtr.h"
#include"DAO.h"
#include"View.h"
#include<list>
#include"rapidjson\stringbuffer.h"
using namespace std;

bool StudentCtr::checkID(int id)
{
	DAO dao;
	list<Student> list2 = dao.readList("output.txt");
	list<Student>::iterator it;
	for (it = list2.begin(); it != list2.end(); it++) {
		if ((*it).getID() == id) {
			return true;
		}
	}
	return false;
}

bool StudentCtr::add(Student st)
{
	DAO dao;
	if (checkID(st.getID())) {
		cout << "student is esixt hihi" << endl;
	}
	else {
		if (dao.writeFile(st, "output.txt")) {
			return true;
		}
		return false;
	}
}

string StudentCtr::showAll()
{
	DAO dao;
	//cout << dao.readFile("output.txt");
	string result = dao.readFile("output.txt");
	return result;
}

StudentCtr::StudentCtr()
{
}

struct CompareBy
{//tham khao cua hoang
	const string SORT_FIELD;
	CompareBy(const string& sort_field = "name") :SORT_FIELD(sort_field)
	{
		/* validate sort_field */
	}

	bool operator()(Student& st1, Student& st2)
	{
		if (SORT_FIELD == "name")
			return st1.getName() < st2.getName();
		else if (SORT_FIELD == "sum")
			return st1.getMath() + st1.getPhys() + st1.getChem() < st2.getMath() + st2.getPhys() + st2.getChem();
		else if (SORT_FIELD == "id")
			return st1.getID() < st2.getID();
	}
};

void StudentCtr::sort(list<Student> list1)
{
	View v;
	switch (v.showSortMenu())
	{
	case 1: {//sort by id
		list1.sort(CompareBy("id"));
		v.showList(list1);
		break;
	}
	case 2: {//sort by name
		list1.sort(CompareBy("name"));
		v.showList(list1);
		break;
	}
	case 3: {//sort by sum
		list1.sort(CompareBy("sum"));
		v.showList(list1);
		break;
	}
	default:
		break;
	}
}

Student StudentCtr::searchID( int id)
{
	list<Student> list2;
	list<Student>::iterator it;
	Student st;
	DAO dao;
	list2 = dao.readList("output.txt");
	system("cls");
	if (list2.empty()) cout << "empty" << endl;
	else {
		int k = 0;
		for (it = list2.begin(); it != list2.end(); it++) {
			if ((*it).getID() == id) {
				k = 1;
				st.setID((*it).getID());
				st.setName((*it).getName());
				st.setAddress((*it).getAddress());
				st.setSex((*it).getSex());
				st.setMath((*it).getMath());
				st.setPhys((*it).getPhys());
				st.setChem((*it).getChem());
			}
		}
		if (k == 0) cout << "not found" << endl;
		
		return st;
	}
}

void StudentCtr::searchName()
{
	list<Student> list2, result_search;
	list<Student>::iterator it;
	Student st = Student();
	DAO dao;
	list2 = dao.readList("output.txt");
	system("cls");
	if (list2.empty()) cout << "empty" << endl;
	else {
		string name;
		cout << "enter Name: ";
		cin.ignore();
		getline(cin, name);
		int k = 0;
		for (it = list2.begin(); it != list2.end(); it++) {
			if ((*it).getName() == name) {
				k = 1;
				st.setID((*it).getID());
				st.setName((*it).getName());
				st.setAddress((*it).getAddress());
				st.setSex((*it).getSex());
				st.setMath((*it).getMath());
				st.setPhys((*it).getPhys());
				st.setChem((*it).getChem());
				Student st = Student((*it).getID(), (*it).getName(), (*it).getAddress(), (*it).getSex(), (*it).getMath(), (*it).getPhys(), (*it).getChem());
				result_search.push_back(st);
			}
		}
		if (k == 0) cout << "not found" << endl;
		else
			sort(result_search);
	}
}

void StudentCtr::searchSum()
{
	list<Student> list2, result;
	list<Student>::iterator it;
	Student st;
	DAO dao;
	list2 = dao.readList("output.txt");
	system("cls");
	if (list2.empty()) cout << "empty" << endl;
	else {
		int sum;
		cout << "enter Sum: ";
		cin >> sum;
		int k = 0;
		for (it = list2.begin(); it != list2.end(); it++) {
			float Sum = (*it).getMath() + (*it).getPhys() + (*it).getChem();
			if (Sum == sum) {
				k = 1;
				st.setID((*it).getID());
				st.setName((*it).getName());
				st.setAddress((*it).getAddress());
				st.setSex((*it).getSex());
				st.setMath((*it).getMath());
				st.setPhys((*it).getPhys());
				st.setChem((*it).getChem());
				result.push_back(st);
			}
		}
		if (k == 0) cout << "not found" << endl;
		else
			sort(result);
	}
}

void StudentCtr::searchMath()
{
	list<Student> list2, result;
	list<Student>::iterator it;
	Student st;
	DAO dao;
	list2 = dao.readList("output.txt");
	system("cls");
	if (list2.empty()) cout << "empty" << endl;
	else {
		int m;
		cout << "enter Math: ";
		cin >> m;
		int k = 0;
		for (it = list2.begin(); it != list2.end(); it++) {
			if ((*it).getMath() == m) {
				k = 1;
				st.setID((*it).getID());
				st.setName((*it).getName());
				st.setAddress((*it).getAddress());
				st.setSex((*it).getSex());
				st.setMath((*it).getMath());
				st.setPhys((*it).getPhys());
				st.setChem((*it).getChem());
				result.push_back(st);
			}
		}
		if (k == 0) cout << "not found" << endl;
		else
			sort(result);
	}
}

void StudentCtr::searchPhys()
{
	list<Student> list2, result;
	list<Student>::iterator it;
	Student st;
	DAO dao;
	list2 = dao.readList("output.txt");
	system("cls");
	if (list2.empty()) cout << "empty" << endl;
	else {
		float p;
		cout << "enter Phys: ";
		cin >> p;
		int k = 0;
		for (it = list2.begin(); it != list2.end(); it++) {
			if ((*it).getPhys() == p) {
				k = 1;
				st.setID((*it).getID());
				st.setName((*it).getName());
				st.setAddress((*it).getAddress());
				st.setSex((*it).getSex());
				st.setMath((*it).getMath());
				st.setPhys((*it).getPhys());
				st.setChem((*it).getChem());
				result.push_back(st);
			}
		}
		if (k == 0) cout << "not found" << endl;
		else
			sort(result);
	}
}

void StudentCtr::searchChem()
{
	list<Student> list2, result;
	list<Student>::iterator it;
	Student st;
	DAO dao;
	list2 = dao.readList("output.txt");
	system("cls");
	if (list2.empty()) cout << "empty" << endl;
	else {
		cout << "enter Chem: ";
		float c;
		cin >> c;
		int k = 0;
		for (it = list2.begin(); it != list2.end(); it++) {
			if ((*it).getChem() == c) {
				k = 1;
				st.setID((*it).getID());
				st.setName((*it).getName());
				st.setAddress((*it).getAddress());
				st.setSex((*it).getSex());
				st.setMath((*it).getMath());
				st.setPhys((*it).getPhys());
				st.setChem((*it).getChem());
				result.push_back(st);
			}
		}
		if (k == 0) cout << "not found" << endl;
		else
			sort(result);
	}
}



bool StudentCtr::edit(int id, Student st)
{
	DAO dao;
	View v;
	list<Student> list2;
	list<Student>::iterator it;
	cout << "EDIT" << endl;
	//int id = v.showSearchFrm();
	list2 = dao.readList("output.txt");
	for (it = list2.begin(); it != list2.end(); it++) {
		if ((*it).getID() == id) {
			(*it).setID(st.getID());
			(*it).setName(st.getName());
			(*it).setAddress(st.getSex());
			(*it).setSex(st.getSex());
			(*it).setMath(st.getMath());
			(*it).setPhys(st.getPhys());
			(*it).setChem(st.getChem());
		}
	}
	remove("output.txt");
	for (it = list2.begin(); it != list2.end(); it++) {
		Student st1;
		st1.setID((*it).getID());
		st1.setName((*it).getName());
		st1.setAddress((*it).getAddress());
		st1.setSex((*it).getSex());
		st1.setMath((*it).getMath());
		st1.setPhys((*it).getPhys());
		st1.setChem((*it).getChem());
		dao.writeFile(st1, "output.txt");
	}
	return true;
}

bool StudentCtr::del(int id)
{
	View v;
	DAO dao;
	cout << "DELETE" << endl;
	list<Student> list2, result;
	list<Student>::iterator it;
	list2 = dao.readList("output.txt");
	for (it = list2.begin(); it != list2.end(); it++) {
		if ((*it).getID() == id) {
			Student st;
			st.setID((*it).getID());
			st.setName((*it).getName());
			st.setAddress((*it).getAddress());
			st.setSex((*it).getSex());
			st.setMath((*it).getMath());
			st.setPhys((*it).getPhys());
			st.setChem((*it).getChem());
				it = list2.erase(it);
			if (it == list2.end()) break;
		}
		else cout << "not found" << endl;
	}
	remove("output.txt");
	for (it = list2.begin(); it != list2.end(); it++) {
		Student st1;
		st1.setID((*it).getID());
		st1.setName((*it).getName());
		st1.setAddress((*it).getAddress());
		st1.setSex((*it).getSex());
		st1.setMath((*it).getMath());
		st1.setPhys((*it).getPhys());
		st1.setChem((*it).getChem());
		dao.writeFile(st1, "output.txt");
	}
	return true;
}

void StudentCtr::thongke()
{
	int n = 0, a = 0, b = 0, c = 0, d = 0;
	View v;
	DAO dao;
	list<Student> list2;
	list<Student>::iterator it;
	list2 = dao.readList("output.txt");
	for (it = list2.begin(); it != list2.end(); it++) {
		n++;
		float s = (*it).getMath() + (*it).getPhys() + (*it).getChem();
		if (s < 15) { a++; }
		if (s >= 15 && s < 20) { b++; }
		if (s >= 20 && s < 25) { c++; }
		if (s >= 25) { d++; }
	}
	v.statistical(n, a, b, c, d);
}

void StudentCtr::swap(Student st1, Student st2)
{
	Student tem;
	memcpy(&tem, &st1, sizeof(Student));
	memcpy(&st1, &st2, sizeof(Student));
	memcpy(&st2, &tem, sizeof(Student));
}

StudentCtr::~StudentCtr()
{
}