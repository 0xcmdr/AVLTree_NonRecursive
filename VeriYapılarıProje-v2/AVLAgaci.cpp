#include "stdafx.h"
#include "AVLAgaci.h"
/* AÇIKLAMA: GÝRÝLEN ÝKÝ ÝNTEGER DEÐERDEN EN BÜYÜK OLANI BULUP DÖNDEREN FONKSÝYON, AÞAÐIDAKÝ FONKSÝYONLARIMIZDA DESTEK OLARAK KULLANILMIÞTIR
*/
int AVLAgaci::max(int a, int b) {
	return (a < b) ? b : a;
}

/* AÇIKLAMA: En soldaki elemanýmýzý bulup dönderen methodtur*/
AVLNode* AVLAgaci::EnKucuk(AVLNode* dugum) // en soldaki elemaný bulur
 {
	 if (dugum != NULL)
		 while (dugum->sol != NULL)
			 dugum = dugum->sol;
	return dugum;
}

/* AÇIKLAMA: Aðaçta eleman yoksa kök=NULL ise true deðilse false dönderir*/
bool AVLAgaci::BosMu()
{
	return (root == NULL) ? true : false; // boþsa true yoksa false dönder
}

/* AÇIKLAMA: CONSTRUCTOR METHOD*/
AVLAgaci::AVLAgaci()
{
	root = NULL;
}

AVLAgaci::~AVLAgaci()
{
}

/* AÇIKLAMA: AVL Agacinda, parametre olarak verilen öðrenciyi, öðrencinin numarasýna göre arayan fonksiyondur.Her bir düðüme geldiðinde ögrenci numaralarýný karþýlaþtýrýr.Eðer numara düðümdekinden küçükse sola gider, büyükse saða gider.
 Düðümü bulana kadar veya gidebileceði düðüm kalmayana kadar bu iþlem devam eder.Bulursa düðümün pointerini, bulamazsa da NULL dönderir*/
AVLNode* AVLAgaci::AVLBul(Ogrenci* o)
{
	AVLNode* GeziciNode = root;
	if (root==NULL) 
		return root; //aðaç boþssa
	else //boþ deðilse
	{
		while (GeziciNode != NULL) // aðacý gezmek için gezicinode oluþturuldu
		{
			if (o->ogrNo == GeziciNode->ogr->ogrNo) // öðrenciyi bulursan döngüden çýk
				break;
			else if (o->ogrNo > GeziciNode->ogr->ogrNo)//girilen öðrenci no,düðümdekinden büyükse sað düðüme git
				GeziciNode = GeziciNode->sag;
			else if (o->ogrNo < GeziciNode->ogr->ogrNo)//girilen öðrenci no,düðümdekinden küçükse sol düðüme git
				GeziciNode = GeziciNode->sol;
		}
		
	}
	return GeziciNode;
}

/* AÇIKLAMA: Verilen öðrenciyi AVL aðacýna eklemizi saðlar.Mantýk AVLBul fonksiyonu ile nerdeyse aynýdýr.Ýndexleme öðrenci numarasýna göredir. Eðer aðaçta hiç eleman yoksa kök olarak en baþa öðrenciyi ekler. Eðer aðaçta eleman varsa, ilk düðüme gelir, düðümdeki ögrenci numarasýndan küçükse girilen öðrenci numarasý,sola gider. Büyükse saða gider.NULL yani boþ düðüm bulduðunda oraya yeni düðüm eklenir.Aðaçta saðda büyük elemanlar solda ise küçükler bulunur.AVL aðacý olduðu içinse aðacýn denge bozulma ihtimali vardýr.Bunun için düðüm eklendikten sonra, eklenen düðüm denge_kontrol fonksiyonuna gönderilir.Ekleme baþarýlý ise true döner...*/
bool AVLAgaci::AVLEkle(Ogrenci* o)
{
	AVLNode* YeniNode = new AVLNode(o);
	if (root == NULL) // aðaç boþsa baþa ekle
	{
		root = YeniNode;
		return true;
	}
		
	else // deðilse yerini bul
	{
		AVLNode* GeziciNode = root;
		while (GeziciNode!=NULL)
		{
			if (o->ogrNo > (GeziciNode->ogr->ogrNo))
			{
				if (GeziciNode->sag==NULL)//yeni dugum 'u yaprak olarak ekle
				{
					YeniNode->parent = GeziciNode;// her dugum ebeveyninin pointerini tutacak
					GeziciNode->sag = YeniNode;
					break;
				}
				else	
					GeziciNode = GeziciNode->sag;					
			}
			else 
			{
				if (GeziciNode->sol==NULL)//yeni dugum 'u yaprak olarak ekle
				{
					YeniNode->parent = GeziciNode;// her dugum ebeveyninin pointerini tutacak
					GeziciNode->sol = YeniNode;
					break;
				}
					
				else	
					GeziciNode = GeziciNode->sol;		
			}
				
		}
		
	
		denge_kontrol(YeniNode);
		return true;
	}
	return false;
}

