multiline_comment|/* Linux driver for Philips webcam&n;   (C) 2004      Luc Saillard (luc@saillard.org)&n;&n;   NOTE: this version of pwc is an unofficial (modified) release of pwc &amp; pcwx&n;   driver and thus may have bugs that are not present in the original version.&n;   Please send bug reports and support requests to &lt;luc@saillard.org&gt;.&n;   The decompression routines have been implemented by reverse-engineering the&n;   Nemosoft binary pwcx module. Caveat emptor.&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n;&n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
multiline_comment|/* Entries for the Kiara (730/740/750) camera */
macro_line|#ifndef PWC_KIARA_H
DECL|macro|PWC_KIARA_H
mdefine_line|#define PWC_KIARA_H
macro_line|#include &quot;pwc-ioctl.h&quot;
DECL|struct|Kiara_table_entry
r_struct
id|Kiara_table_entry
(brace
DECL|member|alternate
r_char
id|alternate
suffix:semicolon
multiline_comment|/* USB alternate interface */
DECL|member|packetsize
r_int
r_int
id|packetsize
suffix:semicolon
multiline_comment|/* Normal packet size */
DECL|member|bandlength
r_int
r_int
id|bandlength
suffix:semicolon
multiline_comment|/* Bandlength when decompressing */
DECL|member|mode
r_int
r_char
id|mode
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* precomputed mode settings for cam */
)brace
suffix:semicolon
r_const
r_extern
r_struct
id|Kiara_table_entry
id|Kiara_table
(braket
id|PSZ_MAX
)braket
(braket
l_int|6
)braket
(braket
l_int|4
)braket
suffix:semicolon
r_const
r_extern
r_int
r_int
id|KiaraRomTable
(braket
l_int|8
)braket
(braket
l_int|2
)braket
(braket
l_int|16
)braket
(braket
l_int|8
)braket
suffix:semicolon
macro_line|#endif
eof
