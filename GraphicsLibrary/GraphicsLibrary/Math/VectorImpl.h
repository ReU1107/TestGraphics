#pragma once
#pragma once
#include "Vector.h"
#include <cassert>

namespace Alpha
{
	// “ÁŽê‰»
	template<>
	const TVector<uint32_t, 1> TVector<uint32_t, 1>::Zero = TVector<uint32_t, 1>(0);
	const TVector<uint32_t, 2> TVector<uint32_t, 2>::Zero = TVector<uint32_t, 2>(0, 0);
	const TVector<uint32_t, 3> TVector<uint32_t, 3>::Zero = TVector<uint32_t, 3>(0, 0, 0);
	const TVector<uint32_t, 4> TVector<uint32_t, 4>::Zero = TVector<uint32_t, 4>(0, 0, 0, 0);

	template<>
	const TVector<uint32_t, 1> TVector<uint32_t, 1>::One = TVector<uint32_t, 1>(1);
	const TVector<uint32_t, 2> TVector<uint32_t, 2>::One = TVector<uint32_t, 2>(1, 1);
	const TVector<uint32_t, 3> TVector<uint32_t, 3>::One = TVector<uint32_t, 3>(1, 1, 1);
	const TVector<uint32_t, 4> TVector<uint32_t, 4>::One = TVector<uint32_t, 4>(1, 1, 1, 1);

	template<>
	const TVector<float, 1> TVector<float, 1>::Zero = TVector<float, 1>(0.0f);
	const TVector<float, 2> TVector<float, 2>::Zero = TVector<float, 2>(0.0f, 0.0f);
	const TVector<float, 3> TVector<float, 3>::Zero = TVector<float, 3>(0.0f, 0.0f, 0.0f);
	const TVector<float, 4> TVector<float, 4>::Zero = TVector<float, 4>(0.0f, 0.0f, 0.0f, 0.0f);

	template<>
	const TVector<float, 1> TVector<float, 1>::One = TVector<float, 1>(1.0f);
	const TVector<float, 2> TVector<float, 2>::One = TVector<float, 2>(1.0f, 1.0f);
	const TVector<float, 3> TVector<float, 3>::One = TVector<float, 3>(1.0f, 1.0f, 1.0f);
	const TVector<float, 4> TVector<float, 4>::One = TVector<float, 4>(1.0f, 1.0f, 1.0f, 1.0f);

	template<class Type, uint32_t N>
	inline Type& TVector<Type, N>::X()
	{
		static_assert(N >= 1, "Count is less than 1(X)");
		return value[0];
	}

	template<class Type, uint32_t N>
	inline Type TVector<Type, N>::X() const
	{
		static_assert(N >= 1, "Count is less than 1(X)");
		return value[0];
	}

	template<class Type, uint32_t N>
	inline Type& TVector<Type, N>::Y()
	{
		static_assert(N >= 2, "Count is less than 2(Y)");
		return value[1];
	}

	template<class Type, uint32_t N>
	inline Type TVector<Type, N>::Y() const
	{
		static_assert(N >= 2, "Count is less than 1(Y)");
		return value[1];
	}

	template<class Type, uint32_t N>
	inline Type& TVector<Type, N>::Z()
	{
		static_assert(N >= 3, "Count is less than 3(Z)");
		return value[2];
	}

	template<class Type, uint32_t N>
	inline Type TVector<Type, N>::Z() const
	{
		static_assert(N >= 3, "Count is less than 1(Z)");
		return value[2];
	}

	template<class Type, uint32_t N>
	inline Type& TVector<Type, N>::W()
	{
		static_assert(N >= 4, "Count is less than 4(W)");
		return value[3];
	}

	template<class Type, uint32_t N>
	inline Type TVector<Type, N>::W() const
	{
		static_assert(N >= 4, "Count is less than 1(W)");
		return value[3];
	}

	template<class Type, uint32_t N>
	inline TVector<Type, 2>& TVector<Type, N>::XY()
	{
		static_assert(N >= 2, "Count is less than 2(XY)");
		return *reinterpret_cast<TVector<Type, 2>*>(&value[0]);
	}

	template<class Type, uint32_t N>
	inline const TVector<Type, 2>& TVector<Type, N>::XY() const
	{
		static_assert(N >= 2, "Count is less than 2(XY)");
		return *reinterpret_cast<TVector<Type, 2>*>(const_cast<Type*>(&value[0]));
	}

	template<class Type, uint32_t N>
	inline TVector<Type, 2>& TVector<Type, N>::YZ()
	{
		static_assert(N >= 3, "Count is less than 2(YZ)");
		return *reinterpret_cast<TVector<Type, 2>*>(&value[1]);
	}

