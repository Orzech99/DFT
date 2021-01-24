//it should actually be complexDFT not complex FFT because
//we use discrete fourier transform not fast fourier transform mb :(

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <fstream>
#include <vector>
#include <math.h>
#include <iostream>
#include <complex>
#include <cmath>
#include <epicycle.h>
#include <data.h>
#include <slider.h>
using namespace std; 

sf::Color black = sf::Color::Black;
sf::Color white = sf::Color::White;

void prepareEpicycles(vector <Epicycle> &epicycles,  Data &data, const sf::Texture &at, const int noc)
{
  //data.convert_to_coef(noc);
  epicycles.clear();
  epicycles.emplace_back(Epicycle());
  epicycles[0].setPosition(sf::Vector2f(data.getSize().x/2,data.getSize().y/2));

  epicycles[0].arrow.setTexture(&at);

  epicycles[0].setAngle(arg(data.get_coef(0)) * 180 / M_PI);
  epicycles[0].setRadius(std::abs(data.get_coef(0)));
  epicycles[0].setAngularVelocity(0);


  for(int l = 1; l < noc; ++l)
    {
      Epicycle tmp;
      tmp.setPosition(epicycles[l-1].pointingTo());
      tmp.arrow.setTexture(&at);

      tmp.setAngle(arg(data.get_coef(l)) * 180 / M_PI);
      tmp.setRadius(std::abs(data.get_coef(l)));
      tmp.circle.setOutlineColor(sf::Color::Red);
      tmp.arrow.setFillColor(sf::Color::Red);
      epicycles.emplace_back(tmp);
      if(l%2==0)epicycles[l].setAngularVelocity(-l/2);
      else epicycles[l].setAngularVelocity(l/2+1);
    }
  epicycles[epicycles.size()-1].arrow.setFillColor(sf::Color::Blue);
}

void prepareEpicyclesDrawn(vector <Epicycle> &epicycles,  Data &data, const sf::Texture &at, const int noc)
{
  //data.convert_to_coef(noc);
  epicycles.clear();
  epicycles.emplace_back(Epicycle());
  epicycles[0].setPosition(sf::Vector2f(500,500));

  epicycles[0].arrow.setTexture(&at);

  epicycles[0].setAngle(arg(data.get_coef(0)) * 180 / M_PI);
  epicycles[0].setRadius(std::abs(data.get_coef(0)));
  epicycles[0].setAngularVelocity(0);


  for(int l = 1; l < noc; ++l)
    {
      Epicycle tmp;
      tmp.setPosition(epicycles[l-1].pointingTo());
      tmp.arrow.setTexture(&at);

      tmp.setAngle(arg(data.get_coef(l)) * 180 / M_PI);
      tmp.setRadius(std::abs(data.get_coef(l)));

      epicycles.emplace_back(tmp);
      if(l%2==0)epicycles[l].setAngularVelocity(-l/2);
      else epicycles[l].setAngularVelocity(l/2+1);
    }
  epicycles[epicycles.size()-1].arrow.setFillColor(sf::Color::Blue);
}


