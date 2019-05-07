#include <ace/generic/main.h>
#include <ace/managers/key.h>
#include <ace/managers/joy.h>
#include "hyperx.h"


void genericCreate(void) {
  // Here goes your startup code
  logWrite("Hello, Amiga!\n");
  keyCreate(); // We'll use keyboard
  logWrite("Keyboard initialized");
  joyOpen(0);
  logWrite("Joy 0 initialized");
  gamePushState(gameGsCreate, gameGsLoop, gameGsDestroy);
}

void genericProcess(void) {
  // Here goes code done each game frame
  // Nothing here right now
  keyProcess();
  joyProcess();
  gameProcess();
}

void genericDestroy(void) {
  // Here goes your cleanup code
  keyDestroy();
  joyClose();
  logWrite("Goodbye, Amiga!\n");
}
