multiline_comment|/*&n; * Linux ARCnet driver - COM20020 PCMCIA support&n; * &n; * Written 1994-1999 by Avery Pennarun,&n; *    based on an ISA version by David Woodhouse.&n; * Derived from ibmtr_cs.c by Steve Kipisz (pcmcia-cs 3.1.4)&n; *    which was derived from pcnet_cs.c by David Hinds.&n; * Some additional portions derived from skeleton.c by Donald Becker.&n; *&n; * Special thanks to Contemporary Controls, Inc. (www.ccontrols.com)&n; *  for sponsoring the further development of this driver.&n; *&n; * **********************&n; *&n; * The original copyright of skeleton.c was as follows:&n; *&n; * skeleton.c Written 1993 by Donald Becker.&n; * Copyright 1993 United States Government as represented by the&n; * Director, National Security Agency.  This software may only be used&n; * and distributed according to the terms of the GNU General Public License as&n; * modified by SRC, incorporated herein by reference.&n; * &n; * **********************&n; * Changes:&n; * Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt; - 08/08/2000&n; * - reorganize kmallocs in com20020_attach, checking all for failure&n; *   and releasing the previous allocations if one fails&n; * **********************&n; * &n; * For more details, see drivers/net/arcnet.c&n; *&n; * **********************&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/arcdevice.h&gt;
macro_line|#include &lt;linux/com20020.h&gt;
macro_line|#include &lt;pcmcia/version.h&gt;
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &lt;pcmcia/ds.h&gt;
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;arcnet: COM20020 PCMCIA support loaded.&bslash;n&quot;
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
DECL|function|regdump
r_static
r_void
id|regdump
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
id|count
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;com20020 register dump:&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
id|ioaddr
suffix:semicolon
id|count
OL
id|ioaddr
op_plus
l_int|16
suffix:semicolon
id|count
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|count
op_mod
l_int|16
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n%04X: &quot;
comma
id|count
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%02X &quot;
comma
id|inb
c_func
(paren
id|count
)paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;buffer0 dump:&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* set up the address register */
id|count
op_assign
l_int|0
suffix:semicolon
id|outb
c_func
(paren
(paren
id|count
op_rshift
l_int|8
)paren
op_or
id|RDDATAflag
op_or
id|AUTOINCflag
comma
id|_ADDR_HI
)paren
suffix:semicolon
id|outb
c_func
(paren
id|count
op_amp
l_int|0xff
comma
id|_ADDR_LO
)paren
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
l_int|256
op_plus
l_int|32
suffix:semicolon
id|count
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|count
op_mod
l_int|16
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n%04X: &quot;
comma
id|count
)paren
suffix:semicolon
multiline_comment|/* copy the data */
id|printk
c_func
(paren
l_string|&quot;%02X &quot;
comma
id|inb
c_func
(paren
id|_MEMDATA
)paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|DEBUG
mdefine_line|#define DEBUG(n, args...) do { } while (0)
DECL|function|regdump
r_static
r_inline
r_void
id|regdump
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
)brace
macro_line|#endif
multiline_comment|/*====================================================================*/
multiline_comment|/* Parameters that can be set with &squot;insmod&squot; */
DECL|variable|node
r_static
r_int
id|node
suffix:semicolon
DECL|variable|timeout
r_static
r_int
id|timeout
op_assign
l_int|3
suffix:semicolon
DECL|variable|backplane
r_static
r_int
id|backplane
suffix:semicolon
DECL|variable|clockp
r_static
r_int
id|clockp
suffix:semicolon
DECL|variable|clockm
r_static
r_int
id|clockm
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|node
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|timeout
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|backplane
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|clockp
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|clockm
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
multiline_comment|/* Bit map of interrupts to choose from */
DECL|variable|irq_mask
r_static
id|u_int
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
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*====================================================================*/
r_static
r_void
id|com20020_config
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
suffix:semicolon
r_static
r_void
id|com20020_release
c_func
(paren
id|u_long
id|arg
)paren
suffix:semicolon
r_static
r_int
id|com20020_event
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
DECL|variable|dev_info
r_static
id|dev_info_t
id|dev_info
op_assign
l_string|&quot;com20020_cs&quot;
suffix:semicolon
r_static
id|dev_link_t
op_star
id|com20020_attach
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|com20020_detach
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
multiline_comment|/*====================================================================*/
DECL|struct|com20020_dev_t
r_typedef
r_struct
id|com20020_dev_t
(brace
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|dev_configured
r_int
id|dev_configured
suffix:semicolon
DECL|member|node
id|dev_node_t
id|node
suffix:semicolon
DECL|typedef|com20020_dev_t
)brace
id|com20020_dev_t
suffix:semicolon
multiline_comment|/*======================================================================&n;&n;    This bit of code is used to avoid unregistering network devices&n;    at inappropriate times.  2.2 and later kernels are fairly picky&n;    about when this can happen.&n;    &n;======================================================================*/
DECL|function|flush_stale_links
r_static
r_void
id|flush_stale_links
c_func
(paren
r_void
)paren
(brace
id|dev_link_t
op_star
id|link
comma
op_star
id|next
suffix:semicolon
r_for
c_loop
(paren
id|link
op_assign
id|dev_list
suffix:semicolon
id|link
suffix:semicolon
id|link
op_assign
id|next
)paren
(brace
id|next
op_assign
id|link-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_STALE_LINK
)paren
id|com20020_detach
c_func
(paren
id|link
)paren
suffix:semicolon
)brace
)brace
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
multiline_comment|/*======================================================================&n;&n;    com20020_attach() creates an &quot;instance&quot; of the driver, allocating&n;    local data structures for one device.  The device is registered&n;    with Card Services.&n;&n;======================================================================*/
DECL|function|com20020cs_open_close
r_static
r_void
id|com20020cs_open_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_bool
id|open
)paren
(brace
r_if
c_cond
(paren
id|open
)paren
id|MOD_INC_USE_COUNT
suffix:semicolon
r_else
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|function|com20020_attach
r_static
id|dev_link_t
op_star
id|com20020_attach
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
id|com20020_dev_t
op_star
id|info
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_int
id|i
comma
id|ret
suffix:semicolon
r_struct
id|arcnet_local
op_star
id|lp
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;com20020_attach()&bslash;n&quot;
)paren
suffix:semicolon
id|flush_stale_links
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Create new network device */
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
r_return
l_int|NULL
suffix:semicolon
id|info
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|com20020_dev_t
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
r_goto
id|fail_alloc_info
suffix:semicolon
id|lp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|arcnet_local
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lp
)paren
r_goto
id|fail_alloc_lp
suffix:semicolon
id|dev
op_assign
id|dev_alloc
c_func
(paren
l_string|&quot;arc%d&quot;
comma
op_amp
id|ret
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_goto
id|fail_alloc_dev
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
r_struct
id|com20020_dev_t
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|lp
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|arcnet_local
)paren
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
id|dev-&gt;priv
op_assign
id|lp
suffix:semicolon
id|link-&gt;release.function
op_assign
op_amp
id|com20020_release
suffix:semicolon
id|link-&gt;release.data
op_assign
(paren
id|u_long
)paren
id|link
suffix:semicolon
id|link-&gt;io.Attributes1
op_assign
id|IO_DATA_PATH_WIDTH_8
suffix:semicolon
id|link-&gt;io.NumPorts1
op_assign
l_int|16
suffix:semicolon
id|link-&gt;io.IOAddrLines
op_assign
l_int|16
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
multiline_comment|/* fill in our module parameters as defaults */
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
op_assign
id|node
suffix:semicolon
id|lp-&gt;timeout
op_assign
id|timeout
suffix:semicolon
id|lp-&gt;backplane
op_assign
id|backplane
suffix:semicolon
id|lp-&gt;clockp
op_assign
id|clockp
suffix:semicolon
id|lp-&gt;clockm
op_assign
id|clockm
op_amp
l_int|3
suffix:semicolon
id|lp-&gt;hw.open_close_ll
op_assign
id|com20020cs_open_close
suffix:semicolon
id|link-&gt;irq.Instance
op_assign
id|info-&gt;dev
op_assign
id|dev
suffix:semicolon
id|link-&gt;priv
op_assign
id|info
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
id|com20020_event
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
id|com20020_detach
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
id|fail_alloc_dev
suffix:colon
id|kfree
c_func
(paren
id|lp
)paren
suffix:semicolon
id|fail_alloc_lp
suffix:colon
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
id|fail_alloc_info
suffix:colon
id|kfree
c_func
(paren
id|link
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* com20020_attach */
multiline_comment|/*======================================================================&n;&n;    This deletes a driver &quot;instance&quot;.  The device is de-registered&n;    with Card Services.  If it has been released, all local data&n;    structures are freed.  Otherwise, the structures will be freed&n;    when the device is released.&n;&n;======================================================================*/
DECL|function|com20020_detach
r_static
r_void
id|com20020_detach
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
(brace
r_struct
id|com20020_dev_t
op_star
id|info
op_assign
id|link-&gt;priv
suffix:semicolon
id|dev_link_t
op_star
op_star
id|linkp
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;detach...&bslash;n&quot;
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;com20020_detach(0x%p)&bslash;n&quot;
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
id|dev
op_assign
id|info-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_CONFIG
)paren
(brace
id|com20020_release
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
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;unlinking...&bslash;n&quot;
)paren
suffix:semicolon
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
id|dev
op_assign
id|info-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
r_if
c_cond
(paren
id|info-&gt;dev_configured
)paren
(brace
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;unregister...&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|netif_running
c_func
(paren
id|dev
)paren
)paren
id|dev
op_member_access_from_pointer
id|stop
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * this is necessary because we register our IRQ separately&n;&t;&t; * from card services.&n;&t;&t; */
r_if
c_cond
(paren
id|dev-&gt;irq
)paren
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* ...but I/O ports are done automatically by card services */
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;kfree...&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev-&gt;priv
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;kfree2...&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
)brace
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;kfree3...&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|link
)paren
suffix:semicolon
)brace
multiline_comment|/* com20020_detach */
multiline_comment|/*======================================================================&n;&n;    com20020_config() is scheduled to run after a CARD_INSERTION event&n;    is received, to configure the PCMCIA socket, and to make the&n;    device available to the system.&n;&n;======================================================================*/
DECL|macro|CS_CHECK
mdefine_line|#define CS_CHECK(fn, args...) &bslash;&n;while ((last_ret=CardServices(last_fn=(fn), args))!=0) goto cs_failed
DECL|function|com20020_config
r_static
r_void
id|com20020_config
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
(brace
r_struct
id|arcnet_local
op_star
id|lp
suffix:semicolon
id|client_handle_t
id|handle
suffix:semicolon
id|tuple_t
id|tuple
suffix:semicolon
id|cisparse_t
id|parse
suffix:semicolon
id|com20020_dev_t
op_star
id|info
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_int
id|i
comma
id|last_ret
comma
id|last_fn
suffix:semicolon
id|u_char
id|buf
(braket
l_int|64
)braket
suffix:semicolon
r_int
id|ioaddr
suffix:semicolon
id|handle
op_assign
id|link-&gt;handle
suffix:semicolon
id|info
op_assign
id|link-&gt;priv
suffix:semicolon
id|dev
op_assign
id|info-&gt;dev
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;config...&bslash;n&quot;
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;com20020_config(0x%p)&bslash;n&quot;
comma
id|link
)paren
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
multiline_comment|/* Configure card */
id|link-&gt;state
op_or_assign
id|DEV_CONFIG
suffix:semicolon
id|strcpy
c_func
(paren
id|info-&gt;node.dev_name
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;arcnet: baseport1 is %Xh&bslash;n&quot;
comma
id|link-&gt;io.BasePort1
)paren
suffix:semicolon
id|i
op_assign
op_logical_neg
id|CS_SUCCESS
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|link-&gt;io.BasePort1
)paren
(brace
r_for
c_loop
(paren
id|ioaddr
op_assign
l_int|0x100
suffix:semicolon
id|ioaddr
OL
l_int|0x400
suffix:semicolon
id|ioaddr
op_add_assign
l_int|0x10
)paren
(brace
id|link-&gt;io.BasePort1
op_assign
id|ioaddr
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
r_break
suffix:semicolon
)brace
)brace
r_else
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
op_ne
id|CS_SUCCESS
)paren
(brace
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;arcnet: requestIO failed totally!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|failed
suffix:semicolon
)brace
id|ioaddr
op_assign
id|dev-&gt;base_addr
op_assign
id|link-&gt;io.BasePort1
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;arcnet: got ioaddr %Xh&bslash;n&quot;
comma
id|ioaddr
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;arcnet: request IRQ %d (%Xh/%Xh)&bslash;n&quot;
comma
id|link-&gt;irq.AssignedIRQ
comma
id|link-&gt;irq.IRQInfo1
comma
id|link-&gt;irq.IRQInfo2
)paren
suffix:semicolon
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
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;arcnet: requestIRQ failed totally!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|failed
suffix:semicolon
)brace
id|dev-&gt;irq
op_assign
id|link-&gt;irq.AssignedIRQ
suffix:semicolon
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
r_if
c_cond
(paren
id|com20020_check
c_func
(paren
id|dev
)paren
)paren
(brace
id|regdump
c_func
(paren
id|dev
)paren
suffix:semicolon
r_goto
id|failed
suffix:semicolon
)brace
id|MOD_INC_USE_COUNT
suffix:semicolon
id|lp
op_assign
id|dev-&gt;priv
suffix:semicolon
id|lp-&gt;card_name
op_assign
l_string|&quot;PCMCIA COM20020&quot;
suffix:semicolon
id|lp-&gt;card_flags
op_assign
id|ARC_CAN_10MBIT
suffix:semicolon
multiline_comment|/* pretend all of them can 10Mbit */
id|i
op_assign
id|com20020_found
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
l_int|0
)paren
(brace
id|DEBUG
c_func
(paren
l_int|1
comma
id|KERN_NOTICE
l_string|&quot;com20020_cs: com20020_found() failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|failed
suffix:semicolon
)brace
id|info-&gt;dev_configured
op_assign
l_int|1
suffix:semicolon
id|link-&gt;dev
op_assign
op_amp
id|info-&gt;node
suffix:semicolon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_CONFIG_PENDING
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: port %#3lx, irq %d&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|dev-&gt;base_addr
comma
id|dev-&gt;irq
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
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;com20020_config failed...&bslash;n&quot;
)paren
suffix:semicolon
id|com20020_release
c_func
(paren
(paren
id|u_long
)paren
id|link
)paren
suffix:semicolon
)brace
multiline_comment|/* com20020_config */
multiline_comment|/*======================================================================&n;&n;    After a card is removed, com20020_release() will unregister the net&n;    device, and release the PCMCIA configuration.  If the device is&n;    still open, this will be postponed until it is closed.&n;&n;======================================================================*/
DECL|function|com20020_release
r_static
r_void
id|com20020_release
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
l_int|1
comma
l_string|&quot;release...&bslash;n&quot;
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;com20020_release(0x%p)&bslash;n&quot;
comma
id|link
)paren
suffix:semicolon
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
l_string|&quot;postpone...&bslash;n&quot;
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;com20020_cs: release postponed, device stll open&bslash;n&quot;
)paren
suffix:semicolon
id|link-&gt;state
op_or_assign
id|DEV_STALE_CONFIG
suffix:semicolon
r_return
suffix:semicolon
)brace
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
(paren
id|DEV_CONFIG
op_or
id|DEV_RELEASE_PENDING
)paren
suffix:semicolon
)brace
multiline_comment|/* com20020_release */
multiline_comment|/*======================================================================&n;&n;    The card status event handler.  Mostly, this schedules other&n;    stuff to run after an event is received.  A CARD_REMOVAL event&n;    also sets some flags to discourage the net drivers from trying&n;    to talk to the card any more.&n;&n;======================================================================*/
DECL|function|com20020_event
r_static
r_int
id|com20020_event
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
id|com20020_dev_t
op_star
id|info
op_assign
id|link-&gt;priv
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|info-&gt;dev
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;com20020_event(0x%06x)&bslash;n&quot;
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
id|dev
)paren
suffix:semicolon
id|link-&gt;release.expires
op_assign
id|jiffies
op_plus
id|HZ
op_div
l_int|20
suffix:semicolon
id|link-&gt;state
op_or_assign
id|DEV_RELEASE_PENDING
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
suffix:semicolon
id|com20020_config
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
r_if
c_cond
(paren
id|link-&gt;open
)paren
(brace
id|netif_device_detach
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|link-&gt;open
)paren
(brace
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_struct
id|arcnet_local
op_star
id|lp
op_assign
(paren
r_struct
id|arcnet_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|ARCRESET
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* com20020_event */
multiline_comment|/*====================================================================*/
DECL|function|init_com20020_cs
r_static
r_int
id|__init
id|init_com20020_cs
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
id|VERSION
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
l_string|&quot;com20020_cs: Card Services release &quot;
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
id|com20020_attach
comma
op_amp
id|com20020_detach
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|exit_com20020_cs
r_static
r_void
id|__exit
id|exit_com20020_cs
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
l_string|&quot;com20020_cs: unloading&bslash;n&quot;
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
id|com20020_detach
c_func
(paren
id|dev_list
)paren
suffix:semicolon
)brace
DECL|variable|init_com20020_cs
id|module_init
c_func
(paren
id|init_com20020_cs
)paren
suffix:semicolon
DECL|variable|exit_com20020_cs
id|module_exit
c_func
(paren
id|exit_com20020_cs
)paren
suffix:semicolon
eof
