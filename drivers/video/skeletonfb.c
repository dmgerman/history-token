multiline_comment|/*&n; * linux/drivers/video/skeletonfb.c -- Skeleton for a frame buffer device&n; *&n; *  Modified to new api Jan 2001 by James Simmons (jsimmons@transvirtual.com)&n; *&n; *  Created 28 Dec 1997 by Geert Uytterhoeven&n; *&n; *&n; *  I have started rewriting this driver as a example of the upcoming new API&n; *  The primary goal is to remove the console code from fbdev and place it&n; *  into fbcon.c. This reduces the code and makes writing a new fbdev driver&n; *  easy since the author doesn&squot;t need to worry about console internals. It&n; *  also allows the ability to run fbdev without a console/tty system on top &n; *  of it. &n; *&n; *  First the roles of struct fb_info and struct display have changed. Struct&n; *  display will go away. The way the the new framebuffer console code will&n; *  work is that it will act to translate data about the tty/console in &n; *  struct vc_data to data in a device independent way in struct fb_info. Then&n; *  various functions in struct fb_ops will be called to store the device &n; *  dependent state in the par field in struct fb_info and to change the &n; *  hardware to that state. This allows a very clean seperation of the fbdev&n; *  layer from the console layer. It also allows one to use fbdev on its own&n; *  which is a bounus for embedded devices. The reason this approach works is  &n; *  for each framebuffer device when used as a tty/console device is allocated&n; *  a set of virtual terminals to it. Only one virtual terminal can be active &n; *  per framebuffer device. We already have all the data we need in struct &n; *  vc_data so why store a bunch of colormaps and other fbdev specific data&n; *  per virtual terminal. &n; *&n; *  As you can see doing this makes the con parameter pretty much useless&n; *  for struct fb_ops functions, as it should be. Also having struct  &n; *  fb_var_screeninfo and other data in fb_info pretty much eliminates the &n; *  need for get_fix and get_var. Once all drivers use the fix, var, and cmap&n; *  fbcon can be written around these fields. This will also eliminate the&n; *  need to regenerate struct fb_var_screeninfo, struct fb_fix_screeninfo&n; *  struct fb_cmap every time get_var, get_fix, get_cmap functions are called&n; *  as many drivers do now. &n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/*&n;     *  This is just simple sample code.&n;     *&n;     *  No warranty that it actually compiles.&n;     *  Even less warranty that it actually works :-)&n;     */
multiline_comment|/*&n; *  If your driver supports multiple boards, you should make the  &n; *  below data types arrays, or allocate them dynamically (using kmalloc()). &n; */
multiline_comment|/* &n; * This structure defines the hardware state of the graphics card. Normally&n; * you place this in a header file in linux/include/video. This file usually&n; * also includes register information. That allows other driver subsystems&n; * and userland applications the ability to use the same header file to &n; * avoid duplicate work and easy porting of software. &n; */
r_struct
id|xxx_par
suffix:semicolon
multiline_comment|/*&n; * Here we define the default structs fb_fix_screeninfo and fb_var_screeninfo&n; * if we don&squot;t use modedb. If we do use modedb see xxxfb_init how to use it&n; * to get a fb_var_screeninfo. Otherwise define a default var as well. &n; */
DECL|variable|__initdata
r_static
r_struct
id|fb_fix_screeninfo
id|xxxfb_fix
id|__initdata
op_assign
(brace
dot
id|id
op_assign
l_string|&quot;FB&squot;s name&quot;
comma
dot
id|type
op_assign
id|FB_TYPE_PACKED_PIXELS
comma
dot
id|visual
op_assign
id|FB_VISUAL_PSEUDOCOLOR
comma
dot
id|xpanstep
op_assign
l_int|1
comma
dot
id|ypanstep
op_assign
l_int|1
comma
dot
id|ywrapstep
op_assign
l_int|1
comma
dot
id|accel
op_assign
id|FB_ACCEL_NONE
comma
)brace
suffix:semicolon
multiline_comment|/*&n;     * &t;Modern graphical hardware not only supports pipelines but some &n;     *  also support multiple monitors where each display can have its  &n;     *  its own unique data. In this case each display could be  &n;     *  represented by a seperate framebuffer device thus a seperate &n;     *  struct fb_info. Now the struct xxx_par represents the graphics&n;     *  hardware state thus only one exist per card. In this case the &n;     *  struct xxx_par for each graphics card would be shared between &n;     *  every struct fb_info that represents a framebuffer on that card. &n;     *  This allows when one display changes it video resolution (info-&gt;var) &n;     *  the other displays know instantly. Each display can always be&n;     *  aware of the entire hardware state that affects it because they share&n;     *  the same xxx_par struct. The other side of the coin is multiple&n;     *  graphics cards that pass data around until it is finally displayed&n;     *  on one monitor. Such examples are the voodoo 1 cards and high end&n;     *  NUMA graphics servers. For this case we have a bunch of pars, each&n;     *  one that represents a graphics state, that belong to one struct &n;     *  fb_info. Their you would want to have *par point to a array of device&n;     *  states and have each struct fb_ops function deal with all those &n;     *  states. I hope this covers every possible hardware design. If not&n;     *  feel free to send your ideas at jsimmons@users.sf.net &n;     */
multiline_comment|/*&n;     *  If your driver supports multiple boards or it supports multiple &n;     *  framebuffers, you should make these arrays, or allocate them &n;     *  dynamically (using kmalloc()). &n;     */
DECL|variable|info
r_static
r_struct
id|fb_info
id|info
suffix:semicolon
multiline_comment|/* &n;     * Each one represents the a state of the hardware. Most hardware have &n;     * just one hardware state. These here represent the default state(s). &n;     */
DECL|variable|current_par
r_static
r_struct
id|xxx_par
id|__initdata
id|current_par
suffix:semicolon
r_int
id|xxxfb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|xxxfb_setup
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/**&n; *      xxxfb_check_var - Optional function. Validates a var passed in. &n; *      @var: frame buffer variable screen structure&n; *      @info: frame buffer structure that represents a single frame buffer &n; *&n; *&t;Checks to see if the hardware supports the state requested by&n; *&t;var passed in. This function does not alter the hardware state!!! &n; *&t;This means the data stored in struct fb_info and struct xxx_par do &n; *      not change. This includes the var inside of struct fb_info. &n; *&t;Do NOT change these. This function can be called on its own if we&n; *&t;intent to only test a mode and not actually set it. The stuff in &n; *&t;modedb.c is a example of this. If the var passed in is slightly &n; *&t;off by what the hardware can support then we alter the var PASSED in&n; *&t;to what we can do. If the hardware doesn&squot;t support mode change &n; * &t;a -EINVAL will be returned by the upper layers. You don&squot;t need to &n; *&t;implement this function then.&n; *&n; *&t;Returns negative errno on error, or zero on success.&n; */
DECL|function|xxxfb_check_var
r_static
r_int
id|xxxfb_check_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_const
r_struct
id|xxx_par
op_star
id|par
op_assign
(paren
r_const
r_struct
id|xxx_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
multiline_comment|/* ... */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *      xxxfb_set_par - Optional function. Alters the hardware state.&n; *      @info: frame buffer structure that represents a single frame buffer&n; *&n; *&t;Using the fb_var_screeninfo in fb_info we set the resolution of the&n; *&t;this particular framebuffer. This function alters the par AND the&n; *&t;fb_fix_screeninfo stored in fb_info. It doesn&squot;t not alter var in &n; *&t;fb_info since we are using that data. This means we depend on the&n; *&t;data in var inside fb_info to be supported by the hardware. &n; *&t;xxxfb_check_var is always called before xxxfb_set_par to ensure this.&n; *&n; */
DECL|function|xxxfb_set_par
r_static
r_int
id|xxxfb_set_par
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|xxx_par
op_star
id|par
op_assign
(paren
r_struct
id|xxx_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
multiline_comment|/* ... */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *  &t;xxxfb_setcolreg - Optional function. Sets a color register.&n; *      @regno: boolean, 0 copy local, 1 get_user() function&n; *      @red: frame buffer colormap structure&n; *&t;@green: The green value which can be up to 16 bits wide &n; *&t;@blue:  The blue value which can be up to 16 bits wide.&n; *&t;@transp: If supported the alpha value which can be up to 16 bits wide.&t;&n; *      @info: frame buffer info structure&n; * &n; *  &t;Set a single color register. The values supplied have a 16 bit&n; *  &t;magnitude which needs to be scaled in this function for the hardware. &n; *&t;Things to take into consideration are how many color registers, if&n; *&t;any, are supported with the current color visual. With truecolor mode&n; *&t;no color palettes are supported. Here a psuedo palette is created &n; *&t;which we store the value in pseudo_palette in struct fb_info. For&n; *&t;pseudocolor mode we have a limited color palette. To deal with this&n; *&t;we can program what color is displayed for a particular pixel value.&n; *&t;DirectColor is similar in that we can program each color field. If&n; *&t;we have a static colormap we don&squot;t need to implement this function. &n; * &n; *&t;Returns negative errno on error, or zero on success.&n; */
DECL|function|xxxfb_setcolreg
r_static
r_int
id|xxxfb_setcolreg
c_func
(paren
r_int
id|regno
comma
r_int
id|red
comma
r_int
id|green
comma
r_int
id|blue
comma
r_int
id|transp
comma
r_const
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
op_ge
l_int|256
)paren
multiline_comment|/* no. of hw registers */
r_return
l_int|1
suffix:semicolon
multiline_comment|/*&n;     * Program hardware... do anything you want with transp&n;     */
multiline_comment|/* grayscale works only partially under directcolor */
r_if
c_cond
(paren
id|info-&gt;var.grayscale
)paren
(brace
multiline_comment|/* grayscale = 0.30*R + 0.59*G + 0.11*B */
id|red
op_assign
id|green
op_assign
id|blue
op_assign
(paren
id|red
op_star
l_int|77
op_plus
id|green
op_star
l_int|151
op_plus
id|blue
op_star
l_int|28
)paren
op_rshift
l_int|8
suffix:semicolon
)brace
multiline_comment|/* Directcolor:&n;     *   var-&gt;{color}.offset contains start of bitfield&n;     *   var-&gt;{color}.length contains length of bitfield&n;     *   {hardwarespecific} contains width of DAC&n;     *   cmap[X] is programmed to (X &lt;&lt; red.offset) | (X &lt;&lt; green.offset) | (X &lt;&lt; blue.offset)&n;     *   RAMDAC[X] is programmed to (red, green, blue)&n;     *&n;     * Pseudocolor:&n;     *    uses offset = 0 &amp;&amp; length = DAC register width.&n;     *    var-&gt;{color}.offset is 0&n;     *    var-&gt;{color}.length contains widht of DAC&n;     *    cmap is not used&n;     *    DAC[X] is programmed to (red, green, blue)&n;     * Truecolor:&n;     *    does not use RAMDAC (usually has 3 of them).&n;     *    var-&gt;{color}.offset contains start of bitfield&n;     *    var-&gt;{color}.length contains length of bitfield&n;     *    cmap is programmed to (red &lt;&lt; red.offset) | (green &lt;&lt; green.offset) |&n;     *                      (blue &lt;&lt; blue.offset) | (transp &lt;&lt; transp.offset)&n;     *    RAMDAC does not exist&n;     */
DECL|macro|CNVT_TOHW
mdefine_line|#define CNVT_TOHW(val,width) ((((val)&lt;&lt;(width))+0x7FFF-(val))&gt;&gt;16)
r_switch
c_cond
(paren
id|info-&gt;fix.visual
)paren
(brace
r_case
id|FB_VISUAL_TRUECOLOR
suffix:colon
r_case
id|FB_VISUAL_PSEUDOCOLOR
suffix:colon
id|red
op_assign
id|CNVT_TOHW
c_func
(paren
id|red
comma
id|info-&gt;var.red.length
)paren
suffix:semicolon
id|green
op_assign
id|CNVT_TOHW
c_func
(paren
id|green
comma
id|info-&gt;var.green.length
)paren
suffix:semicolon
id|blue
op_assign
id|CNVT_TOHW
c_func
(paren
id|blue
comma
id|info-&gt;var.blue.length
)paren
suffix:semicolon
id|transp
op_assign
id|CNVT_TOHW
c_func
(paren
id|transp
comma
id|info-&gt;var.transp.length
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FB_VISUAL_DIRECTCOLOR
suffix:colon
multiline_comment|/* example here assumes 8 bit DAC. Might be different &n;&t;&t;* for your hardware */
id|red
op_assign
id|CNVT_TOHW
c_func
(paren
id|red
comma
l_int|8
)paren
suffix:semicolon
id|green
op_assign
id|CNVT_TOHW
c_func
(paren
id|green
comma
l_int|8
)paren
suffix:semicolon
id|blue
op_assign
id|CNVT_TOHW
c_func
(paren
id|blue
comma
l_int|8
)paren
suffix:semicolon
multiline_comment|/* hey, there is bug in transp handling... */
id|transp
op_assign
id|CNVT_TOHW
c_func
(paren
id|transp
comma
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
DECL|macro|CNVT_TOHW
macro_line|#undef CNVT_TOHW
multiline_comment|/* Truecolor has hardware independent palette */
r_if
c_cond
(paren
id|info-&gt;fix.visual
op_eq
id|FB_VISUAL_TRUECOLOR
)paren
(brace
id|u32
id|v
suffix:semicolon
r_if
c_cond
(paren
id|regno
op_ge
l_int|16
)paren
r_return
l_int|1
suffix:semicolon
id|v
op_assign
(paren
id|red
op_lshift
id|info-&gt;var.red.offset
)paren
op_or
(paren
id|green
op_lshift
id|info-&gt;var.green.offset
)paren
op_or
(paren
id|blue
op_lshift
id|info-&gt;var.blue.offset
)paren
op_or
(paren
id|transp
op_lshift
id|info-&gt;var.transp.offset
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|info-&gt;var.bits_per_pixel
)paren
(brace
r_case
l_int|8
suffix:colon
multiline_comment|/* Yes some hand held devices have this. */
(paren
(paren
id|u8
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
id|v
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
(paren
(paren
id|u16
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
id|v
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|24
suffix:colon
r_case
l_int|32
suffix:colon
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
id|v
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ... */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *      xxxfb_pan_display - NOT a required function. Pans the display.&n; *      @var: frame buffer variable screen structure&n; *      @info: frame buffer structure that represents a single frame buffer&n; *&n; *&t;Pan (or wrap, depending on the `vmode&squot; field) the display using the&n; *  &t;`xoffset&squot; and `yoffset&squot; fields of the `var&squot; structure.&n; *  &t;If the values don&squot;t fit, return -EINVAL.&n; *&n; *      Returns negative errno on error, or zero on success.&n; *&n; */
DECL|function|xxxfb_pan_display
r_static
r_int
id|xxxfb_pan_display
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
r_const
r_struct
id|fb_info
op_star
id|info
)paren
(brace
multiline_comment|/* ... */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *      xxxfb_blank - NOT a required function. Blanks the display.&n; *      @blank_mode: the blank mode we want. &n; *      @info: frame buffer structure that represents a single frame buffer&n; *&n; *      Blank the screen if blank_mode != 0, else unblank. Return 0 if&n; *      blanking succeeded, != 0 if un-/blanking failed due to e.g. a &n; *      video mode which doesn&squot;t support it. Implements VESA suspend&n; *      and powerdown modes on hardware that supports disabling hsync/vsync:&n; *      blank_mode == 2: suspend vsync&n; *      blank_mode == 3: suspend hsync&n; *      blank_mode == 4: powerdown&n; *&n; *      Returns negative errno on error, or zero on success.&n; *&n; */
DECL|function|xxxfb_blank
r_static
r_int
id|xxxfb_blank
c_func
(paren
r_int
id|blank_mode
comma
r_const
r_struct
id|fb_info
op_star
id|info
)paren
(brace
multiline_comment|/* ... */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ------------ Accelerated Functions --------------------- */
multiline_comment|/*&n; * We provide our own functions if we have hardware acceleration&n; * or non packed pixel format layouts. If we have no hardware &n; * acceleration, we use a generic unaccelerated function. If using&n; * a pack pixel format just use the functions in cfb*.c. Each file &n; * has one of the three different accel functions we support. You   &n; * can use these functions as fallbacks if hardware unsupported&n; * action is requested. Also if you have non pack pixel modes and&n; * non accelerated cards you have to provide your own functions.&n; */
multiline_comment|/**&n; *      xxxfb_fillrect - REQUIRED function. Can use generic routines if &n; *&t;&t; &t; non acclerated hardware and packed pixel based.&n; *&t;&t;&t; Draws a rectangle on the screen.&t;&t;&n; *&n; *      @info: frame buffer structure that represents a single frame buffer&n; *&t;@x1: The x and y corrdinates of the upper left hand corner of the &n; *&t;@y1: area we want to draw to. &n; *&t;@width: How wide the rectangle is we want to draw.&n; *&t;@height: How tall the rectangle is we want to draw.&n; *&t;@color:&t;The color to fill in the rectangle with. &n; *&t;@rop: The rater operation. We can draw the rectangle with a COPY&n; *&t;      of XOR which provides erasing effect. &n; *&n; *&t;This drawing operation places/removes a retangle on the screen &n; *&t;depending on the rastering operation with the value of color which&n; *&t;is in the current color depth format.&n; */
DECL|function|xxxfb_fillrect
r_void
id|xxxfb_fillrect
c_func
(paren
r_struct
id|fb_info
op_star
id|p
comma
r_struct
id|fb_fillrect
op_star
id|region
)paren
(brace
)brace
multiline_comment|/**&n; *      xxxfb_copyarea - REQUIRED function. Can use generic routines if&n; *                       non acclerated hardware and packed pixel based.&n; *                       Copies on area of the screen to another area.&n; *&n; *      @info: frame buffer structure that represents a single frame buffer&n; *      @sx: The x and y corrdinates of the upper left hand corner of the&n; *      @sy: source area on the screen.&n; *      @width: How wide the rectangle is we want to copy.&n; *      @height: How tall the rectangle is we want to copy.&n; *      @dx: The x and y coordinates of the destination area on the screen.&n; *&n; *      This drawing operation copies a rectangular area from one area of the&n; *&t;screen to another area.&n; */
DECL|function|xxxfb_copyarea
r_void
id|xxxfb_copyarea
c_func
(paren
r_struct
id|fb_info
op_star
id|p
comma
r_struct
id|fb_copyarea
op_star
id|area
)paren
(brace
)brace
multiline_comment|/**&n; *      xxxfb_imageblit - REQUIRED function. Can use generic routines if&n; *                        non acclerated hardware and packed pixel based.&n; *                        Copies a image from system memory to the screen. &n; *&n; *      @info: frame buffer structure that represents a single frame buffer&n; *&t;@image:&t;structure defining the image.&n; *&n; *      This drawing operation draws a image on the screen. It can be a &n; *&t;mono image (needed for font handling) or a color image (needed for&n; *&t;tux). &n; */
DECL|function|xxxfb_imageblit
r_void
id|xxxfb_imageblit
c_func
(paren
r_struct
id|fb_info
op_star
id|p
comma
r_struct
id|fb_image
op_star
id|image
)paren
(brace
)brace
multiline_comment|/* ------------ Hardware Independent Functions ------------ */
multiline_comment|/*&n;     *  Initialization&n;     */
DECL|function|xxxfb_init
r_int
id|__init
id|xxxfb_init
c_func
(paren
r_void
)paren
(brace
r_int
id|cmap_len
comma
id|retval
suffix:semicolon
multiline_comment|/* &n;     * Here we set the screen_base to the vitrual memory address&n;     * for the framebuffer. Usually we obtain the resource address&n;     * from the bus layer and then translate it to virtual memory&n;     * space via ioremap. Consult ioport.h. &n;     */
id|info.screen_base
op_assign
id|framebuffer_virtual_memory
suffix:semicolon
id|info.node
op_assign
id|NODEV
suffix:semicolon
id|info.fbops
op_assign
op_amp
id|xxxfb_ops
suffix:semicolon
id|info.fix
op_assign
id|xxxfb_fix
suffix:semicolon
id|info.pseudo_palette
op_assign
id|pseudo_palette
suffix:semicolon
id|info.flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
id|info.par
op_assign
id|current_par
suffix:semicolon
multiline_comment|/* The following has to be set but in th efuture will go away */
id|strcpy
c_func
(paren
id|info.modename
comma
id|xxxfb_fix.id
)paren
suffix:semicolon
id|info.changevar
op_assign
l_int|NULL
suffix:semicolon
id|info.currcon
op_assign
op_minus
l_int|1
suffix:semicolon
id|info.disp
op_assign
op_amp
id|disp
suffix:semicolon
id|info.switch_con
op_assign
id|gen_switch
suffix:semicolon
id|info.updatevar
op_assign
id|gen_update_var
suffix:semicolon
multiline_comment|/*&n;     * This should give a reasonable default video mode. The following is&n;     * done when we can set a video mode. &n;     */
r_if
c_cond
(paren
op_logical_neg
id|mode_option
)paren
id|mode_option
op_assign
l_string|&quot;640x480@60&quot;
suffix:semicolon
id|retval
op_assign
id|fb_find_mode
c_func
(paren
op_amp
id|info.var
comma
op_amp
id|info
comma
id|mode_option
comma
l_int|NULL
comma
l_int|0
comma
l_int|NULL
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
op_logical_or
id|retval
op_eq
l_int|4
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* This has to been done !!! */
id|fb_alloc_cmap
c_func
(paren
op_amp
id|info.cmap
comma
id|cmap_len
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* &n;     * The following is done in the case of having hardware with a static &n;     * mode. If we are setting the mode ourselves we don&squot;t call this. &n;     */
id|info.var
op_assign
id|xxxfb_var
suffix:semicolon
r_if
c_cond
(paren
id|register_framebuffer
c_func
(paren
op_amp
id|info
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
id|KERN_INFO
l_string|&quot;fb%d: %s frame buffer device&bslash;n&quot;
comma
id|GET_FB_IDX
c_func
(paren
id|info.node
)paren
comma
id|info.fix.id
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Cleanup&n;     */
DECL|function|xxxfb_cleanup
r_static
r_void
id|__exit
id|xxxfb_cleanup
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;     *  If your driver supports multiple boards, you should unregister and&n;     *  clean up all instances.&n;     */
id|unregister_framebuffer
c_func
(paren
id|info
)paren
suffix:semicolon
multiline_comment|/* ... */
)brace
multiline_comment|/*&n;     *  Setup&n;     */
multiline_comment|/* &n; * Only necessary if your driver takes special options,&n; * otherwise we fall back on the generic fb_setup().&n; */
DECL|function|xxxfb_setup
r_int
id|__init
id|xxxfb_setup
c_func
(paren
r_char
op_star
id|options
)paren
(brace
multiline_comment|/* Parse user speficied options (`video=xxxfb:&squot;) */
)brace
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/*&n;     *  Frame buffer operations&n;     */
multiline_comment|/* If all you need is that - just don&squot;t define -&gt;fb_open */
DECL|function|xxxfb_open
r_static
r_int
id|xxxfb_open
c_func
(paren
r_const
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|user
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* If all you need is that - just don&squot;t define -&gt;fb_release */
DECL|function|xxxfb_release
r_static
r_int
id|xxxfb_release
c_func
(paren
r_const
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|user
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|xxxfb_ops
r_static
r_struct
id|fb_ops
id|xxxfb_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|fb_open
op_assign
id|xxxfb_open
comma
multiline_comment|/* only if you need it to do something */
dot
id|fb_release
op_assign
id|xxxfb_release
comma
multiline_comment|/* only if you need it to do something */
multiline_comment|/* Stuff to go away. Use generic functions for now */
dot
id|fb_set_var
op_assign
id|gen_set_var
comma
dot
id|fb_check_var
op_assign
id|xxxfb_check_var
comma
dot
id|fb_set_par
op_assign
id|xxxfb_set_par
comma
multiline_comment|/* optional */
dot
id|fb_setcolreg
op_assign
id|xxxfb_setcolreg
comma
dot
id|fb_blank
op_assign
id|xxxfb_blank
comma
multiline_comment|/* optional */
dot
id|fb_pan_display
op_assign
id|xxxfb_pan_display
comma
multiline_comment|/* optional */
dot
id|fb_fillrect
op_assign
id|xxxfb_fillrect
comma
dot
id|fb_copyarea
op_assign
id|xxxfb_copyarea
comma
dot
id|fb_imageblit
op_assign
id|xxxfb_imageblit
comma
dot
id|fb_ioctl
op_assign
id|xxxfb_ioctl
comma
multiline_comment|/* optional */
dot
id|fb_mmap
op_assign
id|xxxfb_mmap
comma
multiline_comment|/* optional */
)brace
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/*&n;     *  Modularization&n;     */
macro_line|#ifdef MODULE
DECL|variable|xxxfb_init
id|module_init
c_func
(paren
id|xxxfb_init
)paren
suffix:semicolon
macro_line|#endif 
DECL|variable|xxxfb_cleanup
id|module_exit
c_func
(paren
id|xxxfb_cleanup
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
