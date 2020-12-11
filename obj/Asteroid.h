#ifndef AsteroidGAME_ASTEROID_H
#define AsteroidGAME_ASTEROID_H

#include "../core/Object.h"
#include "../glUtils/GLD.h"

class Asteroid : public Object{

public:
    Asteroid() : Object(){
        init();
    }
    Asteroid(float a, float b) : Object(a,b){
        init();
    }
    Asteroid(float a, float b,float c, float d) : Object(a,b,c,d){
        init();
    }
    Asteroid(vec2 q) : Object(q){
        init();
    }
    Asteroid(vec2 q,vec2 v) : Object(q,v){
        init();
    }

    void init(){
        this->n = 0;
        this->r.setPos(getX(),getY());
        this->r.setSize(getW(),getH());
        this->r.setColor(vec3(1,1,1));
        kill();
    }

    void draw(float a, float b) override{
        r.draw(a,b);
    }

    void move() override{
        setPos(getX() + getSX(),getY() + getSY());
        r.setPos(getX() + getSX(),getY() + getSY());
    }

    void kill(){

        switch(n){
            case 0:   r.loadTexture((char*)"../assets/img/astr1.jpg");break;
            case 1:   r.loadTexture((char*)"../assets/img/astr2.jpg");break;
            case 2:   r.loadTexture((char*)"../assets/img/astr3.jpg");break;
            case 3:   r.loadTexture((char*)"../assets/img/astr4.jpg");break;
           // default : r.loadTexture((char*)"../assets/img/astr.jpg");
        }

        if(n < 4) {
            int q = n + 1;
            this->n = q;
        }else{
            this->n = 0;
        }
    }
    
    bool colide(vec4 rect1){
        if (rect1.x < this->getX() + this->getW() &&
            rect1.x + rect1.z > this->getX() &&
            rect1.y < this->getY() + this->getH() &&
            rect1.y + rect1.w > this->getY()) {
            return true;
        }
        return false;
    }
private:
    Rect r;
    int n ;

};

#endif //AsteroidGAME_ASTEROID_H
