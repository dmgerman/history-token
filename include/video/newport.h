multiline_comment|/* $Id: newport.h,v 1.5 1999/08/04 06:01:51 ulfc Exp $&n; *&n; * newport.h: Defines and register layout for NEWPORT graphics&n; *            hardware.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; * &n; * Ulf Carlsson - Compability with the IRIX structures added&n; */
macro_line|#ifndef _SGI_NEWPORT_H
DECL|macro|_SGI_NEWPORT_H
mdefine_line|#define _SGI_NEWPORT_H
DECL|typedef|npireg_t
r_typedef
r_volatile
r_int
r_int
id|npireg_t
suffix:semicolon
DECL|union|npfloat
r_union
id|npfloat
(brace
DECL|member|flt
r_volatile
r_float
id|flt
suffix:semicolon
DECL|member|word
id|npireg_t
id|word
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|npfreg_t
r_typedef
r_union
id|npfloat
id|npfreg_t
suffix:semicolon
DECL|union|np_dcb
r_union
id|np_dcb
(brace
DECL|member|byword
id|npireg_t
id|byword
suffix:semicolon
DECL|member|s0
DECL|member|s1
DECL|member|byshort
r_struct
(brace
r_volatile
r_int
r_int
id|s0
comma
id|s1
suffix:semicolon
)brace
id|byshort
suffix:semicolon
DECL|member|b0
DECL|member|b1
DECL|member|b2
DECL|member|b3
DECL|member|bybytes
r_struct
(brace
r_volatile
r_int
r_char
id|b0
comma
id|b1
comma
id|b2
comma
id|b3
suffix:semicolon
)brace
id|bybytes
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|newport_rexregs
r_struct
id|newport_rexregs
(brace
DECL|member|drawmode1
id|npireg_t
id|drawmode1
suffix:semicolon
multiline_comment|/* GL extra mode bits */
DECL|macro|DM1_PLANES
mdefine_line|#define DM1_PLANES         0x00000007
DECL|macro|DM1_NOPLANES
mdefine_line|#define    DM1_NOPLANES    0x00000000
DECL|macro|DM1_RGBPLANES
mdefine_line|#define    DM1_RGBPLANES   0x00000001
DECL|macro|DM1_RGBAPLANES
mdefine_line|#define    DM1_RGBAPLANES  0x00000002
DECL|macro|DM1_OLAYPLANES
mdefine_line|#define    DM1_OLAYPLANES  0x00000004
DECL|macro|DM1_PUPPLANES
mdefine_line|#define    DM1_PUPPLANES   0x00000005
DECL|macro|DM1_CIDPLANES
mdefine_line|#define    DM1_CIDPLANES   0x00000006
DECL|macro|NPORT_DMODE1_DDMASK
mdefine_line|#define NPORT_DMODE1_DDMASK      0x00000018
DECL|macro|NPORT_DMODE1_DD4
mdefine_line|#define NPORT_DMODE1_DD4         0x00000000
DECL|macro|NPORT_DMODE1_DD8
mdefine_line|#define NPORT_DMODE1_DD8         0x00000008
DECL|macro|NPORT_DMODE1_DD12
mdefine_line|#define NPORT_DMODE1_DD12        0x00000010
DECL|macro|NPORT_DMODE1_DD24
mdefine_line|#define NPORT_DMODE1_DD24        0x00000018
DECL|macro|NPORT_DMODE1_DSRC
mdefine_line|#define NPORT_DMODE1_DSRC        0x00000020
DECL|macro|NPORT_DMODE1_YFLIP
mdefine_line|#define NPORT_DMODE1_YFLIP       0x00000040
DECL|macro|NPORT_DMODE1_RWPCKD
mdefine_line|#define NPORT_DMODE1_RWPCKD      0x00000080
DECL|macro|NPORT_DMODE1_HDMASK
mdefine_line|#define NPORT_DMODE1_HDMASK      0x00000300
DECL|macro|NPORT_DMODE1_HD4
mdefine_line|#define NPORT_DMODE1_HD4         0x00000000
DECL|macro|NPORT_DMODE1_HD8
mdefine_line|#define NPORT_DMODE1_HD8         0x00000100
DECL|macro|NPORT_DMODE1_HD12
mdefine_line|#define NPORT_DMODE1_HD12        0x00000200
DECL|macro|NPORT_DMODE1_HD32
mdefine_line|#define NPORT_DMODE1_HD32        0x00000300
DECL|macro|NPORT_DMODE1_RWDBL
mdefine_line|#define NPORT_DMODE1_RWDBL       0x00000400
DECL|macro|NPORT_DMODE1_ESWAP
mdefine_line|#define NPORT_DMODE1_ESWAP       0x00000800 /* Endian swap */
DECL|macro|NPORT_DMODE1_CCMASK
mdefine_line|#define NPORT_DMODE1_CCMASK      0x00007000
DECL|macro|NPORT_DMODE1_CCLT
mdefine_line|#define NPORT_DMODE1_CCLT        0x00001000
DECL|macro|NPORT_DMODE1_CCEQ
mdefine_line|#define NPORT_DMODE1_CCEQ        0x00002000
DECL|macro|NPORT_DMODE1_CCGT
mdefine_line|#define NPORT_DMODE1_CCGT        0x00004000
DECL|macro|NPORT_DMODE1_RGBMD
mdefine_line|#define NPORT_DMODE1_RGBMD       0x00008000
DECL|macro|NPORT_DMODE1_DENAB
mdefine_line|#define NPORT_DMODE1_DENAB       0x00010000 /* Dither enable */
DECL|macro|NPORT_DMODE1_FCLR
mdefine_line|#define NPORT_DMODE1_FCLR        0x00020000 /* Fast clear */
DECL|macro|NPORT_DMODE1_BENAB
mdefine_line|#define NPORT_DMODE1_BENAB       0x00040000 /* Blend enable */
DECL|macro|NPORT_DMODE1_SFMASK
mdefine_line|#define NPORT_DMODE1_SFMASK      0x00380000
DECL|macro|NPORT_DMODE1_SF0
mdefine_line|#define NPORT_DMODE1_SF0         0x00000000
DECL|macro|NPORT_DMODE1_SF1
mdefine_line|#define NPORT_DMODE1_SF1         0x00080000
DECL|macro|NPORT_DMODE1_SFDC
mdefine_line|#define NPORT_DMODE1_SFDC        0x00100000
DECL|macro|NPORT_DMODE1_SFMDC
mdefine_line|#define NPORT_DMODE1_SFMDC       0x00180000
DECL|macro|NPORT_DMODE1_SFSA
mdefine_line|#define NPORT_DMODE1_SFSA        0x00200000
DECL|macro|NPORT_DMODE1_SFMSA
mdefine_line|#define NPORT_DMODE1_SFMSA       0x00280000
DECL|macro|NPORT_DMODE1_DFMASK
mdefine_line|#define NPORT_DMODE1_DFMASK      0x01c00000
DECL|macro|NPORT_DMODE1_DF0
mdefine_line|#define NPORT_DMODE1_DF0         0x00000000
DECL|macro|NPORT_DMODE1_DF1
mdefine_line|#define NPORT_DMODE1_DF1         0x00400000
DECL|macro|NPORT_DMODE1_DFSC
mdefine_line|#define NPORT_DMODE1_DFSC        0x00800000
DECL|macro|NPORT_DMODE1_DFMSC
mdefine_line|#define NPORT_DMODE1_DFMSC       0x00c00000
DECL|macro|NPORT_DMODE1_DFSA
mdefine_line|#define NPORT_DMODE1_DFSA        0x01000000
DECL|macro|NPORT_DMODE1_DFMSA
mdefine_line|#define NPORT_DMODE1_DFMSA       0x01400000
DECL|macro|NPORT_DMODE1_BBENAB
mdefine_line|#define NPORT_DMODE1_BBENAB      0x02000000 /* Back blend enable */
DECL|macro|NPORT_DMODE1_PFENAB
mdefine_line|#define NPORT_DMODE1_PFENAB      0x04000000 /* Pre-fetch enable */
DECL|macro|NPORT_DMODE1_ABLEND
mdefine_line|#define NPORT_DMODE1_ABLEND      0x08000000 /* Alpha blend */
DECL|macro|NPORT_DMODE1_LOMASK
mdefine_line|#define NPORT_DMODE1_LOMASK      0xf0000000
DECL|macro|NPORT_DMODE1_LOZERO
mdefine_line|#define NPORT_DMODE1_LOZERO      0x00000000
DECL|macro|NPORT_DMODE1_LOAND
mdefine_line|#define NPORT_DMODE1_LOAND       0x10000000
DECL|macro|NPORT_DMODE1_LOANDR
mdefine_line|#define NPORT_DMODE1_LOANDR      0x20000000
DECL|macro|NPORT_DMODE1_LOSRC
mdefine_line|#define NPORT_DMODE1_LOSRC       0x30000000
DECL|macro|NPORT_DMODE1_LOANDI
mdefine_line|#define NPORT_DMODE1_LOANDI      0x40000000
DECL|macro|NPORT_DMODE1_LODST
mdefine_line|#define NPORT_DMODE1_LODST       0x50000000
DECL|macro|NPORT_DMODE1_LOXOR
mdefine_line|#define NPORT_DMODE1_LOXOR       0x60000000
DECL|macro|NPORT_DMODE1_LOOR
mdefine_line|#define NPORT_DMODE1_LOOR        0x70000000
DECL|macro|NPORT_DMODE1_LONOR
mdefine_line|#define NPORT_DMODE1_LONOR       0x80000000
DECL|macro|NPORT_DMODE1_LOXNOR
mdefine_line|#define NPORT_DMODE1_LOXNOR      0x90000000
DECL|macro|NPORT_DMODE1_LONDST
mdefine_line|#define NPORT_DMODE1_LONDST      0xa0000000
DECL|macro|NPORT_DMODE1_LOORR
mdefine_line|#define NPORT_DMODE1_LOORR       0xb0000000
DECL|macro|NPORT_DMODE1_LONSRC
mdefine_line|#define NPORT_DMODE1_LONSRC      0xc0000000
DECL|macro|NPORT_DMODE1_LOORI
mdefine_line|#define NPORT_DMODE1_LOORI       0xd0000000
DECL|macro|NPORT_DMODE1_LONAND
mdefine_line|#define NPORT_DMODE1_LONAND      0xe0000000
DECL|macro|NPORT_DMODE1_LOONE
mdefine_line|#define NPORT_DMODE1_LOONE       0xf0000000
DECL|member|drawmode0
id|npireg_t
id|drawmode0
suffix:semicolon
multiline_comment|/* REX command register */
multiline_comment|/* These bits define the graphics opcode being performed. */
DECL|macro|NPORT_DMODE0_OPMASK
mdefine_line|#define NPORT_DMODE0_OPMASK   0x00000003 /* Opcode mask */
DECL|macro|NPORT_DMODE0_NOP
mdefine_line|#define NPORT_DMODE0_NOP      0x00000000 /* No operation */
DECL|macro|NPORT_DMODE0_RD
mdefine_line|#define NPORT_DMODE0_RD       0x00000001 /* Read operation */
DECL|macro|NPORT_DMODE0_DRAW
mdefine_line|#define NPORT_DMODE0_DRAW     0x00000002 /* Draw operation */
DECL|macro|NPORT_DMODE0_S2S
mdefine_line|#define NPORT_DMODE0_S2S      0x00000003 /* Screen to screen operation */
multiline_comment|/* The following decide what addressing mode(s) are to be used */
DECL|macro|NPORT_DMODE0_AMMASK
mdefine_line|#define NPORT_DMODE0_AMMASK   0x0000001c /* Address mode mask */
DECL|macro|NPORT_DMODE0_SPAN
mdefine_line|#define NPORT_DMODE0_SPAN     0x00000000 /* Spanning address mode */
DECL|macro|NPORT_DMODE0_BLOCK
mdefine_line|#define NPORT_DMODE0_BLOCK    0x00000004 /* Block address mode */
DECL|macro|NPORT_DMODE0_ILINE
mdefine_line|#define NPORT_DMODE0_ILINE    0x00000008 /* Iline address mode */
DECL|macro|NPORT_DMODE0_FLINE
mdefine_line|#define NPORT_DMODE0_FLINE    0x0000000c /* Fline address mode */
DECL|macro|NPORT_DMODE0_ALINE
mdefine_line|#define NPORT_DMODE0_ALINE    0x00000010 /* Aline address mode */
DECL|macro|NPORT_DMODE0_TLINE
mdefine_line|#define NPORT_DMODE0_TLINE    0x00000014 /* Tline address mode */
DECL|macro|NPORT_DMODE0_BLINE
mdefine_line|#define NPORT_DMODE0_BLINE    0x00000018 /* Bline address mode */
multiline_comment|/* And now some misc. operation control bits. */
DECL|macro|NPORT_DMODE0_DOSETUP
mdefine_line|#define NPORT_DMODE0_DOSETUP  0x00000020
DECL|macro|NPORT_DMODE0_CHOST
mdefine_line|#define NPORT_DMODE0_CHOST    0x00000040
DECL|macro|NPORT_DMODE0_AHOST
mdefine_line|#define NPORT_DMODE0_AHOST    0x00000080
DECL|macro|NPORT_DMODE0_STOPX
mdefine_line|#define NPORT_DMODE0_STOPX    0x00000100
DECL|macro|NPORT_DMODE0_STOPY
mdefine_line|#define NPORT_DMODE0_STOPY    0x00000200
DECL|macro|NPORT_DMODE0_SK1ST
mdefine_line|#define NPORT_DMODE0_SK1ST    0x00000400
DECL|macro|NPORT_DMODE0_SKLST
mdefine_line|#define NPORT_DMODE0_SKLST    0x00000800
DECL|macro|NPORT_DMODE0_ZPENAB
mdefine_line|#define NPORT_DMODE0_ZPENAB   0x00001000
DECL|macro|NPORT_DMODE0_LISPENAB
mdefine_line|#define NPORT_DMODE0_LISPENAB 0x00002000
DECL|macro|NPORT_DMODE0_LISLST
mdefine_line|#define NPORT_DMODE0_LISLST   0x00004000
DECL|macro|NPORT_DMODE0_L32
mdefine_line|#define NPORT_DMODE0_L32      0x00008000
DECL|macro|NPORT_DMODE0_ZOPQ
mdefine_line|#define NPORT_DMODE0_ZOPQ     0x00010000
DECL|macro|NPORT_DMODE0_LISOPQ
mdefine_line|#define NPORT_DMODE0_LISOPQ   0x00020000
DECL|macro|NPORT_DMODE0_SHADE
mdefine_line|#define NPORT_DMODE0_SHADE    0x00040000
DECL|macro|NPORT_DMODE0_LRONLY
mdefine_line|#define NPORT_DMODE0_LRONLY   0x00080000
DECL|macro|NPORT_DMODE0_XYOFF
mdefine_line|#define NPORT_DMODE0_XYOFF    0x00100000
DECL|macro|NPORT_DMODE0_CLAMP
mdefine_line|#define NPORT_DMODE0_CLAMP    0x00200000
DECL|macro|NPORT_DMODE0_ENDPF
mdefine_line|#define NPORT_DMODE0_ENDPF    0x00400000
DECL|macro|NPORT_DMODE0_YSTR
mdefine_line|#define NPORT_DMODE0_YSTR     0x00800000
DECL|member|lsmode
id|npireg_t
id|lsmode
suffix:semicolon
multiline_comment|/* Mode for line stipple ops */
DECL|member|lspattern
id|npireg_t
id|lspattern
suffix:semicolon
multiline_comment|/* Pattern for line stipple ops */
DECL|member|lspatsave
id|npireg_t
id|lspatsave
suffix:semicolon
multiline_comment|/* Backup save pattern */
DECL|member|zpattern
id|npireg_t
id|zpattern
suffix:semicolon
multiline_comment|/* Pixel zpattern */
DECL|member|colorback
id|npireg_t
id|colorback
suffix:semicolon
multiline_comment|/* Background color */
DECL|member|colorvram
id|npireg_t
id|colorvram
suffix:semicolon
multiline_comment|/* Clear color for fast vram */
DECL|member|alpharef
id|npireg_t
id|alpharef
suffix:semicolon
multiline_comment|/* Reference value for afunctions */
DECL|member|pad0
r_int
r_int
id|pad0
suffix:semicolon
DECL|member|smask0x
id|npireg_t
id|smask0x
suffix:semicolon
multiline_comment|/* Window GL relative screen mask 0 */
DECL|member|smask0y
id|npireg_t
id|smask0y
suffix:semicolon
multiline_comment|/* Window GL relative screen mask 0 */
DECL|member|_setup
id|npireg_t
id|_setup
suffix:semicolon
DECL|member|_stepz
id|npireg_t
id|_stepz
suffix:semicolon
DECL|member|_lsrestore
id|npireg_t
id|_lsrestore
suffix:semicolon
DECL|member|_lssave
id|npireg_t
id|_lssave
suffix:semicolon
DECL|member|_pad1
r_int
r_int
id|_pad1
(braket
l_int|0x30
)braket
suffix:semicolon
multiline_comment|/* Iterators, full state for context switch */
DECL|member|_xstart
id|npfreg_t
id|_xstart
suffix:semicolon
multiline_comment|/* X-start point (current) */
DECL|member|_ystart
id|npfreg_t
id|_ystart
suffix:semicolon
multiline_comment|/* Y-start point (current) */
DECL|member|_xend
id|npfreg_t
id|_xend
suffix:semicolon
multiline_comment|/* x-end point */
DECL|member|_yend
id|npfreg_t
id|_yend
suffix:semicolon
multiline_comment|/* y-end point */
DECL|member|xsave
id|npireg_t
id|xsave
suffix:semicolon
multiline_comment|/* copy of xstart integer value for BLOCk addressing MODE */
DECL|member|xymove
id|npireg_t
id|xymove
suffix:semicolon
multiline_comment|/* x.y offset from xstart, ystart for relative operations */
DECL|member|bresd
id|npfreg_t
id|bresd
suffix:semicolon
DECL|member|bress1
id|npfreg_t
id|bress1
suffix:semicolon
DECL|member|bresoctinc1
id|npireg_t
id|bresoctinc1
suffix:semicolon
DECL|member|bresrndinc2
r_volatile
r_int
id|bresrndinc2
suffix:semicolon
DECL|member|brese1
id|npireg_t
id|brese1
suffix:semicolon
DECL|member|bress2
id|npireg_t
id|bress2
suffix:semicolon
DECL|member|aweight0
id|npireg_t
id|aweight0
suffix:semicolon
DECL|member|aweight1
id|npireg_t
id|aweight1
suffix:semicolon
DECL|member|xstartf
id|npfreg_t
id|xstartf
suffix:semicolon
DECL|member|ystartf
id|npfreg_t
id|ystartf
suffix:semicolon
DECL|member|xendf
id|npfreg_t
id|xendf
suffix:semicolon
DECL|member|yendf
id|npfreg_t
id|yendf
suffix:semicolon
DECL|member|xstarti
id|npireg_t
id|xstarti
suffix:semicolon
DECL|member|xendf1
id|npfreg_t
id|xendf1
suffix:semicolon
DECL|member|xystarti
id|npireg_t
id|xystarti
suffix:semicolon
DECL|member|xyendi
id|npireg_t
id|xyendi
suffix:semicolon
DECL|member|xstartendi
id|npireg_t
id|xstartendi
suffix:semicolon
DECL|member|_unused2
r_int
r_int
id|_unused2
(braket
l_int|0x29
)braket
suffix:semicolon
DECL|member|colorred
id|npfreg_t
id|colorred
suffix:semicolon
DECL|member|coloralpha
id|npfreg_t
id|coloralpha
suffix:semicolon
DECL|member|colorgrn
id|npfreg_t
id|colorgrn
suffix:semicolon
DECL|member|colorblue
id|npfreg_t
id|colorblue
suffix:semicolon
DECL|member|slopered
id|npfreg_t
id|slopered
suffix:semicolon
DECL|member|slopealpha
id|npfreg_t
id|slopealpha
suffix:semicolon
DECL|member|slopegrn
id|npfreg_t
id|slopegrn
suffix:semicolon
DECL|member|slopeblue
id|npfreg_t
id|slopeblue
suffix:semicolon
DECL|member|wrmask
id|npireg_t
id|wrmask
suffix:semicolon
DECL|member|colori
id|npireg_t
id|colori
suffix:semicolon
DECL|member|colorx
id|npfreg_t
id|colorx
suffix:semicolon
DECL|member|slopered1
id|npfreg_t
id|slopered1
suffix:semicolon
DECL|member|hostrw0
id|npireg_t
id|hostrw0
suffix:semicolon
DECL|member|hostrw1
id|npireg_t
id|hostrw1
suffix:semicolon
DECL|member|dcbmode
id|npireg_t
id|dcbmode
suffix:semicolon
DECL|macro|NPORT_DMODE_WMASK
mdefine_line|#define NPORT_DMODE_WMASK   0x00000003
DECL|macro|NPORT_DMODE_W4
mdefine_line|#define NPORT_DMODE_W4      0x00000000
DECL|macro|NPORT_DMODE_W1
mdefine_line|#define NPORT_DMODE_W1      0x00000001
DECL|macro|NPORT_DMODE_W2
mdefine_line|#define NPORT_DMODE_W2      0x00000002
DECL|macro|NPORT_DMODE_W3
mdefine_line|#define NPORT_DMODE_W3      0x00000003
DECL|macro|NPORT_DMODE_EDPACK
mdefine_line|#define NPORT_DMODE_EDPACK  0x00000004
DECL|macro|NPORT_DMODE_ECINC
mdefine_line|#define NPORT_DMODE_ECINC   0x00000008
DECL|macro|NPORT_DMODE_CMASK
mdefine_line|#define NPORT_DMODE_CMASK   0x00000070
DECL|macro|NPORT_DMODE_AMASK
mdefine_line|#define NPORT_DMODE_AMASK   0x00000780
DECL|macro|NPORT_DMODE_AVC2
mdefine_line|#define NPORT_DMODE_AVC2    0x00000000
DECL|macro|NPORT_DMODE_ACMALL
mdefine_line|#define NPORT_DMODE_ACMALL  0x00000080
DECL|macro|NPORT_DMODE_ACM0
mdefine_line|#define NPORT_DMODE_ACM0    0x00000100
DECL|macro|NPORT_DMODE_ACM1
mdefine_line|#define NPORT_DMODE_ACM1    0x00000180
DECL|macro|NPORT_DMODE_AXMALL
mdefine_line|#define NPORT_DMODE_AXMALL  0x00000200
DECL|macro|NPORT_DMODE_AXM0
mdefine_line|#define NPORT_DMODE_AXM0    0x00000280
DECL|macro|NPORT_DMODE_AXM1
mdefine_line|#define NPORT_DMODE_AXM1    0x00000300
DECL|macro|NPORT_DMODE_ABT
mdefine_line|#define NPORT_DMODE_ABT     0x00000380
DECL|macro|NPORT_DMODE_AVCC1
mdefine_line|#define NPORT_DMODE_AVCC1   0x00000400
DECL|macro|NPORT_DMODE_AVAB1
mdefine_line|#define NPORT_DMODE_AVAB1   0x00000480
DECL|macro|NPORT_DMODE_ALG3V0
mdefine_line|#define NPORT_DMODE_ALG3V0  0x00000500
DECL|macro|NPORT_DMODE_A1562
mdefine_line|#define NPORT_DMODE_A1562   0x00000580
DECL|macro|NPORT_DMODE_ESACK
mdefine_line|#define NPORT_DMODE_ESACK   0x00000800
DECL|macro|NPORT_DMODE_EASACK
mdefine_line|#define NPORT_DMODE_EASACK  0x00001000
DECL|macro|NPORT_DMODE_CWMASK
mdefine_line|#define NPORT_DMODE_CWMASK  0x0003e000
DECL|macro|NPORT_DMODE_CHMASK
mdefine_line|#define NPORT_DMODE_CHMASK  0x007c0000
DECL|macro|NPORT_DMODE_CSMASK
mdefine_line|#define NPORT_DMODE_CSMASK  0x0f800000
DECL|macro|NPORT_DMODE_SENDIAN
mdefine_line|#define NPORT_DMODE_SENDIAN 0x10000000
DECL|member|_unused3
r_int
r_int
id|_unused3
suffix:semicolon
DECL|member|dcbdata0
r_union
id|np_dcb
id|dcbdata0
suffix:semicolon
DECL|member|dcbdata1
id|npireg_t
id|dcbdata1
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|newport_cregs
r_struct
id|newport_cregs
(brace
DECL|member|smask1x
id|npireg_t
id|smask1x
suffix:semicolon
DECL|member|smask1y
id|npireg_t
id|smask1y
suffix:semicolon
DECL|member|smask2x
id|npireg_t
id|smask2x
suffix:semicolon
DECL|member|smask2y
id|npireg_t
id|smask2y
suffix:semicolon
DECL|member|smask3x
id|npireg_t
id|smask3x
suffix:semicolon
DECL|member|smask3y
id|npireg_t
id|smask3y
suffix:semicolon
DECL|member|smask4x
id|npireg_t
id|smask4x
suffix:semicolon
DECL|member|smask4y
id|npireg_t
id|smask4y
suffix:semicolon
DECL|member|topscan
id|npireg_t
id|topscan
suffix:semicolon
DECL|member|xywin
id|npireg_t
id|xywin
suffix:semicolon
DECL|member|clipmode
id|npireg_t
id|clipmode
suffix:semicolon
DECL|macro|NPORT_CMODE_SM0
mdefine_line|#define NPORT_CMODE_SM0   0x00000001
DECL|macro|NPORT_CMODE_SM1
mdefine_line|#define NPORT_CMODE_SM1   0x00000002
DECL|macro|NPORT_CMODE_SM2
mdefine_line|#define NPORT_CMODE_SM2   0x00000004
DECL|macro|NPORT_CMODE_SM3
mdefine_line|#define NPORT_CMODE_SM3   0x00000008
DECL|macro|NPORT_CMODE_SM4
mdefine_line|#define NPORT_CMODE_SM4   0x00000010
DECL|macro|NPORT_CMODE_CMSK
mdefine_line|#define NPORT_CMODE_CMSK  0x00001e00
DECL|member|_unused0
r_int
r_int
id|_unused0
suffix:semicolon
DECL|member|config
r_int
r_int
id|config
suffix:semicolon
DECL|macro|NPORT_CFG_G32MD
mdefine_line|#define NPORT_CFG_G32MD   0x00000001
DECL|macro|NPORT_CFG_BWIDTH
mdefine_line|#define NPORT_CFG_BWIDTH  0x00000002
DECL|macro|NPORT_CFG_ERCVR
mdefine_line|#define NPORT_CFG_ERCVR   0x00000004
DECL|macro|NPORT_CFG_BDMSK
mdefine_line|#define NPORT_CFG_BDMSK   0x00000078
DECL|macro|NPORT_CFG_BFAINT
mdefine_line|#define NPORT_CFG_BFAINT  0x00000080
DECL|macro|NPORT_CFG_GDMSK
mdefine_line|#define NPORT_CFG_GDMSK   0x00001f80
DECL|macro|NPORT_CFG_GD0
mdefine_line|#define NPORT_CFG_GD0     0x00000100
DECL|macro|NPORT_CFG_GD1
mdefine_line|#define NPORT_CFG_GD1     0x00000200
DECL|macro|NPORT_CFG_GD2
mdefine_line|#define NPORT_CFG_GD2     0x00000400
DECL|macro|NPORT_CFG_GD3
mdefine_line|#define NPORT_CFG_GD3     0x00000800
DECL|macro|NPORT_CFG_GD4
mdefine_line|#define NPORT_CFG_GD4     0x00001000
DECL|macro|NPORT_CFG_GFAINT
mdefine_line|#define NPORT_CFG_GFAINT  0x00002000
DECL|macro|NPORT_CFG_TOMSK
mdefine_line|#define NPORT_CFG_TOMSK   0x0001c000
DECL|macro|NPORT_CFG_VRMSK
mdefine_line|#define NPORT_CFG_VRMSK   0x000e0000
DECL|macro|NPORT_CFG_FBTYP
mdefine_line|#define NPORT_CFG_FBTYP   0x00100000
DECL|member|_unused1
id|npireg_t
id|_unused1
suffix:semicolon
DECL|member|status
id|npireg_t
id|status
suffix:semicolon
DECL|macro|NPORT_STAT_VERS
mdefine_line|#define NPORT_STAT_VERS   0x00000007
DECL|macro|NPORT_STAT_GBUSY
mdefine_line|#define NPORT_STAT_GBUSY  0x00000008
DECL|macro|NPORT_STAT_BBUSY
mdefine_line|#define NPORT_STAT_BBUSY  0x00000010
DECL|macro|NPORT_STAT_VRINT
mdefine_line|#define NPORT_STAT_VRINT  0x00000020
DECL|macro|NPORT_STAT_VIDINT
mdefine_line|#define NPORT_STAT_VIDINT 0x00000040
DECL|macro|NPORT_STAT_GLMSK
mdefine_line|#define NPORT_STAT_GLMSK  0x00001f80
DECL|macro|NPORT_STAT_BLMSK
mdefine_line|#define NPORT_STAT_BLMSK  0x0007e000
DECL|macro|NPORT_STAT_BFIRQ
mdefine_line|#define NPORT_STAT_BFIRQ  0x00080000
DECL|macro|NPORT_STAT_GFIRQ
mdefine_line|#define NPORT_STAT_GFIRQ  0x00100000
DECL|member|ustatus
id|npireg_t
id|ustatus
suffix:semicolon
DECL|member|dcbreset
id|npireg_t
id|dcbreset
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|newport_regs
r_struct
id|newport_regs
(brace
DECL|member|set
r_struct
id|newport_rexregs
id|set
suffix:semicolon
DECL|member|_unused0
r_int
r_int
id|_unused0
(braket
l_int|0x16e
)braket
suffix:semicolon
DECL|member|go
r_struct
id|newport_rexregs
id|go
suffix:semicolon
DECL|member|_unused1
r_int
r_int
id|_unused1
(braket
l_int|0x22e
)braket
suffix:semicolon
DECL|member|cset
r_struct
id|newport_cregs
id|cset
suffix:semicolon
DECL|member|_unused2
r_int
r_int
id|_unused2
(braket
l_int|0x1ef
)braket
suffix:semicolon
DECL|member|cgo
r_struct
id|newport_cregs
id|cgo
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|newport_regs
op_star
id|npregs
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|drawmode1
r_int
r_int
id|drawmode1
suffix:semicolon
DECL|member|drawmode0
r_int
r_int
id|drawmode0
suffix:semicolon
DECL|member|lsmode
r_int
r_int
id|lsmode
suffix:semicolon
DECL|member|lspattern
r_int
r_int
id|lspattern
suffix:semicolon
DECL|member|lspatsave
r_int
r_int
id|lspatsave
suffix:semicolon
DECL|member|zpattern
r_int
r_int
id|zpattern
suffix:semicolon
DECL|member|colorback
r_int
r_int
id|colorback
suffix:semicolon
DECL|member|colorvram
r_int
r_int
id|colorvram
suffix:semicolon
DECL|member|alpharef
r_int
r_int
id|alpharef
suffix:semicolon
DECL|member|smask0x
r_int
r_int
id|smask0x
suffix:semicolon
DECL|member|smask0y
r_int
r_int
id|smask0y
suffix:semicolon
DECL|member|_xstart
r_int
r_int
id|_xstart
suffix:semicolon
DECL|member|_ystart
r_int
r_int
id|_ystart
suffix:semicolon
DECL|member|_xend
r_int
r_int
id|_xend
suffix:semicolon
DECL|member|_yend
r_int
r_int
id|_yend
suffix:semicolon
DECL|member|xsave
r_int
r_int
id|xsave
suffix:semicolon
DECL|member|xymove
r_int
r_int
id|xymove
suffix:semicolon
DECL|member|bresd
r_int
r_int
id|bresd
suffix:semicolon
DECL|member|bress1
r_int
r_int
id|bress1
suffix:semicolon
DECL|member|bresoctinc1
r_int
r_int
id|bresoctinc1
suffix:semicolon
DECL|member|bresrndinc2
r_int
r_int
id|bresrndinc2
suffix:semicolon
DECL|member|brese1
r_int
r_int
id|brese1
suffix:semicolon
DECL|member|bress2
r_int
r_int
id|bress2
suffix:semicolon
DECL|member|aweight0
r_int
r_int
id|aweight0
suffix:semicolon
DECL|member|aweight1
r_int
r_int
id|aweight1
suffix:semicolon
DECL|member|colorred
r_int
r_int
id|colorred
suffix:semicolon
DECL|member|coloralpha
r_int
r_int
id|coloralpha
suffix:semicolon
DECL|member|colorgrn
r_int
r_int
id|colorgrn
suffix:semicolon
DECL|member|colorblue
r_int
r_int
id|colorblue
suffix:semicolon
DECL|member|slopered
r_int
r_int
id|slopered
suffix:semicolon
DECL|member|slopealpha
r_int
r_int
id|slopealpha
suffix:semicolon
DECL|member|slopegrn
r_int
r_int
id|slopegrn
suffix:semicolon
DECL|member|slopeblue
r_int
r_int
id|slopeblue
suffix:semicolon
DECL|member|wrmask
r_int
r_int
id|wrmask
suffix:semicolon
DECL|member|hostrw0
r_int
r_int
id|hostrw0
suffix:semicolon
DECL|member|hostrw1
r_int
r_int
id|hostrw1
suffix:semicolon
multiline_comment|/* configregs */
DECL|member|smask1x
r_int
r_int
id|smask1x
suffix:semicolon
DECL|member|smask1y
r_int
r_int
id|smask1y
suffix:semicolon
DECL|member|smask2x
r_int
r_int
id|smask2x
suffix:semicolon
DECL|member|smask2y
r_int
r_int
id|smask2y
suffix:semicolon
DECL|member|smask3x
r_int
r_int
id|smask3x
suffix:semicolon
DECL|member|smask3y
r_int
r_int
id|smask3y
suffix:semicolon
DECL|member|smask4x
r_int
r_int
id|smask4x
suffix:semicolon
DECL|member|smask4y
r_int
r_int
id|smask4y
suffix:semicolon
DECL|member|topscan
r_int
r_int
id|topscan
suffix:semicolon
DECL|member|xywin
r_int
r_int
id|xywin
suffix:semicolon
DECL|member|clipmode
r_int
r_int
id|clipmode
suffix:semicolon
DECL|member|config
r_int
r_int
id|config
suffix:semicolon
multiline_comment|/* dcb registers */
DECL|member|dcbmode
r_int
r_int
id|dcbmode
suffix:semicolon
DECL|member|dcbdata0
r_int
r_int
id|dcbdata0
suffix:semicolon
DECL|member|dcbdata1
r_int
r_int
id|dcbdata1
suffix:semicolon
DECL|typedef|newport_ctx
)brace
id|newport_ctx
suffix:semicolon
multiline_comment|/* Reading/writing VC2 registers. */
DECL|macro|VC2_REGADDR_INDEX
mdefine_line|#define VC2_REGADDR_INDEX      0x00000000
DECL|macro|VC2_REGADDR_IREG
mdefine_line|#define VC2_REGADDR_IREG       0x00000010
DECL|macro|VC2_REGADDR_RAM
mdefine_line|#define VC2_REGADDR_RAM        0x00000030
DECL|macro|VC2_PROTOCOL
mdefine_line|#define VC2_PROTOCOL           (NPORT_DMODE_EASACK | 0x00800000 | 0x00040000)
DECL|macro|VC2_VLINET_ADDR
mdefine_line|#define VC2_VLINET_ADDR        0x000
DECL|macro|VC2_VFRAMET_ADDR
mdefine_line|#define VC2_VFRAMET_ADDR       0x400
DECL|macro|VC2_CGLYPH_ADDR
mdefine_line|#define VC2_CGLYPH_ADDR        0x500
multiline_comment|/* Now the Indexed registers of the VC2. */
DECL|macro|VC2_IREG_VENTRY
mdefine_line|#define VC2_IREG_VENTRY        0x00
DECL|macro|VC2_IREG_CENTRY
mdefine_line|#define VC2_IREG_CENTRY        0x01
DECL|macro|VC2_IREG_CURSX
mdefine_line|#define VC2_IREG_CURSX         0x02
DECL|macro|VC2_IREG_CURSY
mdefine_line|#define VC2_IREG_CURSY         0x03
DECL|macro|VC2_IREG_CCURSX
mdefine_line|#define VC2_IREG_CCURSX        0x04
DECL|macro|VC2_IREG_DENTRY
mdefine_line|#define VC2_IREG_DENTRY        0x05
DECL|macro|VC2_IREG_SLEN
mdefine_line|#define VC2_IREG_SLEN          0x06
DECL|macro|VC2_IREG_RADDR
mdefine_line|#define VC2_IREG_RADDR         0x07
DECL|macro|VC2_IREG_VFPTR
mdefine_line|#define VC2_IREG_VFPTR         0x08
DECL|macro|VC2_IREG_VLSPTR
mdefine_line|#define VC2_IREG_VLSPTR        0x09
DECL|macro|VC2_IREG_VLIR
mdefine_line|#define VC2_IREG_VLIR          0x0a
DECL|macro|VC2_IREG_VLCTR
mdefine_line|#define VC2_IREG_VLCTR         0x0b
DECL|macro|VC2_IREG_CTPTR
mdefine_line|#define VC2_IREG_CTPTR         0x0c
DECL|macro|VC2_IREG_WCURSY
mdefine_line|#define VC2_IREG_WCURSY        0x0d
DECL|macro|VC2_IREG_DFPTR
mdefine_line|#define VC2_IREG_DFPTR         0x0e
DECL|macro|VC2_IREG_DLTPTR
mdefine_line|#define VC2_IREG_DLTPTR        0x0f
DECL|macro|VC2_IREG_CONTROL
mdefine_line|#define VC2_IREG_CONTROL       0x10
DECL|macro|VC2_IREG_CONFIG
mdefine_line|#define VC2_IREG_CONFIG        0x20
DECL|function|newport_vc2_set
r_extern
id|__inline__
r_void
id|newport_vc2_set
c_func
(paren
r_struct
id|newport_regs
op_star
id|regs
comma
r_int
r_char
id|vc2ireg
comma
r_int
r_int
id|val
)paren
(brace
id|regs-&gt;set.dcbmode
op_assign
(paren
id|NPORT_DMODE_AVC2
op_or
id|VC2_REGADDR_INDEX
op_or
id|NPORT_DMODE_W3
op_or
id|NPORT_DMODE_ECINC
op_or
id|VC2_PROTOCOL
)paren
suffix:semicolon
id|regs-&gt;set.dcbdata0.byword
op_assign
(paren
id|vc2ireg
op_lshift
l_int|24
)paren
op_or
(paren
id|val
op_lshift
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|newport_vc2_get
r_extern
id|__inline__
r_int
r_int
id|newport_vc2_get
c_func
(paren
r_struct
id|newport_regs
op_star
id|regs
comma
r_int
r_char
id|vc2ireg
)paren
(brace
id|regs-&gt;set.dcbmode
op_assign
(paren
id|NPORT_DMODE_AVC2
op_or
id|VC2_REGADDR_INDEX
op_or
id|NPORT_DMODE_W1
op_or
id|NPORT_DMODE_ECINC
op_or
id|VC2_PROTOCOL
)paren
suffix:semicolon
id|regs-&gt;set.dcbdata0.bybytes.b3
op_assign
id|vc2ireg
suffix:semicolon
id|regs-&gt;set.dcbmode
op_assign
(paren
id|NPORT_DMODE_AVC2
op_or
id|VC2_REGADDR_IREG
op_or
id|NPORT_DMODE_W2
op_or
id|NPORT_DMODE_ECINC
op_or
id|VC2_PROTOCOL
)paren
suffix:semicolon
r_return
id|regs-&gt;set.dcbdata0.byshort.s1
suffix:semicolon
)brace
multiline_comment|/* VC2 Control register bits */
DECL|macro|VC2_CTRL_EVIRQ
mdefine_line|#define VC2_CTRL_EVIRQ     0x0001
DECL|macro|VC2_CTRL_EDISP
mdefine_line|#define VC2_CTRL_EDISP     0x0002
DECL|macro|VC2_CTRL_EVIDEO
mdefine_line|#define VC2_CTRL_EVIDEO    0x0004
DECL|macro|VC2_CTRL_EDIDS
mdefine_line|#define VC2_CTRL_EDIDS     0x0008
DECL|macro|VC2_CTRL_ECURS
mdefine_line|#define VC2_CTRL_ECURS     0x0010
DECL|macro|VC2_CTRL_EGSYNC
mdefine_line|#define VC2_CTRL_EGSYNC    0x0020
DECL|macro|VC2_CTRL_EILACE
mdefine_line|#define VC2_CTRL_EILACE    0x0040
DECL|macro|VC2_CTRL_ECDISP
mdefine_line|#define VC2_CTRL_ECDISP    0x0080
DECL|macro|VC2_CTRL_ECCURS
mdefine_line|#define VC2_CTRL_ECCURS    0x0100
DECL|macro|VC2_CTRL_ECG64
mdefine_line|#define VC2_CTRL_ECG64     0x0200
DECL|macro|VC2_CTRL_GLSEL
mdefine_line|#define VC2_CTRL_GLSEL     0x0400
multiline_comment|/* Controlling the color map on NEWPORT. */
DECL|macro|NCMAP_REGADDR_AREG
mdefine_line|#define NCMAP_REGADDR_AREG   0x00000000
DECL|macro|NCMAP_REGADDR_ALO
mdefine_line|#define NCMAP_REGADDR_ALO    0x00000000
DECL|macro|NCMAP_REGADDR_AHI
mdefine_line|#define NCMAP_REGADDR_AHI    0x00000010
DECL|macro|NCMAP_REGADDR_PBUF
mdefine_line|#define NCMAP_REGADDR_PBUF   0x00000020
DECL|macro|NCMAP_REGADDR_CREG
mdefine_line|#define NCMAP_REGADDR_CREG   0x00000030
DECL|macro|NCMAP_REGADDR_SREG
mdefine_line|#define NCMAP_REGADDR_SREG   0x00000040
DECL|macro|NCMAP_REGADDR_RREG
mdefine_line|#define NCMAP_REGADDR_RREG   0x00000060
DECL|macro|NCMAP_PROTOCOL
mdefine_line|#define NCMAP_PROTOCOL       (0x00008000 | 0x00040000 | 0x00800000)
DECL|function|newport_cmap_setaddr
r_static
id|__inline__
r_void
id|newport_cmap_setaddr
c_func
(paren
r_struct
id|newport_regs
op_star
id|regs
comma
r_int
r_int
id|addr
)paren
(brace
id|regs-&gt;set.dcbmode
op_assign
(paren
id|NPORT_DMODE_ACMALL
op_or
id|NCMAP_PROTOCOL
op_or
id|NPORT_DMODE_SENDIAN
op_or
id|NPORT_DMODE_ECINC
op_or
id|NCMAP_REGADDR_AREG
op_or
id|NPORT_DMODE_W2
)paren
suffix:semicolon
id|regs-&gt;set.dcbdata0.byshort.s1
op_assign
id|addr
suffix:semicolon
id|regs-&gt;set.dcbmode
op_assign
(paren
id|NPORT_DMODE_ACMALL
op_or
id|NCMAP_PROTOCOL
op_or
id|NCMAP_REGADDR_PBUF
op_or
id|NPORT_DMODE_W3
)paren
suffix:semicolon
)brace
DECL|function|newport_cmap_setrgb
r_static
id|__inline__
r_void
id|newport_cmap_setrgb
c_func
(paren
r_struct
id|newport_regs
op_star
id|regs
comma
r_int
r_char
id|red
comma
r_int
r_char
id|green
comma
r_int
r_char
id|blue
)paren
(brace
id|regs-&gt;set.dcbdata0.byword
op_assign
(paren
id|red
op_lshift
l_int|24
)paren
op_or
(paren
id|green
op_lshift
l_int|16
)paren
op_or
(paren
id|blue
op_lshift
l_int|8
)paren
suffix:semicolon
)brace
multiline_comment|/* Miscellaneous NEWPORT routines. */
DECL|macro|BUSY_TIMEOUT
mdefine_line|#define BUSY_TIMEOUT 100000
DECL|function|newport_wait
r_static
id|__inline__
r_int
id|newport_wait
c_func
(paren
r_void
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|BUSY_TIMEOUT
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|npregs-&gt;cset.status
op_amp
id|NPORT_STAT_GBUSY
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
id|BUSY_TIMEOUT
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|newport_bfwait
r_static
id|__inline__
r_int
id|newport_bfwait
c_func
(paren
r_void
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|BUSY_TIMEOUT
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|npregs-&gt;cset.status
op_amp
id|NPORT_STAT_BBUSY
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
id|BUSY_TIMEOUT
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* newport.c and cons_newport.c routines */
r_extern
r_struct
id|graphics_ops
op_star
id|newport_probe
(paren
r_int
comma
r_const
r_char
op_star
op_star
)paren
suffix:semicolon
r_void
id|newport_save
(paren
r_void
op_star
)paren
suffix:semicolon
r_void
id|newport_restore
(paren
r_void
op_star
)paren
suffix:semicolon
r_void
id|newport_reset
(paren
r_void
)paren
suffix:semicolon
r_int
id|newport_ioctl
(paren
r_int
id|card
comma
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
multiline_comment|/*&n; * DCBMODE register defines:&n; */
multiline_comment|/* Width of the data being transferred for each DCBDATA[01] word */
DECL|macro|DCB_DATAWIDTH_4
mdefine_line|#define DCB_DATAWIDTH_4 0x0
DECL|macro|DCB_DATAWIDTH_1
mdefine_line|#define DCB_DATAWIDTH_1 0x1
DECL|macro|DCB_DATAWIDTH_2
mdefine_line|#define DCB_DATAWIDTH_2 0x2
DECL|macro|DCB_DATAWIDTH_3
mdefine_line|#define DCB_DATAWIDTH_3 0x3
multiline_comment|/* If set, all of DCBDATA will be moved, otherwise only DATAWIDTH bytes */
DECL|macro|DCB_ENDATAPACK
mdefine_line|#define DCB_ENDATAPACK   (1 &lt;&lt; 2)
multiline_comment|/* Enables DCBCRS auto increment after each DCB transfer */
DECL|macro|DCB_ENCRSINC
mdefine_line|#define DCB_ENCRSINC     (1 &lt;&lt; 3)
multiline_comment|/* shift for accessing the control register select address (DBCCRS, 3 bits) */
DECL|macro|DCB_CRS_SHIFT
mdefine_line|#define DCB_CRS_SHIFT    4
multiline_comment|/* DCBADDR (4 bits): display bus slave address */
DECL|macro|DCB_ADDR_SHIFT
mdefine_line|#define DCB_ADDR_SHIFT   7
DECL|macro|DCB_VC2
mdefine_line|#define DCB_VC2          (0 &lt;&lt;  DCB_ADDR_SHIFT)
DECL|macro|DCB_CMAP_ALL
mdefine_line|#define DCB_CMAP_ALL     (1 &lt;&lt;  DCB_ADDR_SHIFT)
DECL|macro|DCB_CMAP0
mdefine_line|#define DCB_CMAP0        (2 &lt;&lt;  DCB_ADDR_SHIFT)
DECL|macro|DCB_CMAP1
mdefine_line|#define DCB_CMAP1        (3 &lt;&lt;  DCB_ADDR_SHIFT)
DECL|macro|DCB_XMAP_ALL
mdefine_line|#define DCB_XMAP_ALL     (4 &lt;&lt;  DCB_ADDR_SHIFT)
DECL|macro|DCB_XMAP0
mdefine_line|#define DCB_XMAP0        (5 &lt;&lt;  DCB_ADDR_SHIFT)
DECL|macro|DCB_XMAP1
mdefine_line|#define DCB_XMAP1        (6 &lt;&lt;  DCB_ADDR_SHIFT)
DECL|macro|DCB_BT445
mdefine_line|#define DCB_BT445        (7 &lt;&lt;  DCB_ADDR_SHIFT)
DECL|macro|DCB_VCC1
mdefine_line|#define DCB_VCC1         (8 &lt;&lt;  DCB_ADDR_SHIFT)
DECL|macro|DCB_VAB1
mdefine_line|#define DCB_VAB1         (9 &lt;&lt;  DCB_ADDR_SHIFT)
DECL|macro|DCB_LG3_BDVERS0
mdefine_line|#define DCB_LG3_BDVERS0  (10 &lt;&lt; DCB_ADDR_SHIFT)
DECL|macro|DCB_LG3_ICS1562
mdefine_line|#define DCB_LG3_ICS1562  (11 &lt;&lt; DCB_ADDR_SHIFT)
DECL|macro|DCB_RESERVED
mdefine_line|#define DCB_RESERVED     (15 &lt;&lt; DCB_ADDR_SHIFT)
multiline_comment|/* DCB protocol ack types */
DECL|macro|DCB_ENSYNCACK
mdefine_line|#define DCB_ENSYNCACK    (1 &lt;&lt; 11)
DECL|macro|DCB_ENASYNCACK
mdefine_line|#define DCB_ENASYNCACK   (1 &lt;&lt; 12)
DECL|macro|DCB_CSWIDTH_SHIFT
mdefine_line|#define DCB_CSWIDTH_SHIFT 13
DECL|macro|DCB_CSHOLD_SHIFT
mdefine_line|#define DCB_CSHOLD_SHIFT  18
DECL|macro|DCB_CSSETUP_SHIFT
mdefine_line|#define DCB_CSSETUP_SHIFT 23
multiline_comment|/* XMAP9 specific defines */
multiline_comment|/*   XMAP9 -- registers as seen on the DCBMODE register*/
DECL|macro|XM9_CRS_CONFIG
macro_line|#   define XM9_CRS_CONFIG            (0 &lt;&lt; DCB_CRS_SHIFT)
DECL|macro|XM9_PUPMODE
macro_line|#       define XM9_PUPMODE           (1 &lt;&lt; 0)
DECL|macro|XM9_ODD_PIXEL
macro_line|#       define XM9_ODD_PIXEL         (1 &lt;&lt; 1)
DECL|macro|XM9_8_BITPLANES
macro_line|#       define XM9_8_BITPLANES       (1 &lt;&lt; 2)
DECL|macro|XM9_SLOW_DCB
macro_line|#       define XM9_SLOW_DCB          (1 &lt;&lt; 3)
DECL|macro|XM9_VIDEO_RGBMAP_MASK
macro_line|#       define XM9_VIDEO_RGBMAP_MASK (3 &lt;&lt; 4)
DECL|macro|XM9_EXPRESS_VIDEO
macro_line|#       define XM9_EXPRESS_VIDEO     (1 &lt;&lt; 6)
DECL|macro|XM9_VIDEO_OPTION
macro_line|#       define XM9_VIDEO_OPTION      (1 &lt;&lt; 7)
DECL|macro|XM9_CRS_REVISION
macro_line|#   define XM9_CRS_REVISION          (1 &lt;&lt; DCB_CRS_SHIFT)
DECL|macro|XM9_CRS_FIFO_AVAIL
macro_line|#   define XM9_CRS_FIFO_AVAIL        (2 &lt;&lt; DCB_CRS_SHIFT)
DECL|macro|XM9_FIFO_0_AVAIL
macro_line|#       define XM9_FIFO_0_AVAIL      0
DECL|macro|XM9_FIFO_1_AVAIL
macro_line|#       define XM9_FIFO_1_AVAIL      1
DECL|macro|XM9_FIFO_2_AVAIL
macro_line|#       define XM9_FIFO_2_AVAIL      3
DECL|macro|XM9_FIFO_3_AVAIL
macro_line|#       define XM9_FIFO_3_AVAIL      2
DECL|macro|XM9_FIFO_FULL
macro_line|#       define XM9_FIFO_FULL         XM9_FIFO_0_AVAIL
DECL|macro|XM9_FIFO_EMPTY
macro_line|#       define XM9_FIFO_EMPTY        XM9_FIFO_3_AVAIL
DECL|macro|XM9_CRS_CURS_CMAP_MSB
macro_line|#   define XM9_CRS_CURS_CMAP_MSB     (3 &lt;&lt; DCB_CRS_SHIFT)
DECL|macro|XM9_CRS_PUP_CMAP_MSB
macro_line|#   define XM9_CRS_PUP_CMAP_MSB      (4 &lt;&lt; DCB_CRS_SHIFT)
DECL|macro|XM9_CRS_MODE_REG_DATA
macro_line|#   define XM9_CRS_MODE_REG_DATA     (5 &lt;&lt; DCB_CRS_SHIFT)
DECL|macro|XM9_CRS_MODE_REG_INDEX
macro_line|#   define XM9_CRS_MODE_REG_INDEX    (7 &lt;&lt; DCB_CRS_SHIFT)
DECL|macro|DCB_CYCLES
mdefine_line|#define DCB_CYCLES(setup,hold,width)                &bslash;&n;                  ((hold &lt;&lt; DCB_CSHOLD_SHIFT)  |    &bslash;&n;&t;&t;   (setup &lt;&lt; DCB_CSSETUP_SHIFT)|    &bslash;&n;&t;&t;   (width &lt;&lt; DCB_CSWIDTH_SHIFT))
DECL|macro|W_DCB_XMAP9_PROTOCOL
mdefine_line|#define W_DCB_XMAP9_PROTOCOL       DCB_CYCLES (2, 1, 0)
DECL|macro|WSLOW_DCB_XMAP9_PROTOCOL
mdefine_line|#define WSLOW_DCB_XMAP9_PROTOCOL   DCB_CYCLES (5, 5, 0)
DECL|macro|WAYSLOW_DCB_XMAP9_PROTOCOL
mdefine_line|#define WAYSLOW_DCB_XMAP9_PROTOCOL DCB_CYCLES (12, 12, 0)
DECL|macro|R_DCB_XMAP9_PROTOCOL
mdefine_line|#define R_DCB_XMAP9_PROTOCOL       DCB_CYCLES (2, 1, 3)
r_static
id|__inline__
r_void
DECL|function|xmap9FIFOWait
id|xmap9FIFOWait
(paren
r_struct
id|newport_regs
op_star
id|rex
)paren
(brace
id|rex-&gt;set.dcbmode
op_assign
id|DCB_XMAP0
op_or
id|XM9_CRS_FIFO_AVAIL
op_or
id|DCB_DATAWIDTH_1
op_or
id|R_DCB_XMAP9_PROTOCOL
suffix:semicolon
id|newport_bfwait
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|rex-&gt;set.dcbdata0.bybytes.b3
op_amp
l_int|3
)paren
op_ne
id|XM9_FIFO_EMPTY
)paren
suffix:semicolon
)brace
r_static
id|__inline__
r_void
DECL|function|xmap9SetModeReg
id|xmap9SetModeReg
(paren
r_struct
id|newport_regs
op_star
id|rex
comma
r_int
r_int
id|modereg
comma
r_int
r_int
id|data24
comma
r_int
id|cfreq
)paren
(brace
r_if
c_cond
(paren
id|cfreq
OG
l_int|119
)paren
id|rex-&gt;set.dcbmode
op_assign
id|DCB_XMAP_ALL
op_or
id|XM9_CRS_MODE_REG_DATA
op_or
id|DCB_DATAWIDTH_4
op_or
id|W_DCB_XMAP9_PROTOCOL
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cfreq
OG
l_int|59
)paren
id|rex-&gt;set.dcbmode
op_assign
id|DCB_XMAP_ALL
op_or
id|XM9_CRS_MODE_REG_DATA
op_or
id|DCB_DATAWIDTH_4
op_or
id|WSLOW_DCB_XMAP9_PROTOCOL
suffix:semicolon
r_else
id|rex-&gt;set.dcbmode
op_assign
id|DCB_XMAP_ALL
op_or
id|XM9_CRS_MODE_REG_DATA
op_or
id|DCB_DATAWIDTH_4
op_or
id|WAYSLOW_DCB_XMAP9_PROTOCOL
suffix:semicolon
id|rex-&gt;set.dcbdata0.byword
op_assign
(paren
(paren
id|modereg
)paren
op_lshift
l_int|24
)paren
op_or
(paren
id|data24
op_amp
l_int|0xffffff
)paren
suffix:semicolon
)brace
DECL|macro|BT445_PROTOCOL
mdefine_line|#define BT445_PROTOCOL&t;&t;DCB_CYCLES(1,1,3)
DECL|macro|BT445_CSR_ADDR_REG
mdefine_line|#define BT445_CSR_ADDR_REG&t;(0 &lt;&lt; DCB_CRS_SHIFT)
DECL|macro|BT445_CSR_REVISION
mdefine_line|#define BT445_CSR_REVISION&t;(2 &lt;&lt; DCB_CRS_SHIFT)
DECL|macro|BT445_REVISION_REG
mdefine_line|#define BT445_REVISION_REG&t;0x01
macro_line|#endif /* !(_SGI_NEWPORT_H) */
eof
