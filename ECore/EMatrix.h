#pragma once

#include "ECommon.h"
namespace E3D 
{
	//define the matrix type
	struct EMatrix44
	{
		static EMatrix44 IDENTITY;

		EFloat m[4][4];

		EMatrix44()
		{
			memset(m, 0, sizeof(EFloat) * 16);
		}

		//init
		EMatrix44(const EMatrix44 &right)
		{
			m[0][0] = right.m[0][0], m[0][1] = right.m[0][1], m[0][2] = right.m[0][2], m[0][3] = right.m[0][3];
			m[1][0] = right.m[1][0], m[1][1] = right.m[1][1], m[1][2] = right.m[1][2], m[1][3] = right.m[1][3];
			m[2][0] = right.m[2][0], m[2][1] = right.m[2][1], m[2][2] = right.m[2][2], m[2][3] = right.m[2][3];
			m[3][0] = right.m[3][0], m[3][1] = right.m[3][1], m[3][2] = right.m[3][2], m[3][3] = right.m[3][3];
		}
		//init 2
		EMatrix44(
			EFloat m00, EFloat m01, EFloat m02, EFloat m03,
			EFloat m10, EFloat m11, EFloat m12, EFloat m13,
			EFloat m20, EFloat m21, EFloat m22, EFloat m23,
			EFloat m30, EFloat m31, EFloat m32, EFloat m33)
		{
			m[0][0] = m00, m[0][1] = m01, m[0][2] = m02, m[0][3] = m03;
			m[1][0] = m10, m[1][1] = m11, m[1][2] = m12, m[1][3] = m13;
			m[2][0] = m20, m[2][1] = m21, m[2][2] = m22, m[2][3] = m23;
			m[3][0] = m30, m[3][1] = m31, m[3][2] = m32, m[3][3] = m33;
		}


		//transpose
		inline EMatrix44 transpose() const 
		{
			EMatrix44 tmp;
			for (EInt i = 0; i < 4; ++i) {
				for (EInt j = 0; j < 4; ++j) {
					tmp.m[i][j] = m[j][i];
				}
			}

			return tmp;
		}

		//visit index 
		inline EFloat at(size_t i, size_t j) const 
		{
			return m[i][j];
		}

		//visit index
		inline EFloat& at(size_t i, size_t j)
		{
			return m[i][j];
		}

		//overload operator
		//matrix + matrix
		inline EMatrix44 operator + (const EMatrix44 &right) const
		{
			return EMatrix44(
				m[0][0] + right.m[0][0], m[0][1] + right.m[0][1], m[0][2] + right.m[0][2], m[0][3] + right.m[0][3],
				m[1][0] + right.m[1][0], m[1][1] + right.m[1][1], m[1][2] + right.m[1][2], m[1][3] + right.m[1][3],
				m[2][0] + right.m[2][0], m[2][1] + right.m[2][1], m[2][2] + right.m[2][2], m[2][3] + right.m[2][3],
				m[3][0] + right.m[3][0], m[3][1] + right.m[3][1], m[3][2] + right.m[3][2], m[3][3] + right.m[3][3]);
		}
        //matrix - matrix
		inline EMatrix44 operator - (const EMatrix44 &right) const
		{
			return EMatrix44(
				m[0][0] - right.m[0][0], m[0][1] - right.m[0][1], m[0][2] - right.m[0][2], m[0][3] - right.m[0][3],
				m[1][0] - right.m[1][0], m[1][1] - right.m[1][1], m[1][2] - right.m[1][2], m[1][3] - right.m[1][3],
				m[2][0] - right.m[2][0], m[2][1] - right.m[2][1], m[2][2] - right.m[2][2], m[2][3] - right.m[2][3],
				m[3][0] - right.m[3][0], m[3][1] - right.m[3][1], m[3][2] - right.m[3][2], m[3][3] - right.m[3][3]);
		}
        //matrix * number
        inline EMatrix44 operator * (EFloat factor) const
        {
            return EMatrix44(
                m[0][0] * factor, m[0][1] * factor, m[0][2] * factor, m[0][3] * factor,
                m[1][0] * factor, m[1][1] * factor, m[1][2] * factor, m[1][3] * factor,
                m[2][0] * factor, m[2][1] * factor, m[2][2] * factor, m[2][3] * factor,
                m[3][0] * factor, m[3][1] * factor, m[3][2] * factor, m[3][3] * factor);
        }
        //matrix * matrix
        inline EMatrix44 operator * (const EMatrix44 &right) const
        {
            EMatrix44 tmp;
            for (EInt i = 0; i < 4; ++i) {
                for (EInt j = 0; j < 4; ++j) {
                    for (EInt k = 0; k < 4; ++k) {
                        tmp.m[i][j] = m[i][k] * right.[k][j];
                    }
                }
            }
            return tmp;
        }

        // asign = 
        inline EMatrix44& operator = (const EMatrix44 &right) 
        {
            m[0][0] + right.m[0][0], m[0][1] + right.m[0][1], m[0][2] + right.m[0][2], m[0][3] + right.m[0][3];
            m[1][0] + right.m[1][0], m[1][1] + right.m[1][1], m[1][2] + right.m[1][2], m[1][3] + right.m[1][3];
            m[2][0] + right.m[2][0], m[2][1] + right.m[2][1], m[2][2] + right.m[2][2], m[2][3] + right.m[2][3];
            m[3][0] + right.m[3][0], m[3][1] + right.m[3][1], m[3][2] + right.m[3][2], m[3][3] + right.m[3][3];
            return *this;           
        }

        inline bool operator == (const EMatrix44 &right) const
        {
            if (m[0][0] != right.m[0][0] || m[0][1] != right.m[0][1] || m[0][2] != right.m[0][2] || m[0][3] != right.m[0][3] ||
                m[1][0] != right.m[1][0] || m[1][1] != right.m[1][1] || m[1][2] != right.m[1][2] || m[1][3] != right.m[1][3] ||
                m[2][0] != right.m[2][0] || m[2][1] != right.m[2][1] || m[2][2] != right.m[2][2] || m[2][3] != right.m[2][3] ||
                m[3][0] != right.m[3][0] || m[3][1] != right.m[3][1] || m[3][2] != right.m[3][2] || m[3][3] != right.m[3][3]) {
                return false;
            }
            return true;
        }

	};
}