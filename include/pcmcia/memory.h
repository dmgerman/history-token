multiline_comment|/*&n; * memory.h 1.7 2000/06/12 21:55:40&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License. &n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in which&n; * case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use&n; * your version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n; */
macro_line|#ifndef _LINUX_MEMORY_H
DECL|macro|_LINUX_MEMORY_H
mdefine_line|#define _LINUX_MEMORY_H
DECL|struct|erase_info_t
r_typedef
r_struct
id|erase_info_t
(brace
DECL|member|Offset
id|u_long
id|Offset
suffix:semicolon
DECL|member|Size
id|u_long
id|Size
suffix:semicolon
DECL|typedef|erase_info_t
)brace
id|erase_info_t
suffix:semicolon
DECL|macro|MEMGETINFO
mdefine_line|#define MEMGETINFO&t;&t;_IOR(&squot;M&squot;, 1, region_info_t)
DECL|macro|MEMERASE
mdefine_line|#define MEMERASE&t;&t;_IOW(&squot;M&squot;, 2, erase_info_t)
macro_line|#endif /* _LINUX_MEMORY_H */
eof
