#pragma once
#include <utility>
#include "Ders.h"
class Fonksiyonlar
{
	void heapSirala(int eSay); //heapsort i�in ana fonksiyon
	void heapify(int kok, int eSay); // heapify �zelli�ini sa�latan fonksiyon
	void degistir(int i, int j); // heapsort i�in
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
	/*A�A�IDAK� FONKS�YONLAR MEN�DEK� ��LEVSEL ��LEMLER ���ND�R*/
	void klavyedenEkle(string secim);
	void Yazdir(string ders);
	void klavyedenBul(string ders);
	void klavyedenSil(string ders);
	Fonksiyonlar();
	~Fonksiyonlar();
};

