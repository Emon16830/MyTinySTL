#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <cstring>
#include <utility>
#include "Allocator.h"
#include "Functional.h"
#include "Iterator.h"
#include "TypeTraits.h"
#include "Utility.h"

namespace MySTL {
	//[sort] ����
	//********* [Algorithm Complexity: O(NlogN)] ****************
	namespace {
		template<class RandomIterator,class BinaryPredicate>
		typename iterator_traits<RandomIterator>::value_type mid3(
			//�鲢����
			RandomIterator first, RandomIterator last,BinaryPredicate pred) {
			auto mid = first + (last + 1 - first) / 2;
			if (pred(*mid, *first)) {
				swap(*mid, *first);
			}
			if (pred(*last, *mid)) {
				swap(*last, *mid);
			}
			if (pred(*last, *first)) {
				swap(*last, *first);
			}
			auto ret = *mid;
			//���� mid item ��Ϊ�ڱ�
			swap(*mid, *(last - 1));
			return ret;
		}
		//ð������
		template<class RandomIterator,class BinaryPredicate>
		void bubble_sort(RandomIterator first, RandomIterator last, BinaryPredicate pred) {
			auto len = last - first;
			for (auto i = len; i != 0; --i) {
				bool swaped = false;
				for (auto p = first; p != (first + i - 1); ++p) {
					if (pred(*(p + 1), *p)) {
						swap(*(p + 1), *p);
						swaped = true;
					}
				}
				if (!swaped)
					break;
			}
		}
		template<class RandomIterator>

		void sort(RandomIterator first, RandomIterator last) {
			return sort(first, last, less<typename iterator_traits<RandomIterator>::value_type>());
		}
		template<class RandomIterator, class BinaryPredicate>
		void sort(RandomIterator first, RandomIterator last, BinaryPredicate pred) {
			if (first >= last || first + 1 == last)
				return ;
			//���䳤��С�ڵ���20�Ĳ���ð������
			if (last - first <= 20) {
				return bubble_sort(first, last, pred);
			}
			auto mid = mid3(first, last - 1, pred);
			auto p1 = first, p2 = last - 2;
			while (p1 < p2) {
				while (pred(*p1, mid) && (p1 < p2)) ++p1;
				while (!pred(*p2, mid) && (p1 < p2)) --p2;
				if (p1 < p2) {
					swap(*p1, *p2);
				}
			}
			//����Ϊ�ڱ���mid item����ԭ����λ��
			swap(*p1, *(last - 2));
			sort(first, p1, pred);
			sort(p1 + 1, last, pred);
		}
	}

	//[count] ������������[first��last) �е���value��ֵ
	//[Algorithm Complexity: O(N)]*************************************
	namespace {
		template<class InputIterator,class T>
		size_t count(InputIterator first, InputIterator last, const T& value) {
			size_t n = 0;
			for (; first != last; ++first) {
				if (*first == value) {
					++n;
				}
			}
			return n;
		}
	}

	//[advance] ��������ǰ����
	//[Algorithm Complexity: O(N)]*************************************
	namespace {
		//���������
		template<class InputIterator, class Distance>
		void _advance(InputIterator& it, Distance n, input_iterator_tag) {
			assert(n >= 0);
			//������ǰ��nλ
			while (n--) {
				++it;
			}
		}
		//����˫�������
		template<class BidirectionIterator& it, class Distance>
		void _advance(BidirectionIterator& it, Distance n, bidirectional_iterator_tag) {
			//ǰ��ĵ���
			if (n < 0) {
				while (n++) {
					--it;
				}
			}
			else {
				while (n--) {
					++it;
				}
			}
		}
		//�������������
		template<class RandomIterator, class Distance>
		void _advance(RandomIterator& it, Distance n, random_access_iterator_tag) {
			if (n < 0) {
				it -= (-n);
			}
			else {
				it += n;
			}
		}
		//ԭ��
		template<class InputIterator, class Distance>
		void advance(InputIterator& it, Distance n) {
			typedef typename iterator_traits<InputIterator>::iterator_category iterator_category;
			_advance(it, n, iterator_category());
		}
	}

