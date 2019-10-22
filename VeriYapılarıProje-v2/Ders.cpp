#include "stdafx.h"
#include "Ders.h"

Ders::Ders()
{

}
/*											---->A�IKLAMA<----
	S�n�f listelerini olu�turaca��m�z derslerin, dersin adi, kodu ve dersin ��renim y�l� de�i�kenleri nesneyi olu�tururken belirlemize sa�layan constructor method
*/
Ders::Ders(string Adi, string kodu, int yili)
{
	dersAdi = Adi;
	dersKodu = kodu;
	yil = yili;
}

Ders::~Ders()
{
}

/*											---->A�IKLAMA<----
	��rencilerimizi iki ayr� metin belgesinde tutuyoruz. Bu metin belgesinden okuyup s�n�f listesi olu�turmam�z gerekti�i i�in, burda dosya okuma yazma yapmam�z gerekiyor.Listenin boyutu bilinmedi�i i�in c++ daki dinamik dizi g�reci g�ren vectorden bir ��renci pointeri tutan vector olu�turuldu.Dosya okumak i�in gerek ifstream ve okunan stringi par�alamam�za yarayan stringstream s�n�flardan t�retilen nesneler sayesinde metin belgemizdeki her bir sat�r� ":" i�aretine g�re par�alay�p diziye atad�k, bu dizinin her bir eleman� s�ra�yla �grencinin bilgilerini i�ermektedir.Bu bilgileri kullanarak ��renci olu�turup vectorde saklad�k. Bu vekt�r� ise d�nderip ListeOlustur ve AgacOlustur Methodu ile sinif listesini olu�turduk. Fonksiyonun ald��� dosyayolu parametresi iki adet metin belgemiz oldu�u i�in i�inden istedi�imizi olu�turmam�za olanak sa�lad�.
*/
vector<Ogrenci*> Ders::OgrenciAl(string dYolu) 
{
	vector<Ogrenci*> ogr; // ��rencilerin tutulaca�� vectoru olu�tur
	ifstream belge(dYolu, ios::in);// a��lacak metin belgesini belirle
	if (belge.is_open()) //belgeni a��k olmama durumunu kontrol et
	{
		string okunan;
		while (getline(belge, okunan)) //sat�r sat�r oku, okunana aktar
		{
			vector<string> parca; // par�alar� tutacak string
			string s; // par�alanan par�ay� ge�ici olarak tutacak string
			stringstream sst(okunan);//stringstream e okunan sat�r� yolla
			int iparca[2];//ogrencinin numaras� ve s�n�f� i�in integer de�er tutacak dizi
			while (getline(sst, s, ':')) {
				parca.push_back(s);
			}
			istringstream(parca[2]) >> iparca[0];
			istringstream(parca[3]) >> iparca[1];
			Ogrenci* o = new Ogrenci(parca[0], parca[1], iparca[0], iparca[1], parca[4]);
			ogr.push_back(o);
		}

	}
	else
		cout << "Ogrencilerin bulundugu dosya acilamadi!";
	
	return ogr;

}
/*											---->A�IKLAMA<----
A�a� ve liste olu�umlar� farkl� oldu�u i�in, ikisini farkl� methodlar �zerinde i�ledik. �kiside yukar�daki ogrencial methodunu kullanarak ��rencileri tutan vectoru al�p,a�aca veya listeye ekledi. Vectorun kar��la�t�r�lmas�nda size_T kullan�ld�.Fonksiyonlar�n biri Liste biride AVLAgaci d�ndermektedir.Bunu ileriki k�s�mlarda listelerimizi olu�turmak ve �zerinde oynama yapmak i�in kullanaca��z...
*/
AVLAgaci* Ders::agacOlustur(vector<Ogrenci*> & ogr)
{
	size_t i; //vectorun size methoduyla, int kar��la�t�r�lamad��� i�in size_t kullan�ld�m
	AVLAgaci* agac = new AVLAgaci();
	for (i = 0; i < ogr.size(); i++) {
		agac->AVLEkle(ogr[i]);
	}
	return agac;
}

/*											---->A�IKLAMA<----
A�a� ve liste olu�umlar� farkl� oldu�u i�in, ikisini farkl� methodlar �zerinde i�ledik. �kiside yukar�daki ogrencial methodunu kullanarak ��rencileri tutan vectoru al�p,a�aca veya listeye ekledi. Vectorun kar��la�t�r�lmas�nda size_T kullan�ld�.Fonksiyonlar�n biri Liste biride AVLAgaci d�ndermektedir.Bunu ileriki k�s�mlarda listelerimizi olu�turmak ve �zerinde oynama yapmak i�in kullanaca��z...
*/
Liste* Ders::listeOlustur(vector<Ogrenci*> & ogr)
{
	size_t i; //vectorun size methoduyla, int kar��la�t�r�lamad��� i�in size_t kullan�ld�k
	Liste* list = new Liste();
	for (i = 0; i < ogr.size(); i++) {
		list->NodeEkle(i, ogr[i]);
	}
	return list;
}
