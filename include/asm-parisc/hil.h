macro_line|#ifndef _ASM_HIL_H
DECL|macro|_ASM_HIL_H
mdefine_line|#define _ASM_HIL_H
multiline_comment|/*&n; *&t;linux/asm-parisc/hil.h&n; *&n; *&t;(c) 1999 Matthew Wilcox&n; */
r_extern
r_int
r_int
id|hil_base
suffix:semicolon
multiline_comment|/* declared in drivers/gsc/hil.c */
r_extern
r_int
r_int
id|hil_irq
suffix:semicolon
DECL|macro|HILBASE
mdefine_line|#define HILBASE&t;&t;&t;hil_base /* 0xf0821000 (old) or 0xf0201000 (new) */
DECL|macro|HIL_DATA
mdefine_line|#define HIL_DATA&t;&t;0x800
DECL|macro|HIL_CMD
mdefine_line|#define HIL_CMD&t;&t;&t;0x801
DECL|macro|HIL_IRQ
mdefine_line|#define HIL_IRQ&t;&t;&t;hil_irq
DECL|macro|hil_busy
mdefine_line|#define hil_busy()&t;&t;(gsc_readb(HILBASE + HIL_CMD) &amp; HIL_BUSY)
DECL|macro|hil_data_available
mdefine_line|#define hil_data_available()&t;(gsc_readb(HILBASE + HIL_CMD) &amp; HIL_DATA_RDY)
DECL|macro|hil_status
mdefine_line|#define hil_status()&t;&t;(gsc_readb(HILBASE + HIL_CMD))
DECL|macro|hil_command
mdefine_line|#define hil_command(x)&t;&t;do { gsc_writeb((x), HILBASE + HIL_CMD); } while (0)
DECL|macro|hil_read_data
mdefine_line|#define hil_read_data()&t;&t;(gsc_readb(HILBASE + HIL_DATA))
DECL|macro|hil_write_data
mdefine_line|#define hil_write_data(x)&t;do { gsc_writeb((x), HILBASE + HIL_DATA); } while (0)
macro_line|#endif
eof
