multiline_comment|/******************************************************************************&n; *&n; * Name: actbl.h - Table data structures defined in ACPI specification&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2005, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
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
multiline_comment|/*&n; * ACPI Version-independent tables&n; *&n; * NOTE: The tables that are specific to ACPI versions (1.0, 2.0, etc.)&n; * are in separate files.&n; */
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
DECL|macro|ACPI_TABLE_HEADER_DEF
mdefine_line|#define ACPI_TABLE_HEADER_DEF   /* ACPI common table header */ &bslash;&n;&t;char                            signature [4];          /* ACPI signature (4 ASCII characters) */&bslash;&n;&t;u32                             length;                 /* Length of table, in bytes, including header */&bslash;&n;&t;u8                              revision;               /* ACPI Specification minor version # */&bslash;&n;&t;u8                              checksum;               /* To make sum of entire table == 0 */&bslash;&n;&t;char                            oem_id [6];             /* OEM identification */&bslash;&n;&t;char                            oem_table_id [8];       /* OEM table identification */&bslash;&n;&t;u32                             oem_revision;           /* OEM revision number */&bslash;&n;&t;char                            asl_compiler_id [4];    /* ASL compiler vendor ID */&bslash;&n;&t;u32                             asl_compiler_revision;  /* ASL compiler revision number */
DECL|struct|acpi_table_header
r_struct
id|acpi_table_header
multiline_comment|/* ACPI common table header */
(brace
id|ACPI_TABLE_HEADER_DEF
)brace
suffix:semicolon
multiline_comment|/*&n; * MADT values and structures&n; */
multiline_comment|/* Values for MADT PCATCompat */
DECL|macro|DUAL_PIC
mdefine_line|#define DUAL_PIC                0
DECL|macro|MULTIPLE_APIC
mdefine_line|#define MULTIPLE_APIC           1
multiline_comment|/* Master MADT */
DECL|struct|multiple_apic_table
r_struct
id|multiple_apic_table
(brace
id|ACPI_TABLE_HEADER_DEF
multiline_comment|/* ACPI common table header */
DECL|member|local_apic_address
id|u32
id|local_apic_address
suffix:semicolon
multiline_comment|/* Physical address of local APIC */
DECL|member|PCATcompat
id|u32
id|PCATcompat
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* A one indicates system also has dual 8259s */
DECL|member|reserved1
id|u32
id|reserved1
suffix:colon
l_int|31
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Values for Type in APIC_HEADER_DEF */
DECL|macro|APIC_PROCESSOR
mdefine_line|#define APIC_PROCESSOR          0
DECL|macro|APIC_IO
mdefine_line|#define APIC_IO                 1
DECL|macro|APIC_XRUPT_OVERRIDE
mdefine_line|#define APIC_XRUPT_OVERRIDE     2
DECL|macro|APIC_NMI
mdefine_line|#define APIC_NMI                3
DECL|macro|APIC_LOCAL_NMI
mdefine_line|#define APIC_LOCAL_NMI          4
DECL|macro|APIC_ADDRESS_OVERRIDE
mdefine_line|#define APIC_ADDRESS_OVERRIDE   5
DECL|macro|APIC_IO_SAPIC
mdefine_line|#define APIC_IO_SAPIC           6
DECL|macro|APIC_LOCAL_SAPIC
mdefine_line|#define APIC_LOCAL_SAPIC        7
DECL|macro|APIC_XRUPT_SOURCE
mdefine_line|#define APIC_XRUPT_SOURCE       8
DECL|macro|APIC_RESERVED
mdefine_line|#define APIC_RESERVED           9           /* 9 and greater are reserved */
multiline_comment|/*&n; * MADT sub-structures (Follow MULTIPLE_APIC_DESCRIPTION_TABLE)&n; */
DECL|macro|APIC_HEADER_DEF
mdefine_line|#define APIC_HEADER_DEF                     /* Common APIC sub-structure header */&bslash;&n;&t;u8                              type; &bslash;&n;&t;u8                              length;
DECL|struct|apic_header
r_struct
id|apic_header
(brace
id|APIC_HEADER_DEF
)brace
suffix:semicolon
multiline_comment|/* Values for MPS INTI flags */
DECL|macro|POLARITY_CONFORMS
mdefine_line|#define POLARITY_CONFORMS       0
DECL|macro|POLARITY_ACTIVE_HIGH
mdefine_line|#define POLARITY_ACTIVE_HIGH    1
DECL|macro|POLARITY_RESERVED
mdefine_line|#define POLARITY_RESERVED       2
DECL|macro|POLARITY_ACTIVE_LOW
mdefine_line|#define POLARITY_ACTIVE_LOW     3
DECL|macro|TRIGGER_CONFORMS
mdefine_line|#define TRIGGER_CONFORMS        0
DECL|macro|TRIGGER_EDGE
mdefine_line|#define TRIGGER_EDGE            1
DECL|macro|TRIGGER_RESERVED
mdefine_line|#define TRIGGER_RESERVED        2
DECL|macro|TRIGGER_LEVEL
mdefine_line|#define TRIGGER_LEVEL           3
multiline_comment|/* Common flag definitions */
DECL|macro|MPS_INTI_FLAGS
mdefine_line|#define MPS_INTI_FLAGS &bslash;&n;&t;u16                             polarity        : 2;    /* Polarity of APIC I/O input signals */&bslash;&n;&t;u16                             trigger_mode    : 2;    /* Trigger mode of APIC input signals */&bslash;&n;&t;u16                             reserved1       : 12;   /* Reserved, must be zero */
DECL|macro|LOCAL_APIC_FLAGS
mdefine_line|#define LOCAL_APIC_FLAGS &bslash;&n;&t;u32                             processor_enabled: 1;   /* Processor is usable if set */&bslash;&n;&t;u32                             reserved2       : 31;   /* Reserved, must be zero */
multiline_comment|/* Sub-structures for MADT */
DECL|struct|madt_processor_apic
r_struct
id|madt_processor_apic
(brace
id|APIC_HEADER_DEF
DECL|member|processor_id
id|u8
id|processor_id
suffix:semicolon
multiline_comment|/* ACPI processor id */
DECL|member|local_apic_id
id|u8
id|local_apic_id
suffix:semicolon
multiline_comment|/* Processor&squot;s local APIC id */
id|LOCAL_APIC_FLAGS
)brace
suffix:semicolon
DECL|struct|madt_io_apic
r_struct
id|madt_io_apic
(brace
id|APIC_HEADER_DEF
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
DECL|member|address
id|u32
id|address
suffix:semicolon
multiline_comment|/* APIC physical address */
DECL|member|interrupt
id|u32
id|interrupt
suffix:semicolon
multiline_comment|/* Global system interrupt where INTI&n;&t;&t;&t;  * lines start */
)brace
suffix:semicolon
DECL|struct|madt_interrupt_override
r_struct
id|madt_interrupt_override
(brace
id|APIC_HEADER_DEF
DECL|member|bus
id|u8
id|bus
suffix:semicolon
multiline_comment|/* 0 - ISA */
DECL|member|source
id|u8
id|source
suffix:semicolon
multiline_comment|/* Interrupt source (IRQ) */
DECL|member|interrupt
id|u32
id|interrupt
suffix:semicolon
multiline_comment|/* Global system interrupt */
id|MPS_INTI_FLAGS
)brace
suffix:semicolon
DECL|struct|madt_nmi_source
r_struct
id|madt_nmi_source
(brace
id|APIC_HEADER_DEF
id|MPS_INTI_FLAGS
DECL|member|interrupt
id|u32
id|interrupt
suffix:semicolon
multiline_comment|/* Global system interrupt */
)brace
suffix:semicolon
DECL|struct|madt_local_apic_nmi
r_struct
id|madt_local_apic_nmi
(brace
id|APIC_HEADER_DEF
DECL|member|processor_id
id|u8
id|processor_id
suffix:semicolon
multiline_comment|/* ACPI processor id */
id|MPS_INTI_FLAGS
DECL|member|lint
id|u8
id|lint
suffix:semicolon
multiline_comment|/* LINTn to which NMI is connected */
)brace
suffix:semicolon
DECL|struct|madt_address_override
r_struct
id|madt_address_override
(brace
id|APIC_HEADER_DEF
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
multiline_comment|/* Reserved - must be zero */
DECL|member|address
id|u64
id|address
suffix:semicolon
multiline_comment|/* APIC physical address */
)brace
suffix:semicolon
DECL|struct|madt_io_sapic
r_struct
id|madt_io_sapic
(brace
id|APIC_HEADER_DEF
DECL|member|io_sapic_id
id|u8
id|io_sapic_id
suffix:semicolon
multiline_comment|/* I/O SAPIC ID */
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
multiline_comment|/* Reserved - must be zero */
DECL|member|interrupt_base
id|u32
id|interrupt_base
suffix:semicolon
multiline_comment|/* Glocal interrupt for SAPIC start */
DECL|member|address
id|u64
id|address
suffix:semicolon
multiline_comment|/* SAPIC physical address */
)brace
suffix:semicolon
DECL|struct|madt_local_sapic
r_struct
id|madt_local_sapic
(brace
id|APIC_HEADER_DEF
DECL|member|processor_id
id|u8
id|processor_id
suffix:semicolon
multiline_comment|/* ACPI processor id */
DECL|member|local_sapic_id
id|u8
id|local_sapic_id
suffix:semicolon
multiline_comment|/* SAPIC ID */
DECL|member|local_sapic_eid
id|u8
id|local_sapic_eid
suffix:semicolon
multiline_comment|/* SAPIC EID */
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Reserved - must be zero */
id|LOCAL_APIC_FLAGS
)brace
suffix:semicolon
DECL|struct|madt_interrupt_source
r_struct
id|madt_interrupt_source
(brace
id|APIC_HEADER_DEF
id|MPS_INTI_FLAGS
DECL|member|interrupt_type
id|u8
id|interrupt_type
suffix:semicolon
multiline_comment|/* 1=PMI, 2=INIT, 3=corrected */
DECL|member|processor_id
id|u8
id|processor_id
suffix:semicolon
multiline_comment|/* Processor ID */
DECL|member|processor_eid
id|u8
id|processor_eid
suffix:semicolon
multiline_comment|/* Processor EID */
DECL|member|io_sapic_vector
id|u8
id|io_sapic_vector
suffix:semicolon
multiline_comment|/* Vector value for PMI interrupts */
DECL|member|interrupt
id|u32
id|interrupt
suffix:semicolon
multiline_comment|/* Global system interrupt */
DECL|member|reserved
id|u32
id|reserved
suffix:semicolon
multiline_comment|/* Reserved - must be zero */
)brace
suffix:semicolon
multiline_comment|/*&n; * Smart Battery&n; */
DECL|struct|smart_battery_table
r_struct
id|smart_battery_table
(brace
id|ACPI_TABLE_HEADER_DEF
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
multiline_comment|/*&n; * Get the ACPI version-specific tables&n; */
macro_line|#include &quot;actbl1.h&quot;   /* Acpi 1.0 table definitions */
macro_line|#include &quot;actbl2.h&quot;   /* Acpi 2.0 table definitions */
r_extern
id|u8
id|acpi_fadt_is_v1
suffix:semicolon
multiline_comment|/* is set to 1 if FADT is revision 1,&n;&t;&t;&t;    * needed for certain workarounds */
macro_line|#pragma pack(1)
multiline_comment|/*&n; * High performance timer&n; */
DECL|struct|hpet_table
r_struct
id|hpet_table
(brace
id|ACPI_TABLE_HEADER_DEF
DECL|member|hardware_id
id|u32
id|hardware_id
suffix:semicolon
DECL|member|base_address
r_struct
id|acpi_generic_address
id|base_address
suffix:semicolon
DECL|member|hpet_number
id|u8
id|hpet_number
suffix:semicolon
DECL|member|clock_tick
id|u16
id|clock_tick
suffix:semicolon
DECL|member|attributes
id|u8
id|attributes
suffix:semicolon
)brace
suffix:semicolon
macro_line|#pragma pack()
macro_line|#endif /* __ACTBL_H__ */
eof
