#include <cstdio>
#include <cstring>
#define N (2000)
#define M (300)
#define MOD (8)#include <cstdio>
#include <cstring>
#define MAXLEN 500//���鳤�����ޣ����Ը���������������
#define BASE_DIGIT 9//����Ľ��ƣ�9������10^9����
#define BASE 1000000000//10^9����
#define PRINTCHAR ("%09d")//ר���������������ַ���
#define IsDigit(c) (('0'<=(c))&&((c)<='9'))//�ж��ַ�c�Ƿ�Ϊ����
using namespace std;
char instr[MAXLEN*BASE_DIGIT+1];
short CMP(const int *a,const int *b){//�Ƚ������������Ҳ���Ǵ������ľ���ֵ
    if(a[0]<b[0])//��λ�ٵ�С
        return -1;
    if(a[0]>b[0])//��λ��Ĵ�
        return 1;
    for(int i=a[0];i>0;i--)
    {
        if(a[i]<b[i])//��λС��С
            return -1;
        if(a[i]>b[i])//��λ�������
            return 1;
    }
    return 0;
}
void ADD(const int *a,const int *b,int *c){//�����ʾ�Ĵ������ӷ�
    memset(c,0,sizeof(int)*MAXLEN);
    int la=a[0],lb=b[0],d=0;
    c[0]=(la>lb?la:lb)+1;
    for(int i=1;i<c[0];i++)
    {
        if(i>la)
            c[i]=b[i]+d;
        else if(i>lb)
            c[i]=a[i]+d;
        else
            c[i]=a[i]+b[i]+d;
        d=0;
        if(c[i]>=BASE)
        {//��Ҫ��λ
            d=1;
            c[i]-=BASE;
        }
    }
    while(c[0]>1&&c[c[0]]==0)//��ȥǰ����
         c[0]--;
}
void SUB(const int *a,const int *b,int *c){//����
    memset(c,0,sizeof(int)*MAXLEN);
    c[0]=a[0];
    int d=0;
    for(int i=1;i<=a[0];i++)
    {
        if(i<=b[0])
            c[i]=a[i]-b[i]-d;
        else c[i]-=d;
        d=0;
        if(c[i]<0)
        {//��Ҫ��λ
            c[i]+=BASE;
            d++;
        }
    }
    while(c[0]>1&&c[c[0]]==0)
        c[0]--;//��ȥǰ����
    return ;
}
void MUL(const int *a,const int *b,int *c){//�˷�
    memset(c,0,sizeof(int)*MAXLEN);
    __int64 t=0;
    int l = a[0]+b[0]+1;
    c[0]=l;
    for(int i=1;i<=a[0];i++)
        for(int j=1;j<=b[0];j++)
        {
            /*�����м����ܿ��ܳ���int32��Χ����ʹ��int64��ת*/
            t=(__int64)c[i+j-1]+(__int64)a[i]*(__int64)b[j];
            c[i+j-1]=t%BASE;
            c[i+j] += t/BASE;//�洢��λ
        }
    while(c[0]>1&&c[c[0]]==0)
        c[0]--;//��ȥǰ����
}
void MUL(const int *a,int b,int *c){//�߾��˵���
    memset(c,0,sizeof(int)*MAXLEN);
    int l = a[0] + 1 ;
    __int64 t=0;
    for(int i=1;i<l;i++)
    {
        t = (__int64)a[i]*b + (__int64)c[i];
        c[i+1] = t/BASE;
        c[i] = (t%BASE);
    }
    while(c[l]==0&&l>1) l--;
    c[0]=l;
}
void DIV(const int *a,const int *b,int *c,int *d){//����
        memset(c,0,sizeof(int)*MAXLEN);memset(d,0,sizeof(int)*MAXLEN);
        int *t1 = new int[MAXLEN],*t2 = new int[MAXLEN];
        int la=a[0],lb=b[0],ld=0,min=0,max=0,mid=0,l = la;
        double tdmin=0,tdmax=0,tbmin=b[lb],tbmax=tbmin+1.0;
        if(lb>1)
        {//ȡ������λ��ֵ����������
            tbmin = tbmin*(double)BASE + (double)b[lb-1];
            tbmax = tbmin+1.0;
        }
        for(int i=l;i>0;i--)
        {
            for(int j=d[0];j>=1;j--)d[j+1]=d[j];d[1]=a[i];
            if(d[d[0]+1]!=0)d[0]++;
            if(CMP(d,b)<0)
                continue;
            ld = d[0];
            tdmin = d[ld];
            int j = 1;
            while(tdmin<tbmin)
            {
                tdmin = tdmin*BASE + d[ld-j];
                j++;
            }
            tdmax = tdmin+1.0;
            max =(int)(tdmax/tbmin)+1;min =(int)(tdmin/tbmax)-1;
            while(true)
            {//��������
                mid = (min+max)/2;
                MUL(b,mid,t1);
                if(CMP(d,t1)<0){max = mid-1;continue;}//����ƫ�ߣ��ı�maxֵ
                SUB(d,t1,t2);

                if(CMP(t2,b)>=0){min = mid+1;continue;}//����ƫ�ͣ��ı�minֵ
                break;//���̳ɹ�����midֵΪ��λ����ֵ
            }
            c[i]=mid;
            memcpy(d,t2,sizeof(int)*MAXLEN);//t2Ϊ��ֵ������d
        }
        delete []t1;delete []t2;
        while(c[l]==0&&l>1) l--;
        c[0]=l;//��ȥǰ����
}
class HarInt{/*�����������֧࣬�������������Ļ�������*/
public:

