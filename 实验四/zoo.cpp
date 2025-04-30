#include "zoo.h"
#include <cstdlib>
#include <ctime>
Money::Money(int dollar, int cent) : dollars(dollar), cents(cent)
{
    if (cents >= 100)
    {
        dollars += cents / 100;
        cents %= 100;
    }
}

Money &Money::operator+(const Money &money)
{
    dollars += money.dollars;
    cents += money.cents;
    if (cents / 100)
    {
        dollars += cents % 100;
        cents /= 100;
    }
    return *this;
}

Money &Money::operator-(const Money &money)
{
    cents -= money.cents;
    dollars -= money.dollars;
    if (cents < 0)
    {
        cents += 100;
        dollars--;
    }

    return *this;
}

AnimalFood::AnimalFood(int type, int cnt) : FoodType(type), amount(cnt) {}

AnimalEnclosure::~AnimalEnclosure(){
    for (int i = 0; i < animals.size();i++){
        delete animals[i];
    }
}

void AnimalEnclosure::open_() { 
    for(Animal* animal: animals){
        animal->poop();
    }
    open = true; 
}
void AnimalEnclosure::close_() { open = false; }

void AnimalEnclosure::Add_Animal(Animal *animal)
{
    animals.push_back(animal);
}
void AnimalEnclosure::Animal_eat(int count,bool& cleaning)
{
    bool all_full = true;
            for(Animal* animal: animals){
                if(!animal->full())
                    all_full = false;
    }
    if(all_full)
        return;
    while(this->open && count > 0){
        int max = animals.size();
        int rand_th = rand() % max;
        if(rand_th >= animals.size()) continue;
        Animal* animal = th(rand_th);
        count = animal->eat(count);
        dust += count;
        if (dust > 2000 && !cleaning)
        {
            cleaning = true;
            close_();
            closed_days++;
            dust = 0;
        }
    }
}

Animal::Animal(float w) : weight(w), food_eaten(0) {}
Elephant::Elephant(float w, float l) : Animal(w), length_nose(l) { max_eaten = 750; }
Monkey::Monkey(float w, float l) : Animal(w), length_arm(l) { max_eaten = 300; }
Giraffe::Giraffe(float w, float l) : Animal(w), length_neck(l) { max_eaten = 500; }

int Elephant::eat(int food)
{
    if (food_eaten >= max_eaten)
        return 0;
    if (food + food_eaten < max_eaten)
    {
        food_eaten += food;
        return food;
    }
    else
    {
        food = 500 - food_eaten;
        food_eaten = 500;
        return food;
    }
}

int Monkey::eat(int food)
{
    if (food_eaten >= max_eaten)
        return 0;
    if (food + food_eaten < max_eaten)
    {
        food_eaten += food;
        return food;
    }
    else
    {
        food = 500 - food_eaten;
        food_eaten = 500;
        return food;
    }
}

int Giraffe::eat(int food)
{
    if (food_eaten >= max_eaten)
        return 0;
    if (food + food_eaten < max_eaten)
    {
        food_eaten += food;
        return food;
    }
    else
    {
        food = 500 - food_eaten;
        food_eaten = 500;
        return food;
    }
}

Person::Person(const std::string name_, int age_) : name(name_), age(age_) {}

ZooKeeper::ZooKeeper(const std::string name_, int age_) : Person(name_, age_) {}
void ZooKeeper::work()
{
    days_cleaned++;
    if (days_cleaned >= 10)
    {
        quit();
    }
}
void ZooKeeper::quit()
{
    working = false;
}

FoodSeller::FoodSeller(const std::string name_, int age_, int p, int c, int b) : Person(name_, age_)
{
    Food = {p, c, b};
}

bool FoodSeller::sell(int type, int cnt)
{
    if (Food[type] < cnt)
    {
        return false;
    }
    else
    {
        Food[type] -= cnt;
        return true;
    }
}

bool FoodSeller::runout(){
    if (Food[0] > 0 &&Food[1] > 0 &&Food[2] > 0)
        return false;
    else{
    if(Food[0] <= 0)
        cout << "peanuts sold out!" << endl;
    if(Food[1] <= 0)
        cout << "carrots sold out!" << endl;
    if(Food[2] <= 0)
        cout << "bananas sold out!" << endl;
    }
    return true;
}

Visitor::Visitor(const std::string name_, int age_, int num) : Person(name_, age_), passcard_number(num) {}

Child::Child(const std::string name_, int age_, int pass, int p, int c, int b) : Visitor(name_, age_, pass)
{
    food_inhand = {p, c, b};
}

bool Child::feed(int type, int cnt)
{

    if (food_inhand[type])
    {
        food_inhand[type] -= cnt;
        return true;
    }
    else
    {
        return false;
    }
}

void Child::receive_food(int p, int c, int b)
{
    food_inhand[(int)Food_calss::Peanut] += p;
    food_inhand[(int)Food_calss::Carrot] += c;
    food_inhand[(int)Food_calss::Banana] += b;
}

Adult::Adult(const std::string name_, int age_, int pass, Money money) : Visitor(name_, age_, pass), money_inhand(money) {}

