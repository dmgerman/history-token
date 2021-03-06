multiline_comment|/* -*- c-basic-offset: 8 -*-&n; *&n; * cmp.c - Connection Management Procedures&n; * Copyright (C) 2001 Kristian H&#xfffd;gsberg&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software Foundation,&n; * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; */
multiline_comment|/* TODO&n; * ----&n; *&n; * - Implement IEC61883-1 output plugs and connection management.&n; *   This should probably be part of the general subsystem, as it could&n; *   be shared with dv1394.&n; *&n; * - Add IEC61883 unit directory when loading this module.  This&n; *   requires a run-time changeable config rom.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;highlevel.h&quot;
macro_line|#include &quot;ieee1394.h&quot;
macro_line|#include &quot;ieee1394_core.h&quot;
macro_line|#include &quot;cmp.h&quot;
DECL|struct|plug
r_struct
id|plug
(brace
r_union
(brace
DECL|member|pcr
r_struct
id|cmp_pcr
id|pcr
suffix:semicolon
DECL|member|quadlet
id|quadlet_t
id|quadlet
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|update
r_void
(paren
op_star
id|update
)paren
(paren
r_struct
id|cmp_pcr
op_star
id|plug
comma
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cmp_host
r_struct
id|cmp_host
(brace
DECL|member|host
r_struct
id|hpsb_host
op_star
id|host
suffix:semicolon
r_union
(brace
DECL|member|ompr
r_struct
id|cmp_mpr
id|ompr
suffix:semicolon
DECL|member|ompr_quadlet
id|quadlet_t
id|ompr_quadlet
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|opcr
r_struct
id|plug
id|opcr
(braket
l_int|2
)braket
suffix:semicolon
r_union
(brace
DECL|member|impr
r_struct
id|cmp_mpr
id|impr
suffix:semicolon
DECL|member|impr_quadlet
id|quadlet_t
id|impr_quadlet
suffix:semicolon
DECL|member|v
)brace
id|v
suffix:semicolon
DECL|member|ipcr
r_struct
id|plug
id|ipcr
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|CMP_P2P_CONNECTION
id|CMP_P2P_CONNECTION
comma
DECL|enumerator|CMP_BC_CONNECTION
id|CMP_BC_CONNECTION
)brace
suffix:semicolon
DECL|macro|CSR_PCR_MAP
mdefine_line|#define CSR_PCR_MAP      0x900
DECL|macro|CSR_PCR_MAP_END
mdefine_line|#define CSR_PCR_MAP_END  0x9fc
DECL|variable|cmp_highlevel
r_static
r_struct
id|hpsb_highlevel
id|cmp_highlevel
suffix:semicolon
r_static
r_void
id|cmp_add_host
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
suffix:semicolon
r_static
r_void
id|cmp_host_reset
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
suffix:semicolon
r_static
r_int
id|pcr_read
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
id|nodeid
comma
id|quadlet_t
op_star
id|buf
comma
id|u64
id|addr
comma
r_int
id|length
comma
id|u16
id|flags
)paren
suffix:semicolon
r_static
r_int
id|pcr_lock
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
id|nodeid
comma
id|quadlet_t
op_star
id|store
comma
id|u64
id|addr
comma
id|quadlet_t
id|data
comma
id|quadlet_t
id|arg
comma
r_int
id|extcode
comma
id|u16
id|flags
)paren
suffix:semicolon
DECL|variable|cmp_highlevel
r_static
r_struct
id|hpsb_highlevel
id|cmp_highlevel
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;cmp&quot;
comma
dot
id|add_host
op_assign
id|cmp_add_host
comma
dot
id|host_reset
op_assign
id|cmp_host_reset
comma
)brace
suffix:semicolon
DECL|variable|pcr_ops
r_static
r_struct
id|hpsb_address_ops
id|pcr_ops
op_assign
(brace
dot
id|read
op_assign
id|pcr_read
comma
dot
id|lock
op_assign
id|pcr_lock
comma
)brace
suffix:semicolon
r_struct
id|cmp_pcr
op_star
DECL|function|cmp_register_opcr
id|cmp_register_opcr
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
id|opcr_number
comma
r_int
id|payload
comma
r_void
(paren
op_star
id|update
)paren
(paren
r_struct
id|cmp_pcr
op_star
id|pcr
comma
r_void
op_star
id|data
)paren
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|cmp_host
op_star
id|ch
suffix:semicolon
r_struct
id|plug
op_star
id|plug
suffix:semicolon
id|ch
op_assign
id|hpsb_get_hostinfo
c_func
(paren
op_amp
id|cmp_highlevel
comma
id|host
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opcr_number
op_ge
id|ch-&gt;u.ompr.nplugs
op_logical_or
id|ch-&gt;opcr
(braket
id|opcr_number
)braket
dot
id|update
op_ne
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|plug
op_assign
op_amp
id|ch-&gt;opcr
(braket
id|opcr_number
)braket
suffix:semicolon
id|plug-&gt;u.pcr.online
op_assign
l_int|1
suffix:semicolon
id|plug-&gt;u.pcr.bcast_count
op_assign
l_int|0
suffix:semicolon
id|plug-&gt;u.pcr.p2p_count
op_assign
l_int|0
suffix:semicolon
id|plug-&gt;u.pcr.overhead
op_assign
l_int|0
suffix:semicolon
id|plug-&gt;u.pcr.payload
op_assign
id|payload
suffix:semicolon
id|plug-&gt;update
op_assign
id|update
suffix:semicolon
id|plug-&gt;data
op_assign
id|data
suffix:semicolon
r_return
op_amp
id|plug-&gt;u.pcr
suffix:semicolon
)brace
DECL|function|cmp_unregister_opcr
r_void
id|cmp_unregister_opcr
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_struct
id|cmp_pcr
op_star
id|opcr
)paren
(brace
r_struct
id|cmp_host
op_star
id|ch
suffix:semicolon
r_struct
id|plug
op_star
id|plug
suffix:semicolon
id|ch
op_assign
id|hpsb_get_hostinfo
c_func
(paren
op_amp
id|cmp_highlevel
comma
id|host
)paren
suffix:semicolon
id|plug
op_assign
(paren
r_struct
id|plug
op_star
)paren
id|opcr
suffix:semicolon
r_if
c_cond
(paren
id|plug
op_minus
id|ch-&gt;opcr
op_ge
id|ch-&gt;u.ompr.nplugs
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|plug-&gt;u.pcr.online
op_assign
l_int|0
suffix:semicolon
id|plug-&gt;update
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|reset_plugs
r_static
r_void
id|reset_plugs
c_func
(paren
r_struct
id|cmp_host
op_star
id|ch
)paren
(brace
r_int
id|i
suffix:semicolon
id|ch-&gt;u.ompr.non_persistent_ext
op_assign
l_int|0xff
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ch-&gt;u.ompr.nplugs
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ch-&gt;opcr
(braket
id|i
)braket
dot
id|u.pcr.bcast_count
op_assign
l_int|0
suffix:semicolon
id|ch-&gt;opcr
(braket
id|i
)braket
dot
id|u.pcr.p2p_count
op_assign
l_int|0
suffix:semicolon
id|ch-&gt;opcr
(braket
id|i
)braket
dot
id|u.pcr.overhead
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|cmp_add_host
r_static
r_void
id|cmp_add_host
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
(brace
r_struct
id|cmp_host
op_star
id|ch
op_assign
id|hpsb_create_hostinfo
c_func
(paren
op_amp
id|cmp_highlevel
comma
id|host
comma
r_sizeof
(paren
op_star
id|ch
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
l_int|NULL
)paren
(brace
id|HPSB_ERR
c_func
(paren
l_string|&quot;Failed to allocate cmp_host&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|hpsb_register_addrspace
c_func
(paren
op_amp
id|cmp_highlevel
comma
id|host
comma
op_amp
id|pcr_ops
comma
id|CSR_REGISTER_BASE
op_plus
id|CSR_PCR_MAP
comma
id|CSR_REGISTER_BASE
op_plus
id|CSR_PCR_MAP_END
)paren
suffix:semicolon
id|ch-&gt;host
op_assign
id|host
suffix:semicolon
id|ch-&gt;u.ompr.rate
op_assign
id|IEEE1394_SPEED_100
suffix:semicolon
id|ch-&gt;u.ompr.bcast_channel_base
op_assign
l_int|63
suffix:semicolon
id|ch-&gt;u.ompr.nplugs
op_assign
l_int|2
suffix:semicolon
id|reset_plugs
c_func
(paren
id|ch
)paren
suffix:semicolon
)brace
DECL|function|cmp_host_reset
r_static
r_void
id|cmp_host_reset
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
(brace
r_struct
id|cmp_host
op_star
id|ch
suffix:semicolon
id|ch
op_assign
id|hpsb_get_hostinfo
c_func
(paren
op_amp
id|cmp_highlevel
comma
id|host
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
l_int|NULL
)paren
(brace
id|HPSB_ERR
c_func
(paren
l_string|&quot;cmp: Tried to reset unknown host&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|reset_plugs
c_func
(paren
id|ch
)paren
suffix:semicolon
)brace
DECL|function|pcr_read
r_static
r_int
id|pcr_read
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
id|nodeid
comma
id|quadlet_t
op_star
id|buf
comma
id|u64
id|addr
comma
r_int
id|length
comma
id|u16
id|flags
)paren
(brace
r_int
id|csraddr
op_assign
id|addr
op_minus
id|CSR_REGISTER_BASE
suffix:semicolon
r_int
id|plug
suffix:semicolon
r_struct
id|cmp_host
op_star
id|ch
suffix:semicolon
r_if
c_cond
(paren
id|length
op_ne
l_int|4
)paren
r_return
id|RCODE_TYPE_ERROR
suffix:semicolon
id|ch
op_assign
id|hpsb_get_hostinfo
c_func
(paren
op_amp
id|cmp_highlevel
comma
id|host
)paren
suffix:semicolon
r_if
c_cond
(paren
id|csraddr
op_eq
l_int|0x900
)paren
(brace
op_star
id|buf
op_assign
id|cpu_to_be32
c_func
(paren
id|ch-&gt;u.ompr_quadlet
)paren
suffix:semicolon
r_return
id|RCODE_COMPLETE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|csraddr
OL
l_int|0x904
op_plus
id|ch-&gt;u.ompr.nplugs
op_star
l_int|4
)paren
(brace
id|plug
op_assign
(paren
id|csraddr
op_minus
l_int|0x904
)paren
op_div
l_int|4
suffix:semicolon
op_star
id|buf
op_assign
id|cpu_to_be32
c_func
(paren
id|ch-&gt;opcr
(braket
id|plug
)braket
dot
id|u.quadlet
)paren
suffix:semicolon
r_return
id|RCODE_COMPLETE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|csraddr
OL
l_int|0x980
)paren
(brace
r_return
id|RCODE_ADDRESS_ERROR
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|csraddr
op_eq
l_int|0x980
)paren
(brace
op_star
id|buf
op_assign
id|cpu_to_be32
c_func
(paren
id|ch-&gt;v.impr_quadlet
)paren
suffix:semicolon
r_return
id|RCODE_COMPLETE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|csraddr
OL
l_int|0x984
op_plus
id|ch-&gt;v.impr.nplugs
op_star
l_int|4
)paren
(brace
id|plug
op_assign
(paren
id|csraddr
op_minus
l_int|0x984
)paren
op_div
l_int|4
suffix:semicolon
op_star
id|buf
op_assign
id|cpu_to_be32
c_func
(paren
id|ch-&gt;ipcr
(braket
id|plug
)braket
dot
id|u.quadlet
)paren
suffix:semicolon
r_return
id|RCODE_COMPLETE
suffix:semicolon
)brace
r_else
r_return
id|RCODE_ADDRESS_ERROR
suffix:semicolon
)brace
DECL|function|pcr_lock
r_static
r_int
id|pcr_lock
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
id|nodeid
comma
id|quadlet_t
op_star
id|store
comma
id|u64
id|addr
comma
id|quadlet_t
id|data
comma
id|quadlet_t
id|arg
comma
r_int
id|extcode
comma
id|u16
id|flags
)paren
(brace
r_int
id|csraddr
op_assign
id|addr
op_minus
id|CSR_REGISTER_BASE
suffix:semicolon
r_int
id|plug
suffix:semicolon
r_struct
id|cmp_host
op_star
id|ch
suffix:semicolon
id|ch
op_assign
id|hpsb_get_hostinfo
c_func
(paren
op_amp
id|cmp_highlevel
comma
id|host
)paren
suffix:semicolon
r_if
c_cond
(paren
id|extcode
op_ne
id|EXTCODE_COMPARE_SWAP
)paren
r_return
id|RCODE_TYPE_ERROR
suffix:semicolon
r_if
c_cond
(paren
id|csraddr
op_eq
l_int|0x900
)paren
(brace
multiline_comment|/* FIXME: Ignore writes to bits 30-31 and 0-7 */
op_star
id|store
op_assign
id|cpu_to_be32
c_func
(paren
id|ch-&gt;u.ompr_quadlet
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arg
op_eq
id|cpu_to_be32
c_func
(paren
id|ch-&gt;u.ompr_quadlet
)paren
)paren
id|ch-&gt;u.ompr_quadlet
op_assign
id|be32_to_cpu
c_func
(paren
id|data
)paren
suffix:semicolon
r_return
id|RCODE_COMPLETE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|csraddr
OL
l_int|0x904
op_plus
id|ch-&gt;u.ompr.nplugs
op_star
l_int|4
)paren
(brace
id|plug
op_assign
(paren
id|csraddr
op_minus
l_int|0x904
)paren
op_div
l_int|4
suffix:semicolon
op_star
id|store
op_assign
id|cpu_to_be32
c_func
(paren
id|ch-&gt;opcr
(braket
id|plug
)braket
dot
id|u.quadlet
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arg
op_eq
op_star
id|store
)paren
id|ch-&gt;opcr
(braket
id|plug
)braket
dot
id|u.quadlet
op_assign
id|be32_to_cpu
c_func
(paren
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|be32_to_cpu
c_func
(paren
op_star
id|store
)paren
op_ne
id|ch-&gt;opcr
(braket
id|plug
)braket
dot
id|u.quadlet
op_logical_and
id|ch-&gt;opcr
(braket
id|plug
)braket
dot
id|update
op_ne
l_int|NULL
)paren
id|ch-&gt;opcr
(braket
id|plug
)braket
dot
id|update
c_func
(paren
op_amp
id|ch-&gt;opcr
(braket
id|plug
)braket
dot
id|u.pcr
comma
id|ch-&gt;opcr
(braket
id|plug
)braket
dot
id|data
)paren
suffix:semicolon
r_return
id|RCODE_COMPLETE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|csraddr
OL
l_int|0x980
)paren
(brace
r_return
id|RCODE_ADDRESS_ERROR
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|csraddr
op_eq
l_int|0x980
)paren
(brace
multiline_comment|/* FIXME: Ignore writes to bits 24-31 and 0-7 */
op_star
id|store
op_assign
id|cpu_to_be32
c_func
(paren
id|ch-&gt;u.ompr_quadlet
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arg
op_eq
id|cpu_to_be32
c_func
(paren
id|ch-&gt;u.ompr_quadlet
)paren
)paren
id|ch-&gt;u.ompr_quadlet
op_assign
id|be32_to_cpu
c_func
(paren
id|data
)paren
suffix:semicolon
r_return
id|RCODE_COMPLETE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|csraddr
OL
l_int|0x984
op_plus
id|ch-&gt;v.impr.nplugs
op_star
l_int|4
)paren
(brace
id|plug
op_assign
(paren
id|csraddr
op_minus
l_int|0x984
)paren
op_div
l_int|4
suffix:semicolon
op_star
id|store
op_assign
id|cpu_to_be32
c_func
(paren
id|ch-&gt;ipcr
(braket
id|plug
)braket
dot
id|u.quadlet
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arg
op_eq
op_star
id|store
)paren
id|ch-&gt;ipcr
(braket
id|plug
)braket
dot
id|u.quadlet
op_assign
id|be32_to_cpu
c_func
(paren
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|be32_to_cpu
c_func
(paren
op_star
id|store
)paren
op_ne
id|ch-&gt;ipcr
(braket
id|plug
)braket
dot
id|u.quadlet
op_logical_and
id|ch-&gt;ipcr
(braket
id|plug
)braket
dot
id|update
op_ne
l_int|NULL
)paren
id|ch-&gt;ipcr
(braket
id|plug
)braket
dot
id|update
c_func
(paren
op_amp
id|ch-&gt;ipcr
(braket
id|plug
)braket
dot
id|u.pcr
comma
id|ch-&gt;ipcr
(braket
id|plug
)braket
dot
id|data
)paren
suffix:semicolon
r_return
id|RCODE_COMPLETE
suffix:semicolon
)brace
r_else
r_return
id|RCODE_ADDRESS_ERROR
suffix:semicolon
)brace
multiline_comment|/* Module interface */
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Kristian Hogsberg &lt;hogsberg@users.sf.net&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Connection Management Procedures (CMP)&quot;
)paren
suffix:semicolon
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;cmp&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|cmp_register_opcr
id|EXPORT_SYMBOL
c_func
(paren
id|cmp_register_opcr
)paren
suffix:semicolon
DECL|variable|cmp_unregister_opcr
id|EXPORT_SYMBOL
c_func
(paren
id|cmp_unregister_opcr
)paren
suffix:semicolon
DECL|function|cmp_init_module
r_static
r_int
id|__init
id|cmp_init_module
(paren
r_void
)paren
(brace
id|hpsb_register_highlevel
(paren
op_amp
id|cmp_highlevel
)paren
suffix:semicolon
id|HPSB_INFO
c_func
(paren
l_string|&quot;Loaded CMP driver&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmp_exit_module
r_static
r_void
id|__exit
id|cmp_exit_module
(paren
r_void
)paren
(brace
id|hpsb_unregister_highlevel
c_func
(paren
op_amp
id|cmp_highlevel
)paren
suffix:semicolon
id|HPSB_INFO
c_func
(paren
l_string|&quot;Unloaded CMP driver&quot;
)paren
suffix:semicolon
)brace
DECL|variable|cmp_init_module
id|module_init
c_func
(paren
id|cmp_init_module
)paren
suffix:semicolon
DECL|variable|cmp_exit_module
id|module_exit
c_func
(paren
id|cmp_exit_module
)paren
suffix:semicolon
eof