    int numb[MAXLEN];//�������֣���0λ��ʾ���ֳ��ȣ���һλ���Ժ�ֱ��ʾ���ֵĸ�λ����λ
    bool flag;
    HarInt(){}/*Ĭ�Ϲ��캯��*/
    ~HarInt(){}/*��������*/
    bool Parse(const char *s){/*��һ���ַ���ת��Ϊһ��������*/
        clear();int l=strlen(s),i=0,nl=1;flag = true;//Ĭ��Ϊ�Ǹ���
        if(s[0]=='-'){i++;flag = false;}//Ϊ��������ֵ�ӵ�2λ��ʼ
        for(int j=l-1;j>=i;j-=BASE_DIGIT)
        {//�Ӹ�λ����λһλһλת
            int n=0,ten=1;
            for(int k=0;(k<BASE_DIGIT&&j-k>=i);k++)
            {
                if(!IsDigit(s[j-k])){clear();return false;}//���������ַ�����ֵʧ��
                n+=(s[j-k]-'0')*ten;ten*=10;
            }
            numb[nl++]=n;//�ӵ�һλ��ʼ������numb��ֵ����0λԤ��Ϊ���ֳ�
        }
        nl--;while(numb[nl]==0&&nl>1)nl--;//��ȥǰ����
        numb[0]=nl;return true;//��ֵ�ɹ�
    }
    void clear(){memset(numb,0,sizeof(int)*MAXLEN);}/*��������λ��Ϊ��*/
    void Parse(const HarInt hi){/*ͨ��������֪����ֵ*/
        memcpy(numb,hi.numb,sizeof(int)*MAXLEN);
        flag = hi.flag;
    }
    void value(const int a){/*ͨ��һ����С����������ֵ*/
        int t=a;
        flag=true;if(t<0){flag=false;t*=-1;}
        numb[0]=1;numb[1]=t;
    }
    bool isNegative(){return (!flag&&(numb[0]>1||numb[1]));};
    int operator[](int i){return numb[i];}/*����[]�����ʵ�iλ����*/
    bool Flag(){return flag;}/*��ȡ��ǰ���ķ���*/
    bool isZero(){return (numb[0]==1&&numb[1]==0);}/*�Ƿ�Ϊ0*/
    int Get(){if(scanf("%s",instr)==EOF)return EOF;return Parse(instr);}/*�Զ������뺯��*/
    void print(char s){/*�Զ����������*/
        if(!flag)putchar('-');
        printf("%d",numb[numb[0]]);
        for(int i=numb[0]-1;i>=1;i--)
            printf(PRINTCHAR,numb[i]);
        putchar(s);
    }
    friend short HarIntCmp(HarInt,HarInt);//��Ԫ�ȽϺ���
    friend void DIV(HarInt,HarInt,HarInt&,HarInt&);//��Ԫ��������
    HarInt& operator+=(const HarInt& a){//����+=�������ʵ�ִ�������+=����
        int *n = new int[MAXLEN];
        memcpy(n,numb,sizeof(int)*MAXLEN);
        if(flag==a.flag)//ͬ�ţ�����ֱֵ����ӣ����Ų���
            ADD(n,a.numb,numb);
        else{//��������ֵ��ļ�����ֵС�ģ����������ֵ�����ͬ
            int c = CMP(n,a.numb);//�Ƚ������ľ���ֵ
            if(c==0){numb[0]=1;numb[1]=0;flag=true;}//|a|==|b|&&a*b<0��a-b=0;
            else if(c<0){SUB(a.numb,n,numb);flag=a.flag;}//|a|<|b|
            else    SUB(n,a.numb,numb);
        }
        delete []n;n=NULL;
        return *this;
    }
    HarInt& operator-=(const HarInt& a){//����-=�������ʵ�ִ�������-=����
        int *n = new int[MAXLEN];
        memcpy(n,numb,sizeof(int)*MAXLEN);
        if(flag!=a.flag)//��ţ�����ֱֵ����ӣ����Ų���
            ADD(n,a.numb,numb);
        else{//ͬ�ţ�����ֵ���С�������������Ĵ�Сȷ��
            int c = CMP(n,a.numb);
            if(c==0){numb[0]=1;numb[1]=0;flag=true;}//0
            else if(c<0){SUB(a.numb,n,numb);flag=!flag;}//a<b����ȡ��
            else    SUB(n,a.numb,numb);//a>b���Ų���
        }
        delete []n;n=NULL;
        return *this;
    }
    HarInt& operator*=(const HarInt& a){//����*=�������ʵ�ִ�������*=����
        int *n = new int[MAXLEN];
        memcpy(n,numb,sizeof(int)*MAXLEN);
        MUL(n,a.numb,numb);//����ֵ���
        flag = (flag==a.flag);//ͬ��ȡ�������ȡ��
        delete []n;n=NULL;
        return *this;
    }
    HarInt& operator/=(const HarInt& a){//����/=�������ʵ�ִ�������/=����
        int *n1 = new int[MAXLEN],*n2 = new int[MAXLEN];
        memcpy(n1,numb,sizeof(int)*MAXLEN);
        DIV(n1,a.numb,numb,n2);//����ֵ���
        delete []n1;delete []n2;
        flag = (flag==a.flag);//ͬ��ȡ�������ȡ��
        return *this;
    }
    HarInt& operator%=(const HarInt& a){//����%=�������ʵ�ִ�������%=����
        int *n1 = new int[MAXLEN],*n2 = new int[MAXLEN];
        memcpy(n1,numb,sizeof(int)*MAXLEN);
        DIV(n1,a.numb,n2,numb);
        delete []n1;delete []n2;
        flag = (flag==a.flag);
        return *this;
    }
    HarInt& operator=(const int &a)
    {
        if(a>=0)
        {
            numb[1]=a;
            flag=1;
        }
        else
        {
            numb[1]=-a;
            flag=0;
        }
        numb[0]=1;
    }
    void half();
    void dv( HarInt & v,int *r);
};
void HarInt::dv( HarInt & v,int *r)
{
    int *n1 = new int[MAXLEN+1];
    memcpy(n1,numb,sizeof(int)*MAXLEN);
    DIV(n1,v.numb,numb,r);//����ֵ���
    delete []n1;
    flag = (flag==v.flag);//ͬ��ȡ�������ȡ��
}
void HarInt::half()
{
    for(int i=numb[0];i>=1;--i)
    {
        if(i>1 && (numb[i]&1))
            numb[i-1]+=BASE/2;
        numb[i]>>=1;
    }
    if(numb[0]>1 && !numb[numb[0]])
        --numb[0];
}
void DIV(HarInt a,HarInt b,HarInt& c,HarInt& d){//������һ������ͬʱȡ����������
    c.flag= (a.flag==b.flag);d.flag=c.flag;
    DIV(a.numb,b.numb,c.numb,d.numb);
    return ;
}
short HarIntCmp(HarInt a,HarInt b){
    if(a.Flag()>b.Flag())//��������ڸ���
        return 1;
    if(a.Flag()<b.Flag())//������С������
        return -1;
    if(a[0]<b[0])//��λ�ٵ���ֵС�����ݷ����жϴ�С
        return ((!a.Flag())?1:-1);
    if(a[0]>b[0])
        return (a.Flag()?1:-1);
    for(int i=a[0];i>=1;i--)
    {
        if(a[i]<b[i])
            return ((!a.Flag())?1:-1);
        if(a[i]>b[i])
            return (a.Flag()?1:-1);
    }
    return 0;
}
/*�Ƚ������������*/
bool operator<(HarInt a,HarInt b){return (HarIntCmp(a,b)<0);}
bool operator>(HarInt a,HarInt b){return (HarIntCmp(a,b)>0);}
bool operator==(HarInt a,HarInt b){return (HarIntCmp(a,b)==0);}
bool operator==(HarInt a,int b){return a.isZero();}
bool operator!=(HarInt a,HarInt b){return (HarIntCmp(a,b)!=0);}
bool operator<=(HarInt a,HarInt b){return (HarIntCmp(a,b)<=0);}
bool operator>=(HarInt a,HarInt b){return (HarIntCmp(a,b)>=0);}
/*���������������*/
HarInt operator+(const HarInt& a,const HarInt& b){HarInt c=a;c+=b;return c;}
HarInt operator+(const HarInt& a,const int b){HarInt c;c.value(b);c+=a;return c;}
HarInt operator-(const HarInt& a,const HarInt& b){HarInt c=a;c-=b;return c;}
HarInt operator-(const HarInt& a,const int b){HarInt c;c.value(b);return (a-c);}
HarInt operator*(const HarInt& a,const HarInt& b){HarInt c=a;c*=b;return c;}
HarInt operator*(const HarInt& a,const int b){HarInt c;c.value(b);c*=a;return c;}
HarInt operator/(const HarInt& a,const HarInt& b){HarInt c=a;c/=b;return c;}
HarInt operator/(const HarInt& a,const int b){HarInt c;c.value(b);return (a/c);}
HarInt operator%(const HarInt& a,const HarInt& b){HarInt c=a;c%=b;return c;}
HarInt operator%(const HarInt& a,const int b){HarInt c;c.value(b);return (a%c);}

