multiline_comment|/*&n; * PCMCIA client driver for AVM A1 / Fritz!PCMCIA&n; *&n; * Author       Carsten Paeth&n; * Copyright    1998-2001 by Carsten Paeth &lt;calle@calle.in-berlin.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;pcmcia/version.h&gt;
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &lt;pcmcia/ds.h&gt;
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ISDN4Linux: PCMCIA client driver for AVM A1/Fritz!PCMCIA cards&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Carsten Paeth&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
r_int
id|avm_a1_init_pcmcia
c_func
(paren
r_void
op_star
id|pcm_iob
comma
r_int
id|pcm_irq
comma
r_int
op_star
id|busy_flag
comma
r_int
id|prot
)paren
suffix:semicolon
r_void
id|HiSax_closecard
c_func
(paren
r_int
id|cardnr
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
id|MODULE_PARM
c_func
(paren
id|pc_debug
comma
l_string|&quot;i&quot;
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
l_string|&quot;avma1_cs.c 1.00 1998/01/23 10:00:00 (Carsten Paeth)&quot;
suffix:semicolon
macro_line|#else
DECL|macro|DEBUG
mdefine_line|#define DEBUG(n, args...)
macro_line|#endif
multiline_comment|/*====================================================================*/
multiline_comment|/* Parameters that can be set with &squot;insmod&squot; */
DECL|variable|default_irq_list
r_static
r_int
id|default_irq_list
(braket
l_int|11
)braket
op_assign
(brace
l_int|15
comma
l_int|13
comma
l_int|12
comma
l_int|11
comma
l_int|10
comma
l_int|9
comma
l_int|7
comma
l_int|5
comma
l_int|4
comma
l_int|3
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|irq_list
r_static
r_int
id|irq_list
(braket
l_int|11
)braket
op_assign
(brace
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|isdnprot
r_static
r_int
id|isdnprot
op_assign
l_int|2
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|irq_list
comma
l_string|&quot;1-11i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|isdnprot
comma
l_string|&quot;1-4i&quot;
)paren
suffix:semicolon
multiline_comment|/*====================================================================*/
multiline_comment|/*&n;   The event() function is this driver&squot;s Card Services event handler.&n;   It will be called by Card Services when an appropriate card status&n;   event is received.  The config() and release() entry points are&n;   used to configure or release a socket, in response to card insertion&n;   and ejection events.  They are invoked from the skeleton event&n;   handler.&n;*/
r_static
r_void
id|avma1cs_config
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
suffix:semicolon
r_static
r_void
id|avma1cs_release
c_func
(paren
id|u_long
id|arg
)paren
suffix:semicolon
r_static
r_int
id|avma1cs_event
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
id|avma1cs_attach
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|avma1cs_detach
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
l_string|&quot;avma1_cs&quot;
suffix:semicolon
multiline_comment|/*&n;   A linked list of &quot;instances&quot; of the skeleton device.  Each actual&n;   PCMCIA card corresponds to one device instance, and is described&n;   by one dev_link_t structure (defined in ds.h).&n;&n;   You may not want to use a linked list for this -- for example, the&n;   memory card driver uses an array of dev_link_t pointers, where minor&n;   device numbers are used to derive the corresponding array index.&n;*/
DECL|variable|dev_list
r_static
id|dev_link_t
op_star
id|dev_list
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;   A dev_link_t structure has fields for most things that are needed&n;   to keep track of a socket, but there will usually be some device&n;   specific information that also needs to be kept track of.  The&n;   &squot;priv&squot; pointer in a dev_link_t structure can be used to point to&n;   a device-specific private data structure, like this.&n;&n;   A driver needs to provide a dev_node_t structure for each device&n;   on a card.  In some cases, there is only one device per card (for&n;   example, ethernet cards, modems).  In other cases, there may be&n;   many actual or logical devices (SCSI adapters, memory cards with&n;   multiple partitions).  The dev_node_t structures need to be kept&n;   in a linked list starting at the &squot;dev&squot; field of a dev_link_t&n;   structure.  We allocate them in the card&squot;s private data structure,&n;   because they generally can&squot;t be allocated dynamically.&n;*/
DECL|struct|local_info_t
r_typedef
r_struct
id|local_info_t
(brace
DECL|member|node
id|dev_node_t
id|node
suffix:semicolon
DECL|typedef|local_info_t
)brace
id|local_info_t
suffix:semicolon
multiline_comment|/*======================================================================&n;&n;    avma1cs_attach() creates an &quot;instance&quot; of the driver, allocating&n;    local data structures for one device.  The device is registered&n;    with Card Services.&n;&n;    The dev_link structure is initialized, but we don&squot;t actually&n;    configure the card at this point -- we wait until we receive a&n;    card insertion event.&n;    &n;======================================================================*/
DECL|function|avma1cs_attach
r_static
id|dev_link_t
op_star
id|avma1cs_attach
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
l_string|&quot;avma1cs_attach()&bslash;n&quot;
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
id|link-&gt;release.function
op_assign
op_amp
id|avma1cs_release
suffix:semicolon
id|link-&gt;release.data
op_assign
(paren
id|u_long
)paren
id|link
suffix:semicolon
multiline_comment|/* The io structure describes IO port mapping */
id|link-&gt;io.NumPorts1
op_assign
l_int|16
suffix:semicolon
id|link-&gt;io.Attributes1
op_assign
id|IO_DATA_PATH_WIDTH_8
suffix:semicolon
id|link-&gt;io.NumPorts2
op_assign
l_int|16
suffix:semicolon
id|link-&gt;io.Attributes2
op_assign
id|IO_DATA_PATH_WIDTH_16
suffix:semicolon
id|link-&gt;io.IOAddrLines
op_assign
l_int|5
suffix:semicolon
multiline_comment|/* Interrupt setup */
id|link-&gt;irq.Attributes
op_assign
id|IRQ_TYPE_EXCLUSIVE
suffix:semicolon
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
suffix:semicolon
r_if
c_cond
(paren
id|irq_list
(braket
l_int|0
)braket
op_ne
op_minus
l_int|1
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
template_param
l_int|0
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
)brace
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
template_param
l_int|0
suffix:semicolon
id|i
op_increment
)paren
id|link-&gt;irq.IRQInfo2
op_or_assign
l_int|1
op_lshift
id|default_irq_list
(braket
id|i
)braket
suffix:semicolon
)brace
multiline_comment|/* General socket configuration */
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
id|avma1cs_event
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
id|avma1cs_detach
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
multiline_comment|/* avma1cs_attach */
multiline_comment|/*======================================================================&n;&n;    This deletes a driver &quot;instance&quot;.  The device is de-registered&n;    with Card Services.  If it has been released, all local data&n;    structures are freed.  Otherwise, the structures will be freed&n;    when the device is released.&n;&n;======================================================================*/
DECL|function|avma1cs_detach
r_static
r_void
id|avma1cs_detach
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
l_string|&quot;avma1cs_detach(0x%p)&bslash;n&quot;
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
multiline_comment|/*&n;       If the device is currently configured and active, we won&squot;t&n;       actually delete it yet.  Instead, it is marked so that when&n;       the release() function is called, that will trigger a proper&n;       detach().&n;    */
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_CONFIG
)paren
(brace
macro_line|#ifdef PCMCIA_DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;avma1_cs: detach postponed, &squot;%s&squot; &quot;
l_string|&quot;still locked&bslash;n&quot;
comma
id|link-&gt;dev-&gt;dev_name
)paren
suffix:semicolon
macro_line|#endif
id|link-&gt;state
op_or_assign
id|DEV_STALE_LINK
suffix:semicolon
r_return
suffix:semicolon
)brace
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
multiline_comment|/* avma1cs_detach */
multiline_comment|/*======================================================================&n;&n;    avma1cs_config() is scheduled to run after a CARD_INSERTION event&n;    is received, to configure the PCMCIA socket, and to make the&n;    ethernet device available to the system.&n;    &n;======================================================================*/
DECL|function|get_tuple
r_static
r_int
id|get_tuple
c_func
(paren
r_int
id|fn
comma
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
suffix:semicolon
id|i
op_assign
id|CardServices
c_func
(paren
id|fn
comma
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
id|i
op_assign
id|CardServices
c_func
(paren
id|GetTupleData
comma
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
id|CardServices
c_func
(paren
id|ParseTuple
comma
id|handle
comma
id|tuple
comma
id|parse
)paren
suffix:semicolon
)brace
DECL|macro|first_tuple
mdefine_line|#define first_tuple(a, b, c) get_tuple(GetFirstTuple, a, b, c)
DECL|macro|next_tuple
mdefine_line|#define next_tuple(a, b, c) get_tuple(GetNextTuple, a, b, c)
DECL|function|avma1cs_config
r_static
r_void
id|avma1cs_config
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
id|cistpl_cftable_entry_t
op_star
id|cf
op_assign
op_amp
id|parse.cftable_entry
suffix:semicolon
id|local_info_t
op_star
id|dev
suffix:semicolon
r_int
id|i
suffix:semicolon
id|u8
id|buf
(braket
l_int|64
)braket
suffix:semicolon
r_char
id|devname
(braket
l_int|128
)braket
suffix:semicolon
r_int
id|busy
op_assign
l_int|0
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
l_string|&quot;avma1cs_config(0x%p)&bslash;n&quot;
comma
id|link
)paren
suffix:semicolon
multiline_comment|/*&n;       This reads the card&squot;s CONFIG tuple to find its configuration&n;       registers.&n;    */
r_do
(brace
id|tuple.DesiredTuple
op_assign
id|CISTPL_CONFIG
suffix:semicolon
id|i
op_assign
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
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
id|CS_SUCCESS
)paren
r_break
suffix:semicolon
id|tuple.TupleData
op_assign
id|buf
suffix:semicolon
id|tuple.TupleDataMax
op_assign
l_int|64
suffix:semicolon
id|tuple.TupleOffset
op_assign
l_int|0
suffix:semicolon
id|i
op_assign
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
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
id|CS_SUCCESS
)paren
r_break
suffix:semicolon
id|i
op_assign
id|CardServices
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
id|i
op_ne
id|CS_SUCCESS
)paren
r_break
suffix:semicolon
id|link-&gt;conf.ConfigBase
op_assign
id|parse.config.base
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|0
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
id|cs_error
c_func
(paren
id|link-&gt;handle
comma
id|ParseTuple
comma
id|i
)paren
suffix:semicolon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_CONFIG_PENDING
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Configure card */
id|link-&gt;state
op_or_assign
id|DEV_CONFIG
suffix:semicolon
r_do
(brace
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
l_int|254
suffix:semicolon
id|tuple.TupleOffset
op_assign
l_int|0
suffix:semicolon
id|tuple.DesiredTuple
op_assign
id|CISTPL_VERS_1
suffix:semicolon
id|devname
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
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
op_logical_and
id|parse.version_1.ns
OG
l_int|1
)paren
(brace
id|strncpy
c_func
(paren
id|devname
comma
id|parse.version_1.str
op_plus
id|parse.version_1.ofs
(braket
l_int|1
)braket
comma
r_sizeof
(paren
id|devname
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;         * find IO port&n;         */
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
id|cf-&gt;io.nwin
OG
l_int|0
)paren
(brace
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
id|link-&gt;io.NumPorts1
op_assign
id|cf-&gt;io.win
(braket
l_int|0
)braket
dot
id|len
suffix:semicolon
id|link-&gt;io.NumPorts2
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;avma1_cs: testing i/o %#x-%#x&bslash;n&quot;
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
id|i
op_assign
id|CardServices
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
r_if
c_cond
(paren
id|i
op_eq
id|CS_SUCCESS
)paren
r_goto
id|found_port
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
id|found_port
suffix:colon
r_if
c_cond
(paren
id|i
op_ne
id|CS_SUCCESS
)paren
(brace
id|cs_error
c_func
(paren
id|link-&gt;handle
comma
id|RequestIO
comma
id|i
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * allocate an interrupt line&n;&t; */
id|i
op_assign
id|CardServices
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
r_if
c_cond
(paren
id|i
op_ne
id|CS_SUCCESS
)paren
(brace
id|cs_error
c_func
(paren
id|link-&gt;handle
comma
id|RequestIRQ
comma
id|i
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
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;         * configure the PCMCIA socket&n;&t;  */
id|i
op_assign
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
id|i
op_ne
id|CS_SUCCESS
)paren
(brace
id|cs_error
c_func
(paren
id|link-&gt;handle
comma
id|RequestConfiguration
comma
id|i
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
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* At this point, the dev_node_t structure(s) should be&n;       initialized and arranged in a linked list at link-&gt;dev. */
id|strcpy
c_func
(paren
id|dev-&gt;node.dev_name
comma
l_string|&quot;A1&quot;
)paren
suffix:semicolon
id|dev-&gt;node.major
op_assign
l_int|45
suffix:semicolon
id|dev-&gt;node.minor
op_assign
l_int|0
suffix:semicolon
id|link-&gt;dev
op_assign
op_amp
id|dev-&gt;node
suffix:semicolon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_CONFIG_PENDING
suffix:semicolon
multiline_comment|/* If any step failed, release any partially configured state */
r_if
c_cond
(paren
id|i
op_ne
l_int|0
)paren
(brace
id|avma1cs_release
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
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;avma1_cs: checking at i/o %#x, irq %d&bslash;n&quot;
comma
id|link-&gt;io.BasePort1
comma
id|link-&gt;irq.AssignedIRQ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|avm_a1_init_pcmcia
c_func
(paren
(paren
r_void
op_star
)paren
(paren
r_int
)paren
id|link-&gt;io.BasePort1
comma
id|link-&gt;irq.AssignedIRQ
comma
op_amp
id|busy
comma
id|isdnprot
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;avma1_cs: failed to initialize AVM A1 PCMCIA %d at i/o %#x&bslash;n&quot;
comma
id|i
comma
id|link-&gt;io.BasePort1
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|i
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* no returncode for cardnr :-( */
id|dev-&gt;node.minor
op_assign
id|i
suffix:semicolon
)brace
multiline_comment|/* avma1cs_config */
multiline_comment|/*======================================================================&n;&n;    After a card is removed, avma1cs_release() will unregister the net&n;    device, and release the PCMCIA configuration.  If the device is&n;    still open, this will be postponed until it is closed.&n;    &n;======================================================================*/
DECL|function|avma1cs_release
r_static
r_void
id|avma1cs_release
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
l_string|&quot;avma1cs_release(0x%p)&bslash;n&quot;
comma
id|link
)paren
suffix:semicolon
multiline_comment|/*&n;       If the device is currently in use, we won&squot;t release until it&n;       is actually closed.&n;    */
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
l_string|&quot;avma1_cs: release postponed, &squot;%s&squot; still open&bslash;n&quot;
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
multiline_comment|/* no unregister function with hisax */
id|HiSax_closecard
c_func
(paren
id|local-&gt;node.minor
)paren
suffix:semicolon
multiline_comment|/* Unlink the device chain */
id|link-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Don&squot;t bother checking to see if these succeed or not */
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
id|avma1cs_detach
c_func
(paren
id|link
)paren
suffix:semicolon
)brace
multiline_comment|/* avma1cs_release */
multiline_comment|/*======================================================================&n;&n;    The card status event handler.  Mostly, this schedules other&n;    stuff to run after an event is received.  A CARD_REMOVAL event&n;    also sets some flags to discourage the net drivers from trying&n;    to talk to the card any more.&n;&n;    When a CARD_REMOVAL event is received, we immediately set a flag&n;    to block future accesses to this device.  All the functions that&n;    actually access the device should check this flag to make sure&n;    the card is still present.&n;    &n;======================================================================*/
DECL|function|avma1cs_event
r_static
r_int
id|avma1cs_event
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
l_string|&quot;avma1cs_event(0x%06x)&bslash;n&quot;
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
id|link-&gt;release.expires
op_assign
id|jiffies
op_plus
id|HZ
op_div
l_int|20
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|link-&gt;release
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
id|avma1cs_config
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
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* avma1cs_event */
multiline_comment|/*====================================================================*/
DECL|function|init_avma1_cs
r_static
r_int
id|__init
id|init_avma1_cs
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
l_string|&quot;avma1_cs: Card Services release &quot;
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
id|avma1cs_attach
comma
op_amp
id|avma1cs_detach
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|exit_avma1_cs
r_static
r_void
id|__exit
id|exit_avma1_cs
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
l_string|&quot;avma1_cs: unloading&bslash;n&quot;
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
r_if
c_cond
(paren
id|dev_list-&gt;state
op_amp
id|DEV_CONFIG
)paren
id|avma1cs_release
c_func
(paren
(paren
id|u_long
)paren
id|dev_list
)paren
suffix:semicolon
id|avma1cs_detach
c_func
(paren
id|dev_list
)paren
suffix:semicolon
)brace
DECL|variable|init_avma1_cs
id|module_init
c_func
(paren
id|init_avma1_cs
)paren
suffix:semicolon
DECL|variable|exit_avma1_cs
id|module_exit
c_func
(paren
id|exit_avma1_cs
)paren
suffix:semicolon
eof
