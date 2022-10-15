#include "framework.h"

#include "includes.h"
#include <cassert>
#include <cmath> //for sqrt (square root) function
#include <math.h> //atan2


#ifndef M_PI_2
    #define M_PI_2 1.57079632679489661923
#endif

//**************************************
float Vector2::distance(const Vector2& v)
{
	return float((v - *this).length());
}

float Vector2::dot( const Vector2& v )
{
	return x * v.x + y * v.y;
}

float Vector2::perpdot( const Vector2& v )
{
	return y * v.x + -x * v.y;
}

void Vector2::random(float range)
{
	//rand returns a value between 0 and RAND_MAX
	x = (rand() / (float)RAND_MAX) * 2.0f * range - range; //value between -range and range
	y = (rand() / (float)RAND_MAX) * 2.0f * range - range; //value between -range and range
}


Vector2 operator * (const Vector2& a, float v) { return Vector2(a.x * v, a.y * v); }
Vector2 operator + (const Vector2& a, const Vector2& b) { return Vector2(a.x + b.x, a.y + b.y); }
Vector2 operator - (const Vector2& a, const Vector2& b) { return Vector2(a.x - b.x, a.y - b.y); }


// **************************************

double Vector3::length() 
{
	return sqrt(x*x + y*y + z*z);
}

double Vector3::length() const
{
	return sqrt(x*x + y*y + z*z);
}

Vector3& Vector3::normalize()
{
	double len = length();
	x = float(x / len);
	y = float(y / len);
	z = float(z / len);
	return *this;
}

float Vector3::distance(const Vector3& v) const
{
	return float((v - *this).length());
}

Vector3 Vector3::cross( const Vector3& b ) const
{
	return Vector3(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);
}

float Vector3::dot( const Vector3& v ) const
{
	return x*v.x + y*v.y + z*v.z;
}

void Vector3::random(float range)
{
	//rand returns a value between 0 and RAND_MAX
	x = (rand() / (float)RAND_MAX) * 2.0f * range - range; //value between -range and range
	y = (rand() / (float)RAND_MAX) * 2.0f * range - range; //value between -range and range
	z = (rand() / (float)RAND_MAX) * 2.0f * range - range; //value between -range and range
}

void Vector3::random(Vector3 range)
{
	//rand returns a value between 0 and RAND_MAX
	x = (rand() / (float)RAND_MAX) * 2.0f * range.x - range.x; //value between -range and range
	y = (rand() / (float)RAND_MAX) * 2.0f * range.y - range.y; //value between -range and range
	z = (rand() / (float)RAND_MAX) * 2.0f * range.z - range.z; //value between -range and range
}


Vector3 Vector3::lerp(const Vector3& end, float percentatge)
{
	return (*this + ((end - *this) * percentatge));
}


//*********************************
Matrix44::Matrix44()
{
	setIdentity();
}

Matrix44& Matrix44::clear()
{
	memset(m, 0, 16*sizeof(float));
   return *this;
}

Matrix44& Matrix44::setIdentity()
{
	m[0]=1; m[4]=0; m[8]=0; m[12]=0;
	m[1]=0; m[5]=1; m[9]=0; m[13]=0;
	m[2]=0; m[6]=0; m[10]=1; m[14]=0;
	m[3]=0; m[7]=0; m[11]=0; m[15]=1;
   return *this;
}

Matrix44& Matrix44::transpose()
{
   std::swap(m[1],m[4]); std::swap(m[2],m[8]); std::swap(m[3],m[12]);
   std::swap(m[6],m[9]); std::swap(m[7],m[13]); std::swap(m[11],m[14]);
   return *this;
}

void Matrix44::traslate(float x, float y, float z)
{
	Matrix44 T;
	T.setTranslation(x, y, z);
	*this = *this * T;
}

void Matrix44::rotate( float angle_in_rad, const Vector3& axis )
{
	Matrix44 R;
	R.setRotation(angle_in_rad, axis);
	*this = *this * R;
}

