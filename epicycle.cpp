#include "epicycle.h"

Epicycle::Epicycle()
{
  circle.setFillColor(sf::Color::Transparent);
  circle.setOutlineThickness(1.0f);
  circle.setOutlineColor(sf::Color::White);
  arrow.setFillColor(sf::Color::White);

}
void Epicycle::draw(sf::RenderWindow *window , int n)
{
  if(n == 0) window->draw(arrow);
  else
    {
      window->draw(arrow);
      window->draw(circle);
    }

}
void Epicycle::move(float time)
{ 
  arrow.rotate(-angular_velocity*time);
}
void Epicycle::setAngle(float angle)
{
  arrow.setRotation(angle);
}
float Epicycle::getAngle()
{

  return arrow.getRotation();
}
void Epicycle::setRadius(float radius)
{
  circle.setRadius(radius);
  arrow.setSize(sf::Vector2f(radius,radius * 0.1f));
  circle.setOutlineThickness(1.5f);
  circle.setPointCount(256);
}
float Epicycle::getRadius()
{
  return circle.getRadius();
}
void Epicycle::setAngularVelocity(int angular_velocity)
{
  this->angular_velocity = -angular_velocity;
}
float Epicycle::getAngularVelocity()
{
  return angular_velocity;
}
void Epicycle::setPosition(float x, float y)
{
   arrow.setPosition(x,y);
   circle.setPosition(x-circle.getRadius(),y-circle.getRadius());
}

void Epicycle::setPosition(sf::Vector2f position)
{
  arrow.setPosition(position);
  arrow.setPosition(sf::Vector2f(position.x - arrow.getSize().y/2.0f * sin((360-arrow.getRotation())*M_PI/180.0f),position.y - arrow.getSize().y/2.0f * cos((360-arrow.getRotation())*M_PI/180.0f))); //wow
  circle.setPosition(position-sf::Vector2f(circle.getRadius(),circle.getRadius()));
}
sf::Vector2f Epicycle::pointingTo()
{
  sf::Vector2f out;
  out.x = circle.getPosition().x + circle.getRadius() + (circle.getRadius() * cos((360-arrow.getRotation())*M_PI/180.0f));
  out.y = circle.getPosition().y + circle.getRadius() - (circle.getRadius() * sin((360-arrow.getRotation())*M_PI/180.0f));
  return out;
}


/*
  Epicycle();
  Epicycle(sf::RenderWindow &window);

  void draw();
  void setAngle(float angle);
  float getAngle();
  void setRadius(float radius);
  float getRadius();
  void setAngularVelocity(float angular_velocity);
  float getAngularVelocity();
  void setPosition(int x, int y);
  void setPosition(sf::Vector2i position);
  sf::Vector2i getPosition();
  sf::Vector2i pointingTo();



private:

  sf::RenderWindow &window = window;

  sf::RectangleShape arrow;
  sf::CircleShape circle;

  sf::Vector2i pointing;

  float angle;
  float angular_velocity;
  float radius;

protected: //idk why i dont need this
*/
