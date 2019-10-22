#include "stdafx.h"
#include "Fonksiyonlar.h"
Ders BAg = Ders("Bilgisayar A�lar�", "BZ108", 1); //Dersi Olu�tur, 1.S�n�f Dersi
Ders BMim = Ders("Bilgisayar Mimarisi", "BZ207", 2);//Dersi Olu�tur, 2.S�n�f Dersi
Liste* liste = new Liste(); // Bilgisayar A�lar�n� Alan ��rencileri Tutacak Liste
AVLAgaci* agac = new AVLAgaci(); //BMimarisi Dersini alanlar� tutacak a�a�
Liste* eemliler = new Liste(); //eem alan ��rencileri tutacak
Liste* ikiders = new Liste(); //heapa�ac�n� tutacak


Fonksiyonlar::Fonksiyonlar()
{
}


Fonksiyonlar::~Fonksiyonlar()
{
}

/* A�IKLAMASI :Bu Fonksiyondan program i�inde gerekli yerlerde liste olu�turmam�z gerekti�i zaman, metin belgesinden okuyup ��rencileri �eken fonksiyon olan OgrencileriAl Fonksiyonunu kullanarak listemizi veya a�ac�m�z� olu�turuyoruz.
	BAg ve BMim Ders s�n�f�n�n nesneleri olup derslerimizi temsil ederken, liste ve agac kavramlar� ise uygulama i�inden genel olarak eri�ebilece�imiz ana liste ve a�ac�m�z� temsil etmektedir. Di�er Fonksiyonlar�n hepsi bu liste ve agac'� kullanarak kendi b�nyelerinde gerekli i�lemleri yapmaktad�r.*/
void Fonksiyonlar::ListeOlustur(string kod)
{
	if (kod == "BZ108")
		liste = BAg.listeOlustur(BAg.OgrenciAl("baglari.txt"));

	else
		agac = BMim.agacOlustur(BMim.OgrenciAl("bmimarisi.txt"));

}
/* A�IKLAMASI: Bu fonksiyonda 2.sorunun a ��kk�nda istenilen �zerine, Her iki derside alttan alan ��renciler listelenmi�tir.�lk olarak bu i�lem i�in foknsiyon i�inde ba��ms�z bir liste olu�turulmu�tur. Daha sora Bilgisayar A�lar� S�n�f Listesini ��eren liste'nin en ba��ndan ba�lanarak, her bir d���mdeki ��rencinin sinifi B.A�lar� dersinin ders y�l� olan 1.s�n�f ile kar��la�t�r�lm��t�r. E�er ��renci 1.s�n�ftan b�y�kse bu dersi alttan al�yor demektir, bundan sonra bu ��renci AVLAgacinda listesi tutulan Bilgisayar Mimarisi Dersinin listesinde aranm��t�r. E�er sonu� olumlu ise bu ��rencinin o derside alttan al�p almad��� ders yili ve ��rencinin s�n�f� k�yaslanarak kontrol edilmi�tir.E�er sonu� tekrar olumlu ��karsa bu ��renci Alttan Alanlar listesine eklenmi�tir. Bu i�lem liste sonuna kadar t�m ��rencilere uygulanacakt�r.En sonu�ta ortaya ��kan liste bo� de�ilse liste yazd�r�lacak,yoksa liste bo� mesaj� d�nderilecektir.*/
void Fonksiyonlar::AlttanAlanlar()
{
	Liste* altalan = new Liste();
	//ilk olarak olu�turulmam�� sinif listesi varsa olu�turuyoruz
	kontrol();
	// Daha sonra BAglarindaki ogrencinin sinifi > dersyilindan onu agacta ar�yoruz
	Node* geznode = liste->head; // listenin ba��ndan ba�la
	int i = 0; // listeye eklenme s�ras�
	while (geznode != NULL)
	{
		if (geznode->ogr->sinif > BAg.yil) // Ogrencinin sinifi dersin yilindan b�y�kse alttan al�yor demektir
			if (agac->AVLBul(geznode->ogr) != NULL)// e�er bu ��renci a�a�ta varsa
				if (geznode->ogr->sinif > BMim.yil) // BMimarisini alttan al�yorsa
				{
					altalan->NodeEkle(i, geznode->ogr);//listeye ekle
					i++;
				}
					
		geznode = geznode->sonraki;//listenin sonraki ��rencisine ge�
	}
	if (altalan->BosMu()) // liste bo��sa bilgilendir
		cout << "\t\t\t\t  ----------> �K� DERS�DE AYNI ANDA ALTTAN ALAN ��RENC� YOKTUR!<----------" << endl;
	else
	{
		cout << "\t\t\t\t  ----------> �K� DERS�DE AYNI ANDA ALTTAN ALANLAR  <----------" << endl;
		altalan->ListeyiYazdir();// yoksa listeyi yazd�r
	}
		


}

