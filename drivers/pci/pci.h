multiline_comment|/* Functions internal to the PCI core code */
r_extern
r_int
id|pci_hotplug
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
op_star
id|envp
comma
r_int
id|num_envp
comma
r_char
op_star
id|buffer
comma
r_int
id|buffer_size
)paren
suffix:semicolon
r_extern
r_void
id|pci_create_sysfs_dev_files
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
suffix:semicolon
r_extern
r_int
id|pci_bus_alloc_resource
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_struct
id|resource
op_star
id|res
comma
r_int
r_int
id|size
comma
r_int
r_int
id|align
comma
r_int
r_int
id|min
comma
r_int
r_int
id|type_mask
comma
r_void
(paren
op_star
id|alignf
)paren
(paren
r_void
op_star
comma
r_struct
id|resource
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
comma
r_void
op_star
id|alignf_data
)paren
suffix:semicolon
multiline_comment|/* PCI /proc functions */
macro_line|#ifdef CONFIG_PROC_FS
r_extern
r_int
id|pci_proc_attach_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|pci_proc_detach_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|pci_proc_attach_bus
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
id|pci_proc_detach_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
suffix:semicolon
macro_line|#else
DECL|function|pci_proc_attach_device
r_static
r_inline
r_int
id|pci_proc_attach_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_proc_detach_device
r_static
r_inline
r_int
id|pci_proc_detach_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_proc_attach_bus
r_static
r_inline
r_int
id|pci_proc_attach_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_proc_detach_bus
r_static
r_inline
r_int
id|pci_proc_detach_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Functions for PCI Hotplug drivers to use */
r_extern
r_struct
id|pci_bus
op_star
id|pci_add_new_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|parent
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|busnr
)paren
suffix:semicolon
r_extern
r_int
r_int
id|pci_do_scan_bus
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
id|pci_remove_device_safe
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
r_char
id|pci_max_busnr
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_char
id|pci_bus_max_busnr
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
id|pci_bus_find_capability
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|cap
)paren
suffix:semicolon
DECL|struct|pci_dev_wrapped
r_struct
id|pci_dev_wrapped
(brace
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pci_bus_wrapped
r_struct
id|pci_bus_wrapped
(brace
DECL|member|bus
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pci_visit
r_struct
id|pci_visit
(brace
DECL|member|pre_visit_pci_bus
r_int
(paren
op_star
id|pre_visit_pci_bus
)paren
(paren
r_struct
id|pci_bus_wrapped
op_star
comma
r_struct
id|pci_dev_wrapped
op_star
)paren
suffix:semicolon
DECL|member|post_visit_pci_bus
r_int
(paren
op_star
id|post_visit_pci_bus
)paren
(paren
r_struct
id|pci_bus_wrapped
op_star
comma
r_struct
id|pci_dev_wrapped
op_star
)paren
suffix:semicolon
DECL|member|pre_visit_pci_dev
r_int
(paren
op_star
id|pre_visit_pci_dev
)paren
(paren
r_struct
id|pci_dev_wrapped
op_star
comma
r_struct
id|pci_bus_wrapped
op_star
)paren
suffix:semicolon
DECL|member|visit_pci_dev
r_int
(paren
op_star
id|visit_pci_dev
)paren
(paren
r_struct
id|pci_dev_wrapped
op_star
comma
r_struct
id|pci_bus_wrapped
op_star
)paren
suffix:semicolon
DECL|member|post_visit_pci_dev
r_int
(paren
op_star
id|post_visit_pci_dev
)paren
(paren
r_struct
id|pci_dev_wrapped
op_star
comma
r_struct
id|pci_bus_wrapped
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|pci_visit_dev
c_func
(paren
r_struct
id|pci_visit
op_star
id|fn
comma
r_struct
id|pci_dev_wrapped
op_star
id|wrapped_dev
comma
r_struct
id|pci_bus_wrapped
op_star
id|wrapped_parent
)paren
suffix:semicolon
multiline_comment|/* Lock for read/write access to pci device and bus lists */
r_extern
id|spinlock_t
id|pci_bus_lock
suffix:semicolon
eof
