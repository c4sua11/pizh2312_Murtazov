#include <iostream>
#include <string>
using namespace std;

class Article {
    string name;
    string author;
public:
    string getName() { return name; }
    void setName(string name) { this->name = name; }
    string getAuthor() { return author; }
    void setAuthor(string author) { this->author = author; }

    Article() {
        name = "No name";
        author = "No author";
    }
    Article(string _name, string _author) {
        name = _name;
        author = _author;
    }
    virtual ~Article() {}

    virtual void print() = 0;
};

class Scientific : public Article {
    string science;
public:
    string getScience() { return science; }
    void setScience(string science) { this->science = science; }

    Scientific() {
        science = "No science";
    }
    Scientific(string _name, string _author, string science)
        : Article(_name, _author) {
        this->science = science;
    }
    void print() override {
        cout << "Scientific -=-=- Name: " << getName()
            << " Author: " << getAuthor()
            << " Science: " << getScience() << endl;
    }
};

class News : public Article {
    string area;
public:
    string getArea() { return area; }
    void setArea(string area) { this->area = area; }

    News() {
        area = "No area";
    }
    News(string _name, string _author, string area) {
        setName(_name);
        setAuthor(_author);
        this->area = area;
    }
    void print() override {
        cout << "News -=-=- Name: " << getName()
            << " Author: " << getAuthor()
            << " Area: " << getArea() << endl;
    }
};

class Newspaper {
    string name;
    Article* arr[10];  // увеличим массив до 10 для безопасности
    static int countArr;
public:
    string getName() { return name; }
    void setName(string name) { this->name = name; }

    void setArticle(Article* art, int i) {
        if (i >= 0 && i < 10) {
            arr[i] = art;
            countArr++;
        }
    }

    Article* getArticle(int i) {
        if (i >= 0 && i < countArr) return arr[i];
        return nullptr;
    }

    void show() {
        cout << "-=-=- Newspaper -=-=- Name: " << getName() << endl;
        for (int i = 0; i < getCountArray(); i++) {
            arr[i]->print();
        }
    }

    static int getCountArray() { return countArr; }

    void operator+(Article* art) {
        if (countArr < 10) {
            setArticle(art, countArr);
        }
    }

    // Префиксный ++
    Newspaper& operator++() {
        if (countArr < 10) {
            Article* def = new Scientific(); // по умолчанию Scientific
            arr[countArr++] = def;
        }
        return *this;
    }

    // Постфиксный ++
    Newspaper operator++(int) {
        Newspaper temp = *this; // просто создаём копию с теми же указателями
        if (countArr < 10) {
            Article* def = new News(); // по умолчанию News
            arr[countArr++] = def;
        }
        return temp;
    }

    Article* operator[](int i) {
        if (i >= 0 && i < countArr) return arr[i];
        return nullptr;
    }

    friend ostream& operator<<(ostream& os, Newspaper& np);
};

int Newspaper::countArr = 0;

ostream& operator<<(ostream& os, Newspaper& np) {
    os << "Newspaper: " << np.getName() << endl;
    return os;
}

int main() {
    Scientific* sc1 = new Scientific();
    Scientific* sc2 = new Scientific("Biology article", "Petrov", "Ecology");
    News* n1 = new News();
    News* n2 = new News("Top news", "Sidorov", "Politics");

    Newspaper np;
    np.setName("Vestnik");

    np + sc1;
    np + sc2;
    np.show();

    np + n1;
    np + n2;
    np.show();

    cout << "-=-=- Operator [] -=-=-" << endl;
    np[3]->print();

    cout << "-=-=- Operator << -=-=-" << endl;
    cout << np;

    cout << "-=-=- Operator ++ префиксный -=-=-" << endl;
    ++np;
    np.show();

    cout << "-=-=- Operator ++ постфиксный -=-=-" << endl;
    np++;
    np.show();

    // Освобождаем всю память
    for (int i = 0; i < Newspaper::getCountArray(); i++) {
        delete np[i];
    }

    return 0;
}
