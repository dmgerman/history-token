r_extern
r_struct
id|bus_type
id|pnp_bus_type
suffix:semicolon
r_extern
id|spinlock_t
id|pnp_lock
suffix:semicolon
r_void
op_star
id|pnp_alloc
c_func
(paren
r_int
id|size
)paren
suffix:semicolon
r_int
id|pnp_interface_attach_device
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|pnp_fixup_device
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|pnp_free_option
c_func
(paren
r_struct
id|pnp_option
op_star
id|option
)paren
suffix:semicolon
r_int
id|__pnp_add_device
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|__pnp_remove_device
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|pnp_check_port
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|idx
)paren
suffix:semicolon
r_int
id|pnp_check_mem
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|idx
)paren
suffix:semicolon
r_int
id|pnp_check_irq
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|idx
)paren
suffix:semicolon
r_int
id|pnp_check_dma
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|idx
)paren
suffix:semicolon
eof
