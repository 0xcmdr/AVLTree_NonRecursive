#include "stdafx.h"
#include "AVLAgaci.h"
/* A�IKLAMA: G�R�LEN �K� �NTEGER DE�ERDEN EN B�Y�K OLANI BULUP D�NDEREN FONKS�YON, A�A�IDAK� FONKS�YONLARIMIZDA DESTEK OLARAK KULLANILMI�TIR
*/
int AVLAgaci::max(int a, int b) {
	return (a < b) ? b : a;
}

/* A�IKLAMA: En soldaki eleman�m�z� bulup d�nderen methodtur*/
AVLNode* AVLAgaci::EnKucuk(AVLNode* dugum) // en soldaki eleman� bulur
 {
	 if (dugum != NULL)
		 while (dugum->sol != NULL)
			 dugum = dugum->sol;
	return dugum;
}

/* A�IKLAMA: A�a�ta eleman yoksa k�k=NULL ise true de�ilse false d�nderir*/
bool AVLAgaci::BosMu()
{
	return (root == NULL) ? true : false; // bo�sa true yoksa false d�nder
}

/* A�IKLAMA: CONSTRUCTOR METHOD*/
AVLAgaci::AVLAgaci()
{
	root = NULL;
}

AVLAgaci::~AVLAgaci()
{
}

/* A�IKLAMA: AVL Agacinda, parametre olarak verilen ��renciyi, ��rencinin numaras�na g�re arayan fonksiyondur.Her bir d���me geldi�inde �grenci numaralar�n� kar��la�t�r�r.E�er numara d���mdekinden k���kse sola gider, b�y�kse sa�a gider.
 D���m� bulana kadar veya gidebilece�i d���m kalmayana kadar bu i�lem devam eder.Bulursa d���m�n pointerini, bulamazsa da NULL d�nderir*/
AVLNode* AVLAgaci::AVLBul(Ogrenci* o)
{
	AVLNode* GeziciNode = root;
	if (root==NULL) 
		return root; //a�a� bo�ssa
	else //bo� de�ilse
	{
		while (GeziciNode != NULL) // a�ac� gezmek i�in gezicinode olu�turuldu
		{
			if (o->ogrNo == GeziciNode->ogr->ogrNo) // ��renciyi bulursan d�ng�den ��k
				break;
			else if (o->ogrNo > GeziciNode->ogr->ogrNo)//girilen ��renci no,d���mdekinden b�y�kse sa� d���me git
				GeziciNode = GeziciNode->sag;
			else if (o->ogrNo < GeziciNode->ogr->ogrNo)//girilen ��renci no,d���mdekinden k���kse sol d���me git
				GeziciNode = GeziciNode->sol;
		}
		
	}
	return GeziciNode;
}

