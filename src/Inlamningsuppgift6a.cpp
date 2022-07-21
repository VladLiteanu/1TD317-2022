#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// Globala konstanter:
const int MAX_PERSONER = 10;
const int MAX_TRANSAKTIONER = 30;

//--------------------------------------------------------
// Har kommer klassdeklarationen
class Transaktion
{
private:
    string datum;
    string typ;
    string namn;
    double belopp;
    int antal_kompisar;
    string kompisar[MAX_PERSONER];

public:
    Transaktion();
    ~Transaktion();
    string hamtaNamn();
    double hamtaBelopp();
    int hamtaAntalKompisar();
    bool finnsKompis(const string &namnet);
    bool lasIn(istream &is);
    void skrivUt(ostream &os);
    void skrivTitel(ostream &os);
};

class Person
{
private:
    string namn;
    double betalat_andras; // ligger ute med totalt
    double skyldig;        // skyldig totalt

public:
    Person();
    Person(const string &namn, double betalat_andras, double skyldig);
    string hamtaNamn();
    double hamtaBetalat();
    double hamtaSkyldig();
    void skrivUt(ostream &os);
};

class PersonLista
{
private:
    int antal_personer;
    Person personer[MAX_PERSONER];

public:
    PersonLista();
    ~PersonLista();
    void laggTill(Person ny_person);
    void skrivUtOchFixa(ostream &os);
    double summaSkyldig();
    double summaBetalat();
    bool finnsPerson(const string &namn);
};

class TransaktionsLista
{
private:
    int antal_transaktioner;
    Transaktion transaktioner[MAX_TRANSAKTIONER];

public:
    TransaktionsLista();
    ~TransaktionsLista();
    void lasIn(istream &is);
    void skrivUt(ostream &os);
    void laggTill(Transaktion &t);
    double totalKostnad();
    double liggerUteMed(const string &namnet);
    double arSkyldig(const string &namnet);
    PersonLista fixaPersoner();
};

// -------------------------------------------------------
// Huvudprogram:
int main()
{
    cout << "Startar med att lasa fran en fil." << endl;

    // Deklarera variabler
    TransaktionsLista transaktioner;
    std::ifstream is("resa.txt");
    // Kolla om filen finns
    if (!is)
    {
        cout << "Kunde inte oppna filen." << endl;
        return 1;
    }
    // Las in filen
    transaktioner.lasIn(is);
    // Stang filen
    is.close();

    // Visa menyn och las in val
    int operation = 1;
    while (operation != 0)
    {
        cout << endl;
        cout << "Valj i menyn nedan:" << endl;
        cout << "0. Avsluta. Alla transaktioner sparas pa fil." << endl;
        cout << "1. Skriv ut information om alla transaktioner." << endl;
        cout << "2. Las in en transaktion fran tangentbordet." << endl;
        cout << "3. Berakna totala kostnaden." << endl;
        cout << "4. Hur mycket arr en viss person skyldig?" << endl;
        cout << "5. Hur mycket ligger en viss person ute med?" << endl;
        cout << "6. Lista alla personer mm och FIXA" << endl;

        cin >> operation;
        cout << endl;

        switch (operation)
        {
        case 1:
        {
            transaktioner.skrivUt(cout);
            break;
        }
        case 2:
        {
            Transaktion transaktion;
            cout << "Ange transaktion i foljande format" << endl;
            transaktion.skrivTitel(cout);
            transaktion.lasIn(cin);
            transaktioner.laggTill(transaktion);
            break;
        }
        case 3:
        {
            cout << "Den totala kostnanden for resan var "
                 << transaktioner.totalKostnad() << endl;
            break;
        }
        case 4:
        {
            cout << "Ange personen: ";
            string namn;
            cin >> namn;
            double ar_skyldig = transaktioner.arSkyldig(namn);
            if (ar_skyldig == 0.)
                cout << "Kan inte hitta personen " << namn << endl;
            else
                cout << namn << " ar skyldig " << ar_skyldig << endl;
            break;
        }
        case 5:
        {
            cout << "Ange personen: ";
            string namn;
            cin >> namn;
            double ligger_ute_med = transaktioner.liggerUteMed(namn);
            if (ligger_ute_med == 0.)
                cout << "Kan inte hitta personen " << namn << endl;
            else
                cout << namn << " ligger ute med " << ligger_ute_med << endl;
            break;
        }
        case 6:
        {
            cout << "Nu skapar vi en personarray och reder ut det hela!" << endl;
            PersonLista lista = transaktioner.fixaPersoner();
            lista.skrivUtOchFixa(cout);
            break;
        }
        }
    }

    std::ofstream os("transaktioner.txt");
    transaktioner.skrivUt(os);
    os.close();

    return 0;
}

