# Datalab-69

## absVal*

- 获取x的绝对值

- 示例: absVal(-1) = 1

- 说明：-TMax <= x <= TMAX
- 限制操作: ! ~ & ^ | + << >>
- 操作数量: 10
- 难度: 4

$$
x=\begin{cases}
  \ \ \thicksim x+1,&  if\ x<0\\
  \ \ x,&if\ x>0
\end{cases}
$$

可知
$$
X_n>>(n-1)=\begin{cases}
&1111...1111&\text{x<0}\\
&0000...0000&\text{x>0}
\end{cases}
$$

### 解法1

因此可用负数可用移位后的与变正数后的取交。正确可用移位的按位取反再取与。两张取或。

即

~~~c
long absVal(long x){
    return ((x>>63)&(~x+1))((~(x>>63)&x));
}
~~~

### 解法2

对X处理为负数**取反+1**,**正数不变**

一个数取反可以异或1，不变可以异或0。

可用移位后的与原数异或即为对应的反码，在用移位的与1判判定是否需要加1。

~~~c
long absVal(long x){
    return ((x>>63)^x)+((x>>63)&1);
}
~~~

##  addOK

- 判断x+y是否溢出，溢出返回0，反之
- 示例：addOK(0x8000000,0x8000000) = 0
- 限制操作：! ~ & ^ | + << >>
- 操作数量：20
- 难度：3

只有正数相加和负数相加可能溢出。

正数判断符号位是否变为1，负数判断是否变为0。

即判断是否与原来相同。

~~~c
long addOK(long x,long y){
    return (((x^y)>>63)|(~(x^(x+y)>>63)))&1;
}
~~~

## allEvenBits

- 判断一个二进制数偶数位是否全为1
- 示例：allEvenBits(0xFFFFFFFD) = 0
- 限制操作：! ~ & ^ | + << >>
- 操作数量：12
- 难度：2

$$
0x55=01010101\\
0x55<<8=01010101 \ 00000000
$$

通过不断上式就可以得到偶数位全为1的表达式。

此式子与X取与即相当于将奇数位去掉，然后再与上式子取异或观察是否为0.

~~~c
long allEvenBits(long x){
    long t=(0x55<<8)|0x55;
    t=(t<<16)|t;
    t=(t<<32)|t;
    return !((x&t)^t)
}
~~~

## allOddBits

- 判断一个二进制数奇数位是否全为1
- 示例：allOddBits(0xAAAAAAAA) = 1
- 限制操作：! ~ & ^ | + << >>
- 操作数量：12
- 难度：2

其实这道题和上道题几乎差不多。将偶位改为了奇而已。
$$
0xA=10101010\\
0xAA<<8=10101010 \ 00000000
$$
先与MASK取与，再取异或，判断是否为0。

~~~c
int allOddBits(int x) {
  long mask=(0xAA<<8)|0xAA;
    mask=(mask<<16)|mask;
    mask=(mask<<32)|mask;
    return !((x&mask)^mask);
}
~~~

## anyEvenBit

- 判断一个二进制数任意偶数位是否有1
- 示例：anyEvenBit(0xE) = 1
- 限制操作：! ~ & ^ | + << >>
- 操作数量：12
- 难度：2

与上两题有关，即可先找MASK，可以判断是否全为0。

先与MASK取与。即完成了任务。

与的第一重含义是mask，将奇数位全置为0.

第二重含义如果全偶数位为0，即将MASK全置为了0。

因此如果全为0，得到的结果应该是0。

但当有一位为1时，得到的数一定大于1，为了使返回值为1，则两次!!。

~~~c
int anayEvenBits(int x) {
  long mask=(0x55<<8)|0x55;
    mask=(mask<<16)|mask;
    mask=(mask<<32)|mask;
    return !!(x&mask);
}
~~~



## anyOddBit

- 判断一个二进制数任意奇数位是否有1
- 示例：anyOddBit(0x7) = 1
- 限制操作：! ~ & ^ | + << >>
- 操作数量：12
- 难度：2

与上题类似，MASK改变即可。

~~~c
int anayOddBits(int x) {
  long mask=(0xAA<<8)|0xAA;
    mask=(mask<<16)|mask;
    mask=(mask<<32)|mask;
    return !!(x&mask);
}
~~~

