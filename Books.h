#ifndef BOOKSTORE_BOOKS_H
#define BOOKSTORE_BOOKS_H

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;

class Book{//存储每一本Book的信息
private:
    char ISBN[25] = "";
    char Book_Name[65] = "";
    char Author[65] = "";
    char Keyword[65] = "";
    int Quantity = 0;
    //小数默认为固定为小数点后两位
    double Price = 0;
    double Total_Cost = 0;
};
class Book_System{
private:

};

#endif //BOOKSTORE_BOOKS_H
