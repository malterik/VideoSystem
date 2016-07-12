#include "Pixel.hpp"

Pixel::Pixel(int numberOfLabels) : 
  best_assignment()
{
  for(int i = 0; i < 5; i++) {
    msg[i] = new unsigned int [numberOfLabels];
  }
    


}
