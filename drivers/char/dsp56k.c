multiline_comment|/*&n; * The DSP56001 Device Driver, saviour of the Free World(tm)&n; *&n; * Authors: Fredrik Noring   &lt;noring@nocrew.org&gt;&n; *          lars brinkhoff   &lt;lars@nocrew.org&gt;&n; *          Tomas Berndtsson &lt;tomas@nocrew.org&gt;&n; *&n; * First version May 1996&n; *&n; * History:&n; *  97-01-29   Tomas Berndtsson,&n; *               Integrated with Linux 2.1.21 kernel sources.&n; *  97-02-15   Tomas Berndtsson,&n; *               Fixed for kernel 2.1.26&n; *&n; * BUGS:&n; *  Hmm... there must be something here :)&n; *&n; * Copyright (C) 1996,1997 Fredrik Noring, lars brinkhoff &amp; Tomas Berndtsson&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/slab.h&gt;&t;/* for kmalloc() and kfree() */
macro_line|#include &lt;linux/sched.h&gt;&t;/* for struct wait_queue etc */
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/delay.h&gt;&t;/* guess what */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/atarihw.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;&t;/* For put_user and get_user */
macro_line|#include &lt;asm/dsp56k.h&gt;
multiline_comment|/* minor devices */
DECL|macro|DSP56K_DEV_56001
mdefine_line|#define DSP56K_DEV_56001        0    /* The only device so far */
DECL|macro|TIMEOUT
mdefine_line|#define TIMEOUT    10   /* Host port timeout in number of tries */
DECL|macro|MAXIO
mdefine_line|#define MAXIO    2048   /* Maximum number of words before sleep */
DECL|macro|DSP56K_MAX_BINARY_LENGTH
mdefine_line|#define DSP56K_MAX_BINARY_LENGTH (3*64*1024)
DECL|macro|DSP56K_TX_INT_ON
mdefine_line|#define DSP56K_TX_INT_ON&t;dsp56k_host_interface.icr |=  DSP56K_ICR_TREQ
DECL|macro|DSP56K_RX_INT_ON
mdefine_line|#define DSP56K_RX_INT_ON&t;dsp56k_host_interface.icr |=  DSP56K_ICR_RREQ
DECL|macro|DSP56K_TX_INT_OFF
mdefine_line|#define DSP56K_TX_INT_OFF&t;dsp56k_host_interface.icr &amp;= ~DSP56K_ICR_TREQ
DECL|macro|DSP56K_RX_INT_OFF
mdefine_line|#define DSP56K_RX_INT_OFF&t;dsp56k_host_interface.icr &amp;= ~DSP56K_ICR_RREQ
DECL|macro|DSP56K_TRANSMIT
mdefine_line|#define DSP56K_TRANSMIT&t;&t;(dsp56k_host_interface.isr &amp; DSP56K_ISR_TXDE)
DECL|macro|DSP56K_RECEIVE
mdefine_line|#define DSP56K_RECEIVE&t;&t;(dsp56k_host_interface.isr &amp; DSP56K_ISR_RXDF)
DECL|macro|wait_some
mdefine_line|#define wait_some(n) &bslash;&n;{ &bslash;&n;&t;set_current_state(TASK_INTERRUPTIBLE); &bslash;&n;&t;schedule_timeout(n); &bslash;&n;}
DECL|macro|handshake
mdefine_line|#define handshake(count, maxio, timeout, ENABLE, f) &bslash;&n;{ &bslash;&n;&t;long i, t, m; &bslash;&n;&t;while (count &gt; 0) { &bslash;&n;&t;&t;m = min_t(unsigned long, count, maxio); &bslash;&n;&t;&t;for (i = 0; i &lt; m; i++) { &bslash;&n;&t;&t;&t;for (t = 0; t &lt; timeout &amp;&amp; !ENABLE; t++) &bslash;&n;&t;&t;&t;&t;wait_some(HZ/50); &bslash;&n;&t;&t;&t;if(!ENABLE) &bslash;&n;&t;&t;&t;&t;return -EIO; &bslash;&n;&t;&t;&t;f; &bslash;&n;&t;&t;} &bslash;&n;&t;&t;count -= m; &bslash;&n;&t;&t;if (m == maxio) wait_some(HZ/50); &bslash;&n;&t;} &bslash;&n;}
DECL|macro|tx_wait
mdefine_line|#define tx_wait(n) &bslash;&n;{ &bslash;&n;&t;int t; &bslash;&n;&t;for(t = 0; t &lt; n &amp;&amp; !DSP56K_TRANSMIT; t++) &bslash;&n;&t;&t;wait_some(HZ/100); &bslash;&n;&t;if(!DSP56K_TRANSMIT) { &bslash;&n;&t;&t;return -EIO; &bslash;&n;&t;} &bslash;&n;}
DECL|macro|rx_wait
mdefine_line|#define rx_wait(n) &bslash;&n;{ &bslash;&n;&t;int t; &bslash;&n;&t;for(t = 0; t &lt; n &amp;&amp; !DSP56K_RECEIVE; t++) &bslash;&n;&t;&t;wait_some(HZ/100); &bslash;&n;&t;if(!DSP56K_RECEIVE) { &bslash;&n;&t;&t;return -EIO; &bslash;&n;&t;} &bslash;&n;}
multiline_comment|/* DSP56001 bootstrap code */
DECL|variable|bootstrap
r_static
r_char
id|bootstrap
(braket
)braket
op_assign
(brace
l_int|0x0c
comma
l_int|0x00
comma
l_int|0x40
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x60
comma
l_int|0xf4
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x4f
comma
l_int|0x61
comma
l_int|0xf4
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x7e
comma
l_int|0xa9
comma
l_int|0x06
comma
l_int|0x2e
comma
l_int|0x80
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x47
comma
l_int|0x07
comma
l_int|0xd8
comma
l_int|0x84
comma
l_int|0x07
comma
l_int|0x59
comma
l_int|0x84
comma
l_int|0x08
comma
l_int|0xf4
comma
l_int|0xa8
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x04
comma
l_int|0x08
comma
l_int|0xf4
comma
l_int|0xbf
comma
l_int|0x00
comma
l_int|0x0c
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0xfe
comma
l_int|0xb8
comma
l_int|0x0a
comma
l_int|0xf0
comma
l_int|0x80
comma
l_int|0x00
comma
l_int|0x7e
comma
l_int|0xa9
comma
l_int|0x08
comma
l_int|0xf4
comma
l_int|0xa0
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x01
comma
l_int|0x08
comma
l_int|0xf4
comma
l_int|0xbe
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x0a
comma
l_int|0xa9
comma
l_int|0x80
comma
l_int|0x00
comma
l_int|0x7e
comma
l_int|0xad
comma
l_int|0x08
comma
l_int|0x4e
comma
l_int|0x2b
comma
l_int|0x44
comma
l_int|0xf4
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x03
comma
l_int|0x44
comma
l_int|0xf4
comma
l_int|0x45
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x01
comma
l_int|0x0e
comma
l_int|0xa0
comma
l_int|0x00
comma
l_int|0x0a
comma
l_int|0xa9
comma
l_int|0x80
comma
l_int|0x00
comma
l_int|0x7e
comma
l_int|0xb5
comma
l_int|0x08
comma
l_int|0x50
comma
l_int|0x2b
comma
l_int|0x0a
comma
l_int|0xa9
comma
l_int|0x80
comma
l_int|0x00
comma
l_int|0x7e
comma
l_int|0xb8
comma
l_int|0x08
comma
l_int|0x46
comma
l_int|0x2b
comma
l_int|0x44
comma
l_int|0xf4
comma
l_int|0x45
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x02
comma
l_int|0x0a
comma
l_int|0xf0
comma
l_int|0xaa
comma
l_int|0x00
comma
l_int|0x7e
comma
l_int|0xc9
comma
l_int|0x20
comma
l_int|0x00
comma
l_int|0x45
comma
l_int|0x0a
comma
l_int|0xf0
comma
l_int|0xaa
comma
l_int|0x00
comma
l_int|0x7e
comma
l_int|0xd0
comma
l_int|0x06
comma
l_int|0xc6
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x7e
comma
l_int|0xc6
comma
l_int|0x0a
comma
l_int|0xa9
comma
l_int|0x80
comma
l_int|0x00
comma
l_int|0x7e
comma
l_int|0xc4
comma
l_int|0x08
comma
l_int|0x58
comma
l_int|0x6b
comma
l_int|0x0a
comma
l_int|0xf0
comma
l_int|0x80
comma
l_int|0x00
comma
l_int|0x7e
comma
l_int|0xad
comma
l_int|0x06
comma
l_int|0xc6
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x7e
comma
l_int|0xcd
comma
l_int|0x0a
comma
l_int|0xa9
comma
l_int|0x80
comma
l_int|0x00
comma
l_int|0x7e
comma
l_int|0xcb
comma
l_int|0x08
comma
l_int|0x58
comma
l_int|0xab
comma
l_int|0x0a
comma
l_int|0xf0
comma
l_int|0x80
comma
l_int|0x00
comma
l_int|0x7e
comma
l_int|0xad
comma
l_int|0x06
comma
l_int|0xc6
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x7e
comma
l_int|0xd4
comma
l_int|0x0a
comma
l_int|0xa9
comma
l_int|0x80
comma
l_int|0x00
comma
l_int|0x7e
comma
l_int|0xd2
comma
l_int|0x08
comma
l_int|0x58
comma
l_int|0xeb
comma
l_int|0x0a
comma
l_int|0xf0
comma
l_int|0x80
comma
l_int|0x00
comma
l_int|0x7e
comma
l_int|0xad
)brace
suffix:semicolon
DECL|variable|sizeof_bootstrap
r_static
r_int
id|sizeof_bootstrap
op_assign
l_int|375
suffix:semicolon
DECL|struct|dsp56k_device
r_static
r_struct
id|dsp56k_device
(brace
DECL|member|in_use
r_int
id|in_use
suffix:semicolon
DECL|member|maxio
DECL|member|timeout
r_int
id|maxio
comma
id|timeout
suffix:semicolon
DECL|member|tx_wsize
DECL|member|rx_wsize
r_int
id|tx_wsize
comma
id|rx_wsize
suffix:semicolon
DECL|variable|dsp56k
)brace
id|dsp56k
suffix:semicolon
DECL|function|dsp56k_reset
r_static
r_int
id|dsp56k_reset
c_func
(paren
r_void
)paren
(brace
id|u_char
id|status
suffix:semicolon
multiline_comment|/* Power down the DSP */
id|sound_ym.rd_data_reg_sel
op_assign
l_int|14
suffix:semicolon
id|status
op_assign
id|sound_ym.rd_data_reg_sel
op_amp
l_int|0xef
suffix:semicolon
id|sound_ym.wd_data
op_assign
id|status
suffix:semicolon
id|sound_ym.wd_data
op_assign
id|status
op_or
l_int|0x10
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
multiline_comment|/* Power up the DSP */
id|sound_ym.rd_data_reg_sel
op_assign
l_int|14
suffix:semicolon
id|sound_ym.wd_data
op_assign
id|sound_ym.rd_data_reg_sel
op_amp
l_int|0xef
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dsp56k_upload
r_static
r_int
id|dsp56k_upload
c_func
(paren
id|u_char
op_star
id|bin
comma
r_int
id|len
)paren
(brace
r_int
id|i
suffix:semicolon
id|u_char
op_star
id|p
suffix:semicolon
id|dsp56k_reset
c_func
(paren
)paren
suffix:semicolon
id|p
op_assign
id|bootstrap
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
id|sizeof_bootstrap
op_div
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* tx_wait(10); */
id|dsp56k_host_interface.data.b
(braket
l_int|1
)braket
op_assign
op_star
id|p
op_increment
suffix:semicolon
id|dsp56k_host_interface.data.b
(braket
l_int|2
)braket
op_assign
op_star
id|p
op_increment
suffix:semicolon
id|dsp56k_host_interface.data.b
(braket
l_int|3
)braket
op_assign
op_star
id|p
op_increment
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
l_int|512
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* tx_wait(10); */
id|dsp56k_host_interface.data.b
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|dsp56k_host_interface.data.b
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
id|dsp56k_host_interface.data.b
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tx_wait
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|get_user
c_func
(paren
id|dsp56k_host_interface.data.b
(braket
l_int|1
)braket
comma
id|bin
op_increment
)paren
suffix:semicolon
id|get_user
c_func
(paren
id|dsp56k_host_interface.data.b
(braket
l_int|2
)braket
comma
id|bin
op_increment
)paren
suffix:semicolon
id|get_user
c_func
(paren
id|dsp56k_host_interface.data.b
(braket
l_int|3
)braket
comma
id|bin
op_increment
)paren
suffix:semicolon
)brace
id|tx_wait
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|dsp56k_host_interface.data.l
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* Magic execute */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dsp56k_read
r_static
id|ssize_t
id|dsp56k_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
id|dev
op_assign
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_amp
l_int|0x0f
suffix:semicolon
r_switch
c_cond
(paren
id|dev
)paren
(brace
r_case
id|DSP56K_DEV_56001
suffix:colon
(brace
r_int
id|n
suffix:semicolon
multiline_comment|/* Don&squot;t do anything if nothing is to be done */
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
l_int|0
suffix:semicolon
id|n
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|dsp56k.rx_wsize
)paren
(brace
r_case
l_int|1
suffix:colon
multiline_comment|/* 8 bit */
(brace
id|handshake
c_func
(paren
id|count
comma
id|dsp56k.maxio
comma
id|dsp56k.timeout
comma
id|DSP56K_RECEIVE
comma
id|put_user
c_func
(paren
id|dsp56k_host_interface.data.b
(braket
l_int|3
)braket
comma
id|buf
op_plus
id|n
op_increment
)paren
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
r_case
l_int|2
suffix:colon
multiline_comment|/* 16 bit */
(brace
r_int
op_star
id|data
suffix:semicolon
id|count
op_div_assign
l_int|2
suffix:semicolon
id|data
op_assign
(paren
r_int
op_star
)paren
id|buf
suffix:semicolon
id|handshake
c_func
(paren
id|count
comma
id|dsp56k.maxio
comma
id|dsp56k.timeout
comma
id|DSP56K_RECEIVE
comma
id|put_user
c_func
(paren
id|dsp56k_host_interface.data.w
(braket
l_int|1
)braket
comma
id|data
op_plus
id|n
op_increment
)paren
)paren
suffix:semicolon
r_return
l_int|2
op_star
id|n
suffix:semicolon
)brace
r_case
l_int|3
suffix:colon
multiline_comment|/* 24 bit */
(brace
id|count
op_div_assign
l_int|3
suffix:semicolon
id|handshake
c_func
(paren
id|count
comma
id|dsp56k.maxio
comma
id|dsp56k.timeout
comma
id|DSP56K_RECEIVE
comma
id|put_user
c_func
(paren
id|dsp56k_host_interface.data.b
(braket
l_int|1
)braket
comma
id|buf
op_plus
id|n
op_increment
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|dsp56k_host_interface.data.b
(braket
l_int|2
)braket
comma
id|buf
op_plus
id|n
op_increment
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|dsp56k_host_interface.data.b
(braket
l_int|3
)braket
comma
id|buf
op_plus
id|n
op_increment
)paren
)paren
suffix:semicolon
r_return
l_int|3
op_star
id|n
suffix:semicolon
)brace
r_case
l_int|4
suffix:colon
multiline_comment|/* 32 bit */
(brace
r_int
op_star
id|data
suffix:semicolon
id|count
op_div_assign
l_int|4
suffix:semicolon
id|data
op_assign
(paren
r_int
op_star
)paren
id|buf
suffix:semicolon
id|handshake
c_func
(paren
id|count
comma
id|dsp56k.maxio
comma
id|dsp56k.timeout
comma
id|DSP56K_RECEIVE
comma
id|put_user
c_func
(paren
id|dsp56k_host_interface.data.l
comma
id|data
op_plus
id|n
op_increment
)paren
)paren
suffix:semicolon
r_return
l_int|4
op_star
id|n
suffix:semicolon
)brace
)brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;DSP56k driver: Unknown minor device: %d&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
)brace
DECL|function|dsp56k_write
r_static
id|ssize_t
id|dsp56k_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
id|dev
op_assign
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_amp
l_int|0x0f
suffix:semicolon
r_switch
c_cond
(paren
id|dev
)paren
(brace
r_case
id|DSP56K_DEV_56001
suffix:colon
(brace
r_int
id|n
suffix:semicolon
multiline_comment|/* Don&squot;t do anything if nothing is to be done */
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
l_int|0
suffix:semicolon
id|n
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|dsp56k.tx_wsize
)paren
(brace
r_case
l_int|1
suffix:colon
multiline_comment|/* 8 bit */
(brace
id|handshake
c_func
(paren
id|count
comma
id|dsp56k.maxio
comma
id|dsp56k.timeout
comma
id|DSP56K_TRANSMIT
comma
id|get_user
c_func
(paren
id|dsp56k_host_interface.data.b
(braket
l_int|3
)braket
comma
id|buf
op_plus
id|n
op_increment
)paren
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
r_case
l_int|2
suffix:colon
multiline_comment|/* 16 bit */
(brace
r_int
op_star
id|data
suffix:semicolon
id|count
op_div_assign
l_int|2
suffix:semicolon
id|data
op_assign
(paren
r_int
op_star
)paren
id|buf
suffix:semicolon
id|handshake
c_func
(paren
id|count
comma
id|dsp56k.maxio
comma
id|dsp56k.timeout
comma
id|DSP56K_TRANSMIT
comma
id|get_user
c_func
(paren
id|dsp56k_host_interface.data.w
(braket
l_int|1
)braket
comma
id|data
op_plus
id|n
op_increment
)paren
)paren
suffix:semicolon
r_return
l_int|2
op_star
id|n
suffix:semicolon
)brace
r_case
l_int|3
suffix:colon
multiline_comment|/* 24 bit */
(brace
id|count
op_div_assign
l_int|3
suffix:semicolon
id|handshake
c_func
(paren
id|count
comma
id|dsp56k.maxio
comma
id|dsp56k.timeout
comma
id|DSP56K_TRANSMIT
comma
id|get_user
c_func
(paren
id|dsp56k_host_interface.data.b
(braket
l_int|1
)braket
comma
id|buf
op_plus
id|n
op_increment
)paren
suffix:semicolon
id|get_user
c_func
(paren
id|dsp56k_host_interface.data.b
(braket
l_int|2
)braket
comma
id|buf
op_plus
id|n
op_increment
)paren
suffix:semicolon
id|get_user
c_func
(paren
id|dsp56k_host_interface.data.b
(braket
l_int|3
)braket
comma
id|buf
op_plus
id|n
op_increment
)paren
)paren
suffix:semicolon
r_return
l_int|3
op_star
id|n
suffix:semicolon
)brace
r_case
l_int|4
suffix:colon
multiline_comment|/* 32 bit */
(brace
r_int
op_star
id|data
suffix:semicolon
id|count
op_div_assign
l_int|4
suffix:semicolon
id|data
op_assign
(paren
r_int
op_star
)paren
id|buf
suffix:semicolon
id|handshake
c_func
(paren
id|count
comma
id|dsp56k.maxio
comma
id|dsp56k.timeout
comma
id|DSP56K_TRANSMIT
comma
id|get_user
c_func
(paren
id|dsp56k_host_interface.data.l
comma
id|data
op_plus
id|n
op_increment
)paren
)paren
suffix:semicolon
r_return
l_int|4
op_star
id|n
suffix:semicolon
)brace
)brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;DSP56k driver: Unknown minor device: %d&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
)brace
DECL|function|dsp56k_ioctl
r_static
r_int
id|dsp56k_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
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
r_int
id|dev
op_assign
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_amp
l_int|0x0f
suffix:semicolon
r_switch
c_cond
(paren
id|dev
)paren
(brace
r_case
id|DSP56K_DEV_56001
suffix:colon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|DSP56K_UPLOAD
suffix:colon
(brace
r_char
op_star
id|bin
suffix:semicolon
r_int
id|r
comma
id|len
suffix:semicolon
r_struct
id|dsp56k_upload
op_star
id|binary
op_assign
(paren
r_struct
id|dsp56k_upload
op_star
)paren
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|len
comma
op_amp
id|binary-&gt;len
)paren
OL
l_int|0
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|bin
comma
op_amp
id|binary-&gt;bin
)paren
OL
l_int|0
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
op_eq
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* nothing to upload?!? */
)brace
r_if
c_cond
(paren
id|len
OG
id|DSP56K_MAX_BINARY_LENGTH
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|r
op_assign
id|dsp56k_upload
c_func
(paren
id|bin
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
OL
l_int|0
)paren
(brace
r_return
id|r
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
id|DSP56K_SET_TX_WSIZE
suffix:colon
r_if
c_cond
(paren
id|arg
OG
l_int|4
op_logical_or
id|arg
OL
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dsp56k.tx_wsize
op_assign
(paren
r_int
)paren
id|arg
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DSP56K_SET_RX_WSIZE
suffix:colon
r_if
c_cond
(paren
id|arg
OG
l_int|4
op_logical_or
id|arg
OL
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dsp56k.rx_wsize
op_assign
(paren
r_int
)paren
id|arg
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DSP56K_HOST_FLAGS
suffix:colon
(brace
r_int
id|dir
comma
id|out
comma
id|status
suffix:semicolon
r_struct
id|dsp56k_host_flags
op_star
id|hf
op_assign
(paren
r_struct
id|dsp56k_host_flags
op_star
)paren
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|dir
comma
op_amp
id|hf-&gt;dir
)paren
OL
l_int|0
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|out
comma
op_amp
id|hf-&gt;out
)paren
OL
l_int|0
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|dir
op_amp
l_int|0x1
)paren
op_logical_and
(paren
id|out
op_amp
l_int|0x1
)paren
)paren
id|dsp56k_host_interface.icr
op_or_assign
id|DSP56K_ICR_HF0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dir
op_amp
l_int|0x1
)paren
id|dsp56k_host_interface.icr
op_and_assign
op_complement
id|DSP56K_ICR_HF0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dir
op_amp
l_int|0x2
)paren
op_logical_and
(paren
id|out
op_amp
l_int|0x2
)paren
)paren
id|dsp56k_host_interface.icr
op_or_assign
id|DSP56K_ICR_HF1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dir
op_amp
l_int|0x2
)paren
id|dsp56k_host_interface.icr
op_and_assign
op_complement
id|DSP56K_ICR_HF1
suffix:semicolon
id|status
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dsp56k_host_interface.icr
op_amp
id|DSP56K_ICR_HF0
)paren
id|status
op_or_assign
l_int|0x1
suffix:semicolon
r_if
c_cond
(paren
id|dsp56k_host_interface.icr
op_amp
id|DSP56K_ICR_HF1
)paren
id|status
op_or_assign
l_int|0x2
suffix:semicolon
r_if
c_cond
(paren
id|dsp56k_host_interface.isr
op_amp
id|DSP56K_ISR_HF2
)paren
id|status
op_or_assign
l_int|0x4
suffix:semicolon
r_if
c_cond
(paren
id|dsp56k_host_interface.isr
op_amp
id|DSP56K_ISR_HF3
)paren
id|status
op_or_assign
l_int|0x8
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|status
comma
op_amp
id|hf-&gt;status
)paren
suffix:semicolon
)brace
r_case
id|DSP56K_HOST_CMD
suffix:colon
r_if
c_cond
(paren
id|arg
OG
l_int|31
op_logical_or
id|arg
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dsp56k_host_interface.cvr
op_assign
(paren
id|u_char
)paren
(paren
(paren
id|arg
op_amp
id|DSP56K_CVR_HV_MASK
)paren
op_or
id|DSP56K_CVR_HC
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;DSP56k driver: Unknown minor device: %d&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
)brace
multiline_comment|/* As of 2.1.26 this should be dsp56k_poll,&n; * but how do I then check device minor number?&n; * Do I need this function at all???&n; */
macro_line|#if 0
r_static
r_int
r_int
id|dsp56k_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
(brace
r_int
id|dev
op_assign
id|minor
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
op_amp
l_int|0x0f
suffix:semicolon
r_switch
c_cond
(paren
id|dev
)paren
(brace
r_case
id|DSP56K_DEV_56001
suffix:colon
multiline_comment|/* poll_wait(file, ???, wait); */
r_return
id|POLLIN
op_or
id|POLLRDNORM
op_or
id|POLLOUT
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;DSP56k driver: Unknown minor device: %d&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|function|dsp56k_open
r_static
r_int
id|dsp56k_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
id|dev
op_assign
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_amp
l_int|0x0f
suffix:semicolon
r_switch
c_cond
(paren
id|dev
)paren
(brace
r_case
id|DSP56K_DEV_56001
suffix:colon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|dsp56k.in_use
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|dsp56k.timeout
op_assign
id|TIMEOUT
suffix:semicolon
id|dsp56k.maxio
op_assign
id|MAXIO
suffix:semicolon
id|dsp56k.rx_wsize
op_assign
id|dsp56k.tx_wsize
op_assign
l_int|4
suffix:semicolon
id|DSP56K_TX_INT_OFF
suffix:semicolon
id|DSP56K_RX_INT_OFF
suffix:semicolon
multiline_comment|/* Zero host flags */
id|dsp56k_host_interface.icr
op_and_assign
op_complement
id|DSP56K_ICR_HF0
suffix:semicolon
id|dsp56k_host_interface.icr
op_and_assign
op_complement
id|DSP56K_ICR_HF1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dsp56k_release
r_static
r_int
id|dsp56k_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
id|dev
op_assign
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_amp
l_int|0x0f
suffix:semicolon
r_switch
c_cond
(paren
id|dev
)paren
(brace
r_case
id|DSP56K_DEV_56001
suffix:colon
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|dsp56k.in_use
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;DSP56k driver: Unknown minor device: %d&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|dsp56k_fops
r_static
r_struct
id|file_operations
id|dsp56k_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|read
op_assign
id|dsp56k_read
comma
dot
id|write
op_assign
id|dsp56k_write
comma
dot
id|ioctl
op_assign
id|dsp56k_ioctl
comma
dot
id|open
op_assign
id|dsp56k_open
comma
dot
id|release
op_assign
id|dsp56k_release
comma
)brace
suffix:semicolon
multiline_comment|/****** Init and module functions ******/
DECL|variable|devfs_handle
r_static
id|devfs_handle_t
id|devfs_handle
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|banner
(braket
)braket
id|__initdata
op_assign
id|KERN_INFO
l_string|&quot;DSP56k driver installed&bslash;n&quot;
suffix:semicolon
DECL|function|dsp56k_init_driver
r_static
r_int
id|__init
id|dsp56k_init_driver
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_ATARI
op_logical_or
op_logical_neg
id|ATARIHW_PRESENT
c_func
(paren
id|DSP56K
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;DSP56k driver: Hardware not present&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|DSP56K_MAJOR
comma
l_string|&quot;dsp56k&quot;
comma
op_amp
id|dsp56k_fops
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;DSP56k driver: Unable to register driver&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|devfs_handle
op_assign
id|devfs_register
c_func
(paren
l_int|NULL
comma
l_string|&quot;dsp56k&quot;
comma
id|DEVFS_FL_DEFAULT
comma
id|DSP56K_MAJOR
comma
l_int|0
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
op_amp
id|dsp56k_fops
comma
l_int|NULL
)paren
suffix:semicolon
id|printk
c_func
(paren
id|banner
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|dsp56k_init_driver
id|module_init
c_func
(paren
id|dsp56k_init_driver
)paren
suffix:semicolon
DECL|function|dsp56k_cleanup_driver
r_static
r_void
id|__exit
id|dsp56k_cleanup_driver
c_func
(paren
r_void
)paren
(brace
id|unregister_chrdev
c_func
(paren
id|DSP56K_MAJOR
comma
l_string|&quot;dsp56k&quot;
)paren
suffix:semicolon
id|devfs_unregister
c_func
(paren
id|devfs_handle
)paren
suffix:semicolon
)brace
DECL|variable|dsp56k_cleanup_driver
id|module_exit
c_func
(paren
id|dsp56k_cleanup_driver
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
