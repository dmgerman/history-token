multiline_comment|/*&n; *&t;IrNET protocol module : Synchronous PPP over an IrDA socket.&n; *&n; *&t;&t;Jean II - HPL `00 - &lt;jt@hpl.hp.com&gt;&n; *&n; * This file contains definitions and declarations global to the IrNET module,&n; * all grouped in one place...&n; * This file is a *private* header, so other modules don&squot;t want to know&n; * what&squot;s in there...&n; *&n; * Note : as most part of the Linux kernel, this module is available&n; * under the GNU General Public License (GPL).&n; */
macro_line|#ifndef IRNET_H
DECL|macro|IRNET_H
mdefine_line|#define IRNET_H
multiline_comment|/************************** DOCUMENTATION ***************************/
multiline_comment|/*&n; * What is IrNET&n; * -------------&n; * IrNET is a protocol allowing to carry TCP/IP traffic between two&n; * IrDA peers in an efficient fashion. It is a thin layer, passing PPP&n; * packets to IrTTP and vice versa. It uses PPP in synchronous mode,&n; * because IrTTP offer a reliable sequenced packet service (as opposed&n; * to a byte stream). In fact, you could see IrNET as carrying TCP/IP&n; * in a IrDA socket, using PPP to provide the glue.&n; *&n; * The main difference with traditional PPP over IrCOMM is that we&n; * avoid the framing and serial emulation which are a performance&n; * bottleneck. It also allows multipoint communications in a sensible&n; * fashion.&n; *&n; * The main difference with IrLAN is that we use PPP for the link&n; * management, which is more standard, interoperable and flexible than&n; * the IrLAN protocol. For example, PPP adds authentication,&n; * encryption, compression, header compression and automated routing&n; * setup. And, as IrNET let PPP do the hard work, the implementation&n; * is much simpler than IrLAN.&n; *&n; * The Linux implementation&n; * ------------------------&n; * IrNET is written on top of the Linux-IrDA stack, and interface with&n; * the generic Linux PPP driver. Because IrNET depend on recent&n; * changes of the PPP driver interface, IrNET will work only with very&n; * recent kernel (2.3.99-pre6 and up).&n; * &n; * The present implementation offer the following features :&n; *&t;o simple user interface using pppd&n; *&t;o efficient implementation (interface directly to PPP and IrTTP)&n; *&t;o addressing (you can specify the name of the IrNET recipient)&n; *&t;o multipoint operation (limited by IrLAP specification)&n; *&t;o information in /proc/net/irda/irnet&n; *&t;o IrNET events on /dev/irnet (for user space daemon)&n; *&t;o IrNET daemon (irnetd) to automatically handle incoming requests&n; *&t;o Windows 2000 compatibility (tested, but need more work)&n; * Currently missing :&n; *&t;o Lot&squot;s of testing (that&squot;s your job)&n; *&t;o Connection retries (may be too hard to do)&n; *&t;o Check pppd persist mode&n; *&t;o User space daemon (to automatically handle incoming requests)&n; *&n; * The setup is not currently the most easy, but this should get much&n; * better when everything will get integrated...&n; *&n; * Acknowledgements&n; * ----------------&n; * This module is based on :&n; *&t;o The PPP driver (ppp_synctty/ppp_generic) by Paul Mackerras&n; *&t;o The IrLAN protocol (irlan_common/XXX) by Dag Brattli&n; *&t;o The IrSock interface (af_irda) by Dag Brattli&n; *&t;o Some other bits from the kernel and my drivers...&n; * Infinite thanks to those brave souls for providing the infrastructure&n; * upon which IrNET is built.&n; *&n; * Thanks to all my collegues in HP for helping me. In particular,&n; * thanks to Salil Pradhan and Bill Serra for W2k testing...&n; * Thanks to Luiz Magalhaes for irnetd and much testing...&n; *&n; * Thanks to Alan Cox for answering lot&squot;s of my stupid questions, and&n; * to Paul Mackerras answering my questions on how to best integrate&n; * IrNET and pppd.&n; *&n; * Jean II&n; *&n; * Note on some implementations choices...&n; * ------------------------------------&n; *&t;1) Direct interface vs tty/socket&n; * I could have used a tty interface to hook to ppp and use the full&n; * socket API to connect to IrDA. The code would have been easier to&n; * maintain, and maybe the code would have been smaller...&n; * Instead, we hook directly to ppp_generic and to IrTTP, which make&n; * things more complicated...&n; *&n; * The first reason is flexibility : this allow us to create IrNET&n; * instances on demand (no /dev/ircommX crap) and to allow linkname&n; * specification on pppd command line...&n; *&n; * Second reason is speed optimisation. If you look closely at the&n; * transmit and receive paths, you will notice that they are &quot;super lean&quot;&n; * (that&squot;s why they look ugly), with no function calls and as little data&n; * copy and modification as I could...&n; *&n; *&t;2) irnetd in user space&n; * irnetd is implemented in user space, which is necessary to call pppd.&n; * This also give maximum benefits in term of flexibility and customability,&n; * and allow to offer the event channel, useful for other stuff like debug.&n; *&n; * On the other hand, this require a loose coordination between the&n; * present module and irnetd. One critical area is how incoming request&n; * are handled.&n; * When irnet receive an incoming request, it send an event to irnetd and&n; * drop the incoming IrNET socket.&n; * irnetd start a pppd instance, which create a new IrNET socket. This new&n; * socket is then connected in the originating node to the pppd instance.&n; * At this point, in the originating node, the first socket is closed.&n; *&n; * I admit, this is a bit messy and waste some ressources. The alternative&n; * is caching incoming socket, and that&squot;s also quite messy and waste&n; * ressources.&n; * We also make connection time slower. For example, on a 115 kb/s link it&n; * adds 60ms to the connection time (770 ms). However, this is slower than&n; * the time it takes to fire up pppd on my P133...&n; *&n; *&n; * History :&n; * -------&n; *&n; * v1 - 15.5.00 - Jean II&n; *&t;o Basic IrNET (hook to ppp_generic &amp; IrTTP - incl. multipoint)&n; *&t;o control channel on /dev/irnet (set name/address)&n; *&t;o event channel on /dev/irnet (for user space daemon)&n; *&n; * v2 - 5.6.00 - Jean II&n; *&t;o Enable DROP_NOT_READY to avoid PPP timeouts &amp; other weirdness...&n; *&t;o Add DISCONNECT_TO event and rename DISCONNECT_FROM.&n; *&t;o Set official device number alloaction on /dev/irnet&n; *&n; * v3 - 30.8.00 - Jean II&n; *&t;o Update to latest Linux-IrDA changes :&n; *&t;&t;- queue_t =&gt; irda_queue_t&n; *&t;o Update to ppp-2.4.0 :&n; *&t;&t;- move irda_irnet_connect from PPPIOCATTACH to TIOCSETD&n; *&t;o Add EXPIRE event (depend on new IrDA-Linux patch)&n; *&t;o Switch from `hashbin_remove&squot; to `hashbin_remove_this&squot; to fix&n; *&t;  a multilink bug... (depend on new IrDA-Linux patch)&n; *&t;o fix a self-&gt;daddr to self-&gt;raddr in irda_irnet_connect to fix&n; *&t;  another multilink bug (darn !)&n; *&t;o Remove LINKNAME_IOCTL cruft&n; *&n; * v3b - 31.8.00 - Jean II&n; *&t;o Dump discovery log at event channel startup&n; *&n; * v4 - 28.9.00 - Jean II&n; *&t;o Fix interaction between poll/select and dump discovery log&n; *&t;o Add IRNET_BLOCKED_LINK event (depend on new IrDA-Linux patch)&n; *&t;o Add IRNET_NOANSWER_FROM event (mostly to help support)&n; *&t;o Release flow control in disconnect_indication&n; *&t;o Block packets while connecting (speed up connections)&n; *&n; * v5 - 11.01.01 - Jean II&n; *&t;o Init self-&gt;max_header_size, just in case...&n; *&t;o Set up ap-&gt;chan.hdrlen, to get zero copy on tx side working.&n; *&t;o avoid tx-&gt;ttp-&gt;flow-&gt;ppp-&gt;tx-&gt;... loop, by checking flow state&n; *&t;&t;Thanks to Christian Gennerat for finding this bug !&n; *&t;---&n; *&t;o Declare the proper MTU/MRU that we can support&n; *&t;&t;(but PPP doesn&squot;t read the MTU value :-()&n; *&t;o Declare hashbin HB_NOLOCK instead of HB_LOCAL to avoid&n; *&t;&t;disabling and enabling irq twice&n; *&n; * v6 - 31.05.01 - Jean II&n; *&t;o Print source address in Found, Discovery, Expiry &amp; Request events&n; *&t;o Print requested source address in /proc/net/irnet&n; *&t;o Change control channel input. Allow multiple commands in one line.&n; *&t;o Add saddr command to change ap-&gt;rsaddr (and use that in IrDA)&n; *&t;---&n; *&t;o Make the IrDA connection procedure totally asynchronous.&n; *&t;  Heavy rewrite of the IAS query code and the whole connection&n; *&t;  procedure. Now, irnet_connect() no longer need to be called from&n; *&t;  a process context...&n; *&t;o Enable IrDA connect retries in ppp_irnet_send(). The good thing&n; *&t;  is that IrDA connect retries are directly driven by PPP LCP&n; *&t;  retries (we retry for each LCP packet), so that everything&n; *&t;  is transparently controlled from pppd lcp-max-configure.&n; *&t;o Add ttp_connect flag to prevent rentry on the connect procedure&n; *&t;o Test and fixups to eliminate side effects of retries&n; *&n; * v7 - 22.08.01 - Jean II&n; *&t;o Cleanup : Change &quot;saddr = 0x0&quot; to &quot;saddr = DEV_ADDR_ANY&quot;&n; *&t;o Fix bug in BLOCK_WHEN_CONNECT introduced in v6 : due to the&n; *&t;  asynchronous IAS query, self-&gt;tsap is NULL when PPP send the&n; *&t;  first packet.  This was preventing &quot;connect-delay 0&quot; to work.&n; *&t;  Change the test in ppp_irnet_send() to self-&gt;ttp_connect.&n; *&n; * v8 - 1.11.01 - Jean II&n; *&t;o Tighten the use of self-&gt;ttp_connect and self-&gt;ttp_open to&n; *&t;  prevent various race conditions.&n; *&t;o Avoid leaking discovery log and skb&n; *&t;o Replace &quot;self&quot; with &quot;server&quot; in irnet_connect_indication() to&n; *&t;  better detect cut&squot;n&squot;paste error ;-)&n; *&n; * v9 - 29.11.01 - Jean II&n; *&t;o Fix event generation in disconnect indication that I broke in v8&n; *&t;  It was always generation &quot;No-Answer&quot; because I was testing ttp_open&n; *&t;  just after clearing it. *blush*.&n; *&t;o Use newly created irttp_listen() to fix potential crash when LAP&n; *&t;  destroyed before irnet module removed.&n; *&n; * v10 - 4.3.2 - Jean II&n; *&t;o When receiving a disconnect indication, don&squot;t reenable the&n; *&t;  PPP Tx queue, this will trigger a reconnect. Instead, close&n; *&t;  the channel, which will kill pppd...&n; *&n; * v11 - 20.3.02 - Jean II&n; *&t;o Oops ! v10 fix disabled IrNET retries and passive behaviour.&n; *&t;  Better fix in irnet_disconnect_indication() :&n; *&t;  - if connected, kill pppd via hangup.&n; *&t;  - if not connected, reenable ppp Tx, which trigger IrNET retry.&n; *&n; * v12 - 10.4.02 - Jean II&n; *&t;o Fix race condition in irnet_connect_indication().&n; *&t;  If the socket was already trying to connect, drop old connection&n; *&t;  and use new one only if acting as primary. See comments.&n; */
multiline_comment|/***************************** INCLUDES *****************************/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;&t;/* isspace() */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/ppp_defs.h&gt;
macro_line|#include &lt;linux/if_ppp.h&gt;
macro_line|#include &lt;linux/ppp_channel.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/iriap.h&gt;
macro_line|#include &lt;net/irda/irias_object.h&gt;
macro_line|#include &lt;net/irda/irlmp.h&gt;
macro_line|#include &lt;net/irda/irttp.h&gt;
macro_line|#include &lt;net/irda/discovery.h&gt;
multiline_comment|/***************************** OPTIONS *****************************/
multiline_comment|/*&n; * Define or undefine to compile or not some optional part of the&n; * IrNET driver...&n; * Note : the present defaults make sense, play with that at your&n; * own risk...&n; */
multiline_comment|/* IrDA side of the business... */
DECL|macro|DISCOVERY_NOMASK
mdefine_line|#define DISCOVERY_NOMASK&t;/* To enable W2k compatibility... */
DECL|macro|ADVERTISE_HINT
mdefine_line|#define ADVERTISE_HINT&t;&t;/* Advertise IrLAN hint bit */
DECL|macro|ALLOW_SIMULT_CONNECT
mdefine_line|#define ALLOW_SIMULT_CONNECT&t;/* This seem to work, cross fingers... */
DECL|macro|DISCOVERY_EVENTS
mdefine_line|#define DISCOVERY_EVENTS&t;/* Query the discovery log to post events */
DECL|macro|INITIAL_DISCOVERY
mdefine_line|#define INITIAL_DISCOVERY&t;/* Dump current discovery log as events */
DECL|macro|STREAM_COMPAT
macro_line|#undef STREAM_COMPAT&t;&t;/* Not needed - potentially messy */
DECL|macro|CONNECT_INDIC_KICK
macro_line|#undef CONNECT_INDIC_KICK&t;/* Might mess IrDA, not needed */
DECL|macro|FAIL_SEND_DISCONNECT
macro_line|#undef FAIL_SEND_DISCONNECT&t;/* Might mess IrDA, not needed */
DECL|macro|PASS_CONNECT_PACKETS
macro_line|#undef PASS_CONNECT_PACKETS&t;/* Not needed ? Safe */
multiline_comment|/* PPP side of the business */
DECL|macro|BLOCK_WHEN_CONNECT
mdefine_line|#define BLOCK_WHEN_CONNECT&t;/* Block packets when connecting */
DECL|macro|CONNECT_IN_SEND
mdefine_line|#define CONNECT_IN_SEND&t;&t;/* Retry IrDA connection procedure */
DECL|macro|FLUSH_TO_PPP
macro_line|#undef FLUSH_TO_PPP&t;&t;/* Not sure about this one, let&squot;s play safe */
DECL|macro|SECURE_DEVIRNET
macro_line|#undef SECURE_DEVIRNET&t;&t;/* Bah... */
multiline_comment|/****************************** DEBUG ******************************/
multiline_comment|/*&n; * This set of flags enable and disable all the various warning,&n; * error and debug message of this driver.&n; * Each section can be enabled and disabled independantly&n; */
multiline_comment|/* In the PPP part */
DECL|macro|DEBUG_CTRL_TRACE
mdefine_line|#define DEBUG_CTRL_TRACE&t;0&t;/* Control channel */
DECL|macro|DEBUG_CTRL_INFO
mdefine_line|#define DEBUG_CTRL_INFO&t;&t;0&t;/* various info */
DECL|macro|DEBUG_CTRL_ERROR
mdefine_line|#define DEBUG_CTRL_ERROR&t;1&t;/* problems */
DECL|macro|DEBUG_FS_TRACE
mdefine_line|#define DEBUG_FS_TRACE&t;&t;0&t;/* filesystem callbacks */
DECL|macro|DEBUG_FS_INFO
mdefine_line|#define DEBUG_FS_INFO&t;&t;0&t;/* various info */
DECL|macro|DEBUG_FS_ERROR
mdefine_line|#define DEBUG_FS_ERROR&t;&t;1&t;/* problems */
DECL|macro|DEBUG_PPP_TRACE
mdefine_line|#define DEBUG_PPP_TRACE&t;&t;0&t;/* PPP related functions */
DECL|macro|DEBUG_PPP_INFO
mdefine_line|#define DEBUG_PPP_INFO&t;&t;0&t;/* various info */
DECL|macro|DEBUG_PPP_ERROR
mdefine_line|#define DEBUG_PPP_ERROR&t;&t;1&t;/* problems */
DECL|macro|DEBUG_MODULE_TRACE
mdefine_line|#define DEBUG_MODULE_TRACE&t;0&t;/* module insertion/removal */
DECL|macro|DEBUG_MODULE_ERROR
mdefine_line|#define DEBUG_MODULE_ERROR&t;1&t;/* problems */
multiline_comment|/* In the IrDA part */
DECL|macro|DEBUG_IRDA_SR_TRACE
mdefine_line|#define DEBUG_IRDA_SR_TRACE&t;0&t;/* IRDA subroutines */
DECL|macro|DEBUG_IRDA_SR_INFO
mdefine_line|#define DEBUG_IRDA_SR_INFO&t;0&t;/* various info */
DECL|macro|DEBUG_IRDA_SR_ERROR
mdefine_line|#define DEBUG_IRDA_SR_ERROR&t;1&t;/* problems */
DECL|macro|DEBUG_IRDA_SOCK_TRACE
mdefine_line|#define DEBUG_IRDA_SOCK_TRACE&t;0&t;/* IRDA main socket functions */
DECL|macro|DEBUG_IRDA_SOCK_INFO
mdefine_line|#define DEBUG_IRDA_SOCK_INFO&t;0&t;/* various info */
DECL|macro|DEBUG_IRDA_SOCK_ERROR
mdefine_line|#define DEBUG_IRDA_SOCK_ERROR&t;1&t;/* problems */
DECL|macro|DEBUG_IRDA_SERV_TRACE
mdefine_line|#define DEBUG_IRDA_SERV_TRACE&t;0&t;/* The IrNET server */
DECL|macro|DEBUG_IRDA_SERV_INFO
mdefine_line|#define DEBUG_IRDA_SERV_INFO&t;0&t;/* various info */
DECL|macro|DEBUG_IRDA_SERV_ERROR
mdefine_line|#define DEBUG_IRDA_SERV_ERROR&t;1&t;/* problems */
DECL|macro|DEBUG_IRDA_TCB_TRACE
mdefine_line|#define DEBUG_IRDA_TCB_TRACE&t;0&t;/* IRDA IrTTP callbacks */
DECL|macro|DEBUG_IRDA_CB_INFO
mdefine_line|#define DEBUG_IRDA_CB_INFO&t;0&t;/* various info */
DECL|macro|DEBUG_IRDA_CB_ERROR
mdefine_line|#define DEBUG_IRDA_CB_ERROR&t;1&t;/* problems */
DECL|macro|DEBUG_IRDA_OCB_TRACE
mdefine_line|#define DEBUG_IRDA_OCB_TRACE&t;0&t;/* IRDA other callbacks */
DECL|macro|DEBUG_IRDA_OCB_INFO
mdefine_line|#define DEBUG_IRDA_OCB_INFO&t;0&t;/* various info */
DECL|macro|DEBUG_IRDA_OCB_ERROR
mdefine_line|#define DEBUG_IRDA_OCB_ERROR&t;1&t;/* problems */
DECL|macro|DEBUG_ASSERT
mdefine_line|#define DEBUG_ASSERT&t;&t;0&t;/* Verify all assertions */
multiline_comment|/* &n; * These are the macros we are using to actually print the debug&n; * statements. Don&squot;t look at it, it&squot;s ugly...&n; *&n; * One of the trick is that, as the DEBUG_XXX are constant, the&n; * compiler will optimise away the if() in all cases.&n; */
multiline_comment|/* All error messages (will show up in the normal logs) */
DECL|macro|DERROR
mdefine_line|#define DERROR(dbg, args...) &bslash;&n;&t;{if(DEBUG_##dbg) &bslash;&n;&t;&t;printk(KERN_INFO &quot;irnet: &quot; __FUNCTION__ &quot;(): &quot; args);}
multiline_comment|/* Normal debug message (will show up in /var/log/debug) */
DECL|macro|DEBUG
mdefine_line|#define DEBUG(dbg, args...) &bslash;&n;&t;{if(DEBUG_##dbg) &bslash;&n;&t;&t;printk(KERN_DEBUG &quot;irnet: &quot; __FUNCTION__ &quot;(): &quot; args);}
multiline_comment|/* Entering a function (trace) */
DECL|macro|DENTER
mdefine_line|#define DENTER(dbg, args...) &bslash;&n;&t;{if(DEBUG_##dbg) &bslash;&n;&t;&t;printk(KERN_DEBUG &quot;irnet: -&gt;&quot; __FUNCTION__ args);}
multiline_comment|/* Entering and exiting a function in one go (trace) */
DECL|macro|DPASS
mdefine_line|#define DPASS(dbg, args...) &bslash;&n;&t;{if(DEBUG_##dbg) &bslash;&n;&t;&t;printk(KERN_DEBUG &quot;irnet: &lt;&gt;&quot; __FUNCTION__ args);}
multiline_comment|/* Exiting a function (trace) */
DECL|macro|DEXIT
mdefine_line|#define DEXIT(dbg, args...) &bslash;&n;&t;{if(DEBUG_##dbg) &bslash;&n;&t;&t;printk(KERN_DEBUG &quot;irnet: &lt;-&quot; __FUNCTION__ &quot;()&quot; args);}
multiline_comment|/* Exit a function with debug */
DECL|macro|DRETURN
mdefine_line|#define DRETURN(ret, dbg, args...) &bslash;&n;&t;{DEXIT(dbg, &quot;: &quot; args);&bslash;&n;&t;return(ret); }
multiline_comment|/* Exit a function on failed condition */
DECL|macro|DABORT
mdefine_line|#define DABORT(cond, ret, dbg, args...) &bslash;&n;&t;{if(cond) {&bslash;&n;&t;&t;DERROR(dbg, args);&bslash;&n;&t;&t;return(ret); }}
multiline_comment|/* Invalid assertion, print out an error and exit... */
DECL|macro|DASSERT
mdefine_line|#define DASSERT(cond, ret, dbg, args...) &bslash;&n;&t;{if((DEBUG_ASSERT) &amp;&amp; !(cond)) {&bslash;&n;&t;&t;DERROR(dbg, &quot;Invalid assertion: &quot; args);&bslash;&n;&t;&t;return ret; }}
multiline_comment|/************************ CONSTANTS &amp; MACROS ************************/
multiline_comment|/* Paranoia */
DECL|macro|IRNET_MAGIC
mdefine_line|#define IRNET_MAGIC&t;0xB00754
multiline_comment|/* Number of control events in the control channel buffer... */
DECL|macro|IRNET_MAX_EVENTS
mdefine_line|#define IRNET_MAX_EVENTS&t;8&t;/* Should be more than enough... */
multiline_comment|/****************************** TYPES ******************************/
multiline_comment|/*&n; * This is the main structure where we store all the data pertaining to&n; * one instance of irnet.&n; * Note : in irnet functions, a pointer this structure is usually called&n; * &quot;ap&quot; or &quot;self&quot;. If the code is borrowed from the IrDA stack, it tend&n; * to be called &quot;self&quot;, and if it is borrowed from the PPP driver it is&n; * &quot;ap&quot;. Apart from that, it&squot;s exactly the same structure ;-)&n; */
DECL|struct|irnet_socket
r_typedef
r_struct
id|irnet_socket
(brace
multiline_comment|/* ------------------- Instance management ------------------- */
multiline_comment|/* We manage a linked list of IrNET socket instances */
DECL|member|q
id|irda_queue_t
id|q
suffix:semicolon
multiline_comment|/* Must be first - for hasbin */
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* Paranoia */
multiline_comment|/* --------------------- FileSystem part --------------------- */
multiline_comment|/* &quot;pppd&quot; interact directly with us on a /dev/ file */
DECL|member|file
r_struct
id|file
op_star
id|file
suffix:semicolon
multiline_comment|/* File descriptor of this instance */
multiline_comment|/* TTY stuff - to keep &quot;pppd&quot; happy */
DECL|member|termios
r_struct
id|termios
id|termios
suffix:semicolon
multiline_comment|/* Various tty flags */
multiline_comment|/* Stuff for the control channel */
DECL|member|event_index
r_int
id|event_index
suffix:semicolon
multiline_comment|/* Last read in the event log */
multiline_comment|/* ------------------------- PPP part ------------------------- */
multiline_comment|/* We interface directly to the ppp_generic driver in the kernel */
DECL|member|ppp_open
r_int
id|ppp_open
suffix:semicolon
multiline_comment|/* registered with ppp_generic */
DECL|member|chan
r_struct
id|ppp_channel
id|chan
suffix:semicolon
multiline_comment|/* Interface to generic ppp layer */
DECL|member|mru
r_int
id|mru
suffix:semicolon
multiline_comment|/* Max size of PPP payload */
DECL|member|xaccm
id|u32
id|xaccm
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Asynchronous character map (just */
DECL|member|raccm
id|u32
id|raccm
suffix:semicolon
multiline_comment|/* to please pppd - dummy) */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* PPP flags (compression, ...) */
DECL|member|rbits
r_int
r_int
id|rbits
suffix:semicolon
multiline_comment|/* Unused receive flags ??? */
multiline_comment|/* ------------------------ IrTTP part ------------------------ */
multiline_comment|/* We create a pseudo &quot;socket&quot; over the IrDA tranport */
DECL|member|ttp_open
r_int
r_int
id|ttp_open
suffix:semicolon
multiline_comment|/* Set when IrTTP is ready */
DECL|member|ttp_connect
r_int
r_int
id|ttp_connect
suffix:semicolon
multiline_comment|/* Set when IrTTP is connecting */
DECL|member|tsap
r_struct
id|tsap_cb
op_star
id|tsap
suffix:semicolon
multiline_comment|/* IrTTP instance (the connection) */
DECL|member|rname
r_char
id|rname
(braket
id|NICKNAME_MAX_LEN
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* IrDA nickname of destination */
DECL|member|rdaddr
id|__u32
id|rdaddr
suffix:semicolon
multiline_comment|/* Requested peer IrDA address */
DECL|member|rsaddr
id|__u32
id|rsaddr
suffix:semicolon
multiline_comment|/* Requested local IrDA address */
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
multiline_comment|/* actual peer IrDA address */
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
multiline_comment|/* my local IrDA address */
DECL|member|dtsap_sel
id|__u8
id|dtsap_sel
suffix:semicolon
multiline_comment|/* Remote TSAP selector */
DECL|member|stsap_sel
id|__u8
id|stsap_sel
suffix:semicolon
multiline_comment|/* Local TSAP selector */
DECL|member|max_sdu_size_rx
id|__u32
id|max_sdu_size_rx
suffix:semicolon
multiline_comment|/* Socket parameters used for IrTTP */
DECL|member|max_sdu_size_tx
id|__u32
id|max_sdu_size_tx
suffix:semicolon
DECL|member|max_data_size
id|__u32
id|max_data_size
suffix:semicolon
DECL|member|max_header_size
id|__u8
id|max_header_size
suffix:semicolon
DECL|member|tx_flow
id|LOCAL_FLOW
id|tx_flow
suffix:semicolon
multiline_comment|/* State of the Tx path in IrTTP */
multiline_comment|/* ------------------- IrLMP and IrIAS part ------------------- */
multiline_comment|/* Used for IrDA Discovery and socket name resolution */
DECL|member|ckey
id|__u32
id|ckey
suffix:semicolon
multiline_comment|/* IrLMP client handle */
DECL|member|mask
id|__u16
id|mask
suffix:semicolon
multiline_comment|/* Hint bits mask (filter discov.)*/
DECL|member|nslots
r_int
id|nslots
suffix:semicolon
multiline_comment|/* Number of slots for discovery */
DECL|member|iriap
r_struct
id|iriap_cb
op_star
id|iriap
suffix:semicolon
multiline_comment|/* Used to query remote IAS */
DECL|member|errno
r_int
id|errno
suffix:semicolon
multiline_comment|/* status of the IAS query */
multiline_comment|/* -------------------- Discovery log part -------------------- */
multiline_comment|/* Used by initial discovery on the control channel&n;   * and by irnet_discover_daddr_and_lsap_sel() */
DECL|member|discoveries
r_struct
id|irda_device_info
op_star
id|discoveries
suffix:semicolon
multiline_comment|/* Copy of the discovery log */
DECL|member|disco_index
r_int
id|disco_index
suffix:semicolon
multiline_comment|/* Last read in the discovery log */
DECL|member|disco_number
r_int
id|disco_number
suffix:semicolon
multiline_comment|/* Size of the discovery log */
DECL|typedef|irnet_socket
)brace
id|irnet_socket
suffix:semicolon
multiline_comment|/*&n; * This is the various event that we will generate on the control channel&n; */
DECL|enum|irnet_event
r_typedef
r_enum
id|irnet_event
(brace
DECL|enumerator|IRNET_DISCOVER
id|IRNET_DISCOVER
comma
multiline_comment|/* New IrNET node discovered */
DECL|enumerator|IRNET_EXPIRE
id|IRNET_EXPIRE
comma
multiline_comment|/* IrNET node expired */
DECL|enumerator|IRNET_CONNECT_TO
id|IRNET_CONNECT_TO
comma
multiline_comment|/* IrNET socket has connected to other node */
DECL|enumerator|IRNET_CONNECT_FROM
id|IRNET_CONNECT_FROM
comma
multiline_comment|/* Other node has connected to IrNET socket */
DECL|enumerator|IRNET_REQUEST_FROM
id|IRNET_REQUEST_FROM
comma
multiline_comment|/* Non satisfied connection request */
DECL|enumerator|IRNET_NOANSWER_FROM
id|IRNET_NOANSWER_FROM
comma
multiline_comment|/* Failed connection request */
DECL|enumerator|IRNET_BLOCKED_LINK
id|IRNET_BLOCKED_LINK
comma
multiline_comment|/* Link (IrLAP) is blocked for &gt; 3s */
DECL|enumerator|IRNET_DISCONNECT_FROM
id|IRNET_DISCONNECT_FROM
comma
multiline_comment|/* IrNET socket has disconnected */
DECL|enumerator|IRNET_DISCONNECT_TO
id|IRNET_DISCONNECT_TO
multiline_comment|/* Closing IrNET socket */
DECL|typedef|irnet_event
)brace
id|irnet_event
suffix:semicolon
multiline_comment|/*&n; * This is the storage for an event and its arguments&n; */
DECL|struct|irnet_log
r_typedef
r_struct
id|irnet_log
(brace
DECL|member|event
id|irnet_event
id|event
suffix:semicolon
DECL|member|unit
r_int
id|unit
suffix:semicolon
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|NICKNAME_MAX_LEN
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* 21 + 1 */
DECL|typedef|irnet_log
)brace
id|irnet_log
suffix:semicolon
multiline_comment|/*&n; * This is the storage for all events and related stuff...&n; */
DECL|struct|irnet_ctrl_channel
r_typedef
r_struct
id|irnet_ctrl_channel
(brace
DECL|member|log
id|irnet_log
id|log
(braket
id|IRNET_MAX_EVENTS
)braket
suffix:semicolon
multiline_comment|/* Event log */
DECL|member|index
r_int
id|index
suffix:semicolon
multiline_comment|/* Current index in log */
DECL|member|spinlock
id|spinlock_t
id|spinlock
suffix:semicolon
multiline_comment|/* Serialize access to the event log */
DECL|member|rwait
id|wait_queue_head_t
id|rwait
suffix:semicolon
multiline_comment|/* processes blocked on read (or poll) */
DECL|typedef|irnet_ctrl_channel
)brace
id|irnet_ctrl_channel
suffix:semicolon
multiline_comment|/**************************** PROTOTYPES ****************************/
multiline_comment|/*&n; * Global functions of the IrNET module&n; * Note : we list here also functions called from one file to the other.&n; */
multiline_comment|/* -------------------------- IRDA PART -------------------------- */
r_extern
r_int
id|irda_irnet_create
c_func
(paren
id|irnet_socket
op_star
)paren
suffix:semicolon
multiline_comment|/* Initialise a IrNET socket */
r_extern
r_int
id|irda_irnet_connect
c_func
(paren
id|irnet_socket
op_star
)paren
suffix:semicolon
multiline_comment|/* Try to connect over IrDA */
r_extern
r_void
id|irda_irnet_destroy
c_func
(paren
id|irnet_socket
op_star
)paren
suffix:semicolon
multiline_comment|/* Teardown  a IrNET socket */
r_extern
r_int
id|irda_irnet_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Initialise IrDA part of IrNET */
r_extern
r_void
id|irda_irnet_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Teardown IrDA part of IrNET */
multiline_comment|/* --------------------------- PPP PART --------------------------- */
r_extern
r_int
id|ppp_irnet_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Initialise PPP part of IrNET */
r_extern
r_void
id|ppp_irnet_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Teardown PPP part of IrNET */
multiline_comment|/* ---------------------------- MODULE ---------------------------- */
r_extern
r_int
id|init_module
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Initialise IrNET module */
r_extern
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Teardown IrNET module  */
multiline_comment|/**************************** VARIABLES ****************************/
multiline_comment|/* Control channel stuff - allocated in irnet_irda.h */
r_extern
r_struct
id|irnet_ctrl_channel
id|irnet_events
suffix:semicolon
macro_line|#endif /* IRNET_H */
eof
