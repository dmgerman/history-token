multiline_comment|/*&n; *  linux/include/asm-arm/proc-armv/processor.h&n; *&n; *  Copyright (C) 1996-1999 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   20-09-1996&t;RMK&t;Created&n; *   26-09-1996&t;RMK&t;Added &squot;EXTRA_THREAD_STRUCT*&squot;&n; *   28-09-1996&t;RMK&t;Moved start_thread into the processor dependencies&n; *   09-09-1998&t;PJB&t;Delete redundant `wp_works_ok&squot;&n; *   30-05-1999&t;PJB&t;Save sl across context switches&n; *   31-07-1999&t;RMK&t;Added &squot;domain&squot; stuff&n; */
macro_line|#ifndef __ASM_PROC_PROCESSOR_H
DECL|macro|__ASM_PROC_PROCESSOR_H
mdefine_line|#define __ASM_PROC_PROCESSOR_H
macro_line|#include &lt;asm/proc/domain.h&gt;
macro_line|#include &lt;asm/proc/ptrace.h&gt;
DECL|macro|KERNEL_STACK_SIZE
mdefine_line|#define KERNEL_STACK_SIZE&t;PAGE_SIZE
DECL|struct|cpu_context_save
r_struct
id|cpu_context_save
(brace
DECL|member|cpsr
r_int
r_int
id|cpsr
suffix:semicolon
DECL|member|r4
r_int
r_int
id|r4
suffix:semicolon
DECL|member|r5
r_int
r_int
id|r5
suffix:semicolon
DECL|member|r6
r_int
r_int
id|r6
suffix:semicolon
DECL|member|r7
r_int
r_int
id|r7
suffix:semicolon
DECL|member|r8
r_int
r_int
id|r8
suffix:semicolon
DECL|member|r9
r_int
r_int
id|r9
suffix:semicolon
DECL|member|sl
r_int
r_int
id|sl
suffix:semicolon
DECL|member|fp
r_int
r_int
id|fp
suffix:semicolon
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
)brace
suffix:semicolon
DECL|function|init_pc_psr
r_static
r_inline
r_void
id|init_pc_psr
c_func
(paren
r_struct
id|cpu_context_save
op_star
id|s
comma
r_void
op_star
id|fn
)paren
(brace
id|s-&gt;pc
op_assign
(paren
r_int
r_int
)paren
id|fn
suffix:semicolon
id|s-&gt;cpsr
op_assign
id|PSR_I_BIT
op_or
id|SVC_MODE
suffix:semicolon
)brace
DECL|macro|INIT_EXTRA_THREAD_INFO
mdefine_line|#define INIT_EXTRA_THREAD_INFO&t;&t;&t;&t;&t;&t;&bslash;&n;&t;cpu_domain:&t;  domain_val(DOMAIN_USER, DOMAIN_CLIENT) |&t;&bslash;&n;&t;&t;&t;  domain_val(DOMAIN_KERNEL, DOMAIN_MANAGER) |&t;&bslash;&n;&t;&t;&t;  domain_val(DOMAIN_IO, DOMAIN_CLIENT)
DECL|macro|start_thread
mdefine_line|#define start_thread(regs,pc,sp)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long *stack = (unsigned long *)sp;&t;&t;&t;&bslash;&n;&t;set_fs(USER_DS);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;memzero(regs-&gt;uregs, sizeof(regs-&gt;uregs));&t;&t;&t;&bslash;&n;&t;if (current-&gt;personality &amp; ADDR_LIMIT_32BIT)&t;&t;&t;&bslash;&n;&t;&t;regs-&gt;ARM_cpsr = USR_MODE;&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;regs-&gt;ARM_cpsr = USR26_MODE;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;ARM_pc = pc;&t;&t;/* pc */&t;&t;&t;&bslash;&n;&t;regs-&gt;ARM_sp = sp;&t;&t;/* sp */&t;&t;&t;&bslash;&n;&t;regs-&gt;ARM_r2 = stack[2];&t;/* r2 (envp) */&t;&t;&t;&bslash;&n;&t;regs-&gt;ARM_r1 = stack[1];&t;/* r1 (argv) */&t;&t;&t;&bslash;&n;&t;regs-&gt;ARM_r0 = stack[0];&t;/* r0 (argc) */&t;&t;&t;&bslash;&n;})
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk)&t;(((unsigned long *)(4096+(unsigned long)(tsk)))[1021])
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk)&t;(((unsigned long *)(4096+(unsigned long)(tsk)))[1019])
macro_line|#endif
eof
