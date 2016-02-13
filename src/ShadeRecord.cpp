#include "ShadeRecord.h"
#include "World.h"

ShadeRecord::ShadeRecord(World &wr)
	: hit(false),
	  hitPoint(),
	  normal(),
	  color(0.0f, 0.0f, 0.0f),
	  w(wr)
{}

ShadeRecord::ShadeRecord(const ShadeRecord &sr)
	: hit(sr.hit),
	  hitPoint(sr.hitPoint),
	  color(sr.color),
	  w(sr.w)
{}

ShadeRecord::~ShadeRecord()
{}
