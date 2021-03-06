#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

/*
获取x的绝对值
示例: absVal(-1) = 1
说明：-TMax <= x <= TMAX
限制操作: ! ~ & ^ | + << >>
操作数量: 10
难度: 4
*/
long absVal(long x){
    return ((x>>63)&(~x+1))|(((~(x>>63))& (x)));
}
/*

- 判断x+y是否溢出，溢出返回0，反之
- 示例：addOK(0x8000000,0x8000000) = 0
- 限制操作：! ~ & ^ | + << >>
- 操作数量：20
- 难度：3
*/
long addOK(long x,long y){
    return (((x^y)>>63)|(~(x^(x+y)>>63)))&1;
}
/*
- 判断一个二进制数偶数位是否全为1
- 示例：allEvenBits(0xFFFFFFFD) = 0
- 限制操作：! ~ & ^ | + << >>
- 操作数量：12
- 难度：2
*/

long allEvenBits(long x){
    long mask=(0x55<<8)|0x55;
    mask=(mask<<16)|mask;
    mask=(mask<<32)|mask;
    return !((x&mask)^mask);
}
/*
- 判断一个二进制数奇数位是否全为1
- 示例：allOddBits(0xAAAAAAAA) = 1
- 限制操作：! ~ & ^ | + << >>
- 操作数量：12
- 难度：2
*/
long allOddBits(long x) {
  long mask=(0xAA<<8)|0xAA;
    mask=(mask<<16)|mask;
    mask=(mask<<32)|mask;
    return !((x&mask)^mask);

}
/*
- 判断一个二进制数任意偶数位是否有1
- 示例：anyEvenBit(0xE) = 1
- 限制操作：! ~ & ^ | + << >>
- 操作数量：12
- 难度：2
*/
long anayEvenBits(long x) {
  long mask=(0xAA<<8)|0xAA;
    mask=(mask<<16)|mask;
    mask=(mask<<32)|mask;
    return !!(x&mask);
}
/*
- 判断一个二进制数任意奇数位是否有1
- 示例：anyOddBit(0x7) = 1
- 限制操作：! ~ & ^ | + << >>
- 操作数量：12
- 难度：2

*/
long anayOddBits(long x) {
  long mask=(0xAA<<8)|0xAA;
    mask=(mask<<16)|mask;
    mask=(mask<<32)|mask;
    return !!(x&mask);
}
/*
- 不使用`!`计算`!x`
- 示例：bang(3)=0
- 限制操作：~ & ^ | + << >>
- 操作数量：12
- 难度：4
*/
long bang(long x){
  return ((~(x|(x^(((0x1<<63)>>63)+1))))>>63)&1;
}
/*
- 只使用 `~`和`|`计算x&y
- 示例：bitAnd(6,5)=4
- 限制操作：~ |
- 操作数量：8
- 难度：1
*/
long bitAnd (long x,long y){
  return ~(~x|~y);
}
/*- 计算二进制数中1的个数
- 示例：bitCount(7) = 3
- 限制操作：! ~ & ^ | + << >>
- 操作数量：40
- 难度：4
*/
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

/*- 产生一个在`[lowbit,highbit]`区间内全为`1`的数，其余位为`0`
- 示例：bitMask(5,3) = 0x38
- 说明：0 <= lowbig <= 31，0 <= highbit <= 31，若low>high，返回0
- 限制操作：! ~ & ^ | + << >>
- 操作数量：16
- 难度：3*/
long bitMask(long x,long y){
  return (((~0)<<x)&((~0)+1<<y<<1));
}
/* - 产生一个掩码，表示x和y中哪些位相等。只使用`~`和`&`
- 示例：bitMatch(0x7,0xE) = 0x6
- 限制操作：~ &
- 操作数量：14
- 难度：1 */
long bitMatch(long x,long y){
  return (~(x&(~y))&~(~x&y));
}
/* - 使用`~`和`&`实现`~(x|y)`
- 示例：bitNor(0x6,0x5) = 0xFFFFFFF8
- 限制操作：~ &
- 操作数量：8
- 难度：1 */
long bitNor(long x,long y){
  return (~x)&(~y);
}
/* - 使用`~`和`&`实现`x|y`
- 示例：bitNor(0x6,0x5) = 0x7
- 限制操作：~ &
- 操作数量：8
- 难度：1 */
long bitOr(long x,long y){
  return ~((~x)&(~y));
}
/* - 若x中含有奇数个0返回1，反之返回0.
- 示例：bitParity(5) = 0
- 限制操作：! ~ & ^ | + << >>
- 操作数量：20
- 难度：4 */
long bitParity(long x){

  x=(x>>32)^x;
  x=(x>>16)^x;
  x=(x>>8)^x;
  x=(x>>4)^x;
  x=(x>>2)^x;
  return ((x>>1)^x)&1;
}

/* - 逆序32位比特数
- 示例：bitReverse(0x80000002) = 0x40000001
- 限制操作：! ~ & ^ | + << >>
- 操作数量：45
- 难度：４ */
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
/* - 使用`~`和`&`实现`x^y`
- 示例：bitNor(0x4,0x5) = 0x1
- 限制操作：~ &
- 操作数量：14
- 难度：1 */
long bitXor(long x,long y){
  return ~((~(~ x&y))&(~(x&~ y)));
}

/* 交换第n，m字节
示例：byteSwap(0x12345678,1,3) = 0x56341278
说明：0 <= n <= 3, 0 <= m <= 3
限制操作：! ~ & ^ | + << >>
操作数量：25
难度：2 */
long byteswap(long x,long n,long m){
  long MASK_n=0xff<<(n<<8);
  long MASK_m=0xff<<(m<<8);
  return ((((x&MASK_m)>>(m<<8))<<(n<<8))|(((x&MASK_n)>>(n<<8))<<(m<<8))|(x&~(MASK_m|MASK_n)));
}
/* - 实现`x?y:z`
- 示例：conditional(2,4,5) = 4
- 限制操作：! ~ & ^ | + << >>
- 操作数量：16
- 难度：3 */
long conditional(long x, long y,long z){
  long temp=((!!x)<<63)>>63;
  return (temp&y)|((~temp)z);
}
/* 将二进制数所有位的数置为最低位数
示例：copyLSB(6) = 0x00000000
限制操作：! ~ & ^ | + << >>
操作数量：5
难度：2 */
long copyLSB(long x){
  return (x<<63)>>63;
}
/* 判断 x != -x ，满足返回1，反之。
限制操作：! ~ & ^ | +
操作数量：5
难度：2 */
long distinctNegation(long x){
  return x^(~x+1);
}
/* 计算x/(2^n)，divpwr2
说明：0 <= n <= 30
示例：dividePower2(-33,4) = -2
限制操作：! ~ & ^ | + << >>
操作数量：15
难度：2 */
long divpwr2(long x,long n){
  return (x+(x>>63)&(1<<n+~1))>>n;
}