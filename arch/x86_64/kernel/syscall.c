multiline_comment|/* System call table for x86-64. */
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/sys.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
DECL|macro|__NO_STUBS
mdefine_line|#define __NO_STUBS
DECL|macro|__SYSCALL
mdefine_line|#define __SYSCALL(nr, sym) extern asmlinkage void sym(void) ; 
DECL|macro|_ASM_X86_64_UNISTD_H_
macro_line|#undef _ASM_X86_64_UNISTD_H_
macro_line|#include &lt;asm-x86_64/unistd.h&gt;
DECL|macro|__SYSCALL
macro_line|#undef __SYSCALL
DECL|macro|__SYSCALL
mdefine_line|#define __SYSCALL(nr, sym) [ nr ] = sym, 
DECL|macro|_ASM_X86_64_UNISTD_H_
macro_line|#undef _ASM_X86_64_UNISTD_H_
DECL|typedef|sys_call_ptr_t
r_typedef
r_void
(paren
op_star
id|sys_call_ptr_t
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sys_ni_syscall
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|__cacheline_aligned
id|sys_call_ptr_t
id|sys_call_table
(braket
id|__NR_syscall_max
op_plus
l_int|1
)braket
id|__cacheline_aligned
op_assign
(brace
multiline_comment|/* Smells like a like a compiler bug -- it doesn&squot;t work when the &amp; below is removed. */
(braket
l_int|0
dot
dot
dot
id|__NR_syscall_max
)braket
op_assign
op_amp
id|sys_ni_syscall
comma
macro_line|#include &lt;asm-x86_64/unistd.h&gt;
)brace
suffix:semicolon
eof
