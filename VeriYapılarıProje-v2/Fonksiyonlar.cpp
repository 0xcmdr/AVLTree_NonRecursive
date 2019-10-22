#include "stdafx.h"
#include "Fonksiyonlar.h"
Ders BAg = Ders("Bilgisayar Aðlarý", "BZ108", 1); //Dersi Oluþtur, 1.Sýnýf Dersi
Ders BMim = Ders("Bilgisayar Mimarisi", "BZ207", 2);//Dersi Oluþtur, 2.Sýnýf Dersi
Liste* liste = new Liste(); // Bilgisayar Aðlarýný Alan öðrencileri Tutacak Liste
AVLAgaci* agac = new AVLAgaci(); //BMimarisi Dersini alanlarý tutacak aðaç
Liste* eemliler = new Liste(); //eem alan öðrencileri tutacak
Liste* ikiders = new Liste(); //heapaðacýný tutacak


Fonksiyonlar::Fonksiyonlar()
{
}


Fonksiyonlar::~Fonksiyonlar()
{
}

/* AÇIKLAMASI :Bu Fonksiyondan program içinde gerekli yerlerde liste oluþturmamýz gerektiði zaman, metin belgesinden okuyup öðrencileri çeken fonksiyon olan OgrencileriAl Fonksiyonunu kullanarak listemizi veya aðacýmýzý oluþturuyoruz.
	BAg ve BMim Ders sýnýfýnýn nesneleri olup derslerimizi temsil ederken, liste ve agac kavramlarý ise uygulama içinden genel olarak eriþebileceðimiz ana liste ve aðacýmýzý temsil etmektedir. Diðer Fonksiyonlarýn hepsi bu liste ve agac'ý kullanarak kendi bünyelerinde gerekli iþlemleri yapmaktadýr.*/
void Fonksiyonlar::ListeOlustur(string kod)
{
	if (kod == "BZ108")
		liste = BAg.listeOlustur(BAg.OgrenciAl("baglari.txt"));

	else
		agac = BMim.agacOlustur(BMim.OgrenciAl("bmimarisi.txt"));

}
/* AÇIKLAMASI: Bu fonksiyonda 2.sorunun a þýkkýnda istenilen üzerine, Her iki derside alttan alan öðrenciler listelenmiþtir.Ýlk olarak bu iþlem için foknsiyon içinde baðýmsýz bir liste oluþturulmuþtur. Daha sora Bilgisayar Aðlarý Sýnýf Listesini Ýçeren liste'nin en baþýndan baþlanarak, her bir düðümdeki öðrencinin sinifi B.Aðlarý dersinin ders yýlý olan 1.sýnýf ile karþýlaþtýrýlmýþtýr. Eðer öðrenci 1.sýnýftan büyükse bu dersi alttan alýyor demektir, bundan sonra bu öðrenci AVLAgacinda listesi tutulan Bilgisayar Mimarisi Dersinin listesinde aranmýþtýr. Eðer sonuç olumlu ise bu öðrencinin o derside alttan alýp almadýðý ders yili ve öðrencinin sýnýfý kýyaslanarak kontrol edilmiþtir.Eðer sonuç tekrar olumlu çýkarsa bu öðrenci Alttan Alanlar listesine eklenmiþtir. Bu iþlem liste sonuna kadar tüm öðrencilere uygulanacaktýr.En sonuçta ortaya çýkan liste boþ deðilse liste yazdýrýlacak,yoksa liste boþ mesajý dönderilecektir.*/
void Fonksiyonlar::AlttanAlanlar()
{
	Liste* altalan = new Liste();
	//ilk olarak oluþturulmamýþ sinif listesi varsa oluþturuyoruz
	kontrol();
	// Daha sonra BAglarindaki ogrencinin sinifi > dersyilindan onu agacta arýyoruz
	Node* geznode = liste->head; // listenin baþýndan baþla
	int i = 0; // listeye eklenme sýrasý
	while (geznode != NULL)
	{
		if (geznode->ogr->sinif > BAg.yil) // Ogrencinin sinifi dersin yilindan büyükse alttan alýyor demektir
			if (agac->AVLBul(geznode->ogr) != NULL)// eðer bu öðrenci aðaçta varsa
				if (geznode->ogr->sinif > BMim.yil) // BMimarisini alttan alýyorsa
				{
					altalan->NodeEkle(i, geznode->ogr);//listeye ekle
					i++;
				}
					
		geznode = geznode->sonraki;//listenin sonraki öðrencisine geç
	}
	if (altalan->BosMu()) // liste boþþsa bilgilendir
		cout << "\t\t\t\t  ----------> ÝKÝ DERSÝDE AYNI ANDA ALTTAN ALAN ÖÐRENCÝ YOKTUR!<----------" << endl;
	else
	{
		cout << "\t\t\t\t  ----------> ÝKÝ DERSÝDE AYNI ANDA ALTTAN ALANLAR  <----------" << endl;
		altalan->ListeyiYazdir();// yoksa listeyi yazdýr
	}
		


}

