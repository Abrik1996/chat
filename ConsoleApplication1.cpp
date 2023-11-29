#include "Message.h"
#include <vector> 
#include <memory> // для работы с умными указателями
#include <exception>

class NoSynchronFiles : public std::exception
{
public:
    virtual const char* what() const noexcept override
    {
        return "ERROR: Not synchronized configuration files !";
    }
};
class UserVector : public std::vector<Account> // динамический массив для хранения аккаунтов в памяти , чтобы не обращаться к файлу каждый раз
{
    typedef std::vector<Account> ParentT;
};
class status              // структура для фиксации текущего пользователя
{
public:
    bool isloged;
    std::string loggedacc;
    status() { isloged = false; loggedacc = ""; }
};

void sendmessage(status Mystate, std::string target, std::string input) // отправка сообщения путём добавления его в messlog.txt
{
    std::ofstream out;
    out.open("messlog.txt", std::ios_base::app);// открываем файл для записи
    if (out.is_open())
    {
        out << Mystate.loggedacc << " " << target << " " << input << std::endl;
    }

    out.close();
}
bool search_acc(const std::string target, UserVector& A)  //поиск аккаунта (проверка валидности цели сообщения)
{

    for (std::vector<Account>::iterator iter = A.begin(); iter != A.end(); iter++)
    {
        if (iter->get_name() == target) return true;
    }
    return false;
}
bool login(status& Mystate , UserVector& A) // функция входа по логину/паролю 
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
void showallacc(UserVector& A) //фукция нужны была для тестирования , оставлена для упрощения выбора пользователя при отправке сообщений
{
    for (std::vector<Account>::iterator iter = A.begin(); iter != A.end(); iter++) {
        iter->show();
    }
}
void showmessages(status Mystate) // вывод всех сообщений для текущего пользователя
{
    system("cls");
    char buff[100];
    std::ifstream in("messlog.txt");// окрываем файл для чтения
    if (!in.is_open()) // если файл не открыт
        std::cout << "Empty message file!\n"; // сообщить об этом
    while (in)
    {
        in.getline(buff, 100);
        Message *tmp = new Message(std::string(buff));
        if (Mystate.loggedacc==tmp->get_target())
        tmp->show();
        delete tmp;
    }
    in.close();
}
int main(int argc, char* argv[])
{
    //account counter 
    /*
    std::ofstream out3;
    out3.open("messlog.txt");
    out3.close();
    */
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
    данный блок можно использовать для заполнения файлов дефолтными аккаунтами
    */
    int n = 0; //счётчик дла аккаунтов
    try
    {
        std::string check;
        std::ifstream in("accounts.txt");// окрываем файл для чтения
        if (in.is_open())
        {
            while (in)
            {
                in >> check;
                n++;
            }
        }
        in.close();
        std::ifstream in2("passwds.txt");// окрываем файл для чтения
        if (in2.is_open())
        {
            while (in2)
            {
                in2 >> check;
                n--;
            }
        }
        in.close();
        if (n != 0) throw NoSynchronFiles();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        std::ofstream out, out2;
        out.open("accounts.txt");
        out2.open("passwds.txt");
        return 1;
    }
    
        UserVector* A = new UserVector();
        std::ifstream in("accounts.txt");// окрываем файл для чтения
        if (in.is_open())
        {
            while (in)
            {
                Account* D = new Account();
                std::string tmp;
                in >> tmp;
                if (tmp != "") D->chg_name(tmp);
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
    while (1)
    {


        do {
            system("cls");
            std::cout << "Current account state " << Mystate.isloged << " " << Mystate.loggedacc << std::endl;
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
            case 3: 
            {
                A->clear();
                return 0; // возвращаем 0 - правило хорошего тона 
            }
            };
        } while (choice != 3);

        do
        {
            std::cout << "\n1:send message to user 2:send message to all 3:read all messages 4:logout user \n";
            std::cin >> choice;
            std::string tmp2 = "";
            std::string tmp = "";
            switch (choice)
            {
            case 1:
            {
                showallacc(*A);
                tmp = "";
                std::cout << "\nTarget accout : ";
                std::cin >> tmp;
                if (!search_acc(tmp, *A))
                {
                    std::cout << "\nno such user\n";
                    break;
                }
                tmp2 = "";
                std::cout << "\nType message until char ';' : ";
                std::string word;
                do
                {
                    std::cin >> word;
                    tmp2 += word + " ";
                } while (word != ";");
                sendmessage(Mystate, tmp, tmp2);
                break;
            }
            case 2:
            {
                tmp2 = "";
                std::cout << "\nType message until char ';' : ";
                std::string word;
                do
                {
                    std::cin >> word;
                    tmp2 += word + " ";
                } while (word != ";");
                for (std::vector<Account>::iterator iter = A->begin(); iter != A->end(); iter++)
                {
                    sendmessage(Mystate, iter->get_name(), tmp2);
                }
                break;
            }
            case 3:
                showmessages(Mystate);
            case 4: 
            {
                Mystate.isloged = false;
                Mystate.loggedacc = "";
            }
            };
        } while (choice != 4);

    }
}