macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/ocp.h&gt;
DECL|variable|ocp_sys_info
r_struct
id|ocp_sys_info_data
id|ocp_sys_info
op_assign
(brace
dot
id|opb_bus_freq
op_assign
l_int|50000000
comma
multiline_comment|/* OPB Bus Frequency (Hz) */
dot
id|ebc_bus_freq
op_assign
l_int|33333333
comma
multiline_comment|/* EBC Bus Frequency (Hz) */
)brace
suffix:semicolon
DECL|variable|ocp_sys_info
id|EXPORT_SYMBOL
c_func
(paren
id|ocp_sys_info
)paren
suffix:semicolon
eof