/* AÇIKLAMASI: Bu Fonksiyon için öncelikle yeni bir liste oluþturuyoruz. Bu listede bizim istediðimiz öðrencileri tutacaðýz.Bilgisayar Aðlarý sýnýf listesinin tutulduðu ana listemizin ilk düðümünden baþlýyoruz. Bu düðümdeki öðrenciyi Bilgisayar Mimarisi Listesinin tutulduðu aðaçta arýyoruz. Eðer öðrenci burada yoksa bu öðrenciyi SADECE BÝLGÝSAYAR AÐLARI ALAN Öðrenciler listemize ekliyoruz.Daha sonra listeyi yazdýrýyoruz */
Liste* Fonksiyonlar::BAglariAlan()
{
	Liste* bagAlan = new Liste();
	//ilk olarak oluþturulmamýþ sinif listesi varsa oluþturuyoruz
	kontrol();
	// Daha sonra BAglarindaki ogrencinin sinifi > dersyilindan onu agacta arýyoruz
	Node* geznode = liste->head; // listenin baþýndan baþla
	while (geznode != NULL)
	{
		if (agac->AVLBul(geznode->ogr) == NULL)// eðer bu öðrenci aðaçta yoksa
			bagAlan->NodeEkle(0, geznode->ogr);//listeye ekle
		geznode = geznode->sonraki;//listenin sonraki öðrencisine geç
	}
	if (bagAlan->BosMu()) // liste boþþsa bilgilendir
		cout << "\t\t\t\t  ----------> SADECE BÝLGÝSAYAR AÐLARI ALAN ÖÐRENCÝ YOKTUR <----------" << endl;
	else
	{
		cout << "\t\t\t\t  ----------> (YALNIZCA) BÝLGÝSAYAR AGLARI DERSÝ ALANLAR  <----------" << endl;
		bagAlan->ListeyiYazdir();// yoksa listeyi yazdýr
	}

	return bagAlan;

}

/*AÇIKLAMASI : Bu fonksiyonda Bilgisayar Aðlarý listesini A ve B grubu olarak parçalamamýz isteniyor. A Grubunda Soyadý A-K arasýnda olanlar, B Grubunda ise soyadý L-Z arasýnda olanlar olacaktýr. 2 adet liste oluþturuyoruz birisi Agrup diðeri ise Bgrup olacak þekilde.Bilgisayar Aðlarý Dersininin Sýnýf Listesini içeren ana listenin ilk elemanýndan baþlýyoruz.Bu Elemanýn içindeki öðrencinin soyadýnýn ÝLK HARFÝ A-K arasýnda ise A grubuna yoksa B grubuna ait listeye ekliyoruz. Bunu ana listenin tüm elemanlarý için uyguluyoruz ve en sonda iki ayrý listemizi yazdýrýyoruz.*/
void Fonksiyonlar::BAglariParcala()
{
	kontrol();
	//Gerekli listeleri oluþtur
	Liste Agrup, Bgrup = Liste();
	//listede gezmeye baþla
	Node* gezNode = liste->head;
	int i=0, j=0; // eklerken tutlacak indisler
	while (gezNode != NULL)
	{
		//char ch = &(gezNode->ogr->soyad.at[0]); //Ogrencinin Soyadýnýn ilk harfini al
		string soyad = gezNode->ogr->soyad; // soyad karakterini al
		char ch = soyad.at(0); // soyad karakterini chara at
		if (ch >= 'A' && ch <= 'K') // eðer soyadý bu harfler arasýndaysa a grubuna ekle
		{
			Agrup.NodeEkle(i, gezNode->ogr);
			i++;
		}
			
		else
		{
			Bgrup.NodeEkle(j, gezNode->ogr); // deðilse B grubuna ekle
			j++;
		}
			

		gezNode = gezNode->sonraki;//sonraki düðüme geç
	}
	// A Grubunu yazdir
	if (Agrup.BosMu())
		cout << "A Grubunda Ögrenci Mevcut Degil";
	else
	{
		cout << "\t\t\t\t  ----------> BÝLGÝSAYAR AGLARI DERSÝ - A GRUBU  <----------" << endl;
		Agrup.ListeyiYazdir();
	}

	//B grubunu Yazdir
	if (Bgrup.BosMu())
		cout << "B Grubunda Ögrenci Mevcut Degil";
	else
	{
		cout << "\t\t\t\t ----------> BÝLGÝSAYAR AGLARI DERSÝ - B GRUBU  <----------" << endl;
		Bgrup.ListeyiYazdir();
	}

}

