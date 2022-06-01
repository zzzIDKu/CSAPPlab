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
  400f02:	48 89 e6             	mov    %rsp,%rsi
  400f05:	e8 52 05 00 00       	call   40145c <read_six_numbers>
  400f0a:	83 3c 24 01          	cmpl   $0x1,(%rsp)
  400f0e:	74 20                	je     400f30 <phase_2+0x34>
  400f10:	e8 25 05 00 00       	call   40143a <explode_bomb>
  400f15:	eb 19                	jmp    400f30 <phase_2+0x34>
  400f17:	8b 43 fc             	mov    -0x4(%rbx),%eax
  400f1a:	01 c0                	add    %eax,%eax
  400f1c:	39 03                	cmp    %eax,(%rbx)
  400f1e:	74 05                	je     400f25 <phase_2+0x29>
  400f20:	e8 15 05 00 00       	call   40143a <explode_bomb>
  400f25:	48 83 c3 04          	add    $0x4,%rbx
  400f29:	48 39 eb             	cmp    %rbp,%rbx
  400f2c:	75 e9                	jne    400f17 <phase_2+0x1b>
  400f2e:	eb 0c                	jmp    400f3c <phase_2+0x40>
  400f30:	48 8d 5c 24 04       	lea    0x4(%rsp),%rbx
  400f35:	48 8d 6c 24 18       	lea    0x18(%rsp),%rbp
  400f3a:	eb db                	jmp    400f17 <phase_2+0x1b>
  400f3c:	48 83 c4 28          	add    $0x28,%rsp
  400f40:	5b                   	pop    %rbx
  400f41:	5d                   	pop    %rbp
  400f42:	c3                   	ret    
~~~