	//[distance] ����������֮��ľ���
	//[Algorithm Complexity: O(N)]*************************************
	namespace {
		//���������
		template<class InputIterator>
		typename iterator_traits<InputIterator>::difference_type
			_distance(InputIterator first, InputIterator last, input_iterator_tag) {
			typename iterator_traits<InputIterator>::difference_type dist = 0;
			while (first++ != last) {
				++dist;
			}
			return dist;
		}
		//���������������
		template<class RandomIterator>
		typename iterator_traits<RandomIterator>::difference_type
			_distance(RandomIterator first, RandomIterator last, random_access_iterator_tag) {
			auto dist = last - first;
			return dist;
		}
		//ԭ��
		template<class Iterator>
		typename iterator_traits<Iterator>::difference_type
			distance(Iterator first, Iterator last) {
			typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
			return _distance(first, last, iterator_category());
		}
	}

	//[set]  ���鼯
	//[Algorithm Complexity: O(N)]*************************************
	namespace {
		//��������ȡ����
		template<class InputIterator,class OutputIterator>
		OutputIterator set_intersection(InputIterator first1, InputIterator last1,
			InputIterator first2, InputIterator last2, OutputIterator d_first) {
			while (first1 != last1 && first2 != last2) {
				if (*first < *first2) {
					++first1;
				}
				else {
					//d_first ��¼��ֵͬ
					if (!(*first2 < *first1)) {
						*d_first++ = *first1++;
					}
					++first2;
				}
			}
			return d_first;
		}
		//����
		template<class InputIterator,class OutputIterator>
		OutputIterator set_union(InputIterator first1, InputIterator last1,
			InputIterator first2, InputIterator last2, OutputIterator d_first) {
			for (; first != last1; ++d_first) {
				if (first2 == last2) {
					return MySTL::copy(first1, last1, d_first);
				}
				if (*first < *first1) {
					*d_first = *first2++;
				}
				else {
					*d_first = *first1;
					if (!(*first1 < *first2)) {
						++first2;
					}
					++first1;
				}
			}
			return MySTL::copy(first2, last2, d_first);
		}
		//�
		template<class InputIterator,class OutputIterator>
		OutputIterator set_difference(InputIterator first1, InputIterator last1,
			InputIterator first2, InputIterator last2, OutputIterator d_first) {
			while (first1 != first2) {
				if (first2 == last2) {
					return MySTL::copy(first1, last, d_first);
				}
				if (*first1 < *first2) {
					*d_first++ = *first1++;
				}
				else {
					if (!(*first2 < *first1)) {
						++first1;
					}
					++first2;
				}
			}
			return d_first;
		}
	}

