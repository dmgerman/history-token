multiline_comment|/* $Id: diva_pci.h,v 1.6 2003/01/04 15:29:45 schindler Exp $ */
macro_line|#ifndef __DIVA_PCI_INTERFACE_H__
DECL|macro|__DIVA_PCI_INTERFACE_H__
mdefine_line|#define __DIVA_PCI_INTERFACE_H__
r_void
op_star
id|divasa_remap_pci_bar
c_func
(paren
id|diva_os_xdi_adapter_t
op_star
id|a
comma
r_int
id|id
comma
r_int
r_int
id|bar
comma
r_int
r_int
id|area_length
)paren
suffix:semicolon
r_void
id|divasa_unmap_pci_bar
c_func
(paren
r_void
op_star
id|bar
)paren
suffix:semicolon
r_int
r_int
id|divasa_get_pci_irq
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|func
comma
r_void
op_star
id|pci_dev_handle
)paren
suffix:semicolon
r_int
r_int
id|divasa_get_pci_bar
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|func
comma
r_int
id|bar
comma
r_void
op_star
id|pci_dev_handle
)paren
suffix:semicolon
id|byte
id|diva_os_get_pci_bus
c_func
(paren
r_void
op_star
id|pci_dev_handle
)paren
suffix:semicolon
id|byte
id|diva_os_get_pci_func
c_func
(paren
r_void
op_star
id|pci_dev_handle
)paren
suffix:semicolon
macro_line|#endif
eof
