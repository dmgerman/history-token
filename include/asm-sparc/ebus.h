multiline_comment|/* $Id: ebus.h,v 1.2 1999/09/11 23:05:55 zaitcev Exp $&n; * ebus.h: PCI to Ebus pseudo driver software state.&n; *&n; * Copyright (C) 1997 Eddie C. Dost (ecd@skynet.be) &n; *&n; * Adopted for sparc by V. Roganov and G. Raiko.&n; */
macro_line|#ifndef __SPARC_EBUS_H
DECL|macro|__SPARC_EBUS_H
mdefine_line|#define __SPARC_EBUS_H
macro_line|#ifndef _LINUX_IOPORT_H
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/oplib.h&gt;
DECL|struct|linux_ebus_child
r_struct
id|linux_ebus_child
(brace
DECL|member|next
r_struct
id|linux_ebus_child
op_star
id|next
suffix:semicolon
DECL|member|parent
r_struct
id|linux_ebus_device
op_star
id|parent
suffix:semicolon
DECL|member|bus
r_struct
id|linux_ebus
op_star
id|bus
suffix:semicolon
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
DECL|member|prom_name
r_char
id|prom_name
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|resource
r_struct
id|resource
id|resource
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
DECL|member|num_addrs
r_int
id|num_addrs
suffix:semicolon
DECL|member|irqs
r_int
r_int
id|irqs
(braket
id|PROMINTR_MAX
)braket
suffix:semicolon
DECL|member|num_irqs
r_int
id|num_irqs
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|linux_ebus_device
r_struct
id|linux_ebus_device
(brace
DECL|member|next
r_struct
id|linux_ebus_device
op_star
id|next
suffix:semicolon
DECL|member|children
r_struct
id|linux_ebus_child
op_star
id|children
suffix:semicolon
DECL|member|bus
r_struct
id|linux_ebus
op_star
id|bus
suffix:semicolon
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
DECL|member|prom_name
r_char
id|prom_name
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|resource
r_struct
id|resource
id|resource
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
DECL|member|num_addrs
r_int
id|num_addrs
suffix:semicolon
DECL|member|irqs
r_int
r_int
id|irqs
(braket
id|PROMINTR_MAX
)braket
suffix:semicolon
DECL|member|num_irqs
r_int
id|num_irqs
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|linux_ebus
r_struct
id|linux_ebus
(brace
DECL|member|next
r_struct
id|linux_ebus
op_star
id|next
suffix:semicolon
DECL|member|devices
r_struct
id|linux_ebus_device
op_star
id|devices
suffix:semicolon
DECL|member|parent
r_struct
id|linux_pbm_info
op_star
id|parent
suffix:semicolon
DECL|member|self
r_struct
id|pci_dev
op_star
id|self
suffix:semicolon
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
DECL|member|prom_name
r_char
id|prom_name
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|ebus_ranges
r_struct
id|linux_prom_ebus_ranges
id|ebus_ranges
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
DECL|member|num_ebus_ranges
r_int
id|num_ebus_ranges
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|linux_ebus_dma
r_struct
id|linux_ebus_dma
(brace
DECL|member|dcsr
r_int
r_int
id|dcsr
suffix:semicolon
DECL|member|dacr
r_int
r_int
id|dacr
suffix:semicolon
DECL|member|dbcr
r_int
r_int
id|dbcr
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EBUS_DCSR_INT_PEND
mdefine_line|#define EBUS_DCSR_INT_PEND&t;0x00000001
DECL|macro|EBUS_DCSR_ERR_PEND
mdefine_line|#define EBUS_DCSR_ERR_PEND&t;0x00000002
DECL|macro|EBUS_DCSR_DRAIN
mdefine_line|#define EBUS_DCSR_DRAIN&t;&t;0x00000004
DECL|macro|EBUS_DCSR_INT_EN
mdefine_line|#define EBUS_DCSR_INT_EN&t;0x00000010
DECL|macro|EBUS_DCSR_RESET
mdefine_line|#define EBUS_DCSR_RESET&t;&t;0x00000080
DECL|macro|EBUS_DCSR_WRITE
mdefine_line|#define EBUS_DCSR_WRITE&t;&t;0x00000100
DECL|macro|EBUS_DCSR_EN_DMA
mdefine_line|#define EBUS_DCSR_EN_DMA&t;0x00000200
DECL|macro|EBUS_DCSR_CYC_PEND
mdefine_line|#define EBUS_DCSR_CYC_PEND&t;0x00000400
DECL|macro|EBUS_DCSR_DIAG_RD_DONE
mdefine_line|#define EBUS_DCSR_DIAG_RD_DONE&t;0x00000800
DECL|macro|EBUS_DCSR_DIAG_WR_DONE
mdefine_line|#define EBUS_DCSR_DIAG_WR_DONE&t;0x00001000
DECL|macro|EBUS_DCSR_EN_CNT
mdefine_line|#define EBUS_DCSR_EN_CNT&t;0x00002000
DECL|macro|EBUS_DCSR_TC
mdefine_line|#define EBUS_DCSR_TC&t;&t;0x00004000
DECL|macro|EBUS_DCSR_DIS_CSR_DRN
mdefine_line|#define EBUS_DCSR_DIS_CSR_DRN&t;0x00010000
DECL|macro|EBUS_DCSR_BURST_SZ_MASK
mdefine_line|#define EBUS_DCSR_BURST_SZ_MASK&t;0x000c0000
DECL|macro|EBUS_DCSR_BURST_SZ_1
mdefine_line|#define EBUS_DCSR_BURST_SZ_1&t;0x00080000
DECL|macro|EBUS_DCSR_BURST_SZ_4
mdefine_line|#define EBUS_DCSR_BURST_SZ_4&t;0x00000000
DECL|macro|EBUS_DCSR_BURST_SZ_8
mdefine_line|#define EBUS_DCSR_BURST_SZ_8&t;0x00040000
DECL|macro|EBUS_DCSR_BURST_SZ_16
mdefine_line|#define EBUS_DCSR_BURST_SZ_16&t;0x000c0000
DECL|macro|EBUS_DCSR_DIAG_EN
mdefine_line|#define EBUS_DCSR_DIAG_EN&t;0x00100000
DECL|macro|EBUS_DCSR_DIS_ERR_PEND
mdefine_line|#define EBUS_DCSR_DIS_ERR_PEND&t;0x00400000
DECL|macro|EBUS_DCSR_TCI_DIS
mdefine_line|#define EBUS_DCSR_TCI_DIS&t;0x00800000
DECL|macro|EBUS_DCSR_EN_NEXT
mdefine_line|#define EBUS_DCSR_EN_NEXT&t;0x01000000
DECL|macro|EBUS_DCSR_DMA_ON
mdefine_line|#define EBUS_DCSR_DMA_ON&t;0x02000000
DECL|macro|EBUS_DCSR_A_LOADED
mdefine_line|#define EBUS_DCSR_A_LOADED&t;0x04000000
DECL|macro|EBUS_DCSR_NA_LOADED
mdefine_line|#define EBUS_DCSR_NA_LOADED&t;0x08000000
DECL|macro|EBUS_DCSR_DEV_ID_MASK
mdefine_line|#define EBUS_DCSR_DEV_ID_MASK&t;0xf0000000
r_extern
r_struct
id|linux_ebus
op_star
id|ebus_chain
suffix:semicolon
r_extern
r_void
id|ebus_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|for_each_ebus
mdefine_line|#define for_each_ebus(bus)&t;&t;&t;&t;&t;&t;&bslash;&n;        for((bus) = ebus_chain; (bus); (bus) = (bus)-&gt;next)
DECL|macro|for_each_ebusdev
mdefine_line|#define for_each_ebusdev(dev, bus)&t;&t;&t;&t;&t;&bslash;&n;        for((dev) = (bus)-&gt;devices; (dev); (dev) = (dev)-&gt;next)
DECL|macro|for_each_edevchild
mdefine_line|#define for_each_edevchild(dev, child)&t;&t;&t;&t;&t;&bslash;&n;        for((child) = (dev)-&gt;children; (child); (child) = (child)-&gt;next)
macro_line|#endif /* !(__SPARC_EBUS_H) */
eof
