#include "note.h"


//========================第一章.快速上手========================
//program 1.1
#if 1
int main()
{
    int n_columns;            //所要处理的标号个数
    int columns[MAX_COLS];    //标号
    char input[MAX_INPUT];    //输入行
    char output[MAX_INPUT];   //输出行

    //读取标号
    n_columns = read_column_numbers(columns, MAX_INPUT);  //数组参数是以引用进行传递的

    //读取、处理和打印输入行
    while (gets(input) != NULL)
    {
        printf("Original input: %s\n", input);
        rearrange(output, input, n_columns, columns);
        printf("Rearranged line: %s\n", output);
    }

    return EXIT_SUCCESS;
}


//读取标号
int read_column_numbers(int columns[], int max)
{
    int num = 0;
    int ch;  //这里用整型，因为返回的有可能是EOF，EOF是整型，所以接受的ch必须足以容纳EOF

    //取标号
    while (num < max && scanf("%d", &columns[num]) == 1 && columns[num] >= 0) // NOLINT(cert-err34-c)
    {
        num += 1;
    }

    //确认读到了偶数个
    if (num % 2 != 0)
    {
        puts("不是成对出现");
        exit(EXIT_FAILURE);
    }

    //丢掉改行剩余部分，使下次读取不会读到上次剩下的
    while ((ch = getchar()) != EOF && ch != '\n') ;

    return num;
}


void rearrange(char *output, char const *input, int n_columns, int const columns[])
{
    int col;
    int output_col;
    unsigned long len;

    len = strlen(input);
    output_col = 0;

    //处理每对标号
    for (col = 0; col < n_columns; col += 2)
    {
        int nchars = columns[col + 1] - columns[col] + 1;

        //判断是否该结束
        if (columns[col] >= len || output_col == MAX_INPUT - 1) break;
        //如果输出行数据不够，只复制可以容纳的数据
        if (output_col + nchars > MAX_INPUT - 1) nchars = MAX_INPUT - 1 - output_col;

        //复制开始
        strncpy(output + output_col, input + columns[col], nchars);
        output_col += nchars;
    }

    //以NUL字符结尾
    output[output_col] = '\0';
}
# endif //1.1


//========================第二章.基本概念========================
/* 1.环境
 * 1.1 环境：翻译环境、执行环境
 * 1.2 翻译：源代码.c-（预处理器+解析（编译））->目标代码.obj+函数库中被用到函数-（链接器）->可执行程序.exe
 * 1.3 执行：载入内存->调用main函数->运行时堆栈存储局部变量和返回地址、静态内存存储一直保留->程序结束
 * 2.词法规则
 * 2.1 程序 = 声明 + 函数
 * 2.2 \ 转义字符
 * 2.3 大小写区分、不能以数字开头命名
 * */


//========================第三章.数据========================
/* 变量的三个属性：作用域、链接属性、存储属性
 * 1.基本数据类型
 * 1.1 4种基本数据类型：整型、浮点型、指针、聚合类型（数组、结构、等）
 * 1.2 整型    ：字符、短整型、整型、长整型。都有signed和unsigned
 *            0开头：八进制；0x开头：十六进制
 *            枚举：enum Jar_Type {CUP = 8, PINT =  16};
 * 1.3 浮点类型 ：float、double、long double
 * 1.4 指针    ：指针是C语言为什么如此流行的一个重要原因。
 *            可以把字符串常量赋值给一个“指向字符的指针”
 * 2.基本声明
 * 2.1 声明三个指针： int *b, *c, *d
 * 2.2 指针初始化： char *message = "Hello world";
 *             char *message;
 *             message = "Hello world";
 * 3.typedef
 * 3.1 typedef char *ptr_to_char;
 *   ptr_to_char a;  //a是一个字符指针
 * 4.常量
 * 4.1 int const *pci;  //指向整型常量，可以改地址，不可以改指向的值
 *     int *const pci;  //地址是常量，所指向的整型的值可以改
 * 5.作用域
 * 5.1 四种作用域：文件作用域、函数作用域、代码块作用域、原型作用域
 * 6.链接属性
 * 6.1 external、internal、none
 * 6.2 static int b //全局变量b将为这个源文件所私有，或局部变量b在函数结束时不会被释放，下次此函数启动b沿用上次存下来的值
 *    extern int b  //extern可以置于变量或者函数前，以标示变量或者函数的定义在别的文件中
 * 7.存储类型
 * 7.1 普通内存、运行时堆栈、硬件寄存器
 *     静态变量：凡是在任何代码块之外声明的变量存储与静态内存中，在整个执行期间始终存在
 *     自动变量：在代码块内部声明的变量缺省存储类型是自动的，它存储于堆栈中，若代码块的变量加上static，则变为静态
 *     寄存器变量：register用于自动变量，则变量会存于硬件寄存器，访问起来效率高
 */


