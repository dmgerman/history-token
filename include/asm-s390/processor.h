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
macro_line|#ifdef __s390x__
DECL|member|pmd_quick
r_int
r_int
op_star
id|pmd_quick
suffix:semicolon
macro_line|#endif /* __s390x__ */
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
multiline_comment|/*&n; * User space process size: 2GB for 31 bit, 4TB for 64 bit.&n; */
macro_line|#ifndef __s390x__
DECL|macro|TASK_SIZE
macro_line|# define TASK_SIZE&t;&t;(0x80000000UL)
DECL|macro|TASK_UNMAPPED_BASE
macro_line|# define TASK_UNMAPPED_BASE&t;(TASK_SIZE / 2)
DECL|macro|DEFAULT_TASK_SIZE
macro_line|# define DEFAULT_TASK_SIZE&t;(0x80000000UL)
macro_line|#else /* __s390x__ */
DECL|macro|TASK_SIZE
macro_line|# define TASK_SIZE&t;&t;(test_thread_flag(TIF_31BIT) ? &bslash;&n;&t;&t;&t;&t;&t;(0x80000000UL) : (0x40000000000UL))
DECL|macro|TASK_UNMAPPED_BASE
macro_line|# define TASK_UNMAPPED_BASE&t;(TASK_SIZE / 2)
DECL|macro|DEFAULT_TASK_SIZE
macro_line|# define DEFAULT_TASK_SIZE&t;(0x40000000000UL)
macro_line|#endif /* __s390x__ */
DECL|macro|MM_VM_SIZE
mdefine_line|#define MM_VM_SIZE(mm)&t;&t;DEFAULT_TASK_SIZE
DECL|macro|HAVE_ARCH_PICK_MMAP_LAYOUT
mdefine_line|#define HAVE_ARCH_PICK_MMAP_LAYOUT
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
multiline_comment|/*&n; * Thread structure&n; */
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|fp_regs
id|s390_fp_regs
id|fp_regs
suffix:semicolon
DECL|member|acrs
r_int
r_int
id|acrs
(braket
id|NUM_ACRS
)braket
suffix:semicolon
DECL|member|ksp
r_int
r_int
id|ksp
suffix:semicolon
multiline_comment|/* kernel stack pointer             */
DECL|member|user_seg
r_int
r_int
id|user_seg
suffix:semicolon
multiline_comment|/* HSTD                             */
DECL|member|mm_segment
id|mm_segment_t
id|mm_segment
suffix:semicolon
DECL|member|prot_addr
r_int
r_int
id|prot_addr
suffix:semicolon
multiline_comment|/* address of protection-excep.     */
DECL|member|error_code
r_int
r_int
id|error_code
suffix:semicolon
multiline_comment|/* error-code of last prog-excep.   */
DECL|member|trap_no
r_int
r_int
id|trap_no
suffix:semicolon
DECL|member|per_info
id|per_struct
id|per_info
suffix:semicolon
multiline_comment|/* Used to give failing instruction back to user for ieee exceptions */
DECL|member|ieee_instruction_pointer
r_int
r_int
id|ieee_instruction_pointer
suffix:semicolon
multiline_comment|/* pfault_wait is used to block the process on a pfault event */
DECL|member|pfault_wait
r_int
r_int
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
multiline_comment|/*&n; * Stack layout of a C stack frame.&n; */
macro_line|#ifndef __PACK_STACK
DECL|struct|stack_frame
r_struct
id|stack_frame
(brace
DECL|member|back_chain
r_int
r_int
id|back_chain
suffix:semicolon
DECL|member|empty1
r_int
r_int
id|empty1
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|gprs
r_int
r_int
id|gprs
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|empty2
r_int
r_int
id|empty2
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#else
DECL|struct|stack_frame
r_struct
id|stack_frame
(brace
DECL|member|empty1
r_int
r_int
id|empty1
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|empty2
r_int
r_int
id|empty2
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|gprs
r_int
r_int
id|gprs
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|back_chain
r_int
r_int
id|back_chain
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
DECL|macro|ARCH_MIN_TASKALIGN
mdefine_line|#define ARCH_MIN_TASKALIGN&t;8
macro_line|#ifndef __s390x__
DECL|macro|__SWAPPER_PG_DIR
macro_line|# define __SWAPPER_PG_DIR __pa(&amp;swapper_pg_dir[0]) + _SEGMENT_TABLE
macro_line|#else /* __s390x__ */
DECL|macro|__SWAPPER_PG_DIR
macro_line|# define __SWAPPER_PG_DIR __pa(&amp;swapper_pg_dir[0]) + _REGION_TABLE
macro_line|#endif /* __s390x__ */
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD {{0,{{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},&t;       &bslash;&n;&t;&t;&t;    {0},{0},{0},{0},{0},{0}}},&t;&t;&t;       &bslash;&n;&t;&t;     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},&t;       &bslash;&n;&t;&t;     sizeof(init_stack) + (unsigned long) &amp;init_stack,&t;       &bslash;&n;&t;&t;     __SWAPPER_PG_DIR,&t;&t;&t;&t;&t;       &bslash;&n;&t;&t;     {0},&t;&t;&t;&t;&t;&t;       &bslash;&n;&t;&t;     0,0,0,&t;&t;&t;&t;&t;&t;       &bslash;&n;&t;&t;     (per_struct) {{{{0,}}},0,0,0,0,{{0,}}},&t;&t;       &bslash;&n;&t;&t;     0, 0&t;&t;&t;&t;&t;&t;       &bslash;&n;} 
multiline_comment|/*&n; * Do necessary setup to start up a new thread.&n; */
macro_line|#ifndef __s390x__
DECL|macro|start_thread
mdefine_line|#define start_thread(regs, new_psw, new_stackp) do {            &bslash;&n;        regs-&gt;psw.mask  = PSW_USER_BITS;                        &bslash;&n;        regs-&gt;psw.addr  = new_psw | PSW_ADDR_AMODE;             &bslash;&n;        regs-&gt;gprs[15]  = new_stackp ;                          &bslash;&n;} while (0)
macro_line|#else /* __s390x__ */
DECL|macro|start_thread
mdefine_line|#define start_thread(regs, new_psw, new_stackp) do {            &bslash;&n;        regs-&gt;psw.mask  = PSW_USER_BITS;                        &bslash;&n;        regs-&gt;psw.addr  = new_psw;                              &bslash;&n;        regs-&gt;gprs[15]  = new_stackp;                           &bslash;&n;} while (0)
DECL|macro|start_thread31
mdefine_line|#define start_thread31(regs, new_psw, new_stackp) do {          &bslash;&n;&t;regs-&gt;psw.mask  = PSW_USER32_BITS;&t;&t;&t;&bslash;&n;        regs-&gt;psw.addr  = new_psw;                              &bslash;&n;        regs-&gt;gprs[15]  = new_stackp;                           &bslash;&n;} while (0)
macro_line|#endif /* __s390x__ */
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
multiline_comment|/* Prepare to copy thread state - unlazy all lazy status */
DECL|macro|prepare_to_copy
mdefine_line|#define prepare_to_copy(tsk)&t;do { } while (0)
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
r_extern
r_void
id|show_registers
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|show_trace
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
r_int
op_star
id|sp
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
mdefine_line|#define __KSTK_PTREGS(tsk) ((struct pt_regs *) &bslash;&n;        ((unsigned long) tsk-&gt;thread_info + THREAD_SIZE - sizeof(struct pt_regs)))
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk)&t;(__KSTK_PTREGS(tsk)-&gt;psw.addr)
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk)&t;(__KSTK_PTREGS(tsk)-&gt;gprs[15])
multiline_comment|/*&n; * Give up the time slice of the virtual PU.&n; */
macro_line|#ifndef __s390x__
DECL|macro|cpu_relax
macro_line|# define cpu_relax()&t;asm volatile (&quot;diag 0,0,68&quot; : : : &quot;memory&quot;)
macro_line|#else /* __s390x__ */
DECL|macro|cpu_relax
macro_line|# define cpu_relax() &bslash;&n;&t;asm volatile (&quot;ex 0,%0&quot; : : &quot;i&quot; (__LC_DIAG44_OPCODE) : &quot;memory&quot;)
macro_line|#endif /* __s390x__ */
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
macro_line|#ifndef __s390x__
id|asm
r_volatile
(paren
l_string|&quot;    basr %0,0&bslash;n&quot;
l_string|&quot;0:  ahi  %0,1f-0b&bslash;n&quot;
l_string|&quot;    st&t;  %0,4(%1)&bslash;n&quot;
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
comma
l_string|&quot;m&quot;
(paren
id|psw
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
macro_line|#else /* __s390x__ */
id|asm
r_volatile
(paren
l_string|&quot;    larl  %0,1f&bslash;n&quot;
l_string|&quot;    stg   %0,8(%1)&bslash;n&quot;
l_string|&quot;    lpswe 0(%1)&bslash;n&quot;
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
comma
l_string|&quot;m&quot;
(paren
id|psw
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
macro_line|#endif /* __s390x__ */
)brace
multiline_comment|/*&n; * Function to stop a processor until an interruption occurred&n; */
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
id|PSW_BASE_BITS
op_or
id|PSW_MASK_IO
op_or
id|PSW_MASK_EXT
op_or
id|PSW_MASK_MCHECK
op_or
id|PSW_MASK_WAIT
suffix:semicolon
macro_line|#ifndef __s390x__
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
comma
l_string|&quot;m&quot;
(paren
id|wait_psw
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
macro_line|#else /* __s390x__ */
id|asm
r_volatile
(paren
l_string|&quot;    larl  %0,0f&bslash;n&quot;
l_string|&quot;    stg   %0,8(%1)&bslash;n&quot;
l_string|&quot;    lpswe 0(%1)&bslash;n&quot;
l_string|&quot;0:&quot;
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
comma
l_string|&quot;m&quot;
(paren
id|wait_psw
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
macro_line|#endif /* __s390x__ */
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
r_int
r_int
id|ctl_buf
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
id|PSW_BASE_BITS
op_or
id|PSW_MASK_WAIT
suffix:semicolon
id|dw_psw-&gt;addr
op_assign
id|code
suffix:semicolon
multiline_comment|/* &n;         * Store status and then load disabled wait psw,&n;         * the processor is dead afterwards&n;         */
macro_line|#ifndef __s390x__
id|asm
r_volatile
(paren
l_string|&quot;    stctl 0,0,0(%2)&bslash;n&quot;
l_string|&quot;    ni    0(%2),0xef&bslash;n&quot;
multiline_comment|/* switch off protection */
l_string|&quot;    lctl  0,0,0(%2)&bslash;n&quot;
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
l_string|&quot;    oi    0x1c0,0x10&bslash;n&quot;
multiline_comment|/* fake protection bit */
l_string|&quot;    lpsw 0(%1)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|ctl_buf
)paren
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
comma
l_string|&quot;m&quot;
(paren
id|dw_psw
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
macro_line|#else /* __s390x__ */
id|asm
r_volatile
(paren
l_string|&quot;    stctg 0,0,0(%2)&bslash;n&quot;
l_string|&quot;    ni    4(%2),0xef&bslash;n&quot;
multiline_comment|/* switch off protection */
l_string|&quot;    lctlg 0,0,0(%2)&bslash;n&quot;
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
l_string|&quot;    lpswe 0(%1)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|ctl_buf
)paren
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
comma
l_string|&quot;m&quot;
(paren
id|dw_psw
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;0&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
macro_line|#endif /* __s390x__ */
)brace
multiline_comment|/*&n; * CPU idle notifier chain.&n; */
DECL|macro|CPU_IDLE
mdefine_line|#define CPU_IDLE&t;0
DECL|macro|CPU_NOT_IDLE
mdefine_line|#define CPU_NOT_IDLE&t;1
r_struct
id|notifier_block
suffix:semicolon
r_int
id|register_idle_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
)paren
suffix:semicolon
r_int
id|unregister_idle_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif                                 /* __ASM_S390_PROCESSOR_H           */
eof
