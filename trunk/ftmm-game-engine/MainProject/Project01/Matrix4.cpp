#include "Matrix4.h"

Matrix4::Matrix4(
float m00, float m01, float m02, float m03,
float m10, float m11, float m12, float m13,
float m20, float m21, float m22, float m23,
float m30, float m31, float m32, float m33 )
{
	m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
	m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
	m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
	m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
}

 bool Matrix4::operator == ( const Matrix4& m2 ) const
{
	if( 
		m[0][0] != m2.m[0][0] || m[0][1] != m2.m[0][1] || m[0][2] != m2.m[0][2] || m[0][3] != m2.m[0][3] ||
		m[1][0] != m2.m[1][0] || m[1][1] != m2.m[1][1] || m[1][2] != m2.m[1][2] || m[1][3] != m2.m[1][3] ||
		m[2][0] != m2.m[2][0] || m[2][1] != m2.m[2][1] || m[2][2] != m2.m[2][2] || m[2][3] != m2.m[2][3] ||
		m[3][0] != m2.m[3][0] || m[3][1] != m2.m[3][1] || m[3][2] != m2.m[3][2] || m[3][3] != m2.m[3][3] )
	return false;
	// "else"
	return true;
}

bool Matrix4::operator != ( const Matrix4& m2 ) const
{
	if( 
		m[0][0] != m2.m[0][0] || m[0][1] != m2.m[0][1] || m[0][2] != m2.m[0][2] || m[0][3] != m2.m[0][3] ||
		m[1][0] != m2.m[1][0] || m[1][1] != m2.m[1][1] || m[1][2] != m2.m[1][2] || m[1][3] != m2.m[1][3] ||
		m[2][0] != m2.m[2][0] || m[2][1] != m2.m[2][1] || m[2][2] != m2.m[2][2] || m[2][3] != m2.m[2][3] ||
		m[3][0] != m2.m[3][0] || m[3][1] != m2.m[3][1] || m[3][2] != m2.m[3][2] || m[3][3] != m2.m[3][3] )
	return true;
	//"else"
	return false;
}

Matrix4 Matrix4:: operator * (const Matrix4 &m2) const
{
	Matrix4 r;

	r.m[0][0] = m[0][0] * m2.m[0][0] + m[0][1] * m2.m[1][0] + m[0][2] * m2.m[2][0] + m[0][3] * m2.m[3][0];
	r.m[0][1] = m[0][0] * m2.m[0][1] + m[0][1] * m2.m[1][1] + m[0][2] * m2.m[2][1] + m[0][3] * m2.m[3][1];
	r.m[0][2] = m[0][0] * m2.m[0][2] + m[0][1] * m2.m[1][2] + m[0][2] * m2.m[2][2] + m[0][3] * m2.m[3][2];
	r.m[0][3] = m[0][0] * m2.m[0][3] + m[0][1] * m2.m[1][3] + m[0][2] * m2.m[2][3] + m[0][3] * m2.m[3][3];

	r.m[1][0] = m[1][0] * m2.m[0][0] + m[1][1] * m2.m[1][0] + m[1][2] * m2.m[2][0] + m[1][3] * m2.m[3][0];
	r.m[1][1] = m[1][0] * m2.m[0][1] + m[1][1] * m2.m[1][1] + m[1][2] * m2.m[2][1] + m[1][3] * m2.m[3][1];
	r.m[1][2] = m[1][0] * m2.m[0][2] + m[1][1] * m2.m[1][2] + m[1][2] * m2.m[2][2] + m[1][3] * m2.m[3][2];
	r.m[1][3] = m[1][0] * m2.m[0][3] + m[1][1] * m2.m[1][3] + m[1][2] * m2.m[2][3] + m[1][3] * m2.m[3][3];

	r.m[2][0] = m[2][0] * m2.m[0][0] + m[2][1] * m2.m[1][0] + m[2][2] * m2.m[2][0] + m[2][3] * m2.m[3][0];
	r.m[2][1] = m[2][0] * m2.m[0][1] + m[2][1] * m2.m[1][1] + m[2][2] * m2.m[2][1] + m[2][3] * m2.m[3][1];
	r.m[2][2] = m[2][0] * m2.m[0][2] + m[2][1] * m2.m[1][2] + m[2][2] * m2.m[2][2] + m[2][3] * m2.m[3][2];
	r.m[2][3] = m[2][0] * m2.m[0][3] + m[2][1] * m2.m[1][3] + m[2][2] * m2.m[2][3] + m[2][3] * m2.m[3][3];

	r.m[3][0] = m[3][0] * m2.m[0][0] + m[3][1] * m2.m[1][0] + m[3][2] * m2.m[2][0] + m[3][3] * m2.m[3][0];
	r.m[3][1] = m[3][0] * m2.m[0][1] + m[3][1] * m2.m[1][1] + m[3][2] * m2.m[2][1] + m[3][3] * m2.m[3][1];
	r.m[3][2] = m[3][0] * m2.m[0][2] + m[3][1] * m2.m[1][2] + m[3][2] * m2.m[2][2] + m[3][3] * m2.m[3][2];
	r.m[3][3] = m[3][0] * m2.m[0][3] + m[3][1] * m2.m[1][3] + m[3][2] * m2.m[2][3] + m[3][3] * m2.m[3][3];

	return r;
}

