
#include "Math.h"

Radian& Radian::operator= ( const float& f ) 
{ mRad = f; return *this; }

Radian& Radian::operator= ( const Radian& r ) 
{ mRad = r.mRad; return *this; }

float Radian::valueRadians() const 
{ return mRad; }

Radian Radian::operator- ( const Radian& r ) const 
{ return Radian ( mRad - r.mRad ); }

bool Radian::operator<  ( const Radian& r ) const 
{ return mRad <  r.mRad; }

bool Radian::operator>  ( const Radian& r ) const 
{ return mRad >  r.mRad; }