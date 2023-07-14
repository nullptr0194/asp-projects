#include "fje.h"

int main() {

	Elem* prvi = nullptr;
	Elem* trenutni = nullptr;
	int izb, brPitanja = 0, ispisMenija=0;

	Node* pronadjen, * pronadjenOdgovor;

	while (1) {
		if (ispisMenija % 4 == 0)
			ispisiMeni();
		ispisMenija++;

		string strg, odg;

		cout << endl << "Unesite vas izbor:";
		cin >> izb;

		switch (izb)
		{
		case 0: {
			oslobodi(prvi);
			cout << endl << "Bon Voyage!";
			return 0;
			break;
		}

		case 1: {
			cout << "unesi pitanje:";
			getchar();
			getline(cin, strg);
			prvi = dodajPitanje(strg, &trenutni, prvi, brPitanja);
			break;
		}

		case 2: {
			cout << "Na koje pitanje zelite da odgovorite?" << endl;
			getchar();
			getline(cin, strg);
			pronadjen = pretraziPitanje(prvi, strg);
			if (!pronadjen) {
				cout << "Dato pitnaje ne postoji" << endl; break;
			}
			cout << "Ako zelite da odgovorite na postojeci odgovor, unesite ga, ako ne, enter:" << endl;
			getline(cin, odg);
			if (odg == "") {
				cout << "Unesite vas odgovor" << endl;
				getline(cin, odg);
				dodajOdgovor(&pronadjen, odg);
				break;
			}
			pronadjenOdgovor = pretraziOgovor(pronadjen, odg);
			if (!pronadjenOdgovor) {
				cout << "Dati odgovor ne postoji" << endl;
				break;
			}
			cout << "Unesite vas odgovor" << endl;
			getline(cin, odg);


			dodajOdgovor(&pronadjenOdgovor, odg);
			break;
		}

		case 3: {
			cout << "Unesite vase pitanje:" << endl;
			getchar();
			getline(cin, strg);
			pronadjen = pretraziPitanje(prvi, strg);
			if (!pronadjen)
				cout << "Dato pitnaje ne postoji" << endl;
			else
				cout << "Pitanje pronadjeno!" << endl;
			break;
		}

		case 4: {
			cout << "Trazite odgovor na koje pitanje?" << endl;
			getchar();
			getline(cin, strg);
			pronadjen = pretraziPitanje(prvi, strg);
			if (!pronadjen) {
				cout << "Dato pitnaje ne postoji" << endl;
				break;
			}
			cout << "Koji odgovor pretrazujete?" << endl;
			getline(cin, odg);

			pronadjenOdgovor = pretraziOgovor(pronadjen, odg);
			if (!pronadjenOdgovor)
				cout << "Dati odgovor ne postoji" << endl;
			else
				cout << "Odgovor pronadjen!" << endl;
			break;
		}

		case 5: {
			cout << "Menjate ocenu odgovora na koje pitanje?" << endl;
			getchar();
			getline(cin, strg);
			pronadjen = pretraziPitanje(prvi, strg);
			if (!pronadjen) {
				cout << "Dato pitnaje ne postoji" << endl;
				break;
			}
			cout << "Menjate ocenu kog odgovora?" << endl;
			getline(cin, odg);
			promeniOcenu(pronadjen, odg);

			break;
		}

		case 6: { sortirajPoOcenama(prvi);
			break;
		}

		case 7: {
			ispisiPitanja(prvi);
			break;
		}

		case 8: {
			cout << "Unesite pitanje cije odgovori treba da budu ispisani" << endl;
			getchar();
			getline(cin, strg);
			pronadjen = pretraziPitanje(prvi, strg);
			if (!pronadjen) {
				cout << "Dato pitnaje ne postoji" << endl;
				break;
			}

			ispisiOdgovore(pronadjen);
			break;
		}

		case 9: {
			cout << "Unesite pitanje ciji neki odgovori treba da budu obrisani" << endl;
			getchar();
			getline(cin, strg);
			pronadjen = pretraziPitanje(prvi, strg);
			if (!pronadjen) {
				cout << "Dato pitnaje ne postoji" << endl;
				break;
			}
			cout << "Brisete thread kog odgovora?" << endl;
			getline(cin, odg);
			pronadjenOdgovor = pretraziOgovor(pronadjen, odg);
			if (!pronadjenOdgovor)
				cout << "Dati odgovor ne postoji" << endl;
			
			obrisiPosle(pronadjen, odg);
			
			break;
		}

		case 10: {
			cout << "Unesite pitanje koje treba biti obrisano" << endl;
			getchar();
			getline(cin, strg);
			pronadjen = pretraziPitanje(prvi, strg);
			if (!pronadjen) {
				cout << "Dato pitnaje ne postoji" << endl;
				break;
			}
			obrisiIzListe(prvi, pronadjen);
			brisanje(pronadjen);
			break;

		}

		case 11: {
			pronadjen = pitanjeSaMaxOdg(prvi);
			if (!pronadjen) {
				cout << "Nema pitanja" << endl;
				break;
			}
			cout << "Pitanje sa najvise odgovora je ->> " << pronadjen->tekst << " <<-" << endl;
			break;
		}

		default:
			cout << "Izaberite validnu opciju" << endl;
		}


	}

}