Vector4 Matrix4::operator *( const Vector4 & v) const
{
	Vector4 result = Vector4(0.0,0.0,0.0,0.0);
	
	result.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
	result.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
	result.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
	result.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;

	return result;

}

Matrix4 Matrix4::operator + ( const Matrix4 &m2 ) const
{
	Matrix4 r;

	r.m[0][0] = m[0][0] + m2.m[0][0];
	r.m[0][1] = m[0][1] + m2.m[0][1];
	r.m[0][2] = m[0][2] + m2.m[0][2];
	r.m[0][3] = m[0][3] + m2.m[0][3];

	r.m[1][0] = m[1][0] + m2.m[1][0];
	r.m[1][1] = m[1][1] + m2.m[1][1];
	r.m[1][2] = m[1][2] + m2.m[1][2];
	r.m[1][3] = m[1][3] + m2.m[1][3];

	r.m[2][0] = m[2][0] + m2.m[2][0];
	r.m[2][1] = m[2][1] + m2.m[2][1];
	r.m[2][2] = m[2][2] + m2.m[2][2];
	r.m[2][3] = m[2][3] + m2.m[2][3];

	r.m[3][0] = m[3][0] + m2.m[3][0];
	r.m[3][1] = m[3][1] + m2.m[3][1];
	r.m[3][2] = m[3][2] + m2.m[3][2];
	r.m[3][3] = m[3][3] + m2.m[3][3];

	return r;
}

Matrix4 Matrix4::operator - ( const Matrix4 &m2 ) const
{
	Matrix4 r;

	r.m[0][0] = m[0][0] - m2.m[0][0];
	r.m[0][1] = m[0][1] - m2.m[0][1];
	r.m[0][2] = m[0][2] - m2.m[0][2];
	r.m[0][3] = m[0][3] - m2.m[0][3];

	r.m[1][0] = m[1][0] - m2.m[1][0];
	r.m[1][1] = m[1][1] - m2.m[1][1];
	r.m[1][2] = m[1][2] - m2.m[1][2];
	r.m[1][3] = m[1][3] - m2.m[1][3];

	r.m[2][0] = m[2][0] - m2.m[2][0];
	r.m[2][1] = m[2][1] - m2.m[2][1];
	r.m[2][2] = m[2][2] - m2.m[2][2];
	r.m[2][3] = m[2][3] - m2.m[2][3];

	r.m[3][0] = m[3][0] - m2.m[3][0];
	r.m[3][1] = m[3][1] - m2.m[3][1];
	r.m[3][2] = m[3][2] - m2.m[3][2];
	r.m[3][3] = m[3][3] - m2.m[3][3];

	return r;
}

Matrix4 Matrix4::transpose(void) const
{
	return Matrix4(m[0][0], m[1][0], m[2][0], m[3][0],
		m[0][1], m[1][1], m[2][1], m[3][1],
		m[0][2], m[1][2], m[2][2], m[3][2],
		m[0][3], m[1][3], m[2][3], m[3][3]);
}


