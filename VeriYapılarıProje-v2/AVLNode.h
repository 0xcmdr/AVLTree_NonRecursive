#pragma once
#include "Ogrenci.h"
class AVLNode
{
	Ogrenci* ogr = new Ogrenci();
	AVLNode* sol;
	AVLNode* sag;
	AVLNode* parent;
	int yukseklik;
	int denge_fak;

public:
	friend class Fonksiyonlar;
	friend class AVLAgaci;
	AVLNode::AVLNode();
	AVLNode(Ogrenci* o);
	~AVLNode();
};

