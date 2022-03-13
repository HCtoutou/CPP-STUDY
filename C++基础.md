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



#### const的内部链接与外部链接

c语言中const默认是外部链接，外部可见，即在整个工程文件中都可见。

C++中const默认是内部链接，外部不可见，只可在当前文件中可见



#### const的内存分配情况

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

- 目的：为了让类只有一个实例，实例不需要自己释放
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

#### 前置后置递增运算符重载

```c++
class MyInteger {
	friend ostream& operator<<(ostream& cout, MyInteger& m);
public:
	MyInteger() { num = 0; }

	//前置++
	MyInteger& operator++()
	{
		this->num++;
		return *this;
	}

	//后置++   用占位参数表示这个为后置运算符
	MyInteger operator++(int)//返回的是值
	{
		MyInteger tmp = *this;
		this->num++;
		return tmp;
	}
//private:
	int num;
};

ostream& operator<<(ostream& cout, MyInteger& m)
{
	cout << m.num;
	return cout;
}
```

 

#### 指针运算符重载(智能指针)

```c++
#include<iostream>

using namespace std;

class Person
{
public:
	Person(int age) {//有参构造函数
		this->m_Age = age;
	}

	void showAge()
	{
		cout << this->m_Age << endl;
	}
	~Person() { cout << "默认析构函数" << endl; }

	int m_Age;
};

//智能指针
//用来托管自定义类型的对象，让其自动释放
class smartPointer
{
public:
	smartPointer(Person* person)
	{
		this->person = person;
	}
	Person* operator->()//重载->运算符，返回的是指针
	{
		return this->person;
	}

	Person& operator*()//重载*运算符，返回的为引用
	{
		return *this->person;
	}

	~smartPointer()
	{
		cout << "智能指针析构函数" << endl;
		if (this->person != NULL)
		{
			delete this->person;
			this->person = NULL;
		}
	}

private:
	Person* person;
};

void test()
{
	//Person p1(10);//开辟到栈空间上，会自动调用析构函数
	/*Person* p2 = new Person(10);//开辟在堆上，需要调用delete主动释放
	delete p2;*/
	smartPointer sp(new Person(10));//sp开辟在栈空间上，会自动调用析构函数
	sp->showAge();  //sp->返回的是一个指针，应该sp->->showAge(),此处编译器进行了优化，因此只需写一次箭头
	(*sp).showAge();
}


int main()
{
	test();
}
```

#### 赋值运算符重载

- 系统默认给类提供赋值运算符写法，是简单值拷贝
- 导致如果类中有指向堆区的指针，就可能出现深浅拷贝问题
- 所以要重载 = 运算符
- 如果想链式编程 return*this

```c++
#include<iostream>
using namespace std;

class Person
{
public:
	Person(int a)
	{
		this->m_A = a;
	}

	int m_A;
};
class Person2
{
public:
	Person2(char * name)
	{
		this->m_Name = new char[strlen(name)+1];
		strcpy(this->m_Name, name);
		//this->m_Name = name;
	}
	//类中默认提供的 = 运算符只是简单的值拷贝
	//当涉及到堆空间的释放时会由于是浅拷贝而产生错误，因此需要进行=的重载
	Person2& operator=(const Person2& p)
	{
		if (this->m_Name != NULL)
		{
			delete[] this->m_Name;
			this->m_Name = NULL;
		}

		this->m_Name = new char[strlen(p.m_Name) + 1];
		strcpy(this->m_Name, p.m_Name);
		return *this;
	}

	~Person2()
	{
		cout << "Person2的析构函数" << endl;
		if (this->m_Name != NULL)
		{
			delete[] this->m_Name;
			this->m_Name = NULL;
		}
	}

	char* m_Name;
};
void test1()
{
	Person p1(10);

	Person p2 = p1;
	cout << p2.m_A << endl;
}

void test2()
{
	Person2 p1((char*)("狗蛋"));
	Person2 p2((char*)("狗剩"));
	cout << p2.m_Name << endl;
	Person2 p3((char*)(" "));
	p3 = p2 = p1;
	cout << p1.m_Name << endl;
	cout << p2.m_Name << endl;
	cout << p3.m_Name << endl;
}
int main()
{
	//test1();
	test2();
}
```

#### []运算符重载

- **返回引用，可以作为左值**

```c++
int& MyArray::operator[](int val)
{
	return this->pAddress[val];
}
```

#### 函数调用运算符重载()

```c++
class MyPrint
{
	public:
    void operator()()
    {
        cout<<"hello world"<<endl;
    }
};

void test01()
{
    MyPrint mtPrint;
    myPrint();//仿函数
}
```

#### 不要重载&&，||

不能重载&&和||的原因，无法在这两种情况下实现内置操作符的完整语义。说的具体一点，内置版本的特殊之处在于：内置版本的&&和||首先计算左边的表达式，如果这完全能够决定结果，就无需计算右边的表达式了，而且能保证不需要。我们都已经习惯了这种方便的特性了。

### 类的继承

  **降低代码的重复性**

