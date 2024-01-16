/*Задача 3: Создать и инициализировать массив из 4-х объектов типа Дробь (Fraction) и 
записать этот массив в файл в бинарном режиме.
Затем создать другой массив из 4-х объектов типа Дробь и считать в этот массив объекты из этого файла.*/
#include <iostream>
#include <fstream>
using namespace std;

class Fraction {
    int numerator = 0;
    int denominator = 1;

public:
    void setNumerator(int num) {
        numerator = num;
    }

    void setDenominator(int denom) {
        if (denom == 0) denom = 1;
        denominator = denom;
    }

    Fraction() {}

    Fraction(int num, int denom) {
        setNumerator(num);
        setDenominator(denom);
    }

    void serialize(ofstream& outFile) const {
        outFile.write(reinterpret_cast<const char*>(&numerator), sizeof(numerator));
        outFile.write(reinterpret_cast<const char*>(&denominator), sizeof(denominator));
    }

    void deserialize(ifstream& inFile) {
        inFile.read(reinterpret_cast<char*>(&numerator), sizeof(numerator));
        inFile.read(reinterpret_cast<char*>(&denominator), sizeof(denominator));
    }

    void print() const {
        cout << numerator << " / " << denominator << "\n";
    }
};

int main() {
    setlocale(0, "");

    Fraction fractions[4] = {
        Fraction(1, 2),
        Fraction(3, 4),
        Fraction(5, 6),
        Fraction(7, 8)
    };

    ofstream outFile("fractions.dat", ios::binary);
    for (const Fraction& fraction : fractions) {
        fraction.serialize(outFile);
    }
    outFile.close();

    Fraction fractionsFromFile[4];

    ifstream inFile("fractions.dat", ios::binary);
    for (Fraction& fraction : fractionsFromFile) {
        fraction.deserialize(inFile);
    }
    inFile.close();

    for (const Fraction& fraction : fractionsFromFile) {
        fraction.print();
    }

    return 0;
}
