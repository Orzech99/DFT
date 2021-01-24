#include "slider.h"

Slider::Slider()
{

}
Slider::Slider(const sf::Vector2f &position,const sf::Vector2f &size)
{
  this->back.setPosition(position);
  this->back.setSize(size);
  this->block.setSize(sf::Vector2f(15.0f,3.0f * size.y));
  this->block.setPosition(sf::Vector2f(position.x,position.y - 1.0f/3.0f * block.getSize().y));
  block.setFillColor(sf::Color::Green);
  back.setFillColor(sf::Color::White);
}
bool Slider::canSlide(const sf::Vector2f &mouse_pos)
{
 // cout << "Blocks pos x = " << block.getGlobalBounds().left << endl;
 // cout << "Blocks pos x and width  = " << this->block.getGlobalBounds().left + this->block.getGlobalBounds().width << endl;
  if(this->block.getGlobalBounds().left <= mouse_pos.x && (this->block.getGlobalBounds().left + this->block.getGlobalBounds().width) >= mouse_pos.x) return true;
  else return false;
}
bool Slider::processEvent(const sf::Event &event, const sf::Mouse &mouse,const sf::RenderWindow &window)
{
  if(block.getGlobalBounds().contains(sf::Vector2f(mouse.getPosition(window))))
    {
      block.setFillColor(sf::Color::Red);
    }

  if(slide && this->canSlide(sf::Vector2f(mouse.getPosition())))
    {
      cout << "Can slide " << endl;
      block.setPosition(mouse.getPosition().x,this->block.getPosition().y);
    }
//  else cout << "Cannot slide" << endl;
//  cout << "left " << block.getPosition().x << endl;
//  cout << "top " << block.getPosition().y << endl;
//   cout << "left2 " << block.getPosition().x + block.getSize().x << endl;
//   cout << "top2 " << block.getPosition().y + block.getSize().y << endl;

  cout << "mps " << mouse.getPosition(window).x << " " << mouse.getPosition(window).y << endl;

  if(event.type == event.MouseButtonPressed && this->block.getGlobalBounds().contains(sf::Vector2f(mouse.getPosition(window))))
    {
      cout << "Clicked on block" << endl;
      slide = !slide;
    }
  this->value = ((this->block.getPosition().x-this->back.getPosition().x)/(this->block.getGlobalBounds().width))*100;
  return true;
}

int Slider::getValue()
{
  return this->value;
}
void Slider::draw(sf::RenderWindow *window)
{
  window->draw(this->back);
  window->draw(this->block);
}
