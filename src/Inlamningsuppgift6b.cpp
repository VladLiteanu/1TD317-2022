#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// Klassdeklaration
class Transaktion
{
private:
    string datum;
    string typ;
    string namn;
    double belopp;
    int antal_kompisar;
    string *kompisar;

public:
    Transaktion();
    ~Transaktion();
    Transaktion &operator=(const Transaktion &t);
    string hamtaNamn() const;
    double hamtaBelopp() const;
    int hamtaAntalKompisar() const;
    bool finnsKompis(const string &namnet) const;
    bool lasIn(istream &is);
    void skrivUt(ostream &os) const;
    void skrivTitel(ostream &os) const;
};

class Person
{
private:
    string namn;
    double betalat_andras;
    double skyldig;

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
    Person *personer;

public:
    PersonLista();
    ~PersonLista();
    void laggTill(Person ny_person);
    void skrivUtOchFixa(ostream &os);
    double summaSkyldig() const;
    double summaBetalat() const;
    bool finnsPerson(const string &namn);
};

class TransaktionsLista
{
private:
    int antal_transaktioner;
    Transaktion *transaktioner;

public:
    TransaktionsLista();
    ~TransaktionsLista();
    void lasIn(istream &is);
    void skrivUt(ostream &os);
    void laggTill(Transaktion &t);
    double totalKostnad() const;
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
    belopp = 0.;
    antal_kompisar = 0;
    kompisar = 0;
}

Transaktion::~Transaktion()
{
    // Ta bort alla kompisar
    delete[] kompisar;
}

Transaktion &Transaktion::operator=(const Transaktion &t)
{
    // Kopiera en transaktion
    if (this != &t)
    {
        delete[] kompisar;
        datum = t.datum;
        typ = t.typ;
        namn = t.namn;
        belopp = t.belopp;
        antal_kompisar = t.antal_kompisar;
        kompisar = new string[antal_kompisar];
        for (int i = 0; i < antal_kompisar; i++)
            kompisar[i] = t.kompisar[i];
    }
    return *this;
}

string Transaktion::hamtaNamn() const
{
    // Returnera namnet
    return namn;
}

double Transaktion::hamtaBelopp() const
{
    // Returnera beloppet
    return belopp;
}

int Transaktion::hamtaAntalKompisar() const
{
    // Returnera antalet kompisar
    return antal_kompisar;
}

bool Transaktion::finnsKompis(const string &namnet) const
{
    // Kontrollera om namnet finns i kompisarna
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
    // Las in en transaktion
    is >> datum >> typ >> namn >> belopp >> antal_kompisar;
    // Skapa en array for kompisar
    kompisar = new string[antal_kompisar + 1];
    // Las in kompisarna
    for (int i = 0; i < antal_kompisar; i++)
    {
        is >> kompisar[i];
    }
    return true;
}

void Transaktion::skrivUt(ostream &os) const
{
    // Skriv ut en transaktion
    os << datum << " " << typ << " " << namn << " " << belopp << " " << antal_kompisar << " ";
    // Skriv ut kompisarna
    for (int i = 0; i < antal_kompisar; i++)
    {
        os << kompisar[i] << " ";
    }
    os << endl;
}

void Transaktion::skrivTitel(ostream &os) const
{
    // Skriv ut titel for en transaktion
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
    // Skriv ut en person
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
    // Skapa en tom lista
    antal_personer = 0;
    personer = 0;
}

PersonLista::~PersonLista()
{
    // Ta bort alla personer
    delete[] personer;
}

void PersonLista::laggTill(Person ny_person)
{
    // Lagg till en person
    // Skapa en ny array med storre storlek
    Person *nya_personer = new Person[antal_personer + 1];
    // Kopiera alla personer till nya_personer
    for (int i = 0; i < antal_personer; i++)
    {
        nya_personer[i] = personer[i];
    }
    // Lagg till den nya personen
    nya_personer[antal_personer] = ny_person;
    // Ta bort gamla arrayen
    delete[] personer;
    // Satt den nya arrayen som personer
    personer = nya_personer;
    // oka antal_personer med 1
    antal_personer++;
}

void PersonLista::skrivUtOchFixa(ostream &os)
{
    // Ga igenom listan och skriv ut alla personer
    for (int i = 0; i < antal_personer; i++)
    {
        personer[i].skrivUt(os);
    }
}

double PersonLista::summaSkyldig() const
{
    // Summerar alla skyldiga belopp
    double summa = 0;
    for (int i = 0; i < antal_personer; i++)
    {
        summa += personer[i].hamtaSkyldig();
    }
    return summa;
}

double PersonLista::summaBetalat() const
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
    // Skapa en tom lista
    antal_transaktioner = 0;
    transaktioner = 0;
}

TransaktionsLista::~TransaktionsLista()
{
    // Ta bort alla transaktioner
    delete[] transaktioner;
}

void TransaktionsLista::lasIn(istream &is)
{
    // Las in en lista med transaktioner
    while (is)
    {
        Transaktion ny_transaktion;
        ny_transaktion.lasIn(is);
        if (ny_transaktion.hamtaNamn() != "")
        {
            laggTill(ny_transaktion);
        }
    }
}

void TransaktionsLista::skrivUt(ostream &os)
{
    cout << "Antal trans: " << antal_transaktioner << endl;

    // Skriver ut alla transaktioner
    for (int i = 0; i < antal_transaktioner; i++)
    {
        transaktioner[i].skrivUt(os);
    }
}

void TransaktionsLista::laggTill(Transaktion &t)
{
    // Lagg till en transaktion
    // Skapa en ny array med storre storlek
    Transaktion *nyTrans = new Transaktion[antal_transaktioner + 1];
    // Kopiera alla transaktioner till nya_personer
    for (int i = 0; i < antal_transaktioner; i++)
    {
        nyTrans[i] = transaktioner[i];
    }
    // Lagg till den nya transaktionen
    nyTrans[antal_transaktioner] = t;
    // Ta bort gamla arrayen
    delete[] transaktioner;
    // Satt den nya arrayen som transaktioner
    transaktioner = nyTrans;
    // oka antal_transaktioner med 1
    antal_transaktioner++;
}

double TransaktionsLista::totalKostnad() const
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
    string namn = "";
    double betalat_andras = 0;
    double skyldig = 0;

    for (int i = 0; i < antal_transaktioner; i++)
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
