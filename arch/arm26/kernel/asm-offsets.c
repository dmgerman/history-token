multiline_comment|/*&n; * Copyright (C) 1995-2001 Russell King&n; *               2001-2002 Keith Owens&n; *               2003      Ian Molton&n; *     &n; * Generate definitions needed by assembly language modules.&n; * This code generates raw asm output which is post-processed to extract&n; * and format the required data.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n; * Make sure that the compiler and target are compatible.&n; */
macro_line|#if defined(__APCS_32__) &amp;&amp; defined(CONFIG_CPU_26)
macro_line|#error Sorry, your compiler targets APCS-32 but this kernel requires APCS-26
macro_line|#endif
macro_line|#if __GNUC__ &lt; 2 || (__GNUC__ == 2 &amp;&amp; __GNUC_MINOR__ &lt; 95)
macro_line|#error Sorry, your compiler is known to miscompile kernels.  Only use gcc 2.95.3 and later.
macro_line|#endif
macro_line|#if __GNUC__ == 2 &amp;&amp; __GNUC_MINOR__ == 95
multiline_comment|/* shame we can&squot;t detect the .1 or .2 releases */
macro_line|#warning GCC 2.95.2 and earlier miscompiles kernels.
macro_line|#endif
multiline_comment|/* Use marker if you need to separate the values later */
DECL|macro|DEFINE
mdefine_line|#define DEFINE(sym, val) &bslash;&n;        asm volatile(&quot;&bslash;n-&gt;&quot; #sym &quot; %0 &quot; #val : : &quot;i&quot; (val))
DECL|macro|BLANK
mdefine_line|#define BLANK() asm volatile(&quot;&bslash;n-&gt;&quot; : : )
DECL|function|main
r_int
id|main
c_func
(paren
r_void
)paren
(brace
id|DEFINE
c_func
(paren
id|TSK_ACTIVE_MM
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|active_mm
)paren
)paren
suffix:semicolon
id|BLANK
c_func
(paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|VMA_VM_MM
comma
m_offsetof
(paren
r_struct
id|vm_area_struct
comma
id|vm_mm
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|VMA_VM_FLAGS
comma
m_offsetof
(paren
r_struct
id|vm_area_struct
comma
id|vm_flags
)paren
)paren
suffix:semicolon
id|BLANK
c_func
(paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|VM_EXEC
comma
id|VM_EXEC
)paren
suffix:semicolon
id|BLANK
c_func
(paren
)paren
suffix:semicolon
id|BLANK
c_func
(paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PAGE_PRESENT
comma
id|_PAGE_PRESENT
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PAGE_READONLY
comma
id|_PAGE_READONLY
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PAGE_NOT_USER
comma
id|_PAGE_NOT_USER
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PAGE_OLD
comma
id|_PAGE_OLD
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PAGE_CLEAN
comma
id|_PAGE_CLEAN
)paren
suffix:semicolon
id|BLANK
c_func
(paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PAGE_SZ
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|BLANK
c_func
(paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|SYS_ERROR0
comma
l_int|0x9f0000
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