/*EEMOgrenciListe AÇIKLAMA : Bilgisayar Aðlarý ve Bilgisayar Mimarisi derslerinin en az birini alan ve elektronik mühendisliði bölümü öðrencisi olan öðrencileri listelemek istiyoruz.Bunun öncelikle ana listemiz gibi baþka fonksiyonlardan eriþilebilecek bir liste oluþturuyoruz.Eemliler adlý bu listeyi dýþarda tutmamýzýn amacý bu listeye aðaçta gezerken ihtiyacýmýz olmasýdýr.Öncelikle Bigisayar Aðlarý Dersinin listesini tutan ana listenin en baþýndaki öðrenciyi alýyoruz, burda öðrencinin öncelikle numarasýnýn ilk harfini tespit ediyoruz.Bu numara eðer 3 ile baþlýyorsa veya Yandalý "Elektrik Elektronik Mühendisliði" ise bu öðrenciyi eemliler listesine ekliyoruz.Bunu liste bitene kadar tekrarlýyoruz.Ondan sonra Agaçta gezme fonksiyonunu çaðýrýp, eriþebilirliði açýk olan eemliler listemizde bu fonksiyon ile deðiþiklik yapýyoruz. En sonda ise bu listeyi yazdýrýyoruz.*/
void Fonksiyonlar::EEMOgrenciListe()
{
	kontrol(); // boþ liste olmasýna karþý kontrol
	Node* geznode = liste->head;
	while (geznode != NULL)
	{
		//öðrenci numarasýnýn ilk numarasýný al bölüm belirlemek için
		int digit = geznode->ogr->numaraTespit(geznode->ogr->ogrNo);
		//eðer elektrik bölümü öðrencisiyse,agactan gelen listede varmý kontrol et
		if (digit == 3 || geznode->ogr->yandal == "Elektrik Elektronik Mühendisligi")
			eemliler->NodeEkle(0, geznode->ogr); // kriteri saðlýyorsa listeye ekle
		geznode = geznode->sonraki; // sonraki düðüme geç
	}
	agacGez(agac->root);
	cout << "Bilgisayar Aðlarý ve Bilgisayar Mimarisi derslerinin en az birini alan EEMLÝLER";
	eemliler->ListeyiYazdir();

}


/* AÇIKLAMASI : AVLAgacinde içkök gezerek aðaç içinde kontrol yaptýk. Aðacýn en soluna gidip ordaki öðrencinin numarasýnýn ilk harfininin 3 olup olmadýðýný veya varsa öðrencinin yandalýnýn elektrik elektronik mühendisliði olup olmadýðýný kontrol ediyor.Eðer öðrenci bu kriterleri saðlýyorsa bu öðrenciyi eemliler listesinde arýyor.Eðer bu öðrenci eemliler listesinde mevcut DEÐÝLSE öðrenciyi eemliler listesine ekliyor.Tüm aðaç boyunca içkök kuralýnca bunu yaparak aðacý taramýþ oluyor.*/
void Fonksiyonlar::agacGez(AVLNode* kok)
{
	if (kok == NULL)
		return;
	agacGez(kok->sol); //en sola git
	int digit = kok->ogr->numaraTespit(kok->ogr->ogrNo); //bölüm bilgisi için
	if (digit == 3 || kok->ogr->yandal == "Elektrik Elektronik Mühendisligi")//aðacýn elemaný eemlimi
		if (eemliler->NodeBul(kok->ogr) == NULL) // eðer öðrenci B.Aðlarýnda yoksa
			eemliler->NodeEkle(0, kok->ogr); // öðrenciyi ekle
	agacGez(kok->sag);
}

