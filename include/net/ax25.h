multiline_comment|/*&n; *&t;Declarations of AX.25 type objects.&n; *&n; *&t;Alan Cox (GW4PTS) &t;10/11/93&n; */
macro_line|#ifndef _AX25_H
DECL|macro|_AX25_H
mdefine_line|#define _AX25_H 
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ax25.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
DECL|macro|AX25_T1CLAMPLO
mdefine_line|#define&t;AX25_T1CLAMPLO  &t;&t;1
DECL|macro|AX25_T1CLAMPHI
mdefine_line|#define&t;AX25_T1CLAMPHI &t;&t;&t;(30 * HZ)
DECL|macro|AX25_BPQ_HEADER_LEN
mdefine_line|#define&t;AX25_BPQ_HEADER_LEN&t;&t;16
DECL|macro|AX25_KISS_HEADER_LEN
mdefine_line|#define&t;AX25_KISS_HEADER_LEN&t;&t;1
DECL|macro|AX25_HEADER_LEN
mdefine_line|#define&t;AX25_HEADER_LEN&t;&t;&t;17
DECL|macro|AX25_ADDR_LEN
mdefine_line|#define&t;AX25_ADDR_LEN&t;&t;&t;7
DECL|macro|AX25_DIGI_HEADER_LEN
mdefine_line|#define&t;AX25_DIGI_HEADER_LEN&t;&t;(AX25_MAX_DIGIS * AX25_ADDR_LEN)
DECL|macro|AX25_MAX_HEADER_LEN
mdefine_line|#define&t;AX25_MAX_HEADER_LEN&t;&t;(AX25_HEADER_LEN + AX25_DIGI_HEADER_LEN)
multiline_comment|/* AX.25 Protocol IDs */
DECL|macro|AX25_P_ROSE
mdefine_line|#define AX25_P_ROSE&t;&t;&t;0x01
DECL|macro|AX25_P_IP
mdefine_line|#define AX25_P_IP&t;&t;&t;0xCC
DECL|macro|AX25_P_ARP
mdefine_line|#define AX25_P_ARP&t;&t;&t;0xCD
DECL|macro|AX25_P_TEXT
mdefine_line|#define AX25_P_TEXT &t;&t;&t;0xF0
DECL|macro|AX25_P_NETROM
mdefine_line|#define AX25_P_NETROM &t;&t;&t;0xCF
DECL|macro|AX25_P_SEGMENT
mdefine_line|#define&t;AX25_P_SEGMENT&t;&t;&t;0x08
multiline_comment|/* AX.25 Segment control values */
DECL|macro|AX25_SEG_REM
mdefine_line|#define&t;AX25_SEG_REM&t;&t;&t;0x7F
DECL|macro|AX25_SEG_FIRST
mdefine_line|#define&t;AX25_SEG_FIRST&t;&t;&t;0x80
DECL|macro|AX25_CBIT
mdefine_line|#define AX25_CBIT&t;&t;&t;0x80&t;/* Command/Response bit */
DECL|macro|AX25_EBIT
mdefine_line|#define AX25_EBIT&t;&t;&t;0x01&t;/* HDLC Address Extension bit */
DECL|macro|AX25_HBIT
mdefine_line|#define AX25_HBIT&t;&t;&t;0x80&t;/* Has been repeated bit */
DECL|macro|AX25_SSSID_SPARE
mdefine_line|#define AX25_SSSID_SPARE&t;&t;0x60&t;/* Unused bits in SSID for standard AX.25 */
DECL|macro|AX25_ESSID_SPARE
mdefine_line|#define AX25_ESSID_SPARE&t;&t;0x20&t;/* Unused bits in SSID for extended AX.25 */
DECL|macro|AX25_DAMA_FLAG
mdefine_line|#define AX25_DAMA_FLAG&t;&t;&t;0x20&t;/* Well, it is *NOT* unused! (dl1bke 951121 */
DECL|macro|AX25_COND_ACK_PENDING
mdefine_line|#define&t;AX25_COND_ACK_PENDING&t;&t;0x01
DECL|macro|AX25_COND_REJECT
mdefine_line|#define&t;AX25_COND_REJECT&t;&t;0x02
DECL|macro|AX25_COND_PEER_RX_BUSY
mdefine_line|#define&t;AX25_COND_PEER_RX_BUSY&t;&t;0x04
DECL|macro|AX25_COND_OWN_RX_BUSY
mdefine_line|#define&t;AX25_COND_OWN_RX_BUSY&t;&t;0x08
DECL|macro|AX25_COND_DAMA_MODE
mdefine_line|#define&t;AX25_COND_DAMA_MODE&t;&t;0x10
macro_line|#ifndef _LINUX_NETDEVICE_H
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#endif
multiline_comment|/* Upper sub-layer (LAPB) definitions */
multiline_comment|/* Control field templates */
DECL|macro|AX25_I
mdefine_line|#define&t;AX25_I&t;&t;&t;0x00&t;/* Information frames */
DECL|macro|AX25_S
mdefine_line|#define&t;AX25_S&t;&t;&t;0x01&t;/* Supervisory frames */
DECL|macro|AX25_RR
mdefine_line|#define&t;AX25_RR&t;&t;&t;0x01&t;/* Receiver ready */
DECL|macro|AX25_RNR
mdefine_line|#define&t;AX25_RNR&t;&t;0x05&t;/* Receiver not ready */
DECL|macro|AX25_REJ
mdefine_line|#define&t;AX25_REJ&t;&t;0x09&t;/* Reject */
DECL|macro|AX25_U
mdefine_line|#define&t;AX25_U&t;&t;&t;0x03&t;/* Unnumbered frames */
DECL|macro|AX25_SABM
mdefine_line|#define&t;AX25_SABM&t;&t;0x2f&t;/* Set Asynchronous Balanced Mode */
DECL|macro|AX25_SABME
mdefine_line|#define&t;AX25_SABME&t;&t;0x6f&t;/* Set Asynchronous Balanced Mode Extended */
DECL|macro|AX25_DISC
mdefine_line|#define&t;AX25_DISC&t;&t;0x43&t;/* Disconnect */
DECL|macro|AX25_DM
mdefine_line|#define&t;AX25_DM&t;&t;&t;0x0f&t;/* Disconnected mode */
DECL|macro|AX25_UA
mdefine_line|#define&t;AX25_UA&t;&t;&t;0x63&t;/* Unnumbered acknowledge */
DECL|macro|AX25_FRMR
mdefine_line|#define&t;AX25_FRMR&t;&t;0x87&t;/* Frame reject */
DECL|macro|AX25_UI
mdefine_line|#define&t;AX25_UI&t;&t;&t;0x03&t;/* Unnumbered information */
DECL|macro|AX25_XID
mdefine_line|#define&t;AX25_XID&t;&t;0xaf&t;/* Exchange information */
DECL|macro|AX25_TEST
mdefine_line|#define&t;AX25_TEST&t;&t;0xe3&t;/* Test */
DECL|macro|AX25_PF
mdefine_line|#define&t;AX25_PF&t;&t;&t;0x10&t;/* Poll/final bit for standard AX.25 */
DECL|macro|AX25_EPF
mdefine_line|#define&t;AX25_EPF&t;&t;0x01&t;/* Poll/final bit for extended AX.25 */
DECL|macro|AX25_ILLEGAL
mdefine_line|#define AX25_ILLEGAL&t;&t;0x100&t;/* Impossible to be a real frame type */
DECL|macro|AX25_POLLOFF
mdefine_line|#define&t;AX25_POLLOFF&t;&t;0
DECL|macro|AX25_POLLON
mdefine_line|#define&t;AX25_POLLON&t;&t;1
multiline_comment|/* AX25 L2 C-bit */
DECL|macro|AX25_COMMAND
mdefine_line|#define AX25_COMMAND&t;&t;1
DECL|macro|AX25_RESPONSE
mdefine_line|#define AX25_RESPONSE&t;&t;2
multiline_comment|/* Define Link State constants. */
r_enum
(brace
DECL|enumerator|AX25_STATE_0
id|AX25_STATE_0
comma
DECL|enumerator|AX25_STATE_1
id|AX25_STATE_1
comma
DECL|enumerator|AX25_STATE_2
id|AX25_STATE_2
comma
DECL|enumerator|AX25_STATE_3
id|AX25_STATE_3
comma
DECL|enumerator|AX25_STATE_4
id|AX25_STATE_4
)brace
suffix:semicolon
DECL|macro|AX25_MODULUS
mdefine_line|#define AX25_MODULUS &t;&t;8&t;/*  Standard AX.25 modulus */
DECL|macro|AX25_EMODULUS
mdefine_line|#define&t;AX25_EMODULUS&t;&t;128&t;/*  Extended AX.25 modulus */
r_enum
(brace
DECL|enumerator|AX25_PROTO_STD_SIMPLEX
id|AX25_PROTO_STD_SIMPLEX
comma
DECL|enumerator|AX25_PROTO_STD_DUPLEX
id|AX25_PROTO_STD_DUPLEX
comma
DECL|enumerator|AX25_PROTO_DAMA_SLAVE
id|AX25_PROTO_DAMA_SLAVE
comma
DECL|enumerator|AX25_PROTO_DAMA_MASTER
id|AX25_PROTO_DAMA_MASTER
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|AX25_VALUES_IPDEFMODE
id|AX25_VALUES_IPDEFMODE
comma
multiline_comment|/* 0=DG 1=VC */
DECL|enumerator|AX25_VALUES_AXDEFMODE
id|AX25_VALUES_AXDEFMODE
comma
multiline_comment|/* 0=Normal 1=Extended Seq Nos */
DECL|enumerator|AX25_VALUES_BACKOFF
id|AX25_VALUES_BACKOFF
comma
multiline_comment|/* 0=None 1=Linear 2=Exponential */
DECL|enumerator|AX25_VALUES_CONMODE
id|AX25_VALUES_CONMODE
comma
multiline_comment|/* Allow connected modes - 0=No 1=no &quot;PID text&quot; 2=all PIDs */
DECL|enumerator|AX25_VALUES_WINDOW
id|AX25_VALUES_WINDOW
comma
multiline_comment|/* Default window size for standard AX.25 */
DECL|enumerator|AX25_VALUES_EWINDOW
id|AX25_VALUES_EWINDOW
comma
multiline_comment|/* Default window size for extended AX.25 */
DECL|enumerator|AX25_VALUES_T1
id|AX25_VALUES_T1
comma
multiline_comment|/* Default T1 timeout value */
DECL|enumerator|AX25_VALUES_T2
id|AX25_VALUES_T2
comma
multiline_comment|/* Default T2 timeout value */
DECL|enumerator|AX25_VALUES_T3
id|AX25_VALUES_T3
comma
multiline_comment|/* Default T3 timeout value */
DECL|enumerator|AX25_VALUES_IDLE
id|AX25_VALUES_IDLE
comma
multiline_comment|/* Connected mode idle timer */
DECL|enumerator|AX25_VALUES_N2
id|AX25_VALUES_N2
comma
multiline_comment|/* Default N2 value */
DECL|enumerator|AX25_VALUES_PACLEN
id|AX25_VALUES_PACLEN
comma
multiline_comment|/* AX.25 MTU */
DECL|enumerator|AX25_VALUES_PROTOCOL
id|AX25_VALUES_PROTOCOL
comma
multiline_comment|/* Std AX.25, DAMA Slave, DAMA Master */
DECL|enumerator|AX25_VALUES_DS_TIMEOUT
id|AX25_VALUES_DS_TIMEOUT
comma
multiline_comment|/* DAMA Slave timeout */
DECL|enumerator|AX25_MAX_VALUES
id|AX25_MAX_VALUES
multiline_comment|/* THIS MUST REMAIN THE LAST ENTRY OF THIS LIST */
)brace
suffix:semicolon
DECL|macro|AX25_DEF_IPDEFMODE
mdefine_line|#define&t;AX25_DEF_IPDEFMODE&t;0&t;&t;&t;/* Datagram */
DECL|macro|AX25_DEF_AXDEFMODE
mdefine_line|#define&t;AX25_DEF_AXDEFMODE&t;0&t;&t;&t;/* Normal */
DECL|macro|AX25_DEF_BACKOFF
mdefine_line|#define&t;AX25_DEF_BACKOFF&t;1&t;&t;&t;/* Linear backoff */
DECL|macro|AX25_DEF_CONMODE
mdefine_line|#define&t;AX25_DEF_CONMODE&t;2&t;&t;&t;/* Connected mode allowed */
DECL|macro|AX25_DEF_WINDOW
mdefine_line|#define&t;AX25_DEF_WINDOW&t;&t;2&t;&t;&t;/* Window=2 */
DECL|macro|AX25_DEF_EWINDOW
mdefine_line|#define&t;AX25_DEF_EWINDOW&t;32&t;&t;&t;/* Module-128 Window=32 */
DECL|macro|AX25_DEF_T1
mdefine_line|#define&t;AX25_DEF_T1&t;&t;(10 * HZ)&t;&t;/* T1=10s */
DECL|macro|AX25_DEF_T2
mdefine_line|#define&t;AX25_DEF_T2&t;&t;(3 * HZ)&t;&t;/* T2=3s  */
DECL|macro|AX25_DEF_T3
mdefine_line|#define&t;AX25_DEF_T3&t;&t;(300 * HZ)&t;&t;/* T3=300s */
DECL|macro|AX25_DEF_N2
mdefine_line|#define&t;AX25_DEF_N2&t;&t;10&t;&t;&t;/* N2=10 */
DECL|macro|AX25_DEF_IDLE
mdefine_line|#define AX25_DEF_IDLE&t;&t;(0 * 60 * HZ)&t;&t;/* Idle=None */
DECL|macro|AX25_DEF_PACLEN
mdefine_line|#define AX25_DEF_PACLEN&t;&t;256&t;&t;&t;/* Paclen=256 */
DECL|macro|AX25_DEF_PROTOCOL
mdefine_line|#define&t;AX25_DEF_PROTOCOL&t;AX25_PROTO_STD_SIMPLEX&t;/* Standard AX.25 */
DECL|macro|AX25_DEF_DS_TIMEOUT
mdefine_line|#define AX25_DEF_DS_TIMEOUT&t;(3 * 60 * HZ)&t;&t;/* DAMA timeout 3 minutes */
DECL|struct|ax25_uid_assoc
r_typedef
r_struct
id|ax25_uid_assoc
(brace
DECL|member|next
r_struct
id|ax25_uid_assoc
op_star
id|next
suffix:semicolon
DECL|member|uid
id|uid_t
id|uid
suffix:semicolon
DECL|member|call
id|ax25_address
id|call
suffix:semicolon
DECL|typedef|ax25_uid_assoc
)brace
id|ax25_uid_assoc
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|calls
id|ax25_address
id|calls
(braket
id|AX25_MAX_DIGIS
)braket
suffix:semicolon
DECL|member|repeated
r_int
r_char
id|repeated
(braket
id|AX25_MAX_DIGIS
)braket
suffix:semicolon
DECL|member|ndigi
r_int
r_char
id|ndigi
suffix:semicolon
DECL|member|lastrepeat
r_char
id|lastrepeat
suffix:semicolon
DECL|typedef|ax25_digi
)brace
id|ax25_digi
suffix:semicolon
DECL|struct|ax25_route
r_typedef
r_struct
id|ax25_route
(brace
DECL|member|next
r_struct
id|ax25_route
op_star
id|next
suffix:semicolon
DECL|member|ref
id|atomic_t
id|ref
suffix:semicolon
DECL|member|callsign
id|ax25_address
id|callsign
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|digipeat
id|ax25_digi
op_star
id|digipeat
suffix:semicolon
DECL|member|ip_mode
r_char
id|ip_mode
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|typedef|ax25_route
)brace
id|ax25_route
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|slave
r_char
id|slave
suffix:semicolon
multiline_comment|/* slave_mode?   */
DECL|member|slave_timer
r_struct
id|timer_list
id|slave_timer
suffix:semicolon
multiline_comment|/* timeout timer */
DECL|member|slave_timeout
r_int
r_int
id|slave_timeout
suffix:semicolon
multiline_comment|/* when? */
DECL|typedef|ax25_dama_info
)brace
id|ax25_dama_info
suffix:semicolon
r_struct
id|ctl_table
suffix:semicolon
DECL|struct|ax25_dev
r_typedef
r_struct
id|ax25_dev
(brace
DECL|member|next
r_struct
id|ax25_dev
op_star
id|next
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|forward
r_struct
id|net_device
op_star
id|forward
suffix:semicolon
DECL|member|systable
r_struct
id|ctl_table
op_star
id|systable
suffix:semicolon
DECL|member|values
r_int
id|values
(braket
id|AX25_MAX_VALUES
)braket
suffix:semicolon
macro_line|#if defined(CONFIG_AX25_DAMA_SLAVE) || defined(CONFIG_AX25_DAMA_MASTER)
DECL|member|dama
id|ax25_dama_info
id|dama
suffix:semicolon
macro_line|#endif
DECL|typedef|ax25_dev
)brace
id|ax25_dev
suffix:semicolon
DECL|struct|ax25_cb
r_typedef
r_struct
id|ax25_cb
(brace
DECL|member|next
r_struct
id|ax25_cb
op_star
id|next
suffix:semicolon
DECL|member|source_addr
DECL|member|dest_addr
id|ax25_address
id|source_addr
comma
id|dest_addr
suffix:semicolon
DECL|member|digipeat
id|ax25_digi
op_star
id|digipeat
suffix:semicolon
DECL|member|ax25_dev
id|ax25_dev
op_star
id|ax25_dev
suffix:semicolon
DECL|member|iamdigi
r_int
r_char
id|iamdigi
suffix:semicolon
DECL|member|state
DECL|member|modulus
DECL|member|pidincl
r_int
r_char
id|state
comma
id|modulus
comma
id|pidincl
suffix:semicolon
DECL|member|vs
DECL|member|vr
DECL|member|va
r_int
r_int
id|vs
comma
id|vr
comma
id|va
suffix:semicolon
DECL|member|condition
DECL|member|backoff
r_int
r_char
id|condition
comma
id|backoff
suffix:semicolon
DECL|member|n2
DECL|member|n2count
r_int
r_char
id|n2
comma
id|n2count
suffix:semicolon
DECL|member|t1timer
DECL|member|t2timer
DECL|member|t3timer
DECL|member|idletimer
r_struct
id|timer_list
id|t1timer
comma
id|t2timer
comma
id|t3timer
comma
id|idletimer
suffix:semicolon
DECL|member|t1
DECL|member|t2
DECL|member|t3
DECL|member|idle
DECL|member|rtt
r_int
r_int
id|t1
comma
id|t2
comma
id|t3
comma
id|idle
comma
id|rtt
suffix:semicolon
DECL|member|paclen
DECL|member|fragno
DECL|member|fraglen
r_int
r_int
id|paclen
comma
id|fragno
comma
id|fraglen
suffix:semicolon
DECL|member|write_queue
r_struct
id|sk_buff_head
id|write_queue
suffix:semicolon
DECL|member|reseq_queue
r_struct
id|sk_buff_head
id|reseq_queue
suffix:semicolon
DECL|member|ack_queue
r_struct
id|sk_buff_head
id|ack_queue
suffix:semicolon
DECL|member|frag_queue
r_struct
id|sk_buff_head
id|frag_queue
suffix:semicolon
DECL|member|window
r_int
r_char
id|window
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
multiline_comment|/* Backlink to socket */
DECL|typedef|ax25_cb
)brace
id|ax25_cb
suffix:semicolon
DECL|macro|ax25_sk
mdefine_line|#define ax25_sk(__sk) ((ax25_cb *)(__sk)-&gt;protinfo)
multiline_comment|/* af_ax25.c */
r_extern
id|ax25_cb
op_star
id|ax25_list
suffix:semicolon
r_extern
id|spinlock_t
id|ax25_list_lock
suffix:semicolon
r_extern
r_void
id|ax25_free_cb
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_insert_socket
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_struct
id|sock
op_star
id|ax25_find_listener
c_func
(paren
id|ax25_address
op_star
comma
r_int
comma
r_struct
id|net_device
op_star
comma
r_int
)paren
suffix:semicolon
r_struct
id|sock
op_star
id|ax25_get_socket
c_func
(paren
id|ax25_address
op_star
comma
id|ax25_address
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
id|ax25_cb
op_star
id|ax25_find_cb
c_func
(paren
id|ax25_address
op_star
comma
id|ax25_address
op_star
comma
id|ax25_digi
op_star
comma
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|sock
op_star
id|ax25_addr_match
c_func
(paren
id|ax25_address
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_send_to_raw
c_func
(paren
r_struct
id|sock
op_star
comma
r_struct
id|sk_buff
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ax25_destroy_socket
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
id|ax25_cb
op_star
id|ax25_create_cb
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ax25_fillin_cb
c_func
(paren
id|ax25_cb
op_star
comma
id|ax25_dev
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ax25_create
c_func
(paren
r_struct
id|socket
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|sock
op_star
id|ax25_make_new
c_func
(paren
r_struct
id|sock
op_star
comma
r_struct
id|ax25_dev
op_star
)paren
suffix:semicolon
multiline_comment|/* ax25_addr.c */
r_extern
id|ax25_address
id|null_ax25_address
suffix:semicolon
r_extern
r_char
op_star
id|ax2asc
c_func
(paren
id|ax25_address
op_star
)paren
suffix:semicolon
r_extern
id|ax25_address
op_star
id|asc2ax
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ax25cmp
c_func
(paren
id|ax25_address
op_star
comma
id|ax25_address
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ax25digicmp
c_func
(paren
id|ax25_digi
op_star
comma
id|ax25_digi
op_star
)paren
suffix:semicolon
r_extern
r_int
r_char
op_star
id|ax25_addr_parse
c_func
(paren
r_int
r_char
op_star
comma
r_int
comma
id|ax25_address
op_star
comma
id|ax25_address
op_star
comma
id|ax25_digi
op_star
comma
r_int
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ax25_addr_build
c_func
(paren
r_int
r_char
op_star
comma
id|ax25_address
op_star
comma
id|ax25_address
op_star
comma
id|ax25_digi
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ax25_addr_size
c_func
(paren
id|ax25_digi
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_digi_invert
c_func
(paren
id|ax25_digi
op_star
comma
id|ax25_digi
op_star
)paren
suffix:semicolon
multiline_comment|/* ax25_dev.c */
r_extern
id|ax25_dev
op_star
id|ax25_dev_list
suffix:semicolon
r_extern
id|spinlock_t
id|ax25_dev_lock
suffix:semicolon
DECL|function|ax25_dev_ax25dev
r_static
r_inline
id|ax25_dev
op_star
id|ax25_dev_ax25dev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
id|dev-&gt;ax25_ptr
suffix:semicolon
)brace
r_extern
id|ax25_dev
op_star
id|ax25_addr_ax25dev
c_func
(paren
id|ax25_address
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_dev_device_up
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_dev_device_down
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ax25_fwd_ioctl
c_func
(paren
r_int
r_int
comma
r_struct
id|ax25_fwd_struct
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|net_device
op_star
id|ax25_fwd_dev
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_dev_free
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* ax25_ds_in.c */
r_extern
r_int
id|ax25_ds_frame_in
c_func
(paren
id|ax25_cb
op_star
comma
r_struct
id|sk_buff
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* ax25_ds_subr.c */
r_extern
r_void
id|ax25_ds_nr_error_recovery
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_ds_enquiry_response
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_ds_establish_data_link
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_dev_dama_on
c_func
(paren
id|ax25_dev
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_dev_dama_off
c_func
(paren
id|ax25_dev
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_dama_on
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_dama_off
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
multiline_comment|/* ax25_ds_timer.c */
r_extern
r_void
id|ax25_ds_set_timer
c_func
(paren
id|ax25_dev
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_ds_del_timer
c_func
(paren
id|ax25_dev
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_ds_timer
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_ds_t1_timeout
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_ds_heartbeat_expiry
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_ds_t3timer_expiry
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_ds_idletimer_expiry
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
multiline_comment|/* ax25_iface.c */
r_extern
r_int
id|ax25_protocol_register
c_func
(paren
r_int
r_int
comma
r_int
(paren
op_star
)paren
(paren
r_struct
id|sk_buff
op_star
comma
id|ax25_cb
op_star
)paren
)paren
suffix:semicolon
r_extern
r_void
id|ax25_protocol_release
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ax25_linkfail_register
c_func
(paren
r_void
(paren
op_star
)paren
(paren
id|ax25_cb
op_star
comma
r_int
)paren
)paren
suffix:semicolon
r_extern
r_void
id|ax25_linkfail_release
c_func
(paren
r_void
(paren
op_star
)paren
(paren
id|ax25_cb
op_star
comma
r_int
)paren
)paren
suffix:semicolon
r_extern
r_int
id|ax25_listen_register
c_func
(paren
id|ax25_address
op_star
comma
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_listen_release
c_func
(paren
id|ax25_address
op_star
comma
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|ax25_protocol_function
c_func
(paren
r_int
r_int
)paren
)paren
(paren
r_struct
id|sk_buff
op_star
comma
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ax25_listen_mine
c_func
(paren
id|ax25_address
op_star
comma
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_link_failed
c_func
(paren
id|ax25_cb
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ax25_protocol_is_registered
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* ax25_in.c */
r_extern
r_int
id|ax25_rx_iframe
c_func
(paren
id|ax25_cb
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ax25_kiss_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|net_device
op_star
comma
r_struct
id|packet_type
op_star
)paren
suffix:semicolon
multiline_comment|/* ax25_ip.c */
r_extern
r_int
id|ax25_encapsulate
c_func
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|net_device
op_star
comma
r_int
r_int
comma
r_void
op_star
comma
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ax25_rebuild_header
c_func
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
multiline_comment|/* ax25_out.c */
r_extern
id|ax25_cb
op_star
id|ax25_send_frame
c_func
(paren
r_struct
id|sk_buff
op_star
comma
r_int
comma
id|ax25_address
op_star
comma
id|ax25_address
op_star
comma
id|ax25_digi
op_star
comma
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_output
c_func
(paren
id|ax25_cb
op_star
comma
r_int
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_kick
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_transmit_buffer
c_func
(paren
id|ax25_cb
op_star
comma
r_struct
id|sk_buff
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ax25_queue_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ax25_check_iframes_acked
c_func
(paren
id|ax25_cb
op_star
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* ax25_route.c */
r_extern
r_void
id|ax25_rt_device_down
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ax25_rt_ioctl
c_func
(paren
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ax25_rt_get_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ax25_rt_autobind
c_func
(paren
id|ax25_cb
op_star
comma
id|ax25_address
op_star
)paren
suffix:semicolon
r_extern
id|ax25_route
op_star
id|ax25_rt_find_route
c_func
(paren
id|ax25_route
op_star
comma
id|ax25_address
op_star
comma
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|sk_buff
op_star
id|ax25_rt_build_path
c_func
(paren
r_struct
id|sk_buff
op_star
comma
id|ax25_address
op_star
comma
id|ax25_address
op_star
comma
id|ax25_digi
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_rt_free
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|ax25_put_route
r_static
r_inline
r_void
id|ax25_put_route
c_func
(paren
id|ax25_route
op_star
id|ax25_rt
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|ax25_rt-&gt;ref
)paren
suffix:semicolon
)brace
multiline_comment|/* ax25_std_in.c */
r_extern
r_int
id|ax25_std_frame_in
c_func
(paren
id|ax25_cb
op_star
comma
r_struct
id|sk_buff
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* ax25_std_subr.c */
r_extern
r_void
id|ax25_std_nr_error_recovery
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_std_establish_data_link
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_std_transmit_enquiry
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_std_enquiry_response
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_std_timeout_response
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
multiline_comment|/* ax25_std_timer.c */
r_extern
r_void
id|ax25_std_heartbeat_expiry
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_std_t1timer_expiry
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_std_t2timer_expiry
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_std_t3timer_expiry
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_std_idletimer_expiry
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
multiline_comment|/* ax25_subr.c */
r_extern
r_void
id|ax25_clear_queues
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_frames_acked
c_func
(paren
id|ax25_cb
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ax25_requeue_frames
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ax25_validate_nr
c_func
(paren
id|ax25_cb
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ax25_decode
c_func
(paren
id|ax25_cb
op_star
comma
r_struct
id|sk_buff
op_star
comma
r_int
op_star
comma
r_int
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_send_control
c_func
(paren
id|ax25_cb
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ax25_return_dm
c_func
(paren
r_struct
id|net_device
op_star
comma
id|ax25_address
op_star
comma
id|ax25_address
op_star
comma
id|ax25_digi
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_calculate_t1
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_calculate_rtt
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_disconnect
c_func
(paren
id|ax25_cb
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* ax25_timer.c */
r_extern
r_void
id|ax25_start_heartbeat
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_start_t1timer
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_start_t2timer
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_start_t3timer
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_start_idletimer
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_stop_heartbeat
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_stop_t1timer
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_stop_t2timer
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_stop_t3timer
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ax25_stop_idletimer
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ax25_t1timer_running
c_func
(paren
id|ax25_cb
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ax25_display_timer
c_func
(paren
r_struct
id|timer_list
op_star
)paren
suffix:semicolon
multiline_comment|/* ax25_uid.c */
r_extern
r_int
id|ax25_uid_policy
suffix:semicolon
r_extern
id|ax25_address
op_star
id|ax25_findbyuid
c_func
(paren
id|uid_t
)paren
suffix:semicolon
r_extern
r_int
id|ax25_uid_ioctl
c_func
(paren
r_int
comma
r_struct
id|sockaddr_ax25
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ax25_uid_get_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ax25_uid_free
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* sysctl_net_ax25.c */
macro_line|#ifdef CONFIG_SYSCTL
r_extern
r_void
id|ax25_register_sysctl
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ax25_unregister_sysctl
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|function|ax25_register_sysctl
r_static
r_inline
r_void
id|ax25_register_sysctl
c_func
(paren
r_void
)paren
(brace
)brace
suffix:semicolon
DECL|function|ax25_unregister_sysctl
r_static
r_inline
r_void
id|ax25_unregister_sysctl
c_func
(paren
r_void
)paren
(brace
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_SYSCTL */
macro_line|#endif
eof