/* AÇIKLAMA: BU FONKSÝYON ALDIÐI DÜÐÜMÜN SAÐ VE SOL ÇOCUKLARININ YÜKSEKLÝÐÝNÝ ALIP DÖNDERÝR. Mesela bir düðümüm sol yüksekliðine bakmak için dügüm->sol diye parametre yollarsak ve düðüm mevcut deðilse -1 dönderir eðer orda düðüm mevcut ise düðümün sahip olduðu yükseklik deðerini dönderir. Bu fonksiyon denge iþlemlerinde sýkça kullanýlacaktýr*/
int AVLAgaci::yuk_hesap(AVLNode* dugum) 
{
	if (dugum==NULL)
		return -1;
	else 
		return dugum->yukseklik;
}

/* AÇIKLAMA: 
AVL Aðacýmýzýn bel kemiði dediðimiz denge kontrol Fonksiyonun Ana giriþ fonksiyonu olan bu fonksiyon.AVL Aðacýný diðer aðaçlardan ayýran solcocuk-saðcocuk yuksekliði -1,0,1 deðerlerinden farklý olursa aðacýn dengesinin bozulmasýdýr.Bu dengeyi her ekleme ve silme yaptýðýmýzda her düðüm için bu üç deðerden birinin olmasýný saðlamalýyýz.

Bu Fonksiyonda öncelikle kontrol düðümümüz mevcut, bu düðüm dengeyi bozan düðüm olacaktýr ve bu düðümü rotasyon fonksiyonlarýna göndererek dengeyi oluþturacaðýz.Bu fonksiyona yolladýðýmýz düðüm deðeri, AÐACA EKLENEN DEÐER, AÐAÇTAN SÝLÝNEN DEÐERÝN PARENTÝ VEYA DÖNÜÞ YAPILAN KRÝTÝK DÜÐÜM olabilir. Yani deðiþiklik olan düðümden denge kontrolüne baþlýyoruz.

Gelen düðüm deðerinden baþlayýp, YUKARI doðru , düðümün sol yüksekliði ve sað yüksekliðinin maxsimumum deðerinin 1 fazlasýný alarak, o düðümün yuksekliðini hesaplýyoruz.

Denge Faktörü ise, bir düðümün sol ve sað düðümünün yükseklikleri farkýdýr.Bu deðer -1,0,1 den farklý deðer olursa kontrol düðümümüz denge faktörü bu deðerlerden farklý olan düðüme eþitlenir.Sorunlu düðüm tespit edildiði için döngüden çýkýlýr

Eðer kontrol düðümü tespit edildiyse, aðacýn rotasyon ile dengelenmesi gerekir bunun için AVLDengele fonksiyonunda gerekli rottasyon tespit edilip uygulanýr.*/
void AVLAgaci::denge_kontrol(AVLNode* dugum)
{
	AVLNode* kontrol=NULL; // sorunlu düðümü tutacak dugum
	AVLNode* sonraki = NULL;
	while(dugum!=NULL)
	{
	dugum->yukseklik = 1 + max(yuk_hesap(dugum->sol) , yuk_hesap(dugum->sag)); //o anki düðümün yükseklik hesabý
	dugum->denge_fak = (yuk_hesap(dugum->sol) - yuk_hesap(dugum->sag)); //o anki düðümün dengefaktörü hesabý
	if (dugum->denge_fak > 1 || dugum->denge_fak < -1)
	{
		kontrol = dugum; // hatalý düðümü tespit et
		break; // burada döngüden çýkmazsak, kontrol düðümü hatalý bulunabilir
	}
		
	
	dugum = dugum->parent; // denge faktörü bozulmadýkça yukarý doðru yükseklik ve denge faktörü hesabý devam eder
	}
	if (kontrol != NULL)
		AVLDengele(kontrol);
}

