#ifndef STARGAME_OBJECT_H
#define STARGAME_OBJECT_H

#include "shortCalls.h"

class Object{
public:

    Object(){
        this->setPos (0.0f,0.0f);
        this->setSize(0.0f,0.0f);
    }

    Object(float x,float y){
        this->setPos (x,y);
        this->setSize(0.0f,0.0f);
    }

    Object(float x,float y,float w,float h){
        this->setPos (x,y);
        this->setSize(w,h);
    }

    Object(vec2 p){
        this->setPos (p.x,p.y);
        this->setSize(0.0f,0.0f);
    }

    Object(vec2 p,vec2 s){
        this->setPos (p.x,p.y);
        this->setSize(s.x,s.y);
    }

    vfun draw(float a, float b) = 0;
    vfun move() = 0;

    fun setX(float x){this->X = x;}
    fun setY(float y){this->Y = y;}
    fun setW(float w){this->W = w;}
    fun setH(float h){this->H = h;}
    fun setPos  (float x,float y){setX(x);setY(y);}
    fun setSize (float w,float h){setW(w);setH(h);}
    fun setPos  (vec2 p){setX(p.x);setY(p.y);}
    fun setSize (vec2 s){setW(s.x);setH(s.y);}

    float getX(){ret X;}
    float getY(){ret Y;}
    float getW(){ret W;}
    float getH(){ret H;}

    vec2 getSize(){ret vec2(getX(),getY());}
    vec2 getPos(){ret vec2(getW(),getH());}

    float getX()C{ret X;}
    float getY()C{ret Y;}
    float getW()C{ret W;}
    float getH()C{ret H;}

    vec2 getSize()C{ret vec2(getX(),getY());}
    vec2 getPos() C{ret vec2(getW(),getH());}

    float getSX(){ret speedX;}
    float getSY(){ret speedY;}
    float getSX()C{ret speedX;}
    float getSY()C{ret speedY;}

    fun setSX(float x){this->speedX = x;}
    fun setSY(float y){this->speedY = y;}
    fun setS(vec2 sp){setSX(sp.x);setSY(sp.y);}

    vec2 getS(){ret vec2(getSX(),getSY());}
    vec2 getS()C{ret vec2(getSX(),getSY());}


private:
    float X,Y,W,H;
    float speedX,speedY;
};

#endif //STARGAME_OBJECT_H
