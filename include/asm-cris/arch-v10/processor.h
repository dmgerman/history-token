macro_line|#ifndef __ASM_CRIS_ARCH_PROCESSOR_H
DECL|macro|__ASM_CRIS_ARCH_PROCESSOR_H
mdefine_line|#define __ASM_CRIS_ARCH_PROCESSOR_H
multiline_comment|/*&n; * Default implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({void *pc; __asm__ (&quot;move.d $pc,%0&quot; : &quot;=rm&quot; (pc)); pc; })
multiline_comment|/* CRIS has no problems with write protection */
DECL|macro|wp_works_ok
mdefine_line|#define wp_works_ok 1
multiline_comment|/* CRIS thread_struct. this really has nothing to do with the processor itself, since&n; * CRIS does not do any hardware task-switching, but it&squot;s here for legacy reasons.&n; * The thread_struct here is used when task-switching using _resume defined in entry.S.&n; * The offsets here are hardcoded into _resume - if you change this struct, you need to&n; * change them as well!!!&n;*/
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|ksp
r_int
r_int
id|ksp
suffix:semicolon
multiline_comment|/* kernel stack pointer */
DECL|member|usp
r_int
r_int
id|usp
suffix:semicolon
multiline_comment|/* user stack pointer */
DECL|member|dccr
r_int
r_int
id|dccr
suffix:semicolon
multiline_comment|/* saved flag register */
)brace
suffix:semicolon
multiline_comment|/*&n; * User space process size. This is hardcoded into a few places,&n; * so don&squot;t change it unless you know what you are doing.&n; */
macro_line|#ifdef CONFIG_CRIS_LOW_MAP
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE       (0x50000000UL)   /* 1.25 GB */
macro_line|#else
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE       (0xA0000000UL)   /* 2.56 GB */
macro_line|#endif
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD  { &bslash;&n;   0, 0, 0x20 }  /* ccr = int enable, nothing else */
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk)&t;&bslash;&n;({&t;&t;&t;&bslash;&n;&t;unsigned long eip = 0;   &bslash;&n;&t;unsigned long regs = (unsigned long)user_regs(tsk); &bslash;&n;&t;if (regs &gt; PAGE_SIZE &amp;&amp; &bslash;&n;&t;&t;virt_addr_valid(regs)) &bslash;&n;&t;eip = ((struct pt_regs *)regs)-&gt;irp; &bslash;&n;&t;eip; &bslash;&n;})
multiline_comment|/* give the thread a program location&n; * set user-mode (The &squot;U&squot; flag (User mode flag) is CCR/DCCR bit 8) &n; * switch user-stackpointer&n; */
DECL|macro|start_thread
mdefine_line|#define start_thread(regs, ip, usp) do { &bslash;&n;&t;set_fs(USER_DS);      &bslash;&n;&t;regs-&gt;irp = ip;       &bslash;&n;&t;regs-&gt;dccr |= 1 &lt;&lt; U_DCCR_BITNR; &bslash;&n;&t;wrusp(usp);           &bslash;&n;} while(0)
macro_line|#endif
eof
