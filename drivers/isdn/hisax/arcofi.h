multiline_comment|/* $Id: arcofi.h,v 1.6.6.2 2001/09/23 22:24:46 kai Exp $&n; *&n; * Ansteuerung ARCOFI 2165&n; *&n; * Author       Karsten Keil&n; * Copyright    by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
DECL|macro|ARCOFI_USE
mdefine_line|#define ARCOFI_USE&t;1
multiline_comment|/* states */
DECL|macro|ARCOFI_NOP
mdefine_line|#define ARCOFI_NOP&t;0
DECL|macro|ARCOFI_TRANSMIT
mdefine_line|#define ARCOFI_TRANSMIT&t;1
DECL|macro|ARCOFI_RECEIVE
mdefine_line|#define ARCOFI_RECEIVE&t;2
multiline_comment|/* events */
DECL|macro|ARCOFI_START
mdefine_line|#define ARCOFI_START&t;1
DECL|macro|ARCOFI_TX_END
mdefine_line|#define ARCOFI_TX_END&t;2
DECL|macro|ARCOFI_RX_END
mdefine_line|#define ARCOFI_RX_END&t;3
DECL|macro|ARCOFI_TIMEOUT
mdefine_line|#define ARCOFI_TIMEOUT&t;4
r_extern
r_int
id|arcofi_fsm
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|event
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_void
id|init_arcofi
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
r_extern
r_void
id|clear_arcofi
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
eof