/* A�IKLAMA: Verilen ��renciyi AVL a�ac�na eklemizi sa�lar.Mant�k AVLBul fonksiyonu ile nerdeyse ayn�d�r.�ndexleme ��renci numaras�na g�redir. E�er a�a�ta hi� eleman yoksa k�k olarak en ba�a ��renciyi ekler. E�er a�a�ta eleman varsa, ilk d���me gelir, d���mdeki �grenci numaras�ndan k���kse girilen ��renci numaras�,sola gider. B�y�kse sa�a gider.NULL yani bo� d���m buldu�unda oraya yeni d���m eklenir.A�a�ta sa�da b�y�k elemanlar solda ise k���kler bulunur.AVL a�ac� oldu�u i�inse a�ac�n denge bozulma ihtimali vard�r.Bunun i�in d���m eklendikten sonra, eklenen d���m denge_kontrol fonksiyonuna g�nderilir.Ekleme ba�ar�l� ise true d�ner...*/
bool AVLAgaci::AVLEkle(Ogrenci* o)
{
	AVLNode* YeniNode = new AVLNode(o);
	if (root == NULL) // a�a� bo�sa ba�a ekle
	{
		root = YeniNode;
		return true;
	}
		
	else // de�ilse yerini bul
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

/* A�IKLAMA: BU FONKS�YON ALDI�I D���M�N SA� VE SOL �OCUKLARININ Y�KSEKL���N� ALIP D�NDER�R. Mesela bir d���m�m sol y�ksekli�ine bakmak i�in d�g�m->sol diye parametre yollarsak ve d���m mevcut de�ilse -1 d�nderir e�er orda d���m mevcut ise d���m�n sahip oldu�u y�kseklik de�erini d�nderir. Bu fonksiyon denge i�lemlerinde s�k�a kullan�lacakt�r*/
int AVLAgaci::yuk_hesap(AVLNode* dugum) 
{
	if (dugum==NULL)
		return -1;
	else 
		return dugum->yukseklik;
}

/* A�IKLAMA: 
AVL A�ac�m�z�n bel kemi�i dedi�imiz denge kontrol Fonksiyonun Ana giri� fonksiyonu olan bu fonksiyon.AVL A�ac�n� di�er a�a�lardan ay�ran solcocuk-sa�cocuk yuksekli�i -1,0,1 de�erlerinden farkl� olursa a�ac�n dengesinin bozulmas�d�r.Bu dengeyi her ekleme ve silme yapt���m�zda her d���m i�in bu �� de�erden birinin olmas�n� sa�lamal�y�z.

Bu Fonksiyonda �ncelikle kontrol d���m�m�z mevcut, bu d���m dengeyi bozan d���m olacakt�r ve bu d���m� rotasyon fonksiyonlar�na g�ndererek dengeyi olu�turaca��z.Bu fonksiyona yollad���m�z d���m de�eri, A�ACA EKLENEN DE�ER, A�A�TAN S�L�NEN DE�ER�N PARENT� VEYA D�N�� YAPILAN KR�T�K D���M olabilir. Yani de�i�iklik olan d���mden denge kontrol�ne ba�l�yoruz.

Gelen d���m de�erinden ba�lay�p, YUKARI do�ru , d���m�n sol y�ksekli�i ve sa� y�ksekli�inin maxsimumum de�erinin 1 fazlas�n� alarak, o d���m�n yuksekli�ini hesapl�yoruz.

Denge Fakt�r� ise, bir d���m�n sol ve sa� d���m�n�n y�kseklikleri fark�d�r.Bu de�er -1,0,1 den farkl� de�er olursa kontrol d���m�m�z denge fakt�r� bu de�erlerden farkl� olan d���me e�itlenir.Sorunlu d���m tespit edildi�i i�in d�ng�den ��k�l�r

E�er kontrol d���m� tespit edildiyse, a�ac�n rotasyon ile dengelenmesi gerekir bunun i�in AVLDengele fonksiyonunda gerekli rottasyon tespit edilip uygulan�r.*/
void AVLAgaci::denge_kontrol(AVLNode* dugum)
{
	AVLNode* kontrol=NULL; // sorunlu d���m� tutacak dugum
	AVLNode* sonraki = NULL;
	while(dugum!=NULL)
	{
	dugum->yukseklik = 1 + max(yuk_hesap(dugum->sol) , yuk_hesap(dugum->sag)); //o anki d���m�n y�kseklik hesab�
	dugum->denge_fak = (yuk_hesap(dugum->sol) - yuk_hesap(dugum->sag)); //o anki d���m�n dengefakt�r� hesab�
	if (dugum->denge_fak > 1 || dugum->denge_fak < -1)
	{
		kontrol = dugum; // hatal� d���m� tespit et
		break; // burada d�ng�den ��kmazsak, kontrol d���m� hatal� bulunabilir
	}
		
	
	dugum = dugum->parent; // denge fakt�r� bozulmad�k�a yukar� do�ru y�kseklik ve denge fakt�r� hesab� devam eder
	}
	if (kontrol != NULL)
		AVLDengele(kontrol);
}

/* A�IKLAMA: Bu fonksiyon yukar�da denge fakt�r� -1,0,1 den farkl� olup sorunlu tespit edilen d���md�r. �imdi denge fakt�r�n�n de�erine g�re ve sol ve sa� y�ksekliklere g�re rotasyonlar belirlenip uygulanacakt�r.A�a��da kodlar�n yan�nda a��klamas� yap�lm��t�r.Sol-Sa� yapt���m�z i�in dengefak > 1 sola bask�nl�k vard�r. dengefak <-1 ise sa� tarafta bask�nl�k vard�r.Ayr�yeten d�n��ler yap�ld�ktan sonra, d�n��e sebep olan d�g�m, rotasyon fonksiyonlar�ndan geri d�ner ve o d�g�mden yukar� do�ru tekrar denge kontrol� yap�l�r.*/
void AVLAgaci::AVLDengele(AVLNode* dugum)
{
	if (dugum->denge_fak > 1) //Sol taraf uzun, sa�a tek d�n�� veya Sol sa� d�n�� gerekir
		if (yuk_hesap(dugum->sol->sol) >= yuk_hesap(dugum->sol->sag)) // solun solun daha b�y�kse o yap�l�r
			denge_kontrol(SagaTekDonus(dugum));
			
		else //solun sa�� b�y�kse buras� yap�l�r
			denge_kontrol(SolSagDonus(dugum));

	if (dugum->denge_fak < -1) // de�er negatif yani sa� taraf daha uzun, sola tek d�n�� veya sa� sol d�n�� gereklidir
		if (yuk_hesap(dugum->sag->sag) >= yuk_hesap(dugum->sag->sol)) // sa��n sa�� uzunsa sola tek d�n��
		denge_kontrol(SolaTekDonus(dugum));

		else//de�ilse sapsol d�n�� yap�l�r
			denge_kontrol(SagSolDonus(dugum));

}

/* A�IKLAMA: Bu K�s�m a�a��daki AVLSil fonksiyonundan, e�er d���m tek �ocu�a sahipse veya hi� �ocu�u yoksa buras�na yollan�r.Fonksiyonu ay�rma sebebim bulunan d���m�n parentine ula�mak istememdi.Bu fonksiyonda yollanan d���mde e�er tek �ocuk varsa �ocu�un taraf� tespit edilir, ondan sonra bu �ocu�un atan�n sol koluna m� yoksa sa� koluna m� ba�l� oldu�u tespit edilir..��nk� d���m�n tek �ocu�u olunca �ocu�u d���m�n atas�na ba�lamam�z gerekiyor.Kol tespit edildikten sonra �ocuk ataya ba�lan�r. D���mlerin parentleri de�i�tirilir.�stenilen d���m silinir. E�er hi� cocuk yoksa, �ocu�a giden pointeri tespit edip NULL de�eri atamam�z gerekiyor, yoksa o k�s�m haf�zadan silindi�i i�in dengeleme fonksiyonunda sorun yarat�yor.Ondan sonra d���m silinir.*/
bool AVLAgaci::AVLSilTek(AVLNode* bulunan) //tek �ocuk veya hi� �ocuk yoksa buras� �al���r
{
	AVLNode* ata = bulunan->parent;
	AVLNode* tespit = NULL;
	tespit = (bulunan->sag != NULL) ? bulunan->sag : bulunan->sol; // �ocu�un taraf�n� tespit et
	if (tespit != NULL) // e�er tek �ocu�u varsa
	{
		 // �ocuk atan�n hangi koluna ba�l�
		if (ata->sag == bulunan)
			ata->sag = tespit; // �ocu�u ataya ba�la
			
		else if(ata->sol == bulunan) // �ocu�u atan�n soluna ba�la
			ata->sol = tespit; // �ocu�u ataya ba�la
			
		tespit->parent = ata; // parentini de�i�tir
	}

	//hi� �ocuk yok ise
	else
	{
		(ata->sag == bulunan) ? ata->sag = NULL : ata->sol = NULL; //�ocu�a giden pointere null ata
	}
	delete bulunan;//bulunan nodu sil,
	denge_kontrol(ata);
	return true; // i�lem ba�ar�l�
}

/* A�IKLAMA: Bu fonksiyon d���m�n iki �ocu�u varsa �al���r. �ncelikle silinecek d���m bulunur. Ondan sonra silinecek d���m�n sa��ndaki ENKUCUK d���m bulunur. Bu en k���k d���m�n ogrencisi ile, silinecek d���m�n �grencisi de�i�tirilir.Ondan sonra Enkucuk olarak tespit etti�imiz (yani alttaki d���m) silme fonksiyonuna g�nderilir. ��nk� tek �ocuk veya hi� �ocuk olmama ihtimali vard�r.Bu y�zden fonksiyonu iki ay�rd�k.*/
bool AVLAgaci::AVLSil(Ogrenci* o) 
{
	//�ncelikle silinecek d���m� bul
	AVLNode* bulunan = AVLBul(o);
	
	if(bulunan != NULL) // silinecek d���m mevcutsa
	{
		//iki �ocu�u varsa
		if (bulunan->sag != NULL && bulunan->sol != NULL)
		{
			AVLNode* enkucuk = EnKucuk(bulunan->sag);
			bulunan->ogr = enkucuk->ogr;// bulunan ile en kucuk eleman�n de�erlerini yer de�i�tir
			return AVLSilTek(enkucuk);// 1. ve 2. durum var m� diye kontrol et
		}
		else // tek �ocuk varsa veya hi� �ocu�u yoksa
			return AVLSilTek(bulunan);
	}

	return false; // silinecek dugum bulunamad�
}


/* A�IKLAMA: 
Denge fonksiyonun en �nemli k�sm� d�n�� fonksiyonlar�d�r. �ncelikle sola d�n�� yapaca��m�z i�in sagcocuk diye d���m olu�turuyoruz ve d���m�n sa��n� at�yoruz. D�n��ten sonra SA� �OCU�UN SOLUNA,D���M�N SA� KOLU ba�lanaca�� i�in, Sa� �ocu�un sol de�erini ge�ici bir d���mde tutuyoruz. Daha sonra k�k de�i�imlerini yapmam�z gerekir. 2 Durum mevcut, d�nd�r�lecek d���m root sa veya de�ilse, e�er d�nd�rlecek d���m a�ac�n rootuna e�itse,root ve sa� co�uk yer de�i�tirir.
E�er d�nd�r�lecek eleman a�ac�n k�k� de�ilse, ebeveyninin hangi koluna ba�l� oldu�unu tespit etmemiz gerekiyor.��nk� d�nd�rlecek d���m, ebeveyninin hangi koluna ba�l�ysa, d���m�n sagcocu�unu, ebeveyninin o koluna ba�layaca��z.
Daha sonra d�n��� tamamlamak i�in sagcocuk soluna dugumu ba�lar�z ve dugumun sa� kolunada ba�ta tuttu�umuz ge�ici node u ba�lar�z. B�ylece D�n�� tamamlanm�� olur. Ek olarak a�a�ta dengeyi sa�lamam�zda laz�m olan parentleri de�i�tirmeliyiz.Daha sonra d�nen k�sm�n y�ksekliklerini g�ncelleriz.Bu fonksiyondan d�nen d���m tekrardan denge kontrole gidecektir.*/
AVLNode* AVLAgaci::SolaTekDonus(AVLNode* dugum)
{
	AVLNode* sagcocuk = dugum->sag; // cocu�u tut
	AVLNode* gecici = sagcocuk->sol; // sol �ocu�un ta��nacak �ocu�unu tut
	//**Root De�i�imi
	if (dugum->parent == NULL) // e�er root d�nd�r�lecekse buras� �al���r
		root = sagcocuk;
	else // d�nd�relecek eleman root de�ilse
		if (dugum->parent->sag == dugum)//sag kola m� ba�l�
			dugum->parent->sag = sagcocuk; 
		else // sol kola m� ba�l�
			dugum->parent->sol = sagcocuk;
	sagcocuk->sol = dugum;
	dugum->sag = gecici;
	//**Parent de�i�imleri
	if (gecici != NULL)
		gecici->parent = dugum;
	sagcocuk->parent = dugum->parent;
	dugum->parent = sagcocuk;
	//**Y�kseklikleri g�ncelle
	dugum->yukseklik = 1 + max(yuk_hesap(dugum->sol), yuk_hesap(dugum->sag));
	sagcocuk->yukseklik = 1 + max(yuk_hesap(sagcocuk->sol), yuk_hesap(sagcocuk->sag));
	return dugum;
}

/*  A�IKLAMA:  Yukarida anlat�lan solatek d�n���n, tam tersidir.*/
AVLNode* AVLAgaci::SagaTekDonus(AVLNode* dugum)
{
	AVLNode* solcocuk = dugum->sol; // cocu�u tut
	AVLNode* gecici = solcocuk->sag; // sol �ocu�un ta��nacak �ocu�unu tut
									 //**Root De�i�imi
	if (dugum->parent == NULL) // e�er root d�nd�r�lecekse buras� �al���r
		root = solcocuk;
	else // d�nd�relecek eleman root de�ilse
		if (dugum->parent->sol == dugum) // sol kola m� ba�l�
			dugum->parent->sol = solcocuk;
		else // sa� kola m� ba�l�
			dugum->parent->sag = solcocuk;

	solcocuk->sag = dugum;
	dugum->sol = gecici;
	//**Parent de�i�imleri 
	if (gecici != NULL)
		gecici->parent = dugum;
	solcocuk->parent = dugum->parent;
	dugum->parent = solcocuk;
	//**Y�kseklikleri g�ncelle
	dugum->yukseklik = 1 + max(yuk_hesap(dugum->sol), yuk_hesap(dugum->sag));
	solcocuk->yukseklik = 1 + max(yuk_hesap(solcocuk->sol), yuk_hesap(solcocuk->sag));
	return dugum;
}

/* A�IKLAMA: 
Burda ise sorunlu d���m�n �nce solundaki d���me sola tek d�n�� uygulan�r, daha sonra d���m�m kendisine sa�a tek d�n�� uygulan�r.
*/
AVLNode* AVLAgaci::SolSagDonus(AVLNode* dugum)
{
	SolaTekDonus(dugum->sol);
	return SagaTekDonus(dugum);
}

/* A�IKLAMA: Burada ise sorunlu d���m�n sa��ndaki d���me sa�a tek d�n�� uygulan�r, sonra d���m�n kendisine sola tek d�n�� uygulan�r.*/
AVLNode* AVLAgaci::SagSolDonus(AVLNode* dugum)
{

	SagaTekDonus(dugum->sag);
	return SolaTekDonus(dugum);
}

/* A�IKLAMA: AVL A�ACI TEMEL �ZELL��� ��K�K GEZME / REK�RS�F YAPIDA*/
void AVLAgaci::ickok(AVLNode* kok)
{
	if (kok == NULL)
		return;
	ickok(kok->sol); //en sola git, solu yaz
	cout << kok->ogr->ogrNo << "  "; //k�k� yaz
	ickok(kok->sag);//sa�� yaz
}

/* A�IKLAMA : AVL A�ACI TEMEL �ZELL��� SONRA K�K GEZME / REK�RS�F YAPIDA */
void AVLAgaci::sonrakok(AVLNode* kok)
{
	if (kok == NULL)
		return;
	sonrakok(kok->sol);
	sonrakok(kok->sag);
	cout << kok->ogr->ogrNo << "  ";
}


/* A�IKLAMA : AVL A�ACI TEMEL �ZELL��� �NCEK�K GEZME / REK�RS�F YAPIDA*/
void AVLAgaci::oncekok(AVLNode* kok)
{
	if (kok == NULL)
		return;
	cout << kok->ogr->ogrNo << "  ";
	oncekok(kok->sol);
	oncekok(kok->sag);
}

/*  A�IKLAMA:  AVL A�ac� Listeden farkl� oldu�u i�in, a�a�ta gezmek listede farkl�. En kolay yolu rek�rsif fonksiyon ile gezmek oldu�undan a�a��da rek�rsif fonksiyon kullan�lm��t�r.kok->sag gitti�i rek�rsif fonksiyonda yaprak kalmayana kadar yani kok=NULL olana kadar en sa�a gidecektir.Ordan geri kalan hepsini toplayarak geriye do�ru gelecektir.Ayn�s� a�a��daki sol k�s�m i�inde ge�erli.Bu a�ac� gezme i�lemi olurkende a�ac� yazd�r�yoruz.*/
void AVLAgaci::AVLYazdir(AVLNode* kok,int level)
{
	int i;
	if (kok != NULL)
	{
		AVLYazdir(kok->sag, level + 1);
		cout << endl;
		if (kok == root)
			cout << "K�K -> ";
		for (i = 0; i < level && kok != root; i++)
			cout << "        ";
		cout << kok->ogr->ogrNo;
		AVLYazdir(kok->sol, level + 1);
	}

}
