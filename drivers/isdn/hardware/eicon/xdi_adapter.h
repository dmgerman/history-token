multiline_comment|/* $Id: xdi_adapter.h,v 1.5 2003/06/21 17:06:08 schindler Exp $ */
macro_line|#ifndef __DIVA_OS_XDI_ADAPTER_H__
DECL|macro|__DIVA_OS_XDI_ADAPTER_H__
mdefine_line|#define __DIVA_OS_XDI_ADAPTER_H__
DECL|macro|DIVAS_XDI_ADAPTER_BUS_PCI
mdefine_line|#define DIVAS_XDI_ADAPTER_BUS_PCI  0
DECL|macro|DIVAS_XDI_ADAPTER_BUS_ISA
mdefine_line|#define DIVAS_XDI_ADAPTER_BUS_ISA  1
DECL|struct|_divas_pci_card_resources
r_typedef
r_struct
id|_divas_pci_card_resources
(brace
DECL|member|bus
id|byte
id|bus
suffix:semicolon
DECL|member|func
id|byte
id|func
suffix:semicolon
DECL|member|hdev
r_void
op_star
id|hdev
suffix:semicolon
DECL|member|bar
id|dword
id|bar
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* contains context of appropriate BAR Register */
DECL|member|addr
r_void
op_star
id|addr
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* same bar, but mapped into memory */
DECL|member|length
id|dword
id|length
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* bar length */
DECL|member|mem_type_id
r_int
id|mem_type_id
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|qoffset
r_int
r_int
id|qoffset
suffix:semicolon
DECL|member|irq
id|byte
id|irq
suffix:semicolon
DECL|typedef|divas_pci_card_resources_t
)brace
id|divas_pci_card_resources_t
suffix:semicolon
DECL|union|_divas_card_resources
r_typedef
r_union
id|_divas_card_resources
(brace
DECL|member|pci
id|divas_pci_card_resources_t
id|pci
suffix:semicolon
DECL|typedef|divas_card_resources_t
)brace
id|divas_card_resources_t
suffix:semicolon
r_struct
id|_diva_os_xdi_adapter
suffix:semicolon
DECL|typedef|diva_init_card_proc_t
r_typedef
r_int
(paren
op_star
id|diva_init_card_proc_t
)paren
(paren
r_struct
id|_diva_os_xdi_adapter
op_star
id|a
)paren
suffix:semicolon
DECL|typedef|diva_cmd_card_proc_t
r_typedef
r_int
(paren
op_star
id|diva_cmd_card_proc_t
)paren
(paren
r_struct
id|_diva_os_xdi_adapter
op_star
id|a
comma
id|diva_xdi_um_cfg_cmd_t
op_star
id|data
comma
r_int
id|length
)paren
suffix:semicolon
DECL|typedef|diva_xdi_clear_interrupts_proc_t
r_typedef
r_void
(paren
op_star
id|diva_xdi_clear_interrupts_proc_t
)paren
(paren
r_struct
id|_diva_os_xdi_adapter
op_star
)paren
suffix:semicolon
DECL|macro|DIVA_XDI_MBOX_BUSY
mdefine_line|#define DIVA_XDI_MBOX_BUSY&t;&t;&t;1
DECL|macro|DIVA_XDI_MBOX_WAIT_XLOG
mdefine_line|#define DIVA_XDI_MBOX_WAIT_XLOG&t;2
DECL|struct|_xdi_mbox_t
r_typedef
r_struct
id|_xdi_mbox_t
(brace
DECL|member|status
id|dword
id|status
suffix:semicolon
DECL|member|cmd_data
id|diva_xdi_um_cfg_cmd_data_t
id|cmd_data
suffix:semicolon
DECL|member|data_length
id|dword
id|data_length
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|typedef|xdi_mbox_t
)brace
id|xdi_mbox_t
suffix:semicolon
DECL|struct|_diva_os_idi_adapter_interface
r_typedef
r_struct
id|_diva_os_idi_adapter_interface
(brace
DECL|member|cleanup_adapter_proc
id|diva_init_card_proc_t
id|cleanup_adapter_proc
suffix:semicolon
DECL|member|cmd_proc
id|diva_cmd_card_proc_t
id|cmd_proc
suffix:semicolon
DECL|typedef|diva_os_idi_adapter_interface_t
)brace
id|diva_os_idi_adapter_interface_t
suffix:semicolon
DECL|struct|_diva_os_xdi_adapter
r_typedef
r_struct
id|_diva_os_xdi_adapter
(brace
DECL|member|link
id|diva_entity_link_t
id|link
suffix:semicolon
DECL|member|CardIndex
r_int
id|CardIndex
suffix:semicolon
DECL|member|CardOrdinal
r_int
id|CardOrdinal
suffix:semicolon
DECL|member|controller
r_int
id|controller
suffix:semicolon
multiline_comment|/* number of this controller */
DECL|member|Bus
r_int
id|Bus
suffix:semicolon
multiline_comment|/* PCI, ISA, ... */
DECL|member|resources
id|divas_card_resources_t
id|resources
suffix:semicolon
DECL|member|port_name
r_char
id|port_name
(braket
l_int|24
)braket
suffix:semicolon
DECL|member|xdi_adapter
id|ISDN_ADAPTER
id|xdi_adapter
suffix:semicolon
DECL|member|xdi_mbox
id|xdi_mbox_t
id|xdi_mbox
suffix:semicolon
DECL|member|interface
id|diva_os_idi_adapter_interface_t
id|interface
suffix:semicolon
DECL|member|slave_adapters
r_struct
id|_diva_os_xdi_adapter
op_star
id|slave_adapters
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|slave_list
r_void
op_star
id|slave_list
suffix:semicolon
DECL|member|proc_adapter_dir
r_void
op_star
id|proc_adapter_dir
suffix:semicolon
multiline_comment|/* adapterX proc entry */
DECL|member|proc_info
r_void
op_star
id|proc_info
suffix:semicolon
multiline_comment|/* info proc entry     */
DECL|member|proc_grp_opt
r_void
op_star
id|proc_grp_opt
suffix:semicolon
multiline_comment|/* group_optimization  */
DECL|member|proc_d_l1_down
r_void
op_star
id|proc_d_l1_down
suffix:semicolon
multiline_comment|/* dynamic_l1_down     */
DECL|member|clear_interrupts_proc
r_volatile
id|diva_xdi_clear_interrupts_proc_t
id|clear_interrupts_proc
suffix:semicolon
DECL|member|dsp_mask
id|dword
id|dsp_mask
suffix:semicolon
DECL|typedef|diva_os_xdi_adapter_t
)brace
id|diva_os_xdi_adapter_t
suffix:semicolon
macro_line|#endif
eof
