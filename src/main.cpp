#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

const int MAX_SIZE = 100;
/// 10% nuolaida
const int NUOLAIDA = 10;

const string kategorijuVardai[3] = {"Dviraciai", "Dalys", "Aksesuarai"};

int readFile(string kategorijos[], string pavadinimai[], double kainos[], int kiekiai[]) {
  ifstream fs("uzsakymas.txt");
  int kiekis;
  char trash;

  fs >> kiekis;
  if (kiekis > MAX_SIZE || kiekis < 1)
    return -1;

  for (int i = 0; i < kiekis; i++) {
    fs >> ws;
    getline(fs, kategorijos[i], ';');
    getline(fs, pavadinimai[i], ';');
    fs >> kainos[i];
    fs.ignore(1);
    fs >> kiekiai[i];
  }

  return kiekis;
}

void showAll(int kiekis, const string kategorijos[], const string pavadinimai[], const double kainos[], const int kiekiai[]) {
  cout << left << setw(18) << "Kategorija";
  cout << left << setw(52) << "Pavadinimas";
  cout << right << fixed << setprecision(2) << setw(10) << "Kaina";
  cout << right << fixed << setprecision(2) << setw(8) << "Kiekis";
  cout << endl;

  for (int i = 0; i < kiekis; i++) {
    cout << left << setw(18) << kategorijos[i];
    cout << left << setw(52) << pavadinimai[i];
    cout << right << setw(10) << kainos[i];
    cout << right << setw(8) << kiekiai[i];
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

void showCategory(int kiekis, const string kategorijos[], const string pavadinimai[], const double kainos[], const int kiekiai[]) {
  int kategorija = chooseCategory(kategorijuVardai, size(kategorijuVardai));

  cout << left << setw(18) << "Kategorija";
  cout << left << setw(52) << "Pavadinimas";
  cout << right << fixed << setprecision(2) << setw(10) << "Kaina";
  cout << right << fixed << setprecision(2) << setw(8) << "Kiekis";
  cout << endl;

  for (int i = 0; i < kiekis; i++) {
    bool isSame = kategorijos[i] == kategorijuVardai[kategorija];
    if (!isSame)
      continue;

    cout << left << setw(18) << kategorijos[i];
    cout << left << setw(52) << pavadinimai[i];
    cout << right << setw(10) << kainos[i];
    cout << right << setw(8) << kiekiai[i];
    cout << endl;
  }
}

// Skaičiavimo funkcijos turi priimti reikalingus duomenis per parametrus
// ir grąžinti apskaičiuotas reikšmes, kurios panaudojamos programoje.
// Duomenims tarp funkcijų perduoti nenaudoti globalių kintamųjų.
int gautiKaina(int vienetoKaina, int kiekis) {
    return vienetoKaina * kiekis;
}

double calculateCategoryTotal(string pasirinktaKategorija, int kiekis,
                              const string kategorijos[], const double kainos[],
                              const int kiekiai[]) {
  double suma = 0;
  for (int i = 0; i < kiekis; i++) {
    if (kategorijos[i] == pasirinktaKategorija) {
      double eilutesSuma = kainos[i] * kiekiai[i];
      double nuolaida = 0;
      if (kiekiai[i] >= 10) {
        nuolaida = eilutesSuma / NUOLAIDA;
      }
      suma += eilutesSuma - nuolaida;
    }
  }
  return suma;
}

void showReport(ostream &out, int kiekis, const string kategorijos[], const string pavadinimai[], const double kainos[], const int kiekiai[]) {
  double suma = 0;
  double nuolaida = 0;

  out << "Uzsakymo ataskaita" << endl;
  out << left << setw(18) << "Kategorija";
  out << left << setw(52) << "Pavadinimas";
  out << right << setw(10) << "Kaina";
  out << setw(8) << "Kiekis";
  out << setw(15) << "Suma";
  out << setw(15) << "Nuolaida";
  out << setw(15) << "Galutine Suma" << endl;

  for (int i = 0; i < kiekis; i++) {
    double eilutesSuma = kainos[i] * kiekiai[i];
    double eilutesNuolaida = 0;
    if (kiekiai[i] >= 10) {
      eilutesNuolaida = eilutesSuma / NUOLAIDA;
    }

    suma += eilutesSuma;
    nuolaida += eilutesNuolaida;

    out << left << setw(18) << kategorijos[i];
    out << setw(52) << pavadinimai[i];
    out << right << fixed << setprecision(2) << setw(10) << kainos[i];
    out << setw(8) << kiekiai[i];
    out << setw(15) << eilutesSuma;
    out << setw(15) << eilutesNuolaida;
    out << setw(15) << eilutesSuma - eilutesNuolaida << endl;
  }

  out << string(135, '-') << endl;
  out << right << setw(98) << "Uzsakymo suma:" << setw(15) << suma << endl;
  out << right << setw(98) << "Nuolaida:" << setw(15) << nuolaida << endl;
  out << right << setw(98) << "Galutine suma:" << setw(15) << suma - nuolaida << endl;
  out << endl << "Sumos pagal kategorijas" << endl;
  for (int i = 0; i < size(kategorijuVardai); i++) {
    out << right << setw(98) << kategorijuVardai[i]
        << fixed << setprecision(2) << setw(15)
        << calculateCategoryTotal(kategorijuVardai[i], kiekis, kategorijos, kainos, kiekiai)
        << endl;
  }
}

void saveReport(int kiekis, const string kategorijos[], const string pavadinimai[], const double kainos[], const int kiekiai[]) {
  ofstream fs("ataskaita.txt");
  if (!fs) {
    cout << "Nepavyko sukurti ataskaitos failo." << endl;
    return;
  }

  showReport(fs, kiekis, kategorijos, pavadinimai, kainos, kiekiai);
  cout << "Ataskaita issaugota faile ataskaita.txt" << endl;
}

void calculatePrices(int kiekis, bool allCategories, const string kategorijos[], const string pavadinimai[], const double kainos[], const int kiekiai[]) {
    int kategorija;
    if(!allCategories) {
        kategorija = chooseCategory(kategorijuVardai, size(kategorijuVardai));
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
      double kaina = 0;
      double nuolaida = 0;

      if(!allCategories) {
          bool isSame = kategorijos[i] == kategorijuVardai[kategorija];
          if(!isSame) continue;
      }

      kaina = gautiKaina(kainos[i], kiekiai[i]);
      if(kiekiai[i] >= 10) nuolaida = (kaina / NUOLAIDA);

      cout << left << setw(52) << pavadinimai[i];
      cout << right << fixed << setprecision(2) << setw(15) << kaina;
      cout << right << fixed << setprecision(2) << setw(15) << nuolaida;
      cout << right << fixed << setprecision(2) << setw(15) <<  kaina - nuolaida;
      cout << endl;
  }
}

int main() {
  string kategorijos[MAX_SIZE];
  string pavadinimai[MAX_SIZE];
  double kainos[MAX_SIZE];
  int kiekiai[MAX_SIZE];
  int kiekis = readFile(kategorijos, pavadinimai, kainos, kiekiai);
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
    cout << "5. Perziureti ataskaita." << endl;
    cout << "6. Issaugoti visa ataskaita i faila." << endl;
    cout << "7. Iseiti." << endl;
    cout << "----------------------" << endl;

    int pasirinkimas;
    cin >> pasirinkimas;

    if (pasirinkimas < 1 || pasirinkimas > 7) {
      cout << "!!! Netinkamas pasirinkimas !!!" << endl;
      continue;
    }

    if (pasirinkimas == 1)
      showAll(kiekis, kategorijos, pavadinimai, kainos, kiekiai);

    if (pasirinkimas == 2)
      showCategory(kiekis, kategorijos, pavadinimai, kainos, kiekiai);
    if (pasirinkimas == 3)
      calculatePrices(kiekis, true, kategorijos, pavadinimai, kainos, kiekiai);
    if (pasirinkimas == 4)
      calculatePrices(kiekis, false, kategorijos, pavadinimai, kainos, kiekiai);
    if (pasirinkimas == 5)
      showReport(cout, kiekis, kategorijos, pavadinimai, kainos, kiekiai);
    if (pasirinkimas == 6)
      saveReport(kiekis, kategorijos, pavadinimai, kainos, kiekiai);
    if (pasirinkimas == 7)
      break;

  }
  return 0;
}
