multiline_comment|/*&n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/init.h&quot;
macro_line|#include &quot;linux/bootmem.h&quot;
macro_line|#include &quot;linux/initrd.h&quot;
macro_line|#include &quot;asm/types.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;initrd.h&quot;
macro_line|#include &quot;init.h&quot;
macro_line|#include &quot;os.h&quot;
multiline_comment|/* Changed by uml_initrd_setup, which is a setup */
DECL|variable|__initdata
r_static
r_char
op_star
id|initrd
id|__initdata
op_assign
l_int|NULL
suffix:semicolon
DECL|function|read_initrd
r_static
r_int
id|__init
id|read_initrd
c_func
(paren
r_void
)paren
(brace
r_void
op_star
id|area
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|initrd
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|err
op_assign
id|os_file_size
c_func
(paren
id|initrd
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|area
op_assign
id|alloc_bootmem
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|area
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|load_initrd
c_func
(paren
id|initrd
comma
id|area
comma
id|size
)paren
op_eq
op_minus
l_int|1
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|initrd_start
op_assign
(paren
r_int
r_int
)paren
id|area
suffix:semicolon
id|initrd_end
op_assign
id|initrd_start
op_plus
id|size
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|read_initrd
id|__uml_postsetup
c_func
(paren
id|read_initrd
)paren
suffix:semicolon
DECL|function|uml_initrd_setup
r_static
r_int
id|__init
id|uml_initrd_setup
c_func
(paren
r_char
op_star
id|line
comma
r_int
op_star
id|add
)paren
(brace
id|initrd
op_assign
id|line
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|__uml_setup
c_func
(paren
l_string|&quot;initrd=&quot;
comma
id|uml_initrd_setup
comma
l_string|&quot;initrd=&lt;initrd image&gt;&bslash;n&quot;
l_string|&quot;    This is used to boot UML from an initrd image.  The argument is the&bslash;n&quot;
l_string|&quot;    name of the file containing the image.&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
