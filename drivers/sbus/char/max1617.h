multiline_comment|/* $Id: max1617.h,v 1.1 2001/04/02 09:59:08 davem Exp $ */
macro_line|#ifndef _MAX1617_H
DECL|macro|_MAX1617_H
mdefine_line|#define _MAX1617_H
DECL|macro|MAX1617_AMB_TEMP
mdefine_line|#define MAX1617_AMB_TEMP&t;0x00 /* Ambient temp in C&t;*/
DECL|macro|MAX1617_CPU_TEMP
mdefine_line|#define MAX1617_CPU_TEMP&t;0x01 /* Processor die temp in C&t;*/
DECL|macro|MAX1617_STATUS
mdefine_line|#define MAX1617_STATUS&t;&t;0x02 /* Chip status bits&t;*/
multiline_comment|/* Read-only versions of changable registers. */
DECL|macro|MAX1617_RD_CFG_BYTE
mdefine_line|#define MAX1617_RD_CFG_BYTE&t;0x03 /* Config register&t;&t;*/
DECL|macro|MAX1617_RD_CVRATE_BYTE
mdefine_line|#define MAX1617_RD_CVRATE_BYTE&t;0x04 /* Temp conversion rate&t;*/
DECL|macro|MAX1617_RD_AMB_HIGHLIM
mdefine_line|#define MAX1617_RD_AMB_HIGHLIM&t;0x05 /* Ambient high limit&t;*/
DECL|macro|MAX1617_RD_AMB_LOWLIM
mdefine_line|#define MAX1617_RD_AMB_LOWLIM&t;0x06 /* Ambient low limit&t;*/
DECL|macro|MAX1617_RD_CPU_HIGHLIM
mdefine_line|#define MAX1617_RD_CPU_HIGHLIM&t;0x07 /* Processor high limit&t;*/
DECL|macro|MAX1617_RD_CPU_LOWLIM
mdefine_line|#define MAX1617_RD_CPU_LOWLIM&t;0x08 /* Processor low limit&t;*/
multiline_comment|/* Write-only versions of the same. */
DECL|macro|MAX1617_WR_CFG_BYTE
mdefine_line|#define MAX1617_WR_CFG_BYTE&t;0x09
DECL|macro|MAX1617_WR_CVRATE_BYTE
mdefine_line|#define MAX1617_WR_CVRATE_BYTE&t;0x0a
DECL|macro|MAX1617_WR_AMB_HIGHLIM
mdefine_line|#define MAX1617_WR_AMB_HIGHLIM&t;0x0b
DECL|macro|MAX1617_WR_AMB_LOWLIM
mdefine_line|#define MAX1617_WR_AMB_LOWLIM&t;0x0c
DECL|macro|MAX1617_WR_CPU_HIGHLIM
mdefine_line|#define MAX1617_WR_CPU_HIGHLIM&t;0x0d
DECL|macro|MAX1617_WR_CPU_LOWLIM
mdefine_line|#define MAX1617_WR_CPU_LOWLIM&t;0x0e
DECL|macro|MAX1617_ONESHOT
mdefine_line|#define MAX1617_ONESHOT&t;&t;0x0f
macro_line|#endif /* _MAX1617_H */
eof
