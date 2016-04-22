CC = g++
OBJS = ${GOBJECTS} ${SAMPLERS} ${TRACERS} ${UTIL} ${WORLD}
LIBS = ./libRayTracer.so
C11FLAG = -std=c++11

GOBJECTS = Object.o Plane.o Sphere.o
SAMPLERS = Jittered.o MultiJittered.o PureRandom.o Regular.o Sampler.o 
TRACERS = MultipleObjects.o Tracer.o
UTIL = Ray.o RGBColor.o ShadeRecord.o
WORLD = ViewPlane.o World.o

# Geometric Objects
Object.o:
	@echo "Geometric Objects"
	${CC} Object.cpp -c

Plane.o:
	${CC} Plane.cpp -c

Sphere.o:
	${CC} Sphere.cpp -c

# Samplers
Jittered.o:
	@echo "\nSamplers"
	${CC} Jittered.cpp -c ${C11FLAG}

MultiJittered.o:
	${CC} MultiJittered.cpp -c ${C11FLAG}

PureRandom.o:
	${CC} PureRandom.cpp -c ${C11FLAG}

Regular.o:
	${CC} Regular.cpp -c ${C11FLAG}

Sampler.o:
	${CC} Sampler.cpp -c ${C11FLAG}


# Tracers
MultipleObjects.o:
	@echo "\nTracers"
	${CC} MultipleObjects.cpp -c ${C11FLAG}

Tracer.o:
	${CC} Tracer.cpp -c ${C11FLAG}

# Utilities
Ray.o:
	@echo "\nUtilities"
	${CC} Ray.cpp -c

RGBColor.o:
	${CC} RGBColor.cpp -c

ShadeRecord.o:
	${CC} ShadeRecord.cpp -c ${C11FLAG}

# World
ViewPlane.o:
	@echo "\nWorld"
	${CC} ViewPlane.cpp -c ${C11FLAG}

World.o:
	${CC} World.cpp -c ${C11FLAG}

# Shared library
RayTracer.so: ${OBJS}
	@echo "\nShared library"
	${CC} ${OBJS} -shared -fPIC -o ./libRayTracer.so

# Main
main: RayTracer.so
	@echo "\nMain program"
	${CC} main.cpp ${LIBS} ${C11FLAG} -o main

# all and clean targets
all: ${OBJS} RayTracer.so main

clean:
	rm *.o *~
