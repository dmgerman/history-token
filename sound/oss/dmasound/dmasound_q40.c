multiline_comment|/*&n; *  linux/drivers/sound/dmasound/dmasound_q40.c&n; *&n; *  Q40 DMA Sound Driver&n; *&n; *  See linux/drivers/sound/dmasound/dmasound_core.c for copyright and credits&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/soundcard.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/q40_master.h&gt;
macro_line|#include &quot;dmasound.h&quot;
DECL|variable|expand_bal
r_static
r_int
id|expand_bal
suffix:semicolon
multiline_comment|/* Balance factor for expanding (not volume!) */
DECL|variable|expand_data
r_static
r_int
id|expand_data
suffix:semicolon
multiline_comment|/* Data for expanding */
multiline_comment|/*** Low level stuff *********************************************************/
r_static
r_void
id|Q40Open
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|Q40Release
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
op_star
id|Q40Alloc
c_func
(paren
r_int
r_int
id|size
comma
r_int
id|flags
)paren
suffix:semicolon
r_static
r_void
id|Q40Free
c_func
(paren
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_static
r_int
id|Q40IrqInit
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef MODULE
r_static
r_void
id|Q40IrqCleanUp
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
r_static
r_void
id|Q40Silence
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|Q40Init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|Q40SetFormat
c_func
(paren
r_int
id|format
)paren
suffix:semicolon
r_static
r_int
id|Q40SetVolume
c_func
(paren
r_int
id|volume
)paren
suffix:semicolon
r_static
r_void
id|Q40PlayNextFrame
c_func
(paren
r_int
id|index
)paren
suffix:semicolon
r_static
r_void
id|Q40Play
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|Q40StereoInterrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dummy
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
suffix:semicolon
r_static
r_void
id|Q40MonoInterrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dummy
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
suffix:semicolon
r_static
r_void
id|Q40Interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*** Mid level stuff *********************************************************/
macro_line|#if 1
multiline_comment|/* userCount, frameUsed, frameLeft == byte counts */
DECL|function|q40_ct_law
r_static
id|ssize_t
id|q40_ct_law
c_func
(paren
r_const
id|u_char
op_star
id|userPtr
comma
r_int
id|userCount
comma
id|u_char
id|frame
(braket
)braket
comma
id|ssize_t
op_star
id|frameUsed
comma
id|ssize_t
id|frameLeft
)paren
(brace
r_char
op_star
id|table
op_assign
id|dmasound.soft.format
op_eq
id|AFMT_MU_LAW
ques
c_cond
id|dmasound_ulaw2dma8
suffix:colon
id|dmasound_alaw2dma8
suffix:semicolon
id|ssize_t
id|count
comma
id|used
suffix:semicolon
id|u_char
op_star
id|p
op_assign
(paren
id|u_char
op_star
)paren
op_amp
id|frame
(braket
op_star
id|frameUsed
)braket
suffix:semicolon
id|used
op_assign
id|count
op_assign
id|min_t
c_func
(paren
r_int
comma
id|userCount
comma
id|frameLeft
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|p
comma
id|userPtr
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
op_star
id|p
op_assign
id|table
(braket
op_star
id|p
)braket
op_plus
l_int|128
suffix:semicolon
id|p
op_increment
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
op_star
id|frameUsed
op_add_assign
id|used
suffix:semicolon
r_return
id|used
suffix:semicolon
)brace
macro_line|#else
DECL|function|q40_ct_law
r_static
id|ssize_t
id|q40_ct_law
c_func
(paren
r_const
id|u_char
op_star
id|userPtr
comma
r_int
id|userCount
comma
id|u_char
id|frame
(braket
)braket
comma
id|ssize_t
op_star
id|frameUsed
comma
id|ssize_t
id|frameLeft
)paren
(brace
r_char
op_star
id|table
op_assign
id|dmasound.soft.format
op_eq
id|AFMT_MU_LAW
ques
c_cond
id|dmasound_ulaw2dma8
suffix:colon
id|dmasound_alaw2dma8
suffix:semicolon
id|ssize_t
id|count
comma
id|used
suffix:semicolon
id|u_char
op_star
id|p
op_assign
(paren
id|u_char
op_star
)paren
op_amp
id|frame
(braket
op_star
id|frameUsed
)braket
suffix:semicolon
id|u_char
id|val
suffix:semicolon
r_int
id|stereo
op_assign
id|sound.soft.stereo
suffix:semicolon
id|frameLeft
op_rshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|stereo
)paren
id|userCount
op_rshift_assign
l_int|1
suffix:semicolon
id|used
op_assign
id|count
op_assign
id|min_t
c_func
(paren
r_int
comma
id|userCount
comma
id|frameLeft
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
id|u_char
id|data
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|data
comma
id|userPtr
op_increment
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|val
op_assign
id|table
(braket
id|data
)braket
op_plus
l_int|128
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|val
suffix:semicolon
r_if
c_cond
(paren
id|stereo
)paren
(brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|data
comma
id|userPtr
op_increment
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|val
op_assign
id|table
(braket
id|data
)braket
op_plus
l_int|128
suffix:semicolon
)brace
op_star
id|p
op_increment
op_assign
id|val
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
op_star
id|frameUsed
op_add_assign
id|used
op_star
l_int|2
suffix:semicolon
r_return
id|stereo
ques
c_cond
id|used
op_star
l_int|2
suffix:colon
id|used
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if 1
DECL|function|q40_ct_s8
r_static
id|ssize_t
id|q40_ct_s8
c_func
(paren
r_const
id|u_char
op_star
id|userPtr
comma
r_int
id|userCount
comma
id|u_char
id|frame
(braket
)braket
comma
id|ssize_t
op_star
id|frameUsed
comma
id|ssize_t
id|frameLeft
)paren
(brace
id|ssize_t
id|count
comma
id|used
suffix:semicolon
id|u_char
op_star
id|p
op_assign
(paren
id|u_char
op_star
)paren
op_amp
id|frame
(braket
op_star
id|frameUsed
)braket
suffix:semicolon
id|used
op_assign
id|count
op_assign
id|min_t
c_func
(paren
r_int
comma
id|userCount
comma
id|frameLeft
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|p
comma
id|userPtr
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
op_star
id|p
op_assign
op_star
id|p
op_plus
l_int|128
suffix:semicolon
id|p
op_increment
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
op_star
id|frameUsed
op_add_assign
id|used
suffix:semicolon
r_return
id|used
suffix:semicolon
)brace
macro_line|#else
DECL|function|q40_ct_s8
r_static
id|ssize_t
id|q40_ct_s8
c_func
(paren
r_const
id|u_char
op_star
id|userPtr
comma
r_int
id|userCount
comma
id|u_char
id|frame
(braket
)braket
comma
id|ssize_t
op_star
id|frameUsed
comma
id|ssize_t
id|frameLeft
)paren
(brace
id|ssize_t
id|count
comma
id|used
suffix:semicolon
id|u_char
op_star
id|p
op_assign
(paren
id|u_char
op_star
)paren
op_amp
id|frame
(braket
op_star
id|frameUsed
)braket
suffix:semicolon
id|u_char
id|val
suffix:semicolon
r_int
id|stereo
op_assign
id|dmasound.soft.stereo
suffix:semicolon
id|frameLeft
op_rshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|stereo
)paren
id|userCount
op_rshift_assign
l_int|1
suffix:semicolon
id|used
op_assign
id|count
op_assign
id|min_t
c_func
(paren
r_int
comma
id|userCount
comma
id|frameLeft
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
id|u_char
id|data
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|data
comma
id|userPtr
op_increment
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|val
op_assign
id|data
op_plus
l_int|128
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|val
suffix:semicolon
r_if
c_cond
(paren
id|stereo
)paren
(brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|data
comma
id|userPtr
op_increment
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|val
op_assign
id|data
op_plus
l_int|128
suffix:semicolon
)brace
op_star
id|p
op_increment
op_assign
id|val
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
op_star
id|frameUsed
op_add_assign
id|used
op_star
l_int|2
suffix:semicolon
r_return
id|stereo
ques
c_cond
id|used
op_star
l_int|2
suffix:colon
id|used
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if 1
DECL|function|q40_ct_u8
r_static
id|ssize_t
id|q40_ct_u8
c_func
(paren
r_const
id|u_char
op_star
id|userPtr
comma
r_int
id|userCount
comma
id|u_char
id|frame
(braket
)braket
comma
id|ssize_t
op_star
id|frameUsed
comma
id|ssize_t
id|frameLeft
)paren
(brace
id|ssize_t
id|count
comma
id|used
suffix:semicolon
id|u_char
op_star
id|p
op_assign
(paren
id|u_char
op_star
)paren
op_amp
id|frame
(braket
op_star
id|frameUsed
)braket
suffix:semicolon
id|used
op_assign
id|count
op_assign
id|min_t
c_func
(paren
r_int
comma
id|userCount
comma
id|frameLeft
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|p
comma
id|userPtr
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
op_star
id|frameUsed
op_add_assign
id|used
suffix:semicolon
r_return
id|used
suffix:semicolon
)brace
macro_line|#else
DECL|function|q40_ct_u8
r_static
id|ssize_t
id|q40_ct_u8
c_func
(paren
r_const
id|u_char
op_star
id|userPtr
comma
r_int
id|userCount
comma
id|u_char
id|frame
(braket
)braket
comma
id|ssize_t
op_star
id|frameUsed
comma
id|ssize_t
id|frameLeft
)paren
(brace
id|ssize_t
id|count
comma
id|used
suffix:semicolon
id|u_char
op_star
id|p
op_assign
(paren
id|u_char
op_star
)paren
op_amp
id|frame
(braket
op_star
id|frameUsed
)braket
suffix:semicolon
id|u_char
id|val
suffix:semicolon
r_int
id|stereo
op_assign
id|dmasound.soft.stereo
suffix:semicolon
id|frameLeft
op_rshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|stereo
)paren
id|userCount
op_rshift_assign
l_int|1
suffix:semicolon
id|used
op_assign
id|count
op_assign
id|min_t
c_func
(paren
r_int
comma
id|userCount
comma
id|frameLeft
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
id|u_char
id|data
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|data
comma
id|userPtr
op_increment
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|val
op_assign
id|data
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|val
suffix:semicolon
r_if
c_cond
(paren
id|stereo
)paren
(brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|data
comma
id|userPtr
op_increment
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|val
op_assign
id|data
suffix:semicolon
)brace
op_star
id|p
op_increment
op_assign
id|val
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
op_star
id|frameUsed
op_add_assign
id|used
op_star
l_int|2
suffix:semicolon
r_return
id|stereo
ques
c_cond
id|used
op_star
l_int|2
suffix:colon
id|used
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* a bit too complicated to optimise right now ..*/
DECL|function|q40_ctx_law
r_static
id|ssize_t
id|q40_ctx_law
c_func
(paren
r_const
id|u_char
op_star
id|userPtr
comma
r_int
id|userCount
comma
id|u_char
id|frame
(braket
)braket
comma
id|ssize_t
op_star
id|frameUsed
comma
id|ssize_t
id|frameLeft
)paren
(brace
r_int
r_char
op_star
id|table
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
id|dmasound.soft.format
op_eq
id|AFMT_MU_LAW
ques
c_cond
id|dmasound_ulaw2dma8
suffix:colon
id|dmasound_alaw2dma8
)paren
suffix:semicolon
r_int
r_int
id|data
op_assign
id|expand_data
suffix:semicolon
id|u_char
op_star
id|p
op_assign
(paren
id|u_char
op_star
)paren
op_amp
id|frame
(braket
op_star
id|frameUsed
)braket
suffix:semicolon
r_int
id|bal
op_assign
id|expand_bal
suffix:semicolon
r_int
id|hSpeed
op_assign
id|dmasound.hard.speed
comma
id|sSpeed
op_assign
id|dmasound.soft.speed
suffix:semicolon
r_int
id|utotal
comma
id|ftotal
suffix:semicolon
id|ftotal
op_assign
id|frameLeft
suffix:semicolon
id|utotal
op_assign
id|userCount
suffix:semicolon
r_while
c_loop
(paren
id|frameLeft
)paren
(brace
id|u_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|bal
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|userCount
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|c
comma
id|userPtr
op_increment
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|data
op_assign
id|table
(braket
id|c
)braket
suffix:semicolon
id|data
op_add_assign
l_int|0x80
suffix:semicolon
id|userCount
op_decrement
suffix:semicolon
id|bal
op_add_assign
id|hSpeed
suffix:semicolon
)brace
op_star
id|p
op_increment
op_assign
id|data
suffix:semicolon
id|frameLeft
op_decrement
suffix:semicolon
id|bal
op_sub_assign
id|sSpeed
suffix:semicolon
)brace
id|expand_bal
op_assign
id|bal
suffix:semicolon
id|expand_data
op_assign
id|data
suffix:semicolon
op_star
id|frameUsed
op_add_assign
(paren
id|ftotal
op_minus
id|frameLeft
)paren
suffix:semicolon
id|utotal
op_sub_assign
id|userCount
suffix:semicolon
r_return
id|utotal
suffix:semicolon
)brace
DECL|function|q40_ctx_s8
r_static
id|ssize_t
id|q40_ctx_s8
c_func
(paren
r_const
id|u_char
op_star
id|userPtr
comma
r_int
id|userCount
comma
id|u_char
id|frame
(braket
)braket
comma
id|ssize_t
op_star
id|frameUsed
comma
id|ssize_t
id|frameLeft
)paren
(brace
id|u_char
op_star
id|p
op_assign
(paren
id|u_char
op_star
)paren
op_amp
id|frame
(braket
op_star
id|frameUsed
)braket
suffix:semicolon
r_int
r_int
id|data
op_assign
id|expand_data
suffix:semicolon
r_int
id|bal
op_assign
id|expand_bal
suffix:semicolon
r_int
id|hSpeed
op_assign
id|dmasound.hard.speed
comma
id|sSpeed
op_assign
id|dmasound.soft.speed
suffix:semicolon
r_int
id|utotal
comma
id|ftotal
suffix:semicolon
id|ftotal
op_assign
id|frameLeft
suffix:semicolon
id|utotal
op_assign
id|userCount
suffix:semicolon
r_while
c_loop
(paren
id|frameLeft
)paren
(brace
id|u_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|bal
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|userCount
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|c
comma
id|userPtr
op_increment
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|data
op_assign
id|c
suffix:semicolon
id|data
op_add_assign
l_int|0x80
suffix:semicolon
id|userCount
op_decrement
suffix:semicolon
id|bal
op_add_assign
id|hSpeed
suffix:semicolon
)brace
op_star
id|p
op_increment
op_assign
id|data
suffix:semicolon
id|frameLeft
op_decrement
suffix:semicolon
id|bal
op_sub_assign
id|sSpeed
suffix:semicolon
)brace
id|expand_bal
op_assign
id|bal
suffix:semicolon
id|expand_data
op_assign
id|data
suffix:semicolon
op_star
id|frameUsed
op_add_assign
(paren
id|ftotal
op_minus
id|frameLeft
)paren
suffix:semicolon
id|utotal
op_sub_assign
id|userCount
suffix:semicolon
r_return
id|utotal
suffix:semicolon
)brace
DECL|function|q40_ctx_u8
r_static
id|ssize_t
id|q40_ctx_u8
c_func
(paren
r_const
id|u_char
op_star
id|userPtr
comma
r_int
id|userCount
comma
id|u_char
id|frame
(braket
)braket
comma
id|ssize_t
op_star
id|frameUsed
comma
id|ssize_t
id|frameLeft
)paren
(brace
id|u_char
op_star
id|p
op_assign
(paren
id|u_char
op_star
)paren
op_amp
id|frame
(braket
op_star
id|frameUsed
)braket
suffix:semicolon
r_int
r_int
id|data
op_assign
id|expand_data
suffix:semicolon
r_int
id|bal
op_assign
id|expand_bal
suffix:semicolon
r_int
id|hSpeed
op_assign
id|dmasound.hard.speed
comma
id|sSpeed
op_assign
id|dmasound.soft.speed
suffix:semicolon
r_int
id|utotal
comma
id|ftotal
suffix:semicolon
id|ftotal
op_assign
id|frameLeft
suffix:semicolon
id|utotal
op_assign
id|userCount
suffix:semicolon
r_while
c_loop
(paren
id|frameLeft
)paren
(brace
id|u_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|bal
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|userCount
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|c
comma
id|userPtr
op_increment
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|data
op_assign
id|c
suffix:semicolon
id|userCount
op_decrement
suffix:semicolon
id|bal
op_add_assign
id|hSpeed
suffix:semicolon
)brace
op_star
id|p
op_increment
op_assign
id|data
suffix:semicolon
id|frameLeft
op_decrement
suffix:semicolon
id|bal
op_sub_assign
id|sSpeed
suffix:semicolon
)brace
id|expand_bal
op_assign
id|bal
suffix:semicolon
id|expand_data
op_assign
id|data
suffix:semicolon
op_star
id|frameUsed
op_add_assign
(paren
id|ftotal
op_minus
id|frameLeft
)paren
suffix:semicolon
id|utotal
op_sub_assign
id|userCount
suffix:semicolon
r_return
id|utotal
suffix:semicolon
)brace
DECL|variable|transQ40Normal
r_static
id|TRANS
id|transQ40Normal
op_assign
(brace
id|q40_ct_law
comma
id|q40_ct_law
comma
id|q40_ct_s8
comma
id|q40_ct_u8
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|transQ40Expanding
r_static
id|TRANS
id|transQ40Expanding
op_assign
(brace
id|q40_ctx_law
comma
id|q40_ctx_law
comma
id|q40_ctx_s8
comma
id|q40_ctx_u8
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/*** Low level stuff *********************************************************/
DECL|function|Q40Open
r_static
r_void
id|Q40Open
c_func
(paren
r_void
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
DECL|function|Q40Release
r_static
r_void
id|Q40Release
c_func
(paren
r_void
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|function|Q40Alloc
r_static
r_void
op_star
id|Q40Alloc
c_func
(paren
r_int
r_int
id|size
comma
r_int
id|flags
)paren
(brace
r_return
id|kmalloc
c_func
(paren
id|size
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* change to vmalloc */
)brace
DECL|function|Q40Free
r_static
r_void
id|Q40Free
c_func
(paren
r_void
op_star
id|ptr
comma
r_int
r_int
id|size
)paren
(brace
id|kfree
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
DECL|function|Q40IrqInit
r_static
r_int
id|__init
id|Q40IrqInit
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Register interrupt handler. */
id|request_irq
c_func
(paren
id|Q40_IRQ_SAMPLE
comma
id|Q40StereoInterrupt
comma
l_int|0
comma
l_string|&quot;DMA sound&quot;
comma
id|Q40Interrupt
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|Q40IrqCleanUp
r_static
r_void
id|Q40IrqCleanUp
c_func
(paren
r_void
)paren
(brace
id|master_outb
c_func
(paren
l_int|0
comma
id|SAMPLE_ENABLE_REG
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|Q40_IRQ_SAMPLE
comma
id|Q40Interrupt
)paren
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
DECL|function|Q40Silence
r_static
r_void
id|Q40Silence
c_func
(paren
r_void
)paren
(brace
id|master_outb
c_func
(paren
l_int|0
comma
id|SAMPLE_ENABLE_REG
)paren
suffix:semicolon
op_star
id|DAC_LEFT
op_assign
op_star
id|DAC_RIGHT
op_assign
l_int|0
suffix:semicolon
)brace
DECL|variable|q40_pp
r_static
r_char
op_star
id|q40_pp
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|q40_sc
r_static
r_int
r_int
id|q40_sc
op_assign
l_int|0
suffix:semicolon
DECL|function|Q40PlayNextFrame
r_static
r_void
id|Q40PlayNextFrame
c_func
(paren
r_int
id|index
)paren
(brace
id|u_char
op_star
id|start
suffix:semicolon
id|u_long
id|size
suffix:semicolon
id|u_char
id|speed
suffix:semicolon
multiline_comment|/* used by Q40Play() if all doubts whether there really is something&n;&t; * to be played are already wiped out.&n;&t; */
id|start
op_assign
id|write_sq.buffers
(braket
id|write_sq.front
)braket
suffix:semicolon
id|size
op_assign
(paren
id|write_sq.count
op_eq
id|index
ques
c_cond
id|write_sq.rear_size
suffix:colon
id|write_sq.block_size
)paren
suffix:semicolon
id|q40_pp
op_assign
id|start
suffix:semicolon
id|q40_sc
op_assign
id|size
suffix:semicolon
id|write_sq.front
op_assign
(paren
id|write_sq.front
op_plus
l_int|1
)paren
op_mod
id|write_sq.max_count
suffix:semicolon
id|write_sq.active
op_increment
suffix:semicolon
id|speed
op_assign
(paren
id|dmasound.hard.speed
op_eq
l_int|10000
ques
c_cond
l_int|0
suffix:colon
l_int|1
)paren
suffix:semicolon
id|master_outb
c_func
(paren
l_int|0
comma
id|SAMPLE_ENABLE_REG
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|Q40_IRQ_SAMPLE
comma
id|Q40Interrupt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dmasound.soft.stereo
)paren
id|request_irq
c_func
(paren
id|Q40_IRQ_SAMPLE
comma
id|Q40StereoInterrupt
comma
l_int|0
comma
l_string|&quot;Q40 sound&quot;
comma
id|Q40Interrupt
)paren
suffix:semicolon
r_else
id|request_irq
c_func
(paren
id|Q40_IRQ_SAMPLE
comma
id|Q40MonoInterrupt
comma
l_int|0
comma
l_string|&quot;Q40 sound&quot;
comma
id|Q40Interrupt
)paren
suffix:semicolon
id|master_outb
c_func
(paren
id|speed
comma
id|SAMPLE_RATE_REG
)paren
suffix:semicolon
id|master_outb
c_func
(paren
l_int|1
comma
id|SAMPLE_CLEAR_REG
)paren
suffix:semicolon
id|master_outb
c_func
(paren
l_int|1
comma
id|SAMPLE_ENABLE_REG
)paren
suffix:semicolon
)brace
DECL|function|Q40Play
r_static
r_void
id|Q40Play
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|write_sq.active
op_logical_or
id|write_sq.count
op_le
l_int|0
)paren
(brace
multiline_comment|/* There&squot;s already a frame loaded */
r_return
suffix:semicolon
)brace
multiline_comment|/* nothing in the queue */
r_if
c_cond
(paren
id|write_sq.count
op_le
l_int|1
op_logical_and
id|write_sq.rear_size
OL
id|write_sq.block_size
op_logical_and
op_logical_neg
id|write_sq.syncing
)paren
(brace
multiline_comment|/* hmmm, the only existing frame is not&n;&t;&t;  * yet filled and we&squot;re not syncing?&n;&t;&t;  */
r_return
suffix:semicolon
)brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|Q40PlayNextFrame
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|Q40StereoInterrupt
r_static
r_void
id|Q40StereoInterrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dummy
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
r_if
c_cond
(paren
id|q40_sc
OG
l_int|1
)paren
(brace
op_star
id|DAC_LEFT
op_assign
op_star
id|q40_pp
op_increment
suffix:semicolon
op_star
id|DAC_RIGHT
op_assign
op_star
id|q40_pp
op_increment
suffix:semicolon
id|q40_sc
op_sub_assign
l_int|2
suffix:semicolon
id|master_outb
c_func
(paren
l_int|1
comma
id|SAMPLE_CLEAR_REG
)paren
suffix:semicolon
)brace
r_else
(brace
id|Q40Interrupt
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|Q40MonoInterrupt
r_static
r_void
id|Q40MonoInterrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dummy
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
r_if
c_cond
(paren
id|q40_sc
OG
l_int|0
)paren
(brace
op_star
id|DAC_LEFT
op_assign
op_star
id|q40_pp
suffix:semicolon
op_star
id|DAC_RIGHT
op_assign
op_star
id|q40_pp
op_increment
suffix:semicolon
id|q40_sc
op_decrement
suffix:semicolon
id|master_outb
c_func
(paren
l_int|1
comma
id|SAMPLE_CLEAR_REG
)paren
suffix:semicolon
)brace
r_else
(brace
id|Q40Interrupt
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|Q40Interrupt
r_static
r_void
id|Q40Interrupt
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|write_sq.active
)paren
(brace
multiline_comment|/* playing was interrupted and sq_reset() has already cleared&n;&t;&t;   * the sq variables, so better don&squot;t do anything here.&n;&t;&t;   */
id|WAKE_UP
c_func
(paren
id|write_sq.sync_queue
)paren
suffix:semicolon
id|master_outb
c_func
(paren
l_int|0
comma
id|SAMPLE_ENABLE_REG
)paren
suffix:semicolon
multiline_comment|/* better safe */
r_goto
m_exit
suffix:semicolon
)brace
r_else
id|write_sq.active
op_assign
l_int|0
suffix:semicolon
id|write_sq.count
op_decrement
suffix:semicolon
id|Q40Play
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q40_sc
OL
l_int|2
)paren
(brace
multiline_comment|/* there was nothing to play, disable irq */
id|master_outb
c_func
(paren
l_int|0
comma
id|SAMPLE_ENABLE_REG
)paren
suffix:semicolon
op_star
id|DAC_LEFT
op_assign
op_star
id|DAC_RIGHT
op_assign
l_int|0
suffix:semicolon
)brace
id|WAKE_UP
c_func
(paren
id|write_sq.action_queue
)paren
suffix:semicolon
m_exit
suffix:colon
id|master_outb
c_func
(paren
l_int|1
comma
id|SAMPLE_CLEAR_REG
)paren
suffix:semicolon
)brace
DECL|function|Q40Init
r_static
r_void
id|Q40Init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|idx
suffix:semicolon
r_const
r_int
id|freq
(braket
)braket
op_assign
(brace
l_int|10000
comma
l_int|20000
)brace
suffix:semicolon
multiline_comment|/* search a frequency that fits into the allowed error range */
id|idx
op_assign
op_minus
l_int|1
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
l_int|100
op_star
id|abs
c_func
(paren
id|dmasound.soft.speed
op_minus
id|freq
(braket
id|i
)braket
)paren
op_div
id|freq
(braket
id|i
)braket
)paren
op_le
id|catchRadius
)paren
id|idx
op_assign
id|i
suffix:semicolon
id|dmasound.hard
op_assign
id|dmasound.soft
suffix:semicolon
multiline_comment|/*sound.hard.stereo=1;*/
multiline_comment|/* no longer true */
id|dmasound.hard.size
op_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|idx
OG
op_minus
l_int|1
)paren
(brace
id|dmasound.soft.speed
op_assign
id|freq
(braket
id|idx
)braket
suffix:semicolon
id|dmasound.trans_write
op_assign
op_amp
id|transQ40Normal
suffix:semicolon
)brace
r_else
id|dmasound.trans_write
op_assign
op_amp
id|transQ40Expanding
suffix:semicolon
id|Q40Silence
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dmasound.hard.speed
OG
l_int|20000
)paren
(brace
multiline_comment|/* we would need to squeeze the sound, but we won&squot;t do that */
id|dmasound.hard.speed
op_assign
l_int|20000
suffix:semicolon
id|dmasound.trans_write
op_assign
op_amp
id|transQ40Normal
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dmasound.hard.speed
OG
l_int|10000
)paren
(brace
id|dmasound.hard.speed
op_assign
l_int|20000
suffix:semicolon
)brace
r_else
(brace
id|dmasound.hard.speed
op_assign
l_int|10000
suffix:semicolon
)brace
id|expand_bal
op_assign
op_minus
id|dmasound.soft.speed
suffix:semicolon
)brace
DECL|function|Q40SetFormat
r_static
r_int
id|Q40SetFormat
c_func
(paren
r_int
id|format
)paren
(brace
multiline_comment|/* Q40 sound supports only 8bit modes */
r_switch
c_cond
(paren
id|format
)paren
(brace
r_case
id|AFMT_QUERY
suffix:colon
r_return
id|dmasound.soft.format
suffix:semicolon
r_case
id|AFMT_MU_LAW
suffix:colon
r_case
id|AFMT_A_LAW
suffix:colon
r_case
id|AFMT_S8
suffix:colon
r_case
id|AFMT_U8
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|format
op_assign
id|AFMT_S8
suffix:semicolon
)brace
id|dmasound.soft.format
op_assign
id|format
suffix:semicolon
id|dmasound.soft.size
op_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|dmasound.minDev
op_eq
id|SND_DEV_DSP
)paren
(brace
id|dmasound.dsp.format
op_assign
id|format
suffix:semicolon
id|dmasound.dsp.size
op_assign
l_int|8
suffix:semicolon
)brace
id|Q40Init
c_func
(paren
)paren
suffix:semicolon
r_return
id|format
suffix:semicolon
)brace
DECL|function|Q40SetVolume
r_static
r_int
id|Q40SetVolume
c_func
(paren
r_int
id|volume
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*** Machine definitions *****************************************************/
DECL|variable|machQ40
r_static
id|MACHINE
id|machQ40
op_assign
(brace
id|name
suffix:colon
l_string|&quot;Q40&quot;
comma
id|name2
suffix:colon
l_string|&quot;Q40&quot;
comma
id|open
suffix:colon
id|Q40Open
comma
id|release
suffix:colon
id|Q40Release
comma
id|dma_alloc
suffix:colon
id|Q40Alloc
comma
id|dma_free
suffix:colon
id|Q40Free
comma
id|irqinit
suffix:colon
id|Q40IrqInit
comma
macro_line|#ifdef MODULE
id|irqcleanup
suffix:colon
id|Q40IrqCleanUp
comma
macro_line|#endif /* MODULE */
id|init
suffix:colon
id|Q40Init
comma
id|silence
suffix:colon
id|Q40Silence
comma
id|setFormat
suffix:colon
id|Q40SetFormat
comma
id|setVolume
suffix:colon
id|Q40SetVolume
comma
id|play
suffix:colon
id|Q40Play
)brace
suffix:semicolon
multiline_comment|/*** Config &amp; Setup **********************************************************/
DECL|function|dmasound_q40_init
r_int
id|__init
id|dmasound_q40_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|MACH_IS_Q40
)paren
(brace
id|dmasound.mach
op_assign
id|machQ40
suffix:semicolon
r_return
id|dmasound_init
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|dmasound_q40_cleanup
r_static
r_void
id|__exit
id|dmasound_q40_cleanup
c_func
(paren
r_void
)paren
(brace
id|dmasound_deinit
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|dmasound_q40_init
id|module_init
c_func
(paren
id|dmasound_q40_init
)paren
suffix:semicolon
DECL|variable|dmasound_q40_cleanup
id|module_exit
c_func
(paren
id|dmasound_q40_cleanup
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof