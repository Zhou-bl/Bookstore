# Bookstore开发文档👨‍💻

## 1️⃣文档相关说明

本文档为周秉霖所写Bookstore开发文档，将由陆逸凡实现，大致地说明了程序的框架结构及实现思路，包含实现Bookstore所需的Account_System，Book_System,Log_System,Command_System四个大类。在代码具体实现时可能会有与文档不符的情况，可以适当修改开发文档以便于实现。

## 2️⃣代码风格与变量命名规范

**常量**：由下划线构成的复合（或不复合）单词表示，每个单词首字母大写，例如：

```c++
const int Maxn = 1e5;
const int Maxn_Book = 19260817;
```

**类名**：由下划线构成的复合（或不复合）单词表示，每个单词首字母大写，例如：

```c++
class Account_Systerm{
  private:
    //todo:Add some varible.
  public:
    //todo:Add some function.
};
class Book{
    private:
    //todo:Add some varible.
  public:
    //todo:Add some function.
};
```

**成员变量**：以下划线开头构成的复合(或不复合)的英文字母构成。例如：

```c++
class Book{
    private:
    std::string _ISBN,_Book_Name,_Author;
    int _Price;
}
```

**成员函数名**：由下划线构成的能大致表示函数行为的复合词（或非复合）表示。为了更好地与变量区分，函数名开头不加下划线，且函数名全由小写字母表示。例如：

```c++
class Book{
    private://todo
    public:
    void show_information(string ISBN = "",string Name = "",string Author = "",string KeyWord[]){
        //todo:
    }
};
```

**形参变量**：双峰型变量，可参考上方  show_information 的形参。

**其他变量**：不做具体要求，但要和成员变量，成员函数名区分开。例如：

```c++
std::string tmp_name,tmp_ISBN;
int tmp_price;
```



## 3️⃣程序实现大致思路

首先，程序的实现依托于我们所涉及的四个大系统：(account_system，book_system,log_system,command_system)。由 command_systerm 读取指令然后下派到操作对应的其他三个系统实现。

### 图书系统

```c++
//Book_System:接口文件：book_systerm.h
#ifndef BOOKSTORE_BOOKDATABASE_H
#define BOOKSTORE_BOOKDATABASE_H

#include <set>
#include <unordered_map>
using std::string;
const int Maxn = 1e5;
class Book_System{
private:
    class Book{//创建一个Book类维护每一本Book的信息
    private:
        string _ISBN,_Book_Name,_Author,_Keyword[Maxn];
        int _Quantity,_Book_NO;
        double _Price,_Total_cost;
    public:
        Book(){
            _Price = _Total_cost = 0;
            _Quantity = 0;
        }
    }
    //todo:维护有序性
    //可能会用到
    set<string> _Book_List;
    unordered_map<string,Book> _Book_Map;

public:
    void show(string ISBN = "",string Name = "",string Author = "",string KeyWord[]){
        //todo:legal or not?
        if (KeyWord[]) {}
        if (ISBN != "") {}
        if (Name != "") {}
    }
    void buy(string ISBN,const int Quantity){
        
    }
    void select(string ISBN){

    }
    void modify(string ISBN = "",string Name = "",string Author = "",string KeyWord = "",double Price = 0){

    }
    void import(int Quantity,double TotalCost){
    }
}

#endif //BOOKSTORE_BOOKDATABASE_H
```

****

### 账户系统

```c++
//Account_System:接口文件：account_sysyem.h
#ifndef CODE_LAST_HOMEWORK_H
#define CODE_LAST_HOMEWORK_H
#include<unordered_map>
#include<fstream>
class Account_system {
    struct User_Account{
        string _User_ID;
        string _User_Name;
        string Password;
        short int Priority;
        bool Login;
        int Cnt;
    };
    string _User_id;
public:
    void su(command Op,string UserId,string PasswordTry) ;
    void log_out(command Op);
    void register(command Op,string UserId,string Password,string UserName);
    void passwd(command Op,string UserId,string Old_Password,string New_Password);
    void user_add(command a,string UserId,string Password,short int Priority,string User_Name);
    void delete(command a,string UserId);
private:
    unordered_map(std::string,UserAccount);
};
#endif //CODE_LAST_HOMEWORK_H
```

### 日志系统

```c++
//Log_System:接口文件：log_system.h
#ifndef HOMEWORK6_TMP_H
#define HOMEWORK6_TMP_H

#include <vector>
#include <string>
#include <unordered_map>
#include <set>
using std::unordered_map;
using std::set;
using std::vector;
using std::string;
using std::cout;
const int Maxn = 1e5;
class log_system{
private:
    int _Time;
    string _Record_Op[Maxn];
    vector<double> _Finance;
    unordered_map<string, vector<string>> _Employee_Op;
    unordered_map<string, vector<string>> _Customer_Op;
    vector<string> _Owner_Op;
public:

    Log() : Time(0){}
    void report_op(const string& name){}//todo:员工操作记录指令
    void show_finance(const int& t){}//todo:财务记录查询
    void report_finance(){}//todo:财务记录报告
    void report_employee(){}//todo:遍历map，输出全体员工的所有操作记录
    void report_customer(){}//todo:顾客
    void report_owner(){}//todo：店主
    void log(){//todo:生成日志
        report_finance();
        report_employee();
        report_customer();
        report_owner();
    }
};

#endif //HOMEWORK6_TMP_H
```



## 4️⃣其他待完善内容

//todo:

