#ifndef SPRITE_H
#define SPRITE_H

int addSprite(const char* name, double x, double y);
void removeSprite(int index);
void setSpritePosition(int index, double x, double y);
void setSpriteSize(int index, double size);
void setSpriteDirection(int index, double direction);
void setSpriteVisible(int index, bool visible);
void renameSprite(int index, const char* newName);

#endif
