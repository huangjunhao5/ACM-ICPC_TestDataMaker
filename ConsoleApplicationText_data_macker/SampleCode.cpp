// SampleCode.cpp : 此文件为DataMaker使用的示例代码
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
//可以通过传入的参数得知该组数据是否随机生成，或者生成特定的什么数据
void make(__int32 num) {
	int n = 50000;
	cout << n << endl;
	if (num == 1) {//第一组数据生成方法
		while(n -- )cout << 0 << ' ' << 0 << endl;
	}
	else if (num == 2) {//第二组数据生成方法
		while(n -- )cout << (int)1e4 << ' ' << (int)1e4 << endl;
	}
	else if (num == 3) {
		while (n--)cout << (int)-1e4 << ' ' << (int)-1e4 << endl;
	}
	else if(num == 4) {
		while (n--)cout << (int)1e4 << ' ' << (int)-1e4 << endl;
	}
	else if (num == 5) {
		int i = 0, j = 0;
		int len = 1;
		for (; len < n;i++) {
			for (j = 0; len <= n && j < 1e4; len++, j++) {
				cout << i << ' ' << j << endl;
			}
		}
	}
	else {
		int u, v;
		const int maxn = 1e4 + 1;
		for (int i = 1; i <= n; i++) {
			u = mt() % maxn;
			v = mt() % maxn;
			if (mt() & 1) {
				u *= -1;
			}
			if (mt() & 1) {
				v *= -1;
			}
			cout << u << ' ' << v << endl;
		}
	}
}

signed main() {
	string stdEXEPath = "D:\\11111\\repos\\ConsoleApplication3\\x64\\Debug\\ConsoleApplication3.exe";
	//stdEXEPath是标程在电脑上的全路径
	string testPath = "D:/input/";
	//testPath是生成数据的全路径
	__int32 testnum;
	cin >> testnum;
	DataMaker* maker = new DataMakerFromEXE(stdEXEPath ,testPath, make, testnum);
	maker->run();
	delete maker;
	return 0;
}







