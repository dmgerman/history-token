multiline_comment|/*&n; *  linux/drivers/video/modedb.c -- Standard video mode database management&n; *&n; *&t;Copyright (C) 1999 Geert Uytterhoeven&n; *&n; *&t;2001 - Documented with DocBook&n; *&t;- Brad Douglas &lt;brad@neruo.com&gt;&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;video/fbcon.h&gt;
DECL|macro|DEBUG
macro_line|#undef DEBUG
DECL|macro|name_matches
mdefine_line|#define name_matches(v, s, l) &bslash;&n;    ((v).name &amp;&amp; !strncmp((s), (v).name, (l)) &amp;&amp; strlen((v).name) == (l))
DECL|macro|res_matches
mdefine_line|#define res_matches(v, x, y) &bslash;&n;    ((v).xres == (x) &amp;&amp; (v).yres == (y))
macro_line|#ifdef DEBUG
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(fmt, args...)&t;printk(KERN_DEBUG &quot;%s: &quot; fmt, __FUNCTION__ , ## args)
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(fmt, args...)
macro_line|#endif
DECL|variable|global_mode_option
r_const
r_char
op_star
id|global_mode_option
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;     *  Standard video mode definitions (taken from XFree86)&n;     */
DECL|macro|DEFAULT_MODEDB_INDEX
mdefine_line|#define DEFAULT_MODEDB_INDEX&t;0
DECL|variable|__initdata
r_static
r_const
r_struct
id|fb_videomode
id|modedb
(braket
)braket
id|__initdata
op_assign
(brace
(brace
multiline_comment|/* 640x400 @ 70 Hz, 31.5 kHz hsync */
l_int|NULL
comma
l_int|70
comma
l_int|640
comma
l_int|400
comma
l_int|39721
comma
l_int|40
comma
l_int|24
comma
l_int|39
comma
l_int|9
comma
l_int|96
comma
l_int|2
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 640x480 @ 60 Hz, 31.5 kHz hsync */
l_int|NULL
comma
l_int|60
comma
l_int|640
comma
l_int|480
comma
l_int|39721
comma
l_int|40
comma
l_int|24
comma
l_int|32
comma
l_int|11
comma
l_int|96
comma
l_int|2
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 800x600 @ 56 Hz, 35.15 kHz hsync */
l_int|NULL
comma
l_int|56
comma
l_int|800
comma
l_int|600
comma
l_int|27777
comma
l_int|128
comma
l_int|24
comma
l_int|22
comma
l_int|1
comma
l_int|72
comma
l_int|2
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1024x768 @ 87 Hz interlaced, 35.5 kHz hsync */
l_int|NULL
comma
l_int|87
comma
l_int|1024
comma
l_int|768
comma
l_int|22271
comma
l_int|56
comma
l_int|24
comma
l_int|33
comma
l_int|8
comma
l_int|160
comma
l_int|8
comma
l_int|0
comma
id|FB_VMODE_INTERLACED
)brace
comma
(brace
multiline_comment|/* 640x400 @ 85 Hz, 37.86 kHz hsync */
l_int|NULL
comma
l_int|85
comma
l_int|640
comma
l_int|400
comma
l_int|31746
comma
l_int|96
comma
l_int|32
comma
l_int|41
comma
l_int|1
comma
l_int|64
comma
l_int|3
comma
id|FB_SYNC_VERT_HIGH_ACT
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 640x480 @ 72 Hz, 36.5 kHz hsync */
l_int|NULL
comma
l_int|72
comma
l_int|640
comma
l_int|480
comma
l_int|31746
comma
l_int|144
comma
l_int|40
comma
l_int|30
comma
l_int|8
comma
l_int|40
comma
l_int|3
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 640x480 @ 75 Hz, 37.50 kHz hsync */
l_int|NULL
comma
l_int|75
comma
l_int|640
comma
l_int|480
comma
l_int|31746
comma
l_int|120
comma
l_int|16
comma
l_int|16
comma
l_int|1
comma
l_int|64
comma
l_int|3
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 800x600 @ 60 Hz, 37.8 kHz hsync */
l_int|NULL
comma
l_int|60
comma
l_int|800
comma
l_int|600
comma
l_int|25000
comma
l_int|88
comma
l_int|40
comma
l_int|23
comma
l_int|1
comma
l_int|128
comma
l_int|4
comma
id|FB_SYNC_HOR_HIGH_ACT
op_or
id|FB_SYNC_VERT_HIGH_ACT
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 640x480 @ 85 Hz, 43.27 kHz hsync */
l_int|NULL
comma
l_int|85
comma
l_int|640
comma
l_int|480
comma
l_int|27777
comma
l_int|80
comma
l_int|56
comma
l_int|25
comma
l_int|1
comma
l_int|56
comma
l_int|3
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1152x864 @ 89 Hz interlaced, 44 kHz hsync */
l_int|NULL
comma
l_int|69
comma
l_int|1152
comma
l_int|864
comma
l_int|15384
comma
l_int|96
comma
l_int|16
comma
l_int|110
comma
l_int|1
comma
l_int|216
comma
l_int|10
comma
l_int|0
comma
id|FB_VMODE_INTERLACED
)brace
comma
(brace
multiline_comment|/* 800x600 @ 72 Hz, 48.0 kHz hsync */
l_int|NULL
comma
l_int|72
comma
l_int|800
comma
l_int|600
comma
l_int|20000
comma
l_int|64
comma
l_int|56
comma
l_int|23
comma
l_int|37
comma
l_int|120
comma
l_int|6
comma
id|FB_SYNC_HOR_HIGH_ACT
op_or
id|FB_SYNC_VERT_HIGH_ACT
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1024x768 @ 60 Hz, 48.4 kHz hsync */
l_int|NULL
comma
l_int|60
comma
l_int|1024
comma
l_int|768
comma
l_int|15384
comma
l_int|168
comma
l_int|8
comma
l_int|29
comma
l_int|3
comma
l_int|144
comma
l_int|6
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 640x480 @ 100 Hz, 53.01 kHz hsync */
l_int|NULL
comma
l_int|100
comma
l_int|640
comma
l_int|480
comma
l_int|21834
comma
l_int|96
comma
l_int|32
comma
l_int|36
comma
l_int|8
comma
l_int|96
comma
l_int|6
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1152x864 @ 60 Hz, 53.5 kHz hsync */
l_int|NULL
comma
l_int|60
comma
l_int|1152
comma
l_int|864
comma
l_int|11123
comma
l_int|208
comma
l_int|64
comma
l_int|16
comma
l_int|4
comma
l_int|256
comma
l_int|8
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 800x600 @ 85 Hz, 55.84 kHz hsync */
l_int|NULL
comma
l_int|85
comma
l_int|800
comma
l_int|600
comma
l_int|16460
comma
l_int|160
comma
l_int|64
comma
l_int|36
comma
l_int|16
comma
l_int|64
comma
l_int|5
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1024x768 @ 70 Hz, 56.5 kHz hsync */
l_int|NULL
comma
l_int|70
comma
l_int|1024
comma
l_int|768
comma
l_int|13333
comma
l_int|144
comma
l_int|24
comma
l_int|29
comma
l_int|3
comma
l_int|136
comma
l_int|6
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1280x1024 @ 87 Hz interlaced, 51 kHz hsync */
l_int|NULL
comma
l_int|87
comma
l_int|1280
comma
l_int|1024
comma
l_int|12500
comma
l_int|56
comma
l_int|16
comma
l_int|128
comma
l_int|1
comma
l_int|216
comma
l_int|12
comma
l_int|0
comma
id|FB_VMODE_INTERLACED
)brace
comma
(brace
multiline_comment|/* 800x600 @ 100 Hz, 64.02 kHz hsync */
l_int|NULL
comma
l_int|100
comma
l_int|800
comma
l_int|600
comma
l_int|14357
comma
l_int|160
comma
l_int|64
comma
l_int|30
comma
l_int|4
comma
l_int|64
comma
l_int|6
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1024x768 @ 76 Hz, 62.5 kHz hsync */
l_int|NULL
comma
l_int|76
comma
l_int|1024
comma
l_int|768
comma
l_int|11764
comma
l_int|208
comma
l_int|8
comma
l_int|36
comma
l_int|16
comma
l_int|120
comma
l_int|3
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1152x864 @ 70 Hz, 62.4 kHz hsync */
l_int|NULL
comma
l_int|70
comma
l_int|1152
comma
l_int|864
comma
l_int|10869
comma
l_int|106
comma
l_int|56
comma
l_int|20
comma
l_int|1
comma
l_int|160
comma
l_int|10
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1280x1024 @ 61 Hz, 64.2 kHz hsync */
l_int|NULL
comma
l_int|61
comma
l_int|1280
comma
l_int|1024
comma
l_int|9090
comma
l_int|200
comma
l_int|48
comma
l_int|26
comma
l_int|1
comma
l_int|184
comma
l_int|3
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1400x1050 @ 60Hz, 63.9 kHz hsync */
l_int|NULL
comma
l_int|68
comma
l_int|1400
comma
l_int|1050
comma
l_int|9259
comma
l_int|136
comma
l_int|40
comma
l_int|13
comma
l_int|1
comma
l_int|112
comma
l_int|3
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1024x768 @ 85 Hz, 70.24 kHz hsync */
l_int|NULL
comma
l_int|85
comma
l_int|1024
comma
l_int|768
comma
l_int|10111
comma
l_int|192
comma
l_int|32
comma
l_int|34
comma
l_int|14
comma
l_int|160
comma
l_int|6
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1152x864 @ 78 Hz, 70.8 kHz hsync */
l_int|NULL
comma
l_int|78
comma
l_int|1152
comma
l_int|864
comma
l_int|9090
comma
l_int|228
comma
l_int|88
comma
l_int|32
comma
l_int|0
comma
l_int|84
comma
l_int|12
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1280x1024 @ 70 Hz, 74.59 kHz hsync */
l_int|NULL
comma
l_int|70
comma
l_int|1280
comma
l_int|1024
comma
l_int|7905
comma
l_int|224
comma
l_int|32
comma
l_int|28
comma
l_int|8
comma
l_int|160
comma
l_int|8
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1600x1200 @ 60Hz, 75.00 kHz hsync */
l_int|NULL
comma
l_int|60
comma
l_int|1600
comma
l_int|1200
comma
l_int|6172
comma
l_int|304
comma
l_int|64
comma
l_int|46
comma
l_int|1
comma
l_int|192
comma
l_int|3
comma
id|FB_SYNC_HOR_HIGH_ACT
op_or
id|FB_SYNC_VERT_HIGH_ACT
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1152x864 @ 84 Hz, 76.0 kHz hsync */
l_int|NULL
comma
l_int|84
comma
l_int|1152
comma
l_int|864
comma
l_int|7407
comma
l_int|184
comma
l_int|312
comma
l_int|32
comma
l_int|0
comma
l_int|128
comma
l_int|12
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1280x1024 @ 74 Hz, 78.85 kHz hsync */
l_int|NULL
comma
l_int|74
comma
l_int|1280
comma
l_int|1024
comma
l_int|7407
comma
l_int|256
comma
l_int|32
comma
l_int|34
comma
l_int|3
comma
l_int|144
comma
l_int|3
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1024x768 @ 100Hz, 80.21 kHz hsync */
l_int|NULL
comma
l_int|100
comma
l_int|1024
comma
l_int|768
comma
l_int|8658
comma
l_int|192
comma
l_int|32
comma
l_int|21
comma
l_int|3
comma
l_int|192
comma
l_int|10
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1280x1024 @ 76 Hz, 81.13 kHz hsync */
l_int|NULL
comma
l_int|76
comma
l_int|1280
comma
l_int|1024
comma
l_int|7407
comma
l_int|248
comma
l_int|32
comma
l_int|34
comma
l_int|3
comma
l_int|104
comma
l_int|3
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1600x1200 @ 70 Hz, 87.50 kHz hsync */
l_int|NULL
comma
l_int|70
comma
l_int|1600
comma
l_int|1200
comma
l_int|5291
comma
l_int|304
comma
l_int|64
comma
l_int|46
comma
l_int|1
comma
l_int|192
comma
l_int|3
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1152x864 @ 100 Hz, 89.62 kHz hsync */
l_int|NULL
comma
l_int|100
comma
l_int|1152
comma
l_int|864
comma
l_int|7264
comma
l_int|224
comma
l_int|32
comma
l_int|17
comma
l_int|2
comma
l_int|128
comma
l_int|19
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1280x1024 @ 85 Hz, 91.15 kHz hsync */
l_int|NULL
comma
l_int|85
comma
l_int|1280
comma
l_int|1024
comma
l_int|6349
comma
l_int|224
comma
l_int|64
comma
l_int|44
comma
l_int|1
comma
l_int|160
comma
l_int|3
comma
id|FB_SYNC_HOR_HIGH_ACT
op_or
id|FB_SYNC_VERT_HIGH_ACT
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1600x1200 @ 75 Hz, 93.75 kHz hsync */
l_int|NULL
comma
l_int|75
comma
l_int|1600
comma
l_int|1200
comma
l_int|4938
comma
l_int|304
comma
l_int|64
comma
l_int|46
comma
l_int|1
comma
l_int|192
comma
l_int|3
comma
id|FB_SYNC_HOR_HIGH_ACT
op_or
id|FB_SYNC_VERT_HIGH_ACT
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1600x1200 @ 85 Hz, 105.77 kHz hsync */
l_int|NULL
comma
l_int|85
comma
l_int|1600
comma
l_int|1200
comma
l_int|4545
comma
l_int|272
comma
l_int|16
comma
l_int|37
comma
l_int|4
comma
l_int|192
comma
l_int|3
comma
id|FB_SYNC_HOR_HIGH_ACT
op_or
id|FB_SYNC_VERT_HIGH_ACT
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1280x1024 @ 100 Hz, 107.16 kHz hsync */
l_int|NULL
comma
l_int|100
comma
l_int|1280
comma
l_int|1024
comma
l_int|5502
comma
l_int|256
comma
l_int|32
comma
l_int|26
comma
l_int|7
comma
l_int|128
comma
l_int|15
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1800x1440 @ 64Hz, 96.15 kHz hsync  */
l_int|NULL
comma
l_int|64
comma
l_int|1800
comma
l_int|1440
comma
l_int|4347
comma
l_int|304
comma
l_int|96
comma
l_int|46
comma
l_int|1
comma
l_int|192
comma
l_int|3
comma
id|FB_SYNC_HOR_HIGH_ACT
op_or
id|FB_SYNC_VERT_HIGH_ACT
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 1800x1440 @ 70Hz, 104.52 kHz hsync  */
l_int|NULL
comma
l_int|70
comma
l_int|1800
comma
l_int|1440
comma
l_int|4000
comma
l_int|304
comma
l_int|96
comma
l_int|46
comma
l_int|1
comma
l_int|192
comma
l_int|3
comma
id|FB_SYNC_HOR_HIGH_ACT
op_or
id|FB_SYNC_VERT_HIGH_ACT
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 512x384 @ 78 Hz, 31.50 kHz hsync */
l_int|NULL
comma
l_int|78
comma
l_int|512
comma
l_int|384
comma
l_int|49603
comma
l_int|48
comma
l_int|16
comma
l_int|16
comma
l_int|1
comma
l_int|64
comma
l_int|3
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 512x384 @ 85 Hz, 34.38 kHz hsync */
l_int|NULL
comma
l_int|85
comma
l_int|512
comma
l_int|384
comma
l_int|45454
comma
l_int|48
comma
l_int|16
comma
l_int|16
comma
l_int|1
comma
l_int|64
comma
l_int|3
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
comma
(brace
multiline_comment|/* 320x200 @ 70 Hz, 31.5 kHz hsync, 8:5 aspect ratio */
l_int|NULL
comma
l_int|70
comma
l_int|320
comma
l_int|200
comma
l_int|79440
comma
l_int|16
comma
l_int|16
comma
l_int|20
comma
l_int|4
comma
l_int|48
comma
l_int|1
comma
l_int|0
comma
id|FB_VMODE_DOUBLE
)brace
comma
(brace
multiline_comment|/* 320x240 @ 60 Hz, 31.5 kHz hsync, 4:3 aspect ratio */
l_int|NULL
comma
l_int|60
comma
l_int|320
comma
l_int|240
comma
l_int|79440
comma
l_int|16
comma
l_int|16
comma
l_int|16
comma
l_int|5
comma
l_int|48
comma
l_int|1
comma
l_int|0
comma
id|FB_VMODE_DOUBLE
)brace
comma
(brace
multiline_comment|/* 320x240 @ 72 Hz, 36.5 kHz hsync */
l_int|NULL
comma
l_int|72
comma
l_int|320
comma
l_int|240
comma
l_int|63492
comma
l_int|16
comma
l_int|16
comma
l_int|16
comma
l_int|4
comma
l_int|48
comma
l_int|2
comma
l_int|0
comma
id|FB_VMODE_DOUBLE
)brace
comma
(brace
multiline_comment|/* 400x300 @ 56 Hz, 35.2 kHz hsync, 4:3 aspect ratio */
l_int|NULL
comma
l_int|56
comma
l_int|400
comma
l_int|300
comma
l_int|55555
comma
l_int|64
comma
l_int|16
comma
l_int|10
comma
l_int|1
comma
l_int|32
comma
l_int|1
comma
l_int|0
comma
id|FB_VMODE_DOUBLE
)brace
comma
(brace
multiline_comment|/* 400x300 @ 60 Hz, 37.8 kHz hsync */
l_int|NULL
comma
l_int|60
comma
l_int|400
comma
l_int|300
comma
l_int|50000
comma
l_int|48
comma
l_int|16
comma
l_int|11
comma
l_int|1
comma
l_int|64
comma
l_int|2
comma
l_int|0
comma
id|FB_VMODE_DOUBLE
)brace
comma
(brace
multiline_comment|/* 400x300 @ 72 Hz, 48.0 kHz hsync */
l_int|NULL
comma
l_int|72
comma
l_int|400
comma
l_int|300
comma
l_int|40000
comma
l_int|32
comma
l_int|24
comma
l_int|11
comma
l_int|19
comma
l_int|64
comma
l_int|3
comma
l_int|0
comma
id|FB_VMODE_DOUBLE
)brace
comma
(brace
multiline_comment|/* 480x300 @ 56 Hz, 35.2 kHz hsync, 8:5 aspect ratio */
l_int|NULL
comma
l_int|56
comma
l_int|480
comma
l_int|300
comma
l_int|46176
comma
l_int|80
comma
l_int|16
comma
l_int|10
comma
l_int|1
comma
l_int|40
comma
l_int|1
comma
l_int|0
comma
id|FB_VMODE_DOUBLE
)brace
comma
(brace
multiline_comment|/* 480x300 @ 60 Hz, 37.8 kHz hsync */
l_int|NULL
comma
l_int|60
comma
l_int|480
comma
l_int|300
comma
l_int|41858
comma
l_int|56
comma
l_int|16
comma
l_int|11
comma
l_int|1
comma
l_int|80
comma
l_int|2
comma
l_int|0
comma
id|FB_VMODE_DOUBLE
)brace
comma
(brace
multiline_comment|/* 480x300 @ 63 Hz, 39.6 kHz hsync */
l_int|NULL
comma
l_int|63
comma
l_int|480
comma
l_int|300
comma
l_int|40000
comma
l_int|56
comma
l_int|16
comma
l_int|11
comma
l_int|1
comma
l_int|80
comma
l_int|2
comma
l_int|0
comma
id|FB_VMODE_DOUBLE
)brace
comma
(brace
multiline_comment|/* 480x300 @ 72 Hz, 48.0 kHz hsync */
l_int|NULL
comma
l_int|72
comma
l_int|480
comma
l_int|300
comma
l_int|33386
comma
l_int|40
comma
l_int|24
comma
l_int|11
comma
l_int|19
comma
l_int|80
comma
l_int|3
comma
l_int|0
comma
id|FB_VMODE_DOUBLE
)brace
comma
)brace
suffix:semicolon
DECL|function|my_atoi
r_static
r_int
id|__init
id|my_atoi
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_int
id|val
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
id|name
op_increment
)paren
(brace
r_switch
c_cond
(paren
op_star
id|name
)paren
(brace
r_case
l_char|&squot;0&squot;
dot
dot
dot
l_char|&squot;9&squot;
suffix:colon
id|val
op_assign
l_int|10
op_star
id|val
op_plus
(paren
op_star
id|name
op_minus
l_char|&squot;0&squot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
id|val
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/**&n; *&t;__fb_try_mode - test a video mode&n; *&t;@var: frame buffer user defined part of display&n; *&t;@info: frame buffer info structure&n; *&t;@mode: frame buffer video mode structure&n; *&t;@bpp: color depth in bits per pixel&n; *&n; *&t;Tries a video mode to test it&squot;s validity for device @info.&n; *&n; *&t;Returns 1 on success.&n; *&n; */
DECL|function|__fb_try_mode
r_int
id|__fb_try_mode
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
comma
r_const
r_struct
id|fb_videomode
op_star
id|mode
comma
r_int
r_int
id|bpp
)paren
(brace
r_int
id|err
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;Trying mode %s %dx%d-%d@%d&bslash;n&quot;
comma
id|mode-&gt;name
ques
c_cond
id|mode-&gt;name
suffix:colon
l_string|&quot;noname&quot;
comma
id|mode-&gt;xres
comma
id|mode-&gt;yres
comma
id|bpp
comma
id|mode-&gt;refresh
)paren
suffix:semicolon
id|var-&gt;xres
op_assign
id|mode-&gt;xres
suffix:semicolon
id|var-&gt;yres
op_assign
id|mode-&gt;yres
suffix:semicolon
id|var-&gt;xres_virtual
op_assign
id|mode-&gt;xres
suffix:semicolon
id|var-&gt;yres_virtual
op_assign
id|mode-&gt;yres
suffix:semicolon
id|var-&gt;xoffset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;yoffset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;bits_per_pixel
op_assign
id|bpp
suffix:semicolon
id|var-&gt;activate
op_or_assign
id|FB_ACTIVATE_TEST
suffix:semicolon
id|var-&gt;pixclock
op_assign
id|mode-&gt;pixclock
suffix:semicolon
id|var-&gt;left_margin
op_assign
id|mode-&gt;left_margin
suffix:semicolon
id|var-&gt;right_margin
op_assign
id|mode-&gt;right_margin
suffix:semicolon
id|var-&gt;upper_margin
op_assign
id|mode-&gt;upper_margin
suffix:semicolon
id|var-&gt;lower_margin
op_assign
id|mode-&gt;lower_margin
suffix:semicolon
id|var-&gt;hsync_len
op_assign
id|mode-&gt;hsync_len
suffix:semicolon
id|var-&gt;vsync_len
op_assign
id|mode-&gt;vsync_len
suffix:semicolon
id|var-&gt;sync
op_assign
id|mode-&gt;sync
suffix:semicolon
id|var-&gt;vmode
op_assign
id|mode-&gt;vmode
suffix:semicolon
id|err
op_assign
id|info-&gt;fbops
op_member_access_from_pointer
id|fb_set_var
c_func
(paren
id|var
comma
id|PROC_CONSOLE
c_func
(paren
id|info
)paren
comma
id|info
)paren
suffix:semicolon
id|var-&gt;activate
op_and_assign
op_complement
id|FB_ACTIVATE_TEST
suffix:semicolon
id|gen_set_disp
c_func
(paren
id|PROC_CONSOLE
c_func
(paren
id|info
)paren
comma
id|info
)paren
suffix:semicolon
r_return
op_logical_neg
id|err
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;fb_find_mode - finds a valid video mode&n; *&t;@var: frame buffer user defined part of display&n; *&t;@info: frame buffer info structure&n; *&t;@mode_option: string video mode to find&n; *&t;@db: video mode database&n; *&t;@dbsize: size of @db&n; *&t;@default_mode: default video mode to fall back to&n; *&t;@default_bpp: default color depth in bits per pixel&n; *&n; *&t;Finds a suitable video mode, starting with the specified mode&n; *&t;in @mode_option with fallback to @default_mode.  If&n; *&t;@default_mode fails, all modes in the video mode database will&n; *&t;be tried.&n; *&n; *&t;Valid mode specifiers for @mode_option:&n; *&n; *&t;&lt;xres&gt;x&lt;yres&gt;[-&lt;bpp&gt;][@&lt;refresh&gt;] or&n; *&t;&lt;name&gt;[-&lt;bpp&gt;][@&lt;refresh&gt;]&n; *&n; *&t;with &lt;xres&gt;, &lt;yres&gt;, &lt;bpp&gt; and &lt;refresh&gt; decimal numbers and&n; *&t;&lt;name&gt; a string.&n; *&n; *&t;NOTE: The passed struct @var is _not_ cleared!  This allows you&n; *&t;to supply values for e.g. the grayscale and accel_flags fields.&n; *&n; *&t;Returns zero for failure, 1 if using specified @mode_option,&n; *&t;2 if using specified @mode_option with an ignored refresh rate,&n; *&t;3 if default mode is used, 4 if fall back to any valid mode.&n; *&n; */
DECL|function|fb_find_mode
r_int
id|__init
id|fb_find_mode
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
comma
r_const
r_char
op_star
id|mode_option
comma
r_const
r_struct
id|fb_videomode
op_star
id|db
comma
r_int
r_int
id|dbsize
comma
r_const
r_struct
id|fb_videomode
op_star
id|default_mode
comma
r_int
r_int
id|default_bpp
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
multiline_comment|/* Set up defaults */
r_if
c_cond
(paren
op_logical_neg
id|db
)paren
(brace
id|db
op_assign
id|modedb
suffix:semicolon
id|dbsize
op_assign
r_sizeof
(paren
id|modedb
)paren
op_div
r_sizeof
(paren
op_star
id|modedb
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|default_mode
)paren
id|default_mode
op_assign
op_amp
id|modedb
(braket
id|DEFAULT_MODEDB_INDEX
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|default_bpp
)paren
id|default_bpp
op_assign
l_int|8
suffix:semicolon
multiline_comment|/* Did the user specify a video mode? */
r_if
c_cond
(paren
id|mode_option
op_logical_or
(paren
id|mode_option
op_assign
id|global_mode_option
)paren
)paren
(brace
r_const
r_char
op_star
id|name
op_assign
id|mode_option
suffix:semicolon
r_int
r_int
id|namelen
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
r_int
id|res_specified
op_assign
l_int|0
comma
id|bpp_specified
op_assign
l_int|0
comma
id|refresh_specified
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|xres
op_assign
l_int|0
comma
id|yres
op_assign
l_int|0
comma
id|bpp
op_assign
id|default_bpp
comma
id|refresh
op_assign
l_int|0
suffix:semicolon
r_int
id|yres_specified
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|namelen
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_switch
c_cond
(paren
id|name
(braket
id|i
)braket
)paren
(brace
r_case
l_char|&squot;@&squot;
suffix:colon
id|namelen
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|refresh_specified
op_logical_and
op_logical_neg
id|bpp_specified
op_logical_and
op_logical_neg
id|yres_specified
)paren
(brace
id|refresh
op_assign
id|my_atoi
c_func
(paren
op_amp
id|name
(braket
id|i
op_plus
l_int|1
)braket
)paren
suffix:semicolon
id|refresh_specified
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_goto
id|done
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;-&squot;
suffix:colon
id|namelen
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bpp_specified
op_logical_and
op_logical_neg
id|yres_specified
)paren
(brace
id|bpp
op_assign
id|my_atoi
c_func
(paren
op_amp
id|name
(braket
id|i
op_plus
l_int|1
)braket
)paren
suffix:semicolon
id|bpp_specified
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_goto
id|done
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;x&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|yres_specified
)paren
(brace
id|yres
op_assign
id|my_atoi
c_func
(paren
op_amp
id|name
(braket
id|i
op_plus
l_int|1
)braket
)paren
suffix:semicolon
id|yres_specified
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_goto
id|done
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;0&squot;
dot
dot
dot
l_char|&squot;9&squot;
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|done
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|i
OL
l_int|0
op_logical_and
id|yres_specified
)paren
(brace
id|xres
op_assign
id|my_atoi
c_func
(paren
id|name
)paren
suffix:semicolon
id|res_specified
op_assign
l_int|1
suffix:semicolon
)brace
id|done
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
id|refresh_specified
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;Trying specified video mode%s&bslash;n&quot;
comma
id|i
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot; (ignoring refresh rate)&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|dbsize
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
(paren
id|name_matches
c_func
(paren
id|db
(braket
id|j
)braket
comma
id|name
comma
id|namelen
)paren
op_logical_or
(paren
id|res_specified
op_logical_and
id|res_matches
c_func
(paren
id|db
(braket
id|j
)braket
comma
id|xres
comma
id|yres
)paren
)paren
)paren
op_logical_and
(paren
op_logical_neg
id|i
op_logical_or
id|db
(braket
id|j
)braket
dot
id|refresh
op_eq
id|refresh
)paren
op_logical_and
id|__fb_try_mode
c_func
(paren
id|var
comma
id|info
comma
op_amp
id|db
(braket
id|j
)braket
comma
id|bpp
)paren
)paren
r_return
l_int|2
op_minus
id|i
suffix:semicolon
)brace
)brace
id|DPRINTK
c_func
(paren
l_string|&quot;Trying default video mode&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|__fb_try_mode
c_func
(paren
id|var
comma
id|info
comma
id|default_mode
comma
id|default_bpp
)paren
)paren
r_return
l_int|3
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;Trying all modes&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dbsize
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|__fb_try_mode
c_func
(paren
id|var
comma
id|info
comma
op_amp
id|db
(braket
id|i
)braket
comma
id|default_bpp
)paren
)paren
r_return
l_int|4
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;No valid mode found&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|__fb_try_mode
id|EXPORT_SYMBOL
c_func
(paren
id|__fb_try_mode
)paren
suffix:semicolon
eof
