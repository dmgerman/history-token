multiline_comment|/* $Id: dcr.h,v 1.3 2001/03/01 23:23:33 davem Exp $ */
macro_line|#ifndef _SPARC64_DCR_H
DECL|macro|_SPARC64_DCR_H
mdefine_line|#define _SPARC64_DCR_H
multiline_comment|/* UltraSparc-III Dispatch Control Register, ASR 0x12 */
DECL|macro|DCR_BPE
mdefine_line|#define DCR_BPE&t;&t;0x0000000000000020 /* Branch Predict Enable&t;&t;*/
DECL|macro|DCR_RPE
mdefine_line|#define DCR_RPE&t;&t;0x0000000000000010 /* Return Address Prediction Enable*/
DECL|macro|DCR_SI
mdefine_line|#define DCR_SI&t;&t;0x0000000000000008 /* Single Instruction Disable&t;*/
DECL|macro|DCR_MS
mdefine_line|#define DCR_MS&t;&t;0x0000000000000001 /* Multi-Scalar dispatch&t;&t;*/
macro_line|#endif /* _SPARC64_DCR_H */
eof
