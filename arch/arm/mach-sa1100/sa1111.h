multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/sa1111.h&n; */
r_struct
id|device
suffix:semicolon
multiline_comment|/*&n; * Probe for a SA1111 chip.&n; */
r_extern
r_int
id|sa1111_init
c_func
(paren
r_struct
id|device
op_star
id|parent
comma
r_int
r_int
id|phys
comma
r_int
r_int
id|irq
)paren
suffix:semicolon
multiline_comment|/*&n; * Wake up a SA1111 chip.&n; */
r_extern
r_void
id|sa1111_wake
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Doze the SA1111 chip.&n; */
r_extern
r_void
id|sa1111_doze
c_func
(paren
r_void
)paren
suffix:semicolon
eof
