multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992-1997,2000-2004 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_PCI_PCIBR_PROVIDER_H
DECL|macro|_ASM_IA64_SN_PCI_PCIBR_PROVIDER_H
mdefine_line|#define _ASM_IA64_SN_PCI_PCIBR_PROVIDER_H
multiline_comment|/* Workarounds */
DECL|macro|PV907516
mdefine_line|#define PV907516 (1 &lt;&lt; 1) /* TIOCP: Don&squot;t write the write buffer flush reg */
DECL|macro|BUSTYPE_MASK
mdefine_line|#define BUSTYPE_MASK                    0x1
multiline_comment|/* Macros given a pcibus structure */
DECL|macro|IS_PCIX
mdefine_line|#define IS_PCIX(ps)     ((ps)-&gt;pbi_bridge_mode &amp; BUSTYPE_MASK)
DECL|macro|IS_PCI_BRIDGE_ASIC
mdefine_line|#define IS_PCI_BRIDGE_ASIC(asic) (asic == PCIIO_ASIC_TYPE_PIC || &bslash;&n;                asic == PCIIO_ASIC_TYPE_TIOCP)
DECL|macro|IS_PIC_SOFT
mdefine_line|#define IS_PIC_SOFT(ps)     (ps-&gt;pbi_bridge_type == PCIBR_BRIDGETYPE_PIC)
multiline_comment|/* &n; * The different PCI Bridge types supported on the SGI Altix platforms&n; */
DECL|macro|PCIBR_BRIDGETYPE_UNKNOWN
mdefine_line|#define PCIBR_BRIDGETYPE_UNKNOWN       -1
DECL|macro|PCIBR_BRIDGETYPE_PIC
mdefine_line|#define PCIBR_BRIDGETYPE_PIC            2
DECL|macro|PCIBR_BRIDGETYPE_TIOCP
mdefine_line|#define PCIBR_BRIDGETYPE_TIOCP          3
multiline_comment|/*&n; * Bridge 64bit Direct Map Attributes&n; */
DECL|macro|PCI64_ATTR_PREF
mdefine_line|#define PCI64_ATTR_PREF                 (1ull &lt;&lt; 59)
DECL|macro|PCI64_ATTR_PREC
mdefine_line|#define PCI64_ATTR_PREC                 (1ull &lt;&lt; 58)
DECL|macro|PCI64_ATTR_VIRTUAL
mdefine_line|#define PCI64_ATTR_VIRTUAL              (1ull &lt;&lt; 57)
DECL|macro|PCI64_ATTR_BAR
mdefine_line|#define PCI64_ATTR_BAR                  (1ull &lt;&lt; 56)
DECL|macro|PCI64_ATTR_SWAP
mdefine_line|#define PCI64_ATTR_SWAP                 (1ull &lt;&lt; 55)
DECL|macro|PCI64_ATTR_VIRTUAL1
mdefine_line|#define PCI64_ATTR_VIRTUAL1             (1ull &lt;&lt; 54)
DECL|macro|PCI32_LOCAL_BASE
mdefine_line|#define PCI32_LOCAL_BASE                0
DECL|macro|PCI32_MAPPED_BASE
mdefine_line|#define PCI32_MAPPED_BASE               0x40000000
DECL|macro|PCI32_DIRECT_BASE
mdefine_line|#define PCI32_DIRECT_BASE               0x80000000
DECL|macro|IS_PCI32_MAPPED
mdefine_line|#define IS_PCI32_MAPPED(x)              ((uint64_t)(x) &lt; PCI32_DIRECT_BASE &amp;&amp; &bslash;&n;                                         (uint64_t)(x) &gt;= PCI32_MAPPED_BASE)
DECL|macro|IS_PCI32_DIRECT
mdefine_line|#define IS_PCI32_DIRECT(x)              ((uint64_t)(x) &gt;= PCI32_MAPPED_BASE)
multiline_comment|/*&n; * Bridge PMU Address Transaltion Entry Attibutes&n; */
DECL|macro|PCI32_ATE_V
mdefine_line|#define PCI32_ATE_V                     (0x1 &lt;&lt; 0)
DECL|macro|PCI32_ATE_CO
mdefine_line|#define PCI32_ATE_CO                    (0x1 &lt;&lt; 1)
DECL|macro|PCI32_ATE_PREC
mdefine_line|#define PCI32_ATE_PREC                  (0x1 &lt;&lt; 2)
DECL|macro|PCI32_ATE_PREF
mdefine_line|#define PCI32_ATE_PREF                  (0x1 &lt;&lt; 3)
DECL|macro|PCI32_ATE_BAR
mdefine_line|#define PCI32_ATE_BAR                   (0x1 &lt;&lt; 4)
DECL|macro|PCI32_ATE_ADDR_SHFT
mdefine_line|#define PCI32_ATE_ADDR_SHFT             12
DECL|macro|MINIMAL_ATES_REQUIRED
mdefine_line|#define MINIMAL_ATES_REQUIRED(addr, size) &bslash;&n;&t;(IOPG(IOPGOFF(addr) + (size) - 1) == IOPG((size) - 1))
DECL|macro|MINIMAL_ATE_FLAG
mdefine_line|#define MINIMAL_ATE_FLAG(addr, size) &bslash;&n;&t;(MINIMAL_ATES_REQUIRED((uint64_t)addr, size) ? 1 : 0)
multiline_comment|/* bit 29 of the pci address is the SWAP bit */
DECL|macro|ATE_SWAPSHIFT
mdefine_line|#define ATE_SWAPSHIFT                   29
DECL|macro|ATE_SWAP_ON
mdefine_line|#define ATE_SWAP_ON(x)                  ((x) |= (1 &lt;&lt; ATE_SWAPSHIFT))
DECL|macro|ATE_SWAP_OFF
mdefine_line|#define ATE_SWAP_OFF(x)                 ((x) &amp;= ~(1 &lt;&lt; ATE_SWAPSHIFT))
multiline_comment|/*&n; * I/O page size&n; */
macro_line|#if PAGE_SIZE &lt; 16384
DECL|macro|IOPFNSHIFT
mdefine_line|#define IOPFNSHIFT                      12      /* 4K per mapped page */
macro_line|#else
DECL|macro|IOPFNSHIFT
mdefine_line|#define IOPFNSHIFT                      14      /* 16K per mapped page */
macro_line|#endif
DECL|macro|IOPGSIZE
mdefine_line|#define IOPGSIZE                        (1 &lt;&lt; IOPFNSHIFT)
DECL|macro|IOPG
mdefine_line|#define IOPG(x)                         ((x) &gt;&gt; IOPFNSHIFT)
DECL|macro|IOPGOFF
mdefine_line|#define IOPGOFF(x)                      ((x) &amp; (IOPGSIZE-1))
DECL|macro|PCIBR_DEV_SWAP_DIR
mdefine_line|#define PCIBR_DEV_SWAP_DIR              (1ull &lt;&lt; 19)
DECL|macro|PCIBR_CTRL_PAGE_SIZE
mdefine_line|#define PCIBR_CTRL_PAGE_SIZE            (0x1 &lt;&lt; 21)
multiline_comment|/*&n; * PMU resources.&n; */
DECL|struct|ate_resource
r_struct
id|ate_resource
(brace
DECL|member|ate
r_uint64
op_star
id|ate
suffix:semicolon
DECL|member|num_ate
r_uint64
id|num_ate
suffix:semicolon
DECL|member|lowest_free_index
r_uint64
id|lowest_free_index
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pcibus_info
r_struct
id|pcibus_info
(brace
DECL|member|pbi_buscommon
r_struct
id|pcibus_bussoft
id|pbi_buscommon
suffix:semicolon
multiline_comment|/* common header */
DECL|member|pbi_moduleid
r_uint32
id|pbi_moduleid
suffix:semicolon
DECL|member|pbi_bridge_type
r_int
id|pbi_bridge_type
suffix:semicolon
DECL|member|pbi_bridge_mode
r_int
id|pbi_bridge_mode
suffix:semicolon
DECL|member|pbi_int_ate_resource
r_struct
id|ate_resource
id|pbi_int_ate_resource
suffix:semicolon
DECL|member|pbi_int_ate_size
r_uint64
id|pbi_int_ate_size
suffix:semicolon
DECL|member|pbi_dir_xbase
r_uint64
id|pbi_dir_xbase
suffix:semicolon
DECL|member|pbi_hub_xid
r_char
id|pbi_hub_xid
suffix:semicolon
DECL|member|pbi_devreg
r_uint64
id|pbi_devreg
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|pbi_lock
id|spinlock_t
id|pbi_lock
suffix:semicolon
DECL|member|pbi_valid_devices
r_uint32
id|pbi_valid_devices
suffix:semicolon
DECL|member|pbi_enabled_devices
r_uint32
id|pbi_enabled_devices
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * pcibus_info structure locking macros&n; */
r_inline
r_static
r_int
r_int
DECL|function|pcibr_lock
id|pcibr_lock
c_func
(paren
r_struct
id|pcibus_info
op_star
id|pcibus_info
)paren
(brace
r_int
r_int
id|flag
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pcibus_info-&gt;pbi_lock
comma
id|flag
)paren
suffix:semicolon
r_return
id|flag
suffix:semicolon
)brace
DECL|macro|pcibr_unlock
mdefine_line|#define pcibr_unlock(pcibus_info, flag)  spin_unlock_irqrestore(&amp;pcibus_info-&gt;pbi_lock, flag)
r_extern
r_void
op_star
id|pcibr_bus_fixup
c_func
(paren
r_struct
id|pcibus_bussoft
op_star
)paren
suffix:semicolon
r_extern
r_uint64
id|pcibr_dma_map
c_func
(paren
r_struct
id|pcidev_info
op_star
comma
r_int
r_int
comma
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|pcibr_dma_unmap
c_func
(paren
r_struct
id|pcidev_info
op_star
comma
id|dma_addr_t
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * prototypes for the bridge asic register access routines in pcibr_reg.c&n; */
r_extern
r_void
id|pcireg_control_bit_clr
c_func
(paren
r_struct
id|pcibus_info
op_star
comma
r_uint64
)paren
suffix:semicolon
r_extern
r_void
id|pcireg_control_bit_set
c_func
(paren
r_struct
id|pcibus_info
op_star
comma
r_uint64
)paren
suffix:semicolon
r_extern
r_uint64
id|pcireg_tflush_get
c_func
(paren
r_struct
id|pcibus_info
op_star
)paren
suffix:semicolon
r_extern
r_uint64
id|pcireg_intr_status_get
c_func
(paren
r_struct
id|pcibus_info
op_star
)paren
suffix:semicolon
r_extern
r_void
id|pcireg_intr_enable_bit_clr
c_func
(paren
r_struct
id|pcibus_info
op_star
comma
r_uint64
)paren
suffix:semicolon
r_extern
r_void
id|pcireg_intr_enable_bit_set
c_func
(paren
r_struct
id|pcibus_info
op_star
comma
r_uint64
)paren
suffix:semicolon
r_extern
r_void
id|pcireg_intr_addr_addr_set
c_func
(paren
r_struct
id|pcibus_info
op_star
comma
r_int
comma
r_uint64
)paren
suffix:semicolon
r_extern
r_void
id|pcireg_force_intr_set
c_func
(paren
r_struct
id|pcibus_info
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_uint64
id|pcireg_wrb_flush_get
c_func
(paren
r_struct
id|pcibus_info
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|pcireg_int_ate_set
c_func
(paren
r_struct
id|pcibus_info
op_star
comma
r_int
comma
r_uint64
)paren
suffix:semicolon
r_extern
r_uint64
op_star
id|pcireg_int_ate_addr
c_func
(paren
r_struct
id|pcibus_info
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|pcibr_force_interrupt
c_func
(paren
r_struct
id|sn_irq_info
op_star
id|sn_irq_info
)paren
suffix:semicolon
r_extern
r_void
id|pcibr_change_devices_irq
c_func
(paren
r_struct
id|sn_irq_info
op_star
id|sn_irq_info
)paren
suffix:semicolon
r_extern
r_int
id|pcibr_ate_alloc
c_func
(paren
r_struct
id|pcibus_info
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|pcibr_ate_free
c_func
(paren
r_struct
id|pcibus_info
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ate_write
c_func
(paren
r_struct
id|pcibus_info
op_star
comma
r_int
comma
r_int
comma
r_uint64
)paren
suffix:semicolon
macro_line|#endif
eof
