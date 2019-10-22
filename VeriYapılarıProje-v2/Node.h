#pragma once
#include "Ogrenci.h"
class Node
{
public:
	Ogrenci *ogr = new Ogrenci();
	Node* onceki;
	Node* sonraki;
	
public:
	Node();
	Node(Ogrenci* o);
	~Node();
};

