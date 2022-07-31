# ACM-ICPC_TestDataMaker
用于创建题目数据的工具类，使用该工具类可以方便地生成测试数据

使用时，只需要将你的项目包含DataMaker.h,然后就可以方便地调用数据生成器和拓展其功能

基本用法：创建对应的对象，设置正确的参数后，调用对象的.run()函数即可完成数据生成

下面说明DataMaker.h中一些类的用法：

# DataMaker
所有数据生成器的父类，是一个抽象类，不能实例化为对象。

该类中定义了一些数据生成器的基本功能的函数，并且定义了数据生成函数，需要子类对这些函数重写

下面对该类的继承、拓展功能操作进行说明

未实现make函数和run函数，需要重写make函数和run函数

make函数编写说明：传入一个参数，为当前制造的数据编号（第几组数据）

调用数据路径生成函数生成测试数据的全路径（包括.in文件和.out文件，1为in，0为out）

然后使用freopen打开测试数据文件

再调用传入的tesxMakeFunction函数生成数据

fun函数可以使用cout构造数据

run函数需要进行基本的运行判断，判断生成数据的必要参数是否具备

否则抛出异常

如果使用无参构造函数，将使用默认的生成参数设置

数据生成的路径：D:/input/

数据的组数：12

默认的数据生成函数不提供，如果没有传入数据生成函数，将抛出异常

接下来是成员函数的说明：

## std::string fileNameMaker(int name, std::string testPath, bool __IS_INPUT_FILE)

该函数的作用是返回生成数据文件的全路径，以便数据进行生成。

第一个参数name代表当前生成数据的编号

第二个参数testPath代表生成数据的路径

第三个参数__IS_INPUT_FILE代表当前在生成的数据是.in文件还是.out文件



## void makeInFile(std::string __INPUT_FILE__ ,int __test_num)

该函数的作用是生成对应测试数据的输入文件（.in）

第一个参数代表当前生成的输入文件全路径

第二个参数代表当前的测试数据编号



## void setPath(std::string path)

该函数的作用是设置数据生成路径



## void setTestNum(int num)

该函数的作用是设置数据组数

## void setMakeTestFunc(MakeTestFun func)

该函数的作用是设置输入数据生成函数



## void setignoreMakeInputDataError(bool model)

设置忽略输入数据生成错误（不建议），设置为true后，将忽略大部分数据生成异常



## void setignoreMakeOutputDataError(bool model)

设置忽略输出数据生成错误（不建议），设置为true后，将忽略标程运行异常



## 构造函数：3个参数，随意放置位置

1、数据生成函数

2、数据生成路径

3、数据生成的组数


提供无参构造函数，将自动使用默认配置



# SpecialJudgeDataMaker

SpecialJudgeDataMaker：继承自DataMaker类，用于实现生成SpecialJudge题目的数据

此类生成数据时，必须要传入数据生成方法（生成函数）和数据生成路径

如果不忽略数据生成异常，默认在数据生成错误时抛出异常中断程序

如果使用无参构造函数，将使用默认配置





# DataMakerFromEXE

DataMakerFromEXE：继承自DataMaker类，用于实现生成数据，使用std可执行文件生成数据

此类生成数据时，必须要传入数据生成方法（生成函数）、std可执行文件的全路径和数据生成路径

如果不忽略数据生成异常，默认在数据生成错误时抛出异常中断程序



## void makeOutFileEXE(std::string __INPUT_FILE__, std::string __OUTPUT_FILE__, int __text_num)

通过系统调用std标程的可执行文件生成输出文件(.out)

第一个参数代表输入文件的全路径

第二个参数代表输出文件的全路径

第三个参数代表生成数据的编号



## 构造函数：提供3个参数、4个参数的构造函数

3个参数的构造函数与DataMaker相同

使用4个参数的构造函数时，要保证第一个参数是标程EXE在电脑中的全路径，后面3个参数随意

提供无参构造函数，将尽可能使用默认配置：

标程默认路径：D:/input/std.exe

其余默认配置继承自DataMaker类

