multiline_comment|/* Linux ISDN subsystem, network interface support code&n; *&n; * Copyright 1994-1998  by Fritz Elfert (fritz@isdn4linux.de)&n; *           1995,96    by Thinking Objects Software GmbH Wuerzburg&n; *           1995,96    by Michael Hipp (Michael.Hipp@student.uni-tuebingen.de)&n; *           1999-2002  by Kai Germaschewski &lt;kai@germaschewski.name&gt;&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; */
macro_line|#ifndef __ISDN_NET_LIB_H__
DECL|macro|__ISDN_NET_LIB_H__
mdefine_line|#define __ISDN_NET_LIB_H__
macro_line|#include &lt;linux/isdn.h&gt;
DECL|typedef|isdn_net_local
r_typedef
r_struct
id|isdn_net_local_s
id|isdn_net_local
suffix:semicolon
DECL|typedef|isdn_net_dev
r_typedef
r_struct
id|isdn_net_dev_s
id|isdn_net_dev
suffix:semicolon
DECL|struct|isdn_netif_ops
r_struct
id|isdn_netif_ops
(brace
DECL|member|hard_start_xmit
r_int
(paren
op_star
id|hard_start_xmit
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|member|hard_header
r_int
(paren
op_star
id|hard_header
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
comma
r_int
r_int
id|type
comma
r_void
op_star
id|daddr
comma
r_void
op_star
id|saddr
comma
r_int
id|len
)paren
suffix:semicolon
DECL|member|do_ioctl
r_int
(paren
op_star
id|do_ioctl
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ifreq
op_star
id|ifr
comma
r_int
id|cmd
)paren
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* interface flags (a la BSD)&t;*/
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* interface hardware type&t;*/
DECL|member|addr_len
r_int
r_char
id|addr_len
suffix:semicolon
multiline_comment|/* hardware address length&t;*/
DECL|member|receive
r_void
(paren
op_star
id|receive
)paren
(paren
r_struct
id|isdn_net_local_s
op_star
comma
r_struct
id|isdn_net_dev_s
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
DECL|member|connected
r_void
(paren
op_star
id|connected
)paren
(paren
r_struct
id|isdn_net_dev_s
op_star
)paren
suffix:semicolon
DECL|member|disconnected
r_void
(paren
op_star
id|disconnected
)paren
(paren
r_struct
id|isdn_net_dev_s
op_star
)paren
suffix:semicolon
DECL|member|bind
r_int
(paren
op_star
id|bind
)paren
(paren
r_struct
id|isdn_net_dev_s
op_star
)paren
suffix:semicolon
DECL|member|unbind
r_void
(paren
op_star
id|unbind
)paren
(paren
r_struct
id|isdn_net_dev_s
op_star
)paren
suffix:semicolon
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|isdn_net_local_s
op_star
)paren
suffix:semicolon
DECL|member|cleanup
r_void
(paren
op_star
id|cleanup
)paren
(paren
r_struct
id|isdn_net_local_s
op_star
)paren
suffix:semicolon
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|isdn_net_local_s
op_star
)paren
suffix:semicolon
DECL|member|close
r_void
(paren
op_star
id|close
)paren
(paren
r_struct
id|isdn_net_local_s
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* our interface to isdn_common.c */
r_void
id|isdn_net_lib_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|isdn_net_lib_exit
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|isdn_net_hangup_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|isdn_net_ioctl
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
id|uint
comma
id|ulong
)paren
suffix:semicolon
r_int
id|isdn_net_find_icall
c_func
(paren
r_int
comma
r_int
comma
r_int
comma
id|setup_parm
op_star
)paren
suffix:semicolon
multiline_comment|/* provided for interface types to use */
r_void
id|isdn_net_writebuf_skb
c_func
(paren
id|isdn_net_dev
op_star
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_void
id|isdn_net_write_super
c_func
(paren
id|isdn_net_dev
op_star
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_void
id|isdn_net_online
c_func
(paren
id|isdn_net_dev
op_star
id|idev
)paren
suffix:semicolon
r_void
id|isdn_net_offline
c_func
(paren
id|isdn_net_dev
op_star
id|idev
)paren
suffix:semicolon
r_int
id|isdn_net_start_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|ndev
)paren
suffix:semicolon
r_void
id|isdn_netif_rx
c_func
(paren
id|isdn_net_dev
op_star
id|idev
comma
r_struct
id|sk_buff
op_star
id|skb
comma
id|u16
id|protocol
)paren
suffix:semicolon
id|isdn_net_dev
op_star
id|isdn_net_get_xmit_dev
c_func
(paren
id|isdn_net_local
op_star
id|mlp
)paren
suffix:semicolon
r_int
id|isdn_net_hangup
c_func
(paren
id|isdn_net_dev
op_star
)paren
suffix:semicolon
r_int
id|isdn_net_autodial
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|ndev
)paren
suffix:semicolon
r_int
id|isdn_net_dial_req
c_func
(paren
id|isdn_net_dev
op_star
)paren
suffix:semicolon
r_int
id|register_isdn_netif
c_func
(paren
r_int
id|encap
comma
r_struct
id|isdn_netif_ops
op_star
id|ops
)paren
suffix:semicolon
multiline_comment|/* ====================================================================== */
multiline_comment|/* Feature- and status-flags for a net-interface */
DECL|macro|ISDN_NET_SECURE
mdefine_line|#define ISDN_NET_SECURE     0x02       /* Accept calls from phonelist only  */
DECL|macro|ISDN_NET_CALLBACK
mdefine_line|#define ISDN_NET_CALLBACK   0x04       /* activate callback                 */
DECL|macro|ISDN_NET_CBHUP
mdefine_line|#define ISDN_NET_CBHUP      0x08       /* hangup before callback            */
DECL|macro|ISDN_NET_CBOUT
mdefine_line|#define ISDN_NET_CBOUT      0x10       /* remote machine does callback      */
DECL|macro|ISDN_NET_MAGIC
mdefine_line|#define ISDN_NET_MAGIC      0x49344C02 /* for paranoia-checking             */
multiline_comment|/* Phone-list-element */
DECL|struct|isdn_net_phone
r_struct
id|isdn_net_phone
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|num
r_char
id|num
(braket
id|ISDN_MSNLEN
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* per network interface data (dev-&gt;priv) */
DECL|struct|isdn_net_local_s
r_struct
id|isdn_net_local_s
(brace
DECL|member|magic
id|ulong
id|magic
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
id|dev
suffix:semicolon
multiline_comment|/* interface to upper levels        */
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
multiline_comment|/* Ethernet Statistics              */
DECL|member|ops
r_struct
id|isdn_netif_ops
op_star
id|ops
suffix:semicolon
DECL|member|inl_priv
r_void
op_star
id|inl_priv
suffix:semicolon
multiline_comment|/* interface types can put their&n;&t;&t;&t;&t;&t;  private data here                */
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* Connection-flags                 */
DECL|member|dialmax
r_int
id|dialmax
suffix:semicolon
multiline_comment|/* Max. Number of Dial-retries      */
DECL|member|dialtimeout
r_int
id|dialtimeout
suffix:semicolon
multiline_comment|/* How long shall we try on dialing */
DECL|member|dialwait
r_int
id|dialwait
suffix:semicolon
multiline_comment|/* wait after failed attempt        */
DECL|member|cbdelay
r_int
id|cbdelay
suffix:semicolon
multiline_comment|/* Delay before Callback starts     */
DECL|member|msn
r_char
id|msn
(braket
id|ISDN_MSNLEN
)braket
suffix:semicolon
multiline_comment|/* MSNs/EAZs for this interface */
DECL|member|cbhup
id|u_char
id|cbhup
suffix:semicolon
multiline_comment|/* Flag: Reject Call before Callback*/
DECL|member|hupflags
r_int
id|hupflags
suffix:semicolon
multiline_comment|/* Flags for charge-unit-hangup:    */
DECL|member|onhtime
r_int
id|onhtime
suffix:semicolon
multiline_comment|/* Time to keep link up             */
DECL|member|p_encap
id|u_char
id|p_encap
suffix:semicolon
multiline_comment|/* Packet encapsulation             */
DECL|member|l2_proto
id|u_char
id|l2_proto
suffix:semicolon
multiline_comment|/* Layer-2-protocol                 */
DECL|member|l3_proto
id|u_char
id|l3_proto
suffix:semicolon
multiline_comment|/* Layer-3-protocol                 */
DECL|member|slavedelay
id|ulong
id|slavedelay
suffix:semicolon
multiline_comment|/* Dynamic bundling delaytime       */
DECL|member|triggercps
r_int
id|triggercps
suffix:semicolon
multiline_comment|/* BogoCPS needed for trigger slave */
DECL|member|phone
r_struct
id|list_head
id|phone
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* List of remote-phonenumbers      */
multiline_comment|/* phone[0] = Incoming Numbers      */
multiline_comment|/* phone[1] = Outgoing Numbers      */
DECL|member|slaves
r_struct
id|list_head
id|slaves
suffix:semicolon
multiline_comment|/* list of all bundled channels    &n;&t;&t;&t;&t;&t;  protected by serializing config&n;&t;&t;&t;&t;&t;  ioctls / no change allowed when&n;&t;&t;&t;&t;&t;  interface is running             */
DECL|member|online
r_struct
id|list_head
id|online
suffix:semicolon
multiline_comment|/* list of all bundled channels &n;&t;&t;&t;&t;&t;  which can be used for actual&n;&t;&t;&t;&t;&t;  data (IP) transfer              &n;&t;&t;&t;&t;&t;  protected by xmit_lock           */
DECL|member|xmit_lock
id|spinlock_t
id|xmit_lock
suffix:semicolon
multiline_comment|/* used to protect the xmit path of &n;&t;&t;&t;&t;&t;  a net_device, including all&n;&t;&t;&t;&t;&t;  associated channels&squot;s frame_cnt  */
DECL|member|running_devs
r_struct
id|list_head
id|running_devs
suffix:semicolon
multiline_comment|/* member of global running_devs    */
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
multiline_comment|/* references held by ISDN code     */
)brace
suffix:semicolon
multiline_comment|/* per ISDN channel (ISDN interface) data */
DECL|struct|isdn_net_dev_s
r_struct
id|isdn_net_dev_s
(brace
DECL|member|isdn_slot
r_int
id|isdn_slot
suffix:semicolon
multiline_comment|/* Index to isdn device/channel     */
DECL|member|pre_device
r_int
id|pre_device
suffix:semicolon
multiline_comment|/* Preselected isdn-device          */
DECL|member|pre_channel
r_int
id|pre_channel
suffix:semicolon
multiline_comment|/* Preselected isdn-channel         */
DECL|member|exclusive
r_int
id|exclusive
suffix:semicolon
multiline_comment|/* -1 if non excl./idx to excl chan */
DECL|member|dial_timer
r_struct
id|timer_list
id|dial_timer
suffix:semicolon
multiline_comment|/* dial events timer                */
DECL|member|fi
r_struct
id|fsm_inst
id|fi
suffix:semicolon
multiline_comment|/* call control state machine       */
DECL|member|dial_event
r_int
id|dial_event
suffix:semicolon
multiline_comment|/* event in case of timer expiry    */
DECL|member|dial
r_int
id|dial
suffix:semicolon
multiline_comment|/* # of phone number just dialed    */
DECL|member|outgoing
r_int
id|outgoing
suffix:semicolon
multiline_comment|/* Flag: outgoing call              */
DECL|member|dialretry
r_int
id|dialretry
suffix:semicolon
multiline_comment|/* Counter for Dialout-retries      */
DECL|member|cps
r_int
id|cps
suffix:semicolon
multiline_comment|/* current speed of this interface  */
DECL|member|transcount
r_int
id|transcount
suffix:semicolon
multiline_comment|/* byte-counter for cps-calculation */
DECL|member|last_jiffies
r_int
id|last_jiffies
suffix:semicolon
multiline_comment|/* when transcount was reset        */
DECL|member|sqfull
r_int
id|sqfull
suffix:semicolon
multiline_comment|/* Flag: netdev-queue overloaded    */
DECL|member|sqfull_stamp
id|ulong
id|sqfull_stamp
suffix:semicolon
multiline_comment|/* Start-Time of overload           */
DECL|member|huptimer
r_int
id|huptimer
suffix:semicolon
multiline_comment|/* Timeout-counter for auto-hangup  */
DECL|member|charge
r_int
id|charge
suffix:semicolon
multiline_comment|/* Counter for charging units       */
DECL|member|charge_state
r_int
id|charge_state
suffix:semicolon
multiline_comment|/* ChargeInfo state machine         */
DECL|member|chargetime
r_int
r_int
id|chargetime
suffix:semicolon
multiline_comment|/* Timer for Charging info          */
DECL|member|chargeint
r_int
id|chargeint
suffix:semicolon
multiline_comment|/* Interval between charge-infos    */
DECL|member|pppbind
r_int
id|pppbind
suffix:semicolon
multiline_comment|/* ippp device for bindings         */
DECL|member|super_tx_queue
r_struct
id|sk_buff_head
id|super_tx_queue
suffix:semicolon
multiline_comment|/* List of supervisory frames to  */
multiline_comment|/* be transmitted asap              */
DECL|member|frame_cnt
r_int
id|frame_cnt
suffix:semicolon
multiline_comment|/* number of frames currently       */
multiline_comment|/* queued in HL driver              */
DECL|member|tlet
r_struct
id|tasklet_struct
id|tlet
suffix:semicolon
DECL|member|mlp
id|isdn_net_local
op_star
id|mlp
suffix:semicolon
multiline_comment|/* Ptr to master device for all devs*/
DECL|member|slaves
r_struct
id|list_head
id|slaves
suffix:semicolon
multiline_comment|/* member of local-&gt;slaves          */
DECL|member|online
r_struct
id|list_head
id|online
suffix:semicolon
multiline_comment|/* member of local-&gt;online          */
DECL|member|name
r_char
id|name
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* Name of device                   */
DECL|member|global_list
r_struct
id|list_head
id|global_list
suffix:semicolon
multiline_comment|/* global list of all isdn_net_devs */
DECL|member|ind_priv
r_void
op_star
id|ind_priv
suffix:semicolon
multiline_comment|/* interface types can put their&n;&t;&t;&t;&t;&t;  private data here                */
)brace
suffix:semicolon
multiline_comment|/* ====================================================================== */
r_static
r_inline
r_int
DECL|function|put_u8
id|put_u8
c_func
(paren
r_int
r_char
op_star
id|p
comma
id|u8
id|x
)paren
(brace
op_star
id|p
op_assign
id|x
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|put_u16
id|put_u16
c_func
(paren
r_int
r_char
op_star
id|p
comma
id|u16
id|x
)paren
(brace
op_star
(paren
(paren
id|u16
op_star
)paren
id|p
)paren
op_assign
id|htons
c_func
(paren
id|x
)paren
suffix:semicolon
r_return
l_int|2
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|put_u32
id|put_u32
c_func
(paren
r_int
r_char
op_star
id|p
comma
id|u32
id|x
)paren
(brace
op_star
(paren
(paren
id|u32
op_star
)paren
id|p
)paren
op_assign
id|htonl
c_func
(paren
id|x
)paren
suffix:semicolon
r_return
l_int|4
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|get_u8
id|get_u8
c_func
(paren
r_int
r_char
op_star
id|p
comma
id|u8
op_star
id|x
)paren
(brace
op_star
id|x
op_assign
op_star
id|p
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|get_u16
id|get_u16
c_func
(paren
r_int
r_char
op_star
id|p
comma
id|u16
op_star
id|x
)paren
(brace
op_star
id|x
op_assign
id|ntohs
c_func
(paren
op_star
(paren
(paren
id|u16
op_star
)paren
id|p
)paren
)paren
suffix:semicolon
r_return
l_int|2
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|get_u32
id|get_u32
c_func
(paren
r_int
r_char
op_star
id|p
comma
id|u32
op_star
id|x
)paren
(brace
op_star
id|x
op_assign
id|ntohl
c_func
(paren
op_star
(paren
(paren
id|u32
op_star
)paren
id|p
)paren
)paren
suffix:semicolon
r_return
l_int|4
suffix:semicolon
)brace
macro_line|#endif
eof
