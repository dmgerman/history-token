multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 Waldorf GMBH&n; * Copyright (C) 1995, 1996, 1997, 1998, 1999, 2001, 2002, 2003 Ralf Baechle&n; * Copyright (C) 1996 Paul M. Antoine&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_PROCESSOR_H
DECL|macro|_ASM_PROCESSOR_H
mdefine_line|#define _ASM_PROCESSOR_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/cachectl.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/cpu-info.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/prefetch.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * Return current * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({ __label__ _l; _l: &amp;&amp;_l;})
multiline_comment|/*&n; * System setup and hardware flags..&n; */
r_extern
r_void
(paren
op_star
id|cpu_wait
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|vced_count
comma
id|vcei_count
suffix:semicolon
macro_line|#ifdef CONFIG_MIPS32
multiline_comment|/*&n; * User space process size: 2GB. This is hardcoded into a few places,&n; * so don&squot;t change it unless you know what you are doing.&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;0x7fff8000UL
multiline_comment|/*&n; * This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;(PAGE_ALIGN(TASK_SIZE / 3))
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS64
multiline_comment|/*&n; * User space process size: 1TB. This is hardcoded into a few places,&n; * so don&squot;t change it unless you know what you are doing.  TASK_SIZE&n; * is limited to 1TB by the R4000 architecture; R10000 and better can&n; * support 16TB; the architectural reserve for future expansion is&n; * 8192EB ...&n; */
DECL|macro|TASK_SIZE32
mdefine_line|#define TASK_SIZE32&t;0x7fff8000UL
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;0x10000000000UL
multiline_comment|/*&n; * This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;((current-&gt;thread.mflags &amp; MF_32BIT_ADDR) ? &bslash;&n;&t;PAGE_ALIGN(TASK_SIZE32 / 3) : PAGE_ALIGN(TASK_SIZE / 3))
macro_line|#endif
multiline_comment|/*&n; * Size of io_bitmap in longwords.&n; */
DECL|macro|IO_BITMAP_SIZE
mdefine_line|#define IO_BITMAP_SIZE&t;2048
DECL|macro|NUM_FPU_REGS
mdefine_line|#define NUM_FPU_REGS&t;32
DECL|typedef|fpureg_t
r_typedef
id|__u64
id|fpureg_t
suffix:semicolon
DECL|struct|mips_fpu_hard_struct
r_struct
id|mips_fpu_hard_struct
(brace
DECL|member|fpr
id|fpureg_t
id|fpr
(braket
id|NUM_FPU_REGS
)braket
suffix:semicolon
DECL|member|fcr31
r_int
r_int
id|fcr31
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * It would be nice to add some more fields for emulator statistics, but there&n; * are a number of fixed offsets in offset.h and elsewhere that would have to&n; * be recalculated by hand.  So the additional information will be private to&n; * the FPU emulator for now.  See asm-mips/fpu_emulator.h.&n; */
DECL|struct|mips_fpu_soft_struct
r_struct
id|mips_fpu_soft_struct
(brace
DECL|member|fpr
id|fpureg_t
id|fpr
(braket
id|NUM_FPU_REGS
)braket
suffix:semicolon
DECL|member|fcr31
r_int
r_int
id|fcr31
suffix:semicolon
)brace
suffix:semicolon
DECL|union|mips_fpu_union
r_union
id|mips_fpu_union
(brace
DECL|member|hard
r_struct
id|mips_fpu_hard_struct
id|hard
suffix:semicolon
DECL|member|soft
r_struct
id|mips_fpu_soft_struct
id|soft
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_FPU
mdefine_line|#define INIT_FPU { &bslash;&n;&t;{{0,},} &bslash;&n;}
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
DECL|macro|ARCH_MIN_TASKALIGN
mdefine_line|#define ARCH_MIN_TASKALIGN&t;8
multiline_comment|/*&n; * If you change thread_struct remember to change the #defines below too!&n; */
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
multiline_comment|/* Saved main processor registers. */
DECL|member|reg16
r_int
r_int
id|reg16
suffix:semicolon
DECL|member|reg17
DECL|member|reg18
DECL|member|reg19
DECL|member|reg20
DECL|member|reg21
DECL|member|reg22
DECL|member|reg23
r_int
r_int
id|reg17
comma
id|reg18
comma
id|reg19
comma
id|reg20
comma
id|reg21
comma
id|reg22
comma
id|reg23
suffix:semicolon
DECL|member|reg29
DECL|member|reg30
DECL|member|reg31
r_int
r_int
id|reg29
comma
id|reg30
comma
id|reg31
suffix:semicolon
multiline_comment|/* Saved cp0 stuff. */
DECL|member|cp0_status
r_int
r_int
id|cp0_status
suffix:semicolon
multiline_comment|/* Saved fpu/fpu emulator stuff. */
DECL|member|fpu
r_union
id|mips_fpu_union
id|fpu
suffix:semicolon
multiline_comment|/* Other stuff associated with the thread. */
DECL|member|cp0_badvaddr
r_int
r_int
id|cp0_badvaddr
suffix:semicolon
multiline_comment|/* Last user fault */
DECL|member|cp0_baduaddr
r_int
r_int
id|cp0_baduaddr
suffix:semicolon
multiline_comment|/* Last kernel fault accessing USEG */
DECL|member|error_code
r_int
r_int
id|error_code
suffix:semicolon
DECL|member|trap_no
r_int
r_int
id|trap_no
suffix:semicolon
DECL|macro|MF_FIXADE
mdefine_line|#define MF_FIXADE&t;1&t;&t;/* Fix address errors in software */
DECL|macro|MF_LOGADE
mdefine_line|#define MF_LOGADE&t;2&t;&t;/* Log address errors to syslog */
DECL|macro|MF_32BIT_REGS
mdefine_line|#define MF_32BIT_REGS&t;4&t;&t;/* also implies 16/32 fprs */
DECL|macro|MF_32BIT_ADDR
mdefine_line|#define MF_32BIT_ADDR&t;8&t;&t;/* 32-bit address space (o32/n32) */
DECL|member|mflags
r_int
r_int
id|mflags
suffix:semicolon
DECL|member|irix_trampoline
r_int
r_int
id|irix_trampoline
suffix:semicolon
multiline_comment|/* Wheee... */
DECL|member|irix_oldctx
r_int
r_int
id|irix_oldctx
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MF_ABI_MASK
mdefine_line|#define MF_ABI_MASK&t;(MF_32BIT_REGS | MF_32BIT_ADDR)
DECL|macro|MF_O32
mdefine_line|#define MF_O32&t;&t;(MF_32BIT_REGS | MF_32BIT_ADDR)
DECL|macro|MF_N32
mdefine_line|#define MF_N32&t;&t;MF_32BIT_ADDR
DECL|macro|MF_N64
mdefine_line|#define MF_N64&t;&t;0
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD  { &bslash;&n;        /* &bslash;&n;         * saved main processor registers &bslash;&n;         */ &bslash;&n;&t;0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;&t;               0, 0, 0, &bslash;&n;&t;/* &bslash;&n;&t; * saved cp0 stuff &bslash;&n;&t; */ &bslash;&n;&t;0, &bslash;&n;&t;/* &bslash;&n;&t; * saved fpu/fpu emulator stuff &bslash;&n;&t; */ &bslash;&n;&t;INIT_FPU, &bslash;&n;&t;/* &bslash;&n;&t; * Other stuff associated with the process &bslash;&n;&t; */ &bslash;&n;&t;0, 0, 0, 0, &bslash;&n;&t;/* &bslash;&n;&t; * For now the default is to fix address errors &bslash;&n;&t; */ &bslash;&n;&t;MF_FIXADE, 0, 0 &bslash;&n;}
r_struct
id|task_struct
suffix:semicolon
multiline_comment|/* Free all resources held by a thread. */
DECL|macro|release_thread
mdefine_line|#define release_thread(thread) do { } while(0)
multiline_comment|/* Prepare to copy thread state - unlazy all lazy status */
DECL|macro|prepare_to_copy
mdefine_line|#define prepare_to_copy(tsk)&t;do { } while (0)
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
r_extern
r_int
r_int
id|thread_saved_pc
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
multiline_comment|/*&n; * Do necessary setup to start up a newly executed thread.&n; */
r_extern
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
id|pc
comma
r_int
r_int
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
DECL|macro|__PT_REG
mdefine_line|#define __PT_REG(reg) ((long)&amp;((struct pt_regs *)0)-&gt;reg - sizeof(struct pt_regs))
DECL|macro|__KSTK_TOS
mdefine_line|#define __KSTK_TOS(tsk) ((unsigned long)(tsk-&gt;thread_info) + THREAD_SIZE - 32)
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk) (*(unsigned long *)(__KSTK_TOS(tsk) + __PT_REG(cp0_epc)))
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk) (*(unsigned long *)(__KSTK_TOS(tsk) + __PT_REG(regs[29])))
DECL|macro|KSTK_STATUS
mdefine_line|#define KSTK_STATUS(tsk) (*(unsigned long *)(__KSTK_TOS(tsk) + __PT_REG(cp0_status)))
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()&t;barrier()
multiline_comment|/*&n; * Return_address is a replacement for __builtin_return_address(count)&n; * which on certain architectures cannot reasonably be implemented in GCC&n; * (MIPS, Alpha) or is unuseable with -fomit-frame-pointer (i386).&n; * Note that __builtin_return_address(x&gt;=1) is forbidden because GCC&n; * aborts compilation on some CPUs.  It&squot;s simply not possible to unwind&n; * some CPU&squot;s stackframes.&n; *&n; * __builtin_return_address works only for non-leaf functions.  We avoid the&n; * overhead of a function call by forcing the compiler to save the return&n; * address register on the stack.&n; */
DECL|macro|return_address
mdefine_line|#define return_address() ({__asm__ __volatile__(&quot;&quot;:::&quot;$31&quot;);__builtin_return_address(0);})
macro_line|#ifdef CONFIG_CPU_HAS_PREFETCH
DECL|macro|ARCH_HAS_PREFETCH
mdefine_line|#define ARCH_HAS_PREFETCH
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
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;.set&t;mips4&t;&t;&bslash;n&quot;
l_string|&quot;&t;pref&t;%0, (%1)&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;mips0&t;&t;&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;i&quot;
(paren
id|Pref_Load
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* _ASM_PROCESSOR_H */
eof
