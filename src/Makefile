CC = g++
OBJS = MultipleObjects.o Object.o Plane.o Ray.o RGBColor.o ShadeRec.o Sphere.o Tracer.o ViewPlane.o World.o
LIBS = ./libRayTracer.so

all: ${OBJS} RayTracer.so main

MultipleObjects.o:
	${CC} MultipleObjects.cpp -c

Object.o:
	${CC} Object.cpp -c

Plane.o:
	${CC} Plane.cpp -c

Ray.o:
	${CC} Ray.cpp -c

RGBColor.o:
	${CC} RGBColor.cpp -c

ShadeRec.o:
	${CC} ShadeRec.cpp -c

Sphere.o:
	${CC} Sphere.cpp -c

Tracer.o:
	${CC} Tracer.cpp -c

ViewPlane.o:
	${CC} ViewPlane.cpp -c

World.o: 
	${CC} World.cpp -c

RayTracer.so: ${OBJS}
	${CC} ${OBJS} -shared -fPIC -o ./libRayTracer.so

main: RayTracer.so
	${CC} main.cpp ${LIBS} -o main

clean:
	rm *.o *~
