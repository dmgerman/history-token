multiline_comment|/* &n;   Common Flash Interface probe code.&n;   (C) 2000 Red Hat. GPL&squot;d.&n;   $Id: cfi_probe.c,v 1.77 2004/07/14 08:38:44 dwmw2 Exp $&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/cfi.h&gt;
macro_line|#include &lt;linux/mtd/gen_probe.h&gt;
singleline_comment|//#define DEBUG_CFI 
macro_line|#ifdef DEBUG_CFI
r_static
r_void
id|print_cfi_ident
c_func
(paren
r_struct
id|cfi_ident
op_star
)paren
suffix:semicolon
macro_line|#endif
r_static
r_int
id|cfi_probe_chip
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|__u32
id|base
comma
r_int
r_int
op_star
id|chip_map
comma
r_struct
id|cfi_private
op_star
id|cfi
)paren
suffix:semicolon
r_static
r_int
id|cfi_chip_setup
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_struct
id|cfi_private
op_star
id|cfi
)paren
suffix:semicolon
r_struct
id|mtd_info
op_star
id|cfi_probe
c_func
(paren
r_struct
id|map_info
op_star
id|map
)paren
suffix:semicolon
multiline_comment|/* check for QRY.&n;   in: interleave,type,mode&n;   ret: table index, &lt;0 for error&n; */
DECL|function|qry_present
r_static
r_int
id|qry_present
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|__u32
id|base
comma
r_struct
id|cfi_private
op_star
id|cfi
)paren
(brace
r_int
id|osf
op_assign
id|cfi-&gt;interleave
op_star
id|cfi-&gt;device_type
suffix:semicolon
singleline_comment|// scale factor
id|map_word
id|val
suffix:semicolon
id|map_word
id|qry
suffix:semicolon
id|qry
op_assign
id|cfi_build_cmd
c_func
(paren
l_char|&squot;Q&squot;
comma
id|map
comma
id|cfi
)paren
suffix:semicolon
id|val
op_assign
id|map_read
c_func
(paren
id|map
comma
id|base
op_plus
id|osf
op_star
l_int|0x10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|map_word_equal
c_func
(paren
id|map
comma
id|qry
comma
id|val
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|qry
op_assign
id|cfi_build_cmd
c_func
(paren
l_char|&squot;R&squot;
comma
id|map
comma
id|cfi
)paren
suffix:semicolon
id|val
op_assign
id|map_read
c_func
(paren
id|map
comma
id|base
op_plus
id|osf
op_star
l_int|0x11
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|map_word_equal
c_func
(paren
id|map
comma
id|qry
comma
id|val
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|qry
op_assign
id|cfi_build_cmd
c_func
(paren
l_char|&squot;Y&squot;
comma
id|map
comma
id|cfi
)paren
suffix:semicolon
id|val
op_assign
id|map_read
c_func
(paren
id|map
comma
id|base
op_plus
id|osf
op_star
l_int|0x12
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|map_word_equal
c_func
(paren
id|map
comma
id|qry
comma
id|val
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
singleline_comment|// nothing found
)brace
DECL|function|cfi_probe_chip
r_static
r_int
id|cfi_probe_chip
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|__u32
id|base
comma
r_int
r_int
op_star
id|chip_map
comma
r_struct
id|cfi_private
op_star
id|cfi
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|base
op_plus
l_int|0
)paren
op_ge
id|map-&gt;size
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Probe at base[0x00](0x%08lx) past the end of the map(0x%08lx)&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|base
comma
id|map-&gt;size
op_minus
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|base
op_plus
l_int|0xff
)paren
op_ge
id|map-&gt;size
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Probe at base[0x55](0x%08lx) past the end of the map(0x%08lx)&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|base
op_plus
l_int|0x55
comma
id|map-&gt;size
op_minus
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|cfi_send_gen_cmd
c_func
(paren
l_int|0xF0
comma
l_int|0
comma
id|base
comma
id|map
comma
id|cfi
comma
id|cfi-&gt;device_type
comma
l_int|NULL
)paren
suffix:semicolon
id|cfi_send_gen_cmd
c_func
(paren
l_int|0xFF
comma
l_int|0
comma
id|base
comma
id|map
comma
id|cfi
comma
id|cfi-&gt;device_type
comma
l_int|NULL
)paren
suffix:semicolon
id|cfi_send_gen_cmd
c_func
(paren
l_int|0x98
comma
l_int|0x55
comma
id|base
comma
id|map
comma
id|cfi
comma
id|cfi-&gt;device_type
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|qry_present
c_func
(paren
id|map
comma
id|base
comma
id|cfi
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cfi-&gt;numchips
)paren
(brace
multiline_comment|/* This is the first time we&squot;re called. Set up the CFI &n;&t;&t;   stuff accordingly and return */
r_return
id|cfi_chip_setup
c_func
(paren
id|map
comma
id|cfi
)paren
suffix:semicolon
)brace
multiline_comment|/* Check each previous chip to see if it&squot;s an alias */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
id|base
op_rshift
id|cfi-&gt;chipshift
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|start
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|i
comma
id|chip_map
)paren
)paren
(brace
multiline_comment|/* Skip location; no valid chip at this address */
r_continue
suffix:semicolon
)brace
id|start
op_assign
id|i
op_lshift
id|cfi-&gt;chipshift
suffix:semicolon
multiline_comment|/* This chip should be in read mode if it&squot;s one&n;&t;&t;   we&squot;ve already touched. */
r_if
c_cond
(paren
id|qry_present
c_func
(paren
id|map
comma
id|start
comma
id|cfi
)paren
)paren
(brace
multiline_comment|/* Eep. This chip also had the QRY marker. &n;&t;&t;&t; * Is it an alias for the new one? */
id|cfi_send_gen_cmd
c_func
(paren
l_int|0xF0
comma
l_int|0
comma
id|start
comma
id|map
comma
id|cfi
comma
id|cfi-&gt;device_type
comma
l_int|NULL
)paren
suffix:semicolon
id|cfi_send_gen_cmd
c_func
(paren
l_int|0xFF
comma
l_int|0
comma
id|start
comma
id|map
comma
id|cfi
comma
id|cfi-&gt;device_type
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* If the QRY marker goes away, it&squot;s an alias */
r_if
c_cond
(paren
op_logical_neg
id|qry_present
c_func
(paren
id|map
comma
id|start
comma
id|cfi
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: Found an alias at 0x%x for the chip at 0x%lx&bslash;n&quot;
comma
id|map-&gt;name
comma
id|base
comma
id|start
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Yes, it&squot;s actually got QRY for data. Most &n;&t;&t;&t; * unfortunate. Stick the new chip in read mode&n;&t;&t;&t; * too and if it&squot;s the same, assume it&squot;s an alias. */
multiline_comment|/* FIXME: Use other modes to do a proper check */
id|cfi_send_gen_cmd
c_func
(paren
l_int|0xF0
comma
l_int|0
comma
id|base
comma
id|map
comma
id|cfi
comma
id|cfi-&gt;device_type
comma
l_int|NULL
)paren
suffix:semicolon
id|cfi_send_gen_cmd
c_func
(paren
l_int|0xFF
comma
l_int|0
comma
id|start
comma
id|map
comma
id|cfi
comma
id|cfi-&gt;device_type
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qry_present
c_func
(paren
id|map
comma
id|base
comma
id|cfi
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: Found an alias at 0x%x for the chip at 0x%lx&bslash;n&quot;
comma
id|map-&gt;name
comma
id|base
comma
id|start
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* OK, if we got to here, then none of the previous chips appear to&n;&t;   be aliases for the current one. */
id|set_bit
c_func
(paren
(paren
id|base
op_rshift
id|cfi-&gt;chipshift
)paren
comma
id|chip_map
)paren
suffix:semicolon
multiline_comment|/* Update chip map */
id|cfi-&gt;numchips
op_increment
suffix:semicolon
multiline_comment|/* Put it back into Read Mode */
id|cfi_send_gen_cmd
c_func
(paren
l_int|0xF0
comma
l_int|0
comma
id|base
comma
id|map
comma
id|cfi
comma
id|cfi-&gt;device_type
comma
l_int|NULL
)paren
suffix:semicolon
id|cfi_send_gen_cmd
c_func
(paren
l_int|0xFF
comma
l_int|0
comma
id|base
comma
id|map
comma
id|cfi
comma
id|cfi-&gt;device_type
comma
l_int|NULL
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Found %d x%d devices at 0x%x in %d-bit bank&bslash;n&quot;
comma
id|map-&gt;name
comma
id|cfi-&gt;interleave
comma
id|cfi-&gt;device_type
op_star
l_int|8
comma
id|base
comma
id|map-&gt;bankwidth
op_star
l_int|8
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|cfi_chip_setup
r_static
r_int
id|cfi_chip_setup
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_struct
id|cfi_private
op_star
id|cfi
)paren
(brace
r_int
id|ofs_factor
op_assign
id|cfi-&gt;interleave
op_star
id|cfi-&gt;device_type
suffix:semicolon
id|__u32
id|base
op_assign
l_int|0
suffix:semicolon
r_int
id|num_erase_regions
op_assign
id|cfi_read_query
c_func
(paren
id|map
comma
id|base
op_plus
(paren
l_int|0x10
op_plus
l_int|28
)paren
op_star
id|ofs_factor
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
macro_line|#ifdef DEBUG_CFI
id|printk
c_func
(paren
l_string|&quot;Number of erase regions: %d&bslash;n&quot;
comma
id|num_erase_regions
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|num_erase_regions
)paren
r_return
l_int|0
suffix:semicolon
id|cfi-&gt;cfiq
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|cfi_ident
)paren
op_plus
id|num_erase_regions
op_star
l_int|4
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cfi-&gt;cfiq
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: kmalloc failed for CFI ident structure&bslash;n&quot;
comma
id|map-&gt;name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|memset
c_func
(paren
id|cfi-&gt;cfiq
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|cfi_ident
)paren
)paren
suffix:semicolon
id|cfi-&gt;cfi_mode
op_assign
id|CFI_MODE_CFI
suffix:semicolon
multiline_comment|/* Read the CFI info structure */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
r_sizeof
(paren
r_struct
id|cfi_ident
)paren
op_plus
id|num_erase_regions
op_star
l_int|4
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
(paren
(paren
r_int
r_char
op_star
)paren
id|cfi-&gt;cfiq
)paren
(braket
id|i
)braket
op_assign
id|cfi_read_query
c_func
(paren
id|map
comma
id|base
op_plus
(paren
l_int|0x10
op_plus
id|i
)paren
op_star
id|ofs_factor
)paren
suffix:semicolon
)brace
multiline_comment|/* Do any necessary byteswapping */
id|cfi-&gt;cfiq-&gt;P_ID
op_assign
id|le16_to_cpu
c_func
(paren
id|cfi-&gt;cfiq-&gt;P_ID
)paren
suffix:semicolon
id|cfi-&gt;cfiq-&gt;P_ADR
op_assign
id|le16_to_cpu
c_func
(paren
id|cfi-&gt;cfiq-&gt;P_ADR
)paren
suffix:semicolon
id|cfi-&gt;cfiq-&gt;A_ID
op_assign
id|le16_to_cpu
c_func
(paren
id|cfi-&gt;cfiq-&gt;A_ID
)paren
suffix:semicolon
id|cfi-&gt;cfiq-&gt;A_ADR
op_assign
id|le16_to_cpu
c_func
(paren
id|cfi-&gt;cfiq-&gt;A_ADR
)paren
suffix:semicolon
id|cfi-&gt;cfiq-&gt;InterfaceDesc
op_assign
id|le16_to_cpu
c_func
(paren
id|cfi-&gt;cfiq-&gt;InterfaceDesc
)paren
suffix:semicolon
id|cfi-&gt;cfiq-&gt;MaxBufWriteSize
op_assign
id|le16_to_cpu
c_func
(paren
id|cfi-&gt;cfiq-&gt;MaxBufWriteSize
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_CFI
multiline_comment|/* Dump the information therein */
id|print_cfi_ident
c_func
(paren
id|cfi-&gt;cfiq
)paren
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|cfi-&gt;cfiq-&gt;NumEraseRegions
suffix:semicolon
id|i
op_increment
)paren
(brace
id|cfi-&gt;cfiq-&gt;EraseRegionInfo
(braket
id|i
)braket
op_assign
id|le32_to_cpu
c_func
(paren
id|cfi-&gt;cfiq-&gt;EraseRegionInfo
(braket
id|i
)braket
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_CFI&t;&t;
id|printk
c_func
(paren
l_string|&quot;  Erase Region #%d: BlockSize 0x%4.4X bytes, %d blocks&bslash;n&quot;
comma
id|i
comma
(paren
id|cfi-&gt;cfiq-&gt;EraseRegionInfo
(braket
id|i
)braket
op_rshift
l_int|8
)paren
op_amp
op_complement
l_int|0xff
comma
(paren
id|cfi-&gt;cfiq-&gt;EraseRegionInfo
(braket
id|i
)braket
op_amp
l_int|0xffff
)paren
op_plus
l_int|1
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* Note we put the device back into Read Mode BEFORE going into Auto&n;&t; * Select Mode, as some devices support nesting of modes, others&n;&t; * don&squot;t. This way should always work.&n;&t; * On cmdset 0001 the writes of 0xaa and 0x55 are not needed, and&n;&t; * so should be treated as nops or illegal (and so put the device&n;&t; * back into Read Mode, which is a nop in this case).&n;&t; */
id|cfi_send_gen_cmd
c_func
(paren
l_int|0xf0
comma
l_int|0
comma
id|base
comma
id|map
comma
id|cfi
comma
id|cfi-&gt;device_type
comma
l_int|NULL
)paren
suffix:semicolon
id|cfi_send_gen_cmd
c_func
(paren
l_int|0xaa
comma
l_int|0x555
comma
id|base
comma
id|map
comma
id|cfi
comma
id|cfi-&gt;device_type
comma
l_int|NULL
)paren
suffix:semicolon
id|cfi_send_gen_cmd
c_func
(paren
l_int|0x55
comma
l_int|0x2aa
comma
id|base
comma
id|map
comma
id|cfi
comma
id|cfi-&gt;device_type
comma
l_int|NULL
)paren
suffix:semicolon
id|cfi_send_gen_cmd
c_func
(paren
l_int|0x90
comma
l_int|0x555
comma
id|base
comma
id|map
comma
id|cfi
comma
id|cfi-&gt;device_type
comma
l_int|NULL
)paren
suffix:semicolon
id|cfi-&gt;mfr
op_assign
id|cfi_read_query
c_func
(paren
id|map
comma
id|base
)paren
suffix:semicolon
id|cfi-&gt;id
op_assign
id|cfi_read_query
c_func
(paren
id|map
comma
id|base
op_plus
id|ofs_factor
)paren
suffix:semicolon
multiline_comment|/* Put it back into Read Mode */
id|cfi_send_gen_cmd
c_func
(paren
l_int|0xF0
comma
l_int|0
comma
id|base
comma
id|map
comma
id|cfi
comma
id|cfi-&gt;device_type
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* ... even if it&squot;s an Intel chip */
id|cfi_send_gen_cmd
c_func
(paren
l_int|0xFF
comma
l_int|0
comma
id|base
comma
id|map
comma
id|cfi
comma
id|cfi-&gt;device_type
comma
l_int|NULL
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Found %d x%d devices at 0x%x in %d-bit bank&bslash;n&quot;
comma
id|map-&gt;name
comma
id|cfi-&gt;interleave
comma
id|cfi-&gt;device_type
op_star
l_int|8
comma
id|base
comma
id|map-&gt;bankwidth
op_star
l_int|8
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_CFI
DECL|function|vendorname
r_static
r_char
op_star
id|vendorname
c_func
(paren
id|__u16
id|vendor
)paren
(brace
r_switch
c_cond
(paren
id|vendor
)paren
(brace
r_case
id|P_ID_NONE
suffix:colon
r_return
l_string|&quot;None&quot;
suffix:semicolon
r_case
id|P_ID_INTEL_EXT
suffix:colon
r_return
l_string|&quot;Intel/Sharp Extended&quot;
suffix:semicolon
r_case
id|P_ID_AMD_STD
suffix:colon
r_return
l_string|&quot;AMD/Fujitsu Standard&quot;
suffix:semicolon
r_case
id|P_ID_INTEL_STD
suffix:colon
r_return
l_string|&quot;Intel/Sharp Standard&quot;
suffix:semicolon
r_case
id|P_ID_AMD_EXT
suffix:colon
r_return
l_string|&quot;AMD/Fujitsu Extended&quot;
suffix:semicolon
r_case
id|P_ID_MITSUBISHI_STD
suffix:colon
r_return
l_string|&quot;Mitsubishi Standard&quot;
suffix:semicolon
r_case
id|P_ID_MITSUBISHI_EXT
suffix:colon
r_return
l_string|&quot;Mitsubishi Extended&quot;
suffix:semicolon
r_case
id|P_ID_RESERVED
suffix:colon
r_return
l_string|&quot;Not Allowed / Reserved for Future Use&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;Unknown&quot;
suffix:semicolon
)brace
)brace
DECL|function|print_cfi_ident
r_static
r_void
id|print_cfi_ident
c_func
(paren
r_struct
id|cfi_ident
op_star
id|cfip
)paren
(brace
macro_line|#if 0
r_if
c_cond
(paren
id|cfip-&gt;qry
(braket
l_int|0
)braket
op_ne
l_char|&squot;Q&squot;
op_logical_or
id|cfip-&gt;qry
(braket
l_int|1
)braket
op_ne
l_char|&squot;R&squot;
op_logical_or
id|cfip-&gt;qry
(braket
l_int|2
)braket
op_ne
l_char|&squot;Y&squot;
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Invalid CFI ident structure.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif&t;&t;
id|printk
c_func
(paren
l_string|&quot;Primary Vendor Command Set: %4.4X (%s)&bslash;n&quot;
comma
id|cfip-&gt;P_ID
comma
id|vendorname
c_func
(paren
id|cfip-&gt;P_ID
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cfip-&gt;P_ADR
)paren
id|printk
c_func
(paren
l_string|&quot;Primary Algorithm Table at %4.4X&bslash;n&quot;
comma
id|cfip-&gt;P_ADR
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;No Primary Algorithm Table&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Alternative Vendor Command Set: %4.4X (%s)&bslash;n&quot;
comma
id|cfip-&gt;A_ID
comma
id|vendorname
c_func
(paren
id|cfip-&gt;A_ID
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cfip-&gt;A_ADR
)paren
id|printk
c_func
(paren
l_string|&quot;Alternate Algorithm Table at %4.4X&bslash;n&quot;
comma
id|cfip-&gt;A_ADR
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;No Alternate Algorithm Table&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Vcc Minimum: %2d.%d V&bslash;n&quot;
comma
id|cfip-&gt;VccMin
op_rshift
l_int|4
comma
id|cfip-&gt;VccMin
op_amp
l_int|0xf
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Vcc Maximum: %2d.%d V&bslash;n&quot;
comma
id|cfip-&gt;VccMax
op_rshift
l_int|4
comma
id|cfip-&gt;VccMax
op_amp
l_int|0xf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cfip-&gt;VppMin
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Vpp Minimum: %2d.%d V&bslash;n&quot;
comma
id|cfip-&gt;VppMin
op_rshift
l_int|4
comma
id|cfip-&gt;VppMin
op_amp
l_int|0xf
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Vpp Maximum: %2d.%d V&bslash;n&quot;
comma
id|cfip-&gt;VppMax
op_rshift
l_int|4
comma
id|cfip-&gt;VppMax
op_amp
l_int|0xf
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;No Vpp line&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Typical byte/word write timeout: %d &#xfffd;s&bslash;n&quot;
comma
l_int|1
op_lshift
id|cfip-&gt;WordWriteTimeoutTyp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Maximum byte/word write timeout: %d &#xfffd;s&bslash;n&quot;
comma
(paren
l_int|1
op_lshift
id|cfip-&gt;WordWriteTimeoutMax
)paren
op_star
(paren
l_int|1
op_lshift
id|cfip-&gt;WordWriteTimeoutTyp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cfip-&gt;BufWriteTimeoutTyp
op_logical_or
id|cfip-&gt;BufWriteTimeoutMax
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Typical full buffer write timeout: %d &#xfffd;s&bslash;n&quot;
comma
l_int|1
op_lshift
id|cfip-&gt;BufWriteTimeoutTyp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Maximum full buffer write timeout: %d &#xfffd;s&bslash;n&quot;
comma
(paren
l_int|1
op_lshift
id|cfip-&gt;BufWriteTimeoutMax
)paren
op_star
(paren
l_int|1
op_lshift
id|cfip-&gt;BufWriteTimeoutTyp
)paren
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;Full buffer write not supported&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Typical block erase timeout: %d ms&bslash;n&quot;
comma
l_int|1
op_lshift
id|cfip-&gt;BlockEraseTimeoutTyp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Maximum block erase timeout: %d ms&bslash;n&quot;
comma
(paren
l_int|1
op_lshift
id|cfip-&gt;BlockEraseTimeoutMax
)paren
op_star
(paren
l_int|1
op_lshift
id|cfip-&gt;BlockEraseTimeoutTyp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cfip-&gt;ChipEraseTimeoutTyp
op_logical_or
id|cfip-&gt;ChipEraseTimeoutMax
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Typical chip erase timeout: %d ms&bslash;n&quot;
comma
l_int|1
op_lshift
id|cfip-&gt;ChipEraseTimeoutTyp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Maximum chip erase timeout: %d ms&bslash;n&quot;
comma
(paren
l_int|1
op_lshift
id|cfip-&gt;ChipEraseTimeoutMax
)paren
op_star
(paren
l_int|1
op_lshift
id|cfip-&gt;ChipEraseTimeoutTyp
)paren
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;Chip erase not supported&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Device size: 0x%X bytes (%d MiB)&bslash;n&quot;
comma
l_int|1
op_lshift
id|cfip-&gt;DevSize
comma
l_int|1
op_lshift
(paren
id|cfip-&gt;DevSize
op_minus
l_int|20
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Flash Device Interface description: 0x%4.4X&bslash;n&quot;
comma
id|cfip-&gt;InterfaceDesc
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cfip-&gt;InterfaceDesc
)paren
(brace
r_case
l_int|0
suffix:colon
id|printk
c_func
(paren
l_string|&quot;  - x8-only asynchronous interface&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|printk
c_func
(paren
l_string|&quot;  - x16-only asynchronous interface&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|printk
c_func
(paren
l_string|&quot;  - supports x8 and x16 via BYTE# with asynchronous interface&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|printk
c_func
(paren
l_string|&quot;  - x32-only asynchronous interface&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|65535
suffix:colon
id|printk
c_func
(paren
l_string|&quot;  - Not Allowed / Reserved&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;  - Unknown&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Max. bytes in buffer write: 0x%x&bslash;n&quot;
comma
l_int|1
op_lshift
id|cfip-&gt;MaxBufWriteSize
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Number of Erase Block Regions: %d&bslash;n&quot;
comma
id|cfip-&gt;NumEraseRegions
)paren
suffix:semicolon
)brace
macro_line|#endif /* DEBUG_CFI */
DECL|variable|cfi_chip_probe
r_static
r_struct
id|chip_probe
id|cfi_chip_probe
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;CFI&quot;
comma
dot
id|probe_chip
op_assign
id|cfi_probe_chip
)brace
suffix:semicolon
DECL|function|cfi_probe
r_struct
id|mtd_info
op_star
id|cfi_probe
c_func
(paren
r_struct
id|map_info
op_star
id|map
)paren
(brace
multiline_comment|/*&n;&t; * Just use the generic probe stuff to call our CFI-specific&n;&t; * chip_probe routine in all the possible permutations, etc.&n;&t; */
r_return
id|mtd_do_chip_probe
c_func
(paren
id|map
comma
op_amp
id|cfi_chip_probe
)paren
suffix:semicolon
)brace
DECL|variable|cfi_chipdrv
r_static
r_struct
id|mtd_chip_driver
id|cfi_chipdrv
op_assign
(brace
dot
id|probe
op_assign
id|cfi_probe
comma
dot
id|name
op_assign
l_string|&quot;cfi_probe&quot;
comma
dot
id|module
op_assign
id|THIS_MODULE
)brace
suffix:semicolon
DECL|function|cfi_probe_init
r_int
id|__init
id|cfi_probe_init
c_func
(paren
r_void
)paren
(brace
id|register_mtd_chip_driver
c_func
(paren
op_amp
id|cfi_chipdrv
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cfi_probe_exit
r_static
r_void
id|__exit
id|cfi_probe_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_mtd_chip_driver
c_func
(paren
op_amp
id|cfi_chipdrv
)paren
suffix:semicolon
)brace
DECL|variable|cfi_probe_init
id|module_init
c_func
(paren
id|cfi_probe_init
)paren
suffix:semicolon
DECL|variable|cfi_probe_exit
id|module_exit
c_func
(paren
id|cfi_probe_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;David Woodhouse &lt;dwmw2@infradead.org&gt; et al.&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Probe code for CFI-compliant flash chips&quot;
)paren
suffix:semicolon
eof
