multiline_comment|/*&n; * Export MIPS-specific functions needed for loadable modules.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 97, 98, 99, 2000, 01, 03 by Ralf Baechle&n; * Copyright (C) 1999, 2000, 01 Silicon Graphics, Inc.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_extern
r_void
op_star
id|__bzero
c_func
(paren
r_void
op_star
id|__s
comma
r_int
id|__count
)paren
suffix:semicolon
r_extern
r_int
id|__strncpy_from_user_nocheck_asm
c_func
(paren
r_char
op_star
id|__to
comma
r_const
r_char
op_star
id|__from
comma
r_int
id|__len
)paren
suffix:semicolon
r_extern
r_int
id|__strncpy_from_user_asm
c_func
(paren
r_char
op_star
id|__to
comma
r_const
r_char
op_star
id|__from
comma
r_int
id|__len
)paren
suffix:semicolon
r_extern
r_int
id|__strlen_user_nocheck_asm
c_func
(paren
r_const
r_char
op_star
id|s
)paren
suffix:semicolon
r_extern
r_int
id|__strlen_user_asm
c_func
(paren
r_const
r_char
op_star
id|s
)paren
suffix:semicolon
r_extern
r_int
id|__strnlen_user_nocheck_asm
c_func
(paren
r_const
r_char
op_star
id|s
)paren
suffix:semicolon
r_extern
r_int
id|__strnlen_user_asm
c_func
(paren
r_const
r_char
op_star
id|s
)paren
suffix:semicolon
multiline_comment|/*&n; * String functions&n; */
DECL|variable|memchr
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memchr
)paren
suffix:semicolon
DECL|variable|memcmp
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memcmp
)paren
suffix:semicolon
DECL|variable|memset
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memset
)paren
suffix:semicolon
DECL|variable|memcpy
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memcpy
)paren
suffix:semicolon
DECL|variable|memmove
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memmove
)paren
suffix:semicolon
DECL|variable|strcat
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strcat
)paren
suffix:semicolon
DECL|variable|strchr
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strchr
)paren
suffix:semicolon
DECL|variable|strlen
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strlen
)paren
suffix:semicolon
DECL|variable|strpbrk
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strpbrk
)paren
suffix:semicolon
DECL|variable|strncat
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strncat
)paren
suffix:semicolon
DECL|variable|strnlen
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strnlen
)paren
suffix:semicolon
DECL|variable|strrchr
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strrchr
)paren
suffix:semicolon
DECL|variable|strstr
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strstr
)paren
suffix:semicolon
DECL|variable|kernel_thread
id|EXPORT_SYMBOL
c_func
(paren
id|kernel_thread
)paren
suffix:semicolon
multiline_comment|/*&n; * Userspace access stuff.&n; */
DECL|variable|__copy_user
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__copy_user
)paren
suffix:semicolon
DECL|variable|__bzero
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__bzero
)paren
suffix:semicolon
DECL|variable|__strncpy_from_user_nocheck_asm
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__strncpy_from_user_nocheck_asm
)paren
suffix:semicolon
DECL|variable|__strncpy_from_user_asm
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__strncpy_from_user_asm
)paren
suffix:semicolon
DECL|variable|__strlen_user_nocheck_asm
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__strlen_user_nocheck_asm
)paren
suffix:semicolon
DECL|variable|__strlen_user_asm
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__strlen_user_asm
)paren
suffix:semicolon
DECL|variable|__strnlen_user_nocheck_asm
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__strnlen_user_nocheck_asm
)paren
suffix:semicolon
DECL|variable|__strnlen_user_asm
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__strnlen_user_asm
)paren
suffix:semicolon
DECL|variable|csum_partial
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial
)paren
suffix:semicolon
DECL|variable|invalid_pte_table
id|EXPORT_SYMBOL
c_func
(paren
id|invalid_pte_table
)paren
suffix:semicolon
eof
