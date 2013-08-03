const int maxn=100;
int mod=1000007;

struct matrix
{
    int data[maxn][maxn];
    int row,col;

    void init(int r,int c)          //初始为全零矩阵
    {
        row=r;
        col=c;
        MEM(data);
    }
    void init(int size)             //初始为单位矩阵
    {
        row=size;
        col=size;
        MEM(data);
        for(int i=0; i<size; i++)
            data[i][i]=1;
    }
};

matrix operator*(const matrix& m1,const matrix &m2)      //矩阵相乘
{
    matrix ret;
    ret.init(m1.row,m2.col);
    for(int i=0; i<m1.row; i++)
    {
        for(int j=0; j<m1.col; j++)
        {
            if(!m1.data[i][j])
                continue;
            for(int k=0; k!=m2.col; k++)
            {

                if(!m2.data[j][k])
                    continue;
                ret.data[i][k]=(ret.data[i][k]+((long long)m1.data[i][j]*m2.data[j][k]))%mod;
            }
        }
    }
    return ret;
}

matrix pow(matrix temp,int m)            //矩阵的快速幂
{
    matrix pret;
    pret.init(temp.row);
    while(m)
    {
        if(m&1)
            pret=temp*pret;
        temp=temp*temp;
        m>>=1;
    }
    return pret;
}

double det(matrix a)                //矩阵的行列式,这里的data要用double
{
    double key, det = 1;
    int i, j, k;
    for (i=0; i<a.row; i++)
    {
        if (a.data[i][i]==0)
        {
            for (j=i+1; j<a.row; j++)
            {
                if (a.data[j][i]==0)
                    continue;
                for (int k=i; k<a.row; k++)
                    swap(a.data[i][k], a.data[j][k]);
                det = -det;
                break;
            }
            if (j==a.row)
            {
                return 0;
            }
        }

        key = a.data[i][i];
        a.data[i][i] = 1;
        for (j=i+1; j<a.row; j++)
            a.data[i][j] /=  key;
        det *= key;

        for (j=0; j<a.row; j++)
        {
            if (i==j||a.data[j][i]==0)
                continue;
            key = a.data[j][i], a.data[j][i] = 0;
            for (k=i+1; k<a.row; k++)
                a.data[j][k] -= a.data[i][k] * key;
        }
    }
    return det;
}