//========================第四章.语句========================
/* 1.空语句 一个分号 ；
 * 2.表达式语句：x = y + 3
 * 3.代码块
 * 4.if语句：许多程序员倾向于在任何时候都添加花括号
 *   else在没有花括号时，从属于最靠近它的不完整if语句
 * 5.while语句
 * 6.break:    终止循环
 *   continue：终止本次循环
 *   break和continue只对最内层的循环起作用
 * 7.for语句
 * 8.do{} while();语句：至少循环一次
 * 9.switch(){case : ; break; default: }；语句：不写break，进来后会继续执行下去，直到default的内容被执行完
 * 10.goto语句：跳出多层嵌套的循环。
 */


//========================第五章.操作符和表达式========================
/* 1.操作符
 * 1.1 算数操作符
 * 1.2 移位操作符
 *   左移位<<：最左边的几位被丢弃，右边多出来的几个空位则由0补齐（必须是整型）。
 *   右移位>>：逻辑移位：用0填充；算数移位：用符号位填充（必须是整型）。
 * 1.3 位操作符（必须整型）
 *     AND &：如果两个位都是1，结果为1，否则结果为0；
 *     OR  |：如果两个位都是0，结果为0，否则结果为1；
 *     XOR ^：两个位不同，结果为1，两个位相同，结果为0；
 * 1.4 赋值
 * 1.5 单目操作符
 *     ~     ： 求补
 *     &     ： 产生地址
 *     *     ： 访问指针所指向的值
 *     sizeof： 返回类型长度
 *    （类型） ： (float) a;
 *     ++,-- ： c = ++ a:c和a都+1。c= a++ :c没有+1。在左侧：先加1，再拷贝。在右侧：先拷贝，再加1。最后c与拷贝的那个值相等
 *     !     ：
 *     +     ：
 *     -     ：
 * 1.6 关系操作符
 *     >,>=,<,<=,!=,==
 * 1.7 逻辑操作符
 *     &&，||:短路求值。
 * 1.8 条件操作符
 *     b = a > 5 ? 3 : -20; // a大于5，b=3,a小于5，b=-20
 * 1.9 逗号操作符
 *     它能不能让程序更出色，更出色并不包括更炫、更酷、令人印象深刻
 * 1.10. 下标应用、函数调用、结构成员
 *       array[下标] 等于 *（array + （下标））
 *       .和->访问结构的成员。结构本身.成员；指针->成员
 * 2.布尔值
 * 2.1 不要通过把它与任何特定的值进行比较来测试这个变量是否为真值，应该：if(a)...或者if(!a)
 * 3.左值和右值
 * 4.表达式求值
 * 4.1 字符型和短整型操作数在使用之前被转换为普通整型
 * 4.2 算术转换：int a, b; long c = (long) a * b;
 * 4.3 操作符的属性
 *     看执行哪个，先看优先级，如果优先级一样，再看结合性。
 * 4.4 优先级和求值的顺序
 */


