multiline_comment|/* suncore.h&n; *&n; * Generic SUN serial/kbd/ms layer.  Based entirely&n; * upon drivers/sbus/char/sunserial.h which is:&n; *&n; * Copyright (C) 1997  Eddie C. Dost  (ecd@skynet.be)&n; *&n; * Port to new UART layer is:&n; *&n; * Copyright (C) 2002 David S. Miller (davem@redhat.com)&n; */
macro_line|#ifndef _SERIAL_SUN_H
DECL|macro|_SERIAL_SUN_H
mdefine_line|#define _SERIAL_SUN_H
multiline_comment|/* Serial keyboard defines for L1-A processing... */
DECL|macro|SUNKBD_RESET
mdefine_line|#define SUNKBD_RESET&t;&t;0xff
DECL|macro|SUNKBD_L1
mdefine_line|#define SUNKBD_L1&t;&t;0x01
DECL|macro|SUNKBD_UP
mdefine_line|#define SUNKBD_UP&t;&t;0x80
DECL|macro|SUNKBD_A
mdefine_line|#define SUNKBD_A&t;&t;0x4d
r_extern
r_int
r_int
id|suncore_mouse_baud_cflag_next
c_func
(paren
r_int
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|suncore_mouse_baud_detection
c_func
(paren
r_int
r_char
comma
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|pt_regs
op_star
id|kbd_pt_regs
suffix:semicolon
r_extern
r_int
id|serial_console
suffix:semicolon
r_extern
r_int
id|stop_a_enabled
suffix:semicolon
r_extern
r_int
id|sunserial_current_minor
suffix:semicolon
DECL|function|con_is_present
r_static
id|__inline__
r_int
id|con_is_present
c_func
(paren
r_void
)paren
(brace
r_return
id|serial_console
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
r_extern
r_void
id|sunserial_console_termios
c_func
(paren
r_struct
id|console
op_star
)paren
suffix:semicolon
macro_line|#endif /* !(_SERIAL_SUN_H) */
eof
