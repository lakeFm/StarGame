#ifndef STARGAME_STAR_H
#define STARGAME_STAR_H

#include "../core/Object.h"
#include "../glUtils/GLD.h"

class Star : public Object{

public:
    Star() : Object(){
        init();
    }
    Star(float a, float b) : Object(a,b){
        init();
    }
    Star(float a, float b,float c, float d) : Object(a,b,c,d){
        init();
    }
    Star(vec2 q) : Object(q){
        init();
    }
    Star(vec2 q,vec2 v) : Object(q,v){
        init();
    }

    void init(){
        Rect star;
        star.setPos(getX(),getY());
        star.setSize(getW(),getH());
        star.setColor(vec3(1,1,1));
        star.loadTexture((char*)"../assets/img/star.jpg");
        r = star;
    }

    void draw(float a, float b) override{
        r.draw(a,b);
    }

    void move() override{
        setPos(getX() + getSX(),getY() + getSY());
        r.setPos(getX() + getSX(),getY() + getSY());
    }
private:
    Rect r;

};

#endif //STARGAME_STAR_H
