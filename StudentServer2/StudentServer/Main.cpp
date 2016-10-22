#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Student.h"
#include "View.h"
#include "StudentCtr.h"
#include "DAO.h"
#include <list>
#include<iostream>
#include<winsock.h>
#include"rapidjson\stringbuffer.h"
#include"rapidjson\document.h"
#include"rapidjson\stringbuffer.h"
#include"rapidjson\prettywriter.h"
using namespace std;
#include <sstream>

std::string Convert(float number) {
	std::ostringstream buff;
	buff << number;
	return buff.str();
}
std::string Convert1(int number) {
	std::ostringstream buff;
	buff << number;
	return buff.str();
}

int main() {
	StudentCtr sc;
	char success[20] = "Add success!";
	char fail[10] = "Failed!";

	//winsock startup
	WSADATA wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) {
		MessageBoxA(NULL, "winshock startup is fail", "ERROR", MB_OK | MB_ICONERROR);
		exit(1);
	}
	SOCKADDR_IN addr;
	int addrLen = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(12345);
	addr.sin_family = AF_INET;

	//listen
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);
	cout << "wating for connect" << endl;
	//creat connect
	SOCKET newConn;
	newConn = accept(sListen, (SOCKADDR*)&addr, &addrLen);

	

	if (newConn == 0) {
		cout << "fail to accept" << endl;
	}
	else {
		cout << "connected" << endl;
	}

	char mesSend[100];
	char mesRecv[100];
	char welcome[170] = "==== Welcome To Student Manager ====\n1.show all student\n2.add 1 student\n3.edit 1 student\n4.delete 1 student\n5.search \n6.statistical\nYour choice is ....";
	send(newConn, welcome, sizeof(welcome), NULL);
	while (true)
	{
		//send(newConn, welcome, sizeof(welcome), NULL);
		recv(newConn, mesRecv, sizeof(mesRecv), NULL);
		string x = (string)mesRecv;
		cout << "Receviced: " << x << endl;
		if (x == "1") {
			string x = sc.showAll();
			const char* y = x.c_str();
			send(newConn, y, sizeof(welcome), NULL);
			cout << "send: " << x << endl;
		}
		if (x == "2") {
			char id[100], name[100], sex[100], addr[100], math[100], phys[100], chem[100];
			char a[100] = "ADD a Student.\nEnter Student Infor.\nID: ";
			char b[100] = "Name: ";
			char c[100] = "Addr: ";
			char d[100] = "Sex: ";
			char e[100] = "Math: ";
			char f[100] = "Phys: ";
			char g[100] = "Chem: ";
			
			send(newConn, a, sizeof(welcome), NULL);
			recv(newConn, id, sizeof(mesRecv), NULL);

			send(newConn, b, sizeof(welcome), NULL);
			recv(newConn, name, sizeof(mesRecv), NULL);

			send(newConn, c, sizeof(welcome), NULL);
			recv(newConn, addr, sizeof(mesRecv), NULL);

			send(newConn, d, sizeof(welcome), NULL);
			recv(newConn, sex, sizeof(mesRecv), NULL);

			send(newConn, e, sizeof(welcome), NULL);
			recv(newConn, math, sizeof(mesRecv), NULL);

			send(newConn, f, sizeof(welcome), NULL);
			recv(newConn, phys, sizeof(mesRecv), NULL);

			send(newConn, g, sizeof(welcome), NULL);
			recv(newConn, chem, sizeof(mesRecv), NULL);
			string name1(name);
			string addr1(addr);
			string sex1(sex);
			int id1 = stoi(id);
			float math1 = stof(math);
			float phys1 = stof(phys);
			float chem1 = stof(chem);
			Student st = Student(id1, name1, addr1, sex1, math1, phys1, chem1);
			
			if (sc.add(st)) {
				send(newConn, success, sizeof(success), NULL);
				cout << success;
			}
			else {
				send(newConn, welcome, sizeof(fail), NULL);
			}
		  }
		if (x == "3") {//edit
			char id[1000], name[1000], sex[1000], addr[1000], math[1000], phys[1000], chem[1000];
			char a1[1000] = "EDIT a Student.\nEnter ID: ";
			char a[1000] = "EDIT a Student.\nEnter new Student Infor.\nID: ";
			char b[1000] = "Name: ";
			char c[1000] = "Addr: ";
			char d[1000] = "Gender: ";
			char e[1000] = "Math: ";
			char f[1000] = "Phys: ";
			char g[1000] = "Chem: ";

			send(newConn, a1, sizeof(welcome), NULL);
			recv(newConn, id, sizeof(mesRecv), NULL);

			int id1 = stoi(id);
			Student st = sc.searchID(id1);
			string send1 = "ID: "+ Convert1(st.getID()) + "\nName:" + st.getName() + "\nAddress:" + st.getAddress() + "\nSex:" + st.getSex() + "\nMath:"+ Convert(st.getMath()) + "\nPhysic:" + Convert(st.getPhys()) + "\nChem:" + Convert(st.getChem())+ "\nDo you want to edit? (y/n)\n";
			cout << send;
			char x[100];
			const char* send2 = send1.c_str();
			send(newConn, send2, sizeof(mesSend), NULL);
			recv(newConn, x, sizeof(mesRecv), NULL);
			string x1(x);
			if (x1 == "y" || x == "Y")
			{

				send(newConn, b, sizeof(welcome), NULL);
				recv(newConn, name, sizeof(mesRecv), NULL);

				send(newConn, c, sizeof(welcome), NULL);
				recv(newConn, addr, sizeof(mesRecv), NULL);

				send(newConn, d, sizeof(welcome), NULL);
				recv(newConn, sex, sizeof(mesRecv), NULL);

				send(newConn, e, sizeof(welcome), NULL);
				recv(newConn, math, sizeof(mesRecv), NULL);

				send(newConn, f, sizeof(welcome), NULL);
				recv(newConn, phys, sizeof(mesRecv), NULL);

				send(newConn, g, sizeof(welcome), NULL);
				recv(newConn, chem, sizeof(mesRecv), NULL);
				string name2(name);
				string addr2(addr);
				string sex2(sex);
				float math2 = stof(math);
				float phys2 = stof(phys);
				float chem2 = stof(chem);
				
				Student st = Student(id1, name2, addr2, sex2, math2, phys2, chem2);
				if (sc.edit(id1,st) == true) {
					send(newConn, welcome, sizeof(success), NULL);
				}
				else {
					send(newConn, welcome, sizeof(fail), NULL);
				}
				
			}
			
		}
		if (x == "4")
		{
			char id[100];
			char delete1[100] = "DELETE a Student.\nEnter id:  ";
			send(newConn, delete1, sizeof(welcome), NULL);
			recv(newConn, id, sizeof(mesRecv), NULL);
			int id1 = stoi(id);
			Student st = sc.searchID(id1);
			string del = "ID: " + Convert1(st.getID()) + "\nName:" + st.getName() + "\nAddress:" + st.getAddress() + "\nSex:" + st.getSex() + "\nMath:" + Convert(st.getMath()) + "\nPhysic:" + Convert(st.getPhys()) + "\nChem:" + Convert(st.getChem()) + "\nDo you want to DELETE? (y/n)\n";
			cout << send;
			char x[100];
			const char* del2 = del.c_str();
			send(newConn, del2, sizeof(mesSend), NULL);
			recv(newConn, x, sizeof(mesRecv), NULL);
			string m(x);
			if (m == "y" || m == "Y")
			{
				if (sc.del(id1) == true) {
					send(newConn, welcome, sizeof(success), NULL);
				}
				else {
					send(newConn, welcome, sizeof(fail), NULL);
				}
			}
		}
	}
	//system("pause");
	return 0;
}