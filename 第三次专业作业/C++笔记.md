 # C++笔记
## 引言
### 面向对象程序设计方法
- 将某类事物共同特点（属性）归纳出来，形成一个数据结构（可以用多个变量描述事物的属性）；

- 将这类事物所能进行的行为也归纳出来，形成一个个函数，这些函数可以用来操作数据结构（这一步叫“抽象”）

然后通过某种语法形式，将数据结构和操作该数据结构的函数“捆绑”在一起，形成一个“类”，从而使得数据结构和操作该数据结构的算法呈现出显而易见的紧密关系，这就是“封装”。























## 第一课“引用”

```c
int &r=n
//r和n等价
```
 
 - 1.定义引用时一定要将其初始化成引用某个变量
 - 2.初始化后，不可以改变其引用的变量
 
 - 3.只能引用变量，不能引用常量和表达式

### 交换值
```c
void swap(int& a,int& b)
{
    int tmp;
    tmp=a;a=b;b=tmp;
}
int n1,n2;
swap(n1,n2);//n1,n2的值被交换
```
### 引用可以作为全局变量的返回值
```c
int n = 4;
int &SetVaue(){return n;}
int main()
{
    SetValue()=40;
    cout<<n;
    return 0;
}
```
### 常引用

不能通过常引用去修改其引用的内容

```c
int n= 100;
const &r=n;
r=200;  //编译报错
n=300;  //不报错
```
### 常引用和非常引用之间的转化
- T&类型的引用或T类型的变量可以用来初始化
const T&类型的引用

- const T类型的常变量和const T&类型的引用则不能用来初始化T&类型的引用，除非进行强制类型转换。


----

## const关键字

### 定义常量

```c
const int MAX_VAL=23;
const double Pi = 3.14;
const char* SCHOOL_NAME = "Peking Univsersity";
```

### 定义常量指针
- 不可以通过指针去修改指向的内容
- 不可以把常量指针赋值给非常量指针，反过来可以
```c
const int*p1;int *p2;
p1=p2;  //ok
p2=p1;  //报错
p2=(int*)p1;   //ok
```


----


## new运算符
### 第一种用法，分配一个变量
P=new T;

T是任意类型名，P是类型为T *的指针。
动态分配出一片大小为sizeof(T)字节的内存空间，并且将该内存的空间的起始地址赋值给P。

```c
int *pn;
pn = new int;
*pn = 5;

```
### 第二钟用法，分配一个数组
P = new T[N];

```c
int *pn;
int i =5;
pn= new int[i*20];
pn[0] = 20;
pn[100] = 30;//编译没问题，运行时导致数组越界
```

### new 运算符的返回值类型

new T;

new T[N];

这两个表达式的返回值都是T*

### new分配的内存空间用完之后要释放掉

delete指针; //该指针必须指向new出来的空间

```c
int *p=new int;
*p=5;
delete p;
delete p;   //导致异常，一片空间不能被delete多次
```

### 用delete释放动态分配的数组，要加“[]”
delete[]指针    //该指针必须指向new出来的空间

```c
int *p=new int[20];
p[0]=1;
delete[]p;
```

----
## 内联函数和外联函数

### 内联函数
- 由于函数本身语句较少，在调用函数时，调用语句占用了程序运行效率，所以直接将函数插入到程序当中，不用使用调用语句。

在函数前面加个关键字"inline",即可定义内联函数

```c
inline int MAX(int a,int b)
{
    if(a>b)return a;
    return b;
}
```

### 函数重载

一个或多个函数，名字相同，但参数个数和参数类型不相同，这叫做参数的重载

- 1.函数的命名变得简单
- 2.编译器根据调用语句中的实参的个数和类型判断应该调用哪个函数

### 函数的缺省参数

>定义函数时，可以让最右边的连续若干个参数有缺省值，那么调用函数的时候，若相应位置不写参数，参数就是缺省值

```c
void func(int x1,int x2=2,int x3=3){}
func(10);   //等效于func(10,2,3)  
func(10,8); //等效于func(10,8,3)
func(10,,8) //不行，只能最右边的连续若干个参数缺省
```
- 提高程序的可扩充性


