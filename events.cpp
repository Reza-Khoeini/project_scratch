#include "events.h"
#include "globals.h"
#include "sound.h"
#include <cstdio>
#include <cstring>

void triggerGreenFlag(void) {
    gGreenFlagPressed = true;
    gProgramRunning = true;
    printf("Green Flag triggered - Program started\n");
}

void triggerStopAll(void) {
    gProgramRunning = false;
    gGreenFlagPressed = false;
    stopAllSounds();
    printf("Program stopped\n");
}

void broadcastMessage(const char* message) {
    strncpy(gLastBroadcast, message, MAX_NAME_LEN - 1);
    gLastBroadcast[MAX_NAME_LEN - 1] = '\0';
    printf("Broadcast: %s\n", message);
}

bool checkEvent(Event* event) {
    switch (event->type) {
        case EVENT_GREEN_FLAG:
            if (gGreenFlagPressed) {
                gGreenFlagPressed = false;
                return true;
            }
            return false;
        case EVENT_KEY_PRESSED:
            return gLastKeyPressed == event->keyCode;
        case EVENT_BROADCAST_RECEIVED:
            return strcmp(gLastBroadcast, event->broadcastName) == 0;
        default:
            return false;
    }
}

void clearEvents(void) {
    gLastKeyPressed = '\0';
    memset(gLastBroadcast, 0, MAX_NAME_LEN);
}