/* AÇIKLAMA: Bu fonksiyon yukarýda denge faktörü -1,0,1 den farklý olup sorunlu tespit edilen düðümdür. Þimdi denge faktörünün deðerine göre ve sol ve sað yüksekliklere göre rotasyonlar belirlenip uygulanacaktýr.Aþaðýda kodlarýn yanýnda açýklamasý yapýlmýþtýr.Sol-Sað yaptýðýmýz için dengefak > 1 sola baskýnlýk vardýr. dengefak <-1 ise sað tarafta baskýnlýk vardýr.Ayrýyeten dönüþler yapýldýktan sonra, dönüþe sebep olan dügüm, rotasyon fonksiyonlarýndan geri döner ve o dügümden yukarý doðru tekrar denge kontrolü yapýlýr.*/
void AVLAgaci::AVLDengele(AVLNode* dugum)
{
	if (dugum->denge_fak > 1) //Sol taraf uzun, saða tek dönüþ veya Sol sað dönüþ gerekir
		if (yuk_hesap(dugum->sol->sol) >= yuk_hesap(dugum->sol->sag)) // solun solun daha büyükse o yapýlýr
			denge_kontrol(SagaTekDonus(dugum));
			
		else //solun saðý büyükse burasý yapýlýr
			denge_kontrol(SolSagDonus(dugum));

	if (dugum->denge_fak < -1) // deðer negatif yani sað taraf daha uzun, sola tek dönüþ veya sað sol dönüþ gereklidir
		if (yuk_hesap(dugum->sag->sag) >= yuk_hesap(dugum->sag->sol)) // saðýn saðý uzunsa sola tek dönüþ
		denge_kontrol(SolaTekDonus(dugum));

		else//deðilse sapsol dönüþ yapýlýr
			denge_kontrol(SagSolDonus(dugum));

}

/* AÇIKLAMA: Bu Kýsým aþaðýdaki AVLSil fonksiyonundan, eðer düðüm tek çocuða sahipse veya hiç çocuðu yoksa burasýna yollanýr.Fonksiyonu ayýrma sebebim bulunan düðümün parentine ulaþmak istememdi.Bu fonksiyonda yollanan düðümde eðer tek çocuk varsa çocuðun tarafý tespit edilir, ondan sonra bu çocuðun atanýn sol koluna mý yoksa sað koluna mý baðlý olduðu tespit edilir..Çünkü düðümün tek çocuðu olunca çocuðu düðümün atasýna baðlamamýz gerekiyor.Kol tespit edildikten sonra çocuk ataya baðlanýr. Düðümlerin parentleri deðiþtirilir.Ýstenilen düðüm silinir. Eðer hiç cocuk yoksa, çocuða giden pointeri tespit edip NULL deðeri atamamýz gerekiyor, yoksa o kýsým hafýzadan silindiði için dengeleme fonksiyonunda sorun yaratýyor.Ondan sonra düðüm silinir.*/
bool AVLAgaci::AVLSilTek(AVLNode* bulunan) //tek çocuk veya hiç çocuk yoksa burasý çalýþýr
{
	AVLNode* ata = bulunan->parent;
	AVLNode* tespit = NULL;
	tespit = (bulunan->sag != NULL) ? bulunan->sag : bulunan->sol; // çocuðun tarafýný tespit et
	if (tespit != NULL) // eðer tek çocuðu varsa
	{
		 // çocuk atanýn hangi koluna baðlý
		if (ata->sag == bulunan)
			ata->sag = tespit; // çocuðu ataya baðla
			
		else if(ata->sol == bulunan) // çocuðu atanýn soluna baðla
			ata->sol = tespit; // çocuðu ataya baðla
			
		tespit->parent = ata; // parentini deðiþtir
	}

	//hiç çocuk yok ise
	else
	{
		(ata->sag == bulunan) ? ata->sag = NULL : ata->sol = NULL; //çocuða giden pointere null ata
	}
	delete bulunan;//bulunan nodu sil,
	denge_kontrol(ata);
	return true; // iþlem baþarýlý
}

