multiline_comment|/*&n; * ip22-setup.c: SGI specific setup, including init of the feature struct.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; * Copyright (C) 1997, 1998 Ralf Baechle (ralf@gnu.org)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/bcache.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/ds1286.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/gdb-stub.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#include &lt;asm/sgi/mc.h&gt;
macro_line|#include &lt;asm/sgi/hpc3.h&gt;
macro_line|#include &lt;asm/sgi/ip22.h&gt;
macro_line|#ifdef CONFIG_KGDB
r_extern
r_void
id|rs_kgdb_hook
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|breakpoint
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|remote_debug
r_static
r_int
id|remote_debug
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_IP22_SERIAL_CONSOLE) || defined(CONFIG_ARC_CONSOLE)
r_extern
r_void
id|console_setup
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_struct
id|rtc_ops
id|ip22_rtc_ops
suffix:semicolon
DECL|macro|KBD_STAT_IBF
mdefine_line|#define KBD_STAT_IBF&t;&t;0x02&t;/* Keyboard input buffer full */
DECL|variable|sgi_gfxaddr
r_int
r_int
id|sgi_gfxaddr
suffix:semicolon
multiline_comment|/*&n; * Stop-A is originally a Sun thing that isn&squot;t standard on IP22 so to avoid&n; * accidents it&squot;s disabled by default on IP22.&n; *&n; * FIXME: provide a mechanism to change the value of stop_a_enabled.&n; */
DECL|variable|serial_console
r_int
id|serial_console
suffix:semicolon
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
r_void
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
macro_line|#ifdef CONFIG_KGDB
r_char
op_star
id|kgdb_ttyd
suffix:semicolon
macro_line|#endif
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
macro_line|#ifdef CONFIG_VT
id|conswitchp
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
multiline_comment|/* Set the IO space to some sane value */
id|set_io_port_base
(paren
id|KSEG1ADDR
(paren
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
macro_line|#ifdef CONFIG_IP22_SERIAL_CONSOLE
r_if
c_cond
(paren
op_star
(paren
id|ctype
op_plus
l_int|1
)paren
op_eq
l_char|&squot;2&squot;
)paren
id|console_setup
c_func
(paren
l_string|&quot;ttyS1&quot;
)paren
suffix:semicolon
r_else
id|console_setup
c_func
(paren
l_string|&quot;ttyS0&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifdef CONFIG_ARC_CONSOLE
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
id|console_setup
c_func
(paren
l_string|&quot;arc&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_KGDB
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
id|remote_debug
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Breakpoints and stuff are in sgi_irq_setup() */
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_VT
macro_line|#ifdef CONFIG_SGI_NEWPORT_CONSOLE
r_if
c_cond
(paren
id|ctype
op_logical_and
op_star
id|ctype
op_eq
l_char|&squot;g&squot;
)paren
(brace
r_int
r_int
op_star
id|gfxinfo
suffix:semicolon
r_int
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
op_star
(paren
r_int
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
suffix:semicolon
id|gfxinfo
op_assign
(paren
r_int
r_int
op_star
)paren
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
id|screen_info
op_assign
(paren
r_struct
id|screen_info
)paren
(brace
l_int|0
comma
l_int|0
comma
multiline_comment|/* orig-x, orig-y */
l_int|0
comma
multiline_comment|/* unused */
l_int|0
comma
multiline_comment|/* orig_video_page */
l_int|0
comma
multiline_comment|/* orig_video_mode */
l_int|160
comma
multiline_comment|/* orig_video_cols */
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* unused, ega_bx, unused */
l_int|64
comma
multiline_comment|/* orig_video_lines */
l_int|0
comma
multiline_comment|/* orig_video_isVGA */
l_int|16
multiline_comment|/* orig_video_points */
)brace
suffix:semicolon
)brace
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_DUMMY_CONSOLE
multiline_comment|/* Either if newport console wasn&squot;t used or failed to initialize. */
macro_line|#ifdef CONFIG_SGI_NEWPORT_CONSOLE
r_if
c_cond
(paren
id|conswitchp
op_ne
op_amp
id|newport_con
)paren
(brace
macro_line|#endif
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
id|rtc_ops
op_assign
op_amp
id|ip22_rtc_ops
suffix:semicolon
macro_line|#ifdef CONFIG_PSMOUSE
id|aux_device_present
op_assign
l_int|0xaa
suffix:semicolon
macro_line|#endif
)brace
eof
