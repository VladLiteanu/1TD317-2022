#include <iostream>
#include <limits>

using namespace std;

int main()
{
    // Deklaration av variabler
    int startnummer = 1;
    int startTidTimmar;
    int startTidMinuter;
    int startTidSekunder;
    int slutTidTimmar;
    int slutTidMinuter;
    int slutTidSekunder;
    int antal = 0;
    int lastTime = std::numeric_limits<int>::max();
    int winnerNummer;
    int winnerTidTimmar;
    int winnerTidMinuter;
    int winnerTidSekunder;

    // Om startnummer är ett positivt heltal
    while (startnummer > 0)
    {
        // Fråga efter startnummer
        cout << "Startnummer?" << endl;
        cin >> startnummer;
        // Kolla om startnummer är ett positivt heltal
        if (startnummer <= 0)
        {
            // Lämna while loopen
            continue;
        }
        // Addera 1 till antal spelare
        antal++;
        // Fråga efter starttid
        cout << "Starttid? (hh:mm:ss)" << endl;
        cin >> startTidTimmar >> startTidMinuter >> startTidSekunder;
        // Fråga efter sluttid
        cout << "Måltid? (hh:mm:ss)" << endl;
        cin >> slutTidTimmar >> slutTidMinuter >> slutTidSekunder;

        // Konvertera starttid till sekunder
        startTidTimmar *= 3600;
        startTidMinuter *= 60;
        startTidSekunder *= 1;
        // Kombinera starttid
        int Starttid_seconds = startTidTimmar + startTidMinuter + startTidSekunder;

        // Konvertera sluttid till sekunder
        slutTidTimmar *= 3600;
        slutTidMinuter *= 60;
        slutTidSekunder *= 1;
        // Kombinera sluttid
        int Måltid_seconds = slutTidTimmar + slutTidMinuter + slutTidSekunder;

        // Calcylera tids skillnaden
        int tid_diff = Måltid_seconds - Starttid_seconds;
        // Kolla om tids skillnaden är mindre än 0
        if (tid_diff < 0)
        {
            // Lägg på 24 timmar till tids skillnaden
            tid_diff += 86400;
        }
        // Kolla om tids skillnaden är mindre än lastTime
        if (tid_diff < lastTime)
        {
            // Konvertera tids skillnaden till timmar, minuter och sekunder
            int tid_hours = tid_diff / 3600;
            int tid_minutes = (tid_diff % 3600) / 60;
            int tid_seconds = (tid_diff % 3600) % 60;
            // Sätt senaste spelaren som vinare
            winnerNummer = startnummer;
            winnerTidTimmar = tid_hours;
            winnerTidMinuter = tid_minutes;
            winnerTidSekunder = tid_seconds;
            lastTime = tid_diff;
        }
    }
    // Skriv ut vinnaren
    if (antal == 0)
    {
        cout << "Inga tävlande" << endl;
    }
    else
    {
        cout << "Vinnare är startnr: " << winnerNummer << endl;
        cout << "Tim: " << winnerTidTimmar << " Min: " << winnerTidMinuter << " Sek: " << winnerTidSekunder << endl;
        cout << "Antal tävlande: " << antal << endl;
    }

    cout << "Programmet avslutas" << endl;
    return 0;
}
