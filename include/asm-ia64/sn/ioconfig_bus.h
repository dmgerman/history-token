multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2003 Silicon Graphics, Inc.  All Rights Reserved.&n; */
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
