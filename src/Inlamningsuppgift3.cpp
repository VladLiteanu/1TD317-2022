#include <iostream>
using namespace std;

// Deklarationer av funktionerna

void skrivInfo();

int lasEttTal();

char lasOp();

void ordna(int &a, int &b);

double berakna(int small, int big, char op);

void skrivResultat(double resultat);

int main()
{
    // Här ska deklaration av variabler finnas
    int tal1;
    int tal2;
    char op;
    double svar;

    // Kalla på funktionen skrivInfo()
    skrivInfo();

    // Läs in tal1
    tal1 = lasEttTal();

    // Läs in tal2
    tal2 = lasEttTal();

    // Läs in operatorn
    op = lasOp();

    // Kalla på funktionen ordna()
    ordna(tal1, tal2);

    // Kalla på funktionen berakna()
    svar = berakna(tal1, tal2, op);

    // Kalla på funktionen skrivResultat()
    skrivResultat(svar);

    return 0;
}

// Definitioner av funktionerna

void skrivInfo()
{
    // Skriv ut en information om programmet
    cout << "Programmet beräknar ett värde på en operation" << endl;
    cout << "med två tal och en operator." << endl;
    cout << "-----------------------------------------" << endl;
}

int lasEttTal()
{
    // Läs in ett tal
    int tal;
    cout << "Skriv ett tal: ";
    cin >> tal;
    return tal;
}

char lasOp()
{
    // Läs in en operator
    char op;
    cout << "Välj en operator (a, m, k): ";
    cin >> op;
    return op;
}

void ordna(int &a, int &b)
{
    // Ordna de två talen
    // Om a > b ska a och b byta plats
    if (a > b)
    {
        int temp = a;
        a = b;
        b = temp;
    }
}

double berakna(int small, int big, char op)
{
    // Beräkna ett värde på en operation
    // med två tal och en operator
    double resultat = 0;
    switch (op)
    {
    // Om operatorn är 'a'
    case 'a':
        // Beräkna resultatet
        for (int i = small; i <= big; i++)
        {
            resultat += i;
        }
        break;
    // Om operatorn är 'm'
    case 'm':
        // Beräkna resultatet
        resultat = 1;
        for (int i = small; i <= big; i++)
        {
            resultat *= i;
        }
        break;
    // Om operatorn är 'k'
    case 'k':
        // Beräkna resultatet
        for (int i = small; i <= big; i++)
        {
            resultat += i * i;
        }
        break;
    }
    // Returnera resultatet
    return resultat;
}

void skrivResultat(double resultat)
{
    // Skriv ut resultatet
    cout << "Resultatet är: " << resultat << endl;
}
