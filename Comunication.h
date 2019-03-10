/*
 * Comunication.h
 *
 * class permetant de gere la comunication sur le port com.
 * gestion de la reception des info pour le mettre sous forme de tableau de byte
 * gestion de l'envoie de message
 * gestion d'un crc.
 *
 *  Created on: 15 oct. 2018
 *      Author: phenom
 */




#ifndef COMUNICATION_H_
#define COMUNICATION_H_

//#define DEBUG_XG

#include "general.h"
#include "MSG.h"

//structure de donnee pour la lecture sur le por com
struct Msg{
	byte temp=0;
	byte tabTemp[NB_MAX_VALEUR]={0};
	byte ind=0;
	bool valideInt=false;
	bool valide=false;
};

class Comunication {
public:
	Comunication(); // constructeur
	virtual ~Comunication(); //destructeur
    // differente fonction qui permetent d'envoyer un message
	// sans retour a la ligne
	// chaque message est ajouter au crc
	// les fonction sont inline
	void print(const int,const byte);
	void print(const String,const byte);
	void print(const int);
	void print(const String);
	// differente fonction qui permetent d'envoyer un message
	// avec retour a la ligne et envoie du crc
	// les fonctions sont inline
	void println(const int,byte);
	void println(const String,const byte);
	void println(const int);
	void println(const String);

	void eventlecture(); //fonction qui gere les entree du por com pour les metre sous forme de tableau
	bool isLecture(); // y a t'il une lecture valide
	Msg* lecture(); // recuperation d'une lecture valide
protected:
	void ajoutControle(const int); // ajoute le int transmit en parametre au calcul du crc
	void printContole(); // envoie du crc calculer sur le port com
	byte calculControle(const byte msg[NB_MAX_VALEUR],const byte nbByte); // calcul du crc sur le tableau de byte envoyer en parametre msg[NB_MAX_VALEUR],nbByte corespond au nb de byte a recuperer du tableau.

	Msg* serialCourante; // pointeur vers la structure message en cour de traitement.
	Msg* serialGood; // pointeur vers la structure message valide.
	byte crc=0; // crc en cours de calul
    byte retenue=0;// retenue du crc
};

extern Comunication* com; // !!! il faut bien pensser a declarer et initialiser cette variable (de preferance dans le main)



inline void Comunication::print(const int msg, const byte var) {
	print(msg);
	print(var);

}

inline void Comunication::print(const String msg, const byte var) {
	print(msg);
	print(var);
}

inline void Comunication::print(const int msg) {
	ajoutControle(msg); // j'ajoute le msg pour le calul du crc
	Serial.print(msg); // j'envoie le message
	Serial.print(" ");
}

inline void Comunication::print(const String msg) {
	Serial.print(msg);
}

inline void Comunication::println(const int msg, const byte var) {
	print(msg,var);
	printContole();
}

inline void Comunication::println(const String msg,const  byte var) {
	print(msg);
	print(var);
	Serial.println();
}

inline void Comunication::println(const int msg) {
	print(msg);
	printContole();
}

inline void Comunication::println(const String msg) {
	print(msg);
	Serial.println();
}

inline void Comunication::printContole() {
Serial.println(crc); //j'envoie le crc avec un retour chariot
crc=0;
retenue=0;
}

#endif /* COMUNICATION_H_ */
