#ifndef EPICYCLE_H
#define EPICYCLE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <math.h>
#include <complex>
#include <cmath>
#include <iostream>

class Epicycle
{
public:

  Epicycle();
  //Epicycle(sf::RenderWindow *window);
  //void draw();
  void draw(sf::RenderWindow *window, int n = 1);
  void move(float time);
  void setAngle(float angle);
  float getAngle();
  void setRadius(float radius);
  float getRadius();
  void setAngularVelocity(int angular_velocity);
  float getAngularVelocity();
  void setPosition(float x, float y);
  void setPosition(sf::Vector2f position);
  sf::Vector2f getPosition()
  {
     return this->arrow.getPosition();
  }
  float getRotation()
  {
     return arrow.getRotation();
  }
  sf::Vector2f pointingTo();
  sf::RectangleShape arrow;
  sf::CircleShape circle;

protected: //idk why i dont need this

  int angular_velocity;

};

#endif // EPICYCLE_H