/* AÇIKLAMA: Bu fonksiyon düðümün iki çocuðu varsa çalýþýr. Öncelikle silinecek düðüm bulunur. Ondan sonra silinecek düðümün saðýndaki ENKUCUK düðüm bulunur. Bu en küçük düðümün ogrencisi ile, silinecek düðümün ögrencisi deðiþtirilir.Ondan sonra Enkucuk olarak tespit ettiðimiz (yani alttaki düðüm) silme fonksiyonuna gönderilir. Çünkü tek çocuk veya hiç çocuk olmama ihtimali vardýr.Bu yüzden fonksiyonu iki ayýrdýk.*/
bool AVLAgaci::AVLSil(Ogrenci* o) 
{
	//öncelikle silinecek düðümü bul
	AVLNode* bulunan = AVLBul(o);
	
	if(bulunan != NULL) // silinecek düðüm mevcutsa
	{
		//iki çocuðu varsa
		if (bulunan->sag != NULL && bulunan->sol != NULL)
		{
			AVLNode* enkucuk = EnKucuk(bulunan->sag);
			bulunan->ogr = enkucuk->ogr;// bulunan ile en kucuk elemanýn deðerlerini yer deðiþtir
			return AVLSilTek(enkucuk);// 1. ve 2. durum var mý diye kontrol et
		}
		else // tek çocuk varsa veya hiç çocuðu yoksa
			return AVLSilTek(bulunan);
	}

	return false; // silinecek dugum bulunamadý
}


/* AÇIKLAMA: 
Denge fonksiyonun en önemli kýsmý dönüþ fonksiyonlarýdýr. Öncelikle sola dönüþ yapacaðýmýz için sagcocuk diye düðüm oluþturuyoruz ve düðümün saðýný atýyoruz. Dönüþten sonra SAÐ ÇOCUÐUN SOLUNA,DÜÐÜMÜN SAÐ KOLU baðlanacaðý için, Sað çocuðun sol deðerini geçici bir düðümde tutuyoruz. Daha sonra kök deðiþimlerini yapmamýz gerekir. 2 Durum mevcut, döndürülecek düðüm root sa veya deðilse, eðer döndürlecek düðüm aðacýn rootuna eþitse,root ve sað coçuk yer deðiþtirir.
Eðer döndürülecek eleman aðacýn kökü deðilse, ebeveyninin hangi koluna baðlý olduðunu tespit etmemiz gerekiyor.Çünkü döndürlecek düðüm, ebeveyninin hangi koluna baðlýysa, düðümün sagcocuðunu, ebeveyninin o koluna baðlayacaðýz.
Daha sonra dönüþü tamamlamak için sagcocuk soluna dugumu baðlarýz ve dugumun sað kolunada baþta tuttuðumuz geçici node u baðlarýz. Böylece Dönüþ tamamlanmýþ olur. Ek olarak aðaçta dengeyi saðlamamýzda lazým olan parentleri deðiþtirmeliyiz.Daha sonra dönen kýsmýn yüksekliklerini güncelleriz.Bu fonksiyondan dönen düðüm tekrardan denge kontrole gidecektir.*/
AVLNode* AVLAgaci::SolaTekDonus(AVLNode* dugum)
{
	AVLNode* sagcocuk = dugum->sag; // cocuðu tut
	AVLNode* gecici = sagcocuk->sol; // sol çocuðun taþýnacak çocuðunu tut
	//**Root Deðiþimi
	if (dugum->parent == NULL) // eðer root döndürülecekse burasý çalýþýr
		root = sagcocuk;
	else // döndürelecek eleman root deðilse
		if (dugum->parent->sag == dugum)//sag kola mý baðlý
			dugum->parent->sag = sagcocuk; 
		else // sol kola mý baðlý
			dugum->parent->sol = sagcocuk;
	sagcocuk->sol = dugum;
	dugum->sag = gecici;
	//**Parent deðiþimleri
	if (gecici != NULL)
		gecici->parent = dugum;
	sagcocuk->parent = dugum->parent;
	dugum->parent = sagcocuk;
	//**Yükseklikleri güncelle
	dugum->yukseklik = 1 + max(yuk_hesap(dugum->sol), yuk_hesap(dugum->sag));
	sagcocuk->yukseklik = 1 + max(yuk_hesap(sagcocuk->sol), yuk_hesap(sagcocuk->sag));
	return dugum;
}

