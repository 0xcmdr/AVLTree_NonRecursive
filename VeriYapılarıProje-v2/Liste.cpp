#include "stdafx.h"
#include "Liste.h"

/*A�IKLAMA: Bo� liste i�in head=NULL olur. Constructor method*/
Liste::Liste()
{
	head = NULL;
}

/*A�IKLAMA: Memory Leak ya�anmamas� i�in, liste nesnesi silindi�inde haf�zadan listenin i�ini bo�alt�r*/
Liste::~Liste()
{
	
	Node *silinecekNode = head, *sonrakiNode = NULL;
	while (silinecekNode->sonraki != NULL) {
		sonrakiNode = silinecekNode->sonraki;// bir sonraki nodu belirleyip, o anki nodu siliyoruz
		delete silinecekNode;
		silinecekNode = sonrakiNode;//�uanki nodu tekrar at�yoruz..
	}
}

/*A�IKLAMA: Liste bo�sa true , de�ilse false d�nderir*/
bool Liste::BosMu()
	{
	return (head == NULL) ? true : false; // bo�sa true yoksa false d�nder
	}

/*A�IKLAMA: Olu�turulan bir listenin belirli bir indexine, Ogrenci eklemesi yapar.2 �zel durumu vard�r. Ba�a ekleme ve ortaya veya sona ekleme. Listenin i�inde belirtilen index e�er s�f�rsa direkt ba�a ekler, currIndex=1 olur ve 1.s�raya ekler, di�er �ekilde indeximi currIndex olana kadar liste i�inde gezinerek indeximizin  denk geldi�i node'u tespit eder. Tespit edilen node'un hemen sonras�na yeni node eklenir. Bu �ift tarafl� ba�lant�l� liste oldu�u i�in �nceki de�erleride de�i�ecektir*/
bool Liste::NodeEkle(int index,Ogrenci* o) 
{
	if (index < 0) return NULL; // index kontrol�
	int currIndex = 1; //istenilen indexteki eleman� bulmak i�in kullan�l�r.As�l index 0.indexten ba�layarak ilerler.
	Node* currNode = head;
	while (currNode && index > currIndex) {//istenin index'ten bir �nceki eleman�n� bulup, onu currNode de�erine at�yoruz.
		currNode = currNode->sonraki;
		currIndex++;
	}

	if (index > 0 && currNode == NULL) return NULL;
	
	Node* NewNode = new Node(o);

	if (index == 0) { //e�er eleman ba�a eklenecekse
		NewNode->sonraki = head;
		head = NewNode;
		NewNode->onceki = NULL;
	}

	else { //ortaya veya sona eklenecekse
		Node* AfterNode = currNode->sonraki;// bir sonraki nodu tutmak i�in
		if(AfterNode)
			AfterNode->onceki = NewNode;
		NewNode->sonraki = currNode->sonraki;
		currNode->sonraki = NewNode;
		NewNode->onceki = currNode;
	}
	return (NewNode == NULL) ? false : true;
}

/*A�IKLAMA: Verilen ��rencinin �grenci numaras�na g�re ��renci varsa, oldu�u node 'u d�nderir yoksa NULL d�nderir*/
Node* Liste::NodeBul(Ogrenci* o) {
	Node* currNode = head;
	int currIndex = 1;
	while (currNode && currNode->ogr->ogrNo != o->ogrNo) { //istenilen d���m� buluyor
		currNode = currNode->sonraki;//numaralar uyu�muyorsa di�er d���me ge�
	}
	return currNode;

}
/*A�IKLAMA: 
Verilen indexten, o indexe tekab�l eden node'u bulur ve pointerini d�nderir. Bu fonksiyon heapsort i�in yaz�lm��t�r
*/
Node* Liste::indextenNodeBul(int index)
{
	Node* gecici = head;
	for (int i = 0; i < index; i++) {
		gecici = gecici->sonraki;
	}
	return gecici; // bulunan node'u d�nder
}

/*A�IKLAMA: Aynen NodeEkle fonksiyonunda oldu�u gibi bundada �grenci numaras�na g�re listede gezerek istenen index bulunur, bulunan indexten �nceki node ge�ici bir node'a at�l�r. Gecici node un sonrali de�eri, bulunan node'un sonraki de�erine e�itlenir ve bulunannode silinir. E�er gecici node NULL ise bu listenin ba��ndaki node'u buldu�umuzu g�sterir.*/
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
/*A�IKLAMA: Listenin ba��ndan ba�l�yarak t�m ��rencileri yazd�r�r,her bir yazd�rmas�na sirayi bir artt�r�r, bu s�ra de�i�keni bizim ka��nc� ��renciyi yazd�rd���m�z� g�steren de�erdir*/
void Liste::ListeyiYazdir() 
{
	int sira = 1;
	Node* yazilanNode = head;
	while (yazilanNode != NULL) 
	{
		cout << sira << ". ��rencinin, ";
		yazilanNode->ogr->OgrenciYaz();
		cout << "***********************************"<<endl;
		yazilanNode = yazilanNode->sonraki;
		sira++;
	}
	
	
}
