#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <locale>
#include <windows.h>

using namespace std;

// ������� ����� - ������
class Payment {
protected:
    string date;
    double amount;
    string description;

public:
    // ������������
    Payment() : date("01.01.1970"), amount(0.0), description("��� ��������") {}

    Payment(const string& dt, double amt, const string& desc)
        : date(dt), amount(amt), description(desc) {
    }

    Payment(const Payment& other)
        : date(other.date), amount(other.amount), description(other.description) {
    }

    virtual ~Payment() {}

    // �������
    string getDate() const { return date; }
    double getAmount() const { return amount; }
    string getDescription() const { return description; }

    // �������
    void setDate(const string& date) { this->date = date; }
    void setAmount(double amount) { this->amount = amount; }
    void setDescription(const string& description) { this->description = description; }

    // ����������� �����
    virtual void print() const {
        cout << "������: " << date << ", " << amount << ", " << description << endl;
    }

    // ���������� ��������� ��� ������ � �������
    friend ostream& operator<<(ostream& os, const Payment& p) {
        os << p.date << '\n' << p.amount << '\n' << p.description << '\n';
        return os;
    }

    friend istream& operator>>(istream& is, Payment& p) {
        getline(is, p.date);
        is >> p.amount;
        is.ignore(); // ������� \n ����� �����
        getline(is, p.description);
        return is;
    }
};

// �����-��������� 1 - �����
class Income : public Payment {
private:
    string source;
    bool taxable;

public:
    Income() : source("�� ������"), taxable(false) {}

    Income(const string& dt, double amt, const string& desc, const string& src, bool tax)
        : Payment(dt, amt, desc), source(src), taxable(tax) {
    }

    Income(const Income& other)
        : Payment(other), source(other.source), taxable(other.taxable) {
    }

    void print() const override {
        cout << "�����: " << date << ", " << amount << ", " << description
            << ", ��������: " << source << ", ����������������: " << (taxable ? "��" : "���") << endl;
    }
};

// �����-��������� 2 - ������
class Expense : public Payment {
private:
    string category;
    bool deductible;

public:
    Expense() : category("�� �������"), deductible(false) {}

    Expense(const string& dt, double amt, const string& desc, const string& cat, bool ded)
        : Payment(dt, amt, desc), category(cat), deductible(ded) {
    }

    Expense(const Expense& other)
        : Payment(other), category(other.category), deductible(other.deductible) {
    }

    void print() const override {
        cout << "������: " << date << ", " << amount << ", " << description
            << ", ���������: " << category << ", ����������� ��� ���������������: " << (deductible ? "��" : "���") << endl;
    }
};

// ������� ��� ������ � �������
void saveToFile(const vector<Payment*>& list, const string& filename) {
    ofstream file(filename);
    for (const auto& p : list) {
        file << *p;
    }
    file.close();
    cout << "��������� � ���� " << filename << endl;
}

void loadFromFile(vector<Payment*>& list, const string& filename) {
    ifstream file(filename);
    while (!file.eof()) {
        Payment* p = new Payment;
        file >> *p;
        if (file) list.push_back(p);
    }
    file.close();
    cout << "��������� �� ����� " << filename << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    cout << "=== ��� 1: �������� ���������� vector<Payment*> ===" << endl;
    vector<Payment*> payments;
    payments.push_back(new Payment("01.01.2024", 1000.0, "�����"));
    payments.push_back(new Income("05.01.2024", 3000.0, "��������", "������", true));
    payments.push_back(new Expense("10.01.2024", 500.0, "��������", "���", false));

    cout << "\n=== ��� 2: �������� ��������� (������� ����) ===" << endl;
    for (const auto& p : payments) {
        p->print();
    }

    cout << "\n=== ��� 3: ������ 1-� ������� � ������� �������� � ������� ===" << endl;
    delete payments[0];
    payments.erase(payments.begin());
    payments[0]->setDescription("���������� ��������");

    cout << "\n=== ��� 4: �������� ����� ��������� ===" << endl;
    for (auto it = payments.begin(); it != payments.end(); ++it) {
        (*it)->print();
    }

    cout << "\n=== ��� 5: ��������� ������ � ���� ===" << endl;
    saveToFile(payments, "payments.txt");

    cout << "\n=== ��� 6: ��������� ������ �� ����� � ����� ��������� ===" << endl;
    vector<Payment*> loadedPayments;
    loadFromFile(loadedPayments, "payments.txt");

    for (const auto& p : loadedPayments) {
        p->print();
    }

    // ������� ������
    for (auto& p : payments) delete p;
    for (auto& p : loadedPayments) delete p;

    cout << "\n=== ���������� ��������� ===" << endl;
    return 0;
}
