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
int main(){
    for(long x=0;x!=LONG_MAX;x++)
        if(x!=absVal(x))
            printf("wrong\n");


}

