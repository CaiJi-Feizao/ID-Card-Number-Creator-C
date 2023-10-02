#include <stdio.h>
#include <stdlib.h>

int cnmint(char a){
    int b;
    if(a=='X')
        b=10;
    else
        b=a-48;
    return b;
}
char cnmstr(int a){
    char b;
    if(a==10)
        b='X';
    else
        b=a+48;
    return b;
}

int myd(char IDCard[18]){ //日期校验函数
    int ok=1;
    int mmstd[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int yyyy,leapyear=0;
    yyyy=cnmint(IDCard[6])*1000+cnmint(IDCard[7])*100+cnmint(IDCard[8])*10+cnmint(IDCard[9]);
    if((yyyy%4==0 && yyyy%100!=0)||yyyy%400==0)
        leapyear=1;
    else;
    int mm=cnmint(IDCard[10])*10+cnmint(IDCard[11]),
    dd=cnmint(IDCard[12])*10+cnmint(IDCard[13]);
    if(mm==2)
    {
        if(leapyear==1)
        {
            if(dd==0 || dd>29)
                {
                    ok=0;
                }
                else;
            }
        else
        {
            if(dd==0 || dd>mmstd[mm-1])
            {
                ok=0;
            }
            else;
        }
    }
    else if(mm==1 || (2<mm&&mm<13))
    {
        if(dd==0 || dd>mmstd[mm-1])
        {
            ok=0;
        }
        else;
    }
    else
        ok=0;
    return ok;
}

int mode(char IDCard[18]){
    int m=0; //0为验证，1为补全
    for(int i=0;i<18;i++) //判断哪位缺失
    {
        if((47<IDCard[i] && 58>IDCard[i]) || IDCard[i]=='X')
            m=0;
        else
        {
            m=1;
            break;
        }
    }
    return m;
}

int modeone(char IDCard[18]){
    int w[18]={7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2,1}; //加权码
    int sum=0;
    for(int i=0;i<18;i++)
    {
        sum+=w[i]*cnmint(IDCard[i]);
    }
    if(sum%11==1 && myd(IDCard)==1)
        return 1;
    else
        return 0;
}

int cnmpow(int a, int n){
    int sum=1;
    for(int i=0;i<n;i++)
        sum*=a;
    return sum;
}

int modetwo(char IDCard[18]){
    int hm=0;
    int w[18]={7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2,1}; //加权码
    int needornot[18]={0},times=0; //0为验证，1为补全
    for(int i=0;i<18;i++) //判断哪位缺失
    {
        if((47<IDCard[i] && 58>IDCard[i]) || IDCard[i]=='X')
        {
            needornot[i]=0;
        }
        else
        {
            needornot[i]=1;
            times++;
        }
    }
    if(needornot[17])
    {
        if(times>1)
        {
            for(int k=0;k<=10;k++)
            {
                IDCard[17]=cnmstr(k);
                for(int i=0;i<cnmpow(10,times-1);i++)
                {   
                    char cnmi[times-1];
                    itoa(i,cnmi,10);
                    char tem[times-1];
                    int teme=0;
                    for(int o=times-2;o>-1;o--)
                    {
                        if(cnmi[o]==0)
                        {
                            tem[times-2-o]='0';
                            teme++;
                        }
                        else
                            tem[times-2-o]=cnmi[times-2-o-teme];
                    }
                    for(int o=0;o<times-1;o++)
                    {
                        cnmi[o]=tem[o];
                    }
                    int place=0;
                    for(int j=0;j<17;j++)
                    {
                        if(needornot[j])
                        {
                            IDCard[j]=cnmi[place];
                            place+=1;
                        }
                        else;
                    }
                    if(modeone(IDCard))
                    {
                        printf("%s\n", IDCard);
                        hm++;
                    }
                    else;
                }
            }
        }
        else
        {
            for(int k=0;k<=10;k++)
            {
                IDCard[17]=cnmstr(k);
                if(modeone(IDCard))
                {
                    printf("%s\n", IDCard);
                    hm++;
                }
                else;
            }
        }
        
    }
    else
    {
        for(int i=0;i<cnmpow(10,times);i++)
        {   
            char cnmi[times];
            itoa(i,cnmi,10);
            char tem[times];
            int teme=0;
            for(int o=times-1;o>-1;o--)
            {
                if(cnmi[o]==0)
                {
                    tem[times-1-o]='0';
                    teme++;
                }
                else
                    tem[times-1-o]=cnmi[times-1-o-teme];
            }
            for(int o=0;o<times;o++)
            {
                cnmi[o]=tem[o];
            }
            int place=0;
            for(int j=0;j<18;j++)
            {
                if(needornot[j])
                {
                    IDCard[j]=cnmi[place];
                    place+=1;
                }
                else;
            }
            if(modeone(IDCard))
            {
                printf("%s\n", IDCard);
                hm++;
            }
            else;
        }
    }
    return hm;
}

int main(){
    char a;
    do{
        char IDCard[18];
        printf("If you want to validate your ID Card number, just enter it;\n");
        printf("If you complete your fragmentary ID Card number, replace the blank with \"a\".\n");
        printf("Now, please tell me your ID Card number(full or fragmentary):");
        scanf("%s",&IDCard);
        getchar();
        if(mode(IDCard)==0)
        {
            if(modeone(IDCard))
                printf("It\'s right.\n");
            else
                printf("It\'s wrong.\n");
        }
        else
        {
            printf("There are(is) several situation(s):\n");
            printf("%d in total.",modetwo(IDCard));
        }
        printf("If you want to continue, input \"Y\"; press Enter twice otherwise:");
        scanf("%c%*c",&a);
    }while(a=='Y');
    printf("Glad to help you. See you next time.\n");
    system("pause");
    return 0;
}