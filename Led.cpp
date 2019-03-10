/*
 * Led.cpp
 *
 *  Created on: 26 oct. 2018
 *      Author: phenom
 */

#include "Led.h"
#include "Comunication.h"

Led::Led():Sortie() {
	delete(relais_sortie);
	relais_sortie=new byte[2](0);
	//ecritureSortie();

}

Led::~Led() {
	// TODO Auto-generated destructor stub
}

void Led::activer(byte relais) {
	{
		Sortie::desactiver(relais);
	}
}

void Led::desactiver(byte relais) {
	{
		Sortie::activer(relais);
	}
}
