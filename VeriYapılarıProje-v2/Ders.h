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
	int yil; // dersin kaçýncý sýnýfa ait olduðu
public:
	friend class Fonksiyonlar;
	Ders();
	Ders(string Adi,string kodu,int yil);
	~Ders();
	Liste* listeOlustur(vector<Ogrenci*> & ogr); //Listenin pointerini dönderiyoruz,liste yok olmasýn diye
	AVLAgaci* agacOlustur(vector<Ogrenci*> & ogr);
	vector<Ogrenci*> OgrenciAl(string dYolu);
};