//========================第六章.指针========================
/* 1.内存和地址
 * 2.值和类型
 * 3.指针变量的内容
 * 4.间接访问操作符：*
 * 5.未初始化和非法指针
 * 5.1 int *a; *a = 12; //指针还没有进行初始化，所以12不知道会存储于什么地方
 * 5.2 数组名可以作为数组的地址：int *a = array;
 * 6.NULL指针
 * 6.1 如果你已经知道指针将被初始化为什么地址，就把它初始化为该地址，否则就把它初始化为NULL
 * 7.指针、间接访问和左值
 * 7.1 *&a=12等于a=12
 * 8.指针常量
 * 8.1 *(int *)100 = 25 // 将整型100变化为指向整型的指针，且地址为100，然后访问地址100，将地址100内的值设为25
 * 9.指针的指针
 * 9.1 int **c;
 * 10.指针表达式
 * 11.指针运算
 * 11.1 算术运算
 *      当一个指针和一个整数量执行算术运算时，整数在执行加法运算前始终会根据合适的大小（指向类型的大小）进行调整。
 *      *p++:①产生p的拷贝，不动②p++③访问拷贝的p上的内容。
 *      只有当两个指针都指向同一个数组中的元素时，才允许从一个指针减去另一个指针，得到两个内容在数组中的距离。
 * 11.2 关系运算
 *      前提时它们都指向同一个数组中的元素
 *      标准允许指向数组元素的指针与指向数组最后一个元素后面的那个内存位置的指针进行比较，
 *      但不允许与指向数组第一个元素之前的那个内存位置的指针进行比较
*/


//========================第七章.函数========================
/* 1.函数定义
 * 2.函数申明
 * 2.1 函数原型
 *     向编译器提供函数信息
 *     int *func(void);  //一个没有参数的函数原型需要写void
 * 2.2 函数的缺省认定：所有的函数都应该具有原型。
 * 3.函数的参数
 * 3.1 传递给函数的标量参数是传值调用的
 * 3.2 传递给函数的数组参数在行为上就像它们是通过传址调用的那样
 * 3.3 void clear_array(int array[], int n_elements)
 *    {
 *       while (n_elements >0)
 *           array[--n_elements] = 0;
 *    }
 * 4.ADT和黑盒
 * 4.1 限制对模块的访问是通过static关键字的合理使用实现的
 * 5.递归
 * 5.1 通过运行时堆栈支持递归函数的实现
 * 5.2 递归与迭代
 *     能迭代就不递归，递归消耗内存大，而且容易产生冗余计算，比如斐波那契数列的实现
 * 6.可变参数列表
 * 6.1 stdarg宏
 *     一个类型 ：va_list和三个宏：va_start\va_arg\va_end
 * 6.2 可变参数的限制
 *     这些宏无法判断实际存在的参数的数量
 *     这些宏无法判断每个参数的类型
 */


//========================第八章.数组========================
/* 1.一维数组
 * 1.1 数组名
 *     数组名的值是一个指针常量，也就是数组第1个元素的地址。只有当数组名在表达式中使用时，编译器才会为它产生一个指针常量。
 * 1.2 下标应用
 *     array[subscript] 等于 *(array + (subscript))  //array可以是数组名也可以是指针，数组名就是个指针
 *     *ap + 6 //先间接访问，再加6
 * 1.3 指针与下标
 *     下标绝不会比指针更有效率，但指针有时会比下标更有效率。
 * 1.4 指针的效率
 *     当在一个数组中移动时，使用指针变量将比使用下标产生效率更高的代码。
 * 1.5 数组和指针
 * 1.6 作为函数参数的数组名
 * 1.7 声明数组参数
 *     int f(char *string);等于 int f(char string[])
 *     如果函数需要知道数组的长度，它必须作为一个显式的参数传递给函数
 * 1.8 初始化
 *     静态和自动初始化：在程序的执行流每次进入该函数时，每次都对数组进行重新初始化是不是值得。如果不值得，就把数组声明为static。
 * 1.9 不完整的初始化
 * 1.10 自动计算数组长度
 *      int vector[] = {1,2,3};
 * 1.11 字符数组的初始化
 *      char message[] = "hello"
 * 2.多维数组
 * 2.1 存储顺序
 * 2.2 数组名
 *     指向第0行数组的指针
 * 2.3 下标
 *     二维数组matrix: *(matrix + 1):  括号里表示指向第一行的一维数组，*表示指向该一维数组第0个元素的指针
 * 2.4 指向数组的指针
 *     int matrix[3][10]; int (*p)[10] = matrix;  //p是一个指向整型数组的指针，p+1就是下一行
 *     int matrix[3][10]; int *pi = &matrix[0][0]  或者  int *pi = matrix[0]; p+1就是下一个
 * 2.5 作为函数参数的多维数组
 *     接受matrix[3][10]: void func(int (*p)[10]) 或者 void func(int ma[][10])
 * 2.6 初始化
 * 2.7 数组长度自动计算
 * 3.指针数组
 * 3.1 int *p[10];
 * 3.2 char *a[] = {"fuck", "you", "bitch"};
 */


