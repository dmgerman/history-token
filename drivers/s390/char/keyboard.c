multiline_comment|/*&n; *  drivers/s390/char/keyboard.c&n; *    ebcdic keycode functions for s390 console drivers&n; *&n; *  S390 version&n; *    Copyright (C) 2003 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/sysrq.h&gt;
macro_line|#include &lt;linux/kbd_kern.h&gt;
macro_line|#include &lt;linux/kbd_diacr.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;keyboard.h&quot;
multiline_comment|/*&n; * Handler Tables.&n; */
DECL|macro|K_HANDLERS
mdefine_line|#define K_HANDLERS&bslash;&n;&t;k_self,&t;&t;k_fn,&t;&t;k_spec,&t;&t;k_ignore,&bslash;&n;&t;k_dead,&t;&t;k_ignore,&t;k_ignore,&t;k_ignore,&bslash;&n;&t;k_ignore,&t;k_ignore,&t;k_ignore,&t;k_ignore,&bslash;&n;&t;k_ignore,&t;k_ignore,&t;k_ignore,&t;k_ignore
DECL|typedef|k_handler_fn
r_typedef
r_void
(paren
id|k_handler_fn
)paren
(paren
r_struct
id|kbd_data
op_star
comma
r_int
r_char
)paren
suffix:semicolon
DECL|variable|K_HANDLERS
r_static
id|k_handler_fn
id|K_HANDLERS
suffix:semicolon
DECL|variable|k_handler
r_static
id|k_handler_fn
op_star
id|k_handler
(braket
l_int|16
)braket
op_assign
(brace
id|K_HANDLERS
)brace
suffix:semicolon
multiline_comment|/* maximum values each key_handler can handle */
DECL|variable|kbd_max_vals
r_static
r_const
r_int
id|kbd_max_vals
(braket
)braket
op_assign
(brace
l_int|255
comma
id|ARRAY_SIZE
c_func
(paren
id|func_table
)paren
op_minus
l_int|1
comma
id|NR_FN_HANDLER
op_minus
l_int|1
comma
l_int|0
comma
id|NR_DEAD
op_minus
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|KBD_NR_TYPES
r_static
r_const
r_int
id|KBD_NR_TYPES
op_assign
id|ARRAY_SIZE
c_func
(paren
id|kbd_max_vals
)paren
suffix:semicolon
DECL|variable|ret_diacr
r_static
r_int
r_char
id|ret_diacr
(braket
id|NR_DEAD
)braket
op_assign
(brace
l_char|&squot;`&squot;
comma
l_char|&squot;&bslash;&squot;&squot;
comma
l_char|&squot;^&squot;
comma
l_char|&squot;~&squot;
comma
l_char|&squot;&quot;&squot;
comma
l_char|&squot;,&squot;
)brace
suffix:semicolon
multiline_comment|/*&n; * Alloc/free of kbd_data structures.&n; */
r_struct
id|kbd_data
op_star
DECL|function|kbd_alloc
id|kbd_alloc
c_func
(paren
r_void
)paren
(brace
r_struct
id|kbd_data
op_star
id|kbd
suffix:semicolon
r_int
id|i
comma
id|len
suffix:semicolon
id|kbd
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|kbd_data
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kbd
)paren
r_goto
id|out
suffix:semicolon
id|memset
c_func
(paren
id|kbd
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|kbd_data
)paren
)paren
suffix:semicolon
id|kbd-&gt;key_maps
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|key_maps
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|key_maps
)paren
r_goto
id|out_kbd
suffix:semicolon
id|memset
c_func
(paren
id|kbd-&gt;key_maps
comma
l_int|0
comma
r_sizeof
(paren
id|key_maps
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|key_maps
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|key_maps
(braket
id|i
)braket
)paren
(brace
id|kbd-&gt;key_maps
(braket
id|i
)braket
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|u_short
)paren
op_star
id|NR_KEYS
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kbd-&gt;key_maps
(braket
id|i
)braket
)paren
r_goto
id|out_maps
suffix:semicolon
id|memcpy
c_func
(paren
id|kbd-&gt;key_maps
(braket
id|i
)braket
comma
id|key_maps
(braket
id|i
)braket
comma
r_sizeof
(paren
id|u_short
)paren
op_star
id|NR_KEYS
)paren
suffix:semicolon
)brace
)brace
id|kbd-&gt;func_table
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|func_table
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kbd-&gt;func_table
)paren
r_goto
id|out_maps
suffix:semicolon
id|memset
c_func
(paren
id|kbd-&gt;func_table
comma
l_int|0
comma
r_sizeof
(paren
id|func_table
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|func_table
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|func_table
(braket
id|i
)braket
)paren
(brace
id|len
op_assign
id|strlen
c_func
(paren
id|func_table
(braket
id|i
)braket
)paren
op_plus
l_int|1
suffix:semicolon
id|kbd-&gt;func_table
(braket
id|i
)braket
op_assign
id|kmalloc
c_func
(paren
id|len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kbd-&gt;func_table
(braket
id|i
)braket
)paren
r_goto
id|out_func
suffix:semicolon
id|memcpy
c_func
(paren
id|kbd-&gt;func_table
(braket
id|i
)braket
comma
id|func_table
(braket
id|i
)braket
comma
id|len
)paren
suffix:semicolon
)brace
)brace
id|kbd-&gt;fn_handler
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|fn_handler_fn
op_star
)paren
op_star
id|NR_FN_HANDLER
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kbd-&gt;fn_handler
)paren
r_goto
id|out_func
suffix:semicolon
id|memset
c_func
(paren
id|kbd-&gt;fn_handler
comma
l_int|0
comma
r_sizeof
(paren
id|fn_handler_fn
op_star
)paren
op_star
id|NR_FN_HANDLER
)paren
suffix:semicolon
id|kbd-&gt;accent_table
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|kbdiacr
)paren
op_star
id|MAX_DIACR
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kbd-&gt;accent_table
)paren
r_goto
id|out_fn_handler
suffix:semicolon
id|memcpy
c_func
(paren
id|kbd-&gt;accent_table
comma
id|accent_table
comma
r_sizeof
(paren
r_struct
id|kbdiacr
)paren
op_star
id|MAX_DIACR
)paren
suffix:semicolon
id|kbd-&gt;accent_table_size
op_assign
id|accent_table_size
suffix:semicolon
r_return
id|kbd
suffix:semicolon
id|out_fn_handler
suffix:colon
id|kfree
c_func
(paren
id|kbd-&gt;fn_handler
)paren
suffix:semicolon
id|out_func
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|func_table
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|kbd-&gt;func_table
(braket
id|i
)braket
)paren
id|kfree
c_func
(paren
id|kbd-&gt;func_table
(braket
id|i
)braket
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|kbd-&gt;func_table
)paren
suffix:semicolon
id|out_maps
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|key_maps
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|kbd-&gt;key_maps
(braket
id|i
)braket
)paren
id|kfree
c_func
(paren
id|kbd-&gt;key_maps
(braket
id|i
)braket
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|kbd-&gt;key_maps
)paren
suffix:semicolon
id|out_kbd
suffix:colon
id|kfree
c_func
(paren
id|kbd
)paren
suffix:semicolon
id|out
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|kbd_free
id|kbd_free
c_func
(paren
r_struct
id|kbd_data
op_star
id|kbd
)paren
(brace
r_int
id|i
suffix:semicolon
id|kfree
c_func
(paren
id|kbd-&gt;accent_table
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|kbd-&gt;fn_handler
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|func_table
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|kbd-&gt;func_table
(braket
id|i
)braket
)paren
id|kfree
c_func
(paren
id|kbd-&gt;func_table
(braket
id|i
)braket
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|kbd-&gt;func_table
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|key_maps
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|kbd-&gt;key_maps
(braket
id|i
)braket
)paren
id|kfree
c_func
(paren
id|kbd-&gt;key_maps
(braket
id|i
)braket
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|kbd-&gt;key_maps
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|kbd
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Generate ascii -&gt; ebcdic translation table from kbd_data.&n; */
r_void
DECL|function|kbd_ascebc
id|kbd_ascebc
c_func
(paren
r_struct
id|kbd_data
op_star
id|kbd
comma
r_int
r_char
op_star
id|ascebc
)paren
(brace
r_int
r_int
op_star
id|keymap
comma
id|keysym
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|k
suffix:semicolon
id|memset
c_func
(paren
id|ascebc
comma
l_int|0x40
comma
l_int|256
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|key_maps
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|keymap
op_assign
id|kbd-&gt;key_maps
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|keymap
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|NR_KEYS
suffix:semicolon
id|j
op_increment
)paren
(brace
id|k
op_assign
(paren
(paren
id|i
op_amp
l_int|1
)paren
op_lshift
l_int|7
)paren
op_plus
id|j
suffix:semicolon
id|keysym
op_assign
id|keymap
(braket
id|j
)braket
suffix:semicolon
r_if
c_cond
(paren
id|KTYP
c_func
(paren
id|keysym
)paren
op_eq
(paren
id|KT_LATIN
op_or
l_int|0xf0
)paren
op_logical_or
id|KTYP
c_func
(paren
id|keysym
)paren
op_eq
(paren
id|KT_LETTER
op_or
l_int|0xf0
)paren
)paren
id|ascebc
(braket
id|KVAL
c_func
(paren
id|keysym
)paren
)braket
op_assign
id|k
suffix:semicolon
r_else
r_if
c_cond
(paren
id|KTYP
c_func
(paren
id|keysym
)paren
op_eq
(paren
id|KT_DEAD
op_or
l_int|0xf0
)paren
)paren
id|ascebc
(braket
id|ret_diacr
(braket
id|KVAL
c_func
(paren
id|keysym
)paren
)braket
)braket
op_assign
id|k
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Generate ebcdic -&gt; ascii translation table from kbd_data.&n; */
r_void
DECL|function|kbd_ebcasc
id|kbd_ebcasc
c_func
(paren
r_struct
id|kbd_data
op_star
id|kbd
comma
r_int
r_char
op_star
id|ebcasc
)paren
(brace
r_int
r_int
op_star
id|keymap
comma
id|keysym
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|k
suffix:semicolon
id|memset
c_func
(paren
id|ebcasc
comma
l_char|&squot; &squot;
comma
l_int|256
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|key_maps
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|keymap
op_assign
id|kbd-&gt;key_maps
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|keymap
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|NR_KEYS
suffix:semicolon
id|j
op_increment
)paren
(brace
id|keysym
op_assign
id|keymap
(braket
id|j
)braket
suffix:semicolon
id|k
op_assign
(paren
(paren
id|i
op_amp
l_int|1
)paren
op_lshift
l_int|7
)paren
op_plus
id|j
suffix:semicolon
r_if
c_cond
(paren
id|KTYP
c_func
(paren
id|keysym
)paren
op_eq
(paren
id|KT_LATIN
op_or
l_int|0xf0
)paren
op_logical_or
id|KTYP
c_func
(paren
id|keysym
)paren
op_eq
(paren
id|KT_LETTER
op_or
l_int|0xf0
)paren
)paren
id|ebcasc
(braket
id|k
)braket
op_assign
id|KVAL
c_func
(paren
id|keysym
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|KTYP
c_func
(paren
id|keysym
)paren
op_eq
(paren
id|KT_DEAD
op_or
l_int|0xf0
)paren
)paren
id|ebcasc
(braket
id|k
)braket
op_assign
id|ret_diacr
(braket
id|KVAL
c_func
(paren
id|keysym
)paren
)braket
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * We have a combining character DIACR here, followed by the character CH.&n; * If the combination occurs in the table, return the corresponding value.&n; * Otherwise, if CH is a space or equals DIACR, return DIACR.&n; * Otherwise, conclude that DIACR was not combining after all,&n; * queue it and return CH.&n; */
r_static
r_int
r_char
DECL|function|handle_diacr
id|handle_diacr
c_func
(paren
r_struct
id|kbd_data
op_star
id|kbd
comma
r_int
r_char
id|ch
)paren
(brace
r_int
id|i
comma
id|d
suffix:semicolon
id|d
op_assign
id|kbd-&gt;diacr
suffix:semicolon
id|kbd-&gt;diacr
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|kbd-&gt;accent_table_size
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|kbd-&gt;accent_table
(braket
id|i
)braket
dot
id|diacr
op_eq
id|d
op_logical_and
id|kbd-&gt;accent_table
(braket
id|i
)braket
dot
id|base
op_eq
id|ch
)paren
r_return
id|kbd-&gt;accent_table
(braket
id|i
)braket
dot
id|result
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot; &squot;
op_logical_or
id|ch
op_eq
id|d
)paren
r_return
id|d
suffix:semicolon
id|kbd_put_queue
c_func
(paren
id|kbd-&gt;tty
comma
id|d
)paren
suffix:semicolon
r_return
id|ch
suffix:semicolon
)brace
multiline_comment|/*&n; * Handle dead key.&n; */
r_static
r_void
DECL|function|k_dead
id|k_dead
c_func
(paren
r_struct
id|kbd_data
op_star
id|kbd
comma
r_int
r_char
id|value
)paren
(brace
id|value
op_assign
id|ret_diacr
(braket
id|value
)braket
suffix:semicolon
id|kbd-&gt;diacr
op_assign
(paren
id|kbd-&gt;diacr
ques
c_cond
id|handle_diacr
c_func
(paren
id|kbd
comma
id|value
)paren
suffix:colon
id|value
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Normal character handler.&n; */
r_static
r_void
DECL|function|k_self
id|k_self
c_func
(paren
r_struct
id|kbd_data
op_star
id|kbd
comma
r_int
r_char
id|value
)paren
(brace
r_if
c_cond
(paren
id|kbd-&gt;diacr
)paren
id|value
op_assign
id|handle_diacr
c_func
(paren
id|kbd
comma
id|value
)paren
suffix:semicolon
id|kbd_put_queue
c_func
(paren
id|kbd-&gt;tty
comma
id|value
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Special key handlers&n; */
r_static
r_void
DECL|function|k_ignore
id|k_ignore
c_func
(paren
r_struct
id|kbd_data
op_star
id|kbd
comma
r_int
r_char
id|value
)paren
(brace
)brace
multiline_comment|/*&n; * Function key handler.&n; */
r_static
r_void
DECL|function|k_fn
id|k_fn
c_func
(paren
r_struct
id|kbd_data
op_star
id|kbd
comma
r_int
r_char
id|value
)paren
(brace
r_if
c_cond
(paren
id|kbd-&gt;func_table
(braket
id|value
)braket
)paren
id|kbd_puts_queue
c_func
(paren
id|kbd-&gt;tty
comma
id|kbd-&gt;func_table
(braket
id|value
)braket
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|k_spec
id|k_spec
c_func
(paren
r_struct
id|kbd_data
op_star
id|kbd
comma
r_int
r_char
id|value
)paren
(brace
r_if
c_cond
(paren
id|value
op_ge
id|NR_FN_HANDLER
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|kbd-&gt;fn_handler
(braket
id|value
)braket
)paren
id|kbd-&gt;fn_handler
(braket
id|value
)braket
(paren
id|kbd
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Put utf8 character to tty flip buffer.&n; * UTF-8 is defined for words of up to 31 bits,&n; * but we need only 16 bits here&n; */
r_static
r_void
DECL|function|to_utf8
id|to_utf8
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
id|ushort
id|c
)paren
(brace
r_if
c_cond
(paren
id|c
OL
l_int|0x80
)paren
multiline_comment|/*  0******* */
id|kbd_put_queue
c_func
(paren
id|tty
comma
id|c
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|c
OL
l_int|0x800
)paren
(brace
multiline_comment|/* 110***** 10****** */
id|kbd_put_queue
c_func
(paren
id|tty
comma
l_int|0xc0
op_or
(paren
id|c
op_rshift
l_int|6
)paren
)paren
suffix:semicolon
id|kbd_put_queue
c_func
(paren
id|tty
comma
l_int|0x80
op_or
(paren
id|c
op_amp
l_int|0x3f
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* 1110**** 10****** 10****** */
id|kbd_put_queue
c_func
(paren
id|tty
comma
l_int|0xe0
op_or
(paren
id|c
op_rshift
l_int|12
)paren
)paren
suffix:semicolon
id|kbd_put_queue
c_func
(paren
id|tty
comma
l_int|0x80
op_or
(paren
(paren
id|c
op_rshift
l_int|6
)paren
op_amp
l_int|0x3f
)paren
)paren
suffix:semicolon
id|kbd_put_queue
c_func
(paren
id|tty
comma
l_int|0x80
op_or
(paren
id|c
op_amp
l_int|0x3f
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Process keycode.&n; */
r_void
DECL|function|kbd_keycode
id|kbd_keycode
c_func
(paren
r_struct
id|kbd_data
op_star
id|kbd
comma
r_int
r_int
id|keycode
)paren
(brace
r_int
r_int
id|keysym
suffix:semicolon
r_int
r_char
id|type
comma
id|value
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kbd
op_logical_or
op_logical_neg
id|kbd-&gt;tty
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|keycode
op_ge
l_int|384
)paren
id|keysym
op_assign
id|kbd-&gt;key_maps
(braket
l_int|5
)braket
(braket
id|keycode
op_minus
l_int|384
)braket
suffix:semicolon
r_else
r_if
c_cond
(paren
id|keycode
op_ge
l_int|256
)paren
id|keysym
op_assign
id|kbd-&gt;key_maps
(braket
l_int|4
)braket
(braket
id|keycode
op_minus
l_int|256
)braket
suffix:semicolon
r_else
r_if
c_cond
(paren
id|keycode
op_ge
l_int|128
)paren
id|keysym
op_assign
id|kbd-&gt;key_maps
(braket
l_int|1
)braket
(braket
id|keycode
op_minus
l_int|128
)braket
suffix:semicolon
r_else
id|keysym
op_assign
id|kbd-&gt;key_maps
(braket
l_int|0
)braket
(braket
id|keycode
)braket
suffix:semicolon
id|type
op_assign
id|KTYP
c_func
(paren
id|keysym
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ge
l_int|0xf0
)paren
(brace
id|type
op_sub_assign
l_int|0xf0
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|KT_LETTER
)paren
id|type
op_assign
id|KT_LATIN
suffix:semicolon
id|value
op_assign
id|KVAL
c_func
(paren
id|keysym
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MAGIC_SYSRQ&t;       /* Handle the SysRq Hack */
r_if
c_cond
(paren
id|kbd-&gt;sysrq
)paren
(brace
r_if
c_cond
(paren
id|kbd-&gt;sysrq
op_eq
id|K
c_func
(paren
id|KT_LATIN
comma
l_char|&squot;-&squot;
)paren
)paren
(brace
id|kbd-&gt;sysrq
op_assign
l_int|0
suffix:semicolon
id|handle_sysrq
c_func
(paren
id|value
comma
l_int|0
comma
id|kbd-&gt;tty
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|value
op_eq
l_char|&squot;-&squot;
)paren
(brace
id|kbd-&gt;sysrq
op_assign
id|K
c_func
(paren
id|KT_LATIN
comma
l_char|&squot;-&squot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Incomplete sysrq sequence. */
(paren
op_star
id|k_handler
(braket
id|KTYP
c_func
(paren
id|kbd-&gt;sysrq
)paren
)braket
)paren
(paren
id|kbd
comma
id|KVAL
c_func
(paren
id|kbd-&gt;sysrq
)paren
)paren
suffix:semicolon
id|kbd-&gt;sysrq
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|type
op_eq
id|KT_LATIN
op_logical_and
id|value
op_eq
l_char|&squot;^&squot;
)paren
op_logical_or
(paren
id|type
op_eq
id|KT_DEAD
op_logical_and
id|ret_diacr
(braket
id|value
)braket
op_eq
l_char|&squot;^&squot;
)paren
)paren
(brace
id|kbd-&gt;sysrq
op_assign
id|K
c_func
(paren
id|type
comma
id|value
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
(paren
op_star
id|k_handler
(braket
id|type
)braket
)paren
(paren
id|kbd
comma
id|value
)paren
suffix:semicolon
)brace
r_else
id|to_utf8
c_func
(paren
id|kbd-&gt;tty
comma
id|keysym
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Ioctl stuff.&n; */
r_static
r_int
DECL|function|do_kdsk_ioctl
id|do_kdsk_ioctl
c_func
(paren
r_struct
id|kbd_data
op_star
id|kbd
comma
r_struct
id|kbentry
id|__user
op_star
id|user_kbe
comma
r_int
id|cmd
comma
r_int
id|perm
)paren
(brace
r_struct
id|kbentry
id|tmp
suffix:semicolon
id|ushort
op_star
id|key_map
comma
id|val
comma
id|ov
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|tmp
comma
id|user_kbe
comma
r_sizeof
(paren
r_struct
id|kbentry
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
macro_line|#if NR_KEYS &lt; 256
r_if
c_cond
(paren
id|tmp.kb_index
op_ge
id|NR_KEYS
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
macro_line|#endif
macro_line|#if MAX_NR_KEYMAPS &lt; 256
r_if
c_cond
(paren
id|tmp.kb_table
op_ge
id|MAX_NR_KEYMAPS
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|KDGKBENT
suffix:colon
id|key_map
op_assign
id|kbd-&gt;key_maps
(braket
id|tmp.kb_table
)braket
suffix:semicolon
r_if
c_cond
(paren
id|key_map
)paren
(brace
id|val
op_assign
id|U
c_func
(paren
id|key_map
(braket
id|tmp.kb_index
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|KTYP
c_func
(paren
id|val
)paren
op_ge
id|KBD_NR_TYPES
)paren
id|val
op_assign
id|K_HOLE
suffix:semicolon
)brace
r_else
id|val
op_assign
(paren
id|tmp.kb_index
ques
c_cond
id|K_HOLE
suffix:colon
id|K_NOSUCHMAP
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|val
comma
op_amp
id|user_kbe-&gt;kb_value
)paren
suffix:semicolon
r_case
id|KDSKBENT
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|perm
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp.kb_index
op_logical_and
id|tmp.kb_value
op_eq
id|K_NOSUCHMAP
)paren
(brace
multiline_comment|/* disallocate map */
id|key_map
op_assign
id|kbd-&gt;key_maps
(braket
id|tmp.kb_table
)braket
suffix:semicolon
r_if
c_cond
(paren
id|key_map
)paren
(brace
id|kbd-&gt;key_maps
(braket
id|tmp.kb_table
)braket
op_assign
l_int|0
suffix:semicolon
id|kfree
c_func
(paren
id|key_map
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|KTYP
c_func
(paren
id|tmp.kb_value
)paren
op_ge
id|KBD_NR_TYPES
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|KVAL
c_func
(paren
id|tmp.kb_value
)paren
OG
id|kbd_max_vals
(braket
id|KTYP
c_func
(paren
id|tmp.kb_value
)paren
)braket
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|key_map
op_assign
id|kbd-&gt;key_maps
(braket
id|tmp.kb_table
)braket
)paren
)paren
(brace
r_int
id|j
suffix:semicolon
id|key_map
op_assign
(paren
id|ushort
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|plain_map
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|key_map
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|kbd-&gt;key_maps
(braket
id|tmp.kb_table
)braket
op_assign
id|key_map
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|NR_KEYS
suffix:semicolon
id|j
op_increment
)paren
id|key_map
(braket
id|j
)braket
op_assign
id|U
c_func
(paren
id|K_HOLE
)paren
suffix:semicolon
)brace
id|ov
op_assign
id|U
c_func
(paren
id|key_map
(braket
id|tmp.kb_index
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp.kb_value
op_eq
id|ov
)paren
r_break
suffix:semicolon
multiline_comment|/* nothing to do */
multiline_comment|/*&n;&t;&t; * Attention Key.&n;&t;&t; */
r_if
c_cond
(paren
(paren
(paren
id|ov
op_eq
id|K_SAK
)paren
op_logical_or
(paren
id|tmp.kb_value
op_eq
id|K_SAK
)paren
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|key_map
(braket
id|tmp.kb_index
)braket
op_assign
id|U
c_func
(paren
id|tmp.kb_value
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|do_kdgkb_ioctl
id|do_kdgkb_ioctl
c_func
(paren
r_struct
id|kbd_data
op_star
id|kbd
comma
r_struct
id|kbsentry
id|__user
op_star
id|u_kbs
comma
r_int
id|cmd
comma
r_int
id|perm
)paren
(brace
r_int
r_char
id|kb_func
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_int
id|len
suffix:semicolon
multiline_comment|/* Get u_kbs-&gt;kb_func. */
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|kb_func
comma
op_amp
id|u_kbs-&gt;kb_func
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
macro_line|#if MAX_NR_FUNC &lt; 256
r_if
c_cond
(paren
id|kb_func
op_ge
id|MAX_NR_FUNC
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|KDGKBSENT
suffix:colon
id|p
op_assign
id|kbd-&gt;func_table
(braket
id|kb_func
)braket
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
(brace
id|len
op_assign
id|strlen
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
r_sizeof
(paren
id|u_kbs-&gt;kb_string
)paren
)paren
id|len
op_assign
r_sizeof
(paren
id|u_kbs-&gt;kb_string
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|u_kbs-&gt;kb_string
comma
id|p
comma
id|len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
id|len
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
l_char|&squot;&bslash;0&squot;
comma
id|u_kbs-&gt;kb_string
op_plus
id|len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|KDSKBSENT
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|perm
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|len
op_assign
id|strnlen_user
c_func
(paren
id|u_kbs-&gt;kb_string
comma
r_sizeof
(paren
id|u_kbs-&gt;kb_string
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|p
op_assign
id|kmalloc
c_func
(paren
id|len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|p
comma
id|u_kbs-&gt;kb_string
comma
id|len
)paren
)paren
(brace
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|p
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|kbd-&gt;func_table
(braket
id|kb_func
)braket
)paren
id|kfree
c_func
(paren
id|kbd-&gt;func_table
(braket
id|kb_func
)braket
)paren
suffix:semicolon
id|kbd-&gt;func_table
(braket
id|kb_func
)braket
op_assign
id|p
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|kbd_ioctl
id|kbd_ioctl
c_func
(paren
r_struct
id|kbd_data
op_star
id|kbd
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|kbdiacrs
id|__user
op_star
id|a
suffix:semicolon
r_void
id|__user
op_star
id|argp
suffix:semicolon
r_int
id|ct
comma
id|perm
suffix:semicolon
id|argp
op_assign
(paren
r_void
id|__user
op_star
)paren
id|arg
suffix:semicolon
multiline_comment|/*&n;&t; * To have permissions to do most of the vt ioctls, we either have&n;&t; * to be the owner of the tty, or have CAP_SYS_TTY_CONFIG.&n;&t; */
id|perm
op_assign
id|current-&gt;signal-&gt;tty
op_eq
id|kbd-&gt;tty
op_logical_or
id|capable
c_func
(paren
id|CAP_SYS_TTY_CONFIG
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|KDGKBTYPE
suffix:colon
r_return
id|put_user
c_func
(paren
id|KB_101
comma
(paren
r_char
id|__user
op_star
)paren
id|argp
)paren
suffix:semicolon
r_case
id|KDGKBENT
suffix:colon
r_case
id|KDSKBENT
suffix:colon
r_return
id|do_kdsk_ioctl
c_func
(paren
id|kbd
comma
id|argp
comma
id|cmd
comma
id|perm
)paren
suffix:semicolon
r_case
id|KDGKBSENT
suffix:colon
r_case
id|KDSKBSENT
suffix:colon
r_return
id|do_kdgkb_ioctl
c_func
(paren
id|kbd
comma
id|argp
comma
id|cmd
comma
id|perm
)paren
suffix:semicolon
r_case
id|KDGKBDIACR
suffix:colon
id|a
op_assign
id|argp
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|kbd-&gt;accent_table_size
comma
op_amp
id|a-&gt;kb_cnt
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|ct
op_assign
id|kbd-&gt;accent_table_size
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|a-&gt;kbdiacr
comma
id|kbd-&gt;accent_table
comma
id|ct
op_star
r_sizeof
(paren
r_struct
id|kbdiacr
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|KDSKBDIACR
suffix:colon
id|a
op_assign
id|argp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|perm
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|ct
comma
op_amp
id|a-&gt;kb_cnt
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|ct
op_ge
id|MAX_DIACR
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|kbd-&gt;accent_table_size
op_assign
id|ct
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|kbd-&gt;accent_table
comma
id|a-&gt;kbdiacr
comma
id|ct
op_star
r_sizeof
(paren
r_struct
id|kbdiacr
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
)brace
DECL|variable|kbd_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|kbd_ioctl
)paren
suffix:semicolon
DECL|variable|kbd_ascebc
id|EXPORT_SYMBOL
c_func
(paren
id|kbd_ascebc
)paren
suffix:semicolon
DECL|variable|kbd_free
id|EXPORT_SYMBOL
c_func
(paren
id|kbd_free
)paren
suffix:semicolon
DECL|variable|kbd_alloc
id|EXPORT_SYMBOL
c_func
(paren
id|kbd_alloc
)paren
suffix:semicolon
DECL|variable|kbd_keycode
id|EXPORT_SYMBOL
c_func
(paren
id|kbd_keycode
)paren
suffix:semicolon
eof
