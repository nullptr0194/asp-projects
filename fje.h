#ifndef _fje_h_
#define _fje_h_
#include<iostream>
#include<string>
#include<vector>
#include<queue>

using namespace std;

struct Elem {
	int br;
	struct Elem* sledeci = nullptr;
	struct Node* korenPok = nullptr;
};

struct Node {
	string br;
	string tekst;
	vector <int> ocene;
	vector <Node*> pokazivaci;
};

int oslobodi(Elem* head);

Elem* dodajPitanje(string pit, Elem** pok, Elem* prv,  int& rb);

void ispisiPitanja(Elem* prvi);

void ispisiOdgovore(Node* pitanje);

Node* pretraziPitanjeiOdg(Elem* hed, string pitanje);

Node* pretraziPitanje(Elem* hed, string pitanje);

Node* pretraziOgovor(Node* pitanje, string odgovor);

void promeniOcenu(Node* pitanje, string odgovor);

void sortirajPoOcenama(Elem* pocetak);

void dodajOdgovor(Node** pitanje, string odg);

void obrisiPosle(Node* pit, string odg);

void brisanje(Node* pit);

void obrisiIzListe(Elem* head, Node* pit);

Node* pitanjeSaMaxOdg(Elem* hed);

Node* najviseOdgovora(Elem* head);

void ispisiMeni();

#endif // !_

