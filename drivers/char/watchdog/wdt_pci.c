multiline_comment|/*&n; *&t;Industrial Computer Source PCI-WDT500/501 driver&n; *&n; *&t;(c) Copyright 1996-1997 Alan Cox &lt;alan@redhat.com&gt;, All Rights Reserved.&n; *&t;&t;&t;&t;http://www.redhat.com&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;Neither Alan Cox nor CymruNet Ltd. admit liability nor provide&n; *&t;warranty for any of this software. This material is provided&n; *&t;&quot;AS-IS&quot; and at no charge.&n; *&n; *&t;(c) Copyright 1995    Alan Cox &lt;alan@lxorguk.ukuu.org.uk&gt;&n; *&n; *&t;Release 0.10.&n; *&n; *&t;Fixes&n; *&t;&t;Dave Gregorich&t;:&t;Modularisation and minor bugs&n; *&t;&t;Alan Cox&t;:&t;Added the watchdog ioctl() stuff&n; *&t;&t;Alan Cox&t;:&t;Fixed the reboot problem (as noted by&n; *&t;&t;&t;&t;&t;Matt Crocker).&n; *&t;&t;Alan Cox&t;:&t;Added wdt= boot option&n; *&t;&t;Alan Cox&t;:&t;Cleaned up copy/user stuff&n; *&t;&t;Tim Hockin&t;:&t;Added insmod parameters, comment cleanup&n; *&t;&t;&t;&t;&t;Parameterized timeout&n; *&t;&t;JP Nollmann&t;:&t;Added support for PCI wdt501p&n; *&t;&t;Alan Cox&t;:&t;Split ISA and PCI cards into two drivers&n; *&t;&t;Jeff Garzik&t;:&t;PCI cleanups&n; *&t;&t;Tigran Aivazian&t;:&t;Restructured wdtpci_init_one() to handle failures&n; *&t;&t;Joel Becker &t;:&t;Added WDIOC_GET/SETTIMEOUT&n; *&t;&t;Zwane Mwaikambo&t;:&t;Magic char closing, locking changes, cleanups&n; *&t;&t;Matt Domsch&t;:&t;nowayout module option&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|WDT_IS_PCI
mdefine_line|#define WDT_IS_PCI
macro_line|#include &quot;wd501p.h&quot;
DECL|macro|PFX
mdefine_line|#define PFX &quot;wdt_pci: &quot;
multiline_comment|/*&n; * Until Access I/O gets their application for a PCI vendor ID approved,&n; * I don&squot;t think that it&squot;s appropriate to move these constants into the&n; * regular pci_ids.h file. -- JPN 2000/01/18&n; */
macro_line|#ifndef PCI_VENDOR_ID_ACCESSIO
DECL|macro|PCI_VENDOR_ID_ACCESSIO
mdefine_line|#define PCI_VENDOR_ID_ACCESSIO 0x494f
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_WDG_CSM
DECL|macro|PCI_DEVICE_ID_WDG_CSM
mdefine_line|#define PCI_DEVICE_ID_WDG_CSM 0x22c0
macro_line|#endif
multiline_comment|/* We can only use 1 card due to the /dev/watchdog restriction */
DECL|variable|dev_count
r_static
r_int
id|dev_count
suffix:semicolon
DECL|variable|open_sem
r_static
r_struct
id|semaphore
id|open_sem
suffix:semicolon
DECL|variable|wdtpci_lock
r_static
id|spinlock_t
id|wdtpci_lock
suffix:semicolon
DECL|variable|expect_close
r_static
r_char
id|expect_close
suffix:semicolon
DECL|variable|io
r_static
r_int
id|io
suffix:semicolon
DECL|variable|irq
r_static
r_int
id|irq
suffix:semicolon
multiline_comment|/* Default timeout */
DECL|macro|WD_TIMO
mdefine_line|#define WD_TIMO 60&t;&t;&t;/* Default heartbeat = 60 seconds */
DECL|variable|heartbeat
r_static
r_int
id|heartbeat
op_assign
id|WD_TIMO
suffix:semicolon
DECL|variable|wd_heartbeat
r_static
r_int
id|wd_heartbeat
suffix:semicolon
id|module_param
c_func
(paren
id|heartbeat
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|heartbeat
comma
l_string|&quot;Watchdog heartbeat in seconds. (0&lt;heartbeat&lt;65536, default=&quot;
id|__MODULE_STRING
c_func
(paren
id|WD_TIMO
)paren
l_string|&quot;)&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_WATCHDOG_NOWAYOUT
DECL|variable|nowayout
r_static
r_int
id|nowayout
op_assign
l_int|1
suffix:semicolon
macro_line|#else
DECL|variable|nowayout
r_static
r_int
id|nowayout
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|module_param
c_func
(paren
id|nowayout
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|nowayout
comma
l_string|&quot;Watchdog cannot be stopped once started (default=CONFIG_WATCHDOG_NOWAYOUT)&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_WDT_501_PCI
multiline_comment|/* Support for the Fan Tachometer on the PCI-WDT501 */
DECL|variable|tachometer
r_static
r_int
id|tachometer
suffix:semicolon
id|module_param
c_func
(paren
id|tachometer
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|tachometer
comma
l_string|&quot;PCI-WDT501 Fan Tachometer support (0=disable, default=0)&quot;
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_WDT_501_PCI */
multiline_comment|/*&n; *&t;Programming support&n; */
DECL|function|wdtpci_ctr_mode
r_static
r_void
id|wdtpci_ctr_mode
c_func
(paren
r_int
id|ctr
comma
r_int
id|mode
)paren
(brace
id|ctr
op_lshift_assign
l_int|6
suffix:semicolon
id|ctr
op_or_assign
l_int|0x30
suffix:semicolon
id|ctr
op_or_assign
(paren
id|mode
op_lshift
l_int|1
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|ctr
comma
id|WDT_CR
)paren
suffix:semicolon
)brace
DECL|function|wdtpci_ctr_load
r_static
r_void
id|wdtpci_ctr_load
c_func
(paren
r_int
id|ctr
comma
r_int
id|val
)paren
(brace
id|outb_p
c_func
(paren
id|val
op_amp
l_int|0xFF
comma
id|WDT_COUNT0
op_plus
id|ctr
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|val
op_rshift
l_int|8
comma
id|WDT_COUNT0
op_plus
id|ctr
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;wdtpci_start:&n; *&n; *&t;Start the watchdog driver.&n; */
DECL|function|wdtpci_start
r_static
r_int
id|wdtpci_start
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|wdtpci_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * &quot;pet&quot; the watchdog, as Access says.&n;&t; * This resets the clock outputs.&n;&t; */
id|inb_p
c_func
(paren
id|WDT_DC
)paren
suffix:semicolon
multiline_comment|/* Disable watchdog */
id|wdtpci_ctr_mode
c_func
(paren
l_int|2
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Program CTR2 for Mode 0: Pulse on Terminal Count */
id|outb_p
c_func
(paren
l_int|0
comma
id|WDT_DC
)paren
suffix:semicolon
multiline_comment|/* Enable watchdog */
id|inb_p
c_func
(paren
id|WDT_DC
)paren
suffix:semicolon
multiline_comment|/* Disable watchdog */
id|outb_p
c_func
(paren
l_int|0
comma
id|WDT_CLOCK
)paren
suffix:semicolon
multiline_comment|/* 2.0833MHz clock */
id|inb_p
c_func
(paren
id|WDT_BUZZER
)paren
suffix:semicolon
multiline_comment|/* disable */
id|inb_p
c_func
(paren
id|WDT_OPTONOTRST
)paren
suffix:semicolon
multiline_comment|/* disable */
id|inb_p
c_func
(paren
id|WDT_OPTORST
)paren
suffix:semicolon
multiline_comment|/* disable */
id|inb_p
c_func
(paren
id|WDT_PROGOUT
)paren
suffix:semicolon
multiline_comment|/* disable */
id|wdtpci_ctr_mode
c_func
(paren
l_int|0
comma
l_int|3
)paren
suffix:semicolon
multiline_comment|/* Program CTR0 for Mode 3: Square Wave Generator */
id|wdtpci_ctr_mode
c_func
(paren
l_int|1
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* Program CTR1 for Mode 2: Rate Generator */
id|wdtpci_ctr_mode
c_func
(paren
l_int|2
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Program CTR2 for Mode 1: Retriggerable One-Shot */
id|wdtpci_ctr_load
c_func
(paren
l_int|0
comma
l_int|20833
)paren
suffix:semicolon
multiline_comment|/* count at 100Hz */
id|wdtpci_ctr_load
c_func
(paren
l_int|1
comma
id|wd_heartbeat
)paren
suffix:semicolon
multiline_comment|/* Heartbeat */
multiline_comment|/* DO NOT LOAD CTR2 on PCI card! -- JPN */
id|outb_p
c_func
(paren
l_int|0
comma
id|WDT_DC
)paren
suffix:semicolon
multiline_comment|/* Enable watchdog */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|wdtpci_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;wdtpci_stop:&n; *&n; *&t;Stop the watchdog driver.&n; */
DECL|function|wdtpci_stop
r_static
r_int
id|wdtpci_stop
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Turn the card off */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|wdtpci_lock
comma
id|flags
)paren
suffix:semicolon
id|inb_p
c_func
(paren
id|WDT_DC
)paren
suffix:semicolon
multiline_comment|/* Disable watchdog */
id|wdtpci_ctr_load
c_func
(paren
l_int|2
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* 0 length reset pulses now */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|wdtpci_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;wdtpci_ping:&n; *&n; *&t;Reload counter one with the watchdog heartbeat. We don&squot;t bother reloading&n; *&t;the cascade counter.&n; */
DECL|function|wdtpci_ping
r_static
r_int
id|wdtpci_ping
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Write a watchdog value */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|wdtpci_lock
comma
id|flags
)paren
suffix:semicolon
id|inb_p
c_func
(paren
id|WDT_DC
)paren
suffix:semicolon
multiline_comment|/* Disable watchdog */
id|wdtpci_ctr_mode
c_func
(paren
l_int|1
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* Re-Program CTR1 for Mode 2: Rate Generator */
id|wdtpci_ctr_load
c_func
(paren
l_int|1
comma
id|wd_heartbeat
)paren
suffix:semicolon
multiline_comment|/* Heartbeat */
id|outb_p
c_func
(paren
l_int|0
comma
id|WDT_DC
)paren
suffix:semicolon
multiline_comment|/* Enable watchdog */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|wdtpci_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;wdtpci_set_heartbeat:&n; *&t;@t:&t;&t;the new heartbeat value that needs to be set.&n; *&n; *&t;Set a new heartbeat value for the watchdog device. If the heartbeat value is&n; *&t;incorrect we keep the old value and return -EINVAL. If successfull we&n; *&t;return 0.&n; */
DECL|function|wdtpci_set_heartbeat
r_static
r_int
id|wdtpci_set_heartbeat
c_func
(paren
r_int
id|t
)paren
(brace
multiline_comment|/* Arbitrary, can&squot;t find the card&squot;s limits */
r_if
c_cond
(paren
(paren
id|t
OL
l_int|1
)paren
op_logical_or
(paren
id|t
OG
l_int|65535
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|heartbeat
op_assign
id|t
suffix:semicolon
id|wd_heartbeat
op_assign
id|t
op_star
l_int|100
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;wdtpci_get_status:&n; *&t;@status:&t;&t;the new status.&n; *&n; *&t;Extract the status information from a WDT watchdog device. There are&n; *&t;several board variants so we have to know which bits are valid. Some&n; *&t;bits default to one and some to zero in order to be maximally painful.&n; *&n; *&t;we then map the bits onto the status ioctl flags.&n; */
DECL|function|wdtpci_get_status
r_static
r_int
id|wdtpci_get_status
c_func
(paren
r_int
op_star
id|status
)paren
(brace
r_int
r_char
id|new_status
op_assign
id|inb_p
c_func
(paren
id|WDT_SR
)paren
suffix:semicolon
op_star
id|status
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|new_status
op_amp
id|WDC_SR_ISOI0
)paren
op_star
id|status
op_or_assign
id|WDIOF_EXTERN1
suffix:semicolon
r_if
c_cond
(paren
id|new_status
op_amp
id|WDC_SR_ISII1
)paren
op_star
id|status
op_or_assign
id|WDIOF_EXTERN2
suffix:semicolon
macro_line|#ifdef CONFIG_WDT_501_PCI
r_if
c_cond
(paren
op_logical_neg
(paren
id|new_status
op_amp
id|WDC_SR_TGOOD
)paren
)paren
op_star
id|status
op_or_assign
id|WDIOF_OVERHEAT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|new_status
op_amp
id|WDC_SR_PSUOVER
)paren
)paren
op_star
id|status
op_or_assign
id|WDIOF_POWEROVER
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|new_status
op_amp
id|WDC_SR_PSUUNDR
)paren
)paren
op_star
id|status
op_or_assign
id|WDIOF_POWERUNDER
suffix:semicolon
r_if
c_cond
(paren
id|tachometer
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|new_status
op_amp
id|WDC_SR_FANGOOD
)paren
)paren
op_star
id|status
op_or_assign
id|WDIOF_FANFAULT
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_WDT_501_PCI */
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_WDT_501_PCI
multiline_comment|/**&n; *&t;wdtpci_get_temperature:&n; *&n; *&t;Reports the temperature in degrees Fahrenheit. The API is in&n; *&t;farenheit. It was designed by an imperial measurement luddite.&n; */
DECL|function|wdtpci_get_temperature
r_static
r_int
id|wdtpci_get_temperature
c_func
(paren
r_int
op_star
id|temperature
)paren
(brace
r_int
r_int
id|c
op_assign
id|inb_p
c_func
(paren
id|WDT_RT
)paren
suffix:semicolon
op_star
id|temperature
op_assign
(paren
id|c
op_star
l_int|11
op_div
l_int|15
)paren
op_plus
l_int|7
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_WDT_501_PCI */
multiline_comment|/**&n; *&t;wdtpci_interrupt:&n; *&t;@irq:&t;&t;Interrupt number&n; *&t;@dev_id:&t;Unused as we don&squot;t allow multiple devices.&n; *&t;@regs:&t;&t;Unused.&n; *&n; *&t;Handle an interrupt from the board. These are raised when the status&n; *&t;map changes in what the board considers an interesting way. That means&n; *&t;a failure condition occurring.&n; */
DECL|function|wdtpci_interrupt
r_static
id|irqreturn_t
id|wdtpci_interrupt
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
multiline_comment|/*&n;&t; *&t;Read the status register see what is up and&n;&t; *&t;then printk it.&n;&t; */
r_int
r_char
id|status
op_assign
id|inb_p
c_func
(paren
id|WDT_SR
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
id|PFX
l_string|&quot;status %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_WDT_501_PCI
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|WDC_SR_TGOOD
)paren
)paren
id|printk
c_func
(paren
id|KERN_CRIT
id|PFX
l_string|&quot;Overheat alarm.(%d)&bslash;n&quot;
comma
id|inb_p
c_func
(paren
id|WDT_RT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|WDC_SR_PSUOVER
)paren
)paren
id|printk
c_func
(paren
id|KERN_CRIT
id|PFX
l_string|&quot;PSU over voltage.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|WDC_SR_PSUUNDR
)paren
)paren
id|printk
c_func
(paren
id|KERN_CRIT
id|PFX
l_string|&quot;PSU under voltage.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tachometer
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|WDC_SR_FANGOOD
)paren
)paren
id|printk
c_func
(paren
id|KERN_CRIT
id|PFX
l_string|&quot;Possible fan fault.&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_WDT_501_PCI */
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|WDC_SR_WCCR
)paren
)paren
macro_line|#ifdef SOFTWARE_REBOOT
macro_line|#ifdef ONLY_TESTING
id|printk
c_func
(paren
id|KERN_CRIT
id|PFX
l_string|&quot;Would Reboot.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
id|KERN_CRIT
id|PFX
l_string|&quot;Initiating system reboot.&bslash;n&quot;
)paren
suffix:semicolon
id|machine_restart
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
macro_line|#else
id|printk
c_func
(paren
id|KERN_CRIT
id|PFX
l_string|&quot;Reset in 5ms.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;wdtpci_write:&n; *&t;@file: file handle to the watchdog&n; *&t;@buf: buffer to write (unused as data does not matter here&n; *&t;@count: count of bytes&n; *&t;@ppos: pointer to the position to write. No seeks allowed&n; *&n; *&t;A write to a watchdog device is defined as a keepalive signal. Any&n; *&t;write of data will do, as we we don&squot;t define content meaning.&n; */
DECL|function|wdtpci_write
r_static
id|ssize_t
id|wdtpci_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_if
c_cond
(paren
id|count
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|nowayout
)paren
(brace
r_int
id|i
suffix:semicolon
id|expect_close
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_ne
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|c
comma
id|buf
op_plus
id|i
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;V&squot;
)paren
id|expect_close
op_assign
l_int|42
suffix:semicolon
)brace
)brace
id|wdtpci_ping
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;wdtpci_ioctl:&n; *&t;@inode: inode of the device&n; *&t;@file: file handle to the device&n; *&t;@cmd: watchdog command&n; *&t;@arg: argument pointer&n; *&n; *&t;The watchdog API defines a common set of functions for all watchdogs&n; *&t;according to their available features. We only actually usefully support&n; *&t;querying capabilities and current status.&n; */
DECL|function|wdtpci_ioctl
r_static
r_int
id|wdtpci_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|new_heartbeat
suffix:semicolon
r_int
id|status
suffix:semicolon
r_void
id|__user
op_star
id|argp
op_assign
(paren
r_void
id|__user
op_star
)paren
id|arg
suffix:semicolon
r_int
id|__user
op_star
id|p
op_assign
id|argp
suffix:semicolon
r_static
r_struct
id|watchdog_info
id|ident
op_assign
(brace
dot
id|options
op_assign
id|WDIOF_SETTIMEOUT
op_or
id|WDIOF_MAGICCLOSE
op_or
id|WDIOF_KEEPALIVEPING
comma
dot
id|firmware_version
op_assign
l_int|1
comma
dot
id|identity
op_assign
l_string|&quot;PCI-WDT500/501&quot;
comma
)brace
suffix:semicolon
multiline_comment|/* Add options according to the card we have */
id|ident.options
op_or_assign
(paren
id|WDIOF_EXTERN1
op_or
id|WDIOF_EXTERN2
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_WDT_501_PCI
id|ident.options
op_or_assign
(paren
id|WDIOF_OVERHEAT
op_or
id|WDIOF_POWERUNDER
op_or
id|WDIOF_POWEROVER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tachometer
)paren
id|ident.options
op_or_assign
id|WDIOF_FANFAULT
suffix:semicolon
macro_line|#endif /* CONFIG_WDT_501_PCI */
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
r_case
id|WDIOC_GETSUPPORT
suffix:colon
r_return
id|copy_to_user
c_func
(paren
id|argp
comma
op_amp
id|ident
comma
r_sizeof
(paren
id|ident
)paren
)paren
ques
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|WDIOC_GETSTATUS
suffix:colon
id|wdtpci_get_status
c_func
(paren
op_amp
id|status
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|status
comma
id|p
)paren
suffix:semicolon
r_case
id|WDIOC_GETBOOTSTATUS
suffix:colon
r_return
id|put_user
c_func
(paren
l_int|0
comma
id|p
)paren
suffix:semicolon
r_case
id|WDIOC_KEEPALIVE
suffix:colon
id|wdtpci_ping
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|WDIOC_SETTIMEOUT
suffix:colon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|new_heartbeat
comma
id|p
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|wdtpci_set_heartbeat
c_func
(paren
id|new_heartbeat
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|wdtpci_ping
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Fall */
r_case
id|WDIOC_GETTIMEOUT
suffix:colon
r_return
id|put_user
c_func
(paren
id|heartbeat
comma
id|p
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;wdtpci_open:&n; *&t;@inode: inode of device&n; *&t;@file: file handle to device&n; *&n; *&t;The watchdog device has been opened. The watchdog device is single&n; *&t;open and on opening we load the counters. Counter zero is a 100Hz&n; *&t;cascade, into counter 1 which downcounts to reboot. When the counter&n; *&t;triggers counter 2 downcounts the length of the reset pulse which&n; *&t;set set to be as long as possible.&n; */
DECL|function|wdtpci_open
r_static
r_int
id|wdtpci_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_if
c_cond
(paren
id|down_trylock
c_func
(paren
op_amp
id|open_sem
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|nowayout
)paren
(brace
id|__module_get
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Activate&n;&t; */
id|wdtpci_start
c_func
(paren
)paren
suffix:semicolon
r_return
id|nonseekable_open
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;wdtpci_release:&n; *&t;@inode: inode to board&n; *&t;@file: file handle to board&n; *&n; *&t;The watchdog has a configurable API. There is a religious dispute&n; *&t;between people who want their watchdog to be able to shut down and&n; *&t;those who want to be sure if the watchdog manager dies the machine&n; *&t;reboots. In the former case we disable the counters, in the latter&n; *&t;case you have to open it again very soon.&n; */
DECL|function|wdtpci_release
r_static
r_int
id|wdtpci_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_if
c_cond
(paren
id|expect_close
op_eq
l_int|42
)paren
(brace
id|wdtpci_stop
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_CRIT
id|PFX
l_string|&quot;Unexpected close, not stopping timer!&quot;
)paren
suffix:semicolon
id|wdtpci_ping
c_func
(paren
)paren
suffix:semicolon
)brace
id|expect_close
op_assign
l_int|0
suffix:semicolon
id|up
c_func
(paren
op_amp
id|open_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_WDT_501_PCI
multiline_comment|/**&n; *&t;wdtpci_temp_read:&n; *&t;@file: file handle to the watchdog board&n; *&t;@buf: buffer to write 1 byte into&n; *&t;@count: length of buffer&n; *&t;@ptr: offset (no seek allowed)&n; *&n; *&t;Read reports the temperature in degrees Fahrenheit. The API is in&n; *&t;fahrenheit. It was designed by an imperial measurement luddite.&n; */
DECL|function|wdtpci_temp_read
r_static
id|ssize_t
id|wdtpci_temp_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ptr
)paren
(brace
r_int
id|temperature
suffix:semicolon
r_if
c_cond
(paren
id|wdtpci_get_temperature
c_func
(paren
op_amp
id|temperature
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
(paren
id|buf
comma
op_amp
id|temperature
comma
l_int|1
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;wdtpci_temp_open:&n; *&t;@inode: inode of device&n; *&t;@file: file handle to device&n; *&n; *&t;The temperature device has been opened.&n; */
DECL|function|wdtpci_temp_open
r_static
r_int
id|wdtpci_temp_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
id|nonseekable_open
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;wdtpci_temp_release:&n; *&t;@inode: inode to board&n; *&t;@file: file handle to board&n; *&n; *&t;The temperature device has been closed.&n; */
DECL|function|wdtpci_temp_release
r_static
r_int
id|wdtpci_temp_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_WDT_501_PCI */
multiline_comment|/**&n; *&t;notify_sys:&n; *&t;@this: our notifier block&n; *&t;@code: the event being reported&n; *&t;@unused: unused&n; *&n; *&t;Our notifier is called on system shutdowns. We want to turn the card&n; *&t;off at reboot otherwise the machine will reboot again during memory&n; *&t;test or worse yet during the following fsck. This would suck, in fact&n; *&t;trust me - if it happens it does suck.&n; */
DECL|function|wdtpci_notify_sys
r_static
r_int
id|wdtpci_notify_sys
c_func
(paren
r_struct
id|notifier_block
op_star
id|this
comma
r_int
r_int
id|code
comma
r_void
op_star
id|unused
)paren
(brace
r_if
c_cond
(paren
id|code
op_eq
id|SYS_DOWN
op_logical_or
id|code
op_eq
id|SYS_HALT
)paren
(brace
multiline_comment|/* Turn the card off */
id|wdtpci_stop
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Kernel Interfaces&n; */
DECL|variable|wdtpci_fops
r_static
r_struct
id|file_operations
id|wdtpci_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|llseek
op_assign
id|no_llseek
comma
dot
id|write
op_assign
id|wdtpci_write
comma
dot
id|ioctl
op_assign
id|wdtpci_ioctl
comma
dot
id|open
op_assign
id|wdtpci_open
comma
dot
id|release
op_assign
id|wdtpci_release
comma
)brace
suffix:semicolon
DECL|variable|wdtpci_miscdev
r_static
r_struct
id|miscdevice
id|wdtpci_miscdev
op_assign
(brace
dot
id|minor
op_assign
id|WATCHDOG_MINOR
comma
dot
id|name
op_assign
l_string|&quot;watchdog&quot;
comma
dot
id|fops
op_assign
op_amp
id|wdtpci_fops
comma
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_WDT_501_PCI
DECL|variable|wdtpci_temp_fops
r_static
r_struct
id|file_operations
id|wdtpci_temp_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|llseek
op_assign
id|no_llseek
comma
dot
id|read
op_assign
id|wdtpci_temp_read
comma
dot
id|open
op_assign
id|wdtpci_temp_open
comma
dot
id|release
op_assign
id|wdtpci_temp_release
comma
)brace
suffix:semicolon
DECL|variable|temp_miscdev
r_static
r_struct
id|miscdevice
id|temp_miscdev
op_assign
(brace
dot
id|minor
op_assign
id|TEMP_MINOR
comma
dot
id|name
op_assign
l_string|&quot;temperature&quot;
comma
dot
id|fops
op_assign
op_amp
id|wdtpci_temp_fops
comma
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_WDT_501_PCI */
multiline_comment|/*&n; *&t;The WDT card needs to learn about soft shutdowns in order to&n; *&t;turn the timebomb registers off.&n; */
DECL|variable|wdtpci_notifier
r_static
r_struct
id|notifier_block
id|wdtpci_notifier
op_assign
(brace
dot
id|notifier_call
op_assign
id|wdtpci_notify_sys
comma
)brace
suffix:semicolon
DECL|function|wdtpci_init_one
r_static
r_int
id|__devinit
id|wdtpci_init_one
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_struct
id|pci_device_id
op_star
id|ent
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
id|dev_count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|dev_count
OG
l_int|1
)paren
(brace
id|printk
(paren
id|KERN_ERR
id|PFX
l_string|&quot;this driver only supports 1 device&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pci_enable_device
(paren
id|dev
)paren
)paren
(brace
id|printk
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Not possible to enable PCI Device&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pci_resource_start
(paren
id|dev
comma
l_int|2
)paren
op_eq
l_int|0x0000
)paren
(brace
id|printk
(paren
id|KERN_ERR
id|PFX
l_string|&quot;No I/O-Address for card detected&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out_pci
suffix:semicolon
)brace
id|sema_init
c_func
(paren
op_amp
id|open_sem
comma
l_int|1
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|wdtpci_lock
)paren
suffix:semicolon
id|irq
op_assign
id|dev-&gt;irq
suffix:semicolon
id|io
op_assign
id|pci_resource_start
(paren
id|dev
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_region
(paren
id|io
comma
l_int|16
comma
l_string|&quot;wdt_pci&quot;
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
(paren
id|KERN_ERR
id|PFX
l_string|&quot;I/O address 0x%04x already in use&bslash;n&quot;
comma
id|io
)paren
suffix:semicolon
r_goto
id|out_pci
suffix:semicolon
)brace
r_if
c_cond
(paren
id|request_irq
(paren
id|irq
comma
id|wdtpci_interrupt
comma
id|SA_INTERRUPT
op_or
id|SA_SHIRQ
comma
l_string|&quot;wdt_pci&quot;
comma
op_amp
id|wdtpci_miscdev
)paren
)paren
(brace
id|printk
(paren
id|KERN_ERR
id|PFX
l_string|&quot;IRQ %d is not free&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_goto
id|out_reg
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;PCI-WDT500/501 (PCI-WDG-CSM) driver 0.10 at 0x%04x (Interrupt %d)&bslash;n&quot;
comma
id|io
comma
id|irq
)paren
suffix:semicolon
multiline_comment|/* Check that the heartbeat value is within it&squot;s range ; if not reset to the default */
r_if
c_cond
(paren
id|wdtpci_set_heartbeat
c_func
(paren
id|heartbeat
)paren
)paren
(brace
id|wdtpci_set_heartbeat
c_func
(paren
id|WD_TIMO
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;heartbeat value must be 0&lt;heartbeat&lt;65536, using %d&bslash;n&quot;
comma
id|WD_TIMO
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|register_reboot_notifier
(paren
op_amp
id|wdtpci_notifier
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
(paren
id|KERN_ERR
id|PFX
l_string|&quot;cannot register reboot notifier (err=%d)&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_goto
id|out_irq
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_WDT_501_PCI
id|ret
op_assign
id|misc_register
(paren
op_amp
id|temp_miscdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
(paren
id|KERN_ERR
id|PFX
l_string|&quot;cannot register miscdev on minor=%d (err=%d)&bslash;n&quot;
comma
id|TEMP_MINOR
comma
id|ret
)paren
suffix:semicolon
r_goto
id|out_rbt
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_WDT_501_PCI */
id|ret
op_assign
id|misc_register
(paren
op_amp
id|wdtpci_miscdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
(paren
id|KERN_ERR
id|PFX
l_string|&quot;cannot register miscdev on minor=%d (err=%d)&bslash;n&quot;
comma
id|WATCHDOG_MINOR
comma
id|ret
)paren
suffix:semicolon
r_goto
id|out_misc
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;initialized. heartbeat=%d sec (nowayout=%d)&bslash;n&quot;
comma
id|heartbeat
comma
id|nowayout
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_WDT_501_PCI
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;wdt: Fan Tachometer is %s&bslash;n&quot;
comma
(paren
id|tachometer
ques
c_cond
l_string|&quot;Enabled&quot;
suffix:colon
l_string|&quot;Disabled&quot;
)paren
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_WDT_501_PCI */
id|ret
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
id|out_misc
suffix:colon
macro_line|#ifdef CONFIG_WDT_501_PCI
id|misc_deregister
c_func
(paren
op_amp
id|temp_miscdev
)paren
suffix:semicolon
id|out_rbt
suffix:colon
macro_line|#endif /* CONFIG_WDT_501_PCI */
id|unregister_reboot_notifier
c_func
(paren
op_amp
id|wdtpci_notifier
)paren
suffix:semicolon
id|out_irq
suffix:colon
id|free_irq
c_func
(paren
id|irq
comma
op_amp
id|wdtpci_miscdev
)paren
suffix:semicolon
id|out_reg
suffix:colon
id|release_region
(paren
id|io
comma
l_int|16
)paren
suffix:semicolon
id|out_pci
suffix:colon
id|pci_disable_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|wdtpci_remove_one
r_static
r_void
id|__devexit
id|wdtpci_remove_one
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
multiline_comment|/* here we assume only one device will ever have&n;&t; * been picked up and registered by probe function */
id|misc_deregister
c_func
(paren
op_amp
id|wdtpci_miscdev
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_WDT_501_PCI
id|misc_deregister
c_func
(paren
op_amp
id|temp_miscdev
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_WDT_501_PCI */
id|unregister_reboot_notifier
c_func
(paren
op_amp
id|wdtpci_notifier
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|irq
comma
op_amp
id|wdtpci_miscdev
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|io
comma
l_int|16
)paren
suffix:semicolon
id|pci_disable_device
c_func
(paren
id|pdev
)paren
suffix:semicolon
id|dev_count
op_decrement
suffix:semicolon
)brace
DECL|variable|wdtpci_pci_tbl
r_static
r_struct
id|pci_device_id
id|wdtpci_pci_tbl
(braket
)braket
op_assign
(brace
(brace
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_ACCESSIO
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_WDG_CSM
comma
dot
id|subvendor
op_assign
id|PCI_ANY_ID
comma
dot
id|subdevice
op_assign
id|PCI_ANY_ID
comma
)brace
comma
(brace
l_int|0
comma
)brace
comma
multiline_comment|/* terminate list */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|wdtpci_pci_tbl
)paren
suffix:semicolon
DECL|variable|wdtpci_driver
r_static
r_struct
id|pci_driver
id|wdtpci_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;wdt_pci&quot;
comma
dot
id|id_table
op_assign
id|wdtpci_pci_tbl
comma
dot
id|probe
op_assign
id|wdtpci_init_one
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|wdtpci_remove_one
)paren
comma
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;wdtpci_cleanup:&n; *&n; *&t;Unload the watchdog. You cannot do this with any file handles open.&n; *&t;If your watchdog is set to continue ticking on close and you unload&n; *&t;it, well it keeps ticking. We won&squot;t get the interrupt but the board&n; *&t;will not touch PC memory so all is fine. You just have to load a new&n; *&t;module in xx seconds or reboot.&n; */
DECL|function|wdtpci_cleanup
r_static
r_void
id|__exit
id|wdtpci_cleanup
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
(paren
op_amp
id|wdtpci_driver
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * &t;wdtpci_init:&n; *&n; *&t;Set up the WDT watchdog board. All we have to do is grab the&n; *&t;resources we require and bitch if anyone beat us to them.&n; *&t;The open() function will actually kick the board off.&n; */
DECL|function|wdtpci_init
r_static
r_int
id|__init
id|wdtpci_init
c_func
(paren
r_void
)paren
(brace
r_return
id|pci_register_driver
(paren
op_amp
id|wdtpci_driver
)paren
suffix:semicolon
)brace
DECL|variable|wdtpci_init
id|module_init
c_func
(paren
id|wdtpci_init
)paren
suffix:semicolon
DECL|variable|wdtpci_cleanup
id|module_exit
c_func
(paren
id|wdtpci_cleanup
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;JP Nollmann, Alan Cox&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Driver for the ICS PCI-WDT500/501 watchdog cards&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|WATCHDOG_MINOR
id|MODULE_ALIAS_MISCDEV
c_func
(paren
id|WATCHDOG_MINOR
)paren
suffix:semicolon
DECL|variable|TEMP_MINOR
id|MODULE_ALIAS_MISCDEV
c_func
(paren
id|TEMP_MINOR
)paren
suffix:semicolon
eof
