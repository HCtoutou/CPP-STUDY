### STL概论

长久以来，软件界一直希望建立一种可重复利用的东西，以及一种得以制造出“可重复运用的东西”的方法，让程序员的心血不止于随时间的迁移，人事异动而烟消云散，从函数(function),类别(classes),库函数(function libraries),类别库(class libraries),各种组件，从模块化设计，到面向对象(object oriented),为的就是复用性的提升。

复用性必须建立在某种标准之上，但是在许多环境下，就连软件开发最基本的数据结构和算法都未能有一套标准。大量程序员被迫从事大量重复的工作，竟然是为了完成前人已经完成而自己手上并未拥有的程序代码，这不仅是人力资源的浪费，也是挫折与痛苦的来源。

为了建立数据结构和算法的一套标准，并且降低它们之间的耦合关系，以提升各自的独立性，弹性，交互操作性，诞生了STL。

#### STL基本概念

STL(Standard Template Library,标准模板库)，是惠普实验室开发的一系列软件的统称。现在主要出现在C++中，但是在引入C++之前该技术已经存在很长时间了。

STL从广义上分为：容器(container)，算法(algorithm)，迭代器(iterator),容器和算法之间通过迭代器进行无缝连接。STL几乎所有的代码都采用了模板类或者模板函数，这相比传统的由函数和类组成的库来说提供了更好的代码重用机会。STL标准模板库，在我们C++标准程序库中隶属于STL的占到80%以上

#### STL六大组件简介

STL提供了六大组件，彼此之间可以组合套用，这六大组件分别是：**容器，算法，迭代器，仿函数，适配器（配接器），空间配置器。**

**容器：**各种数据结构，如vector，list，deque，set，map等，用来存放数据，从实现角度来看STL容器是一种class template。

**算法：**各种常用的算法，如sort，find，copy，for_each。从实现角度来看，STL算法是一种function template。

**迭代器：**扮演了容器与算法之间的胶合剂，共有五种类型，从实现角度来看，迭代器是一种将operate\*,operate->,operate++,operate--等指针相关操作予以重载的class template。所有STL容器都附带有自己专属的迭代器，只有容器的设计者才知道如何遍历自己的元素。原生指针（native pointer）也是一种迭代器。

**仿函数：**行为类似函数，可作为算法的某种策略。从实现角度来看，仿函数是一种重载了operate()的class或者class template。

 **适配器：**一种用来修饰容器或者仿函数或迭代器接口的东西

**空间配置器：**负责空间的配置与管理。从实现角度看，配置器是一个实现了动态空间配置，空间管理，空间释放的class template。

 **STL六大组件的交互关系，容器通过空间配置器取得数据存储空间，算法通过迭代器存储容器中的内容，仿函数可以协助算法完成不同的策略的变化，适配器可以修饰仿函数**

#### STL优点

- STL是C++的一部分，因此不用额外安装什么，它被内建在你的编译器之内。

- STL的一个重要特性是将数据和操作分离。数据由容器类别加以管理，操作则由可定制的算法定义。迭代器在两者之间充当“粘合剂”，以使算法可以和容器交互运作。

- 程序员可以不用思考STL具体的实现过程，只要能够熟练的使用STL就ok了。这样它们就可以把精力放在程序开发的别的方面。

- STL具有高可重用性，高性能，高移植性，跨平台的优点

  **高可重用性：**STL中几乎所有的代码都采用了模板类和模板函数的方式来实现，这相比于传统的由函数和类组成的库来说提供了更好的代码重用机会。

  **高性能：**如map可以高效的从十万条记录里面查找出指定的记录，因为map是采用红黑树的变体实现的。

  **高移植性：**如在项目A上用STL编写的模块，可以直接移植到项目B上。

### 三大组件的基本使用

- 容器
- 算法
- 迭代器（每个容器有专属的迭代器）

