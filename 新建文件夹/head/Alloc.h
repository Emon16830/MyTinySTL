#ifndef ALLOC_H
#define ALLOC_H

#include <cstdlib>
#include <memory.h>

namespace MySTL {
	/*
	* �ռ��������ĵײ�ʵ��
	* �ڲ�
	*/
	class alloc {
	private:
		//enum ö�ٴ��������еĳ���

		//С�͵Ŀ������ϵ��߽�
		enum EAlign { ALIGN = 8 };
		//С�͵���������� 128 Bytes���������� malloc ����
		enum EMaxBytes { MAXBYTES = 128 };
		//free - lists �ĸ��� max = 16
		enum ENFreeLists { NFREELISTS = (EMaxBytes::MAXBYTES / EAlign::ALIGN) };
		//ÿ�����ӵĽڵ���
		enum ENObjs { NOBJS = 20 };
	private:
		//free - lists �Ľڵ㹹��
		union obj {
			union obj* next;
			char client[1];
		};
		static obj* free_list[ENFreeLists::NFREELISTS];
	private:

		//�ڴ����ʼλ��
		static char* start_free;
		//�ڴ�ؽ���λ��
		static char* end_free;
		static size_t heap_size;
	private:
		//��bytes �ϵ���8�ı���
		static size_t ROUND_UP(size_t bytes) {
			return ((bytes + EAlign::ALIGN - 1) & ~(EAlign::ALIGN - 1));
		}
		//��������Ĵ�С������ʹ�õ� n �� free - list ��n�� 0 ��ʼ
		static size_t FREELIST_INDEX(size_t bytes) {
			return (((bytes)+EAlign::ALIGN - 1) / EAlign::ALIGN - 1);
		}
		//����һ����СΪ n �Ķ��󣬲������СΪ n ���������鵽 free - list��
		static void* refill(size_t n);
		//����һ���ռ䣬������ nobjs ����СΪ size ������
		//������� nobjs �������������㣬nobjs ���ܻή��
		static char* chunk_alloc(size_t size, size_t& nobjs);

	public:
		static void* allocate(size_t bytes);
		static void deallocate(void* ptr, size_t bytes);
		static void* reallocate(void* ptr, size_t old_sz, size_t new_sz);
	};

	//���� 16 ��free_list 
	alloc::obj* alloc::free_list[alloc::ENFreeLists::NFREELISTS] = {
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0, 
		0, 0, 0, 0,
	};

	//��ʼ���ڴ�ص�λ��
	char* alloc::start_free = 0;
	char* alloc::end_free = 0;
	size_t alloc::heap_size = 0;

	//���� bytes �����ڴ�
	void* alloc::allocate(size_t bytes) {
		if (bytes > EMaxBytes::MAXBYTES) {
			return malloc(bytes);
		}
		size_t index = FREELIST_INDEX(bytes);
		obj* list = free_list[index];
		//��ǰlist ���пռ�����
		if (list) {
			free_list[index] = list->next;
			return list;
		}
		//��ǰ������ڴ����128������Ҫȥ�ڴ����ȡ�ռ�
		else {
			return refill(ROUND_UP(bytes));
		}
	}

	//�ͷŶ�����ռ�õ��ڴ�ռ�
	void alloc::deallocate(void* ptr, size_t bytes) {
		// �ͷ�ptrָ����ڴ�ռ�
		if (bytes > EMaxBytes::MAXBYTES) {
			free(ptr);
		}
		else {
			//index ��¼ʹ�õڼ��������ڴ�ռ�
			size_t index = FREELIST_INDEX(bytes);
			//ptr תΪobj ��node ��¼
			obj* node = static_cast<obj*>(ptr);
			node->next = free_list[index];
			free_list[index] = node;
		}
	}

	//���������ڴ�
	void* alloc::reallocate(void* ptr, size_t old_sz, size_t new_sz) {
		deallocate(ptr, old_sz);
		ptr = allocate(new_sz);
		return ptr;
	}

	//����һ����СΪ n �Ķ�������ʱ���Ϊ�ʵ��� free_list ���ӽڵ�
	//�˴�����bytes �Ѿ��ϵ�Ϊ 8 �ı���
	void* alloc::refill(size_t bytes) {
		size_t nobjs = ENObjs::NOBJS;
		//���ڴ����ȡ
		char* chunk = chunk_alloc(bytes, nobjs);
		obj** my_free_list = 0;
		obj* result = 0;
		obj* current_obj = 0, * next_obj = 0;
		//ȡ���Ŀռ�ֻ��һ������ʹ��
		if (nobjs == 1) {
			return chunk;
		}
		else {
			my_free_list = free_list + FREELIST_INDEX(bytes);
			result = (obj*)(chunk);
			*my_free_list = next_obj = (obj*)(chunk + bytes);
			//ȡ������Ŀռ�ֱ�Ӽ����Ӧ�� free_list ��
			for (int i = 1;; ++i) {
				current_obj = next_obj;
				next_obj = (obj*)next_obj + bytes;
				if (nobjs - 1 == i) {
					current_obj->next = 0;
					break;
				}
				else {
					current_obj->next = next_obj;
				}
			}
			return result;
		}
	}

	//���� bytes �Ѿ��ϵ�Ϊ 8 �ı���
	char* alloc::chunk_alloc(size_t bytes, size_t& nobjs) {
		char* result = 0;
		size_t total_bytes = bytes * nobjs;
		size_t bytes_left = end_free - start_free;
		//�ڴ�ص�ǰ��ʣ��ռ��㹻
		if (bytes_left >= total_bytes) {
			result = start_free;
			start_free = start_free + total_bytes;
			return result;
		}
		//�ڴ��ʣ��ռ䲻����ȫ�������󣬵����ܹ���Ӧһ���������ϵ�����
		else if(bytes_left >= bytes) {
			nobjs = bytes_left / bytes;
			total_bytes = nobjs * bytes;
			result = start_free;
			start_free += total_bytes;
			return result;
		}
		//�ڴ��ʣ��ռ���һ������Ĵ�С���޷��ṩ
		else {
			size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
			if (bytes_left > 0) {
				obj** my_free_list = free_list + FREELIST_INDEX(bytes_left);
				((obj*)start_free)->next = *my_free_list;
				*my_free_list = (obj*)start_free;
			}
			start_free = (char*)malloc(bytes_to_get);
			if (!start_free) {
				obj** my_free_list = 0, * p = 0;
				for (int i = 0; i <= EMaxBytes::MAXBYTES; i += EAlign::ALIGN) {
					my_free_list = free_list + FREELIST_INDEX(i);
					p = *my_free_list;
					if (p != 0) {
						*my_free_list = p->next;
						start_free = (char*)p;
						end_free = start_free + 1;
						return chunk_alloc(bytes, nobjs);
					}
				}
				end_free = 0;
			}
			heap_size += bytes_to_get;
			end_free = start_free + bytes_to_get;
			return chunk_alloc(bytes, nobjs);
		}
	}
};
#endif // !ALLOC_H
