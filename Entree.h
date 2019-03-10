/*
 * entree.h
 *
 *  Created on: 22 août 2018
 *      Author: phenom
 */

#ifndef ENTREE_H_
#define ENTREE_H_
#include "general.h"



#define VALIDE_PIN_ENTREE A0//10 // maron 		pin de validation des 74hc595
#define HORLOGE_PIN_ENTREE A1 //9 // jaune		pin de la clock
#define DONNEE_PIN_ENTREE  A2//8 //violet		pin des donnee

//#define VALIDE_PIN_ENTREE 10 // maron 		pin de validation des 74hc595
//#define HORLOGE_PIN_ENTREE 9 // jaune		pin de la clock
//#define DONNEE_PIN_ENTREE  8 //violet		pin des donnee
/*
byte lectureCircuitEntree();
void lectureEntree();
void affichageEntree();
void initEntree();
*/

class Entree {
public:
	Entree();// constructeur par default
	virtual ~Entree();// destructeur
	// on retourne le dernier bit qui a ete modifier si positif il a ete ajouter si negatif il a ete enlever
	// !!! atention cette fonction ne renvoie qu'une seule modif a la fois.
	// !!! si il y a plusieurs modif en meme temps. il faut de nouveau executer la fonction.
	int entreeActive();
	void lectureEntree(); // affichage du tableau lecture entree.
private:
	byte NB_74HC595; // nb de 74hc595 gere
	byte* ancienneLectureOK; // tabeau contenant la valeur des differents 74hc595 validee
	int8_t ancienneValeur;
	byte nbFoiIdentique;
	int testEntreeActive();
};



#endif /* ENTREE_H_ */
