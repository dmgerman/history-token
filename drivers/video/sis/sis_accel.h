multiline_comment|/*&n; * SiS 300/630/730/540/315/550/650/740 frame buffer driver&n; * for Linux kernels 2.4.x and 2.5.x&n; *&n; * 2D acceleration part&n; *&n; * Based on the X driver&squot;s sis300_accel.h which is&n; *     Copyright Xavier Ducoin &lt;x.ducoin@lectra.com&gt;&n; *     Copyright 2002 by Thomas Winischhofer, Vienna, Austria&n; * and sis310_accel.h which is&n; *     Copyright 2002 by Thomas Winischhofer, Vienna, Austria&n; *&n; * Author:   Thomas Winischhofer &lt;thomas@winischhofer.net&gt;:&n; *&t;&t;&t;(see http://www.winischhofer.net/&n; *&t;&t;&t;for more information and updates)&n; */
macro_line|#ifndef _SISFB_ACCEL_H
DECL|macro|_SISFB_ACCEL_H
mdefine_line|#define _SISFB_ACCEL_H
multiline_comment|/* Guard accelerator accesses with spin_lock_irqsave? Works well without. */
DECL|macro|SISFB_USE_SPINLOCKS
macro_line|#undef SISFB_USE_SPINLOCKS
macro_line|#ifdef SISFB_USE_SPINLOCKS
macro_line|#include &lt;linux/spinlock.h&gt;
DECL|macro|CRITBEGIN
mdefine_line|#define CRITBEGIN  spin_lock_irqsave(&amp;ivideo.lockaccel), critflags);
DECL|macro|CRITEND
mdefine_line|#define CRITEND&t;   spin_unlock_irqrestore(&amp;ivideo.lockaccel), critflags);
DECL|macro|CRITFLAGS
mdefine_line|#define CRITFLAGS  unsigned long critflags;
macro_line|#else
DECL|macro|CRITBEGIN
mdefine_line|#define CRITBEGIN
DECL|macro|CRITEND
mdefine_line|#define CRITEND
DECL|macro|CRITFLAGS
mdefine_line|#define CRITFLAGS
macro_line|#endif
multiline_comment|/* Definitions for the SIS engine communication. */
DECL|macro|PATREGSIZE
mdefine_line|#define PATREGSIZE      384  /* Pattern register size. 384 bytes @ 0x8300 */
DECL|macro|BR
mdefine_line|#define BR(x)   (0x8200 | (x) &lt;&lt; 2)
DECL|macro|PBR
mdefine_line|#define PBR(x)  (0x8300 | (x) &lt;&lt; 2)
multiline_comment|/* SiS300 engine commands */
DECL|macro|BITBLT
mdefine_line|#define BITBLT                  0x00000000  /* Blit */
DECL|macro|COLOREXP
mdefine_line|#define COLOREXP                0x00000001  /* Color expand */
DECL|macro|ENCOLOREXP
mdefine_line|#define ENCOLOREXP              0x00000002  /* Enhanced color expand */
DECL|macro|MULTIPLE_SCANLINE
mdefine_line|#define MULTIPLE_SCANLINE       0x00000003  /* ? */
DECL|macro|LINE
mdefine_line|#define LINE                    0x00000004  /* Draw line */
DECL|macro|TRAPAZOID_FILL
mdefine_line|#define TRAPAZOID_FILL          0x00000005  /* Fill trapezoid */
DECL|macro|TRANSPARENT_BITBLT
mdefine_line|#define TRANSPARENT_BITBLT      0x00000006  /* Transparent Blit */
multiline_comment|/* Additional engine commands for 310/325 */
DECL|macro|ALPHA_BLEND
mdefine_line|#define ALPHA_BLEND&t;&t;0x00000007  /* Alpha blend ? */
DECL|macro|A3D_FUNCTION
mdefine_line|#define A3D_FUNCTION&t;&t;0x00000008  /* 3D command ? */
DECL|macro|CLEAR_Z_BUFFER
mdefine_line|#define&t;CLEAR_Z_BUFFER&t;&t;0x00000009  /* ? */
DECL|macro|GRADIENT_FILL
mdefine_line|#define GRADIENT_FILL&t;&t;0x0000000A  /* Gradient fill */
DECL|macro|STRETCH_BITBLT
mdefine_line|#define STRETCH_BITBLT&t;&t;0x0000000B  /* Stretched Blit */
multiline_comment|/* source select */
DECL|macro|SRCVIDEO
mdefine_line|#define SRCVIDEO                0x00000000  /* source is video RAM */
DECL|macro|SRCSYSTEM
mdefine_line|#define SRCSYSTEM               0x00000010  /* source is system memory */
DECL|macro|SRCCPUBLITBUF
mdefine_line|#define SRCCPUBLITBUF           SRCSYSTEM   /* source is CPU-driven BitBuffer (for color expand) */
DECL|macro|SRCAGP
mdefine_line|#define SRCAGP                  0x00000020  /* source is AGP memory (?) */
multiline_comment|/* Pattern flags */
DECL|macro|PATFG
mdefine_line|#define PATFG                   0x00000000  /* foreground color */
DECL|macro|PATPATREG
mdefine_line|#define PATPATREG               0x00000040  /* pattern in pattern buffer (0x8300) */
DECL|macro|PATMONO
mdefine_line|#define PATMONO                 0x00000080  /* mono pattern */
multiline_comment|/* blitting direction (300 series only) */
DECL|macro|X_INC
mdefine_line|#define X_INC                   0x00010000
DECL|macro|X_DEC
mdefine_line|#define X_DEC                   0x00000000
DECL|macro|Y_INC
mdefine_line|#define Y_INC                   0x00020000
DECL|macro|Y_DEC
mdefine_line|#define Y_DEC                   0x00000000
multiline_comment|/* Clipping flags */
DECL|macro|NOCLIP
mdefine_line|#define NOCLIP                  0x00000000
DECL|macro|NOMERGECLIP
mdefine_line|#define NOMERGECLIP             0x04000000
DECL|macro|CLIPENABLE
mdefine_line|#define CLIPENABLE              0x00040000
DECL|macro|CLIPWITHOUTMERGE
mdefine_line|#define CLIPWITHOUTMERGE        0x04040000
multiline_comment|/* Transparency */
DECL|macro|OPAQUE
mdefine_line|#define OPAQUE                  0x00000000
DECL|macro|TRANSPARENT
mdefine_line|#define TRANSPARENT             0x00100000
multiline_comment|/* ? */
DECL|macro|DSTAGP
mdefine_line|#define DSTAGP                  0x02000000
DECL|macro|DSTVIDEO
mdefine_line|#define DSTVIDEO                0x02000000
multiline_comment|/* Line */
DECL|macro|LINE_STYLE
mdefine_line|#define LINE_STYLE              0x00800000
DECL|macro|NO_RESET_COUNTER
mdefine_line|#define NO_RESET_COUNTER        0x00400000
DECL|macro|NO_LAST_PIXEL
mdefine_line|#define NO_LAST_PIXEL           0x00200000
multiline_comment|/* Subfunctions for Color/Enhanced Color Expansion (310/325 only) */
DECL|macro|COLOR_TO_MONO
mdefine_line|#define COLOR_TO_MONO&t;&t;0x00100000
DECL|macro|AA_TEXT
mdefine_line|#define AA_TEXT&t;&t;&t;0x00200000
multiline_comment|/* Some general registers for 310/325 series */
DECL|macro|SRC_ADDR
mdefine_line|#define SRC_ADDR&t;&t;0x8200
DECL|macro|SRC_PITCH
mdefine_line|#define SRC_PITCH&t;&t;0x8204
DECL|macro|AGP_BASE
mdefine_line|#define AGP_BASE&t;&t;0x8206 /* color-depth dependent value */
DECL|macro|SRC_Y
mdefine_line|#define SRC_Y&t;&t;&t;0x8208
DECL|macro|SRC_X
mdefine_line|#define SRC_X&t;&t;&t;0x820A
DECL|macro|DST_Y
mdefine_line|#define DST_Y&t;&t;&t;0x820C
DECL|macro|DST_X
mdefine_line|#define DST_X&t;&t;&t;0x820E
DECL|macro|DST_ADDR
mdefine_line|#define DST_ADDR&t;&t;0x8210
DECL|macro|DST_PITCH
mdefine_line|#define DST_PITCH&t;&t;0x8214
DECL|macro|DST_HEIGHT
mdefine_line|#define DST_HEIGHT&t;&t;0x8216
DECL|macro|RECT_WIDTH
mdefine_line|#define RECT_WIDTH&t;&t;0x8218
DECL|macro|RECT_HEIGHT
mdefine_line|#define RECT_HEIGHT&t;&t;0x821A
DECL|macro|PAT_FGCOLOR
mdefine_line|#define PAT_FGCOLOR&t;&t;0x821C
DECL|macro|PAT_BGCOLOR
mdefine_line|#define PAT_BGCOLOR&t;&t;0x8220
DECL|macro|SRC_FGCOLOR
mdefine_line|#define SRC_FGCOLOR&t;&t;0x8224
DECL|macro|SRC_BGCOLOR
mdefine_line|#define SRC_BGCOLOR&t;&t;0x8228
DECL|macro|MONO_MASK
mdefine_line|#define MONO_MASK&t;&t;0x822C
DECL|macro|LEFT_CLIP
mdefine_line|#define LEFT_CLIP&t;&t;0x8234
DECL|macro|TOP_CLIP
mdefine_line|#define TOP_CLIP&t;&t;0x8236
DECL|macro|RIGHT_CLIP
mdefine_line|#define RIGHT_CLIP&t;&t;0x8238
DECL|macro|BOTTOM_CLIP
mdefine_line|#define BOTTOM_CLIP&t;&t;0x823A
DECL|macro|COMMAND_READY
mdefine_line|#define COMMAND_READY&t;&t;0x823C
DECL|macro|FIRE_TRIGGER
mdefine_line|#define FIRE_TRIGGER      &t;0x8240
DECL|macro|PATTERN_REG
mdefine_line|#define PATTERN_REG&t;&t;0x8300  /* 384 bytes pattern buffer */
multiline_comment|/* Line registers */
DECL|macro|LINE_X0
mdefine_line|#define LINE_X0&t;&t;&t;SRC_Y
DECL|macro|LINE_X1
mdefine_line|#define LINE_X1&t;&t;&t;DST_Y
DECL|macro|LINE_Y0
mdefine_line|#define LINE_Y0&t;&t;&t;SRC_X
DECL|macro|LINE_Y1
mdefine_line|#define LINE_Y1&t;&t;&t;DST_X
DECL|macro|LINE_COUNT
mdefine_line|#define LINE_COUNT&t;&t;RECT_WIDTH
DECL|macro|LINE_STYLE_PERIOD
mdefine_line|#define LINE_STYLE_PERIOD&t;RECT_HEIGHT
DECL|macro|LINE_STYLE_0
mdefine_line|#define LINE_STYLE_0&t;&t;MONO_MASK
DECL|macro|LINE_STYLE_1
mdefine_line|#define LINE_STYLE_1&t;&t;0x8230
DECL|macro|LINE_XN
mdefine_line|#define LINE_XN&t;&t;&t;PATTERN_REG
DECL|macro|LINE_YN
mdefine_line|#define LINE_YN&t;&t;&t;PATTERN_REG+2
multiline_comment|/* Transparent bitblit registers */
DECL|macro|TRANS_DST_KEY_HIGH
mdefine_line|#define TRANS_DST_KEY_HIGH&t;PAT_FGCOLOR
DECL|macro|TRANS_DST_KEY_LOW
mdefine_line|#define TRANS_DST_KEY_LOW&t;PAT_BGCOLOR
DECL|macro|TRANS_SRC_KEY_HIGH
mdefine_line|#define TRANS_SRC_KEY_HIGH&t;SRC_FGCOLOR
DECL|macro|TRANS_SRC_KEY_LOW
mdefine_line|#define TRANS_SRC_KEY_LOW&t;SRC_BGCOLOR
multiline_comment|/* Queue */
DECL|macro|Q_BASE_ADDR
mdefine_line|#define Q_BASE_ADDR&t;&t;0x85C0  /* Base address of software queue (?) */
DECL|macro|Q_WRITE_PTR
mdefine_line|#define Q_WRITE_PTR&t;&t;0x85C4  /* Current write pointer (?) */
DECL|macro|Q_READ_PTR
mdefine_line|#define Q_READ_PTR&t;&t;0x85C8  /* Current read pointer (?) */
DECL|macro|Q_STATUS
mdefine_line|#define Q_STATUS&t;&t;0x85CC  /* queue status */
DECL|macro|MMIO_IN8
mdefine_line|#define MMIO_IN8(base, offset) &bslash;&n;&t;*(volatile u8 *)(((u8*)(base)) + (offset))
DECL|macro|MMIO_IN16
mdefine_line|#define MMIO_IN16(base, offset) &bslash;&n;&t;*(volatile u16 *)(void *)(((u8*)(base)) + (offset))
DECL|macro|MMIO_IN32
mdefine_line|#define MMIO_IN32(base, offset) &bslash;&n;&t;*(volatile u32 *)(void *)(((u8*)(base)) + (offset))
DECL|macro|MMIO_OUT8
mdefine_line|#define MMIO_OUT8(base, offset, val) &bslash;&n;&t;*(volatile u8 *)(((u8*)(base)) + (offset)) = (val)
DECL|macro|MMIO_OUT16
mdefine_line|#define MMIO_OUT16(base, offset, val) &bslash;&n;&t;*(volatile u16 *)(void *)(((u8*)(base)) + (offset)) = (val)
DECL|macro|MMIO_OUT32
mdefine_line|#define MMIO_OUT32(base, offset, val) &bslash;&n;&t;*(volatile u32 *)(void *)(((u8*)(base)) + (offset)) = (val)
multiline_comment|/* ------------- SiS 300 series -------------- */
multiline_comment|/* Macros to do useful things with the SIS BitBLT engine */
multiline_comment|/* BR(16) (0x8420):&n;&n;   bit 31 2D engine: 1 is idle,&n;   bit 30 3D engine: 1 is idle,&n;   bit 29 Command queue: 1 is empty&n;&n;   bits 28:24: Current CPU driven BitBlt buffer stage bit[4:0]&n;&n;   bits 15:0:  Current command queue length&n;&n;*/
multiline_comment|/* TW: BR(16)+2 = 0x8242 */
DECL|variable|CmdQueLen
r_int
id|CmdQueLen
suffix:semicolon
DECL|macro|SiS300Idle
mdefine_line|#define SiS300Idle &bslash;&n;  { &bslash;&n;  while( (MMIO_IN16(ivideo.mmio_vbase, BR(16)+2) &amp; 0xE000) != 0xE000){}; &bslash;&n;  while( (MMIO_IN16(ivideo.mmio_vbase, BR(16)+2) &amp; 0xE000) != 0xE000){}; &bslash;&n;  while( (MMIO_IN16(ivideo.mmio_vbase, BR(16)+2) &amp; 0xE000) != 0xE000){}; &bslash;&n;  CmdQueLen=MMIO_IN16(ivideo.mmio_vbase, 0x8240); &bslash;&n;  }
multiline_comment|/* TW: (do three times, because 2D engine seems quite unsure about whether or not it&squot;s idle) */
DECL|macro|SiS300SetupSRCBase
mdefine_line|#define SiS300SetupSRCBase(base) &bslash;&n;                if (CmdQueLen &lt;= 0)  SiS300Idle;&bslash;&n;                MMIO_OUT32(ivideo.mmio_vbase, BR(0), base);&bslash;&n;                CmdQueLen --;
DECL|macro|SiS300SetupSRCPitch
mdefine_line|#define SiS300SetupSRCPitch(pitch) &bslash;&n;                if (CmdQueLen &lt;= 0)  SiS300Idle;&bslash;&n;                MMIO_OUT16(ivideo.mmio_vbase, BR(1), pitch);&bslash;&n;                CmdQueLen --;
DECL|macro|SiS300SetupSRCXY
mdefine_line|#define SiS300SetupSRCXY(x,y) &bslash;&n;                if (CmdQueLen &lt;= 0)  SiS300Idle;&bslash;&n;                MMIO_OUT32(ivideo.mmio_vbase, BR(2), (x)&lt;&lt;16 | (y) );&bslash;&n;                CmdQueLen --;
DECL|macro|SiS300SetupDSTBase
mdefine_line|#define SiS300SetupDSTBase(base) &bslash;&n;                if (CmdQueLen &lt;= 0)  SiS300Idle;&bslash;&n;                MMIO_OUT32(ivideo.mmio_vbase, BR(4), base);&bslash;&n;                CmdQueLen --;
DECL|macro|SiS300SetupDSTXY
mdefine_line|#define SiS300SetupDSTXY(x,y) &bslash;&n;                if (CmdQueLen &lt;= 0)  SiS300Idle;&bslash;&n;                MMIO_OUT32(ivideo.mmio_vbase, BR(3), (x)&lt;&lt;16 | (y) );&bslash;&n;                CmdQueLen --;
DECL|macro|SiS300SetupDSTRect
mdefine_line|#define SiS300SetupDSTRect(x,y) &bslash;&n;                if (CmdQueLen &lt;= 0)  SiS300Idle;&bslash;&n;                MMIO_OUT32(ivideo.mmio_vbase, BR(5), (y)&lt;&lt;16 | (x) );&bslash;&n;                CmdQueLen --;
DECL|macro|SiS300SetupDSTColorDepth
mdefine_line|#define SiS300SetupDSTColorDepth(bpp) &bslash;&n;                if (CmdQueLen &lt;= 0)  SiS300Idle;&bslash;&n;                MMIO_OUT16(ivideo.mmio_vbase, BR(1)+2, bpp);&bslash;&n;                CmdQueLen --;
DECL|macro|SiS300SetupRect
mdefine_line|#define SiS300SetupRect(w,h) &bslash;&n;                if (CmdQueLen &lt;= 0)  SiS300Idle;&bslash;&n;                MMIO_OUT32(ivideo.mmio_vbase, BR(6), (h)&lt;&lt;16 | (w) );&bslash;&n;                CmdQueLen --;
DECL|macro|SiS300SetupPATFG
mdefine_line|#define SiS300SetupPATFG(color) &bslash;&n;                if (CmdQueLen &lt;= 0)  SiS300Idle;&bslash;&n;                MMIO_OUT32(ivideo.mmio_vbase, BR(7), color);&bslash;&n;                CmdQueLen --;
DECL|macro|SiS300SetupPATBG
mdefine_line|#define SiS300SetupPATBG(color) &bslash;&n;                if (CmdQueLen &lt;= 0)  SiS300Idle;&bslash;&n;                MMIO_OUT32(ivideo.mmio_vbase, BR(8), color);&bslash;&n;                CmdQueLen --;
DECL|macro|SiS300SetupSRCFG
mdefine_line|#define SiS300SetupSRCFG(color) &bslash;&n;                if (CmdQueLen &lt;= 0)  SiS300Idle;&bslash;&n;                MMIO_OUT32(ivideo.mmio_vbase, BR(9), color);&bslash;&n;                CmdQueLen --;
DECL|macro|SiS300SetupSRCBG
mdefine_line|#define SiS300SetupSRCBG(color) &bslash;&n;                if (CmdQueLen &lt;= 0)  SiS300Idle;&bslash;&n;                MMIO_OUT32(ivideo.mmio_vbase, BR(10), color);&bslash;&n;                CmdQueLen --;
multiline_comment|/* 0x8224 src colorkey high */
multiline_comment|/* 0x8228 src colorkey low */
multiline_comment|/* 0x821c dest colorkey high */
multiline_comment|/* 0x8220 dest colorkey low */
DECL|macro|SiS300SetupSRCTrans
mdefine_line|#define SiS300SetupSRCTrans(color) &bslash;&n;                if (CmdQueLen &lt;= 1)  SiS300Idle;&bslash;&n;                MMIO_OUT32(ivideo.mmio_vbase, 0x8224, color);&bslash;&n;&t;&t;MMIO_OUT32(ivideo.mmio_vbase, 0x8228, color);&bslash;&n;&t;&t;CmdQueLen -= 2;
DECL|macro|SiS300SetupDSTTrans
mdefine_line|#define SiS300SetupDSTTrans(color) &bslash;&n;&t;&t;if (CmdQueLen &lt;= 1)  SiS300Idle;&bslash;&n;&t;&t;MMIO_OUT32(ivideo.mmio_vbase, 0x821C, color); &bslash;&n;&t;&t;MMIO_OUT32(ivideo.mmio_vbase, 0x8220, color); &bslash;&n;                CmdQueLen -= 2;
DECL|macro|SiS300SetupMONOPAT
mdefine_line|#define SiS300SetupMONOPAT(p0,p1) &bslash;&n;                if (CmdQueLen &lt;= 1)  SiS300Idle;&bslash;&n;                MMIO_OUT32(ivideo.mmio_vbase, BR(11), p0);&bslash;&n;                MMIO_OUT32(ivideo.mmio_vbase, BR(12), p1);&bslash;&n;                CmdQueLen -= 2;
DECL|macro|SiS300SetupClipLT
mdefine_line|#define SiS300SetupClipLT(left,top) &bslash;&n;                if (CmdQueLen &lt;= 0)  SiS300Idle;&bslash;&n;                MMIO_OUT32(ivideo.mmio_vbase, BR(13), ((left) &amp; 0xFFFF) | (top)&lt;&lt;16 );&bslash;&n;                CmdQueLen--;
DECL|macro|SiS300SetupClipRB
mdefine_line|#define SiS300SetupClipRB(right,bottom) &bslash;&n;                if (CmdQueLen &lt;= 0)  SiS300Idle;&bslash;&n;                MMIO_OUT32(ivideo.mmio_vbase, BR(14), ((right) &amp; 0xFFFF) | (bottom)&lt;&lt;16 );&bslash;&n;                CmdQueLen--;
multiline_comment|/* General */
DECL|macro|SiS300SetupROP
mdefine_line|#define SiS300SetupROP(rop) &bslash;&n;                ivideo.CommandReg = (rop) &lt;&lt; 8;
DECL|macro|SiS300SetupCMDFlag
mdefine_line|#define SiS300SetupCMDFlag(flags) &bslash;&n;                ivideo.CommandReg |= (flags);
DECL|macro|SiS300DoCMD
mdefine_line|#define SiS300DoCMD &bslash;&n;                if (CmdQueLen &lt;= 1)  SiS300Idle;&bslash;&n;                MMIO_OUT32(ivideo.mmio_vbase, BR(15), ivideo.CommandReg); &bslash;&n;                MMIO_OUT32(ivideo.mmio_vbase, BR(16), 0);&bslash;&n;                CmdQueLen -= 2;
multiline_comment|/* Line */
DECL|macro|SiS300SetupX0Y0
mdefine_line|#define SiS300SetupX0Y0(x,y) &bslash;&n;                if (CmdQueLen &lt;= 0)  SiS300Idle;&bslash;&n;                MMIO_OUT32(ivideo.mmio_vbase, BR(2), (y)&lt;&lt;16 | (x) );&bslash;&n;                CmdQueLen--;
DECL|macro|SiS300SetupX1Y1
mdefine_line|#define SiS300SetupX1Y1(x,y) &bslash;&n;                if (CmdQueLen &lt;= 0)  SiS300Idle;&bslash;&n;                MMIO_OUT32(ivideo.mmio_vbase, BR(3), (y)&lt;&lt;16 | (x) );&bslash;&n;                CmdQueLen--;
DECL|macro|SiS300SetupLineCount
mdefine_line|#define SiS300SetupLineCount(c) &bslash;&n;                if (CmdQueLen &lt;= 0)  SiS300Idle;&bslash;&n;                MMIO_OUT16(ivideo.mmio_vbase, BR(6), c);&bslash;&n;                CmdQueLen--;
DECL|macro|SiS300SetupStylePeriod
mdefine_line|#define SiS300SetupStylePeriod(p) &bslash;&n;                if (CmdQueLen &lt;= 0)  SiS300Idle;&bslash;&n;                MMIO_OUT16(ivideo.mmio_vbase, BR(6)+2, p);&bslash;&n;                CmdQueLen--;
DECL|macro|SiS300SetupStyleLow
mdefine_line|#define SiS300SetupStyleLow(ls) &bslash;&n;                if (CmdQueLen &lt;= 0)  SiS300Idle;&bslash;&n;                MMIO_OUT32(ivideo.mmio_vbase, BR(11), ls);&bslash;&n;                CmdQueLen--;
DECL|macro|SiS300SetupStyleHigh
mdefine_line|#define SiS300SetupStyleHigh(ls) &bslash;&n;                if (CmdQueLen &lt;= 0)  SiS300Idle;&bslash;&n;                MMIO_OUT32(ivideo.mmio_vbase, BR(12), ls);&bslash;&n;                CmdQueLen--;
multiline_comment|/* ----------- SiS 310/325 series --------------- */
multiline_comment|/* Q_STATUS:&n;   bit 31 = 1: All engines idle and all queues empty&n;   bit 30 = 1: Hardware Queue (=HW CQ, 2D queue, 3D queue) empty&n;   bit 29 = 1: 2D engine is idle&n;   bit 28 = 1: 3D engine is idle&n;   bit 27 = 1: HW command queue empty&n;   bit 26 = 1: 2D queue empty&n;   bit 25 = 1: 3D queue empty&n;   bit 24 = 1: SW command queue empty&n;   bits 23:16: 2D counter 3&n;   bits 15:8:  2D counter 2&n;   bits 7:0:   2D counter 1&n;&n;   Where is the command queue length (current amount of commands the queue&n;   can accept) on the 310/325 series? (The current implementation is taken&n;   from 300 series and certainly wrong...)&n;*/
multiline_comment|/* TW: FIXME: CmdQueLen is... where....? */
DECL|macro|SiS310Idle
mdefine_line|#define SiS310Idle &bslash;&n;  { &bslash;&n;  while( (MMIO_IN16(ivideo.mmio_vbase, Q_STATUS+2) &amp; 0x8000) != 0x8000){}; &bslash;&n;  while( (MMIO_IN16(ivideo.mmio_vbase, Q_STATUS+2) &amp; 0x8000) != 0x8000){}; &bslash;&n;  CmdQueLen=MMIO_IN16(ivideo.mmio_vbase, Q_STATUS); &bslash;&n;  }
DECL|macro|SiS310SetupSRCBase
mdefine_line|#define SiS310SetupSRCBase(base) &bslash;&n;      if (CmdQueLen &lt;= 0)  SiS310Idle;&bslash;&n;      MMIO_OUT32(ivideo.mmio_vbase, SRC_ADDR, base);&bslash;&n;      CmdQueLen--;
DECL|macro|SiS310SetupSRCPitch
mdefine_line|#define SiS310SetupSRCPitch(pitch) &bslash;&n;      if (CmdQueLen &lt;= 0)  SiS310Idle;&bslash;&n;      MMIO_OUT16(ivideo.mmio_vbase, SRC_PITCH, pitch);&bslash;&n;      CmdQueLen--;
DECL|macro|SiS310SetupSRCXY
mdefine_line|#define SiS310SetupSRCXY(x,y) &bslash;&n;      if (CmdQueLen &lt;= 0)  SiS310Idle;&bslash;&n;      MMIO_OUT32(ivideo.mmio_vbase, SRC_Y, (x)&lt;&lt;16 | (y) );&bslash;&n;      CmdQueLen--;
DECL|macro|SiS310SetupDSTBase
mdefine_line|#define SiS310SetupDSTBase(base) &bslash;&n;      if (CmdQueLen &lt;= 0)  SiS310Idle;&bslash;&n;      MMIO_OUT32(ivideo.mmio_vbase, DST_ADDR, base);&bslash;&n;      CmdQueLen--;
DECL|macro|SiS310SetupDSTXY
mdefine_line|#define SiS310SetupDSTXY(x,y) &bslash;&n;      if (CmdQueLen &lt;= 0)  SiS310Idle;&bslash;&n;      MMIO_OUT32(ivideo.mmio_vbase, DST_Y, (x)&lt;&lt;16 | (y) );&bslash;&n;      CmdQueLen--;
DECL|macro|SiS310SetupDSTRect
mdefine_line|#define SiS310SetupDSTRect(x,y) &bslash;&n;      if (CmdQueLen &lt;= 0)  SiS310Idle;&bslash;&n;      MMIO_OUT32(ivideo.mmio_vbase, DST_PITCH, (y)&lt;&lt;16 | (x) );&bslash;&n;      CmdQueLen--;
DECL|macro|SiS310SetupDSTColorDepth
mdefine_line|#define SiS310SetupDSTColorDepth(bpp) &bslash;&n;      if (CmdQueLen &lt;= 0)  SiS310Idle;&bslash;&n;      MMIO_OUT16(ivideo.mmio_vbase, AGP_BASE, bpp);&bslash;&n;      CmdQueLen--;
DECL|macro|SiS310SetupRect
mdefine_line|#define SiS310SetupRect(w,h) &bslash;&n;      if (CmdQueLen &lt;= 0)  SiS310Idle;&bslash;&n;      MMIO_OUT32(ivideo.mmio_vbase, RECT_WIDTH, (h)&lt;&lt;16 | (w) );&bslash;&n;      CmdQueLen--;
DECL|macro|SiS310SetupPATFG
mdefine_line|#define SiS310SetupPATFG(color) &bslash;&n;      if (CmdQueLen &lt;= 0)  SiS310Idle;&bslash;&n;      MMIO_OUT32(ivideo.mmio_vbase, PAT_FGCOLOR, color);&bslash;&n;      CmdQueLen--;
DECL|macro|SiS310SetupPATBG
mdefine_line|#define SiS310SetupPATBG(color) &bslash;&n;      if (CmdQueLen &lt;= 0)  SiS310Idle;&bslash;&n;      MMIO_OUT32(ivideo.mmio_vbase, PAT_BGCOLOR, color);&bslash;&n;      CmdQueLen--;
DECL|macro|SiS310SetupSRCFG
mdefine_line|#define SiS310SetupSRCFG(color) &bslash;&n;      if (CmdQueLen &lt;= 0)  SiS310Idle;&bslash;&n;      MMIO_OUT32(ivideo.mmio_vbase, SRC_FGCOLOR, color);&bslash;&n;      CmdQueLen--;
DECL|macro|SiS310SetupSRCBG
mdefine_line|#define SiS310SetupSRCBG(color) &bslash;&n;      if (CmdQueLen &lt;= 0)  SiS310Idle;&bslash;&n;      MMIO_OUT32(ivideo.mmio_vbase, SRC_BGCOLOR, color);&bslash;&n;      CmdQueLen--;
DECL|macro|SiS310SetupSRCTrans
mdefine_line|#define SiS310SetupSRCTrans(color) &bslash;&n;      if (CmdQueLen &lt;= 1)  SiS310Idle;&bslash;&n;      MMIO_OUT32(ivideo.mmio_vbase, TRANS_SRC_KEY_HIGH, color);&bslash;&n;      MMIO_OUT32(ivideo.mmio_vbase, TRANS_SRC_KEY_LOW, color);&bslash;&n;      CmdQueLen -= 2;
DECL|macro|SiS310SetupDSTTrans
mdefine_line|#define SiS310SetupDSTTrans(color) &bslash;&n;      if (CmdQueLen &lt;= 1)  SiS310Idle;&bslash;&n;      MMIO_OUT32(ivideo.mmio_vbase, TRANS_DST_KEY_HIGH, color); &bslash;&n;      MMIO_OUT32(ivideo.mmio_vbase, TRANS_DST_KEY_LOW, color); &bslash;&n;      CmdQueLen -= 2;
DECL|macro|SiS310SetupMONOPAT
mdefine_line|#define SiS310SetupMONOPAT(p0,p1) &bslash;&n;      if (CmdQueLen &lt;= 1)  SiS310Idle;&bslash;&n;      MMIO_OUT32(ivideo.mmio_vbase, MONO_MASK, p0);&bslash;&n;      MMIO_OUT32(ivideo.mmio_vbase, MONO_MASK+4, p1);&bslash;&n;      CmdQueLen -= 2;
DECL|macro|SiS310SetupClipLT
mdefine_line|#define SiS310SetupClipLT(left,top) &bslash;&n;      if (CmdQueLen &lt;= 0)  SiS310Idle;&bslash;&n;      MMIO_OUT32(ivideo.mmio_vbase, LEFT_CLIP, ((left) &amp; 0xFFFF) | (top)&lt;&lt;16 );&bslash;&n;      CmdQueLen--;
DECL|macro|SiS310SetupClipRB
mdefine_line|#define SiS310SetupClipRB(right,bottom) &bslash;&n;      if (CmdQueLen &lt;= 0)  SiS310Idle;&bslash;&n;      MMIO_OUT32(ivideo.mmio_vbase, RIGHT_CLIP, ((right) &amp; 0xFFFF) | (bottom)&lt;&lt;16 );&bslash;&n;      CmdQueLen--;
DECL|macro|SiS310SetupROP
mdefine_line|#define SiS310SetupROP(rop) &bslash;&n;      ivideo.CommandReg = (rop) &lt;&lt; 8;
DECL|macro|SiS310SetupCMDFlag
mdefine_line|#define SiS310SetupCMDFlag(flags) &bslash;&n;      ivideo.CommandReg |= (flags);
DECL|macro|SiS310DoCMD
mdefine_line|#define SiS310DoCMD &bslash;&n;      if (CmdQueLen &lt;= 1)  SiS310Idle;&bslash;&n;      MMIO_OUT32(ivideo.mmio_vbase, COMMAND_READY, ivideo.CommandReg); &bslash;&n;      MMIO_OUT32(ivideo.mmio_vbase, FIRE_TRIGGER, 0); &bslash;&n;      CmdQueLen -= 2;
DECL|macro|SiS310SetupX0Y0
mdefine_line|#define SiS310SetupX0Y0(x,y) &bslash;&n;      if (CmdQueLen &lt;= 0)  SiS310Idle;&bslash;&n;      MMIO_OUT32(ivideo.mmio_vbase, LINE_X0, (y)&lt;&lt;16 | (x) );&bslash;&n;      CmdQueLen--;
DECL|macro|SiS310SetupX1Y1
mdefine_line|#define SiS310SetupX1Y1(x,y) &bslash;&n;      if (CmdQueLen &lt;= 0)  SiS310Idle;&bslash;&n;      MMIO_OUT32(ivideo.mmio_vbase, LINE_X1, (y)&lt;&lt;16 | (x) );&bslash;&n;      CmdQueLen--;
DECL|macro|SiS310SetupLineCount
mdefine_line|#define SiS310SetupLineCount(c) &bslash;&n;      if (CmdQueLen &lt;= 0)  SiS310Idle;&bslash;&n;      MMIO_OUT16(ivideo.mmio_vbase, LINE_COUNT, c);&bslash;&n;      CmdQueLen--;
DECL|macro|SiS310SetupStylePeriod
mdefine_line|#define SiS310SetupStylePeriod(p) &bslash;&n;      if (CmdQueLen &lt;= 0)  SiS310Idle;&bslash;&n;      MMIO_OUT16(ivideo.mmio_vbase, LINE_STYLE_PERIOD, p);&bslash;&n;      CmdQueLen--;
DECL|macro|SiS310SetupStyleLow
mdefine_line|#define SiS310SetupStyleLow(ls) &bslash;&n;      if (CmdQueLen &lt;= 0)  SiS310Idle;&bslash;&n;      MMIO_OUT32(ivideo.mmio_vbase, LINE_STYLE_0, ls);&bslash;&n;      CmdQueLen--;
DECL|macro|SiS310SetupStyleHigh
mdefine_line|#define SiS310SetupStyleHigh(ls) &bslash;&n;      if (CmdQueLen &lt;= 0)  SiS310Idle;&bslash;&n;      MMIO_OUT32(ivideo.mmio_vbase, LINE_STYLE_1, ls);&bslash;&n;      CmdQueLen--;
r_int
id|sisfb_initaccel
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|sisfb_syncaccel
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|video_info
id|ivideo
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt;= KERNEL_VERSION(2,5,33)
r_void
id|fbcon_sis_bmove
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|srcy
comma
r_int
id|srcx
comma
r_int
id|dsty
comma
r_int
id|dstx
comma
r_int
id|height
comma
r_int
id|width
)paren
suffix:semicolon
r_void
id|fbcon_sis_revc
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|srcy
comma
r_int
id|srcx
)paren
suffix:semicolon
r_void
id|fbcon_sis_clear8
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|srcy
comma
r_int
id|srcx
comma
r_int
id|height
comma
r_int
id|width
)paren
suffix:semicolon
r_void
id|fbcon_sis_clear16
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|srcy
comma
r_int
id|srcx
comma
r_int
id|height
comma
r_int
id|width
)paren
suffix:semicolon
r_void
id|fbcon_sis_clear32
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|srcy
comma
r_int
id|srcx
comma
r_int
id|height
comma
r_int
id|width
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,5,34)
r_extern
r_int
id|sisfb_accel
suffix:semicolon
r_void
id|fbcon_sis_fillrect
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_const
r_struct
id|fb_fillrect
op_star
id|rect
)paren
suffix:semicolon
r_void
id|fbcon_sis_copyarea
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_const
r_struct
id|fb_copyarea
op_star
id|area
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
