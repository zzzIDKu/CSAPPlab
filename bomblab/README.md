# Bomb Lab

- gdb

- `objdump -t ` 

  This will print out the bomb’s symbol table. The symbol table includes the names of all functions and global variables in the bomb, the names of all the functions the bomb calls, and their addresses. You may learn something by looking at the function names!

- `objdump -d`

  Use this to disassemble all of the code in the bomb. You can also just look at individual functions. Reading the assembler code can tell you how the bomb works.

在反汇编文件中找到main，可以看到调用`phase_1`

![image-20220601224926129](https://cdn.jsdelivr.net/gh/zzzIDKu/image/image-20220601224926129.png)

## phase_1

![image-20220601225108275](https://cdn.jsdelivr.net/gh/zzzIDKu/image/image-20220601225108275.png)

在第348行有`mov`，其中移动的`$0x402400`移到`%esi`，然后调用了一个函数，

其中可以看到`%esi` 已经存了值，一般用于第二个参数，也应该有第一个参数，应该在`rdi`中，应该也是`phase_1`传进来的参数。

下一行`test` 使用的寄存器`%eax` 是Return value。应该是上个调用函数返回的值，上个调用的函数名为`string_not_equal` 从字面上理解应该是字符串不相等。

传入的第二个参数理解成地址，就查看那个内存位置的值，应该就是对应的答案。
![image-20220601230733950](https://cdn.jsdelivr.net/gh/zzzIDKu/image/image-20220601230733950.png)

## phase_2

~~~assembly
0000000000400efc <phase_2>:
  400efc:	55                   	push   %rbp
  400efd:	53                   	push   %rbx
  400efe:	48 83 ec 28          	sub    $0x28,%rsp
  #前两分别将寄存器rbp,rbx的值压入栈中
  #第三行将栈顶值减了0x28即5个8，共四十个字节。
  400f02:	48 89 e6             	mov    %rsp,%rsi
  #将栈顶指针移到了%rsi,调用函数时的第二个参数。
  400f05:	e8 52 05 00 00       	call   40145c <read_six_numbers>
  #调用了read_six_numbers的函数，且上一步传入了栈顶指针的值，应该是用来存放着这六个数。汇编代码在下一代码块。
  400f0a:	83 3c 24 01          	cmpl   $0x1,(%rsp)
  400f0e:	74 20                	je     400f30 <phase_2+0x34>
  #此时让0x1与栈顶的值比较
  #如果相等跳转到0xfc+0x34=0x30
  400f10:	e8 25 05 00 00       	call   40143a <explode_bomb>
  400f15:	eb 19                	jmp    400f30 <phase_2+0x34>
  400f17:	8b 43 fc             	mov    -0x4(%rbx),%eax
  #可以看出想当与每次将前一个数乘2然后比较是否与现在的相等。
  #(%eax)=%rbx-0x4
  400f1a:	01 c0                	add    %eax,%eax
  #(%eax)=2(%eax)
  400f1c:	39 03                	cmp    %eax,(%rbx)
  #比较%rbx指向的值与%eax的值。
  400f1e:	74 05                	je     400f25 <phase_2+0x29>
  #相等跳转到0xfc+0x29=0x25
  400f20:	e8 15 05 00 00       	call   40143a <explode_bomb>
  400f25:	48 83 c3 04          	add    $0x4,%rbx
  #(%rbx)=(%rbx)+0x4，相当于向上挪了四个字节。
  400f29:	48 39 eb             	cmp    %rbp,%rbx
  #(%rbp)=0x18(%rsp)，这一步相当于判断是否比较完了六个数。
  400f2c:	75 e9                	jne    400f17 <phase_2+0x1b>
  #没有的话就继续到位置0x17比较下一个。
  400f2e:	eb 0c                	jmp    400f3c <phase_2+0x40>
  #比较完了就退出，可以看到相当于
  400f30:	48 8d 5c 24 04       	lea    0x4(%rsp),%rbx
  400f35:	48 8d 6c 24 18       	lea    0x18(%rsp),%rbp
  #在此将栈顶加4,和栈顶加0x18的值放入到rbx和rbp中。
  400f3a:	eb db                	jmp    400f17 <phase_2+0x1b>
  #跳转到0xfc+0x1b=0x17
  400f3c:	48 83 c4 28          	add    $0x28,%rsp
  400f40:	5b                   	pop    %rbx
  400f41:	5d                   	pop    %rbp
  400f42:	c3                   	ret    
~~~

~~~assembly
000000000040145c <read_six_numbers>:
  40145c:	48 83 ec 18          	sub    $0x18,%rsp
  #栈顶减了0x18
  401460:	48 89 f2             	mov    %rsi,%rdx
  #传入的%rsi是栈顶的指针。
  # %rdx= (%rsi) 3rd argument 1
  401463:	48 8d 4e 04          	lea    0x4(%rsi),%rcx
  # %rcx=0x4(%rsi) 4th argument 2
  401467:	48 8d 46 14          	lea    0x14(%rsi),%rax
  40146b:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  # (0x8(%rsp))=0x14(%rsi) 6
  401470:	48 8d 46 10          	lea    0x10(%rsi),%rax
  401474:	48 89 04 24          	mov    %rax,(%rsp)
  # (%rsp)=0x10(%rsi) 5
  401478:	4c 8d 4e 0c          	lea    0xc(%rsi),%r9
  # %r9=0xc(%rsi) 6th argument 4
  40147c:	4c 8d 46 08          	lea    0x8(%rsi),%r8
  # %r8=0x8(%rsi) 5th argument 3
  401480:	be c3 25 40 00       	mov    $0x4025c3,%esi
  #0x4025c3:       "%d %d %d %d %d %d"应该就是读六个数。%esi 2nd argument
  401485:	b8 00 00 00 00       	mov    $0x0,%eax
  40148a:	e8 61 f7 ff ff       	call   400bf0 <__isoc99_sscanf@plt>
  40148f:	83 f8 05             	cmp    $0x5,%eax
  #%eax是返回值，与5比较，大于5就不出发炸弹
  #上述调用sscanf函数，返回的值是成功转化的数字个数。
  401492:	7f 05                	jg     401499 <read_six_numbers+0x3d>
  401494:	e8 a1 ff ff ff       	call   40143a <explode_bomb>
  401499:	48 83 c4 18          	add    $0x18,%rsp
  40149d:	c3                   	ret    
~~~

上述内容有对照关系。

可知传入的数据为1，2，4，8，16，32.

## phase_3

~~~assembly
  400f43:	48 83 ec 18          	sub    $0x18,%rsp
  400f47:	48 8d 4c 24 0c       	lea    0xc(%rsp),%rcx
  400f4c:	48 8d 54 24 08       	lea    0x8(%rsp),%rdx
  400f51:	be cf 25 40 00       	mov    $0x4025cf,%esi
  400f56:	b8 00 00 00 00       	mov    $0x0,%eax
  400f5b:	e8 90 fc ff ff       	call   400bf0 <__isoc99_sscanf@plt>
  400f60:	83 f8 01             	cmp    $0x1,%eax
~~~

`  400f51:	be cf 25 40 00       	mov    $0x4025cf,%esi`

在这里将`0x4025cf`放到了`%esi`,而其内容是 `0x4025cf:  "%d %d"`.

之后调用了函数`sscanf`参数分别是`%rdi,%rsi,%rdx,%rcx`

内容分别为`input的一行，"%d %d",0xc(%rsp),0x8(%rsp)`.

~~~assembly
  400f60:	83 f8 01             	cmp    $0x1,%eax
  400f63:	7f 05                	jg     400f6a <phase_3+0x27>
  400f65:	e8 d0 04 00 00       	call   40143a <explode_bomb>
  400f6a:	83 7c 24 08 07       	cmpl   $0x7,0x8(%rsp)
  400f6f:	77 3c                	ja     400fad <phase_3+0x6a>
  #400fad:	e8 88 04 00 00       	call   40143a <explode_bomb>
  400f71:	8b 44 24 08          	mov    0x8(%rsp),%eax
  400f75:	ff 24 c5 70 24 40 00 	jmp    *0x402470(,%rax,8)
  400f7c:	b8 cf 00 00 00       	mov    $0xcf,%eax
  400f81:	eb 3b                	jmp    400fbe <phase_3+0x7b>
~~~

之后比较返回值是否大于1，小于等于1就调用`explode_bomb`,反之跳转到`400f6a `.

在`4006fa`比较了`$0x7,0x8(%rsp)`, 大于7跳转到`400fad`，爆炸。反之将`0x8(%rsp)`放入`%eax`。跳转到`*0x402470(,%rax,8)`即`(8*[%rax]+0x402470)`

~~~assembly
  400f7c:	b8 cf 00 00 00       	mov    $0xcf,%eax
  400f81:	eb 3b                	jmp    400fbe <phase_3+0x7b>
  400f83:	b8 c3 02 00 00       	mov    $0x2c3,%eax
  400f88:	eb 34                	jmp    400fbe <phase_3+0x7b>
  400f8a:	b8 00 01 00 00       	mov    $0x100,%eax
  400f8f:	eb 2d                	jmp    400fbe <phase_3+0x7b>
  400f91:	b8 85 01 00 00       	mov    $0x185,%eax
  400f96:	eb 26                	jmp    400fbe <phase_3+0x7b>
  400f98:	b8 ce 00 00 00       	mov    $0xce,%eax
  400f9d:	eb 1f                	jmp    400fbe <phase_3+0x7b>
  400f9f:	b8 aa 02 00 00       	mov    $0x2aa,%eax
  400fa4:	eb 18                	jmp    400fbe <phase_3+0x7b>
  400fa6:	b8 47 01 00 00       	mov    $0x147,%eax
  400fab:	eb 11                	jmp    400fbe <phase_3+0x7b>
  400fad:	e8 88 04 00 00       	call   40143a <explode_bomb>
  400fb2:	b8 00 00 00 00       	mov    $0x0,%eax
  400fb7:	eb 05                	jmp    400fbe <phase_3+0x7b>
  400fb9:	b8 37 01 00 00       	mov    $0x137,%eax
  400fbe:	3b 44 24 0c          	cmp    0xc(%rsp),%eax
  400fc2:	74 05                	je     400fc9 <phase_3+0x86>
  400fc4:	e8 71 04 00 00       	call   40143a <explode_bomb>
  400fc9:	48 83 c4 18          	add    $0x18,%rsp
  400fcd:	c3                   	ret
~~~

可以看到在

`0x402470:       U"\x400f7c“  跳到f7c，将$0xcf放到%eax,又跳到了fbe
0x402478:       U"\x400fb9“  跳到fb9 将0x137放到%eax,接下来该运行fbe
0x402480:       U"\x400f83“   跳到f83 将$0x2c3放到%eax,又跳到了fbe
0x402488:       U"\x400f8a"
0x402490:       U"\x400f91"
0x402498:       U"\x400f98"
0x4024a0:       U"\x400f9f"
0x4024a8:       U"\x400fa6"  跳到 `   .

因此能跳转的位置无非就上面八个。在上面的汇编代码中有跳转的所有地方。可以看到所有都是将一个数字放入到`%eax`然后运行`400fbe`。比较`0xc(%rsp)`与`%eax`是否相等。相等就可以跳到`400fc9`然后正常结束。

因此这个bomb有八个对应的答案。

`0 207`,`1 311`,`2 707`,`3 256`.剩下的就不一一展示。

 



