multiline_comment|/*======================================================================&n;&n;    A driver for the Qlogic SCSI card&n;&n;    qlogic_cs.c 1.79 2000/06/12 21:27:26&n;&n;    The contents of this file are subject to the Mozilla Public&n;    License Version 1.1 (the &quot;License&quot;); you may not use this file&n;    except in compliance with the License. You may obtain a copy of&n;    the License at http://www.mozilla.org/MPL/&n;&n;    Software distributed under the License is distributed on an &quot;AS&n;    IS&quot; basis, WITHOUT WARRANTY OF ANY KIND, either express or&n;    implied. See the License for the specific language governing&n;    rights and limitations under the License.&n;&n;    The initial developer of the original code is David A. Hinds&n;    &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n;    are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n;&n;    Alternatively, the contents of this file may be used under the&n;    terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in which&n;    case the provisions of the GPL are applicable instead of the&n;    above.  If you wish to allow the use of your version of this file&n;    only under the terms of the GPL and not to allow others to use&n;    your version of this file under the MPL, indicate your decision&n;    by deleting the provisions above and replace them with the notice&n;    and other provisions required by the GPL.  If you do not delete&n;    the provisions above, a recipient may use your version of this&n;    file under either the MPL or the GPL.&n;    &n;======================================================================*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;scsi/scsi.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;../drivers/scsi/scsi.h&gt;
macro_line|#include &lt;../drivers/scsi/hosts.h&gt;
macro_line|#include &lt;scsi/scsi_ioctl.h&gt;
macro_line|#include &lt;../drivers/scsi/qlogicfas.h&gt;
macro_line|#include &lt;pcmcia/version.h&gt;
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &lt;pcmcia/ds.h&gt;
macro_line|#include &lt;pcmcia/ciscode.h&gt;
r_extern
r_void
id|qlogicfas_preset
c_func
(paren
r_int
id|port
comma
r_int
id|irq
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
id|MODULE_PARM
c_func
(paren
id|pc_debug
comma
l_string|&quot;i&quot;
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
l_string|&quot;qlogic_cs.c 1.79-ac 2002/10/26 (David Hinds)&quot;
suffix:semicolon
macro_line|#else
DECL|macro|DEBUG
mdefine_line|#define DEBUG(n, args...)
macro_line|#endif
multiline_comment|/*====================================================================*/
multiline_comment|/* Parameters that can be set with &squot;insmod&squot; */
multiline_comment|/* Bit map of interrupts to choose from */
DECL|variable|irq_mask
r_static
r_int
r_int
id|irq_mask
op_assign
l_int|0xdeb8
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
id|MODULE_PARM
c_func
(paren
id|irq_mask
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|irq_list
comma
l_string|&quot;1-4i&quot;
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
DECL|member|manf_id
r_int
r_int
id|manf_id
suffix:semicolon
DECL|member|ndev
r_int
id|ndev
suffix:semicolon
DECL|member|node
id|dev_node_t
id|node
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|scsi_info_t
)brace
id|scsi_info_t
suffix:semicolon
r_static
r_void
id|qlogic_release
c_func
(paren
id|u_long
id|arg
)paren
suffix:semicolon
r_static
r_int
id|qlogic_event
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
id|qlogic_attach
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|qlogic_detach
c_func
(paren
id|dev_link_t
op_star
)paren
suffix:semicolon
multiline_comment|/* Import our driver template */
r_extern
id|Scsi_Host_Template
id|qlogicfas_driver_template
suffix:semicolon
DECL|macro|driver_template
mdefine_line|#define driver_template qlogicfas_driver_template
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
l_string|&quot;qlogic_cs&quot;
suffix:semicolon
multiline_comment|/*====================================================================*/
DECL|function|cs_error
r_static
r_void
id|cs_error
c_func
(paren
id|client_handle_t
id|handle
comma
r_int
id|func
comma
r_int
id|ret
)paren
(brace
id|error_info_t
id|err
op_assign
(brace
id|func
comma
id|ret
)brace
suffix:semicolon
id|CardServices
c_func
(paren
id|ReportError
comma
id|handle
comma
op_amp
id|err
)paren
suffix:semicolon
)brace
multiline_comment|/*====================================================================*/
DECL|function|qlogic_attach
r_static
id|dev_link_t
op_star
id|qlogic_attach
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
l_string|&quot;qlogic_attach()&bslash;n&quot;
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
id|link-&gt;release.function
op_assign
op_amp
id|qlogic_release
suffix:semicolon
id|link-&gt;release.data
op_assign
(paren
id|u_long
)paren
id|link
suffix:semicolon
id|link-&gt;io.NumPorts1
op_assign
l_int|16
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
id|qlogic_event
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
id|CardServices
c_func
(paren
id|RegisterClient
comma
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
id|qlogic_detach
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
multiline_comment|/* qlogic_attach */
multiline_comment|/*====================================================================*/
DECL|function|qlogic_detach
r_static
r_void
id|qlogic_detach
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
l_string|&quot;qlogic_detach(0x%p)&bslash;n&quot;
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
id|del_timer_sync
c_func
(paren
op_amp
id|link-&gt;release
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_CONFIG
)paren
(brace
id|qlogic_release
c_func
(paren
(paren
id|u_long
)paren
id|link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_STALE_CONFIG
)paren
(brace
id|link-&gt;state
op_or_assign
id|DEV_STALE_LINK
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|link-&gt;handle
)paren
id|CardServices
c_func
(paren
id|DeregisterClient
comma
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
multiline_comment|/* qlogic_detach */
multiline_comment|/*====================================================================*/
DECL|macro|CS_CHECK
mdefine_line|#define CS_CHECK(fn, args...) &bslash;&n;while ((last_ret=CardServices(last_fn=(fn), args))!=0) goto cs_failed
DECL|macro|CFG_CHECK
mdefine_line|#define CFG_CHECK(fn, args...) &bslash;&n;if (CardServices(fn, args) != 0) goto next_entry
DECL|function|qlogic_config
r_static
r_void
id|qlogic_config
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
r_int
r_int
id|tuple_data
(braket
l_int|32
)braket
suffix:semicolon
id|Scsi_Device
op_star
id|dev
suffix:semicolon
id|dev_node_t
op_star
op_star
id|tail
comma
op_star
id|node
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
l_string|&quot;qlogic_config(0x%p)&bslash;n&quot;
comma
id|link
)paren
suffix:semicolon
id|tuple.TupleData
op_assign
(paren
id|cisdata_t
op_star
)paren
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
id|tuple.DesiredTuple
op_assign
id|CISTPL_CONFIG
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|GetFirstTuple
comma
id|handle
comma
op_amp
id|tuple
)paren
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|GetTupleData
comma
id|handle
comma
op_amp
id|tuple
)paren
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|ParseTuple
comma
id|handle
comma
op_amp
id|tuple
comma
op_amp
id|parse
)paren
suffix:semicolon
id|link-&gt;conf.ConfigBase
op_assign
id|parse.config.base
suffix:semicolon
id|tuple.DesiredTuple
op_assign
id|CISTPL_MANFID
suffix:semicolon
r_if
c_cond
(paren
(paren
id|CardServices
c_func
(paren
id|GetFirstTuple
comma
id|handle
comma
op_amp
id|tuple
)paren
op_eq
id|CS_SUCCESS
)paren
op_logical_and
(paren
id|CardServices
c_func
(paren
id|GetTupleData
comma
id|handle
comma
op_amp
id|tuple
)paren
op_eq
id|CS_SUCCESS
)paren
)paren
id|info-&gt;manf_id
op_assign
id|le16_to_cpu
c_func
(paren
id|tuple.TupleData
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/* Configure card */
id|driver_template.module
op_assign
op_amp
id|__this_module
suffix:semicolon
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
id|handle
comma
op_amp
id|tuple
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|CFG_CHECK
c_func
(paren
id|GetTupleData
comma
id|handle
comma
op_amp
id|tuple
)paren
suffix:semicolon
id|CFG_CHECK
c_func
(paren
id|ParseTuple
comma
id|handle
comma
op_amp
id|tuple
comma
op_amp
id|parse
)paren
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
id|link-&gt;io.NumPorts1
op_assign
id|parse.cftable_entry.io.win
(braket
l_int|0
)braket
dot
id|len
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;io.BasePort1
op_ne
l_int|0
)paren
(brace
id|i
op_assign
id|CardServices
c_func
(paren
id|RequestIO
comma
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
id|handle
comma
op_amp
id|tuple
)paren
suffix:semicolon
)brace
id|CS_CHECK
c_func
(paren
id|RequestIRQ
comma
id|handle
comma
op_amp
id|link-&gt;irq
)paren
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|RequestConfiguration
comma
id|handle
comma
op_amp
id|link-&gt;conf
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|info-&gt;manf_id
op_eq
id|MANFID_MACNICA
)paren
op_logical_or
(paren
id|info-&gt;manf_id
op_eq
id|MANFID_PIONEER
)paren
op_logical_or
(paren
id|info-&gt;manf_id
op_eq
l_int|0x0098
)paren
)paren
(brace
multiline_comment|/* set ATAcmd */
id|outb
c_func
(paren
l_int|0xb4
comma
id|link-&gt;io.BasePort1
op_plus
l_int|0xd
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x24
comma
id|link-&gt;io.BasePort1
op_plus
l_int|0x9
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x04
comma
id|link-&gt;io.BasePort1
op_plus
l_int|0xd
)paren
suffix:semicolon
)brace
multiline_comment|/* A bad hack... */
id|release_region
c_func
(paren
id|link-&gt;io.BasePort1
comma
id|link-&gt;io.NumPorts1
)paren
suffix:semicolon
multiline_comment|/* The KXL-810AN has a bigger IO port window */
r_if
c_cond
(paren
id|link-&gt;io.NumPorts1
op_eq
l_int|32
)paren
id|qlogicfas_preset
c_func
(paren
id|link-&gt;io.BasePort1
op_plus
l_int|16
comma
id|link-&gt;irq.AssignedIRQ
)paren
suffix:semicolon
r_else
id|qlogicfas_preset
c_func
(paren
id|link-&gt;io.BasePort1
comma
id|link-&gt;irq.AssignedIRQ
)paren
suffix:semicolon
id|scsi_register_host
c_func
(paren
op_amp
id|driver_template
)paren
suffix:semicolon
id|tail
op_assign
op_amp
id|link-&gt;dev
suffix:semicolon
id|info-&gt;ndev
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|host
op_assign
id|scsi_host_get_next
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|host
suffix:semicolon
id|host
op_assign
id|scsi_host_get_next
c_func
(paren
id|host
)paren
)paren
r_if
c_cond
(paren
id|host-&gt;hostt
op_eq
op_amp
id|driver_template
)paren
id|list_for_each_entry
(paren
id|dev
comma
op_amp
id|host-&gt;my_devices
comma
id|siblings
)paren
(brace
id|u_long
id|arg
(braket
l_int|2
)braket
comma
id|id
suffix:semicolon
id|kernel_scsi_ioctl
c_func
(paren
id|dev
comma
id|SCSI_IOCTL_GET_IDLUN
comma
id|arg
)paren
suffix:semicolon
id|id
op_assign
(paren
id|arg
(braket
l_int|0
)braket
op_amp
l_int|0x0f
)paren
op_plus
(paren
(paren
id|arg
(braket
l_int|0
)braket
op_rshift
l_int|4
)paren
op_amp
l_int|0xf0
)paren
op_plus
(paren
(paren
id|arg
(braket
l_int|0
)braket
op_rshift
l_int|8
)paren
op_amp
l_int|0xf00
)paren
op_plus
(paren
(paren
id|arg
(braket
l_int|0
)braket
op_rshift
l_int|12
)paren
op_amp
l_int|0xf000
)paren
suffix:semicolon
id|node
op_assign
op_amp
id|info-&gt;node
(braket
id|info-&gt;ndev
)braket
suffix:semicolon
id|node-&gt;minor
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|dev-&gt;type
)paren
(brace
r_case
id|TYPE_TAPE
suffix:colon
id|node-&gt;major
op_assign
id|SCSI_TAPE_MAJOR
suffix:semicolon
id|sprintf
c_func
(paren
id|node-&gt;dev_name
comma
l_string|&quot;st#%04lx&quot;
comma
id|id
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TYPE_DISK
suffix:colon
r_case
id|TYPE_MOD
suffix:colon
id|node-&gt;major
op_assign
id|SCSI_DISK0_MAJOR
suffix:semicolon
id|sprintf
c_func
(paren
id|node-&gt;dev_name
comma
l_string|&quot;sd#%04lx&quot;
comma
id|id
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TYPE_ROM
suffix:colon
r_case
id|TYPE_WORM
suffix:colon
id|node-&gt;major
op_assign
id|SCSI_CDROM_MAJOR
suffix:semicolon
id|sprintf
c_func
(paren
id|node-&gt;dev_name
comma
l_string|&quot;sr#%04lx&quot;
comma
id|id
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|node-&gt;major
op_assign
id|SCSI_GENERIC_MAJOR
suffix:semicolon
id|sprintf
c_func
(paren
id|node-&gt;dev_name
comma
l_string|&quot;sg#%04lx&quot;
comma
id|id
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
op_star
id|tail
op_assign
id|node
suffix:semicolon
id|tail
op_assign
op_amp
id|node-&gt;next
suffix:semicolon
id|info-&gt;ndev
op_increment
suffix:semicolon
)brace
op_star
id|tail
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;ndev
op_eq
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;qlogic_cs: no SCSI devices found&bslash;n&quot;
)paren
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
id|qlogic_release
c_func
(paren
(paren
id|u_long
)paren
id|link
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* qlogic_config */
multiline_comment|/*====================================================================*/
DECL|function|qlogic_release
r_static
r_void
id|qlogic_release
c_func
(paren
id|u_long
id|arg
)paren
(brace
id|dev_link_t
op_star
id|link
op_assign
(paren
id|dev_link_t
op_star
)paren
id|arg
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;qlogic_release(0x%p)&bslash;n&quot;
comma
id|link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|GET_USE_COUNT
c_func
(paren
op_amp
id|__this_module
)paren
op_ne
l_int|0
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;qlogic_cs: release postponed, device still open&bslash;n&quot;
)paren
suffix:semicolon
id|link-&gt;state
op_or_assign
id|DEV_STALE_CONFIG
suffix:semicolon
r_return
suffix:semicolon
)brace
id|scsi_unregister_host
c_func
(paren
op_amp
id|driver_template
)paren
suffix:semicolon
id|link-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
id|CardServices
c_func
(paren
id|ReleaseConfiguration
comma
id|link-&gt;handle
)paren
suffix:semicolon
id|CardServices
c_func
(paren
id|ReleaseIO
comma
id|link-&gt;handle
comma
op_amp
id|link-&gt;io
)paren
suffix:semicolon
id|CardServices
c_func
(paren
id|ReleaseIRQ
comma
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
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_STALE_LINK
)paren
id|qlogic_detach
c_func
(paren
id|link
)paren
suffix:semicolon
)brace
multiline_comment|/* qlogic_release */
multiline_comment|/*====================================================================*/
DECL|function|qlogic_event
r_static
r_int
id|qlogic_event
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
l_string|&quot;qlogic_event(0x%06x)&bslash;n&quot;
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
id|mod_timer
c_func
(paren
op_amp
id|link-&gt;release
comma
id|jiffies
op_plus
id|HZ
op_div
l_int|20
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
id|qlogic_config
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
id|CardServices
c_func
(paren
id|ReleaseConfiguration
comma
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
id|scsi_info_t
op_star
id|info
op_assign
id|link-&gt;priv
suffix:semicolon
id|CardServices
c_func
(paren
id|RequestConfiguration
comma
id|link-&gt;handle
comma
op_amp
id|link-&gt;conf
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|info-&gt;manf_id
op_eq
id|MANFID_MACNICA
)paren
op_logical_or
(paren
id|info-&gt;manf_id
op_eq
id|MANFID_PIONEER
)paren
op_logical_or
(paren
id|info-&gt;manf_id
op_eq
l_int|0x0098
)paren
)paren
(brace
id|outb
c_func
(paren
l_int|0x80
comma
id|link-&gt;io.BasePort1
op_plus
l_int|0xd
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x24
comma
id|link-&gt;io.BasePort1
op_plus
l_int|0x9
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x04
comma
id|link-&gt;io.BasePort1
op_plus
l_int|0xd
)paren
suffix:semicolon
)brace
multiline_comment|/* Ugggglllyyyy!!! */
id|driver_template
dot
id|eh_bus_reset_handler
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
multiline_comment|/* qlogic_event */
multiline_comment|/*====================================================================*/
DECL|function|init_qlogic_cs
r_static
r_int
id|__init
id|init_qlogic_cs
c_func
(paren
r_void
)paren
(brace
id|servinfo_t
id|serv
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|version
)paren
suffix:semicolon
id|CardServices
c_func
(paren
id|GetCardServicesInfo
comma
op_amp
id|serv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|serv.Revision
op_ne
id|CS_RELEASE_CODE
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;qlogic_cs: Card Services release &quot;
l_string|&quot;does not match!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|register_pccard_driver
c_func
(paren
op_amp
id|dev_info
comma
op_amp
id|qlogic_attach
comma
op_amp
id|qlogic_detach
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|exit_qlogic_cs
r_static
r_void
id|__exit
id|exit_qlogic_cs
c_func
(paren
r_void
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;qlogic_cs: unloading&bslash;n&quot;
)paren
suffix:semicolon
id|unregister_pccard_driver
c_func
(paren
op_amp
id|dev_info
)paren
suffix:semicolon
r_while
c_loop
(paren
id|dev_list
op_ne
l_int|NULL
)paren
id|qlogic_detach
c_func
(paren
id|dev_list
)paren
suffix:semicolon
)brace
DECL|variable|init_qlogic_cs
id|module_init
c_func
(paren
id|init_qlogic_cs
)paren
suffix:semicolon
DECL|variable|exit_qlogic_cs
id|module_exit
c_func
(paren
id|exit_qlogic_cs
)paren
suffix:semicolon
eof
