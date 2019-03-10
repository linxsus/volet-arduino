/*
 * general.h
 *
 *  Created on: 22 août 2018
 *      Author: phenom
 */

#ifndef GENERAL_H_
#define GENERAL_H_
#include "Arduino.h"
#include <EEPROM.h>
#include "AddProm.h"

#define SERIAL_BAUD 9600 //vitesse de comunication
#define NB_MAX_VALEUR 12 //nb de byte valide par ligne

extern bool reset; // un passage a true va reseter les differents object

#endif /* GENERAL_H_ */
