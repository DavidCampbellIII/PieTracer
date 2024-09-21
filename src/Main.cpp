#include <fstream>
#include <iomanip>
#include <iostream>
#include <filesystem>

#include "Matrix.h"
#include "Point.h"
#include "Vector.h"
#include "Shared/Canvas.h"
#include "Shared/Color.h"
#include "Shared/Tuple.h"

namespace fs = std::filesystem;

struct Projectile
{
    Point position;
    Vector velocity;

	Projectile() : 
        position(Point::Zero()), velocity(Vector::Zero()) {}
};

 int main()
 {
     const int WIDTH = 900;
     const int HEIGHT = 550;
     
     const int groundY = 0;
     const float gravity = -0.1f;
     const float wind = 0.07f;
     
     Canvas canvas(WIDTH, HEIGHT);
     
     Projectile projectile;
     projectile.position = Point(0, HEIGHT, 0);
     projectile.velocity = Vector::Zero();
     
     while(projectile.position.y >= groundY)
     {
         std::cout << "Projectile position: " << projectile.position.x << ", " << projectile.position.y << std::endl;
         projectile.velocity += Vector(wind, gravity, 0);
         projectile.position += projectile.velocity;
     
         const int x = static_cast<int>(projectile.position.x);
         const int y = HEIGHT - static_cast<int>(projectile.position.y);
         canvas.WritePixel(x, y, Color(1, 0, 0));
     }
     
     const std::string ppm = canvas.ToPPM();

	 const fs::path exeDir = fs::current_path();
	 //file is running in out/build/Debug or out/build/Release, so we need to go up 3 directories to get to the project root
	 const fs::path outDir = exeDir.parent_path().parent_path().parent_path() / "renders";
     if (!fs::exists(outDir))
     {
         fs::create_directory(outDir);
		 std::cout << "Created directory: " << outDir << std::endl;
     }
     
	 const fs::path filePath = outDir / "projectile.ppm";
     std::ofstream file(filePath, std::ios::out | std::ios::trunc);
     if(!file)
     {
         std::cerr << "Error creating file" << std::endl;
         return 1;
     }
     file << ppm;
     file.close();
     
     return 0;
}
