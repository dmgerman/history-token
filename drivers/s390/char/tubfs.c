multiline_comment|/*&n; *  IBM/3270 Driver -- Copyright (C) UTS Global LLC&n; *&n; *  tubfs.c -- Fullscreen driver&n; *&n; *&n; *&n; *&n; *&n; *  Author:  Richard Hitt&n; */
macro_line|#include &quot;tubio.h&quot;
DECL|variable|fs3270_major
r_int
id|fs3270_major
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* init to impossible -1 */
r_static
r_int
id|fs3270_open
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
r_int
id|fs3270_close
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
r_int
id|fs3270_ioctl
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
r_static
id|ssize_t
id|fs3270_read
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
id|ssize_t
id|fs3270_write
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
suffix:semicolon
r_static
r_int
id|fs3270_wait
c_func
(paren
id|tub_t
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_static
r_void
id|fs3270_int
c_func
(paren
id|tub_t
op_star
id|tubp
comma
id|devstat_t
op_star
id|dsp
)paren
suffix:semicolon
r_extern
r_void
id|tty3270_refresh
c_func
(paren
id|tub_t
op_star
)paren
suffix:semicolon
DECL|variable|fs3270_fops
r_static
r_struct
id|file_operations
id|fs3270_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
multiline_comment|/* owner */
dot
id|read
op_assign
id|fs3270_read
comma
multiline_comment|/* read */
dot
id|write
op_assign
id|fs3270_write
comma
multiline_comment|/* write */
dot
id|ioctl
op_assign
id|fs3270_ioctl
comma
multiline_comment|/* ioctl */
dot
id|open
op_assign
id|fs3270_open
comma
multiline_comment|/* open */
dot
id|release
op_assign
id|fs3270_close
comma
multiline_comment|/* release */
)brace
suffix:semicolon
multiline_comment|/*&n; * fs3270_init() -- Initialize fullscreen tubes&n; */
r_int
DECL|function|fs3270_init
id|fs3270_init
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
suffix:semicolon
id|rc
op_assign
id|register_chrdev
c_func
(paren
id|IBM_FS3270_MAJOR
comma
l_string|&quot;fs3270&quot;
comma
op_amp
id|fs3270_fops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;tubmod can&squot;t get major nbr %d: error %d&bslash;n&quot;
comma
id|IBM_FS3270_MAJOR
comma
id|rc
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|devfs_mk_dir
c_func
(paren
l_string|&quot;3270&quot;
)paren
suffix:semicolon
id|devfs_mk_cdev
c_func
(paren
id|MKDEV
c_func
(paren
id|IBM_FS3270_MAJOR
comma
l_int|0
)paren
comma
id|S_IFCHR
op_or
id|S_IRUGO
op_or
id|S_IWUGO
comma
l_string|&quot;3270/tub&quot;
)paren
suffix:semicolon
id|fs3270_major
op_assign
id|IBM_FS3270_MAJOR
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * fs3270_fini() -- Uninitialize fullscreen tubes&n; */
r_void
DECL|function|fs3270_fini
id|fs3270_fini
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|fs3270_major
op_ne
op_minus
l_int|1
)paren
(brace
id|devfs_remove
c_func
(paren
l_string|&quot;3270&quot;
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;3270/tub&quot;
)paren
suffix:semicolon
id|unregister_chrdev
c_func
(paren
id|fs3270_major
comma
l_string|&quot;fs3270&quot;
)paren
suffix:semicolon
id|fs3270_major
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * fs3270_open&n; */
r_static
r_int
DECL|function|fs3270_open
id|fs3270_open
c_func
(paren
r_struct
id|inode
op_star
id|ip
comma
r_struct
id|file
op_star
id|fp
)paren
(brace
id|tub_t
op_star
id|tubp
suffix:semicolon
r_int
id|flags
suffix:semicolon
multiline_comment|/* See INODE2TUB(ip) for handling of &quot;/dev/3270/tub&quot; */
r_if
c_cond
(paren
(paren
id|tubp
op_assign
id|INODE2TUB
c_func
(paren
id|ip
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
id|TUBLOCK
c_func
(paren
id|tubp-&gt;irq
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tubp-&gt;mode
op_eq
id|TBM_FS
op_logical_or
id|tubp-&gt;mode
op_eq
id|TBM_FSLN
)paren
(brace
id|TUBUNLOCK
c_func
(paren
id|tubp-&gt;irq
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|fp-&gt;private_data
op_assign
id|ip
suffix:semicolon
id|tubp-&gt;mode
op_assign
id|TBM_FS
suffix:semicolon
id|tubp-&gt;intv
op_assign
id|fs3270_int
suffix:semicolon
id|tubp-&gt;dstat
op_assign
l_int|0
suffix:semicolon
id|tubp-&gt;fs_pid
op_assign
id|current-&gt;pid
suffix:semicolon
id|tubp-&gt;fsopen
op_assign
l_int|1
suffix:semicolon
id|TUBUNLOCK
c_func
(paren
id|tubp-&gt;irq
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * fs3270_close aka release:  free the irq&n; */
r_static
r_int
DECL|function|fs3270_close
id|fs3270_close
c_func
(paren
r_struct
id|inode
op_star
id|ip
comma
r_struct
id|file
op_star
id|fp
)paren
(brace
id|tub_t
op_star
id|tubp
suffix:semicolon
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tubp
op_assign
id|INODE2TUB
c_func
(paren
id|ip
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|fs3270_wait
c_func
(paren
id|tubp
comma
op_amp
id|flags
)paren
suffix:semicolon
id|tubp-&gt;fsopen
op_assign
l_int|0
suffix:semicolon
id|tubp-&gt;fs_pid
op_assign
l_int|0
suffix:semicolon
id|tubp-&gt;intv
op_assign
l_int|NULL
suffix:semicolon
id|tubp-&gt;mode
op_assign
l_int|0
suffix:semicolon
id|tty3270_refresh
c_func
(paren
id|tubp
)paren
suffix:semicolon
id|TUBUNLOCK
c_func
(paren
id|tubp-&gt;irq
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * fs3270_release() called from tty3270_hangup()&n; */
r_void
DECL|function|fs3270_release
id|fs3270_release
c_func
(paren
id|tub_t
op_star
id|tubp
)paren
(brace
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|tubp-&gt;mode
op_ne
id|TBM_FS
)paren
r_return
suffix:semicolon
id|fs3270_wait
c_func
(paren
id|tubp
comma
op_amp
id|flags
)paren
suffix:semicolon
id|tubp-&gt;fsopen
op_assign
l_int|0
suffix:semicolon
id|tubp-&gt;fs_pid
op_assign
l_int|0
suffix:semicolon
id|tubp-&gt;intv
op_assign
l_int|NULL
suffix:semicolon
id|tubp-&gt;mode
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*tty3270_refresh(tubp);*/
id|TUBUNLOCK
c_func
(paren
id|tubp-&gt;irq
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * fs3270_wait(tub_t *tubp, int *flags) -- Wait to use tube&n; * Entered without irq lock&n; * On return:&n; *      * Lock is held&n; *      * Value is 0 or -ERESTARTSYS&n; */
r_static
r_int
DECL|function|fs3270_wait
id|fs3270_wait
c_func
(paren
id|tub_t
op_star
id|tubp
comma
r_int
op_star
id|flags
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|TUBLOCK
c_func
(paren
id|tubp-&gt;irq
comma
op_star
id|flags
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|tubp-&gt;waitq
comma
op_amp
id|wait
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|signal_pending
c_func
(paren
id|current
)paren
op_logical_and
(paren
(paren
id|tubp-&gt;mode
op_ne
id|TBM_FS
)paren
op_logical_or
(paren
id|tubp-&gt;flags
op_amp
(paren
id|TUB_WORKING
op_or
id|TUB_RDPENDING
)paren
)paren
op_ne
l_int|0
)paren
)paren
(brace
macro_line|#warning FIXME: [kj] use set_current_state instead of current-&gt;state=
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|TUBUNLOCK
c_func
(paren
id|tubp-&gt;irq
comma
op_star
id|flags
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
macro_line|#warning FIXME: [kj] use set_current_state instead of current-&gt;state=
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|TUBLOCK
c_func
(paren
id|tubp-&gt;irq
comma
op_star
id|flags
)paren
suffix:semicolon
)brace
id|remove_wait_queue
c_func
(paren
op_amp
id|tubp-&gt;waitq
comma
op_amp
id|wait
)paren
suffix:semicolon
r_return
id|signal_pending
c_func
(paren
id|current
)paren
ques
c_cond
op_minus
id|ERESTARTSYS
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * fs3270_io(tubp, ccw1_t*) -- start I/O on the tube&n; * Entered with irq lock held, WORKING off&n; */
r_static
r_int
DECL|function|fs3270_io
id|fs3270_io
c_func
(paren
id|tub_t
op_star
id|tubp
comma
id|ccw1_t
op_star
id|ccwp
)paren
(brace
r_int
id|rc
suffix:semicolon
id|rc
op_assign
id|do_IO
c_func
(paren
id|tubp-&gt;irq
comma
id|ccwp
comma
id|tubp-&gt;irq
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|tubp-&gt;flags
op_or_assign
id|TUB_WORKING
suffix:semicolon
id|tubp-&gt;dstat
op_assign
l_int|0
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * fs3270_tasklet(tubp) -- Perform back-half processing&n; */
r_static
r_void
DECL|function|fs3270_tasklet
id|fs3270_tasklet
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_int
id|flags
suffix:semicolon
id|tub_t
op_star
id|tubp
suffix:semicolon
id|addr_t
op_star
id|ip
suffix:semicolon
id|tubp
op_assign
(paren
id|tub_t
op_star
)paren
id|data
suffix:semicolon
id|TUBLOCK
c_func
(paren
id|tubp-&gt;irq
comma
id|flags
)paren
suffix:semicolon
id|tubp-&gt;flags
op_and_assign
op_complement
id|TUB_BHPENDING
suffix:semicolon
r_if
c_cond
(paren
id|tubp-&gt;wbuf
)paren
(brace
multiline_comment|/* if we were writing */
r_for
c_loop
(paren
id|ip
op_assign
id|tubp-&gt;wbuf
suffix:semicolon
id|ip
OL
id|tubp-&gt;wbuf
op_plus
l_int|33
suffix:semicolon
id|ip
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|ip
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|kfree
c_func
(paren
id|phys_to_virt
c_func
(paren
op_star
id|ip
)paren
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|tubp-&gt;wbuf
)paren
suffix:semicolon
id|tubp-&gt;wbuf
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|tubp-&gt;flags
op_amp
(paren
id|TUB_ATTN
op_or
id|TUB_RDPENDING
)paren
)paren
op_eq
(paren
id|TUB_ATTN
op_or
id|TUB_RDPENDING
)paren
)paren
(brace
id|fs3270_io
c_func
(paren
id|tubp
comma
op_amp
id|tubp-&gt;rccw
)paren
suffix:semicolon
id|tubp-&gt;flags
op_and_assign
op_complement
(paren
id|TUB_ATTN
op_or
id|TUB_RDPENDING
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|tubp-&gt;flags
op_amp
id|TUB_WORKING
)paren
op_eq
l_int|0
)paren
id|wake_up_interruptible
c_func
(paren
op_amp
id|tubp-&gt;waitq
)paren
suffix:semicolon
id|TUBUNLOCK
c_func
(paren
id|tubp-&gt;irq
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * fs3270_sched_tasklet(tubp) -- Schedule the back half&n; * Irq lock must be held on entry and remains held on exit.&n; */
r_static
r_void
DECL|function|fs3270_sched_tasklet
id|fs3270_sched_tasklet
c_func
(paren
id|tub_t
op_star
id|tubp
)paren
(brace
r_if
c_cond
(paren
id|tubp-&gt;flags
op_amp
id|TUB_BHPENDING
)paren
r_return
suffix:semicolon
id|tubp-&gt;flags
op_or_assign
id|TUB_BHPENDING
suffix:semicolon
id|tasklet_init
c_func
(paren
op_amp
id|tubp-&gt;tasklet
comma
id|fs3270_tasklet
comma
(paren
r_int
r_int
)paren
id|tubp
)paren
suffix:semicolon
id|tasklet_schedule
c_func
(paren
op_amp
id|tubp-&gt;tasklet
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * fs3270_int(tubp, prp) -- Process interrupt from tube in FS mode&n; * This routine is entered with irq lock held (see do_IRQ in s390io.c)&n; */
r_static
r_void
DECL|function|fs3270_int
id|fs3270_int
c_func
(paren
id|tub_t
op_star
id|tubp
comma
id|devstat_t
op_star
id|dsp
)paren
(brace
DECL|macro|DEV_UE_BUSY
mdefine_line|#define&t;DEV_UE_BUSY &bslash;&n;&t;(DEV_STAT_CHN_END | DEV_STAT_DEV_END | DEV_STAT_UNIT_EXCEP)
macro_line|#ifdef RBHNOTYET
multiline_comment|/* XXX needs more work; must save 2d arg to fs370_io() */
multiline_comment|/* Handle CE-DE-UE and subsequent UDE */
r_if
c_cond
(paren
id|dsp-&gt;dstat
op_eq
id|DEV_UE_BUSY
)paren
(brace
id|tubp-&gt;flags
op_or_assign
id|TUB_UE_BUSY
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|tubp-&gt;flags
op_amp
id|TUB_UE_BUSY
)paren
(brace
id|tubp-&gt;flags
op_and_assign
op_complement
id|TUB_UE_BUSY
suffix:semicolon
r_if
c_cond
(paren
id|dsp-&gt;dstat
op_eq
id|DEV_STAT_DEV_END
op_logical_and
(paren
id|tubp-&gt;flags
op_amp
id|TUB_WORKING
)paren
op_ne
l_int|0
)paren
(brace
id|fs3270_io
c_func
(paren
id|tubp
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/* Handle ATTN */
r_if
c_cond
(paren
id|dsp-&gt;dstat
op_amp
id|DEV_STAT_ATTENTION
)paren
id|tubp-&gt;flags
op_or_assign
id|TUB_ATTN
suffix:semicolon
r_if
c_cond
(paren
id|dsp-&gt;dstat
op_amp
id|DEV_STAT_CHN_END
)paren
(brace
id|tubp-&gt;cswl
op_assign
id|dsp-&gt;rescnt
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dsp-&gt;dstat
op_amp
id|DEV_STAT_DEV_END
)paren
op_eq
l_int|0
)paren
id|tubp-&gt;flags
op_or_assign
id|TUB_EXPECT_DE
suffix:semicolon
r_else
id|tubp-&gt;flags
op_and_assign
op_complement
id|TUB_EXPECT_DE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dsp-&gt;dstat
op_amp
id|DEV_STAT_DEV_END
)paren
(brace
r_if
c_cond
(paren
(paren
id|tubp-&gt;flags
op_amp
id|TUB_EXPECT_DE
)paren
op_eq
l_int|0
)paren
id|tubp-&gt;flags
op_or_assign
id|TUB_UNSOL_DE
suffix:semicolon
id|tubp-&gt;flags
op_and_assign
op_complement
id|TUB_EXPECT_DE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dsp-&gt;dstat
op_amp
id|DEV_STAT_DEV_END
)paren
id|tubp-&gt;flags
op_and_assign
op_complement
id|TUB_WORKING
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tubp-&gt;flags
op_amp
id|TUB_WORKING
)paren
op_eq
l_int|0
)paren
id|fs3270_sched_tasklet
c_func
(paren
id|tubp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * process ioctl commands for the tube driver&n; */
r_static
r_int
DECL|function|fs3270_ioctl
id|fs3270_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|ip
comma
r_struct
id|file
op_star
id|fp
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
id|tub_t
op_star
id|tubp
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tubp
op_assign
id|INODE2TUB
c_func
(paren
id|ip
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|fs3270_wait
c_func
(paren
id|tubp
comma
op_amp
id|flags
)paren
)paren
)paren
(brace
id|TUBUNLOCK
c_func
(paren
id|tubp-&gt;irq
comma
id|flags
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|TUBICMD
suffix:colon
id|tubp-&gt;icmd
op_assign
id|arg
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TUBOCMD
suffix:colon
id|tubp-&gt;ocmd
op_assign
id|arg
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TUBGETI
suffix:colon
id|put_user
c_func
(paren
id|tubp-&gt;icmd
comma
(paren
r_char
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TUBGETO
suffix:colon
id|put_user
c_func
(paren
id|tubp-&gt;ocmd
comma
(paren
r_char
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TUBGETMOD
suffix:colon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_char
op_star
)paren
id|arg
comma
op_amp
id|tubp-&gt;tubiocb
comma
r_sizeof
id|tubp-&gt;tubiocb
)paren
)paren
id|rc
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|TUBUNLOCK
c_func
(paren
id|tubp-&gt;irq
comma
id|flags
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * process read commands for the tube driver&n; */
r_static
id|ssize_t
DECL|function|fs3270_read
id|fs3270_read
c_func
(paren
r_struct
id|file
op_star
id|fp
comma
r_char
op_star
id|dp
comma
r_int
id|len
comma
id|loff_t
op_star
id|off
)paren
(brace
id|tub_t
op_star
id|tubp
suffix:semicolon
r_char
op_star
id|kp
suffix:semicolon
id|ccw1_t
op_star
id|cp
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_int
id|flags
suffix:semicolon
id|addr_t
op_star
id|idalp
comma
op_star
id|ip
suffix:semicolon
r_char
op_star
id|tp
suffix:semicolon
r_int
id|count
comma
id|piece
suffix:semicolon
r_int
id|size
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|0
op_logical_or
id|len
OG
l_int|65535
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|tubp
op_assign
id|INODE2TUB
c_func
(paren
(paren
r_struct
id|inode
op_star
)paren
id|fp-&gt;private_data
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|ip
op_assign
id|idalp
op_assign
id|kmalloc
c_func
(paren
l_int|33
op_star
r_sizeof
(paren
id|addr_t
)paren
comma
id|GFP_ATOMIC
op_or
id|GFP_DMA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idalp
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|memset
c_func
(paren
id|idalp
comma
l_int|0
comma
l_int|33
op_star
r_sizeof
op_star
id|idalp
)paren
suffix:semicolon
id|count
op_assign
id|len
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
id|piece
op_assign
id|MIN
c_func
(paren
id|count
comma
l_int|0x800
)paren
suffix:semicolon
id|size
op_assign
id|count
op_eq
id|len
ques
c_cond
id|piece
suffix:colon
l_int|0x800
suffix:semicolon
r_if
c_cond
(paren
(paren
id|kp
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
op_or
id|GFP_DMA
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|len
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|do_cleanup
suffix:semicolon
)brace
op_star
id|ip
op_increment
op_assign
id|virt_to_phys
c_func
(paren
id|kp
)paren
suffix:semicolon
id|count
op_sub_assign
id|piece
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|fs3270_wait
c_func
(paren
id|tubp
comma
op_amp
id|flags
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|TUBUNLOCK
c_func
(paren
id|tubp-&gt;irq
comma
id|flags
)paren
suffix:semicolon
id|len
op_assign
id|rc
suffix:semicolon
r_goto
id|do_cleanup
suffix:semicolon
)brace
id|cp
op_assign
op_amp
id|tubp-&gt;rccw
suffix:semicolon
r_if
c_cond
(paren
id|tubp-&gt;icmd
op_eq
l_int|0
op_logical_and
id|tubp-&gt;ocmd
op_ne
l_int|0
)paren
id|tubp-&gt;icmd
op_assign
l_int|6
suffix:semicolon
id|cp-&gt;cmd_code
op_assign
id|tubp-&gt;icmd
ques
c_cond
suffix:colon
l_int|2
suffix:semicolon
id|cp-&gt;flags
op_assign
id|CCW_FLAG_SLI
op_or
id|CCW_FLAG_IDA
suffix:semicolon
id|cp-&gt;count
op_assign
id|len
suffix:semicolon
id|cp-&gt;cda
op_assign
id|virt_to_phys
c_func
(paren
id|idalp
)paren
suffix:semicolon
id|tubp-&gt;flags
op_or_assign
id|TUB_RDPENDING
suffix:semicolon
id|TUBUNLOCK
c_func
(paren
id|tubp-&gt;irq
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|fs3270_wait
c_func
(paren
id|tubp
comma
op_amp
id|flags
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|tubp-&gt;flags
op_and_assign
op_complement
id|TUB_RDPENDING
suffix:semicolon
id|len
op_assign
id|rc
suffix:semicolon
id|TUBUNLOCK
c_func
(paren
id|tubp-&gt;irq
comma
id|flags
)paren
suffix:semicolon
r_goto
id|do_cleanup
suffix:semicolon
)brace
id|TUBUNLOCK
c_func
(paren
id|tubp-&gt;irq
comma
id|flags
)paren
suffix:semicolon
id|len
op_sub_assign
id|tubp-&gt;cswl
suffix:semicolon
id|count
op_assign
id|len
suffix:semicolon
id|tp
op_assign
id|dp
suffix:semicolon
id|ip
op_assign
id|idalp
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
id|piece
op_assign
id|MIN
c_func
(paren
id|count
comma
l_int|0x800
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|tp
comma
id|phys_to_virt
c_func
(paren
op_star
id|ip
)paren
comma
id|piece
)paren
op_ne
l_int|0
)paren
(brace
id|len
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|do_cleanup
suffix:semicolon
)brace
id|count
op_sub_assign
id|piece
suffix:semicolon
id|tp
op_add_assign
id|piece
suffix:semicolon
id|ip
op_increment
suffix:semicolon
)brace
id|do_cleanup
suffix:colon
r_for
c_loop
(paren
id|ip
op_assign
id|idalp
suffix:semicolon
id|ip
OL
id|idalp
op_plus
l_int|33
suffix:semicolon
id|ip
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|ip
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|kfree
c_func
(paren
id|phys_to_virt
c_func
(paren
op_star
id|ip
)paren
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|idalp
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n; * process write commands for the tube driver&n; */
r_static
id|ssize_t
DECL|function|fs3270_write
id|fs3270_write
c_func
(paren
r_struct
id|file
op_star
id|fp
comma
r_const
r_char
op_star
id|dp
comma
r_int
id|len
comma
id|loff_t
op_star
id|off
)paren
(brace
id|tub_t
op_star
id|tubp
suffix:semicolon
id|ccw1_t
op_star
id|cp
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_int
id|flags
suffix:semicolon
r_void
op_star
id|kb
suffix:semicolon
id|addr_t
op_star
id|idalp
comma
op_star
id|ip
suffix:semicolon
r_int
id|count
comma
id|piece
suffix:semicolon
r_int
id|index
suffix:semicolon
r_int
id|size
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|65535
op_logical_or
id|len
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Locate the tube */
r_if
c_cond
(paren
(paren
id|tubp
op_assign
id|INODE2TUB
c_func
(paren
(paren
r_struct
id|inode
op_star
)paren
id|fp-&gt;private_data
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|ip
op_assign
id|idalp
op_assign
id|kmalloc
c_func
(paren
l_int|33
op_star
r_sizeof
(paren
id|addr_t
)paren
comma
id|GFP_ATOMIC
op_or
id|GFP_DMA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idalp
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|memset
c_func
(paren
id|idalp
comma
l_int|0
comma
l_int|33
op_star
r_sizeof
op_star
id|idalp
)paren
suffix:semicolon
id|count
op_assign
id|len
suffix:semicolon
id|index
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
id|piece
op_assign
id|MIN
c_func
(paren
id|count
comma
l_int|0x800
)paren
suffix:semicolon
id|size
op_assign
id|count
op_eq
id|len
ques
c_cond
id|piece
suffix:colon
l_int|0x800
suffix:semicolon
r_if
c_cond
(paren
(paren
id|kb
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
op_or
id|GFP_DMA
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|len
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|do_cleanup
suffix:semicolon
)brace
op_star
id|ip
op_increment
op_assign
id|virt_to_phys
c_func
(paren
id|kb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|kb
comma
op_amp
id|dp
(braket
id|index
)braket
comma
id|piece
)paren
op_ne
l_int|0
)paren
(brace
id|len
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|do_cleanup
suffix:semicolon
)brace
id|count
op_sub_assign
id|piece
suffix:semicolon
id|index
op_add_assign
id|piece
suffix:semicolon
)brace
multiline_comment|/* Wait till tube&squot;s not working or signal is pending */
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|fs3270_wait
c_func
(paren
id|tubp
comma
op_amp
id|flags
)paren
)paren
)paren
(brace
id|len
op_assign
id|rc
suffix:semicolon
id|TUBUNLOCK
c_func
(paren
id|tubp-&gt;irq
comma
id|flags
)paren
suffix:semicolon
r_goto
id|do_cleanup
suffix:semicolon
)brace
multiline_comment|/* Make CCW and start I/O.  Back end will free buffers &amp; idal. */
id|tubp-&gt;wbuf
op_assign
id|idalp
suffix:semicolon
id|cp
op_assign
op_amp
id|tubp-&gt;wccw
suffix:semicolon
id|cp-&gt;cmd_code
op_assign
id|tubp-&gt;ocmd
ques
c_cond
id|tubp-&gt;ocmd
op_eq
l_int|5
ques
c_cond
l_int|13
suffix:colon
id|tubp-&gt;ocmd
suffix:colon
l_int|1
suffix:semicolon
id|cp-&gt;flags
op_assign
id|CCW_FLAG_SLI
op_or
id|CCW_FLAG_IDA
suffix:semicolon
id|cp-&gt;count
op_assign
id|len
suffix:semicolon
id|cp-&gt;cda
op_assign
id|virt_to_phys
c_func
(paren
id|tubp-&gt;wbuf
)paren
suffix:semicolon
id|fs3270_io
c_func
(paren
id|tubp
comma
id|cp
)paren
suffix:semicolon
id|TUBUNLOCK
c_func
(paren
id|tubp-&gt;irq
comma
id|flags
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
id|do_cleanup
suffix:colon
r_for
c_loop
(paren
id|ip
op_assign
id|idalp
suffix:semicolon
id|ip
OL
id|idalp
op_plus
l_int|33
suffix:semicolon
id|ip
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|ip
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|kfree
c_func
(paren
id|phys_to_virt
c_func
(paren
op_star
id|ip
)paren
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|idalp
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
eof