## 类
```c
int CRectangle::Area()
{
    return w*h;
}
```
 CRectangle::表示后面的函数是CRectangle的成员函数
 那么一定要通过对象，对象的指针或对象的引用才能调用

 ### 类成员的可访问范围

> -private:私有成员，只能在成员函数内访问

> -public：公有成员，可以在任何地方访问

> -protected：保护成员

### 成员函数的重载和参数缺省
> 成员函数也可以重载

> 成员函数可以带缺省参数

> 使用缺省参数要注意避免有函数重载时的二义性

### 复制构造函数
>只有一个参数，即对同类对象的引用。

> 形式：   X::X(const X &)
```cpp
class Compex{
    private:
        double real,imag;
}
Compex c1;  //调用了缺省无参构造函数
Compexc2(c1);   //调用缺省的复制构造函数，将c2初始化成和c1一样
```
```cpp
class Complex{
    public:
        double real,imag;
    Complex(){}
    Complex(const Complex & c){
        real = c.real;
        imag = c.imag;
        cout<<"Copy Constructor called";
    }
};
Complex c1;
Complex c2(c1);
```
### 类型转换构造函数
> 目的是实现类型的自动转换

> 只有一个参数，而且不是复制构造函数的构造函数，一般就可以看作转换构造函数

> 当需要的时候，编译系统会自动调用转换构造函数，建立一个无名的临时对象（或临时变量）

```cpp
class Complex{
    public:
        double real,imag;
        Complex(int i){     //类型转换构造函数
            cout << "IntConstructor called"<<endl;
            real=i;imag=0;
        }
        Complex(double r,double i){real = r;imag = i;}
};
int main()
{
    Complex c1(7,8);
    Complex c2 = 12;
    c1 = 9;     //9被自动转换为一个临时的Complex对象
    coutK<<c1.real<<","<<c1.imag<<endl;
    return 0;
}
```

### 析构函数 
>名字与类名相同，在前面加上“~”，没有参数和返回值，一个类最多只能有一个析构函数。
 
>析构函数对象消亡时则自动被调用。可以定义析构函数来在对象消亡前做善后工作，比如释放分配的空间等。

>如果定义类的时候没有写析构函数，那么编译器生成缺省析构函数，缺省析构函数什么也不做。

>如果定义了析构函数，则编译器不生成析构函数
```cpp
class String
{
    private:
        char *p;
    public:
        String(){
            p=new char[10];
        }
        ~ String();
};
String ::~String()
{
    delete [] p ;
}

```
### delete运算符

>delete运算导致析构函数被调用。
```cpp
Ctest *pTest;
pTest = new Ctest;  //构造函数调用
delete pTest;       //析构函数调用
-----------------------------------
pTest = new Ctest[3];   //构造函数被调用3次
delete [] pTest;        //析构函数调用3次
```
> 若new一个对象数组，那么用delete释放时应该写[]。否则只delete一个对象（调用一次析构函数）





析构函数在对象作为函数返回值返回后被调用

``` cpp
class CMyclass{
    public:
    ~CMyclass(){coutM<<"destructor"<<endl;}
};
CMyclass obj;
CMyclass fun(CMyclass sobj){    //参数函数消亡也会导致析构函数被调用
    return obj;     //函数对象返回时生成临时对象返回
}
int main(){
    obj = fun(obj);     //函数调用的返回值(临时对象)被用过后，临时对象析构函数被调用
    return 0;
}
```

### 构造函数和析构函数什么时候被调用

```cpp
class Demo{
    int  i;
    public:
        Demo(int i){
            id=i;
            cout<<"id = "<<id<<"constructed"<<endl;
        }
        ~Demo(){
            cout<<"id = "<<id<<"detructed"<<endl;
        }
};
Demo d1(1);
void Func()
{
    static Demo d2(2);
    Demo d3(3);
    cout<<"func"<<endl;
}
int main()
{
    Demo d4(4);
    d4 =6 ;
    cout << main << endl;
    {
        Demo d5(5)
    }
    Func();
    cout << main ends << endl;
    return 0;
}
```


