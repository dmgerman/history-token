multiline_comment|/* &n;    bt848.h - Bt848 register offsets&n;&n;    Copyright (C) 1996,97,98 Ralph Metzler (rjkm@thp.uni-koeln.de)&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef _BT848_H_
DECL|macro|_BT848_H_
mdefine_line|#define _BT848_H_
macro_line|#ifndef PCI_VENDOR_ID_BROOKTREE
DECL|macro|PCI_VENDOR_ID_BROOKTREE
mdefine_line|#define PCI_VENDOR_ID_BROOKTREE 0x109e 
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_BT848
DECL|macro|PCI_DEVICE_ID_BT848
mdefine_line|#define PCI_DEVICE_ID_BT848     0x350&t;
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_BT849
DECL|macro|PCI_DEVICE_ID_BT849
mdefine_line|#define PCI_DEVICE_ID_BT849     0x351
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_BT878
DECL|macro|PCI_DEVICE_ID_BT878
mdefine_line|#define PCI_DEVICE_ID_BT878     0x36e
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_BT879
DECL|macro|PCI_DEVICE_ID_BT879
mdefine_line|#define PCI_DEVICE_ID_BT879     0x36f
macro_line|#endif
multiline_comment|/* Brooktree 848 registers */
DECL|macro|BT848_DSTATUS
mdefine_line|#define BT848_DSTATUS          0x000
DECL|macro|BT848_DSTATUS_PRES
mdefine_line|#define BT848_DSTATUS_PRES     (1&lt;&lt;7)
DECL|macro|BT848_DSTATUS_HLOC
mdefine_line|#define BT848_DSTATUS_HLOC     (1&lt;&lt;6)
DECL|macro|BT848_DSTATUS_FIELD
mdefine_line|#define BT848_DSTATUS_FIELD    (1&lt;&lt;5)
DECL|macro|BT848_DSTATUS_NUML
mdefine_line|#define BT848_DSTATUS_NUML     (1&lt;&lt;4)
DECL|macro|BT848_DSTATUS_CSEL
mdefine_line|#define BT848_DSTATUS_CSEL     (1&lt;&lt;3)
DECL|macro|BT848_DSTATUS_PLOCK
mdefine_line|#define BT848_DSTATUS_PLOCK    (1&lt;&lt;2)
DECL|macro|BT848_DSTATUS_LOF
mdefine_line|#define BT848_DSTATUS_LOF      (1&lt;&lt;1)
DECL|macro|BT848_DSTATUS_COF
mdefine_line|#define BT848_DSTATUS_COF      (1&lt;&lt;0)
DECL|macro|BT848_IFORM
mdefine_line|#define BT848_IFORM            0x004  
DECL|macro|BT848_IFORM_HACTIVE
mdefine_line|#define BT848_IFORM_HACTIVE    (1&lt;&lt;7)
DECL|macro|BT848_IFORM_MUXSEL
mdefine_line|#define BT848_IFORM_MUXSEL     (3&lt;&lt;5)
DECL|macro|BT848_IFORM_MUX0
mdefine_line|#define BT848_IFORM_MUX0       (2&lt;&lt;5)
DECL|macro|BT848_IFORM_MUX1
mdefine_line|#define BT848_IFORM_MUX1       (3&lt;&lt;5)
DECL|macro|BT848_IFORM_MUX2
mdefine_line|#define BT848_IFORM_MUX2       (1&lt;&lt;5)
DECL|macro|BT848_IFORM_XTSEL
mdefine_line|#define BT848_IFORM_XTSEL      (3&lt;&lt;3)
DECL|macro|BT848_IFORM_XT0
mdefine_line|#define BT848_IFORM_XT0        (1&lt;&lt;3)
DECL|macro|BT848_IFORM_XT1
mdefine_line|#define BT848_IFORM_XT1        (2&lt;&lt;3)
DECL|macro|BT848_IFORM_XTAUTO
mdefine_line|#define BT848_IFORM_XTAUTO     (3&lt;&lt;3)
DECL|macro|BT848_IFORM_XTBOTH
mdefine_line|#define BT848_IFORM_XTBOTH     (3&lt;&lt;3)
DECL|macro|BT848_IFORM_NTSC
mdefine_line|#define BT848_IFORM_NTSC       1
DECL|macro|BT848_IFORM_NTSC_J
mdefine_line|#define BT848_IFORM_NTSC_J     2
DECL|macro|BT848_IFORM_PAL_BDGHI
mdefine_line|#define BT848_IFORM_PAL_BDGHI  3
DECL|macro|BT848_IFORM_PAL_M
mdefine_line|#define BT848_IFORM_PAL_M      4
DECL|macro|BT848_IFORM_PAL_N
mdefine_line|#define BT848_IFORM_PAL_N      5
DECL|macro|BT848_IFORM_SECAM
mdefine_line|#define BT848_IFORM_SECAM      6
DECL|macro|BT848_IFORM_PAL_NC
mdefine_line|#define BT848_IFORM_PAL_NC     7
DECL|macro|BT848_IFORM_AUTO
mdefine_line|#define BT848_IFORM_AUTO       0
DECL|macro|BT848_IFORM_NORM
mdefine_line|#define BT848_IFORM_NORM       7
DECL|macro|BT848_TDEC
mdefine_line|#define BT848_TDEC             0x008  
DECL|macro|BT848_TDEC_DEC_FIELD
mdefine_line|#define BT848_TDEC_DEC_FIELD   (1&lt;&lt;7)
DECL|macro|BT848_TDEC_FLDALIGN
mdefine_line|#define BT848_TDEC_FLDALIGN    (1&lt;&lt;6)
DECL|macro|BT848_TDEC_DEC_RAT
mdefine_line|#define BT848_TDEC_DEC_RAT     (0x1f)
DECL|macro|BT848_E_CROP
mdefine_line|#define BT848_E_CROP           0x00C
DECL|macro|BT848_O_CROP
mdefine_line|#define BT848_O_CROP           0x08C
DECL|macro|BT848_E_VDELAY_LO
mdefine_line|#define BT848_E_VDELAY_LO      0x010
DECL|macro|BT848_O_VDELAY_LO
mdefine_line|#define BT848_O_VDELAY_LO      0x090
DECL|macro|BT848_E_VACTIVE_LO
mdefine_line|#define BT848_E_VACTIVE_LO     0x014
DECL|macro|BT848_O_VACTIVE_LO
mdefine_line|#define BT848_O_VACTIVE_LO     0x094
DECL|macro|BT848_E_HDELAY_LO
mdefine_line|#define BT848_E_HDELAY_LO      0x018
DECL|macro|BT848_O_HDELAY_LO
mdefine_line|#define BT848_O_HDELAY_LO      0x098
DECL|macro|BT848_E_HACTIVE_LO
mdefine_line|#define BT848_E_HACTIVE_LO     0x01C
DECL|macro|BT848_O_HACTIVE_LO
mdefine_line|#define BT848_O_HACTIVE_LO     0x09C
DECL|macro|BT848_E_HSCALE_HI
mdefine_line|#define BT848_E_HSCALE_HI      0x020
DECL|macro|BT848_O_HSCALE_HI
mdefine_line|#define BT848_O_HSCALE_HI      0x0A0
DECL|macro|BT848_E_HSCALE_LO
mdefine_line|#define BT848_E_HSCALE_LO      0x024
DECL|macro|BT848_O_HSCALE_LO
mdefine_line|#define BT848_O_HSCALE_LO      0x0A4
DECL|macro|BT848_BRIGHT
mdefine_line|#define BT848_BRIGHT           0x028
DECL|macro|BT848_E_CONTROL
mdefine_line|#define BT848_E_CONTROL        0x02C
DECL|macro|BT848_O_CONTROL
mdefine_line|#define BT848_O_CONTROL        0x0AC
DECL|macro|BT848_CONTROL_LNOTCH
mdefine_line|#define BT848_CONTROL_LNOTCH    (1&lt;&lt;7)
DECL|macro|BT848_CONTROL_COMP
mdefine_line|#define BT848_CONTROL_COMP      (1&lt;&lt;6)
DECL|macro|BT848_CONTROL_LDEC
mdefine_line|#define BT848_CONTROL_LDEC      (1&lt;&lt;5)
DECL|macro|BT848_CONTROL_CBSENSE
mdefine_line|#define BT848_CONTROL_CBSENSE   (1&lt;&lt;4)
DECL|macro|BT848_CONTROL_CON_MSB
mdefine_line|#define BT848_CONTROL_CON_MSB   (1&lt;&lt;2)
DECL|macro|BT848_CONTROL_SAT_U_MSB
mdefine_line|#define BT848_CONTROL_SAT_U_MSB (1&lt;&lt;1)
DECL|macro|BT848_CONTROL_SAT_V_MSB
mdefine_line|#define BT848_CONTROL_SAT_V_MSB (1&lt;&lt;0)
DECL|macro|BT848_CONTRAST_LO
mdefine_line|#define BT848_CONTRAST_LO      0x030
DECL|macro|BT848_SAT_U_LO
mdefine_line|#define BT848_SAT_U_LO         0x034
DECL|macro|BT848_SAT_V_LO
mdefine_line|#define BT848_SAT_V_LO         0x038
DECL|macro|BT848_HUE
mdefine_line|#define BT848_HUE              0x03C
DECL|macro|BT848_E_SCLOOP
mdefine_line|#define BT848_E_SCLOOP         0x040
DECL|macro|BT848_O_SCLOOP
mdefine_line|#define BT848_O_SCLOOP         0x0C0
DECL|macro|BT848_SCLOOP_CAGC
mdefine_line|#define BT848_SCLOOP_CAGC       (1&lt;&lt;6)
DECL|macro|BT848_SCLOOP_CKILL
mdefine_line|#define BT848_SCLOOP_CKILL      (1&lt;&lt;5)
DECL|macro|BT848_SCLOOP_HFILT_AUTO
mdefine_line|#define BT848_SCLOOP_HFILT_AUTO (0&lt;&lt;3)
DECL|macro|BT848_SCLOOP_HFILT_CIF
mdefine_line|#define BT848_SCLOOP_HFILT_CIF  (1&lt;&lt;3)
DECL|macro|BT848_SCLOOP_HFILT_QCIF
mdefine_line|#define BT848_SCLOOP_HFILT_QCIF (2&lt;&lt;3)
DECL|macro|BT848_SCLOOP_HFILT_ICON
mdefine_line|#define BT848_SCLOOP_HFILT_ICON (3&lt;&lt;3)
DECL|macro|BT848_SCLOOP_PEAK
mdefine_line|#define BT848_SCLOOP_PEAK       (1&lt;&lt;7)
DECL|macro|BT848_SCLOOP_HFILT_MINP
mdefine_line|#define BT848_SCLOOP_HFILT_MINP (1&lt;&lt;3)
DECL|macro|BT848_SCLOOP_HFILT_MEDP
mdefine_line|#define BT848_SCLOOP_HFILT_MEDP (2&lt;&lt;3)
DECL|macro|BT848_SCLOOP_HFILT_MAXP
mdefine_line|#define BT848_SCLOOP_HFILT_MAXP (3&lt;&lt;3)
DECL|macro|BT848_OFORM
mdefine_line|#define BT848_OFORM            0x048
DECL|macro|BT848_OFORM_RANGE
mdefine_line|#define BT848_OFORM_RANGE      (1&lt;&lt;7)
DECL|macro|BT848_OFORM_CORE0
mdefine_line|#define BT848_OFORM_CORE0      (0&lt;&lt;5)
DECL|macro|BT848_OFORM_CORE8
mdefine_line|#define BT848_OFORM_CORE8      (1&lt;&lt;5)
DECL|macro|BT848_OFORM_CORE16
mdefine_line|#define BT848_OFORM_CORE16     (2&lt;&lt;5)
DECL|macro|BT848_OFORM_CORE32
mdefine_line|#define BT848_OFORM_CORE32     (3&lt;&lt;5)
DECL|macro|BT848_E_VSCALE_HI
mdefine_line|#define BT848_E_VSCALE_HI      0x04C
DECL|macro|BT848_O_VSCALE_HI
mdefine_line|#define BT848_O_VSCALE_HI      0x0CC
DECL|macro|BT848_VSCALE_YCOMB
mdefine_line|#define BT848_VSCALE_YCOMB     (1&lt;&lt;7)
DECL|macro|BT848_VSCALE_COMB
mdefine_line|#define BT848_VSCALE_COMB      (1&lt;&lt;6)
DECL|macro|BT848_VSCALE_INT
mdefine_line|#define BT848_VSCALE_INT       (1&lt;&lt;5)
DECL|macro|BT848_VSCALE_HI
mdefine_line|#define BT848_VSCALE_HI        15
DECL|macro|BT848_E_VSCALE_LO
mdefine_line|#define BT848_E_VSCALE_LO      0x050
DECL|macro|BT848_O_VSCALE_LO
mdefine_line|#define BT848_O_VSCALE_LO      0x0D0
DECL|macro|BT848_TEST
mdefine_line|#define BT848_TEST             0x054
DECL|macro|BT848_ADELAY
mdefine_line|#define BT848_ADELAY           0x060
DECL|macro|BT848_BDELAY
mdefine_line|#define BT848_BDELAY           0x064
DECL|macro|BT848_ADC
mdefine_line|#define BT848_ADC              0x068
DECL|macro|BT848_ADC_RESERVED
mdefine_line|#define BT848_ADC_RESERVED     (2&lt;&lt;6)
DECL|macro|BT848_ADC_SYNC_T
mdefine_line|#define BT848_ADC_SYNC_T       (1&lt;&lt;5)
DECL|macro|BT848_ADC_AGC_EN
mdefine_line|#define BT848_ADC_AGC_EN       (1&lt;&lt;4)
DECL|macro|BT848_ADC_CLK_SLEEP
mdefine_line|#define BT848_ADC_CLK_SLEEP    (1&lt;&lt;3)
DECL|macro|BT848_ADC_Y_SLEEP
mdefine_line|#define BT848_ADC_Y_SLEEP      (1&lt;&lt;2)
DECL|macro|BT848_ADC_C_SLEEP
mdefine_line|#define BT848_ADC_C_SLEEP      (1&lt;&lt;1)
DECL|macro|BT848_ADC_CRUSH
mdefine_line|#define BT848_ADC_CRUSH        (1&lt;&lt;0)
DECL|macro|BT848_E_VTC
mdefine_line|#define BT848_E_VTC            0x06C
DECL|macro|BT848_O_VTC
mdefine_line|#define BT848_O_VTC            0x0EC
DECL|macro|BT848_VTC_HSFMT
mdefine_line|#define BT848_VTC_HSFMT        (1&lt;&lt;7)
DECL|macro|BT848_VTC_VFILT_2TAP
mdefine_line|#define BT848_VTC_VFILT_2TAP   0
DECL|macro|BT848_VTC_VFILT_3TAP
mdefine_line|#define BT848_VTC_VFILT_3TAP   1
DECL|macro|BT848_VTC_VFILT_4TAP
mdefine_line|#define BT848_VTC_VFILT_4TAP   2
DECL|macro|BT848_VTC_VFILT_5TAP
mdefine_line|#define BT848_VTC_VFILT_5TAP   3
DECL|macro|BT848_SRESET
mdefine_line|#define BT848_SRESET           0x07C
DECL|macro|BT848_COLOR_FMT
mdefine_line|#define BT848_COLOR_FMT             0x0D4
DECL|macro|BT848_COLOR_FMT_O_RGB32
mdefine_line|#define BT848_COLOR_FMT_O_RGB32     (0&lt;&lt;4)
DECL|macro|BT848_COLOR_FMT_O_RGB24
mdefine_line|#define BT848_COLOR_FMT_O_RGB24     (1&lt;&lt;4)
DECL|macro|BT848_COLOR_FMT_O_RGB16
mdefine_line|#define BT848_COLOR_FMT_O_RGB16     (2&lt;&lt;4)
DECL|macro|BT848_COLOR_FMT_O_RGB15
mdefine_line|#define BT848_COLOR_FMT_O_RGB15     (3&lt;&lt;4)
DECL|macro|BT848_COLOR_FMT_O_YUY2
mdefine_line|#define BT848_COLOR_FMT_O_YUY2      (4&lt;&lt;4)
DECL|macro|BT848_COLOR_FMT_O_BtYUV
mdefine_line|#define BT848_COLOR_FMT_O_BtYUV     (5&lt;&lt;4)
DECL|macro|BT848_COLOR_FMT_O_Y8
mdefine_line|#define BT848_COLOR_FMT_O_Y8        (6&lt;&lt;4)
DECL|macro|BT848_COLOR_FMT_O_RGB8
mdefine_line|#define BT848_COLOR_FMT_O_RGB8      (7&lt;&lt;4)
DECL|macro|BT848_COLOR_FMT_O_YCrCb422
mdefine_line|#define BT848_COLOR_FMT_O_YCrCb422  (8&lt;&lt;4)
DECL|macro|BT848_COLOR_FMT_O_YCrCb411
mdefine_line|#define BT848_COLOR_FMT_O_YCrCb411  (9&lt;&lt;4)
DECL|macro|BT848_COLOR_FMT_O_RAW
mdefine_line|#define BT848_COLOR_FMT_O_RAW       (14&lt;&lt;4)
DECL|macro|BT848_COLOR_FMT_E_RGB32
mdefine_line|#define BT848_COLOR_FMT_E_RGB32     0
DECL|macro|BT848_COLOR_FMT_E_RGB24
mdefine_line|#define BT848_COLOR_FMT_E_RGB24     1
DECL|macro|BT848_COLOR_FMT_E_RGB16
mdefine_line|#define BT848_COLOR_FMT_E_RGB16     2
DECL|macro|BT848_COLOR_FMT_E_RGB15
mdefine_line|#define BT848_COLOR_FMT_E_RGB15     3
DECL|macro|BT848_COLOR_FMT_E_YUY2
mdefine_line|#define BT848_COLOR_FMT_E_YUY2      4
DECL|macro|BT848_COLOR_FMT_E_BtYUV
mdefine_line|#define BT848_COLOR_FMT_E_BtYUV     5
DECL|macro|BT848_COLOR_FMT_E_Y8
mdefine_line|#define BT848_COLOR_FMT_E_Y8        6
DECL|macro|BT848_COLOR_FMT_E_RGB8
mdefine_line|#define BT848_COLOR_FMT_E_RGB8      7
DECL|macro|BT848_COLOR_FMT_E_YCrCb422
mdefine_line|#define BT848_COLOR_FMT_E_YCrCb422  8
DECL|macro|BT848_COLOR_FMT_E_YCrCb411
mdefine_line|#define BT848_COLOR_FMT_E_YCrCb411  9
DECL|macro|BT848_COLOR_FMT_E_RAW
mdefine_line|#define BT848_COLOR_FMT_E_RAW       14
DECL|macro|BT848_COLOR_FMT_RGB32
mdefine_line|#define BT848_COLOR_FMT_RGB32       0x00
DECL|macro|BT848_COLOR_FMT_RGB24
mdefine_line|#define BT848_COLOR_FMT_RGB24       0x11
DECL|macro|BT848_COLOR_FMT_RGB16
mdefine_line|#define BT848_COLOR_FMT_RGB16       0x22
DECL|macro|BT848_COLOR_FMT_RGB15
mdefine_line|#define BT848_COLOR_FMT_RGB15       0x33
DECL|macro|BT848_COLOR_FMT_YUY2
mdefine_line|#define BT848_COLOR_FMT_YUY2        0x44
DECL|macro|BT848_COLOR_FMT_BtYUV
mdefine_line|#define BT848_COLOR_FMT_BtYUV       0x55
DECL|macro|BT848_COLOR_FMT_Y8
mdefine_line|#define BT848_COLOR_FMT_Y8          0x66
DECL|macro|BT848_COLOR_FMT_RGB8
mdefine_line|#define BT848_COLOR_FMT_RGB8        0x77
DECL|macro|BT848_COLOR_FMT_YCrCb422
mdefine_line|#define BT848_COLOR_FMT_YCrCb422    0x88
DECL|macro|BT848_COLOR_FMT_YCrCb411
mdefine_line|#define BT848_COLOR_FMT_YCrCb411    0x99
DECL|macro|BT848_COLOR_FMT_RAW
mdefine_line|#define BT848_COLOR_FMT_RAW         0xee
DECL|macro|BT848_COLOR_CTL
mdefine_line|#define BT848_COLOR_CTL                0x0D8
DECL|macro|BT848_COLOR_CTL_EXT_FRMRATE
mdefine_line|#define BT848_COLOR_CTL_EXT_FRMRATE    (1&lt;&lt;7)
DECL|macro|BT848_COLOR_CTL_COLOR_BARS
mdefine_line|#define BT848_COLOR_CTL_COLOR_BARS     (1&lt;&lt;6)
DECL|macro|BT848_COLOR_CTL_RGB_DED
mdefine_line|#define BT848_COLOR_CTL_RGB_DED        (1&lt;&lt;5)
DECL|macro|BT848_COLOR_CTL_GAMMA
mdefine_line|#define BT848_COLOR_CTL_GAMMA          (1&lt;&lt;4)
DECL|macro|BT848_COLOR_CTL_WSWAP_ODD
mdefine_line|#define BT848_COLOR_CTL_WSWAP_ODD      (1&lt;&lt;3)
DECL|macro|BT848_COLOR_CTL_WSWAP_EVEN
mdefine_line|#define BT848_COLOR_CTL_WSWAP_EVEN     (1&lt;&lt;2)
DECL|macro|BT848_COLOR_CTL_BSWAP_ODD
mdefine_line|#define BT848_COLOR_CTL_BSWAP_ODD      (1&lt;&lt;1)
DECL|macro|BT848_COLOR_CTL_BSWAP_EVEN
mdefine_line|#define BT848_COLOR_CTL_BSWAP_EVEN     (1&lt;&lt;0)
DECL|macro|BT848_CAP_CTL
mdefine_line|#define BT848_CAP_CTL                  0x0DC
DECL|macro|BT848_CAP_CTL_DITH_FRAME
mdefine_line|#define BT848_CAP_CTL_DITH_FRAME       (1&lt;&lt;4)
DECL|macro|BT848_CAP_CTL_CAPTURE_VBI_ODD
mdefine_line|#define BT848_CAP_CTL_CAPTURE_VBI_ODD  (1&lt;&lt;3)
DECL|macro|BT848_CAP_CTL_CAPTURE_VBI_EVEN
mdefine_line|#define BT848_CAP_CTL_CAPTURE_VBI_EVEN (1&lt;&lt;2)
DECL|macro|BT848_CAP_CTL_CAPTURE_ODD
mdefine_line|#define BT848_CAP_CTL_CAPTURE_ODD      (1&lt;&lt;1)
DECL|macro|BT848_CAP_CTL_CAPTURE_EVEN
mdefine_line|#define BT848_CAP_CTL_CAPTURE_EVEN     (1&lt;&lt;0)
DECL|macro|BT848_VBI_PACK_SIZE
mdefine_line|#define BT848_VBI_PACK_SIZE    0x0E0
DECL|macro|BT848_VBI_PACK_DEL
mdefine_line|#define BT848_VBI_PACK_DEL     0x0E4
DECL|macro|BT848_VBI_PACK_DEL_VBI_HDELAY
mdefine_line|#define BT848_VBI_PACK_DEL_VBI_HDELAY 0xfc
DECL|macro|BT848_VBI_PACK_DEL_EXT_FRAME
mdefine_line|#define BT848_VBI_PACK_DEL_EXT_FRAME  2
DECL|macro|BT848_VBI_PACK_DEL_VBI_PKT_HI
mdefine_line|#define BT848_VBI_PACK_DEL_VBI_PKT_HI 1
DECL|macro|BT848_INT_STAT
mdefine_line|#define BT848_INT_STAT         0x100
DECL|macro|BT848_INT_MASK
mdefine_line|#define BT848_INT_MASK         0x104
DECL|macro|BT848_INT_ETBF
mdefine_line|#define BT848_INT_ETBF         (1&lt;&lt;23)
DECL|macro|BT848_INT_RISCS
mdefine_line|#define BT848_INT_RISCS   (0xf&lt;&lt;28)
DECL|macro|BT848_INT_RISC_EN
mdefine_line|#define BT848_INT_RISC_EN (1&lt;&lt;27)
DECL|macro|BT848_INT_RACK
mdefine_line|#define BT848_INT_RACK    (1&lt;&lt;25)
DECL|macro|BT848_INT_FIELD
mdefine_line|#define BT848_INT_FIELD   (1&lt;&lt;24)
DECL|macro|BT848_INT_SCERR
mdefine_line|#define BT848_INT_SCERR   (1&lt;&lt;19)
DECL|macro|BT848_INT_OCERR
mdefine_line|#define BT848_INT_OCERR   (1&lt;&lt;18)
DECL|macro|BT848_INT_PABORT
mdefine_line|#define BT848_INT_PABORT  (1&lt;&lt;17)
DECL|macro|BT848_INT_RIPERR
mdefine_line|#define BT848_INT_RIPERR  (1&lt;&lt;16)
DECL|macro|BT848_INT_PPERR
mdefine_line|#define BT848_INT_PPERR   (1&lt;&lt;15)
DECL|macro|BT848_INT_FDSR
mdefine_line|#define BT848_INT_FDSR    (1&lt;&lt;14)
DECL|macro|BT848_INT_FTRGT
mdefine_line|#define BT848_INT_FTRGT   (1&lt;&lt;13)
DECL|macro|BT848_INT_FBUS
mdefine_line|#define BT848_INT_FBUS    (1&lt;&lt;12)
DECL|macro|BT848_INT_RISCI
mdefine_line|#define BT848_INT_RISCI   (1&lt;&lt;11)
DECL|macro|BT848_INT_GPINT
mdefine_line|#define BT848_INT_GPINT   (1&lt;&lt;9)
DECL|macro|BT848_INT_I2CDONE
mdefine_line|#define BT848_INT_I2CDONE (1&lt;&lt;8)
DECL|macro|BT848_INT_VPRES
mdefine_line|#define BT848_INT_VPRES   (1&lt;&lt;5)
DECL|macro|BT848_INT_HLOCK
mdefine_line|#define BT848_INT_HLOCK   (1&lt;&lt;4)
DECL|macro|BT848_INT_OFLOW
mdefine_line|#define BT848_INT_OFLOW   (1&lt;&lt;3)
DECL|macro|BT848_INT_HSYNC
mdefine_line|#define BT848_INT_HSYNC   (1&lt;&lt;2)
DECL|macro|BT848_INT_VSYNC
mdefine_line|#define BT848_INT_VSYNC   (1&lt;&lt;1)
DECL|macro|BT848_INT_FMTCHG
mdefine_line|#define BT848_INT_FMTCHG  (1&lt;&lt;0)
DECL|macro|BT848_GPIO_DMA_CTL
mdefine_line|#define BT848_GPIO_DMA_CTL             0x10C
DECL|macro|BT848_GPIO_DMA_CTL_GPINTC
mdefine_line|#define BT848_GPIO_DMA_CTL_GPINTC      (1&lt;&lt;15)
DECL|macro|BT848_GPIO_DMA_CTL_GPINTI
mdefine_line|#define BT848_GPIO_DMA_CTL_GPINTI      (1&lt;&lt;14)
DECL|macro|BT848_GPIO_DMA_CTL_GPWEC
mdefine_line|#define BT848_GPIO_DMA_CTL_GPWEC       (1&lt;&lt;13)
DECL|macro|BT848_GPIO_DMA_CTL_GPIOMODE
mdefine_line|#define BT848_GPIO_DMA_CTL_GPIOMODE    (3&lt;&lt;11)
DECL|macro|BT848_GPIO_DMA_CTL_GPCLKMODE
mdefine_line|#define BT848_GPIO_DMA_CTL_GPCLKMODE   (1&lt;&lt;10)
DECL|macro|BT848_GPIO_DMA_CTL_PLTP23_4
mdefine_line|#define BT848_GPIO_DMA_CTL_PLTP23_4    (0&lt;&lt;6)
DECL|macro|BT848_GPIO_DMA_CTL_PLTP23_8
mdefine_line|#define BT848_GPIO_DMA_CTL_PLTP23_8    (1&lt;&lt;6)
DECL|macro|BT848_GPIO_DMA_CTL_PLTP23_16
mdefine_line|#define BT848_GPIO_DMA_CTL_PLTP23_16   (2&lt;&lt;6)
DECL|macro|BT848_GPIO_DMA_CTL_PLTP23_32
mdefine_line|#define BT848_GPIO_DMA_CTL_PLTP23_32   (3&lt;&lt;6)
DECL|macro|BT848_GPIO_DMA_CTL_PLTP1_4
mdefine_line|#define BT848_GPIO_DMA_CTL_PLTP1_4     (0&lt;&lt;4)
DECL|macro|BT848_GPIO_DMA_CTL_PLTP1_8
mdefine_line|#define BT848_GPIO_DMA_CTL_PLTP1_8     (1&lt;&lt;4)
DECL|macro|BT848_GPIO_DMA_CTL_PLTP1_16
mdefine_line|#define BT848_GPIO_DMA_CTL_PLTP1_16    (2&lt;&lt;4)
DECL|macro|BT848_GPIO_DMA_CTL_PLTP1_32
mdefine_line|#define BT848_GPIO_DMA_CTL_PLTP1_32    (3&lt;&lt;4)
DECL|macro|BT848_GPIO_DMA_CTL_PKTP_4
mdefine_line|#define BT848_GPIO_DMA_CTL_PKTP_4      (0&lt;&lt;2)
DECL|macro|BT848_GPIO_DMA_CTL_PKTP_8
mdefine_line|#define BT848_GPIO_DMA_CTL_PKTP_8      (1&lt;&lt;2)
DECL|macro|BT848_GPIO_DMA_CTL_PKTP_16
mdefine_line|#define BT848_GPIO_DMA_CTL_PKTP_16     (2&lt;&lt;2)
DECL|macro|BT848_GPIO_DMA_CTL_PKTP_32
mdefine_line|#define BT848_GPIO_DMA_CTL_PKTP_32     (3&lt;&lt;2)
DECL|macro|BT848_GPIO_DMA_CTL_RISC_ENABLE
mdefine_line|#define BT848_GPIO_DMA_CTL_RISC_ENABLE (1&lt;&lt;1)
DECL|macro|BT848_GPIO_DMA_CTL_FIFO_ENABLE
mdefine_line|#define BT848_GPIO_DMA_CTL_FIFO_ENABLE (1&lt;&lt;0)
DECL|macro|BT848_I2C
mdefine_line|#define BT848_I2C              0x110
DECL|macro|BT848_I2C_DIV
mdefine_line|#define BT848_I2C_DIV          (0xf&lt;&lt;4)
DECL|macro|BT848_I2C_SYNC
mdefine_line|#define BT848_I2C_SYNC         (1&lt;&lt;3)
DECL|macro|BT848_I2C_W3B
mdefine_line|#define BT848_I2C_W3B&t;       (1&lt;&lt;2)
DECL|macro|BT848_I2C_SCL
mdefine_line|#define BT848_I2C_SCL          (1&lt;&lt;1)
DECL|macro|BT848_I2C_SDA
mdefine_line|#define BT848_I2C_SDA          (1&lt;&lt;0)
DECL|macro|BT848_RISC_STRT_ADD
mdefine_line|#define BT848_RISC_STRT_ADD    0x114
DECL|macro|BT848_GPIO_OUT_EN
mdefine_line|#define BT848_GPIO_OUT_EN      0x118
DECL|macro|BT848_GPIO_REG_INP
mdefine_line|#define BT848_GPIO_REG_INP     0x11C
DECL|macro|BT848_RISC_COUNT
mdefine_line|#define BT848_RISC_COUNT       0x120
DECL|macro|BT848_GPIO_DATA
mdefine_line|#define BT848_GPIO_DATA        0x200
multiline_comment|/* Bt848 RISC commands */
multiline_comment|/* only for the SYNC RISC command */
DECL|macro|BT848_FIFO_STATUS_FM1
mdefine_line|#define BT848_FIFO_STATUS_FM1  0x06
DECL|macro|BT848_FIFO_STATUS_FM3
mdefine_line|#define BT848_FIFO_STATUS_FM3  0x0e
DECL|macro|BT848_FIFO_STATUS_SOL
mdefine_line|#define BT848_FIFO_STATUS_SOL  0x02
DECL|macro|BT848_FIFO_STATUS_EOL4
mdefine_line|#define BT848_FIFO_STATUS_EOL4 0x01
DECL|macro|BT848_FIFO_STATUS_EOL3
mdefine_line|#define BT848_FIFO_STATUS_EOL3 0x0d
DECL|macro|BT848_FIFO_STATUS_EOL2
mdefine_line|#define BT848_FIFO_STATUS_EOL2 0x09
DECL|macro|BT848_FIFO_STATUS_EOL1
mdefine_line|#define BT848_FIFO_STATUS_EOL1 0x05
DECL|macro|BT848_FIFO_STATUS_VRE
mdefine_line|#define BT848_FIFO_STATUS_VRE  0x04
DECL|macro|BT848_FIFO_STATUS_VRO
mdefine_line|#define BT848_FIFO_STATUS_VRO  0x0c
DECL|macro|BT848_FIFO_STATUS_PXV
mdefine_line|#define BT848_FIFO_STATUS_PXV  0x00
DECL|macro|BT848_RISC_RESYNC
mdefine_line|#define BT848_RISC_RESYNC      (1&lt;&lt;15)
multiline_comment|/* WRITE and SKIP */
multiline_comment|/* disable which bytes of each DWORD */
DECL|macro|BT848_RISC_BYTE0
mdefine_line|#define BT848_RISC_BYTE0       (1&lt;&lt;12)
DECL|macro|BT848_RISC_BYTE1
mdefine_line|#define BT848_RISC_BYTE1       (1&lt;&lt;13)
DECL|macro|BT848_RISC_BYTE2
mdefine_line|#define BT848_RISC_BYTE2       (1&lt;&lt;14)
DECL|macro|BT848_RISC_BYTE3
mdefine_line|#define BT848_RISC_BYTE3       (1&lt;&lt;15)
DECL|macro|BT848_RISC_BYTE_ALL
mdefine_line|#define BT848_RISC_BYTE_ALL    (0x0f&lt;&lt;12)
DECL|macro|BT848_RISC_BYTE_NONE
mdefine_line|#define BT848_RISC_BYTE_NONE   0
multiline_comment|/* cause RISCI */
DECL|macro|BT848_RISC_IRQ
mdefine_line|#define BT848_RISC_IRQ         (1&lt;&lt;24)
multiline_comment|/* RISC command is last one in this line */
DECL|macro|BT848_RISC_EOL
mdefine_line|#define BT848_RISC_EOL         (1&lt;&lt;26)
multiline_comment|/* RISC command is first one in this line */
DECL|macro|BT848_RISC_SOL
mdefine_line|#define BT848_RISC_SOL         (1&lt;&lt;27)
DECL|macro|BT848_RISC_WRITE
mdefine_line|#define BT848_RISC_WRITE       (0x01&lt;&lt;28)
DECL|macro|BT848_RISC_SKIP
mdefine_line|#define BT848_RISC_SKIP        (0x02&lt;&lt;28)
DECL|macro|BT848_RISC_WRITEC
mdefine_line|#define BT848_RISC_WRITEC      (0x05&lt;&lt;28)
DECL|macro|BT848_RISC_JUMP
mdefine_line|#define BT848_RISC_JUMP        (0x07&lt;&lt;28)
DECL|macro|BT848_RISC_SYNC
mdefine_line|#define BT848_RISC_SYNC        (0x08&lt;&lt;28)
DECL|macro|BT848_RISC_WRITE123
mdefine_line|#define BT848_RISC_WRITE123    (0x09&lt;&lt;28)
DECL|macro|BT848_RISC_SKIP123
mdefine_line|#define BT848_RISC_SKIP123     (0x0a&lt;&lt;28)
DECL|macro|BT848_RISC_WRITE1S23
mdefine_line|#define BT848_RISC_WRITE1S23   (0x0b&lt;&lt;28)
multiline_comment|/* Bt848A and higher only !! */
DECL|macro|BT848_TGLB
mdefine_line|#define BT848_TGLB             0x080
DECL|macro|BT848_TGCTRL
mdefine_line|#define BT848_TGCTRL           0x084
DECL|macro|BT848_FCAP
mdefine_line|#define BT848_FCAP             0x0E8
DECL|macro|BT848_PLL_F_LO
mdefine_line|#define BT848_PLL_F_LO         0x0F0
DECL|macro|BT848_PLL_F_HI
mdefine_line|#define BT848_PLL_F_HI         0x0F4
DECL|macro|BT848_PLL_XCI
mdefine_line|#define BT848_PLL_XCI          0x0F8
DECL|macro|BT848_PLL_X
mdefine_line|#define BT848_PLL_X            (1&lt;&lt;7)
DECL|macro|BT848_PLL_C
mdefine_line|#define BT848_PLL_C            (1&lt;&lt;6)
multiline_comment|/* Bt878 register */
DECL|macro|BT878_DEVCTRL
mdefine_line|#define BT878_DEVCTRL 0x40
DECL|macro|BT878_EN_TBFX
mdefine_line|#define BT878_EN_TBFX 0x02
macro_line|#endif
eof
