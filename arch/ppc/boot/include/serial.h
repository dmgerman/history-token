multiline_comment|/*&n; * A really private header file for the (dumb) serial driver in arch/ppc/boot&n; *&n; * Shamelessly taken from include/linux/serialP.h:&n; *&n; * Copyright (C) 1997 by Theodore Ts&squot;o.&n; *&n; * Redistribution of this file is permitted under the terms of the GNU&n; * Public License (GPL)&n; */
macro_line|#ifndef _PPC_BOOT_SERIALP_H
DECL|macro|_PPC_BOOT_SERIALP_H
mdefine_line|#define _PPC_BOOT_SERIALP_H
multiline_comment|/*&n; * This is our internal structure for each serial port&squot;s state.&n; *&n; * Many fields are paralleled by the structure used by the serial_struct&n; * structure.&n; *&n; * Given that this is how SERIAL_PORT_DFNS are done, and that we need&n; * to use a few of their fields, we need to have our own copy of it.&n; */
DECL|struct|serial_state
r_struct
id|serial_state
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|baud_base
r_int
id|baud_base
suffix:semicolon
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|hub6
r_int
id|hub6
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|line
r_int
id|line
suffix:semicolon
DECL|member|revision
r_int
id|revision
suffix:semicolon
multiline_comment|/* Chip revision (950) */
DECL|member|xmit_fifo_size
r_int
id|xmit_fifo_size
suffix:semicolon
DECL|member|custom_divisor
r_int
id|custom_divisor
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|iomem_base
id|u8
op_star
id|iomem_base
suffix:semicolon
DECL|member|iomem_reg_shift
id|u16
id|iomem_reg_shift
suffix:semicolon
DECL|member|close_delay
r_int
r_int
id|close_delay
suffix:semicolon
DECL|member|closing_wait
r_int
r_int
id|closing_wait
suffix:semicolon
multiline_comment|/* time to wait before closing */
DECL|member|icount
r_int
r_int
id|icount
suffix:semicolon
DECL|member|io_type
r_int
id|io_type
suffix:semicolon
DECL|member|info
r_void
op_star
id|info
suffix:semicolon
DECL|member|dev
r_void
op_star
id|dev
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _PPC_BOOT_SERIAL_H */
eof