void Matrix44::scale( float x, float y, float z )
{
	Matrix44 S;
	S.setScale(x,y,z);
	*this = *this * S;
}

Vector3 Matrix44::rotateVector(const Vector3& v)
{
	Matrix44 temp = *this;
	temp.m[12] = 0.0;
	temp.m[13] = 0.0;
	temp.m[14] = 0.0;
	return temp * v;
}

void Matrix44::traslateLocal(float x, float y, float z)
{
	Matrix44 T;
	T.setTranslation(x, y, z);
	*this = T * *this;
}

void Matrix44::rotateLocal( float angle_in_rad, const Vector3& axis )
{
	Matrix44 R;
	R.setRotation(angle_in_rad, axis);
	*this = R * *this;
}

//To create a traslation matrix
void Matrix44::setTranslation(float x, float y, float z)
{
	setIdentity();
	m[12] = x;
	m[13] = y;
	m[14] = z;
}

//To create a traslation matrix
void Matrix44::setScale(float x, float y, float z)
{
	setIdentity();
	m[0] = x;
	m[5] = y;
	m[10] = z;
}

//To create a rotation matrix
void Matrix44::setRotation( float angle_in_rad, const Vector3& axis  )
{
	clear();
	Vector3 axis_n = axis;
	axis_n.normalize();

	float c = cos( angle_in_rad );
	float s = sin( angle_in_rad );
	float t = 1 - c;

	M[0][0] = t * axis_n.x * axis_n.x + c;
	M[0][1] = t * axis_n.x * axis_n.y - s * axis_n.z;
	M[0][2] = t * axis_n.x * axis_n.z + s * axis_n.y;

	M[1][0] = t * axis_n.x * axis_n.y + s * axis_n.z;
	M[1][1] = t * axis_n.y * axis_n.y + c;
	M[1][2] = t * axis_n.y * axis_n.z - s * axis_n.x;

	M[2][0] = t * axis_n.x * axis_n.z - s * axis_n.y;
	M[2][1] = t * axis_n.y * axis_n.z + s * axis_n.x;
	M[2][2] = t * axis_n.z * axis_n.z + c;

	M[3][3] = 1.0f;
}

Matrix44 Matrix44::getRotationOnly()
{
	Matrix44 trans = *this;
	trans.transpose();

	Matrix44 inv = *this;
	inv.inverse();

	return trans * inv;
}

void Matrix44::lookAt(Vector3& eye, Vector3& center, Vector3& up)
{
	Vector3 front = (center - eye);
	front.normalize();
	Vector3 right = front.cross( up );
	right.normalize();
	Vector3 top = right.cross(front);
	top.normalize();

	setIdentity();

	M[0][0] = right.x; M[0][1] = top.x; M[0][2] = -front.x;
	M[1][0] = right.y; M[1][1] = top.y; M[1][2] = -front.y;
	M[2][0] = right.z; M[2][1] = top.z; M[2][2] = -front.z;

	traslateLocal(-eye.x, -eye.y, -eye.z);
}

//double check this functions
void Matrix44::perspective(float fov, float aspect, float near_plane, float far_plane)
{
	setIdentity();

	float f = 1.0f / tan( fov * float(DEG2RAD) * 0.5f );

	M[0][0] = f / aspect;
	M[1][1] = f;
	M[2][2] = (far_plane + near_plane) / (near_plane - far_plane);
	M[2][3] = -1.0f;
	M[3][2] = 2.0f * (far_plane * near_plane) / (near_plane - far_plane);
	M[3][3] = 0.0f;
}

void Matrix44::ortho(float left, float right, float bottom, float top, float near_plane, float far_plane)
{
	clear();
	M[0][0] = 2.0f / (right - left);
	M[3][0] = - (right + left) / (right - left);
	M[1][1] = 2.0f / (top - bottom); 
	M[3][1] = -(top + bottom) / (top - bottom);
	M[2][2] = -2.0f / (far_plane - near_plane);
	M[3][2] = (far_plane + near_plane) / (far_plane - near_plane);
	M[3][3] = 1.0f;
}

