multiline_comment|/*&n; *  linux/drivers/video/fm2fb.c -- BSC FrameMaster II/Rainbow II frame buffer&n; *&t;&t;&t;&t;   device&n; *&n; *&t;Copyright (C) 1998 Steffen A. Mork (mork@ls7.cs.uni-dortmund.de)&n; *&t;Copyright (C) 1999 Geert Uytterhoeven&n; *&n; *  Written for 2.0.x by Steffen A. Mork&n; *  Ported to 2.1.x by Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/zorro.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;video/fbcon.h&gt;
macro_line|#include &lt;video/fbcon-cfb32.h&gt;
multiline_comment|/*&n; *&t;Some technical notes:&n; *&n; *&t;The BSC FrameMaster II (or Rainbow II) is a simple very dumb&n; *&t;frame buffer which allows to display 24 bit true color images.&n; *&t;Each pixel is 32 bit width so it&squot;s very easy to maintain the&n; *&t;frame buffer. One long word has the following layout:&n; *&t;AARRGGBB which means: AA the alpha channel byte, RR the red&n; *&t;channel, GG the green channel and BB the blue channel.&n; *&n; *&t;The FrameMaster II supports the following video modes.&n; *&t;- PAL/NTSC&n; *&t;- interlaced/non interlaced&n; *&t;- composite sync/sync/sync over green&n; *&n; *&t;The resolution is to the following both ones:&n; *&t;- 768x576 (PAL)&n; *&t;- 768x480 (NTSC)&n; *&n; *&t;This means that pixel access per line is fixed due to the&n; *&t;fixed line width. In case of maximal resolution the frame&n; *&t;buffer needs an amount of memory of 1.769.472 bytes which&n; *&t;is near to 2 MByte (the allocated address space of Zorro2).&n; *&t;The memory is channel interleaved. That means every channel&n; *&t;owns four VRAMs. Unfortunatly most FrameMasters II are&n; *&t;not assembled with memory for the alpha channel. In this&n; *&t;case it could be possible to add the frame buffer into the&n; *&t;normal memory pool.&n; *&t;&n; *&t;At relative address 0x1ffff8 of the frame buffers base address&n; *&t;there exists a control register with the number of&n; *&t;four control bits. They have the following meaning:&n; *&t;bit value meaning&n; *&n; *&t; 0    1   0=interlaced/1=non interlaced&n; *&t; 1    2   0=video out disabled/1=video out enabled&n; *&t; 2    4   0=normal mode as jumpered via JP8/1=complement mode&n; *&t; 3    8   0=read  onboard ROM/1 normal operation (required)&n; *&n; *&t;As mentioned above there are several jumper. I think there&n; *&t;is not very much information about the FrameMaster II in&n; *&t;the world so I add these information for completeness.&n; *&n; *&t;JP1  interlace selection (1-2 non interlaced/2-3 interlaced) &n; *&t;JP2  wait state creation (leave as is!)&n; *&t;JP3  wait state creation (leave as is!)&n; *&t;JP4  modulate composite sync on green output (1-2 composite&n; *&t;     sync on green channel/2-3 normal composite sync)&n; *&t;JP5  create test signal, shorting this jumper will create&n; *&t;     a white screen&n; *&t;JP6  sync creation (1-2 composite sync/2-3 H-sync output)&n; *&t;JP8  video mode (1-2 PAL/2-3 NTSC)&n; *&n; *&t;With the following jumpering table you can connect the&n; *&t;FrameMaster II to a normal TV via SCART connector:&n; *&t;JP1:  2-3&n; *&t;JP4:  2-3&n; *&t;JP6:  2-3&n; *&t;JP8:  1-2 (means PAL for Europe)&n; *&n; *&t;NOTE:&n; *&t;There is no other possibility to change the video timings&n; *&t;except the interlaced/non interlaced, sync control and the&n; *&t;video mode PAL (50 Hz)/NTSC (60 Hz). Inside this&n; *&t;FrameMaster II driver are assumed values to avoid anomalies&n; *&t;to a future X server. Except the pixel clock is really&n; *&t;constant at 30 MHz.&n; *&n; *&t;9 pin female video connector:&n; *&n; *&t;1  analog red 0.7 Vss&n; *&t;2  analog green 0.7 Vss&n; *&t;3  analog blue 0.7 Vss&n; *&t;4  H-sync TTL&n; *&t;5  V-sync TTL&n; *&t;6  ground&n; *&t;7  ground&n; *&t;8  ground&n; *&t;9  ground&n; *&n; *&t;Some performance notes:&n; *&t;The FrameMaster II was not designed to display a console&n; *&t;this driver would do! It was designed to display still true&n; *&t;color images. Imagine: When scroll up a text line there&n; *&t;must copied ca. 1.7 MBytes to another place inside this&n; *&t;frame buffer. This means 1.7 MByte read and 1.7 MByte write&n; *&t;over the slow 16 bit wide Zorro2 bus! A scroll of one&n; *&t;line needs 1 second so do not expect to much from this&n; *&t;driver - he is at the limit!&n; *&n; */
multiline_comment|/*&n; *&t;definitions&n; */
DECL|macro|FRAMEMASTER_SIZE
mdefine_line|#define FRAMEMASTER_SIZE&t;0x200000
DECL|macro|FRAMEMASTER_REG
mdefine_line|#define FRAMEMASTER_REG&t;&t;0x1ffff8
DECL|macro|FRAMEMASTER_NOLACE
mdefine_line|#define FRAMEMASTER_NOLACE&t;1
DECL|macro|FRAMEMASTER_ENABLE
mdefine_line|#define FRAMEMASTER_ENABLE&t;2
DECL|macro|FRAMEMASTER_COMPL
mdefine_line|#define FRAMEMASTER_COMPL&t;4
DECL|macro|FRAMEMASTER_ROM
mdefine_line|#define FRAMEMASTER_ROM&t;&t;8
DECL|struct|FrameMaster_fb_par
r_struct
id|FrameMaster_fb_par
(brace
DECL|member|xres
r_int
id|xres
suffix:semicolon
DECL|member|yres
r_int
id|yres
suffix:semicolon
DECL|member|bpp
r_int
id|bpp
suffix:semicolon
DECL|member|pixclock
r_int
id|pixclock
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|fm2fb_mem_phys
r_static
r_int
r_int
id|fm2fb_mem_phys
suffix:semicolon
DECL|variable|fm2fb_mem
r_static
r_void
op_star
id|fm2fb_mem
suffix:semicolon
DECL|variable|fm2fb_reg_phys
r_static
r_int
r_int
id|fm2fb_reg_phys
suffix:semicolon
DECL|variable|fm2fb_reg
r_static
r_volatile
r_int
r_char
op_star
id|fm2fb_reg
suffix:semicolon
DECL|variable|disp
r_static
r_struct
id|display
id|disp
suffix:semicolon
DECL|variable|fb_info
r_static
r_struct
id|fb_info
id|fb_info
suffix:semicolon
DECL|member|red
DECL|member|green
DECL|member|blue
DECL|member|pad
DECL|variable|palette
r_static
r_struct
(brace
id|u_char
id|red
comma
id|green
comma
id|blue
comma
id|pad
suffix:semicolon
)brace
id|palette
(braket
l_int|16
)braket
suffix:semicolon
macro_line|#ifdef FBCON_HAS_CFB32
DECL|variable|fbcon_cfb32_cmap
r_static
id|u32
id|fbcon_cfb32_cmap
(braket
l_int|16
)braket
suffix:semicolon
macro_line|#endif
DECL|variable|fb_fix
r_static
r_struct
id|fb_fix_screeninfo
id|fb_fix
suffix:semicolon
DECL|variable|fb_var
r_static
r_struct
id|fb_var_screeninfo
id|fb_var
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|fm2fb_mode
id|__initdata
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|macro|FM2FB_MODE_PAL
mdefine_line|#define FM2FB_MODE_PAL&t;0
DECL|macro|FM2FB_MODE_NTSC
mdefine_line|#define FM2FB_MODE_NTSC&t;1
DECL|variable|__initdata
r_static
r_struct
id|fb_var_screeninfo
id|fb_var_modes
(braket
)braket
id|__initdata
op_assign
(brace
(brace
multiline_comment|/* 768 x 576, 32 bpp (PAL) */
l_int|768
comma
l_int|576
comma
l_int|768
comma
l_int|576
comma
l_int|0
comma
l_int|0
comma
l_int|32
comma
l_int|0
comma
(brace
l_int|16
comma
l_int|8
comma
l_int|0
)brace
comma
(brace
l_int|8
comma
l_int|8
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|8
comma
l_int|0
)brace
comma
(brace
l_int|24
comma
l_int|8
comma
l_int|0
)brace
comma
l_int|0
comma
id|FB_ACTIVATE_NOW
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
id|FB_ACCEL_NONE
comma
l_int|33333
comma
l_int|10
comma
l_int|102
comma
l_int|10
comma
l_int|5
comma
l_int|80
comma
l_int|34
comma
id|FB_SYNC_COMP_HIGH_ACT
comma
l_int|0
)brace
comma
(brace
multiline_comment|/* 768 x 480, 32 bpp (NTSC - not supported yet */
l_int|768
comma
l_int|480
comma
l_int|768
comma
l_int|480
comma
l_int|0
comma
l_int|0
comma
l_int|32
comma
l_int|0
comma
(brace
l_int|16
comma
l_int|8
comma
l_int|0
)brace
comma
(brace
l_int|8
comma
l_int|8
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|8
comma
l_int|0
)brace
comma
(brace
l_int|24
comma
l_int|8
comma
l_int|0
)brace
comma
l_int|0
comma
id|FB_ACTIVATE_NOW
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
id|FB_ACCEL_NONE
comma
l_int|33333
comma
l_int|10
comma
l_int|102
comma
l_int|10
comma
l_int|5
comma
l_int|80
comma
l_int|34
comma
id|FB_SYNC_COMP_HIGH_ACT
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/*&n;     *  Interface used by the world&n;     */
r_static
r_int
id|fm2fb_get_fix
c_func
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|fm2fb_get_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|fm2fb_set_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|fm2fb_get_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_int
id|kspc
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|fm2fb_setcolreg
c_func
(paren
id|u_int
id|regno
comma
id|u_int
id|red
comma
id|u_int
id|green
comma
id|u_int
id|blue
comma
id|u_int
id|transp
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|fm2fb_blank
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
multiline_comment|/*&n;     *  Interface to the low level console driver&n;     */
r_int
id|fm2fb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|fm2fbcon_switch
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|fm2fbcon_updatevar
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/*&n;     *  Internal routines&n;     */
r_static
r_int
id|fm2fb_getcolreg
c_func
(paren
id|u_int
id|regno
comma
id|u_int
op_star
id|red
comma
id|u_int
op_star
id|green
comma
id|u_int
op_star
id|blue
comma
id|u_int
op_star
id|transp
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
DECL|variable|fm2fb_ops
r_static
r_struct
id|fb_ops
id|fm2fb_ops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|fb_get_fix
suffix:colon
id|fm2fb_get_fix
comma
id|fb_get_var
suffix:colon
id|fm2fb_get_var
comma
id|fb_set_var
suffix:colon
id|fm2fb_set_var
comma
id|fb_get_cmap
suffix:colon
id|fm2fb_get_cmap
comma
id|fb_set_cmap
suffix:colon
id|gen_set_cmap
comma
id|fb_setcolreg
suffix:colon
id|fm2fb_setcolreg
comma
id|fb_blank
suffix:colon
id|fm2fb_blank
comma
)brace
suffix:semicolon
multiline_comment|/*&n;     *  Get the Fixed Part of the Display&n;     */
DECL|function|fm2fb_get_fix
r_static
r_int
id|fm2fb_get_fix
c_func
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
id|memcpy
c_func
(paren
id|fix
comma
op_amp
id|fb_fix
comma
r_sizeof
(paren
id|fb_fix
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Get the User Defined Part of the Display&n;     */
DECL|function|fm2fb_get_var
r_static
r_int
id|fm2fb_get_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
id|memcpy
c_func
(paren
id|var
comma
op_amp
id|fb_var
comma
r_sizeof
(paren
id|fb_var
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Set the User Defined Part of the Display&n;     */
DECL|function|fm2fb_set_var
r_static
r_int
id|fm2fb_set_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|display
op_star
id|display
suffix:semicolon
r_int
id|oldbpp
op_assign
op_minus
l_int|1
comma
id|err
suffix:semicolon
r_if
c_cond
(paren
id|con
op_ge
l_int|0
)paren
id|display
op_assign
op_amp
id|fb_display
(braket
id|con
)braket
suffix:semicolon
r_else
id|display
op_assign
op_amp
id|disp
suffix:semicolon
multiline_comment|/* used during initialization */
r_if
c_cond
(paren
id|var-&gt;xres
OG
id|fb_var.xres
op_logical_or
id|var-&gt;yres
OG
id|fb_var.yres
op_logical_or
id|var-&gt;xres_virtual
OG
id|fb_var.xres_virtual
op_logical_or
id|var-&gt;yres_virtual
OG
id|fb_var.yres_virtual
op_logical_or
id|var-&gt;bits_per_pixel
OG
id|fb_var.bits_per_pixel
op_logical_or
id|var-&gt;nonstd
op_logical_or
(paren
id|var-&gt;vmode
op_amp
id|FB_VMODE_MASK
)paren
op_ne
id|FB_VMODE_NONINTERLACED
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|memcpy
c_func
(paren
id|var
comma
op_amp
id|fb_var
comma
r_sizeof
(paren
id|fb_var
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|var-&gt;activate
op_amp
id|FB_ACTIVATE_MASK
)paren
op_eq
id|FB_ACTIVATE_NOW
)paren
(brace
id|oldbpp
op_assign
id|display-&gt;var.bits_per_pixel
suffix:semicolon
id|display-&gt;var
op_assign
op_star
id|var
suffix:semicolon
)brace
r_if
c_cond
(paren
id|oldbpp
op_ne
id|var-&gt;bits_per_pixel
)paren
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|fb_alloc_cmap
c_func
(paren
op_amp
id|display-&gt;cmap
comma
l_int|0
comma
l_int|0
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
id|do_install_cmap
c_func
(paren
id|con
comma
id|info
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Get the Colormap&n;     */
DECL|function|fm2fb_get_cmap
r_static
r_int
id|fm2fb_get_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_int
id|kspc
comma
r_int
id|con
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
id|con
op_eq
id|info-&gt;currcon
)paren
multiline_comment|/* current console? */
r_return
id|fb_get_cmap
c_func
(paren
id|cmap
comma
id|kspc
comma
id|fm2fb_getcolreg
comma
id|info
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fb_display
(braket
id|con
)braket
dot
id|cmap.len
)paren
multiline_comment|/* non default colormap? */
id|fb_copy_cmap
c_func
(paren
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|cmap
comma
id|cmap
comma
id|kspc
ques
c_cond
l_int|0
suffix:colon
l_int|2
)paren
suffix:semicolon
r_else
id|fb_copy_cmap
c_func
(paren
id|fb_default_cmap
c_func
(paren
l_int|256
)paren
comma
id|cmap
comma
id|kspc
ques
c_cond
l_int|0
suffix:colon
l_int|2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Initialisation&n;     */
DECL|function|fm2fb_init
r_int
id|__init
id|fm2fb_init
c_func
(paren
r_void
)paren
(brace
r_int
id|is_fm
suffix:semicolon
r_struct
id|zorro_dev
op_star
id|z
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
op_star
id|ptr
suffix:semicolon
r_int
id|x
comma
id|y
suffix:semicolon
r_while
c_loop
(paren
(paren
id|z
op_assign
id|zorro_find_device
c_func
(paren
id|ZORRO_WILDCARD
comma
id|z
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|z-&gt;id
op_eq
id|ZORRO_PROD_BSC_FRAMEMASTER_II
)paren
id|is_fm
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|z-&gt;id
op_eq
id|ZORRO_PROD_HELFRICH_RAINBOW_II
)paren
id|is_fm
op_assign
l_int|0
suffix:semicolon
r_else
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|z-&gt;resource.start
comma
id|FRAMEMASTER_SIZE
comma
l_string|&quot;fm2fb&quot;
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* assigning memory to kernel space */
id|fm2fb_mem_phys
op_assign
id|z-&gt;resource.start
suffix:semicolon
id|fm2fb_mem
op_assign
id|ioremap
c_func
(paren
id|fm2fb_mem_phys
comma
id|FRAMEMASTER_SIZE
)paren
suffix:semicolon
id|fm2fb_reg_phys
op_assign
id|fm2fb_mem_phys
op_plus
id|FRAMEMASTER_REG
suffix:semicolon
id|fm2fb_reg
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
id|fm2fb_mem
op_plus
id|FRAMEMASTER_REG
)paren
suffix:semicolon
multiline_comment|/* make EBU color bars on display */
id|ptr
op_assign
(paren
r_int
r_int
op_star
)paren
id|fm2fb_mem
suffix:semicolon
r_for
c_loop
(paren
id|y
op_assign
l_int|0
suffix:semicolon
id|y
OL
l_int|576
suffix:semicolon
id|y
op_increment
)paren
(brace
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
l_int|96
suffix:semicolon
id|x
op_increment
)paren
op_star
id|ptr
op_increment
op_assign
l_int|0xffffff
suffix:semicolon
multiline_comment|/* white */
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
l_int|96
suffix:semicolon
id|x
op_increment
)paren
op_star
id|ptr
op_increment
op_assign
l_int|0xffff00
suffix:semicolon
multiline_comment|/* yellow */
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
l_int|96
suffix:semicolon
id|x
op_increment
)paren
op_star
id|ptr
op_increment
op_assign
l_int|0x00ffff
suffix:semicolon
multiline_comment|/* cyan */
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
l_int|96
suffix:semicolon
id|x
op_increment
)paren
op_star
id|ptr
op_increment
op_assign
l_int|0x00ff00
suffix:semicolon
multiline_comment|/* green */
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
l_int|96
suffix:semicolon
id|x
op_increment
)paren
op_star
id|ptr
op_increment
op_assign
l_int|0xff00ff
suffix:semicolon
multiline_comment|/* magenta */
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
l_int|96
suffix:semicolon
id|x
op_increment
)paren
op_star
id|ptr
op_increment
op_assign
l_int|0xff0000
suffix:semicolon
multiline_comment|/* red */
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
l_int|96
suffix:semicolon
id|x
op_increment
)paren
op_star
id|ptr
op_increment
op_assign
l_int|0x0000ff
suffix:semicolon
multiline_comment|/* blue */
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
l_int|96
suffix:semicolon
id|x
op_increment
)paren
op_star
id|ptr
op_increment
op_assign
l_int|0x000000
suffix:semicolon
multiline_comment|/* black */
)brace
id|fm2fb_blank
c_func
(paren
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fm2fb_mode
op_eq
op_minus
l_int|1
)paren
id|fm2fb_mode
op_assign
id|FM2FB_MODE_PAL
suffix:semicolon
id|fb_var
op_assign
id|fb_var_modes
(braket
id|fm2fb_mode
)braket
suffix:semicolon
id|strcpy
c_func
(paren
id|fb_fix.id
comma
id|is_fm
ques
c_cond
l_string|&quot;FrameMaster II&quot;
suffix:colon
l_string|&quot;Rainbow II&quot;
)paren
suffix:semicolon
id|fb_fix.smem_start
op_assign
id|fm2fb_mem_phys
suffix:semicolon
id|fb_fix.smem_len
op_assign
id|FRAMEMASTER_REG
suffix:semicolon
id|fb_fix.type
op_assign
id|FB_TYPE_PACKED_PIXELS
suffix:semicolon
id|fb_fix.type_aux
op_assign
l_int|0
suffix:semicolon
id|fb_fix.visual
op_assign
id|FB_VISUAL_TRUECOLOR
suffix:semicolon
id|fb_fix.line_length
op_assign
l_int|768
op_lshift
l_int|2
suffix:semicolon
id|fb_fix.mmio_start
op_assign
id|fm2fb_reg_phys
suffix:semicolon
id|fb_fix.mmio_len
op_assign
l_int|8
suffix:semicolon
id|fb_fix.accel
op_assign
id|FB_ACCEL_NONE
suffix:semicolon
id|disp.var
op_assign
id|fb_var
suffix:semicolon
id|disp.cmap.start
op_assign
l_int|0
suffix:semicolon
id|disp.cmap.len
op_assign
l_int|0
suffix:semicolon
id|disp.cmap.red
op_assign
id|disp.cmap.green
op_assign
id|disp.cmap.blue
op_assign
id|disp.cmap.transp
op_assign
l_int|NULL
suffix:semicolon
id|disp.screen_base
op_assign
(paren
r_char
op_star
)paren
id|fm2fb_mem
suffix:semicolon
id|disp.visual
op_assign
id|fb_fix.visual
suffix:semicolon
id|disp.type
op_assign
id|fb_fix.type
suffix:semicolon
id|disp.type_aux
op_assign
id|fb_fix.type_aux
suffix:semicolon
id|disp.ypanstep
op_assign
l_int|0
suffix:semicolon
id|disp.ywrapstep
op_assign
l_int|0
suffix:semicolon
id|disp.line_length
op_assign
id|fb_fix.line_length
suffix:semicolon
id|disp.can_soft_blank
op_assign
l_int|1
suffix:semicolon
id|disp.inverse
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef FBCON_HAS_CFB32
id|disp.dispsw
op_assign
op_amp
id|fbcon_cfb32
suffix:semicolon
id|disp.dispsw_data
op_assign
op_amp
id|fbcon_cfb32_cmap
suffix:semicolon
macro_line|#else
id|disp.dispsw
op_assign
op_amp
id|fbcon_dummy
suffix:semicolon
macro_line|#endif
id|disp.scrollmode
op_assign
id|SCROLL_YREDRAW
suffix:semicolon
id|strcpy
c_func
(paren
id|fb_info.modename
comma
id|fb_fix.id
)paren
suffix:semicolon
id|fb_info.node
op_assign
id|NODEV
suffix:semicolon
id|fb_info.fbops
op_assign
op_amp
id|fm2fb_ops
suffix:semicolon
id|fb_info.currcon
op_assign
op_minus
l_int|1
suffix:semicolon
id|fb_info.disp
op_assign
op_amp
id|disp
suffix:semicolon
id|fb_info.fontname
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|fb_info.changevar
op_assign
l_int|NULL
suffix:semicolon
id|fb_info.switch_con
op_assign
op_amp
id|fm2fbcon_switch
suffix:semicolon
id|fb_info.updatevar
op_assign
op_amp
id|fm2fbcon_updatevar
suffix:semicolon
id|fb_info.flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
id|fm2fb_set_var
c_func
(paren
op_amp
id|fb_var
comma
op_minus
l_int|1
comma
op_amp
id|fb_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_framebuffer
c_func
(paren
op_amp
id|fb_info
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;fb%d: %s frame buffer device&bslash;n&quot;
comma
id|GET_FB_IDX
c_func
(paren
id|fb_info.node
)paren
comma
id|fb_fix.id
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|fm2fb_setup
r_int
id|__init
id|fm2fb_setup
c_func
(paren
r_char
op_star
id|options
)paren
(brace
r_char
op_star
id|this_opt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|options
op_logical_or
op_logical_neg
op_star
id|options
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|this_opt
op_assign
id|strsep
c_func
(paren
op_amp
id|options
comma
l_string|&quot;,&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|this_opt
comma
l_string|&quot;pal&quot;
comma
l_int|3
)paren
)paren
id|fm2fb_mode
op_assign
id|FM2FB_MODE_PAL
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|this_opt
comma
l_string|&quot;ntsc&quot;
comma
l_int|4
)paren
)paren
id|fm2fb_mode
op_assign
id|FM2FB_MODE_NTSC
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fm2fbcon_switch
r_static
r_int
id|fm2fbcon_switch
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
multiline_comment|/* Do we have to save the colormap? */
r_if
c_cond
(paren
id|fb_display
(braket
id|info-&gt;currcon
)braket
dot
id|cmap.len
)paren
id|fb_get_cmap
c_func
(paren
op_amp
id|fb_display
(braket
id|info-&gt;currcon
)braket
dot
id|cmap
comma
l_int|1
comma
id|fm2fb_getcolreg
comma
id|info
)paren
suffix:semicolon
id|info-&gt;currcon
op_assign
id|con
suffix:semicolon
multiline_comment|/* Install new colormap */
id|do_install_cmap
c_func
(paren
id|con
comma
id|info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Update the `var&squot; structure (called by fbcon.c)&n;     */
DECL|function|fm2fbcon_updatevar
r_static
r_int
id|fm2fbcon_updatevar
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
multiline_comment|/* Nothing */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Blank the display.&n;     */
DECL|function|fm2fb_blank
r_static
r_int
id|fm2fb_blank
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
r_int
r_char
id|t
op_assign
id|FRAMEMASTER_ROM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|blank
)paren
id|t
op_or_assign
id|FRAMEMASTER_ENABLE
op_or
id|FRAMEMASTER_NOLACE
suffix:semicolon
id|fm2fb_reg
(braket
l_int|0
)braket
op_assign
id|t
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Read a single color register and split it into&n;     *  colors/transparent. Return != 0 for invalid regno.&n;     */
DECL|function|fm2fb_getcolreg
r_static
r_int
id|fm2fb_getcolreg
c_func
(paren
id|u_int
id|regno
comma
id|u_int
op_star
id|red
comma
id|u_int
op_star
id|green
comma
id|u_int
op_star
id|blue
comma
id|u_int
op_star
id|transp
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
id|regno
OG
l_int|15
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|red
op_assign
(paren
id|palette
(braket
id|regno
)braket
dot
id|red
op_lshift
l_int|8
)paren
op_or
id|palette
(braket
id|regno
)braket
dot
id|red
suffix:semicolon
op_star
id|green
op_assign
(paren
id|palette
(braket
id|regno
)braket
dot
id|green
op_lshift
l_int|8
)paren
op_or
id|palette
(braket
id|regno
)braket
dot
id|green
suffix:semicolon
op_star
id|blue
op_assign
(paren
id|palette
(braket
id|regno
)braket
dot
id|blue
op_lshift
l_int|8
)paren
op_or
id|palette
(braket
id|regno
)braket
dot
id|blue
suffix:semicolon
op_star
id|transp
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Set a single color register. The values supplied are already&n;     *  rounded down to the hardware&squot;s capabilities (according to the&n;     *  entries in the var structure). Return != 0 for invalid regno.&n;     */
DECL|function|fm2fb_setcolreg
r_static
r_int
id|fm2fb_setcolreg
c_func
(paren
id|u_int
id|regno
comma
id|u_int
id|red
comma
id|u_int
id|green
comma
id|u_int
id|blue
comma
id|u_int
id|transp
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
id|regno
OG
l_int|15
)paren
r_return
l_int|1
suffix:semicolon
id|red
op_rshift_assign
l_int|8
suffix:semicolon
id|green
op_rshift_assign
l_int|8
suffix:semicolon
id|blue
op_rshift_assign
l_int|8
suffix:semicolon
id|palette
(braket
id|regno
)braket
dot
id|red
op_assign
id|red
suffix:semicolon
id|palette
(braket
id|regno
)braket
dot
id|green
op_assign
id|green
suffix:semicolon
id|palette
(braket
id|regno
)braket
dot
id|blue
op_assign
id|blue
suffix:semicolon
macro_line|#ifdef FBCON_HAS_CFB32
id|fbcon_cfb32_cmap
(braket
id|regno
)braket
op_assign
(paren
id|red
op_lshift
l_int|16
)paren
op_or
(paren
id|green
op_lshift
l_int|8
)paren
op_or
id|blue
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
