macro_line|#ifndef _LAPB_H
DECL|macro|_LAPB_H
mdefine_line|#define _LAPB_H 
macro_line|#include &lt;linux/lapb.h&gt;
DECL|macro|LAPB_HEADER_LEN
mdefine_line|#define&t;LAPB_HEADER_LEN&t;20&t;&t;/* LAPB over Ethernet + a bit more */
DECL|macro|LAPB_ACK_PENDING_CONDITION
mdefine_line|#define&t;LAPB_ACK_PENDING_CONDITION&t;0x01
DECL|macro|LAPB_REJECT_CONDITION
mdefine_line|#define&t;LAPB_REJECT_CONDITION&t;&t;0x02
DECL|macro|LAPB_PEER_RX_BUSY_CONDITION
mdefine_line|#define&t;LAPB_PEER_RX_BUSY_CONDITION&t;0x04
multiline_comment|/* Control field templates */
DECL|macro|LAPB_I
mdefine_line|#define&t;LAPB_I&t;&t;0x00&t;/* Information frames */
DECL|macro|LAPB_S
mdefine_line|#define&t;LAPB_S&t;&t;0x01&t;/* Supervisory frames */
DECL|macro|LAPB_U
mdefine_line|#define&t;LAPB_U&t;&t;0x03&t;/* Unnumbered frames */
DECL|macro|LAPB_RR
mdefine_line|#define&t;LAPB_RR&t;&t;0x01&t;/* Receiver ready */
DECL|macro|LAPB_RNR
mdefine_line|#define&t;LAPB_RNR&t;0x05&t;/* Receiver not ready */
DECL|macro|LAPB_REJ
mdefine_line|#define&t;LAPB_REJ&t;0x09&t;/* Reject */
DECL|macro|LAPB_SABM
mdefine_line|#define&t;LAPB_SABM&t;0x2F&t;/* Set Asynchronous Balanced Mode */
DECL|macro|LAPB_SABME
mdefine_line|#define&t;LAPB_SABME&t;0x6F&t;/* Set Asynchronous Balanced Mode Extended */
DECL|macro|LAPB_DISC
mdefine_line|#define&t;LAPB_DISC&t;0x43&t;/* Disconnect */
DECL|macro|LAPB_DM
mdefine_line|#define&t;LAPB_DM&t;&t;0x0F&t;/* Disconnected mode */
DECL|macro|LAPB_UA
mdefine_line|#define&t;LAPB_UA&t;&t;0x63&t;/* Unnumbered acknowledge */
DECL|macro|LAPB_FRMR
mdefine_line|#define&t;LAPB_FRMR&t;0x87&t;/* Frame reject */
DECL|macro|LAPB_ILLEGAL
mdefine_line|#define LAPB_ILLEGAL&t;0x100&t;/* Impossible to be a real frame type */
DECL|macro|LAPB_SPF
mdefine_line|#define&t;LAPB_SPF&t;0x10&t;/* Poll/final bit for standard LAPB */
DECL|macro|LAPB_EPF
mdefine_line|#define&t;LAPB_EPF&t;0x01&t;/* Poll/final bit for extended LAPB */
DECL|macro|LAPB_FRMR_W
mdefine_line|#define&t;LAPB_FRMR_W&t;0x01&t;/* Control field invalid&t;*/
DECL|macro|LAPB_FRMR_X
mdefine_line|#define&t;LAPB_FRMR_X&t;0x02&t;/* I field invalid&t;&t;*/
DECL|macro|LAPB_FRMR_Y
mdefine_line|#define&t;LAPB_FRMR_Y&t;0x04&t;/* I field too long&t;&t;*/
DECL|macro|LAPB_FRMR_Z
mdefine_line|#define&t;LAPB_FRMR_Z&t;0x08&t;/* Invalid N(R)&t;&t;&t;*/
DECL|macro|LAPB_POLLOFF
mdefine_line|#define&t;LAPB_POLLOFF&t;0
DECL|macro|LAPB_POLLON
mdefine_line|#define&t;LAPB_POLLON&t;1
multiline_comment|/* LAPB C-bit */
DECL|macro|LAPB_COMMAND
mdefine_line|#define LAPB_COMMAND&t;1
DECL|macro|LAPB_RESPONSE
mdefine_line|#define LAPB_RESPONSE&t;2
DECL|macro|LAPB_ADDR_A
mdefine_line|#define&t;LAPB_ADDR_A&t;0x03
DECL|macro|LAPB_ADDR_B
mdefine_line|#define&t;LAPB_ADDR_B&t;0x01
DECL|macro|LAPB_ADDR_C
mdefine_line|#define&t;LAPB_ADDR_C&t;0x0F
DECL|macro|LAPB_ADDR_D
mdefine_line|#define&t;LAPB_ADDR_D&t;0x07
multiline_comment|/* Define Link State constants. */
r_enum
(brace
DECL|enumerator|LAPB_STATE_0
id|LAPB_STATE_0
comma
multiline_comment|/* Disconnected State&t;&t;*/
DECL|enumerator|LAPB_STATE_1
id|LAPB_STATE_1
comma
multiline_comment|/* Awaiting Connection State&t;*/
DECL|enumerator|LAPB_STATE_2
id|LAPB_STATE_2
comma
multiline_comment|/* Awaiting Disconnection State&t;*/
DECL|enumerator|LAPB_STATE_3
id|LAPB_STATE_3
comma
multiline_comment|/* Data Transfer State&t;&t;*/
DECL|enumerator|LAPB_STATE_4
id|LAPB_STATE_4
multiline_comment|/* Frame Reject State&t;&t;*/
)brace
suffix:semicolon
DECL|macro|LAPB_DEFAULT_MODE
mdefine_line|#define&t;LAPB_DEFAULT_MODE&t;&t;(LAPB_STANDARD | LAPB_SLP | LAPB_DTE)
DECL|macro|LAPB_DEFAULT_WINDOW
mdefine_line|#define&t;LAPB_DEFAULT_WINDOW&t;&t;7&t;&t;/* Window=7 */
DECL|macro|LAPB_DEFAULT_T1
mdefine_line|#define&t;LAPB_DEFAULT_T1&t;&t;&t;(5 * HZ)&t;/* T1=5s    */
DECL|macro|LAPB_DEFAULT_T2
mdefine_line|#define&t;LAPB_DEFAULT_T2&t;&t;&t;(1 * HZ)&t;/* T2=1s    */
DECL|macro|LAPB_DEFAULT_N2
mdefine_line|#define&t;LAPB_DEFAULT_N2&t;&t;&t;20&t;&t;/* N2=20    */
DECL|macro|LAPB_SMODULUS
mdefine_line|#define&t;LAPB_SMODULUS&t;8
DECL|macro|LAPB_EMODULUS
mdefine_line|#define&t;LAPB_EMODULUS&t;128
multiline_comment|/*&n; *&t;Information about the current frame.&n; */
DECL|struct|lapb_frame
r_struct
id|lapb_frame
(brace
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* Parsed type&t;&t;*/
DECL|member|nr
DECL|member|ns
r_int
r_int
id|nr
comma
id|ns
suffix:semicolon
multiline_comment|/* N(R), N(S)&t;&t;*/
DECL|member|cr
r_int
r_char
id|cr
suffix:semicolon
multiline_comment|/* Command/Response&t;*/
DECL|member|pf
r_int
r_char
id|pf
suffix:semicolon
multiline_comment|/* Poll/Final&t;&t;*/
DECL|member|control
r_int
r_char
id|control
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Original control data*/
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;The per LAPB connection control structure.&n; */
DECL|struct|lapb_cb
r_struct
id|lapb_cb
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|token
r_void
op_star
id|token
suffix:semicolon
multiline_comment|/* Link status fields */
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
DECL|member|state
r_int
r_char
id|state
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
r_int
r_char
id|condition
suffix:semicolon
DECL|member|n2
DECL|member|n2count
r_int
r_int
id|n2
comma
id|n2count
suffix:semicolon
DECL|member|t1
DECL|member|t2
r_int
r_int
id|t1
comma
id|t2
suffix:semicolon
DECL|member|t1timer
DECL|member|t2timer
r_struct
id|timer_list
id|t1timer
comma
id|t2timer
suffix:semicolon
multiline_comment|/* Internal control information */
DECL|member|write_queue
r_struct
id|sk_buff_head
id|write_queue
suffix:semicolon
DECL|member|ack_queue
r_struct
id|sk_buff_head
id|ack_queue
suffix:semicolon
DECL|member|window
r_int
r_char
id|window
suffix:semicolon
DECL|member|callbacks
r_struct
id|lapb_register_struct
id|callbacks
suffix:semicolon
multiline_comment|/* FRMR control information */
DECL|member|frmr_data
r_struct
id|lapb_frame
id|frmr_data
suffix:semicolon
DECL|member|frmr_type
r_int
r_char
id|frmr_type
suffix:semicolon
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* lapb_iface.c */
r_extern
r_void
id|lapb_connect_confirmation
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|lapb_connect_indication
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|lapb_disconnect_confirmation
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|lapb_disconnect_indication
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|lapb_data_indication
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_int
id|lapb_data_transmit
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
multiline_comment|/* lapb_in.c */
r_extern
r_void
id|lapb_data_input
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
multiline_comment|/* lapb_out.c */
r_extern
r_void
id|lapb_kick
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
)paren
suffix:semicolon
r_extern
r_void
id|lapb_transmit_buffer
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
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
id|lapb_establish_data_link
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
)paren
suffix:semicolon
r_extern
r_void
id|lapb_enquiry_response
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
)paren
suffix:semicolon
r_extern
r_void
id|lapb_timeout_response
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
)paren
suffix:semicolon
r_extern
r_void
id|lapb_check_iframes_acked
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|lapb_check_need_response
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* lapb_subr.c */
r_extern
r_void
id|lapb_clear_queues
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
)paren
suffix:semicolon
r_extern
r_void
id|lapb_frames_acked
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|lapb_requeue_frames
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
)paren
suffix:semicolon
r_extern
r_int
id|lapb_validate_nr
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|lapb_decode
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
comma
r_struct
id|sk_buff
op_star
comma
r_struct
id|lapb_frame
op_star
)paren
suffix:semicolon
r_extern
r_void
id|lapb_send_control
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
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
id|lapb_transmit_frmr
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
)paren
suffix:semicolon
multiline_comment|/* lapb_timer.c */
r_extern
r_void
id|lapb_start_t1timer
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
)paren
suffix:semicolon
r_extern
r_void
id|lapb_start_t2timer
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
)paren
suffix:semicolon
r_extern
r_void
id|lapb_stop_t1timer
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
)paren
suffix:semicolon
r_extern
r_void
id|lapb_stop_t2timer
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
)paren
suffix:semicolon
r_extern
r_int
id|lapb_t1timer_running
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
)paren
suffix:semicolon
multiline_comment|/*&n; * Debug levels.&n; *&t;0 = Off&n; *&t;1 = State Changes&n; *&t;2 = Packets I/O and State Changes&n; *&t;3 = Hex dumps, Packets I/O and State Changes.&n; */
DECL|macro|LAPB_DEBUG
mdefine_line|#define&t;LAPB_DEBUG&t;0
macro_line|#endif
eof
