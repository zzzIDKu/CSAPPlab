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
  \ \ \thicksim x+1,& \text{ if  x<0}\\
  \ \ x,&\text{  if x>0}
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

## bitAnd

- 只使用 `~`和`！`计算x&y
- 示例：bitAnd(6,5)=4
- 限制操作：~ |
- 操作数量：8
- 难度：1

## bitCount

- 计算二进制数中1的个数
- 示例：bitCount(7) = 3
- 限制操作：! ~ & ^ | + << >>
- 操作数量：40
- 难度：4

## bitMask

- 产生一个在`[lowbit,highbit]`区间内全为`1`的数，其余位为`0`
- 示例：bitMask(5,3) = 0x38
- 说明：0 <= lowbig <= 31，0 <= highbit <= 31，若low>high，返回0
- 限制操作：! ~ & ^ | + << >>
- 操作数量：16
- 难度：3

