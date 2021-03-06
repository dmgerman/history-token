multiline_comment|/*&n; *  drivers/s390/char/raw3270.h&n; *    IBM/3270 Driver&n; *&n; *  Author(s):&n; *    Original 3270 Code for 2.4 written by Richard Hitt (UTS Global)&n; *    Rewritten for 2.5 by Martin Schwidefsky &lt;schwidefsky@de.ibm.com&gt;&n; *&t;-- Copyright (C) 2003 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; */
macro_line|#include &lt;asm/idals.h&gt;
macro_line|#include &lt;asm/ioctl.h&gt;
multiline_comment|/* ioctls for fullscreen 3270 */
DECL|macro|TUBICMD
mdefine_line|#define TUBICMD&t;&t;_IO(&squot;3&squot;, 3)&t;/* set ccw command for fs reads. */
DECL|macro|TUBOCMD
mdefine_line|#define TUBOCMD&t;&t;_IO(&squot;3&squot;, 4)&t;/* set ccw command for fs writes. */
DECL|macro|TUBGETI
mdefine_line|#define TUBGETI&t;&t;_IO(&squot;3&squot;, 7)&t;/* get ccw command for fs reads. */
DECL|macro|TUBGETO
mdefine_line|#define TUBGETO&t;&t;_IO(&squot;3&squot;, 8)&t;/* get ccw command for fs writes. */
DECL|macro|TUBSETMOD
mdefine_line|#define TUBSETMOD&t;_IO(&squot;3&squot;,12)&t;/* FIXME: what does it do ?*/
DECL|macro|TUBGETMOD
mdefine_line|#define TUBGETMOD&t;_IO(&squot;3&squot;,13)&t;/* FIXME: what does it do ?*/
multiline_comment|/* Local Channel Commands */
DECL|macro|TC_WRITE
mdefine_line|#define TC_WRITE&t;0x01&t;&t;/* Write */
DECL|macro|TC_EWRITE
mdefine_line|#define TC_EWRITE&t;0x05&t;&t;/* Erase write */
DECL|macro|TC_READMOD
mdefine_line|#define TC_READMOD&t;0x06&t;&t;/* Read modified */
DECL|macro|TC_EWRITEA
mdefine_line|#define TC_EWRITEA&t;0x0d&t;&t;/* Erase write alternate */
DECL|macro|TC_WRITESF
mdefine_line|#define TC_WRITESF&t;0x11&t;&t;/* Write structured field */
multiline_comment|/* Buffer Control Orders */
DECL|macro|TO_SF
mdefine_line|#define TO_SF&t;&t;0x1d&t;&t;/* Start field */
DECL|macro|TO_SBA
mdefine_line|#define TO_SBA&t;&t;0x11&t;&t;/* Set buffer address */
DECL|macro|TO_IC
mdefine_line|#define TO_IC&t;&t;0x13&t;&t;/* Insert cursor */
DECL|macro|TO_PT
mdefine_line|#define TO_PT&t;&t;0x05&t;&t;/* Program tab */
DECL|macro|TO_RA
mdefine_line|#define TO_RA&t;&t;0x3c&t;&t;/* Repeat to address */
DECL|macro|TO_SFE
mdefine_line|#define TO_SFE&t;&t;0x29&t;&t;/* Start field extended */
DECL|macro|TO_EUA
mdefine_line|#define TO_EUA&t;&t;0x12&t;&t;/* Erase unprotected to address */
DECL|macro|TO_MF
mdefine_line|#define TO_MF&t;&t;0x2c&t;&t;/* Modify field */
DECL|macro|TO_SA
mdefine_line|#define TO_SA&t;&t;0x28&t;&t;/* Set attribute */
multiline_comment|/* Field Attribute Bytes */
DECL|macro|TF_INPUT
mdefine_line|#define TF_INPUT&t;0x40&t;&t;/* Visible input */
DECL|macro|TF_INPUTN
mdefine_line|#define TF_INPUTN&t;0x4c&t;&t;/* Invisible input */
DECL|macro|TF_INMDT
mdefine_line|#define TF_INMDT&t;0xc1&t;&t;/* Visible, Set-MDT */
DECL|macro|TF_LOG
mdefine_line|#define TF_LOG&t;&t;0x60
multiline_comment|/* Character Attribute Bytes */
DECL|macro|TAT_RESET
mdefine_line|#define TAT_RESET&t;0x00
DECL|macro|TAT_FIELD
mdefine_line|#define TAT_FIELD&t;0xc0
DECL|macro|TAT_EXTHI
mdefine_line|#define TAT_EXTHI&t;0x41
DECL|macro|TAT_COLOR
mdefine_line|#define TAT_COLOR&t;0x42
DECL|macro|TAT_CHARS
mdefine_line|#define TAT_CHARS&t;0x43
DECL|macro|TAT_TRANS
mdefine_line|#define TAT_TRANS&t;0x46
multiline_comment|/* Extended-Highlighting Bytes */
DECL|macro|TAX_RESET
mdefine_line|#define TAX_RESET&t;0x00
DECL|macro|TAX_BLINK
mdefine_line|#define TAX_BLINK&t;0xf1
DECL|macro|TAX_REVER
mdefine_line|#define TAX_REVER&t;0xf2
DECL|macro|TAX_UNDER
mdefine_line|#define TAX_UNDER&t;0xf4
multiline_comment|/* Reset value */
DECL|macro|TAR_RESET
mdefine_line|#define TAR_RESET&t;0x00
multiline_comment|/* Color values */
DECL|macro|TAC_RESET
mdefine_line|#define TAC_RESET&t;0x00
DECL|macro|TAC_BLUE
mdefine_line|#define TAC_BLUE&t;0xf1
DECL|macro|TAC_RED
mdefine_line|#define TAC_RED&t;&t;0xf2
DECL|macro|TAC_PINK
mdefine_line|#define TAC_PINK&t;0xf3
DECL|macro|TAC_GREEN
mdefine_line|#define TAC_GREEN&t;0xf4
DECL|macro|TAC_TURQ
mdefine_line|#define TAC_TURQ&t;0xf5
DECL|macro|TAC_YELLOW
mdefine_line|#define TAC_YELLOW&t;0xf6
DECL|macro|TAC_WHITE
mdefine_line|#define TAC_WHITE&t;0xf7
DECL|macro|TAC_DEFAULT
mdefine_line|#define TAC_DEFAULT&t;0x00
multiline_comment|/* Write Control Characters */
DECL|macro|TW_NONE
mdefine_line|#define TW_NONE&t;&t;0x40&t;&t;/* No particular action */
DECL|macro|TW_KR
mdefine_line|#define TW_KR&t;&t;0xc2&t;&t;/* Keyboard restore */
DECL|macro|TW_PLUSALARM
mdefine_line|#define TW_PLUSALARM&t;0x04&t;&t;/* Add this bit for alarm */
DECL|macro|RAW3270_MAXDEVS
mdefine_line|#define RAW3270_MAXDEVS&t;256
multiline_comment|/* For TUBGETMOD and TUBSETMOD. Should include. */
DECL|struct|raw3270_iocb
r_struct
id|raw3270_iocb
(brace
DECL|member|model
r_int
id|model
suffix:semicolon
DECL|member|line_cnt
r_int
id|line_cnt
suffix:semicolon
DECL|member|col_cnt
r_int
id|col_cnt
suffix:semicolon
DECL|member|pf_cnt
r_int
id|pf_cnt
suffix:semicolon
DECL|member|re_cnt
r_int
id|re_cnt
suffix:semicolon
DECL|member|map
r_int
id|map
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|raw3270
suffix:semicolon
r_struct
id|raw3270_view
suffix:semicolon
multiline_comment|/* 3270 CCW request */
DECL|struct|raw3270_request
r_struct
id|raw3270_request
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* list head for request queueing. */
DECL|member|view
r_struct
id|raw3270_view
op_star
id|view
suffix:semicolon
multiline_comment|/* view of this request */
DECL|member|ccw
r_struct
id|ccw1
id|ccw
suffix:semicolon
multiline_comment|/* single ccw. */
DECL|member|buffer
r_void
op_star
id|buffer
suffix:semicolon
multiline_comment|/* output buffer. */
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* size of output buffer. */
DECL|member|rescnt
r_int
id|rescnt
suffix:semicolon
multiline_comment|/* residual count from devstat. */
DECL|member|rc
r_int
id|rc
suffix:semicolon
multiline_comment|/* return code for this request. */
multiline_comment|/* Callback for delivering final status. */
DECL|member|callback
r_void
(paren
op_star
id|callback
)paren
(paren
r_struct
id|raw3270_request
op_star
comma
r_void
op_star
)paren
suffix:semicolon
DECL|member|callback_data
r_void
op_star
id|callback_data
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|raw3270_request
op_star
id|raw3270_request_alloc
c_func
(paren
r_int
id|size
)paren
suffix:semicolon
r_struct
id|raw3270_request
op_star
id|raw3270_request_alloc_bootmem
c_func
(paren
r_int
id|size
)paren
suffix:semicolon
r_void
id|raw3270_request_free
c_func
(paren
r_struct
id|raw3270_request
op_star
)paren
suffix:semicolon
r_void
id|raw3270_request_reset
c_func
(paren
r_struct
id|raw3270_request
op_star
)paren
suffix:semicolon
r_void
id|raw3270_request_set_cmd
c_func
(paren
r_struct
id|raw3270_request
op_star
comma
id|u8
id|cmd
)paren
suffix:semicolon
r_int
id|raw3270_request_add_data
c_func
(paren
r_struct
id|raw3270_request
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|raw3270_request_set_data
c_func
(paren
r_struct
id|raw3270_request
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|raw3270_request_set_idal
c_func
(paren
r_struct
id|raw3270_request
op_star
comma
r_struct
id|idal_buffer
op_star
)paren
suffix:semicolon
r_static
r_inline
r_int
DECL|function|raw3270_request_final
id|raw3270_request_final
c_func
(paren
r_struct
id|raw3270_request
op_star
id|rq
)paren
(brace
r_return
id|list_empty
c_func
(paren
op_amp
id|rq-&gt;list
)paren
suffix:semicolon
)brace
r_void
id|raw3270_buffer_address
c_func
(paren
r_struct
id|raw3270
op_star
comma
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* Return value of *intv (see raw3270_fn below) can be one of the following: */
DECL|macro|RAW3270_IO_DONE
mdefine_line|#define RAW3270_IO_DONE&t;&t;0&t;/* request finished */
DECL|macro|RAW3270_IO_BUSY
mdefine_line|#define RAW3270_IO_BUSY&t;&t;1&t;/* request still active */
DECL|macro|RAW3270_IO_RETRY
mdefine_line|#define RAW3270_IO_RETRY&t;2&t;/* retry current request */
DECL|macro|RAW3270_IO_STOP
mdefine_line|#define RAW3270_IO_STOP&t;&t;3&t;/* kill current request */
multiline_comment|/*&n; * Functions of a 3270 view.&n; */
DECL|struct|raw3270_fn
r_struct
id|raw3270_fn
(brace
DECL|member|activate
r_int
(paren
op_star
id|activate
)paren
(paren
r_struct
id|raw3270_view
op_star
)paren
suffix:semicolon
DECL|member|deactivate
r_void
(paren
op_star
id|deactivate
)paren
(paren
r_struct
id|raw3270_view
op_star
)paren
suffix:semicolon
DECL|member|intv
r_int
(paren
op_star
id|intv
)paren
(paren
r_struct
id|raw3270_view
op_star
comma
r_struct
id|raw3270_request
op_star
comma
r_struct
id|irb
op_star
)paren
suffix:semicolon
DECL|member|release
r_void
(paren
op_star
id|release
)paren
(paren
r_struct
id|raw3270_view
op_star
)paren
suffix:semicolon
DECL|member|free
r_void
(paren
op_star
id|free
)paren
(paren
r_struct
id|raw3270_view
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * View structure chaining. The raw3270_view structure is meant to&n; * be embedded at the start of the real view data structure, e.g.:&n; *   struct example {&n; *     struct raw3270_view view;&n; *     ...&n; *   };&n; */
DECL|struct|raw3270_view
r_struct
id|raw3270_view
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|ref_count
id|atomic_t
id|ref_count
suffix:semicolon
DECL|member|dev
r_struct
id|raw3270
op_star
id|dev
suffix:semicolon
DECL|member|fn
r_struct
id|raw3270_fn
op_star
id|fn
suffix:semicolon
DECL|member|model
r_int
r_int
id|model
suffix:semicolon
DECL|member|rows
DECL|member|cols
r_int
r_int
id|rows
comma
id|cols
suffix:semicolon
multiline_comment|/* # of rows &amp; colums of the view */
DECL|member|ascebc
r_int
r_char
op_star
id|ascebc
suffix:semicolon
multiline_comment|/* ascii -&gt; ebcdic table */
)brace
suffix:semicolon
r_int
id|raw3270_add_view
c_func
(paren
r_struct
id|raw3270_view
op_star
comma
r_struct
id|raw3270_fn
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|raw3270_activate_view
c_func
(paren
r_struct
id|raw3270_view
op_star
)paren
suffix:semicolon
r_void
id|raw3270_del_view
c_func
(paren
r_struct
id|raw3270_view
op_star
)paren
suffix:semicolon
r_void
id|raw3270_deactivate_view
c_func
(paren
r_struct
id|raw3270_view
op_star
)paren
suffix:semicolon
r_struct
id|raw3270_view
op_star
id|raw3270_find_view
c_func
(paren
r_struct
id|raw3270_fn
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|raw3270_start
c_func
(paren
r_struct
id|raw3270_view
op_star
comma
r_struct
id|raw3270_request
op_star
)paren
suffix:semicolon
r_int
id|raw3270_start_irq
c_func
(paren
r_struct
id|raw3270_view
op_star
comma
r_struct
id|raw3270_request
op_star
)paren
suffix:semicolon
multiline_comment|/* Reference count inliner for view structures. */
r_static
r_inline
r_void
DECL|function|raw3270_get_view
id|raw3270_get_view
c_func
(paren
r_struct
id|raw3270_view
op_star
id|view
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|view-&gt;ref_count
)paren
suffix:semicolon
)brace
r_extern
id|wait_queue_head_t
id|raw3270_wait_queue
suffix:semicolon
r_static
r_inline
r_void
DECL|function|raw3270_put_view
id|raw3270_put_view
c_func
(paren
r_struct
id|raw3270_view
op_star
id|view
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_return
c_func
(paren
op_amp
id|view-&gt;ref_count
)paren
op_eq
l_int|0
)paren
id|wake_up
c_func
(paren
op_amp
id|raw3270_wait_queue
)paren
suffix:semicolon
)brace
r_struct
id|raw3270
op_star
id|raw3270_setup_console
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
suffix:semicolon
r_void
id|raw3270_wait_cons_dev
c_func
(paren
r_struct
id|raw3270
op_star
)paren
suffix:semicolon
multiline_comment|/* Notifier for device addition/removal */
r_int
id|raw3270_register_notifier
c_func
(paren
r_void
(paren
op_star
id|notifier
)paren
(paren
r_int
comma
r_int
)paren
)paren
suffix:semicolon
r_void
id|raw3270_unregister_notifier
c_func
(paren
r_void
(paren
op_star
id|notifier
)paren
(paren
r_int
comma
r_int
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Little memory allocator for string objects. &n; */
DECL|struct|string
r_struct
id|string
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|update
r_struct
id|list_head
id|update
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|string
r_char
id|string
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
r_static
r_inline
r_struct
id|string
op_star
DECL|function|alloc_string
id|alloc_string
c_func
(paren
r_struct
id|list_head
op_star
id|free_list
comma
r_int
r_int
id|len
)paren
(brace
r_struct
id|string
op_star
id|cs
comma
op_star
id|tmp
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
id|size
op_assign
(paren
id|len
op_plus
l_int|7L
)paren
op_amp
op_minus
l_int|8L
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|cs
comma
id|free_list
comma
id|list
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;size
OL
id|size
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;size
OG
id|size
op_plus
r_sizeof
(paren
r_struct
id|string
)paren
)paren
(brace
r_char
op_star
id|endaddr
op_assign
(paren
r_char
op_star
)paren
(paren
id|cs
op_plus
l_int|1
)paren
op_plus
id|cs-&gt;size
suffix:semicolon
id|tmp
op_assign
(paren
r_struct
id|string
op_star
)paren
(paren
id|endaddr
op_minus
id|size
)paren
op_minus
l_int|1
suffix:semicolon
id|tmp-&gt;size
op_assign
id|size
suffix:semicolon
id|cs-&gt;size
op_sub_assign
id|size
op_plus
r_sizeof
(paren
r_struct
id|string
)paren
suffix:semicolon
id|cs
op_assign
id|tmp
suffix:semicolon
)brace
r_else
id|list_del
c_func
(paren
op_amp
id|cs-&gt;list
)paren
suffix:semicolon
id|cs-&gt;len
op_assign
id|len
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|cs-&gt;list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|cs-&gt;update
)paren
suffix:semicolon
r_return
id|cs
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|free_string
id|free_string
c_func
(paren
r_struct
id|list_head
op_star
id|free_list
comma
r_struct
id|string
op_star
id|cs
)paren
(brace
r_struct
id|string
op_star
id|tmp
suffix:semicolon
r_struct
id|list_head
op_star
id|p
comma
op_star
id|left
suffix:semicolon
multiline_comment|/* Find out the left neighbour in free memory list. */
id|left
op_assign
id|free_list
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
id|free_list
)paren
(brace
r_if
c_cond
(paren
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|string
comma
id|list
)paren
OG
id|cs
)paren
r_break
suffix:semicolon
id|left
op_assign
id|p
suffix:semicolon
)brace
multiline_comment|/* Try to merge with right neighbour = next element from left. */
r_if
c_cond
(paren
id|left-&gt;next
op_ne
id|free_list
)paren
(brace
id|tmp
op_assign
id|list_entry
c_func
(paren
id|left-&gt;next
comma
r_struct
id|string
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_char
op_star
)paren
(paren
id|cs
op_plus
l_int|1
)paren
op_plus
id|cs-&gt;size
op_eq
(paren
r_char
op_star
)paren
id|tmp
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|tmp-&gt;list
)paren
suffix:semicolon
id|cs-&gt;size
op_add_assign
id|tmp-&gt;size
op_plus
r_sizeof
(paren
r_struct
id|string
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Try to merge with left neighbour. */
r_if
c_cond
(paren
id|left
op_ne
id|free_list
)paren
(brace
id|tmp
op_assign
id|list_entry
c_func
(paren
id|left
comma
r_struct
id|string
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_char
op_star
)paren
(paren
id|tmp
op_plus
l_int|1
)paren
op_plus
id|tmp-&gt;size
op_eq
(paren
r_char
op_star
)paren
id|cs
)paren
(brace
id|tmp-&gt;size
op_add_assign
id|cs-&gt;size
op_plus
r_sizeof
(paren
r_struct
id|string
)paren
suffix:semicolon
r_return
id|tmp-&gt;size
suffix:semicolon
)brace
)brace
id|__list_add
c_func
(paren
op_amp
id|cs-&gt;list
comma
id|left
comma
id|left-&gt;next
)paren
suffix:semicolon
r_return
id|cs-&gt;size
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|add_string_memory
id|add_string_memory
c_func
(paren
r_struct
id|list_head
op_star
id|free_list
comma
r_void
op_star
id|mem
comma
r_int
r_int
id|size
)paren
(brace
r_struct
id|string
op_star
id|cs
suffix:semicolon
id|cs
op_assign
(paren
r_struct
id|string
op_star
)paren
id|mem
suffix:semicolon
id|cs-&gt;size
op_assign
id|size
op_minus
r_sizeof
(paren
r_struct
id|string
)paren
suffix:semicolon
id|free_string
c_func
(paren
id|free_list
comma
id|cs
)paren
suffix:semicolon
)brace
eof
