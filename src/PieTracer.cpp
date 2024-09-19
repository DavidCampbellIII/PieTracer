#include <iostream>

#include "Tuple.h"

struct Projectile
{
    Tuple position;
    Tuple velocity;
};

// int main()
// {
//     const int WIDTH = 900;
//     const int HEIGHT = 550;
//     
//     const int groundY = 0;
//     const float gravity = -0.1f;
//     const float wind = 0.01f;
//
//     Projectile projectile;
//     projectile.position = Tuple::Point(0, 1, 0);
//     projectile.velocity = Tuple::VectorZero();
//
//     while(projectile.position.y >= groundY)
//     {
//         std::cout << "Projectile position: " << projectile.position.x << ", " << projectile.position.y << std::endl;
//         projectile.velocity += Tuple::Vector(wind, gravity, 0);
//         projectile.position += projectile.velocity;
//     }
//
//     std::cout << "Done!" << std::endl;
//     return 0;
// }
