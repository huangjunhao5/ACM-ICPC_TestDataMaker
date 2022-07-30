// ConsoleApplicationText_data_macker.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<bits/stdc++.h>
#include<random>
#include"DataMaker.h"
#define ll long long
#define int long long
//#define cout out
const int mod = 1e5;
int Mod = 1e5;

using namespace std;

random_device rd;
mt19937 mt(rd());


void make(__int32 num) {
	int n = 3e5;
	cout << n << endl;
	if (num == 1) {
		for (int i = 1; i <= n; i++) {
			cout << i << ' ';
		}cout << endl;
		for (int i = 1; i <= n; i++) {
			cout << i << ' ';
		}cout << endl;
	}
	else if (num == 2) {
		for (int i = 1; i <= n; i++) {
			cout << i << ' ';
		}cout << endl;
		for (int i = 1; i <= n; i++) {
			cout << n - i + 1 << ' ';
		}cout << endl;
	}
	else if (num == 3) {
		for (int i = 1; i <= n; i++) {
			cout << i << ' ';
		}cout << endl;
		for (int i = 1; i <= n; i++) {
			cout << i / 2 + 1 << ' ';
		}cout << endl;
	}
	else if (num == 4) {		
		for (int i = 1; i <= n; i++) {
			cout << i / 2 + 1 << ' ';
		}cout << endl;
		for (int i = 1; i <= n; i++) {
			cout << i << ' ';
		}cout << endl;
	}
	else {
		for (int i = 1; i <= n; i++) {
			cout << mt() % n + 1 << ' ';
		}cout << endl;
		for (int i = 1; i <= n; i++) {
			cout << mt() % n + 1 << ' ';
		}cout << endl;
	}
}

signed main() {
	string stdEXEPath = "D:\\11111\\repos\\ConsoleApplication3\\x64\\Debug\\ConsoleApplication3.exe";
	string textPath = "D:/input/";
	__int32 textnum;
	cin >> textnum;
	DataMaker* maker = new DataMakerFromEXE(stdEXEPath ,textPath, make, textnum);
	maker->run();
	delete maker;
	return 0;
}







