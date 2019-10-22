#include "stdafx.h"
#include "Menu.h"
string BAglari = "BZ108",BMimari= "BZ207";
Fonksiyonlar Fonks; //Fonksiyonlar� men�den kullanabilmek i�in nesne olu�turuldu.

Menu::Menu()
{
}


Menu::~Menu()
{
}

/* A�IKLAMA :A�a��daki par�al� fonksiyonlar�n hepsi men� ge�i�leri i�indir.D�ng�ler kullan�larak kullan�c�dan ��kma iste�i al�nana kadar program �al��mas�n� devam ettirilmesi sa�lanm��t�r.
*/

void Menu::menuListele()
{
	int dersSecim = 0;
	do {
		cout << "   ==>L�tfen ��lem Yapmak �stediginiz Dersin Numaras�n� Giriniz..." << endl;
		cout << " --> (1) Bilgisayar Aglar� Dersi ��in" << endl;
		cout << " --> (2) Bilgisayar Mimarisi Dersi ��in" << endl;
		cout << " --> (3) �IKI� \n" << endl;
		cin >> dersSecim;
		temelMenu(dersSecim);
	} while (dersSecim != 3);
	
}
void Menu::temelMenu(int secim)
{
	Fonks.kontrol(); // listeleri kullan�ma haz�rla
	if (secim == 1)
	{
		
		int Lsecim;//liste se�im
		do {
			
			cout << "******** BU MEN� B�LG�SAYAR AGLARI DERS�(L�STE)'N�N TEMEL �ZELL�KLER�N� ��ER�R ********" << endl;
			cout << " --> (1) Derse �grenci Ekle" << endl;
			cout << " --> (2) Derse Kay�tl� Bir ��renciyi Bul " << endl;
			cout << " --> (3) Dersten Bir �grenciyi Sil" << endl;
			cout << " --> (4) S�n�f Listesini Yazd�r" << endl;
			cout << " --> (5) Ek Fonksiyonlar & S�ralamalar ��in" << endl;
			cout << " --> (6) �lk Orjinal S�n�f Listesi" << endl;
			cout << " --> (0) Ders Se�im Men�s� ��in \n" << endl;
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
			case 5:system("cls");//ekran� temizle
				ekMenu();
				break;
			case 6:Fonks.ListeOlustur(BAglari);
				Fonks.Yazdir(BAglari);
				break;
			case 0:system("cls");//ekran� temizle
				break;
			default:cout << "B�yle bir se�enek mevcut degil \n";
				break;
			}
		} while (Lsecim != 0);
		

	}
	else if (secim == 2)
	{
		int Lsecim;//liste se�im
		do {
			cout << "******** BU MEN� B�LG�SAYAR M�MAR�S� DERS�(AGAC)'N�N TEMEL �ZELL�KLER�N� ��ER�R ********" << endl;
			cout << " --> (1) Derse �grenci Ekle" << endl;
			cout << " --> (2) Derse Kay�tl� Bir ��renciyi Bul" << endl;
			cout << " --> (3) Dersten Bir �grenciyi Sil" << endl;
			cout << " --> (4) S�n�f Listesini Yazd�r" << endl;
			cout << " --> (5) Ek Fonksiyonlar & S�ralamalar ��in" << endl;
			cout << " --> (6) �lk Orjinal S�n�f Listesi" << endl;
			cout << " --> (0) Ders Se�im Men�s� ��in \n" << endl;
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
			case 5:system("cls");//ekran� temizle
				ekMenu();
				break;
			case 6:Fonks.ListeOlustur(BMimari);
				   Fonks.Yazdir(BMimari);
				break;
			case 0:system("cls");//ekran� temizle
				break;
			default:cout << "B�yle bir se�enek mevcut degil\n";
				break;
			}
		} while (Lsecim != 0);
	}
	else if(secim==3)
		cout << "****HO��AKAL :)****\n"<<endl;
	else
		cout << "\n****B�yle bir se�enek Mevcut De�il!****\n" << endl;
	
}

void Menu::ekMenu()
{
	int secim; //ek men� secimi
	do {
	cout << " --> (1) EK FONKS�YONLAR ���N " << endl;
	cout << " --> (2)  SIRALAMALAR ���N " << endl;
	cout << " --> (0) B�R �ST MEN� ���N \n" << endl;
	cin >> secim;
	if (secim == 1)
	{
		int Fsecim;//fonksiyon se�imi
		do {

			cout << "******** BU MEN� EK FONKS�YONLARI ��ER�R ********" << endl;
			cout << " --> (1) HER �K� DERS� DE Alttan Alan �grenciler" << endl;
			cout << " --> (2) Sadece B�LG�SAYAR AGLARI Dersini Alan �grenciler" << endl;
			cout << " --> (3) B�LG�SAYAR AGLARI Dersini A ve B Grubu Olarak Ay�r" << endl;
			cout << " --> (4) Derslerden Herhangi Birini Alan EEM �grencileri" << endl;
			cout << " --> (0) �ST MEN� ���N \n" << endl;
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
			case 0:system("cls"); // ekran� temizle
				break;
			default:cout << "B�yle bir se�enek mevcut degil";
				break;
			}
		} while (Fsecim!= 0);


	}
	else if (secim == 2)
	{
		int Ssecim;//SIRALAMA SE��M
		do {
			cout << "******** BU MEN� SINIF L�STELER�N� SIRALAMAK ���ND�R ********" << endl;
			cout << " --> (1) K�MELEME SIRALAMA �le ADLARINA G�re S�rala" << endl;
			cout << " --> (2) Bilgisayar Aglar� S�n�f�n�, RAD�KS SIRALAMA �le SOYADLARINA G�re S�rala" << endl;
			cout << " --> (3) Bilgisayar Mimarisi S�n�f�n�, Numaraya G�re SE�MEL� SIRALAMA" << endl;
			cout << " --> (0) �ST MEN� ���N \n" << endl;
			cin >> Ssecim;
			switch (Ssecim)
			{
			case 1:Fonks.KumelemeAd(); //K�meleme S�ralama Fonksiyonunu �a��r
				break;
			case 2:Fonks.RadiksSoyad(); //Radiks S�ralama Fonksiyonunu �a��r
				break;
			case 3:Fonks.secmeliyazdir();//Se�meli S�ralama Fonksiyonunu �a��r
				break;
			case 0:system("cls");
				break;
			default:cout << "B�yle bir se�enek mevcut degil";
				break;
			}
		} while (Ssecim != 0);
	}
	else
		cout << "****B�yle bir se�enek Mevcut De�il!****" << endl;
	} while (secim != 0);
}