```c++
// 迭代器 遍历功能 用指针理解
void test01()
{
	int array[5] = { 1,2,3,4,5 };
	int* p = array; // 指针指向数组的首地址
	for (int i = 0; i < 5; i++)
		//cout << array[i] << endl;
		cout << *(p++) << endl; // 普通指针也算是一种迭代器
}

// 容器 vector
#include<vector>

void myPrint(int v)
{
	cout << v << endl;
}
void test02()
{
	vector<int> v; // 声明一个容器，这个容器中存放int类型数据
	// 向容器中加入数据
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	// 遍历容器中的数据（利用迭代器）
	// 声明迭代器
	vector<int>::iterator itBegin = v.begin(); // itBegin指向容器v的起始位置
	//vector<int>::iterator itEnd = v.end(); // itEnd指向v容器中最后一个位置的下一个地址
	
	/* 一种遍历方式，并不常用，通常使用for循环来遍历
	while (itBegin != itEnd)
		cout << *(itBegin++) << endl;*/
	// 第二种遍历for循环
	/*for (; itBegin != v.end(); itBegin++)
		cout << *itBegin << endl; */
	// 第三种方式 利用算法
	for_each(v.begin(), v.end(), myPrint);
}

// 操作自定义的数据类型
class Person
{
public:
	Person(string name, int age)
	{
		m_Name = name;
		m_Age = age;
	}

	string m_Name;
	int m_Age;
};
void test03()
{
	vector<Person> v;
	Person p1("大头",10);
	Person p2("小头",30);
	Person p3("小猫", 12); 
	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
		cout << (*it).m_Name << " " << it->m_Age << endl;
}

// 存放自定义数据类型的指针
void test04()
{
	vector<Person*> v;
	Person p1("大头", 10);
	Person p2("小头", 30);
	Person p3("小猫", 12);
	v.push_back(&p1);
	v.push_back(&p2);
	v.push_back(&p3);
	for (vector<Person*>::iterator it = v.begin(); it != v.end(); it++)
		cout << (*it)->m_Name << " " << (*(*it)).m_Age << endl;
}

// 容器嵌套容器
void test05()
{
	vector<vector<int>> v;
	vector<int> v1;
	vector<int> v2;
	vector<int> v3;
	for (int i = 0; i < 5; i++)
	{
		v1.push_back(i);
		v2.push_back(i+10);
		v3.push_back(i+100);
	}

	v.push_back(v1);
	v.push_back(v2);
	v.push_back(v3);
	// 从容器中遍历所有数据
	for (vector<vector<int>>::iterator it = v.begin(); it != v.end(); it++)
		for (vector<int>::iterator vit = (*it).begin(); vit != (*it).end(); vit++)
			cout << (*vit) << endl;

}
```

### string容器

 C风格字符串（以空字符结尾的字符数组）太过复杂难以掌握，不适合大程序的开发，所以C++标准库定义了一种string类，定义在头文件\<string\>。

string 和 c 风格字符串对比：

- char*是一个指针，string是一个类

  string封装了char\*，管理这个字符串，是一个char\*型的容器。

- string封装了很多实用的成员方法

  查找find，拷贝copy，删除delete，替换replace，插入insert

- 不用考虑内存释放和越界

  string管理char*所分配的内存。每一次string的复制，取值都由string类负责维护，不用担心复制越界和取值越界等。

#### string容器的API

##### string容器 构造 赋值

  ```c++
  /*
  string 构造函数
  string(); // 创建一个空的字符串
  string(const string& str); // 使用一个string对象初始化另外一个string对象
  string(const char* s); // 使用字符串s初始化
  string(int n,char c); // 使用n个字符初始化
  
  string基本赋值操作
  stirng& operator=(const char* s); // char*类型字符串赋值给当前的字符串
  string& operator=(const string s); // 把字符串s赋给当前的字符串
  string& operator=(char c); // 字符赋值给当前的字符串
  string& assign(const char* s); // 把字符串s赋给当前的字符串
  string& assign(const char* s,int n); // 把字符串s的前n个字符赋给当前的字符串
  string& assign(const string& s); // 把字符串s赋给当前字符串
  string& assign(int n,char c); // 用n个字符c赋给当前的字符串
  string& assign(const string& s,int start,int n); // 将s从start开始n个字符赋值给字符串
  /*
  ```

  ```c++
  void test01()
  {
  	string str; // 默认构造
  	string str2(str); // 拷贝构造
  	string str3 = str;
  	string str4 = "abcd";
  	string str5(10, 'a');
  
  	// 基本赋值
  	str = "hello";
  	str2 = str4; 
  }
  ```

##### string存取字符串

```c++
/*
string存取字符串
char& operator[](int n); // 通过[]方式取字符
char& at(int n); // 通过at获取字符
*/
```

```c++
void test01()
{
    string s = "hello world";
    for(int i = 0; i < s.size(); i++)
    {
        //cout<<s[i]<<endl;
        cout<<s.at[i]<<endl;
        // []和at的区别? []访问越界，会直接挂掉 at则会抛出异常
    }
}
```

##### string拼接操作

```c++
/*
string& operator+=(const string& str); // 重载+=操作符
string& operator+=(const char* str); 
string& operator+=(const char c);

string& append(const char* s); // 把字符串s连接到当前字符串结尾
string& append(const char* s,int n); // 把字符串s的前n个字符连接到当前字符串结尾
string& append(const string& s);
string& append(const string& s,int pos,int n); // 把字符串s中从pos开始的n个字符连接到当前字符串结尾
stirng& append(int n,char c); // 在当前字符串结尾添加n个字符c
```

##### string查找和替换

```c++
//查找找不到返回-1，找到了返回下标 

int find(const string& str,int pos = 0) const; // 查找str第一次出现位置，从pos开始查找
int find(const char* s,int pos = 0) const; // 查找s第一次出现位置，从pos开始查找
int find(const char* s,int pos,int n) const; // 从pos位置查找s的前n个字符第一次位置
int find(const char c,int pos = 0) const; // 查找字符c第一次出现的位置

int rfind(const string& str,int pos = npos) const; // 查找str最后一次位置，从pos开始找
int rfind(const char* s,int pos = npos) const; // 查早s最后一次出现的位置，从pos开始找
int rfind(const char* s,int pos,int n) const; // 从pos查找s的前n个字符最后一次位置
int rfind(const char c,int pos = 0) const; // 查找字符c最后一次出现的位置
string& replace(int pos,int n,const string& str); // 替换从pos开始n个字符为字符串str
string& replace(int pos,int n,const char* s);
```

