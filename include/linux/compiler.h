macro_line|#ifndef __LINUX_COMPILER_H
DECL|macro|__LINUX_COMPILER_H
mdefine_line|#define __LINUX_COMPILER_H
multiline_comment|/* Somewhere in the middle of the GCC 2.96 development cycle, we implemented&n;   a mechanism by which the user can annotate likely branch directions and&n;   expect the blocks to be reordered appropriately.  Define __builtin_expect&n;   to nothing for earlier compilers.  */
macro_line|#if __GNUC__ == 2 &amp;&amp; __GNUC_MINOR__ &lt; 96
DECL|macro|__builtin_expect
mdefine_line|#define __builtin_expect(x, expected_value) (x)
macro_line|#endif
macro_line|#endif /* __LINUX_COMPILER_H */
eof
