#include "Matrix.h"
#include <cstring>
using std::cout, std::cin, std::endl;
int main(){
    Matrix mat1;
    Matrix mat2;

    cout << "input mat1: ";
    cin >> mat1;
    cout << "input mat2: ";
    cin >> mat2;

    while(true){
        char choice[5];
        cout << "input your choice: " << endl;
        cin >> choice;
        if(strcmp(choice,"*")==0){
            cout << "mat1*mat2: " << endl;
            cout << mat1 * mat2;
            continue;
        }
        if(strcmp(choice,"+")==0){
            cout << "mat1+mat2: " << endl;
            cout << mat1 + mat2;
            continue;
        }
        if(strcmp(choice,"-")==0){
            cout << "mat1-mat2: " << endl;
            cout << mat1 - mat2;
            continue;
        }
        if(strcmp(choice,"+=")==0){
            cout << "mat1+=mat2: \nmat1:" << endl;
            mat1+=mat2;
            cout << mat1;
            continue;
        }
        if(strcmp(choice,"-=")==0){
            cout << "mat1-=mat2: \nmat1:" << endl;
            mat1-=mat2;
            cout << mat1;
            continue;
        }
        if(strcmp(choice,"*=")==0){
            cout << "mat1*=mat2: \nmat1:" << endl;
            mat1*=mat2;
            cout << mat1;
            continue;
        }
        if(strcmp(choice,"==")==0){
            cout << "mat1==mat2: " << endl;
            cout << std::boolalpha;
            cout << (mat1 == mat2) << endl;
            cout << std::noboolalpha;
            continue;
        }
        if(strcmp(choice,"!=")==0){
            cout << "mat1!=mat2: " << endl;
            cout << std::boolalpha;
            cout << (mat1 != mat2) << endl;
            cout << std::noboolalpha;
            continue;
        }
        if(strcmp(choice,"r")==0){
            cout << "done!quitting now" << endl;
            return 0;
        }
    }
}