multiline_comment|/*&t;From uart401.c */
r_int
id|probe_uart401
(paren
r_struct
id|address_info
op_star
id|hw_config
comma
r_struct
id|module
op_star
id|owner
)paren
suffix:semicolon
r_void
id|unload_uart401
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
id|irqreturn_t
id|uart401intr
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|dummy
)paren
suffix:semicolon
multiline_comment|/*&t;From mpu401.c */
r_int
id|probe_mpu401
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
r_int
id|attach_mpu401
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
comma
r_struct
id|module
op_star
id|owner
)paren
suffix:semicolon
r_void
id|unload_mpu401
c_func
(paren
r_struct
id|address_info
op_star
id|hw_info
)paren
suffix:semicolon
r_int
id|intchk_mpu401
c_func
(paren
r_void
op_star
id|dev_id
)paren
suffix:semicolon
id|irqreturn_t
id|mpuintr
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|dummy
)paren
suffix:semicolon
eof