void Matrix4::setTrans( const Vector3& v )
{
	m[0][3] = v.x;
	m[1][3] = v.y;
	m[2][3] = v.z;
}

Vector3 Matrix4::getTrans() const
{
	return Vector3(m[0][3], m[1][3], m[2][3]);
}

void Matrix4::makeTrans( const Vector3& v )
{
	m[0][0] = 1.0; m[0][1] = 0.0; m[0][2] = 0.0; m[0][3] = v.x;
	m[1][0] = 0.0; m[1][1] = 1.0; m[1][2] = 0.0; m[1][3] = v.y;
	m[2][0] = 0.0; m[2][1] = 0.0; m[2][2] = 1.0; m[2][3] = v.z;
	m[3][0] = 0.0; m[3][1] = 0.0; m[3][2] = 0.0; m[3][3] = 1.0;
}

// I removed static here but kept it in the header. So if errors occur maybe something to look into
Matrix4 Matrix4::getTrans( const Vector3& v ) 
{
	Matrix4 r;

	r.m[0][0] = 1.0; r.m[0][1] = 0.0; r.m[0][2] = 0.0; r.m[0][3] = v.x;
	r.m[1][0] = 0.0; r.m[1][1] = 1.0; r.m[1][2] = 0.0; r.m[1][3] = v.y;
	r.m[2][0] = 0.0; r.m[2][1] = 0.0; r.m[2][2] = 1.0; r.m[2][3] = v.z;
	r.m[3][0] = 0.0; r.m[3][1] = 0.0; r.m[3][2] = 0.0; r.m[3][3] = 1.0;

	return r;
}

void Matrix4::setScale( const Vector3& v )
{
	m[0][0] = v.x;
	m[1][1] = v.y;
	m[2][2] = v.z;
}


Vector3 Matrix4::getScale() const{


	return Vector3(m[0][0],m[1][1],m[2][2]);
}

// I removed static here, so if it causes bugs look into it
/*
Matrix4 Matrix4::getScale( const Vector3& v )
{
	Matrix4 r;
	r.m[0][0] = v.x; r.m[0][1] = 0.0; r.m[0][2] = 0.0; r.m[0][3] = 0.0;
	r.m[1][0] = 0.0; r.m[1][1] = v.y; r.m[1][2] = 0.0; r.m[1][3] = 0.0;
	r.m[2][0] = 0.0; r.m[2][1] = 0.0; r.m[2][2] = v.z; r.m[2][3] = 0.0;
	r.m[3][0] = 0.0; r.m[3][1] = 0.0; r.m[3][2] = 0.0; r.m[3][3] = 1.0;

	return r;
}
*/
void Matrix4::extract3x3Matrix(Matrix3& m3x3) const
{
	m3x3.m[0][0] = m[0][0];
	m3x3.m[0][1] = m[0][1];
	m3x3.m[0][2] = m[0][2];
	m3x3.m[1][0] = m[1][0];
	m3x3.m[1][1] = m[1][1];
	m3x3.m[1][2] = m[1][2];
	m3x3.m[2][0] = m[2][0];
	m3x3.m[2][1] = m[2][1];
	m3x3.m[2][2] = m[2][2];
}


const Matrix4 Matrix4::ZERO(
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0 );



const Matrix4 Matrix4::IDENTITY(
1, 0, 0, 0,
0, 1, 0, 0,
0, 0, 1, 0,
0, 0, 0, 1 );

void Matrix4::fromMatrix3( const Matrix3& mt3 )
{
	m[0][0] = mt3[0][0];
	m[0][1] = mt3[0][1];
	m[0][2] = mt3[0][2];
	m[0][3] = 0;
	m[1][0] = mt3[1][0];
	m[1][1] = mt3[1][1];
	m[1][2] = mt3[1][2];
	m[1][3] = 0;
	m[2][0] = mt3[2][0];
	m[2][1] = mt3[2][1];
	m[2][2] = mt3[2][2];
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

