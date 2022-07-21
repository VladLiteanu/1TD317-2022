//
// Programskal till Inlupp5A
//
// Hanterar fallet med 26 bokst�ver A-Z

#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// Globala konstanter:

// Tips: Anv�nd de globala konstanterna ANTAL_BOKSTAVER och ANTAL_SPRAK
// ist�llet f�r v�rdena 26 och 4 i programmet.
const int ANTAL_BOKSTAVER = 26; // A-Z
const int ANTAL_SPRAK = 4;

// 2d-arrayen TOLK_HJALP inneh�ller bokstavsfrekvensen i %
// f�r fyra spr�k. TOLK_HJALP[0][0] �r frekvensen av
// bokstaven a f�r engelska. TOLK_HJALP[0][25] �r frekvensen av
// bokstaven z f�r engelska.
// Arrayen �r en GLOBAL KONSTANT och skall allts� ej skickas
// som parameter till den funktion som beh�ver den.
const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER] =
    {{8.27, 1.48, 2.94, 4.03, 11.78, 2.22, 1.72, 6.77, // engelska
      7.39, 0.12, 0.81, 3.76, 2.85, 6.71, 7.79, 1.54,
      0.05, 5.95, 6.69, 9.07, 2.66, 1.13, 2.14, 0.19,
      1.89, 0.03},
     {7.97, 1.40, 3.55, 3.79, 16.89, 1.02, 1.00, 0.75, // franska
      7.08, 0.38, 0.04, 5.51, 2.82, 8.11, 5.19, 2.78,
      1.01, 6.69, 8.35, 7.22, 6.09, 1.35, 0.02, 0.54,
      0.30, 0.15},
     {9.50, 1.11, 1.53, 5.30, 8.94, 1.74, 3.57, 3.94, // svenska
      3.98, 0.89, 3.26, 4.93, 3.41, 8.46, 5.01, 1.77,
      0.00, 6.73, 5.56, 9.20, 1.94, 2.42, 0.00, 0.05,
      0.45, 0.00},
     {5.12, 1.95, 3.57, 5.07, 16.87, 1.35, 3.00, 5.79, // tyska
      8.63, 0.19, 1.14, 3.68, 3.12, 10.64, 1.74, 0.42,
      0.01, 6.30, 6.99, 5.19, 3.92, 0.77, 1.79, 0.01,
      0.69, 1.24}};

// Globala variabler �r ej till�tna

//--------------------------------------------------------
// H�r kommer klassdeklarationen

class Text
{
private:
  // Deklarera variabler
  string text;
  double histogram[ANTAL_BOKSTAVER] = {0};
  string filnamn;

public:
  // Konstruktor
  Text(){};
  // Destruktor
  ~Text(){};
  // Metoder
  void set_filnamn(string filnamn);
  void berakna_histogram_abs();
  void abs_till_rel();
  void plotta_histogram_rel();
  void tolkning();
  void namn_pa_fil();
  string inlasning();
};

// -------------------------------------------------------

// Huvudprogram:
int main()
{
  // Deklarera variabler
  string filnamn;
  string text = "";
  Text minText; // Ett objekt av typen Text skapas

  // Fraga om filnamn
  cout << "Ange filnamn: ";
  getline(cin, filnamn);

  // Anropa metoder fran objektet
  minText.set_filnamn(filnamn);
  minText.namn_pa_fil();
  text = minText.inlasning();
  if (text != "")
  {
    minText.berakna_histogram_abs();
    minText.abs_till_rel();
    minText.tolkning();
    minText.plotta_histogram_rel();
  }

  return 0;
}

// -------------------------------------------------------
// H�r skriver du klassimplementationen

void Text::set_filnamn(string filnamn)
{
  // Sätt filnamnet
  this->filnamn = filnamn;
}

