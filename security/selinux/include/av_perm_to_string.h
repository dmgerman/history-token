multiline_comment|/* This file is automatically generated.  Do not edit. */
id|S_
c_func
(paren
id|SECCLASS_FILESYSTEM
comma
id|FILESYSTEM__MOUNT
comma
l_string|&quot;mount&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_FILESYSTEM
comma
id|FILESYSTEM__REMOUNT
comma
l_string|&quot;remount&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_FILESYSTEM
comma
id|FILESYSTEM__UNMOUNT
comma
l_string|&quot;unmount&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_FILESYSTEM
comma
id|FILESYSTEM__GETATTR
comma
l_string|&quot;getattr&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_FILESYSTEM
comma
id|FILESYSTEM__RELABELFROM
comma
l_string|&quot;relabelfrom&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_FILESYSTEM
comma
id|FILESYSTEM__RELABELTO
comma
l_string|&quot;relabelto&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_FILESYSTEM
comma
id|FILESYSTEM__TRANSITION
comma
l_string|&quot;transition&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_FILESYSTEM
comma
id|FILESYSTEM__ASSOCIATE
comma
l_string|&quot;associate&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_FILESYSTEM
comma
id|FILESYSTEM__QUOTAMOD
comma
l_string|&quot;quotamod&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_FILESYSTEM
comma
id|FILESYSTEM__QUOTAGET
comma
l_string|&quot;quotaget&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_DIR
comma
id|DIR__ADD_NAME
comma
l_string|&quot;add_name&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_DIR
comma
id|DIR__REMOVE_NAME
comma
l_string|&quot;remove_name&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_DIR
comma
id|DIR__REPARENT
comma
l_string|&quot;reparent&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_DIR
comma
id|DIR__SEARCH
comma
l_string|&quot;search&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_DIR
comma
id|DIR__RMDIR
comma
l_string|&quot;rmdir&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_FILE
comma
id|FILE__EXECUTE_NO_TRANS
comma
l_string|&quot;execute_no_trans&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_FILE
comma
id|FILE__ENTRYPOINT
comma
l_string|&quot;entrypoint&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_FILE
comma
id|FILE__EXECMOD
comma
l_string|&quot;execmod&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CHR_FILE
comma
id|CHR_FILE__EXECUTE_NO_TRANS
comma
l_string|&quot;execute_no_trans&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CHR_FILE
comma
id|CHR_FILE__ENTRYPOINT
comma
l_string|&quot;entrypoint&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CHR_FILE
comma
id|CHR_FILE__EXECMOD
comma
l_string|&quot;execmod&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_FD
comma
id|FD__USE
comma
l_string|&quot;use&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_TCP_SOCKET
comma
id|TCP_SOCKET__CONNECTTO
comma
l_string|&quot;connectto&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_TCP_SOCKET
comma
id|TCP_SOCKET__NEWCONN
comma
l_string|&quot;newconn&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_TCP_SOCKET
comma
id|TCP_SOCKET__ACCEPTFROM
comma
l_string|&quot;acceptfrom&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_TCP_SOCKET
comma
id|TCP_SOCKET__NODE_BIND
comma
l_string|&quot;node_bind&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_UDP_SOCKET
comma
id|UDP_SOCKET__NODE_BIND
comma
l_string|&quot;node_bind&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_RAWIP_SOCKET
comma
id|RAWIP_SOCKET__NODE_BIND
comma
l_string|&quot;node_bind&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NODE
comma
id|NODE__TCP_RECV
comma
l_string|&quot;tcp_recv&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NODE
comma
id|NODE__TCP_SEND
comma
l_string|&quot;tcp_send&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NODE
comma
id|NODE__UDP_RECV
comma
l_string|&quot;udp_recv&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NODE
comma
id|NODE__UDP_SEND
comma
l_string|&quot;udp_send&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NODE
comma
id|NODE__RAWIP_RECV
comma
l_string|&quot;rawip_recv&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NODE
comma
id|NODE__RAWIP_SEND
comma
l_string|&quot;rawip_send&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NODE
comma
id|NODE__ENFORCE_DEST
comma
l_string|&quot;enforce_dest&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NETIF
comma
id|NETIF__TCP_RECV
comma
l_string|&quot;tcp_recv&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NETIF
comma
id|NETIF__TCP_SEND
comma
l_string|&quot;tcp_send&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NETIF
comma
id|NETIF__UDP_RECV
comma
l_string|&quot;udp_recv&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NETIF
comma
id|NETIF__UDP_SEND
comma
l_string|&quot;udp_send&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NETIF
comma
id|NETIF__RAWIP_RECV
comma
l_string|&quot;rawip_recv&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NETIF
comma
id|NETIF__RAWIP_SEND
comma
l_string|&quot;rawip_send&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_UNIX_STREAM_SOCKET
comma
id|UNIX_STREAM_SOCKET__CONNECTTO
comma
l_string|&quot;connectto&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_UNIX_STREAM_SOCKET
comma
id|UNIX_STREAM_SOCKET__NEWCONN
comma
l_string|&quot;newconn&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_UNIX_STREAM_SOCKET
comma
id|UNIX_STREAM_SOCKET__ACCEPTFROM
comma
l_string|&quot;acceptfrom&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__FORK
comma
l_string|&quot;fork&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__TRANSITION
comma
l_string|&quot;transition&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__SIGCHLD
comma
l_string|&quot;sigchld&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__SIGKILL
comma
l_string|&quot;sigkill&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__SIGSTOP
comma
l_string|&quot;sigstop&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__SIGNULL
comma
l_string|&quot;signull&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__SIGNAL
comma
l_string|&quot;signal&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__PTRACE
comma
l_string|&quot;ptrace&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__GETSCHED
comma
l_string|&quot;getsched&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__SETSCHED
comma
l_string|&quot;setsched&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__GETSESSION
comma
l_string|&quot;getsession&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__GETPGID
comma
l_string|&quot;getpgid&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__SETPGID
comma
l_string|&quot;setpgid&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__GETCAP
comma
l_string|&quot;getcap&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__SETCAP
comma
l_string|&quot;setcap&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__SHARE
comma
l_string|&quot;share&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__GETATTR
comma
l_string|&quot;getattr&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__SETEXEC
comma
l_string|&quot;setexec&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__SETFSCREATE
comma
l_string|&quot;setfscreate&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__NOATSECURE
comma
l_string|&quot;noatsecure&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__SIGINH
comma
l_string|&quot;siginh&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__SETRLIMIT
comma
l_string|&quot;setrlimit&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__RLIMITINH
comma
l_string|&quot;rlimitinh&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__DYNTRANSITION
comma
l_string|&quot;dyntransition&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__SETCURRENT
comma
l_string|&quot;setcurrent&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROCESS
comma
id|PROCESS__EXECMEM
comma
l_string|&quot;execmem&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_MSGQ
comma
id|MSGQ__ENQUEUE
comma
l_string|&quot;enqueue&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_MSG
comma
id|MSG__SEND
comma
l_string|&quot;send&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_MSG
comma
id|MSG__RECEIVE
comma
l_string|&quot;receive&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_SHM
comma
id|SHM__LOCK
comma
l_string|&quot;lock&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_SECURITY
comma
id|SECURITY__COMPUTE_AV
comma
l_string|&quot;compute_av&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_SECURITY
comma
id|SECURITY__COMPUTE_CREATE
comma
l_string|&quot;compute_create&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_SECURITY
comma
id|SECURITY__COMPUTE_MEMBER
comma
l_string|&quot;compute_member&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_SECURITY
comma
id|SECURITY__CHECK_CONTEXT
comma
l_string|&quot;check_context&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_SECURITY
comma
id|SECURITY__LOAD_POLICY
comma
l_string|&quot;load_policy&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_SECURITY
comma
id|SECURITY__COMPUTE_RELABEL
comma
l_string|&quot;compute_relabel&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_SECURITY
comma
id|SECURITY__COMPUTE_USER
comma
l_string|&quot;compute_user&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_SECURITY
comma
id|SECURITY__SETENFORCE
comma
l_string|&quot;setenforce&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_SECURITY
comma
id|SECURITY__SETBOOL
comma
l_string|&quot;setbool&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_SECURITY
comma
id|SECURITY__SETSECPARAM
comma
l_string|&quot;setsecparam&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_SYSTEM
comma
id|SYSTEM__IPC_INFO
comma
l_string|&quot;ipc_info&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_SYSTEM
comma
id|SYSTEM__SYSLOG_READ
comma
l_string|&quot;syslog_read&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_SYSTEM
comma
id|SYSTEM__SYSLOG_MOD
comma
l_string|&quot;syslog_mod&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_SYSTEM
comma
id|SYSTEM__SYSLOG_CONSOLE
comma
l_string|&quot;syslog_console&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__CHOWN
comma
l_string|&quot;chown&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__DAC_OVERRIDE
comma
l_string|&quot;dac_override&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__DAC_READ_SEARCH
comma
l_string|&quot;dac_read_search&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__FOWNER
comma
l_string|&quot;fowner&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__FSETID
comma
l_string|&quot;fsetid&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__KILL
comma
l_string|&quot;kill&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__SETGID
comma
l_string|&quot;setgid&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__SETUID
comma
l_string|&quot;setuid&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__SETPCAP
comma
l_string|&quot;setpcap&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__LINUX_IMMUTABLE
comma
l_string|&quot;linux_immutable&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__NET_BIND_SERVICE
comma
l_string|&quot;net_bind_service&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__NET_BROADCAST
comma
l_string|&quot;net_broadcast&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__NET_ADMIN
comma
l_string|&quot;net_admin&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__NET_RAW
comma
l_string|&quot;net_raw&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__IPC_LOCK
comma
l_string|&quot;ipc_lock&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__IPC_OWNER
comma
l_string|&quot;ipc_owner&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__SYS_MODULE
comma
l_string|&quot;sys_module&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__SYS_RAWIO
comma
l_string|&quot;sys_rawio&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__SYS_CHROOT
comma
l_string|&quot;sys_chroot&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__SYS_PTRACE
comma
l_string|&quot;sys_ptrace&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__SYS_PACCT
comma
l_string|&quot;sys_pacct&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__SYS_ADMIN
comma
l_string|&quot;sys_admin&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__SYS_BOOT
comma
l_string|&quot;sys_boot&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__SYS_NICE
comma
l_string|&quot;sys_nice&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__SYS_RESOURCE
comma
l_string|&quot;sys_resource&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__SYS_TIME
comma
l_string|&quot;sys_time&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__SYS_TTY_CONFIG
comma
l_string|&quot;sys_tty_config&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__MKNOD
comma
l_string|&quot;mknod&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CAPABILITY
comma
id|CAPABILITY__LEASE
comma
l_string|&quot;lease&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PASSWD
comma
id|PASSWD__PASSWD
comma
l_string|&quot;passwd&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PASSWD
comma
id|PASSWD__CHFN
comma
l_string|&quot;chfn&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PASSWD
comma
id|PASSWD__CHSH
comma
l_string|&quot;chsh&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PASSWD
comma
id|PASSWD__ROOTOK
comma
l_string|&quot;rootok&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PASSWD
comma
id|PASSWD__CRONTAB
comma
l_string|&quot;crontab&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_DRAWABLE
comma
id|DRAWABLE__CREATE
comma
l_string|&quot;create&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_DRAWABLE
comma
id|DRAWABLE__DESTROY
comma
l_string|&quot;destroy&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_DRAWABLE
comma
id|DRAWABLE__DRAW
comma
l_string|&quot;draw&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_DRAWABLE
comma
id|DRAWABLE__COPY
comma
l_string|&quot;copy&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_DRAWABLE
comma
id|DRAWABLE__GETATTR
comma
l_string|&quot;getattr&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_GC
comma
id|GC__CREATE
comma
l_string|&quot;create&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_GC
comma
id|GC__FREE
comma
l_string|&quot;free&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_GC
comma
id|GC__GETATTR
comma
l_string|&quot;getattr&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_GC
comma
id|GC__SETATTR
comma
l_string|&quot;setattr&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__ADDCHILD
comma
l_string|&quot;addchild&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__CREATE
comma
l_string|&quot;create&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__DESTROY
comma
l_string|&quot;destroy&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__MAP
comma
l_string|&quot;map&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__UNMAP
comma
l_string|&quot;unmap&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__CHSTACK
comma
l_string|&quot;chstack&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__CHPROPLIST
comma
l_string|&quot;chproplist&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__CHPROP
comma
l_string|&quot;chprop&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__LISTPROP
comma
l_string|&quot;listprop&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__GETATTR
comma
l_string|&quot;getattr&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__SETATTR
comma
l_string|&quot;setattr&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__SETFOCUS
comma
l_string|&quot;setfocus&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__MOVE
comma
l_string|&quot;move&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__CHSELECTION
comma
l_string|&quot;chselection&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__CHPARENT
comma
l_string|&quot;chparent&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__CTRLLIFE
comma
l_string|&quot;ctrllife&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__ENUMERATE
comma
l_string|&quot;enumerate&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__TRANSPARENT
comma
l_string|&quot;transparent&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__MOUSEMOTION
comma
l_string|&quot;mousemotion&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__CLIENTCOMEVENT
comma
l_string|&quot;clientcomevent&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__INPUTEVENT
comma
l_string|&quot;inputevent&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__DRAWEVENT
comma
l_string|&quot;drawevent&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__WINDOWCHANGEEVENT
comma
l_string|&quot;windowchangeevent&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__WINDOWCHANGEREQUEST
comma
l_string|&quot;windowchangerequest&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__SERVERCHANGEEVENT
comma
l_string|&quot;serverchangeevent&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_WINDOW
comma
id|WINDOW__EXTENSIONEVENT
comma
l_string|&quot;extensionevent&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_FONT
comma
id|FONT__LOAD
comma
l_string|&quot;load&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_FONT
comma
id|FONT__FREE
comma
l_string|&quot;free&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_FONT
comma
id|FONT__GETATTR
comma
l_string|&quot;getattr&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_FONT
comma
id|FONT__USE
comma
l_string|&quot;use&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_COLORMAP
comma
id|COLORMAP__CREATE
comma
l_string|&quot;create&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_COLORMAP
comma
id|COLORMAP__FREE
comma
l_string|&quot;free&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_COLORMAP
comma
id|COLORMAP__INSTALL
comma
l_string|&quot;install&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_COLORMAP
comma
id|COLORMAP__UNINSTALL
comma
l_string|&quot;uninstall&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_COLORMAP
comma
id|COLORMAP__LIST
comma
l_string|&quot;list&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_COLORMAP
comma
id|COLORMAP__READ
comma
l_string|&quot;read&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_COLORMAP
comma
id|COLORMAP__STORE
comma
l_string|&quot;store&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_COLORMAP
comma
id|COLORMAP__GETATTR
comma
l_string|&quot;getattr&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_COLORMAP
comma
id|COLORMAP__SETATTR
comma
l_string|&quot;setattr&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROPERTY
comma
id|PROPERTY__CREATE
comma
l_string|&quot;create&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROPERTY
comma
id|PROPERTY__FREE
comma
l_string|&quot;free&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROPERTY
comma
id|PROPERTY__READ
comma
l_string|&quot;read&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PROPERTY
comma
id|PROPERTY__WRITE
comma
l_string|&quot;write&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CURSOR
comma
id|CURSOR__CREATE
comma
l_string|&quot;create&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CURSOR
comma
id|CURSOR__CREATEGLYPH
comma
l_string|&quot;createglyph&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CURSOR
comma
id|CURSOR__FREE
comma
l_string|&quot;free&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CURSOR
comma
id|CURSOR__ASSIGN
comma
l_string|&quot;assign&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_CURSOR
comma
id|CURSOR__SETATTR
comma
l_string|&quot;setattr&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_XCLIENT
comma
id|XCLIENT__KILL
comma
l_string|&quot;kill&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_XINPUT
comma
id|XINPUT__LOOKUP
comma
l_string|&quot;lookup&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_XINPUT
comma
id|XINPUT__GETATTR
comma
l_string|&quot;getattr&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_XINPUT
comma
id|XINPUT__SETATTR
comma
l_string|&quot;setattr&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_XINPUT
comma
id|XINPUT__SETFOCUS
comma
l_string|&quot;setfocus&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_XINPUT
comma
id|XINPUT__WARPPOINTER
comma
l_string|&quot;warppointer&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_XINPUT
comma
id|XINPUT__ACTIVEGRAB
comma
l_string|&quot;activegrab&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_XINPUT
comma
id|XINPUT__PASSIVEGRAB
comma
l_string|&quot;passivegrab&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_XINPUT
comma
id|XINPUT__UNGRAB
comma
l_string|&quot;ungrab&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_XINPUT
comma
id|XINPUT__BELL
comma
l_string|&quot;bell&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_XINPUT
comma
id|XINPUT__MOUSEMOTION
comma
l_string|&quot;mousemotion&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_XINPUT
comma
id|XINPUT__RELABELINPUT
comma
l_string|&quot;relabelinput&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_XSERVER
comma
id|XSERVER__SCREENSAVER
comma
l_string|&quot;screensaver&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_XSERVER
comma
id|XSERVER__GETHOSTLIST
comma
l_string|&quot;gethostlist&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_XSERVER
comma
id|XSERVER__SETHOSTLIST
comma
l_string|&quot;sethostlist&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_XSERVER
comma
id|XSERVER__GETFONTPATH
comma
l_string|&quot;getfontpath&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_XSERVER
comma
id|XSERVER__SETFONTPATH
comma
l_string|&quot;setfontpath&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_XSERVER
comma
id|XSERVER__GETATTR
comma
l_string|&quot;getattr&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_XSERVER
comma
id|XSERVER__GRAB
comma
l_string|&quot;grab&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_XSERVER
comma
id|XSERVER__UNGRAB
comma
l_string|&quot;ungrab&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_XEXTENSION
comma
id|XEXTENSION__QUERY
comma
l_string|&quot;query&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_XEXTENSION
comma
id|XEXTENSION__USE
comma
l_string|&quot;use&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PAX
comma
id|PAX__PAGEEXEC
comma
l_string|&quot;pageexec&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PAX
comma
id|PAX__EMUTRAMP
comma
l_string|&quot;emutramp&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PAX
comma
id|PAX__MPROTECT
comma
l_string|&quot;mprotect&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PAX
comma
id|PAX__RANDMMAP
comma
l_string|&quot;randmmap&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PAX
comma
id|PAX__RANDEXEC
comma
l_string|&quot;randexec&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_PAX
comma
id|PAX__SEGMEXEC
comma
l_string|&quot;segmexec&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NETLINK_ROUTE_SOCKET
comma
id|NETLINK_ROUTE_SOCKET__NLMSG_READ
comma
l_string|&quot;nlmsg_read&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NETLINK_ROUTE_SOCKET
comma
id|NETLINK_ROUTE_SOCKET__NLMSG_WRITE
comma
l_string|&quot;nlmsg_write&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NETLINK_FIREWALL_SOCKET
comma
id|NETLINK_FIREWALL_SOCKET__NLMSG_READ
comma
l_string|&quot;nlmsg_read&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NETLINK_FIREWALL_SOCKET
comma
id|NETLINK_FIREWALL_SOCKET__NLMSG_WRITE
comma
l_string|&quot;nlmsg_write&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NETLINK_TCPDIAG_SOCKET
comma
id|NETLINK_TCPDIAG_SOCKET__NLMSG_READ
comma
l_string|&quot;nlmsg_read&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NETLINK_TCPDIAG_SOCKET
comma
id|NETLINK_TCPDIAG_SOCKET__NLMSG_WRITE
comma
l_string|&quot;nlmsg_write&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NETLINK_XFRM_SOCKET
comma
id|NETLINK_XFRM_SOCKET__NLMSG_READ
comma
l_string|&quot;nlmsg_read&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NETLINK_XFRM_SOCKET
comma
id|NETLINK_XFRM_SOCKET__NLMSG_WRITE
comma
l_string|&quot;nlmsg_write&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NETLINK_AUDIT_SOCKET
comma
id|NETLINK_AUDIT_SOCKET__NLMSG_READ
comma
l_string|&quot;nlmsg_read&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NETLINK_AUDIT_SOCKET
comma
id|NETLINK_AUDIT_SOCKET__NLMSG_WRITE
comma
l_string|&quot;nlmsg_write&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NETLINK_IP6FW_SOCKET
comma
id|NETLINK_IP6FW_SOCKET__NLMSG_READ
comma
l_string|&quot;nlmsg_read&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NETLINK_IP6FW_SOCKET
comma
id|NETLINK_IP6FW_SOCKET__NLMSG_WRITE
comma
l_string|&quot;nlmsg_write&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_DBUS
comma
id|DBUS__ACQUIRE_SVC
comma
l_string|&quot;acquire_svc&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_DBUS
comma
id|DBUS__SEND_MSG
comma
l_string|&quot;send_msg&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NSCD
comma
id|NSCD__GETPWD
comma
l_string|&quot;getpwd&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NSCD
comma
id|NSCD__GETGRP
comma
l_string|&quot;getgrp&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NSCD
comma
id|NSCD__GETHOST
comma
l_string|&quot;gethost&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NSCD
comma
id|NSCD__GETSTAT
comma
l_string|&quot;getstat&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NSCD
comma
id|NSCD__ADMIN
comma
l_string|&quot;admin&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NSCD
comma
id|NSCD__SHMEMPWD
comma
l_string|&quot;shmempwd&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NSCD
comma
id|NSCD__SHMEMGRP
comma
l_string|&quot;shmemgrp&quot;
)paren
id|S_
c_func
(paren
id|SECCLASS_NSCD
comma
id|NSCD__SHMEMHOST
comma
l_string|&quot;shmemhost&quot;
)paren
eof
