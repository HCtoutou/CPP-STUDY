### const

#### C语言中的const

在c语言中可以通过指针的方式修改const的值，因为编译器会为它分配内存空间，只要分配了内存空间，就可以通过指针的方式强行修改其中的值。

```c++
const int num = 10;//全局下的一个const常量，这个不能通过指针进行修改，受到保护
void test1(){
    const int a=10;
    int *p = (int *)&a;
    *p = 200;//进行修改
}

void test2()
{
    const int b=10;//伪常量
    int arr[b]//不可以用const来声明数组，因为在c语言中它是一个伪常量。
}
```

#### C++中的const  

在C++中const为一个真正的常量，不可以利用指针对const常量中的值进行修改，且const修饰的值可以用来初始化数组。

```c++
void test(){
    const int a=10;//真正的常量
    int *p = (int *)&a;
    *p = 200;
    cout<<"*p = "<<*p<<endl;
    cout<<"a = "<<a<<endl;
    // *p = 200,a = 10  并没有修改a的值
    int arr[a];//可以用来初始化
} 
```



**为什么上方代码中使用指针修改了a的值，但是最终a的值并没有改变**

```c++
//上方代码的解释
	const int a=10;//真正的常量
    int *p = (int *)&a;
    *p = 200;

//编译器会临时开辟一块内存空间
int tmp = a;//tmp有自己的内存
int *p  =(int*)&tmp;
//*p指向了临时的tmp的空间，所以修改的是tmp的值
```



#### cosnt的内部链接与外部链接

c语言中const默认是外部链接，外部可见，即在整个工程文件中都可见。

C++中const默认是内部链接，外部不可见，只可在当前文件中可见



#### cosnt的内存分配情况

```c++
void test01()
{
    //1、const分配内存 取地址会分配临时内存
    const int a = 10;
    int *p = (int*)&a;//会分配临时内存
    //2、extern编译器也会给const变量分配内存
    
    //3、用普通变量初始化const的变量
    int m = 10;
    const int n=m;//会分配内存
    
    //判断是否分配内存只需要使用指针看是否能修改其值
    int *p =(int*)&m;
    *p = 100;
    cout<<p<<endl;
}

void test02()
{
    //4、自定义数据类型，加const也会分配内存空间
    struct Person
    {
        string name;
        int age;
    }
    const Person p1;
    //p1.name = "hhh"   //因为加了const不能直接修改
    //但是对自定义数据类型用const修饰会分配内存，所以可以用指针进行修改
    Person *p = (Person*)&p1;
    //(*p).name = "hhh";
    p->name = "hhh";
}
```

### const代替define

```c++
#define MAX 1024

#undef MAX  //卸载宏常量
```

我们定义的宏MAX从未被编译器看到过，因为在**预处理阶段，所有的MAX已经被替换为了1024**，于是MAX并没有被加入到符号表中。但我们使用这个常量获得一个编译错误信息时，可能会带来一些困惑，因为这个信息可能会提到1024，但是并不会提到MAX。如果MAX被定义在一个不是你写的头文件中，你可能并不知道1024代表什么，也许解决这个问题要花费很长时间。**一个办法就是用常量替换上面的宏。**

**const和#define 区别总结**

- const有类型，可进行编译器类型安全检查。#define无类型，不可进行类型检查
- const有作用域，而#define不重视作用域，默认定义处到文件结尾。如果定义在指定作用域下有效的常量，那么#define就不能用。

### 引用

引用的实质就是起别名

另外以一种给函数传递地址的途径

- 变量名实质上是一段连续内存空间的别名，是一个标号
- 程序中通过变量来申请并命名内存空间
- 通过变量的名字可以使用存储空间

#### 引用的基本语法

```c++
void test(){
    int a = 10;
    int &b = a;//给a起别名，即a和b指向同一个内存空间
     b=20;//修改b的值，a的值也会改变
}
```

#### 引用必须被初始化

```c++
void test()
{
    // int &a; //报错，未初始化
    int a = 10;
    int &b = a;//引用初始化后不能修改
    int c = 20;
    b = c;//赋值，并不是重新初始化为C
}
```

#### 对数组建立引用

```c++
void test(){
    int arr[10];
    for(int i = 0;i<10;i++)
        arr[i]=i;
    
    //给数组起别名
    int (&pArr)[10] = arr;
    
    typedef int(ARRAYREF)[10];//一个具有10个元素的int类型的数组 
    
    ARRAYREF &pArr2 = arr;//给arr有重新起别名为pArr2
} 
```

#### 参数的传递方式

```c++
//交换两数
void mySwap(int a,int b)//值传递，并不能交换两数的值
{//只做逻辑上的判断，但是并不改变原始 的值
    int tmp = a;
    a = b;
    b = a;
}

void mySwap1(int *a,int *b)//指针传递 
{  
    int tmp = *a;
    *a = *b;
    *b = *tmp;
}

void mySwap2(int &a,int &b)//引用传递
{
    int tmp = a;
    a = b;
    b = tmp;
}

int main()
{
    int a=10,b=20;
}
```

#### 引用的注意事项

```c++
void test1()
{
    //1、int &a = 10;错误，引用必须引用合法的内存空间。
    
}

//2、不要返回局部变量的引用
int &doWork()
{
    int a = 10;
    return a;
}

void test2()
{
    int &ret = doWork();
    cout<<"ret = "<<ret<<endl;//第一次输出编译器可能会自动优化
    cout<<"ret = "<<ret<<endl;//如果多次打印，则会输出其他结果，因为doWork返回的是局部变量的引用
    cout<<"ret = "<<ret<<endl;//调用完这个局部变量就会消亡
    cout<<"ret = "<<ret<<endl;
    
    //如果函数的返回值是一个引用，那么这个函数调用可以作为左值
    doWork()= 20;
}
```

#### 引用的本质

引用的本质在C++内部实现是一个指针常量,C++编译器在编译过程中使用常指针作为引用的内部实现，因此引用所占的空间与指针相同，只是这个过程是编译器内部实现的，用户不可见

```c++
Type& ref = val;  //Type* const ref = &val;
```

