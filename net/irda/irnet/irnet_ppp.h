multiline_comment|/*&n; *&t;IrNET protocol module : Synchronous PPP over an IrDA socket.&n; *&n; *&t;&t;Jean II - HPL `00 - &lt;jt@hpl.hp.com&gt;&n; *&n; * This file contains all definitions and declarations necessary for the&n; * PPP part of the IrNET module.&n; * This file is a private header, so other modules don&squot;t want to know&n; * what&squot;s in there...&n; */
macro_line|#ifndef IRNET_PPP_H
DECL|macro|IRNET_PPP_H
mdefine_line|#define IRNET_PPP_H
multiline_comment|/***************************** INCLUDES *****************************/
macro_line|#include &quot;irnet.h&quot;&t;&t;/* Module global include */
multiline_comment|/************************ CONSTANTS &amp; MACROS ************************/
multiline_comment|/* /dev/irnet file constants */
DECL|macro|IRNET_MAJOR
mdefine_line|#define IRNET_MAJOR&t;10&t;/* Misc range */
DECL|macro|IRNET_MINOR
mdefine_line|#define IRNET_MINOR&t;187&t;/* Official allocation */
multiline_comment|/* IrNET control channel stuff */
DECL|macro|IRNET_MAX_COMMAND
mdefine_line|#define IRNET_MAX_COMMAND&t;256&t;/* Max length of a command line */
multiline_comment|/* PPP hardcore stuff */
multiline_comment|/* Bits in rbits (PPP flags in irnet struct) */
DECL|macro|SC_RCV_BITS
mdefine_line|#define SC_RCV_BITS&t;(SC_RCV_B7_1|SC_RCV_B7_0|SC_RCV_ODDP|SC_RCV_EVNP)
multiline_comment|/* Bit numbers in busy */
DECL|macro|XMIT_BUSY
mdefine_line|#define XMIT_BUSY&t;0
DECL|macro|RECV_BUSY
mdefine_line|#define RECV_BUSY&t;1
DECL|macro|XMIT_WAKEUP
mdefine_line|#define XMIT_WAKEUP&t;2
DECL|macro|XMIT_FULL
mdefine_line|#define XMIT_FULL&t;3
multiline_comment|/* Queue management */
DECL|macro|PPPSYNC_MAX_RQLEN
mdefine_line|#define PPPSYNC_MAX_RQLEN&t;32&t;/* arbitrary */
multiline_comment|/****************************** TYPES ******************************/
multiline_comment|/**************************** PROTOTYPES ****************************/
multiline_comment|/* ----------------------- CONTROL CHANNEL ----------------------- */
r_static
r_inline
id|ssize_t
id|irnet_ctrl_write
c_func
(paren
id|irnet_socket
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_inline
id|ssize_t
id|irnet_ctrl_read
c_func
(paren
id|irnet_socket
op_star
comma
r_struct
id|file
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_inline
r_int
r_int
id|irnet_ctrl_poll
c_func
(paren
id|irnet_socket
op_star
comma
r_struct
id|file
op_star
comma
id|poll_table
op_star
)paren
suffix:semicolon
multiline_comment|/* ----------------------- CHARACTER DEVICE ----------------------- */
r_static
r_int
id|dev_irnet_open
c_func
(paren
r_struct
id|inode
op_star
comma
multiline_comment|/* fs callback : open */
r_struct
id|file
op_star
)paren
comma
id|dev_irnet_close
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_static
id|ssize_t
id|dev_irnet_write
c_func
(paren
r_struct
id|file
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
comma
id|dev_irnet_read
c_func
(paren
r_struct
id|file
op_star
comma
r_char
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
r_static
r_int
r_int
id|dev_irnet_poll
c_func
(paren
r_struct
id|file
op_star
comma
id|poll_table
op_star
)paren
suffix:semicolon
r_static
r_int
id|dev_irnet_ioctl
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* ------------------------ PPP INTERFACE ------------------------ */
r_static
r_inline
r_struct
id|sk_buff
op_star
id|irnet_prepare_skb
c_func
(paren
id|irnet_socket
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_static
r_int
id|ppp_irnet_send
c_func
(paren
r_struct
id|ppp_channel
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_static
r_int
id|ppp_irnet_ioctl
c_func
(paren
r_struct
id|ppp_channel
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/**************************** VARIABLES ****************************/
multiline_comment|/* Filesystem callbacks (to call us) */
DECL|variable|irnet_device_fops
r_static
r_struct
id|file_operations
id|irnet_device_fops
op_assign
(brace
id|read
suffix:colon
id|dev_irnet_read
comma
id|write
suffix:colon
id|dev_irnet_write
comma
id|poll
suffix:colon
id|dev_irnet_poll
comma
id|ioctl
suffix:colon
id|dev_irnet_ioctl
comma
id|open
suffix:colon
id|dev_irnet_open
comma
id|release
suffix:colon
id|dev_irnet_close
multiline_comment|/* Also : llseek, readdir, mmap, flush, fsync, fasync, lock, readv, writev */
)brace
suffix:semicolon
multiline_comment|/* Structure so that the misc major (drivers/char/misc.c) take care of us... */
DECL|variable|irnet_misc_device
r_static
r_struct
id|miscdevice
id|irnet_misc_device
op_assign
(brace
id|IRNET_MINOR
comma
l_string|&quot;irnet&quot;
comma
op_amp
id|irnet_device_fops
)brace
suffix:semicolon
multiline_comment|/* Generic PPP callbacks (to call us) */
DECL|variable|irnet_ppp_ops
r_struct
id|ppp_channel_ops
id|irnet_ppp_ops
op_assign
(brace
id|ppp_irnet_send
comma
id|ppp_irnet_ioctl
)brace
suffix:semicolon
macro_line|#endif /* IRNET_PPP_H */
eof
