multiline_comment|/*======================================================================&n;&n;    Aironet driver for 4500 and 4800 series cards&n;&n;    This code is released under both the GPL version 2 and BSD licenses.&n;    Either license may be used.  The respective licenses are found at&n;    the end of this file.&n;&n;    This code was developed by Benjamin Reed &lt;breed@users.sourceforge.net&gt;&n;    including portions of which come from the Aironet PC4500&n;    Developer&squot;s Reference Manual and used with permission.  Copyright&n;    (C) 1999 Benjamin Reed.  All Rights Reserved.  Permission to use&n;    code in the Developer&squot;s manual was granted for this driver by&n;    Aironet.&n;&n;    In addition this module was derived from dummy_cs.&n;    The initial developer of dummy_cs is David A. Hinds&n;    &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n;    are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.    &n;    &n;======================================================================*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef __IN_PCMCIA_PACKAGE__
macro_line|#include &lt;pcmcia/k_compat.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;pcmcia/version.h&gt;
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &lt;pcmcia/cisreg.h&gt;
macro_line|#include &lt;pcmcia/ds.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n;   All the PCMCIA modules use PCMCIA_DEBUG to control debugging.  If&n;   you do not define PCMCIA_DEBUG at all, all the debug code will be&n;   left out.  If you compile with PCMCIA_DEBUG=0, the debug code will&n;   be present but disabled -- but it can then be enabled for specific&n;   modules at load time with a &squot;pc_debug=#&squot; option to insmod.&n;*/
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
DECL|variable|version
r_static
r_char
op_star
id|version
op_assign
l_string|&quot;$Revision: 1.2 $&quot;
suffix:semicolon
DECL|macro|DEBUG
mdefine_line|#define DEBUG(n, args...) if (pc_debug&gt;(n)) printk(KERN_DEBUG args);
macro_line|#else
DECL|macro|DEBUG
mdefine_line|#define DEBUG(n, args...)
macro_line|#endif
multiline_comment|/*====================================================================*/
multiline_comment|/* Parameters that can be set with &squot;insmod&squot; */
multiline_comment|/* The old way: bit map of interrupts to choose from */
multiline_comment|/* This means pick from 15, 14, 12, 11, 10, 9, 7, 5, 4, and 3 */
DECL|variable|irq_mask
r_static
id|u_int
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
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Benjamin Reed&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Support for Cisco/Aironet 802.11 wireless ethernet &bslash;&n;                   cards.  This is the module that links the PCMCIA card &bslash;&n;&t;&t;   with the airo module.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;Dual BSD/GPL&quot;
)paren
suffix:semicolon
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;Aironet 4500, 4800 and Cisco 340 PCMCIA cards&quot;
)paren
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
multiline_comment|/*&n;   The event() function is this driver&squot;s Card Services event handler.&n;   It will be called by Card Services when an appropriate card status&n;   event is received.  The config() and release() entry points are&n;   used to configure or release a socket, in response to card&n;   insertion and ejection events.  They are invoked from the airo_cs&n;   event handler. &n;*/
r_struct
id|net_device
op_star
id|init_airo_card
c_func
(paren
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_void
id|stop_airo_card
c_func
(paren
r_struct
id|net_device
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|reset_airo_card
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_static
r_void
id|airo_config
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
suffix:semicolon
r_static
r_void
id|airo_release
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
suffix:semicolon
r_static
r_int
id|airo_event
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
multiline_comment|/*&n;   The attach() and detach() entry points are used to create and destroy&n;   &quot;instances&quot; of the driver, where each instance represents everything&n;   needed to manage one actual PCMCIA card.&n;*/
r_static
id|dev_link_t
op_star
id|airo_attach
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|airo_detach
c_func
(paren
id|dev_link_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;   You&squot;ll also need to prototype all the functions that will actually&n;   be used to talk to your device.  See &squot;pcmem_cs&squot; for a good example&n;   of a fully self-sufficient driver; the other drivers rely more or&n;   less on other parts of the kernel.&n;*/
multiline_comment|/*&n;   The dev_info variable is the &quot;key&quot; that is used to match up this&n;   device driver with appropriate cards, through the card configuration&n;   database.&n;*/
DECL|variable|dev_info
r_static
id|dev_info_t
id|dev_info
op_assign
l_string|&quot;airo_cs&quot;
suffix:semicolon
multiline_comment|/*&n;   A linked list of &quot;instances&quot; of the  aironet device.  Each actual&n;   PCMCIA card corresponds to one device instance, and is described&n;   by one dev_link_t structure (defined in ds.h).&n;&n;   You may not want to use a linked list for this -- for example, the&n;   memory card driver uses an array of dev_link_t pointers, where minor&n;   device numbers are used to derive the corresponding array index.&n;*/
DECL|variable|dev_list
r_static
id|dev_link_t
op_star
id|dev_list
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;   A dev_link_t structure has fields for most things that are needed&n;   to keep track of a socket, but there will usually be some device&n;   specific information that also needs to be kept track of.  The&n;   &squot;priv&squot; pointer in a dev_link_t structure can be used to point to&n;   a device-specific private data structure, like this.&n;&n;   A driver needs to provide a dev_node_t structure for each device&n;   on a card.  In some cases, there is only one device per card (for&n;   example, ethernet cards, modems).  In other cases, there may be&n;   many actual or logical devices (SCSI adapters, memory cards with&n;   multiple partitions).  The dev_node_t structures need to be kept&n;   in a linked list starting at the &squot;dev&squot; field of a dev_link_t&n;   structure.  We allocate them in the card&squot;s private data structure,&n;   because they generally shouldn&squot;t be allocated dynamically.&n;&n;   In this case, we also provide a flag to indicate if a device is&n;   &quot;stopped&quot; due to a power management event, or card ejection.  The&n;   device IO routines can use a flag like this to throttle IO to a&n;   card that is not ready to accept it.&n;*/
DECL|struct|local_info_t
r_typedef
r_struct
id|local_info_t
(brace
DECL|member|node
id|dev_node_t
id|node
suffix:semicolon
DECL|member|eth_dev
r_struct
id|net_device
op_star
id|eth_dev
suffix:semicolon
DECL|typedef|local_info_t
)brace
id|local_info_t
suffix:semicolon
multiline_comment|/*======================================================================&n;  &n;  airo_attach() creates an &quot;instance&quot; of the driver, allocating&n;  local data structures for one device.  The device is registered&n;  with Card Services.&n;  &n;  The dev_link structure is initialized, but we don&squot;t actually&n;  configure the card at this point -- we wait until we receive a&n;  card insertion event.&n;  &n;  ======================================================================*/
DECL|function|airo_attach
r_static
id|dev_link_t
op_star
id|airo_attach
c_func
(paren
r_void
)paren
(brace
id|client_reg_t
id|client_reg
suffix:semicolon
id|dev_link_t
op_star
id|link
suffix:semicolon
id|local_info_t
op_star
id|local
suffix:semicolon
r_int
id|ret
comma
id|i
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;airo_attach()&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Initialize the dev_link_t structure */
id|link
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|dev_link_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|link
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;airo_cs: no memory for new device&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|link
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|dev_link_t
)paren
)paren
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
multiline_comment|/*&n;&t;  General socket configuration defaults can go here.  In this&n;&t;  client, we assume very little, and rely on the CIS for almost&n;&t;  everything.  In most clients, many details (i.e., number, sizes,&n;&t;  and attributes of IO windows) are fixed by the nature of the&n;&t;  device, and can be hard-wired here.&n;&t;*/
id|link-&gt;conf.Attributes
op_assign
l_int|0
suffix:semicolon
id|link-&gt;conf.Vcc
op_assign
l_int|50
suffix:semicolon
id|link-&gt;conf.IntType
op_assign
id|INT_MEMORY_AND_IO
suffix:semicolon
multiline_comment|/* Allocate space for private device-specific data */
id|local
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|local_info_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|local
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;airo_cs: no memory for new device&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
(paren
id|link
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|local
comma
l_int|0
comma
r_sizeof
(paren
id|local_info_t
)paren
)paren
suffix:semicolon
id|link-&gt;priv
op_assign
id|local
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
id|airo_event
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
id|airo_detach
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
multiline_comment|/* airo_attach */
multiline_comment|/*======================================================================&n;  &n;  This deletes a driver &quot;instance&quot;.  The device is de-registered&n;  with Card Services.  If it has been released, all local data&n;  structures are freed.  Otherwise, the structures will be freed&n;  when the device is released.&n;  &n;  ======================================================================*/
DECL|function|airo_detach
r_static
r_void
id|airo_detach
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
l_string|&quot;airo_detach(0x%p)&bslash;n&quot;
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
(brace
id|airo_release
c_func
(paren
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
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
(paren
id|local_info_t
op_star
)paren
id|link-&gt;priv
)paren
op_member_access_from_pointer
id|eth_dev
)paren
(brace
id|stop_airo_card
c_func
(paren
(paren
(paren
id|local_info_t
op_star
)paren
id|link-&gt;priv
)paren
op_member_access_from_pointer
id|eth_dev
comma
l_int|0
)paren
suffix:semicolon
)brace
(paren
(paren
id|local_info_t
op_star
)paren
id|link-&gt;priv
)paren
op_member_access_from_pointer
id|eth_dev
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Break the link with Card Services */
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
multiline_comment|/* Unlink device structure, free pieces */
op_star
id|linkp
op_assign
id|link-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;priv
)paren
(brace
id|kfree
c_func
(paren
id|link-&gt;priv
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|link
)paren
suffix:semicolon
)brace
multiline_comment|/* airo_detach */
multiline_comment|/*======================================================================&n;  &n;  airo_config() is scheduled to run after a CARD_INSERTION event&n;  is received, to configure the PCMCIA socket, and to make the&n;  device available to the system.&n;  &n;  ======================================================================*/
DECL|macro|CS_CHECK
mdefine_line|#define CS_CHECK(fn, args...) &bslash;&n;while ((last_ret=CardServices(last_fn=(fn),args))!=0) goto cs_failed
DECL|macro|CFG_CHECK
mdefine_line|#define CFG_CHECK(fn, args...) &bslash;&n;if (CardServices(fn, args) != 0) goto next_entry
DECL|function|airo_config
r_static
r_void
id|airo_config
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
(brace
id|client_handle_t
id|handle
suffix:semicolon
id|tuple_t
id|tuple
suffix:semicolon
id|cisparse_t
id|parse
suffix:semicolon
id|local_info_t
op_star
id|dev
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
id|win_req_t
id|req
suffix:semicolon
id|memreq_t
id|map
suffix:semicolon
id|handle
op_assign
id|link-&gt;handle
suffix:semicolon
id|dev
op_assign
id|link-&gt;priv
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;airo_config(0x%p)&bslash;n&quot;
comma
id|link
)paren
suffix:semicolon
multiline_comment|/*&n;&t;  This reads the card&squot;s CONFIG tuple to find its configuration&n;&t;  registers.&n;&t;*/
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
multiline_comment|/*&n;&t;  In this loop, we scan the CIS for configuration table entries,&n;&t;  each of which describes a valid card configuration, including&n;&t;  voltage, IO window, memory window, and interrupt settings.&n;&t;  &n;&t;  We make no assumptions about the card to be configured: we use&n;&t;  just the information available in the CIS.  In an ideal world,&n;&t;  this would work for any PCMCIA card, but it requires a complete&n;&t;  and accurate CIS.  In practice, a driver usually &quot;knows&quot; most of&n;&t;  these things without consulting the CIS, and most client drivers&n;&t;  will only use the CIS to fill in implementation-defined details.&n;&t;*/
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
id|cistpl_cftable_entry_t
id|dflt
op_assign
(brace
l_int|0
)brace
suffix:semicolon
id|cistpl_cftable_entry_t
op_star
id|cfg
op_assign
op_amp
(paren
id|parse.cftable_entry
)paren
suffix:semicolon
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
multiline_comment|/*  Note that the CIS values need to be rescaled */
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
id|link-&gt;conf.Vcc
op_assign
id|cfg-&gt;vcc.param
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
id|dflt.vcc.present
op_amp
(paren
l_int|1
op_lshift
id|CISTPL_POWER_VNOM
)paren
)paren
id|link-&gt;conf.Vcc
op_assign
id|dflt.vcc.param
(braket
id|CISTPL_POWER_VNOM
)braket
op_div
l_int|10000
suffix:semicolon
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
)brace
multiline_comment|/* This reserves IO space but doesn&squot;t actually enable it */
id|CFG_CHECK
c_func
(paren
id|RequestIO
comma
id|link-&gt;handle
comma
op_amp
id|link-&gt;io
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;  Now set up a common memory window, if needed.  There is room&n;&t;&t;  in the dev_link_t structure for one memory window handle,&n;&t;&t;  but if the base addresses need to be saved, or if multiple&n;&t;&t;  windows are needed, the info should go in the private data&n;&t;&t;  structure for this device.&n;&t;&t;  &n;&t;&t;  Note that the memory window base is a physical address, and&n;&t;&t;  needs to be mapped to virtual space with ioremap() before it&n;&t;&t;  is used.&n;&t;&t;*/
r_if
c_cond
(paren
(paren
id|cfg-&gt;mem.nwin
OG
l_int|0
)paren
op_logical_or
(paren
id|dflt.mem.nwin
OG
l_int|0
)paren
)paren
(brace
id|cistpl_mem_t
op_star
id|mem
op_assign
(paren
id|cfg-&gt;mem.nwin
)paren
ques
c_cond
op_amp
id|cfg-&gt;mem
suffix:colon
op_amp
id|dflt.mem
suffix:semicolon
id|req.Attributes
op_assign
id|WIN_DATA_WIDTH_16
op_or
id|WIN_MEMORY_TYPE_CM
suffix:semicolon
id|req.Base
op_assign
id|mem-&gt;win
(braket
l_int|0
)braket
dot
id|host_addr
suffix:semicolon
id|req.Size
op_assign
id|mem-&gt;win
(braket
l_int|0
)braket
dot
id|len
suffix:semicolon
id|req.AccessSpeed
op_assign
l_int|0
suffix:semicolon
id|link-&gt;win
op_assign
(paren
id|window_handle_t
)paren
id|link-&gt;handle
suffix:semicolon
id|CFG_CHECK
c_func
(paren
id|RequestWindow
comma
op_amp
id|link-&gt;win
comma
op_amp
id|req
)paren
suffix:semicolon
id|map.Page
op_assign
l_int|0
suffix:semicolon
id|map.CardOffset
op_assign
id|mem-&gt;win
(braket
l_int|0
)braket
dot
id|card_addr
suffix:semicolon
id|CFG_CHECK
c_func
(paren
id|MapMemPage
comma
id|link-&gt;win
comma
op_amp
id|map
)paren
suffix:semicolon
)brace
multiline_comment|/* If we got this far, we&squot;re cool! */
r_break
suffix:semicolon
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
multiline_comment|/*&n;      Allocate an interrupt line.  Note that this does not assign a&n;      handler to the interrupt, unless the &squot;Handler&squot; member of the&n;      irq structure is initialized.&n;    */
r_if
c_cond
(paren
id|link-&gt;conf.Attributes
op_amp
id|CONF_ENABLE_IRQ
)paren
id|CS_CHECK
c_func
(paren
id|RequestIRQ
comma
id|link-&gt;handle
comma
op_amp
id|link-&gt;irq
)paren
suffix:semicolon
multiline_comment|/*&n;&t;  This actually configures the PCMCIA socket -- setting up&n;&t;  the I/O windows and the interrupt mapping, and putting the&n;&t;  card and host interface into &quot;Memory and IO&quot; mode.&n;&t;*/
id|CS_CHECK
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
(paren
(paren
id|local_info_t
op_star
)paren
id|link-&gt;priv
)paren
op_member_access_from_pointer
id|eth_dev
op_assign
id|init_airo_card
c_func
(paren
id|link-&gt;irq.AssignedIRQ
comma
id|link-&gt;io.BasePort1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|local_info_t
op_star
)paren
id|link-&gt;priv
)paren
op_member_access_from_pointer
id|eth_dev
)paren
r_goto
id|cs_failed
suffix:semicolon
multiline_comment|/*&n;&t;  At this point, the dev_node_t structure(s) need to be&n;&t;  initialized and arranged in a linked list at link-&gt;dev.&n;&t;*/
id|strcpy
c_func
(paren
id|dev-&gt;node.dev_name
comma
(paren
(paren
id|local_info_t
op_star
)paren
id|link-&gt;priv
)paren
op_member_access_from_pointer
id|eth_dev-&gt;name
)paren
suffix:semicolon
id|dev-&gt;node.major
op_assign
id|dev-&gt;node.minor
op_assign
l_int|0
suffix:semicolon
id|link-&gt;dev
op_assign
op_amp
id|dev-&gt;node
suffix:semicolon
multiline_comment|/* Finally, report what we&squot;ve done */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: index 0x%02x: Vcc %d.%d&quot;
comma
id|dev-&gt;node.dev_name
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
r_if
c_cond
(paren
id|link-&gt;win
)paren
id|printk
c_func
(paren
l_string|&quot;, mem 0x%06lx-0x%06lx&quot;
comma
id|req.Base
comma
id|req.Base
op_plus
id|req.Size
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
id|airo_release
c_func
(paren
id|link
)paren
suffix:semicolon
)brace
multiline_comment|/* airo_config */
multiline_comment|/*======================================================================&n;  &n;  After a card is removed, airo_release() will unregister the&n;  device, and release the PCMCIA configuration.  If the device is&n;  still open, this will be postponed until it is closed.&n;  &n;  ======================================================================*/
DECL|function|airo_release
r_static
r_void
id|airo_release
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;airo_release(0x%p)&bslash;n&quot;
comma
id|link
)paren
suffix:semicolon
multiline_comment|/*&n;&t;  If the device is currently in use, we won&squot;t release until it&n;&t;  is actually closed, because until then, we can&squot;t be sure that&n;&t;  no one will try to access the device or its data structures.&n;&t;*/
r_if
c_cond
(paren
id|link-&gt;open
)paren
(brace
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;airo_cs: release postponed, &squot;%s&squot; still open&bslash;n&quot;
comma
id|link-&gt;dev-&gt;dev_name
)paren
suffix:semicolon
id|link-&gt;state
op_or_assign
id|DEV_STALE_CONFIG
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Unlink the device chain */
id|link-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t;  In a normal driver, additional code may be needed to release&n;&t;  other kernel data structures associated with this device. &n;&t;*/
multiline_comment|/* Don&squot;t bother checking to see if these succeed or not */
r_if
c_cond
(paren
id|link-&gt;win
)paren
id|CardServices
c_func
(paren
id|ReleaseWindow
comma
id|link-&gt;win
)paren
suffix:semicolon
id|CardServices
c_func
(paren
id|ReleaseConfiguration
comma
id|link-&gt;handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;io.NumPorts1
)paren
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
r_if
c_cond
(paren
id|link-&gt;irq.AssignedIRQ
)paren
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
id|DEV_STALE_CONFIG
)paren
id|airo_detach
c_func
(paren
id|link
)paren
suffix:semicolon
)brace
multiline_comment|/*======================================================================&n;  &n;  The card status event handler.  Mostly, this schedules other&n;  stuff to run after an event is received.&n;&n;  When a CARD_REMOVAL event is received, we immediately set a&n;  private flag to block future accesses to this device.  All the&n;  functions that actually access the device should check this flag&n;  to make sure the card is still present.&n;  &n;  ======================================================================*/
DECL|function|airo_event
r_static
r_int
id|airo_event
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
id|local_info_t
op_star
id|local
op_assign
id|link-&gt;priv
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;airo_event(0x%06x)&bslash;n&quot;
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
(brace
id|netif_device_detach
c_func
(paren
id|local-&gt;eth_dev
)paren
suffix:semicolon
id|airo_release
c_func
(paren
id|link
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
id|airo_config
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
(brace
id|netif_device_detach
c_func
(paren
id|local-&gt;eth_dev
)paren
suffix:semicolon
id|CardServices
c_func
(paren
id|ReleaseConfiguration
comma
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
id|reset_airo_card
c_func
(paren
id|local-&gt;eth_dev
)paren
suffix:semicolon
id|netif_device_attach
c_func
(paren
id|local-&gt;eth_dev
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
multiline_comment|/* airo_event */
DECL|variable|airo_driver
r_static
r_struct
id|pcmcia_driver
id|airo_driver
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
l_string|&quot;airo_cs&quot;
comma
)brace
comma
dot
id|attach
op_assign
id|airo_attach
comma
dot
id|detach
op_assign
id|airo_detach
comma
)brace
suffix:semicolon
DECL|function|airo_cs_init
r_static
r_int
id|airo_cs_init
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
id|airo_driver
)paren
suffix:semicolon
)brace
DECL|function|airo_cs_cleanup
r_static
r_void
id|airo_cs_cleanup
c_func
(paren
r_void
)paren
(brace
id|pcmcia_unregister_driver
c_func
(paren
op_amp
id|airo_driver
)paren
suffix:semicolon
multiline_comment|/* XXX: this really needs to move into generic code.. */
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
id|airo_release
c_func
(paren
id|dev_list
)paren
suffix:semicolon
id|airo_detach
c_func
(paren
id|dev_list
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;    This program is free software; you can redistribute it and/or&n;    modify it under the terms of the GNU General Public License&n;    as published by the Free Software Foundation; either version 2&n;    of the License, or (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    In addition:&n;&n;    Redistribution and use in source and binary forms, with or without&n;    modification, are permitted provided that the following conditions&n;    are met:&n;&n;    1. Redistributions of source code must retain the above copyright&n;       notice, this list of conditions and the following disclaimer.&n;    2. Redistributions in binary form must reproduce the above copyright&n;       notice, this list of conditions and the following disclaimer in the&n;       documentation and/or other materials provided with the distribution.&n;    3. The name of the author may not be used to endorse or promote&n;       products derived from this software without specific prior written&n;       permission.&n;&n;    THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS&squot;&squot; AND ANY EXPRESS OR&n;    IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED&n;    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n;    ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,&n;    INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES&n;    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR&n;    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n;    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n;    STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n;    IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n;    POSSIBILITY OF SUCH DAMAGE.    &n;*/
DECL|variable|airo_cs_init
id|module_init
c_func
(paren
id|airo_cs_init
)paren
suffix:semicolon
DECL|variable|airo_cs_cleanup
id|module_exit
c_func
(paren
id|airo_cs_cleanup
)paren
suffix:semicolon
eof
