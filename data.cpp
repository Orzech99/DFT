#include "data.h"

Data::Data()
{

}

sf::Vector2f Data::getSize()
{
  return this->size;
}
Data::Data( vector <sf::Vector2i> &po, const int &scaling_factor)
{
  points.clear();
  float re, im;
  float sumre = 0;
  float sumri = 0;
  size.x = po[0].x;
  size.y = po[0].y;
  po.erase(po.begin());
      for(auto &p : po)
        {
         re = p.x;
         im = p.y;
         sumre+=re;
         sumri+=im;
         points.emplace_back(std::complex<float>(re,im));
        }


  sumre/=points.size();
  sumri/=points.size();
  for(auto &p : points)
    {
      p -= std::complex<float>(sumre,-sumri);
    }
  cout << "Data has been succesfully read" << endl;
}
Data::Data(const std::string &file_path, const int &scaling_factor)
{
  float re, im;
  float sumre = 0;
  float sumri = 0;
  int count = 0;
  fstream file;
  file.open(file_path);
  if(!file.good()) cout << "Could not open data" << endl;
  file >> re;
  file >> im;
  size.x = re;
  size.y = im;
  while(!file.eof())
    {
      if(count % scaling_factor == 0)
      {
         file >> re;
         file >> im;
         sumre+=re;
         sumri+=im;
         points.emplace_back(std::complex<float>(re,im));


      }
      else
      {
          file >> re;
          file >> im;
      }
    count++;
    }
  sumre/=points.size();
  sumri/=points.size();
  for(auto &p : points)
    {
      p -= std::complex<float>(sumre,-sumri);
    }
  file.close();
  cout << "Data has been succesfully read" << endl;
}

void Data::convert_to_coef(const int &no_epicycles)
{

  coef.clear();
  int coef_num = 1;
  coef.emplace_back(calculate_nth_coef(points,0));

  while(coef.size() != no_epicycles)
    {
        coef.emplace_back(calculate_nth_coef(points,coef_num));
        if(coef_num < 0)
          {
            coef_num *= -1;
            coef_num += 1;
          }
        else coef_num *= -1;
    }
 // points.clear();
  cout << "Converted to coefs" << endl;
 // points.clear();
//    coef.clear();
//      coef.emplace_back(calculate_nth_coef(points,0));
//      cout << "0" << endl;
//      //cout << "Emplaced 0" << endl;
//  for(int l = 1; l <= no_epicycles/2; ++l)
//    {
//      coef.emplace_back(calculate_nth_coef(points,l));
//      cout << "Emplaced " << l <<endl;
//      coef.emplace_back(calculate_nth_coef(points,-l));
//      cout << "Emplaced " << -l <<endl;
//    }
//  points.clear();

  cout << "Number of coefficients: " << coef.size() << endl;
}

std::complex<float> Data::get_coef(const int &n)
{
  //cout << "Will return " << n << "th coefficient" << endl;
//    if(n < 0) return coef[-2*n];
//    else if(n > 0 )return coef[(2/n)-1];
//    else return coef[0];
  return coef[n];

}




/*
private:
  std::vector <std::complex <float>> points;
  std::vector <std::complex <float>> coef;

};
*/
