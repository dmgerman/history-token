multiline_comment|/*&n;** -----------------------------------------------------------------------------&n;**&n;**  Perle Specialix driver for Linux&n;**  Ported from existing RIO Driver for SCO sources.&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**&t;Module&t;&t;: eisa.h&n;**&t;SID&t;&t;: 1.2&n;**&t;Last Modified&t;: 11/6/98 11:34:10&n;**&t;Retrieved&t;: 11/6/98 11:34:21&n;**&n;**  ident @(#)eisa.h&t;1.2&n;**&n;** -----------------------------------------------------------------------------&n;*/
macro_line|#ifndef __rio_eisa_h__
DECL|macro|__rio_eisa_h__
mdefine_line|#define __rio_eisa_h__
macro_line|#ifdef SCCS_LABELS
macro_line|#ifndef lint
DECL|variable|_eisa_h_sccs_
r_static
r_char
op_star
id|_eisa_h_sccs_
op_assign
l_string|&quot;@(#)eisa.h&t;1.2&quot;
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n;** things to do with the EISA bus&n;*/
DECL|macro|RIO_EISA_STRING_ADDRESS
mdefine_line|#define RIO_EISA_STRING_ADDRESS &t;0xfffd9&t;/* where EISA is stored */
DECL|macro|RIO_MAX_EISA_SLOTS
mdefine_line|#define&t;RIO_MAX_EISA_SLOTS&t;&t;16&t;/* how many EISA slots? */
DECL|macro|RIO_EISA_IDENT
mdefine_line|#define&t;RIO_EISA_IDENT&t;&t;&t;0x984D&t;/* Specialix */
DECL|macro|RIO_EISA_PRODUCT_CODE
mdefine_line|#define&t;RIO_EISA_PRODUCT_CODE&t;&t;0x14&t;/* Code 14 */
DECL|macro|RIO_EISA_ENABLE_BIT
mdefine_line|#define&t;RIO_EISA_ENABLE_BIT&t;&t;0x01&t;/* To enable card */
DECL|macro|EISA_MEMORY_BASE_LO
mdefine_line|#define&t;EISA_MEMORY_BASE_LO&t;&t;0xC00&t;/* A16-A23 */
DECL|macro|EISA_MEMORY_BASE_HI
mdefine_line|#define&t;EISA_MEMORY_BASE_HI&t;&t;0xC01&t;/* A24-A31 */
DECL|macro|EISA_INTERRUPT_VEC
mdefine_line|#define&t;EISA_INTERRUPT_VEC&t;&t;0xC02&t;/* see below */
DECL|macro|EISA_CONTROL_PORT
mdefine_line|#define&t;EISA_CONTROL_PORT&t;&t;0xC02&t;/* see below */
DECL|macro|EISA_INTERRUPT_RESET
mdefine_line|#define&t;EISA_INTERRUPT_RESET&t;&t;0xC03&t;/* read to clear IRQ */
DECL|macro|EISA_PRODUCT_IDENT_LO
mdefine_line|#define&t;EISA_PRODUCT_IDENT_LO&t;&t;0xC80&t;/* where RIO_EISA_IDENT is */
DECL|macro|EISA_PRODUCT_IDENT_HI
mdefine_line|#define&t;EISA_PRODUCT_IDENT_HI&t;&t;0xC81
DECL|macro|EISA_PRODUCT_NUMBER
mdefine_line|#define&t;EISA_PRODUCT_NUMBER&t;&t;0xC82   /* where PROD_CODE is */
DECL|macro|EISA_REVISION_NUMBER
mdefine_line|#define&t;EISA_REVISION_NUMBER&t;&t;0xC83&t;/* revision (1dp) */
DECL|macro|EISA_ENABLE
mdefine_line|#define&t;EISA_ENABLE&t;&t;&t;0xC84&t;/* set LSB to enable card */
DECL|macro|EISA_UNIQUE_NUM_0
mdefine_line|#define&t;EISA_UNIQUE_NUM_0&t;&t;0xC88&t;/* vomit */
DECL|macro|EISA_UNIQUE_NUM_1
mdefine_line|#define&t;EISA_UNIQUE_NUM_1&t;&t;0xC8A
DECL|macro|EISA_UNIQUE_NUM_2
mdefine_line|#define&t;EISA_UNIQUE_NUM_2&t;&t;0xC90&t;/* bit strangely arranged */
DECL|macro|EISA_UNIQUE_NUM_3
mdefine_line|#define&t;EISA_UNIQUE_NUM_3&t;&t;0xC92
DECL|macro|EISA_MANUF_YEAR
mdefine_line|#define&t;EISA_MANUF_YEAR&t;&t;&t;0xC98&t;/* when */
DECL|macro|EISA_MANUF_WEEK
mdefine_line|#define&t;EISA_MANUF_WEEK&t;&t;&t;0xC9A&t;/* more when */
DECL|macro|EISA_TP_BOOT_FROM_RAM
mdefine_line|#define&t;EISA_TP_BOOT_FROM_RAM&t;0x01
DECL|macro|EISA_TP_BOOT_FROM_LINK
mdefine_line|#define&t;EISA_TP_BOOT_FROM_LINK&t;0x00
DECL|macro|EISA_TP_FAST_LINKS
mdefine_line|#define&t;EISA_TP_FAST_LINKS&t;0x02
DECL|macro|EISA_TP_SLOW_LINKS
mdefine_line|#define&t;EISA_TP_SLOW_LINKS&t;0x00
DECL|macro|EISA_TP_BUS_ENABLE
mdefine_line|#define&t;EISA_TP_BUS_ENABLE&t;0x04
DECL|macro|EISA_TP_BUS_DISABLE
mdefine_line|#define&t;EISA_TP_BUS_DISABLE&t;0x00
DECL|macro|EISA_TP_RUN
mdefine_line|#define&t;EISA_TP_RUN&t;&t;0x08
DECL|macro|EISA_TP_RESET
mdefine_line|#define&t;EISA_TP_RESET&t;&t;0x00
DECL|macro|EISA_POLLED
mdefine_line|#define&t;EISA_POLLED&t;&t;0x00
DECL|macro|EISA_IRQ_3
mdefine_line|#define&t;EISA_IRQ_3&t;&t;0x30
DECL|macro|EISA_IRQ_4
mdefine_line|#define&t;EISA_IRQ_4&t;&t;0x40
DECL|macro|EISA_IRQ_5
mdefine_line|#define&t;EISA_IRQ_5&t;&t;0x50
DECL|macro|EISA_IRQ_6
mdefine_line|#define&t;EISA_IRQ_6&t;&t;0x60
DECL|macro|EISA_IRQ_7
mdefine_line|#define&t;EISA_IRQ_7&t;&t;0x70
DECL|macro|EISA_IRQ_9
mdefine_line|#define&t;EISA_IRQ_9&t;&t;0x90
DECL|macro|EISA_IRQ_10
mdefine_line|#define&t;EISA_IRQ_10&t;&t;0xA0
DECL|macro|EISA_IRQ_11
mdefine_line|#define&t;EISA_IRQ_11&t;&t;0xB0
DECL|macro|EISA_IRQ_12
mdefine_line|#define&t;EISA_IRQ_12&t;&t;0xC0
DECL|macro|EISA_IRQ_14
mdefine_line|#define&t;EISA_IRQ_14&t;&t;0xE0
DECL|macro|EISA_IRQ_15
mdefine_line|#define&t;EISA_IRQ_15&t;&t;0xF0
DECL|macro|EISA_INTERRUPT_MASK
mdefine_line|#define&t;EISA_INTERRUPT_MASK&t;0xF0
DECL|macro|EISA_CONTROL_MASK
mdefine_line|#define&t;EISA_CONTROL_MASK&t;0x0F
DECL|macro|RIO_EISA_DEFAULT_MODE
mdefine_line|#define&t;RIO_EISA_DEFAULT_MODE&t;EISA_TP_SLOW_LINKS
DECL|macro|RIOEisaToIvec
mdefine_line|#define&t;RIOEisaToIvec(X)&t;(uchar )((uchar)((X) &amp; EISA_INTERRUPT_MASK)&gt;&gt;4)
DECL|macro|INBZ
mdefine_line|#define&t;INBZ(z,x)&t;inb(((z)&lt;&lt;12) | (x))
DECL|macro|OUTBZ
mdefine_line|#define&t;OUTBZ(z,x,y)&t;outb((((z)&lt;&lt;12) | (x)), y)
macro_line|#endif /* __rio_eisa_h__ */
eof
