multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/sa1111.h&n; */
multiline_comment|/*&n; * Probe for a SA1111 chip.&n; */
r_extern
r_int
id|sa1111_probe
c_func
(paren
r_int
r_int
id|phys
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
multiline_comment|/*&n; * Configure the SA1111 shared memory controller.&n; */
r_extern
r_void
id|sa1111_configure_smc
c_func
(paren
r_int
id|sdram
comma
r_int
r_int
id|drac
comma
r_int
r_int
id|cas_latency
)paren
suffix:semicolon
r_extern
r_void
id|sa1111_init_irq
c_func
(paren
r_int
id|irq_nr
)paren
suffix:semicolon
eof
