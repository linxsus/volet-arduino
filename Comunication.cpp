/*
 * Comunication.cpp
 *
 *  Created on: 15 oct. 2018
 *      Author: phenom
 */

#include "Comunication.h"

// on renvoie la fonction d'interruption de la voie série vers com.lecture
void serialEvent()
{
    if (com!=0){
	   com->eventlecture();
    }
}



Comunication::Comunication() {
	Serial.begin(SERIAL_BAUD); // on definit la vitesse de comunication du port com
	//!!! new !!!
	serialCourante=new Msg;
	serialGood=new Msg;
	println(MSG_CREATION_COMUNICATION); // on envoie un message de creation
}

Comunication::~Comunication() {
	println(MSG_DESTRUCTION_COMUNICATION);
	delete serialCourante;
	delete serialGood;
	delay(100);// ici pour corriger un bug.
}

void Comunication::eventlecture() {
	char car=Serial.read(); // on regarde lit le dernier caractere saisie
	if (car!=-1){ // si il y a bien un caractere
		if (car>='0' && car<='9') // si c'est un nombre
		{
			serialCourante->temp=(10*serialCourante->temp)+(car-'0'); // calcul le nombre envoyer
			serialCourante->valideInt=true; // on valide le faite qu'il y ai bien un nombre
		}else if (car==' ' || car=='\r'){ //sinon si c'est un espace ou un retour chariot
			if (serialCourante->valideInt==true){ // si il y a eu un nombre
				if (serialCourante->ind<NB_MAX_VALEUR){ // si on est pas ateint la limite des valeur sur une ligne
					serialCourante->tabTemp[serialCourante->ind]=serialCourante->temp; // on ajoute la valeur saisie au tableau
					serialCourante->ind++; // on passe au suivant
					// on reinitialise les variables
					serialCourante->temp=0;
					serialCourante->valideInt=false;
				}else{ // sinon on a depasser la limite
					reset=true; // on met reset a true
				}
			}
			if(car=='\r'){ // si c'est un retour chario
				if (calculControle(serialCourante->tabTemp,serialCourante->ind-1)==serialCourante->tabTemp[serialCourante->ind-1]) // si le crc est correcte
				{
					serialCourante->valide=true; // on a une lecture valide
					delete serialGood; // suprime l'ancienne l'ecture
					serialGood=serialCourante; // la lecture en cours devien la lecture valide
					serialCourante=new Msg;// on recree une nouvelle lecture en cours
				}else{ // sinon le crc n'est pas correcte
					com->println(MSG_CRC_NOK,calculControle(serialCourante->tabTemp,serialCourante->ind-1)); //envoie un message d'erreur
					delete serialCourante; // supprime l'ancienne l'ecture
					delay(50); // au cas ou il y ai un bug.
					serialCourante=new Msg;// on recree une nouvelle lecture en cours
				}

			}
		}
	}
}


bool Comunication::isLecture() {
	return serialGood->valide;
}

Msg* Comunication::lecture() {
	return serialGood;
}

void Comunication::ajoutControle(int msg) {
	for ( byte j = 0 ; j < 16 ; j ++ ) // pour chaque bits !!!
			{
				crc = ( ( msg ^ retenue)  << 7 )   |  (crc >> 1); // nouveau crc
				retenue = (crc>>7)^(crc>>4)^(crc>>3)^crc; // retenue a xorer (dans bit0), autres bits quelconques
				msg >>= 1; // bit suivant
			}
}

byte Comunication::calculControle(const byte msg[NB_MAX_VALEUR],const byte nbByte){
	byte result = 0;
	byte ret = 0;
	for ( byte i = 0 ; i < nbByte ;i ++ ) // pour chaque Byte
	{
		byte octet_lu = msg[i];
		for ( byte j = 0 ; j < 16 ; j ++ ) // pour chaque bits !! ici il y a 16 pour la compatibilité avec les int
		{
			result = ( ( octet_lu ^ ret)  << 7 )   |  (result >> 1); // nouveau crc
			ret = (result>>7)^(result>>4)^(result>>3)^result; // retenue a xorer (dans bit0), autres bits quelconques
			octet_lu >>= 1; // bit suivant
		}
	}

	return result;
}

//void Comunication::ajoutControle(int msg) {
//	crc+=msg+(msg>>2);
//}
//
//byte Comunication::calculControle(const byte msg[NB_MAX_VALEUR],const byte nbByte){
//	for ( byte i = 0 ; i < nbByte ;i ++ ) // pour chaque Byte
//	{crc+=msg[i]+(msg[i]>>2);
//	}
//
//	return crc;
//}

