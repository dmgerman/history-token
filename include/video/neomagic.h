multiline_comment|/*&n; * linux/include/video/neo_reg.h -- NeoMagic Framebuffer Driver&n; *&n; * Copyright (c) 2001  Denis Oliver Kropp &lt;dok@convergence.de&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; */
DECL|macro|NEO_BS0_BLT_BUSY
mdefine_line|#define NEO_BS0_BLT_BUSY        0x00000001
DECL|macro|NEO_BS0_FIFO_AVAIL
mdefine_line|#define NEO_BS0_FIFO_AVAIL      0x00000002
DECL|macro|NEO_BS0_FIFO_PEND
mdefine_line|#define NEO_BS0_FIFO_PEND       0x00000004
DECL|macro|NEO_BC0_DST_Y_DEC
mdefine_line|#define NEO_BC0_DST_Y_DEC       0x00000001
DECL|macro|NEO_BC0_X_DEC
mdefine_line|#define NEO_BC0_X_DEC           0x00000002
DECL|macro|NEO_BC0_SRC_TRANS
mdefine_line|#define NEO_BC0_SRC_TRANS       0x00000004
DECL|macro|NEO_BC0_SRC_IS_FG
mdefine_line|#define NEO_BC0_SRC_IS_FG       0x00000008
DECL|macro|NEO_BC0_SRC_Y_DEC
mdefine_line|#define NEO_BC0_SRC_Y_DEC       0x00000010
DECL|macro|NEO_BC0_FILL_PAT
mdefine_line|#define NEO_BC0_FILL_PAT        0x00000020
DECL|macro|NEO_BC0_SRC_MONO
mdefine_line|#define NEO_BC0_SRC_MONO        0x00000040
DECL|macro|NEO_BC0_SYS_TO_VID
mdefine_line|#define NEO_BC0_SYS_TO_VID      0x00000080
DECL|macro|NEO_BC1_DEPTH8
mdefine_line|#define NEO_BC1_DEPTH8          0x00000100
DECL|macro|NEO_BC1_DEPTH16
mdefine_line|#define NEO_BC1_DEPTH16         0x00000200
DECL|macro|NEO_BC1_X_320
mdefine_line|#define NEO_BC1_X_320           0x00000400
DECL|macro|NEO_BC1_X_640
mdefine_line|#define NEO_BC1_X_640           0x00000800
DECL|macro|NEO_BC1_X_800
mdefine_line|#define NEO_BC1_X_800           0x00000c00
DECL|macro|NEO_BC1_X_1024
mdefine_line|#define NEO_BC1_X_1024          0x00001000
DECL|macro|NEO_BC1_X_1152
mdefine_line|#define NEO_BC1_X_1152          0x00001400
DECL|macro|NEO_BC1_X_1280
mdefine_line|#define NEO_BC1_X_1280          0x00001800
DECL|macro|NEO_BC1_X_1600
mdefine_line|#define NEO_BC1_X_1600          0x00001c00
DECL|macro|NEO_BC1_DST_TRANS
mdefine_line|#define NEO_BC1_DST_TRANS       0x00002000
DECL|macro|NEO_BC1_MSTR_BLT
mdefine_line|#define NEO_BC1_MSTR_BLT        0x00004000
DECL|macro|NEO_BC1_FILTER_Z
mdefine_line|#define NEO_BC1_FILTER_Z        0x00008000
DECL|macro|NEO_BC2_WR_TR_DST
mdefine_line|#define NEO_BC2_WR_TR_DST       0x00800000
DECL|macro|NEO_BC3_SRC_XY_ADDR
mdefine_line|#define NEO_BC3_SRC_XY_ADDR     0x01000000
DECL|macro|NEO_BC3_DST_XY_ADDR
mdefine_line|#define NEO_BC3_DST_XY_ADDR     0x02000000
DECL|macro|NEO_BC3_CLIP_ON
mdefine_line|#define NEO_BC3_CLIP_ON         0x04000000
DECL|macro|NEO_BC3_FIFO_EN
mdefine_line|#define NEO_BC3_FIFO_EN         0x08000000
DECL|macro|NEO_BC3_BLT_ON_ADDR
mdefine_line|#define NEO_BC3_BLT_ON_ADDR     0x10000000
DECL|macro|NEO_BC3_SKIP_MAPPING
mdefine_line|#define NEO_BC3_SKIP_MAPPING    0x80000000
DECL|macro|NEO_MODE1_DEPTH8
mdefine_line|#define NEO_MODE1_DEPTH8        0x0100
DECL|macro|NEO_MODE1_DEPTH16
mdefine_line|#define NEO_MODE1_DEPTH16       0x0200
DECL|macro|NEO_MODE1_DEPTH24
mdefine_line|#define NEO_MODE1_DEPTH24       0x0300
DECL|macro|NEO_MODE1_X_320
mdefine_line|#define NEO_MODE1_X_320         0x0400
DECL|macro|NEO_MODE1_X_640
mdefine_line|#define NEO_MODE1_X_640         0x0800
DECL|macro|NEO_MODE1_X_800
mdefine_line|#define NEO_MODE1_X_800         0x0c00
DECL|macro|NEO_MODE1_X_1024
mdefine_line|#define NEO_MODE1_X_1024        0x1000
DECL|macro|NEO_MODE1_X_1152
mdefine_line|#define NEO_MODE1_X_1152        0x1400
DECL|macro|NEO_MODE1_X_1280
mdefine_line|#define NEO_MODE1_X_1280        0x1800
DECL|macro|NEO_MODE1_X_1600
mdefine_line|#define NEO_MODE1_X_1600        0x1c00
DECL|macro|NEO_MODE1_BLT_ON_ADDR
mdefine_line|#define NEO_MODE1_BLT_ON_ADDR   0x2000
multiline_comment|/* These are offseted in MMIO space by par-&gt;CursorOff */
DECL|macro|NEOREG_CURSCNTL
mdefine_line|#define NEOREG_CURSCNTL&t;&t;0x00
DECL|macro|NEOREG_CURSX
mdefine_line|#define NEOREG_CURSX&t;&t;0x04
DECL|macro|NEOREG_CURSY
mdefine_line|#define NEOREG_CURSY&t;&t;0x08
DECL|macro|NEOREG_CURSBGCOLOR
mdefine_line|#define NEOREG_CURSBGCOLOR&t;0x0C
DECL|macro|NEOREG_CURSFGCOLOR
mdefine_line|#define NEOREG_CURSFGCOLOR&t;0x10
DECL|macro|NEOREG_CURSMEMPOS
mdefine_line|#define NEOREG_CURSMEMPOS&t;0x14
DECL|macro|NEO_CURS_DISABLE
mdefine_line|#define NEO_CURS_DISABLE&t;0x00000000
DECL|macro|NEO_CURS_ENABLE
mdefine_line|#define NEO_CURS_ENABLE&t;&t;0x00000001
DECL|macro|NEO_ICON64_ENABLE
mdefine_line|#define NEO_ICON64_ENABLE&t;0x00000008
DECL|macro|NEO_ICON128_ENABLE
mdefine_line|#define NEO_ICON128_ENABLE&t;0x0000000C
DECL|macro|NEO_ICON_BLANK
mdefine_line|#define NEO_ICON_BLANK&t;&t;0x00000010
DECL|macro|NEO_GR01_SUPPRESS_VSYNC
mdefine_line|#define NEO_GR01_SUPPRESS_VSYNC 0x10
DECL|macro|NEO_GR01_SUPPRESS_HSYNC
mdefine_line|#define NEO_GR01_SUPPRESS_HSYNC 0x20
macro_line|#ifdef __KERNEL__
macro_line|#ifdef NEOFB_DEBUG
DECL|macro|DBG
macro_line|# define DBG(x)&t;&t;printk (KERN_DEBUG &quot;neofb: %s&bslash;n&quot;, (x));
macro_line|#else
DECL|macro|DBG
macro_line|# define DBG(x)
macro_line|#endif
DECL|macro|PCI_CHIP_NM2070
mdefine_line|#define PCI_CHIP_NM2070 0x0001
DECL|macro|PCI_CHIP_NM2090
mdefine_line|#define PCI_CHIP_NM2090 0x0002
DECL|macro|PCI_CHIP_NM2093
mdefine_line|#define PCI_CHIP_NM2093 0x0003
DECL|macro|PCI_CHIP_NM2097
mdefine_line|#define PCI_CHIP_NM2097 0x0083
DECL|macro|PCI_CHIP_NM2160
mdefine_line|#define PCI_CHIP_NM2160 0x0004
DECL|macro|PCI_CHIP_NM2200
mdefine_line|#define PCI_CHIP_NM2200 0x0005
DECL|macro|PCI_CHIP_NM2230
mdefine_line|#define PCI_CHIP_NM2230 0x0025
DECL|macro|PCI_CHIP_NM2360
mdefine_line|#define PCI_CHIP_NM2360 0x0006
DECL|macro|PCI_CHIP_NM2380
mdefine_line|#define PCI_CHIP_NM2380 0x0016
DECL|struct|xtimings
r_struct
id|xtimings
(brace
DECL|member|pixclock
r_int
r_int
id|pixclock
suffix:semicolon
DECL|member|HDisplay
r_int
r_int
id|HDisplay
suffix:semicolon
DECL|member|HSyncStart
r_int
r_int
id|HSyncStart
suffix:semicolon
DECL|member|HSyncEnd
r_int
r_int
id|HSyncEnd
suffix:semicolon
DECL|member|HTotal
r_int
r_int
id|HTotal
suffix:semicolon
DECL|member|VDisplay
r_int
r_int
id|VDisplay
suffix:semicolon
DECL|member|VSyncStart
r_int
r_int
id|VSyncStart
suffix:semicolon
DECL|member|VSyncEnd
r_int
r_int
id|VSyncEnd
suffix:semicolon
DECL|member|VTotal
r_int
r_int
id|VTotal
suffix:semicolon
DECL|member|sync
r_int
r_int
id|sync
suffix:semicolon
DECL|member|dblscan
r_int
id|dblscan
suffix:semicolon
DECL|member|interlaced
r_int
id|interlaced
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
r_typedef
r_volatile
r_struct
(brace
DECL|member|bltStat
id|__u32
id|bltStat
suffix:semicolon
DECL|member|bltCntl
id|__u32
id|bltCntl
suffix:semicolon
DECL|member|xpColor
id|__u32
id|xpColor
suffix:semicolon
DECL|member|fgColor
id|__u32
id|fgColor
suffix:semicolon
DECL|member|bgColor
id|__u32
id|bgColor
suffix:semicolon
DECL|member|pitch
id|__u32
id|pitch
suffix:semicolon
DECL|member|clipLT
id|__u32
id|clipLT
suffix:semicolon
DECL|member|clipRB
id|__u32
id|clipRB
suffix:semicolon
DECL|member|srcBitOffset
id|__u32
id|srcBitOffset
suffix:semicolon
DECL|member|srcStart
id|__u32
id|srcStart
suffix:semicolon
DECL|member|reserved0
id|__u32
id|reserved0
suffix:semicolon
DECL|member|dstStart
id|__u32
id|dstStart
suffix:semicolon
DECL|member|xyExt
id|__u32
id|xyExt
suffix:semicolon
DECL|member|reserved1
id|__u32
id|reserved1
(braket
l_int|19
)braket
suffix:semicolon
DECL|member|pageCntl
id|__u32
id|pageCntl
suffix:semicolon
DECL|member|pageBase
id|__u32
id|pageBase
suffix:semicolon
DECL|member|postBase
id|__u32
id|postBase
suffix:semicolon
DECL|member|postPtr
id|__u32
id|postPtr
suffix:semicolon
DECL|member|dataPtr
id|__u32
id|dataPtr
suffix:semicolon
DECL|typedef|Neo2200
)brace
id|Neo2200
suffix:semicolon
DECL|macro|MMIO_SIZE
mdefine_line|#define MMIO_SIZE 0x200000
DECL|macro|NEO_EXT_CR_MAX
mdefine_line|#define NEO_EXT_CR_MAX 0x85
DECL|macro|NEO_EXT_GR_MAX
mdefine_line|#define NEO_EXT_GR_MAX 0xC7
DECL|struct|neofb_par
r_struct
id|neofb_par
(brace
DECL|member|state
r_struct
id|vgastate
id|state
suffix:semicolon
DECL|member|ref_count
id|atomic_t
id|ref_count
suffix:semicolon
DECL|member|MiscOutReg
r_int
r_char
id|MiscOutReg
suffix:semicolon
multiline_comment|/* Misc */
DECL|member|CRTC
r_int
r_char
id|CRTC
(braket
l_int|25
)braket
suffix:semicolon
multiline_comment|/* Crtc Controller */
DECL|member|Sequencer
r_int
r_char
id|Sequencer
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* Video Sequencer */
DECL|member|Graphics
r_int
r_char
id|Graphics
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* Video Graphics */
DECL|member|Attribute
r_int
r_char
id|Attribute
(braket
l_int|21
)braket
suffix:semicolon
multiline_comment|/* Video Atribute */
DECL|member|GeneralLockReg
r_int
r_char
id|GeneralLockReg
suffix:semicolon
DECL|member|ExtCRTDispAddr
r_int
r_char
id|ExtCRTDispAddr
suffix:semicolon
DECL|member|ExtCRTOffset
r_int
r_char
id|ExtCRTOffset
suffix:semicolon
DECL|member|SysIfaceCntl1
r_int
r_char
id|SysIfaceCntl1
suffix:semicolon
DECL|member|SysIfaceCntl2
r_int
r_char
id|SysIfaceCntl2
suffix:semicolon
DECL|member|ExtColorModeSelect
r_int
r_char
id|ExtColorModeSelect
suffix:semicolon
DECL|member|biosMode
r_int
r_char
id|biosMode
suffix:semicolon
DECL|member|PanelDispCntlReg1
r_int
r_char
id|PanelDispCntlReg1
suffix:semicolon
DECL|member|PanelDispCntlReg2
r_int
r_char
id|PanelDispCntlReg2
suffix:semicolon
DECL|member|PanelDispCntlReg3
r_int
r_char
id|PanelDispCntlReg3
suffix:semicolon
DECL|member|PanelVertCenterReg1
r_int
r_char
id|PanelVertCenterReg1
suffix:semicolon
DECL|member|PanelVertCenterReg2
r_int
r_char
id|PanelVertCenterReg2
suffix:semicolon
DECL|member|PanelVertCenterReg3
r_int
r_char
id|PanelVertCenterReg3
suffix:semicolon
DECL|member|PanelVertCenterReg4
r_int
r_char
id|PanelVertCenterReg4
suffix:semicolon
DECL|member|PanelVertCenterReg5
r_int
r_char
id|PanelVertCenterReg5
suffix:semicolon
DECL|member|PanelHorizCenterReg1
r_int
r_char
id|PanelHorizCenterReg1
suffix:semicolon
DECL|member|PanelHorizCenterReg2
r_int
r_char
id|PanelHorizCenterReg2
suffix:semicolon
DECL|member|PanelHorizCenterReg3
r_int
r_char
id|PanelHorizCenterReg3
suffix:semicolon
DECL|member|PanelHorizCenterReg4
r_int
r_char
id|PanelHorizCenterReg4
suffix:semicolon
DECL|member|PanelHorizCenterReg5
r_int
r_char
id|PanelHorizCenterReg5
suffix:semicolon
DECL|member|ProgramVCLK
r_int
id|ProgramVCLK
suffix:semicolon
DECL|member|VCLK3NumeratorLow
r_int
r_char
id|VCLK3NumeratorLow
suffix:semicolon
DECL|member|VCLK3NumeratorHigh
r_int
r_char
id|VCLK3NumeratorHigh
suffix:semicolon
DECL|member|VCLK3Denominator
r_int
r_char
id|VCLK3Denominator
suffix:semicolon
DECL|member|VerticalExt
r_int
r_char
id|VerticalExt
suffix:semicolon
macro_line|#ifdef CONFIG_MTRR
DECL|member|mtrr
r_int
id|mtrr
suffix:semicolon
macro_line|#endif
DECL|member|mmio_vbase
id|u8
id|__iomem
op_star
id|mmio_vbase
suffix:semicolon
DECL|member|cursorOff
id|u8
id|cursorOff
suffix:semicolon
DECL|member|cursorPad
id|u8
op_star
id|cursorPad
suffix:semicolon
multiline_comment|/* Must die !! */
DECL|member|neo2200
id|Neo2200
id|__iomem
op_star
id|neo2200
suffix:semicolon
multiline_comment|/* Panels size */
DECL|member|NeoPanelWidth
r_int
id|NeoPanelWidth
suffix:semicolon
DECL|member|NeoPanelHeight
r_int
id|NeoPanelHeight
suffix:semicolon
DECL|member|maxClock
r_int
id|maxClock
suffix:semicolon
DECL|member|pci_burst
r_int
id|pci_burst
suffix:semicolon
DECL|member|lcd_stretch
r_int
id|lcd_stretch
suffix:semicolon
DECL|member|internal_display
r_int
id|internal_display
suffix:semicolon
DECL|member|external_display
r_int
id|external_display
suffix:semicolon
DECL|member|libretto
r_int
id|libretto
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|x_res
r_int
id|x_res
suffix:semicolon
DECL|member|y_res
r_int
id|y_res
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|typedef|biosMode
)brace
id|biosMode
suffix:semicolon
macro_line|#endif
eof
