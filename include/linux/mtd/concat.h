multiline_comment|/*&n; * MTD device concatenation layer definitions&n; *&n; * (C) 2002 Robert Kaiser &lt;rkaiser@sysgo.de&gt;&n; *&n; * This code is GPL&n; *&n; * $Id: concat.h,v 1.1 2002/03/08 16:34:36 rkaiser Exp $&n; */
macro_line|#ifndef MTD_CONCAT_H
DECL|macro|MTD_CONCAT_H
mdefine_line|#define MTD_CONCAT_H
r_struct
id|mtd_info
op_star
id|mtd_concat_create
c_func
(paren
r_struct
id|mtd_info
op_star
id|subdev
(braket
)braket
comma
multiline_comment|/* subdevices to concatenate */
r_int
id|num_devs
comma
multiline_comment|/* number of subdevices      */
r_char
op_star
id|name
)paren
suffix:semicolon
multiline_comment|/* name for the new device   */
r_void
id|mtd_concat_destroy
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
macro_line|#endif
eof
