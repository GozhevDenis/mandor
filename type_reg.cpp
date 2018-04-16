#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <vector>

#include "type_reg.h"

#include "testConstMacros.h"
//#include "cfg_domain.h"		        ///< \todo Replace by \b dimensions.h.
//#include "test.h"      //only for test
//#include "log.h"

reg_t::reg_t(int Min[3], int Max[3], int Cpu, int Barcode, int Wrap[3])
{
	for(int axis = 0; axis < 3; ++axis){
			min[axis] = Min[axis];
			max[axis] = Max[axis];
			wrap[axis] = Wrap[axis];
	}
	cpu = Cpu;
	barcode = Barcode;
}
reg_t::reg_t(int Min[3], int Max[3])        //cpu, barcode, wrap??
{
	for(int axis = 0; axis < 3; ++axis) {
			min[axis] = Min[axis];
			max[axis] = Max[axis];
      wrap[axis] = 0;
	}
  cpu = -1;
  barcode = 0;

}

reg_t::reg_t(int Min0, int Min1, int Min2,
             int Max0, int Max1, int Max2)
{
    min[0] = Min0;
    min[1] = Min1;
    min[2] = Min2;
    max[0] = Max0;
    max[1] = Max1;
    max[2] = Max2;
    for(int axis = 0; axis < 3; ++axis)
      wrap[axis] = 0;
    cpu = -1;
    barcode = 0;
}

reg_t::reg_t(int Min0, int Min1, int Min2,
             int Max0, int Max1, int Max2,
             int Cpu,
             int Barcode,
             int Wrap0, int Wrap1, int Wrap2)
{
    min[0] = Min0;
    min[1] = Min1;
    min[2] = Min2;
    max[0] = Max0;
    max[1] = Max1;
    max[2] = Max2;
    cpu = Cpu;
    barcode = Barcode;
    wrap[0] = Wrap0;
    wrap[1] = Wrap1;
    wrap[2] = Wrap2;
}

reg_t::reg_t()
{
  for(int axis = 0; axis < 3; ++axis) {
		min[axis] = 0;
		max[axis] = 0;
		wrap[axis] = 0;
	}
	cpu = -1;
	barcode = 0;
}
// ---------------------------------------------------------------------------
/// Returns region's domain as string one may use with printf
//
//	Only one string!!
// ---------------------------------------------------------------------------

const char *
reg_t::printRanges()
{
	char buffer[200];
	snprintf (buffer, 200, "[%d %d] [%d %d] [%d %d]",
			min[0], max[0], min[1], max[1], min[2], max[2]);
	buffer[199] = 0;		// Ensures NULL terminator.
	return buffer;
}

const char *
reg_t::printCorners()
{
	char buffer[200];                          //тут наверно статик всё же нужен по смыслу(в оригинале статик, хотя надо думать для чего и как тут делать, если внутри класса то не нужен статик)
	snprintf (buffer, 200, "[%d %d %d] [%d %d %d]",
			min[0], min[1], min[2], max[0], max[1], max[2]);
	buffer[199] = 0;		// Ensures NULL terminator.
	return buffer;
}

const int *                     //warning!!! çàùèòà îò äóðàêà? getMin()[3] = max[0];  
reg_t::getMin()
{
  return min;
}

const int
reg_t::getMin(int axis)
{
  return min[axis];
}

const int *
reg_t::getMax()
{
  return max;
}

const int
reg_t::getMax(int axis)
{
  return max[axis];
}

const int *
reg_t::getWrap()
{
  return wrap;
}

const int
reg_t::getWrap(int axis)
{
  return wrap[axis];
}

const int
reg_t::getCpu()
{
  return cpu;
}

const int
reg_t::getBarcode()
{
  return barcode;
}
// ---------------------------------------------------------------------------
/// Returns true if 'reg' is inside of the 'dmn'.
// ---------------------------------------------------------------------------

int
reg_t::operator <= (const reg_t &dmn)
{
	if ( (!MC_X || (dmn.min[0] <= min[0] && dmn.max[0] >= max[0])) &&
		 (!MC_Y || (dmn.min[1] <= min[1] && dmn.max[1] >= max[1])) &&
		 (!MC_Z || (dmn.min[2] <= min[2] && dmn.max[2] >= max[2])) )
			return 1;
	return 0;
}

void
reg_t::setMin(int Min0, int Min1, int Min2)
{
  min[0] = Min0;
  min[1] = Min1;
  min[2] = Min2;
}

