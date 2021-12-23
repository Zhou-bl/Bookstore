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
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

class Command{//中枢系统，完成以下任务 1.指令的合法性的检查。2.指令的解析。 3.指令的运行。
private:
    vector<string> Pars_Op;//记录解析后的操作
    Account_System AccountSystem;
public:
    Command(){
        AccountSystem.init();
    }
    void get_cmd(const string& cmd){
        Pars_Op.clear();
        string tmp_op = "";
        int len = cmd.length();
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
        if(Pars_Op[0] == "quit"){
            //todo:退出登录
            return;
        }
        if(Pars_Op[0] == "exit"){
            //todo
            return;
        }

        // #账户系统指令
        if(Pars_Op[0] == "su"){
            if(Pars_Op.size() == 3) AccountSystem.Login(Pars_Op[1], Pars_Op[2]);
            else AccountSystem.Login(Pars_Op[1]);
            return;
        }
        if(Pars_Op[0] == "logout"){
            AccountSystem.Logout();
            return;
        }
        if(Pars_Op[0] == "register"){
            AccountSystem.Register(Pars_Op[1], Pars_Op[2], Pars_Op[3]);
            return;
        }
        if(Pars_Op[0] == "passwd"){
            if(Pars_Op.size() == 3){//无密码
                AccountSystem.Passwd(Pars_Op[1], Pars_Op[2]);
            }
            else{//需要密码
                AccountSystem.Passwd(Pars_Op[1], Pars_Op[2], Pars_Op[3]);
            }
            return;
        }
        if(Pars_Op[0] == "useradd"){
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
        if(Pars_Op[0] == "show" && Pars_Op[1] == "-ISBN"){
            //todo
            return;
        }
        if(Pars_Op[0] == "buy"){
            //todo:
            return;
        }
        if(Pars_Op[0] == "select"){
            //todo
            return;
        }
        if(Pars_Op[0] == "modify"){
            //todo
            return;
        }
        if(Pars_Op[0] == "import"){
            //todo
            return;
        }

        // #日志系统指令
        if(Pars_Op[0] == "report"){
            //todo
            return;
        }
        if(Pars_Op[0] == "show" && Pars_Op[1] == "finance"){
            //todo
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
    }
};

#endif //BOOKSTORE_COMMAND_H