/* A�IKLAMASI: Bu Fonksiyon i�in �ncelikle yeni bir liste olu�turuyoruz. Bu listede bizim istedi�imiz ��rencileri tutaca��z.Bilgisayar A�lar� s�n�f listesinin tutuldu�u ana listemizin ilk d���m�nden ba�l�yoruz. Bu d���mdeki ��renciyi Bilgisayar Mimarisi Listesinin tutuldu�u a�a�ta ar�yoruz. E�er ��renci burada yoksa bu ��renciyi SADECE B�LG�SAYAR A�LARI ALAN ��renciler listemize ekliyoruz.Daha sonra listeyi yazd�r�yoruz */
Liste* Fonksiyonlar::BAglariAlan()
{
	Liste* bagAlan = new Liste();
	//ilk olarak olu�turulmam�� sinif listesi varsa olu�turuyoruz
	kontrol();
	// Daha sonra BAglarindaki ogrencinin sinifi > dersyilindan onu agacta ar�yoruz
	Node* geznode = liste->head; // listenin ba��ndan ba�la
	while (geznode != NULL)
	{
		if (agac->AVLBul(geznode->ogr) == NULL)// e�er bu ��renci a�a�ta yoksa
			bagAlan->NodeEkle(0, geznode->ogr);//listeye ekle
		geznode = geznode->sonraki;//listenin sonraki ��rencisine ge�
	}
	if (bagAlan->BosMu()) // liste bo��sa bilgilendir
		cout << "\t\t\t\t  ----------> SADECE B�LG�SAYAR A�LARI ALAN ��RENC� YOKTUR <----------" << endl;
	else
	{
		cout << "\t\t\t\t  ----------> (YALNIZCA) B�LG�SAYAR AGLARI DERS� ALANLAR  <----------" << endl;
		bagAlan->ListeyiYazdir();// yoksa listeyi yazd�r
	}

	return bagAlan;

}

/*A�IKLAMASI : Bu fonksiyonda Bilgisayar A�lar� listesini A ve B grubu olarak par�alamam�z isteniyor. A Grubunda Soyad� A-K aras�nda olanlar, B Grubunda ise soyad� L-Z aras�nda olanlar olacakt�r. 2 adet liste olu�turuyoruz birisi Agrup di�eri ise Bgrup olacak �ekilde.Bilgisayar A�lar� Dersininin S�n�f Listesini i�eren ana listenin ilk eleman�ndan ba�l�yoruz.Bu Eleman�n i�indeki ��rencinin soyad�n�n �LK HARF� A-K aras�nda ise A grubuna yoksa B grubuna ait listeye ekliyoruz. Bunu ana listenin t�m elemanlar� i�in uyguluyoruz ve en sonda iki ayr� listemizi yazd�r�yoruz.*/
void Fonksiyonlar::BAglariParcala()
{
	kontrol();
	//Gerekli listeleri olu�tur
	Liste Agrup, Bgrup = Liste();
	//listede gezmeye ba�la
	Node* gezNode = liste->head;
	int i=0, j=0; // eklerken tutlacak indisler
	while (gezNode != NULL)
	{
		//char ch = &(gezNode->ogr->soyad.at[0]); //Ogrencinin Soyad�n�n ilk harfini al
		string soyad = gezNode->ogr->soyad; // soyad karakterini al
		char ch = soyad.at(0); // soyad karakterini chara at
		if (ch >= 'A' && ch <= 'K') // e�er soyad� bu harfler aras�ndaysa a grubuna ekle
		{
			Agrup.NodeEkle(i, gezNode->ogr);
			i++;
		}
			
		else
		{
			Bgrup.NodeEkle(j, gezNode->ogr); // de�ilse B grubuna ekle
			j++;
		}
			

		gezNode = gezNode->sonraki;//sonraki d���me ge�
	}
	// A Grubunu yazdir
	if (Agrup.BosMu())
		cout << "A Grubunda �grenci Mevcut Degil";
	else
	{
		cout << "\t\t\t\t  ----------> B�LG�SAYAR AGLARI DERS� - A GRUBU  <----------" << endl;
		Agrup.ListeyiYazdir();
	}

	//B grubunu Yazdir
	if (Bgrup.BosMu())
		cout << "B Grubunda �grenci Mevcut Degil";
	else
	{
		cout << "\t\t\t\t ----------> B�LG�SAYAR AGLARI DERS� - B GRUBU  <----------" << endl;
		Bgrup.ListeyiYazdir();
	}

}

