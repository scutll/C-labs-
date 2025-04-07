#pragma once
#include <string>
#define MAX 1000
#include <iostream>
#include <fstream>
using std::cout, std::endl, std::cin;
using std::fstream;
using std::string;



//图书馆中一类藏书的所有信息
class BookRecord{
    private:
    string book_id;
    string book_title;
    string author_first_name;
    string author_last_name;
    int year;
    int number_of_copies;   //总副本数
    int available_copies;
public:
    string get_id() const { return book_id;}
    BookRecord(string id, string title, string author_f, string author_l, int year_, int copies) : book_id(id), book_title(title), author_first_name(author_f), author_last_name(author_l),year(year_),number_of_copies(copies), available_copies(copies){}
    BookRecord() {}
    void show_book() const;
    bool exam_id();
    bool available() const{
        return available_copies > 0;
    }

    void save(fstream& fout);
    void load(fstream& fin);
    void borrowed() { available_copies--; }
};


class Catalogue{
    private:
    int record_of_books;
    BookRecord* (records[MAX]);


    public:
    Catalogue():record_of_books(0){}
    // ~Catalogue();
    void show() const;    //展示所有信息
    bool add_book(BookRecord);
    bool have_book(const string);

    int books_num() { return record_of_books; }
    //在保证有书本的前提下调用
    BookRecord& check_book(const string bookID) const;

    void save(fstream& fout);
    void load(fstream &fin);
};

class Borrower{
private:
    int id;
    string first_name;
    string last_name;
    int borrow_nums;
    string *(book_ids[MAX]);

public:
    void set_borrow_num(int n) { borrow_nums = n;}
    // ~Borrower();
    Borrower(int id_,const string last,const string first):id(id_),last_name(last),first_name(first),borrow_nums(0){}
    void borrow_book(string book_id);   //将id添加到ids里面，是否有该书或id是否规范由Library判断
    void show_borrower() const;
    string books_id(int i) { return *(book_ids[i]);}
    int borrowed() { return borrow_nums; }

    void save(fstream& fout);
    void load(fstream& fin);
};



class Library{
    private:
        int record_book;    //拥有的书籍总数
        int book_borrowed;  //借出数
        int borrowers;
        Catalogue books;
        Borrower* (readers[MAX]);
    public:
        // ~Library();
        Library():book_borrowed(0),record_book(0),borrowers(0){}
        bool add_borrower(int,string, string);
        bool add_borrower(Borrower reader);
        bool add_book(BookRecord);
    
        bool borrow_book(Borrower&,const string book_id);
    
        void show() const;
        void save(const string path);
        void load(const string path);
    };
    