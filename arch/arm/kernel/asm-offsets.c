multiline_comment|/*&n; * Copyright (C) 1995-2003 Russell King&n; *               2001-2002 Keith Owens&n; *     &n; * Generate definitions needed by assembly language modules.&n; * This code generates raw asm output which is post-processed to extract&n; * and format the required data.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
multiline_comment|/*&n; * Make sure that the compiler and target are compatible.&n; */
macro_line|#if defined(__APCS_26__)
macro_line|#error Sorry, your compiler targets APCS-26 but this kernel requires APCS-32
macro_line|#endif
multiline_comment|/*&n; * GCC 2.95.1, 2.95.2: ignores register clobber list in asm().&n; * GCC 3.0, 3.1: general bad code generation.&n; * GCC 3.2.0: incorrect function argument offset calculation.&n; * GCC 3.2.x: miscompiles NEW_AUX_ENT in fs/binfmt_elf.c&n; *            (http://gcc.gnu.org/PR8896) and incorrect structure&n; *&t;      initialisation in fs/jffs2/erase.c&n; */
macro_line|#if __GNUC__ &lt; 2 || &bslash;&n;   (__GNUC__ == 2 &amp;&amp; __GNUC_MINOR__ &lt; 95) || &bslash;&n;   (__GNUC__ == 2 &amp;&amp; __GNUC_MINOR__ == 95 &amp;&amp; __GNUC_PATCHLEVEL__ != 0 &amp;&amp; &bslash;&n;&t;&t;&t;&t;&t;     __GNUC_PATCHLEVEL__ &lt; 3) || &bslash;&n;   (__GNUC__ == 3 &amp;&amp; __GNUC_MINOR__ &lt; 3)
macro_line|#error Your compiler is too buggy; it is known to miscompile kernels.
macro_line|#error    Known good compilers: 2.95.3, 2.95.4, 2.96, 3.3
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
macro_line|#if __LINUX_ARM_ARCH__ &gt;= 6
id|DEFINE
c_func
(paren
id|MM_CONTEXT_ID
comma
m_offsetof
(paren
r_struct
id|mm_struct
comma
id|context.id
)paren
)paren
suffix:semicolon
macro_line|#endif
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
