multiline_comment|/*&n; * Written by: Garry Forsgren, Unisys Corporation&n; *             Natalie Protasevich, Unisys Corporation&n; * This file contains the code to configure and interface &n; * with Unisys ES7000 series hardware system manager.&n; *&n; * Copyright (c) 2003 Unisys Corporation.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Unisys Corporation, Township Line &amp; Union Meeting &n; * Roads-A, Unisys Way, Blue Bell, Pennsylvania, 19424, or:&n; *&n; * http://www.unisys.com&n; */
DECL|macro|MIP_REG
mdefine_line|#define&t;MIP_REG&t;&t;&t;1
DECL|macro|MIP_PSAI_REG
mdefine_line|#define&t;MIP_PSAI_REG&t;&t;4
DECL|macro|MIP_BUSY
mdefine_line|#define&t;MIP_BUSY&t;&t;1
DECL|macro|MIP_SPIN
mdefine_line|#define&t;MIP_SPIN&t;&t;0xf0000
DECL|macro|MIP_VALID
mdefine_line|#define&t;MIP_VALID&t;&t;0x0100000000000000ULL
DECL|macro|MIP_PORT
mdefine_line|#define&t;MIP_PORT(VALUE)&t;((VALUE &gt;&gt; 32) &amp; 0xffff)
DECL|macro|MIP_RD_LO
mdefine_line|#define&t;MIP_RD_LO(VALUE)&t;(VALUE &amp; 0xffffffff)   
DECL|struct|mip_reg_info
r_struct
id|mip_reg_info
(brace
DECL|member|mip_info
r_int
r_int
r_int
id|mip_info
suffix:semicolon
DECL|member|delivery_info
r_int
r_int
r_int
id|delivery_info
suffix:semicolon
DECL|member|host_reg
r_int
r_int
r_int
id|host_reg
suffix:semicolon
DECL|member|mip_reg
r_int
r_int
r_int
id|mip_reg
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|part_info
r_struct
id|part_info
(brace
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
DECL|member|length
r_int
r_char
id|length
suffix:semicolon
DECL|member|part_id
r_int
r_char
id|part_id
suffix:semicolon
DECL|member|apic_mode
r_int
r_char
id|apic_mode
suffix:semicolon
DECL|member|snum
r_int
r_int
id|snum
suffix:semicolon
DECL|member|ptype
r_char
id|ptype
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|sname
r_char
id|sname
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|pname
r_char
id|pname
(braket
l_int|64
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|psai
r_struct
id|psai
(brace
DECL|member|entry_type
r_int
r_int
r_int
id|entry_type
suffix:semicolon
DECL|member|addr
r_int
r_int
r_int
id|addr
suffix:semicolon
DECL|member|bep_addr
r_int
r_int
r_int
id|bep_addr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|es7000_mem_info
r_struct
id|es7000_mem_info
(brace
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
DECL|member|length
r_int
r_char
id|length
suffix:semicolon
DECL|member|resv
r_int
r_char
id|resv
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|start
r_int
r_int
r_int
id|start
suffix:semicolon
DECL|member|size
r_int
r_int
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|es7000_oem_table
r_struct
id|es7000_oem_table
(brace
DECL|member|hdr
r_int
r_int
r_int
id|hdr
suffix:semicolon
DECL|member|mip
r_struct
id|mip_reg_info
id|mip
suffix:semicolon
DECL|member|pif
r_struct
id|part_info
id|pif
suffix:semicolon
DECL|member|shm
r_struct
id|es7000_mem_info
id|shm
suffix:semicolon
DECL|member|psai
r_struct
id|psai
id|psai
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acpi_table_sdt
r_struct
id|acpi_table_sdt
(brace
DECL|member|pa
r_int
r_int
id|pa
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
r_struct
(brace
DECL|member|pa
r_int
r_int
id|pa
suffix:semicolon
DECL|member|id
r_enum
id|acpi_table_id
id|id
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|entry
)brace
id|entry
(braket
l_int|50
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|oem_table
r_struct
id|oem_table
(brace
DECL|member|Header
r_struct
id|acpi_table_header
id|Header
suffix:semicolon
DECL|member|OEMTableAddr
id|u32
id|OEMTableAddr
suffix:semicolon
DECL|member|OEMTableSize
id|u32
id|OEMTableSize
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mip_reg
r_struct
id|mip_reg
(brace
DECL|member|off_0
r_int
r_int
r_int
id|off_0
suffix:semicolon
DECL|member|off_8
r_int
r_int
r_int
id|off_8
suffix:semicolon
DECL|member|off_10
r_int
r_int
r_int
id|off_10
suffix:semicolon
DECL|member|off_18
r_int
r_int
r_int
id|off_18
suffix:semicolon
DECL|member|off_20
r_int
r_int
r_int
id|off_20
suffix:semicolon
DECL|member|off_28
r_int
r_int
r_int
id|off_28
suffix:semicolon
DECL|member|off_30
r_int
r_int
r_int
id|off_30
suffix:semicolon
DECL|member|off_38
r_int
r_int
r_int
id|off_38
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MIP_SW_APIC
mdefine_line|#define&t;MIP_SW_APIC&t;&t;0x1020b
DECL|macro|MIP_FUNC
mdefine_line|#define&t;MIP_FUNC(VALUE) &t;(VALUE &amp; 0xff)
macro_line|#if defined(CONFIG_X86_IO_APIC) &amp;&amp; (defined(CONFIG_ACPI_INTERPRETER) || defined(CONFIG_ACPI_BOOT))
DECL|macro|IOAPIC_GSI_BOUND
mdefine_line|#define IOAPIC_GSI_BOUND(ioapic) ((ioapic+1) * (nr_ioapic_registers[ioapic]-1))
DECL|macro|MAX_GSI_MAPSIZE
mdefine_line|#define MAX_GSI_MAPSIZE 32
macro_line|#endif
r_extern
r_int
r_int
id|io_apic_irqs
suffix:semicolon
r_extern
r_int
id|parse_unisys_oem
(paren
r_char
op_star
id|oemptr
comma
r_int
id|oem_entries
)paren
suffix:semicolon
r_extern
r_int
id|find_unisys_acpi_oem_table
c_func
(paren
r_int
r_int
op_star
id|oem_addr
comma
r_int
op_star
id|length
)paren
suffix:semicolon
r_extern
r_int
id|es7000_start_cpu
c_func
(paren
r_int
id|cpu
comma
r_int
r_int
id|eip
)paren
suffix:semicolon
r_extern
r_void
id|es7000_sw_apic
c_func
(paren
r_void
)paren
suffix:semicolon
eof
