multiline_comment|/*&n; * Platform dependent support for DIG64 platforms.&n; *&n; * Copyright (C) 1999 Intel Corp.&n; * Copyright (C) 1999, 2001 Hewlett-Packard Co&n; * Copyright (C) 1999, 2001 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 1999 VA Linux Systems&n; * Copyright (C) 1999 Walt Drummond &lt;drummond@valinux.com&gt;&n; * Copyright (C) 1999 Vijay Chander &lt;vijay@engr.sgi.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * This is here so we can use the CMOS detection in ide-probe.c to&n; * determine what drives are present.  In theory, we don&squot;t need this&n; * as the auto-detection could be done via ide-probe.c:do_probe() but&n; * in practice that would be much slower, which is painful when&n; * running in the simulator.  Note that passing zeroes in DRIVE_INFO&n; * is sufficient (the IDE driver will autodetect the drive geometry).&n; */
DECL|variable|drive_info
r_char
id|drive_info
(braket
l_int|4
op_star
l_int|16
)braket
suffix:semicolon
r_extern
r_int
id|pcat_compat
suffix:semicolon
r_void
id|__init
DECL|function|dig_setup
id|dig_setup
(paren
r_char
op_star
op_star
id|cmdline_p
)paren
(brace
r_int
r_int
id|orig_x
comma
id|orig_y
comma
id|num_cols
comma
id|num_rows
comma
id|font_height
suffix:semicolon
multiline_comment|/*&n;&t; * Default to /dev/sda2.  This assumes that the EFI partition&n;&t; * is physical disk 1 partition 1 and the Linux root disk is&n;&t; * physical disk 1 partition 2.&n;&t; */
id|ROOT_DEV
op_assign
id|to_kdev_t
c_func
(paren
l_int|0x0802
)paren
suffix:semicolon
multiline_comment|/* default to second partition on first drive */
macro_line|#ifdef CONFIG_SMP
id|init_smp_config
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|memset
c_func
(paren
op_amp
id|screen_info
comma
l_int|0
comma
r_sizeof
(paren
id|screen_info
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ia64_boot_param-&gt;console_info.num_rows
op_logical_or
op_logical_neg
id|ia64_boot_param-&gt;console_info.num_cols
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;dig_setup: warning: invalid screen-info, guessing 80x25&bslash;n&quot;
)paren
suffix:semicolon
id|orig_x
op_assign
l_int|0
suffix:semicolon
id|orig_y
op_assign
l_int|0
suffix:semicolon
id|num_cols
op_assign
l_int|80
suffix:semicolon
id|num_rows
op_assign
l_int|25
suffix:semicolon
id|font_height
op_assign
l_int|16
suffix:semicolon
)brace
r_else
(brace
id|orig_x
op_assign
id|ia64_boot_param-&gt;console_info.orig_x
suffix:semicolon
id|orig_y
op_assign
id|ia64_boot_param-&gt;console_info.orig_y
suffix:semicolon
id|num_cols
op_assign
id|ia64_boot_param-&gt;console_info.num_cols
suffix:semicolon
id|num_rows
op_assign
id|ia64_boot_param-&gt;console_info.num_rows
suffix:semicolon
id|font_height
op_assign
l_int|400
op_div
id|num_rows
suffix:semicolon
)brace
id|screen_info.orig_x
op_assign
id|orig_x
suffix:semicolon
id|screen_info.orig_y
op_assign
id|orig_y
suffix:semicolon
id|screen_info.orig_video_cols
op_assign
id|num_cols
suffix:semicolon
id|screen_info.orig_video_lines
op_assign
id|num_rows
suffix:semicolon
id|screen_info.orig_video_points
op_assign
id|font_height
suffix:semicolon
id|screen_info.orig_video_mode
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* XXX fake */
id|screen_info.orig_video_isVGA
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* XXX fake */
id|screen_info.orig_video_ega_bx
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* XXX fake */
)brace
r_void
id|__init
DECL|function|dig_irq_init
id|dig_irq_init
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|pcat_compat
)paren
(brace
multiline_comment|/*&n;&t;&t; * Disable the compatibility mode interrupts (8259 style), needs IN/OUT support&n;&t;&t; * enabled.&n;&t;&t; */
id|printk
c_func
(paren
l_string|&quot;%s: Disabling PC-AT compatible 8259 interrupts&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xff
comma
l_int|0xA1
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xff
comma
l_int|0x21
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;%s: System doesn&squot;t have PC-AT compatible dual-8259 setup. &quot;
l_string|&quot;Nothing to be done&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
)brace
eof
