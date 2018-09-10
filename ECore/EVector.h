#pragma once

#include "ECommon.h"
#include "EMath.h"
#include "EUtil.h"

namespace E3D
{
    struct EVector2D 
    {
        static EVector2D ZERO;
        static EVector2D UNIT_X;
        static EVector2D UNIT_Y;

        EFloat x;
        EFloat y;

        EVector2D() : x(0), y(0){}
        EVector2D(EFloat xf, EFloat yf) : x(xf), y(yf){}
        EVector2D(const EVector2D &v) : x(v.x), y(v.y){}

        //length of the vector
        inline EFloat length() const
        {
            return sqrt(x*x + y * y);
        }

        //normalize
        inline EFloat normalize()
        {
            EFloat len = length();
            if (len > EPSILON_E6) {
                EFloat invLen = 1.0f / len;
                x *= invLen;
                y *= invLen;
            }
            return len;
        }

        //dotproduct
        inline EFloat dotProduct(const EVector2D &right) const
        {
            return x * right.x + y * right.y;
        }

        //return the angle between two vectors, radian
        inline EFloat angleBetween(const EVector2D &right) const
        {
            EFloat lenProduct = length() * right.length();

            //check zero
            if (lenProduct < EPSILON_E6)
                lenProduct = EPSILON_E6;

            EFloat f = dotProduct(right) / lenProduct;
            f = Clamp(f, -1.0f, 1.0f);
            return acos(f);
        }

        //check length is zero or not
        inline bool isZero() const
        {
            return length() < EPSILON_E6;
        }

        //get squared length
        inline EFloat squareLength() const
        {
            return x * x + y * y;
        }

        //operator * :vector * number 
        inline EVector2D operator * (float right) const
        {
            return EVector2D(x * right, y * right);
        }

        //operator * :vector * vector
        inline EVector2D operator * (const EVector2D &right) const
        {
            return EVector2D(x * right.x, y * right.y);
        }

        //operator + : vec + vec
        inline EVector2D operator + (const EVector2D &right) const
        {
            return EVector2D(x + right.x, y + right.y);
        }

        //operator - : vec - vec
        inline EVector2D operator - (const EVector2D &right) const
        {
            return EVector2D(x - right.x, y - right.y);
        }

        //negation -
        inline EVector2D operator - ()
        {
            x = -x;
            y = -y;
            return *this;
        }

        //positive +
        inline EVector2D operator + ()
        {
            x = +x;
            y = +y;
            return *this;
        }

        //equal ==
        inline bool operator == (const EVector2D &right) const
        {
            return EqualFloat(x, right.x) && EqualFloat(y, right.y);
        }

        //vector assign =
        inline EVector2D operator = (const EVector2D &right)
        {
            x = right.x;
            y = right.y;
            return *this;
        }
    };

    struct EVector3D
    {
        static EVector3D ZERO;
        static EVector3D UNIT_X;
        static EVector3D UNIT_Y;
        static EVector3D UNIT_Z;


        EFloat x;
        EFloat y;
        EFloat z;

        EVector3D() : x(0), y(0), z(0) {}
        EVector3D(EFloat xf, EFloat yf, EFloat zf) : x(xf), y(yf), z(zf) {}
        EVector3D(const EVector3D &v) : x(v.x), y(v.y), z(v.z) {}

        //length of the vector
        inline EFloat length() const
        {
            return sqrt(x*x + y * y + z * z);
        }

        //normalize
        inline EFloat normalize()
        {
            EFloat len = length();
            if (len > EPSILON_E6) {
                EFloat invLen = 1.0f / len;
                x *= invLen;
                y *= invLen;
                z *= invLen;
            }
            return len;
        }

        //dotproduct
        inline EFloat dotProduct(const EVector3D &right) const
        {
            return x * right.x + y * right.y + z * right.z;
        }

        //cross product
        inline EVector3D crossProduct(const EVector3D &right) const
        {
            return EVector3D(y * right.z - z * right.y, z*right.x - x * right.z, x*right.y - y * right.x);
        }

        //return the angle between two vectors, radian
        inline EFloat angleBetween(const EVector3D &right) const
        {
            EFloat lenProduct = length() * right.length();

            //check zero
            if (lenProduct < EPSILON_E6)
                lenProduct = EPSILON_E6;

            EFloat f = dotProduct(right) / lenProduct;
            f = Clamp(f, -1.0f, 1.0f);
            return acos(f);
        }

        //check length is zero or not
        inline bool isZero() const
        {
            return length() < EPSILON_E6;
        }

        //get squared length
        inline EFloat squareLength() const
        {
            return x * x + y * y + z * z;
        }