## this指针


>指向成员函数所作用的对象



>非静态成员函数中可以直接使用this来代表指向该函数作用对象的指针。
```cpp
class Compex{
public:
    double real,imag;
    void Print(){cout<<real<<","<<imag;}
    Complex(double r,double i):real(r),imag(i)
{}
Complex AddOne(){
    this->real++;
    this->Print();
    return *this;
}
};
int main()
{
    Complex c1(1,1),c2(2,0);
    c2=c1.AddOne();
    return 0;
}
```
```cpp
class A
{
    int i;
public:
    void Hello(){cout<<"hello"<<endl;}                 //void Hello(A *this){cout<<"hello"<<endl;}
};
int main()
{
    A *p = NULL;
    p->Hello();              //=Hello(p)
}//输出hello




>False
class A
{
    int i;
public:
    void Hello(){cout<<i<<"hello"<<endl;}         //void Hello(A *this){cout<<this->i<<"hello"<<endl;}         
};
int main()
{
    A *p = NULL;
    p->Hello();              
}//输出hello

```

静态成员函数中不能使用this指针

因为静态成员函数并不具体作用于某个对象
因此静态函数的真实的参数个数，就是程序中写出的参数个数！


## 静态成员变量和静态成员函数

静态成员：定义的时候在前面加了关键字static
```cpp
class CRectangle
{
    private:
        int w,h;
        static int nTotalArea;      //静态成员变量
        static int nTotalNumber;
    public:
        CRrctangle(int w_,int h_);
        ~CRrctangle();
        static void PrintTotal();       //静态成员函数
}

```

>普通成员变量每个成员有一份，静态成员变量一共就一份

sizeof()不会计算静态成员变量

### 如何访问静态成员
- 类名::成员名
    CRentangle::PrintTotal();
- 对象名.成员名
    CRentangle r;r.PrintTotal();
- 指针->成员名
    CRentangle *p = &r; p->PrintTotal();


- 引用.成员名
    CRectangle & ref=r; int n=ref.nTotalNumber


> 静态成员变量本质上是全局变量，哪怕一个对象都不存在，类的静态成员变量也存在

> 静态成员函数本质上是全局函数

> 设置静态成员这种机制的目的是将和某些紧密相关的全局变量和函数写到类里面，看上去像一个整体，易于理解和维护。

> 静态函数中，不能访问非静态成员变量，也不能调用非静态成员函数
```cpp
void CRtangle::PrintTotal()
{
    cout<<w<<","<<nTotalNumber<<","<<nTotalArea<<endl;   //wrong
}
```
 

 ## 成员对象和封闭类

 > 有成员对象的类叫封闭类

 ```cpp
 class CType        //车轮
 {
    private:
        int radius;
        int width;
    public:
    CTypre(int r,int w):radius(r),width(w){ }
 };
 
 class CEngine      //引擎类
 {

 };

class CCar{     //汽车类     封闭
    private:
        int price;
        CTyre type;
        CEngine engine;
    public:
        CCar(int p,int tr, int tw);
};
CCar::CCar(int p,int tr,int w):prince(p),type(tr,w)
{

};
int main()
{
    CCar car(20000,17,225)
    return 0;
}

```
如果CCar不定义构造函数，会编译出错

> 任何生成封闭类对象的语句，又要让编译器明白，对象中的成员对象，是如何初始化的。通过封闭类的构造函数初始化列表。


### 封闭类构造函数和析构函数的执行顺序

> 封闭类对象生成时，先执行所有对象成员的构造函数，然后才执行封闭类的构造函数

>对象成员的构造函数调用次序和对象成员在类中的说明次序一样，与他们在成员初始化列表中出现的次序无关

>当封闭类的对象消亡时，先执行封闭类的析构函数，然后在执行成员对象的析构函数。次序和构造函数的调用次序相反。

### 封闭类的复制构造函数

