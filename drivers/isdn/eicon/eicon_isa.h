multiline_comment|/* $Id: eicon_isa.h,v 1.10 2000/05/07 08:51:04 armin Exp $&n; *&n; * ISDN low-level module for Eicon active ISDN-Cards.&n; *&n; * Copyright 1998      by Fritz Elfert (fritz@isdn4linux.de)&n; * Copyright 1998-2000 by Armin Schindler (mac@melware.de)&n; * Copyright 1999,2000 Cytronics &amp; Melware (info@melware.de)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n; *&n; */
macro_line|#ifndef eicon_isa_h
DECL|macro|eicon_isa_h
mdefine_line|#define eicon_isa_h
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Factory defaults for ISA-Cards */
DECL|macro|EICON_ISA_MEMBASE
mdefine_line|#define EICON_ISA_MEMBASE 0xd0000
DECL|macro|EICON_ISA_IRQ
mdefine_line|#define EICON_ISA_IRQ     3
multiline_comment|/* shmem offset for Quadro parts */
DECL|macro|EICON_ISA_QOFFSET
mdefine_line|#define EICON_ISA_QOFFSET 0x0800
r_typedef
r_struct
(brace
DECL|member|length
id|__u16
id|length
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* length of data/parameter field         */
DECL|member|P
id|__u8
id|P
(braket
l_int|270
)braket
suffix:semicolon
multiline_comment|/* data/parameter field                   */
DECL|typedef|eicon_scom_PBUFFER
)brace
id|eicon_scom_PBUFFER
suffix:semicolon
multiline_comment|/* General communication buffer */
r_typedef
r_struct
(brace
DECL|member|Req
id|__u8
id|Req
suffix:semicolon
multiline_comment|/* request register                       */
DECL|member|ReqId
id|__u8
id|ReqId
suffix:semicolon
multiline_comment|/* request task/entity identification     */
DECL|member|Rc
id|__u8
id|Rc
suffix:semicolon
multiline_comment|/* return code register                   */
DECL|member|RcId
id|__u8
id|RcId
suffix:semicolon
multiline_comment|/* return code task/entity identification */
DECL|member|Ind
id|__u8
id|Ind
suffix:semicolon
multiline_comment|/* Indication register                    */
DECL|member|IndId
id|__u8
id|IndId
suffix:semicolon
multiline_comment|/* Indication task/entity identification  */
DECL|member|IMask
id|__u8
id|IMask
suffix:semicolon
multiline_comment|/* Interrupt Mask Flag                    */
DECL|member|RNR
id|__u8
id|RNR
suffix:semicolon
multiline_comment|/* Receiver Not Ready (set by PC)         */
DECL|member|XLock
id|__u8
id|XLock
suffix:semicolon
multiline_comment|/* XBuffer locked Flag                    */
DECL|member|Int
id|__u8
id|Int
suffix:semicolon
multiline_comment|/* ISDN interrupt                         */
DECL|member|ReqCh
id|__u8
id|ReqCh
suffix:semicolon
multiline_comment|/* Channel field for layer-3 Requests     */
DECL|member|RcCh
id|__u8
id|RcCh
suffix:semicolon
multiline_comment|/* Channel field for layer-3 Returncodes  */
DECL|member|IndCh
id|__u8
id|IndCh
suffix:semicolon
multiline_comment|/* Channel field for layer-3 Indications  */
DECL|member|MInd
id|__u8
id|MInd
suffix:semicolon
multiline_comment|/* more data indication field             */
DECL|member|MLength
id|__u16
id|MLength
suffix:semicolon
multiline_comment|/* more data total packet length          */
DECL|member|ReadyInt
id|__u8
id|ReadyInt
suffix:semicolon
multiline_comment|/* request field for ready interrupt      */
DECL|member|Reserved
id|__u8
id|Reserved
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* reserved space                         */
DECL|member|IfType
id|__u8
id|IfType
suffix:semicolon
multiline_comment|/* 1 = 16k-Interface                      */
DECL|member|Signature
id|__u16
id|Signature
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* ISDN adapter Signature                 */
DECL|member|XBuffer
id|eicon_scom_PBUFFER
id|XBuffer
suffix:semicolon
multiline_comment|/* Transmit Buffer                        */
DECL|member|RBuffer
id|eicon_scom_PBUFFER
id|RBuffer
suffix:semicolon
multiline_comment|/* Receive Buffer                         */
DECL|typedef|eicon_isa_com
)brace
id|eicon_isa_com
suffix:semicolon
multiline_comment|/* struct for downloading firmware */
r_typedef
r_struct
(brace
DECL|member|ctrl
id|__u8
id|ctrl
suffix:semicolon
DECL|member|card
id|__u8
id|card
suffix:semicolon
DECL|member|msize
id|__u8
id|msize
suffix:semicolon
DECL|member|fill0
id|__u8
id|fill0
suffix:semicolon
DECL|member|ebit
id|__u16
id|ebit
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|eloc
id|__u32
id|eloc
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|reserved
id|__u8
id|reserved
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|signature
id|__u16
id|signature
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|fill
id|__u8
id|fill
(braket
l_int|224
)braket
suffix:semicolon
DECL|member|b
id|__u8
id|b
(braket
l_int|256
)braket
suffix:semicolon
DECL|typedef|eicon_isa_boot
)brace
id|eicon_isa_boot
suffix:semicolon
multiline_comment|/* Shared memory */
r_typedef
r_union
(brace
DECL|member|c
r_int
r_char
id|c
(braket
l_int|0x400
)braket
suffix:semicolon
DECL|member|com
id|eicon_isa_com
id|com
suffix:semicolon
DECL|member|boot
id|eicon_isa_boot
id|boot
suffix:semicolon
DECL|typedef|eicon_isa_shmem
)brace
id|eicon_isa_shmem
suffix:semicolon
multiline_comment|/*&n; * card&squot;s description&n; */
r_typedef
r_struct
(brace
DECL|member|ramsize
r_int
id|ramsize
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* IRQ                        */
DECL|member|physmem
r_int
r_int
id|physmem
suffix:semicolon
multiline_comment|/* physical memory address&t;  */
macro_line|#ifdef CONFIG_MCA
DECL|member|io
r_int
id|io
suffix:semicolon
multiline_comment|/* IO-port for MCA brand      */
macro_line|#endif /* CONFIG_MCA */
DECL|member|card
r_void
op_star
id|card
suffix:semicolon
DECL|member|shmem
id|eicon_isa_shmem
op_star
id|shmem
suffix:semicolon
multiline_comment|/* Shared-memory area         */
DECL|member|intack
r_int
r_char
op_star
id|intack
suffix:semicolon
multiline_comment|/* Int-Acknowledge            */
DECL|member|stopcpu
r_int
r_char
op_star
id|stopcpu
suffix:semicolon
multiline_comment|/* Writing here stops CPU     */
DECL|member|startcpu
r_int
r_char
op_star
id|startcpu
suffix:semicolon
multiline_comment|/* Writing here starts CPU    */
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
multiline_comment|/* card type                  */
DECL|member|channels
r_int
id|channels
suffix:semicolon
multiline_comment|/* No. of channels&t;&t;  */
DECL|member|irqprobe
r_int
r_char
id|irqprobe
suffix:semicolon
multiline_comment|/* Flag: IRQ-probing          */
DECL|member|mvalid
r_int
r_char
id|mvalid
suffix:semicolon
multiline_comment|/* Flag: Memory is valid      */
DECL|member|ivalid
r_int
r_char
id|ivalid
suffix:semicolon
multiline_comment|/* Flag: IRQ is valid         */
DECL|member|master
r_int
r_char
id|master
suffix:semicolon
multiline_comment|/* Flag: Card ist Quadro 1/4  */
DECL|typedef|eicon_isa_card
)brace
id|eicon_isa_card
suffix:semicolon
multiline_comment|/* Offsets for special locations on standard cards */
DECL|macro|INTACK
mdefine_line|#define INTACK     0x03fe 
DECL|macro|STOPCPU
mdefine_line|#define STOPCPU    0x0400
DECL|macro|STARTCPU
mdefine_line|#define STARTCPU   0x0401
DECL|macro|RAMSIZE
mdefine_line|#define RAMSIZE    0x0400
multiline_comment|/* Offsets for special location on PRI card */
DECL|macro|INTACK_P
mdefine_line|#define INTACK_P   0x3ffc
DECL|macro|STOPCPU_P
mdefine_line|#define STOPCPU_P  0x3ffe
DECL|macro|STARTCPU_P
mdefine_line|#define STARTCPU_P 0x3fff
DECL|macro|RAMSIZE_P
mdefine_line|#define RAMSIZE_P  0x4000
r_extern
r_int
id|eicon_isa_load
c_func
(paren
id|eicon_isa_card
op_star
id|card
comma
id|eicon_isa_codebuf
op_star
id|cb
)paren
suffix:semicolon
r_extern
r_int
id|eicon_isa_bootload
c_func
(paren
id|eicon_isa_card
op_star
id|card
comma
id|eicon_isa_codebuf
op_star
id|cb
)paren
suffix:semicolon
r_extern
r_void
id|eicon_isa_release
c_func
(paren
id|eicon_isa_card
op_star
id|card
)paren
suffix:semicolon
r_extern
r_void
id|eicon_isa_printpar
c_func
(paren
id|eicon_isa_card
op_star
id|card
)paren
suffix:semicolon
r_extern
r_void
id|eicon_isa_transmit
c_func
(paren
id|eicon_isa_card
op_star
id|card
)paren
suffix:semicolon
r_extern
r_int
id|eicon_isa_find_card
c_func
(paren
r_int
id|Mem
comma
r_int
id|Irq
comma
r_char
op_star
id|Id
)paren
suffix:semicolon
macro_line|#endif  /* __KERNEL__ */
macro_line|#endif&t;/* eicon_isa_h */
eof
