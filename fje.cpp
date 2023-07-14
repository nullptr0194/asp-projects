#include "fje.h"

int oslobodi(Elem* head)
{
	while (head) {

		brisanje(head->korenPok);
		Elem* stari = head;
		head = head->sledeci;
		delete stari;
	}
	return 0;
}

Elem* dodajPitanje(string pit, Elem** pok, Elem* prv, int& rb)
{


	Elem* el = new Elem();
	if (!(*pok)) {
		*pok = el;
	}
	else { 
		(*pok)->sledeci = el;
		(*pok) = (*pok)->sledeci;
	}
	(*pok)->br = rb;
	
	if (!rb) {
		prv = el;
	}
	
	Node* pitanje = new Node();
	(*pok)->korenPok = pitanje;
	pitanje->tekst = pit;
	pitanje->br = to_string(rb);

	rb++;

	return prv;
}

Node* pretraziPitanjeiOdg(Elem* hed, string pitanje)
{
	Elem* trenutni = hed;

	while (trenutni) {

		Node* sledeci = trenutni->korenPok;
		queue<Node*> red;
		red.push(sledeci);

		while (!red.empty()) {
			sledeci = red.front();
			red.pop();
			if (sledeci->tekst == pitanje) return sledeci;
			for (int i = 0; i < sledeci->pokazivaci.size(); i++) {
				red.push(sledeci->pokazivaci[i]);
			}
		}
		trenutni = trenutni->sledeci;
	}
	return nullptr;
}

Node* pretraziPitanje(Elem* hed, string pitanje)
{
	Elem* trenutni = hed;

	while (trenutni) {
		if (trenutni->korenPok->tekst == pitanje)
			return trenutni->korenPok;
		
		trenutni = trenutni->sledeci;

	}
	return nullptr;
}

Node* pretraziOgovor(Node* pitanje, string odgovor)
{
		Node* sledeci = pitanje;
		queue<Node*> red;
		red.push(sledeci);

		while (!red.empty()) {
			sledeci = red.front();
			red.pop();
			if (sledeci->tekst == odgovor) return sledeci;
			for (int i = 0; i < sledeci->pokazivaci.size(); i++) {
				red.push(sledeci->pokazivaci[i]);
			}
		}
	
	return nullptr;
}

void promeniOcenu(Node* pitanje, string odgovor) {

	Node* sledeci = pitanje;
	queue<Node*> red;
	red.push(sledeci);
	int novaOc, ind=0;
	
	while (!red.empty()) {
		sledeci = red.front();
		red.pop();
		for (int i = 0; i < sledeci->pokazivaci.size(); i++) {
			if (sledeci->pokazivaci[i]->tekst == odgovor) {
				cout << "Unesite novu ocenu" << endl;
				cin >> novaOc;
				sledeci->ocene[i] = novaOc;
				ind++;
				cout << "Ocena promenjena!" << endl;
			}

			red.push(sledeci->pokazivaci[i]);
		}

	}
	if(!ind)
		cout << "Odgovor ne postoji" << endl;
}

void sortirajPoOcenama(Elem* pocetak)
{
	Elem* trenutni = pocetak;

	while (trenutni) {

		Node* sledeci = trenutni->korenPok;
		queue<Node*> red;
		red.push(sledeci);

		while (!red.empty()) {
			sledeci = red.front();
			red.pop();
			for (int i = 0; i < sledeci->pokazivaci.size(); i++) {
				for (int j = i; j < sledeci->pokazivaci.size(); j++) {
					if (sledeci->ocene[i] < sledeci->ocene[j]) {
						Node* tmp = sledeci->pokazivaci[i];
						sledeci->pokazivaci[i] = sledeci->pokazivaci[j];
						sledeci->pokazivaci[j] = tmp;
						int oc = sledeci->ocene[i];
						sledeci->ocene[i] = sledeci->ocene[j];
						sledeci->ocene[j] = oc;
					}
				}
			}
			for (int i = 0; i < sledeci->pokazivaci.size(); i++) {
				red.push(sledeci->pokazivaci[i]);
			}
		}

		trenutni = trenutni->sledeci;
	}
}

void ispisiPitanja(Elem* prvi)
{
	int ind = 0;

	Elem* trenutni = prvi;
	while (trenutni) {
		if (trenutni->korenPok) {
			cout << trenutni->br << " -> " << trenutni->korenPok->tekst << endl;
			ind++;
		}
		trenutni = trenutni->sledeci;
	}
	if (!ind)
		cout << "Nema postavljenih pitanja" << endl;
}

void ispisiOdgovore(Node* pitanje)
{
	Node* trt = pitanje;
	int ind = 0;
	cout << trt->br << " -> " << trt->tekst<<endl;
	queue<Node*> redPok;
	redPok.push(trt);
	
	while (!redPok.empty()) {
		trt = redPok.front();
		redPok.pop();

		for (int i = 0; i < trt->pokazivaci.size(); i++) {
			cout <<trt->pokazivaci[i]->br << " -> " << trt->pokazivaci[i]->tekst << " ("<<trt->ocene[i]<< ");   ";
			redPok.push(trt->pokazivaci[i]);
			ind++;
			if(i == trt->pokazivaci.size()-1)
				cout << endl;
			}
		if (!ind)
			cout<< endl << "Ovo pitanje nema odgovora";
		
	}

}

