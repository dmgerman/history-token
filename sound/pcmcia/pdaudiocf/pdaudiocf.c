multiline_comment|/*&n; * Driver for Sound Core PDAudioCF soundcard&n; *&n; * Copyright (c) 2003 by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;pcmcia/version.h&gt;
macro_line|#include &lt;pcmcia/ciscode.h&gt;
macro_line|#include &lt;pcmcia/cisreg.h&gt;
macro_line|#include &quot;pdaudiocf.h&quot;
macro_line|#include &lt;sound/initval.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/*&n; */
DECL|macro|CARD_NAME
mdefine_line|#define CARD_NAME&t;&quot;PDAudio-CF&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jaroslav Kysela &lt;perex@suse.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Sound Core &quot;
id|CARD_NAME
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;{{Sound Core,&quot;
id|CARD_NAME
l_string|&quot;}}&quot;
)paren
suffix:semicolon
DECL|variable|index
r_static
r_int
id|index
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_IDX
suffix:semicolon
multiline_comment|/* Index 0-MAX */
DECL|variable|id
r_static
r_char
op_star
id|id
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_STR
suffix:semicolon
multiline_comment|/* ID for this card */
DECL|variable|enable
r_static
r_int
id|enable
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_ENABLE_PNP
suffix:semicolon
multiline_comment|/* Enable switches */
id|module_param_array
c_func
(paren
id|index
comma
r_int
comma
l_int|NULL
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|index
comma
l_string|&quot;Index value for &quot;
id|CARD_NAME
l_string|&quot; soundcard.&quot;
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|id
comma
id|charp
comma
l_int|NULL
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|id
comma
l_string|&quot;ID string for &quot;
id|CARD_NAME
l_string|&quot; soundcard.&quot;
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|enable
comma
r_bool
comma
l_int|NULL
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|enable
comma
l_string|&quot;Enable &quot;
id|CARD_NAME
l_string|&quot; soundcard.&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; */
DECL|variable|dev_info
r_static
id|dev_info_t
id|dev_info
op_assign
l_string|&quot;snd-pdaudiocf&quot;
suffix:semicolon
DECL|variable|card_list
r_static
id|snd_card_t
op_star
id|card_list
(braket
id|SNDRV_CARDS
)braket
suffix:semicolon
DECL|variable|dev_list
r_static
id|dev_link_t
op_star
id|dev_list
suffix:semicolon
multiline_comment|/*&n; * prototypes&n; */
r_static
r_void
id|pdacf_config
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
suffix:semicolon
r_static
r_int
id|pdacf_event
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
r_void
id|snd_pdacf_detach
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
suffix:semicolon
DECL|function|pdacf_release
r_static
r_void
id|pdacf_release
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
DECL|function|snd_pdacf_free
r_static
r_int
id|snd_pdacf_free
c_func
(paren
id|pdacf_t
op_star
id|pdacf
)paren
(brace
id|dev_link_t
op_star
id|link
op_assign
op_amp
id|pdacf-&gt;link
suffix:semicolon
id|pdacf_release
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
id|card_list
(braket
id|pdacf-&gt;index
)braket
op_assign
l_int|NULL
suffix:semicolon
id|pdacf-&gt;card
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|pdacf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_pdacf_dev_free
r_static
r_int
id|snd_pdacf_dev_free
c_func
(paren
id|snd_device_t
op_star
id|device
)paren
(brace
id|pdacf_t
op_star
id|chip
op_assign
id|device-&gt;device_data
suffix:semicolon
r_return
id|snd_pdacf_free
c_func
(paren
id|chip
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * snd_pdacf_attach - attach callback for cs&n; */
DECL|function|snd_pdacf_attach
r_static
id|dev_link_t
op_star
id|snd_pdacf_attach
c_func
(paren
r_void
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
id|pdacf_t
op_star
id|pdacf
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
id|snd_pdacf_dev_free
comma
)brace
suffix:semicolon
id|snd_printdd
c_func
(paren
id|KERN_DEBUG
l_string|&quot;pdacf_attach called&bslash;n&quot;
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
id|card_list
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
l_string|&quot;pdacf: too many cards found&bslash;n&quot;
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
id|enable
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
id|index
(braket
id|i
)braket
comma
id|id
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
l_string|&quot;pdacf: cannot create a card instance&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|pdacf
op_assign
id|snd_pdacf_create
c_func
(paren
id|card
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pdacf
)paren
r_return
l_int|NULL
suffix:semicolon
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
id|pdacf
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
id|pdacf
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
id|pdacf-&gt;index
op_assign
id|i
suffix:semicolon
id|card_list
(braket
id|i
)braket
op_assign
id|card
suffix:semicolon
id|link
op_assign
op_amp
id|pdacf-&gt;link
suffix:semicolon
id|link-&gt;priv
op_assign
id|pdacf
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
op_or
id|IRQ_FORCED_PULSE
suffix:semicolon
singleline_comment|// link-&gt;irq.Attributes = IRQ_TYPE_DYNAMIC_SHARING|IRQ_FIRST_SHARED;
id|link-&gt;irq.IRQInfo1
op_assign
l_int|0
multiline_comment|/* | IRQ_LEVEL_ID */
suffix:semicolon
id|link-&gt;irq.Handler
op_assign
id|pdacf_interrupt
suffix:semicolon
id|link-&gt;irq.Instance
op_assign
id|pdacf
suffix:semicolon
id|link-&gt;conf.Attributes
op_assign
id|CONF_ENABLE_IRQ
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
multiline_comment|/* Chain drivers */
id|link-&gt;next
op_assign
id|dev_list
suffix:semicolon
id|dev_list
op_assign
id|link
suffix:semicolon
multiline_comment|/* Register with Card Services */
id|client_reg.dev_info
op_assign
op_amp
id|dev_info
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
id|pdacf_event
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
id|snd_pdacf_detach
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
multiline_comment|/**&n; * snd_pdacf_assign_resources - initialize the hardware and card instance.&n; * @port: i/o port for the card&n; * @irq: irq number for the card&n; *&n; * this function assigns the specified port and irq, boot the card,&n; * create pcm and control instances, and initialize the rest hardware.&n; *&n; * returns 0 if successful, or a negative error code.&n; */
DECL|function|snd_pdacf_assign_resources
r_static
r_int
id|snd_pdacf_assign_resources
c_func
(paren
id|pdacf_t
op_star
id|pdacf
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
id|pdacf-&gt;card
suffix:semicolon
id|snd_printdd
c_func
(paren
id|KERN_DEBUG
l_string|&quot;pdacf assign resources: port = 0x%x, irq = %d&bslash;n&quot;
comma
id|port
comma
id|irq
)paren
suffix:semicolon
id|pdacf-&gt;port
op_assign
id|port
suffix:semicolon
id|pdacf-&gt;irq
op_assign
id|irq
suffix:semicolon
id|pdacf-&gt;chip_status
op_or_assign
id|PDAUDIOCF_STAT_IS_CONFIGURED
suffix:semicolon
id|err
op_assign
id|snd_pdacf_ak4117_create
c_func
(paren
id|pdacf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|strcpy
c_func
(paren
id|card-&gt;driver
comma
l_string|&quot;PDAudio-CF&quot;
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;shortname
comma
l_string|&quot;Core Sound %s&quot;
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
id|err
op_assign
id|snd_pdacf_pcm_new
c_func
(paren
id|pdacf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|snd_card_set_pm_callback
c_func
(paren
id|card
comma
id|snd_pdacf_suspend
comma
id|snd_pdacf_resume
comma
id|pdacf
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_card_register
c_func
(paren
id|card
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
multiline_comment|/*&n; * snd_pdacf_detach - detach callback for cs&n; */
DECL|function|snd_pdacf_detach
r_static
r_void
id|snd_pdacf_detach
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
(brace
id|pdacf_t
op_star
id|chip
op_assign
id|link-&gt;priv
suffix:semicolon
id|snd_printdd
c_func
(paren
id|KERN_DEBUG
l_string|&quot;pdacf_detach called&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Remove the interface data from the linked list */
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
)paren
op_star
id|linkp
op_assign
id|link-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chip-&gt;chip_status
op_amp
id|PDAUDIOCF_STAT_IS_CONFIGURED
)paren
id|snd_pdacf_powerdown
c_func
(paren
id|chip
)paren
suffix:semicolon
id|chip-&gt;chip_status
op_or_assign
id|PDAUDIOCF_STAT_IS_STALE
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
DECL|function|pdacf_config
r_static
r_void
id|pdacf_config
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
id|pdacf_t
op_star
id|pdacf
op_assign
id|link-&gt;priv
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
id|config_info_t
id|conf
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
l_string|&quot;pdacf_config called&bslash;n&quot;
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
l_string|&quot;pdacf_config: cannot allocate&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|tuple.DesiredTuple
op_assign
id|CISTPL_CFTABLE_ENTRY
suffix:semicolon
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
id|link-&gt;conf.ConfigIndex
op_assign
l_int|0x5
suffix:semicolon
id|kfree
c_func
(paren
id|parse
)paren
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|GetConfigurationInfo
comma
id|pcmcia_get_configuration_info
c_func
(paren
id|handle
comma
op_amp
id|conf
)paren
)paren
suffix:semicolon
id|link-&gt;conf.Vcc
op_assign
id|conf.Vcc
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
id|snd_pdacf_assign_resources
c_func
(paren
id|pdacf
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
id|pdacf-&gt;node
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
)brace
multiline_comment|/*&n; * event callback&n; */
DECL|function|pdacf_event
r_static
r_int
id|pdacf_event
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
id|pdacf_t
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
id|PDAUDIOCF_STAT_IS_STALE
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
suffix:semicolon
id|pdacf_config
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
)paren
(brace
id|snd_printdd
c_func
(paren
id|KERN_DEBUG
l_string|&quot;snd_pdacf_suspend calling&bslash;n&quot;
)paren
suffix:semicolon
id|snd_pdacf_suspend
c_func
(paren
id|chip-&gt;card
comma
id|PMSG_SUSPEND
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
)paren
(brace
id|snd_printdd
c_func
(paren
id|KERN_DEBUG
l_string|&quot;calling snd_pdacf_resume&bslash;n&quot;
)paren
suffix:semicolon
id|snd_pdacf_resume
c_func
(paren
id|chip-&gt;card
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
multiline_comment|/*&n; * Module entry points&n; */
DECL|variable|pdacf_cs_driver
r_static
r_struct
id|pcmcia_driver
id|pdacf_cs_driver
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
l_string|&quot;snd-pdaudiocf&quot;
comma
)brace
comma
dot
id|attach
op_assign
id|snd_pdacf_attach
comma
dot
id|detach
op_assign
id|snd_pdacf_detach
)brace
suffix:semicolon
DECL|function|init_pdacf
r_static
r_int
id|__init
id|init_pdacf
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
id|pdacf_cs_driver
)paren
suffix:semicolon
)brace
DECL|function|exit_pdacf
r_static
r_void
id|__exit
id|exit_pdacf
c_func
(paren
r_void
)paren
(brace
id|pcmcia_unregister_driver
c_func
(paren
op_amp
id|pdacf_cs_driver
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
DECL|variable|init_pdacf
id|module_init
c_func
(paren
id|init_pdacf
)paren
suffix:semicolon
DECL|variable|exit_pdacf
id|module_exit
c_func
(paren
id|exit_pdacf
)paren
suffix:semicolon
eof