```c++
//发现是引用，转换为int* const ref = &a;
void testFunc(int& ref){
    ref = 100;//ref是引用，转换为*ref = 100；
}

int main()
{
    int a = 10;
    itn& aRef = a;//自动转换为 int* const aRef = &a,这也能说明引用为什么必须初始化
    aRef = 20; //内部发现aRef是引用，自动帮我们转化为：*aRef = 20;
    cout<<"a: "<<a<<endl;
    cout<<"aRef: "<<aRef<<endl;
    testFunc(a);
    return EXIT_SUCCESS
}
```

#### 指针的引用

```c++
struct Person
{
    int m_Age;
}

void allocatMemory(Person ** p)//**p 具体的Person对象 *p对象的指针  p指针的指针
{
    *p = (Person*)malloc(sizeof(Person));
    (*p)->m_Age = 100;
}

void test01()
{
    Person* p = nullptr;
    allocateMemory(&p);
    cout<<"p的年龄： "<<p->m_Age<<endl;
}

//利用指针引用开辟空间
void allocatMemoryByRef(Person* &p)
{
    p = (Person*)malloc(sizeof(Person));
    p->m_Age = 1000;
}
void test02()
{
    Person* p =nullptr;
    allocatMemoryByRef(p);
}
```

#### 常量的引用

```c++
void test01()
{
   // int &ref = 10;//会报错，引用了不合法的内存
    const int &ref = 10;//不会报错，加入const后，编译器的处理方式为：int tmp = 10;const int &ref = tmp
    //可通过指针修改ref的值  
    int *p = (int*)&ref;
    *p = 100;
}
```

**常量引用场景，通常用来修饰形参**

```c++
void showValue(const int &val)//如果只是想展示内容，而不修改内容，那么就用const修饰这个形参
{
    cout<<"val = "<<val<<endl;
}

void test02()
{
    int a = 10;
    showValue(a);
}
```



### 内联函数

C++从C中继承的一个重要特征就是效率。假如C++的效率明显低于C的效率，那么就会有很大一批程序员不会使用C++了。

在C中我们经常把一些短的并且执行频繁的计算写成宏，而不是函数，这样做的理由是为了执行效率，**宏可以避免函数调用的开销，这些都由预处理来完成。**

但是在C++出现之后，使用预处理宏会出现两个问题：

- 第一个在C中也常出现，宏看起来像一个函数调用，但是会有隐藏一些难以发现的错误
- 第二个问题是C++特有的，预处理器不允许访问类的成员，也就是说预处理器宏不能用作类的成员函数

**为了保持预处理宏的效率又增加安全性，而且还能像一般成员函数那样可以在类里访问自如，C++引入了内联函数（inline function）**

####  宏函数的缺陷

```c++
#include<iostream>
using namespace std;

//定义一个加法
#define MyAdd(x,y) x+y;//可通过加括号来避免test01中的宏缺陷

void test01()
{
    //int ret = MyAdd(10,20);
    int ret = MyAdd(10,20)*20;//预期结果 （10+20）*20=600  实际结果 10+20*20 =410  宏缺陷 
    cout<<"ret = "<<ret<<endl;

}
```

```c++
//定义一个比较的方法
#define MyCompare(a,b) a < b ? a : b//C++中返变量a或b，c中返回的是a或b的具体的值

void test02()
{
    int a = 10;
    int b = 20;
    //int ret = MyCompare(a,b);结果返回10
    int ret = MyCompare(++a,b);//将宏展开 ++a < b ? ++a : b 预期应该返回11，结果返回12
    
    cout<<"ret = "<<ret<<endl; 
```

#### 内联函数基本概念

在C++中，预定义宏的概念是用内联函数来实现的（避免宏缺陷），**而内联函数是一个真正的函数。**内联函数具有普通函数的所有行为。唯一不同之处在于内联函数会在适当的地方像预定义宏一样展开，所以不需要函数调用的开销。

**在普通函数（非成员函数）前面加上inline关键字使之成为内联函数。**但是必须注意函数体和声明必须结合在一起，否则编译器将他作为普通函数来对待

```c++
inline void func(int a);//这种写法没有任何效果，仅仅只是声明函数
```

```c++
inline void func(int a){return a++;}//应该协商具体的实现
```

内联函数的确占用空间，但是内联函数相对于普通函数的优势只是省去了函数调用时候的压栈，跳转，返回的开销。我们可以理解为**内联函数是以空间换时间。**

```c++
inline void mycompare(int a,int b)
{
    return a < b ? a : b;
}

void test(){
    int a = 10;
    int b = 20;
    int ret = mycompare(++a,b);
    cout<<"ret = "<<ret<<endl;
}
```

#### 类内部的内联函数

**类内部定义内联函数时并不是必须的，任何在类内部定义的函数自动成为内联函数**

```c++
class Person{
  public:
    Person(){cout<<"构造函数"<<endl;}
    void PrintPerson(){cout<<"输出Person！"<<endl;}
};
```

构造函数Person，成员函数PrintPerson在类的内部定义，自动成为内联函数。

#### 内联函数与编译器

C++内联编译会有一些限制，以下情况编译器可能考虑不会将函数进行内联编译

- 不能存在任何形式的循环语句
- 不能存在过多的条件判断语句
- 函数体不能过于庞大
- 不能对函数进行取址操作

**内联仅仅是给编译器一个建议，编译器不一定会接收这种建议，如果你没有将函数声明为内联函数，那么编译器也可能将此函数做内联编译，一个好的编译器将会内联小的，简单的函数**

### 函数的默认参数

C++在声明函数原型的时候可以为一个或者多个参数指定默认（缺省）的参数值，当函数调用的时候如果没有指定这个值，编译器会自动用默认值代替。

在C++中编译器不会为其分配内存，在内部是一个key-value的表。

```c++
void TestFunc01(int a=10,int b=20)
{
	cout<<"a+b= "<<a+b<<endl;
}
//注意点：
//1、形参b设置默认参数值，那么后面位置的形参c也需要设置默认参数
void TestFunc02(int a,int b=10,int c=10){}
//2、如果函数声明和函数定义分开，函数声明设置了默认参数，函数定义不能再设置默认参数
void TestFunc03(int a=0,int b=0);
void TestFunc03(int a,int b);

int main(){
	//1、如果没有传参数，那么使用默认参数
    TestFunc01();
    //2、如果传一个参数，那么第二个参数使用默认参数
    TestFunc01(100);
    //3、如果传入两个参数，那么两个参数都使用我们传入的参数
    TestFunc01(100,200);
    
    return EXIT_SUCCESS;
}
```

