multiline_comment|/*&n; * ftl.h 1.8 2000/06/12 21:55:40&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License. &n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU Public License version 2 (the &quot;GPL&quot;), in which&n; * case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use&n; * your version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n; */
macro_line|#ifndef _LINUX_FTL_H
DECL|macro|_LINUX_FTL_H
mdefine_line|#define _LINUX_FTL_H
DECL|struct|erase_unit_header_t
r_typedef
r_struct
id|erase_unit_header_t
(brace
DECL|member|LinkTargetTuple
id|u_char
id|LinkTargetTuple
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|DataOrgTuple
id|u_char
id|DataOrgTuple
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|NumTransferUnits
id|u_char
id|NumTransferUnits
suffix:semicolon
DECL|member|EraseCount
id|u_int
id|EraseCount
suffix:semicolon
DECL|member|LogicalEUN
id|u_short
id|LogicalEUN
suffix:semicolon
DECL|member|BlockSize
id|u_char
id|BlockSize
suffix:semicolon
DECL|member|EraseUnitSize
id|u_char
id|EraseUnitSize
suffix:semicolon
DECL|member|FirstPhysicalEUN
id|u_short
id|FirstPhysicalEUN
suffix:semicolon
DECL|member|NumEraseUnits
id|u_short
id|NumEraseUnits
suffix:semicolon
DECL|member|FormattedSize
id|u_int
id|FormattedSize
suffix:semicolon
DECL|member|FirstVMAddress
id|u_int
id|FirstVMAddress
suffix:semicolon
DECL|member|NumVMPages
id|u_short
id|NumVMPages
suffix:semicolon
DECL|member|Flags
id|u_char
id|Flags
suffix:semicolon
DECL|member|Code
id|u_char
id|Code
suffix:semicolon
DECL|member|SerialNumber
id|u_int
id|SerialNumber
suffix:semicolon
DECL|member|AltEUHOffset
id|u_int
id|AltEUHOffset
suffix:semicolon
DECL|member|BAMOffset
id|u_int
id|BAMOffset
suffix:semicolon
DECL|member|Reserved
id|u_char
id|Reserved
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|EndTuple
id|u_char
id|EndTuple
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|erase_unit_header_t
)brace
id|erase_unit_header_t
suffix:semicolon
multiline_comment|/* Flags in erase_unit_header_t */
DECL|macro|HIDDEN_AREA
mdefine_line|#define HIDDEN_AREA&t;&t;0x01
DECL|macro|REVERSE_POLARITY
mdefine_line|#define REVERSE_POLARITY&t;0x02
DECL|macro|DOUBLE_BAI
mdefine_line|#define DOUBLE_BAI&t;&t;0x04
multiline_comment|/* Definitions for block allocation information */
DECL|macro|BLOCK_FREE
mdefine_line|#define BLOCK_FREE(b)&t;&t;((b) == 0xffffffff)
DECL|macro|BLOCK_DELETED
mdefine_line|#define BLOCK_DELETED(b)&t;(((b) == 0) || ((b) == 0xfffffffe))
DECL|macro|BLOCK_TYPE
mdefine_line|#define BLOCK_TYPE(b)&t;&t;((b) &amp; 0x7f)
DECL|macro|BLOCK_ADDRESS
mdefine_line|#define BLOCK_ADDRESS(b)&t;((b) &amp; ~0x7f)
DECL|macro|BLOCK_NUMBER
mdefine_line|#define BLOCK_NUMBER(b)&t;&t;((b) &gt;&gt; 9)
DECL|macro|BLOCK_CONTROL
mdefine_line|#define BLOCK_CONTROL&t;&t;0x30
DECL|macro|BLOCK_DATA
mdefine_line|#define BLOCK_DATA&t;&t;0x40
DECL|macro|BLOCK_REPLACEMENT
mdefine_line|#define BLOCK_REPLACEMENT&t;0x60
DECL|macro|BLOCK_BAD
mdefine_line|#define BLOCK_BAD&t;&t;0x70
macro_line|#endif /* _LINUX_FTL_H */
eof
