#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cassert>
#include <new>
#include <cstddef>
#include "Alloc.h"
#include "Construct.h"

/*
* 空间配置器
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

	//模板 T 申请内存
	template<class T>
	T* allocator<T>::allocate() {
		return static_cast<T*> (alloc::allocate(sizeof(T)));
	}

	//模板T，数量n
	template<class T>
	T* allocator<T>::allocate(size_t n) {
		if (n == 0)return 0;
		return static_cast<T * (alloc::allocate(sizeof(T) * n));
	}

	//释放对象指向的内存
	template<class T>
	void allocator<T>::deallocate(T* ptr) {
		alloc::deallocate(static_cast<void*>(ptr, sizeof(T));
	}

	//释放内存的重载，根据数量 n 来释放一段内存
	template<class T>
	void allocator<T>::deallocate(T* ptr, size_t n) {
		if (n == 0) {
			return 0;
		}
		alloc::deallocate(static_cast<void*>(ptr), sizeof(T) * n);
	}

	//构造
	template<class T>
	void allocator<T>::construct(T* ptr) {
		new(ptr) T();
	}

	//重载构造，传值
	template<class T>
	void allocator<T>::construct(T* ptr, const T& value) {
		new(ptr)T(value);
	}

	//析构
	template<class T>
	void allocator<T>::destroy(T* ptr) {
		ptr->~T();
	}

	//重载析构
	template<class T>
	void allocator<T>::destroy(T* first, T* last) {
		for (; first != last; ++first) {
			first->~T();
		}
	}
}
#endif // !ALLOCATOR_H
