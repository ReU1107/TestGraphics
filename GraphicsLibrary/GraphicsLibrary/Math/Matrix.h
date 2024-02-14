#pragma once
#include "Vector.h"


namespace Alpha
{
	/*
	Row:行
	Column:列
	*/

	template<class Type, uint32_t Row, uint32_t Column>
	class TMatrix
	{
	public:
		union
		{
			TVector<Type, Column> vec[Row];
			Type value[Row * Column];
		};
	public:
		static const TMatrix<Type, Row, Column> Zero;
		static const TMatrix<Type, Row, Column> Identity;

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

		template<typename... Args>
		TMatrix(Args... args)
		{
			size_t index = 0;
			Expansion(index, args...);
		}

		inline TMatrix<Type, Row, Column>& operator*=(const TMatrix<Type, Row, Column>& other);

		inline TMatrix<Type, Row, Column>& operator=(const TMatrix<Type, Row, Column>& other);

		inline TVector<Type, Column>& operator[](const uint32_t index);

		inline TVector<Type, Column> At(const uint32_t index) const;

		inline TVector<Type, Column>& _1();
		inline TVector<Type, Column>& _2();
		inline TVector<Type, Column>& _3();
		inline TVector<Type, Column>& _4();

		inline TVector<Type, Column> _1() const;
		inline TVector<Type, Column> _2() const;
		inline TVector<Type, Column> _3() const;
		inline TVector<Type, Column> _4() const;

		inline float& _11();
		inline float& _12();
		inline float& _13();
		inline float& _14();
		inline float& _21();
		inline float& _22();
		inline float& _23();
		inline float& _24();
		inline float& _31();
		inline float& _32();
		inline float& _33();
		inline float& _34();
		inline float& _41();
		inline float& _42();
		inline float& _43();
		inline float& _44();

		inline float _11() const;
		inline float _12() const;
		inline float _13() const;
		inline float _14() const;
		inline float _21() const;
		inline float _22() const;
		inline float _23() const;
		inline float _24() const;
		inline float _31() const;
		inline float _32() const;
		inline float _33() const;
		inline float _34() const;
		inline float _41() const;
		inline float _42() const;
		inline float _43() const;
		inline float _44() const;
	};

	template<class Type, uint32_t Row, uint32_t Column>
	static inline TMatrix<Type, Row, Column> operator*(const TMatrix<Type, Row, Column>& lhs, const TMatrix<Type, Row, Column>& rhs);

	using Matrix2x2 = TMatrix<float, 2, 2>;
	using Matrix3x3 = TMatrix<float, 3, 3>;
	using Matrix3x4 = TMatrix<float, 3, 4>;
	using Matrix4x3 = TMatrix<float, 4, 3>;
	using Matrix4x4 = TMatrix<float, 4, 4>;

	using matrix2x2 = Matrix2x2;
	using matrix3x3 = Matrix3x3;
	using matrix3x4 = Matrix3x4;
	using matrix4x3 = Matrix4x3;
	using matrix4x4 = Matrix4x4;

	using float2x2 = Matrix2x2;
	using float3x3 = Matrix3x3;
	using float3x4 = Matrix3x4;
	using float4x3 = Matrix4x3;
	using float4x4 = Matrix4x4;

}

//#include "../../src/Math/MatrixImpl.h"