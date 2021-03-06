multiline_comment|/*&n; * $Id: rpxlite.c,v 1.22 2004/11/04 13:24:15 gleixner Exp $&n; *&n; * Handle mapping of the flash on the RPX Lite and CLLF boards&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
DECL|macro|WINDOW_ADDR
mdefine_line|#define WINDOW_ADDR 0xfe000000
DECL|macro|WINDOW_SIZE
mdefine_line|#define WINDOW_SIZE 0x800000
DECL|variable|mymtd
r_static
r_struct
id|mtd_info
op_star
id|mymtd
suffix:semicolon
DECL|variable|rpxlite_map
r_static
r_struct
id|map_info
id|rpxlite_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;RPX&quot;
comma
dot
id|size
op_assign
id|WINDOW_SIZE
comma
dot
id|bankwidth
op_assign
l_int|4
comma
dot
id|phys
op_assign
id|WINDOW_ADDR
comma
)brace
suffix:semicolon
DECL|function|init_rpxlite
r_int
id|__init
id|init_rpxlite
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;RPX Lite or CLLF flash device: %x at %x&bslash;n&quot;
comma
id|WINDOW_SIZE
op_star
l_int|4
comma
id|WINDOW_ADDR
)paren
suffix:semicolon
id|rpxlite_map.virt
op_assign
id|ioremap
c_func
(paren
id|WINDOW_ADDR
comma
id|WINDOW_SIZE
op_star
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rpxlite_map.virt
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failed to ioremap&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|simple_map_init
c_func
(paren
op_amp
id|rpxlite_map
)paren
suffix:semicolon
id|mymtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;cfi_probe&quot;
comma
op_amp
id|rpxlite_map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mymtd
)paren
(brace
id|mymtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|add_mtd_device
c_func
(paren
id|mymtd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|rpxlite_map.virt
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|cleanup_rpxlite
r_static
r_void
id|__exit
id|cleanup_rpxlite
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|mymtd
)paren
(brace
id|del_mtd_device
c_func
(paren
id|mymtd
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|mymtd
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rpxlite_map.virt
)paren
(brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|rpxlite_map.virt
)paren
suffix:semicolon
id|rpxlite_map.virt
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|variable|init_rpxlite
id|module_init
c_func
(paren
id|init_rpxlite
)paren
suffix:semicolon
DECL|variable|cleanup_rpxlite
id|module_exit
c_func
(paren
id|cleanup_rpxlite
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Arnold Christensen &lt;AKC@pel.dk&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MTD map driver for RPX Lite and CLLF boards&quot;
)paren
suffix:semicolon
eof
