macro_line|#ifdef __KERNEL__
DECL|typedef|kobj_probe_t
r_typedef
r_struct
id|kobject
op_star
id|kobj_probe_t
c_func
(paren
id|dev_t
comma
r_int
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_struct
id|kobj_map
suffix:semicolon
r_int
id|kobj_map
c_func
(paren
r_struct
id|kobj_map
op_star
comma
id|dev_t
comma
r_int
r_int
comma
r_struct
id|module
op_star
comma
id|kobj_probe_t
op_star
comma
r_int
(paren
op_star
)paren
(paren
id|dev_t
comma
r_void
op_star
)paren
comma
r_void
op_star
)paren
suffix:semicolon
r_void
id|kobj_unmap
c_func
(paren
r_struct
id|kobj_map
op_star
comma
id|dev_t
comma
r_int
r_int
)paren
suffix:semicolon
r_struct
id|kobject
op_star
id|kobj_lookup
c_func
(paren
r_struct
id|kobj_map
op_star
comma
id|dev_t
comma
r_int
op_star
)paren
suffix:semicolon
r_struct
id|kobj_map
op_star
id|kobj_map_init
c_func
(paren
id|kobj_probe_t
op_star
comma
r_struct
id|semaphore
op_star
)paren
suffix:semicolon
macro_line|#endif
eof