/* AÇIKLAMASI: Bu fonksiyon yukarýda bahssettiðimiz liste oluþtur fonksiyonlarýný kullanarak. Eðer ANA LÝSTE ve AÐACIMIZ Boþ ise program yürütülemeyeceðinden, bunlarý kontrol edip, boþ ise dolduruyor.*/
void Fonksiyonlar::kontrol()
{
	// Menü arasý geçiþlerde, Listelerin oluþturulmadýðý durumlar için kontrol
	if (liste->BosMu())
		ListeOlustur("BZ108");
	if (agac->BosMu())
		ListeOlustur("BZ207");
}

/*AÇIKLAMASI: Aðacýn bir elemaný alýnýr, aðaç baþtan sona gezilir en soldaki eleman tüm aðaçla karþýlaþtýrýlýr, en küçük bulunup listeye eklenir*/
void Fonksiyonlar::secmeliSirala(AVLNode* kok) // en son buraya dön
{
	if (kok == NULL)
		return;
	secmeliSirala(kok->sol); //en sola git
	kok->ogr->OgrenciYaz();
	secmeliSirala(kok->sag);
}

/*Secmeli Sýralanan Aðacý Yazdýrýr*/
void Fonksiyonlar::secmeliyazdir()
{
	secmeliSirala(agac->root);
}
/* AÇIKLAMASI : Radiks sýralama kuralý gereði, ilk önce boþ bir liste oluþturuyoruz bu listeye yukarýda daha önceden yapmýþ olduðumuz Sadece Bilgisayar Aðlarý Alanlarýn listesini atýyoruz.Onun haricinde birde elimizde sýraladýktan sonra koyacaðýmýz bir boþ liste oluþturuyoruz.Dolu olan orjinal listemizin içine giriyoruz bütün öðrencileri tarayarak öðrenciye ulaþmamýzý saðlayacak öðrenci bilgisini ve öðrencisini iki boyutlu bir dizi çiftinde tutuyoruz.Bu sýrada her öðrencinin soyadýný eklemeden önce, kaç karakterden oluþtuðunu bir sonraki öðrenci ile karþýlaþtýrarak maxBoy deðiþkeninde tutuyoruz ki, bu bizim radikste gereken elemanlarýn niteliklerini eþitlememiz için kullanacaðýmýz deðiþken.Fonksiyonun devamýnda bütün soyadlarýn son harfini alýp,Soyadýn uzunluðu maxBoy a eþit olana kadar son harfi sürekli ekliyoruz.Bu þekilde bütün soyadlarýn uzunluklarý eþitlenmiþ oluyor. Bundan sonraki kýsýmda en son karakterden baþlayarak soyadlarý birer birer sýralýyoruz taki maxBoy deðeri sýfýra eþit olana kadar.Öncelikle tüm soyadlarýn son karakterini göz önüne alýyoruz, hepsi ayný boyutta olduðu için sorun çýkmýyor. Sonra içinde A varmý diye bakýyoruz varsa o soyada sahip öðrenciyi en baþa alýyoruz ,Daha sonra B ye geçiyoruz. Bu iþlem soyadlarýn hepsi ilk harfine göre yerleþinceye kadar sürekli devam edecek. Tuttuðumuz index deðerinin amacý ise, eðer A-Z arasý harflerden biri bulunursa bu yer deðiþimine sebep olacak buda indexi 1 artýracak, ve index deðeri tüm soyadlarýn toplam sayýsýna(öðrenci sayýsýna) eþit olunca, bu artýk o anki kontrol edilen karakter için sýralanabilecek bir ihtimal kalmadýðý anlamýna gelir ve  bir sonraki karakteri karþýlaþtýrmaya baþlanýr.En sonunda bu tutulan deðerler siralanmis listesine eklenir ve liste ekrana yazdýrýlýr.
Yada Kýsaca:Öðrenci bilgilerinden soyada gidilir. Soyadlarda max boy bulunur. Ýlk öðrencinin soyadýndan baþlanýr max boy olup olmadýðý kontrol edilir son elemana kadar. Max boy olmayanlarý max boy eþitlenir. Ýlk harfini max boy olana kadar ilk harfe tekrarlayarak. Hepsi max boy oldukan sonra her bir soyadýn son harfinden baþlayýp A dan Z ye kontrol edip yazýlýr bu iþlem soyadýn ilk harfine gelene kadar yapýlýr. Sonunda sýralanmýþ þekilde yeni öðrenci düðümüne atanýr ve ekrana yazdýrýlýr.*/
void Fonksiyonlar::RadiksSoyad()
{
	Liste* orjinal = BAglariAlan();
	Liste* siralanmis = new Liste();
	//listedeki soyadlarý vectore ekle
	Node* gezNode = orjinal->head;
	vector<pair<Ogrenci*, string>> soyad; //vector içinde, öðrenci pointeri ve öðrenciye ait soyad çifti tutuldu
	int i = 0, maxBoy = 0;
	//bu kýsýmda öðrencinin pointer ve soyadýný listeden vector çiftimize atýyoruz
	while (gezNode != NULL)
	{
		soyad.push_back({ gezNode->ogr,gezNode->ogr->soyad });//öðrencinin pointeri ve soyadý vectore eklendi
		if (i != 0)
			if (soyad[i - 1].second.size() > soyad[i].second.size()) // soyadlarýn karakter uzunluðu kontrolü
				maxBoy = soyad[i - 1].second.size(); // soyadlardan arasýndan maximum karakter sayýsýný tuttuk
		i++;
		gezNode = gezNode->sonraki;
	}
	//BU KISIM SOYADLARI EÞÝT UZUNLUÐA GETÝREBÝLMEK ÝÇÝN
	for (int j = 0; j < soyad.size(); j++) // Her soyadýn sonuna son karakterini ekliyoruz
	{
		while (soyad[j].second.size() != maxBoy)
		{
			soyad[j].second.push_back(soyad[j].second.back()); //soyadýn sonuna maxboy olana kadar son harfi ekle
		}
	}

	//BU KISIM SOYADLARA GÖRE SIRALAMAK ÝÇÝN
	for (int k = maxBoy - 1; k >= 0; k--) //soyadýn maxsimum karakteri kadar sýralama yapýlacak,sýralama sondan baþlayacak
	{
		char kontrol = 'A';//her bir eleman için A harfi varmý kontrol et
		int index = 0; //soyadlarýn her biri yerine yerleþince bu deðer 1 artacak
		while (kontrol != 'Z')
		{
			for (int j = 0; j < soyad.size(); j++)//her bir soyadý al
			{
				if (soyad[j].second[k] == kontrol)// eðer soyadda kontrol harfi varsa
				{
					swap(soyad[j], soyad[index]);	//yerlerini deðiþtir
					index++;	//sýrayla baþa eklemek için gerekli index
				}

			}
			if (index == soyad.size() - 1) // eðer elemanlarýn hepsi yerleþtiyse diðer harfe geç
				break;
			kontrol++;//eðer hala yerleþmeyen varsa bir sonraki harfe geç

		}

	}

	//ÞÝMDÝ SIRALANMIÞ VECTORU LÝSTEYE ATIP YAZDIRALIM
	for (int p = 0; p<soyad.size(); p++)
	{
		siralanmis->NodeEkle(p, soyad[p].first); //siralanmis öðrencileri yeni listeye ekle
	}

	//Yeni Listeyi Yazdýr
	cout << "\t\t\t\t ------> RADÝKS SIRALANMIÞ LÝSTE (SOYADA GÖRE) <------ " << endl;
	siralanmis->ListeyiYazdir();
}

