macro_line|#ifndef _TDFX_H
DECL|macro|_TDFX_H
mdefine_line|#define _TDFX_H
multiline_comment|/* membase0 register offsets */
DECL|macro|STATUS
mdefine_line|#define STATUS          0x00
DECL|macro|PCIINIT0
mdefine_line|#define PCIINIT0        0x04
DECL|macro|SIPMONITOR
mdefine_line|#define SIPMONITOR      0x08
DECL|macro|LFBMEMORYCONFIG
mdefine_line|#define LFBMEMORYCONFIG 0x0c
DECL|macro|MISCINIT0
mdefine_line|#define MISCINIT0       0x10
DECL|macro|MISCINIT1
mdefine_line|#define MISCINIT1       0x14
DECL|macro|DRAMINIT0
mdefine_line|#define DRAMINIT0       0x18
DECL|macro|DRAMINIT1
mdefine_line|#define DRAMINIT1       0x1c
DECL|macro|AGPINIT
mdefine_line|#define AGPINIT         0x20
DECL|macro|TMUGBEINIT
mdefine_line|#define TMUGBEINIT      0x24
DECL|macro|VGAINIT0
mdefine_line|#define VGAINIT0        0x28
DECL|macro|VGAINIT1
mdefine_line|#define VGAINIT1        0x2c
DECL|macro|DRAMCOMMAND
mdefine_line|#define DRAMCOMMAND     0x30
DECL|macro|DRAMDATA
mdefine_line|#define DRAMDATA        0x34
multiline_comment|/* reserved             0x38 */
multiline_comment|/* reserved             0x3c */
DECL|macro|PLLCTRL0
mdefine_line|#define PLLCTRL0        0x40
DECL|macro|PLLCTRL1
mdefine_line|#define PLLCTRL1        0x44
DECL|macro|PLLCTRL2
mdefine_line|#define PLLCTRL2        0x48
DECL|macro|DACMODE
mdefine_line|#define DACMODE         0x4c
DECL|macro|DACADDR
mdefine_line|#define DACADDR         0x50
DECL|macro|DACDATA
mdefine_line|#define DACDATA         0x54
DECL|macro|RGBMAXDELTA
mdefine_line|#define RGBMAXDELTA     0x58
DECL|macro|VIDPROCCFG
mdefine_line|#define VIDPROCCFG      0x5c
DECL|macro|HWCURPATADDR
mdefine_line|#define HWCURPATADDR    0x60
DECL|macro|HWCURLOC
mdefine_line|#define HWCURLOC        0x64
DECL|macro|HWCURC0
mdefine_line|#define HWCURC0         0x68
DECL|macro|HWCURC1
mdefine_line|#define HWCURC1         0x6c
DECL|macro|VIDINFORMAT
mdefine_line|#define VIDINFORMAT     0x70
DECL|macro|VIDINSTATUS
mdefine_line|#define VIDINSTATUS     0x74
DECL|macro|VIDSERPARPORT
mdefine_line|#define VIDSERPARPORT   0x78
DECL|macro|VIDINXDELTA
mdefine_line|#define VIDINXDELTA     0x7c
DECL|macro|VIDININITERR
mdefine_line|#define VIDININITERR    0x80
DECL|macro|VIDINYDELTA
mdefine_line|#define VIDINYDELTA     0x84
DECL|macro|VIDPIXBUFTHOLD
mdefine_line|#define VIDPIXBUFTHOLD  0x88
DECL|macro|VIDCHRMIN
mdefine_line|#define VIDCHRMIN       0x8c
DECL|macro|VIDCHRMAX
mdefine_line|#define VIDCHRMAX       0x90
DECL|macro|VIDCURLIN
mdefine_line|#define VIDCURLIN       0x94
DECL|macro|VIDSCREENSIZE
mdefine_line|#define VIDSCREENSIZE   0x98
DECL|macro|VIDOVRSTARTCRD
mdefine_line|#define VIDOVRSTARTCRD  0x9c
DECL|macro|VIDOVRENDCRD
mdefine_line|#define VIDOVRENDCRD    0xa0
DECL|macro|VIDOVRDUDX
mdefine_line|#define VIDOVRDUDX      0xa4
DECL|macro|VIDOVRDUDXOFF
mdefine_line|#define VIDOVRDUDXOFF   0xa8
DECL|macro|VIDOVRDVDY
mdefine_line|#define VIDOVRDVDY      0xac
multiline_comment|/*  ... */
DECL|macro|VIDOVRDVDYOFF
mdefine_line|#define VIDOVRDVDYOFF   0xe0
DECL|macro|VIDDESKSTART
mdefine_line|#define VIDDESKSTART    0xe4
DECL|macro|VIDDESKSTRIDE
mdefine_line|#define VIDDESKSTRIDE   0xe8
DECL|macro|VIDINADDR0
mdefine_line|#define VIDINADDR0      0xec
DECL|macro|VIDINADDR1
mdefine_line|#define VIDINADDR1      0xf0
DECL|macro|VIDINADDR2
mdefine_line|#define VIDINADDR2      0xf4
DECL|macro|VIDINSTRIDE
mdefine_line|#define VIDINSTRIDE     0xf8
DECL|macro|VIDCUROVRSTART
mdefine_line|#define VIDCUROVRSTART  0xfc
DECL|macro|INTCTRL
mdefine_line|#define INTCTRL         (0x00100000 + 0x04)
DECL|macro|CLIP0MIN
mdefine_line|#define CLIP0MIN        (0x00100000 + 0x08)
DECL|macro|CLIP0MAX
mdefine_line|#define CLIP0MAX        (0x00100000 + 0x0c)
DECL|macro|DSTBASE
mdefine_line|#define DSTBASE         (0x00100000 + 0x10)
DECL|macro|DSTFORMAT
mdefine_line|#define DSTFORMAT       (0x00100000 + 0x14)
DECL|macro|SRCBASE
mdefine_line|#define SRCBASE         (0x00100000 + 0x34)
DECL|macro|COMMANDEXTRA_2D
mdefine_line|#define COMMANDEXTRA_2D (0x00100000 + 0x38)
DECL|macro|CLIP1MIN
mdefine_line|#define CLIP1MIN        (0x00100000 + 0x4c)
DECL|macro|CLIP1MAX
mdefine_line|#define CLIP1MAX        (0x00100000 + 0x50)
DECL|macro|SRCFORMAT
mdefine_line|#define SRCFORMAT       (0x00100000 + 0x54)
DECL|macro|SRCSIZE
mdefine_line|#define SRCSIZE         (0x00100000 + 0x58)
DECL|macro|SRCXY
mdefine_line|#define SRCXY           (0x00100000 + 0x5c)
DECL|macro|COLORBACK
mdefine_line|#define COLORBACK       (0x00100000 + 0x60)
DECL|macro|COLORFORE
mdefine_line|#define COLORFORE       (0x00100000 + 0x64)
DECL|macro|DSTSIZE
mdefine_line|#define DSTSIZE         (0x00100000 + 0x68)
DECL|macro|DSTXY
mdefine_line|#define DSTXY           (0x00100000 + 0x6c)
DECL|macro|COMMAND_2D
mdefine_line|#define COMMAND_2D      (0x00100000 + 0x70)
DECL|macro|LAUNCH_2D
mdefine_line|#define LAUNCH_2D       (0x00100000 + 0x80)
DECL|macro|COMMAND_3D
mdefine_line|#define COMMAND_3D      (0x00200000 + 0x120)
multiline_comment|/* register bitfields (not all, only as needed) */
DECL|macro|BIT
mdefine_line|#define BIT(x) (1UL &lt;&lt; (x))
multiline_comment|/* COMMAND_2D reg. values */
DECL|macro|TDFX_ROP_COPY
mdefine_line|#define TDFX_ROP_COPY        0xcc     
singleline_comment|// src
DECL|macro|TDFX_ROP_INVERT
mdefine_line|#define TDFX_ROP_INVERT      0x55     
singleline_comment|// NOT dst
DECL|macro|TDFX_ROP_XOR
mdefine_line|#define TDFX_ROP_XOR         0x66     
singleline_comment|// src XOR dst
DECL|macro|AUTOINC_DSTX
mdefine_line|#define AUTOINC_DSTX                    BIT(10)
DECL|macro|AUTOINC_DSTY
mdefine_line|#define AUTOINC_DSTY                    BIT(11)
DECL|macro|COMMAND_2D_FILLRECT
mdefine_line|#define COMMAND_2D_FILLRECT             0x05
DECL|macro|COMMAND_2D_S2S_BITBLT
mdefine_line|#define COMMAND_2D_S2S_BITBLT           0x01      
singleline_comment|// screen to screen
DECL|macro|COMMAND_2D_H2S_BITBLT
mdefine_line|#define COMMAND_2D_H2S_BITBLT           0x03       
singleline_comment|// host to screen
DECL|macro|COMMAND_3D_NOP
mdefine_line|#define COMMAND_3D_NOP                  0x00
DECL|macro|STATUS_RETRACE
mdefine_line|#define STATUS_RETRACE                  BIT(6)
DECL|macro|STATUS_BUSY
mdefine_line|#define STATUS_BUSY                     BIT(9)
DECL|macro|MISCINIT1_CLUT_INV
mdefine_line|#define MISCINIT1_CLUT_INV              BIT(0)
DECL|macro|MISCINIT1_2DBLOCK_DIS
mdefine_line|#define MISCINIT1_2DBLOCK_DIS           BIT(15)
DECL|macro|DRAMINIT0_SGRAM_NUM
mdefine_line|#define DRAMINIT0_SGRAM_NUM             BIT(26)
DECL|macro|DRAMINIT0_SGRAM_TYPE
mdefine_line|#define DRAMINIT0_SGRAM_TYPE            BIT(27)
DECL|macro|DRAMINIT1_MEM_SDRAM
mdefine_line|#define DRAMINIT1_MEM_SDRAM             BIT(30)
DECL|macro|VGAINIT0_VGA_DISABLE
mdefine_line|#define VGAINIT0_VGA_DISABLE            BIT(0)
DECL|macro|VGAINIT0_EXT_TIMING
mdefine_line|#define VGAINIT0_EXT_TIMING             BIT(1)
DECL|macro|VGAINIT0_8BIT_DAC
mdefine_line|#define VGAINIT0_8BIT_DAC               BIT(2)
DECL|macro|VGAINIT0_EXT_ENABLE
mdefine_line|#define VGAINIT0_EXT_ENABLE             BIT(6)
DECL|macro|VGAINIT0_WAKEUP_3C3
mdefine_line|#define VGAINIT0_WAKEUP_3C3             BIT(8)
DECL|macro|VGAINIT0_LEGACY_DISABLE
mdefine_line|#define VGAINIT0_LEGACY_DISABLE         BIT(9)
DECL|macro|VGAINIT0_ALT_READBACK
mdefine_line|#define VGAINIT0_ALT_READBACK           BIT(10)
DECL|macro|VGAINIT0_FAST_BLINK
mdefine_line|#define VGAINIT0_FAST_BLINK             BIT(11)
DECL|macro|VGAINIT0_EXTSHIFTOUT
mdefine_line|#define VGAINIT0_EXTSHIFTOUT            BIT(12)
DECL|macro|VGAINIT0_DECODE_3C6
mdefine_line|#define VGAINIT0_DECODE_3C6             BIT(13)
DECL|macro|VGAINIT0_SGRAM_HBLANK_DISABLE
mdefine_line|#define VGAINIT0_SGRAM_HBLANK_DISABLE   BIT(22)
DECL|macro|VGAINIT1_MASK
mdefine_line|#define VGAINIT1_MASK                   0x1fffff
DECL|macro|VIDCFG_VIDPROC_ENABLE
mdefine_line|#define VIDCFG_VIDPROC_ENABLE           BIT(0)
DECL|macro|VIDCFG_CURS_X11
mdefine_line|#define VIDCFG_CURS_X11                 BIT(1)
DECL|macro|VIDCFG_HALF_MODE
mdefine_line|#define VIDCFG_HALF_MODE                BIT(4)
DECL|macro|VIDCFG_DESK_ENABLE
mdefine_line|#define VIDCFG_DESK_ENABLE              BIT(7)
DECL|macro|VIDCFG_CLUT_BYPASS
mdefine_line|#define VIDCFG_CLUT_BYPASS              BIT(10)
DECL|macro|VIDCFG_2X
mdefine_line|#define VIDCFG_2X                       BIT(26)
DECL|macro|VIDCFG_HWCURSOR_ENABLE
mdefine_line|#define VIDCFG_HWCURSOR_ENABLE          BIT(27)
DECL|macro|VIDCFG_PIXFMT_SHIFT
mdefine_line|#define VIDCFG_PIXFMT_SHIFT             18
DECL|macro|DACMODE_2X
mdefine_line|#define DACMODE_2X                      BIT(0)
multiline_comment|/* VGA rubbish, need to change this for multihead support */
DECL|macro|MISC_W
mdefine_line|#define MISC_W  0x3c2
DECL|macro|MISC_R
mdefine_line|#define MISC_R  0x3cc
DECL|macro|SEQ_I
mdefine_line|#define SEQ_I   0x3c4
DECL|macro|SEQ_D
mdefine_line|#define SEQ_D   0x3c5
DECL|macro|CRT_I
mdefine_line|#define CRT_I   0x3d4
DECL|macro|CRT_D
mdefine_line|#define CRT_D   0x3d5
DECL|macro|ATT_IW
mdefine_line|#define ATT_IW  0x3c0
DECL|macro|IS1_R
mdefine_line|#define IS1_R   0x3da
DECL|macro|GRA_I
mdefine_line|#define GRA_I   0x3ce
DECL|macro|GRA_D
mdefine_line|#define GRA_D   0x3cf
macro_line|#ifdef __KERNEL__
DECL|struct|banshee_reg
r_struct
id|banshee_reg
(brace
multiline_comment|/* VGA rubbish */
DECL|member|att
r_int
r_char
id|att
(braket
l_int|21
)braket
suffix:semicolon
DECL|member|crt
r_int
r_char
id|crt
(braket
l_int|25
)braket
suffix:semicolon
DECL|member|gra
r_int
r_char
id|gra
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|misc
r_int
r_char
id|misc
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|seq
r_int
r_char
id|seq
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* Banshee extensions */
DECL|member|ext
r_int
r_char
id|ext
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|vidcfg
r_int
r_int
id|vidcfg
suffix:semicolon
DECL|member|vidpll
r_int
r_int
id|vidpll
suffix:semicolon
DECL|member|mempll
r_int
r_int
id|mempll
suffix:semicolon
DECL|member|gfxpll
r_int
r_int
id|gfxpll
suffix:semicolon
DECL|member|dacmode
r_int
r_int
id|dacmode
suffix:semicolon
DECL|member|vgainit0
r_int
r_int
id|vgainit0
suffix:semicolon
DECL|member|vgainit1
r_int
r_int
id|vgainit1
suffix:semicolon
DECL|member|screensize
r_int
r_int
id|screensize
suffix:semicolon
DECL|member|stride
r_int
r_int
id|stride
suffix:semicolon
DECL|member|cursloc
r_int
r_int
id|cursloc
suffix:semicolon
DECL|member|curspataddr
r_int
r_int
id|curspataddr
suffix:semicolon
DECL|member|cursc0
r_int
r_int
id|cursc0
suffix:semicolon
DECL|member|cursc1
r_int
r_int
id|cursc1
suffix:semicolon
DECL|member|startaddr
r_int
r_int
id|startaddr
suffix:semicolon
DECL|member|clip0min
r_int
r_int
id|clip0min
suffix:semicolon
DECL|member|clip0max
r_int
r_int
id|clip0max
suffix:semicolon
DECL|member|clip1min
r_int
r_int
id|clip1min
suffix:semicolon
DECL|member|clip1max
r_int
r_int
id|clip1max
suffix:semicolon
DECL|member|srcbase
r_int
r_int
id|srcbase
suffix:semicolon
DECL|member|dstbase
r_int
r_int
id|dstbase
suffix:semicolon
DECL|member|miscinit0
r_int
r_int
id|miscinit0
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n;struct tdfx_par {&n;  u32 max_pixclock;&n;&n;  void *regbase_virt;&n;  unsigned long iobase;&n;  u32 baseline;&n;&n;  struct {&n;     int w,u,d;&n;     unsigned long enable,disable;&n;     struct timer_list timer;&n;  } hwcursor; &n;&n;  spinlock_t DAClock;&n;};&n;*/
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _TDFX_H */
eof
