multiline_comment|/*&n; * controlfb_hw.h: Constants of all sorts for controlfb&n; *&n; * Copyright (C) 1998 Daniel Jacobowitz &lt;dan@debian.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * Based on an awful lot of code, including:&n; *&n; * control.c: Console support for PowerMac &quot;control&quot; display adaptor.&n; * Copyright (C) 1996 Paul Mackerras.&n; *&n; * The so far unpublished platinumfb.c&n; * Copyright (C) 1998 Jon Howell&n; */
multiline_comment|/*&n; * Structure of the registers for the RADACAL colormap device.&n; */
DECL|struct|cmap_regs
r_struct
id|cmap_regs
(brace
DECL|member|addr
r_int
r_char
id|addr
suffix:semicolon
multiline_comment|/* index for both cmap and misc registers */
DECL|member|pad1
r_char
id|pad1
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|crsr
r_int
r_char
id|crsr
suffix:semicolon
multiline_comment|/* cursor palette */
DECL|member|pad2
r_char
id|pad2
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|dat
r_int
r_char
id|dat
suffix:semicolon
multiline_comment|/* RADACAL misc register data */
DECL|member|pad3
r_char
id|pad3
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|lut
r_int
r_char
id|lut
suffix:semicolon
multiline_comment|/* cmap data */
DECL|member|pad4
r_char
id|pad4
(braket
l_int|15
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Structure of the registers for the &quot;control&quot; display adaptor.&n; */
DECL|macro|PAD
mdefine_line|#define PAD(x)&t;char x[12]
DECL|struct|preg
r_struct
id|preg
(brace
multiline_comment|/* padded register */
DECL|member|r
r_int
id|r
suffix:semicolon
DECL|member|pad
r_char
id|pad
(braket
l_int|12
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|control_regs
r_struct
id|control_regs
(brace
DECL|member|vcount
r_struct
id|preg
id|vcount
suffix:semicolon
multiline_comment|/* vertical counter */
multiline_comment|/* Vertical parameters are in units of 1/2 scan line */
DECL|member|vswin
r_struct
id|preg
id|vswin
suffix:semicolon
multiline_comment|/* between vsblank and vssync */
DECL|member|vsblank
r_struct
id|preg
id|vsblank
suffix:semicolon
multiline_comment|/* vert start blank */
DECL|member|veblank
r_struct
id|preg
id|veblank
suffix:semicolon
multiline_comment|/* vert end blank (display start) */
DECL|member|vewin
r_struct
id|preg
id|vewin
suffix:semicolon
multiline_comment|/* between vesync and veblank */
DECL|member|vesync
r_struct
id|preg
id|vesync
suffix:semicolon
multiline_comment|/* vert end sync */
DECL|member|vssync
r_struct
id|preg
id|vssync
suffix:semicolon
multiline_comment|/* vert start sync */
DECL|member|vperiod
r_struct
id|preg
id|vperiod
suffix:semicolon
multiline_comment|/* vert period */
DECL|member|piped
r_struct
id|preg
id|piped
suffix:semicolon
multiline_comment|/* pipe delay hardware cursor */
multiline_comment|/* Horizontal params are in units of 2 pixels */
DECL|member|hperiod
r_struct
id|preg
id|hperiod
suffix:semicolon
multiline_comment|/* horiz period - 2 */
DECL|member|hsblank
r_struct
id|preg
id|hsblank
suffix:semicolon
multiline_comment|/* horiz start blank */
DECL|member|heblank
r_struct
id|preg
id|heblank
suffix:semicolon
multiline_comment|/* horiz end blank */
DECL|member|hesync
r_struct
id|preg
id|hesync
suffix:semicolon
multiline_comment|/* horiz end sync */
DECL|member|hssync
r_struct
id|preg
id|hssync
suffix:semicolon
multiline_comment|/* horiz start sync */
DECL|member|heq
r_struct
id|preg
id|heq
suffix:semicolon
multiline_comment|/* half horiz sync len */
DECL|member|hlfln
r_struct
id|preg
id|hlfln
suffix:semicolon
multiline_comment|/* half horiz period */
DECL|member|hserr
r_struct
id|preg
id|hserr
suffix:semicolon
multiline_comment|/* horiz period - horiz sync len */
DECL|member|cnttst
r_struct
id|preg
id|cnttst
suffix:semicolon
DECL|member|ctrl
r_struct
id|preg
id|ctrl
suffix:semicolon
multiline_comment|/* display control */
DECL|member|start_addr
r_struct
id|preg
id|start_addr
suffix:semicolon
multiline_comment|/* start address: 5 lsbs zero */
DECL|member|pitch
r_struct
id|preg
id|pitch
suffix:semicolon
multiline_comment|/* addrs diff between scan lines */
DECL|member|mon_sense
r_struct
id|preg
id|mon_sense
suffix:semicolon
multiline_comment|/* monitor sense bits */
DECL|member|vram_attr
r_struct
id|preg
id|vram_attr
suffix:semicolon
multiline_comment|/* enable vram banks */
DECL|member|mode
r_struct
id|preg
id|mode
suffix:semicolon
DECL|member|rfrcnt
r_struct
id|preg
id|rfrcnt
suffix:semicolon
multiline_comment|/* refresh count */
DECL|member|intr_ena
r_struct
id|preg
id|intr_ena
suffix:semicolon
multiline_comment|/* interrupt enable */
DECL|member|intr_stat
r_struct
id|preg
id|intr_stat
suffix:semicolon
multiline_comment|/* interrupt status */
DECL|member|res
r_struct
id|preg
id|res
(braket
l_int|5
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|control_regints
r_struct
id|control_regints
(brace
multiline_comment|/* Vertical parameters are in units of 1/2 scan line */
DECL|member|vswin
r_int
id|vswin
suffix:semicolon
multiline_comment|/* between vsblank and vssync */
DECL|member|vsblank
r_int
id|vsblank
suffix:semicolon
multiline_comment|/* vert start blank */
DECL|member|veblank
r_int
id|veblank
suffix:semicolon
multiline_comment|/* vert end blank (display start) */
DECL|member|vewin
r_int
id|vewin
suffix:semicolon
multiline_comment|/* between vesync and veblank */
DECL|member|vesync
r_int
id|vesync
suffix:semicolon
multiline_comment|/* vert end sync */
DECL|member|vssync
r_int
id|vssync
suffix:semicolon
multiline_comment|/* vert start sync */
DECL|member|vperiod
r_int
id|vperiod
suffix:semicolon
multiline_comment|/* vert period */
DECL|member|piped
r_int
id|piped
suffix:semicolon
multiline_comment|/* pipe delay hardware cursor */
multiline_comment|/* Horizontal params are in units of 2 pixels */
multiline_comment|/* Except, apparently, for hres &gt; 1024 (or == 1280?) */
DECL|member|hperiod
r_int
id|hperiod
suffix:semicolon
multiline_comment|/* horiz period - 2 */
DECL|member|hsblank
r_int
id|hsblank
suffix:semicolon
multiline_comment|/* horiz start blank */
DECL|member|heblank
r_int
id|heblank
suffix:semicolon
multiline_comment|/* horiz end blank */
DECL|member|hesync
r_int
id|hesync
suffix:semicolon
multiline_comment|/* horiz end sync */
DECL|member|hssync
r_int
id|hssync
suffix:semicolon
multiline_comment|/* horiz start sync */
DECL|member|heq
r_int
id|heq
suffix:semicolon
multiline_comment|/* half horiz sync len */
DECL|member|hlfln
r_int
id|hlfln
suffix:semicolon
multiline_comment|/* half horiz period */
DECL|member|hserr
r_int
id|hserr
suffix:semicolon
multiline_comment|/* horiz period - horiz sync len */
)brace
suffix:semicolon
multiline_comment|/*&n; * Dot clock rate is&n; * 3.9064MHz * 2**clock_params[2] * clock_params[1] / clock_params[0].&n; */
DECL|struct|control_regvals
r_struct
id|control_regvals
(brace
DECL|member|regs
r_int
id|regs
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* for vswin .. hserr */
DECL|member|mode
r_int
r_char
id|mode
suffix:semicolon
DECL|member|radacal_ctrl
r_int
r_char
id|radacal_ctrl
suffix:semicolon
DECL|member|clock_params
r_int
r_char
id|clock_params
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CTRLFB_OFF
mdefine_line|#define CTRLFB_OFF 16&t;/* position of pixel 0 in frame buffer */
multiline_comment|/*&n; * Best cmode supported by control&n; */
DECL|struct|max_cmodes
r_struct
id|max_cmodes
(brace
DECL|member|m
r_int
id|m
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0: 2MB vram, 1: 4MB vram */
)brace
suffix:semicolon
multiline_comment|/*&n; * Video modes supported by macmodes.c&n; */
DECL|variable|control_mac_modes
r_static
r_struct
id|max_cmodes
id|control_mac_modes
(braket
)braket
op_assign
(brace
(brace
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
)brace
comma
multiline_comment|/* 512x384, 60Hz interlaced (NTSC) */
(brace
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
)brace
comma
multiline_comment|/* 512x384, 60Hz */
(brace
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
)brace
comma
multiline_comment|/* 640x480, 50Hz interlaced (PAL) */
(brace
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
)brace
comma
multiline_comment|/* 640x480, 60Hz interlaced (NTSC) */
(brace
(brace
l_int|2
comma
l_int|2
)brace
)brace
comma
multiline_comment|/* 640x480, 60Hz (VGA) */
(brace
(brace
l_int|2
comma
l_int|2
)brace
)brace
comma
multiline_comment|/* 640x480, 67Hz */
(brace
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
)brace
comma
multiline_comment|/* 640x870, 75Hz (portrait) */
(brace
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
)brace
comma
multiline_comment|/* 768x576, 50Hz (PAL full frame) */
(brace
(brace
l_int|2
comma
l_int|2
)brace
)brace
comma
multiline_comment|/* 800x600, 56Hz */
(brace
(brace
l_int|2
comma
l_int|2
)brace
)brace
comma
multiline_comment|/* 800x600, 60Hz */
(brace
(brace
l_int|2
comma
l_int|2
)brace
)brace
comma
multiline_comment|/* 800x600, 72Hz */
(brace
(brace
l_int|2
comma
l_int|2
)brace
)brace
comma
multiline_comment|/* 800x600, 75Hz */
(brace
(brace
l_int|1
comma
l_int|2
)brace
)brace
comma
multiline_comment|/* 832x624, 75Hz */
(brace
(brace
l_int|1
comma
l_int|2
)brace
)brace
comma
multiline_comment|/* 1024x768, 60Hz */
(brace
(brace
l_int|1
comma
l_int|2
)brace
)brace
comma
multiline_comment|/* 1024x768, 70Hz (or 72Hz?) */
(brace
(brace
l_int|1
comma
l_int|2
)brace
)brace
comma
multiline_comment|/* 1024x768, 75Hz (VESA) */
(brace
(brace
l_int|1
comma
l_int|2
)brace
)brace
comma
multiline_comment|/* 1024x768, 75Hz */
(brace
(brace
l_int|1
comma
l_int|2
)brace
)brace
comma
multiline_comment|/* 1152x870, 75Hz */
(brace
(brace
l_int|0
comma
l_int|1
)brace
)brace
comma
multiline_comment|/* 1280x960, 75Hz */
(brace
(brace
l_int|0
comma
l_int|1
)brace
)brace
comma
multiline_comment|/* 1280x1024, 75Hz */
)brace
suffix:semicolon
eof
