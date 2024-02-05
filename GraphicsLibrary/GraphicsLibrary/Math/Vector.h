#pragma once
#include <cstdint>

namespace Alpha
{
	/*
	* 一段階クラスを挟んだら今できていないXZ()とかできそう
	* 今できない理由が現状　XY() YZ()のようにメモリが連続していることを前提として参照を渡しているから
	*/

	template<class Type, uint32_t N>
	class TVector
	{
	private:
		Type value[N];

	public:
		static const TVector<Type, N> Zero;
		static const TVector<Type, N> One;

		template<typename... Args>
		TVector(Args... args)
		{
			size_t index = 0;
			Expansion(index, args...);
		}

		inline Type& X();
		inline Type X()const;

		inline Type& Y();
		inline Type Y()const;

		inline Type& Z();
		inline Type Z()const;

		inline Type& W();
		inline Type W()const;

		inline TVector<Type, 2>& XY();
		inline const TVector<Type, 2>& XY() const;

		inline TVector<Type, 2>& YZ();
		inline const TVector<Type, 2>& YZ() const;

		inline TVector<Type, 2>& ZW();
		inline const TVector<Type, 2>& ZW() const;

		inline TVector<Type, 3>& XYZ();
		inline const TVector<Type, 3>& XYZ() const;

		inline TVector<Type, 3>& YZW();
		inline const TVector<Type, 3>& YZW() const;

		inline TVector<Type, 4>& XYZW();
		inline const TVector<Type, 4>& XYZW() const;

		inline TVector<Type, N>& operator=(const TVector<Type, N>& other);
		inline TVector<Type, N>& operator+=(const TVector<Type, N>& other);
		inline TVector<Type, N>& operator-=(const TVector<Type, N>& other);
		inline TVector<Type, N>& operator*=(const TVector<Type, N>& other);
		inline TVector<Type, N>& operator/=(const TVector<Type, N>& other);

		inline TVector<Type, N>& operator=(const Type other);
		inline TVector<Type, N>& operator+=(const Type other);
		inline TVector<Type, N>& operator-=(const Type other);
		inline TVector<Type, N>& operator*=(const Type other);
		inline TVector<Type, N>& operator/=(const Type other);

		// UnSafe
		inline Type& operator[](const uint32_t index);

		// Safe
		inline Type At(const uint32_t index) const;

	private:
		// パラメータパック展開用関数
		void Expansion(size_t& index)
		{
		}
		// パラメータパック展開用関数
		template<typename Head, typename... Tail>
		void Expansion(size_t& index, Head&& head, Tail&&... tail)
		{
			if (index >= N)
				return;
			constexpr size_t ByteSize = sizeof(head);
			constexpr size_t TypeSize = sizeof(Type);
			constexpr size_t Count = (ByteSize / TypeSize);
			const Type* data = (Type*)(&head);
			for (size_t i = 0; i < Count; i++)
			{
				if (index >= N)
					return;
				value[index++] = data[i];
			}

			Expansion(index, tail...);
		}
	};

	// 
	template<class Type, uint32_t N>
	static inline TVector<Type, N> operator+(const TVector<Type, N>& lhs, const TVector<Type, N>& rhs);
	template<class Type, uint32_t N>
	static inline TVector<Type, N> operator-(const TVector<Type, N>& lhs, const TVector<Type, N>& rhs);
	template<class Type, uint32_t N>
	static inline TVector<Type, N> operator*(const TVector<Type, N>& lhs, const TVector<Type, N>& rhs);
	template<class Type, uint32_t N>
	static inline TVector<Type, N> operator/(const TVector<Type, N>& lhs, const TVector<Type, N>& rhs);

	// 
	template<class Type, uint32_t N>
	static inline TVector<Type, N> operator+(const TVector<Type, N>& lhs, const Type rhs);
	template<class Type, uint32_t N>
	static inline TVector<Type, N> operator-(const TVector<Type, N>& lhs, const Type rhs);
	template<class Type, uint32_t N>
	static inline TVector<Type, N> operator*(const TVector<Type, N>& lhs, const Type rhs);
	template<class Type, uint32_t N>
	static inline TVector<Type, N> operator/(const TVector<Type, N>& lhs, const Type rhs);

	// 
	template<class Type, uint32_t N>
	static inline TVector<Type, N> operator+(const Type lhs, const TVector<Type, N>& rhs);
	template<class Type, uint32_t N>
	static inline TVector<Type, N> operator-(const Type lhs, const TVector<Type, N>& rhs);
	template<class Type, uint32_t N>
	static inline TVector<Type, N> operator*(const Type lhs, const TVector<Type, N>& rhs);
	template<class Type, uint32_t N>
	static inline TVector<Type, N> operator/(const Type lhs, const TVector<Type, N>& rhs);


	template<class Type, uint32_t N>
	static inline bool operator<(const TVector<Type, N>& lhs, const TVector<Type, N>& rhs);
	template<class Type, uint32_t N>
	static inline bool operator>(const TVector<Type, N>& lhs, const TVector<Type, N>& rhs);
	template<class Type, uint32_t N>
	static inline bool operator==(const TVector<Type, N>& lhs, const TVector<Type, N>& rhs);

	// エイリアス
	using Vector1 = TVector<float, 1>;
	using Vector2 = TVector<float, 2>;
	using Vector3 = TVector<float, 3>;
	using Vector4 = TVector<float, 4>;

	using float1 = Vector1;
	using float2 = Vector2;
	using float3 = Vector3;
	using float4 = Vector4;
}

#include "VectorImpl.h"
