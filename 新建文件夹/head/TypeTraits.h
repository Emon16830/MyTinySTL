#ifndef TYPETRAITS_H
#define TYPETRAITS_H
//���Ϳ⣬������һЩ����
namespace MySTL {

	namespace {
		
		template<bool,class Ta,class Tb>
		struct IfThenElse;

		//����ģ����
		template<class Ta,class Tb>
		struct IfThenElse<true, Ta, Tb> {
			using result = Ta;
		};
		template<class Ta,class Tb>
		struct IfThenElse <false,Ta,Tb>{
			using result = Tb;
		};

		struct _true_type {};
		struct _false_type {};

		/*������ȡ
		* ��ʵ���ڱ����ڼ��㡢�жϡ�ת������ѯ�ȵȹ���
		*�ѹ�����ͬ��������ͬ�ĺ������������ͨ��traits����ͬ�Ĳ�������ͬ������ȡ������
		*�ں�����������Щ��traits��ȡ�����ԣ�ʹ�ú����Բ�ͬ�Ĳ�������һ�¡�
		*/
		
		//ԭ���Լ����������͵�һ��typedef
		template<class T>
		struct _type_traits {
			typedef _false_type		has_trivial_default_constructor;
			typedef _false_type		has_trivial_copy_constructor;
			typedef _false_type		has_trivial_assignment_operator;
			typedef _false_type		has_trivial_destructor;
			typedef _false_type		is_POD_type;
		};
		//bool 
		template<>
		struct _type_traits<bool> {
			typedef _true_type		has_trivial_default_constructor;
			typedef _true_type		has_trivial_copy_constructor;
			typedef _true_type		has_trivial_assignment_operator;
			typedef _true_type		has_trivial_destructor;
			typedef _true_type		is_POD_type;
		};
		//char 
		template<>
		struct _type_traits<char> {
			typedef _true_type		has_trivial_default_constructor;
			typedef _true_type		has_trivial_copy_constructor;
			typedef _true_type		has_trivial_assignment_operator;
			typedef _true_type		has_trivial_destructor;
			typedef _true_type		is_POD_type;
		};
		//unsigned char 
		template<>
		struct _type_traits<unsigned char> {
			typedef _true_type		has_trivial_default_constructor;
			typedef _true_type		has_trivial_copy_constructor;
			typedef _true_type		has_trivial_assignment_operator;
			typedef _true_type		has_trivial_destructor;
			typedef _true_type		is_POD_type;
		};
		//signed char 
		template<>
		struct _type_traits<signed char> {
			typedef _true_type		has_trivial_default_constructor;
			typedef _true_type		has_trivial_copy_constructor;
			typedef _true_type		has_trivial_assignment_operator;
			typedef _true_type		has_trivial_destructor;
			typedef _true_type		is_POD_type;
		};
		//wchar_t 
		template<>
		struct _type_traits<wchar_t> {
			typedef _true_type		has_trivial_default_constructor;
			typedef _true_type		has_trivial_copy_constructor;
			typedef _true_type		has_trivial_assignment_operator;
			typedef _true_type		has_trivial_destructor;
			typedef _true_type		is_POD_type;
		};
		//short 
		template<>
		struct _type_traits<short> {
			typedef _true_type		has_trivial_default_constructor;
			typedef _true_type		has_trivial_copy_constructor;
			typedef _true_type		has_trivial_assignment_operator;
			typedef _true_type		has_trivial_destructor;
			typedef _true_type		is_POD_type;
		};
		//unsigned short ����
		template<>
		struct _type_traits<unsigned short> {
			typedef _true_type		has_trivial_default_constructor;
			typedef _true_type		has_trivial_copy_constructor;
			typedef _true_type		has_trivial_assignment_operator;
			typedef _true_type		has_trivial_destructor;
			typedef _true_type		is_POD_type;
		};
		//int
		template<>
		struct _type_traits<int> {
			typedef _true_type		has_trivial_default_constructor;
			typedef _true_type		has_trivial_copy_constructor;
			typedef _true_type		has_trivial_assignment_operator;
			typedef _true_type		has_trivial_destructor;
			typedef _true_type		is_POD_type;
		};
		//unsigned int
		template<>
		struct _type_traits<unsigned int> {
			typedef _true_type		has_trivial_default_constructor;
			typedef _true_type		has_trivial_copy_constructor;
			typedef _true_type		has_trivial_assignment_operator;
			typedef _true_type		has_trivial_destructor;
			typedef _true_type		is_POD_type;
		};
		//long
		template<>
		struct _type_traits<long> {
			typedef _true_type		has_trivial_default_constructor;
			typedef _true_type		has_trivial_copy_constructor;
			typedef _true_type		has_trivial_assignment_operator;
			typedef _true_type		has_trivial_destructor;
			typedef _true_type		is_POD_type;
		};
		//unsigned long
		template<>
		struct _type_traits<unsigned long> {
			typedef _true_type		has_trivial_default_constructor;
			typedef _true_type		has_trivial_copy_constructor;
			typedef _true_type		has_trivial_assignment_operator;
			typedef _true_type		has_trivial_destructor;
			typedef _true_type		is_POD_type;
		};
		//long long 
		template<>
		struct _type_traits<long long> {
			typedef _true_type		has_trivial_default_constructor;
			typedef _true_type		has_trivial_copy_constructor;
			typedef _true_type		has_trivial_assignment_operator;
			typedef _true_type		has_trivial_destructor;
			typedef _true_type		is_POD_type;
		};
		//unsigned long long 
		template<>
		struct _type_traits<unsigned long long> {
			typedef _true_type		has_trivial_default_constructor;
			typedef _true_type		has_trivial_copy_constructor;
			typedef _true_type		has_trivial_assignment_operator;
			typedef _true_type		has_trivial_destructor;
			typedef _true_type		is_POD_type;
		};
		//float
		template<>
		struct _type_traits<float> {
			typedef _true_type		has_trivial_default_constructor;
			typedef _true_type		has_trivial_copy_constructor;
			typedef _true_type		has_trivial_assignment_operator;
			typedef _true_type		has_trivial_destructor;
			typedef _true_type		is_POD_type;
		};
		//double
		template<>
		struct _type_traits<double> {
			typedef _true_type		has_trivial_default_constructor;
			typedef _true_type		has_trivial_copy_constructor;
			typedef _true_type		has_trivial_assignment_operator;
			typedef _true_type		has_trivial_destructor;
			typedef _true_type		is_POD_type;
		};
		//long double
		template<>
		struct _type_traits<long double> {
			typedef _true_type		has_trivial_default_constructor;
			typedef _true_type		has_trivial_copy_constructor;
			typedef _true_type		has_trivial_assignment_operator;
			typedef _true_type		has_trivial_destructor;
			typedef _true_type		is_POD_type;
		};
		//*class
		template<class T>
		struct _type_traits<T*> {
			typedef _true_type		has_trivial_default_constructor;
			typedef _true_type		has_trivial_copy_constructor;
			typedef _true_type		has_trivial_assignment_operator;
			typedef _true_type		has_trivial_destructor;
			typedef _true_type		is_POD_type;
		};
		//const* class
		template<class T>
		struct _type_traits<const T*> {
			typedef _true_type		has_trivial_default_constructor;
			typedef _true_type		has_trivial_copy_constructor;
			typedef _true_type		has_trivial_assignment_operator;
			typedef _true_type		has_trivial_destructor;
			typedef _true_type		is_POD_type;
		};
		//char*
		template<>
		struct _type_traits<char*> {
			typedef _true_type		has_trivial_default_constructor;
			typedef _true_type		has_trivial_copy_constructor;
			typedef _true_type		has_trivial_assignment_operator;
			typedef _true_type		has_trivial_destructor;
			typedef _true_type		is_POD_type;
		};
		//unsigned char*
		template<>
		struct _type_traits<unsigned char*> {
			typedef _true_type		has_trivial_default_constructor;
			typedef _true_type		has_trivial_copy_constructor;
			typedef _true_type		has_trivial_assignment_operator;
			typedef _true_type		has_trivial_destructor;
			typedef _true_type		is_POD_type;
		};
		//signed char*
		template<>
		struct _type_traits<signed char*> {
			typedef _true_type		has_trivial_default_constructor;
			typedef _true_type		has_trivial_copy_constructor;
			typedef _true_type		has_trivial_assignment_operator;
			typedef _true_type		has_trivial_destructor;
			typedef _true_type		is_POD_type;
		};
		//const char*
		template<>
		struct _type_traits<const char*> {
			typedef _true_type		has_trivial_default_constructor;
			typedef _true_type		has_trivial_copy_constructor;
			typedef _true_type		has_trivial_assignment_operator;
			typedef _true_type		has_trivial_destructor;
			typedef _true_type		is_POD_type;
		};
		//const unsigned char*
		template<>
		struct _type_traits<const unsigned char*> {
			typedef _true_type		has_trivial_default_constructor;
			typedef _true_type		has_trivial_copy_constructor;
			typedef _true_type		has_trivial_assignment_operator;
			typedef _true_type		has_trivial_destructor;
			typedef _true_type		is_POD_type;
		};
		//const signed char*
		template<>
		struct _type_traits<const signed char*> {
			typedef _true_type		has_trivial_default_constructor;
			typedef _true_type		has_trivial_copy_constructor;
			typedef _true_type		has_trivial_assignment_operator;
			typedef _true_type		has_trivial_destructor;
			typedef _true_type		is_POD_type;
		};

	}
}
#endif // !TYPETRAITS_H