void Adult::add_Child(Child child)
{
    children.push_back(child);
}
void Adult::buy_food(FoodSeller* seller)
{
    int cents_for_every_food = (money_inhand.dollars * 100 + money_inhand.cents) / 3;
    // 各种食物可以买的数量
    int p_c = cents_for_every_food / (peanut * 100);
    int c_c = cents_for_every_food / (carrot * 100);
    int b_c = cents_for_every_food / (banana * 100);
    int children_cnt = children.size();
    // 平均分配给所有儿童，最后一个多拿一点
    for (auto &child : children)
    {
        std::vector<int> foods_stored;
        foods_stored = seller->ask_for_food(p_c / children_cnt, c_c / children_cnt, b_c / children_cnt);

        //减少购买量
        int rand_[3];
        for(int& i:rand_){
            i = 1 + rand() % 2;
        }
        for (int i = 0; i < 3;i++){
            foods_stored[i] -= rand_[i];
            if(foods_stored[i]<=0)
                foods_stored[i] = 1;
        }
        child.receive_food(foods_stored[0], foods_stored[1], foods_stored[1]);
        for (int i = 0; i < 3;i++){
            seller->sell(i, foods_stored[i]);
        }
    }
}

std::vector<int> FoodSeller::ask_for_food(int p, int c, int b){
    std::vector<int> result(3);
    for (int i = 0; i < 3;i++){
        if (p <= Food[i])
            result[i] = p;
        else
            result[i] = Food[i];
    }
    return result;
}

Money FoodSeller::profit(){
    int p = 10000 - Food[0];
    int c = 7000 - Food[1];
    int b = 4000 - Food[2];

    return Money(0, p * 50 + c * 30 + b * 20);
}

void Adult::buy_passcard()
{
    int children_c = children.size();
    Money ticket(1, 40 * children_c);
    money_inhand = money_inhand - ticket;
}

zoo::zoo() : profit_all(Money(0, 0)), adult_all(0), children_all(0)
{

    seller = new FoodSeller(std::string("seller"), 30);
    keeper = new ZooKeeper(std::string("keeper"), 41);

    Monkey *monkey1 = new Monkey(55.5, 1.4);
    Monkey *monkey2 = new Monkey(53.4, 1.2);
    Monkey *monkey3 = new Monkey(50.4, 0.9);
    monkeys.Add_Animal(monkey1);
    monkeys.Add_Animal(monkey2);
    monkeys.Add_Animal(monkey3);

    Giraffe *g1 = new Giraffe(300.6, 12.5);
    Giraffe *g2 = new Giraffe(266.6, 9.8);
    giraffes.Add_Animal(g1);
    giraffes.Add_Animal(g2);

    Elephant *e = new Elephant(666.6, 12.7);
    elephants.Add_Animal(e);
}

zoo::~zoo(){
    delete seller;
    delete keeper;

    monkeys.~AnimalEnclosure();
    giraffes.~AnimalEnclosure();
    elephants.~AnimalEnclosure();
}


bool zoo::ADay()
{
    bool cleaning = false;
    monkeys.open_();
    giraffes.open_();
    elephants.open_();

    srand(static_cast<unsigned int>(time(NULL)));
    if (keeper->quited())
    {
        cout << "zoo closed for the keeper quitted!" << endl;
        return false;
    }

    keeper->work();
    // 随机数量成年人来访
    int adult_cnt = 20 + rand() % 21; // 20~40人
    adult_all += adult_cnt;
    while (adult_cnt--)
    {
        cleaning = false;
        Money money(10 + rand() % 11, 0);
        Adult adult(std::string("adult" + std::to_string(adult_cnt)), 20, 10000 + rand() % 90000, money);

        int child_cnt = 1 + rand() % 3; // 1~3人
        int t = child_cnt;
        children_all += child_cnt;
        while (t--)
        {
            adult.add_Child(Child(std::string("child" + std::to_string(child_cnt)), rand() % 7 + 4, 10000 + rand() % 90000));
        }

        adult.buy_passcard();
        adult.buy_food(seller);

        if (seller->runout())
        {
            cout << "food sold out!" << endl;
            return false; // 食物卖完了
        }

        // 儿童会随机喂1~3个食物
        t = child_cnt;
        while (t--)
        {
            for (int i = 0; i < 3; i++)
            {
                int food_count = 1 + rand() % 3;
                bool feed = adult.children[t].feed(i, food_count);
                if (feed)
                { // 儿童有这么多食物
                    if (i == int(Food_calss::Banana) && monkeys.is_open())
                    {
                        monkeys.Animal_eat(food_count,cleaning);
                    }
                    else if (i == int(Food_calss::Carrot) && giraffes.is_open())
                    {
                        giraffes.Animal_eat(food_count,cleaning);
                    }
                    else if (i == int(Food_calss::Peanut) && elephants.is_open())
                    {
                        elephants.Animal_eat(food_count,cleaning);
                    }
                }
            }
        }
    }


    return true;
}

void zoo::Days(int days){
    cout << "the zoo open!" << endl;
    int i;
    for(i=1;i<=days;i++){
        if(!ADay()){
            break;
        }
    }
    cout << adult_all << " adults, " << children_all << " children visited in " << i << " days" << endl;
    Money pass(adult_all, children_all * 40);
    cout << "we sold passcards with $ " << pass.dollars << "." << pass.cents << endl;

    cout << "we sold food with $ " << seller->profit().dollars << ". " << seller->profit().cents << endl;
    cout << "the keeped worked for " << keeper->workint_days()<<" days"<<endl;
    cout << "monkeys' enclosure closed for " << monkeys.closed_length()<< " days" << endl;
    cout << "girffes' enclosure closed for " << giraffes.closed_length()<< " days" << endl;
    cout << "elephants' enclosure closed for " << elephants.closed_length() << " days" << endl;

    cout << "the zoo closed!" << endl;
}