multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irsysctl.c&n; * Version:       1.0&n; * Description:   Sysctl interface for IrDA&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Sun May 24 22:12:06 1998&n; * Modified at:   Fri Jun  4 02:50:15 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1997, 1999 Dag Brattli, All Rights Reserved.&n; *     Copyright (c) 2000-2001 Jean Tourrilhes &lt;jt@hpl.hp.com&gt;&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;&t;&t;/* irda_debug */
macro_line|#include &lt;net/irda/irias_object.h&gt;
DECL|macro|NET_IRDA
mdefine_line|#define NET_IRDA 412 /* Random number */
DECL|enumerator|DISCOVERY
DECL|enumerator|DEVNAME
DECL|enumerator|DEBUG
DECL|enumerator|FAST_POLL
DECL|enumerator|DISCOVERY_SLOTS
r_enum
(brace
id|DISCOVERY
op_assign
l_int|1
comma
id|DEVNAME
comma
id|DEBUG
comma
id|FAST_POLL
comma
id|DISCOVERY_SLOTS
comma
DECL|enumerator|DISCOVERY_TIMEOUT
DECL|enumerator|SLOT_TIMEOUT
DECL|enumerator|MAX_BAUD_RATE
DECL|enumerator|MIN_TX_TURN_TIME
id|DISCOVERY_TIMEOUT
comma
id|SLOT_TIMEOUT
comma
id|MAX_BAUD_RATE
comma
id|MIN_TX_TURN_TIME
comma
DECL|enumerator|MAX_TX_DATA_SIZE
DECL|enumerator|MAX_TX_WINDOW
DECL|enumerator|MAX_NOREPLY_TIME
DECL|enumerator|WARN_NOREPLY_TIME
id|MAX_TX_DATA_SIZE
comma
id|MAX_TX_WINDOW
comma
id|MAX_NOREPLY_TIME
comma
id|WARN_NOREPLY_TIME
comma
DECL|enumerator|LAP_KEEPALIVE_TIME
id|LAP_KEEPALIVE_TIME
)brace
suffix:semicolon
r_extern
r_int
id|sysctl_discovery
suffix:semicolon
r_extern
r_int
id|sysctl_discovery_slots
suffix:semicolon
r_extern
r_int
id|sysctl_discovery_timeout
suffix:semicolon
r_extern
r_int
id|sysctl_slot_timeout
suffix:semicolon
r_extern
r_int
id|sysctl_fast_poll_increase
suffix:semicolon
DECL|variable|sysctl_compression
r_int
id|sysctl_compression
op_assign
l_int|0
suffix:semicolon
r_extern
r_char
id|sysctl_devname
(braket
)braket
suffix:semicolon
r_extern
r_int
id|sysctl_max_baud_rate
suffix:semicolon
r_extern
r_int
id|sysctl_min_tx_turn_time
suffix:semicolon
r_extern
r_int
id|sysctl_max_tx_data_size
suffix:semicolon
r_extern
r_int
id|sysctl_max_tx_window
suffix:semicolon
r_extern
r_int
id|sysctl_max_noreply_time
suffix:semicolon
r_extern
r_int
id|sysctl_warn_noreply_time
suffix:semicolon
r_extern
r_int
id|sysctl_lap_keepalive_time
suffix:semicolon
multiline_comment|/* this is needed for the proc_dointvec_minmax - Jean II */
DECL|variable|max_discovery_slots
r_static
r_int
id|max_discovery_slots
op_assign
l_int|16
suffix:semicolon
multiline_comment|/* ??? */
DECL|variable|min_discovery_slots
r_static
r_int
id|min_discovery_slots
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* IrLAP 6.13.2 says 25ms to 10+70ms - allow higher since some devices&n; * seems to require it. (from Dag&squot;s comment) */
DECL|variable|max_slot_timeout
r_static
r_int
id|max_slot_timeout
op_assign
l_int|160
suffix:semicolon
DECL|variable|min_slot_timeout
r_static
r_int
id|min_slot_timeout
op_assign
l_int|20
suffix:semicolon
DECL|variable|max_max_baud_rate
r_static
r_int
id|max_max_baud_rate
op_assign
l_int|16000000
suffix:semicolon
multiline_comment|/* See qos.c - IrLAP spec */
DECL|variable|min_max_baud_rate
r_static
r_int
id|min_max_baud_rate
op_assign
l_int|2400
suffix:semicolon
DECL|variable|max_min_tx_turn_time
r_static
r_int
id|max_min_tx_turn_time
op_assign
l_int|10000
suffix:semicolon
multiline_comment|/* See qos.c - IrLAP spec */
DECL|variable|min_min_tx_turn_time
r_static
r_int
id|min_min_tx_turn_time
suffix:semicolon
DECL|variable|max_max_tx_data_size
r_static
r_int
id|max_max_tx_data_size
op_assign
l_int|2048
suffix:semicolon
multiline_comment|/* See qos.c - IrLAP spec */
DECL|variable|min_max_tx_data_size
r_static
r_int
id|min_max_tx_data_size
op_assign
l_int|64
suffix:semicolon
DECL|variable|max_max_tx_window
r_static
r_int
id|max_max_tx_window
op_assign
l_int|7
suffix:semicolon
multiline_comment|/* See qos.c - IrLAP spec */
DECL|variable|min_max_tx_window
r_static
r_int
id|min_max_tx_window
op_assign
l_int|1
suffix:semicolon
DECL|variable|max_max_noreply_time
r_static
r_int
id|max_max_noreply_time
op_assign
l_int|40
suffix:semicolon
multiline_comment|/* See qos.c - IrLAP spec */
DECL|variable|min_max_noreply_time
r_static
r_int
id|min_max_noreply_time
op_assign
l_int|3
suffix:semicolon
DECL|variable|max_warn_noreply_time
r_static
r_int
id|max_warn_noreply_time
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* 3s == standard */
DECL|variable|min_warn_noreply_time
r_static
r_int
id|min_warn_noreply_time
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* 1s == min WD_TIMER */
DECL|variable|max_lap_keepalive_time
r_static
r_int
id|max_lap_keepalive_time
op_assign
l_int|10000
suffix:semicolon
multiline_comment|/* 10s */
DECL|variable|min_lap_keepalive_time
r_static
r_int
id|min_lap_keepalive_time
op_assign
l_int|100
suffix:semicolon
multiline_comment|/* 100us */
multiline_comment|/* For other sysctl, I&squot;ve no idea of the range. Maybe Dag could help&n; * us on that - Jean II */
DECL|function|do_devname
r_static
r_int
id|do_devname
c_func
(paren
id|ctl_table
op_star
id|table
comma
r_int
id|write
comma
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|buffer
comma
r_int
op_star
id|lenp
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|proc_dostring
c_func
(paren
id|table
comma
id|write
comma
id|filp
comma
id|buffer
comma
id|lenp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
op_logical_and
id|write
)paren
(brace
r_struct
id|ias_value
op_star
id|val
suffix:semicolon
id|val
op_assign
id|irias_new_string_value
c_func
(paren
id|sysctl_devname
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
id|irias_object_change_attribute
c_func
(paren
l_string|&quot;Device&quot;
comma
l_string|&quot;DeviceName&quot;
comma
id|val
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* One file */
DECL|variable|irda_table
r_static
id|ctl_table
id|irda_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|DISCOVERY
comma
dot
id|procname
op_assign
l_string|&quot;discovery&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_discovery
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|DEVNAME
comma
dot
id|procname
op_assign
l_string|&quot;devname&quot;
comma
dot
id|data
op_assign
id|sysctl_devname
comma
dot
id|maxlen
op_assign
l_int|65
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|do_devname
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_string
)brace
comma
macro_line|#ifdef CONFIG_IRDA_DEBUG
(brace
dot
id|ctl_name
op_assign
id|DEBUG
comma
dot
id|procname
op_assign
l_string|&quot;debug&quot;
comma
dot
id|data
op_assign
op_amp
id|irda_debug
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_IRDA_FAST_RR
(brace
dot
id|ctl_name
op_assign
id|FAST_POLL
comma
dot
id|procname
op_assign
l_string|&quot;fast_poll_increase&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_fast_poll_increase
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
macro_line|#endif
(brace
dot
id|ctl_name
op_assign
id|DISCOVERY_SLOTS
comma
dot
id|procname
op_assign
l_string|&quot;discovery_slots&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_discovery_slots
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_minmax
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_intvec
comma
dot
id|extra1
op_assign
op_amp
id|min_discovery_slots
comma
dot
id|extra2
op_assign
op_amp
id|max_discovery_slots
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|DISCOVERY_TIMEOUT
comma
dot
id|procname
op_assign
l_string|&quot;discovery_timeout&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_discovery_timeout
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|SLOT_TIMEOUT
comma
dot
id|procname
op_assign
l_string|&quot;slot_timeout&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_slot_timeout
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_minmax
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_intvec
comma
dot
id|extra1
op_assign
op_amp
id|min_slot_timeout
comma
dot
id|extra2
op_assign
op_amp
id|max_slot_timeout
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|MAX_BAUD_RATE
comma
dot
id|procname
op_assign
l_string|&quot;max_baud_rate&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_max_baud_rate
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_minmax
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_intvec
comma
dot
id|extra1
op_assign
op_amp
id|min_max_baud_rate
comma
dot
id|extra2
op_assign
op_amp
id|max_max_baud_rate
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|MIN_TX_TURN_TIME
comma
dot
id|procname
op_assign
l_string|&quot;min_tx_turn_time&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_min_tx_turn_time
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_minmax
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_intvec
comma
dot
id|extra1
op_assign
op_amp
id|min_min_tx_turn_time
comma
dot
id|extra2
op_assign
op_amp
id|max_min_tx_turn_time
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|MAX_TX_DATA_SIZE
comma
dot
id|procname
op_assign
l_string|&quot;max_tx_data_size&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_max_tx_data_size
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_minmax
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_intvec
comma
dot
id|extra1
op_assign
op_amp
id|min_max_tx_data_size
comma
dot
id|extra2
op_assign
op_amp
id|max_max_tx_data_size
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|MAX_TX_WINDOW
comma
dot
id|procname
op_assign
l_string|&quot;max_tx_window&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_max_tx_window
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_minmax
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_intvec
comma
dot
id|extra1
op_assign
op_amp
id|min_max_tx_window
comma
dot
id|extra2
op_assign
op_amp
id|max_max_tx_window
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|MAX_NOREPLY_TIME
comma
dot
id|procname
op_assign
l_string|&quot;max_noreply_time&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_max_noreply_time
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_minmax
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_intvec
comma
dot
id|extra1
op_assign
op_amp
id|min_max_noreply_time
comma
dot
id|extra2
op_assign
op_amp
id|max_max_noreply_time
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|WARN_NOREPLY_TIME
comma
dot
id|procname
op_assign
l_string|&quot;warn_noreply_time&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_warn_noreply_time
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_minmax
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_intvec
comma
dot
id|extra1
op_assign
op_amp
id|min_warn_noreply_time
comma
dot
id|extra2
op_assign
op_amp
id|max_warn_noreply_time
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|LAP_KEEPALIVE_TIME
comma
dot
id|procname
op_assign
l_string|&quot;lap_keepalive_time&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_lap_keepalive_time
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_minmax
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_intvec
comma
dot
id|extra1
op_assign
op_amp
id|min_lap_keepalive_time
comma
dot
id|extra2
op_assign
op_amp
id|max_lap_keepalive_time
)brace
comma
(brace
dot
id|ctl_name
op_assign
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* One directory */
DECL|variable|irda_net_table
r_static
id|ctl_table
id|irda_net_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|NET_IRDA
comma
dot
id|procname
op_assign
l_string|&quot;irda&quot;
comma
dot
id|maxlen
op_assign
l_int|0
comma
dot
id|mode
op_assign
l_int|0555
comma
dot
id|child
op_assign
id|irda_table
)brace
comma
(brace
dot
id|ctl_name
op_assign
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* The parent directory */
DECL|variable|irda_root_table
r_static
id|ctl_table
id|irda_root_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|CTL_NET
comma
dot
id|procname
op_assign
l_string|&quot;net&quot;
comma
dot
id|maxlen
op_assign
l_int|0
comma
dot
id|mode
op_assign
l_int|0555
comma
dot
id|child
op_assign
id|irda_net_table
)brace
comma
(brace
dot
id|ctl_name
op_assign
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|irda_table_header
r_static
r_struct
id|ctl_table_header
op_star
id|irda_table_header
suffix:semicolon
multiline_comment|/*&n; * Function irda_sysctl_register (void)&n; *&n; *    Register our sysctl interface&n; *&n; */
DECL|function|irda_sysctl_register
r_int
id|__init
id|irda_sysctl_register
c_func
(paren
r_void
)paren
(brace
id|irda_table_header
op_assign
id|register_sysctl_table
c_func
(paren
id|irda_root_table
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|irda_table_header
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_sysctl_unregister (void)&n; *&n; *    Unregister our sysctl interface&n; *&n; */
DECL|function|irda_sysctl_unregister
r_void
id|__exit
id|irda_sysctl_unregister
c_func
(paren
r_void
)paren
(brace
id|unregister_sysctl_table
c_func
(paren
id|irda_table_header
)paren
suffix:semicolon
)brace
eof
