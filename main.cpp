#include <cstdlib>
#include <cstdio>
#include <vector>
#include "core/shortCalls.h"
#include "glUtils/TextRenderer.h"
#include "glUtils/GLD.h"
#include "obj/Star.h"
#include "obj/Rocket.h"
#include "obj/Asteroid.h"
#include "core/Saver.h"
#include "obj/Bullet.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


#define DIFF 20

enum MODE{
    MENU,
    HELP,
    GAME
};

MODE state = MENU;
std::string font((char*)"../assets/connection.otf");
float Gs = 1.0f;
int score = 0;
int width, height;
float dt,lt;
int bul = 0;
float blt;
int skin = 1;

string hTable(int i, int ii) {
    stringstream  ss;
    ss << i << " -> " << ii << " ";
    ret ss.str();
}

void init(vector<Asteroid> *ast){
    ast->clear();
    ast->reserve(DIFF);
    for(int a = 0; a < DIFF; a++)
        ast->emplace_back();

    for(auto & astr : *ast) {
        auto b = 20;
        astr = Asteroid(rand()%width,rand()%height,b,b);
        astr.setS(vec2(0.0f, -Gs));
    }
}

int main(int argc, char *argv[]){
    GLFWwindow* window;
    srand(time(nullptr));
    if( !glfwInit() ){
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow( 720, 480, "StarGame", nullptr, nullptr );
    if (!window){
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    glfwMakeContextCurrent(window);
    glewInit();
    glfwSwapInterval( 1 );

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glEnable(GL_MULTISAMPLE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwGetFramebufferSize(window, &width, &height);
    glViewport( 0, 0, (GLuint) width, (GLuint) height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0,width,0,height,-1,1);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    TextRenderer r(font,vec2(width,height));
    Rocket rt(width - 200,  height - 300,64,128);
    Star stars[15];
    vector<Asteroid> astrs;
    Bullet* bullet[5];

    for(int a = 0;a < 5;a++){
        bullet[a] = nullptr;
    }

    for(auto &star : stars) {
        auto b = (float)(rand() % 8);
        star = Star(rand() % width,rand() % height,b,b);
        star.setS(vec2(0.0f, -(float)(rand()%4 + 1)));
    }

    while( !glfwWindowShouldClose(window) ) {

        auto time = (float)glfwGetTime();
        dt = time - lt;
        lt = dt;

        if(state == MODE::GAME) {
            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
                rt.keyMove(0,1);
            }

            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
                if(blt+0.3 < glfwGetTime()) {
                    bullet[bul] = new Bullet(rt.getX() + rt.getW() / 2.0f, rt.getY() + rt.getH() - 10);
                    if(bul > 4)
                        bul=0;
                    else
                        bul++;

                    blt = glfwGetTime();
                }
            }

            if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                rt.keyMove(1,1);
            }

            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                state = MODE::MENU;
                score = 0;
                Gs = 1;
                astrs.clear();
                for(int a = 0; a < 5 ;a ++)bullet[a] = nullptr;
            }
        }
        if(state == MODE::MENU) {
            if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
                init(&astrs);
                state = MODE::GAME;
                rt.setSize(32,64);
                rt.setPos(width/2 - 20.0f,50);
            }

            if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
                state = MODE::HELP;
            }

            if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
                glfwSetWindowShouldClose(window,1);
            }

            if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
                skin = 1;

            }
            if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
                skin = 2;
            }
            if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
                skin = 3;
            }
            if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
                skin = 4;
            }

            rt.skin(skin);
            rt.init();

        }
        if(state == MODE::HELP) {
            if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
                state = MODE::MENU;
            }
        }
        if(state == MODE::GAME){
            score+=(int)Gs;
              Gs = (score <   100)? 1.0f
            :(score <=  500)? 1.2f
            :(score <= 1500)? 1.4f
            :(score <= 2500)? 1.6f
            :(score <= 3500)? 1.8f
            :(score <= 4500)? 2.0f
            :(score <= 6000)? 2.4f
            :(score <= 7000)? 2.8f
            :(score <= 8000)? 3.2f
            :(score <= 9000)? 3.6f
            :(score <= 10000)? 4.0f
            : 5.0f;
            //printf("Speed -> %.2f\n",Gs);
        }

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        if(state == MODE::GAME){

            for (auto &astr : astrs) {
                for (int c = 0; c < 5;c++)
                    if (bullet[c] != nullptr) {
                        if (astr.colide(vec4(bullet[c]->getX(), bullet[c]->getY(), bullet[c]->getW(), bullet[c]->getH()))) {
                            astr.setPos((float) (rand() % width), height + 20);
                            astr.kill();
                            astr.setSY(-Gs);
                            bullet[c] = nullptr;
                        }
                    }
                }

            for (auto &star : stars)
                star.draw((float) width, (float) height);

            for (auto &astr : astrs) {
                astr.draw((float) width, (float) height);
                if(astr.colide(vec4(rt.getX(),rt.getY(),rt.getW(),rt.getH()))  ){
                    state = MODE::MENU;
                    save(score);
                    score = 0;
                    Gs = 1;
                    astrs.clear();
                    rt.setPos(width/2 - 20.0f,50);
                    for(int a = 0;a < 5;a++)bullet[a] = nullptr;
                }
            }
            for(int a = 0;a < 5;a++)
                if(bullet[a] != nullptr)
                    bullet[a]->draw((float) width, (float) height);


            rt.draw((float) width, (float) height);

            r.draw("Score : " + to_string(score), 0, height - 20, 20, vec3(1.0f, 1.0f, 1.0f));
        }

        if(state == MODE::MENU){
            r.draw("StarGame",              width/3.5, height - height/4, 64, vec3(1.0f, 1.0f, 1.0f));
            r.draw("Press Enter to start" , width-320,   10, 32, vec3(1.0f, 1.0f, 1.0f));
            r.draw("Press Q to quit" ,      10,   10, 28, vec3(1.0f, 1.0f, 1.0f));

            vector<int> H = getScore();
            rt.setPos(width - 200,  height - 300);
            rt.setSize(64,128);
            rt.skin(skin);
            rt.draw(width,height);
            r.draw("Skin" ,      width - 200,  height - height/3, 28, vec3(1.0f, 1.0f, 1.0f));

            r.draw("HighScores" ,      width/3-100,  height - height/3, 28, vec3(1.0f, 1.0f, 1.0f));
            for(int a = 0; a < 5;a++){
                r.draw( hTable(a+1,H[a]) ,      width/3-100,   height - height/2.5 -(30*a), 28, vec3(1.0f, 1.0f, 1.0f));
            }
        }

        if(state == MODE::HELP){
            r.draw("HELP",                                    width/3 - 20, height - 80, 64, vec3(1.0f, 1.0f, 1.0f));
            r.draw("In Game : " ,                             width/10,   height - (150 + 100), 28, vec3(1.0f, 1.0f, 1.0f));
            r.draw("Use < and > to manipulate rocket" ,       width/10,   height - (150 + 130), 32, vec3(1.0f, 1.0f, 1.0f));
            r.draw("Press Esc to Pause/Enter the Main Menu" , width/10,   height - (150 + 160), 28, vec3(1.0f, 1.0f, 1.0f));
            r.draw("Press Space to shoot" ,                   width/10,   height - (150 + 190), 28, vec3(1.0f, 1.0f, 1.0f));
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        if(state == MODE::GAME) {

            for (auto &star : stars) {
                if (star.getY() < -10) {
                    star.setPos(rand() % width, height + 20);
                    int b = rand() % 15;
                    star.setSize(b, b);
                    star.setS(vec2(0.0f, -(float) (rand() % 4 + 1)));
                } else {
                    star.move();
                }
            }

            for(int a = 0;a < 5;a++) {
                if (bullet[a] != nullptr) {
                    if (bullet[a]->getY() < height + 10) {
                        bullet[a]->setSY(2.5f);
                        bullet[a]->move();
                    }
                }
            }

            for (auto &astr : astrs) {
                if (astr.getY() < -10) {
                    astr.setPos((float) (rand() % width), height + 20);
                    astr.setSY(-Gs);
                    astr.kill();
                } else {
                    astr.move();
                }
            }
        }
    }
    glfwTerminate();
    exit( EXIT_SUCCESS );
}
