macro_line|#ifndef __LINUX_COMPILER_H
DECL|macro|__LINUX_COMPILER_H
mdefine_line|#define __LINUX_COMPILER_H
multiline_comment|/* Somewhere in the middle of the GCC 2.96 development cycle, we implemented&n;   a mechanism by which the user can annotate likely branch directions and&n;   expect the blocks to be reordered appropriately.  Define __builtin_expect&n;   to nothing for earlier compilers.  */
macro_line|#if __GNUC__ == 2 &amp;&amp; __GNUC_MINOR__ &lt; 96
DECL|macro|__builtin_expect
mdefine_line|#define __builtin_expect(x, expected_value) (x)
macro_line|#endif
DECL|macro|likely
mdefine_line|#define likely(x)&t;__builtin_expect((x),1)
DECL|macro|unlikely
mdefine_line|#define unlikely(x)&t;__builtin_expect((x),0)
multiline_comment|/* This macro obfuscates arithmetic on a variable address so that gcc&n;   shouldn&squot;t recognize the original var, and make assumptions about it */
id|strcpy
c_func
(paren
id|s
comma
l_string|&quot;xxx&quot;
op_plus
id|X
)paren
op_assign
OG
id|memcpy
c_func
(paren
id|s
comma
l_string|&quot;xxx&quot;
op_plus
id|X
comma
l_int|4
op_minus
id|X
)paren
op_star
op_div
DECL|macro|RELOC_HIDE
mdefine_line|#define RELOC_HIDE(var, off)&t;&t;&t;&t;&t;&t;&bslash;&n;  ({ __typeof__(&amp;(var)) __ptr;&t;&t;&t;&t;&t;&bslash;&n;    __asm__ (&quot;&quot; : &quot;=g&quot;(__ptr) : &quot;0&quot;((void *)&amp;(var) + (off)));&t;&bslash;&n;    *__ptr; })
macro_line|#endif /* __LINUX_COMPILER_H */
eof
