multiline_comment|/*&n; * Copyright (C) 2001-2004 by Thomas Winischhofer, Vienna, Austria.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the named License,&n; * or any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA&n; */
macro_line|#ifndef _LINUX_SISFB
DECL|macro|_LINUX_SISFB
mdefine_line|#define _LINUX_SISFB
macro_line|#include &lt;asm/ioctl.h&gt;
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/**********************************************/
multiline_comment|/*                   PUBLIC                   */
multiline_comment|/**********************************************/
multiline_comment|/* vbflags */
DECL|macro|CRT2_DEFAULT
mdefine_line|#define CRT2_DEFAULT            0x00000001
DECL|macro|CRT2_LCD
mdefine_line|#define CRT2_LCD                0x00000002  /* TW: Never change the order of the CRT2_XXX entries */
DECL|macro|CRT2_TV
mdefine_line|#define CRT2_TV                 0x00000004  /*     (see SISCycleCRT2Type())                       */
DECL|macro|CRT2_VGA
mdefine_line|#define CRT2_VGA                0x00000008
DECL|macro|TV_NTSC
mdefine_line|#define TV_NTSC                 0x00000010
DECL|macro|TV_PAL
mdefine_line|#define TV_PAL                  0x00000020
DECL|macro|TV_HIVISION
mdefine_line|#define TV_HIVISION             0x00000040
DECL|macro|TV_YPBPR
mdefine_line|#define TV_YPBPR                0x00000080
DECL|macro|TV_AVIDEO
mdefine_line|#define TV_AVIDEO               0x00000100
DECL|macro|TV_SVIDEO
mdefine_line|#define TV_SVIDEO               0x00000200
DECL|macro|TV_SCART
mdefine_line|#define TV_SCART                0x00000400
DECL|macro|VB_CONEXANT
mdefine_line|#define VB_CONEXANT&t;&t;0x00000800&t;/* 661 series only */
DECL|macro|VB_TRUMPION
mdefine_line|#define VB_TRUMPION&t;&t;VB_CONEXANT&t;/* 300 series only */
DECL|macro|TV_PALM
mdefine_line|#define TV_PALM                 0x00001000
DECL|macro|TV_PALN
mdefine_line|#define TV_PALN                 0x00002000
DECL|macro|TV_NTSCJ
mdefine_line|#define TV_NTSCJ&t;&t;0x00001000
DECL|macro|VB_302ELV
mdefine_line|#define VB_302ELV&t;&t;0x00004000
DECL|macro|TV_CHSCART
mdefine_line|#define TV_CHSCART              0x00008000
DECL|macro|TV_CHYPBPR525I
mdefine_line|#define TV_CHYPBPR525I          0x00010000
DECL|macro|CRT1_VGA
mdefine_line|#define CRT1_VGA&t;&t;0x00000000
DECL|macro|CRT1_LCDA
mdefine_line|#define CRT1_LCDA&t;&t;0x00020000
DECL|macro|VGA2_CONNECTED
mdefine_line|#define VGA2_CONNECTED          0x00040000
DECL|macro|VB_DISPTYPE_CRT1
mdefine_line|#define VB_DISPTYPE_CRT1&t;0x00080000  &t;/* CRT1 connected and used */
DECL|macro|VB_301
mdefine_line|#define VB_301                  0x00100000&t;/* Video bridge type */
DECL|macro|VB_301B
mdefine_line|#define VB_301B                 0x00200000
DECL|macro|VB_302B
mdefine_line|#define VB_302B                 0x00400000
DECL|macro|VB_30xBDH
mdefine_line|#define VB_30xBDH&t;&t;0x00800000      /* 30xB DH version (w/o LCD support) */
DECL|macro|VB_LVDS
mdefine_line|#define VB_LVDS                 0x01000000
DECL|macro|VB_CHRONTEL
mdefine_line|#define VB_CHRONTEL             0x02000000
DECL|macro|VB_301LV
mdefine_line|#define VB_301LV                0x04000000
DECL|macro|VB_302LV
mdefine_line|#define VB_302LV                0x08000000
DECL|macro|VB_301C
mdefine_line|#define VB_301C&t;&t;&t;0x10000000
DECL|macro|VB_SINGLE_MODE
mdefine_line|#define VB_SINGLE_MODE          0x20000000   &t;/* CRT1 or CRT2; determined by DISPTYPE_CRTx */
DECL|macro|VB_MIRROR_MODE
mdefine_line|#define VB_MIRROR_MODE&t;&t;0x40000000   &t;/* CRT1 + CRT2 identical (mirror mode) */
DECL|macro|VB_DUALVIEW_MODE
mdefine_line|#define VB_DUALVIEW_MODE&t;0x80000000   &t;/* CRT1 + CRT2 independent (dual head mode) */
multiline_comment|/* Aliases: */
DECL|macro|CRT2_ENABLE
mdefine_line|#define CRT2_ENABLE&t;&t;(CRT2_LCD | CRT2_TV | CRT2_VGA)
DECL|macro|TV_STANDARD
mdefine_line|#define TV_STANDARD             (TV_NTSC | TV_PAL | TV_PALM | TV_PALN | TV_NTSCJ)
DECL|macro|TV_INTERFACE
mdefine_line|#define TV_INTERFACE            (TV_AVIDEO|TV_SVIDEO|TV_SCART|TV_HIVISION|TV_YPBPR|TV_CHSCART|TV_CHYPBPR525I)
multiline_comment|/* Only if TV_YPBPR is set: */
DECL|macro|TV_YPBPR525I
mdefine_line|#define TV_YPBPR525I&t;&t;TV_NTSC
DECL|macro|TV_YPBPR525P
mdefine_line|#define TV_YPBPR525P&t;&t;TV_PAL
DECL|macro|TV_YPBPR750P
mdefine_line|#define TV_YPBPR750P&t;&t;TV_PALM
DECL|macro|TV_YPBPR1080I
mdefine_line|#define TV_YPBPR1080I&t;&t;TV_PALN
DECL|macro|TV_YPBPRALL
mdefine_line|#define TV_YPBPRALL &t;&t;(TV_YPBPR525I | TV_YPBPR525P | TV_YPBPR750P | TV_YPBPR1080I)
DECL|macro|VB_SISBRIDGE
mdefine_line|#define VB_SISBRIDGE            (VB_301|VB_301B|VB_301C|VB_302B|VB_301LV|VB_302LV|VB_302ELV)
DECL|macro|VB_SISTVBRIDGE
mdefine_line|#define VB_SISTVBRIDGE          (VB_301|VB_301B|VB_301C|VB_302B|VB_301LV|VB_302LV)
DECL|macro|VB_VIDEOBRIDGE
mdefine_line|#define VB_VIDEOBRIDGE&t;&t;(VB_SISBRIDGE | VB_LVDS | VB_CHRONTEL | VB_CONEXANT)
DECL|macro|VB_DISPTYPE_DISP2
mdefine_line|#define VB_DISPTYPE_DISP2&t;CRT2_ENABLE
DECL|macro|VB_DISPTYPE_CRT2
mdefine_line|#define VB_DISPTYPE_CRT2&t;CRT2_ENABLE
DECL|macro|VB_DISPTYPE_DISP1
mdefine_line|#define VB_DISPTYPE_DISP1&t;VB_DISPTYPE_CRT1
DECL|macro|VB_DISPMODE_SINGLE
mdefine_line|#define VB_DISPMODE_SINGLE&t;VB_SINGLE_MODE
DECL|macro|VB_DISPMODE_MIRROR
mdefine_line|#define VB_DISPMODE_MIRROR&t;VB_MIRROR_MODE
DECL|macro|VB_DISPMODE_DUAL
mdefine_line|#define VB_DISPMODE_DUAL&t;VB_DUALVIEW_MODE
DECL|macro|VB_DISPLAY_MODE
mdefine_line|#define VB_DISPLAY_MODE       &t;(SINGLE_MODE | MIRROR_MODE | DUALVIEW_MODE)
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
id|__u32
id|sisfb_id
suffix:semicolon
multiline_comment|/* for identifying sisfb */
macro_line|#ifndef SISFB_ID
DECL|macro|SISFB_ID
mdefine_line|#define SISFB_ID&t;  0x53495346    /* Identify myself with &squot;SISF&squot; */
macro_line|#endif
DECL|member|chip_id
id|__u32
id|chip_id
suffix:semicolon
multiline_comment|/* PCI-ID of detected chip */
DECL|member|memory
id|__u32
id|memory
suffix:semicolon
multiline_comment|/* video memory in KB which sisfb manages */
DECL|member|heapstart
id|__u32
id|heapstart
suffix:semicolon
multiline_comment|/* heap start (= sisfb &quot;mem&quot; argument) in KB */
DECL|member|fbvidmode
id|__u8
id|fbvidmode
suffix:semicolon
multiline_comment|/* current sisfb mode */
DECL|member|sisfb_version
id|__u8
id|sisfb_version
suffix:semicolon
DECL|member|sisfb_revision
id|__u8
id|sisfb_revision
suffix:semicolon
DECL|member|sisfb_patchlevel
id|__u8
id|sisfb_patchlevel
suffix:semicolon
DECL|member|sisfb_caps
id|__u8
id|sisfb_caps
suffix:semicolon
multiline_comment|/* sisfb capabilities */
DECL|member|sisfb_tqlen
id|__u32
id|sisfb_tqlen
suffix:semicolon
multiline_comment|/* turbo queue length (in KB) */
DECL|member|sisfb_pcibus
id|__u32
id|sisfb_pcibus
suffix:semicolon
multiline_comment|/* The card&squot;s PCI ID */
DECL|member|sisfb_pcislot
id|__u32
id|sisfb_pcislot
suffix:semicolon
DECL|member|sisfb_pcifunc
id|__u32
id|sisfb_pcifunc
suffix:semicolon
DECL|member|sisfb_lcdpdc
id|__u8
id|sisfb_lcdpdc
suffix:semicolon
multiline_comment|/* PanelDelayCompensation */
DECL|member|sisfb_lcda
id|__u8
id|sisfb_lcda
suffix:semicolon
multiline_comment|/* Detected status of LCDA for low res/text modes */
DECL|member|sisfb_vbflags
id|__u32
id|sisfb_vbflags
suffix:semicolon
DECL|member|sisfb_currentvbflags
id|__u32
id|sisfb_currentvbflags
suffix:semicolon
DECL|member|sisfb_scalelcd
id|__u32
id|sisfb_scalelcd
suffix:semicolon
DECL|member|sisfb_specialtiming
id|__u32
id|sisfb_specialtiming
suffix:semicolon
DECL|member|sisfb_haveemi
id|__u8
id|sisfb_haveemi
suffix:semicolon
DECL|member|sisfb_emi30
DECL|member|sisfb_emi31
DECL|member|sisfb_emi32
DECL|member|sisfb_emi33
id|__u8
id|sisfb_emi30
comma
id|sisfb_emi31
comma
id|sisfb_emi32
comma
id|sisfb_emi33
suffix:semicolon
DECL|member|sisfb_haveemilcd
id|__u8
id|sisfb_haveemilcd
suffix:semicolon
DECL|member|sisfb_lcdpdca
id|__u8
id|sisfb_lcdpdca
suffix:semicolon
multiline_comment|/* PanelDelayCompensation for LCD-via-CRT1 */
DECL|member|sisfb_tvxpos
DECL|member|sisfb_tvypos
id|__u16
id|sisfb_tvxpos
comma
id|sisfb_tvypos
suffix:semicolon
multiline_comment|/* Warning: Values + 32 ! */
DECL|member|reserved
id|__u8
id|reserved
(braket
l_int|208
)braket
suffix:semicolon
multiline_comment|/* for future use */
)brace
suffix:semicolon
multiline_comment|/* Addtional IOCTLs for communication sisfb &lt;&gt; X driver                */
multiline_comment|/* If changing this, vgatypes.h must also be changed (for X driver)    */
multiline_comment|/* ioctl for identifying and giving some info (esp. memory heap start) */
DECL|macro|SISFB_GET_INFO_SIZE
mdefine_line|#define SISFB_GET_INFO_SIZE  &t;_IOR(0xF3,0x00,__u32)
DECL|macro|SISFB_GET_INFO
mdefine_line|#define SISFB_GET_INFO&t;  &t;_IOR(0xF3,0x01,struct _SISFB_INFO)
multiline_comment|/* ioctrl to get current vertical retrace status */
DECL|macro|SISFB_GET_VBRSTATUS
mdefine_line|#define SISFB_GET_VBRSTATUS  &t;_IOR(0xF3,0x02,__u32)
multiline_comment|/* ioctl to enable/disable panning auto-maximize (like nomax parameter) */
DECL|macro|SISFB_GET_AUTOMAXIMIZE
mdefine_line|#define SISFB_GET_AUTOMAXIMIZE &t;_IOR(0xF3,0x03,__u32)
DECL|macro|SISFB_SET_AUTOMAXIMIZE
mdefine_line|#define SISFB_SET_AUTOMAXIMIZE &t;_IOW(0xF3,0x03,__u32)
multiline_comment|/* ioctls to relocate TV output (x=D[31:16], y=D[15:0], + 32)*/
DECL|macro|SISFB_GET_TVPOSOFFSET
mdefine_line|#define SISFB_GET_TVPOSOFFSET   _IOR(0xF3,0x04,__u32)
DECL|macro|SISFB_SET_TVPOSOFFSET
mdefine_line|#define SISFB_SET_TVPOSOFFSET   _IOW(0xF3,0x04,__u32)
multiline_comment|/* ioctl for locking sisfb (no register access during lock) */
multiline_comment|/* As of now, only used to avoid register access during&n; * the ioctls listed above.&n; */
DECL|macro|SISFB_SET_LOCK
mdefine_line|#define SISFB_SET_LOCK  &t;_IOW(0xF3,0x06,__u32)
multiline_comment|/* more to come soon */
multiline_comment|/* ioctls 0xF3 up to 0x3F reserved for sisfb */
multiline_comment|/****************************************************************/
multiline_comment|/* The following are deprecated and should not be used anymore: */
multiline_comment|/****************************************************************/
multiline_comment|/* ioctl for identifying and giving some info (esp. memory heap start) */
DECL|macro|SISFB_GET_INFO_OLD
mdefine_line|#define SISFB_GET_INFO_OLD  &t;   _IOR(&squot;n&squot;,0xF8,__u32)
multiline_comment|/* ioctrl to get current vertical retrace status */
DECL|macro|SISFB_GET_VBRSTATUS_OLD
mdefine_line|#define SISFB_GET_VBRSTATUS_OLD&t;   _IOR(&squot;n&squot;,0xF9,__u32)
multiline_comment|/* ioctl to enable/disable panning auto-maximize (like nomax parameter) */
DECL|macro|SISFB_GET_AUTOMAXIMIZE_OLD
mdefine_line|#define SISFB_GET_AUTOMAXIMIZE_OLD _IOR(&squot;n&squot;,0xFA,__u32)
DECL|macro|SISFB_SET_AUTOMAXIMIZE_OLD
mdefine_line|#define SISFB_SET_AUTOMAXIMIZE_OLD _IOW(&squot;n&squot;,0xFA,__u32)
multiline_comment|/****************************************************************/
multiline_comment|/*               End of deprecated ioctl numbers                */
multiline_comment|/****************************************************************/
multiline_comment|/* For fb memory manager (FBIO_ALLOC, FBIO_FREE) */
DECL|struct|sis_memreq
r_struct
id|sis_memreq
(brace
DECL|member|offset
id|__u32
id|offset
suffix:semicolon
DECL|member|size
id|__u32
id|size
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**********************************************/
multiline_comment|/*                  PRIVATE                   */
multiline_comment|/*         (for IN-KERNEL usage only)         */
multiline_comment|/**********************************************/
macro_line|#ifdef __KERNEL__
DECL|macro|UNKNOWN_VGA
mdefine_line|#define&t;UNKNOWN_VGA  0
DECL|macro|SIS_300_VGA
mdefine_line|#define&t;SIS_300_VGA  1
DECL|macro|SIS_315_VGA
mdefine_line|#define&t;SIS_315_VGA  2
r_extern
r_void
id|sis_malloc
c_func
(paren
r_struct
id|sis_memreq
op_star
id|req
)paren
suffix:semicolon
r_extern
r_void
id|sis_free
c_func
(paren
id|u32
id|base
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
