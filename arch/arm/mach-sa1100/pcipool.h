r_struct
id|pci_pool
op_star
id|pci_pool_create
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|size
comma
r_int
id|align
comma
r_int
id|allocation
comma
r_int
id|flags
)paren
suffix:semicolon
r_void
id|pci_pool_destroy
(paren
r_struct
id|pci_pool
op_star
id|pool
)paren
suffix:semicolon
r_void
op_star
id|pci_pool_alloc
(paren
r_struct
id|pci_pool
op_star
id|pool
comma
r_int
id|flags
comma
id|dma_addr_t
op_star
id|handle
)paren
suffix:semicolon
r_void
id|pci_pool_free
(paren
r_struct
id|pci_pool
op_star
id|pool
comma
r_void
op_star
id|vaddr
comma
id|dma_addr_t
id|addr
)paren
suffix:semicolon
eof