/*EEMOgrenciListe A�IKLAMA : Bilgisayar A�lar� ve Bilgisayar Mimarisi derslerinin en az birini alan ve elektronik m�hendisli�i b�l�m� ��rencisi olan ��rencileri listelemek istiyoruz.Bunun �ncelikle ana listemiz gibi ba�ka fonksiyonlardan eri�ilebilecek bir liste olu�turuyoruz.Eemliler adl� bu listeyi d��arda tutmam�z�n amac� bu listeye a�a�ta gezerken ihtiyac�m�z olmas�d�r.�ncelikle Bigisayar A�lar� Dersinin listesini tutan ana listenin en ba��ndaki ��renciyi al�yoruz, burda ��rencinin �ncelikle numaras�n�n ilk harfini tespit ediyoruz.Bu numara e�er 3 ile ba�l�yorsa veya Yandal� "Elektrik Elektronik M�hendisli�i" ise bu ��renciyi eemliler listesine ekliyoruz.Bunu liste bitene kadar tekrarl�yoruz.Ondan sonra Aga�ta gezme fonksiyonunu �a��r�p, eri�ebilirli�i a��k olan eemliler listemizde bu fonksiyon ile de�i�iklik yap�yoruz. En sonda ise bu listeyi yazd�r�yoruz.*/
void Fonksiyonlar::EEMOgrenciListe()
{
	kontrol(); // bo� liste olmas�na kar�� kontrol
	Node* geznode = liste->head;
	while (geznode != NULL)
	{
		//��renci numaras�n�n ilk numaras�n� al b�l�m belirlemek i�in
		int digit = geznode->ogr->numaraTespit(geznode->ogr->ogrNo);
		//e�er elektrik b�l�m� ��rencisiyse,agactan gelen listede varm� kontrol et
		if (digit == 3 || geznode->ogr->yandal == "Elektrik Elektronik M�hendisligi")
			eemliler->NodeEkle(0, geznode->ogr); // kriteri sa�l�yorsa listeye ekle
		geznode = geznode->sonraki; // sonraki d���me ge�
	}
	agacGez(agac->root);
	cout << "Bilgisayar A�lar� ve Bilgisayar Mimarisi derslerinin en az birini alan EEML�LER";
	eemliler->ListeyiYazdir();

}


/* A�IKLAMASI : AVLAgacinde i�k�k gezerek a�a� i�inde kontrol yapt�k. A�ac�n en soluna gidip ordaki ��rencinin numaras�n�n ilk harfininin 3 olup olmad���n� veya varsa ��rencinin yandal�n�n elektrik elektronik m�hendisli�i olup olmad���n� kontrol ediyor.E�er ��renci bu kriterleri sa�l�yorsa bu ��renciyi eemliler listesinde ar�yor.E�er bu ��renci eemliler listesinde mevcut DE��LSE ��renciyi eemliler listesine ekliyor.T�m a�a� boyunca i�k�k kural�nca bunu yaparak a�ac� taram�� oluyor.*/
void Fonksiyonlar::agacGez(AVLNode* kok)
{
	if (kok == NULL)
		return;
	agacGez(kok->sol); //en sola git
	int digit = kok->ogr->numaraTespit(kok->ogr->ogrNo); //b�l�m bilgisi i�in
	if (digit == 3 || kok->ogr->yandal == "Elektrik Elektronik M�hendisligi")//a�ac�n eleman� eemlimi
		if (eemliler->NodeBul(kok->ogr) == NULL) // e�er ��renci B.A�lar�nda yoksa
			eemliler->NodeEkle(0, kok->ogr); // ��renciyi ekle
	agacGez(kok->sag);
}

