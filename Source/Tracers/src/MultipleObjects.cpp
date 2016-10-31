#include "MultipleObjects.h"
#include "ShadeRecord.h"
#include "World.h"

MultipleObjects::MultipleObjects()
	: Tracer() {

}

MultipleObjects::MultipleObjects(World *wPtr)
	: Tracer(wPtr) {

}

RGBColor MultipleObjects::TraceRay(const Ray &ray) const {
	ShadeRecord sr(m_WorldPtr->HitObjects(ray));

	if (sr.m_Hit)
		return sr.m_Color;
	else
		return m_WorldPtr->m_BackgroundColor;
}
