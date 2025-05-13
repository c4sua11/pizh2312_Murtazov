#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
using namespace std;

// === ������� ����� ===
class Article {
protected:
    string name;
    string author;
public:
    Article() : name("No name"), author("No author") {}
    Article(string _name, string _author) : name(_name), author(_author) {}
    virtual ~Article() {}

    string getName() const { return name; }
    string getAuthor() const { return author; }
    void setName(const string& _name) { name = _name; }
    void setAuthor(const string& _author) { author = _author; }

    virtual void print() const = 0;

    // ��������� << � >> ��� �������� ������
    friend ostream& operator<<(ostream& os, const Article& art) {
        os << art.name << ";" << art.author;
        return os;
    }

    friend istream& operator>>(istream& is, Article& art) {
        getline(is, art.name, ';');
        getline(is, art.author);
        return is;
    }
};

// === ���������� ===
class Scientific : public Article {
    string science;
public:
    Scientific() : science("No science") {}
    Scientific(string _name, string _author, string _science)
        : Article(_name, _author), science(_science) {
    }
    void print() const override {
        cout << "Scientific -=-=- Name: " << name << " Author: " << author << " Science: " << science << endl;
    }

    friend ostream& operator<<(ostream& os, const Scientific& s) {
        os << s.name << ";" << s.author << ";" << s.science;
        return os;
    }

    friend istream& operator>>(istream& is, Scientific& s) {
        getline(is, s.name, ';');
        getline(is, s.author, ';');
        getline(is, s.science);
        return is;
    }
};

class News : public Article {
    string area;
public:
    News() : area("No area") {}
    News(string _name, string _author, string _area)
        : Article(_name, _author), area(_area) {
    }
    void print() const override {
        cout << "News -=-=- Name: " << name << " Author: " << author << " Area: " << area << endl;
    }

    friend ostream& operator<<(ostream& os, const News& n) {
        os << n.name << ";" << n.author << ";" << n.area;
        return os;
    }

    friend istream& operator>>(istream& is, News& n) {
        getline(is, n.name, ';');
        getline(is, n.author, ';');
        getline(is, n.area);
        return is;
    }
};

// === ���������� � �������� ===
void saveToFile(const Scientific& s, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << s;
        file.close();
        cout << "��������� � ����: " << filename << endl;
    }
    else {
        cout << "������ �������� ����� ��� ������." << endl;
    }
}

void loadFromFile(Scientific& s, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        file >> s;
        file.close();
        cout << "��������� �� �����: " << filename << endl;
    }
    else {
        cout << "������ �������� ����� ��� ������." << endl;
    }
}

// === ������� ������� ===
int main() {
    setlocale(LC_ALL, "RU");
    // ������������ �����/������
    Scientific s1("Ecology Report", "Ivanov", "Biology");
    cout << "������ s1: ";
    s1.print();

    saveToFile(s1, "scientific.txt");

    Scientific s2;
    loadFromFile(s2, "scientific.txt");

    cout << "������ s2 ����� ������ �� �����: ";
    s2.print();

    return 0;
}