	template<class Type, uint32_t N>
	inline const TVector<Type, 2>& TVector<Type, N>::YZ() const
	{
		static_assert(N >= 3, "Count is less than 2(YZ)");
		return *reinterpret_cast<TVector<Type, 2>*>(const_cast<Type*>(&value[1]));
	}

	template<class Type, uint32_t N>
	inline TVector<Type, 2>& TVector<Type, N>::ZW()
	{
		static_assert(N >= 4, "Count is less than 2(ZW)");
		return *reinterpret_cast<TVector<Type, 2>*>(&value[2]);
	}

	template<class Type, uint32_t N>
	inline const TVector<Type, 2>& TVector<Type, N>::ZW() const
	{
		static_assert(N >= 4, "Count is less than 2(ZW)");
		return *reinterpret_cast<TVector<Type, 2>*>(const_cast<Type*>(&value[2]));
	}

	template<class Type, uint32_t N>
	inline TVector<Type, 3>& TVector<Type, N>::XYZ()
	{
		static_assert(N >= 3, "Count is less than 3(XYZ)");
		return *reinterpret_cast<TVector<Type, 3>*>(&value[0]);
	}

	template<class Type, uint32_t N>
	inline const TVector<Type, 3>& TVector<Type, N>::XYZ() const
	{
		static_assert(N >= 3, "Count is less than 3(XYZ)");
		return *reinterpret_cast<TVector<Type, 3>*>(const_cast<Type*>(&value[0]));

	}

	template<class Type, uint32_t N>
	inline TVector<Type, 3>& TVector<Type, N>::YZW()
	{
		static_assert(N >= 4, "Count is less than 3(YZW)");
		return *reinterpret_cast<TVector<Type, 3>*>(&value[1]);
	}

	template<class Type, uint32_t N>
	inline const TVector<Type, 3>& TVector<Type, N>::YZW() const
	{
		static_assert(N >= 4, "Count is less than 3(YZW)");
		return *reinterpret_cast<TVector<Type, 3>*>(const_cast<Type*>(&value[1]));
	}

	template<class Type, uint32_t N>
	inline TVector<Type, 4>& TVector<Type, N>::XYZW()
	{
		static_assert(N >= 4, "Count is less than 4(XYZW)");
		return *reinterpret_cast<TVector<Type, 4>*>(&value[0]);
	}

	template<class Type, uint32_t N>
	inline const TVector<Type, 4>& TVector<Type, N>::XYZW() const
	{
		static_assert(N >= 4, "Count is less than 4(XYZW)");
		return *reinterpret_cast<TVector<Type, 4>*>(const_cast<Type*>(&value[0]));
	}

	template<class Type, uint32_t N>
	inline TVector<Type, N>& TVector<Type, N>::operator=(const TVector<Type, N>& other)
	{
		for (int32_t i = 0; i < N; i++)
		{
			value[i] = other.value[i];
		}

		return *this;
	}

	template<class Type, uint32_t N>
	inline TVector<Type, N>& TVector<Type, N>::operator+=(const TVector<Type, N>& other)
	{
		for (int32_t i = 0; i < N; i++)
		{
			value[i] += other.value[i];
		}

		return *this;
	}

	template<class Type, uint32_t N>
	inline TVector<Type, N>& TVector<Type, N>::operator-=(const TVector<Type, N>& other)
	{
		for (int32_t i = 0; i < N; i++)
		{
			value[i] -= other.value[i];
		}

		return *this;
	}

	template<class Type, uint32_t N>
	inline TVector<Type, N>& TVector<Type, N>::operator*=(const TVector<Type, N>& other)
	{
		for (int32_t i = 0; i < N; i++)
		{
			value[i] *= other.value[i];

			return *this;
		}
	}

	template<class Type, uint32_t N>
	inline TVector<Type, N>& TVector<Type, N>::operator/=(const TVector<Type, N>& other)
	{
		for (int32_t i = 0; i < N; i++)
		{
			value[i] /= other.value[i];
		}

		return *this;
	}

	template<class Type, uint32_t N>
	inline TVector<Type, N>& TVector<Type, N>::operator=(const Type other)
	{
		for (int32_t i = 0; i < N; i++)
		{
			value[i] = other;
		}

		return *this;
	}

	template<class Type, uint32_t N>
	inline TVector<Type, N>& TVector<Type, N>::operator+=(const Type other)
	{
		for (int32_t i = 0; i < N; i++)
		{
			value[i] += other;
		}

		return *this;
	}

