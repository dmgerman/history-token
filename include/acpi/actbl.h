multiline_comment|/******************************************************************************&n; *&n; * Name: actbl.h - Table data structures defined in ACPI specification&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2003, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#ifndef __ACTBL_H__
DECL|macro|__ACTBL_H__
mdefine_line|#define __ACTBL_H__
multiline_comment|/*&n; *  Values for description table header signatures&n; */
DECL|macro|RSDP_NAME
mdefine_line|#define RSDP_NAME               &quot;RSDP&quot;
DECL|macro|RSDP_SIG
mdefine_line|#define RSDP_SIG                &quot;RSD PTR &quot;  /* RSDT Pointer signature */
DECL|macro|APIC_SIG
mdefine_line|#define APIC_SIG                &quot;APIC&quot;      /* Multiple APIC Description Table */
DECL|macro|DSDT_SIG
mdefine_line|#define DSDT_SIG                &quot;DSDT&quot;      /* Differentiated System Description Table */
DECL|macro|FADT_SIG
mdefine_line|#define FADT_SIG                &quot;FACP&quot;      /* Fixed ACPI Description Table */
DECL|macro|FACS_SIG
mdefine_line|#define FACS_SIG                &quot;FACS&quot;      /* Firmware ACPI Control Structure */
DECL|macro|PSDT_SIG
mdefine_line|#define PSDT_SIG                &quot;PSDT&quot;      /* Persistent System Description Table */
DECL|macro|RSDT_SIG
mdefine_line|#define RSDT_SIG                &quot;RSDT&quot;      /* Root System Description Table */
DECL|macro|XSDT_SIG
mdefine_line|#define XSDT_SIG                &quot;XSDT&quot;      /* Extended  System Description Table */
DECL|macro|SSDT_SIG
mdefine_line|#define SSDT_SIG                &quot;SSDT&quot;      /* Secondary System Description Table */
DECL|macro|SBST_SIG
mdefine_line|#define SBST_SIG                &quot;SBST&quot;      /* Smart Battery Specification Table */
DECL|macro|SPIC_SIG
mdefine_line|#define SPIC_SIG                &quot;SPIC&quot;      /* IOSAPIC table */
DECL|macro|BOOT_SIG
mdefine_line|#define BOOT_SIG                &quot;BOOT&quot;      /* Boot table */
DECL|macro|GL_OWNED
mdefine_line|#define GL_OWNED                0x02        /* Ownership of global lock is bit 1 */
multiline_comment|/* values of Mapic.Model */
DECL|macro|DUAL_PIC
mdefine_line|#define DUAL_PIC                0
DECL|macro|MULTIPLE_APIC
mdefine_line|#define MULTIPLE_APIC           1
multiline_comment|/* values of Type in struct apic_header */
DECL|macro|APIC_PROC
mdefine_line|#define APIC_PROC               0
DECL|macro|APIC_IO
mdefine_line|#define APIC_IO                 1
multiline_comment|/*&n; * Common table types.  The base code can remain&n; * constant if the underlying tables are changed&n; */
DECL|macro|RSDT_DESCRIPTOR
mdefine_line|#define RSDT_DESCRIPTOR         struct rsdt_descriptor_rev2
DECL|macro|XSDT_DESCRIPTOR
mdefine_line|#define XSDT_DESCRIPTOR         struct xsdt_descriptor_rev2
DECL|macro|FACS_DESCRIPTOR
mdefine_line|#define FACS_DESCRIPTOR         struct facs_descriptor_rev2
DECL|macro|FADT_DESCRIPTOR
mdefine_line|#define FADT_DESCRIPTOR         struct fadt_descriptor_rev2
macro_line|#pragma pack(1)
multiline_comment|/*&n; * Architecture-independent tables&n; * The architecture dependent tables are in separate files&n; */
DECL|struct|rsdp_descriptor
r_struct
id|rsdp_descriptor
multiline_comment|/* Root System Descriptor Pointer */
(brace
DECL|member|signature
r_char
id|signature
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* ACPI signature, contains &quot;RSD PTR &quot; */
DECL|member|checksum
id|u8
id|checksum
suffix:semicolon
multiline_comment|/* To make sum of struct == 0 */
DECL|member|oem_id
r_char
id|oem_id
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* OEM identification */
DECL|member|revision
id|u8
id|revision
suffix:semicolon
multiline_comment|/* Must be 0 for 1.0, 2 for 2.0 */
DECL|member|rsdt_physical_address
id|u32
id|rsdt_physical_address
suffix:semicolon
multiline_comment|/* 32-bit physical address of RSDT */
DECL|member|length
id|u32
id|length
suffix:semicolon
multiline_comment|/* XSDT Length in bytes including hdr */
DECL|member|xsdt_physical_address
id|u64
id|xsdt_physical_address
suffix:semicolon
multiline_comment|/* 64-bit physical address of XSDT */
DECL|member|extended_checksum
id|u8
id|extended_checksum
suffix:semicolon
multiline_comment|/* Checksum of entire table */
DECL|member|reserved
r_char
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Reserved field must be 0 */
)brace
suffix:semicolon
DECL|struct|acpi_table_header
r_struct
id|acpi_table_header
multiline_comment|/* ACPI common table header */
(brace
DECL|member|signature
r_char
id|signature
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* ACPI signature (4 ASCII characters) */
DECL|member|length
id|u32
id|length
suffix:semicolon
multiline_comment|/* Length of table, in bytes, including header */
DECL|member|revision
id|u8
id|revision
suffix:semicolon
multiline_comment|/* ACPI Specification minor version # */
DECL|member|checksum
id|u8
id|checksum
suffix:semicolon
multiline_comment|/* To make sum of entire table == 0 */
DECL|member|oem_id
r_char
id|oem_id
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* OEM identification */
DECL|member|oem_table_id
r_char
id|oem_table_id
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* OEM table identification */
DECL|member|oem_revision
id|u32
id|oem_revision
suffix:semicolon
multiline_comment|/* OEM revision number */
DECL|member|asl_compiler_id
r_char
id|asl_compiler_id
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* ASL compiler vendor ID */
DECL|member|asl_compiler_revision
id|u32
id|asl_compiler_revision
suffix:semicolon
multiline_comment|/* ASL compiler revision number */
)brace
suffix:semicolon
DECL|struct|acpi_common_facs
r_struct
id|acpi_common_facs
multiline_comment|/* Common FACS for internal use */
(brace
DECL|member|global_lock
id|u32
op_star
id|global_lock
suffix:semicolon
DECL|member|firmware_waking_vector
id|u64
op_star
id|firmware_waking_vector
suffix:semicolon
DECL|member|vector_width
id|u8
id|vector_width
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|apic_table
r_struct
id|apic_table
(brace
DECL|member|header
r_struct
id|acpi_table_header
id|header
suffix:semicolon
multiline_comment|/* ACPI table header */
DECL|member|local_apic_address
id|u32
id|local_apic_address
suffix:semicolon
multiline_comment|/* Physical address for accessing local APICs */
DECL|member|PCATcompat
id|u32
id|PCATcompat
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* a one indicates system also has dual 8259s */
DECL|member|reserved1
id|u32
id|reserved1
suffix:colon
l_int|31
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|apic_header
r_struct
id|apic_header
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
multiline_comment|/* APIC type.  Either APIC_PROC or APIC_IO */
DECL|member|length
id|u8
id|length
suffix:semicolon
multiline_comment|/* Length of APIC structure */
)brace
suffix:semicolon
DECL|struct|processor_apic
r_struct
id|processor_apic
(brace
DECL|member|header
r_struct
id|apic_header
id|header
suffix:semicolon
DECL|member|processor_apic_id
id|u8
id|processor_apic_id
suffix:semicolon
multiline_comment|/* ACPI processor id */
DECL|member|local_apic_id
id|u8
id|local_apic_id
suffix:semicolon
multiline_comment|/* Processor&squot;s local APIC id */
DECL|member|processor_enabled
id|u32
id|processor_enabled
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Processor is usable if set */
DECL|member|reserved1
id|u32
id|reserved1
suffix:colon
l_int|31
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|io_apic
r_struct
id|io_apic
(brace
DECL|member|header
r_struct
id|apic_header
id|header
suffix:semicolon
DECL|member|io_apic_id
id|u8
id|io_apic_id
suffix:semicolon
multiline_comment|/* I/O APIC ID */
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
multiline_comment|/* Reserved - must be zero */
DECL|member|io_apic_address
id|u32
id|io_apic_address
suffix:semicolon
multiline_comment|/* APIC&squot;s physical address */
DECL|member|vector
id|u32
id|vector
suffix:semicolon
multiline_comment|/* Interrupt vector index where INTI&n;&t;&t;&t;  * lines start */
)brace
suffix:semicolon
multiline_comment|/*&n; *  IA64 TBD:  Add SAPIC Tables&n; */
multiline_comment|/*&n; *  IA64 TBD:   Modify Smart Battery Description to comply with ACPI IA64&n; *              extensions.&n; */
DECL|struct|smart_battery_description_table
r_struct
id|smart_battery_description_table
(brace
DECL|member|header
r_struct
id|acpi_table_header
id|header
suffix:semicolon
DECL|member|warning_level
id|u32
id|warning_level
suffix:semicolon
DECL|member|low_level
id|u32
id|low_level
suffix:semicolon
DECL|member|critical_level
id|u32
id|critical_level
suffix:semicolon
)brace
suffix:semicolon
macro_line|#pragma pack()
multiline_comment|/*&n; * ACPI Table information.  We save the table address, length,&n; * and type of memory allocation (mapped or allocated) for each&n; * table for 1) when we exit, and 2) if a new table is installed&n; */
DECL|macro|ACPI_MEM_NOT_ALLOCATED
mdefine_line|#define ACPI_MEM_NOT_ALLOCATED  0
DECL|macro|ACPI_MEM_ALLOCATED
mdefine_line|#define ACPI_MEM_ALLOCATED      1
DECL|macro|ACPI_MEM_MAPPED
mdefine_line|#define ACPI_MEM_MAPPED         2
multiline_comment|/* Definitions for the Flags bitfield member of struct acpi_table_support */
DECL|macro|ACPI_TABLE_SINGLE
mdefine_line|#define ACPI_TABLE_SINGLE       0x00
DECL|macro|ACPI_TABLE_MULTIPLE
mdefine_line|#define ACPI_TABLE_MULTIPLE     0x01
DECL|macro|ACPI_TABLE_EXECUTABLE
mdefine_line|#define ACPI_TABLE_EXECUTABLE   0x02
DECL|macro|ACPI_TABLE_ROOT
mdefine_line|#define ACPI_TABLE_ROOT         0x00
DECL|macro|ACPI_TABLE_PRIMARY
mdefine_line|#define ACPI_TABLE_PRIMARY      0x10
DECL|macro|ACPI_TABLE_SECONDARY
mdefine_line|#define ACPI_TABLE_SECONDARY    0x20
DECL|macro|ACPI_TABLE_ALL
mdefine_line|#define ACPI_TABLE_ALL          0x30
DECL|macro|ACPI_TABLE_TYPE_MASK
mdefine_line|#define ACPI_TABLE_TYPE_MASK    0x30
multiline_comment|/* Data about each known table type */
DECL|struct|acpi_table_support
r_struct
id|acpi_table_support
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|signature
r_char
op_star
id|signature
suffix:semicolon
DECL|member|global_ptr
r_void
op_star
op_star
id|global_ptr
suffix:semicolon
DECL|member|sig_length
id|u8
id|sig_length
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Get the architecture-specific tables&n; */
macro_line|#include &quot;actbl1.h&quot;   /* Acpi 1.0 table definitions */
macro_line|#include &quot;actbl2.h&quot;   /* Acpi 2.0 table definitions */
macro_line|#endif /* __ACTBL_H__ */
eof
