// VeriYapılarıProje-v2.cpp: Konsol uygulamasının giriş noktasını tanımlar.
//

#include "stdafx.h"
#include <iostream>
#include "Fonksiyonlar.h"
#include "Menu.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Turkish");//Utf-8 karakter sorunu için
	Menu menu; //menümüzü oluşturduk
	menu.menuListele(); //menümüzü çağırdık
	Fonksiyonlar fonk;
	AVLAgaci* agac = new AVLAgaci();
	
	system("pause"); 
    return 0;
}

