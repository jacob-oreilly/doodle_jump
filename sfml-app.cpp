#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

struct point
{
    int x, y;
};

const int player_w = 16;
const int player_h = 16;
const int platform_w = 32;
const int platform_h = 8;

int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(300, 600), "Doodle game!");
    app.setFramerateLimit(60);

    Texture t1, t2, t3;
    t1.loadFromFile("./tmpplayer.png");
    t2.loadFromFile("./plat.png");

    Sprite sPlayer(t1), sPlat(t2);

    point plat[20];

    for (int i = 0; i < 10; i++) {
        plat[i].x = (rand() % 300);
        plat[i].y = (rand() % 600);
    }

    int x=100, y=550, h=75;
    float dx=0, dy=0;
    bool firstBounce = true;


    while(app.isOpen()) {
        Event e;
        while(app.pollEvent(e)) {
            if (e.type == Event::Closed) {
                app.close();
            }
        }
        app.clear();

        //Restart
        if (Keyboard::isKeyPressed(Keyboard::R)) {
            firstBounce = true;
            x = 100;
            y = 550;
            dy += 0.5;
            for (int i = 0; i < 10; i++) {
                plat[i].x = (rand() % 300);
                plat[i].y = (rand() % 600);
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Q)) {
            app.close();
        }

        

        if (Keyboard::isKeyPressed(Keyboard::Right) && x < 284) x+=8;
        if (Keyboard::isKeyPressed(Keyboard::Left) && x > 0) x-=8;
        if (Keyboard::isKeyPressed(Keyboard::D) && x < 284) x+=8;
        if (Keyboard::isKeyPressed(Keyboard::A) && x > 0) x-=8;
        dy += 0.5;
        y += dy;
        if(y > 600 && firstBounce) {
            dy = -15;
            firstBounce = false;
        }
        sPlayer.setPosition(x, y);
        app.draw(sPlayer);
        for (int i = 0; i < 10; i++) {
            sPlat.setPosition(plat[i].x, plat[i].y);
            
            app.draw(sPlat);
            if (sPlayer.getPosition().x + player_w >= plat[i].x &&
                sPlayer.getPosition().x <= plat[i].x + platform_w &&
                sPlayer.getPosition().y + player_h >= plat[i].y &&
                sPlayer.getPosition().y <= plat[i].y + platform_h) {
                    dy = -15; 
            }
            if (sPlayer.getPosition().y <= h) {
                        plat[i].y += h;
                        y += h;
            }
        }
        
        app.display();
    }
    return 0;
}