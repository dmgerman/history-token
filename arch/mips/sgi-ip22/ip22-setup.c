multiline_comment|/*&n; * ip22-setup.c: SGI specific setup, including init of the feature struct.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; * Copyright (C) 1997, 1998 Ralf Baechle (ralf@gnu.org)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ds1286.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/bcache.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/gdb-stub.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#include &lt;asm/sgi/mc.h&gt;
macro_line|#include &lt;asm/sgi/hpc3.h&gt;
macro_line|#include &lt;asm/sgi/ip22.h&gt;
DECL|variable|sgi_gfxaddr
r_int
r_int
id|sgi_gfxaddr
suffix:semicolon
multiline_comment|/*&n; * Stop-A is originally a Sun thing that isn&squot;t standard on IP22 so to avoid&n; * accidents it&squot;s disabled by default on IP22.&n; *&n; * FIXME: provide a mechanism to change the value of stop_a_enabled.&n; */
DECL|variable|stop_a_enabled
r_int
id|stop_a_enabled
suffix:semicolon
DECL|function|ip22_do_break
r_void
id|ip22_do_break
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|stop_a_enabled
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|ArcEnterInteractiveMode
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|ip22_do_break
id|EXPORT_SYMBOL
c_func
(paren
id|ip22_do_break
)paren
suffix:semicolon
r_extern
r_void
id|ip22_be_init
c_func
(paren
r_void
)paren
id|__init
suffix:semicolon
r_extern
r_void
id|ip22_time_init
c_func
(paren
r_void
)paren
id|__init
suffix:semicolon
DECL|function|ip22_setup
r_static
r_int
id|__init
id|ip22_setup
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|ctype
suffix:semicolon
id|board_be_init
op_assign
id|ip22_be_init
suffix:semicolon
id|ip22_time_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Init the INDY HPC I/O controller.  Need to call this before&n;&t; * fucking with the memory controller because it needs to know the&n;&t; * boardID and whether this is a Guiness or a FullHouse machine.&n;&t; */
id|sgihpc_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Init INDY memory controller. */
id|sgimc_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BOARD_SCACHE
multiline_comment|/* Now enable boardcaches, if any. */
id|indy_sc_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Set EISA IO port base for Indigo2&n;&t; * ioremap cannot fail */
id|set_io_port_base
c_func
(paren
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
l_int|0x00080000
comma
l_int|0x1fffffff
op_minus
l_int|0x00080000
)paren
)paren
suffix:semicolon
multiline_comment|/* ARCS console environment variable is set to &quot;g?&quot; for&n;&t; * graphics console, it is set to &quot;d&quot; for the first serial&n;&t; * line and &quot;d2&quot; for the second serial line.&n;&t; */
id|ctype
op_assign
id|ArcGetEnvironmentVariable
c_func
(paren
l_string|&quot;console&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ctype
op_logical_and
op_star
id|ctype
op_eq
l_char|&squot;d&squot;
)paren
(brace
r_static
r_char
id|options
(braket
l_int|8
)braket
suffix:semicolon
r_char
op_star
id|baud
op_assign
id|ArcGetEnvironmentVariable
c_func
(paren
l_string|&quot;dbaud&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|baud
)paren
id|strcpy
c_func
(paren
id|options
comma
id|baud
)paren
suffix:semicolon
id|add_preferred_console
c_func
(paren
l_string|&quot;ttyS&quot;
comma
op_star
(paren
id|ctype
op_plus
l_int|1
)paren
op_eq
l_char|&squot;2&squot;
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
id|baud
ques
c_cond
id|options
suffix:colon
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|ctype
op_logical_or
op_star
id|ctype
op_ne
l_char|&squot;g&squot;
)paren
(brace
multiline_comment|/* Use ARC if we don&squot;t want serial (&squot;d&squot;) or Newport (&squot;g&squot;). */
id|prom_flags
op_or_assign
id|PROM_FLAG_USE_AS_CONSOLE
suffix:semicolon
id|add_preferred_console
c_func
(paren
l_string|&quot;arc&quot;
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_KGDB
(brace
r_char
op_star
id|kgdb_ttyd
op_assign
id|prom_getcmdline
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|kgdb_ttyd
op_assign
id|strstr
c_func
(paren
id|kgdb_ttyd
comma
l_string|&quot;kgdb=ttyd&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
id|line
suffix:semicolon
id|kgdb_ttyd
op_add_assign
id|strlen
c_func
(paren
l_string|&quot;kgdb=ttyd&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|kgdb_ttyd
op_ne
l_char|&squot;1&squot;
op_logical_and
op_star
id|kgdb_ttyd
op_ne
l_char|&squot;2&squot;
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;KGDB: Uknown serial line /dev/ttyd%c&quot;
l_string|&quot;, falling back to /dev/ttyd1&bslash;n&quot;
comma
op_star
id|kgdb_ttyd
)paren
suffix:semicolon
id|line
op_assign
op_star
id|kgdb_ttyd
op_eq
l_char|&squot;2&squot;
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;KGDB: Using serial line /dev/ttyd%d for &quot;
l_string|&quot;session&bslash;n&quot;
comma
id|line
ques
c_cond
l_int|1
suffix:colon
l_int|2
)paren
suffix:semicolon
id|rs_kgdb_hook
c_func
(paren
id|line
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;KGDB: Using serial line /dev/ttyd%d for &quot;
l_string|&quot;session, please connect your debugger&bslash;n&quot;
comma
id|line
ques
c_cond
l_int|1
suffix:colon
l_int|2
)paren
suffix:semicolon
id|kgdb_enabled
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Breakpoints and stuff are in sgi_irq_setup() */
)brace
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_VT) &amp;&amp; defined(CONFIG_SGI_NEWPORT_CONSOLE)
(brace
id|ULONG
op_star
id|gfxinfo
suffix:semicolon
id|ULONG
op_star
(paren
op_star
id|__vec
)paren
(paren
r_void
)paren
op_assign
(paren
r_void
op_star
)paren
(paren
r_int
)paren
op_star
(paren
(paren
id|_PULONG
op_star
)paren
(paren
r_int
)paren
(paren
(paren
id|PROMBLOCK
)paren
op_member_access_from_pointer
id|pvector
op_plus
l_int|0x20
)paren
)paren
suffix:semicolon
id|gfxinfo
op_assign
id|__vec
c_func
(paren
)paren
suffix:semicolon
id|sgi_gfxaddr
op_assign
(paren
(paren
id|gfxinfo
(braket
l_int|1
)braket
op_ge
l_int|0xa0000000
op_logical_and
id|gfxinfo
(braket
l_int|1
)braket
op_le
l_int|0xc0000000
)paren
ques
c_cond
id|gfxinfo
(braket
l_int|1
)braket
op_minus
l_int|0xa0000000
suffix:colon
l_int|0
)paren
suffix:semicolon
multiline_comment|/* newport addresses? */
r_if
c_cond
(paren
id|sgi_gfxaddr
op_eq
l_int|0x1f0f0000
op_logical_or
id|sgi_gfxaddr
op_eq
l_int|0x1f4f0000
)paren
(brace
id|conswitchp
op_assign
op_amp
id|newport_con
suffix:semicolon
)brace
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ip22_setup
id|early_initcall
c_func
(paren
id|ip22_setup
)paren
suffix:semicolon
eof
