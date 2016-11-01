#ifndef MULTIPLEOBJECTS_H
#define MULTIPLEOBJECTS_H

#include "Tracer.h"

class MultipleObjects : public Tracer {
	public:
		MultipleObjects();
		MultipleObjects(std::shared_ptr<World>);
		
		virtual RGBColor TraceRay(const Ray &) const;
};

#endif
