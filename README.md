# Raytracer
Welcome to the Raytracer, this project is about making a render with multiple shapes with the raytracing method
Contributors:

 - Martin Sabatier
 - Raphaël Castres
 - Nathanaël Kimbembe--croissant
 - Matthias Soual

![image](https://github.com/EpitechPromo2027/B-OOP-400-TLS-4-1-raytracer-raphael.castres/assets/96376018/e225005c-36fa-4c7b-b852-eecd0e010f5f)
![image](https://github.com/EpitechPromo2027/B-OOP-400-TLS-4-1-raytracer-raphael.castres/assets/96376018/3d95d18b-dacf-40db-9012-bd9e2324c783)
![image](https://github.com/EpitechPromo2027/B-OOP-400-TLS-4-1-raytracer-raphael.castres/assets/96376018/ed99afc0-9e93-4a92-b484-23f3753d806a)
![image](https://github.com/EpitechPromo2027/B-OOP-400-TLS-4-1-raytracer-raphael.castres/assets/96376018/2814a2ad-f658-49f9-b2b8-961e33bc4bdc)
![image](https://github.com/EpitechPromo2027/B-OOP-400-TLS-4-1-raytracer-raphael.castres/assets/96376018/1d1b9d8f-a47c-48d1-9f97-63a8d2947dfd)


# Requirements
- g++
- make
- SFML Graphic Library
- libconfig++


# Usage

    make
    ./raytracer {config_file.cfg}

# Configuration File
The config file need for the progam is parsed using libconfig++, here is a example of what it should look like:

    World:
    {
	    width = 800;
	    height = 800;
	    skybox = { r = 0.0; g = 0.0; b = 0.0; };
	    bounces  =  10;
	    iterations  =  10;
	    frames  =  10;
	    display  =  true;
     		cameras  =  (
			{
				anti_aliasing  =  false;
				depth_of_field  =  false;
				origin  =  {
					origin  =  {  x  =  -0.5;  y  =  -0.5;  z  =  0.8;  };
					botSide  =  {  x  =  1.0;  y  =  0.0;  z  =  0.0;  };
					leftSide  =  {  x  =  0.0;  y  =  1.0;  z  =  0.0;  };
				};
				screen  =  {
					origin  =  {  x  =  -0.5;  y  =  -0.5;  z  =  1.0;  };
					botSide  =  {  x  =  1.0;  y  =  0.0;  z  =  0.0;  };
					leftSide  =  {  x  =  0.0;  y  =  1.0;  z  =  0.0;  };
				};
			}
		);
	};
	#Materials in the scene
	Materials:
	{
		flats  =  (
			{ name = "Light";  color  =  {  r  =  255.0;  g  =  255.0;  b  =  255.0;  }; intensity = 10.0; },
			{ name = "Red";  color  =  {  r  =  255.0;  g  =  0.0;  b  =  0.0;  };  intensity  =  0.0;  },
			{ name = "Green";  color  =  {  r  =  0.0;  g  =  255.0;  b  =  0.0;  };  intensity  =  0.0;  },
			{ name = "Blue";  color  =  {  r  =  0.0;  g  =  0.0;  b  =  255.0;  };  intensity  =  0.0;  }
		);
		reflectors  =  (
			{  name  =  "Mirror";  color  =  {  r  =  255.0;  g  =  255.0;  b  =  255.0;  };  }
		);
	};
	#Objects in the scene
	Shapes:
	{
		spheres  =  (
			{  name  =  "Earth";
				origin  =  {  x  =  0.0;  y  =  55.0;  z  =  5.0;  };
				radius  =  50.0;
				material  =  "Blue";
			},
			{  name  =  "Sun";
				origin  =  {  x  =  0.0;  y  =  5.0;  z  =  10.0;  };
				radius  =  3.0;
				material  =  "Light";
			}
		);
		planes  =  (
			{  name  =  "Plane";
				origin  =  {  x  =  0.0;  y  =  5.1;  z  =  10.0;  };
				normal  =  {  x  =  0.0;  y  =  1.0;  z  =  0.0;  };
				material  =  "Green";
				rotation  =  {  angle  =  45.0;  axis  =  "x";  };
			}
		);
		cylinders  =  (
			{  name  =  "Cyl";
				origin  =  {  x  =  -2.0;  y  =  0.0;  z  =  5.0;  };
				radius  =  0.3;
				direction  =  {  x  =  0.0;  y  =  1.0;  z  =  0.0;  };
				material  =  "Red";
				translation  =  {  x  =  4.0;  y  =  0.0;  z  =  0.0;  };
				scale  =  {  x  =  2.0;  y  =  2.0;  z  =  2.0;  };
			}
		);
		cones  =  (
			{  name  =  "Cone";
				origin  =  {  x  =  5.0;  y  =  0.0;  z  =  5.0;  };
				angle  =  10.0;
				direction  =  {  x  =  0.0;  y  =  1.0;  z  =  0.0;  };
				material  =  "Green";
			}
		);
		triangles  =  (
			{  name  =  "Triangle";
				p1  =  {  x  =  -6.0;  y  =  5.0;  z  =  5.0;  };
				p2  =  {  x  =  -4.0;  y  =  5.0;  z  =  6.0;  };
				p3  =  {  x  =  -5.0;  y  =  5.0;  z  =  4.0;  };
				material  =  "Red";
			}
		);
	};`

## World parameters
This will define the paramaters used for the render

 - width/height: Resolution of the render
 - skybox: RGB values of the background of the render
 - bounces: defines the number of times each ray of light will bounce
 - iterations: 
 - frames: defines the number of renders to get the final result, the more frames you have, the more detailed the render will be, but it will take longer
 - display: if true, will open a CSFML window where you can see the render in real time
 * Cameras
	 * Origin
		 * origin: determines the coordinates of the camera
		 * botside: offset from the bottom
		 * leftside: offset from the left
	* Screen 
		* origin: determines the coordinates of the camera
		 * botside: offset from the bottom
		 * leftside: offset from the left

## Materials
Materials are the texture that you apply on shapes, they need a name so they can be attached to shapes.

* Flats: Materials with only a flat color
	* Name: Name of the material
	* Color: RGB values of the color
	* Intensity: Set this value if the material should emit light, an intensity at 0 means it doesn't emit light, the higher the value, the higher the intensity of the light is
* Reflectors: Materials that can reflect light
	* Name: Name of the material
	* Color: RGB value of the color

## Shapes
Shapes are the core of the render, place shapes at different places with different materials and see what happens.

Every shape has a material attached to it reference by the name defined earlier, and every shape except triangles have an origin, which are the coordinates of the shape.

Every shape can have a transformation vector applied to it, the transformations are:

* Translation
* Scale
* Rotation

Here are the specifics for every shape.

* Spheres
	* Radius: Radius of the sphere
* Planes
	* Normal: Normal vector of the plane
* Cylinders
	* Radius: Radius of the cylinder
	* Direction: Vector that determines the direction of the cylinder
* Cones
	* Angle: angle at the top of the cone
	* Direction: Vector that determines the direction of the cone
* Triangles
	* P1/P2/P3, Coordinates of each point of the triangle
