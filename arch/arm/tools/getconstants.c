multiline_comment|/*&n; *  linux/arch/arm/tools/getconsdata.c&n; *&n; *  Copyright (C) 1995-2001 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n; * Make sure that the compiler and target are compatible.&n; */
macro_line|#if defined(__APCS_32__) &amp;&amp; defined(CONFIG_CPU_26)
macro_line|#error Sorry, your compiler targets APCS-32 but this kernel requires APCS-26
macro_line|#endif
macro_line|#if defined(__APCS_26__) &amp;&amp; defined(CONFIG_CPU_32)
macro_line|#error Sorry, your compiler targets APCS-26 but this kernel requires APCS-32
macro_line|#endif
macro_line|#if __GNUC__ &lt; 2 || (__GNUC__ == 2 &amp;&amp; __GNUC_MINOR__ &lt; 95)
macro_line|#error Sorry, your compiler is known to miscompile kernels.  Only use gcc 2.95.3 and later.
macro_line|#endif
macro_line|#if __GNUC__ == 2 &amp;&amp; __GNUC_MINOR__ == 95
multiline_comment|/* shame we can&squot;t detect the .1 or .2 releases */
macro_line|#warning GCC 2.95.2 and earlier miscompiles kernels.
macro_line|#endif
DECL|macro|OFF_TSK
mdefine_line|#define OFF_TSK(n) (unsigned long)&amp;(((struct task_struct *)0)-&gt;n)
DECL|macro|DEFN
mdefine_line|#define DEFN(name,off) asm(&quot;&bslash;n#define &quot;name&quot; %0&quot; :: &quot;I&quot; (off))
DECL|function|func
r_void
id|func
c_func
(paren
r_void
)paren
(brace
id|DEFN
c_func
(paren
l_string|&quot;TSK_SIGPENDING&quot;
comma
id|OFF_TSK
c_func
(paren
id|sigpending
)paren
)paren
suffix:semicolon
id|DEFN
c_func
(paren
l_string|&quot;TSK_ADDR_LIMIT&quot;
comma
id|OFF_TSK
c_func
(paren
id|addr_limit
)paren
)paren
suffix:semicolon
id|DEFN
c_func
(paren
l_string|&quot;TSK_NEED_RESCHED&quot;
comma
id|OFF_TSK
c_func
(paren
id|need_resched
)paren
)paren
suffix:semicolon
id|DEFN
c_func
(paren
l_string|&quot;TSK_PTRACE&quot;
comma
id|OFF_TSK
c_func
(paren
id|ptrace
)paren
)paren
suffix:semicolon
id|DEFN
c_func
(paren
l_string|&quot;TSK_USED_MATH&quot;
comma
id|OFF_TSK
c_func
(paren
id|used_math
)paren
)paren
suffix:semicolon
id|DEFN
c_func
(paren
l_string|&quot;TSS_SAVE&quot;
comma
id|OFF_TSK
c_func
(paren
id|thread.save
)paren
)paren
suffix:semicolon
id|DEFN
c_func
(paren
l_string|&quot;TSS_FPESAVE&quot;
comma
id|OFF_TSK
c_func
(paren
id|thread.fpstate.soft.save
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_32
id|DEFN
c_func
(paren
l_string|&quot;TSS_DOMAIN&quot;
comma
id|OFF_TSK
c_func
(paren
id|thread.domain
)paren
)paren
suffix:semicolon
id|DEFN
c_func
(paren
l_string|&quot;HPTE_TYPE_SMALL&quot;
comma
id|PTE_TYPE_SMALL
)paren
suffix:semicolon
id|DEFN
c_func
(paren
l_string|&quot;HPTE_AP_READ&quot;
comma
id|PTE_AP_READ
)paren
suffix:semicolon
id|DEFN
c_func
(paren
l_string|&quot;HPTE_AP_WRITE&quot;
comma
id|PTE_AP_WRITE
)paren
suffix:semicolon
id|DEFN
c_func
(paren
l_string|&quot;LPTE_PRESENT&quot;
comma
id|L_PTE_PRESENT
)paren
suffix:semicolon
id|DEFN
c_func
(paren
l_string|&quot;LPTE_YOUNG&quot;
comma
id|L_PTE_YOUNG
)paren
suffix:semicolon
id|DEFN
c_func
(paren
l_string|&quot;LPTE_BUFFERABLE&quot;
comma
id|L_PTE_BUFFERABLE
)paren
suffix:semicolon
id|DEFN
c_func
(paren
l_string|&quot;LPTE_CACHEABLE&quot;
comma
id|L_PTE_CACHEABLE
)paren
suffix:semicolon
id|DEFN
c_func
(paren
l_string|&quot;LPTE_USER&quot;
comma
id|L_PTE_USER
)paren
suffix:semicolon
id|DEFN
c_func
(paren
l_string|&quot;LPTE_WRITE&quot;
comma
id|L_PTE_WRITE
)paren
suffix:semicolon
id|DEFN
c_func
(paren
l_string|&quot;LPTE_EXEC&quot;
comma
id|L_PTE_EXEC
)paren
suffix:semicolon
id|DEFN
c_func
(paren
l_string|&quot;LPTE_DIRTY&quot;
comma
id|L_PTE_DIRTY
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_CPU_26
id|DEFN
c_func
(paren
l_string|&quot;PAGE_PRESENT&quot;
comma
id|_PAGE_PRESENT
)paren
suffix:semicolon
id|DEFN
c_func
(paren
l_string|&quot;PAGE_READONLY&quot;
comma
id|_PAGE_READONLY
)paren
suffix:semicolon
id|DEFN
c_func
(paren
l_string|&quot;PAGE_NOT_USER&quot;
comma
id|_PAGE_NOT_USER
)paren
suffix:semicolon
id|DEFN
c_func
(paren
l_string|&quot;PAGE_OLD&quot;
comma
id|_PAGE_OLD
)paren
suffix:semicolon
id|DEFN
c_func
(paren
l_string|&quot;PAGE_CLEAN&quot;
comma
id|_PAGE_CLEAN
)paren
suffix:semicolon
macro_line|#endif
id|DEFN
c_func
(paren
l_string|&quot;PAGE_SZ&quot;
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|DEFN
c_func
(paren
l_string|&quot;SYS_ERROR0&quot;
comma
l_int|0x9f0000
)paren
suffix:semicolon
)brace
eof