```cpp
class A
{
public:
    A(){cout<<"default"<<endl;}
    A(A &a){cout << "copy"<< endl;}
};
class B(A a;)
int main()
[
    B b1,b2(b1);
    return 0;
]
```
## 常量对象，常量成员函数，常引用
> 如果定义一个对象的时候，不希望它的值被改变，可以加上const关键字

>在类的成员函数说明后面加上const，成为常量成员函数

>在引用的前面加const关键字，不可以改变其引用的值

## 友元

友元函数和友元类

1）友元函数：一个类的友元函数可以访问该类的私有成员

2）友元类；如果A是B的友元类，那么A的成员函数可以访问B的私有成员

> 友元类之间的关系不能传递，不能继承



## 运算符的重载

让对象也能通过运算符运算

> 运算符重载，就是对已有的运算符（C++中预定义的运算符）赋予多重的含义，使一运算符作用于不同类型的数据时导致不同类型的行为。

>运算符重载的目的是：扩展运算符的适用范围，使之能做用于对象

>同一运算符，对不同类型的操作数，所发生的行为不同

返回值类型 operator 运算符（形参表）
{
    ...........
}

## 赋值运算符的重载

赋值运算符“=“只能重载为成员函数

## 浅拷贝和深拷贝

## 运算符被重载为友元函数
```cpp
class Complex
{
    double real,imag;
    public:
    Complex(double r,double i):real(r),imag(i){};
    Complex operator+(doule r);
};
Complex Complex::operator+(double r)
{
    return Complex(real+r,imag);
}
```
>一般情况下，将运算符重载为类的成员函数，是较好的选择

>但有时，重载为成员函数不能满足使用要求，重载为普通函数，又不能访问类的私有成员，所以需要将运算符重载为友元

```cpp
Complex c;
c=c+5;      //有定义，相当于c=c.operator+(5);
但是：
c=5+c;      //编译出错
```


- 所以，为了使得上述的表达式能成立，需要将+重载为普通函数。
```cpp
Complex operator+ (double r,const Complex & c)

Complex operator+ (double r,const Complex & c)
{       //能解释5+c
    return Complex(c.real+r,c.imag);
}
```
```cpp
class Complex
{
    double real,imag;
    public:
    Complex(double r,double i):real(r),imag(i){};
    Complex operator+(doule r);
    friend Complex operator+(doule r,const Complex & c);
};
Complex Complex::operator+(double r)
{
    return Complex(real+r,imag);
}
```


## 可变长数组类的实现
```cpp
int main() {    //要编写可变长整型数组类，使之能如下使用：
    CArraya;    //开始里的数组是空的
    for( inti= 0;i < 5;++i)
        a.push_back(i);
    CArraya2,a3;
    a2 = a;
    for( inti= 0; i< a.length(); ++i)
         cout<< a2[i] << " " ;
 a2 = a3; //a2是空的
for( inti= 0; i< a2.length(); ++i) //a2.length()返回0
        cout<< a2[i] << " ";
 cout<< endl;
 a[3] = 100;
 CArraya4(a);
    for( inti= 0; i< a4.length(); ++i)
        cout<< a4[i] << " ";
    return 0;
    }
```
```cpp
class  CArray {
    int size; //数组元素的个数
    int *ptr; //指向动态分配的数组
public:
    CArray(int s = 0);     //s代表数组元素的个数
    CArray(CArray & a);
    ~CArray();
    void push_back(int v); //用于在数组尾部添加一个元素v
    CArray & operator=( const CArray & a); 
    //用于数组对象间的赋值
    int length() { return size; } //返回数组元素个数
    int & CArray::operator[](int i)  //返回值为 int 不行!不支持 a[i] = 4
    {//用以支持根据下标访问数组元素，
    // 如n = a[i] 和a[i] = 4; 这样的语句
    return ptr[i]; 
    } 
};
```

## 继承和派生
- **继承的概念**
  - 派生类从基类继承成员函数和变量。
  - 派生类可以扩展新的成员函数和变量。
- **派生类的写法**
  - `class 派生类名 : public 基类名 { ... }`