### 函数的占位参数

没什么大用途

```c++
//如果有了占位参数，函数调用的时候必须提供这个参数，但是用不到参数
//占位参数 没什么大用途，只有后面重载 ++符号有一点用
//占位参数 可以有默认值
void func(int a,int)
{
    
} 
```

### 函数重载

函数重载是一种特殊情况，C++允许在**同一个作用域中**声明几个类似的同名函数，这些同名函数的形参列表（参数个数，类型，顺序）必须不同，常用来处理实现功能类似数据类型不同的问题。

**返回值不同不足以构成函数重载的条件**

- 同一个作用域
- 参数个数不同
- 参数类型不同
- 参数顺序不同

 ```c++
 //函数重载
 //C++中函数名称可以相同
 //必须在同一个作用域下，函数名称相同
 //函数的参数个数不同，或类型不同，或者顺序不同
 void func(){
 	cout<<"无参数的函数"<<endl;
 }
 
 void func(int a){
     cout<<"有参数的函数"<<endl;
 }
 
 void func(double a){
     cout<<"有参数的函数"<<endl;
 }
 
 
 class Person{
    public:
     void func();//不是函数重载
 }；
 ```

#### 当函数重载 碰到了默认参数时候，要注意避免二义性的问题

```c++
void fun2(int a,int b=10)
{
    
}
void fun2(int a)
{
    
}
int main()
{
    fun2(10);//此时会出现二义性问题，不知道该调用哪一个函数。
}
```

#### 引用的重载

```c++
void func3(int &a)
{     
}

void func3(const int &a)//const也是可以作为重载的条件  int tmp = 10;const int &a=tmp
{
    
}

int main(){
    func3(10);//会调用const，因为引用必须指向一个合法的内存，直接写10并未为其分配内存空间
}
```

#### 函数重载的实现原理

编译器为了实现函数重载，也是默认为我们做了一些幕后工作，编译器用不同的参数类型来修饰不同的函数名，比如void func();编译器可能会将函数名修饰成 _func，当编译器碰到void func(int x),编译器可能将函数名修饰为 _func_int,当编译器碰到void func(int x,char c)时，编译器可能会将函数名修饰为 _func_int_char 我这里用“可能”这个字眼是因为编译器如何修饰重载函数名称并没有一个统一的标准，所以不同的编译器可能会产生不同的内部名。



```c++
void func(){}
void func(int x){}
void func(int x,char y){}
```

以上三个函数在linux下生成的编译之后的函数名为：

```c++
_Z4funcv//v代表void，无参数
_Z4funci//i代表参数为int类型
_Z4funcic//i代表第一个参数为int类型，c代表第二个参数为char类型
```

### extern “C”浅析

extern “C”的主要作用就是为了实现C++代码能够调用其他C语言代码。加上extern“C"后，这部分代码编译器按C语言的方式进行编译和链接，而不是按C++。

```c++
//test.h
#include<stdio.h>
void show();

//test.c
#include<test.h>
void show()
{
    printf("hello world\n");
}

//main.cpp
#include<iostream>
using namespace std;
//#include"test.h"

//C++中想要调用C语言方法
extern "C" void show();//按照C语言的方式做链接
int main(){
    show();
}
```



若C语言的代码中函数比较多，则可按照以下方式写

```c++
//test.h
#pragma once
#ifdef __cplusplus//两个下划线
extern "C" {
#endif
    
#include<stdio.h>
void show();

#ifdef __cplusplus
}
#endif

//test.c
#include<test.h>
void show()
{
    printf("hello world\n");
}

//main.cpp
#include<iostream>
using namespace std;
#include"test.h"//这种方法需要包含头文件

//C++中想要调用C语言方法
//extern "C" void show();//按照C语言的方式做链接
int main(){
    show();
}
```

### C语言的封装与C++语言的封装

#### C语言下

c语言没有class类，但有结构体,结构体中不能有函数，因此只能将一个结构体的属性和方法分开写

```c++
struct Person{
    char mName[64];
    int mAge;
};
void PersonEat(struct Person *p)//人的吃饭的方法
{
    printf("%s 在吃饭\n",p->mName);
}
void test01(){
    struct Person p1;
    strcpy(p1,mName,"名字");
    PersonEat(&p1);
}

struct Dog{
    char mName[64];
    int mAge;
};
void DogEat(struct Dog *dog)//人的吃饭的方法
{
    printf("%s 在吃狗粮\n",dog->mName);
}
void test02(){
    struct Dog d1;
    strcpy(d1.mName,"名字");
    DogEat(&d1);
    
    struct Person p1;
    strcpy(p1.mName,"人");
    DogEat(&p1);//传进去的为一个人（结构体） ，结果输出为一个人调用了狗的方法。属性和行为分开处理
    //C语言中没有严格的类型转换，没有严格的匹配类型，强制将人变为狗传入
}
```

- C语言封装中，属性和行为分开处理

- 无严格的类型转换，没有严格的类型匹配

#### C++语言下的封装

C++中也有结构体，但在C++中对结构体进行了增强，结构体中可以有相应的方法，从而可以将属性和方法放在一起处理。

**C++中的封装，有严格的类型转换检测，让属性和行为绑定到一起**

**C++中的封装还有控制权限：**

| 访问属性  | 属性 | 对象内部 | 对象外部           |
| --------- | ---- | -------- | ------------------ |
| public    | 公有 | 可以访问 | 可以访问           |
| protected | 保护 | 可以访问 | 不可访问（子类可） |
| private   | 私有 | 可以访问 | 不可访问           |



- class中不声明权限默认为private，struct中不声明权限默认为public

```C++
class Animal{
    private：
        string name;
    
  void show();//在class中不声明权限，默认为private  
};
```

#### 将成员属性设置为私有

建议将所有成员属性设置为私有，自己提供公共的对外接口来进行set或者get方法访问