```c++
//抽象一个基类的网页 重复的代码都写在这个上面
class BasePage  //父类 基类
{
    public:
    void header(){cout<<"公共头部"<<endl;}
    void footer(){cout<<"公共底部"<<endl;}
    void left(){cout<<"左侧列表"<<endl;}
};

//派生类  子类
class News :public BasePage  //继承，News类继承于 BasePage类
{
   public:
    void content(){cout<<"新闻播放"<<endl;}
}；
class Game :public BasePage
{
  cout<<"游戏内容"<<endl;  
};
```

#### 继承方式

**语法：**class 子类 ：继承方式 父类

三种继承方式： 不论是那种继承方式，父类的私有属性都不会被继承

- 公有继承 public
- 私有继承 private
- 保护继承 protected 

```c++
class A
{
    public:
    int a;
    protected:
    int b;
    private://私有属性不被继承
    int c;
};

class B:public A	//公有继承
{
    public:
    int a;
    protected:
    int b;
    不可访问:
    int c;
};

class B:protected A		//保护继承
{
    protected:
    int a;int b;
    不可访问:
    int c;
};

class B:private A	//私有继承
{
    private:
    int a;
    int b;
    不可访问:
    int c;
}
```

#### 继承中的对象模型

**子类会继承父类中的所有内容，包括私有属性，但是访问不到，编译器给隐藏起来了**

```c++
class Base
{
    public:
    int m_A;
    protected:
    int m_B;
    private:
    int m_C;
};
class Son:public Base
{
    public:
    int m_D;
};

//子类中 会继承父类的私有成员，只是被编译器给隐藏起来，访问不到私有成员
void test01()
{
    cout<<sizeof(Son)<<endl;//16
}
```

#### 继承中的构造和析构

**先调用父类的构造函数，之后调用自己的构造函数**

**析构时，先调用自己的析构函数，之后再调用父类的析构函数**

**子类会继承父类的成员属性，成员函数**

**但是子类不会继承父类的构造函数和析构函数**

**因为只有父类自己直到如何初始化自己的属性**

```c++
class Base
{
    public:
    Base(){cout<<"Base默认构造函数调用"<<endl;}
    ~Base(){cout<<"Base析构函数调用"<<endl;}
    
};

class Son:public Base
{
    public:
    Son(){cout<<"Son默认构造函数调用"<<endl;}
    ~Son(){cout<<"Son析构函数调用"<<endl;}
};
void test01()
{
    Son s1;
}
```

 #### 继承中的同名成员处理

- 如果子类和父类拥有同名的函数 属性，子类会覆盖父类的成员吗？  不会，只是隐藏起来了

**如果子类与父类的成员函数名称相同，子类回把父类的所有的同名版本都隐藏掉(重载的所有同名方法)**

要想通过子类调用父类的方法，必须加上作用域

```c++
class Base
{
    public:
    Base(){m_A = 100;}
    void fun()
    {
        cout<<"Base func"<<endl;
    }
    int m_A;
}

class Son:public Base
{
    public:
    Son(){m_A = 200;}
    void fun()
    {
        cout<<"Son func"<<endl;
    }
    int m_A;
}
void test01()
{
    Son s1;
    cout<<s1.m_A<<endl;//200
    //想调用父类中的m_A  加上作用域
    cout<<s1.Base::m_A<<endl;//100
    
    s1.func();//调用子类的func方法
    //调用父类的func方法
    s1.Base::func();//调用父类的func方法
}
```

#### 继承中静态成员的处理

类似于非静态成员的处理

```c++
class Base
{
    public:
    static void func(){cout<<"Base func"<<endl;}
    static int m_A;
};
int Base::m_A = 10;

class Son:public Base
{
    public:
    static void func(){cout<<"Son func"<<endl;}
    static int m_A;
};
int Son::m_A = 20;
void test01()
{
    //静态成员属性可以被继承下来
    cout<<Son::m_A<<endl;//20
    //访问父类的静态成员属性
    cout<Base::m_A<<endl;//10
    
    Son::func();
    Base::func();//父类
    Son::Base::func();//通过儿子找父亲
    
}
```

#### 多继承

##### 多继承的概念

我们可以从一个类继承，我们也可以能从多个类继承，这就是多继承。但是由于多继承是非常受争议的，从多个类继承可能会导致函数，变量等同名导致较多的歧义。   

```c++
class Base1 {
public:
    int m_A;
    Base1(){m_A = 10;}
	void func1() { cout << "Base1::func1" << endl; }
};
class Base2 {
public:
    int m_B;
    Base2(){m_B = 20;}
	void func1() { cout << "Base2::func1" << endl; }
};
class Son :public Base1, public Base2
{
public:
	int m_C;
    int m_D;
};
void test01()
{
	Son s;
	cout<<s1.m_A<<endl;//10
    //s1.func()//产生二义性，不直到应该调用谁的func方法
}
```

##### 菱形继承的问题以及解决方法

**问题：**

**会从不同的父类重复继承相同的属性，造成空间浪费。**

**利用虚继承解决**

**利用虚继承操作的是一份共享的数据**

```c++
class Animal
{
    public:
    int m_Age;
};
//虚基类
class Sheep:virtual public Animal
{
    
};
class Tuo:virtual public Animal
{
    
};
class SheepTuo:public Sheep,public Tuo
{
    
};
void test01()
{
    SheepTuo st;
    st.Sheep::m_Age = 10;
    st.Sheep::m_Age = 20;
}
```

