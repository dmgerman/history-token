multiline_comment|/*&n; * Generic routines for AGP 3.0 compliant bridges.&n; */
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &quot;agp.h&quot;
multiline_comment|/*&n; * Fully configure and enable an AGP 3.0 host bridge and all the devices&n; * lying behind it.&n; */
DECL|function|agp_3_0_enable
r_int
id|agp_3_0_enable
c_func
(paren
r_struct
id|agp_bridge_data
op_star
id|bridge
comma
id|u32
id|mode
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|agp_3_0_enable
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|agp_3_0_enable
)paren
suffix:semicolon
eof