```c++
class Person{
  public:
    //设置年龄
    void setAge(int age)
    {
        m_Age = age;
    }
    //获取年龄
    int getAge()
    {
        return m_Age;
    }
    
    private:
    string m_Nmae;
    int m_Age;
};
```

### 面向对象设计案例

#### 立方体案例

设计立方体类，求出立方体的面积和体积，分别用全局函数和成员函数判断连两个立方体是否相等

```c++
class Cube
{
  public:
    //设置于获取长宽高
  	void setL(int l){ m_L = l;}
    int getL(){ return m_L;}
    void setW(int w){ m_W = w;}
    int getW(){ return m_W;}
    void setH(int h){ m_H = h;}
    int getH(){ return m_H;}
    
    //求立方体的面积
    int getCubes()
    {
        return 2*(m_L*m_W+m_W*m_H+m_H*m_L);
    }
    //求立方体体积
    int getCubev()
    {
        return m_L*m_W*m_H;
    }
    
    //通过成员函数判断是否相等
    bool compareCubeByClaa(Cube &cub)
    {
        bool ret = m_L == cub.getL() && m_W == cub.getW() && m_H == cub.getH();
        return ret;
    }
  private:
    //长宽高
    int m_L;
    int m_W;
    int m_H;
};

//全局函数判断 两个立方体是否相等
//采用引用传递可以提高效率
bool compareCube(Cube &cub1,Cube &cub2)//传两个参数 不能用const修饰，不能保证成员方法里是否修改了成员属性
{
    if(cub1.getL()==cub2.getL()&&cub1.getW()==cub2.getW()&&cub1.getH()==cub2.getH()) 
        return true;
    return false;
}
```

#### 点和圆的关系

设计一个圆类和一个点类，计算点和圆的关系 

```c++
class Point {
    public:
    void setX(int x) {m_X = x;}
    void setY(int y) {m_Y = y;}
    int getX() {return m_X;}
    int getY() {return m_Y;}
    private:
    int m_X;
    int m_Y;
}; 
class Circle {
  public:
    void setR(int r) {m_R = r;}//设置半径
    int getR() {return m_R;}//获取半径
    void setCenter(Point p)//设置圆心
    {
        m_Center = p;
    }
    int getCenter() {return m_Center;}
    //利用成员函数判断点和圆的关系
    void isInCircleByClass(Point &p)
    {
        int distance = (m_Center.getX()-p.getX())*(m_Center.getX()-p.getX())+(m_Center.getY()-p.getY())*(m_Center.getY()-p.getY());
    	int rDistance = m_R*m_R;
        if(rDistance == distance)
        cout<<"点在圆上"<<endl;
    else if(rDistance > distance)
        cout<<"点在圆内"<<endl;
    else
        cout<<"点在圆外"<<endl;
    }
    
  private:
    int m_R; //半径
    Point m_Center; //圆心
};

//利用全局函数判断点和圆的关系
void isInCircle(Circle& c,Point& p)
{
    //获取圆心到点的距离
    int distance = (c.getCenter().getX()-p.getX())*(c.getCenter().getX()-p.getX())+(c.getCenter().getY()-p.getY())*(c.getCenter().getY()-p.getY());
    int rDistance = c.getR()*c.getR();
    if(rDistance == distance)
        cout<<"点在圆上"<<endl;
    else if(rDistance > distance)
        cout<<"点在圆内"<<endl;
    else
        cout<<"点在圆外"<<endl;
}
```

**当类过多的时候分为.h和.cpp文件编写，提高效率**

### 对象的构造和析构

#### 对象的初始化和清理（构造和析构）

在C++中OO思想也是来源于现实，是对现实事物的抽象模拟，具体来说，**当我们创建对象的时候，这个对象应该有一个初始状态，当对象销毁之前应该销毁自己创建的一些数据**

对象的初始化和清理也是两个非常重要的问题安全问题，一个对象或者变量没有初始时，对其使用后果是未知，同样的使用完一个变量，没有及时清理，也会造成一定的安全问题。C++为了给我们提供这种问题的解决方案，**构造函数和析构函数**，这两个函数将会被编译器自动调用，完成对象初始化和对象清理工作。

**对象的初始化和清理工作是编译器强制我们要做的事情，即使你不提供初始化和清理操作，编译器也会给你增加默认的操作，只是这个默认初始化操作不会做任何事情，所以编写类就应该顺便提供初始化函数**

```c++
class Person {
  public:
      //构造函数写法
    //与类名相同，没有返回值，不写void，可以发生重载（可以有参数）
    //构造函数由编译器自动调用，而不是手动，而且只会调用一次
    Person(){cout<<"构造函数"<<endl;}
    
    //析构函数
    //与类名相同 类名前面加一个符号~，也没有返回值，不写void，不可以有参数（不能发生重载）
    //自动调用 只会调用一次
    ~Person() {cout<<"析构函数调用"<<endl;}
};

void test()
{
    Person p;
}

int main()
{
    //test();//因为对象的创建写在函数中，因此函数执行完毕就会释放，会自动调用构造函数和析构函数
    Person p;//写在main函数中，会自动调用构造函数，当main函数执行完毕时在自动调用析构函数
}
```

#### 构造函数的分类及调用

 分类：

- 按照参数分类

  无参构造函数

  有参构造函数

- 按照类型分类

  普通构造函数

  拷贝构造函数

```c++
class Person {
  public: //构造和析构都必须写在public下才可以调用
    //普通构造函数
    Person(){}//默认 无参构造函数
    Person(){int a}//有参构造函数
    
    //拷贝构造函数
    Person(const Person& p){cout<<"拷贝构造函数"<<endl;}//p不可随意修改
    ~Person() {}//析构函数 
};

void test1()//构造函数的调用  括号法
{
    Person p1(1);//普通构造 有参
    Person p2(p1);//拷贝构造
    
    Person p3;///默认构造函数 不要加小括号()
    //Person p3();//编译器认为这行是一个返回值为Person的函数的声明。
}

void test2()//显示法调用
{
    /*Person(100)  叫匿名对象*/
    /*单写一行匿名对象，编译器会在这行代码结束后就释放这个对象*/
    Person p4 = Person(100);//有参构造
    Person p5 = Person(p4);//拷贝构造
    /*不能用拷贝构造函数初始化匿名对象
      Person(p5) 编译器认为你写成Person p5，是一个对象声明。如果写到右值，那么可以*/
    Person p6 = 100;//有参构造 相当于Person p6 = Person(100) 隐式类型转换
    Person p7 = p6;//这种写法看起来不直观，不推荐使用
    
}
```

