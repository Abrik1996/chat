// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Account.h"
#include <vector>
#include <memory> // для работы с умными указателями
class UserVector : public std::vector<Account>
{
    typedef std::vector<Account> ParentT;
public:
    /*
    UserVector& sort(int field);
    ParentT::size_type find(int field, const std::string& request);
    */
};
void regnewacc(const std::string input, UserVector& vec)
{
    if (input == "") { std::cout << "empty name\n"; return; }
    for (std::vector<Account>::iterator iter = vec.begin(); iter != vec.end(); iter++) {
        if (input == iter->get_name()) { std::cout << "existed name\n"; return; }
    }
    std::cout << "Account name ok! Please input password\n";
    std::string tmp;
    std::cin >> tmp;
    Account* D = new Account(input, tmp);
    vec.push_back(*D);
    //*
    std::ofstream out, out2;
    out.open("accounts.txt", std::ios_base::app);
    out2.open("passwds.txt", std::ios_base::app);// открываем файл для записи
    if(out.is_open() && out2.is_open())
    {
        std::cout << "registered new user , user info:\n";
        D->show();
        out << D->get_name()<< std::endl;
        out2 << D->get_passwd()<< std::endl;
    }
    out.close(); out2.close();
    //*/
    return;
}
void showallacc(UserVector& A)
{
    for (std::vector<Account>::iterator iter = A.begin(); iter != A.end(); iter++) {
        iter->show();
    }
}
int main(int argc, char* argv[])
{
    /*
    std::unique_ptr<Account> A1(new Account("user1", "1"));
    std::unique_ptr<Account> B(new Account("user2", "1"));
    std::unique_ptr<Account> C(new Account("user3", "1"));
    std::ofstream out , out2;          // поток для записи
    out.open("accounts.txt");
    out2.open("passwds.txt");// открываем файл для записи
    if (out.is_open() && out2.is_open())
    {
        out << A1->get_name() << std::endl;
        out2 << A1->get_passwd() << std::endl;
        out << B->get_name() << std::endl;
        out2 << B->get_passwd() << std::endl;
        out << C->get_name() << std::endl;
        out2 << C->get_passwd() << std::endl;
    }
    out.close(); out2.close(); 
    */
    //std::unique_ptr<Account> D(new Account());
    UserVector* A = new UserVector();
    std::ifstream in("accounts.txt");// окрываем файл для чтения
    if (in.is_open()) 
    {
        while (in)
        {
            Account* D = new Account();
            std::string tmp; 
            in >> tmp;
            if (tmp!="") D->chg_name(tmp);
            if (tmp != "") A->push_back(*D);
            delete D;
        }
    }
    in.close();
    std::ifstream in2("passwds.txt");// окрываем файл для чтения
    for (std::vector<Account>::iterator iter = A->begin(); iter != A->end(); iter++) {
        std::string tmp;
        in2 >> tmp;
        if (tmp != "") iter->chg_passwd(tmp);
    }
    in2.close();






















//    regnewacc("usertestreg",*A);
//    showallacc(*A);
    A->clear();
    return 0; // возвращаем 0 - правило хорошего тона
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
