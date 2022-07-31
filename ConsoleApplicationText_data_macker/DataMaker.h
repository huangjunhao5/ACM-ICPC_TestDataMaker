#pragma once
#include <string>
#include <iostream>
#include <cstdlib>



// 抽象类DataMaker：未实现make函数和run函数，需要重写make函数和run函数
// make函数编写说明：传入一个参数，为当前制造的数据编号（第几组数据）
// 调用数据路径生成函数生成测试数据的全路径（包括.in文件和.out文件，1为in，0为out）
// 然后使用freopen打开测试数据文件
// 再调用传入的fun函数生成数据
// fun函数可以使用cout构造数据
// run函数需要进行基本的运行判断，判断生成数据的必要参数是否具备
// 否则抛出异常
// 如果使用无参构造函数，将使用默认的生成参数设置
// 数据生成的路径：D:/input/
// 数据的组数：12
// 默认的数据生成函数不提供，如果没有传入数据生成函数，将抛出异常
class DataMaker
{
protected:
	typedef void (*MakeTestFun)(int testcase);
	std::string testcasePath = "";	
	MakeTestFun testMakeFunction = nullptr;
	int testNum = 12;
	
	bool ignoreMakeInputDataError = 0;

	bool ignoreMakeOutputDataError = 0;

	// 构造所需文件的全路径，如果未指定路径，抛出异常
	std::string fileNameMaker(int name, std::string testPath, bool __IS_INPUT_FILE) {
		if (testPath == "")throw std::runtime_error("NoFilePathError:You are not set file path!");
		char ts[1000];
		int tf = name;
		int len = 0;
		memset(ts, 0, sizeof(ts));
		while (tf) {
			ts[++len] = tf % 10 + '0';
			tf /= 10;
		}
		char s[1000];
		memset(s, 0, sizeof(s));
		for (int i = 1; i <= strlen(ts + 1); i++) {
			s[len - i] = ts[i];
		}
		std::string fname = ".in";
		if (!__IS_INPUT_FILE)fname = ".out";
		fname = s + fname + '\0';
		return testPath + fname;
	}

	//使用fun函数构造数据
	void makeInFile(std::string __INPUT_FILE__ ,int __test_num) {
		std::cerr << __INPUT_FILE__ << " :make begin" << std::endl;
		auto it = freopen(__INPUT_FILE__.c_str(), "w", stdout);
		if (it == nullptr) {
			//输入文件打开失败，抛出异常
			std::cerr << __INPUT_FILE__ << " make error : can't open file path" << __INPUT_FILE__ << std::endl;
			if(!ignoreMakeInputDataError){
				throw std::runtime_error("InputFileMakeError:make input file error!");
			}
			return;
		}
		{
			//在这里构造数据
			testMakeFunction(__test_num);
		}
		fclose(stdout);
		std::cerr << __INPUT_FILE__ << " :make done" << std::endl;
	}

	virtual void make(int __test_num) = 0;
public:
	virtual void run() = 0;
	virtual void defaultPathSet() {
		testcasePath = "D:/input/";
		testNum = 12;
	}
	DataMaker() { defaultPathSet(); }
	//构造函数：提供无参构造函数，有参构造函数有3个参数,参数位置随意
	//可以省略测试数据个数，默认为12组数据
	DataMaker(std::string path, MakeTestFun func, int testNum = 12) : testcasePath(path), testMakeFunction(func), testNum(testNum) {}
	DataMaker(std::string path, int testNum, MakeTestFun func) : testcasePath(path), testMakeFunction(func), testNum(testNum) {}
	DataMaker(int testNum, std::string path, MakeTestFun func) : testcasePath(path), testMakeFunction(func), testNum(testNum) {}
	DataMaker(int testNum, MakeTestFun func, std::string path) : testcasePath(path), testMakeFunction(func), testNum(testNum) {}
	DataMaker(MakeTestFun func, int testNum, std::string path) : testcasePath(path), testMakeFunction(func), testNum(testNum) {}
	DataMaker(MakeTestFun func, std::string path, int testNum = 12) : testcasePath(path), testMakeFunction(func), testNum(testNum) {}

	void setPath(std::string path) {
		this->testcasePath = path;
	}
	void setTestNum(int num) {
		this->testNum = num;
	}
	void setMakeTestFunc(MakeTestFun func) {
		this->testMakeFunction = func;
	}

	void setignoreMakeInputDataError(bool model) {
		this->ignoreMakeInputDataError = model;
	}
	void setignoreMakeOutputDataError(bool model) {
		this->ignoreMakeOutputDataError = model;
	}
};


