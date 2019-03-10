/*
 * sortie.h
 *
 *  gestion des sortie (74hc165)
 *
 *  Created on: 22 août 2018
 *      Author: xavier Gouraud
 */

#ifndef SORTIE_H_
#define SORTIE_H_
#include "general.h"



class Sortie {
public:
	Sortie();// constructeur par default
	virtual ~Sortie();// destructeur
	virtual void activer(byte relais); // activation du relais passer en parametre
	virtual void desactiver(byte relais);// desactivation du relais passer en parametre
	void lectureSortie(); // affichage du tableau relais_sortie
	void ecritureSortie();// activation des relais en fonction du tableau relais_sortie
	//pour les test
	// activer le relais taper au clavier et desactive le relais suivant
	void test();

protected:
	byte* relais_sortie;// tabeau contenant la valeur des differents relais activer
};


#endif /* SORTIE_H_ */