- **继承关系**
  - **“是”关系**：派生类对象也是基类对象。
  - **“有”关系**：复合关系，一个类中包含另一个类的对象。
- **类之间的两种关系**
  - 继承：“是”关系。
  - 复合：“有”关系。
- **派生类的构造函数**
  - 需要调用基类的构造函数初始化基类成员。
  - 示例：`Derived(int i):Base(i) { ... }`
- **类的保护成员**
  - 基类的`protected`成员在派生类中可以访问，但对外部隐藏。
- **基类与派生类的指针强制转换**
  - 公有派生情况下，派生类指针可以隐式转换为基类指针。
  - 强制转换时需谨慎，确保对象类型匹配。
- **直接基类和间接基类**
  - 类的继承层次结构，派生类自动继承间接基类的成员。
  ## 虚函数和多态
- **虚函数**
  - 定义：`virtual void SomeVirtualFunction() { }`
  - 作用：实现多态。
- **多态的表现形式**
  - 通过基类指针调用虚函数。
  - 通过基类引用调用虚函数。
- **多态的实现原理**
  - 虚函数表：每个类有一个虚函数表，存储虚函数地址。
  - 动态联编：运行时确定调用哪个函数。
- **纯虚函数和抽象类**
  - 纯虚函数：`virtual void Print() = 0;`
  - 抽象类：包含纯虚函数的类，不能实例化。
- **虚析构函数**
  - 作用：确保删除派生类对象时调用正确的析构函数。
  - 定义：`virtual ~Base() { ... }`
  ## 函数模板和类模板
- **函数模板**
  - 定义：`template <class T> void Swap(T & x, T & y) { T tmp = x; x = y; y = tmp; }`
  - 重载：可以重载函数模板。
- **类模板**
  - 定义：`template <class T1, class T2> class Pair { public: T1 key; T2 value; }`
  - 实例化：`Pair<string, int> student("Tom", 19);`
  - 成员函数模板：`template <class T2> void Func(T2 t) { cout << t; }`
- **类模板的继承**
  - 从类模板派生：`class B : public A<T2, T1> { ... }`
  - 从模板类派生：`class B : public A<int, double> { ... }`
  ## C++中的`string`类
- **基本操作**
  - 初始化：`string s1("Hello");`
  - 赋值：`s2 = s1;`
  - 连接：`s1 += s2;`
  - 比较：`==, >, >=, <, <=, !=`
- **成员函数**
  - `length()`：获取字符串长度。
  - `at()` 和 `[]`：访问字符。
  - `find()` 和 `rfind()`：查找子串。
  - `erase()`：删除字符。
  - `replace()`：替换字符。
  - `insert()`：插入字符。
  - `substr()`：获取子串。
- **字符串流处理**
  - `istringstream`：输入流。
  - `ostringstream`：输出流。
  - 示例：`istringstream inputString("Input test 123 4.7 A");`
  ## STL（标准模板库）
- **关联容器**
  - `set` 和 `multiset`：内部元素有序排列，支持快速查找。
  - `map` 和 `multimap`：存储键值对，按键排序。
- **`set` 和 `multiset` 的成员函数**
  - `find`：查找元素。
  - `insert`：插入元素。
  - `count`：统计元素个数。
  - `lower_bound` 和 `upper_bound`：查找上下界。
  - `equal_range`：同时查找上下界。
  - `erase`：删除元素。
- **`map` 和 `multimap` 的用法**
  - 存储键值对，支持按键排序和查找。
- **容器适配器**
  - `stack`：后进先出。
  - `queue`：先进先出。
  - `priority_queue`：优先队列，按优先级排序。
- **STL算法**
  - 分类：不变序列算法、变值算法、删除算法、变序算法、排序算法、有序区间算法、数值算法。
  - 示例算法：
    - `min_element` 和 `max_element`：查找最小和最大元素。
    - `find` 和 `find_if`：查找满足条件的元素。
    - `transform`：对区间元素进行变换。
    - `sort` 和 `stable_sort`：排序算法。