#ifndef _PEW_H
#define _PEW_H

#define PEW_PIN D6  // Sounder pin

/// Inicializa el pin del sounder
void PEW_init(void);
/// Beep 100 ms
void PEW_pew(void);
/// Suena para indicar que el sistema inició correctamente
void PEW_all_ok(void);

#endif
