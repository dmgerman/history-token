multiline_comment|/* This file is automatically generated.  Do not edit. */
macro_line|#ifndef _SELINUX_FLASK_H_
DECL|macro|_SELINUX_FLASK_H_
mdefine_line|#define _SELINUX_FLASK_H_
multiline_comment|/*&n; * Security object class definitions&n; */
DECL|macro|SECCLASS_SECURITY
mdefine_line|#define SECCLASS_SECURITY                                1
DECL|macro|SECCLASS_PROCESS
mdefine_line|#define SECCLASS_PROCESS                                 2
DECL|macro|SECCLASS_SYSTEM
mdefine_line|#define SECCLASS_SYSTEM                                  3
DECL|macro|SECCLASS_CAPABILITY
mdefine_line|#define SECCLASS_CAPABILITY                              4
DECL|macro|SECCLASS_FILESYSTEM
mdefine_line|#define SECCLASS_FILESYSTEM                              5
DECL|macro|SECCLASS_FILE
mdefine_line|#define SECCLASS_FILE                                    6
DECL|macro|SECCLASS_DIR
mdefine_line|#define SECCLASS_DIR                                     7
DECL|macro|SECCLASS_FD
mdefine_line|#define SECCLASS_FD                                      8
DECL|macro|SECCLASS_LNK_FILE
mdefine_line|#define SECCLASS_LNK_FILE                                9
DECL|macro|SECCLASS_CHR_FILE
mdefine_line|#define SECCLASS_CHR_FILE                                10
DECL|macro|SECCLASS_BLK_FILE
mdefine_line|#define SECCLASS_BLK_FILE                                11
DECL|macro|SECCLASS_SOCK_FILE
mdefine_line|#define SECCLASS_SOCK_FILE                               12
DECL|macro|SECCLASS_FIFO_FILE
mdefine_line|#define SECCLASS_FIFO_FILE                               13
DECL|macro|SECCLASS_SOCKET
mdefine_line|#define SECCLASS_SOCKET                                  14
DECL|macro|SECCLASS_TCP_SOCKET
mdefine_line|#define SECCLASS_TCP_SOCKET                              15
DECL|macro|SECCLASS_UDP_SOCKET
mdefine_line|#define SECCLASS_UDP_SOCKET                              16
DECL|macro|SECCLASS_RAWIP_SOCKET
mdefine_line|#define SECCLASS_RAWIP_SOCKET                            17
DECL|macro|SECCLASS_NODE
mdefine_line|#define SECCLASS_NODE                                    18
DECL|macro|SECCLASS_NETIF
mdefine_line|#define SECCLASS_NETIF                                   19
DECL|macro|SECCLASS_NETLINK_SOCKET
mdefine_line|#define SECCLASS_NETLINK_SOCKET                          20
DECL|macro|SECCLASS_PACKET_SOCKET
mdefine_line|#define SECCLASS_PACKET_SOCKET                           21
DECL|macro|SECCLASS_KEY_SOCKET
mdefine_line|#define SECCLASS_KEY_SOCKET                              22
DECL|macro|SECCLASS_UNIX_STREAM_SOCKET
mdefine_line|#define SECCLASS_UNIX_STREAM_SOCKET                      23
DECL|macro|SECCLASS_UNIX_DGRAM_SOCKET
mdefine_line|#define SECCLASS_UNIX_DGRAM_SOCKET                       24
DECL|macro|SECCLASS_SEM
mdefine_line|#define SECCLASS_SEM                                     25
DECL|macro|SECCLASS_MSG
mdefine_line|#define SECCLASS_MSG                                     26
DECL|macro|SECCLASS_MSGQ
mdefine_line|#define SECCLASS_MSGQ                                    27
DECL|macro|SECCLASS_SHM
mdefine_line|#define SECCLASS_SHM                                     28
DECL|macro|SECCLASS_IPC
mdefine_line|#define SECCLASS_IPC                                     29
DECL|macro|SECCLASS_PASSWD
mdefine_line|#define SECCLASS_PASSWD                                  30
DECL|macro|SECCLASS_DRAWABLE
mdefine_line|#define SECCLASS_DRAWABLE                                31
DECL|macro|SECCLASS_WINDOW
mdefine_line|#define SECCLASS_WINDOW                                  32
DECL|macro|SECCLASS_GC
mdefine_line|#define SECCLASS_GC                                      33
DECL|macro|SECCLASS_FONT
mdefine_line|#define SECCLASS_FONT                                    34
DECL|macro|SECCLASS_COLORMAP
mdefine_line|#define SECCLASS_COLORMAP                                35
DECL|macro|SECCLASS_PROPERTY
mdefine_line|#define SECCLASS_PROPERTY                                36
DECL|macro|SECCLASS_CURSOR
mdefine_line|#define SECCLASS_CURSOR                                  37
DECL|macro|SECCLASS_XCLIENT
mdefine_line|#define SECCLASS_XCLIENT                                 38
DECL|macro|SECCLASS_XINPUT
mdefine_line|#define SECCLASS_XINPUT                                  39
DECL|macro|SECCLASS_XSERVER
mdefine_line|#define SECCLASS_XSERVER                                 40
DECL|macro|SECCLASS_XEXTENSION
mdefine_line|#define SECCLASS_XEXTENSION                              41
DECL|macro|SECCLASS_PAX
mdefine_line|#define SECCLASS_PAX                                     42
DECL|macro|SECCLASS_NETLINK_ROUTE_SOCKET
mdefine_line|#define SECCLASS_NETLINK_ROUTE_SOCKET                    43
DECL|macro|SECCLASS_NETLINK_FIREWALL_SOCKET
mdefine_line|#define SECCLASS_NETLINK_FIREWALL_SOCKET                 44
DECL|macro|SECCLASS_NETLINK_TCPDIAG_SOCKET
mdefine_line|#define SECCLASS_NETLINK_TCPDIAG_SOCKET                  45
DECL|macro|SECCLASS_NETLINK_NFLOG_SOCKET
mdefine_line|#define SECCLASS_NETLINK_NFLOG_SOCKET                    46
DECL|macro|SECCLASS_NETLINK_XFRM_SOCKET
mdefine_line|#define SECCLASS_NETLINK_XFRM_SOCKET                     47
DECL|macro|SECCLASS_NETLINK_SELINUX_SOCKET
mdefine_line|#define SECCLASS_NETLINK_SELINUX_SOCKET                  48
DECL|macro|SECCLASS_NETLINK_AUDIT_SOCKET
mdefine_line|#define SECCLASS_NETLINK_AUDIT_SOCKET                    49
DECL|macro|SECCLASS_NETLINK_IP6FW_SOCKET
mdefine_line|#define SECCLASS_NETLINK_IP6FW_SOCKET                    50
DECL|macro|SECCLASS_NETLINK_DNRT_SOCKET
mdefine_line|#define SECCLASS_NETLINK_DNRT_SOCKET                     51
DECL|macro|SECCLASS_DBUS
mdefine_line|#define SECCLASS_DBUS                                    52
DECL|macro|SECCLASS_NSCD
mdefine_line|#define SECCLASS_NSCD                                    53
multiline_comment|/*&n; * Security identifier indices for initial entities&n; */
DECL|macro|SECINITSID_KERNEL
mdefine_line|#define SECINITSID_KERNEL                               1
DECL|macro|SECINITSID_SECURITY
mdefine_line|#define SECINITSID_SECURITY                             2
DECL|macro|SECINITSID_UNLABELED
mdefine_line|#define SECINITSID_UNLABELED                            3
DECL|macro|SECINITSID_FS
mdefine_line|#define SECINITSID_FS                                   4
DECL|macro|SECINITSID_FILE
mdefine_line|#define SECINITSID_FILE                                 5
DECL|macro|SECINITSID_FILE_LABELS
mdefine_line|#define SECINITSID_FILE_LABELS                          6
DECL|macro|SECINITSID_INIT
mdefine_line|#define SECINITSID_INIT                                 7
DECL|macro|SECINITSID_ANY_SOCKET
mdefine_line|#define SECINITSID_ANY_SOCKET                           8
DECL|macro|SECINITSID_PORT
mdefine_line|#define SECINITSID_PORT                                 9
DECL|macro|SECINITSID_NETIF
mdefine_line|#define SECINITSID_NETIF                                10
DECL|macro|SECINITSID_NETMSG
mdefine_line|#define SECINITSID_NETMSG                               11
DECL|macro|SECINITSID_NODE
mdefine_line|#define SECINITSID_NODE                                 12
DECL|macro|SECINITSID_IGMP_PACKET
mdefine_line|#define SECINITSID_IGMP_PACKET                          13
DECL|macro|SECINITSID_ICMP_SOCKET
mdefine_line|#define SECINITSID_ICMP_SOCKET                          14
DECL|macro|SECINITSID_TCP_SOCKET
mdefine_line|#define SECINITSID_TCP_SOCKET                           15
DECL|macro|SECINITSID_SYSCTL_MODPROBE
mdefine_line|#define SECINITSID_SYSCTL_MODPROBE                      16
DECL|macro|SECINITSID_SYSCTL
mdefine_line|#define SECINITSID_SYSCTL                               17
DECL|macro|SECINITSID_SYSCTL_FS
mdefine_line|#define SECINITSID_SYSCTL_FS                            18
DECL|macro|SECINITSID_SYSCTL_KERNEL
mdefine_line|#define SECINITSID_SYSCTL_KERNEL                        19
DECL|macro|SECINITSID_SYSCTL_NET
mdefine_line|#define SECINITSID_SYSCTL_NET                           20
DECL|macro|SECINITSID_SYSCTL_NET_UNIX
mdefine_line|#define SECINITSID_SYSCTL_NET_UNIX                      21
DECL|macro|SECINITSID_SYSCTL_VM
mdefine_line|#define SECINITSID_SYSCTL_VM                            22
DECL|macro|SECINITSID_SYSCTL_DEV
mdefine_line|#define SECINITSID_SYSCTL_DEV                           23
DECL|macro|SECINITSID_KMOD
mdefine_line|#define SECINITSID_KMOD                                 24
DECL|macro|SECINITSID_POLICY
mdefine_line|#define SECINITSID_POLICY                               25
DECL|macro|SECINITSID_SCMP_PACKET
mdefine_line|#define SECINITSID_SCMP_PACKET                          26
DECL|macro|SECINITSID_DEVNULL
mdefine_line|#define SECINITSID_DEVNULL                              27
DECL|macro|SECINITSID_NUM
mdefine_line|#define SECINITSID_NUM                                  27
macro_line|#endif
eof
