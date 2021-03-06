multiline_comment|/*======================================================================&n;&n;    A driver for Adaptec AHA152X-compatible PCMCIA SCSI cards.&n;&n;    This driver supports the Adaptec AHA-1460, the New Media Bus&n;    Toaster, and the New Media Toast &amp; Jam.&n;    &n;    aha152x_cs.c 1.54 2000/06/12 21:27:25&n;&n;    The contents of this file are subject to the Mozilla Public&n;    License Version 1.1 (the &quot;License&quot;); you may not use this file&n;    except in compliance with the License. You may obtain a copy of&n;    the License at http://www.mozilla.org/MPL/&n;&n;    Software distributed under the License is distributed on an &quot;AS&n;    IS&quot; basis, WITHOUT WARRANTY OF ANY KIND, either express or&n;    implied. See the License for the specific language governing&n;    rights and limitations under the License.&n;&n;    The initial developer of the original code is David A. Hinds&n;    &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n;    are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n;&n;    Alternatively, the contents of this file may be used under the&n;    terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in which&n;    case the provisions of the GPL are applicable instead of the&n;    above.  If you wish to allow the use of your version of this file&n;    only under the terms of the GPL and not to allow others to use&n;    your version of this file under the MPL, indicate your decision&n;    by deleting the provisions above and replace them with the notice&n;    and other provisions required by the GPL.  If you do not delete&n;    the provisions above, a recipient may use your version of this&n;    file under either the MPL or the GPL.&n;    &n;======================================================================*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;scsi/scsi.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;scsi/scsi_ioctl.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &quot;aha152x.h&quot;
macro_line|#include &lt;pcmcia/version.h&gt;
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &lt;pcmcia/ds.h&gt;
macro_line|#ifdef PCMCIA_DEBUG
DECL|variable|pc_debug
r_static
r_int
id|pc_debug
op_assign
id|PCMCIA_DEBUG
suffix:semicolon
id|module_param
c_func
(paren
id|pc_debug
comma
r_int
comma
l_int|0644
)paren
suffix:semicolon
DECL|macro|DEBUG
mdefine_line|#define DEBUG(n, args...) if (pc_debug&gt;(n)) printk(KERN_DEBUG args)
DECL|variable|version
r_static
r_char
op_star
id|version
op_assign
l_string|&quot;aha152x_cs.c 1.54 2000/06/12 21:27:25 (David Hinds)&quot;
suffix:semicolon
macro_line|#else
DECL|macro|DEBUG
mdefine_line|#define DEBUG(n, args...)
macro_line|#endif
multiline_comment|/*====================================================================*/
multiline_comment|/* Parameters that can be set with &squot;insmod&squot; */
multiline_comment|/* SCSI bus setup options */
DECL|variable|host_id
r_static
r_int
id|host_id
op_assign
l_int|7
suffix:semicolon
DECL|variable|reconnect
r_static
r_int
id|reconnect
op_assign
l_int|1
suffix:semicolon
DECL|variable|parity
r_static
r_int
id|parity
op_assign
l_int|1
suffix:semicolon
DECL|variable|synchronous
r_static
r_int
id|synchronous
op_assign
l_int|1
suffix:semicolon
DECL|variable|reset_delay
r_static
r_int
id|reset_delay
op_assign
l_int|100
suffix:semicolon
DECL|variable|ext_trans
r_static
r_int
id|ext_trans
op_assign
l_int|0
suffix:semicolon
id|module_param
c_func
(paren
id|host_id
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|reconnect
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|parity
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|synchronous
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|reset_delay
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|ext_trans
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;Dual MPL/GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*====================================================================*/
DECL|struct|scsi_info_t
r_typedef
r_struct
id|scsi_info_t
(brace
DECL|member|link
id|dev_link_t
id|link
suffix:semicolon
DECL|member|node
id|dev_node_t
id|node
suffix:semicolon
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
DECL|typedef|scsi_info_t
)brace
id|scsi_info_t
suffix:semicolon
r_static
r_void
id|aha152x_release_cs
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
suffix:semicolon
r_static
r_int
id|aha152x_event
c_func
(paren
id|event_t
id|event
comma
r_int
id|priority
comma
id|event_callback_args_t
op_star
id|args
)paren
suffix:semicolon
r_static
id|dev_link_t
op_star
id|aha152x_attach
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|aha152x_detach
c_func
(paren
id|dev_link_t
op_star
)paren
suffix:semicolon
DECL|variable|dev_list
r_static
id|dev_link_t
op_star
id|dev_list
suffix:semicolon
DECL|variable|dev_info
r_static
id|dev_info_t
id|dev_info
op_assign
l_string|&quot;aha152x_cs&quot;
suffix:semicolon
DECL|function|aha152x_attach
r_static
id|dev_link_t
op_star
id|aha152x_attach
c_func
(paren
r_void
)paren
(brace
id|scsi_info_t
op_star
id|info
suffix:semicolon
id|client_reg_t
id|client_reg
suffix:semicolon
id|dev_link_t
op_star
id|link
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;aha152x_attach()&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Create new SCSI device */
id|info
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|info
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|info
)paren
)paren
suffix:semicolon
id|link
op_assign
op_amp
id|info-&gt;link
suffix:semicolon
id|link-&gt;priv
op_assign
id|info
suffix:semicolon
id|link-&gt;io.NumPorts1
op_assign
l_int|0x20
suffix:semicolon
id|link-&gt;io.Attributes1
op_assign
id|IO_DATA_PATH_WIDTH_AUTO
suffix:semicolon
id|link-&gt;io.IOAddrLines
op_assign
l_int|10
suffix:semicolon
id|link-&gt;irq.Attributes
op_assign
id|IRQ_TYPE_EXCLUSIVE
suffix:semicolon
id|link-&gt;irq.IRQInfo1
op_assign
id|IRQ_LEVEL_ID
suffix:semicolon
id|link-&gt;conf.Attributes
op_assign
id|CONF_ENABLE_IRQ
suffix:semicolon
id|link-&gt;conf.Vcc
op_assign
l_int|50
suffix:semicolon
id|link-&gt;conf.IntType
op_assign
id|INT_MEMORY_AND_IO
suffix:semicolon
id|link-&gt;conf.Present
op_assign
id|PRESENT_OPTION
suffix:semicolon
multiline_comment|/* Register with Card Services */
id|link-&gt;next
op_assign
id|dev_list
suffix:semicolon
id|dev_list
op_assign
id|link
suffix:semicolon
id|client_reg.dev_info
op_assign
op_amp
id|dev_info
suffix:semicolon
id|client_reg.event_handler
op_assign
op_amp
id|aha152x_event
suffix:semicolon
id|client_reg.EventMask
op_assign
id|CS_EVENT_RESET_REQUEST
op_or
id|CS_EVENT_CARD_RESET
op_or
id|CS_EVENT_CARD_INSERTION
op_or
id|CS_EVENT_CARD_REMOVAL
op_or
id|CS_EVENT_PM_SUSPEND
op_or
id|CS_EVENT_PM_RESUME
suffix:semicolon
id|client_reg.Version
op_assign
l_int|0x0210
suffix:semicolon
id|client_reg.event_callback_args.client_data
op_assign
id|link
suffix:semicolon
id|ret
op_assign
id|pcmcia_register_client
c_func
(paren
op_amp
id|link-&gt;handle
comma
op_amp
id|client_reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
(brace
id|cs_error
c_func
(paren
id|link-&gt;handle
comma
id|RegisterClient
comma
id|ret
)paren
suffix:semicolon
id|aha152x_detach
c_func
(paren
id|link
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|link
suffix:semicolon
)brace
multiline_comment|/* aha152x_attach */
multiline_comment|/*====================================================================*/
DECL|function|aha152x_detach
r_static
r_void
id|aha152x_detach
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
(brace
id|dev_link_t
op_star
op_star
id|linkp
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;aha152x_detach(0x%p)&bslash;n&quot;
comma
id|link
)paren
suffix:semicolon
multiline_comment|/* Locate device structure */
r_for
c_loop
(paren
id|linkp
op_assign
op_amp
id|dev_list
suffix:semicolon
op_star
id|linkp
suffix:semicolon
id|linkp
op_assign
op_amp
(paren
op_star
id|linkp
)paren
op_member_access_from_pointer
id|next
)paren
r_if
c_cond
(paren
op_star
id|linkp
op_eq
id|link
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_star
id|linkp
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_CONFIG
)paren
id|aha152x_release_cs
c_func
(paren
id|link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;handle
)paren
id|pcmcia_deregister_client
c_func
(paren
id|link-&gt;handle
)paren
suffix:semicolon
multiline_comment|/* Unlink device structure, free bits */
op_star
id|linkp
op_assign
id|link-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|link-&gt;priv
)paren
suffix:semicolon
)brace
multiline_comment|/* aha152x_detach */
multiline_comment|/*====================================================================*/
DECL|macro|CS_CHECK
mdefine_line|#define CS_CHECK(fn, ret) &bslash;&n;do { last_fn = (fn); if ((last_ret = (ret)) != 0) goto cs_failed; } while (0)
DECL|function|aha152x_config_cs
r_static
r_void
id|aha152x_config_cs
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
(brace
id|client_handle_t
id|handle
op_assign
id|link-&gt;handle
suffix:semicolon
id|scsi_info_t
op_star
id|info
op_assign
id|link-&gt;priv
suffix:semicolon
r_struct
id|aha152x_setup
id|s
suffix:semicolon
id|tuple_t
id|tuple
suffix:semicolon
id|cisparse_t
id|parse
suffix:semicolon
r_int
id|i
comma
id|last_ret
comma
id|last_fn
suffix:semicolon
id|u_char
id|tuple_data
(braket
l_int|64
)braket
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;aha152x_config(0x%p)&bslash;n&quot;
comma
id|link
)paren
suffix:semicolon
id|tuple.DesiredTuple
op_assign
id|CISTPL_CONFIG
suffix:semicolon
id|tuple.TupleData
op_assign
id|tuple_data
suffix:semicolon
id|tuple.TupleDataMax
op_assign
l_int|64
suffix:semicolon
id|tuple.TupleOffset
op_assign
l_int|0
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|GetFirstTuple
comma
id|pcmcia_get_first_tuple
c_func
(paren
id|handle
comma
op_amp
id|tuple
)paren
)paren
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|GetTupleData
comma
id|pcmcia_get_tuple_data
c_func
(paren
id|handle
comma
op_amp
id|tuple
)paren
)paren
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|ParseTuple
comma
id|pcmcia_parse_tuple
c_func
(paren
id|handle
comma
op_amp
id|tuple
comma
op_amp
id|parse
)paren
)paren
suffix:semicolon
id|link-&gt;conf.ConfigBase
op_assign
id|parse.config.base
suffix:semicolon
multiline_comment|/* Configure card */
id|link-&gt;state
op_or_assign
id|DEV_CONFIG
suffix:semicolon
id|tuple.DesiredTuple
op_assign
id|CISTPL_CFTABLE_ENTRY
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|GetFirstTuple
comma
id|pcmcia_get_first_tuple
c_func
(paren
id|handle
comma
op_amp
id|tuple
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|pcmcia_get_tuple_data
c_func
(paren
id|handle
comma
op_amp
id|tuple
)paren
op_ne
l_int|0
op_logical_or
id|pcmcia_parse_tuple
c_func
(paren
id|handle
comma
op_amp
id|tuple
comma
op_amp
id|parse
)paren
op_ne
l_int|0
)paren
r_goto
id|next_entry
suffix:semicolon
multiline_comment|/* For New Media T&amp;J, look for a SCSI window */
r_if
c_cond
(paren
id|parse.cftable_entry.io.win
(braket
l_int|0
)braket
dot
id|len
op_ge
l_int|0x20
)paren
id|link-&gt;io.BasePort1
op_assign
id|parse.cftable_entry.io.win
(braket
l_int|0
)braket
dot
id|base
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|parse.cftable_entry.io.nwin
OG
l_int|1
)paren
op_logical_and
(paren
id|parse.cftable_entry.io.win
(braket
l_int|1
)braket
dot
id|len
op_ge
l_int|0x20
)paren
)paren
id|link-&gt;io.BasePort1
op_assign
id|parse.cftable_entry.io.win
(braket
l_int|1
)braket
dot
id|base
suffix:semicolon
r_if
c_cond
(paren
(paren
id|parse.cftable_entry.io.nwin
OG
l_int|0
)paren
op_logical_and
(paren
id|link-&gt;io.BasePort1
OL
l_int|0xffff
)paren
)paren
(brace
id|link-&gt;conf.ConfigIndex
op_assign
id|parse.cftable_entry.index
suffix:semicolon
id|i
op_assign
id|pcmcia_request_io
c_func
(paren
id|handle
comma
op_amp
id|link-&gt;io
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|CS_SUCCESS
)paren
r_break
suffix:semicolon
)brace
id|next_entry
suffix:colon
id|CS_CHECK
c_func
(paren
id|GetNextTuple
comma
id|pcmcia_get_next_tuple
c_func
(paren
id|handle
comma
op_amp
id|tuple
)paren
)paren
suffix:semicolon
)brace
id|CS_CHECK
c_func
(paren
id|RequestIRQ
comma
id|pcmcia_request_irq
c_func
(paren
id|handle
comma
op_amp
id|link-&gt;irq
)paren
)paren
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|RequestConfiguration
comma
id|pcmcia_request_configuration
c_func
(paren
id|handle
comma
op_amp
id|link-&gt;conf
)paren
)paren
suffix:semicolon
multiline_comment|/* Set configuration options for the aha152x driver */
id|memset
c_func
(paren
op_amp
id|s
comma
l_int|0
comma
r_sizeof
(paren
id|s
)paren
)paren
suffix:semicolon
id|s.conf
op_assign
l_string|&quot;PCMCIA setup&quot;
suffix:semicolon
id|s.io_port
op_assign
id|link-&gt;io.BasePort1
suffix:semicolon
id|s.irq
op_assign
id|link-&gt;irq.AssignedIRQ
suffix:semicolon
id|s.scsiid
op_assign
id|host_id
suffix:semicolon
id|s.reconnect
op_assign
id|reconnect
suffix:semicolon
id|s.parity
op_assign
id|parity
suffix:semicolon
id|s.synchronous
op_assign
id|synchronous
suffix:semicolon
id|s.delay
op_assign
id|reset_delay
suffix:semicolon
r_if
c_cond
(paren
id|ext_trans
)paren
id|s.ext_trans
op_assign
id|ext_trans
suffix:semicolon
id|host
op_assign
id|aha152x_probe_one
c_func
(paren
op_amp
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|host
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;aha152x_cs: no SCSI devices found&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cs_failed
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|info-&gt;node.dev_name
comma
l_string|&quot;scsi%d&quot;
comma
id|host-&gt;host_no
)paren
suffix:semicolon
id|link-&gt;dev
op_assign
op_amp
id|info-&gt;node
suffix:semicolon
id|info-&gt;host
op_assign
id|host
suffix:semicolon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_CONFIG_PENDING
suffix:semicolon
r_return
suffix:semicolon
id|cs_failed
suffix:colon
id|cs_error
c_func
(paren
id|link-&gt;handle
comma
id|last_fn
comma
id|last_ret
)paren
suffix:semicolon
id|aha152x_release_cs
c_func
(paren
id|link
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|aha152x_release_cs
r_static
r_void
id|aha152x_release_cs
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
(brace
id|scsi_info_t
op_star
id|info
op_assign
id|link-&gt;priv
suffix:semicolon
id|aha152x_release
c_func
(paren
id|info-&gt;host
)paren
suffix:semicolon
id|link-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
id|pcmcia_release_configuration
c_func
(paren
id|link-&gt;handle
)paren
suffix:semicolon
id|pcmcia_release_io
c_func
(paren
id|link-&gt;handle
comma
op_amp
id|link-&gt;io
)paren
suffix:semicolon
id|pcmcia_release_irq
c_func
(paren
id|link-&gt;handle
comma
op_amp
id|link-&gt;irq
)paren
suffix:semicolon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_CONFIG
suffix:semicolon
)brace
DECL|function|aha152x_event
r_static
r_int
id|aha152x_event
c_func
(paren
id|event_t
id|event
comma
r_int
id|priority
comma
id|event_callback_args_t
op_star
id|args
)paren
(brace
id|dev_link_t
op_star
id|link
op_assign
id|args-&gt;client_data
suffix:semicolon
id|scsi_info_t
op_star
id|info
op_assign
id|link-&gt;priv
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;aha152x_event(0x%06x)&bslash;n&quot;
comma
id|event
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|CS_EVENT_CARD_REMOVAL
suffix:colon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_PRESENT
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_CONFIG
)paren
id|aha152x_release_cs
c_func
(paren
id|link
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS_EVENT_CARD_INSERTION
suffix:colon
id|link-&gt;state
op_or_assign
id|DEV_PRESENT
op_or
id|DEV_CONFIG_PENDING
suffix:semicolon
id|aha152x_config_cs
c_func
(paren
id|link
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS_EVENT_PM_SUSPEND
suffix:colon
id|link-&gt;state
op_or_assign
id|DEV_SUSPEND
suffix:semicolon
multiline_comment|/* Fall through... */
r_case
id|CS_EVENT_RESET_PHYSICAL
suffix:colon
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_CONFIG
)paren
id|pcmcia_release_configuration
c_func
(paren
id|link-&gt;handle
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS_EVENT_PM_RESUME
suffix:colon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_SUSPEND
suffix:semicolon
multiline_comment|/* Fall through... */
r_case
id|CS_EVENT_CARD_RESET
suffix:colon
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_CONFIG
)paren
(brace
id|Scsi_Cmnd
id|tmp
suffix:semicolon
id|pcmcia_request_configuration
c_func
(paren
id|link-&gt;handle
comma
op_amp
id|link-&gt;conf
)paren
suffix:semicolon
id|tmp.device-&gt;host
op_assign
id|info-&gt;host
suffix:semicolon
id|aha152x_host_reset
c_func
(paren
op_amp
id|tmp
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|aha152x_cs_driver
r_static
r_struct
id|pcmcia_driver
id|aha152x_cs_driver
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|drv
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;aha152x_cs&quot;
comma
)brace
comma
dot
id|attach
op_assign
id|aha152x_attach
comma
dot
id|detach
op_assign
id|aha152x_detach
comma
)brace
suffix:semicolon
DECL|function|init_aha152x_cs
r_static
r_int
id|__init
id|init_aha152x_cs
c_func
(paren
r_void
)paren
(brace
r_return
id|pcmcia_register_driver
c_func
(paren
op_amp
id|aha152x_cs_driver
)paren
suffix:semicolon
)brace
DECL|function|exit_aha152x_cs
r_static
r_void
id|__exit
id|exit_aha152x_cs
c_func
(paren
r_void
)paren
(brace
id|pcmcia_unregister_driver
c_func
(paren
op_amp
id|aha152x_cs_driver
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|dev_list
op_ne
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|init_aha152x_cs
id|module_init
c_func
(paren
id|init_aha152x_cs
)paren
suffix:semicolon
DECL|variable|exit_aha152x_cs
id|module_exit
c_func
(paren
id|exit_aha152x_cs
)paren
suffix:semicolon
eof
