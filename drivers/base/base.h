DECL|macro|DEBUG
macro_line|#undef DEBUG
r_extern
r_struct
id|semaphore
id|device_sem
suffix:semicolon
r_extern
r_struct
id|semaphore
id|devclass_sem
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
id|bus_add_driver
c_func
(paren
r_struct
id|device_driver
op_star
)paren
suffix:semicolon
r_extern
r_void
id|bus_remove_driver
c_func
(paren
r_struct
id|device_driver
op_star
)paren
suffix:semicolon
r_extern
r_int
id|devclass_add_device
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|devclass_remove_device
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|devclass_add_driver
c_func
(paren
r_struct
id|device_driver
op_star
)paren
suffix:semicolon
r_extern
r_void
id|devclass_remove_driver
c_func
(paren
r_struct
id|device_driver
op_star
)paren
suffix:semicolon
r_extern
r_int
id|interface_add_dev
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|interface_remove_dev
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HOTPLUG
r_extern
r_int
id|dev_hotplug
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_const
r_char
op_star
id|action
)paren
suffix:semicolon
r_extern
r_int
id|class_hotplug
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_const
r_char
op_star
id|action
)paren
suffix:semicolon
macro_line|#else
DECL|function|dev_hotplug
r_static
r_inline
r_int
id|dev_hotplug
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_const
r_char
op_star
id|action
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|class_hotplug
r_static
r_inline
r_int
id|class_hotplug
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_const
r_char
op_star
id|action
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
eof
