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

Uzsakymas uzsakimai[100];

int readFile() {
  ifstream fs("uzsakymas.txt");
  int kiekis;
  char trash;

  fs >> kiekis;
  if (kiekis > 100 || kiekis < 1)
    return -1;

  for (int i = 0; i < kiekis; i++) {
    Uzsakymas uzsakymas;
    string temp;

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

  for(int i = 0; i < kiekis; i++){
      Uzsakymas uzsakymas = uzsakimai[i];

      cout << left << setw(18) << uzsakymas.kategorija;
      cout << left << setw(52) << uzsakymas.pavadinimas;
      cout << right << setw(10) << uzsakymas.kaina;
      cout << right << setw(8) << uzsakymas.kiekis;
      cout << endl;
  }
}

int main() {
  std::cout << "Hello, world!\n";

  int kiekis = readFile();
  if (kiekis == -1) {
    cout << "Netinkamas failas! Kiekis per didelis";
    return 0;
  }

  while (true) {
    cout << "----------------------" << endl;
    cout << "1. Perziureti visas prekes" << endl;
    cout << "2. Perziureti tam skirta kategorija prekes" << endl;
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

  }
  return 0;
}
