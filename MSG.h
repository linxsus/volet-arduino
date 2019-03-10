/*
 * MSG.h
 *
 *  Created on: 15 oct. 2018
 *      Author: phenom
 */

#ifndef MSG_H_
#define MSG_H_


#ifdef DEBUG_XG
// message pour debug
#define MSG_TEST "test"
#define MSG_CREATION_COMUNICATION "debug creation Comunication"
#define MSG_DESTRUCTION_COMUNICATION "debug destruction Comunication"
#define MSG_INIT_START "debug init start"
#define MSG_INIT_FIN "debug init ok"
#define MSG_CREATION_SORTIE "debug creation Sortie "
#define MSG_DESTRUCTION_SORTIE  "debug destruction Sortie "
#define MSG_ECRITURE_SORTIE "debug ecriture  Sortie "
#define MSG_CREATION_ENTREE "debug creation Entree avec un nb de 74HC595 :  "
#define MSG_DESTRUCTION_ENTREE  "debug destruction Entree "
#define MSG_CREATION_PROM "debug creation Prom"
#define MSG_DESTRUCTION_PROM "debug destruction Prom "
#define MSG_ECRITURE_ES "debug eciture dans la prom de la ligne "
#define MSG_ECRITURE_ADRESSE "debug eciture dans la prom a l'adresse "

//message important
#define MSG_ACTIVATION_SORTIE "activation  Sortie "
#define MSG_DESACTIVATION_SORTIE "desactivation  Sortie "
#define MSG_LECTURE_SORTIE "lecture  Sortie [numero du 74HC165, valeur du 74HC165] :"
#define MSG_LECTURE_ENTREE "lecture  Entree [numero du 74HC595, valeur du 74HC595] :"
#define MSG_ACTIVATION_ENTREE "activation de l'entree :"
#define MSG_DESACTIVATION_ENTREE "desactivation de l'entree :"
#define MSG_NB_74HC165 "Nombre de 74hc165 :"
#define MSG_NB_74HC595 "Nombre de 74hc595 :"
#define MSG_AFFICHAGE_ES "contenu de la prom [ x x ... ] n° de ligne  crc"
#define MSG_MEMOIRE_RESTANTE "memoire restante  [xx xx crc] "

//message erreur
#define MSG_RESET "reset"
#define MSG_MSG_INCONNUE "message inconnue"
#define MSG_CRC_NOK " le crc n'est pas correcte il devrait etre "


#else
// message pour debug
#define MSG_TEST 3000
#define MSG_CREATION_COMUNICATION 3001
#define MSG_DESTRUCTION_COMUNICATION 3002
#define MSG_INIT_START 3003
#define MSG_INIT_FIN 3004
#define MSG_CREATION_SORTIE 3005
#define MSG_DESTRUCTION_SORTIE  3006
#define MSG_ECRITURE_SORTIE 3007
#define MSG_CREATION_ENTREE 3008
#define MSG_DESTRUCTION_ENTREE  3009
#define MSG_CREATION_PROM 3010
#define MSG_DESTRUCTION_PROM 3011
#define MSG_ECRITURE_ES 3012
#define MSG_ECRITURE_ADRESSE 3013

//message important a partir de 1000
#define MSG_ACTIVATION_SORTIE 1000
#define MSG_DESACTIVATION_SORTIE 1001
#define MSG_LECTURE_SORTIE 1002
#define MSG_LECTURE_ENTREE 1003
#define MSG_ACTIVATION_ENTREE 1004
#define MSG_DESACTIVATION_ENTREE 1005
#define MSG_NB_74HC165 1006
#define MSG_NB_74HC595 1007
#define MSG_AFFICHAGE_ES 1008
#define MSG_MEMOIRE_RESTANTE 1009

//message erreur a partir de 2000
#define MSG_RESET 2000
#define MSG_MSG_INCONNUE 2001
#define MSG_CRC_NOK 2002

#endif

// demande

#define RESET 0
#define LEC_PROM 1
#define LEC_SORTIE 2
#define LEC_ENTREE 3
#define ACTIVATION_SORTIE 4
#define DESACTIVATION_SORTIE 5
#define ECRITURE_PROM 6
#define MEMOIRE_RESTANTE 7



#endif /* MSG_H_ */
