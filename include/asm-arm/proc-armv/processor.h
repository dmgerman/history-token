multiline_comment|/*&n; *  linux/include/asm-arm/proc-armv/processor.h&n; *&n; *  Copyright (C) 1996-1999 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   20-09-1996&t;RMK&t;Created&n; *   26-09-1996&t;RMK&t;Added &squot;EXTRA_THREAD_STRUCT*&squot;&n; *   28-09-1996&t;RMK&t;Moved start_thread into the processor dependencies&n; *   09-09-1998&t;PJB&t;Delete redundant `wp_works_ok&squot;&n; *   30-05-1999&t;PJB&t;Save sl across context switches&n; *   31-07-1999&t;RMK&t;Added &squot;domain&squot; stuff&n; */
macro_line|#ifndef __ASM_PROC_PROCESSOR_H
DECL|macro|__ASM_PROC_PROCESSOR_H
mdefine_line|#define __ASM_PROC_PROCESSOR_H
macro_line|#include &lt;asm/proc/domain.h&gt;
DECL|macro|KERNEL_STACK_SIZE
mdefine_line|#define KERNEL_STACK_SIZE&t;PAGE_SIZE
DECL|macro|INIT_EXTRA_THREAD_INFO
mdefine_line|#define INIT_EXTRA_THREAD_INFO&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.cpu_domain&t;= domain_val(DOMAIN_USER, DOMAIN_CLIENT) |&t;&bslash;&n;&t;&t;&t;  domain_val(DOMAIN_KERNEL, DOMAIN_MANAGER) |&t;&bslash;&n;&t;&t;&t;  domain_val(DOMAIN_IO, DOMAIN_CLIENT)
DECL|macro|start_thread
mdefine_line|#define start_thread(regs,pc,sp)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long *stack = (unsigned long *)sp;&t;&t;&t;&bslash;&n;&t;set_fs(USER_DS);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;memzero(regs-&gt;uregs, sizeof(regs-&gt;uregs));&t;&t;&t;&bslash;&n;&t;if (current-&gt;personality &amp; ADDR_LIMIT_32BIT)&t;&t;&t;&bslash;&n;&t;&t;regs-&gt;ARM_cpsr = USR_MODE;&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;regs-&gt;ARM_cpsr = USR26_MODE;&t;&t;&t;&t;&bslash;&n;&t;if (elf_hwcap &amp; HWCAP_THUMB &amp;&amp; pc &amp; 1)&t;&t;&t;&t;&bslash;&n;&t;&t;regs-&gt;ARM_cpsr |= PSR_T_BIT;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;ARM_pc = pc &amp; ~1;&t;&t;/* pc */&t;&t;&t;&bslash;&n;&t;regs-&gt;ARM_sp = sp;&t;&t;/* sp */&t;&t;&t;&bslash;&n;&t;regs-&gt;ARM_r2 = stack[2];&t;/* r2 (envp) */&t;&t;&t;&bslash;&n;&t;regs-&gt;ARM_r1 = stack[1];&t;/* r1 (argv) */&t;&t;&t;&bslash;&n;&t;regs-&gt;ARM_r0 = stack[0];&t;/* r0 (argc) */&t;&t;&t;&bslash;&n;})
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk)&t;(((unsigned long *)(4096+(unsigned long)(tsk)-&gt;thread_info))[1019])
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk)&t;(((unsigned long *)(4096+(unsigned long)(tsk)-&gt;thread_info))[1017])
macro_line|#endif
eof