// Beraknar histogrammet
void Text::berakna_histogram_abs()
{
  // andra rad till stora bokstaver
  for (int i = 0; i < text.length(); i++)
  {
    if (isalpha(text[i]))
    {
      text[i] = toupper(text[i]);
    }
    // Ta bort alla andra tecken
    else
    {
      text.erase(i, 1);
      i--;
    }
  }
  cout << "Totala antalet bokstaver: " << text.length() << endl;
  // Berakna histogrammet
  for (int i = 0; i < text.length(); i++)
  {
    if (isalpha(text[i]))
    {
      histogram[text[i] - 'A']++;
    }
  }
}

void Text::abs_till_rel()
{
  // Calculate the persentages of each letter
  for (int i = 0; i < ANTAL_BOKSTAVER; i++)
  {
    histogram[i] = histogram[i] / text.length() * 100;
  }
  // Round the percentages to the nearest half number
  for (int i = 0; i < ANTAL_BOKSTAVER; i++)
  {
    histogram[i] = round(histogram[i] * 2) / 2;
  }
}

void Text::plotta_histogram_rel()
{
  cout << endl;
  cout << "Bokstavsfordelning: " << endl;
  cout << endl;
  // Skriv ut ett * for varje halv procent av histogrammet
  for (int i = 0; i < ANTAL_BOKSTAVER; i++)
  {
    cout << char(i + 'A') << ": ";
    for (double j = 0; j < histogram[i]; j += 0.5)
    {
      cout << "*";
    }
    cout << endl;
  }
}

void Text::tolkning()
{
  // Rakna ut skillnaden mellan histogram och TOLK_HJALP for varje bokstav
  double skillnad[ANTAL_SPRAK][ANTAL_BOKSTAVER];
  string sprak[ANTAL_SPRAK] = {"engelska", "franska", "svenska", "tyska"};
  for (int i = 0; i < ANTAL_SPRAK; i++)
  {
    for (int j = 0; j < ANTAL_BOKSTAVER; j++)
    {
      skillnad[i][j] = TOLK_HJALP[i][j] - histogram[j];
    }
  }

  // Rakna kvadratsumman for skillnaden
  double kvadratsumman[ANTAL_SPRAK];
  for (int i = 0; i < ANTAL_SPRAK; i++)
  {
    kvadratsumman[i] = 0;
    for (int j = 0; j < ANTAL_BOKSTAVER; j++)
    {
      kvadratsumman[i] += skillnad[i][j] * skillnad[i][j];
    }
  }

  // Skriv ut kvadratsumman for varje sprak
  for (int i = 0; i < ANTAL_SPRAK; i++)
  {
    cout << "Kvadratsumman for " << sprak[i] << ": " << kvadratsumman[i] << endl;
  }

  // Valj den minsta kvadratsumman
  double min = kvadratsumman[0];
  int min_index = 0;
  for (int i = 1; i < ANTAL_SPRAK; i++)
  {
    if (kvadratsumman[i] < min)
    {
      min = kvadratsumman[i];
      min_index = i;
    }
  }
  // Skriv ut det sprak som har min kvadratsumman
  cout << "Det ar mest troligt att spraket ar " << sprak[min_index] << endl;
}

void Text::namn_pa_fil()
{
  // Check if a file name ends with .txt
  // If not, add .txt to the end of the file name
  // Check if the name if shorter than 4 characters
  if (filnamn.length() < 4)
  {
    filnamn += ".txt";
  }
  else if (filnamn.substr(filnamn.length() - 4, 4) == ".txt")
  {
    filnamn = filnamn;
  }
  else
  {
    filnamn += ".txt";
  }
  this->filnamn = filnamn;
}

string Text::inlasning()
{
  // Return the text from the file
  string temp = "";
  string rad = "";
  ifstream fil(filnamn);
  if (fil.is_open())
  {
    while (!fil.eof())
    {
      getline(fil, temp);
      rad += temp;
    }
    fil.close();
  }
  else
  {
    cout << "Det finns ingen fil med namnet " << filnamn << endl;
  }
  this->text = rad;
  return text;
}

//--------------------------------------------------------
// Funktionsdefinitioner:

// -------------------------------------------------------
// Rapport om uppgiften
