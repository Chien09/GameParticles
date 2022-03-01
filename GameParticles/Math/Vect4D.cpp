//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <math.h>
#include "Vect4D.h"

Vect4D::Vect4D()
	:x(0.0f), y(0.0f), z(0.0f), w(1.0f)
{
	/*this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = 1.0f;*/
}

Vect4D::Vect4D(const float tx, const float ty, const float tz, const float tw)
	:x(tx), y(ty), z(tz), w(tw)
{
	/*this->x = tx;
	this->y = ty;
	this->z = tz;
	this->w = tw;*/
}


Vect4D::~Vect4D()
{
	// nothing to delete
}

void Vect4D::norm(Vect4D& out)
{

	Vect4D tmp;

	//_mm_sqrt_ps() --> sqrt()   _mm_dp_ps --> dot product masking position 0X77 
	tmp._m = _mm_sqrt_ps(_mm_dp_ps(this->_m, this->_m, 0X77));

	//_mm_div_ps --> divide () to Normalize vector and set x,y,z,w
	out._m = _mm_div_ps(this->_m, tmp._m);
	out.w = 1.0f;


	//float mag = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);

	//if (0.0f < mag)
	//{
	//	out.x = this->x / mag;
	//	out.y = this->y / mag;
	//	out.z = this->z / mag;
	//	out.w = 1.0f;
	//}
}


const Vect4D Vect4D::operator + (const Vect4D t) const
{
	//Vect4D out;

	//out.x = this->x + t.x;
	//out.y = this->y + t.y;
	//out.z = this->z + t.z;

	return Vect4D(this->x + t.x, this->y + t.y, this->z +t.z);  //RVO
}

const Vect4D Vect4D::operator - (const Vect4D t) const
{
	//Vect4D out;

	//out.x = this->x - t.x;
	//out.y = this->y - t.y;
	//out.z = this->z - t.z;

	return Vect4D(this->x - t.x, this->y - t.y, this->z - t.z); //RVO
}

const Vect4D Vect4D::operator *(const float scale) const
{
	//Vect4D tmp;

	//tmp.x = this->x * scale;
	//tmp.y = this->y * scale;
	//tmp.z = this->z * scale;

	return Vect4D(this->x * scale, this->y * scale, this->z * scale); //RVO
}



float& Vect4D::operator[](VECT_ENUM e)
{
	switch (e)
	{
	case 0:
		return x;
		break;
	case 1:
		return y;
		break;
	case 2:
		return z;
		break;
	case 3:
		return w;
		break;
	default:
		assert(0);
		return x;
	}
}

void Vect4D::Cross(const Vect4D& vin, Vect4D& vout) const
{
	Vect4D tmpresult;

	tmpresult._m = _mm_sub_ps(
		_mm_mul_ps(this->_m, _mm_shuffle_ps(vin._m, vin._m, _MM_SHUFFLE(3, 0, 2, 1))),
		_mm_mul_ps(vin._m, _mm_shuffle_ps(this->_m, this->_m, _MM_SHUFFLE(3, 0, 2, 1)))); 

	vout._m = _mm_shuffle_ps(tmpresult._m, tmpresult._m, _MM_SHUFFLE(3, 0, 2, 1));

	//Reference for CrossProduct http://fastcpp.blogspot.com/2011/04/vector-cross-product-using-sse-code.html

	//vout.x = (y*vin.z - z * vin.y);
	//vout.y = (z*vin.x - x * vin.z);
	//vout.z = (x*vin.y - y * vin.x);
	//vout.w = 1.0f;
}

void Vect4D::set(const float tx, const float ty, const float tz, const float tw)
{
	this->_m = _mm_set_ps(tw, tz, ty, tx); //in reverse order 
	//this->x = tx;
	//this->y = ty;
	//this->z = tz;
	//this->w = tw;
	
}

// End of file
