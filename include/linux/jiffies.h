macro_line|#ifndef _LINUX_JIFFIES_H
DECL|macro|_LINUX_JIFFIES_H
mdefine_line|#define _LINUX_JIFFIES_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/seqlock.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/param.h&gt;&t;&t;&t;/* for HZ */
multiline_comment|/*&n; * The 64-bit value is not volatile - you MUST NOT read it&n; * without holding read_lock_irq(&amp;xtime_lock).&n; * get_jiffies_64() will do this for you as appropriate.&n; */
r_extern
id|u64
id|jiffies_64
suffix:semicolon
r_extern
r_int
r_int
r_volatile
id|jiffies
suffix:semicolon
macro_line|#if (BITS_PER_LONG &lt; 64)
id|u64
id|get_jiffies_64
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|function|get_jiffies_64
r_static
r_inline
id|u64
id|get_jiffies_64
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|u64
)paren
id|jiffies
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; *&t;These inlines deal with timer wrapping correctly. You are &n; *&t;strongly encouraged to use them&n; *&t;1. Because people otherwise forget&n; *&t;2. Because if the timer wrap changes in future you wont have to&n; *&t;   alter your driver code.&n; *&n; * time_after(a,b) returns true if the time a is after time b.&n; *&n; * Do this with &quot;&lt;0&quot; and &quot;&gt;=0&quot; to only test the sign of the result. A&n; * good compiler would generate better code (and a really good compiler&n; * wouldn&squot;t care). Gcc is currently neither.&n; */
DECL|macro|time_after
mdefine_line|#define time_after(a,b)&t;&t;((long)(b) - (long)(a) &lt; 0)
DECL|macro|time_before
mdefine_line|#define time_before(a,b)&t;time_after(b,a)
DECL|macro|time_after_eq
mdefine_line|#define time_after_eq(a,b)&t;((long)(a) - (long)(b) &gt;= 0)
DECL|macro|time_before_eq
mdefine_line|#define time_before_eq(a,b)&t;time_after_eq(b,a)
macro_line|#endif
eof
