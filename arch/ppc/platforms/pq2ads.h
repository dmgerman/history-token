multiline_comment|/*&n; * A collection of structures, addresses, and values associated with&n; * the Motorola MPC8260ADS/MPC8266ADS-PCI boards.&n; * Copied from the RPX-Classic and SBS8260 stuff.&n; *&n; * Copyright (c) 2001 Dan Malek (dan@mvista.com)&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __MACH_ADS8260_DEFS
DECL|macro|__MACH_ADS8260_DEFS
mdefine_line|#define __MACH_ADS8260_DEFS
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ppcboot.h&gt;
multiline_comment|/* Memory map is configured by the PROM startup.&n; * We just map a few things we need.  The CSR is actually 4 byte-wide&n; * registers that can be accessed as 8-, 16-, or 32-bit values.&n; */
DECL|macro|CPM_MAP_ADDR
mdefine_line|#define CPM_MAP_ADDR&t;&t;((uint)0xf0000000)
DECL|macro|BCSR_ADDR
mdefine_line|#define BCSR_ADDR&t;&t;((uint)0xf4500000)
DECL|macro|BCSR_SIZE
mdefine_line|#define BCSR_SIZE&t;&t;((uint)(32 * 1024))
DECL|macro|BOOTROM_RESTART_ADDR
mdefine_line|#define BOOTROM_RESTART_ADDR&t;((uint)0xff000104)
multiline_comment|/* For our show_cpuinfo hooks. */
DECL|macro|CPUINFO_VENDOR
mdefine_line|#define CPUINFO_VENDOR&t;&t;&quot;Motorola&quot;
DECL|macro|CPUINFO_MACHINE
mdefine_line|#define CPUINFO_MACHINE&t;&t;&quot;PQ2 ADS PowerPC&quot;
multiline_comment|/* The ADS8260 has 16, 32-bit wide control/status registers, accessed&n; * only on word boundaries.&n; * Not all are used (yet), or are interesting to us (yet).&n; */
multiline_comment|/* Things of interest in the CSR.&n;*/
DECL|macro|BCSR0_LED0
mdefine_line|#define BCSR0_LED0&t;&t;((uint)0x02000000)&t;/* 0 == on */
DECL|macro|BCSR0_LED1
mdefine_line|#define BCSR0_LED1&t;&t;((uint)0x01000000)&t;/* 0 == on */
DECL|macro|BCSR1_FETHIEN
mdefine_line|#define BCSR1_FETHIEN&t;&t;((uint)0x08000000)&t;/* 0 == enable */
DECL|macro|BCSR1_FETH_RST
mdefine_line|#define BCSR1_FETH_RST&t;&t;((uint)0x04000000)&t;/* 0 == reset */
DECL|macro|BCSR1_RS232_EN1
mdefine_line|#define BCSR1_RS232_EN1&t;&t;((uint)0x02000000)&t;/* 0 == enable */
DECL|macro|BCSR1_RS232_EN2
mdefine_line|#define BCSR1_RS232_EN2&t;&t;((uint)0x01000000)&t;/* 0 == enable */
DECL|macro|BCSR3_FETHIEN2
mdefine_line|#define BCSR3_FETHIEN2&t;&t;((uint)0x10000000)&t;/* 0 == enable */
DECL|macro|BCSR3_FETH2_RST
mdefine_line|#define BCSR3_FETH2_RST &t;((uint)0x80000000)&t;/* 0 == reset */
DECL|macro|PHY_INTERRUPT
mdefine_line|#define PHY_INTERRUPT&t;SIU_INT_IRQ7
macro_line|#ifdef CONFIG_PCI
multiline_comment|/* PCI interrupt controller */
DECL|macro|PCI_INT_STAT_REG
mdefine_line|#define PCI_INT_STAT_REG&t;0xF8200000
DECL|macro|PCI_INT_MASK_REG
mdefine_line|#define PCI_INT_MASK_REG&t;0xF8200004
DECL|macro|PIRQA
mdefine_line|#define PIRQA&t;&t;&t;(NR_SIU_INTS + 0)
DECL|macro|PIRQB
mdefine_line|#define PIRQB&t;&t;&t;(NR_SIU_INTS + 1)
DECL|macro|PIRQC
mdefine_line|#define PIRQC&t;&t;&t;(NR_SIU_INTS + 2)
DECL|macro|PIRQD
mdefine_line|#define PIRQD&t;&t;&t;(NR_SIU_INTS + 3)
multiline_comment|/*&n; * PCI memory map definitions for MPC8266ADS-PCI.&n; *&n; * processor view&n; *&t;local address&t;&t;PCI address&t;&t;target&n; *&t;0x80000000-0x9FFFFFFF&t;0x80000000-0x9FFFFFFF&t;PCI mem with prefetch&n; *&t;0xA0000000-0xBFFFFFFF&t;0xA0000000-0xBFFFFFFF&t;PCI mem w/o prefetch&n; *&t;0xF4000000-0xF7FFFFFF&t;0x00000000-0x03FFFFFF&t;PCI IO&n; *&n; * PCI master view&n; *&t;local address&t;&t;PCI address&t;&t;target&n; *&t;0x00000000-0x1FFFFFFF&t;0x00000000-0x1FFFFFFF&t;MPC8266 local memory&n; */
multiline_comment|/* window for a PCI master to access MPC8266 memory */
DECL|macro|PCI_SLV_MEM_LOCAL
mdefine_line|#define PCI_SLV_MEM_LOCAL&t;0x00000000&t;/* Local base */
DECL|macro|PCI_SLV_MEM_BUS
mdefine_line|#define PCI_SLV_MEM_BUS&t;&t;0x00000000&t;/* PCI base */
multiline_comment|/* window for the processor to access PCI memory with prefetching */
DECL|macro|PCI_MSTR_MEM_LOCAL
mdefine_line|#define PCI_MSTR_MEM_LOCAL&t;0x80000000&t;/* Local base */
DECL|macro|PCI_MSTR_MEM_BUS
mdefine_line|#define PCI_MSTR_MEM_BUS&t;0x80000000&t;/* PCI base   */
DECL|macro|PCI_MSTR_MEM_SIZE
mdefine_line|#define PCI_MSTR_MEM_SIZE&t;0x20000000&t;/* 512MB */
multiline_comment|/* window for the processor to access PCI memory without prefetching */
DECL|macro|PCI_MSTR_MEMIO_LOCAL
mdefine_line|#define PCI_MSTR_MEMIO_LOCAL&t;0xA0000000&t;/* Local base */
DECL|macro|PCI_MSTR_MEMIO_BUS
mdefine_line|#define PCI_MSTR_MEMIO_BUS&t;0xA0000000&t;/* PCI base   */
DECL|macro|PCI_MSTR_MEMIO_SIZE
mdefine_line|#define PCI_MSTR_MEMIO_SIZE&t;0x20000000&t;/* 512MB */
multiline_comment|/* window for the processor to access PCI I/O */
DECL|macro|PCI_MSTR_IO_LOCAL
mdefine_line|#define PCI_MSTR_IO_LOCAL&t;0xF4000000&t;/* Local base */
DECL|macro|PCI_MSTR_IO_BUS
mdefine_line|#define PCI_MSTR_IO_BUS         0x00000000&t;/* PCI base   */
DECL|macro|PCI_MSTR_IO_SIZE
mdefine_line|#define PCI_MSTR_IO_SIZE        0x04000000&t;/* 64MB */
DECL|macro|_IO_BASE
mdefine_line|#define _IO_BASE&t;&t;PCI_MSTR_IO_LOCAL
DECL|macro|_ISA_MEM_BASE
mdefine_line|#define _ISA_MEM_BASE&t;&t;PCI_MSTR_MEMIO_LOCAL
DECL|macro|PCI_DRAM_OFFSET
mdefine_line|#define PCI_DRAM_OFFSET&t;&t;PCI_SLV_MEM_BUS
macro_line|#endif /* CONFIG_PCI */
macro_line|#endif /* __MACH_ADS8260_DEFS */
macro_line|#endif /* __KERNEL__ */
eof
