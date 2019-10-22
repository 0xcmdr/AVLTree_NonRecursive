#pragma once
#include <utility>
#include "Ders.h"
class Fonksiyonlar
{
	void heapSirala(int eSay); //heapsort için ana fonksiyon
	void heapify(int kok, int eSay); // heapify özelliðini saðlatan fonksiyon
	void degistir(int i, int j); // heapsort için
public:

	void kontrol();
	void ListeOlustur(string kod);
	void AlttanAlanlar();
	Liste* BAglariAlan();
	void BAglariParcala();
	void EEMOgrenciListe();
	void agacGez(AVLNode* kok);
	void secmeliSirala(AVLNode* kok);
	void secmeliyazdir();
	void RadiksSoyad();
	void KumelemeAd();
	/*AÞAÐIDAKÝ FONKSÝYONLAR MENÜDEKÝ ÝÞLEVSEL ÝÞLEMLER ÝÇÝNDÝR*/
	void klavyedenEkle(string secim);
	void Yazdir(string ders);
	void klavyedenBul(string ders);
	void klavyedenSil(string ders);
	Fonksiyonlar();
	~Fonksiyonlar();
};

