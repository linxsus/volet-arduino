/*
 * Led.h
 *
 *  Created on: 26 oct. 2018
 *      Author: phenom
 */

#ifndef LED_H_
#define LED_H_

#include "Sortie.h"

class Led: public Sortie {
public:
	Led();
	virtual ~Led();
	void activer(byte relais); // activation du relais passer en parametre
	void desactiver(byte relais);// desactivation du relais passer en parametre

};

#endif /* LED_H_ */