#### 拷贝构造函数调用的时机

- 用已经创建好的对象来初始化一个新的对象
- 以值传递的方式给函数参数传值
- 以值的方式返回局部对象 

 ```c++
 class Person {
 public:
 	Person() { cout << "无参构造" << endl; }
     person(int a) {cout<<"有参构造"<<endl; }
 	Person(const Person& p) { //引用必须加
         m_Age = p.m_Age;
         cout << "拷贝构造" << endl;
     }
     
 	~Person() { cout << "析构函数" << endl; }
     private:
     int m_Age;
 };
 
 void test01()
 {
     Person p1;
     p1.m_Age = 10;
     //1、用已经创建好的对象来初始化新的对象
     Person p2(p1);
 }
 
 //2、以值传递的方式给函数参数传值
 void doWork(Person p)//相当于 Person p = Person(p1) 利用拷贝构造函数进行函数参数的值传递
 {
     
 }
 void test02()
 {
     Person p1;
     p1.m_Age = 10;
     doWork(p1);//使用拷贝构造函数进行函数的值传递
 }
 
 //3、以值的方式返回局部对象
 Person doWork2()
 {
     Person p1;
     return p1;//返回的是值不是引用，会调用拷贝构造  
 }
 void test03()
 {
     Person p = doWork2();//调用拷贝构造生成一个新的p返回
 }
 //relesae下优化成什么样
 /*Person p; //不调用默认构造
 doWork2(p);
 
 void dowork2(Person& p)
 {
     Person p1;//调用默认构造
 }*/
 ```

#### 构造函数调用规则

**系统默认给一个类提供三个函数**

**默认构造函数：无参函数体为空**

**默认拷贝构造函数 ：对类中的非静态成员属性进行简单的值拷贝**

**默认析构函数：无参，函数体为空**

- 当我们提供了有参的构造函数，那么系统就不会给我们提供默认的构造函数，但是系统还会提供默认的拷贝构造函数，进行简单的值拷贝。 
- 当我们提供了拷贝构造，系统就不会提供其他构造了。

#### 深拷贝和浅拷贝

- 系统默认提供的拷贝构造会进行简单的值拷贝，属于浅拷贝

- 如果属性里有指向堆区空间的数据，那么简单的浅拷贝会导致重复释放内存的异常
- 解决上述问题需要我们自己提供拷贝构造函数，进行深拷贝

```c++
class Person {
  public:
    Person(){}
    //有参构造
    Person(char *name,int age)
    {
        m_Name = (char*)malloc(strlen(name)+1);
        strcpy(m_Name,name);
        m_age = age;
    }
    //自己提供一个拷贝构造（深拷贝）
    //浅拷贝会释放堆区空间两次，导致挂掉
    Person(const Person& p)
    {//深拷贝
        m_age = p.age;
        m_Name = (char*)malloc(strlen(p.m_Name)+1);//+1因为\0为数组结尾
        strcpy(m_Name,p.m_Name);
    }
    
    ~Person()
    {
        if(m_Name!=NULL)
        {
            free(m_Name);
            m_Name = NULL;
        }
        cout<<"析构函数"<<endl;
    }
    char* m_Name;
    int m_age; 
};

void test01()
{
    Person p1("小米",10);
    Person p2(p1);//调用拷贝构造
}
```

#### 初始化列表

构造函数和其他函数不同，除了有名字，参数列表，函数体之外还有初始化列表。

```c++
class Person {
	public:
    Person(){}
    //有参构造
    /*Person(int a,int b,int c)
    {
        m_A = a;
        m_B = b;
        m_C = c;
    }*/
    //利用初始化列表来初始化数据
    //构造函数后面加一个“：”然后加上需要初始化的属性以及初始化这个属性的参数
    Person(int a,int b,int c):m_A(a),m_B(b),m_C(c){}
    
    int m_A;
    int m_B;
    int m_C;
}
```

#### 类对象作为类成员的案例

```c++
class Phone{
  public:
    Phone(){
        cout<<"手机的默认构造函数"<<endl;
    }
    Phone(string name)
    {
        m_PhoneName = name;
    }
    ~Phone()
    {
        cout<<"手机的析构函数调用"<<endl;
    }
    
    string m_PhoneName;
};

class Game{
  public:
    Game(){
        cout<<"游戏的默认构造函数"<<endl;
    }
    Game(string name){
        m_GameName = name;
    }
    ~Game()
    {
        cout<<"游戏的析构函数调用"<<endl;
    }
    
    string  m_GameName;
};


class Person{
  public:
    Person()
    {
        cout<<"Person 的默认构造函数"<<endl;
    }
    Person(string name)
    {
        m_Name  = name;
    }
    ~Person()
    {
        cout<<"Person的析构函数调用"
    }
    string m_Name;
    Phone m_Phone;
    Game m_Game;
    /*类对象作为类成员时候，构造顺序先将类对象一一构造，析构的顺序是相反的*/
};
void test01(){
    Person p;//先构造Person类内部的Phone和Game，最后在构造Person，析构顺序则相反
    //没有下列两行代码也会调用Phone和Game的构造函数
    //p.m_Phone = "华为"  不可以这么直接赋值
    p.m_Phone.m_PhoneName = "华为";  
    p.m_Game.m_GameName = "斗地主";
}
```

#### explicit关键字作用

**防止隐式类型转换**

```c++
class MyString{
    public:
    MyString(const char *str)
    {
        
    }
    explicit MyString(int a)
    {
        mSize = a;
    }
    char* mStr;
    int mSize;
}

void test01()
{
    MyString str = "abc";
    MyString str2(10);//加上explicit关键字防止隐式类型转换 
    //MyString str3 = 10; 写法表达的意思不明确，可读性不强
    //存在隐式类型转换 MyString str3 = MyString(10);
}
```

#### 动态对象的创建

