#ifndef TRACER_H
#define TRACER_H

#include "Prerequisites.h"

class Tracer {
	public:
		Tracer();
		Tracer(World *);

		virtual RGBColor TraceRay(const Ray &) const;

	protected:
		World *m_WorldPtr;
};

#endif
