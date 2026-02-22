#include "project.h"
#include "globals.h"
#include "sound.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>

void initProject(void) {
    memset(&gProject, 0, sizeof(ProjectState));
    strcpy(gProject.projectName, "NewProject");
    gProject.spriteCount = 0;
    gProject.soundCount = 0;
}

bool saveProject(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Cannot save to file %s\n", filename);
        return false;
    }
    
    fprintf(file, "PROJECT|%s\n", gProject.projectName);
    fprintf(file, "SPRITE_COUNT|%d\n", gProject.spriteCount);
    
    for (int i = 0; i < gProject.spriteCount; i++) {
        Sprite* s = &gProject.sprites[i];
        fprintf(file, "SPRITE|%s|%.2f|%.2f|%.2f|%.2f|%d\n",
                s->name, s->x, s->y, s->direction, s->size, s->visible ? 1 : 0);
    }
    
    fprintf(file, "SOUND_COUNT|%d\n", gProject.soundCount);
    for (int i = 0; i < gProject.soundCount; i++) {
        Sound* snd = &gProject.sounds[i];
        fprintf(file, "SOUND|%s|%d|%d\n", snd->name, snd->volume, snd->muted ? 1 : 0);
    }
    
    fclose(file);
    printf("Project saved to %s\n", filename);
    return true;
}

bool loadProject(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot load file %s\n", filename);
        return false;
    }
    
    initProject();
    
    char line[256];
    int spriteIdx = 0;
    int soundIdx = 0;
    
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, "|");
        if (!token) continue;
        
        if (strcmp(token, "PROJECT") == 0) {
            token = strtok(NULL, "|\n");
            if (token) strncpy(gProject.projectName, token, MAX_NAME_LEN - 1);
        }
        else if (strcmp(token, "SPRITE_COUNT") == 0) {
            token = strtok(NULL, "|\n");
            if (token) gProject.spriteCount = atoi(token);
        }
        else if (strcmp(token, "SPRITE") == 0) {
            if (spriteIdx < MAX_SPRITES) {
                Sprite* s = &gProject.sprites[spriteIdx];
                s->active = true;
                
                token = strtok(NULL, "|");
                if (token) strncpy(s->name, token, MAX_NAME_LEN - 1);
                
                token = strtok(NULL, "|");
                if (token) s->x = atof(token);
                
                token = strtok(NULL, "|");
                if (token) s->y = atof(token);
                
                token = strtok(NULL, "|");
                if (token) s->direction = atof(token);
                
                token = strtok(NULL, "|");
                if (token) s->size = atof(token);
                
                token = strtok(NULL, "|\n");
                if (token) s->visible = atoi(token) == 1;
                
                spriteIdx++;
            }
        }
        else if (strcmp(token, "SOUND_COUNT") == 0) {
            token = strtok(NULL, "|\n");
            if (token) gProject.soundCount = atoi(token);
        }
        else if (strcmp(token, "SOUND") == 0) {
            if (soundIdx < MAX_SOUNDS) {
                Sound* snd = &gProject.sounds[soundIdx];
                snd->active = true;
                
                token = strtok(NULL, "|");
                if (token) strncpy(snd->name, token, MAX_NAME_LEN - 1);
                
                token = strtok(NULL, "|");
                if (token) snd->volume = atoi(token);
                
                token = strtok(NULL, "|\n");
                if (token) snd->muted = atoi(token) == 1;
                
                soundIdx++;
            }
        }
    }
    
    fclose(file);
    printf("Project loaded from %s\n", filename);
    return true;
}

void newProject(void) {
    cleanupSounds();
    initProject();
    printf("New project created\n");
}
