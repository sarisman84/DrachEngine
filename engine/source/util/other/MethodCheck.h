#pragma once
#include <type_traits>
namespace drach
{
	template<typename T, typename R, typename... Args>
	struct is_valid_call
	{
	private:
		template<typename U>
		static auto test(U* p) -> decltype((*p)(std::declval<Args>()...), std::is_same<R, decltype((*p)(std::declval<Args>()...))>::value);

		template<typename>
		static std::false_type test(...);

	public:
		static constexpr bool value = decltype(test<T>(nullptr))::value;
	};
}

#define DEFINE_METHOD_CHECK(x)                                                                                           \
template<typename, typename T>                                                                                           \
struct Has_ ## x                                                                                                          \
{                                                                                                                         \
   static_assert(std::integral_constant<T, false>::value,"Second template parameter needs to be of function type.");     \
};                                                                                                                        \
template<typename C, typename Ret, typename... Args>                                                                     \
struct Has_ ## x < C, Ret(Args...) >                                                                                      \
{                                                                                                                         \
private:                                                                                                                  \
    template<typename T>                                                                                                  \
    static constexpr auto check(T*)                                                                                       \
    -> typename                                                                                                           \
    std::is_same<decltype(std::declval<T>().x(std::declval<Args>()...)), Ret>::type;                                      \
    \
    template<typename>                                                                                                    \
    static constexpr std::false_type check(...);                                                                         \
    \
    typedef decltype(check<C>(0)) type;                                                                                   \
    \
public:                                                                                                                   \
    static constexpr bool value = type::value;                                                                            \
}