##### 虚基类的内部工作原理

虚基类内部结构：

- vbptr：虚基类指针（virtual base pointer）
- 指向一张**虚基类表**
- 通过表找到偏移量
- 找到共有的数据

找到sheep的偏移量操作

```c++
void test02()
{
    SheepTuo st;
    st.m_Age = 100;
    //找到Sheep的偏移量操作
    cout<<*(int *)((int *)*(int *)&st + 1)<<endl;
    //找到Tuo的偏移量
    cout<<*((int *)((int *)*((int *)&st + 1) + 1))<<endl;
    //输出age
    cout<<((Animal*)((char*)&st + *(int *)((int*)*(int *)&st + 1 )))->m_Age<<endl;
}
```

### 多态

#### 多态的基本概念

多态是面向对象程序设计语言中数据抽象和继承之外的第三个基本特征。

多态性（polymorphism）**提供接口与具体实现之间的另一层隔离**，从而将what 和 how分离开来。多态性改善了代码的可读性和组织性，同时也使创建的程序具有可扩展性，项目不仅在最初创建时期可以扩展，而且当项目在需要有新的功能时也能扩展。

C++支持编译时多态（**静态多态**）和运行时多态（**动态多态**），运算符重载和函数重载就是编译时多态，而**派生类和虚函数实现运行时多态。**

静态多态和动态多态的区别就是函数地址是早绑定（静态联编）还是晚绑定（动态联编）。如果函数的调用，在编译阶段就可以确定函数的调用地址，并产生代码，就是静态多态（编译时多态），就是说地址是早绑定的。而如果函数的调用地址不能在编译期间确定，而需要在运行时才能决定，这就属于晚绑定（动态多态，运行时多态）

#### 多态的成立条件

- 有继承

- 子类重写父类虚函数

  a.返回值，函数名字，函数参数必须和父类完全一致（析构函数除外）

  b.子类中virtual关键字可写可不写，建议写

- 类型兼容，父类指针，父类引用指向子类对象

#### 静态联编和动态联编

```c++
class Animal{
  public:
    virtual void speak(){cout<<"动物在说话"<<endl;}//虚函数
};

class Cat:public Animal{
  public:
    void speak(){cout<<"Cat 在说话"<<endl;}
};

//调用doSpeak函数时，在编译阶段就已经绑定好了（早绑定），属于静态联编
void doSpeak (Animal& animal)
{
    animal.speak();
}
//如果想要调用猫的speak，那就不能提前绑定好地址了，所以需要在运行的时候再去确认函数地址
//动态联编 写法：speak改为虚函数，在父类上声明了虚函数(子类中可写可不写)，发生了多态
//什么是多态?  父类的引用或者指针 指向子类对象


//如果发生继承的关系，编译器允许进行类型转换
void test01()
{
    Cat cat;
    doSpeak(cat);//输出“动物在说话”，并不是“Cat 在说话”，在父类中加上虚函数，就发生了多态
}
```

#### 多态原理解析

```c++
//Animal内部结构
//不加virtual，sizeof(Animal) = 1,加上virtual，sizeof(Animal) = 4
//加上virtual后，Animal内部有个指针，叫 vfptr
//virtual function pointer 虚函数表指针
//这个指针指向 &Animal::speak()
class Animal
{
    public:
    virtual void speak(){cout<<"动物在说话"<<endl;}
}

//Cat内部结构
//会将上述的Animal的虚函数表指针继承下来
//在对象创建的时候（调用构造函数的时候），将所有的虚函数表指针都指向自己的虚函数表
//但是这个操作我们是看不到的 
class Cat:public Animal
{
   public:
    //子类写speak父类的虚函数，这种写法叫重写
    //重写就相当于把父类的方法重新写一遍（返回值，参数个数，类型，顺序都相同，其实现的具体内容不同 ）
    void speak(){cout<<"小猫在说话"<<endl;}
};
```

```c++
//寻找自己的方法
//父类指针指向子类对象
Animal *animal = new Cat;
//animal->speak();//直接调用子类的方法
///具体过程
//*(int*)*(int*)animal  函数的地址
((void(*)()) (*(int*)*(int*)animal))();
```

#### 多态案例—计算器案例

- 开发有原则 ，开闭原则——对扩展开放，对修改关闭
- 利用多态实现，有利于后期扩展，结构性非常好，可读性高，效率稍微低，发生多态时内部结构复杂。

```c++
#include<iostream>
using namespace std;
//开闭原则 ：对扩展开放，对修改关闭
class abstractCalculator
{
public:
	virtual int getResult() { return 0; }
	void setv1(int val) { val1 = val; }
	void setv2(int val) { val2 = val; }

	int val1;
	int val2;
};

class PlusCalculator :public abstractCalculator
{
public:
	int getResult()
	{
		return val1 + val2;
	}
};

class SubCalculator :public abstractCalculator
{
public:
	int getResult()
	{
		return val1 - val2;
	}
};

void test01()
{
	abstractCalculator* abc;
	abc = new PlusCalculator;//加法计算器
	abc->setv1(10);
	abc->setv2(20);
	cout << abc->getResult() << endl;
	delete abc;
	abc = new SubCalculator;//减法计算器
	abc->setv1(10);
	abc->setv2(20);
	cout << abc->getResult() << endl;

}
int main()
{
	test01();
}
```

