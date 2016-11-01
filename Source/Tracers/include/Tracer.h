#ifndef TRACER_H
#define TRACER_H

#include "Prerequisites.h"

class Tracer {
	public:
		Tracer();
		Tracer(std::shared_ptr<World>);

		virtual RGBColor TraceRay(const Ray &) const;

	protected:
		std::weak_ptr<World> m_WorldPtr;
};

#endif
