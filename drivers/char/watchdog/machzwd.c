multiline_comment|/*&n; *  MachZ ZF-Logic Watchdog Timer driver for Linux&n; *  &n; * &n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; *&n; *  The author does NOT admit liability nor provide warranty for&n; *  any of this software. This material is provided &quot;AS-IS&quot; in&n; *  the hope that it may be useful for others.&n; *&n; *  Author: Fernando Fuganti &lt;fuganti@conectiva.com.br&gt;&n; *&n; *  Based on sbc60xxwdt.c by Jakob Oestergaard&n; * &n; *&n; *  We have two timers (wd#1, wd#2) driven by a 32 KHz clock with the &n; *  following periods:&n; *      wd#1 - 2 seconds;&n; *      wd#2 - 7.2 ms;&n; *  After the expiration of wd#1, it can generate a NMI, SCI, SMI, or &n; *  a system RESET and it starts wd#2 that unconditionaly will RESET &n; *  the system when the counter reaches zero.&n; *&n; *  14-Dec-2001 Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; *      Added nowayout module option to override CONFIG_WATCHDOG_NOWAYOUT&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/* ports */
DECL|macro|ZF_IOBASE
mdefine_line|#define ZF_IOBASE&t;0x218
DECL|macro|INDEX
mdefine_line|#define INDEX&t;&t;0x218
DECL|macro|DATA_B
mdefine_line|#define DATA_B&t;&t;0x219
DECL|macro|DATA_W
mdefine_line|#define DATA_W&t;&t;0x21A
DECL|macro|DATA_D
mdefine_line|#define DATA_D&t;&t;0x21A
multiline_comment|/* indexes */
multiline_comment|/* size */
DECL|macro|ZFL_VERSION
mdefine_line|#define ZFL_VERSION&t;0x02&t;/* 16   */
DECL|macro|CONTROL
mdefine_line|#define CONTROL &t;0x10&t;/* 16   */&t;
DECL|macro|STATUS
mdefine_line|#define STATUS&t;&t;0x12&t;/* 8    */
DECL|macro|COUNTER_1
mdefine_line|#define COUNTER_1&t;0x0C&t;/* 16   */
DECL|macro|COUNTER_2
mdefine_line|#define COUNTER_2&t;0x0E&t;/* 8    */
DECL|macro|PULSE_LEN
mdefine_line|#define PULSE_LEN&t;0x0F&t;/* 8    */
multiline_comment|/* controls */
DECL|macro|ENABLE_WD1
mdefine_line|#define ENABLE_WD1&t;0x0001
DECL|macro|ENABLE_WD2
mdefine_line|#define ENABLE_WD2&t;0x0002
DECL|macro|RESET_WD1
mdefine_line|#define RESET_WD1&t;0x0010
DECL|macro|RESET_WD2
mdefine_line|#define RESET_WD2&t;0x0020
DECL|macro|GEN_SCI
mdefine_line|#define GEN_SCI&t;&t;0x0100
DECL|macro|GEN_NMI
mdefine_line|#define GEN_NMI&t;&t;0x0200
DECL|macro|GEN_SMI
mdefine_line|#define GEN_SMI&t;&t;0x0400
DECL|macro|GEN_RESET
mdefine_line|#define GEN_RESET&t;0x0800
multiline_comment|/* utilities */
DECL|macro|WD1
mdefine_line|#define WD1&t;0
DECL|macro|WD2
mdefine_line|#define WD2&t;1
DECL|macro|zf_writew
mdefine_line|#define zf_writew(port, data)  { outb(port, INDEX); outw(data, DATA_W); }
DECL|macro|zf_writeb
mdefine_line|#define zf_writeb(port, data)  { outb(port, INDEX); outb(data, DATA_B); }
DECL|macro|zf_get_ZFL_version
mdefine_line|#define zf_get_ZFL_version()   zf_readw(ZFL_VERSION)
DECL|function|zf_readw
r_static
r_int
r_int
id|zf_readw
c_func
(paren
r_int
r_char
id|port
)paren
(brace
id|outb
c_func
(paren
id|port
comma
id|INDEX
)paren
suffix:semicolon
r_return
id|inw
c_func
(paren
id|DATA_W
)paren
suffix:semicolon
)brace
DECL|function|zf_readb
r_static
r_int
r_int
id|zf_readb
c_func
(paren
r_int
r_char
id|port
)paren
(brace
id|outb
c_func
(paren
id|port
comma
id|INDEX
)paren
suffix:semicolon
r_return
id|inb
c_func
(paren
id|DATA_B
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Fernando Fuganti &lt;fuganti@conectiva.com.br&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MachZ ZF-Logic Watchdog driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
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
DECL|macro|PFX
mdefine_line|#define PFX &quot;machzwd&quot;
DECL|variable|zf_info
r_static
r_struct
id|watchdog_info
id|zf_info
op_assign
(brace
dot
id|options
op_assign
id|WDIOF_KEEPALIVEPING
op_or
id|WDIOF_MAGICCLOSE
comma
dot
id|firmware_version
op_assign
l_int|1
comma
dot
id|identity
op_assign
l_string|&quot;ZF-Logic watchdog&quot;
)brace
suffix:semicolon
multiline_comment|/*&n; * action refers to action taken when watchdog resets&n; * 0 = GEN_RESET&n; * 1 = GEN_SMI&n; * 2 = GEN_NMI&n; * 3 = GEN_SCI&n; * defaults to GEN_RESET (0)&n; */
DECL|variable|action
r_static
r_int
id|action
op_assign
l_int|0
suffix:semicolon
id|module_param
c_func
(paren
id|action
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|action
comma
l_string|&quot;after watchdog resets, generate: 0 = RESET(*)  1 = SMI  2 = NMI  3 = SCI&quot;
)paren
suffix:semicolon
DECL|variable|zf_action
r_static
r_int
id|zf_action
op_assign
id|GEN_RESET
suffix:semicolon
DECL|variable|zf_is_open
r_static
r_int
id|zf_is_open
op_assign
l_int|0
suffix:semicolon
DECL|variable|zf_expect_close
r_static
r_char
id|zf_expect_close
suffix:semicolon
DECL|variable|zf_lock
r_static
id|spinlock_t
id|zf_lock
suffix:semicolon
DECL|variable|zf_port_lock
r_static
id|spinlock_t
id|zf_port_lock
suffix:semicolon
DECL|variable|zf_timer
r_static
r_struct
id|timer_list
id|zf_timer
suffix:semicolon
DECL|variable|next_heartbeat
r_static
r_int
r_int
id|next_heartbeat
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* timeout for user land heart beat (10 seconds) */
DECL|macro|ZF_USER_TIMEO
mdefine_line|#define ZF_USER_TIMEO (HZ*10)
multiline_comment|/* timeout for hardware watchdog (~500ms) */
DECL|macro|ZF_HW_TIMEO
mdefine_line|#define ZF_HW_TIMEO (HZ/2)
multiline_comment|/* number of ticks on WD#1 (driven by a 32KHz clock, 2s) */
DECL|macro|ZF_CTIMEOUT
mdefine_line|#define ZF_CTIMEOUT 0xffff
macro_line|#ifndef ZF_DEBUG
DECL|macro|dprintk
macro_line|#&t;define dprintk(format, args...)
macro_line|#else
DECL|macro|dprintk
macro_line|#&t;define dprintk(format, args...) printk(KERN_DEBUG PFX; &quot;:&quot; __FUNCTION__ &quot;:%d: &quot; format, __LINE__ , ## args)
macro_line|#endif
multiline_comment|/* STATUS register functions */
DECL|function|zf_get_status
r_static
r_inline
r_int
r_char
id|zf_get_status
c_func
(paren
r_void
)paren
(brace
r_return
id|zf_readb
c_func
(paren
id|STATUS
)paren
suffix:semicolon
)brace
DECL|function|zf_set_status
r_static
r_inline
r_void
id|zf_set_status
c_func
(paren
r_int
r_char
r_new
)paren
(brace
id|zf_writeb
c_func
(paren
id|STATUS
comma
r_new
)paren
suffix:semicolon
)brace
multiline_comment|/* CONTROL register functions */
DECL|function|zf_get_control
r_static
r_inline
r_int
r_int
id|zf_get_control
c_func
(paren
r_void
)paren
(brace
r_return
id|zf_readw
c_func
(paren
id|CONTROL
)paren
suffix:semicolon
)brace
DECL|function|zf_set_control
r_static
r_inline
r_void
id|zf_set_control
c_func
(paren
r_int
r_int
r_new
)paren
(brace
id|zf_writew
c_func
(paren
id|CONTROL
comma
r_new
)paren
suffix:semicolon
)brace
multiline_comment|/* WD#? counter functions */
multiline_comment|/*&n; *&t;Just get current counter value&n; */
DECL|function|zf_get_timer
r_static
r_inline
r_int
r_int
id|zf_get_timer
c_func
(paren
r_int
r_char
id|n
)paren
(brace
r_switch
c_cond
(paren
id|n
)paren
(brace
r_case
id|WD1
suffix:colon
r_return
id|zf_readw
c_func
(paren
id|COUNTER_1
)paren
suffix:semicolon
r_case
id|WD2
suffix:colon
r_return
id|zf_readb
c_func
(paren
id|COUNTER_2
)paren
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Just set counter value&n; */
DECL|function|zf_set_timer
r_static
r_inline
r_void
id|zf_set_timer
c_func
(paren
r_int
r_int
r_new
comma
r_int
r_char
id|n
)paren
(brace
r_switch
c_cond
(paren
id|n
)paren
(brace
r_case
id|WD1
suffix:colon
id|zf_writew
c_func
(paren
id|COUNTER_1
comma
r_new
)paren
suffix:semicolon
r_case
id|WD2
suffix:colon
id|zf_writeb
c_func
(paren
id|COUNTER_2
comma
r_new
OG
l_int|0xff
ques
c_cond
l_int|0xff
suffix:colon
r_new
)paren
suffix:semicolon
r_default
suffix:colon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * stop hardware timer&n; */
DECL|function|zf_timer_off
r_static
r_void
id|zf_timer_off
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|ctrl_reg
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* stop internal ping */
id|del_timer_sync
c_func
(paren
op_amp
id|zf_timer
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|zf_port_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* stop watchdog timer */
id|ctrl_reg
op_assign
id|zf_get_control
c_func
(paren
)paren
suffix:semicolon
id|ctrl_reg
op_or_assign
(paren
id|ENABLE_WD1
op_or
id|ENABLE_WD2
)paren
suffix:semicolon
multiline_comment|/* disable wd1 and wd2 */
id|ctrl_reg
op_and_assign
op_complement
(paren
id|ENABLE_WD1
op_or
id|ENABLE_WD2
)paren
suffix:semicolon
id|zf_set_control
c_func
(paren
id|ctrl_reg
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|zf_port_lock
comma
id|flags
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;: Watchdog timer is now disabled&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * start hardware timer &n; */
DECL|function|zf_timer_on
r_static
r_void
id|zf_timer_on
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|ctrl_reg
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|zf_port_lock
comma
id|flags
)paren
suffix:semicolon
id|zf_writeb
c_func
(paren
id|PULSE_LEN
comma
l_int|0xff
)paren
suffix:semicolon
id|zf_set_timer
c_func
(paren
id|ZF_CTIMEOUT
comma
id|WD1
)paren
suffix:semicolon
multiline_comment|/* user land ping */
id|next_heartbeat
op_assign
id|jiffies
op_plus
id|ZF_USER_TIMEO
suffix:semicolon
multiline_comment|/* start the timer for internal ping */
id|zf_timer.expires
op_assign
id|jiffies
op_plus
id|ZF_HW_TIMEO
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|zf_timer
)paren
suffix:semicolon
multiline_comment|/* start watchdog timer */
id|ctrl_reg
op_assign
id|zf_get_control
c_func
(paren
)paren
suffix:semicolon
id|ctrl_reg
op_or_assign
(paren
id|ENABLE_WD1
op_or
id|zf_action
)paren
suffix:semicolon
id|zf_set_control
c_func
(paren
id|ctrl_reg
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|zf_port_lock
comma
id|flags
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;: Watchdog timer is now enabled&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|zf_ping
r_static
r_void
id|zf_ping
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_int
r_int
id|ctrl_reg
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|zf_writeb
c_func
(paren
id|COUNTER_2
comma
l_int|0xff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|time_before
c_func
(paren
id|jiffies
comma
id|next_heartbeat
)paren
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;time_before: %ld&bslash;n&quot;
comma
id|next_heartbeat
op_minus
id|jiffies
)paren
suffix:semicolon
multiline_comment|/* &n;&t;&t; * reset event is activated by transition from 0 to 1 on&n;&t;&t; * RESET_WD1 bit and we assume that it is already zero...&n;&t;&t; */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|zf_port_lock
comma
id|flags
)paren
suffix:semicolon
id|ctrl_reg
op_assign
id|zf_get_control
c_func
(paren
)paren
suffix:semicolon
id|ctrl_reg
op_or_assign
id|RESET_WD1
suffix:semicolon
id|zf_set_control
c_func
(paren
id|ctrl_reg
)paren
suffix:semicolon
multiline_comment|/* ...and nothing changes until here */
id|ctrl_reg
op_and_assign
op_complement
(paren
id|RESET_WD1
)paren
suffix:semicolon
id|zf_set_control
c_func
(paren
id|ctrl_reg
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|zf_port_lock
comma
id|flags
)paren
suffix:semicolon
id|zf_timer.expires
op_assign
id|jiffies
op_plus
id|ZF_HW_TIMEO
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|zf_timer
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
l_string|&quot;: I will reset your machine&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|zf_write
r_static
id|ssize_t
id|zf_write
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
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
multiline_comment|/*  Can&squot;t seek (pwrite) on this device  */
r_if
c_cond
(paren
id|ppos
op_ne
op_amp
id|file-&gt;f_pos
)paren
r_return
op_minus
id|ESPIPE
suffix:semicolon
multiline_comment|/* See if we got the magic character */
r_if
c_cond
(paren
id|count
)paren
(brace
multiline_comment|/*&n;&t;&t; * no need to check for close confirmation&n;&t;&t; * no way to disable watchdog ;)&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|nowayout
)paren
(brace
r_int
id|ofs
suffix:semicolon
multiline_comment|/* &n;&t;&t;&t; * note: just in case someone wrote the magic character&n;&t;&t;&t; * five months ago...&n;&t;&t;&t; */
id|zf_expect_close
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* now scan */
r_for
c_loop
(paren
id|ofs
op_assign
l_int|0
suffix:semicolon
id|ofs
op_ne
id|count
suffix:semicolon
id|ofs
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
id|ofs
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;V&squot;
)paren
(brace
id|zf_expect_close
op_assign
l_int|42
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;zf_expect_close = 42&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n;&t;&t; * Well, anyhow someone wrote to us,&n;&t;&t; * we should return that favour&n;&t;&t; */
id|next_heartbeat
op_assign
id|jiffies
op_plus
id|ZF_USER_TIMEO
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;user ping at %ld&bslash;n&quot;
comma
id|jiffies
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|zf_ioctl
r_static
r_int
id|zf_ioctl
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
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|WDIOC_GETSUPPORT
suffix:colon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_struct
id|watchdog_info
op_star
)paren
id|arg
comma
op_amp
id|zf_info
comma
r_sizeof
(paren
id|zf_info
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WDIOC_GETSTATUS
suffix:colon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_int
op_star
)paren
id|arg
comma
op_amp
id|zf_is_open
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WDIOC_KEEPALIVE
suffix:colon
id|zf_ping
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOTTY
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|zf_open
r_static
r_int
id|zf_open
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
id|spin_lock
c_func
(paren
op_amp
id|zf_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|zf_is_open
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|zf_lock
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nowayout
)paren
id|__module_get
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
id|zf_is_open
op_assign
l_int|1
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|zf_lock
)paren
suffix:semicolon
id|zf_timer_on
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|zf_close
r_static
r_int
id|zf_close
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
id|zf_expect_close
op_eq
l_int|42
)paren
(brace
id|zf_timer_off
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|del_timer
c_func
(paren
op_amp
id|zf_timer
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;: device file closed unexpectedly. Will not stop the WDT!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|zf_lock
)paren
suffix:semicolon
id|zf_is_open
op_assign
l_int|0
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|zf_lock
)paren
suffix:semicolon
id|zf_expect_close
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Notifier for system down&n; */
DECL|function|zf_notify_sys
r_static
r_int
id|zf_notify_sys
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
id|zf_timer_off
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
DECL|variable|zf_fops
r_static
r_struct
id|file_operations
id|zf_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|write
op_assign
id|zf_write
comma
dot
id|ioctl
op_assign
id|zf_ioctl
comma
dot
id|open
op_assign
id|zf_open
comma
dot
id|release
op_assign
id|zf_close
comma
)brace
suffix:semicolon
DECL|variable|zf_miscdev
r_static
r_struct
id|miscdevice
id|zf_miscdev
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
id|zf_fops
)brace
suffix:semicolon
multiline_comment|/*&n; * The device needs to learn about soft shutdowns in order to&n; * turn the timebomb registers off.&n; */
DECL|variable|zf_notifier
r_static
r_struct
id|notifier_block
id|zf_notifier
op_assign
(brace
dot
id|notifier_call
op_assign
id|zf_notify_sys
comma
dot
id|next
op_assign
l_int|NULL
comma
dot
id|priority
op_assign
l_int|0
)brace
suffix:semicolon
DECL|function|zf_show_action
r_static
r_void
id|__init
id|zf_show_action
c_func
(paren
r_int
id|act
)paren
(brace
r_char
op_star
id|str
(braket
)braket
op_assign
(brace
l_string|&quot;RESET&quot;
comma
l_string|&quot;SMI&quot;
comma
l_string|&quot;NMI&quot;
comma
l_string|&quot;SCI&quot;
)brace
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;: Watchdog using action = %s&bslash;n&quot;
comma
id|str
(braket
id|act
)braket
)paren
suffix:semicolon
)brace
DECL|function|zf_init
r_static
r_int
id|__init
id|zf_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;: MachZ ZF-Logic Watchdog driver initializing.&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
id|zf_get_ZFL_version
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%#x&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|ret
)paren
op_logical_or
(paren
id|ret
op_ne
l_int|0xffff
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PFX
l_string|&quot;: no ZF-Logic found&bslash;n&quot;
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
(paren
id|action
op_le
l_int|3
)paren
op_logical_and
(paren
id|action
op_ge
l_int|0
)paren
)paren
(brace
id|zf_action
op_assign
id|zf_action
op_rshift
id|action
suffix:semicolon
)brace
r_else
id|action
op_assign
l_int|0
suffix:semicolon
id|zf_show_action
c_func
(paren
id|action
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|zf_lock
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|zf_port_lock
)paren
suffix:semicolon
id|ret
op_assign
id|misc_register
c_func
(paren
op_amp
id|zf_miscdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;can&squot;t misc_register on minor=%d&bslash;n&quot;
comma
id|WATCHDOG_MINOR
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|ZF_IOBASE
comma
l_int|3
comma
l_string|&quot;MachZ ZFL WDT&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cannot reserve I/O ports at %d&bslash;n&quot;
comma
id|ZF_IOBASE
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|no_region
suffix:semicolon
)brace
id|ret
op_assign
id|register_reboot_notifier
c_func
(paren
op_amp
id|zf_notifier
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;can&squot;t register reboot notifier (err=%d)&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_goto
id|no_reboot
suffix:semicolon
)brace
id|zf_set_status
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|zf_set_control
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* this is the timer that will do the hard work */
id|init_timer
c_func
(paren
op_amp
id|zf_timer
)paren
suffix:semicolon
id|zf_timer.function
op_assign
id|zf_ping
suffix:semicolon
id|zf_timer.data
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|no_reboot
suffix:colon
id|release_region
c_func
(paren
id|ZF_IOBASE
comma
l_int|3
)paren
suffix:semicolon
id|no_region
suffix:colon
id|misc_deregister
c_func
(paren
op_amp
id|zf_miscdev
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|zf_exit
r_void
id|__exit
id|zf_exit
c_func
(paren
r_void
)paren
(brace
id|zf_timer_off
c_func
(paren
)paren
suffix:semicolon
id|misc_deregister
c_func
(paren
op_amp
id|zf_miscdev
)paren
suffix:semicolon
id|unregister_reboot_notifier
c_func
(paren
op_amp
id|zf_notifier
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|ZF_IOBASE
comma
l_int|3
)paren
suffix:semicolon
)brace
DECL|variable|zf_init
id|module_init
c_func
(paren
id|zf_init
)paren
suffix:semicolon
DECL|variable|zf_exit
id|module_exit
c_func
(paren
id|zf_exit
)paren
suffix:semicolon
eof
