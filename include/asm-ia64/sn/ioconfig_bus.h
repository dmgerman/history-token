multiline_comment|/*&n; * Copyright (c) 2003 Silicon Graphics, Inc.  All Rights Reserved.&n; * &n; * This program is free software; you can redistribute it and/or modify it &n; * under the terms of version 2 of the GNU General Public License &n; * as published by the Free Software Foundation.&n; * &n; * This program is distributed in the hope that it would be useful, but &n; * WITHOUT ANY WARRANTY; without even the implied warranty of &n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. &n; * &n; * Further, this software is distributed without any warranty that it is &n; * free of the rightful claim of any third person regarding infringement &n; * or the like.  Any license provided herein, whether implied or &n; * otherwise, applies only to this software file.  Patent licenses, if &n; * any, provided herein do not apply to combinations of this program with &n; * other software, or any other product whatsoever.&n; * &n; * You should have received a copy of the GNU General Public &n; * License along with this program; if not, write the Free Software &n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; * &n; * Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pkwy, &n; * Mountain View, CA  94043, or:&n; * &n; * http://www.sgi.com &n; * &n; * For further information regarding this notice, see: &n; * &n; * http://oss.sgi.com/projects/GenInfo/NoticeExplan&n; */
DECL|macro|IOCONFIG_PCIBUS
mdefine_line|#define IOCONFIG_PCIBUS &quot;/boot/efi/ioconfig_pcibus&quot;
DECL|macro|POUND_CHAR
mdefine_line|#define POUND_CHAR                   &squot;#&squot;
DECL|macro|MAX_LINE_LEN
mdefine_line|#define MAX_LINE_LEN&t;128
DECL|macro|MAXPATHLEN
mdefine_line|#define MAXPATHLEN&t;128
DECL|struct|ioconfig_parm
r_struct
id|ioconfig_parm
(brace
DECL|member|ioconfig_activated
r_int
r_int
id|ioconfig_activated
suffix:semicolon
DECL|member|number
r_int
r_int
id|number
suffix:semicolon
DECL|member|buffer
r_void
op_star
id|buffer
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ascii_moduleid
r_struct
id|ascii_moduleid
(brace
DECL|member|io_moduleid
r_int
r_char
id|io_moduleid
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* pci path name */
)brace
suffix:semicolon
eof
