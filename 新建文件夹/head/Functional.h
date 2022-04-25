#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H
//������
namespace MySTL {
	//һԪ��������Ļ��࣬����������뷵��ֵ
	template<class T>
	struct unary_function {
		typedef T arguement_type;
		typedef T result_type;
	};
	//��Ԫ��������Ļ���
	template<class T>
	struct binary_funtion {
		typedef T first_argument_type;
		typedef T second_arguement_type;
		typedef T result_type;
	};
	//less ����������С���Ǹ�
	template<class T>
	struct less {
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;
		
		result_type operator()(const first_argument_type& x, const second_argument_type& y) {
			return x < y;
		}
	};
	//equals_to �����Ƿ����
	template<class T>
	struct equals_to {
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;
		result_type operator()(const first_argument_type& x, const second_argument_type& y) {
			return x == y;
		}
	};
	//identity ��֤ͬһ��
	template<class T>
	struct identity : public unary_function<T> {
		const T& operator()(const T& x) const { return x; }
	};
	//select1st ���ؼ�ֵ���еļ�ֵ
	template<class T>
	struct selectlst : public unary_function<T, typename T::first_type> {
		const typename T::first_type& operator()(const T& x) const { return x.first };
	};
}
#endif // !FUNCTIONAL_H
