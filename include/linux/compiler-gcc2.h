multiline_comment|/* Never include this file directly.  Include &lt;linux/compiler.h&gt; instead.  */
multiline_comment|/* These definitions are for GCC v2.x.  */
multiline_comment|/* Somewhere in the middle of the GCC 2.96 development cycle, we implemented&n;   a mechanism by which the user can annotate likely branch directions and&n;   expect the blocks to be reordered appropriately.  Define __builtin_expect&n;   to nothing for earlier compilers.  */
macro_line|#include &lt;linux/compiler-gcc.h&gt;
macro_line|#if __GNUC_MINOR__ &lt; 96
DECL|macro|__builtin_expect
macro_line|# define __builtin_expect(x, expected_value) (x)
macro_line|#endif
DECL|macro|__attribute_used__
mdefine_line|#define __attribute_used__&t;__attribute__((__unused__))
multiline_comment|/*&n; * The attribute `pure&squot; is not implemented in GCC versions earlier&n; * than 2.96.&n; */
macro_line|#if __GNUC_MINOR__ &gt;= 96
DECL|macro|__attribute_pure__
macro_line|# define __attribute_pure__&t;__attribute__((pure))
DECL|macro|__attribute_const__
macro_line|# define __attribute_const__&t;__attribute__((__const__))
macro_line|#endif
eof
