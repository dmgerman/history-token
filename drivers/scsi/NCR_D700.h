multiline_comment|/* -*- mode: c; c-basic-offset: 8 -*- */
multiline_comment|/* NCR Dual 700 MCA SCSI Driver&n; *&n; * Copyright (C) 2001 by James.Bottomley@HansenPartnership.com&n; */
macro_line|#ifndef _NCR_D700_H
DECL|macro|_NCR_D700_H
mdefine_line|#define _NCR_D700_H
multiline_comment|/* Don&squot;t turn on debugging messages */
DECL|macro|NCR_D700_DEBUG
macro_line|#undef NCR_D700_DEBUG
multiline_comment|/* The MCA identifier */
DECL|macro|NCR_D700_MCA_ID
mdefine_line|#define NCR_D700_MCA_ID&t;&t;0x0092
multiline_comment|/* Defines for the Board registers */
DECL|macro|BOARD_RESET
mdefine_line|#define&t;BOARD_RESET&t;&t;0x80&t;/* board level reset */
DECL|macro|ADD_PARENB
mdefine_line|#define ADD_PARENB&t;&t;0x04&t;/* Address Parity Enabled */
DECL|macro|DAT_PARENB
mdefine_line|#define DAT_PARENB&t;&t;0x01&t;/* Data Parity Enabled */
DECL|macro|SFBK_ENB
mdefine_line|#define SFBK_ENB&t;&t;0x10&t;/* SFDBK Interrupt Enabled */
DECL|macro|LED0GREEN
mdefine_line|#define LED0GREEN&t;&t;0x20&t;/* Led 0 (red 0; green 1) */
DECL|macro|LED1GREEN
mdefine_line|#define LED1GREEN&t;&t;0x40&t;/* Led 1 (red 0; green 1) */
DECL|macro|LED0RED
mdefine_line|#define LED0RED&t;&t;&t;0xDF&t;/* Led 0 (red 0; green 1) */
DECL|macro|LED1RED
mdefine_line|#define LED1RED&t;&t;&t;0xBF&t;/* Led 1 (red 0; green 1) */
DECL|macro|NCR_D700_CLOCK_MHZ
mdefine_line|#define NCR_D700_CLOCK_MHZ&t;50
macro_line|#endif
eof
