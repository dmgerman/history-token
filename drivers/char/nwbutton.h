macro_line|#ifndef __NWBUTTON_H
DECL|macro|__NWBUTTON_H
mdefine_line|#define __NWBUTTON_H
multiline_comment|/*&n; * &t;NetWinder Button Driver-&n; *&t;Copyright (C) Alex Holden &lt;alex@linuxhacker.org&gt; 1998, 1999.&n; */
macro_line|#ifdef __NWBUTTON_C&t;/* Actually compiling the driver itself */
multiline_comment|/* Various defines: */
DECL|macro|NUM_PRESSES_REBOOT
mdefine_line|#define NUM_PRESSES_REBOOT 2&t;/* How many presses to activate shutdown */
DECL|macro|BUTTON_DELAY
mdefine_line|#define BUTTON_DELAY 30 &t;/* How many jiffies for sequence to end */
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;0.3&quot;&t;&t;/* Driver version number */
DECL|macro|BUTTON_MINOR
mdefine_line|#define BUTTON_MINOR 158&t;/* Major 10, Minor 158, /dev/nwbutton */
multiline_comment|/* Structure definitions: */
DECL|struct|button_callback
r_struct
id|button_callback
(brace
DECL|member|callback
r_void
(paren
op_star
id|callback
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Function prototypes: */
r_static
r_void
id|button_sequence_finished
(paren
r_int
r_int
id|parameters
)paren
suffix:semicolon
r_static
id|irqreturn_t
id|button_handler
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
id|regs
)paren
suffix:semicolon
r_int
id|button_init
(paren
r_void
)paren
suffix:semicolon
r_int
id|button_add_callback
(paren
r_void
(paren
op_star
id|callback
)paren
(paren
r_void
)paren
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|button_del_callback
(paren
r_void
(paren
op_star
id|callback
)paren
(paren
r_void
)paren
)paren
suffix:semicolon
r_static
r_void
id|button_consume_callbacks
(paren
r_int
id|bpcount
)paren
suffix:semicolon
macro_line|#else /* Not compiling the driver itself */
r_extern
r_int
id|button_add_callback
(paren
r_void
(paren
op_star
id|callback
)paren
(paren
r_void
)paren
comma
r_int
id|count
)paren
suffix:semicolon
r_extern
r_int
id|button_del_callback
(paren
r_void
(paren
op_star
id|callback
)paren
(paren
r_void
)paren
)paren
suffix:semicolon
macro_line|#endif /* __NWBUTTON_C */
macro_line|#endif /* __NWBUTTON_H */
eof
