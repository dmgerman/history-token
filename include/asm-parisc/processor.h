multiline_comment|/*&n; * include/asm-parisc/processor.h&n; *&n; * Copyright (C) 1994 Linus Torvalds&n; */
macro_line|#ifndef __ASM_PARISC_PROCESSOR_H
DECL|macro|__ASM_PARISC_PROCESSOR_H
mdefine_line|#define __ASM_PARISC_PROCESSOR_H
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pdc.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/*&n; * Default implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
multiline_comment|/* We cannot use MFIA as it was added for PA2.0 - prumpf&n;&n;   At one point there were no &quot;0f/0b&quot; type local symbols in gas for&n;   PA-RISC.  This is no longer true, but this still seems like the&n;   nicest way to implement this. */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({ void *pc; __asm__(&quot;&bslash;n&bslash;tblr 0,%0&bslash;n&bslash;tnop&quot;:&quot;=r&quot; (pc)); pc; })
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;    (PAGE_OFFSET)
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE  (TASK_SIZE / 3)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n;** Data detected about CPUs at boot time which is the same for all CPU&squot;s.&n;** HP boxes are SMP - ie identical processors.&n;**&n;** FIXME: some CPU rev info may be processor specific...&n;*/
DECL|struct|system_cpuinfo_parisc
r_struct
id|system_cpuinfo_parisc
(brace
DECL|member|cpu_count
r_int
r_int
id|cpu_count
suffix:semicolon
DECL|member|cpu_hz
r_int
r_int
id|cpu_hz
suffix:semicolon
DECL|member|hversion
r_int
r_int
id|hversion
suffix:semicolon
DECL|member|sversion
r_int
r_int
id|sversion
suffix:semicolon
DECL|member|cpu_type
r_enum
id|cpu_type
id|cpu_type
suffix:semicolon
r_struct
(brace
DECL|member|model
r_struct
id|pdc_model
id|model
suffix:semicolon
DECL|member|versions
r_struct
id|pdc_model_cpuid
multiline_comment|/* ARGH */
id|versions
suffix:semicolon
DECL|member|cpuid
r_struct
id|pdc_model_cpuid
id|cpuid
suffix:semicolon
macro_line|#if 0
r_struct
id|pdc_model_caps
id|caps
suffix:semicolon
macro_line|#endif
DECL|member|sys_model_name
r_char
id|sys_model_name
(braket
l_int|81
)braket
suffix:semicolon
multiline_comment|/* PDC-ROM returnes this model name */
DECL|member|pdc
)brace
id|pdc
suffix:semicolon
DECL|member|model_name
r_char
op_star
id|model_name
suffix:semicolon
DECL|member|cpu_name
r_char
op_star
id|cpu_name
suffix:semicolon
DECL|member|family_name
r_char
op_star
id|family_name
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n;** Per CPU data structure - ie varies per CPU.&n;*/
DECL|struct|cpuinfo_parisc
r_struct
id|cpuinfo_parisc
(brace
DECL|member|cpuid
r_int
id|cpuid
suffix:semicolon
DECL|member|region
r_struct
id|irq_region
op_star
id|region
suffix:semicolon
DECL|member|it_value
r_int
r_int
id|it_value
suffix:semicolon
multiline_comment|/* Interval Timer value at last timer interrupt */
DECL|member|it_delta
r_int
r_int
id|it_delta
suffix:semicolon
multiline_comment|/* Interval Timer delta (tic_10ms / HZ * 100) */
DECL|member|hpa
r_int
r_int
id|hpa
suffix:semicolon
multiline_comment|/* Host Physical address */
DECL|member|txn_addr
r_int
r_int
id|txn_addr
suffix:semicolon
multiline_comment|/* External Interrupt Register or id_eid */
DECL|member|bh_count
r_int
r_int
id|bh_count
suffix:semicolon
multiline_comment|/* number of times bh was invoked */
DECL|member|irq_count
r_int
r_int
id|irq_count
suffix:semicolon
multiline_comment|/* number of IRQ&squot;s since boot */
DECL|member|irq_max_cr16
r_int
r_int
id|irq_max_cr16
suffix:semicolon
multiline_comment|/* longest time to handle a single IRQ */
)brace
suffix:semicolon
r_extern
r_struct
id|system_cpuinfo_parisc
id|boot_cpu_data
suffix:semicolon
r_extern
r_struct
id|cpuinfo_parisc
id|cpu_data
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|current_cpu_data
mdefine_line|#define current_cpu_data cpu_data[smp_processor_id()]
r_extern
r_void
id|identify_cpu
c_func
(paren
r_struct
id|cpuinfo_parisc
op_star
)paren
suffix:semicolon
DECL|macro|EISA_bus
mdefine_line|#define EISA_bus 0 /* we don&squot;t have ISA support yet */
DECL|macro|EISA_bus__is_a_macro
mdefine_line|#define EISA_bus__is_a_macro /* for versions in ksyms.c */
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
DECL|macro|MCA_bus__is_a_macro
mdefine_line|#define MCA_bus__is_a_macro /* for versions in ksyms.c */
r_typedef
r_struct
(brace
DECL|member|seg
r_int
id|seg
suffix:semicolon
DECL|typedef|mm_segment_t
)brace
id|mm_segment_t
suffix:semicolon
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|regs
r_struct
id|pt_regs
id|regs
suffix:semicolon
DECL|member|pg_tables
r_int
r_int
id|pg_tables
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Thread struct flags. */
DECL|macro|PARISC_KERNEL_DEATH
mdefine_line|#define PARISC_KERNEL_DEATH&t;(1UL &lt;&lt; 31)&t;/* see die_if_kernel()... */
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD { {&t;&t;&t;&bslash;&n;&t;{ 0, 0, 0, 0, 0, 0, 0, 0,&t;&bslash;&n;&t;  0, 0, 0, 0, 0, 0, 0, 0,&t;&bslash;&n;&t;  0, 0, 0, 0, 0, 0, 0, 0,&t;&bslash;&n;&t;  0, 0, 0, 0, 0, 0, 0, 0 },&t;&bslash;&n;&t;{ 0, 0, 0, 0, 0, 0, 0, 0,&t;&bslash;&n;&t;  0, 0, 0, 0, 0, 0, 0, 0,&t;&bslash;&n;&t;  0, 0, 0, 0, 0, 0, 0, 0,&t;&bslash;&n;&t;  0, 0, 0, 0, 0, 0, 0, 0 },&t;&bslash;&n;&t;{ 0, 0, 0, 0, 0, 0, 0, 0 },&t;&bslash;&n;&t;{ 0, 0}, { 0, 0}, 0, 0, 0, 0&t;&bslash;&n;&t;}, __pa((unsigned long) swapper_pg_dir) }
multiline_comment|/*&n; * Return saved PC of a blocked thread.  This is used by ps mostly.&n; */
DECL|function|thread_saved_pc
r_extern
r_inline
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
l_int|0xabcdef
suffix:semicolon
)brace
multiline_comment|/*&n; * Start user thread in another space.&n; *&n; * Note that we set both the iaoq and r31 to the new pc. When&n; * the kernel initially calls execve it will return through an&n; * rfi path that will use the values in the iaoq. The execve&n; * syscall path will return through the gateway page, and&n; * that uses r31 to branch to.&n; *&n; * For ELF we clear r23, because the dynamic linker uses it to pass&n; * the address of the finalizer function.&n; *&n; * We also initialize sr3 to an illegal value (illegal for our&n; * implementation, not for the architecture).&n; */
multiline_comment|/* The ELF abi wants things done a &quot;wee bit&quot; differently than&n; * som does.  Supporting this behavior here avoids&n; * having our own version of create_elf_tables.&n; *&n; * Oh, and yes, that is not a typo, we are really passing argc in r25&n; * and argv in r24 (rather than r26 and r25).  This is because that&squot;s&n; * where __libc_start_main wants them.&n; *&n; * Duplicated from dl-machine.h for the benefit of readers:&n; *&n; *  Our initial stack layout is rather different from everyone else&squot;s&n; *  due to the unique PA-RISC ABI.  As far as I know it looks like&n; *  this:&n;&n;   -----------------------------------  (user startup code creates this frame)&n;   |         32 bytes of magic       |&n;   |---------------------------------|&n;   | 32 bytes argument/sp save area  |&n;   |---------------------------------|  ((current-&gt;mm-&gt;env_end) + 63 &amp; ~63)&n;   |         N bytes of slack        |&n;   |---------------------------------|&n;   |      envvar and arg strings     |&n;   |---------------------------------|&n;   |&t;    ELF auxiliary info&t;     |&n;   |         (up to 28 words)        |&n;   |---------------------------------|&n;   |  Environment variable pointers  |&n;   |         upwards to NULL&t;     |&n;   |---------------------------------|&n;   |        Argument pointers        |&n;   |         upwards to NULL&t;     |&n;   |---------------------------------|&n;   |          argc (1 word)          |&n;   -----------------------------------&n;&n; *  The pleasant part of this is that if we need to skip arguments we&n; *  can just decrement argc and move argv, because the stack pointer&n; *  is utterly unrelated to the location of the environment and&n; *  argument vectors.&n; *&n; * Note that the S/390 people took the easy way out and hacked their&n; * GCC to make the stack grow downwards.  */
DECL|macro|start_thread_som
mdefine_line|#define start_thread_som(regs, new_pc, new_sp) do {&t;&t;&bslash;&n;&t;unsigned long *sp = (unsigned long *)new_sp;&t;&bslash;&n;&t;__u32 spaceid = (__u32)current-&gt;mm-&gt;context;&t;&bslash;&n;&t;unsigned long pc = (unsigned long)new_pc;&t;&bslash;&n;&t;/* offset pc for priv. level */&t;&t;&t;&bslash;&n;&t;pc |= 3;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;set_fs(USER_DS);&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;iasq[0] = spaceid;&t;&t;&t;&bslash;&n;&t;regs-&gt;iasq[1] = spaceid;&t;&t;&t;&bslash;&n;&t;regs-&gt;iaoq[0] = pc;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;iaoq[1] = pc;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;sr[2] = LINUX_GATEWAY_SPACE;              &bslash;&n;&t;regs-&gt;sr[3] = 0xffff;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;sr[4] = spaceid;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;sr[5] = spaceid;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;sr[6] = spaceid;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;sr[7] = spaceid;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;gr[ 0] = USER_INIT_PSW;&t;&t;&t;&bslash;&n;&t;regs-&gt;gr[30] = ((new_sp)+63)&amp;~63;&t;&t;&bslash;&n;&t;regs-&gt;gr[31] = pc;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;get_user(regs-&gt;gr[26],&amp;sp[0]);&t;&t;&t;&bslash;&n;&t;get_user(regs-&gt;gr[25],&amp;sp[-1]); &t;&t;&bslash;&n;&t;get_user(regs-&gt;gr[24],&amp;sp[-2]); &t;&t;&bslash;&n;&t;get_user(regs-&gt;gr[23],&amp;sp[-3]); &t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;cr30 = (u32) current;&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|start_thread
mdefine_line|#define start_thread(regs, new_pc, new_sp) do {&t;&t;&bslash;&n;&t;unsigned long *sp = (unsigned long *)new_sp;&t;&bslash;&n;&t;__u32 spaceid = (__u32)current-&gt;mm-&gt;context;&t;&bslash;&n;        unsigned long pc = (unsigned long)new_pc;       &bslash;&n;        /* offset pc for priv. level */                 &bslash;&n;        pc |= 3;                                        &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;set_fs(USER_DS);&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;iasq[0] = spaceid;&t;&t;&t;&bslash;&n;&t;regs-&gt;iasq[1] = spaceid;&t;&t;&t;&bslash;&n;&t;regs-&gt;iaoq[0] = pc;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;iaoq[1] = pc; &t;               &t;&t;&bslash;&n;&t;regs-&gt;sr[2] = LINUX_GATEWAY_SPACE;              &bslash;&n;&t;regs-&gt;sr[3] = 0xffff;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;sr[4] = spaceid;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;sr[5] = spaceid;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;sr[6] = spaceid;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;sr[7] = spaceid;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;gr[ 0] = USER_INIT_PSW;&t;&t;&t;&bslash;&n;&t;regs-&gt;fr[ 0] = 0LL;                            &t;&bslash;&n;&t;regs-&gt;fr[ 1] = 0LL;                            &t;&bslash;&n;&t;regs-&gt;fr[ 2] = 0LL;                            &t;&bslash;&n;&t;regs-&gt;fr[ 3] = 0LL;                            &t;&bslash;&n;&t;regs-&gt;gr[30] = ((current-&gt;mm-&gt;env_end)+63)&amp;~63;&t;&bslash;&n;&t;regs-&gt;gr[31] = pc;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;get_user(regs-&gt;gr[25],&amp;sp[0]);&t;&t;&t;&bslash;&n;&t;regs-&gt;gr[24] = (unsigned long) &amp;sp[1];&t;&t;&bslash;&n;&t;regs-&gt;gr[23] = 0;                            &t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;cr30 = (u32) current;&t;&t;&t;&bslash;&n;} while(0)
macro_line|#ifdef __LP64__
multiline_comment|/*&n; * For 64 bit kernels we need a version of start thread for 32 bit&n; * elf files.&n; *&n; * FIXME: It should be possible to not duplicate the above code&n; *        by playing games with concatenation to form both&n; *        macros at compile time. The only difference between&n; *        this macro and the above is the name and the types&n; *        for sp and pc.&n; */
DECL|macro|start_thread32
mdefine_line|#define start_thread32(regs, new_pc, new_sp) do {         &bslash;&n;&t;__u32 *sp = (__u32 *)new_sp;                    &bslash;&n;&t;__u32 spaceid = (__u32)current-&gt;mm-&gt;context;&t;&bslash;&n;&t;__u32 pc = (__u32)new_pc;                       &bslash;&n;        /* offset pc for priv. level */                 &bslash;&n;        pc |= 3;                                        &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;set_fs(USER_DS);&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;iasq[0] = spaceid;&t;&t;&t;&bslash;&n;&t;regs-&gt;iasq[1] = spaceid;&t;&t;&t;&bslash;&n;&t;regs-&gt;iaoq[0] = pc;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;iaoq[1] = pc; &t;               &t;&t;&bslash;&n;&t;regs-&gt;sr[2] = LINUX_GATEWAY_SPACE;              &bslash;&n;&t;regs-&gt;sr[3] = 0xffff;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;sr[4] = spaceid;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;sr[5] = spaceid;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;sr[6] = spaceid;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;sr[7] = spaceid;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;gr[ 0] = USER_INIT_PSW;&t;&t;&t;&bslash;&n;&t;regs-&gt;fr[ 0] = 0LL;                            &t;&bslash;&n;&t;regs-&gt;fr[ 1] = 0LL;                            &t;&bslash;&n;&t;regs-&gt;fr[ 2] = 0LL;                            &t;&bslash;&n;&t;regs-&gt;fr[ 3] = 0LL;                            &t;&bslash;&n;&t;regs-&gt;gr[30] = ((current-&gt;mm-&gt;env_end)+63)&amp;~63;&t;&bslash;&n;&t;regs-&gt;gr[31] = pc;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;get_user(regs-&gt;gr[25],&amp;sp[0]);&t;&t;&t;&bslash;&n;&t;regs-&gt;gr[24] = (unsigned long) &amp;sp[1];&t;&t;&bslash;&n;&t;regs-&gt;gr[23] = 0;                            &t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;cr30 = (u32) current;&t;&t;&t;&bslash;&n;} while(0)
macro_line|#endif
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
DECL|macro|copy_segments
mdefine_line|#define copy_segments(tsk, mm)&t;do { } while (0)
DECL|macro|release_segments
mdefine_line|#define release_segments(mm)&t;do { } while (0)
DECL|function|get_wchan
r_extern
r_inline
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
(brace
r_return
l_int|0xdeadbeef
suffix:semicolon
multiline_comment|/* XXX */
)brace
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk)&t;(0xdeadbeef)
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk)&t;(0xdeadbeef)
multiline_comment|/* Be sure to hunt all references to this down when you change the size of&n; * the kernel stack */
macro_line|#endif /* __ASSEMBLY__ */
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE&t;(4*PAGE_SIZE)
DECL|macro|alloc_task_struct
mdefine_line|#define alloc_task_struct() &bslash;&n;&t;((struct task_struct *) __get_free_pages(GFP_KERNEL,2))
DECL|macro|free_task_struct
mdefine_line|#define free_task_struct(p)     free_pages((unsigned long)(p),2)
DECL|macro|get_task_struct
mdefine_line|#define get_task_struct(tsk)      atomic_inc(&amp;virt_to_page(tsk)-&gt;count)
DECL|macro|init_task
mdefine_line|#define init_task (init_task_union.task) 
DECL|macro|init_stack
mdefine_line|#define init_stack (init_task_union.stack)
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()&t;do { } while (0)
macro_line|#endif /* __ASM_PARISC_PROCESSOR_H */
eof
