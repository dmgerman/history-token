multiline_comment|/* $Id: ng1hw.h,v 1.4 1999/08/04 06:01:51 ulfc Exp $&n; * &n; * ng1hw.h: Tweaks the newport.h structures and definations to be compatible&n; * &t;    with IRIX.  Quite ugly, but it works.&n; *&n; * Copyright (C) 1999 Ulf Carlsson (ulfc@thepuffingroup.com)&n; *&n; */
macro_line|#ifndef _SGI_NG1HW_H
DECL|macro|_SGI_NG1HW_H
mdefine_line|#define _SGI_NG1HW_H
macro_line|#include &lt;video/newport.h&gt;
DECL|macro|rex3regs
mdefine_line|#define rex3regs&t;newport_rexregs
DECL|macro|configregs
mdefine_line|#define configregs&t;newport_cregs
DECL|macro|float_long
mdefine_line|#define float_long&t;npfreg_t
DECL|typedef|Rex3regs
r_typedef
r_struct
id|newport_rexregs
id|Rex3regs
suffix:semicolon
DECL|typedef|Configregs
r_typedef
r_struct
id|newport_cregs
id|Configregs
suffix:semicolon
DECL|typedef|DCB_reg
r_typedef
r_union
id|np_dcb
id|DCB_reg
suffix:semicolon
multiline_comment|/* It looks like I can&squot;t do a simple tweak with this structure because the IRIX&n; * version is just *too* stupid.  Ok, here&squot;s a new version of it..&n; */
DECL|struct|rex3chip
r_struct
id|rex3chip
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
r_struct
(brace
DECL|member|set
r_struct
id|newport_cregs
id|set
suffix:semicolon
DECL|member|_unused2
r_int
r_int
id|_unused2
(braket
l_int|0x1ef
)braket
suffix:semicolon
DECL|member|go
r_struct
id|newport_cregs
id|go
suffix:semicolon
DECL|member|p1
)brace
id|p1
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|rex3Chip
r_typedef
r_struct
id|rex3chip
id|rex3Chip
suffix:semicolon
DECL|typedef|Rex3chip
r_typedef
r_struct
id|rex3chip
id|Rex3chip
suffix:semicolon
multiline_comment|/* Tweak the defines .. */
DECL|macro|DM0_OPCODE
mdefine_line|#define DM0_OPCODE&t;&t;NPORT_DMODE0_OPMASK
DECL|macro|DM0_NOP
mdefine_line|#define DM0_NOP&t;&t;&t;NPORT_DMODE0_NOP
DECL|macro|DM0_READ
mdefine_line|#define DM0_READ&t;&t;NPORT_DMODE0_RD
DECL|macro|DM0_DRAW
mdefine_line|#define DM0_DRAW&t;&t;NPORT_DMODE0_DRAW
DECL|macro|DM0_SCR2SCR
mdefine_line|#define DM0_SCR2SCR&t;&t;NPORT_DMODE0_S2S
DECL|macro|DM0_ADRMODE_SHIFT
mdefine_line|#define DM0_ADRMODE_SHIFT&t;2
DECL|macro|DM0_ADRMODE
mdefine_line|#define DM0_ADRMODE&t;&t;NPORT_DMODE0_AMMASK
DECL|macro|DM0_SPAN
mdefine_line|#define DM0_SPAN&t;&t;NPORT_DMODE0_SPAN
DECL|macro|DM0_BLOCK
mdefine_line|#define DM0_BLOCK&t;&t;NPORT_DMODE0_BLOCK
DECL|macro|DM0_ILINE
mdefine_line|#define DM0_ILINE&t;&t;NPORT_DMODE0_ILINE
DECL|macro|DM0_FLINE
mdefine_line|#define DM0_FLINE&t;&t;NPORT_DMODE0_FLINE
DECL|macro|DM0_ALINE
mdefine_line|#define DM0_ALINE&t;&t;NPORT_DMODE0_ALINE
DECL|macro|DM0_TLINE
mdefine_line|#define DM0_TLINE&t;&t;NPORT_DMODE0_TLINE
DECL|macro|DM0_BLINE
mdefine_line|#define DM0_BLINE               NPORT_DMODE0_BLINE
DECL|macro|DM0_DOSETUP
mdefine_line|#define DM0_DOSETUP&t;&t;NPORT_DMODE0_DOSETUP
DECL|macro|DM0_COLORHOST
mdefine_line|#define DM0_COLORHOST&t;&t;NPORT_DMODE0_CHOST
DECL|macro|DM0_ALPHAHOST
mdefine_line|#define DM0_ALPHAHOST&t;&t;NPORT_DMODE0_AHOST
DECL|macro|DM0_STOPONX
mdefine_line|#define DM0_STOPONX&t;&t;NPORT_DMODE0_STOPX
DECL|macro|DM0_STOPONY
mdefine_line|#define DM0_STOPONY&t;&t;NPORT_DMODE0_STOPY
DECL|macro|DM0_STOPONXY
mdefine_line|#define DM0_STOPONXY&t;&t;(NPORT_DMODE0_STOPX | NPORT_DMODE0_STOPY)
DECL|macro|DM0_SKIPFIRST
mdefine_line|#define DM0_SKIPFIRST&t;&t;NPORT_DMODE0_SK1ST
DECL|macro|DM0_SKIPLAST
mdefine_line|#define DM0_SKIPLAST&t;&t;NPORT_DMODE0_SKLST
DECL|macro|DM0_ENZPATTERN
mdefine_line|#define DM0_ENZPATTERN&t;&t;NPORT_DMODE0_ZPENAB
DECL|macro|DM0_ENLSPATTERN
mdefine_line|#define DM0_ENLSPATTERN&t;&t;NPORT_DMODE0_LISPENAB
DECL|macro|DM0_LSADVLAST
mdefine_line|#define DM0_LSADVLAST&t;&t;NPORT_DMODE0_LISLST
DECL|macro|DM0_LENGTH32
mdefine_line|#define DM0_LENGTH32&t;&t;NPORT_DMODE0_L32
DECL|macro|DM0_ZOPAQUE
mdefine_line|#define DM0_ZOPAQUE&t;&t;NPORT_DMODE0_ZOPQ
DECL|macro|DM0_LSOPAQUE
mdefine_line|#define DM0_LSOPAQUE&t;&t;NPORT_DMODE0_LISOPQ
DECL|macro|DM0_SHADE
mdefine_line|#define DM0_SHADE&t;&t;NPORT_DMODE0_SHADE
DECL|macro|DM0_LRONLY
mdefine_line|#define DM0_LRONLY&t;&t;NPORT_DMODE0_LRONLY
DECL|macro|DM0_XYOFFSET
mdefine_line|#define DM0_XYOFFSET&t;&t;NPORT_DMODE0_XYOFF
DECL|macro|DM0_CICLAMP
mdefine_line|#define DM0_CICLAMP&t;&t;NPORT_DMODE0_CLAMP
DECL|macro|DM0_ENDPTFILTER
mdefine_line|#define DM0_ENDPTFILTER&t;&t;NPORT_DMODE0_ENDPF
DECL|macro|DM0_YSTRIDE
mdefine_line|#define&t;DM0_YSTRIDE&t;&t;NPORT_DMODE0_YSTR 
DECL|macro|DM1_PLANES_SHIFT
mdefine_line|#define DM1_PLANES_SHIFT&t;0
multiline_comment|/* The rest of the DM1 planes defines are in newport.h */
DECL|macro|DM1_DRAWDEPTH_SHIFT
mdefine_line|#define DM1_DRAWDEPTH_SHIFT&t;3
DECL|macro|DM1_DRAWDEPTH_MASK
mdefine_line|#define DM1_DRAWDEPTH_MASK&t;NPORT_DMODE1_DDMASK
DECL|macro|DM1_DRAWDEPTH
mdefine_line|#define DM1_DRAWDEPTH&t;&t;NPORT_DMODE1_DD24 /* An alias? */
DECL|macro|DM1_DRAWDEPTH4
mdefine_line|#define DM1_DRAWDEPTH4&t;&t;NPORT_DMODE1_DD4
DECL|macro|DM1_DRAWDEPTH8
mdefine_line|#define DM1_DRAWDEPTH8&t;&t;NPORT_DMODE1_DD8
DECL|macro|DM1_DRAWDEPTH12
mdefine_line|#define DM1_DRAWDEPTH12&t;&t;NPORT_DMODE1_DD12
DECL|macro|DM1_DRAWDEPTH24
mdefine_line|#define DM1_DRAWDEPTH24&t;&t;NPORT_DMODE1_DD24
DECL|macro|DM1_DBLSRC
mdefine_line|#define DM1_DBLSRC&t;&t;NPORT_DMODE1_DSRC
DECL|macro|DM1_YFLIP
mdefine_line|#define DM1_YFLIP&t;&t;NPORT_DMODE1_YFLIP
DECL|macro|DM1_RWPACKED
mdefine_line|#define DM1_RWPACKED&t;&t;NPORT_DMODE1_RWPCKD
DECL|macro|DM1_HOSTDEPTH_SHIFT
mdefine_line|#define DM1_HOSTDEPTH_SHIFT &t;8
DECL|macro|DM1_HOSTDEPTH_MASK
mdefine_line|#define DM1_HOSTDEPTH_MASK&t;NPORT_DMODE1_HDMASK
DECL|macro|DM1_HOSTDEPTH
mdefine_line|#define DM1_HOSTDEPTH&t;&t;NPORT_DMODE1_HD32 /* An alias? */
DECL|macro|DM1_HOSTDEPTH4
mdefine_line|#define DM1_HOSTDEPTH4&t;&t;NPORT_DMODE1_HD4
DECL|macro|DM1_HOSTDEPTH8
mdefine_line|#define DM1_HOSTDEPTH8&t;&t;NPORT_DMODE1_HD8
DECL|macro|DM1_HOSTDEPTH12
mdefine_line|#define DM1_HOSTDEPTH12&t;&t;NPORT_DMODE1_HD12
DECL|macro|DM1_HOSTDEPTH32
mdefine_line|#define DM1_HOSTDEPTH32&t;&t;NPORT_DMODE1_HD32
DECL|macro|DM1_RWDOUBLE
mdefine_line|#define DM1_RWDOUBLE&t;&t;NPORT_DMODE1_RWDBL
DECL|macro|DM1_SWAPENDIAN
mdefine_line|#define DM1_SWAPENDIAN&t;&t;NPORT_DMODE1_ESWAP
DECL|macro|DM1_COLORCOMPARE_SHIFT
mdefine_line|#define DM1_COLORCOMPARE_SHIFT&t;12
DECL|macro|DM1_COLORCOMPARE_MASK
mdefine_line|#define DM1_COLORCOMPARE_MASK&t;NPORT_DMODE1_CCMASK
DECL|macro|DM1_COLORCOMPARE
mdefine_line|#define DM1_COLORCOMPARE&t;NPORT_DMODE1_CCMASK
DECL|macro|DM1_COLORCOMPLT
mdefine_line|#define DM1_COLORCOMPLT&t;&t;NPORT_DMODE1_CCLT
DECL|macro|DM1_COLORCOMPEQ
mdefine_line|#define DM1_COLORCOMPEQ&t;&t;NPORT_DMODE1_CCEQ
DECL|macro|DM1_COLORCOMPGT
mdefine_line|#define DM1_COLORCOMPGT&t;&t;NPORT_DMODE1_CCGT
DECL|macro|DM1_RGBMODE
mdefine_line|#define DM1_RGBMODE&t;&t;NPORT_DMODE1_RGBMD
DECL|macro|DM1_ENDITHER
mdefine_line|#define DM1_ENDITHER&t;&t;NPORT_DMODE1_DENAB
DECL|macro|DM1_FASTCLEAR
mdefine_line|#define DM1_FASTCLEAR&t;&t;NPORT_DMODE1_FCLR
DECL|macro|DM1_ENBLEND
mdefine_line|#define DM1_ENBLEND&t;&t;NPORT_DMODE1_BENAB
DECL|macro|DM1_SF_SHIFT
mdefine_line|#define DM1_SF_SHIFT&t;&t;19
DECL|macro|DM1_SF_MASK
mdefine_line|#define DM1_SF_MASK   &t;&t;NPORT_DMODE1_SFMASK
DECL|macro|DM1_SF
mdefine_line|#define DM1_SF&t;&t;&t;NPORT_DMODE1_SFMASK 
DECL|macro|DM1_SF_ZERO
mdefine_line|#define DM1_SF_ZERO&t;&t;NPORT_DMODE1_SF0
DECL|macro|DM1_SF_ONE
mdefine_line|#define DM1_SF_ONE&t;&t;NPORT_DMODE1_SF1
DECL|macro|DM1_SF_DC
mdefine_line|#define DM1_SF_DC&t;&t;NPORT_DMODE1_SFDC
DECL|macro|DM1_SF_MDC
mdefine_line|#define DM1_SF_MDC&t;&t;NPORT_DMODE1_SFMDC
DECL|macro|DM1_SF_SA
mdefine_line|#define DM1_SF_SA&t;&t;NPORT_DMODE1_SFSA
DECL|macro|DM1_SF_MSA
mdefine_line|#define DM1_SF_MSA&t;&t;NPORT_DMODE1_SFMSA
DECL|macro|DM1_DF_SHIFT
mdefine_line|#define DM1_DF_SHIFT&t;&t;22&t;/* dfactor(2:0)&t;*/
DECL|macro|DM1_DF_MASK
mdefine_line|#define DM1_DF_MASK&t;&t;NPORT_DMODE1_DFMASK 
DECL|macro|DM1_DF
mdefine_line|#define DM1_DF&t;&t;&t;NPORT_DMODE1_DFMASK 
DECL|macro|DM1_DF_ZERO
mdefine_line|#define DM1_DF_ZERO&t;&t;NPORT_DMODE1_DF0
DECL|macro|DM1_DF_ONE
mdefine_line|#define DM1_DF_ONE&t;&t;NPORT_DMODE1_DF1
DECL|macro|DM1_DF_SC
mdefine_line|#define DM1_DF_SC&t;&t;NPORT_DMODE1_DFSC
DECL|macro|DM1_DF_MSC
mdefine_line|#define DM1_DF_MSC&t;&t;NPORT_DMODE1_DFMSC
DECL|macro|DM1_DF_SA
mdefine_line|#define DM1_DF_SA&t;&t;NPORT_DMODE1_DFSA
DECL|macro|DM1_DF_MSA
mdefine_line|#define DM1_DF_MSA&t;&t;NPORT_DMODE1_DFMSA
DECL|macro|DM1_ENBACKBLEND
mdefine_line|#define DM1_ENBACKBLEND&t;&t;NPORT_DMODE1_BBENAB
DECL|macro|DM1_ENPREFETCH
mdefine_line|#define DM1_ENPREFETCH&t;&t;NPORT_DMODE1_PFENAB
DECL|macro|DM1_BLENDALPHA
mdefine_line|#define DM1_BLENDALPHA&t;&t;NPORT_DMODE1_ABLEND
DECL|macro|DM1_LO_SHIFT
mdefine_line|#define DM1_LO_SHIFT&t;&t;28
DECL|macro|DM1_LO
mdefine_line|#define DM1_LO&t;&t;&t;NPORT_DMODE1_LOMASK
DECL|macro|DM1_LO_MASK
mdefine_line|#define DM1_LO_MASK      &t;NPORT_DMODE1_LOMASK
DECL|macro|DM1_LO_ZERO
mdefine_line|#define DM1_LO_ZERO&t;&t;NPORT_DMODE1_LOZERO
DECL|macro|DM1_LO_AND
mdefine_line|#define DM1_LO_AND&t;&t;NPORT_DMODE1_LOAND
DECL|macro|DM1_LO_ANDR
mdefine_line|#define DM1_LO_ANDR&t;&t;NPORT_DMODE1_LOANDR
DECL|macro|DM1_LO_SRC
mdefine_line|#define DM1_LO_SRC&t;&t;NPORT_DMODE1_LOSRC
DECL|macro|DM1_LO_ANDI
mdefine_line|#define DM1_LO_ANDI&t;&t;NPORT_DMODE1_LOANDI
DECL|macro|DM1_LO_DST
mdefine_line|#define DM1_LO_DST&t;&t;NPORT_DMODE1_LODST
DECL|macro|DM1_LO_XOR
mdefine_line|#define DM1_LO_XOR&t;&t;NPORT_DMODE1_LOXOR
DECL|macro|DM1_LO_OR
mdefine_line|#define DM1_LO_OR&t;&t;NPORT_DMODE1_LOOR
DECL|macro|DM1_LO_NOR
mdefine_line|#define DM1_LO_NOR&t;&t;NPORT_DMODE1_LONOR
DECL|macro|DM1_LO_XNOR
mdefine_line|#define DM1_LO_XNOR&t;&t;NPORT_DMODE1_LOXNOR
DECL|macro|DM1_LO_NDST
mdefine_line|#define DM1_LO_NDST&t;&t;NPORT_DMODE1_LONDST
DECL|macro|DM1_LO_ORR
mdefine_line|#define DM1_LO_ORR&t;&t;NPORT_DMODE1_LOORR
DECL|macro|DM1_LO_NSRC
mdefine_line|#define DM1_LO_NSRC&t;&t;NPORT_DMODE1_LONSRC
DECL|macro|DM1_LO_ORI
mdefine_line|#define DM1_LO_ORI&t;&t;NPORT_DMODE1_LOORI
DECL|macro|DM1_LO_NAND
mdefine_line|#define DM1_LO_NAND&t;&t;NPORT_DMODE1_LONAND
DECL|macro|DM1_LO_ONE
mdefine_line|#define DM1_LO_ONE&t;&t;NPORT_DMODE1_LOONE
DECL|macro|SMASK0
mdefine_line|#define SMASK0&t;&t;&t;NPORT_CMODE_SM0
DECL|macro|SMASK1
mdefine_line|#define SMASK1&t;&t;&t;NPORT_CMODE_SM1
DECL|macro|SMASK2
mdefine_line|#define SMASK2&t;&t;&t;NPORT_CMODE_SM2
DECL|macro|SMASK3
mdefine_line|#define SMASK3&t;&t;&t;NPORT_CMODE_SM3
DECL|macro|SMASK4
mdefine_line|#define SMASK4&t;&t;&t;NPORT_CMODE_SM4
DECL|macro|ALL_SMASKS
mdefine_line|#define ALL_SMASKS&t;&t;0x1f
DECL|macro|CM_CIDMATCH_SHIFT
mdefine_line|#define CM_CIDMATCH_SHIFT       9
DECL|macro|CM_CIDMATCH_MASK
mdefine_line|#define CM_CIDMATCH_MASK        NPORT_CMODE_CMSK
DECL|macro|REX3VERSION_MASK
mdefine_line|#define REX3VERSION_MASK&t;NPORT_STAT_VERS
DECL|macro|GFXBUSY
mdefine_line|#define GFXBUSY        &t;&t;NPORT_STAT_GBUSY
DECL|macro|BACKBUSY
mdefine_line|#define BACKBUSY        &t;NPORT_STAT_BBUSY
DECL|macro|VRINT
mdefine_line|#define VRINT           &t;NPORT_STAT_VRINT
DECL|macro|VIDEOINT
mdefine_line|#define VIDEOINT        &t;NPORT_STAT_VIDINT
DECL|macro|GFIFO_LEVEL_SHIFT
mdefine_line|#define GFIFO_LEVEL_SHIFT       7
DECL|macro|GFIFO_LEVEL_MASK
mdefine_line|#define GFIFO_LEVEL_MASK        NPORT_STAT_GLMSK 
DECL|macro|BFIFO_LEVEL_SHIFT
mdefine_line|#define BFIFO_LEVEL_SHIFT       13
DECL|macro|BFIFO_LEVEL_MASK
mdefine_line|#define BFIFO_LEVEL_MASK        NPORT_STAT_BLMSK 
DECL|macro|BFIFO_INT
mdefine_line|#define BFIFO_INT        &t;NPORT_STAT_BFIRQ
DECL|macro|GFIFO_INT
mdefine_line|#define GFIFO_INT        &t;NPORT_STAT_GFIRQ
DECL|macro|GIO32MODE
mdefine_line|#define GIO32MODE&t;&t;NPORT_CFG_G32MD 
DECL|macro|BUSWIDTH
mdefine_line|#define BUSWIDTH&t;&t;NPORT_CFG_BWIDTH
DECL|macro|EXTREGXCVR
mdefine_line|#define EXTREGXCVR&t;&t;NPORT_CFG_ERCVR 
DECL|macro|BFIFODEPTH_SHIFT
mdefine_line|#define BFIFODEPTH_SHIFT&t;3
DECL|macro|BFIFODEPTH_MASK
mdefine_line|#define BFIFODEPTH_MASK&t;&t;NPORT_CFG_BDMSK
DECL|macro|BFIFOABOVEINT
mdefine_line|#define BFIFOABOVEINT&t;&t;NPORT_CFG_BFAINT
DECL|macro|GFIFODEPTH_SHIFT
mdefine_line|#define GFIFODEPTH_SHIFT        8
DECL|macro|GFIFODEPTH_MASK
mdefine_line|#define GFIFODEPTH_MASK&t;&t;NPORT_CFG_GDMSK 
DECL|macro|GFIFOABOVEINT
mdefine_line|#define GFIFOABOVEINT&t;&t;NPORT_CFG_GFAINT
DECL|macro|TIMEOUT_SHIFT
mdefine_line|#define TIMEOUT_SHIFT&t;&t;14
DECL|macro|TIMEOUT_MASK
mdefine_line|#define TIMEOUT_MASK&t;&t;NPORT_CFG_TOMSK 
DECL|macro|VREFRESH_SHIFT
mdefine_line|#define VREFRESH_SHIFT&t;&t;17
DECL|macro|VREFRESH_MASK
mdefine_line|#define VREFRESH_MASK&t;&t;NPORT_CFG_VRMSK
DECL|macro|FB_TYPE
mdefine_line|#define FB_TYPE&t;&t;&t;NPORT_CFG_FBTYP
DECL|macro|DCB_DATAWIDTH_MASK
mdefine_line|#define DCB_DATAWIDTH_MASK&t;(0x3)
DECL|macro|DCB_CRS_MASK
mdefine_line|#define DCB_CRS_MASK&t;&t;(0x7 &lt;&lt; DCB_CRS_SHIFT)
DECL|macro|DCB_ADDR_MASK
mdefine_line|#define DCB_ADDR_MASK&t;&t;(0xf &lt;&lt; DCB_ADDR_SHIFT)
DECL|macro|DCB_CSWIDTH_MASK
mdefine_line|#define DCB_CSWIDTH_MASK&t;(0x1f &lt;&lt; DCB_CSWIDTH_SHIFT)
DECL|macro|DCB_CSHOLD_MASK
mdefine_line|#define DCB_CSHOLD_MASK&t;&t;(0x1f &lt;&lt; DCB_CSHOLD_SHIFT)
DECL|macro|DCB_CSSETUP_MASK
mdefine_line|#define DCB_CSSETUP_MASK&t;(0x1f &lt;&lt; DCB_CSSETUP_SHIFT)
DECL|macro|DCB_SWAPENDIAN
mdefine_line|#define DCB_SWAPENDIAN&t;&t;(1 &lt;&lt; 28)
DECL|macro|REX3WAIT
mdefine_line|#define REX3WAIT(rex3)  while ((rex3)-&gt;p1.set.status &amp; GFXBUSY)
DECL|macro|BFIFOWAIT
mdefine_line|#define BFIFOWAIT(rex3)  while ((rex3)-&gt;p1.set.status &amp; BACKBUSY)
DECL|macro|REX3_GIO_ADDR_0
mdefine_line|#define REX3_GIO_ADDR_0         0x1f0f0000
DECL|macro|REX3_GIO_ADDR_1
mdefine_line|#define REX3_GIO_ADDR_1         0x1f4f0000
DECL|macro|REX3_GIO_ADDR_2
mdefine_line|#define REX3_GIO_ADDR_2         0x1f8f0000
DECL|macro|REX3_GIO_ADDR_3
mdefine_line|#define REX3_GIO_ADDR_3         0x1fcf0000
DECL|macro|NG1_XSIZE
mdefine_line|#define NG1_XSIZE&t;&t;1280
DECL|macro|NG1_YSIZE
mdefine_line|#define NG1_YSIZE&t;&t;1024
macro_line|#endif
eof
