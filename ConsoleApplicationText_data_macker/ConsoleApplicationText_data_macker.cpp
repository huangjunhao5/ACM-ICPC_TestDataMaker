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



//ofstream out;
//
//
//string C_ptr = "D:/input/";
////int visit[mod];
//random_device rd;
//mt19937 mt(rd());
////char ts[1000];
////char lib[4] = "\\/";
//string File_name_maker(int name, string ptr,bool __IS_INPUT_FILE) {
//	char ts[1000];
//	int tf = name;
//	int len = 0;
//	memset(ts, 0, sizeof(ts));
//	while (tf) {
//		ts[++len] = tf % 10 + '0';
//		tf /= 10;
//	}
//	char s[1000];
//	memset(s, 0, sizeof(s));
//	for (int i = 1; i <= strlen(ts + 1); i++) {
//		s[len - i] = ts[i];
//	}
//	string fname = ".in";
//	if (!__IS_INPUT_FILE)fname = ".out";
//	fname = s + fname;
//	return ptr + fname;
//}
//
//
//
//const int MOD = 1e9 + 7;
//
//void __make_text(int __text_num) {
//	cerr << "Text" << __text_num << ":" << " :make begin" << endl;
//	string __INPUT_FILE__ = File_name_maker(__text_num, C_ptr, 1);
//	string __OUTPUT_FILE__ = File_name_maker(__text_num, C_ptr, 0);
//	cerr << __INPUT_FILE__ << " :make begin" << endl;
//	freopen(__INPUT_FILE__.c_str(), "w", stdout);
//	{
//		//在这里构造数据
//
//	}
//	fclose(stdout);
//	cerr << __INPUT_FILE__ << " :make done" << endl;
//	cerr << __OUTPUT_FILE__ << " :make begin" << endl;
//	//freopen(__OUTPUT_FILE__.c_str(), "w", stdout);
//	//std解法
//	string cmd = "D:\\11111\\repos\\ConsoleApplication3\\x64\\Debug\\ConsoleApplication3.exe";
//	//cmd字符串为std程序的全路径
//	cmd += " <" + __INPUT_FILE__;
//	cmd += " >" + __OUTPUT_FILE__;
//	system(cmd.c_str());
//	//使用std标程重定向到文件输出.out文件
//	//fclose(stdout);
//	cerr << __OUTPUT_FILE__ << " :make done" << endl;
//	cerr << "Text" << __text_num << " :make done!" << endl;
//	cerr << endl;
//}
//
//
//signed main() {
//	int __TEXT_NUM__;
//	cin >> __TEXT_NUM__;
//	for (int i = 1; i <= __TEXT_NUM__; i++) {
//		__make_text(i);
//	}
//	cerr << "All Text Make Successfully!" << endl;
//	exit(0);
//	return 0;
//}



