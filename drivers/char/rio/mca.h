multiline_comment|/*&n;** -----------------------------------------------------------------------------&n;**&n;**  Perle Specialix driver for Linux&n;**  Ported from existing RIO Driver for SCO sources.&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**&t;Module&t;&t;: mca.h&n;**&t;SID&t;&t;: 1.2&n;**&t;Last Modified&t;: 11/6/98 11:34:11&n;**&t;Retrieved&t;: 11/6/98 11:34:21&n;**&n;**  ident @(#)mca.h&t;1.2&n;**&n;** -----------------------------------------------------------------------------&n;*/
macro_line|#ifndef __rio_mca_h__
DECL|macro|__rio_mca_h__
mdefine_line|#define&t;__rio_mca_h__
macro_line|#ifdef SCCS_LABELS
DECL|variable|_mca_h_sccs_
r_static
r_char
op_star
id|_mca_h_sccs_
op_assign
l_string|&quot;@(#)mca.h&t;1.2&quot;
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;** Micro Channel stuff&n;*/
DECL|macro|McaMaxSlots
mdefine_line|#define&t;McaMaxSlots&t;8
DECL|macro|McaSlotSelect
mdefine_line|#define McaSlotSelect&t;0x96
DECL|macro|McaSlotEnable
mdefine_line|#define&t;McaSlotEnable&t;0x08
DECL|macro|McaIdLow
mdefine_line|#define&t;McaIdLow&t;0x100
DECL|macro|McaIdHigh
mdefine_line|#define&t;McaIdHigh&t;0x101
DECL|macro|McaIrqEnable
mdefine_line|#define&t;McaIrqEnable&t;0x102
DECL|macro|McaMemory
mdefine_line|#define&t;McaMemory&t;0x103
DECL|macro|McaRIOId
mdefine_line|#define McaRIOId&t;0x6a5c
DECL|macro|McaIrq9
mdefine_line|#define&t;McaIrq9&t;&t;0x00
DECL|macro|McaIrq3
mdefine_line|#define&t;McaIrq3&t;&t;0x02
DECL|macro|McaIrq4
mdefine_line|#define&t;McaIrq4&t;&t;0x04
DECL|macro|McaIrq7
mdefine_line|#define&t;McaIrq7&t;&t;0x06
DECL|macro|McaIrq10
mdefine_line|#define&t;McaIrq10&t;0x08
DECL|macro|McaIrq11
mdefine_line|#define&t;McaIrq11&t;0x0A
DECL|macro|McaIrq12
mdefine_line|#define&t;McaIrq12&t;0x0C
DECL|macro|McaIrq15
mdefine_line|#define&t;McaIrq15&t;0x0E
DECL|macro|McaIrqMask
mdefine_line|#define McaIrqMask&t;0x0E
DECL|macro|McaCardEnable
mdefine_line|#define&t;McaCardEnable&t;0x01
DECL|macro|McaAddress
mdefine_line|#define&t;McaAddress(X)&t;(((X)&amp;0xFF)&lt;&lt;16)
DECL|macro|McaTpFastLinks
mdefine_line|#define&t;McaTpFastLinks&t;        0x40
DECL|macro|McaTpSlowLinks
mdefine_line|#define&t;McaTpSlowLinks&t;        0x00
DECL|macro|McaTpBootFromRam
mdefine_line|#define&t;McaTpBootFromRam&t;0x01
DECL|macro|McaTpBootFromLink
mdefine_line|#define&t;McaTpBootFromLink&t;0x00
DECL|macro|McaTpBusEnable
mdefine_line|#define&t;McaTpBusEnable&t;&t;0x02
DECL|macro|McaTpBusDisable
mdefine_line|#define&t;McaTpBusDisable&t;&t;0x00
DECL|macro|RIO_MCA_DEFAULT_MODE
mdefine_line|#define&t;RIO_MCA_DEFAULT_MODE&t;SLOW_LINKS
macro_line|#endif&t;/* __rio_mca_h__ */
eof
