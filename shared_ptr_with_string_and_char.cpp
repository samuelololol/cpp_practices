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
void string_indexing(std::tr1::shared_ptr<std::string>);
void string_operation(std::tr1::shared_ptr<std::string>);


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

    // string indexing
    string_indexing(ptr);

    // string indexing
    string_operation(ptr);
    return 0;
}


std::tr1::shared_ptr<std::string> char_to_string(std::tr1::shared_ptr<std::string> strptr)
{
    cout << "================================================================================" << endl;
    strptr = std::tr1::shared_ptr<std::string>(new std::string("hahahaha"));
    cout << "address of strptr: " << strptr << ", strptr: " << *strptr << endl;
    //*strptr = "ccccc";
    strptr->assign("ccccccc");
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


void string_indexing(std::tr1::shared_ptr<std::string> reuseptr4)
{
    cout << "================================================================================" << endl;
    for (int i=0; i < reuseptr4->size(); i++){
        cout << "index: " << i << ", value: " << (*reuseptr4)[i] << endl;
    }
}


void string_operation(std::tr1::shared_ptr<std::string> reuseptr5)
{
    cout << "================================================================================" << endl;
    // 0123456789....
    // ccccccc_postfix
    //                 substr(start, len)
    cout << reuseptr5->substr(6,3) << endl;
    //                      assign(str, start, len)
    *reuseptr5 = reuseptr5->assign(*reuseptr5, 3, 9);
    cout << *reuseptr5 << endl;
    //                      append(str, start, len)
    *reuseptr5 = reuseptr5->append(*reuseptr5, 0, 9);
    cout << *reuseptr5 << endl;
    //                      insert(pos, str)
    *reuseptr5 = reuseptr5->insert(9, "[_append_]");
    cout << *reuseptr5 << endl;
    cout << "find: c_" << reuseptr5->find("c_") << endl;
    cout << "length: " << reuseptr5->length() << endl;
    cout << "size: " << reuseptr5->size() << endl;
    //cout << "*reuseptr5: " << *reuseptr5 << endl;
    std::string copied_string = std::string(*reuseptr5);
    cout << "operator== : " << (copied_string == *reuseptr5) << endl;

}
