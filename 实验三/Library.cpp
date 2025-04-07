#include "Library.h"

bool BookRecord::exam_id(){
    return book_id[0] <= 'Z' && book_id[0] >= 'A' 
    && book_id[1]>='1' && book_id[1]<='2';
}

bool Catalogue::add_book(BookRecord book){
    if(!book.exam_id()){
        cout << "book id not formatted : Uppersized and 1 or 2!" << endl;
        return false;
    }
    if (record_of_books == MAX)
        return false;

    records[record_of_books++] = new BookRecord(book);
    return true;

}

// Catalogue::~Catalogue(){
//     while(record_of_books--){
//         int i = record_of_books - 1;
//         delete records[i];
//     }
// }

bool Catalogue::have_book(const string id){
    int cnt = 0;
    while(cnt != record_of_books && records[cnt] != nullptr){
        if(records[cnt++]->get_id() == id)
            return true;
    }
    return false;
}

void BookRecord::show_book() const{
    cout << "Book ID: " << book_id << endl
         << "Title: " << book_title << endl
         << "Author: " << author_first_name << " " << author_last_name << endl
         << "Year published: " << year << endl
         << "Total number of copies: " << number_of_copies << endl
         << "Number available for loan: " << available_copies << endl;
}

void Borrower::show_borrower() const{
    cout << "Name: " << first_name << " " << last_name << endl
         << "Number of loaned books: " << borrow_nums << endl
         << "IDs of books on loan: ";
    int cnt = 0;
    while(cnt != borrow_nums && book_ids[cnt] != nullptr){
        cout << *(book_ids[cnt++]) << " ";
    }
    cout << endl;
}

void Borrower::borrow_book(string book_id){
    book_ids[borrow_nums++] = new string(book_id);

}

// Borrower::~Borrower(){
//     while(borrow_nums--){
//         int i = borrow_nums - 1;
//         delete book_ids[i];
//     }
// }

BookRecord& Catalogue::check_book(const string bookID) const{
    int cnt = 0;
    while(cnt != record_of_books && records[cnt] != nullptr){
        if(records[cnt]->get_id() == bookID)
            return *(records[cnt]);
        cnt++;
    }

    return *(records[cnt]);
}

void Catalogue::show() const{
    int cnt = 0;
    for (cnt = 0; cnt < record_of_books; cnt++){
        cout << "Book Record " << cnt << endl;

        for (int c = 0; c < 20;c++)
            cout << "=";
        cout << endl;

        records[cnt]->show_book();
    }
    cout << endl;
}

bool Library::add_book(BookRecord book){
    if(!books.add_book(book)){
        return false;
    }
    record_book++;
    return true;
}

bool Library::add_borrower(int id,string firstname,string lastname){
    Borrower man(id,lastname, firstname);
    if (id > 99999 || id < 10000){
        cout << "id contains 5 numbers!" << endl;
        return false;
    }
    if(borrowers < MAX && readers[borrowers] == nullptr){readers[borrowers++] = new Borrower(man);
            return true;
    }
    else{
        return false;
    }
}

void Library::show() const{
    //Books
    books.show();

    //Readers
    int cnt = 0;
    while(cnt != borrowers && readers[cnt] != nullptr){
        cout << "Reader Record: " << cnt << endl;
        for (int i = 0; i < 20;i++)
            cout << "=";
        cout << endl;
        readers[cnt++]->show_borrower();
    }
    cout << endl;
}

bool Library::borrow_book(Borrower& reader,const string book_id){
    if(!books.have_book(book_id)){
        cout << "book not in Library, add it first!" << endl;
        return false;
    }

    BookRecord& book = books.check_book(book_id);
    if(!book.available()){
        cout << "no available copies for book " << book_id << endl;
        return false;
    }

    reader.borrow_book(book_id);
    book_borrowed++;
    book.borrowed();
    return true;
}

bool Library::add_borrower(Borrower reader){
    if(borrowers < MAX && readers[borrowers] == nullptr){
        readers[borrowers] = new Borrower(reader);
        
        //录入reader借了的书本
        int cnt = 0;
        int max = readers[borrowers]->borrowed();
        readers[borrowers]->set_borrow_num(0);
        while(cnt != max && readers[borrowers] != nullptr){
            borrow_book(*readers[borrowers],readers[borrowers]->books_id(cnt));
            cnt++;
        }
        
        borrowers++;
        return true;
    }
    else{
        return false;
    }
}

// Library::~Library(){
//     while(borrowers--){
//         int i = borrowers - 1;
//         delete readers[i];
//     }
// }


BookRecord read_book_info_from_type(){
    string id,title,name_f,name_l;
    int year, copies;

    cin >> id >> title >> name_f >> name_l >> year >> copies;
    BookRecord book(id, title, name_f, name_l, year, copies);
    return book;
}

Borrower read_borrower_info_from_type(){
    string last, first;
    int id,borrow_nums;
    string ids[MAX];

    cin >> id >> first >> last >> borrow_nums;
    Borrower man(id, last, first);

    for (int i = 0; i < borrow_nums;i++){
        cin >> ids[i];
        man.borrow_book(ids[i]);
    }

    return man;
}

