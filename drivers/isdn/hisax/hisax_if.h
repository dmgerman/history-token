macro_line|#ifndef __HISAX_IF_H__
DECL|macro|__HISAX_IF_H__
mdefine_line|#define __HISAX_IF_H__
macro_line|#include &lt;linux/skbuff.h&gt;
DECL|macro|REQUEST
mdefine_line|#define REQUEST&t;&t;0
DECL|macro|CONFIRM
mdefine_line|#define CONFIRM&t;&t;1
DECL|macro|INDICATION
mdefine_line|#define INDICATION&t;2
DECL|macro|RESPONSE
mdefine_line|#define RESPONSE&t;3
DECL|macro|PH_ACTIVATE
mdefine_line|#define PH_ACTIVATE&t;0x0100
DECL|macro|PH_DEACTIVATE
mdefine_line|#define PH_DEACTIVATE&t;0x0110
DECL|macro|PH_DATA
mdefine_line|#define PH_DATA&t;&t;0x0120
DECL|macro|PH_PULL
mdefine_line|#define PH_PULL&t;&t;0x0130
DECL|macro|PH_DATA_E
mdefine_line|#define PH_DATA_E&t;0x0140
DECL|macro|L1_MODE_NULL
mdefine_line|#define L1_MODE_NULL&t;0
DECL|macro|L1_MODE_TRANS
mdefine_line|#define L1_MODE_TRANS&t;1
DECL|macro|L1_MODE_HDLC
mdefine_line|#define L1_MODE_HDLC&t;2
DECL|macro|L1_MODE_EXTRN
mdefine_line|#define L1_MODE_EXTRN&t;3
DECL|macro|L1_MODE_HDLC_56K
mdefine_line|#define L1_MODE_HDLC_56K 4
DECL|macro|L1_MODE_MODEM
mdefine_line|#define L1_MODE_MODEM&t;7
DECL|macro|L1_MODE_V32
mdefine_line|#define L1_MODE_V32&t;8
DECL|macro|L1_MODE_FAX
mdefine_line|#define L1_MODE_FAX&t;9
DECL|struct|hisax_if
r_struct
id|hisax_if
(brace
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
singleline_comment|// private to driver
DECL|member|l1l2
r_void
(paren
op_star
id|l1l2
)paren
(paren
r_struct
id|hisax_if
op_star
comma
r_int
id|pr
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
DECL|member|l2l1
r_void
(paren
op_star
id|l2l1
)paren
(paren
r_struct
id|hisax_if
op_star
comma
r_int
id|pr
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hisax_b_if
r_struct
id|hisax_b_if
(brace
DECL|member|ifc
r_struct
id|hisax_if
id|ifc
suffix:semicolon
singleline_comment|// private to hisax
DECL|member|bcs
r_struct
id|BCState
op_star
id|bcs
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hisax_d_if
r_struct
id|hisax_d_if
(brace
DECL|member|ifc
r_struct
id|hisax_if
id|ifc
suffix:semicolon
singleline_comment|// private to hisax
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|cs
r_struct
id|IsdnCardState
op_star
id|cs
suffix:semicolon
DECL|member|b_if
r_struct
id|hisax_b_if
op_star
id|b_if
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|erq
r_struct
id|sk_buff_head
id|erq
suffix:semicolon
DECL|member|ph_state
r_int
id|ph_state
suffix:semicolon
)brace
suffix:semicolon
r_int
id|hisax_register
c_func
(paren
r_struct
id|hisax_d_if
op_star
id|hisax_if
comma
r_struct
id|hisax_b_if
op_star
id|b_if
(braket
)braket
comma
r_char
op_star
id|name
comma
r_int
id|protocol
)paren
suffix:semicolon
r_void
id|hisax_unregister
c_func
(paren
r_struct
id|hisax_d_if
op_star
id|hisax_if
)paren
suffix:semicolon
macro_line|#endif
eof
