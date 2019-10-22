#include "stdafx.h"
#include "Ders.h"

Ders::Ders()
{

}
/*											---->AÇIKLAMA<----
	Sýnýf listelerini oluþturacaðýmýz derslerin, dersin adi, kodu ve dersin öðrenim yýlý deðiþkenleri nesneyi oluþtururken belirlemize saðlayan constructor method
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

/*											---->AÇIKLAMA<----
	Öðrencilerimizi iki ayrý metin belgesinde tutuyoruz. Bu metin belgesinden okuyup sýnýf listesi oluþturmamýz gerektiði için, burda dosya okuma yazma yapmamýz gerekiyor.Listenin boyutu bilinmediði için c++ daki dinamik dizi göreci gören vectorden bir öðrenci pointeri tutan vector oluþturuldu.Dosya okumak için gerek ifstream ve okunan stringi parçalamamýza yarayan stringstream sýnýflardan türetilen nesneler sayesinde metin belgemizdeki her bir satýrý ":" iþaretine göre parçalayýp diziye atadýk, bu dizinin her bir elemaný sýraýyla ögrencinin bilgilerini içermektedir.Bu bilgileri kullanarak öðrenci oluþturup vectorde sakladýk. Bu vektörü ise dönderip ListeOlustur ve AgacOlustur Methodu ile sinif listesini oluþturduk. Fonksiyonun aldýðý dosyayolu parametresi iki adet metin belgemiz olduðu için içinden istediðimizi oluþturmamýza olanak saðladý.
*/
vector<Ogrenci*> Ders::OgrenciAl(string dYolu) 
{
	vector<Ogrenci*> ogr; // öðrencilerin tutulacaðý vectoru oluþtur
	ifstream belge(dYolu, ios::in);// açýlacak metin belgesini belirle
	if (belge.is_open()) //belgeni açýk olmama durumunu kontrol et
	{
		string okunan;
		while (getline(belge, okunan)) //satýr satýr oku, okunana aktar
		{
			vector<string> parca; // parçalarý tutacak string
			string s; // parçalanan parçayý geçici olarak tutacak string
			stringstream sst(okunan);//stringstream e okunan satýrý yolla
			int iparca[2];//ogrencinin numarasý ve sýnýfý için integer deðer tutacak dizi
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
/*											---->AÇIKLAMA<----
Aðaç ve liste oluþumlarý farklý olduðu için, ikisini farklý methodlar üzerinde iþledik. Ýkiside yukarýdaki ogrencial methodunu kullanarak öðrencileri tutan vectoru alýp,aðaca veya listeye ekledi. Vectorun karþýlaþtýrýlmasýnda size_T kullanýldý.Fonksiyonlarýn biri Liste biride AVLAgaci döndermektedir.Bunu ileriki kýsýmlarda listelerimizi oluþturmak ve üzerinde oynama yapmak için kullanacaðýz...
*/
AVLAgaci* Ders::agacOlustur(vector<Ogrenci*> & ogr)
{
	size_t i; //vectorun size methoduyla, int karþýlaþtýrýlamadýðý için size_t kullanýldým
	AVLAgaci* agac = new AVLAgaci();
	for (i = 0; i < ogr.size(); i++) {
		agac->AVLEkle(ogr[i]);
	}
	return agac;
}

/*											---->AÇIKLAMA<----
Aðaç ve liste oluþumlarý farklý olduðu için, ikisini farklý methodlar üzerinde iþledik. Ýkiside yukarýdaki ogrencial methodunu kullanarak öðrencileri tutan vectoru alýp,aðaca veya listeye ekledi. Vectorun karþýlaþtýrýlmasýnda size_T kullanýldý.Fonksiyonlarýn biri Liste biride AVLAgaci döndermektedir.Bunu ileriki kýsýmlarda listelerimizi oluþturmak ve üzerinde oynama yapmak için kullanacaðýz...
*/
Liste* Ders::listeOlustur(vector<Ogrenci*> & ogr)
{
	size_t i; //vectorun size methoduyla, int karþýlaþtýrýlamadýðý için size_t kullanýldýk
	Liste* list = new Liste();
	for (i = 0; i < ogr.size(); i++) {
		list->NodeEkle(i, ogr[i]);
	}
	return list;
}
