#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <fstream>
#include "Command.h"
#include "Blocks.h"
using std::string;
int main(){
    Command System;
    string cmd;
    while(getline(cin, cmd)){
        //对于每一条指令，先解析，再执行
        System.get_cmd(cmd);
        System.run();
    }
    return 0;
}