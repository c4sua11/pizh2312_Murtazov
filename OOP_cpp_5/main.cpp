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
    static int totalPayments; // Статический счетчик объектов

public:
    Payment() : date("01.01.1970"), amount(0.0), description("Без описания") {
        totalPayments++;
    }

    Payment(const string& dt, double amt, const string& desc)
        : date(dt), amount(amt), description(desc) {
        totalPayments++;
    }

    virtual ~Payment() {
        totalPayments--;
    }

    // Чисто виртуальные функции
    virtual void printDetails() const = 0;
    virtual string serialize() const = 0;
    virtual Payment* clone() const = 0;

    // Статический метод для получения количества объектов
    static int getTotalPayments() {
        return totalPayments;
    }

    // Геттеры и сеттеры
    string getDate() const { return date; }
    double getAmount() const { return amount; }
    string getDescription() const { return description; }
    void setDate(const string& dt) { date = dt; }
    void setAmount(double amt) { amount = amt; }
    void setDescription(const string& desc) { description = desc; }
};

// Инициализация статической переменной
int Payment::totalPayments = 0;

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

    ~Income() override = default;

    // Реализация виртуальных методов
    void printDetails() const override {
        cout << "ДОХОД: " << date << "\n"
            << "  Сумма: " << amount << " руб.\n"
            << "  Описание: " << description << "\n"
            << "  Источник: " << source << "\n"
            << "  Налогооблагаемый: " << (isTaxable ? "Да" : "Нет") << "\n\n";
    }

    string serialize() const override {
        return "INCOME|" + date + "|" + to_string(amount) + "|" +
            description + "|" + source + "|" + (isTaxable ? "1" : "0");
    }

    Payment* clone() const override {
        return new Income(*this);
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

    ~Expense() override = default;

    // Реализация виртуальных методов
    void printDetails() const override {
        cout << "РАСХОД: " << date << "\n"
            << "  Сумма: " << amount << " руб.\n"
            << "  Описание: " << description << "\n"
            << "  Категория: " << category << "\n"
            << "  Обязательный: " << (isEssential ? "Да" : "Нет") << "\n\n";
    }

    string serialize() const override {
        return "EXPENSE|" + date + "|" + to_string(amount) + "|" +
            description + "|" + category + "|" + (isEssential ? "1" : "0");
    }

    Payment* clone() const override {
        return new Expense(*this);
    }

    // Дополнительные методы
    string getCategory() const { return category; }
    bool getIsEssential() const { return isEssential; }
    void setCategory(const string& cat) { category = cat; }
    void setIsEssential(bool essential) { isEssential = essential; }
};

// Основной класс AccountingJournal
class AccountingJournal {
private:
    string journalName;
    vector<unique_ptr<Payment>> payments;
    static int totalInJournal; // Статический счетчик объектов в журнале

public:
    AccountingJournal() : journalName("Без названия") {}

    AccountingJournal(const string& name) : journalName(name) {}

    ~AccountingJournal() {
        totalInJournal -= payments.size();
    }

    // Метод для добавления платежа
    void addPayment(unique_ptr<Payment> payment) {
        payments.push_back(move(payment));
        totalInJournal++;
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

    // Статический метод для получения количества объектов в журналах
    static int getTotalInJournals() {
        return totalInJournal;
    }

    // Геттеры и сеттеры
    string getJournalName() const { return journalName; }
    void setJournalName(const string& name) { journalName = name; }
};

// Инициализация статической переменной
int AccountingJournal::totalInJournal = 0;

int main() {
    // Настройка консоли для кириллицы
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    cout << "=== Шаг 1: Проверка счетчиков до создания объектов ===\n";
    cout << "Всего платежей в системе: " << Payment::getTotalPayments() << endl;
    cout << "Платежей в журналах: " << AccountingJournal::getTotalInJournals() << endl;

    cout << "\n=== Шаг 2: Создание объектов ===\n";
    auto income1 = make_unique<Income>("15.05.2023", 50000, "Зарплата", "Компания А", true);
    auto expense1 = make_unique<Expense>("16.05.2023", 1500, "Продукты", "Питание", true);

    cout << "Всего платежей в системе: " << Payment::getTotalPayments() << endl;
    cout << "Платежей в журналах: " << AccountingJournal::getTotalInJournals() << endl;

    cout << "\n=== Шаг 3: Добавление в журнал ===\n";
    AccountingJournal journal("Основной журнал");
    journal.addPayment(move(income1));
    journal.addPayment(move(expense1));

    cout << "Всего платежей в системе: " << Payment::getTotalPayments() << endl;
    cout << "Платежей в журналах: " << AccountingJournal::getTotalInJournals() << endl;

    cout << "\n=== Шаг 4: Вывод журнала ===\n";
    journal.printAll();

    cout << "\n=== Шаг 5: Удаление объектов ===\n";
    // Объекты автоматически удаляются при выходе из scope

    return 0;
}