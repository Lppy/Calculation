# Calculation

A light and simple mini Matlab.

#### Dependency

* Qt 5+

#### Author

* 陈宏霖：组长，ViewModel , Model
* 李朋洋：View, 持续集成部署服务器
* 蔡孜涵：Model, 测试
* 陈星宇：Model, 测试

#### Usage

1. 矩阵求条件数    

   * 可选2-条件数 cond(A)  

   ~~~ 
   Cond2 A=[1,2,3;4,5,6;7,8,9]
   ~~~

   * 无穷-条件数 cond(A,inf)

   ~~~
   CondInf A=[1,1,2;6,5,0;71,8,9]
   ~~~

2. 求解矩阵 Ax=b  

   ~~~
   A=[1,2,3;4,5,6;7,8,9]
   b=[0;0;0]
   solveMatrix Ax=b
   ~~~

3. 求解高阶方程  

   ~~~
   solvePoly  6*x^6+4*x^3+2*x^1+1=0
   solvePoly  1*x^2+2*x^1+1=0
   ~~~

4. 求解定积分  

   ~~~
   Int  6*x^6+4*x^3+2*x+1 (1,2)		
                        //上下限
   ~~~

5. 求解常微分方程  

   ```
   Ode dy/dt=y^2-t^4+y^3-t+100 (0,1) y(0)=0
   Ode dy/dt=y-t^2+1 (0,2) y(0)=0.5
   ```

6. 自然样条拟合

   ~~~
   Fit (0,0) (1,1) (2,2)
   ~~~

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
