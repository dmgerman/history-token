multiline_comment|/* $Id: hscx.h,v 1.6.6.1 2001/02/16 16:43:27 kai Exp $&n; *&n; * hscx.h   HSCX specific defines&n; *&n; * Author       Karsten Keil (keil@isdn4linux.de)&n; *&n; * This file is (c) under GNU General Public License&n; *&n; */
multiline_comment|/* All Registers original Siemens Spec  */
DECL|macro|HSCX_ISTA
mdefine_line|#define HSCX_ISTA 0x20
DECL|macro|HSCX_CCR1
mdefine_line|#define HSCX_CCR1 0x2f
DECL|macro|HSCX_CCR2
mdefine_line|#define HSCX_CCR2 0x2c
DECL|macro|HSCX_TSAR
mdefine_line|#define HSCX_TSAR 0x31
DECL|macro|HSCX_TSAX
mdefine_line|#define HSCX_TSAX 0x30
DECL|macro|HSCX_XCCR
mdefine_line|#define HSCX_XCCR 0x32
DECL|macro|HSCX_RCCR
mdefine_line|#define HSCX_RCCR 0x33
DECL|macro|HSCX_MODE
mdefine_line|#define HSCX_MODE 0x22
DECL|macro|HSCX_CMDR
mdefine_line|#define HSCX_CMDR 0x21
DECL|macro|HSCX_EXIR
mdefine_line|#define HSCX_EXIR 0x24
DECL|macro|HSCX_XAD1
mdefine_line|#define HSCX_XAD1 0x24
DECL|macro|HSCX_XAD2
mdefine_line|#define HSCX_XAD2 0x25
DECL|macro|HSCX_RAH2
mdefine_line|#define HSCX_RAH2 0x27
DECL|macro|HSCX_RSTA
mdefine_line|#define HSCX_RSTA 0x27
DECL|macro|HSCX_TIMR
mdefine_line|#define HSCX_TIMR 0x23
DECL|macro|HSCX_STAR
mdefine_line|#define HSCX_STAR 0x21
DECL|macro|HSCX_RBCL
mdefine_line|#define HSCX_RBCL 0x25
DECL|macro|HSCX_XBCH
mdefine_line|#define HSCX_XBCH 0x2d
DECL|macro|HSCX_VSTR
mdefine_line|#define HSCX_VSTR 0x2e
DECL|macro|HSCX_RLCR
mdefine_line|#define HSCX_RLCR 0x2e
DECL|macro|HSCX_MASK
mdefine_line|#define HSCX_MASK 0x20
r_extern
r_int
id|HscxVersion
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_char
op_star
id|s
)paren
suffix:semicolon
r_extern
r_void
id|hscx_sched_event
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
comma
r_int
id|event
)paren
suffix:semicolon
r_extern
r_void
id|modehscx
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
comma
r_int
id|mode
comma
r_int
id|bc
)paren
suffix:semicolon
r_extern
r_void
id|clear_pending_hscx_ints
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
id|inithscx
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
id|inithscxisac
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|part
)paren
suffix:semicolon
eof
