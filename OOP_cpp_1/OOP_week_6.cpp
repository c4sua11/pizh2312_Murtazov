#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Класс Платеж
class Payment {
private:
    string date;
    double amount;
    string description;

public:
    // Конструктор по умолчанию
    Payment() : date("неизвестно"), amount(0.0), description("нет описания") {}

    // Конструктор с параметрами
    Payment(string d, double a, string desc) : date(d), amount(a), description(desc) {}

    // Перегруженные методы для инициализации атрибутов
    void setPayment(string d, double a, string desc) {
        date = d;
        amount = a;
        description = desc;
    }

    void setPayment(double a, string desc) {
        amount = a;
        description = desc;
        date = "2023-01-01";
    }

    // Методы для получения данных
    string getDate() const { return date; }
    double getAmount() const { return amount; }
    string getDescription() const { return description; }

    // Метод для вывода данных
    void display() const {
        cout << "Дата: " << date << ", Сумма: " << amount << ", Описание: " << description << endl;
    }
};

// Класс Журнал учета
class AccountJournal {
private:
    string card;
    string name;
    vector<Payment> payments;

public:
    // Конструктор по умолчанию
    AccountJournal() : card("неизвестно"), name("неизвестно") {}

    // Конструктор с параметрами
    AccountJournal(string c, string n) : card(c), name(n) {}

    // Перегруженные методы для инициализации атрибутов
    void setJournal(string c, string n) {
        card = c;
        name = n;
    }

    void setJournal(string n) {
        name = n;
        card = "0000-0000-0000-0000";
    }

    // Метод для добавления платежа
    void addPayment(const Payment& payment) {
        payments.push_back(payment);
    }

    // Метод для вывода всех платежей
    void displayPayments() const {
        cout << "Журнал учета для карты: " << card << ", Владелец: " << name << endl;
        for (const auto& payment : payments) {
            payment.display();
        }
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    AccountJournal journal;
    journal.setJournal("1234-5678-9012-3456", "Иван Иванов");

    Payment payment1;
    payment1.setPayment("2023-10-01", 500.0, "Оплата за интернет");

    Payment payment2;
    payment2.setPayment(1200.0, "Оплата за телефон");

    Payment payment3("2023-10-10", 3000.0, "Оплата за квартиру");

    journal.addPayment(payment1);
    journal.addPayment(payment2);
    journal.addPayment(payment3);

    journal.displayPayments();

    return 0;
}