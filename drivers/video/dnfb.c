macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;asm/amigaints.h&gt;
macro_line|#include &lt;asm/apollohw.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/module.h&gt;
multiline_comment|/* apollo video HW definitions */
multiline_comment|/*&n; * Control Registers.   IOBASE + $x&n; *&n; * Note: these are the Memory/IO BASE definitions for a mono card set to the&n; * alternate address&n; *&n; * Control 3A and 3B serve identical functions except that 3A&n; * deals with control 1 and 3b deals with Color LUT reg.&n; */
DECL|macro|AP_IOBASE
mdefine_line|#define AP_IOBASE       0x3b0&t;/* Base address of 1 plane board. */
DECL|macro|AP_STATUS
mdefine_line|#define AP_STATUS       isaIO2mem(AP_IOBASE+0)&t;/* Status register.  Read */
DECL|macro|AP_WRITE_ENABLE
mdefine_line|#define AP_WRITE_ENABLE isaIO2mem(AP_IOBASE+0)&t;/* Write Enable Register Write */
DECL|macro|AP_DEVICE_ID
mdefine_line|#define AP_DEVICE_ID    isaIO2mem(AP_IOBASE+1)&t;/* Device ID Register. Read */
DECL|macro|AP_ROP_1
mdefine_line|#define AP_ROP_1        isaIO2mem(AP_IOBASE+2)&t;/* Raster Operation reg. Write Word */
DECL|macro|AP_DIAG_MEM_REQ
mdefine_line|#define AP_DIAG_MEM_REQ isaIO2mem(AP_IOBASE+4)&t;/* Diagnostic Memory Request. Write Word */
DECL|macro|AP_CONTROL_0
mdefine_line|#define AP_CONTROL_0    isaIO2mem(AP_IOBASE+8)&t;/* Control Register 0.  Read/Write */
DECL|macro|AP_CONTROL_1
mdefine_line|#define AP_CONTROL_1    isaIO2mem(AP_IOBASE+0xa)&t;/* Control Register 1.  Read/Write */
DECL|macro|AP_CONTROL_3A
mdefine_line|#define AP_CONTROL_3A   isaIO2mem(AP_IOBASE+0xe)&t;/* Control Register 3a. Read/Write */
DECL|macro|AP_CONTROL_2
mdefine_line|#define AP_CONTROL_2    isaIO2mem(AP_IOBASE+0xc)&t;/* Control Register 2. Read/Write */
DECL|macro|FRAME_BUFFER_START
mdefine_line|#define FRAME_BUFFER_START 0x0FA0000
DECL|macro|FRAME_BUFFER_LEN
mdefine_line|#define FRAME_BUFFER_LEN 0x40000
multiline_comment|/* CREG 0 */
DECL|macro|VECTOR_MODE
mdefine_line|#define VECTOR_MODE 0x40&t;/* 010x.xxxx */
DECL|macro|DBLT_MODE
mdefine_line|#define DBLT_MODE   0x80&t;/* 100x.xxxx */
DECL|macro|NORMAL_MODE
mdefine_line|#define NORMAL_MODE 0xE0&t;/* 111x.xxxx */
DECL|macro|SHIFT_BITS
mdefine_line|#define SHIFT_BITS  0x1F&t;/* xxx1.1111 */
multiline_comment|/* other bits are Shift value */
multiline_comment|/* CREG 1 */
DECL|macro|AD_BLT
mdefine_line|#define AD_BLT      0x80&t;/* 1xxx.xxxx */
DECL|macro|NORMAL
mdefine_line|#define NORMAL      0x80 /* 1xxx.xxxx */&t;/* What is happening here ?? */
DECL|macro|INVERSE
mdefine_line|#define INVERSE     0x00 /* 0xxx.xxxx */&t;/* Clearing this reverses the screen */
DECL|macro|PIX_BLT
mdefine_line|#define PIX_BLT     0x00&t;/* 0xxx.xxxx */
DECL|macro|AD_HIBIT
mdefine_line|#define AD_HIBIT        0x40&t;/* xIxx.xxxx */
DECL|macro|ROP_EN
mdefine_line|#define ROP_EN          0x10&t;/* xxx1.xxxx */
DECL|macro|DST_EQ_SRC
mdefine_line|#define DST_EQ_SRC      0x00&t;/* xxx0.xxxx */
DECL|macro|nRESET_SYNC
mdefine_line|#define nRESET_SYNC     0x08&t;/* xxxx.1xxx */
DECL|macro|SYNC_ENAB
mdefine_line|#define SYNC_ENAB       0x02&t;/* xxxx.xx1x */
DECL|macro|BLANK_DISP
mdefine_line|#define BLANK_DISP      0x00&t;/* xxxx.xxx0 */
DECL|macro|ENAB_DISP
mdefine_line|#define ENAB_DISP       0x01&t;/* xxxx.xxx1 */
DECL|macro|NORM_CREG1
mdefine_line|#define NORM_CREG1      (nRESET_SYNC | SYNC_ENAB | ENAB_DISP)&t;/* no reset sync */
multiline_comment|/* CREG 2 */
multiline_comment|/*&n; * Following 3 defines are common to 1, 4 and 8 plane.&n; */
DECL|macro|S_DATA_1s
mdefine_line|#define S_DATA_1s   0x00 /* 00xx.xxxx */&t;/* set source to all 1&squot;s -- vector drawing */
DECL|macro|S_DATA_PIX
mdefine_line|#define S_DATA_PIX  0x40 /* 01xx.xxxx */&t;/* takes source from ls-bits and replicates over 16 bits */
DECL|macro|S_DATA_PLN
mdefine_line|#define S_DATA_PLN  0xC0 /* 11xx.xxxx */&t;/* normal, each data access =16-bits in&n;&t;&t;&t;&t;&t;&t;   one plane of image mem */
multiline_comment|/* CREG 3A/CREG 3B */
DECL|macro|RESET_CREG
macro_line|#       define RESET_CREG 0x80&t;/* 1000.0000 */
multiline_comment|/* ROP REG  -  all one nibble */
multiline_comment|/*      ********* NOTE : this is used r0,r1,r2,r3 *********** */
DECL|macro|ROP
mdefine_line|#define ROP(r2,r3,r0,r1) ( (U_SHORT)((r0)|((r1)&lt;&lt;4)|((r2)&lt;&lt;8)|((r3)&lt;&lt;12)) )
DECL|macro|DEST_ZERO
mdefine_line|#define DEST_ZERO               0x0
DECL|macro|SRC_AND_DEST
mdefine_line|#define SRC_AND_DEST    0x1
DECL|macro|SRC_AND_nDEST
mdefine_line|#define SRC_AND_nDEST   0x2
DECL|macro|SRC
mdefine_line|#define SRC                             0x3
DECL|macro|nSRC_AND_DEST
mdefine_line|#define nSRC_AND_DEST   0x4
DECL|macro|DEST
mdefine_line|#define DEST                    0x5
DECL|macro|SRC_XOR_DEST
mdefine_line|#define SRC_XOR_DEST    0x6
DECL|macro|SRC_OR_DEST
mdefine_line|#define SRC_OR_DEST             0x7
DECL|macro|SRC_NOR_DEST
mdefine_line|#define SRC_NOR_DEST    0x8
DECL|macro|SRC_XNOR_DEST
mdefine_line|#define SRC_XNOR_DEST   0x9
DECL|macro|nDEST
mdefine_line|#define nDEST                   0xA
DECL|macro|SRC_OR_nDEST
mdefine_line|#define SRC_OR_nDEST    0xB
DECL|macro|nSRC
mdefine_line|#define nSRC                    0xC
DECL|macro|nSRC_OR_DEST
mdefine_line|#define nSRC_OR_DEST    0xD
DECL|macro|SRC_NAND_DEST
mdefine_line|#define SRC_NAND_DEST   0xE
DECL|macro|DEST_ONE
mdefine_line|#define DEST_ONE                0xF
DECL|macro|SWAP
mdefine_line|#define SWAP(A) ((A&gt;&gt;8) | ((A&amp;0xff) &lt;&lt;8))
macro_line|#if 0
mdefine_line|#define outb(a,d) *(char *)(a)=(d)
mdefine_line|#define outw(a,d) *(unsigned short *)a=d
macro_line|#endif
DECL|variable|fb_info
r_static
r_struct
id|fb_info
id|fb_info
suffix:semicolon
multiline_comment|/* frame buffer operations */
r_static
r_int
id|dnfb_blank
c_func
(paren
r_int
id|blank
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_void
id|dnfb_copyarea
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_copyarea
op_star
id|area
)paren
suffix:semicolon
DECL|variable|dn_fb_ops
r_static
r_struct
id|fb_ops
id|dn_fb_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|fb_blank
op_assign
id|dnfb_blank
comma
dot
id|fb_fillrect
op_assign
id|cfb_fillrect
comma
dot
id|fb_copyarea
op_assign
id|dnfb_copyarea
comma
dot
id|fb_imageblit
op_assign
id|cfb_imageblit
comma
dot
id|fb_cursor
op_assign
id|cfb_cursor
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_struct
id|fb_var_screeninfo
id|dnfb_var
id|__initdata
op_assign
(brace
dot
id|xres
l_int|1280
comma
dot
id|yres
l_int|1024
comma
dot
id|xres_virtual
l_int|2048
comma
dot
id|yres_virtual
l_int|1024
comma
dot
id|bits_per_pixel
l_int|1
comma
dot
id|height
op_minus
l_int|1
comma
dot
id|width
op_minus
l_int|1
comma
dot
id|vmode
id|FB_VMODE_NONINTERLACED
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|fb_fix_screeninfo
id|dnfb_fix
id|__initdata
op_assign
(brace
dot
id|id
l_string|&quot;Apollo Mono&quot;
comma
dot
id|smem_start
(paren
id|FRAME_BUFFER_START
op_plus
id|IO_BASE
)paren
comma
dot
id|smem_len
id|FRAME_BUFFER_LEN
comma
dot
id|type
id|FB_TYPE_PACKED_PIXELS
comma
dot
id|visual
id|FB_VISUAL_MONO10
comma
dot
id|line_length
l_int|256
comma
)brace
suffix:semicolon
DECL|function|dnfb_blank
r_static
r_int
id|dnfb_blank
c_func
(paren
r_int
id|blank
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_if
c_cond
(paren
id|blank
)paren
id|outb
c_func
(paren
l_int|0x0
comma
id|AP_CONTROL_3A
)paren
suffix:semicolon
r_else
id|outb
c_func
(paren
l_int|0x1
comma
id|AP_CONTROL_3A
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|dnfb_copyarea
r_void
id|dnfb_copyarea
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_copyarea
op_star
id|area
)paren
(brace
r_int
id|incr
comma
id|y_delta
comma
id|pre_read
op_assign
l_int|0
comma
id|x_end
comma
id|x_word_count
suffix:semicolon
id|ushort
op_star
id|src
comma
id|dummy
suffix:semicolon
id|uint
id|start_mask
comma
id|end_mask
comma
id|dest
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
id|incr
op_assign
(paren
id|area-&gt;dy
op_le
id|area-&gt;sy
)paren
ques
c_cond
l_int|1
suffix:colon
op_minus
l_int|1
suffix:semicolon
id|src
op_assign
(paren
id|ushort
op_star
)paren
(paren
id|info-&gt;screen_base
op_plus
id|area-&gt;sy
op_star
id|info-&gt;fix.line_length
op_plus
(paren
id|area-&gt;sx
op_rshift
l_int|4
)paren
)paren
suffix:semicolon
id|dest
op_assign
id|area-&gt;dy
op_star
(paren
id|info-&gt;fix.line_length
op_rshift
l_int|1
)paren
op_plus
(paren
id|area-&gt;dx
op_rshift
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|incr
OG
l_int|0
)paren
(brace
id|y_delta
op_assign
(paren
id|info-&gt;fix.line_length
op_star
l_int|8
)paren
op_minus
id|area-&gt;sx
op_minus
id|area-&gt;width
suffix:semicolon
id|x_end
op_assign
id|area-&gt;dx
op_plus
id|area-&gt;width
op_minus
l_int|1
suffix:semicolon
id|x_word_count
op_assign
(paren
id|x_end
op_rshift
l_int|4
)paren
op_minus
(paren
id|area-&gt;dx
op_rshift
l_int|4
)paren
op_plus
l_int|1
suffix:semicolon
id|start_mask
op_assign
l_int|0xffff0000
op_rshift
(paren
id|area-&gt;dx
op_amp
l_int|0xf
)paren
suffix:semicolon
id|end_mask
op_assign
l_int|0x7ffff
op_rshift
(paren
id|x_end
op_amp
l_int|0xf
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
(paren
(paren
id|area-&gt;dx
op_amp
l_int|0xf
)paren
op_minus
(paren
id|area-&gt;sx
op_amp
l_int|0xf
)paren
)paren
op_mod
l_int|16
)paren
op_or
(paren
l_int|0x4
op_lshift
l_int|5
)paren
comma
id|AP_CONTROL_0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|area-&gt;dx
op_amp
l_int|0xf
)paren
OL
(paren
id|area-&gt;sx
op_amp
l_int|0xf
)paren
)paren
id|pre_read
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|y_delta
op_assign
op_minus
(paren
(paren
id|info-&gt;fix.line_length
op_star
l_int|8
)paren
op_minus
id|area-&gt;sx
op_minus
id|area-&gt;width
)paren
suffix:semicolon
id|x_end
op_assign
id|area-&gt;dx
op_minus
id|area-&gt;width
op_plus
l_int|1
suffix:semicolon
id|x_word_count
op_assign
(paren
id|area-&gt;dx
op_rshift
l_int|4
)paren
op_minus
(paren
id|x_end
op_rshift
l_int|4
)paren
op_plus
l_int|1
suffix:semicolon
id|start_mask
op_assign
l_int|0x7ffff
op_rshift
(paren
id|area-&gt;dx
op_amp
l_int|0xf
)paren
suffix:semicolon
id|end_mask
op_assign
l_int|0xffff0000
op_rshift
(paren
id|x_end
op_amp
l_int|0xf
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
(paren
op_minus
(paren
(paren
id|area-&gt;sx
op_amp
l_int|0xf
)paren
op_minus
(paren
id|area-&gt;dx
op_amp
l_int|0xf
)paren
)paren
)paren
op_mod
l_int|16
)paren
op_or
(paren
l_int|0x4
op_lshift
l_int|5
)paren
comma
id|AP_CONTROL_0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|area-&gt;dx
op_amp
l_int|0xf
)paren
OG
(paren
id|area-&gt;sx
op_amp
l_int|0xf
)paren
)paren
id|pre_read
op_assign
l_int|1
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|area-&gt;height
suffix:semicolon
id|i
op_increment
)paren
(brace
id|outb
c_func
(paren
l_int|0xc
op_or
(paren
id|dest
op_rshift
l_int|16
)paren
comma
id|AP_CONTROL_3A
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pre_read
)paren
(brace
id|dummy
op_assign
op_star
id|src
suffix:semicolon
id|src
op_add_assign
id|incr
suffix:semicolon
)brace
r_if
c_cond
(paren
id|x_word_count
)paren
(brace
id|outb
c_func
(paren
id|start_mask
comma
id|AP_WRITE_ENABLE
)paren
suffix:semicolon
op_star
id|src
op_assign
id|dest
suffix:semicolon
id|src
op_add_assign
id|incr
suffix:semicolon
id|dest
op_add_assign
id|incr
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|AP_WRITE_ENABLE
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|1
suffix:semicolon
id|j
OL
(paren
id|x_word_count
op_minus
l_int|1
)paren
suffix:semicolon
id|j
op_increment
)paren
(brace
op_star
id|src
op_assign
id|dest
suffix:semicolon
id|src
op_add_assign
id|incr
suffix:semicolon
id|dest
op_add_assign
id|incr
suffix:semicolon
)brace
id|outb
c_func
(paren
id|start_mask
comma
id|AP_WRITE_ENABLE
)paren
suffix:semicolon
op_star
id|src
op_assign
id|dest
suffix:semicolon
id|dest
op_add_assign
id|incr
suffix:semicolon
id|src
op_add_assign
id|incr
suffix:semicolon
)brace
r_else
(brace
id|outb
c_func
(paren
id|start_mask
op_or
id|end_mask
comma
id|AP_WRITE_ENABLE
)paren
suffix:semicolon
op_star
id|src
op_assign
id|dest
suffix:semicolon
id|dest
op_add_assign
id|incr
suffix:semicolon
id|src
op_add_assign
id|incr
suffix:semicolon
)brace
id|src
op_add_assign
(paren
id|y_delta
op_div
l_int|16
)paren
suffix:semicolon
id|dest
op_add_assign
(paren
id|y_delta
op_div
l_int|16
)paren
suffix:semicolon
)brace
id|outb
c_func
(paren
id|NORMAL_MODE
comma
id|AP_CONTROL_0
)paren
suffix:semicolon
)brace
DECL|function|dnfb_init
r_int
r_int
id|__init
id|dnfb_init
c_func
(paren
r_int
r_int
id|mem_start
)paren
(brace
r_int
id|err
suffix:semicolon
id|fb_info.node
op_assign
id|NODEV
suffix:semicolon
id|fb_info.fbops
op_assign
op_amp
id|dn_fb_ops
suffix:semicolon
id|fb_info.fix
op_assign
id|dnfb_fix
suffix:semicolon
id|fb_info.var
op_assign
id|dnfb_var
suffix:semicolon
id|fb_info.screen_base
op_assign
(paren
id|u_char
op_star
)paren
id|fb_info.fix.smem_start
suffix:semicolon
id|fb_alloc_cmap
c_func
(paren
op_amp
id|fb_info.cmap
comma
l_int|2
comma
l_int|0
)paren
suffix:semicolon
id|err
op_assign
id|register_framebuffer
c_func
(paren
op_amp
id|fb_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;unable to register apollo frame buffer&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* now we have registered we can safely setup the hardware */
id|outb
c_func
(paren
id|RESET_CREG
comma
id|AP_CONTROL_3A
)paren
suffix:semicolon
id|outw
c_func
(paren
l_int|0x0
comma
id|AP_WRITE_ENABLE
)paren
suffix:semicolon
id|outb
c_func
(paren
id|NORMAL_MODE
comma
id|AP_CONTROL_0
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
id|AD_BLT
op_or
id|DST_EQ_SRC
op_or
id|NORM_CREG1
)paren
comma
id|AP_CONTROL_1
)paren
suffix:semicolon
id|outb
c_func
(paren
id|S_DATA_PLN
comma
id|AP_CONTROL_2
)paren
suffix:semicolon
id|outw
c_func
(paren
id|SWAP
c_func
(paren
l_int|0x3
)paren
comma
id|AP_ROP_1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;apollo frame buffer alive and kicking !&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|mem_start
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
