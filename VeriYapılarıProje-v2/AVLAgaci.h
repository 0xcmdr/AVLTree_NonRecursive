#pragma once
#include "AVLNode.h"
class AVLAgaci
{
public:AVLNode* root;
public:
	int max(int a, int b);
	bool BosMu();
	AVLNode* EnKucuk(AVLNode* dugum);
	bool AVLEkle(Ogrenci* o);
	AVLNode* AVLBul(Ogrenci* o);
	bool AVLSil(Ogrenci* o);
	bool AVLSilTek(AVLNode* bulunan);
	int yuk_hesap(AVLNode* dugum);
	void denge_kontrol(AVLNode* dugum);
	void AVLDengele(AVLNode* denge);
	void AVLYazdir(AVLNode* ptr, int level);
	void oncekok(AVLNode* kok);
	void sonrakok(AVLNode* kok);
	void ickok(AVLNode* kok);
	AVLNode* SolaTekDonus(AVLNode* dugum);
	AVLNode* SagaTekDonus(AVLNode* dugum);
	AVLNode* SolSagDonus(AVLNode* dugum);
	AVLNode* SagSolDonus(AVLNode* dugum);
	AVLAgaci();
	~AVLAgaci();

};