// SpecialJudgeDataMaker：继承自DataMaker类，用于实现生成SpecialJudge题目的数据
// 此类生成数据时，必须要传入数据生成方法（生成函数）和数据生成路径
// 如果不忽略数据生成异常，默认在数据生成错误时抛出异常中断程序
// 如果使用无参构造函数，将使用默认配置
class SpecialJudgeDataMaker :public DataMaker {
protected:
	virtual void make(int __test_num) override {
		std::cerr << "Test" << __test_num << " :make begin" << std::endl;
		std::string __INPUT_FILE__ = fileNameMaker(__test_num, testcasePath, 1);

		makeInFile(__INPUT_FILE__, __test_num);
		//std解法

		//Special Judge不产生.out文件，将跳过输出数据生成
		//使用std标程重定向到文件输出.out文件

		std::cerr << "Special Judge Test , Skip OutputFile Create !" << std::endl;

		std::cerr << "Test" << __test_num << " :make done!" << std::endl;
		std::cerr << std::endl;
	}
public:
	virtual void run() override {
		if (testMakeFunction == nullptr)throw std::runtime_error("NullPtrError:You are not set make function!");
		if (testcasePath == "")throw std::runtime_error("NoPathError:You are not set path!");
		if (testNum < 1)throw std::runtime_error("NoTestNumError:You are not set testnum!");
		for (int i = 1; i <= testNum; i++) {
			make(i);
		}
		std::cerr << "All TestCases make done!" << std::endl;
	}

	virtual void defaultPathSet() override {
		DataMaker::defaultPathSet();
	}

	SpecialJudgeDataMaker() { this->defaultPathSet(); }
	//继承父类构造函数，不提供新的构造函数（不需要新构造函数）
	//构造函数：提供无参构造函数，有参构造函数有3个参数,参数位置随意
	//可以省略测试数据个数，默认为12组数据
	SpecialJudgeDataMaker(std::string path, MakeTestFun func, int testNum = 12) : DataMaker(path, func, testNum) {}
	SpecialJudgeDataMaker(std::string path, int testNum, MakeTestFun func) : DataMaker(path, func, testNum) {}
	SpecialJudgeDataMaker(int testNum, std::string path, MakeTestFun func) : DataMaker(path, func, testNum) {}
	SpecialJudgeDataMaker(int testNum, MakeTestFun func, std::string path) : DataMaker(path, func, testNum) {}
	SpecialJudgeDataMaker(MakeTestFun func, int testNum, std::string path) : DataMaker(path, func, testNum) {}
	SpecialJudgeDataMaker(MakeTestFun func, std::string path, int testNum = 12) : DataMaker(path, func, testNum) {}
};


// DataMakerFromEXE：继承自DataMaker类，用于实现生成数据，使用std可执行文件生成数据
// 此类生成数据时，必须要传入数据生成方法（生成函数）、std可执行文件的全路径和数据生成路径
// 如果不忽略数据生成异常，默认在数据生成错误时抛出异常中断程序
class DataMakerFromEXE :public DataMaker {
protected:
	std::string cmd;

	//使用标程的EXE文件构造数据
	void makeOutFileEXE(std::string __INPUT_FILE__, std::string __OUTPUT_FILE__, int __test_num) {
		std::cerr << __OUTPUT_FILE__ << " :make begin" << std::endl;
		auto tcmd = cmd;
		//cmd字符串为std程序的全路径
		tcmd += " <" + __INPUT_FILE__;
		tcmd += " >" + __OUTPUT_FILE__;
		int returnNum = system(tcmd.c_str());
		if (returnNum) {
			//调用标程时出现错误，抛出异常
			std::cerr << __OUTPUT_FILE__ << " :make failed , error num = " << returnNum << std::endl;
			if (!ignoreMakeOutputDataError) {
				throw std::runtime_error("OutputFileMakeError:make output file error!");
			}
		}
		else {
			std::cerr << __OUTPUT_FILE__ << " :make done" << std::endl;
		}
	}

	virtual void make(int __test_num) override {
		std::cerr << "Test" << __test_num << " :make begin" << std::endl;
		std::string __INPUT_FILE__ = fileNameMaker(__test_num, testcasePath, 1);
		std::string __OUTPUT_FILE__ = fileNameMaker(__test_num, testcasePath, 0);

		makeInFile(__INPUT_FILE__, __test_num);
		//std解法

		//Special Judge不产生.out文件，将跳过输出数据生成
		//如果不是SpecialJudge，生成.out文件
		makeOutFileEXE(__INPUT_FILE__, __OUTPUT_FILE__, __test_num);

		//使用std标程重定向到文件输出.out文件

		std::cerr << "Test" << __test_num << " :make done!" << std::endl;
		std::cerr << std::endl;
	}

public:
	virtual void run() override {
		if (testMakeFunction == nullptr)throw std::runtime_error("NullPtrError:You are not set make function!");
		if (testcasePath == "")throw std::runtime_error("NoPathError:You are not set path!");
		if (testNum < 1)throw std::runtime_error("NoTestNumError:You are not set testnum!");
		if (cmd == "")throw std::runtime_error("NoStdSourceError:You are not set std Source!");
		for (int i = 1; i <= testNum; i++) {
			make(i);
		}
		std::cerr << "All TestCases make done!" << std::endl;
	}