//========================第九章.字符和字节========================
/* 1.字符串基础
 * 1.1 字符串就是一串零个或多个字符，并且以一个位模式为全0的NULL字节结尾。
 * 1.2 char message[] = "fuck you"; 或者 char *message = "fuck you";
 * 2.字符串长度
 * 2.1 size_t strlen(char const *string);  // 返回的是无符号数，无符号数减去无符号数还是无符号数！
 * 3.不受限制的字符串函数
 * 3.1 复制字符串：  char *strcpy(char *dst, char const *src);
 * 3.2 连接字符串：  char *strcat(char *dst, char const *src);
 * 3.3 函数的返回值：指向目标字符数组的指针，事实上，在绝大多数调用中，它们的返回值只是被简单的忽略。
 * 3.4 字符串比较：  int strcmp(char const *s1, char const *s2);  //如果相等，返回0
 * 4.长度受限的字符串函数
 * 4.1 char *strncpy(char *dst, char *src, size_t len);
 *     //如果src长度大于len，只有len个字符被复制，结果不以NULL结尾。所以加一句 *(dst + len) = '\0';
 *     char *strncat(char *dst, char const *src, size_t len);
 *     int  *strncmp(char const *s1, char const *s2);
 * 5.字符串查找基础
 * 6.高级字符串查找
 * 7.错误信息
 * 8.字符操作
 * 8.1 字符分类
 * 8.2 字符转换
 * 9.内存操作
 * 9.1 void *memcpy(void *dst, void const *src, size_t length);
 *     //复制length个字节；任何类型的指针都可以转换为void型指针。
 *     memmove;memcmp;memchr;memset;
 */


//========================第十章.结构和联合========================
/* 1.结构基础知识
 * 1.1 结构声明：
 *     struct SIMPLE
 *     {
 *          int  a;
 *          char b;
 *     };
 *     struct SIMPLE x;
 *     struct SIMPLE y[20], *z;
 *     或者：
 *     typedef struct
 *     {
 *          int  a;
 *          char b;
 *     } Simple;
 *     Simple x, y[20], *z;
 * 1.2 结构成员
 * 1.3 结构成员的直接访问 "."
 * 1.4 结构成员的间接访问 "->"
 * 1.5 结构的自应用
 *     struct SELF_REF
 *     {
 *         int a;
 *         struct SELF_REF *b;  //指针能指向这一种类型的结构，但是还没有指，所以是合法的
 *     }
 * 1.6 不完整的声明
 * 1.7 结构的初始化
 * 2.结构、指针和成员
 *      struct X{int a}x; struct X *p = &x;
 * 3.结构的存储分配
 * 3.1 所有结构的起始存储位置必须是结构中边界要求最严格的数据类型所要求的位置。
 * 4.作为函数参数的结构
 * 4.1 把结构作为参数传给一个函数是合法的，但它的效率很低。传递给函数的是指向结构的指针能调高效率。
 * 5.位段
 * 6.联合
 * 6.1 联合的所有成员引用的是内存中的相同位置。内存数量取决于它的最长成员的长度。
 */


