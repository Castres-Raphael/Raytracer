##
## EPITECH PROJECT, 2024
## raytracer
## File description:
## Makefile
##

SRC     =   src/Ray/Ray.cpp\
			src/Shape/Transformation/Matrix.cpp\
			src/Shape/AShape.cpp\
			src/Shape/Sphere.cpp\
			src/Shape/Cylinder.cpp\
			src/Shape/Plane.cpp\
			src/Shape/Cone.cpp\
			src/Shape/Triangle.cpp\
			src/Shape/Materials/Flat.cpp\
			src/Shape/Materials/Mirror.cpp\
			src/Shape/Rectangle3D.cpp\
			src/World/Camera.cpp\
			src/World/World.cpp\
			src/World/Scene.cpp\
			src/World/ObjectFactory.cpp\
			src/World/WorldBuilder.cpp\
			src/main.cpp


OBJ     =   $(SRC:.cpp=.o)

NAME    =   raytracer

CC      =   g++
CFLAGS  =   -std=c++20 -Wall -Wextra -O3
LDFLAGS =   -lsfml-graphics -lsfml-window -lsfml-system -lconfig++
INCLUDES =  -I./src/Ray -I./src/Shape -I./src/Shape/Materials -I./src/World -I./src -I./src/Shape/Transformation

%.o : %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(NAME) :   $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

all :       $(NAME)

profile : CFLAGS += -pg
profile : LDFLAGS += -pg
profile : re

debug : CFLAGS += -g3
debug : re

clean :
	rm -f *~
	rm -f #*#
	rm -f vgcore.*
	rm -f $(OBJ)

fclean :    clean
	rm -f $(NAME)

re :        fclean all

.PHONY :    all clean fclean re
