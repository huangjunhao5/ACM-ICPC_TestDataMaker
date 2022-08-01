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
void make(__int32 num) {
	int n = 10, m = 100;
	cout << n << '\n' << m << endl;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			int temp = (mt() % 3);
			cout << temp - 1 << ' ';
		}cout << endl;
	}
}

signed main() {
	string stdEXEPath = "D:\\11111\\repos\\ConsoleApplication4\\x64\\Debug\\ConsoleApplication4.exe";
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