//applies matrix projection to vector (returns in normalized coordinates)
Vector3 Matrix44::project(const Vector3& v) 
{   
	float x = m[0] * v.x + m[4] * v.y + m[8] * v.z + m[12]; 
	float y = m[1] * v.x + m[5] * v.y + m[9] * v.z + m[13]; 
	float z = m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14];
	float w = m[3] * v.x + m[7] * v.y + m[11] * v.z + m[15];

	return Vector3( (x / w + 1.0f) / 2.0f, (y / w + 1.0f) / 2.0f,  (z / w + 1.0f) / 2.0f );
}

bool Matrix44::getXYZ(float* euler) const
{
// Code adapted from www.geometrictools.com
//	Matrix3<Real>::EulerResult Matrix3<Real>::ToEulerAnglesXYZ 
    // +-           -+   +-                                        -+
    // | r00 r01 r02 |   |  cy*cz           -cy*sz            sy    |
    // | r10 r11 r12 | = |  cz*sx*sy+cx*sz   cx*cz-sx*sy*sz  -cy*sx |
    // | r20 r21 r22 |   | -cx*cz*sy+sx*sz   cz*sx+cx*sy*sz   cx*cy |
    // +-           -+   +-                                        -+
    if (_13 < 1.0f)
    {
        if (_13 > - 1.0f)
        {
            // y_angle = asin(r02)
            // x_angle = atan2(-r12,r22)
            // z_angle = atan2(-r01,r00)
            euler[1] = asinf(_13);
            euler[0] = atan2f(-_23,_33);
            euler[2] = atan2f(-_12,_11);
            return true;
        }
        else
        {
            // y_angle = -pi/2
            // z_angle - x_angle = atan2(r10,r11)
            // WARNING.  The solution is not unique.  Choosing z_angle = 0.
            euler[1] = (float)-M_PI_2;
            euler[0] = -atan2f(_21,_22);
            euler[2] = 0.0f;
            return false;
        }
    }
    else
    {
        // y_angle = +pi/2
        // z_angle + x_angle = atan2(r10,r11)
        // WARNING.  The solutions is not unique.  Choosing z_angle = 0.
        euler[1] = (float)M_PI_2;
        euler[0] = atan2f(_21,_22);
        euler[2] = 0.0f;
    }
	return false;
}

//Multiply a matrix by another and returns the result
Matrix44 Matrix44::operator*(const Matrix44& matrix) const
{
	Matrix44 ret;

	unsigned int i,j,k;
	for (i=0;i<4;i++) 	
	{
		for (j=0;j<4;j++) 
		{
			ret.M[i][j]=0.0;
			for (k=0;k<4;k++) 
				ret.M[i][j] += M[i][k] * matrix.M[k][j];
		}
	}

	return ret;
}

//it allows to add two vectors
Vector3 operator + (const Vector3& a, const Vector3& b) 
{
	return Vector3(a.x + b.x, a.y + b.y, a.z + b.z );
}

//it allows to add two vectors
Vector3 operator - (const Vector3& a, const Vector3& b) 
{
	return Vector3(a.x - b.x, a.y - b.y, a.z - b.z );
}

Vector3 operator * (const Vector3& a, float v) 
{
	return Vector3(a.x * v, a.y * v, a.z * v);
}

//Multiplies a vector by a matrix and returns the new vector
Vector3 operator * (const Matrix44& matrix, const Vector3& v) 
{   
   float x = matrix.m[0] * v.x + matrix.m[4] * v.y + matrix.m[8] * v.z + matrix.m[12]; 
   float y = matrix.m[1] * v.x + matrix.m[5] * v.y + matrix.m[9] * v.z + matrix.m[13]; 
   float z = matrix.m[2] * v.x + matrix.m[6] * v.y + matrix.m[10] * v.z + matrix.m[14];
   return Vector3(x,y,z);
}