        //operator * :vector * number 
        inline EVector3D operator * (float right) const
        {
            return EVector3D(x * right, y * right, z * right);
        }

        //operator * :vector * vector
        inline EVector3D operator * (const EVector3D &right) const
        {
            return EVector3D(x * right.x, y * right.y, z * right.z);
        }

        //operator + : vec + vec
        inline EVector3D operator + (const EVector3D &right) const
        {
            return EVector3D(x + right.x, y + right.y, z + right.z);
        }

        //operator - : vec - vec
        inline EVector3D operator - (const EVector3D &right) const
        {
            return EVector3D(x - right.x, y - right.y, z - right.z);
        }

        //negation -
        inline EVector3D operator - ()
        {
            x = -x;
            y = -y;
            z = -z;
            return *this;
        }

        //positive +
        inline EVector3D operator + ()
        {
            x = +x;
            y = +y;
            z = +z;
            return *this;
        }

        //equal ==
        inline bool operator == (const EVector3D &right) const
        {
            return EqualFloat(x, right.x) && EqualFloat(y, right.y) && EqualFloat(z, right.z);
        }

        //vector assign =
        inline EVector3D operator = (const EVector3D &right)
        {
            x = right.x;
            y = right.y;
            z = right.z;
            return *this;
        }
    };
    
    struct EVector4D
    {
        static EVector4D ZERO;
        static EVector4D UNIT_X;
        static EVector4D UNIT_Y;
        static EVector4D UNIT_Z;


        EFloat x;
        EFloat y;
        EFloat z;
        EFloat w;

        EVector4D() : x(0), y(0), z(0), w(1) {}
        EVector4D(EFloat xf, EFloat yf, EFloat zf, EFloat wf = 1) : x(xf), y(yf), z(zf), w(wf) {}
        EVector4D(const EVector4D &v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

        //length of the vector
        inline EFloat length() const
        {
            return sqrt(x*x + y * y + z * z);
        }

        //normalize
        inline EFloat normalize()
        {
            EFloat len = length();
            if (len > EPSILON_E6) {
                EFloat invLen = 1.0f / len;
                x *= invLen;
                y *= invLen;
                z *= invLen;
                w = 1;
            }
            return len;
        }

        //dotproduct
        inline EFloat dotProduct(const EVector4D &right) const
        {
            return x * right.x + y * right.y + z * right.z;
        }

        //cross product
        inline EVector4D crossProduct(const EVector4D &right) const
        {
            return EVector4D(y * right.z - z * right.y, z*right.x - x * right.z, x*right.y - y * right.x, 1);
        }

        //return the angle between two vectors, radian
        inline EFloat angleBetween(const EVector4D &right) const
        {
            EFloat lenProduct = length() * right.length();

            //check zero
            if (lenProduct < EPSILON_E6)
                lenProduct = EPSILON_E6;

            EFloat f = dotProduct(right) / lenProduct;
            f = Clamp(f, -1.0f, 1.0f);
            return acos(f);
        }

        //check length is zero or not
        inline bool isZero() const
        {
            return length() < EPSILON_E6;
        }

        //get squared length
        inline EFloat squareLength() const
        {
            return x * x + y * y + z * z;
        }

        //operator * :vector * number 
        inline EVector4D operator * (float right) const
        {
            return EVector4D(x * right, y * right, z * right, 1);
        }

        //operator * :vector * vector
        inline EVector4D operator * (const EVector4D &right) const
        {
            return EVector4D(x * right.x, y * right.y, z * right.z, 1);
        }

        //operator + : vec + vec
        inline EVector4D operator + (const EVector4D &right) const
        {
            return EVector4D(x + right.x, y + right.y, z + right.z, 1);
        }

        //operator - : vec - vec
        inline EVector4D operator - (const EVector4D &right) const
        {
            return EVector4D(x - right.x, y - right.y, z - right.z, 1);
        }

        //negation -
        inline EVector4D operator - ()
        {
            x = -x;
            y = -y;
            z = -z;
            return *this;
        }

        //positive +
        inline EVector4D operator + ()
        {
            x = +x;
            y = +y;
            z = +z;
            return *this;
        }

        //equal ==
        inline bool operator == (const EVector4D &right) const
        {
            return EqualFloat(x, right.x) && EqualFloat(y, right.y) 
                && EqualFloat(z, right.z && EqualFloat(w, right.w));
        }

        //vector assign =
        inline EVector4D operator = (const EVector4D &right)
        {
            x = right.x;
            y = right.y;
            z = right.z;
            return *this;
        }
    };


}