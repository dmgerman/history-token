multiline_comment|/*&n; * Copyright (c) 2002 Silicon Graphics, Inc.  All Rights Reserved.&n; * &n; * This program is free software; you can redistribute it and/or modify it &n; * under the terms of version 2 of the GNU General Public License &n; * as published by the Free Software Foundation.&n; * &n; * This program is distributed in the hope that it would be useful, but &n; * WITHOUT ANY WARRANTY; without even the implied warranty of &n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. &n; * &n; * Further, this software is distributed without any warranty that it is &n; * free of the rightful claim of any third person regarding infringement &n; * or the like.  Any license provided herein, whether implied or &n; * otherwise, applies only to this software file.  Patent licenses, if &n; * any, provided herein do not apply to combinations of this program with &n; * other software, or any other product whatsoever.&n; * &n; * You should have received a copy of the GNU General Public &n; * License along with this program; if not, write the Free Software &n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; * &n; * Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pkwy, &n; * Mountain View, CA  94043, or:&n; * &n; * http://www.sgi.com &n; * &n; * For further information regarding this notice, see: &n; * &n; * http://oss.sgi.com/projects/GenInfo/NoticeExplan&n; */
multiline_comment|/* $Id: ioc3.h,v 1.2 2000/11/16 19:49:17 pfg Exp $&n; *&n; * Copyright (C) 1999 Ralf Baechle&n; * This file is part of the Linux driver for the SGI IOC3.&n; */
macro_line|#ifndef _ASM_IA64_SN_IOC3_H
DECL|macro|_ASM_IA64_SN_IOC3_H
mdefine_line|#define _ASM_IA64_SN_IOC3_H
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/* SUPERIO uart register map */
DECL|struct|ioc3_uartregs
r_typedef
r_volatile
r_struct
id|ioc3_uartregs
(brace
r_union
(brace
DECL|member|rbr
r_volatile
id|u8
id|rbr
suffix:semicolon
multiline_comment|/* read only, DLAB == 0 */
DECL|member|thr
r_volatile
id|u8
id|thr
suffix:semicolon
multiline_comment|/* write only, DLAB == 0 */
DECL|member|dll
r_volatile
id|u8
id|dll
suffix:semicolon
multiline_comment|/* DLAB == 1 */
DECL|member|u1
)brace
id|u1
suffix:semicolon
r_union
(brace
DECL|member|ier
r_volatile
id|u8
id|ier
suffix:semicolon
multiline_comment|/* DLAB == 0 */
DECL|member|dlm
r_volatile
id|u8
id|dlm
suffix:semicolon
multiline_comment|/* DLAB == 1 */
DECL|member|u2
)brace
id|u2
suffix:semicolon
r_union
(brace
DECL|member|iir
r_volatile
id|u8
id|iir
suffix:semicolon
multiline_comment|/* read only */
DECL|member|fcr
r_volatile
id|u8
id|fcr
suffix:semicolon
multiline_comment|/* write only */
DECL|member|u3
)brace
id|u3
suffix:semicolon
DECL|member|iu_lcr
r_volatile
id|u8
id|iu_lcr
suffix:semicolon
DECL|member|iu_mcr
r_volatile
id|u8
id|iu_mcr
suffix:semicolon
DECL|member|iu_lsr
r_volatile
id|u8
id|iu_lsr
suffix:semicolon
DECL|member|iu_msr
r_volatile
id|u8
id|iu_msr
suffix:semicolon
DECL|member|iu_scr
r_volatile
id|u8
id|iu_scr
suffix:semicolon
DECL|typedef|ioc3_uregs_t
)brace
id|ioc3_uregs_t
suffix:semicolon
DECL|macro|iu_rbr
mdefine_line|#define iu_rbr u1.rbr
DECL|macro|iu_thr
mdefine_line|#define iu_thr u1.thr
DECL|macro|iu_dll
mdefine_line|#define iu_dll u1.dll
DECL|macro|iu_ier
mdefine_line|#define iu_ier u2.ier
DECL|macro|iu_dlm
mdefine_line|#define iu_dlm u2.dlm
DECL|macro|iu_iir
mdefine_line|#define iu_iir u3.iir
DECL|macro|iu_fcr
mdefine_line|#define iu_fcr u3.fcr
DECL|struct|ioc3_sioregs
r_struct
id|ioc3_sioregs
(brace
DECL|member|fill
r_volatile
id|u8
id|fill
(braket
l_int|0x141
)braket
suffix:semicolon
multiline_comment|/* starts at 0x141 */
DECL|member|uartc
r_volatile
id|u8
id|uartc
suffix:semicolon
DECL|member|kbdcg
r_volatile
id|u8
id|kbdcg
suffix:semicolon
DECL|member|fill0
r_volatile
id|u8
id|fill0
(braket
l_int|0x150
op_minus
l_int|0x142
op_minus
l_int|1
)braket
suffix:semicolon
DECL|member|pp_data
r_volatile
id|u8
id|pp_data
suffix:semicolon
DECL|member|pp_dsr
r_volatile
id|u8
id|pp_dsr
suffix:semicolon
DECL|member|pp_dcr
r_volatile
id|u8
id|pp_dcr
suffix:semicolon
DECL|member|fill1
r_volatile
id|u8
id|fill1
(braket
l_int|0x158
op_minus
l_int|0x152
op_minus
l_int|1
)braket
suffix:semicolon
DECL|member|pp_fifa
r_volatile
id|u8
id|pp_fifa
suffix:semicolon
DECL|member|pp_cfgb
r_volatile
id|u8
id|pp_cfgb
suffix:semicolon
DECL|member|pp_ecr
r_volatile
id|u8
id|pp_ecr
suffix:semicolon
DECL|member|fill2
r_volatile
id|u8
id|fill2
(braket
l_int|0x168
op_minus
l_int|0x15a
op_minus
l_int|1
)braket
suffix:semicolon
DECL|member|rtcad
r_volatile
id|u8
id|rtcad
suffix:semicolon
DECL|member|rtcdat
r_volatile
id|u8
id|rtcdat
suffix:semicolon
DECL|member|fill3
r_volatile
id|u8
id|fill3
(braket
l_int|0x170
op_minus
l_int|0x169
op_minus
l_int|1
)braket
suffix:semicolon
DECL|member|uartb
r_struct
id|ioc3_uartregs
id|uartb
suffix:semicolon
multiline_comment|/* 0x20170  */
DECL|member|uarta
r_struct
id|ioc3_uartregs
id|uarta
suffix:semicolon
multiline_comment|/* 0x20178  */
)brace
suffix:semicolon
multiline_comment|/* Register layout of IOC3 in configuration space.  */
DECL|struct|ioc3
r_struct
id|ioc3
(brace
DECL|member|pad0
r_volatile
id|u32
id|pad0
(braket
l_int|7
)braket
suffix:semicolon
multiline_comment|/* 0x00000  */
DECL|member|sio_ir
r_volatile
id|u32
id|sio_ir
suffix:semicolon
multiline_comment|/* 0x0001c  */
DECL|member|sio_ies
r_volatile
id|u32
id|sio_ies
suffix:semicolon
multiline_comment|/* 0x00020  */
DECL|member|sio_iec
r_volatile
id|u32
id|sio_iec
suffix:semicolon
multiline_comment|/* 0x00024  */
DECL|member|sio_cr
r_volatile
id|u32
id|sio_cr
suffix:semicolon
multiline_comment|/* 0x00028  */
DECL|member|int_out
r_volatile
id|u32
id|int_out
suffix:semicolon
multiline_comment|/* 0x0002c  */
DECL|member|mcr
r_volatile
id|u32
id|mcr
suffix:semicolon
multiline_comment|/* 0x00030  */
multiline_comment|/* General Purpose I/O registers  */
DECL|member|gpcr_s
r_volatile
id|u32
id|gpcr_s
suffix:semicolon
multiline_comment|/* 0x00034  */
DECL|member|gpcr_c
r_volatile
id|u32
id|gpcr_c
suffix:semicolon
multiline_comment|/* 0x00038  */
DECL|member|gpdr
r_volatile
id|u32
id|gpdr
suffix:semicolon
multiline_comment|/* 0x0003c  */
DECL|member|gppr_0
r_volatile
id|u32
id|gppr_0
suffix:semicolon
multiline_comment|/* 0x00040  */
DECL|member|gppr_1
r_volatile
id|u32
id|gppr_1
suffix:semicolon
multiline_comment|/* 0x00044  */
DECL|member|gppr_2
r_volatile
id|u32
id|gppr_2
suffix:semicolon
multiline_comment|/* 0x00048  */
DECL|member|gppr_3
r_volatile
id|u32
id|gppr_3
suffix:semicolon
multiline_comment|/* 0x0004c  */
DECL|member|gppr_4
r_volatile
id|u32
id|gppr_4
suffix:semicolon
multiline_comment|/* 0x00050  */
DECL|member|gppr_5
r_volatile
id|u32
id|gppr_5
suffix:semicolon
multiline_comment|/* 0x00054  */
DECL|member|gppr_6
r_volatile
id|u32
id|gppr_6
suffix:semicolon
multiline_comment|/* 0x00058  */
DECL|member|gppr_7
r_volatile
id|u32
id|gppr_7
suffix:semicolon
multiline_comment|/* 0x0005c  */
DECL|member|gppr_8
r_volatile
id|u32
id|gppr_8
suffix:semicolon
multiline_comment|/* 0x00060  */
DECL|member|gppr_9
r_volatile
id|u32
id|gppr_9
suffix:semicolon
multiline_comment|/* 0x00064  */
DECL|member|gppr_10
r_volatile
id|u32
id|gppr_10
suffix:semicolon
multiline_comment|/* 0x00068  */
DECL|member|gppr_11
r_volatile
id|u32
id|gppr_11
suffix:semicolon
multiline_comment|/* 0x0006c  */
DECL|member|gppr_12
r_volatile
id|u32
id|gppr_12
suffix:semicolon
multiline_comment|/* 0x00070  */
DECL|member|gppr_13
r_volatile
id|u32
id|gppr_13
suffix:semicolon
multiline_comment|/* 0x00074  */
DECL|member|gppr_14
r_volatile
id|u32
id|gppr_14
suffix:semicolon
multiline_comment|/* 0x00078  */
DECL|member|gppr_15
r_volatile
id|u32
id|gppr_15
suffix:semicolon
multiline_comment|/* 0x0007c  */
multiline_comment|/* Parallel Port Registers  */
DECL|member|ppbr_h_a
r_volatile
id|u32
id|ppbr_h_a
suffix:semicolon
multiline_comment|/* 0x00080  */
DECL|member|ppbr_l_a
r_volatile
id|u32
id|ppbr_l_a
suffix:semicolon
multiline_comment|/* 0x00084  */
DECL|member|ppcr_a
r_volatile
id|u32
id|ppcr_a
suffix:semicolon
multiline_comment|/* 0x00088  */
DECL|member|ppcr
r_volatile
id|u32
id|ppcr
suffix:semicolon
multiline_comment|/* 0x0008c  */
DECL|member|ppbr_h_b
r_volatile
id|u32
id|ppbr_h_b
suffix:semicolon
multiline_comment|/* 0x00090  */
DECL|member|ppbr_l_b
r_volatile
id|u32
id|ppbr_l_b
suffix:semicolon
multiline_comment|/* 0x00094  */
DECL|member|ppcr_b
r_volatile
id|u32
id|ppcr_b
suffix:semicolon
multiline_comment|/* 0x00098  */
multiline_comment|/* Keyboard and Mouse Registers  */
DECL|member|km_csr
r_volatile
id|u32
id|km_csr
suffix:semicolon
multiline_comment|/* 0x0009c  */
DECL|member|k_rd
r_volatile
id|u32
id|k_rd
suffix:semicolon
multiline_comment|/* 0x000a0  */
DECL|member|m_rd
r_volatile
id|u32
id|m_rd
suffix:semicolon
multiline_comment|/* 0x000a4  */
DECL|member|k_wd
r_volatile
id|u32
id|k_wd
suffix:semicolon
multiline_comment|/* 0x000a8  */
DECL|member|m_wd
r_volatile
id|u32
id|m_wd
suffix:semicolon
multiline_comment|/* 0x000ac  */
multiline_comment|/* Serial Port Registers  */
DECL|member|sbbr_h
r_volatile
id|u32
id|sbbr_h
suffix:semicolon
multiline_comment|/* 0x000b0  */
DECL|member|sbbr_l
r_volatile
id|u32
id|sbbr_l
suffix:semicolon
multiline_comment|/* 0x000b4  */
DECL|member|sscr_a
r_volatile
id|u32
id|sscr_a
suffix:semicolon
multiline_comment|/* 0x000b8  */
DECL|member|stpir_a
r_volatile
id|u32
id|stpir_a
suffix:semicolon
multiline_comment|/* 0x000bc  */
DECL|member|stcir_a
r_volatile
id|u32
id|stcir_a
suffix:semicolon
multiline_comment|/* 0x000c0  */
DECL|member|srpir_a
r_volatile
id|u32
id|srpir_a
suffix:semicolon
multiline_comment|/* 0x000c4  */
DECL|member|srcir_a
r_volatile
id|u32
id|srcir_a
suffix:semicolon
multiline_comment|/* 0x000c8  */
DECL|member|srtr_a
r_volatile
id|u32
id|srtr_a
suffix:semicolon
multiline_comment|/* 0x000cc  */
DECL|member|shadow_a
r_volatile
id|u32
id|shadow_a
suffix:semicolon
multiline_comment|/* 0x000d0  */
DECL|member|sscr_b
r_volatile
id|u32
id|sscr_b
suffix:semicolon
multiline_comment|/* 0x000d4  */
DECL|member|stpir_b
r_volatile
id|u32
id|stpir_b
suffix:semicolon
multiline_comment|/* 0x000d8  */
DECL|member|stcir_b
r_volatile
id|u32
id|stcir_b
suffix:semicolon
multiline_comment|/* 0x000dc  */
DECL|member|srpir_b
r_volatile
id|u32
id|srpir_b
suffix:semicolon
multiline_comment|/* 0x000e0  */
DECL|member|srcir_b
r_volatile
id|u32
id|srcir_b
suffix:semicolon
multiline_comment|/* 0x000e4  */
DECL|member|srtr_b
r_volatile
id|u32
id|srtr_b
suffix:semicolon
multiline_comment|/* 0x000e8  */
DECL|member|shadow_b
r_volatile
id|u32
id|shadow_b
suffix:semicolon
multiline_comment|/* 0x000ec  */
multiline_comment|/* Ethernet Registers  */
DECL|member|emcr
r_volatile
id|u32
id|emcr
suffix:semicolon
multiline_comment|/* 0x000f0  */
DECL|member|eisr
r_volatile
id|u32
id|eisr
suffix:semicolon
multiline_comment|/* 0x000f4  */
DECL|member|eier
r_volatile
id|u32
id|eier
suffix:semicolon
multiline_comment|/* 0x000f8  */
DECL|member|ercsr
r_volatile
id|u32
id|ercsr
suffix:semicolon
multiline_comment|/* 0x000fc  */
DECL|member|erbr_h
r_volatile
id|u32
id|erbr_h
suffix:semicolon
multiline_comment|/* 0x00100  */
DECL|member|erbr_l
r_volatile
id|u32
id|erbr_l
suffix:semicolon
multiline_comment|/* 0x00104  */
DECL|member|erbar
r_volatile
id|u32
id|erbar
suffix:semicolon
multiline_comment|/* 0x00108  */
DECL|member|ercir
r_volatile
id|u32
id|ercir
suffix:semicolon
multiline_comment|/* 0x0010c  */
DECL|member|erpir
r_volatile
id|u32
id|erpir
suffix:semicolon
multiline_comment|/* 0x00110  */
DECL|member|ertr
r_volatile
id|u32
id|ertr
suffix:semicolon
multiline_comment|/* 0x00114  */
DECL|member|etcsr
r_volatile
id|u32
id|etcsr
suffix:semicolon
multiline_comment|/* 0x00118  */
DECL|member|ersr
r_volatile
id|u32
id|ersr
suffix:semicolon
multiline_comment|/* 0x0011c  */
DECL|member|etcdc
r_volatile
id|u32
id|etcdc
suffix:semicolon
multiline_comment|/* 0x00120  */
DECL|member|ebir
r_volatile
id|u32
id|ebir
suffix:semicolon
multiline_comment|/* 0x00124  */
DECL|member|etbr_h
r_volatile
id|u32
id|etbr_h
suffix:semicolon
multiline_comment|/* 0x00128  */
DECL|member|etbr_l
r_volatile
id|u32
id|etbr_l
suffix:semicolon
multiline_comment|/* 0x0012c  */
DECL|member|etcir
r_volatile
id|u32
id|etcir
suffix:semicolon
multiline_comment|/* 0x00130  */
DECL|member|etpir
r_volatile
id|u32
id|etpir
suffix:semicolon
multiline_comment|/* 0x00134  */
DECL|member|emar_h
r_volatile
id|u32
id|emar_h
suffix:semicolon
multiline_comment|/* 0x00138  */
DECL|member|emar_l
r_volatile
id|u32
id|emar_l
suffix:semicolon
multiline_comment|/* 0x0013c  */
DECL|member|ehar_h
r_volatile
id|u32
id|ehar_h
suffix:semicolon
multiline_comment|/* 0x00140  */
DECL|member|ehar_l
r_volatile
id|u32
id|ehar_l
suffix:semicolon
multiline_comment|/* 0x00144  */
DECL|member|micr
r_volatile
id|u32
id|micr
suffix:semicolon
multiline_comment|/* 0x00148  */
DECL|member|midr_r
r_volatile
id|u32
id|midr_r
suffix:semicolon
multiline_comment|/* 0x0014c  */
DECL|member|midr_w
r_volatile
id|u32
id|midr_w
suffix:semicolon
multiline_comment|/* 0x00150  */
DECL|member|pad1
r_volatile
id|u32
id|pad1
(braket
(paren
l_int|0x20000
op_minus
l_int|0x00154
)paren
op_div
l_int|4
)braket
suffix:semicolon
multiline_comment|/* SuperIO Registers  XXX */
DECL|member|sregs
r_struct
id|ioc3_sioregs
id|sregs
suffix:semicolon
multiline_comment|/* 0x20000 */
DECL|member|pad2
r_volatile
id|u32
id|pad2
(braket
(paren
l_int|0x40000
op_minus
l_int|0x20180
)paren
op_div
l_int|4
)braket
suffix:semicolon
multiline_comment|/* SSRAM Diagnostic Access */
DECL|member|ssram
r_volatile
id|u32
id|ssram
(braket
(paren
l_int|0x80000
op_minus
l_int|0x40000
)paren
op_div
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Bytebus device offsets&n;&t;   0x80000 -   Access to the generic devices selected with   DEV0&n;&t;   0x9FFFF     bytebus DEV_SEL_0&n;&t;   0xA0000 -   Access to the generic devices selected with   DEV1&n;&t;   0xBFFFF     bytebus DEV_SEL_1&n;&t;   0xC0000 -   Access to the generic devices selected with   DEV2&n;&t;   0xDFFFF     bytebus DEV_SEL_2&n;&t;   0xE0000 -   Access to the generic devices selected with   DEV3&n;&t;   0xFFFFF     bytebus DEV_SEL_3  */
)brace
suffix:semicolon
multiline_comment|/*&n; * Ethernet RX Buffer&n; */
DECL|struct|ioc3_erxbuf
r_struct
id|ioc3_erxbuf
(brace
DECL|member|w0
id|u32
id|w0
suffix:semicolon
multiline_comment|/* first word (valid,bcnt,cksum) */
DECL|member|err
id|u32
id|err
suffix:semicolon
multiline_comment|/* second word various errors */
multiline_comment|/* next comes n bytes of padding */
multiline_comment|/* then the received ethernet frame itself */
)brace
suffix:semicolon
DECL|macro|ERXBUF_IPCKSUM_MASK
mdefine_line|#define ERXBUF_IPCKSUM_MASK&t;0x0000ffff
DECL|macro|ERXBUF_BYTECNT_MASK
mdefine_line|#define ERXBUF_BYTECNT_MASK&t;0x07ff0000
DECL|macro|ERXBUF_BYTECNT_SHIFT
mdefine_line|#define ERXBUF_BYTECNT_SHIFT&t;16
DECL|macro|ERXBUF_V
mdefine_line|#define ERXBUF_V&t;&t;0x80000000
DECL|macro|ERXBUF_CRCERR
mdefine_line|#define ERXBUF_CRCERR&t;&t;0x00000001&t;/* aka RSV15 */
DECL|macro|ERXBUF_FRAMERR
mdefine_line|#define ERXBUF_FRAMERR&t;&t;0x00000002&t;/* aka RSV14 */
DECL|macro|ERXBUF_CODERR
mdefine_line|#define ERXBUF_CODERR&t;&t;0x00000004&t;/* aka RSV13 */
DECL|macro|ERXBUF_INVPREAMB
mdefine_line|#define ERXBUF_INVPREAMB&t;0x00000008&t;/* aka RSV18 */
DECL|macro|ERXBUF_LOLEN
mdefine_line|#define ERXBUF_LOLEN&t;&t;0x00007000&t;/* aka RSV2_0 */
DECL|macro|ERXBUF_HILEN
mdefine_line|#define ERXBUF_HILEN&t;&t;0x03ff0000&t;/* aka RSV12_3 */
DECL|macro|ERXBUF_MULTICAST
mdefine_line|#define ERXBUF_MULTICAST&t;0x04000000&t;/* aka RSV16 */
DECL|macro|ERXBUF_BROADCAST
mdefine_line|#define ERXBUF_BROADCAST&t;0x08000000&t;/* aka RSV17 */
DECL|macro|ERXBUF_LONGEVENT
mdefine_line|#define ERXBUF_LONGEVENT&t;0x10000000&t;/* aka RSV19 */
DECL|macro|ERXBUF_BADPKT
mdefine_line|#define ERXBUF_BADPKT&t;&t;0x20000000&t;/* aka RSV20 */
DECL|macro|ERXBUF_GOODPKT
mdefine_line|#define ERXBUF_GOODPKT&t;&t;0x40000000&t;/* aka RSV21 */
DECL|macro|ERXBUF_CARRIER
mdefine_line|#define ERXBUF_CARRIER&t;&t;0x80000000&t;/* aka RSV22 */
multiline_comment|/*&n; * Ethernet TX Descriptor&n; */
DECL|macro|ETXD_DATALEN
mdefine_line|#define ETXD_DATALEN    104
DECL|struct|ioc3_etxd
r_struct
id|ioc3_etxd
(brace
DECL|member|cmd
id|u32
id|cmd
suffix:semicolon
multiline_comment|/* command field */
DECL|member|bufcnt
id|u32
id|bufcnt
suffix:semicolon
multiline_comment|/* buffer counts field */
DECL|member|p1
id|u64
id|p1
suffix:semicolon
multiline_comment|/* buffer pointer 1 */
DECL|member|p2
id|u64
id|p2
suffix:semicolon
multiline_comment|/* buffer pointer 2 */
DECL|member|data
id|u8
id|data
(braket
id|ETXD_DATALEN
)braket
suffix:semicolon
multiline_comment|/* opt. tx data */
)brace
suffix:semicolon
DECL|macro|ETXD_BYTECNT_MASK
mdefine_line|#define ETXD_BYTECNT_MASK&t;0x000007ff&t;/* total byte count */
DECL|macro|ETXD_INTWHENDONE
mdefine_line|#define ETXD_INTWHENDONE&t;0x00001000&t;/* intr when done */
DECL|macro|ETXD_D0V
mdefine_line|#define ETXD_D0V&t;&t;0x00010000&t;/* data 0 valid */
DECL|macro|ETXD_B1V
mdefine_line|#define ETXD_B1V&t;&t;0x00020000&t;/* buf 1 valid */
DECL|macro|ETXD_B2V
mdefine_line|#define ETXD_B2V&t;&t;0x00040000&t;/* buf 2 valid */
DECL|macro|ETXD_DOCHECKSUM
mdefine_line|#define ETXD_DOCHECKSUM&t;&t;0x00080000&t;/* insert ip cksum */
DECL|macro|ETXD_CHKOFF_MASK
mdefine_line|#define ETXD_CHKOFF_MASK&t;0x07f00000&t;/* cksum byte offset */
DECL|macro|ETXD_CHKOFF_SHIFT
mdefine_line|#define ETXD_CHKOFF_SHIFT&t;20
DECL|macro|ETXD_D0CNT_MASK
mdefine_line|#define ETXD_D0CNT_MASK&t;&t;0x0000007f
DECL|macro|ETXD_B1CNT_MASK
mdefine_line|#define ETXD_B1CNT_MASK&t;&t;0x0007ff00
DECL|macro|ETXD_B1CNT_SHIFT
mdefine_line|#define ETXD_B1CNT_SHIFT&t;8
DECL|macro|ETXD_B2CNT_MASK
mdefine_line|#define ETXD_B2CNT_MASK&t;&t;0x7ff00000
DECL|macro|ETXD_B2CNT_SHIFT
mdefine_line|#define ETXD_B2CNT_SHIFT&t;20
multiline_comment|/*&n; * Bytebus device space&n; */
DECL|macro|IOC3_BYTEBUS_DEV0
mdefine_line|#define IOC3_BYTEBUS_DEV0&t;0x80000L
DECL|macro|IOC3_BYTEBUS_DEV1
mdefine_line|#define IOC3_BYTEBUS_DEV1&t;0xa0000L
DECL|macro|IOC3_BYTEBUS_DEV2
mdefine_line|#define IOC3_BYTEBUS_DEV2&t;0xc0000L
DECL|macro|IOC3_BYTEBUS_DEV3
mdefine_line|#define IOC3_BYTEBUS_DEV3&t;0xe0000L
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* Superio Registers (PIO Access) */
DECL|macro|IOC3_SIO_BASE
mdefine_line|#define IOC3_SIO_BASE&t;&t;0x20000
DECL|macro|IOC3_SIO_UARTC
mdefine_line|#define IOC3_SIO_UARTC&t;&t;(IOC3_SIO_BASE+0x141)&t;/* UART Config */
DECL|macro|IOC3_SIO_KBDCG
mdefine_line|#define IOC3_SIO_KBDCG&t;&t;(IOC3_SIO_BASE+0x142)&t;/* KBD Config */
DECL|macro|IOC3_SIO_PP_BASE
mdefine_line|#define IOC3_SIO_PP_BASE&t;(IOC3_SIO_BASE+PP_BASE)&t;&t;/* Parallel Port */
DECL|macro|IOC3_SIO_RTC_BASE
mdefine_line|#define IOC3_SIO_RTC_BASE&t;(IOC3_SIO_BASE+0x168)&t;/* Real Time Clock */
DECL|macro|IOC3_SIO_UB_BASE
mdefine_line|#define IOC3_SIO_UB_BASE&t;(IOC3_SIO_BASE+UARTB_BASE)&t;/* UART B */
DECL|macro|IOC3_SIO_UA_BASE
mdefine_line|#define IOC3_SIO_UA_BASE&t;(IOC3_SIO_BASE+UARTA_BASE)&t;/* UART A */
multiline_comment|/* SSRAM Diagnostic Access */
DECL|macro|IOC3_SSRAM
mdefine_line|#define IOC3_SSRAM&t;IOC3_RAM_OFF&t;/* base of SSRAM diagnostic access */
DECL|macro|IOC3_SSRAM_LEN
mdefine_line|#define IOC3_SSRAM_LEN&t;0x40000 /* 256kb (address space size, may not be fully populated) */
DECL|macro|IOC3_SSRAM_DM
mdefine_line|#define IOC3_SSRAM_DM&t;0x0000ffff&t;/* data mask */
DECL|macro|IOC3_SSRAM_PM
mdefine_line|#define IOC3_SSRAM_PM&t;0x00010000&t;/* parity mask */
multiline_comment|/* bitmasks for PCI_SCR */
DECL|macro|PCI_SCR_PAR_RESP_EN
mdefine_line|#define PCI_SCR_PAR_RESP_EN&t;0x00000040&t;/* enb PCI parity checking */
DECL|macro|PCI_SCR_SERR_EN
mdefine_line|#define PCI_SCR_SERR_EN&t;&t;0x00000100&t;/* enable the SERR# driver */
DECL|macro|PCI_SCR_DROP_MODE_EN
mdefine_line|#define PCI_SCR_DROP_MODE_EN&t;0x00008000&t;/* drop pios on parity err */
DECL|macro|PCI_SCR_RX_SERR
mdefine_line|#define PCI_SCR_RX_SERR&t;&t;(0x1 &lt;&lt; 16)
DECL|macro|PCI_SCR_DROP_MODE
mdefine_line|#define PCI_SCR_DROP_MODE&t;(0x1 &lt;&lt; 17)
DECL|macro|PCI_SCR_SIG_PAR_ERR
mdefine_line|#define PCI_SCR_SIG_PAR_ERR&t;(0x1 &lt;&lt; 24)
DECL|macro|PCI_SCR_SIG_TAR_ABRT
mdefine_line|#define PCI_SCR_SIG_TAR_ABRT&t;(0x1 &lt;&lt; 27)
DECL|macro|PCI_SCR_RX_TAR_ABRT
mdefine_line|#define PCI_SCR_RX_TAR_ABRT&t;(0x1 &lt;&lt; 28)
DECL|macro|PCI_SCR_SIG_MST_ABRT
mdefine_line|#define PCI_SCR_SIG_MST_ABRT&t;(0x1 &lt;&lt; 29)
DECL|macro|PCI_SCR_SIG_SERR
mdefine_line|#define PCI_SCR_SIG_SERR&t;(0x1 &lt;&lt; 30)
DECL|macro|PCI_SCR_PAR_ERR
mdefine_line|#define PCI_SCR_PAR_ERR&t;&t;(0x1 &lt;&lt; 31)
multiline_comment|/* bitmasks for IOC3_KM_CSR */
DECL|macro|KM_CSR_K_WRT_PEND
mdefine_line|#define KM_CSR_K_WRT_PEND 0x00000001&t;/* kbd port xmitting or resetting */
DECL|macro|KM_CSR_M_WRT_PEND
mdefine_line|#define KM_CSR_M_WRT_PEND 0x00000002&t;/* mouse port xmitting or resetting */
DECL|macro|KM_CSR_K_LCB
mdefine_line|#define KM_CSR_K_LCB&t;  0x00000004&t;/* Line Cntrl Bit for last KBD write */
DECL|macro|KM_CSR_M_LCB
mdefine_line|#define KM_CSR_M_LCB&t;  0x00000008&t;/* same for mouse */
DECL|macro|KM_CSR_K_DATA
mdefine_line|#define KM_CSR_K_DATA&t;  0x00000010&t;/* state of kbd data line */
DECL|macro|KM_CSR_K_CLK
mdefine_line|#define KM_CSR_K_CLK&t;  0x00000020&t;/* state of kbd clock line */
DECL|macro|KM_CSR_K_PULL_DATA
mdefine_line|#define KM_CSR_K_PULL_DATA 0x00000040&t;/* pull kbd data line low */
DECL|macro|KM_CSR_K_PULL_CLK
mdefine_line|#define KM_CSR_K_PULL_CLK 0x00000080&t;/* pull kbd clock line low */
DECL|macro|KM_CSR_M_DATA
mdefine_line|#define KM_CSR_M_DATA&t;  0x00000100&t;/* state of ms data line */
DECL|macro|KM_CSR_M_CLK
mdefine_line|#define KM_CSR_M_CLK&t;  0x00000200&t;/* state of ms clock line */
DECL|macro|KM_CSR_M_PULL_DATA
mdefine_line|#define KM_CSR_M_PULL_DATA 0x00000400&t;/* pull ms data line low */
DECL|macro|KM_CSR_M_PULL_CLK
mdefine_line|#define KM_CSR_M_PULL_CLK 0x00000800&t;/* pull ms clock line low */
DECL|macro|KM_CSR_EMM_MODE
mdefine_line|#define KM_CSR_EMM_MODE&t;  0x00001000&t;/* emulation mode */
DECL|macro|KM_CSR_SIM_MODE
mdefine_line|#define KM_CSR_SIM_MODE&t;  0x00002000&t;/* clock X8 */
DECL|macro|KM_CSR_K_SM_IDLE
mdefine_line|#define KM_CSR_K_SM_IDLE  0x00004000&t;/* Keyboard is idle */
DECL|macro|KM_CSR_M_SM_IDLE
mdefine_line|#define KM_CSR_M_SM_IDLE  0x00008000&t;/* Mouse is idle */
DECL|macro|KM_CSR_K_TO
mdefine_line|#define KM_CSR_K_TO&t;  0x00010000&t;/* Keyboard trying to send/receive */
DECL|macro|KM_CSR_M_TO
mdefine_line|#define KM_CSR_M_TO&t;  0x00020000&t;/* Mouse trying to send/receive */
DECL|macro|KM_CSR_K_TO_EN
mdefine_line|#define KM_CSR_K_TO_EN&t;  0x00040000&t;/* KM_CSR_K_TO + KM_CSR_K_TO_EN = cause&n;&t;&t;&t;&t;&t;   SIO_IR to assert */
DECL|macro|KM_CSR_M_TO_EN
mdefine_line|#define KM_CSR_M_TO_EN&t;  0x00080000&t;/* KM_CSR_M_TO + KM_CSR_M_TO_EN = cause&n;&t;&t;&t;&t;&t;   SIO_IR to assert */
DECL|macro|KM_CSR_K_CLAMP_ONE
mdefine_line|#define KM_CSR_K_CLAMP_ONE&t;0x00100000&t;/* Pull K_CLK low after rec. one char */
DECL|macro|KM_CSR_M_CLAMP_ONE
mdefine_line|#define KM_CSR_M_CLAMP_ONE&t;0x00200000&t;/* Pull M_CLK low after rec. one char */
DECL|macro|KM_CSR_K_CLAMP_THREE
mdefine_line|#define KM_CSR_K_CLAMP_THREE&t;0x00400000&t;/* Pull K_CLK low after rec. three chars */
DECL|macro|KM_CSR_M_CLAMP_THREE
mdefine_line|#define KM_CSR_M_CLAMP_THREE&t;0x00800000&t;/* Pull M_CLK low after rec. three char */
multiline_comment|/* bitmasks for IOC3_K_RD and IOC3_M_RD */
DECL|macro|KM_RD_DATA_2
mdefine_line|#define KM_RD_DATA_2&t;0x000000ff&t;/* 3rd char recvd since last read */
DECL|macro|KM_RD_DATA_2_SHIFT
mdefine_line|#define KM_RD_DATA_2_SHIFT 0
DECL|macro|KM_RD_DATA_1
mdefine_line|#define KM_RD_DATA_1&t;0x0000ff00&t;/* 2nd char recvd since last read */
DECL|macro|KM_RD_DATA_1_SHIFT
mdefine_line|#define KM_RD_DATA_1_SHIFT 8
DECL|macro|KM_RD_DATA_0
mdefine_line|#define KM_RD_DATA_0&t;0x00ff0000&t;/* 1st char recvd since last read */
DECL|macro|KM_RD_DATA_0_SHIFT
mdefine_line|#define KM_RD_DATA_0_SHIFT 16
DECL|macro|KM_RD_FRAME_ERR_2
mdefine_line|#define KM_RD_FRAME_ERR_2 0x01000000&t;/*  framing or parity error in byte 2 */
DECL|macro|KM_RD_FRAME_ERR_1
mdefine_line|#define KM_RD_FRAME_ERR_1 0x02000000&t;/* same for byte 1 */
DECL|macro|KM_RD_FRAME_ERR_0
mdefine_line|#define KM_RD_FRAME_ERR_0 0x04000000&t;/* same for byte 0 */
DECL|macro|KM_RD_KBD_MSE
mdefine_line|#define KM_RD_KBD_MSE&t;0x08000000&t;/* 0 if from kbd, 1 if from mouse */
DECL|macro|KM_RD_OFLO
mdefine_line|#define KM_RD_OFLO&t;0x10000000&t;/* 4th char recvd before this read */
DECL|macro|KM_RD_VALID_2
mdefine_line|#define KM_RD_VALID_2&t;0x20000000&t;/* DATA_2 valid */
DECL|macro|KM_RD_VALID_1
mdefine_line|#define KM_RD_VALID_1&t;0x40000000&t;/* DATA_1 valid */
DECL|macro|KM_RD_VALID_0
mdefine_line|#define KM_RD_VALID_0&t;0x80000000&t;/* DATA_0 valid */
DECL|macro|KM_RD_VALID_ALL
mdefine_line|#define KM_RD_VALID_ALL (KM_RD_VALID_0|KM_RD_VALID_1|KM_RD_VALID_2)
multiline_comment|/* bitmasks for IOC3_K_WD &amp; IOC3_M_WD */
DECL|macro|KM_WD_WRT_DATA
mdefine_line|#define KM_WD_WRT_DATA&t;0x000000ff&t;/* write to keyboard/mouse port */
DECL|macro|KM_WD_WRT_DATA_SHIFT
mdefine_line|#define KM_WD_WRT_DATA_SHIFT 0
multiline_comment|/* bitmasks for serial RX status byte */
DECL|macro|RXSB_OVERRUN
mdefine_line|#define RXSB_OVERRUN&t;0x01&t;/* char(s) lost */
DECL|macro|RXSB_PAR_ERR
mdefine_line|#define RXSB_PAR_ERR&t;0x02&t;/* parity error */
DECL|macro|RXSB_FRAME_ERR
mdefine_line|#define RXSB_FRAME_ERR&t;0x04&t;/* framing error */
DECL|macro|RXSB_BREAK
mdefine_line|#define RXSB_BREAK&t;0x08&t;/* break character */
DECL|macro|RXSB_CTS
mdefine_line|#define RXSB_CTS&t;0x10&t;/* state of CTS */
DECL|macro|RXSB_DCD
mdefine_line|#define RXSB_DCD&t;0x20&t;/* state of DCD */
DECL|macro|RXSB_MODEM_VALID
mdefine_line|#define RXSB_MODEM_VALID 0x40&t;/* DCD, CTS and OVERRUN are valid */
DECL|macro|RXSB_DATA_VALID
mdefine_line|#define RXSB_DATA_VALID 0x80&t;/* data byte, FRAME_ERR PAR_ERR &amp; BREAK valid */
multiline_comment|/* bitmasks for serial TX control byte */
DECL|macro|TXCB_INT_WHEN_DONE
mdefine_line|#define TXCB_INT_WHEN_DONE 0x20 /* interrupt after this byte is sent */
DECL|macro|TXCB_INVALID
mdefine_line|#define TXCB_INVALID&t;0x00&t;/* byte is invalid */
DECL|macro|TXCB_VALID
mdefine_line|#define TXCB_VALID&t;0x40&t;/* byte is valid */
DECL|macro|TXCB_MCR
mdefine_line|#define TXCB_MCR&t;0x80&t;/* data&lt;7:0&gt; to modem control register */
DECL|macro|TXCB_DELAY
mdefine_line|#define TXCB_DELAY&t;0xc0&t;/* delay data&lt;7:0&gt; mSec */
multiline_comment|/* bitmasks for IOC3_SBBR_L */
DECL|macro|SBBR_L_SIZE
mdefine_line|#define SBBR_L_SIZE&t;0x00000001&t;/* 0 == 1KB rings, 1 == 4KB rings */
DECL|macro|SBBR_L_BASE
mdefine_line|#define SBBR_L_BASE&t;0xfffff000&t;/* lower serial ring base addr */
multiline_comment|/* bitmasks for IOC3_SSCR_&lt;A:B&gt; */
DECL|macro|SSCR_RX_THRESHOLD
mdefine_line|#define SSCR_RX_THRESHOLD 0x000001ff&t;/* hiwater mark */
DECL|macro|SSCR_TX_TIMER_BUSY
mdefine_line|#define SSCR_TX_TIMER_BUSY 0x00010000&t;/* TX timer in progress */
DECL|macro|SSCR_HFC_EN
mdefine_line|#define SSCR_HFC_EN&t;0x00020000&t;/* hardware flow control enabled */
DECL|macro|SSCR_RX_RING_DCD
mdefine_line|#define SSCR_RX_RING_DCD 0x00040000&t;/* post RX record on delta-DCD */
DECL|macro|SSCR_RX_RING_CTS
mdefine_line|#define SSCR_RX_RING_CTS 0x00080000&t;/* post RX record on delta-CTS */
DECL|macro|SSCR_HIGH_SPD
mdefine_line|#define SSCR_HIGH_SPD&t;0x00100000&t;/* 4X speed */
DECL|macro|SSCR_DIAG
mdefine_line|#define SSCR_DIAG&t;0x00200000&t;/* bypass clock divider for sim */
DECL|macro|SSCR_RX_DRAIN
mdefine_line|#define SSCR_RX_DRAIN&t;0x08000000&t;/* drain RX buffer to memory */
DECL|macro|SSCR_DMA_EN
mdefine_line|#define SSCR_DMA_EN&t;0x10000000&t;/* enable ring buffer DMA */
DECL|macro|SSCR_DMA_PAUSE
mdefine_line|#define SSCR_DMA_PAUSE&t;0x20000000&t;/* pause DMA */
DECL|macro|SSCR_PAUSE_STATE
mdefine_line|#define SSCR_PAUSE_STATE 0x40000000&t;/* sets when PAUSE takes effect */
DECL|macro|SSCR_RESET
mdefine_line|#define SSCR_RESET&t;0x80000000&t;/* reset DMA channels */
multiline_comment|/* all producer/comsumer pointers are the same bitfield */
DECL|macro|PROD_CONS_PTR_4K
mdefine_line|#define PROD_CONS_PTR_4K 0x00000ff8&t;/* for 4K buffers */
DECL|macro|PROD_CONS_PTR_1K
mdefine_line|#define PROD_CONS_PTR_1K 0x000003f8&t;/* for 1K buffers */
DECL|macro|PROD_CONS_PTR_OFF
mdefine_line|#define PROD_CONS_PTR_OFF 3
multiline_comment|/* bitmasks for IOC3_SRCIR_&lt;A:B&gt; */
DECL|macro|SRCIR_ARM
mdefine_line|#define SRCIR_ARM&t;0x80000000&t;/* arm RX timer */
multiline_comment|/* bitmasks for IOC3_SRPIR_&lt;A:B&gt; */
DECL|macro|SRPIR_BYTE_CNT
mdefine_line|#define SRPIR_BYTE_CNT&t;0x07000000&t;/* bytes in packer */
DECL|macro|SRPIR_BYTE_CNT_SHIFT
mdefine_line|#define SRPIR_BYTE_CNT_SHIFT 24
multiline_comment|/* bitmasks for IOC3_STCIR_&lt;A:B&gt; */
DECL|macro|STCIR_BYTE_CNT
mdefine_line|#define STCIR_BYTE_CNT&t;0x0f000000&t;/* bytes in unpacker */
DECL|macro|STCIR_BYTE_CNT_SHIFT
mdefine_line|#define STCIR_BYTE_CNT_SHIFT 24
multiline_comment|/* bitmasks for IOC3_SHADOW_&lt;A:B&gt; */
DECL|macro|SHADOW_DR
mdefine_line|#define SHADOW_DR&t;0x00000001&t;/* data ready */
DECL|macro|SHADOW_OE
mdefine_line|#define SHADOW_OE&t;0x00000002&t;/* overrun error */
DECL|macro|SHADOW_PE
mdefine_line|#define SHADOW_PE&t;0x00000004&t;/* parity error */
DECL|macro|SHADOW_FE
mdefine_line|#define SHADOW_FE&t;0x00000008&t;/* framing error */
DECL|macro|SHADOW_BI
mdefine_line|#define SHADOW_BI&t;0x00000010&t;/* break interrupt */
DECL|macro|SHADOW_THRE
mdefine_line|#define SHADOW_THRE&t;0x00000020&t;/* transmit holding register empty */
DECL|macro|SHADOW_TEMT
mdefine_line|#define SHADOW_TEMT&t;0x00000040&t;/* transmit shift register empty */
DECL|macro|SHADOW_RFCE
mdefine_line|#define SHADOW_RFCE&t;0x00000080&t;/* char in RX fifo has an error */
DECL|macro|SHADOW_DCTS
mdefine_line|#define SHADOW_DCTS&t;0x00010000&t;/* delta clear to send */
DECL|macro|SHADOW_DDCD
mdefine_line|#define SHADOW_DDCD&t;0x00080000&t;/* delta data carrier detect */
DECL|macro|SHADOW_CTS
mdefine_line|#define SHADOW_CTS&t;0x00100000&t;/* clear to send */
DECL|macro|SHADOW_DCD
mdefine_line|#define SHADOW_DCD&t;0x00800000&t;/* data carrier detect */
DECL|macro|SHADOW_DTR
mdefine_line|#define SHADOW_DTR&t;0x01000000&t;/* data terminal ready */
DECL|macro|SHADOW_RTS
mdefine_line|#define SHADOW_RTS&t;0x02000000&t;/* request to send */
DECL|macro|SHADOW_OUT1
mdefine_line|#define SHADOW_OUT1&t;0x04000000&t;/* 16550 OUT1 bit */
DECL|macro|SHADOW_OUT2
mdefine_line|#define SHADOW_OUT2&t;0x08000000&t;/* 16550 OUT2 bit */
DECL|macro|SHADOW_LOOP
mdefine_line|#define SHADOW_LOOP&t;0x10000000&t;/* loopback enabled */
multiline_comment|/* bitmasks for IOC3_SRTR_&lt;A:B&gt; */
DECL|macro|SRTR_CNT
mdefine_line|#define SRTR_CNT&t;0x00000fff&t;/* reload value for RX timer */
DECL|macro|SRTR_CNT_VAL
mdefine_line|#define SRTR_CNT_VAL&t;0x0fff0000&t;/* current value of RX timer */
DECL|macro|SRTR_CNT_VAL_SHIFT
mdefine_line|#define SRTR_CNT_VAL_SHIFT 16
DECL|macro|SRTR_HZ
mdefine_line|#define SRTR_HZ&t;&t;16000&t;/* SRTR clock frequency */
multiline_comment|/* bitmasks for IOC3_SIO_IR, IOC3_SIO_IEC and IOC3_SIO_IES  */
DECL|macro|SIO_IR_SA_TX_MT
mdefine_line|#define SIO_IR_SA_TX_MT&t;&t;0x00000001&t;/* Serial port A TX empty */
DECL|macro|SIO_IR_SA_RX_FULL
mdefine_line|#define SIO_IR_SA_RX_FULL&t;0x00000002&t;/* port A RX buf full */
DECL|macro|SIO_IR_SA_RX_HIGH
mdefine_line|#define SIO_IR_SA_RX_HIGH&t;0x00000004&t;/* port A RX hiwat */
DECL|macro|SIO_IR_SA_RX_TIMER
mdefine_line|#define SIO_IR_SA_RX_TIMER&t;0x00000008&t;/* port A RX timeout */
DECL|macro|SIO_IR_SA_DELTA_DCD
mdefine_line|#define SIO_IR_SA_DELTA_DCD&t;0x00000010&t;/* port A delta DCD */
DECL|macro|SIO_IR_SA_DELTA_CTS
mdefine_line|#define SIO_IR_SA_DELTA_CTS&t;0x00000020&t;/* port A delta CTS */
DECL|macro|SIO_IR_SA_INT
mdefine_line|#define SIO_IR_SA_INT&t;&t;0x00000040&t;/* port A pass-thru intr */
DECL|macro|SIO_IR_SA_TX_EXPLICIT
mdefine_line|#define SIO_IR_SA_TX_EXPLICIT&t;0x00000080&t;/* port A explicit TX thru */
DECL|macro|SIO_IR_SA_MEMERR
mdefine_line|#define SIO_IR_SA_MEMERR&t;0x00000100&t;/* port A PCI error */
DECL|macro|SIO_IR_SB_TX_MT
mdefine_line|#define SIO_IR_SB_TX_MT&t;&t;0x00000200&t;/* */
DECL|macro|SIO_IR_SB_RX_FULL
mdefine_line|#define SIO_IR_SB_RX_FULL&t;0x00000400&t;/* */
DECL|macro|SIO_IR_SB_RX_HIGH
mdefine_line|#define SIO_IR_SB_RX_HIGH&t;0x00000800&t;/* */
DECL|macro|SIO_IR_SB_RX_TIMER
mdefine_line|#define SIO_IR_SB_RX_TIMER&t;0x00001000&t;/* */
DECL|macro|SIO_IR_SB_DELTA_DCD
mdefine_line|#define SIO_IR_SB_DELTA_DCD&t;0x00002000&t;/* */
DECL|macro|SIO_IR_SB_DELTA_CTS
mdefine_line|#define SIO_IR_SB_DELTA_CTS&t;0x00004000&t;/* */
DECL|macro|SIO_IR_SB_INT
mdefine_line|#define SIO_IR_SB_INT&t;&t;0x00008000&t;/* */
DECL|macro|SIO_IR_SB_TX_EXPLICIT
mdefine_line|#define SIO_IR_SB_TX_EXPLICIT&t;0x00010000&t;/* */
DECL|macro|SIO_IR_SB_MEMERR
mdefine_line|#define SIO_IR_SB_MEMERR&t;0x00020000&t;/* */
DECL|macro|SIO_IR_PP_INT
mdefine_line|#define SIO_IR_PP_INT&t;&t;0x00040000&t;/* P port pass-thru intr */
DECL|macro|SIO_IR_PP_INTA
mdefine_line|#define SIO_IR_PP_INTA&t;&t;0x00080000&t;/* PP context A thru */
DECL|macro|SIO_IR_PP_INTB
mdefine_line|#define SIO_IR_PP_INTB&t;&t;0x00100000&t;/* PP context B thru */
DECL|macro|SIO_IR_PP_MEMERR
mdefine_line|#define SIO_IR_PP_MEMERR&t;0x00200000&t;/* PP PCI error */
DECL|macro|SIO_IR_KBD_INT
mdefine_line|#define SIO_IR_KBD_INT&t;&t;0x00400000&t;/* kbd/mouse intr */
DECL|macro|SIO_IR_RT_INT
mdefine_line|#define SIO_IR_RT_INT&t;&t;0x08000000&t;/* RT output pulse */
DECL|macro|SIO_IR_GEN_INT1
mdefine_line|#define SIO_IR_GEN_INT1&t;&t;0x10000000&t;/* RT input pulse */
DECL|macro|SIO_IR_GEN_INT_SHIFT
mdefine_line|#define SIO_IR_GEN_INT_SHIFT&t;28
multiline_comment|/* per device interrupt masks */
DECL|macro|SIO_IR_SA
mdefine_line|#define SIO_IR_SA&t;&t;(SIO_IR_SA_TX_MT | SIO_IR_SA_RX_FULL | &bslash;&n;&t;&t;&t;&t; SIO_IR_SA_RX_HIGH | SIO_IR_SA_RX_TIMER | &bslash;&n;&t;&t;&t;&t; SIO_IR_SA_DELTA_DCD | SIO_IR_SA_DELTA_CTS | &bslash;&n;&t;&t;&t;&t; SIO_IR_SA_INT | SIO_IR_SA_TX_EXPLICIT | &bslash;&n;&t;&t;&t;&t; SIO_IR_SA_MEMERR)
DECL|macro|SIO_IR_SB
mdefine_line|#define SIO_IR_SB&t;&t;(SIO_IR_SB_TX_MT | SIO_IR_SB_RX_FULL | &bslash;&n;&t;&t;&t;&t; SIO_IR_SB_RX_HIGH | SIO_IR_SB_RX_TIMER | &bslash;&n;&t;&t;&t;&t; SIO_IR_SB_DELTA_DCD | SIO_IR_SB_DELTA_CTS | &bslash;&n;&t;&t;&t;&t; SIO_IR_SB_INT | SIO_IR_SB_TX_EXPLICIT | &bslash;&n;&t;&t;&t;&t; SIO_IR_SB_MEMERR)
DECL|macro|SIO_IR_PP
mdefine_line|#define SIO_IR_PP&t;&t;(SIO_IR_PP_INT | SIO_IR_PP_INTA | &bslash;&n;&t;&t;&t;&t; SIO_IR_PP_INTB | SIO_IR_PP_MEMERR)
DECL|macro|SIO_IR_RT
mdefine_line|#define SIO_IR_RT&t;&t;(SIO_IR_RT_INT | SIO_IR_GEN_INT1)
multiline_comment|/* macro to load pending interrupts */
DECL|macro|IOC3_PENDING_INTRS
mdefine_line|#define IOC3_PENDING_INTRS(mem) (PCI_INW(&amp;((mem)-&gt;sio_ir)) &amp; &bslash;&n;&t;&t;&t;&t; PCI_INW(&amp;((mem)-&gt;sio_ies_ro)))
multiline_comment|/* bitmasks for SIO_CR */
DECL|macro|SIO_CR_SIO_RESET
mdefine_line|#define SIO_CR_SIO_RESET&t;0x00000001&t;/* reset the SIO */
DECL|macro|SIO_CR_SER_A_BASE
mdefine_line|#define SIO_CR_SER_A_BASE&t;0x000000fe&t;/* DMA poll addr port A */
DECL|macro|SIO_CR_SER_A_BASE_SHIFT
mdefine_line|#define SIO_CR_SER_A_BASE_SHIFT 1
DECL|macro|SIO_CR_SER_B_BASE
mdefine_line|#define SIO_CR_SER_B_BASE&t;0x00007f00&t;/* DMA poll addr port B */
DECL|macro|SIO_CR_SER_B_BASE_SHIFT
mdefine_line|#define SIO_CR_SER_B_BASE_SHIFT 8
DECL|macro|SIO_SR_CMD_PULSE
mdefine_line|#define SIO_SR_CMD_PULSE&t;0x00078000&t;/* byte bus strobe length */
DECL|macro|SIO_CR_CMD_PULSE_SHIFT
mdefine_line|#define SIO_CR_CMD_PULSE_SHIFT&t;15
DECL|macro|SIO_CR_ARB_DIAG
mdefine_line|#define SIO_CR_ARB_DIAG&t;&t;0x00380000&t;/* cur !enet PCI requet (ro) */
DECL|macro|SIO_CR_ARB_DIAG_TXA
mdefine_line|#define SIO_CR_ARB_DIAG_TXA&t;0x00000000
DECL|macro|SIO_CR_ARB_DIAG_RXA
mdefine_line|#define SIO_CR_ARB_DIAG_RXA&t;0x00080000
DECL|macro|SIO_CR_ARB_DIAG_TXB
mdefine_line|#define SIO_CR_ARB_DIAG_TXB&t;0x00100000
DECL|macro|SIO_CR_ARB_DIAG_RXB
mdefine_line|#define SIO_CR_ARB_DIAG_RXB&t;0x00180000
DECL|macro|SIO_CR_ARB_DIAG_PP
mdefine_line|#define SIO_CR_ARB_DIAG_PP&t;0x00200000
DECL|macro|SIO_CR_ARB_DIAG_IDLE
mdefine_line|#define SIO_CR_ARB_DIAG_IDLE&t;0x00400000&t;/* 0 -&gt; active request (ro) */
multiline_comment|/* bitmasks for INT_OUT */
DECL|macro|INT_OUT_COUNT
mdefine_line|#define INT_OUT_COUNT&t;0x0000ffff&t;/* pulse interval timer */
DECL|macro|INT_OUT_MODE
mdefine_line|#define INT_OUT_MODE&t;0x00070000&t;/* mode mask */
DECL|macro|INT_OUT_MODE_0
mdefine_line|#define INT_OUT_MODE_0&t;0x00000000&t;/* set output to 0 */
DECL|macro|INT_OUT_MODE_1
mdefine_line|#define INT_OUT_MODE_1&t;0x00040000&t;/* set output to 1 */
DECL|macro|INT_OUT_MODE_1PULSE
mdefine_line|#define INT_OUT_MODE_1PULSE 0x00050000&t;/* send 1 pulse */
DECL|macro|INT_OUT_MODE_PULSES
mdefine_line|#define INT_OUT_MODE_PULSES 0x00060000&t;/* send 1 pulse every interval */
DECL|macro|INT_OUT_MODE_SQW
mdefine_line|#define INT_OUT_MODE_SQW 0x00070000&t;/* toggle output every interval */
DECL|macro|INT_OUT_DIAG
mdefine_line|#define INT_OUT_DIAG&t;0x40000000&t;/* diag mode */
DECL|macro|INT_OUT_INT_OUT
mdefine_line|#define INT_OUT_INT_OUT 0x80000000&t;/* current state of INT_OUT */
multiline_comment|/* time constants for INT_OUT */
DECL|macro|INT_OUT_NS_PER_TICK
mdefine_line|#define INT_OUT_NS_PER_TICK (30 * 260)&t;/* 30 ns PCI clock, divisor=260 */
DECL|macro|INT_OUT_TICKS_PER_PULSE
mdefine_line|#define INT_OUT_TICKS_PER_PULSE 3&t;/* outgoing pulse lasts 3 ticks */
DECL|macro|INT_OUT_US_TO_COUNT
mdefine_line|#define INT_OUT_US_TO_COUNT(x)&t;&t;/* convert uS to a count value */ &bslash;&n;&t;(((x) * 10 + INT_OUT_NS_PER_TICK / 200) *&t;&bslash;&n;&t; 100 / INT_OUT_NS_PER_TICK - 1)
DECL|macro|INT_OUT_COUNT_TO_US
mdefine_line|#define INT_OUT_COUNT_TO_US(x)&t;&t;/* convert count value to uS */ &bslash;&n;&t;(((x) + 1) * INT_OUT_NS_PER_TICK / 1000)
DECL|macro|INT_OUT_MIN_TICKS
mdefine_line|#define INT_OUT_MIN_TICKS 3&t;/* min period is width of pulse in &quot;ticks&quot; */
DECL|macro|INT_OUT_MAX_TICKS
mdefine_line|#define INT_OUT_MAX_TICKS INT_OUT_COUNT&t;&t;/* largest possible count */
multiline_comment|/* bitmasks for GPCR */
DECL|macro|GPCR_DIR
mdefine_line|#define GPCR_DIR&t;0x000000ff&t;/* tristate pin input or output */
DECL|macro|GPCR_DIR_PIN
mdefine_line|#define GPCR_DIR_PIN(x) (1&lt;&lt;(x))&t;/* access one of the DIR bits */
DECL|macro|GPCR_EDGE
mdefine_line|#define GPCR_EDGE&t;0x000f0000&t;/* extint edge or level sensitive */
DECL|macro|GPCR_EDGE_PIN
mdefine_line|#define GPCR_EDGE_PIN(x) (1&lt;&lt;((x)+15))&t;/* access one of the EDGE bits */
multiline_comment|/* values for GPCR */
DECL|macro|GPCR_INT_OUT_EN
mdefine_line|#define GPCR_INT_OUT_EN 0x00100000&t;/* enable INT_OUT to pin 0 */
DECL|macro|GPCR_MLAN_EN
mdefine_line|#define GPCR_MLAN_EN&t;0x00200000&t;/* enable MCR to pin 8 */
DECL|macro|GPCR_DIR_SERA_XCVR
mdefine_line|#define GPCR_DIR_SERA_XCVR 0x00000080&t;/* Port A Transceiver select enable */
DECL|macro|GPCR_DIR_SERB_XCVR
mdefine_line|#define GPCR_DIR_SERB_XCVR 0x00000040&t;/* Port B Transceiver select enable */
DECL|macro|GPCR_DIR_PHY_RST
mdefine_line|#define GPCR_DIR_PHY_RST   0x00000020&t;/* ethernet PHY reset enable */
multiline_comment|/* defs for some of the generic I/O pins */
DECL|macro|GPCR_PHY_RESET
mdefine_line|#define GPCR_PHY_RESET&t;&t;0x20&t;/* pin is output to PHY reset */
DECL|macro|GPCR_UARTB_MODESEL
mdefine_line|#define GPCR_UARTB_MODESEL&t;0x40&t;/* pin is output to port B mode sel */
DECL|macro|GPCR_UARTA_MODESEL
mdefine_line|#define GPCR_UARTA_MODESEL&t;0x80&t;/* pin is output to port A mode sel */
DECL|macro|GPPR_PHY_RESET_PIN
mdefine_line|#define GPPR_PHY_RESET_PIN&t;5&t;/* GIO pin controlling phy reset */
DECL|macro|GPPR_UARTB_MODESEL_PIN
mdefine_line|#define GPPR_UARTB_MODESEL_PIN&t;6&t;/* GIO pin controlling uart b mode select */
DECL|macro|GPPR_UARTA_MODESEL_PIN
mdefine_line|#define GPPR_UARTA_MODESEL_PIN&t;7&t;/* GIO pin controlling uart a mode select */
DECL|macro|EMCR_DUPLEX
mdefine_line|#define EMCR_DUPLEX&t;&t;0x00000001
DECL|macro|EMCR_PROMISC
mdefine_line|#define EMCR_PROMISC&t;&t;0x00000002
DECL|macro|EMCR_PADEN
mdefine_line|#define EMCR_PADEN&t;&t;0x00000004
DECL|macro|EMCR_RXOFF_MASK
mdefine_line|#define EMCR_RXOFF_MASK&t;&t;0x000001f8
DECL|macro|EMCR_RXOFF_SHIFT
mdefine_line|#define EMCR_RXOFF_SHIFT&t;3
DECL|macro|EMCR_RAMPAR
mdefine_line|#define EMCR_RAMPAR&t;&t;0x00000200
DECL|macro|EMCR_BADPAR
mdefine_line|#define EMCR_BADPAR&t;&t;0x00000800
DECL|macro|EMCR_BUFSIZ
mdefine_line|#define EMCR_BUFSIZ&t;&t;0x00001000
DECL|macro|EMCR_TXDMAEN
mdefine_line|#define EMCR_TXDMAEN&t;&t;0x00002000
DECL|macro|EMCR_TXEN
mdefine_line|#define EMCR_TXEN&t;&t;0x00004000
DECL|macro|EMCR_RXDMAEN
mdefine_line|#define EMCR_RXDMAEN&t;&t;0x00008000
DECL|macro|EMCR_RXEN
mdefine_line|#define EMCR_RXEN&t;&t;0x00010000
DECL|macro|EMCR_LOOPBACK
mdefine_line|#define EMCR_LOOPBACK&t;&t;0x00020000
DECL|macro|EMCR_ARB_DIAG
mdefine_line|#define EMCR_ARB_DIAG&t;&t;0x001c0000
DECL|macro|EMCR_ARB_DIAG_IDLE
mdefine_line|#define EMCR_ARB_DIAG_IDLE&t;0x00200000
DECL|macro|EMCR_RST
mdefine_line|#define EMCR_RST&t;&t;0x80000000
DECL|macro|EISR_RXTIMERINT
mdefine_line|#define EISR_RXTIMERINT&t;&t;0x00000001
DECL|macro|EISR_RXTHRESHINT
mdefine_line|#define EISR_RXTHRESHINT&t;0x00000002
DECL|macro|EISR_RXOFLO
mdefine_line|#define EISR_RXOFLO&t;&t;0x00000004
DECL|macro|EISR_RXBUFOFLO
mdefine_line|#define EISR_RXBUFOFLO&t;&t;0x00000008
DECL|macro|EISR_RXMEMERR
mdefine_line|#define EISR_RXMEMERR&t;&t;0x00000010
DECL|macro|EISR_RXPARERR
mdefine_line|#define EISR_RXPARERR&t;&t;0x00000020
DECL|macro|EISR_TXEMPTY
mdefine_line|#define EISR_TXEMPTY&t;&t;0x00010000
DECL|macro|EISR_TXRTRY
mdefine_line|#define EISR_TXRTRY&t;&t;0x00020000
DECL|macro|EISR_TXEXDEF
mdefine_line|#define EISR_TXEXDEF&t;&t;0x00040000
DECL|macro|EISR_TXLCOL
mdefine_line|#define EISR_TXLCOL&t;&t;0x00080000
DECL|macro|EISR_TXGIANT
mdefine_line|#define EISR_TXGIANT&t;&t;0x00100000
DECL|macro|EISR_TXBUFUFLO
mdefine_line|#define EISR_TXBUFUFLO&t;&t;0x00200000
DECL|macro|EISR_TXEXPLICIT
mdefine_line|#define EISR_TXEXPLICIT&t;&t;0x00400000
DECL|macro|EISR_TXCOLLWRAP
mdefine_line|#define EISR_TXCOLLWRAP&t;&t;0x00800000
DECL|macro|EISR_TXDEFERWRAP
mdefine_line|#define EISR_TXDEFERWRAP&t;0x01000000
DECL|macro|EISR_TXMEMERR
mdefine_line|#define EISR_TXMEMERR&t;&t;0x02000000
DECL|macro|EISR_TXPARERR
mdefine_line|#define EISR_TXPARERR&t;&t;0x04000000
DECL|macro|ERCSR_THRESH_MASK
mdefine_line|#define ERCSR_THRESH_MASK&t;0x000001ff&t;/* enet RX threshold */
DECL|macro|ERCSR_RX_TMR
mdefine_line|#define ERCSR_RX_TMR&t;&t;0x40000000&t;/* simulation only */
DECL|macro|ERCSR_DIAG_OFLO
mdefine_line|#define ERCSR_DIAG_OFLO&t;&t;0x80000000&t;/* simulation only */
DECL|macro|ERBR_ALIGNMENT
mdefine_line|#define ERBR_ALIGNMENT&t;&t;4096
DECL|macro|ERBR_L_RXRINGBASE_MASK
mdefine_line|#define ERBR_L_RXRINGBASE_MASK&t;0xfffff000
DECL|macro|ERBAR_BARRIER_BIT
mdefine_line|#define ERBAR_BARRIER_BIT&t;0x0100
DECL|macro|ERBAR_RXBARR_MASK
mdefine_line|#define ERBAR_RXBARR_MASK&t;0xffff0000
DECL|macro|ERBAR_RXBARR_SHIFT
mdefine_line|#define ERBAR_RXBARR_SHIFT&t;16
DECL|macro|ERCIR_RXCONSUME_MASK
mdefine_line|#define ERCIR_RXCONSUME_MASK&t;0x00000fff
DECL|macro|ERPIR_RXPRODUCE_MASK
mdefine_line|#define ERPIR_RXPRODUCE_MASK&t;0x00000fff
DECL|macro|ERPIR_ARM
mdefine_line|#define ERPIR_ARM&t;&t;0x80000000
DECL|macro|ERTR_CNT_MASK
mdefine_line|#define ERTR_CNT_MASK&t;&t;0x000007ff
DECL|macro|ETCSR_IPGT_MASK
mdefine_line|#define ETCSR_IPGT_MASK&t;&t;0x0000007f
DECL|macro|ETCSR_IPGR1_MASK
mdefine_line|#define ETCSR_IPGR1_MASK&t;0x00007f00
DECL|macro|ETCSR_IPGR1_SHIFT
mdefine_line|#define ETCSR_IPGR1_SHIFT&t;8
DECL|macro|ETCSR_IPGR2_MASK
mdefine_line|#define ETCSR_IPGR2_MASK&t;0x007f0000
DECL|macro|ETCSR_IPGR2_SHIFT
mdefine_line|#define ETCSR_IPGR2_SHIFT&t;16
DECL|macro|ETCSR_NOTXCLK
mdefine_line|#define ETCSR_NOTXCLK&t;&t;0x80000000
DECL|macro|ETCDC_COLLCNT_MASK
mdefine_line|#define ETCDC_COLLCNT_MASK&t;0x0000ffff
DECL|macro|ETCDC_DEFERCNT_MASK
mdefine_line|#define ETCDC_DEFERCNT_MASK&t;0xffff0000
DECL|macro|ETCDC_DEFERCNT_SHIFT
mdefine_line|#define ETCDC_DEFERCNT_SHIFT&t;16
DECL|macro|ETBR_ALIGNMENT
mdefine_line|#define ETBR_ALIGNMENT&t;&t;(64*1024)
DECL|macro|ETBR_L_RINGSZ_MASK
mdefine_line|#define ETBR_L_RINGSZ_MASK&t;0x00000001
DECL|macro|ETBR_L_RINGSZ128
mdefine_line|#define ETBR_L_RINGSZ128&t;0
DECL|macro|ETBR_L_RINGSZ512
mdefine_line|#define ETBR_L_RINGSZ512&t;1
DECL|macro|ETBR_L_TXRINGBASE_MASK
mdefine_line|#define ETBR_L_TXRINGBASE_MASK&t;0xffffc000
DECL|macro|ETCIR_TXCONSUME_MASK
mdefine_line|#define ETCIR_TXCONSUME_MASK&t;0x0000ffff
DECL|macro|ETCIR_IDLE
mdefine_line|#define ETCIR_IDLE&t;&t;0x80000000
DECL|macro|ETPIR_TXPRODUCE_MASK
mdefine_line|#define ETPIR_TXPRODUCE_MASK&t;0x0000ffff
DECL|macro|EBIR_TXBUFPROD_MASK
mdefine_line|#define EBIR_TXBUFPROD_MASK&t;0x0000001f
DECL|macro|EBIR_TXBUFCONS_MASK
mdefine_line|#define EBIR_TXBUFCONS_MASK&t;0x00001f00
DECL|macro|EBIR_TXBUFCONS_SHIFT
mdefine_line|#define EBIR_TXBUFCONS_SHIFT&t;8
DECL|macro|EBIR_RXBUFPROD_MASK
mdefine_line|#define EBIR_RXBUFPROD_MASK&t;0x007fc000
DECL|macro|EBIR_RXBUFPROD_SHIFT
mdefine_line|#define EBIR_RXBUFPROD_SHIFT&t;14
DECL|macro|EBIR_RXBUFCONS_MASK
mdefine_line|#define EBIR_RXBUFCONS_MASK&t;0xff800000
DECL|macro|EBIR_RXBUFCONS_SHIFT
mdefine_line|#define EBIR_RXBUFCONS_SHIFT&t;23
DECL|macro|MICR_REGADDR_MASK
mdefine_line|#define MICR_REGADDR_MASK&t;0x0000001f
DECL|macro|MICR_PHYADDR_MASK
mdefine_line|#define MICR_PHYADDR_MASK&t;0x000003e0
DECL|macro|MICR_PHYADDR_SHIFT
mdefine_line|#define MICR_PHYADDR_SHIFT&t;5
DECL|macro|MICR_READTRIG
mdefine_line|#define MICR_READTRIG&t;&t;0x00000400
DECL|macro|MICR_BUSY
mdefine_line|#define MICR_BUSY&t;&t;0x00000800
DECL|macro|MIDR_DATA_MASK
mdefine_line|#define MIDR_DATA_MASK&t;&t;0x0000ffff
DECL|macro|ERXBUF_IPCKSUM_MASK
mdefine_line|#define ERXBUF_IPCKSUM_MASK&t;0x0000ffff
DECL|macro|ERXBUF_BYTECNT_MASK
mdefine_line|#define ERXBUF_BYTECNT_MASK&t;0x07ff0000
DECL|macro|ERXBUF_BYTECNT_SHIFT
mdefine_line|#define ERXBUF_BYTECNT_SHIFT&t;16
DECL|macro|ERXBUF_V
mdefine_line|#define ERXBUF_V&t;&t;0x80000000
DECL|macro|ERXBUF_CRCERR
mdefine_line|#define ERXBUF_CRCERR&t;&t;0x00000001&t;/* aka RSV15 */
DECL|macro|ERXBUF_FRAMERR
mdefine_line|#define ERXBUF_FRAMERR&t;&t;0x00000002&t;/* aka RSV14 */
DECL|macro|ERXBUF_CODERR
mdefine_line|#define ERXBUF_CODERR&t;&t;0x00000004&t;/* aka RSV13 */
DECL|macro|ERXBUF_INVPREAMB
mdefine_line|#define ERXBUF_INVPREAMB&t;0x00000008&t;/* aka RSV18 */
DECL|macro|ERXBUF_LOLEN
mdefine_line|#define ERXBUF_LOLEN&t;&t;0x00007000&t;/* aka RSV2_0 */
DECL|macro|ERXBUF_HILEN
mdefine_line|#define ERXBUF_HILEN&t;&t;0x03ff0000&t;/* aka RSV12_3 */
DECL|macro|ERXBUF_MULTICAST
mdefine_line|#define ERXBUF_MULTICAST&t;0x04000000&t;/* aka RSV16 */
DECL|macro|ERXBUF_BROADCAST
mdefine_line|#define ERXBUF_BROADCAST&t;0x08000000&t;/* aka RSV17 */
DECL|macro|ERXBUF_LONGEVENT
mdefine_line|#define ERXBUF_LONGEVENT&t;0x10000000&t;/* aka RSV19 */
DECL|macro|ERXBUF_BADPKT
mdefine_line|#define ERXBUF_BADPKT&t;&t;0x20000000&t;/* aka RSV20 */
DECL|macro|ERXBUF_GOODPKT
mdefine_line|#define ERXBUF_GOODPKT&t;&t;0x40000000&t;/* aka RSV21 */
DECL|macro|ERXBUF_CARRIER
mdefine_line|#define ERXBUF_CARRIER&t;&t;0x80000000&t;/* aka RSV22 */
DECL|macro|ETXD_BYTECNT_MASK
mdefine_line|#define ETXD_BYTECNT_MASK&t;0x000007ff&t;/* total byte count */
DECL|macro|ETXD_INTWHENDONE
mdefine_line|#define ETXD_INTWHENDONE&t;0x00001000&t;/* intr when done */
DECL|macro|ETXD_D0V
mdefine_line|#define ETXD_D0V&t;&t;0x00010000&t;/* data 0 valid */
DECL|macro|ETXD_B1V
mdefine_line|#define ETXD_B1V&t;&t;0x00020000&t;/* buf 1 valid */
DECL|macro|ETXD_B2V
mdefine_line|#define ETXD_B2V&t;&t;0x00040000&t;/* buf 2 valid */
DECL|macro|ETXD_DOCHECKSUM
mdefine_line|#define ETXD_DOCHECKSUM&t;&t;0x00080000&t;/* insert ip cksum */
DECL|macro|ETXD_CHKOFF_MASK
mdefine_line|#define ETXD_CHKOFF_MASK&t;0x07f00000&t;/* cksum byte offset */
DECL|macro|ETXD_CHKOFF_SHIFT
mdefine_line|#define ETXD_CHKOFF_SHIFT&t;20
DECL|macro|ETXD_D0CNT_MASK
mdefine_line|#define ETXD_D0CNT_MASK&t;&t;0x0000007f
DECL|macro|ETXD_B1CNT_MASK
mdefine_line|#define ETXD_B1CNT_MASK&t;&t;0x0007ff00
DECL|macro|ETXD_B1CNT_SHIFT
mdefine_line|#define ETXD_B1CNT_SHIFT&t;8
DECL|macro|ETXD_B2CNT_MASK
mdefine_line|#define ETXD_B2CNT_MASK&t;&t;0x7ff00000
DECL|macro|ETXD_B2CNT_SHIFT
mdefine_line|#define ETXD_B2CNT_SHIFT&t;20
DECL|enum|ioc3_subdevs_e
r_typedef
r_enum
id|ioc3_subdevs_e
(brace
DECL|enumerator|ioc3_subdev_ether
id|ioc3_subdev_ether
comma
DECL|enumerator|ioc3_subdev_generic
id|ioc3_subdev_generic
comma
DECL|enumerator|ioc3_subdev_nic
id|ioc3_subdev_nic
comma
DECL|enumerator|ioc3_subdev_kbms
id|ioc3_subdev_kbms
comma
DECL|enumerator|ioc3_subdev_ttya
id|ioc3_subdev_ttya
comma
DECL|enumerator|ioc3_subdev_ttyb
id|ioc3_subdev_ttyb
comma
DECL|enumerator|ioc3_subdev_ecpp
id|ioc3_subdev_ecpp
comma
DECL|enumerator|ioc3_subdev_rt
id|ioc3_subdev_rt
comma
DECL|enumerator|ioc3_nsubdevs
id|ioc3_nsubdevs
DECL|typedef|ioc3_subdev_t
)brace
id|ioc3_subdev_t
suffix:semicolon
multiline_comment|/* subdevice disable bits,&n; * from the standard INFO_LBL_SUBDEVS&n; */
DECL|macro|IOC3_SDB_ETHER
mdefine_line|#define IOC3_SDB_ETHER&t;&t;(1&lt;&lt;ioc3_subdev_ether)
DECL|macro|IOC3_SDB_GENERIC
mdefine_line|#define IOC3_SDB_GENERIC&t;(1&lt;&lt;ioc3_subdev_generic)
DECL|macro|IOC3_SDB_NIC
mdefine_line|#define IOC3_SDB_NIC&t;&t;(1&lt;&lt;ioc3_subdev_nic)
DECL|macro|IOC3_SDB_KBMS
mdefine_line|#define IOC3_SDB_KBMS&t;&t;(1&lt;&lt;ioc3_subdev_kbms)
DECL|macro|IOC3_SDB_TTYA
mdefine_line|#define IOC3_SDB_TTYA&t;&t;(1&lt;&lt;ioc3_subdev_ttya)
DECL|macro|IOC3_SDB_TTYB
mdefine_line|#define IOC3_SDB_TTYB&t;&t;(1&lt;&lt;ioc3_subdev_ttyb)
DECL|macro|IOC3_SDB_ECPP
mdefine_line|#define IOC3_SDB_ECPP&t;&t;(1&lt;&lt;ioc3_subdev_ecpp)
DECL|macro|IOC3_SDB_RT
mdefine_line|#define IOC3_SDB_RT&t;&t;(1&lt;&lt;ioc3_subdev_rt)
DECL|macro|IOC3_ALL_SUBDEVS
mdefine_line|#define IOC3_ALL_SUBDEVS&t;((1&lt;&lt;ioc3_nsubdevs)-1)
DECL|macro|IOC3_SDB_SERIAL
mdefine_line|#define IOC3_SDB_SERIAL&t;&t;(IOC3_SDB_TTYA|IOC3_SDB_TTYB)
DECL|macro|IOC3_STD_SUBDEVS
mdefine_line|#define IOC3_STD_SUBDEVS&t;IOC3_ALL_SUBDEVS
DECL|macro|IOC3_INTA_SUBDEVS
mdefine_line|#define IOC3_INTA_SUBDEVS&t;IOC3_SDB_ETHER
DECL|macro|IOC3_INTB_SUBDEVS
mdefine_line|#define IOC3_INTB_SUBDEVS&t;(IOC3_SDB_GENERIC|IOC3_SDB_KBMS|IOC3_SDB_SERIAL|IOC3_SDB_ECPP|IOC3_SDB_RT)
multiline_comment|/*&n; * PCI Configuration Space Register Address Map, use offset from IOC3 PCI&n; * configuration base such that this can be used for multiple IOC3s&n; */
DECL|macro|IOC3_PCI_ID
mdefine_line|#define IOC3_PCI_ID&t;&t;0x0&t;/* ID */
DECL|macro|IOC3_VENDOR_ID_NUM
mdefine_line|#define IOC3_VENDOR_ID_NUM&t;0x10A9
DECL|macro|IOC3_DEVICE_ID_NUM
mdefine_line|#define IOC3_DEVICE_ID_NUM&t;0x0003
macro_line|#endif /* _ASM_IA64_SN_IOC3_H */
eof
