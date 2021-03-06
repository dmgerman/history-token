multiline_comment|/* -*- linux-c -*- ------------------------------------------------------- *&n; *&n; *   Copyright 2002 H. Peter Anvin - All Rights Reserved&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation, Inc., 53 Temple Place Ste 330,&n; *   Bostom MA 02111-1307, USA; either version 2 of the License, or&n; *   (at your option) any later version; incorporated herein by reference.&n; *&n; * ----------------------------------------------------------------------- */
multiline_comment|/*&n; * raid6test.c&n; *&n; * Test RAID-6 recovery with various algorithms&n; */
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &quot;raid6.h&quot;
DECL|macro|NDISKS
mdefine_line|#define NDISKS&t;&t;16&t;/* Including P and Q */
DECL|variable|raid6_empty_zero_page
r_const
r_char
id|raid6_empty_zero_page
(braket
id|PAGE_SIZE
)braket
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|256
)paren
)paren
)paren
suffix:semicolon
DECL|variable|raid6_call
r_struct
id|raid6_calls
id|raid6_call
suffix:semicolon
DECL|variable|dataptrs
r_char
op_star
id|dataptrs
(braket
id|NDISKS
)braket
suffix:semicolon
DECL|variable|data
r_char
id|data
(braket
id|NDISKS
)braket
(braket
id|PAGE_SIZE
)braket
suffix:semicolon
DECL|variable|recovi
DECL|variable|recovj
r_char
id|recovi
(braket
id|PAGE_SIZE
)braket
comma
id|recovj
(braket
id|PAGE_SIZE
)braket
suffix:semicolon
DECL|function|makedata
r_void
id|makedata
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|j
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
id|NDISKS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|PAGE_SIZE
suffix:semicolon
id|j
op_increment
)paren
(brace
id|data
(braket
id|i
)braket
(braket
id|j
)braket
op_assign
id|rand
c_func
(paren
)paren
suffix:semicolon
)brace
id|dataptrs
(braket
id|i
)braket
op_assign
id|data
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
id|argv
(braket
)braket
)paren
(brace
r_const
r_struct
id|raid6_calls
op_star
r_const
op_star
id|algo
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_int
id|erra
comma
id|errb
suffix:semicolon
id|makedata
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|algo
op_assign
id|raid6_algos
suffix:semicolon
op_star
id|algo
suffix:semicolon
id|algo
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|algo
)paren
op_member_access_from_pointer
id|valid
op_logical_or
(paren
op_star
id|algo
)paren
op_member_access_from_pointer
id|valid
c_func
(paren
)paren
)paren
(brace
id|raid6_call
op_assign
op_star
op_star
id|algo
suffix:semicolon
multiline_comment|/* Nuke syndromes */
id|memset
c_func
(paren
id|data
(braket
id|NDISKS
op_minus
l_int|2
)braket
comma
l_int|0xee
comma
l_int|2
op_star
id|PAGE_SIZE
)paren
suffix:semicolon
multiline_comment|/* Generate assumed good syndrome */
id|raid6_call
dot
id|gen_syndrome
c_func
(paren
id|NDISKS
comma
id|PAGE_SIZE
comma
(paren
r_void
op_star
op_star
)paren
op_amp
id|dataptrs
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
id|NDISKS
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
id|j
OL
id|NDISKS
suffix:semicolon
id|j
op_increment
)paren
(brace
id|memset
c_func
(paren
id|recovi
comma
l_int|0xf0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|memset
c_func
(paren
id|recovj
comma
l_int|0xba
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|dataptrs
(braket
id|i
)braket
op_assign
id|recovi
suffix:semicolon
id|dataptrs
(braket
id|j
)braket
op_assign
id|recovj
suffix:semicolon
id|raid6_dual_recov
c_func
(paren
id|NDISKS
comma
id|PAGE_SIZE
comma
id|i
comma
id|j
comma
(paren
r_void
op_star
op_star
)paren
op_amp
id|dataptrs
)paren
suffix:semicolon
id|erra
op_assign
id|memcmp
c_func
(paren
id|data
(braket
id|i
)braket
comma
id|recovi
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|errb
op_assign
id|memcmp
c_func
(paren
id|data
(braket
id|j
)braket
comma
id|recovj
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|NDISKS
op_minus
l_int|2
op_logical_and
id|j
op_eq
id|NDISKS
op_minus
l_int|1
)paren
(brace
multiline_comment|/* We don&squot;t implement the DQ failure scenario, since it&squot;s&n;&t;&t;&t;&t;&t;&t;   equivalent to a RAID-5 failure (XOR, then recompute Q) */
)brace
r_else
(brace
id|printf
c_func
(paren
l_string|&quot;algo=%-8s  faila=%3d(%c)  failb=%3d(%c)  %s&bslash;n&quot;
comma
id|raid6_call.name
comma
id|i
comma
(paren
id|i
op_eq
id|NDISKS
op_minus
l_int|2
)paren
ques
c_cond
l_char|&squot;P&squot;
suffix:colon
l_char|&squot;D&squot;
comma
id|j
comma
(paren
id|j
op_eq
id|NDISKS
op_minus
l_int|1
)paren
ques
c_cond
l_char|&squot;Q&squot;
suffix:colon
(paren
id|j
op_eq
id|NDISKS
op_minus
l_int|2
)paren
ques
c_cond
l_char|&squot;P&squot;
suffix:colon
l_char|&squot;D&squot;
comma
(paren
op_logical_neg
id|erra
op_logical_and
op_logical_neg
id|errb
)paren
ques
c_cond
l_string|&quot;OK&quot;
suffix:colon
op_logical_neg
id|erra
ques
c_cond
l_string|&quot;ERRB&quot;
suffix:colon
op_logical_neg
id|errb
ques
c_cond
l_string|&quot;ERRA&quot;
suffix:colon
l_string|&quot;ERRAB&quot;
)paren
suffix:semicolon
)brace
id|dataptrs
(braket
id|i
)braket
op_assign
id|data
(braket
id|i
)braket
suffix:semicolon
id|dataptrs
(braket
id|j
)braket
op_assign
id|data
(braket
id|j
)braket
suffix:semicolon
)brace
)brace
)brace
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Pick the best algorithm test */
id|raid6_select_algo
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
