#include "stdafx.h"
#include "Ogrenci.h"

Ogrenci::Ogrenci(){}
/*AÇIKLAMA:Öðrenci nesnesi oluþtururken, öðrenci bilgilerini alýp öðrenciye atan Constructor Method*/
Ogrenci::Ogrenci(string adi, string soyadi, int no, int sinifi, string yandali)
{
	ad = adi;
	soyad = soyadi;
	ogrNo = no;
	sinif = sinifi;
	bolum = bolumTespit(no);
	yandal = yandali;
}


Ogrenci::~Ogrenci()
{
}

/*AÇIKLAMA:Ogrencinin bilgilerini ekrana yazdýran fonksiyon*/
void Ogrenci::OgrenciYaz() 
{
	cout << "\nÖgrenci Bilgileri"<<endl;
	cout << "Adý: " << ad << endl;
	cout << "Soyadý: " << soyad << endl;
	cout << "Numarasý: " << ogrNo << endl;
	cout << "Bölümü: " << bolum << endl;
	cout << "Sýnýfý: " << sinif << endl;
	cout << "Yandal: " << yandal << endl <<endl;

}

/*AÇIKLAMA:6 haneli öðrenci numarasanýn en baþýndaki hanesini bulup döndüren fonksiyon, bölüm tespit etmek için kullanýlacak*/
int Ogrenci::numaraTespit(int no)
{
	int digit = (int)(no / pow(10, (6 - 1))) % 10;
	return digit;
}
/*AÇIKLAMA:Aldýðý öðrenci numarasýný, öðrenci oluþturulurken bölümünü tespit etmek için kullanýlan method. Numarasýnýn baþ hanesine göre öðrenciye bölüm atar*/
string Ogrenci::bolumTespit(int no)
{
	string b="";
	int digit = numaraTespit(no);// 6 haneli numaranýn en baþýndaki numara
	switch (digit)
	{
	case 1:
		b = "Çevre Mühendisligi";
		break;
	case 2:
		b = "Ýnþaat Mühendisligi ";
		break;
	case 3:
		b = "Elektrik Elektronik Mühendisligi";
		break;
	case 4:
		b = "Mekatronik Mühendisligi";
		break;
	case 5:
		b = "Bilgisayar Mühendisligi";
		break;
	case 6:
		b = "Endüstriyel Tasarým Mühendisligi";
		break;
	case 7:
		b = "Gýda Mühendisligi";
		break;
	case 8:
		b = "Makina Mühendisligi";
		break;
	case 9:
		b = "Tekstil Mühendisligi";
		break;
	default:
		b = "Bölüm Yok";
		break;
	}
	return b;
}