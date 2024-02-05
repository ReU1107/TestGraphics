#pragma once
#include <type_traits>

namespace Alpha
{

	// �񋓂���{�^�ɃL���X�g
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

	// �r�b�g�Ƀt���O�������Ă��邩(EnumClassFlags�K�{)
	template<typename EnumClass>
	inline bool EnumHasFlag(EnumClass bit, EnumClass flag)
	{
		return ((bit & flag) != 0);
	}
	// �r�b�g�Ƀt���O�𗧂Ă�(EnumClassFlags�K�{)
	template<typename EnumClass>
	inline EnumClass OnBit(EnumClass& bit, EnumClass flag)
	{
		return (bit |= flag);
	}
}
//
//// �K�v��enum class�Ɍ��肷�邽�߂Ɂ��̃}�N���ɕύX
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
