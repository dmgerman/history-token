multiline_comment|/*-*- linux-c -*-&n; *  linux/drivers/video/i810_regs.h -- Intel 810/815 Register List&n; *&n; *      Copyright (C) 2001 Antonino Daplas&lt;adaplas@pol.net&gt;&n; *      All Rights Reserved      &n; *&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
multiline_comment|/*&n; * Intel 810 Chipset Family PRM 15 3.1 &n; * GC Register Memory Address Map &n; *&n; * Based on:&n; * Intel (R) 810 Chipset Family &n; * Programmer s Reference Manual &n; * November 1999 &n; * Revision 1.0 &n; * Order Number: 298026-001 R&n; *&n; * All GC registers are memory-mapped. In addition, the VGA and extended VGA registers &n; * are I/O mapped. &n; */
macro_line|#ifndef __I810_REGS_H__
DECL|macro|__I810_REGS_H__
mdefine_line|#define __I810_REGS_H__
multiline_comment|/*  Instruction and Interrupt Control Registers (01000h 02FFFh) */
DECL|macro|FENCE
mdefine_line|#define FENCE                 0x02000                
DECL|macro|PGTBL_CTL
mdefine_line|#define PGTBL_CTL             0x02020 
DECL|macro|PGTBL_ER
mdefine_line|#define PGTBL_ER              0x02024               
DECL|macro|LRING
mdefine_line|#define    LRING              0x02030
DECL|macro|IRING
mdefine_line|#define    IRING              0x02040
DECL|macro|HWS_PGA
mdefine_line|#define HWS_PGA               0x02080 
DECL|macro|IPEIR
mdefine_line|#define IPEIR                 0x02088
DECL|macro|IPEHR
mdefine_line|#define IPEHR                 0x0208C 
DECL|macro|INSTDONE
mdefine_line|#define INSTDONE              0x02090 
DECL|macro|NOPID
mdefine_line|#define NOPID                 0x02094
DECL|macro|HWSTAM
mdefine_line|#define HWSTAM                0x02098 
DECL|macro|IER
mdefine_line|#define IER                   0x020A0
DECL|macro|IIR
mdefine_line|#define IIR                   0x020A4
DECL|macro|IMR
mdefine_line|#define IMR                   0x020A8 
DECL|macro|ISR
mdefine_line|#define ISR                   0x020AC 
DECL|macro|EIR
mdefine_line|#define EIR                   0x020B0 
DECL|macro|EMR
mdefine_line|#define EMR                   0x020B4 
DECL|macro|ESR
mdefine_line|#define ESR                   0x020B8 
DECL|macro|INSTPM
mdefine_line|#define INSTPM                0x020C0
DECL|macro|INSTPS
mdefine_line|#define INSTPS                0x020C4 
DECL|macro|BBP_PTR
mdefine_line|#define BBP_PTR               0x020C8 
DECL|macro|ABB_SRT
mdefine_line|#define ABB_SRT               0x020CC
DECL|macro|ABB_END
mdefine_line|#define ABB_END               0x020D0
DECL|macro|DMA_FADD
mdefine_line|#define DMA_FADD              0x020D4 
DECL|macro|FW_BLC
mdefine_line|#define FW_BLC                0x020D8
DECL|macro|MEM_MODE
mdefine_line|#define MEM_MODE              0x020DC        
multiline_comment|/*  Memory Control Registers (03000h 03FFFh) */
DECL|macro|DRT
mdefine_line|#define DRT                   0x03000
DECL|macro|DRAMCL
mdefine_line|#define DRAMCL                0x03001
DECL|macro|DRAMCH
mdefine_line|#define DRAMCH                0x03002
multiline_comment|/* Span Cursor Registers (04000h 04FFFh) */
DECL|macro|UI_SC_CTL
mdefine_line|#define UI_SC_CTL             0x04008 
multiline_comment|/* I/O Control Registers (05000h 05FFFh) */
DECL|macro|HVSYNC
mdefine_line|#define HVSYNC                0x05000 
DECL|macro|GPIOA
mdefine_line|#define GPIOA                 0x05010
DECL|macro|GPIOB
mdefine_line|#define GPIOB                 0x05014 
multiline_comment|/* Clock Control and Power Management Registers (06000h 06FFFh) */
DECL|macro|DCLK_0D
mdefine_line|#define DCLK_0D               0x06000
DECL|macro|DCLK_1D
mdefine_line|#define DCLK_1D               0x06004
DECL|macro|DCLK_2D
mdefine_line|#define DCLK_2D               0x06008
DECL|macro|LCD_CLKD
mdefine_line|#define LCD_CLKD              0x0600C
DECL|macro|DCLK_0DS
mdefine_line|#define DCLK_0DS              0x06010
DECL|macro|PWR_CLKC
mdefine_line|#define PWR_CLKC              0x06014
multiline_comment|/* Graphics Translation Table Range Definition (10000h 1FFFFh) */
DECL|macro|GTT
mdefine_line|#define GTT                   0x10000  
multiline_comment|/*  Overlay Registers (30000h 03FFFFh) */
DECL|macro|OVOADDR
mdefine_line|#define OVOADDR               0x30000
DECL|macro|DOVOSTA
mdefine_line|#define DOVOSTA               0x30008
DECL|macro|GAMMA
mdefine_line|#define GAMMA                 0x30010
DECL|macro|OBUF_0Y
mdefine_line|#define OBUF_0Y               0x30100
DECL|macro|OBUF_1Y
mdefine_line|#define OBUF_1Y               0x30104
DECL|macro|OBUF_0U
mdefine_line|#define OBUF_0U               0x30108
DECL|macro|OBUF_0V
mdefine_line|#define OBUF_0V               0x3010C
DECL|macro|OBUF_1U
mdefine_line|#define OBUF_1U               0x30110
DECL|macro|OBUF_1V
mdefine_line|#define OBUF_1V               0x30114 
DECL|macro|OVOSTRIDE
mdefine_line|#define OVOSTRIDE             0x30118
DECL|macro|YRGB_VPH
mdefine_line|#define YRGB_VPH              0x3011C
DECL|macro|UV_VPH
mdefine_line|#define UV_VPH                0x30120
DECL|macro|HORZ_PH
mdefine_line|#define HORZ_PH               0x30124
DECL|macro|INIT_PH
mdefine_line|#define INIT_PH               0x30128
DECL|macro|DWINPOS
mdefine_line|#define DWINPOS               0x3012C 
DECL|macro|DWINSZ
mdefine_line|#define DWINSZ                0x30130
DECL|macro|SWID
mdefine_line|#define SWID                  0x30134
DECL|macro|SWIDQW
mdefine_line|#define SWIDQW                0x30138
DECL|macro|SHEIGHT
mdefine_line|#define SHEIGHT               0x3013F
DECL|macro|YRGBSCALE
mdefine_line|#define YRGBSCALE             0x30140 
DECL|macro|UVSCALE
mdefine_line|#define UVSCALE               0x30144
DECL|macro|OVOCLRCO
mdefine_line|#define OVOCLRCO              0x30148
DECL|macro|OVOCLRC1
mdefine_line|#define OVOCLRC1              0x3014C
DECL|macro|DCLRKV
mdefine_line|#define DCLRKV                0x30150
DECL|macro|DLCRKM
mdefine_line|#define DLCRKM                0x30154
DECL|macro|SCLRKVH
mdefine_line|#define SCLRKVH               0x30158
DECL|macro|SCLRKVL
mdefine_line|#define SCLRKVL               0x3015C
DECL|macro|SCLRKM
mdefine_line|#define SCLRKM                0x30160
DECL|macro|OVOCONF
mdefine_line|#define OVOCONF               0x30164
DECL|macro|OVOCMD
mdefine_line|#define OVOCMD                0x30168
DECL|macro|AWINPOS
mdefine_line|#define AWINPOS               0x30170
DECL|macro|AWINZ
mdefine_line|#define AWINZ                 0x30174
multiline_comment|/*  BLT Engine Status (40000h 4FFFFh) (Software Debug) */
DECL|macro|BR00
mdefine_line|#define BR00                  0x40000
DECL|macro|BRO1
mdefine_line|#define BRO1                  0x40004
DECL|macro|BR02
mdefine_line|#define BR02                  0x40008
DECL|macro|BR03
mdefine_line|#define BR03                  0x4000C
DECL|macro|BR04
mdefine_line|#define BR04                  0x40010
DECL|macro|BR05
mdefine_line|#define BR05                  0x40014
DECL|macro|BR06
mdefine_line|#define BR06                  0x40018
DECL|macro|BR07
mdefine_line|#define BR07                  0x4001C
DECL|macro|BR08
mdefine_line|#define BR08                  0x40020
DECL|macro|BR09
mdefine_line|#define BR09                  0x40024
DECL|macro|BR10
mdefine_line|#define BR10                  0x40028
DECL|macro|BR11
mdefine_line|#define BR11                  0x4002C
DECL|macro|BR12
mdefine_line|#define BR12                  0x40030
DECL|macro|BR13
mdefine_line|#define BR13                  0x40034
DECL|macro|BR14
mdefine_line|#define BR14                  0x40038
DECL|macro|BR15
mdefine_line|#define BR15                  0x4003C
DECL|macro|BR16
mdefine_line|#define BR16                  0x40040
DECL|macro|BR17
mdefine_line|#define BR17                  0x40044
DECL|macro|BR18
mdefine_line|#define BR18                  0x40048
DECL|macro|BR19
mdefine_line|#define BR19                  0x4004C
DECL|macro|SSLADD
mdefine_line|#define SSLADD                0x40074
DECL|macro|DSLH
mdefine_line|#define DSLH                  0x40078
DECL|macro|DSLRADD
mdefine_line|#define DSLRADD               0x4007C
multiline_comment|/* LCD/TV-Out and HW DVD Registers (60000h 6FFFFh) */
multiline_comment|/* LCD/TV-Out */
DECL|macro|HTOTAL
mdefine_line|#define HTOTAL                0x60000
DECL|macro|HBLANK
mdefine_line|#define HBLANK                0x60004
DECL|macro|HSYNC
mdefine_line|#define HSYNC                 0x60008
DECL|macro|VTOTAL
mdefine_line|#define VTOTAL                0x6000C
DECL|macro|VBLANK
mdefine_line|#define VBLANK                0x60010
DECL|macro|VSYNC
mdefine_line|#define VSYNC                 0x60014
DECL|macro|LCDTV_C
mdefine_line|#define LCDTV_C               0x60018
DECL|macro|OVRACT
mdefine_line|#define OVRACT                0x6001C
DECL|macro|BCLRPAT
mdefine_line|#define BCLRPAT               0x60020
multiline_comment|/*  Display and Cursor Control Registers (70000h 7FFFFh) */
DECL|macro|DISP_SL
mdefine_line|#define DISP_SL               0x70000
DECL|macro|DISP_SLC
mdefine_line|#define DISP_SLC              0x70004
DECL|macro|PIXCONF
mdefine_line|#define PIXCONF               0x70008
DECL|macro|PIXCONF1
mdefine_line|#define PIXCONF1              0x70009
DECL|macro|BLTCNTL
mdefine_line|#define BLTCNTL               0x7000C
DECL|macro|SWF
mdefine_line|#define SWF                   0x70014
DECL|macro|DPLYBASE
mdefine_line|#define DPLYBASE              0x70020
DECL|macro|DPLYSTAS
mdefine_line|#define DPLYSTAS              0x70024
DECL|macro|CURCNTR
mdefine_line|#define CURCNTR               0x70080
DECL|macro|CURBASE
mdefine_line|#define CURBASE               0x70084
DECL|macro|CURPOS
mdefine_line|#define CURPOS                0x70088
multiline_comment|/* VGA Registers */
multiline_comment|/* SMRAM Registers */
DECL|macro|SMRAM
mdefine_line|#define SMRAM                 0x10
multiline_comment|/* Graphics Control Registers */
DECL|macro|GR_INDEX
mdefine_line|#define GR_INDEX              0x3CE
DECL|macro|GR_DATA
mdefine_line|#define GR_DATA               0x3CF
DECL|macro|GR10
mdefine_line|#define GR10                  0x10
DECL|macro|GR11
mdefine_line|#define GR11                  0x11
multiline_comment|/* CRT Controller Registers */
DECL|macro|CR_INDEX_MDA
mdefine_line|#define CR_INDEX_MDA          0x3B4
DECL|macro|CR_INDEX_CGA
mdefine_line|#define CR_INDEX_CGA          0x3D4
DECL|macro|CR_DATA_MDA
mdefine_line|#define CR_DATA_MDA           0x3B5
DECL|macro|CR_DATA_CGA
mdefine_line|#define CR_DATA_CGA           0x3D5
DECL|macro|CR30
mdefine_line|#define CR30                  0x30
DECL|macro|CR31
mdefine_line|#define CR31                  0x31
DECL|macro|CR32
mdefine_line|#define CR32                  0x32
DECL|macro|CR33
mdefine_line|#define CR33                  0x33
DECL|macro|CR35
mdefine_line|#define CR35                  0x35
DECL|macro|CR39
mdefine_line|#define CR39                  0x39
DECL|macro|CR40
mdefine_line|#define CR40                  0x40
DECL|macro|CR41
mdefine_line|#define CR41                  0x41
DECL|macro|CR42
mdefine_line|#define CR42                  0x42
DECL|macro|CR70
mdefine_line|#define CR70                  0x70
DECL|macro|CR80
mdefine_line|#define CR80                  0x80 
DECL|macro|CR81
mdefine_line|#define CR81                  0x82
multiline_comment|/* Extended VGA Registers */
multiline_comment|/* General Control and Status Registers */
DECL|macro|ST00
mdefine_line|#define ST00                  0x3C2
DECL|macro|ST01_MDA
mdefine_line|#define ST01_MDA              0x3BA
DECL|macro|ST01_CGA
mdefine_line|#define ST01_CGA              0x3DA
DECL|macro|FRC_READ
mdefine_line|#define FRC_READ              0x3CA
DECL|macro|FRC_WRITE_MDA
mdefine_line|#define FRC_WRITE_MDA         0x3BA
DECL|macro|FRC_WRITE_CGA
mdefine_line|#define FRC_WRITE_CGA         0x3DA
DECL|macro|MSR_READ
mdefine_line|#define MSR_READ              0x3CC
DECL|macro|MSR_WRITE
mdefine_line|#define MSR_WRITE             0x3C2
multiline_comment|/* Sequencer Registers */
DECL|macro|SR_INDEX
mdefine_line|#define SR_INDEX              0x3C4
DECL|macro|SR_DATA
mdefine_line|#define SR_DATA               0x3C5
DECL|macro|SR01
mdefine_line|#define SR01                  0x01
DECL|macro|SR02
mdefine_line|#define SR02                  0x02
DECL|macro|SR03
mdefine_line|#define SR03                  0x03
DECL|macro|SR04
mdefine_line|#define SR04                  0x04
DECL|macro|SR07
mdefine_line|#define SR07                  0x07
multiline_comment|/* Graphics Controller Registers */
DECL|macro|GR00
mdefine_line|#define GR00                  0x00   
DECL|macro|GR01
mdefine_line|#define GR01                  0x01
DECL|macro|GR02
mdefine_line|#define GR02                  0x02
DECL|macro|GR03
mdefine_line|#define GR03                  0x03
DECL|macro|GR04
mdefine_line|#define GR04                  0x04
DECL|macro|GR05
mdefine_line|#define GR05                  0x05
DECL|macro|GR06
mdefine_line|#define GR06                  0x06
DECL|macro|GR07
mdefine_line|#define GR07                  0x07
DECL|macro|GR08
mdefine_line|#define GR08                  0x08  
multiline_comment|/* Attribute Controller Registers */
DECL|macro|ATTR_WRITE
mdefine_line|#define ATTR_WRITE              0x3C0
DECL|macro|ATTR_READ
mdefine_line|#define ATTR_READ               0x3C1
multiline_comment|/* VGA Color Palette Registers */
multiline_comment|/* CLUT */
DECL|macro|CLUT_DATA
mdefine_line|#define CLUT_DATA             0x3C9        /* DACDATA */
DECL|macro|CLUT_INDEX_READ
mdefine_line|#define CLUT_INDEX_READ       0x3C7        /* DACRX */
DECL|macro|CLUT_INDEX_WRITE
mdefine_line|#define CLUT_INDEX_WRITE      0x3C8        /* DACWX */
DECL|macro|DACMASK
mdefine_line|#define DACMASK               0x3C6
multiline_comment|/* CRT Controller Registers */
DECL|macro|CR00
mdefine_line|#define CR00                  0x00
DECL|macro|CR01
mdefine_line|#define CR01                  0x01
DECL|macro|CR02
mdefine_line|#define CR02                  0x02
DECL|macro|CR03
mdefine_line|#define CR03                  0x03
DECL|macro|CR04
mdefine_line|#define CR04                  0x04
DECL|macro|CR05
mdefine_line|#define CR05                  0x05
DECL|macro|CR06
mdefine_line|#define CR06                  0x06
DECL|macro|CR07
mdefine_line|#define CR07                  0x07
DECL|macro|CR08
mdefine_line|#define CR08                  0x08
DECL|macro|CR09
mdefine_line|#define CR09                  0x09
DECL|macro|CR0A
mdefine_line|#define CR0A                  0x0A
DECL|macro|CR0B
mdefine_line|#define CR0B                  0x0B
DECL|macro|CR0C
mdefine_line|#define CR0C                  0x0C
DECL|macro|CR0D
mdefine_line|#define CR0D                  0x0D
DECL|macro|CR0E
mdefine_line|#define CR0E                  0x0E
DECL|macro|CR0F
mdefine_line|#define CR0F                  0x0F
DECL|macro|CR10
mdefine_line|#define CR10                  0x10
DECL|macro|CR11
mdefine_line|#define CR11                  0x11
DECL|macro|CR12
mdefine_line|#define CR12                  0x12
DECL|macro|CR13
mdefine_line|#define CR13                  0x13
DECL|macro|CR14
mdefine_line|#define CR14                  0x14
DECL|macro|CR15
mdefine_line|#define CR15                  0x15
DECL|macro|CR16
mdefine_line|#define CR16                  0x16
DECL|macro|CR17
mdefine_line|#define CR17                  0x17
DECL|macro|CR18
mdefine_line|#define CR18                  0x18
macro_line|#endif /* __I810_REGS_H__ */
eof
