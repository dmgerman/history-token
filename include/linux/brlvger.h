multiline_comment|/*&n; *      Tieman Voyager braille display USB driver.&n; *&n; *      Copyright 2001-2002 Stephane Dalton &lt;sdalton@videotron.ca&gt;&n; *                      and St&#xfffd;phane Doyon  &lt;s.doyon@videotron.ca&gt;&n; *            Maintained by St&#xfffd;phane Doyon  &lt;s.doyon@videotron.ca&gt;.&n; */
multiline_comment|/*&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_BRLVGER_H
DECL|macro|_LINUX_BRLVGER_H
mdefine_line|#define _LINUX_BRLVGER_H
multiline_comment|/* Ioctl request codes */
DECL|macro|BRLVGER_GET_INFO
mdefine_line|#define BRLVGER_GET_INFO&t;0
DECL|macro|BRLVGER_DISPLAY_ON
mdefine_line|#define BRLVGER_DISPLAY_ON&t;2
DECL|macro|BRLVGER_DISPLAY_OFF
mdefine_line|#define BRLVGER_DISPLAY_OFF&t;3
DECL|macro|BRLVGER_BUZZ
mdefine_line|#define BRLVGER_BUZZ&t;&t;4
multiline_comment|/* Number of supported devices, and range of covered minors */
DECL|macro|MAX_NR_BRLVGER_DEVS
mdefine_line|#define MAX_NR_BRLVGER_DEVS&t;2
multiline_comment|/* Base minor for the char devices */
DECL|macro|BRLVGER_MINOR
mdefine_line|#define BRLVGER_MINOR&t;&t;128
multiline_comment|/* Size of some fields */
DECL|macro|BRLVGER_HWVER_SIZE
mdefine_line|#define BRLVGER_HWVER_SIZE&t;2
DECL|macro|BRLVGER_FWVER_SIZE
mdefine_line|#define BRLVGER_FWVER_SIZE&t;200 /* arbitrary, a long string */
DECL|macro|BRLVGER_SERIAL_BIN_SIZE
mdefine_line|#define BRLVGER_SERIAL_BIN_SIZE&t;8
DECL|macro|BRLVGER_SERIAL_SIZE
mdefine_line|#define BRLVGER_SERIAL_SIZE&t;((2*BRLVGER_SERIAL_BIN_SIZE)+1)
DECL|struct|brlvger_info
r_struct
id|brlvger_info
(brace
DECL|member|driver_version
id|__u8
id|driver_version
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|driver_banner
id|__u8
id|driver_banner
(braket
l_int|200
)braket
suffix:semicolon
DECL|member|display_length
id|__u32
id|display_length
suffix:semicolon
multiline_comment|/* All other char[] fields are strings except this one.&n;&t;   Hardware version: first byte is major, second byte is minor. */
DECL|member|hwver
id|__u8
id|hwver
(braket
id|BRLVGER_HWVER_SIZE
)braket
suffix:semicolon
DECL|member|fwver
id|__u8
id|fwver
(braket
id|BRLVGER_FWVER_SIZE
)braket
suffix:semicolon
DECL|member|serialnum
id|__u8
id|serialnum
(braket
id|BRLVGER_SERIAL_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
