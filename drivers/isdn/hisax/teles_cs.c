multiline_comment|/* $Id: teles_cs.c,v 1.1.2.2 2004/01/25 15:07:06 keil Exp $ */
multiline_comment|/*======================================================================&n;&n;    A teles S0 PCMCIA client driver&n;&n;    Based on skeleton by David Hinds, dhinds@allegro.stanford.edu&n;    Written by Christof Petig, christof.petig@wtal.de&n;    &n;    Also inspired by ELSA PCMCIA driver &n;    by Klaus Lichtenwalder &lt;Lichtenwalder@ACM.org&gt;&n;    &n;    Extentions to new hisax_pcmcia by Karsten Keil&n;&n;    minor changes to be compatible with kernel 2.4.x&n;    by Jan.Schubert@GMX.li&n;&n;======================================================================*/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;pcmcia/version.h&gt;
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &lt;pcmcia/cisreg.h&gt;
macro_line|#include &lt;pcmcia/ds.h&gt;
macro_line|#include &quot;hisax_cfg.h&quot;
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ISDN4Linux: PCMCIA client driver for Teles PCMCIA cards&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Christof Petig, christof.petig@wtal.de, Karsten Keil, kkeil@suse.de&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;   All the PCMCIA modules use PCMCIA_DEBUG to control debugging.  If&n;   you do not define PCMCIA_DEBUG at all, all the debug code will be&n;   left out.  If you compile with PCMCIA_DEBUG=0, the debug code will&n;   be present but disabled -- but it can then be enabled for specific&n;   modules at load time with a &squot;pc_debug=#&squot; option to insmod.&n;*/
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
mdefine_line|#define DEBUG(n, args...) if (pc_debug&gt;(n)) printk(KERN_DEBUG args);
DECL|variable|version
r_static
r_char
op_star
id|version
op_assign
l_string|&quot;teles_cs.c 2.10 2002/07/30 22:23:34 kkeil&quot;
suffix:semicolon
macro_line|#else
DECL|macro|DEBUG
mdefine_line|#define DEBUG(n, args...)
macro_line|#endif
multiline_comment|/*====================================================================*/
multiline_comment|/* Parameters that can be set with &squot;insmod&squot; */
multiline_comment|/* Bit map of interrupts to choose from, the old way */
multiline_comment|/* This means pick from 15, 14, 12, 11, 10, 9, 7, 5, 4, 3 */
DECL|variable|irq_mask
r_static
id|u_long
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
id|module_param
c_func
(paren
id|irq_mask
comma
id|ulong
comma
l_int|0
)paren
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
DECL|variable|protocol
r_static
r_int
id|protocol
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* EURO-ISDN Default */
id|module_param
c_func
(paren
id|protocol
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*====================================================================*/
multiline_comment|/*&n;   The event() function is this driver&squot;s Card Services event handler.&n;   It will be called by Card Services when an appropriate card status&n;   event is received.  The config() and release() entry points are&n;   used to configure or release a socket, in response to card insertion&n;   and ejection events.  They are invoked from the teles_cs event&n;   handler.&n;*/
r_static
r_void
id|teles_cs_config
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
suffix:semicolon
r_static
r_void
id|teles_cs_release
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
suffix:semicolon
r_static
r_int
id|teles_cs_event
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
id|teles_attach
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|teles_detach
c_func
(paren
id|dev_link_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;   The dev_info variable is the &quot;key&quot; that is used to match up this&n;   device driver with appropriate cards, through the card configuration&n;   database.&n;*/
DECL|variable|dev_info
r_static
id|dev_info_t
id|dev_info
op_assign
l_string|&quot;teles_cs&quot;
suffix:semicolon
multiline_comment|/*&n;   A linked list of &quot;instances&quot; of the teles_cs device.  Each actual&n;   PCMCIA card corresponds to one device instance, and is described&n;   by one dev_link_t structure (defined in ds.h).&n;&n;   You may not want to use a linked list for this -- for example, the&n;   memory card driver uses an array of dev_link_t pointers, where minor&n;   device numbers are used to derive the corresponding array index.&n;*/
DECL|variable|dev_list
r_static
id|dev_link_t
op_star
id|dev_list
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;   A dev_link_t structure has fields for most things that are needed&n;   to keep track of a socket, but there will usually be some device&n;   specific information that also needs to be kept track of.  The&n;   &squot;priv&squot; pointer in a dev_link_t structure can be used to point to&n;   a device-specific private data structure, like this.&n;&n;   To simplify the data structure handling, we actually include the&n;   dev_link_t structure in the device&squot;s private data structure.&n;&n;   A driver needs to provide a dev_node_t structure for each device&n;   on a card.  In some cases, there is only one device per card (for&n;   example, ethernet cards, modems).  In other cases, there may be&n;   many actual or logical devices (SCSI adapters, memory cards with&n;   multiple partitions).  The dev_node_t structures need to be kept&n;   in a linked list starting at the &squot;dev&squot; field of a dev_link_t&n;   structure.  We allocate them in the card&squot;s private data structure,&n;   because they generally shouldn&squot;t be allocated dynamically.&n;   In this case, we also provide a flag to indicate if a device is&n;   &quot;stopped&quot; due to a power management event, or card ejection.  The&n;   device IO routines can use a flag like this to throttle IO to a&n;   card that is not ready to accept it.&n;*/
DECL|struct|local_info_t
r_typedef
r_struct
id|local_info_t
(brace
DECL|member|link
id|dev_link_t
id|link
suffix:semicolon
DECL|member|node
id|dev_node_t
id|node
suffix:semicolon
DECL|member|busy
r_int
id|busy
suffix:semicolon
DECL|member|cardnr
r_int
id|cardnr
suffix:semicolon
DECL|typedef|local_info_t
)brace
id|local_info_t
suffix:semicolon
multiline_comment|/*======================================================================&n;&n;    teles_attach() creates an &quot;instance&quot; of the driver, allocatingx&n;    local data structures for one device.  The device is registered&n;    with Card Services.&n;&n;    The dev_link structure is initialized, but we don&squot;t actually&n;    configure the card at this point -- we wait until we receive a&n;    card insertion event.&n;&n;======================================================================*/
DECL|function|teles_attach
r_static
id|dev_link_t
op_star
id|teles_attach
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
l_string|&quot;teles_attach()&bslash;n&quot;
)paren
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
r_return
l_int|NULL
suffix:semicolon
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
id|local-&gt;cardnr
op_assign
op_minus
l_int|1
suffix:semicolon
id|link
op_assign
op_amp
id|local-&gt;link
suffix:semicolon
id|link-&gt;priv
op_assign
id|local
suffix:semicolon
multiline_comment|/* Interrupt setup */
id|link-&gt;irq.Attributes
op_assign
id|IRQ_TYPE_DYNAMIC_SHARING
op_or
id|IRQ_FIRST_SHARED
suffix:semicolon
id|link-&gt;irq.IRQInfo1
op_assign
id|IRQ_INFO2_VALID
op_or
id|IRQ_LEVEL_ID
op_or
id|IRQ_SHARE_ID
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
multiline_comment|/*&n;      General socket configuration defaults can go here.  In this&n;      client, we assume very little, and rely on the CIS for almost&n;      everything.  In most clients, many details (i.e., number, sizes,&n;      and attributes of IO windows) are fixed by the nature of the&n;      device, and can be hard-wired here.&n;    */
id|link-&gt;io.NumPorts1
op_assign
l_int|96
suffix:semicolon
id|link-&gt;io.Attributes1
op_assign
id|IO_DATA_PATH_WIDTH_AUTO
suffix:semicolon
id|link-&gt;io.IOAddrLines
op_assign
l_int|5
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
id|teles_cs_event
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
id|teles_detach
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
multiline_comment|/* teles_attach */
multiline_comment|/*======================================================================&n;&n;    This deletes a driver &quot;instance&quot;.  The device is de-registered&n;    with Card Services.  If it has been released, all local data&n;    structures are freed.  Otherwise, the structures will be freed&n;    when the device is released.&n;&n;======================================================================*/
DECL|function|teles_detach
r_static
r_void
id|teles_detach
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
id|local_info_t
op_star
id|info
op_assign
id|link-&gt;priv
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;teles_detach(0x%p)&bslash;n&quot;
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
id|teles_cs_release
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
(brace
id|ret
op_assign
id|pcmcia_deregister_client
c_func
(paren
id|link-&gt;handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|CS_SUCCESS
)paren
id|cs_error
c_func
(paren
id|link-&gt;handle
comma
id|DeregisterClient
comma
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/* Unlink device structure and free it */
op_star
id|linkp
op_assign
id|link-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
)brace
multiline_comment|/* teles_detach */
multiline_comment|/*======================================================================&n;&n;    teles_cs_config() is scheduled to run after a CARD_INSERTION event&n;    is received, to configure the PCMCIA socket, and to make the&n;    device available to the system.&n;&n;======================================================================*/
DECL|function|get_tuple
r_static
r_int
id|get_tuple
c_func
(paren
id|client_handle_t
id|handle
comma
id|tuple_t
op_star
id|tuple
comma
id|cisparse_t
op_star
id|parse
)paren
(brace
r_int
id|i
op_assign
id|pcmcia_get_tuple_data
c_func
(paren
id|handle
comma
id|tuple
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
id|CS_SUCCESS
)paren
r_return
id|i
suffix:semicolon
r_return
id|pcmcia_parse_tuple
c_func
(paren
id|handle
comma
id|tuple
comma
id|parse
)paren
suffix:semicolon
)brace
DECL|function|first_tuple
r_static
r_int
id|first_tuple
c_func
(paren
id|client_handle_t
id|handle
comma
id|tuple_t
op_star
id|tuple
comma
id|cisparse_t
op_star
id|parse
)paren
(brace
r_int
id|i
op_assign
id|pcmcia_get_first_tuple
c_func
(paren
id|handle
comma
id|tuple
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
id|CS_SUCCESS
)paren
r_return
id|i
suffix:semicolon
r_return
id|get_tuple
c_func
(paren
id|handle
comma
id|tuple
comma
id|parse
)paren
suffix:semicolon
)brace
DECL|function|next_tuple
r_static
r_int
id|next_tuple
c_func
(paren
id|client_handle_t
id|handle
comma
id|tuple_t
op_star
id|tuple
comma
id|cisparse_t
op_star
id|parse
)paren
(brace
r_int
id|i
op_assign
id|pcmcia_get_next_tuple
c_func
(paren
id|handle
comma
id|tuple
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
id|CS_SUCCESS
)paren
r_return
id|i
suffix:semicolon
r_return
id|get_tuple
c_func
(paren
id|handle
comma
id|tuple
comma
id|parse
)paren
suffix:semicolon
)brace
DECL|function|teles_cs_config
r_static
r_void
id|teles_cs_config
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
id|i
comma
id|j
comma
id|last_fn
suffix:semicolon
id|u_short
id|buf
(braket
l_int|128
)braket
suffix:semicolon
id|cistpl_cftable_entry_t
op_star
id|cf
op_assign
op_amp
id|parse.cftable_entry
suffix:semicolon
id|IsdnCard_t
id|icard
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;teles_config(0x%p)&bslash;n&quot;
comma
id|link
)paren
suffix:semicolon
id|handle
op_assign
id|link-&gt;handle
suffix:semicolon
id|dev
op_assign
id|link-&gt;priv
suffix:semicolon
multiline_comment|/*&n;       This reads the card&squot;s CONFIG tuple to find its configuration&n;       registers.&n;    */
id|tuple.DesiredTuple
op_assign
id|CISTPL_CONFIG
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
l_int|255
suffix:semicolon
id|tuple.TupleOffset
op_assign
l_int|0
suffix:semicolon
id|tuple.Attributes
op_assign
l_int|0
suffix:semicolon
id|i
op_assign
id|first_tuple
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
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
id|CS_SUCCESS
)paren
(brace
id|last_fn
op_assign
id|ParseTuple
suffix:semicolon
r_goto
id|cs_failed
suffix:semicolon
)brace
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
id|tuple.TupleData
op_assign
(paren
id|cisdata_t
op_star
)paren
id|buf
suffix:semicolon
id|tuple.TupleOffset
op_assign
l_int|0
suffix:semicolon
id|tuple.TupleDataMax
op_assign
l_int|255
suffix:semicolon
id|tuple.Attributes
op_assign
l_int|0
suffix:semicolon
id|tuple.DesiredTuple
op_assign
id|CISTPL_CFTABLE_ENTRY
suffix:semicolon
id|i
op_assign
id|first_tuple
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
suffix:semicolon
r_while
c_loop
(paren
id|i
op_eq
id|CS_SUCCESS
)paren
(brace
r_if
c_cond
(paren
(paren
id|cf-&gt;io.nwin
OG
l_int|0
)paren
op_logical_and
id|cf-&gt;io.win
(braket
l_int|0
)braket
dot
id|base
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;(teles_cs: looks like the 96 model)&bslash;n&quot;
)paren
suffix:semicolon
id|link-&gt;conf.ConfigIndex
op_assign
id|cf-&gt;index
suffix:semicolon
id|link-&gt;io.BasePort1
op_assign
id|cf-&gt;io.win
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
id|link-&gt;handle
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
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;(teles_cs: looks like the 97 model)&bslash;n&quot;
)paren
suffix:semicolon
id|link-&gt;conf.ConfigIndex
op_assign
id|cf-&gt;index
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|j
op_assign
l_int|0x2f0
suffix:semicolon
id|j
OG
l_int|0x100
suffix:semicolon
id|j
op_sub_assign
l_int|0x10
)paren
(brace
id|link-&gt;io.BasePort1
op_assign
id|j
suffix:semicolon
id|i
op_assign
id|pcmcia_request_io
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
id|i
op_eq
id|CS_SUCCESS
)paren
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|i
op_assign
id|next_tuple
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
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_ne
id|CS_SUCCESS
)paren
(brace
id|last_fn
op_assign
id|RequestIO
suffix:semicolon
r_goto
id|cs_failed
suffix:semicolon
)brace
id|i
op_assign
id|pcmcia_request_irq
c_func
(paren
id|link-&gt;handle
comma
op_amp
id|link-&gt;irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
id|CS_SUCCESS
)paren
(brace
id|link-&gt;irq.AssignedIRQ
op_assign
l_int|0
suffix:semicolon
id|last_fn
op_assign
id|RequestIRQ
suffix:semicolon
r_goto
id|cs_failed
suffix:semicolon
)brace
id|i
op_assign
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
id|i
op_ne
id|CS_SUCCESS
)paren
(brace
id|last_fn
op_assign
id|RequestConfiguration
suffix:semicolon
r_goto
id|cs_failed
suffix:semicolon
)brace
multiline_comment|/* At this point, the dev_node_t structure(s) should be&n;       initialized and arranged in a linked list at link-&gt;dev. */
multiline_comment|/*  */
id|sprintf
c_func
(paren
id|dev-&gt;node.dev_name
comma
l_string|&quot;teles&quot;
)paren
suffix:semicolon
id|dev-&gt;node.major
op_assign
id|dev-&gt;node.minor
op_assign
l_int|0x0
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
id|icard.para
(braket
l_int|0
)braket
op_assign
id|link-&gt;irq.AssignedIRQ
suffix:semicolon
id|icard.para
(braket
l_int|1
)braket
op_assign
id|link-&gt;io.BasePort1
suffix:semicolon
id|icard.protocol
op_assign
id|protocol
suffix:semicolon
id|icard.typ
op_assign
id|ISDN_CTYPE_TELESPCMCIA
suffix:semicolon
id|i
op_assign
id|hisax_init_pcmcia
c_func
(paren
id|link
comma
op_amp
(paren
(paren
(paren
id|local_info_t
op_star
)paren
id|link-&gt;priv
)paren
op_member_access_from_pointer
id|busy
)paren
comma
op_amp
id|icard
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;teles_cs: failed to initialize Teles PCMCIA %d at i/o %#x&bslash;n&quot;
comma
id|i
comma
id|link-&gt;io.BasePort1
)paren
suffix:semicolon
id|teles_cs_release
c_func
(paren
id|link
)paren
suffix:semicolon
)brace
r_else
(paren
(paren
id|local_info_t
op_star
)paren
id|link-&gt;priv
)paren
op_member_access_from_pointer
id|cardnr
op_assign
id|i
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
id|i
)paren
suffix:semicolon
id|teles_cs_release
c_func
(paren
id|link
)paren
suffix:semicolon
)brace
multiline_comment|/* teles_cs_config */
multiline_comment|/*======================================================================&n;&n;    After a card is removed, teles_cs_release() will unregister the net&n;    device, and release the PCMCIA configuration.  If the device is&n;    still open, this will be postponed until it is closed.&n;&n;======================================================================*/
DECL|function|teles_cs_release
r_static
r_void
id|teles_cs_release
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
(brace
id|local_info_t
op_star
id|local
op_assign
id|link-&gt;priv
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;teles_cs_release(0x%p)&bslash;n&quot;
comma
id|link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|local
)paren
(brace
r_if
c_cond
(paren
id|local-&gt;cardnr
op_ge
l_int|0
)paren
(brace
multiline_comment|/* no unregister function with hisax */
id|HiSax_closecard
c_func
(paren
id|local-&gt;cardnr
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Unlink the device chain */
id|link-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Don&squot;t bother checking to see if these succeed or not */
r_if
c_cond
(paren
id|link-&gt;win
)paren
id|pcmcia_release_window
c_func
(paren
id|link-&gt;win
)paren
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
multiline_comment|/* teles_cs_release */
multiline_comment|/*======================================================================&n;&n;    The card status event handler.  Mostly, this schedules other&n;    stuff to run after an event is received.  A CARD_REMOVAL event&n;    also sets some flags to discourage the net drivers from trying&n;    to talk to the card any more.&n;&n;    When a CARD_REMOVAL event is received, we immediately set a flag&n;    to block future accesses to this device.  All the functions that&n;    actually access the device should check this flag to make sure&n;    the card is still present.&n;&n;======================================================================*/
DECL|function|teles_cs_event
r_static
r_int
id|teles_cs_event
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
id|dev
op_assign
id|link-&gt;priv
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;teles_cs_event(%d)&bslash;n&quot;
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
(paren
(paren
id|local_info_t
op_star
)paren
id|link-&gt;priv
)paren
op_member_access_from_pointer
id|busy
op_assign
l_int|1
suffix:semicolon
id|teles_cs_release
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
id|teles_cs_config
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
id|dev-&gt;busy
op_assign
l_int|1
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
id|pcmcia_request_configuration
c_func
(paren
id|link-&gt;handle
comma
op_amp
id|link-&gt;conf
)paren
suffix:semicolon
id|dev-&gt;busy
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* teles_cs_event */
DECL|variable|teles_cs_driver
r_static
r_struct
id|pcmcia_driver
id|teles_cs_driver
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
l_string|&quot;teles_cs&quot;
comma
)brace
comma
dot
id|attach
op_assign
id|teles_attach
comma
dot
id|detach
op_assign
id|teles_detach
comma
)brace
suffix:semicolon
DECL|function|init_teles_cs
r_static
r_int
id|__init
id|init_teles_cs
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
id|teles_cs_driver
)paren
suffix:semicolon
)brace
DECL|function|exit_teles_cs
r_static
r_void
id|__exit
id|exit_teles_cs
c_func
(paren
r_void
)paren
(brace
id|pcmcia_unregister_driver
c_func
(paren
op_amp
id|teles_cs_driver
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
DECL|variable|init_teles_cs
id|module_init
c_func
(paren
id|init_teles_cs
)paren
suffix:semicolon
DECL|variable|exit_teles_cs
id|module_exit
c_func
(paren
id|exit_teles_cs
)paren
suffix:semicolon
eof
