#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <locale>
#include <windows.h>

using namespace std;

// ������� ����������� ����� Payment
class Payment {
protected:
    string date;
    double amount;
    string description;
    static int totalPayments; // ����������� ������� ��������

public:
    Payment() : date("01.01.1970"), amount(0.0), description("��� ��������") {
        totalPayments++;
    }

    Payment(const string& dt, double amt, const string& desc)
        : date(dt), amount(amt), description(desc) {
        totalPayments++;
    }

    virtual ~Payment() {
        totalPayments--;
    }

    // ����� ����������� �������
    virtual void printDetails() const = 0;
    virtual string serialize() const = 0;
    virtual Payment* clone() const = 0;

    // ����������� ����� ��� ��������� ���������� ��������
    static int getTotalPayments() {
        return totalPayments;
    }

    // ������� � �������
    string getDate() const { return date; }
    double getAmount() const { return amount; }
    string getDescription() const { return description; }
    void setDate(const string& dt) { date = dt; }
    void setAmount(double amt) { amount = amt; }
    void setDescription(const string& desc) { description = desc; }
};

// ������������� ����������� ����������
int Payment::totalPayments = 0;

// ����� Income (������)
class Income : public Payment {
private:
    string source;
    bool isTaxable;

public:
    Income() : source("�� ������"), isTaxable(false) {}

    Income(const string& dt, double amt, const string& desc,
        const string& src, bool tax)
        : Payment(dt, amt, desc), source(src), isTaxable(tax) {
    }

    ~Income() override = default;

    // ���������� ����������� �������
    void printDetails() const override {
        cout << "�����: " << date << "\n"
            << "  �����: " << amount << " ���.\n"
            << "  ��������: " << description << "\n"
            << "  ��������: " << source << "\n"
            << "  ����������������: " << (isTaxable ? "��" : "���") << "\n\n";
    }

    string serialize() const override {
        return "INCOME|" + date + "|" + to_string(amount) + "|" +
            description + "|" + source + "|" + (isTaxable ? "1" : "0");
    }

    Payment* clone() const override {
        return new Income(*this);
    }

    // �������������� ������
    string getSource() const { return source; }
    bool getIsTaxable() const { return isTaxable; }
    void setSource(const string& src) { source = src; }
    void setIsTaxable(bool tax) { isTaxable = tax; }
};

// ����� Expense (�������)
class Expense : public Payment {
private:
    string category;
    bool isEssential;

public:
    Expense() : category("�� �������"), isEssential(false) {}

    Expense(const string& dt, double amt, const string& desc,
        const string& cat, bool essential)
        : Payment(dt, amt, desc), category(cat), isEssential(essential) {
    }

    ~Expense() override = default;

    // ���������� ����������� �������
    void printDetails() const override {
        cout << "������: " << date << "\n"
            << "  �����: " << amount << " ���.\n"
            << "  ��������: " << description << "\n"
            << "  ���������: " << category << "\n"
            << "  ������������: " << (isEssential ? "��" : "���") << "\n\n";
    }

    string serialize() const override {
        return "EXPENSE|" + date + "|" + to_string(amount) + "|" +
            description + "|" + category + "|" + (isEssential ? "1" : "0");
    }

    Payment* clone() const override {
        return new Expense(*this);
    }

    // �������������� ������
    string getCategory() const { return category; }
    bool getIsEssential() const { return isEssential; }
    void setCategory(const string& cat) { category = cat; }
    void setIsEssential(bool essential) { isEssential = essential; }
};

// �������� ����� AccountingJournal
class AccountingJournal {
private:
    string journalName;
    vector<unique_ptr<Payment>> payments;
    static int totalInJournal; // ����������� ������� �������� � �������

public:
    AccountingJournal() : journalName("��� ��������") {}

    AccountingJournal(const string& name) : journalName(name) {}

    ~AccountingJournal() {
        totalInJournal -= payments.size();
    }

    // ����� ��� ���������� �������
    void addPayment(unique_ptr<Payment> payment) {
        payments.push_back(move(payment));
        totalInJournal++;
    }

    // ����� ������ ���� ������
    void printAll() const {
        cout << "=== ������ �����: " << journalName << " ===\n";
        cout << "����� ��������: " << payments.size() << "\n\n";

        for (const auto& payment : payments) {
            payment->printDetails();
        }

        cout << "=== ����� ������ ===\n";
    }

    // ����������� ����� ��� ��������� ���������� �������� � ��������
    static int getTotalInJournals() {
        return totalInJournal;
    }

    // ������� � �������
    string getJournalName() const { return journalName; }
    void setJournalName(const string& name) { journalName = name; }
};

// ������������� ����������� ����������
int AccountingJournal::totalInJournal = 0;

int main() {
    // ��������� ������� ��� ���������
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    cout << "=== ��� 1: �������� ��������� �� �������� �������� ===\n";
    cout << "����� �������� � �������: " << Payment::getTotalPayments() << endl;
    cout << "�������� � ��������: " << AccountingJournal::getTotalInJournals() << endl;

    cout << "\n=== ��� 2: �������� �������� ===\n";
    auto income1 = make_unique<Income>("15.05.2023", 50000, "��������", "�������� �", true);
    auto expense1 = make_unique<Expense>("16.05.2023", 1500, "��������", "�������", true);

    cout << "����� �������� � �������: " << Payment::getTotalPayments() << endl;
    cout << "�������� � ��������: " << AccountingJournal::getTotalInJournals() << endl;

    cout << "\n=== ��� 3: ���������� � ������ ===\n";
    AccountingJournal journal("�������� ������");
    journal.addPayment(move(income1));
    journal.addPayment(move(expense1));

    cout << "����� �������� � �������: " << Payment::getTotalPayments() << endl;
    cout << "�������� � ��������: " << AccountingJournal::getTotalInJournals() << endl;

    cout << "\n=== ��� 4: ����� ������� ===\n";
    journal.printAll();

    cout << "\n=== ��� 5: �������� �������� ===\n";
    // ������� ������������� ��������� ��� ������ �� scope

    return 0;
}