//========================第十一章.动态内存分配========================
/* 1.为什么使用动态内存分配
 * 2.malloc和free
 *   void *malloc(size_t size);  //对每个从malloc返回的指针都进行检查，确保它并非NULL是非常重要的。
 *   void *free(void *pointer);
 * 3.calloc和realloc
 * 4.使用动态分配的内存
 *   int *pi;
 *   pi = malloc(25 * sizeof(int));
 *   if (pi == NULL) exit(1);  //要检查确保非NULL
 * 5.常见的动态内存错误
 */


//========================第十二章.使用结构和指针========================
/* 1.链表
 * 2.单链表
 *    每个节点包含一个指向链表下一节点的指针。最后一个节点的指针字段的值为NULL。
 *    跟指针指向链表的第一个节点。
 *    typedef struct NODE
 *    {
 *         struct NODE *link;
 *         int value;
 *    } Node;
 * 2.1 在单链表中插入：为了在链表的起始位置插入一个节点，函数必须修改跟指针。解决方法是把一个指向root的指针作为参数传递给函数。
 * 3.双链表
 *   每个节点包含两个指针。链表中第一个节点的bwd指针和最后一个节点的rwd指针都为NULL。
 *   两个跟指针，一个指向第一个节点，一个指向最后一个节点
 */


//========================第十三章.高级指针话题========================
/* 1.进一步探讨指向指针的指针
 * 2.高级声明
 *   int *f();      //f是一个函数，它的返回值是一个指向整型的指针。
 *   int (*f)();    //f是一个函数指针，它所指向的函数返回一个整型值。
 *   int *f[];      //f是一个数组，里面的成员是指向整型的指针。
 *   int (*f[])();  //f是一个数组，里面的成员是指向函数的指针，函数返回整型。
 *   int *(*f[])(); //f是一个数组，里面的成员是指向函数的指针，函数返回整型指针。
 * 3.函数指针
 * 3.1 初始化：int f(int);
 *           int (*pf)(int) = &f;  //&可以不加
 * 3.2 调用函数指针： ans = pf(25); 或者 ans = (*pf)(25);
 * 3.3 回调函数
 *     函数能在不同的时刻执行不同类型的工作
 *     实现：int f(int (*pf)(int, int)){}
 *          a = f(function);
 * 3.4 转移表
 *     int (*f_group[])(int, int) = {f1, f2, f3};
 *     result = f_group[1](3, 4);
 * 4.命令行参数
 * 5.字符串常量
 * 5.1 当一个字符串常量出现于表达式中时，它的值是指向第一个字符的指针。
 */


//========================第十四章.预处理器========================
/* 删除注释、插入#include包含的文件的内容、定义和替换由#define指令定义的符号、确定代码部分内容是否进行编译
 * 1.预定义符号
 *    _FILE_; _LINE_; _DATE_; _TIME_; _STDC_;
 * 2.#define
 * 2.1 宏
 *     #define SQUARE(x) ((x) * (x))  //多用括号
 * 2.2 #define 替换
 *     #define PRINT(FORMAT, VALUE)
 *             printf("The value is" FORMAT "\n", VALUE)
 *     PRINT("%d", x + 3);
 * 2.3 宏与函数
 *     #define MAX(a, b) ((a) > (b) ? (a) : (b))
 *     #define MALLOC(n, type) ((type *)malloc((n) * sizeof(type)))
 * 2.4 带副作用的宏参数
 *     #define MAX(a, b)  ((a) > (b) ? (a) : (b))
 *     x = 5;
 *     y = 8;
 *     z = MAX(x++, y++);
 *     结果：x = 6; y = 10; z = 9;
 * 2.5 命名约定
 *     宏名字全部大写
 * 2.6 #undef
 * 2.7 命令行定义
 * 3.条件编译
 *   #if CONSTANT_EXPRESSION
 *       STATEMENTS
 *   #elif CONSTANT_EXPRESSION
 *       OTHER STATEMENTS
 *   #endif
 * 3.1 是否被定义
 *     #ifdef symbol  等于 #if defined(symbol)
 *     #ifndef symbol 等于 #if !defined(symbol)
 * 3.2 嵌套指令
 * 4.文件包含
 * 4.1 函数库文件包含： #include <filename>
 * 4.2 本地文件包含：  #include "filename"
 * 4.3 嵌套文件包含： 消除嵌套：
 *     #ifndef _HEADERNAME_H
 *     #define _HEADERNAME_H 1
 *
 *     #endif
 * 5.其他指令
 */


