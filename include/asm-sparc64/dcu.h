multiline_comment|/* $Id: dcu.h,v 1.2 2001/03/01 23:23:33 davem Exp $ */
macro_line|#ifndef _SPARC64_DCU_H
DECL|macro|_SPARC64_DCU_H
mdefine_line|#define _SPARC64_DCU_H
multiline_comment|/* UltraSparc-III Data Cache Unit Control Register */
DECL|macro|DCU_CP
mdefine_line|#define DCU_CP&t;&t;0x0002000000000000 /* Physical Cache Enable w/o mmu*/
DECL|macro|DCU_CV
mdefine_line|#define DCU_CV&t;&t;0x0001000000000000 /* Virtual Cache Enable&t;w/o mmu&t;*/
DECL|macro|DCU_ME
mdefine_line|#define DCU_ME&t;&t;0x0000800000000000 /* NC-store Merging Enable&t;*/
DECL|macro|DCU_RE
mdefine_line|#define DCU_RE&t;&t;0x0000400000000000 /* RAW bypass Enable&t;&t;*/
DECL|macro|DCU_PE
mdefine_line|#define DCU_PE&t;&t;0x0000200000000000 /* PCache Enable&t;&t;*/
DECL|macro|DCU_HPE
mdefine_line|#define DCU_HPE&t;&t;0x0000100000000000 /* HW prefetch Enable&t;&t;*/
DECL|macro|DCU_SPE
mdefine_line|#define DCU_SPE&t;&t;0x0000080000000000 /* SW prefetch Enable&t;&t;*/
DECL|macro|DCU_SL
mdefine_line|#define DCU_SL&t;&t;0x0000040000000000 /* Secondary load steering Enab&t;*/
DECL|macro|DCU_WE
mdefine_line|#define DCU_WE&t;&t;0x0000020000000000 /* WCache enable&t;&t;*/
DECL|macro|DCU_PM
mdefine_line|#define DCU_PM&t;&t;0x000001fe00000000 /* PA Watchpoint Byte Mask&t;*/
DECL|macro|DCU_VM
mdefine_line|#define DCU_VM&t;&t;0x00000001fe000000 /* VA Watchpoint Byte Mask&t;*/
DECL|macro|DCU_PR
mdefine_line|#define DCU_PR&t;&t;0x0000000001000000 /* PA Watchpoint Read Enable&t;*/
DECL|macro|DCU_PW
mdefine_line|#define DCU_PW&t;&t;0x0000000000800000 /* PA Watchpoint Write Enable&t;*/
DECL|macro|DCU_VR
mdefine_line|#define DCU_VR&t;&t;0x0000000000400000 /* VA Watchpoint Read Enable&t;*/
DECL|macro|DCU_VW
mdefine_line|#define DCU_VW&t;&t;0x0000000000200000 /* VA Watchpoint Write Enable&t;*/
DECL|macro|DCU_DM
mdefine_line|#define DCU_DM&t;&t;0x0000000000000008 /* DMMU Enable&t;&t;&t;*/
DECL|macro|DCU_IM
mdefine_line|#define DCU_IM&t;&t;0x0000000000000004 /* IMMU Enable&t;&t;&t;*/
DECL|macro|DCU_DC
mdefine_line|#define DCU_DC&t;&t;0x0000000000000002 /* Data Cache Enable&t;&t;*/
DECL|macro|DCU_IC
mdefine_line|#define DCU_IC&t;&t;0x0000000000000001 /* Instruction Cache Enable&t;*/
macro_line|#endif /* _SPARC64_DCU_H */
eof
