multiline_comment|/* RS-485 structures */
multiline_comment|/* RS-485 support */
multiline_comment|/* Used with ioctl() TIOCSERSETRS485 */
DECL|struct|rs485_control
r_struct
id|rs485_control
(brace
DECL|member|rts_on_send
r_int
r_int
id|rts_on_send
suffix:semicolon
DECL|member|rts_after_sent
r_int
r_int
id|rts_after_sent
suffix:semicolon
DECL|member|delay_rts_before_send
r_int
r_int
id|delay_rts_before_send
suffix:semicolon
DECL|member|enabled
r_int
r_int
id|enabled
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|member|disable_serial_loopback
r_int
id|disable_serial_loopback
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* Used with ioctl() TIOCSERWRRS485 */
DECL|struct|rs485_write
r_struct
id|rs485_write
(brace
DECL|member|outc_size
r_int
r_int
id|outc_size
suffix:semicolon
DECL|member|outc
r_int
r_char
op_star
id|outc
suffix:semicolon
)brace
suffix:semicolon
eof
