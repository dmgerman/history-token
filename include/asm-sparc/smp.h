multiline_comment|/* smp.h: Sparc specific SMP stuff.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_SMP_H
DECL|macro|_SPARC_SMP_H
mdefine_line|#define _SPARC_SMP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/head.h&gt;
macro_line|#include &lt;asm/btfixup.h&gt;
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* PROM provided per-processor information we need&n; * to start them all up.&n; */
DECL|struct|prom_cpuinfo
r_struct
id|prom_cpuinfo
(brace
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
DECL|member|mid
r_int
id|mid
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|linux_num_cpus
suffix:semicolon
multiline_comment|/* number of CPUs probed  */
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#ifdef CONFIG_SMP
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/asi.h&gt;
r_extern
r_struct
id|prom_cpuinfo
id|linux_cpus
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/* Per processor Sparc parameters we need. */
DECL|struct|cpuinfo_sparc
r_struct
id|cpuinfo_sparc
(brace
DECL|member|udelay_val
r_int
r_int
id|udelay_val
suffix:semicolon
multiline_comment|/* that&squot;s it */
DECL|member|next
r_int
r_int
id|next
suffix:semicolon
DECL|member|mid
r_int
r_int
id|mid
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|cpuinfo_sparc
id|cpu_data
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_int
r_int
id|cpu_offset
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/*&n; *&t;Private routines/data&n; */
r_extern
r_int
r_char
id|boot_cpu_id
suffix:semicolon
r_extern
r_int
r_int
id|cpu_present_map
suffix:semicolon
DECL|macro|cpu_online_map
mdefine_line|#define cpu_online_map cpu_present_map
DECL|typedef|smpfunc_t
r_typedef
r_void
(paren
op_star
id|smpfunc_t
)paren
(paren
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;General functions that each host system must provide.&n; */
r_void
id|sun4m_init_smp
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|sun4d_init_smp
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|smp_callin
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|smp_boot_cpus
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|smp_store_cpu_info
c_func
(paren
r_int
)paren
suffix:semicolon
r_struct
id|seq_file
suffix:semicolon
r_void
id|smp_bogo_info
c_func
(paren
r_struct
id|seq_file
op_star
)paren
suffix:semicolon
r_void
id|smp_info
c_func
(paren
r_struct
id|seq_file
op_star
)paren
suffix:semicolon
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|smp_cross_call
comma
id|smpfunc_t
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|smp_message_pass
comma
r_int
comma
r_int
comma
r_int
r_int
comma
r_int
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_int
comma
id|__smp_processor_id
comma
r_void
)paren
id|BTFIXUPDEF_BLACKBOX
c_func
(paren
id|smp_processor_id
)paren
id|BTFIXUPDEF_BLACKBOX
c_func
(paren
id|load_current
)paren
DECL|macro|smp_cross_call
mdefine_line|#define smp_cross_call(func,arg1,arg2,arg3,arg4,arg5) BTFIXUP_CALL(smp_cross_call)(func,arg1,arg2,arg3,arg4,arg5)
DECL|macro|smp_message_pass
mdefine_line|#define smp_message_pass(target,msg,data,wait) BTFIXUP_CALL(smp_message_pass)(target,msg,data,wait)
DECL|function|xc0
r_extern
id|__inline__
r_void
id|xc0
c_func
(paren
id|smpfunc_t
id|func
)paren
(brace
id|smp_cross_call
c_func
(paren
id|func
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|xc1
r_extern
id|__inline__
r_void
id|xc1
c_func
(paren
id|smpfunc_t
id|func
comma
r_int
r_int
id|arg1
)paren
(brace
id|smp_cross_call
c_func
(paren
id|func
comma
id|arg1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|xc2
r_extern
id|__inline__
r_void
id|xc2
c_func
(paren
id|smpfunc_t
id|func
comma
r_int
r_int
id|arg1
comma
r_int
r_int
id|arg2
)paren
(brace
id|smp_cross_call
c_func
(paren
id|func
comma
id|arg1
comma
id|arg2
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|xc3
r_extern
id|__inline__
r_void
id|xc3
c_func
(paren
id|smpfunc_t
id|func
comma
r_int
r_int
id|arg1
comma
r_int
r_int
id|arg2
comma
r_int
r_int
id|arg3
)paren
(brace
id|smp_cross_call
c_func
(paren
id|func
comma
id|arg1
comma
id|arg2
comma
id|arg3
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|xc4
r_extern
id|__inline__
r_void
id|xc4
c_func
(paren
id|smpfunc_t
id|func
comma
r_int
r_int
id|arg1
comma
r_int
r_int
id|arg2
comma
r_int
r_int
id|arg3
comma
r_int
r_int
id|arg4
)paren
(brace
id|smp_cross_call
c_func
(paren
id|func
comma
id|arg1
comma
id|arg2
comma
id|arg3
comma
id|arg4
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|xc5
r_extern
id|__inline__
r_void
id|xc5
c_func
(paren
id|smpfunc_t
id|func
comma
r_int
r_int
id|arg1
comma
r_int
r_int
id|arg2
comma
r_int
r_int
id|arg3
comma
r_int
r_int
id|arg4
comma
r_int
r_int
id|arg5
)paren
(brace
id|smp_cross_call
c_func
(paren
id|func
comma
id|arg1
comma
id|arg2
comma
id|arg3
comma
id|arg4
comma
id|arg5
)paren
suffix:semicolon
)brace
DECL|function|smp_call_function
r_extern
id|__inline__
r_int
id|smp_call_function
c_func
(paren
r_void
(paren
op_star
id|func
)paren
(paren
r_void
op_star
id|info
)paren
comma
r_void
op_star
id|info
comma
r_int
id|nonatomic
comma
r_int
id|wait
)paren
(brace
id|xc1
c_func
(paren
(paren
id|smpfunc_t
)paren
id|func
comma
(paren
r_int
r_int
)paren
id|info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_extern
id|__volatile__
r_int
id|__cpu_number_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
id|__volatile__
r_int
id|__cpu_logical_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_int
r_int
id|smp_proc_in_lock
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|function|cpu_logical_map
r_extern
id|__inline__
r_int
id|cpu_logical_map
c_func
(paren
r_int
id|cpu
)paren
(brace
r_return
id|__cpu_logical_map
(braket
id|cpu
)braket
suffix:semicolon
)brace
DECL|function|cpu_number_map
r_extern
id|__inline__
r_int
id|cpu_number_map
c_func
(paren
r_int
id|cpu
)paren
(brace
r_return
id|__cpu_number_map
(braket
id|cpu
)braket
suffix:semicolon
)brace
DECL|function|hard_smp4m_processor_id
r_extern
id|__inline__
r_int
id|hard_smp4m_processor_id
c_func
(paren
r_void
)paren
(brace
r_int
id|cpuid
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rd %%tbr, %0&bslash;n&bslash;t&quot;
l_string|&quot;srl %0, 12, %0&bslash;n&bslash;t&quot;
l_string|&quot;and %0, 3, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|cpuid
)paren
)paren
suffix:semicolon
r_return
id|cpuid
suffix:semicolon
)brace
DECL|function|hard_smp4d_processor_id
r_extern
id|__inline__
r_int
id|hard_smp4d_processor_id
c_func
(paren
r_void
)paren
(brace
r_int
id|cpuid
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%%g0] %1, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|cpuid
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|ASI_M_VIKING_TMP1
)paren
)paren
suffix:semicolon
r_return
id|cpuid
suffix:semicolon
)brace
macro_line|#ifndef MODULE
DECL|function|hard_smp_processor_id
r_extern
id|__inline__
r_int
id|hard_smp_processor_id
c_func
(paren
r_void
)paren
(brace
r_int
id|cpuid
suffix:semicolon
multiline_comment|/* Black box - sun4m&n;&t;&t;__asm__ __volatile__(&quot;rd %%tbr, %0&bslash;n&bslash;t&quot;&n;&t;&t;&t;&t;     &quot;srl %0, 12, %0&bslash;n&bslash;t&quot;&n;&t;&t;&t;&t;     &quot;and %0, 3, %0&bslash;n&bslash;t&quot; :&n;&t;&t;&t;&t;     &quot;=&amp;r&quot; (cpuid));&n;&t;             - sun4d&n;&t;   &t;__asm__ __volatile__(&quot;lda [%g0] ASI_M_VIKING_TMP1, %0&bslash;n&bslash;t&quot;&n;&t;   &t;&t;&t;     &quot;nop; nop&quot; :&n;&t;   &t;&t;&t;     &quot;=&amp;r&quot; (cpuid));&n;&t;   See btfixup.h and btfixupprep.c to understand how a blackbox works.&n;&t; */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sethi %%hi(___b_smp_processor_id), %0&bslash;n&bslash;t&quot;
l_string|&quot;sethi %%hi(boot_cpu_id), %0&bslash;n&bslash;t&quot;
l_string|&quot;ldub [%0 + %%lo(boot_cpu_id)], %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|cpuid
)paren
)paren
suffix:semicolon
r_return
id|cpuid
suffix:semicolon
)brace
macro_line|#else
DECL|function|hard_smp_processor_id
r_extern
id|__inline__
r_int
id|hard_smp_processor_id
c_func
(paren
r_void
)paren
(brace
r_int
id|cpuid
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov %%o7, %%g1&bslash;n&bslash;t&quot;
l_string|&quot;call ___f___smp_processor_id&bslash;n&bslash;t&quot;
l_string|&quot; nop&bslash;n&bslash;t&quot;
l_string|&quot;mov %%g2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cpuid
)paren
suffix:colon
suffix:colon
l_string|&quot;g1&quot;
comma
l_string|&quot;g2&quot;
)paren
suffix:semicolon
r_return
id|cpuid
suffix:semicolon
)brace
macro_line|#endif
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id() hard_smp_processor_id()
multiline_comment|/* XXX We really need to implement this now.  -DaveM */
DECL|function|smp_send_reschedule
r_extern
id|__inline__
r_void
id|smp_send_reschedule
c_func
(paren
r_int
id|cpu
)paren
(brace
)brace
DECL|function|smp_send_stop
r_extern
id|__inline__
r_void
id|smp_send_stop
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif /* !(__ASSEMBLY__) */
multiline_comment|/* Sparc specific messages. */
DECL|macro|MSG_CROSS_CALL
mdefine_line|#define MSG_CROSS_CALL         0x0005       /* run func on cpus */
multiline_comment|/* Empirical PROM processor mailbox constants.  If the per-cpu mailbox&n; * contains something other than one of these then the ipi is from&n; * Linux&squot;s active_kernel_processor.  This facility exists so that&n; * the boot monitor can capture all the other cpus when one catches&n; * a watchdog reset or the user enters the monitor using L1-A keys.&n; */
DECL|macro|MBOX_STOPCPU
mdefine_line|#define MBOX_STOPCPU          0xFB
DECL|macro|MBOX_IDLECPU
mdefine_line|#define MBOX_IDLECPU          0xFC
DECL|macro|MBOX_IDLECPU2
mdefine_line|#define MBOX_IDLECPU2         0xFD
DECL|macro|MBOX_STOPCPU2
mdefine_line|#define MBOX_STOPCPU2         0xFE
macro_line|#endif /* !(CONFIG_SMP) */
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID            0xFF
macro_line|#endif /* !(_SPARC_SMP_H) */
eof
