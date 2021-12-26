#ifndef BOOKSTORE_BOOKS_H
#define BOOKSTORE_BOOKS_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <iomanip>

using std::cout;
using std::endl;
using std::string;
using std::fixed;
using std::setprecision;

class Book{//存储每一本Book的信息
private:
    char ISBN[25] = "";
    char Book_Name[64] = "";
    char Author[64] = "";
    char Keyword[64];
    int Quantity = 0;
    //小数默认为固定为小数点后两位
    double Price = 0;
public:
    Book() = default;
    Book(string tmp_ISBN){
        strcpy(ISBN, tmp_ISBN.c_str());
    }
    int Get_Num(){
        return Quantity;
    }
    void Sub_Num(const int& num){
        Quantity -= num;
    }
    void Add_Num(const int& num){
        Quantity += num;
    }
    string Get_ISBN(){
        return ISBN;
    }
    string Get_Name(){
        return Book_Name;
    }
    string Get_Author(){
        return Author;
    }
    string Get_Key(){
        return Keyword;
    }
    double Get_Price(){
        return Price;
    }
    void Change_ISBN(const string& t){
        strcpy(ISBN, t.c_str());
    }
    void Change_Name(const string& t){
        strcpy(Book_Name, t.c_str());
    }
    void Change_Author(const string& t){
        strcpy(Author, t.c_str());
    }
    void Change_Key(const string& t){
        strcpy(Keyword, t.c_str());
    }
    void Change_Price(const double& t){
        Price = t;
    }
    Book& operator = (const Book& rhs){
        strcpy(ISBN, rhs.ISBN);
        strcpy(Book_Name, rhs.Book_Name);
        strcpy(Author, rhs.Author);
        strcpy(Keyword, rhs.Keyword);
        Quantity = rhs.Quantity;
        Price = rhs.Price;
        return *this;
    }
    bool operator < (const Book& rhs){
        int l_len = strlen(ISBN), r_len = strlen(rhs.ISBN), min_len;
        min_len = l_len <= r_len ? l_len : r_len;
        for(int i = 0; i < min_len; ++i)
            if(ISBN[i] != rhs.ISBN[i])
                return ISBN[i] < rhs.ISBN[i];
        return l_len < r_len;
    }
    friend std::ostream& operator << (std::ostream& os, const Book& tmp){
        os << tmp.ISBN << "\t" << tmp.Book_Name << "\t" << tmp.Author << "\t" << tmp.Keyword <<"\t";
        os << fixed << setprecision(2) << tmp.Price << "\t" << tmp.Quantity;
        return os;
    }
};
class Book_System{
private:
    Book Selected;
    MemoryRiver<Book> Book_Data;
    BlockList ISBN_Index;
    BlockList Name_Index;
    BlockList Author_Index;
    BlockList Keyword_Index;
public:
    Book_System() : Book_Data("book_data"), ISBN_Index("ISBN_index"), Name_Index("name_index")
                    , Author_Index("author_index"), Keyword_Index("keyword_index"){}
    void SplitKeyword(const string& str, vector<string>& ans){
        string tmp = "";
        for(int i = 0; i <= str.length(); ++i){
            if(i == str.length() || str[i] == '|'){
                ans.push_back(tmp);
                tmp.clear();
            }
            else{
                tmp += str[i];
            }
        }
        return;
    }
    void Show(Account_System& tmp_account) {
        if(tmp_account.Get_Now_Pri() < 1){
            cout << "Invalid" << endl;
            return;
        }
        vector<int> ans;
        ISBN_Index.FindAll(ans);
        Book tmp_book;
        if(ans.empty()){//输出空行
            cout << endl;
            return;
        }
        else{
            for(int i = 0; i < ans.size(); ++i){
                Book_Data.read(tmp_book, ans[i]);
                cout << tmp_book << endl;
            }
        }
    }
    void Show(Account_System& tmp_account, const string& tmp_index){
        if(tmp_account.Get_Now_Pri() < 1){
            cout << "Invalid" << endl;
            return;
        }
        vector<int> ans;
        Book tmp_book;
        string index = "";
        int pos;
        for(int i = 0; i < tmp_index.size(); ++i){
            if(tmp_index[i] == '='){
                pos = i;
                break;
            }
            else index += tmp_index[i];
        }
        string imf = "";
        if(index == "-ISBN"){
            for(int i = pos + 1; i < tmp_index.size(); ++i){
                imf += tmp_index[i];
            }
        }
        else{
            for(int i = pos + 2; i < tmp_index.size() - 1; ++i){
                imf += tmp_index[i];
            }
        }
        if(index == "-ISBN") {ISBN_Index.Find(imf, ans);}
        if(index == "-name") {Name_Index.Find(imf, ans);}
        if(index == "-author") {Author_Index.Find(imf, ans);}
        if(index == "-keyword") {Keyword_Index.Find(imf, ans);}
        if(ans.empty()){//输出空行
            cout << endl;
            return;
        }
        else{
            for(int i = 0; i < ans.size(); ++i){
                Book_Data.read(tmp_book, ans[i]);
                cout << tmp_book << endl;
            }
        }
    }
    bool Buy(Account_System& tmp_account, const string tmp_ISBN, const int& tmp_q, double& tot){
        if(tmp_account.Get_Now_Pri() < 1 || Selected.Get_ISBN() == ""){
            cout << "Invalid" << endl;
            return false;
        }
        vector<int> ans;
        Book tmp_book;
        ISBN_Index.Find(tmp_ISBN, ans);
        if(ans.empty()){
            cout << "Invalid" << endl;
            return false;
        }
        else{
            Book_Data.read(tmp_book, ans[0]);
            if(tmp_book.Get_Num() < tmp_q){
                cout << "Invalid" << endl;
                return false;
            }
            else{
                tot = tmp_q * tmp_book.Get_Price();
                tmp_book.Sub_Num(tmp_q);
                cout << fixed << setprecision(2) << tot << endl;
                Book_Data.update(tmp_book, ans[0]);
                return true;
            }
        }
    }
    void Select(Account_System& tmp_account, const string& tmp_ISBN){
        //3
        if(tmp_account.Get_Now_Pri() < 3){
            //权限不够
            cout << "Invalid" << endl;
            return;
        }
        vector<int> ans;
        ISBN_Index.Find(tmp_ISBN, ans);
        if(ans.empty()){//如果没有则创建
            Selected = Book(tmp_ISBN);
            int pos = 0;
            pos = Book_Data.write(Selected);
            ISBN_Index.Insert(Node(tmp_ISBN, pos));
        }
        else{
            Book_Data.read(Selected, ans[0]);
        }
    }
    void Modify(Account_System& tmp_account, const string& imf){
        //notice:这里的imf已经确保为单操作指令，不用考虑修改多个信息的情况
        if(Selected.Get_ISBN() == ""){
            cout << "Invalid" << endl;
            return;
        }
        string ty = "", new_imf = "";
        int pos = 0;
        for(int i = 0; i < imf.length(); ++i){
            if(imf[i] == '='){
                pos = i;
                break;
            }
            else ty += imf[i];
        }
        if(ty == "-ISBN" || ty == "-price"){
            for(int i = pos + 1; i < imf.length(); ++i){
                new_imf += imf[i];
            }
        }
        else{//去掉引号
            for(int i = pos + 2; i < imf.length() - 1; ++i){
                new_imf += imf[i];
            }
        }
        if(ty == "-ISBN"){
            string old_isbn = Selected.Get_ISBN();
            vector<int> old_ans, new_ans;
            ISBN_Index.Find(old_isbn, old_ans);
            ISBN_Index.Find(new_imf, new_ans);
            if(!new_ans.empty()){//与已有ISBN重复
                cout << "Invalid" << endl;
                return;
            }
            else{
                int pos = old_ans[0];////数组越界
                Selected.Change_ISBN(new_imf);
                Book_Data.update(Selected, pos);
                ISBN_Index.Delete(Node(old_isbn, pos));
                ISBN_Index.Insert(Node(new_imf, pos));
                return;
            }
        }
        if(ty == "-name"){
            string isbn = Selected.Get_ISBN(), old_name = Selected.Get_Name();
            vector<int> ans;
            int pos = 0;
            ISBN_Index.Find(isbn, ans);
            pos = ans[0];
            Selected.Change_Name(new_imf);
            Book_Data.update(Selected, pos);
            Name_Index.Delete(Node(old_name, pos));
            Name_Index.Insert(Node(new_imf, pos));
            return;
        }
        if(ty == "-author"){
            string isbn = Selected.Get_ISBN(), old_author = Selected.Get_Author();
            vector<int> ans;
            int pos = 0;
            ISBN_Index.Find(isbn, ans);
            pos = ans[0];
            Selected.Change_Author(new_imf);
            Book_Data.update(Selected, pos);
            Author_Index.Delete(Node(old_author, pos));
            Author_Index.Insert(Node(new_imf, pos));
            return;
        }
        if(ty == "-keyword"){
            string isbn = Selected.Get_ISBN();
            int pos;
            vector<int> ans;
            vector<string> old_key, new_key;
            ISBN_Index.Find(isbn, ans);
            pos = ans[0];
            SplitKeyword(Selected.Get_Key(), old_key);
            SplitKeyword(new_imf, new_key);
            Selected.Change_Key(new_imf);
            Book_Data.update(Selected, pos);
            for(int i = 0; i < old_key.size(); ++i){
                Keyword_Index.Delete(Node(old_key[i], pos));
            }
            for(int i = 0; i < new_key.size(); ++i){
                Keyword_Index.Insert(Node(new_key[i], pos));
            }
            return;
        }
        if(ty == "-price"){
            string isbn = Selected.Get_ISBN();
            vector<int> ans;
            double new_price = std::stod(new_imf);
            ISBN_Index.Find(isbn, ans);
            pos = ans[0];
            Selected.Change_Price(new_price);
            Book_Data.update(Selected, pos);
            return;
        }
    }
    bool Import(Account_System& tmp_account, const int& tmp_q, const double& tmp_tot){
        if(tmp_account.Get_Now_Pri() < 3 || Selected.Get_ISBN() == ""){
            cout << "Invalid" << endl;
            return false;
        }
        else{
            vector<int> ans;
            ISBN_Index.Find(Selected.Get_ISBN(), ans);
            Selected.Add_Num(tmp_q);
            Book_Data.update(Selected, ans[0]);
            return true;
        }
    }
};

#endif //BOOKSTORE_BOOKS_H
