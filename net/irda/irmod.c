multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irmod.c&n; * Version:       0.9&n; * Description:   IrDA stack main entry points&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Mon Dec 15 13:55:39 1997&n; * Modified at:   Wed Jan  5 15:12:41 2000&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1997, 1999-2000 Dag Brattli, All Rights Reserved.&n; *     Copyright (c) 2000-2004 Jean Tourrilhes &lt;jt@hpl.hp.com&gt;&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
multiline_comment|/*&n; * This file contains the main entry points of the IrDA stack.&n; * They are in this file and not af_irda.c because some developpers&n; * are using the IrDA stack without the socket API (compiling out&n; * af_irda.c).&n; * Jean II&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irmod.h&gt;&t;&t;/* notify_t */
macro_line|#include &lt;net/irda/irlap.h&gt;&t;&t;/* irlap_init */
macro_line|#include &lt;net/irda/irlmp.h&gt;&t;&t;/* irlmp_init */
macro_line|#include &lt;net/irda/iriap.h&gt;&t;&t;/* iriap_init */
macro_line|#include &lt;net/irda/irttp.h&gt;&t;&t;/* irttp_init */
macro_line|#include &lt;net/irda/irda_device.h&gt;&t;/* irda_device_init */
multiline_comment|/* irproc.c */
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
multiline_comment|/* irsysctl.c */
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
multiline_comment|/* af_irda.c */
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
multiline_comment|/* irlap_frame.c */
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
multiline_comment|/*&n; * Module parameters&n; */
macro_line|#ifdef CONFIG_IRDA_DEBUG
DECL|variable|irda_debug
r_int
r_int
id|irda_debug
op_assign
id|IRDA_DEBUG_LEVEL
suffix:semicolon
id|module_param_named
c_func
(paren
id|debug
comma
id|irda_debug
comma
id|uint
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|debug
comma
l_string|&quot;IRDA debugging level&quot;
)paren
suffix:semicolon
DECL|variable|irda_debug
id|EXPORT_SYMBOL
c_func
(paren
id|irda_debug
)paren
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
DECL|variable|irda_notify_init
id|EXPORT_SYMBOL
c_func
(paren
id|irda_notify_init
)paren
suffix:semicolon
multiline_comment|/*&n; * Function irda_init (void)&n; *&n; *  Protocol stack initialisation entry point.&n; *  Initialise the various components of the IrDA stack&n; */
DECL|function|irda_init
r_static
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
r_static
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
DECL|variable|PF_IRDA
id|MODULE_ALIAS_NETPROTO
c_func
(paren
id|PF_IRDA
)paren
suffix:semicolon
eof
