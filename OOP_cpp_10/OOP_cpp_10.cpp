#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <locale>
#include <windows.h>

using namespace std;

// Базовый класс - Платеж
class Payment {
protected:
    string date;
    double amount;
    string description;

public:
    // Конструкторы
    Payment() : date("01.01.1970"), amount(0.0), description("Без описания") {}

    Payment(const string& dt, double amt, const string& desc)
        : date(dt), amount(amt), description(desc) {
    }

    Payment(const Payment& other)
        : date(other.date), amount(other.amount), description(other.description) {
    }

    virtual ~Payment() {}

    // Геттеры
    string getDate() const { return date; }
    double getAmount() const { return amount; }
    string getDescription() const { return description; }

    // Сеттеры
    void setDate(const string& date) { this->date = date; }
    void setAmount(double amount) { this->amount = amount; }
    void setDescription(const string& description) { this->description = description; }

    // Виртуальный метод
    virtual void print() const {
        cout << "Платеж: " << date << ", " << amount << ", " << description << endl;
    }

    // Глобальные операторы для работы с файлами
    friend ostream& operator<<(ostream& os, const Payment& p) {
        os << p.date << '\n' << p.amount << '\n' << p.description << '\n';
        return os;
    }

    friend istream& operator>>(istream& is, Payment& p) {
        getline(is, p.date);
        is >> p.amount;
        is.ignore(); // пропуск \n после числа
        getline(is, p.description);
        return is;
    }
};

// Класс-наследник 1 - Доход
class Income : public Payment {
private:
    string source;
    bool taxable;

public:
    Income() : source("Не указан"), taxable(false) {}

    Income(const string& dt, double amt, const string& desc, const string& src, bool tax)
        : Payment(dt, amt, desc), source(src), taxable(tax) {
    }

    Income(const Income& other)
        : Payment(other), source(other.source), taxable(other.taxable) {
    }

    void print() const override {
        cout << "Доход: " << date << ", " << amount << ", " << description
            << ", Источник: " << source << ", Налогооблагаемый: " << (taxable ? "Да" : "Нет") << endl;
    }
};

// Класс-наследник 2 - Расход
class Expense : public Payment {
private:
    string category;
    bool deductible;

public:
    Expense() : category("Не указана"), deductible(false) {}

    Expense(const string& dt, double amt, const string& desc, const string& cat, bool ded)
        : Payment(dt, amt, desc), category(cat), deductible(ded) {
    }

    Expense(const Expense& other)
        : Payment(other), category(other.category), deductible(other.deductible) {
    }

    void print() const override {
        cout << "Расход: " << date << ", " << amount << ", " << description
            << ", Категория: " << category << ", Учитывается при налогообложении: " << (deductible ? "Да" : "Нет") << endl;
    }
};

// Функции для работы с файлами
void saveToFile(const vector<Payment*>& list, const string& filename) {
    ofstream file(filename);
    for (const auto& p : list) {
        file << *p;
    }
    file.close();
    cout << "Сохранено в файл " << filename << endl;
}

void loadFromFile(vector<Payment*>& list, const string& filename) {
    ifstream file(filename);
    while (!file.eof()) {
        Payment* p = new Payment;
        file >> *p;
        if (file) list.push_back(p);
    }
    file.close();
    cout << "Загружено из файла " << filename << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    cout << "=== Шаг 1: Создание контейнера vector<Payment*> ===" << endl;
    vector<Payment*> payments;
    payments.push_back(new Payment("01.01.2024", 1000.0, "Аванс"));
    payments.push_back(new Income("05.01.2024", 3000.0, "Зарплата", "Работа", true));
    payments.push_back(new Expense("10.01.2024", 500.0, "Продукты", "Еда", false));

    cout << "\n=== Шаг 2: Просмотр элементов (обычный цикл) ===" << endl;
    for (const auto& p : payments) {
        p->print();
    }

    cout << "\n=== Шаг 3: Удалим 1-й элемент и изменим описание у второго ===" << endl;
    delete payments[0];
    payments.erase(payments.begin());
    payments[0]->setDescription("Обновлённая зарплата");

    cout << "\n=== Шаг 4: Просмотр через итераторы ===" << endl;
    for (auto it = payments.begin(); it != payments.end(); ++it) {
        (*it)->print();
    }

    cout << "\n=== Шаг 5: Сохраняем данные в файл ===" << endl;
    saveToFile(payments, "payments.txt");

    cout << "\n=== Шаг 6: Загружаем данные из файла в новый контейнер ===" << endl;
    vector<Payment*> loadedPayments;
    loadFromFile(loadedPayments, "payments.txt");

    for (const auto& p : loadedPayments) {
        p->print();
    }

    // Очистка памяти
    for (auto& p : payments) delete p;
    for (auto& p : loadedPayments) delete p;

    cout << "\n=== Завершение программы ===" << endl;
    return 0;
}
