multiline_comment|/*&n; * include/asm-x86_64/i387.h&n; *&n; * Copyright (C) 1994 Linus Torvalds&n; *&n; * Pentium III FXSR, SSE support&n; * General FPU state handling cleanups&n; *&t;Gareth Hughes &lt;gareth@valinux.com&gt;, May 2000&n; * x86-64 work by Andi Kleen 2002&n; */
macro_line|#ifndef __ASM_X86_64_I387_H
DECL|macro|__ASM_X86_64_I387_H
mdefine_line|#define __ASM_X86_64_I387_H
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/sigcontext.h&gt;
macro_line|#include &lt;asm/user.h&gt;
macro_line|#include &lt;asm/thread_info.h&gt;
r_extern
r_void
id|fpu_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|init_fpu
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|save_i387
c_func
(paren
r_struct
id|_fpstate
op_star
id|buf
)paren
suffix:semicolon
DECL|function|need_signal_i387
r_static
r_inline
r_int
id|need_signal_i387
c_func
(paren
r_struct
id|task_struct
op_star
id|me
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|me-&gt;used_math
)paren
r_return
l_int|0
suffix:semicolon
id|me-&gt;used_math
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_thread_flag
c_func
(paren
id|TIF_USEDFPU
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * FPU lazy state save handling...&n; */
DECL|macro|kernel_fpu_end
mdefine_line|#define kernel_fpu_end() stts()
DECL|macro|unlazy_fpu
mdefine_line|#define unlazy_fpu(tsk) do { &bslash;&n;&t;if (test_tsk_thread_flag(tsk, TIF_USEDFPU)) &bslash;&n;&t;&t;save_init_fpu(tsk); &bslash;&n;} while (0)
DECL|macro|unlazy_current_fpu
mdefine_line|#define unlazy_current_fpu() do { &bslash;&n;&t;if (test_thread_flag(TIF_USEDFPU)) &bslash;&n;&t;&t;save_init_fpu(tsk); &bslash;&n;} while (0)
DECL|macro|clear_fpu
mdefine_line|#define clear_fpu(tsk) do { &bslash;&n;&t;if (test_tsk_thread_flag(tsk, TIF_USEDFPU)) {&t;&t;&bslash;&n;&t;&t;asm volatile(&quot;fwait&quot;);&t;&t;&t;&t;&bslash;&n;&t;&t;clear_tsk_thread_flag(tsk,TIF_USEDFPU); &t;&bslash;&n;&t;&t;stts();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|load_mxcsr
mdefine_line|#define load_mxcsr(val) do { &bslash;&n;&t;&t;unsigned long __mxcsr = ((unsigned long)(val) &amp; 0xffbf); &bslash;&n;&t;&t;asm volatile(&quot;ldmxcsr %0&quot; : : &quot;m&quot; (__mxcsr)); &bslash;&n;} while (0)
multiline_comment|/*&n; * ptrace request handers...&n; */
r_extern
r_int
id|get_fpregs
c_func
(paren
r_struct
id|user_i387_struct
op_star
id|buf
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
r_extern
r_int
id|set_fpregs
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|user_i387_struct
op_star
id|buf
)paren
suffix:semicolon
multiline_comment|/*&n; * i387 state interaction&n; */
DECL|macro|get_fpu_mxcsr
mdefine_line|#define get_fpu_mxcsr(t) ((t)-&gt;thread.i387.fxsave.mxcsr)
DECL|macro|get_fpu_cwd
mdefine_line|#define get_fpu_cwd(t) ((t)-&gt;thread.i387.fxsave.cwd)
DECL|macro|get_fpu_fxsr_twd
mdefine_line|#define get_fpu_fxsr_twd(t) ((t)-&gt;thread.i387.fxsave.twd)
DECL|macro|get_fpu_swd
mdefine_line|#define get_fpu_swd(t) ((t)-&gt;thread.i387.fxsave.swd)
DECL|macro|set_fpu_cwd
mdefine_line|#define set_fpu_cwd(t,val) ((t)-&gt;thread.i387.fxsave.cwd = (val))
DECL|macro|set_fpu_swd
mdefine_line|#define set_fpu_swd(t,val) ((t)-&gt;thread.i387.fxsave.swd = (val))
DECL|macro|set_fpu_fxsr_twd
mdefine_line|#define set_fpu_fxsr_twd(t,val) ((t)-&gt;thread.i387.fxsave.twd = (val))
DECL|macro|set_fpu_mxcsr
mdefine_line|#define set_fpu_mxcsr(t,val) ((t)-&gt;thread.i387.fxsave.mxcsr = (val)&amp;0xffbf)
DECL|function|restore_fpu_checking
r_static
r_inline
r_int
id|restore_fpu_checking
c_func
(paren
r_struct
id|i387_fxsave_struct
op_star
id|fx
)paren
(brace
r_int
id|err
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;1:  rex64 ; fxrstor (%[fx])&bslash;n&bslash;t&quot;
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;3:  movl $-1,%[err]&bslash;n&quot;
l_string|&quot;    jmp  2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 8&bslash;n&quot;
l_string|&quot;   .quad  1b,3b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
(braket
id|err
)braket
l_string|&quot;=r&quot;
(paren
id|err
)paren
suffix:colon
(braket
id|fx
)braket
l_string|&quot;r&quot;
(paren
id|fx
)paren
comma
l_string|&quot;0&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|save_i387_checking
r_static
r_inline
r_int
id|save_i387_checking
c_func
(paren
r_struct
id|i387_fxsave_struct
op_star
id|fx
)paren
(brace
r_int
id|err
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;1:  rex64 ; fxsave (%[fx])&bslash;n&bslash;t&quot;
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;3:  movl $-1,%[err]&bslash;n&quot;
l_string|&quot;    jmp  2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 8&bslash;n&quot;
l_string|&quot;   .quad  1b,3b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
(braket
id|err
)braket
l_string|&quot;=r&quot;
(paren
id|err
)paren
suffix:colon
(braket
id|fx
)braket
l_string|&quot;r&quot;
(paren
id|fx
)paren
comma
l_string|&quot;0&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|kernel_fpu_begin
r_static
r_inline
r_void
id|kernel_fpu_begin
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|me
op_assign
id|current
suffix:semicolon
r_if
c_cond
(paren
id|test_tsk_thread_flag
c_func
(paren
id|me
comma
id|TIF_USEDFPU
)paren
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;fxsave %0 ; fnclex&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|me-&gt;thread.i387.fxsave
)paren
)paren
suffix:semicolon
id|clear_tsk_thread_flag
c_func
(paren
id|me
comma
id|TIF_USEDFPU
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|clts
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|save_init_fpu
r_static
r_inline
r_void
id|save_init_fpu
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;fxsave %0 ; fnclex&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|tsk-&gt;thread.i387.fxsave
)paren
)paren
suffix:semicolon
id|clear_tsk_thread_flag
c_func
(paren
id|tsk
comma
id|TIF_USEDFPU
)paren
suffix:semicolon
id|stts
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; * This restores directly out of user space. Exceptions are handled.&n; */
DECL|function|restore_i387
r_static
r_inline
r_int
id|restore_i387
c_func
(paren
r_struct
id|_fpstate
op_star
id|buf
)paren
(brace
r_return
id|restore_fpu_checking
c_func
(paren
(paren
r_struct
id|i387_fxsave_struct
op_star
)paren
id|buf
)paren
suffix:semicolon
)brace
DECL|function|empty_fpu
r_static
r_inline
r_void
id|empty_fpu
c_func
(paren
r_struct
id|task_struct
op_star
id|child
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|child-&gt;used_math
)paren
(brace
multiline_comment|/* Simulate an empty FPU. */
id|memset
c_func
(paren
op_amp
id|child-&gt;thread.i387.fxsave
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|i387_fxsave_struct
)paren
)paren
suffix:semicolon
id|child-&gt;thread.i387.fxsave.cwd
op_assign
l_int|0x037f
suffix:semicolon
id|child-&gt;thread.i387.fxsave.swd
op_assign
l_int|0
suffix:semicolon
id|child-&gt;thread.i387.fxsave.twd
op_assign
l_int|0
suffix:semicolon
id|child-&gt;thread.i387.fxsave.mxcsr
op_assign
l_int|0x1f80
suffix:semicolon
)brace
id|child-&gt;used_math
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#endif /* __ASM_X86_64_I387_H */
eof
