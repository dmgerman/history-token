multiline_comment|/* $Id: isac.h,v 1.7 2000/06/26 08:59:13 keil Exp $&n; *&n; * isac.h   ISAC specific defines&n; *&n; * Author       Karsten Keil (keil@isdn4linux.de)&n; *&n; * This file is (c) under GNU PUBLIC LICENSE&n; *&n; */
multiline_comment|/* All Registers original Siemens Spec  */
DECL|macro|ISAC_MASK
mdefine_line|#define ISAC_MASK 0x20
DECL|macro|ISAC_ISTA
mdefine_line|#define ISAC_ISTA 0x20
DECL|macro|ISAC_STAR
mdefine_line|#define ISAC_STAR 0x21
DECL|macro|ISAC_CMDR
mdefine_line|#define ISAC_CMDR 0x21
DECL|macro|ISAC_EXIR
mdefine_line|#define ISAC_EXIR 0x24
DECL|macro|ISAC_ADF2
mdefine_line|#define ISAC_ADF2 0x39
DECL|macro|ISAC_SPCR
mdefine_line|#define ISAC_SPCR 0x30
DECL|macro|ISAC_ADF1
mdefine_line|#define ISAC_ADF1 0x38
DECL|macro|ISAC_CIR0
mdefine_line|#define ISAC_CIR0 0x31
DECL|macro|ISAC_CIX0
mdefine_line|#define ISAC_CIX0 0x31
DECL|macro|ISAC_CIR1
mdefine_line|#define ISAC_CIR1 0x33
DECL|macro|ISAC_CIX1
mdefine_line|#define ISAC_CIX1 0x33
DECL|macro|ISAC_STCR
mdefine_line|#define ISAC_STCR 0x37
DECL|macro|ISAC_MODE
mdefine_line|#define ISAC_MODE 0x22
DECL|macro|ISAC_RSTA
mdefine_line|#define ISAC_RSTA 0x27
DECL|macro|ISAC_RBCL
mdefine_line|#define ISAC_RBCL 0x25
DECL|macro|ISAC_RBCH
mdefine_line|#define ISAC_RBCH 0x2A
DECL|macro|ISAC_TIMR
mdefine_line|#define ISAC_TIMR 0x23
DECL|macro|ISAC_SQXR
mdefine_line|#define ISAC_SQXR 0x3b
DECL|macro|ISAC_MOSR
mdefine_line|#define ISAC_MOSR 0x3a
DECL|macro|ISAC_MOCR
mdefine_line|#define ISAC_MOCR 0x3a
DECL|macro|ISAC_MOR0
mdefine_line|#define ISAC_MOR0 0x32
DECL|macro|ISAC_MOX0
mdefine_line|#define ISAC_MOX0 0x32
DECL|macro|ISAC_MOR1
mdefine_line|#define ISAC_MOR1 0x34
DECL|macro|ISAC_MOX1
mdefine_line|#define ISAC_MOX1 0x34
DECL|macro|ISAC_RBCH_XAC
mdefine_line|#define ISAC_RBCH_XAC 0x80
DECL|macro|ISAC_CMD_TIM
mdefine_line|#define ISAC_CMD_TIM&t;0x0
DECL|macro|ISAC_CMD_RS
mdefine_line|#define ISAC_CMD_RS&t;0x1
DECL|macro|ISAC_CMD_SCZ
mdefine_line|#define ISAC_CMD_SCZ&t;0x4
DECL|macro|ISAC_CMD_SSZ
mdefine_line|#define ISAC_CMD_SSZ&t;0x2
DECL|macro|ISAC_CMD_AR8
mdefine_line|#define ISAC_CMD_AR8&t;0x8
DECL|macro|ISAC_CMD_AR10
mdefine_line|#define ISAC_CMD_AR10&t;0x9
DECL|macro|ISAC_CMD_ARL
mdefine_line|#define ISAC_CMD_ARL&t;0xA
DECL|macro|ISAC_CMD_DUI
mdefine_line|#define ISAC_CMD_DUI&t;0xF
DECL|macro|ISAC_IND_RS
mdefine_line|#define ISAC_IND_RS&t;0x1
DECL|macro|ISAC_IND_PU
mdefine_line|#define ISAC_IND_PU&t;0x7
DECL|macro|ISAC_IND_DR
mdefine_line|#define ISAC_IND_DR&t;0x0
DECL|macro|ISAC_IND_SD
mdefine_line|#define ISAC_IND_SD&t;0x2
DECL|macro|ISAC_IND_DIS
mdefine_line|#define ISAC_IND_DIS&t;0x3
DECL|macro|ISAC_IND_EI
mdefine_line|#define ISAC_IND_EI&t;0x6
DECL|macro|ISAC_IND_RSY
mdefine_line|#define ISAC_IND_RSY&t;0x4
DECL|macro|ISAC_IND_ARD
mdefine_line|#define ISAC_IND_ARD&t;0x8
DECL|macro|ISAC_IND_TI
mdefine_line|#define ISAC_IND_TI&t;0xA
DECL|macro|ISAC_IND_ATI
mdefine_line|#define ISAC_IND_ATI&t;0xB
DECL|macro|ISAC_IND_AI8
mdefine_line|#define ISAC_IND_AI8&t;0xC
DECL|macro|ISAC_IND_AI10
mdefine_line|#define ISAC_IND_AI10&t;0xD
DECL|macro|ISAC_IND_DID
mdefine_line|#define ISAC_IND_DID&t;0xF
r_extern
r_void
id|ISACVersion
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
id|initisac
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
id|isac_interrupt
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
id|val
)paren
suffix:semicolon
r_extern
r_void
id|clear_pending_isac_ints
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
eof
