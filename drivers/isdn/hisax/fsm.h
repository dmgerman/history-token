multiline_comment|/* $Id: fsm.h,v 1.3.2.2 2001/09/23 22:24:47 kai Exp $&n; *&n; * Finite state machine&n; *&n; * Author       Karsten Keil&n; * Copyright    by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; *              by Kai Germaschewski &lt;kai.germaschewski@gmx.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#ifndef __FSM_H__
DECL|macro|__FSM_H__
mdefine_line|#define __FSM_H__
macro_line|#include &lt;linux/timer.h&gt;
r_struct
id|FsmInst
suffix:semicolon
DECL|typedef|FSMFNPTR
r_typedef
r_void
(paren
op_star
id|FSMFNPTR
)paren
(paren
r_struct
id|FsmInst
op_star
comma
r_int
comma
r_void
op_star
)paren
suffix:semicolon
DECL|struct|Fsm
r_struct
id|Fsm
(brace
DECL|member|jumpmatrix
id|FSMFNPTR
op_star
id|jumpmatrix
suffix:semicolon
DECL|member|state_count
DECL|member|event_count
r_int
id|state_count
comma
id|event_count
suffix:semicolon
DECL|member|strEvent
DECL|member|strState
r_char
op_star
op_star
id|strEvent
comma
op_star
op_star
id|strState
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|FsmInst
r_struct
id|FsmInst
(brace
DECL|member|fsm
r_struct
id|Fsm
op_star
id|fsm
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|debug
r_int
id|debug
suffix:semicolon
DECL|member|userdata
r_void
op_star
id|userdata
suffix:semicolon
DECL|member|userint
r_int
id|userint
suffix:semicolon
DECL|member|printdebug
r_void
(paren
op_star
id|printdebug
)paren
(paren
r_struct
id|FsmInst
op_star
comma
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|FsmNode
r_struct
id|FsmNode
(brace
DECL|member|state
DECL|member|event
r_int
id|state
comma
id|event
suffix:semicolon
DECL|member|routine
r_void
(paren
op_star
id|routine
)paren
(paren
r_struct
id|FsmInst
op_star
comma
r_int
comma
r_void
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|FsmTimer
r_struct
id|FsmTimer
(brace
DECL|member|fi
r_struct
id|FsmInst
op_star
id|fi
suffix:semicolon
DECL|member|tl
r_struct
id|timer_list
id|tl
suffix:semicolon
DECL|member|event
r_int
id|event
suffix:semicolon
DECL|member|arg
r_void
op_star
id|arg
suffix:semicolon
)brace
suffix:semicolon
r_int
id|FsmNew
c_func
(paren
r_struct
id|Fsm
op_star
id|fsm
comma
r_struct
id|FsmNode
op_star
id|fnlist
comma
r_int
id|fncount
)paren
suffix:semicolon
r_void
id|FsmFree
c_func
(paren
r_struct
id|Fsm
op_star
id|fsm
)paren
suffix:semicolon
r_int
id|FsmEvent
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_void
id|FsmChangeState
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_int
id|newstate
)paren
suffix:semicolon
r_void
id|FsmInitTimer
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_struct
id|FsmTimer
op_star
id|ft
)paren
suffix:semicolon
r_int
id|FsmAddTimer
c_func
(paren
r_struct
id|FsmTimer
op_star
id|ft
comma
r_int
id|millisec
comma
r_int
id|event
comma
r_void
op_star
id|arg
comma
r_int
id|where
)paren
suffix:semicolon
r_void
id|FsmRestartTimer
c_func
(paren
r_struct
id|FsmTimer
op_star
id|ft
comma
r_int
id|millisec
comma
r_int
id|event
comma
r_void
op_star
id|arg
comma
r_int
id|where
)paren
suffix:semicolon
r_void
id|FsmDelTimer
c_func
(paren
r_struct
id|FsmTimer
op_star
id|ft
comma
r_int
id|where
)paren
suffix:semicolon
macro_line|#endif
eof