void
reg_t::setMin(int axis, int Min)
{
  min[axis] = Min;
}

void
reg_t::setMax(int Max0, int Max1, int Max2)
{
  max[0] = Max0;
  max[1] = Max1;
  max[2] = Max2;
}

void
reg_t::setMax(int axis, int Max)
{
  max[axis] = Max;
}

void
reg_t::setWrap(int Wrap0, int Wrap1, int Wrap2)
{
  max[0] = Wrap0;
  max[1] = Wrap1;
  max[2] = Wrap2;
}

void
reg_t::setWrap(int axis, int Wrap)
{
  wrap[axis] = Wrap;
}
// ---------------------------------------------------------------------------
/// Shifts region back to the normal position (inside of the actual
/// computational domain). Wrapping information stored in the reg_t::wrap field
/// is used to define the shift with no additional analysis.
// ---------------------------------------------------------------------------

void
reg_t::unwrap()
{
	for(int axis = 0; axis < 3; ++axis){
		min[axis] -= wrap[axis];
		max[axis] -= wrap[axis];
		wrap[axis] = 0;
	}
}

/**
  * Resets sizes along degenerated axises.
  */

void
reg_t::collapse()
{
  min[0] *= MC_X;
  min[1] *= MC_Y;
  min[2] *= MC_Z;
  max[0] *= MC_X;
  max[1] *= MC_Y;
  max[2] *= MC_Z;
  wrap[0] *= MC_X;
  wrap[1] *= MC_Y;
  wrap[2] *= MC_Z;
}
// ---------------------------------------------------------------------------
/// Calculates volume (number of nodes) of the region. Returns \b -1 in case of
/// badly sorted vertices of the region.
// ---------------------------------------------------------------------------

long long
reg_t::volume()         //const
{
	if ((MC_X && max[0] < min[0])
   	||  (MC_Y && max[1] < min[1])
   	||  (MC_Z && max[2] < min[2])){
      return -1;
   }
   long long res = 1;
   if (MC_X)										//directive #if used in original file
   		res *= (max[0] - min[0] + 1);
   if (MC_Y)
   		res *= (max[1] - min[1] + 1);
   if (MC_Z)
   		res *= (max[2] - min[2] + 1);

   return res;
}

const int
regList_t::getSize()
{
  return (list.size());
}

void
regList_t::push_back(const reg_t &reg)   
{
  list.push_back(reg);
}

void
regList_t::slice(int axis, int coord)
{
  assert(axis >= 0 && axis < 3 && !list.empty());
  auto end = list.end();                                //warning!!! after list.push_back (end+1) is not list.end()
  for (auto it = list.begin(); it != end; ++it) {
    if (it->getMin(axis) < coord && it->getMax(axis) > coord){
      reg_t r2 = *it;                                  // Copy of sliced region.
      it->setMax(axis, coord);
      r2.setMin(axis,coord);                           // Cuts top/bottoms out of two copies.
      list.push_back(r2);                              // New element added
    }
  }
}

void
regList_t::clear()
{
  list.clear();
}


// ---------------------------------------------------------------------------
/// \brief Checks that all elements have properly sorted vertices and all regions do not overlap. Returns \b 1 if there are any region with bad vertices,
/// and returns \b 2 if all regions are fine but come nodes are covered more than once.
// ---------------------------------------------------------------------------
const int
regList_t::verify()
{
  if (!list.empty())                  ////?? Why is not it assert? return 0?
  {
    for (auto it = list.begin(); it != list.end(); ++it)
      if(it->volume() <= 0)                                                     // Checks that all regions are sorted normally.
        return 1;
    for (auto it1 = list.begin(); it1 != list.end(); ++it1)
      for(auto it2 = it1 + 1; it2 != list.end(); ++it2)                       // Checks that there are no overlapping.
        if ( (MC_X && it1->getMin(0) <= it2->getMax(0) && it1->getMax(0) >= it2->getMin(0)) ||
             (MC_Y && it1->getMin(1) <= it2->getMax(1) && it1->getMax(1) >= it2->getMin(1)) ||
             (MC_Z && it1->getMin(2) <= it2->getMax(2) && it1->getMax(2) >= it2->getMin(2)) )
          return 2;
  }
  return 0;
}
/*long long
reg_tlist::distrib()
{
  int result res;
  reg_t *reg;
  const reg_t, *node = map->list;

  for(int i = 0; )
}*/

