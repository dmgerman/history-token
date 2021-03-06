multiline_comment|/******************************************************************************&n; *&n; * Name: acpiosxf.h - All interfaces to the OS Services Layer (OSL).  These&n; *                    interfaces must be implemented by OSL to interface the&n; *                    ACPI components to the host operating system.&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2005, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#ifndef __ACPIOSXF_H__
DECL|macro|__ACPIOSXF_H__
mdefine_line|#define __ACPIOSXF_H__
macro_line|#include &quot;platform/acenv.h&quot;
macro_line|#include &quot;actypes.h&quot;
multiline_comment|/* Priorities for acpi_os_queue_for_execution */
DECL|macro|OSD_PRIORITY_GPE
mdefine_line|#define OSD_PRIORITY_GPE            1
DECL|macro|OSD_PRIORITY_HIGH
mdefine_line|#define OSD_PRIORITY_HIGH           2
DECL|macro|OSD_PRIORITY_MED
mdefine_line|#define OSD_PRIORITY_MED            3
DECL|macro|OSD_PRIORITY_LO
mdefine_line|#define OSD_PRIORITY_LO             4
DECL|macro|ACPI_NO_UNIT_LIMIT
mdefine_line|#define ACPI_NO_UNIT_LIMIT          ((u32) -1)
DECL|macro|ACPI_MUTEX_SEM
mdefine_line|#define ACPI_MUTEX_SEM              1
multiline_comment|/* Functions for acpi_os_signal */
DECL|macro|ACPI_SIGNAL_FATAL
mdefine_line|#define ACPI_SIGNAL_FATAL           0
DECL|macro|ACPI_SIGNAL_BREAKPOINT
mdefine_line|#define ACPI_SIGNAL_BREAKPOINT      1
DECL|struct|acpi_signal_fatal_info
r_struct
id|acpi_signal_fatal_info
(brace
DECL|member|type
id|u32
id|type
suffix:semicolon
DECL|member|code
id|u32
id|code
suffix:semicolon
DECL|member|argument
id|u32
id|argument
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * OSL Initialization and shutdown primitives&n; */
id|acpi_status
id|acpi_os_initialize
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_os_terminate
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * ACPI Table interfaces&n; */
id|acpi_status
id|acpi_os_get_root_pointer
(paren
id|u32
id|flags
comma
r_struct
id|acpi_pointer
op_star
id|address
)paren
suffix:semicolon
id|acpi_status
id|acpi_os_predefined_override
(paren
r_const
r_struct
id|acpi_predefined_names
op_star
id|init_val
comma
id|acpi_string
op_star
id|new_val
)paren
suffix:semicolon
id|acpi_status
id|acpi_os_table_override
(paren
r_struct
id|acpi_table_header
op_star
id|existing_table
comma
r_struct
id|acpi_table_header
op_star
op_star
id|new_table
)paren
suffix:semicolon
multiline_comment|/*&n; * Synchronization primitives&n; */
id|acpi_status
id|acpi_os_create_semaphore
(paren
id|u32
id|max_units
comma
id|u32
id|initial_units
comma
id|acpi_handle
op_star
id|out_handle
)paren
suffix:semicolon
id|acpi_status
id|acpi_os_delete_semaphore
(paren
id|acpi_handle
id|handle
)paren
suffix:semicolon
id|acpi_status
id|acpi_os_wait_semaphore
(paren
id|acpi_handle
id|handle
comma
id|u32
id|units
comma
id|u16
id|timeout
)paren
suffix:semicolon
id|acpi_status
id|acpi_os_signal_semaphore
(paren
id|acpi_handle
id|handle
comma
id|u32
id|units
)paren
suffix:semicolon
id|acpi_status
id|acpi_os_create_lock
(paren
id|acpi_handle
op_star
id|out_handle
)paren
suffix:semicolon
r_void
id|acpi_os_delete_lock
(paren
id|acpi_handle
id|handle
)paren
suffix:semicolon
r_void
id|acpi_os_acquire_lock
(paren
id|acpi_handle
id|handle
comma
id|u32
id|flags
)paren
suffix:semicolon
r_void
id|acpi_os_release_lock
(paren
id|acpi_handle
id|handle
comma
id|u32
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n; * Memory allocation and mapping&n; */
r_void
op_star
id|acpi_os_allocate
(paren
id|acpi_size
id|size
)paren
suffix:semicolon
r_void
id|acpi_os_free
(paren
r_void
op_star
id|memory
)paren
suffix:semicolon
id|acpi_status
id|acpi_os_map_memory
(paren
id|acpi_physical_address
id|physical_address
comma
id|acpi_size
id|size
comma
r_void
id|__iomem
op_star
op_star
id|logical_address
)paren
suffix:semicolon
r_void
id|acpi_os_unmap_memory
(paren
r_void
id|__iomem
op_star
id|logical_address
comma
id|acpi_size
id|size
)paren
suffix:semicolon
macro_line|#ifdef ACPI_FUTURE_USAGE
id|acpi_status
id|acpi_os_get_physical_address
(paren
r_void
op_star
id|logical_address
comma
id|acpi_physical_address
op_star
id|physical_address
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Interrupt handlers&n; */
id|acpi_status
id|acpi_os_install_interrupt_handler
(paren
id|u32
id|gsi
comma
id|acpi_osd_handler
id|service_routine
comma
r_void
op_star
id|context
)paren
suffix:semicolon
id|acpi_status
id|acpi_os_remove_interrupt_handler
(paren
id|u32
id|gsi
comma
id|acpi_osd_handler
id|service_routine
)paren
suffix:semicolon
multiline_comment|/*&n; * Threads and Scheduling&n; */
id|u32
id|acpi_os_get_thread_id
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_os_queue_for_execution
(paren
id|u32
id|priority
comma
id|acpi_osd_exec_callback
id|function
comma
r_void
op_star
id|context
)paren
suffix:semicolon
r_void
id|acpi_os_wait_events_complete
c_func
(paren
r_void
op_star
id|context
)paren
suffix:semicolon
r_void
id|acpi_os_wait_events_complete
(paren
r_void
op_star
id|context
)paren
suffix:semicolon
r_void
id|acpi_os_sleep
(paren
id|acpi_integer
id|milliseconds
)paren
suffix:semicolon
r_void
id|acpi_os_stall
(paren
id|u32
id|microseconds
)paren
suffix:semicolon
multiline_comment|/*&n; * Platform and hardware-independent I/O interfaces&n; */
id|acpi_status
id|acpi_os_read_port
(paren
id|acpi_io_address
id|address
comma
id|u32
op_star
id|value
comma
id|u32
id|width
)paren
suffix:semicolon
id|acpi_status
id|acpi_os_write_port
(paren
id|acpi_io_address
id|address
comma
id|u32
id|value
comma
id|u32
id|width
)paren
suffix:semicolon
multiline_comment|/*&n; * Platform and hardware-independent physical memory interfaces&n; */
id|acpi_status
id|acpi_os_read_memory
(paren
id|acpi_physical_address
id|address
comma
id|u32
op_star
id|value
comma
id|u32
id|width
)paren
suffix:semicolon
id|acpi_status
id|acpi_os_write_memory
(paren
id|acpi_physical_address
id|address
comma
id|u32
id|value
comma
id|u32
id|width
)paren
suffix:semicolon
multiline_comment|/*&n; * Platform and hardware-independent PCI configuration space access&n; * Note: Can&squot;t use &quot;Register&quot; as a parameter, changed to &quot;Reg&quot; --&n; * certain compilers complain.&n; */
id|acpi_status
id|acpi_os_read_pci_configuration
(paren
r_struct
id|acpi_pci_id
op_star
id|pci_id
comma
id|u32
id|reg
comma
r_void
op_star
id|value
comma
id|u32
id|width
)paren
suffix:semicolon
id|acpi_status
id|acpi_os_write_pci_configuration
(paren
r_struct
id|acpi_pci_id
op_star
id|pci_id
comma
id|u32
id|reg
comma
id|acpi_integer
id|value
comma
id|u32
id|width
)paren
suffix:semicolon
multiline_comment|/*&n; * Interim function needed for PCI IRQ routing&n; */
r_void
id|acpi_os_derive_pci_id
c_func
(paren
id|acpi_handle
id|rhandle
comma
id|acpi_handle
id|chandle
comma
r_struct
id|acpi_pci_id
op_star
op_star
id|pci_id
)paren
suffix:semicolon
multiline_comment|/*&n; * Miscellaneous&n; */
id|u8
id|acpi_os_readable
(paren
r_void
op_star
id|pointer
comma
id|acpi_size
id|length
)paren
suffix:semicolon
macro_line|#ifdef ACPI_FUTURE_USAGE
id|u8
id|acpi_os_writable
(paren
r_void
op_star
id|pointer
comma
id|acpi_size
id|length
)paren
suffix:semicolon
macro_line|#endif
id|u64
id|acpi_os_get_timer
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_os_signal
(paren
id|u32
id|function
comma
r_void
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/*&n; * Debug print routines&n; */
r_void
id|ACPI_INTERNAL_VAR_XFACE
id|acpi_os_printf
(paren
r_const
r_char
op_star
id|format
comma
dot
dot
dot
)paren
suffix:semicolon
r_void
id|acpi_os_vprintf
(paren
r_const
r_char
op_star
id|format
comma
id|va_list
id|args
)paren
suffix:semicolon
r_void
id|acpi_os_redirect_output
(paren
r_void
op_star
id|destination
)paren
suffix:semicolon
multiline_comment|/*&n; * Debug input&n; */
macro_line|#ifdef ACPI_FUTURE_USAGE
id|u32
id|acpi_os_get_line
(paren
r_char
op_star
id|buffer
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Directory manipulation&n; */
r_void
op_star
id|acpi_os_open_directory
(paren
r_char
op_star
id|pathname
comma
r_char
op_star
id|wildcard_spec
comma
r_char
id|requested_file_type
)paren
suffix:semicolon
multiline_comment|/* requeste_file_type values */
DECL|macro|REQUEST_FILE_ONLY
mdefine_line|#define REQUEST_FILE_ONLY                   0
DECL|macro|REQUEST_DIR_ONLY
mdefine_line|#define REQUEST_DIR_ONLY                    1
r_char
op_star
id|acpi_os_get_next_filename
(paren
r_void
op_star
id|dir_handle
)paren
suffix:semicolon
r_void
id|acpi_os_close_directory
(paren
r_void
op_star
id|dir_handle
)paren
suffix:semicolon
multiline_comment|/*&n; * Debug&n; */
r_void
id|acpi_os_dbg_assert
c_func
(paren
r_void
op_star
id|failed_assertion
comma
r_void
op_star
id|file_name
comma
id|u32
id|line_number
comma
r_char
op_star
id|message
)paren
suffix:semicolon
macro_line|#endif /* __ACPIOSXF_H__ */
eof
