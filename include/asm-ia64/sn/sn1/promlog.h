multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef&t;_ASM_SN_SN1_PROMLOG_H
DECL|macro|_ASM_SN_SN1_PROMLOG_H
mdefine_line|#define&t;_ASM_SN_SN1_PROMLOG_H
macro_line|#include &lt;asm/sn/fprom.h&gt;
DECL|macro|PROMLOG_MAGIC
mdefine_line|#define PROMLOG_MAGIC&t;&t;&t;0x504c4f49
DECL|macro|PROMLOG_VERSION
mdefine_line|#define PROMLOG_VERSION&t;&t;&t;1
DECL|macro|PROMLOG_OFFSET_MAGIC
mdefine_line|#define PROMLOG_OFFSET_MAGIC&t;&t;0x10
DECL|macro|PROMLOG_OFFSET_VERSION
mdefine_line|#define PROMLOG_OFFSET_VERSION&t;&t;0x14
DECL|macro|PROMLOG_OFFSET_SEQUENCE
mdefine_line|#define PROMLOG_OFFSET_SEQUENCE&t;&t;0x18
DECL|macro|PROMLOG_OFFSET_ENTRY0
mdefine_line|#define PROMLOG_OFFSET_ENTRY0&t;&t;0x100
DECL|macro|PROMLOG_ERROR_NONE
mdefine_line|#define PROMLOG_ERROR_NONE&t;&t;0
DECL|macro|PROMLOG_ERROR_PROM
mdefine_line|#define PROMLOG_ERROR_PROM&t;       -1
DECL|macro|PROMLOG_ERROR_MAGIC
mdefine_line|#define PROMLOG_ERROR_MAGIC&t;       -2
DECL|macro|PROMLOG_ERROR_CORRUPT
mdefine_line|#define PROMLOG_ERROR_CORRUPT&t;       -3
DECL|macro|PROMLOG_ERROR_BOL
mdefine_line|#define PROMLOG_ERROR_BOL&t;       -4
DECL|macro|PROMLOG_ERROR_EOL
mdefine_line|#define PROMLOG_ERROR_EOL&t;       -5
DECL|macro|PROMLOG_ERROR_POS
mdefine_line|#define PROMLOG_ERROR_POS&t;       -6
DECL|macro|PROMLOG_ERROR_REPLACE
mdefine_line|#define PROMLOG_ERROR_REPLACE&t;       -7
DECL|macro|PROMLOG_ERROR_COMPACT
mdefine_line|#define PROMLOG_ERROR_COMPACT&t;       -8
DECL|macro|PROMLOG_ERROR_FULL
mdefine_line|#define PROMLOG_ERROR_FULL&t;       -9
DECL|macro|PROMLOG_ERROR_ARG
mdefine_line|#define PROMLOG_ERROR_ARG&t;       -10
DECL|macro|PROMLOG_ERROR_UNUSED
mdefine_line|#define PROMLOG_ERROR_UNUSED&t;       -11&t;  &t;
DECL|macro|PROMLOG_TYPE_UNUSED
mdefine_line|#define PROMLOG_TYPE_UNUSED&t;&t;0xf
DECL|macro|PROMLOG_TYPE_LOG
mdefine_line|#define PROMLOG_TYPE_LOG&t;&t;3
DECL|macro|PROMLOG_TYPE_LIST
mdefine_line|#define PROMLOG_TYPE_LIST&t;&t;2
DECL|macro|PROMLOG_TYPE_VAR
mdefine_line|#define PROMLOG_TYPE_VAR&t;&t;1
DECL|macro|PROMLOG_TYPE_DELETED
mdefine_line|#define PROMLOG_TYPE_DELETED&t;&t;0
DECL|macro|PROMLOG_TYPE_ANY
mdefine_line|#define PROMLOG_TYPE_ANY&t;&t;98
DECL|macro|PROMLOG_TYPE_INVALID
mdefine_line|#define PROMLOG_TYPE_INVALID&t;&t;99
DECL|macro|PROMLOG_KEY_MAX
mdefine_line|#define PROMLOG_KEY_MAX&t;&t;&t;14
DECL|macro|PROMLOG_VALUE_MAX
mdefine_line|#define PROMLOG_VALUE_MAX&t;&t;47
DECL|macro|PROMLOG_CPU_MAX
mdefine_line|#define PROMLOG_CPU_MAX&t;&t;&t;4
DECL|struct|promlog_header_s
r_typedef
r_struct
id|promlog_header_s
(brace
DECL|member|unused
r_int
r_int
id|unused
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
DECL|member|version
r_int
r_int
id|version
suffix:semicolon
DECL|member|sequence
r_int
r_int
id|sequence
suffix:semicolon
DECL|typedef|promlog_header_t
)brace
id|promlog_header_t
suffix:semicolon
DECL|typedef|promlog_pos_t
r_typedef
r_int
r_int
id|promlog_pos_t
suffix:semicolon
DECL|struct|promlog_ent_s
r_typedef
r_struct
id|promlog_ent_s
(brace
multiline_comment|/* PROM individual entry */
DECL|member|type
id|uint
id|type
suffix:colon
l_int|4
suffix:semicolon
DECL|member|cpu_num
id|uint
id|cpu_num
suffix:colon
l_int|4
suffix:semicolon
DECL|member|key
r_char
id|key
(braket
id|PROMLOG_KEY_MAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|value
r_char
id|value
(braket
id|PROMLOG_VALUE_MAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|typedef|promlog_ent_t
)brace
id|promlog_ent_t
suffix:semicolon
DECL|struct|promlog_s
r_typedef
r_struct
id|promlog_s
(brace
multiline_comment|/* Activation handle */
DECL|member|f
id|fprom_t
id|f
suffix:semicolon
DECL|member|sector_base
r_int
id|sector_base
suffix:semicolon
DECL|member|cpu_num
r_int
id|cpu_num
suffix:semicolon
DECL|member|active
r_int
id|active
suffix:semicolon
multiline_comment|/* Active sector, 0 or 1 */
DECL|member|log_start
id|promlog_pos_t
id|log_start
suffix:semicolon
DECL|member|log_end
id|promlog_pos_t
id|log_end
suffix:semicolon
DECL|member|alt_start
id|promlog_pos_t
id|alt_start
suffix:semicolon
DECL|member|alt_end
id|promlog_pos_t
id|alt_end
suffix:semicolon
DECL|member|pos
id|promlog_pos_t
id|pos
suffix:semicolon
DECL|member|ent
id|promlog_ent_t
id|ent
suffix:semicolon
DECL|typedef|promlog_t
)brace
id|promlog_t
suffix:semicolon
macro_line|#endif /* _ASM_SN_SN1_PROMLOG_H */
eof
