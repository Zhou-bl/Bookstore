#include <iostream>
#include "Command.h"
using std::string;
int main(){
    //freopen("testcase5.txt","r",stdin);
    //freopen("Myans.txt","w",stdout);
    Command System;
    string cmd;

    int cnt = 0;

    while(getline(cin, cmd)){
        //对于每一条指令，先解析，再执行
        cnt++;
        //cout << cnt << endl;
        if(cmd.length() > 1024){//单次指令最大为1024
            cout << "Invalid" << endl;
            continue;
        }
        System.pre(cmd);
        System.get_cmd(cmd);
        System.run();
    }
    return 0;
}