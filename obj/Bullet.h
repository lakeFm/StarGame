#ifndef STARGAME_BULLET_H
#define STARGAME_BULLET_H

#include "../core/Object.h"
#include "../glUtils/GLD.h"

class Bullet : public Object{

public:
    Bullet() : Object(){
        init();
    }
    Bullet(float a, float b) : Object(a,b){
        init();
    }
    Bullet(float a, float b,float c, float d) : Object(a,b,c,d){
        init();
    }
    Bullet(vec2 q) : Object(q){
        init();
    }
    Bullet(vec2 q,vec2 v) : Object(q,v){
        init();
    }

    void init(){
        Rect star;
        star.setPos(getX(),getY());
        star.setSize(4,8);
        star.setColor(vec3(1,1,1));
        star.loadTexture((char*)"../assets/img/bullet.jpg");
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

#endif //STARGAME_BULLET_H
