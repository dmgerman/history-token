multiline_comment|/* &n; *    PDC Console support - ie use firmware to dump text via boot console&n; *&n; *    Copyright (C) 1999-2003 Matthew Wilcox &lt;willy at parisc-linux.org&gt;&n; *    Copyright (C) 2000 Martin K Petersen &lt;mkp at mkp.net&gt;&n; *    Copyright (C) 2000 John Marvin &lt;jsm at parisc-linux.org&gt;&n; *    Copyright (C) 2000-2003 Paul Bame &lt;bame at parisc-linux.org&gt;&n; *    Copyright (C) 2000 Philipp Rumpf &lt;prumpf with tux.org&gt;&n; *    Copyright (C) 2000 Michael Ang &lt;mang with subcarrier.org&gt;&n; *    Copyright (C) 2000 Grant Grundler &lt;grundler with parisc-linux.org&gt;&n; *    Copyright (C) 2001-2002 Ryan Bradetich &lt;rbrad at parisc-linux.org&gt;&n; *    Copyright (C) 2001 Helge Deller &lt;deller at parisc-linux.org&gt;&n; *    Copyright (C) 2001 Thomas Bogendoerfer &lt;tsbogend at parisc-linux.org&gt;&n; *    Copyright (C) 2002 Randolph Chung &lt;tausq with parisc-linux.org&gt;&n; *&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2 of the License, or&n; *    (at your option) any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
multiline_comment|/*&n; *  The PDC console is a simple console, which can be used for debugging &n; *  boot related problems on HP PA-RISC machines.&n; *&n; *  This code uses the ROM (=PDC) based functions to read and write characters&n; *  from and to PDC&squot;s boot path.&n; *  Since all character read from that path must be polled, this code never&n; *  can or will be a fully functional linux console.&n; */
multiline_comment|/* Define EARLY_BOOTUP_DEBUG to debug kernel related boot problems. &n; * On production kernels EARLY_BOOTUP_DEBUG should be undefined. */
DECL|macro|EARLY_BOOTUP_DEBUG
macro_line|#undef EARLY_BOOTUP_DEBUG
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pdc.h&gt;&t;&t;/* for iodc_call() proto and friends */
DECL|function|pdc_console_write
r_static
r_void
id|pdc_console_write
c_func
(paren
r_struct
id|console
op_star
id|co
comma
r_const
r_char
op_star
id|s
comma
r_int
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
id|pdc_iodc_putc
c_func
(paren
op_star
id|s
op_increment
)paren
suffix:semicolon
)brace
)brace
DECL|function|pdc_outc
r_void
id|pdc_outc
c_func
(paren
r_int
r_char
id|c
)paren
(brace
id|pdc_iodc_outc
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
DECL|function|pdc_console_poll_key
r_int
id|pdc_console_poll_key
c_func
(paren
r_struct
id|console
op_star
id|co
)paren
(brace
r_return
id|pdc_iodc_getc
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|pdc_console_setup
r_static
r_int
id|pdc_console_setup
c_func
(paren
r_struct
id|console
op_star
id|co
comma
r_char
op_star
id|options
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_PDC_CONSOLE)
DECL|macro|PDC_CONSOLE_DEVICE
mdefine_line|#define PDC_CONSOLE_DEVICE pdc_console_device
DECL|function|pdc_console_device
r_static
r_struct
id|tty_driver
op_star
id|pdc_console_device
(paren
r_struct
id|console
op_star
id|c
comma
r_int
op_star
id|index
)paren
(brace
r_extern
r_struct
id|tty_driver
id|console_driver
suffix:semicolon
op_star
id|index
op_assign
id|c-&gt;index
ques
c_cond
id|c-&gt;index
op_minus
l_int|1
suffix:colon
id|fg_console
suffix:semicolon
r_return
op_amp
id|console_driver
suffix:semicolon
)brace
macro_line|#else
DECL|macro|PDC_CONSOLE_DEVICE
mdefine_line|#define PDC_CONSOLE_DEVICE NULL
macro_line|#endif
DECL|variable|pdc_cons
r_static
r_struct
id|console
id|pdc_cons
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ttyB&quot;
comma
dot
id|write
op_assign
id|pdc_console_write
comma
dot
id|device
op_assign
id|PDC_CONSOLE_DEVICE
comma
dot
id|setup
op_assign
id|pdc_console_setup
comma
dot
id|flags
op_assign
id|CON_BOOT
op_or
id|CON_PRINTBUFFER
op_or
id|CON_ENABLED
comma
dot
id|index
op_assign
op_minus
l_int|1
comma
)brace
suffix:semicolon
DECL|variable|pdc_console_initialized
r_static
r_int
id|pdc_console_initialized
suffix:semicolon
r_extern
r_int
r_int
id|con_start
suffix:semicolon
multiline_comment|/* kernel/printk.c */
r_extern
r_int
r_int
id|log_end
suffix:semicolon
multiline_comment|/* kernel/printk.c */
DECL|function|pdc_console_init_force
r_static
r_void
id|pdc_console_init_force
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|pdc_console_initialized
)paren
r_return
suffix:semicolon
op_increment
id|pdc_console_initialized
suffix:semicolon
multiline_comment|/* If the console is duplex then copy the COUT parameters to CIN. */
r_if
c_cond
(paren
id|PAGE0-&gt;mem_cons.cl_class
op_eq
id|CL_DUPLEX
)paren
id|memcpy
c_func
(paren
op_amp
id|PAGE0-&gt;mem_kbd
comma
op_amp
id|PAGE0-&gt;mem_cons
comma
r_sizeof
(paren
id|PAGE0-&gt;mem_cons
)paren
)paren
suffix:semicolon
multiline_comment|/* register the pdc console */
id|register_console
c_func
(paren
op_amp
id|pdc_cons
)paren
suffix:semicolon
)brace
DECL|function|pdc_console_init
r_void
id|__init
id|pdc_console_init
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(EARLY_BOOTUP_DEBUG) || defined(CONFIG_PDC_CONSOLE)
id|pdc_console_init_force
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef EARLY_BOOTUP_DEBUG
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Initialized PDC Console for debugging.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* Unregister the pdc console with the printk console layer */
DECL|function|pdc_console_die
r_void
id|pdc_console_die
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pdc_console_initialized
)paren
r_return
suffix:semicolon
op_decrement
id|pdc_console_initialized
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Switching from PDC console&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t repeat what we&squot;ve already printed */
id|con_start
op_assign
id|log_end
suffix:semicolon
id|unregister_console
c_func
(paren
op_amp
id|pdc_cons
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Used for emergencies. Currently only used if an HPMC occurs. If an&n; * HPMC occurs, it is possible that the current console may not be&n; * properly initialed after the PDC IO reset. This routine unregisters all&n; * of the current consoles, reinitializes the pdc console and&n; * registers it.&n; */
DECL|function|pdc_console_restart
r_void
id|pdc_console_restart
c_func
(paren
r_void
)paren
(brace
r_struct
id|console
op_star
id|console
suffix:semicolon
r_if
c_cond
(paren
id|pdc_console_initialized
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
(paren
id|console
op_assign
id|console_drivers
)paren
op_ne
l_int|NULL
)paren
id|unregister_console
c_func
(paren
id|console_drivers
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t repeat what we&squot;ve already printed */
id|con_start
op_assign
id|log_end
suffix:semicolon
multiline_comment|/* force registering the pdc console */
id|pdc_console_init_force
c_func
(paren
)paren
suffix:semicolon
)brace
eof
