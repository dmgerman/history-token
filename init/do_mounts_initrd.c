DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/romfs_fs.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &quot;do_mounts.h&quot;
DECL|variable|initrd_start
DECL|variable|initrd_end
r_int
r_int
id|initrd_start
comma
id|initrd_end
suffix:semicolon
DECL|variable|initrd_below_start_ok
r_int
id|initrd_below_start_ok
suffix:semicolon
DECL|variable|real_root_dev
r_int
r_int
id|real_root_dev
suffix:semicolon
multiline_comment|/* do_proc_dointvec cannot handle kdev_t */
DECL|variable|old_fd
DECL|variable|root_fd
r_static
r_int
id|__initdata
id|old_fd
comma
id|root_fd
suffix:semicolon
DECL|variable|mount_initrd
r_static
r_int
id|__initdata
id|mount_initrd
op_assign
l_int|1
suffix:semicolon
DECL|function|no_initrd
r_static
r_int
id|__init
id|no_initrd
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|mount_initrd
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;noinitrd&quot;
comma
id|no_initrd
)paren
suffix:semicolon
DECL|function|do_linuxrc
r_static
r_int
id|__init
id|do_linuxrc
c_func
(paren
r_void
op_star
id|shell
)paren
(brace
r_static
r_char
op_star
id|argv
(braket
)braket
op_assign
(brace
l_string|&quot;linuxrc&quot;
comma
l_int|NULL
comma
)brace
suffix:semicolon
r_extern
r_char
op_star
id|envp_init
(braket
)braket
suffix:semicolon
id|sys_close
c_func
(paren
id|old_fd
)paren
suffix:semicolon
id|sys_close
c_func
(paren
id|root_fd
)paren
suffix:semicolon
id|sys_close
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|sys_close
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|sys_close
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|sys_setsid
c_func
(paren
)paren
suffix:semicolon
(paren
r_void
)paren
id|sys_open
c_func
(paren
l_string|&quot;/dev/console&quot;
comma
id|O_RDWR
comma
l_int|0
)paren
suffix:semicolon
(paren
r_void
)paren
id|sys_dup
c_func
(paren
l_int|0
)paren
suffix:semicolon
(paren
r_void
)paren
id|sys_dup
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_return
id|execve
c_func
(paren
id|shell
comma
id|argv
comma
id|envp_init
)paren
suffix:semicolon
)brace
DECL|function|handle_initrd
r_static
r_void
id|__init
id|handle_initrd
c_func
(paren
r_void
)paren
(brace
r_int
id|error
suffix:semicolon
r_int
id|i
comma
id|pid
suffix:semicolon
id|real_root_dev
op_assign
id|new_encode_dev
c_func
(paren
id|ROOT_DEV
)paren
suffix:semicolon
id|create_dev
c_func
(paren
l_string|&quot;/dev/root.old&quot;
comma
id|Root_RAM0
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* mount initrd on rootfs&squot; /root */
id|mount_block_root
c_func
(paren
l_string|&quot;/dev/root.old&quot;
comma
id|root_mountflags
op_amp
op_complement
id|MS_RDONLY
)paren
suffix:semicolon
id|sys_mkdir
c_func
(paren
l_string|&quot;/old&quot;
comma
l_int|0700
)paren
suffix:semicolon
id|root_fd
op_assign
id|sys_open
c_func
(paren
l_string|&quot;/&quot;
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|old_fd
op_assign
id|sys_open
c_func
(paren
l_string|&quot;/old&quot;
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* move initrd over / and chdir/chroot in initrd root */
id|sys_chdir
c_func
(paren
l_string|&quot;/root&quot;
)paren
suffix:semicolon
id|sys_mount
c_func
(paren
l_string|&quot;.&quot;
comma
l_string|&quot;/&quot;
comma
l_int|NULL
comma
id|MS_MOVE
comma
l_int|NULL
)paren
suffix:semicolon
id|sys_chroot
c_func
(paren
l_string|&quot;.&quot;
)paren
suffix:semicolon
id|mount_devfs_fs
(paren
)paren
suffix:semicolon
id|pid
op_assign
id|kernel_thread
c_func
(paren
id|do_linuxrc
comma
l_string|&quot;/linuxrc&quot;
comma
id|SIGCHLD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OG
l_int|0
)paren
(brace
r_while
c_loop
(paren
id|pid
op_ne
id|sys_wait4
c_func
(paren
op_minus
l_int|1
comma
op_amp
id|i
comma
l_int|0
comma
l_int|NULL
)paren
)paren
id|yield
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* move initrd to rootfs&squot; /old */
id|sys_fchdir
c_func
(paren
id|old_fd
)paren
suffix:semicolon
id|sys_mount
c_func
(paren
l_string|&quot;/&quot;
comma
l_string|&quot;.&quot;
comma
l_int|NULL
comma
id|MS_MOVE
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* switch root and cwd back to / of rootfs */
id|sys_fchdir
c_func
(paren
id|root_fd
)paren
suffix:semicolon
id|sys_chroot
c_func
(paren
l_string|&quot;.&quot;
)paren
suffix:semicolon
id|sys_close
c_func
(paren
id|old_fd
)paren
suffix:semicolon
id|sys_close
c_func
(paren
id|root_fd
)paren
suffix:semicolon
id|umount_devfs
c_func
(paren
l_string|&quot;/old/dev&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_decode_dev
c_func
(paren
id|real_root_dev
)paren
op_eq
id|Root_RAM0
)paren
(brace
id|sys_chdir
c_func
(paren
l_string|&quot;/old&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ROOT_DEV
op_assign
id|new_decode_dev
c_func
(paren
id|real_root_dev
)paren
suffix:semicolon
id|mount_root
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Trying to move old root to /initrd ... &quot;
)paren
suffix:semicolon
id|error
op_assign
id|sys_mount
c_func
(paren
l_string|&quot;/old&quot;
comma
l_string|&quot;/root/initrd&quot;
comma
l_int|NULL
comma
id|MS_MOVE
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|printk
c_func
(paren
l_string|&quot;okay&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
r_int
id|fd
op_assign
id|sys_open
c_func
(paren
l_string|&quot;/dev/root.old&quot;
comma
id|O_RDWR
comma
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;failed&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Unmounting old root&bslash;n&quot;
)paren
suffix:semicolon
id|sys_umount
c_func
(paren
l_string|&quot;/old&quot;
comma
id|MNT_DETACH
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Trying to free ramdisk memory ... &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
id|error
op_assign
id|fd
suffix:semicolon
)brace
r_else
(brace
id|error
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|BLKFLSBUF
comma
l_int|0
)paren
suffix:semicolon
id|sys_close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
op_logical_neg
id|error
ques
c_cond
l_string|&quot;okay&bslash;n&quot;
suffix:colon
l_string|&quot;failed&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|initrd_load
r_int
id|__init
id|initrd_load
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|mount_initrd
)paren
(brace
id|create_dev
c_func
(paren
l_string|&quot;/dev/ram&quot;
comma
id|Root_RAM0
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Load the initrd data into /dev/ram0. Execute it as initrd&n;&t;&t; * unless /dev/ram0 is supposed to be our actual root device,&n;&t;&t; * in that case the ram disk is just set up here, and gets&n;&t;&t; * mounted in the normal path.&n;&t;&t; */
r_if
c_cond
(paren
id|rd_load_image
c_func
(paren
l_string|&quot;/initrd.image&quot;
)paren
op_logical_and
id|ROOT_DEV
op_ne
id|Root_RAM0
)paren
(brace
id|sys_unlink
c_func
(paren
l_string|&quot;/initrd.image&quot;
)paren
suffix:semicolon
id|handle_initrd
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
id|sys_unlink
c_func
(paren
l_string|&quot;/initrd.image&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
