macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_PPC_PROCESSOR_H
DECL|macro|__ASM_PPC_PROCESSOR_H
mdefine_line|#define __ASM_PPC_PROCESSOR_H
multiline_comment|/*&n; * Default implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({ __label__ _l; _l: &amp;&amp;_l;})
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/stringify.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/mpc8xx.h&gt;
macro_line|#include &lt;asm/reg.h&gt;
multiline_comment|/* We only need to define a new _MACH_xxx for machines which are part of&n; * a configuration which supports more than one type of different machine.&n; * This is currently limited to CONFIG_PPC_MULTIPLATFORM and CHRP/PReP/PMac.&n; * -- Tom&n; */
DECL|macro|_MACH_prep
mdefine_line|#define _MACH_prep&t;0x00000001
DECL|macro|_MACH_Pmac
mdefine_line|#define _MACH_Pmac&t;0x00000002&t;/* pmac or pmac clone (non-chrp) */
DECL|macro|_MACH_chrp
mdefine_line|#define _MACH_chrp&t;0x00000004&t;/* chrp machine */
multiline_comment|/* see residual.h for these */
DECL|macro|_PREP_Motorola
mdefine_line|#define _PREP_Motorola&t;0x01&t;/* motorola prep */
DECL|macro|_PREP_Firm
mdefine_line|#define _PREP_Firm&t;0x02&t;/* firmworks prep */
DECL|macro|_PREP_IBM
mdefine_line|#define _PREP_IBM&t;0x00&t;/* ibm prep */
DECL|macro|_PREP_Bull
mdefine_line|#define _PREP_Bull&t;0x03&t;/* bull prep */
multiline_comment|/* these are arbitrary */
DECL|macro|_CHRP_Motorola
mdefine_line|#define _CHRP_Motorola&t;0x04&t;/* motorola chrp, the cobra */
DECL|macro|_CHRP_IBM
mdefine_line|#define _CHRP_IBM&t;0x05&t;/* IBM chrp, the longtrail and longtrail 2 */
DECL|macro|_GLOBAL
mdefine_line|#define _GLOBAL(n)&bslash;&n;&t;.stabs __stringify(n:F-1),N_FUN,0,0,n;&bslash;&n;&t;.globl n;&bslash;&n;n:
multiline_comment|/*&n; * this is the minimum allowable io space due to the location&n; * of the io areas on prep (first one at 0x80000000) but&n; * as soon as I get around to remapping the io areas with the BATs&n; * to match the mac we can raise this. -- Cort&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(CONFIG_TASK_SIZE)
macro_line|#ifndef __ASSEMBLY__
macro_line|#ifdef CONFIG_PPC_MULTIPLATFORM
r_extern
r_int
id|_machine
suffix:semicolon
multiline_comment|/* what kind of prep workstation we are */
r_extern
r_int
id|_prep_type
suffix:semicolon
multiline_comment|/*&n; * This is used to identify the board type from a given PReP board&n; * vendor. Board revision is also made available.&n; */
r_extern
r_int
r_char
id|ucSystemType
suffix:semicolon
r_extern
r_int
r_char
id|ucBoardRev
suffix:semicolon
r_extern
r_int
r_char
id|ucBoardRevMaj
comma
id|ucBoardRevMin
suffix:semicolon
macro_line|#else
DECL|macro|_machine
mdefine_line|#define _machine 0
macro_line|#endif /* CONFIG_PPC_MULTIPLATFORM */
r_struct
id|task_struct
suffix:semicolon
r_void
id|start_thread
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|nip
comma
r_int
r_int
id|sp
)paren
suffix:semicolon
r_void
id|release_thread
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
multiline_comment|/* Prepare to copy thread state - unlazy all lazy status */
r_extern
r_void
id|prepare_to_copy
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
multiline_comment|/*&n; * Create a new kernel thread.&n; */
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
multiline_comment|/* Lazy FPU handling on uni-processor */
r_extern
r_struct
id|task_struct
op_star
id|last_task_used_math
suffix:semicolon
r_extern
r_struct
id|task_struct
op_star
id|last_task_used_altivec
suffix:semicolon
r_extern
r_struct
id|task_struct
op_star
id|last_task_used_spe
suffix:semicolon
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;(TASK_SIZE / 8 * 3)
r_typedef
r_struct
(brace
DECL|member|seg
r_int
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
DECL|member|ksp
r_int
r_int
id|ksp
suffix:semicolon
multiline_comment|/* Kernel stack pointer */
DECL|member|regs
r_struct
id|pt_regs
op_star
id|regs
suffix:semicolon
multiline_comment|/* Pointer to saved register state */
DECL|member|fs
id|mm_segment_t
id|fs
suffix:semicolon
multiline_comment|/* for get_fs() validation */
DECL|member|pgdir
r_void
op_star
id|pgdir
suffix:semicolon
multiline_comment|/* root of page-table tree */
DECL|member|fpexc_mode
r_int
id|fpexc_mode
suffix:semicolon
multiline_comment|/* floating-point exception mode */
DECL|member|last_syscall
r_int
r_int
id|last_syscall
suffix:semicolon
macro_line|#if defined(CONFIG_4xx) || defined (CONFIG_BOOKE)
DECL|member|dbcr0
r_int
r_int
id|dbcr0
suffix:semicolon
multiline_comment|/* debug control register values */
DECL|member|dbcr1
r_int
r_int
id|dbcr1
suffix:semicolon
macro_line|#endif
DECL|member|fpr
r_float
id|fpr
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Complete floating point set */
DECL|member|fpscr_pad
r_int
r_int
id|fpscr_pad
suffix:semicolon
multiline_comment|/* fpr ... fpscr must be contiguous */
DECL|member|fpscr
r_int
r_int
id|fpscr
suffix:semicolon
multiline_comment|/* Floating point status */
macro_line|#ifdef CONFIG_ALTIVEC
multiline_comment|/* Complete AltiVec register set */
id|vector128
id|vr
(braket
l_int|32
)braket
id|__attribute
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* AltiVec status */
id|vector128
id|vscr
id|__attribute
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
DECL|member|vrsave
r_int
r_int
id|vrsave
suffix:semicolon
DECL|member|used_vr
r_int
id|used_vr
suffix:semicolon
multiline_comment|/* set if process has used altivec */
macro_line|#endif /* CONFIG_ALTIVEC */
macro_line|#ifdef CONFIG_SPE
DECL|member|evr
r_int
r_int
id|evr
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* upper 32-bits of SPE regs */
DECL|member|acc
id|u64
id|acc
suffix:semicolon
multiline_comment|/* Accumulator */
DECL|member|spefscr
r_int
r_int
id|spefscr
suffix:semicolon
multiline_comment|/* SPE &amp; eFP status */
DECL|member|used_spe
r_int
id|used_spe
suffix:semicolon
multiline_comment|/* set if process has used spe */
macro_line|#endif /* CONFIG_SPE */
)brace
suffix:semicolon
DECL|macro|ARCH_MIN_TASKALIGN
mdefine_line|#define ARCH_MIN_TASKALIGN 16
DECL|macro|INIT_SP
mdefine_line|#define INIT_SP&t;&t;(sizeof(init_stack) + (unsigned long) &amp;init_stack)
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD { &bslash;&n;&t;.ksp = INIT_SP, &bslash;&n;&t;.fs = KERNEL_DS, &bslash;&n;&t;.pgdir = swapper_pg_dir, &bslash;&n;&t;.fpexc_mode = MSR_FE0 | MSR_FE1, &bslash;&n;}
multiline_comment|/*&n; * Return saved PC of a blocked thread. For now, this is the &quot;user&quot; PC&n; */
DECL|macro|thread_saved_pc
mdefine_line|#define thread_saved_pc(tsk)&t;&bslash;&n;&t;((tsk)-&gt;thread.regs? (tsk)-&gt;thread.regs-&gt;nip: 0)
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
mdefine_line|#define KSTK_EIP(tsk)&t;((tsk)-&gt;thread.regs? (tsk)-&gt;thread.regs-&gt;nip: 0)
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk)&t;((tsk)-&gt;thread.regs? (tsk)-&gt;thread.regs-&gt;gpr[1]: 0)
multiline_comment|/* Get/set floating-point exception mode */
DECL|macro|GET_FPEXC_CTL
mdefine_line|#define GET_FPEXC_CTL(tsk, adr)&t;get_fpexc_mode((tsk), (adr))
DECL|macro|SET_FPEXC_CTL
mdefine_line|#define SET_FPEXC_CTL(tsk, val)&t;set_fpexc_mode((tsk), (val))
r_extern
r_int
id|get_fpexc_mode
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|adr
)paren
suffix:semicolon
r_extern
r_int
id|set_fpexc_mode
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|val
)paren
suffix:semicolon
DECL|function|__unpack_fe01
r_static
r_inline
r_int
r_int
id|__unpack_fe01
c_func
(paren
r_int
r_int
id|msr_bits
)paren
(brace
r_return
(paren
(paren
id|msr_bits
op_amp
id|MSR_FE0
)paren
op_rshift
l_int|10
)paren
op_or
(paren
(paren
id|msr_bits
op_amp
id|MSR_FE1
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|__pack_fe01
r_static
r_inline
r_int
r_int
id|__pack_fe01
c_func
(paren
r_int
r_int
id|fpmode
)paren
(brace
r_return
(paren
(paren
id|fpmode
op_lshift
l_int|10
)paren
op_amp
id|MSR_FE0
)paren
op_or
(paren
(paren
id|fpmode
op_lshift
l_int|8
)paren
op_amp
id|MSR_FE1
)paren
suffix:semicolon
)brace
multiline_comment|/* in process.c - for early bootup debug -- Cort */
r_int
id|ll_printk
c_func
(paren
r_const
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
r_void
id|ll_puts
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/* In misc.c */
r_void
id|_nmask_and_or_msr
c_func
(paren
r_int
r_int
id|nmask
comma
r_int
r_int
id|or_val
)paren
suffix:semicolon
DECL|macro|have_of
mdefine_line|#define have_of (_machine == _MACH_chrp || _machine == _MACH_Pmac)
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()&t;barrier()
multiline_comment|/*&n; * Prefetch macros.&n; */
DECL|macro|ARCH_HAS_PREFETCH
mdefine_line|#define ARCH_HAS_PREFETCH
DECL|macro|ARCH_HAS_PREFETCHW
mdefine_line|#define ARCH_HAS_PREFETCHW
DECL|macro|ARCH_HAS_SPINLOCK_PREFETCH
mdefine_line|#define ARCH_HAS_SPINLOCK_PREFETCH
DECL|function|prefetch
r_extern
r_inline
r_void
id|prefetch
c_func
(paren
r_const
r_void
op_star
id|x
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;dcbt 0,%0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
)brace
DECL|function|prefetchw
r_extern
r_inline
r_void
id|prefetchw
c_func
(paren
r_const
r_void
op_star
id|x
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;dcbtst 0,%0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
)brace
DECL|macro|spin_lock_prefetch
mdefine_line|#define spin_lock_prefetch(x)&t;prefetchw(x)
r_extern
r_int
id|emulate_altivec
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __ASM_PPC_PROCESSOR_H */
macro_line|#endif /* __KERNEL__ */
eof