#### 抽象类和纯虚函数

在设计时，常常希望基类仅仅作为其派生类的一个接口。这就是说，仅想对基类进行向上类型转换，使用它的接口，而不希望用户实际创建一个基类的对象。同时创建一个纯虚函数允许接口中放置成员原函数，而不一定要提供一段可能对这个函数毫无意义的代码。

做到这点，可以在基类中加入至少一个纯虚函数，使得基类称为抽象类：

- 纯虚函数使用关键字virtual，并在其后面加上=0。如果试图去实例化一个抽象类，编译器会阻止这种操作
- 当继承一个抽象类的时候，必须实现所有的纯虚函数，否则由抽象类派生的类也是抽象类
- virtual void func() = 0;告诉编译器在vtable中为函数保留一个位置，但在这个特定位置不放地址

**建立公共接口的目的是为了将子类的公共操作抽象出来，可以通过一个公共接口来操作一组类，且这个公共接口不需要事先实现，可以建立一个公共类。**

```c++
//如果父类中有了纯虚函数，那么子类继承父类，就必须实现纯虚函数
//如果父类中有了纯虚函数，那么这个父类就无法实例化对象
//这个类有了纯虚函数，通常这个类成为抽象类
virtual int getResult() = 0;//纯虚函数
```

#### 虚析构函数和纯虚析构函数

- 析构函数前面加关键字 virtual构成虚析构
- 解决通过父类指针指向子类对象释放不干净的问题。
- 纯虚析构函数类似于纯虚函数，类内声明，类外实现（因为父类的析构函数必须要调用，因此必须实现）
- 有纯虚析构函数的类也为抽象类，不能实例化对象

```c++
class Animal
{
  public:
    virtual void speak()
    {
        cout<<"动物在说话"<<endl;
    }
    //普通的析构不会调用子类的析构的，所以可能会导致释放不干净
    //利用虚析构来解决这个问题
    //virtual ~Animal()
    //{
    //    cout<<"Animal的析构调用"<<endl;
    //}
    
    //纯虚析构
    //纯虚析构，需要声明，还需要实现，类内声明，类外实现
    virtual ~Animal() = 0; 
};
Animal::~Animal()
{
    //纯虚析构函数的实现
    cout<<"Animal的纯虚析构调用"<<endl;
    //如果函数中出现了 纯虚析构函数，那么这个类也算抽象类  不能实例化对象
    //抽象类不可实例化对象
} 


class Cat:public Animal
{
    public:
    Cat(const char* name)
    {
        this->m_Name = new char[strlen(name)+1];
        strcpy(this->m_Name,name);
    }
    virtual void speak()
    {
        cout<<"小猫在说话"<<endl;
    }
    ~Cat()
    {
        cout<<"Cat的析构调用"<<endl;
        if(this->m_Name != NULL)
        {
            delete[] this->m_Name;
            this->m_Name = NULL;
        }
    }
    
    char *m_Name;
}

//虚析构
void test01()
{
    Animal* animal = new Cat("Tom");//父类的指针指向子类的对象
    animal->speak();
    delete animal;
}
```

### 向上类型转换和向下类型转换

- 主要取决于父类与子类的大小的关系

- 基类转派生类是向下类型转换，是不安全的，可能会越界
- 派生类转基类是向上类型转换，是安全的
- 如果发生多态，那么向上类型转换和向下类型转换总是安全的。

### 泛型编程

