#include <fstream>
#include <iomanip>
#include <iostream>
#include <filesystem>
#include <vector>

#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Matrix.h"
#include "Point.h"
#include "Ray.h"
#include "Raytracer.h"
#include "Vector.h"
#include "World.h"
#include "Shapes/Sphere.h"
#include "Core/Canvas.h"
#include "Core/Color.h"
#include "Core/Intersection.h"
#include "Core/Tuple.h"

namespace fs = std::filesystem;

 int main()
 {
	 const Raytracer raytracer;
	 const int WIDTH = 1024;
	 const int HEIGHT = 1024;
     
     Canvas canvas(WIDTH, HEIGHT);
     
	 Material material;
	 material.color = Color(1.f, 1.f, 1.f);
	 material.specular = 0.6f;
	 material.ambient = 0.2f;
	 material.shininess = 200.f;
	 Sphere sphere(Matrix<4, 4>::Translation(0.f, -1.f, 0.f), 
		 std::make_shared<Material>(material));

	 const float intensity = 1.f;
	 const Light light(Point(2, 10, 0), Color(1, 0.f, 0.f) * intensity);

     World world;
	 world.AddLight(std::make_shared<Light>(light));
	 world.AddTraceable(std::make_shared<Sphere>(sphere));

	 //TODO : implement camera

	 raytracer.Render(world, Camera(), canvas);
     
     const std::string ppm = canvas.ToPPM();

	 const fs::path exeDir = fs::current_path();
	 //file is running in out/build/Debug or out/build/Release, so we need to go up 3 directories to get to the project root
	 const fs::path outDir = exeDir.parent_path().parent_path().parent_path() / "renders";
     if (!fs::exists(outDir))
     {
         fs::create_directory(outDir);
		 std::cout << "Created directory: " << outDir << std::endl;
     }
     
	 const fs::path filePath = outDir / "out.ppm";
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