##### string比较操作

```c++
/*
compare函数在>时返回1，<时返回-1，==时返回0.
比较区分大小写，比较时参考字典顺序，排越前面的越小
*/
int compare(const string& s) const; // 与字符串s比较
int compare(const char* s) const; // 与字符串s比较
```

##### string子串

```c++
string substr(int pos = 0,int n = npos) const; // 返回由pos开始的n个字符组成的字符串
```

##### string插入和删除操作 

```c++
string& insert(int pos,const char* s); // 插入字符串
string& insert(int pos,const string& str); // 插入字符串
string& insert(int pos,int n,char c); // 在指定位置插入n个字符c
string& erase(int pos,int n = npos); // 删除从pos开始的n个字符
```

#### string和c-style字符串转换

在c++中存在一个中存在一个从const char*到string的隐式类型转换，却不存在从一个string对象到C_string的自动类型转换。对于string类型的字符串，可以通过c_str()函数返回string对象对应的C_string

通常程序员在整个程序中应坚持使用string类对象，直到必须将内容转化为char*时才将其转化为C_string.

```c++
// string 转 char
string str = "itcast";
const char* cstr = str.c_str(); //转const char*
//char* 转 string
char* s = "itcast";
string str(s);
```

**为了修改string字符串的内容，下标操作符[]和at都会返回字符的引用。但是当字符串的内存被重新分配之后，可能发生错误**

```c++
string s = "abcdefg";
char& a = s[2];
char& b = s[3];

a = '1';
b = '2';
cout<<s<<endl;
cout<<(int*)s.c_str()<<endl;

s = "pppppppppppppppp";

a = '1';
b = '2';

cout<<s<<endl;
cout<<(int*)s.c_str()<<endl;
```

### vector容器

vector的数据安排以及操作方式，与array非常相似，两者的唯一差别在于空间的运用的灵活性。array是静态空间，一旦配置了就不能改变，要换大一点或者小一点的空间，可以，一切琐碎得由自己来，首先配置一块新的空间，然后将旧空间的数据搬往新空间，再释放原来的空间。vector是动态空间，随着元素的放入，它的内部机制会自动扩充空间以容纳新元素。因此vector的运用对于内存的合理利用与运用的灵活性有很大的帮助，我们再也不必害怕空间不足而一开始就要求一个大块头的array了。

vector的实现技术，关键在于其对大小的控制以及重新配置时的数据移动效率，一旦vector旧空间满了，如果客户每新增一个元素，vector内部只是扩充一个元素空间，实为不智，因为所谓的扩充空间（不论多大），如刚才所说，是"配置新空间-数据移动-释放旧空间"的大工程，时间成本很高，应该加入某种未雨绸缪的考虑。

#### vector迭代器

vector维护一个线性空间，所以不论元素的型别如何，普通指针都可以作为vector的迭代器，因为vector迭代器所需要的操作行为，如operatpr*,operator->,operatpr++,operator--,operator+,operator-,operator+=,operator-=,普通指针天生具备。vector支持随机存取，而普通指针正有着这样的能力。所以vector提供的是随机访问迭代器(Random Access Iterators)

```c++
void test01()
{
    vector<int> v;
    for(int i = 0; i < 10; i++)
    {
        v.push_back(i);
        cout<<v.capacity()<<endl; // v.capacity() 容器的容量
    }
}
```

#### vector的数据结构

vector所采用的数据结构非常简单，线性连续空间，它以两个迭代器\_Myfirst和\_Mylast分别指向所配置得来的连续空间中目前已被使用的范围，并以迭代器\_Myend指向整块连续内存空间的尾端。

为了降低空间配置时的速度成本，vector实际配置的大小可能比客户端要求大一些，以备将来可能的扩充，这边是容量的概念。换句话说，**一个vector的容量永远大于或等于其大小，一旦容量等于大小，便是满载，下次再有新增元素，整个vector容器就得重新分配空间。**

```
注意：
所谓动态增加大小，并不是在原有的空间之后续接新的空间(因为无法保证原空间之后尚有可配置的空间)，而是一块更大的内存空间，然后将原数据拷贝新空间，并释放原空间。因此，对vector的任何操作，一旦引起空间的重新配置，指向原vector的所有迭代器就都失效了。
```

#### vector的API

##### vector构造函数

```c++
vector<T> v; // 采用模板类实现，默认构造函数
vector(v.begin(),v.end()); // 将v中begin到end区间中的元素拷贝给本身
vector(int n,T elem); // 构造函数将n个elem拷贝给本身
vector(const vector& vec); //拷贝构造函数

// 例子 使用第二个构造函数，我们可以
int arr[] = {2,3,4,1,9};
vector<int> v1(arr,arr+sizeof(arr)/sizeof(int));

```

