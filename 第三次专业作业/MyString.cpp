#include <cstdlib>
#include <iostream>
using namespace std;
int strlen(const char * s) 
{	int i = 0;
	for(; s[i]; ++i);
	return i;
}
void strcpy(char * d,const char * s)
{
	int i = 0;
	for( i = 0; s[i]; ++i)
		d[i] = s[i];
	d[i] = 0;
		
}
int strcmp(const char * s1,const char * s2)
{
	for(int i = 0; s1[i] && s2[i] ; ++i) {
		if( s1[i] < s2[i] )
			return -1;
		else if( s1[i] > s2[i])
			return 1;
	}
	return 0;
}
void strcat(char * d,const char * s)
{
	int len = strlen(d);
	strcpy(d+len,s);
}
class MyString
{
size_t len;
    char* str = nullptr;
public:
    MyString(const char* s)
    {
        if (s == nullptr)
            return;
        len = strlen(s);
        str = new char[len + 1];
        strcpy(str, s);
        str[strlen(s)] = '\0';
 
    }
    MyString()
    {
        len = 0;
        str = nullptr;
    }
    ~MyString()
    {
        //一定得判断str是否是空，要不删除一个空指针应该是不行的吧
        if (str)
            delete[]str;
    }
    MyString(const MyString& mys)
    {
        if (mys.str == nullptr)
            return;
        else
        {
            len = strlen(mys.str);
            str = new char[len + 1];
            strcpy(str, mys.str);
        }
    }
    friend ostream& operator<<(ostream& cout, const MyString& s)
    {
        if (s.str != nullptr)
            cout << s.str;
        return cout;
    }
    MyString& operator=(const MyString& mys)
    {
        if (mys.str == str)
            return *this;
        else
        {
            if (str)
                delete[]str;
            len = strlen(mys.str);
            str = new char[len + 1];
            strcpy(str, mys.str);
        }
        return *this;
    }
    MyString operator+(const MyString& mys)
    {
        if (mys.str == nullptr)
            return *this;
        MyString tempmys;
 
        tempmys.len =len + strlen(mys.str);
        tempmys.str = new char[tempmys.len + 1];
        strcpy(tempmys.str, str);
        strcat(tempmys.str, mys.str);
        return tempmys;
    }
    MyString operator+(const char* s)
    {
        MyString mys(s);
        return *this + mys;
    }
    friend MyString operator+(const char* s,  const MyString& rhs)
    {
        MyString mys(s);
        return mys + rhs;
    }
    MyString& operator+=(const char* s)
    {
        MyString mys(s);
        *this = *this + mys;
        return *this;
    } 
    MyString operator()(int i, int j)
    {
        MyString mys;
        mys.len = j;
        char* temps = new char[j+1];
        int start = 0;
        for (start = 0; start < j; start++)
            temps[start] = str[i + start];
        temps[start] = 0;
        mys.str = temps;
        return mys;
    }
 
    int operator<(const MyString& rhs)
    {
        if (strcmp(str, rhs.str) < 0)
            return true;
        else
            return false;
    }
    int operator==(const MyString& rhs)
    {
        if (strcmp(str, rhs.str) == 0)
            return true;
        else
            return false;
    }
    int operator>(const MyString& rhs)
    {
        if (strcmp(str, rhs.str) > 0)
            return true;
        else
            return false;
    }
    char& operator[](int i)
    {
        return str[i];
    }
};
int CompareString( const void * e1, const void * e2)
{
	MyString * s1 = (MyString * ) e1;
	MyString * s2 = (MyString * ) e2;
	if( * s1 < *s2 )
	return -1;
	else if( *s1 == *s2)
	return 0;
	else if( *s1 > *s2 )
	return 1;
}
int main()
{
	MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
	MyString SArray[4] = {"big","me","about","take"};
	cout << "1. " << s1 << s2 << s3<< s4<< endl;
	s4 = s3;
	s3 = s1 + s3;
	cout << "2. " << s1 << endl;
	cout << "3. " << s2 << endl;
	cout << "4. " << s3 << endl;
	cout << "5. " << s4 << endl;
	cout << "6. " << s1[2] << endl;
	s2 = s1;
	s1 = "ijkl-";
	s1[2] = 'A' ;
	cout << "7. " << s2 << endl;
	cout << "8. " << s1 << endl;
	s1 += "mnop";
	cout << "9. " << s1 << endl;
	s4 = "qrst-" + s2;
	cout << "10. " << s4 << endl;
	s1 = s2 + s4 + " uvw " + "xyz";
	cout << "11. " << s1 << endl;
	qsort(SArray,4,sizeof(MyString),CompareString);
	for( int i = 0;i < 4;i ++ )
	cout << SArray[i] << endl;
	//s1的从下标0开始长度为4的子串
	cout << s1(0,4) << endl;
	//s1的从下标5开始长度为10的子串
	cout << s1(5,10) << endl;
	return 0;
}