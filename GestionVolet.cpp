/*
 * GestionVolet.cpp
 *
 *  Created on: 16 oct. 2018
 *      Author: phenom
 */

#include "GestionVolet.h"
#include "Entree.h"
#include "Sortie.h"
#include "Comunication.h"
#include "Prom.h"
#include "AddProm.h"



Sortie* sortie(0);
Entree* entree(0);
Comunication* com(0);
Prom* prom(0);
int8_t modifInter(0);


GestionVolet::GestionVolet() {
	//!! new!!
		com=new Comunication; //a effectuer en premier pour definir la comunication
	    com->println(MSG_INIT_START);
	    //!! new !! on cree les object
	    sortie=new Sortie;
	    entree=new Entree;
	    prom=new Prom;
	    com->println(MSG_INIT_FIN);
//	    byte message[NB_BYTE_LIGNE]={1,2,3,4,5,6,7,8};
//	    prom->ecriture(0,message);
//	    byte message1[NB_BYTE_LIGNE]={9,10,11,12,13,14,15,16};
//	   	prom->ecriture(1,message1);
//	   	prom->ecriture(ADD_NB_74HC595,2);
//	   	prom->ecriture((const byte)ADD_NB_74HC165,2);
}

GestionVolet::~GestionVolet() {
	delete sortie;
	delete entree;
	delete prom;
	// !!!doit toujour etre en dernier
	delete com;
	delay(100);// ici pour corriger un bug.
}

// fonction pour le calucl du reste de memoire.
// fonction prise sur internet.
int GestionVolet::freeRam () {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

//le vrais loop
void GestionVolet::run()
{
	modifInter=entree->entreeActive(); // on recupere si il y a eu une modif sur les entree
	if (modifInter!=0){ // si il a eu une modif
		if (modifInter>0){ // si c'est une entree que l'on vien d'activer
			sortie->activer(EEPROM.read(ADD_MIN_ES+modifInter-1));
		}else //sinon c'est un une entree que l'on vien de desactiver
		{
			sortie->desactiver(EEPROM.read(ADD_MIN_ES-modifInter-1)); //ici il y a un - car modifinter est negatif
		}
	}

	if (com->isLecture()){ // si il y a une lecture valide sur le port com
		gestionMsg(com->lecture()); // gestion de du message
	}
	if (freeRam()<100){ // si il reste moin de 100 octet de memoire
		reset=true; // je signal qu'il faut rester.
	}
}

//gestion des messages.
void GestionVolet::gestionMsg(Msg* msg){
	switch (msg->tabTemp[0]){
    case RESET: // reset
       reset=true;
       break;
    case LEC_PROM: //affichage du contenue de la prom
    	prom->lecture();
    	break;
    case LEC_SORTIE: //affichage du contenue des sortie
    	sortie->lectureSortie();
    	break;
    case LEC_ENTREE: //affichage du contenue des entree
    	entree->lectureEntree();
    	break;
    case ACTIVATION_SORTIE: //activation d'une sortie (msg->tabTemp[1])
    	sortie->activer(msg->tabTemp[1]);
    	break;
    case DESACTIVATION_SORTIE: //desactivation d'une sortie (msg->tabTemp[1])
    	sortie->desactiver(msg->tabTemp[1]);
    	break;
    case ECRITURE_PROM: // ecriture dans la prom a l'adress (msg->tabTemp[1])  des donnee (msg->tabTemp[2])
    	prom->ecriture(msg->tabTemp[1],msg->tabTemp[2]);
    	break;
    case MEMOIRE_RESTANTE: // demande de memoire restante
    	com->print(MSG_MEMOIRE_RESTANTE,freeRam()/100); // affichage en 2 fois car on est sur un int pas un byte
    	com->println(freeRam()%100);
    	break;
    default: // on a un message que l'on ne sait pas gerer
       com->println(MSG_MSG_INCONNUE);
 }
	msg->valide=false;
}
;
