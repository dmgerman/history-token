macro_line|#ifndef _LINUX_KERNEL_H
DECL|macro|_LINUX_KERNEL_H
mdefine_line|#define _LINUX_KERNEL_H
multiline_comment|/*&n; * &squot;kernel.h&squot; contains some often-used function prototypes etc&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
multiline_comment|/* Optimization barrier */
multiline_comment|/* The &quot;volatile&quot; is due to gcc bugs */
DECL|macro|barrier
mdefine_line|#define barrier() __asm__ __volatile__(&quot;&quot;: : :&quot;memory&quot;)
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
DECL|macro|NORET_TYPE
macro_line|# define NORET_TYPE    /**/
DECL|macro|ATTRIB_NORET
macro_line|# define ATTRIB_NORET  __attribute__((noreturn))
DECL|macro|NORET_AND
macro_line|# define NORET_AND     noreturn,
macro_line|#ifdef __i386__
DECL|macro|FASTCALL
mdefine_line|#define FASTCALL(x)&t;x __attribute__((regparm(3)))
macro_line|#else
DECL|macro|FASTCALL
mdefine_line|#define FASTCALL(x)&t;x
macro_line|#endif
r_struct
id|semaphore
suffix:semicolon
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
id|up_and_exit
c_func
(paren
r_struct
id|semaphore
op_star
comma
r_int
)paren
id|ATTRIB_NORET
suffix:semicolon
r_extern
r_int
id|abs
c_func
(paren
r_int
)paren
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
r_void
id|dev_probe_lock
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|dev_probe_unlock
c_func
(paren
r_void
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
r_extern
r_int
id|console_loglevel
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
macro_line|#if DEBUG
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
DECL|macro|HIPQUAD
mdefine_line|#define HIPQUAD(addr) &bslash;&n;&t;((unsigned char *)&amp;addr)[3], &bslash;&n;&t;((unsigned char *)&amp;addr)[2], &bslash;&n;&t;((unsigned char *)&amp;addr)[1], &bslash;&n;&t;((unsigned char *)&amp;addr)[0]
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
macro_line|#endif
eof
