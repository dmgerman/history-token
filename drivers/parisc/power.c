multiline_comment|/*&n; * linux/arch/parisc/kernel/power.c&n; * HP PARISC soft power switch support driver&n; *&n; * Copyright (c) 2001-2002 Helge Deller &lt;deller@gmx.de&gt;&n; * All rights reserved.&n; *&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;).&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; *&n; *&n; * &n; *  HINT:&n; *  Support of the soft power switch button may be enabled or disabled at&n; *  runtime through the &quot;/proc/sys/kernel/power&quot; procfs entry.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;asm/pdc.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/led.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#ifdef DEBUG
DECL|macro|DPRINTK
macro_line|# define DPRINTK(x) printk x
macro_line|#else
DECL|macro|DPRINTK
macro_line|# define DPRINTK(x) do { } while (0)
macro_line|#endif
multiline_comment|/* filename in /proc which can be used to enable/disable the power switch */
DECL|macro|SYSCTL_FILENAME
mdefine_line|#define SYSCTL_FILENAME&t;&t;&quot;sys/kernel/power&quot;
DECL|macro|DIAG_CODE
mdefine_line|#define DIAG_CODE(code)&t;&t;(0x14000000 + ((code)&lt;&lt;5))
multiline_comment|/* this will go to processor.h or any other place... */
multiline_comment|/* taken from PCXL ERS page 82 */
DECL|macro|MFCPU_X
mdefine_line|#define MFCPU_X(rDiagReg, t_ch, t_th, code) &bslash;&n;&t;(DIAG_CODE(code) + ((rDiagReg)&lt;&lt;21) + ((t_ch)&lt;&lt;16) + ((t_th)&lt;&lt;0) )
DECL|macro|MTCPU
mdefine_line|#define MTCPU(dr, gr)&t;&t;MFCPU_X(dr, gr,  0, 0x12)       /* move value of gr to dr[dr] */
DECL|macro|MFCPU_C
mdefine_line|#define MFCPU_C(dr, gr)&t;&t;MFCPU_X(dr, gr,  0, 0x30)&t;/* for dr0 and dr8 only ! */
DECL|macro|MFCPU_T
mdefine_line|#define MFCPU_T(dr, gr)&t;&t;MFCPU_X(dr,  0, gr, 0xa0)&t;/* all dr except dr0 and dr8 */
DECL|macro|__getDIAG
mdefine_line|#define __getDIAG(dr) ( { &t;&t;&t;&bslash;&n;        register unsigned long __res asm(&quot;r28&quot;);&bslash;&n;&t; __asm__ __volatile__ (&t;&t;&t;&bslash;&n;&t;&t;&quot;.word %1&bslash;n nop&bslash;n&quot; : &quot;=&amp;r&quot; (__res) : &quot;i&quot; (MFCPU_T(dr,28)) &bslash;&n;&t;);&t;&t;&t;&t;&t;&bslash;&n;&t;__res;&t;&t;&t;&t;&t;&bslash;&n;} )
DECL|function|deferred_poweroff
r_static
r_void
id|deferred_poweroff
c_func
(paren
r_void
op_star
id|dummy
)paren
(brace
r_extern
r_int
id|cad_pid
suffix:semicolon
multiline_comment|/* from kernel/sys.c */
r_if
c_cond
(paren
id|kill_proc
c_func
(paren
id|cad_pid
comma
id|SIGINT
comma
l_int|1
)paren
)paren
(brace
multiline_comment|/* just in case killing init process failed */
id|machine_power_off
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * This function gets called from interrupt context.&n; * As it&squot;s called within an interrupt, it wouldn&squot;t sync if we don&squot;t&n; * use schedule_work().&n; */
r_static
id|DECLARE_WORK
c_func
(paren
id|poweroff_work
comma
id|deferred_poweroff
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|poweroff
r_static
r_void
id|poweroff
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|powering_off
suffix:semicolon
r_if
c_cond
(paren
id|powering_off
)paren
r_return
suffix:semicolon
id|powering_off
op_increment
suffix:semicolon
id|schedule_work
c_func
(paren
op_amp
id|poweroff_work
)paren
suffix:semicolon
)brace
multiline_comment|/* local time-counter for shutdown */
DECL|variable|shutdown_timer
r_static
r_int
id|shutdown_timer
suffix:semicolon
multiline_comment|/* check, give feedback and start shutdown after one second */
DECL|function|process_shutdown
r_static
r_void
id|process_shutdown
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|shutdown_timer
op_eq
l_int|0
)paren
id|DPRINTK
c_func
(paren
(paren
id|KERN_INFO
l_string|&quot;Shutdown requested...&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|shutdown_timer
op_increment
suffix:semicolon
multiline_comment|/* wait until the button was pressed for 1 second */
r_if
c_cond
(paren
id|shutdown_timer
op_eq
id|HZ
)paren
(brace
r_static
r_char
id|msg
(braket
)braket
op_assign
l_string|&quot;Shutting down...&quot;
suffix:semicolon
id|DPRINTK
c_func
(paren
(paren
id|KERN_INFO
l_string|&quot;%s&bslash;n&quot;
comma
id|msg
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CHASSIS_LCD_LED
id|lcd_print
c_func
(paren
id|msg
)paren
suffix:semicolon
macro_line|#endif
id|poweroff
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* main power switch tasklet struct (scheduled from time.c) */
id|DECLARE_TASKLET_DISABLED
c_func
(paren
id|power_tasklet
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* soft power switch enabled/disabled */
macro_line|#ifdef CONFIG_PROC_FS
DECL|variable|pwrsw_enabled
r_static
r_int
id|pwrsw_enabled
op_assign
l_int|1
suffix:semicolon
macro_line|#else
DECL|macro|pwrsw_enabled
mdefine_line|#define pwrsw_enabled (1)
macro_line|#endif
multiline_comment|/*&n; * On gecko style machines (e.g. 712/xx and 715/xx) &n; * the power switch status is stored in Bit 0 (&quot;the highest bit&quot;)&n; * of CPU diagnose register 25.&n; * &n; */
DECL|function|gecko_tasklet_func
r_static
r_void
id|gecko_tasklet_func
c_func
(paren
r_int
r_int
id|unused
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pwrsw_enabled
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|__getDIAG
c_func
(paren
l_int|25
)paren
op_amp
l_int|0x80000000
)paren
(brace
multiline_comment|/* power switch button not pressed or released again */
multiline_comment|/* Warning: Some machines do never reset this DIAG flag! */
id|shutdown_timer
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|process_shutdown
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Check the power switch status which is read from the&n; * real I/O location at soft_power_reg.&n; * Bit 31 (&quot;the lowest bit) is the status of the power switch.&n; */
DECL|function|polling_tasklet_func
r_static
r_void
id|polling_tasklet_func
c_func
(paren
r_int
r_int
id|soft_power_reg
)paren
(brace
r_int
r_int
id|current_status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pwrsw_enabled
)paren
r_return
suffix:semicolon
id|current_status
op_assign
id|gsc_readl
c_func
(paren
id|soft_power_reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current_status
op_amp
l_int|0x1
)paren
(brace
multiline_comment|/* power switch button not pressed */
id|shutdown_timer
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|process_shutdown
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * powerfail interruption handler (irq IRQ_FROM_REGION(CPU_IRQ_REGION)+2) &n; */
macro_line|#if 0
r_static
r_void
id|powerfail_interrupt
c_func
(paren
r_int
id|code
comma
r_void
op_star
id|x
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;POWERFAIL INTERRUPTION !&bslash;n&quot;
)paren
suffix:semicolon
id|poweroff
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* &n; * /proc filesystem support &n; */
macro_line|#ifdef CONFIG_SYSCTL
DECL|function|power_proc_read
r_static
r_int
id|power_proc_read
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_char
op_star
id|out
op_assign
id|page
suffix:semicolon
r_int
id|len
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;Software power switch support: &quot;
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
id|pwrsw_enabled
ques
c_cond
l_string|&quot;enabled (1)&quot;
suffix:colon
l_string|&quot;disabled (0)&quot;
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|len
op_assign
id|out
op_minus
id|page
op_minus
id|off
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|count
)paren
(brace
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|len
op_assign
id|count
suffix:semicolon
)brace
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|power_proc_write
r_static
r_int
id|power_proc_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
(brace
r_char
op_star
id|cur
comma
id|lbuf
(braket
id|count
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
id|memset
c_func
(paren
id|lbuf
comma
l_int|0
comma
id|count
)paren
suffix:semicolon
id|copy_from_user
c_func
(paren
id|lbuf
comma
id|buf
comma
id|count
)paren
suffix:semicolon
id|cur
op_assign
id|lbuf
suffix:semicolon
multiline_comment|/* skip initial spaces */
r_while
c_loop
(paren
op_star
id|cur
op_logical_and
id|isspace
c_func
(paren
op_star
id|cur
)paren
)paren
id|cur
op_increment
suffix:semicolon
r_switch
c_cond
(paren
op_star
id|cur
)paren
(brace
r_case
l_char|&squot;0&squot;
suffix:colon
id|pwrsw_enabled
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;1&squot;
suffix:colon
id|pwrsw_enabled
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;/proc/&quot;
id|SYSCTL_FILENAME
l_string|&quot;: Parse error: only &squot;0&squot; or &squot;1&squot; allowed!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* switch() */
r_return
id|count
suffix:semicolon
)brace
DECL|variable|ent
r_static
r_struct
id|proc_dir_entry
op_star
id|ent
suffix:semicolon
DECL|function|power_create_procfs
r_static
r_void
id|__init
id|power_create_procfs
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|power_tasklet.func
)paren
r_return
suffix:semicolon
id|ent
op_assign
id|create_proc_entry
c_func
(paren
id|SYSCTL_FILENAME
comma
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ent
)paren
r_return
suffix:semicolon
id|ent-&gt;nlink
op_assign
l_int|1
suffix:semicolon
id|ent-&gt;read_proc
op_assign
id|power_proc_read
suffix:semicolon
id|ent-&gt;write_proc
op_assign
id|power_proc_write
suffix:semicolon
id|ent-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
)brace
DECL|function|power_remove_procfs
r_static
r_void
id|__exit
id|power_remove_procfs
c_func
(paren
r_void
)paren
(brace
id|remove_proc_entry
c_func
(paren
id|SYSCTL_FILENAME
comma
l_int|NULL
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|power_create_procfs
mdefine_line|#define power_create_procfs()&t;do { } while (0)
DECL|macro|power_remove_procfs
mdefine_line|#define power_remove_procfs()&t;do { } while (0)
macro_line|#endif&t;/* CONFIG_SYSCTL */
multiline_comment|/* parisc_panic_event() is called by the panic handler.&n; * As soon as a panic occurs, our tasklets above will not be&n; * executed any longer. This function then re-enables the &n; * soft-power switch and allows the user to switch off the system&n; */
DECL|function|parisc_panic_event
r_static
r_int
id|parisc_panic_event
c_func
(paren
r_struct
id|notifier_block
op_star
id|this
comma
r_int
r_int
id|event
comma
r_void
op_star
id|ptr
)paren
(brace
multiline_comment|/* re-enable the soft-power switch */
id|pdc_soft_power_button
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
DECL|variable|parisc_panic_block
r_static
r_struct
id|notifier_block
id|parisc_panic_block
op_assign
(brace
dot
id|notifier_call
op_assign
id|parisc_panic_event
comma
dot
id|priority
op_assign
id|INT_MAX
comma
)brace
suffix:semicolon
DECL|function|power_init
r_static
r_int
id|__init
id|power_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|ret
suffix:semicolon
r_int
r_int
id|soft_power_reg
op_assign
l_int|0
suffix:semicolon
macro_line|#if 0
id|request_irq
c_func
(paren
id|IRQ_FROM_REGION
c_func
(paren
id|CPU_IRQ_REGION
)paren
op_plus
l_int|2
comma
op_amp
id|powerfail_interrupt
comma
l_int|0
comma
l_string|&quot;powerfail&quot;
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* enable the soft power switch if possible */
id|ret
op_assign
id|pdc_soft_power_info
c_func
(paren
op_amp
id|soft_power_reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|PDC_OK
)paren
id|ret
op_assign
id|pdc_soft_power_button
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|PDC_OK
)paren
id|soft_power_reg
op_assign
op_minus
l_int|1UL
suffix:semicolon
r_switch
c_cond
(paren
id|soft_power_reg
)paren
(brace
r_case
l_int|0
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Gecko-style soft power switch enabled.&bslash;n&quot;
)paren
suffix:semicolon
id|power_tasklet.func
op_assign
id|gecko_tasklet_func
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|1UL
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Soft power switch support not available.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Soft power switch enabled, polling @ 0x%08lx.&bslash;n&quot;
comma
id|soft_power_reg
)paren
suffix:semicolon
id|power_tasklet.data
op_assign
id|soft_power_reg
suffix:semicolon
id|power_tasklet.func
op_assign
id|polling_tasklet_func
suffix:semicolon
)brace
multiline_comment|/* Register a call for panic conditions. */
id|notifier_chain_register
c_func
(paren
op_amp
id|panic_notifier_list
comma
op_amp
id|parisc_panic_block
)paren
suffix:semicolon
id|power_create_procfs
c_func
(paren
)paren
suffix:semicolon
id|tasklet_enable
c_func
(paren
op_amp
id|power_tasklet
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|power_exit
r_static
r_void
id|__exit
id|power_exit
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|power_tasklet.func
)paren
r_return
suffix:semicolon
id|tasklet_disable
c_func
(paren
op_amp
id|power_tasklet
)paren
suffix:semicolon
id|notifier_chain_unregister
c_func
(paren
op_amp
id|panic_notifier_list
comma
op_amp
id|parisc_panic_block
)paren
suffix:semicolon
id|power_remove_procfs
c_func
(paren
)paren
suffix:semicolon
id|power_tasklet.func
op_assign
l_int|NULL
suffix:semicolon
id|pdc_soft_power_button
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|power_init
id|module_init
c_func
(paren
id|power_init
)paren
suffix:semicolon
DECL|variable|power_exit
id|module_exit
c_func
(paren
id|power_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Helge Deller&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Soft power switch driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;Dual BSD/GPL&quot;
)paren
suffix:semicolon
id|EXPORT_NO_SYMBOLS
suffix:semicolon
eof
