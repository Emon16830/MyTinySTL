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
	//[sort] 排序
	//********* [Algorithm Complexity: O(NlogN)] ****************
	namespace {
		template<class RandomIterator,class BinaryPredicate>
		typename iterator_traits<RandomIterator>::value_type mid3(
			//归并排序
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
			//交换 mid item 作为哨兵
			swap(*mid, *(last - 1));
			return ret;
		}
		//冒泡排序
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
			//区间长度小于等于20的采用冒泡排序
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
			//将作为哨兵的mid item换回原来的位置
			swap(*p1, *(last - 2));
			sort(first, p1, pred);
			sort(p1 + 1, last, pred);
		}
	}

	//[count] 计数迭代器中[first，last) 中等于value的值
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

	//[advance] 迭代器向前遍历
	//[Algorithm Complexity: O(N)]*************************************
	namespace {
		//输入迭代器
		template<class InputIterator, class Distance>
		void _advance(InputIterator& it, Distance n, input_iterator_tag) {
			assert(n >= 0);
			//迭代器前移n位
			while (n--) {
				++it;
			}
		}
		//重载双向迭代器
		template<class BidirectionIterator& it, class Distance>
		void _advance(BidirectionIterator& it, Distance n, bidirectional_iterator_tag) {
			//前后的迭代
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
		//重载随机迭代器
		template<class RandomIterator, class Distance>
		void _advance(RandomIterator& it, Distance n, random_access_iterator_tag) {
			if (n < 0) {
				it -= (-n);
			}
			else {
				it += n;
			}
		}
		//原型
		template<class InputIterator, class Distance>
		void advance(InputIterator& it, Distance n) {
			typedef typename iterator_traits<InputIterator>::iterator_category iterator_category;
			_advance(it, n, iterator_category());
		}
	}

	//[distance] 两个迭代器之间的距离
	//[Algorithm Complexity: O(N)]*************************************
	namespace {
		//输入迭代器
		template<class InputIterator>
		typename iterator_traits<InputIterator>::difference_type
			_distance(InputIterator first, InputIterator last, input_iterator_tag) {
			typename iterator_traits<InputIterator>::difference_type dist = 0;
			while (first++ != last) {
				++dist;
			}
			return dist;
		}
		//随机迭代器的重载
		template<class RandomIterator>
		typename iterator_traits<RandomIterator>::difference_type
			_distance(RandomIterator first, RandomIterator last, random_access_iterator_tag) {
			auto dist = last - first;
			return dist;
		}
		//原型
		template<class Iterator>
		typename iterator_traits<Iterator>::difference_type
			distance(Iterator first, Iterator last) {
			typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
			return _distance(first, last, iterator_category());
		}
	}

	//[set]  并查集
	//[Algorithm Complexity: O(N)]*************************************
	namespace {
		//有序数列取交集
		template<class InputIterator,class OutputIterator>
		OutputIterator set_intersection(InputIterator first1, InputIterator last1,
			InputIterator first2, InputIterator last2, OutputIterator d_first) {
			while (first1 != last1 && first2 != last2) {
				if (*first < *first2) {
					++first1;
				}
				else {
					//d_first 记录相同值
					if (!(*first2 < *first1)) {
						*d_first++ = *first1++;
					}
					++first2;
				}
			}
			return d_first;
		}
		//并集
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
		//差集
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

	//[copy]  复制
	//[Algorithm Complexity: O(N)]*************************************
	namespace {
		template<class InputIerator,class OutputIterator>
		OutputIterator __copy(InputIerator first, InputIerator last, OutputIterator result,_true_type) {
			//计算距离，拷贝内存
			auto dist = distance(first, last);
			memcpy(result, first, sizeof(*first) * dist);
			advance(result, dist);
			return result;
		}
		template<class InputIterator,class OutputIterator>
		OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, _false_type) {
			//逐个拷贝
			while (first != last) {
				*result = *first;
				++result;
				++first;
			}
			return result;
		}
		//重载,指向类型T
		template<class InputIterator,class OutputIterator,class T>
		OutputIterator _copy(InputIterator first, InputIterator last, OutputIterator result,T*) {
			typedef typename MySTL::_type_traits<T>::is_POD_type is_pod;
			return __copy(first, last, result, is_pod());
		}
		//函数原型，迭代器实现
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

	//[fill]  填充
	//[Algorithm Complexity: O(N)]*************************************
	namespace {
		template<class ForwardIterator,class T>
		void fill(ForwardIterator first, ForwardIterator last, const T& value) {
			for (; fist != lastl++first) {
				*first = value;
			}
		}
		void fill(char* first, char* last, const char& value) {
			//memset初始化，static_cast C++11 的类型转换
			memset(first, static_cast<unsigned char>(value), last - first);
		}
		void fill(wchar_t* first, wchar_t* last, const wchar_t& value) {
			memset(first, static_cast<unsigned char>(value), (last - first) * sizeof(wchar_t));
		}
	}

	//[min]  最小值
	//[Algorithm Complexity: O(1)]*************************************
	namespace {
		template <class T>
		const T& min(const T& a, const T& b) {
			return !(b < a) ? a : b;
		}
		//自定义比较
		template <class T, class Compare>
		const T& min(const T& a, const T& b, Compare comp) {
			return !comp(b, a) ? a : b;
		}
	}

	//[max]  最大值
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

	//[heap] 默认大根堆
	//[Algorithm Complexity: O(N)]*************************************
	namespace {
		//向上回溯,将新节点与其父节点比对，key 大于 父节点时，进行一个swap
		//序列容器[first,last)
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
		//heap下降，有序序列的建树
		//head指向堆顶
		//[first,last) 序列容器
		template<class RandomAccessIterator, class Compare>
		static void down(RandomAccessIterator first, RandomAccessIterator last,
			RandomAccessIterator head, Compare comp) {
			if (first != last) {
				auto index = first - head;
				auto leftChildIndex = index * 2 + 1;
				for (auto cur = first; leftChildIndex < (last - head + 1) && cur < last; leftChildIndex = index * 2 + 1) {
					//获得其左孩子
					auto child = head + leftChildIndex;
					//cur指向右孩子
					if ((child + 1) <= last && *(child + 1) > *child)
						child = child + 1;
					if (comp(*cur, *child))
						mySTL::swap(*cur, *child);
					cur = child;
					index = cur - head;
				}
			}
		}
		//建堆函数
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
		//入堆
		template <class RandomAccessIterator>
		void push_heap(RandomAccessIterator first, RandomAccessIterator last) {
			mySTL::push_heap(first, last,
				mySTL::less<typename mySTL::iterator_traits<RandomAccessIterator>::value_type>());
		}
		template <class RandomAccessIterator, class Compare>
		void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
			mySTL::up(first, last - 1, first, comp);
		}
		//出堆
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