//========================第十五章.输入\输出函数========================
/* 1.错误报告
 *   void perror(char const *message);  //errno.h
 * 2.终止执行
 *   void exit(int status);  (EXIT_SUCCESS; EXIT_FAILURE)  //stdlib.h
 * 3.标准I/O函数库
 * 4.ANSI I/O 概念
 * 4.1 流
 *     就C程序而言，所有的I/O操作只是简单地从程序移进或移出字节的事情。这种字节流被称为流。
 *     绝大多数流是完全缓冲的。“读取”和“写入”实际上是一块被称为缓冲区的内存区域来回复制数据。
 *     printf("something");
 *     fflush(stdout);  //迫使缓冲区的数据立即写入，不管它是否已满。
 * 4.2 文件
 *     FILE是一个数据结构，用于访问一个流。
 * 4.3 标准 I/O 常量
 * 5.流 I/O 总览
 * 6.打开流
 *   FILE *fopen(char const *name, char const *made);
 *   int main()
 *   {
 *       FILE *input;
 *       input = fopen("fuck", "r");
 *       if(input == NULL)
 *       {
 *            perror("fuck");  //用来将上一个函数发生错误的原因输出到标准设备
 *            exit(EXIT_FAILURE);
 *        }
 *    }
 * 7.关闭流
 *   int fcolse(FILE *f);  //执行成功，返回零值
 *   if (fclose(input) != 0)  //多判断是个好习惯，利于后期维护
 *   {
 *      perror("fclose");
 *      exit("EXIT_FAILURE");
 *   }
 * 8.字符I/O
 *   从流中读取：
 *   int fgetc(FILE *stream);
 *   int getc(FILE *stream);  //宏
 *   int getchar(void);  //此函数从标准输入读取，宏
 *   写入到流中：
 *   int fputc(int character, FILE *stream);
 *   int putc(int character, FILE *stream);  //宏
 *   int putchar(int character);  //宏
 *   撤销字符I/O：
 *   int ungetc(int character, FILE *stream);
 * 9.未格式化的行I/O
 *   简单读取或写入字符串
 *   char *fgets(char *buffer, int buffer_size, FILE *stream);
 *   char *gets(char *buffer);
 *   int fputs(char const *buffer, FILE *stream);
 *   int puts(char const *buffer);
 *   例：
 *      #define MAX_LINE_LENGTH 1024
 *      void
 *      copylines(FILE *input, FILE *output)
 *      {
 *          char buffer[MAX_LINE_LENGTH];
 *          while(fgets(buffer, MAX_LINE_LENGTH, input) != NULL)
 *          {
 *              fputs(buffer, output);
 *          }
 *      }
 * 10.格式化的行I/O
 *    执行数字和其他变量的内部和外部表示形式之间的转换。
 * 10.1 scanf家族
 *      int fscanf(FILE *stream, char const *format, ...);
 *      int scanf(char const *format, ...);
 *      int sscanf(char const *string, char const *format, ...);
 * 10.2 printf家族
 *      int fprintf(FILE *stream, char const *format, ...);
 *      int printf(char const *format, ...);
 *      int sprintf(char *buffer, char const *format, ...);
 * 11.二进制 I/O
 * 12.刷新和定位函数
 *    int fflush(FILE *stream);
 *    long ftell(FILE *stream);
 *    int fseek(FILE *stream, long offset, int from);
 * 13.改变缓冲方式
 * 14.流错误函数
 * 15.临时文件
 * 16.文件操纵函数
 */


