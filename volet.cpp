#include "general.h"
#include "GestionVolet.h"
#include "Comunication.h"
#include "GestionLed.h"
#include <avr/wdt.h>

GestionVolet* volet;
bool reset=false;

void setup()
{
	volet=new GestionVolet;
	wdt_enable(WDTO_500MS); // temps maximum d'une execution d'un loop avant de lancer un reset.(watchdog)
}


void loop()
{
volet->run();
wdt_reset();
if(reset){
	com->println(MSG_RESET);
	delay (1000); // utilisation du watchdog la valeur doit etre superieur a la valeur du watchdog
}
}



