multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
macro_line|#ifndef&t;_SKFBIINC_
DECL|macro|_SKFBIINC_
mdefine_line|#define _SKFBIINC_
macro_line|#include &quot;h/supern_2.h&quot;
multiline_comment|/*&n; * special defines for use into .asm files&n; */
DECL|macro|ERR_FLAGS
mdefine_line|#define ERR_FLAGS (FS_MSRABT | FS_SEAC2 | FS_SFRMERR | FS_SFRMTY1)
macro_line|#ifdef&t;ISA
DECL|macro|DMA_BUSY_CHECK
mdefine_line|#define DMA_BUSY_CHECK&t;CSRA
DECL|macro|IMASK_FAST
mdefine_line|#define&t;IMASK_FAST&t;(IS_PLINT1 | IS_PLINT2 | IS_TIMINT)
DECL|macro|HRQR
mdefine_line|#define&t;HRQR&t;&t;(RQAA+(RQ_RRQ&lt;&lt;1))
DECL|macro|HRQW
mdefine_line|#define&t;HRQW&t;&t;(RQAA+(RQ_WA2&lt;&lt;1))
DECL|macro|HRQA0
mdefine_line|#define&t;HRQA0&t;&t;(RQAA+(RQ_WA0&lt;&lt;1))
DECL|macro|HRQSQ
mdefine_line|#define HRQSQ&t;&t;(RQAA+(RQ_WSQ&lt;&lt;1))
macro_line|#endif
macro_line|#ifdef&t;EISA
DECL|macro|DMA_BUSY_CHECK
mdefine_line|#define&t;DMA_BUSY_CHECK&t;CSRA
DECL|macro|DMA_HIGH_WORD
mdefine_line|#define DMA_HIGH_WORD&t;0x0400
DECL|macro|DMA_MASK_M
mdefine_line|#define DMA_MASK_M&t;0x0a
DECL|macro|DMA_MODE_M
mdefine_line|#define DMA_MODE_M&t;0x0b
DECL|macro|DMA_BYTE_PTR_M
mdefine_line|#define DMA_BYTE_PTR_M&t;0x0c
DECL|macro|DMA_MASK_S
mdefine_line|#define DMA_MASK_S&t;0x0d4
DECL|macro|DMA_MODE_S
mdefine_line|#define DMA_MODE_S&t;0x0d6
DECL|macro|DMA_BYTE_PTR_S
mdefine_line|#define DMA_BYTE_PTR_S&t;0x0d8
DECL|macro|IMASK_FAST
mdefine_line|#define&t;IMASK_FAST&t;(IS_PLINT1 | IS_PLINT2 | IS_TIMINT | IS_TC)
macro_line|#endif&t;/* EISA */
macro_line|#ifdef&t;MCA
DECL|macro|IMASK_FAST
mdefine_line|#define&t;IMASK_FAST&t;(IS_PLINT1 | IS_PLINT2 | IS_TIMINT | IS_TOKEN | &bslash;&n;&t;&t;&t; IS_CHCK_L | IS_BUSERR)
macro_line|#endif
macro_line|#ifdef PCI
DECL|macro|IMASK_FAST
mdefine_line|#define&t;IMASK_FAST&t;(IS_PLINT1 | IS_PLINT2 | IS_TIMINT | IS_TOKEN | &bslash;&n;&t;&t;&t; IS_MINTR2 | IS_MINTR3 | IS_R1_P | &bslash;&n;&t;&t;&t; IS_R1_C | IS_XA_C | IS_XS_C)
macro_line|#endif
macro_line|#ifdef&t;PCI
DECL|macro|ISR_MASK
mdefine_line|#define&t;ISR_MASK&t;(IS_MINTR1 | IS_R1_F | IS_XS_F| IS_XA_F | IMASK_FAST)
macro_line|#else
DECL|macro|ISR_MASK
mdefine_line|#define&t;ISR_MASK&t;(IS_MINTR1 | IS_MINTR2 | IMASK_FAST)
macro_line|#endif
DECL|macro|FMA_FM_CMDREG1
mdefine_line|#define&t;FMA_FM_CMDREG1&t;FMA(FM_CMDREG1)
DECL|macro|FMA_FM_CMDREG2
mdefine_line|#define&t;FMA_FM_CMDREG2&t;FMA(FM_CMDREG2)
DECL|macro|FMA_FM_STMCHN
mdefine_line|#define&t;FMA_FM_STMCHN&t;FMA(FM_STMCHN)
DECL|macro|FMA_FM_RPR
mdefine_line|#define&t;FMA_FM_RPR&t;FMA(FM_RPR)
DECL|macro|FMA_FM_WPXA0
mdefine_line|#define&t;FMA_FM_WPXA0&t;FMA(FM_WPXA0)
DECL|macro|FMA_FM_WPXA2
mdefine_line|#define&t;FMA_FM_WPXA2&t;FMA(FM_WPXA2)
DECL|macro|FMA_FM_MARR
mdefine_line|#define&t;FMA_FM_MARR&t;FMA(FM_MARR)
DECL|macro|FMA_FM_MARW
mdefine_line|#define&t;FMA_FM_MARW&t;FMA(FM_MARW)
DECL|macro|FMA_FM_MDRU
mdefine_line|#define&t;FMA_FM_MDRU&t;FMA(FM_MDRU)
DECL|macro|FMA_FM_MDRL
mdefine_line|#define&t;FMA_FM_MDRL&t;FMA(FM_MDRL)
DECL|macro|FMA_ST1L
mdefine_line|#define&t;FMA_ST1L&t;FMA(FM_ST1L)
DECL|macro|FMA_ST1U
mdefine_line|#define&t;FMA_ST1U&t;FMA(FM_ST1U)
DECL|macro|FMA_ST2L
mdefine_line|#define&t;FMA_ST2L&t;FMA(FM_ST2L)
DECL|macro|FMA_ST2U
mdefine_line|#define&t;FMA_ST2U&t;FMA(FM_ST2U)
macro_line|#ifdef&t;SUPERNET_3
DECL|macro|FMA_ST3L
mdefine_line|#define FMA_ST3L&t;FMA(FM_ST3L)
DECL|macro|FMA_ST3U
mdefine_line|#define FMA_ST3U&t;FMA(FM_ST3U)
macro_line|#endif
DECL|macro|TMODE_RRQ
mdefine_line|#define TMODE_RRQ&t;RQ_RRQ
DECL|macro|TMODE_WAQ2
mdefine_line|#define TMODE_WAQ2&t;RQ_WA2
DECL|macro|HSRA
mdefine_line|#define&t;HSRA&t;&t;HSR(0)
DECL|macro|FMA_FM_ST1L
mdefine_line|#define FMA_FM_ST1L&t;FMA_ST1L
DECL|macro|FMA_FM_ST1U
mdefine_line|#define FMA_FM_ST1U&t;FMA_ST1U
DECL|macro|FMA_FM_ST2L
mdefine_line|#define FMA_FM_ST2L&t;FMA_ST2L
DECL|macro|FMA_FM_ST2U
mdefine_line|#define FMA_FM_ST2U&t;FMA_ST2U
macro_line|#ifdef&t;SUPERNET_3
DECL|macro|FMA_FM_ST3L
mdefine_line|#define FMA_FM_ST3L&t;FMA_ST3L
DECL|macro|FMA_FM_ST3U
mdefine_line|#define FMA_FM_ST3U&t;FMA_ST3U
macro_line|#endif
DECL|macro|FMA_FM_SWPR
mdefine_line|#define FMA_FM_SWPR&t;FMA(FM_SWPR)
DECL|macro|FMA_FM_RPXA0
mdefine_line|#define FMA_FM_RPXA0&t;FMA(FM_RPXA0)
DECL|macro|FMA_FM_RPXS
mdefine_line|#define&t;FMA_FM_RPXS&t;FMA(FM_RPXS)
DECL|macro|FMA_FM_WPXS
mdefine_line|#define&t;FMA_FM_WPXS&t;FMA(FM_WPXS)
DECL|macro|FMA_FM_IMSK1U
mdefine_line|#define&t;FMA_FM_IMSK1U&t;FMA(FM_IMSK1U)
DECL|macro|FMA_FM_IMSK1L
mdefine_line|#define&t;FMA_FM_IMSK1L&t;FMA(FM_IMSK1L)
DECL|macro|FMA_FM_EAS
mdefine_line|#define&t;FMA_FM_EAS&t;FMA(FM_EAS)
DECL|macro|FMA_FM_EAA0
mdefine_line|#define&t;FMA_FM_EAA0&t;FMA(FM_EAA0)
DECL|macro|TMODE_WAQ0
mdefine_line|#define&t;TMODE_WAQ0&t;RQ_WA0
DECL|macro|TMODE_WSQ
mdefine_line|#define TMODE_WSQ&t;RQ_WSQ
multiline_comment|/* Define default for DRV_PCM_STATE_CHANGE */
macro_line|#ifndef&t;DRV_PCM_STATE_CHANGE
DECL|macro|DRV_PCM_STATE_CHANGE
mdefine_line|#define&t;DRV_PCM_STATE_CHANGE(smc,plc,p_state)&t;/* nothing */
macro_line|#endif
multiline_comment|/* Define default for DRV_RMT_INDICATION */
macro_line|#ifndef&t;DRV_RMT_INDICATION
DECL|macro|DRV_RMT_INDICATION
mdefine_line|#define&t;DRV_RMT_INDICATION(smc,i)&t;/* nothing */
macro_line|#endif
macro_line|#endif&t;/* n_SKFBIINC_ */
eof