//========================第十六章.标准函数库========================
/* 1.整形函数
 * 1.1 算数<stdlib.h>
 *     int abs(int value);
 *     long int labs(long int value);
 *     div_t div(int numerator, int denominator);    //用一个结构返回，包含商和余数
 *     ldiv_t ldiv(long int number, long int denom); //同上
 * 1.2 随机数<stdlib.h>
 *     int rand(void);  //伪随机数
 *     void srand(unsigned int seed);  //对随机数发生器进行初始化
 * 1.3 字符串转换
 *     int atoi(char *string);
 *     long int atol(char const *string);
 *     long int strtol(char const *string， char **unused, int base);
 *     unsigned long int strtoul(char const *string, char **unuesd, int base);
 * 2.浮点型函数
 * 2.1 三角函数<math.h>
 * 2.2 双曲函数
 * 2.3 对数和指数函数
 * 2.4 浮点表示形式
 * 2.5 幂
 * 2.6 底数、顶数、绝对值和余数
 *     floor;ceil;fabs;fmod
 * 2.7 字符串转换<stdlib.h>
 *     double atof(char const *string);
 *     double strtod(char const *string, char **unused);
 * 3.日期和时间函数
 * 3.1 处理器时间<time.h>
 * 3.2 当天时间
 * 4.非本地跳转<setjmp.h>
 * 5.信号
 *   程序可以调用signal函数，或者忽略这个信号，或者设置一个信号处理函数，当信号发生时程序就调用这个函数。
 * 6.打印可变参数列表<stdarg.h>
 * 7.执行环境
 * 7.1 执行环境
 * 7.2 断言<assert.h>  //为假跳出程序，为真什么都不做
 * 7.3 环境<stdlib.h>
 * 7.4 执行系统命令<stdlib.h>
 * 7.5 排序和查找<stdlib.h>
 * 7.6 locale
 */


//========================第十七章.经典抽象数据类型========================
/*ADT：链表、堆栈、队列、树等。
 * 1.内存分配
 * 1.1 三种方案：静态数组、动态分配的数组、动态分配的链式结构。
 * 2.堆栈
 *   后进先出（Last_In First_Out, LIFO）
 * 2.1 堆栈接口
 *     传统：
 *     push：把一个新值压入到堆栈的顶部。
 *     pop ：把堆栈顶部的值移出并返回这个值。
 *     其他：
 *     push：把一个新值压入到堆栈的顶部。
 *     pop ：把堆栈顶部的值移.
 *     top ：返回顶部元素的值。
 * 2.2 实现堆栈 */
//program 17.2.1  用静态数组实现堆栈
#if 0
#define STACK_SIZE 100  //堆栈中数量的最大限制
static STACK_TYPE stack[STACK_SIZE];  //所有不属于外部接口的内容都被声明为static
static int top_element = -1;

void push(STACK_TYPE value)
{
    assert(!is_full());
    top_element += 1;
    stack[top_element] = value;
}

void pop(void)
{
    assert(!is_empty());
    top_element -= 1;
}

STACK_TYPE top(void)
{
    assert(!is_empty());
    return stack[top_element];
}

int is_empty(void)
{
    return top_element == -1;
}

int is_full(void)
{
    return top_element == STACK_SIZE - 1;
}
#endif  //用静态数组实现堆栈

//program 17.2.2  用动态内存实现堆栈
#if 0
static STACK_TYPE *stack;
static size_t stack_size;
static int top_element = -1;

void creat_stack(size_t size)
{
    assert(stack_size == 0);
    stack_size = size;
    stack = malloc(stack_size * sizeof(STACK_TYPE));
    assert(stack != NULL);
}