void gcd(HarInt a,HarInt b,HarInt &x)
{
    HarInt y,tmp;
    y=0;
    x=1;
    for(;;)
    {
        tmp=a/b;
        y=y-tmp*x;
        a=a-tmp*b;
        if(a.isZero())
            break;
        tmp=a,a=b,b=tmp;
        tmp=x,x=y,y=tmp;
    }
}
HarInt na,nb;
int b,n;
HarInt an[6];
int ans=0;
void solv(int p1,int p2)
{
    if(p1==0)
        return;
    HarInt nc;
    nc=1;
    na=1;
    nb=1;
    HarInt c,d,e;
    c=p1;
    d=p2;
    e=b;
    for(int i=1;i<=n;i<<=1)
    {
        if(i&n)
            na*=c,nb*=d,nc*=e;
        c=c*c;
        d=d*d;
        e=e*e;
    }
    gcd(na,nb,d);
    d=d%na;
    if(d.isNegative())
    {
        d.flag=0;
        d*=(na-1);
        d%=na;
    }
    c=d;
    e=nc/b;
    an[ans]=d*nb;
    if(an[ans]>=e)
        ++ans;
    c=na-c;
    an[ans]=c*nb+1;
    if(an[ans]>=e)
        ++ans;
}
void ptr(int i)
{
    if(an[i].isZero())
        printf("0");
    else
    {
        static char str[2007];
        int poi=0;
        int *a=an[i].numb;
        int l=a[0];
        for(;l>0;)
        {
            long long r=0;
            for(int i=l;i>0;--i)
            {
                long long tmp=a[i];
                tmp+=r*BASE;
                r=tmp%b;
                tmp/=b;
                a[i]=tmp;
            }
            r%=(long long)b;
            str[poi++]=(char)(r<10?r+'0':r-10+'A');
            for(;l>0 && !a[l];--l)
                ;
        }
        for(;poi>1 && str[poi-1]=='0';--poi)
            ;
        for(int i=poi-1;i>=0;--i)
            printf("%c",str[i]);
    }
    printf("\n");
}
int main()
{
    freopen("in.txt","r",stdin);
    scanf("%d %d",&b,&n);
static const int ii[][2]={
    //0     1     2     3     4     5     6     7     8     9
    {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{2,3},{0,0},{0,0},{0,0},
    //10    11    12    13    14    15    16    17    18    19
    {2,5},{0,0},{3,4},{0,0},{2,7},{3,5},{0,0},{0,0},{2,9},{0,0},
    //20    21    22    23    24    25    26    27     28     29    30
    {4,5},{3,7},{2,11},{0,0},{3,8},{0,0},{2,13},{0,0},{4,7},{0,0},{0,0},
    //31    32     33    34    35     36
    {0,0},{0,0},{3,11},{2,17},{5,7},{4,9}
};
    if(b!=30)
    {
        if(ii[b][0])
            solv(ii[b][0],ii[b][1]);
    }
    else
    {
        solv(2,15);
        solv(6,5);
        solv(10,3);
    }
    printf("%d\n",ans+(n==1?2:0));
    if(n==1)
        printf("0\n1\n");
    for(int i=0;i<ans;++i)
        ptr(i);
    return 0;
}
