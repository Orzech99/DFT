#ifndef SLIDER_H
#define SLIDER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <iostream>
using namespace std;
class Slider
{
public:
  Slider();
  Slider(const sf::Vector2f &position,const sf::Vector2f &size);
  bool processEvent(const sf::Event &event, const sf::Mouse &mouse, const sf::RenderWindow &window); //true if event occured
  int getValue();
  void draw(sf::RenderWindow *window);
 private:
  int value = 0;
  sf::RectangleShape back;
  sf::RectangleShape block;
  bool slide = false;
  bool canSlide(const sf::Vector2f &mouse_pos);

protected:

};

#endif // SLIDER_H
