multiline_comment|/* $Id: pci_impl.h,v 1.9 2001/06/13 06:34:30 davem Exp $&n; * pci_impl.h: Helper definitions for PCI controller support.&n; *&n; * Copyright (C) 1999 David S. Miller (davem@redhat.com)&n; */
macro_line|#ifndef PCI_IMPL_H
DECL|macro|PCI_IMPL_H
mdefine_line|#define PCI_IMPL_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/io.h&gt;
r_extern
r_struct
id|pci_controller_info
op_star
id|pci_controller_root
suffix:semicolon
r_extern
r_int
id|pci_num_controllers
suffix:semicolon
multiline_comment|/* PCI bus scanning and fixup support. */
r_extern
r_void
id|pci_fixup_host_bridge_self
c_func
(paren
r_struct
id|pci_bus
op_star
id|pbus
)paren
suffix:semicolon
r_extern
r_void
id|pci_fill_in_pbm_cookies
c_func
(paren
r_struct
id|pci_bus
op_star
id|pbus
comma
r_struct
id|pci_pbm_info
op_star
id|pbm
comma
r_int
id|prom_node
)paren
suffix:semicolon
r_extern
r_void
id|pci_record_assignments
c_func
(paren
r_struct
id|pci_pbm_info
op_star
id|pbm
comma
r_struct
id|pci_bus
op_star
id|pbus
)paren
suffix:semicolon
r_extern
r_void
id|pci_assign_unassigned
c_func
(paren
r_struct
id|pci_pbm_info
op_star
id|pbm
comma
r_struct
id|pci_bus
op_star
id|pbus
)paren
suffix:semicolon
r_extern
r_void
id|pci_fixup_irq
c_func
(paren
r_struct
id|pci_pbm_info
op_star
id|pbm
comma
r_struct
id|pci_bus
op_star
id|pbus
)paren
suffix:semicolon
r_extern
r_void
id|pci_determine_66mhz_disposition
c_func
(paren
r_struct
id|pci_pbm_info
op_star
id|pbm
comma
r_struct
id|pci_bus
op_star
id|pbus
)paren
suffix:semicolon
r_extern
r_void
id|pci_setup_busmastering
c_func
(paren
r_struct
id|pci_pbm_info
op_star
id|pbm
comma
r_struct
id|pci_bus
op_star
id|pbus
)paren
suffix:semicolon
r_extern
r_void
id|pci_register_legacy_regions
c_func
(paren
r_struct
id|resource
op_star
id|io_res
comma
r_struct
id|resource
op_star
id|mem_res
)paren
suffix:semicolon
multiline_comment|/* Error reporting support. */
r_extern
r_void
id|pci_scan_for_target_abort
c_func
(paren
r_struct
id|pci_controller_info
op_star
comma
r_struct
id|pci_pbm_info
op_star
comma
r_struct
id|pci_bus
op_star
)paren
suffix:semicolon
r_extern
r_void
id|pci_scan_for_master_abort
c_func
(paren
r_struct
id|pci_controller_info
op_star
comma
r_struct
id|pci_pbm_info
op_star
comma
r_struct
id|pci_bus
op_star
)paren
suffix:semicolon
r_extern
r_void
id|pci_scan_for_parity_error
c_func
(paren
r_struct
id|pci_controller_info
op_star
comma
r_struct
id|pci_pbm_info
op_star
comma
r_struct
id|pci_bus
op_star
)paren
suffix:semicolon
multiline_comment|/* Configuration space access. */
r_extern
r_void
id|pci_config_read8
c_func
(paren
id|u8
op_star
id|addr
comma
id|u8
op_star
id|ret
)paren
suffix:semicolon
r_extern
r_void
id|pci_config_read16
c_func
(paren
id|u16
op_star
id|addr
comma
id|u16
op_star
id|ret
)paren
suffix:semicolon
r_extern
r_void
id|pci_config_read32
c_func
(paren
id|u32
op_star
id|addr
comma
id|u32
op_star
id|ret
)paren
suffix:semicolon
r_extern
r_void
id|pci_config_write8
c_func
(paren
id|u8
op_star
id|addr
comma
id|u8
id|val
)paren
suffix:semicolon
r_extern
r_void
id|pci_config_write16
c_func
(paren
id|u16
op_star
id|addr
comma
id|u16
id|val
)paren
suffix:semicolon
r_extern
r_void
id|pci_config_write32
c_func
(paren
id|u32
op_star
id|addr
comma
id|u32
id|val
)paren
suffix:semicolon
macro_line|#endif /* !(PCI_IMPL_H) */
eof
