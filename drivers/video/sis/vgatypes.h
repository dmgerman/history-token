multiline_comment|/* $XFree86$ */
multiline_comment|/* $XdotOrg$ */
multiline_comment|/*&n; * General type definitions for universal mode switching modules&n; *&n; * Copyright (C) 2001-2004 by Thomas Winischhofer, Vienna, Austria&n; *&n; * If distributed as part of the Linux kernel, the following license terms&n; * apply:&n; *&n; * * This program is free software; you can redistribute it and/or modify&n; * * it under the terms of the GNU General Public License as published by&n; * * the Free Software Foundation; either version 2 of the named License,&n; * * or any later version.&n; * *&n; * * This program is distributed in the hope that it will be useful,&n; * * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; * * GNU General Public License for more details.&n; * *&n; * * You should have received a copy of the GNU General Public License&n; * * along with this program; if not, write to the Free Software&n; * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA&n; *&n; * Otherwise, the following license terms apply:&n; *&n; * * Redistribution and use in source and binary forms, with or without&n; * * modification, are permitted provided that the following conditions&n; * * are met:&n; * * 1) Redistributions of source code must retain the above copyright&n; * *    notice, this list of conditions and the following disclaimer.&n; * * 2) Redistributions in binary form must reproduce the above copyright&n; * *    notice, this list of conditions and the following disclaimer in the&n; * *    documentation and/or other materials provided with the distribution.&n; * * 3) The name of the author may not be used to endorse or promote products&n; * *    derived from this software without specific prior written permission.&n; * *&n; * * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS&squot;&squot; AND ANY EXPRESS OR&n; * * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES&n; * * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.&n; * * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,&n; * * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY&n; * * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * Author: &t;Thomas Winischhofer &lt;thomas@winischhofer.net&gt;&n; *&n; */
macro_line|#ifndef _VGATYPES_
DECL|macro|_VGATYPES_
mdefine_line|#define _VGATYPES_
macro_line|#ifdef LINUX_KERNEL  /* We don&squot;t want the X driver to depend on kernel source */
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE   0
macro_line|#endif
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE    1
macro_line|#endif
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL    0
macro_line|#endif
macro_line|#ifndef CHAR
DECL|typedef|CHAR
r_typedef
r_char
id|CHAR
suffix:semicolon
macro_line|#endif
macro_line|#ifndef SHORT
DECL|typedef|SHORT
r_typedef
r_int
id|SHORT
suffix:semicolon
macro_line|#endif
macro_line|#ifndef LONG
DECL|typedef|LONG
r_typedef
r_int
id|LONG
suffix:semicolon
macro_line|#endif
macro_line|#ifndef UCHAR
DECL|typedef|UCHAR
r_typedef
r_int
r_char
id|UCHAR
suffix:semicolon
macro_line|#endif
macro_line|#ifndef USHORT
DECL|typedef|USHORT
r_typedef
r_int
r_int
id|USHORT
suffix:semicolon
macro_line|#endif
macro_line|#ifndef ULONG
DECL|typedef|ULONG
r_typedef
r_int
r_int
id|ULONG
suffix:semicolon
macro_line|#endif
macro_line|#ifndef BOOLEAN
DECL|typedef|BOOLEAN
r_typedef
r_int
r_char
id|BOOLEAN
suffix:semicolon
macro_line|#endif
DECL|macro|SISIOMEMTYPE
mdefine_line|#define SISIOMEMTYPE
macro_line|#ifdef LINUX_KERNEL
DECL|typedef|SISIOADDRESS
r_typedef
r_int
r_int
id|SISIOADDRESS
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,6,8)
macro_line|#include &lt;linux/types.h&gt;  /* Need __iomem */
DECL|macro|SISIOMEMTYPE
macro_line|#undef SISIOMEMTYPE
DECL|macro|SISIOMEMTYPE
mdefine_line|#define SISIOMEMTYPE __iomem
macro_line|#endif
macro_line|#endif
macro_line|#ifdef LINUX_XF86
macro_line|#if XF86_VERSION_CURRENT &lt; XF86_VERSION_NUMERIC(4,2,0,0,0)
DECL|typedef|IOADDRESS
r_typedef
r_int
r_int
id|IOADDRESS
suffix:semicolon
DECL|typedef|SISIOADDRESS
r_typedef
r_int
r_int
id|SISIOADDRESS
suffix:semicolon
macro_line|#else
DECL|typedef|SISIOADDRESS
r_typedef
id|IOADDRESS
id|SISIOADDRESS
suffix:semicolon
macro_line|#endif
macro_line|#endif
DECL|enum|_SIS_CHIP_TYPE
r_enum
id|_SIS_CHIP_TYPE
(brace
DECL|enumerator|SIS_VGALegacy
id|SIS_VGALegacy
op_assign
l_int|0
comma
DECL|enumerator|SIS_530
id|SIS_530
comma
DECL|enumerator|SIS_OLD
id|SIS_OLD
comma
DECL|enumerator|SIS_300
id|SIS_300
comma
DECL|enumerator|SIS_630
id|SIS_630
comma
DECL|enumerator|SIS_730
id|SIS_730
comma
DECL|enumerator|SIS_540
id|SIS_540
comma
DECL|enumerator|SIS_315H
id|SIS_315H
comma
multiline_comment|/* SiS 310 */
DECL|enumerator|SIS_315
id|SIS_315
comma
DECL|enumerator|SIS_315PRO
id|SIS_315PRO
comma
DECL|enumerator|SIS_550
id|SIS_550
comma
DECL|enumerator|SIS_650
id|SIS_650
comma
DECL|enumerator|SIS_740
id|SIS_740
comma
DECL|enumerator|SIS_330
id|SIS_330
comma
DECL|enumerator|SIS_661
id|SIS_661
comma
DECL|enumerator|SIS_741
id|SIS_741
comma
DECL|enumerator|SIS_660
id|SIS_660
comma
DECL|enumerator|SIS_760
id|SIS_760
comma
DECL|enumerator|SIS_761
id|SIS_761
comma
DECL|enumerator|SIS_340
id|SIS_340
comma
DECL|enumerator|MAX_SIS_CHIP
id|MAX_SIS_CHIP
)brace
suffix:semicolon
macro_line|#ifndef SIS_HW_INFO
DECL|typedef|SIS_HW_INFO
DECL|typedef|PSIS_HW_INFO
r_typedef
r_struct
id|_SIS_HW_INFO
id|SIS_HW_INFO
comma
op_star
id|PSIS_HW_INFO
suffix:semicolon
DECL|struct|_SIS_HW_INFO
r_struct
id|_SIS_HW_INFO
(brace
macro_line|#ifdef LINUX_XF86
DECL|member|PciTag
id|PCITAG
id|PciTag
suffix:semicolon
multiline_comment|/* PCI Tag */
macro_line|#endif
DECL|member|pjVirtualRomBase
id|UCHAR
op_star
id|pjVirtualRomBase
suffix:semicolon
multiline_comment|/* ROM image */
DECL|member|UseROM
id|BOOLEAN
id|UseROM
suffix:semicolon
multiline_comment|/* Use the ROM image if provided */
macro_line|#ifdef LINUX_KERNEL
DECL|member|pjVideoMemoryAddress
id|UCHAR
id|SISIOMEMTYPE
op_star
id|pjVideoMemoryAddress
suffix:semicolon
multiline_comment|/* base virtual memory address */
multiline_comment|/* of Linear VGA memory */
DECL|member|ulVideoMemorySize
id|ULONG
id|ulVideoMemorySize
suffix:semicolon
multiline_comment|/* size, in bytes, of the memory on the board */
macro_line|#endif
DECL|member|ulIOAddress
id|SISIOADDRESS
id|ulIOAddress
suffix:semicolon
multiline_comment|/* base I/O address of VGA ports (0x3B0; relocated) */
DECL|member|jChipType
id|UCHAR
id|jChipType
suffix:semicolon
multiline_comment|/* Used to Identify SiS Graphics Chip */
multiline_comment|/* defined in the enum &quot;SIS_CHIP_TYPE&quot; (above or sisfb.h) */
DECL|member|jChipRevision
id|UCHAR
id|jChipRevision
suffix:semicolon
multiline_comment|/* Used to Identify SiS Graphics Chip Revision */
DECL|member|bIntegratedMMEnabled
id|BOOLEAN
id|bIntegratedMMEnabled
suffix:semicolon
multiline_comment|/* supporting integration MM enable */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* Addtional IOCTLs for communication sisfb &lt;&gt; X driver        */
multiline_comment|/* If changing this, sisfb.h must also be changed (for sisfb) */
macro_line|#ifdef LINUX_XF86  /* We don&squot;t want the X driver to depend on the kernel source */
multiline_comment|/* ioctl for identifying and giving some info (esp. memory heap start) */
DECL|macro|SISFB_GET_INFO_SIZE
mdefine_line|#define SISFB_GET_INFO_SIZE&t;0x8004f300
DECL|macro|SISFB_GET_INFO
mdefine_line|#define SISFB_GET_INFO&t;&t;0x8000f301  /* Must be patched with result from ..._SIZE at D[29:16] */
multiline_comment|/* deprecated ioctl number (for older versions of sisfb) */
DECL|macro|SISFB_GET_INFO_OLD
mdefine_line|#define SISFB_GET_INFO_OLD    &t;0x80046ef8
multiline_comment|/* ioctls for tv parameters (position) */
DECL|macro|SISFB_SET_TVPOSOFFSET
mdefine_line|#define SISFB_SET_TVPOSOFFSET   0x4004f304
multiline_comment|/* lock sisfb from register access */
DECL|macro|SISFB_SET_LOCK
mdefine_line|#define SISFB_SET_LOCK&t;&t;0x4004f306
multiline_comment|/* Structure argument for SISFB_GET_INFO ioctl  */
DECL|typedef|sisfb_info
DECL|typedef|psisfb_info
r_typedef
r_struct
id|_SISFB_INFO
id|sisfb_info
comma
op_star
id|psisfb_info
suffix:semicolon
DECL|struct|_SISFB_INFO
r_struct
id|_SISFB_INFO
(brace
DECL|member|sisfb_id
id|CARD32
id|sisfb_id
suffix:semicolon
multiline_comment|/* for identifying sisfb */
macro_line|#ifndef SISFB_ID
DECL|macro|SISFB_ID
mdefine_line|#define SISFB_ID&t;  0x53495346    /* Identify myself with &squot;SISF&squot; */
macro_line|#endif
DECL|member|chip_id
id|CARD32
id|chip_id
suffix:semicolon
multiline_comment|/* PCI ID of detected chip */
DECL|member|memory
id|CARD32
id|memory
suffix:semicolon
multiline_comment|/* video memory in KB which sisfb manages */
DECL|member|heapstart
id|CARD32
id|heapstart
suffix:semicolon
multiline_comment|/* heap start (= sisfb &quot;mem&quot; argument) in KB */
DECL|member|fbvidmode
id|CARD8
id|fbvidmode
suffix:semicolon
multiline_comment|/* current sisfb mode */
DECL|member|sisfb_version
id|CARD8
id|sisfb_version
suffix:semicolon
DECL|member|sisfb_revision
id|CARD8
id|sisfb_revision
suffix:semicolon
DECL|member|sisfb_patchlevel
id|CARD8
id|sisfb_patchlevel
suffix:semicolon
DECL|member|sisfb_caps
id|CARD8
id|sisfb_caps
suffix:semicolon
multiline_comment|/* sisfb&squot;s capabilities */
DECL|member|sisfb_tqlen
id|CARD32
id|sisfb_tqlen
suffix:semicolon
multiline_comment|/* turbo queue length (in KB) */
DECL|member|sisfb_pcibus
id|CARD32
id|sisfb_pcibus
suffix:semicolon
multiline_comment|/* The card&squot;s PCI ID */
DECL|member|sisfb_pcislot
id|CARD32
id|sisfb_pcislot
suffix:semicolon
DECL|member|sisfb_pcifunc
id|CARD32
id|sisfb_pcifunc
suffix:semicolon
DECL|member|sisfb_lcdpdc
id|CARD8
id|sisfb_lcdpdc
suffix:semicolon
DECL|member|sisfb_lcda
id|CARD8
id|sisfb_lcda
suffix:semicolon
DECL|member|sisfb_vbflags
id|CARD32
id|sisfb_vbflags
suffix:semicolon
DECL|member|sisfb_currentvbflags
id|CARD32
id|sisfb_currentvbflags
suffix:semicolon
DECL|member|sisfb_scalelcd
id|CARD32
id|sisfb_scalelcd
suffix:semicolon
DECL|member|sisfb_specialtiming
id|CARD32
id|sisfb_specialtiming
suffix:semicolon
DECL|member|sisfb_haveemi
id|CARD8
id|sisfb_haveemi
suffix:semicolon
DECL|member|sisfb_emi30
DECL|member|sisfb_emi31
DECL|member|sisfb_emi32
DECL|member|sisfb_emi33
id|CARD8
id|sisfb_emi30
comma
id|sisfb_emi31
comma
id|sisfb_emi32
comma
id|sisfb_emi33
suffix:semicolon
DECL|member|sisfb_haveemilcd
id|CARD8
id|sisfb_haveemilcd
suffix:semicolon
DECL|member|sisfb_lcdpdca
id|CARD8
id|sisfb_lcdpdca
suffix:semicolon
DECL|member|sisfb_tvxpos
DECL|member|sisfb_tvypos
id|CARD16
id|sisfb_tvxpos
comma
id|sisfb_tvypos
suffix:semicolon
multiline_comment|/* Warning: Values + 32 ! */
DECL|member|reserved
id|CARD8
id|reserved
(braket
l_int|208
)braket
suffix:semicolon
multiline_comment|/* for future use */
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
