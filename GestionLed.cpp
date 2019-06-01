/*
 * GestionLed.cpp
 *
 *  Created on: 26 oct. 2018
 *      Author: phenom
 */
#include "Led.h"
#include "GestionLed.h"
#include "GestionVolet.h"
#include "Entree.h"
#include "Sortie.h"
#include "Comunication.h"
#include "Prom.h"

extern Sortie* sortie;

GestionLed::GestionLed():GestionVolet() {
	delete(sortie);
	sortie=new Led;

}

GestionLed::~GestionLed() {
}

