multiline_comment|/* $Id: proc.c,v 1.1 1999/09/28 22:25:51 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 1996, 1999 Ralf Baechle&n; *&n; * XXX Rewrite this mess.&n; */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/watch.h&gt;
DECL|variable|unaligned_instructions
r_int
r_int
id|unaligned_instructions
suffix:semicolon
DECL|variable|vced_count
DECL|variable|vcei_count
r_int
r_int
id|vced_count
comma
id|vcei_count
suffix:semicolon
multiline_comment|/*&n; * BUFFER is PAGE_SIZE bytes long.&n; *&n; * Currently /proc/cpuinfo is being abused to print data about the&n; * number of date/instruction cacheflushes.&n; */
DECL|function|get_cpuinfo
r_int
id|get_cpuinfo
c_func
(paren
r_char
op_star
id|buffer
)paren
(brace
r_char
id|fmt
(braket
l_int|64
)braket
suffix:semicolon
r_int
id|len
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;cpu&bslash;t&bslash;t&bslash;t: MIPS&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#if 0
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;cpu model&bslash;t&bslash;t: %s V%d.%d&bslash;n&quot;
comma
id|cpu_name
(braket
id|mips_cputype
op_le
id|CPU_LAST
ques
c_cond
id|mips_cputype
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
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;system type&bslash;t&bslash;t: %s %s&bslash;n&quot;
comma
id|mach_group_names
(braket
id|mips_machgroup
)braket
comma
id|mach_group_to_name
(braket
id|mips_machgroup
)braket
(braket
id|mips_machtype
)braket
)paren
suffix:semicolon
macro_line|#endif
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;BogoMIPS&bslash;t&bslash;t: %lu.%02lu&bslash;n&quot;
comma
(paren
id|loops_per_jiffy
op_plus
l_int|2500
)paren
op_div
(paren
l_int|500000
op_div
id|HZ
)paren
comma
(paren
(paren
id|loops_per_jiffy
op_plus
l_int|2500
)paren
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
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Number of cpus&bslash;t&bslash;t: %d&bslash;n&quot;
comma
id|smp_num_cpus
)paren
suffix:semicolon
macro_line|#if defined (__MIPSEB__)
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;byteorder&bslash;t&bslash;t: big endian&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined (__MIPSEL__)
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;byteorder&bslash;t&bslash;t: little endian&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;unaligned accesses&bslash;t: %lu&bslash;n&quot;
comma
id|unaligned_instructions
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;wait instruction&bslash;t: %s&bslash;n&quot;
comma
id|wait_available
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;microsecond timers&bslash;t: %s&bslash;n&quot;
comma
id|cyclecounter_available
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;extra interrupt vector&bslash;t: %s&bslash;n&quot;
comma
id|dedicated_iv_available
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;hardware watchpoint&bslash;t: %s&bslash;n&quot;
comma
id|watch_available
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
id|vce_available
ques
c_cond
l_string|&quot;%d&quot;
suffix:colon
l_string|&quot;not available&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
id|fmt
comma
l_char|&squot;D&squot;
comma
id|vced_count
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
id|fmt
comma
l_char|&squot;I&squot;
comma
id|vcei_count
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|init_irq_proc
r_void
id|init_irq_proc
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Nothing, for now.  */
)brace
eof
