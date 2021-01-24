#ifndef DATA_H
#define DATA_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;




class Data
{
public:
  Data();
  Data(const std::string &file_path, const int &scaling_factor);
  Data( vector <sf::Vector2i> &po, const int &scaling_factor);
  void convert_to_coef(const int &no_epicycles);
  std::complex<float> get_coef(const int &n);
  sf::Vector2f getSize();
  std::vector <std::complex <float>> points;

private:
  complex <float> calculate_nth_coef(const vector <complex <float>> &points, const int &nof_coef)
  {
     float pi = M_PI;
     float t = 2*pi;
     complex <float> sum = complex<float>(0.0f,0.0f);
     float step = t/(points.size()-1);
     for(float k = 0; k < static_cast<int>(points.size())-1; k++)
       {
         sum += /*1*/(exp((-complex<float>(0.0f,1.0f)*static_cast<float>(nof_coef)*(k*step) * 2.0f * pi)/t)) * /*2*/ step /*((k+1)*step-(k*step))*/ * /*3*/ points[k];
       }
     sum /= (t);
   return sum;
  }
  //wstd::vector <std::complex <float>> points;
  std::vector <std::complex <float>> coef;
  sf::Vector2f size;

};

#endif // DATA_H
