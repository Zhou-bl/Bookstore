//
// Created by zbl on 2021/12/18.
//

#ifndef BOOKSTORE_COMMAND_H
#define BOOKSTORE_COMMAND_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "Account.h"
#include "Books.h"
#include "Log.h"

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

class Command{//中枢系统，完成以下任务 1.指令的合法性的检查。2.指令的解析。 3.指令的运行。
private:
    vector<string> Pars_Op;//记录解析后的操作
    Account_System AccountSystem;
    Book_System BookSystem;
    Log_System LogSystem;
public:
    Command(){//创建超级用户
        AccountSystem.init();
    }
    void pre(string& cmd){//去除多余的空格
        //0.若为空字符串,则什么也不干
        if(cmd == ""){
            cmd = " ";
            return;
        }
        //1.若全为空白(多个空格)
        bool Is_Blank = 1;
        for(int i = 0; i < cmd.length(); ++i)
            if(cmd[i] != ' '){
                Is_Blank = 0;
                break;
            }
        if(Is_Blank){
            cmd = " ";
            return;
        }

        //2.不全为空白，需要处理行首行末的空格以及多余的空格
        int len = cmd.length(), l, r;
        bool *book = new bool[len];
        for(int i = 0; i < len; ++i)
            book[i] = 0;
        for(int i = 0; i < len; ++i)
            if(cmd[i] != ' '){
                l = i;
                break;
            }
        for(int i = len - 1; i >= 0; --i)
            if(cmd[i] != ' '){
                r = i;
                break;
            }
        for(int i = l + 1; i <= r; ++i)
            if(cmd[i] == ' ' && cmd[i - 1] == ' '){
                book[i] = 1;
            }
        string new_cmd = "";
        for(int i = l; i <= r; ++i){
            if(!book[i]) new_cmd += cmd[i];
        }
        delete []book;
        cmd = new_cmd;
        return;
    }
    void get_cmd(const string& cmd){
        Pars_Op.clear();
        string tmp_op = "";
        int len = cmd.length();
        if(cmd == " "){
            Pars_Op.push_back(" ");
            return;
        }
        for(int i = 0; i <= len; ++i){
            if(i == len || cmd[i] == ' '){//遇到空格则取出命令
                Pars_Op.push_back(tmp_op);
                tmp_op.clear();
            }
            else{
                tmp_op += cmd[i];
            }
        }
    }
    void run(){//解析完命令开始运行命令
        // #基础指令
//        AccountSystem.Get_Size();
        if(Pars_Op.size() == 1 && Pars_Op[0] == " ")//仅有空白的指令是合法的
            return;
        if(Pars_Op[0] == "quit" || Pars_Op[0] == "exit"){
            if(Pars_Op.size() > 1){
                cout << "Invalid" << endl;
                return;
            }
            else{
                AccountSystem.Quit();
                return;
            }
        }

        // #账户系统指令
        if(Pars_Op[0] == "su"){
            if(Pars_Op.size() == 3)
                AccountSystem.Login(Pars_Op[1], Pars_Op[2]);
            else
                AccountSystem.Login(Pars_Op[1], "");
            return;
        }
        if(Pars_Op[0] == "logout"){
            AccountSystem.Logout();
            return;
        }
        if(Pars_Op[0] == "register"){
            if(Pars_Op.size() != 4){
                cout << "Invalid" << endl;
                return;
            }
            AccountSystem.Register(Pars_Op[1], Pars_Op[2], Pars_Op[3]);
            return;
        }
        if(Pars_Op[0] == "passwd"){
            if(Pars_Op.size() == 3){//无密码
                AccountSystem.Passwd(Pars_Op[1], Pars_Op[2], "");
            }
            else{//需要密码
                AccountSystem.Passwd(Pars_Op[1], Pars_Op[3], Pars_Op[2]);
            }
            return;
        }
        if(Pars_Op[0] == "useradd"){
            if(Pars_Op.size() != 5){
                cout << "Invalid" << endl;
                return;
            }
            int pri = 0;
            for(int i = 0; i < Pars_Op[3].length(); ++i){
                pri = pri * 10 + Pars_Op[3][i] - '0';
            }
            AccountSystem.Useradd(Pars_Op[1], Pars_Op[2], pri, Pars_Op[4]);
            return;
        }
        if(Pars_Op[0] == "delete"){
            AccountSystem.Delete(Pars_Op[1]);
            return;
        }

        // #图书系统指令
        if(Pars_Op[0] == "show" && ( Pars_Op.size() == 1 || Pars_Op[1] != "finance")){
            if(Pars_Op.size() == 1){
                BookSystem.Show(AccountSystem);
                return;
            }
            if(Pars_Op.size() == 2){
                BookSystem.Show(AccountSystem, Pars_Op[1]);
                return;
            }
            else{
                cout << "Invalid" << endl;
                return;
            }
        }
        if(Pars_Op[0] == "buy"){
            if(Pars_Op.size() != 3){
                cout << "Invalid" << endl;
                return;
            }
            int num = 0;
            for(int i = 0; i < Pars_Op[2].length(); ++i){
                num = num * 10 + Pars_Op[2][i] - '0';
            }
            double tot;
            bool flag = BookSystem.Buy(AccountSystem, Pars_Op[1], num, tot);
            if(flag){
                LogSystem.add_finance(Pars_Op[0], tot);
            }
            return;
        }
        if(Pars_Op[0] == "select"){
            if(Pars_Op.size() != 2){
                cout << "Invalid" << endl;
                return;
            }
            BookSystem.Select(AccountSystem, Pars_Op[1]);
            return;
        }
        if(Pars_Op[0] == "modify"){
            //todo：check the invalid！！！
            //如未选中图书则操作失败
            //有重复附加参数为非法指令
            //附加参数内容为空则操作失败
            //[keyword] 包含重复信息段则操作失败
            //与已有ISBN冲突
            if(AccountSystem.Get_Now_Pri() < 3){
                cout << "Invalid" << endl;
                return;
            }
            for(int i = 1; i < Pars_Op.size(); ++i){
                BookSystem.Modify(AccountSystem, Pars_Op[i]);
            }
            return;
        }
        if(Pars_Op[0] == "import"){
            if(Pars_Op.size() != 3){
                cout << "Invalid" << endl;
                return;
            }
            int q;
            double p;
            q = std::stoi(Pars_Op[1]);
            p = std::stod(Pars_Op[2]);
            bool flag = BookSystem.Import(AccountSystem, q, p);
            if(flag){
                LogSystem.add_finance(Pars_Op[0], p);
            }
            return;
        }

        // #日志系统指令
        if(Pars_Op[0] == "report"){
            //todo
            return;
        }
        if(Pars_Op[0] == "show" && Pars_Op[1] == "finance"){
            if(Pars_Op.size() != 2 && Pars_Op.size() != 3){
                cout << "Invalid" << endl;
                return;
            }
            if(Pars_Op.size() == 2){
                LogSystem.show();
            }
            else{
                int t = std::stoi(Pars_Op[2]);
                LogSystem.show(t);
            }
            return;
        }
        if(Pars_Op[0] == "report" && Pars_Op[1] == "finance"){
            //todo
            return;
        }
        if(Pars_Op[0] == "report" && Pars_Op[1] == "employee"){
            //todo
            return;
        }
        if(Pars_Op[0] == "log"){
            //todo
            return;
        }
        //仍然不返回说明指令不合法
        //todo:处理不合法的指令
        cout << "Invalid\n";
        return;
    }
};

#endif //BOOKSTORE_COMMAND_H
