multiline_comment|/*======================================================================&n;&n;    A driver for Future Domain-compatible PCMCIA SCSI cards&n;&n;    fdomain_cs.c 1.47 2001/10/13 00:08:52&n;&n;    The contents of this file are subject to the Mozilla Public&n;    License Version 1.1 (the &quot;License&quot;); you may not use this file&n;    except in compliance with the License. You may obtain a copy of&n;    the License at http://www.mozilla.org/MPL/&n;&n;    Software distributed under the License is distributed on an &quot;AS&n;    IS&quot; basis, WITHOUT WARRANTY OF ANY KIND, either express or&n;    implied. See the License for the specific language governing&n;    rights and limitations under the License.&n;&n;    The initial developer of the original code is David A. Hinds&n;    &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n;    are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n;&n;    Alternatively, the contents of this file may be used under the&n;    terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in&n;    which case the provisions of the GPL are applicable instead of the&n;    above.  If you wish to allow the use of your version of this file&n;    only under the terms of the GPL and not to allow others to use&n;    your version of this file under the MPL, indicate your decision&n;    by deleting the provisions above and replace them with the notice&n;    and other provisions required by the GPL.  If you do not delete&n;    the provisions above, a recipient may use your version of this&n;    file under either the MPL or the GPL.&n;    &n;======================================================================*/
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
macro_line|#include &quot;fdomain.h&quot;
macro_line|#include &lt;pcmcia/version.h&gt;
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &lt;pcmcia/ds.h&gt;
multiline_comment|/*====================================================================*/
multiline_comment|/* Module parameters */
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;David Hinds &lt;dahinds@users.sourceforge.net&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Future Domain PCMCIA SCSI driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;Dual MPL/GPL&quot;
)paren
suffix:semicolon
multiline_comment|/* Bit map of interrupts to choose from */
DECL|variable|irq_mask
r_static
r_int
id|irq_mask
op_assign
l_int|0xdeb8
suffix:semicolon
id|module_param
c_func
(paren
id|irq_mask
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
DECL|variable|irq_list
r_static
r_int
id|irq_list
(braket
l_int|4
)braket
op_assign
(brace
op_minus
l_int|1
)brace
suffix:semicolon
id|module_param_array
c_func
(paren
id|irq_list
comma
r_int
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
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
l_int|0
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
l_string|&quot;fdomain_cs.c 1.47 2001/10/13 00:08:52 (David Hinds)&quot;
suffix:semicolon
macro_line|#else
DECL|macro|DEBUG
mdefine_line|#define DEBUG(n, args...)
macro_line|#endif
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
id|fdomain_release
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
suffix:semicolon
r_static
r_int
id|fdomain_event
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
id|fdomain_attach
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|fdomain_detach
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
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|dev_info
r_static
id|dev_info_t
id|dev_info
op_assign
l_string|&quot;fdomain_cs&quot;
suffix:semicolon
DECL|function|fdomain_attach
r_static
id|dev_link_t
op_star
id|fdomain_attach
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
id|i
comma
id|ret
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;fdomain_attach()&bslash;n&quot;
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
l_int|0x10
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
id|IRQ_INFO2_VALID
op_or
id|IRQ_LEVEL_ID
suffix:semicolon
r_if
c_cond
(paren
id|irq_list
(braket
l_int|0
)braket
op_eq
op_minus
l_int|1
)paren
id|link-&gt;irq.IRQInfo2
op_assign
id|irq_mask
suffix:semicolon
r_else
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
id|link-&gt;irq.IRQInfo2
op_or_assign
l_int|1
op_lshift
id|irq_list
(braket
id|i
)braket
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
id|client_reg.Attributes
op_assign
id|INFO_IO_CLIENT
op_or
id|INFO_CARD_SHARE
suffix:semicolon
id|client_reg.event_handler
op_assign
op_amp
id|fdomain_event
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
id|fdomain_detach
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
multiline_comment|/* fdomain_attach */
multiline_comment|/*====================================================================*/
DECL|function|fdomain_detach
r_static
r_void
id|fdomain_detach
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
l_string|&quot;fdomain_detach(0x%p)&bslash;n&quot;
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
id|fdomain_release
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
multiline_comment|/* fdomain_detach */
multiline_comment|/*====================================================================*/
DECL|macro|CS_CHECK
mdefine_line|#define CS_CHECK(fn, ret) &bslash;&n;do { last_fn = (fn); if ((last_ret = (ret)) != 0) goto cs_failed; } while (0)
DECL|function|fdomain_config
r_static
r_void
id|fdomain_config
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
r_char
id|str
(braket
l_int|16
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
l_string|&quot;fdomain_config(0x%p)&bslash;n&quot;
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
id|link-&gt;conf.ConfigIndex
op_assign
id|parse.cftable_entry.index
suffix:semicolon
id|link-&gt;io.BasePort1
op_assign
id|parse.cftable_entry.io.win
(braket
l_int|0
)braket
dot
id|base
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
multiline_comment|/* A bad hack... */
id|release_region
c_func
(paren
id|link-&gt;io.BasePort1
comma
id|link-&gt;io.NumPorts1
)paren
suffix:semicolon
multiline_comment|/* Set configuration options for the fdomain driver */
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;%d,%d&quot;
comma
id|link-&gt;io.BasePort1
comma
id|link-&gt;irq.AssignedIRQ
)paren
suffix:semicolon
id|fdomain_setup
c_func
(paren
id|str
)paren
suffix:semicolon
id|host
op_assign
id|__fdomain_16x0_detect
c_func
(paren
op_amp
id|fdomain_driver_template
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;fdomain_cs: no SCSI devices found&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cs_failed
suffix:semicolon
)brace
id|scsi_add_host
c_func
(paren
id|host
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* XXX handle failure */
id|scsi_scan_host
c_func
(paren
id|host
)paren
suffix:semicolon
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
id|fdomain_release
c_func
(paren
id|link
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* fdomain_config */
multiline_comment|/*====================================================================*/
DECL|function|fdomain_release
r_static
r_void
id|fdomain_release
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
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;fdomain_release(0x%p)&bslash;n&quot;
comma
id|link
)paren
suffix:semicolon
id|scsi_remove_host
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
id|scsi_unregister
c_func
(paren
id|info-&gt;host
)paren
suffix:semicolon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_CONFIG
suffix:semicolon
)brace
multiline_comment|/*====================================================================*/
DECL|function|fdomain_event
r_static
r_int
id|fdomain_event
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
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;fdomain_event(0x%06x)&bslash;n&quot;
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
id|fdomain_release
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
id|fdomain_config
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
id|pcmcia_request_configuration
c_func
(paren
id|link-&gt;handle
comma
op_amp
id|link-&gt;conf
)paren
suffix:semicolon
id|fdomain_16x0_bus_reset
c_func
(paren
l_int|NULL
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
multiline_comment|/* fdomain_event */
DECL|variable|fdomain_cs_driver
r_static
r_struct
id|pcmcia_driver
id|fdomain_cs_driver
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
l_string|&quot;fdomain_cs&quot;
comma
)brace
comma
dot
id|attach
op_assign
id|fdomain_attach
comma
dot
id|detach
op_assign
id|fdomain_detach
comma
)brace
suffix:semicolon
DECL|function|init_fdomain_cs
r_static
r_int
id|__init
id|init_fdomain_cs
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
id|fdomain_cs_driver
)paren
suffix:semicolon
)brace
DECL|function|exit_fdomain_cs
r_static
r_void
id|__exit
id|exit_fdomain_cs
c_func
(paren
r_void
)paren
(brace
id|pcmcia_unregister_driver
c_func
(paren
op_amp
id|fdomain_cs_driver
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
DECL|variable|init_fdomain_cs
id|module_init
c_func
(paren
id|init_fdomain_cs
)paren
suffix:semicolon
DECL|variable|exit_fdomain_cs
id|module_exit
c_func
(paren
id|exit_fdomain_cs
)paren
suffix:semicolon
eof
