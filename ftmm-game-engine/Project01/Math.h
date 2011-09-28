#ifndef __Math_H__
#define __Math_H__

class Radian
{
	public:
		float mRad;
		
		explicit Radian ( float r=0 ) : mRad(r) {};

		Radian& operator = ( const float& f );
		Radian& operator = ( const Radian& r );

		float valueRadians() const;

		Radian operator - ( const Radian& r ) const;

		bool operator <  ( const Radian& r ) const;
		bool operator >  ( const Radian& r ) const;
};

#endif