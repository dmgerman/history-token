multiline_comment|/*&n; * Linux Plug and Play Support&n; * Copyright by Adam Belay &lt;ambx1@neo.rr.com&gt;&n; *&n; */
macro_line|#ifndef _LINUX_PNP_H
DECL|macro|_LINUX_PNP_H
mdefine_line|#define _LINUX_PNP_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
multiline_comment|/*&n; * Device Managemnt&n; */
DECL|macro|DEVICE_COUNT_IRQ
mdefine_line|#define DEVICE_COUNT_IRQ&t;2
DECL|macro|DEVICE_COUNT_DMA
mdefine_line|#define DEVICE_COUNT_DMA&t;2
DECL|macro|DEVICE_COUNT_IO
mdefine_line|#define DEVICE_COUNT_IO&t;&t;8
DECL|macro|DEVICE_COUNT_MEM
mdefine_line|#define DEVICE_COUNT_MEM&t;4
DECL|macro|MAX_DEVICES
mdefine_line|#define MAX_DEVICES&t;&t;8
r_struct
id|pnp_resource
suffix:semicolon
r_struct
id|pnp_protocol
suffix:semicolon
r_struct
id|pnp_id
suffix:semicolon
r_struct
id|pnp_cfg
suffix:semicolon
DECL|struct|pnp_card
r_struct
id|pnp_card
(brace
DECL|member|name
r_char
id|name
(braket
l_int|80
)braket
suffix:semicolon
DECL|member|status
r_int
id|status
suffix:semicolon
multiline_comment|/* status of the card */
DECL|member|number
r_int
r_char
id|number
suffix:semicolon
multiline_comment|/* card number */
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
DECL|member|protocol_data
r_void
op_star
id|protocol_data
suffix:semicolon
multiline_comment|/* Used to store protocol specific data */
DECL|member|driver
r_struct
id|pnpc_driver
op_star
id|driver
suffix:semicolon
multiline_comment|/* pointer to the driver bound to this device */
DECL|member|rdevs
r_struct
id|list_head
id|rdevs
suffix:semicolon
multiline_comment|/* a list of devices requested by the card driver */
DECL|member|procdir
r_struct
id|proc_dir_entry
op_star
id|procdir
suffix:semicolon
multiline_comment|/* directory entry in /proc/bus/isapnp */
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
multiline_comment|/* Driver Model device interface */
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
DECL|macro|pnp_card_for_each_dev
mdefine_line|#define pnp_card_for_each_dev(card,dev) &bslash;&n;&t;for((dev) = card_to_pnp_dev((card)-&gt;devices.next); &bslash;&n;&t;(dev) != card_to_pnp_dev(&amp;(card)-&gt;devices); &bslash;&n;&t;(dev) = card_to_pnp_dev((dev)-&gt;card_list.next))
DECL|function|pnpc_get_drvdata
r_static
r_inline
r_void
op_star
id|pnpc_get_drvdata
(paren
r_struct
id|pnp_card
op_star
id|pcard
)paren
(brace
r_return
id|dev_get_drvdata
c_func
(paren
op_amp
id|pcard-&gt;dev
)paren
suffix:semicolon
)brace
DECL|function|pnpc_set_drvdata
r_static
r_inline
r_void
id|pnpc_set_drvdata
(paren
r_struct
id|pnp_card
op_star
id|pcard
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
id|pcard-&gt;dev
comma
id|data
)paren
suffix:semicolon
)brace
DECL|function|pnpc_get_protodata
r_static
r_inline
r_void
op_star
id|pnpc_get_protodata
(paren
r_struct
id|pnp_card
op_star
id|pcard
)paren
(brace
r_return
id|pcard-&gt;protocol_data
suffix:semicolon
)brace
DECL|function|pnpc_set_protodata
r_static
r_inline
r_void
id|pnpc_set_protodata
(paren
r_struct
id|pnp_card
op_star
id|pcard
comma
r_void
op_star
id|data
)paren
(brace
id|pcard-&gt;protocol_data
op_assign
id|data
suffix:semicolon
)brace
DECL|struct|pnp_dev
r_struct
id|pnp_dev
(brace
DECL|member|name
r_char
id|name
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* device name */
DECL|member|active
r_int
id|active
suffix:semicolon
multiline_comment|/* status of the device */
DECL|member|capabilities
r_int
id|capabilities
suffix:semicolon
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
DECL|member|id
r_struct
id|pnp_id
op_star
id|id
suffix:semicolon
multiline_comment|/* contains supported EISA IDs*/
DECL|member|protocol_data
r_void
op_star
id|protocol_data
suffix:semicolon
multiline_comment|/* Used to store protocol specific data */
DECL|member|number
r_int
r_char
id|number
suffix:semicolon
multiline_comment|/* must be unique */
DECL|member|regs
r_int
r_int
id|regs
suffix:semicolon
multiline_comment|/* ISAPnP: supported registers */
DECL|member|res
r_struct
id|pnp_resources
op_star
id|res
suffix:semicolon
multiline_comment|/* possible resource information */
DECL|member|lock_resources
r_int
id|lock_resources
suffix:semicolon
multiline_comment|/* resources are locked */
DECL|member|io_resource
r_struct
id|resource
id|io_resource
(braket
id|DEVICE_COUNT_IO
)braket
suffix:semicolon
multiline_comment|/* port regions */
DECL|member|mem_resource
r_struct
id|resource
id|mem_resource
(braket
id|DEVICE_COUNT_MEM
)braket
suffix:semicolon
multiline_comment|/* memory regions + expansion ROMs */
DECL|member|dma_resource
r_struct
id|resource
id|dma_resource
(braket
id|DEVICE_COUNT_DMA
)braket
suffix:semicolon
DECL|member|irq_resource
r_struct
id|resource
id|irq_resource
(braket
id|DEVICE_COUNT_IRQ
)braket
suffix:semicolon
DECL|member|driver
r_struct
id|pnp_driver
op_star
id|driver
suffix:semicolon
multiline_comment|/* pointer to the driver bound to this device */
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
multiline_comment|/* Driver Model device interface */
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
mdefine_line|#define pnp_for_each_dev(dev) &bslash;&n;&t;for(dev = global_to_pnp_dev(pnp_global.next); &bslash;&n;&t;dev != global_to_pnp_dev(&amp;pnp_global); &bslash;&n;&t;dev = global_to_pnp_dev(dev-&gt;global_list.next))
DECL|macro|card_for_each_dev
mdefine_line|#define card_for_each_dev(card,dev) &bslash;&n;&t;for((dev) = card_to_pnp_dev((card)-&gt;devices.next); &bslash;&n;&t;(dev) != card_to_pnp_dev(&amp;(card)-&gt;devices); &bslash;&n;&t;(dev) = card_to_pnp_dev((dev)-&gt;card_list.next))
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
DECL|function|pnp_get_protodata
r_static
r_inline
r_void
op_star
id|pnp_get_protodata
(paren
r_struct
id|pnp_dev
op_star
id|pdev
)paren
(brace
r_return
id|pdev-&gt;protocol_data
suffix:semicolon
)brace
DECL|function|pnp_set_protodata
r_static
r_inline
r_void
id|pnp_set_protodata
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
id|pdev-&gt;protocol_data
op_assign
id|data
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
mdefine_line|#define pnp_can_configure(dev)&t;((!(dev)-&gt;active) &amp;&amp; ((dev)-&gt;capabilities &amp; PNP_CONFIGURABLE))
multiline_comment|/* status */
DECL|macro|PNP_INIT
mdefine_line|#define PNP_INIT&t;&t;0x0000
DECL|macro|PNP_READY
mdefine_line|#define PNP_READY&t;&t;0x0001
DECL|macro|PNP_ATTACHED
mdefine_line|#define PNP_ATTACHED&t;&t;0x0002
DECL|macro|PNP_BUSY
mdefine_line|#define PNP_BUSY&t;&t;0x0004
DECL|macro|PNP_FAULTY
mdefine_line|#define PNP_FAULTY&t;&t;0x0008
multiline_comment|/*&n; * Driver Management&n; */
DECL|struct|pnp_id
r_struct
id|pnp_id
(brace
DECL|member|id
r_char
id|id
(braket
l_int|7
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
DECL|struct|pnp_device_id
r_struct
id|pnp_device_id
(brace
DECL|member|id
r_char
id|id
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|driver_data
r_int
r_int
id|driver_data
suffix:semicolon
multiline_comment|/* data private to the driver */
)brace
suffix:semicolon
DECL|struct|pnp_card_device_id
r_struct
id|pnp_card_device_id
(brace
DECL|member|id
r_char
id|id
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|driver_data
r_int
r_int
id|driver_data
suffix:semicolon
multiline_comment|/* data private to the driver */
r_struct
(brace
DECL|member|id
r_char
id|id
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|devs
)brace
id|devs
(braket
id|MAX_DEVICES
)braket
suffix:semicolon
multiline_comment|/* logical devices */
)brace
suffix:semicolon
DECL|macro|PNP_DRIVER_DO_NOT_ACTIVATE
mdefine_line|#define PNP_DRIVER_DO_NOT_ACTIVATE&t;(1&lt;&lt;0)
DECL|struct|pnp_driver
r_struct
id|pnp_driver
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
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
mdefine_line|#define&t;to_pnp_driver(drv) container_of(drv,struct pnp_driver, driver)
DECL|macro|PNPC_DRIVER_DO_NOT_ACTIVATE
mdefine_line|#define PNPC_DRIVER_DO_NOT_ACTIVATE&t;(1&lt;&lt;0)
DECL|struct|pnpc_driver
r_struct
id|pnpc_driver
(brace
DECL|member|node
r_struct
id|list_head
id|node
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
id|pnp_card
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
id|pnp_card
op_star
id|card
)paren
suffix:semicolon
DECL|member|driver
r_struct
id|device_driver
id|driver
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_pnpc_driver
mdefine_line|#define&t;to_pnpc_driver(drv) container_of(drv,struct pnpc_driver, driver)
multiline_comment|/*&n; * Resource Management&n; */
DECL|macro|pnp_flags_valid
mdefine_line|#define pnp_flags_valid(resrc)&t;(((resrc)-&gt;flags &amp; IORESOURCE_UNSET) == 0 &amp;&amp; &bslash;&n;&t;&t;&t;&t; ((resrc)-&gt;flags &amp; (IORESOURCE_IO|IORESOURCE_MEM|IORESOURCE_IRQ|IORESOURCE_DMA)) != 0)
multiline_comment|/* Use these instead of directly reading pnp_dev to get resource information */
DECL|macro|pnp_port_start
mdefine_line|#define pnp_port_start(dev,bar)&t;((dev)-&gt;io_resource[(bar)].start)
DECL|macro|pnp_port_end
mdefine_line|#define pnp_port_end(dev,bar)&t;((dev)-&gt;io_resource[(bar)].end)
DECL|macro|pnp_port_flags
mdefine_line|#define pnp_port_flags(dev,bar)&t;((dev)-&gt;io_resource[(bar)].flags)
DECL|macro|pnp_port_valid
mdefine_line|#define pnp_port_valid(dev,bar)&t;pnp_flags_valid(&amp;(dev)-&gt;io_resource[(bar)])
DECL|macro|pnp_port_len
mdefine_line|#define pnp_port_len(dev,bar) &bslash;&n;&t;((pnp_port_start((dev),(bar)) == 0 &amp;&amp;&t;&bslash;&n;&t;  pnp_port_end((dev),(bar)) ==&t;&t;&bslash;&n;&t;  pnp_port_start((dev),(bar))) ? 0 :&t;&bslash;&n;&t;  &t;&t;&t;&t;&t;&bslash;&n;&t; (pnp_port_end((dev),(bar)) -&t;&t;&bslash;&n;&t;  pnp_port_start((dev),(bar)) + 1))
DECL|macro|pnp_mem_start
mdefine_line|#define pnp_mem_start(dev,bar)&t;((dev)-&gt;mem_resource[(bar)].start)
DECL|macro|pnp_mem_end
mdefine_line|#define pnp_mem_end(dev,bar)&t;((dev)-&gt;mem_resource[(bar)].end)
DECL|macro|pnp_mem_flags
mdefine_line|#define pnp_mem_flags(dev,bar)&t;((dev)-&gt;mem_resource[(bar)].flags)
DECL|macro|pnp_mem_valid
mdefine_line|#define pnp_mem_valid(dev,bar)&t;pnp_flags_valid(&amp;(dev)-&gt;mem_resource[(bar)])
DECL|macro|pnp_mem_len
mdefine_line|#define pnp_mem_len(dev,bar) &bslash;&n;&t;((pnp_mem_start((dev),(bar)) == 0 &amp;&amp;&t;&bslash;&n;&t;  pnp_mem_end((dev),(bar)) ==&t;&t;&bslash;&n;&t;  pnp_mem_start((dev),(bar))) ? 0 :&t;&bslash;&n;&t;  &t;&t;&t;&t;&t;&bslash;&n;&t; (pnp_mem_end((dev),(bar)) -&t;&t;&bslash;&n;&t;  pnp_mem_start((dev),(bar)) + 1))
DECL|macro|pnp_irq
mdefine_line|#define pnp_irq(dev,bar)&t;((dev)-&gt;irq_resource[(bar)].start)
DECL|macro|pnp_irq_flags
mdefine_line|#define pnp_irq_flags(dev,bar)&t;((dev)-&gt;irq_resource[(bar)].flags)
DECL|macro|pnp_irq_valid
mdefine_line|#define pnp_irq_valid(dev,bar)&t;pnp_flags_valid(&amp;(dev)-&gt;irq_resource[(bar)])
DECL|macro|pnp_dma
mdefine_line|#define pnp_dma(dev,bar)&t;((dev)-&gt;dma_resource[(bar)].start)
DECL|macro|pnp_dma_flags
mdefine_line|#define pnp_dma_flags(dev,bar)&t;((dev)-&gt;dma_resource[(bar)].flags)
DECL|macro|pnp_dma_valid
mdefine_line|#define pnp_dma_valid(dev,bar)&t;pnp_flags_valid(&amp;(dev)-&gt;dma_resource[(bar)])
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
DECL|member|res
r_struct
id|pnp_resources
op_star
id|res
suffix:semicolon
multiline_comment|/* parent */
DECL|member|next
r_struct
id|pnp_port
op_star
id|next
suffix:semicolon
multiline_comment|/* next port */
)brace
suffix:semicolon
DECL|struct|pnp_irq
r_struct
id|pnp_irq
(brace
DECL|member|map
r_int
r_int
id|map
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
DECL|member|res
r_struct
id|pnp_resources
op_star
id|res
suffix:semicolon
multiline_comment|/* parent */
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
DECL|member|res
r_struct
id|pnp_resources
op_star
id|res
suffix:semicolon
multiline_comment|/* parent */
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
DECL|member|res
r_struct
id|pnp_resources
op_star
id|res
suffix:semicolon
multiline_comment|/* parent */
DECL|member|next
r_struct
id|pnp_mem
op_star
id|next
suffix:semicolon
multiline_comment|/* next memory resource */
)brace
suffix:semicolon
DECL|struct|pnp_mem32
r_struct
id|pnp_mem32
(brace
DECL|member|data
r_int
r_char
id|data
(braket
l_int|17
)braket
suffix:semicolon
DECL|member|res
r_struct
id|pnp_resources
op_star
id|res
suffix:semicolon
multiline_comment|/* parent */
DECL|member|next
r_struct
id|pnp_mem32
op_star
id|next
suffix:semicolon
multiline_comment|/* next 32-bit memory resource */
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
DECL|struct|pnp_resources
r_struct
id|pnp_resources
(brace
DECL|member|priority
r_int
r_int
id|priority
suffix:semicolon
multiline_comment|/* priority */
DECL|member|dependent
r_int
r_int
id|dependent
suffix:semicolon
multiline_comment|/* dependent resources */
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
DECL|member|mem32
r_struct
id|pnp_mem32
op_star
id|mem32
suffix:semicolon
multiline_comment|/* first 32-bit memory */
DECL|member|dev
r_struct
id|pnp_dev
op_star
id|dev
suffix:semicolon
multiline_comment|/* parent */
DECL|member|dep
r_struct
id|pnp_resources
op_star
id|dep
suffix:semicolon
multiline_comment|/* dependent resources */
)brace
suffix:semicolon
DECL|struct|pnp_res_cfg
r_struct
id|pnp_res_cfg
(brace
DECL|member|io_resource
r_struct
id|resource
id|io_resource
(braket
id|DEVICE_COUNT_IO
)braket
suffix:semicolon
multiline_comment|/* I/O ports */
DECL|member|mem_resource
r_struct
id|resource
id|mem_resource
(braket
id|DEVICE_COUNT_MEM
)braket
suffix:semicolon
multiline_comment|/* memory regions + expansion ROMs */
DECL|member|dma_resource
r_struct
id|resource
id|dma_resource
(braket
id|DEVICE_COUNT_DMA
)braket
suffix:semicolon
DECL|member|irq_resource
r_struct
id|resource
id|irq_resource
(braket
id|DEVICE_COUNT_IRQ
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pnp_cfg
r_struct
id|pnp_cfg
(brace
DECL|member|port
r_struct
id|pnp_port
op_star
id|port
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|irq
r_struct
id|pnp_irq
op_star
id|irq
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|dma
r_struct
id|pnp_dma
op_star
id|dma
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|mem
r_struct
id|pnp_mem
op_star
id|mem
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|request
r_struct
id|pnp_res_cfg
id|request
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &n; * Protocol Management&n; */
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
id|name
(braket
id|DEVICE_NAME_SIZE
)braket
suffix:semicolon
multiline_comment|/* functions */
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
id|pnp_cfg
op_star
id|config
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
multiline_comment|/* core */
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
r_extern
r_struct
id|list_head
id|pnp_global
suffix:semicolon
multiline_comment|/* resource */
r_struct
id|pnp_resources
op_star
id|pnp_build_resource
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|dependent
)paren
suffix:semicolon
r_struct
id|pnp_resources
op_star
id|pnp_find_resources
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|depnum
)paren
suffix:semicolon
r_int
id|pnp_get_max_depnum
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|pnp_add_irq_resource
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|depnum
comma
r_struct
id|pnp_irq
op_star
id|data
)paren
suffix:semicolon
r_int
id|pnp_add_dma_resource
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|depnum
comma
r_struct
id|pnp_dma
op_star
id|data
)paren
suffix:semicolon
r_int
id|pnp_add_port_resource
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|depnum
comma
r_struct
id|pnp_port
op_star
id|data
)paren
suffix:semicolon
r_int
id|pnp_add_mem_resource
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|depnum
comma
r_struct
id|pnp_mem
op_star
id|data
)paren
suffix:semicolon
r_int
id|pnp_add_mem32_resource
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|depnum
comma
r_struct
id|pnp_mem32
op_star
id|data
)paren
suffix:semicolon
r_int
id|pnp_init_res_cfg
c_func
(paren
r_struct
id|pnp_res_cfg
op_star
r_template
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
comma
r_struct
id|pnp_res_cfg
op_star
r_template
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
r_int
id|pnp_raw_set_dev
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|depnum
comma
r_struct
id|pnp_res_cfg
op_star
r_template
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
multiline_comment|/* driver */
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
macro_line|#else
multiline_comment|/* just in case anyone decides to call these without PnP Support Enabled */
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
DECL|function|pnp_build_resource
r_static
r_inline
r_struct
id|pnp_resources
op_star
id|pnp_build_resource
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|dependent
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|pnp_find_resources
r_static
r_inline
r_struct
id|pnp_resources
op_star
id|pnp_find_resources
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|depnum
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|pnp_get_max_depnum
r_static
r_inline
r_int
id|pnp_get_max_depnum
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
DECL|function|pnp_add_irq_resource
r_static
r_inline
r_int
id|pnp_add_irq_resource
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|depnum
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
DECL|function|pnp_add_dma_resource
r_static
r_inline
r_int
id|pnp_add_dma_resource
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|depnum
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
DECL|function|pnp_add_port_resource
r_static
r_inline
r_int
id|pnp_add_port_resource
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|depnum
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
DECL|function|pnp_add_mem_resource
r_static
r_inline
r_int
id|pnp_add_mem_resource
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|depnum
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
DECL|function|pnp_add_mem32_resource
r_static
r_inline
r_int
id|pnp_add_mem32_resource
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|depnum
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
DECL|function|pnp_init_res_cfg
r_static
r_inline
r_int
id|pnp_init_res_cfg
c_func
(paren
r_struct
id|pnp_res_cfg
op_star
r_template
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
comma
r_struct
id|pnp_res_cfg
op_star
r_template
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
DECL|function|pnp_raw_set_dev
r_static
r_inline
r_int
id|pnp_raw_set_dev
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|depnum
comma
r_struct
id|pnp_res_cfg
op_star
r_template
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
id|list_head
op_star
id|id_list
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
macro_line|#endif /* CONFIG_PNP */
macro_line|#if defined(CONFIG_PNP_CARD)
multiline_comment|/* card */
r_int
id|pnpc_add_card
c_func
(paren
r_struct
id|pnp_card
op_star
id|card
)paren
suffix:semicolon
r_void
id|pnpc_remove_card
c_func
(paren
r_struct
id|pnp_card
op_star
id|card
)paren
suffix:semicolon
r_int
id|pnpc_add_device
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
id|pnpc_remove_device
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
suffix:semicolon
r_struct
id|pnp_dev
op_star
id|pnp_request_card_device
c_func
(paren
r_struct
id|pnp_card
op_star
id|card
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
id|pnpc_register_driver
c_func
(paren
r_struct
id|pnpc_driver
op_star
id|drv
)paren
suffix:semicolon
r_void
id|pnpc_unregister_driver
c_func
(paren
r_struct
id|pnpc_driver
op_star
id|drv
)paren
suffix:semicolon
r_int
id|pnpc_add_id
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
r_extern
r_struct
id|list_head
id|pnp_cards
suffix:semicolon
r_int
id|pnpc_attach
c_func
(paren
r_struct
id|pnp_card
op_star
id|card
)paren
suffix:semicolon
r_void
id|pnpc_detach
c_func
(paren
r_struct
id|pnp_card
op_star
id|card
)paren
suffix:semicolon
macro_line|#else
DECL|function|pnpc_add_card
r_static
r_inline
r_int
id|pnpc_add_card
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
DECL|function|pnpc_remove_card
r_static
r_inline
r_void
id|pnpc_remove_card
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
DECL|function|pnpc_add_device
r_static
r_inline
r_int
id|pnpc_add_device
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
DECL|function|pnpc_remove_device
r_static
r_inline
r_void
id|pnpc_remove_device
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
id|pnp_card
op_star
id|card
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
DECL|function|pnpc_register_driver
r_static
r_inline
r_int
id|pnpc_register_driver
c_func
(paren
r_struct
id|pnpc_driver
op_star
id|drv
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pnpc_unregister_driver
r_static
r_inline
r_void
id|pnpc_unregister_driver
c_func
(paren
r_struct
id|pnpc_driver
op_star
id|drv
)paren
(brace
suffix:semicolon
)brace
DECL|function|pnpc_add_id
r_static
r_inline
r_int
id|pnpc_add_id
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
DECL|function|pnpc_attach
r_static
r_inline
r_int
id|pnpc_attach
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
DECL|function|pnpc_detach
r_static
r_inline
r_void
id|pnpc_detach
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
macro_line|#endif /* CONFIG_PNP_CARD */
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
