multiline_comment|/* $Id: conv.h,v 1.4 1998/08/15 20:42:51 davem Exp $&n; * conv.h: Utility macros for Solaris emulation&n; *&n; * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
multiline_comment|/* #define DEBUG_SOLARIS */
DECL|macro|DEBUG_SOLARIS_KMALLOC
mdefine_line|#define DEBUG_SOLARIS_KMALLOC
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/unistd.h&gt;
multiline_comment|/* Use this to get at 32-bit user passed pointers. */
DECL|macro|A
mdefine_line|#define A(__x)&t;&t;&t;&t;&bslash;&n;({&t;unsigned long __ret;&t;&t;&bslash;&n;&t;__asm__ (&quot;srl&t;%0, 0, %0&quot;&t;&bslash;&n;&t;&t; : &quot;=r&quot; (__ret)&t;&t;&bslash;&n;&t;&t; : &quot;0&quot; (__x));&t;&t;&bslash;&n;&t;__ret;&t;&t;&t;&t;&bslash;&n;})
r_extern
r_int
id|sys_call_table
(braket
)braket
suffix:semicolon
r_extern
r_int
id|sys_call_table32
(braket
)braket
suffix:semicolon
r_extern
r_int
id|sunos_sys_table
(braket
)braket
suffix:semicolon
DECL|macro|SYS
mdefine_line|#define SYS(name) ((long)sys_call_table[__NR_##name])
DECL|macro|SUNOS
mdefine_line|#define SUNOS(x) ((long)sunos_sys_table[x])
macro_line|#ifdef DEBUG_SOLARIS
DECL|macro|SOLD
mdefine_line|#define SOLD(s) printk(&quot;%s,%d,%s(): %s&bslash;n&quot;,__FILE__,__LINE__,__FUNCTION__,(s))
DECL|macro|SOLDD
mdefine_line|#define SOLDD(s) printk(&quot;solaris: &quot;); printk s
macro_line|#else
DECL|macro|SOLD
mdefine_line|#define SOLD(s)
DECL|macro|SOLDD
mdefine_line|#define SOLDD(s)
macro_line|#endif
macro_line|#endif /* __ASSEMBLY__ */
eof
