multiline_comment|/******************************************************************************&n; *&n; * Name: acpiosxf.h - All interfaces to the OS Services Layer (OSL).  These&n; *                    interfaces must be implemented by OSL to interface the&n; *                    ACPI components to the host operating system.&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ACPIOSXF_H__
DECL|macro|__ACPIOSXF_H__
mdefine_line|#define __ACPIOSXF_H__
macro_line|#include &quot;platform/acenv.h&quot;
macro_line|#include &quot;actypes.h&quot;
multiline_comment|/* Priorities for Acpi_os_queue_for_execution */
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
multiline_comment|/*&n; * Types specific to the OS service interfaces&n; */
r_typedef
DECL|typedef|OSD_HANDLER
id|u32
(paren
op_star
id|OSD_HANDLER
)paren
(paren
r_void
op_star
id|context
)paren
suffix:semicolon
r_typedef
DECL|typedef|OSD_EXECUTION_CALLBACK
r_void
(paren
op_star
id|OSD_EXECUTION_CALLBACK
)paren
(paren
r_void
op_star
id|context
)paren
suffix:semicolon
multiline_comment|/*&n; * OSL Initialization and shutdown primitives&n; */
id|ACPI_STATUS
id|acpi_os_initialize
(paren
r_void
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_os_terminate
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Synchronization primitives&n; */
id|ACPI_STATUS
id|acpi_os_create_semaphore
(paren
id|u32
id|max_units
comma
id|u32
id|initial_units
comma
id|ACPI_HANDLE
op_star
id|out_handle
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_os_delete_semaphore
(paren
id|ACPI_HANDLE
id|handle
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_os_wait_semaphore
(paren
id|ACPI_HANDLE
id|handle
comma
id|u32
id|units
comma
id|u32
id|timeout
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_os_signal_semaphore
(paren
id|ACPI_HANDLE
id|handle
comma
id|u32
id|units
)paren
suffix:semicolon
multiline_comment|/*&n; * Memory allocation and mapping&n; */
r_void
op_star
id|acpi_os_allocate
(paren
id|u32
id|size
)paren
suffix:semicolon
r_void
op_star
id|acpi_os_callocate
(paren
id|u32
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
id|ACPI_STATUS
id|acpi_os_map_memory
(paren
id|ACPI_PHYSICAL_ADDRESS
id|physical_address
comma
id|u32
id|length
comma
r_void
op_star
op_star
id|logical_address
)paren
suffix:semicolon
r_void
id|acpi_os_unmap_memory
(paren
r_void
op_star
id|logical_address
comma
id|u32
id|length
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_os_get_physical_address
(paren
r_void
op_star
id|logical_address
comma
id|ACPI_PHYSICAL_ADDRESS
op_star
id|physical_address
)paren
suffix:semicolon
multiline_comment|/*&n; * Interrupt handlers&n; */
id|ACPI_STATUS
id|acpi_os_install_interrupt_handler
(paren
id|u32
id|interrupt_number
comma
id|OSD_HANDLER
id|service_routine
comma
r_void
op_star
id|context
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_os_remove_interrupt_handler
(paren
id|u32
id|interrupt_number
comma
id|OSD_HANDLER
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
id|ACPI_STATUS
id|acpi_os_queue_for_execution
(paren
id|u32
id|priority
comma
id|OSD_EXECUTION_CALLBACK
id|function
comma
r_void
op_star
id|context
)paren
suffix:semicolon
r_void
id|acpi_os_sleep
(paren
id|u32
id|seconds
comma
id|u32
id|milliseconds
)paren
suffix:semicolon
r_void
id|acpi_os_sleep_usec
(paren
id|u32
id|microseconds
)paren
suffix:semicolon
multiline_comment|/*&n; * Platform/Hardware independent I/O interfaces&n; */
id|u8
id|acpi_os_in8
(paren
id|ACPI_IO_ADDRESS
id|in_port
)paren
suffix:semicolon
id|u16
id|acpi_os_in16
(paren
id|ACPI_IO_ADDRESS
id|in_port
)paren
suffix:semicolon
id|u32
id|acpi_os_in32
(paren
id|ACPI_IO_ADDRESS
id|in_port
)paren
suffix:semicolon
r_void
id|acpi_os_out8
(paren
id|ACPI_IO_ADDRESS
id|out_port
comma
id|u8
id|value
)paren
suffix:semicolon
r_void
id|acpi_os_out16
(paren
id|ACPI_IO_ADDRESS
id|out_port
comma
id|u16
id|value
)paren
suffix:semicolon
r_void
id|acpi_os_out32
(paren
id|ACPI_IO_ADDRESS
id|out_port
comma
id|u32
id|value
)paren
suffix:semicolon
multiline_comment|/*&n; * Platform/Hardware independent physical memory interfaces&n; */
id|u8
id|acpi_os_mem_in8
(paren
id|ACPI_PHYSICAL_ADDRESS
id|in_addr
)paren
suffix:semicolon
id|u16
id|acpi_os_mem_in16
(paren
id|ACPI_PHYSICAL_ADDRESS
id|in_addr
)paren
suffix:semicolon
id|u32
id|acpi_os_mem_in32
(paren
id|ACPI_PHYSICAL_ADDRESS
id|in_addr
)paren
suffix:semicolon
r_void
id|acpi_os_mem_out8
(paren
id|ACPI_PHYSICAL_ADDRESS
id|out_addr
comma
id|u8
id|value
)paren
suffix:semicolon
r_void
id|acpi_os_mem_out16
(paren
id|ACPI_PHYSICAL_ADDRESS
id|out_addr
comma
id|u16
id|value
)paren
suffix:semicolon
r_void
id|acpi_os_mem_out32
(paren
id|ACPI_PHYSICAL_ADDRESS
id|out_addr
comma
id|u32
id|value
)paren
suffix:semicolon
multiline_comment|/*&n; * Standard access to PCI configuration space&n; */
id|ACPI_STATUS
id|acpi_os_read_pci_cfg_byte
(paren
id|u32
id|bus
comma
id|u32
id|device_function
comma
id|u32
r_register
comma
id|u8
op_star
id|value
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_os_read_pci_cfg_word
(paren
id|u32
id|bus
comma
id|u32
id|device_function
comma
id|u32
r_register
comma
id|u16
op_star
id|value
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_os_read_pci_cfg_dword
(paren
id|u32
id|bus
comma
id|u32
id|device_function
comma
id|u32
r_register
comma
id|u32
op_star
id|value
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_os_write_pci_cfg_byte
(paren
id|u32
id|bus
comma
id|u32
id|device_function
comma
id|u32
r_register
comma
id|u8
id|value
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_os_write_pci_cfg_word
(paren
id|u32
id|bus
comma
id|u32
id|device_function
comma
id|u32
r_register
comma
id|u16
id|value
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_os_write_pci_cfg_dword
(paren
id|u32
id|bus
comma
id|u32
id|device_function
comma
id|u32
r_register
comma
id|u32
id|value
)paren
suffix:semicolon
multiline_comment|/*&n; * Miscellaneous&n; */
id|ACPI_STATUS
id|acpi_os_breakpoint
(paren
id|NATIVE_CHAR
op_star
id|message
)paren
suffix:semicolon
id|u8
id|acpi_os_readable
(paren
r_void
op_star
id|pointer
comma
id|u32
id|length
)paren
suffix:semicolon
id|u8
id|acpi_os_writable
(paren
r_void
op_star
id|pointer
comma
id|u32
id|length
)paren
suffix:semicolon
id|u32
id|acpi_os_get_timer
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Debug print routines&n; */
id|s32
id|acpi_os_printf
(paren
r_const
id|NATIVE_CHAR
op_star
id|format
comma
dot
dot
dot
)paren
suffix:semicolon
id|s32
id|acpi_os_vprintf
(paren
r_const
id|NATIVE_CHAR
op_star
id|format
comma
id|va_list
id|args
)paren
suffix:semicolon
multiline_comment|/*&n; * Debug input&n; */
id|u32
id|acpi_os_get_line
(paren
id|NATIVE_CHAR
op_star
id|buffer
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
id|NATIVE_CHAR
op_star
id|message
)paren
suffix:semicolon
macro_line|#endif /* __ACPIOSXF_H__ */
eof