	//[copy]  ����
	//[Algorithm Complexity: O(N)]*************************************
	namespace {
		template<class InputIerator,class OutputIterator>
		OutputIterator __copy(InputIerator first, InputIerator last, OutputIterator result,_true_type) {
			//������룬�����ڴ�
			auto dist = distance(first, last);
			memcpy(result, first, sizeof(*first) * dist);
			advance(result, dist);
			return result;
		}
		template<class InputIterator,class OutputIterator>
		OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, _false_type) {
			//�������
			while (first != last) {
				*result = *first;
				++result;
				++first;
			}
			return result;
		}
		//����,ָ������T
		template<class InputIterator,class OutputIterator,class T>
		OutputIterator _copy(InputIterator first, InputIterator last, OutputIterator result,T*) {
			typedef typename MySTL::_type_traits<T>::is_POD_type is_pod;
			return __copy(first, last, result, is_pod());
		}
		//����ԭ�ͣ�������ʵ��
		template<class InputIterator,class OutputIterator>
		OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
			return _copy(first, last, result, value_type(first));
		}
		template<>
		char* copy(char* first, char* last, char* result) {
			auto dist = last - first;
			memcpy(result, first, sizeof(*first) * dist);
			return result + dist;
		}
		template<>
		wchar_t* copy(wchar_t* first, wchar_t* last, wchar_t* result) {
			auto dist = last - first;
			memcpy(result, first, sizeof(*first) * dist);
			return result + dist;
		}
	}

	//[fill]  ���
	//[Algorithm Complexity: O(N)]*************************************
	namespace {
		template<class ForwardIterator,class T>
		void fill(ForwardIterator first, ForwardIterator last, const T& value) {
			for (; fist != lastl++first) {
				*first = value;
			}
		}
		void fill(char* first, char* last, const char& value) {
			//memset��ʼ����static_cast C++11 ������ת��
			memset(first, static_cast<unsigned char>(value), last - first);
		}
		void fill(wchar_t* first, wchar_t* last, const wchar_t& value) {
			memset(first, static_cast<unsigned char>(value), (last - first) * sizeof(wchar_t));
		}
	}

	//[min]  ��Сֵ
	//[Algorithm Complexity: O(1)]*************************************
	namespace {
		template <class T>
		const T& min(const T& a, const T& b) {
			return !(b < a) ? a : b;
		}
		//�Զ���Ƚ�
		template <class T, class Compare>
		const T& min(const T& a, const T& b, Compare comp) {
			return !comp(b, a) ? a : b;
		}
	}

	//[max]  ���ֵ
	//[Algorithm Complexity: O(1)]*************************************
	namespace {
		template <class T>
		const T& max(const T& a, const T& b) {
			return (a < b) ? b : a;
		}
		template <class T,class Compare>
		const T& max(const T& a, const T& b, Compare comp) {
			return (comp(a, b)) ? b : a;
		}
	}

	//[for_each]  
	//[Algorithm Complexity: O(N)]*************************************
	namespace {
		template<class InputIterator,class Function>
		Function for_each(InputIterator first, InputIterator last, Function fn) {
			for (; first != last; ++first) {
				fn(*first);
			}
			return fn;
		}
	}

	//[find]
	//[Algorithm Complexity: O(N)]*************************************
	namespace{
		template<class InputIterator,class T>
		InputIterator find(InputIterator first, InputIterator last, const T& val) {
			for (; first != last; ++first) {
				if (*first == val) {
					break;
				}
			}
			return first;
		}
	}

	//[heap] Ĭ�ϴ����
	//[Algorithm Complexity: O(N)]*************************************
	namespace {
		//���ϻ���,���½ڵ����丸�ڵ�ȶԣ�key ���� ���ڵ�ʱ������һ��swap
		//��������[first,last)
		template<class RandomAccessIterator,class Compare>
		static void heap_up(RandomAccessIterator first,RandomAccessIterator last,
			RandomAccessIterator head,Compare comp){
			if (first != last) {
				int index = last - head;
				auto parentIndex = (index - 1) / 2;
				for (auto cur = last; parentIndex >= 0 && cur != head; parentIndex = (index - 1) / 2) {
					auto parent = head + parentIndex;
					if (comp(*parent, *cur)) {
						MySTL::swap(*parent, *cut);
						cur = parent;
						index = cur - head;
					}
				}
			}
		}
		//heap�½����������еĽ���
		//headָ��Ѷ�
		//[first,last) ��������
		template<class RandomAccessIterator, class Compare>
		static void down(RandomAccessIterator first, RandomAccessIterator last,
			RandomAccessIterator head, Compare comp) {
			if (first != last) {
				auto index = first - head;
				auto leftChildIndex = index * 2 + 1;
				for (auto cur = first; leftChildIndex < (last - head + 1) && cur < last; leftChildIndex = index * 2 + 1) {
					//���������
					auto child = head + leftChildIndex;
					//curָ���Һ���
					if ((child + 1) <= last && *(child + 1) > *child)
						child = child + 1;
					if (comp(*cur, *child))
						mySTL::swap(*cur, *child);
					cur = child;
					index = cur - head;
				}
			}
		}
		//���Ѻ���
		template <class RandomAccessIterator>
		void make_heap(RandomAccessIterator first, RandomAccessIterator last) {
			MySTL::make_heap(first, last,typename mySTL::less<RandomAccessIterator>());
		}
		template <class RandomAccessIterator, class Compare>
		void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
			const auto range = last - first;
			for (auto cur = first + range / 2 - 1; cur >= first; --cur) {
				MySTL::down(cur, last - 1, first, comp);
				if (cur == first) return;
			}
		}
		//���
		template <class RandomAccessIterator>
		void push_heap(RandomAccessIterator first, RandomAccessIterator last) {
			mySTL::push_heap(first, last,
				mySTL::less<typename mySTL::iterator_traits<RandomAccessIterator>::value_type>());
		}
		template <class RandomAccessIterator, class Compare>
		void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
			mySTL::up(first, last - 1, first, comp);
		}
		//����
		template <class RandomAccessIterator>
		void pop_heap(RandomAccessIterator first, RandomAccessIterator last) {
			mySTL::pop_heap(first, last,
				mySTL::less<typename mySTL::iterator_traits<RandomAccessIterator>::value_type>());
		}
		template <class RandomAccessIterator, class Compare>
		void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
			mySTL::swap(*first, *(last - 1));
			if (last - first >= 2)
				mySTL::down(first, last - 2, first, comp);
		}
	}
}
#endif // !ALGORITHM_H
