#pragma once
#include "Node.h"
class Liste
{
public:
	Liste();
	~Liste();
	friend class Fonksiyonlar;
	bool BosMu();
	bool NodeEkle(int index, Ogrenci* o);
	Node* NodeBul(Ogrenci* o);
	Node* indextenNodeBul(int index);
	int NodeSil(Ogrenci* o);
	void ListeyiYazdir();

private:
	Node* head;
};

