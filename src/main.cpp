#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#define XW 800
#define YW 600

typedef unsigned char u_int8_t;
typedef unsigned short u_int16_t;
typedef unsigned int u_int32_t;

int main(int argc, char *argv[])
{
    // Variablen
    u_int8_t grayrasterbar[256];

    float sintab[1024];
    float costab[1024];

    u_int32_t counter1start = 0;
    u_int32_t frequcounter1 = 0;

    u_int32_t counter2start = 0;
    u_int32_t frequcounter2 = 0;

    u_int32_t counter3start = 0;
    u_int32_t frequcounter3 = 0;

    u_int32_t counter4start = 0;
    u_int32_t frequcounter4 = 0;

    u_int32_t counter5start = 0;
    u_int32_t frequcounter5 = 0;

    u_int32_t counter6start = 0;
    u_int32_t frequcounter6 = 0;

    // Gray Rasterbar erstellen
    grayrasterbar[128];

    for(int i=0; i<128; i++)
    {
        static u_int8_t gray = 0xff;

        grayrasterbar[128 + i] = gray;
        grayrasterbar[128 - i] = gray;

        gray -= 2;
    }

    // SIN und COS Tabellen erstellen
    for(int i=0; i<1024; i++)
    {
        costab[i] = cos(i*M_PI*2*(1.0/1024));
        sintab[i] = sin(i*M_PI*2*(1.0/1024));
    }

    cout << "SFML Demo" << endl;

    // Window Open
    sf::RenderWindow window(sf::VideoMode(XW,YW,32),"Demo SFML");

    // Font erstellen
    sf::Font font1;
    font1.loadFromFile("./data/arial.ttf");

    // Text erstellen
    sf::Text text1("Test1",font1);
    text1.setCharacterSize(16);

    // Clock
    sf::Clock clock;

    // Texture erstellen
    sf::Texture texture1;
    texture1.setSmooth(true);
    texture1.create(XW,YW);

    // Pixelpuffer erstellen
    unsigned char* pixelbuffer1 = new unsigned char[XW * YW * 4];

    // Sprite erstellen
    sf::Sprite sprite1;
    sprite1.setPosition(0,0);
    sprite1.setTexture(texture1);

    while (window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // Bildschirm löschen
        window.clear();


        u_int32_t* buffer = (u_int32_t*) pixelbuffer1;
        for(int i=0; i<XW*YW; i++)
            buffer[i] = 0;

        frequcounter1 = counter1start;
        frequcounter2 = counter2start;
        frequcounter3 = counter3start;
        frequcounter4 = counter4start;
        frequcounter5 = counter5start;
        frequcounter6 = counter6start;

        for(int x=0; x<XW; x++)
        {
            int ypos, buffer_pos;

            ypos = YW/2-128;
            ypos += sintab[frequcounter1&0x3ff]*costab[frequcounter2&0x3ff]*120;
            buffer_pos = ypos*XW+x;
            for(int y=0; y<256; y++)
            {
                buffer[buffer_pos] = grayrasterbar[y] | 0xff000000;
                buffer_pos += XW;
            }

            ypos = YW/2-128;
            ypos += sintab[frequcounter3&0x3ff]*sintab[frequcounter4&0x3ff]*130;
            buffer_pos = ypos*XW+x;
            for(int y=0; y<256; y++)
            {
                buffer[buffer_pos] |= (grayrasterbar[y]<<8 | 0xff000000);
                buffer_pos += XW;
            }

            ypos = YW/2-128;
            ypos += costab[frequcounter5&0x3ff]*sintab[frequcounter6&0x3ff]*140;
            buffer_pos = ypos*XW+x;
            for(int y=0; y<256; y++)
            {
                buffer[buffer_pos] |= (grayrasterbar[y]<<16 | 0xff000000);
                buffer_pos += XW;
            }


            frequcounter1 += 10;
            frequcounter2 += 4;

            frequcounter3 += 6;
            frequcounter4 += 12;

            frequcounter5 += 2;
            frequcounter6 += 10;


            /*
            frequcounter1 += 3;
            frequcounter2 += 1;

            frequcounter3 += 1;
            frequcounter4 += 2;

            frequcounter5 += 3;
            frequcounter6 += 1;
            */
        }

        static int c1 = 0;



        c1++;
        if(c1 == 5)
        {
            c1=0;
            counter1start += 3;
            counter2start += 10;
            counter3start -= 5;
            counter4start += 14;
            counter5start += 8;
            counter6start += 12;
        }

        // Bitmap darstellen
        texture1.update(pixelbuffer1);
        window.draw(sprite1);

        // FPS anzeigen
        sf::Time time1 = time1 = clock.restart();
        char tmp[10];
        sprintf(tmp,"%dfps",int(1000000/time1.asMicroseconds()));
        text1.setString(tmp);
        window.draw(text1);

        // Aktuellen Bildschirm darstellen
        window.display();
    }
    return(0);
}
