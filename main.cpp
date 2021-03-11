#include <SFML/Graphics.hpp>
#include "Collision.hpp"
#include <vector>
#include <string.h>
using namespace sf;
int main() {
    RenderWindow window(VideoMode(600,900),"KnifeHit++");
    
    std::string a = "/Users/dodepep/Library/Developer/Xcode/DerivedData/KnifeHit++-dhpgajyldhwjuwabuvjcdhdohxcp/Build/Products/Debug/assets";
    Texture t1,t2;
    t1.loadFromFile(a + "/knife.png");
    t2.loadFromFile(a + "/log.png");
    Sprite log,knife,s;
    float speed = 5.0f;
    Font font;
    Text text;
    bool lose = false;
    Image icon;
    /////// Sprite Configuration ///////
    log.setTexture(t2);
    knife.setTexture(t1);
    knife.setOrigin(200, 200);
    log.setOrigin(317/2, 311/2);
    log.setPosition(300, 250);
    knife.setPosition(300, 700);
    knife.setScale(0.7f, 0.7f);
    s.setTexture(t1);
    s.setPosition(10000, 10000);
    font.loadFromFile(a + "/font.ttf");
    text.setFont(font);
    text.setString("Play Again?");
    text.setPosition(180, 200);
    //text.setColor(Color::Black);
    //icon.loadFromFile("assets/icon.png");
    //window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    std::vector<Sprite> objs;
    objs.push_back(s);
    window.setFramerateLimit(30);
    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e)) {
            if(e.type == Event::Closed) {
                window.close();
            }
            if(e.type == Event::KeyPressed)
            {
                if(Keyboard::isKeyPressed(Keyboard::Space)) {
                    Sprite Nknife;
                    Nknife.setTexture(t1);
                    Nknife.setOrigin(200, -50);
                    Nknife.setScale(0.7f, 0.7f);
                    Nknife.setPosition(300, 250);
                    //Nknife.setRotation(-45);
                    objs.push_back(Nknife);
                }
                if(lose && Keyboard::isKeyPressed(Keyboard::Space)) {
                    lose = false;
                    objs.clear();
                    speed = 5;
                }
            }
        }
        // throw new knife when space key is pressed
        
        for(int i=0;i<objs.size();i++) {
            for(int j=0;j<objs.size();j++) {
                if (Collision::PixelPerfectTest(objs[i], objs[j]) && i != j) {
                    speed = 0;
                    lose = true;
                }
            }
        }
        
        
        log.rotate(speed);
        window.clear(Color(150,200,150));
        window.draw(knife);
        for(int i=0;i<objs.size();i++) {
            objs[i].rotate(speed);
            window.draw(objs[i]);
        }
        window.draw(log);
        if(lose) {
            window.draw(text);
        }
        window.display();
    }
    return 0;
}
