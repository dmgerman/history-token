multiline_comment|/* &n; * Motion Eye video4linux driver for Sony Vaio PictureBook&n; *&n; * Copyright (C) 2001 Stelian Pop &lt;stelian.pop@fr.alcove.com&gt;, Alc&#xfffd;ve&n; *&n; * Copyright (C) 2000 Andrew Tridgell &lt;tridge@valinux.com&gt;&n; *&n; * Earlier work by Werner Almesberger, Paul `Rusty&squot; Russell and Paul Mackerras.&n; * &n; * Some parts borrowed from various video4linux drivers, especially&n; * bttv-driver.c and zoran.c, see original files for credits.&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _MEYE_H_
DECL|macro|_MEYE_H_
mdefine_line|#define _MEYE_H_
multiline_comment|/****************************************************************************/
multiline_comment|/* Private API for handling mjpeg capture / playback.                       */
multiline_comment|/****************************************************************************/
DECL|struct|meye_params
r_struct
id|meye_params
(brace
DECL|member|subsample
r_int
r_char
id|subsample
suffix:semicolon
DECL|member|quality
r_int
r_char
id|quality
suffix:semicolon
DECL|member|sharpness
r_int
r_char
id|sharpness
suffix:semicolon
DECL|member|agc
r_int
r_char
id|agc
suffix:semicolon
DECL|member|picture
r_int
r_char
id|picture
suffix:semicolon
DECL|member|framerate
r_int
r_char
id|framerate
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* query the extended parameters */
DECL|macro|MEYEIOC_G_PARAMS
mdefine_line|#define MEYEIOC_G_PARAMS&t;_IOR (&squot;v&squot;, BASE_VIDIOCPRIVATE+0, struct meye_params)
multiline_comment|/* set the extended parameters */
DECL|macro|MEYEIOC_S_PARAMS
mdefine_line|#define MEYEIOC_S_PARAMS&t;_IOW (&squot;v&squot;, BASE_VIDIOCPRIVATE+1, struct meye_params)
multiline_comment|/* queue a buffer for mjpeg capture */
DECL|macro|MEYEIOC_QBUF_CAPT
mdefine_line|#define MEYEIOC_QBUF_CAPT&t;_IOW (&squot;v&squot;, BASE_VIDIOCPRIVATE+2, int)
multiline_comment|/* sync a previously queued mjpeg buffer */
DECL|macro|MEYEIOC_SYNC
mdefine_line|#define MEYEIOC_SYNC&t;&t;_IOWR(&squot;v&squot;, BASE_VIDIOCPRIVATE+3, int)
multiline_comment|/* get a still uncompressed snapshot */
DECL|macro|MEYEIOC_STILLCAPT
mdefine_line|#define MEYEIOC_STILLCAPT&t;_IO  (&squot;v&squot;, BASE_VIDIOCPRIVATE+4)
multiline_comment|/* get a jpeg compressed snapshot */
DECL|macro|MEYEIOC_STILLJCAPT
mdefine_line|#define MEYEIOC_STILLJCAPT&t;_IOR (&squot;v&squot;, BASE_VIDIOCPRIVATE+5, int)
macro_line|#endif
eof