当我们创建数组的时候，总是需要提前预定数组的长度，然后编译器分配预定长度的数组空间，在使用数组的时候，会有这样的问题，数组也许空间太大了，浪费空间，也许空间不足，所以对于数组来讲，如果能根据需要来分配空间大小再合适不过。

所以动态意味着不确定性

为了解决这个普遍的编程问题，在运行中可以创建和销毁对象是最基本的要求。当然C早就提供了动态内存分配（dynamic memory allocation），函数malloc和free可以运行时从堆中分配存储单元。

然而这些函数在C++中不能很好的运行，因为他不能帮我们完成对象的初始化工作。

**malloc存在的问题**

- 程序员必须确定对象的长度
- malloc返回一个void*指针，C++不允许将void\*赋值给其他任何指针，必须强转。
- malloc可能申请内存失败，所以必须判断返回值来确保内存分配成功
- 用户在使用对象之前必须记住对他初始化，构造函数不能显示调用初始化（构造函数是由编译器调用），用户可能忘记调用初始化函数。 

```c++
Person p = new Person;  
相当于
Person* person = (Person*)malloc(sizeof(Person));
if(person == NULL)
    return 0;
person->Init();
```

**new操作符能确定在调用构造函数初始化之前内存分配是成功的，所有不用显式确定调用是否成功**

```c++
class Person{
    public:
    Person()
    {
        cout<<"默认构造函数"<<endl;
    }
    ~Person()
    { 
        cout<<"默认析构函数"<<endl;
    }
    
};
//new和malloc区别
void test01()
{
    //Person p1;放在栈区
    Person *p2 = new Person;//在堆区开辟的，不会主动释放（析构函数）
    //malloc不会调用构造函数 new会调用构造函数
    //new是一个运算符不是一个函数  malloc是一个函数
    //释放堆区空间调用delete
    delete p2;//delete也是一个运算符  配合new用，于malloc配合free同理
}

void test02()
{
    void *p = new Person;
    //当用void*接收new出来的指针，会出现释放的问题
    delete p;//不会调用析构函数释放
    //无法释放这个p
}

//通过new开辟数组
void test03()
{
    //一定会调用默认构造，需要提供。
    Person* pArray = new Person[10];//开辟10次大小的空间，调用十次构造
    
    Person pArray2[2] = {Person(1),Person(2)};
    
    //释放数组
    delete []pArray;//释放new出来的数组空间，delete释放时必须加上中括号[];
}
```

### 静态成员变量

在一个类中，若将一个成员变量声明为static，这种成员称为静态成员变量。与一般的数据成员不同，不论建立了多少个对象，都只有一个静态数据的拷贝。**静态成员变量属于某个类，所有对象共享**

静态变量，是在**编译阶段**就分配空间，对象还没有创建时，就已经分配好空间。

- 静态成员变量必须在类中声明，在类外定义。
- 静态数据成员不属于某个对象，在为对象分配空间中不包括静态成员所占的空间。
- 静态数据成员可以通过类名或者对象名来引用。

```c++
class Person {
    public:
    Person(){
        //不在构造函数里初始化静态变量，因为若不适用对象来访问这个静态属性的话，而是直接使用类名访问，那么就不会调用构造函数，也就不会对静态成员变量进行初始话了
    }
    static int m_Age;//加入static就是静态成员变量，会共享数据
    //静态成员变量在类内声明，在类外进行初始化。
    
    private://静态成员变量也是有权限的
    static int m_high;
};
int Person::m_Age = 0;//类外初始化实现
int Person::m_high = 0;//类外可以初始化私有的静态成员变量，编译器认为此操作还是在类的内部。
//但是四有权限在类外不可访问
void test01()
{
    //通过对象访问属性
    Person p1;
    p1.m_Age = 10;
    Person p2;
    p2.m_Age = 20;
    cout<<"p1的年龄 "<<p1.m_Age<<endl;
    cout<<"p2的年龄 "<<p2.m_Age<<endl;//输出都是二十，静态成员变量所有对象共享
    
    //通过类名访问属性
    cout<<"通过类名访问Age "<<Person::m_Age<<endl;
}
```

### 静态成员函数

与静态成员变量类似，普通方法加上static变成静态成员函数。

**静态成员函数不可以访问普通变量 （存在逻辑上的问题），因为静态成员函数是所有对象共有的，当用其访问普通变量时，不知道应该访问的是那个对象的变量**

**普通成员函数可以访问静态方法（不存在逻辑上的问题）**

```c++
class Person{
  public:
    Person(){cout<<"默认构造函数"<<endl}
    static void func()//与静态成员变量类似，加static关键字
    {
        cout<<"静态方法"<<endl;
    }
    ~Person(){cout<<"默认析构函数"<<endl;}
};

void test01()
{
    Person p1;
    //通过对象访问
    p1.func();
    //通过类名访问
    Person::func();
}
```

### 静态成员实现单例模式

#### 单例模式的简介

单例模式是一种常用的软件设计模式。在他的核心结构中只包含一个被称为单例的特殊类。通过单例模式可以保证系统中**一个类只有一个实例而且该实例易于外界访问**，从而方便对实例个数的控制并节约系统资源。如果希望在系统中某个类的对象只能存在一个，单例模式就是最好的解决方案。

#### 单例模式案例

##### 主席案例

- 目的：巍峨了让类只有一个实例，实例不需要自己释放
- 将默认构造和拷贝构造私有化
- 内部维护一个对象指针
- 私有化唯一指针
- 对外提供getInstance方法来访问这个指针
- 保证类中只能实例化一个对象

```c++
#include<iostream>
using namespace std;

//创建主席类
class ChairMan
{
	//1、构造函数私有
public:
	static ChairMan* singleMan;
	~ChairMan(){}

private:
	ChairMan() { cout << "默认构造函数" << endl; }
};
//类外初始化静态成员变量
ChairMan* ChairMan::singleMan = new ChairMan;//在编译阶段就已经创建好了

void test01()
{
	ChairMan::singleMan;
	ChairMan::singleMan = NULL;//singleMan可以被干掉,因此应该将singleMan私有化，让外界无法直接访问
}

int main()
{
	cout << "main调用" << endl;
	test01();
}
```

