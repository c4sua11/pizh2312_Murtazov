#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <locale>
#include <windows.h>

using namespace std;

// Базовый абстрактный класс Payment
class Payment {
protected:
    string date;
    double amount;
    string description;

public:
    Payment() : date("01.01.1970"), amount(0.0), description("Без описания") {}
    Payment(const string& dt, double amt, const string& desc)
        : date(dt), amount(amt), description(desc) {
    }
    virtual ~Payment() = default;

    // Чисто виртуальная функция
    virtual void printDetails() const = 0;

    // Геттеры
    string getDate() const { return date; }
    double getAmount() const { return amount; }
    string getDescription() const { return description; }

    // Сеттеры
    void setDate(const string& dt) { date = dt; }
    void setAmount(double amt) { amount = amt; }
    void setDescription(const string& desc) { description = desc; }
};

// Класс Income (доходы)
class Income : public Payment {
private:
    string source;
    bool isTaxable;

public:
    Income() : source("Не указан"), isTaxable(false) {}
    Income(const string& dt, double amt, const string& desc,
        const string& src, bool tax)
        : Payment(dt, amt, desc), source(src), isTaxable(tax) {
    }

    void printDetails() const override {
        cout << "ДОХОД: " << date << "\n"
            << "  Сумма: " << amount << " руб.\n"
            << "  Описание: " << description << "\n"
            << "  Источник: " << source << "\n"
            << "  Налогооблагаемый: " << (isTaxable ? "Да" : "Нет") << "\n\n";
    }

    // Дополнительные методы
    string getSource() const { return source; }
    bool getIsTaxable() const { return isTaxable; }
    void setSource(const string& src) { source = src; }
    void setIsTaxable(bool tax) { isTaxable = tax; }
};

// Класс Expense (расходы)
class Expense : public Payment {
private:
    string category;
    bool isEssential;

public:
    Expense() : category("Не указана"), isEssential(false) {}
    Expense(const string& dt, double amt, const string& desc,
        const string& cat, bool essential)
        : Payment(dt, amt, desc), category(cat), isEssential(essential) {
    }

    void printDetails() const override {
        cout << "РАСХОД: " << date << "\n"
            << "  Сумма: " << amount << " руб.\n"
            << "  Описание: " << description << "\n"
            << "  Категория: " << category << "\n"
            << "  Обязательный: " << (isEssential ? "Да" : "Нет") << "\n\n";
    }

    // Дополнительные методы
    string getCategory() const { return category; }
    bool getIsEssential() const { return isEssential; }
    void setCategory(const string& cat) { category = cat; }
    void setIsEssential(bool essential) { isEssential = essential; }
};

// Модифицированный основной класс AccountingJournal
class AccountingJournal {
private:
    string journalName;
    vector<unique_ptr<Payment>> payments;

public:
    AccountingJournal() : journalName("Без названия") {}
    AccountingJournal(const string& name) : journalName(name) {}

    // Метод для добавления любого типа платежа
    void addPayment(unique_ptr<Payment> payment) {
        payments.push_back(move(payment));
    }

    // Метод вывода всех данных
    void printAll() const {
        cout << "=== ЖУРНАЛ УЧЕТА: " << journalName << " ===\n";
        cout << "Всего операций: " << payments.size() << "\n\n";

        for (const auto& payment : payments) {
            payment->printDetails();
        }

        cout << "=== КОНЕЦ ОТЧЕТА ===\n";
    }

    // Геттеры и сеттеры
    string getJournalName() const { return journalName; }
    void setJournalName(const string& name) { journalName = name; }
};

int main() {
    // Настройка консоли для кириллицы
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    cout << "=== Шаг 1: Создание массива базового класса ===\n";

    // Создаем массив указателей базового класса
    vector<unique_ptr<Payment>> payments;

    // Добавляем объекты разных типов
    payments.push_back(make_unique<Income>("15.05.2023", 50000, "Зарплата", "Компания А", true));
    payments.push_back(make_unique<Expense>("16.05.2023", 1500, "Продукты", "Питание", true));
    payments.push_back(make_unique<Income>("17.05.2023", 10000, "Фриланс", "Заказчик Б", false));
    payments.push_back(make_unique<Expense>("18.05.2023", 3000, "Одежда", "Гардероб", false));

    // Выводим через полиморфный интерфейс
    for (const auto& payment : payments) {
        payment->printDetails();
    }

    cout << "\n=== Шаг 2: Работа с модифицированным основным классом ===\n";

    // Создаем журнал
    AccountingJournal journal("Основной журнал учета");

    // Добавляем платежи разных типов
    journal.addPayment(make_unique<Income>("20.05.2023", 25000, "Аванс", "Компания А", true));
    journal.addPayment(make_unique<Expense>("21.05.2023", 2000, "Кафе", "Развлечения", false));
    journal.addPayment(make_unique<Income>("22.05.2023", 5000, "Подработка", "Заказчик В", true));

    // Выводим полный отчет
    journal.printAll();

    return 0;
}