// -------------------------------------------------------
// Klassimplementationen:
// Transaktion
Transaktion::Transaktion()
{
    // Skapa en tom transaktion
    datum = "";
    typ = "";
    namn = "";
    belopp = 0;
    antal_kompisar = 0;
}

Transaktion::~Transaktion()
{
}

string Transaktion::hamtaNamn()
{
    // Returnera namnet
    return namn;
}

double Transaktion::hamtaBelopp()
{
    // Returnera beloppet
    return belopp;
}

int Transaktion::hamtaAntalKompisar()
{
    // Returnera antalet kompisar
    return antal_kompisar;
}

bool Transaktion::finnsKompis(const string &namnet)
{
    // Kontrollera om namnet finns i kompislistan
    for (int i = 0; i < antal_kompisar; i++)
    {
        if (kompisar[i] == namnet)
        {
            return true;
        }
    }
    return false;
}

bool Transaktion::lasIn(istream &is)
{
    // Las in en transaktion fran istreamen
    is >> datum >> typ >> namn >> belopp >> antal_kompisar;
    for (int i = 0; i < antal_kompisar; i++)
    {
        is >> kompisar[i];
    }
    // Ta bort gamla rader om det finns
    for (int i = antal_kompisar; i < MAX_PERSONER; i++)
    {
        kompisar[i] = "";
    }
    return true;
}

void Transaktion::skrivUt(ostream &os)
{
    // Skriv ut en transaktion till os
    os << datum << "\t" << typ << "\t" << namn << "\t" << belopp << "\t" << antal_kompisar << "\t";
    // Skriv ut kompisarna
    for (int i = 0; i < MAX_PERSONER; i++)
    {
        os << kompisar[i] << "\t";
    }
    os << endl;
}

void Transaktion::skrivTitel(ostream &os)
{
    // Skriv ut titeln
    os << "Datum \tTyp \tNamn \tBelopp \tAntal \tKompisar " << endl;
}

// Person
Person::Person()
{
    // Skapa en tom person
    namn = "";
    betalat_andras = 0;
    skyldig = 0;
}

Person::Person(const string &namn, double betalat_andras, double skyldig)
{
    // Skapa en person med namn, betalat_andras och skyldig
    this->namn = namn;
    this->betalat_andras = betalat_andras;
    this->skyldig = skyldig;
}

string Person::hamtaNamn()
{
    // Returnera namnet
    return namn;
}

double Person::hamtaBetalat()
{
    // Returnera betalat_andras
    return betalat_andras;
}

double Person::hamtaSkyldig()
{
    // Returnera skyldig
    return skyldig;
}

void Person::skrivUt(ostream &os)
{
    // Skriv ut en person till os
    os << namn << " ligger ute med: " << betalat_andras << " och ar skyldig " << skyldig;
    // Kolla om personen maste betala eller fa tillbaka
    if (skyldig < betalat_andras)
    {
        os << ". Ska ha " << betalat_andras - skyldig << " fran potten!" << endl;
    }
    else
    {
        os << ". Ska lagga " << skyldig - betalat_andras << " till potten!" << endl;
    }
}

// PersonLista
PersonLista::PersonLista()
{
    // Skapa en tom personlista
    antal_personer = 0;
}

PersonLista::~PersonLista()
{
}

void PersonLista::laggTill(Person ny_person)
{
    // Lagg till en person i listan
    personer[antal_personer] = ny_person;
    antal_personer++;
}

