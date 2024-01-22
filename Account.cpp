#include "Account.h"

void Account::chg_passwd(const std::string tmp)
{
	this->passwd = tmp;
	std::cout << "pass set " << tmp << std::endl;
}

void Account::chg_name(const std::string tmp)
{
	this->name = tmp;
	std::cout << "name set " << tmp << std::endl;
}

void Account::show()
{
	
		std::cout << "Account name = " << name << std::endl; // ", Passwd = " << passwd << std::endl; (старый функционал для тестирования)
	
}

HashTable::HashTable() {
    count = 0;
    mem_size = 8;
    array = new Pair[mem_size];
}
HashTable::~HashTable() {
    delete[] array;
}
void HashTable::add(Login ac_name, int ac_pass) {
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++) {
        index = hash_func(ac_name, i);
        if (array[index].status == enPairStatus::free) {
            // найдена пустая ячейка, занимаем ее
            break;
        }
    }
    if (i >= mem_size) return; // все перебрали, нет места

    // кладем в свободную ячейку пару
    array[index] = Pair(ac_name, ac_pass);
    count++;
}
int HashTable::hash_func(Login ac_name, int offset) {
    // вычисляем индекс
    int sum = 0, i = 0;
    for (; i < NAMELENGTH; i++) {
        sum += ac_name[i];
    }
    // линейные пробы
    return (sum % mem_size + offset) % mem_size;
}
void HashTable::del(Login fr_name) {
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++) {
        index = hash_func(fr_name, i);
        if (array[index].status == enPairStatus::engaged &&
            !strcmp(array[index].acc_name, fr_name)) {
            array[index].status = enPairStatus::deleted;
            count--;
            return;
        }
        else if (array[index].status == enPairStatus::free) {
            return;
        }
    }
}

int HashTable::find(Login fr_name) {

    for (int i = 0; i < mem_size; i++) {
        int index = hash_func(fr_name, i);
        if (array[index].status == enPairStatus::engaged &&
            !strcmp(array[index].acc_name, fr_name)) {
            return array[index].acc_pass;
        }
        else if (array[index].status == enPairStatus::free) {
            return -1;
        }
    }
    return -1;
}