泛型编程（Generic Programming）最初提出时的动机很简单直接：发明一种语言机制，能够帮助实现一个通用的标准容器库。所谓通用的标准容器库，就是要能够做到，比如用一个[List](https://baike.baidu.com/item/List/4825101)类存放所有可能类型的对象这样的事；泛型编程让你编写完全一般化并可重复使用的算法，其效率与针对某特定数据类型而设计的算法相同。泛型即是指具有在多种数据类型上皆可操作的含义，与模板有些相似。STL巨大，而且可以扩充，它包含很多计算机基本算法和数据结构，而且将算法与数据结构完全分离，其中算法是泛型的，不与任何特定数据结构或对象类型系在一起。

### C++模板

#### 模板概论

C++提供了函数模板（function template），**所谓函数模板，实际上是建立一个通用函数，其函数类型和形参类型不具体制定，用一个虚拟的类型来代表。**这个通用函数就成为函数模板。凡是函数体相同的函数都可以用这个模板代替，不必定义多个函数，只需要在模板中定义一次即可。在调用函数时系统会自动根据实参的类型来取代模板中的虚拟类型，从而实现不同函数的功能。

- C++提供两种模板机制：函数模板和类模板
- 类属 - 类型参数化，又称参数模板

**总结：**

- 模板把函数或类要处理的数据类型参数化，表现为参数的多态性，称为类属。
- 模板用于表达逻辑结构相同，但具体数据元素类型不同的数据对象的通用行为。

#### 函数模板的基本使用

- template<class/typename T>  告诉编译器紧跟的代码里出现T不要报错
- 函数模板必须要能推导出T的类型  自动推导或显示指定

```c++
//参数类型不同，逻辑又十分相似
//类型参数化   泛型编程 --模板技术
template<class T> //告诉编译器，下面如果出现了T不要报错，T是一个通用类型
void Swap(T& a, T& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}
void test01()
{
	int a = 10;
	int b = 20;
	//自动类型推导 观察到啊a,b为int类型，自动把T换位int
	//必须有参数类型才能推到
	Swap(a, b);

	//显示指定类型
	Swap<int>(a, b);
	//模板必须要推出类型，否则指定出T
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
}
```

#### 函数模板与普通函数的区别以及调用规则

- C++编译器优先考虑普通函数
- 普通函数可以进行隐式类型转换，函数模板不可以🙅‍
- 可以通过空模板实参列表的语法限定编译器只能通过模板匹配
- 函数模板可以像普通函数那样重载
- 如果函数模板可以产生一个更好的匹配，那么会调用函数模板

```c++
template<class T>
T myPlus(T a, T b)
{
	return a + b;
}

int myPlus2(int a, int b)
{
	return a + b;
}

void test01()
{
	int a = 10;
	int b = 20;
	myPlus(a, b);
	myPlus2(a, b);
	char c = 'c';
	//myPlus(a, c);  不可调用 推到不出T的类型，不可进行隐士类型转换
	myPlus2(a, c);  //普通函数可以进行隐式类型转换
}


template<class T>
void myPrint(T a, T b)
{
	cout << "模板调用的myPrint" << endl;
}

template<class T>
void myPrint(T a, T b,T c)
{
	cout << "模板调用的myPrint<a,b,c>" << endl;
}

void myPrint(int a, int b)
{
	cout << "int调用的myPrint" << endl;
}
void test02()
{
	int a = 10;
	int b = 20;
	myPrint(a, b);//发生了函数重载 优先使用普通函数 若发生重载，但普通函数没有实现，就会报错
	myPrint<>(a, b);//加入一个空参数列表  调用模板
	//函数模板可以发生重载
	int c = 30;
	myPrint(a, b, c);

	//如果函数模板可以产生更好的匹配，那么优先调用函数模板
	char m = 'm';
	char n = 'n';
	myPrint(m, n);//调用函数模板
}
```

#### 模板机制剖析

- 编译器并不是把函数模板处理成能够处理任何类型数据的函数
- 函数模板通过具体类型产生不同的函数
- 编译器会对函数模板进行**两次编译**，在声明的地方对模板代码本身进行编译，在调用的地方对参数替换后的代码进行编译。

#### 函数模板的局限性

- 模板不能解决所有的类型
- 如果出现不能解决的类型，可以通过第三代具体化来解决问题

```c++
class Person
{
public:
	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	string m_Name;
	int m_Age;
};
template<class T>
bool myCompare(T& a,T& b)
{
	if (a == b)
		return true;
	else
		return false;
}

//通过具体化自定义数据类型，解决上述问题
//如果具体化能够优先匹配  那么就选择具体化
//语法 template<> bool myCompare<Person>(Person& a,Person& b)
template<> bool myCompare<Person>(Person& a, Person& b)
{
	if (a.m_Age == b.m_Age)
		return true;
	else
		return false;
}
void test01()
{
	int a = 10;
	int b = 20;
	int res = myCompare(a, b);
	cout << "res =" << res << endl;
	Person p1("Tom", 10);
	Person p2("Jerry", 20);
	int res2 = myCompare(p1, p2);
}
```

#### 类模板

- 与函数模板类似，下面跟的类
- 类模板可以有默认参数，函数模板不行
- 类模板不可以进行自动类型推导，函数模板可以

```c++
template <class NameType,class AgeType> //类模板可以有默认类型，函数模板不行
class Person
{
public:
	Person(NameType name, AgeType age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	void showPerson()
	{
		cout << this->m_Name << endl;
		cout << this->m_Age << endl;
	}
	NameType m_Name;
	AgeType m_Age;
};

void test01()
{
	//自动类型推导 类模板不支持
	//Person p("孙悟空", 10);
	Person<string, int> p("孙悟空", 10000);
	p.showPerson();
}
```

#### 成员函数的创建时机

- 类模板中，成员函数一开始不会创建出来，而是运行时候创建出来的

```c++
class Person1
{
public:
	void showPerson1()
	{
		cout << "Person1的调用" << endl;
	}
};

class Person2
{
public:
	void showPerson2()
	{
		cout << "Person2的调用" << endl;
	}
};

template<class T>
class myClass
{
public:
	T obj;
	void func1()
	{
		obj.showperson1();
	}
	void func2()
	{
		obj.showperson2();
	}
};

//成员函数一开始不会创建出来，而是运行时候创建出来的
void test01()
{
	myClass<Person1> m;
	m.func1();
}
```

#### 类模板做函数的参数

```c++
template <class NameType, class AgeType> //类模板可以有默认类型，函数模板不行
class Person
{
public:
	Person(NameType name, AgeType age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	void showPerson()
	{
		cout << this->m_Name << endl;
		cout << this->m_Age << endl;
	}
	NameType m_Name;
	AgeType m_Age;
};
//1、指定传入类型
void doWork(Person<string, int>& p)
{
	p.showPerson();
}

//2、参数模板化
template<class T1,class T2>
void doWork2(Person<T1, T2>& p)
{
	//如何查看类型
	cout << typeid(T1).name(); << endl;
	cout << typeid(T2).name(); << endl;
	p.showPerson();
}
//3、整体类型化 
template<class T>
void doWork3(T& p)
{
	p.showPerson();
}
```

#### 类模板碰到继承问题以及解决

- 基类如果是模板类，必须让子类告诉编译器基类中的模板是什么类型，否则无法分配内存
- 利用参数列表来解决。

```c++
template<class T>
class Base
{
public:
	T m_A;
};

//Child继承Base必须告诉Base中的T的类型，否则T无法分配内存
class Child :public Base<int>
{

};
template<class T1,class T2>
class Child2 :public Base<T2>
{
public:
	T1 m_B;
};
```

#### 类模板的类外实现成员函数

```c++
template<class T1,class T2>
class Person
{
public:
	Person(T1 name, T2 age);
	void showPerson();

	T1 m_Name;
	T2 m_Age;
};

//类外实现成员函数
template<class T1,class T2>
Person<T1, T2>::Person(T1 name, T2 age)
{
	this->m_Name = name;
	this->m_Age = age;
}
template<class T1,class T2>
void Person<T1, T2>::showPerson()
{
	cout << this->m_Name << this->m_Age << endl;
}
```

#### 友元碰到类模板

##### 类内实现

```c++
template<class T1,class T2>
class Person
{
	//友元函数类内实现
	friend void printfPerson(Person<T1,T2>& p)
	{
		cout << p.m_Name << p.m_Age << endl;
	}
public:
	Person(T1 name, T2 age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}
private:
	T1 m_Name;
	T2 m_Age;
};
```

##### 类外实现

```c++
//让编译器看到Person声明
template<class T1, class T2> class Person;
//让编译器看到printfPerson的声明
template<class T1,class T2> void printfPerson(Person<T1, T2>& p);

template<class T1,class T2>
class Person
{
	//友元函数类外实现
	//friend void printfPerson(Person<T1, T2>& p);//这是一个普通函数的声明
	//当有普通函数和模板函数的时候，优先匹配普通函数
	//利用空参数列表 告诉编译器 这是模板函数的声明
	friend void printfPerson<>(Person<T1, T2>& p);
public:
	Person(T1 name, T2 age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}
private:
	T1 m_Name;
	T2 m_Age;
};
template<class T1,class T2>
void printfPerson(Person<T1, T2>& p)
{
	cout << p.m_Name << p.m_Age << endl;
}
```

### C++类型转换

类型转换（cast）是将一种数据类型转换成另一种数据类型。例如，如果将一个整型值赋给一个浮点类型的变量，编译器会暗地里将其转换成浮点类型

转换是非常有用的，但是它也会带来一些问题，比如在转换指针时，我们很可能将其转换成一个比他更大的类型，但这可能会破坏其他的数据。

**一般情况下，尽量少的去使用类型转换，除非用来解决非常特殊的问题**

标准C++提供了一个显示的转换的语法，来代替旧的C风格的类型转换

Q：使用C风格的强制转换可以把想要的任何东西转换成我们需要的类型，那为什么还需要一个新的C++类型的强制转换呢？

A：新类型的强制转换可以提供更好的控制强制转换过程，允许控制各种不同种类的强制转换。C++风格的强制转换其他的好处是，它们能更清晰的表明它们要干什么。程序员只要扫一眼这样的代码，就能立即直到一个强制转换的目的

#### 静态转换

- 用于类层次结构中基类和派生类之间指针或引用的转换
  - 进行上行转换（把派生类的指针或引用转换成基类表示）是安全的
  - 进行下行转换（把基类的指针或引用转换成派生类表示），由于没有动态类型检查。所以是不安全的。
- 用于基类数据类型之间的转换，如把int转换成char，把char转换成int。这种转换的安全性也要开发人员来保证。

```c++
//静态转化
//基础类型
void test01()
{
	char a = 'a';
	double d = static_cast<double>(a);
	cout << d << endl;
}
class Base{};
class Child:public Base{};
class Other{};
void test02()
{
	Base* base = NULL;
	Child* child = NULL;

	//把Base转为Chid 向下不安全
	Child* child2 = static_cast<Child*>(base);

	//把Child转为Base 向上安全
	Base* base2 = static_cast<Base*>(child);

	//转Other 转换无效
	//Other* other = static_cast<Other*>(Base);
}
```

#### 动态转换（dynamic_cast）

- dynamic_cast主要用于类层次间的上行转换和下行转换
- 在类层次间进行上行转换时，dynamic_cast和static_cast的效果是一样的
- 在进行下行转换时，dynamic_cast具有类型检查的功能，比static_cast更安全

```c++
void test01()
{
	//基础类型不可以转换
	//char c = 'a';
	//dynamic_cast非常严格，失去精度 或者不安全都不可以转换
	//double d = dynamic_cast<double>(c);
}

class Base{};
class Child:public Base{};
class Other{};
void test02()
{
	Base* base = NULL;
	Child* child = NULL;
	//child转base  安全
	Base* base2 = dynamic_cast<Base*>(child);

	//base转为child  不安全
	//Child* child2 = dynamic_cast<Child*>(base);
}
//dynamic_cast如果发生了多态，那么可以让基类转为派生类，向下转换
class Base1 {
	virtual void func()
	{

	}
};
class Child1 :public Base1 {
	virtual void func()
	{}
};

void test03()
{
	//发生多态情况   父类指针或引用指向子类对象
	Base1* base = new Child1;
	Child1* child = dynamic_cast<Child1*>(base);
}
```

#### 常量转换（const_cast）

const_cast 运算符来修改const属性

- 常量指针被转化成非常量指针，并且仍然指向原来的对象
- 常量引用被转换成非常量引用，并且仍然指向原来的对象

**注意：不能直接对非指针和非引用的变量使用const_cast操作符去直接移除它的const**

```c++
void test01()
{
	const int* p = NULL;
	//去除const
	int* newp = const_cast<int*>(p);

	int* p2 = NULL;
	const int* newp2 = const_cast<const int*>(p2);

	//不能对非指针 或 非引用的变量进行转换
	const int a = 10;
	//int b = const_cast<int>(a);

	//引用
	int num = 10;
	int& numRef = num;
	const int& numRef2 = const_cast<const int&>(numRef);
}
```

### C++中的异常处理

#### 异常处理的基本使用

在C语言的世界里，对错误的处理总是围绕两种方法：一种是使用整形的返回值标识错误；二是使用errno宏（可以简单的理解为一个全局整型变量）去记录错误。当然C++中仍然是可以用这两种方法的。

这两种方法最大的缺陷就是会出现不一致问题。例如有些函数返回1表示成功，返回0表示出错；而有些函数返回0表示成功，返回非0表示出错。

还有一个缺点就是函数的返回值只有一个，你通过函数的返回值表示错误代码，那么函数就不能返回其他的值。当然，你也可以通过指针或者C++的引用来返回另外的值，但是这样可能会令你的程序晦涩难懂。

**C++异常机制相比C语言异常处理的优势**

- 函数返回值可以忽略，但异常不可以忽略。如果程序出现异常，但是没有被捕获，程序就会终止，这多少会促使程序员开发出来的程序更健壮一点。而如果使用C语言的error宏或者返回值，调用者都有可能忘记检查，从而没有对错误进行处理，结果造成程序莫名的终止或出现错误的结果。
- 整型返回值没有任何语义信息。而异常却包含语义信息，有时你从类名就能够体现出来。
- 整型返回值缺乏相关的上下文信息。异常作为一个类，可以拥有自己的成员，这些成员就可以传递足够的信息。
- 异常处理可以在调用跳级。这是一个代码编写时的问题：假设在有多个函数的调用栈中出现了某个错误，使用整型返回码要求你在每一级函数中都要进行处理。而使用异常处理的栈展开机制，只需要在一处进行处理就可以了，不需要每级函数都处理。

```c++
int myDevide(int a,int b)
{
	if (b == 0)
	{
		//如果b是异常，抛出异常
		throw -1;
		//return -1;原来C语言的处理方式
	}
	return a / b;
}

void test01()
{
	int a = 10;
	int b = 0;

	//C++中异常处理
	try
	{
		myDevide(a, b);
	}
	catch (int) //捕获异常
	{
		throw;//如果不想处理这个异常可继续向上抛出
		cout << "int类型异常捕获" << endl;
	}
	catch (...)
	{
		cout << "其他类型异常捕获" << endl;
	}
}

int main()
{
	try {
		test01();
	}
	catch (int)//如果异常都没有处理，那么成员terminate函数，使程序中断。
	{
		cout << "main中的int异常处理" << endl;
	}
	return 0;
}
```

#### 对自定义异常进行捕获

```c++
class myException //自定义异常类
{
public:
	void printError()
	{
		cout << "自定义异常" << endl;
	}
};

int myDevide(int a,int b)
{
	if (b == 0)
	{
		throw myException(); //匿名对象
	}
	return a / b;
}

void test01()
{
	int a = 10;
	int b = 0;

	//C++中异常处理
	try
	{
		myDevide(a, b);
	}
	catch (int) //捕获异常
	{
		throw;//如果不想处理这个异常可继续向上抛出
		cout << "int类型异常捕获" << endl;
	}
	catch (myException e)
	{
		e.printError();
	}
	catch (...)
	{
		cout << "其他类型异常捕获" << endl;
	}
}
```

#### 栈解旋

**异常被抛出后，从进入try块起，到异常被抛弃前，在这期间在栈上构造的所有对象，都会被自动析构，析构的顺序与构造的顺序相反，这一过程称为栈的解旋**

#### 异常的接口声明 

- 为了加强程序的可读性，可以在函数声明中列出可能抛出异常的所有类型，例如：

  ```
  void func() throw(A,B,C);
  ```

  这个函数func能够且只能抛出类型A,B,C及其子类型的异常。

- 如果在函数声明中没有包含异常接口声明，则此函数可以抛任何类型的异常，例如void func()

- 一个不抛任何类型异常的函数可声明为：void func() throw()

- 如果一个函数抛出了它的异常接口声明所不允许抛出的异常，unexcepted函数会被调用，该函数默认行为调用terminate函数中断程序。

#### 异常变量的生命周期

- throw的异常是有类型的，可以是数字，字符串，类对象
- throw的异常是有类型的，catch需要严格匹配异常类型
- 如果 MyException e，会多开销一份数据，调用拷贝构造
- 如果 MyException *e，不new，会提前释放对象，new要自己管理delete

```c++
class MyException {
public:
	MyException() { cout << "默认构造函数" << endl; }
	MyException(const MyException& e) { cout << "拷贝构造函数" << endl; }

	~MyException() { cout << "析构函数" << endl; }
};

void doWork()
{
	throw MyException();
	//throw new MyException();
}

void test01()
{ 
	try
	{
		doWork();
	}
	catch (MyException &e) // MyException e,会多开销一份数据 可以加上引用
	{
		cout << "捕获异常" << endl;
	}
	/*catch (MyException* e)
	{
		cout << "指针类型异常捕获" << endl;
		delete e;
	}*/
}
```

#### 异常的多态使用

- 利用多态来实现 printfError同一个接口调用
- 抛出不同的错误对象

 ```c++
 class BaseException
 {
 public:
 	virtual void printError(){}
 };
 
 class NullPointerException :public BaseException
 {
 public:
 	virtual void printError()
 	{
 		cout << "空指针异常" << endl;
 	}
 };
 
 class OutofRangeException :public BaseException
 {
 public:
 	virtual void printError()
 	{
 		cout << "越界异常" << endl;
 	}
 };
 
 void doWork()
 {
 	//throw NullPointerException();
 	throw OutofRangeException();
 }
 
 void test01() {
 	try
 	{
 		doWork();
 	}
 	catch (BaseException& e) // 用引用节省开销
 	{
 		e.printError();
 	}
 }
 ```

#### 使用系统标准异常

- 使用系统标准异常需要包含头文件 #include\<stdexcept\>

```c++
class Person
{
public:
	Person(string name,int age)
	{
		if (age < 0 || age>200)
		{
			throw out_of_range("年龄越界");
		}
		this->m_Age = age;
		this->m_Name = name;
	}

	string m_Name;
	int m_Age;
};
void test01()
{
	try
	{
		Person p("张三",300);
	}
	catch (out_of_range& e)
	{
		cout << e.what();
	}
}
```

### C++输入和输出流

#### 流的概念和流类库的结构

程序的输入指的是从输入文件将数据传送给程序，程序的输出指的是从程序将数据传送给输出文件。

C++输入输出包含以下三个方面的内容：

- 对系统指定的标准设备的输入和输出。即从键盘输入数据，输出到显示器屏幕，这种输入输出称为标准的输入输出，简称I/O。
- 以外存磁盘文件为对象进行输入输出，即从磁盘文件输入数据，数据输出到磁盘文件。以外存文件为对象的输入输出称为文件的输入输出，简称文件I/O。
- 对内存中指定的空间进行输入和输出。通常指定一个字符数组作为存储空间（实际上可以利用该空间存储任何信息）。这种输入和输出称为字符串输入输出，简称串I/O。

C++编译系统提供了用于输入输出的iostream类库。iostream这个单词是由三个部分组成的，即i-o-stream,意为输入输出流。在iostream类库中包含许多用于输入输出的类。

#### 标准输入流

cin是有缓冲区的，会将键盘的输入先放在缓冲区。

```c++
cin.get() // 一次只能读取一个字符
cin.get(一个参数) // 读一个字符
cin.get(两个参数) // 可以读字符串
cin.getline()
cin.ignore()
cin.peek()
cin.putback()
```

#### 标准输出流

```c++
cout.flush() // 刷新缓冲区 Linux下有效
cout.put() // 向缓冲区写字符
cout.write() // 从buffer中写num个字节到当前输出流中
```

### 文件读写

和文件有关系的输入输出类主要在fstream.h这个头文件中被定义，在这个头文件中主要被定义了三个类，由这三个类控制对文件的各种输入输出操作，它们分别是ifstream，ofstream，fstream，其中fstream类是由iostream类派生而来的。

```c++
#include<fstream> // 包含有关文件读写的头文件

// 写文件
void test01()
{
	// 以输出的方式打开文件
	ofstream ofs("./test.txt", ios::out | ios::trunc);
	if (!ofs.is_open())
		cout << "打开失败" << endl;

	ofs << "姓名：何炜" << endl;
	ofs << "年龄：100" << endl;
	ofs << "身高：180cm" << endl;

	ofs.close();

}

// 读文件
void test02()
{
	ifstream ifs;
	ifs.open("./test.txt", ios::in);

	// 判断是否打开成功
	if (!ifs.is_open())
		cout << "打开失败" << endl;

	/*char buf[1024];
	while (ifs >> buf) // 按行读
	{
		cout << buf << endl;
	}*/

	/*char buf[1024];
	while (!ifs.eof()) // eof读到文件的尾部
	{
		ifs.getline(buf, sizeof(buf));
		cout << buf << endl;
	}*/

	char c;
	while (c = ifs.get() != EOF) // EOF文件尾
	{
		cout << c;
	}
	ifs.close();
}
```

