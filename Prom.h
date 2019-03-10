/*
 * Prom.h
 *
 *  Created on: 13 oct. 2018
 *      Author: phenom
 */

#ifndef PROM_H_
#define PROM_H_

#include "AddProm.h"
#include "general.h"

class Prom {
public:
	Prom();
	virtual ~Prom();
	void ecriture(byte,const byte[NB_BYTE_LIGNE]);
	void ecriture(byte,const byte);
	void lecture();
};

#endif /* PROM_H_ */
