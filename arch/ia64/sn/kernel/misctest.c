multiline_comment|/* &n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000-2002 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/sn/sn_sal.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/timex.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/sn/intr.h&gt;
macro_line|#include &lt;asm/hw_irq.h&gt;
macro_line|#include &lt;asm/sn/leds.h&gt;
r_extern
r_int
id|autotest_enabled
suffix:semicolon
DECL|variable|mcatest
DECL|variable|debug0
DECL|variable|debug1
DECL|variable|debug2
DECL|variable|debug3
r_int
id|mcatest
op_assign
l_int|0
comma
id|debug0
comma
id|debug1
comma
id|debug2
comma
id|debug3
suffix:semicolon
DECL|macro|HDELAY
mdefine_line|#define HDELAY(t)&t;(IS_RUNNING_ON_SIMULATOR() ? udelay(1) : udelay(t))
multiline_comment|/* &n; * mcatest&n; *&t;mactest contains a decimal number (RPTT) where&n; *&t;&t;R - flag, if non zero, run forever&n; *&n; *&t;&t;P - identifies when to run the test&n; *&t;&t;    0 execute test at cpu 0 early init&n; *&t;&t;    1 execute test at cpu 0 idle&n; *&t;&t;    2 execute test at last (highest numbered) cpu idle&n; *&t;&t;    3 execute test on all cpus at idle&n; *&n; *&t;&t;TT- identifies test to run&n; *&t;&t;    01 = MCA via dup TLB dropin&n; *&t;&t;    02 = MCA via garbage address&n; *&t;&t;    03 = lfetch via garbage address&n; *&t;&t;    05 = INIT self&n; *&t;&t;    06 = INIT other cpu&n; *&t;&t;    07 = INIT non-existent cpu&n; *&t;&t;    10 = IPI stress test. Target cpu 0&n; *&t;&t;    11 = IPI stress test. Target all cpus&n; *&t;&t;    12 = TLB stress test&n; *&t;&t;    13 = Park cpu (spinloop)&n; *&t;&t;    14 = One shot TLB test with tlb spinlock&n; *&t;&t;    15 = One shot TLB test&n; *&t;&t;    16 = One shot TLB test sync&squot;ed with RTC&n; *&t;&t;    20 = set led to the cpuid &amp; spin.&n; *&t;&t;    21 = Try mixed cache/uncached refs &amp; see what happens&n; *&t;&t;    22 = Call SAL reboot&n; *&t;&t;    23 = Call PAL halt&n; */
DECL|function|set_mcatest
r_static
r_int
id|__init
id|set_mcatest
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|val
suffix:semicolon
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|val
)paren
suffix:semicolon
id|mcatest
op_assign
id|val
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;mcatest=&quot;
comma
id|set_mcatest
)paren
suffix:semicolon
DECL|function|set_debug0
r_static
r_int
id|__init
id|set_debug0
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|val
suffix:semicolon
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|val
)paren
suffix:semicolon
id|debug0
op_assign
id|val
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;debug0=&quot;
comma
id|set_debug0
)paren
suffix:semicolon
DECL|function|set_debug1
r_static
r_int
id|__init
id|set_debug1
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|val
suffix:semicolon
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|val
)paren
suffix:semicolon
id|debug1
op_assign
id|val
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;debug1=&quot;
comma
id|set_debug1
)paren
suffix:semicolon
DECL|function|set_debug2
r_static
r_int
id|__init
id|set_debug2
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|val
suffix:semicolon
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|val
)paren
suffix:semicolon
id|debug2
op_assign
id|val
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;debug2=&quot;
comma
id|set_debug2
)paren
suffix:semicolon
DECL|function|set_debug3
r_static
r_int
id|__init
id|set_debug3
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|val
suffix:semicolon
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|val
)paren
suffix:semicolon
id|debug3
op_assign
id|val
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;debug3=&quot;
comma
id|set_debug3
)paren
suffix:semicolon
DECL|variable|go
r_static
r_volatile
r_int
id|go
suffix:semicolon
r_static
r_void
DECL|function|do_sync
id|do_sync
c_func
(paren
r_int
id|pos
)paren
(brace
r_if
c_cond
(paren
id|pos
op_ne
l_int|3
)paren
r_return
suffix:semicolon
r_else
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
op_eq
l_int|0
)paren
id|go
op_assign
l_int|1
suffix:semicolon
r_else
r_while
c_loop
(paren
op_logical_neg
id|go
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|sgi_mcatest_bkpt
id|sgi_mcatest_bkpt
c_func
(paren
r_void
)paren
(brace
)brace
multiline_comment|/*&n; * Optional test&n; *&t;pos - 0 called from early init&n; *&t;pos - called when cpu about to go idle (fully initialized&n; */
r_void
DECL|function|sgi_mcatest
id|sgi_mcatest
c_func
(paren
r_int
id|pos
)paren
(brace
r_int
id|spos
comma
id|test
comma
id|repeat
suffix:semicolon
r_int
id|cpu
comma
id|curcpu
comma
id|i
comma
id|n
suffix:semicolon
singleline_comment|//if (IS_RUNNING_ON_SIMULATOR()) mcatest=1323;
id|repeat
op_assign
id|mcatest
op_div
l_int|1000
suffix:semicolon
id|spos
op_assign
(paren
id|mcatest
op_div
l_int|100
)paren
op_mod
l_int|10
suffix:semicolon
id|test
op_assign
id|mcatest
op_mod
l_int|100
suffix:semicolon
id|curcpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mcatest
op_eq
l_int|0
op_logical_or
op_logical_neg
(paren
(paren
id|pos
op_eq
l_int|0
op_logical_and
id|spos
op_eq
l_int|0
)paren
op_logical_or
(paren
id|pos
op_eq
l_int|1
op_logical_and
id|spos
op_eq
l_int|3
)paren
op_logical_or
(paren
id|pos
op_eq
l_int|1
op_logical_and
id|spos
op_eq
l_int|1
op_logical_and
id|curcpu
op_eq
l_int|0
)paren
op_logical_or
(paren
id|pos
op_eq
l_int|1
op_logical_and
id|spos
op_eq
l_int|2
op_logical_and
id|curcpu
op_eq
id|smp_num_cpus
op_minus
l_int|1
)paren
)paren
)paren
r_return
suffix:semicolon
id|again
suffix:colon
r_if
c_cond
(paren
id|test
op_eq
l_int|1
op_logical_or
id|test
op_eq
l_int|2
op_logical_or
id|test
op_eq
l_int|3
)paren
(brace
r_void
id|zzzmca
c_func
(paren
r_int
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU %d: About to cause unexpected MCA&bslash;n&quot;
comma
id|curcpu
)paren
suffix:semicolon
id|HDELAY
c_func
(paren
l_int|100000
)paren
suffix:semicolon
id|sgi_mcatest_bkpt
c_func
(paren
)paren
suffix:semicolon
id|do_sync
c_func
(paren
id|spos
)paren
suffix:semicolon
id|zzzmca
c_func
(paren
id|test
op_minus
l_int|1
)paren
suffix:semicolon
id|HDELAY
c_func
(paren
l_int|100000
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|test
op_eq
l_int|4
)paren
(brace
r_int
id|result
comma
id|adrs
(braket
)braket
op_assign
(brace
l_int|0xe0021000009821e0UL
comma
l_int|0xc0003f3000000000UL
comma
l_int|0xc0000081101c0000UL
comma
l_int|0xc00000180e021004UL
comma
l_int|0xc00000180e022004UL
comma
l_int|0xc00000180e023004UL
)brace
suffix:semicolon
r_int
id|size
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|2
comma
l_int|4
comma
l_int|8
)brace
suffix:semicolon
r_int
id|r
comma
id|i
comma
id|j
comma
id|k
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
l_int|2
suffix:semicolon
id|k
op_increment
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|4
suffix:semicolon
id|j
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Probing 0x%lx, size %ld&bslash;n&quot;
comma
id|adrs
(braket
id|i
)braket
comma
id|size
(braket
id|j
)braket
)paren
suffix:semicolon
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
id|r
op_assign
id|ia64_sn_probe_io_slot
(paren
id|adrs
(braket
id|i
)braket
comma
id|size
(braket
id|j
)braket
comma
op_amp
id|result
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;    status %d, val 0x%lx&bslash;n&quot;
comma
id|r
comma
id|result
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|100000
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
r_if
c_cond
(paren
id|test
op_eq
l_int|5
)paren
(brace
id|cpu
op_assign
id|curcpu
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU %d: About to send INIT to self (cpu %d)&bslash;n&quot;
comma
id|curcpu
comma
id|cpu
)paren
suffix:semicolon
id|HDELAY
c_func
(paren
l_int|100000
)paren
suffix:semicolon
id|sgi_mcatest_bkpt
c_func
(paren
)paren
suffix:semicolon
id|do_sync
c_func
(paren
id|spos
)paren
suffix:semicolon
id|platform_send_ipi
c_func
(paren
id|cpu
comma
l_int|0
comma
id|IA64_IPI_DM_INIT
comma
l_int|0
)paren
suffix:semicolon
id|HDELAY
c_func
(paren
l_int|100000
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU %d: Returned from INIT&bslash;n&quot;
comma
id|curcpu
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|test
op_eq
l_int|6
)paren
(brace
id|cpu
op_assign
id|curcpu
op_xor
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU %d: About to send INIT to other cpu (cpu %d)&bslash;n&quot;
comma
id|curcpu
comma
id|cpu
)paren
suffix:semicolon
id|HDELAY
c_func
(paren
l_int|100000
)paren
suffix:semicolon
id|sgi_mcatest_bkpt
c_func
(paren
)paren
suffix:semicolon
id|do_sync
c_func
(paren
id|spos
)paren
suffix:semicolon
id|platform_send_ipi
c_func
(paren
id|cpu
comma
l_int|0
comma
id|IA64_IPI_DM_INIT
comma
l_int|0
)paren
suffix:semicolon
id|HDELAY
c_func
(paren
l_int|100000
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU %d: Done&bslash;n&quot;
comma
id|curcpu
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|test
op_eq
l_int|7
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;CPU %d: About to send INIT to non-existent cpu&bslash;n&quot;
comma
id|curcpu
)paren
suffix:semicolon
id|HDELAY
c_func
(paren
l_int|100000
)paren
suffix:semicolon
id|sgi_mcatest_bkpt
c_func
(paren
)paren
suffix:semicolon
id|do_sync
c_func
(paren
id|spos
)paren
suffix:semicolon
id|sn_send_IPI_phys
c_func
(paren
l_int|0xffff
comma
l_int|0
comma
id|IA64_IPI_DM_INIT
)paren
suffix:semicolon
id|HDELAY
c_func
(paren
l_int|100000
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU %d: Done&bslash;n&quot;
comma
id|curcpu
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|test
op_eq
l_int|10
)paren
(brace
id|n
op_assign
id|IS_RUNNING_ON_SIMULATOR
c_func
(paren
)paren
ques
c_cond
l_int|10
suffix:colon
l_int|10000000
suffix:semicolon
id|cpu
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU %d: IPI stress test. Target cpu 0&bslash;n&quot;
comma
id|curcpu
)paren
suffix:semicolon
id|HDELAY
c_func
(paren
l_int|100000
)paren
suffix:semicolon
id|sgi_mcatest_bkpt
c_func
(paren
)paren
suffix:semicolon
id|do_sync
c_func
(paren
id|spos
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|n
suffix:semicolon
id|i
op_increment
)paren
id|platform_send_ipi
c_func
(paren
id|cpu
comma
id|IA64_IPI_RESCHEDULE
comma
id|IA64_IPI_DM_INT
comma
l_int|0
)paren
suffix:semicolon
id|HDELAY
c_func
(paren
l_int|100000
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU %d: Done&bslash;n&quot;
comma
id|curcpu
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|test
op_eq
l_int|11
)paren
(brace
id|n
op_assign
id|IS_RUNNING_ON_SIMULATOR
c_func
(paren
)paren
ques
c_cond
l_int|100
suffix:colon
l_int|10000000
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU %d: IPI stress test. Target all cpus&bslash;n&quot;
comma
id|curcpu
)paren
suffix:semicolon
id|HDELAY
c_func
(paren
l_int|100000
)paren
suffix:semicolon
id|sgi_mcatest_bkpt
c_func
(paren
)paren
suffix:semicolon
id|do_sync
c_func
(paren
id|spos
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|n
suffix:semicolon
id|i
op_increment
)paren
r_for
c_loop
(paren
id|cpu
op_assign
l_int|0
suffix:semicolon
id|cpu
OL
id|smp_num_cpus
suffix:semicolon
id|cpu
op_increment
)paren
r_if
c_cond
(paren
id|smp_num_cpus
OG
l_int|2
op_logical_and
id|cpu
op_ne
id|curcpu
)paren
id|platform_send_ipi
c_func
(paren
id|cpu
comma
id|IA64_IPI_RESCHEDULE
comma
id|IA64_IPI_DM_INT
comma
l_int|0
)paren
suffix:semicolon
id|HDELAY
c_func
(paren
l_int|100000
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU %d: Done&bslash;n&quot;
comma
id|curcpu
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|test
op_eq
l_int|12
)paren
(brace
r_int
id|adr
op_assign
l_int|0xe002200000000000UL
suffix:semicolon
id|n
op_assign
id|IS_RUNNING_ON_SIMULATOR
c_func
(paren
)paren
ques
c_cond
l_int|1000
suffix:colon
l_int|100000
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU %d: TLB flush stress test&bslash;n&quot;
comma
id|curcpu
)paren
suffix:semicolon
id|HDELAY
c_func
(paren
l_int|100000
)paren
suffix:semicolon
id|sgi_mcatest_bkpt
c_func
(paren
)paren
suffix:semicolon
id|do_sync
c_func
(paren
id|spos
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|n
suffix:semicolon
id|i
op_increment
)paren
id|platform_global_tlb_purge
c_func
(paren
id|adr
comma
id|adr
op_plus
l_int|25
op_star
id|PAGE_SIZE
comma
l_int|14
)paren
suffix:semicolon
id|HDELAY
c_func
(paren
l_int|100000
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU %d: Done&bslash;n&quot;
comma
id|curcpu
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|test
op_eq
l_int|13
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;CPU %d: Park cpu in spinloop&bslash;n&quot;
comma
id|curcpu
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|test
op_eq
l_int|14
op_logical_or
id|test
op_eq
l_int|15
op_logical_or
id|test
op_eq
l_int|16
op_logical_or
id|test
op_eq
l_int|17
)paren
(brace
r_int
id|adr
op_assign
l_int|0xe002200000000000UL
suffix:semicolon
r_static
r_int
id|inited
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|inited
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|debug0
op_eq
l_int|0
)paren
id|debug0
op_assign
l_int|1
suffix:semicolon
id|repeat
op_assign
l_int|1
suffix:semicolon
id|do_sync
c_func
(paren
id|spos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|curcpu
op_ge
id|smp_num_cpus
op_minus
l_int|2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Parking cpu %d&bslash;n&quot;
comma
id|curcpu
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;Waiting cpu %d&bslash;n&quot;
comma
id|curcpu
)paren
suffix:semicolon
id|HDELAY
c_func
(paren
l_int|1000000
)paren
suffix:semicolon
)brace
id|HDELAY
c_func
(paren
l_int|1000000
)paren
suffix:semicolon
id|inited
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|test
op_eq
l_int|16
op_logical_or
id|test
op_eq
l_int|17
)paren
(brace
r_int
r_int
id|t
comma
id|shift
comma
id|mask
suffix:semicolon
id|mask
op_assign
(paren
id|smp_num_cpus
OG
l_int|16
)paren
ques
c_cond
l_int|0x1f
suffix:colon
l_int|0xf
suffix:semicolon
id|shift
op_assign
l_int|25
op_minus
id|debug1
suffix:semicolon
r_do
(brace
id|t
op_assign
id|get_cycles
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_RUNNING_ON_SIMULATOR
c_func
(paren
)paren
)paren
id|t
op_assign
(paren
id|t
op_rshift
l_int|8
)paren
suffix:semicolon
r_else
id|t
op_assign
(paren
id|t
op_rshift
id|shift
)paren
suffix:semicolon
id|t
op_assign
id|t
op_amp
id|mask
suffix:semicolon
)brace
r_while
c_loop
(paren
id|t
op_eq
id|curcpu
)paren
suffix:semicolon
r_do
(brace
id|t
op_assign
id|get_cycles
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_RUNNING_ON_SIMULATOR
c_func
(paren
)paren
)paren
id|t
op_assign
(paren
id|t
op_rshift
l_int|8
)paren
suffix:semicolon
r_else
id|t
op_assign
(paren
id|t
op_rshift
id|shift
)paren
suffix:semicolon
id|t
op_assign
id|t
op_amp
id|mask
suffix:semicolon
)brace
r_while
c_loop
(paren
id|t
op_ne
id|curcpu
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|debug3
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;CPU %d: One TLB start&bslash;n&quot;
comma
id|curcpu
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|test
op_ne
l_int|17
)paren
id|platform_global_tlb_purge
c_func
(paren
id|adr
comma
id|adr
op_plus
id|PAGE_SIZE
op_star
id|debug0
comma
l_int|14
)paren
suffix:semicolon
r_if
c_cond
(paren
id|debug3
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;CPU %d: One TLB flush done&bslash;n&quot;
comma
id|curcpu
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|test
op_eq
l_int|20
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|set_led_bits
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
l_int|0xff
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|test
op_eq
l_int|21
)paren
(brace
r_extern
r_int
id|ia64_mca_stack
(braket
)braket
suffix:semicolon
r_int
id|i
comma
id|n
suffix:semicolon
r_volatile
r_int
op_star
id|p
comma
op_star
id|up
suffix:semicolon
id|p
op_assign
(paren
r_volatile
r_int
op_star
)paren
id|__imva
c_func
(paren
id|ia64_mca_stack
)paren
suffix:semicolon
id|up
op_assign
(paren
r_volatile
r_int
op_star
)paren
(paren
id|__pa
c_func
(paren
id|p
)paren
op_or
id|__IA64_UNCACHED_OFFSET
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_RUNNING_ON_SIMULATOR
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ZZZ get data in cache&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|n
op_assign
l_int|0
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|100
suffix:semicolon
id|i
op_increment
)paren
id|n
op_add_assign
op_star
(paren
id|p
op_plus
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_RUNNING_ON_SIMULATOR
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ZZZ Make uncached refs to same data&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|n
op_assign
l_int|0
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|100
suffix:semicolon
id|i
op_increment
)paren
id|n
op_add_assign
op_star
(paren
id|up
op_plus
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_RUNNING_ON_SIMULATOR
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ZZZ dirty the data via cached refs&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|n
op_assign
l_int|0
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|100
suffix:semicolon
id|i
op_increment
)paren
op_star
(paren
id|p
op_plus
id|i
)paren
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_RUNNING_ON_SIMULATOR
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ZZZ Make uncached refs to same data&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|n
op_assign
l_int|0
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|100
suffix:semicolon
id|i
op_increment
)paren
id|n
op_add_assign
op_star
(paren
id|up
op_plus
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_RUNNING_ON_SIMULATOR
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ZZZ Flushing cache&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|n
op_assign
l_int|0
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|100
suffix:semicolon
id|i
op_increment
)paren
id|ia64_fc
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|p
op_plus
id|i
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ZZZ done&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|test
op_eq
l_int|21
)paren
(brace
r_int
id|i
suffix:semicolon
r_volatile
r_int
id|tb
comma
id|t
(braket
l_int|10
)braket
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|10
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tb
op_assign
id|debug3
op_plus
id|ia64_get_itc
c_func
(paren
)paren
suffix:semicolon
id|sgi_mcatest_bkpt
c_func
(paren
)paren
suffix:semicolon
id|t
(braket
id|i
)braket
op_assign
id|ia64_get_itc
c_func
(paren
)paren
op_minus
id|tb
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|10
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ZZZ NULL  0x%lx&bslash;n&quot;
comma
id|t
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|10
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tb
op_assign
id|debug3
op_plus
id|ia64_get_itc
c_func
(paren
)paren
suffix:semicolon
id|ia64_pal_call_static
c_func
(paren
id|PAL_MC_DRAIN
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
id|t
(braket
id|i
)braket
op_assign
id|ia64_get_itc
c_func
(paren
)paren
op_minus
id|tb
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|10
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ZZZ DRAIN 0x%lx&bslash;n&quot;
comma
id|t
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|test
op_eq
l_int|22
)paren
(brace
r_extern
r_void
id|machine_restart
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ZZZ machine_restart&bslash;n&quot;
)paren
suffix:semicolon
id|machine_restart
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|test
op_eq
l_int|23
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ZZZ ia64_pal_halt_light&bslash;n&quot;
)paren
suffix:semicolon
id|ia64_pal_halt_light
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|repeat
)paren
r_goto
id|again
suffix:semicolon
)brace
eof
