# Calculation

1. 矩阵求特征值、特征向量   

2. 矩阵求条件数    

   $$cond(A)=\Vert{A}\Vert\Vert{A^{-1}}\Vert$$

   可选2-条件数 cond(A)   

    $$||A||_2=\sqrt{\lambda_{max}(A^TA)} $$

   无穷-条件数 cond(A,inf)

   $$\Vert A \Vert_\infty = \max_{1\le i\le n} \sum_{i=1}^n |a_{ij}|$$

3. 求解矩阵 Ax=b  
   $$
   \begin{bmatrix}
   a_{00} & a_{01} & \cdots\ & a_{0n} \\
   a_{10} & a_{11} & \cdots\ & a_{1n} \\
   \vdots\ & \vdots\ & & \vdots\ \\
   a_{n0} & a_{n1} & \cdots\ & a_{nn} \\
   \end{bmatrix}
   \begin{bmatrix}
   x_{0} \\
   x_{1}  \\
   \vdots\ \\
   x_{n}  \\
   \end{bmatrix}
   =
   \begin{bmatrix}
   b_{0} \\
   b_{1}  \\
   \vdots\ \\
   b_{n}  \\
   \end{bmatrix}
   $$

4. 求解高阶方程  

   $a_n *x^n+a_{n-1}*x^{n-1}+...+a_0*x^0=0$

5. 求解定积分  

   quad()   Romberg()

6. 求解常微分方程  

   $y'=f(t,y)$ $a \le t \le b$  $y(a)=ya$  左边只有一阶

7. 曲线拟合 

8. 绘图 可视化

9. 交互式shell