//***** BU KISIMDAN ÝTÝBAREN HEAPSORT BAÞLIYOR *******

/* AÇIKLAMASI : Bilgisayar Aðlarý listesinde gezerek tüm öðrencileri avl aðacýnda ara, eðer öðrenci aðaçta varsa ikidersi alan öðrenci olur. Bunu ikiders listesine ekle.Bu iki ders listesi genel eriþime sahip çünkü heapsortun diðer fonksiyonlarýnýn rahat kullanmasýný amaçladýk.Bu kýsýmda sadece liste oluþturuluyor ve bu siralanmamis iki ders listesi heapSirala fonksiyonuna gönderiliyor.Sýralandýktan sonra bu fonksiyon içinde ikiders listesinin sýralanmýþ hali yazdýrýlýyor.Ek olarak bilgisayar aðlarý listesi gezilirken her bir öðrenci eklenmesinde belirlenen index deðerimiz 1 artýrýlýyor, bu index heapsortta görev alacaktýr. */
void Fonksiyonlar::KumelemeAd()
{
	kontrol();//boþ liste kontrolü
			  //HER ÝKÝ DERSÝ DE ALAN ÖÐRENCÝLERÝ BUL, LÝSTEYE AT
	Node* geznode = liste->head; // listenin baþýndan baþla
	int index = 0; //iki derside alanlarýn listesindeki eleman sayýsý
	while (geznode != NULL)
	{
		if (agac->AVLBul(geznode->ogr) != NULL)// eðer bu öðrenci aðaçta varsa
		{
			ikiders->NodeEkle(index, geznode->ogr);//listeye ekle
			index++;
		}
		geznode = geznode->sonraki;//listenin sonraki öðrencisine geç
	}
	Liste* siralanmamis = ikiders;
	cout << "\t\t\t\t -----> SIRALANMAMIÞ LÝSTE <-----";
	siralanmamis->ListeyiYazdir();
	cout << "\t\t\t\t -----> HEAPSORT(ADA GÖRE) SIRALANMIÞ LÝSTE <-----";
	heapSirala(index);
	ikiders->ListeyiYazdir();

}
/* AÇIKLAMA: Heapify algoritmasýnýn kuralýndan dolayý listenin elemansayýsý/2-1, den baþlayýp listemizi heapify ediyoruz.Ondan sonra sürekli en büyük elemaný baþa alýyoruz*/
void Fonksiyonlar::heapSirala(int eSay) {
	for (int i = eSay / 2 - 1; i >= 0; i--) {
		heapify(i, eSay);
	}
	for (int i = eSay - 1; i>0; i--) {
		degistir(0, i);   // En büyük elemaný en baþa al
		heapify(0, i);   // Heapify özelliðini kontrol et
	}
}

