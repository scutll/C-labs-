#include "Library.h"
#include <iostream>

BookRecord read_book_info_from_type();
Borrower read_borrower_info_from_type();
Library library;

#define SAVE 

#ifdef SAVE
int main(){
    int n;
    cout << "要录入的书籍量: " << endl;
    cin >> n;
    cout << "录入书籍信息: " << endl;
    while(n--){
        if(library.add_book(read_book_info_from_type()))
            continue;
        n++;
    }

    cout << "要录入的读者量: " << endl;
    cin >> n;
    cout << "录入读者信息: " << endl;
    while(n--){
        if(library.add_borrower(read_borrower_info_from_type()))
            continue;
        n++;
    }

    library.show();
    library.save("test.kpl");
    return 0;
}
#else
int main(){
    library.load("test.kpl");
    library.show();
    return 0;
}
#endif