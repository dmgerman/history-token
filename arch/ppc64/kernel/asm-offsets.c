multiline_comment|/*&n; * This program is used to generate definitions needed by&n; * assembly language modules.&n; *&n; * We use the technique used in the OSF Mach kernel code:&n; * generate asm statements containing #defines,&n; * compile this file to assembler, and then extract the&n; * #defines from the assembly-language output.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/naca.h&gt;
macro_line|#include &lt;asm/paca.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpPaca.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpQueue.h&gt;
macro_line|#include &lt;asm/iSeries/HvLpEvent.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/rtas.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
DECL|macro|DEFINE
mdefine_line|#define DEFINE(sym, val) &bslash;&n;&t;asm volatile(&quot;&bslash;n-&gt;&quot; #sym &quot; %0 &quot; #val : : &quot;i&quot; (val))
DECL|macro|BLANK
mdefine_line|#define BLANK() asm volatile(&quot;&bslash;n-&gt;&quot; : : )
DECL|function|main
r_int
id|main
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* thread struct on stack */
id|DEFINE
c_func
(paren
id|THREAD_SHIFT
comma
id|THREAD_SHIFT
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|THREAD_SIZE
comma
id|THREAD_SIZE
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TI_FLAGS
comma
m_offsetof
(paren
r_struct
id|thread_info
comma
id|flags
)paren
)paren
suffix:semicolon
multiline_comment|/* task_struct-&gt;thread */
id|DEFINE
c_func
(paren
id|THREAD
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_REGS
comma
m_offsetof
(paren
r_struct
id|thread_struct
comma
id|regs
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|THREAD_FPEXC_MODE
comma
m_offsetof
(paren
r_struct
id|thread_struct
comma
id|fpexc_mode
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|THREAD_FPR0
comma
m_offsetof
(paren
r_struct
id|thread_struct
comma
id|fpr
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|THREAD_FPSCR
comma
m_offsetof
(paren
r_struct
id|thread_struct
comma
id|fpscr
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|KSP
comma
m_offsetof
(paren
r_struct
id|thread_struct
comma
id|ksp
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|MM
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|mm
)paren
)paren
suffix:semicolon
multiline_comment|/* naca */
id|DEFINE
c_func
(paren
id|PACA
comma
m_offsetof
(paren
r_struct
id|naca_struct
comma
id|paca
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|DCACHEL1LINESIZE
comma
m_offsetof
(paren
r_struct
id|systemcfg
comma
id|dCacheL1LineSize
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|DCACHEL1LOGLINESIZE
comma
m_offsetof
(paren
r_struct
id|naca_struct
comma
id|dCacheL1LogLineSize
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|DCACHEL1LINESPERPAGE
comma
m_offsetof
(paren
r_struct
id|naca_struct
comma
id|dCacheL1LinesPerPage
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ICACHEL1LINESIZE
comma
m_offsetof
(paren
r_struct
id|systemcfg
comma
id|iCacheL1LineSize
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ICACHEL1LOGLINESIZE
comma
m_offsetof
(paren
r_struct
id|naca_struct
comma
id|iCacheL1LogLineSize
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ICACHEL1LINESPERPAGE
comma
m_offsetof
(paren
r_struct
id|naca_struct
comma
id|iCacheL1LinesPerPage
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|SLBSIZE
comma
m_offsetof
(paren
r_struct
id|naca_struct
comma
id|slb_size
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PLATFORM
comma
m_offsetof
(paren
r_struct
id|systemcfg
comma
id|platform
)paren
)paren
suffix:semicolon
multiline_comment|/* paca */
id|DEFINE
c_func
(paren
id|PACA_SIZE
comma
r_sizeof
(paren
r_struct
id|paca_struct
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACAPACAINDEX
comma
m_offsetof
(paren
r_struct
id|paca_struct
comma
id|xPacaIndex
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACAPROCSTART
comma
m_offsetof
(paren
r_struct
id|paca_struct
comma
id|xProcStart
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACAKSAVE
comma
m_offsetof
(paren
r_struct
id|paca_struct
comma
id|xKsave
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACACURRENT
comma
m_offsetof
(paren
r_struct
id|paca_struct
comma
id|xCurrent
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACASAVEDMSR
comma
m_offsetof
(paren
r_struct
id|paca_struct
comma
id|xSavedMsr
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACASTABREAL
comma
m_offsetof
(paren
r_struct
id|paca_struct
comma
id|xStab_data.real
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACASTABVIRT
comma
m_offsetof
(paren
r_struct
id|paca_struct
comma
id|xStab_data.virt
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACASTABRR
comma
m_offsetof
(paren
r_struct
id|paca_struct
comma
id|xStab_data.next_round_robin
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACAR1
comma
m_offsetof
(paren
r_struct
id|paca_struct
comma
id|xR1
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACALPQUEUE
comma
m_offsetof
(paren
r_struct
id|paca_struct
comma
id|lpQueuePtr
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACATOC
comma
m_offsetof
(paren
r_struct
id|paca_struct
comma
id|xTOC
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACAEXCSP
comma
m_offsetof
(paren
r_struct
id|paca_struct
comma
id|exception_sp
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACAPROCENABLED
comma
m_offsetof
(paren
r_struct
id|paca_struct
comma
id|xProcEnabled
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACADEFAULTDECR
comma
m_offsetof
(paren
r_struct
id|paca_struct
comma
id|default_decr
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACAPROFENABLED
comma
m_offsetof
(paren
r_struct
id|paca_struct
comma
id|prof_enabled
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACAPROFLEN
comma
m_offsetof
(paren
r_struct
id|paca_struct
comma
id|prof_len
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACAPROFSHIFT
comma
m_offsetof
(paren
r_struct
id|paca_struct
comma
id|prof_shift
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACAPROFBUFFER
comma
m_offsetof
(paren
r_struct
id|paca_struct
comma
id|prof_buffer
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACAPROFSTEXT
comma
m_offsetof
(paren
r_struct
id|paca_struct
comma
id|prof_stext
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACALPPACA
comma
m_offsetof
(paren
r_struct
id|paca_struct
comma
id|xLpPaca
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|LPPACA
comma
m_offsetof
(paren
r_struct
id|paca_struct
comma
id|xLpPaca
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACAREGSAV
comma
m_offsetof
(paren
r_struct
id|paca_struct
comma
id|xRegSav
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACAEXC
comma
m_offsetof
(paren
r_struct
id|paca_struct
comma
id|exception_stack
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACAGUARD
comma
m_offsetof
(paren
r_struct
id|paca_struct
comma
id|guard
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|LPPACASRR0
comma
m_offsetof
(paren
r_struct
id|ItLpPaca
comma
id|xSavedSrr0
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|LPPACASRR1
comma
m_offsetof
(paren
r_struct
id|ItLpPaca
comma
id|xSavedSrr1
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|LPPACAANYINT
comma
m_offsetof
(paren
r_struct
id|ItLpPaca
comma
id|xIntDword.xAnyInt
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|LPPACADECRINT
comma
m_offsetof
(paren
r_struct
id|ItLpPaca
comma
id|xIntDword.xFields.xDecrInt
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|LPQCUREVENTPTR
comma
m_offsetof
(paren
r_struct
id|ItLpQueue
comma
id|xSlicCurEventPtr
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|LPQOVERFLOW
comma
m_offsetof
(paren
r_struct
id|ItLpQueue
comma
id|xPlicOverflowIntPending
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|LPEVENTFLAGS
comma
m_offsetof
(paren
r_struct
id|HvLpEvent
comma
id|xFlags
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PROMENTRY
comma
m_offsetof
(paren
r_struct
id|prom_t
comma
id|entry
)paren
)paren
suffix:semicolon
multiline_comment|/* RTAS */
id|DEFINE
c_func
(paren
id|RTASBASE
comma
m_offsetof
(paren
r_struct
id|rtas_t
comma
id|base
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|RTASENTRY
comma
m_offsetof
(paren
r_struct
id|rtas_t
comma
id|entry
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|RTASSIZE
comma
m_offsetof
(paren
r_struct
id|rtas_t
comma
id|size
)paren
)paren
suffix:semicolon
multiline_comment|/* Interrupt register frame */
id|DEFINE
c_func
(paren
id|STACK_FRAME_OVERHEAD
comma
id|STACK_FRAME_OVERHEAD
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|SWITCH_FRAME_SIZE
comma
id|STACK_FRAME_OVERHEAD
op_plus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
suffix:semicolon
multiline_comment|/* 288 = # of volatile regs, int &amp; fp, for leaf routines */
multiline_comment|/* which do not stack a frame.  See the PPC64 ABI.       */
id|DEFINE
c_func
(paren
id|INT_FRAME_SIZE
comma
id|STACK_FRAME_OVERHEAD
op_plus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
op_plus
l_int|288
)paren
suffix:semicolon
multiline_comment|/* Create extra stack space for SRR0 and SRR1 when calling prom/rtas. */
id|DEFINE
c_func
(paren
id|PROM_FRAME_SIZE
comma
id|STACK_FRAME_OVERHEAD
op_plus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
op_plus
l_int|16
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|RTAS_FRAME_SIZE
comma
id|STACK_FRAME_OVERHEAD
op_plus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
op_plus
l_int|16
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR0
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gpr
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR1
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gpr
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR2
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gpr
(braket
l_int|2
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR3
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gpr
(braket
l_int|3
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR4
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gpr
(braket
l_int|4
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR5
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gpr
(braket
l_int|5
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR6
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gpr
(braket
l_int|6
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR7
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gpr
(braket
l_int|7
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR8
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gpr
(braket
l_int|8
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR9
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gpr
(braket
l_int|9
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR20
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gpr
(braket
l_int|20
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR21
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gpr
(braket
l_int|21
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR22
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gpr
(braket
l_int|22
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR23
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gpr
(braket
l_int|23
)braket
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Note: these symbols include _ because they overlap with special&n;&t; * register names&n;&t; */
id|DEFINE
c_func
(paren
id|_NIP
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|nip
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|_MSR
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|msr
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|_CTR
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|ctr
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|_LINK
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|link
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|_CCR
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|ccr
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|_XER
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|xer
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|_DAR
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|dar
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|_DSISR
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|dsisr
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ORIG_GPR3
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|orig_gpr3
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|RESULT
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|result
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TRAP
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|trap
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|SOFTE
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|softe
)paren
)paren
suffix:semicolon
multiline_comment|/* These _only_ to be used with {PROM,RTAS}_FRAME_SIZE!!! */
id|DEFINE
c_func
(paren
id|_SRR0
comma
id|STACK_FRAME_OVERHEAD
op_plus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|_SRR1
comma
id|STACK_FRAME_OVERHEAD
op_plus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
op_plus
l_int|8
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|CLONE_VM
comma
id|CLONE_VM
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|CLONE_UNTRACED
comma
id|CLONE_UNTRACED
)paren
suffix:semicolon
multiline_comment|/* About the CPU features table */
id|DEFINE
c_func
(paren
id|CPU_SPEC_ENTRY_SIZE
comma
r_sizeof
(paren
r_struct
id|cpu_spec
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|CPU_SPEC_PVR_MASK
comma
m_offsetof
(paren
r_struct
id|cpu_spec
comma
id|pvr_mask
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|CPU_SPEC_PVR_VALUE
comma
m_offsetof
(paren
r_struct
id|cpu_spec
comma
id|pvr_value
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|CPU_SPEC_FEATURES
comma
m_offsetof
(paren
r_struct
id|cpu_spec
comma
id|cpu_features
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|CPU_SPEC_SETUP
comma
m_offsetof
(paren
r_struct
id|cpu_spec
comma
id|cpu_setup
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