/* A�IKLAMASI: Bu fonksiyon yukar�da bahssetti�imiz liste olu�tur fonksiyonlar�n� kullanarak. E�er ANA L�STE ve A�ACIMIZ Bo� ise program y�r�t�lemeyece�inden, bunlar� kontrol edip, bo� ise dolduruyor.*/
void Fonksiyonlar::kontrol()
{
	// Men� aras� ge�i�lerde, Listelerin olu�turulmad��� durumlar i�in kontrol
	if (liste->BosMu())
		ListeOlustur("BZ108");
	if (agac->BosMu())
		ListeOlustur("BZ207");
}

/*A�IKLAMASI: A�ac�n bir eleman� al�n�r, a�a� ba�tan sona gezilir en soldaki eleman t�m a�a�la kar��la�t�r�l�r, en k���k bulunup listeye eklenir*/
void Fonksiyonlar::secmeliSirala(AVLNode* kok) // en son buraya d�n
{
	if (kok == NULL)
		return;
	secmeliSirala(kok->sol); //en sola git
	kok->ogr->OgrenciYaz();
	secmeliSirala(kok->sag);
}

/*Secmeli S�ralanan A�ac� Yazd�r�r*/
void Fonksiyonlar::secmeliyazdir()
{
	secmeliSirala(agac->root);
}
/* A�IKLAMASI : Radiks s�ralama kural� gere�i, ilk �nce bo� bir liste olu�turuyoruz bu listeye yukar�da daha �nceden yapm�� oldu�umuz Sadece Bilgisayar A�lar� Alanlar�n listesini at�yoruz.Onun haricinde birde elimizde s�ralad�ktan sonra koyaca��m�z bir bo� liste olu�turuyoruz.Dolu olan orjinal listemizin i�ine giriyoruz b�t�n ��rencileri tarayarak ��renciye ula�mam�z� sa�layacak ��renci bilgisini ve ��rencisini iki boyutlu bir dizi �iftinde tutuyoruz.Bu s�rada her ��rencinin soyad�n� eklemeden �nce, ka� karakterden olu�tu�unu bir sonraki ��renci ile kar��la�t�rarak maxBoy de�i�keninde tutuyoruz ki, bu bizim radikste gereken elemanlar�n niteliklerini e�itlememiz i�in kullanaca��m�z de�i�ken.Fonksiyonun devam�nda b�t�n soyadlar�n son harfini al�p,Soyad�n uzunlu�u maxBoy a e�it olana kadar son harfi s�rekli ekliyoruz.Bu �ekilde b�t�n soyadlar�n uzunluklar� e�itlenmi� oluyor. Bundan sonraki k�s�mda en son karakterden ba�layarak soyadlar� birer birer s�ral�yoruz taki maxBoy de�eri s�f�ra e�it olana kadar.�ncelikle t�m soyadlar�n son karakterini g�z �n�ne al�yoruz, hepsi ayn� boyutta oldu�u i�in sorun ��km�yor. Sonra i�inde A varm� diye bak�yoruz varsa o soyada sahip ��renciyi en ba�a al�yoruz ,Daha sonra B ye ge�iyoruz. Bu i�lem soyadlar�n hepsi ilk harfine g�re yerle�inceye kadar s�rekli devam edecek. Tuttu�umuz index de�erinin amac� ise, e�er A-Z aras� harflerden biri bulunursa bu yer de�i�imine sebep olacak buda indexi 1 art�racak, ve index de�eri t�m soyadlar�n toplam say�s�na(��renci say�s�na) e�it olunca, bu art�k o anki kontrol edilen karakter i�in s�ralanabilecek bir ihtimal kalmad��� anlam�na gelir ve  bir sonraki karakteri kar��la�t�rmaya ba�lan�r.En sonunda bu tutulan de�erler siralanmis listesine eklenir ve liste ekrana yazd�r�l�r.
Yada K�saca:��renci bilgilerinden soyada gidilir. Soyadlarda max boy bulunur. �lk ��rencinin soyad�ndan ba�lan�r max boy olup olmad��� kontrol edilir son elemana kadar. Max boy olmayanlar� max boy e�itlenir. �lk harfini max boy olana kadar ilk harfe tekrarlayarak. Hepsi max boy oldukan sonra her bir soyad�n son harfinden ba�lay�p A dan Z ye kontrol edip yaz�l�r bu i�lem soyad�n ilk harfine gelene kadar yap�l�r. Sonunda s�ralanm�� �ekilde yeni ��renci d���m�ne atan�r ve ekrana yazd�r�l�r.*/
void Fonksiyonlar::RadiksSoyad()
{
	Liste* orjinal = BAglariAlan();
	Liste* siralanmis = new Liste();
	//listedeki soyadlar� vectore ekle
	Node* gezNode = orjinal->head;
	vector<pair<Ogrenci*, string>> soyad; //vector i�inde, ��renci pointeri ve ��renciye ait soyad �ifti tutuldu
	int i = 0, maxBoy = 0;
	//bu k�s�mda ��rencinin pointer ve soyad�n� listeden vector �iftimize at�yoruz
	while (gezNode != NULL)
	{
		soyad.push_back({ gezNode->ogr,gezNode->ogr->soyad });//��rencinin pointeri ve soyad� vectore eklendi
		if (i != 0)
			if (soyad[i - 1].second.size() > soyad[i].second.size()) // soyadlar�n karakter uzunlu�u kontrol�
				maxBoy = soyad[i - 1].second.size(); // soyadlardan aras�ndan maximum karakter say�s�n� tuttuk
		i++;
		gezNode = gezNode->sonraki;
	}
	//BU KISIM SOYADLARI E��T UZUNLU�A GET�REB�LMEK ���N
	for (int j = 0; j < soyad.size(); j++) // Her soyad�n sonuna son karakterini ekliyoruz
	{
		while (soyad[j].second.size() != maxBoy)
		{
			soyad[j].second.push_back(soyad[j].second.back()); //soyad�n sonuna maxboy olana kadar son harfi ekle
		}
	}

	//BU KISIM SOYADLARA G�RE SIRALAMAK ���N
	for (int k = maxBoy - 1; k >= 0; k--) //soyad�n maxsimum karakteri kadar s�ralama yap�lacak,s�ralama sondan ba�layacak
	{
		char kontrol = 'A';//her bir eleman i�in A harfi varm� kontrol et
		int index = 0; //soyadlar�n her biri yerine yerle�ince bu de�er 1 artacak
		while (kontrol != 'Z')
		{
			for (int j = 0; j < soyad.size(); j++)//her bir soyad� al
			{
				if (soyad[j].second[k] == kontrol)// e�er soyadda kontrol harfi varsa
				{
					swap(soyad[j], soyad[index]);	//yerlerini de�i�tir
					index++;	//s�rayla ba�a eklemek i�in gerekli index
				}

			}
			if (index == soyad.size() - 1) // e�er elemanlar�n hepsi yerle�tiyse di�er harfe ge�
				break;
			kontrol++;//e�er hala yerle�meyen varsa bir sonraki harfe ge�

		}

	}

	//��MD� SIRALANMI� VECTORU L�STEYE ATIP YAZDIRALIM
	for (int p = 0; p<soyad.size(); p++)
	{
		siralanmis->NodeEkle(p, soyad[p].first); //siralanmis ��rencileri yeni listeye ekle
	}

	//Yeni Listeyi Yazd�r
	cout << "\t\t\t\t ------> RAD�KS SIRALANMI� L�STE (SOYADA G�RE) <------ " << endl;
	siralanmis->ListeyiYazdir();
}

