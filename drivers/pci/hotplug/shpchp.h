multiline_comment|/*&n; * Standard Hot Plug Controller Driver&n; *&n; * Copyright (C) 1995,2001 Compaq Computer Corporation&n; * Copyright (C) 2001 Greg Kroah-Hartman (greg@kroah.com)&n; * Copyright (C) 2001 IBM&n; * Copyright (C) 2003-2004 Intel Corporation&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or (at&n; * your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;greg@kroah.com&gt;,&lt;dely.l.sy@intel.com&gt;&n; *&n; */
macro_line|#ifndef _SHPCHP_H
DECL|macro|_SHPCHP_H
mdefine_line|#define _SHPCHP_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/io.h&gt;&t;&t;
macro_line|#include &quot;pci_hotplug.h&quot;
macro_line|#if !defined(CONFIG_HOTPLUG_PCI_SHPC_MODULE)
DECL|macro|MY_NAME
mdefine_line|#define MY_NAME&t;&quot;shpchp&quot;
macro_line|#else
DECL|macro|MY_NAME
mdefine_line|#define MY_NAME&t;THIS_MODULE-&gt;name
macro_line|#endif
r_extern
r_int
id|shpchp_poll_mode
suffix:semicolon
r_extern
r_int
id|shpchp_poll_time
suffix:semicolon
r_extern
r_int
id|shpchp_debug
suffix:semicolon
multiline_comment|/*#define dbg(format, arg...) do { if (shpchp_debug) printk(KERN_DEBUG &quot;%s: &quot; format, MY_NAME , ## arg); } while (0)*/
DECL|macro|dbg
mdefine_line|#define dbg(format, arg...) do { if (shpchp_debug) printk(&quot;%s: &quot; format, MY_NAME , ## arg); } while (0)
DECL|macro|err
mdefine_line|#define err(format, arg...) printk(KERN_ERR &quot;%s: &quot; format, MY_NAME , ## arg)
DECL|macro|info
mdefine_line|#define info(format, arg...) printk(KERN_INFO &quot;%s: &quot; format, MY_NAME , ## arg)
DECL|macro|warn
mdefine_line|#define warn(format, arg...) printk(KERN_WARNING &quot;%s: &quot; format, MY_NAME , ## arg)
DECL|struct|pci_func
r_struct
id|pci_func
(brace
DECL|member|next
r_struct
id|pci_func
op_star
id|next
suffix:semicolon
DECL|member|bus
id|u8
id|bus
suffix:semicolon
DECL|member|device
id|u8
id|device
suffix:semicolon
DECL|member|function
id|u8
id|function
suffix:semicolon
DECL|member|is_a_board
id|u8
id|is_a_board
suffix:semicolon
DECL|member|status
id|u16
id|status
suffix:semicolon
DECL|member|configured
id|u8
id|configured
suffix:semicolon
DECL|member|switch_save
id|u8
id|switch_save
suffix:semicolon
DECL|member|presence_save
id|u8
id|presence_save
suffix:semicolon
DECL|member|pwr_save
id|u8
id|pwr_save
suffix:semicolon
DECL|member|base_length
id|u32
id|base_length
(braket
l_int|0x06
)braket
suffix:semicolon
DECL|member|base_type
id|u8
id|base_type
(braket
l_int|0x06
)braket
suffix:semicolon
DECL|member|reserved2
id|u16
id|reserved2
suffix:semicolon
DECL|member|config_space
id|u32
id|config_space
(braket
l_int|0x20
)braket
suffix:semicolon
DECL|member|mem_head
r_struct
id|pci_resource
op_star
id|mem_head
suffix:semicolon
DECL|member|p_mem_head
r_struct
id|pci_resource
op_star
id|p_mem_head
suffix:semicolon
DECL|member|io_head
r_struct
id|pci_resource
op_star
id|io_head
suffix:semicolon
DECL|member|bus_head
r_struct
id|pci_resource
op_star
id|bus_head
suffix:semicolon
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SLOT_MAGIC
mdefine_line|#define SLOT_MAGIC&t;0x67267321
DECL|struct|slot
r_struct
id|slot
(brace
DECL|member|magic
id|u32
id|magic
suffix:semicolon
DECL|member|next
r_struct
id|slot
op_star
id|next
suffix:semicolon
DECL|member|bus
id|u8
id|bus
suffix:semicolon
DECL|member|device
id|u8
id|device
suffix:semicolon
DECL|member|number
id|u32
id|number
suffix:semicolon
DECL|member|is_a_board
id|u8
id|is_a_board
suffix:semicolon
DECL|member|configured
id|u8
id|configured
suffix:semicolon
DECL|member|state
id|u8
id|state
suffix:semicolon
DECL|member|switch_save
id|u8
id|switch_save
suffix:semicolon
DECL|member|presence_save
id|u8
id|presence_save
suffix:semicolon
DECL|member|capabilities
id|u32
id|capabilities
suffix:semicolon
DECL|member|reserved2
id|u16
id|reserved2
suffix:semicolon
DECL|member|task_event
r_struct
id|timer_list
id|task_event
suffix:semicolon
DECL|member|hp_slot
id|u8
id|hp_slot
suffix:semicolon
DECL|member|ctrl
r_struct
id|controller
op_star
id|ctrl
suffix:semicolon
DECL|member|hpc_ops
r_struct
id|hpc_ops
op_star
id|hpc_ops
suffix:semicolon
DECL|member|hotplug_slot
r_struct
id|hotplug_slot
op_star
id|hotplug_slot
suffix:semicolon
DECL|member|slot_list
r_struct
id|list_head
id|slot_list
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pci_resource
r_struct
id|pci_resource
(brace
DECL|member|next
r_struct
id|pci_resource
op_star
id|next
suffix:semicolon
DECL|member|base
id|u32
id|base
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|event_info
r_struct
id|event_info
(brace
DECL|member|event_type
id|u32
id|event_type
suffix:semicolon
DECL|member|hp_slot
id|u8
id|hp_slot
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|controller
r_struct
id|controller
(brace
DECL|member|next
r_struct
id|controller
op_star
id|next
suffix:semicolon
DECL|member|crit_sect
r_struct
id|semaphore
id|crit_sect
suffix:semicolon
multiline_comment|/* critical section semaphore */
DECL|member|hpc_ctlr_handle
r_void
op_star
id|hpc_ctlr_handle
suffix:semicolon
multiline_comment|/* HPC controller handle */
DECL|member|num_slots
r_int
id|num_slots
suffix:semicolon
multiline_comment|/* Number of slots on ctlr */
DECL|member|slot_num_inc
r_int
id|slot_num_inc
suffix:semicolon
multiline_comment|/* 1 or -1 */
DECL|member|mem_head
r_struct
id|pci_resource
op_star
id|mem_head
suffix:semicolon
DECL|member|p_mem_head
r_struct
id|pci_resource
op_star
id|p_mem_head
suffix:semicolon
DECL|member|io_head
r_struct
id|pci_resource
op_star
id|io_head
suffix:semicolon
DECL|member|bus_head
r_struct
id|pci_resource
op_star
id|bus_head
suffix:semicolon
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
DECL|member|pci_bus
r_struct
id|pci_bus
op_star
id|pci_bus
suffix:semicolon
DECL|member|event_queue
r_struct
id|event_info
id|event_queue
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|slot
r_struct
id|slot
op_star
id|slot
suffix:semicolon
DECL|member|hpc_ops
r_struct
id|hpc_ops
op_star
id|hpc_ops
suffix:semicolon
DECL|member|queue
id|wait_queue_head_t
id|queue
suffix:semicolon
multiline_comment|/* sleep &amp; wake process */
DECL|member|next_event
id|u8
id|next_event
suffix:semicolon
DECL|member|seg
id|u8
id|seg
suffix:semicolon
DECL|member|bus
id|u8
id|bus
suffix:semicolon
DECL|member|device
id|u8
id|device
suffix:semicolon
DECL|member|function
id|u8
id|function
suffix:semicolon
DECL|member|rev
id|u8
id|rev
suffix:semicolon
DECL|member|slot_device_offset
id|u8
id|slot_device_offset
suffix:semicolon
DECL|member|add_support
id|u8
id|add_support
suffix:semicolon
DECL|member|speed
r_enum
id|pci_bus_speed
id|speed
suffix:semicolon
DECL|member|first_slot
id|u32
id|first_slot
suffix:semicolon
multiline_comment|/* First physical slot number */
DECL|member|slot_bus
id|u8
id|slot_bus
suffix:semicolon
multiline_comment|/* Bus where the slots handled by this controller sit */
DECL|member|push_flag
id|u8
id|push_flag
suffix:semicolon
DECL|member|ctlrcap
id|u16
id|ctlrcap
suffix:semicolon
DECL|member|vendor_id
id|u16
id|vendor_id
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|irq_mapping
r_struct
id|irq_mapping
(brace
DECL|member|barber_pole
id|u8
id|barber_pole
suffix:semicolon
DECL|member|valid_INT
id|u8
id|valid_INT
suffix:semicolon
DECL|member|interrupt
id|u8
id|interrupt
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|resource_lists
r_struct
id|resource_lists
(brace
DECL|member|mem_head
r_struct
id|pci_resource
op_star
id|mem_head
suffix:semicolon
DECL|member|p_mem_head
r_struct
id|pci_resource
op_star
id|p_mem_head
suffix:semicolon
DECL|member|io_head
r_struct
id|pci_resource
op_star
id|io_head
suffix:semicolon
DECL|member|bus_head
r_struct
id|pci_resource
op_star
id|bus_head
suffix:semicolon
DECL|member|irqs
r_struct
id|irq_mapping
op_star
id|irqs
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Define AMD SHPC ID  */
DECL|macro|PCI_DEVICE_ID_AMD_GOLAM_7450
mdefine_line|#define PCI_DEVICE_ID_AMD_GOLAM_7450&t;0x7450 
DECL|macro|INT_BUTTON_IGNORE
mdefine_line|#define INT_BUTTON_IGNORE&t;&t;0
DECL|macro|INT_PRESENCE_ON
mdefine_line|#define INT_PRESENCE_ON&t;&t;&t;1
DECL|macro|INT_PRESENCE_OFF
mdefine_line|#define INT_PRESENCE_OFF&t;&t;2
DECL|macro|INT_SWITCH_CLOSE
mdefine_line|#define INT_SWITCH_CLOSE&t;&t;3
DECL|macro|INT_SWITCH_OPEN
mdefine_line|#define INT_SWITCH_OPEN&t;&t;&t;4
DECL|macro|INT_POWER_FAULT
mdefine_line|#define INT_POWER_FAULT&t;&t;&t;5
DECL|macro|INT_POWER_FAULT_CLEAR
mdefine_line|#define INT_POWER_FAULT_CLEAR&t;&t;6
DECL|macro|INT_BUTTON_PRESS
mdefine_line|#define INT_BUTTON_PRESS&t;&t;7
DECL|macro|INT_BUTTON_RELEASE
mdefine_line|#define INT_BUTTON_RELEASE&t;&t;8
DECL|macro|INT_BUTTON_CANCEL
mdefine_line|#define INT_BUTTON_CANCEL&t;&t;9
DECL|macro|STATIC_STATE
mdefine_line|#define STATIC_STATE&t;&t;&t;0
DECL|macro|BLINKINGON_STATE
mdefine_line|#define BLINKINGON_STATE&t;&t;1
DECL|macro|BLINKINGOFF_STATE
mdefine_line|#define BLINKINGOFF_STATE&t;&t;2
DECL|macro|POWERON_STATE
mdefine_line|#define POWERON_STATE&t;&t;&t;3
DECL|macro|POWEROFF_STATE
mdefine_line|#define POWEROFF_STATE&t;&t;&t;4
DECL|macro|PCI_TO_PCI_BRIDGE_CLASS
mdefine_line|#define PCI_TO_PCI_BRIDGE_CLASS&t;&t;0x00060400
multiline_comment|/* Error messages */
DECL|macro|INTERLOCK_OPEN
mdefine_line|#define INTERLOCK_OPEN&t;&t;&t;0x00000002
DECL|macro|ADD_NOT_SUPPORTED
mdefine_line|#define ADD_NOT_SUPPORTED&t;&t;0x00000003
DECL|macro|CARD_FUNCTIONING
mdefine_line|#define CARD_FUNCTIONING&t;&t;0x00000005
DECL|macro|ADAPTER_NOT_SAME
mdefine_line|#define ADAPTER_NOT_SAME&t;&t;0x00000006
DECL|macro|NO_ADAPTER_PRESENT
mdefine_line|#define NO_ADAPTER_PRESENT&t;&t;0x00000009
DECL|macro|NOT_ENOUGH_RESOURCES
mdefine_line|#define NOT_ENOUGH_RESOURCES&t;&t;0x0000000B
DECL|macro|DEVICE_TYPE_NOT_SUPPORTED
mdefine_line|#define DEVICE_TYPE_NOT_SUPPORTED&t;0x0000000C
DECL|macro|WRONG_BUS_FREQUENCY
mdefine_line|#define WRONG_BUS_FREQUENCY&t;&t;0x0000000D
DECL|macro|POWER_FAILURE
mdefine_line|#define POWER_FAILURE&t;&t;&t;0x0000000E
DECL|macro|REMOVE_NOT_SUPPORTED
mdefine_line|#define REMOVE_NOT_SUPPORTED&t;&t;0x00000003
DECL|macro|DISABLE_CARD
mdefine_line|#define DISABLE_CARD&t;&t;&t;1
multiline_comment|/*&n; * error Messages&n; */
DECL|macro|msg_initialization_err
mdefine_line|#define msg_initialization_err&t;&quot;Initialization failure, error=%d&bslash;n&quot;
DECL|macro|msg_HPC_rev_error
mdefine_line|#define msg_HPC_rev_error&t;&quot;Unsupported revision of the PCI hot plug controller found.&bslash;n&quot;
DECL|macro|msg_HPC_non_shpc
mdefine_line|#define msg_HPC_non_shpc&t;&quot;The PCI hot plug controller is not supported by this driver.&bslash;n&quot;
DECL|macro|msg_HPC_not_supported
mdefine_line|#define msg_HPC_not_supported&t;&quot;This system is not supported by this version of shpcphd mdoule. Upgrade to a newer version of shpchpd&bslash;n&quot;
DECL|macro|msg_unable_to_save
mdefine_line|#define msg_unable_to_save&t;&quot;Unable to store PCI hot plug add resource information. This system must be rebooted before adding any PCI devices.&bslash;n&quot;
DECL|macro|msg_button_on
mdefine_line|#define msg_button_on&t;&t;&quot;PCI slot #%d - powering on due to button press.&bslash;n&quot;
DECL|macro|msg_button_off
mdefine_line|#define msg_button_off&t;&t;&quot;PCI slot #%d - powering off due to button press.&bslash;n&quot;
DECL|macro|msg_button_cancel
mdefine_line|#define msg_button_cancel&t;&quot;PCI slot #%d - action canceled due to button press.&bslash;n&quot;
DECL|macro|msg_button_ignore
mdefine_line|#define msg_button_ignore&t;&quot;PCI slot #%d - button press ignored.  (action in progress...)&bslash;n&quot;
multiline_comment|/* sysfs functions for the hotplug controller info */
r_extern
r_void
id|shpchp_create_ctrl_files
(paren
r_struct
id|controller
op_star
id|ctrl
)paren
suffix:semicolon
multiline_comment|/* controller functions */
r_extern
r_int
id|shpchprm_find_available_resources
c_func
(paren
r_struct
id|controller
op_star
id|ctrl
)paren
suffix:semicolon
r_extern
r_int
id|shpchp_event_start_thread
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|shpchp_event_stop_thread
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|pci_func
op_star
id|shpchp_slot_create
c_func
(paren
r_int
r_char
id|busnumber
)paren
suffix:semicolon
r_extern
r_struct
id|pci_func
op_star
id|shpchp_slot_find
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|device
comma
r_int
r_char
id|index
)paren
suffix:semicolon
r_extern
r_int
id|shpchp_enable_slot
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
suffix:semicolon
r_extern
r_int
id|shpchp_disable_slot
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
suffix:semicolon
r_extern
id|u8
id|shpchp_handle_attention_button
c_func
(paren
id|u8
id|hp_slot
comma
r_void
op_star
id|inst_id
)paren
suffix:semicolon
r_extern
id|u8
id|shpchp_handle_switch_change
c_func
(paren
id|u8
id|hp_slot
comma
r_void
op_star
id|inst_id
)paren
suffix:semicolon
r_extern
id|u8
id|shpchp_handle_presence_change
c_func
(paren
id|u8
id|hp_slot
comma
r_void
op_star
id|inst_id
)paren
suffix:semicolon
r_extern
id|u8
id|shpchp_handle_power_fault
c_func
(paren
id|u8
id|hp_slot
comma
r_void
op_star
id|inst_id
)paren
suffix:semicolon
multiline_comment|/* resource functions */
r_extern
r_int
id|shpchp_resource_sort_and_combine
c_func
(paren
r_struct
id|pci_resource
op_star
op_star
id|head
)paren
suffix:semicolon
multiline_comment|/* pci functions */
r_extern
r_int
id|shpchp_set_irq
c_func
(paren
id|u8
id|bus_num
comma
id|u8
id|dev_num
comma
id|u8
id|int_pin
comma
id|u8
id|irq_num
)paren
suffix:semicolon
multiline_comment|/*extern int&t;shpchp_get_bus_dev(struct controller *ctrl, u8 *bus_num, u8 *dev_num, struct slot *slot);*/
r_extern
r_int
id|shpchp_save_config
c_func
(paren
r_struct
id|controller
op_star
id|ctrl
comma
r_int
id|busnumber
comma
r_int
id|num_ctlr_slots
comma
r_int
id|first_device_num
)paren
suffix:semicolon
r_extern
r_int
id|shpchp_save_used_resources
c_func
(paren
r_struct
id|controller
op_star
id|ctrl
comma
r_struct
id|pci_func
op_star
id|func
comma
r_int
id|flag
)paren
suffix:semicolon
r_extern
r_int
id|shpchp_save_slot_config
c_func
(paren
r_struct
id|controller
op_star
id|ctrl
comma
r_struct
id|pci_func
op_star
id|new_slot
)paren
suffix:semicolon
r_extern
r_void
id|shpchp_destroy_board_resources
c_func
(paren
r_struct
id|pci_func
op_star
id|func
)paren
suffix:semicolon
r_extern
r_int
id|shpchp_return_board_resources
c_func
(paren
r_struct
id|pci_func
op_star
id|func
comma
r_struct
id|resource_lists
op_star
id|resources
)paren
suffix:semicolon
r_extern
r_void
id|shpchp_destroy_resource_list
c_func
(paren
r_struct
id|resource_lists
op_star
id|resources
)paren
suffix:semicolon
r_extern
r_int
id|shpchp_configure_device
c_func
(paren
r_struct
id|controller
op_star
id|ctrl
comma
r_struct
id|pci_func
op_star
id|func
)paren
suffix:semicolon
r_extern
r_int
id|shpchp_unconfigure_device
c_func
(paren
r_struct
id|pci_func
op_star
id|func
)paren
suffix:semicolon
multiline_comment|/* Global variables */
r_extern
r_struct
id|controller
op_star
id|shpchp_ctrl_list
suffix:semicolon
r_extern
r_struct
id|pci_func
op_star
id|shpchp_slot_list
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* These are added to support AMD shpc */
r_extern
id|u8
id|shpchp_nic_irq
suffix:semicolon
r_extern
id|u8
id|shpchp_disk_irq
suffix:semicolon
DECL|struct|ctrl_reg
r_struct
id|ctrl_reg
(brace
DECL|member|base_offset
r_volatile
id|u32
id|base_offset
suffix:semicolon
DECL|member|slot_avail1
r_volatile
id|u32
id|slot_avail1
suffix:semicolon
DECL|member|slot_avail2
r_volatile
id|u32
id|slot_avail2
suffix:semicolon
DECL|member|slot_config
r_volatile
id|u32
id|slot_config
suffix:semicolon
DECL|member|sec_bus_config
r_volatile
id|u16
id|sec_bus_config
suffix:semicolon
DECL|member|msi_ctrl
r_volatile
id|u8
id|msi_ctrl
suffix:semicolon
DECL|member|prog_interface
r_volatile
id|u8
id|prog_interface
suffix:semicolon
DECL|member|cmd
r_volatile
id|u16
id|cmd
suffix:semicolon
DECL|member|cmd_status
r_volatile
id|u16
id|cmd_status
suffix:semicolon
DECL|member|intr_loc
r_volatile
id|u32
id|intr_loc
suffix:semicolon
DECL|member|serr_loc
r_volatile
id|u32
id|serr_loc
suffix:semicolon
DECL|member|serr_intr_enable
r_volatile
id|u32
id|serr_intr_enable
suffix:semicolon
DECL|member|slot1
r_volatile
id|u32
id|slot1
suffix:semicolon
DECL|member|slot2
r_volatile
id|u32
id|slot2
suffix:semicolon
DECL|member|slot3
r_volatile
id|u32
id|slot3
suffix:semicolon
DECL|member|slot4
r_volatile
id|u32
id|slot4
suffix:semicolon
DECL|member|slot5
r_volatile
id|u32
id|slot5
suffix:semicolon
DECL|member|slot6
r_volatile
id|u32
id|slot6
suffix:semicolon
DECL|member|slot7
r_volatile
id|u32
id|slot7
suffix:semicolon
DECL|member|slot8
r_volatile
id|u32
id|slot8
suffix:semicolon
DECL|member|slot9
r_volatile
id|u32
id|slot9
suffix:semicolon
DECL|member|slot10
r_volatile
id|u32
id|slot10
suffix:semicolon
DECL|member|slot11
r_volatile
id|u32
id|slot11
suffix:semicolon
DECL|member|slot12
r_volatile
id|u32
id|slot12
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* offsets to the controller registers based on the above structure layout */
DECL|enum|ctrl_offsets
r_enum
id|ctrl_offsets
(brace
DECL|enumerator|BASE_OFFSET
id|BASE_OFFSET
op_assign
m_offsetof
(paren
r_struct
id|ctrl_reg
comma
id|base_offset
)paren
comma
DECL|enumerator|SLOT_AVAIL1
id|SLOT_AVAIL1
op_assign
m_offsetof
(paren
r_struct
id|ctrl_reg
comma
id|slot_avail1
)paren
comma
DECL|enumerator|SLOT_AVAIL2
id|SLOT_AVAIL2
op_assign
m_offsetof
(paren
r_struct
id|ctrl_reg
comma
id|slot_avail2
)paren
comma
DECL|enumerator|SLOT_CONFIG
id|SLOT_CONFIG
op_assign
m_offsetof
(paren
r_struct
id|ctrl_reg
comma
id|slot_config
)paren
comma
DECL|enumerator|SEC_BUS_CONFIG
id|SEC_BUS_CONFIG
op_assign
m_offsetof
(paren
r_struct
id|ctrl_reg
comma
id|sec_bus_config
)paren
comma
DECL|enumerator|MSI_CTRL
id|MSI_CTRL
op_assign
m_offsetof
(paren
r_struct
id|ctrl_reg
comma
id|msi_ctrl
)paren
comma
DECL|enumerator|PROG_INTERFACE
id|PROG_INTERFACE
op_assign
m_offsetof
(paren
r_struct
id|ctrl_reg
comma
id|prog_interface
)paren
comma
DECL|enumerator|CMD
id|CMD
op_assign
m_offsetof
(paren
r_struct
id|ctrl_reg
comma
id|cmd
)paren
comma
DECL|enumerator|CMD_STATUS
id|CMD_STATUS
op_assign
m_offsetof
(paren
r_struct
id|ctrl_reg
comma
id|cmd_status
)paren
comma
DECL|enumerator|INTR_LOC
id|INTR_LOC
op_assign
m_offsetof
(paren
r_struct
id|ctrl_reg
comma
id|intr_loc
)paren
comma
DECL|enumerator|SERR_LOC
id|SERR_LOC
op_assign
m_offsetof
(paren
r_struct
id|ctrl_reg
comma
id|serr_loc
)paren
comma
DECL|enumerator|SERR_INTR_ENABLE
id|SERR_INTR_ENABLE
op_assign
m_offsetof
(paren
r_struct
id|ctrl_reg
comma
id|serr_intr_enable
)paren
comma
DECL|enumerator|SLOT1
id|SLOT1
op_assign
m_offsetof
(paren
r_struct
id|ctrl_reg
comma
id|slot1
)paren
comma
DECL|enumerator|SLOT2
id|SLOT2
op_assign
m_offsetof
(paren
r_struct
id|ctrl_reg
comma
id|slot2
)paren
comma
DECL|enumerator|SLOT3
id|SLOT3
op_assign
m_offsetof
(paren
r_struct
id|ctrl_reg
comma
id|slot3
)paren
comma
DECL|enumerator|SLOT4
id|SLOT4
op_assign
m_offsetof
(paren
r_struct
id|ctrl_reg
comma
id|slot4
)paren
comma
DECL|enumerator|SLOT5
id|SLOT5
op_assign
m_offsetof
(paren
r_struct
id|ctrl_reg
comma
id|slot5
)paren
comma
DECL|enumerator|SLOT6
id|SLOT6
op_assign
m_offsetof
(paren
r_struct
id|ctrl_reg
comma
id|slot6
)paren
comma
DECL|enumerator|SLOT7
id|SLOT7
op_assign
m_offsetof
(paren
r_struct
id|ctrl_reg
comma
id|slot7
)paren
comma
DECL|enumerator|SLOT8
id|SLOT8
op_assign
m_offsetof
(paren
r_struct
id|ctrl_reg
comma
id|slot8
)paren
comma
DECL|enumerator|SLOT9
id|SLOT9
op_assign
m_offsetof
(paren
r_struct
id|ctrl_reg
comma
id|slot9
)paren
comma
DECL|enumerator|SLOT10
id|SLOT10
op_assign
m_offsetof
(paren
r_struct
id|ctrl_reg
comma
id|slot10
)paren
comma
DECL|enumerator|SLOT11
id|SLOT11
op_assign
m_offsetof
(paren
r_struct
id|ctrl_reg
comma
id|slot11
)paren
comma
DECL|enumerator|SLOT12
id|SLOT12
op_assign
m_offsetof
(paren
r_struct
id|ctrl_reg
comma
id|slot12
)paren
comma
)brace
suffix:semicolon
DECL|typedef|php_intr_callback_t
r_typedef
id|u8
c_func
(paren
op_star
id|php_intr_callback_t
)paren
(paren
r_int
r_int
id|change_id
comma
r_void
op_star
id|instance_id
)paren
suffix:semicolon
DECL|struct|php_ctlr_state_s
r_struct
id|php_ctlr_state_s
(brace
DECL|member|pnext
r_struct
id|php_ctlr_state_s
op_star
id|pnext
suffix:semicolon
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* spinlock&squot;s */
DECL|member|slot_device_offset
id|u32
id|slot_device_offset
suffix:semicolon
DECL|member|num_slots
id|u32
id|num_slots
suffix:semicolon
DECL|member|int_poll_timer
r_struct
id|timer_list
id|int_poll_timer
suffix:semicolon
multiline_comment|/* Added for poll event */
DECL|member|attention_button_callback
id|php_intr_callback_t
id|attention_button_callback
suffix:semicolon
DECL|member|switch_change_callback
id|php_intr_callback_t
id|switch_change_callback
suffix:semicolon
DECL|member|presence_change_callback
id|php_intr_callback_t
id|presence_change_callback
suffix:semicolon
DECL|member|power_fault_callback
id|php_intr_callback_t
id|power_fault_callback
suffix:semicolon
DECL|member|callback_instance_id
r_void
op_star
id|callback_instance_id
suffix:semicolon
DECL|member|creg
r_void
op_star
id|creg
suffix:semicolon
multiline_comment|/* Ptr to controller register space */
)brace
suffix:semicolon
multiline_comment|/* Inline functions */
multiline_comment|/* Inline functions to check the sanity of a pointer that is passed to us */
DECL|function|slot_paranoia_check
r_static
r_inline
r_int
id|slot_paranoia_check
(paren
r_struct
id|slot
op_star
id|slot
comma
r_const
r_char
op_star
id|function
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|slot
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - slot == NULL&quot;
comma
id|function
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|slot-&gt;magic
op_ne
id|SLOT_MAGIC
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - bad magic number for slot&quot;
comma
id|function
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|slot-&gt;hotplug_slot
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - slot-&gt;hotplug_slot == NULL!&quot;
comma
id|function
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_slot
r_static
r_inline
r_struct
id|slot
op_star
id|get_slot
(paren
r_struct
id|hotplug_slot
op_star
id|hotplug_slot
comma
r_const
r_char
op_star
id|function
)paren
(brace
r_struct
id|slot
op_star
id|slot
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hotplug_slot
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - hotplug_slot == NULL&bslash;n&quot;
comma
id|function
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|slot
op_assign
(paren
r_struct
id|slot
op_star
)paren
id|hotplug_slot
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
id|slot_paranoia_check
(paren
id|slot
comma
id|function
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|slot
suffix:semicolon
)brace
DECL|function|shpchp_find_slot
r_static
r_inline
r_struct
id|slot
op_star
id|shpchp_find_slot
(paren
r_struct
id|controller
op_star
id|ctrl
comma
id|u8
id|device
)paren
(brace
r_struct
id|slot
op_star
id|p_slot
comma
op_star
id|tmp_slot
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ctrl
)paren
r_return
l_int|NULL
suffix:semicolon
id|p_slot
op_assign
id|ctrl-&gt;slot
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;p_slot = %p&bslash;n&quot;
comma
id|p_slot
)paren
suffix:semicolon
r_while
c_loop
(paren
id|p_slot
op_logical_and
(paren
id|p_slot-&gt;device
op_ne
id|device
)paren
)paren
(brace
id|tmp_slot
op_assign
id|p_slot
suffix:semicolon
id|p_slot
op_assign
id|p_slot-&gt;next
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;In while loop, p_slot = %p&bslash;n&quot;
comma
id|p_slot
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p_slot
op_eq
l_int|NULL
)paren
(brace
id|err
c_func
(paren
l_string|&quot;ERROR: shpchp_find_slot device=0x%x&bslash;n&quot;
comma
id|device
)paren
suffix:semicolon
id|p_slot
op_assign
id|tmp_slot
suffix:semicolon
)brace
r_return
(paren
id|p_slot
)paren
suffix:semicolon
)brace
DECL|function|wait_for_ctrl_irq
r_static
r_inline
r_int
id|wait_for_ctrl_irq
(paren
r_struct
id|controller
op_star
id|ctrl
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s : start&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|ctrl-&gt;queue
comma
op_amp
id|wait
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shpchp_poll_mode
)paren
(brace
multiline_comment|/* Sleep for up to 1 second */
id|schedule_timeout
c_func
(paren
l_int|1
op_star
id|HZ
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Sleep for up to 2 seconds */
id|schedule_timeout
c_func
(paren
l_int|2
op_star
id|HZ
)paren
suffix:semicolon
)brace
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|ctrl-&gt;queue
comma
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
id|retval
op_assign
op_minus
id|EINTR
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s : end&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Puts node back in the resource list pointed to by head */
DECL|function|return_resource
r_static
r_inline
r_void
id|return_resource
c_func
(paren
r_struct
id|pci_resource
op_star
op_star
id|head
comma
r_struct
id|pci_resource
op_star
id|node
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|node
op_logical_or
op_logical_neg
id|head
)paren
r_return
suffix:semicolon
id|node-&gt;next
op_assign
op_star
id|head
suffix:semicolon
op_star
id|head
op_assign
id|node
suffix:semicolon
)brace
DECL|macro|SLOT_NAME_SIZE
mdefine_line|#define SLOT_NAME_SIZE 10
DECL|function|make_slot_name
r_static
r_inline
r_void
id|make_slot_name
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
id|buffer_size
comma
r_struct
id|slot
op_star
id|slot
)paren
(brace
id|snprintf
c_func
(paren
id|buffer
comma
id|buffer_size
comma
l_string|&quot;%d&quot;
comma
id|slot-&gt;number
)paren
suffix:semicolon
)brace
DECL|enum|php_ctlr_type
r_enum
id|php_ctlr_type
(brace
DECL|enumerator|PCI
id|PCI
comma
DECL|enumerator|ISA
id|ISA
comma
DECL|enumerator|ACPI
id|ACPI
)brace
suffix:semicolon
r_int
id|shpc_init
c_func
(paren
r_struct
id|controller
op_star
id|ctrl
comma
r_struct
id|pci_dev
op_star
id|pdev
comma
id|php_intr_callback_t
id|attention_button_callback
comma
id|php_intr_callback_t
id|switch_change_callback
comma
id|php_intr_callback_t
id|presence_change_callback
comma
id|php_intr_callback_t
id|power_fault_callback
)paren
suffix:semicolon
r_int
id|shpc_get_ctlr_slot_config
c_func
(paren
r_struct
id|controller
op_star
id|ctrl
comma
r_int
op_star
id|num_ctlr_slots
comma
r_int
op_star
id|first_device_num
comma
r_int
op_star
id|physical_slot_num
comma
r_int
op_star
id|updown
comma
r_int
op_star
id|flags
)paren
suffix:semicolon
DECL|struct|hpc_ops
r_struct
id|hpc_ops
(brace
DECL|member|power_on_slot
r_int
(paren
op_star
id|power_on_slot
)paren
(paren
r_struct
id|slot
op_star
id|slot
)paren
suffix:semicolon
DECL|member|slot_enable
r_int
(paren
op_star
id|slot_enable
)paren
(paren
r_struct
id|slot
op_star
id|slot
)paren
suffix:semicolon
DECL|member|slot_disable
r_int
(paren
op_star
id|slot_disable
)paren
(paren
r_struct
id|slot
op_star
id|slot
)paren
suffix:semicolon
DECL|member|enable_all_slots
r_int
(paren
op_star
id|enable_all_slots
)paren
(paren
r_struct
id|slot
op_star
id|slot
)paren
suffix:semicolon
DECL|member|pwr_on_all_slots
r_int
(paren
op_star
id|pwr_on_all_slots
)paren
(paren
r_struct
id|slot
op_star
id|slot
)paren
suffix:semicolon
DECL|member|set_bus_speed_mode
r_int
(paren
op_star
id|set_bus_speed_mode
)paren
(paren
r_struct
id|slot
op_star
id|slot
comma
r_enum
id|pci_bus_speed
id|speed
)paren
suffix:semicolon
DECL|member|get_power_status
r_int
(paren
op_star
id|get_power_status
)paren
(paren
r_struct
id|slot
op_star
id|slot
comma
id|u8
op_star
id|status
)paren
suffix:semicolon
DECL|member|get_attention_status
r_int
(paren
op_star
id|get_attention_status
)paren
(paren
r_struct
id|slot
op_star
id|slot
comma
id|u8
op_star
id|status
)paren
suffix:semicolon
DECL|member|set_attention_status
r_int
(paren
op_star
id|set_attention_status
)paren
(paren
r_struct
id|slot
op_star
id|slot
comma
id|u8
id|status
)paren
suffix:semicolon
DECL|member|get_latch_status
r_int
(paren
op_star
id|get_latch_status
)paren
(paren
r_struct
id|slot
op_star
id|slot
comma
id|u8
op_star
id|status
)paren
suffix:semicolon
DECL|member|get_adapter_status
r_int
(paren
op_star
id|get_adapter_status
)paren
(paren
r_struct
id|slot
op_star
id|slot
comma
id|u8
op_star
id|status
)paren
suffix:semicolon
DECL|member|get_max_bus_speed
r_int
(paren
op_star
id|get_max_bus_speed
)paren
(paren
r_struct
id|slot
op_star
id|slot
comma
r_enum
id|pci_bus_speed
op_star
id|speed
)paren
suffix:semicolon
DECL|member|get_cur_bus_speed
r_int
(paren
op_star
id|get_cur_bus_speed
)paren
(paren
r_struct
id|slot
op_star
id|slot
comma
r_enum
id|pci_bus_speed
op_star
id|speed
)paren
suffix:semicolon
DECL|member|get_adapter_speed
r_int
(paren
op_star
id|get_adapter_speed
)paren
(paren
r_struct
id|slot
op_star
id|slot
comma
r_enum
id|pci_bus_speed
op_star
id|speed
)paren
suffix:semicolon
DECL|member|get_mode1_ECC_cap
r_int
(paren
op_star
id|get_mode1_ECC_cap
)paren
(paren
r_struct
id|slot
op_star
id|slot
comma
id|u8
op_star
id|mode
)paren
suffix:semicolon
DECL|member|get_prog_int
r_int
(paren
op_star
id|get_prog_int
)paren
(paren
r_struct
id|slot
op_star
id|slot
comma
id|u8
op_star
id|prog_int
)paren
suffix:semicolon
DECL|member|query_power_fault
r_int
(paren
op_star
id|query_power_fault
)paren
(paren
r_struct
id|slot
op_star
id|slot
)paren
suffix:semicolon
DECL|member|green_led_on
r_void
(paren
op_star
id|green_led_on
)paren
(paren
r_struct
id|slot
op_star
id|slot
)paren
suffix:semicolon
DECL|member|green_led_off
r_void
(paren
op_star
id|green_led_off
)paren
(paren
r_struct
id|slot
op_star
id|slot
)paren
suffix:semicolon
DECL|member|green_led_blink
r_void
(paren
op_star
id|green_led_blink
)paren
(paren
r_struct
id|slot
op_star
id|slot
)paren
suffix:semicolon
DECL|member|release_ctlr
r_void
(paren
op_star
id|release_ctlr
)paren
(paren
r_struct
id|controller
op_star
id|ctrl
)paren
suffix:semicolon
DECL|member|check_cmd_status
r_int
(paren
op_star
id|check_cmd_status
)paren
(paren
r_struct
id|controller
op_star
id|ctrl
)paren
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _SHPCHP_H */
eof
