multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irsyms.c&n; * Version:       0.9&n; * Description:   IrDA module symbols&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Mon Dec 15 13:55:39 1997&n; * Modified at:   Wed Jan  5 15:12:41 2000&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1997, 1999-2000 Dag Brattli, All Rights Reserved.&n; *     Copyright (c) 2000-2001 Jean Tourrilhes &lt;jt@hpl.hp.com&gt;&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;&t;&t;/* ARPHRD_IRDA */
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irlap.h&gt;
macro_line|#include &lt;net/irda/irlmp.h&gt;
macro_line|#include &lt;net/irda/iriap.h&gt;
macro_line|#include &lt;net/irda/irias_object.h&gt;
macro_line|#include &lt;net/irda/irttp.h&gt;
macro_line|#include &lt;net/irda/irda_device.h&gt;
macro_line|#include &lt;net/irda/wrapper.h&gt;
macro_line|#include &lt;net/irda/timer.h&gt;
macro_line|#include &lt;net/irda/parameters.h&gt;
macro_line|#include &lt;net/irda/crc.h&gt;
r_extern
r_struct
id|proc_dir_entry
op_star
id|proc_irda
suffix:semicolon
r_extern
r_void
id|irda_proc_register
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|irda_proc_unregister
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|irda_sysctl_register
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|irda_sysctl_unregister
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|irda_proto_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|irda_proto_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|irda_device_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|irlan_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|irlan_client_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|irlan_server_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ircomm_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ircomm_tty_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|irlpt_client_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|irlpt_server_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|irsock_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|irsock_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|irlap_driver_rcv
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
multiline_comment|/* IrTTP */
DECL|variable|irttp_open_tsap
id|EXPORT_SYMBOL
c_func
(paren
id|irttp_open_tsap
)paren
suffix:semicolon
DECL|variable|irttp_close_tsap
id|EXPORT_SYMBOL
c_func
(paren
id|irttp_close_tsap
)paren
suffix:semicolon
DECL|variable|irttp_connect_response
id|EXPORT_SYMBOL
c_func
(paren
id|irttp_connect_response
)paren
suffix:semicolon
DECL|variable|irttp_data_request
id|EXPORT_SYMBOL
c_func
(paren
id|irttp_data_request
)paren
suffix:semicolon
DECL|variable|irttp_disconnect_request
id|EXPORT_SYMBOL
c_func
(paren
id|irttp_disconnect_request
)paren
suffix:semicolon
DECL|variable|irttp_flow_request
id|EXPORT_SYMBOL
c_func
(paren
id|irttp_flow_request
)paren
suffix:semicolon
DECL|variable|irttp_connect_request
id|EXPORT_SYMBOL
c_func
(paren
id|irttp_connect_request
)paren
suffix:semicolon
DECL|variable|irttp_udata_request
id|EXPORT_SYMBOL
c_func
(paren
id|irttp_udata_request
)paren
suffix:semicolon
DECL|variable|irttp_dup
id|EXPORT_SYMBOL
c_func
(paren
id|irttp_dup
)paren
suffix:semicolon
multiline_comment|/* Main IrDA module */
macro_line|#ifdef CONFIG_IRDA_DEBUG
DECL|variable|irda_debug
id|EXPORT_SYMBOL
c_func
(paren
id|irda_debug
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|irda_notify_init
id|EXPORT_SYMBOL
c_func
(paren
id|irda_notify_init
)paren
suffix:semicolon
DECL|variable|irda_param_insert
id|EXPORT_SYMBOL
c_func
(paren
id|irda_param_insert
)paren
suffix:semicolon
DECL|variable|irda_param_extract
id|EXPORT_SYMBOL
c_func
(paren
id|irda_param_extract
)paren
suffix:semicolon
DECL|variable|irda_param_extract_all
id|EXPORT_SYMBOL
c_func
(paren
id|irda_param_extract_all
)paren
suffix:semicolon
DECL|variable|irda_param_pack
id|EXPORT_SYMBOL
c_func
(paren
id|irda_param_pack
)paren
suffix:semicolon
DECL|variable|irda_param_unpack
id|EXPORT_SYMBOL
c_func
(paren
id|irda_param_unpack
)paren
suffix:semicolon
multiline_comment|/* IrIAP/IrIAS */
DECL|variable|iriap_open
id|EXPORT_SYMBOL
c_func
(paren
id|iriap_open
)paren
suffix:semicolon
DECL|variable|iriap_close
id|EXPORT_SYMBOL
c_func
(paren
id|iriap_close
)paren
suffix:semicolon
DECL|variable|iriap_getvaluebyclass_request
id|EXPORT_SYMBOL
c_func
(paren
id|iriap_getvaluebyclass_request
)paren
suffix:semicolon
DECL|variable|irias_object_change_attribute
id|EXPORT_SYMBOL
c_func
(paren
id|irias_object_change_attribute
)paren
suffix:semicolon
DECL|variable|irias_add_integer_attrib
id|EXPORT_SYMBOL
c_func
(paren
id|irias_add_integer_attrib
)paren
suffix:semicolon
DECL|variable|irias_add_octseq_attrib
id|EXPORT_SYMBOL
c_func
(paren
id|irias_add_octseq_attrib
)paren
suffix:semicolon
DECL|variable|irias_add_string_attrib
id|EXPORT_SYMBOL
c_func
(paren
id|irias_add_string_attrib
)paren
suffix:semicolon
DECL|variable|irias_insert_object
id|EXPORT_SYMBOL
c_func
(paren
id|irias_insert_object
)paren
suffix:semicolon
DECL|variable|irias_new_object
id|EXPORT_SYMBOL
c_func
(paren
id|irias_new_object
)paren
suffix:semicolon
DECL|variable|irias_delete_object
id|EXPORT_SYMBOL
c_func
(paren
id|irias_delete_object
)paren
suffix:semicolon
DECL|variable|irias_delete_value
id|EXPORT_SYMBOL
c_func
(paren
id|irias_delete_value
)paren
suffix:semicolon
DECL|variable|irias_find_object
id|EXPORT_SYMBOL
c_func
(paren
id|irias_find_object
)paren
suffix:semicolon
DECL|variable|irias_find_attrib
id|EXPORT_SYMBOL
c_func
(paren
id|irias_find_attrib
)paren
suffix:semicolon
DECL|variable|irias_new_integer_value
id|EXPORT_SYMBOL
c_func
(paren
id|irias_new_integer_value
)paren
suffix:semicolon
DECL|variable|irias_new_string_value
id|EXPORT_SYMBOL
c_func
(paren
id|irias_new_string_value
)paren
suffix:semicolon
DECL|variable|irias_new_octseq_value
id|EXPORT_SYMBOL
c_func
(paren
id|irias_new_octseq_value
)paren
suffix:semicolon
multiline_comment|/* IrLMP */
DECL|variable|irlmp_discovery_request
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_discovery_request
)paren
suffix:semicolon
DECL|variable|irlmp_get_discoveries
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_get_discoveries
)paren
suffix:semicolon
DECL|variable|sysctl_discovery_timeout
id|EXPORT_SYMBOL
c_func
(paren
id|sysctl_discovery_timeout
)paren
suffix:semicolon
DECL|variable|irlmp_register_client
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_register_client
)paren
suffix:semicolon
DECL|variable|irlmp_unregister_client
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_unregister_client
)paren
suffix:semicolon
DECL|variable|irlmp_update_client
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_update_client
)paren
suffix:semicolon
DECL|variable|irlmp_register_service
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_register_service
)paren
suffix:semicolon
DECL|variable|irlmp_unregister_service
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_unregister_service
)paren
suffix:semicolon
DECL|variable|irlmp_service_to_hint
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_service_to_hint
)paren
suffix:semicolon
DECL|variable|irlmp_data_request
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_data_request
)paren
suffix:semicolon
DECL|variable|irlmp_open_lsap
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_open_lsap
)paren
suffix:semicolon
DECL|variable|irlmp_close_lsap
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_close_lsap
)paren
suffix:semicolon
DECL|variable|irlmp_connect_request
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_connect_request
)paren
suffix:semicolon
DECL|variable|irlmp_connect_response
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_connect_response
)paren
suffix:semicolon
DECL|variable|irlmp_disconnect_request
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_disconnect_request
)paren
suffix:semicolon
DECL|variable|irlmp_get_daddr
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_get_daddr
)paren
suffix:semicolon
DECL|variable|irlmp_get_saddr
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_get_saddr
)paren
suffix:semicolon
DECL|variable|irlmp_dup
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_dup
)paren
suffix:semicolon
DECL|variable|lmp_reasons
id|EXPORT_SYMBOL
c_func
(paren
id|lmp_reasons
)paren
suffix:semicolon
multiline_comment|/* Queue */
DECL|variable|hashbin_new
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_new
)paren
suffix:semicolon
DECL|variable|hashbin_insert
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_insert
)paren
suffix:semicolon
DECL|variable|hashbin_delete
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_delete
)paren
suffix:semicolon
DECL|variable|hashbin_remove
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_remove
)paren
suffix:semicolon
DECL|variable|hashbin_remove_this
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_remove_this
)paren
suffix:semicolon
DECL|variable|hashbin_find
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_find
)paren
suffix:semicolon
DECL|variable|hashbin_lock_find
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_lock_find
)paren
suffix:semicolon
DECL|variable|hashbin_find_next
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_find_next
)paren
suffix:semicolon
DECL|variable|hashbin_get_next
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_get_next
)paren
suffix:semicolon
DECL|variable|hashbin_get_first
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_get_first
)paren
suffix:semicolon
multiline_comment|/* IrLAP */
DECL|variable|irlap_open
id|EXPORT_SYMBOL
c_func
(paren
id|irlap_open
)paren
suffix:semicolon
DECL|variable|irlap_close
id|EXPORT_SYMBOL
c_func
(paren
id|irlap_close
)paren
suffix:semicolon
DECL|variable|irda_init_max_qos_capabilies
id|EXPORT_SYMBOL
c_func
(paren
id|irda_init_max_qos_capabilies
)paren
suffix:semicolon
DECL|variable|irda_qos_bits_to_value
id|EXPORT_SYMBOL
c_func
(paren
id|irda_qos_bits_to_value
)paren
suffix:semicolon
DECL|variable|irda_device_setup
id|EXPORT_SYMBOL
c_func
(paren
id|irda_device_setup
)paren
suffix:semicolon
DECL|variable|alloc_irdadev
id|EXPORT_SYMBOL
c_func
(paren
id|alloc_irdadev
)paren
suffix:semicolon
DECL|variable|irda_device_set_media_busy
id|EXPORT_SYMBOL
c_func
(paren
id|irda_device_set_media_busy
)paren
suffix:semicolon
DECL|variable|irda_device_txqueue_empty
id|EXPORT_SYMBOL
c_func
(paren
id|irda_device_txqueue_empty
)paren
suffix:semicolon
DECL|variable|irda_device_dongle_init
id|EXPORT_SYMBOL
c_func
(paren
id|irda_device_dongle_init
)paren
suffix:semicolon
DECL|variable|irda_device_dongle_cleanup
id|EXPORT_SYMBOL
c_func
(paren
id|irda_device_dongle_cleanup
)paren
suffix:semicolon
DECL|variable|irda_device_register_dongle
id|EXPORT_SYMBOL
c_func
(paren
id|irda_device_register_dongle
)paren
suffix:semicolon
DECL|variable|irda_device_unregister_dongle
id|EXPORT_SYMBOL
c_func
(paren
id|irda_device_unregister_dongle
)paren
suffix:semicolon
DECL|variable|irda_task_execute
id|EXPORT_SYMBOL
c_func
(paren
id|irda_task_execute
)paren
suffix:semicolon
DECL|variable|irda_task_next_state
id|EXPORT_SYMBOL
c_func
(paren
id|irda_task_next_state
)paren
suffix:semicolon
DECL|variable|irda_task_delete
id|EXPORT_SYMBOL
c_func
(paren
id|irda_task_delete
)paren
suffix:semicolon
DECL|variable|async_wrap_skb
id|EXPORT_SYMBOL
c_func
(paren
id|async_wrap_skb
)paren
suffix:semicolon
DECL|variable|async_unwrap_char
id|EXPORT_SYMBOL
c_func
(paren
id|async_unwrap_char
)paren
suffix:semicolon
DECL|variable|irda_calc_crc16
id|EXPORT_SYMBOL
c_func
(paren
id|irda_calc_crc16
)paren
suffix:semicolon
DECL|variable|irda_crc16_table
id|EXPORT_SYMBOL
c_func
(paren
id|irda_crc16_table
)paren
suffix:semicolon
DECL|variable|irda_start_timer
id|EXPORT_SYMBOL
c_func
(paren
id|irda_start_timer
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IRDA_DEBUG
DECL|variable|irda_debug
id|__u32
id|irda_debug
op_assign
id|IRDA_DEBUG_LEVEL
suffix:semicolon
macro_line|#endif
multiline_comment|/* Packet type handler.&n; * Tell the kernel how IrDA packets should be handled.&n; */
DECL|variable|irda_packet_type
r_static
r_struct
id|packet_type
id|irda_packet_type
op_assign
(brace
dot
id|type
op_assign
id|__constant_htons
c_func
(paren
id|ETH_P_IRDA
)paren
comma
dot
id|func
op_assign
id|irlap_driver_rcv
comma
multiline_comment|/* Packet type handler irlap_frame.c */
)brace
suffix:semicolon
multiline_comment|/*&n; * Function irda_notify_init (notify)&n; *&n; *    Used for initializing the notify structure&n; *&n; */
DECL|function|irda_notify_init
r_void
id|irda_notify_init
c_func
(paren
id|notify_t
op_star
id|notify
)paren
(brace
id|notify-&gt;data_indication
op_assign
l_int|NULL
suffix:semicolon
id|notify-&gt;udata_indication
op_assign
l_int|NULL
suffix:semicolon
id|notify-&gt;connect_confirm
op_assign
l_int|NULL
suffix:semicolon
id|notify-&gt;connect_indication
op_assign
l_int|NULL
suffix:semicolon
id|notify-&gt;disconnect_indication
op_assign
l_int|NULL
suffix:semicolon
id|notify-&gt;flow_indication
op_assign
l_int|NULL
suffix:semicolon
id|notify-&gt;status_indication
op_assign
l_int|NULL
suffix:semicolon
id|notify-&gt;instance
op_assign
l_int|NULL
suffix:semicolon
id|strlcpy
c_func
(paren
id|notify-&gt;name
comma
l_string|&quot;Unknown&quot;
comma
r_sizeof
(paren
id|notify-&gt;name
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_init (void)&n; *&n; *  Protocol stack initialisation entry point.&n; *  Initialise the various components of the IrDA stack&n; */
DECL|function|irda_init
r_int
id|__init
id|irda_init
c_func
(paren
r_void
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
multiline_comment|/* Lower layer of the stack */
id|irlmp_init
c_func
(paren
)paren
suffix:semicolon
id|irlap_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Higher layers of the stack */
id|iriap_init
c_func
(paren
)paren
suffix:semicolon
id|irttp_init
c_func
(paren
)paren
suffix:semicolon
id|irsock_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Add IrDA packet type (Start receiving packets) */
id|dev_add_pack
c_func
(paren
op_amp
id|irda_packet_type
)paren
suffix:semicolon
multiline_comment|/* External APIs */
macro_line|#ifdef CONFIG_PROC_FS
id|irda_proc_register
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SYSCTL
id|irda_sysctl_register
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Driver/dongle support */
id|irda_device_init
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_cleanup (void)&n; *&n; *  Protocol stack cleanup/removal entry point.&n; *  Cleanup the various components of the IrDA stack&n; */
DECL|function|irda_cleanup
r_void
id|__exit
id|irda_cleanup
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Remove External APIs */
macro_line|#ifdef CONFIG_SYSCTL
id|irda_sysctl_unregister
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif&t;
macro_line|#ifdef CONFIG_PROC_FS
id|irda_proc_unregister
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Remove IrDA packet type (stop receiving packets) */
id|dev_remove_pack
c_func
(paren
op_amp
id|irda_packet_type
)paren
suffix:semicolon
multiline_comment|/* Remove higher layers */
id|irsock_cleanup
c_func
(paren
)paren
suffix:semicolon
id|irttp_cleanup
c_func
(paren
)paren
suffix:semicolon
id|iriap_cleanup
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Remove lower layers */
id|irda_device_cleanup
c_func
(paren
)paren
suffix:semicolon
id|irlap_cleanup
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Must be done before irlmp_cleanup()! DB */
multiline_comment|/* Remove middle layer */
id|irlmp_cleanup
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The IrDA stack must be initialised *before* drivers get initialised,&n; * and *before* higher protocols (IrLAN/IrCOMM/IrNET) get initialised,&n; * otherwise bad things will happen (hashbins will be NULL for example).&n; * Those modules are at module_init()/device_initcall() level.&n; *&n; * On the other hand, it needs to be initialised *after* the basic&n; * networking, the /proc/net filesystem and sysctl module. Those are&n; * currently initialised in .../init/main.c (before initcalls).&n; * Also, IrDA drivers needs to be initialised *after* the random number&n; * generator (main stack and higher layer init don&squot;t need it anymore).&n; *&n; * Jean II&n; */
DECL|variable|irda_init
id|subsys_initcall
c_func
(paren
id|irda_init
)paren
suffix:semicolon
DECL|variable|irda_cleanup
id|module_exit
c_func
(paren
id|irda_cleanup
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Dag Brattli &lt;dagb@cs.uit.no&gt; &amp; Jean Tourrilhes &lt;jt@hpl.hp.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;The Linux IrDA Protocol Stack&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IRDA_DEBUG
id|MODULE_PARM
c_func
(paren
id|irda_debug
comma
l_string|&quot;1l&quot;
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|PF_IRDA
id|MODULE_ALIAS_NETPROTO
c_func
(paren
id|PF_IRDA
)paren
suffix:semicolon
eof
