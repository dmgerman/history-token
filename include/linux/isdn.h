multiline_comment|/* Linux ISDN subsystem, main header&n; *&n; * Copyright 1994,95,96 by Fritz Elfert (fritz@isdn4linux.de)&n; * Copyright 1995,96    by Thinking Objects Software GmbH Wuerzburg&n; * Copyright 1995,96    by Michael Hipp (Michael.Hipp@student.uni-tuebingen.de)&n; * Copyright 2000-2002  by Kai Germaschewski (kai@germaschewski.name)&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#ifndef __ISDN_H__
DECL|macro|__ISDN_H__
mdefine_line|#define __ISDN_H__
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/isdn/fsm.h&gt;
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
DECL|macro|ISDN_NET_ENCAP_NR
mdefine_line|#define ISDN_NET_ENCAP_NR         8
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
multiline_comment|/* GLOBAL_FLAGS */
DECL|macro|ISDN_GLOBAL_STOPPED
mdefine_line|#define ISDN_GLOBAL_STOPPED 1
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
DECL|member|isdn_slot
r_struct
id|isdn_slot
op_star
id|isdn_slot
suffix:semicolon
multiline_comment|/* Ptr to isdn-driver/channel     */
DECL|member|rpqueue
r_struct
id|sk_buff_head
id|rpqueue
suffix:semicolon
multiline_comment|/* Queue of recv&squot;d packets        */
DECL|member|rcvcount
r_int
id|rcvcount
suffix:semicolon
multiline_comment|/* Byte-counters for B rx         */
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
DECL|member|DLEflag
r_int
r_int
id|DLEflag
suffix:semicolon
multiline_comment|/* Insert DLE at next read     */
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
DECL|member|escape_timer
r_struct
id|timer_list
id|escape_timer
suffix:semicolon
multiline_comment|/* to recognize +++ escape        */
DECL|member|ring_timer
r_struct
id|timer_list
id|ring_timer
suffix:semicolon
multiline_comment|/* for writing &squot;RING&squot; responses   */
DECL|member|connect_timer
r_struct
id|timer_list
id|connect_timer
suffix:semicolon
multiline_comment|/* waiting for CONNECT            */
DECL|member|read_timer
r_struct
id|timer_list
id|read_timer
suffix:semicolon
multiline_comment|/* read incoming data             */
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
DECL|member|profd
r_struct
id|task_struct
op_star
id|profd
suffix:semicolon
multiline_comment|/* For iprofd                 */
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
