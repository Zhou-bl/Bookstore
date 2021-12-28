//
// Created by zbl on 2021/12/26.
//

#ifndef BOOKSTORE_LOG_H
#define BOOKSTORE_LOG_H

#include <iostream>
#include <iomanip>

class FinanceLog{//一个对象表示一次交易
private:
    bool ty = 0;//表示buy or import 0表示buy(收入)， 1表示import(支出)
    double tot = 0;//正数，该笔交易额
public:
    bool Get_ty(){
        return ty;
    }
    double Get_tot(){
        return tot;
    }
    FinanceLog() = default;
    FinanceLog(const bool& type, const double& num):ty(type), tot(num){}
    FinanceLog& operator = (const FinanceLog& rhs){
        ty = rhs.ty;
        tot = rhs.tot;
        return *this;
    }
};
class Log_System{
private:
    int tot_time;
    FinanceLog cur;
    MemoryRiver<FinanceLog> Log_Data;
    int sizeofF = sizeof(FinanceLog);
public:
    Log_System():Log_Data("log_data"){}
    void show(Account_System& tmp_account){
        if(tmp_account.Get_Now_Pri() < 7){
            cout << "Invalid\n";
            return;
        }
        double income = 0, outcome = 0;
        Log_Data.get_info(tot_time, 1);
        for(int i = 8; i <= 8 + (tot_time - 1) * sizeofF; i += sizeofF){
            Log_Data.read(cur, i);
            if(!cur.Get_ty()){
                income += cur.Get_tot();
            }
            else{
                outcome += cur.Get_tot();
            }
        }
        cout << fixed << std::setprecision(2)<< "+ " << income << " - " << outcome << endl;
    }
    void show(Account_System& tmp_account, const int& num){
        if(tmp_account.Get_Now_Pri() < 7){
            cout << "Invalid\n";
            return;
        }
        if(!num){
            cout << endl;
            return;
        }
        double income = 0, outcome = 0;
        Log_Data.get_info(tot_time, 1);
        if(num > tot_time){
            cout << "Invalid\n";
            return;
        }
        for(int i = 8 + (tot_time - 1) * sizeofF; i >= 8 + (tot_time - num) * sizeofF; i -= sizeofF){
            Log_Data.read(cur, i);
            if(!cur.Get_ty()){
                income += cur.Get_tot();
            }
            else{
                outcome += cur.Get_tot();
            }
        }
        cout << fixed << std::setprecision(2)<< "+ " << income << " - " << outcome << endl;
    }
    void add_finance(const string& type, const double& num){
        if(type == "buy"){
            cur = FinanceLog(0, num);
            Log_Data.write(cur);
        }
        else{
            cur = FinanceLog(1, num);
            Log_Data.write(cur);
        }
    }
};

#endif //BOOKSTORE_LOG_H
