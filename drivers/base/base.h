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
eof
