#pragma once

#define banana 0.5
#define carrot 0.3
#define peanut 0.2

#include <iostream>
#include <vector>
#include <string>
using std::cout, std::endl;

class Money{
public:
    int dollars;
    int cents;

    Money& operator+(const Money&);
    Money &operator-(const Money &);
    Money(int, int);
};

enum class Food_calss :int
{
    Peanut,
    Carrot,
    Banana,
};
class AnimalFood{
    int FoodType;
    int amount;

    AnimalFood(int, int);
};



//ABC   
class Animal{
    float weight;
protected:
    int max_eaten;
    int food_eaten;
public:
    bool full() { return max_eaten <= food_eaten; }
    void poop() { food_eaten = 0; }
    Animal(float);
    //返回吃了的食物数
    virtual int eat(int) = 0;
};

class Elephant : public Animal{
    float length_nose;
public:
    Elephant(float, float);
    virtual int eat(int);
};

class Giraffe : public Animal{
    float length_neck;
public:
    Giraffe(float, float);
    virtual int eat(int);
};

class Monkey : public Animal{
    float length_arm;
public:
    Monkey(float, float);
    virtual int eat(int);
};


//每种动物一个围栏
class AnimalEnclosure{
    int dust;
    bool open;
    int closed_days = 0;

    std::vector<Animal *> animals;
public:
    AnimalEnclosure() : dust(0), open(true){}
    int closed_length() { return closed_days; }
    void open_();
    void close_();
    void Add_Animal(Animal*);
    void Animal_eat(int,bool&);
    bool is_open() { return open; }
    Animal* th(int i){
        return animals[i];
    }
};

//ABC
class Person{
    std::string name;
    int age;
public:
    Person(const std::string, int);
};

class ZooKeeper : public Person{
    int days_cleaned;
    bool working = true;

public:
    int workint_days() { return days_cleaned; }
    void work();
    void quit();
    bool quited() { return working == false; }
    ZooKeeper(const std::string, int);
};

class FoodSeller : public Person{
    std::vector<int> Food; // 直接通过Food_class::种类来访问
    std::vector<double> Food_values = {0.5,0.3,0.2};
public:
    FoodSeller(const std::string name_, int age_, int p = 10000, int c = 7000, int b = 4000);
    bool sell(int, int);
    bool runout();
    Money profit();
    //Adult先询问是否有这么多，seller返回实际能卖出来的数数目
    std::vector<int> ask_for_food(int p, int c, int b);
};

class Visitor : public Person{
    int passcard_number;
public:
    Visitor(const std::string, int, int);
};

class Child : public Visitor{
    std::vector<int> food_inhand;

public:
    Child(const std::string name_, int age_, int pass, int p = 0, int c = 0, int b = 0);

    void receive_food(int, int, int);
    bool feed(int, int);
};

class Adult : public Visitor{
    Money money_inhand;
public:
    std::vector<Child> children;
    void add_Child(Child);
    //剩下的钱平均分到三种食物，食物也分别平均分给小孩
    void buy_food(FoodSeller* seller);
    void buy_passcard();
    Adult(const std::string, int, int, Money);
};


class zoo{
    Money profit_all;

    int adult_all, children_all;
    // std::vector<Monkey*> monkeys;
    // std::vector<Elephant*> elephants;
    // std::vector<Giraffe*> giraffes;

    AnimalEnclosure monkeys;
    AnimalEnclosure elephants;
    AnimalEnclosure giraffes;

    FoodSeller* seller;
    ZooKeeper* keeper;

public:
    zoo();
    bool ADay();
    void Days(int days);
};
