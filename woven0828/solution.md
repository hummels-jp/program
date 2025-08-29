
解题目标：
	1 求多个多边形之间的重叠区域，当重叠区域超过该多边形面积的50%时，在输出结果中，不显示该多边形。
业务逻辑：

创建类 Point
	1 私有成员：
	  double x_; // x坐标
	  double y_; // y 坐标
	  
创建类 Polygon
	私有成员：
	  vector<Point> points_; // 存储多边形的顶点坐标
	  double area_; //存储多边形的面积，防止多次计算。
	  double max_ratio_; // 计算与其他多边形相加时，相交面积与自身面积比值的最大值。
	  
	成员函数：
	  1 点是否在多边形内部(射线法)
	  bool point_inside_polygon(const Point& point);
	  
	  2 判断两个多边形是否相交(边相交法)
	  bool polygon_overlap(const Polygon& other);
	  
	  3 计算多边形的面积(showlace 方法), 使用变量存储，只计算一次面积。
	  double get_area();
	  
	  4 计算2个相交多边形的重叠部分，得到一个新的多边形，同时更新 max_ratio_ 的值
	  void polygon_clip(const Polygon& other);
	  
创建类 PolygonFilter
	私有成员：
		vector<Polygon> polygons_; // 存储需要进行过滤的所有Polygon
	
	成员方法：
		1 从Json 文件中读取Polygon数据，生成对应的polygon集合
		void read_json();

		1 对集合中的所有Polygon，两两循环，计算2个多边形之间的重叠比例，并更新每个Polygon的 max_ratio_ 比例
		void loop_filter();
		
		2 遍历集合中的Polygon， 输出 max_ratio_ 比例小于0.5 的Polygon 到 output.json 文件中去。
		void output_result();




线程池逻辑：
	1 创建线程池，属于计算密集型任务，可以将2个Polygon之间的重叠区域计算包装成 package_task 进行异步执行。
	2 算法复杂度为 N*N*10*5 一个多边形有10个顶点左右，有5条变参与计算。
	3 分别统计单线程或多线程条件下，执行时间的区别

		100条	1000条	10000条
单线程   24ms 	1758 ms  156498 ms
多线程   13ms   348 ms   21729 ms

	4 线程数量等于CPU的核心数


使用线程池进行并行计算
1 线程池类型， 固定数量的线程池  可变数量的线程池(在达到固定数量后，针对小任务可以动态增加和销毁的线程)
2 任务队列，每个任务处理 当前多边形idx 和 之后所有多边形的交集


线程池类

	![alt text](image.png)
	  
	  