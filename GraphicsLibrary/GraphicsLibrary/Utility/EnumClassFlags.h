#pragma once
#include <type_traits>

namespace Alpha
{

	// 列挙を基本型にキャスト
	template<class T>
	inline std::underlying_type_t<T> CovertEnumClassToBaseType(T e)
	{
		return static_cast<std::underlying_type_t<T>>(e);
	}

#define EnumClassFlags(Flag) \
inline Flag operator |(Flag lhs, Flag rhs)	{ return static_cast<Flag>(CovertEnumClassToBaseType(lhs) | CovertEnumClassToBaseType(rhs)); }\
inline Flag operator ^(Flag lhs, Flag rhs)	{ return static_cast<Flag>(CovertEnumClassToBaseType(lhs) ^ CovertEnumClassToBaseType(rhs)); }\
inline bool operator &(Flag lhs, Flag rhs)	{ return CovertEnumClassToBaseType(lhs) & CovertEnumClassToBaseType(rhs); }\
inline Flag operator |=(Flag& lhs, Flag rhs){ lhs = lhs | rhs;return lhs; }\
inline Flag operator ^=(Flag& lhs, Flag rhs){ lhs = lhs ^ rhs;return lhs; }

	// ビットにフラグが立っているか(EnumClassFlags必須)
	template<typename EnumClass>
	inline bool EnumHasFlag(EnumClass bit, EnumClass flag)
	{
		return ((bit & flag) != 0);
	}
	// ビットにフラグを立てる(EnumClassFlags必須)
	template<typename EnumClass>
	inline EnumClass OnBit(EnumClass& bit, EnumClass flag)
	{
		return (bit |= flag);
	}
}
//
//// 必要なenum classに限定するために↑のマクロに変更
//template<class T>
//inline T operator |(T l, T r)
//{
//	return static_cast<T>(CovertToBaseType(l) | CovertToBaseType(r));
//}
//// 
//template<class T>
//inline T operator ^(T l, T r)
//{
//	return static_cast<T>(CovertToBaseType(l) ^ CovertToBaseType(r));
//}
//
//template<class T>
//inline bool operator &(T l, T r)
//{
//	return CovertToBaseType(l) & CovertToBaseType(r);
//}
//
//template<class T>
//inline T operator |=(T& l, T r)
//{
//	l = l | r;
//	return l;
//}
//
//template<class T>
//inline T operator ^=(T& l, T r)
//{
//	l = l ^ r;
//	return l;
//}
//
