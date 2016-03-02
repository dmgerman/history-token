macro_line|#ifndef _LINUX_KERNEL_H
DECL|macro|_LINUX_KERNEL_H
mdefine_line|#define _LINUX_KERNEL_H
multiline_comment|/*&n; * &squot;kernel.h&squot; contains some often-used function prototypes etc&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/bug.h&gt;
DECL|macro|INT_MAX
mdefine_line|#define INT_MAX&t;&t;((int)(~0U&gt;&gt;1))
DECL|macro|INT_MIN
mdefine_line|#define INT_MIN&t;&t;(-INT_MAX - 1)
DECL|macro|UINT_MAX
mdefine_line|#define UINT_MAX&t;(~0U)
DECL|macro|LONG_MAX
mdefine_line|#define LONG_MAX&t;((long)(~0UL&gt;&gt;1))
DECL|macro|LONG_MIN
mdefine_line|#define LONG_MIN&t;(-LONG_MAX - 1)
DECL|macro|ULONG_MAX
mdefine_line|#define ULONG_MAX&t;(~0UL)
DECL|macro|STACK_MAGIC
mdefine_line|#define STACK_MAGIC&t;0xdeadbeef
DECL|macro|ARRAY_SIZE
mdefine_line|#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
DECL|macro|ALIGN
mdefine_line|#define ALIGN(x,a) (((x)+(a)-1)&amp;~((a)-1))
DECL|macro|KERN_EMERG
mdefine_line|#define&t;KERN_EMERG&t;&quot;&lt;0&gt;&quot;&t;/* system is unusable&t;&t;&t;*/
DECL|macro|KERN_ALERT
mdefine_line|#define&t;KERN_ALERT&t;&quot;&lt;1&gt;&quot;&t;/* action must be taken immediately&t;*/
DECL|macro|KERN_CRIT
mdefine_line|#define&t;KERN_CRIT&t;&quot;&lt;2&gt;&quot;&t;/* critical conditions&t;&t;&t;*/
DECL|macro|KERN_ERR
mdefine_line|#define&t;KERN_ERR&t;&quot;&lt;3&gt;&quot;&t;/* error conditions&t;&t;&t;*/
DECL|macro|KERN_WARNING
mdefine_line|#define&t;KERN_WARNING&t;&quot;&lt;4&gt;&quot;&t;/* warning conditions&t;&t;&t;*/
DECL|macro|KERN_NOTICE
mdefine_line|#define&t;KERN_NOTICE&t;&quot;&lt;5&gt;&quot;&t;/* normal but significant condition&t;*/
DECL|macro|KERN_INFO
mdefine_line|#define&t;KERN_INFO&t;&quot;&lt;6&gt;&quot;&t;/* informational&t;&t;&t;*/
DECL|macro|KERN_DEBUG
mdefine_line|#define&t;KERN_DEBUG&t;&quot;&lt;7&gt;&quot;&t;/* debug-level messages&t;&t;&t;*/
r_extern
r_int
id|console_printk
(braket
)braket
suffix:semicolon
DECL|macro|console_loglevel
mdefine_line|#define console_loglevel (console_printk[0])
DECL|macro|default_message_loglevel
mdefine_line|#define default_message_loglevel (console_printk[1])
DECL|macro|minimum_console_loglevel
mdefine_line|#define minimum_console_loglevel (console_printk[2])
DECL|macro|default_console_loglevel
mdefine_line|#define default_console_loglevel (console_printk[3])
r_struct
id|completion
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_SPINLOCK_SLEEP
r_void
id|__might_sleep
c_func
(paren
r_char
op_star
id|file
comma
r_int
id|line
)paren
suffix:semicolon
DECL|macro|might_sleep
mdefine_line|#define might_sleep() __might_sleep(__FILE__, __LINE__)
DECL|macro|might_sleep_if
mdefine_line|#define might_sleep_if(cond) do { if (unlikely(cond)) might_sleep(); } while (0)
macro_line|#else
DECL|macro|might_sleep
mdefine_line|#define might_sleep() do {} while(0)
DECL|macro|might_sleep_if
mdefine_line|#define might_sleep_if(cond) do {} while (0)
macro_line|#endif
DECL|macro|abs
mdefine_line|#define abs(x) ({&t;&t;&t;&t;&bslash;&n;&t;&t;int __x = (x);&t;&t;&t;&bslash;&n;&t;&t;(__x &lt; 0) ? -__x : __x;&t;&t;&bslash;&n;&t;})
DECL|macro|labs
mdefine_line|#define labs(x) ({&t;&t;&t;&t;&bslash;&n;&t;&t;long __x = (x);&t;&t;&t;&bslash;&n;&t;&t;(__x &lt; 0) ? -__x : __x;&t;&t;&bslash;&n;&t;})
r_extern
r_struct
id|notifier_block
op_star
id|panic_notifier_list
suffix:semicolon
id|NORET_TYPE
r_void
id|panic
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|NORET_AND
id|format
(paren
id|printf
comma
l_int|1
comma
l_int|2
)paren
)paren
)paren
suffix:semicolon
id|asmlinkage
id|NORET_TYPE
r_void
id|do_exit
c_func
(paren
r_int
id|error_code
)paren
id|ATTRIB_NORET
suffix:semicolon
id|NORET_TYPE
r_void
id|complete_and_exit
c_func
(paren
r_struct
id|completion
op_star
comma
r_int
)paren
id|ATTRIB_NORET
suffix:semicolon
r_extern
r_int
r_int
id|simple_strtoul
c_func
(paren
r_const
r_char
op_star
comma
r_char
op_star
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|simple_strtol
c_func
(paren
r_const
r_char
op_star
comma
r_char
op_star
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
r_int
id|simple_strtoull
c_func
(paren
r_const
r_char
op_star
comma
r_char
op_star
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|simple_strtoll
c_func
(paren
r_const
r_char
op_star
comma
r_char
op_star
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|sprintf
c_func
(paren
r_char
op_star
id|buf
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|format
(paren
id|printf
comma
l_int|2
comma
l_int|3
)paren
)paren
)paren
suffix:semicolon
r_extern
r_int
id|vsprintf
c_func
(paren
r_char
op_star
id|buf
comma
r_const
r_char
op_star
comma
id|va_list
)paren
suffix:semicolon
r_extern
r_int
id|snprintf
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|size
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|format
(paren
id|printf
comma
l_int|3
comma
l_int|4
)paren
)paren
)paren
suffix:semicolon
r_extern
r_int
id|vsnprintf
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|size
comma
r_const
r_char
op_star
id|fmt
comma
id|va_list
id|args
)paren
suffix:semicolon
r_extern
r_int
id|scnprintf
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|size
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|format
(paren
id|printf
comma
l_int|3
comma
l_int|4
)paren
)paren
)paren
suffix:semicolon
r_extern
r_int
id|vscnprintf
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|size
comma
r_const
r_char
op_star
id|fmt
comma
id|va_list
id|args
)paren
suffix:semicolon
r_extern
r_int
id|sscanf
c_func
(paren
r_const
r_char
op_star
comma
r_const
r_char
op_star
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|format
(paren
id|scanf
comma
l_int|2
comma
l_int|3
)paren
)paren
)paren
suffix:semicolon
r_extern
r_int
id|vsscanf
c_func
(paren
r_const
r_char
op_star
comma
r_const
r_char
op_star
comma
id|va_list
)paren
suffix:semicolon
r_extern
r_int
id|get_option
c_func
(paren
r_char
op_star
op_star
id|str
comma
r_int
op_star
id|pint
)paren
suffix:semicolon
r_extern
r_char
op_star
id|get_options
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_int
id|nints
comma
r_int
op_star
id|ints
)paren
suffix:semicolon
r_extern
r_int
r_int
r_int
id|memparse
c_func
(paren
r_char
op_star
id|ptr
comma
r_char
op_star
op_star
id|retptr
)paren
suffix:semicolon
r_extern
r_int
id|kernel_text_address
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|session_of_pgrp
c_func
(paren
r_int
id|pgrp
)paren
suffix:semicolon
id|asmlinkage
r_int
id|printk
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|format
(paren
id|printf
comma
l_int|1
comma
l_int|2
)paren
)paren
)paren
suffix:semicolon
r_int
r_int
id|int_sqrt
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|function|long_log2
r_static
r_inline
r_int
id|__attribute_pure__
id|long_log2
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_int
id|r
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|x
op_rshift_assign
l_int|1
suffix:semicolon
id|x
OG
l_int|0
suffix:semicolon
id|x
op_rshift_assign
l_int|1
)paren
id|r
op_increment
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
r_extern
r_int
id|printk_ratelimit
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|__printk_ratelimit
c_func
(paren
r_int
id|ratelimit_jiffies
comma
r_int
id|ratelimit_burst
)paren
suffix:semicolon
DECL|function|console_silent
r_static
r_inline
r_void
id|console_silent
c_func
(paren
r_void
)paren
(brace
id|console_loglevel
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|console_verbose
r_static
r_inline
r_void
id|console_verbose
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|console_loglevel
)paren
id|console_loglevel
op_assign
l_int|15
suffix:semicolon
)brace
r_extern
r_void
id|bust_spinlocks
c_func
(paren
r_int
id|yes
)paren
suffix:semicolon
r_extern
r_int
id|oops_in_progress
suffix:semicolon
multiline_comment|/* If set, an oops, panic(), BUG() or die() is in progress */
r_extern
r_int
id|panic_on_oops
suffix:semicolon
r_extern
r_int
id|tainted
suffix:semicolon
r_extern
r_const
r_char
op_star
id|print_tainted
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Values used for system_state */
DECL|enum|system_states
r_extern
r_enum
id|system_states
(brace
DECL|enumerator|SYSTEM_BOOTING
id|SYSTEM_BOOTING
comma
DECL|enumerator|SYSTEM_RUNNING
id|SYSTEM_RUNNING
comma
DECL|enumerator|SYSTEM_HALT
id|SYSTEM_HALT
comma
DECL|enumerator|SYSTEM_POWER_OFF
id|SYSTEM_POWER_OFF
comma
DECL|enumerator|SYSTEM_RESTART
id|SYSTEM_RESTART
comma
)brace
id|system_state
suffix:semicolon
DECL|macro|TAINT_PROPRIETARY_MODULE
mdefine_line|#define TAINT_PROPRIETARY_MODULE&t;(1&lt;&lt;0)
DECL|macro|TAINT_FORCED_MODULE
mdefine_line|#define TAINT_FORCED_MODULE&t;&t;(1&lt;&lt;1)
DECL|macro|TAINT_UNSAFE_SMP
mdefine_line|#define TAINT_UNSAFE_SMP&t;&t;(1&lt;&lt;2)
DECL|macro|TAINT_FORCED_RMMOD
mdefine_line|#define TAINT_FORCED_RMMOD&t;&t;(1&lt;&lt;3)
r_extern
r_void
id|dump_stack
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
DECL|macro|pr_debug
mdefine_line|#define pr_debug(fmt,arg...) &bslash;&n;&t;printk(KERN_DEBUG fmt,##arg)
macro_line|#else
DECL|macro|pr_debug
mdefine_line|#define pr_debug(fmt,arg...) &bslash;&n;&t;do { } while (0)
macro_line|#endif
DECL|macro|pr_info
mdefine_line|#define pr_info(fmt,arg...) &bslash;&n;&t;printk(KERN_INFO fmt,##arg)
multiline_comment|/*&n; *      Display an IP address in readable format.&n; */
DECL|macro|NIPQUAD
mdefine_line|#define NIPQUAD(addr) &bslash;&n;&t;((unsigned char *)&amp;addr)[0], &bslash;&n;&t;((unsigned char *)&amp;addr)[1], &bslash;&n;&t;((unsigned char *)&amp;addr)[2], &bslash;&n;&t;((unsigned char *)&amp;addr)[3]
DECL|macro|NIP6
mdefine_line|#define NIP6(addr) &bslash;&n;&t;ntohs((addr).s6_addr16[0]), &bslash;&n;&t;ntohs((addr).s6_addr16[1]), &bslash;&n;&t;ntohs((addr).s6_addr16[2]), &bslash;&n;&t;ntohs((addr).s6_addr16[3]), &bslash;&n;&t;ntohs((addr).s6_addr16[4]), &bslash;&n;&t;ntohs((addr).s6_addr16[5]), &bslash;&n;&t;ntohs((addr).s6_addr16[6]), &bslash;&n;&t;ntohs((addr).s6_addr16[7])
macro_line|#if defined(__LITTLE_ENDIAN)
DECL|macro|HIPQUAD
mdefine_line|#define HIPQUAD(addr) &bslash;&n;&t;((unsigned char *)&amp;addr)[3], &bslash;&n;&t;((unsigned char *)&amp;addr)[2], &bslash;&n;&t;((unsigned char *)&amp;addr)[1], &bslash;&n;&t;((unsigned char *)&amp;addr)[0]
macro_line|#elif defined(__BIG_ENDIAN)
DECL|macro|HIPQUAD
mdefine_line|#define HIPQUAD&t;NIPQUAD
macro_line|#else
macro_line|#error &quot;Please fix asm/byteorder.h&quot;
macro_line|#endif /* __LITTLE_ENDIAN */
multiline_comment|/*&n; * min()/max() macros that also do&n; * strict type-checking.. See the&n; * &quot;unnecessary&quot; pointer comparison.&n; */
DECL|macro|min
mdefine_line|#define min(x,y) ({ &bslash;&n;&t;typeof(x) _x = (x);&t;&bslash;&n;&t;typeof(y) _y = (y);&t;&bslash;&n;&t;(void) (&amp;_x == &amp;_y);&t;&t;&bslash;&n;&t;_x &lt; _y ? _x : _y; })
DECL|macro|max
mdefine_line|#define max(x,y) ({ &bslash;&n;&t;typeof(x) _x = (x);&t;&bslash;&n;&t;typeof(y) _y = (y);&t;&bslash;&n;&t;(void) (&amp;_x == &amp;_y);&t;&t;&bslash;&n;&t;_x &gt; _y ? _x : _y; })
multiline_comment|/*&n; * ..and if you can&squot;t take the strict&n; * types, you can specify one yourself.&n; *&n; * Or not use min/max at all, of course.&n; */
DECL|macro|min_t
mdefine_line|#define min_t(type,x,y) &bslash;&n;&t;({ type __x = (x); type __y = (y); __x &lt; __y ? __x: __y; })
DECL|macro|max_t
mdefine_line|#define max_t(type,x,y) &bslash;&n;&t;({ type __x = (x); type __y = (y); __x &gt; __y ? __x: __y; })
multiline_comment|/**&n; * container_of - cast a member of a structure out to the containing structure&n; *&n; * @ptr:&t;the pointer to the member.&n; * @type:&t;the type of the container struct this is embedded in.&n; * @member:&t;the name of the member within the struct.&n; *&n; */
DECL|macro|container_of
mdefine_line|#define container_of(ptr, type, member) ({&t;&t;&t;&bslash;&n;        const typeof( ((type *)0)-&gt;member ) *__mptr = (ptr);&t;&bslash;&n;        (type *)( (char *)__mptr - offsetof(type,member) );})
multiline_comment|/*&n; * Check at compile time that something is of a particular type.&n; * Always evaluates to 1 so you may use it easily in comparisons.&n; */
DECL|macro|typecheck
mdefine_line|#define typecheck(type,x) &bslash;&n;({&t;type __dummy; &bslash;&n;&t;typeof(x) __dummy2; &bslash;&n;&t;(void)(&amp;__dummy == &amp;__dummy2); &bslash;&n;&t;1; &bslash;&n;})
macro_line|#endif /* __KERNEL__ */
DECL|macro|SI_LOAD_SHIFT
mdefine_line|#define SI_LOAD_SHIFT&t;16
DECL|struct|sysinfo
r_struct
id|sysinfo
(brace
DECL|member|uptime
r_int
id|uptime
suffix:semicolon
multiline_comment|/* Seconds since boot */
DECL|member|loads
r_int
r_int
id|loads
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* 1, 5, and 15 minute load averages */
DECL|member|totalram
r_int
r_int
id|totalram
suffix:semicolon
multiline_comment|/* Total usable main memory size */
DECL|member|freeram
r_int
r_int
id|freeram
suffix:semicolon
multiline_comment|/* Available memory size */
DECL|member|sharedram
r_int
r_int
id|sharedram
suffix:semicolon
multiline_comment|/* Amount of shared memory */
DECL|member|bufferram
r_int
r_int
id|bufferram
suffix:semicolon
multiline_comment|/* Memory used by buffers */
DECL|member|totalswap
r_int
r_int
id|totalswap
suffix:semicolon
multiline_comment|/* Total swap space size */
DECL|member|freeswap
r_int
r_int
id|freeswap
suffix:semicolon
multiline_comment|/* swap space still available */
DECL|member|procs
r_int
r_int
id|procs
suffix:semicolon
multiline_comment|/* Number of current processes */
DECL|member|pad
r_int
r_int
id|pad
suffix:semicolon
multiline_comment|/* explicit padding for m68k */
DECL|member|totalhigh
r_int
r_int
id|totalhigh
suffix:semicolon
multiline_comment|/* Total high memory size */
DECL|member|freehigh
r_int
r_int
id|freehigh
suffix:semicolon
multiline_comment|/* Available high memory size */
DECL|member|mem_unit
r_int
r_int
id|mem_unit
suffix:semicolon
multiline_comment|/* Memory unit size in bytes */
DECL|member|_f
r_char
id|_f
(braket
l_int|20
op_minus
l_int|2
op_star
r_sizeof
(paren
r_int
)paren
op_minus
r_sizeof
(paren
r_int
)paren
)braket
suffix:semicolon
multiline_comment|/* Padding: libc5 uses this.. */
)brace
suffix:semicolon
r_extern
r_void
id|BUILD_BUG
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|BUILD_BUG_ON
mdefine_line|#define BUILD_BUG_ON(condition) do { if (condition) BUILD_BUG(); } while(0)
multiline_comment|/* Trap pasters of __FUNCTION__ at compile-time */
macro_line|#if __GNUC__ &gt; 2 || __GNUC_MINOR__ &gt;= 95
DECL|macro|__FUNCTION__
mdefine_line|#define __FUNCTION__ (__func__)
macro_line|#endif
macro_line|#endif
eof