## bang

- 不使用`!`计算`!x`
- 示例：bang(3)=0
- 限制操作：~ & ^ | + << >>
- 操作数量：12
- 难度：4

$$
!x=\begin{cases}
1 &x=0\\
0 &x\neq0
\end{cases}
$$

### 解法1

对于一个至少含一个一的数来说，分两种情况：

1. 首位为1
2. 首位为0，但此时至少有一个1，因此与111....111取异或，可知为1的位一定为0且首位一定为1。也因此再加上1，会使第一个为0的位变为1，而不会影响首位的1。

对于0，与111...111取异或后加1首位一定为0。

因此可通过上述三种情况将其右移再与1取与即可。

由于要!x因此可以先取反再与1取与。

~~~c
long bang(long x){
  return ((~(x|(x^(((0x1<<63)>>63)+1))))>>63)&1;
}
~~~

### 解法2

利用正负数的性质

- 对于0来说，正与负高位均为0
- 对于非0数来说，正数与负数最高位分别为0和1（补数最小全为1），因此取或后，为1。

~~~c
long bang(long x){
    return ((~(x|(~x+1))>>63)&1
}
~~~

等等这个方法好像和上面的其实实质一样。但上面的麻烦了一点，没有真正领会。

## bitAnd

- 只使用 `~`和`|`计算x&y
- 示例：bitAnd(6,5)=4
- 限制操作：~ |
- 操作数量：8
- 难度：1

De Morgan's Law

~~~c
long bitAnd (long x,long y){
  return ~(~x|~y);
}
~~~

## bitCount ***

- 计算二进制数中1的个数
- 示例：bitCount(7) = 3
- 限制操作：! ~ & ^ | + << >>
- 操作数量：40
- 难度：4

对于一位数，二进制位个数即当前位的值。

对于二位数，二进制位个数即为两个位的值做加法。
$$
cnt_{l,r}=\begin{cases}
&cnt_{l,x}+cnt_{x,r},& l<r\\
&cnt_l,&l=r
\end{cases}
$$
可根据动态规划思想计算所有。

显然$cnt_i=b_i$

去构造$cnt_{i,i+1}$, 加法可能会进位，因此此时需要两位去保存和。可以将x整体右移移位，全部取MASK后，再计算和。

以此类推。

构造$cnt_{i,i+3}$, 将上述结果右移两位取MASK求和，每四位及对应这四项中的一的个数和。

对于后面的情况就没有可能数量到符号位才能表示个数。

上述过程每一步都要取对应的MASK。

~~~cpp
long bitCount(long x,long y){
  long MASK_1=(0x5555<<16)|(0x5555);
  MASK_1=(MASK_1<<32)|(MASK_1);
  long MASK_2=(0x3333<<16)|(0x3333);
  MASK_2=(MASK_2<<32)|MASK_2;
  long MASK_3=(0x0f0f<<16)|(0x0f0f);
  MASK_3=(MASK_3<<32)|MASK_3;
  long MASK_4=(0x00ff<<16)|(0x00ff);
  MASK_4=(MASK_4<<32)|MASK_4;
  long MASK_5=(0xffff<<32)|(0xffff);
  long MASK_6=(0xffff<<16);


  long cnt_width_2=(x&MASK_1)+((x>>1)&MASK_1);
  long cnt_width_4=(cnt_width_2>>2)&MASK_2+cnt_width_2&MASK_2;
  long cnt_width_8=(cnt_width_4>>4)&MASK_3+cnt_width_4&MASK_3;
  long cnt_width_16=(cnt_width_8>>8)&MASK_4+cnt_width_8&MASK_4;
  long cnt_width_32=(cnt_width_16>>16)&MASK_5+cnt_width_16&MASK_5;
  long cnt_width_64=(cnt_width_32>>32)&MASK_6+cnt_width_32&MASK_6;
  return cnt_width_64;

}
~~~

## bitMask

- 产生一个在`[lowbit,highbit]`区间内全为`1`的数，其余位为`0`
- 示例：bitMask(5,3) = 0x38
- 说明：0 <= lowbig <= 31，0 <= highbit <= 31，若low>high，返回0
- 限制操作：! ~ & ^ | + << >>
- 操作数量：16
- 难度：3

