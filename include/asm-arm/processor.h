multiline_comment|/*&n; *  linux/include/asm-arm/processor.h&n; *&n; *  Copyright (C) 1995 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARM_PROCESSOR_H
DECL|macro|__ASM_ARM_PROCESSOR_H
mdefine_line|#define __ASM_ARM_PROCESSOR_H
multiline_comment|/*&n; * Default implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({ __label__ _l; _l: &amp;&amp;_l;})
DECL|macro|FP_SIZE
mdefine_line|#define FP_SIZE 35
DECL|struct|fp_hard_struct
r_struct
id|fp_hard_struct
(brace
DECL|member|save
r_int
r_int
id|save
(braket
id|FP_SIZE
)braket
suffix:semicolon
multiline_comment|/* as yet undefined */
)brace
suffix:semicolon
DECL|struct|fp_soft_struct
r_struct
id|fp_soft_struct
(brace
DECL|member|save
r_int
r_int
id|save
(braket
id|FP_SIZE
)braket
suffix:semicolon
multiline_comment|/* undefined information */
)brace
suffix:semicolon
DECL|union|fp_state
r_union
id|fp_state
(brace
DECL|member|hard
r_struct
id|fp_hard_struct
id|hard
suffix:semicolon
DECL|member|soft
r_struct
id|fp_soft_struct
id|soft
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|mm_segment_t
r_typedef
r_int
r_int
id|mm_segment_t
suffix:semicolon
multiline_comment|/* domain register&t;*/
macro_line|#ifdef __KERNEL__
DECL|macro|EISA_bus
mdefine_line|#define EISA_bus 0
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/arch/memory.h&gt;
macro_line|#include &lt;asm/proc/processor.h&gt;
DECL|struct|debug_info
r_struct
id|debug_info
(brace
DECL|member|nsaved
r_int
id|nsaved
suffix:semicolon
r_struct
(brace
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
DECL|member|insn
r_int
r_int
id|insn
suffix:semicolon
DECL|member|bp
)brace
id|bp
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|refcount
id|atomic_t
id|refcount
suffix:semicolon
multiline_comment|/* fault info&t;  */
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
DECL|member|trap_no
r_int
r_int
id|trap_no
suffix:semicolon
DECL|member|error_code
r_int
r_int
id|error_code
suffix:semicolon
multiline_comment|/* floating point */
DECL|member|fpstate
r_union
id|fp_state
id|fpstate
suffix:semicolon
multiline_comment|/* debugging&t;  */
DECL|member|debug
r_struct
id|debug_info
id|debug
suffix:semicolon
multiline_comment|/* context info&t;  */
DECL|member|save
r_struct
id|context_save_struct
op_star
id|save
suffix:semicolon
id|EXTRA_THREAD_STRUCT
)brace
suffix:semicolon
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP {&t;&t;&t;&t;&t;&bslash;&n;&t;vm_mm:&t;&t;&amp;init_mm,&t;&t;&t;&bslash;&n;&t;vm_page_prot:&t;PAGE_SHARED,&t;&t;&t;&bslash;&n;&t;vm_flags:&t;VM_READ | VM_WRITE | VM_EXEC,&t;&bslash;&n;&t;vm_avl_height:&t;1,&t;&t;&t;&t;&bslash;&n;}
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD  {&t;&t;&t;&t;&t;&bslash;&n;&t;refcount:&t;ATOMIC_INIT(1),&t;&t;&t;&bslash;&n;&t;EXTRA_THREAD_STRUCT_INIT&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; * Return saved PC of a blocked thread.&n; */
DECL|function|thread_saved_pc
r_extern
id|__inline__
r_int
r_int
id|thread_saved_pc
c_func
(paren
r_struct
id|thread_struct
op_star
id|t
)paren
(brace
r_return
id|t-&gt;save
ques
c_cond
id|pc_pointer
c_func
(paren
id|t-&gt;save-&gt;pc
)paren
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|get_css_fp
r_extern
id|__inline__
r_int
r_int
id|get_css_fp
c_func
(paren
r_struct
id|thread_struct
op_star
id|t
)paren
(brace
r_return
id|t-&gt;save
ques
c_cond
id|t-&gt;save-&gt;fp
suffix:colon
l_int|0
suffix:semicolon
)brace
id|asmlinkage
r_void
id|ret_from_sys_call
c_func
(paren
r_void
)paren
id|__asm__
c_func
(paren
l_string|&quot;ret_from_sys_call&quot;
)paren
suffix:semicolon
DECL|function|init_thread_css
r_extern
id|__inline__
r_void
id|init_thread_css
c_func
(paren
r_struct
id|context_save_struct
op_star
id|save
)paren
(brace
op_star
id|save
op_assign
id|INIT_CSS
suffix:semicolon
id|save-&gt;pc
op_or_assign
(paren
r_int
r_int
)paren
id|ret_from_sys_call
suffix:semicolon
)brace
multiline_comment|/* Forward declaration, a strange C thing */
r_struct
id|task_struct
suffix:semicolon
multiline_comment|/* Free all resources held by a thread. */
r_extern
r_void
id|release_thread
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
multiline_comment|/* Copy and release all segment info associated with a VM */
DECL|macro|copy_segments
mdefine_line|#define copy_segments(tsk, mm)&t;&t;do { } while (0)
DECL|macro|release_segments
mdefine_line|#define release_segments(mm)&t;&t;do { } while (0)
r_int
r_int
id|get_wchan
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
suffix:semicolon
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE&t;(8192)
r_extern
r_struct
id|task_struct
op_star
id|alloc_task_struct
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__free_task_struct
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
DECL|macro|get_task_struct
mdefine_line|#define get_task_struct(p)&t;atomic_inc(&amp;(p)-&gt;thread.refcount)
DECL|macro|free_task_struct
mdefine_line|#define free_task_struct(p)&t;&t;&t;&t;&t;&bslash;&n; do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (atomic_dec_and_test(&amp;(p)-&gt;thread.refcount))&t;&t;&bslash;&n;&t;&t;__free_task_struct((p));&t;&t;&t;&bslash;&n; } while (0)
DECL|macro|init_task
mdefine_line|#define init_task&t;(init_task_union.task)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;(init_task_union.stack)
multiline_comment|/*&n; * Create a new kernel thread&n; */
r_extern
r_int
id|kernel_thread
c_func
(paren
r_int
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|arg
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __ASM_ARM_PROCESSOR_H */
eof
