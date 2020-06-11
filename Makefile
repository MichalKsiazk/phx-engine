# -lXrandr -lXi 

objects += main.o
objects += shader.o
objects += phx_engine.o
objects += atom.o
objects += math_utils.o
objects += phx_config.o
objects += collision_system.o
objects += renderer.o
objects += model_loader.o
objects += bmfont.o
objects += utils.o


libs =  -lGLEW -lglfw -lGLU -lGL -lX11 -lpthread -ldl -lcglm
engine: $(objects)
	gcc -t -Wall -o engine $(headers) $(objects) $(libs) -lm -ldl -I.
	find . -name "*.o" -type f -delete
main.o : shader.h