void PersonLista::skrivUtOchFixa(ostream &os)
{
    // Ga igenom listan och skriv ut alla personer
    for (int i = 0; i < antal_personer - 1; i++)
    {
        personer[i].skrivUt(os);
    }
}

double PersonLista::summaSkyldig()
{
    // Summerar alla skyldiga belopp
    double summa = 0;
    for (int i = 0; i < antal_personer; i++)
    {
        summa += personer[i].hamtaSkyldig();
    }
    return summa;
}

double PersonLista::summaBetalat()
{
    // Summerar alla betalade belopp
    double summa = 0;
    for (int i = 0; i < antal_personer; i++)
    {
        summa += personer[i].hamtaBetalat();
    }
    return summa;
}

bool PersonLista::finnsPerson(const string &namn)
{
    // Kollar om en person finns i listan
    for (int i = 0; i < antal_personer; i++)
    {
        if (personer[i].hamtaNamn() == namn)
        {
            return true;
        }
    }
    return false;
}

// TransaktionLista
TransaktionsLista::TransaktionsLista()
{
    // Skapa en tom transaktionslista
    antal_transaktioner = 0;
}

TransaktionsLista::~TransaktionsLista()
{
}

void TransaktionsLista::lasIn(istream &is)
{
    // Laser in alla transaktioner fran filen 
    while (is)
    {
        Transaktion ny_transaktion;
        ny_transaktion.lasIn(is);
        ny_transaktion.hamtaBelopp();

        if (ny_transaktion.hamtaNamn() != "")
        {
            transaktioner[antal_transaktioner] = ny_transaktion;
            antal_transaktioner++;
        }
    }
}

void TransaktionsLista::skrivUt(ostream &os)
{
    cout << "Antal trans: " << antal_transaktioner << endl;
    // Skriver ut alla transaktioner
    transaktioner->skrivTitel(os);
    for (int i = 0; i < antal_transaktioner; i++)
    {
        transaktioner[i].skrivUt(os);
    }
}

void TransaktionsLista::laggTill(Transaktion &t)
{
    // Lagger till en ny transaktion i listan
    transaktioner[antal_transaktioner] = t;
    antal_transaktioner++;
}

double TransaktionsLista::totalKostnad()
{
    // Summerar alla transaktioner
    double summa = 0;
    for (int i = 0; i < antal_transaktioner; i++)
    {
        summa += transaktioner[i].hamtaBelopp();
    }
    return summa;
}

double TransaktionsLista::liggerUteMed(const string &namnet)
{
    // Summerar alla transaktioner som ligger ut med namnet
    double summa = 0.;
    for (int i = 0; i < antal_transaktioner; i++)
        if (transaktioner[i].hamtaNamn() == namnet)
            summa += transaktioner[i].hamtaBelopp() *
                     (1.0 - 1.0 / (transaktioner[i].hamtaAntalKompisar() + 1));
    return summa;
}

double TransaktionsLista::arSkyldig(const string &namnet)
{
    // Summerar alla transaktioner som en person ar skyldig
    double summa = 0;
    for (int i = 0; i < antal_transaktioner; i++)
    {
        if (transaktioner[i].finnsKompis(namnet))
        {
            summa += transaktioner[i].hamtaBelopp() / (transaktioner[i].hamtaAntalKompisar() + 1);
        }
    }
    return summa;
}

PersonLista TransaktionsLista::fixaPersoner()
{
    // Skapar en personlista med alla personer och hur mycket de ska betala eller fa tillbaka
    PersonLista personList;
    string namn;
    double betalat_andras = 0;
    double skyldig = 0;

    for (int i = 0; i <= antal_transaktioner; i++)
    {
        namn = transaktioner[i].hamtaNamn();
        if (!personList.finnsPerson(namn))
        {
            skyldig = arSkyldig(namn);
            betalat_andras = liggerUteMed(namn);
            Person person(namn, betalat_andras, skyldig);
            personList.laggTill(person);
        }
    }
    return personList;
}
