multiline_comment|/*&n; * Zoran zr36057/zr36067 PCI controller driver, for the&n; * Pinnacle/Miro DC10/DC10+/DC30/DC30+, Iomega Buz, Linux&n; * Media Labs LML33/LML33R10.&n; *&n; * This part handles card-specific data and detection&n; * &n; * Copyright (C) 2000 Serguei Miridonov &lt;mirsev@cicese.mx&gt;&n; *&n; * Currently maintained by:&n; *   Ronald Bultje    &lt;rbultje@ronald.bitfreak.net&gt;&n; *   Laurent Pinchart &lt;laurent.pinchart@skynet.be&gt;&n; *   Mailinglist      &lt;mjpeg-users@lists.sf.net&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __ZORAN_CARD_H__
DECL|macro|__ZORAN_CARD_H__
mdefine_line|#define __ZORAN_CARD_H__
multiline_comment|/* Anybody who uses more than four? */
DECL|macro|BUZ_MAX
mdefine_line|#define BUZ_MAX 4
r_extern
r_int
id|zoran_num
suffix:semicolon
r_extern
r_struct
id|zoran
id|zoran
(braket
id|BUZ_MAX
)braket
suffix:semicolon
r_extern
r_struct
id|video_device
id|zoran_template
suffix:semicolon
r_extern
r_int
id|zoran_check_jpg_settings
c_func
(paren
r_struct
id|zoran
op_star
id|zr
comma
r_struct
id|zoran_jpg_settings
op_star
id|settings
)paren
suffix:semicolon
r_extern
r_void
id|zoran_open_init_params
c_func
(paren
r_struct
id|zoran
op_star
id|zr
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* __ZORAN_CARD_H__ */
eof
