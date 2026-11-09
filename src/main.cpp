#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

struct Uzsakymas {
  string kategorija;
  string pavadinimas;
  double kaina;
  int kiekis;
};
const int MAX_SIZE = 100;
/// 10% nuolaida
const int NUOLAIDA = 10;

Uzsakymas uzsakimai[MAX_SIZE];
string kategorijos[3] = {"Dviraciai", "Dalys", "Aksesuarai"};

int readFile() {
  ifstream fs("uzsakymas.txt");
  int kiekis;
  char trash;

  fs >> kiekis;
  if (kiekis > MAX_SIZE || kiekis < 1)
    return -1;

  for (int i = 0; i < kiekis; i++) {
    Uzsakymas uzsakymas;
    string temp;

    fs >> ws;
    getline(fs, uzsakymas.kategorija, ';');
    getline(fs, uzsakymas.pavadinimas, ';');
    fs >> uzsakymas.kaina;
    fs.ignore(1);
    fs >> uzsakymas.kiekis;

    // cout << uzsakymas.kategorija << endl;
    // cout << uzsakymas.pavadinimas << endl;
    // cout <<  fixed << setprecision(2) << uzsakymas.kaina << endl;
    // cout <<  fixed << setprecision(2) << uzsakymas.kiekis << endl;
    uzsakimai[i] = uzsakymas;
  }

  return kiekis;
}

void showAll(int kiekis) {
  cout << left << setw(18) << "Kategorija";
  cout << left << setw(52) << "Pavadinimas";
  cout << right << fixed << setprecision(2) << setw(10) << "Kaina";
  cout << right << fixed << setprecision(2) << setw(8) << "Kiekis";
  cout << endl;

  for (int i = 0; i < kiekis; i++) {
    Uzsakymas uzsakymas = uzsakimai[i];

    cout << left << setw(18) << uzsakymas.kategorija;
    cout << left << setw(52) << uzsakymas.pavadinimas;
    cout << right << setw(10) << uzsakymas.kaina;
    cout << right << setw(8) << uzsakymas.kiekis;
    cout << endl;
  }
}

int chooseCategory(const string kategorijos[], int count) {
  int kategorija;

  cout << "Pasirinkite Kategorija:" << endl;
  for (int i = 0; i < count; i++) {
    cout << i + 1 << ". " << kategorijos[i] << endl;
  }

  while (true) {
    if (!(cin >> kategorija) || kategorija < 1 || kategorija > count) {
      cin.clear();
      cin.ignore(999999999, '\n');
      cout << "Invalid category." << endl;
      continue;
    }

    return kategorija - 1;
  }
}

void showCategory(int kiekis) {
  int kategorija = chooseCategory(kategorijos, size(kategorijos));

  cout << left << setw(18) << "Kategorija";
  cout << left << setw(52) << "Pavadinimas";
  cout << right << fixed << setprecision(2) << setw(10) << "Kaina";
  cout << right << fixed << setprecision(2) << setw(8) << "Kiekis";
  cout << endl;

  for (int i = 0; i < kiekis; i++) {
    Uzsakymas uzsakymas = uzsakimai[i];
    bool isSame = uzsakymas.kategorija == kategorijos[kategorija];
    if (!isSame)
      continue;

    cout << left << setw(18) << uzsakymas.kategorija;
    cout << left << setw(52) << uzsakymas.pavadinimas;
    cout << right << setw(10) << uzsakymas.kaina;
    cout << right << setw(8) << uzsakymas.kiekis;
    cout << endl;
  }
}

// Skaičiavimo funkcijos turi priimti reikalingus duomenis per parametrus
// ir grąžinti apskaičiuotas reikšmes, kurios panaudojamos programoje.
// Duomenims tarp funkcijų perduoti nenaudoti globalių kintamųjų.
int gautiKaina(int vienetoKaina, int kiekis) {
    return vienetoKaina * kiekis;
}

void calculatePrices(int kiekis, bool allCategories) {
    int kategorija;
    if(!allCategories) {
        kategorija = chooseCategory(kategorijos, size(kategorijos));
    }

    // int kainos[MAX_SIZE];
  // int nuolaidos[MAX_SIZE];
  // cout << left << setw(18) << "Kategorija";
  cout << left << setw(52) << "Pavadinimas";
  cout << right << fixed << setprecision(2) << setw(15) << "Suma";
  cout << right << fixed << setprecision(2) << setw(15) << "Nuolaida";
  cout << right << fixed << setprecision(2) << setw(15) << "Galutine Suma";
  cout << endl;

  for(int i = 0; i < kiekis; i++) {
      Uzsakymas uzsakymas = uzsakimai[i];
      double kaina = 0;
      double nuolaida = 0;

      if(!allCategories) {
          bool isSame = uzsakymas.kategorija == kategorijos[kategorija];
          if(!isSame) continue;
      }

      kaina = gautiKaina(uzsakymas.kaina, uzsakymas.kiekis);
      if(uzsakymas.kiekis >= 10) nuolaida = (kaina / NUOLAIDA);

      cout << left << setw(52) << uzsakymas.pavadinimas;
      cout << right << fixed << setprecision(2) << setw(15) << kaina;
      cout << right << fixed << setprecision(2) << setw(15) << nuolaida;
      cout << right << fixed << setprecision(2) << setw(15) <<  kaina - nuolaida;
      cout << endl;
  }
}

int main() {
  int kiekis = readFile();
  if (kiekis == -1) {
    cout << "Netinkamas failas! Kiekis per didelis";
    return 0;
  }

  while (true) {
    cout << "----------------------" << endl;
    cout << "1. Perziureti visas prekes" << endl;
    cout << "2. Perziureti tam skirta kategorija prekes" << endl;
    cout << "3. Suskaiciuoti suma, akcijas bei galutine suma." << endl;
    cout << "4. Suskaiciuoti suma, akcijas bei galutine suma tam skirtai kategirijai." << endl;
    cout << "6. Perziureti ataskaita." << endl;
    cout << "6. Issaugoti visa ataskaita i faila." << endl;
    cout << "7. Iseiti." << endl;
    cout << "----------------------" << endl;

    int pasirinkimas;
    cin >> pasirinkimas;

    if (pasirinkimas < 1 || pasirinkimas > 5) {
      cout << "!!! Netinkamas pasirinkimas !!!" << endl;
      continue;
    }

    if (pasirinkimas == 1)
      showAll(kiekis);

    if (pasirinkimas == 2)
      showCategory(kiekis);
    if (pasirinkimas == 3)
      calculatePrices(kiekis, true);
    if (pasirinkimas == 4)
      calculatePrices(kiekis, false);

  }
  return 0;
}
