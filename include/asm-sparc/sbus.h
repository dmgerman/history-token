multiline_comment|/* $Id: sbus.h,v 1.22 2000/02/18 13:50:50 davem Exp $&n; * sbus.h:  Defines for the Sun SBus.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_SBUS_H
DECL|macro|_SPARC_SBUS_H
mdefine_line|#define _SPARC_SBUS_H
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
multiline_comment|/* #include &lt;asm/iommu.h&gt; */
multiline_comment|/* Unused since we use opaque iommu (|io-unit) */
macro_line|#include &lt;asm/scatterlist.h&gt;
multiline_comment|/* We scan which devices are on the SBus using the PROM node device&n; * tree.  SBus devices are described in two different ways.  You can&n; * either get an absolute address at which to access the device, or&n; * you can get a SBus &squot;slot&squot; number and an offset within that slot.&n; */
multiline_comment|/* The base address at which to calculate device OBIO addresses. */
DECL|macro|SUN_SBUS_BVADDR
mdefine_line|#define SUN_SBUS_BVADDR        0xf8000000
DECL|macro|SBUS_OFF_MASK
mdefine_line|#define SBUS_OFF_MASK          0x01ffffff
multiline_comment|/* These routines are used to calculate device address from slot&n; * numbers + offsets, and vice versa.&n; */
DECL|function|sbus_devaddr
r_extern
id|__inline__
r_int
r_int
id|sbus_devaddr
c_func
(paren
r_int
id|slotnum
comma
r_int
r_int
id|offset
)paren
(brace
r_return
(paren
r_int
r_int
)paren
(paren
id|SUN_SBUS_BVADDR
op_plus
(paren
(paren
id|slotnum
)paren
op_lshift
l_int|25
)paren
op_plus
(paren
id|offset
)paren
)paren
suffix:semicolon
)brace
DECL|function|sbus_dev_slot
r_extern
id|__inline__
r_int
id|sbus_dev_slot
c_func
(paren
r_int
r_int
id|dev_addr
)paren
(brace
r_return
(paren
r_int
)paren
(paren
(paren
(paren
id|dev_addr
)paren
op_minus
id|SUN_SBUS_BVADDR
)paren
op_rshift
l_int|25
)paren
suffix:semicolon
)brace
r_struct
id|sbus_bus
suffix:semicolon
multiline_comment|/* Linux SBUS device tables */
DECL|struct|sbus_dev
r_struct
id|sbus_dev
(brace
DECL|member|bus
r_struct
id|sbus_bus
op_star
id|bus
suffix:semicolon
multiline_comment|/* Back ptr to sbus */
DECL|member|next
r_struct
id|sbus_dev
op_star
id|next
suffix:semicolon
multiline_comment|/* next device on this SBus or null */
DECL|member|child
r_struct
id|sbus_dev
op_star
id|child
suffix:semicolon
multiline_comment|/* For ledma and espdma on sun4m */
DECL|member|parent
r_struct
id|sbus_dev
op_star
id|parent
suffix:semicolon
multiline_comment|/* Parent device if not toplevel */
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
multiline_comment|/* PROM device tree node for this device */
DECL|member|prom_name
r_char
id|prom_name
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* PROM device name */
DECL|member|slot
r_int
id|slot
suffix:semicolon
DECL|member|resource
r_struct
id|resource
id|resource
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
DECL|member|reg_addrs
r_struct
id|linux_prom_registers
id|reg_addrs
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
DECL|member|num_registers
DECL|member|ranges_applied
r_int
id|num_registers
comma
id|ranges_applied
suffix:semicolon
DECL|member|device_ranges
r_struct
id|linux_prom_ranges
id|device_ranges
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
DECL|member|num_device_ranges
r_int
id|num_device_ranges
suffix:semicolon
DECL|member|irqs
r_int
r_int
id|irqs
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|num_irqs
r_int
id|num_irqs
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This struct describes the SBus(s) found on this machine. */
DECL|struct|sbus_bus
r_struct
id|sbus_bus
(brace
DECL|member|iommu
r_void
op_star
id|iommu
suffix:semicolon
multiline_comment|/* Opaque IOMMU cookie */
DECL|member|devices
r_struct
id|sbus_dev
op_star
id|devices
suffix:semicolon
multiline_comment|/* Link to devices on this SBus */
DECL|member|next
r_struct
id|sbus_bus
op_star
id|next
suffix:semicolon
multiline_comment|/* next SBus, if more than one SBus */
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
multiline_comment|/* PROM device tree node for this SBus */
DECL|member|prom_name
r_char
id|prom_name
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* Usually &quot;sbus&quot; or &quot;sbi&quot; */
DECL|member|clock_freq
r_int
id|clock_freq
suffix:semicolon
DECL|member|sbus_ranges
r_struct
id|linux_prom_ranges
id|sbus_ranges
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
DECL|member|num_sbus_ranges
r_int
id|num_sbus_ranges
suffix:semicolon
DECL|member|devid
r_int
id|devid
suffix:semicolon
DECL|member|board
r_int
id|board
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|sbus_bus
op_star
id|sbus_root
suffix:semicolon
r_extern
id|__inline__
r_int
DECL|function|sbus_is_slave
id|sbus_is_slave
c_func
(paren
r_struct
id|sbus_dev
op_star
id|dev
)paren
(brace
multiline_comment|/* XXX Have to write this for sun4c&squot;s */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Device probing routines could find these handy */
DECL|macro|for_each_sbus
mdefine_line|#define for_each_sbus(bus) &bslash;&n;        for((bus) = sbus_root; (bus); (bus)=(bus)-&gt;next)
DECL|macro|for_each_sbusdev
mdefine_line|#define for_each_sbusdev(device, bus) &bslash;&n;        for((device) = (bus)-&gt;devices; (device); (device)=(device)-&gt;next)
DECL|macro|for_all_sbusdev
mdefine_line|#define for_all_sbusdev(device, bus) &bslash;&n;&t;for ((bus) = sbus_root; (bus); (bus) = (bus)-&gt;next) &bslash;&n;&t;&t;for ((device) = (bus)-&gt;devices; (device); (device) = (device)-&gt;next)
multiline_comment|/* Driver DVMA interfaces. */
DECL|macro|sbus_can_dma_64bit
mdefine_line|#define sbus_can_dma_64bit(sdev)&t;(0) /* actually, sparc_cpu_model==sun4d */
DECL|macro|sbus_can_burst64
mdefine_line|#define sbus_can_burst64(sdev)&t;&t;(0) /* actually, sparc_cpu_model==sun4d */
r_extern
r_void
id|sbus_set_sbus64
c_func
(paren
r_struct
id|sbus_dev
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* These yield IOMMU mappings in consistent mode. */
r_extern
r_void
op_star
id|sbus_alloc_consistent
c_func
(paren
r_struct
id|sbus_dev
op_star
comma
r_int
comma
id|u32
op_star
id|dma_addrp
)paren
suffix:semicolon
r_extern
r_void
id|sbus_free_consistent
c_func
(paren
r_struct
id|sbus_dev
op_star
comma
r_int
comma
r_void
op_star
comma
id|u32
)paren
suffix:semicolon
DECL|macro|SBUS_DMA_BIDIRECTIONAL
mdefine_line|#define SBUS_DMA_BIDIRECTIONAL&t;0
DECL|macro|SBUS_DMA_TODEVICE
mdefine_line|#define SBUS_DMA_TODEVICE&t;1
DECL|macro|SBUS_DMA_FROMDEVICE
mdefine_line|#define SBUS_DMA_FROMDEVICE&t;2
DECL|macro|SBUS_DMA_NONE
mdefine_line|#define&t;SBUS_DMA_NONE&t;&t;3
multiline_comment|/* All the rest use streaming mode mappings. */
r_extern
id|dma_addr_t
id|sbus_map_single
c_func
(paren
r_struct
id|sbus_dev
op_star
comma
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|sbus_unmap_single
c_func
(paren
r_struct
id|sbus_dev
op_star
comma
id|dma_addr_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|sbus_map_sg
c_func
(paren
r_struct
id|sbus_dev
op_star
comma
r_struct
id|scatterlist
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|sbus_unmap_sg
c_func
(paren
r_struct
id|sbus_dev
op_star
comma
r_struct
id|scatterlist
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Finally, allow explicit synchronization of streamable mappings. */
r_extern
r_void
id|sbus_dma_sync_single_for_cpu
c_func
(paren
r_struct
id|sbus_dev
op_star
comma
id|dma_addr_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|macro|sbus_dma_sync_single
mdefine_line|#define sbus_dma_sync_single sbus_dma_sync_single_for_cpu
r_extern
r_void
id|sbus_dma_sync_single_for_device
c_func
(paren
r_struct
id|sbus_dev
op_star
comma
id|dma_addr_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|sbus_dma_sync_sg_for_cpu
c_func
(paren
r_struct
id|sbus_dev
op_star
comma
r_struct
id|scatterlist
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|macro|sbus_dma_sync_sg
mdefine_line|#define sbus_dma_sync_sg sbus_dma_sync_sg_for_cpu
r_extern
r_void
id|sbus_dma_sync_sg_for_device
c_func
(paren
r_struct
id|sbus_dev
op_star
comma
r_struct
id|scatterlist
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Eric Brower (ebrower@usa.net)&n; * Translate SBus interrupt levels to ino values--&n; * this is used when converting sbus &quot;interrupts&quot; OBP &n; * node values to &quot;intr&quot; node values, and is platform &n; * dependent.  If only we could call OBP with &n; * &quot;sbus-intr&gt;cpu (sbint -- ino)&quot; from kernel...&n; * See .../drivers/sbus/sbus.c for details.&n; */
id|BTFIXUPDEF_CALL
c_func
(paren
r_int
r_int
comma
id|sbint_to_irq
comma
r_struct
id|sbus_dev
op_star
id|sdev
comma
r_int
r_int
)paren
DECL|macro|sbint_to_irq
mdefine_line|#define sbint_to_irq(sdev, sbint) BTFIXUP_CALL(sbint_to_irq)(sdev, sbint)
macro_line|#endif /* !(_SPARC_SBUS_H) */
eof
