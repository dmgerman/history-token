singleline_comment|// $Id: icc.h,v 1.2.6.1 2001/02/16 16:43:27 kai Exp $
singleline_comment|//-----------------------------------------------------------------------------
singleline_comment|//
singleline_comment|// ICC specific routines
singleline_comment|//
singleline_comment|// Author       Matt Henderson &amp; Guy Ellis - Traverse Tecnologies Pty Ltd
singleline_comment|//              www.traverse.com.au
singleline_comment|//
singleline_comment|// 1999.7.14 Initial implementation of routines for Siemens ISDN 
singleline_comment|// Communication Controller PEB 2070 based on the ISAC routines 
singleline_comment|// written by Karsten Keil.
singleline_comment|//
singleline_comment|// This file is (c) under GNU General Public License
singleline_comment|//
singleline_comment|//-----------------------------------------------------------------------------
multiline_comment|/* All Registers original Siemens Spec  */
DECL|macro|ICC_MASK
mdefine_line|#define ICC_MASK 0x20
DECL|macro|ICC_ISTA
mdefine_line|#define ICC_ISTA 0x20
DECL|macro|ICC_STAR
mdefine_line|#define ICC_STAR 0x21
DECL|macro|ICC_CMDR
mdefine_line|#define ICC_CMDR 0x21
DECL|macro|ICC_EXIR
mdefine_line|#define ICC_EXIR 0x24
DECL|macro|ICC_ADF2
mdefine_line|#define ICC_ADF2 0x39
DECL|macro|ICC_SPCR
mdefine_line|#define ICC_SPCR 0x30
DECL|macro|ICC_ADF1
mdefine_line|#define ICC_ADF1 0x38
DECL|macro|ICC_CIR0
mdefine_line|#define ICC_CIR0 0x31
DECL|macro|ICC_CIX0
mdefine_line|#define ICC_CIX0 0x31
DECL|macro|ICC_CIR1
mdefine_line|#define ICC_CIR1 0x33
DECL|macro|ICC_CIX1
mdefine_line|#define ICC_CIX1 0x33
DECL|macro|ICC_STCR
mdefine_line|#define ICC_STCR 0x37
DECL|macro|ICC_MODE
mdefine_line|#define ICC_MODE 0x22
DECL|macro|ICC_RSTA
mdefine_line|#define ICC_RSTA 0x27
DECL|macro|ICC_RBCL
mdefine_line|#define ICC_RBCL 0x25
DECL|macro|ICC_RBCH
mdefine_line|#define ICC_RBCH 0x2A
DECL|macro|ICC_TIMR
mdefine_line|#define ICC_TIMR 0x23
DECL|macro|ICC_SQXR
mdefine_line|#define ICC_SQXR 0x3b
DECL|macro|ICC_MOSR
mdefine_line|#define ICC_MOSR 0x3a
DECL|macro|ICC_MOCR
mdefine_line|#define ICC_MOCR 0x3a
DECL|macro|ICC_MOR0
mdefine_line|#define ICC_MOR0 0x32
DECL|macro|ICC_MOX0
mdefine_line|#define ICC_MOX0 0x32
DECL|macro|ICC_MOR1
mdefine_line|#define ICC_MOR1 0x34
DECL|macro|ICC_MOX1
mdefine_line|#define ICC_MOX1 0x34
DECL|macro|ICC_RBCH_XAC
mdefine_line|#define ICC_RBCH_XAC 0x80
DECL|macro|ICC_CMD_TIM
mdefine_line|#define ICC_CMD_TIM    0x0
DECL|macro|ICC_CMD_RES
mdefine_line|#define ICC_CMD_RES    0x1
DECL|macro|ICC_CMD_DU
mdefine_line|#define ICC_CMD_DU     0x3
DECL|macro|ICC_CMD_EI1
mdefine_line|#define ICC_CMD_EI1    0x4
DECL|macro|ICC_CMD_SSP
mdefine_line|#define ICC_CMD_SSP    0x5
DECL|macro|ICC_CMD_DT
mdefine_line|#define ICC_CMD_DT     0x6
DECL|macro|ICC_CMD_AR
mdefine_line|#define ICC_CMD_AR     0x8
DECL|macro|ICC_CMD_ARL
mdefine_line|#define ICC_CMD_ARL    0xA
DECL|macro|ICC_CMD_AI
mdefine_line|#define ICC_CMD_AI     0xC
DECL|macro|ICC_CMD_DI
mdefine_line|#define ICC_CMD_DI     0xF
DECL|macro|ICC_IND_DR
mdefine_line|#define ICC_IND_DR     0x0
DECL|macro|ICC_IND_FJ
mdefine_line|#define ICC_IND_FJ     0x2
DECL|macro|ICC_IND_EI1
mdefine_line|#define ICC_IND_EI1    0x4
DECL|macro|ICC_IND_INT
mdefine_line|#define ICC_IND_INT    0x6
DECL|macro|ICC_IND_PU
mdefine_line|#define ICC_IND_PU     0x7
DECL|macro|ICC_IND_AR
mdefine_line|#define ICC_IND_AR     0x8
DECL|macro|ICC_IND_ARL
mdefine_line|#define ICC_IND_ARL    0xA
DECL|macro|ICC_IND_AI
mdefine_line|#define ICC_IND_AI     0xC
DECL|macro|ICC_IND_AIL
mdefine_line|#define ICC_IND_AIL    0xE
DECL|macro|ICC_IND_DC
mdefine_line|#define ICC_IND_DC     0xF
r_extern
r_void
id|ICCVersion
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
id|initicc
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
id|icc_interrupt
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
id|clear_pending_icc_ints
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
eof
