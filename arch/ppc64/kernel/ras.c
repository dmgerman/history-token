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
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/sysrq.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
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
DECL|variable|ras_log_buf
r_static
r_int
r_char
id|ras_log_buf
(braket
id|RTAS_ERROR_LOG_MAX
)braket
suffix:semicolon
DECL|variable|ras_log_buf_lock
r_static
id|spinlock_t
id|ras_log_buf_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* This is true if we are using the firmware NMI handler (typically LPAR) */
r_extern
r_int
id|fwnmi_active
suffix:semicolon
DECL|variable|ras_get_sensor_state_token
r_static
r_int
id|ras_get_sensor_state_token
suffix:semicolon
DECL|variable|ras_check_exception_token
r_static
r_int
id|ras_check_exception_token
suffix:semicolon
DECL|macro|EPOW_SENSOR_TOKEN
mdefine_line|#define EPOW_SENSOR_TOKEN&t;9
DECL|macro|EPOW_SENSOR_INDEX
mdefine_line|#define EPOW_SENSOR_INDEX&t;0
DECL|macro|RAS_VECTOR_OFFSET
mdefine_line|#define RAS_VECTOR_OFFSET&t;0x500
r_static
id|irqreturn_t
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
id|irqreturn_t
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
multiline_comment|/* #define DEBUG */
DECL|function|request_ras_irqs
r_static
r_void
id|request_ras_irqs
c_func
(paren
r_struct
id|device_node
op_star
id|np
comma
r_char
op_star
id|propname
comma
id|irqreturn_t
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_int
r_int
op_star
id|ireg
comma
id|len
comma
id|i
suffix:semicolon
r_int
id|virq
comma
id|n_intr
suffix:semicolon
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
id|propname
comma
op_amp
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ireg
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|n_intr
op_assign
id|prom_n_intr_cells
c_func
(paren
id|np
)paren
suffix:semicolon
id|len
op_div_assign
id|n_intr
op_star
r_sizeof
(paren
op_star
id|ireg
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
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
id|virq
op_assign
id|virt_irq_create_mapping
c_func
(paren
op_star
id|ireg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|virq
op_eq
id|NO_IRQ
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Unable to allocate interrupt &quot;
l_string|&quot;number for %s&bslash;n&quot;
comma
id|np-&gt;full_name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|irq_offset_up
c_func
(paren
id|virq
)paren
comma
id|handler
comma
l_int|0
comma
id|name
comma
l_int|NULL
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Unable to request interrupt %d for &quot;
l_string|&quot;%s&bslash;n&quot;
comma
id|irq_offset_up
c_func
(paren
id|virq
)paren
comma
id|np-&gt;full_name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ireg
op_add_assign
id|n_intr
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Initialize handlers for the set of interrupts caused by hardware errors&n; * and power system events.&n; */
DECL|function|init_ras_IRQ
r_static
r_int
id|__init
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
id|ras_get_sensor_state_token
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;get-sensor-state&quot;
)paren
suffix:semicolon
id|ras_check_exception_token
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;check-exception&quot;
)paren
suffix:semicolon
multiline_comment|/* Internal Errors */
id|np
op_assign
id|of_find_node_by_path
c_func
(paren
l_string|&quot;/event-sources/internal-errors&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
op_ne
l_int|NULL
)paren
(brace
id|request_ras_irqs
c_func
(paren
id|np
comma
l_string|&quot;open-pic-interrupt&quot;
comma
id|ras_error_interrupt
comma
l_string|&quot;RAS_ERROR&quot;
)paren
suffix:semicolon
id|request_ras_irqs
c_func
(paren
id|np
comma
l_string|&quot;interrupts&quot;
comma
id|ras_error_interrupt
comma
l_string|&quot;RAS_ERROR&quot;
)paren
suffix:semicolon
id|of_node_put
c_func
(paren
id|np
)paren
suffix:semicolon
)brace
multiline_comment|/* EPOW Events */
id|np
op_assign
id|of_find_node_by_path
c_func
(paren
l_string|&quot;/event-sources/epow-events&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
op_ne
l_int|NULL
)paren
(brace
id|request_ras_irqs
c_func
(paren
id|np
comma
l_string|&quot;open-pic-interrupt&quot;
comma
id|ras_epow_interrupt
comma
l_string|&quot;RAS_EPOW&quot;
)paren
suffix:semicolon
id|request_ras_irqs
c_func
(paren
id|np
comma
l_string|&quot;interrupts&quot;
comma
id|ras_epow_interrupt
comma
l_string|&quot;RAS_EPOW&quot;
)paren
suffix:semicolon
id|of_node_put
c_func
(paren
id|np
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|init_ras_IRQ
id|__initcall
c_func
(paren
id|init_ras_IRQ
)paren
suffix:semicolon
multiline_comment|/*&n; * Handle power subsystem events (EPOW).&n; *&n; * Presently we just log the event has occurred.  This should be fixed&n; * to examine the type of power failure and take appropriate action where&n; * the time horizon permits something useful to be done.&n; */
r_static
id|irqreturn_t
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
r_int
id|status
op_assign
l_int|0xdeadbeef
suffix:semicolon
r_int
id|state
op_assign
l_int|0
suffix:semicolon
r_int
id|critical
suffix:semicolon
id|status
op_assign
id|rtas_call
c_func
(paren
id|ras_get_sensor_state_token
comma
l_int|2
comma
l_int|2
comma
op_amp
id|state
comma
id|EPOW_SENSOR_TOKEN
comma
id|EPOW_SENSOR_INDEX
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state
OG
l_int|3
)paren
id|critical
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Time Critical */
r_else
id|critical
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|ras_log_buf_lock
)paren
suffix:semicolon
id|status
op_assign
id|rtas_call
c_func
(paren
id|ras_check_exception_token
comma
l_int|6
comma
l_int|1
comma
l_int|NULL
comma
id|RAS_VECTOR_OFFSET
comma
id|virt_irq_to_real
c_func
(paren
id|irq_offset_down
c_func
(paren
id|irq
)paren
)paren
comma
id|RTAS_EPOW_WARNING
op_or
id|RTAS_POWERMGM_EVENTS
comma
id|critical
comma
id|__pa
c_func
(paren
op_amp
id|ras_log_buf
)paren
comma
id|rtas_get_error_log_max
c_func
(paren
)paren
)paren
suffix:semicolon
id|udbg_printf
c_func
(paren
l_string|&quot;EPOW &lt;0x%lx 0x%x 0x%x&gt;&bslash;n&quot;
comma
op_star
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|ras_log_buf
)paren
comma
id|status
comma
id|state
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;EPOW &lt;0x%lx 0x%x 0x%x&gt;&bslash;n&quot;
comma
op_star
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|ras_log_buf
)paren
comma
id|status
comma
id|state
)paren
suffix:semicolon
multiline_comment|/* format and print the extended information */
id|log_error
c_func
(paren
id|ras_log_buf
comma
id|ERR_TYPE_RTAS_LOG
comma
l_int|0
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|ras_log_buf_lock
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/*&n; * Handle hardware error interrupts.&n; *&n; * RTAS check-exception is called to collect data on the exception.  If&n; * the error is deemed recoverable, we log a warning and return.&n; * For nonrecoverable errors, an error is logged and we stop all processing&n; * as quickly as possible in order to prevent propagation of the failure.&n; */
r_static
id|irqreturn_t
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
op_star
id|rtas_elog
suffix:semicolon
r_int
id|status
op_assign
l_int|0xdeadbeef
suffix:semicolon
r_int
id|fatal
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|ras_log_buf_lock
)paren
suffix:semicolon
id|status
op_assign
id|rtas_call
c_func
(paren
id|ras_check_exception_token
comma
l_int|6
comma
l_int|1
comma
l_int|NULL
comma
id|RAS_VECTOR_OFFSET
comma
id|virt_irq_to_real
c_func
(paren
id|irq_offset_down
c_func
(paren
id|irq
)paren
)paren
comma
id|RTAS_INTERNAL_ERROR
comma
l_int|1
multiline_comment|/*Time Critical */
comma
id|__pa
c_func
(paren
op_amp
id|ras_log_buf
)paren
comma
id|rtas_get_error_log_max
c_func
(paren
)paren
)paren
suffix:semicolon
id|rtas_elog
op_assign
(paren
r_struct
id|rtas_error_log
op_star
)paren
id|ras_log_buf
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_eq
l_int|0
)paren
op_logical_and
(paren
id|rtas_elog-&gt;severity
op_ge
id|RTAS_SEVERITY_ERROR_SYNC
)paren
)paren
id|fatal
op_assign
l_int|1
suffix:semicolon
r_else
id|fatal
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* format and print the extended information */
id|log_error
c_func
(paren
id|ras_log_buf
comma
id|ERR_TYPE_RTAS_LOG
comma
id|fatal
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fatal
)paren
(brace
id|udbg_printf
c_func
(paren
l_string|&quot;Fatal HW Error &lt;0x%lx 0x%x&gt;&bslash;n&quot;
comma
op_star
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|ras_log_buf
)paren
comma
id|status
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Error: Fatal hardware error &lt;0x%lx 0x%x&gt;&bslash;n&quot;
comma
op_star
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|ras_log_buf
)paren
comma
id|status
)paren
suffix:semicolon
macro_line|#ifndef DEBUG
multiline_comment|/* Don&squot;t actually power off when debugging so we can test&n;&t;&t; * without actually failing while injecting errors.&n;&t;&t; * Error data will not be logged to syslog.&n;&t;&t; */
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
l_string|&quot;Recoverable HW Error &lt;0x%lx 0x%x&gt;&bslash;n&quot;
comma
op_star
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|ras_log_buf
)paren
comma
id|status
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Warning: Recoverable hardware error &lt;0x%lx 0x%x&gt;&bslash;n&quot;
comma
op_star
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|ras_log_buf
)paren
comma
id|status
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|ras_log_buf_lock
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/* Get the error information for errors coming through the&n; * FWNMI vectors.  The pt_regs&squot; r3 will be updated to reflect&n; * the actual r3 if possible, and a ptr to the error log entry&n; * will be returned if found.&n; */
DECL|function|fwnmi_get_errinfo
r_static
r_struct
id|rtas_error_log
op_star
id|fwnmi_get_errinfo
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|errdata
op_assign
id|regs-&gt;gpr
(braket
l_int|3
)braket
suffix:semicolon
r_struct
id|rtas_error_log
op_star
id|errhdr
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
op_star
id|savep
suffix:semicolon
r_if
c_cond
(paren
(paren
id|errdata
op_ge
l_int|0x7000
op_logical_and
id|errdata
OL
l_int|0x7fff0
)paren
op_logical_or
(paren
id|errdata
op_ge
id|rtas.base
op_logical_and
id|errdata
OL
id|rtas.base
op_plus
id|rtas.size
op_minus
l_int|16
)paren
)paren
(brace
id|savep
op_assign
id|__va
c_func
(paren
id|errdata
)paren
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|3
)braket
op_assign
id|savep
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* restore original r3 */
id|errhdr
op_assign
(paren
r_struct
id|rtas_error_log
op_star
)paren
(paren
id|savep
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;FWNMI: corrupt r3&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|errhdr
suffix:semicolon
)brace
multiline_comment|/* Call this when done with the data returned by FWNMI_get_errinfo.&n; * It will release the saved data area for other CPUs in the&n; * partition to receive FWNMI errors.&n; */
DECL|function|fwnmi_release_errinfo
r_static
r_void
id|fwnmi_release_errinfo
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
op_assign
id|rtas_call
c_func
(paren
id|rtas_token
c_func
(paren
l_string|&quot;ibm,nmi-interlock&quot;
)paren
comma
l_int|0
comma
l_int|1
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;FWNMI: nmi-interlock failed: %d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
)brace
DECL|function|pSeries_system_reset_exception
r_void
id|pSeries_system_reset_exception
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_if
c_cond
(paren
id|fwnmi_active
)paren
(brace
r_struct
id|rtas_error_log
op_star
id|errhdr
op_assign
id|fwnmi_get_errinfo
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|errhdr
)paren
(brace
multiline_comment|/* XXX Should look at FWNMI information */
)brace
id|fwnmi_release_errinfo
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * See if we can recover from a machine check exception.&n; * This is only called on power4 (or above) and only via&n; * the Firmware Non-Maskable Interrupts (fwnmi) handler&n; * which provides the error analysis for us.&n; *&n; * Return 1 if corrected (or delivered a signal).&n; * Return 0 if there is nothing we can do.&n; */
DECL|function|recover_mce
r_static
r_int
id|recover_mce
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|rtas_error_log
id|err
)paren
(brace
r_if
c_cond
(paren
id|err.disposition
op_eq
id|RTAS_DISP_FULLY_RECOVERED
)paren
(brace
multiline_comment|/* Platform corrected itself */
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|regs-&gt;msr
op_amp
id|MSR_RI
)paren
op_logical_and
id|user_mode
c_func
(paren
id|regs
)paren
op_logical_and
id|err.severity
op_eq
id|RTAS_SEVERITY_ERROR_SYNC
op_logical_and
id|err.disposition
op_eq
id|RTAS_DISP_NOT_RECOVERED
op_logical_and
id|err.target
op_eq
id|RTAS_TARGET_MEMORY
op_logical_and
id|err.type
op_eq
id|RTAS_TYPE_ECC_UNCORR
op_logical_and
op_logical_neg
(paren
id|current-&gt;pid
op_eq
l_int|0
op_logical_or
id|current-&gt;pid
op_eq
l_int|1
)paren
)paren
(brace
multiline_comment|/* Kill off a user process with an ECC error */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;MCE: uncorrectable ecc error for pid %d&bslash;n&quot;
comma
id|current-&gt;pid
)paren
suffix:semicolon
multiline_comment|/* XXX something better for ECC error? */
id|_exception
c_func
(paren
id|SIGBUS
comma
id|regs
comma
id|BUS_ADRERR
comma
id|regs-&gt;nip
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Handle a machine check.&n; *&n; * Note that on Power 4 and beyond Firmware Non-Maskable Interrupts (fwnmi)&n; * should be present.  If so the handler which called us tells us if the&n; * error was recovered (never true if RI=0).&n; *&n; * On hardware prior to Power 4 these exceptions were asynchronous which&n; * means we can&squot;t tell exactly where it occurred and so we can&squot;t recover.&n; */
DECL|function|pSeries_machine_check_exception
r_int
id|pSeries_machine_check_exception
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|rtas_error_log
id|err
comma
op_star
id|errp
suffix:semicolon
r_if
c_cond
(paren
id|fwnmi_active
)paren
(brace
id|errp
op_assign
id|fwnmi_get_errinfo
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|errp
)paren
id|err
op_assign
op_star
id|errp
suffix:semicolon
id|fwnmi_release_errinfo
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* frees errp */
r_if
c_cond
(paren
id|errp
op_logical_and
id|recover_mce
c_func
(paren
id|regs
comma
id|err
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
