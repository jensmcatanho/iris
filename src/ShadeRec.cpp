#include "ShadeRec.h"
#include "World.h"

ShadeRec::ShadeRec(World& wr)
	: hit(false),
	  hitPoint(),
	  normal(),
	  color(0.0f, 0.0f, 0.0f),
	  w(wr)
{}

ShadeRec::ShadeRec(const ShadeRec& sr)
	: hit(sr.hit),
	  hitPoint(sr.hitPoint),
	  color(sr.color),
	  w(sr.w)
{}
