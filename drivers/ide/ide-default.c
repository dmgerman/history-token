multiline_comment|/*&n; *&t;ide-default&t;&t;-&t;Driver for unbound ide devices&n; *&n; *&t;This provides a clean way to bind a device to default operations&n; *&t;by having an actual driver class that rather than special casing&n; *&t;&quot;no driver&quot; all over the IDE code&n; *&n; *&t;Copyright (C) 2003, Red Hat &lt;alan@redhat.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/cdrom.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/unaligned.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
DECL|macro|IDEDEFAULT_VERSION
mdefine_line|#define IDEDEFAULT_VERSION&t;&quot;0.9.newide&quot;
multiline_comment|/*&n; *&t;Driver initialization.&n; */
r_static
r_int
id|idedefault_attach
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;IDE subdriver functions, registered with ide.c&n; */
DECL|variable|idedefault_driver
id|ide_driver_t
id|idedefault_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ide-default&quot;
comma
dot
id|version
op_assign
id|IDEDEFAULT_VERSION
comma
dot
id|attach
op_assign
id|idedefault_attach
comma
dot
id|drives
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|idedefault_driver.drives
)paren
)brace
suffix:semicolon
DECL|function|idedefault_attach
r_static
r_int
id|idedefault_attach
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_if
c_cond
(paren
id|ide_register_subdriver
c_func
(paren
id|drive
comma
op_amp
id|idedefault_driver
comma
id|IDE_SUBDRIVER_VERSION
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ide-default: %s: Failed to register the &quot;
l_string|&quot;driver with ide.c&bslash;n&quot;
comma
id|drive-&gt;name
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
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IDE Default Driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
