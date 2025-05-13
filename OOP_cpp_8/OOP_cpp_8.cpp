#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

// ����������� ���������� (��������� �� invalid_argument)
class MyException : public invalid_argument {
public:
    MyException(string str) : invalid_argument(str) {}
};

// ������ ����������� ���������� (��������� �� out_of_range)
class AnotherException : public out_of_range {
public:
    AnotherException(string str) : out_of_range(str) {}
};

template<class T>
class MyArray {
    T* arr;
    int count = 0;
    int size;
public:
    MyArray(int n) {
        if (n <= 0) throw length_error("������ ������� ������ �������� �������.");
        arr = new T[n];
        size = n;
    }

    ~MyArray() {
        delete[] arr;
    }

    void addItem(T obj) {
        try {
            if constexpr (is_pointer<T>::value) {
                if (obj == nullptr) {
                    throw MyException("������� �������� nullptr");
                }
            }
            if (count >= size) {
                throw AnotherException("������ ����������");
            }
            arr[count++] = obj;
        }
        catch (exception& e) {
            cout << "��������� ������: " << e.what() << endl;
        }
    }

    T getItem(int i) {
        if (i < 0 || i >= size) {
            throw out_of_range("������ ��� ���������");
        }
        return arr[i];
    }

    int findItem(T obj) {
        for (int i = 0; i < count; i++) {
            if (arr[i] == obj) return i;
        }
        return -1;
    }
};

class Article {
    string name;
    string author;
public:
    Article() : name("No name"), author("No author") {}
    Article(string _name, string _author) : name(_name), author(_author) {}
    virtual ~Article() {}
    virtual void print() = 0;

    string getName() { return name; }
    string getAuthor() { return author; }
    void setName(string n) { name = n; }
    void setAuthor(string a) { author = a; }
};

class Scientific : public Article {
    string science;
public:
    Scientific() : science("No science") {}
    Scientific(string _name, string _author, string _science)
        : Article(_name, _author), science(_science) {
    }

    void print() override {
        cout << "Scientific -=-=- Name: " << getName()
            << " Author: " << getAuthor()
            << " Science: " << science << endl;
    }
};

class News : public Article {
    string area;
public:
    News() : area("No area") {}
    News(string _name, string _author, string _area) {
        setName(_name);
        setAuthor(_author);
        area = _area;
    }

    void print() override {
        cout << "News -=-=- Name: " << getName()
            << " Author: " << getAuthor()
            << " Area: " << area << endl;
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    try {
        MyArray<int> intArr(3);
        intArr.addItem(10);
        intArr.addItem(20);

        cout << "������� ����� (0 ������� ����������): ";
        int x;
        cin >> x;
        if (x == 0) throw string("������: ������� �� ����");
        intArr.addItem(30 / x);

        cout << "������� ������ (>2 ������� ����������): ";
        int idx;
        cin >> idx;
        cout << "�������: " << intArr.getItem(idx) << endl;
    }
    catch (string& s) {
        cout << "��������� ����������: " << s << endl;
    }
    catch (int i) {
        cout << "������������� ����������: " << i << endl;
    }
    catch (out_of_range& e) {
        cout << "std::out_of_range: " << e.what() << endl;
    }
    catch (...) {
        cout << "������ ����������" << endl;
    }

    try {
        MyArray<char> chars(2);
        chars.addItem('a');
        chars.addItem('b');

        cout << "������� ������ (�� a-z ������� ����������): ";
        char c;
        cin >> c;
        if (c < 'a' || c > 'z') throw invalid_argument("������������ ������");
        chars.addItem(c);
    }
    catch (invalid_argument& e) {
        cout << "������ �������: " << e.what() << endl;
    }

    try {
        Scientific* s1 = new Scientific();
        Scientific* s2 = new Scientific("Article", "Petrov", "Biology");
        News* n1 = nullptr;
        News* n2 = new News("Politics", "Sidorov", "Politics");

        MyArray<Article*> articles(4);
        articles.addItem(s1);
        articles.addItem(s2);
        articles.addItem(n1); // ������� ��������� ���������
        articles.addItem(n2);

        cout << "������ ��������� ������: " << articles.findItem(n2) << endl;

        delete s1;
        delete s2;
        delete n2;
    }
    catch (...) {
        cout << "������ ���������� ������" << endl;
    }

    return 0;
}