//***** BU KISIMDAN �T�BAREN HEAPSORT BA�LIYOR *******

/* A�IKLAMASI : Bilgisayar A�lar� listesinde gezerek t�m ��rencileri avl a�ac�nda ara, e�er ��renci a�a�ta varsa ikidersi alan ��renci olur. Bunu ikiders listesine ekle.Bu iki ders listesi genel eri�ime sahip ��nk� heapsortun di�er fonksiyonlar�n�n rahat kullanmas�n� ama�lad�k.Bu k�s�mda sadece liste olu�turuluyor ve bu siralanmamis iki ders listesi heapSirala fonksiyonuna g�nderiliyor.S�raland�ktan sonra bu fonksiyon i�inde ikiders listesinin s�ralanm�� hali yazd�r�l�yor.Ek olarak bilgisayar a�lar� listesi gezilirken her bir ��renci eklenmesinde belirlenen index de�erimiz 1 art�r�l�yor, bu index heapsortta g�rev alacakt�r. */
void Fonksiyonlar::KumelemeAd()
{
	kontrol();//bo� liste kontrol�
			  //HER �K� DERS� DE ALAN ��RENC�LER� BUL, L�STEYE AT
	Node* geznode = liste->head; // listenin ba��ndan ba�la
	int index = 0; //iki derside alanlar�n listesindeki eleman say�s�
	while (geznode != NULL)
	{
		if (agac->AVLBul(geznode->ogr) != NULL)// e�er bu ��renci a�a�ta varsa
		{
			ikiders->NodeEkle(index, geznode->ogr);//listeye ekle
			index++;
		}
		geznode = geznode->sonraki;//listenin sonraki ��rencisine ge�
	}
	Liste* siralanmamis = ikiders;
	cout << "\t\t\t\t -----> SIRALANMAMI� L�STE <-----";
	siralanmamis->ListeyiYazdir();
	cout << "\t\t\t\t -----> HEAPSORT(ADA G�RE) SIRALANMI� L�STE <-----";
	heapSirala(index);
	ikiders->ListeyiYazdir();

}
/* A�IKLAMA: Heapify algoritmas�n�n kural�ndan dolay� listenin elemansay�s�/2-1, den ba�lay�p listemizi heapify ediyoruz.Ondan sonra s�rekli en b�y�k eleman� ba�a al�yoruz*/
void Fonksiyonlar::heapSirala(int eSay) {
	for (int i = eSay / 2 - 1; i >= 0; i--) {
		heapify(i, eSay);
	}
	for (int i = eSay - 1; i>0; i--) {
		degistir(0, i);   // En b�y�k eleman� en ba�a al
		heapify(0, i);   // Heapify �zelli�ini kontrol et
	}
}

