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
  #(%eax)=%rbx-0x4
  400f1a:	01 c0                	add    %eax,%eax
  #(%eax)=2(%eax)
  400f1c:	39 03                	cmp    %eax,(%rbx)
  #比较%rbx指向的值与%eax的值。
  400f1e:	74 05                	je     400f25 <phase_2+0x29>
  #相等跳转到0xfc+0x29=0x25
  400f20:	e8 15 05 00 00       	call   40143a <explode_bomb>
  400f25:	48 83 c3 04          	add    $0x4,%rbx
  400f29:	48 39 eb             	cmp    %rbp,%rbx
  400f2c:	75 e9                	jne    400f17 <phase_2+0x1b>
  400f2e:	eb 0c                	jmp    400f3c <phase_2+0x40>
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
  401460:	48 89 f2             	mov    %rsi,%rdx
  401463:	48 8d 4e 04          	lea    0x4(%rsi),%rcx
  401467:	48 8d 46 14          	lea    0x14(%rsi),%rax
  40146b:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  401470:	48 8d 46 10          	lea    0x10(%rsi),%rax
  401474:	48 89 04 24          	mov    %rax,(%rsp)
  401478:	4c 8d 4e 0c          	lea    0xc(%rsi),%r9
  40147c:	4c 8d 46 08          	lea    0x8(%rsi),%r8
  401480:	be c3 25 40 00       	mov    $0x4025c3,%esi
  #0x4025c3:       "%d %d %d %d %d %d"应该就是读六个数。
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

