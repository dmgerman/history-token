macro_line|#ifndef __MATROXFB_DAC1064_H__
DECL|macro|__MATROXFB_DAC1064_H__
mdefine_line|#define __MATROXFB_DAC1064_H__
multiline_comment|/* make checkconfig does not walk through include tree */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;matroxfb_base.h&quot;
macro_line|#ifdef CONFIG_FB_MATROX_MYSTIQUE
r_extern
r_struct
id|matrox_switch
id|matrox_mystique
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_FB_MATROX_G100
r_extern
r_struct
id|matrox_switch
id|matrox_G100
suffix:semicolon
macro_line|#endif
macro_line|#ifdef NEED_DAC1064
r_void
id|DAC1064_global_init
c_func
(paren
id|CPMINFO
r_struct
id|matrox_hw_state
op_star
)paren
suffix:semicolon
r_void
id|DAC1064_global_restore
c_func
(paren
id|CPMINFO
r_const
r_struct
id|matrox_hw_state
op_star
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|M1064_INDEX
mdefine_line|#define M1064_INDEX&t;0x00
DECL|macro|M1064_PALWRADD
mdefine_line|#define M1064_PALWRADD&t;0x00
DECL|macro|M1064_PALDATA
mdefine_line|#define M1064_PALDATA&t;0x01
DECL|macro|M1064_PIXRDMSK
mdefine_line|#define M1064_PIXRDMSK&t;0x02
DECL|macro|M1064_PALRDADD
mdefine_line|#define M1064_PALRDADD&t;0x03
DECL|macro|M1064_X_DATAREG
mdefine_line|#define M1064_X_DATAREG&t;0x0A
DECL|macro|M1064_CURPOSXL
mdefine_line|#define M1064_CURPOSXL&t;0x0C&t;/* can be accessed as DWORD */
DECL|macro|M1064_CURPOSXH
mdefine_line|#define M1064_CURPOSXH&t;0x0D
DECL|macro|M1064_CURPOSYL
mdefine_line|#define M1064_CURPOSYL&t;0x0E
DECL|macro|M1064_CURPOSYH
mdefine_line|#define M1064_CURPOSYH&t;0x0F
DECL|macro|M1064_XCURADDL
mdefine_line|#define M1064_XCURADDL&t;&t;0x04
DECL|macro|M1064_XCURADDH
mdefine_line|#define M1064_XCURADDH&t;&t;0x05
DECL|macro|M1064_XCURCTRL
mdefine_line|#define M1064_XCURCTRL&t;&t;0x06
DECL|macro|M1064_XCURCTRL_DIS
mdefine_line|#define     M1064_XCURCTRL_DIS&t;&t;0x00&t;/* transparent, transparent, transparent, transparent */
DECL|macro|M1064_XCURCTRL_3COLOR
mdefine_line|#define     M1064_XCURCTRL_3COLOR&t;0x01&t;/* transparent, 0, 1, 2 */
DECL|macro|M1064_XCURCTRL_XGA
mdefine_line|#define     M1064_XCURCTRL_XGA&t;&t;0x02&t;/* 0, 1, transparent, complement */
DECL|macro|M1064_XCURCTRL_XWIN
mdefine_line|#define     M1064_XCURCTRL_XWIN&t;&t;0x03&t;/* transparent, transparent, 0, 1 */
DECL|macro|M1064_XCURCOL0RED
mdefine_line|#define M1064_XCURCOL0RED&t;0x08
DECL|macro|M1064_XCURCOL0GREEN
mdefine_line|#define M1064_XCURCOL0GREEN&t;0x09
DECL|macro|M1064_XCURCOL0BLUE
mdefine_line|#define M1064_XCURCOL0BLUE&t;0x0A
DECL|macro|M1064_XCURCOL1RED
mdefine_line|#define M1064_XCURCOL1RED&t;0x0C
DECL|macro|M1064_XCURCOL1GREEN
mdefine_line|#define M1064_XCURCOL1GREEN&t;0x0D
DECL|macro|M1064_XCURCOL1BLUE
mdefine_line|#define M1064_XCURCOL1BLUE&t;0x0E
DECL|macro|M1064_XCURCOL2RED
mdefine_line|#define M1064_XCURCOL2RED&t;0x10
DECL|macro|M1064_XCURCOL2GREEN
mdefine_line|#define M1064_XCURCOL2GREEN&t;0x11
DECL|macro|M1064_XCURCOL2BLUE
mdefine_line|#define M1064_XCURCOL2BLUE&t;0x12
DECL|macro|DAC1064_XVREFCTRL
mdefine_line|#define DAC1064_XVREFCTRL&t;0x18
DECL|macro|DAC1064_XVREFCTRL_INTERNAL
mdefine_line|#define      DAC1064_XVREFCTRL_INTERNAL&t;&t;0x3F
DECL|macro|DAC1064_XVREFCTRL_EXTERNAL
mdefine_line|#define      DAC1064_XVREFCTRL_EXTERNAL&t;&t;0x00
DECL|macro|DAC1064_XVREFCTRL_G100_DEFAULT
mdefine_line|#define      DAC1064_XVREFCTRL_G100_DEFAULT&t;0x03
DECL|macro|M1064_XMULCTRL
mdefine_line|#define M1064_XMULCTRL&t;&t;0x19
DECL|macro|M1064_XMULCTRL_DEPTH_8BPP
mdefine_line|#define      M1064_XMULCTRL_DEPTH_8BPP&t;&t;0x00&t;/* 8 bpp paletized */
DECL|macro|M1064_XMULCTRL_DEPTH_15BPP_1BPP
mdefine_line|#define      M1064_XMULCTRL_DEPTH_15BPP_1BPP&t;0x01&t;/* 15 bpp paletized + 1 bpp overlay */
DECL|macro|M1064_XMULCTRL_DEPTH_16BPP
mdefine_line|#define      M1064_XMULCTRL_DEPTH_16BPP&t;&t;0x02&t;/* 16 bpp paletized */
DECL|macro|M1064_XMULCTRL_DEPTH_24BPP
mdefine_line|#define      M1064_XMULCTRL_DEPTH_24BPP&t;&t;0x03&t;/* 24 bpp paletized */
DECL|macro|M1064_XMULCTRL_DEPTH_24BPP_8BPP
mdefine_line|#define      M1064_XMULCTRL_DEPTH_24BPP_8BPP&t;0x04&t;/* 24 bpp direct + 8 bpp overlay paletized */
DECL|macro|M1064_XMULCTRL_2G8V16
mdefine_line|#define      M1064_XMULCTRL_2G8V16&t;&t;0x05&t;/* 15 bpp video direct, half xres, 8bpp paletized */
DECL|macro|M1064_XMULCTRL_G16V16
mdefine_line|#define      M1064_XMULCTRL_G16V16&t;&t;0x06&t;/* 15 bpp video, 15bpp graphics, one of them paletized */
DECL|macro|M1064_XMULCTRL_DEPTH_32BPP
mdefine_line|#define      M1064_XMULCTRL_DEPTH_32BPP&t;&t;0x07&t;/* 24 bpp paletized + 8 bpp unused */
DECL|macro|M1064_XMULCTRL_GRAPHICS_PALETIZED
mdefine_line|#define      M1064_XMULCTRL_GRAPHICS_PALETIZED&t;0x00
DECL|macro|M1064_XMULCTRL_VIDEO_PALETIZED
mdefine_line|#define      M1064_XMULCTRL_VIDEO_PALETIZED&t;0x08
DECL|macro|M1064_XPIXCLKCTRL
mdefine_line|#define M1064_XPIXCLKCTRL&t;0x1A
DECL|macro|M1064_XPIXCLKCTRL_SRC_PCI
mdefine_line|#define      M1064_XPIXCLKCTRL_SRC_PCI&t;&t;0x00
DECL|macro|M1064_XPIXCLKCTRL_SRC_PLL
mdefine_line|#define      M1064_XPIXCLKCTRL_SRC_PLL&t;&t;0x01
DECL|macro|M1064_XPIXCLKCTRL_SRC_EXT
mdefine_line|#define      M1064_XPIXCLKCTRL_SRC_EXT&t;&t;0x02
DECL|macro|M1064_XPIXCLKCTRL_SRC_SYS
mdefine_line|#define&t;     M1064_XPIXCLKCTRL_SRC_SYS&t;&t;0x03&t;/* G200/G400 */
DECL|macro|M1064_XPIXCLKCTRL_SRC_PLL2
mdefine_line|#define      M1064_XPIXCLKCTRL_SRC_PLL2&t;&t;0x03&t;/* G450 */
DECL|macro|M1064_XPIXCLKCTRL_SRC_MASK
mdefine_line|#define      M1064_XPIXCLKCTRL_SRC_MASK&t;&t;0x03
DECL|macro|M1064_XPIXCLKCTRL_EN
mdefine_line|#define      M1064_XPIXCLKCTRL_EN&t;&t;0x00
DECL|macro|M1064_XPIXCLKCTRL_DIS
mdefine_line|#define      M1064_XPIXCLKCTRL_DIS&t;&t;0x04
DECL|macro|M1064_XPIXCLKCTRL_PLL_DOWN
mdefine_line|#define      M1064_XPIXCLKCTRL_PLL_DOWN&t;&t;0x00
DECL|macro|M1064_XPIXCLKCTRL_PLL_UP
mdefine_line|#define      M1064_XPIXCLKCTRL_PLL_UP&t;&t;0x08
DECL|macro|M1064_XGENCTRL
mdefine_line|#define M1064_XGENCTRL&t;&t;0x1D
DECL|macro|M1064_XGENCTRL_VS_0
mdefine_line|#define      M1064_XGENCTRL_VS_0&t;&t;0x00
DECL|macro|M1064_XGENCTRL_VS_1
mdefine_line|#define      M1064_XGENCTRL_VS_1&t;&t;0x01
DECL|macro|M1064_XGENCTRL_ALPHA_DIS
mdefine_line|#define      M1064_XGENCTRL_ALPHA_DIS&t;&t;0x00
DECL|macro|M1064_XGENCTRL_ALPHA_EN
mdefine_line|#define      M1064_XGENCTRL_ALPHA_EN&t;&t;0x02
DECL|macro|M1064_XGENCTRL_BLACK_0IRE
mdefine_line|#define      M1064_XGENCTRL_BLACK_0IRE&t;&t;0x00
DECL|macro|M1064_XGENCTRL_BLACK_75IRE
mdefine_line|#define      M1064_XGENCTRL_BLACK_75IRE&t;&t;0x10
DECL|macro|M1064_XGENCTRL_SYNC_ON_GREEN
mdefine_line|#define      M1064_XGENCTRL_SYNC_ON_GREEN&t;0x00
DECL|macro|M1064_XGENCTRL_NO_SYNC_ON_GREEN
mdefine_line|#define      M1064_XGENCTRL_NO_SYNC_ON_GREEN&t;0x20
DECL|macro|M1064_XGENCTRL_SYNC_ON_GREEN_MASK
mdefine_line|#define      M1064_XGENCTRL_SYNC_ON_GREEN_MASK&t;0x20
DECL|macro|M1064_XMISCCTRL
mdefine_line|#define M1064_XMISCCTRL&t;&t;0x1E
DECL|macro|M1064_XMISCCTRL_DAC_DIS
mdefine_line|#define      M1064_XMISCCTRL_DAC_DIS&t;&t;0x00
DECL|macro|M1064_XMISCCTRL_DAC_EN
mdefine_line|#define      M1064_XMISCCTRL_DAC_EN&t;&t;0x01
DECL|macro|M1064_XMISCCTRL_MFC_VGA
mdefine_line|#define      M1064_XMISCCTRL_MFC_VGA&t;&t;0x00
DECL|macro|M1064_XMISCCTRL_MFC_MAFC
mdefine_line|#define      M1064_XMISCCTRL_MFC_MAFC&t;&t;0x02
DECL|macro|M1064_XMISCCTRL_MFC_DIS
mdefine_line|#define      M1064_XMISCCTRL_MFC_DIS&t;&t;0x06
DECL|macro|GX00_XMISCCTRL_MFC_MAFC
mdefine_line|#define      GX00_XMISCCTRL_MFC_MAFC&t;&t;0x02
DECL|macro|GX00_XMISCCTRL_MFC_PANELLINK
mdefine_line|#define      GX00_XMISCCTRL_MFC_PANELLINK&t;0x04
DECL|macro|GX00_XMISCCTRL_MFC_DIS
mdefine_line|#define      GX00_XMISCCTRL_MFC_DIS&t;&t;0x06
DECL|macro|GX00_XMISCCTRL_MFC_MASK
mdefine_line|#define      GX00_XMISCCTRL_MFC_MASK&t;&t;0x06
DECL|macro|M1064_XMISCCTRL_DAC_6BIT
mdefine_line|#define      M1064_XMISCCTRL_DAC_6BIT&t;&t;0x00
DECL|macro|M1064_XMISCCTRL_DAC_8BIT
mdefine_line|#define      M1064_XMISCCTRL_DAC_8BIT&t;&t;0x08
DECL|macro|M1064_XMISCCTRL_DAC_WIDTHMASK
mdefine_line|#define      M1064_XMISCCTRL_DAC_WIDTHMASK&t;0x08
DECL|macro|M1064_XMISCCTRL_LUT_DIS
mdefine_line|#define      M1064_XMISCCTRL_LUT_DIS&t;&t;0x00
DECL|macro|M1064_XMISCCTRL_LUT_EN
mdefine_line|#define      M1064_XMISCCTRL_LUT_EN&t;&t;0x10
DECL|macro|G400_XMISCCTRL_VDO_MAFC12
mdefine_line|#define      G400_XMISCCTRL_VDO_MAFC12&t;&t;0x00
DECL|macro|G400_XMISCCTRL_VDO_BYPASS656
mdefine_line|#define      G400_XMISCCTRL_VDO_BYPASS656&t;0x40
DECL|macro|G400_XMISCCTRL_VDO_C2_MAFC12
mdefine_line|#define      G400_XMISCCTRL_VDO_C2_MAFC12&t;0x80
DECL|macro|G400_XMISCCTRL_VDO_C2_BYPASS656
mdefine_line|#define      G400_XMISCCTRL_VDO_C2_BYPASS656&t;0xC0
DECL|macro|G400_XMISCCTRL_VDO_MASK
mdefine_line|#define      G400_XMISCCTRL_VDO_MASK&t;&t;0xE0
DECL|macro|M1064_XGENIOCTRL
mdefine_line|#define M1064_XGENIOCTRL&t;0x2A
DECL|macro|M1064_XGENIODATA
mdefine_line|#define M1064_XGENIODATA&t;0x2B
DECL|macro|DAC1064_XSYSPLLM
mdefine_line|#define DAC1064_XSYSPLLM&t;0x2C
DECL|macro|DAC1064_XSYSPLLN
mdefine_line|#define DAC1064_XSYSPLLN&t;0x2D
DECL|macro|DAC1064_XSYSPLLP
mdefine_line|#define DAC1064_XSYSPLLP&t;0x2E
DECL|macro|DAC1064_XSYSPLLSTAT
mdefine_line|#define DAC1064_XSYSPLLSTAT&t;0x2F
DECL|macro|M1064_XZOOMCTRL
mdefine_line|#define M1064_XZOOMCTRL&t;&t;0x38
DECL|macro|M1064_XZOOMCTRL_1
mdefine_line|#define      M1064_XZOOMCTRL_1&t;&t;&t;0x00
DECL|macro|M1064_XZOOMCTRL_2
mdefine_line|#define      M1064_XZOOMCTRL_2&t;&t;&t;0x01
DECL|macro|M1064_XZOOMCTRL_4
mdefine_line|#define      M1064_XZOOMCTRL_4&t;&t;&t;0x03
DECL|macro|M1064_XSENSETEST
mdefine_line|#define M1064_XSENSETEST&t;0x3A
DECL|macro|M1064_XSENSETEST_BCOMP
mdefine_line|#define      M1064_XSENSETEST_BCOMP&t;&t;0x01
DECL|macro|M1064_XSENSETEST_GCOMP
mdefine_line|#define      M1064_XSENSETEST_GCOMP&t;&t;0x02
DECL|macro|M1064_XSENSETEST_RCOMP
mdefine_line|#define      M1064_XSENSETEST_RCOMP&t;&t;0x04
DECL|macro|M1064_XSENSETEST_PDOWN
mdefine_line|#define      M1064_XSENSETEST_PDOWN&t;&t;0x00
DECL|macro|M1064_XSENSETEST_PUP
mdefine_line|#define      M1064_XSENSETEST_PUP&t;&t;0x80
DECL|macro|M1064_XCRCREML
mdefine_line|#define M1064_XCRCREML&t;&t;0x3C
DECL|macro|M1064_XCRCREMH
mdefine_line|#define M1064_XCRCREMH&t;&t;0x3D
DECL|macro|M1064_XCRCBITSEL
mdefine_line|#define M1064_XCRCBITSEL&t;0x3E
DECL|macro|M1064_XCOLKEYMASKL
mdefine_line|#define M1064_XCOLKEYMASKL&t;0x40
DECL|macro|M1064_XCOLKEYMASKH
mdefine_line|#define M1064_XCOLKEYMASKH&t;0x41
DECL|macro|M1064_XCOLKEYL
mdefine_line|#define M1064_XCOLKEYL&t;&t;0x42
DECL|macro|M1064_XCOLKEYH
mdefine_line|#define M1064_XCOLKEYH&t;&t;0x43
DECL|macro|M1064_XPIXPLLAM
mdefine_line|#define M1064_XPIXPLLAM&t;&t;0x44
DECL|macro|M1064_XPIXPLLAN
mdefine_line|#define M1064_XPIXPLLAN&t;&t;0x45
DECL|macro|M1064_XPIXPLLAP
mdefine_line|#define M1064_XPIXPLLAP&t;&t;0x46
DECL|macro|M1064_XPIXPLLBM
mdefine_line|#define M1064_XPIXPLLBM&t;&t;0x48
DECL|macro|M1064_XPIXPLLBN
mdefine_line|#define M1064_XPIXPLLBN&t;&t;0x49
DECL|macro|M1064_XPIXPLLBP
mdefine_line|#define M1064_XPIXPLLBP&t;&t;0x4A
DECL|macro|M1064_XPIXPLLCM
mdefine_line|#define M1064_XPIXPLLCM&t;&t;0x4C
DECL|macro|M1064_XPIXPLLCN
mdefine_line|#define M1064_XPIXPLLCN&t;&t;0x4D
DECL|macro|M1064_XPIXPLLCP
mdefine_line|#define M1064_XPIXPLLCP&t;&t;0x4E
DECL|macro|M1064_XPIXPLLSTAT
mdefine_line|#define M1064_XPIXPLLSTAT&t;0x4F
DECL|macro|M1064_XTVO_IDX
mdefine_line|#define M1064_XTVO_IDX&t;&t;0x87
DECL|macro|M1064_XTVO_DATA
mdefine_line|#define M1064_XTVO_DATA&t;&t;0x88
DECL|macro|M1064_XOUTPUTCONN
mdefine_line|#define M1064_XOUTPUTCONN&t;0x8A
DECL|macro|M1064_XSYNCCTRL
mdefine_line|#define M1064_XSYNCCTRL&t;&t;0x8B
DECL|macro|M1064_XPIXPLL2STAT
mdefine_line|#define M1064_XPIXPLL2STAT&t;0x8C
DECL|macro|M1064_XPIXPLL2P
mdefine_line|#define M1064_XPIXPLL2P&t;&t;0x8D
DECL|macro|M1064_XPIXPLL2N
mdefine_line|#define M1064_XPIXPLL2N&t;&t;0x8E
DECL|macro|M1064_XPIXPLL2M
mdefine_line|#define M1064_XPIXPLL2M&t;&t;0x8F
DECL|macro|M1064_XPWRCTRL
mdefine_line|#define M1064_XPWRCTRL&t;&t;0xA0
DECL|enum|POS1064
r_enum
id|POS1064
(brace
DECL|enumerator|POS1064_XCURADDL
DECL|enumerator|POS1064_XCURADDH
DECL|enumerator|POS1064_XCURCTRL
id|POS1064_XCURADDL
op_assign
l_int|0
comma
id|POS1064_XCURADDH
comma
id|POS1064_XCURCTRL
comma
DECL|enumerator|POS1064_XCURCOL0RED
DECL|enumerator|POS1064_XCURCOL0GREEN
DECL|enumerator|POS1064_XCURCOL0BLUE
id|POS1064_XCURCOL0RED
comma
id|POS1064_XCURCOL0GREEN
comma
id|POS1064_XCURCOL0BLUE
comma
DECL|enumerator|POS1064_XCURCOL1RED
DECL|enumerator|POS1064_XCURCOL1GREEN
DECL|enumerator|POS1064_XCURCOL1BLUE
id|POS1064_XCURCOL1RED
comma
id|POS1064_XCURCOL1GREEN
comma
id|POS1064_XCURCOL1BLUE
comma
DECL|enumerator|POS1064_XCURCOL2RED
DECL|enumerator|POS1064_XCURCOL2GREEN
DECL|enumerator|POS1064_XCURCOL2BLUE
id|POS1064_XCURCOL2RED
comma
id|POS1064_XCURCOL2GREEN
comma
id|POS1064_XCURCOL2BLUE
comma
DECL|enumerator|POS1064_XVREFCTRL
DECL|enumerator|POS1064_XMULCTRL
DECL|enumerator|POS1064_XPIXCLKCTRL
DECL|enumerator|POS1064_XGENCTRL
id|POS1064_XVREFCTRL
comma
id|POS1064_XMULCTRL
comma
id|POS1064_XPIXCLKCTRL
comma
id|POS1064_XGENCTRL
comma
DECL|enumerator|POS1064_XMISCCTRL
id|POS1064_XMISCCTRL
comma
DECL|enumerator|POS1064_XGENIOCTRL
DECL|enumerator|POS1064_XGENIODATA
DECL|enumerator|POS1064_XZOOMCTRL
DECL|enumerator|POS1064_XSENSETEST
id|POS1064_XGENIOCTRL
comma
id|POS1064_XGENIODATA
comma
id|POS1064_XZOOMCTRL
comma
id|POS1064_XSENSETEST
comma
DECL|enumerator|POS1064_XCRCBITSEL
id|POS1064_XCRCBITSEL
comma
DECL|enumerator|POS1064_XCOLKEYMASKL
DECL|enumerator|POS1064_XCOLKEYMASKH
DECL|enumerator|POS1064_XCOLKEYL
DECL|enumerator|POS1064_XCOLKEYH
id|POS1064_XCOLKEYMASKL
comma
id|POS1064_XCOLKEYMASKH
comma
id|POS1064_XCOLKEYL
comma
id|POS1064_XCOLKEYH
comma
DECL|enumerator|POS1064_XOUTPUTCONN
id|POS1064_XOUTPUTCONN
)brace
suffix:semicolon
macro_line|#endif&t;/* __MATROXFB_DAC1064_H__ */
eof
