#pragma once
#include "AVLAgaci.h"
#include "Liste.h"
#include <vector>
#include <fstream>
#include <sstream>
class Ders
{
	string dersAdi;
	string dersKodu;
	int yil; // dersin ka��nc� s�n�fa ait oldu�u
public:
	friend class Fonksiyonlar;
	Ders();
	Ders(string Adi,string kodu,int yil);
	~Ders();
	Liste* listeOlustur(vector<Ogrenci*> & ogr); //Listenin pointerini d�nderiyoruz,liste yok olmas�n diye
	AVLAgaci* agacOlustur(vector<Ogrenci*> & ogr);
	vector<Ogrenci*> OgrenciAl(string dYolu);
};