##### vector常用赋值操作

```c++
assign(begin,end); // 将[begin,end)区间中的数拷贝赋值给本身
assign(n,elem); // 将n个elem拷贝赋值给本身
vector& operator=(const vector &vec); // 重载等号操作
swap(vec); // 将vec与本身的元素互换
```

##### vector大小操作 

```c++
size(); // 返回容器中元素的个数
empty(); // 判断容器是否为空
resize(int n); // 重新指定容器的长度为num，若容器变长，则以默认值填充新位置。如果容器变短 ，则末尾超出容器长度的元素被删除
capacity(); // 容器的容量
reserve(int len); // 容器预留len个元素长度，预留位置不初始化，元素不可访问
```

##### vector数据存取 

```c++
at(int idx); // 返回索引idx所指的数据，若idx越界，抛出out_of_range异常
operator[]; // 返回索引所指的数据，越界时，直接崩掉
front(); // 返回容器中第一个数据元素
back(); // 返回容器中最后一个数据元素
```

##### vector插入和删除

```c++
insert(const_iterator pos,int count,ele); // 迭代器指向位置pos插入count个元素ele。
push_back(ele); // 尾部插入元素
pop_back(ele); // 删除最后一个元素
erase(const_iterator start,const_iterator end); // 删除迭代器从start到end之间的元素
erase(const_iterator pos); // 删除迭代器指向的元素
clear(); // 删除容器中的所有元素
```

### deque容器

#### deque容器基本概念

vector容器是单向开口的**连续内存空间**，deque则是一种双向开口的**连续线性空间。**所谓的双向开口，意思是可以在头尾两端分别做元素的插入和删除操作，当然，vector容器也可以在头尾两端插入元素，但是在其头部操作效率奇差，无法被接受。

deque容器和vector容器最大的差异，一在于deque允许使用常数项时间对头端进行元素的插入和删除。二在于deque没有容量的概念，因为它是动态的以分段连续空间组合而成，随时可以增加一段新的空间并连接起来，换句话说，像vector那样，”旧空间不足而重新配置一块更大空间，然后复制元素，在释放旧空间“这样的事情在deque身上是不会发生的。也因此，deque没有必须要提供所谓的空间保留(reverse)功能。

虽然deque容器也提供了Random Access Iterator，但是它的迭代器并不是普通的指针，其复杂度和vector不是一个量级，这当然影响各个运算的层面。因此，除非有必要，我们应该尽可能的使用vector，而不是deque。对deque进行的排序操作，为了最高效率，可将deque先完整的复制到一个vector中，对vector容器进行排序，在复 回deque。

#### deque容器实现原理

deque容器是连续的空间，至少逻辑上看来如此，连续线性空间总是令我们联想到array和vector，array无法成长，vector虽可成长，却只能向尾端成长，而且其成长其实是一个假象，事实上 ”申请更大的空间，元数据复制新空间，释放原空间“三步骤，如果不是vector每次配置新的空间时都留有余裕，其成长假象所带来的代价是非常昂贵的。

deque是由一段一段定量的连续空间构成。一旦有必要在deque前端或者尾端增加新的空间，便配置一段连续定量的空间，串接在deque的头端或者尾端。deque最大的工作就是维护这些分段连续的内存空间的整体性的假象，并提供随机存取的接口，避开了重新配置空间，复制，释放的轮回，代价就是复杂的迭代器架构。

既然deque是分段连续内存空间，那么就必须有中央控制，维持整体连续的假象，数据结构的设计及迭代器的前进后退操作颇为繁琐。deque代码的实现远比vector或list都多得多。

deque采取一块所谓的map(注意不是STL的map容器)作为主控，这里所谓的map是一小块连续的内存空间，其中每一个元素(此处称为一个结点)都是一个指针，指向另一端连续性内存空间，称作缓冲区。缓冲区才是deque的存储空间的主体。

#### deque容器常用API

##### deque的构造函数

```c++
deque<T> deqT; // 默认构造函数
deque(begin,end); // 构造函数将[begin,end)区间中的元素拷贝给本身
deque(n,elem); // 构造函数将n个elem拷贝给本身
deque(const deque& deq); // 拷贝构造
```

##### deque的赋值操作

```c++
assign(begin,end); // 将[begin,end)区间中的数据拷贝赋值给本身
assign(n,elem); // 将n个elem拷贝赋值给本身
deque& operator=(const deque& deq); // 重载等号运算符
swap(deq); // 将deq与本身的元素互换
```

##### deque的大小操作

```c++
deque.size(); // 返回容器中元素的个数
deque.empty(); // 判断容器是否为空
deque.resize(num); // 重新指定容器的长度为num，若容器变长，则以默认值填充新位置，如果容器变短，则末尾超出容器长度的元素被删除
deque.resize(num,elem); // 重新指定容器的长度为num，若容器变长，则以elem填充多出来的，如果容器变短，则末尾超出容器长度的元素被删除
```

##### deque双端插入和删除操作

