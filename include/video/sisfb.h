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
mdefine_line|#define VB_CONEXANT&t;&t;0x00000800
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
multiline_comment|/* *Never* change the order of the following enum */
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
multiline_comment|/* chip_id in sisfb_info */
DECL|enumerator|SIS_300
id|SIS_300
comma
DECL|enumerator|SIS_630
id|SIS_630
comma
DECL|enumerator|SIS_540
id|SIS_540
comma
DECL|enumerator|SIS_730
id|SIS_730
comma
DECL|enumerator|SIS_315H
id|SIS_315H
comma
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
DECL|enumerator|MAX_SIS_CHIP
id|MAX_SIS_CHIP
DECL|typedef|SIS_CHIP_TYPE
)brace
id|SIS_CHIP_TYPE
suffix:semicolon
multiline_comment|/* Addtional IOCTLs for communication sisfb &lt;&gt; X driver                */
multiline_comment|/* If changing this, vgatypes.h must also be changed (for X driver)    */
multiline_comment|/* ioctl for identifying and giving some info (esp. memory heap start) */
DECL|macro|SISFB_GET_INFO
mdefine_line|#define SISFB_GET_INFO&t;  &t;_IOR(&squot;n&squot;,0xF8,__u32)
multiline_comment|/* ioctrl to get current vertical retrace status */
DECL|macro|SISFB_GET_VBRSTATUS
mdefine_line|#define SISFB_GET_VBRSTATUS  &t;_IOR(&squot;n&squot;,0xF9,__u32)
multiline_comment|/* ioctl to enable/disable panning auto-maximize (like nomax parameter) */
DECL|macro|SISFB_GET_AUTOMAXIMIZE
mdefine_line|#define SISFB_GET_AUTOMAXIMIZE &t;_IOR(&squot;n&squot;,0xFA,__u32)
DECL|macro|SISFB_SET_AUTOMAXIMIZE
mdefine_line|#define SISFB_SET_AUTOMAXIMIZE &t;_IOW(&squot;n&squot;,0xFA,__u32)
multiline_comment|/* TW: Structure argument for SISFB_GET_INFO ioctl  */
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
multiline_comment|/* Sisfb capabilities */
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
multiline_comment|/* PanelDelayCompensation */
DECL|member|sisfb_lcda
r_int
r_char
id|sisfb_lcda
suffix:semicolon
multiline_comment|/* Detected status of LCDA for low res/text modes */
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
multiline_comment|/* For fb memory manager */
DECL|struct|sis_memreq
r_struct
id|sis_memreq
(brace
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* More or less deprecated stuff follows: */
DECL|enum|_TVTYPE
r_typedef
r_enum
id|_TVTYPE
(brace
DECL|enumerator|TVMODE_NTSC
id|TVMODE_NTSC
op_assign
l_int|0
comma
DECL|enumerator|TVMODE_PAL
id|TVMODE_PAL
comma
DECL|enumerator|TVMODE_HIVISION
id|TVMODE_HIVISION
comma
DECL|enumerator|TVMODE_TOTAL
id|TVMODE_TOTAL
DECL|typedef|SIS_TV_TYPE
)brace
id|SIS_TV_TYPE
suffix:semicolon
DECL|enum|_TVPLUGTYPE
r_typedef
r_enum
id|_TVPLUGTYPE
(brace
DECL|enumerator|TVPLUG_Legacy
id|TVPLUG_Legacy
op_assign
l_int|0
comma
DECL|enumerator|TVPLUG_COMPOSITE
id|TVPLUG_COMPOSITE
comma
DECL|enumerator|TVPLUG_SVIDEO
id|TVPLUG_SVIDEO
comma
DECL|enumerator|TVPLUG_SCART
id|TVPLUG_SCART
comma
DECL|enumerator|TVPLUG_TOTAL
id|TVPLUG_TOTAL
DECL|typedef|SIS_TV_PLUG
)brace
id|SIS_TV_PLUG
suffix:semicolon
DECL|struct|mode_info
r_struct
id|mode_info
(brace
DECL|member|bpp
r_int
id|bpp
suffix:semicolon
DECL|member|xres
r_int
id|xres
suffix:semicolon
DECL|member|yres
r_int
id|yres
suffix:semicolon
DECL|member|v_xres
r_int
id|v_xres
suffix:semicolon
multiline_comment|/* deprecated - use var instead */
DECL|member|v_yres
r_int
id|v_yres
suffix:semicolon
multiline_comment|/* deprecated - use var instead */
DECL|member|org_x
r_int
id|org_x
suffix:semicolon
multiline_comment|/* deprecated - use var instead */
DECL|member|org_y
r_int
id|org_y
suffix:semicolon
multiline_comment|/* deprecated - use var instead */
DECL|member|vrate
r_int
r_int
id|vrate
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ap_data
r_struct
id|ap_data
(brace
DECL|member|minfo
r_struct
id|mode_info
id|minfo
suffix:semicolon
DECL|member|iobase
r_int
r_int
id|iobase
suffix:semicolon
DECL|member|mem_size
r_int
r_int
id|mem_size
suffix:semicolon
DECL|member|disp_state
r_int
r_int
id|disp_state
suffix:semicolon
multiline_comment|/* deprecated */
DECL|member|chip
id|SIS_CHIP_TYPE
id|chip
suffix:semicolon
DECL|member|hasVB
r_int
r_char
id|hasVB
suffix:semicolon
DECL|member|TV_type
id|SIS_TV_TYPE
id|TV_type
suffix:semicolon
multiline_comment|/* deprecated */
DECL|member|TV_plug
id|SIS_TV_PLUG
id|TV_plug
suffix:semicolon
multiline_comment|/* deprecated */
DECL|member|version
r_int
r_int
id|version
suffix:semicolon
DECL|member|vbflags
r_int
r_int
id|vbflags
suffix:semicolon
multiline_comment|/* replaces deprecated entries above */
DECL|member|currentvbflags
r_int
r_int
id|currentvbflags
suffix:semicolon
DECL|member|reserved
r_char
id|reserved
(braket
l_int|248
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**********************************************/
multiline_comment|/*                  PRIVATE                   */
multiline_comment|/**********************************************/
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/spinlock.h&gt;
DECL|enum|_VGA_ENGINE
r_typedef
r_enum
id|_VGA_ENGINE
(brace
DECL|enumerator|UNKNOWN_VGA
id|UNKNOWN_VGA
op_assign
l_int|0
comma
DECL|enumerator|SIS_300_VGA
id|SIS_300_VGA
comma
DECL|enumerator|SIS_315_VGA
id|SIS_315_VGA
comma
DECL|typedef|VGA_ENGINE
)brace
id|VGA_ENGINE
suffix:semicolon
DECL|struct|video_info
r_struct
id|video_info
(brace
DECL|member|chip_id
r_int
id|chip_id
suffix:semicolon
DECL|member|video_size
r_int
r_int
id|video_size
suffix:semicolon
DECL|member|video_base
r_int
r_int
id|video_base
suffix:semicolon
DECL|member|video_vbase
r_char
op_star
id|video_vbase
suffix:semicolon
DECL|member|mmio_base
r_int
r_int
id|mmio_base
suffix:semicolon
DECL|member|mmio_vbase
r_char
op_star
id|mmio_vbase
suffix:semicolon
DECL|member|vga_base
r_int
r_int
id|vga_base
suffix:semicolon
DECL|member|mtrr
r_int
r_int
id|mtrr
suffix:semicolon
DECL|member|heapstart
r_int
r_int
id|heapstart
suffix:semicolon
DECL|member|video_bpp
r_int
id|video_bpp
suffix:semicolon
DECL|member|video_cmap_len
r_int
id|video_cmap_len
suffix:semicolon
DECL|member|video_width
r_int
id|video_width
suffix:semicolon
DECL|member|video_height
r_int
id|video_height
suffix:semicolon
DECL|member|video_vwidth
r_int
id|video_vwidth
suffix:semicolon
multiline_comment|/* DEPRECATED - use var instead */
DECL|member|video_vheight
r_int
id|video_vheight
suffix:semicolon
multiline_comment|/* DEPRECATED - use var instead */
DECL|member|org_x
r_int
id|org_x
suffix:semicolon
multiline_comment|/* DEPRECATED - use var instead */
DECL|member|org_y
r_int
id|org_y
suffix:semicolon
multiline_comment|/* DEPRECATED - use var instead */
DECL|member|video_linelength
r_int
id|video_linelength
suffix:semicolon
DECL|member|refresh_rate
r_int
r_int
id|refresh_rate
suffix:semicolon
DECL|member|disp_state
r_int
r_int
id|disp_state
suffix:semicolon
multiline_comment|/* DEPRECATED */
DECL|member|hasVB
r_int
r_char
id|hasVB
suffix:semicolon
multiline_comment|/* DEPRECATED */
DECL|member|TV_type
r_int
r_char
id|TV_type
suffix:semicolon
multiline_comment|/* DEPRECATED */
DECL|member|TV_plug
r_int
r_char
id|TV_plug
suffix:semicolon
multiline_comment|/* DEPRECATED */
DECL|member|chip
id|SIS_CHIP_TYPE
id|chip
suffix:semicolon
DECL|member|revision_id
r_int
r_char
id|revision_id
suffix:semicolon
DECL|member|DstColor
r_int
r_int
id|DstColor
suffix:semicolon
multiline_comment|/* For 2d acceleration */
DECL|member|SiS310_AccelDepth
r_int
r_int
id|SiS310_AccelDepth
suffix:semicolon
DECL|member|CommandReg
r_int
r_int
id|CommandReg
suffix:semicolon
DECL|member|lockaccel
id|spinlock_t
id|lockaccel
suffix:semicolon
multiline_comment|/* Do not use outside of kernel! */
DECL|member|pcibus
r_int
r_int
id|pcibus
suffix:semicolon
DECL|member|pcislot
r_int
r_int
id|pcislot
suffix:semicolon
DECL|member|pcifunc
r_int
r_int
id|pcifunc
suffix:semicolon
DECL|member|accel
r_int
id|accel
suffix:semicolon
DECL|member|subsysvendor
r_int
r_int
id|subsysvendor
suffix:semicolon
DECL|member|subsysdevice
r_int
r_int
id|subsysdevice
suffix:semicolon
DECL|member|vbflags
r_int
r_int
id|vbflags
suffix:semicolon
multiline_comment|/* Replacing deprecated stuff from above */
DECL|member|currentvbflags
r_int
r_int
id|currentvbflags
suffix:semicolon
DECL|member|current_bpp
r_int
id|current_bpp
suffix:semicolon
DECL|member|current_width
r_int
id|current_width
suffix:semicolon
DECL|member|current_height
r_int
id|current_height
suffix:semicolon
DECL|member|current_htotal
r_int
id|current_htotal
suffix:semicolon
DECL|member|current_vtotal
r_int
id|current_vtotal
suffix:semicolon
DECL|member|current_pixclock
id|__u32
id|current_pixclock
suffix:semicolon
DECL|member|current_refresh_rate
r_int
id|current_refresh_rate
suffix:semicolon
DECL|member|reserved
r_char
id|reserved
(braket
l_int|200
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|video_info
id|ivideo
suffix:semicolon
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
r_int
r_int
id|base
)paren
suffix:semicolon
r_extern
r_void
id|sis_dispinfo
c_func
(paren
r_struct
id|ap_data
op_star
id|rec
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
