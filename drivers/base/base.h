DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DBG
macro_line|# define DBG(x...) printk(x)
macro_line|#else
DECL|macro|DBG
macro_line|# define DBG(x...)
macro_line|#endif
r_extern
r_struct
id|device
id|device_root
suffix:semicolon
r_extern
id|spinlock_t
id|device_lock
suffix:semicolon
r_extern
r_int
id|bus_add_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|bus_remove_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|device_create_dir
c_func
(paren
r_struct
id|driver_dir_entry
op_star
id|dir
comma
r_struct
id|driver_dir_entry
op_star
id|parent
)paren
suffix:semicolon
r_extern
r_int
id|device_make_dir
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|device_remove_dir
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|device_bus_link
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
eof