/*  AÇIKLAMA:  Yukarida anlatýlan solatek dönüþün, tam tersidir.*/
AVLNode* AVLAgaci::SagaTekDonus(AVLNode* dugum)
{
	AVLNode* solcocuk = dugum->sol; // cocuðu tut
	AVLNode* gecici = solcocuk->sag; // sol çocuðun taþýnacak çocuðunu tut
									 //**Root Deðiþimi
	if (dugum->parent == NULL) // eðer root döndürülecekse burasý çalýþýr
		root = solcocuk;
	else // döndürelecek eleman root deðilse
		if (dugum->parent->sol == dugum) // sol kola mý baðlý
			dugum->parent->sol = solcocuk;
		else // sað kola mý baðlý
			dugum->parent->sag = solcocuk;

	solcocuk->sag = dugum;
	dugum->sol = gecici;
	//**Parent deðiþimleri 
	if (gecici != NULL)
		gecici->parent = dugum;
	solcocuk->parent = dugum->parent;
	dugum->parent = solcocuk;
	//**Yükseklikleri güncelle
	dugum->yukseklik = 1 + max(yuk_hesap(dugum->sol), yuk_hesap(dugum->sag));
	solcocuk->yukseklik = 1 + max(yuk_hesap(solcocuk->sol), yuk_hesap(solcocuk->sag));
	return dugum;
}

/* AÇIKLAMA: 
Burda ise sorunlu düðümün önce solundaki düðüme sola tek dönüþ uygulanýr, daha sonra düðümüm kendisine saða tek dönüþ uygulanýr.
*/
AVLNode* AVLAgaci::SolSagDonus(AVLNode* dugum)
{
	SolaTekDonus(dugum->sol);
	return SagaTekDonus(dugum);
}

/* AÇIKLAMA: Burada ise sorunlu düðümün saðýndaki düðüme saða tek dönüþ uygulanýr, sonra düðümün kendisine sola tek dönüþ uygulanýr.*/
AVLNode* AVLAgaci::SagSolDonus(AVLNode* dugum)
{

	SagaTekDonus(dugum->sag);
	return SolaTekDonus(dugum);
}

/* AÇIKLAMA: AVL AÐACI TEMEL ÖZELLÝÐÝ ÝÇKÖK GEZME / REKÜRSÝF YAPIDA*/
void AVLAgaci::ickok(AVLNode* kok)
{
	if (kok == NULL)
		return;
	ickok(kok->sol); //en sola git, solu yaz
	cout << kok->ogr->ogrNo << "  "; //kökü yaz
	ickok(kok->sag);//saðý yaz
}

/* AÇIKLAMA : AVL AÐACI TEMEL ÖZELLÝÐÝ SONRA KÖK GEZME / REKÜRSÝF YAPIDA */
void AVLAgaci::sonrakok(AVLNode* kok)
{
	if (kok == NULL)
		return;
	sonrakok(kok->sol);
	sonrakok(kok->sag);
	cout << kok->ogr->ogrNo << "  ";
}


/* AÇIKLAMA : AVL AÐACI TEMEL ÖZELLÝÐÝ ÖNCEKÖK GEZME / REKÜRSÝF YAPIDA*/
void AVLAgaci::oncekok(AVLNode* kok)
{
	if (kok == NULL)
		return;
	cout << kok->ogr->ogrNo << "  ";
	oncekok(kok->sol);
	oncekok(kok->sag);
}

/*  AÇIKLAMA:  AVL Aðacý Listeden farklý olduðu için, aðaçta gezmek listede farklý. En kolay yolu rekürsif fonksiyon ile gezmek olduðundan aþaðýda rekürsif fonksiyon kullanýlmýþtýr.kok->sag gittiði rekürsif fonksiyonda yaprak kalmayana kadar yani kok=NULL olana kadar en saða gidecektir.Ordan geri kalan hepsini toplayarak geriye doðru gelecektir.Aynýsý aþaðýdaki sol kýsým içinde geçerli.Bu aðacý gezme iþlemi olurkende aðacý yazdýrýyoruz.*/
void AVLAgaci::AVLYazdir(AVLNode* kok,int level)
{
	int i;
	if (kok != NULL)
	{
		AVLYazdir(kok->sag, level + 1);
		cout << endl;
		if (kok == root)
			cout << "KÖK -> ";
		for (i = 0; i < level && kok != root; i++)
			cout << "        ";
		cout << kok->ogr->ogrNo;
		AVLYazdir(kok->sol, level + 1);
	}

}
