#include "MultipleObjects.h"
#include "ShadeRecord.h"
#include "World.h"

MultipleObjects::MultipleObjects()
	: Tracer() {

}

MultipleObjects::MultipleObjects(std::shared_ptr<World> worldPtr)
	: Tracer(worldPtr) {

}

RGBColor MultipleObjects::TraceRay(const Ray &ray) const {
	std::shared_ptr<World> worldPtr = m_WorldPtr.lock();
	assert(worldPtr);
	ShadeRecord sr(worldPtr->HitObjects(ray));

	if (sr.m_Hit)
		return sr.m_Color;
	else
		return worldPtr->m_BackgroundColor;
}
