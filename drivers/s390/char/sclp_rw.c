multiline_comment|/*&n; *  drivers/s390/char/sclp_rw.c&n; *     driver: reading from and writing to system console on S/390 via SCLP&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Peschke &lt;mpeschke@de.ibm.com&gt;&n; *&t;&t; Martin Schwidefsky &lt;schwidefsky@de.ibm.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;sclp.h&quot;
macro_line|#include &quot;sclp_rw.h&quot;
DECL|macro|SCLP_RW_PRINT_HEADER
mdefine_line|#define SCLP_RW_PRINT_HEADER &quot;sclp low level driver: &quot;
multiline_comment|/*&n; * The room for the SCCB (only for writing) is not equal to a pages size&n; * (as it is specified as the maximum size in the the SCLP ducumentation)&n; * because of the additional data structure described above.&n; */
DECL|macro|MAX_SCCB_ROOM
mdefine_line|#define MAX_SCCB_ROOM (PAGE_SIZE - sizeof(struct sclp_buffer))
multiline_comment|/* Event type structure for write message and write priority message */
DECL|variable|sclp_rw_event
r_static
r_struct
id|sclp_register
id|sclp_rw_event
op_assign
(brace
dot
id|send_mask
op_assign
id|EvTyp_Msg_Mask
op_or
id|EvTyp_PMsgCmd_Mask
)brace
suffix:semicolon
multiline_comment|/*&n; * Setup a sclp write buffer. Gets a page as input (4K) and returns&n; * a pointer to a struct sclp_buffer structure that is located at the&n; * end of the input page. This reduces the buffer space by a few&n; * bytes but simplifies things.&n; */
r_struct
id|sclp_buffer
op_star
DECL|function|sclp_make_buffer
id|sclp_make_buffer
c_func
(paren
r_void
op_star
id|page
comma
r_int
r_int
id|columns
comma
r_int
r_int
id|htab
)paren
(brace
r_struct
id|sclp_buffer
op_star
id|buffer
suffix:semicolon
r_struct
id|write_sccb
op_star
id|sccb
suffix:semicolon
id|sccb
op_assign
(paren
r_struct
id|write_sccb
op_star
)paren
id|page
suffix:semicolon
multiline_comment|/*&n;&t; * We keep the struct sclp_buffer structure at the end&n;&t; * of the sccb page.&n;&t; */
id|buffer
op_assign
(paren
(paren
r_struct
id|sclp_buffer
op_star
)paren
(paren
(paren
id|addr_t
)paren
id|sccb
op_plus
id|PAGE_SIZE
)paren
)paren
op_minus
l_int|1
suffix:semicolon
id|buffer-&gt;sccb
op_assign
id|sccb
suffix:semicolon
id|buffer-&gt;retry_count
op_assign
l_int|0
suffix:semicolon
id|buffer-&gt;mto_number
op_assign
l_int|0
suffix:semicolon
id|buffer-&gt;mto_char_sum
op_assign
l_int|0
suffix:semicolon
id|buffer-&gt;current_line
op_assign
l_int|NULL
suffix:semicolon
id|buffer-&gt;current_length
op_assign
l_int|0
suffix:semicolon
id|buffer-&gt;columns
op_assign
id|columns
suffix:semicolon
id|buffer-&gt;htab
op_assign
id|htab
suffix:semicolon
multiline_comment|/* initialize sccb */
id|memset
c_func
(paren
id|sccb
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|write_sccb
)paren
)paren
suffix:semicolon
id|sccb-&gt;header.length
op_assign
r_sizeof
(paren
r_struct
id|write_sccb
)paren
suffix:semicolon
id|sccb-&gt;msg_buf.header.length
op_assign
r_sizeof
(paren
r_struct
id|msg_buf
)paren
suffix:semicolon
id|sccb-&gt;msg_buf.header.type
op_assign
id|EvTyp_Msg
suffix:semicolon
id|sccb-&gt;msg_buf.mdb.header.length
op_assign
r_sizeof
(paren
r_struct
id|mdb
)paren
suffix:semicolon
id|sccb-&gt;msg_buf.mdb.header.type
op_assign
l_int|1
suffix:semicolon
id|sccb-&gt;msg_buf.mdb.header.tag
op_assign
l_int|0xD4C4C240
suffix:semicolon
multiline_comment|/* ebcdic &quot;MDB &quot; */
id|sccb-&gt;msg_buf.mdb.header.revision_code
op_assign
l_int|1
suffix:semicolon
id|sccb-&gt;msg_buf.mdb.go.length
op_assign
r_sizeof
(paren
r_struct
id|go
)paren
suffix:semicolon
id|sccb-&gt;msg_buf.mdb.go.type
op_assign
l_int|1
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
multiline_comment|/*&n; * Return a pointer to the orignal page that has been used to create&n; * the buffer.&n; */
r_void
op_star
DECL|function|sclp_unmake_buffer
id|sclp_unmake_buffer
c_func
(paren
r_struct
id|sclp_buffer
op_star
id|buffer
)paren
(brace
r_return
id|buffer-&gt;sccb
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize a new Message Text Object (MTO) at the end of the provided buffer&n; * with enough room for max_len characters. Return 0 on success.&n; */
r_static
r_int
DECL|function|sclp_initialize_mto
id|sclp_initialize_mto
c_func
(paren
r_struct
id|sclp_buffer
op_star
id|buffer
comma
r_int
id|max_len
)paren
(brace
r_struct
id|write_sccb
op_star
id|sccb
suffix:semicolon
r_struct
id|mto
op_star
id|mto
suffix:semicolon
r_int
id|mto_size
suffix:semicolon
multiline_comment|/* max size of new Message Text Object including message text  */
id|mto_size
op_assign
r_sizeof
(paren
r_struct
id|mto
)paren
op_plus
id|max_len
suffix:semicolon
multiline_comment|/* check if current buffer sccb can contain the mto */
id|sccb
op_assign
id|buffer-&gt;sccb
suffix:semicolon
r_if
c_cond
(paren
(paren
id|MAX_SCCB_ROOM
op_minus
id|sccb-&gt;header.length
)paren
OL
id|mto_size
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* find address of new message text object */
id|mto
op_assign
(paren
r_struct
id|mto
op_star
)paren
(paren
(paren
(paren
id|addr_t
)paren
id|sccb
)paren
op_plus
id|sccb-&gt;header.length
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * fill the new Message-Text Object,&n;&t; * starting behind the former last byte of the SCCB&n;&t; */
id|memset
c_func
(paren
id|mto
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|mto
)paren
)paren
suffix:semicolon
id|mto-&gt;length
op_assign
r_sizeof
(paren
r_struct
id|mto
)paren
suffix:semicolon
id|mto-&gt;type
op_assign
l_int|4
suffix:semicolon
multiline_comment|/* message text object */
id|mto-&gt;line_type_flags
op_assign
id|LnTpFlgs_EndText
suffix:semicolon
multiline_comment|/* end text */
multiline_comment|/* set pointer to first byte after struct mto. */
id|buffer-&gt;current_line
op_assign
(paren
r_char
op_star
)paren
(paren
id|mto
op_plus
l_int|1
)paren
suffix:semicolon
id|buffer-&gt;current_length
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Finalize MTO initialized by sclp_initialize_mto(), updating the sizes of&n; * MTO, enclosing MDB, event buffer and SCCB.&n; */
r_static
r_void
DECL|function|sclp_finalize_mto
id|sclp_finalize_mto
c_func
(paren
r_struct
id|sclp_buffer
op_star
id|buffer
)paren
(brace
r_struct
id|write_sccb
op_star
id|sccb
suffix:semicolon
r_struct
id|mto
op_star
id|mto
suffix:semicolon
r_int
id|str_len
comma
id|mto_size
suffix:semicolon
id|str_len
op_assign
id|buffer-&gt;current_length
suffix:semicolon
id|buffer-&gt;current_line
op_assign
l_int|NULL
suffix:semicolon
id|buffer-&gt;current_length
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* real size of new Message Text Object including message text&t;*/
id|mto_size
op_assign
r_sizeof
(paren
r_struct
id|mto
)paren
op_plus
id|str_len
suffix:semicolon
multiline_comment|/* find address of new message text object */
id|sccb
op_assign
id|buffer-&gt;sccb
suffix:semicolon
id|mto
op_assign
(paren
r_struct
id|mto
op_star
)paren
(paren
(paren
(paren
id|addr_t
)paren
id|sccb
)paren
op_plus
id|sccb-&gt;header.length
)paren
suffix:semicolon
multiline_comment|/* set size of message text object */
id|mto-&gt;length
op_assign
id|mto_size
suffix:semicolon
multiline_comment|/*&n;&t; * update values of sizes&n;&t; * (SCCB, Event(Message) Buffer, Message Data Block)&n;&t; */
id|sccb-&gt;header.length
op_add_assign
id|mto_size
suffix:semicolon
id|sccb-&gt;msg_buf.header.length
op_add_assign
id|mto_size
suffix:semicolon
id|sccb-&gt;msg_buf.mdb.header.length
op_add_assign
id|mto_size
suffix:semicolon
multiline_comment|/*&n;&t; * count number of buffered messages (= number of Message Text&n;&t; * Objects) and number of buffered characters&n;&t; * for the SCCB currently used for buffering and at all&n;&t; */
id|buffer-&gt;mto_number
op_increment
suffix:semicolon
id|buffer-&gt;mto_char_sum
op_add_assign
id|str_len
suffix:semicolon
)brace
multiline_comment|/*&n; * processing of a message including escape characters,&n; * returns number of characters written to the output sccb&n; * (&quot;processed&quot; means that is not guaranteed that the character have already&n; *  been sent to the SCLP but that it will be done at least next time the SCLP&n; *  is not busy)&n; */
r_int
DECL|function|sclp_write
id|sclp_write
c_func
(paren
r_struct
id|sclp_buffer
op_star
id|buffer
comma
r_const
r_int
r_char
op_star
id|msg
comma
r_int
id|count
)paren
(brace
r_int
id|spaces
comma
id|i_msg
suffix:semicolon
r_int
id|rc
suffix:semicolon
multiline_comment|/*&n;&t; * parse msg for escape sequences (&bslash;t,&bslash;v ...) and put formated&n;&t; * msg into an mto (created by sclp_initialize_mto).&n;&t; *&n;&t; * We have to do this work ourselfs because there is no support for&n;&t; * these characters on the native machine and only partial support&n;&t; * under VM (Why does VM interpret &bslash;n but the native machine doesn&squot;t ?)&n;&t; *&n;&t; * Depending on i/o-control setting the message is always written&n;&t; * immediately or we wait for a final new line maybe coming with the&n;&t; * next message. Besides we avoid a buffer overrun by writing its&n;&t; * content.&n;&t; *&n;&t; * RESTRICTIONS:&n;&t; *&n;&t; * &bslash;r and &bslash;b work within one line because we are not able to modify&n;&t; * previous output that have already been accepted by the SCLP.&n;&t; *&n;&t; * &bslash;t combined with following &bslash;r is not correctly represented because&n;&t; * &bslash;t is expanded to some spaces but &bslash;r does not know about a&n;&t; * previous &bslash;t and decreases the current position by one column.&n;&t; * This is in order to a slim and quick implementation.&n;&t; */
r_for
c_loop
(paren
id|i_msg
op_assign
l_int|0
suffix:semicolon
id|i_msg
OL
id|count
suffix:semicolon
id|i_msg
op_increment
)paren
(brace
r_switch
c_cond
(paren
id|msg
(braket
id|i_msg
)braket
)paren
(brace
r_case
l_char|&squot;&bslash;n&squot;
suffix:colon
multiline_comment|/* new line, line feed (ASCII)&t;*/
multiline_comment|/* check if new mto needs to be created */
r_if
c_cond
(paren
id|buffer-&gt;current_line
op_eq
l_int|NULL
)paren
(brace
id|rc
op_assign
id|sclp_initialize_mto
c_func
(paren
id|buffer
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|i_msg
suffix:semicolon
)brace
id|sclp_finalize_mto
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;a&squot;
suffix:colon
multiline_comment|/* bell, one for several times&t;*/
multiline_comment|/* set SCLP sound alarm bit in General Object */
id|buffer-&gt;sccb-&gt;msg_buf.mdb.go.general_msg_flags
op_or_assign
id|GnrlMsgFlgs_SndAlrm
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;t&squot;
suffix:colon
multiline_comment|/* horizontal tabulator&t; */
multiline_comment|/* check if new mto needs to be created */
r_if
c_cond
(paren
id|buffer-&gt;current_line
op_eq
l_int|NULL
)paren
(brace
id|rc
op_assign
id|sclp_initialize_mto
c_func
(paren
id|buffer
comma
id|buffer-&gt;columns
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|i_msg
suffix:semicolon
)brace
multiline_comment|/* &quot;go to (next htab-boundary + 1, same line)&quot; */
r_do
(brace
r_if
c_cond
(paren
id|buffer-&gt;current_length
op_ge
id|buffer-&gt;columns
)paren
r_break
suffix:semicolon
multiline_comment|/* ok, add a blank */
op_star
id|buffer-&gt;current_line
op_increment
op_assign
l_int|0x40
suffix:semicolon
id|buffer-&gt;current_length
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|buffer-&gt;current_length
op_mod
id|buffer-&gt;htab
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;f&squot;
suffix:colon
multiline_comment|/* form feed  */
r_case
l_char|&squot;&bslash;v&squot;
suffix:colon
multiline_comment|/* vertical tabulator  */
multiline_comment|/* &quot;go to (actual column, actual line + 1)&quot; */
multiline_comment|/* = new line, leading spaces */
r_if
c_cond
(paren
id|buffer-&gt;current_line
op_ne
l_int|NULL
)paren
(brace
id|spaces
op_assign
id|buffer-&gt;current_length
suffix:semicolon
id|sclp_finalize_mto
c_func
(paren
id|buffer
)paren
suffix:semicolon
id|rc
op_assign
id|sclp_initialize_mto
c_func
(paren
id|buffer
comma
id|buffer-&gt;columns
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|i_msg
suffix:semicolon
id|memset
c_func
(paren
id|buffer-&gt;current_line
comma
l_int|0x40
comma
id|spaces
)paren
suffix:semicolon
id|buffer-&gt;current_line
op_add_assign
id|spaces
suffix:semicolon
id|buffer-&gt;current_length
op_assign
id|spaces
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* one an empty line this is the same as &bslash;n */
id|rc
op_assign
id|sclp_initialize_mto
c_func
(paren
id|buffer
comma
id|buffer-&gt;columns
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|i_msg
suffix:semicolon
id|sclp_finalize_mto
c_func
(paren
id|buffer
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;b&squot;
suffix:colon
multiline_comment|/* backspace  */
multiline_comment|/* &quot;go to (actual column - 1, actual line)&quot; */
multiline_comment|/* decrement counter indicating position, */
multiline_comment|/* do not remove last character */
r_if
c_cond
(paren
id|buffer-&gt;current_line
op_ne
l_int|NULL
op_logical_and
id|buffer-&gt;current_length
OG
l_int|0
)paren
(brace
id|buffer-&gt;current_length
op_decrement
suffix:semicolon
id|buffer-&gt;current_line
op_decrement
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|0x00
suffix:colon
multiline_comment|/* end of string  */
multiline_comment|/* transfer current line to SCCB */
r_if
c_cond
(paren
id|buffer-&gt;current_line
op_ne
l_int|NULL
)paren
id|sclp_finalize_mto
c_func
(paren
id|buffer
)paren
suffix:semicolon
multiline_comment|/* skip the rest of the message including the 0 byte */
id|i_msg
op_assign
id|count
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
multiline_comment|/* no escape character&t;*/
multiline_comment|/* do not output unprintable characters */
r_if
c_cond
(paren
op_logical_neg
id|isprint
c_func
(paren
id|msg
(braket
id|i_msg
)braket
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* check if new mto needs to be created */
r_if
c_cond
(paren
id|buffer-&gt;current_line
op_eq
l_int|NULL
)paren
(brace
id|rc
op_assign
id|sclp_initialize_mto
c_func
(paren
id|buffer
comma
id|buffer-&gt;columns
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|i_msg
suffix:semicolon
)brace
op_star
id|buffer-&gt;current_line
op_increment
op_assign
id|sclp_ascebc
c_func
(paren
id|msg
(braket
id|i_msg
)braket
)paren
suffix:semicolon
id|buffer-&gt;current_length
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* check if current mto is full */
r_if
c_cond
(paren
id|buffer-&gt;current_line
op_ne
l_int|NULL
op_logical_and
id|buffer-&gt;current_length
op_ge
id|buffer-&gt;columns
)paren
id|sclp_finalize_mto
c_func
(paren
id|buffer
)paren
suffix:semicolon
)brace
multiline_comment|/* return number of processed characters */
r_return
id|i_msg
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the number of free bytes in the sccb&n; */
r_int
DECL|function|sclp_buffer_space
id|sclp_buffer_space
c_func
(paren
r_struct
id|sclp_buffer
op_star
id|buffer
)paren
(brace
r_int
id|count
suffix:semicolon
id|count
op_assign
id|MAX_SCCB_ROOM
op_minus
id|buffer-&gt;sccb-&gt;header.length
suffix:semicolon
r_if
c_cond
(paren
id|buffer-&gt;current_line
op_ne
l_int|NULL
)paren
id|count
op_sub_assign
r_sizeof
(paren
r_struct
id|mto
)paren
op_plus
id|buffer-&gt;current_length
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * Return number of characters in buffer&n; */
r_int
DECL|function|sclp_chars_in_buffer
id|sclp_chars_in_buffer
c_func
(paren
r_struct
id|sclp_buffer
op_star
id|buffer
)paren
(brace
r_int
id|count
suffix:semicolon
id|count
op_assign
id|buffer-&gt;mto_char_sum
suffix:semicolon
r_if
c_cond
(paren
id|buffer-&gt;current_line
op_ne
l_int|NULL
)paren
id|count
op_add_assign
id|buffer-&gt;current_length
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * sets or provides some values that influence the drivers behaviour&n; */
r_void
DECL|function|sclp_set_columns
id|sclp_set_columns
c_func
(paren
r_struct
id|sclp_buffer
op_star
id|buffer
comma
r_int
r_int
id|columns
)paren
(brace
id|buffer-&gt;columns
op_assign
id|columns
suffix:semicolon
r_if
c_cond
(paren
id|buffer-&gt;current_line
op_ne
l_int|NULL
op_logical_and
id|buffer-&gt;current_length
OG
id|buffer-&gt;columns
)paren
id|sclp_finalize_mto
c_func
(paren
id|buffer
)paren
suffix:semicolon
)brace
r_void
DECL|function|sclp_set_htab
id|sclp_set_htab
c_func
(paren
r_struct
id|sclp_buffer
op_star
id|buffer
comma
r_int
r_int
id|htab
)paren
(brace
id|buffer-&gt;htab
op_assign
id|htab
suffix:semicolon
)brace
multiline_comment|/*&n; * called by sclp_console_init and/or sclp_tty_init&n; */
r_int
DECL|function|sclp_rw_init
id|sclp_rw_init
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|init_done
op_assign
l_int|0
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|init_done
)paren
r_return
l_int|0
suffix:semicolon
id|rc
op_assign
id|sclp_register
c_func
(paren
op_amp
id|sclp_rw_event
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
id|init_done
op_assign
l_int|1
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|macro|SCLP_BUFFER_MAX_RETRY
mdefine_line|#define SCLP_BUFFER_MAX_RETRY&t;&t;1
multiline_comment|/*&n; * second half of Write Event Data-function that has to be done after&n; * interruption indicating completion of Service Call.&n; */
r_static
r_void
DECL|function|sclp_writedata_callback
id|sclp_writedata_callback
c_func
(paren
r_struct
id|sclp_req
op_star
id|request
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|rc
suffix:semicolon
r_struct
id|sclp_buffer
op_star
id|buffer
suffix:semicolon
r_struct
id|write_sccb
op_star
id|sccb
suffix:semicolon
id|buffer
op_assign
(paren
r_struct
id|sclp_buffer
op_star
)paren
id|data
suffix:semicolon
id|sccb
op_assign
id|buffer-&gt;sccb
suffix:semicolon
r_if
c_cond
(paren
id|request-&gt;status
op_eq
id|SCLP_REQ_FAILED
)paren
(brace
r_if
c_cond
(paren
id|buffer-&gt;callback
op_ne
l_int|NULL
)paren
id|buffer
op_member_access_from_pointer
id|callback
c_func
(paren
id|buffer
comma
op_minus
id|EIO
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* check SCLP response code and choose suitable action&t;*/
r_switch
c_cond
(paren
id|sccb-&gt;header.response_code
)paren
(brace
r_case
l_int|0x0020
suffix:colon
multiline_comment|/* Normal completion, buffer processed, message(s) sent */
id|rc
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0340
suffix:colon
multiline_comment|/* Contained SCLP equipment check */
r_if
c_cond
(paren
op_increment
id|buffer-&gt;retry_count
OG
id|SCLP_BUFFER_MAX_RETRY
)paren
(brace
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* remove processed buffers and requeue rest */
r_if
c_cond
(paren
id|sclp_remove_processed
c_func
(paren
(paren
r_struct
id|sccb_header
op_star
)paren
id|sccb
)paren
OG
l_int|0
)paren
(brace
multiline_comment|/* not all buffers were processed */
id|sccb-&gt;header.response_code
op_assign
l_int|0x0000
suffix:semicolon
id|buffer-&gt;request.status
op_assign
id|SCLP_REQ_FILLED
suffix:semicolon
id|rc
op_assign
id|sclp_add_request
c_func
(paren
id|request
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
r_return
suffix:semicolon
)brace
r_else
id|rc
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0040
suffix:colon
multiline_comment|/* SCLP equipment check */
r_case
l_int|0x05f0
suffix:colon
multiline_comment|/* Target resource in improper state */
r_if
c_cond
(paren
op_increment
id|buffer-&gt;retry_count
OG
id|SCLP_BUFFER_MAX_RETRY
)paren
(brace
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* retry request */
id|sccb-&gt;header.response_code
op_assign
l_int|0x0000
suffix:semicolon
id|buffer-&gt;request.status
op_assign
id|SCLP_REQ_FILLED
suffix:semicolon
id|rc
op_assign
id|sclp_add_request
c_func
(paren
id|request
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
r_return
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|sccb-&gt;header.response_code
op_eq
l_int|0x71f0
)paren
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_else
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|buffer-&gt;callback
op_ne
l_int|NULL
)paren
id|buffer
op_member_access_from_pointer
id|callback
c_func
(paren
id|buffer
comma
id|rc
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Setup the request structure in the struct sclp_buffer to do SCLP Write&n; * Event Data and pass the request to the core SCLP loop. Return zero on&n; * success, non-zero otherwise.&n; */
r_int
DECL|function|sclp_emit_buffer
id|sclp_emit_buffer
c_func
(paren
r_struct
id|sclp_buffer
op_star
id|buffer
comma
r_void
(paren
op_star
id|callback
)paren
(paren
r_struct
id|sclp_buffer
op_star
comma
r_int
)paren
)paren
(brace
r_struct
id|write_sccb
op_star
id|sccb
suffix:semicolon
multiline_comment|/* add current line if there is one */
r_if
c_cond
(paren
id|buffer-&gt;current_line
op_ne
l_int|NULL
)paren
id|sclp_finalize_mto
c_func
(paren
id|buffer
)paren
suffix:semicolon
multiline_comment|/* Are there messages in the output buffer ? */
r_if
c_cond
(paren
id|buffer-&gt;mto_number
op_eq
l_int|0
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|sccb
op_assign
id|buffer-&gt;sccb
suffix:semicolon
r_if
c_cond
(paren
id|sclp_rw_event.sclp_send_mask
op_amp
id|EvTyp_Msg_Mask
)paren
multiline_comment|/* Use normal write message */
id|sccb-&gt;msg_buf.header.type
op_assign
id|EvTyp_Msg
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sclp_rw_event.sclp_send_mask
op_amp
id|EvTyp_PMsgCmd_Mask
)paren
multiline_comment|/* Use write priority message */
id|sccb-&gt;msg_buf.header.type
op_assign
id|EvTyp_PMsgCmd
suffix:semicolon
r_else
r_return
op_minus
id|ENOSYS
suffix:semicolon
id|buffer-&gt;request.command
op_assign
id|SCLP_CMDW_WRITEDATA
suffix:semicolon
id|buffer-&gt;request.status
op_assign
id|SCLP_REQ_FILLED
suffix:semicolon
id|buffer-&gt;request.callback
op_assign
id|sclp_writedata_callback
suffix:semicolon
id|buffer-&gt;request.callback_data
op_assign
id|buffer
suffix:semicolon
id|buffer-&gt;request.sccb
op_assign
id|sccb
suffix:semicolon
id|buffer-&gt;callback
op_assign
id|callback
suffix:semicolon
r_return
id|sclp_add_request
c_func
(paren
op_amp
id|buffer-&gt;request
)paren
suffix:semicolon
)brace
eof
