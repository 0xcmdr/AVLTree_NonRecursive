#include "stdafx.h"
#include "Menu.h"
string BAglari = "BZ108",BMimari= "BZ207";
Fonksiyonlar Fonks; //Fonksiyonlarý menüden kullanabilmek için nesne oluþturuldu.

Menu::Menu()
{
}


Menu::~Menu()
{
}

/* AÇIKLAMA :Aþaðýdaki parçalý fonksiyonlarýn hepsi menü geçiþleri içindir.Döngüler kullanýlarak kullanýcýdan çýkma isteði alýnana kadar program çalýþmasýný devam ettirilmesi saðlanmýþtýr.
*/

void Menu::menuListele()
{
	int dersSecim = 0;
	do {
		cout << "   ==>Lütfen Ýþlem Yapmak Ýstediginiz Dersin Numarasýný Giriniz..." << endl;
		cout << " --> (1) Bilgisayar Aglarý Dersi Ýçin" << endl;
		cout << " --> (2) Bilgisayar Mimarisi Dersi Ýçin" << endl;
		cout << " --> (3) ÇIKIÞ \n" << endl;
		cin >> dersSecim;
		temelMenu(dersSecim);
	} while (dersSecim != 3);
	
}
void Menu::temelMenu(int secim)
{
	Fonks.kontrol(); // listeleri kullanýma hazýrla
	if (secim == 1)
	{
		
		int Lsecim;//liste seçim
		do {
			
			cout << "******** BU MENÜ BÝLGÝSAYAR AGLARI DERSÝ(LÝSTE)'NÝN TEMEL ÖZELLÝKLERÝNÝ ÝÇERÝR ********" << endl;
			cout << " --> (1) Derse Ögrenci Ekle" << endl;
			cout << " --> (2) Derse Kayýtlý Bir Öðrenciyi Bul " << endl;
			cout << " --> (3) Dersten Bir Ögrenciyi Sil" << endl;
			cout << " --> (4) Sýnýf Listesini Yazdýr" << endl;
			cout << " --> (5) Ek Fonksiyonlar & Sýralamalar Ýçin" << endl;
			cout << " --> (6) Ýlk Orjinal Sýnýf Listesi" << endl;
			cout << " --> (0) Ders Seçim Menüsü Ýçin \n" << endl;
			cin >> Lsecim;
			switch (Lsecim)
			{
			case 1:
				Fonks.klavyedenEkle(BAglari);
				break;
			case 2:Fonks.klavyedenBul(BAglari);
				break;
			case 3:Fonks.klavyedenSil(BAglari);
				break;
			case 4:Fonks.Yazdir(BAglari);
				break;
			case 5:system("cls");//ekraný temizle
				ekMenu();
				break;
			case 6:Fonks.ListeOlustur(BAglari);
				Fonks.Yazdir(BAglari);
				break;
			case 0:system("cls");//ekraný temizle
				break;
			default:cout << "Böyle bir seçenek mevcut degil \n";
				break;
			}
		} while (Lsecim != 0);
		

	}
	else if (secim == 2)
	{
		int Lsecim;//liste seçim
		do {
			cout << "******** BU MENÜ BÝLGÝSAYAR MÝMARÝSÝ DERSÝ(AGAC)'NÝN TEMEL ÖZELLÝKLERÝNÝ ÝÇERÝR ********" << endl;
			cout << " --> (1) Derse Ögrenci Ekle" << endl;
			cout << " --> (2) Derse Kayýtlý Bir Öðrenciyi Bul" << endl;
			cout << " --> (3) Dersten Bir Ögrenciyi Sil" << endl;
			cout << " --> (4) Sýnýf Listesini Yazdýr" << endl;
			cout << " --> (5) Ek Fonksiyonlar & Sýralamalar Ýçin" << endl;
			cout << " --> (6) Ýlk Orjinal Sýnýf Listesi" << endl;
			cout << " --> (0) Ders Seçim Menüsü Ýçin \n" << endl;
			cin >> Lsecim;
			switch (Lsecim)
			{
			case 1:
				Fonks.klavyedenEkle(BMimari);
				break;
			case 2:Fonks.klavyedenBul(BMimari);
				break;
			case 3:Fonks.klavyedenSil(BMimari);
				break;
			case 4:Fonks.Yazdir(BMimari);
				break;
			case 5:system("cls");//ekraný temizle
				ekMenu();
				break;
			case 6:Fonks.ListeOlustur(BMimari);
				   Fonks.Yazdir(BMimari);
				break;
			case 0:system("cls");//ekraný temizle
				break;
			default:cout << "Böyle bir seçenek mevcut degil\n";
				break;
			}
		} while (Lsecim != 0);
	}
	else if(secim==3)
		cout << "****HOÞÇAKAL :)****\n"<<endl;
	else
		cout << "\n****Böyle bir seçenek Mevcut Deðil!****\n" << endl;
	
}

