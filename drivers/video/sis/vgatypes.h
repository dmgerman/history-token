multiline_comment|/* $XFree86$ */
multiline_comment|/*&n; * General type definitions for universal mode switching modules&n; *&n; * Copyright (C) 2001-2004 by Thomas Winischhofer, Vienna, Austria&n; *&n; * If distributed as part of the Linux kernel, the following license terms&n; * apply:&n; *&n; * * This program is free software; you can redistribute it and/or modify&n; * * it under the terms of the GNU General Public License as published by&n; * * the Free Software Foundation; either version 2 of the named License,&n; * * or any later version.&n; * *&n; * * This program is distributed in the hope that it will be useful,&n; * * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; * * GNU General Public License for more details.&n; * *&n; * * You should have received a copy of the GNU General Public License&n; * * along with this program; if not, write to the Free Software&n; * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA&n; *&n; * Otherwise, the following license terms apply:&n; *&n; * * Redistribution and use in source and binary forms, with or without&n; * * modification, are permitted provided that the following conditions&n; * * are met:&n; * * 1) Redistributions of source code must retain the above copyright&n; * *    notice, this list of conditions and the following disclaimer.&n; * * 2) Redistributions in binary form must reproduce the above copyright&n; * *    notice, this list of conditions and the following disclaimer in the&n; * *    documentation and/or other materials provided with the distribution.&n; * * 3) All advertising materials mentioning features or use of this software&n; * *    must display the following acknowledgement: &quot;This product includes&n; * *    software developed by Thomas Winischhofer, Vienna, Austria.&quot;&n; * * 4) The name of the author may not be used to endorse or promote products&n; * *    derived from this software without specific prior written permission.&n; * *&n; * * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS&squot;&squot; AND ANY EXPRESS OR&n; * * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES&n; * * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.&n; * * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,&n; * * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY&n; * * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * Author: &t;Thomas Winischhofer &lt;thomas@winischhofer.net&gt;&n; *&n; */
macro_line|#ifndef _VGATYPES_
DECL|macro|_VGATYPES_
mdefine_line|#define _VGATYPES_
macro_line|#ifdef LINUX_XF86
macro_line|#include &quot;xf86Version.h&quot;
macro_line|#include &quot;xf86Pci.h&quot;
macro_line|#endif
macro_line|#ifdef LINUX_KERNEL  /* We don&squot;t want the X driver to depend on kernel source */
macro_line|#include &lt;linux/ioctl.h&gt;
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
id|UCHAR
id|BOOLEAN
suffix:semicolon
macro_line|#endif
macro_line|#ifndef bool
DECL|typedef|bool
r_typedef
id|UCHAR
r_bool
suffix:semicolon
macro_line|#endif
macro_line|#ifdef LINUX_KERNEL
DECL|typedef|SISIOADDRESS
r_typedef
r_int
r_int
id|SISIOADDRESS
suffix:semicolon
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
macro_line|#ifndef LINUX_KERNEL   /* For the linux kernel, this is defined in sisfb.h */
macro_line|#ifndef SIS_CHIP_TYPE
DECL|enum|_SIS_CHIP_TYPE
r_typedef
r_enum
id|_SIS_CHIP_TYPE
(brace
DECL|enumerator|SIS_VGALegacy
id|SIS_VGALegacy
op_assign
l_int|0
comma
macro_line|#ifdef LINUX_XF86
DECL|enumerator|SIS_530
id|SIS_530
comma
DECL|enumerator|SIS_OLD
id|SIS_OLD
comma
macro_line|#endif
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
multiline_comment|/* SiS 325 */
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
DECL|enumerator|MAX_SIS_CHIP
id|MAX_SIS_CHIP
DECL|typedef|SIS_CHIP_TYPE
)brace
id|SIS_CHIP_TYPE
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#ifndef SIS_VB_CHIP_TYPE
DECL|enum|_SIS_VB_CHIP_TYPE
r_typedef
r_enum
id|_SIS_VB_CHIP_TYPE
(brace
DECL|enumerator|VB_CHIP_Legacy
id|VB_CHIP_Legacy
op_assign
l_int|0
comma
DECL|enumerator|VB_CHIP_301
id|VB_CHIP_301
comma
DECL|enumerator|VB_CHIP_301B
id|VB_CHIP_301B
comma
DECL|enumerator|VB_CHIP_301LV
id|VB_CHIP_301LV
comma
DECL|enumerator|VB_CHIP_302
id|VB_CHIP_302
comma
DECL|enumerator|VB_CHIP_302B
id|VB_CHIP_302B
comma
DECL|enumerator|VB_CHIP_302LV
id|VB_CHIP_302LV
comma
DECL|enumerator|VB_CHIP_301C
id|VB_CHIP_301C
comma
DECL|enumerator|VB_CHIP_302ELV
id|VB_CHIP_302ELV
comma
DECL|enumerator|VB_CHIP_UNKNOWN
id|VB_CHIP_UNKNOWN
comma
multiline_comment|/* other video bridge or no video bridge */
DECL|enumerator|MAX_VB_CHIP
id|MAX_VB_CHIP
DECL|typedef|SIS_VB_CHIP_TYPE
)brace
id|SIS_VB_CHIP_TYPE
suffix:semicolon
macro_line|#endif
macro_line|#ifndef SIS_LCD_TYPE
DECL|enum|_SIS_LCD_TYPE
r_typedef
r_enum
id|_SIS_LCD_TYPE
(brace
DECL|enumerator|LCD_INVALID
id|LCD_INVALID
op_assign
l_int|0
comma
DECL|enumerator|LCD_800x600
id|LCD_800x600
comma
DECL|enumerator|LCD_1024x768
id|LCD_1024x768
comma
DECL|enumerator|LCD_1280x1024
id|LCD_1280x1024
comma
DECL|enumerator|LCD_1280x960
id|LCD_1280x960
comma
DECL|enumerator|LCD_640x480
id|LCD_640x480
comma
DECL|enumerator|LCD_1600x1200
id|LCD_1600x1200
comma
DECL|enumerator|LCD_1920x1440
id|LCD_1920x1440
comma
DECL|enumerator|LCD_2048x1536
id|LCD_2048x1536
comma
DECL|enumerator|LCD_320x480
id|LCD_320x480
comma
multiline_comment|/* FSTN, DSTN */
DECL|enumerator|LCD_1400x1050
id|LCD_1400x1050
comma
DECL|enumerator|LCD_1152x864
id|LCD_1152x864
comma
DECL|enumerator|LCD_1152x768
id|LCD_1152x768
comma
DECL|enumerator|LCD_1280x768
id|LCD_1280x768
comma
DECL|enumerator|LCD_1024x600
id|LCD_1024x600
comma
DECL|enumerator|LCD_640x480_2
id|LCD_640x480_2
comma
multiline_comment|/* FSTN, DSTN */
DECL|enumerator|LCD_640x480_3
id|LCD_640x480_3
comma
multiline_comment|/* FSTN, DSTN */
DECL|enumerator|LCD_848x480
id|LCD_848x480
comma
DECL|enumerator|LCD_1280x800
id|LCD_1280x800
comma
DECL|enumerator|LCD_1680x1050
id|LCD_1680x1050
comma
DECL|enumerator|LCD_CUSTOM
id|LCD_CUSTOM
comma
DECL|enumerator|LCD_UNKNOWN
id|LCD_UNKNOWN
DECL|typedef|SIS_LCD_TYPE
)brace
id|SIS_LCD_TYPE
suffix:semicolon
macro_line|#endif
macro_line|#ifndef PSIS_DSReg
DECL|struct|_SIS_DSReg
r_typedef
r_struct
id|_SIS_DSReg
(brace
DECL|member|jIdx
id|UCHAR
id|jIdx
suffix:semicolon
DECL|member|jVal
id|UCHAR
id|jVal
suffix:semicolon
DECL|typedef|SIS_DSReg
DECL|typedef|PSIS_DSReg
)brace
id|SIS_DSReg
comma
op_star
id|PSIS_DSReg
suffix:semicolon
macro_line|#endif
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
DECL|typedef|PSIS_QUERYSPACE
r_typedef
id|BOOLEAN
(paren
op_star
id|PSIS_QUERYSPACE
)paren
(paren
id|PSIS_HW_INFO
comma
id|ULONG
comma
id|ULONG
comma
id|ULONG
op_star
)paren
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
DECL|member|pjVideoMemoryAddress
id|UCHAR
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
DECL|member|ulIOAddress
id|SISIOADDRESS
id|ulIOAddress
suffix:semicolon
multiline_comment|/* base I/O address of VGA ports (0x3B0) */
DECL|member|jChipType
id|UCHAR
id|jChipType
suffix:semicolon
multiline_comment|/* Used to Identify SiS Graphics Chip */
multiline_comment|/* defined in the data structure type  */
multiline_comment|/* &quot;SIS_CHIP_TYPE&quot; */
DECL|member|jChipRevision
id|UCHAR
id|jChipRevision
suffix:semicolon
multiline_comment|/* Used to Identify SiS Graphics Chip Revision */
DECL|member|ujVBChipID
id|UCHAR
id|ujVBChipID
suffix:semicolon
multiline_comment|/* the ID of video bridge */
multiline_comment|/* defined in the data structure type */
multiline_comment|/* &quot;SIS_VB_CHIP_TYPE&quot; */
macro_line|#ifdef LINUX_KERNEL
DECL|member|Is301BDH
id|BOOLEAN
id|Is301BDH
suffix:semicolon
macro_line|#endif
DECL|member|usExternalChip
id|USHORT
id|usExternalChip
suffix:semicolon
multiline_comment|/* NO VB or other video bridge (other than  */
multiline_comment|/* SiS video bridge) */
DECL|member|ulCRT2LCDType
id|ULONG
id|ulCRT2LCDType
suffix:semicolon
multiline_comment|/* defined in the data structure type */
multiline_comment|/* &quot;SIS_LCD_TYPE&quot; */
DECL|member|bIntegratedMMEnabled
id|BOOLEAN
id|bIntegratedMMEnabled
suffix:semicolon
multiline_comment|/* supporting integration MM enable */
DECL|member|bSkipDramSizing
id|BOOLEAN
id|bSkipDramSizing
suffix:semicolon
multiline_comment|/* True: Skip video memory sizing. */
macro_line|#ifdef LINUX_KERNEL
DECL|member|pSR
id|PSIS_DSReg
id|pSR
suffix:semicolon
multiline_comment|/* restore SR registers in initial function. */
multiline_comment|/* end data :(idx, val) =  (FF, FF). */
multiline_comment|/* Note : restore SR registers if  */
multiline_comment|/* bSkipDramSizing = TRUE */
DECL|member|pCR
id|PSIS_DSReg
id|pCR
suffix:semicolon
multiline_comment|/* restore CR registers in initial function. */
multiline_comment|/* end data :(idx, val) =  (FF, FF) */
multiline_comment|/* Note : restore cR registers if  */
multiline_comment|/* bSkipDramSizing = TRUE */
macro_line|#endif
DECL|member|pQueryVGAConfigSpace
id|PSIS_QUERYSPACE
id|pQueryVGAConfigSpace
suffix:semicolon
multiline_comment|/* Get/Set VGA Configuration  */
multiline_comment|/* space */
DECL|member|pQueryNorthBridgeSpace
id|PSIS_QUERYSPACE
id|pQueryNorthBridgeSpace
suffix:semicolon
multiline_comment|/* Get/Set North Bridge  */
multiline_comment|/* space  */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* Addtional IOCTL for communication sisfb &lt;&gt; X driver        */
multiline_comment|/* If changing this, sisfb.h must also be changed (for sisfb) */
macro_line|#ifdef LINUX_XF86  /* We don&squot;t want the X driver to depend on the kernel source */
multiline_comment|/* ioctl for identifying and giving some info (esp. memory heap start) */
DECL|macro|SISFB_GET_INFO
mdefine_line|#define SISFB_GET_INFO    0x80046ef8  /* Wow, what a terrible hack... */
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
r_int
r_int
id|sisfb_id
suffix:semicolon
multiline_comment|/* for identifying sisfb */
macro_line|#ifndef SISFB_ID
DECL|macro|SISFB_ID
mdefine_line|#define SISFB_ID&t;  0x53495346    /* Identify myself with &squot;SISF&squot; */
macro_line|#endif
DECL|member|chip_id
r_int
id|chip_id
suffix:semicolon
multiline_comment|/* PCI ID of detected chip */
DECL|member|memory
r_int
id|memory
suffix:semicolon
multiline_comment|/* video memory in KB which sisfb manages */
DECL|member|heapstart
r_int
id|heapstart
suffix:semicolon
multiline_comment|/* heap start (= sisfb &quot;mem&quot; argument) in KB */
DECL|member|fbvidmode
r_int
r_char
id|fbvidmode
suffix:semicolon
multiline_comment|/* current sisfb mode */
DECL|member|sisfb_version
r_int
r_char
id|sisfb_version
suffix:semicolon
DECL|member|sisfb_revision
r_int
r_char
id|sisfb_revision
suffix:semicolon
DECL|member|sisfb_patchlevel
r_int
r_char
id|sisfb_patchlevel
suffix:semicolon
DECL|member|sisfb_caps
r_int
r_char
id|sisfb_caps
suffix:semicolon
multiline_comment|/* sisfb&squot;s capabilities */
DECL|member|sisfb_tqlen
r_int
id|sisfb_tqlen
suffix:semicolon
multiline_comment|/* turbo queue length (in KB) */
DECL|member|sisfb_pcibus
r_int
r_int
id|sisfb_pcibus
suffix:semicolon
multiline_comment|/* The card&squot;s PCI ID */
DECL|member|sisfb_pcislot
r_int
r_int
id|sisfb_pcislot
suffix:semicolon
DECL|member|sisfb_pcifunc
r_int
r_int
id|sisfb_pcifunc
suffix:semicolon
DECL|member|sisfb_lcdpdc
r_int
r_char
id|sisfb_lcdpdc
suffix:semicolon
DECL|member|sisfb_lcda
r_int
r_char
id|sisfb_lcda
suffix:semicolon
DECL|member|sisfb_vbflags
r_int
r_int
id|sisfb_vbflags
suffix:semicolon
DECL|member|sisfb_currentvbflags
r_int
r_int
id|sisfb_currentvbflags
suffix:semicolon
DECL|member|sisfb_scalelcd
r_int
id|sisfb_scalelcd
suffix:semicolon
DECL|member|sisfb_specialtiming
r_int
r_int
id|sisfb_specialtiming
suffix:semicolon
DECL|member|sisfb_haveemi
r_int
r_char
id|sisfb_haveemi
suffix:semicolon
DECL|member|sisfb_emi30
DECL|member|sisfb_emi31
DECL|member|sisfb_emi32
DECL|member|sisfb_emi33
r_int
r_char
id|sisfb_emi30
comma
id|sisfb_emi31
comma
id|sisfb_emi32
comma
id|sisfb_emi33
suffix:semicolon
DECL|member|sisfb_haveemilcd
r_int
r_char
id|sisfb_haveemilcd
suffix:semicolon
DECL|member|reserved
r_char
id|reserved
(braket
l_int|213
)braket
suffix:semicolon
multiline_comment|/* for future use */
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
