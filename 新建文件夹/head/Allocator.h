#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cassert>
#include <new>
#include <cstddef>
#include "Alloc.h"
#include "Construct.h"

/*
* �ռ�������
*/

namespace MySTL {
	template<class T>
	class allocator {
	public:
		typedef T			value_type;
		typedef T* pointer;
		typedef const T* const_poniter;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;
	public:
		static T* allocate();
		static T* allocate(size_t n);
		static void deallocate(T* ptr);
		static void deallocate(T* ptr, size_t n);

		static void construct(T* ptr);
		static void construct(T* ptr, const T& value);
		static void destroy(T* ptr);
		static void destroy(T* first, T* last);
	};

	//ģ�� T �����ڴ�
	template<class T>
	T* allocator<T>::allocate() {
		return static_cast<T*> (alloc::allocate(sizeof(T)));
	}

	//ģ��T������n
	template<class T>
	T* allocator<T>::allocate(size_t n) {
		if (n == 0)return 0;
		return static_cast<T * (alloc::allocate(sizeof(T) * n));
	}

	//�ͷŶ���ָ����ڴ�
	template<class T>
	void allocator<T>::deallocate(T* ptr) {
		alloc::deallocate(static_cast<void*>(ptr, sizeof(T));
	}

	//�ͷ��ڴ�����أ��������� n ���ͷ�һ���ڴ�
	template<class T>
	void allocator<T>::deallocate(T* ptr, size_t n) {
		if (n == 0) {
			return 0;
		}
		alloc::deallocate(static_cast<void*>(ptr), sizeof(T) * n);
	}

	//����
	template<class T>
	void allocator<T>::construct(T* ptr) {
		new(ptr) T();
	}

	//���ع��죬��ֵ
	template<class T>
	void allocator<T>::construct(T* ptr, const T& value) {
		new(ptr)T(value);
	}

	//����
	template<class T>
	void allocator<T>::destroy(T* ptr) {
		ptr->~T();
	}

	//��������
	template<class T>
	void allocator<T>::destroy(T* first, T* last) {
		for (; first != last; ++first) {
			first->~T();
		}
	}
}
#endif // !ALLOCATOR_H
