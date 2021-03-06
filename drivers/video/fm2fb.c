multiline_comment|/*&n; *  linux/drivers/video/fm2fb.c -- BSC FrameMaster II/Rainbow II frame buffer&n; *&t;&t;&t;&t;   device&n; *&n; *&t;Copyright (C) 1998 Steffen A. Mork (linux-dev@morknet.de)&n; *&t;Copyright (C) 1999 Geert Uytterhoeven&n; *&n; *  Written for 2.0.x by Steffen A. Mork&n; *  Ported to 2.1.x by Geert Uytterhoeven&n; *  Ported to new api by James Simmons&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/zorro.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n; *&t;Some technical notes:&n; *&n; *&t;The BSC FrameMaster II (or Rainbow II) is a simple very dumb&n; *&t;frame buffer which allows to display 24 bit true color images.&n; *&t;Each pixel is 32 bit width so it&squot;s very easy to maintain the&n; *&t;frame buffer. One long word has the following layout:&n; *&t;AARRGGBB which means: AA the alpha channel byte, RR the red&n; *&t;channel, GG the green channel and BB the blue channel.&n; *&n; *&t;The FrameMaster II supports the following video modes.&n; *&t;- PAL/NTSC&n; *&t;- interlaced/non interlaced&n; *&t;- composite sync/sync/sync over green&n; *&n; *&t;The resolution is to the following both ones:&n; *&t;- 768x576 (PAL)&n; *&t;- 768x480 (NTSC)&n; *&n; *&t;This means that pixel access per line is fixed due to the&n; *&t;fixed line width. In case of maximal resolution the frame&n; *&t;buffer needs an amount of memory of 1.769.472 bytes which&n; *&t;is near to 2 MByte (the allocated address space of Zorro2).&n; *&t;The memory is channel interleaved. That means every channel&n; *&t;owns four VRAMs. Unfortunatly most FrameMasters II are&n; *&t;not assembled with memory for the alpha channel. In this&n; *&t;case it could be possible to add the frame buffer into the&n; *&t;normal memory pool.&n; *&n; *&t;At relative address 0x1ffff8 of the frame buffers base address&n; *&t;there exists a control register with the number of&n; *&t;four control bits. They have the following meaning:&n; *&t;bit value meaning&n; *&n; *&t; 0    1   0=interlaced/1=non interlaced&n; *&t; 1    2   0=video out disabled/1=video out enabled&n; *&t; 2    4   0=normal mode as jumpered via JP8/1=complement mode&n; *&t; 3    8   0=read  onboard ROM/1 normal operation (required)&n; *&n; *&t;As mentioned above there are several jumper. I think there&n; *&t;is not very much information about the FrameMaster II in&n; *&t;the world so I add these information for completeness.&n; *&n; *&t;JP1  interlace selection (1-2 non interlaced/2-3 interlaced)&n; *&t;JP2  wait state creation (leave as is!)&n; *&t;JP3  wait state creation (leave as is!)&n; *&t;JP4  modulate composite sync on green output (1-2 composite&n; *&t;     sync on green channel/2-3 normal composite sync)&n; *&t;JP5  create test signal, shorting this jumper will create&n; *&t;     a white screen&n; *&t;JP6  sync creation (1-2 composite sync/2-3 H-sync output)&n; *&t;JP8  video mode (1-2 PAL/2-3 NTSC)&n; *&n; *&t;With the following jumpering table you can connect the&n; *&t;FrameMaster II to a normal TV via SCART connector:&n; *&t;JP1:  2-3&n; *&t;JP4:  2-3&n; *&t;JP6:  2-3&n; *&t;JP8:  1-2 (means PAL for Europe)&n; *&n; *&t;NOTE:&n; *&t;There is no other possibility to change the video timings&n; *&t;except the interlaced/non interlaced, sync control and the&n; *&t;video mode PAL (50 Hz)/NTSC (60 Hz). Inside this&n; *&t;FrameMaster II driver are assumed values to avoid anomalies&n; *&t;to a future X server. Except the pixel clock is really&n; *&t;constant at 30 MHz.&n; *&n; *&t;9 pin female video connector:&n; *&n; *&t;1  analog red 0.7 Vss&n; *&t;2  analog green 0.7 Vss&n; *&t;3  analog blue 0.7 Vss&n; *&t;4  H-sync TTL&n; *&t;5  V-sync TTL&n; *&t;6  ground&n; *&t;7  ground&n; *&t;8  ground&n; *&t;9  ground&n; *&n; *&t;Some performance notes:&n; *&t;The FrameMaster II was not designed to display a console&n; *&t;this driver would do! It was designed to display still true&n; *&t;color images. Imagine: When scroll up a text line there&n; *&t;must copied ca. 1.7 MBytes to another place inside this&n; *&t;frame buffer. This means 1.7 MByte read and 1.7 MByte write&n; *&t;over the slow 16 bit wide Zorro2 bus! A scroll of one&n; *&t;line needs 1 second so do not expect to much from this&n; *&t;driver - he is at the limit!&n; *&n; */
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
DECL|variable|fm2fb_reg
r_static
r_volatile
r_int
r_char
op_star
id|fm2fb_reg
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_struct
id|fb_fix_screeninfo
id|fb_fix
id|__devinitdata
op_assign
(brace
dot
id|smem_len
op_assign
id|FRAMEMASTER_REG
comma
dot
id|type
op_assign
id|FB_TYPE_PACKED_PIXELS
comma
dot
id|visual
op_assign
id|FB_VISUAL_TRUECOLOR
comma
dot
id|line_length
op_assign
(paren
l_int|768
op_lshift
l_int|2
)paren
comma
dot
id|mmio_len
op_assign
(paren
l_int|8
)paren
comma
dot
id|accel
op_assign
id|FB_ACCEL_NONE
comma
)brace
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_int
id|fm2fb_mode
id|__devinitdata
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|macro|FM2FB_MODE_PAL
mdefine_line|#define FM2FB_MODE_PAL&t;0
DECL|macro|FM2FB_MODE_NTSC
mdefine_line|#define FM2FB_MODE_NTSC&t;1
DECL|variable|__devinitdata
r_static
r_struct
id|fb_var_screeninfo
id|fb_var_modes
(braket
)braket
id|__devinitdata
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
DECL|variable|fm2fb_ops
r_static
r_struct
id|fb_ops
id|fm2fb_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|fb_setcolreg
op_assign
id|fm2fb_setcolreg
comma
dot
id|fb_blank
op_assign
id|fm2fb_blank
comma
dot
id|fb_fillrect
op_assign
id|cfb_fillrect
comma
dot
id|fb_copyarea
op_assign
id|cfb_copyarea
comma
dot
id|fb_imageblit
op_assign
id|cfb_imageblit
comma
dot
id|fb_cursor
op_assign
id|soft_cursor
comma
)brace
suffix:semicolon
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
id|info-&gt;cmap.len
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
(paren
(paren
id|u32
op_star
)paren
(paren
id|info-&gt;pseudo_palette
)paren
)paren
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Initialisation&n;     */
r_static
r_int
id|__devinit
id|fm2fb_probe
c_func
(paren
r_struct
id|zorro_dev
op_star
id|z
comma
r_const
r_struct
id|zorro_device_id
op_star
id|id
)paren
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_struct
id|zorro_device_id
id|fm2fb_devices
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
id|ZORRO_PROD_BSC_FRAMEMASTER_II
)brace
comma
(brace
id|ZORRO_PROD_HELFRICH_RAINBOW_II
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|fm2fb_driver
r_static
r_struct
id|zorro_driver
id|fm2fb_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fm2fb&quot;
comma
dot
id|id_table
op_assign
id|fm2fb_devices
comma
dot
id|probe
op_assign
id|fm2fb_probe
comma
)brace
suffix:semicolon
DECL|function|fm2fb_probe
r_static
r_int
id|__devinit
id|fm2fb_probe
c_func
(paren
r_struct
id|zorro_dev
op_star
id|z
comma
r_const
r_struct
id|zorro_device_id
op_star
id|id
)paren
(brace
r_struct
id|fb_info
op_star
id|info
suffix:semicolon
r_int
r_int
op_star
id|ptr
suffix:semicolon
r_int
id|is_fm
suffix:semicolon
r_int
id|x
comma
id|y
suffix:semicolon
id|is_fm
op_assign
id|z-&gt;id
op_eq
id|ZORRO_PROD_BSC_FRAMEMASTER_II
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|zorro_request_device
c_func
(paren
id|z
comma
l_string|&quot;fm2fb&quot;
)paren
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|info
op_assign
id|framebuffer_alloc
c_func
(paren
l_int|256
op_star
r_sizeof
(paren
id|u32
)paren
comma
op_amp
id|z-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
)paren
(brace
id|zorro_release_device
c_func
(paren
id|z
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fb_alloc_cmap
c_func
(paren
op_amp
id|info-&gt;cmap
comma
l_int|256
comma
l_int|0
)paren
OL
l_int|0
)paren
(brace
id|framebuffer_release
c_func
(paren
id|info
)paren
suffix:semicolon
id|zorro_release_device
c_func
(paren
id|z
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* assigning memory to kernel space */
id|fb_fix.smem_start
op_assign
id|zorro_resource_start
c_func
(paren
id|z
)paren
suffix:semicolon
id|info-&gt;screen_base
op_assign
id|ioremap
c_func
(paren
id|fb_fix.smem_start
comma
id|FRAMEMASTER_SIZE
)paren
suffix:semicolon
id|fb_fix.mmio_start
op_assign
id|fb_fix.smem_start
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
id|info-&gt;screen_base
op_plus
id|FRAMEMASTER_REG
)paren
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
multiline_comment|/* make EBU color bars on display */
id|ptr
op_assign
(paren
r_int
r_int
op_star
)paren
id|fb_fix.smem_start
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
id|info
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
id|info-&gt;fbops
op_assign
op_amp
id|fm2fb_ops
suffix:semicolon
id|info-&gt;var
op_assign
id|fb_var_modes
(braket
id|fm2fb_mode
)braket
suffix:semicolon
id|info-&gt;pseudo_palette
op_assign
id|info-&gt;par
suffix:semicolon
id|info-&gt;par
op_assign
l_int|NULL
suffix:semicolon
id|info-&gt;fix
op_assign
id|fb_fix
suffix:semicolon
id|info-&gt;flags
op_assign
id|FBINFO_DEFAULT
suffix:semicolon
r_if
c_cond
(paren
id|register_framebuffer
c_func
(paren
id|info
)paren
OL
l_int|0
)paren
(brace
id|fb_dealloc_cmap
c_func
(paren
op_amp
id|info-&gt;cmap
)paren
suffix:semicolon
id|framebuffer_release
c_func
(paren
id|info
)paren
suffix:semicolon
id|zorro_release_device
c_func
(paren
id|z
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;fb%d: %s frame buffer device&bslash;n&quot;
comma
id|info-&gt;node
comma
id|fb_fix.id
)paren
suffix:semicolon
r_return
l_int|0
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
DECL|function|fm2fb_init
r_int
id|__init
id|fm2fb_init
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|option
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|fb_get_options
c_func
(paren
l_string|&quot;fm2fb&quot;
comma
op_amp
id|option
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|fm2fb_setup
c_func
(paren
id|option
)paren
suffix:semicolon
r_return
id|zorro_register_driver
c_func
(paren
op_amp
id|fm2fb_driver
)paren
suffix:semicolon
)brace
DECL|variable|fm2fb_init
id|module_init
c_func
(paren
id|fm2fb_init
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