int main()
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    int noc = 200;

    sf::Image img;
    img.create(5000,5000,black);
    sf::Image clean_img;
    clean_img.create(2500,2500,black);
    sf::Texture tex;
    sf::Texture clean_tex;
    clean_tex.loadFromImage(clean_img);
    sf::Sprite spr;
    spr.setPosition(-500,500);
    sf::Texture at;
    at.loadFromFile("arrow.png");

    sf::RenderWindow window(sf::VideoMode(1920,1080), "complexDFT",sf::Style::Default,settings);

    window.setFramerateLimit(300);
    sf::View camera;
    camera.setSize(1920,1080);
    camera.setCenter(0,0);
    bool drawing = false;
    window.setView(camera);

    Data data("snowflake.txt",1);

    data.convert_to_coef(noc);

    sf::Font font;
    font.loadFromFile("font.ttf");

    sf::Text debug;
    debug.setString("00,here");
    debug.setFont(font);
    debug.setFillColor(white);

    sf::Mouse mouse;


    vector <Epicycle> epicycles;
    prepareEpicycles(epicycles,data,at,noc);
    Slider circlesSlider(sf::Vector2f(epicycles[1].getPosition().x + 500.0f,epicycles[1].getPosition().y),sf::Vector2f(200,10));
    sf::Vector2f big;
    sf::Vector2f smal;
    sf::Event event;
    sf::Clock clock;
    sf::Vector2f last;
    int time_constant = 0;
    bool start = false;
    bool show = false;
    bool follow = true;
    bool draw_circles = true;
    vector <sf::Vector2i> to_erase;
    vector <sf::Vector2i> drawn;
    sf::Vector2i drawn_low;
    sf::Vector2i drawn_high;
    to_erase.clear();

    int what_follow = epicycles.size()-1;

    while(window.isOpen())
    {
        float time =  time_constant * clock.getElapsedTime().asSeconds();
        clock.restart();
        if(start)
          {
          img.setPixel(round(epicycles[epicycles.size()-1].pointingTo().x),round(epicycles[epicycles.size()-1].pointingTo().y),white);
          }
         if(drawing)
          {
            if(!drawn.empty() && drawn.back() != sf::Vector2i(mouse.getPosition(window).x-70,mouse.getPosition(window).y+1130))
              {
                img.setPixel(mouse.getPosition(window).x-70,mouse.getPosition(window).y+1130,white);
                if(drawn_high.x < mouse.getPosition(window).x-70) drawn_high.x = mouse.getPosition(window).x-70;
                if(drawn_high.y < mouse.getPosition(window).y+1130) drawn_high.y = mouse.getPosition(window).y+1130;
                if(drawn_low.x > mouse.getPosition(window).x-70) drawn_low.x = mouse.getPosition(window).x-70;
                if(drawn_low.y > mouse.getPosition(window).y+1130) drawn_low.y = mouse.getPosition(window).y+1130;
                drawn.emplace_back(sf::Vector2i(mouse.getPosition(window).x-70,mouse.getPosition(window).y+1130));
              }

          }
        tex.loadFromImage(img);
        spr.setTexture(tex);
        spr.setPosition(0,0);
        debug.setPosition(spr.getPosition());


           if(window.pollEvent(event))
           {
               circlesSlider.processEvent(event,mouse,window);
               if(event.type == event.Closed) window.close();
               if(event.type == event.KeyPressed && event.key.code == sf::Keyboard::Q) window.close();
               if(event.type == event.KeyPressed && event.key.code == sf::Keyboard::Up)
                 {
                   noc++;
                   data.convert_to_coef(noc);
                   prepareEpicycles(epicycles,data,at,noc);
                 }
               if(event.type == event.KeyPressed && event.key.code == sf::Keyboard::Down)
                 {
                   noc--;
                   data.convert_to_coef(noc);
                   prepareEpicycles(epicycles,data,at,noc);
                 }
               if(event.type == event.KeyPressed && event.key.code == sf::Keyboard::Left)
                 {
                   if(what_follow != 0 ) what_follow--;
                 }
               if(event.type == event.KeyPressed && event.key.code == sf::Keyboard::Right)
                 {
                   if(what_follow != static_cast<int>(epicycles.size()-1)) what_follow++;
                 }
               if(event.type == event.KeyPressed && event.key.code == sf::Keyboard::W)
                 {
                   camera.zoom(0.9f);
                   for(auto &e : epicycles)
                     {
                       e.circle.setOutlineThickness(e.circle.getOutlineThickness() * 0.9f);
                     }
                 }
               if(event.type == event.KeyPressed && event.key.code == sf::Keyboard::S)
                 {
                   camera.zoom(1.1f);
                   for(auto &e : epicycles)
                     {
                       e.circle.setOutlineThickness(e.circle.getOutlineThickness()*1.1f);
                     }
                 }
               if(event.type == event.KeyPressed && event.key.code == sf::Keyboard::P)
                 {
                    show = !show;
                 }
               if(event.type == event.KeyPressed && event.key.code == sf::Keyboard::C)
                 {
                    follow = !follow;
                 }
               if(event.type == event.KeyPressed && event.key.code == sf::Keyboard::Z)
                 {
                    draw_circles = !draw_circles;
                 }
               if(event.type == event.KeyPressed && event.key.code == sf::Keyboard::K)
                 {
                    img = clean_img;
                 }
               if(event.type == event.KeyPressed && event.key.code == sf::Keyboard::D)
                 {
                    drawing = !drawing;
                    if(drawing)
                      {
                        drawn.emplace_back(sf::Vector2i(mouse.getPosition(window).x-70,mouse.getPosition(window).y+1130));
                        drawn_high = drawn[0];
                        drawn_low = drawn[0];
                      }
                    if(!drawing)
                      {
                        for(auto &d : drawn)
                          {
                            d.x-=drawn_high.x;
                            d.y-=drawn_high.y;
                          }
                        data = Data(drawn,1);
                        data.convert_to_coef(noc);
                        epicycles.empty();
                        prepareEpicyclesDrawn(epicycles,data,at,noc);
                        drawn.clear();
                      }
                 }
               if(event.type == event.KeyPressed && event.key.code == sf::Keyboard::Space)
                 {
                   if(start)
                     {
                      time_constant = 0;
                      start = !start;
                     }
                   else
                     {
                      time_constant = 15;
                      start = !start;
                     }
                 }
          }
            for(int l = 0; l < noc; ++l) epicycles[l].move(time);

            cout << "Camera size: " << camera.getSize().x << endl;

           for(int l = 1; l < noc; ++l) epicycles[l].setPosition(epicycles[l-1].pointingTo());



       if(!follow)camera.setCenter(epicycles[0].pointingTo());
       else camera.setCenter(epicycles[what_follow].pointingTo());

       window.setView(camera);

       window.clear();


       window.draw(spr);
      for(int l = 1; l < noc; ++l)
        {
          if(epicycles[l].getRadius() < camera.getSize().x)
            {
              if(draw_circles)epicycles[l].draw(&window,1);
              epicycles[l].draw(&window,0);
            }
        }

      if(show)window.draw(spr);

      circlesSlider.draw(&window);
       window.display();

    }




    return 0;
}
