multiline_comment|/******************************************************************************&n; *&n; * Name: actbl.h - Table data structures defined in ACPI specification&n; *       $Revision: 46 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
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
mdefine_line|#define SPIC_SIG                &quot;SPIC&quot;      /* iosapic table */
DECL|macro|BOOT_SIG
mdefine_line|#define BOOT_SIG                &quot;BOOT&quot;      /* Boot table */
DECL|macro|GL_OWNED
mdefine_line|#define GL_OWNED                0x02        /* Ownership of global lock is bit 1 */
multiline_comment|/* values of Mapic.Model */
DECL|macro|DUAL_PIC
mdefine_line|#define DUAL_PIC                0
DECL|macro|MULTIPLE_APIC
mdefine_line|#define MULTIPLE_APIC           1
multiline_comment|/* values of Type in APIC_HEADER */
DECL|macro|APIC_PROC
mdefine_line|#define APIC_PROC               0
DECL|macro|APIC_IO
mdefine_line|#define APIC_IO                 1
multiline_comment|/*&n; * Common table types.  The base code can remain&n; * constant if the underlying tables are changed&n; */
DECL|macro|RSDT_DESCRIPTOR
mdefine_line|#define RSDT_DESCRIPTOR         RSDT_DESCRIPTOR_REV2
DECL|macro|xsdt_descriptor
mdefine_line|#define xsdt_descriptor         XSDT_DESCRIPTOR_REV2
DECL|macro|FACS_DESCRIPTOR
mdefine_line|#define FACS_DESCRIPTOR         facs_descriptor_rev2
DECL|macro|FADT_DESCRIPTOR
mdefine_line|#define FADT_DESCRIPTOR         fadt_descriptor_rev2
macro_line|#pragma pack(1)
multiline_comment|/*&n; * Architecture-independent tables&n; * The architecture dependent tables are in separate files&n; */
r_typedef
r_struct
multiline_comment|/* Root System Descriptor Pointer */
(brace
DECL|member|signature
id|NATIVE_CHAR
id|signature
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* contains &quot;RSD PTR &quot; */
DECL|member|checksum
id|u8
id|checksum
suffix:semicolon
multiline_comment|/* to make sum of struct == 0 */
DECL|member|oem_id
id|NATIVE_CHAR
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
id|NATIVE_CHAR
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* reserved field must be 0 */
DECL|typedef|RSDP_DESCRIPTOR
)brace
id|RSDP_DESCRIPTOR
suffix:semicolon
r_typedef
r_struct
multiline_comment|/* ACPI common table header */
(brace
DECL|member|signature
id|NATIVE_CHAR
id|signature
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* identifies type of table */
DECL|member|length
id|u32
id|length
suffix:semicolon
multiline_comment|/* length of table, in bytes,&n;&t;&t;&t;  * including header */
DECL|member|revision
id|u8
id|revision
suffix:semicolon
multiline_comment|/* specification minor version # */
DECL|member|checksum
id|u8
id|checksum
suffix:semicolon
multiline_comment|/* to make sum of entire table == 0 */
DECL|member|oem_id
id|NATIVE_CHAR
id|oem_id
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* OEM identification */
DECL|member|oem_table_id
id|NATIVE_CHAR
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
id|NATIVE_CHAR
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
DECL|typedef|acpi_table_header
)brace
id|acpi_table_header
suffix:semicolon
r_typedef
r_struct
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
DECL|typedef|acpi_common_facs
)brace
id|acpi_common_facs
suffix:semicolon
r_typedef
r_struct
multiline_comment|/* APIC Table */
(brace
DECL|member|header
id|acpi_table_header
id|header
suffix:semicolon
multiline_comment|/* table header */
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
DECL|typedef|APIC_TABLE
)brace
id|APIC_TABLE
suffix:semicolon
r_typedef
r_struct
multiline_comment|/* APIC Header */
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
DECL|typedef|APIC_HEADER
)brace
id|APIC_HEADER
suffix:semicolon
r_typedef
r_struct
multiline_comment|/* Processor APIC */
(brace
DECL|member|header
id|APIC_HEADER
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
multiline_comment|/* processor&squot;s local APIC id */
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
DECL|typedef|PROCESSOR_APIC
)brace
id|PROCESSOR_APIC
suffix:semicolon
r_typedef
r_struct
multiline_comment|/* IO APIC */
(brace
DECL|member|header
id|APIC_HEADER
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
multiline_comment|/* reserved - must be zero */
DECL|member|io_apic_address
id|u32
id|io_apic_address
suffix:semicolon
multiline_comment|/* APIC&squot;s physical address */
DECL|member|vector
id|u32
id|vector
suffix:semicolon
multiline_comment|/* interrupt vector index where INTI&n;&t;&t;&t;  * lines start */
DECL|typedef|IO_APIC
)brace
id|IO_APIC
suffix:semicolon
multiline_comment|/*&n;**  IA64 TODO:  Add SAPIC Tables&n;*/
multiline_comment|/*&n;**  IA64 TODO:  Modify Smart Battery Description to comply with ACPI IA64&n;**              extensions.&n;*/
r_typedef
r_struct
multiline_comment|/* Smart Battery Description Table */
(brace
DECL|member|header
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
DECL|typedef|SMART_BATTERY_DESCRIPTION_TABLE
)brace
id|SMART_BATTERY_DESCRIPTION_TABLE
suffix:semicolon
macro_line|#pragma pack()
multiline_comment|/*&n; * ACPI Table information.  We save the table address, length,&n; * and type of memory allocation (mapped or allocated) for each&n; * table for 1) when we exit, and 2) if a new table is installed&n; */
DECL|macro|ACPI_MEM_NOT_ALLOCATED
mdefine_line|#define ACPI_MEM_NOT_ALLOCATED  0
DECL|macro|ACPI_MEM_ALLOCATED
mdefine_line|#define ACPI_MEM_ALLOCATED      1
DECL|macro|ACPI_MEM_MAPPED
mdefine_line|#define ACPI_MEM_MAPPED         2
multiline_comment|/* Definitions for the Flags bitfield member of ACPI_TABLE_SUPPORT */
DECL|macro|ACPI_TABLE_SINGLE
mdefine_line|#define ACPI_TABLE_SINGLE       0
DECL|macro|ACPI_TABLE_MULTIPLE
mdefine_line|#define ACPI_TABLE_MULTIPLE     1
multiline_comment|/* Data about each known table type */
DECL|struct|_acpi_table_support
r_typedef
r_struct
id|_acpi_table_support
(brace
DECL|member|name
id|NATIVE_CHAR
op_star
id|name
suffix:semicolon
DECL|member|signature
id|NATIVE_CHAR
op_star
id|signature
suffix:semicolon
DECL|member|sig_length
id|u8
id|sig_length
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|status
id|u16
id|status
suffix:semicolon
DECL|member|global_ptr
r_void
op_star
op_star
id|global_ptr
suffix:semicolon
DECL|typedef|ACPI_TABLE_SUPPORT
)brace
id|ACPI_TABLE_SUPPORT
suffix:semicolon
multiline_comment|/*&n; * Get the architecture-specific tables&n; */
macro_line|#include &quot;actbl1.h&quot;   /* Acpi 1.0 table defintions */
macro_line|#include &quot;actbl71.h&quot;  /* Acpi 0.71 IA-64 Extension table defintions */
macro_line|#include &quot;actbl2.h&quot;   /* Acpi 2.0 table definitions */
macro_line|#endif /* __ACTBL_H__ */
eof
