﻿// ConsoleApplicationText_data_macker.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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

//用于生成数据的函数：必须为void型，并且要接受一个参数，该参数表示当前生成的数据编号
void make(__int32 num) {
	int n = 3e5;
	cout << n << endl;
	//可以通过传入的数据编号确定生成什么数据：是否随机生成数据、或者生成确定的什么数据
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
	//stdEXEPath是标程在电脑上的全路径
	string testPath = "D:/input/";
	//testPath是生成数据的全路径
	__int32 textnum;
	cin >> textnum;
	DataMaker* maker = new DataMakerFromEXE(stdEXEPath ,testPath, make, textnum);
	maker->run();
	delete maker;
	return 0;
}







