multiline_comment|/*&n;    Definitions for the Philips SAA7196 digital video decoder,&n;    scaler, and clock generator circuit (DESCpro), as used in&n;    the PlanB video input of the Powermac 7x00/8x00 series.&n;  &n;    Copyright (C) 1998 Michel Lanners (mlan@cpu.lu)&n;&n;    The register defines are shamelessly copied from the meteor&n;    driver out of NetBSD (with permission),&n;    and are copyrighted (c) 1995 Mark Tinguely and Jim Lowe&n;    (Thanks !)&n;  &n;    Additional debugging and coding by Takashi Oe (toe@unlinfo.unl.edu)&n;&n;    The default values used for PlanB are my mistakes.&n;*/
multiline_comment|/* $Id: saa7196.h,v 1.5 1999/03/26 23:28:47 mlan Exp $ */
macro_line|#ifndef _SAA7196_H_
DECL|macro|_SAA7196_H_
mdefine_line|#define _SAA7196_H_
DECL|macro|SAA7196_NUMREGS
mdefine_line|#define SAA7196_NUMREGS&t;0x31&t;/* Number of registers (used)*/
DECL|macro|NUM_SUPPORTED_NORM
mdefine_line|#define NUM_SUPPORTED_NORM 3&t;/* Number of supported norms by PlanB */
multiline_comment|/* Decoder part: */
DECL|macro|SAA7196_IDEL
mdefine_line|#define SAA7196_IDEL    0x00    /* Increment delay */
DECL|macro|SAA7196_HSB5
mdefine_line|#define SAA7196_HSB5    0x01    /* H-sync begin; 50 hz */
DECL|macro|SAA7196_HSS5
mdefine_line|#define SAA7196_HSS5    0x02    /* H-sync stop; 50 hz */
DECL|macro|SAA7196_HCB5
mdefine_line|#define SAA7196_HCB5    0x03    /* H-clamp begin; 50 hz */
DECL|macro|SAA7196_HCS5
mdefine_line|#define SAA7196_HCS5    0x04    /* H-clamp stop; 50 hz */
DECL|macro|SAA7196_HSP5
mdefine_line|#define SAA7196_HSP5    0x05    /* H-sync after PHI1; 50 hz */
DECL|macro|SAA7196_LUMC
mdefine_line|#define SAA7196_LUMC    0x06    /* Luminance control */
DECL|macro|SAA7196_HUEC
mdefine_line|#define SAA7196_HUEC    0x07    /* Hue control */
DECL|macro|SAA7196_CKTQ
mdefine_line|#define SAA7196_CKTQ    0x08    /* Colour Killer Threshold QAM (PAL, NTSC) */
DECL|macro|SAA7196_CKTS
mdefine_line|#define SAA7196_CKTS    0x09    /* Colour Killer Threshold SECAM */
DECL|macro|SAA7196_PALS
mdefine_line|#define SAA7196_PALS    0x0a    /* PAL switch sensitivity */
DECL|macro|SAA7196_SECAMS
mdefine_line|#define SAA7196_SECAMS  0x0b    /* SECAM switch sensitivity */
DECL|macro|SAA7196_CGAINC
mdefine_line|#define SAA7196_CGAINC  0x0c    /* Chroma gain control */
DECL|macro|SAA7196_STDC
mdefine_line|#define SAA7196_STDC    0x0d    /* Standard/Mode control */
DECL|macro|SAA7196_IOCC
mdefine_line|#define SAA7196_IOCC    0x0e    /* I/O and Clock Control */
DECL|macro|SAA7196_CTRL1
mdefine_line|#define SAA7196_CTRL1   0x0f    /* Control #1 */
DECL|macro|SAA7196_CTRL2
mdefine_line|#define SAA7196_CTRL2   0x10    /* Control #2 */
DECL|macro|SAA7196_CGAINR
mdefine_line|#define SAA7196_CGAINR  0x11    /* Chroma Gain Reference */
DECL|macro|SAA7196_CSAT
mdefine_line|#define SAA7196_CSAT    0x12    /* Chroma Saturation */
DECL|macro|SAA7196_CONT
mdefine_line|#define SAA7196_CONT    0x13    /* Luminance Contrast */
DECL|macro|SAA7196_HSB6
mdefine_line|#define SAA7196_HSB6    0x14    /* H-sync begin; 60 hz */
DECL|macro|SAA7196_HSS6
mdefine_line|#define SAA7196_HSS6    0x15    /* H-sync stop; 60 hz */
DECL|macro|SAA7196_HCB6
mdefine_line|#define SAA7196_HCB6    0x16    /* H-clamp begin; 60 hz */
DECL|macro|SAA7196_HCS6
mdefine_line|#define SAA7196_HCS6    0x17    /* H-clamp stop; 60 hz */
DECL|macro|SAA7196_HSP6
mdefine_line|#define SAA7196_HSP6    0x18    /* H-sync after PHI1; 60 hz */
DECL|macro|SAA7196_BRIG
mdefine_line|#define SAA7196_BRIG    0x19    /* Luminance Brightness */
multiline_comment|/* Scaler part: */
DECL|macro|SAA7196_FMTS
mdefine_line|#define SAA7196_FMTS    0x20    /* Formats and sequence */
DECL|macro|SAA7196_OUTPIX
mdefine_line|#define SAA7196_OUTPIX  0x21    /* Output data pixel/line */
DECL|macro|SAA7196_INPIX
mdefine_line|#define SAA7196_INPIX   0x22    /* Input data pixel/line */
DECL|macro|SAA7196_HWS
mdefine_line|#define SAA7196_HWS     0x23    /* Horiz. window start */
DECL|macro|SAA7196_HFILT
mdefine_line|#define SAA7196_HFILT   0x24    /* Horiz. filter */
DECL|macro|SAA7196_OUTLINE
mdefine_line|#define SAA7196_OUTLINE 0x25    /* Output data lines/field */
DECL|macro|SAA7196_INLINE
mdefine_line|#define SAA7196_INLINE  0x26    /* Input data lines/field */
DECL|macro|SAA7196_VWS
mdefine_line|#define SAA7196_VWS     0x27    /* Vertical window start */
DECL|macro|SAA7196_VYP
mdefine_line|#define SAA7196_VYP     0x28    /* AFS/vertical Y processing */
DECL|macro|SAA7196_VBS
mdefine_line|#define SAA7196_VBS     0x29    /* Vertical Bypass start */
DECL|macro|SAA7196_VBCNT
mdefine_line|#define SAA7196_VBCNT   0x2a    /* Vertical Bypass count */
DECL|macro|SAA7196_VBP
mdefine_line|#define SAA7196_VBP     0x2b    /* veritcal Bypass Polarity */
DECL|macro|SAA7196_VLOW
mdefine_line|#define SAA7196_VLOW    0x2c    /* Colour-keying lower V limit */
DECL|macro|SAA7196_VHIGH
mdefine_line|#define SAA7196_VHIGH   0x2d    /* Colour-keying upper V limit */
DECL|macro|SAA7196_ULOW
mdefine_line|#define SAA7196_ULOW    0x2e    /* Colour-keying lower U limit */
DECL|macro|SAA7196_UHIGH
mdefine_line|#define SAA7196_UHIGH   0x2f    /* Colour-keying upper U limit */
DECL|macro|SAA7196_DPATH
mdefine_line|#define SAA7196_DPATH   0x30    /* Data path setting  */
multiline_comment|/* Initialization default values: */
DECL|variable|saa_regs
r_int
r_char
id|saa_regs
(braket
id|NUM_SUPPORTED_NORM
)braket
(braket
id|SAA7196_NUMREGS
)braket
op_assign
(brace
multiline_comment|/* PAL, 768x576 (no scaling), composite video-in */
multiline_comment|/* Decoder: */
(brace
l_int|0x50
comma
l_int|0x30
comma
l_int|0x00
comma
l_int|0xe8
comma
l_int|0xb6
comma
l_int|0xe5
comma
l_int|0x63
comma
l_int|0xff
comma
l_int|0xfe
comma
l_int|0xf0
comma
l_int|0xfe
comma
l_int|0xe0
comma
l_int|0x20
comma
l_int|0x06
comma
l_int|0x3b
comma
l_int|0x98
comma
l_int|0x00
comma
l_int|0x59
comma
l_int|0x41
comma
l_int|0x45
comma
l_int|0x34
comma
l_int|0x0a
comma
l_int|0xf4
comma
l_int|0xd2
comma
l_int|0xe9
comma
l_int|0xa2
comma
multiline_comment|/* Padding */
l_int|0x80
comma
l_int|0x80
comma
l_int|0x80
comma
l_int|0x80
comma
l_int|0x80
comma
l_int|0x80
comma
multiline_comment|/* Scaler: */
l_int|0x72
comma
l_int|0x80
comma
l_int|0x00
comma
l_int|0x03
comma
l_int|0x8d
comma
l_int|0x20
comma
l_int|0x20
comma
l_int|0x12
comma
l_int|0xa5
comma
l_int|0x12
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x04
comma
l_int|0x00
comma
l_int|0x04
comma
l_int|0x00
comma
l_int|0x87
)brace
comma
multiline_comment|/* NTSC, 640x480? (no scaling), composite video-in */
multiline_comment|/* Decoder: */
(brace
l_int|0x50
comma
l_int|0x30
comma
l_int|0x00
comma
l_int|0xe8
comma
l_int|0xb6
comma
l_int|0xe5
comma
l_int|0x50
comma
l_int|0x00
comma
l_int|0xf8
comma
l_int|0xf0
comma
l_int|0xfe
comma
l_int|0xe0
comma
l_int|0x00
comma
l_int|0x06
comma
l_int|0x3b
comma
l_int|0x98
comma
l_int|0x00
comma
l_int|0x2c
comma
l_int|0x3d
comma
l_int|0x40
comma
l_int|0x34
comma
l_int|0x0a
comma
l_int|0xf4
comma
l_int|0xd2
comma
l_int|0xe9
comma
l_int|0x98
comma
multiline_comment|/* Padding */
l_int|0x80
comma
l_int|0x80
comma
l_int|0x80
comma
l_int|0x80
comma
l_int|0x80
comma
l_int|0x80
comma
multiline_comment|/* Scaler: */
l_int|0x72
comma
l_int|0x80
comma
l_int|0x80
comma
l_int|0x03
comma
l_int|0x89
comma
l_int|0xf0
comma
l_int|0xf0
comma
l_int|0x0d
comma
l_int|0xa0
comma
l_int|0x0d
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x04
comma
l_int|0x00
comma
l_int|0x04
comma
l_int|0x00
comma
l_int|0x87
)brace
comma
multiline_comment|/* SECAM, 768x576 (no scaling), composite video-in */
multiline_comment|/* Decoder: */
(brace
l_int|0x50
comma
l_int|0x30
comma
l_int|0x00
comma
l_int|0xe8
comma
l_int|0xb6
comma
l_int|0xe5
comma
l_int|0x63
comma
l_int|0xff
comma
l_int|0xfe
comma
l_int|0xf0
comma
l_int|0xfe
comma
l_int|0xe0
comma
l_int|0x20
comma
l_int|0x07
comma
l_int|0x3b
comma
l_int|0x98
comma
l_int|0x00
comma
l_int|0x59
comma
l_int|0x41
comma
l_int|0x45
comma
l_int|0x34
comma
l_int|0x0a
comma
l_int|0xf4
comma
l_int|0xd2
comma
l_int|0xe9
comma
l_int|0xa2
comma
multiline_comment|/* Padding */
l_int|0x80
comma
l_int|0x80
comma
l_int|0x80
comma
l_int|0x80
comma
l_int|0x80
comma
l_int|0x80
comma
multiline_comment|/* Scaler: */
l_int|0x72
comma
l_int|0x80
comma
l_int|0x00
comma
l_int|0x03
comma
l_int|0x8d
comma
l_int|0x20
comma
l_int|0x20
comma
l_int|0x12
comma
l_int|0xa5
comma
l_int|0x12
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x04
comma
l_int|0x00
comma
l_int|0x04
comma
l_int|0x00
comma
l_int|0x87
)brace
)brace
suffix:semicolon
macro_line|#endif /* _SAA7196_H_ */
eof
