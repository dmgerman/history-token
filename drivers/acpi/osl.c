multiline_comment|/*&n; *  acpi_osl.c - OS-dependent functions ($Revision: 83 $)&n; *&n; *  Copyright (C) 2000       Andrew Henroid&n; *  Copyright (C) 2001, 2002 Andy Grover &lt;andrew.grover@intel.com&gt;&n; *  Copyright (C) 2001, 2002 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;acpi_bus.h&quot;
macro_line|#include &quot;acpi.h&quot;
macro_line|#ifdef CONFIG_ACPI_EFI
macro_line|#include &lt;linux/efi.h&gt;
id|u64
id|efi_mem_attributes
(paren
id|u64
id|phys_addr
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT&t;&t;ACPI_OS_SERVICES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;osl&quot;
)paren
DECL|macro|PREFIX
mdefine_line|#define PREFIX&t;&t;&quot;ACPI: &quot;
r_typedef
r_struct
(brace
DECL|member|function
id|OSD_EXECUTION_CALLBACK
id|function
suffix:semicolon
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
DECL|typedef|ACPI_OS_DPC
)brace
id|ACPI_OS_DPC
suffix:semicolon
macro_line|#ifdef ENABLE_DEBUGGER
macro_line|#include &lt;linux/kdb.h&gt;
multiline_comment|/* stuff for debugger support */
DECL|variable|acpi_in_debugger
r_int
id|acpi_in_debugger
op_assign
l_int|0
suffix:semicolon
r_extern
id|NATIVE_CHAR
id|line_buf
(braket
l_int|80
)braket
suffix:semicolon
macro_line|#endif /*ENABLE_DEBUGGER*/
DECL|variable|acpi_irq_irq
r_static
r_int
id|acpi_irq_irq
op_assign
l_int|0
suffix:semicolon
DECL|variable|acpi_irq_handler
r_static
id|OSD_HANDLER
id|acpi_irq_handler
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|acpi_irq_context
r_static
r_void
op_star
id|acpi_irq_context
op_assign
l_int|NULL
suffix:semicolon
r_extern
r_struct
id|pci_ops
op_star
id|pci_root_ops
suffix:semicolon
id|acpi_status
DECL|function|acpi_os_initialize
id|acpi_os_initialize
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Initialize PCI configuration space access, as we&squot;ll need to access&n;&t; * it while walking the namespace (bus 0 and root bridges w/ _BBNs).&n;&t; */
macro_line|#ifdef CONFIG_ACPI_PCI
r_if
c_cond
(paren
op_logical_neg
id|pci_root_ops
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Access to PCI configuration space unavailable&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|AE_NULL_ENTRY
suffix:semicolon
)brace
macro_line|#endif
r_return
id|AE_OK
suffix:semicolon
)brace
id|acpi_status
DECL|function|acpi_os_terminate
id|acpi_os_terminate
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|acpi_irq_handler
)paren
(brace
id|acpi_os_remove_interrupt_handler
c_func
(paren
id|acpi_irq_irq
comma
id|acpi_irq_handler
)paren
suffix:semicolon
)brace
r_return
id|AE_OK
suffix:semicolon
)brace
r_void
DECL|function|acpi_os_printf
id|acpi_os_printf
c_func
(paren
r_const
id|NATIVE_CHAR
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|acpi_os_vprintf
c_func
(paren
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
)brace
r_void
DECL|function|acpi_os_vprintf
id|acpi_os_vprintf
c_func
(paren
r_const
id|NATIVE_CHAR
op_star
id|fmt
comma
id|va_list
id|args
)paren
(brace
r_static
r_char
id|buffer
(braket
l_int|512
)braket
suffix:semicolon
id|vsprintf
c_func
(paren
id|buffer
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
macro_line|#ifdef ENABLE_DEBUGGER
r_if
c_cond
(paren
id|acpi_in_debugger
)paren
(brace
id|kdb_printf
c_func
(paren
l_string|&quot;%s&quot;
comma
id|buffer
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|buffer
)paren
suffix:semicolon
)brace
macro_line|#else
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|buffer
)paren
suffix:semicolon
macro_line|#endif
)brace
r_void
op_star
DECL|function|acpi_os_allocate
id|acpi_os_allocate
c_func
(paren
id|ACPI_SIZE
id|size
)paren
(brace
r_return
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
)brace
r_void
DECL|function|acpi_os_free
id|acpi_os_free
c_func
(paren
r_void
op_star
id|ptr
)paren
(brace
id|kfree
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
id|acpi_status
DECL|function|acpi_os_get_root_pointer
id|acpi_os_get_root_pointer
c_func
(paren
id|u32
id|flags
comma
id|ACPI_POINTER
op_star
id|addr
)paren
(brace
macro_line|#ifdef CONFIG_ACPI_EFI
id|addr-&gt;pointer_type
op_assign
id|ACPI_PHYSICAL_POINTER
suffix:semicolon
r_if
c_cond
(paren
id|efi.acpi20
)paren
id|addr-&gt;pointer.physical
op_assign
(paren
id|ACPI_PHYSICAL_ADDRESS
)paren
id|virt_to_phys
c_func
(paren
id|efi.acpi20
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|efi.acpi
)paren
id|addr-&gt;pointer.physical
op_assign
(paren
id|ACPI_PHYSICAL_ADDRESS
)paren
id|virt_to_phys
c_func
(paren
id|efi.acpi
)paren
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;System description tables not found&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|AE_NOT_FOUND
suffix:semicolon
)brace
macro_line|#else
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|acpi_find_root_pointer
c_func
(paren
id|flags
comma
id|addr
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;System description tables not found&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|AE_NOT_FOUND
suffix:semicolon
)brace
macro_line|#endif /*CONFIG_ACPI_EFI*/
r_return
id|AE_OK
suffix:semicolon
)brace
id|acpi_status
DECL|function|acpi_os_map_memory
id|acpi_os_map_memory
c_func
(paren
id|ACPI_PHYSICAL_ADDRESS
id|phys
comma
id|ACPI_SIZE
id|size
comma
r_void
op_star
op_star
id|virt
)paren
(brace
macro_line|#ifdef CONFIG_ACPI_EFI
r_if
c_cond
(paren
id|EFI_MEMORY_WB
op_amp
id|efi_mem_attributes
c_func
(paren
id|phys
)paren
)paren
(brace
op_star
id|virt
op_assign
id|phys_to_virt
c_func
(paren
id|phys
)paren
suffix:semicolon
)brace
r_else
(brace
op_star
id|virt
op_assign
id|ioremap
c_func
(paren
id|phys
comma
id|size
)paren
suffix:semicolon
)brace
macro_line|#else
r_if
c_cond
(paren
id|phys
OG
id|ULONG_MAX
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Cannot map memory that high&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|AE_BAD_PARAMETER
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * ioremap checks to ensure this is in reserved space&n;&t; */
op_star
id|virt
op_assign
id|ioremap
c_func
(paren
(paren
r_int
r_int
)paren
id|phys
comma
id|size
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
op_star
id|virt
)paren
r_return
id|AE_NO_MEMORY
suffix:semicolon
r_return
id|AE_OK
suffix:semicolon
)brace
r_void
DECL|function|acpi_os_unmap_memory
id|acpi_os_unmap_memory
c_func
(paren
r_void
op_star
id|virt
comma
id|ACPI_SIZE
id|size
)paren
(brace
id|iounmap
c_func
(paren
id|virt
)paren
suffix:semicolon
)brace
id|acpi_status
DECL|function|acpi_os_get_physical_address
id|acpi_os_get_physical_address
c_func
(paren
r_void
op_star
id|virt
comma
id|ACPI_PHYSICAL_ADDRESS
op_star
id|phys
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|phys
op_logical_or
op_logical_neg
id|virt
)paren
(brace
r_return
id|AE_BAD_PARAMETER
suffix:semicolon
)brace
op_star
id|phys
op_assign
id|virt_to_phys
c_func
(paren
id|virt
)paren
suffix:semicolon
r_return
id|AE_OK
suffix:semicolon
)brace
id|acpi_status
DECL|function|acpi_os_table_override
id|acpi_os_table_override
(paren
id|acpi_table_header
op_star
id|existing_table
comma
id|acpi_table_header
op_star
op_star
id|new_table
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|existing_table
op_logical_or
op_logical_neg
id|new_table
)paren
r_return
id|AE_BAD_PARAMETER
suffix:semicolon
op_star
id|new_table
op_assign
l_int|NULL
suffix:semicolon
r_return
id|AE_OK
suffix:semicolon
)brace
r_static
r_void
DECL|function|acpi_irq
id|acpi_irq
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
(paren
op_star
id|acpi_irq_handler
)paren
(paren
id|acpi_irq_context
)paren
suffix:semicolon
)brace
id|acpi_status
DECL|function|acpi_os_install_interrupt_handler
id|acpi_os_install_interrupt_handler
c_func
(paren
id|u32
id|irq
comma
id|OSD_HANDLER
id|handler
comma
r_void
op_star
id|context
)paren
(brace
macro_line|#ifdef CONFIG_IA64
id|irq
op_assign
id|gsi_to_vector
c_func
(paren
id|irq
)paren
suffix:semicolon
macro_line|#endif
id|acpi_irq_irq
op_assign
id|irq
suffix:semicolon
id|acpi_irq_handler
op_assign
id|handler
suffix:semicolon
id|acpi_irq_context
op_assign
id|context
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|irq
comma
id|acpi_irq
comma
id|SA_SHIRQ
comma
l_string|&quot;acpi&quot;
comma
id|acpi_irq
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;SCI (IRQ%d) allocation failed&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
id|AE_NOT_ACQUIRED
suffix:semicolon
)brace
r_return
id|AE_OK
suffix:semicolon
)brace
id|acpi_status
DECL|function|acpi_os_remove_interrupt_handler
id|acpi_os_remove_interrupt_handler
c_func
(paren
id|u32
id|irq
comma
id|OSD_HANDLER
id|handler
)paren
(brace
r_if
c_cond
(paren
id|acpi_irq_handler
)paren
(brace
macro_line|#ifdef CONFIG_IA64
id|irq
op_assign
id|gsi_to_vector
c_func
(paren
id|irq
)paren
suffix:semicolon
macro_line|#endif
id|free_irq
c_func
(paren
id|irq
comma
id|acpi_irq
)paren
suffix:semicolon
id|acpi_irq_handler
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|AE_OK
suffix:semicolon
)brace
multiline_comment|/*&n; * Running in interpreter thread context, safe to sleep&n; */
r_void
DECL|function|acpi_os_sleep
id|acpi_os_sleep
c_func
(paren
id|u32
id|sec
comma
id|u32
id|ms
)paren
(brace
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|HZ
op_star
id|sec
op_plus
(paren
id|ms
op_star
id|HZ
)paren
op_div
l_int|1000
)paren
suffix:semicolon
)brace
r_void
DECL|function|acpi_os_stall
id|acpi_os_stall
c_func
(paren
id|u32
id|us
)paren
(brace
r_if
c_cond
(paren
id|us
OG
l_int|10000
)paren
(brace
id|mdelay
c_func
(paren
id|us
op_div
l_int|1000
)paren
suffix:semicolon
)brace
r_else
(brace
id|udelay
c_func
(paren
id|us
)paren
suffix:semicolon
)brace
)brace
id|acpi_status
DECL|function|acpi_os_read_port
id|acpi_os_read_port
c_func
(paren
id|ACPI_IO_ADDRESS
id|port
comma
r_void
op_star
id|value
comma
id|u32
id|width
)paren
(brace
id|u32
id|dummy
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
id|value
op_assign
op_amp
id|dummy
suffix:semicolon
r_switch
c_cond
(paren
id|width
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
id|value
op_assign
id|inb
c_func
(paren
id|port
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
op_star
(paren
id|u16
op_star
)paren
id|value
op_assign
id|inw
c_func
(paren
id|port
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
op_star
(paren
id|u32
op_star
)paren
id|value
op_assign
id|inl
c_func
(paren
id|port
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|AE_OK
suffix:semicolon
)brace
id|acpi_status
DECL|function|acpi_os_write_port
id|acpi_os_write_port
c_func
(paren
id|ACPI_IO_ADDRESS
id|port
comma
id|acpi_integer
id|value
comma
id|u32
id|width
)paren
(brace
r_switch
c_cond
(paren
id|width
)paren
(brace
r_case
l_int|8
suffix:colon
id|outb
c_func
(paren
id|value
comma
id|port
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|outw
c_func
(paren
id|value
comma
id|port
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
id|outl
c_func
(paren
id|value
comma
id|port
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|AE_OK
suffix:semicolon
)brace
id|acpi_status
DECL|function|acpi_os_read_memory
id|acpi_os_read_memory
c_func
(paren
id|ACPI_PHYSICAL_ADDRESS
id|phys_addr
comma
r_void
op_star
id|value
comma
id|u32
id|width
)paren
(brace
id|u32
id|dummy
suffix:semicolon
r_void
op_star
id|virt_addr
suffix:semicolon
macro_line|#ifdef CONFIG_ACPI_EFI
r_int
id|iomem
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|EFI_MEMORY_WB
op_amp
id|efi_mem_attributes
c_func
(paren
id|phys_addr
)paren
)paren
(brace
id|virt_addr
op_assign
id|phys_to_virt
c_func
(paren
id|phys_addr
)paren
suffix:semicolon
)brace
r_else
(brace
id|iomem
op_assign
l_int|1
suffix:semicolon
id|virt_addr
op_assign
id|ioremap
c_func
(paren
id|phys_addr
comma
id|width
)paren
suffix:semicolon
)brace
macro_line|#else
id|virt_addr
op_assign
id|phys_to_virt
c_func
(paren
id|phys_addr
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
id|value
op_assign
op_amp
id|dummy
suffix:semicolon
r_switch
c_cond
(paren
id|width
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
id|value
op_assign
op_star
(paren
id|u8
op_star
)paren
id|virt_addr
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
op_star
(paren
id|u16
op_star
)paren
id|value
op_assign
op_star
(paren
id|u16
op_star
)paren
id|virt_addr
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
op_star
(paren
id|u32
op_star
)paren
id|value
op_assign
op_star
(paren
id|u32
op_star
)paren
id|virt_addr
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ACPI_EFI
r_if
c_cond
(paren
id|iomem
)paren
id|iounmap
c_func
(paren
id|virt_addr
)paren
suffix:semicolon
macro_line|#endif
r_return
id|AE_OK
suffix:semicolon
)brace
id|acpi_status
DECL|function|acpi_os_write_memory
id|acpi_os_write_memory
c_func
(paren
id|ACPI_PHYSICAL_ADDRESS
id|phys_addr
comma
id|acpi_integer
id|value
comma
id|u32
id|width
)paren
(brace
r_void
op_star
id|virt_addr
suffix:semicolon
macro_line|#ifdef CONFIG_ACPI_EFI
r_int
id|iomem
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|EFI_MEMORY_WB
op_amp
id|efi_mem_attributes
c_func
(paren
id|phys_addr
)paren
)paren
(brace
id|virt_addr
op_assign
id|phys_to_virt
c_func
(paren
id|phys_addr
)paren
suffix:semicolon
)brace
r_else
(brace
id|iomem
op_assign
l_int|1
suffix:semicolon
id|virt_addr
op_assign
id|ioremap
c_func
(paren
id|phys_addr
comma
id|width
)paren
suffix:semicolon
)brace
macro_line|#else
id|virt_addr
op_assign
id|phys_to_virt
c_func
(paren
id|phys_addr
)paren
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|width
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
id|virt_addr
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
op_star
(paren
id|u16
op_star
)paren
id|virt_addr
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
op_star
(paren
id|u32
op_star
)paren
id|virt_addr
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ACPI_EFI
r_if
c_cond
(paren
id|iomem
)paren
id|iounmap
c_func
(paren
id|virt_addr
)paren
suffix:semicolon
macro_line|#endif
r_return
id|AE_OK
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ACPI_PCI
id|acpi_status
DECL|function|acpi_os_read_pci_configuration
id|acpi_os_read_pci_configuration
(paren
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
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
id|size
op_assign
l_int|0
suffix:semicolon
r_struct
id|pci_bus
id|bus
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
id|AE_BAD_PARAMETER
suffix:semicolon
r_switch
c_cond
(paren
id|width
)paren
(brace
r_case
l_int|8
suffix:colon
id|size
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|size
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
id|size
op_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|bus.number
op_assign
id|pci_id-&gt;bus
suffix:semicolon
id|result
op_assign
id|pci_root_ops
op_member_access_from_pointer
id|read
c_func
(paren
op_amp
id|bus
comma
id|PCI_DEVFN
c_func
(paren
id|pci_id-&gt;device
comma
id|pci_id-&gt;function
)paren
comma
id|reg
comma
id|size
comma
id|value
)paren
suffix:semicolon
r_return
(paren
id|result
ques
c_cond
id|AE_ERROR
suffix:colon
id|AE_OK
)paren
suffix:semicolon
)brace
id|acpi_status
DECL|function|acpi_os_write_pci_configuration
id|acpi_os_write_pci_configuration
(paren
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
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
id|size
op_assign
l_int|0
suffix:semicolon
r_struct
id|pci_bus
id|bus
suffix:semicolon
r_switch
c_cond
(paren
id|width
)paren
(brace
r_case
l_int|8
suffix:colon
id|size
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|size
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
id|size
op_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|bus.number
op_assign
id|pci_id-&gt;bus
suffix:semicolon
id|result
op_assign
id|pci_root_ops
op_member_access_from_pointer
id|write
c_func
(paren
op_amp
id|bus
comma
id|PCI_DEVFN
c_func
(paren
id|pci_id-&gt;device
comma
id|pci_id-&gt;function
)paren
comma
id|reg
comma
id|size
comma
id|value
)paren
suffix:semicolon
r_return
(paren
id|result
ques
c_cond
id|AE_ERROR
suffix:colon
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* TODO: Change code to take advantage of driver model more */
r_void
DECL|function|acpi_os_derive_pci_id
id|acpi_os_derive_pci_id
(paren
id|acpi_handle
id|rhandle
comma
multiline_comment|/* upper bound  */
id|acpi_handle
id|chandle
comma
multiline_comment|/* current node */
id|acpi_pci_id
op_star
op_star
id|id
)paren
(brace
id|acpi_handle
id|handle
suffix:semicolon
id|acpi_pci_id
op_star
id|pci_id
op_assign
op_star
id|id
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
r_int
r_int
id|temp
suffix:semicolon
id|acpi_object_type
id|type
suffix:semicolon
id|u8
id|tu8
suffix:semicolon
id|acpi_get_parent
c_func
(paren
id|chandle
comma
op_amp
id|handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|handle
op_ne
id|rhandle
)paren
(brace
id|acpi_os_derive_pci_id
c_func
(paren
id|rhandle
comma
id|handle
comma
op_amp
id|pci_id
)paren
suffix:semicolon
id|status
op_assign
id|acpi_get_type
c_func
(paren
id|handle
comma
op_amp
id|type
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
op_logical_or
(paren
id|type
op_ne
id|ACPI_TYPE_DEVICE
)paren
)paren
r_return
suffix:semicolon
id|status
op_assign
id|acpi_evaluate_integer
c_func
(paren
id|handle
comma
id|METHOD_NAME__ADR
comma
l_int|NULL
comma
op_amp
id|temp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_SUCCESS
c_func
(paren
id|status
)paren
)paren
(brace
id|pci_id-&gt;device
op_assign
id|ACPI_HIWORD
(paren
id|ACPI_LODWORD
(paren
id|temp
)paren
)paren
suffix:semicolon
id|pci_id-&gt;function
op_assign
id|ACPI_LOWORD
(paren
id|ACPI_LODWORD
(paren
id|temp
)paren
)paren
suffix:semicolon
multiline_comment|/* any nicer way to get bus number of bridge ? */
id|status
op_assign
id|acpi_os_read_pci_configuration
c_func
(paren
id|pci_id
comma
l_int|0x0e
comma
op_amp
id|tu8
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_SUCCESS
c_func
(paren
id|status
)paren
op_logical_and
(paren
id|tu8
op_amp
l_int|0x7f
)paren
op_eq
l_int|1
)paren
(brace
id|status
op_assign
id|acpi_os_read_pci_configuration
c_func
(paren
id|pci_id
comma
l_int|0x19
comma
op_amp
id|tu8
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_SUCCESS
c_func
(paren
id|status
)paren
)paren
id|pci_id-&gt;bus
op_assign
id|tu8
suffix:semicolon
)brace
)brace
)brace
)brace
macro_line|#else /*!CONFIG_ACPI_PCI*/
id|acpi_status
DECL|function|acpi_os_write_pci_configuration
id|acpi_os_write_pci_configuration
(paren
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
(brace
r_return
(paren
id|AE_SUPPORT
)paren
suffix:semicolon
)brace
id|acpi_status
DECL|function|acpi_os_read_pci_configuration
id|acpi_os_read_pci_configuration
(paren
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
(brace
r_return
(paren
id|AE_SUPPORT
)paren
suffix:semicolon
)brace
macro_line|#endif /*CONFIG_ACPI_PCI*/
multiline_comment|/*&n; * See acpi_os_queue_for_execution()&n; */
r_static
r_int
DECL|function|acpi_os_queue_exec
id|acpi_os_queue_exec
(paren
r_void
op_star
id|context
)paren
(brace
id|ACPI_OS_DPC
op_star
id|dpc
op_assign
(paren
id|ACPI_OS_DPC
op_star
)paren
id|context
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;os_queue_exec&quot;
)paren
suffix:semicolon
id|daemonize
c_func
(paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|current-&gt;comm
comma
l_string|&quot;kacpidpc&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dpc
op_logical_or
op_logical_neg
id|dpc-&gt;function
)paren
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Executing function [%p(%p)].&bslash;n&quot;
comma
id|dpc-&gt;function
comma
id|dpc-&gt;context
)paren
)paren
suffix:semicolon
id|dpc
op_member_access_from_pointer
id|function
c_func
(paren
id|dpc-&gt;context
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dpc
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|acpi_os_schedule_exec
id|acpi_os_schedule_exec
(paren
r_void
op_star
id|context
)paren
(brace
id|ACPI_OS_DPC
op_star
id|dpc
op_assign
l_int|NULL
suffix:semicolon
r_int
id|thread_pid
op_assign
op_minus
l_int|1
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;os_schedule_exec&quot;
)paren
suffix:semicolon
id|dpc
op_assign
(paren
id|ACPI_OS_DPC
op_star
)paren
id|context
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dpc
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid (NULL) context.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Creating new thread to run function [%p(%p)].&bslash;n&quot;
comma
id|dpc-&gt;function
comma
id|dpc-&gt;context
)paren
)paren
suffix:semicolon
id|thread_pid
op_assign
id|kernel_thread
c_func
(paren
id|acpi_os_queue_exec
comma
id|dpc
comma
(paren
id|CLONE_FS
op_or
id|CLONE_FILES
op_or
id|SIGCHLD
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|thread_pid
OL
l_int|0
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Call to kernel_thread() failed.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|acpi_os_free
c_func
(paren
id|dpc
)paren
suffix:semicolon
)brace
id|return_VOID
suffix:semicolon
)brace
id|acpi_status
DECL|function|acpi_os_queue_for_execution
id|acpi_os_queue_for_execution
c_func
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
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_OS_DPC
op_star
id|dpc
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;os_queue_for_execution&quot;
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Scheduling function [%p(%p)] for deferred execution.&bslash;n&quot;
comma
id|function
comma
id|context
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|function
)paren
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Queue via DPC:&n;&t; * --------------&n;&t; * Note that we have to use two different processes for queuing DPCs:&n;&t; *&t; Interrupt-Level: Use schedule_work; can&squot;t spawn a new thread.&n;&t; *&t;    Kernel-Level: Spawn a new kernel thread, as schedule_work has&n;&t; *&t;&t;&t;  its limitations (e.g. single-threaded model), and&n;&t; *&t;&t;&t;  all other task queues run at interrupt-level.&n;&t; */
r_switch
c_cond
(paren
id|priority
)paren
(brace
r_case
id|OSD_PRIORITY_GPE
suffix:colon
(brace
multiline_comment|/*&n;&t;&t; * Allocate/initialize DPC structure.  Note that this memory will be&n;&t;&t; * freed by the callee.  The kernel handles the tq_struct list  in a&n;&t;&t; * way that allows us to also free its memory inside the callee.&n;&t;&t; * Because we may want to schedule several tasks with different&n;&t;&t; * parameters we can&squot;t use the approach some kernel code uses of&n;&t;&t; * having a static tq_struct.&n;&t;&t; * We can save time and code by allocating the DPC and tq_structs&n;&t;&t; * from the same memory.&n;&t;&t; */
r_struct
id|work_struct
op_star
id|task
suffix:semicolon
id|dpc
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|ACPI_OS_DPC
)paren
op_plus
r_sizeof
(paren
r_struct
id|work_struct
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dpc
)paren
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
id|dpc-&gt;function
op_assign
id|function
suffix:semicolon
id|dpc-&gt;context
op_assign
id|context
suffix:semicolon
id|task
op_assign
(paren
r_void
op_star
)paren
(paren
id|dpc
op_plus
l_int|1
)paren
suffix:semicolon
id|INIT_WORK
c_func
(paren
id|task
comma
id|acpi_os_schedule_exec
comma
(paren
r_void
op_star
)paren
id|dpc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|schedule_work
c_func
(paren
id|task
)paren
OL
l_int|0
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Call to schedule_work() failed.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dpc
)paren
suffix:semicolon
id|status
op_assign
id|AE_ERROR
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/*&n;&t;&t; * Allocate/initialize DPC structure.  Note that this memory will be&n;&t;&t; * freed by the callee.&n;&t;&t; */
id|dpc
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|ACPI_OS_DPC
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dpc
)paren
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
id|dpc-&gt;function
op_assign
id|function
suffix:semicolon
id|dpc-&gt;context
op_assign
id|context
suffix:semicolon
id|acpi_os_schedule_exec
c_func
(paren
id|dpc
)paren
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
id|acpi_status
DECL|function|acpi_os_create_semaphore
id|acpi_os_create_semaphore
c_func
(paren
id|u32
id|max_units
comma
id|u32
id|initial_units
comma
id|acpi_handle
op_star
id|handle
)paren
(brace
r_struct
id|semaphore
op_star
id|sem
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;os_create_semaphore&quot;
)paren
suffix:semicolon
id|sem
op_assign
id|acpi_os_allocate
c_func
(paren
r_sizeof
(paren
r_struct
id|semaphore
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sem
)paren
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
id|memset
c_func
(paren
id|sem
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|semaphore
)paren
)paren
suffix:semicolon
id|sema_init
c_func
(paren
id|sem
comma
id|initial_units
)paren
suffix:semicolon
op_star
id|handle
op_assign
(paren
id|acpi_handle
op_star
)paren
id|sem
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_MUTEX
comma
l_string|&quot;Creating semaphore[%p|%d].&bslash;n&quot;
comma
op_star
id|handle
comma
id|initial_units
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * TODO: A better way to delete semaphores?  Linux doesn&squot;t have a&n; * &squot;delete_semaphore()&squot; function -- may result in an invalid&n; * pointer dereference for non-synchronized consumers.&t;Should&n; * we at least check for blocked threads and signal/cancel them?&n; */
id|acpi_status
DECL|function|acpi_os_delete_semaphore
id|acpi_os_delete_semaphore
c_func
(paren
id|acpi_handle
id|handle
)paren
(brace
r_struct
id|semaphore
op_star
id|sem
op_assign
(paren
r_struct
id|semaphore
op_star
)paren
id|handle
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;os_delete_semaphore&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sem
)paren
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_MUTEX
comma
l_string|&quot;Deleting semaphore[%p].&bslash;n&quot;
comma
id|handle
)paren
)paren
suffix:semicolon
id|acpi_os_free
c_func
(paren
id|sem
)paren
suffix:semicolon
id|sem
op_assign
l_int|NULL
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * TODO: The kernel doesn&squot;t have a &squot;down_timeout&squot; function -- had to&n; * improvise.  The process is to sleep for one scheduler quantum&n; * until the semaphore becomes available.  Downside is that this&n; * may result in starvation for timeout-based waits when there&squot;s&n; * lots of semaphore activity.&n; *&n; * TODO: Support for units &gt; 1?&n; */
id|acpi_status
DECL|function|acpi_os_wait_semaphore
id|acpi_os_wait_semaphore
c_func
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
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_struct
id|semaphore
op_star
id|sem
op_assign
(paren
r_struct
id|semaphore
op_star
)paren
id|handle
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;os_wait_semaphore&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sem
op_logical_or
(paren
id|units
OL
l_int|1
)paren
)paren
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|units
OG
l_int|1
)paren
id|return_ACPI_STATUS
(paren
id|AE_SUPPORT
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_MUTEX
comma
l_string|&quot;Waiting for semaphore[%p|%d|%d]&bslash;n&quot;
comma
id|handle
comma
id|units
comma
id|timeout
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in_atomic
c_func
(paren
)paren
)paren
id|timeout
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|timeout
)paren
(brace
multiline_comment|/*&n;&t;&t; * No Wait:&n;&t;&t; * --------&n;&t;&t; * A zero timeout value indicates that we shouldn&squot;t wait - just&n;&t;&t; * acquire the semaphore if available otherwise return AE_TIME&n;&t;&t; * (a.k.a. &squot;would block&squot;).&n;&t;&t; */
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
id|down_trylock
c_func
(paren
id|sem
)paren
)paren
(brace
id|status
op_assign
id|AE_TIME
suffix:semicolon
)brace
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Wait Indefinitely:&n;&t;&t; * ------------------&n;&t;&t; */
r_case
id|ACPI_WAIT_FOREVER
suffix:colon
id|down
c_func
(paren
id|sem
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Wait w/ Timeout:&n;&t;&t; * ----------------&n;&t;&t; */
r_default
suffix:colon
(brace
)brace
singleline_comment|// TODO: A better timeout algorithm?
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_static
r_const
r_int
id|quantum_ms
op_assign
l_int|1000
op_div
id|HZ
suffix:semicolon
id|ret
op_assign
id|down_trylock
c_func
(paren
id|sem
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|timeout
suffix:semicolon
(paren
id|i
OG
l_int|0
op_logical_and
id|ret
OL
l_int|0
)paren
suffix:semicolon
id|i
op_sub_assign
id|quantum_ms
)paren
(brace
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|ret
op_assign
id|down_trylock
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
id|status
op_assign
id|AE_TIME
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Failed to acquire semaphore[%p|%d|%d], %s&bslash;n&quot;
comma
id|handle
comma
id|units
comma
id|timeout
comma
id|acpi_format_exception
c_func
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_MUTEX
comma
l_string|&quot;Acquired semaphore[%p|%d|%d]&bslash;n&quot;
comma
id|handle
comma
id|units
comma
id|timeout
)paren
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * TODO: Support for units &gt; 1?&n; */
id|acpi_status
DECL|function|acpi_os_signal_semaphore
id|acpi_os_signal_semaphore
c_func
(paren
id|acpi_handle
id|handle
comma
id|u32
id|units
)paren
(brace
r_struct
id|semaphore
op_star
id|sem
op_assign
(paren
r_struct
id|semaphore
op_star
)paren
id|handle
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;os_signal_semaphore&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sem
op_logical_or
(paren
id|units
OL
l_int|1
)paren
)paren
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|units
OG
l_int|1
)paren
id|return_ACPI_STATUS
(paren
id|AE_SUPPORT
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_MUTEX
comma
l_string|&quot;Signaling semaphore[%p|%d]&bslash;n&quot;
comma
id|handle
comma
id|units
)paren
)paren
suffix:semicolon
id|up
c_func
(paren
id|sem
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
id|u32
DECL|function|acpi_os_get_line
id|acpi_os_get_line
c_func
(paren
id|NATIVE_CHAR
op_star
id|buffer
)paren
(brace
macro_line|#ifdef ENABLE_DEBUGGER
r_if
c_cond
(paren
id|acpi_in_debugger
)paren
(brace
id|u32
id|chars
suffix:semicolon
id|kdb_read
c_func
(paren
id|buffer
comma
r_sizeof
(paren
id|line_buf
)paren
)paren
suffix:semicolon
multiline_comment|/* remove the CR kdb includes */
id|chars
op_assign
id|strlen
c_func
(paren
id|buffer
)paren
op_minus
l_int|1
suffix:semicolon
id|buffer
(braket
id|chars
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * We just have to assume we&squot;re dealing with valid memory&n; */
id|BOOLEAN
DECL|function|acpi_os_readable
id|acpi_os_readable
c_func
(paren
r_void
op_star
id|ptr
comma
id|u32
id|len
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
id|BOOLEAN
DECL|function|acpi_os_writable
id|acpi_os_writable
c_func
(paren
r_void
op_star
id|ptr
comma
id|u32
id|len
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
id|u32
DECL|function|acpi_os_get_thread_id
id|acpi_os_get_thread_id
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|in_atomic
c_func
(paren
)paren
)paren
r_return
id|current-&gt;pid
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|acpi_status
DECL|function|acpi_os_signal
id|acpi_os_signal
(paren
id|u32
id|function
comma
r_void
op_star
id|info
)paren
(brace
r_switch
c_cond
(paren
id|function
)paren
(brace
r_case
id|ACPI_SIGNAL_FATAL
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Fatal opcode executed&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_SIGNAL_BREAKPOINT
suffix:colon
(brace
r_char
op_star
id|bp_info
op_assign
(paren
r_char
op_star
)paren
id|info
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ACPI breakpoint: %s&bslash;n&quot;
comma
id|bp_info
)paren
suffix:semicolon
)brace
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
id|AE_OK
suffix:semicolon
)brace
eof
