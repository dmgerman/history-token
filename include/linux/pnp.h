multiline_comment|/*&n; * Linux Plug and Play Support&n; * Copyright by Adam Belay &lt;ambx1@neo.rr.com&gt;&n; *&n; */
macro_line|#ifndef _LINUX_PNP_H
DECL|macro|_LINUX_PNP_H
mdefine_line|#define _LINUX_PNP_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/mod_devicetable.h&gt;
DECL|macro|PNP_MAX_PORT
mdefine_line|#define PNP_MAX_PORT&t;&t;8
DECL|macro|PNP_MAX_MEM
mdefine_line|#define PNP_MAX_MEM&t;&t;4
DECL|macro|PNP_MAX_IRQ
mdefine_line|#define PNP_MAX_IRQ&t;&t;2
DECL|macro|PNP_MAX_DMA
mdefine_line|#define PNP_MAX_DMA&t;&t;2
DECL|macro|PNP_NAME_LEN
mdefine_line|#define PNP_NAME_LEN&t;&t;50
r_struct
id|pnp_protocol
suffix:semicolon
r_struct
id|pnp_dev
suffix:semicolon
multiline_comment|/*&n; * Resource Management&n; */
multiline_comment|/* Use these instead of directly reading pnp_dev to get resource information */
DECL|macro|pnp_port_start
mdefine_line|#define pnp_port_start(dev,bar)   ((dev)-&gt;res.port_resource[(bar)].start)
DECL|macro|pnp_port_end
mdefine_line|#define pnp_port_end(dev,bar)     ((dev)-&gt;res.port_resource[(bar)].end)
DECL|macro|pnp_port_flags
mdefine_line|#define pnp_port_flags(dev,bar)   ((dev)-&gt;res.port_resource[(bar)].flags)
DECL|macro|pnp_port_valid
mdefine_line|#define pnp_port_valid(dev,bar) &bslash;&n;&t;((pnp_port_flags((dev),(bar)) &amp; (IORESOURCE_IO | IORESOURCE_UNSET)) &bslash;&n;&t;&t;== IORESOURCE_IO)
DECL|macro|pnp_port_len
mdefine_line|#define pnp_port_len(dev,bar) &bslash;&n;&t;((pnp_port_start((dev),(bar)) == 0 &amp;&amp;&t;&bslash;&n;&t;  pnp_port_end((dev),(bar)) ==&t;&t;&bslash;&n;&t;  pnp_port_start((dev),(bar))) ? 0 :&t;&bslash;&n;&t;  &t;&t;&t;&t;&t;&bslash;&n;&t; (pnp_port_end((dev),(bar)) -&t;&t;&bslash;&n;&t;  pnp_port_start((dev),(bar)) + 1))
DECL|macro|pnp_mem_start
mdefine_line|#define pnp_mem_start(dev,bar)   ((dev)-&gt;res.mem_resource[(bar)].start)
DECL|macro|pnp_mem_end
mdefine_line|#define pnp_mem_end(dev,bar)     ((dev)-&gt;res.mem_resource[(bar)].end)
DECL|macro|pnp_mem_flags
mdefine_line|#define pnp_mem_flags(dev,bar)   ((dev)-&gt;res.mem_resource[(bar)].flags)
DECL|macro|pnp_mem_valid
mdefine_line|#define pnp_mem_valid(dev,bar) &bslash;&n;&t;((pnp_mem_flags((dev),(bar)) &amp; (IORESOURCE_MEM | IORESOURCE_UNSET)) &bslash;&n;&t;&t;== IORESOURCE_MEM)
DECL|macro|pnp_mem_len
mdefine_line|#define pnp_mem_len(dev,bar) &bslash;&n;&t;((pnp_mem_start((dev),(bar)) == 0 &amp;&amp;&t;&bslash;&n;&t;  pnp_mem_end((dev),(bar)) ==&t;&t;&bslash;&n;&t;  pnp_mem_start((dev),(bar))) ? 0 :&t;&bslash;&n;&t;  &t;&t;&t;&t;&t;&bslash;&n;&t; (pnp_mem_end((dev),(bar)) -&t;&t;&bslash;&n;&t;  pnp_mem_start((dev),(bar)) + 1))
DECL|macro|pnp_irq
mdefine_line|#define pnp_irq(dev,bar)&t; ((dev)-&gt;res.irq_resource[(bar)].start)
DECL|macro|pnp_irq_flags
mdefine_line|#define pnp_irq_flags(dev,bar)&t; ((dev)-&gt;res.irq_resource[(bar)].flags)
DECL|macro|pnp_irq_valid
mdefine_line|#define pnp_irq_valid(dev,bar) &bslash;&n;&t;((pnp_irq_flags((dev),(bar)) &amp; (IORESOURCE_IRQ | IORESOURCE_UNSET)) &bslash;&n;&t;&t;== IORESOURCE_IRQ)
DECL|macro|pnp_dma
mdefine_line|#define pnp_dma(dev,bar)&t; ((dev)-&gt;res.dma_resource[(bar)].start)
DECL|macro|pnp_dma_flags
mdefine_line|#define pnp_dma_flags(dev,bar)&t; ((dev)-&gt;res.dma_resource[(bar)].flags)
DECL|macro|pnp_dma_valid
mdefine_line|#define pnp_dma_valid(dev,bar) &bslash;&n;&t;((pnp_dma_flags((dev),(bar)) &amp; (IORESOURCE_DMA | IORESOURCE_UNSET)) &bslash;&n;&t;&t;== IORESOURCE_DMA)
DECL|macro|PNP_PORT_FLAG_16BITADDR
mdefine_line|#define PNP_PORT_FLAG_16BITADDR&t;(1&lt;&lt;0)
DECL|macro|PNP_PORT_FLAG_FIXED
mdefine_line|#define PNP_PORT_FLAG_FIXED&t;(1&lt;&lt;1)
DECL|struct|pnp_port
r_struct
id|pnp_port
(brace
DECL|member|min
r_int
r_int
id|min
suffix:semicolon
multiline_comment|/* min base number */
DECL|member|max
r_int
r_int
id|max
suffix:semicolon
multiline_comment|/* max base number */
DECL|member|align
r_int
r_char
id|align
suffix:semicolon
multiline_comment|/* align boundary */
DECL|member|size
r_int
r_char
id|size
suffix:semicolon
multiline_comment|/* size of range */
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
multiline_comment|/* port flags */
DECL|member|pad
r_int
r_char
id|pad
suffix:semicolon
multiline_comment|/* pad */
DECL|member|next
r_struct
id|pnp_port
op_star
id|next
suffix:semicolon
multiline_comment|/* next port */
)brace
suffix:semicolon
DECL|macro|PNP_IRQ_NR
mdefine_line|#define PNP_IRQ_NR 256
DECL|struct|pnp_irq
r_struct
id|pnp_irq
(brace
id|DECLARE_BITMAP
c_func
(paren
id|map
comma
id|PNP_IRQ_NR
)paren
suffix:semicolon
multiline_comment|/* bitmaks for IRQ lines */
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
multiline_comment|/* IRQ flags */
DECL|member|pad
r_int
r_char
id|pad
suffix:semicolon
multiline_comment|/* pad */
DECL|member|next
r_struct
id|pnp_irq
op_star
id|next
suffix:semicolon
multiline_comment|/* next IRQ */
)brace
suffix:semicolon
DECL|struct|pnp_dma
r_struct
id|pnp_dma
(brace
DECL|member|map
r_int
r_char
id|map
suffix:semicolon
multiline_comment|/* bitmask for DMA channels */
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
multiline_comment|/* DMA flags */
DECL|member|next
r_struct
id|pnp_dma
op_star
id|next
suffix:semicolon
multiline_comment|/* next port */
)brace
suffix:semicolon
DECL|struct|pnp_mem
r_struct
id|pnp_mem
(brace
DECL|member|min
r_int
r_int
id|min
suffix:semicolon
multiline_comment|/* min base number */
DECL|member|max
r_int
r_int
id|max
suffix:semicolon
multiline_comment|/* max base number */
DECL|member|align
r_int
r_int
id|align
suffix:semicolon
multiline_comment|/* align boundary */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* size of range */
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
multiline_comment|/* memory flags */
DECL|member|pad
r_int
r_char
id|pad
suffix:semicolon
multiline_comment|/* pad */
DECL|member|next
r_struct
id|pnp_mem
op_star
id|next
suffix:semicolon
multiline_comment|/* next memory resource */
)brace
suffix:semicolon
DECL|macro|PNP_RES_PRIORITY_PREFERRED
mdefine_line|#define PNP_RES_PRIORITY_PREFERRED&t;0
DECL|macro|PNP_RES_PRIORITY_ACCEPTABLE
mdefine_line|#define PNP_RES_PRIORITY_ACCEPTABLE&t;1
DECL|macro|PNP_RES_PRIORITY_FUNCTIONAL
mdefine_line|#define PNP_RES_PRIORITY_FUNCTIONAL&t;2
DECL|macro|PNP_RES_PRIORITY_INVALID
mdefine_line|#define PNP_RES_PRIORITY_INVALID&t;65535
DECL|struct|pnp_option
r_struct
id|pnp_option
(brace
DECL|member|priority
r_int
r_int
id|priority
suffix:semicolon
multiline_comment|/* priority */
DECL|member|port
r_struct
id|pnp_port
op_star
id|port
suffix:semicolon
multiline_comment|/* first port */
DECL|member|irq
r_struct
id|pnp_irq
op_star
id|irq
suffix:semicolon
multiline_comment|/* first IRQ */
DECL|member|dma
r_struct
id|pnp_dma
op_star
id|dma
suffix:semicolon
multiline_comment|/* first DMA */
DECL|member|mem
r_struct
id|pnp_mem
op_star
id|mem
suffix:semicolon
multiline_comment|/* first memory resource */
DECL|member|next
r_struct
id|pnp_option
op_star
id|next
suffix:semicolon
multiline_comment|/* used to chain dependent resources */
)brace
suffix:semicolon
DECL|struct|pnp_resource_table
r_struct
id|pnp_resource_table
(brace
DECL|member|port_resource
r_struct
id|resource
id|port_resource
(braket
id|PNP_MAX_PORT
)braket
suffix:semicolon
DECL|member|mem_resource
r_struct
id|resource
id|mem_resource
(braket
id|PNP_MAX_MEM
)braket
suffix:semicolon
DECL|member|dma_resource
r_struct
id|resource
id|dma_resource
(braket
id|PNP_MAX_DMA
)braket
suffix:semicolon
DECL|member|irq_resource
r_struct
id|resource
id|irq_resource
(braket
id|PNP_MAX_IRQ
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Device Managemnt&n; */
DECL|struct|pnp_card
r_struct
id|pnp_card
(brace
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
multiline_comment|/* Driver Model device interface */
DECL|member|number
r_int
r_char
id|number
suffix:semicolon
multiline_comment|/* used as an index, must be unique */
DECL|member|global_list
r_struct
id|list_head
id|global_list
suffix:semicolon
multiline_comment|/* node in global list of cards */
DECL|member|protocol_list
r_struct
id|list_head
id|protocol_list
suffix:semicolon
multiline_comment|/* node in protocol&squot;s list of cards */
DECL|member|devices
r_struct
id|list_head
id|devices
suffix:semicolon
multiline_comment|/* devices attached to the card */
DECL|member|protocol
r_struct
id|pnp_protocol
op_star
id|protocol
suffix:semicolon
DECL|member|id
r_struct
id|pnp_id
op_star
id|id
suffix:semicolon
multiline_comment|/* contains supported EISA IDs*/
DECL|member|name
r_char
id|name
(braket
id|PNP_NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* contains a human-readable name */
DECL|member|pnpver
r_int
r_char
id|pnpver
suffix:semicolon
multiline_comment|/* Plug &amp; Play version */
DECL|member|productver
r_int
r_char
id|productver
suffix:semicolon
multiline_comment|/* product version */
DECL|member|serial
r_int
r_int
id|serial
suffix:semicolon
multiline_comment|/* serial number */
DECL|member|checksum
r_int
r_char
id|checksum
suffix:semicolon
multiline_comment|/* if zero - checksum passed */
DECL|member|procdir
r_struct
id|proc_dir_entry
op_star
id|procdir
suffix:semicolon
multiline_comment|/* directory entry in /proc/bus/isapnp */
)brace
suffix:semicolon
DECL|macro|global_to_pnp_card
mdefine_line|#define global_to_pnp_card(n) list_entry(n, struct pnp_card, global_list)
DECL|macro|protocol_to_pnp_card
mdefine_line|#define protocol_to_pnp_card(n) list_entry(n, struct pnp_card, protocol_list)
DECL|macro|to_pnp_card
mdefine_line|#define to_pnp_card(n) container_of(n, struct pnp_card, dev)
DECL|macro|pnp_for_each_card
mdefine_line|#define pnp_for_each_card(card) &bslash;&n;&t;for((card) = global_to_pnp_card(pnp_cards.next); &bslash;&n;&t;(card) != global_to_pnp_card(&amp;pnp_cards); &bslash;&n;&t;(card) = global_to_pnp_card((card)-&gt;global_list.next))
DECL|struct|pnp_card_link
r_struct
id|pnp_card_link
(brace
DECL|member|card
r_struct
id|pnp_card
op_star
id|card
suffix:semicolon
DECL|member|driver
r_struct
id|pnp_card_driver
op_star
id|driver
suffix:semicolon
DECL|member|driver_data
r_void
op_star
id|driver_data
suffix:semicolon
)brace
suffix:semicolon
DECL|function|pnp_get_card_drvdata
r_static
r_inline
r_void
op_star
id|pnp_get_card_drvdata
(paren
r_struct
id|pnp_card_link
op_star
id|pcard
)paren
(brace
r_return
id|pcard-&gt;driver_data
suffix:semicolon
)brace
DECL|function|pnp_set_card_drvdata
r_static
r_inline
r_void
id|pnp_set_card_drvdata
(paren
r_struct
id|pnp_card_link
op_star
id|pcard
comma
r_void
op_star
id|data
)paren
(brace
id|pcard-&gt;driver_data
op_assign
id|data
suffix:semicolon
)brace
DECL|struct|pnp_dev
r_struct
id|pnp_dev
(brace
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
multiline_comment|/* Driver Model device interface */
DECL|member|number
r_int
r_char
id|number
suffix:semicolon
multiline_comment|/* used as an index, must be unique */
DECL|member|status
r_int
id|status
suffix:semicolon
DECL|member|global_list
r_struct
id|list_head
id|global_list
suffix:semicolon
multiline_comment|/* node in global list of devices */
DECL|member|protocol_list
r_struct
id|list_head
id|protocol_list
suffix:semicolon
multiline_comment|/* node in list of device&squot;s protocol */
DECL|member|card_list
r_struct
id|list_head
id|card_list
suffix:semicolon
multiline_comment|/* node in card&squot;s list of devices */
DECL|member|rdev_list
r_struct
id|list_head
id|rdev_list
suffix:semicolon
multiline_comment|/* node in cards list of requested devices */
DECL|member|protocol
r_struct
id|pnp_protocol
op_star
id|protocol
suffix:semicolon
DECL|member|card
r_struct
id|pnp_card
op_star
id|card
suffix:semicolon
multiline_comment|/* card the device is attached to, none if NULL */
DECL|member|driver
r_struct
id|pnp_driver
op_star
id|driver
suffix:semicolon
DECL|member|card_link
r_struct
id|pnp_card_link
op_star
id|card_link
suffix:semicolon
DECL|member|id
r_struct
id|pnp_id
op_star
id|id
suffix:semicolon
multiline_comment|/* supported EISA IDs*/
DECL|member|active
r_int
id|active
suffix:semicolon
DECL|member|capabilities
r_int
id|capabilities
suffix:semicolon
DECL|member|independent
r_struct
id|pnp_option
op_star
id|independent
suffix:semicolon
DECL|member|dependent
r_struct
id|pnp_option
op_star
id|dependent
suffix:semicolon
DECL|member|res
r_struct
id|pnp_resource_table
id|res
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|PNP_NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* contains a human-readable name */
DECL|member|regs
r_int
r_int
id|regs
suffix:semicolon
multiline_comment|/* ISAPnP: supported registers */
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* used by protocols */
DECL|member|procent
r_struct
id|proc_dir_entry
op_star
id|procent
suffix:semicolon
multiline_comment|/* device entry in /proc/bus/isapnp */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|global_to_pnp_dev
mdefine_line|#define global_to_pnp_dev(n) list_entry(n, struct pnp_dev, global_list)
DECL|macro|card_to_pnp_dev
mdefine_line|#define card_to_pnp_dev(n) list_entry(n, struct pnp_dev, card_list)
DECL|macro|protocol_to_pnp_dev
mdefine_line|#define protocol_to_pnp_dev(n) list_entry(n, struct pnp_dev, protocol_list)
DECL|macro|to_pnp_dev
mdefine_line|#define&t;to_pnp_dev(n) container_of(n, struct pnp_dev, dev)
DECL|macro|pnp_for_each_dev
mdefine_line|#define pnp_for_each_dev(dev) &bslash;&n;&t;for((dev) = global_to_pnp_dev(pnp_global.next); &bslash;&n;&t;(dev) != global_to_pnp_dev(&amp;pnp_global); &bslash;&n;&t;(dev) = global_to_pnp_dev((dev)-&gt;global_list.next))
DECL|macro|card_for_each_dev
mdefine_line|#define card_for_each_dev(card,dev) &bslash;&n;&t;for((dev) = card_to_pnp_dev((card)-&gt;devices.next); &bslash;&n;&t;(dev) != card_to_pnp_dev(&amp;(card)-&gt;devices); &bslash;&n;&t;(dev) = card_to_pnp_dev((dev)-&gt;card_list.next))
DECL|macro|pnp_dev_name
mdefine_line|#define pnp_dev_name(dev) (dev)-&gt;name
DECL|function|pnp_get_drvdata
r_static
r_inline
r_void
op_star
id|pnp_get_drvdata
(paren
r_struct
id|pnp_dev
op_star
id|pdev
)paren
(brace
r_return
id|dev_get_drvdata
c_func
(paren
op_amp
id|pdev-&gt;dev
)paren
suffix:semicolon
)brace
DECL|function|pnp_set_drvdata
r_static
r_inline
r_void
id|pnp_set_drvdata
(paren
r_struct
id|pnp_dev
op_star
id|pdev
comma
r_void
op_star
id|data
)paren
(brace
id|dev_set_drvdata
c_func
(paren
op_amp
id|pdev-&gt;dev
comma
id|data
)paren
suffix:semicolon
)brace
DECL|struct|pnp_fixup
r_struct
id|pnp_fixup
(brace
DECL|member|id
r_char
id|id
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|quirk_function
r_void
(paren
op_star
id|quirk_function
)paren
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* fixup function */
)brace
suffix:semicolon
multiline_comment|/* config parameters */
DECL|macro|PNP_CONFIG_NORMAL
mdefine_line|#define PNP_CONFIG_NORMAL&t;0x0001
DECL|macro|PNP_CONFIG_FORCE
mdefine_line|#define PNP_CONFIG_FORCE&t;0x0002&t;/* disables validity checking */
multiline_comment|/* capabilities */
DECL|macro|PNP_READ
mdefine_line|#define PNP_READ&t;&t;0x0001
DECL|macro|PNP_WRITE
mdefine_line|#define PNP_WRITE&t;&t;0x0002
DECL|macro|PNP_DISABLE
mdefine_line|#define PNP_DISABLE&t;&t;0x0004
DECL|macro|PNP_CONFIGURABLE
mdefine_line|#define PNP_CONFIGURABLE&t;0x0008
DECL|macro|PNP_REMOVABLE
mdefine_line|#define PNP_REMOVABLE&t;&t;0x0010
DECL|macro|pnp_can_read
mdefine_line|#define pnp_can_read(dev)&t;(((dev)-&gt;protocol) &amp;&amp; ((dev)-&gt;protocol-&gt;get) &amp;&amp; &bslash;&n;&t;&t;&t;&t; ((dev)-&gt;capabilities &amp; PNP_READ))
DECL|macro|pnp_can_write
mdefine_line|#define pnp_can_write(dev)&t;(((dev)-&gt;protocol) &amp;&amp; ((dev)-&gt;protocol-&gt;set) &amp;&amp; &bslash;&n;&t;&t;&t;&t; ((dev)-&gt;capabilities &amp; PNP_WRITE))
DECL|macro|pnp_can_disable
mdefine_line|#define pnp_can_disable(dev)&t;(((dev)-&gt;protocol) &amp;&amp; ((dev)-&gt;protocol-&gt;disable) &amp;&amp; &bslash;&n;&t;&t;&t;&t; ((dev)-&gt;capabilities &amp; PNP_DISABLE))
DECL|macro|pnp_can_configure
mdefine_line|#define pnp_can_configure(dev)&t;((!(dev)-&gt;active) &amp;&amp; &bslash;&n;&t;&t;&t;&t; ((dev)-&gt;capabilities &amp; PNP_CONFIGURABLE))
macro_line|#ifdef CONFIG_ISAPNP
r_extern
r_struct
id|pnp_protocol
id|isapnp_protocol
suffix:semicolon
DECL|macro|pnp_device_is_isapnp
mdefine_line|#define pnp_device_is_isapnp(dev) ((dev)-&gt;protocol == (&amp;isapnp_protocol))
macro_line|#else
DECL|macro|pnp_device_is_isapnp
mdefine_line|#define pnp_device_is_isapnp(dev) 0
macro_line|#endif
macro_line|#ifdef CONFIG_PNPBIOS
r_extern
r_struct
id|pnp_protocol
id|pnpbios_protocol
suffix:semicolon
DECL|macro|pnp_device_is_pnpbios
mdefine_line|#define pnp_device_is_pnpbios(dev) ((dev)-&gt;protocol == (&amp;pnpbios_protocol))
macro_line|#else
DECL|macro|pnp_device_is_pnpbios
mdefine_line|#define pnp_device_is_pnpbios(dev) 0
macro_line|#endif
multiline_comment|/* status */
DECL|macro|PNP_READY
mdefine_line|#define PNP_READY&t;&t;0x0000
DECL|macro|PNP_ATTACHED
mdefine_line|#define PNP_ATTACHED&t;&t;0x0001
DECL|macro|PNP_BUSY
mdefine_line|#define PNP_BUSY&t;&t;0x0002
DECL|macro|PNP_FAULTY
mdefine_line|#define PNP_FAULTY&t;&t;0x0004
multiline_comment|/* isapnp specific macros */
DECL|macro|isapnp_card_number
mdefine_line|#define isapnp_card_number(dev)&t;((dev)-&gt;card ? (dev)-&gt;card-&gt;number : -1)
DECL|macro|isapnp_csn_number
mdefine_line|#define isapnp_csn_number(dev)  ((dev)-&gt;number)
multiline_comment|/*&n; * Driver Management&n; */
DECL|struct|pnp_id
r_struct
id|pnp_id
(brace
DECL|member|id
r_char
id|id
(braket
id|PNP_ID_LEN
)braket
suffix:semicolon
DECL|member|next
r_struct
id|pnp_id
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pnp_driver
r_struct
id|pnp_driver
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|id_table
r_const
r_struct
id|pnp_device_id
op_star
id|id_table
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_const
r_struct
id|pnp_device_id
op_star
id|dev_id
)paren
suffix:semicolon
DECL|member|remove
r_void
(paren
op_star
id|remove
)paren
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
suffix:semicolon
DECL|member|driver
r_struct
id|device_driver
id|driver
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_pnp_driver
mdefine_line|#define&t;to_pnp_driver(drv) container_of(drv, struct pnp_driver, driver)
DECL|struct|pnp_card_driver
r_struct
id|pnp_card_driver
(brace
DECL|member|global_list
r_struct
id|list_head
id|global_list
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|id_table
r_const
r_struct
id|pnp_card_device_id
op_star
id|id_table
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_struct
id|pnp_card_link
op_star
id|card
comma
r_const
r_struct
id|pnp_card_device_id
op_star
id|card_id
)paren
suffix:semicolon
DECL|member|remove
r_void
(paren
op_star
id|remove
)paren
(paren
r_struct
id|pnp_card_link
op_star
id|card
)paren
suffix:semicolon
DECL|member|link
r_struct
id|pnp_driver
id|link
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_pnp_card_driver
mdefine_line|#define&t;to_pnp_card_driver(drv) container_of(drv, struct pnp_card_driver, link)
multiline_comment|/* pnp driver flags */
DECL|macro|PNP_DRIVER_RES_DO_NOT_CHANGE
mdefine_line|#define PNP_DRIVER_RES_DO_NOT_CHANGE&t;0x0001&t;/* do not change the state of the device */
DECL|macro|PNP_DRIVER_RES_DISABLE
mdefine_line|#define PNP_DRIVER_RES_DISABLE&t;&t;0x0003&t;/* ensure the device is disabled */
multiline_comment|/*&n; * Protocol Management&n; */
DECL|struct|pnp_protocol
r_struct
id|pnp_protocol
(brace
DECL|member|protocol_list
r_struct
id|list_head
id|protocol_list
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* resource control functions */
DECL|member|get
r_int
(paren
op_star
id|get
)paren
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_struct
id|pnp_resource_table
op_star
id|res
)paren
suffix:semicolon
DECL|member|set
r_int
(paren
op_star
id|set
)paren
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_struct
id|pnp_resource_table
op_star
id|res
)paren
suffix:semicolon
DECL|member|disable
r_int
(paren
op_star
id|disable
)paren
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* used by pnp layer only (look but don&squot;t touch) */
DECL|member|number
r_int
r_char
id|number
suffix:semicolon
multiline_comment|/* protocol number*/
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
multiline_comment|/* link to driver model */
DECL|member|cards
r_struct
id|list_head
id|cards
suffix:semicolon
DECL|member|devices
r_struct
id|list_head
id|devices
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_pnp_protocol
mdefine_line|#define to_pnp_protocol(n) list_entry(n, struct pnp_protocol, protocol_list)
DECL|macro|protocol_for_each_card
mdefine_line|#define protocol_for_each_card(protocol,card) &bslash;&n;&t;for((card) = protocol_to_pnp_card((protocol)-&gt;cards.next); &bslash;&n;&t;(card) != protocol_to_pnp_card(&amp;(protocol)-&gt;cards); &bslash;&n;&t;(card) = protocol_to_pnp_card((card)-&gt;protocol_list.next))
DECL|macro|protocol_for_each_dev
mdefine_line|#define protocol_for_each_dev(protocol,dev) &bslash;&n;&t;for((dev) = protocol_to_pnp_dev((protocol)-&gt;devices.next); &bslash;&n;&t;(dev) != protocol_to_pnp_dev(&amp;(protocol)-&gt;devices); &bslash;&n;&t;(dev) = protocol_to_pnp_dev((dev)-&gt;protocol_list.next))
macro_line|#if defined(CONFIG_PNP)
multiline_comment|/* device management */
r_int
id|pnp_register_protocol
c_func
(paren
r_struct
id|pnp_protocol
op_star
id|protocol
)paren
suffix:semicolon
r_void
id|pnp_unregister_protocol
c_func
(paren
r_struct
id|pnp_protocol
op_star
id|protocol
)paren
suffix:semicolon
r_int
id|pnp_add_device
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|pnp_remove_device
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|pnp_device_attach
c_func
(paren
r_struct
id|pnp_dev
op_star
id|pnp_dev
)paren
suffix:semicolon
r_void
id|pnp_device_detach
c_func
(paren
r_struct
id|pnp_dev
op_star
id|pnp_dev
)paren
suffix:semicolon
r_extern
r_struct
id|list_head
id|pnp_global
suffix:semicolon
multiline_comment|/* multidevice card support */
r_int
id|pnp_add_card
c_func
(paren
r_struct
id|pnp_card
op_star
id|card
)paren
suffix:semicolon
r_void
id|pnp_remove_card
c_func
(paren
r_struct
id|pnp_card
op_star
id|card
)paren
suffix:semicolon
r_int
id|pnp_add_card_device
c_func
(paren
r_struct
id|pnp_card
op_star
id|card
comma
r_struct
id|pnp_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|pnp_remove_card_device
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|pnp_add_card_id
c_func
(paren
r_struct
id|pnp_id
op_star
id|id
comma
r_struct
id|pnp_card
op_star
id|card
)paren
suffix:semicolon
r_struct
id|pnp_dev
op_star
id|pnp_request_card_device
c_func
(paren
r_struct
id|pnp_card_link
op_star
id|clink
comma
r_const
r_char
op_star
id|id
comma
r_struct
id|pnp_dev
op_star
id|from
)paren
suffix:semicolon
r_void
id|pnp_release_card_device
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|pnp_register_card_driver
c_func
(paren
r_struct
id|pnp_card_driver
op_star
id|drv
)paren
suffix:semicolon
r_void
id|pnp_unregister_card_driver
c_func
(paren
r_struct
id|pnp_card_driver
op_star
id|drv
)paren
suffix:semicolon
r_extern
r_struct
id|list_head
id|pnp_cards
suffix:semicolon
multiline_comment|/* resource management */
r_struct
id|pnp_option
op_star
id|pnp_register_independent_option
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
suffix:semicolon
r_struct
id|pnp_option
op_star
id|pnp_register_dependent_option
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|priority
)paren
suffix:semicolon
r_int
id|pnp_register_irq_resource
c_func
(paren
r_struct
id|pnp_option
op_star
id|option
comma
r_struct
id|pnp_irq
op_star
id|data
)paren
suffix:semicolon
r_int
id|pnp_register_dma_resource
c_func
(paren
r_struct
id|pnp_option
op_star
id|option
comma
r_struct
id|pnp_dma
op_star
id|data
)paren
suffix:semicolon
r_int
id|pnp_register_port_resource
c_func
(paren
r_struct
id|pnp_option
op_star
id|option
comma
r_struct
id|pnp_port
op_star
id|data
)paren
suffix:semicolon
r_int
id|pnp_register_mem_resource
c_func
(paren
r_struct
id|pnp_option
op_star
id|option
comma
r_struct
id|pnp_mem
op_star
id|data
)paren
suffix:semicolon
r_void
id|pnp_init_resource_table
c_func
(paren
r_struct
id|pnp_resource_table
op_star
id|table
)paren
suffix:semicolon
r_int
id|pnp_manual_config_dev
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_struct
id|pnp_resource_table
op_star
id|res
comma
r_int
id|mode
)paren
suffix:semicolon
r_int
id|pnp_auto_config_dev
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|pnp_validate_config
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|pnp_activate_dev
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|pnp_disable_dev
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|pnp_resource_change
c_func
(paren
r_struct
id|resource
op_star
id|resource
comma
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* protocol helpers */
r_int
id|pnp_is_active
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|compare_pnp_id
c_func
(paren
r_struct
id|pnp_id
op_star
id|pos
comma
r_const
r_char
op_star
id|id
)paren
suffix:semicolon
r_int
id|pnp_add_id
c_func
(paren
r_struct
id|pnp_id
op_star
id|id
comma
r_struct
id|pnp_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|pnp_register_driver
c_func
(paren
r_struct
id|pnp_driver
op_star
id|drv
)paren
suffix:semicolon
r_void
id|pnp_unregister_driver
c_func
(paren
r_struct
id|pnp_driver
op_star
id|drv
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* device management */
DECL|function|pnp_register_protocol
r_static
r_inline
r_int
id|pnp_register_protocol
c_func
(paren
r_struct
id|pnp_protocol
op_star
id|protocol
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pnp_unregister_protocol
r_static
r_inline
r_void
id|pnp_unregister_protocol
c_func
(paren
r_struct
id|pnp_protocol
op_star
id|protocol
)paren
(brace
)brace
DECL|function|pnp_init_device
r_static
r_inline
r_int
id|pnp_init_device
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pnp_add_device
r_static
r_inline
r_int
id|pnp_add_device
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pnp_remove_device
r_static
r_inline
r_void
id|pnp_remove_device
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
)brace
DECL|function|pnp_device_attach
r_static
r_inline
r_int
id|pnp_device_attach
c_func
(paren
r_struct
id|pnp_dev
op_star
id|pnp_dev
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pnp_device_detach
r_static
r_inline
r_void
id|pnp_device_detach
c_func
(paren
r_struct
id|pnp_dev
op_star
id|pnp_dev
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* multidevice card support */
DECL|function|pnp_add_card
r_static
r_inline
r_int
id|pnp_add_card
c_func
(paren
r_struct
id|pnp_card
op_star
id|card
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pnp_remove_card
r_static
r_inline
r_void
id|pnp_remove_card
c_func
(paren
r_struct
id|pnp_card
op_star
id|card
)paren
(brace
suffix:semicolon
)brace
DECL|function|pnp_add_card_device
r_static
r_inline
r_int
id|pnp_add_card_device
c_func
(paren
r_struct
id|pnp_card
op_star
id|card
comma
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pnp_remove_card_device
r_static
r_inline
r_void
id|pnp_remove_card_device
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
suffix:semicolon
)brace
DECL|function|pnp_add_card_id
r_static
r_inline
r_int
id|pnp_add_card_id
c_func
(paren
r_struct
id|pnp_id
op_star
id|id
comma
r_struct
id|pnp_card
op_star
id|card
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pnp_request_card_device
r_static
r_inline
r_struct
id|pnp_dev
op_star
id|pnp_request_card_device
c_func
(paren
r_struct
id|pnp_card_link
op_star
id|clink
comma
r_const
r_char
op_star
id|id
comma
r_struct
id|pnp_dev
op_star
id|from
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|pnp_release_card_device
r_static
r_inline
r_void
id|pnp_release_card_device
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
suffix:semicolon
)brace
DECL|function|pnp_register_card_driver
r_static
r_inline
r_int
id|pnp_register_card_driver
c_func
(paren
r_struct
id|pnp_card_driver
op_star
id|drv
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pnp_unregister_card_driver
r_static
r_inline
r_void
id|pnp_unregister_card_driver
c_func
(paren
r_struct
id|pnp_card_driver
op_star
id|drv
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* resource management */
DECL|function|pnp_register_independent_option
r_static
r_inline
r_struct
id|pnp_option
op_star
id|pnp_register_independent_option
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|pnp_register_dependent_option
r_static
r_inline
r_struct
id|pnp_option
op_star
id|pnp_register_dependent_option
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|priority
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|pnp_register_irq_resource
r_static
r_inline
r_int
id|pnp_register_irq_resource
c_func
(paren
r_struct
id|pnp_option
op_star
id|option
comma
r_struct
id|pnp_irq
op_star
id|data
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pnp_register_dma_resource
r_static
r_inline
r_int
id|pnp_register_dma_resource
c_func
(paren
r_struct
id|pnp_option
op_star
id|option
comma
r_struct
id|pnp_dma
op_star
id|data
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pnp_register_port_resource
r_static
r_inline
r_int
id|pnp_register_port_resource
c_func
(paren
r_struct
id|pnp_option
op_star
id|option
comma
r_struct
id|pnp_port
op_star
id|data
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pnp_register_mem_resource
r_static
r_inline
r_int
id|pnp_register_mem_resource
c_func
(paren
r_struct
id|pnp_option
op_star
id|option
comma
r_struct
id|pnp_mem
op_star
id|data
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pnp_init_resource_table
r_static
r_inline
r_void
id|pnp_init_resource_table
c_func
(paren
r_struct
id|pnp_resource_table
op_star
id|table
)paren
(brace
)brace
DECL|function|pnp_manual_config_dev
r_static
r_inline
r_int
id|pnp_manual_config_dev
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_struct
id|pnp_resource_table
op_star
id|res
comma
r_int
id|mode
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pnp_auto_config_dev
r_static
r_inline
r_int
id|pnp_auto_config_dev
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pnp_validate_config
r_static
r_inline
r_int
id|pnp_validate_config
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pnp_activate_dev
r_static
r_inline
r_int
id|pnp_activate_dev
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pnp_disable_dev
r_static
r_inline
r_int
id|pnp_disable_dev
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pnp_resource_change
r_static
r_inline
r_void
id|pnp_resource_change
c_func
(paren
r_struct
id|resource
op_star
id|resource
comma
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
(brace
)brace
multiline_comment|/* protocol helpers */
DECL|function|pnp_is_active
r_static
r_inline
r_int
id|pnp_is_active
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|compare_pnp_id
r_static
r_inline
r_int
id|compare_pnp_id
c_func
(paren
r_struct
id|pnp_id
op_star
id|pos
comma
r_const
r_char
op_star
id|id
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pnp_add_id
r_static
r_inline
r_int
id|pnp_add_id
c_func
(paren
r_struct
id|pnp_id
op_star
id|id
comma
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pnp_register_driver
r_static
r_inline
r_int
id|pnp_register_driver
c_func
(paren
r_struct
id|pnp_driver
op_star
id|drv
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pnp_unregister_driver
r_static
r_inline
r_void
id|pnp_unregister_driver
c_func
(paren
r_struct
id|pnp_driver
op_star
id|drv
)paren
(brace
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PNP */
DECL|macro|pnp_err
mdefine_line|#define pnp_err(format, arg...) printk(KERN_ERR &quot;pnp: &quot; format &quot;&bslash;n&quot; , ## arg)
DECL|macro|pnp_info
mdefine_line|#define pnp_info(format, arg...) printk(KERN_INFO &quot;pnp: &quot; format &quot;&bslash;n&quot; , ## arg)
DECL|macro|pnp_warn
mdefine_line|#define pnp_warn(format, arg...) printk(KERN_WARNING &quot;pnp: &quot; format &quot;&bslash;n&quot; , ## arg)
macro_line|#ifdef DEBUG
DECL|macro|pnp_dbg
mdefine_line|#define pnp_dbg(format, arg...) printk(KERN_DEBUG &quot;pnp: &quot; format &quot;&bslash;n&quot; , ## arg)
macro_line|#else
DECL|macro|pnp_dbg
mdefine_line|#define pnp_dbg(format, arg...) do {} while (0)
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_PNP_H */
eof