	virtual void defaultPathSet() override {
		DataMaker::defaultPathSet();
		cmd = "D:/input/std.exe";
	}

	void setstdEXEPath(std::string stdEXEPath) {
		this->cmd = stdEXEPath;
	}

	DataMakerFromEXE() { this->defaultPathSet(); }
	//构造函数：提供无参构造函数，有参构造函数有4个参数，第一个参数必须为std程序的路径，其余参数随意
	//可以省略测试数据个数，默认为12组数据
	DataMakerFromEXE(std::string stdEXEPath, std::string path, MakeTestFun func, int testNum = 12) : DataMaker(path,func,testNum) {
		setstdEXEPath(stdEXEPath);
	}
	DataMakerFromEXE(std::string stdEXEPath, std::string path, int testNum, MakeTestFun func) : DataMaker(path, func, testNum) {
		setstdEXEPath(stdEXEPath);
	}
	DataMakerFromEXE(std::string stdEXEPath, int testNum, std::string path, MakeTestFun func) : DataMaker(path, func, testNum) {
		setstdEXEPath(stdEXEPath);
	}
	DataMakerFromEXE(std::string stdEXEPath, int testNum, MakeTestFun func, std::string path) : DataMaker(path, func, testNum) {
		setstdEXEPath(stdEXEPath);
	}
	DataMakerFromEXE(std::string stdEXEPath, MakeTestFun func, int testNum, std::string path) : DataMaker(path, func, testNum) {
		setstdEXEPath(stdEXEPath);
	}
	DataMakerFromEXE(std::string stdEXEPath, MakeTestFun func, std::string path, int testNum = 12) : DataMaker(path, func, testNum) {
		setstdEXEPath(stdEXEPath);
	}
	
	//继承父类构造函数
	//构造函数：提供无参构造函数，有参构造函数有3个参数,参数位置随意
	//可以省略测试数据个数，默认为12组数据
	DataMakerFromEXE(std::string path, MakeTestFun func, int testNum = 12) : DataMaker(path,func,testNum) {}
	DataMakerFromEXE(std::string path, int testNum, MakeTestFun func) : DataMaker(path, func, testNum) {}
	DataMakerFromEXE(int testNum, std::string path, MakeTestFun func) : DataMaker(path, func, testNum) {}
	DataMakerFromEXE(int testNum, MakeTestFun func, std::string path) : DataMaker(path, func, testNum) {}
	DataMakerFromEXE(MakeTestFun func, int testNum, std::string path) : DataMaker(path, func, testNum) {}
	DataMakerFromEXE(MakeTestFun func, std::string path, int testNum = 12) : DataMaker(path, func, testNum) {}
};

class DataMakerFromCppSourceFile :public DataMakerFromEXE {
protected:
	// cmd为c++源文件路径

	std::string gccCompilePath;

	std::string vcCompile;

	void autoComilePath() {
		int gccReturnNum = system("g++ -v");
		int vcReturnNum = system("cl.exe -v");
		if (!gccReturnNum) {
			gccCompilePath = "g++";
		}
		if (!vcReturnNum) {
			vcCompile = "cl.exe";
		}
	}

	void compileCppFile(std::string stdSourceFilePath) {
		if (gccCompilePath == "" && vcCompile == "") {
			cerr << "compile path not set,system will auto get comple path" << std::endl;
			autoComilePath();
		}
		if (gccCompilePath == "" && vcCompile == "") {
			cerr << "compile error : system can't get comple path" << std::endl;
			throw std::runtime_error("NoCompilePathError:system path has no comile path");
		}
		std::string compileCmd;
		if (gccCompilePath != "") {
			compileCmd = gccCompilePath;
		}
		else {
			compileCmd = vcCompile;
		}
	}

	virtual void make(int __test_num) override {
		std::cerr << "Test" << __test_num << " :make begin" << std::endl;
		std::string __INPUT_FILE__ = fileNameMaker(__test_num, testcasePath, 1);
		std::string __OUTPUT_FILE__ = fileNameMaker(__test_num, testcasePath, 0);

		makeInFile(__INPUT_FILE__, __test_num);
		//std解法

		//Special Judge不产生.out文件，将跳过输出数据生成
		//如果不是SpecialJudge，生成.out文件
		makeOutFileEXE(__INPUT_FILE__, __OUTPUT_FILE__, __test_num);

		//使用std标程重定向到文件输出.out文件

		std::cerr << "Test" << __test_num << " :make done!" << std::endl;
		std::cerr << std::endl;
	}
public:

};
