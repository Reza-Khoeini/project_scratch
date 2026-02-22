#ifndef SOUND_H
#define SOUND_H

int addSound(const char* name, const char* filepath);
void removeSound(int index);
void playSound(int index);
void playSoundUntilDone(int index);
void stopAllSounds(void);
void setSoundVolume(int index, int volume);
void changeSoundVolume(int index, int delta);
void setMasterVolume(int volume);
void muteSound(int index, bool mute);
void cleanupSounds(void);

#endif
