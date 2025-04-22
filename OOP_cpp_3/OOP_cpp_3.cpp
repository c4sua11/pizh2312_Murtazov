#include <iostream>
#include <string>
#include <vector>
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
    Payment() : date("01.01.1970"), amount(0.0), description("Без описания") {
        cout << "Payment: Конструктор по умолчанию" << endl;
    }

    Payment(const string& dt, double amt, const string& desc)
        : date(dt), amount(amt), description(desc) {
        cout << "Payment: Конструктор с параметрами (" << date << ", " << amount << ", " << description << ")" << endl;
    }

    Payment(const Payment& other)
        : date(other.date), amount(other.amount), description(other.description) {
        cout << "Payment: Конструктор копирования (" << date << ", " << amount << ", " << description << ")" << endl;
    }

    // Деструктор
    virtual ~Payment() {
        cout << "Payment: Деструктор для (" << date << ", " << amount << ", " << description << ")" << endl;
    }

    // Геттеры
    string getDate() const { return date; }
    double getAmount() const { return amount; }
    string getDescription() const { return description; }

    // Сеттеры
    void setDate(const string& date) { this->date = date; }
    void setAmount(double amount) { this->amount = amount; }
    void setDescription(const string& description) { this->description = description; }

    // Виртуальный метод вывода
    virtual void print() const {
        cout << "Платеж: Дата: " << date << ", Сумма: " << amount << ", Описание: " << description << endl;
    }
};

// Класс-наследник 1 - Доход
class Income : public Payment {
private:
    string source;  // Источник дохода
    bool taxable;   // Облагается налогом

public:
    // Конструкторы
    Income() : source("Не указан"), taxable(false) {
        cout << "Income: Конструктор по умолчанию" << endl;
    }

    Income(const string& dt, double amt, const string& desc, const string& src, bool tax)
        : Payment(dt, amt, desc), source(src), taxable(tax) {
        cout << "Income: Конструктор с параметрами (" << source << ", " << taxable << ")" << endl;
    }

    Income(const Income& other)
        : Payment(other), source(other.source), taxable(other.taxable) {
        cout << "Income: Конструктор копирования (" << source << ", " << taxable << ")" << endl;
    }

    // Деструктор
    ~Income() {
        cout << "Income: Деструктор для (" << source << ", " << taxable << ")" << endl;
    }

    // Геттеры
    string getSource() const { return source; }
    bool isTaxable() const { return taxable; }

    // Сеттеры
    void setSource(const string& src) { source = src; }
    void setTaxable(bool tax) { taxable = tax; }

    // Метод вывода
    void print() const override {
        cout << "Доход: Дата: " << date << ", Сумма: " << amount
            << "\nОписание: " << description
            << "\nИсточник: " << source
            << ", Налогооблагаемый: " << (taxable ? "Да" : "Нет") << endl << endl;
    }
};

// Класс-наследник 2 - Расход
class Expense : public Payment {
private:
    string category;    // Категория расхода
    bool deductible;   // Учитывается при налогообложении

public:
    // Конструкторы
    Expense() : category("Не указана"), deductible(false) {
        cout << "Expense: Конструктор по умолчанию" << endl;
    }

    Expense(const string& dt, double amt, const string& desc, const string& cat, bool ded)
        : Payment(dt, amt, desc), category(cat), deductible(ded) {
        cout << "Expense: Конструктор с параметрами (" << category << ", " << deductible << ")" << endl;
    }

    Expense(const Expense& other)
        : Payment(other), category(other.category), deductible(other.deductible) {
        cout << "Expense: Конструктор копирования (" << category << ", " << deductible << ")" << endl;
    }

    // Деструктор
    ~Expense() {
        cout << "Expense: Деструктор для (" << category << ", " << deductible << ")" << endl;
    }

    // Геттеры
    string getCategory() const { return category; }
    bool isDeductible() const { return deductible; }

    // Сеттеры
    void setCategory(const string& cat) { category = cat; }
    void setDeductible(bool ded) { deductible = ded; }

    // Метод вывода
    void print() const override {
        cout << "Расход: Дата: " << date << ", Сумма: " << amount
            << "\nОписание: " << description
            << "\nКатегория: " << category
            << ", Учитывается при налогообложении: " << (deductible ? "Да" : "Нет") << endl << endl;
    }
};

int main() {
    // Настройка консоли для кириллицы
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    cout << "=== Шаг 1: Создание объектов ===" << endl;
    Payment payment1;  // Базовый класс - конструктор по умолчанию
    Payment payment2("15.05.2023", 5000.0, "Аванс");  // Базовый класс - конструктор с параметрами

    Income income1;  // Наследник 1 - конструктор по умолчанию
    Income income2("20.05.2023", 30000.0, "Зарплата", "Работа", true);  // Наследник 1 - конструктор с параметрами

    Expense expense1;  // Наследник 2 - конструктор по умолчанию
    Expense expense2("25.05.2023", 1500.0, "Покупка продуктов", "Продукты", false);  // Наследник 2 - конструктор с параметрами

    cout << "\n=== Шаг 2: Вывод созданных объектов ===" << endl;
    payment1.print();
    payment2.print();
    income1.print();
    income2.print();
    expense1.print();
    expense2.print();

    cout << "\n=== Шаг 3: Работа с массивом базового класса ===" << endl;
    Payment* payments[4];  // Массив указателей на базовый класс
    payments[0] = new Payment("01.06.2023", 1000.0, "Перевод");
    payments[1] = new Income("05.06.2023", 5000.0, "Фриланс", "Подработка", true);
    payments[2] = new Expense("10.06.2023", 2000.0, "Одежда", "Гардероб", false);
    payments[3] = new Income("15.06.2023", 25000.0, "Основная работа", "Зарплата", true);

    for (int i = 0; i < 4; i++) {
        payments[i]->print();
    }

    // Очистка памяти
    for (int i = 0; i < 4; i++) {
        delete payments[i];
    }

    cout << "\n=== Шаг 4: Работа с массивом класса-наследника ===" << endl;
    Expense expenses[3];  // Массив объектов класса-наследника
    expenses[0] = Expense("01.06.2023", 500.0, "Проезд", "Транспорт", false);
    expenses[1] = Expense("05.06.2023", 1200.0, "Обед", "Питание вне дома", false);
    expenses[2] = expense2;  // Используем конструктор копирования

    for (int i = 0; i < 3; i++) {
        expenses[i].print();
    }

    cout << "\n=== Шаг 5: Завершение программы ===" << endl;
    return 0;
}