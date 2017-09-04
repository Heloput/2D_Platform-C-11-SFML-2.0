#include <SFML/Graphics.hpp>
#include "map.h"

using namespace sf;


float offsetX=0, offsetY=0;


class PLAYER {

public:

float dx,dy;
FloatRect rect;
bool onGround;
Sprite sprite;
float currentFrame;

    PLAYER(Texture &image)
   {
    sprite.setTexture(image);
    rect = FloatRect(7*32,9*32,40,50);

    dx=dy=0.1;
    currentFrame = 0;
   }


   void update(float time)
   {

     rect.left += dx * time;
     Collision(0);

     if (!onGround) dy=dy+0.0005*time;
     rect.top += dy*time;
     onGround=false;
     Collision(1);


      currentFrame += 0.005*time;
      if (currentFrame > 6) currentFrame -=6 ;

      if (dx>0) sprite.setTextureRect(IntRect(40*int(currentFrame),244,40,50));
      if (dx<0) sprite.setTextureRect(IntRect(40*int(currentFrame)+40,244,-40,50));


      sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

      dx=0;
   }



   void Collision(int dir)
   {
     for (int i = rect.top/32 ; i<(rect.top+rect.height)/32; i++)
      for (int j = rect.left/32; j<(rect.left+rect.width)/32; j++)
        {
         if (TileMap[i][j]=='B')
           {
            if ((dx>0) && (dir==0)) rect.left =  j*32 -  rect.width;
            if ((dx<0) && (dir==0)) rect.left =  j*32 + 32;
            if ((dy>0) && (dir==1))  { rect.top =   i*32 -  rect.height;  dy=0;   onGround=true; }
            if ((dy<0) && (dir==1))  { rect.top = i*32 + 32;   dy=0;}
            //std::cout << i << j << std::endl;
           }

         if (TileMap[i][j]=='0')
                           {
                             TileMap[i][j]=' ';
                           }

        }

   }
};

class ENEMY
{

public:
    float dx, dy;
    FloatRect rect;
    Sprite sprite;
    float currentFrame;
    bool life;


    void set(Texture &image, int x, int y)
    {
        sprite.setTexture(image);
        rect = FloatRect(x, y, 93, 69);

        dx = 0.05;
        currentFrame = 0;
        life = true;
    }

    void update(float time)
    {
        rect.left += dx * time;

        Collision();


        currentFrame += time * 0.005;
        if (currentFrame > 3) currentFrame -= 3;

        sprite.setTextureRect(IntRect(93* int(currentFrame)+93, 0, -93, 69));
        if (!life) sprite.setTextureRect(IntRect(+93, 0, -93, 69));


        sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

    }


    void Collision()
    {

        for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
            for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
                if (TileMap[i][j] == 'B')
                {

                    if (dx > 0)
                    {
                        rect.left = j * 32 - rect.width; dx *= -1;
                    }
                    else if (dx < 0)
                    {
                        rect.left = j * 32 + 32;  dx *= -1;
                    }
                    std::cout << i << j << std::endl;

                    if (TileMap[i][j] == ' ') continue;
                }
    }

};

int main(int argc,char *argv[] )
{
    RenderWindow window( VideoMode(600, 400), "Game");

    float currentFrame = 0.0;

    Texture t;
    t.loadFromFile("images/fang_and_mario.png");

    Sprite sprite;
    sprite.setTexture(t);

    Texture map;
    map.loadFromFile("images/map.png");

    Sprite sprite_map;
    sprite_map.setTexture(map);

    Texture spider;
    spider.loadFromFile("images/enemy.png");

    Sprite s_spider;
    s_spider.setTexture(spider);

    PLAYER p(t);
    ENEMY enemy;
    enemy.set(spider,250, 347);

    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        time = time/700;

        if (time>20) time = 20;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            p.dx = -0.1;

        }

        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            p.dx = 0.1;
        }

        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            if (p.onGround) { p.dy=-0.35; p.onGround=false;}
        }


        p.update(time);

        enemy.update(time);



        if (p.rect.left>300) offsetX = p.rect.left - 300;
        if(p.rect.top >200) offsetY = p.rect.top - 200;

         window.clear(Color(107, 140, 255));

        for (int i = 0; i<H; i++)
            for (int j = 0; j<W; j++)
            {
                if (TileMap[i][j] == 'B')  sprite_map.setTextureRect(IntRect(642, 162, 32, 32));

                if ((TileMap[i][j] == ' ') || (TileMap[i][j] == '0')) continue;

                sprite_map.setPosition(j * 32 - offsetX, i * 32 - offsetY);
                window.draw(sprite_map);
            }
        window.draw(enemy.sprite);
        window.draw(p.sprite);
        window.display();
    }

    return 0;
}