void dodajOdgovor(Node** pitanje, string odg)
{
	if ((*pitanje)->pokazivaci.size() > 9)
		cout << "Uneli ste maksimalan broj odgovora na ovaj cvor" << endl;
	else if (!(*pitanje))
		cout << "Ne postoji zadato pitanje/odgovor" << endl;
	else {
		
		Node* noviOdg = new Node();

		Node* pitOdg = pretraziOgovor((*pitanje) , odg);
		if (!pitOdg) {
			noviOdg->tekst = odg;
			(*pitanje)->ocene.push_back(0);
			(*pitanje)->pokazivaci.push_back(noviOdg);
			(*pitanje)->pokazivaci[(*pitanje)->pokazivaci.size() - 1]->br = (*pitanje)->br + "." + to_string((*pitanje)->pokazivaci.size() - 1);
			
		}
		else {
			noviOdg->tekst = odg;
			pitOdg->ocene.push_back(0);
			pitOdg->pokazivaci.push_back(noviOdg);
			pitOdg->pokazivaci[pitOdg->pokazivaci.size() - 1]->br = pitOdg->br + "." + to_string(pitOdg->pokazivaci.size() - 1);
		}
	}
}

void obrisiPosle(Node* pit, string odg)
{
	Node* sledeci = pit;
		queue<Node*> red;
		red.push(sledeci);

		if (sledeci->tekst == odg) 
			brisanje(sledeci);
	
		while (!red.empty()) {
			sledeci = red.front();
			red.pop();
			for (int i = 0; i < sledeci->pokazivaci.size(); i++) {
				if (sledeci->pokazivaci[i]->tekst == odg) {

					brisanje(sledeci->pokazivaci[i]);
					sledeci->pokazivaci.erase(sledeci->pokazivaci.begin()+i);
					return;
				}
				red.push(sledeci->pokazivaci[i]);
			}
		}
}

void brisanje(Node* pit)
{
	if (!pit) {
		return;
	}
	Node* zaBris = pit;
	queue<Node*> redBris;
	redBris.push(zaBris);
	while (!redBris.empty()) {
		zaBris = redBris.front();
		redBris.pop();

		for (int j = 0; j < zaBris->pokazivaci.size(); j++) {
			redBris.push(zaBris->pokazivaci[j]);
		}
		delete zaBris;
	}
	cout << "uspesno obrisano!" << endl;
}

void obrisiIzListe(Elem* head, Node* pit)
{
	Elem* trenutni = head;
	while (trenutni) {
		if (trenutni->korenPok == pit) {
			trenutni->korenPok = nullptr;
			break;
		}
		trenutni = trenutni->sledeci;
	}
}

Node* pitanjeSaMaxOdg(Elem* hed)
{
	if (!hed) return nullptr;

	Elem* trenutni = hed, *maximalni = hed;
	int trenutnoMax = -1;

	while (trenutni) {
		int br = 0;
		Node* sledeci = trenutni->korenPok;
		queue<Node*> red;
		red.push(sledeci);

		while (!red.empty()) {
			sledeci = red.front();
			red.pop();
			br++;
			for (int i = 0; i < sledeci->pokazivaci.size(); i++) {
				red.push(sledeci->pokazivaci[i]);
			}
		}
		trenutni->br = br;
		if (trenutni->br > trenutnoMax) {
			trenutnoMax = br;
			maximalni = trenutni;
		}

		trenutni = trenutni->sledeci;
	}
	return maximalni->korenPok;
}

Node* najviseOdgovora(Elem* head)
{
	Elem* trenutni = head;

	while (trenutni) {

		Node* sledeci = trenutni->korenPok;
		queue<Node*> red;
		red.push(sledeci);

		while (!red.empty()) {
			sledeci = red.front();
			red.pop();
			for (int i = 0; i < sledeci->pokazivaci.size(); i++) {
				for (int j = i; j < sledeci->pokazivaci.size(); j++) {
					if (sledeci->ocene[i] < sledeci->ocene[j]) {
						Node* tmp = sledeci->pokazivaci[i];
						sledeci->pokazivaci[i] = sledeci->pokazivaci[j];
						sledeci->pokazivaci[j] = tmp;
						int oc = sledeci->ocene[i];
						sledeci->ocene[i] = sledeci->ocene[j];
						sledeci->ocene[j] = oc;
					}
				}
			}
			for (int i = 0; i < sledeci->pokazivaci.size(); i++) {
				red.push(sledeci->pokazivaci[i]);
			}
		}

		trenutni = trenutni->sledeci;
	}

	return nullptr;
}

void ispisiMeni()
{
	cout << "FORMA ZA POSTAVLJANJE PITANJA:" << endl;
	cout << "1 -> Postavi pitanje" << endl;
	cout << "2 -> Napisi odgovor" << endl;
	cout << "3 -> Pretrazi pitanje" << endl;
	cout << "4 -> Pretrazi odgovor" << endl;//lvl
	cout << "5 -> Promeni ocenu odgovora" << endl;
	cout << "6 -> Uredi odgovore prema oceni" << endl;//lvl
	cout << "7 -> Pregledaj sva pitanja" << endl;
	cout << "8 -> Pregledaj sve odgovore na neko pitanje" << endl;//lvl
	cout << "9 -> Obrisi komentare nekog pitanja" << endl;
	cout << "10-> Obrisi pitanje" << endl;//lvl
	cout << "11-> Pronadji pitanje sa najvise odgovora" << endl;//j==2
	cout << "0 -> Kraj programa" << endl;
}

