multiline_comment|/*&n;    $Id: cx88-reg.h,v 1.6 2004/10/13 10:39:00 kraxel Exp $&n;&n;    cx88x-hw.h - CX2388x register offsets&n;&n;    Copyright (C) 1996,97,98 Ralph Metzler (rjkm@thp.uni-koeln.de)&n;                  2001 Michael Eskin&n;                  2002 Yurij Sysoev &lt;yurij@naturesoft.net&gt;&n;                  2003 Gerd Knorr &lt;kraxel@bytesex.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef _CX88_REG_H_
DECL|macro|_CX88_REG_H_
mdefine_line|#define _CX88_REG_H_
multiline_comment|/* ---------------------------------------------------------------------- */
multiline_comment|/* PCI IDs and config space                                               */
macro_line|#ifndef PCI_VENDOR_ID_CONEXANT
DECL|macro|PCI_VENDOR_ID_CONEXANT
macro_line|# define PCI_VENDOR_ID_CONEXANT&t;&t;0x14F1
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_CX2300_VID
DECL|macro|PCI_DEVICE_ID_CX2300_VID
macro_line|# define PCI_DEVICE_ID_CX2300_VID&t;0x8800
macro_line|#endif
DECL|macro|CX88X_DEVCTRL
mdefine_line|#define CX88X_DEVCTRL 0x40
DECL|macro|CX88X_EN_TBFX
mdefine_line|#define CX88X_EN_TBFX 0x02
DECL|macro|CX88X_EN_VSFX
mdefine_line|#define CX88X_EN_VSFX 0x04
multiline_comment|/* ---------------------------------------------------------------------- */
multiline_comment|/* DMA Controller registers                                               */
DECL|macro|MO_PDMA_STHRSH
mdefine_line|#define MO_PDMA_STHRSH      0x200000 
singleline_comment|// Source threshold
DECL|macro|MO_PDMA_STADRS
mdefine_line|#define MO_PDMA_STADRS      0x200004 
singleline_comment|// Source target address
DECL|macro|MO_PDMA_SIADRS
mdefine_line|#define MO_PDMA_SIADRS      0x200008 
singleline_comment|// Source internal address
DECL|macro|MO_PDMA_SCNTRL
mdefine_line|#define MO_PDMA_SCNTRL      0x20000C 
singleline_comment|// Source control
DECL|macro|MO_PDMA_DTHRSH
mdefine_line|#define MO_PDMA_DTHRSH      0x200010 
singleline_comment|// Destination threshold
DECL|macro|MO_PDMA_DTADRS
mdefine_line|#define MO_PDMA_DTADRS      0x200014 
singleline_comment|// Destination target address
DECL|macro|MO_PDMA_DIADRS
mdefine_line|#define MO_PDMA_DIADRS      0x200018 
singleline_comment|// Destination internal address
DECL|macro|MO_PDMA_DCNTRL
mdefine_line|#define MO_PDMA_DCNTRL      0x20001C 
singleline_comment|// Destination control
DECL|macro|MO_LD_SSID
mdefine_line|#define MO_LD_SSID          0x200030 
singleline_comment|// Load subsystem ID
DECL|macro|MO_DEV_CNTRL2
mdefine_line|#define MO_DEV_CNTRL2       0x200034 
singleline_comment|// Device control
DECL|macro|MO_PCI_INTMSK
mdefine_line|#define MO_PCI_INTMSK       0x200040 
singleline_comment|// PCI interrupt mask
DECL|macro|MO_PCI_INTSTAT
mdefine_line|#define MO_PCI_INTSTAT      0x200044 
singleline_comment|// PCI interrupt status
DECL|macro|MO_PCI_INTMSTAT
mdefine_line|#define MO_PCI_INTMSTAT     0x200048 
singleline_comment|// PCI interrupt masked status
DECL|macro|MO_VID_INTMSK
mdefine_line|#define MO_VID_INTMSK       0x200050 
singleline_comment|// Video interrupt mask
DECL|macro|MO_VID_INTSTAT
mdefine_line|#define MO_VID_INTSTAT      0x200054 
singleline_comment|// Video interrupt status
DECL|macro|MO_VID_INTMSTAT
mdefine_line|#define MO_VID_INTMSTAT     0x200058 
singleline_comment|// Video interrupt masked status
DECL|macro|MO_VID_INTSSTAT
mdefine_line|#define MO_VID_INTSSTAT     0x20005C 
singleline_comment|// Video interrupt set status
DECL|macro|MO_AUD_INTMSK
mdefine_line|#define MO_AUD_INTMSK       0x200060 
singleline_comment|// Audio interrupt mask
DECL|macro|MO_AUD_INTSTAT
mdefine_line|#define MO_AUD_INTSTAT      0x200064 
singleline_comment|// Audio interrupt status
DECL|macro|MO_AUD_INTMSTAT
mdefine_line|#define MO_AUD_INTMSTAT     0x200068 
singleline_comment|// Audio interrupt masked status
DECL|macro|MO_AUD_INTSSTAT
mdefine_line|#define MO_AUD_INTSSTAT     0x20006C 
singleline_comment|// Audio interrupt set status
DECL|macro|MO_TS_INTMSK
mdefine_line|#define MO_TS_INTMSK        0x200070 
singleline_comment|// Transport stream interrupt mask
DECL|macro|MO_TS_INTSTAT
mdefine_line|#define MO_TS_INTSTAT       0x200074 
singleline_comment|// Transport stream interrupt status
DECL|macro|MO_TS_INTMSTAT
mdefine_line|#define MO_TS_INTMSTAT      0x200078 
singleline_comment|// Transport stream interrupt mask status
DECL|macro|MO_TS_INTSSTAT
mdefine_line|#define MO_TS_INTSSTAT      0x20007C 
singleline_comment|// Transport stream interrupt set status
DECL|macro|MO_VIP_INTMSK
mdefine_line|#define MO_VIP_INTMSK       0x200080 
singleline_comment|// VIP interrupt mask
DECL|macro|MO_VIP_INTSTAT
mdefine_line|#define MO_VIP_INTSTAT      0x200084 
singleline_comment|// VIP interrupt status
DECL|macro|MO_VIP_INTMSTAT
mdefine_line|#define MO_VIP_INTMSTAT     0x200088 
singleline_comment|// VIP interrupt masked status
DECL|macro|MO_VIP_INTSSTAT
mdefine_line|#define MO_VIP_INTSSTAT     0x20008C 
singleline_comment|// VIP interrupt set status
DECL|macro|MO_GPHST_INTMSK
mdefine_line|#define MO_GPHST_INTMSK     0x200090 
singleline_comment|// Host interrupt mask
DECL|macro|MO_GPHST_INTSTAT
mdefine_line|#define MO_GPHST_INTSTAT    0x200094 
singleline_comment|// Host interrupt status
DECL|macro|MO_GPHST_INTMSTAT
mdefine_line|#define MO_GPHST_INTMSTAT   0x200098 
singleline_comment|// Host interrupt masked status
DECL|macro|MO_GPHST_INTSSTAT
mdefine_line|#define MO_GPHST_INTSSTAT   0x20009C 
singleline_comment|// Host interrupt set status
singleline_comment|// DMA Channels 1-6 belong to SPIPE
DECL|macro|MO_DMA7_PTR1
mdefine_line|#define MO_DMA7_PTR1        0x300018 
singleline_comment|// {24}RW* DMA Current Ptr : Ch#7
DECL|macro|MO_DMA8_PTR1
mdefine_line|#define MO_DMA8_PTR1        0x30001C 
singleline_comment|// {24}RW* DMA Current Ptr : Ch#8
singleline_comment|// DMA Channels 9-20 belong to SPIPE
DECL|macro|MO_DMA21_PTR1
mdefine_line|#define MO_DMA21_PTR1       0x300080 
singleline_comment|// {24}R0* DMA Current Ptr : Ch#21
DECL|macro|MO_DMA22_PTR1
mdefine_line|#define MO_DMA22_PTR1       0x300084 
singleline_comment|// {24}R0* DMA Current Ptr : Ch#22
DECL|macro|MO_DMA23_PTR1
mdefine_line|#define MO_DMA23_PTR1       0x300088 
singleline_comment|// {24}R0* DMA Current Ptr : Ch#23
DECL|macro|MO_DMA24_PTR1
mdefine_line|#define MO_DMA24_PTR1       0x30008C 
singleline_comment|// {24}R0* DMA Current Ptr : Ch#24
DECL|macro|MO_DMA25_PTR1
mdefine_line|#define MO_DMA25_PTR1       0x300090 
singleline_comment|// {24}R0* DMA Current Ptr : Ch#25
DECL|macro|MO_DMA26_PTR1
mdefine_line|#define MO_DMA26_PTR1       0x300094 
singleline_comment|// {24}R0* DMA Current Ptr : Ch#26
DECL|macro|MO_DMA27_PTR1
mdefine_line|#define MO_DMA27_PTR1       0x300098 
singleline_comment|// {24}R0* DMA Current Ptr : Ch#27
DECL|macro|MO_DMA28_PTR1
mdefine_line|#define MO_DMA28_PTR1       0x30009C 
singleline_comment|// {24}R0* DMA Current Ptr : Ch#28
DECL|macro|MO_DMA29_PTR1
mdefine_line|#define MO_DMA29_PTR1       0x3000A0 
singleline_comment|// {24}R0* DMA Current Ptr : Ch#29
DECL|macro|MO_DMA30_PTR1
mdefine_line|#define MO_DMA30_PTR1       0x3000A4 
singleline_comment|// {24}R0* DMA Current Ptr : Ch#30
DECL|macro|MO_DMA31_PTR1
mdefine_line|#define MO_DMA31_PTR1       0x3000A8 
singleline_comment|// {24}R0* DMA Current Ptr : Ch#31
DECL|macro|MO_DMA32_PTR1
mdefine_line|#define MO_DMA32_PTR1       0x3000AC 
singleline_comment|// {24}R0* DMA Current Ptr : Ch#32
DECL|macro|MO_DMA21_PTR2
mdefine_line|#define MO_DMA21_PTR2       0x3000C0 
singleline_comment|// {24}RW* DMA Tab Ptr : Ch#21
DECL|macro|MO_DMA22_PTR2
mdefine_line|#define MO_DMA22_PTR2       0x3000C4 
singleline_comment|// {24}RW* DMA Tab Ptr : Ch#22
DECL|macro|MO_DMA23_PTR2
mdefine_line|#define MO_DMA23_PTR2       0x3000C8 
singleline_comment|// {24}RW* DMA Tab Ptr : Ch#23
DECL|macro|MO_DMA24_PTR2
mdefine_line|#define MO_DMA24_PTR2       0x3000CC 
singleline_comment|// {24}RW* DMA Tab Ptr : Ch#24
DECL|macro|MO_DMA25_PTR2
mdefine_line|#define MO_DMA25_PTR2       0x3000D0 
singleline_comment|// {24}RW* DMA Tab Ptr : Ch#25
DECL|macro|MO_DMA26_PTR2
mdefine_line|#define MO_DMA26_PTR2       0x3000D4 
singleline_comment|// {24}RW* DMA Tab Ptr : Ch#26
DECL|macro|MO_DMA27_PTR2
mdefine_line|#define MO_DMA27_PTR2       0x3000D8 
singleline_comment|// {24}RW* DMA Tab Ptr : Ch#27
DECL|macro|MO_DMA28_PTR2
mdefine_line|#define MO_DMA28_PTR2       0x3000DC 
singleline_comment|// {24}RW* DMA Tab Ptr : Ch#28
DECL|macro|MO_DMA29_PTR2
mdefine_line|#define MO_DMA29_PTR2       0x3000E0 
singleline_comment|// {24}RW* DMA Tab Ptr : Ch#29
DECL|macro|MO_DMA30_PTR2
mdefine_line|#define MO_DMA30_PTR2       0x3000E4 
singleline_comment|// {24}RW* DMA Tab Ptr : Ch#30
DECL|macro|MO_DMA31_PTR2
mdefine_line|#define MO_DMA31_PTR2       0x3000E8 
singleline_comment|// {24}RW* DMA Tab Ptr : Ch#31
DECL|macro|MO_DMA32_PTR2
mdefine_line|#define MO_DMA32_PTR2       0x3000EC 
singleline_comment|// {24}RW* DMA Tab Ptr : Ch#32
DECL|macro|MO_DMA21_CNT1
mdefine_line|#define MO_DMA21_CNT1       0x300100 
singleline_comment|// {11}RW* DMA Buffer Size : Ch#21
DECL|macro|MO_DMA22_CNT1
mdefine_line|#define MO_DMA22_CNT1       0x300104 
singleline_comment|// {11}RW* DMA Buffer Size : Ch#22
DECL|macro|MO_DMA23_CNT1
mdefine_line|#define MO_DMA23_CNT1       0x300108 
singleline_comment|// {11}RW* DMA Buffer Size : Ch#23
DECL|macro|MO_DMA24_CNT1
mdefine_line|#define MO_DMA24_CNT1       0x30010C 
singleline_comment|// {11}RW* DMA Buffer Size : Ch#24
DECL|macro|MO_DMA25_CNT1
mdefine_line|#define MO_DMA25_CNT1       0x300110 
singleline_comment|// {11}RW* DMA Buffer Size : Ch#25
DECL|macro|MO_DMA26_CNT1
mdefine_line|#define MO_DMA26_CNT1       0x300114 
singleline_comment|// {11}RW* DMA Buffer Size : Ch#26
DECL|macro|MO_DMA27_CNT1
mdefine_line|#define MO_DMA27_CNT1       0x300118 
singleline_comment|// {11}RW* DMA Buffer Size : Ch#27
DECL|macro|MO_DMA28_CNT1
mdefine_line|#define MO_DMA28_CNT1       0x30011C 
singleline_comment|// {11}RW* DMA Buffer Size : Ch#28
DECL|macro|MO_DMA29_CNT1
mdefine_line|#define MO_DMA29_CNT1       0x300120 
singleline_comment|// {11}RW* DMA Buffer Size : Ch#29
DECL|macro|MO_DMA30_CNT1
mdefine_line|#define MO_DMA30_CNT1       0x300124 
singleline_comment|// {11}RW* DMA Buffer Size : Ch#30
DECL|macro|MO_DMA31_CNT1
mdefine_line|#define MO_DMA31_CNT1       0x300128 
singleline_comment|// {11}RW* DMA Buffer Size : Ch#31
DECL|macro|MO_DMA32_CNT1
mdefine_line|#define MO_DMA32_CNT1       0x30012C 
singleline_comment|// {11}RW* DMA Buffer Size : Ch#32
DECL|macro|MO_DMA21_CNT2
mdefine_line|#define MO_DMA21_CNT2       0x300140 
singleline_comment|// {11}RW* DMA Table Size : Ch#21
DECL|macro|MO_DMA22_CNT2
mdefine_line|#define MO_DMA22_CNT2       0x300144 
singleline_comment|// {11}RW* DMA Table Size : Ch#22
DECL|macro|MO_DMA23_CNT2
mdefine_line|#define MO_DMA23_CNT2       0x300148 
singleline_comment|// {11}RW* DMA Table Size : Ch#23
DECL|macro|MO_DMA24_CNT2
mdefine_line|#define MO_DMA24_CNT2       0x30014C 
singleline_comment|// {11}RW* DMA Table Size : Ch#24
DECL|macro|MO_DMA25_CNT2
mdefine_line|#define MO_DMA25_CNT2       0x300150 
singleline_comment|// {11}RW* DMA Table Size : Ch#25
DECL|macro|MO_DMA26_CNT2
mdefine_line|#define MO_DMA26_CNT2       0x300154 
singleline_comment|// {11}RW* DMA Table Size : Ch#26
DECL|macro|MO_DMA27_CNT2
mdefine_line|#define MO_DMA27_CNT2       0x300158 
singleline_comment|// {11}RW* DMA Table Size : Ch#27
DECL|macro|MO_DMA28_CNT2
mdefine_line|#define MO_DMA28_CNT2       0x30015C 
singleline_comment|// {11}RW* DMA Table Size : Ch#28
DECL|macro|MO_DMA29_CNT2
mdefine_line|#define MO_DMA29_CNT2       0x300160 
singleline_comment|// {11}RW* DMA Table Size : Ch#29
DECL|macro|MO_DMA30_CNT2
mdefine_line|#define MO_DMA30_CNT2       0x300164 
singleline_comment|// {11}RW* DMA Table Size : Ch#30
DECL|macro|MO_DMA31_CNT2
mdefine_line|#define MO_DMA31_CNT2       0x300168 
singleline_comment|// {11}RW* DMA Table Size : Ch#31
DECL|macro|MO_DMA32_CNT2
mdefine_line|#define MO_DMA32_CNT2       0x30016C 
singleline_comment|// {11}RW* DMA Table Size : Ch#32
multiline_comment|/* ---------------------------------------------------------------------- */
multiline_comment|/* Video registers                                                        */
DECL|macro|MO_VIDY_DMA
mdefine_line|#define MO_VIDY_DMA         0x310000 
singleline_comment|// {64}RWp Video Y
DECL|macro|MO_VIDU_DMA
mdefine_line|#define MO_VIDU_DMA         0x310008 
singleline_comment|// {64}RWp Video U
DECL|macro|MO_VIDV_DMA
mdefine_line|#define MO_VIDV_DMA         0x310010 
singleline_comment|// {64}RWp Video V
DECL|macro|MO_VBI_DMA
mdefine_line|#define MO_VBI_DMA          0x310018 
singleline_comment|// {64}RWp VBI (Vertical blanking interval)
DECL|macro|MO_DEVICE_STATUS
mdefine_line|#define MO_DEVICE_STATUS    0x310100
DECL|macro|MO_INPUT_FORMAT
mdefine_line|#define MO_INPUT_FORMAT     0x310104
DECL|macro|MO_AGC_BURST
mdefine_line|#define MO_AGC_BURST        0x31010c
DECL|macro|MO_CONTR_BRIGHT
mdefine_line|#define MO_CONTR_BRIGHT     0x310110
DECL|macro|MO_UV_SATURATION
mdefine_line|#define MO_UV_SATURATION    0x310114
DECL|macro|MO_HUE
mdefine_line|#define MO_HUE              0x310118
DECL|macro|MO_HTOTAL
mdefine_line|#define MO_HTOTAL           0x310120
DECL|macro|MO_HDELAY_EVEN
mdefine_line|#define MO_HDELAY_EVEN      0x310124
DECL|macro|MO_HDELAY_ODD
mdefine_line|#define MO_HDELAY_ODD       0x310128
DECL|macro|MO_VDELAY_ODD
mdefine_line|#define MO_VDELAY_ODD       0x31012c
DECL|macro|MO_VDELAY_EVEN
mdefine_line|#define MO_VDELAY_EVEN      0x310130
DECL|macro|MO_HACTIVE_EVEN
mdefine_line|#define MO_HACTIVE_EVEN     0x31013c
DECL|macro|MO_HACTIVE_ODD
mdefine_line|#define MO_HACTIVE_ODD      0x310140
DECL|macro|MO_VACTIVE_EVEN
mdefine_line|#define MO_VACTIVE_EVEN     0x310144
DECL|macro|MO_VACTIVE_ODD
mdefine_line|#define MO_VACTIVE_ODD      0x310148
DECL|macro|MO_HSCALE_EVEN
mdefine_line|#define MO_HSCALE_EVEN      0x31014c
DECL|macro|MO_HSCALE_ODD
mdefine_line|#define MO_HSCALE_ODD       0x310150
DECL|macro|MO_VSCALE_EVEN
mdefine_line|#define MO_VSCALE_EVEN      0x310154
DECL|macro|MO_FILTER_EVEN
mdefine_line|#define MO_FILTER_EVEN      0x31015c
DECL|macro|MO_VSCALE_ODD
mdefine_line|#define MO_VSCALE_ODD       0x310158
DECL|macro|MO_FILTER_ODD
mdefine_line|#define MO_FILTER_ODD       0x310160
DECL|macro|MO_OUTPUT_FORMAT
mdefine_line|#define MO_OUTPUT_FORMAT    0x310164
DECL|macro|MO_PLL_REG
mdefine_line|#define MO_PLL_REG          0x310168 
singleline_comment|// PLL register
DECL|macro|MO_PLL_ADJ_CTRL
mdefine_line|#define MO_PLL_ADJ_CTRL     0x31016c 
singleline_comment|// PLL adjust control register
DECL|macro|MO_SCONV_REG
mdefine_line|#define MO_SCONV_REG        0x310170 
singleline_comment|// sample rate conversion register
DECL|macro|MO_SCONV_FIFO
mdefine_line|#define MO_SCONV_FIFO       0x310174 
singleline_comment|// sample rate conversion fifo
DECL|macro|MO_SUB_STEP
mdefine_line|#define MO_SUB_STEP         0x310178 
singleline_comment|// subcarrier step size
DECL|macro|MO_SUB_STEP_DR
mdefine_line|#define MO_SUB_STEP_DR      0x31017c 
singleline_comment|// subcarrier step size for DR line
DECL|macro|MO_CAPTURE_CTRL
mdefine_line|#define MO_CAPTURE_CTRL     0x310180 
singleline_comment|// capture control
DECL|macro|MO_COLOR_CTRL
mdefine_line|#define MO_COLOR_CTRL       0x310184
DECL|macro|MO_VBI_PACKET
mdefine_line|#define MO_VBI_PACKET       0x310188 
singleline_comment|// vbi packet size / delay
DECL|macro|MO_FIELD_COUNT
mdefine_line|#define MO_FIELD_COUNT      0x310190 
singleline_comment|// field counter
DECL|macro|MO_VIP_CONFIG
mdefine_line|#define MO_VIP_CONFIG       0x310194
DECL|macro|MO_VBOS_CONTROL
mdefine_line|#define MO_VBOS_CONTROL&t;    0x3101a8
DECL|macro|MO_AGC_BACK_VBI
mdefine_line|#define MO_AGC_BACK_VBI     0x310200
DECL|macro|MO_AGC_SYNC_TIP1
mdefine_line|#define MO_AGC_SYNC_TIP1    0x310208
DECL|macro|MO_VIDY_GPCNT
mdefine_line|#define MO_VIDY_GPCNT       0x31C020 
singleline_comment|// {16}RO Video Y general purpose counter
DECL|macro|MO_VIDU_GPCNT
mdefine_line|#define MO_VIDU_GPCNT       0x31C024 
singleline_comment|// {16}RO Video U general purpose counter
DECL|macro|MO_VIDV_GPCNT
mdefine_line|#define MO_VIDV_GPCNT       0x31C028 
singleline_comment|// {16}RO Video V general purpose counter
DECL|macro|MO_VBI_GPCNT
mdefine_line|#define MO_VBI_GPCNT        0x31C02C 
singleline_comment|// {16}RO VBI general purpose counter
DECL|macro|MO_VIDY_GPCNTRL
mdefine_line|#define MO_VIDY_GPCNTRL     0x31C030 
singleline_comment|// {2}WO Video Y general purpose control
DECL|macro|MO_VIDU_GPCNTRL
mdefine_line|#define MO_VIDU_GPCNTRL     0x31C034 
singleline_comment|// {2}WO Video U general purpose control
DECL|macro|MO_VIDV_GPCNTRL
mdefine_line|#define MO_VIDV_GPCNTRL     0x31C038 
singleline_comment|// {2}WO Video V general purpose control
DECL|macro|MO_VBI_GPCNTRL
mdefine_line|#define MO_VBI_GPCNTRL      0x31C03C 
singleline_comment|// {2}WO VBI general purpose counter
DECL|macro|MO_VID_DMACNTRL
mdefine_line|#define MO_VID_DMACNTRL     0x31C040 
singleline_comment|// {8}RW Video DMA control
DECL|macro|MO_VID_XFR_STAT
mdefine_line|#define MO_VID_XFR_STAT     0x31C044 
singleline_comment|// {1}RO Video transfer status
multiline_comment|/* ---------------------------------------------------------------------- */
multiline_comment|/* audio registers                                                        */
DECL|macro|MO_AUDD_DMA
mdefine_line|#define MO_AUDD_DMA         0x320000 
singleline_comment|// {64}RWp Audio downstream
DECL|macro|MO_AUDU_DMA
mdefine_line|#define MO_AUDU_DMA         0x320008 
singleline_comment|// {64}RWp Audio upstream
DECL|macro|MO_AUDR_DMA
mdefine_line|#define MO_AUDR_DMA         0x320010 
singleline_comment|// {64}RWp Audio RDS (downstream)
DECL|macro|MO_AUDD_GPCNT
mdefine_line|#define MO_AUDD_GPCNT       0x32C020 
singleline_comment|// {16}RO Audio down general purpose counter
DECL|macro|MO_AUDU_GPCNT
mdefine_line|#define MO_AUDU_GPCNT       0x32C024 
singleline_comment|// {16}RO Audio up general purpose counter
DECL|macro|MO_AUDR_GPCNT
mdefine_line|#define MO_AUDR_GPCNT       0x32C028 
singleline_comment|// {16}RO Audio RDS general purpose counter
DECL|macro|MO_AUDD_GPCNTRL
mdefine_line|#define MO_AUDD_GPCNTRL     0x32C030 
singleline_comment|// {2}WO Audio down general purpose control
DECL|macro|MO_AUDU_GPCNTRL
mdefine_line|#define MO_AUDU_GPCNTRL     0x32C034 
singleline_comment|// {2}WO Audio up general purpose control
DECL|macro|MO_AUDR_GPCNTRL
mdefine_line|#define MO_AUDR_GPCNTRL     0x32C038 
singleline_comment|// {2}WO Audio RDS general purpose control
DECL|macro|MO_AUD_DMACNTRL
mdefine_line|#define MO_AUD_DMACNTRL     0x32C040 
singleline_comment|// {6}RW Audio DMA control
DECL|macro|MO_AUD_XFR_STAT
mdefine_line|#define MO_AUD_XFR_STAT     0x32C044 
singleline_comment|// {1}RO Audio transfer status
DECL|macro|MO_AUDD_LNGTH
mdefine_line|#define MO_AUDD_LNGTH       0x32C048 
singleline_comment|// {12}RW Audio down line length
DECL|macro|MO_AUDR_LNGTH
mdefine_line|#define MO_AUDR_LNGTH       0x32C04C 
singleline_comment|// {12}RW Audio RDS line length
DECL|macro|AUD_INIT
mdefine_line|#define AUD_INIT                 0x320100
DECL|macro|AUD_INIT_LD
mdefine_line|#define AUD_INIT_LD              0x320104
DECL|macro|AUD_SOFT_RESET
mdefine_line|#define AUD_SOFT_RESET           0x320108
DECL|macro|AUD_I2SINPUTCNTL
mdefine_line|#define AUD_I2SINPUTCNTL         0x320120
DECL|macro|AUD_BAUDRATE
mdefine_line|#define AUD_BAUDRATE             0x320124
DECL|macro|AUD_I2SOUTPUTCNTL
mdefine_line|#define AUD_I2SOUTPUTCNTL        0x320128
DECL|macro|AAGC_HYST
mdefine_line|#define AAGC_HYST                0x320134
DECL|macro|AAGC_GAIN
mdefine_line|#define AAGC_GAIN                0x320138
DECL|macro|AAGC_DEF
mdefine_line|#define AAGC_DEF                 0x32013c
DECL|macro|AUD_IIR1_0_SEL
mdefine_line|#define AUD_IIR1_0_SEL           0x320150
DECL|macro|AUD_IIR1_0_SHIFT
mdefine_line|#define AUD_IIR1_0_SHIFT         0x320154
DECL|macro|AUD_IIR1_1_SEL
mdefine_line|#define AUD_IIR1_1_SEL           0x320158
DECL|macro|AUD_IIR1_1_SHIFT
mdefine_line|#define AUD_IIR1_1_SHIFT         0x32015c
DECL|macro|AUD_IIR1_2_SEL
mdefine_line|#define AUD_IIR1_2_SEL           0x320160
DECL|macro|AUD_IIR1_2_SHIFT
mdefine_line|#define AUD_IIR1_2_SHIFT         0x320164
DECL|macro|AUD_IIR1_3_SEL
mdefine_line|#define AUD_IIR1_3_SEL           0x320168
DECL|macro|AUD_IIR1_3_SHIFT
mdefine_line|#define AUD_IIR1_3_SHIFT         0x32016c
DECL|macro|AUD_IIR1_4_SEL
mdefine_line|#define AUD_IIR1_4_SEL           0x320170
DECL|macro|AUD_IIR1_4_SHIFT
mdefine_line|#define AUD_IIR1_4_SHIFT         0x32017c
DECL|macro|AUD_IIR1_5_SEL
mdefine_line|#define AUD_IIR1_5_SEL           0x320180
DECL|macro|AUD_IIR1_5_SHIFT
mdefine_line|#define AUD_IIR1_5_SHIFT         0x320184
DECL|macro|AUD_IIR2_0_SEL
mdefine_line|#define AUD_IIR2_0_SEL           0x320190
DECL|macro|AUD_IIR2_0_SHIFT
mdefine_line|#define AUD_IIR2_0_SHIFT         0x320194
DECL|macro|AUD_IIR2_1_SEL
mdefine_line|#define AUD_IIR2_1_SEL           0x320198
DECL|macro|AUD_IIR2_1_SHIFT
mdefine_line|#define AUD_IIR2_1_SHIFT         0x32019c
DECL|macro|AUD_IIR2_2_SEL
mdefine_line|#define AUD_IIR2_2_SEL           0x3201a0
DECL|macro|AUD_IIR2_2_SHIFT
mdefine_line|#define AUD_IIR2_2_SHIFT         0x3201a4
DECL|macro|AUD_IIR2_3_SEL
mdefine_line|#define AUD_IIR2_3_SEL           0x3201a8
DECL|macro|AUD_IIR2_3_SHIFT
mdefine_line|#define AUD_IIR2_3_SHIFT         0x3201ac
DECL|macro|AUD_IIR3_0_SEL
mdefine_line|#define AUD_IIR3_0_SEL           0x3201c0
DECL|macro|AUD_IIR3_0_SHIFT
mdefine_line|#define AUD_IIR3_0_SHIFT         0x3201c4
DECL|macro|AUD_IIR3_1_SEL
mdefine_line|#define AUD_IIR3_1_SEL           0x3201c8
DECL|macro|AUD_IIR3_1_SHIFT
mdefine_line|#define AUD_IIR3_1_SHIFT         0x3201cc
DECL|macro|AUD_IIR3_2_SEL
mdefine_line|#define AUD_IIR3_2_SEL           0x3201d0
DECL|macro|AUD_IIR3_2_SHIFT
mdefine_line|#define AUD_IIR3_2_SHIFT         0x3201d4
DECL|macro|AUD_IIR4_0_SEL
mdefine_line|#define AUD_IIR4_0_SEL           0x3201e0
DECL|macro|AUD_IIR4_0_SHIFT
mdefine_line|#define AUD_IIR4_0_SHIFT         0x3201e4
DECL|macro|AUD_IIR4_1_SEL
mdefine_line|#define AUD_IIR4_1_SEL           0x3201e8
DECL|macro|AUD_IIR4_1_SHIFT
mdefine_line|#define AUD_IIR4_1_SHIFT         0x3201ec
DECL|macro|AUD_IIR4_2_SEL
mdefine_line|#define AUD_IIR4_2_SEL           0x3201f0
DECL|macro|AUD_IIR4_2_SHIFT
mdefine_line|#define AUD_IIR4_2_SHIFT         0x3201f4
DECL|macro|AUD_IIR4_0_CA0
mdefine_line|#define AUD_IIR4_0_CA0           0x320200
DECL|macro|AUD_IIR4_0_CA1
mdefine_line|#define AUD_IIR4_0_CA1           0x320204
DECL|macro|AUD_IIR4_0_CA2
mdefine_line|#define AUD_IIR4_0_CA2           0x320208
DECL|macro|AUD_IIR4_0_CB0
mdefine_line|#define AUD_IIR4_0_CB0           0x32020c
DECL|macro|AUD_IIR4_0_CB1
mdefine_line|#define AUD_IIR4_0_CB1           0x320210
DECL|macro|AUD_IIR4_1_CA0
mdefine_line|#define AUD_IIR4_1_CA0           0x320214
DECL|macro|AUD_IIR4_1_CA1
mdefine_line|#define AUD_IIR4_1_CA1           0x320218
DECL|macro|AUD_IIR4_1_CA2
mdefine_line|#define AUD_IIR4_1_CA2           0x32021c
DECL|macro|AUD_IIR4_1_CB0
mdefine_line|#define AUD_IIR4_1_CB0           0x320220
DECL|macro|AUD_IIR4_1_CB1
mdefine_line|#define AUD_IIR4_1_CB1           0x320224
DECL|macro|AUD_IIR4_2_CA0
mdefine_line|#define AUD_IIR4_2_CA0           0x320228
DECL|macro|AUD_IIR4_2_CA1
mdefine_line|#define AUD_IIR4_2_CA1           0x32022c
DECL|macro|AUD_IIR4_2_CA2
mdefine_line|#define AUD_IIR4_2_CA2           0x320230
DECL|macro|AUD_IIR4_2_CB0
mdefine_line|#define AUD_IIR4_2_CB0           0x320234
DECL|macro|AUD_IIR4_2_CB1
mdefine_line|#define AUD_IIR4_2_CB1           0x320238
DECL|macro|AUD_HP_MD_IIR4_1
mdefine_line|#define AUD_HP_MD_IIR4_1         0x320250
DECL|macro|AUD_HP_PROG_IIR4_1
mdefine_line|#define AUD_HP_PROG_IIR4_1       0x320254
DECL|macro|AUD_FM_MODE_ENABLE
mdefine_line|#define AUD_FM_MODE_ENABLE       0x320258
DECL|macro|AUD_POLY0_DDS_CONSTANT
mdefine_line|#define AUD_POLY0_DDS_CONSTANT   0x320270
DECL|macro|AUD_DN0_FREQ
mdefine_line|#define AUD_DN0_FREQ             0x320274
DECL|macro|AUD_DN1_FREQ
mdefine_line|#define AUD_DN1_FREQ             0x320278
DECL|macro|AUD_DN1_FREQ_SHIFT
mdefine_line|#define AUD_DN1_FREQ_SHIFT       0x32027c
DECL|macro|AUD_DN1_AFC
mdefine_line|#define AUD_DN1_AFC              0x320280
DECL|macro|AUD_DN1_SRC_SEL
mdefine_line|#define AUD_DN1_SRC_SEL          0x320284
DECL|macro|AUD_DN1_SHFT
mdefine_line|#define AUD_DN1_SHFT             0x320288
DECL|macro|AUD_DN2_FREQ
mdefine_line|#define AUD_DN2_FREQ             0x32028c
DECL|macro|AUD_DN2_FREQ_SHIFT
mdefine_line|#define AUD_DN2_FREQ_SHIFT       0x320290
DECL|macro|AUD_DN2_AFC
mdefine_line|#define AUD_DN2_AFC              0x320294
DECL|macro|AUD_DN2_SRC_SEL
mdefine_line|#define AUD_DN2_SRC_SEL          0x320298
DECL|macro|AUD_DN2_SHFT
mdefine_line|#define AUD_DN2_SHFT             0x32029c
DECL|macro|AUD_CRDC0_SRC_SEL
mdefine_line|#define AUD_CRDC0_SRC_SEL        0x320300
DECL|macro|AUD_CRDC0_SHIFT
mdefine_line|#define AUD_CRDC0_SHIFT          0x320304
DECL|macro|AUD_CORDIC_SHIFT_0
mdefine_line|#define AUD_CORDIC_SHIFT_0       0x320308
DECL|macro|AUD_CRDC1_SRC_SEL
mdefine_line|#define AUD_CRDC1_SRC_SEL        0x32030c
DECL|macro|AUD_CRDC1_SHIFT
mdefine_line|#define AUD_CRDC1_SHIFT          0x320310
DECL|macro|AUD_CORDIC_SHIFT_1
mdefine_line|#define AUD_CORDIC_SHIFT_1       0x320314
DECL|macro|AUD_DCOC_0_SRC
mdefine_line|#define AUD_DCOC_0_SRC           0x320320
DECL|macro|AUD_DCOC0_SHIFT
mdefine_line|#define AUD_DCOC0_SHIFT          0x320324
DECL|macro|AUD_DCOC_0_SHIFT_IN0
mdefine_line|#define AUD_DCOC_0_SHIFT_IN0     0x320328
DECL|macro|AUD_DCOC_0_SHIFT_IN1
mdefine_line|#define AUD_DCOC_0_SHIFT_IN1     0x32032c
DECL|macro|AUD_DCOC_1_SRC
mdefine_line|#define AUD_DCOC_1_SRC           0x320330
DECL|macro|AUD_DCOC1_SHIFT
mdefine_line|#define AUD_DCOC1_SHIFT          0x320334
DECL|macro|AUD_DCOC_1_SHIFT_IN0
mdefine_line|#define AUD_DCOC_1_SHIFT_IN0     0x320338
DECL|macro|AUD_DCOC_1_SHIFT_IN1
mdefine_line|#define AUD_DCOC_1_SHIFT_IN1     0x32033c
DECL|macro|AUD_DCOC_2_SRC
mdefine_line|#define AUD_DCOC_2_SRC           0x320340
DECL|macro|AUD_DCOC2_SHIFT
mdefine_line|#define AUD_DCOC2_SHIFT          0x320344
DECL|macro|AUD_DCOC_2_SHIFT_IN0
mdefine_line|#define AUD_DCOC_2_SHIFT_IN0     0x320348
DECL|macro|AUD_DCOC_2_SHIFT_IN1
mdefine_line|#define AUD_DCOC_2_SHIFT_IN1     0x32034c
DECL|macro|AUD_DCOC_PASS_IN
mdefine_line|#define AUD_DCOC_PASS_IN         0x320350
DECL|macro|AUD_PDET_SRC
mdefine_line|#define AUD_PDET_SRC             0x320370
DECL|macro|AUD_PDET_SHIFT
mdefine_line|#define AUD_PDET_SHIFT           0x320374
DECL|macro|AUD_PILOT_BQD_1_K0
mdefine_line|#define AUD_PILOT_BQD_1_K0       0x320380
DECL|macro|AUD_PILOT_BQD_1_K1
mdefine_line|#define AUD_PILOT_BQD_1_K1       0x320384
DECL|macro|AUD_PILOT_BQD_1_K2
mdefine_line|#define AUD_PILOT_BQD_1_K2       0x320388
DECL|macro|AUD_PILOT_BQD_1_K3
mdefine_line|#define AUD_PILOT_BQD_1_K3       0x32038c
DECL|macro|AUD_PILOT_BQD_1_K4
mdefine_line|#define AUD_PILOT_BQD_1_K4       0x320390
DECL|macro|AUD_PILOT_BQD_2_K0
mdefine_line|#define AUD_PILOT_BQD_2_K0       0x320394
DECL|macro|AUD_PILOT_BQD_2_K1
mdefine_line|#define AUD_PILOT_BQD_2_K1       0x320398
DECL|macro|AUD_PILOT_BQD_2_K2
mdefine_line|#define AUD_PILOT_BQD_2_K2       0x32039c
DECL|macro|AUD_PILOT_BQD_2_K3
mdefine_line|#define AUD_PILOT_BQD_2_K3       0x3203a0
DECL|macro|AUD_PILOT_BQD_2_K4
mdefine_line|#define AUD_PILOT_BQD_2_K4       0x3203a4
DECL|macro|AUD_THR_FR
mdefine_line|#define AUD_THR_FR               0x3203c0
DECL|macro|AUD_X_PROG
mdefine_line|#define AUD_X_PROG               0x3203c4
DECL|macro|AUD_Y_PROG
mdefine_line|#define AUD_Y_PROG               0x3203c8
DECL|macro|AUD_HARMONIC_MULT
mdefine_line|#define AUD_HARMONIC_MULT        0x3203cc
DECL|macro|AUD_C1_UP_THR
mdefine_line|#define AUD_C1_UP_THR            0x3203d0
DECL|macro|AUD_C1_LO_THR
mdefine_line|#define AUD_C1_LO_THR            0x3203d4
DECL|macro|AUD_C2_UP_THR
mdefine_line|#define AUD_C2_UP_THR            0x3203d8
DECL|macro|AUD_C2_LO_THR
mdefine_line|#define AUD_C2_LO_THR            0x3203dc
DECL|macro|AUD_PLL_EN
mdefine_line|#define AUD_PLL_EN               0x320400
DECL|macro|AUD_PLL_SRC
mdefine_line|#define AUD_PLL_SRC              0x320404
DECL|macro|AUD_PLL_SHIFT
mdefine_line|#define AUD_PLL_SHIFT            0x320408
DECL|macro|AUD_PLL_IF_SEL
mdefine_line|#define AUD_PLL_IF_SEL           0x32040c
DECL|macro|AUD_PLL_IF_SHIFT
mdefine_line|#define AUD_PLL_IF_SHIFT         0x320410
DECL|macro|AUD_BIQUAD_PLL_K0
mdefine_line|#define AUD_BIQUAD_PLL_K0        0x320414
DECL|macro|AUD_BIQUAD_PLL_K1
mdefine_line|#define AUD_BIQUAD_PLL_K1        0x320418
DECL|macro|AUD_BIQUAD_PLL_K2
mdefine_line|#define AUD_BIQUAD_PLL_K2        0x32041c
DECL|macro|AUD_BIQUAD_PLL_K3
mdefine_line|#define AUD_BIQUAD_PLL_K3        0x320420
DECL|macro|AUD_BIQUAD_PLL_K4
mdefine_line|#define AUD_BIQUAD_PLL_K4        0x320424
DECL|macro|AUD_DEEMPH0_SRC_SEL
mdefine_line|#define AUD_DEEMPH0_SRC_SEL      0x320440
DECL|macro|AUD_DEEMPH0_SHIFT
mdefine_line|#define AUD_DEEMPH0_SHIFT        0x320444
DECL|macro|AUD_DEEMPH0_G0
mdefine_line|#define AUD_DEEMPH0_G0           0x320448
DECL|macro|AUD_DEEMPH0_A0
mdefine_line|#define AUD_DEEMPH0_A0           0x32044c
DECL|macro|AUD_DEEMPH0_B0
mdefine_line|#define AUD_DEEMPH0_B0           0x320450
DECL|macro|AUD_DEEMPH0_A1
mdefine_line|#define AUD_DEEMPH0_A1           0x320454
DECL|macro|AUD_DEEMPH0_B1
mdefine_line|#define AUD_DEEMPH0_B1           0x320458
DECL|macro|AUD_DEEMPH1_SRC_SEL
mdefine_line|#define AUD_DEEMPH1_SRC_SEL      0x32045c
DECL|macro|AUD_DEEMPH1_SHIFT
mdefine_line|#define AUD_DEEMPH1_SHIFT        0x320460
DECL|macro|AUD_DEEMPH1_G0
mdefine_line|#define AUD_DEEMPH1_G0           0x320464
DECL|macro|AUD_DEEMPH1_A0
mdefine_line|#define AUD_DEEMPH1_A0           0x320468
DECL|macro|AUD_DEEMPH1_B0
mdefine_line|#define AUD_DEEMPH1_B0           0x32046c
DECL|macro|AUD_DEEMPH1_A1
mdefine_line|#define AUD_DEEMPH1_A1           0x320470
DECL|macro|AUD_DEEMPH1_B1
mdefine_line|#define AUD_DEEMPH1_B1           0x320474
DECL|macro|AUD_OUT0_SEL
mdefine_line|#define AUD_OUT0_SEL             0x320490
DECL|macro|AUD_OUT0_SHIFT
mdefine_line|#define AUD_OUT0_SHIFT           0x320494
DECL|macro|AUD_OUT1_SEL
mdefine_line|#define AUD_OUT1_SEL             0x320498
DECL|macro|AUD_OUT1_SHIFT
mdefine_line|#define AUD_OUT1_SHIFT           0x32049c
DECL|macro|AUD_RDSI_SEL
mdefine_line|#define AUD_RDSI_SEL             0x3204a0
DECL|macro|AUD_RDSI_SHIFT
mdefine_line|#define AUD_RDSI_SHIFT           0x3204a4
DECL|macro|AUD_RDSQ_SEL
mdefine_line|#define AUD_RDSQ_SEL             0x3204a8
DECL|macro|AUD_RDSQ_SHIFT
mdefine_line|#define AUD_RDSQ_SHIFT           0x3204ac
DECL|macro|AUD_DBX_IN_GAIN
mdefine_line|#define AUD_DBX_IN_GAIN          0x320500
DECL|macro|AUD_DBX_WBE_GAIN
mdefine_line|#define AUD_DBX_WBE_GAIN         0x320504
DECL|macro|AUD_DBX_SE_GAIN
mdefine_line|#define AUD_DBX_SE_GAIN          0x320508
DECL|macro|AUD_DBX_RMS_WBE
mdefine_line|#define AUD_DBX_RMS_WBE          0x32050c
DECL|macro|AUD_DBX_RMS_SE
mdefine_line|#define AUD_DBX_RMS_SE           0x320510
DECL|macro|AUD_DBX_SE_BYPASS
mdefine_line|#define AUD_DBX_SE_BYPASS        0x320514
DECL|macro|AUD_FAWDETCTL
mdefine_line|#define AUD_FAWDETCTL            0x320530
DECL|macro|AUD_FAWDETWINCTL
mdefine_line|#define AUD_FAWDETWINCTL         0x320534
DECL|macro|AUD_DEEMPHGAIN_R
mdefine_line|#define AUD_DEEMPHGAIN_R         0x320538
DECL|macro|AUD_DEEMPHNUMER1_R
mdefine_line|#define AUD_DEEMPHNUMER1_R       0x32053c
DECL|macro|AUD_DEEMPHNUMER2_R
mdefine_line|#define AUD_DEEMPHNUMER2_R       0x320540
DECL|macro|AUD_DEEMPHDENOM1_R
mdefine_line|#define AUD_DEEMPHDENOM1_R       0x320544
DECL|macro|AUD_DEEMPHDENOM2_R
mdefine_line|#define AUD_DEEMPHDENOM2_R       0x320548
DECL|macro|AUD_ERRLOGPERIOD_R
mdefine_line|#define AUD_ERRLOGPERIOD_R       0x32054c
DECL|macro|AUD_ERRINTRPTTHSHLD1_R
mdefine_line|#define AUD_ERRINTRPTTHSHLD1_R   0x320550
DECL|macro|AUD_ERRINTRPTTHSHLD2_R
mdefine_line|#define AUD_ERRINTRPTTHSHLD2_R   0x320554
DECL|macro|AUD_ERRINTRPTTHSHLD3_R
mdefine_line|#define AUD_ERRINTRPTTHSHLD3_R   0x320558
DECL|macro|AUD_NICAM_STATUS1
mdefine_line|#define AUD_NICAM_STATUS1        0x32055c
DECL|macro|AUD_NICAM_STATUS2
mdefine_line|#define AUD_NICAM_STATUS2        0x320560
DECL|macro|AUD_ERRLOG1
mdefine_line|#define AUD_ERRLOG1              0x320564
DECL|macro|AUD_ERRLOG2
mdefine_line|#define AUD_ERRLOG2              0x320568
DECL|macro|AUD_ERRLOG3
mdefine_line|#define AUD_ERRLOG3              0x32056c
DECL|macro|AUD_DAC_BYPASS_L
mdefine_line|#define AUD_DAC_BYPASS_L         0x320580
DECL|macro|AUD_DAC_BYPASS_R
mdefine_line|#define AUD_DAC_BYPASS_R         0x320584
DECL|macro|AUD_DAC_BYPASS_CTL
mdefine_line|#define AUD_DAC_BYPASS_CTL       0x320588
DECL|macro|AUD_CTL
mdefine_line|#define AUD_CTL                  0x32058c
DECL|macro|AUD_STATUS
mdefine_line|#define AUD_STATUS               0x320590
DECL|macro|AUD_VOL_CTL
mdefine_line|#define AUD_VOL_CTL              0x320594
DECL|macro|AUD_BAL_CTL
mdefine_line|#define AUD_BAL_CTL              0x320598
DECL|macro|AUD_START_TIMER
mdefine_line|#define AUD_START_TIMER          0x3205b0
DECL|macro|AUD_MODE_CHG_TIMER
mdefine_line|#define AUD_MODE_CHG_TIMER       0x3205b4
DECL|macro|AUD_POLYPH80SCALEFAC
mdefine_line|#define AUD_POLYPH80SCALEFAC     0x3205b8
DECL|macro|AUD_DMD_RA_DDS
mdefine_line|#define AUD_DMD_RA_DDS           0x3205bc
DECL|macro|AUD_I2S_RA_DDS
mdefine_line|#define AUD_I2S_RA_DDS           0x3205c0
DECL|macro|AUD_RATE_THRES_DMD
mdefine_line|#define AUD_RATE_THRES_DMD       0x3205d0
DECL|macro|AUD_RATE_THRES_I2S
mdefine_line|#define AUD_RATE_THRES_I2S       0x3205d4
DECL|macro|AUD_RATE_ADJ1
mdefine_line|#define AUD_RATE_ADJ1            0x3205d8
DECL|macro|AUD_RATE_ADJ2
mdefine_line|#define AUD_RATE_ADJ2            0x3205dc
DECL|macro|AUD_RATE_ADJ3
mdefine_line|#define AUD_RATE_ADJ3            0x3205e0
DECL|macro|AUD_RATE_ADJ4
mdefine_line|#define AUD_RATE_ADJ4            0x3205e4
DECL|macro|AUD_RATE_ADJ5
mdefine_line|#define AUD_RATE_ADJ5            0x3205e8
DECL|macro|AUD_APB_IN_RATE_ADJ
mdefine_line|#define AUD_APB_IN_RATE_ADJ      0x3205ec
DECL|macro|AUD_PHASE_FIX_CTL
mdefine_line|#define AUD_PHASE_FIX_CTL        0x3205f0
DECL|macro|AUD_PLL_PRESCALE
mdefine_line|#define AUD_PLL_PRESCALE         0x320600
DECL|macro|AUD_PLL_DDS
mdefine_line|#define AUD_PLL_DDS              0x320604
DECL|macro|AUD_PLL_INT
mdefine_line|#define AUD_PLL_INT              0x320608
DECL|macro|AUD_PLL_FRAC
mdefine_line|#define AUD_PLL_FRAC             0x32060c
DECL|macro|AUD_PLL_JTAG
mdefine_line|#define AUD_PLL_JTAG             0x320620
DECL|macro|AUD_PLL_SPMP
mdefine_line|#define AUD_PLL_SPMP             0x320624
DECL|macro|AUD_AFE_12DB_EN
mdefine_line|#define AUD_AFE_12DB_EN          0x320628
singleline_comment|// Audio QAM Register Addresses
DECL|macro|AUD_PDF_DDS_CNST_BYTE2
mdefine_line|#define AUD_PDF_DDS_CNST_BYTE2   0x320d01
DECL|macro|AUD_PDF_DDS_CNST_BYTE1
mdefine_line|#define AUD_PDF_DDS_CNST_BYTE1   0x320d02
DECL|macro|AUD_PDF_DDS_CNST_BYTE0
mdefine_line|#define AUD_PDF_DDS_CNST_BYTE0   0x320d03
DECL|macro|AUD_PHACC_FREQ_8MSB
mdefine_line|#define AUD_PHACC_FREQ_8MSB      0x320d2a
DECL|macro|AUD_PHACC_FREQ_8LSB
mdefine_line|#define AUD_PHACC_FREQ_8LSB      0x320d2b
DECL|macro|AUD_QAM_MODE
mdefine_line|#define AUD_QAM_MODE             0x320d04
multiline_comment|/* ---------------------------------------------------------------------- */
multiline_comment|/* transport stream registers                                             */
DECL|macro|MO_TS_DMA
mdefine_line|#define MO_TS_DMA           0x330000 
singleline_comment|// {64}RWp Transport stream downstream
DECL|macro|MO_TS_GPCNT
mdefine_line|#define MO_TS_GPCNT         0x33C020 
singleline_comment|// {16}RO TS general purpose counter
DECL|macro|MO_TS_GPCNTRL
mdefine_line|#define MO_TS_GPCNTRL       0x33C030 
singleline_comment|// {2}WO TS general purpose control
DECL|macro|MO_TS_DMACNTRL
mdefine_line|#define MO_TS_DMACNTRL      0x33C040 
singleline_comment|// {6}RW TS DMA control
DECL|macro|MO_TS_XFR_STAT
mdefine_line|#define MO_TS_XFR_STAT      0x33C044 
singleline_comment|// {1}RO TS transfer status
DECL|macro|MO_TS_LNGTH
mdefine_line|#define MO_TS_LNGTH         0x33C048 
singleline_comment|// {12}RW TS line length
DECL|macro|TS_HW_SOP_CNTRL
mdefine_line|#define TS_HW_SOP_CNTRL     0x33C04C
DECL|macro|TS_GEN_CNTRL
mdefine_line|#define TS_GEN_CNTRL        0x33C050
DECL|macro|TS_BD_PKT_STAT
mdefine_line|#define TS_BD_PKT_STAT      0x33C054
DECL|macro|TS_SOP_STAT
mdefine_line|#define TS_SOP_STAT         0x33C058
DECL|macro|TS_FIFO_OVFL_STAT
mdefine_line|#define TS_FIFO_OVFL_STAT   0x33C05C
DECL|macro|TS_VALERR_CNTRL
mdefine_line|#define TS_VALERR_CNTRL     0x33C060
multiline_comment|/* ---------------------------------------------------------------------- */
multiline_comment|/* VIP registers                                                          */
DECL|macro|MO_VIPD_DMA
mdefine_line|#define MO_VIPD_DMA         0x340000 
singleline_comment|// {64}RWp VIP downstream
DECL|macro|MO_VIPU_DMA
mdefine_line|#define MO_VIPU_DMA         0x340008 
singleline_comment|// {64}RWp VIP upstream
DECL|macro|MO_VIPD_GPCNT
mdefine_line|#define MO_VIPD_GPCNT       0x34C020 
singleline_comment|// {16}RO VIP down general purpose counter
DECL|macro|MO_VIPU_GPCNT
mdefine_line|#define MO_VIPU_GPCNT       0x34C024 
singleline_comment|// {16}RO VIP up general purpose counter
DECL|macro|MO_VIPD_GPCNTRL
mdefine_line|#define MO_VIPD_GPCNTRL     0x34C030 
singleline_comment|// {2}WO VIP down general purpose control
DECL|macro|MO_VIPU_GPCNTRL
mdefine_line|#define MO_VIPU_GPCNTRL     0x34C034 
singleline_comment|// {2}WO VIP up general purpose control
DECL|macro|MO_VIP_DMACNTRL
mdefine_line|#define MO_VIP_DMACNTRL     0x34C040 
singleline_comment|// {6}RW VIP DMA control
DECL|macro|MO_VIP_XFR_STAT
mdefine_line|#define MO_VIP_XFR_STAT     0x34C044 
singleline_comment|// {1}RO VIP transfer status
DECL|macro|MO_VIP_CFG
mdefine_line|#define MO_VIP_CFG          0x340048 
singleline_comment|// VIP configuration
DECL|macro|MO_VIPU_CNTRL
mdefine_line|#define MO_VIPU_CNTRL       0x34004C 
singleline_comment|// VIP upstream control #1
DECL|macro|MO_VIPD_CNTRL
mdefine_line|#define MO_VIPD_CNTRL       0x340050 
singleline_comment|// VIP downstream control #2
DECL|macro|MO_VIPD_LNGTH
mdefine_line|#define MO_VIPD_LNGTH       0x340054 
singleline_comment|// VIP downstream line length
DECL|macro|MO_VIP_BRSTLN
mdefine_line|#define MO_VIP_BRSTLN       0x340058 
singleline_comment|// VIP burst length
DECL|macro|MO_VIP_INTCNTRL
mdefine_line|#define MO_VIP_INTCNTRL     0x34C05C 
singleline_comment|// VIP Interrupt Control
DECL|macro|MO_VIP_XFTERM
mdefine_line|#define MO_VIP_XFTERM       0x340060 
singleline_comment|// VIP transfer terminate
multiline_comment|/* ---------------------------------------------------------------------- */
multiline_comment|/* misc registers                                                         */
DECL|macro|MO_M2M_DMA
mdefine_line|#define MO_M2M_DMA          0x350000 
singleline_comment|// {64}RWp Mem2Mem DMA Bfr
DECL|macro|MO_GP0_IO
mdefine_line|#define MO_GP0_IO           0x350010 
singleline_comment|// {32}RW* GPIOoutput enablesdata I/O
DECL|macro|MO_GP1_IO
mdefine_line|#define MO_GP1_IO           0x350014 
singleline_comment|// {32}RW* GPIOoutput enablesdata I/O
DECL|macro|MO_GP2_IO
mdefine_line|#define MO_GP2_IO           0x350018 
singleline_comment|// {32}RW* GPIOoutput enablesdata I/O
DECL|macro|MO_GP3_IO
mdefine_line|#define MO_GP3_IO           0x35001C 
singleline_comment|// {32}RW* GPIO Mode/Ctrloutput enables
DECL|macro|MO_GPIO
mdefine_line|#define MO_GPIO             0x350020 
singleline_comment|// {32}RW* GPIO I2C Ctrldata I/O
DECL|macro|MO_GPOE
mdefine_line|#define MO_GPOE             0x350024 
singleline_comment|// {32}RW  GPIO I2C Ctrloutput enables
DECL|macro|MO_GP_ISM
mdefine_line|#define MO_GP_ISM           0x350028 
singleline_comment|// {16}WO  GPIO Intr Sens/Pol
DECL|macro|MO_PLL_B
mdefine_line|#define MO_PLL_B            0x35C008 
singleline_comment|// {32}RW* PLL Control for ASB bus clks
DECL|macro|MO_M2M_CNT
mdefine_line|#define MO_M2M_CNT          0x35C024 
singleline_comment|// {32}RW  Mem2Mem DMA Cnt
DECL|macro|MO_M2M_XSUM
mdefine_line|#define MO_M2M_XSUM         0x35C028 
singleline_comment|// {32}RO  M2M XOR-Checksum
DECL|macro|MO_CRC
mdefine_line|#define MO_CRC              0x35C02C 
singleline_comment|// {16}RW  CRC16 init/result
DECL|macro|MO_CRC_D
mdefine_line|#define MO_CRC_D            0x35C030 
singleline_comment|// {32}WO  CRC16 new data in
DECL|macro|MO_TM_CNT_LDW
mdefine_line|#define MO_TM_CNT_LDW       0x35C034 
singleline_comment|// {32}RO  Timer : Counter low dword
DECL|macro|MO_TM_CNT_UW
mdefine_line|#define MO_TM_CNT_UW        0x35C038 
singleline_comment|// {16}RO  Timer : Counter high word
DECL|macro|MO_TM_LMT_LDW
mdefine_line|#define MO_TM_LMT_LDW       0x35C03C 
singleline_comment|// {32}RW  Timer : Limit low dword
DECL|macro|MO_TM_LMT_UW
mdefine_line|#define MO_TM_LMT_UW        0x35C040 
singleline_comment|// {32}RW  Timer : Limit high word
DECL|macro|MO_PINMUX_IO
mdefine_line|#define MO_PINMUX_IO        0x35C044 
singleline_comment|// {8}RW  Pin Mux Control
DECL|macro|MO_TSTSEL_IO
mdefine_line|#define MO_TSTSEL_IO        0x35C048 
singleline_comment|// {2}RW  Pin Mux Control
DECL|macro|MO_AFECFG_IO
mdefine_line|#define MO_AFECFG_IO        0x35C04C 
singleline_comment|// AFE configuration reg
DECL|macro|MO_DDS_IO
mdefine_line|#define MO_DDS_IO           0x35C050 
singleline_comment|// DDS Increment reg
DECL|macro|MO_DDSCFG_IO
mdefine_line|#define MO_DDSCFG_IO        0x35C054 
singleline_comment|// DDS Configuration reg
DECL|macro|MO_SAMPLE_IO
mdefine_line|#define MO_SAMPLE_IO        0x35C058 
singleline_comment|// IRIn sample reg
DECL|macro|MO_SRST_IO
mdefine_line|#define MO_SRST_IO          0x35C05C 
singleline_comment|// Output system reset reg
DECL|macro|MO_INT1_MSK
mdefine_line|#define MO_INT1_MSK         0x35C060 
singleline_comment|// DMA RISC interrupt mask
DECL|macro|MO_INT1_STAT
mdefine_line|#define MO_INT1_STAT        0x35C064 
singleline_comment|// DMA RISC interrupt status
DECL|macro|MO_INT1_MSTAT
mdefine_line|#define MO_INT1_MSTAT       0x35C068 
singleline_comment|// DMA RISC interrupt masked status
multiline_comment|/* ---------------------------------------------------------------------- */
multiline_comment|/* i2c bus registers                                                      */
DECL|macro|MO_I2C
mdefine_line|#define MO_I2C              0x368000 
singleline_comment|// I2C data/control
DECL|macro|MO_I2C_DIV
mdefine_line|#define MO_I2C_DIV          (0xf&lt;&lt;4)
DECL|macro|MO_I2C_SYNC
mdefine_line|#define MO_I2C_SYNC         (1&lt;&lt;3)
DECL|macro|MO_I2C_W3B
mdefine_line|#define MO_I2C_W3B          (1&lt;&lt;2)
DECL|macro|MO_I2C_SCL
mdefine_line|#define MO_I2C_SCL          (1&lt;&lt;1)
DECL|macro|MO_I2C_SDA
mdefine_line|#define MO_I2C_SDA          (1&lt;&lt;0)
multiline_comment|/* ---------------------------------------------------------------------- */
multiline_comment|/* general purpose host registers                                         */
multiline_comment|/* FIXME: tyops?  s/0x35/0x38/ ??                                         */
DECL|macro|MO_GPHSTD_DMA
mdefine_line|#define MO_GPHSTD_DMA       0x350000 
singleline_comment|// {64}RWp Host downstream
DECL|macro|MO_GPHSTU_DMA
mdefine_line|#define MO_GPHSTU_DMA       0x350008 
singleline_comment|// {64}RWp Host upstream
DECL|macro|MO_GPHSTU_CNTRL
mdefine_line|#define MO_GPHSTU_CNTRL     0x380048 
singleline_comment|// Host upstream control #1
DECL|macro|MO_GPHSTD_CNTRL
mdefine_line|#define MO_GPHSTD_CNTRL     0x38004C 
singleline_comment|// Host downstream control #2
DECL|macro|MO_GPHSTD_LNGTH
mdefine_line|#define MO_GPHSTD_LNGTH     0x380050 
singleline_comment|// Host downstream line length
DECL|macro|MO_GPHST_WSC
mdefine_line|#define MO_GPHST_WSC        0x380054 
singleline_comment|// Host wait state control
DECL|macro|MO_GPHST_XFR
mdefine_line|#define MO_GPHST_XFR        0x380058 
singleline_comment|// Host transfer control
DECL|macro|MO_GPHST_WDTH
mdefine_line|#define MO_GPHST_WDTH       0x38005C 
singleline_comment|// Host interface width
DECL|macro|MO_GPHST_HDSHK
mdefine_line|#define MO_GPHST_HDSHK      0x380060 
singleline_comment|// Host peripheral handshake
DECL|macro|MO_GPHST_MUX16
mdefine_line|#define MO_GPHST_MUX16      0x380064 
singleline_comment|// Host muxed 16-bit transfer parameters
DECL|macro|MO_GPHST_MODE
mdefine_line|#define MO_GPHST_MODE       0x380068 
singleline_comment|// Host mode select
DECL|macro|MO_GPHSTD_GPCNT
mdefine_line|#define MO_GPHSTD_GPCNT     0x35C020 
singleline_comment|// Host down general purpose counter
DECL|macro|MO_GPHSTU_GPCNT
mdefine_line|#define MO_GPHSTU_GPCNT     0x35C024 
singleline_comment|// Host up general purpose counter
DECL|macro|MO_GPHSTD_GPCNTRL
mdefine_line|#define MO_GPHSTD_GPCNTRL   0x38C030 
singleline_comment|// Host down general purpose control
DECL|macro|MO_GPHSTU_GPCNTRL
mdefine_line|#define MO_GPHSTU_GPCNTRL   0x38C034 
singleline_comment|// Host up general purpose control
DECL|macro|MO_GPHST_DMACNTRL
mdefine_line|#define MO_GPHST_DMACNTRL   0x38C040 
singleline_comment|// Host DMA control
DECL|macro|MO_GPHST_XFR_STAT
mdefine_line|#define MO_GPHST_XFR_STAT   0x38C044 
singleline_comment|// Host transfer status
DECL|macro|MO_GPHST_SOFT_RST
mdefine_line|#define MO_GPHST_SOFT_RST   0x38C06C 
singleline_comment|// Host software reset
multiline_comment|/* ---------------------------------------------------------------------- */
multiline_comment|/* RISC instructions                                                      */
DECL|macro|RISC_SYNC
mdefine_line|#define RISC_SYNC&t;&t; 0x80000000
DECL|macro|RISC_SYNC_ODD
mdefine_line|#define RISC_SYNC_ODD&t;&t; 0x80000000
DECL|macro|RISC_SYNC_EVEN
mdefine_line|#define RISC_SYNC_EVEN&t;&t; 0x80000200
DECL|macro|RISC_RESYNC
mdefine_line|#define RISC_RESYNC&t;&t; 0x80008000
DECL|macro|RISC_RESYNC_ODD
mdefine_line|#define RISC_RESYNC_ODD&t;&t; 0x80008000
DECL|macro|RISC_RESYNC_EVEN
mdefine_line|#define RISC_RESYNC_EVEN&t; 0x80008200
DECL|macro|RISC_WRITE
mdefine_line|#define RISC_WRITE&t;&t; 0x10000000
DECL|macro|RISC_WRITEC
mdefine_line|#define RISC_WRITEC&t;&t; 0x50000000
DECL|macro|RISC_READ
mdefine_line|#define RISC_READ&t;&t; 0x90000000
DECL|macro|RISC_READC
mdefine_line|#define RISC_READC&t;&t; 0xA0000000
DECL|macro|RISC_JUMP
mdefine_line|#define RISC_JUMP&t;&t; 0x70000000
DECL|macro|RISC_SKIP
mdefine_line|#define RISC_SKIP&t;&t; 0x20000000
DECL|macro|RISC_WRITERM
mdefine_line|#define RISC_WRITERM&t;&t; 0xB0000000
DECL|macro|RISC_WRITECM
mdefine_line|#define RISC_WRITECM&t;&t; 0xC0000000
DECL|macro|RISC_WRITECR
mdefine_line|#define RISC_WRITECR&t;&t; 0xD0000000
DECL|macro|RISC_IMM
mdefine_line|#define RISC_IMM&t;&t; 0x00000001
DECL|macro|RISC_SOL
mdefine_line|#define RISC_SOL&t;&t; 0x08000000
DECL|macro|RISC_EOL
mdefine_line|#define RISC_EOL&t;&t; 0x04000000
DECL|macro|RISC_IRQ2
mdefine_line|#define RISC_IRQ2&t;&t; 0x02000000
DECL|macro|RISC_IRQ1
mdefine_line|#define RISC_IRQ1&t;&t; 0x01000000
DECL|macro|RISC_CNT_NONE
mdefine_line|#define RISC_CNT_NONE&t;&t; 0x00000000
DECL|macro|RISC_CNT_INC
mdefine_line|#define RISC_CNT_INC&t;&t; 0x00010000
DECL|macro|RISC_CNT_RSVR
mdefine_line|#define RISC_CNT_RSVR&t;&t; 0x00020000
DECL|macro|RISC_CNT_RESET
mdefine_line|#define RISC_CNT_RESET&t;&t; 0x00030000
DECL|macro|RISC_JMP_SRP
mdefine_line|#define RISC_JMP_SRP         &t; 0x01
multiline_comment|/* ---------------------------------------------------------------------- */
multiline_comment|/* various constants                                                      */
DECL|macro|SEL_BTSC
mdefine_line|#define SEL_BTSC     0x01
DECL|macro|SEL_EIAJ
mdefine_line|#define SEL_EIAJ     0x02
DECL|macro|SEL_A2
mdefine_line|#define SEL_A2       0x04
DECL|macro|SEL_SAP
mdefine_line|#define SEL_SAP      0x08
DECL|macro|SEL_NICAM
mdefine_line|#define SEL_NICAM    0x10
DECL|macro|SEL_FMRADIO
mdefine_line|#define SEL_FMRADIO  0x20
singleline_comment|// AUD_CTL
DECL|macro|EN_BTSC_FORCE_MONO
mdefine_line|#define EN_BTSC_FORCE_MONO      0
DECL|macro|EN_BTSC_FORCE_STEREO
mdefine_line|#define EN_BTSC_FORCE_STEREO    1
DECL|macro|EN_BTSC_FORCE_SAP
mdefine_line|#define EN_BTSC_FORCE_SAP       2
DECL|macro|EN_BTSC_AUTO_STEREO
mdefine_line|#define EN_BTSC_AUTO_STEREO     3
DECL|macro|EN_BTSC_AUTO_SAP
mdefine_line|#define EN_BTSC_AUTO_SAP        4
DECL|macro|EN_A2_FORCE_MONO1
mdefine_line|#define EN_A2_FORCE_MONO1       8
DECL|macro|EN_A2_FORCE_MONO2
mdefine_line|#define EN_A2_FORCE_MONO2       9
DECL|macro|EN_A2_FORCE_STEREO
mdefine_line|#define EN_A2_FORCE_STEREO      10
DECL|macro|EN_A2_AUTO_MONO2
mdefine_line|#define EN_A2_AUTO_MONO2        11
DECL|macro|EN_A2_AUTO_STEREO
mdefine_line|#define EN_A2_AUTO_STEREO       12
DECL|macro|EN_EIAJ_FORCE_MONO1
mdefine_line|#define EN_EIAJ_FORCE_MONO1     16
DECL|macro|EN_EIAJ_FORCE_MONO2
mdefine_line|#define EN_EIAJ_FORCE_MONO2     17
DECL|macro|EN_EIAJ_FORCE_STEREO
mdefine_line|#define EN_EIAJ_FORCE_STEREO    18
DECL|macro|EN_EIAJ_AUTO_MONO2
mdefine_line|#define EN_EIAJ_AUTO_MONO2      19
DECL|macro|EN_EIAJ_AUTO_STEREO
mdefine_line|#define EN_EIAJ_AUTO_STEREO     20
DECL|macro|EN_NICAM_FORCE_MONO1
mdefine_line|#define EN_NICAM_FORCE_MONO1    32
DECL|macro|EN_NICAM_FORCE_MONO2
mdefine_line|#define EN_NICAM_FORCE_MONO2    33
DECL|macro|EN_NICAM_FORCE_STEREO
mdefine_line|#define EN_NICAM_FORCE_STEREO   34
DECL|macro|EN_NICAM_AUTO_MONO2
mdefine_line|#define EN_NICAM_AUTO_MONO2     35
DECL|macro|EN_NICAM_AUTO_STEREO
mdefine_line|#define EN_NICAM_AUTO_STEREO    36
DECL|macro|EN_FMRADIO_FORCE_MONO
mdefine_line|#define EN_FMRADIO_FORCE_MONO   24
DECL|macro|EN_FMRADIO_FORCE_STEREO
mdefine_line|#define EN_FMRADIO_FORCE_STEREO 25
DECL|macro|EN_FMRADIO_AUTO_STEREO
mdefine_line|#define EN_FMRADIO_AUTO_STEREO  26
DECL|macro|EN_NICAM_AUTO_FALLBACK
mdefine_line|#define EN_NICAM_AUTO_FALLBACK  0x00000040
DECL|macro|EN_FMRADIO_EN_RDS
mdefine_line|#define EN_FMRADIO_EN_RDS       0x00000200
DECL|macro|EN_NICAM_TRY_AGAIN_BIT
mdefine_line|#define EN_NICAM_TRY_AGAIN_BIT  0x00000400
DECL|macro|EN_DAC_ENABLE
mdefine_line|#define EN_DAC_ENABLE           0x00001000
DECL|macro|EN_I2SOUT_ENABLE
mdefine_line|#define EN_I2SOUT_ENABLE        0x00002000
DECL|macro|EN_I2SIN_STR2DAC
mdefine_line|#define EN_I2SIN_STR2DAC        0x00004000
DECL|macro|EN_I2SIN_ENABLE
mdefine_line|#define EN_I2SIN_ENABLE         0x00008000
macro_line|#if 0
multiline_comment|/* old */
mdefine_line|#define EN_DMTRX_SUMDIFF        0x00000800
mdefine_line|#define EN_DMTRX_SUMR           0x00000880
mdefine_line|#define EN_DMTRX_LR             0x00000900
mdefine_line|#define EN_DMTRX_MONO           0x00000980
macro_line|#else
multiline_comment|/* dscaler cvs */
DECL|macro|EN_DMTRX_SUMDIFF
mdefine_line|#define EN_DMTRX_SUMDIFF        (0 &lt;&lt; 7)
DECL|macro|EN_DMTRX_SUMR
mdefine_line|#define EN_DMTRX_SUMR           (1 &lt;&lt; 7)
DECL|macro|EN_DMTRX_LR
mdefine_line|#define EN_DMTRX_LR             (2 &lt;&lt; 7)
DECL|macro|EN_DMTRX_MONO
mdefine_line|#define EN_DMTRX_MONO           (3 &lt;&lt; 7)
DECL|macro|EN_DMTRX_BYPASS
mdefine_line|#define EN_DMTRX_BYPASS         (1 &lt;&lt; 11)
macro_line|#endif
singleline_comment|// Video
DECL|macro|VID_CAPTURE_CONTROL
mdefine_line|#define VID_CAPTURE_CONTROL&t;&t;0x310180
DECL|macro|CX23880_CAP_CTL_CAPTURE_VBI_ODD
mdefine_line|#define CX23880_CAP_CTL_CAPTURE_VBI_ODD  (1&lt;&lt;3)
DECL|macro|CX23880_CAP_CTL_CAPTURE_VBI_EVEN
mdefine_line|#define CX23880_CAP_CTL_CAPTURE_VBI_EVEN (1&lt;&lt;2)
DECL|macro|CX23880_CAP_CTL_CAPTURE_ODD
mdefine_line|#define CX23880_CAP_CTL_CAPTURE_ODD      (1&lt;&lt;1)
DECL|macro|CX23880_CAP_CTL_CAPTURE_EVEN
mdefine_line|#define CX23880_CAP_CTL_CAPTURE_EVEN     (1&lt;&lt;0)
DECL|macro|VideoInputMux0
mdefine_line|#define VideoInputMux0&t;&t; 0x0
DECL|macro|VideoInputMux1
mdefine_line|#define VideoInputMux1&t;&t; 0x1
DECL|macro|VideoInputMux2
mdefine_line|#define VideoInputMux2&t;&t; 0x2
DECL|macro|VideoInputMux3
mdefine_line|#define VideoInputMux3&t;&t; 0x3
DECL|macro|VideoInputTuner
mdefine_line|#define VideoInputTuner&t;&t; 0x0
DECL|macro|VideoInputComposite
mdefine_line|#define VideoInputComposite&t; 0x1
DECL|macro|VideoInputSVideo
mdefine_line|#define VideoInputSVideo&t; 0x2
DECL|macro|VideoInputOther
mdefine_line|#define VideoInputOther&t;&t; 0x3
DECL|macro|Xtal0
mdefine_line|#define Xtal0&t;&t; 0x1
DECL|macro|Xtal1
mdefine_line|#define Xtal1&t;&t; 0x2
DECL|macro|XtalAuto
mdefine_line|#define XtalAuto&t; 0x3
DECL|macro|VideoFormatAuto
mdefine_line|#define VideoFormatAuto&t;&t; 0x0
DECL|macro|VideoFormatNTSC
mdefine_line|#define VideoFormatNTSC&t;&t; 0x1
DECL|macro|VideoFormatNTSCJapan
mdefine_line|#define VideoFormatNTSCJapan&t; 0x2
DECL|macro|VideoFormatNTSC443
mdefine_line|#define VideoFormatNTSC443&t; 0x3
DECL|macro|VideoFormatPAL
mdefine_line|#define VideoFormatPAL&t;&t; 0x4
DECL|macro|VideoFormatPALB
mdefine_line|#define VideoFormatPALB&t;&t; 0x4
DECL|macro|VideoFormatPALD
mdefine_line|#define VideoFormatPALD&t;&t; 0x4
DECL|macro|VideoFormatPALG
mdefine_line|#define VideoFormatPALG&t;&t; 0x4
DECL|macro|VideoFormatPALH
mdefine_line|#define VideoFormatPALH&t;&t; 0x4
DECL|macro|VideoFormatPALI
mdefine_line|#define VideoFormatPALI&t;&t; 0x4
DECL|macro|VideoFormatPALBDGHI
mdefine_line|#define VideoFormatPALBDGHI&t; 0x4
DECL|macro|VideoFormatPALM
mdefine_line|#define VideoFormatPALM&t;&t; 0x5
DECL|macro|VideoFormatPALN
mdefine_line|#define VideoFormatPALN&t;&t; 0x6
DECL|macro|VideoFormatPALNC
mdefine_line|#define VideoFormatPALNC&t; 0x7
DECL|macro|VideoFormatPAL60
mdefine_line|#define VideoFormatPAL60&t; 0x8
DECL|macro|VideoFormatSECAM
mdefine_line|#define VideoFormatSECAM&t; 0x9
DECL|macro|VideoFormatAuto27MHz
mdefine_line|#define VideoFormatAuto27MHz&t;&t; 0x10
DECL|macro|VideoFormatNTSC27MHz
mdefine_line|#define VideoFormatNTSC27MHz&t;&t; 0x11
DECL|macro|VideoFormatNTSCJapan27MHz
mdefine_line|#define VideoFormatNTSCJapan27MHz&t; 0x12
DECL|macro|VideoFormatNTSC44327MHz
mdefine_line|#define VideoFormatNTSC44327MHz&t;&t; 0x13
DECL|macro|VideoFormatPAL27MHz
mdefine_line|#define VideoFormatPAL27MHz&t;&t; 0x14
DECL|macro|VideoFormatPALB27MHz
mdefine_line|#define VideoFormatPALB27MHz&t;&t; 0x14
DECL|macro|VideoFormatPALD27MHz
mdefine_line|#define VideoFormatPALD27MHz&t;&t; 0x14
DECL|macro|VideoFormatPALG27MHz
mdefine_line|#define VideoFormatPALG27MHz&t;&t; 0x14
DECL|macro|VideoFormatPALH27MHz
mdefine_line|#define VideoFormatPALH27MHz&t;&t; 0x14
DECL|macro|VideoFormatPALI27MHz
mdefine_line|#define VideoFormatPALI27MHz&t;&t; 0x14
DECL|macro|VideoFormatPALBDGHI27MHz
mdefine_line|#define VideoFormatPALBDGHI27MHz&t; 0x14
DECL|macro|VideoFormatPALM27MHz
mdefine_line|#define VideoFormatPALM27MHz&t;&t; 0x15
DECL|macro|VideoFormatPALN27MHz
mdefine_line|#define VideoFormatPALN27MHz&t;&t; 0x16
DECL|macro|VideoFormatPALNC27MHz
mdefine_line|#define VideoFormatPALNC27MHz&t;&t; 0x17
DECL|macro|VideoFormatPAL6027MHz
mdefine_line|#define VideoFormatPAL6027MHz&t;&t; 0x18
DECL|macro|VideoFormatSECAM27MHz
mdefine_line|#define VideoFormatSECAM27MHz&t;&t; 0x19
DECL|macro|NominalUSECAM
mdefine_line|#define NominalUSECAM&t; 0x87
DECL|macro|NominalVSECAM
mdefine_line|#define NominalVSECAM&t; 0x85
DECL|macro|NominalUNTSC
mdefine_line|#define NominalUNTSC&t; 0xFE
DECL|macro|NominalVNTSC
mdefine_line|#define NominalVNTSC&t; 0xB4
DECL|macro|NominalContrast
mdefine_line|#define NominalContrast  0xD8
DECL|macro|HFilterAutoFormat
mdefine_line|#define HFilterAutoFormat&t; 0x0
DECL|macro|HFilterCIF
mdefine_line|#define HFilterCIF&t;&t; 0x1
DECL|macro|HFilterQCIF
mdefine_line|#define HFilterQCIF&t;&t; 0x2
DECL|macro|HFilterICON
mdefine_line|#define HFilterICON&t;&t; 0x3
DECL|macro|VFilter2TapInterpolate
mdefine_line|#define VFilter2TapInterpolate  0
DECL|macro|VFilter3TapInterpolate
mdefine_line|#define VFilter3TapInterpolate  1
DECL|macro|VFilter4TapInterpolate
mdefine_line|#define VFilter4TapInterpolate  2
DECL|macro|VFilter5TapInterpolate
mdefine_line|#define VFilter5TapInterpolate  3
DECL|macro|VFilter2TapNoInterpolate
mdefine_line|#define VFilter2TapNoInterpolate  4
DECL|macro|VFilter3TapNoInterpolate
mdefine_line|#define VFilter3TapNoInterpolate  5
DECL|macro|VFilter4TapNoInterpolate
mdefine_line|#define VFilter4TapNoInterpolate  6
DECL|macro|VFilter5TapNoInterpolate
mdefine_line|#define VFilter5TapNoInterpolate  7
DECL|macro|ColorFormatRGB32
mdefine_line|#define ColorFormatRGB32&t; 0x0000
DECL|macro|ColorFormatRGB24
mdefine_line|#define ColorFormatRGB24&t; 0x0011
DECL|macro|ColorFormatRGB16
mdefine_line|#define ColorFormatRGB16&t; 0x0022
DECL|macro|ColorFormatRGB15
mdefine_line|#define ColorFormatRGB15&t; 0x0033
DECL|macro|ColorFormatYUY2
mdefine_line|#define ColorFormatYUY2&t;&t; 0x0044
DECL|macro|ColorFormatBTYUV
mdefine_line|#define ColorFormatBTYUV&t; 0x0055
DECL|macro|ColorFormatY8
mdefine_line|#define ColorFormatY8&t;&t; 0x0066
DECL|macro|ColorFormatRGB8
mdefine_line|#define ColorFormatRGB8&t;&t; 0x0077
DECL|macro|ColorFormatPL422
mdefine_line|#define ColorFormatPL422&t; 0x0088
DECL|macro|ColorFormatPL411
mdefine_line|#define ColorFormatPL411&t; 0x0099
DECL|macro|ColorFormatYUV12
mdefine_line|#define ColorFormatYUV12&t; 0x00AA
DECL|macro|ColorFormatYUV9
mdefine_line|#define ColorFormatYUV9&t;&t; 0x00BB
DECL|macro|ColorFormatRAW
mdefine_line|#define ColorFormatRAW&t;&t; 0x00EE
DECL|macro|ColorFormatBSWAP
mdefine_line|#define ColorFormatBSWAP         0x0300
DECL|macro|ColorFormatWSWAP
mdefine_line|#define ColorFormatWSWAP         0x0c00
DECL|macro|ColorFormatEvenMask
mdefine_line|#define ColorFormatEvenMask      0x050f
DECL|macro|ColorFormatOddMask
mdefine_line|#define ColorFormatOddMask       0x0af0
DECL|macro|ColorFormatGamma
mdefine_line|#define ColorFormatGamma         0x1000
DECL|macro|Interlaced
mdefine_line|#define Interlaced&t;&t; 0x1
DECL|macro|NonInterlaced
mdefine_line|#define NonInterlaced&t; &t; 0x0
DECL|macro|FieldEven
mdefine_line|#define FieldEven&t;&t; 0x1
DECL|macro|FieldOdd
mdefine_line|#define FieldOdd&t;&t; 0x0
DECL|macro|TGReadWriteMode
mdefine_line|#define TGReadWriteMode&t; &t; 0x0
DECL|macro|TGEnableMode
mdefine_line|#define TGEnableMode&t; &t; 0x1
DECL|macro|DV_CbAlign
mdefine_line|#define DV_CbAlign&t;&t; 0x0
DECL|macro|DV_Y0Align
mdefine_line|#define DV_Y0Align&t;&t; 0x1
DECL|macro|DV_CrAlign
mdefine_line|#define DV_CrAlign&t;&t; 0x2
DECL|macro|DV_Y1Align
mdefine_line|#define DV_Y1Align&t;&t; 0x3
DECL|macro|DVF_Analog
mdefine_line|#define DVF_Analog&t;&t; 0x0
DECL|macro|DVF_CCIR656
mdefine_line|#define DVF_CCIR656&t;&t; 0x1
DECL|macro|DVF_ByteStream
mdefine_line|#define DVF_ByteStream&t;&t; 0x2
DECL|macro|DVF_ExtVSYNC
mdefine_line|#define DVF_ExtVSYNC&t;&t; 0x4
DECL|macro|DVF_ExtField
mdefine_line|#define DVF_ExtField&t;&t; 0x5
DECL|macro|CHANNEL_VID_Y
mdefine_line|#define CHANNEL_VID_Y&t;&t; 0x1
DECL|macro|CHANNEL_VID_U
mdefine_line|#define CHANNEL_VID_U&t;&t; 0x2
DECL|macro|CHANNEL_VID_V
mdefine_line|#define CHANNEL_VID_V&t;&t; 0x3
DECL|macro|CHANNEL_VID_VBI
mdefine_line|#define CHANNEL_VID_VBI&t;&t; 0x4
DECL|macro|CHANNEL_AUD_DN
mdefine_line|#define CHANNEL_AUD_DN&t;&t; 0x5
DECL|macro|CHANNEL_AUD_UP
mdefine_line|#define CHANNEL_AUD_UP&t;&t; 0x6
DECL|macro|CHANNEL_AUD_RDS_DN
mdefine_line|#define CHANNEL_AUD_RDS_DN&t; 0x7
DECL|macro|CHANNEL_MPEG_DN
mdefine_line|#define CHANNEL_MPEG_DN&t;&t; 0x8
DECL|macro|CHANNEL_VIP_DN
mdefine_line|#define CHANNEL_VIP_DN&t;&t; 0x9
DECL|macro|CHANNEL_VIP_UP
mdefine_line|#define CHANNEL_VIP_UP&t;&t; 0xA
DECL|macro|CHANNEL_HOST_DN
mdefine_line|#define CHANNEL_HOST_DN&t;&t; 0xB
DECL|macro|CHANNEL_HOST_UP
mdefine_line|#define CHANNEL_HOST_UP&t;&t; 0xC
DECL|macro|CHANNEL_FIRST
mdefine_line|#define CHANNEL_FIRST&t;&t; 0x1
DECL|macro|CHANNEL_LAST
mdefine_line|#define CHANNEL_LAST&t;&t; 0xC
DECL|macro|GP_COUNT_CONTROL_NONE
mdefine_line|#define GP_COUNT_CONTROL_NONE&t;&t; 0x0
DECL|macro|GP_COUNT_CONTROL_INC
mdefine_line|#define GP_COUNT_CONTROL_INC&t;&t; 0x1
DECL|macro|GP_COUNT_CONTROL_RESERVED
mdefine_line|#define GP_COUNT_CONTROL_RESERVED&t; 0x2
DECL|macro|GP_COUNT_CONTROL_RESET
mdefine_line|#define GP_COUNT_CONTROL_RESET&t;&t; 0x3
DECL|macro|PLL_PRESCALE_BY_2
mdefine_line|#define PLL_PRESCALE_BY_2  2
DECL|macro|PLL_PRESCALE_BY_3
mdefine_line|#define PLL_PRESCALE_BY_3  3
DECL|macro|PLL_PRESCALE_BY_4
mdefine_line|#define PLL_PRESCALE_BY_4  4
DECL|macro|PLL_PRESCALE_BY_5
mdefine_line|#define PLL_PRESCALE_BY_5  5
DECL|macro|HLNotchFilter4xFsc
mdefine_line|#define HLNotchFilter4xFsc&t; 0
DECL|macro|HLNotchFilterSquare
mdefine_line|#define HLNotchFilterSquare&t; 1
DECL|macro|HLNotchFilter135NTSC
mdefine_line|#define HLNotchFilter135NTSC&t; 2
DECL|macro|HLNotchFilter135PAL
mdefine_line|#define HLNotchFilter135PAL&t; 3
DECL|macro|NTSC_8x_SUB_CARRIER
mdefine_line|#define NTSC_8x_SUB_CARRIER  28.63636E6
DECL|macro|PAL_8x_SUB_CARRIER
mdefine_line|#define PAL_8x_SUB_CARRIER  35.46895E6
singleline_comment|// Default analog settings
DECL|macro|DEFAULT_HUE_NTSC
mdefine_line|#define DEFAULT_HUE_NTSC&t;&t;&t;0x00
DECL|macro|DEFAULT_BRIGHTNESS_NTSC
mdefine_line|#define DEFAULT_BRIGHTNESS_NTSC&t;&t;&t;0x00
DECL|macro|DEFAULT_CONTRAST_NTSC
mdefine_line|#define DEFAULT_CONTRAST_NTSC&t;&t;&t;0x39
DECL|macro|DEFAULT_SAT_U_NTSC
mdefine_line|#define DEFAULT_SAT_U_NTSC&t;&t;&t;0x7F
DECL|macro|DEFAULT_SAT_V_NTSC
mdefine_line|#define DEFAULT_SAT_V_NTSC&t;&t;&t;0x5A
r_typedef
r_enum
(brace
DECL|enumerator|SOURCE_TUNER
id|SOURCE_TUNER
op_assign
l_int|0
comma
DECL|enumerator|SOURCE_COMPOSITE
id|SOURCE_COMPOSITE
comma
DECL|enumerator|SOURCE_SVIDEO
id|SOURCE_SVIDEO
comma
DECL|enumerator|SOURCE_OTHER1
id|SOURCE_OTHER1
comma
DECL|enumerator|SOURCE_OTHER2
id|SOURCE_OTHER2
comma
DECL|enumerator|SOURCE_COMPVIASVIDEO
id|SOURCE_COMPVIASVIDEO
comma
DECL|enumerator|SOURCE_CCIR656
id|SOURCE_CCIR656
DECL|typedef|VIDEOSOURCETYPE
)brace
id|VIDEOSOURCETYPE
suffix:semicolon
macro_line|#endif /* _CX88_REG_H_ */
eof
