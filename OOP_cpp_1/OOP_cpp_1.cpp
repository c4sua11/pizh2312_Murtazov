#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <windows.h> // для SetConsoleCP

using namespace std;

// Дополнительный класс - Платеж
class Payment {
private:
    string date;
    double amount;
    string description;

public:
    // Геттеры
    string getDate() const {
        return date;
    }

    double getAmount() const {
        return amount;
    }

    string getDescription() const {
        return description;
    }

    // Сеттеры
    void setDate(const string& date) {
        this->date = date;
    }

    void setAmount(double amount) {
        this->amount = amount;
    }

    void setDescription(const string& description) {
        this->description = description;
    }

    // Перегруженные методы
    void setPaymentDetails() {
        string input;
        cout << "Введите дату платежа (ДД.ММ.ГГГГ): ";
        getline(cin, input);
        setDate(input);

        cout << "Введите сумму платежа: ";
        cin >> amount;
        cin.ignore(); // Очищаем буфер после cin

        cout << "Введите описание платежа: ";
        getline(cin, input);
        setDescription(input);
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
    // Геттеры
    string getName() const {
        return name;
    }

    string getCardNumber() const {
        return cardNumber;
    }

    const vector<Payment>& getPayments() const {
        return payments;
    }

    // Сеттеры
    void setName(const string& name) {
        this->name = name;
    }

    void setCardNumber(const string& cardNumber) {
        this->cardNumber = cardNumber;
    }

    // Метод для добавления платежа
    void addPayment(const Payment& payment) {
        payments.push_back(payment);
    }
};

int main() {
    // Настройка консоли для корректного отображения кириллицы
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    AccountingJournal journal;

    // Настройка журнала
    string input;
    cout << "Введите название журнала: ";
    getline(cin, input);
    journal.setName(input);

    cout << "Введите номер карты: ";
    getline(cin, input);
    journal.setCardNumber(input);

    // Добавление платежей
    char choice;
    do {
        Payment payment;
        cout << "\nДобавление нового платежа:\n";
        cout << "1. Ввести данные вручную\n";
        cout << "2. Использовать готовые данные\n";
        cout << "Выберите вариант: ";
        cin >> choice;
        cin.ignore();

        if (choice == '1') {
            payment.setPaymentDetails();
        }
        else if (choice == '2') {
            payment.setPaymentDetails("15.05.2023", 1500.0, "Покупка продуктов");
        }
        else {
            cout << "Неверный выбор. Используются стандартные значения.\n";
            payment.setPaymentDetails("01.01.2023", 0.0, "Нет описания");
        }

        journal.addPayment(payment);

        cout << "\nДобавить еще один платеж? (y/n): ";
        cin >> choice;
        cin.ignore();
    } while (tolower(choice) == 'y');

    // Вывод информации
    cout << "\n=== Журнал учета денежных средств ===\n";
    cout << "Название: " << journal.getName() << endl;
    cout << "Номер карты: " << journal.getCardNumber() << endl;
    cout << "\nСписок платежей:\n";

    const vector<Payment>& payments = journal.getPayments();
    for (size_t i = 0; i < payments.size(); ++i) {
        cout << "Платеж #" << i + 1 << ":\n";
        cout << "  Дата: " << payments[i].getDate() << endl;
        cout << "  Сумма: " << payments[i].getAmount() << endl;
        cout << "  Описание: " << payments[i].getDescription() << endl;
    }

    return 0;
}