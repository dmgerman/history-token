multiline_comment|/******************************************************************************&n; *&n; * Module Name: exregion - ACPI default Op_region (address space) handlers&n; *              $Revision: 61 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acinterp.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;achware.h&quot;
macro_line|#include &quot;acevents.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EXECUTER
id|MODULE_NAME
(paren
l_string|&quot;exregion&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_system_memory_space_handler&n; *&n; * PARAMETERS:  Function            - Read or Write operation&n; *              Address             - Where in the space to read or write&n; *              Bit_width           - Field width in bits (8, 16, or 32)&n; *              Value               - Pointer to in or out value&n; *              Handler_context     - Pointer to Handler&squot;s context&n; *              Region_context      - Pointer to context specific to the&n; *                                    accessed region&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Handler for the System Memory address space (Op Region)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_system_memory_space_handler
id|acpi_ex_system_memory_space_handler
(paren
id|u32
id|function
comma
id|ACPI_PHYSICAL_ADDRESS
id|address
comma
id|u32
id|bit_width
comma
id|u32
op_star
id|value
comma
r_void
op_star
id|handler_context
comma
r_void
op_star
id|region_context
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_void
op_star
id|logical_addr_ptr
op_assign
l_int|NULL
suffix:semicolon
id|acpi_mem_space_context
op_star
id|mem_info
op_assign
id|region_context
suffix:semicolon
id|u32
id|length
suffix:semicolon
id|FUNCTION_TRACE
(paren
l_string|&quot;Ex_system_memory_space_handler&quot;
)paren
suffix:semicolon
multiline_comment|/* Validate and translate the bit width */
r_switch
c_cond
(paren
id|bit_width
)paren
(brace
r_case
l_int|8
suffix:colon
id|length
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|length
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
id|length
op_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid System_memory width %d&bslash;n&quot;
comma
id|bit_width
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_OPERAND_VALUE
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Does the request fit into the cached memory mapping?&n;&t; * Is 1) Address below the current mapping? OR&n;&t; *    2) Address beyond the current mapping?&n;&t; */
r_if
c_cond
(paren
(paren
id|address
OL
id|mem_info-&gt;mapped_physical_address
)paren
op_logical_or
(paren
(paren
(paren
id|acpi_integer
)paren
id|address
op_plus
id|length
)paren
OG
(paren
(paren
id|acpi_integer
)paren
id|mem_info-&gt;mapped_physical_address
op_plus
id|mem_info-&gt;mapped_length
)paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * The request cannot be resolved by the current memory mapping;&n;&t;&t; * Delete the existing mapping and create a new one.&n;&t;&t; */
r_if
c_cond
(paren
id|mem_info-&gt;mapped_length
)paren
(brace
multiline_comment|/* Valid mapping, delete it */
id|acpi_os_unmap_memory
(paren
id|mem_info-&gt;mapped_logical_address
comma
id|mem_info-&gt;mapped_length
)paren
suffix:semicolon
)brace
id|mem_info-&gt;mapped_length
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* In case of failure below */
multiline_comment|/* Create a new mapping starting at the address given */
id|status
op_assign
id|acpi_os_map_memory
(paren
id|address
comma
id|SYSMEM_REGION_WINDOW_SIZE
comma
(paren
r_void
op_star
op_star
)paren
op_amp
id|mem_info-&gt;mapped_logical_address
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Save the physical address and mapping size */
id|mem_info-&gt;mapped_physical_address
op_assign
id|address
suffix:semicolon
id|mem_info-&gt;mapped_length
op_assign
id|SYSMEM_REGION_WINDOW_SIZE
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Generate a logical pointer corresponding to the address we want to&n;&t; * access&n;&t; */
multiline_comment|/* TBD: should these pointers go to 64-bit in all cases ? */
id|logical_addr_ptr
op_assign
id|mem_info-&gt;mapped_logical_address
op_plus
(paren
(paren
id|acpi_integer
)paren
id|address
op_minus
(paren
id|acpi_integer
)paren
id|mem_info-&gt;mapped_physical_address
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;System_memory %d (%d width) Address=%8.8X%8.8X&bslash;n&quot;
comma
id|function
comma
id|bit_width
comma
id|HIDWORD
(paren
id|address
)paren
comma
id|LODWORD
(paren
id|address
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Perform the memory read or write */
r_switch
c_cond
(paren
id|function
)paren
(brace
r_case
id|ACPI_READ_ADR_SPACE
suffix:colon
r_switch
c_cond
(paren
id|bit_width
)paren
(brace
r_case
l_int|8
suffix:colon
op_star
id|value
op_assign
(paren
id|u32
)paren
op_star
(paren
id|u8
op_star
)paren
id|logical_addr_ptr
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|MOVE_UNALIGNED16_TO_32
(paren
id|value
comma
id|logical_addr_ptr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
id|MOVE_UNALIGNED32_TO_32
(paren
id|value
comma
id|logical_addr_ptr
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_WRITE_ADR_SPACE
suffix:colon
r_switch
c_cond
(paren
id|bit_width
)paren
(brace
r_case
l_int|8
suffix:colon
op_star
(paren
id|u8
op_star
)paren
id|logical_addr_ptr
op_assign
(paren
id|u8
)paren
op_star
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|MOVE_UNALIGNED16_TO_16
(paren
id|logical_addr_ptr
comma
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
id|MOVE_UNALIGNED32_TO_32
(paren
id|logical_addr_ptr
comma
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|status
op_assign
id|AE_BAD_PARAMETER
suffix:semicolon
r_break
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_system_io_space_handler&n; *&n; * PARAMETERS:  Function            - Read or Write operation&n; *              Address             - Where in the space to read or write&n; *              Bit_width           - Field width in bits (8, 16, or 32)&n; *              Value               - Pointer to in or out value&n; *              Handler_context     - Pointer to Handler&squot;s context&n; *              Region_context      - Pointer to context specific to the&n; *                                    accessed region&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Handler for the System IO address space (Op Region)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_system_io_space_handler
id|acpi_ex_system_io_space_handler
(paren
id|u32
id|function
comma
id|ACPI_PHYSICAL_ADDRESS
id|address
comma
id|u32
id|bit_width
comma
id|u32
op_star
id|value
comma
r_void
op_star
id|handler_context
comma
r_void
op_star
id|region_context
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|FUNCTION_TRACE
(paren
l_string|&quot;Ex_system_io_space_handler&quot;
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;System_iO %d (%d width) Address=%8.8X%8.8X&bslash;n&quot;
comma
id|function
comma
id|bit_width
comma
id|HIDWORD
(paren
id|address
)paren
comma
id|LODWORD
(paren
id|address
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Decode the function parameter */
r_switch
c_cond
(paren
id|function
)paren
(brace
r_case
id|ACPI_READ_ADR_SPACE
suffix:colon
op_star
id|value
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
id|acpi_os_read_port
(paren
(paren
id|ACPI_IO_ADDRESS
)paren
id|address
comma
id|value
comma
id|bit_width
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_WRITE_ADR_SPACE
suffix:colon
id|status
op_assign
id|acpi_os_write_port
(paren
(paren
id|ACPI_IO_ADDRESS
)paren
id|address
comma
op_star
id|value
comma
id|bit_width
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|status
op_assign
id|AE_BAD_PARAMETER
suffix:semicolon
r_break
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_pci_config_space_handler&n; *&n; * PARAMETERS:  Function            - Read or Write operation&n; *              Address             - Where in the space to read or write&n; *              Bit_width           - Field width in bits (8, 16, or 32)&n; *              Value               - Pointer to in or out value&n; *              Handler_context     - Pointer to Handler&squot;s context&n; *              Region_context      - Pointer to context specific to the&n; *                                    accessed region&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Handler for the PCI Config address space (Op Region)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_pci_config_space_handler
id|acpi_ex_pci_config_space_handler
(paren
id|u32
id|function
comma
id|ACPI_PHYSICAL_ADDRESS
id|address
comma
id|u32
id|bit_width
comma
id|u32
op_star
id|value
comma
r_void
op_star
id|handler_context
comma
r_void
op_star
id|region_context
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|acpi_pci_id
op_star
id|pci_id
suffix:semicolon
id|u16
id|pci_register
suffix:semicolon
id|FUNCTION_TRACE
(paren
l_string|&quot;Ex_pci_config_space_handler&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *  The arguments to Acpi_os(Read|Write)Pci_cfg(Byte|Word|Dword) are:&n;&t; *&n;&t; *  Pci_segment is the PCI bus segment range 0-31&n;&t; *  Pci_bus     is the PCI bus number range 0-255&n;&t; *  Pci_device  is the PCI device number range 0-31&n;&t; *  Pci_function is the PCI device function number&n;&t; *  Pci_register is the Config space register range 0-255 bytes&n;&t; *&n;&t; *  Value - input value for write, output address for read&n;&t; *&n;&t; */
id|pci_id
op_assign
(paren
id|acpi_pci_id
op_star
)paren
id|region_context
suffix:semicolon
id|pci_register
op_assign
(paren
id|u16
)paren
id|address
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Pci_config %d (%d) Seg(%04x) Bus(%04x) Dev(%04x) Func(%04x) Reg(%04x)&bslash;n&quot;
comma
id|function
comma
id|bit_width
comma
id|pci_id-&gt;segment
comma
id|pci_id-&gt;bus
comma
id|pci_id-&gt;device
comma
id|pci_id-&gt;function
comma
id|pci_register
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|function
)paren
(brace
r_case
id|ACPI_READ_ADR_SPACE
suffix:colon
op_star
id|value
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
id|acpi_os_read_pci_configuration
(paren
id|pci_id
comma
id|pci_register
comma
id|value
comma
id|bit_width
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_WRITE_ADR_SPACE
suffix:colon
id|status
op_assign
id|acpi_os_write_pci_configuration
(paren
id|pci_id
comma
id|pci_register
comma
op_star
id|value
comma
id|bit_width
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|status
op_assign
id|AE_BAD_PARAMETER
suffix:semicolon
r_break
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_cmos_space_handler&n; *&n; * PARAMETERS:  Function            - Read or Write operation&n; *              Address             - Where in the space to read or write&n; *              Bit_width           - Field width in bits (8, 16, or 32)&n; *              Value               - Pointer to in or out value&n; *              Handler_context     - Pointer to Handler&squot;s context&n; *              Region_context      - Pointer to context specific to the&n; *                                    accessed region&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Handler for the CMOS address space (Op Region)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_cmos_space_handler
id|acpi_ex_cmos_space_handler
(paren
id|u32
id|function
comma
id|ACPI_PHYSICAL_ADDRESS
id|address
comma
id|u32
id|bit_width
comma
id|u32
op_star
id|value
comma
r_void
op_star
id|handler_context
comma
r_void
op_star
id|region_context
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|FUNCTION_TRACE
(paren
l_string|&quot;Ex_cmos_space_handler&quot;
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_pci_bar_space_handler&n; *&n; * PARAMETERS:  Function            - Read or Write operation&n; *              Address             - Where in the space to read or write&n; *              Bit_width           - Field width in bits (8, 16, or 32)&n; *              Value               - Pointer to in or out value&n; *              Handler_context     - Pointer to Handler&squot;s context&n; *              Region_context      - Pointer to context specific to the&n; *                                    accessed region&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Handler for the PCI Bar_target address space (Op Region)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_pci_bar_space_handler
id|acpi_ex_pci_bar_space_handler
(paren
id|u32
id|function
comma
id|ACPI_PHYSICAL_ADDRESS
id|address
comma
id|u32
id|bit_width
comma
id|u32
op_star
id|value
comma
r_void
op_star
id|handler_context
comma
r_void
op_star
id|region_context
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|FUNCTION_TRACE
(paren
l_string|&quot;Ex_pci_bar_space_handler&quot;
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
