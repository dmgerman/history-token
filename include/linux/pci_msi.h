multiline_comment|/*&n; *&t;../include/linux/pci_msi.h&n; *&n; */
macro_line|#ifndef _ASM_PCI_MSI_H
DECL|macro|_ASM_PCI_MSI_H
mdefine_line|#define _ASM_PCI_MSI_H
macro_line|#include &lt;linux/pci.h&gt;
DECL|macro|MSI_AUTO
mdefine_line|#define MSI_AUTO -1
DECL|macro|NR_REPEATS
mdefine_line|#define NR_REPEATS&t;23
DECL|macro|NR_RESERVED_VECTORS
mdefine_line|#define NR_RESERVED_VECTORS 3 /*FIRST_DEVICE_VECTOR,FIRST_SYSTEM_VECTOR,0x80 */
multiline_comment|/*&n; * Assume the maximum number of hot plug slots supported by the system is about&n; * ten. The worstcase is that each of these slots is hot-added with a device,&n; * which has two MSI/MSI-X capable functions. To avoid any MSI-X driver, which&n; * attempts to request all available vectors, NR_HP_RESERVED_VECTORS is defined&n; * as below to ensure at least one message is assigned to each detected MSI/&n; * MSI-X device function.&n; */
DECL|macro|NR_HP_RESERVED_VECTORS
mdefine_line|#define NR_HP_RESERVED_VECTORS &t;20
r_extern
r_int
id|vector_irq
(braket
id|NR_IRQS
)braket
suffix:semicolon
r_extern
id|cpumask_t
id|pending_irq_balance_cpumask
(braket
id|NR_IRQS
)braket
suffix:semicolon
r_extern
r_void
(paren
op_star
id|interrupt
(braket
id|NR_IRQS
)braket
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|macro|set_msi_irq_affinity
mdefine_line|#define set_msi_irq_affinity&t;set_msi_affinity
macro_line|#else
DECL|macro|set_msi_irq_affinity
mdefine_line|#define set_msi_irq_affinity&t;NULL
DECL|function|move_msi
r_static
r_inline
r_void
id|move_msi
c_func
(paren
r_int
id|vector
)paren
(brace
)brace
macro_line|#endif
macro_line|#ifndef CONFIG_X86_IO_APIC
DECL|function|get_ioapic_vector
r_static
r_inline
r_int
id|get_ioapic_vector
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|restore_ioapic_irq_handler
r_static
r_inline
r_void
id|restore_ioapic_irq_handler
c_func
(paren
r_int
id|irq
)paren
(brace
)brace
macro_line|#else
r_extern
r_void
id|restore_ioapic_irq_handler
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * MSI-X Address Register&n; */
DECL|macro|PCI_MSIX_FLAGS_QSIZE
mdefine_line|#define PCI_MSIX_FLAGS_QSIZE&t;&t;0x7FF
DECL|macro|PCI_MSIX_FLAGS_ENABLE
mdefine_line|#define PCI_MSIX_FLAGS_ENABLE&t;&t;(1 &lt;&lt; 15)
DECL|macro|PCI_MSIX_FLAGS_BIRMASK
mdefine_line|#define PCI_MSIX_FLAGS_BIRMASK&t;&t;(7 &lt;&lt; 0)
DECL|macro|PCI_MSIX_FLAGS_BITMASK
mdefine_line|#define PCI_MSIX_FLAGS_BITMASK&t;&t;(1 &lt;&lt; 0)
DECL|macro|PCI_MSIX_ENTRY_LOWER_ADDR_OFFSET
mdefine_line|#define PCI_MSIX_ENTRY_LOWER_ADDR_OFFSET&t;0
DECL|macro|PCI_MSIX_ENTRY_UPPER_ADDR_OFFSET
mdefine_line|#define PCI_MSIX_ENTRY_UPPER_ADDR_OFFSET&t;4
DECL|macro|PCI_MSIX_ENTRY_DATA_OFFSET
mdefine_line|#define PCI_MSIX_ENTRY_DATA_OFFSET&t;&t;8
DECL|macro|PCI_MSIX_ENTRY_VECTOR_CTRL_OFFSET
mdefine_line|#define PCI_MSIX_ENTRY_VECTOR_CTRL_OFFSET&t;12
DECL|macro|PCI_MSIX_ENTRY_SIZE
mdefine_line|#define PCI_MSIX_ENTRY_SIZE&t;&t;&t;16
DECL|macro|msi_control_reg
mdefine_line|#define msi_control_reg(base)&t;&t;(base + PCI_MSI_FLAGS)
DECL|macro|msi_lower_address_reg
mdefine_line|#define msi_lower_address_reg(base)&t;(base + PCI_MSI_ADDRESS_LO)
DECL|macro|msi_upper_address_reg
mdefine_line|#define msi_upper_address_reg(base)&t;(base + PCI_MSI_ADDRESS_HI)
DECL|macro|msi_data_reg
mdefine_line|#define msi_data_reg(base, is64bit)&t;&bslash;&n;&t;( (is64bit == 1) ? base+PCI_MSI_DATA_64 : base+PCI_MSI_DATA_32 )
DECL|macro|msi_mask_bits_reg
mdefine_line|#define msi_mask_bits_reg(base, is64bit) &bslash;&n;&t;( (is64bit == 1) ? base+PCI_MSI_MASK_BIT : base+PCI_MSI_MASK_BIT-4)
DECL|macro|msi_disable
mdefine_line|#define msi_disable(control)&t;&t;control &amp;= ~PCI_MSI_FLAGS_ENABLE
DECL|macro|multi_msi_capable
mdefine_line|#define multi_msi_capable(control) &bslash;&n;&t;(1 &lt;&lt; ((control &amp; PCI_MSI_FLAGS_QMASK) &gt;&gt; 1))
DECL|macro|multi_msi_enable
mdefine_line|#define multi_msi_enable(control, num) &bslash;&n;&t;control |= (((num &gt;&gt; 1) &lt;&lt; 4) &amp; PCI_MSI_FLAGS_QSIZE);
DECL|macro|is_64bit_address
mdefine_line|#define is_64bit_address(control)&t;(control &amp; PCI_MSI_FLAGS_64BIT)
DECL|macro|is_mask_bit_support
mdefine_line|#define is_mask_bit_support(control)&t;(control &amp; PCI_MSI_FLAGS_MASKBIT)
DECL|macro|msi_enable
mdefine_line|#define msi_enable(control, num) multi_msi_enable(control, num); &bslash;&n;&t;control |= PCI_MSI_FLAGS_ENABLE
DECL|macro|msix_control_reg
mdefine_line|#define msix_control_reg&t;&t;msi_control_reg
DECL|macro|msix_table_offset_reg
mdefine_line|#define msix_table_offset_reg(base)&t;(base + 0x04)
DECL|macro|msix_pba_offset_reg
mdefine_line|#define msix_pba_offset_reg(base)&t;(base + 0x08)
DECL|macro|msix_enable
mdefine_line|#define msix_enable(control)&t; &t;control |= PCI_MSIX_FLAGS_ENABLE
DECL|macro|msix_disable
mdefine_line|#define msix_disable(control)&t; &t;control &amp;= ~PCI_MSIX_FLAGS_ENABLE
DECL|macro|msix_table_size
mdefine_line|#define msix_table_size(control) &t;((control &amp; PCI_MSIX_FLAGS_QSIZE)+1)
DECL|macro|multi_msix_capable
mdefine_line|#define multi_msix_capable&t;&t;msix_table_size
DECL|macro|msix_unmask
mdefine_line|#define msix_unmask(address)&t; &t;(address &amp; ~PCI_MSIX_FLAGS_BITMASK)
DECL|macro|msix_mask
mdefine_line|#define msix_mask(address)&t;&t;(address | PCI_MSIX_FLAGS_BITMASK)
DECL|macro|msix_is_pending
mdefine_line|#define msix_is_pending(address) &t;(address &amp; PCI_MSIX_FLAGS_PENDMASK)
r_extern
r_char
id|__dbg_str_buf
(braket
l_int|256
)braket
suffix:semicolon
DECL|macro|_DEFINE_DBG_BUFFER
mdefine_line|#define _DEFINE_DBG_BUFFER&t;char __dbg_str_buf[256];
DECL|macro|_DBG_K_TRACE_ENTRY
mdefine_line|#define _DBG_K_TRACE_ENTRY&t;((unsigned int)0x00000001)
DECL|macro|_DBG_K_TRACE_EXIT
mdefine_line|#define _DBG_K_TRACE_EXIT&t;((unsigned int)0x00000002)
DECL|macro|_DBG_K_INFO
mdefine_line|#define _DBG_K_INFO&t;&t;((unsigned int)0x00000004)
DECL|macro|_DBG_K_ERROR
mdefine_line|#define _DBG_K_ERROR&t;&t;((unsigned int)0x00000008)
DECL|macro|_DBG_K_TRACE
mdefine_line|#define _DBG_K_TRACE&t;(_DBG_K_TRACE_ENTRY | _DBG_K_TRACE_EXIT)
DECL|macro|_DEBUG_LEVEL
mdefine_line|#define _DEBUG_LEVEL&t;(_DBG_K_INFO | _DBG_K_ERROR | _DBG_K_TRACE)
DECL|macro|_DBG_PRINT
mdefine_line|#define _DBG_PRINT( dbg_flags, args... )&t;&t;&bslash;&n;if ( _DEBUG_LEVEL &amp; (dbg_flags) )&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int len;&t;&t;&t;&t;&t;&bslash;&n;&t;len = sprintf(__dbg_str_buf, &quot;%s:%d: %s &quot;, &t;&bslash;&n;&t;&t;__FILE__, __LINE__, __FUNCTION__ ); &t;&bslash;&n;&t;sprintf(__dbg_str_buf + len, args);&t;&t;&bslash;&n;&t;printk(KERN_INFO &quot;%s&bslash;n&quot;, __dbg_str_buf);&t;&bslash;&n;}
DECL|macro|MSI_FUNCTION_TRACE_ENTER
mdefine_line|#define MSI_FUNCTION_TRACE_ENTER&t;&bslash;&n;&t;_DBG_PRINT (_DBG_K_TRACE_ENTRY, &quot;%s&quot;, &quot;[Entry]&quot;);
DECL|macro|MSI_FUNCTION_TRACE_EXIT
mdefine_line|#define MSI_FUNCTION_TRACE_EXIT&t;&t;&bslash;&n;&t;_DBG_PRINT (_DBG_K_TRACE_EXIT, &quot;%s&quot;, &quot;[Entry]&quot;);
multiline_comment|/*&n; * MSI Defined Data Structures&n; */
DECL|macro|MSI_ADDRESS_HEADER
mdefine_line|#define MSI_ADDRESS_HEADER&t;&t;0xfee
DECL|macro|MSI_ADDRESS_HEADER_SHIFT
mdefine_line|#define MSI_ADDRESS_HEADER_SHIFT&t;12
DECL|macro|MSI_ADDRESS_HEADER_MASK
mdefine_line|#define MSI_ADDRESS_HEADER_MASK&t;&t;0xfff000
DECL|macro|MSI_TARGET_CPU_SHIFT
mdefine_line|#define MSI_TARGET_CPU_SHIFT&t;&t;4
DECL|macro|MSI_TARGET_CPU_MASK
mdefine_line|#define MSI_TARGET_CPU_MASK&t;&t;0xff
DECL|macro|MSI_DELIVERY_MODE
mdefine_line|#define MSI_DELIVERY_MODE&t;&t;0
DECL|macro|MSI_LEVEL_MODE
mdefine_line|#define MSI_LEVEL_MODE&t;&t;&t;1&t;/* Edge always assert */
DECL|macro|MSI_TRIGGER_MODE
mdefine_line|#define MSI_TRIGGER_MODE&t;&t;0&t;/* MSI is edge sensitive */
DECL|macro|MSI_LOGICAL_MODE
mdefine_line|#define MSI_LOGICAL_MODE&t;&t;1
DECL|macro|MSI_REDIRECTION_HINT_MODE
mdefine_line|#define MSI_REDIRECTION_HINT_MODE&t;0
macro_line|#ifdef CONFIG_SMP
DECL|macro|MSI_TARGET_CPU
mdefine_line|#define MSI_TARGET_CPU&t;&t;&t;logical_smp_processor_id()
macro_line|#else
DECL|macro|MSI_TARGET_CPU
mdefine_line|#define MSI_TARGET_CPU&t;&t;&t;TARGET_CPUS
macro_line|#endif
DECL|struct|msg_data
r_struct
id|msg_data
(brace
macro_line|#if defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|vector
id|__u32
id|vector
suffix:colon
l_int|8
suffix:semicolon
DECL|member|delivery_mode
id|__u32
id|delivery_mode
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* 000b: FIXED | 001b: lowest prior */
DECL|member|reserved_1
id|__u32
id|reserved_1
suffix:colon
l_int|3
suffix:semicolon
DECL|member|level
id|__u32
id|level
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 0: deassert | 1: assert */
DECL|member|trigger
id|__u32
id|trigger
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 0: edge | 1: level */
DECL|member|reserved_2
id|__u32
id|reserved_2
suffix:colon
l_int|16
suffix:semicolon
macro_line|#elif defined(__BIG_ENDIAN_BITFIELD)
id|__u32
id|reserved_2
suffix:colon
l_int|16
suffix:semicolon
id|__u32
id|trigger
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 0: edge | 1: level */
id|__u32
id|level
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 0: deassert | 1: assert */
id|__u32
id|reserved_1
suffix:colon
l_int|3
suffix:semicolon
id|__u32
id|delivery_mode
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* 000b: FIXED | 001b: lowest prior */
id|__u32
id|vector
suffix:colon
l_int|8
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Bitfield endianness not defined! Check your byteorder.h&quot;
macro_line|#endif
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|msg_address
r_struct
id|msg_address
(brace
r_union
(brace
r_struct
(brace
macro_line|#if defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|reserved_1
id|__u32
id|reserved_1
suffix:colon
l_int|2
suffix:semicolon
DECL|member|dest_mode
id|__u32
id|dest_mode
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*0:physic | 1:logic */
DECL|member|redirection_hint
id|__u32
id|redirection_hint
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*0: dedicated CPU&n;&t;&t;&t;&t;&t;&t;&t;  1: lowest priority */
DECL|member|reserved_2
id|__u32
id|reserved_2
suffix:colon
l_int|4
suffix:semicolon
DECL|member|dest_id
id|__u32
id|dest_id
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* Destination ID */
macro_line|#elif defined(__BIG_ENDIAN_BITFIELD)
id|__u32
id|dest_id
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* Destination ID */
id|__u32
id|reserved_2
suffix:colon
l_int|4
suffix:semicolon
id|__u32
id|redirection_hint
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*0: dedicated CPU&n;&t;&t;&t;&t;&t;&t;&t;  1: lowest priority */
id|__u32
id|dest_mode
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*0:physic | 1:logic */
id|__u32
id|reserved_1
suffix:colon
l_int|2
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Bitfield endianness not defined! Check your byteorder.h&quot;
macro_line|#endif
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|value
id|__u32
id|value
suffix:semicolon
DECL|member|lo_address
)brace
id|lo_address
suffix:semicolon
DECL|member|hi_address
id|__u32
id|hi_address
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|msi_desc
r_struct
id|msi_desc
(brace
r_struct
(brace
DECL|member|type
id|__u8
id|type
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* {0: unused, 5h:MSI, 11h:MSI-X} */
DECL|member|maskbit
id|__u8
id|maskbit
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* mask-pending bit supported ?   */
DECL|member|reserved
id|__u8
id|reserved
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* reserved&t;&t;&t;  */
DECL|member|entry_nr
id|__u8
id|entry_nr
suffix:semicolon
multiline_comment|/* specific enabled entry &t;  */
DECL|member|default_vector
id|__u8
id|default_vector
suffix:semicolon
multiline_comment|/* default pre-assigned vector    */
DECL|member|current_cpu
id|__u8
id|current_cpu
suffix:semicolon
multiline_comment|/* current destination cpu&t;  */
DECL|member|msi_attrib
)brace
id|msi_attrib
suffix:semicolon
r_struct
(brace
DECL|member|head
id|__u16
id|head
suffix:semicolon
DECL|member|tail
id|__u16
id|tail
suffix:semicolon
DECL|member|link
)brace
id|link
suffix:semicolon
DECL|member|mask_base
r_int
r_int
id|mask_base
suffix:semicolon
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _ASM_PCI_MSI_H */
eof
