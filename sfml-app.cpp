#include <SFML/Graphics.hpp>
#include <time.h>
#include <string>
using namespace std;
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

    int score = 0;

    Sprite sPlayer(t1), sPlat(t2);

    point plat[20];

    sf::Font font;
    if (!font.loadFromFile("Roboto-Medium.ttf"))
        return EXIT_FAILURE;
    sf::Text scoreText(to_string(score), font, 25);
    scoreText.setPosition(20.0, 20.0);

    for (int i = 0; i < 10; i++) {
        plat[i].x = (rand() % 400);
        plat[i].y = (rand() % 600);
    }

    int x=100, y=550, h=300;
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
                plat[i].x = (rand() % 400);
                plat[i].y = (rand() % 600);
            }
            score = 0;
            scoreText.setString(to_string(score));
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

        if(y<h) {
            for(int i = 0; i < 10; i++) {
                y = h;
                plat[i].y=plat[i].y-dy;
                if (plat[i].y>600) {
                    plat[i].y=0;
                    plat[i].x=rand() % 400;
                }
            }
        }

        for (int i = 0; i < 10; i++) {
            sPlat.setPosition(plat[i].x, plat[i].y);
            app.draw(sPlat);
            if (sPlayer.getPosition().x + player_w >= plat[i].x &&
                sPlayer.getPosition().x <= plat[i].x + platform_w &&
                sPlayer.getPosition().y + player_h >= plat[i].y &&
                sPlayer.getPosition().y <= plat[i].y + platform_h) {
                    dy = -15; 
                    score += 1; 
                    scoreText.setString(to_string(score));
                    
            }
           
        }
        app.draw(scoreText);
        app.display();
    }
    return 0;
}