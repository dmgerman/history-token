multiline_comment|/*&n; * hack-coff.c - hack the header of an xcoff file to fill in&n; * a few fields needed by the Open Firmware xcoff loader on&n; * Power Macs but not initialized by objcopy.&n; *&n; * Copyright (C) Paul Mackerras 1997.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &quot;rs6000.h&quot;
DECL|macro|AOUT_MAGIC
mdefine_line|#define AOUT_MAGIC&t;0x010b
DECL|macro|get_16be
mdefine_line|#define get_16be(x)&t;((((unsigned char *)(x))[0] &lt;&lt; 8) &bslash;&n;&t;&t;&t; + ((unsigned char *)(x))[1])
DECL|macro|put_16be
mdefine_line|#define put_16be(x, v)&t;(((unsigned char *)(x))[0] = (v) &gt;&gt; 8, &bslash;&n;&t;&t;&t; ((unsigned char *)(x))[1] = (v) &amp; 0xff)
DECL|macro|get_32be
mdefine_line|#define get_32be(x)&t;((((unsigned char *)(x))[0] &lt;&lt; 24) &bslash;&n;&t;&t;&t; + (((unsigned char *)(x))[1] &lt;&lt; 16) &bslash;&n;&t;&t;&t; + (((unsigned char *)(x))[2] &lt;&lt; 8) &bslash;&n;&t;&t;&t; + ((unsigned char *)(x))[3])
r_int
DECL|function|main
id|main
c_func
(paren
r_int
id|ac
comma
r_char
op_star
op_star
id|av
)paren
(brace
r_int
id|fd
suffix:semicolon
r_int
id|i
comma
id|nsect
suffix:semicolon
r_int
id|aoutsz
suffix:semicolon
r_struct
id|external_filehdr
id|fhdr
suffix:semicolon
id|AOUTHDR
id|aout
suffix:semicolon
r_struct
id|external_scnhdr
id|shdr
suffix:semicolon
r_if
c_cond
(paren
id|ac
op_ne
l_int|2
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Usage: hack-coff coff-file&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|fd
op_assign
id|open
c_func
(paren
id|av
(braket
l_int|1
)braket
comma
l_int|2
)paren
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|perror
c_func
(paren
id|av
(braket
l_int|2
)braket
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|read
c_func
(paren
id|fd
comma
op_amp
id|fhdr
comma
r_sizeof
(paren
id|fhdr
)paren
)paren
op_ne
r_sizeof
(paren
id|fhdr
)paren
)paren
r_goto
id|readerr
suffix:semicolon
id|i
op_assign
id|get_16be
c_func
(paren
id|fhdr.f_magic
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
id|U802TOCMAGIC
op_logical_and
id|i
op_ne
id|U802WRMAGIC
op_logical_and
id|i
op_ne
id|U802ROMAGIC
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: not an xcoff file&bslash;n&quot;
comma
id|av
(braket
l_int|1
)braket
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|aoutsz
op_assign
id|get_16be
c_func
(paren
id|fhdr.f_opthdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read
c_func
(paren
id|fd
comma
op_amp
id|aout
comma
id|aoutsz
)paren
op_ne
id|aoutsz
)paren
r_goto
id|readerr
suffix:semicolon
id|nsect
op_assign
id|get_16be
c_func
(paren
id|fhdr.f_nscns
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
id|nsect
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|read
c_func
(paren
id|fd
comma
op_amp
id|shdr
comma
r_sizeof
(paren
id|shdr
)paren
)paren
op_ne
r_sizeof
(paren
id|shdr
)paren
)paren
r_goto
id|readerr
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|shdr.s_name
comma
l_string|&quot;.text&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|put_16be
c_func
(paren
id|aout.o_snentry
comma
id|i
op_plus
l_int|1
)paren
suffix:semicolon
id|put_16be
c_func
(paren
id|aout.o_sntext
comma
id|i
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|shdr.s_name
comma
l_string|&quot;.data&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|put_16be
c_func
(paren
id|aout.o_sndata
comma
id|i
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|shdr.s_name
comma
l_string|&quot;.bss&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|put_16be
c_func
(paren
id|aout.o_snbss
comma
id|i
op_plus
l_int|1
)paren
suffix:semicolon
)brace
)brace
id|put_16be
c_func
(paren
id|aout.magic
comma
id|AOUT_MAGIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lseek
c_func
(paren
id|fd
comma
(paren
r_int
)paren
r_sizeof
(paren
r_struct
id|external_filehdr
)paren
comma
l_int|0
)paren
op_eq
op_minus
l_int|1
op_logical_or
id|write
c_func
(paren
id|fd
comma
op_amp
id|aout
comma
id|aoutsz
)paren
op_ne
id|aoutsz
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: write error&bslash;n&quot;
comma
id|av
(braket
l_int|1
)braket
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
m_exit
(paren
l_int|0
)paren
suffix:semicolon
id|readerr
suffix:colon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: read error or file too short&bslash;n&quot;
comma
id|av
(braket
l_int|1
)braket
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
eof
