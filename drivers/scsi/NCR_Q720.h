multiline_comment|/* -*- mode: c; c-basic-offset: 8 -*- */
multiline_comment|/* NCR Quad 720 MCA SCSI Driver&n; *&n; * Copyright (C) 2003 by James.Bottomley@HansenPartnership.com&n; */
macro_line|#ifndef _NCR_Q720_H
DECL|macro|_NCR_Q720_H
mdefine_line|#define _NCR_Q720_H
multiline_comment|/* The MCA identifier */
DECL|macro|NCR_Q720_MCA_ID
mdefine_line|#define NCR_Q720_MCA_ID&t;&t;0x0720
DECL|macro|NCR_Q720_CLOCK_MHZ
mdefine_line|#define NCR_Q720_CLOCK_MHZ&t;30
DECL|macro|NCR_Q720_POS2_BOARD_ENABLE
mdefine_line|#define NCR_Q720_POS2_BOARD_ENABLE&t;0x01
DECL|macro|NCR_Q720_POS2_INTERRUPT_ENABLE
mdefine_line|#define NCR_Q720_POS2_INTERRUPT_ENABLE&t;0x02
DECL|macro|NCR_Q720_POS2_PARITY_DISABLE
mdefine_line|#define NCR_Q720_POS2_PARITY_DISABLE&t;0x04
DECL|macro|NCR_Q720_POS2_IO_MASK
mdefine_line|#define NCR_Q720_POS2_IO_MASK&t;&t;0xf8
DECL|macro|NCR_Q720_POS2_IO_SHIFT
mdefine_line|#define NCR_Q720_POS2_IO_SHIFT&t;&t;8
DECL|macro|NCR_Q720_CHIP_REGISTER_OFFSET
mdefine_line|#define NCR_Q720_CHIP_REGISTER_OFFSET&t;0x200
DECL|macro|NCR_Q720_SCSR_OFFSET
mdefine_line|#define NCR_Q720_SCSR_OFFSET&t;&t;0x070
DECL|macro|NCR_Q720_SIOP_SHIFT
mdefine_line|#define NCR_Q720_SIOP_SHIFT&t;&t;0x080
macro_line|#endif
eof
