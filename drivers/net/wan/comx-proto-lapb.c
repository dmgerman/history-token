multiline_comment|/*&n; * LAPB protocol module for the COMX driver &n; * for Linux kernel 2.2.X&n; *&n; * Original author: Tivadar Szemethy &lt;tiv@itc.hu&gt;&n; * Maintainer: Gergely Madarasz &lt;gorgo@itc.hu&gt;&n; *&n; * Copyright (C) 1997-1999 (C) ITConsult-Pro Co. &lt;info@itc.hu&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * Version 0.80 (99/06/14):&n; *&t;&t;- cleaned up the source code a bit&n; *&t;&t;- ported back to kernel, now works as non-module&n; *&n; * Changed      (00/10/29, Henner Eisen):&n; * &t;&t;- comx_rx() / comxlapb_data_indication() return status.&n; * &n; */
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;0.80&quot;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/inetdevice.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/lapb.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include&t;&quot;comx.h&quot;
macro_line|#include&t;&quot;comxhw.h&quot;
r_static
r_struct
id|proc_dir_entry
op_star
id|create_comxlapb_proc_entry
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|mode
comma
r_int
id|size
comma
r_struct
id|proc_dir_entry
op_star
id|dir
)paren
suffix:semicolon
DECL|function|comxlapb_rx
r_static
r_void
id|comxlapb_rx
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
id|dev-&gt;priv
)paren
(brace
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_else
(brace
id|lapb_data_received
c_func
(paren
id|dev-&gt;priv
comma
id|skb
)paren
suffix:semicolon
)brace
)brace
DECL|function|comxlapb_tx
r_static
r_int
id|comxlapb_tx
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|netif_wake_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|comxlapb_header
r_static
r_int
id|comxlapb_header
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
(brace
r_return
id|dev-&gt;hard_header_len
suffix:semicolon
)brace
DECL|function|comxlapb_status
r_static
r_void
id|comxlapb_status
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
r_int
id|status
)paren
(brace
r_struct
id|comx_channel
op_star
id|ch
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
(paren
id|ch
op_assign
id|dev-&gt;priv
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
id|LINE_UP
)paren
(brace
id|netif_wake_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|comx_status
c_func
(paren
id|dev
comma
id|status
)paren
suffix:semicolon
)brace
DECL|function|comxlapb_open
r_static
r_int
id|comxlapb_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|comx_channel
op_star
id|ch
op_assign
id|dev-&gt;priv
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ch-&gt;init_status
op_amp
id|HW_OPEN
)paren
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|err
op_assign
id|lapb_connect_request
c_func
(paren
id|ch
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ch-&gt;debug_flags
op_amp
id|DEBUG_COMX_LAPB
)paren
(brace
id|comx_debug
c_func
(paren
id|dev
comma
l_string|&quot;%s: lapb opened, error code: %d&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|err
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
id|ch-&gt;init_status
op_or_assign
id|LINE_OPEN
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|comxlapb_close
r_static
r_int
id|comxlapb_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|comx_channel
op_star
id|ch
op_assign
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ch-&gt;init_status
op_amp
id|HW_OPEN
)paren
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ch-&gt;debug_flags
op_amp
id|DEBUG_COMX_LAPB
)paren
(brace
id|comx_debug
c_func
(paren
id|dev
comma
l_string|&quot;%s: lapb closed&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
id|lapb_disconnect_request
c_func
(paren
id|ch
)paren
suffix:semicolon
id|ch-&gt;init_status
op_and_assign
op_complement
id|LINE_OPEN
suffix:semicolon
id|ch-&gt;line_status
op_and_assign
op_complement
id|PROTO_UP
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|comxlapb_xmit
r_static
r_int
id|comxlapb_xmit
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
id|dev
)paren
(brace
r_struct
id|comx_channel
op_star
id|ch
op_assign
id|dev-&gt;priv
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
(paren
id|ch
op_assign
id|dev-&gt;priv
)paren
op_logical_or
op_logical_neg
(paren
id|dev-&gt;flags
op_amp
(paren
id|IFF_UP
op_or
id|IFF_RUNNING
)paren
)paren
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;type
op_eq
id|ARPHRD_X25
)paren
(brace
singleline_comment|// first byte tells what to do 
r_switch
c_cond
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
)paren
(brace
r_case
l_int|0x00
suffix:colon
r_break
suffix:semicolon
singleline_comment|// transmit
r_case
l_int|0x01
suffix:colon
id|lapb_connect_request
c_func
(paren
id|ch
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
l_int|0x02
suffix:colon
id|lapb_disconnect_request
c_func
(paren
id|ch
)paren
suffix:semicolon
r_default
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|skb_pull
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
)brace
id|netif_stop_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb2
op_assign
id|skb_clone
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|lapb_data_request
c_func
(paren
id|ch
comma
id|skb2
)paren
suffix:semicolon
)brace
r_return
id|FRAME_ACCEPTED
suffix:semicolon
)brace
DECL|function|comxlapb_statistics
r_static
r_int
id|comxlapb_statistics
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_char
op_star
id|page
)paren
(brace
r_struct
id|lapb_parms_struct
id|parms
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;Line status: &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lapb_getparms
c_func
(paren
id|dev-&gt;priv
comma
op_amp
id|parms
)paren
op_ne
id|LAPB_OK
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;not initialized&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;%s (%s), T1: %d/%d, T2: %d/%d, N2: %d/%d, &quot;
l_string|&quot;window: %d&bslash;n&quot;
comma
id|parms.mode
op_amp
id|LAPB_DCE
ques
c_cond
l_string|&quot;DCE&quot;
suffix:colon
l_string|&quot;DTE&quot;
comma
id|parms.mode
op_amp
id|LAPB_EXTENDED
ques
c_cond
l_string|&quot;EXTENDED&quot;
suffix:colon
l_string|&quot;STANDARD&quot;
comma
id|parms.t1timer
comma
id|parms.t1
comma
id|parms.t2timer
comma
id|parms.t2
comma
id|parms.n2count
comma
id|parms.n2
comma
id|parms.window
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|comxlapb_read_proc
r_static
r_int
id|comxlapb_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|file
op_assign
(paren
r_struct
id|proc_dir_entry
op_star
)paren
id|data
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|file-&gt;parent-&gt;data
suffix:semicolon
r_struct
id|lapb_parms_struct
id|parms
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|lapb_getparms
c_func
(paren
id|dev-&gt;priv
comma
op_amp
id|parms
)paren
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|file-&gt;name
comma
id|FILENAME_T1
)paren
op_eq
l_int|0
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;%02u / %02u&bslash;n&quot;
comma
id|parms.t1timer
comma
id|parms.t1
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|file-&gt;name
comma
id|FILENAME_T2
)paren
op_eq
l_int|0
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;%02u / %02u&bslash;n&quot;
comma
id|parms.t2timer
comma
id|parms.t2
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|file-&gt;name
comma
id|FILENAME_N2
)paren
op_eq
l_int|0
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;%02u / %02u&bslash;n&quot;
comma
id|parms.n2count
comma
id|parms.n2
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|file-&gt;name
comma
id|FILENAME_WINDOW
)paren
op_eq
l_int|0
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;%u&bslash;n&quot;
comma
id|parms.window
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|file-&gt;name
comma
id|FILENAME_MODE
)paren
op_eq
l_int|0
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;%s, %s&bslash;n&quot;
comma
id|parms.mode
op_amp
id|LAPB_DCE
ques
c_cond
l_string|&quot;DCE&quot;
suffix:colon
l_string|&quot;DTE&quot;
comma
id|parms.mode
op_amp
id|LAPB_EXTENDED
ques
c_cond
l_string|&quot;EXTENDED&quot;
suffix:colon
l_string|&quot;STANDARD&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;comxlapb: internal error, filename %s&bslash;n&quot;
comma
id|file-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
r_if
c_cond
(paren
id|off
op_ge
id|len
)paren
(brace
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ge
id|len
op_minus
id|off
)paren
(brace
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|min_t
c_func
(paren
r_int
comma
id|count
comma
id|len
op_minus
id|off
)paren
suffix:semicolon
)brace
DECL|function|comxlapb_write_proc
r_static
r_int
id|comxlapb_write_proc
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
id|u_long
id|count
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|entry
op_assign
(paren
r_struct
id|proc_dir_entry
op_star
)paren
id|data
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|entry-&gt;parent-&gt;data
suffix:semicolon
r_struct
id|lapb_parms_struct
id|parms
suffix:semicolon
r_int
r_int
id|parm
suffix:semicolon
r_char
op_star
id|page
suffix:semicolon
r_if
c_cond
(paren
id|lapb_getparms
c_func
(paren
id|dev-&gt;priv
comma
op_amp
id|parms
)paren
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
)paren
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|page
comma
id|buffer
comma
id|count
)paren
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
(paren
id|page
op_plus
id|count
op_minus
l_int|1
)paren
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
op_star
(paren
id|page
op_plus
id|count
op_minus
l_int|1
)paren
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|entry-&gt;name
comma
id|FILENAME_T1
)paren
op_eq
l_int|0
)paren
(brace
id|parm
op_assign
id|simple_strtoul
c_func
(paren
id|page
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parm
OG
l_int|0
op_logical_and
id|parm
OL
l_int|100
)paren
(brace
id|parms.t1
op_assign
id|parm
suffix:semicolon
id|lapb_setparms
c_func
(paren
id|dev-&gt;priv
comma
op_amp
id|parms
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|entry-&gt;name
comma
id|FILENAME_T2
)paren
op_eq
l_int|0
)paren
(brace
id|parm
op_assign
id|simple_strtoul
c_func
(paren
id|page
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parm
OG
l_int|0
op_logical_and
id|parm
OL
l_int|100
)paren
(brace
id|parms.t2
op_assign
id|parm
suffix:semicolon
id|lapb_setparms
c_func
(paren
id|dev-&gt;priv
comma
op_amp
id|parms
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|entry-&gt;name
comma
id|FILENAME_N2
)paren
op_eq
l_int|0
)paren
(brace
id|parm
op_assign
id|simple_strtoul
c_func
(paren
id|page
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parm
OG
l_int|0
op_logical_and
id|parm
OL
l_int|100
)paren
(brace
id|parms.n2
op_assign
id|parm
suffix:semicolon
id|lapb_setparms
c_func
(paren
id|dev-&gt;priv
comma
op_amp
id|parms
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|entry-&gt;name
comma
id|FILENAME_WINDOW
)paren
op_eq
l_int|0
)paren
(brace
id|parms.window
op_assign
id|simple_strtoul
c_func
(paren
id|page
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
id|lapb_setparms
c_func
(paren
id|dev-&gt;priv
comma
op_amp
id|parms
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|entry-&gt;name
comma
id|FILENAME_MODE
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|comx_strcasecmp
c_func
(paren
id|page
comma
l_string|&quot;dte&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|parms.mode
op_and_assign
op_complement
(paren
id|LAPB_DCE
op_or
id|LAPB_DTE
)paren
suffix:semicolon
id|parms.mode
op_or_assign
id|LAPB_DTE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|comx_strcasecmp
c_func
(paren
id|page
comma
l_string|&quot;dce&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|parms.mode
op_and_assign
op_complement
(paren
id|LAPB_DTE
op_or
id|LAPB_DCE
)paren
suffix:semicolon
id|parms.mode
op_or_assign
id|LAPB_DCE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|comx_strcasecmp
c_func
(paren
id|page
comma
l_string|&quot;std&quot;
)paren
op_eq
l_int|0
op_logical_or
id|comx_strcasecmp
c_func
(paren
id|page
comma
l_string|&quot;standard&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|parms.mode
op_and_assign
op_complement
id|LAPB_EXTENDED
suffix:semicolon
id|parms.mode
op_or_assign
id|LAPB_STANDARD
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|comx_strcasecmp
c_func
(paren
id|page
comma
l_string|&quot;ext&quot;
)paren
op_eq
l_int|0
op_logical_or
id|comx_strcasecmp
c_func
(paren
id|page
comma
l_string|&quot;extended&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|parms.mode
op_and_assign
op_complement
id|LAPB_STANDARD
suffix:semicolon
id|parms.mode
op_or_assign
id|LAPB_EXTENDED
suffix:semicolon
)brace
id|lapb_setparms
c_func
(paren
id|dev-&gt;priv
comma
op_amp
id|parms
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;comxlapb_write_proc: internal error, filename %s&bslash;n&quot;
comma
id|entry-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|comxlapb_connected
r_static
r_void
id|comxlapb_connected
c_func
(paren
r_void
op_star
id|token
comma
r_int
id|reason
)paren
(brace
r_struct
id|comx_channel
op_star
id|ch
op_assign
id|token
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|comxdir
op_assign
id|ch-&gt;procdir-&gt;subdir
suffix:semicolon
r_if
c_cond
(paren
id|ch-&gt;debug_flags
op_amp
id|DEBUG_COMX_LAPB
)paren
(brace
id|comx_debug
c_func
(paren
id|ch-&gt;dev
comma
l_string|&quot;%s: lapb connected, reason: %d&bslash;n&quot;
comma
id|ch-&gt;dev-&gt;name
comma
id|reason
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ch-&gt;dev-&gt;type
op_eq
id|ARPHRD_X25
)paren
(brace
r_int
r_char
op_star
id|p
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
l_int|1
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;comxlapb: out of memory!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|p
op_assign
id|skb_put
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
op_star
id|p
op_assign
l_int|0x01
suffix:semicolon
singleline_comment|// link established
id|skb-&gt;dev
op_assign
id|ch-&gt;dev
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_X25
)paren
suffix:semicolon
id|skb-&gt;mac.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb-&gt;pkt_type
op_assign
id|PACKET_HOST
suffix:semicolon
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
id|ch-&gt;dev-&gt;last_rx
op_assign
id|jiffies
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
id|comxdir
suffix:semicolon
id|comxdir
op_assign
id|comxdir-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|comxdir-&gt;name
comma
id|FILENAME_MODE
)paren
op_eq
l_int|0
)paren
(brace
id|comxdir-&gt;mode
op_assign
id|S_IFREG
op_or
l_int|0444
suffix:semicolon
)brace
)brace
id|ch-&gt;line_status
op_or_assign
id|PROTO_UP
suffix:semicolon
id|comx_status
c_func
(paren
id|ch-&gt;dev
comma
id|ch-&gt;line_status
)paren
suffix:semicolon
)brace
DECL|function|comxlapb_disconnected
r_static
r_void
id|comxlapb_disconnected
c_func
(paren
r_void
op_star
id|token
comma
r_int
id|reason
)paren
(brace
r_struct
id|comx_channel
op_star
id|ch
op_assign
id|token
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|comxdir
op_assign
id|ch-&gt;procdir-&gt;subdir
suffix:semicolon
r_if
c_cond
(paren
id|ch-&gt;debug_flags
op_amp
id|DEBUG_COMX_LAPB
)paren
(brace
id|comx_debug
c_func
(paren
id|ch-&gt;dev
comma
l_string|&quot;%s: lapb disconnected, reason: %d&bslash;n&quot;
comma
id|ch-&gt;dev-&gt;name
comma
id|reason
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ch-&gt;dev-&gt;type
op_eq
id|ARPHRD_X25
)paren
(brace
r_int
r_char
op_star
id|p
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
l_int|1
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;comxlapb: out of memory!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|p
op_assign
id|skb_put
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
op_star
id|p
op_assign
l_int|0x02
suffix:semicolon
singleline_comment|// link disconnected
id|skb-&gt;dev
op_assign
id|ch-&gt;dev
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_X25
)paren
suffix:semicolon
id|skb-&gt;mac.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb-&gt;pkt_type
op_assign
id|PACKET_HOST
suffix:semicolon
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
id|ch-&gt;dev-&gt;last_rx
op_assign
id|jiffies
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
id|comxdir
suffix:semicolon
id|comxdir
op_assign
id|comxdir-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|comxdir-&gt;name
comma
id|FILENAME_MODE
)paren
op_eq
l_int|0
)paren
(brace
id|comxdir-&gt;mode
op_assign
id|S_IFREG
op_or
l_int|0644
suffix:semicolon
)brace
)brace
id|ch-&gt;line_status
op_and_assign
op_complement
id|PROTO_UP
suffix:semicolon
id|comx_status
c_func
(paren
id|ch-&gt;dev
comma
id|ch-&gt;line_status
)paren
suffix:semicolon
)brace
DECL|function|comxlapb_data_indication
r_static
r_int
id|comxlapb_data_indication
c_func
(paren
r_void
op_star
id|token
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|comx_channel
op_star
id|ch
op_assign
id|token
suffix:semicolon
r_if
c_cond
(paren
id|ch-&gt;dev-&gt;type
op_eq
id|ARPHRD_X25
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
r_if
c_cond
(paren
id|skb_cow
c_func
(paren
id|skb
comma
l_int|1
)paren
)paren
r_return
id|NET_RX_DROP
suffix:semicolon
id|skb-&gt;data
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
singleline_comment|// indicate data for X25
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_X25
)paren
suffix:semicolon
)brace
r_else
(brace
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_IP
)paren
suffix:semicolon
)brace
id|skb-&gt;dev
op_assign
id|ch-&gt;dev
suffix:semicolon
id|skb-&gt;mac.raw
op_assign
id|skb-&gt;data
suffix:semicolon
r_return
id|comx_rx
c_func
(paren
id|ch-&gt;dev
comma
id|skb
)paren
suffix:semicolon
)brace
DECL|function|comxlapb_data_transmit
r_static
r_void
id|comxlapb_data_transmit
c_func
(paren
r_void
op_star
id|token
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|comx_channel
op_star
id|ch
op_assign
id|token
suffix:semicolon
r_if
c_cond
(paren
id|ch-&gt;HW_send_packet
)paren
(brace
id|ch
op_member_access_from_pointer
id|HW_send_packet
c_func
(paren
id|ch-&gt;dev
comma
id|skb
)paren
suffix:semicolon
)brace
)brace
DECL|function|comxlapb_exit
r_static
r_int
id|comxlapb_exit
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|comx_channel
op_star
id|ch
op_assign
id|dev-&gt;priv
suffix:semicolon
id|dev-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;type
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;mtu
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;hard_header_len
op_assign
l_int|0
suffix:semicolon
id|ch-&gt;LINE_rx
op_assign
l_int|NULL
suffix:semicolon
id|ch-&gt;LINE_tx
op_assign
l_int|NULL
suffix:semicolon
id|ch-&gt;LINE_status
op_assign
l_int|NULL
suffix:semicolon
id|ch-&gt;LINE_open
op_assign
l_int|NULL
suffix:semicolon
id|ch-&gt;LINE_close
op_assign
l_int|NULL
suffix:semicolon
id|ch-&gt;LINE_xmit
op_assign
l_int|NULL
suffix:semicolon
id|ch-&gt;LINE_header
op_assign
l_int|NULL
suffix:semicolon
id|ch-&gt;LINE_statistics
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|ch-&gt;debug_flags
op_amp
id|DEBUG_COMX_LAPB
)paren
(brace
id|comx_debug
c_func
(paren
id|dev
comma
l_string|&quot;%s: unregistering lapb&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
id|lapb_unregister
c_func
(paren
id|dev-&gt;priv
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|FILENAME_T1
comma
id|ch-&gt;procdir
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|FILENAME_T2
comma
id|ch-&gt;procdir
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|FILENAME_N2
comma
id|ch-&gt;procdir
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|FILENAME_MODE
comma
id|ch-&gt;procdir
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|FILENAME_WINDOW
comma
id|ch-&gt;procdir
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|comxlapb_init
r_static
r_int
id|comxlapb_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|comx_channel
op_star
id|ch
op_assign
id|dev-&gt;priv
suffix:semicolon
r_struct
id|lapb_register_struct
id|lapbreg
suffix:semicolon
id|dev-&gt;mtu
op_assign
l_int|1500
suffix:semicolon
id|dev-&gt;hard_header_len
op_assign
l_int|4
suffix:semicolon
id|dev-&gt;addr_len
op_assign
l_int|0
suffix:semicolon
id|ch-&gt;LINE_rx
op_assign
id|comxlapb_rx
suffix:semicolon
id|ch-&gt;LINE_tx
op_assign
id|comxlapb_tx
suffix:semicolon
id|ch-&gt;LINE_status
op_assign
id|comxlapb_status
suffix:semicolon
id|ch-&gt;LINE_open
op_assign
id|comxlapb_open
suffix:semicolon
id|ch-&gt;LINE_close
op_assign
id|comxlapb_close
suffix:semicolon
id|ch-&gt;LINE_xmit
op_assign
id|comxlapb_xmit
suffix:semicolon
id|ch-&gt;LINE_header
op_assign
id|comxlapb_header
suffix:semicolon
id|ch-&gt;LINE_statistics
op_assign
id|comxlapb_statistics
suffix:semicolon
id|lapbreg.connect_confirmation
op_assign
id|comxlapb_connected
suffix:semicolon
id|lapbreg.connect_indication
op_assign
id|comxlapb_connected
suffix:semicolon
id|lapbreg.disconnect_confirmation
op_assign
id|comxlapb_disconnected
suffix:semicolon
id|lapbreg.disconnect_indication
op_assign
id|comxlapb_disconnected
suffix:semicolon
id|lapbreg.data_indication
op_assign
id|comxlapb_data_indication
suffix:semicolon
id|lapbreg.data_transmit
op_assign
id|comxlapb_data_transmit
suffix:semicolon
r_if
c_cond
(paren
id|lapb_register
c_func
(paren
id|dev
comma
id|dev-&gt;priv
comma
op_amp
id|lapbreg
)paren
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ch-&gt;debug_flags
op_amp
id|DEBUG_COMX_LAPB
)paren
(brace
id|comx_debug
c_func
(paren
id|dev
comma
l_string|&quot;%s: lapb registered&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|create_comxlapb_proc_entry
c_func
(paren
id|FILENAME_T1
comma
l_int|0644
comma
l_int|8
comma
id|ch-&gt;procdir
)paren
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|create_comxlapb_proc_entry
c_func
(paren
id|FILENAME_T2
comma
l_int|0644
comma
l_int|8
comma
id|ch-&gt;procdir
)paren
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|create_comxlapb_proc_entry
c_func
(paren
id|FILENAME_N2
comma
l_int|0644
comma
l_int|8
comma
id|ch-&gt;procdir
)paren
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|create_comxlapb_proc_entry
c_func
(paren
id|FILENAME_MODE
comma
l_int|0644
comma
l_int|14
comma
id|ch-&gt;procdir
)paren
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|create_comxlapb_proc_entry
c_func
(paren
id|FILENAME_WINDOW
comma
l_int|0644
comma
l_int|0
comma
id|ch-&gt;procdir
)paren
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|comxlapb_init_lapb
r_static
r_int
id|comxlapb_init_lapb
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|dev-&gt;flags
op_assign
id|IFF_POINTOPOINT
op_or
id|IFF_NOARP
op_or
id|IFF_MULTICAST
suffix:semicolon
id|dev-&gt;type
op_assign
id|ARPHRD_LAPB
suffix:semicolon
r_return
id|comxlapb_init
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|comxlapb_init_x25
r_static
r_int
id|comxlapb_init_x25
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|dev-&gt;flags
op_assign
id|IFF_NOARP
suffix:semicolon
id|dev-&gt;type
op_assign
id|ARPHRD_X25
suffix:semicolon
r_return
id|comxlapb_init
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|create_comxlapb_proc_entry
r_static
r_struct
id|proc_dir_entry
op_star
id|create_comxlapb_proc_entry
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|mode
comma
r_int
id|size
comma
r_struct
id|proc_dir_entry
op_star
id|dir
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|new_file
suffix:semicolon
r_if
c_cond
(paren
(paren
id|new_file
op_assign
id|create_proc_entry
c_func
(paren
id|name
comma
id|S_IFREG
op_or
id|mode
comma
id|dir
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|new_file-&gt;data
op_assign
(paren
r_void
op_star
)paren
id|new_file
suffix:semicolon
id|new_file-&gt;read_proc
op_assign
op_amp
id|comxlapb_read_proc
suffix:semicolon
id|new_file-&gt;write_proc
op_assign
op_amp
id|comxlapb_write_proc
suffix:semicolon
id|new_file-&gt;size
op_assign
id|size
suffix:semicolon
id|new_file-&gt;nlink
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|new_file
suffix:semicolon
)brace
DECL|variable|comxlapb_protocol
r_static
r_struct
id|comx_protocol
id|comxlapb_protocol
op_assign
(brace
l_string|&quot;lapb&quot;
comma
id|VERSION
comma
id|ARPHRD_LAPB
comma
id|comxlapb_init_lapb
comma
id|comxlapb_exit
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|comx25_protocol
r_static
r_struct
id|comx_protocol
id|comx25_protocol
op_assign
(brace
l_string|&quot;x25&quot;
comma
id|VERSION
comma
id|ARPHRD_X25
comma
id|comxlapb_init_x25
comma
id|comxlapb_exit
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|comx_proto_lapb_init
r_static
r_int
id|__init
id|comx_proto_lapb_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|comx_register_protocol
c_func
(paren
op_amp
id|comxlapb_protocol
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_return
id|ret
suffix:semicolon
)brace
r_return
id|comx_register_protocol
c_func
(paren
op_amp
id|comx25_protocol
)paren
suffix:semicolon
)brace
DECL|function|comx_proto_lapb_exit
r_static
r_void
id|__exit
id|comx_proto_lapb_exit
c_func
(paren
r_void
)paren
(brace
id|comx_unregister_protocol
c_func
(paren
id|comxlapb_protocol.name
)paren
suffix:semicolon
id|comx_unregister_protocol
c_func
(paren
id|comx25_protocol.name
)paren
suffix:semicolon
)brace
DECL|variable|comx_proto_lapb_init
id|module_init
c_func
(paren
id|comx_proto_lapb_init
)paren
suffix:semicolon
DECL|variable|comx_proto_lapb_exit
id|module_exit
c_func
(paren
id|comx_proto_lapb_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
