multiline_comment|/*&n; * Driver for Digigram VXpocket soundcards&n; *&n; * PCMCIA entry part&n; *&n; * Copyright (c) 2002 by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &quot;vxpocket.h&quot;
macro_line|#include &lt;pcmcia/ciscode.h&gt;
macro_line|#include &lt;pcmcia/cisreg.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Takashi Iwai &lt;tiwai@suse.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Common routines for Digigram PCMCIA VX drivers&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * prototypes&n; */
r_static
r_void
id|vxpocket_config
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
suffix:semicolon
r_static
r_int
id|vxpocket_event
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
DECL|function|vxpocket_release
r_static
r_void
id|vxpocket_release
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
(brace
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_CONFIG
)paren
(brace
multiline_comment|/* release cs resources */
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
)brace
multiline_comment|/*&n; * destructor&n; */
DECL|function|snd_vxpocket_free
r_static
r_int
id|snd_vxpocket_free
c_func
(paren
id|vx_core_t
op_star
id|chip
)paren
(brace
r_struct
id|snd_vxpocket
op_star
id|vxp
op_assign
(paren
r_struct
id|snd_vxpocket
op_star
)paren
id|chip
suffix:semicolon
r_struct
id|snd_vxp_entry
op_star
id|hw
suffix:semicolon
id|dev_link_t
op_star
id|link
op_assign
op_amp
id|vxp-&gt;link
suffix:semicolon
id|vxpocket_release
c_func
(paren
id|link
)paren
suffix:semicolon
multiline_comment|/* Break the link with Card Services */
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
id|hw
op_assign
id|vxp-&gt;hw_entry
suffix:semicolon
r_if
c_cond
(paren
id|hw
)paren
id|hw-&gt;card_list
(braket
id|vxp-&gt;index
)braket
op_assign
l_int|NULL
suffix:semicolon
id|chip-&gt;card
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;dev
)paren
id|kfree
c_func
(paren
id|chip-&gt;dev
)paren
suffix:semicolon
id|snd_vx_free_firmware
c_func
(paren
id|chip
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|chip
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_vxpocket_dev_free
r_static
r_int
id|snd_vxpocket_dev_free
c_func
(paren
id|snd_device_t
op_star
id|device
)paren
(brace
id|vx_core_t
op_star
id|chip
op_assign
id|device-&gt;device_data
suffix:semicolon
r_return
id|snd_vxpocket_free
c_func
(paren
id|chip
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * snd_vxpocket_attach - attach callback for cs&n; * @hw: the hardware information&n; */
DECL|function|snd_vxpocket_attach
id|dev_link_t
op_star
id|snd_vxpocket_attach
c_func
(paren
r_struct
id|snd_vxp_entry
op_star
id|hw
)paren
(brace
id|client_reg_t
id|client_reg
suffix:semicolon
multiline_comment|/* Register with cardmgr */
id|dev_link_t
op_star
id|link
suffix:semicolon
multiline_comment|/* Info for cardmgr */
r_int
id|i
comma
id|ret
suffix:semicolon
id|vx_core_t
op_star
id|chip
suffix:semicolon
r_struct
id|snd_vxpocket
op_star
id|vxp
suffix:semicolon
id|snd_card_t
op_star
id|card
suffix:semicolon
r_static
id|snd_device_ops_t
id|ops
op_assign
(brace
dot
id|dev_free
op_assign
id|snd_vxpocket_dev_free
comma
)brace
suffix:semicolon
id|snd_printdd
c_func
(paren
id|KERN_DEBUG
l_string|&quot;vxpocket_attach called&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* find an empty slot from the card list */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|SNDRV_CARDS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|hw-&gt;card_list
(braket
id|i
)braket
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_ge
id|SNDRV_CARDS
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;vxpocket: too many cards found&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|hw-&gt;enable_table
(braket
id|i
)braket
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* disabled explicitly */
multiline_comment|/* ok, create a card instance */
id|card
op_assign
id|snd_card_new
c_func
(paren
id|hw-&gt;index_table
(braket
id|i
)braket
comma
id|hw-&gt;id_table
(braket
id|i
)braket
comma
id|THIS_MODULE
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card
op_eq
l_int|NULL
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;vxpocket: cannot create a card instance&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|chip
op_assign
id|snd_vx_create
c_func
(paren
id|card
comma
id|hw-&gt;hardware
comma
id|hw-&gt;ops
comma
r_sizeof
(paren
r_struct
id|snd_vxpocket
)paren
op_minus
r_sizeof
(paren
id|vx_core_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|chip
)paren
r_return
l_int|NULL
suffix:semicolon
macro_line|#ifdef SND_VX_FW_LOADER
multiline_comment|/* fake a device here since pcmcia doesn&squot;t give a valid device... */
id|chip-&gt;dev
op_assign
id|kcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|chip-&gt;dev
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|chip-&gt;dev
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;vxp: can&squot;t malloc chip-&gt;dev&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|chip
)paren
suffix:semicolon
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|device_initialize
c_func
(paren
id|chip-&gt;dev
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|chip-&gt;dev-&gt;bus_id
comma
l_string|&quot;vxpocket%d&quot;
comma
id|i
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|snd_device_new
c_func
(paren
id|card
comma
id|SNDRV_DEV_LOWLEVEL
comma
id|chip
comma
op_amp
id|ops
)paren
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|chip
)paren
suffix:semicolon
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|vxp
op_assign
(paren
r_struct
id|snd_vxpocket
op_star
)paren
id|chip
suffix:semicolon
id|vxp-&gt;index
op_assign
id|i
suffix:semicolon
id|vxp-&gt;hw_entry
op_assign
id|hw
suffix:semicolon
id|chip-&gt;ibl.size
op_assign
id|hw-&gt;ibl
(braket
id|i
)braket
suffix:semicolon
id|hw-&gt;card_list
(braket
id|i
)braket
op_assign
id|chip
suffix:semicolon
id|link
op_assign
op_amp
id|vxp-&gt;link
suffix:semicolon
id|link-&gt;priv
op_assign
id|chip
suffix:semicolon
id|link-&gt;io.Attributes1
op_assign
id|IO_DATA_PATH_WIDTH_AUTO
suffix:semicolon
id|link-&gt;io.NumPorts1
op_assign
l_int|16
suffix:semicolon
id|link-&gt;irq.Attributes
op_assign
id|IRQ_TYPE_EXCLUSIVE
op_or
id|IRQ_HANDLE_PRESENT
suffix:semicolon
singleline_comment|// link-&gt;irq.Attributes = IRQ_TYPE_DYNAMIC_SHARING|IRQ_FIRST_SHARED;
id|link-&gt;irq.IRQInfo1
op_assign
id|IRQ_INFO2_VALID
op_or
id|IRQ_LEVEL_ID
suffix:semicolon
r_if
c_cond
(paren
id|hw-&gt;irq_list
(braket
l_int|0
)braket
op_eq
op_minus
l_int|1
)paren
id|link-&gt;irq.IRQInfo2
op_assign
op_star
id|hw-&gt;irq_mask_p
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
id|hw-&gt;irq_list
(braket
id|i
)braket
suffix:semicolon
id|link-&gt;irq.Handler
op_assign
op_amp
id|snd_vx_irq_handler
suffix:semicolon
id|link-&gt;irq.Instance
op_assign
id|chip
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
id|link-&gt;conf.ConfigIndex
op_assign
l_int|1
suffix:semicolon
id|link-&gt;conf.Present
op_assign
id|PRESENT_OPTION
suffix:semicolon
multiline_comment|/* Register with Card Services */
id|memset
c_func
(paren
op_amp
id|client_reg
comma
l_int|0
comma
r_sizeof
(paren
id|client_reg
)paren
)paren
suffix:semicolon
id|client_reg.dev_info
op_assign
id|hw-&gt;dev_info
suffix:semicolon
id|client_reg.Attributes
op_assign
id|INFO_IO_CLIENT
op_or
id|INFO_CARD_SHARE
suffix:semicolon
id|client_reg.EventMask
op_assign
id|CS_EVENT_CARD_INSERTION
op_or
id|CS_EVENT_CARD_REMOVAL
macro_line|#ifdef CONFIG_PM
op_or
id|CS_EVENT_RESET_PHYSICAL
op_or
id|CS_EVENT_CARD_RESET
op_or
id|CS_EVENT_PM_SUSPEND
op_or
id|CS_EVENT_PM_RESUME
macro_line|#endif
suffix:semicolon
id|client_reg.event_handler
op_assign
op_amp
id|vxpocket_event
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
id|CS_SUCCESS
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
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Chain drivers */
id|link-&gt;next
op_assign
id|hw-&gt;dev_list
suffix:semicolon
id|hw-&gt;dev_list
op_assign
id|link
suffix:semicolon
multiline_comment|/* snd_card_set_pm_callback(card, snd_vxpocket_suspend, snd_vxpocket_resume, chip); */
r_return
id|link
suffix:semicolon
)brace
multiline_comment|/**&n; * snd_vxpocket_assign_resources - initialize the hardware and card instance.&n; * @port: i/o port for the card&n; * @irq: irq number for the card&n; *&n; * this function assigns the specified port and irq, boot the card,&n; * create pcm and control instances, and initialize the rest hardware.&n; *&n; * returns 0 if successful, or a negative error code.&n; */
DECL|function|snd_vxpocket_assign_resources
r_static
r_int
id|snd_vxpocket_assign_resources
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|port
comma
r_int
id|irq
)paren
(brace
r_int
id|err
suffix:semicolon
id|snd_card_t
op_star
id|card
op_assign
id|chip-&gt;card
suffix:semicolon
r_struct
id|snd_vxpocket
op_star
id|vxp
op_assign
(paren
r_struct
id|snd_vxpocket
op_star
)paren
id|chip
suffix:semicolon
id|snd_printdd
c_func
(paren
id|KERN_DEBUG
l_string|&quot;vxpocket assign resources: port = 0x%x, irq = %d&bslash;n&quot;
comma
id|port
comma
id|irq
)paren
suffix:semicolon
id|vxp-&gt;port
op_assign
id|port
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;shortname
comma
l_string|&quot;Digigram %s&quot;
comma
id|card-&gt;driver
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;longname
comma
l_string|&quot;%s at 0x%x, irq %i&quot;
comma
id|card-&gt;shortname
comma
id|port
comma
id|irq
)paren
suffix:semicolon
id|chip-&gt;irq
op_assign
id|irq
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_vx_setup_firmware
c_func
(paren
id|chip
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * snd_vxpocket_detach - detach callback for cs&n; * @hw: the hardware information&n; */
DECL|function|snd_vxpocket_detach
r_void
id|snd_vxpocket_detach
c_func
(paren
r_struct
id|snd_vxp_entry
op_star
id|hw
comma
id|dev_link_t
op_star
id|link
)paren
(brace
id|vx_core_t
op_star
id|chip
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|link
)paren
r_return
suffix:semicolon
id|chip
op_assign
id|link-&gt;priv
suffix:semicolon
id|snd_printdd
c_func
(paren
id|KERN_DEBUG
l_string|&quot;vxpocket_detach called&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Remove the interface data from the linked list */
r_if
c_cond
(paren
id|hw
)paren
(brace
id|dev_link_t
op_star
op_star
id|linkp
suffix:semicolon
multiline_comment|/* Locate device structure */
r_for
c_loop
(paren
id|linkp
op_assign
op_amp
id|hw-&gt;dev_list
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
(brace
op_star
id|linkp
op_assign
id|link-&gt;next
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|chip-&gt;chip_status
op_or_assign
id|VX_STAT_IS_STALE
suffix:semicolon
multiline_comment|/* to be sure */
id|snd_card_disconnect
c_func
(paren
id|chip-&gt;card
)paren
suffix:semicolon
id|snd_card_free_in_thread
c_func
(paren
id|chip-&gt;card
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * configuration callback&n; */
DECL|macro|CS_CHECK
mdefine_line|#define CS_CHECK(fn, ret) &bslash;&n;do { last_fn = (fn); if ((last_ret = (ret)) != 0) goto cs_failed; } while (0)
DECL|function|vxpocket_config
r_static
r_void
id|vxpocket_config
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
id|vx_core_t
op_star
id|chip
op_assign
id|link-&gt;priv
suffix:semicolon
r_struct
id|snd_vxpocket
op_star
id|vxp
op_assign
(paren
r_struct
id|snd_vxpocket
op_star
)paren
id|chip
suffix:semicolon
id|tuple_t
id|tuple
suffix:semicolon
id|cisparse_t
op_star
id|parse
op_assign
l_int|NULL
suffix:semicolon
id|u_short
id|buf
(braket
l_int|32
)braket
suffix:semicolon
r_int
id|last_fn
comma
id|last_ret
suffix:semicolon
id|snd_printdd
c_func
(paren
id|KERN_DEBUG
l_string|&quot;vxpocket_config called&bslash;n&quot;
)paren
suffix:semicolon
id|parse
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|parse
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parse
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;vx: cannot allocate&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|tuple.Attributes
op_assign
l_int|0
suffix:semicolon
id|tuple.TupleData
op_assign
(paren
id|cisdata_t
op_star
)paren
id|buf
suffix:semicolon
id|tuple.TupleDataMax
op_assign
r_sizeof
(paren
id|buf
)paren
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
id|parse
)paren
)paren
suffix:semicolon
id|link-&gt;conf.ConfigBase
op_assign
id|parse-&gt;config.base
suffix:semicolon
id|link-&gt;conf.Present
op_assign
id|parse-&gt;config.rmask
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Configure card */
id|link-&gt;state
op_or_assign
id|DEV_CONFIG
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|RequestIO
comma
id|pcmcia_request_io
c_func
(paren
id|handle
comma
op_amp
id|link-&gt;io
)paren
)paren
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|RequestIRQ
comma
id|pcmcia_request_irq
c_func
(paren
id|link-&gt;handle
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
id|link-&gt;handle
comma
op_amp
id|link-&gt;conf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_vxpocket_assign_resources
c_func
(paren
id|chip
comma
id|link-&gt;io.BasePort1
comma
id|link-&gt;irq.AssignedIRQ
)paren
OL
l_int|0
)paren
r_goto
id|failed
suffix:semicolon
id|link-&gt;dev
op_assign
op_amp
id|vxp-&gt;node
suffix:semicolon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_CONFIG_PENDING
suffix:semicolon
id|kfree
c_func
(paren
id|parse
)paren
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
id|failed
suffix:colon
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
id|kfree
c_func
(paren
id|parse
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * event callback&n; */
DECL|function|vxpocket_event
r_static
r_int
id|vxpocket_event
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
id|vx_core_t
op_star
id|chip
op_assign
id|link-&gt;priv
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
id|snd_printdd
c_func
(paren
id|KERN_DEBUG
l_string|&quot;CARD_REMOVAL..&bslash;n&quot;
)paren
suffix:semicolon
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
(brace
id|chip-&gt;chip_status
op_or_assign
id|VX_STAT_IS_STALE
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|CS_EVENT_CARD_INSERTION
suffix:colon
id|snd_printdd
c_func
(paren
id|KERN_DEBUG
l_string|&quot;CARD_INSERTION..&bslash;n&quot;
)paren
suffix:semicolon
id|link-&gt;state
op_or_assign
id|DEV_PRESENT
op_or
id|DEV_CONFIG_PENDING
suffix:semicolon
id|vxpocket_config
c_func
(paren
id|link
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_PM
r_case
id|CS_EVENT_PM_SUSPEND
suffix:colon
id|snd_printdd
c_func
(paren
id|KERN_DEBUG
l_string|&quot;SUSPEND&bslash;n&quot;
)paren
suffix:semicolon
id|link-&gt;state
op_or_assign
id|DEV_SUSPEND
suffix:semicolon
r_if
c_cond
(paren
id|chip
op_logical_and
id|chip-&gt;card-&gt;pm_suspend
)paren
(brace
id|snd_printdd
c_func
(paren
id|KERN_DEBUG
l_string|&quot;snd_vx_suspend calling&bslash;n&quot;
)paren
suffix:semicolon
id|chip-&gt;card
op_member_access_from_pointer
id|pm_suspend
c_func
(paren
id|chip-&gt;card
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* Fall through... */
r_case
id|CS_EVENT_RESET_PHYSICAL
suffix:colon
id|snd_printdd
c_func
(paren
id|KERN_DEBUG
l_string|&quot;RESET_PHYSICAL&bslash;n&quot;
)paren
suffix:semicolon
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
id|snd_printdd
c_func
(paren
id|KERN_DEBUG
l_string|&quot;RESUME&bslash;n&quot;
)paren
suffix:semicolon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_SUSPEND
suffix:semicolon
multiline_comment|/* Fall through... */
r_case
id|CS_EVENT_CARD_RESET
suffix:colon
id|snd_printdd
c_func
(paren
id|KERN_DEBUG
l_string|&quot;CARD_RESET&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|DEV_OK
c_func
(paren
id|link
)paren
)paren
(brace
singleline_comment|//struct snd_vxpocket *vxp = (struct snd_vxpocket *)chip;
id|snd_printdd
c_func
(paren
id|KERN_DEBUG
l_string|&quot;requestconfig...&bslash;n&quot;
)paren
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
r_if
c_cond
(paren
id|chip
op_logical_and
id|chip-&gt;card-&gt;pm_resume
)paren
(brace
id|snd_printdd
c_func
(paren
id|KERN_DEBUG
l_string|&quot;calling snd_vx_resume&bslash;n&quot;
)paren
suffix:semicolon
id|chip-&gt;card
op_member_access_from_pointer
id|pm_resume
c_func
(paren
id|chip-&gt;card
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
id|snd_printdd
c_func
(paren
id|KERN_DEBUG
l_string|&quot;resume done!&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * exported stuffs&n; */
DECL|variable|snd_vxpocket_ops
id|EXPORT_SYMBOL
c_func
(paren
id|snd_vxpocket_ops
)paren
suffix:semicolon
DECL|variable|snd_vxpocket_attach
id|EXPORT_SYMBOL
c_func
(paren
id|snd_vxpocket_attach
)paren
suffix:semicolon
DECL|variable|snd_vxpocket_detach
id|EXPORT_SYMBOL
c_func
(paren
id|snd_vxpocket_detach
)paren
suffix:semicolon
eof
