multiline_comment|/* Linux driver for Philips webcam&n;   (C) 2004      Luc Saillard (luc@saillard.org)&n;&n;   NOTE: this version of pwc is an unofficial (modified) release of pwc &amp; pcwx&n;   driver and thus may have bugs that are not present in the original version.&n;   Please send bug reports and support requests to &lt;luc@saillard.org&gt;.&n;   The decompression routines have been implemented by reverse-engineering the&n;   Nemosoft binary pwcx module. Caveat emptor.&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n;&n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
macro_line|#ifndef PWC_DEC1_H
DECL|macro|PWC_DEC1_H
mdefine_line|#define PWC_DEC1_H
r_void
id|pwc_dec1_init
c_func
(paren
r_int
id|type
comma
r_int
id|release
comma
r_void
op_star
id|buffer
comma
r_void
op_star
id|private_data
)paren
suffix:semicolon
r_void
id|pwc_dec1_exit
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
