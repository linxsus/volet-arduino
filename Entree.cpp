/*
 * entree.cpp
 *
 *  Created on: 22 août 2018
 *      Author: xavier
 */


#include "Entree.h"
#include "Comunication.h"


Entree::Entree() // constructeur par default
{
	EEPROM.get(ADD_NB_74HC595,NB_74HC595); // recuperation du nb de 74hc595 dans la prom
	// on initialise le tableau des entree a 0
	// la taille du tableau corespond au nb de 74hc595 gere.
	ancienneLectureOK=new byte[NB_74HC595](0); // !!! un new !!!
	ancienneValeur=0;
	nbFoiIdentique=0;
	// initialisation des pin de l'arduino pour gere les 74HC595
	pinMode(VALIDE_PIN_ENTREE, OUTPUT);
	pinMode(HORLOGE_PIN_ENTREE, OUTPUT);
	pinMode(DONNEE_PIN_ENTREE, INPUT);
	digitalWrite(HORLOGE_PIN_ENTREE, LOW);
	// on envoie un message pour dir que l'on vien de cree l'object (debug)
	com->println(MSG_CREATION_ENTREE,NB_74HC595);
}

Entree::~Entree() // destructeur
{
	delete ancienneLectureOK;
	// on envoie un message pour dir que l'on vien de detruire l'object (debug)
	com->println(MSG_DESTRUCTION_ENTREE);
	delay(100);// ici pour corriger un bug.
}


// affichage du tableau lecture entree.
void Entree:: lectureEntree()
{
	for (int i=0; i <NB_74HC595 ; i++ ) // pour chaque 74hc595
	{
			com->print(MSG_LECTURE_ENTREE,i); // j'affiche le numero du 74hc165
			com->println(ancienneLectureOK[i]); //j'afiche sa valeur
	}
}


/* on retourne le dernier bit qui a ete modifier si positif il a ete ajouter si negatif il a ete enlever*/
// !!! atention cette fonction ne renvoie qu'une seule modif a la fois.
// !!! si il y a plusieurs modif en meme temps. il faut de nouveau executer la fonction.
int Entree::testEntreeActive() {
	// init des valeurs
	int valeur = 0, // valeur a retourner (1 = entree 1 activer, -1 = entree 1 desactiver) les entree commance a 1
			t=0, // valeur temporaire du 74hc595 traite
			dif=0; // calcul pour savoir si le bit a ete activer=1,desactiver=-1,non changer=0

	digitalWrite(VALIDE_PIN_ENTREE, HIGH);// on signale que l'on va lire les donnee.
	for (int j=0;j<NB_74HC595;j++)// pour chaque 74hc595
	{
		t=ancienneLectureOK[j];// on lit sa valeur sauvegarder
		for (byte i = 0; i < 8; ++i) { // pour chaque bit contenu dans un 74hc595
			dif=(t & 1) - digitalRead(DONNEE_PIN_ENTREE); // on calcul la diference entre le dernier bit de t et la valeur lu sur le 74hc595
			if (dif>0) { // si on a un bit qui est passer de 1 a 0
				valeur = -1 - ((j*8) + i); // on calcul la valeur a renvoyer
			}
			else if (dif<0){ // si on a un bit qui est passer de 1 a 0
				valeur =1+((j*8) + i); // on calcul la valeur a renvoyer
			}
			// on met un coup d'horloge pour lire la valeur suivante sur le 74hc595
			digitalWrite(HORLOGE_PIN_ENTREE, HIGH);
			digitalWrite(HORLOGE_PIN_ENTREE, LOW);
			t/=2; // on fait un decalage de 1 bit vers la droite pour t
		}
	}
	digitalWrite(VALIDE_PIN_ENTREE, LOW); // on signale que l'on arrete de lire les donnee.
	//Serial.println(valeur);
	return valeur; // on retourne le dernier bit qui a ete modifier si positif il a ete ajouter si negatif il a ete enlever
}

int Entree::entreeActive(){
	int8_t valeur=Entree::testEntreeActive();
	int8_t valeurRetour=0;
	if (valeur!=0) //il y a un changement en cours
	{
		if (valeur!=ancienneValeur){ // c'est un nouveau changement
//			if (nbFoiIdentique>0){
//				Serial.println(nbFoiIdentique);
//			}
			nbFoiIdentique=0;
			ancienneValeur=valeur;
		}else
		{
			nbFoiIdentique++;
			if (nbFoiIdentique>2){
				valeurRetour=valeur;
				// on met a jour le tableau de sauvegarde des 74hc595
				int8_t bit=abs(valeur)-1;
				if (valeur>0){ // si on ajouter un bit
					ancienneLectureOK[bit/8]+=(1<<(bit%8)); // on ajoute ce bit au tableau de sauvegarde de lecture
					com->println(MSG_ACTIVATION_ENTREE,bit+1);// on envoie un message pour dir qu'une entree a ete active
				} else if (valeur<0){// si on enleve un bit
					ancienneLectureOK[bit/8]-=(1<<(bit%8)); // on enleve ce bit au tableau de sauvegarde de lecture
					com->println(MSG_DESACTIVATION_ENTREE,bit+1);// on envoie un message pour dir qu'une entree a ete desactive
				}
			}
		}
	}
	return valeurRetour;
}