/* A�IKLAMA : HeapSortta en b�y�k eleman�n en yukar�da olmas� gerekir.Heapify �zelli�i ile bunu sa�l�yoruz. Sol ve sa� tarafta MaxHeap de�erine sahip d���mden daha b�y�k ada sahip bir d���m varsa heapify �zelli�i bozulur. Bundan dolay� bu d���mlerin ��rencileri, de�i�tir fonksiyonuna yollanarak de�i�tirilir
*/
void Fonksiyonlar::heapify(int kok, int eSay) {
	int left = kok * 2 + 1;          // Sol �ocuk  -> n*2+1
	int right = kok * 2 + 2;         // Sa� �ocuk -> n*2+2
	int maxHeap = kok;           // K�k� en b�y�k kabul et

								 //A�ac�n heap A�ac� �zelli�i sa�lay�p sa�lamad���n� kontrol et
	maxHeap = left<eSay && ikiders->indextenNodeBul(left)->ogr->ad > ikiders->indextenNodeBul(maxHeap)->ogr->ad ? left : maxHeap;
	maxHeap = right<eSay && ikiders->indextenNodeBul(right)->ogr->ad  >ikiders->indextenNodeBul(maxHeap)->ogr->ad ? right : maxHeap;

	if (maxHeap != kok) {            // A�a� heap A�ac� �zelli�i sa�lam�yor demektir
		degistir(kok, maxHeap);       // Yerlerini de�i�tir
		heapify(maxHeap, eSay);  // heapify kontrol�
	}
}
/* A�IKLAMA : G�nderilen indexlerdeki d���mlerin i�indeki ��renci bilgileri de�i�tiriliyor. */
void Fonksiyonlar::degistir(int i, int j) {
	Ogrenci* gecici = ikiders->indextenNodeBul(i)->ogr;
	ikiders->indextenNodeBul(i)->ogr = ikiders->indextenNodeBul(j)->ogr;
	ikiders->indextenNodeBul(j)->ogr = gecici;
}


