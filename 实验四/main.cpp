#include "zoo.h"

int main(int argc,const char* argv[]){
    zoo Zoo;
    int days = 10;
    if(argc>1){
        std::string num(argv[1]);

        days = std::stoi(num);
    }
    Zoo.Days(days);

}