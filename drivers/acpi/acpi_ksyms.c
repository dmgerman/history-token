multiline_comment|/*&n; *  acpi_ksyms.c - ACPI Kernel Symbols ($Revision: 16 $)&n; *&n; *  Copyright (C) 2001, 2002 Andy Grover &lt;andrew.grover@intel.com&gt;&n; *  Copyright (C) 2001, 2002 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or (at&n; *  your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful, but&n; *  WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; *  General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &quot;include/acpi.h&quot;
macro_line|#include &quot;acpi_bus.h&quot;
macro_line|#ifdef CONFIG_ACPI_INTERPRETER
multiline_comment|/* ACPI Debugger */
macro_line|#ifdef ENABLE_DEBUGGER
r_extern
r_int
id|acpi_in_debugger
suffix:semicolon
DECL|variable|acpi_in_debugger
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_in_debugger
)paren
suffix:semicolon
DECL|variable|acpi_db_user_commands
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_db_user_commands
)paren
suffix:semicolon
macro_line|#endif /* ENABLE_DEBUGGER */
multiline_comment|/* ACPI Core Subsystem */
macro_line|#ifdef ACPI_DEBUG_OUTPUT
DECL|variable|acpi_dbg_layer
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_dbg_layer
)paren
suffix:semicolon
DECL|variable|acpi_dbg_level
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_dbg_level
)paren
suffix:semicolon
DECL|variable|acpi_ut_debug_print_raw
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_ut_debug_print_raw
)paren
suffix:semicolon
DECL|variable|acpi_ut_debug_print
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_ut_debug_print
)paren
suffix:semicolon
DECL|variable|acpi_ut_status_exit
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_ut_status_exit
)paren
suffix:semicolon
DECL|variable|acpi_ut_value_exit
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_ut_value_exit
)paren
suffix:semicolon
DECL|variable|acpi_ut_exit
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_ut_exit
)paren
suffix:semicolon
DECL|variable|acpi_ut_trace
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_ut_trace
)paren
suffix:semicolon
macro_line|#endif /*ACPI_DEBUG_OUTPUT*/
DECL|variable|acpi_get_handle
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_get_handle
)paren
suffix:semicolon
DECL|variable|acpi_get_parent
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_get_parent
)paren
suffix:semicolon
DECL|variable|acpi_get_type
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_get_type
)paren
suffix:semicolon
DECL|variable|acpi_get_name
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_get_name
)paren
suffix:semicolon
DECL|variable|acpi_get_object_info
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_get_object_info
)paren
suffix:semicolon
DECL|variable|acpi_get_next_object
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_get_next_object
)paren
suffix:semicolon
DECL|variable|acpi_evaluate_object
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_evaluate_object
)paren
suffix:semicolon
DECL|variable|acpi_get_table
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_get_table
)paren
suffix:semicolon
DECL|variable|acpi_get_firmware_table
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_get_firmware_table
)paren
suffix:semicolon
DECL|variable|acpi_install_notify_handler
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_install_notify_handler
)paren
suffix:semicolon
DECL|variable|acpi_remove_notify_handler
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_remove_notify_handler
)paren
suffix:semicolon
DECL|variable|acpi_install_gpe_handler
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_install_gpe_handler
)paren
suffix:semicolon
DECL|variable|acpi_remove_gpe_handler
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_remove_gpe_handler
)paren
suffix:semicolon
DECL|variable|acpi_install_address_space_handler
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_install_address_space_handler
)paren
suffix:semicolon
DECL|variable|acpi_remove_address_space_handler
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_remove_address_space_handler
)paren
suffix:semicolon
DECL|variable|acpi_install_fixed_event_handler
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_install_fixed_event_handler
)paren
suffix:semicolon
DECL|variable|acpi_remove_fixed_event_handler
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_remove_fixed_event_handler
)paren
suffix:semicolon
DECL|variable|acpi_acquire_global_lock
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_acquire_global_lock
)paren
suffix:semicolon
DECL|variable|acpi_release_global_lock
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_release_global_lock
)paren
suffix:semicolon
DECL|variable|acpi_get_current_resources
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_get_current_resources
)paren
suffix:semicolon
DECL|variable|acpi_get_possible_resources
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_get_possible_resources
)paren
suffix:semicolon
DECL|variable|acpi_set_current_resources
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_set_current_resources
)paren
suffix:semicolon
DECL|variable|acpi_enable_event
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_enable_event
)paren
suffix:semicolon
DECL|variable|acpi_disable_event
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_disable_event
)paren
suffix:semicolon
DECL|variable|acpi_clear_event
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_clear_event
)paren
suffix:semicolon
DECL|variable|acpi_get_timer_duration
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_get_timer_duration
)paren
suffix:semicolon
DECL|variable|acpi_get_timer
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_get_timer
)paren
suffix:semicolon
DECL|variable|acpi_get_sleep_type_data
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_get_sleep_type_data
)paren
suffix:semicolon
DECL|variable|acpi_get_register
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_get_register
)paren
suffix:semicolon
DECL|variable|acpi_set_register
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_set_register
)paren
suffix:semicolon
DECL|variable|acpi_enter_sleep_state
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_enter_sleep_state
)paren
suffix:semicolon
DECL|variable|acpi_get_system_info
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_get_system_info
)paren
suffix:semicolon
DECL|variable|acpi_get_devices
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_get_devices
)paren
suffix:semicolon
multiline_comment|/* ACPI OS Services Layer (acpi_osl.c) */
DECL|variable|acpi_os_free
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_os_free
)paren
suffix:semicolon
DECL|variable|acpi_os_printf
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_os_printf
)paren
suffix:semicolon
DECL|variable|acpi_os_sleep
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_os_sleep
)paren
suffix:semicolon
DECL|variable|acpi_os_stall
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_os_stall
)paren
suffix:semicolon
DECL|variable|acpi_os_signal
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_os_signal
)paren
suffix:semicolon
DECL|variable|acpi_os_queue_for_execution
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_os_queue_for_execution
)paren
suffix:semicolon
DECL|variable|acpi_os_signal_semaphore
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_os_signal_semaphore
)paren
suffix:semicolon
DECL|variable|acpi_os_create_semaphore
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_os_create_semaphore
)paren
suffix:semicolon
DECL|variable|acpi_os_delete_semaphore
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_os_delete_semaphore
)paren
suffix:semicolon
DECL|variable|acpi_os_wait_semaphore
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_os_wait_semaphore
)paren
suffix:semicolon
DECL|variable|acpi_os_read_pci_configuration
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_os_read_pci_configuration
)paren
suffix:semicolon
multiline_comment|/* ACPI Utilities (acpi_utils.c) */
DECL|variable|acpi_extract_package
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_extract_package
)paren
suffix:semicolon
DECL|variable|acpi_evaluate_integer
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_evaluate_integer
)paren
suffix:semicolon
DECL|variable|acpi_evaluate_reference
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_evaluate_reference
)paren
suffix:semicolon
macro_line|#endif /*CONFIG_ACPI_INTERPRETER*/
multiline_comment|/* ACPI Bus Driver (acpi_bus.c) */
macro_line|#ifdef CONFIG_ACPI_BUS
DECL|variable|acpi_fadt
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_fadt
)paren
suffix:semicolon
DECL|variable|acpi_walk_namespace
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_walk_namespace
)paren
suffix:semicolon
DECL|variable|acpi_root_dir
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_root_dir
)paren
suffix:semicolon
DECL|variable|acpi_bus_get_device
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_bus_get_device
)paren
suffix:semicolon
DECL|variable|acpi_bus_get_status
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_bus_get_status
)paren
suffix:semicolon
DECL|variable|acpi_bus_get_power
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_bus_get_power
)paren
suffix:semicolon
DECL|variable|acpi_bus_set_power
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_bus_set_power
)paren
suffix:semicolon
DECL|variable|acpi_bus_generate_event
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_bus_generate_event
)paren
suffix:semicolon
DECL|variable|acpi_bus_receive_event
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_bus_receive_event
)paren
suffix:semicolon
DECL|variable|acpi_bus_register_driver
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_bus_register_driver
)paren
suffix:semicolon
DECL|variable|acpi_bus_unregister_driver
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_bus_unregister_driver
)paren
suffix:semicolon
macro_line|#endif /*CONFIG_ACPI_BUS*/
multiline_comment|/* ACPI PCI Driver (pci_irq.c) */
macro_line|#ifdef CONFIG_ACPI_PCI
macro_line|#include &lt;linux/pci.h&gt;
r_extern
r_int
id|acpi_pci_irq_enable
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
DECL|variable|acpi_pci_irq_enable
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_pci_irq_enable
)paren
suffix:semicolon
r_extern
r_int
id|acpi_pci_irq_lookup
(paren
r_int
id|segment
comma
r_int
id|bus
comma
r_int
id|device
comma
r_int
id|pin
)paren
suffix:semicolon
DECL|variable|acpi_pci_irq_lookup
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_pci_irq_lookup
)paren
suffix:semicolon
macro_line|#endif /*CONFIG_ACPI_PCI */
macro_line|#ifdef CONFIG_ACPI_EC
multiline_comment|/* ACPI EC driver (ec.c) */
DECL|variable|ec_read
id|EXPORT_SYMBOL
c_func
(paren
id|ec_read
)paren
suffix:semicolon
DECL|variable|ec_write
id|EXPORT_SYMBOL
c_func
(paren
id|ec_write
)paren
suffix:semicolon
macro_line|#endif
eof
