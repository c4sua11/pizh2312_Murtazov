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
    Payment(const string& dt = "01.01.1970", double amt = 0.0, const string& desc = "��� ��������")
        : date(dt), amount(amt), description(desc) {
    }

    virtual ~Payment() {}

    double getAmount() const { return amount; }

    virtual void print() const {
        cout << "������: " << date << ", " << amount << ", " << description << endl;
    }

    // ��� ���������� �� ��������
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
        cout << "�����: " << date << ", " << amount << ", " << description
            << ", ��������: " << source << ", ����������������: " << (taxable ? "��" : "���") << endl;
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
        cout << "������: " << date << ", " << amount << ", " << description
            << ", ���������: " << category << ", ����������� ��� �������: " << (deductible ? "��" : "���") << endl;
    }
};

// ������ ����������
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

    // 1-2. �������� ������� ��������
    vector<shared_ptr<Payment>> payments;

    payments.push_back(make_shared<Income>("01.01.2024", 3000.0, "��������", "��������", true));
    payments.push_back(make_shared<Expense>("03.01.2024", 1200.0, "��������", "���", false));
    payments.push_back(make_shared<Income>("05.01.2024", 1800.0, "�������", "��������", true));
    payments.push_back(make_shared<Expense>("06.01.2024", 2200.0, "�����", "�����������", true));
    payments.push_back(make_shared<Payment>("07.01.2024", 2500.0, "�������"));

    printContainer(payments, "����������� ������");

    // 3. ���������� �� ��������
    sort(payments.begin(), payments.end(),
        [](const shared_ptr<Payment>& a, const shared_ptr<Payment>& b) {
            return *a > *b;
        });

    printContainer(payments, "������ ����� ���������� �� ��������");

    // 5. ����� ������� �������� > 2000
    auto found = find_if(payments.begin(), payments.end(),
        [](const shared_ptr<Payment>& p) {
            return p->getAmount() > 2000;
        });

    if (found != payments.end()) {
        cout << "\n������ ������� > 2000:" << endl;
        (*found)->print();
    }
    else {
        cout << "\n������� > 2000 �� ������." << endl;
    }

    // 6. ���������� �������� > 2000 � list
    list<shared_ptr<Payment>> highPayments;

    copy_if(payments.begin(), payments.end(), back_inserter(highPayments),
        [](const shared_ptr<Payment>& p) {
            return p->getAmount() > 2000;
        });

    printContainer(highPayments, "������ ���������: �������� > 2000");

    // 8. ���������� �� �����������
    sort(payments.begin(), payments.end(),
        [](const shared_ptr<Payment>& a, const shared_ptr<Payment>& b) {
            return *a < *b;
        });

    highPayments.sort([](const shared_ptr<Payment>& a, const shared_ptr<Payment>& b) {
        return *a < *b;
        });

    // 9. ����� ��������������� �����������
    printContainer(payments, "������ ��������� ����� ���������� �� �����������");
    printContainer(highPayments, "������ ��������� ����� ���������� �� �����������");

    return 0;
}
