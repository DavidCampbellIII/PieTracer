#include <fstream>
#include <iomanip>
#include <iostream>
#include <filesystem>
#include <vector>

#include "Matrix.h"
#include "Point.h"
#include "Ray.h"
#include "Raytracer.h"
#include "Vector.h"
#include "Shapes/Sphere.h"
#include "Shared/Canvas.h"
#include "Shared/Color.h"
#include "Shared/Intersection.h"
#include "Shared/Tuple.h"

namespace fs = std::filesystem;

 int main()
 {
	 const Raytracer raytracer;
     const int WIDTH = 900;
     const int HEIGHT = 550;
     
     Canvas canvas(WIDTH, HEIGHT);
     
	 const Color red(1, 0, 0);
	 Sphere sphere(Matrix<4, 4>::Translation(0.f, 2.f, 0.f));
	 const float wallSize = 20.f;
	 const float wallZ = 10.f;

	 const float pixelSize = wallSize / WIDTH;
	 const float half = wallSize / 2.f;

	 const Point rayOrigin = Point(0, -1, -5);
	 for (int y = 0; y < HEIGHT; ++y)
     {
		 const float worldY = half - pixelSize * y;
		 for (int x = 0; x < WIDTH; ++x)
		 {
			 const float worldX = -half + pixelSize * x;
			 const Point position = Point(worldX, worldY, wallZ);
			 const Vector direction = (position - rayOrigin).Normalize();
			 const Ray ray(rayOrigin, direction);
			 const std::array<Intersection, 2> sphereIntersections = sphere.Intersect(ray);
			 const std::vector<Intersection> intersections(sphereIntersections.begin(), sphereIntersections.end());
			 const std::shared_ptr<Intersection> hit = raytracer.Hit(intersections);
			 if (hit)
			 {
				 canvas.WritePixel(x, y, red);
			 }
		 }
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
