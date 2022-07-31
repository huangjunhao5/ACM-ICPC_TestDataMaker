#pragma once
#include <string>
#include <iostream>
#include <cstdlib>



// ������DataMaker��δʵ��make������run��������Ҫ��дmake������run����
// make������д˵��������һ��������Ϊ��ǰ��������ݱ�ţ��ڼ������ݣ�
// ��������·�����ɺ������ɲ������ݵ�ȫ·��������.in�ļ���.out�ļ���1Ϊin��0Ϊout��
// Ȼ��ʹ��freopen�򿪲��������ļ�
// �ٵ��ô����fun������������
// fun��������ʹ��cout��������
// run������Ҫ���л����������жϣ��ж��������ݵı�Ҫ�����Ƿ�߱�
// �����׳��쳣
// ���ʹ���޲ι��캯������ʹ��Ĭ�ϵ����ɲ�������
// �������ɵ�·����D:/input/
// ���ݵ�������12
// Ĭ�ϵ��������ɺ������ṩ�����û�д����������ɺ��������׳��쳣
class DataMaker
{
protected:
	typedef void (*MakeTestFun)(int testcase);
	std::string testcasePath = "";	
	MakeTestFun testMakeFunction = nullptr;
	int testNum = 12;
	
	bool ignoreMakeInputDataError = 0;

	bool ignoreMakeOutputDataError = 0;

	// ���������ļ���ȫ·�������δָ��·�����׳��쳣
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

	//ʹ��fun������������
	void makeInFile(std::string __INPUT_FILE__ ,int __test_num) {
		std::cerr << __INPUT_FILE__ << " :make begin" << std::endl;
		auto it = freopen(__INPUT_FILE__.c_str(), "w", stdout);
		if (it == nullptr) {
			//�����ļ���ʧ�ܣ��׳��쳣
			std::cerr << __INPUT_FILE__ << " make error : can't open file path" << __INPUT_FILE__ << std::endl;
			if(!ignoreMakeInputDataError){
				throw std::runtime_error("InputFileMakeError:make input file error!");
			}
			return;
		}
		{
			//�����ﹹ������
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
	//���캯�����ṩ�޲ι��캯�����вι��캯����3������,����λ������
	//����ʡ�Բ������ݸ�����Ĭ��Ϊ12������
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


// SpecialJudgeDataMaker���̳���DataMaker�࣬����ʵ������SpecialJudge��Ŀ������
// ������������ʱ������Ҫ�����������ɷ��������ɺ���������������·��
// ������������������쳣��Ĭ�����������ɴ���ʱ�׳��쳣�жϳ���
// ���ʹ���޲ι��캯������ʹ��Ĭ������
class SpecialJudgeDataMaker :public DataMaker {
protected:
	virtual void make(int __test_num) override {
		std::cerr << "Test" << __test_num << " :make begin" << std::endl;
		std::string __INPUT_FILE__ = fileNameMaker(__test_num, testcasePath, 1);

		makeInFile(__INPUT_FILE__, __test_num);
		//std�ⷨ

		//Special Judge������.out�ļ��������������������
		//ʹ��std����ض����ļ����.out�ļ�

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
	//�̳и��๹�캯�������ṩ�µĹ��캯��������Ҫ�¹��캯����
	//���캯�����ṩ�޲ι��캯�����вι��캯����3������,����λ������
	//����ʡ�Բ������ݸ�����Ĭ��Ϊ12������
	SpecialJudgeDataMaker(std::string path, MakeTestFun func, int testNum = 12) : DataMaker(path, func, testNum) {}
	SpecialJudgeDataMaker(std::string path, int testNum, MakeTestFun func) : DataMaker(path, func, testNum) {}
	SpecialJudgeDataMaker(int testNum, std::string path, MakeTestFun func) : DataMaker(path, func, testNum) {}
	SpecialJudgeDataMaker(int testNum, MakeTestFun func, std::string path) : DataMaker(path, func, testNum) {}
	SpecialJudgeDataMaker(MakeTestFun func, int testNum, std::string path) : DataMaker(path, func, testNum) {}
	SpecialJudgeDataMaker(MakeTestFun func, std::string path, int testNum = 12) : DataMaker(path, func, testNum) {}
};


// DataMakerFromEXE���̳���DataMaker�࣬����ʵ���������ݣ�ʹ��std��ִ���ļ���������
// ������������ʱ������Ҫ�����������ɷ��������ɺ�������std��ִ���ļ���ȫ·������������·��
// ������������������쳣��Ĭ�����������ɴ���ʱ�׳��쳣�жϳ���
class DataMakerFromEXE :public DataMaker {
protected:
	std::string cmd;

	//ʹ�ñ�̵�EXE�ļ���������
	void makeOutFileEXE(std::string __INPUT_FILE__, std::string __OUTPUT_FILE__, int __test_num) {
		std::cerr << __OUTPUT_FILE__ << " :make begin" << std::endl;
		auto tcmd = cmd;
		//cmd�ַ���Ϊstd�����ȫ·��
		tcmd += " <" + __INPUT_FILE__;
		tcmd += " >" + __OUTPUT_FILE__;
		int returnNum = system(tcmd.c_str());
		if (returnNum) {
			//���ñ��ʱ���ִ����׳��쳣
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
		//std�ⷨ

		//Special Judge������.out�ļ��������������������
		//�������SpecialJudge������.out�ļ�
		makeOutFileEXE(__INPUT_FILE__, __OUTPUT_FILE__, __test_num);

		//ʹ��std����ض����ļ����.out�ļ�

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
	//���캯�����ṩ�޲ι��캯�����вι��캯����4����������һ����������Ϊstd�����·���������������
	//����ʡ�Բ������ݸ�����Ĭ��Ϊ12������
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
	
	//�̳и��๹�캯��
	//���캯�����ṩ�޲ι��캯�����вι��캯����3������,����λ������
	//����ʡ�Բ������ݸ�����Ĭ��Ϊ12������
	DataMakerFromEXE(std::string path, MakeTestFun func, int testNum = 12) : DataMaker(path,func,testNum) {}
	DataMakerFromEXE(std::string path, int testNum, MakeTestFun func) : DataMaker(path, func, testNum) {}
	DataMakerFromEXE(int testNum, std::string path, MakeTestFun func) : DataMaker(path, func, testNum) {}
	DataMakerFromEXE(int testNum, MakeTestFun func, std::string path) : DataMaker(path, func, testNum) {}
	DataMakerFromEXE(MakeTestFun func, int testNum, std::string path) : DataMaker(path, func, testNum) {}
	DataMakerFromEXE(MakeTestFun func, std::string path, int testNum = 12) : DataMaker(path, func, testNum) {}
};

class DataMakerFromCppSourceFile :public DataMakerFromEXE {
protected:
	// cmdΪc++Դ�ļ�·��

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
		//std�ⷨ

		//Special Judge������.out�ļ��������������������
		//�������SpecialJudge������.out�ļ�
		makeOutFileEXE(__INPUT_FILE__, __OUTPUT_FILE__, __test_num);

		//ʹ��std����ض����ļ����.out�ļ�

		std::cerr << "Test" << __test_num << " :make done!" << std::endl;
		std::cerr << std::endl;
	}
public:

};
