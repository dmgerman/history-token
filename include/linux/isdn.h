multiline_comment|/* $Id: isdn.h,v 1.111.6.9 2001/09/23 22:25:05 kai Exp $&n; *&n; * Main header for the Linux ISDN subsystem (linklevel).&n; *&n; * Copyright 1994,95,96 by Fritz Elfert (fritz@isdn4linux.de)&n; * Copyright 1995,96    by Thinking Objects Software GmbH Wuerzburg&n; * Copyright 1995,96    by Michael Hipp (Michael.Hipp@student.uni-tuebingen.de)&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#ifndef __ISDN_H__
DECL|macro|__ISDN_H__
mdefine_line|#define __ISDN_H__
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#ifdef CONFIG_COBALT_MICRO_SERVER
multiline_comment|/* Save memory */
DECL|macro|ISDN_MAX_DRIVERS
mdefine_line|#define ISDN_MAX_DRIVERS    2
DECL|macro|ISDN_MAX_CHANNELS
mdefine_line|#define ISDN_MAX_CHANNELS   8
macro_line|#else
DECL|macro|ISDN_MAX_DRIVERS
mdefine_line|#define ISDN_MAX_DRIVERS    32
DECL|macro|ISDN_MAX_CHANNELS
mdefine_line|#define ISDN_MAX_CHANNELS   64
macro_line|#endif
multiline_comment|/* New ioctl-codes */
DECL|macro|IIOCNETAIF
mdefine_line|#define IIOCNETAIF  _IO(&squot;I&squot;,1)
DECL|macro|IIOCNETDIF
mdefine_line|#define IIOCNETDIF  _IO(&squot;I&squot;,2)
DECL|macro|IIOCNETSCF
mdefine_line|#define IIOCNETSCF  _IO(&squot;I&squot;,3)
DECL|macro|IIOCNETGCF
mdefine_line|#define IIOCNETGCF  _IO(&squot;I&squot;,4)
DECL|macro|IIOCNETANM
mdefine_line|#define IIOCNETANM  _IO(&squot;I&squot;,5)
DECL|macro|IIOCNETDNM
mdefine_line|#define IIOCNETDNM  _IO(&squot;I&squot;,6)
DECL|macro|IIOCNETGNM
mdefine_line|#define IIOCNETGNM  _IO(&squot;I&squot;,7)
DECL|macro|IIOCGETSET
mdefine_line|#define IIOCGETSET  _IO(&squot;I&squot;,8) /* no longer supported */
DECL|macro|IIOCSETSET
mdefine_line|#define IIOCSETSET  _IO(&squot;I&squot;,9) /* no longer supported */
DECL|macro|IIOCSETVER
mdefine_line|#define IIOCSETVER  _IO(&squot;I&squot;,10)
DECL|macro|IIOCNETHUP
mdefine_line|#define IIOCNETHUP  _IO(&squot;I&squot;,11)
DECL|macro|IIOCSETGST
mdefine_line|#define IIOCSETGST  _IO(&squot;I&squot;,12)
DECL|macro|IIOCSETBRJ
mdefine_line|#define IIOCSETBRJ  _IO(&squot;I&squot;,13)
DECL|macro|IIOCSIGPRF
mdefine_line|#define IIOCSIGPRF  _IO(&squot;I&squot;,14)
DECL|macro|IIOCGETPRF
mdefine_line|#define IIOCGETPRF  _IO(&squot;I&squot;,15)
DECL|macro|IIOCSETPRF
mdefine_line|#define IIOCSETPRF  _IO(&squot;I&squot;,16)
DECL|macro|IIOCGETMAP
mdefine_line|#define IIOCGETMAP  _IO(&squot;I&squot;,17)
DECL|macro|IIOCSETMAP
mdefine_line|#define IIOCSETMAP  _IO(&squot;I&squot;,18)
DECL|macro|IIOCNETASL
mdefine_line|#define IIOCNETASL  _IO(&squot;I&squot;,19)
DECL|macro|IIOCNETDIL
mdefine_line|#define IIOCNETDIL  _IO(&squot;I&squot;,20)
DECL|macro|IIOCGETCPS
mdefine_line|#define IIOCGETCPS  _IO(&squot;I&squot;,21)
DECL|macro|IIOCGETDVR
mdefine_line|#define IIOCGETDVR  _IO(&squot;I&squot;,22)
DECL|macro|IIOCNETLCR
mdefine_line|#define IIOCNETLCR  _IO(&squot;I&squot;,23) /* dwabc ioctl for LCR from isdnlog */
DECL|macro|IIOCNETDWRSET
mdefine_line|#define IIOCNETDWRSET  _IO(&squot;I&squot;,24) /* dwabc ioctl to reset abc-values to default on a net-interface */
DECL|macro|IIOCNETALN
mdefine_line|#define IIOCNETALN  _IO(&squot;I&squot;,32)
DECL|macro|IIOCNETDLN
mdefine_line|#define IIOCNETDLN  _IO(&squot;I&squot;,33)
DECL|macro|IIOCNETGPN
mdefine_line|#define IIOCNETGPN  _IO(&squot;I&squot;,34)
DECL|macro|IIOCDBGVAR
mdefine_line|#define IIOCDBGVAR  _IO(&squot;I&squot;,127)
DECL|macro|IIOCDRVCTL
mdefine_line|#define IIOCDRVCTL  _IO(&squot;I&squot;,128)
multiline_comment|/* cisco hdlck device private ioctls */
DECL|macro|SIOCGKEEPPERIOD
mdefine_line|#define SIOCGKEEPPERIOD&t;(SIOCDEVPRIVATE + 0)
DECL|macro|SIOCSKEEPPERIOD
mdefine_line|#define SIOCSKEEPPERIOD&t;(SIOCDEVPRIVATE + 1)
DECL|macro|SIOCGDEBSERINT
mdefine_line|#define SIOCGDEBSERINT&t;(SIOCDEVPRIVATE + 2)
DECL|macro|SIOCSDEBSERINT
mdefine_line|#define SIOCSDEBSERINT&t;(SIOCDEVPRIVATE + 3)
multiline_comment|/* Packet encapsulations for net-interfaces */
DECL|macro|ISDN_NET_ENCAP_ETHER
mdefine_line|#define ISDN_NET_ENCAP_ETHER      0
DECL|macro|ISDN_NET_ENCAP_RAWIP
mdefine_line|#define ISDN_NET_ENCAP_RAWIP      1
DECL|macro|ISDN_NET_ENCAP_IPTYP
mdefine_line|#define ISDN_NET_ENCAP_IPTYP      2
DECL|macro|ISDN_NET_ENCAP_CISCOHDLC
mdefine_line|#define ISDN_NET_ENCAP_CISCOHDLC  3 /* Without SLARP and keepalive */
DECL|macro|ISDN_NET_ENCAP_SYNCPPP
mdefine_line|#define ISDN_NET_ENCAP_SYNCPPP    4
DECL|macro|ISDN_NET_ENCAP_UIHDLC
mdefine_line|#define ISDN_NET_ENCAP_UIHDLC     5
DECL|macro|ISDN_NET_ENCAP_CISCOHDLCK
mdefine_line|#define ISDN_NET_ENCAP_CISCOHDLCK 6 /* With SLARP and keepalive    */
DECL|macro|ISDN_NET_ENCAP_X25IFACE
mdefine_line|#define ISDN_NET_ENCAP_X25IFACE   7 /* Documentation/networking/x25-iface.txt*/
DECL|macro|ISDN_NET_ENCAP_MAX_ENCAP
mdefine_line|#define ISDN_NET_ENCAP_MAX_ENCAP  ISDN_NET_ENCAP_X25IFACE
multiline_comment|/* Facility which currently uses an ISDN-channel */
DECL|macro|ISDN_USAGE_NONE
mdefine_line|#define ISDN_USAGE_NONE       0
DECL|macro|ISDN_USAGE_RAW
mdefine_line|#define ISDN_USAGE_RAW        1
DECL|macro|ISDN_USAGE_MODEM
mdefine_line|#define ISDN_USAGE_MODEM      2
DECL|macro|ISDN_USAGE_NET
mdefine_line|#define ISDN_USAGE_NET        3
DECL|macro|ISDN_USAGE_VOICE
mdefine_line|#define ISDN_USAGE_VOICE      4
DECL|macro|ISDN_USAGE_FAX
mdefine_line|#define ISDN_USAGE_FAX        5
DECL|macro|ISDN_USAGE_MASK
mdefine_line|#define ISDN_USAGE_MASK       7 /* Mask to get plain usage */
DECL|macro|ISDN_USAGE_DISABLED
mdefine_line|#define ISDN_USAGE_DISABLED  32 /* This bit is set, if channel is disabled */
DECL|macro|ISDN_USAGE_EXCLUSIVE
mdefine_line|#define ISDN_USAGE_EXCLUSIVE 64 /* This bit is set, if channel is exclusive */
DECL|macro|ISDN_USAGE_OUTGOING
mdefine_line|#define ISDN_USAGE_OUTGOING 128 /* This bit is set, if channel is outgoing  */
DECL|macro|ISDN_MODEM_NUMREG
mdefine_line|#define ISDN_MODEM_NUMREG    24        /* Number of Modem-Registers        */
DECL|macro|ISDN_LMSNLEN
mdefine_line|#define ISDN_LMSNLEN         255 /* Length of tty&squot;s Listen-MSN string */
DECL|macro|ISDN_CMSGLEN
mdefine_line|#define ISDN_CMSGLEN&t;     50&t; /* Length of CONNECT-Message to add for Modem */
DECL|macro|ISDN_MSNLEN
mdefine_line|#define ISDN_MSNLEN          32
DECL|macro|NET_DV
mdefine_line|#define NET_DV 0x06  /* Data version for isdn_net_ioctl_cfg   */
DECL|macro|TTY_DV
mdefine_line|#define TTY_DV 0x06  /* Data version for iprofd etc.          */
DECL|macro|INF_DV
mdefine_line|#define INF_DV 0x01  /* Data version for /dev/isdninfo        */
r_typedef
r_struct
(brace
DECL|member|drvid
r_char
id|drvid
(braket
l_int|25
)braket
suffix:semicolon
DECL|member|arg
r_int
r_int
id|arg
suffix:semicolon
DECL|typedef|isdn_ioctl_struct
)brace
id|isdn_ioctl_struct
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|name
r_char
id|name
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|phone
r_char
id|phone
(braket
id|ISDN_MSNLEN
)braket
suffix:semicolon
DECL|member|outgoing
r_int
id|outgoing
suffix:semicolon
DECL|typedef|isdn_net_ioctl_phone
)brace
id|isdn_net_ioctl_phone
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|name
r_char
id|name
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* Name of interface                     */
DECL|member|master
r_char
id|master
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* Name of Master for Bundling           */
DECL|member|slave
r_char
id|slave
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* Name of Slave for Bundling            */
DECL|member|eaz
r_char
id|eaz
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* EAZ/MSN                               */
DECL|member|drvid
r_char
id|drvid
(braket
l_int|25
)braket
suffix:semicolon
multiline_comment|/* DriverId for Bindings                 */
DECL|member|onhtime
r_int
id|onhtime
suffix:semicolon
multiline_comment|/* Hangup-Timeout                        */
DECL|member|charge
r_int
id|charge
suffix:semicolon
multiline_comment|/* Charge-Units                          */
DECL|member|l2_proto
r_int
id|l2_proto
suffix:semicolon
multiline_comment|/* Layer-2 protocol                      */
DECL|member|l3_proto
r_int
id|l3_proto
suffix:semicolon
multiline_comment|/* Layer-3 protocol                      */
DECL|member|p_encap
r_int
id|p_encap
suffix:semicolon
multiline_comment|/* Encapsulation                         */
DECL|member|exclusive
r_int
id|exclusive
suffix:semicolon
multiline_comment|/* Channel, if bound exclusive           */
DECL|member|dialmax
r_int
id|dialmax
suffix:semicolon
multiline_comment|/* Dial Retry-Counter                    */
DECL|member|slavedelay
r_int
id|slavedelay
suffix:semicolon
multiline_comment|/* Delay until slave starts up           */
DECL|member|cbdelay
r_int
id|cbdelay
suffix:semicolon
multiline_comment|/* Delay before Callback                 */
DECL|member|chargehup
r_int
id|chargehup
suffix:semicolon
multiline_comment|/* Flag: Charge-Hangup                   */
DECL|member|ihup
r_int
id|ihup
suffix:semicolon
multiline_comment|/* Flag: Hangup-Timeout on incoming line */
DECL|member|secure
r_int
id|secure
suffix:semicolon
multiline_comment|/* Flag: Secure                          */
DECL|member|callback
r_int
id|callback
suffix:semicolon
multiline_comment|/* Flag: Callback                        */
DECL|member|cbhup
r_int
id|cbhup
suffix:semicolon
multiline_comment|/* Flag: Reject Call before Callback     */
DECL|member|pppbind
r_int
id|pppbind
suffix:semicolon
multiline_comment|/* ippp device for bindings              */
DECL|member|chargeint
r_int
id|chargeint
suffix:semicolon
multiline_comment|/* Use fixed charge interval length      */
DECL|member|triggercps
r_int
id|triggercps
suffix:semicolon
multiline_comment|/* BogoCPS needed for triggering slave   */
DECL|member|dialtimeout
r_int
id|dialtimeout
suffix:semicolon
multiline_comment|/* Dial-Timeout                          */
DECL|member|dialwait
r_int
id|dialwait
suffix:semicolon
multiline_comment|/* Time to wait after failed dial        */
DECL|member|dialmode
r_int
id|dialmode
suffix:semicolon
multiline_comment|/* Flag: off / on / auto                 */
DECL|typedef|isdn_net_ioctl_cfg
)brace
id|isdn_net_ioctl_cfg
suffix:semicolon
DECL|macro|ISDN_NET_DIALMODE_MASK
mdefine_line|#define ISDN_NET_DIALMODE_MASK  0xC0    /* bits for status                */
DECL|macro|ISDN_NET_DM_OFF
mdefine_line|#define ISDN_NET_DM_OFF&t;        0x00    /* this interface is stopped      */
DECL|macro|ISDN_NET_DM_MANUAL
mdefine_line|#define ISDN_NET_DM_MANUAL&t;0x40    /* this interface is on (manual)  */
DECL|macro|ISDN_NET_DM_AUTO
mdefine_line|#define ISDN_NET_DM_AUTO&t;0x80    /* this interface is autodial     */
DECL|macro|ISDN_NET_DIALMODE
mdefine_line|#define ISDN_NET_DIALMODE(x) ((&amp;(x))-&gt;flags &amp; ISDN_NET_DIALMODE_MASK)
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/tty_flip.h&gt;
macro_line|#include &lt;linux/serial_reg.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
DECL|macro|ISDN_TTY_MAJOR
mdefine_line|#define ISDN_TTY_MAJOR    43
DECL|macro|ISDN_TTYAUX_MAJOR
mdefine_line|#define ISDN_TTYAUX_MAJOR 44
DECL|macro|ISDN_MAJOR
mdefine_line|#define ISDN_MAJOR        45
multiline_comment|/* The minor-devicenumbers for Channel 0 and 1 are used as arguments for&n; * physical Channel-Mapping, so they MUST NOT be changed without changing&n; * the correspondent code in isdn.c&n; */
DECL|macro|ISDN_MINOR_B
mdefine_line|#define ISDN_MINOR_B        0
DECL|macro|ISDN_MINOR_BMAX
mdefine_line|#define ISDN_MINOR_BMAX     (ISDN_MAX_CHANNELS-1)
DECL|macro|ISDN_MINOR_CTRL
mdefine_line|#define ISDN_MINOR_CTRL     64
DECL|macro|ISDN_MINOR_CTRLMAX
mdefine_line|#define ISDN_MINOR_CTRLMAX  (64 + (ISDN_MAX_CHANNELS-1))
DECL|macro|ISDN_MINOR_PPP
mdefine_line|#define ISDN_MINOR_PPP      128
DECL|macro|ISDN_MINOR_PPPMAX
mdefine_line|#define ISDN_MINOR_PPPMAX   (128 + (ISDN_MAX_CHANNELS-1))
DECL|macro|ISDN_MINOR_STATUS
mdefine_line|#define ISDN_MINOR_STATUS   255
macro_line|#ifdef CONFIG_ISDN_PPP
macro_line|#ifdef CONFIG_ISDN_PPP_VJ
macro_line|#  include &lt;net/slhc_vj.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/ppp_defs.h&gt;
macro_line|#include &lt;linux/if_ppp.h&gt;
macro_line|#include &lt;linux/if_pppvar.h&gt;
macro_line|#include &lt;linux/isdn_ppp.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_ISDN_X25
macro_line|#  include &lt;linux/concap.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_DEVFS_FS
macro_line|#  include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/isdnif.h&gt;
DECL|macro|ISDN_DRVIOCTL_MASK
mdefine_line|#define ISDN_DRVIOCTL_MASK       0x7f  /* Mask for Device-ioctl */
multiline_comment|/* Until now unused */
DECL|macro|ISDN_SERVICE_VOICE
mdefine_line|#define ISDN_SERVICE_VOICE 1
DECL|macro|ISDN_SERVICE_AB
mdefine_line|#define ISDN_SERVICE_AB    1&lt;&lt;1 
DECL|macro|ISDN_SERVICE_X21
mdefine_line|#define ISDN_SERVICE_X21   1&lt;&lt;2
DECL|macro|ISDN_SERVICE_G4
mdefine_line|#define ISDN_SERVICE_G4    1&lt;&lt;3
DECL|macro|ISDN_SERVICE_BTX
mdefine_line|#define ISDN_SERVICE_BTX   1&lt;&lt;4
DECL|macro|ISDN_SERVICE_DFUE
mdefine_line|#define ISDN_SERVICE_DFUE  1&lt;&lt;5
DECL|macro|ISDN_SERVICE_X25
mdefine_line|#define ISDN_SERVICE_X25   1&lt;&lt;6
DECL|macro|ISDN_SERVICE_TTX
mdefine_line|#define ISDN_SERVICE_TTX   1&lt;&lt;7
DECL|macro|ISDN_SERVICE_MIXED
mdefine_line|#define ISDN_SERVICE_MIXED 1&lt;&lt;8
DECL|macro|ISDN_SERVICE_FW
mdefine_line|#define ISDN_SERVICE_FW    1&lt;&lt;9
DECL|macro|ISDN_SERVICE_GTEL
mdefine_line|#define ISDN_SERVICE_GTEL  1&lt;&lt;10
DECL|macro|ISDN_SERVICE_BTXN
mdefine_line|#define ISDN_SERVICE_BTXN  1&lt;&lt;11
DECL|macro|ISDN_SERVICE_BTEL
mdefine_line|#define ISDN_SERVICE_BTEL  1&lt;&lt;12
multiline_comment|/* Macros checking plain usage */
DECL|macro|USG_NONE
mdefine_line|#define USG_NONE(x)         ((x &amp; ISDN_USAGE_MASK)==ISDN_USAGE_NONE)
DECL|macro|USG_RAW
mdefine_line|#define USG_RAW(x)          ((x &amp; ISDN_USAGE_MASK)==ISDN_USAGE_RAW)
DECL|macro|USG_MODEM
mdefine_line|#define USG_MODEM(x)        ((x &amp; ISDN_USAGE_MASK)==ISDN_USAGE_MODEM)
DECL|macro|USG_VOICE
mdefine_line|#define USG_VOICE(x)        ((x &amp; ISDN_USAGE_MASK)==ISDN_USAGE_VOICE)
DECL|macro|USG_NET
mdefine_line|#define USG_NET(x)          ((x &amp; ISDN_USAGE_MASK)==ISDN_USAGE_NET)
DECL|macro|USG_FAX
mdefine_line|#define USG_FAX(x)          ((x &amp; ISDN_USAGE_MASK)==ISDN_USAGE_FAX)
DECL|macro|USG_OUTGOING
mdefine_line|#define USG_OUTGOING(x)     ((x &amp; ISDN_USAGE_OUTGOING)==ISDN_USAGE_OUTGOING)
DECL|macro|USG_MODEMORVOICE
mdefine_line|#define USG_MODEMORVOICE(x) (((x &amp; ISDN_USAGE_MASK)==ISDN_USAGE_MODEM) || &bslash;&n;                             ((x &amp; ISDN_USAGE_MASK)==ISDN_USAGE_VOICE)     )
multiline_comment|/* Timer-delays and scheduling-flags */
DECL|macro|ISDN_TIMER_RES
mdefine_line|#define ISDN_TIMER_RES         4                         /* Main Timer-Resolution   */
DECL|macro|ISDN_TIMER_02SEC
mdefine_line|#define ISDN_TIMER_02SEC       (HZ/ISDN_TIMER_RES/5)     /* Slow-Timer1 .2 sec      */
DECL|macro|ISDN_TIMER_1SEC
mdefine_line|#define ISDN_TIMER_1SEC        (HZ/ISDN_TIMER_RES)       /* Slow-Timer2 1 sec       */
DECL|macro|ISDN_TIMER_RINGING
mdefine_line|#define ISDN_TIMER_RINGING     5 /* tty RINGs = ISDN_TIMER_1SEC * this factor       */
DECL|macro|ISDN_TIMER_KEEPINT
mdefine_line|#define ISDN_TIMER_KEEPINT    10 /* Cisco-Keepalive = ISDN_TIMER_1SEC * this factor */
DECL|macro|ISDN_TIMER_MODEMREAD
mdefine_line|#define ISDN_TIMER_MODEMREAD   1
DECL|macro|ISDN_TIMER_MODEMPLUS
mdefine_line|#define ISDN_TIMER_MODEMPLUS   2
DECL|macro|ISDN_TIMER_MODEMRING
mdefine_line|#define ISDN_TIMER_MODEMRING   4
DECL|macro|ISDN_TIMER_MODEMXMIT
mdefine_line|#define ISDN_TIMER_MODEMXMIT   8
DECL|macro|ISDN_TIMER_NETDIAL
mdefine_line|#define ISDN_TIMER_NETDIAL    16 
DECL|macro|ISDN_TIMER_NETHANGUP
mdefine_line|#define ISDN_TIMER_NETHANGUP  32
DECL|macro|ISDN_TIMER_CARRIER
mdefine_line|#define ISDN_TIMER_CARRIER   256 /* Wait for Carrier */
DECL|macro|ISDN_TIMER_FAST
mdefine_line|#define ISDN_TIMER_FAST      (ISDN_TIMER_MODEMREAD | ISDN_TIMER_MODEMPLUS | &bslash;&n;                              ISDN_TIMER_MODEMXMIT)
DECL|macro|ISDN_TIMER_SLOW
mdefine_line|#define ISDN_TIMER_SLOW      (ISDN_TIMER_MODEMRING | ISDN_TIMER_NETHANGUP | &bslash;&n;                              ISDN_TIMER_NETDIAL | ISDN_TIMER_CARRIER)
multiline_comment|/* Timeout-Values for isdn_net_dial() */
DECL|macro|ISDN_TIMER_DTIMEOUT10
mdefine_line|#define ISDN_TIMER_DTIMEOUT10 (10*HZ/(ISDN_TIMER_02SEC*(ISDN_TIMER_RES+1)))
DECL|macro|ISDN_TIMER_DTIMEOUT15
mdefine_line|#define ISDN_TIMER_DTIMEOUT15 (15*HZ/(ISDN_TIMER_02SEC*(ISDN_TIMER_RES+1)))
DECL|macro|ISDN_TIMER_DTIMEOUT60
mdefine_line|#define ISDN_TIMER_DTIMEOUT60 (60*HZ/(ISDN_TIMER_02SEC*(ISDN_TIMER_RES+1)))
multiline_comment|/* GLOBAL_FLAGS */
DECL|macro|ISDN_GLOBAL_STOPPED
mdefine_line|#define ISDN_GLOBAL_STOPPED 1
multiline_comment|/*=================== Start of ip-over-ISDN stuff =========================*/
multiline_comment|/* Feature- and status-flags for a net-interface */
DECL|macro|ISDN_NET_CONNECTED
mdefine_line|#define ISDN_NET_CONNECTED  0x01       /* Bound to ISDN-Channel             */
DECL|macro|ISDN_NET_SECURE
mdefine_line|#define ISDN_NET_SECURE     0x02       /* Accept calls from phonelist only  */
DECL|macro|ISDN_NET_CALLBACK
mdefine_line|#define ISDN_NET_CALLBACK   0x04       /* activate callback                 */
DECL|macro|ISDN_NET_CBHUP
mdefine_line|#define ISDN_NET_CBHUP      0x08       /* hangup before callback            */
DECL|macro|ISDN_NET_CBOUT
mdefine_line|#define ISDN_NET_CBOUT      0x10       /* remote machine does callback      */
DECL|macro|ISDN_NET_MAGIC
mdefine_line|#define ISDN_NET_MAGIC      0x49344C02 /* for paranoia-checking             */
multiline_comment|/* Phone-list-element */
r_typedef
r_struct
(brace
DECL|member|next
r_void
op_star
id|next
suffix:semicolon
DECL|member|num
r_char
id|num
(braket
id|ISDN_MSNLEN
)braket
suffix:semicolon
DECL|typedef|isdn_net_phone
)brace
id|isdn_net_phone
suffix:semicolon
multiline_comment|/*&n;   Principles when extending structures for generic encapsulation protocol&n;   (&quot;concap&quot;) support:&n;   - Stuff which is hardware specific (here i4l-specific) goes in &n;     the netdev -&gt; local structure (here: isdn_net_local)&n;   - Stuff which is encapsulation protocol specific goes in the structure&n;     which holds the linux device structure (here: isdn_net_device)&n;*/
multiline_comment|/* Local interface-data */
DECL|struct|isdn_net_local_s
r_typedef
r_struct
id|isdn_net_local_s
(brace
DECL|member|magic
id|ulong
id|magic
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* Name of device                   */
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
multiline_comment|/* Ethernet Statistics              */
DECL|member|isdn_device
r_int
id|isdn_device
suffix:semicolon
multiline_comment|/* Index to isdn-device             */
DECL|member|isdn_channel
r_int
id|isdn_channel
suffix:semicolon
multiline_comment|/* Index to isdn-channel            */
DECL|member|ppp_slot
r_int
id|ppp_slot
suffix:semicolon
multiline_comment|/* PPPD device slot number          */
DECL|member|pre_device
r_int
id|pre_device
suffix:semicolon
multiline_comment|/* Preselected isdn-device          */
DECL|member|pre_channel
r_int
id|pre_channel
suffix:semicolon
multiline_comment|/* Preselected isdn-channel         */
DECL|member|exclusive
r_int
id|exclusive
suffix:semicolon
multiline_comment|/* If non-zero idx to reserved chan.*/
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* Connection-flags                 */
DECL|member|dialretry
r_int
id|dialretry
suffix:semicolon
multiline_comment|/* Counter for Dialout-retries      */
DECL|member|dialmax
r_int
id|dialmax
suffix:semicolon
multiline_comment|/* Max. Number of Dial-retries      */
DECL|member|cbdelay
r_int
id|cbdelay
suffix:semicolon
multiline_comment|/* Delay before Callback starts     */
DECL|member|dtimer
r_int
id|dtimer
suffix:semicolon
multiline_comment|/* Timeout-counter for dialing      */
DECL|member|msn
r_char
id|msn
(braket
id|ISDN_MSNLEN
)braket
suffix:semicolon
multiline_comment|/* MSNs/EAZs for this interface */
DECL|member|cbhup
id|u_char
id|cbhup
suffix:semicolon
multiline_comment|/* Flag: Reject Call before Callback*/
DECL|member|dialstate
id|u_char
id|dialstate
suffix:semicolon
multiline_comment|/* State for dialing                */
DECL|member|p_encap
id|u_char
id|p_encap
suffix:semicolon
multiline_comment|/* Packet encapsulation             */
multiline_comment|/*   0 = Ethernet over ISDN         */
multiline_comment|/*   1 = RAW-IP                     */
multiline_comment|/*   2 = IP with type field         */
DECL|member|l2_proto
id|u_char
id|l2_proto
suffix:semicolon
multiline_comment|/* Layer-2-protocol                 */
multiline_comment|/* See ISDN_PROTO_L2..-constants in */
multiline_comment|/* isdnif.h                         */
multiline_comment|/*   0 = X75/LAPB with I-Frames     */
multiline_comment|/*   1 = X75/LAPB with UI-Frames    */
multiline_comment|/*   2 = X75/LAPB with BUI-Frames   */
multiline_comment|/*   3 = HDLC                       */
DECL|member|l3_proto
id|u_char
id|l3_proto
suffix:semicolon
multiline_comment|/* Layer-3-protocol                 */
multiline_comment|/* See ISDN_PROTO_L3..-constants in */
multiline_comment|/* isdnif.h                         */
multiline_comment|/*   0 = Transparent                */
DECL|member|huptimer
r_int
id|huptimer
suffix:semicolon
multiline_comment|/* Timeout-counter for auto-hangup  */
DECL|member|charge
r_int
id|charge
suffix:semicolon
multiline_comment|/* Counter for charging units       */
DECL|member|chargetime
id|ulong
id|chargetime
suffix:semicolon
multiline_comment|/* Timer for Charging info          */
DECL|member|hupflags
r_int
id|hupflags
suffix:semicolon
multiline_comment|/* Flags for charge-unit-hangup:    */
multiline_comment|/* bit0: chargeint is invalid       */
multiline_comment|/* bit1: Getting charge-interval    */
multiline_comment|/* bit2: Do charge-unit-hangup      */
multiline_comment|/* bit3: Do hangup even on incoming */
DECL|member|outgoing
r_int
id|outgoing
suffix:semicolon
multiline_comment|/* Flag: outgoing call              */
DECL|member|onhtime
r_int
id|onhtime
suffix:semicolon
multiline_comment|/* Time to keep link up             */
DECL|member|chargeint
r_int
id|chargeint
suffix:semicolon
multiline_comment|/* Interval between charge-infos    */
DECL|member|onum
r_int
id|onum
suffix:semicolon
multiline_comment|/* Flag: at least 1 outgoing number */
DECL|member|cps
r_int
id|cps
suffix:semicolon
multiline_comment|/* current speed of this interface  */
DECL|member|transcount
r_int
id|transcount
suffix:semicolon
multiline_comment|/* byte-counter for cps-calculation */
DECL|member|sqfull
r_int
id|sqfull
suffix:semicolon
multiline_comment|/* Flag: netdev-queue overloaded    */
DECL|member|sqfull_stamp
id|ulong
id|sqfull_stamp
suffix:semicolon
multiline_comment|/* Start-Time of overload           */
DECL|member|slavedelay
id|ulong
id|slavedelay
suffix:semicolon
multiline_comment|/* Dynamic bundling delaytime       */
DECL|member|triggercps
r_int
id|triggercps
suffix:semicolon
multiline_comment|/* BogoCPS needed for trigger slave */
DECL|member|phone
id|isdn_net_phone
op_star
id|phone
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* List of remote-phonenumbers      */
multiline_comment|/* phone[0] = Incoming Numbers      */
multiline_comment|/* phone[1] = Outgoing Numbers      */
DECL|member|dial
id|isdn_net_phone
op_star
id|dial
suffix:semicolon
multiline_comment|/* Pointer to dialed number         */
DECL|member|master
r_struct
id|net_device
op_star
id|master
suffix:semicolon
multiline_comment|/* Ptr to Master device for slaves  */
DECL|member|slave
r_struct
id|net_device
op_star
id|slave
suffix:semicolon
multiline_comment|/* Ptr to Slave device for masters  */
DECL|member|next
r_struct
id|isdn_net_local_s
op_star
id|next
suffix:semicolon
multiline_comment|/* Ptr to next link in bundle       */
DECL|member|last
r_struct
id|isdn_net_local_s
op_star
id|last
suffix:semicolon
multiline_comment|/* Ptr to last link in bundle       */
DECL|member|netdev
r_struct
id|isdn_net_dev_s
op_star
id|netdev
suffix:semicolon
multiline_comment|/* Ptr to netdev                    */
DECL|member|super_tx_queue
r_struct
id|sk_buff_head
id|super_tx_queue
suffix:semicolon
multiline_comment|/* List of supervisory frames to  */
multiline_comment|/* be transmitted asap              */
DECL|member|frame_cnt
id|atomic_t
id|frame_cnt
suffix:semicolon
multiline_comment|/* number of frames currently       */
multiline_comment|/* queued in HL driver              */
multiline_comment|/* Ptr to orig. hard_header_cache   */
DECL|member|xmit_lock
id|spinlock_t
id|xmit_lock
suffix:semicolon
multiline_comment|/* used to protect the xmit path of */
multiline_comment|/* a particular channel (including  */
multiline_comment|/* the frame_cnt                    */
DECL|member|org_hhc
r_int
(paren
op_star
id|org_hhc
)paren
(paren
r_struct
id|neighbour
op_star
id|neigh
comma
r_struct
id|hh_cache
op_star
id|hh
)paren
suffix:semicolon
multiline_comment|/* Ptr to orig. header_cache_update */
DECL|member|org_hcu
r_void
(paren
op_star
id|org_hcu
)paren
(paren
r_struct
id|hh_cache
op_star
comma
r_struct
id|net_device
op_star
comma
r_int
r_char
op_star
)paren
suffix:semicolon
DECL|member|pppbind
r_int
id|pppbind
suffix:semicolon
multiline_comment|/* ippp device for bindings         */
DECL|member|dialtimeout
r_int
id|dialtimeout
suffix:semicolon
multiline_comment|/* How long shall we try on dialing? (jiffies) */
DECL|member|dialwait
r_int
id|dialwait
suffix:semicolon
multiline_comment|/* How long shall we wait after failed attempt? (jiffies) */
DECL|member|dialstarted
id|ulong
id|dialstarted
suffix:semicolon
multiline_comment|/* jiffies of first dialing-attempt */
DECL|member|dialwait_timer
id|ulong
id|dialwait_timer
suffix:semicolon
multiline_comment|/* jiffies of earliest next dialing-attempt */
DECL|member|huptimeout
r_int
id|huptimeout
suffix:semicolon
multiline_comment|/* How long will the connection be up? (seconds) */
macro_line|#ifdef CONFIG_ISDN_X25
DECL|member|dops
r_struct
id|concap_device_ops
op_star
id|dops
suffix:semicolon
multiline_comment|/* callbacks used by encapsulator   */
macro_line|#endif
multiline_comment|/* use an own struct for that in later versions */
DECL|member|cisco_myseq
id|ulong
id|cisco_myseq
suffix:semicolon
multiline_comment|/* Local keepalive seq. for Cisco   */
DECL|member|cisco_mineseen
id|ulong
id|cisco_mineseen
suffix:semicolon
multiline_comment|/* returned keepalive seq. from remote */
DECL|member|cisco_yourseq
id|ulong
id|cisco_yourseq
suffix:semicolon
multiline_comment|/* Remote keepalive seq. for Cisco  */
DECL|member|cisco_keepalive_period
r_int
id|cisco_keepalive_period
suffix:semicolon
multiline_comment|/* keepalive period */
DECL|member|cisco_last_slarp_in
id|ulong
id|cisco_last_slarp_in
suffix:semicolon
multiline_comment|/* jiffie of last keepalive packet we received */
DECL|member|cisco_line_state
r_char
id|cisco_line_state
suffix:semicolon
multiline_comment|/* state of line according to keepalive packets */
DECL|member|cisco_debserint
r_char
id|cisco_debserint
suffix:semicolon
multiline_comment|/* debugging flag of cisco hdlc with slarp */
DECL|member|cisco_timer
r_struct
id|timer_list
id|cisco_timer
suffix:semicolon
DECL|member|tqueue
r_struct
id|tq_struct
id|tqueue
suffix:semicolon
DECL|typedef|isdn_net_local
)brace
id|isdn_net_local
suffix:semicolon
multiline_comment|/* the interface itself */
DECL|struct|isdn_net_dev_s
r_typedef
r_struct
id|isdn_net_dev_s
(brace
DECL|member|local
id|isdn_net_local
op_star
id|local
suffix:semicolon
DECL|member|queue
id|isdn_net_local
op_star
id|queue
suffix:semicolon
multiline_comment|/* circular list of all bundled&n;&t;&t;&t;&t;&t;  channels, which are currently&n;&t;&t;&t;&t;&t;  online                           */
DECL|member|queue_lock
id|spinlock_t
id|queue_lock
suffix:semicolon
multiline_comment|/* lock to protect queue            */
DECL|member|next
r_void
op_star
id|next
suffix:semicolon
multiline_comment|/* Pointer to next isdn-interface   */
DECL|member|dev
r_struct
id|net_device
id|dev
suffix:semicolon
multiline_comment|/* interface to upper levels        */
macro_line|#ifdef CONFIG_ISDN_PPP
DECL|member|pb
id|ippp_bundle
op_star
id|pb
suffix:semicolon
multiline_comment|/* pointer to the common bundle structure&n;   &t;&t;&t;         * with the per-bundle data */
macro_line|#endif
macro_line|#ifdef CONFIG_ISDN_X25
DECL|member|cprot
r_struct
id|concap_proto
op_star
id|cprot
suffix:semicolon
multiline_comment|/* connection oriented encapsulation protocol */
macro_line|#endif
DECL|typedef|isdn_net_dev
)brace
id|isdn_net_dev
suffix:semicolon
multiline_comment|/*===================== End of ip-over-ISDN stuff ===========================*/
multiline_comment|/*======================= Start of ISDN-tty stuff ===========================*/
DECL|macro|ISDN_ASYNC_MAGIC
mdefine_line|#define ISDN_ASYNC_MAGIC          0x49344C01 /* for paranoia-checking        */
DECL|macro|ISDN_ASYNC_INITIALIZED
mdefine_line|#define ISDN_ASYNC_INITIALIZED&t;  0x80000000 /* port was initialized         */
DECL|macro|ISDN_ASYNC_CALLOUT_ACTIVE
mdefine_line|#define ISDN_ASYNC_CALLOUT_ACTIVE 0x40000000 /* Call out device active       */
DECL|macro|ISDN_ASYNC_NORMAL_ACTIVE
mdefine_line|#define ISDN_ASYNC_NORMAL_ACTIVE  0x20000000 /* Normal device active         */
DECL|macro|ISDN_ASYNC_CLOSING
mdefine_line|#define ISDN_ASYNC_CLOSING&t;  0x08000000 /* Serial port is closing       */
DECL|macro|ISDN_ASYNC_CTS_FLOW
mdefine_line|#define ISDN_ASYNC_CTS_FLOW&t;  0x04000000 /* Do CTS flow control          */
DECL|macro|ISDN_ASYNC_CHECK_CD
mdefine_line|#define ISDN_ASYNC_CHECK_CD&t;  0x02000000 /* i.e., CLOCAL                 */
DECL|macro|ISDN_ASYNC_HUP_NOTIFY
mdefine_line|#define ISDN_ASYNC_HUP_NOTIFY         0x0001 /* Notify tty on hangups/closes */
DECL|macro|ISDN_ASYNC_SESSION_LOCKOUT
mdefine_line|#define ISDN_ASYNC_SESSION_LOCKOUT    0x0100 /* Lock cua opens on session    */
DECL|macro|ISDN_ASYNC_PGRP_LOCKOUT
mdefine_line|#define ISDN_ASYNC_PGRP_LOCKOUT       0x0200 /* Lock cua opens on pgrp       */
DECL|macro|ISDN_ASYNC_CALLOUT_NOHUP
mdefine_line|#define ISDN_ASYNC_CALLOUT_NOHUP      0x0400 /* No hangup for cui            */
DECL|macro|ISDN_ASYNC_SPLIT_TERMIOS
mdefine_line|#define ISDN_ASYNC_SPLIT_TERMIOS      0x0008 /* Sep. termios for dialin/out  */
DECL|macro|ISDN_SERIAL_XMIT_SIZE
mdefine_line|#define ISDN_SERIAL_XMIT_SIZE           1024 /* Default bufsize for write    */
DECL|macro|ISDN_SERIAL_XMIT_MAX
mdefine_line|#define ISDN_SERIAL_XMIT_MAX            4000 /* Maximum bufsize for write    */
DECL|macro|ISDN_SERIAL_TYPE_NORMAL
mdefine_line|#define ISDN_SERIAL_TYPE_NORMAL            1
DECL|macro|ISDN_SERIAL_TYPE_CALLOUT
mdefine_line|#define ISDN_SERIAL_TYPE_CALLOUT           2
macro_line|#ifdef CONFIG_ISDN_AUDIO
multiline_comment|/* For using sk_buffs with audio we need some private variables&n; * within each sk_buff. For this purpose, we declare a struct here,&n; * and put it always at skb-&gt;head. A few macros help accessing the&n; * variables. Of course, we need to check skb_headroom prior to&n; * any access.&n; */
DECL|struct|isdn_audio_skb
r_typedef
r_struct
id|isdn_audio_skb
(brace
DECL|member|dle_count
r_int
r_int
id|dle_count
suffix:semicolon
DECL|member|lock
r_int
r_char
id|lock
suffix:semicolon
DECL|typedef|isdn_audio_skb
)brace
id|isdn_audio_skb
suffix:semicolon
DECL|macro|ISDN_AUDIO_SKB_DLECOUNT
mdefine_line|#define ISDN_AUDIO_SKB_DLECOUNT(skb) (((isdn_audio_skb*)skb-&gt;head)-&gt;dle_count)
DECL|macro|ISDN_AUDIO_SKB_LOCK
mdefine_line|#define ISDN_AUDIO_SKB_LOCK(skb) (((isdn_audio_skb*)skb-&gt;head)-&gt;lock)
macro_line|#endif
multiline_comment|/* Private data of AT-command-interpreter */
DECL|struct|atemu
r_typedef
r_struct
id|atemu
(brace
DECL|member|profile
id|u_char
id|profile
(braket
id|ISDN_MODEM_NUMREG
)braket
suffix:semicolon
multiline_comment|/* Modem-Regs. Profile 0              */
DECL|member|mdmreg
id|u_char
id|mdmreg
(braket
id|ISDN_MODEM_NUMREG
)braket
suffix:semicolon
multiline_comment|/* Modem-Registers                    */
DECL|member|pmsn
r_char
id|pmsn
(braket
id|ISDN_MSNLEN
)braket
suffix:semicolon
multiline_comment|/* EAZ/MSNs Profile 0                 */
DECL|member|msn
r_char
id|msn
(braket
id|ISDN_MSNLEN
)braket
suffix:semicolon
multiline_comment|/* EAZ/MSN                            */
DECL|member|plmsn
r_char
id|plmsn
(braket
id|ISDN_LMSNLEN
)braket
suffix:semicolon
multiline_comment|/* Listening MSNs Profile 0           */
DECL|member|lmsn
r_char
id|lmsn
(braket
id|ISDN_LMSNLEN
)braket
suffix:semicolon
multiline_comment|/* Listening MSNs                     */
DECL|member|cpn
r_char
id|cpn
(braket
id|ISDN_MSNLEN
)braket
suffix:semicolon
multiline_comment|/* CalledPartyNumber on incoming call */
DECL|member|connmsg
r_char
id|connmsg
(braket
id|ISDN_CMSGLEN
)braket
suffix:semicolon
multiline_comment|/* CONNECT-Msg from HL-Driver&t;       */
macro_line|#ifdef CONFIG_ISDN_AUDIO
DECL|member|vpar
id|u_char
id|vpar
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* Voice-parameters                   */
DECL|member|lastDLE
r_int
id|lastDLE
suffix:semicolon
multiline_comment|/* Flag for voice-coding: DLE seen    */
macro_line|#endif
DECL|member|mdmcmdl
r_int
id|mdmcmdl
suffix:semicolon
multiline_comment|/* Length of Modem-Commandbuffer      */
DECL|member|pluscount
r_int
id|pluscount
suffix:semicolon
multiline_comment|/* Counter for +++ sequence           */
DECL|member|lastplus
r_int
id|lastplus
suffix:semicolon
multiline_comment|/* Timestamp of last +                */
DECL|member|carrierwait
r_int
id|carrierwait
suffix:semicolon
multiline_comment|/* Seconds of carrier waiting         */
DECL|member|mdmcmd
r_char
id|mdmcmd
(braket
l_int|255
)braket
suffix:semicolon
multiline_comment|/* Modem-Commandbuffer                */
DECL|member|charge
r_int
r_int
id|charge
suffix:semicolon
multiline_comment|/* Charge units of current connection */
DECL|typedef|atemu
)brace
id|atemu
suffix:semicolon
multiline_comment|/* Private data (similar to async_struct in &lt;linux/serial.h&gt;) */
DECL|struct|modem_info
r_typedef
r_struct
id|modem_info
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* defined in tty.h               */
DECL|member|x_char
r_int
id|x_char
suffix:semicolon
multiline_comment|/* xon/xoff character             */
DECL|member|mcr
r_int
id|mcr
suffix:semicolon
multiline_comment|/* Modem control register         */
DECL|member|msr
r_int
id|msr
suffix:semicolon
multiline_comment|/* Modem status register          */
DECL|member|lsr
r_int
id|lsr
suffix:semicolon
multiline_comment|/* Line status register           */
DECL|member|line
r_int
id|line
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* # of fd on device              */
DECL|member|blocked_open
r_int
id|blocked_open
suffix:semicolon
multiline_comment|/* # of blocked opens             */
DECL|member|session
r_int
id|session
suffix:semicolon
multiline_comment|/* Session of opening process     */
DECL|member|pgrp
r_int
id|pgrp
suffix:semicolon
multiline_comment|/* pgrp of opening process        */
DECL|member|online
r_int
id|online
suffix:semicolon
multiline_comment|/* 1 = B-Channel is up, drop data */
multiline_comment|/* 2 = B-Channel is up, deliver d.*/
DECL|member|dialing
r_int
id|dialing
suffix:semicolon
multiline_comment|/* Dial in progress or ATA        */
DECL|member|rcvsched
r_int
id|rcvsched
suffix:semicolon
multiline_comment|/* Receive needs schedule         */
DECL|member|isdn_driver
r_int
id|isdn_driver
suffix:semicolon
multiline_comment|/* Index to isdn-driver           */
DECL|member|isdn_channel
r_int
id|isdn_channel
suffix:semicolon
multiline_comment|/* Index to isdn-channel          */
DECL|member|drv_index
r_int
id|drv_index
suffix:semicolon
multiline_comment|/* Index to dev-&gt;usage            */
DECL|member|ncarrier
r_int
id|ncarrier
suffix:semicolon
multiline_comment|/* Flag: schedule NO CARRIER      */
DECL|member|last_cause
r_int
r_char
id|last_cause
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Last cause message             */
DECL|member|last_num
r_int
r_char
id|last_num
(braket
id|ISDN_MSNLEN
)braket
suffix:semicolon
multiline_comment|/* Last phone-number              */
DECL|member|last_l2
r_int
r_char
id|last_l2
suffix:semicolon
multiline_comment|/* Last layer-2 protocol          */
DECL|member|last_si
r_int
r_char
id|last_si
suffix:semicolon
multiline_comment|/* Last service                   */
DECL|member|last_lhup
r_int
r_char
id|last_lhup
suffix:semicolon
multiline_comment|/* Last hangup local?             */
DECL|member|last_dir
r_int
r_char
id|last_dir
suffix:semicolon
multiline_comment|/* Last direction (in or out)     */
DECL|member|nc_timer
r_struct
id|timer_list
id|nc_timer
suffix:semicolon
multiline_comment|/* Timer for delayed NO CARRIER   */
DECL|member|send_outstanding
r_int
id|send_outstanding
suffix:semicolon
multiline_comment|/* # of outstanding send-requests */
DECL|member|xmit_size
r_int
id|xmit_size
suffix:semicolon
multiline_comment|/* max. # of chars in xmit_buf    */
DECL|member|xmit_count
r_int
id|xmit_count
suffix:semicolon
multiline_comment|/* # of chars in xmit_buf         */
DECL|member|xmit_buf
r_int
r_char
op_star
id|xmit_buf
suffix:semicolon
multiline_comment|/* transmit buffer                */
DECL|member|xmit_queue
r_struct
id|sk_buff_head
id|xmit_queue
suffix:semicolon
multiline_comment|/* transmit queue                 */
DECL|member|xmit_lock
id|atomic_t
id|xmit_lock
suffix:semicolon
multiline_comment|/* Semaphore for isdn_tty_write   */
macro_line|#ifdef CONFIG_ISDN_AUDIO
DECL|member|vonline
r_int
id|vonline
suffix:semicolon
multiline_comment|/* Voice-channel status           */
multiline_comment|/* Bit 0 = recording              */
multiline_comment|/* Bit 1 = playback               */
multiline_comment|/* Bit 2 = playback, DLE-ETX seen */
DECL|member|dtmf_queue
r_struct
id|sk_buff_head
id|dtmf_queue
suffix:semicolon
multiline_comment|/* queue for dtmf results         */
DECL|member|adpcms
r_void
op_star
id|adpcms
suffix:semicolon
multiline_comment|/* state for adpcm decompression  */
DECL|member|adpcmr
r_void
op_star
id|adpcmr
suffix:semicolon
multiline_comment|/* state for adpcm compression    */
DECL|member|dtmf_state
r_void
op_star
id|dtmf_state
suffix:semicolon
multiline_comment|/* state for dtmf decoder         */
DECL|member|silence_state
r_void
op_star
id|silence_state
suffix:semicolon
multiline_comment|/* state for silence detection    */
macro_line|#endif
macro_line|#ifdef CONFIG_ISDN_TTY_FAX
DECL|member|fax
r_struct
id|T30_s
op_star
id|fax
suffix:semicolon
multiline_comment|/* T30 Fax Group 3 data/interface */
DECL|member|faxonline
r_int
id|faxonline
suffix:semicolon
multiline_comment|/* Fax-channel status             */
macro_line|#endif
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
multiline_comment|/* Pointer to corresponding tty   */
DECL|member|emu
id|atemu
id|emu
suffix:semicolon
multiline_comment|/* AT-emulator data               */
DECL|member|normal_termios
r_struct
id|termios
id|normal_termios
suffix:semicolon
multiline_comment|/* For saving termios structs     */
DECL|member|callout_termios
r_struct
id|termios
id|callout_termios
suffix:semicolon
DECL|member|open_wait
DECL|member|close_wait
id|wait_queue_head_t
id|open_wait
comma
id|close_wait
suffix:semicolon
DECL|member|write_sem
r_struct
id|semaphore
id|write_sem
suffix:semicolon
DECL|typedef|modem_info
)brace
id|modem_info
suffix:semicolon
DECL|macro|ISDN_MODEM_WINSIZE
mdefine_line|#define ISDN_MODEM_WINSIZE 8
multiline_comment|/* Description of one ISDN-tty */
r_typedef
r_struct
(brace
DECL|member|refcount
r_int
id|refcount
suffix:semicolon
multiline_comment|/* Number of opens        */
DECL|member|tty_modem
r_struct
id|tty_driver
id|tty_modem
suffix:semicolon
multiline_comment|/* tty-device             */
DECL|member|cua_modem
r_struct
id|tty_driver
id|cua_modem
suffix:semicolon
multiline_comment|/* cua-device             */
DECL|member|modem_table
r_struct
id|tty_struct
op_star
id|modem_table
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
multiline_comment|/* ?? copied from Orig */
DECL|member|modem_termios
r_struct
id|termios
op_star
id|modem_termios
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
DECL|member|modem_termios_locked
r_struct
id|termios
op_star
id|modem_termios_locked
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
DECL|member|info
id|modem_info
id|info
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
multiline_comment|/* Private data           */
DECL|typedef|modem
)brace
id|modem
suffix:semicolon
multiline_comment|/*======================= End of ISDN-tty stuff ============================*/
multiline_comment|/*======================== Start of V.110 stuff ============================*/
DECL|macro|V110_BUFSIZE
mdefine_line|#define V110_BUFSIZE 1024
r_typedef
r_struct
(brace
DECL|member|nbytes
r_int
id|nbytes
suffix:semicolon
multiline_comment|/* 1 Matrixbyte -&gt; nbytes in stream     */
DECL|member|nbits
r_int
id|nbits
suffix:semicolon
multiline_comment|/* Number of used bits in streambyte    */
DECL|member|key
r_int
r_char
id|key
suffix:semicolon
multiline_comment|/* Bitmask in stream eg. 11 (nbits=2)   */
DECL|member|decodelen
r_int
id|decodelen
suffix:semicolon
multiline_comment|/* Amount of data in decodebuf          */
DECL|member|SyncInit
r_int
id|SyncInit
suffix:semicolon
multiline_comment|/* Number of sync frames to send        */
DECL|member|OnlineFrame
r_int
r_char
op_star
id|OnlineFrame
suffix:semicolon
multiline_comment|/* Precalculated V110 idle frame        */
DECL|member|OfflineFrame
r_int
r_char
op_star
id|OfflineFrame
suffix:semicolon
multiline_comment|/* Precalculated V110 sync Frame        */
DECL|member|framelen
r_int
id|framelen
suffix:semicolon
multiline_comment|/* Length of frames                     */
DECL|member|skbuser
r_int
id|skbuser
suffix:semicolon
multiline_comment|/* Number of unacked userdata skbs      */
DECL|member|skbidle
r_int
id|skbidle
suffix:semicolon
multiline_comment|/* Number of unacked idle/sync skbs     */
DECL|member|introducer
r_int
id|introducer
suffix:semicolon
multiline_comment|/* Local vars for decoder               */
DECL|member|dbit
r_int
id|dbit
suffix:semicolon
DECL|member|b
r_int
r_char
id|b
suffix:semicolon
DECL|member|skbres
r_int
id|skbres
suffix:semicolon
multiline_comment|/* space to reserve in outgoing skb     */
DECL|member|maxsize
r_int
id|maxsize
suffix:semicolon
multiline_comment|/* maxbufsize of lowlevel driver        */
DECL|member|encodebuf
r_int
r_char
op_star
id|encodebuf
suffix:semicolon
multiline_comment|/* temporary buffer for encoding        */
DECL|member|decodebuf
r_int
r_char
id|decodebuf
(braket
id|V110_BUFSIZE
)braket
suffix:semicolon
multiline_comment|/* incomplete V110 matrices     */
DECL|typedef|isdn_v110_stream
)brace
id|isdn_v110_stream
suffix:semicolon
multiline_comment|/*========================= End of V.110 stuff =============================*/
multiline_comment|/*======================= Start of general stuff ===========================*/
r_typedef
r_struct
(brace
DECL|member|next
r_char
op_star
id|next
suffix:semicolon
DECL|member|private
r_char
op_star
r_private
suffix:semicolon
DECL|typedef|infostruct
)brace
id|infostruct
suffix:semicolon
DECL|macro|DRV_FLAG_RUNNING
mdefine_line|#define DRV_FLAG_RUNNING 1
DECL|macro|DRV_FLAG_REJBUS
mdefine_line|#define DRV_FLAG_REJBUS  2
DECL|macro|DRV_FLAG_LOADED
mdefine_line|#define DRV_FLAG_LOADED  4
multiline_comment|/* Description of hardware-level-driver */
r_typedef
r_struct
(brace
DECL|member|online
id|ulong
id|online
suffix:semicolon
multiline_comment|/* Channel-Online flags             */
DECL|member|flags
id|ulong
id|flags
suffix:semicolon
multiline_comment|/* Misc driver Flags                */
DECL|member|locks
r_int
id|locks
suffix:semicolon
multiline_comment|/* Number of locks for this driver  */
DECL|member|channels
r_int
id|channels
suffix:semicolon
multiline_comment|/* Number of channels               */
DECL|member|st_waitq
id|wait_queue_head_t
id|st_waitq
suffix:semicolon
multiline_comment|/* Wait-Queue for status-read&squot;s     */
DECL|member|maxbufsize
r_int
id|maxbufsize
suffix:semicolon
multiline_comment|/* Maximum Buffersize supported     */
DECL|member|pktcount
r_int
r_int
id|pktcount
suffix:semicolon
multiline_comment|/* Until now: unused                */
DECL|member|stavail
r_int
id|stavail
suffix:semicolon
multiline_comment|/* Chars avail on Status-device     */
DECL|member|interface
id|isdn_if
op_star
id|interface
suffix:semicolon
multiline_comment|/* Interface to driver              */
DECL|member|rcverr
r_int
op_star
id|rcverr
suffix:semicolon
multiline_comment|/* Error-counters for B-Ch.-receive */
DECL|member|rcvcount
r_int
op_star
id|rcvcount
suffix:semicolon
multiline_comment|/* Byte-counters for B-Ch.-receive  */
macro_line|#ifdef CONFIG_ISDN_AUDIO
DECL|member|DLEflag
r_int
r_int
id|DLEflag
suffix:semicolon
multiline_comment|/* Flags: Insert DLE at next read   */
macro_line|#endif
DECL|member|rpqueue
r_struct
id|sk_buff_head
op_star
id|rpqueue
suffix:semicolon
multiline_comment|/* Pointers to start of Rcv-Queue   */
DECL|member|rcv_waitq
id|wait_queue_head_t
op_star
id|rcv_waitq
suffix:semicolon
multiline_comment|/* Wait-Queues for B-Channel-Reads  */
DECL|member|snd_waitq
id|wait_queue_head_t
op_star
id|snd_waitq
suffix:semicolon
multiline_comment|/* Wait-Queue for B-Channel-Send&squot;s  */
DECL|member|msn2eaz
r_char
id|msn2eaz
(braket
l_int|10
)braket
(braket
id|ISDN_MSNLEN
)braket
suffix:semicolon
multiline_comment|/* Mapping-Table MSN-&gt;EAZ   */
DECL|typedef|driver
)brace
id|driver
suffix:semicolon
multiline_comment|/* Main driver-data */
DECL|struct|isdn_devt
r_typedef
r_struct
id|isdn_devt
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Bitmapped Flags:           */
multiline_comment|/*                            */
DECL|member|drivers
r_int
id|drivers
suffix:semicolon
multiline_comment|/* Current number of drivers  */
DECL|member|channels
r_int
id|channels
suffix:semicolon
multiline_comment|/* Current number of channels */
DECL|member|net_verbose
r_int
id|net_verbose
suffix:semicolon
multiline_comment|/* Verbose-Flag               */
DECL|member|modempoll
r_int
id|modempoll
suffix:semicolon
multiline_comment|/* Flag: tty-read active      */
DECL|member|tflags
r_int
id|tflags
suffix:semicolon
multiline_comment|/* Timer-Flags:               */
multiline_comment|/*  see ISDN_TIMER_..defines  */
DECL|member|global_flags
r_int
id|global_flags
suffix:semicolon
DECL|member|infochain
id|infostruct
op_star
id|infochain
suffix:semicolon
multiline_comment|/* List of open info-devs.    */
DECL|member|info_waitq
id|wait_queue_head_t
id|info_waitq
suffix:semicolon
multiline_comment|/* Wait-Queue for isdninfo    */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/* Misc.-function Timer       */
DECL|member|chanmap
r_int
id|chanmap
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
multiline_comment|/* Map minor-&gt;device-channel  */
DECL|member|drvmap
r_int
id|drvmap
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
multiline_comment|/* Map minor-&gt;driver-index    */
DECL|member|usage
r_int
id|usage
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
multiline_comment|/* Used by tty/ip/voice       */
DECL|member|num
r_char
id|num
(braket
id|ISDN_MAX_CHANNELS
)braket
(braket
id|ISDN_MSNLEN
)braket
suffix:semicolon
multiline_comment|/* Remote number of active ch.*/
DECL|member|m_idx
r_int
id|m_idx
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
multiline_comment|/* Index for mdm....          */
DECL|member|drv
id|driver
op_star
id|drv
(braket
id|ISDN_MAX_DRIVERS
)braket
suffix:semicolon
multiline_comment|/* Array of drivers           */
DECL|member|netdev
id|isdn_net_dev
op_star
id|netdev
suffix:semicolon
multiline_comment|/* Linked list of net-if&squot;s    */
DECL|member|drvid
r_char
id|drvid
(braket
id|ISDN_MAX_DRIVERS
)braket
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* Driver-ID                 */
DECL|member|profd
r_struct
id|task_struct
op_star
id|profd
suffix:semicolon
multiline_comment|/* For iprofd                 */
DECL|member|mdm
id|modem
id|mdm
suffix:semicolon
multiline_comment|/* tty-driver-data            */
DECL|member|rx_netdev
id|isdn_net_dev
op_star
id|rx_netdev
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
multiline_comment|/* rx netdev-pointers     */
DECL|member|st_netdev
id|isdn_net_dev
op_star
id|st_netdev
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
multiline_comment|/* stat netdev-pointers   */
DECL|member|ibytes
id|ulong
id|ibytes
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
multiline_comment|/* Statistics incoming bytes  */
DECL|member|obytes
id|ulong
id|obytes
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
multiline_comment|/* Statistics outgoing bytes  */
DECL|member|v110emu
r_int
id|v110emu
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
multiline_comment|/* V.110 emulator-mode 0=none */
DECL|member|v110use
id|atomic_t
id|v110use
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
multiline_comment|/* Usage-Semaphore for stream */
DECL|member|v110
id|isdn_v110_stream
op_star
id|v110
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
multiline_comment|/* V.110 private data         */
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
multiline_comment|/* serialize list access*/
DECL|member|global_features
r_int
r_int
id|global_features
suffix:semicolon
macro_line|#ifdef CONFIG_DEVFS_FS
DECL|member|devfs_handle_isdninfo
id|devfs_handle_t
id|devfs_handle_isdninfo
suffix:semicolon
DECL|member|devfs_handle_isdnctrl
id|devfs_handle_t
id|devfs_handle_isdnctrl
suffix:semicolon
DECL|member|devfs_handle_isdnX
id|devfs_handle_t
id|devfs_handle_isdnX
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
DECL|member|devfs_handle_isdnctrlX
id|devfs_handle_t
id|devfs_handle_isdnctrlX
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_ISDN_PPP
DECL|member|devfs_handle_ipppX
id|devfs_handle_t
id|devfs_handle_ipppX
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
macro_line|#endif
macro_line|#endif /* CONFIG_DEVFS_FS */
DECL|typedef|isdn_dev
)brace
id|isdn_dev
suffix:semicolon
r_extern
id|isdn_dev
op_star
id|dev
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ISDN_H__ */
eof
