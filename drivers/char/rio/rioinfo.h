multiline_comment|/*&n;** -----------------------------------------------------------------------------&n;**&n;**  Perle Specialix driver for Linux&n;**  Ported from existing RIO Driver for SCO sources.&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**&t;Module&t;&t;: rioinfo.h&n;**&t;SID&t;&t;: 1.2&n;**&t;Last Modified&t;: 11/6/98 14:07:49&n;**&t;Retrieved&t;: 11/6/98 14:07:50&n;**&n;**  ident @(#)rioinfo.h&t;1.2&n;**&n;** -----------------------------------------------------------------------------&n;*/
macro_line|#ifndef __rioinfo_h
DECL|macro|__rioinfo_h
mdefine_line|#define __rioinfo_h
macro_line|#ifdef SCCS_LABELS
DECL|variable|_rioinfo_h_sccs_
r_static
r_char
op_star
id|_rioinfo_h_sccs_
op_assign
l_string|&quot;@(#)rioinfo.h&t;1.2&quot;
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;** Host card data structure&n;*/
DECL|struct|RioHostInfo
r_struct
id|RioHostInfo
(brace
DECL|member|location
r_int
id|location
suffix:semicolon
multiline_comment|/* RIO Card Base I/O address */
DECL|member|vector
r_int
id|vector
suffix:semicolon
multiline_comment|/* RIO Card IRQ vector */
DECL|member|bus
r_int
id|bus
suffix:semicolon
multiline_comment|/* ISA/EISA/MCA/PCI */
DECL|member|mode
r_int
id|mode
suffix:semicolon
multiline_comment|/* pointer to host mode - INTERUPT / POLLED */
r_struct
id|old_sgttyb
DECL|member|Sg
op_star
id|Sg
suffix:semicolon
multiline_comment|/* pointer to default term characteristics */
)brace
suffix:semicolon
multiline_comment|/* Mode in rio device info */
DECL|macro|INTERRUPTED_MODE
mdefine_line|#define INTERRUPTED_MODE&t;0x01&t;&t;/* Interrupt is generated */
DECL|macro|POLLED_MODE
mdefine_line|#define POLLED_MODE&t;&t;0x02&t;&t;/* No interrupt */
DECL|macro|AUTO_MODE
mdefine_line|#define AUTO_MODE&t;&t;0x03&t;&t;/* Auto mode */
DECL|macro|WORD_ACCESS_MODE
mdefine_line|#define WORD_ACCESS_MODE&t;0x10&t;&t;/* Word Access Mode */
DECL|macro|BYTE_ACCESS_MODE
mdefine_line|#define BYTE_ACCESS_MODE&t;0x20&t;&t;/* Byte Access Mode */
multiline_comment|/* Bus type that RIO supports */
DECL|macro|ISA_BUS
mdefine_line|#define ISA_BUS&t;&t;&t;0x01&t;&t;/* The card is ISA */
DECL|macro|EISA_BUS
mdefine_line|#define EISA_BUS&t;&t;0x02&t;&t;/* The card is EISA */
DECL|macro|MCA_BUS
mdefine_line|#define MCA_BUS&t;&t;&t;0x04&t;&t;/* The card is MCA */
DECL|macro|PCI_BUS
mdefine_line|#define PCI_BUS&t;&t;&t;0x08&t;&t;/* The card is PCI */
multiline_comment|/*&n;** 11.11.1998 ARG - ESIL ???? part fix&n;** Moved definition for &squot;CHAN&squot; here from rioinfo.c (it is now&n;** called &squot;DEF_TERM_CHARACTERISTICS&squot;).&n;*/
DECL|macro|DEF_TERM_CHARACTERISTICS
mdefine_line|#define DEF_TERM_CHARACTERISTICS &bslash;&n;{ &bslash;&n;&t;B19200, B19200,&t;&t;&t;&t;/* input and output speed */ &bslash;&n;&t;&squot;H&squot; - &squot;@&squot;,&t;&t;&t;&t;/* erase char */ &bslash;&n;&t;-1,&t;&t;&t;&t;&t;/* 2nd erase char */ &bslash;&n;&t;&squot;U&squot; - &squot;@&squot;,&t;&t;&t;&t;/* kill char */ &bslash;&n;&t;ECHO | CRMOD,&t;&t;&t;&t;/* mode */ &bslash;&n;&t;&squot;C&squot; - &squot;@&squot;,&t;&t;&t;&t;/* interrupt character */ &bslash;&n;&t;&squot;&bslash;&bslash;&squot; - &squot;@&squot;,&t;&t;&t;&t;/* quit char */ &bslash;&n;&t;&squot;Q&squot; - &squot;@&squot;,&t;&t;&t;&t;/* start char */ &bslash;&n;&t;&squot;S&squot; - &squot;@&squot;,&t;&t;&t;&t;/* stop char */ &bslash;&n;&t;&squot;D&squot; - &squot;@&squot;,&t;&t;&t;&t;/* EOF */ &bslash;&n;&t;-1,&t;&t;&t;&t;&t;/* brk */ &bslash;&n;&t;(LCRTBS | LCRTERA | LCRTKIL | LCTLECH),&t;/* local mode word */ &bslash;&n;&t;&squot;Z&squot; - &squot;@&squot;,&t;&t;&t;&t;/* process stop */ &bslash;&n;&t;&squot;Y&squot; - &squot;@&squot;,&t;&t;&t;&t;/* delayed stop */ &bslash;&n;&t;&squot;R&squot; - &squot;@&squot;,&t;&t;&t;&t;/* reprint line */ &bslash;&n;&t;&squot;O&squot; - &squot;@&squot;,&t;&t;&t;&t;/* flush output */ &bslash;&n;&t;&squot;W&squot; - &squot;@&squot;,&t;&t;&t;&t;/* word erase */ &bslash;&n;&t;&squot;V&squot; - &squot;@&squot;&t;&t;&t;&t;/* literal next char */ &bslash;&n;}
macro_line|#endif /* __rioinfo_h */
eof
