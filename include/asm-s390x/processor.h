multiline_comment|/*&n; *  include/asm-s390/processor.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Hartmut Penner (hp@de.ibm.com),&n; *               Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; *  Derived from &quot;include/asm-i386/processor.h&quot;&n; *    Copyright (C) 1994, Linus Torvalds&n; */
macro_line|#ifndef __ASM_S390_PROCESSOR_H
DECL|macro|__ASM_S390_PROCESSOR_H
mdefine_line|#define __ASM_S390_PROCESSOR_H
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
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
DECL|member|pmd_quick
r_int
r_int
op_star
id|pmd_quick
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
DECL|member|cpu_addr
id|__u16
id|cpu_addr
suffix:semicolon
DECL|member|cpu_nr
id|__u16
id|cpu_nr
suffix:semicolon
DECL|member|pad
id|__u16
id|pad
(braket
l_int|2
)braket
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
DECL|macro|S390_FLAG_31BIT
mdefine_line|#define S390_FLAG_31BIT 0x01UL
multiline_comment|/*&n; * User space process size: 4TB (default).&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE       (0x40000000000UL)
DECL|macro|TASK31_SIZE
mdefine_line|#define TASK31_SIZE     (0x80000000UL)
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE      ((current-&gt;thread.flags &amp; S390_FLAG_31BIT) ? &bslash;&n;&t;(TASK31_SIZE / 2) : (TASK_SIZE / 2))
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE (4*PAGE_SIZE)
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
DECL|member|regs
r_struct
id|pt_regs
op_star
id|regs
suffix:semicolon
multiline_comment|/* the user registers can be found on*/
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
id|addr_t
id|ksp
suffix:semicolon
multiline_comment|/* kernel stack pointer             */
DECL|member|user_seg
id|addr_t
id|user_seg
suffix:semicolon
multiline_comment|/* HSTD                             */
DECL|member|prot_addr
id|addr_t
id|prot_addr
suffix:semicolon
multiline_comment|/* address of protection-excep.     */
DECL|member|error_code
id|__u32
id|error_code
suffix:semicolon
multiline_comment|/* error-code of last prog-excep.   */
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
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* various flags */
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
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP &bslash;&n;{ &amp;init_mm, 0, 0, NULL, PAGE_SHARED, &bslash;&n;VM_READ | VM_WRITE | VM_EXEC, 1, NULL,NULL }
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD { (struct pt_regs *) 0,                       &bslash;&n;                    { 0,{{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}, &bslash;&n;&t;&t;&t;    {0},{0},{0},{0},{0},{0}}},            &bslash;&n;                     0, 0,                                        &bslash;&n;                    sizeof(init_stack) + (addr_t) &amp;init_stack,    &bslash;&n;              (__pa((addr_t) &amp;swapper_pg_dir[0]) + _REGION_TABLE),&bslash;&n;                     0,0,0,                                       &bslash;&n;                     (per_struct) {{{{0,}}},0,0,0,0,{{0,}}},      &bslash;&n;&t;&t;     0, 0, 0&t;&t;&t;&t;          &bslash;&n;} 
multiline_comment|/* need to define ... */
DECL|macro|start_thread
mdefine_line|#define start_thread(regs, new_psw, new_stackp) do {            &bslash;&n;        regs-&gt;psw.mask  = _USER_PSW_MASK;                       &bslash;&n;        regs-&gt;psw.addr  = new_psw;                              &bslash;&n;        regs-&gt;gprs[15]  = new_stackp;                           &bslash;&n;} while (0)
DECL|macro|start_thread31
mdefine_line|#define start_thread31(regs, new_psw, new_stackp) do {          &bslash;&n;&t;regs-&gt;psw.mask  = _USER_PSW_MASK &amp; ~(1L &lt;&lt; 32);&t;&t;&bslash;&n;        regs-&gt;psw.addr  = new_psw;                              &bslash;&n;        regs-&gt;gprs[15]  = new_stackp;                           &bslash;&n;} while (0)
multiline_comment|/* Forward declaration, a strange C thing */
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
multiline_comment|/*&n; * Return saved PC of a blocked thread. used in kernel/sched&n; */
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
(paren
id|t-&gt;regs
)paren
ques
c_cond
(paren
(paren
r_int
r_int
)paren
id|t-&gt;regs-&gt;psw.addr
)paren
suffix:colon
l_int|0
suffix:semicolon
)brace
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
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk)   ((tsk)-&gt;thread.regs-&gt;psw.addr)
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk)   ((tsk)-&gt;thread.ksp)
multiline_comment|/* Allocation and freeing of basic task resources. */
multiline_comment|/*&n; * NOTE! The task struct and the stack go together&n; */
DECL|macro|alloc_task_struct
mdefine_line|#define alloc_task_struct() &bslash;&n;        ((struct task_struct *) __get_free_pages(GFP_KERNEL,2))
DECL|macro|free_task_struct
mdefine_line|#define free_task_struct(p)     free_pages((unsigned long)(p),2)
DECL|macro|get_task_struct
mdefine_line|#define get_task_struct(tsk)      atomic_inc(&amp;virt_to_page(tsk)-&gt;count)
DECL|macro|init_task
mdefine_line|#define init_task       (init_task_union.task)
DECL|macro|init_stack
mdefine_line|#define init_stack      (init_task_union.stack)
multiline_comment|/*&n; * Set of msr bits that gdb can change on behalf of a process.&n; */
multiline_comment|/* Only let our hackers near the condition codes */
DECL|macro|PSW_MASK_DEBUGCHANGE
mdefine_line|#define PSW_MASK_DEBUGCHANGE    0x0000300000000000UL
multiline_comment|/* Don&squot;t let em near the addressing mode either */
DECL|macro|PSW_ADDR_DEBUGCHANGE
mdefine_line|#define PSW_ADDR_DEBUGCHANGE    0xFFFFFFFFFFFFFFFFUL
DECL|macro|PSW_ADDR_MASK
mdefine_line|#define PSW_ADDR_MASK           0xFFFFFFFFFFFFFFFFUL
multiline_comment|/* Program event recording mask */
DECL|macro|PSW_PER_MASK
mdefine_line|#define PSW_PER_MASK            0x4000000000000000UL
DECL|macro|USER_STD_MASK
mdefine_line|#define USER_STD_MASK           0x0000000000000080UL
DECL|macro|PSW_PROBLEM_STATE
mdefine_line|#define PSW_PROBLEM_STATE       0x0001000000000000UL
multiline_comment|/*&n; * Function to drop a processor into disabled wait state&n; */
DECL|function|disabled_wait
r_static
r_inline
r_void
id|disabled_wait
c_func
(paren
id|addr_t
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
l_int|8
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
l_int|0x0002000180000000
suffix:semicolon
id|dw_psw-&gt;addr
op_assign
id|code
suffix:semicolon
multiline_comment|/* &n;         * Store status and then load disabled wait psw,&n;         * the processor is dead afterwards&n;         */
id|asm
r_volatile
(paren
l_string|&quot;    stctg 0,0,0(%1)&bslash;n&quot;
l_string|&quot;    ni    4(%1),0xef&bslash;n&quot;
multiline_comment|/* switch off protection */
l_string|&quot;    lctlg 0,0,0(%1)&bslash;n&quot;
l_string|&quot;    lghi  1,0x1000&bslash;n&quot;
l_string|&quot;    stpt  0x328(1)&bslash;n&quot;
multiline_comment|/* store timer */
l_string|&quot;    stckc 0x330(1)&bslash;n&quot;
multiline_comment|/* store clock comparator */
l_string|&quot;    stpx  0x318(1)&bslash;n&quot;
multiline_comment|/* store prefix register */
l_string|&quot;    stam  0,15,0x340(1)&bslash;n&quot;
multiline_comment|/* store access registers */
l_string|&quot;    stfpc 0x31c(1)&bslash;n&quot;
multiline_comment|/* store fpu control */
l_string|&quot;    std   0,0x200(1)&bslash;n&quot;
multiline_comment|/* store f0 */
l_string|&quot;    std   1,0x208(1)&bslash;n&quot;
multiline_comment|/* store f1 */
l_string|&quot;    std   2,0x210(1)&bslash;n&quot;
multiline_comment|/* store f2 */
l_string|&quot;    std   3,0x218(1)&bslash;n&quot;
multiline_comment|/* store f3 */
l_string|&quot;    std   4,0x220(1)&bslash;n&quot;
multiline_comment|/* store f4 */
l_string|&quot;    std   5,0x228(1)&bslash;n&quot;
multiline_comment|/* store f5 */
l_string|&quot;    std   6,0x230(1)&bslash;n&quot;
multiline_comment|/* store f6 */
l_string|&quot;    std   7,0x238(1)&bslash;n&quot;
multiline_comment|/* store f7 */
l_string|&quot;    std   8,0x240(1)&bslash;n&quot;
multiline_comment|/* store f8 */
l_string|&quot;    std   9,0x248(1)&bslash;n&quot;
multiline_comment|/* store f9 */
l_string|&quot;    std   10,0x250(1)&bslash;n&quot;
multiline_comment|/* store f10 */
l_string|&quot;    std   11,0x258(1)&bslash;n&quot;
multiline_comment|/* store f11 */
l_string|&quot;    std   12,0x260(1)&bslash;n&quot;
multiline_comment|/* store f12 */
l_string|&quot;    std   13,0x268(1)&bslash;n&quot;
multiline_comment|/* store f13 */
l_string|&quot;    std   14,0x270(1)&bslash;n&quot;
multiline_comment|/* store f14 */
l_string|&quot;    std   15,0x278(1)&bslash;n&quot;
multiline_comment|/* store f15 */
l_string|&quot;    stmg  0,15,0x280(1)&bslash;n&quot;
multiline_comment|/* store general registers */
l_string|&quot;    stctg 0,15,0x380(1)&bslash;n&quot;
multiline_comment|/* store control registers */
l_string|&quot;    oi    0x384(1),0x10&bslash;n&quot;
multiline_comment|/* fake protection bit */
l_string|&quot;    lpswe 0(%0)&quot;
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
comma
l_string|&quot;0&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif                                 /* __ASM_S390_PROCESSOR_H           */
eof