```c++
push_back(elem); // 在容器尾部添加一个数据
push_front(elem); // 在容器的头部插入一个数据
pop_back(); // 删除容器最后一个数据
pop_front(); // 删除容器第一个数据
```

##### deque数据存取

```c++
at(idx); // 返回索引idx所指的数据，如果idx越界，则抛出out_of_range
operator[]; // 返回索引idx所指的数据，如果idx越界，不抛出异常，直接崩掉
front(); // 返回第一个数据
back(); // 返回最后一个数据
```

##### deque插入操作

```c++
insert(pos,elem); // 在pos位置插入一个elem元素的拷贝，返回新数据位置
insert(pos,n,elem); // 在pos位置插入n个elem，无返回值
insert(pos,begin,end); // 在pos位置插入[begin,end)区间的数据，无返回值
```

##### deque删除操作

```c++
clear(); // 移除容器的所有数据
erase(begin,end); // 删除[begin,end)区间的数据，返回下一个数据位置
erase(pos); // 删除pos位置的数据，返回下一个数据的位置
```

### stack容器

#### stack容器基本概念

stack是一种先进后出的数据结构，他只有一个出口。stack容器允许新增元素，移除元素，取得栈顶元素，但是除了最顶端外，没有任何其他方法可以存取stack的其他元素。换言之，stack不允许有遍历行为。

**有元素入栈的操作称之为push，将元素出栈的操作称之为pop**

#### stack没有迭代器

stack所有元素的进出都必须符合”先进先出“的条件，只有stack顶端的元素，才有机会被外界取用。stack不提供遍历功能，也不提供迭代器。

#### stack常用API

##### stack构造函数

```c++
stack<T> stkT; // stack采用模板类实现，stack对象的默认构造函数
stack(const stack &stk); // 拷贝构造函数
```

##### stack赋值操作 

```c++
stack& operator=(const stack& stk); // 重载等号操作符
```

##### stack数据存取操作

```c++
push(elem); // 向栈顶添加元素
pop(); // 从栈顶移除第一个元素
top(); // 返回栈顶元素
```

##### stack大小操作

```c++
empty(); // 判断是否为空
size(); // 返回栈的大小
```

### queue容器

#### queue容器基本概念

queue是一种先进先出的数据结构，它有两个出口，queue容器允许从一端新增元素，从另一端移除元素。

#### queue没有迭代器

queue所有元素的进出都符合先进先出的条件，只有queue的顶端元素，才有机会被外界取用。queue不提供遍历功能，也不提供迭代器。

#### queue常用的API

##### queue构造函数

```c++
queue<T> queT; // queue采用模板类实现，queue对象的默认构造形式
queue(const queue& que); // 拷贝构造函数
```

##### queue存取，插入和删除

```c++
push(elem); // 往队尾添加元素
pop(); // 从队头移除第一个元素
back(); // 返回最后一个元素
front(); // 返回第一个元素
```

##### queue赋值操作

```c++
queue& operator=(const queue& que); // 重载等号操作符
```

##### queue大小操作

```c++
empty(); // 判断队列是否为空
size(); // 返回队列的大小
```

### list容器

#### list容器基本概念

链表是一种物理存储单元上非连续，非顺序的存储结构，数据元素的逻辑顺序是通过链表中的指针链接次序实现的。链表由一系列结点（链表中的每一个元素称为结点）组成，结点可以在运行时动态生成。每个结点包括两个部分：一个是存储数据元素的数据域，另一个是存储下一个结点地址的指针域。

相较于vector的连续线性空间，list就显得负责许多，它的好处是每次插入或者删除一个元素，就是配置或者释放一个元素的空间。因此list对于空间的运用有绝对的精准，一点也不浪费。而且，对于任何位置的元素插入或元素的移除，list永远是常数时间。

**list容器是一个双向链表**

- 采用动态存储分配，不会造成内存浪费和溢出
- 链表执行插入和删除操作十分方便，修改指针即可，不需要移动大量元素
- 链表灵活，但是空间和时间额外耗费较大

#### list容器的迭代器

list容器不能像vector一样以普通指针作为迭代器，因为其节点不能保证在同一块连续的内存空间上。list迭代器必须有能力指向list节点，并有能力进行正确的递增，递减，取值，成员存取操作。所谓list正确的递增，递减，取值，成员取用是指递增时指向下一个节点，递减时指向上一个节点，取值时取得是节点的数据值，成员取用时取的是节点的成员

由于list是一个双向链表，迭代器必须具备前移，后移的能力，所以list容器提供的是Bidirectional Iterators。

list有一个重要的性质，插入和删除操作都不会造成原有list迭代器的失效。这在vector是不成立的，因为vector的插入操作可能造成记忆体重新配置，导致原有的迭代器全部失效，甚至list元素的删除，也只有被删除的那个元素的迭代器失效，其他迭代器不受任何影响。

#### list容器的数据结构

list容器不仅是一个双向链表，还是一个循环链表

#### list常用API

##### list构造函数