void Matrix44::setUpAndOrthonormalize(Vector3 up)
{
	up.normalize();

	//put the up vector in the matrix
	m[4] = up.x;
	m[5] = up.y;
	m[6] = up.z;

	//orthonormalize
	Vector3 right,front;
	right = rightVector();

	if ( abs(right.dot( up )) < 0.99998 )
	{
		right = up.cross( frontVector() );
		front = right.cross( up );
	}
	else
	{
		front = Vector3(right).cross( up );
		right = up.cross( front );
	}

	right.normalize();
	front.normalize();

	m[8] = front.x;
	m[9] = front.y;
	m[10] = front.z;

	m[0] = right.x;
	m[1] = right.y;
	m[2] = right.z;
}

void Matrix44::setFrontAndOrthonormalize(Vector3 front)
{
	front.normalize();

	//put the up vector in the matrix
	m[8] = front.x;
	m[9] = front.y;
	m[10] = front.z;

	//orthonormalize
	Vector3 right,up;
	right = rightVector();

	if ( abs(right.dot( front )) < 0.99998 )
	{
		right = topVector().cross( front  );
		up = front.cross( right );
	}
	else
	{
		up = front.cross( right );
		right = up.cross( front );
	}

	right.normalize();
	up.normalize();

	m[4] = up.x;
	m[5] = up.y;
	m[6] = up.z;

	m[0] = right.x;
	m[1] = right.y;
	m[2] = right.z;
	
}

bool Matrix44::inverse()
{
   unsigned int i, j, k, swap;
   float t;
   Matrix44 temp, final;
   final.setIdentity();

   temp = (*this);

   unsigned int m,n;
   m = n = 4;
	
   for (i = 0; i < m; i++)
   {
      // Look for largest element in column

      swap = i;
      for (j = i + 1; j < m; j++)// m or n
	  {
		 if ( fabs(temp.M[j][i]) > fabs( temp.M[swap][i]) )
            swap = j;
	  }
   
      if (swap != i)
      {
         // Swap rows.
         for (k = 0; k < n; k++)
         {
			 std::swap( temp.M[i][k],temp.M[swap][k]);
			 std::swap( final.M[i][k], final.M[swap][k]);
         }
      }

      // No non-zero pivot.  The CMatrix is singular, which shouldn't
      // happen.  This means the user gave us a bad CMatrix.


#define MATRIX_SINGULAR_THRESHOLD 0.00001 //change this if you experience problems with matrices

      if ( fabsf(temp.M[i][i]) <= MATRIX_SINGULAR_THRESHOLD)
	  {
		  final.setIdentity();
         return false;
	  }
#undef MATRIX_SINGULAR_THRESHOLD

      t = 1.0f/temp.M[i][i];

      for (k = 0; k < n; k++)//m or n
      {
         temp.M[i][k] *= t;
         final.M[i][k] *= t;
      }

      for (j = 0; j < m; j++) // m or n
      {
         if (j != i)
         {
            t = temp.M[j][i];
            for (k = 0; k < n; k++)//m or n
            {
               temp.M[j][k] -= (temp.M[i][k] * t);
               final.M[j][k] -= (final.M[i][k] * t);
            }
         }
      }
   }

   *this = final;

   return true;
}

float ComputeSignedAngle( Vector2 a, Vector2 b)
{
	a.normalize();
	b.normalize();
	return atan2(a.perpdot(b), a.dot(b) );
}

Vector3 RayPlaneCollision( const Vector3& plane_pos, const Vector3& plane_normal, const Vector3& ray_origin, const Vector3& ray_dir )
{
    double D = plane_pos.dot(plane_normal);
    double numer = plane_normal.dot(ray_origin) + D;
    double denom = plane_normal.dot(ray_dir);
    float t = (float)-(numer / denom);
	return ray_origin + ray_dir * t;
}
