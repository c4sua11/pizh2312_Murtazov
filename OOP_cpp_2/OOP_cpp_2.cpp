#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <windows.h>

using namespace std;

// Дополнительный класс - Платеж
class Payment {
private:
    string date;
    double amount;
    string description;

public:
    // Конструктор без параметров
    Payment() : date("01.01.1970"), amount(0.0), description("Без описания") {
        cout << "Payment: Вызван конструктор по умолчанию" << endl;
    }

    // Конструктор с параметрами
    Payment(const string& dt, double amt, const string& desc)
        : date(dt), amount(amt), description(desc) {
        cout << "Payment: Вызван конструктор с параметрами (" << date << ", " << amount << ", " << description << ")" << endl;
    }

    // Конструктор копирования
    Payment(const Payment& other)
        : date(other.date), amount(other.amount), description(other.description) {
        cout << "Payment: Вызван конструктор копирования (" << date << ", " << amount << ", " << description << ")" << endl;
    }

    // Деструктор
    ~Payment() {
        cout << "Payment: Вызван деструктор для платежа (" << date << ", " << amount << ", " << description << ")" << endl;
    }

    // Геттеры
    string getDate() const { return date; }
    double getAmount() const { return amount; }
    string getDescription() const { return description; }

    // Сеттеры
    void setDate(const string& date) { this->date = date; }
    void setAmount(double amount) { this->amount = amount; }
    void setDescription(const string& description) { this->description = description; }

    // Методы с одинаковыми именами
    void setPaymentDetails() {
        cout << "Введите дату платежа (ДД.ММ.ГГГГ): ";
        getline(cin, date);

        cout << "Введите сумму платежа: ";
        cin >> amount;
        cin.ignore();

        cout << "Введите описание платежа: ";
        getline(cin, description);
    }

    void setPaymentDetails(const string& date, double amount, const string& description) {
        setDate(date);
        setAmount(amount);
        setDescription(description);
    }
};

// Основной класс - Журнал учета
class AccountingJournal {
private:
    string name;
    string cardNumber;
    vector<Payment> payments;

public:
    // Конструктор без параметров
    AccountingJournal() : name("Без названия"), cardNumber("0000 0000 0000 0000") {
        cout << "AccountingJournal: Вызван конструктор по умолчанию" << endl;
    }

    // Конструктор с параметрами
    AccountingJournal(const string& nm, const string& card)
        : name(nm), cardNumber(card) {
        cout << "AccountingJournal: Вызван конструктор с параметрами (" << name << ", " << cardNumber << ")" << endl;
    }

    // Конструктор копирования
    AccountingJournal(const AccountingJournal& other)
        : name(other.name), cardNumber(other.cardNumber), payments(other.payments) {
        cout << "AccountingJournal: Вызван конструктор копирования (" << name << ", " << cardNumber << ")" << endl;
    }

    // Деструктор
    ~AccountingJournal() {
        cout << "AccountingJournal: Вызван деструктор для журнала (" << name << ", " << cardNumber << ")" << endl;
    }

    // Геттеры
    string getName() const { return name; }
    string getCardNumber() const { return cardNumber; }
    const vector<Payment>& getPayments() const { return payments; }

    // Сеттеры
    void setName(const string& name) { this->name = name; }
    void setCardNumber(const string& cardNumber) { this->cardNumber = cardNumber; }

    // Метод для добавления платежа
    void addPayment(const Payment& payment) {
        payments.push_back(payment);
    }

    // Новый метод - создание и добавление платежа с параметрами
    void addNewPayment(const string& date, double amount, const string& description) {
        Payment payment(date, amount, description); // Создание конструктором с параметрами
        payments.push_back(payment);
    }

    // Новый метод - создание копий платежа
    void addCopiesOfPayment(const Payment& payment, int count) {
        for (int i = 0; i < count; ++i) {
            Payment newPayment(payment); // Создание конструктором копирования
            payments.push_back(newPayment);
        }
    }
};

int main() {
    // Настройка консоли для кириллицы
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    cout << "=== Шаг 1: Создание журналов ===" << endl;
    AccountingJournal journal1; // Конструктор по умолчанию
    AccountingJournal journal2("Основной журнал", "1234 5678 9012 3456"); // Конструктор с параметрами
    AccountingJournal journal3(journal2); // Конструктор копирования

    cout << "\n=== Шаг 2: Создание платежей ===" << endl;
    Payment payment1; // Конструктор по умолчанию
    Payment payment2("15.05.2023", 1500.0, "Покупка продуктов"); // Конструктор с параметрами
    Payment payment3(payment2); // Конструктор копирования

    cout << "\n=== Шаг 3: Добавление платежей в журнал 1 ===" << endl;
    journal1.addNewPayment("20.05.2023", 2500.0, "Оплата услуг"); // Новый метод 1
    journal1.addCopiesOfPayment(payment2, 3); // Новый метод 2

    cout << "\n=== Шаг 4: Добавление платежей в журнал 2 ===" << endl;
    journal2.addPayment(payment1); // Обычное добавление
    journal2.addNewPayment("25.05.2023", 3500.0, "Аренда");

    cout << "\n=== Шаг 5: Вывод информации ===" << endl;
    cout << "Журнал 1: " << journal1.getName() << ", карта: " << journal1.getCardNumber() << endl;
    cout << "Платежи:" << endl;
    for (const auto& payment : journal1.getPayments()) {
        cout << "  Дата: " << payment.getDate() << ", Сумма: " << payment.getAmount()
            << ", Описание: " << payment.getDescription() << endl;
    }

    cout << "\nЖурнал 2: " << journal2.getName() << ", карта: " << journal2.getCardNumber() << endl;
    cout << "Платежи:" << endl;
    for (const auto& payment : journal2.getPayments()) {
        cout << "  Дата: " << payment.getDate() << ", Сумма: " << payment.getAmount()
            << ", Описание: " << payment.getDescription() << endl;
    }

    cout << "\n=== Шаг 6: Завершение программы ===" << endl;
    return 0;
}