	template<class Type, uint32_t N>
	inline TVector<Type, N>& TVector<Type, N>::operator-=(const Type other)
	{
		for (int32_t i = 0; i < N; i++)
		{
			value[i] -= other;
		}

		return *this;
	}

	template<class Type, uint32_t N>
	inline TVector<Type, N>& TVector<Type, N>::operator*=(const Type other)
	{
		for (int32_t i = 0; i < N; i++)
		{
			value[i] *= other;
		}

		return *this;
	}

	template<class Type, uint32_t N>
	inline TVector<Type, N>& TVector<Type, N>::operator/=(const Type other)
	{
		for (int32_t i = 0; i < N; i++)
		{
			value[i] /= other;
		}

		return *this;
	}

	template<class Type, uint32_t N>
	inline Type& TVector<Type, N>::operator[](const uint32_t index)
	{
		assert(index < N && "Index is greater than Num");
		return value[index];
	}

	template<class Type, uint32_t N>
	inline Type TVector<Type, N>::At(const uint32_t index) const
	{
		assert(index < N && "Index is greater than Num");
		return value[index];
	}

	template<class Type, uint32_t N>
	inline TVector<Type, N> operator+(const TVector<Type, N>& lhs, const TVector<Type, N>& rhs)
	{
		return TVector<Type, N>(lhs) += rhs;
	}

	template<class Type, uint32_t N>
	inline TVector<Type, N> operator-(const TVector<Type, N>& lhs, const TVector<Type, N>& rhs)
	{
		return TVector<Type, N>(lhs) -= rhs;
	}

	template<class Type, uint32_t N>
	inline TVector<Type, N> operator*(const TVector<Type, N>& lhs, const TVector<Type, N>& rhs)
	{
		return TVector<Type, N>(lhs) *= rhs;
	}

	template<class Type, uint32_t N>
	inline TVector<Type, N> operator/(const TVector<Type, N>& lhs, const TVector<Type, N>& rhs)
	{
		return TVector<Type, N>(lhs) /= rhs;
	}

	template<class Type, uint32_t N>
	inline TVector<Type, N> operator+(const TVector<Type, N>& lhs, const Type rhs)
	{
		return TVector<Type, N>(lhs) += rhs;
	}

	template<class Type, uint32_t N>
	inline TVector<Type, N> operator-(const TVector<Type, N>& lhs, const Type rhs)
	{
		return TVector<Type, N>(lhs) -= rhs;
	}

	template<class Type, uint32_t N>
	inline TVector<Type, N> operator*(const TVector<Type, N>& lhs, const Type rhs)
	{
		return TVector<Type, N>(lhs) *= rhs;
	}

	template<class Type, uint32_t N>
	inline TVector<Type, N> operator/(const TVector<Type, N>& lhs, const Type rhs)
	{
		return TVector<Type, N>(lhs) /= rhs;
	}

	template<class Type, uint32_t N>
	inline TVector<Type, N> operator+(const Type lhs, const TVector<Type, N>& rhs)
	{
		return TVector<Type, N>(lhs) += rhs;
	}

	template<class Type, uint32_t N>
	inline TVector<Type, N> operator-(const Type lhs, const TVector<Type, N>& rhs)
	{
		return TVector<Type, N>(lhs) -= rhs;
	}

	template<class Type, uint32_t N>
	inline TVector<Type, N> operator*(const Type lhs, const TVector<Type, N>& rhs)
	{
		return TVector<Type, N>(lhs) *= rhs;
	}

	template<class Type, uint32_t N>
	inline TVector<Type, N> operator/(const Type lhs, const TVector<Type, N>& rhs)
	{
		return TVector<Type, N>(lhs) /= rhs;
	}

	template<class Type, uint32_t N>
	bool operator<(const TVector<Type, N>& lhs, const TVector<Type, N>& rhs)
	{
		for (uint32_t i = 0; i < N; i++)
		{
			if (lhs.At(i) > rhs.At(i))
				return false;
		}

		return true;
	}

	template<class Type, uint32_t N>
	bool operator>(const TVector<Type, N>& lhs, const TVector<Type, N>& rhs)
	{
		for (uint32_t i = 0; i < N; i++)
		{
			if (lhs.At(i) < rhs.At(i))
				return false;
		}

		return true;
	}

	template<class Type, uint32_t N>
	bool operator==(const TVector<Type, N>& lhs, const TVector<Type, N>& rhs)
	{
		for (uint32_t i = 0; i < N; i++)
		{
			if (lhs.At(i) != rhs.At(i))
				return false;
		}

		return true;
	}
}