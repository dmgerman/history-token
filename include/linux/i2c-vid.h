multiline_comment|/*&n;    i2c-vid.h - Part of lm_sensors, Linux kernel modules for hardware&n;                monitoring&n;    Copyright (c) 2002 Mark D. Studebaker &lt;mdsxyz123@yahoo.com&gt;&n;    With assistance from Trent Piepho &lt;xyzzy@speakeasy.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
multiline_comment|/*&n;    This file contains common code for decoding VID pins.&n;    This file is #included in various chip drivers in this directory.&n;    As the user is unlikely to load more than one driver which&n;    includes this code we don&squot;t worry about the wasted space.&n;    Reference: VRM x.y DC-DC Converter Design Guidelines,&n;    available at http://developer.intel.com&n;*/
multiline_comment|/*&n;    Legal val values 00 - 1F.&n;    vrm is the Intel VRM document version.&n;    Note: vrm version is scaled by 10 and the return value is scaled by 1000&n;    to avoid floating point in the kernel.&n;*/
DECL|macro|DEFAULT_VRM
mdefine_line|#define DEFAULT_VRM&t;82
DECL|function|vid_from_reg
r_static
r_inline
r_int
id|vid_from_reg
c_func
(paren
r_int
id|val
comma
r_int
id|vrm
)paren
(brace
r_switch
c_cond
(paren
id|vrm
)paren
(brace
r_case
l_int|91
suffix:colon
multiline_comment|/* VRM 9.1 */
r_case
l_int|90
suffix:colon
multiline_comment|/* VRM 9.0 */
r_return
id|val
op_eq
l_int|0x1f
ques
c_cond
l_int|0
suffix:colon
l_int|1850
op_minus
id|val
op_star
l_int|25
suffix:semicolon
r_case
l_int|85
suffix:colon
multiline_comment|/* VRM 8.5 */
r_return
(paren
id|val
op_amp
l_int|0x10
ques
c_cond
l_int|25
suffix:colon
l_int|0
)paren
op_plus
(paren
(paren
id|val
op_amp
l_int|0x0f
)paren
OG
l_int|0x04
ques
c_cond
l_int|2050
suffix:colon
l_int|1250
)paren
op_minus
(paren
(paren
id|val
op_amp
l_int|0x0f
)paren
op_star
l_int|50
)paren
suffix:semicolon
r_case
l_int|84
suffix:colon
multiline_comment|/* VRM 8.4 */
id|val
op_and_assign
l_int|0x0f
suffix:semicolon
multiline_comment|/* fall through */
r_default
suffix:colon
multiline_comment|/* VRM 8.2 */
r_return
id|val
op_eq
l_int|0x1f
ques
c_cond
l_int|0
suffix:colon
id|val
op_amp
l_int|0x10
ques
c_cond
l_int|5100
op_minus
(paren
id|val
)paren
op_star
l_int|100
suffix:colon
l_int|2050
op_minus
(paren
id|val
)paren
op_star
l_int|50
suffix:semicolon
)brace
)brace
eof
