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
  long MASK=0x5555<<16+0x5555;
  MASK=MASK<<32+MASK;
  long x_even_bit=x&MASK;
  long x_odd_bit=(x>>1)&MASK;
  long cnt_width_2=x_even_bit+x_odd_bit;
  long cnt_width_4=(cnt_width_2>>2)+(cnt_width_2>>63)&(1<<62)+cnt_width_2;
  long cnt_width_8=(cnt_width_4>>4)+cnt_width_4;
  long cnt_width_16=(cnt_width_8>>8)+cnt_width_8;
  long cnt_width_32=(cnt_width_16>>16)+cnt_width_16;
  long cnt_width_64=(cnt_width_32>>32)+cnt_width_32;
  return cnt_width_64;




}