multiline_comment|/*&n; * include/asm-sh/io_mpc1211.h&n; *&n; * Copyright 2001 Saito.K &amp; Jeanne&n; *&n; * IO functions for an Interface MPC-1211&n; */
macro_line|#ifndef _ASM_SH_IO_MPC1211_H
DECL|macro|_ASM_SH_IO_MPC1211_H
mdefine_line|#define _ASM_SH_IO_MPC1211_H
macro_line|#include &lt;linux/time.h&gt;
r_extern
r_int
id|mpc1211_irq_demux
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|init_mpc1211_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|heartbeat_mpc1211
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mpc1211_rtc_gettimeofday
c_func
(paren
r_struct
id|timeval
op_star
id|tv
)paren
suffix:semicolon
r_extern
r_int
id|mpc1211_rtc_settimeofday
c_func
(paren
r_const
r_struct
id|timeval
op_star
id|tv
)paren
suffix:semicolon
macro_line|#endif /* _ASM_SH_IO_MPC1211_H */
eof