/* AÇIKLAMA : HeapSortta en büyük elemanýn en yukarýda olmasý gerekir.Heapify özelliði ile bunu saðlýyoruz. Sol ve sað tarafta MaxHeap deðerine sahip düðümden daha büyük ada sahip bir düðüm varsa heapify özelliði bozulur. Bundan dolayý bu düðümlerin öðrencileri, deðiþtir fonksiyonuna yollanarak deðiþtirilir
*/
void Fonksiyonlar::heapify(int kok, int eSay) {
	int left = kok * 2 + 1;          // Sol Çocuk  -> n*2+1
	int right = kok * 2 + 2;         // Sað Çocuk -> n*2+2
	int maxHeap = kok;           // Kökü en büyük kabul et

								 //Aðacýn heap Aðacý özelliði saðlayýp saðlamadýðýný kontrol et
	maxHeap = left<eSay && ikiders->indextenNodeBul(left)->ogr->ad > ikiders->indextenNodeBul(maxHeap)->ogr->ad ? left : maxHeap;
	maxHeap = right<eSay && ikiders->indextenNodeBul(right)->ogr->ad  >ikiders->indextenNodeBul(maxHeap)->ogr->ad ? right : maxHeap;

	if (maxHeap != kok) {            // Aðaç heap Aðacý özelliði saðlamýyor demektir
		degistir(kok, maxHeap);       // Yerlerini deðiþtir
		heapify(maxHeap, eSay);  // heapify kontrolü
	}
}
/* AÇIKLAMA : Gönderilen indexlerdeki düðümlerin içindeki öðrenci bilgileri deðiþtiriliyor. */
void Fonksiyonlar::degistir(int i, int j) {
	Ogrenci* gecici = ikiders->indextenNodeBul(i)->ogr;
	ikiders->indextenNodeBul(i)->ogr = ikiders->indextenNodeBul(j)->ogr;
	ikiders->indextenNodeBul(j)->ogr = gecici;
}


