macro_line|#ifndef _X86_64_CURRENT_H
DECL|macro|_X86_64_CURRENT_H
mdefine_line|#define _X86_64_CURRENT_H
macro_line|#if !defined(__ASSEMBLY__) 
r_struct
id|task_struct
suffix:semicolon
macro_line|#include &lt;asm/pda.h&gt;
DECL|function|get_current
r_static
r_inline
r_struct
id|task_struct
op_star
id|get_current
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|t
op_assign
id|read_pda
c_func
(paren
id|pcurrent
)paren
suffix:semicolon
r_return
id|t
suffix:semicolon
)brace
DECL|macro|stack_current
mdefine_line|#define stack_current() &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct thread_info *ti;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__(&quot;andq %%rsp,%0; &quot;:&quot;=r&quot; (ti) : &quot;0&quot; (~8191UL));&t;&bslash;&n;&t;ti-&gt;task;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|current
mdefine_line|#define current get_current()
macro_line|#else
macro_line|#ifndef ASM_OFFSET_H
macro_line|#include &lt;asm/offset.h&gt; 
macro_line|#endif
DECL|macro|GET_CURRENT
mdefine_line|#define GET_CURRENT(reg) movq %gs:(pda_pcurrent),reg
macro_line|#endif
macro_line|#endif /* !(_X86_64_CURRENT_H) */
eof
