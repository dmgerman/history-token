multiline_comment|/*&n; *  include/asm-s390/processor.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Hartmut Penner (hp@de.ibm.com),&n; *               Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; *  Derived from &quot;include/asm-i386/processor.h&quot;&n; *    Copyright (C) 1994, Linus Torvalds&n; */
macro_line|#ifndef __ASM_S390_PROCESSOR_H
DECL|macro|__ASM_S390_PROCESSOR_H
mdefine_line|#define __ASM_S390_PROCESSOR_H
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Default implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({ void *pc; __asm__(&quot;basr %0,0&quot;:&quot;=a&quot;(pc)); pc; })
multiline_comment|/*&n; *  CPU type and hardware bug flags. Kept separately for each CPU.&n; *  Members of this structure are referenced in head.S, so think twice&n; *  before touching them. [mj]&n; */
r_typedef
r_struct
(brace
DECL|member|version
r_int
r_int
id|version
suffix:colon
l_int|8
suffix:semicolon
DECL|member|ident
r_int
r_int
id|ident
suffix:colon
l_int|24
suffix:semicolon
DECL|member|machine
r_int
r_int
id|machine
suffix:colon
l_int|16
suffix:semicolon
DECL|member|unused
r_int
r_int
id|unused
suffix:colon
l_int|16
suffix:semicolon
DECL|typedef|cpuid_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|cpuid_t
suffix:semicolon
DECL|struct|cpuinfo_S390
r_struct
id|cpuinfo_S390
(brace
DECL|member|cpu_id
id|cpuid_t
id|cpu_id
suffix:semicolon
DECL|member|cpu_addr
id|__u16
id|cpu_addr
suffix:semicolon
DECL|member|cpu_nr
id|__u16
id|cpu_nr
suffix:semicolon
DECL|member|loops_per_jiffy
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
DECL|member|pgd_quick
r_int
r_int
op_star
id|pgd_quick
suffix:semicolon
DECL|member|pte_quick
r_int
r_int
op_star
id|pte_quick
suffix:semicolon
DECL|member|pgtable_cache_sz
r_int
r_int
id|pgtable_cache_sz
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|print_cpu_info
c_func
(paren
r_struct
id|cpuinfo_S390
op_star
)paren
suffix:semicolon
multiline_comment|/* Lazy FPU handling on uni-processor */
r_extern
r_struct
id|task_struct
op_star
id|last_task_used_math
suffix:semicolon
multiline_comment|/*&n; * User space process size: 2GB (default).&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE       (0x80000000)
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE      (TASK_SIZE / 2)
r_typedef
r_struct
(brace
DECL|member|ar4
id|__u32
id|ar4
suffix:semicolon
DECL|typedef|mm_segment_t
)brace
id|mm_segment_t
suffix:semicolon
multiline_comment|/* if you change the thread_struct structure, you must&n; * update the _TSS_* defines in entry.S&n; */
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|fp_regs
id|s390_fp_regs
id|fp_regs
suffix:semicolon
DECL|member|ar2
id|__u32
id|ar2
suffix:semicolon
multiline_comment|/* kernel access register 2         */
DECL|member|ar4
id|__u32
id|ar4
suffix:semicolon
multiline_comment|/* kernel access register 4         */
DECL|member|ksp
id|__u32
id|ksp
suffix:semicolon
multiline_comment|/* kernel stack pointer             */
DECL|member|user_seg
id|__u32
id|user_seg
suffix:semicolon
multiline_comment|/* HSTD                             */
DECL|member|error_code
id|__u32
id|error_code
suffix:semicolon
multiline_comment|/* error-code of last prog-excep.   */
DECL|member|prot_addr
id|__u32
id|prot_addr
suffix:semicolon
multiline_comment|/* address of protection-excep.     */
DECL|member|trap_no
id|__u32
id|trap_no
suffix:semicolon
DECL|member|per_info
id|per_struct
id|per_info
suffix:semicolon
multiline_comment|/* Must be aligned on an 4 byte boundary*/
multiline_comment|/* Used to give failing instruction back to user for ieee exceptions */
DECL|member|ieee_instruction_pointer
id|addr_t
id|ieee_instruction_pointer
suffix:semicolon
multiline_comment|/* pfault_wait is used to block the process on a pfault event */
DECL|member|pfault_wait
id|addr_t
id|pfault_wait
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|thread_struct
r_typedef
r_struct
id|thread_struct
id|thread_struct
suffix:semicolon
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD {{0,{{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}, &bslash;&n;&t;&t;&t;    {0},{0},{0},{0},{0},{0}}},            &bslash;&n;                     0, 0,                                        &bslash;&n;                    sizeof(init_stack) + (__u32) &amp;init_stack,     &bslash;&n;              (__pa((__u32) &amp;swapper_pg_dir[0]) + _SEGMENT_TABLE),&bslash;&n;                     0,0,0,                                       &bslash;&n;                     (per_struct) {{{{0,}}},0,0,0,0,{{0,}}},      &bslash;&n;                     0, 0                                         &bslash;&n;}
multiline_comment|/* need to define ... */
DECL|macro|start_thread
mdefine_line|#define start_thread(regs, new_psw, new_stackp) do {            &bslash;&n;        regs-&gt;psw.mask  = _USER_PSW_MASK;                       &bslash;&n;        regs-&gt;psw.addr  = new_psw | 0x80000000;                 &bslash;&n;        regs-&gt;gprs[15]  = new_stackp ;                          &bslash;&n;} while (0)
multiline_comment|/* Forward declaration, a strange C thing */
r_struct
id|task_struct
suffix:semicolon
r_struct
id|mm_struct
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
multiline_comment|/* Copy and release all segment info associated with a VM */
DECL|macro|copy_segments
mdefine_line|#define copy_segments(nr, mm)           do { } while (0)
DECL|macro|release_segments
mdefine_line|#define release_segments(mm)            do { } while (0)
multiline_comment|/*&n; * Return saved PC of a blocked thread.&n; */
r_extern
r_int
r_int
id|thread_saved_pc
c_func
(paren
r_struct
id|task_struct
op_star
id|t
)paren
suffix:semicolon
multiline_comment|/*&n; * Print register of task into buffer. Used in fs/proc/array.c.&n; */
r_extern
r_char
op_star
id|task_show_regs
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_char
op_star
id|buffer
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
DECL|macro|__KSTK_PTREGS
mdefine_line|#define __KSTK_PTREGS(tsk) ((struct pt_regs *) &bslash;&n;        (((addr_t) tsk-&gt;thread_info + THREAD_SIZE - sizeof(struct pt_regs)) &amp; -8L))
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk)&t;(__KSTK_PTREGS(tsk)-&gt;psw.addr)
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk)&t;(__KSTK_PTREGS(tsk)-&gt;gprs[15])
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()&t;do { } while (0)
multiline_comment|/*&n; * Set of msr bits that gdb can change on behalf of a process.&n; */
multiline_comment|/* Only let our hackers near the condition codes */
DECL|macro|PSW_MASK_DEBUGCHANGE
mdefine_line|#define PSW_MASK_DEBUGCHANGE    0x00003000UL
multiline_comment|/* Don&squot;t let em near the addressing mode either */
DECL|macro|PSW_ADDR_DEBUGCHANGE
mdefine_line|#define PSW_ADDR_DEBUGCHANGE    0x7FFFFFFFUL
DECL|macro|PSW_ADDR_MASK
mdefine_line|#define PSW_ADDR_MASK           0x7FFFFFFFUL
multiline_comment|/* Program event recording mask */
DECL|macro|PSW_PER_MASK
mdefine_line|#define PSW_PER_MASK            0x40000000UL
DECL|macro|USER_STD_MASK
mdefine_line|#define USER_STD_MASK           0x00000080UL
DECL|macro|PSW_PROBLEM_STATE
mdefine_line|#define PSW_PROBLEM_STATE       0x00010000UL
multiline_comment|/*&n; * Set PSW mask to specified value, while leaving the&n; * PSW addr pointing to the next instruction.&n; */
DECL|function|__load_psw_mask
r_static
r_inline
r_void
id|__load_psw_mask
(paren
r_int
r_int
id|mask
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
id|psw_t
id|psw
suffix:semicolon
id|psw.mask
op_assign
id|mask
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;    basr %0,0&bslash;n&quot;
l_string|&quot;0:  ahi  %0,1f-0b&bslash;n&quot;
l_string|&quot;    st   %0,4(%1)&bslash;n&quot;
l_string|&quot;    lpsw 0(%1)&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|psw
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function to stop a processor until an interruption occured&n; */
DECL|function|enabled_wait
r_static
r_inline
r_void
id|enabled_wait
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|reg
suffix:semicolon
id|psw_t
id|wait_psw
suffix:semicolon
id|wait_psw.mask
op_assign
l_int|0x070e0000
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;    basr %0,0&bslash;n&quot;
l_string|&quot;0:  la   %0,1f-0b(%0)&bslash;n&quot;
l_string|&quot;    st   %0,4(%1)&bslash;n&quot;
l_string|&quot;    oi   4(%1),0x80&bslash;n&quot;
l_string|&quot;    lpsw 0(%1)&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=&amp;a&quot;
(paren
id|reg
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|wait_psw
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function to drop a processor into disabled wait state&n; */
DECL|function|disabled_wait
r_static
r_inline
r_void
id|disabled_wait
c_func
(paren
r_int
r_int
id|code
)paren
(brace
r_char
id|psw_buffer
(braket
l_int|2
op_star
r_sizeof
(paren
id|psw_t
)paren
)braket
suffix:semicolon
r_char
id|ctl_buf
(braket
l_int|4
)braket
suffix:semicolon
id|psw_t
op_star
id|dw_psw
op_assign
(paren
id|psw_t
op_star
)paren
(paren
(paren
(paren
r_int
r_int
)paren
op_amp
id|psw_buffer
op_plus
r_sizeof
(paren
id|psw_t
)paren
op_minus
l_int|1
)paren
op_amp
op_minus
r_sizeof
(paren
id|psw_t
)paren
)paren
suffix:semicolon
id|dw_psw-&gt;mask
op_assign
l_int|0x000a0000
suffix:semicolon
id|dw_psw-&gt;addr
op_assign
id|code
suffix:semicolon
multiline_comment|/* &n;         * Store status and then load disabled wait psw,&n;         * the processor is dead afterwards&n;         */
id|asm
r_volatile
(paren
l_string|&quot;    stctl 0,0,0(%1)&bslash;n&quot;
l_string|&quot;    ni    0(%1),0xef&bslash;n&quot;
multiline_comment|/* switch off protection */
l_string|&quot;    lctl  0,0,0(%1)&bslash;n&quot;
l_string|&quot;    stpt  0xd8&bslash;n&quot;
multiline_comment|/* store timer */
l_string|&quot;    stckc 0xe0&bslash;n&quot;
multiline_comment|/* store clock comparator */
l_string|&quot;    stpx  0x108&bslash;n&quot;
multiline_comment|/* store prefix register */
l_string|&quot;    stam  0,15,0x120&bslash;n&quot;
multiline_comment|/* store access registers */
l_string|&quot;    std   0,0x160&bslash;n&quot;
multiline_comment|/* store f0 */
l_string|&quot;    std   2,0x168&bslash;n&quot;
multiline_comment|/* store f2 */
l_string|&quot;    std   4,0x170&bslash;n&quot;
multiline_comment|/* store f4 */
l_string|&quot;    std   6,0x178&bslash;n&quot;
multiline_comment|/* store f6 */
l_string|&quot;    stm   0,15,0x180&bslash;n&quot;
multiline_comment|/* store general registers */
l_string|&quot;    stctl 0,15,0x1c0&bslash;n&quot;
multiline_comment|/* store control registers */
l_string|&quot;    oi    0(%1),0x10&bslash;n&quot;
multiline_comment|/* fake protection bit */
l_string|&quot;    lpsw 0(%0)&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|dw_psw
)paren
comma
l_string|&quot;a&quot;
(paren
op_amp
id|ctl_buf
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif                                 /* __ASM_S390_PROCESSOR_H           */
eof
