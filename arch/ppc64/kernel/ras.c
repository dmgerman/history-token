multiline_comment|/*&n; * ras.c&n; * Copyright (C) 2001 Dave Engebretsen IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
multiline_comment|/* Change Activity:&n; * 2001/09/21 : engebret : Created with minimal EPOW and HW exception support.&n; * End Change Activity &n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/sysrq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/iSeries/LparData.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/rtas.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
r_static
r_void
id|ras_epow_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_static
r_void
id|ras_error_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_void
id|init_ras_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* #define DEBUG */
multiline_comment|/*&n; * Initialize handlers for the set of interrupts caused by hardware errors&n; * and power system events.&n; */
DECL|function|init_ras_IRQ
r_void
id|init_ras_IRQ
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|np
suffix:semicolon
r_int
r_int
op_star
id|ireg
comma
id|len
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|np
op_assign
id|find_path_device
c_func
(paren
l_string|&quot;/event-sources/internal-errors&quot;
)paren
)paren
op_logical_and
(paren
id|ireg
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;open-pic-interrupt&quot;
comma
op_amp
id|len
)paren
)paren
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
(paren
id|len
op_div
r_sizeof
(paren
op_star
id|ireg
)paren
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|request_irq
c_func
(paren
id|virt_irq_create_mapping
c_func
(paren
op_star
(paren
id|ireg
)paren
)paren
op_plus
id|NUM_8259_INTERRUPTS
comma
op_amp
id|ras_error_interrupt
comma
l_int|0
comma
l_string|&quot;RAS_ERROR&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|ireg
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|np
op_assign
id|find_path_device
c_func
(paren
l_string|&quot;/event-sources/epow-events&quot;
)paren
)paren
op_logical_and
(paren
id|ireg
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;open-pic-interrupt&quot;
comma
op_amp
id|len
)paren
)paren
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
(paren
id|len
op_div
r_sizeof
(paren
op_star
id|ireg
)paren
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|request_irq
c_func
(paren
id|virt_irq_create_mapping
c_func
(paren
op_star
(paren
id|ireg
)paren
)paren
op_plus
id|NUM_8259_INTERRUPTS
comma
op_amp
id|ras_epow_interrupt
comma
l_int|0
comma
l_string|&quot;RAS_EPOW&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|ireg
op_increment
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Handle power subsystem events (EPOW).&n; *&n; * Presently we just log the event has occurred.  This should be fixed&n; * to examine the type of power failure and take appropriate action where&n; * the time horizon permits something useful to be done.&n; */
r_static
r_void
DECL|function|ras_epow_interrupt
id|ras_epow_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|rtas_error_log
id|log_entry
suffix:semicolon
r_int
r_int
id|size
op_assign
r_sizeof
(paren
id|log_entry
)paren
suffix:semicolon
r_int
id|status
op_assign
l_int|0xdeadbeef
suffix:semicolon
id|status
op_assign
id|rtas_call
c_func
(paren
id|rtas_token
c_func
(paren
l_string|&quot;check-exception&quot;
)paren
comma
l_int|6
comma
l_int|1
comma
l_int|NULL
comma
l_int|0x500
comma
id|irq
comma
id|EPOW_WARNING
op_or
id|POWERMGM_EVENTS
comma
l_int|1
comma
multiline_comment|/* Time Critical */
id|__pa
c_func
(paren
op_amp
id|log_entry
)paren
comma
id|size
)paren
suffix:semicolon
id|udbg_printf
c_func
(paren
l_string|&quot;EPOW &lt;0x%lx 0x%lx&gt;&bslash;n&quot;
comma
op_star
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|log_entry
)paren
comma
id|status
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;EPOW &lt;0x%lx 0x%lx&gt;&bslash;n&quot;
comma
op_star
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|log_entry
)paren
comma
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Handle hardware error interrupts.&n; *&n; * RTAS check-exception is called to collect data on the exception.  If&n; * the error is deemed recoverable, we log a warning and return.&n; * For nonrecoverable errors, an error is logged and we stop all processing&n; * as quickly as possible in order to prevent propagation of the failure.&n; */
r_static
r_void
DECL|function|ras_error_interrupt
id|ras_error_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|rtas_error_log
id|log_entry
suffix:semicolon
r_int
r_int
id|size
op_assign
r_sizeof
(paren
id|log_entry
)paren
suffix:semicolon
r_int
id|status
op_assign
l_int|0xdeadbeef
suffix:semicolon
id|status
op_assign
id|rtas_call
c_func
(paren
id|rtas_token
c_func
(paren
l_string|&quot;check-exception&quot;
)paren
comma
l_int|6
comma
l_int|1
comma
l_int|NULL
comma
l_int|0x500
comma
id|irq
comma
id|INTERNAL_ERROR
comma
l_int|1
comma
multiline_comment|/* Time Critical */
id|__pa
c_func
(paren
op_amp
id|log_entry
)paren
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_ne
l_int|1
)paren
op_logical_and
(paren
id|log_entry.severity
op_ge
id|SEVERITY_ERROR_SYNC
)paren
)paren
(brace
id|udbg_printf
c_func
(paren
l_string|&quot;HW Error &lt;0x%lx 0x%lx&gt;&bslash;n&quot;
comma
op_star
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|log_entry
)paren
comma
id|status
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Error: Fatal hardware error &lt;0x%lx 0x%lx&gt;&bslash;n&quot;
comma
op_star
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|log_entry
)paren
comma
id|status
)paren
suffix:semicolon
macro_line|#ifndef DEBUG
multiline_comment|/* Don&squot;t actually power off when debugging so we can test&n;&t;&t; * without actually failing while injecting errors.&n;&t;&t; */
id|ppc_md
dot
id|power_off
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
id|udbg_printf
c_func
(paren
l_string|&quot;Recoverable HW Error &lt;0x%lx 0x%lx&gt;&bslash;n&quot;
comma
op_star
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|log_entry
)paren
comma
id|status
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Warning: Recoverable hardware error &lt;0x%lx 0x%lx&gt;&bslash;n&quot;
comma
op_star
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|log_entry
)paren
comma
id|status
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
eof
