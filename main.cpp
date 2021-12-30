#include <iostream>
#include "Command.h"
#include "Exception.h"
using namespace std;
int main(){
//    freopen("test.txt","r",stdin);
//    freopen("Myans.txt","w",stdout);
    Command BookstoreSystem;
    string cmd;

    int cnt = 0;

    while(getline(cin, cmd)){
        //对于每一条指令，先解析，再执行
//        cmd = " \t\n    \t\n";
//        cnt++;
//        cout << cnt << endl;
        try{
            BookstoreSystem.pre(cmd);
            BookstoreSystem.get_cmd(cmd);
            BookstoreSystem.run();
        }
        catch (Exception){
            cout << "Invalid\n";
        }
    }
    return 0;
}