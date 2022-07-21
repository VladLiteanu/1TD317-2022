#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

const int ANTAL_BOKSTAVER = 26; // A-Z
// Globala variabler �r ej till�tna

//--------------------------------------------------------
// Funktionsdeklarationer:
// Anv�nd exakt de funktionsnamn som finns nedan

// Funktionen berakna_histogram_abs
void berakna_histogram_abs(int histogram[], string &rad);

// Funktionen skriv_histogram_abs
void skriv_histogram_abs(int histogram[], string rad);

int main()
{
  // Deklarera variabler
  string rad;
  int histogram[ANTAL_BOKSTAVER] = {0};

  // Las in en rad med text fran tangentbordet
  cout << "Ge en rad med text: ";
  getline(cin, rad);

  // Anropa funktionen berakna_histogram_abs som beraknar histogrammet
  berakna_histogram_abs(histogram, rad);

  // Anropa funktionen skriv_histogram_abs som skriver ut histogrammet
  skriv_histogram_abs(histogram, rad);

  return 0;
}

//--------------------------------------------------------
// Funktionsdefinitioner:
void berakna_histogram_abs(int histogram[], string &rad)
{
  // Andra rad till stora bokstaver
  for (int i = 0; i < rad.length(); i++)
  {
    // Om raden innehaller en bokstav
    if (isalpha(rad[i]))
    {
      rad[i] = toupper(rad[i]);
    }
    else
    // Ta bort allt annat
    {
      rad.erase(i, 1);
      i--;
    }
  }
  
  // Berakna histogrammet
  for (int i = 0; i < rad.length(); i++)
  {
    histogram[rad[i] - 'A']++;
  }
}

void skriv_histogram_abs(int histogram[], string rad)
{
  cout << "Resultat för bokstäverna A-Z" << endl;
  // Skriv ut hur många bokstäver som finns i raden
  cout << "Totala antalet bokstäver: " << rad.length() << endl;
  cout << endl;
  cout << "Bokstavsfördelning: " << endl;
  // Skriv ut histogrammet
  for (int i = 0; i < ANTAL_BOKSTAVER; i++)
  {
    cout << char(i + 'A') << ": " << histogram[i] << endl;
  }
}

// Redovisning av uppgiften i ord.
// Program som tar in en rad och skriver ut hur många gånger varje bokstav i raden förekommer.
