macro_line|#ifndef __HISAX_ISAC_H__
DECL|macro|__HISAX_ISAC_H__
mdefine_line|#define __HISAX_ISAC_H__
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &quot;fsm.h&quot;
macro_line|#include &quot;hisax_if.h&quot;
DECL|macro|TIMER3_VALUE
mdefine_line|#define TIMER3_VALUE 7000
DECL|macro|MAX_DFRAME_LEN_L1
mdefine_line|#define MAX_DFRAME_LEN_L1 300
DECL|macro|ISAC_IOM1
mdefine_line|#define ISAC_IOM1&t;0
DECL|struct|isac
r_struct
id|isac
(brace
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
DECL|member|flags
id|u_long
id|flags
suffix:semicolon
DECL|member|hisax_d_if
r_struct
id|hisax_d_if
id|hisax_d_if
suffix:semicolon
DECL|member|l1m
r_struct
id|FsmInst
id|l1m
suffix:semicolon
DECL|member|timer
r_struct
id|FsmTimer
id|timer
suffix:semicolon
DECL|member|mocr
id|u_char
id|mocr
suffix:semicolon
DECL|member|adf2
id|u_char
id|adf2
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|rcvbuf
id|u_char
id|rcvbuf
(braket
id|MAX_DFRAME_LEN_L1
)braket
suffix:semicolon
DECL|member|rcvidx
r_int
id|rcvidx
suffix:semicolon
DECL|member|tx_skb
r_struct
id|sk_buff
op_star
id|tx_skb
suffix:semicolon
DECL|member|tx_cnt
r_int
id|tx_cnt
suffix:semicolon
DECL|member|read_isac
id|u_char
(paren
op_star
id|read_isac
)paren
(paren
r_struct
id|isac
op_star
comma
id|u_char
)paren
suffix:semicolon
DECL|member|write_isac
r_void
(paren
op_star
id|write_isac
)paren
(paren
r_struct
id|isac
op_star
comma
id|u_char
comma
id|u_char
)paren
suffix:semicolon
DECL|member|read_isac_fifo
r_void
(paren
op_star
id|read_isac_fifo
)paren
(paren
r_struct
id|isac
op_star
comma
id|u_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|write_isac_fifo
r_void
(paren
op_star
id|write_isac_fifo
)paren
(paren
r_struct
id|isac
op_star
comma
id|u_char
op_star
comma
r_int
)paren
suffix:semicolon
)brace
suffix:semicolon
r_void
id|isac_init
c_func
(paren
r_struct
id|isac
op_star
id|isac
)paren
suffix:semicolon
r_void
id|isac_d_l2l1
c_func
(paren
r_struct
id|hisax_if
op_star
id|hisax_d_if
comma
r_int
id|pr
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_void
id|isac_setup
c_func
(paren
r_struct
id|isac
op_star
id|isac
)paren
suffix:semicolon
r_void
id|isac_irq
c_func
(paren
r_struct
id|isac
op_star
id|isac
)paren
suffix:semicolon
r_void
id|isacsx_setup
c_func
(paren
r_struct
id|isac
op_star
id|isac
)paren
suffix:semicolon
r_void
id|isacsx_irq
c_func
(paren
r_struct
id|isac
op_star
id|isac
)paren
suffix:semicolon
macro_line|#endif
eof