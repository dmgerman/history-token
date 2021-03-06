multiline_comment|/* $Id: dqueue.c,v 1.5 2003/04/12 21:40:49 schindler Exp $&n; *&n; * Driver for Eicon DIVA Server ISDN cards.&n; * User Mode IDI Interface&n; *&n; * Copyright 2000-2003 by Armin Schindler (mac@melware.de)&n; * Copyright 2000-2003 Cytronics &amp; Melware (info@melware.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; */
macro_line|#include &quot;platform.h&quot;
macro_line|#include &quot;dqueue.h&quot;
r_int
DECL|function|diva_data_q_init
id|diva_data_q_init
c_func
(paren
id|diva_um_idi_data_queue_t
op_star
id|q
comma
r_int
id|max_length
comma
r_int
id|max_segments
)paren
(brace
r_int
id|i
suffix:semicolon
id|q-&gt;max_length
op_assign
id|max_length
suffix:semicolon
id|q-&gt;segments
op_assign
id|max_segments
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
id|q-&gt;segments
suffix:semicolon
id|i
op_increment
)paren
(brace
id|q-&gt;data
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|q-&gt;length
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|q-&gt;read
op_assign
id|q-&gt;write
op_assign
id|q-&gt;count
op_assign
id|q-&gt;segment_pending
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
id|q-&gt;segments
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|q-&gt;data
(braket
id|i
)braket
op_assign
id|diva_os_malloc
c_func
(paren
l_int|0
comma
id|q-&gt;max_length
)paren
)paren
)paren
(brace
id|diva_data_q_finit
c_func
(paren
id|q
)paren
suffix:semicolon
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|diva_data_q_finit
r_int
id|diva_data_q_finit
c_func
(paren
id|diva_um_idi_data_queue_t
op_star
id|q
)paren
(brace
r_int
id|i
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
id|q-&gt;segments
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|q-&gt;data
(braket
id|i
)braket
)paren
(brace
id|diva_os_free
c_func
(paren
l_int|0
comma
id|q-&gt;data
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|q-&gt;data
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|q-&gt;length
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|q-&gt;read
op_assign
id|q-&gt;write
op_assign
id|q-&gt;count
op_assign
id|q-&gt;segment_pending
op_assign
l_int|0
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|diva_data_q_get_max_length
r_int
id|diva_data_q_get_max_length
c_func
(paren
r_const
id|diva_um_idi_data_queue_t
op_star
id|q
)paren
(brace
r_return
(paren
id|q-&gt;max_length
)paren
suffix:semicolon
)brace
DECL|function|diva_data_q_get_segment4write
r_void
op_star
id|diva_data_q_get_segment4write
c_func
(paren
id|diva_um_idi_data_queue_t
op_star
id|q
)paren
(brace
r_if
c_cond
(paren
(paren
op_logical_neg
id|q-&gt;segment_pending
)paren
op_logical_and
(paren
id|q-&gt;count
OL
id|q-&gt;segments
)paren
)paren
(brace
id|q-&gt;segment_pending
op_assign
l_int|1
suffix:semicolon
r_return
(paren
id|q-&gt;data
(braket
id|q-&gt;write
)braket
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_void
DECL|function|diva_data_q_ack_segment4write
id|diva_data_q_ack_segment4write
c_func
(paren
id|diva_um_idi_data_queue_t
op_star
id|q
comma
r_int
id|length
)paren
(brace
r_if
c_cond
(paren
id|q-&gt;segment_pending
)paren
(brace
id|q-&gt;length
(braket
id|q-&gt;write
)braket
op_assign
id|length
suffix:semicolon
id|q-&gt;count
op_increment
suffix:semicolon
id|q-&gt;write
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;write
op_ge
id|q-&gt;segments
)paren
(brace
id|q-&gt;write
op_assign
l_int|0
suffix:semicolon
)brace
id|q-&gt;segment_pending
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|diva_data_q_get_segment4read
r_const
r_void
op_star
id|diva_data_q_get_segment4read
c_func
(paren
r_const
id|diva_um_idi_data_queue_t
op_star
id|q
)paren
(brace
r_if
c_cond
(paren
id|q-&gt;count
)paren
(brace
r_return
(paren
id|q-&gt;data
(braket
id|q-&gt;read
)braket
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|diva_data_q_get_segment_length
r_int
id|diva_data_q_get_segment_length
c_func
(paren
r_const
id|diva_um_idi_data_queue_t
op_star
id|q
)paren
(brace
r_return
(paren
id|q-&gt;length
(braket
id|q-&gt;read
)braket
)paren
suffix:semicolon
)brace
DECL|function|diva_data_q_ack_segment4read
r_void
id|diva_data_q_ack_segment4read
c_func
(paren
id|diva_um_idi_data_queue_t
op_star
id|q
)paren
(brace
r_if
c_cond
(paren
id|q-&gt;count
)paren
(brace
id|q-&gt;length
(braket
id|q-&gt;read
)braket
op_assign
l_int|0
suffix:semicolon
id|q-&gt;count
op_decrement
suffix:semicolon
id|q-&gt;read
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;read
op_ge
id|q-&gt;segments
)paren
(brace
id|q-&gt;read
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
eof
