//
// Created by zbl on 2021/12/18.
//

#ifndef BOOKSTORE_ACCOUNT_H
#define BOOKSTORE_ACCOUNT_H

#include <stack>
#include <iostream>
#include <string>
#include "Blocks.h"

using std::cin;
using std::string;
using std::cout;
using std::endl;
using std::stack;

struct User_Account{
    char User_ID[32] = "";
    char User_Name[32] = "";
    char PassWord[32] = "";
    int Priority = 0; //默认为0
    User_Account() = default;
    User_Account(const string& tmp_ID, const string& tmp_PW, const int& tmp_p, const string tmp_name = ""){
        strcpy(User_ID, tmp_ID.c_str());
        strcpy(User_Name, tmp_name.c_str());
        strcpy(PassWord, tmp_PW.c_str());
        Priority = tmp_p;
    }
};

class Account_System{
private:
    vector<User_Account> Log_Stack;
    BlockList Account_Index;//存储信息在存储文件中的位置
    MemoryRiver<User_Account> Account_Data;//存储账户信息
public:
    Account_System(): Account_Index("account_index"), Account_Data("account_data"){}
    //for de_bug:
    void Get_Size(){
        cout << "Size: " << Log_Stack.size() << endl;
    }
    void init(){//创建超级用户
        vector<int> tmp;
        Account_Index.Find("root", tmp);
        if(tmp.empty()){
            User_Account rt("root", "sjtu", 7);
            int pos = 0;
            pos = Account_Data.write(rt);
            Account_Index.Insert(Node("root", pos));
        }
    }
    int Get_Now_Pri(){
        if(Log_Stack.empty()) return 0;
        return Log_Stack.back().Priority;
    }
    void Quit(){
        while(!Log_Stack.empty())
            Log_Stack.pop_back();
    }
    void Login(const string& tmp_ID, const string& tmp_Password){
        //0
        vector<int> tmp;
        User_Account Selected;
        Account_Index.Find(tmp_ID, tmp);
        if(tmp.empty()){
            cout << "Invalid" << endl;
            return;
        }
        Account_Data.read(Selected, tmp[0]);
        if(!Log_Stack.empty() && Log_Stack.back().Priority > Selected.Priority){
            Log_Stack.push_back(Selected);
            return;
        }
        if(tmp_Password == Selected.PassWord){
            Log_Stack.push_back(Selected);
            return;
        }
        else{
            cout << "Invalid" << endl;
        }
    }
    void Logout(){
        //1
        if(Log_Stack.empty()){
            cout << "Invalid" << endl;
            return;
        }
        Log_Stack.pop_back();
    }
    void Register(const string& tmp_ID, const string& tmp_Password, const string& tmp_Name){
        //0
        //注册的账户的权限等级为1
        vector<int> ans;
        Account_Index.Find(tmp_ID, ans);
        if(!ans.empty()){
            //重复的ID，注册失败
            cout << "Invalid" << endl;
            return;
        }
        User_Account new_account(tmp_ID, tmp_Password, 1, tmp_Name);
        int pos = Account_Data.write(new_account);
        Account_Index.Insert(Node(tmp_ID, pos));
    }
    void Passwd(const string& tmp_ID, const string& tmp_NPW, const string& tmp_OPW){
        //1
        if(Log_Stack.empty() || Log_Stack.back().Priority < 1){
            //权限不够
            cout << "Invalid" << endl;
            return;
        }
        vector<int> ans;
        User_Account Selected;
        Account_Index.Find(tmp_ID, ans);
        if(ans.empty()){
            //账户不存在
            cout << "Invalid" << endl;
            return;
        }
        Account_Data.read(Selected, ans[0]);
        if(Log_Stack.back().Priority == 7){//超级用户
            strcpy(Selected.PassWord, tmp_NPW.c_str());
            Account_Data.update(Selected, ans[0]);
        }
        else{//非超级用户
            if(tmp_OPW != Selected.PassWord){
                //密码不正确
                cout << "Invalid" << endl;
                return;
            }
            else{
                strcpy(Selected.PassWord, tmp_NPW.c_str());
                Account_Data.update(Selected, ans[0]);
            }
        }
    }
    void Useradd(const string& tmp_ID, const string& tmp_PW, const int& tmp_Pri, const string& tmp_Name){
        //3
        //注意：创建用户的权限要小于当前账户
        vector<int> ans;
        Account_Index.Find(tmp_ID, ans);
        if(!ans.empty()){
            //用户名重复
            cout << "Invalid" << endl;
            return;
        }
        if(Log_Stack.empty() || Log_Stack.back().Priority <= tmp_Pri){
            //权限不够
            cout << "Invalid" << endl;
            return;
        }
        User_Account new_account(tmp_ID, tmp_PW, tmp_Pri, tmp_Name);
        int pos = Account_Data.write(new_account);
        Account_Index.Insert(Node(tmp_ID, pos));
    }
    void Delete(const string& tmp_ID){
        //7
        if(Log_Stack.empty() || Log_Stack.back().Priority < 7){
            //权限不够
            cout << "Invalid" << endl;
            return;
        }
        vector<int> ans;
        Account_Index.Find(tmp_ID, ans);
        if(ans.empty()){
            //账户不存在
            cout << "Invalid" << endl;
            return;
        }
        bool flag = 0;
        for(int i = 0; i < Log_Stack.size(); ++i){
            if(Log_Stack[i].User_ID == tmp_ID){
                flag = 1;
                break;
            }
        }
        if(flag){
            //正在登录栈中
            cout << "Invalid" << endl;
            return;
        }
        Account_Index.Delete(Node(tmp_ID, ans[0]));
        Account_Data.Delete(ans[0]);
    }
};

#endif //BOOKSTORE_ACCOUNT_H
