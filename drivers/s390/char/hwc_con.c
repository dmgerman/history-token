multiline_comment|/*&n; *  drivers/s390/char/hwc_con.c&n; *    HWC line mode console driver&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Peschke &lt;peschke@fh-brandenburg.de&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;ctrlchar.h&quot;
macro_line|#include &quot;hwc_rw.h&quot;
macro_line|#ifdef CONFIG_HWC_CONSOLE
DECL|macro|hwc_console_major
mdefine_line|#define  hwc_console_major 4
DECL|macro|hwc_console_minor
mdefine_line|#define  hwc_console_minor 64
DECL|macro|hwc_console_name
mdefine_line|#define  hwc_console_name  &quot;console&quot;
r_void
id|hwc_console_write
(paren
r_struct
id|console
op_star
comma
r_const
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
id|kdev_t
id|hwc_console_device
(paren
r_struct
id|console
op_star
)paren
suffix:semicolon
r_void
id|hwc_console_unblank
(paren
r_void
)paren
suffix:semicolon
DECL|macro|HWC_CON_PRINT_HEADER
mdefine_line|#define  HWC_CON_PRINT_HEADER &quot;hwc console driver: &quot;
DECL|variable|hwc_console
r_struct
id|console
id|hwc_console
op_assign
(brace
id|hwc_console_name
comma
id|hwc_console_write
comma
l_int|NULL
comma
id|hwc_console_device
comma
l_int|NULL
comma
id|hwc_console_unblank
comma
l_int|NULL
comma
id|CON_PRINTBUFFER
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
suffix:semicolon
r_void
DECL|function|hwc_console_write
id|hwc_console_write
(paren
r_struct
id|console
op_star
id|console
comma
r_const
r_char
op_star
id|message
comma
r_int
r_int
id|count
)paren
(brace
r_if
c_cond
(paren
id|console-&gt;device
(paren
id|console
)paren
op_ne
id|hwc_console.device
(paren
op_amp
id|hwc_console
)paren
)paren
(brace
id|hwc_printk
(paren
id|KERN_WARNING
id|HWC_CON_PRINT_HEADER
l_string|&quot;hwc_console_write() called with wrong &quot;
l_string|&quot;device number&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|hwc_write
(paren
l_int|0
comma
id|message
comma
id|count
)paren
suffix:semicolon
)brace
id|kdev_t
DECL|function|hwc_console_device
id|hwc_console_device
(paren
r_struct
id|console
op_star
id|c
)paren
(brace
r_return
id|MKDEV
(paren
id|hwc_console_major
comma
id|hwc_console_minor
)paren
suffix:semicolon
)brace
r_void
DECL|function|hwc_console_unblank
id|hwc_console_unblank
(paren
r_void
)paren
(brace
id|hwc_unblank
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_void
id|__init
DECL|function|hwc_console_init
id|hwc_console_init
(paren
r_void
)paren
(brace
macro_line|#if defined(CONFIG_3215_CONSOLE) || defined(CONFIG_3270_CONSOLE)
r_if
c_cond
(paren
id|MACHINE_IS_VM
)paren
r_return
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|MACHINE_IS_P390
)paren
r_return
suffix:semicolon
id|ctrlchar_init
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hwc_init
(paren
)paren
op_eq
l_int|0
)paren
(brace
macro_line|#ifdef CONFIG_HWC_CONSOLE
id|register_console
(paren
op_amp
id|hwc_console
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
id|panic
(paren
id|HWC_CON_PRINT_HEADER
l_string|&quot;hwc initialisation failed !&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
