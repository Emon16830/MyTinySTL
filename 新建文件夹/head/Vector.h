#ifndef VECTOR_H
#define VECTOR_H

#include <type_traits>
#include "Allocator.h"
#include "Algorithm.h"
#include "Iterator.h"
#include "ReverseIterator.h"
#include "UninitializedFunctions.h"

namespace MySTL {
	
	template<class T,class Alloc = allocator<T>>
	class vector {
	private:
		T* Start_;
		T* Finish_;
		T* EndOfStorage_;
		
		typedef Alloc dataAllocator;
	public:
		typedef T	value_type;
		typedef T* iterator;
		typedef const T* const_iterator;
		typedef reverse_iterator_t<T*>	reverse_iterator;
		typedef reverse_iterator_t<const T*>	const_reverse_iterator;
		typedef iterator	pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t	size_type;
		typedef ptrdiff_t	difference_type;

	//相关函数定义
	public:
		vector() :Start_(0), Finish_(0), EndOfStorage_(0) {}
		explicit vector(const size_type n);
		vector(const size_type n, const value_type& value);
		template<class InputIterator>
		vector(InputIterator first, InputIterator last);
		vector(const vector& v);
		vector(vector&& v);
		vector& operator = (const vector& v);
		vector& operator = (vector&& v);
		~vector();

		//操作符
		bool operator == (const vector& v)const;
		bool operator != (const vector& v)const;

		//迭代器
		iterator begin() {
			return Start_;
		}
		const_iterator begin() const {
			return Start_;
		}
		const_iterator cbegin() const {
			return Start_;
		}
		iterator end() {
			return Finish_;
		}
		const_iterator end() const {
			return Finish_;
		}
		const_iterator cend() const {
			return Finish_;
		}
		reverse_iterator rbegin() {
			return reverse_iterator(Finish_);
		}
		const_reverse_iterator crbegin() const {
			return const_reverse_iterator(Finish_);
		}
		reverse_iterator rend() {
			return reverse_iterator (Start_);
		}
		const_reverse_iterator crend() const {
			return const_reverse_iterator(Start_);
		}

		//与容量相关
		difference_type size() const {
			return Finish_ - Start_;
		}
		difference_type capacity() const {
			return EndOfStorage_ - Start_;
		}
		bool empty() const {
			return Start_ == Finish_;
		}
		void resize(size_type n, value_type val);
		void reserve(size_type n);
		void shrink_to_fit();


		//访问相关
		reference operator[](const difference_type i) {
			return *(begin() + i);
		}
		const_reference operator[](const difference_type i) const {
			return *(cbegin() + i);
		}
		reference front() {
			return *(begin() - 1);
		}
		reference back() {
			return *(end() - 1);
		}
		reference data() {
			return Start_;
		}

		//修改相关
		void clear();
		void swap(vector& v);
		void push_back(const value_type& value);
		void pop_back();
		iterator insert(iterator position, const value_type& val);
		void insert(iterator position, const size_type& n, const value_type& val);
		template<class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);

	private:
		oid destroyAndDeallocateAll();
		void allocateAndFillN(const size_type n, const value_type& value);
		template<class InputIterator>
		void allocateAndCopy(InputIterator first, InputIterator last);

		template<class InputIterator>
		void vector_aux(InputIterator first, InputIterator last, std::false_type);
		template<class Integer>
		void vector_aux(Integer n, const value_type& value, std::true_type);
		template<class InputIterator>
		void insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type);
		template<class Integer>
		void insert_aux(iterator position, Integer n, const value_type& value, std::true_type);
		template<class InputIterator>
		void reallocateAndCopy(iterator position, InputIterator first, InputIterator last);
		void reallocateAndFillN(iterator position, const size_type& n, const value_type& val);
		size_type getNewCapacity(size_type len)const;

	public:
		template<class ELEM, class TEMP>
		friend bool operator == (const vector<ELEM, TEMP>& v1, const vector<ELEM, TEMP>& v2);
		template<class ELEM, class TEMP>
		friend bool operator != (const vector<ELEM, Alloc>& v1, const vector<ELEM, TEMP>& v2);
	};
}

#endif // !VECTOR_H
