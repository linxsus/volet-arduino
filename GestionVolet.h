/*
 * GestionVolet.h
 *
 *  Created on: 16 oct. 2018
 *      Author: phenom
 */


#ifndef GESTIONVOLET_H_
#define GESTIONVOLET_H_
#include "Comunication.h"

class GestionVolet {
public:
	GestionVolet(); // constructeur
	virtual ~GestionVolet(); // destructeur
	void run(); // fonction loop.
	void gestionMsg(Msg*); // fonction de la geston des messages
private:
	int freeRam (); // retourne l'espace libre de la RAM
};

#endif /* GESTIONVOLET_H_ */
