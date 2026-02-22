#include "sound.h"
#include "globals.h"
#include <SDL2/SDL.h>
#include <cstdio>
#include <cstring>

int addSound(const char* name, const char* filepath) {
    if (gProject.soundCount >= MAX_SOUNDS) {
        printf("Error: Maximum sound count reached\n");
        return -1;
    }
    
    int idx = gProject.soundCount;
    Sound* snd = &gProject.sounds[idx];
    
    strncpy(snd->name, name, MAX_NAME_LEN - 1);
    snd->name[MAX_NAME_LEN - 1] = '\0';
    snd->volume = 100;
    snd->muted = false;
    snd->active = true;
    snd->chunk = NULL;
    
    if (filepath && filepath[0] != '\0') {
        snd->chunk = Mix_LoadWAV(filepath);
        if (!snd->chunk) {
            printf("Warning: Could not load sound '%s': %s\n", filepath, Mix_GetError());
        }
    }
    
    gProject.soundCount++;
    printf("Sound '%s' added\n", name);
    return idx;
}

void removeSound(int index) {
    if (index < 0 || index >= gProject.soundCount) return;
    
    if (gProject.sounds[index].chunk) {
        Mix_FreeChunk(gProject.sounds[index].chunk);
    }
    
    printf("Sound '%s' removed\n", gProject.sounds[index].name);
    
    for (int i = index; i < gProject.soundCount - 1; i++) {
        gProject.sounds[i] = gProject.sounds[i + 1];
    }
    gProject.soundCount--;
}

void playSound(int index) {
    if (index < 0 || index >= gProject.soundCount) return;
    Sound* snd = &gProject.sounds[index];
    
    if (snd->muted || !snd->chunk) return;
    
    int effectiveVolume = (snd->volume * gMasterVolume) / 100;
    Mix_VolumeChunk(snd->chunk, (effectiveVolume * MIX_MAX_VOLUME) / 100);
    Mix_PlayChannel(-1, snd->chunk, 0);
    printf("Playing sound '%s'\n", snd->name);
}

void playSoundUntilDone(int index) {
    if (index < 0 || index >= gProject.soundCount) return;
    Sound* snd = &gProject.sounds[index];
    
    if (snd->muted || !snd->chunk) return;
    
    int effectiveVolume = (snd->volume * gMasterVolume) / 100;
    Mix_VolumeChunk(snd->chunk, (effectiveVolume * MIX_MAX_VOLUME) / 100);
    int channel = Mix_PlayChannel(-1, snd->chunk, 0);
    
    if (channel >= 0) {
        while (Mix_Playing(channel)) {
            SDL_Delay(10);
        }
    }
}

void stopAllSounds(void) {
    Mix_HaltChannel(-1);
    printf("All sounds stopped\n");
}

void setSoundVolume(int index, int volume) {
    if (index < 0 || index >= gProject.soundCount) return;
    if (volume < 0) volume = 0;
    if (volume > 100) volume = 100;
    gProject.sounds[index].volume = volume;
}

void changeSoundVolume(int index, int delta) {
    if (index < 0 || index >= gProject.soundCount) return;
    int newVol = gProject.sounds[index].volume + delta;
    setSoundVolume(index, newVol);
}

void setMasterVolume(int volume) {
    if (volume < 0) volume = 0;
    if (volume > 100) volume = 100;
    gMasterVolume = volume;
}

void muteSound(int index, bool mute) {
    if (index < 0 || index >= gProject.soundCount) return;
    gProject.sounds[index].muted = mute;
}

void cleanupSounds(void) {
    for (int i = 0; i < gProject.soundCount; i++) {
        if (gProject.sounds[i].chunk) {
            Mix_FreeChunk(gProject.sounds[i].chunk);
            gProject.sounds[i].chunk = NULL;
        }
    }
}
