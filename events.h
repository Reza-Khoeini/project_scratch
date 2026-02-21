#ifndef EVENTS_H
#define EVENTS_H

#include "types.h"

void triggerGreenFlag(void);
void triggerStopAll(void);
void broadcastMessage(const char* message);
bool checkEvent(Event* event);
void clearEvents(void);

#endif
