multiline_comment|/*&n; *&t;Generate devlist.h and classlist.h from the PCI ID file.&n; *&n; *&t;(c) 1999--2002 Martin Mares &lt;mj@ucw.cz&gt;&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;string.h&gt;
DECL|macro|MAX_NAME_SIZE
mdefine_line|#define MAX_NAME_SIZE 200
r_static
r_void
DECL|function|pq
id|pq
c_func
(paren
id|FILE
op_star
id|f
comma
r_const
r_char
op_star
id|c
comma
r_int
id|len
)paren
(brace
r_int
id|i
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
op_star
id|c
op_logical_and
id|i
op_ne
id|len
)paren
(brace
r_if
c_cond
(paren
op_star
id|c
op_eq
l_char|&squot;&quot;&squot;
)paren
id|fprintf
c_func
(paren
id|f
comma
l_string|&quot;&bslash;&bslash;&bslash;&quot;&quot;
)paren
suffix:semicolon
r_else
(brace
id|fputc
c_func
(paren
op_star
id|c
comma
id|f
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|c
op_eq
l_char|&squot;?&squot;
op_logical_and
id|c
(braket
l_int|1
)braket
op_eq
l_char|&squot;?&squot;
)paren
(brace
multiline_comment|/* Avoid trigraphs */
id|fprintf
c_func
(paren
id|f
comma
l_string|&quot;&bslash;&quot; &bslash;&quot;&quot;
)paren
suffix:semicolon
)brace
)brace
id|c
op_increment
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
)brace
r_int
DECL|function|main
id|main
c_func
(paren
r_void
)paren
(brace
r_char
id|line
(braket
l_int|1024
)braket
comma
op_star
id|c
comma
op_star
id|bra
comma
id|vend
(braket
l_int|8
)braket
suffix:semicolon
r_int
id|vendors
op_assign
l_int|0
suffix:semicolon
r_int
id|mode
op_assign
l_int|0
suffix:semicolon
r_int
id|lino
op_assign
l_int|0
suffix:semicolon
r_int
id|vendor_len
op_assign
l_int|0
suffix:semicolon
id|FILE
op_star
id|devf
comma
op_star
id|clsf
suffix:semicolon
id|devf
op_assign
id|fopen
c_func
(paren
l_string|&quot;devlist.h&quot;
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
id|clsf
op_assign
id|fopen
c_func
(paren
l_string|&quot;classlist.h&quot;
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|devf
op_logical_or
op_logical_neg
id|clsf
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Cannot create output file!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|line
comma
r_sizeof
(paren
id|line
)paren
op_minus
l_int|1
comma
id|stdin
)paren
)paren
(brace
id|lino
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|c
op_assign
id|strchr
c_func
(paren
id|line
comma
l_char|&squot;&bslash;n&squot;
)paren
)paren
)paren
op_star
id|c
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|line
(braket
l_int|0
)braket
op_logical_or
id|line
(braket
l_int|0
)braket
op_eq
l_char|&squot;#&squot;
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|line
(braket
l_int|1
)braket
op_eq
l_char|&squot; &squot;
)paren
(brace
r_if
c_cond
(paren
id|line
(braket
l_int|0
)braket
op_eq
l_char|&squot;C&squot;
op_logical_and
id|strlen
c_func
(paren
id|line
)paren
OG
l_int|4
op_logical_and
id|line
(braket
l_int|4
)braket
op_eq
l_char|&squot; &squot;
)paren
(brace
id|vend
(braket
l_int|0
)braket
op_assign
id|line
(braket
l_int|2
)braket
suffix:semicolon
id|vend
(braket
l_int|1
)braket
op_assign
id|line
(braket
l_int|3
)braket
suffix:semicolon
id|vend
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
id|mode
op_assign
l_int|2
suffix:semicolon
)brace
r_else
r_goto
id|err
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|line
(braket
l_int|0
)braket
op_eq
l_char|&squot;&bslash;t&squot;
)paren
(brace
r_if
c_cond
(paren
id|line
(braket
l_int|1
)braket
op_eq
l_char|&squot;&bslash;t&squot;
)paren
r_continue
suffix:semicolon
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|line
)paren
OG
l_int|5
op_logical_and
id|line
(braket
l_int|5
)braket
op_eq
l_char|&squot; &squot;
)paren
(brace
id|c
op_assign
id|line
op_plus
l_int|5
suffix:semicolon
r_while
c_loop
(paren
op_star
id|c
op_eq
l_char|&squot; &squot;
)paren
op_star
id|c
op_increment
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|vendor_len
op_plus
id|strlen
c_func
(paren
id|c
)paren
op_plus
l_int|1
OG
id|MAX_NAME_SIZE
)paren
(brace
multiline_comment|/* Too long, try cutting off long description */
id|bra
op_assign
id|strchr
c_func
(paren
id|c
comma
l_char|&squot;[&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bra
op_logical_and
id|bra
OG
id|c
op_logical_and
id|bra
(braket
op_minus
l_int|1
)braket
op_eq
l_char|&squot; &squot;
)paren
id|bra
(braket
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|vendor_len
op_plus
id|strlen
c_func
(paren
id|c
)paren
op_plus
l_int|1
OG
id|MAX_NAME_SIZE
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Line %d: Device name too long. Name truncated.&bslash;n&quot;
comma
id|lino
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|c
)paren
suffix:semicolon
multiline_comment|/*return 1;*/
)brace
)brace
id|fprintf
c_func
(paren
id|devf
comma
l_string|&quot;&bslash;tDEVICE(%s,%s,&bslash;&quot;&quot;
comma
id|vend
comma
id|line
op_plus
l_int|1
)paren
suffix:semicolon
id|pq
c_func
(paren
id|devf
comma
id|c
comma
id|MAX_NAME_SIZE
op_minus
id|vendor_len
op_minus
l_int|1
)paren
suffix:semicolon
id|fputs
c_func
(paren
l_string|&quot;&bslash;&quot;)&bslash;n&quot;
comma
id|devf
)paren
suffix:semicolon
)brace
r_else
r_goto
id|err
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|line
)paren
OG
l_int|3
op_logical_and
id|line
(braket
l_int|3
)braket
op_eq
l_char|&squot; &squot;
)paren
(brace
id|c
op_assign
id|line
op_plus
l_int|3
suffix:semicolon
r_while
c_loop
(paren
op_star
id|c
op_eq
l_char|&squot; &squot;
)paren
op_star
id|c
op_increment
op_assign
l_int|0
suffix:semicolon
id|fprintf
c_func
(paren
id|clsf
comma
l_string|&quot;CLASS(%s%s, &bslash;&quot;%s&bslash;&quot;)&bslash;n&quot;
comma
id|vend
comma
id|line
op_plus
l_int|1
comma
id|c
)paren
suffix:semicolon
)brace
r_else
r_goto
id|err
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|err
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|line
)paren
OG
l_int|4
op_logical_and
id|line
(braket
l_int|4
)braket
op_eq
l_char|&squot; &squot;
)paren
(brace
id|c
op_assign
id|line
op_plus
l_int|4
suffix:semicolon
r_while
c_loop
(paren
op_star
id|c
op_eq
l_char|&squot; &squot;
)paren
op_star
id|c
op_increment
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|vendors
)paren
id|fputs
c_func
(paren
l_string|&quot;ENDVENDOR()&bslash;n&bslash;n&quot;
comma
id|devf
)paren
suffix:semicolon
id|vendors
op_increment
suffix:semicolon
id|strcpy
c_func
(paren
id|vend
comma
id|line
)paren
suffix:semicolon
id|vendor_len
op_assign
id|strlen
c_func
(paren
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vendor_len
op_plus
l_int|24
OG
id|MAX_NAME_SIZE
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Line %d: Vendor name too long&bslash;n&quot;
comma
id|lino
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|devf
comma
l_string|&quot;VENDOR(%s,&bslash;&quot;&quot;
comma
id|vend
)paren
suffix:semicolon
id|pq
c_func
(paren
id|devf
comma
id|c
comma
l_int|0
)paren
suffix:semicolon
id|fputs
c_func
(paren
l_string|&quot;&bslash;&quot;)&bslash;n&quot;
comma
id|devf
)paren
suffix:semicolon
id|mode
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|err
suffix:colon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Line %d: Syntax error in mode %d: %s&bslash;n&quot;
comma
id|lino
comma
id|mode
comma
id|line
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
id|fputs
c_func
(paren
l_string|&quot;ENDVENDOR()&bslash;n&bslash;&n;&bslash;n&bslash;&n;#undef VENDOR&bslash;n&bslash;&n;#undef DEVICE&bslash;n&bslash;&n;#undef ENDVENDOR&bslash;n&quot;
comma
id|devf
)paren
suffix:semicolon
id|fputs
c_func
(paren
l_string|&quot;&bslash;n#undef CLASS&bslash;n&quot;
comma
id|clsf
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|devf
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|clsf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
