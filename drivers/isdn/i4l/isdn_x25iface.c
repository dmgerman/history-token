multiline_comment|/* * Linux ISDN subsystem, X.25 related functions&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; */
multiline_comment|/*&n; * stuff needed to support the Linux X.25 PLP code on top of devices that&n; * can provide a lab_b service using the concap_proto mechanism.&n; * This module supports a network interface wich provides lapb_sematics&n; * -- as defined in ../../Documentation/networking/x25-iface.txt -- to&n; * the upper layer and assumes that the lower layer provides a reliable&n; * data link service by means of the concap_device_ops callbacks.&n; *&n; * Only protocol specific stuff goes here. Device specific stuff&n; * goes to another -- device related -- concap_proto support source file.&n; *&n; */
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/concap.h&gt;
macro_line|#include &lt;linux/wanrouter.h&gt;
macro_line|#include &quot;isdn_x25iface.h&quot;
multiline_comment|/* for debugging messages not to cause an oops when device pointer is NULL*/
DECL|macro|MY_DEVNAME
mdefine_line|#define MY_DEVNAME(dev)  ( (dev) ? (dev)-&gt;name : &quot;DEVICE UNSPECIFIED&quot; )
DECL|struct|isdn_x25iface_proto_data
r_typedef
r_struct
id|isdn_x25iface_proto_data
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|state
r_enum
id|wan_states
id|state
suffix:semicolon
multiline_comment|/* Private stuff, not to be accessed via proto_data. We provide the&n;&t;   other storage for the concap_proto instance here as well,&n;&t;   enabling us to allocate both with just one kmalloc(): */
DECL|member|priv
r_struct
id|concap_proto
id|priv
suffix:semicolon
DECL|typedef|ix25_pdata_t
)brace
id|ix25_pdata_t
suffix:semicolon
multiline_comment|/* is now in header file (extern): struct concap_proto * isdn_x25iface_proto_new(void); */
r_void
id|isdn_x25iface_proto_del
c_func
(paren
r_struct
id|concap_proto
op_star
)paren
suffix:semicolon
r_int
id|isdn_x25iface_proto_close
c_func
(paren
r_struct
id|concap_proto
op_star
)paren
suffix:semicolon
r_int
id|isdn_x25iface_proto_restart
c_func
(paren
r_struct
id|concap_proto
op_star
comma
r_struct
id|net_device
op_star
comma
r_struct
id|concap_device_ops
op_star
)paren
suffix:semicolon
r_int
id|isdn_x25iface_xmit
c_func
(paren
r_struct
id|concap_proto
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_int
id|isdn_x25iface_receive
c_func
(paren
r_struct
id|concap_proto
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_int
id|isdn_x25iface_connect_ind
c_func
(paren
r_struct
id|concap_proto
op_star
)paren
suffix:semicolon
r_int
id|isdn_x25iface_disconn_ind
c_func
(paren
r_struct
id|concap_proto
op_star
)paren
suffix:semicolon
DECL|variable|ix25_pops
r_static
r_struct
id|concap_proto_ops
id|ix25_pops
op_assign
(brace
op_amp
id|isdn_x25iface_proto_new
comma
op_amp
id|isdn_x25iface_proto_del
comma
op_amp
id|isdn_x25iface_proto_restart
comma
op_amp
id|isdn_x25iface_proto_close
comma
op_amp
id|isdn_x25iface_xmit
comma
op_amp
id|isdn_x25iface_receive
comma
op_amp
id|isdn_x25iface_connect_ind
comma
op_amp
id|isdn_x25iface_disconn_ind
)brace
suffix:semicolon
multiline_comment|/* error message helper function */
DECL|function|illegal_state_warn
r_static
r_void
id|illegal_state_warn
c_func
(paren
r_int
id|state
comma
r_int
r_char
id|firstbyte
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;isdn_x25iface: firstbyte %x illegal in&quot;
l_string|&quot;current state %d&bslash;n&quot;
comma
id|firstbyte
comma
id|state
)paren
suffix:semicolon
)brace
multiline_comment|/* check protocol data field for consistency */
DECL|function|pdata_is_bad
r_static
r_int
(def_block
id|pdata_is_bad
c_func
(paren
id|ix25_pdata_t
op_star
id|pda
)paren
(brace
r_if
c_cond
(paren
id|pda
op_logical_and
id|pda
op_member_access_from_pointer
id|magic
op_eq
id|ISDN_X25IFACE_MAGIC
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;isdn_x25iface_xxx: illegal pointer to proto data&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)def_block
multiline_comment|/* create a new x25 interface protocol instance&n; */
DECL|function|isdn_x25iface_proto_new
r_struct
id|concap_proto
op_star
id|isdn_x25iface_proto_new
c_func
(paren
)paren
(brace
id|ix25_pdata_t
op_star
id|tmp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|ix25_pdata_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|IX25DEBUG
c_func
(paren
l_string|&quot;isdn_x25iface_proto_new&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
)paren
(brace
id|tmp
op_member_access_from_pointer
id|magic
op_assign
id|ISDN_X25IFACE_MAGIC
suffix:semicolon
id|tmp
op_member_access_from_pointer
id|state
op_assign
id|WAN_UNCONFIGURED
suffix:semicolon
multiline_comment|/* private data space used to hold the concap_proto data.&n;&t;&t;   Only to be accessed via the returned pointer */
id|tmp
op_member_access_from_pointer
id|priv.dops
op_assign
l_int|NULL
suffix:semicolon
id|tmp
op_member_access_from_pointer
id|priv.net_dev
op_assign
l_int|NULL
suffix:semicolon
id|tmp
op_member_access_from_pointer
id|priv.pops
op_assign
op_amp
id|ix25_pops
suffix:semicolon
id|tmp
op_member_access_from_pointer
id|priv.flags
op_assign
l_int|0
suffix:semicolon
id|tmp
op_member_access_from_pointer
id|priv.proto_data
op_assign
id|tmp
suffix:semicolon
r_return
op_amp
(paren
id|tmp
op_member_access_from_pointer
id|priv
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* close the x25iface encapsulation protocol &n; */
DECL|function|isdn_x25iface_proto_close
r_int
(def_block
id|isdn_x25iface_proto_close
c_func
(paren
r_struct
id|concap_proto
op_star
id|cprot
)paren
(brace
id|ix25_pdata_t
op_star
id|tmp
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|ulong
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cprot
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;isdn_x25iface_proto_close: &quot;
l_string|&quot;invalid concap_proto pointer&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|IX25DEBUG
c_func
(paren
l_string|&quot;isdn_x25iface_proto_close %s &bslash;n&quot;
comma
id|MY_DEVNAME
c_func
(paren
id|cprot
op_member_access_from_pointer
id|net_dev
)paren
)paren
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* avoid races with incoming events calling pops methods while&n;&t;&t; cprot members are inconsistent */
id|cprot
op_member_access_from_pointer
id|dops
op_assign
l_int|NULL
suffix:semicolon
id|cprot
op_member_access_from_pointer
id|net_dev
op_assign
l_int|NULL
suffix:semicolon
id|tmp
op_assign
id|cprot
op_member_access_from_pointer
id|proto_data
suffix:semicolon
r_if
c_cond
(paren
id|pdata_is_bad
c_func
(paren
id|tmp
)paren
)paren
(brace
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|tmp
op_member_access_from_pointer
id|state
op_assign
id|WAN_UNCONFIGURED
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
)def_block
multiline_comment|/* Delete the x25iface encapsulation protocol instance&n; */
DECL|function|isdn_x25iface_proto_del
r_void
(def_block
id|isdn_x25iface_proto_del
c_func
(paren
r_struct
id|concap_proto
op_star
id|cprot
)paren
(brace
id|ix25_pdata_t
op_star
id|tmp
suffix:semicolon
id|IX25DEBUG
c_func
(paren
l_string|&quot;isdn_x25iface_proto_del &bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cprot
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;isdn_x25iface_proto_del: &quot;
l_string|&quot;concap_proto pointer is NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|tmp
op_assign
id|cprot
op_member_access_from_pointer
id|proto_data
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;isdn_x25iface_proto_del: inconsistent &quot;
l_string|&quot;proto_data pointer (maybe already deleted?)&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* close if the protocol is still open */
r_if
c_cond
(paren
id|cprot
op_member_access_from_pointer
id|dops
)paren
(brace
id|isdn_x25iface_proto_close
c_func
(paren
id|cprot
)paren
suffix:semicolon
)brace
multiline_comment|/* freeing the storage should be sufficient now. But some additional&n;&t;   settings might help to catch wild pointer bugs */
id|tmp
op_member_access_from_pointer
id|magic
op_assign
l_int|0
suffix:semicolon
id|cprot
op_member_access_from_pointer
id|proto_data
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)def_block
multiline_comment|/* (re-)initialize the data structures for x25iface encapsulation&n; */
DECL|function|isdn_x25iface_proto_restart
r_int
id|isdn_x25iface_proto_restart
c_func
(paren
r_struct
id|concap_proto
op_star
id|cprot
comma
r_struct
id|net_device
op_star
id|ndev
comma
r_struct
id|concap_device_ops
op_star
id|dops
)paren
(brace
id|ix25_pdata_t
op_star
id|pda
op_assign
id|cprot
op_member_access_from_pointer
id|proto_data
suffix:semicolon
id|ulong
id|flags
suffix:semicolon
id|IX25DEBUG
c_func
(paren
l_string|&quot;isdn_x25iface_proto_restart %s &bslash;n&quot;
comma
id|MY_DEVNAME
c_func
(paren
id|ndev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pdata_is_bad
c_func
(paren
id|pda
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dops
op_logical_and
id|dops
op_member_access_from_pointer
id|data_req
op_logical_and
id|dops
op_member_access_from_pointer
id|connect_req
op_logical_and
id|dops
op_member_access_from_pointer
id|disconn_req
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;isdn_x25iface_restart: required dops&quot;
l_string|&quot; missing&bslash;n&quot;
)paren
suffix:semicolon
id|isdn_x25iface_proto_close
c_func
(paren
id|cprot
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* avoid races with incoming events calling pops methods while&n;&t;&t; cprot members are inconsistent */
id|cprot
op_member_access_from_pointer
id|net_dev
op_assign
id|ndev
suffix:semicolon
id|cprot
op_member_access_from_pointer
id|pops
op_assign
op_amp
id|ix25_pops
suffix:semicolon
id|cprot
op_member_access_from_pointer
id|dops
op_assign
id|dops
suffix:semicolon
id|pda
op_member_access_from_pointer
id|state
op_assign
id|WAN_DISCONNECTED
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* deliver a dl_data frame received from i4l HL driver to the network layer &n; */
DECL|function|isdn_x25iface_receive
r_int
id|isdn_x25iface_receive
c_func
(paren
r_struct
id|concap_proto
op_star
id|cprot
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|IX25DEBUG
c_func
(paren
l_string|&quot;isdn_x25iface_receive %s &bslash;n&quot;
comma
id|MY_DEVNAME
c_func
(paren
id|cprot-&gt;net_dev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|ix25_pdata_t
op_star
)paren
(paren
id|cprot-&gt;proto_data
)paren
)paren
op_member_access_from_pointer
id|state
op_eq
id|WAN_CONNECTED
)paren
(brace
id|skb
op_member_access_from_pointer
id|dev
op_assign
id|cprot
op_member_access_from_pointer
id|net_dev
suffix:semicolon
id|skb
op_member_access_from_pointer
id|protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_X25
)paren
suffix:semicolon
id|skb
op_member_access_from_pointer
id|pkt_type
op_assign
id|PACKET_HOST
suffix:semicolon
r_if
c_cond
(paren
id|skb_push
c_func
(paren
id|skb
comma
l_int|1
)paren
)paren
(brace
id|skb
op_member_access_from_pointer
id|data
(braket
l_int|0
)braket
op_assign
l_int|0x00
suffix:semicolon
id|skb
op_member_access_from_pointer
id|mac.raw
op_assign
id|skb
op_member_access_from_pointer
id|data
suffix:semicolon
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;isdn_x25iface_receive %s: not connected, skb dropped&bslash;n&quot;
comma
id|MY_DEVNAME
c_func
(paren
id|cprot-&gt;net_dev
)paren
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* a connection set up is indicated by lower layer &n; */
DECL|function|isdn_x25iface_connect_ind
r_int
id|isdn_x25iface_connect_ind
c_func
(paren
r_struct
id|concap_proto
op_star
id|cprot
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_enum
id|wan_states
op_star
id|state_p
op_assign
op_amp
(paren
(paren
(paren
id|ix25_pdata_t
op_star
)paren
(paren
id|cprot-&gt;proto_data
)paren
)paren
op_member_access_from_pointer
id|state
)paren
suffix:semicolon
id|IX25DEBUG
c_func
(paren
l_string|&quot;isdn_x25iface_connect_ind %s &bslash;n&quot;
comma
id|MY_DEVNAME
c_func
(paren
id|cprot-&gt;net_dev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|state_p
op_eq
id|WAN_UNCONFIGURED
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;isdn_x25iface_connect_ind while unconfigured %s&bslash;n&quot;
comma
id|MY_DEVNAME
c_func
(paren
id|cprot-&gt;net_dev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
op_star
id|state_p
op_assign
id|WAN_CONNECTED
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
op_star
(paren
id|skb_put
c_func
(paren
id|skb
comma
l_int|1
)paren
)paren
op_assign
l_int|0x01
suffix:semicolon
id|skb
op_member_access_from_pointer
id|mac.raw
op_assign
id|skb
op_member_access_from_pointer
id|data
suffix:semicolon
id|skb
op_member_access_from_pointer
id|dev
op_assign
id|cprot
op_member_access_from_pointer
id|net_dev
suffix:semicolon
id|skb
op_member_access_from_pointer
id|protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_X25
)paren
suffix:semicolon
id|skb
op_member_access_from_pointer
id|pkt_type
op_assign
id|PACKET_HOST
suffix:semicolon
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;isdn_x25iface_connect_ind: &quot;
l_string|&quot; out of memory -- disconnecting&bslash;n&quot;
)paren
suffix:semicolon
id|cprot
op_member_access_from_pointer
id|dops
op_member_access_from_pointer
id|disconn_req
c_func
(paren
id|cprot
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* a disconnect is indicated by lower layer &n; */
DECL|function|isdn_x25iface_disconn_ind
r_int
id|isdn_x25iface_disconn_ind
c_func
(paren
r_struct
id|concap_proto
op_star
id|cprot
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_enum
id|wan_states
op_star
id|state_p
op_assign
op_amp
(paren
(paren
(paren
id|ix25_pdata_t
op_star
)paren
(paren
id|cprot-&gt;proto_data
)paren
)paren
op_member_access_from_pointer
id|state
)paren
suffix:semicolon
id|IX25DEBUG
c_func
(paren
l_string|&quot;isdn_x25iface_disconn_ind %s &bslash;n&quot;
comma
id|MY_DEVNAME
c_func
(paren
id|cprot
op_member_access_from_pointer
id|net_dev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|state_p
op_eq
id|WAN_UNCONFIGURED
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;isdn_x25iface_disconn_ind while unconfigured&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cprot
op_member_access_from_pointer
id|net_dev
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
op_star
id|state_p
op_assign
id|WAN_DISCONNECTED
suffix:semicolon
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
op_star
(paren
id|skb_put
c_func
(paren
id|skb
comma
l_int|1
)paren
)paren
op_assign
l_int|0x02
suffix:semicolon
id|skb
op_member_access_from_pointer
id|mac.raw
op_assign
id|skb
op_member_access_from_pointer
id|data
suffix:semicolon
id|skb
op_member_access_from_pointer
id|dev
op_assign
id|cprot
op_member_access_from_pointer
id|net_dev
suffix:semicolon
id|skb
op_member_access_from_pointer
id|protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_X25
)paren
suffix:semicolon
id|skb
op_member_access_from_pointer
id|pkt_type
op_assign
id|PACKET_HOST
suffix:semicolon
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;isdn_x25iface_disconn_ind:&quot;
l_string|&quot; out of memory&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* process a frame handed over to us from linux network layer. First byte&n;   semantics as defined in ../../Documentation/networking/x25-iface.txt &n;   */
DECL|function|isdn_x25iface_xmit
r_int
id|isdn_x25iface_xmit
c_func
(paren
r_struct
id|concap_proto
op_star
id|cprot
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
r_char
id|firstbyte
op_assign
id|skb-&gt;data
(braket
l_int|0
)braket
suffix:semicolon
r_int
op_star
id|state
op_assign
op_amp
(paren
(paren
(paren
id|ix25_pdata_t
op_star
)paren
(paren
id|cprot
op_member_access_from_pointer
id|proto_data
)paren
)paren
op_member_access_from_pointer
id|state
)paren
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|IX25DEBUG
c_func
(paren
l_string|&quot;isdn_x25iface_xmit: %s first=%x state=%d &bslash;n&quot;
comma
id|MY_DEVNAME
c_func
(paren
id|cprot
op_member_access_from_pointer
id|net_dev
)paren
comma
id|firstbyte
comma
op_star
id|state
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|firstbyte
)paren
(brace
r_case
l_int|0x00
suffix:colon
multiline_comment|/* dl_data request */
r_if
c_cond
(paren
op_star
id|state
op_eq
id|WAN_CONNECTED
)paren
(brace
id|skb_pull
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
id|cprot
op_member_access_from_pointer
id|net_dev
op_member_access_from_pointer
id|trans_start
op_assign
id|jiffies
suffix:semicolon
id|ret
op_assign
(paren
id|cprot
op_member_access_from_pointer
id|dops
op_member_access_from_pointer
id|data_req
c_func
(paren
id|cprot
comma
id|skb
)paren
)paren
suffix:semicolon
multiline_comment|/* prepare for future retransmissions */
r_if
c_cond
(paren
id|ret
)paren
(brace
id|skb_push
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
id|illegal_state_warn
c_func
(paren
op_star
id|state
comma
id|firstbyte
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x01
suffix:colon
multiline_comment|/* dl_connect request */
r_if
c_cond
(paren
op_star
id|state
op_eq
id|WAN_DISCONNECTED
)paren
(brace
op_star
id|state
op_assign
id|WAN_CONNECTING
suffix:semicolon
id|ret
op_assign
id|cprot
op_member_access_from_pointer
id|dops
op_member_access_from_pointer
id|connect_req
c_func
(paren
id|cprot
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
multiline_comment|/* reset state and notify upper layer about&n;&t;&t;&t;&t; * immidiatly failed attempts */
id|isdn_x25iface_disconn_ind
c_func
(paren
id|cprot
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|illegal_state_warn
c_func
(paren
op_star
id|state
comma
id|firstbyte
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|0x02
suffix:colon
multiline_comment|/* dl_disconnect request */
r_switch
c_cond
(paren
op_star
id|state
)paren
(brace
r_case
id|WAN_DISCONNECTED
suffix:colon
multiline_comment|/* Should not happen. However, give upper layer a&n;&t;&t;&t;   chance to recover from inconstistency  but don&squot;t&n;&t;&t;&t;   trust the lower layer sending the disconn_confirm&n;&t;&t;&t;   when already disconnected */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;isdn_x25iface_xmit: disconnect &quot;
l_string|&quot; requested while disconnected&bslash;n&quot;
)paren
suffix:semicolon
id|isdn_x25iface_disconn_ind
c_func
(paren
id|cprot
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* prevent infinite loops */
r_case
id|WAN_CONNECTING
suffix:colon
r_case
id|WAN_CONNECTED
suffix:colon
op_star
id|state
op_assign
id|WAN_DISCONNECTED
suffix:semicolon
id|cprot
op_member_access_from_pointer
id|dops
op_member_access_from_pointer
id|disconn_req
c_func
(paren
id|cprot
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|illegal_state_warn
c_func
(paren
op_star
id|state
comma
id|firstbyte
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|0x03
suffix:colon
multiline_comment|/* changing lapb parameters requested */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;isdn_x25iface_xmit: setting of lapb&quot;
l_string|&quot; options not yet supported&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;isdn_x25iface_xmit: frame with illegal&quot;
l_string|&quot; first byte %x ignored:&bslash;n&quot;
comma
id|firstbyte
)paren
suffix:semicolon
)brace
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
