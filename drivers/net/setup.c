multiline_comment|/*&n; *&t;New style setup code for the network devices&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/netlink.h&gt;
r_extern
r_int
id|slip_init_ctrl_dev
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|x25_asy_init_ctrl_dev
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|dmascc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|arcnet_init
c_func
(paren
r_void
)paren
suffix:semicolon
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
r_extern
r_int
id|dlci_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|sdla_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|sdla_c_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|comx_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|lmc_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|madgemc_probe
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Pad device name to IFNAMSIZ=16. F.e. __PAD6 is string of 9 zeros. */
DECL|macro|__PAD6
mdefine_line|#define __PAD6 &quot;&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&quot;
DECL|macro|__PAD5
mdefine_line|#define __PAD5 __PAD6 &quot;&bslash;0&quot;
DECL|macro|__PAD4
mdefine_line|#define __PAD4 __PAD5 &quot;&bslash;0&quot;
DECL|macro|__PAD3
mdefine_line|#define __PAD3 __PAD4 &quot;&bslash;0&quot;
DECL|macro|__PAD2
mdefine_line|#define __PAD2 __PAD3 &quot;&bslash;0&quot;
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
macro_line|#if defined(CONFIG_DMASCC)
(brace
id|dmascc_init
comma
l_int|0
)brace
comma
macro_line|#endif&t;
macro_line|#if defined(CONFIG_DLCI)
(brace
id|dlci_setup
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#if defined(CONFIG_SDLA)
(brace
id|sdla_c_setup
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#if defined(CONFIG_ARCNET)
(brace
id|arcnet_init
comma
l_int|0
)brace
comma
macro_line|#endif
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
macro_line|#if defined(CONFIG_COMX)
(brace
id|comx_init
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#if defined(CONFIG_LANMEDIA)
(brace
id|lmc_setup
comma
l_int|0
)brace
comma
macro_line|#endif
multiline_comment|/*&n; *&t;Token Ring Drivers&n; */
macro_line|#ifdef CONFIG_MADGEMC
(brace
id|madgemc_probe
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
DECL|function|network_probe
r_static
r_void
id|__init
id|network_probe
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
multiline_comment|/*&n; *&t;Initialise the line discipline drivers&n; */
DECL|function|network_ldisc_init
r_static
r_void
id|__init
id|network_ldisc_init
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(CONFIG_SLIP)
id|slip_init_ctrl_dev
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_X25_ASY)
id|x25_asy_init_ctrl_dev
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|special_device_init
r_static
r_void
id|__init
id|special_device_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_NET_SB1000
r_extern
r_int
id|sb1000_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_struct
id|net_device
id|sb1000_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;cm0&quot;
id|__PAD3
comma
dot
id|init
op_assign
id|sb1000_probe
comma
)brace
suffix:semicolon
id|register_netdev
c_func
(paren
op_amp
id|sb1000_dev
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; *&t;Initialise network devices&n; */
DECL|function|net_device_init
r_void
id|__init
id|net_device_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Devices supporting the new probing API */
id|network_probe
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Line disciplines */
id|network_ldisc_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Special devices */
id|special_device_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* That kicks off the legacy init functions */
)brace
eof
