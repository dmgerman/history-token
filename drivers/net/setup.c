multiline_comment|/*&n; *&t;New style setup code for the network devices&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/netlink.h&gt;
r_extern
r_int
id|scc_enet_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|fec_enet_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Devices in this list must do new style probing. That is they must&n; *&t;allocate their own device objects and do their own bus scans.&n; */
DECL|struct|net_probe
r_struct
id|net_probe
(brace
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|status
r_int
id|status
suffix:semicolon
multiline_comment|/* non-zero if autoprobe has failed */
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|net_probe
id|pci_probes
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/*&n;&t; *&t;Early setup devices&n;&t; */
macro_line|#if defined(CONFIG_SCC_ENET)
(brace
id|scc_enet_init
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#if defined(CONFIG_FEC_ENET)
(brace
id|fec_enet_init
comma
l_int|0
)brace
comma
macro_line|#endif
(brace
l_int|NULL
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Run the updated device probes. These do not need a device passed&n; *&t;into them.&n; */
DECL|function|net_device_init
r_void
id|__init
id|net_device_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|net_probe
op_star
id|p
op_assign
id|pci_probes
suffix:semicolon
r_while
c_loop
(paren
id|p-&gt;probe
op_ne
l_int|NULL
)paren
(brace
id|p-&gt;status
op_assign
id|p
op_member_access_from_pointer
id|probe
c_func
(paren
)paren
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
)brace
eof
