macro_line|#ifndef __PPC_KERNEL_PCI_H__
DECL|macro|__PPC_KERNEL_PCI_H__
mdefine_line|#define __PPC_KERNEL_PCI_H__
r_extern
r_int
r_int
id|isa_io_base
suffix:semicolon
r_extern
r_int
r_int
id|isa_mem_base
suffix:semicolon
r_extern
r_int
r_int
id|pci_dram_offset
suffix:semicolon
r_extern
r_int
r_int
op_star
id|pci_config_address
suffix:semicolon
r_extern
r_int
r_char
op_star
id|pci_config_data
suffix:semicolon
r_void
id|fix_intr
c_func
(paren
r_struct
id|device_node
op_star
id|node
comma
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
macro_line|#if 0
mdefine_line|#define decl_config_access_method(name) &t;&bslash;&n;struct pci_ops name##_pci_ops = { &t;&t;&bslash;&n;&t;name##_pcibios_read_config_byte,&t;&bslash;&n;&t;name##_pcibios_read_config_word,&t;&bslash;&n;&t;name##_pcibios_read_config_dword,&t;&bslash;&n;&t;name##_pcibios_write_config_byte,&t;&bslash;&n;&t;name##_pcibios_write_config_word,&t;&bslash;&n;&t;name##_pcibios_write_config_dword&t;&bslash;&n;}
macro_line|#endif
DECL|macro|decl_config_access_method
mdefine_line|#define decl_config_access_method(name) &bslash;&n;extern int name##_pcibios_read_config_byte(unsigned char bus, &bslash;&n;&t;unsigned char dev_fn, unsigned char offset, unsigned char *val); &bslash;&n;extern int name##_pcibios_read_config_word(unsigned char bus, &bslash;&n;&t;unsigned char dev_fn, unsigned char offset, unsigned short *val); &bslash;&n;extern int name##_pcibios_read_config_dword(unsigned char bus, &bslash;&n;&t;unsigned char dev_fn, unsigned char offset, unsigned int *val); &bslash;&n;extern int name##_pcibios_write_config_byte(unsigned char bus, &bslash;&n;&t;unsigned char dev_fn, unsigned char offset, unsigned char val); &bslash;&n;extern int name##_pcibios_write_config_word(unsigned char bus, &bslash;&n;&t;unsigned char dev_fn, unsigned char offset, unsigned short val); &bslash;&n;extern int name##_pcibios_write_config_dword(unsigned char bus, &bslash;&n;&t;unsigned char dev_fn, unsigned char offset, unsigned int val)
DECL|macro|set_config_access_method
mdefine_line|#define set_config_access_method(name) &bslash;&n;&t;ppc_md.pcibios_read_config_byte = name##_pcibios_read_config_byte; &bslash;&n;&t;ppc_md.pcibios_read_config_word = name##_pcibios_read_config_word; &bslash;&n;&t;ppc_md.pcibios_read_config_dword = name##_pcibios_read_config_dword; &bslash;&n;&t;ppc_md.pcibios_write_config_byte = name##_pcibios_write_config_byte; &bslash;&n;&t;ppc_md.pcibios_write_config_word = name##_pcibios_write_config_word; &bslash;&n;&t;ppc_md.pcibios_write_config_dword = name##_pcibios_write_config_dword
macro_line|#endif /* __PPC_KERNEL_PCI_H__ */
eof
