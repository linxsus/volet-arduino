/*
 * sortie.cpp
 *
 * gestion des sortie (74hc165)
 *
 *  Created on: 22 août 2018
 *      Author: xavier Gouraud
 */
#include "Sortie.h"
#include "Comunication.h"


// constructeur par default
Sortie::Sortie() {
	// on initialise le tableau.
	relais_sortie=new byte[2](255);// !!! un new !!!
	// initialisation des pin de l'arduino
	for (int i=2;i<=13;i++){
		pinMode(i, OUTPUT);
		digitalWrite(i, HIGH);
	}
	// on envoie un message pour dir que l'on vien de cree l'object (debug)
	com->println(MSG_CREATION_SORTIE);
}

// destructeur
Sortie::~Sortie()
{
	// on envoie un message pour dir que l'on vien de detruire l'object (debug)
	com->println(MSG_DESTRUCTION_SORTIE);
	delete relais_sortie;
	delay(100);// ici pour corriger un bug.
}

// active les relais
void Sortie::ecritureSortie()
{

	for (int8_t i = 0; i<2; i++) { // pour chaque byte relais_sortie
		for (int8_t j = 0; j < 8; j++)  {
		        digitalWrite(2+i*8+j, !!(relais_sortie[(byte)i] & (1 << j)));
		      }
    }
	//delay(100);
	// on envoie un message pour dir que l'on vien d'ecrire sur les sorties (debug)
	com->println(MSG_ECRITURE_SORTIE);
}

// activation du relais passer en parametre
void Sortie::activer(byte relais) {
	{
		relais--; // on commance au relais 0 en informatique
		byte num = relais / 8; // je calcul le numero de l'index a utiliser.
		byte sortie = (relais % 8); // quelle sortie sur cette index.
		// j'active le relais.
		bitClear(relais_sortie[num], sortie);
		ecritureSortie();
		// on envoie un message pour dir que l'on vien d'activer une sortie
		com->println(MSG_ACTIVATION_SORTIE,relais+1);
	}
}

// desactivation du relais passer en parametre
void Sortie::desactiver(byte relais) {
	{
		relais--;// on commance au relais 0 en informatique
		byte num = relais / 8; // je calcul le numero de l'index a utiliser.
		byte sortie = (relais % 8); // quelle sortie sur cette index.
		// je desactive le relais.
		bitSet(relais_sortie[num], sortie);
		ecritureSortie();
		// on envoie un message pour dir que l'on vien de desactiver une sortie
		com->println(MSG_DESACTIVATION_SORTIE,relais+1);
	}
}

// affichage du tableau relais_sortie
// permet de faire des synchro ou des test.
void Sortie::lectureSortie()
{
	for (int8_t i = 1; i>=0; i--) { // pour chaque index de relais_sortie
		com->print(MSG_LECTURE_SORTIE,i); // j'affiche le numero de l'indexs
		com->println(relais_sortie[i]); //j'afiche sa valeur
	}
}


// pour les test
// activer le relais taper au clavier et desactive le relais suivant
void Sortie::test()
{
	if (Serial.available())
	{
		char ch = Serial.read(); // lecture d'un caractere
		byte led = ch - '0'; // transforamtion pour avoir un numero de relais
		// message
		Serial.print("debug activer ");
		Serial.println(led);
		activer(led); // activation du relais
		Serial.print("debug desactiver ");
		Serial.println(led+1);
		desactiver(led+1); //desactivation du relais
	}
}
