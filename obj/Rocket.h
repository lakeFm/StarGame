#ifndef STARGAME_ROCKET_H
#define STARGAME_ROCKET_H

#include "../core/Object.h"
#include "../glUtils/GLD.h"

#define SPEED 2.5f

class Rocket : public Object{
public:
    Rocket() : Object(){
        init();
    }
    Rocket(float a, float b) : Object(a,b){
        init();
    }
    Rocket(float a, float b,float c, float d) : Object(a,b,c,d){
        init();
    }
    Rocket(vec2 p) : Object(p){
        init();
    }
    Rocket(vec2 p, vec2 q) : Object(p,q){
        init();
    }

    void init(){
        Rect rocket;
        rocket.setPos(getX(),getY());
        rocket.setSize(getW(),getH());
        rocket.setColor(vec3(1,1,1));
        this->r = rocket;
        skin(s);
    }

    void skin(int a){

        string p1 = "../assets/img/rocket1.jpg";
        string p2 = "../assets/img/rocket2.jpg";
        string p3 = "../assets/img/rocket3.jpg";
        string p4 = "../assets/img/rocket4.jpg";

        switch(a){
            case 1:   r.loadTexture((char*)p1.c_str());s = 1;break;
            case 2:   r.loadTexture((char*)p2.c_str());s = 2;break;
            case 3:   r.loadTexture((char*)p3.c_str());s = 3;break;
            case 4:   r.loadTexture((char*)p4.c_str());s = 4;break;
            default : r.loadTexture((char*)p1.c_str());s = 1;break;
        }
        this->s = a;

    }

    void draw(float a, float b) override{
        r.draw(a,b);
    }

    void keyMove(int a,float t){
        if(a == 0){ // left
            if(getX() > 20) {
                setX(getX() - SPEED*t);
                r.setPos(getX() - SPEED*t, getY());
            }
        }else{
            if(getX() < 700-getW()) {
                setX(getX() + SPEED*t);
                r.setPos(getX() + SPEED*t,getY());
            }
        }
    }
    void move() override{
        //empty
    }

private:
    Rect r;
    int s;

};

#endif //STARGAME_ROCKET_H
