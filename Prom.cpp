
/*
 * Prom.cpp
 *
 *  Created on: 15 oct. 2018
 *      Author: phenom
 */
#include "Prom.h"
#include "Comunication.h"

Prom::Prom() {
	com->println(MSG_CREATION_PROM);
}

Prom::~Prom() {
	com->println(MSG_DESTRUCTION_PROM);
	delay(100);// ici pour corriger un bug.
}

void Prom::ecriture(byte numLigne,const byte message[NB_BYTE_LIGNE]) {
	for (int8_t i=0;i<NB_BYTE_LIGNE;i++) // pour chaque BYTE DE LA LIGNE
				{
					EEPROM.put((ADD_MIN_ES+i+(NB_BYTE_LIGNE*numLigne)),message[i]); // affichage de la case memoire
				}
	com->println(MSG_ECRITURE_ES,numLigne); // affichage pour dire que l'on affiche une ligne de memoire
}

void Prom::ecriture(byte adresse,const byte message) {
	EEPROM.put(adresse,message); // affichage de la case memoire
	com->println(MSG_ECRITURE_ADRESSE,adresse); // affichage pour dire que l'on affiche une ligne de memoire
}

void Prom::lecture() {
// affichage du nb de 74hc165
com->println(MSG_NB_74HC165,EEPROM.read(ADD_NB_74HC165));
// affichage du nb de 74hc595
com->println(MSG_NB_74HC595,EEPROM.read(ADD_NB_74HC595));
// affichage des lien ES
for(int8_t i=0;i<((ADD_MAX_ES-ADD_MIN_ES)+1)/NB_BYTE_LIGNE;i++) // pour chaque ligne memoire (la taille d'une ligne est defini par NB_BYTE_LIGNE fichier AddProm)
		{
			com->print(MSG_AFFICHAGE_ES); // affichage pour dire que l'on affiche une ligne de memoire
			for (int8_t j=0;j<NB_BYTE_LIGNE;j++) // pour chaque BYTE DE LA LIGNE
			{
				com->print(EEPROM.read(ADD_MIN_ES+j+(i*NB_BYTE_LIGNE))); // affichage de la case memoire
			}
			com->println(i); // affichage du n° de ligne (on l'affiche en dernier pour le prinln qui envoie le code de controle)
		}
}