void destroy_stack(void)
{
    assert(stack_size > 0);
    stack_size = 0;
    free(stack);
    stack = NULL;
}

void push(STACK_TYPE value)
{
    assert(!is_full());
    top_element += 1;
    stack[top_element] = value;
}

void pop(void)
{
    assert(!is_empty());
    top_element -= 1;
}

STACK_TYPE top(void)
{
    assert(!is_empty());
    return stack[top_element];
}

int is_empty(void)
{
    assert(stack_size > 0);
    return top_element == -1;
}

int is_full(void)
{
    assert(stack_size > 0);
    return top_element == stack_size - 1;
}
#endif  //用动态内存实现堆栈

//program 17.2.3  用单链实现堆栈
#if 0
#define FALSE 0

typedef struct STACK_NODE
{
    STACK_TYPE value;
    struct STACK_NODE *next;
} StackNode;

//指向堆栈中第一个节点的指针
static StackNode *stack;

void creat_stack(size_t size)
{
    //不用产生堆栈，直接用就行
}

void destroy_stack(void)
{
    while(!is_empty())
    {
        pop();
    }
}

void push(STACK_TYPE value)
{
    StackNode *new_node;
    new_node = malloc(sizeof(StackNode));
    assert(new_node != NULL);
    new_node->value = value;
    new_node->next = stack;
    stack = new_node;
}

void pop(void)
{
    StackNode *first_node;
    assert(!is_empty());
    first_node = stack;
    stack = first_node->next;
    free(first_node);
}

STACK_TYPE top(void)
{
    assert(!is_empty());
    return stack->value;
}

int is_empty(void)
{
    return stack == NULL;
}

int is_full(void)
{
    return FALSE;
}
#endif //用单链实现堆栈
/* 3.队列
 *   队列是一种先进先出(First-In First_Out, FIFO)
 * 3.1 队列接口
 * 3.2 实现队列
 *        静态数组：
 *          循环队列：让队列的尾部“环绕”到数组的头部。尾部下标移出尾部时，把它设置为0：rear = (rear + 1) % QUEUE_SIZE
 *          如何判断队列为空还是为满：让尾部下标指向最后一个元素的后面的位置，这个位置为空。当头部下标与尾部下标重合说明为空，
 *                             当尾部下标的前面一位是头部下标，则为满。
 *        动态数组：
 *          和堆栈的情况类似。
 *        链式队列：
 *          测试队列是否为空只是简单的是链表是否为空就可以了，是否以满的结果总是假。
 * 4.树
 *   二叉树：它的每个节点至多具有两个孩子，分别称为左孩子和右孩子。
 *   二叉搜索树：每个节点的值比它的左子树的所有节点的值都要大，但比它的右子树的所有的节点的值都要小。
 * 4.1 在二叉搜索树中插入
 *     如果树为空：
 *         把树作为跟节点插入
 *     否则：
 *         如果新值小于当前节点的值：
 *             把新值插入到当前节点的左子树
 *         否则：
 *             把新值插入到当前节点的右子树
 * 由于递归在算法的尾部出现，所以我们可以使用迭代更有效地实现这个算法。
 * 4.2 从二叉搜索树删除节点
 * 4.3 在二叉搜索树中查找
 *     如果树为空：
 *         这个值不存在树中
 *     否则：
 *         如果这个值和根节点地值相等：
 *             找到这个值
 *         否则：
 *             如果这个值小于根节点的值：
 *                 查找左子树
 *             否则：
 *                 查找右子树
 * 采用迭代方案来实现效率更高。
 * 4.4 树的遍历
 *     前序、中序、后序、层次遍历
 * 5.实现的改进
 */


//========================第十八章.运行时环境========================
/* 我的运行环境的限制是什么？我如何使C程序和汇编语言程序一起工作？
 * 1.判断运行时环境
 *   从你的编译器获得一个汇编语言代码列表
 *   阅读汇编语言代码
 * 2.C和汇编语言的接口
 * 3.运行时效率
 */