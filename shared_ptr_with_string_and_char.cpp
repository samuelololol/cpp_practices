#include <iostream>
#include <string>
#include <tr1/memory>

#include <cstring>
#include <cstdlib>

using std::cout;
using std::endl;


std::tr1::shared_ptr<std::string> char_to_string(std::tr1::shared_ptr<std::string>);
void reuse_stringptr(std::tr1::shared_ptr<std::string>);
void string_to_char(std::tr1::shared_ptr<std::string>);
void string_concate(std::tr1::shared_ptr<std::string>);

int main()
{
    std::tr1::shared_ptr<std::string> ptr;
    cout << "counts of ptr: " << ptr.use_count() << endl;

    // char to string
    ptr = char_to_string(ptr);
    cout << "counts of ptr: " << ptr.use_count() << endl;

    // reuse shared string pointer
    reuse_stringptr(ptr);
    cout << "counts of ptr: " << ptr.use_count() << endl;

    // string to char
    string_to_char(ptr);
    cout << "counts of ptr: " << ptr.use_count() << endl;

    // string concate
    string_concate(ptr);
    cout << "counts of ptr: " << ptr.use_count() << endl;
    cout << "*ptr show in main: " << *ptr << endl;

    return 0;
}


std::tr1::shared_ptr<std::string> char_to_string(std::tr1::shared_ptr<std::string> strptr)
{
    cout << "================================================================================" << endl;
    strptr = std::tr1::shared_ptr<std::string>(new std::string("hahahaha"));
    cout << "address of strptr: " << strptr << ", strptr: " << *strptr << endl;
    *strptr = "ccccc";
    cout << "address of strptr: " << strptr << ", strptr: " << *strptr << endl;
    cout << "counts of strptr: " << strptr.use_count() << endl;
    return strptr;
}


void reuse_stringptr(std::tr1::shared_ptr<std::string> reuseptr1)
{
    cout << "================================================================================" << endl;
    cout << "address of reuseptr1: " << reuseptr1 << ", reuseptr1: " << *reuseptr1 << endl;
    cout << "counts of reuseptr1: " << reuseptr1.use_count() << endl;
}


void string_to_char(std::tr1::shared_ptr<std::string> reuseptr2)
{
    cout << "================================================================================" << endl;
    char* c = (char*)malloc(reuseptr2->size()*sizeof(char));
    strcpy(c, reuseptr2->c_str());
    cout << "address of c: " << &c << ", c: " << c << endl;
    free(c);

    cout << "address of reuseptr2: " << reuseptr2 << ", reuseptr2: " << *reuseptr2 << endl;
    cout << "address of reuseptr2.get(): " << reuseptr2.get() << endl;
}


void string_concate(std::tr1::shared_ptr<std::string> reuseptr3)
{
    cout << "================================================================================" << endl;
    std::string to_concate_string("_postfix");
    cout << "address of to_concate_string: " << &to_concate_string << ", to_concate_string: " << to_concate_string << endl;
    *reuseptr3 = *reuseptr3 + to_concate_string;
    cout << "address of reuseptr3: " << reuseptr3 << ", reuseptr3: " << *reuseptr3 << endl;
}