void Menu::ekMenu()
{
	int secim; //ek menü secimi
	do {
	cout << " --> (1) EK FONKSÝYONLAR ÝÇÝN " << endl;
	cout << " --> (2)  SIRALAMALAR ÝÇÝN " << endl;
	cout << " --> (0) BÝR ÜST MENÜ ÝÇÝN \n" << endl;
	cin >> secim;
	if (secim == 1)
	{
		int Fsecim;//fonksiyon seçimi
		do {

			cout << "******** BU MENÜ EK FONKSÝYONLARI ÝÇERÝR ********" << endl;
			cout << " --> (1) HER ÝKÝ DERSÝ DE Alttan Alan Ögrenciler" << endl;
			cout << " --> (2) Sadece BÝLGÝSAYAR AGLARI Dersini Alan Ögrenciler" << endl;
			cout << " --> (3) BÝLGÝSAYAR AGLARI Dersini A ve B Grubu Olarak Ayýr" << endl;
			cout << " --> (4) Derslerden Herhangi Birini Alan EEM Ögrencileri" << endl;
			cout << " --> (0) ÜST MENÜ ÝÇÝN \n" << endl;
			cin >> Fsecim;
			switch (Fsecim)
			{
			case 1:Fonks.AlttanAlanlar();
				break;
			case 2:Fonks.BAglariAlan();
				break;
			case 3:Fonks.BAglariParcala();
				break;
			case 4:Fonks.EEMOgrenciListe();
				break;
			case 0:system("cls"); // ekraný temizle
				break;
			default:cout << "Böyle bir seçenek mevcut degil";
				break;
			}
		} while (Fsecim!= 0);


	}
	else if (secim == 2)
	{
		int Ssecim;//SIRALAMA SEÇÝM
		do {
			cout << "******** BU MENÜ SINIF LÝSTELERÝNÝ SIRALAMAK ÝÇÝNDÝR ********" << endl;
			cout << " --> (1) KÜMELEME SIRALAMA Ýle ADLARINA Göre Sýrala" << endl;
			cout << " --> (2) Bilgisayar Aglarý Sýnýfýný, RADÝKS SIRALAMA Ýle SOYADLARINA Göre Sýrala" << endl;
			cout << " --> (3) Bilgisayar Mimarisi Sýnýfýný, Numaraya Göre SEÇMELÝ SIRALAMA" << endl;
			cout << " --> (0) ÜST MENÜ ÝÇÝN \n" << endl;
			cin >> Ssecim;
			switch (Ssecim)
			{
			case 1:Fonks.KumelemeAd(); //Kümeleme Sýralama Fonksiyonunu Çaðýr
				break;
			case 2:Fonks.RadiksSoyad(); //Radiks Sýralama Fonksiyonunu Çaðýr
				break;
			case 3:Fonks.secmeliyazdir();//Seçmeli Sýralama Fonksiyonunu Çaðýr
				break;
			case 0:system("cls");
				break;
			default:cout << "Böyle bir seçenek mevcut degil";
				break;
			}
		} while (Ssecim != 0);
	}
	else
		cout << "****Böyle bir seçenek Mevcut Deðil!****" << endl;
	} while (secim != 0);
}