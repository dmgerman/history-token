multiline_comment|/*&n; *  $Id: nfsroot.c,v 1.45 1998/03/07 10:44:46 mj Exp $&n; *&n; *  Copyright (C) 1995, 1996  Gero Kuhlmann &lt;gero@gkminix.han.de&gt;&n; *&n; *  Allow an NFS filesystem to be mounted as root. The way this works is:&n; *     (1) Use the IP autoconfig mechanism to set local IP addresses and routes.&n; *     (2) Handle RPC negotiation with the system which replied to RARP or&n; *         was reported as a boot server by BOOTP or manually.&n; *     (3) The actual mounting is done later, when init() is running.&n; *&n; *&n; *&t;Changes:&n; *&n; *&t;Alan Cox&t;:&t;Removed get_address name clash with FPU.&n; *&t;Alan Cox&t;:&t;Reformatted a bit.&n; *&t;Gero Kuhlmann&t;:&t;Code cleanup&n; *&t;Michael Rausch  :&t;Fixed recognition of an incoming RARP answer.&n; *&t;Martin Mares&t;: (2.0)&t;Auto-configuration via BOOTP supported.&n; *&t;Martin Mares&t;:&t;Manual selection of interface &amp; BOOTP/RARP.&n; *&t;Martin Mares&t;:&t;Using network routes instead of host routes,&n; *&t;&t;&t;&t;allowing the default configuration to be used&n; *&t;&t;&t;&t;for normal operation of the host.&n; *&t;Martin Mares&t;:&t;Randomized timer with exponential backoff&n; *&t;&t;&t;&t;installed to minimize network congestion.&n; *&t;Martin Mares&t;:&t;Code cleanup.&n; *&t;Martin Mares&t;: (2.1)&t;BOOTP and RARP made configuration options.&n; *&t;Martin Mares&t;:&t;Server hostname generation fixed.&n; *&t;Gerd Knorr&t;:&t;Fixed wired inode handling&n; *&t;Martin Mares&t;: (2.2)&t;&quot;0.0.0.0&quot; addresses from command line ignored.&n; *&t;Martin Mares&t;:&t;RARP replies not tested for server address.&n; *&t;Gero Kuhlmann&t;: (2.3) Some bug fixes and code cleanup again (please&n; *&t;&t;&t;&t;send me your new patches _before_ bothering&n; *&t;&t;&t;&t;Linus so that I don&squot; always have to cleanup&n; *&t;&t;&t;&t;_afterwards_ - thanks)&n; *&t;Gero Kuhlmann&t;:&t;Last changes of Martin Mares undone.&n; *&t;Gero Kuhlmann&t;: &t;RARP replies are tested for specified server&n; *&t;&t;&t;&t;again. However, it&squot;s now possible to have&n; *&t;&t;&t;&t;different RARP and NFS servers.&n; *&t;Gero Kuhlmann&t;:&t;&quot;0.0.0.0&quot; addresses from command line are&n; *&t;&t;&t;&t;now mapped to INADDR_NONE.&n; *&t;Gero Kuhlmann&t;:&t;Fixed a bug which prevented BOOTP path name&n; *&t;&t;&t;&t;from being used (thanks to Leo Spiekman)&n; *&t;Andy Walker&t;:&t;Allow to specify the NFS server in nfs_root&n; *&t;&t;&t;&t;without giving a path name&n; *&t;Swen Th&#xfffd;mmler&t;:&t;Allow to specify the NFS options in nfs_root&n; *&t;&t;&t;&t;without giving a path name. Fix BOOTP request&n; *&t;&t;&t;&t;for domainname (domainname is NIS domain, not&n; *&t;&t;&t;&t;DNS domain!). Skip dummy devices for BOOTP.&n; *&t;Jacek Zapala&t;:&t;Fixed a bug which prevented server-ip address&n; *&t;&t;&t;&t;from nfsroot parameter from being used.&n; *&t;Olaf Kirch&t;:&t;Adapted to new NFS code.&n; *&t;Jakub Jelinek&t;:&t;Free used code segment.&n; *&t;Marko Kohtala&t;:&t;Fixed some bugs.&n; *&t;Martin Mares&t;:&t;Debug message cleanup&n; *&t;Martin Mares&t;:&t;Changed to use the new generic IP layer autoconfig&n; *&t;&t;&t;&t;code. BOOTP and RARP moved there.&n; *&t;Martin Mares&t;:&t;Default path now contains host name instead of&n; *&t;&t;&t;&t;host IP address (but host name defaults to IP&n; *&t;&t;&t;&t;address anyway).&n; *&t;Martin Mares&t;:&t;Use root_server_addr appropriately during setup.&n; *&t;Martin Mares&t;:&t;Rewrote parameter parsing, now hopefully giving&n; *&t;&t;&t;&t;correct overriding.&n; *&t;Trond Myklebust :&t;Add in preliminary support for NFSv3 and TCP.&n; *&t;&t;&t;&t;Fix bug in root_nfs_addr(). nfs_data.namlen&n; *&t;&t;&t;&t;is NOT for the length of the hostname.&n; *&t;Hua Qin&t;&t;:&t;Support for mounting root file system via&n; *&t;&t;&t;&t;NFS over TCP.&n; *&t;Fabian Frederick:&t;Option parser rebuilt (using parser lib)&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/nfs.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;linux/nfs_mount.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;net/ipconfig.h&gt;
macro_line|#include &lt;linux/parser.h&gt;
multiline_comment|/* Define this to allow debugging output */
DECL|macro|NFSROOT_DEBUG
macro_line|#undef NFSROOT_DEBUG
DECL|macro|NFSDBG_FACILITY
mdefine_line|#define NFSDBG_FACILITY NFSDBG_ROOT
multiline_comment|/* Default path we try to mount. &quot;%s&quot; gets replaced by our IP address */
DECL|macro|NFS_ROOT
mdefine_line|#define NFS_ROOT&t;&t;&quot;/tftpboot/%s&quot;
multiline_comment|/* Parameters passed from the kernel command line */
DECL|variable|__initdata
r_static
r_char
id|nfs_root_name
(braket
l_int|256
)braket
id|__initdata
op_assign
l_string|&quot;&quot;
suffix:semicolon
multiline_comment|/* Address of NFS server */
DECL|variable|__initdata
r_static
id|__u32
id|servaddr
id|__initdata
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Name of directory to mount */
DECL|variable|__initdata
r_static
r_char
id|nfs_path
(braket
id|NFS_MAXPATHLEN
)braket
id|__initdata
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/* NFS-related data */
DECL|variable|__initdata
r_static
r_struct
id|nfs_mount_data
id|nfs_data
id|__initdata
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/* NFS mount info */
DECL|variable|__initdata
r_static
r_int
id|nfs_port
id|__initdata
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Port to connect to for NFS */
DECL|variable|__initdata
r_static
r_int
id|mount_port
id|__initdata
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Mount daemon port number */
multiline_comment|/***************************************************************************&n;&n;&t;&t;&t;     Parsing of options&n;&n; ***************************************************************************/
r_enum
(brace
multiline_comment|/* Options that take integer arguments */
DECL|enumerator|Opt_port
DECL|enumerator|Opt_rsize
DECL|enumerator|Opt_wsize
DECL|enumerator|Opt_timeo
DECL|enumerator|Opt_retrans
DECL|enumerator|Opt_acregmin
id|Opt_port
comma
id|Opt_rsize
comma
id|Opt_wsize
comma
id|Opt_timeo
comma
id|Opt_retrans
comma
id|Opt_acregmin
comma
DECL|enumerator|Opt_acregmax
DECL|enumerator|Opt_acdirmin
DECL|enumerator|Opt_acdirmax
id|Opt_acregmax
comma
id|Opt_acdirmin
comma
id|Opt_acdirmax
comma
multiline_comment|/* Options that take no arguments */
DECL|enumerator|Opt_soft
DECL|enumerator|Opt_hard
DECL|enumerator|Opt_intr
id|Opt_soft
comma
id|Opt_hard
comma
id|Opt_intr
comma
DECL|enumerator|Opt_nointr
DECL|enumerator|Opt_posix
DECL|enumerator|Opt_noposix
DECL|enumerator|Opt_cto
DECL|enumerator|Opt_nocto
DECL|enumerator|Opt_ac
id|Opt_nointr
comma
id|Opt_posix
comma
id|Opt_noposix
comma
id|Opt_cto
comma
id|Opt_nocto
comma
id|Opt_ac
comma
DECL|enumerator|Opt_noac
DECL|enumerator|Opt_lock
DECL|enumerator|Opt_nolock
DECL|enumerator|Opt_v2
DECL|enumerator|Opt_v3
DECL|enumerator|Opt_udp
DECL|enumerator|Opt_tcp
id|Opt_noac
comma
id|Opt_lock
comma
id|Opt_nolock
comma
id|Opt_v2
comma
id|Opt_v3
comma
id|Opt_udp
comma
id|Opt_tcp
comma
DECL|enumerator|Opt_broken_suid
id|Opt_broken_suid
comma
multiline_comment|/* Error token */
DECL|enumerator|Opt_err
id|Opt_err
)brace
suffix:semicolon
DECL|variable|tokens
r_static
id|match_table_t
id|__initdata
id|tokens
op_assign
(brace
(brace
id|Opt_port
comma
l_string|&quot;port=%u&quot;
)brace
comma
(brace
id|Opt_rsize
comma
l_string|&quot;rsize=%u&quot;
)brace
comma
(brace
id|Opt_wsize
comma
l_string|&quot;wsize=%u&quot;
)brace
comma
(brace
id|Opt_timeo
comma
l_string|&quot;timeo=%u&quot;
)brace
comma
(brace
id|Opt_retrans
comma
l_string|&quot;retrans=%u&quot;
)brace
comma
(brace
id|Opt_acregmin
comma
l_string|&quot;acregmin=%u&quot;
)brace
comma
(brace
id|Opt_acregmax
comma
l_string|&quot;acregmax=%u&quot;
)brace
comma
(brace
id|Opt_acdirmin
comma
l_string|&quot;acdirmin=%u&quot;
)brace
comma
(brace
id|Opt_acdirmax
comma
l_string|&quot;acdirmax=%u&quot;
)brace
comma
(brace
id|Opt_soft
comma
l_string|&quot;soft&quot;
)brace
comma
(brace
id|Opt_hard
comma
l_string|&quot;hard&quot;
)brace
comma
(brace
id|Opt_intr
comma
l_string|&quot;intr&quot;
)brace
comma
(brace
id|Opt_nointr
comma
l_string|&quot;nointr&quot;
)brace
comma
(brace
id|Opt_posix
comma
l_string|&quot;posix&quot;
)brace
comma
(brace
id|Opt_noposix
comma
l_string|&quot;noposix&quot;
)brace
comma
(brace
id|Opt_cto
comma
l_string|&quot;cto&quot;
)brace
comma
(brace
id|Opt_nocto
comma
l_string|&quot;nocto&quot;
)brace
comma
(brace
id|Opt_ac
comma
l_string|&quot;ac&quot;
)brace
comma
(brace
id|Opt_noac
comma
l_string|&quot;noac&quot;
)brace
comma
(brace
id|Opt_lock
comma
l_string|&quot;lock&quot;
)brace
comma
(brace
id|Opt_nolock
comma
l_string|&quot;nolock&quot;
)brace
comma
(brace
id|Opt_v2
comma
l_string|&quot;nfsvers=2&quot;
)brace
comma
(brace
id|Opt_v2
comma
l_string|&quot;v2&quot;
)brace
comma
(brace
id|Opt_v3
comma
l_string|&quot;nfsvers=3&quot;
)brace
comma
(brace
id|Opt_v3
comma
l_string|&quot;v3&quot;
)brace
comma
(brace
id|Opt_udp
comma
l_string|&quot;proto=udp&quot;
)brace
comma
(brace
id|Opt_udp
comma
l_string|&quot;udp&quot;
)brace
comma
(brace
id|Opt_tcp
comma
l_string|&quot;proto=tcp&quot;
)brace
comma
(brace
id|Opt_tcp
comma
l_string|&quot;tcp&quot;
)brace
comma
(brace
id|Opt_broken_suid
comma
l_string|&quot;broken_suid&quot;
)brace
comma
(brace
id|Opt_err
comma
l_int|NULL
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; *  Parse option string.&n; */
DECL|function|root_nfs_parse
r_static
r_int
id|__init
id|root_nfs_parse
c_func
(paren
r_char
op_star
id|name
comma
r_char
op_star
id|buf
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
id|substring_t
id|args
(braket
id|MAX_OPT_ARGS
)braket
suffix:semicolon
r_int
id|option
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Set the NFS remote path */
id|p
op_assign
id|strsep
c_func
(paren
op_amp
id|name
comma
l_string|&quot;,&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
(braket
l_int|0
)braket
op_ne
l_char|&squot;&bslash;0&squot;
op_logical_and
id|strcmp
c_func
(paren
id|p
comma
l_string|&quot;default&quot;
)paren
op_ne
l_int|0
)paren
id|strlcpy
c_func
(paren
id|buf
comma
id|p
comma
id|NFS_MAXPATHLEN
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|p
op_assign
id|strsep
(paren
op_amp
id|name
comma
l_string|&quot;,&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
id|token
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|p
)paren
r_continue
suffix:semicolon
id|token
op_assign
id|match_token
c_func
(paren
id|p
comma
id|tokens
comma
id|args
)paren
suffix:semicolon
multiline_comment|/* %u tokens only. Beware if you add new tokens! */
r_if
c_cond
(paren
id|token
OL
id|Opt_soft
op_logical_and
id|match_int
c_func
(paren
op_amp
id|args
(braket
l_int|0
)braket
comma
op_amp
id|option
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|token
)paren
(brace
r_case
id|Opt_port
suffix:colon
id|nfs_port
op_assign
id|option
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_rsize
suffix:colon
id|nfs_data.rsize
op_assign
id|option
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_wsize
suffix:colon
id|nfs_data.wsize
op_assign
id|option
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_timeo
suffix:colon
id|nfs_data.timeo
op_assign
id|option
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_retrans
suffix:colon
id|nfs_data.retrans
op_assign
id|option
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_acregmin
suffix:colon
id|nfs_data.acregmin
op_assign
id|option
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_acregmax
suffix:colon
id|nfs_data.acregmax
op_assign
id|option
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_acdirmin
suffix:colon
id|nfs_data.acdirmin
op_assign
id|option
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_acdirmax
suffix:colon
id|nfs_data.acdirmax
op_assign
id|option
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_soft
suffix:colon
id|nfs_data.flags
op_or_assign
id|NFS_MOUNT_SOFT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_hard
suffix:colon
id|nfs_data.flags
op_and_assign
op_complement
id|NFS_MOUNT_SOFT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_intr
suffix:colon
id|nfs_data.flags
op_or_assign
id|NFS_MOUNT_INTR
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_nointr
suffix:colon
id|nfs_data.flags
op_and_assign
op_complement
id|NFS_MOUNT_INTR
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_posix
suffix:colon
id|nfs_data.flags
op_or_assign
id|NFS_MOUNT_POSIX
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_noposix
suffix:colon
id|nfs_data.flags
op_and_assign
op_complement
id|NFS_MOUNT_POSIX
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_cto
suffix:colon
id|nfs_data.flags
op_and_assign
op_complement
id|NFS_MOUNT_NOCTO
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_nocto
suffix:colon
id|nfs_data.flags
op_or_assign
id|NFS_MOUNT_NOCTO
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_ac
suffix:colon
id|nfs_data.flags
op_and_assign
op_complement
id|NFS_MOUNT_NOAC
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_noac
suffix:colon
id|nfs_data.flags
op_or_assign
id|NFS_MOUNT_NOAC
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_lock
suffix:colon
id|nfs_data.flags
op_and_assign
op_complement
id|NFS_MOUNT_NONLM
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_nolock
suffix:colon
id|nfs_data.flags
op_or_assign
id|NFS_MOUNT_NONLM
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_v2
suffix:colon
id|nfs_data.flags
op_and_assign
op_complement
id|NFS_MOUNT_VER3
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_v3
suffix:colon
id|nfs_data.flags
op_or_assign
id|NFS_MOUNT_VER3
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_udp
suffix:colon
id|nfs_data.flags
op_and_assign
op_complement
id|NFS_MOUNT_TCP
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_tcp
suffix:colon
id|nfs_data.flags
op_or_assign
id|NFS_MOUNT_TCP
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_broken_suid
suffix:colon
id|nfs_data.flags
op_or_assign
id|NFS_MOUNT_BROKEN_SUID
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; *  Prepare the NFS data structure and parse all options.&n; */
DECL|function|root_nfs_name
r_static
r_int
id|__init
id|root_nfs_name
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_static
r_char
id|buf
(braket
id|NFS_MAXPATHLEN
)braket
id|__initdata
suffix:semicolon
r_char
op_star
id|cp
suffix:semicolon
multiline_comment|/* Set some default values */
id|memset
c_func
(paren
op_amp
id|nfs_data
comma
l_int|0
comma
r_sizeof
(paren
id|nfs_data
)paren
)paren
suffix:semicolon
id|nfs_port
op_assign
op_minus
l_int|1
suffix:semicolon
id|nfs_data.version
op_assign
id|NFS_MOUNT_VERSION
suffix:semicolon
id|nfs_data.flags
op_assign
id|NFS_MOUNT_NONLM
suffix:semicolon
multiline_comment|/* No lockd in nfs root yet */
id|nfs_data.rsize
op_assign
id|NFS_DEF_FILE_IO_BUFFER_SIZE
suffix:semicolon
id|nfs_data.wsize
op_assign
id|NFS_DEF_FILE_IO_BUFFER_SIZE
suffix:semicolon
id|nfs_data.acregmin
op_assign
l_int|3
suffix:semicolon
id|nfs_data.acregmax
op_assign
l_int|60
suffix:semicolon
id|nfs_data.acdirmin
op_assign
l_int|30
suffix:semicolon
id|nfs_data.acdirmax
op_assign
l_int|60
suffix:semicolon
id|strcpy
c_func
(paren
id|buf
comma
id|NFS_ROOT
)paren
suffix:semicolon
multiline_comment|/* Process options received from the remote server */
id|root_nfs_parse
c_func
(paren
id|root_server_path
comma
id|buf
)paren
suffix:semicolon
multiline_comment|/* Override them by options set on kernel command-line */
id|root_nfs_parse
c_func
(paren
id|name
comma
id|buf
)paren
suffix:semicolon
id|cp
op_assign
id|system_utsname.nodename
suffix:semicolon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|buf
)paren
op_plus
id|strlen
c_func
(paren
id|cp
)paren
OG
id|NFS_MAXPATHLEN
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Root-NFS: Pathname for remote directory too long.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|nfs_path
comma
id|buf
comma
id|cp
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; *  Get NFS server address.&n; */
DECL|function|root_nfs_addr
r_static
r_int
id|__init
id|root_nfs_addr
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
(paren
id|servaddr
op_assign
id|root_server_addr
)paren
op_eq
id|INADDR_NONE
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Root-NFS: No NFS server available, giving up.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|snprintf
c_func
(paren
id|nfs_data.hostname
comma
r_sizeof
(paren
id|nfs_data.hostname
)paren
comma
l_string|&quot;%u.%u.%u.%u&quot;
comma
id|NIPQUAD
c_func
(paren
id|servaddr
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Tell the user what&squot;s going on.&n; */
macro_line|#ifdef NFSROOT_DEBUG
DECL|function|root_nfs_print
r_static
r_void
id|__init
id|root_nfs_print
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Root-NFS: Mounting %s on server %s as root&bslash;n&quot;
comma
id|nfs_path
comma
id|nfs_data.hostname
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Root-NFS:     rsize = %d, wsize = %d, timeo = %d, retrans = %d&bslash;n&quot;
comma
id|nfs_data.rsize
comma
id|nfs_data.wsize
comma
id|nfs_data.timeo
comma
id|nfs_data.retrans
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Root-NFS:     acreg (min,max) = (%d,%d), acdir (min,max) = (%d,%d)&bslash;n&quot;
comma
id|nfs_data.acregmin
comma
id|nfs_data.acregmax
comma
id|nfs_data.acdirmin
comma
id|nfs_data.acdirmax
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Root-NFS:     nfsd port = %d, mountd port = %d, flags = %08x&bslash;n&quot;
comma
id|nfs_port
comma
id|mount_port
comma
id|nfs_data.flags
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|root_nfs_init
r_int
id|__init
id|root_nfs_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef NFSROOT_DEBUG
id|nfs_debug
op_or_assign
id|NFSDBG_ROOT
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Decode the root directory path name and NFS options from&n;&t; * the kernel command line. This has to go here in order to&n;&t; * be able to use the client IP address for the remote root&n;&t; * directory (necessary for pure RARP booting).&n;&t; */
r_if
c_cond
(paren
id|root_nfs_name
c_func
(paren
id|nfs_root_name
)paren
OL
l_int|0
op_logical_or
id|root_nfs_addr
c_func
(paren
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
macro_line|#ifdef NFSROOT_DEBUG
id|root_nfs_print
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Parse NFS server and directory information passed on the kernel&n; *  command line.&n; */
DECL|function|nfs_root_setup
r_int
id|__init
id|nfs_root_setup
c_func
(paren
r_char
op_star
id|line
)paren
(brace
id|ROOT_DEV
op_assign
id|Root_NFS
suffix:semicolon
r_if
c_cond
(paren
id|line
(braket
l_int|0
)braket
op_eq
l_char|&squot;/&squot;
op_logical_or
id|line
(braket
l_int|0
)braket
op_eq
l_char|&squot;,&squot;
op_logical_or
(paren
id|line
(braket
l_int|0
)braket
op_ge
l_char|&squot;0&squot;
op_logical_and
id|line
(braket
l_int|0
)braket
op_le
l_char|&squot;9&squot;
)paren
)paren
(brace
id|strlcpy
c_func
(paren
id|nfs_root_name
comma
id|line
comma
r_sizeof
(paren
id|nfs_root_name
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|n
op_assign
id|strlen
c_func
(paren
id|line
)paren
op_plus
r_sizeof
(paren
id|NFS_ROOT
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ge
r_sizeof
(paren
id|nfs_root_name
)paren
)paren
id|line
(braket
r_sizeof
(paren
id|nfs_root_name
)paren
op_minus
r_sizeof
(paren
id|NFS_ROOT
)paren
op_minus
l_int|2
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|sprintf
c_func
(paren
id|nfs_root_name
comma
id|NFS_ROOT
comma
id|line
)paren
suffix:semicolon
)brace
id|root_server_addr
op_assign
id|root_nfs_parse_addr
c_func
(paren
id|nfs_root_name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;nfsroot=&quot;
comma
id|nfs_root_setup
)paren
suffix:semicolon
multiline_comment|/***************************************************************************&n;&n;&t;       Routines to actually mount the root directory&n;&n; ***************************************************************************/
multiline_comment|/*&n; *  Construct sockaddr_in from address and port number.&n; */
r_static
r_inline
r_void
DECL|function|set_sockaddr
id|set_sockaddr
c_func
(paren
r_struct
id|sockaddr_in
op_star
id|sin
comma
id|__u32
id|addr
comma
id|__u16
id|port
)paren
(brace
id|sin-&gt;sin_family
op_assign
id|AF_INET
suffix:semicolon
id|sin-&gt;sin_addr.s_addr
op_assign
id|addr
suffix:semicolon
id|sin-&gt;sin_port
op_assign
id|port
suffix:semicolon
)brace
multiline_comment|/*&n; *  Query server portmapper for the port of a daemon program.&n; */
DECL|function|root_nfs_getport
r_static
r_int
id|__init
id|root_nfs_getport
c_func
(paren
r_int
id|program
comma
r_int
id|version
comma
r_int
id|proto
)paren
(brace
r_struct
id|sockaddr_in
id|sin
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Looking up port of RPC %d/%d on %u.%u.%u.%u&bslash;n&quot;
comma
id|program
comma
id|version
comma
id|NIPQUAD
c_func
(paren
id|servaddr
)paren
)paren
suffix:semicolon
id|set_sockaddr
c_func
(paren
op_amp
id|sin
comma
id|servaddr
comma
l_int|0
)paren
suffix:semicolon
r_return
id|rpc_getport_external
c_func
(paren
op_amp
id|sin
comma
id|program
comma
id|version
comma
id|proto
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Use portmapper to find mountd and nfsd port numbers if not overriden&n; *  by the user. Use defaults if portmapper is not available.&n; *  XXX: Is there any nfs server with no portmapper?&n; */
DECL|function|root_nfs_ports
r_static
r_int
id|__init
id|root_nfs_ports
c_func
(paren
r_void
)paren
(brace
r_int
id|port
suffix:semicolon
r_int
id|nfsd_ver
comma
id|mountd_ver
suffix:semicolon
r_int
id|nfsd_port
comma
id|mountd_port
suffix:semicolon
r_int
id|proto
suffix:semicolon
r_if
c_cond
(paren
id|nfs_data.flags
op_amp
id|NFS_MOUNT_VER3
)paren
(brace
id|nfsd_ver
op_assign
id|NFS3_VERSION
suffix:semicolon
id|mountd_ver
op_assign
id|NFS_MNT3_VERSION
suffix:semicolon
id|nfsd_port
op_assign
id|NFS_PORT
suffix:semicolon
id|mountd_port
op_assign
id|NFS_MNT_PORT
suffix:semicolon
)brace
r_else
(brace
id|nfsd_ver
op_assign
id|NFS2_VERSION
suffix:semicolon
id|mountd_ver
op_assign
id|NFS_MNT_VERSION
suffix:semicolon
id|nfsd_port
op_assign
id|NFS_PORT
suffix:semicolon
id|mountd_port
op_assign
id|NFS_MNT_PORT
suffix:semicolon
)brace
id|proto
op_assign
(paren
id|nfs_data.flags
op_amp
id|NFS_MOUNT_TCP
)paren
ques
c_cond
id|IPPROTO_TCP
suffix:colon
id|IPPROTO_UDP
suffix:semicolon
r_if
c_cond
(paren
id|nfs_port
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|port
op_assign
id|root_nfs_getport
c_func
(paren
id|NFS_PROGRAM
comma
id|nfsd_ver
comma
id|proto
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Root-NFS: Unable to get nfsd port &quot;
l_string|&quot;number from server, using default&bslash;n&quot;
)paren
suffix:semicolon
id|port
op_assign
id|nfsd_port
suffix:semicolon
)brace
id|nfs_port
op_assign
id|htons
c_func
(paren
id|port
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;Root-NFS: Portmapper on server returned %d &quot;
l_string|&quot;as nfsd port&bslash;n&quot;
comma
id|port
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|port
op_assign
id|root_nfs_getport
c_func
(paren
id|NFS_MNT_PROGRAM
comma
id|mountd_ver
comma
id|proto
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Root-NFS: Unable to get mountd port &quot;
l_string|&quot;number from server, using default&bslash;n&quot;
)paren
suffix:semicolon
id|port
op_assign
id|mountd_port
suffix:semicolon
)brace
id|mount_port
op_assign
id|htons
c_func
(paren
id|port
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;Root-NFS: mountd port is %d&bslash;n&quot;
comma
id|port
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Get a file handle from the server for the directory which is to be&n; *  mounted.&n; */
DECL|function|root_nfs_get_handle
r_static
r_int
id|__init
id|root_nfs_get_handle
c_func
(paren
r_void
)paren
(brace
r_struct
id|nfs_fh
id|fh
suffix:semicolon
r_struct
id|sockaddr_in
id|sin
suffix:semicolon
r_int
id|status
suffix:semicolon
r_int
id|protocol
op_assign
(paren
id|nfs_data.flags
op_amp
id|NFS_MOUNT_TCP
)paren
ques
c_cond
id|IPPROTO_TCP
suffix:colon
id|IPPROTO_UDP
suffix:semicolon
r_int
id|version
op_assign
(paren
id|nfs_data.flags
op_amp
id|NFS_MOUNT_VER3
)paren
ques
c_cond
id|NFS_MNT3_VERSION
suffix:colon
id|NFS_MNT_VERSION
suffix:semicolon
id|set_sockaddr
c_func
(paren
op_amp
id|sin
comma
id|servaddr
comma
id|mount_port
)paren
suffix:semicolon
id|status
op_assign
id|nfsroot_mount
c_func
(paren
op_amp
id|sin
comma
id|nfs_path
comma
op_amp
id|fh
comma
id|version
comma
id|protocol
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Root-NFS: Server returned error %d &quot;
l_string|&quot;while mounting %s&bslash;n&quot;
comma
id|status
comma
id|nfs_path
)paren
suffix:semicolon
r_else
(brace
id|nfs_data.root.size
op_assign
id|fh.size
suffix:semicolon
id|memcpy
c_func
(paren
id|nfs_data.root.data
comma
id|fh.data
comma
id|fh.size
)paren
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; *  Get the NFS port numbers and file handle, and return the prepared &squot;data&squot;&n; *  argument for mount() if everything went OK. Return NULL otherwise.&n; */
DECL|function|nfs_root_data
r_void
op_star
id|__init
id|nfs_root_data
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|root_nfs_init
c_func
(paren
)paren
OL
l_int|0
op_logical_or
id|root_nfs_ports
c_func
(paren
)paren
OL
l_int|0
op_logical_or
id|root_nfs_get_handle
c_func
(paren
)paren
OL
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
id|set_sockaddr
c_func
(paren
(paren
r_struct
id|sockaddr_in
op_star
)paren
op_amp
id|nfs_data.addr
comma
id|servaddr
comma
id|nfs_port
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
op_amp
id|nfs_data
suffix:semicolon
)brace
eof
