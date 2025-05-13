#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>
#include <locale>
#include <windows.h>

using namespace std;

class Payment {
protected:
    string date;
    double amount;
    string description;

public:
    Payment(const string& dt = "01.01.1970", double amt = 0.0, const string& desc = "Нет описания")
        : date(dt), amount(amt), description(desc) {
    }

    virtual ~Payment() {}

    double getAmount() const { return amount; }

    virtual void print() const {
        cout << "Платеж: " << date << ", " << amount << ", " << description << endl;
    }

    // Для сортировки по значению
    bool operator<(const Payment& other) const {
        return amount < other.amount;
    }

    bool operator>(const Payment& other) const {
        return amount > other.amount;
    }
};

class Income : public Payment {
    string source;
    bool taxable;

public:
    Income(const string& dt, double amt, const string& desc, const string& src, bool tax)
        : Payment(dt, amt, desc), source(src), taxable(tax) {
    }

    void print() const override {
        cout << "Доход: " << date << ", " << amount << ", " << description
            << ", Источник: " << source << ", Налогооблагаемый: " << (taxable ? "Да" : "Нет") << endl;
    }
};

class Expense : public Payment {
    string category;
    bool deductible;

public:
    Expense(const string& dt, double amt, const string& desc, const string& cat, bool ded)
        : Payment(dt, amt, desc), category(cat), deductible(ded) {
    }

    void print() const override {
        cout << "Расход: " << date << ", " << amount << ", " << description
            << ", Категория: " << category << ", Учитывается при налогах: " << (deductible ? "Да" : "Нет") << endl;
    }
};

// Печать контейнера
template<typename Container>
void printContainer(const Container& cont, const string& title) {
    cout << "\n=== " << title << " ===" << endl;
    for (const auto& item : cont)
        item->print();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    // 1-2. Создание вектора объектов
    vector<shared_ptr<Payment>> payments;

    payments.push_back(make_shared<Income>("01.01.2024", 3000.0, "Зарплата", "Компания", true));
    payments.push_back(make_shared<Expense>("03.01.2024", 1200.0, "Продукты", "Еда", false));
    payments.push_back(make_shared<Income>("05.01.2024", 1800.0, "Фриланс", "Интернет", true));
    payments.push_back(make_shared<Expense>("06.01.2024", 2200.0, "Курсы", "Образование", true));
    payments.push_back(make_shared<Payment>("07.01.2024", 2500.0, "Подарок"));

    printContainer(payments, "Изначальный список");

    // 3. Сортировка по убыванию
    sort(payments.begin(), payments.end(),
        [](const shared_ptr<Payment>& a, const shared_ptr<Payment>& b) {
            return *a > *b;
        });

    printContainer(payments, "Список после сортировки по убыванию");

    // 5. Поиск первого элемента > 2000
    auto found = find_if(payments.begin(), payments.end(),
        [](const shared_ptr<Payment>& p) {
            return p->getAmount() > 2000;
        });

    if (found != payments.end()) {
        cout << "\nНайден элемент > 2000:" << endl;
        (*found)->print();
    }
    else {
        cout << "\nЭлемент > 2000 не найден." << endl;
    }

    // 6. Переместим элементы > 2000 в list
    list<shared_ptr<Payment>> highPayments;

    copy_if(payments.begin(), payments.end(), back_inserter(highPayments),
        [](const shared_ptr<Payment>& p) {
            return p->getAmount() > 2000;
        });

    printContainer(highPayments, "Второй контейнер: элементы > 2000");

    // 8. Сортировка по возрастанию
    sort(payments.begin(), payments.end(),
        [](const shared_ptr<Payment>& a, const shared_ptr<Payment>& b) {
            return *a < *b;
        });

    highPayments.sort([](const shared_ptr<Payment>& a, const shared_ptr<Payment>& b) {
        return *a < *b;
        });

    // 9. Вывод отсортированных контейнеров
    printContainer(payments, "Первый контейнер после сортировки по возрастанию");
    printContainer(highPayments, "Второй контейнер после сортировки по возрастанию");

    return 0;
}
