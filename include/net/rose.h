multiline_comment|/*&n; *&t;Declarations of Rose type objects.&n; *&n; *&t;Jonathan Naylor G4KLX&t;25/8/96&n; */
macro_line|#ifndef _ROSE_H
DECL|macro|_ROSE_H
mdefine_line|#define _ROSE_H 
macro_line|#include &lt;linux/rose.h&gt;
DECL|macro|ROSE_ADDR_LEN
mdefine_line|#define&t;ROSE_ADDR_LEN&t;&t;&t;5
DECL|macro|ROSE_MIN_LEN
mdefine_line|#define&t;ROSE_MIN_LEN&t;&t;&t;3
DECL|macro|ROSE_GFI
mdefine_line|#define&t;ROSE_GFI&t;&t;&t;0x10
DECL|macro|ROSE_Q_BIT
mdefine_line|#define&t;ROSE_Q_BIT&t;&t;&t;0x80
DECL|macro|ROSE_D_BIT
mdefine_line|#define&t;ROSE_D_BIT&t;&t;&t;0x40
DECL|macro|ROSE_M_BIT
mdefine_line|#define&t;ROSE_M_BIT&t;&t;&t;0x10
DECL|macro|ROSE_CALL_REQUEST
mdefine_line|#define&t;ROSE_CALL_REQUEST&t;&t;0x0B
DECL|macro|ROSE_CALL_ACCEPTED
mdefine_line|#define&t;ROSE_CALL_ACCEPTED&t;&t;0x0F
DECL|macro|ROSE_CLEAR_REQUEST
mdefine_line|#define&t;ROSE_CLEAR_REQUEST&t;&t;0x13
DECL|macro|ROSE_CLEAR_CONFIRMATION
mdefine_line|#define&t;ROSE_CLEAR_CONFIRMATION&t;&t;0x17
DECL|macro|ROSE_DATA
mdefine_line|#define&t;ROSE_DATA&t;&t;&t;0x00
DECL|macro|ROSE_INTERRUPT
mdefine_line|#define&t;ROSE_INTERRUPT&t;&t;&t;0x23
DECL|macro|ROSE_INTERRUPT_CONFIRMATION
mdefine_line|#define&t;ROSE_INTERRUPT_CONFIRMATION&t;0x27
DECL|macro|ROSE_RR
mdefine_line|#define&t;ROSE_RR&t;&t;&t;&t;0x01
DECL|macro|ROSE_RNR
mdefine_line|#define&t;ROSE_RNR&t;&t;&t;0x05
DECL|macro|ROSE_REJ
mdefine_line|#define&t;ROSE_REJ&t;&t;&t;0x09
DECL|macro|ROSE_RESET_REQUEST
mdefine_line|#define&t;ROSE_RESET_REQUEST&t;&t;0x1B
DECL|macro|ROSE_RESET_CONFIRMATION
mdefine_line|#define&t;ROSE_RESET_CONFIRMATION&t;&t;0x1F
DECL|macro|ROSE_REGISTRATION_REQUEST
mdefine_line|#define&t;ROSE_REGISTRATION_REQUEST&t;0xF3
DECL|macro|ROSE_REGISTRATION_CONFIRMATION
mdefine_line|#define&t;ROSE_REGISTRATION_CONFIRMATION&t;0xF7
DECL|macro|ROSE_RESTART_REQUEST
mdefine_line|#define&t;ROSE_RESTART_REQUEST&t;&t;0xFB
DECL|macro|ROSE_RESTART_CONFIRMATION
mdefine_line|#define&t;ROSE_RESTART_CONFIRMATION&t;0xFF
DECL|macro|ROSE_DIAGNOSTIC
mdefine_line|#define&t;ROSE_DIAGNOSTIC&t;&t;&t;0xF1
DECL|macro|ROSE_ILLEGAL
mdefine_line|#define&t;ROSE_ILLEGAL&t;&t;&t;0xFD
multiline_comment|/* Define Link State constants. */
r_enum
(brace
DECL|enumerator|ROSE_STATE_0
id|ROSE_STATE_0
comma
multiline_comment|/* Ready */
DECL|enumerator|ROSE_STATE_1
id|ROSE_STATE_1
comma
multiline_comment|/* Awaiting Call Accepted */
DECL|enumerator|ROSE_STATE_2
id|ROSE_STATE_2
comma
multiline_comment|/* Awaiting Clear Confirmation */
DECL|enumerator|ROSE_STATE_3
id|ROSE_STATE_3
comma
multiline_comment|/* Data Transfer */
DECL|enumerator|ROSE_STATE_4
id|ROSE_STATE_4
comma
multiline_comment|/* Awaiting Reset Confirmation */
DECL|enumerator|ROSE_STATE_5
id|ROSE_STATE_5
multiline_comment|/* Deferred Call Acceptance */
)brace
suffix:semicolon
DECL|macro|ROSE_DEFAULT_T0
mdefine_line|#define ROSE_DEFAULT_T0&t;&t;&t;(180 * HZ)&t;/* Default T10 T20 value */
DECL|macro|ROSE_DEFAULT_T1
mdefine_line|#define ROSE_DEFAULT_T1&t;&t;&t;(200 * HZ)&t;/* Default T11 T21 value */
DECL|macro|ROSE_DEFAULT_T2
mdefine_line|#define ROSE_DEFAULT_T2&t;&t;&t;(180 * HZ)&t;/* Default T12 T22 value */
DECL|macro|ROSE_DEFAULT_T3
mdefine_line|#define&t;ROSE_DEFAULT_T3&t;&t;&t;(180 * HZ)&t;/* Default T13 T23 value */
DECL|macro|ROSE_DEFAULT_HB
mdefine_line|#define&t;ROSE_DEFAULT_HB&t;&t;&t;(5 * HZ)&t;/* Default Holdback value */
DECL|macro|ROSE_DEFAULT_IDLE
mdefine_line|#define&t;ROSE_DEFAULT_IDLE&t;&t;(0 * 60 * HZ)&t;/* No Activity Timeout - none */
DECL|macro|ROSE_DEFAULT_ROUTING
mdefine_line|#define&t;ROSE_DEFAULT_ROUTING&t;&t;1&t;&t;/* Default routing flag */
DECL|macro|ROSE_DEFAULT_FAIL_TIMEOUT
mdefine_line|#define&t;ROSE_DEFAULT_FAIL_TIMEOUT&t;(120 * HZ)&t;/* Time until link considered usable */
DECL|macro|ROSE_DEFAULT_MAXVC
mdefine_line|#define&t;ROSE_DEFAULT_MAXVC&t;&t;50&t;&t;/* Maximum number of VCs per neighbour */
DECL|macro|ROSE_DEFAULT_WINDOW_SIZE
mdefine_line|#define&t;ROSE_DEFAULT_WINDOW_SIZE&t;7&t;&t;/* Default window size */
DECL|macro|ROSE_MODULUS
mdefine_line|#define ROSE_MODULUS &t;&t;&t;8
DECL|macro|ROSE_MAX_PACKET_SIZE
mdefine_line|#define&t;ROSE_MAX_PACKET_SIZE&t;&t;251&t;&t;/* Maximum packet size */
DECL|macro|ROSE_COND_ACK_PENDING
mdefine_line|#define&t;ROSE_COND_ACK_PENDING&t;&t;0x01
DECL|macro|ROSE_COND_PEER_RX_BUSY
mdefine_line|#define&t;ROSE_COND_PEER_RX_BUSY&t;&t;0x02
DECL|macro|ROSE_COND_OWN_RX_BUSY
mdefine_line|#define&t;ROSE_COND_OWN_RX_BUSY&t;&t;0x04
DECL|macro|FAC_NATIONAL
mdefine_line|#define&t;FAC_NATIONAL&t;&t;&t;0x00
DECL|macro|FAC_CCITT
mdefine_line|#define&t;FAC_CCITT&t;&t;&t;0x0F
DECL|macro|FAC_NATIONAL_RAND
mdefine_line|#define&t;FAC_NATIONAL_RAND&t;&t;0x7F
DECL|macro|FAC_NATIONAL_FLAGS
mdefine_line|#define&t;FAC_NATIONAL_FLAGS&t;&t;0x3F
DECL|macro|FAC_NATIONAL_DEST_DIGI
mdefine_line|#define&t;FAC_NATIONAL_DEST_DIGI&t;&t;0xE9
DECL|macro|FAC_NATIONAL_SRC_DIGI
mdefine_line|#define&t;FAC_NATIONAL_SRC_DIGI&t;&t;0xEB
DECL|macro|FAC_NATIONAL_FAIL_CALL
mdefine_line|#define&t;FAC_NATIONAL_FAIL_CALL&t;&t;0xED
DECL|macro|FAC_NATIONAL_FAIL_ADD
mdefine_line|#define&t;FAC_NATIONAL_FAIL_ADD&t;&t;0xEE
DECL|macro|FAC_NATIONAL_DIGIS
mdefine_line|#define&t;FAC_NATIONAL_DIGIS&t;&t;&t;0xEF
DECL|macro|FAC_CCITT_DEST_NSAP
mdefine_line|#define&t;FAC_CCITT_DEST_NSAP&t;&t;0xC9
DECL|macro|FAC_CCITT_SRC_NSAP
mdefine_line|#define&t;FAC_CCITT_SRC_NSAP&t;&t;0xCB
DECL|struct|rose_neigh
r_struct
id|rose_neigh
(brace
DECL|member|next
r_struct
id|rose_neigh
op_star
id|next
suffix:semicolon
DECL|member|callsign
id|ax25_address
id|callsign
suffix:semicolon
DECL|member|digipeat
id|ax25_digi
op_star
id|digipeat
suffix:semicolon
DECL|member|ax25
id|ax25_cb
op_star
id|ax25
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|member|use
r_int
r_int
id|use
suffix:semicolon
DECL|member|number
r_int
r_int
id|number
suffix:semicolon
DECL|member|restarted
r_char
id|restarted
suffix:semicolon
DECL|member|dce_mode
r_char
id|dce_mode
suffix:semicolon
DECL|member|loopback
r_char
id|loopback
suffix:semicolon
DECL|member|queue
r_struct
id|sk_buff_head
id|queue
suffix:semicolon
DECL|member|t0timer
r_struct
id|timer_list
id|t0timer
suffix:semicolon
DECL|member|ftimer
r_struct
id|timer_list
id|ftimer
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rose_node
r_struct
id|rose_node
(brace
DECL|member|next
r_struct
id|rose_node
op_star
id|next
suffix:semicolon
DECL|member|address
id|rose_address
id|address
suffix:semicolon
DECL|member|mask
r_int
r_int
id|mask
suffix:semicolon
DECL|member|count
r_int
r_char
id|count
suffix:semicolon
DECL|member|loopback
r_char
id|loopback
suffix:semicolon
DECL|member|neighbour
r_struct
id|rose_neigh
op_star
id|neighbour
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rose_route
r_struct
id|rose_route
(brace
DECL|member|next
r_struct
id|rose_route
op_star
id|next
suffix:semicolon
DECL|member|lci1
DECL|member|lci2
r_int
r_int
id|lci1
comma
id|lci2
suffix:semicolon
DECL|member|src_addr
DECL|member|dest_addr
id|rose_address
id|src_addr
comma
id|dest_addr
suffix:semicolon
DECL|member|src_call
DECL|member|dest_call
id|ax25_address
id|src_call
comma
id|dest_call
suffix:semicolon
DECL|member|neigh1
DECL|member|neigh2
r_struct
id|rose_neigh
op_star
id|neigh1
comma
op_star
id|neigh2
suffix:semicolon
DECL|member|rand
r_int
r_int
id|rand
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|source_addr
DECL|member|dest_addr
id|rose_address
id|source_addr
comma
id|dest_addr
suffix:semicolon
DECL|member|source_call
DECL|member|dest_call
id|ax25_address
id|source_call
comma
id|dest_call
suffix:semicolon
DECL|member|source_ndigis
DECL|member|dest_ndigis
r_int
r_char
id|source_ndigis
comma
id|dest_ndigis
suffix:semicolon
DECL|member|source_digis
id|ax25_address
id|source_digis
(braket
id|ROSE_MAX_DIGIS
)braket
suffix:semicolon
DECL|member|dest_digis
id|ax25_address
id|dest_digis
(braket
id|ROSE_MAX_DIGIS
)braket
suffix:semicolon
DECL|member|neighbour
r_struct
id|rose_neigh
op_star
id|neighbour
suffix:semicolon
DECL|member|device
r_struct
id|net_device
op_star
id|device
suffix:semicolon
DECL|member|lci
DECL|member|rand
r_int
r_int
id|lci
comma
id|rand
suffix:semicolon
DECL|member|state
DECL|member|condition
DECL|member|qbitincl
DECL|member|defer
r_int
r_char
id|state
comma
id|condition
comma
id|qbitincl
comma
id|defer
suffix:semicolon
DECL|member|cause
DECL|member|diagnostic
r_int
r_char
id|cause
comma
id|diagnostic
suffix:semicolon
DECL|member|vs
DECL|member|vr
DECL|member|va
DECL|member|vl
r_int
r_int
id|vs
comma
id|vr
comma
id|va
comma
id|vl
suffix:semicolon
DECL|member|t1
DECL|member|t2
DECL|member|t3
DECL|member|hb
DECL|member|idle
r_int
r_int
id|t1
comma
id|t2
comma
id|t3
comma
id|hb
comma
id|idle
suffix:semicolon
macro_line|#ifdef M_BIT
DECL|member|fraglen
r_int
r_int
id|fraglen
suffix:semicolon
DECL|member|frag_queue
r_struct
id|sk_buff_head
id|frag_queue
suffix:semicolon
macro_line|#endif
DECL|member|ack_queue
r_struct
id|sk_buff_head
id|ack_queue
suffix:semicolon
DECL|member|facilities
r_struct
id|rose_facilities_struct
id|facilities
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|idletimer
r_struct
id|timer_list
id|idletimer
suffix:semicolon
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
multiline_comment|/* Backlink to socket */
DECL|typedef|rose_cb
)brace
id|rose_cb
suffix:semicolon
DECL|macro|rose_sk
mdefine_line|#define rose_sk(__sk) ((rose_cb *)(__sk)-&gt;sk_protinfo)
multiline_comment|/* af_rose.c */
r_extern
id|ax25_address
id|rose_callsign
suffix:semicolon
r_extern
r_int
id|sysctl_rose_restart_request_timeout
suffix:semicolon
r_extern
r_int
id|sysctl_rose_call_request_timeout
suffix:semicolon
r_extern
r_int
id|sysctl_rose_reset_request_timeout
suffix:semicolon
r_extern
r_int
id|sysctl_rose_clear_request_timeout
suffix:semicolon
r_extern
r_int
id|sysctl_rose_no_activity_timeout
suffix:semicolon
r_extern
r_int
id|sysctl_rose_ack_hold_back_timeout
suffix:semicolon
r_extern
r_int
id|sysctl_rose_routing_control
suffix:semicolon
r_extern
r_int
id|sysctl_rose_link_fail_timeout
suffix:semicolon
r_extern
r_int
id|sysctl_rose_maximum_vcs
suffix:semicolon
r_extern
r_int
id|sysctl_rose_window_size
suffix:semicolon
r_extern
r_int
id|rosecmp
c_func
(paren
id|rose_address
op_star
comma
id|rose_address
op_star
)paren
suffix:semicolon
r_extern
r_int
id|rosecmpm
c_func
(paren
id|rose_address
op_star
comma
id|rose_address
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_char
op_star
id|rose2asc
c_func
(paren
id|rose_address
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|sock
op_star
id|rose_find_socket
c_func
(paren
r_int
r_int
comma
r_struct
id|rose_neigh
op_star
)paren
suffix:semicolon
r_extern
r_void
id|rose_kill_by_neigh
c_func
(paren
r_struct
id|rose_neigh
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|rose_new_lci
c_func
(paren
r_struct
id|rose_neigh
op_star
)paren
suffix:semicolon
r_extern
r_int
id|rose_rx_call_request
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
id|rose_neigh
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|rose_destroy_socket
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
multiline_comment|/* rose_dev.c */
r_extern
r_int
id|rose_rx_ip
c_func
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|rose_setup
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
multiline_comment|/* rose_in.c */
r_extern
r_int
id|rose_process_rx_frame
c_func
(paren
r_struct
id|sock
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
multiline_comment|/* rose_link.c */
r_extern
r_void
id|rose_start_ftimer
c_func
(paren
r_struct
id|rose_neigh
op_star
)paren
suffix:semicolon
r_extern
r_void
id|rose_start_t0timer
c_func
(paren
r_struct
id|rose_neigh
op_star
)paren
suffix:semicolon
r_extern
r_void
id|rose_stop_ftimer
c_func
(paren
r_struct
id|rose_neigh
op_star
)paren
suffix:semicolon
r_extern
r_void
id|rose_stop_t0timer
c_func
(paren
r_struct
id|rose_neigh
op_star
)paren
suffix:semicolon
r_extern
r_int
id|rose_ftimer_running
c_func
(paren
r_struct
id|rose_neigh
op_star
)paren
suffix:semicolon
r_extern
r_int
id|rose_t0timer_running
c_func
(paren
r_struct
id|rose_neigh
op_star
)paren
suffix:semicolon
r_extern
r_void
id|rose_link_rx_restart
c_func
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|rose_neigh
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|rose_transmit_restart_request
c_func
(paren
r_struct
id|rose_neigh
op_star
)paren
suffix:semicolon
r_extern
r_void
id|rose_transmit_restart_confirmation
c_func
(paren
r_struct
id|rose_neigh
op_star
)paren
suffix:semicolon
r_extern
r_void
id|rose_transmit_diagnostic
c_func
(paren
r_struct
id|rose_neigh
op_star
comma
r_int
r_char
)paren
suffix:semicolon
r_extern
r_void
id|rose_transmit_clear_request
c_func
(paren
r_struct
id|rose_neigh
op_star
comma
r_int
r_int
comma
r_int
r_char
comma
r_int
r_char
)paren
suffix:semicolon
r_extern
r_void
id|rose_transmit_link
c_func
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|rose_neigh
op_star
)paren
suffix:semicolon
multiline_comment|/* rose_loopback.c */
r_extern
r_void
id|rose_loopback_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|rose_loopback_clear
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|rose_loopback_queue
c_func
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|rose_neigh
op_star
)paren
suffix:semicolon
multiline_comment|/* rose_out.c */
r_extern
r_void
id|rose_kick
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|rose_enquiry_response
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
multiline_comment|/* rose_route.c */
r_extern
r_struct
id|rose_neigh
op_star
id|rose_loopback_neigh
suffix:semicolon
r_extern
r_int
id|rose_add_loopback_neigh
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|rose_add_loopback_node
c_func
(paren
id|rose_address
op_star
)paren
suffix:semicolon
r_extern
r_void
id|rose_del_loopback_node
c_func
(paren
id|rose_address
op_star
)paren
suffix:semicolon
r_extern
r_void
id|rose_rt_device_down
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|rose_link_device_down
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|net_device
op_star
id|rose_dev_first
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|net_device
op_star
id|rose_dev_get
c_func
(paren
id|rose_address
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|rose_route
op_star
id|rose_route_free_lci
c_func
(paren
r_int
r_int
comma
r_struct
id|rose_neigh
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|net_device
op_star
id|rose_ax25_dev_get
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|rose_neigh
op_star
id|rose_get_neigh
c_func
(paren
id|rose_address
op_star
comma
r_int
r_char
op_star
comma
r_int
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|rose_rt_ioctl
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
r_void
id|rose_link_failed
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
id|rose_route_frame
c_func
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
id|rose_nodes_get_info
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
id|rose_neigh_get_info
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
id|rose_routes_get_info
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
id|rose_rt_free
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* rose_subr.c */
r_extern
r_void
id|rose_clear_queues
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|rose_frames_acked
c_func
(paren
r_struct
id|sock
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|rose_requeue_frames
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_int
id|rose_validate_nr
c_func
(paren
r_struct
id|sock
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|rose_write_internal
c_func
(paren
r_struct
id|sock
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|rose_decode
c_func
(paren
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
id|rose_parse_facilities
c_func
(paren
r_int
r_char
op_star
comma
r_struct
id|rose_facilities_struct
op_star
)paren
suffix:semicolon
r_extern
r_int
id|rose_create_facilities
c_func
(paren
r_int
r_char
op_star
comma
id|rose_cb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|rose_disconnect
c_func
(paren
r_struct
id|sock
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* rose_timer.c */
r_extern
r_void
id|rose_start_heartbeat
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|rose_start_t1timer
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|rose_start_t2timer
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|rose_start_t3timer
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|rose_start_hbtimer
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|rose_start_idletimer
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|rose_stop_heartbeat
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|rose_stop_timer
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|rose_stop_idletimer
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
multiline_comment|/* sysctl_net_rose.c */
r_extern
r_void
id|rose_register_sysctl
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|rose_unregister_sysctl
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
