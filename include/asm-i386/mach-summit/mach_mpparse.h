macro_line|#ifndef __ASM_MACH_MPPARSE_H
DECL|macro|__ASM_MACH_MPPARSE_H
mdefine_line|#define __ASM_MACH_MPPARSE_H
macro_line|#include &lt;mach_apic.h&gt;
r_extern
r_int
id|use_cyclone
suffix:semicolon
DECL|function|mpc_oem_bus_info
r_static
r_inline
r_void
id|mpc_oem_bus_info
c_func
(paren
r_struct
id|mpc_config_bus
op_star
id|m
comma
r_char
op_star
id|name
comma
r_struct
id|mpc_config_translation
op_star
id|translation
)paren
(brace
id|Dprintk
c_func
(paren
l_string|&quot;Bus #%d is %s&bslash;n&quot;
comma
id|m-&gt;mpc_busid
comma
id|name
)paren
suffix:semicolon
)brace
DECL|function|mpc_oem_pci_bus
r_static
r_inline
r_void
id|mpc_oem_pci_bus
c_func
(paren
r_struct
id|mpc_config_bus
op_star
id|m
comma
r_struct
id|mpc_config_translation
op_star
id|translation
)paren
(brace
)brace
DECL|function|mps_oem_check
r_static
r_inline
r_int
id|mps_oem_check
c_func
(paren
r_struct
id|mp_config_table
op_star
id|mpc
comma
r_char
op_star
id|oem
comma
r_char
op_star
id|productid
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|oem
comma
l_string|&quot;IBM ENSW&quot;
comma
l_int|8
)paren
op_logical_and
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|productid
comma
l_string|&quot;VIGIL SMP&quot;
comma
l_int|9
)paren
op_logical_or
op_logical_neg
id|strncmp
c_func
(paren
id|productid
comma
l_string|&quot;EXA&quot;
comma
l_int|3
)paren
op_logical_or
op_logical_neg
id|strncmp
c_func
(paren
id|productid
comma
l_string|&quot;RUTHLESS SMP&quot;
comma
l_int|12
)paren
)paren
)paren
(brace
id|use_cyclone
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*enable cyclone-timer*/
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Hook from generic ACPI tables.c */
DECL|function|acpi_madt_oem_check
r_static
r_inline
r_int
id|acpi_madt_oem_check
c_func
(paren
r_char
op_star
id|oem_id
comma
r_char
op_star
id|oem_table_id
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|oem_id
comma
l_string|&quot;IBM&quot;
comma
l_int|3
)paren
op_logical_and
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|oem_table_id
comma
l_string|&quot;SERVIGIL&quot;
comma
l_int|8
)paren
op_logical_or
op_logical_neg
id|strncmp
c_func
(paren
id|oem_table_id
comma
l_string|&quot;EXA&quot;
comma
l_int|3
)paren
)paren
)paren
(brace
id|use_cyclone
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*enable cyclone-timer*/
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|struct|rio_table_hdr
r_struct
id|rio_table_hdr
(brace
DECL|member|version
r_int
r_char
id|version
suffix:semicolon
multiline_comment|/* Version number of this data structure           */
multiline_comment|/* Version 3 adds chassis_num &amp; WP_index           */
DECL|member|num_scal_dev
r_int
r_char
id|num_scal_dev
suffix:semicolon
multiline_comment|/* # of Scalability devices (Twisters for Vigil)   */
DECL|member|num_rio_dev
r_int
r_char
id|num_rio_dev
suffix:semicolon
multiline_comment|/* # of RIO I/O devices (Cyclones and Winnipegs)   */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|scal_detail
r_struct
id|scal_detail
(brace
DECL|member|node_id
r_int
r_char
id|node_id
suffix:semicolon
multiline_comment|/* Scalability Node ID                             */
DECL|member|CBAR
r_int
r_int
id|CBAR
suffix:semicolon
multiline_comment|/* Address of 1MB register space                   */
DECL|member|port0node
r_int
r_char
id|port0node
suffix:semicolon
multiline_comment|/* Node ID port connected to: 0xFF=None            */
DECL|member|port0port
r_int
r_char
id|port0port
suffix:semicolon
multiline_comment|/* Port num port connected to: 0,1,2, or 0xFF=None */
DECL|member|port1node
r_int
r_char
id|port1node
suffix:semicolon
multiline_comment|/* Node ID port connected to: 0xFF = None          */
DECL|member|port1port
r_int
r_char
id|port1port
suffix:semicolon
multiline_comment|/* Port num port connected to: 0,1,2, or 0xFF=None */
DECL|member|port2node
r_int
r_char
id|port2node
suffix:semicolon
multiline_comment|/* Node ID port connected to: 0xFF = None          */
DECL|member|port2port
r_int
r_char
id|port2port
suffix:semicolon
multiline_comment|/* Port num port connected to: 0,1,2, or 0xFF=None */
DECL|member|chassis_num
r_int
r_char
id|chassis_num
suffix:semicolon
multiline_comment|/* 1 based Chassis number (1 = boot node)          */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|rio_detail
r_struct
id|rio_detail
(brace
DECL|member|node_id
r_int
r_char
id|node_id
suffix:semicolon
multiline_comment|/* RIO Node ID                                     */
DECL|member|BBAR
r_int
r_int
id|BBAR
suffix:semicolon
multiline_comment|/* Address of 1MB register space                   */
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
multiline_comment|/* Type of device                                  */
DECL|member|owner_id
r_int
r_char
id|owner_id
suffix:semicolon
multiline_comment|/* For WPEG: Node ID of Cyclone that owns this WPEG*/
multiline_comment|/* For CYC:  Node ID of Twister that owns this CYC */
DECL|member|port0node
r_int
r_char
id|port0node
suffix:semicolon
multiline_comment|/* Node ID port connected to: 0xFF=None            */
DECL|member|port0port
r_int
r_char
id|port0port
suffix:semicolon
multiline_comment|/* Port num port connected to: 0,1,2, or 0xFF=None */
DECL|member|port1node
r_int
r_char
id|port1node
suffix:semicolon
multiline_comment|/* Node ID port connected to: 0xFF=None            */
DECL|member|port1port
r_int
r_char
id|port1port
suffix:semicolon
multiline_comment|/* Port num port connected to: 0,1,2, or 0xFF=None */
DECL|member|first_slot
r_int
r_char
id|first_slot
suffix:semicolon
multiline_comment|/* For WPEG: Lowest slot number below this WPEG    */
multiline_comment|/* For CYC:  0                                     */
DECL|member|status
r_int
r_char
id|status
suffix:semicolon
multiline_comment|/* For WPEG: Bit 0 = 1 : the XAPIC is used         */
multiline_comment|/*                 = 0 : the XAPIC is not used, ie:*/
multiline_comment|/*                     ints fwded to another XAPIC */
multiline_comment|/*           Bits1:7 Reserved                      */
multiline_comment|/* For CYC:  Bits0:7 Reserved                      */
DECL|member|WP_index
r_int
r_char
id|WP_index
suffix:semicolon
multiline_comment|/* For WPEG: WPEG instance index - lower ones have */
multiline_comment|/*           lower slot numbers/PCI bus numbers    */
multiline_comment|/* For CYC:  No meaning                            */
DECL|member|chassis_num
r_int
r_char
id|chassis_num
suffix:semicolon
multiline_comment|/* 1 based Chassis number                          */
multiline_comment|/* For LookOut WPEGs this field indicates the      */
multiline_comment|/* Expansion Chassis #, enumerated from Boot       */
multiline_comment|/* Node WPEG external port, then Boot Node CYC     */
multiline_comment|/* external port, then Next Vigil chassis WPEG     */
multiline_comment|/* external port, etc.                             */
multiline_comment|/* Shared Lookouts have only 1 chassis number (the */
multiline_comment|/* first one assigned)                             */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|CompatTwister
id|CompatTwister
op_assign
l_int|0
comma
multiline_comment|/* Compatibility Twister               */
DECL|enumerator|AltTwister
id|AltTwister
op_assign
l_int|1
comma
multiline_comment|/* Alternate Twister of internal 8-way */
DECL|enumerator|CompatCyclone
id|CompatCyclone
op_assign
l_int|2
comma
multiline_comment|/* Compatibility Cyclone               */
DECL|enumerator|AltCyclone
id|AltCyclone
op_assign
l_int|3
comma
multiline_comment|/* Alternate Cyclone of internal 8-way */
DECL|enumerator|CompatWPEG
id|CompatWPEG
op_assign
l_int|4
comma
multiline_comment|/* Compatibility WPEG                  */
DECL|enumerator|AltWPEG
id|AltWPEG
op_assign
l_int|5
comma
multiline_comment|/* Second Planar WPEG                  */
DECL|enumerator|LookOutAWPEG
id|LookOutAWPEG
op_assign
l_int|6
comma
multiline_comment|/* LookOut WPEG                        */
DECL|enumerator|LookOutBWPEG
id|LookOutBWPEG
op_assign
l_int|7
comma
multiline_comment|/* LookOut WPEG                        */
DECL|typedef|node_type
)brace
id|node_type
suffix:semicolon
DECL|function|is_WPEG
r_static
r_inline
r_int
(def_block
id|is_WPEG
c_func
(paren
id|node_type
id|type
)paren
(brace
r_return
(paren
id|type
op_eq
id|CompatWPEG
op_logical_or
id|type
op_eq
id|AltWPEG
op_logical_or
id|type
op_eq
id|LookOutAWPEG
op_logical_or
id|type
op_eq
id|LookOutBWPEG
)paren
suffix:semicolon
)brace
)def_block
macro_line|#endif /* __ASM_MACH_MPPARSE_H */
eof
