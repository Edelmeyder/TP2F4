#ifndef _PEW_H
#define _PEW_H

#define PEW_PIN D6  // Sounder pin

void PEW_init(void); // Initializes souder pin
void PEW_pew(void);  // Beeps 100 ms
void PEW_all_ok(void); //if its sounds the system is ready and all is good

#endif