void Library::save(const string path){

    cout << "saving: " << path << endl;
    fstream fout(path, std::ios_base::out | std::ios_base::binary);

    fout.seekp(std::ios_base::beg);
    if(!fout.is_open()){
        std::cerr << "fail to open file!" << endl;
        exit(0);
    }
    
    //书本
    books.save(fout);
    
    fout.write(reinterpret_cast<const char*>(&borrowers), sizeof(int));   //要读入的读者数
    //读者
    int cnt = 0;
    while (cnt != borrowers)
    {
        readers[cnt++]->save(fout);
    }

    cout << "save finished!" << endl;
}

void BookRecord::save(fstream& fout){

    size_t len = book_id.size();
    fout.write(reinterpret_cast<const char *>(&len), sizeof(size_t));
    fout.write(book_id.c_str(), len);

    len = book_title.size();
    fout.write(reinterpret_cast<const char *>(&len), sizeof(size_t));
    fout.write(book_title.c_str(), len);

    len = author_first_name.size();
    fout.write(reinterpret_cast<const char *>(&len), sizeof(size_t));
    fout.write(author_first_name.c_str(), len);

    len = author_last_name.size();
    fout.write(reinterpret_cast<const char *>(&len), sizeof(size_t));
    fout.write(author_last_name.c_str(), len);

    fout.write(reinterpret_cast<const char*>(&year), sizeof(int));
    fout.write(reinterpret_cast<const char*>(&number_of_copies), sizeof(int));
    fout.write(reinterpret_cast<const char*>(&available_copies), sizeof(int));

}

void Borrower::save(fstream& fout){
    fout.write(reinterpret_cast < const char *>(&id), sizeof(int));

    size_t len = first_name.size();
    fout.write(reinterpret_cast<const char *>(&len), sizeof(size_t));
    fout.write(first_name.c_str(), len);

    len = last_name.size();
    fout.write(reinterpret_cast<const char *>(&len), sizeof(size_t));
    fout.write(last_name.c_str(), len);

    for (int cnt = 0; cnt < borrow_nums ; cnt++){
        len = 4;
        fout.write(book_ids[cnt]->c_str(), len);
    }

}

void Catalogue::save(fstream& fout){
    fout.write(reinterpret_cast<const char*>(&record_of_books), sizeof(int));
    for (int cnt = 0; cnt < record_of_books ; cnt++){
        if(records[cnt] == nullptr){
            std::cerr << "Nullptr!" << endl;
            exit(0);
        }
        records[cnt]->save(fout);
    }
}

void Library::load(const string path){
    cout << "loading :" << path << endl;
    fstream fin(path, std::ios_base::in | std::ios_base::binary);
    fin.seekg(std::ios_base::beg);

    if(!fin.is_open()){
        std::cerr << "fail to open file!" << endl;
        exit(0);
    }

    //书本
    books.load(fin);


    fin.read(reinterpret_cast<char *>(&borrowers), sizeof(int));



    //读者
    int cnt = 0;
    while (cnt != borrowers)
    {
        readers[cnt++]->load(fin);
    }

    cout << "load finished!" << endl;
}

void BookRecord::load(fstream& fin){
    size_t len;

    fin.read(reinterpret_cast<char*>(&len), sizeof(size_t));
    book_id.resize(len);
    fin.read(&book_id[0], len);

    fin.read(reinterpret_cast<char*>(&len), sizeof(size_t));
    book_title.resize(len);
    fin.read(&book_title[0], len);

    fin.read(reinterpret_cast<char*>(&len), sizeof(size_t));
    author_first_name.resize(len);
    fin.read(&author_first_name[0], len);

    fin.read(reinterpret_cast<char*>(&len), sizeof(size_t));
    author_last_name.resize(len);
    fin.read(&author_last_name[0], len);

    fin.read(reinterpret_cast<char*>(&year), sizeof(int));
    fin.read(reinterpret_cast<char*>(&number_of_copies), sizeof(int));
    fin.read(reinterpret_cast<char*>(&available_copies), sizeof(int));

}

void Borrower::load(fstream& fin){
    fin.read(reinterpret_cast<char*>(&id), sizeof(int));

    size_t len;

    fin.read(reinterpret_cast<char*>(&len), sizeof(size_t));
    first_name.resize(len);
    fin.read(&first_name[0], len);

    fin.read(reinterpret_cast<char*>(&len), sizeof(size_t));
    last_name.resize(len);
    fin.read(&last_name[0], len);
    fin.read(reinterpret_cast<char*>(&borrow_nums), sizeof(int));

    // 读取 book_ids
    for (int cnt = 0; cnt < borrow_nums; cnt++) {
        len = 4;
        book_ids[cnt] = new string();
        book_ids[cnt]->resize(len);
        fin.read(&((*book_ids[cnt])[0]), len);
    }
}

void Catalogue::load(fstream& fin){
    fin.read(reinterpret_cast<char*>(&record_of_books), sizeof(int));
    // 读取每本书的记录
    for (int cnt = 0; cnt < record_of_books; cnt++) {
        records[cnt] = new BookRecord();
        records[cnt]->load(fin);
    }
}