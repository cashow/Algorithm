int fun(int month,int date,int year,int hour)	//month,date,year,hour��2000��1��1��0��
{									//��λ��hour
    bool special=(year%4==0);			//���������Ҫ��һ��
    int tem=hour;
    tem+=(date-1)*24;
    tem+=sum[month-1]*24;
    if(special&&month>2)
        tem+=24;

    for(int i=2000; i<year; i++)
    {
        if(i%4==0)
            tem+=366*24;
        else
            tem+=365*24;
    }
    return tem;
}
