multiline_comment|/* Never include this file directly.  Include &lt;linux/compiler.h&gt; instead.  */
multiline_comment|/*&n; * Common definitions for all gcc versions go here.&n; */
multiline_comment|/* Optimization barrier */
multiline_comment|/* The &quot;volatile&quot; is due to gcc bugs */
DECL|macro|barrier
mdefine_line|#define barrier() __asm__ __volatile__(&quot;&quot;: : :&quot;memory&quot;)
multiline_comment|/* This macro obfuscates arithmetic on a variable address so that gcc&n;   shouldn&squot;t recognize the original var, and make assumptions about it */
DECL|macro|RELOC_HIDE
mdefine_line|#define RELOC_HIDE(ptr, off)&t;&t;&t;&t;&t;&bslash;&n;  ({ unsigned long __ptr;&t;&t;&t;&t;&t;&bslash;&n;    __asm__ (&quot;&quot; : &quot;=g&quot;(__ptr) : &quot;0&quot;(ptr));&t;&t;&bslash;&n;    (typeof(ptr)) (__ptr + (off)); })
eof
