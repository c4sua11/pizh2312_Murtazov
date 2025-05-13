#include <iostream>
#include <string>
using namespace std;

template<class T>
class MyArray {
    T* arr;
    int count = 0;
    int size;
public:
    MyArray(int n) {
        arr = new T[n];
        size = n;
    }
    ~MyArray() {
        delete[] arr;
    }

    void addItem(T obj) {
        if (count < size) {
            arr[count] = obj;
            count++;
        }
    }

    T getItem(int index) {
        if (index >= 0 && index < count)
            return arr[index];
        else
            throw out_of_range("������ ��� ���������");
    }

    int findItem(T obj) {
        int index = -1;
        for (int i = 0; i < count; i++) {
            if (arr[i] == obj) {
                index = i;
                break;
            }
        }
        return index;
    }

    T min() {
        if (count == 0) throw runtime_error("������ ����");
        T minValue = arr[0];
        for (int i = 1; i < count; i++) {
            if (*arr[i] < *minValue) {
                minValue = arr[i];
            }
        }
        return minValue;
    }

    T max() {
        if (count == 0) throw runtime_error("������ ����");
        T maxValue = arr[0];
        for (int i = 1; i < count; i++) {
            if (*arr[i] > *maxValue) {
                maxValue = arr[i];
            }
        }
        return maxValue;
    }
};

class Article {
    string name;
    string author;
public:
    string getName() const {
        return name;
    }

    void setName(string name) {
        this->name = name;
    }

    string getAuthor() const {
        return author;
    }

    void setAuthor(string author) {
        this->author = author;
    }

    Article() {
        name = "��� ��������";
        author = "��� ������";
    }

    Article(string _name, string _author) {
        name = _name;
        author = _author;
    }

    virtual ~Article() {}

    virtual void print() = 0;

    // ��������� �� �����
    bool operator<(const Article& other) const {
        return name < other.name;
    }

    bool operator>(const Article& other) const {
        return name > other.name;
    }
};

class Scientific : public Article {
    string science;
public:
    Scientific() {
        science = "��� �����";
    }

    Scientific(string _name, string _author, string science) : Article(_name, _author) {
        this->science = science;
    }

    string getScience() const {
        return science;
    }

    void setScience(string science) {
        this->science = science;
    }

    void print() override {
        cout << "������� ������ -=- ��������: " << getName() << ", �����: " << getAuthor() << ", �����: " << getScience() << endl;
    }
};

class News : public Article {
    string area;
public:
    News() {
        area = "��� �������";
    }

    News(string _name, string _author, string area) {
        setName(_name);
        setAuthor(_author);
        this->area = area;
    }

    string getArea() const {
        return area;
    }

    void setArea(string area) {
        this->area = area;
    }

    void print() override {
        cout << "������� -=- ��������: " << getName() << ", �����: " << getAuthor() << ", �������: " << getArea() << endl;
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    MyArray<int> intArr(3);
    intArr.addItem(12);
    intArr.addItem(22);
    intArr.addItem(31);
    cout << "������ ����� 22: " << intArr.findItem(22) << endl;

    MyArray<char> charArr(3);
    charArr.addItem('a');
    charArr.addItem('b');
    charArr.addItem('c');
    cout << "������ ������� 'd': " << charArr.findItem('d') << endl;

    Scientific* sc1 = new Scientific();
    Scientific* sc2 = new Scientific("��������", "������", "��������");
    News* n1 = new News();
    News* n2 = new News("������� �������", "�������", "��������");

    MyArray<Article*> myArr(4);
    myArr.addItem(sc1);
    myArr.addItem(sc2);
    myArr.addItem(n1);
    myArr.addItem(n2);

    cout << "������ ������ n1: " << myArr.findItem(n1) << endl;

    cout << "\n����������� ������ �� ��������:" << endl;
    myArr.min()->print();

    cout << "������������ ������ �� ��������:" << endl;
    myArr.max()->print();

    delete sc1;
    delete sc2;
    delete n1;
    delete n2;

    return 0;
}
