multiline_comment|/*&n; * NS16550 Serial Port&n; */
DECL|struct|NS16550
r_struct
id|NS16550
(brace
DECL|member|rbr
r_int
r_char
id|rbr
suffix:semicolon
multiline_comment|/* 0 */
DECL|member|ier
r_int
r_char
id|ier
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|fcr
r_int
r_char
id|fcr
suffix:semicolon
multiline_comment|/* 2 */
DECL|member|lcr
r_int
r_char
id|lcr
suffix:semicolon
multiline_comment|/* 3 */
DECL|member|mcr
r_int
r_char
id|mcr
suffix:semicolon
multiline_comment|/* 4 */
DECL|member|lsr
r_int
r_char
id|lsr
suffix:semicolon
multiline_comment|/* 5 */
DECL|member|msr
r_int
r_char
id|msr
suffix:semicolon
multiline_comment|/* 6 */
DECL|member|scr
r_int
r_char
id|scr
suffix:semicolon
multiline_comment|/* 7 */
)brace
suffix:semicolon
DECL|macro|thr
mdefine_line|#define thr rbr
DECL|macro|iir
mdefine_line|#define iir fcr
DECL|macro|dll
mdefine_line|#define dll rbr
DECL|macro|dlm
mdefine_line|#define dlm ier
DECL|macro|LSR_DR
mdefine_line|#define LSR_DR   0x01  /* Data ready */
DECL|macro|LSR_OE
mdefine_line|#define LSR_OE   0x02  /* Overrun */
DECL|macro|LSR_PE
mdefine_line|#define LSR_PE   0x04  /* Parity error */
DECL|macro|LSR_FE
mdefine_line|#define LSR_FE   0x08  /* Framing error */
DECL|macro|LSR_BI
mdefine_line|#define LSR_BI   0x10  /* Break */
DECL|macro|LSR_THRE
mdefine_line|#define LSR_THRE 0x20  /* Xmit holding register empty */
DECL|macro|LSR_TEMT
mdefine_line|#define LSR_TEMT 0x40  /* Xmitter empty */
DECL|macro|LSR_ERR
mdefine_line|#define LSR_ERR  0x80  /* Error */
DECL|macro|COM1
mdefine_line|#define COM1 0x800003F8
DECL|macro|COM2
mdefine_line|#define COM2 0x800002F8
DECL|macro|COM3
mdefine_line|#define COM3 0x800003F8
DECL|macro|COM4
mdefine_line|#define COM4 0x80000388
eof
