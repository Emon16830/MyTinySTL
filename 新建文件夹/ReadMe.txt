自定义模板类MyTinySTL

功能实现：
容器：
	vector，list，duque，queue，map（使用了RBtree建立），set（使用RBtree建立）

算法:
	sort：采用快速排序中递归树阈值的思想。当数量在20以内时，即递归树深度位于四层内，采用冒泡排序。超过20层时，采用递归式的归并排序
	count：计数器，计算[frist,last)中等于value的值
	advance：迭代器向前遍历
	distance：计算两个迭代器之间的距离
	set：并查集操作，其中并集前提要求序列式容器必须有序。差集和合集无要求
	copy： 复制
	fill：从last开始，填充first位，值为value
	min：取最小值
	max：取最大值
	for_each:循环对[first，last）中的迭代器调用函数
	find：在序列式容器中查找value，存在则返回
	heap相关：默认大根堆

配置器：
	内存分配，通过一级空间配置器（即 allocate ， deallocate 和 reallocate）和二级空间配置器（16个free_list自由链表）直接对内存池进行调配。

迭代器：
	根据模板类和泛型编程，分别实现输入迭代器，输出迭代器，前向迭代器，双向迭代器，以及随机迭代器

仿函数：
	通过重载operator() 的class 实现

适配器
	使用unarry和binarry 两个基类实现
	

