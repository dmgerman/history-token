multiline_comment|/*&n; *  linux/include/asm-arm26/processor.h&n; *&n; *  Copyright (C) 1995 Russell King&n; *  Copyright (C) 2003 Ian Molton&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARM_PROCESSOR_H
DECL|macro|__ASM_ARM_PROCESSOR_H
mdefine_line|#define __ASM_ARM_PROCESSOR_H
multiline_comment|/*&n; * Default implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({ __label__ _l; _l: &amp;&amp;_l;})
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;linux/string.h&gt;
DECL|macro|KERNEL_STACK_SIZE
mdefine_line|#define KERNEL_STACK_SIZE 4096
r_typedef
r_struct
(brace
DECL|member|put_byte
r_void
(paren
op_star
id|put_byte
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Special calling convention */
DECL|member|get_byte
r_void
(paren
op_star
id|get_byte
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Special calling convention */
DECL|member|put_half
r_void
(paren
op_star
id|put_half
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Special calling convention */
DECL|member|get_half
r_void
(paren
op_star
id|get_half
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Special calling convention */
DECL|member|put_word
r_void
(paren
op_star
id|put_word
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Special calling convention */
DECL|member|get_word
r_void
(paren
op_star
id|get_word
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Special calling convention */
DECL|member|put_dword
r_void
(paren
op_star
id|put_dword
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Special calling convention */
DECL|member|copy_from_user
r_int
r_int
(paren
op_star
id|copy_from_user
)paren
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
r_int
id|sz
)paren
suffix:semicolon
DECL|member|copy_to_user
r_int
r_int
(paren
op_star
id|copy_to_user
)paren
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
r_int
id|sz
)paren
suffix:semicolon
DECL|member|clear_user
r_int
r_int
(paren
op_star
id|clear_user
)paren
(paren
r_void
op_star
id|addr
comma
r_int
r_int
id|sz
)paren
suffix:semicolon
DECL|member|strncpy_from_user
r_int
r_int
(paren
op_star
id|strncpy_from_user
)paren
(paren
r_char
op_star
id|to
comma
r_const
r_char
op_star
id|from
comma
r_int
r_int
id|sz
)paren
suffix:semicolon
DECL|member|strnlen_user
r_int
r_int
(paren
op_star
id|strnlen_user
)paren
(paren
r_const
r_char
op_star
id|s
comma
r_int
id|n
)paren
suffix:semicolon
DECL|typedef|uaccess_t
)brace
id|uaccess_t
suffix:semicolon
r_extern
id|uaccess_t
id|uaccess_user
comma
id|uaccess_kernel
suffix:semicolon
DECL|macro|EXTRA_THREAD_STRUCT
mdefine_line|#define EXTRA_THREAD_STRUCT                     &bslash;&n;        uaccess_t       *uaccess;         /* User access functions*/
DECL|macro|EXTRA_THREAD_STRUCT_INIT
mdefine_line|#define EXTRA_THREAD_STRUCT_INIT                &bslash;&n;        .uaccess        = &amp;uaccess_kernel,
singleline_comment|// FIXME?!!
DECL|macro|start_thread
mdefine_line|#define start_thread(regs,pc,sp)                                        &bslash;&n;({                                                                      &bslash;&n;        unsigned long *stack = (unsigned long *)sp;                     &bslash;&n;        set_fs(USER_DS);                                                &bslash;&n;        memzero(regs-&gt;uregs, sizeof (regs-&gt;uregs));                     &bslash;&n;        regs-&gt;ARM_pc = pc | ~0xfc000003;        /* pc */                &bslash;&n;        regs-&gt;ARM_sp = sp;              /* sp */                        &bslash;&n;        regs-&gt;ARM_r2 = stack[2];        /* r2 (envp) */                 &bslash;&n;        regs-&gt;ARM_r1 = stack[1];        /* r1 (argv) */                 &bslash;&n;        regs-&gt;ARM_r0 = stack[0];        /* r0 (argc) */                 &bslash;&n;})
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk)   (((unsigned long *)(4096+(unsigned long)(tsk)))[1020])
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk)   (((unsigned long *)(4096+(unsigned long)(tsk)))[1018])
DECL|struct|debug_entry
r_struct
id|debug_entry
(brace
DECL|member|address
id|u32
id|address
suffix:semicolon
DECL|member|insn
id|u32
id|insn
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|debug_info
r_struct
id|debug_info
(brace
DECL|member|nsaved
r_int
id|nsaved
suffix:semicolon
DECL|member|bp
r_struct
id|debug_entry
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
multiline_comment|/* debugging&t;  */
DECL|member|debug
r_struct
id|debug_info
id|debug
suffix:semicolon
id|EXTRA_THREAD_STRUCT
)brace
suffix:semicolon
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD  { &bslash;&n;EXTRA_THREAD_STRUCT_INIT &bslash;&n;}
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
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()&t;&t;&t;barrier()
multiline_comment|/* Prepare to copy thread state - unlazy all lazy status */
DECL|macro|prepare_to_copy
mdefine_line|#define prepare_to_copy(tsk)    do { } while (0)
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
