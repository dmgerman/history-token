macro_line|#ifndef _VIDEO_S3BLIT_H
DECL|macro|_VIDEO_S3BLIT_H
mdefine_line|#define _VIDEO_S3BLIT_H
multiline_comment|/* s3 commands */
DECL|macro|S3_BITBLT
mdefine_line|#define S3_BITBLT       0xc011
DECL|macro|S3_TWOPOINTLINE
mdefine_line|#define S3_TWOPOINTLINE 0x2811
DECL|macro|S3_FILLEDRECT
mdefine_line|#define S3_FILLEDRECT   0x40b1
DECL|macro|S3_FIFO_EMPTY
mdefine_line|#define S3_FIFO_EMPTY 0x0400
DECL|macro|S3_HDW_BUSY
mdefine_line|#define S3_HDW_BUSY   0x0200
multiline_comment|/* Enhanced register mapping (MMIO mode) */
DECL|macro|S3_READ_SEL
mdefine_line|#define S3_READ_SEL      0xbee8 /* offset f */
DECL|macro|S3_MULT_MISC
mdefine_line|#define S3_MULT_MISC     0xbee8 /* offset e */
DECL|macro|S3_ERR_TERM
mdefine_line|#define S3_ERR_TERM      0x92e8
DECL|macro|S3_FRGD_COLOR
mdefine_line|#define S3_FRGD_COLOR    0xa6e8
DECL|macro|S3_BKGD_COLOR
mdefine_line|#define S3_BKGD_COLOR    0xa2e8
DECL|macro|S3_PIXEL_CNTL
mdefine_line|#define S3_PIXEL_CNTL    0xbee8 /* offset a */
DECL|macro|S3_FRGD_MIX
mdefine_line|#define S3_FRGD_MIX      0xbae8
DECL|macro|S3_BKGD_MIX
mdefine_line|#define S3_BKGD_MIX      0xb6e8
DECL|macro|S3_CUR_Y
mdefine_line|#define S3_CUR_Y         0x82e8
DECL|macro|S3_CUR_X
mdefine_line|#define S3_CUR_X         0x86e8
DECL|macro|S3_DESTY_AXSTP
mdefine_line|#define S3_DESTY_AXSTP   0x8ae8
DECL|macro|S3_DESTX_DIASTP
mdefine_line|#define S3_DESTX_DIASTP  0x8ee8
DECL|macro|S3_MIN_AXIS_PCNT
mdefine_line|#define S3_MIN_AXIS_PCNT 0xbee8 /* offset 0 */
DECL|macro|S3_MAJ_AXIS_PCNT
mdefine_line|#define S3_MAJ_AXIS_PCNT 0x96e8
DECL|macro|S3_CMD
mdefine_line|#define S3_CMD           0x9ae8
DECL|macro|S3_GP_STAT
mdefine_line|#define S3_GP_STAT       0x9ae8
DECL|macro|S3_ADVFUNC_CNTL
mdefine_line|#define S3_ADVFUNC_CNTL  0x4ae8
DECL|macro|S3_WRT_MASK
mdefine_line|#define S3_WRT_MASK      0xaae8
DECL|macro|S3_RD_MASK
mdefine_line|#define S3_RD_MASK       0xaee8
multiline_comment|/* Enhanced register mapping (Packed MMIO mode, write only) */
DECL|macro|S3_ALT_CURXY
mdefine_line|#define S3_ALT_CURXY     0x8100
DECL|macro|S3_ALT_CURXY2
mdefine_line|#define S3_ALT_CURXY2    0x8104
DECL|macro|S3_ALT_STEP
mdefine_line|#define S3_ALT_STEP      0x8108
DECL|macro|S3_ALT_STEP2
mdefine_line|#define S3_ALT_STEP2     0x810c
DECL|macro|S3_ALT_ERR
mdefine_line|#define S3_ALT_ERR       0x8110
DECL|macro|S3_ALT_CMD
mdefine_line|#define S3_ALT_CMD       0x8118
DECL|macro|S3_ALT_MIX
mdefine_line|#define S3_ALT_MIX       0x8134
DECL|macro|S3_ALT_PCNT
mdefine_line|#define S3_ALT_PCNT      0x8148
DECL|macro|S3_ALT_PAT
mdefine_line|#define S3_ALT_PAT       0x8168
multiline_comment|/* Drawing modes */
DECL|macro|S3_NOTCUR
mdefine_line|#define S3_NOTCUR          0x0000
DECL|macro|S3_LOGICALZERO
mdefine_line|#define S3_LOGICALZERO     0x0001
DECL|macro|S3_LOGICALONE
mdefine_line|#define S3_LOGICALONE      0x0002
DECL|macro|S3_LEAVEASIS
mdefine_line|#define S3_LEAVEASIS       0x0003
DECL|macro|S3_NOTNEW
mdefine_line|#define S3_NOTNEW          0x0004
DECL|macro|S3_CURXORNEW
mdefine_line|#define S3_CURXORNEW       0x0005
DECL|macro|S3_NOT_CURXORNEW
mdefine_line|#define S3_NOT_CURXORNEW   0x0006
DECL|macro|S3_NEW
mdefine_line|#define S3_NEW             0x0007
DECL|macro|S3_NOTCURORNOTNEW
mdefine_line|#define S3_NOTCURORNOTNEW  0x0008
DECL|macro|S3_CURORNOTNEW
mdefine_line|#define S3_CURORNOTNEW     0x0009
DECL|macro|S3_NOTCURORNEW
mdefine_line|#define S3_NOTCURORNEW     0x000a
DECL|macro|S3_CURORNEW
mdefine_line|#define S3_CURORNEW        0x000b
DECL|macro|S3_CURANDNEW
mdefine_line|#define S3_CURANDNEW       0x000c
DECL|macro|S3_NOTCURANDNEW
mdefine_line|#define S3_NOTCURANDNEW    0x000d
DECL|macro|S3_CURANDNOTNEW
mdefine_line|#define S3_CURANDNOTNEW    0x000e
DECL|macro|S3_NOTCURANDNOTNEW
mdefine_line|#define S3_NOTCURANDNOTNEW 0x000f
DECL|macro|S3_CRTC_ADR
mdefine_line|#define S3_CRTC_ADR    0x03d4
DECL|macro|S3_CRTC_DATA
mdefine_line|#define S3_CRTC_DATA   0x03d5
DECL|macro|S3_REG_LOCK2
mdefine_line|#define S3_REG_LOCK2 0x39
DECL|macro|S3_HGC_MODE
mdefine_line|#define S3_HGC_MODE  0x45
DECL|macro|S3_HWGC_ORGX_H
mdefine_line|#define S3_HWGC_ORGX_H 0x46
DECL|macro|S3_HWGC_ORGX_L
mdefine_line|#define S3_HWGC_ORGX_L 0x47
DECL|macro|S3_HWGC_ORGY_H
mdefine_line|#define S3_HWGC_ORGY_H 0x48
DECL|macro|S3_HWGC_ORGY_L
mdefine_line|#define S3_HWGC_ORGY_L 0x49
DECL|macro|S3_HWGC_DX
mdefine_line|#define S3_HWGC_DX     0x4e
DECL|macro|S3_HWGC_DY
mdefine_line|#define S3_HWGC_DY     0x4f
DECL|macro|S3_LAW_CTL
mdefine_line|#define S3_LAW_CTL 0x58
macro_line|#endif /* _VIDEO_S3BLIT_H */
eof
