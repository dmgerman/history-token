multiline_comment|/*&n; * include/asm-ppc/mv64x60.h&n; *&n; * Prototypes, etc. for the Marvell/Galileo MV64x60 host bridge routines.&n; *&n; * Author: Mark A. Greer &lt;mgreer@mvista.com&gt;&n; *&n; * 2001-2002 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifndef __ASMPPC_MV64x60_H
DECL|macro|__ASMPPC_MV64x60_H
mdefine_line|#define __ASMPPC_MV64x60_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/mv64x60_defs.h&gt;
r_extern
id|u8
id|mv64x60_pci_exclude_bridge
suffix:semicolon
r_extern
id|spinlock_t
id|mv64x60_lock
suffix:semicolon
multiline_comment|/* 32-bit Window table entry defines */
DECL|macro|MV64x60_CPU2MEM_0_WIN
mdefine_line|#define&t;MV64x60_CPU2MEM_0_WIN&t;&t;&t;0
DECL|macro|MV64x60_CPU2MEM_1_WIN
mdefine_line|#define&t;MV64x60_CPU2MEM_1_WIN&t;&t;&t;1
DECL|macro|MV64x60_CPU2MEM_2_WIN
mdefine_line|#define&t;MV64x60_CPU2MEM_2_WIN&t;&t;&t;2
DECL|macro|MV64x60_CPU2MEM_3_WIN
mdefine_line|#define&t;MV64x60_CPU2MEM_3_WIN&t;&t;&t;3
DECL|macro|MV64x60_CPU2DEV_0_WIN
mdefine_line|#define&t;MV64x60_CPU2DEV_0_WIN&t;&t;&t;4
DECL|macro|MV64x60_CPU2DEV_1_WIN
mdefine_line|#define&t;MV64x60_CPU2DEV_1_WIN&t;&t;&t;5
DECL|macro|MV64x60_CPU2DEV_2_WIN
mdefine_line|#define&t;MV64x60_CPU2DEV_2_WIN&t;&t;&t;6
DECL|macro|MV64x60_CPU2DEV_3_WIN
mdefine_line|#define&t;MV64x60_CPU2DEV_3_WIN&t;&t;&t;7
DECL|macro|MV64x60_CPU2BOOT_WIN
mdefine_line|#define&t;MV64x60_CPU2BOOT_WIN&t;&t;&t;8
DECL|macro|MV64x60_CPU2PCI0_IO_WIN
mdefine_line|#define&t;MV64x60_CPU2PCI0_IO_WIN&t;&t;&t;9
DECL|macro|MV64x60_CPU2PCI0_MEM_0_WIN
mdefine_line|#define&t;MV64x60_CPU2PCI0_MEM_0_WIN&t;&t;10
DECL|macro|MV64x60_CPU2PCI0_MEM_1_WIN
mdefine_line|#define&t;MV64x60_CPU2PCI0_MEM_1_WIN&t;&t;11
DECL|macro|MV64x60_CPU2PCI0_MEM_2_WIN
mdefine_line|#define&t;MV64x60_CPU2PCI0_MEM_2_WIN&t;&t;12
DECL|macro|MV64x60_CPU2PCI0_MEM_3_WIN
mdefine_line|#define&t;MV64x60_CPU2PCI0_MEM_3_WIN&t;&t;13
DECL|macro|MV64x60_CPU2PCI1_IO_WIN
mdefine_line|#define&t;MV64x60_CPU2PCI1_IO_WIN&t;&t;&t;14
DECL|macro|MV64x60_CPU2PCI1_MEM_0_WIN
mdefine_line|#define&t;MV64x60_CPU2PCI1_MEM_0_WIN&t;&t;15
DECL|macro|MV64x60_CPU2PCI1_MEM_1_WIN
mdefine_line|#define&t;MV64x60_CPU2PCI1_MEM_1_WIN&t;&t;16
DECL|macro|MV64x60_CPU2PCI1_MEM_2_WIN
mdefine_line|#define&t;MV64x60_CPU2PCI1_MEM_2_WIN&t;&t;17
DECL|macro|MV64x60_CPU2PCI1_MEM_3_WIN
mdefine_line|#define&t;MV64x60_CPU2PCI1_MEM_3_WIN&t;&t;18
DECL|macro|MV64x60_CPU2SRAM_WIN
mdefine_line|#define&t;MV64x60_CPU2SRAM_WIN&t;&t;&t;19
DECL|macro|MV64x60_CPU2PCI0_IO_REMAP_WIN
mdefine_line|#define&t;MV64x60_CPU2PCI0_IO_REMAP_WIN&t;&t;20
DECL|macro|MV64x60_CPU2PCI1_IO_REMAP_WIN
mdefine_line|#define&t;MV64x60_CPU2PCI1_IO_REMAP_WIN&t;&t;21
DECL|macro|MV64x60_CPU_PROT_0_WIN
mdefine_line|#define&t;MV64x60_CPU_PROT_0_WIN&t;&t;&t;22
DECL|macro|MV64x60_CPU_PROT_1_WIN
mdefine_line|#define&t;MV64x60_CPU_PROT_1_WIN&t;&t;&t;23
DECL|macro|MV64x60_CPU_PROT_2_WIN
mdefine_line|#define&t;MV64x60_CPU_PROT_2_WIN&t;&t;&t;24
DECL|macro|MV64x60_CPU_PROT_3_WIN
mdefine_line|#define&t;MV64x60_CPU_PROT_3_WIN&t;&t;&t;25
DECL|macro|MV64x60_CPU_SNOOP_0_WIN
mdefine_line|#define&t;MV64x60_CPU_SNOOP_0_WIN&t;&t;&t;26
DECL|macro|MV64x60_CPU_SNOOP_1_WIN
mdefine_line|#define&t;MV64x60_CPU_SNOOP_1_WIN&t;&t;&t;27
DECL|macro|MV64x60_CPU_SNOOP_2_WIN
mdefine_line|#define&t;MV64x60_CPU_SNOOP_2_WIN&t;&t;&t;28
DECL|macro|MV64x60_CPU_SNOOP_3_WIN
mdefine_line|#define&t;MV64x60_CPU_SNOOP_3_WIN&t;&t;&t;29
DECL|macro|MV64x60_PCI02MEM_REMAP_0_WIN
mdefine_line|#define&t;MV64x60_PCI02MEM_REMAP_0_WIN&t;&t;30
DECL|macro|MV64x60_PCI02MEM_REMAP_1_WIN
mdefine_line|#define&t;MV64x60_PCI02MEM_REMAP_1_WIN&t;&t;31
DECL|macro|MV64x60_PCI02MEM_REMAP_2_WIN
mdefine_line|#define&t;MV64x60_PCI02MEM_REMAP_2_WIN&t;&t;32
DECL|macro|MV64x60_PCI02MEM_REMAP_3_WIN
mdefine_line|#define&t;MV64x60_PCI02MEM_REMAP_3_WIN&t;&t;33
DECL|macro|MV64x60_PCI12MEM_REMAP_0_WIN
mdefine_line|#define&t;MV64x60_PCI12MEM_REMAP_0_WIN&t;&t;34
DECL|macro|MV64x60_PCI12MEM_REMAP_1_WIN
mdefine_line|#define&t;MV64x60_PCI12MEM_REMAP_1_WIN&t;&t;35
DECL|macro|MV64x60_PCI12MEM_REMAP_2_WIN
mdefine_line|#define&t;MV64x60_PCI12MEM_REMAP_2_WIN&t;&t;36
DECL|macro|MV64x60_PCI12MEM_REMAP_3_WIN
mdefine_line|#define&t;MV64x60_PCI12MEM_REMAP_3_WIN&t;&t;37
DECL|macro|MV64x60_ENET2MEM_0_WIN
mdefine_line|#define&t;MV64x60_ENET2MEM_0_WIN&t;&t;&t;38
DECL|macro|MV64x60_ENET2MEM_1_WIN
mdefine_line|#define&t;MV64x60_ENET2MEM_1_WIN&t;&t;&t;39
DECL|macro|MV64x60_ENET2MEM_2_WIN
mdefine_line|#define&t;MV64x60_ENET2MEM_2_WIN&t;&t;&t;40
DECL|macro|MV64x60_ENET2MEM_3_WIN
mdefine_line|#define&t;MV64x60_ENET2MEM_3_WIN&t;&t;&t;41
DECL|macro|MV64x60_ENET2MEM_4_WIN
mdefine_line|#define&t;MV64x60_ENET2MEM_4_WIN&t;&t;&t;42
DECL|macro|MV64x60_ENET2MEM_5_WIN
mdefine_line|#define&t;MV64x60_ENET2MEM_5_WIN&t;&t;&t;43
DECL|macro|MV64x60_MPSC2MEM_0_WIN
mdefine_line|#define&t;MV64x60_MPSC2MEM_0_WIN&t;&t;&t;44
DECL|macro|MV64x60_MPSC2MEM_1_WIN
mdefine_line|#define&t;MV64x60_MPSC2MEM_1_WIN&t;&t;&t;45
DECL|macro|MV64x60_MPSC2MEM_2_WIN
mdefine_line|#define&t;MV64x60_MPSC2MEM_2_WIN&t;&t;&t;46
DECL|macro|MV64x60_MPSC2MEM_3_WIN
mdefine_line|#define&t;MV64x60_MPSC2MEM_3_WIN&t;&t;&t;47
DECL|macro|MV64x60_IDMA2MEM_0_WIN
mdefine_line|#define&t;MV64x60_IDMA2MEM_0_WIN&t;&t;&t;48
DECL|macro|MV64x60_IDMA2MEM_1_WIN
mdefine_line|#define&t;MV64x60_IDMA2MEM_1_WIN&t;&t;&t;49
DECL|macro|MV64x60_IDMA2MEM_2_WIN
mdefine_line|#define&t;MV64x60_IDMA2MEM_2_WIN&t;&t;&t;50
DECL|macro|MV64x60_IDMA2MEM_3_WIN
mdefine_line|#define&t;MV64x60_IDMA2MEM_3_WIN&t;&t;&t;51
DECL|macro|MV64x60_IDMA2MEM_4_WIN
mdefine_line|#define&t;MV64x60_IDMA2MEM_4_WIN&t;&t;&t;52
DECL|macro|MV64x60_IDMA2MEM_5_WIN
mdefine_line|#define&t;MV64x60_IDMA2MEM_5_WIN&t;&t;&t;53
DECL|macro|MV64x60_IDMA2MEM_6_WIN
mdefine_line|#define&t;MV64x60_IDMA2MEM_6_WIN&t;&t;&t;54
DECL|macro|MV64x60_IDMA2MEM_7_WIN
mdefine_line|#define&t;MV64x60_IDMA2MEM_7_WIN&t;&t;&t;55
DECL|macro|MV64x60_32BIT_WIN_COUNT
mdefine_line|#define&t;MV64x60_32BIT_WIN_COUNT&t;&t;&t;56
multiline_comment|/* 64-bit Window table entry defines */
DECL|macro|MV64x60_CPU2PCI0_MEM_0_REMAP_WIN
mdefine_line|#define&t;MV64x60_CPU2PCI0_MEM_0_REMAP_WIN&t;0
DECL|macro|MV64x60_CPU2PCI0_MEM_1_REMAP_WIN
mdefine_line|#define&t;MV64x60_CPU2PCI0_MEM_1_REMAP_WIN&t;1
DECL|macro|MV64x60_CPU2PCI0_MEM_2_REMAP_WIN
mdefine_line|#define&t;MV64x60_CPU2PCI0_MEM_2_REMAP_WIN&t;2
DECL|macro|MV64x60_CPU2PCI0_MEM_3_REMAP_WIN
mdefine_line|#define&t;MV64x60_CPU2PCI0_MEM_3_REMAP_WIN&t;3
DECL|macro|MV64x60_CPU2PCI1_MEM_0_REMAP_WIN
mdefine_line|#define&t;MV64x60_CPU2PCI1_MEM_0_REMAP_WIN&t;4
DECL|macro|MV64x60_CPU2PCI1_MEM_1_REMAP_WIN
mdefine_line|#define&t;MV64x60_CPU2PCI1_MEM_1_REMAP_WIN&t;5
DECL|macro|MV64x60_CPU2PCI1_MEM_2_REMAP_WIN
mdefine_line|#define&t;MV64x60_CPU2PCI1_MEM_2_REMAP_WIN&t;6
DECL|macro|MV64x60_CPU2PCI1_MEM_3_REMAP_WIN
mdefine_line|#define&t;MV64x60_CPU2PCI1_MEM_3_REMAP_WIN&t;7
DECL|macro|MV64x60_PCI02MEM_ACC_CNTL_0_WIN
mdefine_line|#define&t;MV64x60_PCI02MEM_ACC_CNTL_0_WIN&t;&t;8
DECL|macro|MV64x60_PCI02MEM_ACC_CNTL_1_WIN
mdefine_line|#define&t;MV64x60_PCI02MEM_ACC_CNTL_1_WIN&t;&t;9
DECL|macro|MV64x60_PCI02MEM_ACC_CNTL_2_WIN
mdefine_line|#define&t;MV64x60_PCI02MEM_ACC_CNTL_2_WIN&t;&t;10
DECL|macro|MV64x60_PCI02MEM_ACC_CNTL_3_WIN
mdefine_line|#define&t;MV64x60_PCI02MEM_ACC_CNTL_3_WIN&t;&t;11
DECL|macro|MV64x60_PCI12MEM_ACC_CNTL_0_WIN
mdefine_line|#define&t;MV64x60_PCI12MEM_ACC_CNTL_0_WIN&t;&t;12
DECL|macro|MV64x60_PCI12MEM_ACC_CNTL_1_WIN
mdefine_line|#define&t;MV64x60_PCI12MEM_ACC_CNTL_1_WIN&t;&t;13
DECL|macro|MV64x60_PCI12MEM_ACC_CNTL_2_WIN
mdefine_line|#define&t;MV64x60_PCI12MEM_ACC_CNTL_2_WIN&t;&t;14
DECL|macro|MV64x60_PCI12MEM_ACC_CNTL_3_WIN
mdefine_line|#define&t;MV64x60_PCI12MEM_ACC_CNTL_3_WIN&t;&t;15
DECL|macro|MV64x60_PCI02MEM_SNOOP_0_WIN
mdefine_line|#define&t;MV64x60_PCI02MEM_SNOOP_0_WIN&t;&t;16
DECL|macro|MV64x60_PCI02MEM_SNOOP_1_WIN
mdefine_line|#define&t;MV64x60_PCI02MEM_SNOOP_1_WIN&t;&t;17
DECL|macro|MV64x60_PCI02MEM_SNOOP_2_WIN
mdefine_line|#define&t;MV64x60_PCI02MEM_SNOOP_2_WIN&t;&t;18
DECL|macro|MV64x60_PCI02MEM_SNOOP_3_WIN
mdefine_line|#define&t;MV64x60_PCI02MEM_SNOOP_3_WIN&t;&t;19
DECL|macro|MV64x60_PCI12MEM_SNOOP_0_WIN
mdefine_line|#define&t;MV64x60_PCI12MEM_SNOOP_0_WIN&t;&t;20
DECL|macro|MV64x60_PCI12MEM_SNOOP_1_WIN
mdefine_line|#define&t;MV64x60_PCI12MEM_SNOOP_1_WIN&t;&t;21
DECL|macro|MV64x60_PCI12MEM_SNOOP_2_WIN
mdefine_line|#define&t;MV64x60_PCI12MEM_SNOOP_2_WIN&t;&t;22
DECL|macro|MV64x60_PCI12MEM_SNOOP_3_WIN
mdefine_line|#define&t;MV64x60_PCI12MEM_SNOOP_3_WIN&t;&t;23
DECL|macro|MV64x60_64BIT_WIN_COUNT
mdefine_line|#define&t;MV64x60_64BIT_WIN_COUNT&t;&t;&t;24
multiline_comment|/*&n; * Define a structure that&squot;s used to pass in config information to the&n; * core routines.&n; */
DECL|struct|mv64x60_pci_window
r_struct
id|mv64x60_pci_window
(brace
DECL|member|cpu_base
id|u32
id|cpu_base
suffix:semicolon
DECL|member|pci_base_hi
id|u32
id|pci_base_hi
suffix:semicolon
DECL|member|pci_base_lo
id|u32
id|pci_base_lo
suffix:semicolon
DECL|member|size
id|u32
id|size
suffix:semicolon
DECL|member|swap
id|u32
id|swap
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mv64x60_pci_info
r_struct
id|mv64x60_pci_info
(brace
DECL|member|enable_bus
id|u8
id|enable_bus
suffix:semicolon
multiline_comment|/* allow access to this PCI bus? */
DECL|member|pci_io
r_struct
id|mv64x60_pci_window
id|pci_io
suffix:semicolon
DECL|member|pci_mem
r_struct
id|mv64x60_pci_window
id|pci_mem
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|acc_cntl_options
id|u32
id|acc_cntl_options
(braket
id|MV64x60_CPU2MEM_WINDOWS
)braket
suffix:semicolon
DECL|member|snoop_options
id|u32
id|snoop_options
(braket
id|MV64x60_CPU2MEM_WINDOWS
)braket
suffix:semicolon
DECL|member|pci_cmd_bits
id|u16
id|pci_cmd_bits
suffix:semicolon
DECL|member|latency_timer
id|u16
id|latency_timer
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mv64x60_setup_info
r_struct
id|mv64x60_setup_info
(brace
DECL|member|phys_reg_base
id|u32
id|phys_reg_base
suffix:semicolon
DECL|member|window_preserve_mask_32_hi
id|u32
id|window_preserve_mask_32_hi
suffix:semicolon
DECL|member|window_preserve_mask_32_lo
id|u32
id|window_preserve_mask_32_lo
suffix:semicolon
DECL|member|window_preserve_mask_64
id|u32
id|window_preserve_mask_64
suffix:semicolon
DECL|member|cpu_prot_options
id|u32
id|cpu_prot_options
(braket
id|MV64x60_CPU2MEM_WINDOWS
)braket
suffix:semicolon
DECL|member|cpu_snoop_options
id|u32
id|cpu_snoop_options
(braket
id|MV64x60_CPU2MEM_WINDOWS
)braket
suffix:semicolon
DECL|member|enet_options
id|u32
id|enet_options
(braket
id|MV64x60_CPU2MEM_WINDOWS
)braket
suffix:semicolon
DECL|member|mpsc_options
id|u32
id|mpsc_options
(braket
id|MV64x60_CPU2MEM_WINDOWS
)braket
suffix:semicolon
DECL|member|idma_options
id|u32
id|idma_options
(braket
id|MV64x60_CPU2MEM_WINDOWS
)braket
suffix:semicolon
DECL|member|pci_0
r_struct
id|mv64x60_pci_info
id|pci_0
suffix:semicolon
DECL|member|pci_1
r_struct
id|mv64x60_pci_info
id|pci_1
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Define what the top bits in the extra member of a window entry means. */
DECL|macro|MV64x60_EXTRA_INVALID
mdefine_line|#define&t;MV64x60_EXTRA_INVALID&t;&t;0x00000000
DECL|macro|MV64x60_EXTRA_CPUWIN_ENAB
mdefine_line|#define&t;MV64x60_EXTRA_CPUWIN_ENAB&t;0x10000000
DECL|macro|MV64x60_EXTRA_CPUPROT_ENAB
mdefine_line|#define&t;MV64x60_EXTRA_CPUPROT_ENAB&t;0x20000000
DECL|macro|MV64x60_EXTRA_ENET_ENAB
mdefine_line|#define&t;MV64x60_EXTRA_ENET_ENAB&t;&t;0x30000000
DECL|macro|MV64x60_EXTRA_MPSC_ENAB
mdefine_line|#define&t;MV64x60_EXTRA_MPSC_ENAB&t;&t;0x40000000
DECL|macro|MV64x60_EXTRA_IDMA_ENAB
mdefine_line|#define&t;MV64x60_EXTRA_IDMA_ENAB&t;&t;0x50000000
DECL|macro|MV64x60_EXTRA_PCIACC_ENAB
mdefine_line|#define&t;MV64x60_EXTRA_PCIACC_ENAB&t;0x60000000
DECL|macro|MV64x60_EXTRA_MASK
mdefine_line|#define&t;MV64x60_EXTRA_MASK&t;&t;0xf0000000
multiline_comment|/*&n; * Define the &squot;handle&squot; struct that will be passed between the 64x60 core&n; * code and the platform-specific code that will use it.  The handle&n; * will contain pointers to chip-specific routines &amp; information.&n; */
DECL|struct|mv64x60_32bit_window
r_struct
id|mv64x60_32bit_window
(brace
DECL|member|base_reg
id|u32
id|base_reg
suffix:semicolon
DECL|member|size_reg
id|u32
id|size_reg
suffix:semicolon
DECL|member|base_bits
id|u8
id|base_bits
suffix:semicolon
DECL|member|size_bits
id|u8
id|size_bits
suffix:semicolon
DECL|member|get_from_field
id|u32
(paren
op_star
id|get_from_field
)paren
(paren
id|u32
id|val
comma
id|u32
id|num_bits
)paren
suffix:semicolon
DECL|member|map_to_field
id|u32
(paren
op_star
id|map_to_field
)paren
(paren
id|u32
id|val
comma
id|u32
id|num_bits
)paren
suffix:semicolon
DECL|member|extra
id|u32
id|extra
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mv64x60_64bit_window
r_struct
id|mv64x60_64bit_window
(brace
DECL|member|base_hi_reg
id|u32
id|base_hi_reg
suffix:semicolon
DECL|member|base_lo_reg
id|u32
id|base_lo_reg
suffix:semicolon
DECL|member|size_reg
id|u32
id|size_reg
suffix:semicolon
DECL|member|base_lo_bits
id|u8
id|base_lo_bits
suffix:semicolon
DECL|member|size_bits
id|u8
id|size_bits
suffix:semicolon
DECL|member|get_from_field
id|u32
(paren
op_star
id|get_from_field
)paren
(paren
id|u32
id|val
comma
id|u32
id|num_bits
)paren
suffix:semicolon
DECL|member|map_to_field
id|u32
(paren
op_star
id|map_to_field
)paren
(paren
id|u32
id|val
comma
id|u32
id|num_bits
)paren
suffix:semicolon
DECL|member|extra
id|u32
id|extra
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|mv64x60_handle_t
r_typedef
r_struct
id|mv64x60_handle
id|mv64x60_handle_t
suffix:semicolon
DECL|struct|mv64x60_chip_info
r_struct
id|mv64x60_chip_info
(brace
DECL|member|translate_size
id|u32
(paren
op_star
id|translate_size
)paren
(paren
id|u32
id|base
comma
id|u32
id|size
comma
id|u32
id|num_bits
)paren
suffix:semicolon
DECL|member|untranslate_size
id|u32
(paren
op_star
id|untranslate_size
)paren
(paren
id|u32
id|base
comma
id|u32
id|size
comma
id|u32
id|num_bits
)paren
suffix:semicolon
DECL|member|set_pci2mem_window
r_void
(paren
op_star
id|set_pci2mem_window
)paren
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
id|u32
id|bus
comma
id|u32
id|window
comma
id|u32
id|base
)paren
suffix:semicolon
DECL|member|set_pci2regs_window
r_void
(paren
op_star
id|set_pci2regs_window
)paren
(paren
r_struct
id|mv64x60_handle
op_star
id|bh
comma
r_struct
id|pci_controller
op_star
id|hose
comma
id|u32
id|bus
comma
id|u32
id|base
)paren
suffix:semicolon
DECL|member|is_enabled_32bit
id|u32
(paren
op_star
id|is_enabled_32bit
)paren
(paren
id|mv64x60_handle_t
op_star
id|bh
comma
id|u32
id|window
)paren
suffix:semicolon
DECL|member|enable_window_32bit
r_void
(paren
op_star
id|enable_window_32bit
)paren
(paren
id|mv64x60_handle_t
op_star
id|bh
comma
id|u32
id|window
)paren
suffix:semicolon
DECL|member|disable_window_32bit
r_void
(paren
op_star
id|disable_window_32bit
)paren
(paren
id|mv64x60_handle_t
op_star
id|bh
comma
id|u32
id|window
)paren
suffix:semicolon
DECL|member|enable_window_64bit
r_void
(paren
op_star
id|enable_window_64bit
)paren
(paren
id|mv64x60_handle_t
op_star
id|bh
comma
id|u32
id|window
)paren
suffix:semicolon
DECL|member|disable_window_64bit
r_void
(paren
op_star
id|disable_window_64bit
)paren
(paren
id|mv64x60_handle_t
op_star
id|bh
comma
id|u32
id|window
)paren
suffix:semicolon
DECL|member|disable_all_windows
r_void
(paren
op_star
id|disable_all_windows
)paren
(paren
id|mv64x60_handle_t
op_star
id|bh
comma
r_struct
id|mv64x60_setup_info
op_star
id|si
)paren
suffix:semicolon
DECL|member|config_io2mem_windows
r_void
(paren
op_star
id|config_io2mem_windows
)paren
(paren
id|mv64x60_handle_t
op_star
id|bh
comma
r_struct
id|mv64x60_setup_info
op_star
id|si
comma
id|u32
id|mem_windows
(braket
id|MV64x60_CPU2MEM_WINDOWS
)braket
(braket
l_int|2
)braket
)paren
suffix:semicolon
DECL|member|set_mpsc2regs_window
r_void
(paren
op_star
id|set_mpsc2regs_window
)paren
(paren
r_struct
id|mv64x60_handle
op_star
id|bh
comma
id|u32
id|base
)paren
suffix:semicolon
DECL|member|chip_specific_init
r_void
(paren
op_star
id|chip_specific_init
)paren
(paren
id|mv64x60_handle_t
op_star
id|bh
comma
r_struct
id|mv64x60_setup_info
op_star
id|si
)paren
suffix:semicolon
DECL|member|window_tab_32bit
r_struct
id|mv64x60_32bit_window
op_star
id|window_tab_32bit
suffix:semicolon
DECL|member|window_tab_64bit
r_struct
id|mv64x60_64bit_window
op_star
id|window_tab_64bit
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mv64x60_handle
r_struct
id|mv64x60_handle
(brace
DECL|member|type
id|u32
id|type
suffix:semicolon
multiline_comment|/* type of bridge */
DECL|member|rev
id|u32
id|rev
suffix:semicolon
multiline_comment|/* revision of bridge */
DECL|member|v_base
r_void
op_star
id|v_base
suffix:semicolon
multiline_comment|/* virtual base addr of bridge regs */
DECL|member|p_base
id|phys_addr_t
id|p_base
suffix:semicolon
multiline_comment|/* physical base addr of bridge regs */
DECL|member|pci_mode_a
id|u32
id|pci_mode_a
suffix:semicolon
multiline_comment|/* pci 0 mode: conventional pci, pci-x*/
DECL|member|pci_mode_b
id|u32
id|pci_mode_b
suffix:semicolon
multiline_comment|/* pci 1 mode: conventional pci, pci-x*/
DECL|member|io_base_a
id|u32
id|io_base_a
suffix:semicolon
multiline_comment|/* vaddr of pci 0&squot;s I/O space */
DECL|member|io_base_b
id|u32
id|io_base_b
suffix:semicolon
multiline_comment|/* vaddr of pci 1&squot;s I/O space */
DECL|member|hose_a
r_struct
id|pci_controller
op_star
id|hose_a
suffix:semicolon
DECL|member|hose_b
r_struct
id|pci_controller
op_star
id|hose_b
suffix:semicolon
DECL|member|ci
r_struct
id|mv64x60_chip_info
op_star
id|ci
suffix:semicolon
multiline_comment|/* chip/bridge-specific info */
)brace
suffix:semicolon
multiline_comment|/* Define I/O routines for accessing registers on the 64x60 bridge. */
r_extern
r_inline
r_void
DECL|function|mv64x60_write
id|mv64x60_write
c_func
(paren
r_struct
id|mv64x60_handle
op_star
id|bh
comma
id|u32
id|offset
comma
id|u32
id|val
)paren
(brace
id|ulong
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|mv64x60_lock
comma
id|flags
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|bh-&gt;v_base
op_plus
id|offset
comma
id|val
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mv64x60_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_extern
r_inline
id|u32
DECL|function|mv64x60_read
id|mv64x60_read
c_func
(paren
r_struct
id|mv64x60_handle
op_star
id|bh
comma
id|u32
id|offset
)paren
(brace
id|ulong
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|mv64x60_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|in_le32
c_func
(paren
id|bh-&gt;v_base
op_plus
id|offset
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mv64x60_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_extern
r_inline
r_void
DECL|function|mv64x60_modify
id|mv64x60_modify
c_func
(paren
r_struct
id|mv64x60_handle
op_star
id|bh
comma
id|u32
id|offs
comma
id|u32
id|data
comma
id|u32
id|mask
)paren
(brace
id|u32
id|reg
suffix:semicolon
id|ulong
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|mv64x60_lock
comma
id|flags
)paren
suffix:semicolon
id|reg
op_assign
id|mv64x60_read
c_func
(paren
id|bh
comma
id|offs
)paren
op_amp
(paren
op_complement
id|mask
)paren
suffix:semicolon
multiline_comment|/* zero bits we care about */
id|reg
op_or_assign
id|data
op_amp
id|mask
suffix:semicolon
multiline_comment|/* set bits from the data */
id|mv64x60_write
c_func
(paren
id|bh
comma
id|offs
comma
id|reg
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mv64x60_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|macro|mv64x60_set_bits
mdefine_line|#define&t;mv64x60_set_bits(bh, offs, bits) mv64x60_modify(bh, offs, ~0, bits)
DECL|macro|mv64x60_clr_bits
mdefine_line|#define&t;mv64x60_clr_bits(bh, offs, bits) mv64x60_modify(bh, offs, 0, bits)
multiline_comment|/* Externally visible function prototypes */
r_int
id|mv64x60_init
c_func
(paren
r_struct
id|mv64x60_handle
op_star
id|bh
comma
r_struct
id|mv64x60_setup_info
op_star
id|si
)paren
suffix:semicolon
id|u32
id|mv64x60_get_mem_size
c_func
(paren
id|u32
id|bridge_base
comma
id|u32
id|chip_type
)paren
suffix:semicolon
r_void
id|mv64x60_early_init
c_func
(paren
r_struct
id|mv64x60_handle
op_star
id|bh
comma
r_struct
id|mv64x60_setup_info
op_star
id|si
)paren
suffix:semicolon
r_void
id|mv64x60_alloc_hose
c_func
(paren
r_struct
id|mv64x60_handle
op_star
id|bh
comma
id|u32
id|cfg_addr
comma
id|u32
id|cfg_data
comma
r_struct
id|pci_controller
op_star
op_star
id|hose
)paren
suffix:semicolon
r_int
id|mv64x60_get_type
c_func
(paren
r_struct
id|mv64x60_handle
op_star
id|bh
)paren
suffix:semicolon
r_int
id|mv64x60_setup_for_chip
c_func
(paren
r_struct
id|mv64x60_handle
op_star
id|bh
)paren
suffix:semicolon
r_void
op_star
id|mv64x60_get_bridge_vbase
c_func
(paren
r_void
)paren
suffix:semicolon
id|u32
id|mv64x60_get_bridge_type
c_func
(paren
r_void
)paren
suffix:semicolon
id|u32
id|mv64x60_get_bridge_rev
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|mv64x60_get_mem_windows
c_func
(paren
r_struct
id|mv64x60_handle
op_star
id|bh
comma
id|u32
id|mem_windows
(braket
id|MV64x60_CPU2MEM_WINDOWS
)braket
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_void
id|mv64x60_config_cpu2mem_windows
c_func
(paren
r_struct
id|mv64x60_handle
op_star
id|bh
comma
r_struct
id|mv64x60_setup_info
op_star
id|si
comma
id|u32
id|mem_windows
(braket
id|MV64x60_CPU2MEM_WINDOWS
)braket
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_void
id|mv64x60_config_cpu2pci_windows
c_func
(paren
r_struct
id|mv64x60_handle
op_star
id|bh
comma
r_struct
id|mv64x60_pci_info
op_star
id|pi
comma
id|u32
id|bus
)paren
suffix:semicolon
r_void
id|mv64x60_config_pci2mem_windows
c_func
(paren
r_struct
id|mv64x60_handle
op_star
id|bh
comma
r_struct
id|pci_controller
op_star
id|hose
comma
r_struct
id|mv64x60_pci_info
op_star
id|pi
comma
id|u32
id|bus
comma
id|u32
id|mem_windows
(braket
id|MV64x60_CPU2MEM_WINDOWS
)braket
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_void
id|mv64x60_config_resources
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
r_struct
id|mv64x60_pci_info
op_star
id|pi
comma
id|u32
id|io_base
)paren
suffix:semicolon
r_void
id|mv64x60_config_pci_params
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
r_struct
id|mv64x60_pci_info
op_star
id|pi
)paren
suffix:semicolon
r_void
id|mv64x60_pd_fixup
c_func
(paren
r_struct
id|mv64x60_handle
op_star
id|bh
comma
r_struct
id|platform_device
op_star
id|pd_devs
(braket
)braket
comma
id|u32
id|entries
)paren
suffix:semicolon
r_void
id|mv64x60_get_32bit_window
c_func
(paren
r_struct
id|mv64x60_handle
op_star
id|bh
comma
id|u32
id|window
comma
id|u32
op_star
id|base
comma
id|u32
op_star
id|size
)paren
suffix:semicolon
r_void
id|mv64x60_set_32bit_window
c_func
(paren
r_struct
id|mv64x60_handle
op_star
id|bh
comma
id|u32
id|window
comma
id|u32
id|base
comma
id|u32
id|size
comma
id|u32
id|other_bits
)paren
suffix:semicolon
r_void
id|mv64x60_get_64bit_window
c_func
(paren
r_struct
id|mv64x60_handle
op_star
id|bh
comma
id|u32
id|window
comma
id|u32
op_star
id|base_hi
comma
id|u32
op_star
id|base_lo
comma
id|u32
op_star
id|size
)paren
suffix:semicolon
r_void
id|mv64x60_set_64bit_window
c_func
(paren
r_struct
id|mv64x60_handle
op_star
id|bh
comma
id|u32
id|window
comma
id|u32
id|base_hi
comma
id|u32
id|base_lo
comma
id|u32
id|size
comma
id|u32
id|other_bits
)paren
suffix:semicolon
r_void
id|mv64x60_set_bus
c_func
(paren
r_struct
id|mv64x60_handle
op_star
id|bh
comma
id|u32
id|bus
comma
id|u32
id|child_bus
)paren
suffix:semicolon
r_int
id|mv64x60_pci_exclude_device
c_func
(paren
id|u8
id|bus
comma
id|u8
id|devfn
)paren
suffix:semicolon
r_void
id|gt64260_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|gt64260_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_void
id|mv64360_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|mv64360_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
id|u32
id|mv64x60_mask
c_func
(paren
id|u32
id|val
comma
id|u32
id|num_bits
)paren
suffix:semicolon
id|u32
id|mv64x60_shift_left
c_func
(paren
id|u32
id|val
comma
id|u32
id|num_bits
)paren
suffix:semicolon
id|u32
id|mv64x60_shift_right
c_func
(paren
id|u32
id|val
comma
id|u32
id|num_bits
)paren
suffix:semicolon
id|u32
id|mv64x60_calc_mem_size
c_func
(paren
r_struct
id|mv64x60_handle
op_star
id|bh
comma
id|u32
id|mem_windows
(braket
id|MV64x60_CPU2MEM_WINDOWS
)braket
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_void
id|mv64x60_progress_init
c_func
(paren
id|u32
id|base
)paren
suffix:semicolon
r_void
id|mv64x60_mpsc_progress
c_func
(paren
r_char
op_star
id|s
comma
r_int
r_int
id|hex
)paren
suffix:semicolon
r_extern
r_struct
id|mv64x60_32bit_window
id|gt64260_32bit_windows
(braket
id|MV64x60_32BIT_WIN_COUNT
)braket
suffix:semicolon
r_extern
r_struct
id|mv64x60_64bit_window
id|gt64260_64bit_windows
(braket
id|MV64x60_64BIT_WIN_COUNT
)braket
suffix:semicolon
r_extern
r_struct
id|mv64x60_32bit_window
id|mv64360_32bit_windows
(braket
id|MV64x60_32BIT_WIN_COUNT
)braket
suffix:semicolon
r_extern
r_struct
id|mv64x60_64bit_window
id|mv64360_64bit_windows
(braket
id|MV64x60_64BIT_WIN_COUNT
)braket
suffix:semicolon
macro_line|#endif /* __ASMPPC_MV64x60_H */
eof