/*BURADAN SONRAK� KISIM MEN�DE KULLANILMAK �ZERE EKLEME, S�LME, BULMA G�B� ��LEMLER� ��ERMEKTED�R, BU FONKS�YONLAR ORJ�NAL L�STEY� ETK�LEMEZ RAM �ZER�NDEK� B�LG�DE DE����KL�K YAPAR*/

/* A�IKLAMA : Men�den �a��r�lmak �zere yaz�lm��, klavyeden listeye veya a�aca kullan�c�lardan bilgi al�narak ��renci eklemesi yap�lmas�n� sa�layan fonksiyon :*/
void Fonksiyonlar::klavyedenEkle(string secim)
{
	string ad, soyad, yandal;
	int no, sinif;
	cout << "\t\t -L�tfen ��rencinin Ad�n� Giriniz --> ";
	cin >> ad;
	cout << "\t\t -L�tfen ��rencinin Soyad�n� Giriniz --> ";
	cin >> soyad;
	cout << "\t\t -L�tfen ��rencinin Numaras�n� Giriniz (6 HANEL�) --> ";
	cin >> no;
	cout << "\t\t -L�tfen ��rencinin S�n�f�n� Giriniz --> ";
	cin >> sinif;
	cout << "\t\t -L�tfen ��rencinin Yandal� varsa Giriniz (Yoksa, Yok yaz�n�z...) --> ";
	cin >> yandal;
	Ogrenci* o = new Ogrenci(ad, soyad, no, sinif, yandal);
	if (secim == "BZ108")
		liste->NodeEkle(0, o);
	else
		agac->AVLEkle(o);
	
}
/* A�IKLAMA : Men�den �a��r�lmak �zere yaz�lm��, istenen listeyi al�p ekrana yazd�r�r. Fonksiyon tan�mlama sebebimi ana listelerin burada tutuluyor olmas� */
void Fonksiyonlar::Yazdir(string ders) {
	if (ders == "BZ108")
	{
		cout << "\t\t\t\t ------> B�LG�SAYAR A�LARI DERS� SINIF L�STES� <------ " << endl;
		liste->ListeyiYazdir();
	}
	else
	{
		cout << "\t\t\t\t ------>B�LG�SAYAR M�MAR�S� DERS� SINIF L�STES� <------ " << endl;
		agac->AVLYazdir(agac->root, 1);
	}
		
}
/*A�IKLAMA : Men�den kullan�c� ��renci silmeyi se�erse, bu se�enekle ��renci numaras� al�n�r ve ��renci listeden silinir */
void Fonksiyonlar::klavyedenSil(string ders)
{
	int no;
	bool kontrol;
	cout << "\t\t -L�tfen Silinecek ��rencinin Numaras�n� Giriniz (6 HANEL�) --> ";
	cin >> no;
	Ogrenci* o = new Ogrenci();
	o->ogrNo = no;
	if (ders == "BZ108")
		kontrol = (liste->NodeSil(o) != 0) ? true : false;
	else
		kontrol = agac->AVLSil(o);
	if (kontrol) 
	{
		cout << "\t\t\t ---> S�LME �SLEM� BASARILI!\n"<< endl;
		cout << "\t\t\--> S�L�NEN OGRENC� : "<<o->ogrNo << endl<<endl;
	}
	else
		cout << "\t\t\t ---> S�LME ��LEM� BA�ARISIZ:(\n"<<endl;

		
}
/* A�IKLAMA : Men�den �a��r�lan bu fonksiyon ile numaras� girilen bir ��renci istenen listede bulunabilir */
void Fonksiyonlar::klavyedenBul(string ders)
{
	int no;
	cout << "\t\t -L�tfen Bulunacak ��rencinin Numaras�n� Giriniz (6 HANEL�) --> ";
	cin >> no;
	Ogrenci* o=new Ogrenci();
	o->ogrNo = no;
	//Derse g�re ��renciyi bul ve ekrana yazd�r	
	if (ders == "BZ108")
		liste->NodeBul(o)->ogr->OgrenciYaz();
	else
		agac->AVLBul(o)->ogr->OgrenciYaz();

}