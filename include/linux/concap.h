multiline_comment|/* $Id: concap.h,v 1.2 1999/08/23 15:54:21 keil Exp $&n;*/
macro_line|#ifndef _LINUX_CONCAP_H
DECL|macro|_LINUX_CONCAP_H
mdefine_line|#define _LINUX_CONCAP_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
multiline_comment|/* Stuff to support encapsulation protocols genericly. The encapsulation&n;   protocol is processed at the uppermost layer of the network interface.&n;&n;   (c) 1997 by Henner Eisen &lt;eis@baty.hanse.de&gt;&n;   This software is subject to the GNU General Public License.&n;&n;   Based on a ideas developed in a &squot;synchronous device&squot; thread in the&n;   linux-x25 mailing list contributed by Alan Cox, Thomasz Motylewski&n;   and Jonathan Naylor.&n;&n;   For more documetation on this refer to Documentation/isdn/README.concap&n;   */
r_struct
id|concap_proto_ops
suffix:semicolon
r_struct
id|concap_device_ops
suffix:semicolon
multiline_comment|/* this manages all data needed by the encapsulation protocol&n; */
DECL|struct|concap_proto
r_struct
id|concap_proto
(brace
DECL|member|net_dev
r_struct
id|net_device
op_star
id|net_dev
suffix:semicolon
multiline_comment|/* net device using our service  */
DECL|member|dops
r_struct
id|concap_device_ops
op_star
id|dops
suffix:semicolon
multiline_comment|/* callbacks provided by device */
DECL|member|pops
r_struct
id|concap_proto_ops
op_star
id|pops
suffix:semicolon
multiline_comment|/* callbacks provided by us */
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|proto_data
r_void
op_star
id|proto_data
suffix:semicolon
multiline_comment|/* protocol specific private data, to&n;&t;&t;&t;&t;&t;   be accessed via *pops methods only*/
multiline_comment|/*&n;&t;  :&n;&t;  whatever &n;&t;  :&n;&t;  */
)brace
suffix:semicolon
multiline_comment|/* Operations to be supported by the net device. Called by the encapsulation&n; * protocol entity. No receive method is offered because the encapsulation&n; * protocol directly calls netif_rx().&n; */
DECL|struct|concap_device_ops
r_struct
id|concap_device_ops
(brace
multiline_comment|/* to request data is submitted by device*/
DECL|member|data_req
r_int
(paren
op_star
id|data_req
)paren
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
multiline_comment|/* Control methods must be set to NULL by devices which do not&n;&t;   support connection control.*/
multiline_comment|/* to request a connection is set up */
DECL|member|connect_req
r_int
(paren
op_star
id|connect_req
)paren
(paren
r_struct
id|concap_proto
op_star
)paren
suffix:semicolon
multiline_comment|/* to request a connection is released */
DECL|member|disconn_req
r_int
(paren
op_star
id|disconn_req
)paren
(paren
r_struct
id|concap_proto
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Operations to be supported by the encapsulation protocol. Called by&n; * device driver.&n; */
DECL|struct|concap_proto_ops
r_struct
id|concap_proto_ops
(brace
multiline_comment|/* create a new encapsulation protocol instance of same type */
DECL|member|proto_new
r_struct
id|concap_proto
op_star
(paren
op_star
id|proto_new
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* delete encapsulation protocol instance and free all its resources.&n;&t;   cprot may no loger be referenced after calling this */
DECL|member|proto_del
r_void
(paren
op_star
id|proto_del
)paren
(paren
r_struct
id|concap_proto
op_star
id|cprot
)paren
suffix:semicolon
multiline_comment|/* initialize the protocol&squot;s data. To be called at interface startup&n;&t;   or when the device driver resets the interface. All services of the&n;&t;   encapsulation protocol may be used after this*/
DECL|member|restart
r_int
(paren
op_star
id|restart
)paren
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
suffix:semicolon
multiline_comment|/* inactivate an encapsulation protocol instance. The encapsulation&n;&t;   protocol may not call any *dops methods after this. */
DECL|member|close
r_int
(paren
op_star
id|close
)paren
(paren
r_struct
id|concap_proto
op_star
id|cprot
)paren
suffix:semicolon
multiline_comment|/* process a frame handed down to us by upper layer */
DECL|member|encap_and_xmit
r_int
(paren
op_star
id|encap_and_xmit
)paren
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
suffix:semicolon
multiline_comment|/* to be called for each data entity received from lower layer*/
DECL|member|data_ind
r_int
(paren
op_star
id|data_ind
)paren
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
suffix:semicolon
multiline_comment|/* to be called when a connection was set up/down.&n;&t;   Protocols that don&squot;t process these primitives might fill in&n;&t;   dummy methods here */
DECL|member|connect_ind
r_int
(paren
op_star
id|connect_ind
)paren
(paren
r_struct
id|concap_proto
op_star
id|cprot
)paren
suffix:semicolon
DECL|member|disconn_ind
r_int
(paren
op_star
id|disconn_ind
)paren
(paren
r_struct
id|concap_proto
op_star
id|cprot
)paren
suffix:semicolon
multiline_comment|/*&n;    Some network device support functions, like net_header(), rebuild_header(),&n;    and others, that depend solely on the encapsulation protocol, might&n;    be provided here, too. The net device would just fill them in its&n;    corresponding fields when it is opened.&n;    */
)brace
suffix:semicolon
multiline_comment|/* dummy restart/close/connect/reset/disconn methods&n; */
r_extern
r_int
id|concap_nop
c_func
(paren
r_struct
id|concap_proto
op_star
id|cprot
)paren
suffix:semicolon
multiline_comment|/* dummy submit method&n; */
r_extern
r_int
id|concap_drop_skb
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
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
