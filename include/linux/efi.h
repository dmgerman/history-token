macro_line|#ifndef _LINUX_EFI_H
DECL|macro|_LINUX_EFI_H
mdefine_line|#define _LINUX_EFI_H
multiline_comment|/*&n; * Extensible Firmware Interface&n; * Based on &squot;Extensible Firmware Interface Specification&squot; version 0.9, April 30, 1999&n; *&n; * Copyright (C) 1999 VA Linux Systems&n; * Copyright (C) 1999 Walt Drummond &lt;drummond@valinux.com&gt;&n; * Copyright (C) 1999, 2002-2003 Hewlett-Packard Co.&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&t;Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|EFI_SUCCESS
mdefine_line|#define EFI_SUCCESS&t;&t;0
DECL|macro|EFI_LOAD_ERROR
mdefine_line|#define EFI_LOAD_ERROR          ( 1 | (1UL &lt;&lt; (BITS_PER_LONG-1)))
DECL|macro|EFI_INVALID_PARAMETER
mdefine_line|#define EFI_INVALID_PARAMETER&t;( 2 | (1UL &lt;&lt; (BITS_PER_LONG-1)))
DECL|macro|EFI_UNSUPPORTED
mdefine_line|#define EFI_UNSUPPORTED&t;&t;( 3 | (1UL &lt;&lt; (BITS_PER_LONG-1)))
DECL|macro|EFI_BAD_BUFFER_SIZE
mdefine_line|#define EFI_BAD_BUFFER_SIZE     ( 4 | (1UL &lt;&lt; (BITS_PER_LONG-1)))
DECL|macro|EFI_BUFFER_TOO_SMALL
mdefine_line|#define EFI_BUFFER_TOO_SMALL&t;( 5 | (1UL &lt;&lt; (BITS_PER_LONG-1)))
DECL|macro|EFI_NOT_FOUND
mdefine_line|#define EFI_NOT_FOUND&t;&t;(14 | (1UL &lt;&lt; (BITS_PER_LONG-1)))
DECL|typedef|efi_status_t
r_typedef
r_int
r_int
id|efi_status_t
suffix:semicolon
DECL|typedef|efi_bool_t
r_typedef
id|u8
id|efi_bool_t
suffix:semicolon
DECL|typedef|efi_char16_t
r_typedef
id|u16
id|efi_char16_t
suffix:semicolon
multiline_comment|/* UNICODE character */
r_typedef
r_struct
(brace
DECL|member|b
id|u8
id|b
(braket
l_int|16
)braket
suffix:semicolon
DECL|typedef|efi_guid_t
)brace
id|efi_guid_t
suffix:semicolon
DECL|macro|EFI_GUID
mdefine_line|#define EFI_GUID(a,b,c,d0,d1,d2,d3,d4,d5,d6,d7) &bslash;&n;((efi_guid_t) &bslash;&n;{{ (a) &amp; 0xff, ((a) &gt;&gt; 8) &amp; 0xff, ((a) &gt;&gt; 16) &amp; 0xff, ((a) &gt;&gt; 24) &amp; 0xff, &bslash;&n;  (b) &amp; 0xff, ((b) &gt;&gt; 8) &amp; 0xff, &bslash;&n;  (c) &amp; 0xff, ((c) &gt;&gt; 8) &amp; 0xff, &bslash;&n;  (d0), (d1), (d2), (d3), (d4), (d5), (d6), (d7) }})
multiline_comment|/*&n; * Generic EFI table header&n; */
r_typedef
r_struct
(brace
DECL|member|signature
id|u64
id|signature
suffix:semicolon
DECL|member|revision
id|u32
id|revision
suffix:semicolon
DECL|member|headersize
id|u32
id|headersize
suffix:semicolon
DECL|member|crc32
id|u32
id|crc32
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:semicolon
DECL|typedef|efi_table_hdr_t
)brace
id|efi_table_hdr_t
suffix:semicolon
multiline_comment|/*&n; * Memory map descriptor:&n; */
multiline_comment|/* Memory types: */
DECL|macro|EFI_RESERVED_TYPE
mdefine_line|#define EFI_RESERVED_TYPE&t;&t; 0
DECL|macro|EFI_LOADER_CODE
mdefine_line|#define EFI_LOADER_CODE&t;&t;&t; 1
DECL|macro|EFI_LOADER_DATA
mdefine_line|#define EFI_LOADER_DATA&t;&t;&t; 2
DECL|macro|EFI_BOOT_SERVICES_CODE
mdefine_line|#define EFI_BOOT_SERVICES_CODE&t;&t; 3
DECL|macro|EFI_BOOT_SERVICES_DATA
mdefine_line|#define EFI_BOOT_SERVICES_DATA&t;&t; 4
DECL|macro|EFI_RUNTIME_SERVICES_CODE
mdefine_line|#define EFI_RUNTIME_SERVICES_CODE&t; 5
DECL|macro|EFI_RUNTIME_SERVICES_DATA
mdefine_line|#define EFI_RUNTIME_SERVICES_DATA&t; 6
DECL|macro|EFI_CONVENTIONAL_MEMORY
mdefine_line|#define EFI_CONVENTIONAL_MEMORY&t;&t; 7
DECL|macro|EFI_UNUSABLE_MEMORY
mdefine_line|#define EFI_UNUSABLE_MEMORY&t;&t; 8
DECL|macro|EFI_ACPI_RECLAIM_MEMORY
mdefine_line|#define EFI_ACPI_RECLAIM_MEMORY&t;&t; 9
DECL|macro|EFI_ACPI_MEMORY_NVS
mdefine_line|#define EFI_ACPI_MEMORY_NVS&t;&t;10
DECL|macro|EFI_MEMORY_MAPPED_IO
mdefine_line|#define EFI_MEMORY_MAPPED_IO&t;&t;11
DECL|macro|EFI_MEMORY_MAPPED_IO_PORT_SPACE
mdefine_line|#define EFI_MEMORY_MAPPED_IO_PORT_SPACE&t;12
DECL|macro|EFI_PAL_CODE
mdefine_line|#define EFI_PAL_CODE&t;&t;&t;13
DECL|macro|EFI_MAX_MEMORY_TYPE
mdefine_line|#define EFI_MAX_MEMORY_TYPE&t;&t;14
multiline_comment|/* Attribute values: */
DECL|macro|EFI_MEMORY_UC
mdefine_line|#define EFI_MEMORY_UC&t;&t;0x0000000000000001&t;/* uncached */
DECL|macro|EFI_MEMORY_WC
mdefine_line|#define EFI_MEMORY_WC&t;&t;0x0000000000000002&t;/* write-coalescing */
DECL|macro|EFI_MEMORY_WT
mdefine_line|#define EFI_MEMORY_WT&t;&t;0x0000000000000004&t;/* write-through */
DECL|macro|EFI_MEMORY_WB
mdefine_line|#define EFI_MEMORY_WB&t;&t;0x0000000000000008&t;/* write-back */
DECL|macro|EFI_MEMORY_WP
mdefine_line|#define EFI_MEMORY_WP&t;&t;0x0000000000001000&t;/* write-protect */
DECL|macro|EFI_MEMORY_RP
mdefine_line|#define EFI_MEMORY_RP&t;&t;0x0000000000002000&t;/* read-protect */
DECL|macro|EFI_MEMORY_XP
mdefine_line|#define EFI_MEMORY_XP&t;&t;0x0000000000004000&t;/* execute-protect */
DECL|macro|EFI_MEMORY_RUNTIME
mdefine_line|#define EFI_MEMORY_RUNTIME&t;0x8000000000000000&t;/* range requires runtime mapping */
DECL|macro|EFI_MEMORY_DESCRIPTOR_VERSION
mdefine_line|#define EFI_MEMORY_DESCRIPTOR_VERSION&t;1
DECL|macro|EFI_PAGE_SHIFT
mdefine_line|#define EFI_PAGE_SHIFT&t;&t;12
r_typedef
r_struct
(brace
DECL|member|type
id|u32
id|type
suffix:semicolon
DECL|member|pad
id|u32
id|pad
suffix:semicolon
DECL|member|phys_addr
id|u64
id|phys_addr
suffix:semicolon
DECL|member|virt_addr
id|u64
id|virt_addr
suffix:semicolon
DECL|member|num_pages
id|u64
id|num_pages
suffix:semicolon
DECL|member|attribute
id|u64
id|attribute
suffix:semicolon
DECL|typedef|efi_memory_desc_t
)brace
id|efi_memory_desc_t
suffix:semicolon
DECL|typedef|efi_freemem_callback_t
r_typedef
r_int
id|efi_freemem_callback_t
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
multiline_comment|/*&n; * Types and defines for Time Services&n; */
DECL|macro|EFI_TIME_ADJUST_DAYLIGHT
mdefine_line|#define EFI_TIME_ADJUST_DAYLIGHT 0x1
DECL|macro|EFI_TIME_IN_DAYLIGHT
mdefine_line|#define EFI_TIME_IN_DAYLIGHT     0x2
DECL|macro|EFI_UNSPECIFIED_TIMEZONE
mdefine_line|#define EFI_UNSPECIFIED_TIMEZONE 0x07ff
r_typedef
r_struct
(brace
DECL|member|year
id|u16
id|year
suffix:semicolon
DECL|member|month
id|u8
id|month
suffix:semicolon
DECL|member|day
id|u8
id|day
suffix:semicolon
DECL|member|hour
id|u8
id|hour
suffix:semicolon
DECL|member|minute
id|u8
id|minute
suffix:semicolon
DECL|member|second
id|u8
id|second
suffix:semicolon
DECL|member|pad1
id|u8
id|pad1
suffix:semicolon
DECL|member|nanosecond
id|u32
id|nanosecond
suffix:semicolon
DECL|member|timezone
id|s16
id|timezone
suffix:semicolon
DECL|member|daylight
id|u8
id|daylight
suffix:semicolon
DECL|member|pad2
id|u8
id|pad2
suffix:semicolon
DECL|typedef|efi_time_t
)brace
id|efi_time_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|resolution
id|u32
id|resolution
suffix:semicolon
DECL|member|accuracy
id|u32
id|accuracy
suffix:semicolon
DECL|member|sets_to_zero
id|u8
id|sets_to_zero
suffix:semicolon
DECL|typedef|efi_time_cap_t
)brace
id|efi_time_cap_t
suffix:semicolon
multiline_comment|/*&n; * Types and defines for EFI ResetSystem&n; */
DECL|macro|EFI_RESET_COLD
mdefine_line|#define EFI_RESET_COLD 0
DECL|macro|EFI_RESET_WARM
mdefine_line|#define EFI_RESET_WARM 1
multiline_comment|/*&n; * EFI Runtime Services table&n; */
DECL|macro|EFI_RUNTIME_SERVICES_SIGNATURE
mdefine_line|#define EFI_RUNTIME_SERVICES_SIGNATURE 0x5652453544e5552
DECL|macro|EFI_RUNTIME_SERVICES_REVISION
mdefine_line|#define EFI_RUNTIME_SERVICES_REVISION  0x00010000
r_typedef
r_struct
(brace
DECL|member|hdr
id|efi_table_hdr_t
id|hdr
suffix:semicolon
DECL|member|get_time
r_int
r_int
id|get_time
suffix:semicolon
DECL|member|set_time
r_int
r_int
id|set_time
suffix:semicolon
DECL|member|get_wakeup_time
r_int
r_int
id|get_wakeup_time
suffix:semicolon
DECL|member|set_wakeup_time
r_int
r_int
id|set_wakeup_time
suffix:semicolon
DECL|member|set_virtual_address_map
r_int
r_int
id|set_virtual_address_map
suffix:semicolon
DECL|member|convert_pointer
r_int
r_int
id|convert_pointer
suffix:semicolon
DECL|member|get_variable
r_int
r_int
id|get_variable
suffix:semicolon
DECL|member|get_next_variable
r_int
r_int
id|get_next_variable
suffix:semicolon
DECL|member|set_variable
r_int
r_int
id|set_variable
suffix:semicolon
DECL|member|get_next_high_mono_count
r_int
r_int
id|get_next_high_mono_count
suffix:semicolon
DECL|member|reset_system
r_int
r_int
id|reset_system
suffix:semicolon
DECL|typedef|efi_runtime_services_t
)brace
id|efi_runtime_services_t
suffix:semicolon
DECL|typedef|efi_get_time_t
r_typedef
id|efi_status_t
id|efi_get_time_t
(paren
id|efi_time_t
op_star
id|tm
comma
id|efi_time_cap_t
op_star
id|tc
)paren
suffix:semicolon
DECL|typedef|efi_set_time_t
r_typedef
id|efi_status_t
id|efi_set_time_t
(paren
id|efi_time_t
op_star
id|tm
)paren
suffix:semicolon
DECL|typedef|efi_get_wakeup_time_t
r_typedef
id|efi_status_t
id|efi_get_wakeup_time_t
(paren
id|efi_bool_t
op_star
id|enabled
comma
id|efi_bool_t
op_star
id|pending
comma
id|efi_time_t
op_star
id|tm
)paren
suffix:semicolon
DECL|typedef|efi_set_wakeup_time_t
r_typedef
id|efi_status_t
id|efi_set_wakeup_time_t
(paren
id|efi_bool_t
id|enabled
comma
id|efi_time_t
op_star
id|tm
)paren
suffix:semicolon
DECL|typedef|efi_get_variable_t
r_typedef
id|efi_status_t
id|efi_get_variable_t
(paren
id|efi_char16_t
op_star
id|name
comma
id|efi_guid_t
op_star
id|vendor
comma
id|u32
op_star
id|attr
comma
r_int
r_int
op_star
id|data_size
comma
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|typedef|efi_get_next_variable_t
r_typedef
id|efi_status_t
id|efi_get_next_variable_t
(paren
r_int
r_int
op_star
id|name_size
comma
id|efi_char16_t
op_star
id|name
comma
id|efi_guid_t
op_star
id|vendor
)paren
suffix:semicolon
DECL|typedef|efi_set_variable_t
r_typedef
id|efi_status_t
id|efi_set_variable_t
(paren
id|efi_char16_t
op_star
id|name
comma
id|efi_guid_t
op_star
id|vendor
comma
r_int
r_int
id|attr
comma
r_int
r_int
id|data_size
comma
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|typedef|efi_get_next_high_mono_count_t
r_typedef
id|efi_status_t
id|efi_get_next_high_mono_count_t
(paren
id|u32
op_star
id|count
)paren
suffix:semicolon
DECL|typedef|efi_reset_system_t
r_typedef
r_void
id|efi_reset_system_t
(paren
r_int
id|reset_type
comma
id|efi_status_t
id|status
comma
r_int
r_int
id|data_size
comma
id|efi_char16_t
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/*&n; *  EFI Configuration Table and GUID definitions&n; */
DECL|macro|NULL_GUID
mdefine_line|#define NULL_GUID &bslash;&n;    EFI_GUID(  0x00000000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 )
DECL|macro|MPS_TABLE_GUID
mdefine_line|#define MPS_TABLE_GUID    &bslash;&n;    EFI_GUID(  0xeb9d2d2f, 0x2d88, 0x11d3, 0x9a, 0x16, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d )
DECL|macro|ACPI_TABLE_GUID
mdefine_line|#define ACPI_TABLE_GUID    &bslash;&n;    EFI_GUID(  0xeb9d2d30, 0x2d88, 0x11d3, 0x9a, 0x16, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d )
DECL|macro|ACPI_20_TABLE_GUID
mdefine_line|#define ACPI_20_TABLE_GUID    &bslash;&n;    EFI_GUID(  0x8868e871, 0xe4f1, 0x11d3, 0xbc, 0x22, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81 )
DECL|macro|SMBIOS_TABLE_GUID
mdefine_line|#define SMBIOS_TABLE_GUID    &bslash;&n;    EFI_GUID(  0xeb9d2d31, 0x2d88, 0x11d3, 0x9a, 0x16, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d )
DECL|macro|SAL_SYSTEM_TABLE_GUID
mdefine_line|#define SAL_SYSTEM_TABLE_GUID    &bslash;&n;    EFI_GUID(  0xeb9d2d32, 0x2d88, 0x11d3, 0x9a, 0x16, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d )
DECL|macro|HCDP_TABLE_GUID
mdefine_line|#define HCDP_TABLE_GUID&t;&bslash;&n;    EFI_GUID(  0xf951938d, 0x620b, 0x42ef, 0x82, 0x79, 0xa8, 0x4b, 0x79, 0x61, 0x78, 0x98 )
r_typedef
r_struct
(brace
DECL|member|guid
id|efi_guid_t
id|guid
suffix:semicolon
DECL|member|table
r_int
r_int
id|table
suffix:semicolon
DECL|typedef|efi_config_table_t
)brace
id|efi_config_table_t
suffix:semicolon
DECL|macro|EFI_SYSTEM_TABLE_SIGNATURE
mdefine_line|#define EFI_SYSTEM_TABLE_SIGNATURE 0x5453595320494249
DECL|macro|EFI_SYSTEM_TABLE_REVISION
mdefine_line|#define EFI_SYSTEM_TABLE_REVISION  ((1 &lt;&lt; 16) | 00)
r_typedef
r_struct
(brace
DECL|member|hdr
id|efi_table_hdr_t
id|hdr
suffix:semicolon
DECL|member|fw_vendor
r_int
r_int
id|fw_vendor
suffix:semicolon
multiline_comment|/* physical addr of CHAR16 vendor string */
DECL|member|fw_revision
id|u32
id|fw_revision
suffix:semicolon
DECL|member|con_in_handle
r_int
r_int
id|con_in_handle
suffix:semicolon
DECL|member|con_in
r_int
r_int
id|con_in
suffix:semicolon
DECL|member|con_out_handle
r_int
r_int
id|con_out_handle
suffix:semicolon
DECL|member|con_out
r_int
r_int
id|con_out
suffix:semicolon
DECL|member|stderr_handle
r_int
r_int
id|stderr_handle
suffix:semicolon
DECL|member|stderr
r_int
r_int
id|stderr
suffix:semicolon
DECL|member|runtime
id|efi_runtime_services_t
op_star
id|runtime
suffix:semicolon
DECL|member|boottime
r_int
r_int
id|boottime
suffix:semicolon
DECL|member|nr_tables
r_int
r_int
id|nr_tables
suffix:semicolon
DECL|member|tables
r_int
r_int
id|tables
suffix:semicolon
DECL|typedef|efi_system_table_t
)brace
id|efi_system_table_t
suffix:semicolon
multiline_comment|/*&n; * All runtime access to EFI goes through this structure:&n; */
DECL|struct|efi
r_extern
r_struct
id|efi
(brace
DECL|member|systab
id|efi_system_table_t
op_star
id|systab
suffix:semicolon
multiline_comment|/* EFI system table */
DECL|member|mps
r_void
op_star
id|mps
suffix:semicolon
multiline_comment|/* MPS table */
DECL|member|acpi
r_void
op_star
id|acpi
suffix:semicolon
multiline_comment|/* ACPI table  (IA64 ext 0.71) */
DECL|member|acpi20
r_void
op_star
id|acpi20
suffix:semicolon
multiline_comment|/* ACPI table  (ACPI 2.0) */
DECL|member|smbios
r_void
op_star
id|smbios
suffix:semicolon
multiline_comment|/* SM BIOS table */
DECL|member|sal_systab
r_void
op_star
id|sal_systab
suffix:semicolon
multiline_comment|/* SAL system table */
DECL|member|boot_info
r_void
op_star
id|boot_info
suffix:semicolon
multiline_comment|/* boot info table */
DECL|member|hcdp
r_void
op_star
id|hcdp
suffix:semicolon
multiline_comment|/* HCDP table */
DECL|member|get_time
id|efi_get_time_t
op_star
id|get_time
suffix:semicolon
DECL|member|set_time
id|efi_set_time_t
op_star
id|set_time
suffix:semicolon
DECL|member|get_wakeup_time
id|efi_get_wakeup_time_t
op_star
id|get_wakeup_time
suffix:semicolon
DECL|member|set_wakeup_time
id|efi_set_wakeup_time_t
op_star
id|set_wakeup_time
suffix:semicolon
DECL|member|get_variable
id|efi_get_variable_t
op_star
id|get_variable
suffix:semicolon
DECL|member|get_next_variable
id|efi_get_next_variable_t
op_star
id|get_next_variable
suffix:semicolon
DECL|member|set_variable
id|efi_set_variable_t
op_star
id|set_variable
suffix:semicolon
DECL|member|get_next_high_mono_count
id|efi_get_next_high_mono_count_t
op_star
id|get_next_high_mono_count
suffix:semicolon
DECL|member|reset_system
id|efi_reset_system_t
op_star
id|reset_system
suffix:semicolon
)brace
id|efi
suffix:semicolon
r_static
r_inline
r_int
DECL|function|efi_guidcmp
id|efi_guidcmp
(paren
id|efi_guid_t
id|left
comma
id|efi_guid_t
id|right
)paren
(brace
r_return
id|memcmp
c_func
(paren
op_amp
id|left
comma
op_amp
id|right
comma
r_sizeof
(paren
id|efi_guid_t
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_char
op_star
DECL|function|efi_guid_unparse
id|efi_guid_unparse
c_func
(paren
id|efi_guid_t
op_star
id|guid
comma
r_char
op_star
id|out
)paren
(brace
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x&quot;
comma
id|guid-&gt;b
(braket
l_int|3
)braket
comma
id|guid-&gt;b
(braket
l_int|2
)braket
comma
id|guid-&gt;b
(braket
l_int|1
)braket
comma
id|guid-&gt;b
(braket
l_int|0
)braket
comma
id|guid-&gt;b
(braket
l_int|5
)braket
comma
id|guid-&gt;b
(braket
l_int|4
)braket
comma
id|guid-&gt;b
(braket
l_int|7
)braket
comma
id|guid-&gt;b
(braket
l_int|6
)braket
comma
id|guid-&gt;b
(braket
l_int|8
)braket
comma
id|guid-&gt;b
(braket
l_int|9
)braket
comma
id|guid-&gt;b
(braket
l_int|10
)braket
comma
id|guid-&gt;b
(braket
l_int|11
)braket
comma
id|guid-&gt;b
(braket
l_int|12
)braket
comma
id|guid-&gt;b
(braket
l_int|13
)braket
comma
id|guid-&gt;b
(braket
l_int|14
)braket
comma
id|guid-&gt;b
(braket
l_int|15
)braket
)paren
suffix:semicolon
r_return
id|out
suffix:semicolon
)brace
r_extern
r_void
id|efi_init
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|efi_map_pal_code
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|efi_memmap_walk
(paren
id|efi_freemem_callback_t
id|callback
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_void
id|efi_gettimeofday
(paren
r_struct
id|timespec
op_star
id|ts
)paren
suffix:semicolon
r_extern
r_void
id|efi_enter_virtual_mode
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* switch EFI to virtual mode, if possible */
r_extern
id|u64
id|efi_get_iobase
(paren
r_void
)paren
suffix:semicolon
r_extern
id|u32
id|efi_mem_type
(paren
r_int
r_int
id|phys_addr
)paren
suffix:semicolon
r_extern
id|u64
id|efi_mem_attributes
(paren
r_int
r_int
id|phys_addr
)paren
suffix:semicolon
multiline_comment|/*&n; * Variable Attributes&n; */
DECL|macro|EFI_VARIABLE_NON_VOLATILE
mdefine_line|#define EFI_VARIABLE_NON_VOLATILE       0x0000000000000001
DECL|macro|EFI_VARIABLE_BOOTSERVICE_ACCESS
mdefine_line|#define EFI_VARIABLE_BOOTSERVICE_ACCESS 0x0000000000000002
DECL|macro|EFI_VARIABLE_RUNTIME_ACCESS
mdefine_line|#define EFI_VARIABLE_RUNTIME_ACCESS     0x0000000000000004
multiline_comment|/*&n; * efi_dir is allocated in arch/ia64/kernel/efi.c.&n; */
macro_line|#ifdef CONFIG_PROC_FS
r_extern
r_struct
id|proc_dir_entry
op_star
id|efi_dir
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _LINUX_EFI_H */
eof
