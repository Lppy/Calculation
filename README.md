# Calculation

A light and simple mini Matlab.

#### Dependency

* Qt 5+

#### Author

* 陈宏霖：组长，ViewModel , Model
* 李朋洋：View, 持续集成部署服务器
* 蔡孜涵：Model, 测试
* 陈星宇：Model, 测试

#### Download

###### Windows

1. Download from [here][]

   [here]: 10.189.247.225:8888/Project.rar

2.  Unzip and run

#### Usage

1. 矩阵求特征值、特征向量   

2. 矩阵求条件数    

   可选2-条件数 cond(A)  

   ~~~ 
   Cond2 A=[1,2,3;4,5,6;7,8,9]
   ~~~

   无穷-条件数 cond(A,inf)

   ~~~
   CondInf A=[1,1,2;6,5,0;71,8,9]
   ~~~

3. 求解矩阵 Ax=b  

   ~~~
   A=[1,2,3;4,5,6;7,8,9]
   b=[6;15;24]
   solve Matrix Ax=b
   ~~~

4. 求解高阶方程  

   ~~~
   solve Poly  6*x^6+4*x^3+2*x+1=0
   solve Poly  1*x^2+2*x^1+1=0
   ~~~

5. 求解定积分  

   ~~~
   Int  6*x^6+4*x^3+2*x+1 (1,2)		
                        //上下限
   ~~~

6. 求解常微分方程  

   ```
   dy/dt=y^2-t^4+y^3-t+100 (0,1) y(0)=0
   dy/dt=y-t^2+1 (0,2) y(0)=0.5
   ```

7. 曲线拟合 

   ~~~
   Curve (0,1) (1,2) (9,10) (40,21) (6,3) (7,-10) (33,-19)
   ~~~

8. 折线图

   ~~~
   BrokenLine (0,1)  (9,10) (40,21) (6,3) (33,-19)
   ~~~

9. 数值计算

   ~~~
   a=1
   b=2
   c=44
   a*b-c
   ~~~

   ​