#ifndef MEMORYMANAGERUTILITY_H
#define MEMORYMANAGERUTILITY_H

template<bool, typename, typename>
struct pick_type;
template<typename T, typename U>
struct pick_type<true, T, U> {
	typedef T type;
};
template<typename T, typename U>
struct pick_type<false, T, U> {
	typedef U type;
};

template<typename...>
struct largest;
template<typename T>
struct largest<T> {
	typedef T type;
};
template<typename T, typename... U>
struct largest<T, U...> {
	typedef typename largest<U...>::type tailtype;
	typedef typename pick_type<
		(sizeof(T)>sizeof(tailtype)),
		T,
		tailtype
			>::type type;
};

template<typename Base, typename... Deriveds> struct is_base_of_all;
template<typename Base, typename Derived, typename... Deriveds>
struct is_base_of_all<Base, Derived, Deriveds...> :
std::integral_constant<bool, std::is_base_of<Base, Derived>::value && is_base_of_all<Base, Deriveds...>::value>{};
template<typename Base>
struct is_base_of_all<Base> : std::true_type{};

#endif