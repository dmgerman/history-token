macro_line|#ifndef _LINUX_PNP_H
DECL|macro|_LINUX_PNP_H
mdefine_line|#define _LINUX_PNP_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/list.h&gt;
multiline_comment|/* Device Managemnt */
DECL|macro|DEVICE_COUNT_IRQ
mdefine_line|#define DEVICE_COUNT_IRQ&t;2
DECL|macro|DEVICE_COUNT_DMA
mdefine_line|#define DEVICE_COUNT_DMA&t;2
DECL|macro|DEVICE_COUNT_RESOURCE
mdefine_line|#define DEVICE_COUNT_RESOURCE&t;12
r_struct
id|pnp_resource
suffix:semicolon
r_struct
id|pnp_protocol
suffix:semicolon
DECL|struct|pnp_card
r_struct
id|pnp_card
(brace
multiline_comment|/* this is for ISAPNP */
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
multiline_comment|/* node in list of cards */
DECL|member|name
r_char
id|name
(braket
l_int|80
)braket
suffix:semicolon
DECL|member|number
r_int
r_char
id|number
suffix:semicolon
multiline_comment|/* card number */
DECL|member|ids
r_struct
id|list_head
id|ids
suffix:semicolon
multiline_comment|/* stores all supported dev ids */
DECL|member|devices
r_struct
id|list_head
id|devices
suffix:semicolon
multiline_comment|/* devices attached to the card */
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
DECL|macro|to_pnp_card
mdefine_line|#define to_pnp_card(n) list_entry(n, struct pnp_card, node)
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
DECL|member|ro
r_int
id|ro
suffix:semicolon
multiline_comment|/* read only */
DECL|member|dev_list
r_struct
id|list_head
id|dev_list
suffix:semicolon
multiline_comment|/* node in list of device&squot;s protocol */
DECL|member|global_list
r_struct
id|list_head
id|global_list
suffix:semicolon
DECL|member|card_list
r_struct
id|list_head
id|card_list
suffix:semicolon
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
DECL|member|ids
r_struct
id|list_head
id|ids
suffix:semicolon
multiline_comment|/* stores all supported dev ids */
DECL|member|res
r_struct
id|pnp_resources
op_star
id|res
suffix:semicolon
multiline_comment|/* possible resource information */
DECL|member|resource
r_struct
id|resource
id|resource
(braket
id|DEVICE_COUNT_RESOURCE
)braket
suffix:semicolon
multiline_comment|/* I/O and memory regions + expansion ROMs */
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
multiline_comment|/* which driver has allocated this device */
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
multiline_comment|/* Driver Model device interface */
DECL|member|driver_data
r_void
op_star
id|driver_data
suffix:semicolon
multiline_comment|/* data private to the driver */
DECL|member|protocol_data
r_void
op_star
id|protocol_data
suffix:semicolon
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
mdefine_line|#define protocol_to_pnp_dev(n) list_entry(n, struct pnp_dev, dev_list)
DECL|macro|to_pnp_dev
mdefine_line|#define&t;to_pnp_dev(n) container_of(n, struct pnp_dev, dev)
DECL|macro|pnp_for_each_dev
mdefine_line|#define pnp_for_each_dev(dev) &bslash;&n;&t;for(dev = global_to_pnp_dev(pnp_global.next); &bslash;&n;&t;dev != global_to_pnp_dev(&amp;pnp_global); &bslash;&n;&t;dev = global_to_pnp_dev(dev-&gt;global_list.next))
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
multiline_comment|/*&n; * Linux Plug and Play Support&n; * Copyright by Adam Belay &lt;ambx1@neo.rr.com&gt;&n; *&n; */
multiline_comment|/* Driver Management */
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
DECL|member|driver_data
r_int
r_int
id|driver_data
suffix:semicolon
multiline_comment|/* data private to the driver */
DECL|member|id_list
r_struct
id|list_head
id|id_list
suffix:semicolon
multiline_comment|/* node in card&squot;s or device&squot;s list */
)brace
suffix:semicolon
DECL|macro|to_pnp_id
mdefine_line|#define to_pnp_id(n) list_entry(n, struct pnp_id, id_list)
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
DECL|member|card_id_table
r_const
r_struct
id|pnp_id
op_star
id|card_id_table
suffix:semicolon
DECL|member|id_table
r_const
r_struct
id|pnp_id
op_star
id|id_table
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
id|pnp_id
op_star
id|card_id
comma
r_const
r_struct
id|pnp_id
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
multiline_comment|/* Resource Management */
DECL|macro|DEV_IO
mdefine_line|#define DEV_IO(dev, index) (dev-&gt;resource[index].start)
DECL|macro|DEV_MEM
mdefine_line|#define DEV_MEM(dev, index) (dev-&gt;resource[index+8].start)
DECL|macro|DEV_IRQ
mdefine_line|#define DEV_IRQ(dev, index) (dev-&gt;irq_resource[index].start)
DECL|macro|DEV_DMA
mdefine_line|#define DEV_DMA(dev, index) (dev-&gt;dma_resource[index].start)
DECL|macro|PNP_PORT_FLAG_16BITADDR
mdefine_line|#define PNP_PORT_FLAG_16BITADDR&t;(1&lt;&lt;0)
DECL|macro|PNP_PORT_FLAG_FIXED
mdefine_line|#define PNP_PORT_FLAG_FIXED&t;&t;(1&lt;&lt;1)
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
DECL|macro|PNP_DYNAMIC
mdefine_line|#define PNP_DYNAMIC&t;&t;0&t;/* get or set current resource */
DECL|macro|PNP_STATIC
mdefine_line|#define PNP_STATIC&t;&t;1&t;/* get or set resource for next boot */
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
id|pnp_dev
id|request
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Protocol Management */
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
comma
r_char
id|flags
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
DECL|member|devices
r_struct
id|list_head
id|devices
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_pnp_protocol
mdefine_line|#define to_pnp_protocol(n) list_entry(n, struct pnp_protocol, protocol_list)
macro_line|#if defined(CONFIG_PNP)
multiline_comment|/* core */
r_int
id|pnp_protocol_register
c_func
(paren
r_struct
id|pnp_protocol
op_star
id|protocol
)paren
suffix:semicolon
r_void
id|pnp_protocol_unregister
c_func
(paren
r_struct
id|pnp_protocol
op_star
id|protocol
)paren
suffix:semicolon
r_int
id|pnp_init_device
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
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
r_int
id|mode
)paren
suffix:semicolon
multiline_comment|/* driver */
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
multiline_comment|/* just in case anyone decides to call these without PnP Support Enabled */
DECL|function|pnp_protocol_register
r_static
r_inline
r_int
id|pnp_protocol_register
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
DECL|function|pnp_protocol_unregister
r_static
r_inline
r_void
id|pnp_protocol_unregister
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
r_int
id|mode
)paren
(brace
r_return
op_minus
id|ENODEV
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
macro_line|#if defined(CONFIG_ISAPNP)
multiline_comment|/* compat */
r_struct
id|pnp_card
op_star
id|pnp_find_card
c_func
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|device
comma
r_struct
id|pnp_card
op_star
id|from
)paren
suffix:semicolon
r_struct
id|pnp_dev
op_star
id|pnp_find_dev
c_func
(paren
r_struct
id|pnp_card
op_star
id|card
comma
r_int
r_int
id|vendor
comma
r_int
r_int
id|function
comma
r_struct
id|pnp_dev
op_star
id|from
)paren
suffix:semicolon
macro_line|#else
DECL|function|pnp_find_card
r_static
r_inline
r_struct
id|pnp_card
op_star
id|pnp_find_card
c_func
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|device
comma
r_struct
id|pnp_card
op_star
id|from
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|pnp_find_dev
r_static
r_inline
r_struct
id|pnp_dev
op_star
id|pnp_find_dev
c_func
(paren
r_struct
id|pnp_card
op_star
id|card
comma
r_int
r_int
id|vendor
comma
r_int
r_int
id|function
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
macro_line|#endif /* CONFIG_ISAPNP */
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