**单例实现的完整流程：** 

```c++
#include<iostream>
using namespace std;

//创建主席类
class ChairMan
{
	//1、构造函数私有
public:
	//提供get方法获取主席实例    静态方法
	static ChairMan* getInstance() {//设置为静态方法可以通过类名来访问，保证只有一个对象
		return singleMan;
	}
	~ChairMan(){}

private:
	static ChairMan* singleMan;
	ChairMan(const ChairMan& man)
	{
		cout << "拷贝构造" << endl;
	}
	ChairMan() { cout << "默认构造函数" << endl; }
};
//类外初始化静态成员变量
ChairMan* ChairMan::singleMan = new ChairMan;//在编译阶段就已经创建好了

void test01()
{
	/*ChairMan::singleMan;
	ChairMan::singleMan = NULL;//singleMan可以被干掉*/
	ChairMan* man = ChairMan::getInstance();

	//拷贝构造创建一个新的主席对象    将拷贝构造私有化可解决此问题
	//ChairMan* man1 = new ChairMan(*man);//又创建了一个新的主席对象，只不过名字一样，但是地址不一样
}

int main()
{
	cout << "main调用" << endl;
	test01();
}
```

##### 打印机案例

公司只有一个打印机，所有员工使用这一个打印机

```c++
#include<iostream>
#include<string>
using namespace std;

class Printer
{
public:
	static Printer* getInstance()
	{
		return singlePrinter;
	}

	void printText(string text)
	{
		cout << text << endl;
		count++;
		cout << count;
	}

private:
	Printer() { count = 0; }//构造函数私有
	Printer(const Printer& p){}//拷贝构造私有

private:
	static Printer* singlePrinter;//类内声明，类外初始化
	int count;//打印机使用次数

};
Printer* Printer::singlePrinter = new Printer;

void test01()
{
	//拿到打印机
	Printer* printer = Printer::getInstance();
	printer->printText("hhhhh");
}

int main()
{
	test01();
}
```

### 成员变量和函数的存储

在C语言中，分开声明的，也就是说语言本身并没有支持**数据**和**函数**之间的关联性，我们把这种程序方法称为“程序性的”，由一组分布在各个以功能为导航的函数中的算法驱动。它们处理的是共同的外部数据。

C++实现了**封装**，那么数据（成员属性）和操作（成员函数）是什么样的呢？

**数据**和**处理数据的操作（函数）**是**分开存储**的

- C++中的**非静态数据成员**直接内含在类对象的内部，就像C中的struct一样
- 成员函数虽然内含在class声明之内，却不出现在对象中。
- 每一个非内联成员函数只会诞生一份函数实例

```c++
class Person{
    public:
    int m_A;//非静态成员变量，属于对象身上
    void func(){}//非静态成员函数不属于对象身上
    static int m_B;//静态成员变量也不属于对象身上
    static void func2(){}//静态成员函数不属于对象身上
    double m_C;//对象大小为16不是12——字节对齐 
};

void test01()
{
    cout<<"sizeof of(Person)"<<sizeof(Person)<<endl;
    //空类的大小为1 每个实例的对象都有独一无二的地址  char维护这个地址
}
```

### this指针基本使用

C++的数据和操作也是分开存储，并且每一个非内联成员函数只会诞生一份函数实例，也就是说多个同类型的对象会公用一块代码。

那么问题是：这一块代码是如何区分那个对象调用自己的呢？

**C++通过提供特殊的对象指针，this指针，解决上述问题。this指针指向被调用的成员函数所属的对象**

 ```c++
 class Person{
     public:
     void func(){}
 };
 
 void test02()
 {
     //this指针指向被调用的成员函数所属的对象
     Person p1;
     p1.func(/*&p1*/);//编译器会自动加入一个this指针  Person *this 传入到func中指向被调用的成员函数所属的对象。
     
     Person p2;
     p2.func();
 }
 ```

**this指针永远指向当前对象**

C++规定，this指针是自动隐含在对象成员函数内的一种指针，当一个对象被创建后，它的每一个成员函数都含有一个系统自动生成的隐含指针this，用以保存这个对象的地址，也就是说**虽然我们没有写上this指针，编译器在编译的时候也是会加上的**.因此this也称为**指向本对象的指针**，this指针并不是对象的一部分，不会影响sizeof的结果。

this指针是C++实现封装的一种机制，它将对象和该对象调用的成员函数连接在一起，在外部看来，每一个对象都拥有自己的函数成员。一般情况下，并不写this，而是让系统进行默认设置。

**this指针是一种隐含指针，他隐含于每个类的非静态成员函数中**。

**静态成员函数内部没有this指针，静态成员函数不能操作非静态成员变量**（不知道操作的是那个对象的成员变量）

**C++编译器对普通成员函数的内部处理**

```c++
//原代码
class Test{
  public:
    Test(int a){
        m_a = a;
    }
    int getA(){
        return m_a;
    }
    static void print(){
        cout<<"hello world"<<endl;
    }
    private:
    int m_a;
};

Test a;
a.getA();
Test::Print();


//编译器处理后
struct Test{
  int m_a;  
};
void Test_initialize(Test* pThis,int i)
{
    pThis->m_a = i;
}

int Test_getA(Test* pThis)
{
    return pThis->m_a;
}
void Test_print()
{
    cout<<"hello world"<<endl;
}
Test a;
Test_initialize(&a,10);
Test_getA(&a);
Test_print();
```

#### this指针的使用

- 当形参和成员变量同名时，可用this指针来区分
- 在类的静态成员函数中返回本身的对象，可使用return *this

```c++
class Person {
    public:
    Person(int age)//当形参和成员变量同名时，可用this指针来区分
    {
        this->age = age;
    }
    Person& PlusAge(Person& p)//若返回的不是引用，则会调用拷贝构造函数返回一个新的对象
    {
        this->age+=p.age;
        return *this;//返回对象本身
    }
    
    int age;
};

void test01()
{
 	Person p1(10);
    cout<<p1.age<<endl;
    Person p2(10);
    p1.PlusAge(p2).PlusAge(p2);//链式编程
    cout<<p1.age<<endl;
}
```

### 空指针访问成员函数

