#include "Cubic_Spline.h"

vector<Point> Cubic_Spline::cubic_Spline(vector<Point> p, int Type){
    int n=p.size()-1;
    double x[MAX_N], f[MAX_N], a[MAX_N], b[MAX_N], c[MAX_N], d[MAX_N];
    double s0=0, sn=0, Fmax = INF, t0, tm, h, t, xmax=-1e10, xmin=1e10, yres;
    vector<Point> res;
    for(int i=0;i<=n;i++){
        x[i]=p[i].first;
        f[i]=p[i].second;
        if(x[i]>xmax) xmax=x[i];
        if(x[i]<xmin) xmin=x[i];
    }
    get_Cubic_Spline(n,x,f,Type,s0,sn,a,b,c,d);
    cout<<"abcd"<<endl;
    for (int i=1; i<=n; i++)
       cout<<" "<<a[i]<<" "<<b[i]<<" "<<c[i]<<" "<<d[i]<<endl;
    t0=xmax;tm=xmin;
    int m=50;
    h = (tm-t0)/(double)m;
    for (int i=m; i>=0; i--) {
        t = t0+h*(double)i;
        if((yres=S(t, Fmax, n, x, a, b, c, d))==Fmax)
            continue;
        else
            res.push_back(Point(t,yres));
        cout<<"f("<<t<<") ="<<S(t, Fmax, n, x, a, b, c, d)<<endl;
    }
    return res;
}

//natural: c0=s0/2  cn=sn/2
//clamped: f`(a)-->s0  f`(b)-->sn
void Cubic_Spline::get_Cubic_Spline(int n, double x[], double f[], int Type, double s0, double sn, double a[], double b[], double c[], double d[]){
    //pc=q
    double **p=(double**)malloc((n+1)*sizeof(double*));
    double **l=(double**)malloc((n+1)*sizeof(double*));
    double *q=(double*)malloc((n+1)*sizeof(double));
    double *h=(double*)malloc(n*sizeof(double));
    int i,j,k;
    for(i=0;i<n+1;i++){
        p[i]=(double*)malloc((n+1)*sizeof(double));
        memset(p[i],0,(n+1)*sizeof(double));
        l[i]=(double*)malloc((n+1)*sizeof(double));
        memset(l[i],0,(n+1)*sizeof(double));
        l[i][i]=1;
    }
    for(i=0;i<n;i++)
        h[i]=x[i+1]-x[i];
    for(i=0;i<n+1;i++) a[i]=f[i];

    //initialize p
    if(Type==1){
        p[0][0]=2*h[0];p[0][1]=h[0];
        p[n][n-1]=h[n-1];p[n][n]=2*h[n-1];
    }
    else if(Type==2)
       p[0][0]=p[n][n]=1;
    for(i=1;i<n;i++){
        p[i][i-1]=h[i-1];p[i][i]=2*(h[i-1]+h[i]);p[i][i+1]=h[i];
    }

    //initialize q
    if(Type==1){
        q[0]=3*(a[1]-a[0])/h[0]-3*s0;
        q[n]=3*sn-3*(a[n]-a[n-1])/h[n-1];
    }
    else if(Type==2){
        q[0]=s0/2;
        q[n]=sn/2;
    }
    for(i=1;i<n;i++)
        q[i]=3*(a[i+1]-a[i])/h[i]-3*(a[i]-a[i-1])/h[i-1];

    //P-->LU  l-->l  p-->u
    //Pc=q  LUc=q  y=uc ly=q  Uc=y
    //Ly=q  q-->y
    if(Type==1){
        for(i=0;i<n;i++){
            l[i+1][i]=p[i+1][i]/p[i][i];
            q[i+1]-=l[i+1][i]*q[i];
            p[i+1][i]=0;
            p[i+1][i+1]-=l[i+1][i]*p[i][i+1];
        }
    }
    else if(Type==2){
        l[1][0]=h[0];q[1]-=l[1][0]*q[0];p[1][0]=0;
        for(i=1;i<n-1;i++){
            l[i+1][i]=p[i+1][i]/p[i][i];
            q[i+1]-=l[i+1][i]*q[i];
            p[i+1][i]=0;
            p[i+1][i+1]-=l[i+1][i]*p[i][i+1];
        }
    }

    //Uc=q  pc=q
    for(i=n;i>0;i--){
        q[i]/=p[i][i];
        p[i][i]=1;
        q[i-1]-=p[i-1][i]*q[i];
    }
    q[0]/=p[0][0]; //debug.........
    p[0][0]=1;

    memcpy(c,q,(n+1)*sizeof(double));
    for(i=0;i<n;i++){
        b[i]=(a[i+1]-a[i])/h[i]-(2*c[i]+c[i+1])*h[i]/3;
        d[i]=(c[i+1]-c[i])/(3*h[i]);
    }

    for(i=n;i>0;i--){
        a[i]=a[i-1];b[i]=b[i-1];c[i]=c[i-1];d[i]=d[i-1];
    }
}

double Cubic_Spline::S( double t, double Fmax, int n, double x[], double a[], double b[], double c[], double d[] ){
    int i;
    if(t-x[n]>ZERO||x[0]-t>ZERO) return Fmax;
    if(fabs(t-x[0])<ZERO) i=1;
    else{
        for(i=1;i<=n;i++){
           if(t>x[i-1]&&t<=x[i]) break;
        }
    }
    return a[i]+b[i]*(t-x[i-1])+c[i]*(t-x[i-1])*(t-x[i-1])+d[i]*(t-x[i-1])*(t-x[i-1])*(t-x[i-1]);
}


