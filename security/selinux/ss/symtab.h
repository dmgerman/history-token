multiline_comment|/*&n; * A symbol table (symtab) maintains associations between symbol&n; * strings and datum values.  The type of the datum values&n; * is arbitrary.  The symbol table type is implemented&n; * using the hash table type (hashtab).&n; *&n; * Author : Stephen Smalley, &lt;sds@epoch.ncsc.mil&gt;&n; */
macro_line|#ifndef _SS_SYMTAB_H_
DECL|macro|_SS_SYMTAB_H_
mdefine_line|#define _SS_SYMTAB_H_
macro_line|#include &quot;hashtab.h&quot;
DECL|struct|symtab
r_struct
id|symtab
(brace
DECL|member|table
r_struct
id|hashtab
op_star
id|table
suffix:semicolon
multiline_comment|/* hash table (keyed on a string) */
DECL|member|nprim
id|u32
id|nprim
suffix:semicolon
multiline_comment|/* number of primary names in table */
)brace
suffix:semicolon
r_int
id|symtab_init
c_func
(paren
r_struct
id|symtab
op_star
id|s
comma
r_int
r_int
id|size
)paren
suffix:semicolon
macro_line|#endif&t;/* _SS_SYMTAB_H_ */
eof
