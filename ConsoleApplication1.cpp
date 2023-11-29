#include "Account.h"
#include <vector> 
#include <memory> // для работы с умными указателями
class UserVector : public std::vector<Account> // динамический массив для хранения аккаунтов в памяти
{
    typedef std::vector<Account> ParentT;
};
class status
{
public:
    bool isloged;
    std::string loggedacc;
    status() { isloged = false; loggedacc = ""; }
};
bool login(status& Mystate , UserVector& A)
{
    std::cout << "\nInput account name\n";
    std::string tmp = "";
    std::cin >> tmp;
    //поиск аккаунта
    bool accok, passok = false; 
    for (std::vector<Account>::iterator iter = A.begin(); iter != A.end(); iter++) {
        if (iter->get_name() == tmp)
        {
            accok = true;
            std::cout << "\nInput account password\n";
            std::string tmp2 = "";
            std::cin >> tmp2;
            if (iter->get_passwd() == tmp2) passok = true; // проверка пароля 
            if (accok && passok) 
            {
                Mystate.isloged = true;
                Mystate.loggedacc = iter->get_name();
                return true;
            }
        }
    }
    return false;
}
void regnewacc(const std::string input, UserVector& vec) // функция регистрации пользователя
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
    данный блок используется для заполнения файлов дефолтными аккаунтами
    */
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
    status Mystate;
    short choice = 0;
    do {
        system("cls");
        std::cout << "Current account state "<< Mystate.isloged << " " << Mystate.loggedacc << std::endl;
        std::cout << "\n1:login with account name and passwd 2:register new user 3:exit\n";
        std::cin >> choice;
        switch (choice) 
        {
        case 1:
        {
            if (login(Mystate, *A)) { choice = 3; }
            std::cout << "Current account state " << Mystate.isloged << " " << Mystate.loggedacc << std::endl;
            break;
        }
        case 2: 
        {
            std::string tmp;
            std::cout << "Please input account name \n";
            std::cin >> tmp;
            regnewacc(tmp, *A);
            break;
        }
        case 3: break;
        };
    } while (choice != 3);
















//    regnewacc("usertestreg",*A);
//    showallacc(*A);
    A->clear();
    return 0; // возвращаем 0 - правило хорошего тона
}