multiline_comment|/* $Id: isdnl3.h,v 2.6.6.2 2001/09/23 22:24:49 kai Exp $&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
DECL|macro|SBIT
mdefine_line|#define SBIT(state) (1&lt;&lt;state)
DECL|macro|ALL_STATES
mdefine_line|#define ALL_STATES  0x03ffffff
DECL|macro|PROTO_DIS_EURO
mdefine_line|#define PROTO_DIS_EURO&t;0x08
DECL|macro|L3_DEB_WARN
mdefine_line|#define L3_DEB_WARN&t;0x01
DECL|macro|L3_DEB_PROTERR
mdefine_line|#define L3_DEB_PROTERR&t;0x02
DECL|macro|L3_DEB_STATE
mdefine_line|#define L3_DEB_STATE&t;0x04
DECL|macro|L3_DEB_CHARGE
mdefine_line|#define L3_DEB_CHARGE&t;0x08
DECL|macro|L3_DEB_CHECK
mdefine_line|#define L3_DEB_CHECK&t;0x10
DECL|macro|L3_DEB_SI
mdefine_line|#define L3_DEB_SI&t;0x20
DECL|struct|stateentry
r_struct
id|stateentry
(brace
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|primitive
r_int
id|primitive
suffix:semicolon
DECL|member|rout
r_void
(paren
op_star
id|rout
)paren
(paren
r_struct
id|l3_process
op_star
comma
id|u_char
comma
r_void
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|l3_debug
mdefine_line|#define l3_debug(st, fmt, args...) HiSax_putstatus(st-&gt;l1.hardware, &quot;l3 &quot;, fmt, ## args)
r_extern
r_void
id|newl3state
c_func
(paren
r_struct
id|l3_process
op_star
id|pc
comma
r_int
id|state
)paren
suffix:semicolon
r_extern
r_void
id|L3InitTimer
c_func
(paren
r_struct
id|l3_process
op_star
id|pc
comma
r_struct
id|L3Timer
op_star
id|t
)paren
suffix:semicolon
r_extern
r_void
id|L3DelTimer
c_func
(paren
r_struct
id|L3Timer
op_star
id|t
)paren
suffix:semicolon
r_extern
r_int
id|L3AddTimer
c_func
(paren
r_struct
id|L3Timer
op_star
id|t
comma
r_int
id|millisec
comma
r_int
id|event
)paren
suffix:semicolon
r_extern
r_void
id|StopAllL3Timer
c_func
(paren
r_struct
id|l3_process
op_star
id|pc
)paren
suffix:semicolon
r_extern
r_struct
id|sk_buff
op_star
id|l3_alloc_skb
c_func
(paren
r_int
id|len
)paren
suffix:semicolon
r_extern
r_struct
id|l3_process
op_star
id|new_l3_process
c_func
(paren
r_struct
id|PStack
op_star
id|st
comma
r_int
id|cr
)paren
suffix:semicolon
r_extern
r_void
id|release_l3_process
c_func
(paren
r_struct
id|l3_process
op_star
id|p
)paren
suffix:semicolon
r_extern
r_struct
id|l3_process
op_star
id|getl3proc
c_func
(paren
r_struct
id|PStack
op_star
id|st
comma
r_int
id|cr
)paren
suffix:semicolon
r_extern
r_void
id|l3_msg
c_func
(paren
r_struct
id|PStack
op_star
id|st
comma
r_int
id|pr
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
eof
