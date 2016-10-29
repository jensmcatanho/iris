#include "ShadeRecord.h"

ShadeRecord::ShadeRecord(World &wr)
	: hit(false),
	  hitPoint(),
	  normal(),
	  color(RGBColor::Black),
	  w(wr) {

}

ShadeRecord::ShadeRecord(const ShadeRecord &sr)
	: hit(sr.hit),
	  hitPoint(sr.hitPoint),
	  color(sr.color),
	  w(sr.w) {

}