```c++
list<T> lstT; // list采用模板类实现，对象的默认构造函数
list(begin,end); // 构造函数将[begin,end)区间中的元素拷贝给本身
list(n,elem); // 构造函数将n个elem拷贝给本身
list(const list& lst); // 拷贝构造函数
```

##### list数据元素插入和删除操作

```c++
push_back(elem); // 在容器中尾部加入一个元素
pop_back(); // 删除容器中最后一个元素
push_front(elem); // 在容器开头插入一个元素
pop_front(); // 从容器开头移除第一个元素
insert(pos,elem); // 在pos位置插入elem元素的拷贝，返回新数据的位置
insert(pos,n,elem); // 在pos位置插入n个elem数据，无返回值
insert(pos,begin,end); // 在pos位置插入[begin,end)区间的数据，无返回值
clear(); // 移除容器的所有数据
erase(begin,end); // 删除[begin,end)区间的数据，返回下一个数据的位置
erase(pos); // 删除pos位置的数据，返回下一个数据的位置
remove(elem); // 删除容器中所有与elem值匹配的元素
```

##### list的大小操作

```c++
size(); // 返回容器中元素的个数
empty(); // 判断容器是否为空
resize(num); // 重新指定容器的长度为num 若容器变长，则以默认值填充新位置。 如果容器变短，则末尾超出容器长度的元素被删除。
resize(num,elem); // 重新指定容器的长度为num，若容器变长，则以elem值填充新位置，如果容器变短，则末尾超出容器长度的元素被删除
```

##### list赋值操作

```c++
assign(begin,end); // 将[begin,end)区间中的数据拷贝赋值给本身
assign(begin,end); // 将n个elem拷贝赋值给本身
list& operator=(const list& lst); // 重载等号操作符
swap(lst); // 将lst与本身的元素互换
```

##### list数据的存取

```c++
front(); // 返回第一个元素
back(); // 返回最后一个元素
```

#####  list反转排序

```c++
reverse(); // 反转链表，比如lst包含1，3，5元素，运行后，lst就包含5，3，1元素
sort(); // list排序  
// 所有不支持随机访问的迭代器，不可以用系统提供的算法
```

##### list容器remove删除自定义数据类型

自定义数据类型编译器没办法比较是否相等，因此需要重载==，这样就能调用remove删除自定义数据类型了

### set/multiset容器

#### set容器基本概念

set的特性是，所有元素会根据元素的键值自动被排序。set的元素不像map那样可以同时拥有实值和键值。set不允许有两个元素的值相同。

我们可以通过set迭代器改变set元素的值吗？——不行，因为set元素值就是其键值，关系到set元素的排序规则。如果任意改变set元素值，会严重破坏set组织。换句话说，set的iterator是一种const_iterator.

set拥有和list某些相同的性质，当对容器中的元素进行插入操作或者删除操作的时候，操作之前所有的迭代器，在操作完成之后依然有效，被删除的那个元素的迭代器必然是一个例外。

#### multiset容器基本概念

multiset特性及用法和set完全相同，唯一的差别在于它允许键值重复。set和multiset的底层实现是红黑树，红黑树为平衡二叉树的一种。

#### set常用API

##### set构造函数

```c++
set<T> st; // set默认构造函数
mulitset<T> mst; // multiset默认构造函数
set(const set& st); // 拷贝构造函数
```

##### set赋值操作

```c++
set& operator=(const set& st); // 重载等号操作符
swap(st); // 交换两个集合容器
```

##### set大小操作

```c++
size(); // 返回容器中元素的数目
empty(); // 判断容器是否为空
```

##### set插入和删除

```c++
insert(elem); // 在容器中插入元素
clear(); // 清楚所有元素
erase(pos); // 删除pos迭代器所指的元素，返回下一个元素迭代器的位置
erase(begin,end); // 删除区间[begin,end)的所有元素，返回下一个元素的迭代器
erase(elem); // 删除容器中值为elem的元素
```

##### set查找操作

```c++
find(key); // 查找键key是否存在，若存在，返回该键的元素的迭代器；若不存在，返回set.end()
count(key); // 查找键key的元素个数
lower_bound(keyElem); // 返回第一个key >= keyElem元素的迭代器
upper_bounder(keyElem); // 返回第一个key > keyElem元素的迭代器
equal_range(keyElem); // 返回容器中key与keyElem相等的上下限的两个迭代器  返回的是一个pair
```

#### set不允许插入重复的键值

```c++
void test()
{
    set<int> s1;
    s1.insert(10);
    s1.insert(10); // insert返回值 pair<iterator,bool>
}
```

#### set容器排序

默认从小到大排序

```c++
// 指定set排序规划 从大到小
// 仿函数
// 利用仿函数
class myCompare()
{
    public:
    //重载
    bool operator()(int v1,int v2)
    {
        return v1 > v2;
    }
};


void test()
{
    set<int,myCompare> s1; // 因为int为一个类型，所以需要定义一个仿函数来定义比较规则
    s1.insert(5);
    s1.insert(1);
    s1.insert(9);
    s1.insert(3);
    s1.insert(7);
}
```

