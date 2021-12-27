#include <iostream>
#include <cstdio>
#include "Command.h"
using namespace std;
int main(){
//    freopen("1.in","r",stdin);
//    freopen("Myans.txt","w",stdout);
    Command BookstoreSystem;
    string cmd;

    int cnt = 0;

    while(getline(cin, cmd)){
        //对于每一条指令，先解析，再执行
//        cnt++;
//        cout << cnt << endl;
        if(cmd.length() > 1024){//单次指令最大为1024
            cout << "Invalid" << endl;
            continue;
        }
        BookstoreSystem.pre(cmd);
        BookstoreSystem.get_cmd(cmd);
        BookstoreSystem.run();
    }
    return 0;
}