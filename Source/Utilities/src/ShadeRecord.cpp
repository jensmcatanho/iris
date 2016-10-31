#include "ShadeRecord.h"

ShadeRecord::ShadeRecord(World &wr)
	: m_Hit(false),
	  m_HitPoint(),
	  m_Normal(),
	  m_Color(RGBColor::Black),
	  w(wr) {

}
