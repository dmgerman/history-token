multiline_comment|/*&n; * CompactPCI Hot Plug Core Functions&n; *&n; * Copyright (C) 2002 SOMA Networks, Inc.&n; * Copyright (C) 2001 Greg Kroah-Hartman (greg@kroah.com)&n; * Copyright (C) 2001 IBM Corp.&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or (at&n; * your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;scottm@somanetworks.com&gt;&n; */
macro_line|#ifndef _CPCI_HOTPLUG_H
DECL|macro|_CPCI_HOTPLUG_H
mdefine_line|#define _CPCI_HOTPLUG_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
multiline_comment|/* PICMG 2.12 R2.0 HS CSR bits: */
DECL|macro|HS_CSR_INS
mdefine_line|#define HS_CSR_INS&t;0x0080
DECL|macro|HS_CSR_EXT
mdefine_line|#define HS_CSR_EXT&t;0x0040
DECL|macro|HS_CSR_PI
mdefine_line|#define HS_CSR_PI&t;0x0030
DECL|macro|HS_CSR_LOO
mdefine_line|#define HS_CSR_LOO&t;0x0008
DECL|macro|HS_CSR_PIE
mdefine_line|#define HS_CSR_PIE&t;0x0004
DECL|macro|HS_CSR_EIM
mdefine_line|#define HS_CSR_EIM&t;0x0002
DECL|macro|HS_CSR_DHA
mdefine_line|#define HS_CSR_DHA&t;0x0001
DECL|struct|slot
r_struct
id|slot
(brace
DECL|member|number
id|u8
id|number
suffix:semicolon
DECL|member|devfn
r_int
r_int
id|devfn
suffix:semicolon
DECL|member|bus
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
DECL|member|extracting
r_int
r_int
id|extracting
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
DECL|struct|cpci_hp_controller_ops
r_struct
id|cpci_hp_controller_ops
(brace
DECL|member|query_enum
r_int
(paren
op_star
id|query_enum
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|enable_irq
r_int
(paren
op_star
id|enable_irq
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|disable_irq
r_int
(paren
op_star
id|disable_irq
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|check_irq
r_int
(paren
op_star
id|check_irq
)paren
(paren
r_void
op_star
id|dev_id
)paren
suffix:semicolon
DECL|member|hardware_test
r_int
(paren
op_star
id|hardware_test
)paren
(paren
r_struct
id|slot
op_star
id|slot
comma
id|u32
id|value
)paren
suffix:semicolon
DECL|member|get_power
id|u8
(paren
op_star
id|get_power
)paren
(paren
r_struct
id|slot
op_star
id|slot
)paren
suffix:semicolon
DECL|member|set_power
r_int
(paren
op_star
id|set_power
)paren
(paren
r_struct
id|slot
op_star
id|slot
comma
r_int
id|value
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cpci_hp_controller
r_struct
id|cpci_hp_controller
(brace
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
DECL|member|irq_flags
r_int
r_int
id|irq_flags
suffix:semicolon
DECL|member|devname
r_char
op_star
id|devname
suffix:semicolon
DECL|member|dev_id
r_void
op_star
id|dev_id
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|ops
r_struct
id|cpci_hp_controller_ops
op_star
id|ops
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|cpci_hp_register_controller
c_func
(paren
r_struct
id|cpci_hp_controller
op_star
id|controller
)paren
suffix:semicolon
r_extern
r_int
id|cpci_hp_unregister_controller
c_func
(paren
r_struct
id|cpci_hp_controller
op_star
id|controller
)paren
suffix:semicolon
r_extern
r_int
id|cpci_hp_register_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
id|u8
id|first
comma
id|u8
id|last
)paren
suffix:semicolon
r_extern
r_int
id|cpci_hp_unregister_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
suffix:semicolon
r_extern
r_int
id|cpci_hp_start
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|cpci_hp_stop
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Internal function prototypes, these functions should not be used by&n; * board/chassis drivers.&n; */
r_extern
id|u8
id|cpci_get_attention_status
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
id|cpci_get_latch_status
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
id|cpci_get_adapter_status
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
suffix:semicolon
r_extern
id|u16
id|cpci_get_hs_csr
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
id|cpci_set_attention_status
c_func
(paren
r_struct
id|slot
op_star
id|slot
comma
r_int
id|status
)paren
suffix:semicolon
r_extern
r_int
id|cpci_check_and_clear_ins
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
id|cpci_check_ext
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
id|cpci_clear_ext
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
id|cpci_led_on
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
id|cpci_led_off
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
id|cpci_configure_slot
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
id|cpci_unconfigure_slot
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
suffix:semicolon
macro_line|#endif&t;/* _CPCI_HOTPLUG_H */
eof