- 如果成员函数没有用到this，那么空指针可以直接访问
- 如果成员函数用到this指针，就要注意，可以加if判断。如果this为NULL就return

```c++
class Person
{
  public:
    void show()
    {
        cout<<"Person show"<<endl;
    }
    void showAge()
    {
        cout<<m_Age<<endl;
    }
    int m_Age;
};

void test01()
{
    Person *p = NULL;
    p->show();//空指针可以调用此方法
    p->showAge();//NULL ->m_Age 调用不了
}
```

### 常函数和常对象

- 常函数 void func() const {}
- 常函数 修饰是this指针 const Type* const this   不可以修改指针指向的值
- 常对象 在对象前加入const修饰
- 常对象不可以调用普通成员函数，只能调用常函数

 ```c++
 class Person{
   public:
     Person(){
         //构造中修改属性
         //Person *const this
         this->m_A = 0;
         this->m_B = 0;
     }
     void show() const //函数后面加const 常函数 不允许修改指针指向的值
     {
         cout<<m_A<<endl;
         cout<<m_B<<endl;
         
     }
     int m_A;
    mutable int m_B;//就算是常函数  还能修改 
 };
 
 void test01()
 {
     //常对象 不允许修改属性
     const Person p2;
     //p2.m_A = 100
     //常对象不可以调用普通的成员函数,因为普通的成员函数中可能包含对属性的修改操作
     //常对象只能调用常函数
     p2.show();
 }
 ```

### 友元函数

类的主要特点之一就是数据隐藏，即类的私有成员无法在类的外部(作用域之外)访问。但是，有时候需要在类的外部访问类的私有成员，怎么办？

解决方法就是使用**友元函数**，友元函数是一种特权函数，C++允许这个特权函数访问私有成员。

程序员可以把一个全局函数。某个类中的成员函数。甚至整个类声明为友元。

#### 全局函数做友元函数

```c++
class Building {
  friend void goodGay(Building* building);//声明goodGay函数为友元函数，可访问私有成员
  public:
  	Building()
    {
        this->m_SittingRoom = "客厅";
        this->m_BedRoom = "卧室";
    }
  public:
    string m_SittingRoom;//客厅
    
    private:
    string m_BedRoom;
};

void goodGay(Building* building)
{
    cout<<building->m_SittingRoom<<endl;
    cout<<building->m_BedRoom<<endl;//友元函数访问类的私有成员
}
```

#### 整个类做友元类

- 友元关系不能被继承
- 友元关系是单向的，类A是类B的朋友，但类B不一定是类A的朋友
- 友元关系不具有传递性。类B是类A的朋友，类C是类B的朋友，但类C不一定是类A的朋友

```c++
class goodGay{
  public:
    goodGay(){ building = new Building; }
    void visit()
    {
        cout<<this->building->m_SittingRoom<<endl;
        cout<<this->building->mBedRoom<<endl;//友元类访问私有成员
    }
  private:
    Building* building;
};

class Building{
    friend class goodGay;//类作为友元类
  public:
    Building()
    {
        this->m_SittingRoom = "客厅";
        this->m_BedRoom = "卧室";
    }
  
  public:
    string m_SittingRoom;//客厅
  private:
    string m_BedRoom;
};
```

#### 成员函数做友元函数

```c++
class goodGay{
  public:
    goodGay(){ building = new Building; }
    //只让visit1成为Building的友元而visit2不可以访问
    void visit1()
    {
        cout<<this->building->m_SittingRoom<<endl;
        cout<<this->building->mBedRoom<<endl;//友元类访问私有成员
    }
    void visit2()
    {
        cout<<this->building->m_SittingRoom<<endl;
        //cout<<this->building->mBedRoom<<endl;//友元类访问私有成员
    }
  private:
    Building* building;
};

class Building{
    //让类的一个成员函数成为友元函数
    friend void goodGay::visit1();
    
  public:
    Building()
    {
        this->m_SittingRoom = "客厅";
        this->m_BedRoom = "卧室";
    }
  
  public:
    string m_SittingRoom;//客厅
  private:
    string m_BedRoom;
};
```

### 数组的封装（实现一个数组）

源代码



### 运算符重载

运算符重载，就是对已有的运算符**重新进行定义**，赋予其另一种功能，以适应不同的数据类型。

**运算符重载只是一种语法上的方便，也就是它只是另一种函数调用的方式**

在C++中，可以定义一个处理类的新运算符。这种定义很像一个普通的函数定义，只是函数名字由关键字operator及其紧跟的运算符组成，差别仅此而已。它像任何其他函数一样也是一个函数，当编译器遇到适当的模式时，就会调用这个函数。

#### 加号运算符重载

```c++
class Person
{
    public:
    Person(int a,int b):m_A(a),m_B(b){}
    int m_A;
    int m_B;
    Person operator+(Person& p)//加号运算符重载 成员函数
    {
        Person tmp;
        tmp.m_A = this->m_A+p.m_A;
        tmp.m_B = this->m_B+p.m_B;
        return tmp;
    }
    Person plusPerson(Person& p)//普通的提供成员函数实现加法
    {
        Person tmp;
        tmp.m_A = this->m_A+p.m_A;
        tmp.m_B = this->m_B+p.m_B;
        return tmp;
    }
}

Person p1(1,1);
Person p2(1,1);
Person p3 = p1 + p2;
```

#### 左移运算符重载

- 重载左移运算符不可以写在成员函数中。
- 返回值为cout,类型为ostream
- 第一个参数为cout，类型为ostream

```c++
class Person
{
  public:
    friend ostream& operator<<(ostream &cout,Person &p1);
    Person(){};
    Person(int a,int b)
    {
        this->m_A = a;
        this->m_B = b;
    }
    //重载左移运算符不可以写到成员函数中
    //void operator<<(){}
    int m_A;
    int m_B;
};
//返回值为cout  若访问的属性为私有，则需要设置为类的友元函数
ostream& operator<<(ostream &cout,Person &p1)//第一个参数cout  第二个参数p1
{
    cout<<p1.m_A<<endl;
    cout<<p1.m_B<<endl;
    return cout;
}
void test()
{
    Person p1(10,10);
    cout<<p1<<endl;
}
```



