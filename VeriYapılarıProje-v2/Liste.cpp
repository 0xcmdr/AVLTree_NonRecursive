#include "stdafx.h"
#include "Liste.h"

/*AÇIKLAMA: Boþ liste için head=NULL olur. Constructor method*/
Liste::Liste()
{
	head = NULL;
}

/*AÇIKLAMA: Memory Leak yaþanmamasý için, liste nesnesi silindiðinde hafýzadan listenin içini boþaltýr*/
Liste::~Liste()
{
	
	Node *silinecekNode = head, *sonrakiNode = NULL;
	while (silinecekNode->sonraki != NULL) {
		sonrakiNode = silinecekNode->sonraki;// bir sonraki nodu belirleyip, o anki nodu siliyoruz
		delete silinecekNode;
		silinecekNode = sonrakiNode;//þuanki nodu tekrar atýyoruz..
	}
}

/*AÇIKLAMA: Liste boþsa true , deðilse false dönderir*/
bool Liste::BosMu()
	{
	return (head == NULL) ? true : false; // boþsa true yoksa false dönder
	}

/*AÇIKLAMA: Oluþturulan bir listenin belirli bir indexine, Ogrenci eklemesi yapar.2 özel durumu vardýr. Baþa ekleme ve ortaya veya sona ekleme. Listenin içinde belirtilen index eðer sýfýrsa direkt baþa ekler, currIndex=1 olur ve 1.sýraya ekler, diðer þekilde indeximi currIndex olana kadar liste içinde gezinerek indeximizin  denk geldiði node'u tespit eder. Tespit edilen node'un hemen sonrasýna yeni node eklenir. Bu çift taraflý baðlantýlý liste olduðu için önceki deðerleride deðiþecektir*/
bool Liste::NodeEkle(int index,Ogrenci* o) 
{
	if (index < 0) return NULL; // index kontrolü
	int currIndex = 1; //istenilen indexteki elemaný bulmak için kullanýlýr.Asýl index 0.indexten baþlayarak ilerler.
	Node* currNode = head;
	while (currNode && index > currIndex) {//istenin index'ten bir önceki elemanýný bulup, onu currNode deðerine atýyoruz.
		currNode = currNode->sonraki;
		currIndex++;
	}

	if (index > 0 && currNode == NULL) return NULL;
	
	Node* NewNode = new Node(o);

	if (index == 0) { //eðer eleman baþa eklenecekse
		NewNode->sonraki = head;
		head = NewNode;
		NewNode->onceki = NULL;
	}

	else { //ortaya veya sona eklenecekse
		Node* AfterNode = currNode->sonraki;// bir sonraki nodu tutmak için
		if(AfterNode)
			AfterNode->onceki = NewNode;
		NewNode->sonraki = currNode->sonraki;
		currNode->sonraki = NewNode;
		NewNode->onceki = currNode;
	}
	return (NewNode == NULL) ? false : true;
}

/*AÇIKLAMA: Verilen öðrencinin ögrenci numarasýna göre öðrenci varsa, olduðu node 'u dönderir yoksa NULL dönderir*/
Node* Liste::NodeBul(Ogrenci* o) {
	Node* currNode = head;
	int currIndex = 1;
	while (currNode && currNode->ogr->ogrNo != o->ogrNo) { //istenilen düðümü buluyor
		currNode = currNode->sonraki;//numaralar uyuþmuyorsa diðer düðüme geç
	}
	return currNode;

}
/*AÇIKLAMA: 
Verilen indexten, o indexe tekabül eden node'u bulur ve pointerini dönderir. Bu fonksiyon heapsort için yazýlmýþtýr
*/
Node* Liste::indextenNodeBul(int index)
{
	Node* gecici = head;
	for (int i = 0; i < index; i++) {
		gecici = gecici->sonraki;
	}
	return gecici; // bulunan node'u dönder
}

/*AÇIKLAMA: Aynen NodeEkle fonksiyonunda olduðu gibi bundada ögrenci numarasýna göre listede gezerek istenen index bulunur, bulunan indexten önceki node geçici bir node'a atýlýr. Gecici node un sonrali deðeri, bulunan node'un sonraki deðerine eþitlenir ve bulunannode silinir. Eðer gecici node NULL ise bu listenin baþýndaki node'u bulduðumuzu gösterir.*/
int Liste::NodeSil(Ogrenci* o) {

	Node* arananNode = head;
	int ArananIndex = 1;
	while (arananNode && arananNode->ogr->ogrNo != o->ogrNo) {
		arananNode = arananNode->sonraki;
		ArananIndex++;
	}

	if (arananNode) {
		Node* oncekiNode = arananNode->onceki;
		if (oncekiNode) {
			oncekiNode->sonraki = arananNode->sonraki;
			delete arananNode;
		}
		else {
			head = arananNode->sonraki;
			delete arananNode;
		}
		return ArananIndex;
	}
	return 0;
}
/*AÇIKLAMA: Listenin baþýndan baþlýyarak tüm öðrencileri yazdýrýr,her bir yazdýrmasýna sirayi bir arttýrýr, bu sýra deðiþkeni bizim kaçýncý öðrenciyi yazdýrdýðýmýzý gösteren deðerdir*/
void Liste::ListeyiYazdir() 
{
	int sira = 1;
	Node* yazilanNode = head;
	while (yazilanNode != NULL) 
	{
		cout << sira << ". Öðrencinin, ";
		yazilanNode->ogr->OgrenciYaz();
		cout << "***********************************"<<endl;
		yazilanNode = yazilanNode->sonraki;
		sira++;
	}
	
	
}
