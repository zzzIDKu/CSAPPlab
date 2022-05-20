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

“高的填0，低的填0”

`highbit`

对于产生$[0,...,1_k,1_{k-1},..,1_0]$，可以将1左移k+1位然后减1就能得到。

由于左移k+1，可能出现左移64位未定义，因此先移k位，再移1位。
$$
-1= \backsim1+1=1....1=\backsim0
$$
`lowbit`

对于产生$[1,...,1_k,0_{k-1},..,0_0]$，可以将`1...1`左移k位然后就能得到。

两个取与即可。

~~~c
long bitMask(long x,long y){
  return (((~0)<<x)&((~0)+1<<y<<1));
}
~~~

## BitMatch

- 产生一个掩码，表示x和y中哪些位相等。只使用`~`和`&`
- 示例：bitMatch(0x7,0xE) = 0x6
- 限制操作：~ &
- 操作数量：14
- 难度：1

同或运算。$\sim(x\oplus y)=\sim((A\&\sim B)| (B\&\sim A))=((\sim(A\&\sim B))\&(\sim(B\&\sim A)))$

 ~~~c
 long bitMatch(long x,long y){
   return (~(x&(~y))&~(~x&y));
 }
 ~~~

## bitNor

- 使用`~`和`&`实现`~(x|y)`
- 示例：bitNor(0x6,0x5) = 0xFFFFFFF8
- 限制操作：~ &
- 操作数量：8
- 难度：1

$$
\sim(x|y)=\sim x\&\sim y
$$

~~~c
long bitNor(long x,long y){
  return (~x)&(~y);
}
~~~

## bitOr

- 使用`~`和`&`实现`x|y`
- 示例：bitNor(0x6,0x5) = 0x7
- 限制操作：~ &
- 操作数量：8
- 难度：1

$$
(x|y)=\sim(\sim x\&\sim y)
$$

~~~c
long bitOr(long x,long y){
  return ~((~x)&(~y));
}
~~~

## bitParity

- 若x中含有奇数个0返回1，反之返回0.
- 示例：bitParity(5) = 0
- 限制操作：! ~ & ^ | + << >>
- 操作数量：20
- 难度：4

奇数个0等价于奇数个1.

这道题的思路完全可以按照bitCount的思路，将所有的1当做常数1加起来，然后看最后最低位是否为1。但是由于操作数量的限制要思考一下是否存在更优的方法。

对于一个64位的数，让其高32位和低32位按位异或，如果对应为均为1，则相当于消去两个1不改变是奇数还是偶数。然后让着32位的高16位和低16位进行操作直到最后剩一位。若这一位为1，则奇数个，为0，则偶数个。

可以用归纳推理证明上述正确：

1. 对于$n=2$, 显然，可以根据最后一位的结果来判断是否含有奇数个1。
2. 不放假设对于$n=2(k-1)$时，有经过上述算法可以若最后一位为1，则奇数个，最后一位为0，则偶数个。
   - 对于$n=2k$,不妨将其拆成2位和$2(k-1)$位
   - 对于2位可以根据上述算法，得到最后一位，可以判断2位中奇数个还是偶数个。
   - 对于$2(k-1)$位，根据假设可以得到最后一位决定这$2(k-1)$位奇数个还是偶数个。
   - 将上述分别得到的最后两位取异或，即可判断$2k$位的奇数个还是偶数个。

~~~c
long bitParity(long x){
  x=(x>>32)^x;
  x=(x>>16)^x;
  x=(x>>8)^x;
  x=(x>>4)^x;
  x=(x>>2)^x;
  return ((x>>1)^x)&1;
}
~~~

## bitReverse

- 逆序32位比特数
- 示例：bitReverse(0x80000002) = 0x40000001
- 限制操作：! ~ & ^ | + << >>
- 操作数量：45
- 难度：４

也才用分治的做法，先交换$b_0,b_1$,$b_2,b_3$,...然后交换新的$b_0b1,b_2b_3$,...直到最后。

证明：

1. 对于$2^1$,有$b_0,b_1$显然成立得到$b_0,b_1$。
2. 不妨假设对于$2^{k-1}$,得到的结果正确,序列为$b_0,..,b_{2^{n-1}-1}$。对于$2^n$,将其两部分分别进行对应算法可以得到以下两个序列$b_{2^{n-1}},..,b_{2^{n}-1},b_0,..,b_{2^{n-1}-1}$,再将上述两个序列逆转就有$b_0,..,b_{2^{n-1}-1},b_{2^{n-1}},..,b_{2^{n}-1}$.

对于第一步将所有挨着的两位换位，偶数位先取MASK再左移，奇数位先右移再取MASK，最后取或就可以得到。其他的类似。

~~~c
long bitReverse(long x){
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
  
  long Reverse_2b=((x&MASK_1)<<1)|((x>>1)&MASK_1);
  long Reverse_4b=((Reverse_2b&MASK_2)<<2)|((Reverse_2b>>2)&MASK_2);
  long Reverse_8b=((Reverse_4b&MASK_3)<<4)|((Reverse_2b>>4)&MASK_3);
  long Reverse_16b=((Reverse_8b&MASK_4)<<8)|((Reverse_8b>>8)&MASK_4);
  long Reverse_32b=((Reverse_16b&MASK_5)<<16)|((Reverse_16b>>16)&MASK_5);
  long Reverse_64b=((Reverse_32b&MASK_6)<<32)|((Reverse_32b>>32)&MASK_6);
  return Reverse_64b;
}
~~~

