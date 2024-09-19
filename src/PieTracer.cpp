#include <fstream>
#include <iomanip>
#include <iostream>

#include "Canvas.h"
#include "Color.h"
#include "Tuple.h"

struct Projectile
{
    Tuple position;
    Tuple velocity;
};

//  int main()
//  {
//      const int WIDTH = 900;
//      const int HEIGHT = 550;
//      
//      const int groundY = 0;
//      const float gravity = -0.1f;
//      const float wind = 0.07f;
//      
//      Canvas canvas(WIDTH, HEIGHT);
//      
//      Projectile projectile;
//      projectile.position = Tuple::Point(0, HEIGHT, 0);
//      projectile.velocity = Tuple::VectorZero();
//      
//      while(projectile.position.y >= groundY)
//      {
//          std::cout << "Projectile position: " << projectile.position.x << ", " << projectile.position.y << std::endl;
//          projectile.velocity += Tuple::Vector(wind, gravity, 0);
//          projectile.position += projectile.velocity;
//      
//          const int x = static_cast<int>(projectile.position.x);
//          const int y = HEIGHT - static_cast<int>(projectile.position.y);
//          canvas.WritePixel(x, y, Color(1, 0, 0));
//      }
//      
//      const std::string ppm = canvas.ToPPM();
//      
//      std::ofstream file("out/projectile.ppm", std::ios::out | std::ios::trunc);
//      if(!file)
//      {
//          std::cerr << "Error creating file" << std::endl;
//          return 1;
//      }
//      file << ppm;
//      file.close();
//      
//      return 0;
// }
