multiline_comment|/*&n; *  linux/arch/mips/kernel/proc.c&n; *&n; *  Copyright (C) 1995, 1996, 2001  Ralf Baechle&n; *  Copyright (C) 2001  MIPS Technologies, Inc.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/watch.h&gt;
DECL|variable|vced_count
DECL|variable|vcei_count
r_int
r_int
id|vced_count
comma
id|vcei_count
suffix:semicolon
DECL|variable|cpu_name
r_static
r_const
r_char
op_star
id|cpu_name
(braket
)braket
op_assign
(brace
(braket
id|CPU_UNKNOWN
)braket
l_string|&quot;unknown&quot;
comma
(braket
id|CPU_R2000
)braket
l_string|&quot;R2000&quot;
comma
(braket
id|CPU_R3000
)braket
l_string|&quot;R3000&quot;
comma
(braket
id|CPU_R3000A
)braket
l_string|&quot;R3000A&quot;
comma
(braket
id|CPU_R3041
)braket
l_string|&quot;R3041&quot;
comma
(braket
id|CPU_R3051
)braket
l_string|&quot;R3051&quot;
comma
(braket
id|CPU_R3052
)braket
l_string|&quot;R3052&quot;
comma
(braket
id|CPU_R3081
)braket
l_string|&quot;R3081&quot;
comma
(braket
id|CPU_R3081E
)braket
l_string|&quot;R3081E&quot;
comma
(braket
id|CPU_R4000PC
)braket
l_string|&quot;R4000PC&quot;
comma
(braket
id|CPU_R4000SC
)braket
l_string|&quot;R4000SC&quot;
comma
(braket
id|CPU_R4000MC
)braket
l_string|&quot;R4000MC&quot;
comma
(braket
id|CPU_R4200
)braket
l_string|&quot;R4200&quot;
comma
(braket
id|CPU_R4400PC
)braket
l_string|&quot;R4400PC&quot;
comma
(braket
id|CPU_R4400SC
)braket
l_string|&quot;R4400SC&quot;
comma
(braket
id|CPU_R4400MC
)braket
l_string|&quot;R4400MC&quot;
comma
(braket
id|CPU_R4600
)braket
l_string|&quot;R4600&quot;
comma
(braket
id|CPU_R6000
)braket
l_string|&quot;R6000&quot;
comma
(braket
id|CPU_R6000A
)braket
l_string|&quot;R6000A&quot;
comma
(braket
id|CPU_R8000
)braket
l_string|&quot;R8000&quot;
comma
(braket
id|CPU_R10000
)braket
l_string|&quot;R10000&quot;
comma
(braket
id|CPU_R4300
)braket
l_string|&quot;R4300&quot;
comma
(braket
id|CPU_R4650
)braket
l_string|&quot;R4650&quot;
comma
(braket
id|CPU_R4700
)braket
l_string|&quot;R4700&quot;
comma
(braket
id|CPU_R5000
)braket
l_string|&quot;R5000&quot;
comma
(braket
id|CPU_R5000A
)braket
l_string|&quot;R5000A&quot;
comma
(braket
id|CPU_R4640
)braket
l_string|&quot;R4640&quot;
comma
(braket
id|CPU_NEVADA
)braket
l_string|&quot;Nevada&quot;
comma
(braket
id|CPU_RM7000
)braket
l_string|&quot;RM7000&quot;
comma
(braket
id|CPU_R5432
)braket
l_string|&quot;R5432&quot;
comma
(braket
id|CPU_4KC
)braket
l_string|&quot;MIPS 4Kc&quot;
comma
(braket
id|CPU_5KC
)braket
l_string|&quot;MIPS 5Kc&quot;
comma
(braket
id|CPU_R4310
)braket
l_string|&quot;R4310&quot;
comma
(braket
id|CPU_SB1
)braket
l_string|&quot;SiByte SB1&quot;
comma
(braket
id|CPU_TX3912
)braket
l_string|&quot;TX3912&quot;
comma
(braket
id|CPU_TX3922
)braket
l_string|&quot;TX3922&quot;
comma
(braket
id|CPU_TX3927
)braket
l_string|&quot;TX3927&quot;
comma
(braket
id|CPU_AU1000
)braket
l_string|&quot;Au1000&quot;
comma
(braket
id|CPU_AU1500
)braket
l_string|&quot;Au1500&quot;
comma
(braket
id|CPU_4KEC
)braket
l_string|&quot;MIPS 4KEc&quot;
comma
(braket
id|CPU_4KSC
)braket
l_string|&quot;MIPS 4KSc&quot;
comma
(braket
id|CPU_VR41XX
)braket
l_string|&quot;NEC Vr41xx&quot;
comma
(braket
id|CPU_R5500
)braket
l_string|&quot;R5500&quot;
comma
(braket
id|CPU_TX49XX
)braket
l_string|&quot;TX49xx&quot;
comma
(braket
id|CPU_20KC
)braket
l_string|&quot;MIPS 20Kc&quot;
comma
(braket
id|CPU_VR4111
)braket
l_string|&quot;NEC VR4111&quot;
comma
(braket
id|CPU_VR4121
)braket
l_string|&quot;NEC VR4121&quot;
comma
(braket
id|CPU_VR4122
)braket
l_string|&quot;NEC VR4122&quot;
comma
(braket
id|CPU_VR4131
)braket
l_string|&quot;NEC VR4131&quot;
comma
(braket
id|CPU_VR4181
)braket
l_string|&quot;NEC VR4181&quot;
comma
(braket
id|CPU_VR4181A
)braket
l_string|&quot;NEC VR4181A&quot;
comma
(braket
id|CPU_SR71000
)braket
l_string|&quot;Sandcraft SR71000&quot;
)brace
suffix:semicolon
DECL|function|show_cpuinfo
r_static
r_int
id|show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
r_int
r_int
id|version
op_assign
id|current_cpu_data.processor_id
suffix:semicolon
r_int
r_int
id|fp_vers
op_assign
id|current_cpu_data.fpu_id
suffix:semicolon
r_int
r_int
id|n
op_assign
(paren
r_int
r_int
)paren
id|v
op_minus
l_int|1
suffix:semicolon
r_char
id|fmt
(braket
l_int|64
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
op_logical_neg
id|cpu_isset
c_func
(paren
id|n
comma
id|cpu_online_map
)paren
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * For the first processor also print the system type&n;&t; */
r_if
c_cond
(paren
id|n
op_eq
l_int|0
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;system type&bslash;t&bslash;t: %s&bslash;n&quot;
comma
id|get_system_type
c_func
(paren
)paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;processor&bslash;t&bslash;t: %ld&bslash;n&quot;
comma
id|n
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|fmt
comma
l_string|&quot;cpu model&bslash;t&bslash;t: %%s V%%d.%%d%s&bslash;n&quot;
comma
id|cpu_has_fpu
ques
c_cond
l_string|&quot;  FPU V%d.%d&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
id|fmt
comma
id|cpu_name
(braket
id|current_cpu_data.cputype
op_le
id|CPU_LAST
ques
c_cond
id|current_cpu_data.cputype
suffix:colon
id|CPU_UNKNOWN
)braket
comma
(paren
id|version
op_rshift
l_int|4
)paren
op_amp
l_int|0x0f
comma
id|version
op_amp
l_int|0x0f
comma
(paren
id|fp_vers
op_rshift
l_int|4
)paren
op_amp
l_int|0x0f
comma
id|fp_vers
op_amp
l_int|0x0f
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;BogoMIPS&bslash;t&bslash;t: %lu.%02lu&bslash;n&quot;
comma
id|loops_per_jiffy
op_div
(paren
l_int|500000
op_div
id|HZ
)paren
comma
(paren
id|loops_per_jiffy
op_div
(paren
l_int|5000
op_div
id|HZ
)paren
)paren
op_mod
l_int|100
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;wait instruction&bslash;t: %s&bslash;n&quot;
comma
id|cpu_wait
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;microsecond timers&bslash;t: %s&bslash;n&quot;
comma
id|cpu_has_counter
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;tlb_entries&bslash;t&bslash;t: %d&bslash;n&quot;
comma
id|current_cpu_data.tlbsize
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;extra interrupt vector&bslash;t: %s&bslash;n&quot;
comma
id|cpu_has_divec
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;hardware watchpoint&bslash;t: %s&bslash;n&quot;
comma
id|cpu_has_watch
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|fmt
comma
l_string|&quot;VCE%%c exceptions&bslash;t&bslash;t: %s&bslash;n&quot;
comma
id|cpu_has_vce
ques
c_cond
l_string|&quot;%d&quot;
suffix:colon
l_string|&quot;not available&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
id|fmt
comma
l_char|&squot;D&squot;
comma
id|vced_count
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
id|fmt
comma
l_char|&squot;I&squot;
comma
id|vcei_count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|c_start
r_static
r_void
op_star
id|c_start
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_int
r_int
id|i
op_assign
op_star
id|pos
suffix:semicolon
r_return
id|i
OL
id|NR_CPUS
ques
c_cond
(paren
r_void
op_star
)paren
(paren
id|i
op_plus
l_int|1
)paren
suffix:colon
l_int|NULL
suffix:semicolon
)brace
DECL|function|c_next
r_static
r_void
op_star
id|c_next
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
comma
id|loff_t
op_star
id|pos
)paren
(brace
op_increment
op_star
id|pos
suffix:semicolon
r_return
id|c_start
c_func
(paren
id|m
comma
id|pos
)paren
suffix:semicolon
)brace
DECL|function|c_stop
r_static
r_void
id|c_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
)brace
DECL|variable|cpuinfo_op
r_struct
id|seq_operations
id|cpuinfo_op
op_assign
(brace
dot
id|start
op_assign
id|c_start
comma
dot
id|next
op_assign
id|c_next
comma
dot
id|stop
op_assign
id|c_stop
comma
dot
id|show
op_assign
id|show_cpuinfo
comma
)brace
suffix:semicolon
eof