#### set插入自定义数据类型

```c++
class Person
{
  public:
    Person(string name,int age)
    {
        this->m_Name = name;
        this->m_Age = age;
    }
    
    string m_Name;
    int m_Age;
};
class myComparePerson
{
    public:
    bool operator()(const Person& p1,const Person& p2)
    {
        if(p1.m_Age > P2.m_Age)
            return true;
        return false;
    }
}
void test01()
{
    set<Person,myComparePerson> s1;
    Person p1("asd",10);
    Person p2("xds",20);
    Person p3("asfbx",30);
    s1.insert(p1);
    s1.insert(p2); // 因为插入时需要排序，但是不知道自定义数据类型如何排序，所以不会成功，需要提供比较方法
    s1.insert(p3);
}
```



### pair对组

```c++
//创建对组
void test01()
{
    // 第一种创建方式
    pair<string,int> p(string("Tom"),100);
    cout << p.first << end;
    cout << p.second << endl;
    // 第二种创建方式
    pair<string,int> p2 = make_pair("Jerry",200);
}
```

### map/multimap容器

#### map/multimap基本概念

map的特性是所有元素都会根据元素的键值自动排序。map所有的元素都是pair，同时拥有实值和键值，pair的第一元素被视为键值，第二元素被视为实值，map不允许两个元素有相同的键值

我们可以通过map的迭代器改变map的键值吗？ 答案是不行的，因为map的键值关系到map元素的排列规则，任意改变map键值将会严重破坏map的组织。如果想要修改元素的实值，那么是可以的。

map和list拥有相同的某些性质，当对它的容器元素进行新增操作或者删除操作时，操作之前的所有迭代器，在操作完成之后依然有效，当然被删除的那个元素的迭代器必然是个例外。

multimap和map的操作类似，唯一的区别就是multimap键值可以重复

map和multimap都是以红黑树为底层实现机制

#### map/multimap常用API

##### map构造函数

```c++
map<T1,T2> mapTT; // map的默认构造函数
map(const map& mp); // 拷贝构造函数
```

##### map赋值操作

```c++
map& operator=(const map& mp); // 重载=操作符
swap(mp); // 交换两个集合容器
```

##### map大小操作

```c++
size(); // 返回容器中元素的数目
empty(); // 判断容器是否为空
```

##### map插入数据元素操作

```c++
map.insert(...); // 往容器里插入元素，返回pair<iterator,bool>
map<int,string> mapStu;
// 第一种 通过pair的方式插入对象
mapStu.insert(pair<int,string>(3,"asdasd"));
// 第二种 通过pair的方式插入对象
mapStu.insert(make_pair(-1,"asdasd"));
// 第三种 通过value_type的方式插入对象
mapStu.insert(map<int,string>::value_type(1,"asd"));
// 第四种 通过数组的方式插入值
mapStu[3] = "asdasd"
```

##### map删除操作

```c++
clear(); // 删除所有元素
erase(pos); // 删除pos迭代器所指的元素，返回下一个元素的迭代器
erase(begin,end); // 删除区间[begin,end)的所有元素，返回下一个元素的迭代器
erase(keyElem); // 删除容器中key为keyElem的对组
```

##### map查找操作

```c++
find(key); // 查找键key是否存在，若存在，返回该键的元素的迭代器，若不存在返回map.end()
count(keyElem); // 返回容器中key为keyElem的对组的个数，对map来说，要么是0，要么是1.对multimap来说，可以大于1
lower_bound(keyElem); // 返回第一个key >= keyElem元素的迭代器
uppper_bound(keyElem); // 返回第一个key > keyElem元素的迭代器
equal_range(keyElem); // 返回容器中key与keyElem相等的上下限的两个迭代器
```

### 函数对象

重载函数调用操作符的类，其对象常称为函数对象（function object），即它们是行为类似函数的对象，也叫做仿函数（functor），其实就是重载"()"操作符，使得类对象可以像函数那样调用。

注意：

- 函数对象（仿函数）是一个类，不是一个函数。
- 函数对象（仿函数）重载了"()"操作符使得它可以像函数一样调用

分类：假定某个类有一个重载的operator()，而且重载的operator()要求获取一个参数，我们就将这个类称为“一元仿函数”；相反，如果重载operator()要求获取两个参数，就将这个类称为“二元仿函数”。

**函数对象的作用主要是什么？**

**STL提供的算法往往都有两个版本，其中一个版本表现出最常用的某种运算，另一个版本则允许用户通过template参数的形式来指定所要采取的策略**

总结：

- 函数对象通常不定义构造和析构函数，所以在构造和析构时不会发生任何问题，避免了函数调用的运行时问题
- 函数对象超出普通函数的概念，函数对象可以有自己的状态
- 函数对象可内联编译，性能好。用函数指针几乎不可能
- 模板函数对象使函数对象具有通用性，这也是它的优势之一。