/*BURADAN SONRAKÝ KISIM MENÜDE KULLANILMAK ÜZERE EKLEME, SÝLME, BULMA GÝBÝ ÝÞLEMLERÝ ÝÇERMEKTEDÝR, BU FONKSÝYONLAR ORJÝNAL LÝSTEYÝ ETKÝLEMEZ RAM ÜZERÝNDEKÝ BÝLGÝDE DEÐÝÞÝKLÝK YAPAR*/

/* AÇIKLAMA : Menüden çaðýrýlmak üzere yazýlmýþ, klavyeden listeye veya aðaca kullanýcýlardan bilgi alýnarak öðrenci eklemesi yapýlmasýný saðlayan fonksiyon :*/
void Fonksiyonlar::klavyedenEkle(string secim)
{
	string ad, soyad, yandal;
	int no, sinif;
	cout << "\t\t -Lütfen öðrencinin Adýný Giriniz --> ";
	cin >> ad;
	cout << "\t\t -Lütfen öðrencinin Soyadýný Giriniz --> ";
	cin >> soyad;
	cout << "\t\t -Lütfen öðrencinin Numarasýný Giriniz (6 HANELÝ) --> ";
	cin >> no;
	cout << "\t\t -Lütfen öðrencinin Sýnýfýný Giriniz --> ";
	cin >> sinif;
	cout << "\t\t -Lütfen öðrencinin Yandalý varsa Giriniz (Yoksa, Yok yazýnýz...) --> ";
	cin >> yandal;
	Ogrenci* o = new Ogrenci(ad, soyad, no, sinif, yandal);
	if (secim == "BZ108")
		liste->NodeEkle(0, o);
	else
		agac->AVLEkle(o);
	
}
/* AÇIKLAMA : Menüden çaðýrýlmak üzere yazýlmýþ, istenen listeyi alýp ekrana yazdýrýr. Fonksiyon tanýmlama sebebimi ana listelerin burada tutuluyor olmasý */
void Fonksiyonlar::Yazdir(string ders) {
	if (ders == "BZ108")
	{
		cout << "\t\t\t\t ------> BÝLGÝSAYAR AÐLARI DERSÝ SINIF LÝSTESÝ <------ " << endl;
		liste->ListeyiYazdir();
	}
	else
	{
		cout << "\t\t\t\t ------>BÝLGÝSAYAR MÝMARÝSÝ DERSÝ SINIF LÝSTESÝ <------ " << endl;
		agac->AVLYazdir(agac->root, 1);
	}
		
}
/*AÇIKLAMA : Menüden kullanýcý öðrenci silmeyi seçerse, bu seçenekle öðrenci numarasý alýnýr ve öðrenci listeden silinir */
void Fonksiyonlar::klavyedenSil(string ders)
{
	int no;
	bool kontrol;
	cout << "\t\t -Lütfen Silinecek öðrencinin Numarasýný Giriniz (6 HANELÝ) --> ";
	cin >> no;
	Ogrenci* o = new Ogrenci();
	o->ogrNo = no;
	if (ders == "BZ108")
		kontrol = (liste->NodeSil(o) != 0) ? true : false;
	else
		kontrol = agac->AVLSil(o);
	if (kontrol) 
	{
		cout << "\t\t\t ---> SÝLME ÝSLEMÝ BASARILI!\n"<< endl;
		cout << "\t\t\--> SÝLÝNEN OGRENCÝ : "<<o->ogrNo << endl<<endl;
	}
	else
		cout << "\t\t\t ---> SÝLME ÝÞLEMÝ BAÞARISIZ:(\n"<<endl;

		
}
/* AÇIKLAMA : Menüden çaðýrýlan bu fonksiyon ile numarasý girilen bir öðrenci istenen listede bulunabilir */
void Fonksiyonlar::klavyedenBul(string ders)
{
	int no;
	cout << "\t\t -Lütfen Bulunacak öðrencinin Numarasýný Giriniz (6 HANELÝ) --> ";
	cin >> no;
	Ogrenci* o=new Ogrenci();
	o->ogrNo = no;
	//Derse göre öðrenciyi bul ve ekrana yazdýr	
	if (ders == "BZ108")
		liste->NodeBul(o)->ogr->OgrenciYaz();
	else
		agac->AVLBul(o)->ogr->OgrenciYaz();

}