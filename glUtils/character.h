#ifndef STARGAME_CHARACTER_H
#define STARGAME_CHARACTER_H

#include "../core/shortCalls.h"

struct Character {
    GLuint TextureID;
    vec2 Size,Bearing;
    signed long Advance;
};

#endif //STARGAME_CHARACTER_H
