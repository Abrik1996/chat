#pragma once
#include <iostream>
#include <string.h>
#include <iostream>
#include <fstream>
#define NAMELENGTH 10

class Account
{
public:
	Account() { name = ""; passwd = ""; }
// использовался для фиксации удаления при тестировании	~Account() { std::cout << "deleted account " << this->name << std::endl;  } 
	void chg_passwd(const std::string tmp);
	void chg_name(const std::string tmp);
	std::string get_name() { return this->name; }
	std::string get_passwd() { return this->passwd; }
	Account(const std::string str1, const std::string str2) { name = str1; passwd = str2; }
	void show();
private:
	std::string name;
	std::string passwd;
};

typedef char Login[NAMELENGTH]; // тип имя фрукта

class HashTable { // хэш таблица
public:
    HashTable();
    ~HashTable();
    void add(Login fr_name, int fr_count);
    void del(Login fr_name);
    int find(Login fr_name);

    friend void test(HashTable& ht);
  //  void dummy2(void** p);
private:

    enum enPairStatus {
        free,
        engaged,
        deleted
    };

    struct Pair { // пара ключ-значение

        Pair() :
            acc_name(""),
            acc_pass(-1),
            status(enPairStatus::free)
        {}
        Pair(Login name, int pass) 
        {
            acc_pass = pass;
            status = enPairStatus::engaged;
            int i = 0;
            while (i<10)
            {
                acc_name[i] = name[i];
                i++;
            }
        }
        Pair& operator = (const Pair& other) {
            acc_pass = other.acc_pass;
       //     strcpy_s(acc_name, other.acc_name);
            for (int i = 0; i < 10; i++)
                acc_name[i] = other.acc_name[i];
            status = other.status;
            return *this;
        }

        bool operator == (const Pair& other) {
            return  status == other.status &&
                (status != enPairStatus::engaged || (acc_pass == other.acc_pass && !strcmp(acc_name, other.acc_name)));
        }
        Login acc_name;
        int acc_pass;
        enPairStatus status;
    };
    void resize();
    int hash_func(Login fr_name, int offset);
    void dummy(int a);
    Pair* array;
    int mem_size;
    int count;
};




