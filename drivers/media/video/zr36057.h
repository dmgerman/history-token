multiline_comment|/* &n;   zr36057.h - zr36057 register offsets&n;&n;   Copyright (C) 1998 Dave Perks &lt;dperks@ibm.net&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n;&n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _ZR36057_H_
DECL|macro|_ZR36057_H_
mdefine_line|#define _ZR36057_H_
multiline_comment|/* Zoran ZR36057 registers */
DECL|macro|ZR36057_VFEHCR
mdefine_line|#define ZR36057_VFEHCR          0x000&t;/* Video Front End, Horizontal Configuration Register */
DECL|macro|ZR36057_VFEHCR_HSPol
mdefine_line|#define ZR36057_VFEHCR_HSPol            (1&lt;&lt;30)
DECL|macro|ZR36057_VFEHCR_HStart
mdefine_line|#define ZR36057_VFEHCR_HStart           10
DECL|macro|ZR36057_VFEHCR_HEnd
mdefine_line|#define ZR36057_VFEHCR_HEnd&t;        0
DECL|macro|ZR36057_VFEHCR_Hmask
mdefine_line|#define ZR36057_VFEHCR_Hmask&t;        0x3ff
DECL|macro|ZR36057_VFEVCR
mdefine_line|#define ZR36057_VFEVCR          0x004&t;/* Video Front End, Vertical Configuration Register */
DECL|macro|ZR36057_VFEVCR_VSPol
mdefine_line|#define ZR36057_VFEVCR_VSPol            (1&lt;&lt;30)
DECL|macro|ZR36057_VFEVCR_VStart
mdefine_line|#define ZR36057_VFEVCR_VStart           10
DECL|macro|ZR36057_VFEVCR_VEnd
mdefine_line|#define ZR36057_VFEVCR_VEnd&t;        0
DECL|macro|ZR36057_VFEVCR_Vmask
mdefine_line|#define ZR36057_VFEVCR_Vmask&t;        0x3ff
DECL|macro|ZR36057_VFESPFR
mdefine_line|#define ZR36057_VFESPFR         0x008&t;/* Video Front End, Scaler and Pixel Format Register */
DECL|macro|ZR36057_VFESPFR_ExtFl
mdefine_line|#define ZR36057_VFESPFR_ExtFl           (1&lt;&lt;26)
DECL|macro|ZR36057_VFESPFR_TopField
mdefine_line|#define ZR36057_VFESPFR_TopField        (1&lt;&lt;25)
DECL|macro|ZR36057_VFESPFR_VCLKPol
mdefine_line|#define ZR36057_VFESPFR_VCLKPol         (1&lt;&lt;24)
DECL|macro|ZR36057_VFESPFR_HFilter
mdefine_line|#define ZR36057_VFESPFR_HFilter         21
DECL|macro|ZR36057_VFESPFR_HorDcm
mdefine_line|#define ZR36057_VFESPFR_HorDcm          14
DECL|macro|ZR36057_VFESPFR_VerDcm
mdefine_line|#define ZR36057_VFESPFR_VerDcm          8
DECL|macro|ZR36057_VFESPFR_DispMode
mdefine_line|#define ZR36057_VFESPFR_DispMode        6
DECL|macro|ZR36057_VFESPFR_YUV422
mdefine_line|#define ZR36057_VFESPFR_YUV422          (0&lt;&lt;3)
DECL|macro|ZR36057_VFESPFR_RGB888
mdefine_line|#define ZR36057_VFESPFR_RGB888          (1&lt;&lt;3)
DECL|macro|ZR36057_VFESPFR_RGB565
mdefine_line|#define ZR36057_VFESPFR_RGB565          (2&lt;&lt;3)
DECL|macro|ZR36057_VFESPFR_RGB555
mdefine_line|#define ZR36057_VFESPFR_RGB555          (3&lt;&lt;3)
DECL|macro|ZR36057_VFESPFR_ErrDif
mdefine_line|#define ZR36057_VFESPFR_ErrDif          (1&lt;&lt;2)
DECL|macro|ZR36057_VFESPFR_Pack24
mdefine_line|#define ZR36057_VFESPFR_Pack24          (1&lt;&lt;1)
DECL|macro|ZR36057_VFESPFR_LittleEndian
mdefine_line|#define ZR36057_VFESPFR_LittleEndian    (1&lt;&lt;0)
DECL|macro|ZR36057_VDTR
mdefine_line|#define ZR36057_VDTR            0x00c&t;/* Video Display &quot;Top&quot; Register */
DECL|macro|ZR36057_VDBR
mdefine_line|#define ZR36057_VDBR            0x010&t;/* Video Display &quot;Bottom&quot; Register */
DECL|macro|ZR36057_VSSFGR
mdefine_line|#define ZR36057_VSSFGR          0x014&t;/* Video Stride, Status, and Frame Grab Register */
DECL|macro|ZR36057_VSSFGR_DispStride
mdefine_line|#define ZR36057_VSSFGR_DispStride       16
DECL|macro|ZR36057_VSSFGR_VidOvf
mdefine_line|#define ZR36057_VSSFGR_VidOvf           (1&lt;&lt;8)
DECL|macro|ZR36057_VSSFGR_SnapShot
mdefine_line|#define ZR36057_VSSFGR_SnapShot         (1&lt;&lt;1)
DECL|macro|ZR36057_VSSFGR_FrameGrab
mdefine_line|#define ZR36057_VSSFGR_FrameGrab        (1&lt;&lt;0)
DECL|macro|ZR36057_VDCR
mdefine_line|#define ZR36057_VDCR            0x018&t;/* Video Display Configuration Register */
DECL|macro|ZR36057_VDCR_VidEn
mdefine_line|#define ZR36057_VDCR_VidEn              (1&lt;&lt;31)
DECL|macro|ZR36057_VDCR_MinPix
mdefine_line|#define ZR36057_VDCR_MinPix             24
DECL|macro|ZR36057_VDCR_Triton
mdefine_line|#define ZR36057_VDCR_Triton             (1&lt;&lt;24)
DECL|macro|ZR36057_VDCR_VidWinHt
mdefine_line|#define ZR36057_VDCR_VidWinHt           12
DECL|macro|ZR36057_VDCR_VidWinWid
mdefine_line|#define ZR36057_VDCR_VidWinWid          0
DECL|macro|ZR36057_MMTR
mdefine_line|#define ZR36057_MMTR            0x01c&t;/* Masking Map &quot;Top&quot; Register */
DECL|macro|ZR36057_MMBR
mdefine_line|#define ZR36057_MMBR            0x020&t;/* Masking Map &quot;Bottom&quot; Register */
DECL|macro|ZR36057_OCR
mdefine_line|#define ZR36057_OCR             0x024&t;/* Overlay Control Register */
DECL|macro|ZR36057_OCR_OvlEnable
mdefine_line|#define ZR36057_OCR_OvlEnable           (1 &lt;&lt; 15)
DECL|macro|ZR36057_OCR_MaskStride
mdefine_line|#define ZR36057_OCR_MaskStride          0
DECL|macro|ZR36057_SPGPPCR
mdefine_line|#define ZR36057_SPGPPCR         0x028&t;/* System, PCI, and General Purpose Pins Control Register */
DECL|macro|ZR36057_SPGPPCR_SoftReset
mdefine_line|#define ZR36057_SPGPPCR_SoftReset&t;(1&lt;&lt;24)
DECL|macro|ZR36057_GPPGCR1
mdefine_line|#define ZR36057_GPPGCR1         0x02c&t;/* General Purpose Pins and GuestBus Control Register (1) */
DECL|macro|ZR36057_MCSAR
mdefine_line|#define ZR36057_MCSAR           0x030&t;/* MPEG Code Source Address Register */
DECL|macro|ZR36057_MCTCR
mdefine_line|#define ZR36057_MCTCR           0x034&t;/* MPEG Code Transfer Control Register */
DECL|macro|ZR36057_MCTCR_CodTime
mdefine_line|#define ZR36057_MCTCR_CodTime           (1 &lt;&lt; 30)
DECL|macro|ZR36057_MCTCR_CEmpty
mdefine_line|#define ZR36057_MCTCR_CEmpty            (1 &lt;&lt; 29)
DECL|macro|ZR36057_MCTCR_CFlush
mdefine_line|#define ZR36057_MCTCR_CFlush            (1 &lt;&lt; 28)
DECL|macro|ZR36057_MCTCR_CodGuestID
mdefine_line|#define ZR36057_MCTCR_CodGuestID&t;20
DECL|macro|ZR36057_MCTCR_CodGuestReg
mdefine_line|#define ZR36057_MCTCR_CodGuestReg&t;16
DECL|macro|ZR36057_MCMPR
mdefine_line|#define ZR36057_MCMPR           0x038&t;/* MPEG Code Memory Pointer Register */
DECL|macro|ZR36057_ISR
mdefine_line|#define ZR36057_ISR             0x03c&t;/* Interrupt Status Register */
DECL|macro|ZR36057_ISR_GIRQ1
mdefine_line|#define ZR36057_ISR_GIRQ1               (1&lt;&lt;30)
DECL|macro|ZR36057_ISR_GIRQ0
mdefine_line|#define ZR36057_ISR_GIRQ0               (1&lt;&lt;29)
DECL|macro|ZR36057_ISR_CodRepIRQ
mdefine_line|#define ZR36057_ISR_CodRepIRQ           (1&lt;&lt;28)
DECL|macro|ZR36057_ISR_JPEGRepIRQ
mdefine_line|#define ZR36057_ISR_JPEGRepIRQ          (1&lt;&lt;27)
DECL|macro|ZR36057_ICR
mdefine_line|#define ZR36057_ICR             0x040&t;/* Interrupt Control Register */
DECL|macro|ZR36057_ICR_GIRQ1
mdefine_line|#define ZR36057_ICR_GIRQ1               (1&lt;&lt;30)
DECL|macro|ZR36057_ICR_GIRQ0
mdefine_line|#define ZR36057_ICR_GIRQ0               (1&lt;&lt;29)
DECL|macro|ZR36057_ICR_CodRepIRQ
mdefine_line|#define ZR36057_ICR_CodRepIRQ           (1&lt;&lt;28)
DECL|macro|ZR36057_ICR_JPEGRepIRQ
mdefine_line|#define ZR36057_ICR_JPEGRepIRQ          (1&lt;&lt;27)
DECL|macro|ZR36057_ICR_IntPinEn
mdefine_line|#define ZR36057_ICR_IntPinEn            (1&lt;&lt;24)
DECL|macro|ZR36057_I2CBR
mdefine_line|#define ZR36057_I2CBR           0x044&t;/* I2C Bus Register */
DECL|macro|ZR36057_I2CBR_SDA
mdefine_line|#define ZR36057_I2CBR_SDA       &t;(1&lt;&lt;1)
DECL|macro|ZR36057_I2CBR_SCL
mdefine_line|#define ZR36057_I2CBR_SCL       &t;(1&lt;&lt;0)
DECL|macro|ZR36057_JMC
mdefine_line|#define ZR36057_JMC             0x100&t;/* JPEG Mode and Control */
DECL|macro|ZR36057_JMC_JPG
mdefine_line|#define ZR36057_JMC_JPG                 (1 &lt;&lt; 31)
DECL|macro|ZR36057_JMC_JPGExpMode
mdefine_line|#define ZR36057_JMC_JPGExpMode          (0 &lt;&lt; 29)
DECL|macro|ZR36057_JMC_JPGCmpMode
mdefine_line|#define ZR36057_JMC_JPGCmpMode          (1 &lt;&lt; 29)
DECL|macro|ZR36057_JMC_MJPGExpMode
mdefine_line|#define ZR36057_JMC_MJPGExpMode         (2 &lt;&lt; 29)
DECL|macro|ZR36057_JMC_MJPGCmpMode
mdefine_line|#define ZR36057_JMC_MJPGCmpMode         (3 &lt;&lt; 29)
DECL|macro|ZR36057_JMC_RTBUSY_FB
mdefine_line|#define ZR36057_JMC_RTBUSY_FB           (1 &lt;&lt; 6)
DECL|macro|ZR36057_JMC_Go_en
mdefine_line|#define ZR36057_JMC_Go_en               (1 &lt;&lt; 5)
DECL|macro|ZR36057_JMC_SyncMstr
mdefine_line|#define ZR36057_JMC_SyncMstr            (1 &lt;&lt; 4)
DECL|macro|ZR36057_JMC_Fld_per_buff
mdefine_line|#define ZR36057_JMC_Fld_per_buff        (1 &lt;&lt; 3)
DECL|macro|ZR36057_JMC_VFIFO_FB
mdefine_line|#define ZR36057_JMC_VFIFO_FB            (1 &lt;&lt; 2)
DECL|macro|ZR36057_JMC_CFIFO_FB
mdefine_line|#define ZR36057_JMC_CFIFO_FB            (1 &lt;&lt; 1)
DECL|macro|ZR36057_JMC_Stll_LitEndian
mdefine_line|#define ZR36057_JMC_Stll_LitEndian      (1 &lt;&lt; 0)
DECL|macro|ZR36057_JPC
mdefine_line|#define ZR36057_JPC             0x104&t;/* JPEG Process Control */
DECL|macro|ZR36057_JPC_P_Reset
mdefine_line|#define ZR36057_JPC_P_Reset             (1 &lt;&lt; 7)
DECL|macro|ZR36057_JPC_CodTrnsEn
mdefine_line|#define ZR36057_JPC_CodTrnsEn           (1 &lt;&lt; 5)
DECL|macro|ZR36057_JPC_Active
mdefine_line|#define ZR36057_JPC_Active              (1 &lt;&lt; 0)
DECL|macro|ZR36057_VSP
mdefine_line|#define ZR36057_VSP             0x108&t;/* Vertical Sync Parameters */
DECL|macro|ZR36057_VSP_VsyncSize
mdefine_line|#define ZR36057_VSP_VsyncSize           16
DECL|macro|ZR36057_VSP_FrmTot
mdefine_line|#define ZR36057_VSP_FrmTot              0
DECL|macro|ZR36057_HSP
mdefine_line|#define ZR36057_HSP             0x10c&t;/* Horizontal Sync Parameters */
DECL|macro|ZR36057_HSP_HsyncStart
mdefine_line|#define ZR36057_HSP_HsyncStart          16
DECL|macro|ZR36057_HSP_LineTot
mdefine_line|#define ZR36057_HSP_LineTot             0
DECL|macro|ZR36057_FHAP
mdefine_line|#define ZR36057_FHAP            0x110&t;/* Field Horizontal Active Portion */
DECL|macro|ZR36057_FHAP_NAX
mdefine_line|#define ZR36057_FHAP_NAX                16
DECL|macro|ZR36057_FHAP_PAX
mdefine_line|#define ZR36057_FHAP_PAX                0
DECL|macro|ZR36057_FVAP
mdefine_line|#define ZR36057_FVAP            0x114&t;/* Field Vertical Active Portion */
DECL|macro|ZR36057_FVAP_NAY
mdefine_line|#define ZR36057_FVAP_NAY                16
DECL|macro|ZR36057_FVAP_PAY
mdefine_line|#define ZR36057_FVAP_PAY                0
DECL|macro|ZR36057_FPP
mdefine_line|#define ZR36057_FPP             0x118&t;/* Field Process Parameters */
DECL|macro|ZR36057_FPP_Odd_Even
mdefine_line|#define ZR36057_FPP_Odd_Even            (1 &lt;&lt; 0)
DECL|macro|ZR36057_JCBA
mdefine_line|#define ZR36057_JCBA            0x11c&t;/* JPEG Code Base Address */
DECL|macro|ZR36057_JCFT
mdefine_line|#define ZR36057_JCFT            0x120&t;/* JPEG Code FIFO Threshold */
DECL|macro|ZR36057_JCGI
mdefine_line|#define ZR36057_JCGI            0x124&t;/* JPEG Codec Guest ID */
DECL|macro|ZR36057_JCGI_JPEGuestID
mdefine_line|#define ZR36057_JCGI_JPEGuestID         4
DECL|macro|ZR36057_JCGI_JPEGuestReg
mdefine_line|#define ZR36057_JCGI_JPEGuestReg        0
DECL|macro|ZR36057_GCR2
mdefine_line|#define ZR36057_GCR2            0x12c&t;/* GuestBus Control Register (2) */
DECL|macro|ZR36057_POR
mdefine_line|#define ZR36057_POR             0x200&t;/* Post Office Register */
DECL|macro|ZR36057_POR_POPen
mdefine_line|#define ZR36057_POR_POPen               (1&lt;&lt;25)
DECL|macro|ZR36057_POR_POTime
mdefine_line|#define ZR36057_POR_POTime              (1&lt;&lt;24)
DECL|macro|ZR36057_POR_PODir
mdefine_line|#define ZR36057_POR_PODir               (1&lt;&lt;23)
DECL|macro|ZR36057_STR
mdefine_line|#define ZR36057_STR             0x300&t;/* &quot;Still&quot; Transfer Register */
macro_line|#endif
eof
