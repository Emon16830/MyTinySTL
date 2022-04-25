#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H
//适配器
namespace MySTL {
	//一元函数对象的基类，仅定义参数与返回值
	template<class T>
	struct unary_function {
		typedef T arguement_type;
		typedef T result_type;
	};
	//二元函数对象的基类
	template<class T>
	struct binary_funtion {
		typedef T first_argument_type;
		typedef T second_arguement_type;
		typedef T result_type;
	};
	//less 返回两者最小的那个
	template<class T>
	struct less {
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;
		
		result_type operator()(const first_argument_type& x, const second_argument_type& y) {
			return x < y;
		}
	};
	//equals_to 两者是否相等
	template<class T>
	struct equals_to {
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;
		result_type operator()(const first_argument_type& x, const second_argument_type& y) {
			return x == y;
		}
	};
	//identity 验证同一性
	template<class T>
	struct identity : public unary_function<T> {
		const T& operator()(const T& x) const { return x; }
	};
	//select1st 返回键值对中的键值
	template<class T>
	struct selectlst : public unary_function<T, typename T::first_type> {
		const typename T::first_type& operator()(const T& x) const { return x.first };
	};
}
#endif // !FUNCTIONAL_H
