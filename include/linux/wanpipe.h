multiline_comment|/*****************************************************************************&n;* wanpipe.h&t;WANPIPE(tm) Multiprotocol WAN Link Driver.&n;*&t;&t;User-level API definitions.&n;*&n;* Author: &t;Nenad Corbic &lt;ncorbic@sangoma.com&gt;&n;*&t;&t;Gideon Hack  &t;&n;*&n;* Copyright:&t;(c) 1995-2000 Sangoma Technologies Inc.&n;*&n;*&t;&t;This program is free software; you can redistribute it and/or&n;*&t;&t;modify it under the terms of the GNU General Public License&n;*&t;&t;as published by the Free Software Foundation; either version&n;*&t;&t;2 of the License, or (at your option) any later version.&n;* ============================================================================&n;* Nov 3,  2000  Nenad Corbic    Added config_id to sdla_t structure.&n;*                               Used to determine the protocol running.&n;* Jul 13, 2000  Nenad Corbic&t;Added SyncPPP Support&n;* Feb 24, 2000  Nenad Corbic    Added support for x25api driver&n;* Oct 04, 1999  Nenad Corbic    New CHDLC and FRAME RELAY code, SMP support&n;* Jun 02, 1999  Gideon Hack&t;Added &squot;update_call_count&squot; for Cisco HDLC &n;*&t;&t;&t;&t;support&n;* Jun 26, 1998&t;David Fong&t;Added &squot;ip_mode&squot; in sdla_t.u.p for dynamic IP&n;*&t;&t;&t;&t;routing mode configuration&n;* Jun 12, 1998&t;David Fong&t;Added Cisco HDLC union member in sdla_t&n;* Dec 08, 1997&t;Jaspreet Singh  Added &squot;authenticator&squot; in union of &squot;sdla_t&squot; &n;* Nov 26, 1997&t;Jaspreet Singh&t;Added &squot;load_sharing&squot; structure.  Also added &n;*&t;&t;&t;&t;&squot;devs_struct&squot;,&squot;dev_to_devtint_next&squot; to &squot;sdla_t&squot;&t;&n;* Nov 24, 1997&t;Jaspreet Singh&t;Added &squot;irq_dis_if_send_count&squot;, &n;*&t;&t;&t;&t;&squot;irq_dis_poll_count&squot; to &squot;sdla_t&squot;.&n;* Nov 06, 1997&t;Jaspreet Singh&t;Added a define called &squot;INTR_TEST_MODE&squot;&n;* Oct 20, 1997&t;Jaspreet Singh&t;Added &squot;buff_intr_mode_unbusy&squot; and &n;*&t;&t;&t;&t;&squot;dlci_intr_mode_unbusy&squot; to &squot;sdla_t&squot;&n;* Oct 18, 1997&t;Jaspreet Singh&t;Added structure to maintain global driver&n;*&t;&t;&t;&t;statistics.&n;* Jan 15, 1997&t;Gene Kozin&t;Version 3.1.0&n;*&t;&t;&t;&t; o added UDP management stuff&n;* Jan 02, 1997&t;Gene Kozin&t;Version 3.0.0&n;*****************************************************************************/
macro_line|#ifndef&t;_WANPIPE_H
DECL|macro|_WANPIPE_H
mdefine_line|#define&t;_WANPIPE_H
macro_line|#include &lt;linux/version.h&gt;
macro_line|#ifndef KERNEL_VERSION
DECL|macro|KERNEL_VERSION
mdefine_line|#define KERNEL_VERSION(a,b,c) (((a) &lt;&lt; 16) + ((b) &lt;&lt; 8) + (c))
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,3,0)
DECL|macro|LINUX_2_4
mdefine_line|#define LINUX_2_4
DECL|macro|netdevice_t
mdefine_line|#define netdevice_t struct net_device
DECL|macro|FREE_READ
mdefine_line|#define FREE_READ 1
DECL|macro|FREE_WRITE
mdefine_line|#define FREE_WRITE 0
DECL|macro|stop_net_queue
mdefine_line|#define stop_net_queue(a) &t;netif_stop_queue(a) 
DECL|macro|start_net_queue
mdefine_line|#define start_net_queue(a) &t;netif_start_queue(a)
DECL|macro|is_queue_stopped
mdefine_line|#define is_queue_stopped(a)&t;netif_queue_stopped(a)
DECL|macro|wake_net_dev
mdefine_line|#define wake_net_dev(a)&t;netif_wake_queue(a)
DECL|macro|is_dev_running
mdefine_line|#define is_dev_running(a)&t;netif_running(a)
DECL|macro|wan_dev_kfree_skb
mdefine_line|#define wan_dev_kfree_skb(a,b)&t;dev_kfree_skb_any(a)
macro_line|#elif LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,1,0)
DECL|macro|LINUX_2_1
mdefine_line|#define LINUX_2_1
DECL|macro|netdevice_t
mdefine_line|#define netdevice_t struct device
DECL|macro|FREE_READ
mdefine_line|#define FREE_READ 1
DECL|macro|FREE_WRITE
mdefine_line|#define FREE_WRITE 0
DECL|macro|stop_net_queue
mdefine_line|#define stop_net_queue(a) &t;(set_bit(0, &amp;##a-&gt;tbusy)) 
DECL|macro|start_net_queue
mdefine_line|#define start_net_queue(a) &t;(clear_bit(0,&amp;##a-&gt;tbusy))
DECL|macro|is_queue_stopped
mdefine_line|#define is_queue_stopped(a)&t;(##a-&gt;tbusy)
DECL|macro|wake_net_dev
mdefine_line|#define wake_net_dev(a)&t;{clear_bit(0,&amp;##a-&gt;tbusy);mark_bh(NET_BH);}
DECL|macro|is_dev_running
mdefine_line|#define is_dev_running(a)&t;(test_bit(0,&amp;##a-&gt;start))
DECL|macro|wan_dev_kfree_skb
mdefine_line|#define wan_dev_kfree_skb(a,b)&t;dev_kfree_skb(a)
macro_line|#else
DECL|macro|LINUX_2_0
mdefine_line|#define LINUX_2_0
DECL|macro|netdevice_t
mdefine_line|#define netdevice_t struct device
DECL|macro|test_and_set_bit
mdefine_line|#define test_and_set_bit set_bit
DECL|macro|net_ratelimit
mdefine_line|#define net_ratelimit() 1 
DECL|macro|stop_net_queue
mdefine_line|#define stop_net_queue(a) &t;(set_bit(0, &amp;##a-&gt;tbusy)) 
DECL|macro|start_net_queue
mdefine_line|#define start_net_queue(a) &t;(clear_bit(0,&amp;##a-&gt;tbusy))
DECL|macro|is_queue_stopped
mdefine_line|#define is_queue_stopped(a)&t;(##a-&gt;tbusy)
DECL|macro|wake_net_dev
mdefine_line|#define wake_net_dev(a)&t;{clear_bit(0,&amp;##a-&gt;tbusy);mark_bh(NET_BH);}
DECL|macro|is_dev_running
mdefine_line|#define is_dev_running(a)&t;(test_bit(0,(void*)&amp;##a-&gt;start))
DECL|macro|wan_dev_kfree_skb
mdefine_line|#define wan_dev_kfree_skb(a,b) dev_kfree_skb(a,b)  &t;&t; 
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(a)
DECL|macro|spin_lock
mdefine_line|#define spin_lock(a)
DECL|macro|spin_unlock
mdefine_line|#define spin_unlock(a)
macro_line|#endif
macro_line|#include &lt;linux/wanrouter.h&gt;
multiline_comment|/* Defines */
macro_line|#ifndef&t;PACKED
DECL|macro|PACKED
mdefine_line|#define&t;PACKED&t;__attribute__((packed))
macro_line|#endif
DECL|macro|WANPIPE_MAGIC
mdefine_line|#define&t;WANPIPE_MAGIC&t;0x414C4453L&t;/* signature: &squot;SDLA&squot; reversed */
multiline_comment|/* IOCTL numbers (up to 16) */
DECL|macro|WANPIPE_DUMP
mdefine_line|#define&t;WANPIPE_DUMP&t;(ROUTER_USER+0)&t;/* dump adapter&squot;s memory */
DECL|macro|WANPIPE_EXEC
mdefine_line|#define&t;WANPIPE_EXEC&t;(ROUTER_USER+1)&t;/* execute firmware command */
DECL|macro|TRACE_ALL
mdefine_line|#define TRACE_ALL                       0x00
DECL|macro|TRACE_PROT
mdefine_line|#define TRACE_PROT&t;&t;&t;0x01
DECL|macro|TRACE_DATA
mdefine_line|#define TRACE_DATA&t;&t;&t;0x02
multiline_comment|/* values for request/reply byte */
DECL|macro|UDPMGMT_REQUEST
mdefine_line|#define UDPMGMT_REQUEST&t;0x01
DECL|macro|UDPMGMT_REPLY
mdefine_line|#define UDPMGMT_REPLY&t;0x02
DECL|macro|UDP_OFFSET
mdefine_line|#define UDP_OFFSET&t;12
DECL|macro|MAX_CMD_BUFF
mdefine_line|#define MAX_CMD_BUFF &t;10
DECL|macro|MAX_X25_LCN
mdefine_line|#define MAX_X25_LCN &t;255&t;/* Maximum number of x25 channels */
DECL|macro|MAX_LCN_NUM
mdefine_line|#define MAX_LCN_NUM&t;4095&t;/* Maximum lcn number */
DECL|macro|MAX_FT1_RETRY
mdefine_line|#define MAX_FT1_RETRY &t;100
macro_line|#ifdef LINUX_2_4
macro_line|#ifndef AF_WANPIPE
DECL|macro|AF_WANPIPE
mdefine_line|#define AF_WANPIPE 25
macro_line|#ifndef PF_WANPIPE
DECL|macro|PF_WANPIPE
mdefine_line|#define PF_WANPIPE AF_WANPIPE
macro_line|#endif
macro_line|#endif
macro_line|#else
macro_line|#ifndef AF_WANPIPE
DECL|macro|AF_WANPIPE
mdefine_line|#define AF_WANPIPE 24
macro_line|#ifndef PF_WANPIPE
DECL|macro|PF_WANPIPE
mdefine_line|#define PF_WANPIPE AF_WANPIPE
macro_line|#endif
macro_line|#endif
macro_line|#endif
DECL|macro|TX_TIMEOUT
mdefine_line|#define TX_TIMEOUT 5*HZ
multiline_comment|/* General Critical Flags */
DECL|macro|SEND_CRIT
mdefine_line|#define SEND_CRIT&t;0x00
DECL|macro|PERI_CRIT
mdefine_line|#define PERI_CRIT&t;0x01
multiline_comment|/* Chdlc and PPP polling critical flag */
DECL|macro|POLL_CRIT
mdefine_line|#define POLL_CRIT&t;0x03
multiline_comment|/* Frame Relay Tx IRQ send critical flag */
DECL|macro|SEND_TXIRQ_CRIT
mdefine_line|#define SEND_TXIRQ_CRIT 0x02
multiline_comment|/* Frame Relay ARP critical flag */
DECL|macro|ARP_CRIT
mdefine_line|#define ARP_CRIT&t;0x03
multiline_comment|/* Bit maps for dynamic interface configuration&n; * DYN_OPT_ON : turns this option on/off &n; * DEV_DOWN   : device was shutdown by the driver not&n; *              by user &n; */
DECL|macro|DYN_OPT_ON
mdefine_line|#define DYN_OPT_ON&t;0x00
DECL|macro|DEV_DOWN
mdefine_line|#define DEV_DOWN&t;0x01
multiline_comment|/*&n; * Data structures for IOCTL calls.&n; */
DECL|struct|sdla_dump
r_typedef
r_struct
id|sdla_dump
multiline_comment|/* WANPIPE_DUMP */
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/* for verification */
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
multiline_comment|/* absolute adapter memory address */
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
multiline_comment|/* block length */
DECL|member|ptr
r_void
op_star
id|ptr
suffix:semicolon
multiline_comment|/* -&gt; buffer */
DECL|typedef|sdla_dump_t
)brace
id|sdla_dump_t
suffix:semicolon
DECL|struct|sdla_exec
r_typedef
r_struct
id|sdla_exec
multiline_comment|/* WANPIPE_EXEC */
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/* for verification */
DECL|member|cmd
r_void
op_star
id|cmd
suffix:semicolon
multiline_comment|/* -&gt; command structure */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* -&gt; data buffer */
DECL|typedef|sdla_exec_t
)brace
id|sdla_exec_t
suffix:semicolon
multiline_comment|/* UDP management stuff */
DECL|struct|wum_header
r_typedef
r_struct
id|wum_header
(brace
DECL|member|signature
r_int
r_char
id|signature
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 00h: signature */
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
multiline_comment|/* 08h: request/reply */
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
multiline_comment|/* 09h: commnand */
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* 0Ah: reserved */
DECL|typedef|wum_header_t
)brace
id|wum_header_t
suffix:semicolon
multiline_comment|/*************************************************************************&n; Data Structure for global statistics&n;*************************************************************************/
DECL|struct|global_stats
r_typedef
r_struct
id|global_stats
(brace
DECL|member|isr_entry
r_int
r_int
id|isr_entry
suffix:semicolon
DECL|member|isr_already_critical
r_int
r_int
id|isr_already_critical
suffix:semicolon
DECL|member|isr_rx
r_int
r_int
id|isr_rx
suffix:semicolon
DECL|member|isr_tx
r_int
r_int
id|isr_tx
suffix:semicolon
DECL|member|isr_intr_test
r_int
r_int
id|isr_intr_test
suffix:semicolon
DECL|member|isr_spurious
r_int
r_int
id|isr_spurious
suffix:semicolon
DECL|member|isr_enable_tx_int
r_int
r_int
id|isr_enable_tx_int
suffix:semicolon
DECL|member|rx_intr_corrupt_rx_bfr
r_int
r_int
id|rx_intr_corrupt_rx_bfr
suffix:semicolon
DECL|member|rx_intr_on_orphaned_DLCI
r_int
r_int
id|rx_intr_on_orphaned_DLCI
suffix:semicolon
DECL|member|rx_intr_dev_not_started
r_int
r_int
id|rx_intr_dev_not_started
suffix:semicolon
DECL|member|tx_intr_dev_not_started
r_int
r_int
id|tx_intr_dev_not_started
suffix:semicolon
DECL|member|poll_entry
r_int
r_int
id|poll_entry
suffix:semicolon
DECL|member|poll_already_critical
r_int
r_int
id|poll_already_critical
suffix:semicolon
DECL|member|poll_processed
r_int
r_int
id|poll_processed
suffix:semicolon
DECL|member|poll_tbusy_bad_status
r_int
r_int
id|poll_tbusy_bad_status
suffix:semicolon
DECL|member|poll_host_disable_irq
r_int
r_int
id|poll_host_disable_irq
suffix:semicolon
DECL|member|poll_host_enable_irq
r_int
r_int
id|poll_host_enable_irq
suffix:semicolon
DECL|typedef|global_stats_t
)brace
id|global_stats_t
suffix:semicolon
r_typedef
(def_block
r_struct
(brace
DECL|member|PACKED
r_int
r_int
id|udp_src_port
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|udp_dst_port
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|udp_length
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|udp_checksum
id|PACKED
suffix:semicolon
DECL|typedef|udp_pkt_t
)brace
)def_block
id|udp_pkt_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_char
id|ver_inet_hdr_length
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|service_type
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|total_length
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|identifier
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|flags_frag_offset
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|ttl
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|protocol
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|hdr_checksum
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|ip_src_address
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|ip_dst_address
id|PACKED
suffix:semicolon
DECL|typedef|ip_pkt_t
)brace
id|ip_pkt_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_char
id|signature
(braket
l_int|8
)braket
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|request_reply
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|id
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|reserved
(braket
l_int|6
)braket
id|PACKED
suffix:semicolon
DECL|typedef|wp_mgmt_t
)brace
id|wp_mgmt_t
suffix:semicolon
multiline_comment|/*************************************************************************&n; Data Structure for if_send  statistics&n;*************************************************************************/
DECL|struct|if_send_stat
r_typedef
r_struct
id|if_send_stat
(brace
DECL|member|if_send_entry
r_int
r_int
id|if_send_entry
suffix:semicolon
DECL|member|if_send_skb_null
r_int
r_int
id|if_send_skb_null
suffix:semicolon
DECL|member|if_send_broadcast
r_int
r_int
id|if_send_broadcast
suffix:semicolon
DECL|member|if_send_multicast
r_int
r_int
id|if_send_multicast
suffix:semicolon
DECL|member|if_send_critical_ISR
r_int
r_int
id|if_send_critical_ISR
suffix:semicolon
DECL|member|if_send_critical_non_ISR
r_int
r_int
id|if_send_critical_non_ISR
suffix:semicolon
DECL|member|if_send_tbusy
r_int
r_int
id|if_send_tbusy
suffix:semicolon
DECL|member|if_send_tbusy_timeout
r_int
r_int
id|if_send_tbusy_timeout
suffix:semicolon
DECL|member|if_send_PIPE_request
r_int
r_int
id|if_send_PIPE_request
suffix:semicolon
DECL|member|if_send_wan_disconnected
r_int
r_int
id|if_send_wan_disconnected
suffix:semicolon
DECL|member|if_send_dlci_disconnected
r_int
r_int
id|if_send_dlci_disconnected
suffix:semicolon
DECL|member|if_send_no_bfrs
r_int
r_int
id|if_send_no_bfrs
suffix:semicolon
DECL|member|if_send_adptr_bfrs_full
r_int
r_int
id|if_send_adptr_bfrs_full
suffix:semicolon
DECL|member|if_send_bfr_passed_to_adptr
r_int
r_int
id|if_send_bfr_passed_to_adptr
suffix:semicolon
DECL|member|if_send_protocol_error
r_int
r_int
id|if_send_protocol_error
suffix:semicolon
DECL|member|if_send_bfr_not_passed_to_adptr
r_int
r_int
id|if_send_bfr_not_passed_to_adptr
suffix:semicolon
DECL|member|if_send_tx_int_enabled
r_int
r_int
id|if_send_tx_int_enabled
suffix:semicolon
DECL|member|if_send_consec_send_fail
r_int
r_int
id|if_send_consec_send_fail
suffix:semicolon
DECL|typedef|if_send_stat_t
)brace
id|if_send_stat_t
suffix:semicolon
DECL|struct|rx_intr_stat
r_typedef
r_struct
id|rx_intr_stat
(brace
DECL|member|rx_intr_no_socket
r_int
r_int
id|rx_intr_no_socket
suffix:semicolon
DECL|member|rx_intr_dev_not_started
r_int
r_int
id|rx_intr_dev_not_started
suffix:semicolon
DECL|member|rx_intr_PIPE_request
r_int
r_int
id|rx_intr_PIPE_request
suffix:semicolon
DECL|member|rx_intr_bfr_not_passed_to_stack
r_int
r_int
id|rx_intr_bfr_not_passed_to_stack
suffix:semicolon
DECL|member|rx_intr_bfr_passed_to_stack
r_int
r_int
id|rx_intr_bfr_passed_to_stack
suffix:semicolon
DECL|typedef|rx_intr_stat_t
)brace
id|rx_intr_stat_t
suffix:semicolon
DECL|struct|pipe_mgmt_stat
r_typedef
r_struct
id|pipe_mgmt_stat
(brace
DECL|member|UDP_PIPE_mgmt_kmalloc_err
r_int
r_int
id|UDP_PIPE_mgmt_kmalloc_err
suffix:semicolon
DECL|member|UDP_PIPE_mgmt_direction_err
r_int
r_int
id|UDP_PIPE_mgmt_direction_err
suffix:semicolon
DECL|member|UDP_PIPE_mgmt_adptr_type_err
r_int
r_int
id|UDP_PIPE_mgmt_adptr_type_err
suffix:semicolon
DECL|member|UDP_PIPE_mgmt_adptr_cmnd_OK
r_int
r_int
id|UDP_PIPE_mgmt_adptr_cmnd_OK
suffix:semicolon
DECL|member|UDP_PIPE_mgmt_adptr_cmnd_timeout
r_int
r_int
id|UDP_PIPE_mgmt_adptr_cmnd_timeout
suffix:semicolon
DECL|member|UDP_PIPE_mgmt_adptr_send_passed
r_int
r_int
id|UDP_PIPE_mgmt_adptr_send_passed
suffix:semicolon
DECL|member|UDP_PIPE_mgmt_adptr_send_failed
r_int
r_int
id|UDP_PIPE_mgmt_adptr_send_failed
suffix:semicolon
DECL|member|UDP_PIPE_mgmt_not_passed_to_stack
r_int
r_int
id|UDP_PIPE_mgmt_not_passed_to_stack
suffix:semicolon
DECL|member|UDP_PIPE_mgmt_passed_to_stack
r_int
r_int
id|UDP_PIPE_mgmt_passed_to_stack
suffix:semicolon
DECL|member|UDP_PIPE_mgmt_no_socket
r_int
r_int
id|UDP_PIPE_mgmt_no_socket
suffix:semicolon
DECL|member|UDP_PIPE_mgmt_passed_to_adptr
r_int
r_int
id|UDP_PIPE_mgmt_passed_to_adptr
suffix:semicolon
DECL|typedef|pipe_mgmt_stat_t
)brace
id|pipe_mgmt_stat_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
DECL|typedef|bh_data_t
DECL|typedef|cmd_data_t
)brace
id|bh_data_t
comma
id|cmd_data_t
suffix:semicolon
DECL|macro|MAX_LGTH_UDP_MGNT_PKT
mdefine_line|#define MAX_LGTH_UDP_MGNT_PKT 2000
multiline_comment|/* This is used for interrupt testing */
DECL|macro|INTR_TEST_MODE
mdefine_line|#define INTR_TEST_MODE&t;0x02
DECL|macro|WUM_SIGNATURE_L
mdefine_line|#define&t;WUM_SIGNATURE_L&t;0x50495046
DECL|macro|WUM_SIGNATURE_H
mdefine_line|#define&t;WUM_SIGNATURE_H&t;0x444E3845
DECL|macro|WUM_KILL
mdefine_line|#define&t;WUM_KILL&t;0x50
DECL|macro|WUM_EXEC
mdefine_line|#define&t;WUM_EXEC&t;0x51
DECL|macro|WANPIPE
mdefine_line|#define WANPIPE&t;&t;0x00
DECL|macro|API
mdefine_line|#define API&t;&t;0x01
DECL|macro|BRIDGE
mdefine_line|#define BRIDGE&t;&t;0x02
DECL|macro|BRIDGE_NODE
mdefine_line|#define BRIDGE_NODE&t;0x03
macro_line|#ifdef&t;__KERNEL__
multiline_comment|/****** Kernel Interface ****************************************************/
macro_line|#include &lt;linux/sdladrv.h&gt;&t;/* SDLA support module API definitions */
macro_line|#include &lt;linux/sdlasfm.h&gt;&t;/* SDLA firmware module definitions */
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#ifdef LINUX_2_4
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/serialP.h&gt;
macro_line|#include &lt;linux/serial_reg.h&gt;
macro_line|#include &lt;asm/serial.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/tty_driver.h&gt;
macro_line|#include &lt;linux/tty_flip.h&gt;
macro_line|#ifndef&t;min
DECL|macro|min
mdefine_line|#define min(a,b) (((a)&lt;(b))?(a):(b))
macro_line|#endif
macro_line|#ifndef&t;max
DECL|macro|max
mdefine_line|#define max(a,b) (((a)&gt;(b))?(a):(b))
macro_line|#endif
DECL|macro|is_digit
mdefine_line|#define&t;is_digit(ch) (((ch)&gt;=(unsigned)&squot;0&squot;&amp;&amp;(ch)&lt;=(unsigned)&squot;9&squot;)?1:0)
DECL|macro|is_alpha
mdefine_line|#define&t;is_alpha(ch) ((((ch)&gt;=(unsigned)&squot;a&squot;&amp;&amp;(ch)&lt;=(unsigned)&squot;z&squot;)||&bslash;&n;&t; &t;  ((ch)&gt;=(unsigned)&squot;A&squot;&amp;&amp;(ch)&lt;=(unsigned)&squot;Z&squot;))?1:0)
DECL|macro|is_hex_digit
mdefine_line|#define&t;is_hex_digit(ch) ((((ch)&gt;=(unsigned)&squot;0&squot;&amp;&amp;(ch)&lt;=(unsigned)&squot;9&squot;)||&bslash;&n;&t; &t;  ((ch)&gt;=(unsigned)&squot;a&squot;&amp;&amp;(ch)&lt;=(unsigned)&squot;f&squot;)||&bslash;&n;&t; &t;  ((ch)&gt;=(unsigned)&squot;A&squot;&amp;&amp;(ch)&lt;=(unsigned)&squot;F&squot;))?1:0)
multiline_comment|/****** Data Structures *****************************************************/
multiline_comment|/* Adapter Data Space.&n; * This structure is needed because we handle multiple cards, otherwise&n; * static data would do it.&n; */
DECL|struct|sdla
r_typedef
r_struct
id|sdla
(brace
DECL|member|devname
r_char
id|devname
(braket
id|WAN_DRVNAME_SZ
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* card name */
DECL|member|hw
id|sdlahw_t
id|hw
suffix:semicolon
multiline_comment|/* hardware configuration */
DECL|member|wandev
id|wan_device_t
id|wandev
suffix:semicolon
multiline_comment|/* WAN device data space */
DECL|member|open_cnt
r_int
id|open_cnt
suffix:semicolon
multiline_comment|/* number of open interfaces */
DECL|member|state_tick
r_int
r_int
id|state_tick
suffix:semicolon
multiline_comment|/* link state timestamp */
DECL|member|intr_mode
r_int
id|intr_mode
suffix:semicolon
multiline_comment|/* Type of Interrupt Mode */
DECL|member|in_isr
r_char
id|in_isr
suffix:semicolon
multiline_comment|/* interrupt-in-service flag */
DECL|member|buff_int_mode_unbusy
r_char
id|buff_int_mode_unbusy
suffix:semicolon
multiline_comment|/* flag for carrying out dev_tint */
DECL|member|dlci_int_mode_unbusy
r_char
id|dlci_int_mode_unbusy
suffix:semicolon
multiline_comment|/* flag for carrying out dev_tint */
DECL|member|configured
r_char
id|configured
suffix:semicolon
multiline_comment|/* flag for previous configurations */
DECL|member|irq_dis_if_send_count
r_int
r_int
id|irq_dis_if_send_count
suffix:semicolon
multiline_comment|/* Disabling irqs in if_send*/
DECL|member|irq_dis_poll_count
r_int
r_int
id|irq_dis_poll_count
suffix:semicolon
multiline_comment|/* Disabling irqs in poll routine*/
DECL|member|force_enable_irq
r_int
r_int
id|force_enable_irq
suffix:semicolon
DECL|member|TracingEnabled
r_char
id|TracingEnabled
suffix:semicolon
multiline_comment|/* flag for enabling trace */
DECL|member|statistics
id|global_stats_t
id|statistics
suffix:semicolon
multiline_comment|/* global statistics */
DECL|member|mbox
r_void
op_star
id|mbox
suffix:semicolon
multiline_comment|/* -&gt; mailbox */
DECL|member|rxmb
r_void
op_star
id|rxmb
suffix:semicolon
multiline_comment|/* -&gt; receive mailbox */
DECL|member|flags
r_void
op_star
id|flags
suffix:semicolon
multiline_comment|/* -&gt; adapter status flags */
DECL|member|isr
r_void
(paren
op_star
id|isr
)paren
(paren
r_struct
id|sdla
op_star
id|card
)paren
suffix:semicolon
multiline_comment|/* interrupt service routine */
DECL|member|poll
r_void
(paren
op_star
id|poll
)paren
(paren
r_struct
id|sdla
op_star
id|card
)paren
suffix:semicolon
multiline_comment|/* polling routine */
DECL|member|exec
r_int
(paren
op_star
id|exec
)paren
(paren
r_struct
id|sdla
op_star
id|card
comma
r_void
op_star
id|u_cmd
comma
r_void
op_star
id|u_data
)paren
suffix:semicolon
multiline_comment|/* Used by the listen() system call */
multiline_comment|/* Wanpipe Socket Interface */
DECL|member|func
r_int
(paren
op_star
id|func
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|sock
op_star
)paren
suffix:semicolon
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
multiline_comment|/* Shutdown function */
DECL|member|disable_comm
r_void
(paren
op_star
id|disable_comm
)paren
(paren
r_struct
id|sdla
op_star
id|card
)paren
suffix:semicolon
multiline_comment|/* Secondary Port Device: Piggibacking */
DECL|member|next
r_struct
id|sdla
op_star
id|next
suffix:semicolon
multiline_comment|/* TTY driver variables */
DECL|member|tty_opt
r_int
r_char
id|tty_opt
suffix:semicolon
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|tty_minor
r_int
r_int
id|tty_minor
suffix:semicolon
DECL|member|tty_open
r_int
r_int
id|tty_open
suffix:semicolon
DECL|member|tty_buf
r_int
r_char
op_star
id|tty_buf
suffix:semicolon
DECL|member|tty_rx
r_int
r_char
op_star
id|tty_rx
suffix:semicolon
DECL|member|tty_task_queue
r_struct
id|tq_struct
id|tty_task_queue
suffix:semicolon
r_union
(brace
r_struct
(brace
multiline_comment|/****** X.25 specific data **********/
DECL|member|lo_pvc
id|u32
id|lo_pvc
suffix:semicolon
DECL|member|hi_pvc
id|u32
id|hi_pvc
suffix:semicolon
DECL|member|lo_svc
id|u32
id|lo_svc
suffix:semicolon
DECL|member|hi_svc
id|u32
id|hi_svc
suffix:semicolon
DECL|member|svc_to_dev_map
id|netdevice_t
op_star
id|svc_to_dev_map
(braket
id|MAX_X25_LCN
)braket
suffix:semicolon
DECL|member|pvc_to_dev_map
id|netdevice_t
op_star
id|pvc_to_dev_map
(braket
id|MAX_X25_LCN
)braket
suffix:semicolon
DECL|member|tx_dev
id|netdevice_t
op_star
id|tx_dev
suffix:semicolon
DECL|member|cmd_dev
id|netdevice_t
op_star
id|cmd_dev
suffix:semicolon
DECL|member|no_dev
id|u32
id|no_dev
suffix:semicolon
DECL|member|hdlc_buf_status
r_volatile
id|u8
op_star
id|hdlc_buf_status
suffix:semicolon
DECL|member|tx_interrupts_pending
id|u32
id|tx_interrupts_pending
suffix:semicolon
DECL|member|timer_int_enabled
id|u16
id|timer_int_enabled
suffix:semicolon
DECL|member|poll_device
id|netdevice_t
op_star
id|poll_device
suffix:semicolon
DECL|member|command_busy
id|atomic_t
id|command_busy
suffix:semicolon
DECL|member|udp_pkt_lgth
id|u16
id|udp_pkt_lgth
suffix:semicolon
DECL|member|udp_type
id|u32
id|udp_type
suffix:semicolon
DECL|member|udp_pkt_src
id|u8
id|udp_pkt_src
suffix:semicolon
DECL|member|udp_lcn
id|u32
id|udp_lcn
suffix:semicolon
DECL|member|udp_dev
id|netdevice_t
op_star
id|udp_dev
suffix:semicolon
DECL|member|udp_pkt_data
id|s8
id|udp_pkt_data
(braket
id|MAX_LGTH_UDP_MGNT_PKT
)braket
suffix:semicolon
DECL|member|LAPB_hdlc
id|u8
id|LAPB_hdlc
suffix:semicolon
multiline_comment|/* Option to turn off X25 and run only LAPB */
DECL|member|logging
id|u8
id|logging
suffix:semicolon
multiline_comment|/* Option to log call messages */
DECL|member|oob_on_modem
id|u8
id|oob_on_modem
suffix:semicolon
multiline_comment|/* Option to send modem status to the api */
DECL|member|num_of_ch
id|u16
id|num_of_ch
suffix:semicolon
multiline_comment|/* Number of channels configured by the user */
DECL|member|x25_poll_task
r_struct
id|tq_struct
id|x25_poll_task
suffix:semicolon
DECL|member|x25_timer
r_struct
id|timer_list
id|x25_timer
suffix:semicolon
DECL|member|x
)brace
id|x
suffix:semicolon
r_struct
(brace
multiline_comment|/****** frame relay specific data ***/
DECL|member|rxmb_base
r_void
op_star
id|rxmb_base
suffix:semicolon
multiline_comment|/* -&gt; first Rx buffer */
DECL|member|rxmb_last
r_void
op_star
id|rxmb_last
suffix:semicolon
multiline_comment|/* -&gt; last Rx buffer */
DECL|member|rx_base
r_int
id|rx_base
suffix:semicolon
multiline_comment|/* S508 receive buffer base */
DECL|member|rx_top
r_int
id|rx_top
suffix:semicolon
multiline_comment|/* S508 receive buffer end */
DECL|member|node_dlci
r_int
r_int
id|node_dlci
(braket
l_int|100
)braket
suffix:semicolon
DECL|member|dlci_num
r_int
r_int
id|dlci_num
suffix:semicolon
DECL|member|dlci_to_dev_map
id|netdevice_t
op_star
id|dlci_to_dev_map
(braket
l_int|991
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|tx_interrupts_pending
r_int
id|tx_interrupts_pending
suffix:semicolon
DECL|member|timer_int_enabled
r_int
r_int
id|timer_int_enabled
suffix:semicolon
DECL|member|udp_pkt_lgth
r_int
r_int
id|udp_pkt_lgth
suffix:semicolon
DECL|member|udp_type
r_int
id|udp_type
suffix:semicolon
DECL|member|udp_pkt_src
r_char
id|udp_pkt_src
suffix:semicolon
DECL|member|udp_dlci
r_int
id|udp_dlci
suffix:semicolon
DECL|member|udp_pkt_data
r_char
id|udp_pkt_data
(braket
id|MAX_LGTH_UDP_MGNT_PKT
)braket
suffix:semicolon
DECL|member|trc_el_base
r_void
op_star
id|trc_el_base
suffix:semicolon
multiline_comment|/* first trace element */
DECL|member|trc_el_last
r_void
op_star
id|trc_el_last
suffix:semicolon
multiline_comment|/* last trace element */
DECL|member|curr_trc_el
r_void
op_star
id|curr_trc_el
suffix:semicolon
multiline_comment|/* current trace element */
DECL|member|trc_bfr_space
r_int
r_int
id|trc_bfr_space
suffix:semicolon
multiline_comment|/* trace buffer space */
DECL|member|update_comms_stats
r_int
r_char
id|update_comms_stats
suffix:semicolon
DECL|member|arp_dev
id|netdevice_t
op_star
id|arp_dev
suffix:semicolon
DECL|member|if_send_lock
id|spinlock_t
id|if_send_lock
suffix:semicolon
DECL|member|f
)brace
id|f
suffix:semicolon
r_struct
multiline_comment|/****** PPP-specific data ***********/
(brace
DECL|member|if_name
r_char
id|if_name
(braket
id|WAN_IFNAME_SZ
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* interface name */
DECL|member|txbuf
r_void
op_star
id|txbuf
suffix:semicolon
multiline_comment|/* -&gt; current Tx buffer */
DECL|member|txbuf_base
r_void
op_star
id|txbuf_base
suffix:semicolon
multiline_comment|/* -&gt; first Tx buffer */
DECL|member|txbuf_last
r_void
op_star
id|txbuf_last
suffix:semicolon
multiline_comment|/* -&gt; last Tx buffer */
DECL|member|rxbuf_base
r_void
op_star
id|rxbuf_base
suffix:semicolon
multiline_comment|/* -&gt; first Rx buffer */
DECL|member|rxbuf_last
r_void
op_star
id|rxbuf_last
suffix:semicolon
multiline_comment|/* -&gt; last Rx buffer */
DECL|member|rx_base
r_int
id|rx_base
suffix:semicolon
multiline_comment|/* S508 receive buffer base */
DECL|member|rx_top
r_int
id|rx_top
suffix:semicolon
multiline_comment|/* S508 receive buffer end */
DECL|member|ip_mode
r_char
id|ip_mode
suffix:semicolon
multiline_comment|/* STATIC/HOST/PEER IP Mode */
DECL|member|authenticator
r_char
id|authenticator
suffix:semicolon
multiline_comment|/* Authenticator for PAP/CHAP */
DECL|member|comm_enabled
r_int
r_char
id|comm_enabled
suffix:semicolon
multiline_comment|/* Is comm enabled or not */
DECL|member|peer_route
r_int
r_char
id|peer_route
suffix:semicolon
multiline_comment|/* Process Peer Route */
DECL|member|txbuf_next
r_int
r_int
op_star
id|txbuf_next
suffix:semicolon
multiline_comment|/* Next Tx buffer to use */
DECL|member|rxbuf_next
r_int
r_int
op_star
id|rxbuf_next
suffix:semicolon
multiline_comment|/* Next Rx buffer to use */
DECL|member|p
)brace
id|p
suffix:semicolon
r_struct
multiline_comment|/* Cisco HDLC-specific data */
(brace
DECL|member|if_name
r_char
id|if_name
(braket
id|WAN_IFNAME_SZ
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* interface name */
DECL|member|comm_port
r_int
r_char
id|comm_port
suffix:semicolon
multiline_comment|/* Communication Port O or 1 */
DECL|member|usedby
r_int
r_char
id|usedby
suffix:semicolon
multiline_comment|/* Used by WANPIPE or API */
DECL|member|rxmb
r_void
op_star
id|rxmb
suffix:semicolon
multiline_comment|/* Receive mail box */
DECL|member|flags
r_void
op_star
id|flags
suffix:semicolon
multiline_comment|/* flags */
DECL|member|tx_status
r_void
op_star
id|tx_status
suffix:semicolon
multiline_comment|/* Tx status element */
DECL|member|rx_status
r_void
op_star
id|rx_status
suffix:semicolon
multiline_comment|/* Rx status element */
DECL|member|txbuf
r_void
op_star
id|txbuf
suffix:semicolon
multiline_comment|/* -&gt; current Tx buffer */
DECL|member|txbuf_base
r_void
op_star
id|txbuf_base
suffix:semicolon
multiline_comment|/* -&gt; first Tx buffer */
DECL|member|txbuf_last
r_void
op_star
id|txbuf_last
suffix:semicolon
multiline_comment|/* -&gt; last Tx buffer */
DECL|member|rxbuf_base
r_void
op_star
id|rxbuf_base
suffix:semicolon
multiline_comment|/* -&gt; first Rx buffer */
DECL|member|rxbuf_last
r_void
op_star
id|rxbuf_last
suffix:semicolon
multiline_comment|/* -&gt; last Rx buffer */
DECL|member|rx_base
r_int
id|rx_base
suffix:semicolon
multiline_comment|/* S508 receive buffer base */
DECL|member|rx_top
r_int
id|rx_top
suffix:semicolon
multiline_comment|/* S508 receive buffer end */
DECL|member|receive_only
r_int
r_char
id|receive_only
suffix:semicolon
multiline_comment|/* high speed receivers */
DECL|member|protocol_options
r_int
r_int
id|protocol_options
suffix:semicolon
DECL|member|kpalv_tx
r_int
r_int
id|kpalv_tx
suffix:semicolon
multiline_comment|/* Tx kpalv timer */
DECL|member|kpalv_rx
r_int
r_int
id|kpalv_rx
suffix:semicolon
multiline_comment|/* Rx kpalv timer */
DECL|member|kpalv_err
r_int
r_int
id|kpalv_err
suffix:semicolon
multiline_comment|/* Error tolerance */
DECL|member|slarp_timer
r_int
r_int
id|slarp_timer
suffix:semicolon
multiline_comment|/* SLARP req timer */
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/* state of the link */
DECL|member|api_status
r_int
r_char
id|api_status
suffix:semicolon
DECL|member|update_call_count
r_int
r_char
id|update_call_count
suffix:semicolon
DECL|member|api_options
r_int
r_int
id|api_options
suffix:semicolon
multiline_comment|/* for async config */
DECL|member|async_mode
r_int
r_char
id|async_mode
suffix:semicolon
DECL|member|tx_bits_per_char
r_int
r_int
id|tx_bits_per_char
suffix:semicolon
DECL|member|rx_bits_per_char
r_int
r_int
id|rx_bits_per_char
suffix:semicolon
DECL|member|stop_bits
r_int
r_int
id|stop_bits
suffix:semicolon
DECL|member|parity
r_int
r_int
id|parity
suffix:semicolon
DECL|member|break_timer
r_int
r_int
id|break_timer
suffix:semicolon
DECL|member|inter_char_timer
r_int
r_int
id|inter_char_timer
suffix:semicolon
DECL|member|rx_complete_length
r_int
r_int
id|rx_complete_length
suffix:semicolon
DECL|member|xon_char
r_int
r_int
id|xon_char
suffix:semicolon
DECL|member|xoff_char
r_int
r_int
id|xoff_char
suffix:semicolon
DECL|member|comm_enabled
r_int
r_char
id|comm_enabled
suffix:semicolon
multiline_comment|/* Is comm enabled or not */
DECL|member|backup
r_int
r_char
id|backup
suffix:semicolon
DECL|member|c
)brace
id|c
suffix:semicolon
r_struct
(brace
DECL|member|tx_status
r_void
op_star
id|tx_status
suffix:semicolon
multiline_comment|/* Tx status element */
DECL|member|rx_status
r_void
op_star
id|rx_status
suffix:semicolon
multiline_comment|/* Rx status element */
DECL|member|trace_status
r_void
op_star
id|trace_status
suffix:semicolon
multiline_comment|/* Trace status element */
DECL|member|txbuf
r_void
op_star
id|txbuf
suffix:semicolon
multiline_comment|/* -&gt; current Tx buffer */
DECL|member|txbuf_base
r_void
op_star
id|txbuf_base
suffix:semicolon
multiline_comment|/* -&gt; first Tx buffer */
DECL|member|txbuf_last
r_void
op_star
id|txbuf_last
suffix:semicolon
multiline_comment|/* -&gt; last Tx buffer */
DECL|member|rxbuf_base
r_void
op_star
id|rxbuf_base
suffix:semicolon
multiline_comment|/* -&gt; first Rx buffer */
DECL|member|rxbuf_last
r_void
op_star
id|rxbuf_last
suffix:semicolon
multiline_comment|/* -&gt; last Rx buffer */
DECL|member|tracebuf
r_void
op_star
id|tracebuf
suffix:semicolon
multiline_comment|/* -&gt; current Trace buffer */
DECL|member|tracebuf_base
r_void
op_star
id|tracebuf_base
suffix:semicolon
multiline_comment|/* -&gt; current Trace buffer */
DECL|member|tracebuf_last
r_void
op_star
id|tracebuf_last
suffix:semicolon
multiline_comment|/* -&gt; current Trace buffer */
DECL|member|rx_base
r_int
id|rx_base
suffix:semicolon
multiline_comment|/* receive buffer base */
DECL|member|rx_end
r_int
id|rx_end
suffix:semicolon
multiline_comment|/* receive buffer end */
DECL|member|trace_base
r_int
id|trace_base
suffix:semicolon
multiline_comment|/* trace buffer base */
DECL|member|trace_end
r_int
id|trace_end
suffix:semicolon
multiline_comment|/* trace buffer end */
DECL|member|h
)brace
id|h
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|typedef|sdla_t
)brace
id|sdla_t
suffix:semicolon
multiline_comment|/****** Public Functions ****************************************************/
r_void
id|wanpipe_open
(paren
id|sdla_t
op_star
id|card
)paren
suffix:semicolon
multiline_comment|/* wpmain.c */
r_void
id|wanpipe_close
(paren
id|sdla_t
op_star
id|card
)paren
suffix:semicolon
multiline_comment|/* wpmain.c */
r_void
id|wanpipe_set_state
(paren
id|sdla_t
op_star
id|card
comma
r_int
id|state
)paren
suffix:semicolon
multiline_comment|/* wpmain.c */
r_int
id|wpx_init
(paren
id|sdla_t
op_star
id|card
comma
id|wandev_conf_t
op_star
id|conf
)paren
suffix:semicolon
multiline_comment|/* wpx.c */
r_int
id|wpf_init
(paren
id|sdla_t
op_star
id|card
comma
id|wandev_conf_t
op_star
id|conf
)paren
suffix:semicolon
multiline_comment|/* wpf.c */
r_int
id|wpp_init
(paren
id|sdla_t
op_star
id|card
comma
id|wandev_conf_t
op_star
id|conf
)paren
suffix:semicolon
multiline_comment|/* wpp.c */
r_int
id|wpc_init
(paren
id|sdla_t
op_star
id|card
comma
id|wandev_conf_t
op_star
id|conf
)paren
suffix:semicolon
multiline_comment|/* Cisco HDLC */
r_int
id|bsc_init
(paren
id|sdla_t
op_star
id|card
comma
id|wandev_conf_t
op_star
id|conf
)paren
suffix:semicolon
multiline_comment|/* BSC streaming */
r_int
id|hdlc_init
c_func
(paren
id|sdla_t
op_star
id|card
comma
id|wandev_conf_t
op_star
id|conf
)paren
suffix:semicolon
multiline_comment|/* HDLC support */
r_int
id|wpft1_init
(paren
id|sdla_t
op_star
id|card
comma
id|wandev_conf_t
op_star
id|conf
)paren
suffix:semicolon
multiline_comment|/* FT1 Config support */
r_int
id|wsppp_init
(paren
id|sdla_t
op_star
id|card
comma
id|wandev_conf_t
op_star
id|conf
)paren
suffix:semicolon
multiline_comment|/* Sync PPP on top of RAW CHDLC */
r_extern
id|sdla_t
op_star
id|wanpipe_find_card
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
id|sdla_t
op_star
id|wanpipe_find_card_num
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|wanpipe_queue_tq
(paren
r_struct
id|tq_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|wanpipe_mark_bh
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|wakeup_sk_bh
(paren
id|netdevice_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|change_dev_flags
(paren
id|netdevice_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|get_ip_address
(paren
id|netdevice_t
op_star
id|dev
comma
r_int
id|option
)paren
suffix:semicolon
r_extern
r_void
id|add_gateway
c_func
(paren
id|sdla_t
op_star
comma
id|netdevice_t
op_star
)paren
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* _WANPIPE_H */
eof