```c++
class MyPrint
{
    public:
    void operator()(int num)
    {
        cout<<num<<endl;
        count++; // 可记录调用的次数
    }
    
    int count = 0;
}

MyPrint2(int num)
{
    cout<<num<<endl;
}

void test01()
{
    // MyPrint是一个类，而不是一个函数
    MyPrint myPrint;
    myPrint(111);
    
    //MyPrint2(111);
    
    MyPrint()(1000);
}

// 函数对象超出普通函数概念，内部可以保持状态
void test02()
{
    MyPrint()(1000);
    MyPrint()(1000);
    MyPrint()(1000);
    MyPrint()(1000);
}

// 函数对象作为参数
void doPrint(MyPrint print,int num)
{
    print(num);
}
void test03()
{
    doPrint(MyPrint(),20);
}
```

### 谓词的使用

谓词是指普通函数或重载的operator()返回值是bool类型的函数对象(仿函数)。如果operator接收一个参数，那么叫做一元谓词，如果接收两个参数叫做二元谓词，谓词可作为一个判断式

```c++
class GreaterThen20
{
    public:
    bool operator()(int val)
    {
        return val > 20;
    }
}
// 一元谓词
void test01()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);
    
    // 查找第一个大于20的数字
    // 第三个参数 函数对象 
    vector<int>::iterator pos = find_if(v.begin(),v.end(),GreaterThen20());
    if(pos!=v.end())
    {
        cout<<"找到大于20的数字"<<*pos<<endl;
    }
    else
    {
        cout<<"未找到"<<endl;
    }
    
    // 二元谓词的使用
    // 系统提供的sort默认为从小到大排序
    // 可使用二元谓词变为从大到小排序
}
```

### 内建函数对象

STL内建了一些函数对象。分为：算数类函数对象，关系运算类函数对象，逻辑运算类仿函数。这些仿函数所产生的对象，用法和一般函数完全相同，当然我们还可以产生无名的临时对象来履行函数功能。使用内建函数对象，需要引入头文件#include\<functional\>

- 6个算法类函数对象，除了negate是一元运算，其他都是二元运算

  ```c++
  template<class T> T plus<T> // 加法仿函数
  template<class T> T minus<T> // 减法仿函数
  template<class T> T multiplies<T> // 乘法仿函数
  template<class T> T divides<T> // 除法仿函数
  template<class T> T modulus<T> // 取模仿函数
  template<class T> T negate<T> // 取反仿函数
  ```

- 6个关系运算类函数对象，每一种都是二元运算

  ```c++
  template<class T> bool equal_to<T> // 等于
  template<class T> bool not_equal_to<T> // 不等于
  template<class T> bool greater<T> // 大于
  template<class T> bool greater_equal<T> // 大于等于
  template<class T> bool less<T> // 小于
  template<class T> bool less_equal<T> // 小于等于
  ```

- 逻辑运算类运算函数，not为一元运算，其余为二元运算

  ```c++
  template<class T> bool logical_and<T> // 逻辑与
  template<class T> bool logical_or<T> // 逻辑或
  template<class T> bool logical_not<T> // 逻辑非
  ```



```c++
#include<functional>
// template<class T> T negate<T>
void test01()
{
    negate<int> n;
    
    cout<<n(10)<<endl;
     
    // 加法 template<class T> T plus<T>
    plus<int> p;
    cout<<p(1,1)<<endl; // 1+1
}

// 
void test02()
{
    // template<class T> bool greater<T> 大于
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(40);
    v.push_back(30);
    v.push_back(8);
    sort(v.begin(),v.end()，greater<int>());
}
```

### 适配器的使用

```c++
#include<vector>
#include<algorithm>
#include<functional>
class MyPrint:public binary_function<int,int,void>
{
public:
	void operator()(int v,int num) const
	{
		cout << v + num << endl;
	}
};
void test01()
{
	vector<int> v;
	for (int i = 0; i < 10; i++)
		v.push_back(i);
	int num;
	cin >> num;
	// for_each(v.begin(), v.end(),bind2nd(MyPrint(),num));
	for_each(v.begin(), v.end(), bind1st(MyPrint(), num));
}
// 第一步 绑定数据 bind2nd
// 继承类 binary_function<参数类型1，参数类型2，返回值类型>
// 加const修饰 operator()
```

### 算法

#### 算法概述

算法主要由头文件\<algorithm\>,\<functional\>,\<numeric\>组成。

\<algorithm\>是所有STL头文件中最大的一个，其中常用的功能涉及到比较，交换，查找，遍历，复制，修改，反转，排序，合并等。

\<numeric\>体积很小，只包括在几个序列容器上进行的简单运算的模板函数。

\<functional\>定义了一些模板类，用以声明函数对象

#### 常用的遍历算法

```c++
/*
beg 开始迭代器
end 结束迭代器
_callback 函数回调或者函数对象
*/
// for_each(iterator beg,iterator end,_calback)
class myPrint
{
  public:
    void operator()(int v)
    {
        cout<<v<<endl;
    }
};
void test01()
{
    vector<int> v;
    for(int i = 0; i < 10; i++)
        v.push_back(i);
    for_each(v.begin(),v.end(),)
}
```

