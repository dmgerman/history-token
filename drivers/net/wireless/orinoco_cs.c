multiline_comment|/* orinoco_cs.c 0.13e&t;- (formerly known as dldwd_cs.c)&n; *&n; * A driver for &quot;Hermes&quot; chipset based PCMCIA wireless adaptors, such&n; * as the Lucent WavelanIEEE/Orinoco cards and their OEM (Cabletron/&n; * EnteraSys RoamAbout 802.11, ELSA Airlancer, Melco Buffalo and others).&n; * It should also be usable on various Prism II based cards such as the&n; * Linksys, D-Link and Farallon Skyline. It should also work on Symbol&n; * cards such as the 3Com AirConnect and Ericsson WLAN.&n; * &n; * Copyright notice &amp; release notes in file orinoco.c&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef  __IN_PCMCIA_PACKAGE__
macro_line|#include &lt;pcmcia/k_compat.h&gt;
macro_line|#endif /* __IN_PCMCIA_PACKAGE__ */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/wireless.h&gt;
macro_line|#include &lt;pcmcia/version.h&gt;
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &lt;pcmcia/cisreg.h&gt;
macro_line|#include &lt;pcmcia/ds.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;orinoco.h&quot;
multiline_comment|/********************************************************************/
multiline_comment|/* Module stuff&t;&t;&t;&t;&t;&t;&t;    */
multiline_comment|/********************************************************************/
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;David Gibson &lt;hermes@gibson.dropbear.id.au&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Driver for PCMCIA Lucent Orinoco, Prism II based and similar wireless cards&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;Dual MPL/GPL&quot;
)paren
suffix:semicolon
multiline_comment|/* Module parameters */
multiline_comment|/* The old way: bit map of interrupts to choose from */
multiline_comment|/* This means pick from 15, 14, 12, 11, 10, 9, 7, 5, 4, and 3 */
DECL|variable|irq_mask
r_static
id|uint
id|irq_mask
op_assign
l_int|0xdeb8
suffix:semicolon
multiline_comment|/* Newer, simpler way of listing specific interrupts */
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
multiline_comment|/* Some D-Link cards have buggy CIS. They do work at 5v properly, but&n; * don&squot;t have any CIS entry for it. This workaround it... */
DECL|variable|ignore_cis_vcc
r_static
r_int
id|ignore_cis_vcc
suffix:semicolon
multiline_comment|/* = 0 */
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
id|MODULE_PARM
c_func
(paren
id|ignore_cis_vcc
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
multiline_comment|/********************************************************************/
multiline_comment|/* Magic constants&t;&t;&t;&t;&t;&t;    */
multiline_comment|/********************************************************************/
multiline_comment|/*&n; * The dev_info variable is the &quot;key&quot; that is used to match up this&n; * device driver with appropriate cards, through the card&n; * configuration database.&n; */
DECL|variable|dev_info
r_static
id|dev_info_t
id|dev_info
op_assign
l_string|&quot;orinoco_cs&quot;
suffix:semicolon
multiline_comment|/********************************************************************/
multiline_comment|/* Data structures&t;&t;&t;&t;&t;&t;    */
multiline_comment|/********************************************************************/
multiline_comment|/* PCMCIA specific device information (goes in the card field of&n; * struct orinoco_private */
DECL|struct|orinoco_pccard
r_struct
id|orinoco_pccard
(brace
DECL|member|link
id|dev_link_t
id|link
suffix:semicolon
DECL|member|node
id|dev_node_t
id|node
suffix:semicolon
multiline_comment|/* Used to handle hard reset */
multiline_comment|/* yuck, we need this hack to work around the insanity of the&n;         * PCMCIA layer */
DECL|member|hard_reset_in_progress
r_int
r_int
id|hard_reset_in_progress
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * A linked list of &quot;instances&quot; of the device.  Each actual PCMCIA&n; * card corresponds to one device instance, and is described by one&n; * dev_link_t structure (defined in ds.h).&n; */
DECL|variable|dev_list
r_static
id|dev_link_t
op_star
id|dev_list
suffix:semicolon
multiline_comment|/* = NULL */
multiline_comment|/********************************************************************/
multiline_comment|/* Function prototypes&t;&t;&t;&t;&t;&t;    */
multiline_comment|/********************************************************************/
multiline_comment|/* device methods */
r_static
r_int
id|orinoco_cs_hard_reset
c_func
(paren
r_struct
id|orinoco_private
op_star
id|priv
)paren
suffix:semicolon
multiline_comment|/* PCMCIA gumpf */
r_static
r_void
id|orinoco_cs_config
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
suffix:semicolon
r_static
r_void
id|orinoco_cs_release
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
suffix:semicolon
r_static
r_int
id|orinoco_cs_event
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
id|orinoco_cs_attach
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|orinoco_cs_detach
c_func
(paren
id|dev_link_t
op_star
)paren
suffix:semicolon
multiline_comment|/********************************************************************/
multiline_comment|/* Device methods     &t;&t;&t;&t;&t;&t;    */
multiline_comment|/********************************************************************/
r_static
r_int
DECL|function|orinoco_cs_hard_reset
id|orinoco_cs_hard_reset
c_func
(paren
r_struct
id|orinoco_private
op_star
id|priv
)paren
(brace
r_struct
id|orinoco_pccard
op_star
id|card
op_assign
id|priv-&gt;card
suffix:semicolon
id|dev_link_t
op_star
id|link
op_assign
op_amp
id|card-&gt;link
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/* We need atomic ops here, because we&squot;re not holding the lock */
id|set_bit
c_func
(paren
l_int|0
comma
op_amp
id|card-&gt;hard_reset_in_progress
)paren
suffix:semicolon
id|err
op_assign
id|pcmcia_reset_card
c_func
(paren
id|link-&gt;handle
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|card-&gt;hard_reset_in_progress
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/********************************************************************/
multiline_comment|/* PCMCIA stuff     &t;&t;&t;&t;&t;&t;    */
multiline_comment|/********************************************************************/
multiline_comment|/*&n; * This creates an &quot;instance&quot; of the driver, allocating local data&n; * structures for one device.  The device is registered with Card&n; * Services.&n; * &n; * The dev_link structure is initialized, but we don&squot;t actually&n; * configure the card at this point -- we wait until we receive a card&n; * insertion event.  */
r_static
id|dev_link_t
op_star
DECL|function|orinoco_cs_attach
id|orinoco_cs_attach
c_func
(paren
r_void
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_struct
id|orinoco_private
op_star
id|priv
suffix:semicolon
r_struct
id|orinoco_pccard
op_star
id|card
suffix:semicolon
id|dev_link_t
op_star
id|link
suffix:semicolon
id|client_reg_t
id|client_reg
suffix:semicolon
r_int
id|ret
comma
id|i
suffix:semicolon
id|dev
op_assign
id|alloc_orinocodev
c_func
(paren
r_sizeof
(paren
op_star
id|card
)paren
comma
id|orinoco_cs_hard_reset
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
l_int|NULL
suffix:semicolon
id|priv
op_assign
id|dev-&gt;priv
suffix:semicolon
id|card
op_assign
id|priv-&gt;card
suffix:semicolon
multiline_comment|/* Link both structures together */
id|link
op_assign
op_amp
id|card-&gt;link
suffix:semicolon
id|link-&gt;priv
op_assign
id|dev
suffix:semicolon
multiline_comment|/* Interrupt setup */
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
id|link-&gt;irq.Handler
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* General socket configuration defaults can go here.  In this&n;&t; * client, we assume very little, and rely on the CIS for&n;&t; * almost everything.  In most clients, many details (i.e.,&n;&t; * number, sizes, and attributes of IO windows) are fixed by&n;&t; * the nature of the device, and can be hard-wired here. */
id|link-&gt;conf.Attributes
op_assign
l_int|0
suffix:semicolon
id|link-&gt;conf.IntType
op_assign
id|INT_MEMORY_AND_IO
suffix:semicolon
multiline_comment|/* Register with Card Services */
multiline_comment|/* FIXME: need a lock? */
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
id|client_reg.EventMask
op_assign
id|CS_EVENT_CARD_INSERTION
op_or
id|CS_EVENT_CARD_REMOVAL
op_or
id|CS_EVENT_RESET_PHYSICAL
op_or
id|CS_EVENT_CARD_RESET
op_or
id|CS_EVENT_PM_SUSPEND
op_or
id|CS_EVENT_PM_RESUME
suffix:semicolon
id|client_reg.event_handler
op_assign
op_amp
id|orinoco_cs_event
suffix:semicolon
id|client_reg.Version
op_assign
l_int|0x0210
suffix:semicolon
multiline_comment|/* FIXME: what does this mean? */
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
id|orinoco_cs_detach
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
multiline_comment|/* orinoco_cs_attach */
multiline_comment|/*&n; * This deletes a driver &quot;instance&quot;.  The device is de-registered with&n; * Card Services.  If it has been released, all local data structures&n; * are freed.  Otherwise, the structures will be freed when the device&n; * is released.&n; */
r_static
r_void
DECL|function|orinoco_cs_detach
id|orinoco_cs_detach
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
r_struct
id|net_device
op_star
id|dev
op_assign
id|link-&gt;priv
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
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_CONFIG
)paren
id|orinoco_cs_release
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
multiline_comment|/* Unlink device structure, and free it */
op_star
id|linkp
op_assign
id|link-&gt;next
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;orinoco_cs: detach: link=%p link-&gt;dev=%p&bslash;n&quot;
comma
id|link
comma
id|link-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;dev
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;orinoco_cs: About to unregister net device %p&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/* orinoco_cs_detach */
multiline_comment|/*&n; * orinoco_cs_config() is scheduled to run after a CARD_INSERTION&n; * event is received, to configure the PCMCIA socket, and to make the&n; * device available to the system.&n; */
DECL|macro|CS_CHECK
mdefine_line|#define CS_CHECK(fn, ret) &bslash;&n;do { last_fn = (fn); if ((last_ret = (ret)) != 0) goto cs_failed; } while (0)
r_static
r_void
DECL|function|orinoco_cs_config
id|orinoco_cs_config
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|link-&gt;priv
suffix:semicolon
id|client_handle_t
id|handle
op_assign
id|link-&gt;handle
suffix:semicolon
r_struct
id|orinoco_private
op_star
id|priv
op_assign
id|dev-&gt;priv
suffix:semicolon
r_struct
id|orinoco_pccard
op_star
id|card
op_assign
id|priv-&gt;card
suffix:semicolon
id|hermes_t
op_star
id|hw
op_assign
op_amp
id|priv-&gt;hw
suffix:semicolon
r_int
id|last_fn
comma
id|last_ret
suffix:semicolon
id|u_char
id|buf
(braket
l_int|64
)braket
suffix:semicolon
id|config_info_t
id|conf
suffix:semicolon
id|cisinfo_t
id|info
suffix:semicolon
id|tuple_t
id|tuple
suffix:semicolon
id|cisparse_t
id|parse
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|ValidateCIS
comma
id|pcmcia_validate_cis
c_func
(paren
id|handle
comma
op_amp
id|info
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This reads the card&squot;s CONFIG tuple to find its&n;&t; * configuration registers.&n;&t; */
id|tuple.DesiredTuple
op_assign
id|CISTPL_CONFIG
suffix:semicolon
id|tuple.Attributes
op_assign
l_int|0
suffix:semicolon
id|tuple.TupleData
op_assign
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
id|link-&gt;conf.Present
op_assign
id|parse.config.rmask
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Configure card */
id|link-&gt;state
op_or_assign
id|DEV_CONFIG
suffix:semicolon
multiline_comment|/* Look up the current Vcc */
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
multiline_comment|/*&n;&t; * In this loop, we scan the CIS for configuration table&n;&t; * entries, each of which describes a valid card&n;&t; * configuration, including voltage, IO window, memory window,&n;&t; * and interrupt settings.&n;&t; *&n;&t; * We make no assumptions about the card to be configured: we&n;&t; * use just the information available in the CIS.  In an ideal&n;&t; * world, this would work for any PCMCIA card, but it requires&n;&t; * a complete and accurate CIS.  In practice, a driver usually&n;&t; * &quot;knows&quot; most of these things without consulting the CIS,&n;&t; * and most client drivers will only use the CIS to fill in&n;&t; * implementation-defined details.&n;&t; */
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
id|cistpl_cftable_entry_t
op_star
id|cfg
op_assign
op_amp
(paren
id|parse.cftable_entry
)paren
suffix:semicolon
id|cistpl_cftable_entry_t
id|dflt
op_assign
(brace
dot
id|index
op_assign
l_int|0
)brace
suffix:semicolon
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
r_if
c_cond
(paren
id|cfg-&gt;flags
op_amp
id|CISTPL_CFTABLE_DEFAULT
)paren
id|dflt
op_assign
op_star
id|cfg
suffix:semicolon
r_if
c_cond
(paren
id|cfg-&gt;index
op_eq
l_int|0
)paren
r_goto
id|next_entry
suffix:semicolon
id|link-&gt;conf.ConfigIndex
op_assign
id|cfg-&gt;index
suffix:semicolon
multiline_comment|/* Does this card need audio output? */
r_if
c_cond
(paren
id|cfg-&gt;flags
op_amp
id|CISTPL_CFTABLE_AUDIO
)paren
(brace
id|link-&gt;conf.Attributes
op_or_assign
id|CONF_ENABLE_SPKR
suffix:semicolon
id|link-&gt;conf.Status
op_assign
id|CCSR_AUDIO_ENA
suffix:semicolon
)brace
multiline_comment|/* Use power settings for Vcc and Vpp if present */
multiline_comment|/* Note that the CIS values need to be rescaled */
r_if
c_cond
(paren
id|cfg-&gt;vcc.present
op_amp
(paren
l_int|1
op_lshift
id|CISTPL_POWER_VNOM
)paren
)paren
(brace
r_if
c_cond
(paren
id|conf.Vcc
op_ne
id|cfg-&gt;vcc.param
(braket
id|CISTPL_POWER_VNOM
)braket
op_div
l_int|10000
)paren
(brace
id|DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;orinoco_cs_config: Vcc mismatch (conf.Vcc = %d, CIS = %d)&bslash;n&quot;
comma
id|conf.Vcc
comma
id|cfg-&gt;vcc.param
(braket
id|CISTPL_POWER_VNOM
)braket
op_div
l_int|10000
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ignore_cis_vcc
)paren
r_goto
id|next_entry
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|dflt.vcc.present
op_amp
(paren
l_int|1
op_lshift
id|CISTPL_POWER_VNOM
)paren
)paren
(brace
r_if
c_cond
(paren
id|conf.Vcc
op_ne
id|dflt.vcc.param
(braket
id|CISTPL_POWER_VNOM
)braket
op_div
l_int|10000
)paren
(brace
id|DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;orinoco_cs_config: Vcc mismatch (conf.Vcc = %d, CIS = %d)&bslash;n&quot;
comma
id|conf.Vcc
comma
id|dflt.vcc.param
(braket
id|CISTPL_POWER_VNOM
)braket
op_div
l_int|10000
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ignore_cis_vcc
)paren
(brace
r_goto
id|next_entry
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|cfg-&gt;vpp1.present
op_amp
(paren
l_int|1
op_lshift
id|CISTPL_POWER_VNOM
)paren
)paren
id|link-&gt;conf.Vpp1
op_assign
id|link-&gt;conf.Vpp2
op_assign
id|cfg-&gt;vpp1.param
(braket
id|CISTPL_POWER_VNOM
)braket
op_div
l_int|10000
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dflt.vpp1.present
op_amp
(paren
l_int|1
op_lshift
id|CISTPL_POWER_VNOM
)paren
)paren
id|link-&gt;conf.Vpp1
op_assign
id|link-&gt;conf.Vpp2
op_assign
id|dflt.vpp1.param
(braket
id|CISTPL_POWER_VNOM
)braket
op_div
l_int|10000
suffix:semicolon
multiline_comment|/* Do we need to allocate an interrupt? */
r_if
c_cond
(paren
id|cfg-&gt;irq.IRQInfo1
op_logical_or
id|dflt.irq.IRQInfo1
)paren
id|link-&gt;conf.Attributes
op_or_assign
id|CONF_ENABLE_IRQ
suffix:semicolon
multiline_comment|/* IO window settings */
id|link-&gt;io.NumPorts1
op_assign
id|link-&gt;io.NumPorts2
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cfg-&gt;io.nwin
OG
l_int|0
)paren
op_logical_or
(paren
id|dflt.io.nwin
OG
l_int|0
)paren
)paren
(brace
id|cistpl_io_t
op_star
id|io
op_assign
(paren
id|cfg-&gt;io.nwin
)paren
ques
c_cond
op_amp
id|cfg-&gt;io
suffix:colon
op_amp
id|dflt.io
suffix:semicolon
id|link-&gt;io.Attributes1
op_assign
id|IO_DATA_PATH_WIDTH_AUTO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|io-&gt;flags
op_amp
id|CISTPL_IO_8BIT
)paren
)paren
id|link-&gt;io.Attributes1
op_assign
id|IO_DATA_PATH_WIDTH_16
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|io-&gt;flags
op_amp
id|CISTPL_IO_16BIT
)paren
)paren
id|link-&gt;io.Attributes1
op_assign
id|IO_DATA_PATH_WIDTH_8
suffix:semicolon
id|link-&gt;io.IOAddrLines
op_assign
id|io-&gt;flags
op_amp
id|CISTPL_IO_LINES_MASK
suffix:semicolon
id|link-&gt;io.BasePort1
op_assign
id|io-&gt;win
(braket
l_int|0
)braket
dot
id|base
suffix:semicolon
id|link-&gt;io.NumPorts1
op_assign
id|io-&gt;win
(braket
l_int|0
)braket
dot
id|len
suffix:semicolon
r_if
c_cond
(paren
id|io-&gt;nwin
OG
l_int|1
)paren
(brace
id|link-&gt;io.Attributes2
op_assign
id|link-&gt;io.Attributes1
suffix:semicolon
id|link-&gt;io.BasePort2
op_assign
id|io-&gt;win
(braket
l_int|1
)braket
dot
id|base
suffix:semicolon
id|link-&gt;io.NumPorts2
op_assign
id|io-&gt;win
(braket
l_int|1
)braket
dot
id|len
suffix:semicolon
)brace
multiline_comment|/* This reserves IO space but doesn&squot;t actually enable it */
r_if
c_cond
(paren
id|pcmcia_request_io
c_func
(paren
id|link-&gt;handle
comma
op_amp
id|link-&gt;io
)paren
op_ne
l_int|0
)paren
r_goto
id|next_entry
suffix:semicolon
)brace
multiline_comment|/* If we got this far, we&squot;re cool! */
r_break
suffix:semicolon
id|next_entry
suffix:colon
r_if
c_cond
(paren
id|link-&gt;io.NumPorts1
)paren
id|pcmcia_release_io
c_func
(paren
id|link-&gt;handle
comma
op_amp
id|link-&gt;io
)paren
suffix:semicolon
id|last_ret
op_assign
id|pcmcia_get_next_tuple
c_func
(paren
id|handle
comma
op_amp
id|tuple
)paren
suffix:semicolon
r_if
c_cond
(paren
id|last_ret
op_eq
id|CS_NO_MORE_ITEMS
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;GetNextTuple().  No matching CIS configuration, &quot;
l_string|&quot;maybe you need the ignore_cis_vcc=1 parameter.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cs_failed
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Allocate an interrupt line.  Note that this does not assign&n;&t; * a handler to the interrupt, unless the &squot;Handler&squot; member of&n;&t; * the irq structure is initialized.&n;&t; */
r_if
c_cond
(paren
id|link-&gt;conf.Attributes
op_amp
id|CONF_ENABLE_IRQ
)paren
(brace
r_int
id|i
suffix:semicolon
id|link-&gt;irq.Attributes
op_assign
id|IRQ_TYPE_EXCLUSIVE
op_or
id|IRQ_HANDLE_PRESENT
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
id|link-&gt;irq.Handler
op_assign
id|orinoco_interrupt
suffix:semicolon
id|link-&gt;irq.Instance
op_assign
id|dev
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
)brace
multiline_comment|/* We initialize the hermes structure before completing PCMCIA&n;&t; * configuration just in case the interrupt handler gets&n;&t; * called. */
id|hermes_struct_init
c_func
(paren
id|hw
comma
id|link-&gt;io.BasePort1
comma
id|HERMES_IO
comma
id|HERMES_16BIT_REGSPACING
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This actually configures the PCMCIA socket -- setting up&n;&t; * the I/O windows and the interrupt mapping, and putting the&n;&t; * card and host interface into &quot;Memory and IO&quot; mode.&n;&t; */
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
multiline_comment|/* Ok, we have the configuration, prepare to register the netdev */
id|dev-&gt;base_addr
op_assign
id|link-&gt;io.BasePort1
suffix:semicolon
id|dev-&gt;irq
op_assign
id|link-&gt;irq.AssignedIRQ
suffix:semicolon
id|SET_MODULE_OWNER
c_func
(paren
id|dev
)paren
suffix:semicolon
id|card-&gt;node.major
op_assign
id|card-&gt;node.minor
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* register_netdev will give us an ethX name */
id|dev-&gt;name
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* Tell the stack we exist */
r_if
c_cond
(paren
id|register_netdev
c_func
(paren
id|dev
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;orinoco_cs: register_netdev() failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|failed
suffix:semicolon
)brace
multiline_comment|/* At this point, the dev_node_t structure(s) needs to be&n;&t; * initialized and arranged in a linked list at link-&gt;dev. */
id|strcpy
c_func
(paren
id|card-&gt;node.dev_name
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|link-&gt;dev
op_assign
op_amp
id|card-&gt;node
suffix:semicolon
multiline_comment|/* link-&gt;dev being non-NULL is also&n;                                    used to indicate that the&n;                                    net_device has been registered */
id|link-&gt;state
op_and_assign
op_complement
id|DEV_CONFIG_PENDING
suffix:semicolon
multiline_comment|/* Finally, report what we&squot;ve done */
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: index 0x%02x: Vcc %d.%d&quot;
comma
id|dev-&gt;name
comma
id|link-&gt;conf.ConfigIndex
comma
id|link-&gt;conf.Vcc
op_div
l_int|10
comma
id|link-&gt;conf.Vcc
op_mod
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;conf.Vpp1
)paren
id|printk
c_func
(paren
l_string|&quot;, Vpp %d.%d&quot;
comma
id|link-&gt;conf.Vpp1
op_div
l_int|10
comma
id|link-&gt;conf.Vpp1
op_mod
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;conf.Attributes
op_amp
id|CONF_ENABLE_IRQ
)paren
id|printk
c_func
(paren
l_string|&quot;, irq %d&quot;
comma
id|link-&gt;irq.AssignedIRQ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;io.NumPorts1
)paren
id|printk
c_func
(paren
l_string|&quot;, io 0x%04x-0x%04x&quot;
comma
id|link-&gt;io.BasePort1
comma
id|link-&gt;io.BasePort1
op_plus
id|link-&gt;io.NumPorts1
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;io.NumPorts2
)paren
id|printk
c_func
(paren
l_string|&quot; &amp; 0x%04x-0x%04x&quot;
comma
id|link-&gt;io.BasePort2
comma
id|link-&gt;io.BasePort2
op_plus
id|link-&gt;io.NumPorts2
op_minus
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
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
id|orinoco_cs_release
c_func
(paren
id|link
)paren
suffix:semicolon
)brace
multiline_comment|/* orinoco_cs_config */
multiline_comment|/*&n; * After a card is removed, orinoco_cs_release() will unregister the&n; * device, and release the PCMCIA configuration.  If the device is&n; * still open, this will be postponed until it is closed.&n; */
r_static
r_void
DECL|function|orinoco_cs_release
id|orinoco_cs_release
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|link-&gt;priv
suffix:semicolon
r_struct
id|orinoco_private
op_star
id|priv
op_assign
id|dev-&gt;priv
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* We&squot;re committed to taking the device away now, so mark the&n;&t; * hardware as unavailable */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|priv-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|priv-&gt;hw_unavailable
op_increment
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|priv-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t bother checking to see if these succeed or not */
id|pcmcia_release_configuration
c_func
(paren
id|link-&gt;handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;io.NumPorts1
)paren
id|pcmcia_release_io
c_func
(paren
id|link-&gt;handle
comma
op_amp
id|link-&gt;io
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;irq.AssignedIRQ
)paren
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
multiline_comment|/* orinoco_cs_release */
multiline_comment|/*&n; * The card status event handler.  Mostly, this schedules other stuff&n; * to run after an event is received.&n; */
r_static
r_int
DECL|function|orinoco_cs_event
id|orinoco_cs_event
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
r_struct
id|net_device
op_star
id|dev
op_assign
id|link-&gt;priv
suffix:semicolon
r_struct
id|orinoco_private
op_star
id|priv
op_assign
id|dev-&gt;priv
suffix:semicolon
r_struct
id|orinoco_pccard
op_star
id|card
op_assign
id|priv-&gt;card
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
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
(brace
id|orinoco_lock
c_func
(paren
id|priv
comma
op_amp
id|flags
)paren
suffix:semicolon
id|netif_device_detach
c_func
(paren
id|dev
)paren
suffix:semicolon
id|priv-&gt;hw_unavailable
op_increment
suffix:semicolon
id|orinoco_unlock
c_func
(paren
id|priv
comma
op_amp
id|flags
)paren
suffix:semicolon
)brace
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
id|orinoco_cs_config
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
multiline_comment|/* Mark the device as stopped, to block IO until later */
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_CONFIG
)paren
(brace
multiline_comment|/* This is probably racy, but I can&squot;t think of&n;                           a better way, short of rewriting the PCMCIA&n;                           layer to not suck :-( */
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
l_int|0
comma
op_amp
id|card-&gt;hard_reset_in_progress
)paren
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|priv-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|err
op_assign
id|__orinoco_down
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: %s: Error %d downing interface&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|event
op_eq
id|CS_EVENT_PM_SUSPEND
ques
c_cond
l_string|&quot;SUSPEND&quot;
suffix:colon
l_string|&quot;RESET_PHYSICAL&quot;
comma
id|err
)paren
suffix:semicolon
id|netif_device_detach
c_func
(paren
id|dev
)paren
suffix:semicolon
id|priv-&gt;hw_unavailable
op_increment
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|priv-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
id|pcmcia_release_configuration
c_func
(paren
id|link-&gt;handle
)paren
suffix:semicolon
)brace
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
multiline_comment|/* FIXME: should we double check that this is&n;&t;&t;&t; * the same card as we had before */
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
op_logical_neg
id|test_bit
c_func
(paren
l_int|0
comma
op_amp
id|card-&gt;hard_reset_in_progress
)paren
)paren
(brace
id|err
op_assign
id|orinoco_reinit_firmware
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: Error %d re-initializing firmware&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|err
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|priv-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|netif_device_attach
c_func
(paren
id|dev
)paren
suffix:semicolon
id|priv-&gt;hw_unavailable
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;open
op_logical_and
op_logical_neg
id|priv-&gt;hw_unavailable
)paren
(brace
id|err
op_assign
id|__orinoco_up
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: Error %d restarting card&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|err
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|priv-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* orinoco_cs_event */
multiline_comment|/********************************************************************/
multiline_comment|/* Module initialization&t;&t;&t;&t;&t;    */
multiline_comment|/********************************************************************/
multiline_comment|/* Can&squot;t be declared &quot;const&quot; or the whole __initdata section will&n; * become const */
DECL|variable|__initdata
r_static
r_char
id|version
(braket
)braket
id|__initdata
op_assign
l_string|&quot;orinoco_cs.c 0.13e (David Gibson &lt;hermes@gibson.dropbear.id.au&gt; and others)&quot;
suffix:semicolon
DECL|variable|orinoco_driver
r_static
r_struct
id|pcmcia_driver
id|orinoco_driver
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
l_string|&quot;orinoco_cs&quot;
comma
)brace
comma
dot
id|attach
op_assign
id|orinoco_cs_attach
comma
dot
id|detach
op_assign
id|orinoco_cs_detach
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|init_orinoco_cs
id|init_orinoco_cs
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s&bslash;n&quot;
comma
id|version
)paren
suffix:semicolon
r_return
id|pcmcia_register_driver
c_func
(paren
op_amp
id|orinoco_driver
)paren
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|exit_orinoco_cs
id|exit_orinoco_cs
c_func
(paren
r_void
)paren
(brace
id|pcmcia_unregister_driver
c_func
(paren
op_amp
id|orinoco_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev_list
)paren
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;orinoco_cs: Removing leftover devices.&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|dev_list
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|dev_list-&gt;state
op_amp
id|DEV_CONFIG
)paren
id|orinoco_cs_release
c_func
(paren
id|dev_list
)paren
suffix:semicolon
id|orinoco_cs_detach
c_func
(paren
id|dev_list
)paren
suffix:semicolon
)brace
)brace
DECL|variable|init_orinoco_cs
id|module_init
c_func
(paren
id|init_orinoco_cs
)paren
suffix:semicolon
DECL|variable|exit_orinoco_cs
id|module_exit
c_func
(paren
id|exit_orinoco_cs
)paren
suffix:semicolon
eof
