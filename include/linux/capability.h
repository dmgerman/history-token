multiline_comment|/*&n; * This is &lt;linux/capability.h&gt;&n; *&n; * Andrew G. Morgan &lt;morgan@transmeta.com&gt;&n; * Alexander Kjeldaas &lt;astor@guardian.no&gt;&n; * with help from Aleph1, Roland Buresund and Andrew Main.&n; *&n; * See here for the libcap library (&quot;POSIX draft&quot; compliance):&n; *&n; * ftp://linux.kernel.org/pub/linux/libs/security/linux-privs/kernel-2.2/&n; */
macro_line|#ifndef _LINUX_CAPABILITY_H
DECL|macro|_LINUX_CAPABILITY_H
mdefine_line|#define _LINUX_CAPABILITY_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
multiline_comment|/* User-level do most of the mapping between kernel and user&n;   capabilities based on the version tag given by the kernel. The&n;   kernel might be somewhat backwards compatible, but don&squot;t bet on&n;   it. */
multiline_comment|/* XXX - Note, cap_t, is defined by POSIX to be an &quot;opaque&quot; pointer to&n;   a set of three capability sets.  The transposition of 3*the&n;   following structure to such a composite is better handled in a user&n;   library since the draft standard requires the use of malloc/free&n;   etc.. */
DECL|macro|_LINUX_CAPABILITY_VERSION
mdefine_line|#define _LINUX_CAPABILITY_VERSION  0x19980330
DECL|struct|__user_cap_header_struct
r_typedef
r_struct
id|__user_cap_header_struct
(brace
DECL|member|version
id|__u32
id|version
suffix:semicolon
DECL|member|pid
r_int
id|pid
suffix:semicolon
DECL|typedef|cap_user_header_t
)brace
op_star
id|cap_user_header_t
suffix:semicolon
DECL|struct|__user_cap_data_struct
r_typedef
r_struct
id|__user_cap_data_struct
(brace
DECL|member|effective
id|__u32
id|effective
suffix:semicolon
DECL|member|permitted
id|__u32
id|permitted
suffix:semicolon
DECL|member|inheritable
id|__u32
id|inheritable
suffix:semicolon
DECL|typedef|cap_user_data_t
)brace
op_star
id|cap_user_data_t
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/* #define STRICT_CAP_T_TYPECHECKS */
macro_line|#ifdef STRICT_CAP_T_TYPECHECKS
DECL|struct|kernel_cap_struct
r_typedef
r_struct
id|kernel_cap_struct
(brace
DECL|member|cap
id|__u32
id|cap
suffix:semicolon
DECL|typedef|kernel_cap_t
)brace
id|kernel_cap_t
suffix:semicolon
macro_line|#else
DECL|typedef|kernel_cap_t
r_typedef
id|__u32
id|kernel_cap_t
suffix:semicolon
macro_line|#endif
DECL|macro|_USER_CAP_HEADER_SIZE
mdefine_line|#define _USER_CAP_HEADER_SIZE  (2*sizeof(__u32))
DECL|macro|_KERNEL_CAP_T_SIZE
mdefine_line|#define _KERNEL_CAP_T_SIZE     (sizeof(kernel_cap_t))
macro_line|#endif
multiline_comment|/**&n; ** POSIX-draft defined capabilities. &n; **/
multiline_comment|/* In a system with the [_POSIX_CHOWN_RESTRICTED] option defined, this&n;   overrides the restriction of changing file ownership and group&n;   ownership. */
DECL|macro|CAP_CHOWN
mdefine_line|#define CAP_CHOWN            0
multiline_comment|/* Override all DAC access, including ACL execute access if&n;   [_POSIX_ACL] is defined. Excluding DAC access covered by&n;   CAP_LINUX_IMMUTABLE. */
DECL|macro|CAP_DAC_OVERRIDE
mdefine_line|#define CAP_DAC_OVERRIDE     1
multiline_comment|/* Overrides all DAC restrictions regarding read and search on files&n;   and directories, including ACL restrictions if [_POSIX_ACL] is&n;   defined. Excluding DAC access covered by CAP_LINUX_IMMUTABLE. */
DECL|macro|CAP_DAC_READ_SEARCH
mdefine_line|#define CAP_DAC_READ_SEARCH  2
multiline_comment|/* Overrides all restrictions about allowed operations on files, where&n;   file owner ID must be equal to the user ID, except where CAP_FSETID&n;   is applicable. It doesn&squot;t override MAC and DAC restrictions. */
DECL|macro|CAP_FOWNER
mdefine_line|#define CAP_FOWNER           3
multiline_comment|/* Overrides the following restrictions that the effective user ID&n;   shall match the file owner ID when setting the S_ISUID and S_ISGID&n;   bits on that file; that the effective group ID (or one of the&n;   supplementary group IDs) shall match the file owner ID when setting&n;   the S_ISGID bit on that file; that the S_ISUID and S_ISGID bits are&n;   cleared on successful return from chown(2) (not implemented). */
DECL|macro|CAP_FSETID
mdefine_line|#define CAP_FSETID           4
multiline_comment|/* Used to decide between falling back on the old suser() or fsuser(). */
DECL|macro|CAP_FS_MASK
mdefine_line|#define CAP_FS_MASK          0x1f
multiline_comment|/* Overrides the restriction that the real or effective user ID of a&n;   process sending a signal must match the real or effective user ID&n;   of the process receiving the signal. */
DECL|macro|CAP_KILL
mdefine_line|#define CAP_KILL             5
multiline_comment|/* Allows setgid(2) manipulation */
multiline_comment|/* Allows setgroups(2) */
multiline_comment|/* Allows forged gids on socket credentials passing. */
DECL|macro|CAP_SETGID
mdefine_line|#define CAP_SETGID           6
multiline_comment|/* Allows set*uid(2) manipulation (including fsuid). */
multiline_comment|/* Allows forged pids on socket credentials passing. */
DECL|macro|CAP_SETUID
mdefine_line|#define CAP_SETUID           7
multiline_comment|/**&n; ** Linux-specific capabilities&n; **/
multiline_comment|/* Transfer any capability in your permitted set to any pid,&n;   remove any capability in your permitted set from any pid */
DECL|macro|CAP_SETPCAP
mdefine_line|#define CAP_SETPCAP          8
multiline_comment|/* Allow modification of S_IMMUTABLE and S_APPEND file attributes */
DECL|macro|CAP_LINUX_IMMUTABLE
mdefine_line|#define CAP_LINUX_IMMUTABLE  9
multiline_comment|/* Allows binding to TCP/UDP sockets below 1024 */
multiline_comment|/* Allows binding to ATM VCIs below 32 */
DECL|macro|CAP_NET_BIND_SERVICE
mdefine_line|#define CAP_NET_BIND_SERVICE 10
multiline_comment|/* Allow broadcasting, listen to multicast */
DECL|macro|CAP_NET_BROADCAST
mdefine_line|#define CAP_NET_BROADCAST    11
multiline_comment|/* Allow interface configuration */
multiline_comment|/* Allow administration of IP firewall, masquerading and accounting */
multiline_comment|/* Allow setting debug option on sockets */
multiline_comment|/* Allow modification of routing tables */
multiline_comment|/* Allow setting arbitrary process / process group ownership on&n;   sockets */
multiline_comment|/* Allow binding to any address for transparent proxying */
multiline_comment|/* Allow setting TOS (type of service) */
multiline_comment|/* Allow setting promiscuous mode */
multiline_comment|/* Allow clearing driver statistics */
multiline_comment|/* Allow multicasting */
multiline_comment|/* Allow read/write of device-specific registers */
multiline_comment|/* Allow activation of ATM control sockets */
DECL|macro|CAP_NET_ADMIN
mdefine_line|#define CAP_NET_ADMIN        12
multiline_comment|/* Allow use of RAW sockets */
multiline_comment|/* Allow use of PACKET sockets */
DECL|macro|CAP_NET_RAW
mdefine_line|#define CAP_NET_RAW          13
multiline_comment|/* Allow locking of shared memory segments */
multiline_comment|/* Allow mlock and mlockall (which doesn&squot;t really have anything to do&n;   with IPC) */
DECL|macro|CAP_IPC_LOCK
mdefine_line|#define CAP_IPC_LOCK         14
multiline_comment|/* Override IPC ownership checks */
DECL|macro|CAP_IPC_OWNER
mdefine_line|#define CAP_IPC_OWNER        15
multiline_comment|/* Insert and remove kernel modules - modify kernel without limit */
multiline_comment|/* Modify cap_bset */
DECL|macro|CAP_SYS_MODULE
mdefine_line|#define CAP_SYS_MODULE       16
multiline_comment|/* Allow ioperm/iopl access */
multiline_comment|/* Allow sending USB messages to any device via /proc/bus/usb */
DECL|macro|CAP_SYS_RAWIO
mdefine_line|#define CAP_SYS_RAWIO        17
multiline_comment|/* Allow use of chroot() */
DECL|macro|CAP_SYS_CHROOT
mdefine_line|#define CAP_SYS_CHROOT       18
multiline_comment|/* Allow ptrace() of any process */
DECL|macro|CAP_SYS_PTRACE
mdefine_line|#define CAP_SYS_PTRACE       19
multiline_comment|/* Allow configuration of process accounting */
DECL|macro|CAP_SYS_PACCT
mdefine_line|#define CAP_SYS_PACCT        20
multiline_comment|/* Allow configuration of the secure attention key */
multiline_comment|/* Allow administration of the random device */
multiline_comment|/* Allow examination and configuration of disk quotas */
multiline_comment|/* Allow configuring the kernel&squot;s syslog (printk behaviour) */
multiline_comment|/* Allow setting the domainname */
multiline_comment|/* Allow setting the hostname */
multiline_comment|/* Allow calling bdflush() */
multiline_comment|/* Allow mount() and umount(), setting up new smb connection */
multiline_comment|/* Allow some autofs root ioctls */
multiline_comment|/* Allow nfsservctl */
multiline_comment|/* Allow VM86_REQUEST_IRQ */
multiline_comment|/* Allow to read/write pci config on alpha */
multiline_comment|/* Allow irix_prctl on mips (setstacksize) */
multiline_comment|/* Allow flushing all cache on m68k (sys_cacheflush) */
multiline_comment|/* Allow removing semaphores */
multiline_comment|/* Used instead of CAP_CHOWN to &quot;chown&quot; IPC message queues, semaphores&n;   and shared memory */
multiline_comment|/* Allow locking/unlocking of shared memory segment */
multiline_comment|/* Allow turning swap on/off */
multiline_comment|/* Allow forged pids on socket credentials passing */
multiline_comment|/* Allow setting readahead and flushing buffers on block devices */
multiline_comment|/* Allow setting geometry in floppy driver */
multiline_comment|/* Allow turning DMA on/off in xd driver */
multiline_comment|/* Allow administration of md devices (mostly the above, but some&n;   extra ioctls) */
multiline_comment|/* Allow tuning the ide driver */
multiline_comment|/* Allow access to the nvram device */
multiline_comment|/* Allow administration of apm_bios, serial and bttv (TV) device */
multiline_comment|/* Allow manufacturer commands in isdn CAPI support driver */
multiline_comment|/* Allow reading non-standardized portions of pci configuration space */
multiline_comment|/* Allow DDI debug ioctl on sbpcd driver */
multiline_comment|/* Allow setting up serial ports */
multiline_comment|/* Allow sending raw qic-117 commands */
multiline_comment|/* Allow enabling/disabling tagged queuing on SCSI controllers and sending&n;   arbitrary SCSI commands */
multiline_comment|/* Allow setting encryption key on loopback filesystem */
DECL|macro|CAP_SYS_ADMIN
mdefine_line|#define CAP_SYS_ADMIN        21
multiline_comment|/* Allow use of reboot() */
DECL|macro|CAP_SYS_BOOT
mdefine_line|#define CAP_SYS_BOOT         22
multiline_comment|/* Allow raising priority and setting priority on other (different&n;   UID) processes */
multiline_comment|/* Allow use of FIFO and round-robin (realtime) scheduling on own&n;   processes and setting the scheduling algorithm used by another&n;   process. */
DECL|macro|CAP_SYS_NICE
mdefine_line|#define CAP_SYS_NICE         23
multiline_comment|/* Override resource limits. Set resource limits. */
multiline_comment|/* Override quota limits. */
multiline_comment|/* Override reserved space on ext2 filesystem */
multiline_comment|/* Modify data journaling mode on ext3 filesystem (uses journaling&n;   resources) */
multiline_comment|/* NOTE: ext2 honors fsuid when checking for resource overrides, so &n;   you can override using fsuid too */
multiline_comment|/* Override size restrictions on IPC message queues */
multiline_comment|/* Allow more than 64hz interrupts from the real-time clock */
multiline_comment|/* Override max number of consoles on console allocation */
multiline_comment|/* Override max number of keymaps */
DECL|macro|CAP_SYS_RESOURCE
mdefine_line|#define CAP_SYS_RESOURCE     24
multiline_comment|/* Allow manipulation of system clock */
multiline_comment|/* Allow irix_stime on mips */
multiline_comment|/* Allow setting the real-time clock */
DECL|macro|CAP_SYS_TIME
mdefine_line|#define CAP_SYS_TIME         25
multiline_comment|/* Allow configuration of tty devices */
multiline_comment|/* Allow vhangup() of tty */
DECL|macro|CAP_SYS_TTY_CONFIG
mdefine_line|#define CAP_SYS_TTY_CONFIG   26
multiline_comment|/* Allow the privileged aspects of mknod() */
DECL|macro|CAP_MKNOD
mdefine_line|#define CAP_MKNOD            27
multiline_comment|/* Allow taking of leases on files */
DECL|macro|CAP_LEASE
mdefine_line|#define CAP_LEASE            28
macro_line|#ifdef __KERNEL__
multiline_comment|/* &n; * Bounding set&n; */
r_extern
id|kernel_cap_t
id|cap_bset
suffix:semicolon
multiline_comment|/*&n; * Internal kernel functions only&n; */
macro_line|#ifdef STRICT_CAP_T_TYPECHECKS
DECL|macro|to_cap_t
mdefine_line|#define to_cap_t(x) { x }
DECL|macro|cap_t
mdefine_line|#define cap_t(x) (x).cap
macro_line|#else
DECL|macro|to_cap_t
mdefine_line|#define to_cap_t(x) (x)
DECL|macro|cap_t
mdefine_line|#define cap_t(x) (x)
macro_line|#endif
DECL|macro|CAP_EMPTY_SET
mdefine_line|#define CAP_EMPTY_SET       to_cap_t(0)
DECL|macro|CAP_FULL_SET
mdefine_line|#define CAP_FULL_SET        to_cap_t(~0)
DECL|macro|CAP_INIT_EFF_SET
mdefine_line|#define CAP_INIT_EFF_SET    to_cap_t(~0 &amp; ~CAP_TO_MASK(CAP_SETPCAP))
DECL|macro|CAP_INIT_INH_SET
mdefine_line|#define CAP_INIT_INH_SET    to_cap_t(0)
DECL|macro|CAP_TO_MASK
mdefine_line|#define CAP_TO_MASK(x) (1 &lt;&lt; (x))
DECL|macro|cap_raise
mdefine_line|#define cap_raise(c, flag)   (cap_t(c) |=  CAP_TO_MASK(flag))
DECL|macro|cap_lower
mdefine_line|#define cap_lower(c, flag)   (cap_t(c) &amp;= ~CAP_TO_MASK(flag))
DECL|macro|cap_raised
mdefine_line|#define cap_raised(c, flag)  (cap_t(c) &amp; CAP_TO_MASK(flag))
DECL|function|cap_combine
r_static
r_inline
id|kernel_cap_t
id|cap_combine
c_func
(paren
id|kernel_cap_t
id|a
comma
id|kernel_cap_t
id|b
)paren
(brace
id|kernel_cap_t
id|dest
suffix:semicolon
id|cap_t
c_func
(paren
id|dest
)paren
op_assign
id|cap_t
c_func
(paren
id|a
)paren
op_or
id|cap_t
c_func
(paren
id|b
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
DECL|function|cap_intersect
r_static
r_inline
id|kernel_cap_t
id|cap_intersect
c_func
(paren
id|kernel_cap_t
id|a
comma
id|kernel_cap_t
id|b
)paren
(brace
id|kernel_cap_t
id|dest
suffix:semicolon
id|cap_t
c_func
(paren
id|dest
)paren
op_assign
id|cap_t
c_func
(paren
id|a
)paren
op_amp
id|cap_t
c_func
(paren
id|b
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
DECL|function|cap_drop
r_static
r_inline
id|kernel_cap_t
id|cap_drop
c_func
(paren
id|kernel_cap_t
id|a
comma
id|kernel_cap_t
id|drop
)paren
(brace
id|kernel_cap_t
id|dest
suffix:semicolon
id|cap_t
c_func
(paren
id|dest
)paren
op_assign
id|cap_t
c_func
(paren
id|a
)paren
op_amp
op_complement
id|cap_t
c_func
(paren
id|drop
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
DECL|function|cap_invert
r_static
r_inline
id|kernel_cap_t
id|cap_invert
c_func
(paren
id|kernel_cap_t
id|c
)paren
(brace
id|kernel_cap_t
id|dest
suffix:semicolon
id|cap_t
c_func
(paren
id|dest
)paren
op_assign
op_complement
id|cap_t
c_func
(paren
id|c
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
DECL|macro|cap_isclear
mdefine_line|#define cap_isclear(c)       (!cap_t(c))
DECL|macro|cap_issubset
mdefine_line|#define cap_issubset(a,set)  (!(cap_t(a) &amp; ~cap_t(set)))
DECL|macro|cap_clear
mdefine_line|#define cap_clear(c)         do { cap_t(c) =  0; } while(0)
DECL|macro|cap_set_full
mdefine_line|#define cap_set_full(c)      do { cap_t(c) = ~0; } while(0)
DECL|macro|cap_mask
mdefine_line|#define cap_mask(c,mask)     do { cap_t(c) &amp;= cap_t(mask); } while(0)
DECL|macro|cap_is_fs_cap
mdefine_line|#define cap_is_fs_cap(c)     (CAP_TO_MASK(c) &amp; CAP_FS_MASK)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* !_LINUX_CAPABILITY_H */
eof
