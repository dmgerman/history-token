multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; * This program is used to generate definitions needed by&n; * assembly language modules.&n; *&n; * We use the technique used in the OSF Mach kernel code:&n; * generate asm statements containing #defines,&n; * compile this file to assembler, and then extract the&n; * #defines from the assembly-language output.&n; */
macro_line|#include &lt;stddef.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
macro_line|#include &lt;asm/thread_info.h&gt;
macro_line|#ifdef CONFIG_PPC_ISERIES
macro_line|#include &lt;asm/iSeries/Paca.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpPaca.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpQueue.h&gt;
macro_line|#include &lt;asm/iSeries/HvLpEvent.h&gt;
macro_line|#endif /* CONFIG_PPC_ISERIES */
DECL|macro|DEFINE
mdefine_line|#define DEFINE(sym, val) &bslash;&n;&t;asm volatile(&quot;&bslash;n#define&bslash;t&quot; #sym &quot;&bslash;t%0&quot; : : &quot;i&quot; (val))
r_int
DECL|function|main
id|main
c_func
(paren
r_void
)paren
(brace
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
id|TI_CPU
comma
m_offsetof
(paren
r_struct
id|thread_info
comma
id|cpu
)paren
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
id|DEFINE
c_func
(paren
id|STATE
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|state
)paren
)paren
suffix:semicolon
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
id|DEFINE
c_func
(paren
id|ACTIVE_MM
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|active_mm
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_STRUCT_SIZE
comma
r_sizeof
(paren
r_struct
id|task_struct
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
id|PGDIR
comma
m_offsetof
(paren
r_struct
id|thread_struct
comma
id|pgdir
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|LAST_SYSCALL
comma
m_offsetof
(paren
r_struct
id|thread_struct
comma
id|last_syscall
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
id|TASK_FLAGS
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|flags
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
macro_line|#ifdef CONFIG_ALTIVEC
id|DEFINE
c_func
(paren
id|THREAD_VR0
comma
m_offsetof
(paren
r_struct
id|thread_struct
comma
id|vr
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|THREAD_VRSAVE
comma
m_offsetof
(paren
r_struct
id|thread_struct
comma
id|vrsave
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|THREAD_VSCR
comma
m_offsetof
(paren
r_struct
id|thread_struct
comma
id|vscr
)paren
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ALTIVEC */
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
id|INT_FRAME_SIZE
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
multiline_comment|/* in fact we only use gpr0 - gpr9 and gpr20 - gpr23 */
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
id|GPR10
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
l_int|10
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR11
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
l_int|11
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR12
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
l_int|12
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR13
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
l_int|13
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR14
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
l_int|14
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR15
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
l_int|15
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR16
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
l_int|16
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR17
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
l_int|17
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR18
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
l_int|18
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR19
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
l_int|19
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
id|DEFINE
c_func
(paren
id|GPR24
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
l_int|24
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR25
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
l_int|25
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR26
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
l_int|26
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR27
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
l_int|27
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR28
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
l_int|28
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR29
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
l_int|29
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR30
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
l_int|30
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|GPR31
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
l_int|31
)braket
)paren
)paren
suffix:semicolon
multiline_comment|/* Note: these symbols include _ because they overlap with special&n;&t; * register names&n;&t; */
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
id|_MQ
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|mq
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
multiline_comment|/* The PowerPC 400-class processors have neither the DAR nor the DSISR&n;&t; * SPRs. Hence, we overload them to hold the similar DEAR and ESR SPRs&n;&t; * for such processors.&n;&t; */
id|DEFINE
c_func
(paren
id|_DEAR
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
id|_ESR
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
id|CLONE_VM
comma
id|CLONE_VM
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|MM_PGD
comma
m_offsetof
(paren
r_struct
id|mm_struct
comma
id|pgd
)paren
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
macro_line|#ifdef CONFIG_PPC_ISERIES
id|DEFINE
c_func
(paren
id|PACAPROCENABLED
comma
m_offsetof
(paren
r_struct
id|Paca
comma
id|xProcEnabled
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
id|Paca
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
id|Paca
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
id|Paca
comma
id|xKsave
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
id|Paca
comma
id|xSavedMsr
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACASAVEDLR
comma
m_offsetof
(paren
r_struct
id|Paca
comma
id|xSavedLr
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACACONTEXTOVERFLOW
comma
m_offsetof
(paren
r_struct
id|Paca
comma
id|xContextOverflow
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACAR21
comma
m_offsetof
(paren
r_struct
id|Paca
comma
id|xR21
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACAR22
comma
m_offsetof
(paren
r_struct
id|Paca
comma
id|xR22
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
id|Paca
comma
id|lpQueuePtr
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
id|Paca
comma
id|xLpPaca
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACA_STRUCT_SIZE
comma
r_sizeof
(paren
r_struct
id|Paca
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|LPREGSAV
comma
m_offsetof
(paren
r_struct
id|Paca
comma
id|xRegSav
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
id|Paca
comma
id|default_decr
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
id|xRsvd
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
id|LPPACADECRINT
comma
m_offsetof
(paren
r_struct
id|ItLpPaca
comma
id|xDecrInt
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|LPPACAIPIINT
comma
m_offsetof
(paren
r_struct
id|ItLpPaca
comma
id|xIpiCnt
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
id|LPQINUSEWORD
comma
m_offsetof
(paren
r_struct
id|ItLpQueue
comma
id|xInUseWord
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
id|CONTEXT
comma
m_offsetof
(paren
r_struct
id|mm_struct
comma
id|context
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|_SOFTE
comma
id|STACK_FRAME_OVERHEAD
op_plus
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|mq
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PACA_EXT_INTS
comma
m_offsetof
(paren
r_struct
id|Paca
comma
id|ext_ints
)paren
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PPC_ISERIES */
id|DEFINE
c_func
(paren
id|NUM_USER_SEGMENTS
comma
id|TASK_SIZE
op_rshift
l_int|28
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
