multiline_comment|/*&n; * INET         An implementation of the TCP/IP protocol suite for the LINUX&n; *              operating system.  NET  is implemented using the  BSD Socket&n; *              interface as the means of communication with the user level.&n; *&n; *              Definitions used by the ARCnet driver.&n; *&n; * Authors:     Avery Pennarun and David Woodhouse&n; *&n; *              This program is free software; you can redistribute it and/or&n; *              modify it under the terms of the GNU General Public License&n; *              as published by the Free Software Foundation; either version&n; *              2 of the License, or (at your option) any later version.&n; *&n; */
macro_line|#ifndef _LINUX_ARCDEVICE_H
DECL|macro|_LINUX_ARCDEVICE_H
mdefine_line|#define _LINUX_ARCDEVICE_H
macro_line|#include &lt;asm/timex.h&gt;
macro_line|#include &lt;linux/if_arcnet.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#ifndef bool
DECL|macro|bool
mdefine_line|#define bool int
macro_line|#endif
multiline_comment|/*&n; * RECON_THRESHOLD is the maximum number of RECON messages to receive&n; * within one minute before printing a &quot;cabling problem&quot; warning. The&n; * default value should be fine.&n; *&n; * After that, a &quot;cabling restored&quot; message will be printed on the next IRQ&n; * if no RECON messages have been received for 10 seconds.&n; *&n; * Do not define RECON_THRESHOLD at all if you want to disable this feature.&n; */
DECL|macro|RECON_THRESHOLD
mdefine_line|#define RECON_THRESHOLD 30
multiline_comment|/*&n; * Define this to the minimum &quot;timeout&quot; value.  If a transmit takes longer&n; * than TX_TIMEOUT jiffies, Linux will abort the TX and retry.  On a large&n; * network, or one with heavy network traffic, this timeout may need to be&n; * increased.  The larger it is, though, the longer it will be between&n; * necessary transmits - don&squot;t set this too high.&n; */
DECL|macro|TX_TIMEOUT
mdefine_line|#define TX_TIMEOUT (HZ * 200 / 1000)
multiline_comment|/* Display warnings about the driver being an ALPHA version. */
DECL|macro|ALPHA_WARNING
macro_line|#undef ALPHA_WARNING
multiline_comment|/*&n; * Debugging bitflags: each option can be enabled individually.&n; * &n; * Note: only debug flags included in the ARCNET_DEBUG_MAX define will&n; *   actually be available.  GCC will (at least, GCC 2.7.0 will) notice&n; *   lines using a BUGLVL not in ARCNET_DEBUG_MAX and automatically optimize&n; *   them out.&n; */
DECL|macro|D_NORMAL
mdefine_line|#define D_NORMAL&t;1&t;/* important operational info             */
DECL|macro|D_EXTRA
mdefine_line|#define D_EXTRA&t;&t;2&t;/* useful, but non-vital information      */
DECL|macro|D_INIT
mdefine_line|#define&t;D_INIT&t;&t;4&t;/* show init/probe messages               */
DECL|macro|D_INIT_REASONS
mdefine_line|#define D_INIT_REASONS&t;8&t;/* show reasons for discarding probes     */
DECL|macro|D_RECON
mdefine_line|#define D_RECON&t;&t;32&t;/* print a message whenever token is lost */
DECL|macro|D_PROTO
mdefine_line|#define D_PROTO&t;&t;64&t;/* debug auto-protocol support            */
multiline_comment|/* debug levels below give LOTS of output during normal operation! */
DECL|macro|D_DURING
mdefine_line|#define D_DURING&t;128&t;/* trace operations (including irq&squot;s)     */
DECL|macro|D_TX
mdefine_line|#define D_TX&t;        256&t;/* show tx packets                        */
DECL|macro|D_RX
mdefine_line|#define D_RX&t;&t;512&t;/* show rx packets                        */
DECL|macro|D_SKB
mdefine_line|#define D_SKB&t;&t;1024&t;/* show skb&squot;s                             */
DECL|macro|D_SKB_SIZE
mdefine_line|#define D_SKB_SIZE&t;2048&t;/* show skb sizes&t;&t;&t;  */
DECL|macro|D_TIMING
mdefine_line|#define D_TIMING&t;4096&t;/* show time needed to copy buffers to card */
macro_line|#ifndef ARCNET_DEBUG_MAX
DECL|macro|ARCNET_DEBUG_MAX
mdefine_line|#define ARCNET_DEBUG_MAX (127)&t;/* change to ~0 if you want detailed debugging */
macro_line|#endif
macro_line|#ifndef ARCNET_DEBUG
DECL|macro|ARCNET_DEBUG
mdefine_line|#define ARCNET_DEBUG (D_NORMAL|D_EXTRA)
macro_line|#endif
r_extern
r_int
id|arcnet_debug
suffix:semicolon
multiline_comment|/* macros to simplify debug checking */
DECL|macro|BUGLVL
mdefine_line|#define BUGLVL(x) if ((ARCNET_DEBUG_MAX)&amp;arcnet_debug&amp;(x))
DECL|macro|BUGMSG2
mdefine_line|#define BUGMSG2(x,msg,args...) do { BUGLVL(x) printk(msg, ## args); } while (0)
DECL|macro|BUGMSG
mdefine_line|#define BUGMSG(x,msg,args...) &bslash;&n;&t;BUGMSG2(x, &quot;%s%6s: &quot; msg, &bslash;&n;            x==D_NORMAL&t;? KERN_WARNING &bslash;&n;            &t;&t;: x &lt; D_DURING ? KERN_INFO : KERN_DEBUG, &bslash;&n;&t;    dev-&gt;name , ## args)
multiline_comment|/* see how long a function call takes to run, expressed in CPU cycles */
DECL|macro|TIME
mdefine_line|#define TIME(name, bytes, call) BUGLVL(D_TIMING) { &bslash;&n;&t;    unsigned long _x, _y; &bslash;&n;&t;    _x = get_cycles(); &bslash;&n;&t;    call; &bslash;&n;&t;    _y = get_cycles(); &bslash;&n;&t;    BUGMSG(D_TIMING, &bslash;&n;&t;       &quot;%s: %d bytes in %lu cycles == &quot; &bslash;&n;&t;       &quot;%lu Kbytes/100Mcycle&bslash;n&quot;,&bslash;&n;&t;&t;   name, bytes, _y - _x, &bslash;&n;&t;&t;   100000000 / 1024 * bytes / (_y - _x + 1));&bslash;&n;&t;} &bslash;&n;&t;else { &bslash;&n;&t;&t;    call;&bslash;&n;&t;}
multiline_comment|/*&n; * Time needed to reset the card - in ms (milliseconds).  This works on my&n; * SMC PC100.  I can&squot;t find a reference that tells me just how long I&n; * should wait.&n; */
DECL|macro|RESETtime
mdefine_line|#define RESETtime (300)
multiline_comment|/*&n; * These are the max/min lengths of packet payload, not including the&n; * arc_hardware header, but definitely including the soft header.&n; *&n; * Note: packet sizes 254, 255, 256 are impossible because of the way&n; * ARCnet registers work  That&squot;s why RFC1201 defines &quot;exception&quot; packets.&n; * In non-RFC1201 protocols, we have to just tack some extra bytes on the&n; * end.&n; */
DECL|macro|MTU
mdefine_line|#define MTU&t;253&t;&t;/* normal packet max size */
DECL|macro|MinTU
mdefine_line|#define MinTU&t;257&t;&t;/* extended packet min size */
DECL|macro|XMTU
mdefine_line|#define XMTU&t;508&t;&t;/* extended packet max size */
multiline_comment|/* status/interrupt mask bit fields */
DECL|macro|TXFREEflag
mdefine_line|#define TXFREEflag&t;0x01&t;/* transmitter available */
DECL|macro|TXACKflag
mdefine_line|#define TXACKflag       0x02&t;/* transmitted msg. ackd */
DECL|macro|RECONflag
mdefine_line|#define RECONflag       0x04&t;/* network reconfigured */
DECL|macro|TESTflag
mdefine_line|#define TESTflag        0x08&t;/* test flag */
DECL|macro|RESETflag
mdefine_line|#define RESETflag       0x10&t;/* power-on-reset */
DECL|macro|RES1flag
mdefine_line|#define RES1flag        0x20&t;/* reserved - usually set by jumper */
DECL|macro|RES2flag
mdefine_line|#define RES2flag        0x40&t;/* reserved - usually set by jumper */
DECL|macro|NORXflag
mdefine_line|#define NORXflag        0x80&t;/* receiver inhibited */
multiline_comment|/* Flags used for IO-mapped memory operations */
DECL|macro|AUTOINCflag
mdefine_line|#define AUTOINCflag     0x40&t;/* Increase location with each access */
DECL|macro|IOMAPflag
mdefine_line|#define IOMAPflag       0x02&t;/* (for 90xx) Use IO mapped memory, not mmap */
DECL|macro|ENABLE16flag
mdefine_line|#define ENABLE16flag    0x80&t;/* (for 90xx) Enable 16-bit mode */
multiline_comment|/* in the command register, the following bits have these meanings:&n; *                0-2     command&n; *                3-4     page number (for enable rcv/xmt command)&n; *                 7      receive broadcasts&n; */
DECL|macro|NOTXcmd
mdefine_line|#define NOTXcmd         0x01&t;/* disable transmitter */
DECL|macro|NORXcmd
mdefine_line|#define NORXcmd         0x02&t;/* disable receiver */
DECL|macro|TXcmd
mdefine_line|#define TXcmd           0x03&t;/* enable transmitter */
DECL|macro|RXcmd
mdefine_line|#define RXcmd           0x04&t;/* enable receiver */
DECL|macro|CONFIGcmd
mdefine_line|#define CONFIGcmd       0x05&t;/* define configuration */
DECL|macro|CFLAGScmd
mdefine_line|#define CFLAGScmd       0x06&t;/* clear flags */
DECL|macro|TESTcmd
mdefine_line|#define TESTcmd         0x07&t;/* load test flags */
multiline_comment|/* flags for &quot;clear flags&quot; command */
DECL|macro|RESETclear
mdefine_line|#define RESETclear      0x08&t;/* power-on-reset */
DECL|macro|CONFIGclear
mdefine_line|#define CONFIGclear     0x10&t;/* system reconfigured */
multiline_comment|/* flags for &quot;load test flags&quot; command */
DECL|macro|TESTload
mdefine_line|#define TESTload        0x08&t;/* test flag (diagnostic) */
multiline_comment|/* byte deposited into first address of buffers on reset */
DECL|macro|TESTvalue
mdefine_line|#define TESTvalue       0321&t;/* that&squot;s octal for 0xD1 :) */
multiline_comment|/* for &quot;enable receiver&quot; command */
DECL|macro|RXbcasts
mdefine_line|#define RXbcasts        0x80&t;/* receive broadcasts */
multiline_comment|/* flags for &quot;define configuration&quot; command */
DECL|macro|NORMALconf
mdefine_line|#define NORMALconf      0x00&t;/* 1-249 byte packets */
DECL|macro|EXTconf
mdefine_line|#define EXTconf         0x08&t;/* 250-504 byte packets */
multiline_comment|/* card feature flags, set during auto-detection.&n; * (currently only used by com20020pci)&n; */
DECL|macro|ARC_IS_5MBIT
mdefine_line|#define ARC_IS_5MBIT    1   /* card default speed is 5MBit */
DECL|macro|ARC_CAN_10MBIT
mdefine_line|#define ARC_CAN_10MBIT  2   /* card uses COM20022, supporting 10MBit,&n;&t;&t;&t;&t; but default is 2.5MBit. */
multiline_comment|/* information needed to define an encapsulation driver */
DECL|struct|ArcProto
r_struct
id|ArcProto
(brace
DECL|member|suffix
r_char
id|suffix
suffix:semicolon
multiline_comment|/* a for RFC1201, e for ether-encap, etc. */
DECL|member|mtu
r_int
id|mtu
suffix:semicolon
multiline_comment|/* largest possible packet */
DECL|member|rx
r_void
(paren
op_star
id|rx
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|bufnum
comma
r_struct
id|archdr
op_star
id|pkthdr
comma
r_int
id|length
)paren
suffix:semicolon
DECL|member|build_header
r_int
(paren
op_star
id|build_header
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
r_int
id|ethproto
comma
r_uint8
id|daddr
)paren
suffix:semicolon
multiline_comment|/* these functions return &squot;1&squot; if the skb can now be freed */
DECL|member|prepare_tx
r_int
(paren
op_star
id|prepare_tx
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|archdr
op_star
id|pkt
comma
r_int
id|length
comma
r_int
id|bufnum
)paren
suffix:semicolon
DECL|member|continue_tx
r_int
(paren
op_star
id|continue_tx
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|bufnum
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|ArcProto
op_star
id|arc_proto_map
(braket
l_int|256
)braket
comma
op_star
id|arc_proto_default
comma
op_star
id|arc_bcast_proto
suffix:semicolon
r_extern
r_struct
id|ArcProto
id|arc_proto_null
suffix:semicolon
multiline_comment|/*&n; * &quot;Incoming&quot; is information needed for each address that could be sending&n; * to us.  Mostly for partially-received split packets.&n; */
DECL|struct|Incoming
r_struct
id|Incoming
(brace
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
multiline_comment|/* packet data buffer             */
DECL|member|sequence
r_uint16
id|sequence
suffix:semicolon
multiline_comment|/* sequence number of assembly    */
DECL|member|lastpacket
r_uint8
id|lastpacket
comma
multiline_comment|/* number of last packet (from 1) */
DECL|member|numpackets
id|numpackets
suffix:semicolon
multiline_comment|/* number of packets in split     */
)brace
suffix:semicolon
multiline_comment|/* only needed for RFC1201 */
DECL|struct|Outgoing
r_struct
id|Outgoing
(brace
DECL|member|proto
r_struct
id|ArcProto
op_star
id|proto
suffix:semicolon
multiline_comment|/* protocol driver that owns this:&n;&t;&t;&t;&t; *   if NULL, no packet is pending.&n;&t;&t;&t;&t; */
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
multiline_comment|/* buffer from upper levels */
DECL|member|pkt
r_struct
id|archdr
op_star
id|pkt
suffix:semicolon
multiline_comment|/* a pointer into the skb */
DECL|member|length
r_uint16
id|length
comma
multiline_comment|/* bytes total */
DECL|member|dataleft
id|dataleft
comma
multiline_comment|/* bytes left */
DECL|member|segnum
id|segnum
comma
multiline_comment|/* segment being sent */
DECL|member|numsegs
id|numsegs
suffix:semicolon
multiline_comment|/* number of segments */
)brace
suffix:semicolon
DECL|struct|arcnet_local
r_struct
id|arcnet_local
(brace
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|config
r_uint8
id|config
comma
multiline_comment|/* current value of CONFIG register */
DECL|member|timeout
id|timeout
comma
multiline_comment|/* Extended timeout for COM20020 */
DECL|member|backplane
id|backplane
comma
multiline_comment|/* Backplane flag for COM20020 */
DECL|member|clockp
id|clockp
comma
multiline_comment|/* COM20020 clock divider */
DECL|member|clockm
id|clockm
comma
multiline_comment|/* COM20020 clock multiplier flag */
DECL|member|setup
id|setup
comma
multiline_comment|/* Contents of setup1 register */
DECL|member|setup2
id|setup2
comma
multiline_comment|/* Contents of setup2 register */
DECL|member|intmask
id|intmask
suffix:semicolon
multiline_comment|/* current value of INTMASK register */
DECL|member|default_proto
r_uint8
id|default_proto
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* default encap to use for each host */
DECL|member|cur_tx
r_int
id|cur_tx
comma
multiline_comment|/* buffer used by current transmit, or -1 */
DECL|member|next_tx
id|next_tx
comma
multiline_comment|/* buffer where a packet is ready to send */
DECL|member|cur_rx
id|cur_rx
suffix:semicolon
multiline_comment|/* current receive buffer */
DECL|member|lastload_dest
r_int
id|lastload_dest
comma
multiline_comment|/* can last loaded packet be acked? */
DECL|member|lasttrans_dest
id|lasttrans_dest
suffix:semicolon
multiline_comment|/* can last TX&squot;d packet be acked? */
DECL|member|timed_out
r_int
id|timed_out
suffix:semicolon
multiline_comment|/* need to process TX timeout and drop packet */
DECL|member|last_timeout
r_int
r_int
id|last_timeout
suffix:semicolon
multiline_comment|/* time of last reported timeout */
DECL|member|card_name
r_char
op_star
id|card_name
suffix:semicolon
multiline_comment|/* card ident string */
DECL|member|card_flags
r_int
id|card_flags
suffix:semicolon
multiline_comment|/* special card features */
multiline_comment|/*&n;&t; * Buffer management: an ARCnet card has 4 x 512-byte buffers, each of&n;&t; * which can be used for either sending or receiving.  The new dynamic&n;&t; * buffer management routines use a simple circular queue of available&n;&t; * buffers, and take them as they&squot;re needed.  This way, we simplify&n;&t; * situations in which we (for example) want to pre-load a transmit&n;&t; * buffer, or start receiving while we copy a received packet to&n;&t; * memory.&n;&t; * &n;&t; * The rules: only the interrupt handler is allowed to _add_ buffers to&n;&t; * the queue; thus, this doesn&squot;t require a lock.  Both the interrupt&n;&t; * handler and the transmit function will want to _remove_ buffers, so&n;&t; * we need to handle the situation where they try to do it at the same&n;&t; * time.&n;&t; * &n;&t; * If next_buf == first_free_buf, the queue is empty.  Since there are&n;&t; * only four possible buffers, the queue should never be full.&n;&t; */
DECL|member|buf_lock
id|atomic_t
id|buf_lock
suffix:semicolon
DECL|member|buf_queue
r_int
id|buf_queue
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|next_buf
DECL|member|first_free_buf
r_int
id|next_buf
comma
id|first_free_buf
suffix:semicolon
multiline_comment|/* network &quot;reconfiguration&quot; handling */
DECL|member|first_recon
id|time_t
id|first_recon
comma
multiline_comment|/* time of &quot;first&quot; RECON message to count */
DECL|member|last_recon
id|last_recon
suffix:semicolon
multiline_comment|/* time of most recent RECON */
DECL|member|num_recons
r_int
id|num_recons
suffix:semicolon
multiline_comment|/* number of RECONs between first and last. */
DECL|member|network_down
r_bool
id|network_down
suffix:semicolon
multiline_comment|/* do we think the network is down? */
r_struct
(brace
DECL|member|sequence
r_uint16
id|sequence
suffix:semicolon
multiline_comment|/* sequence number (incs with each packet) */
DECL|member|aborted_seq
r_uint16
id|aborted_seq
suffix:semicolon
DECL|member|incoming
r_struct
id|Incoming
id|incoming
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* one from each address */
DECL|member|rfc1201
)brace
id|rfc1201
suffix:semicolon
multiline_comment|/* really only used by rfc1201, but we&squot;ll pretend it&squot;s not */
DECL|member|outgoing
r_struct
id|Outgoing
id|outgoing
suffix:semicolon
multiline_comment|/* packet currently being sent */
multiline_comment|/* hardware-specific functions */
r_struct
(brace
DECL|member|command
r_void
(paren
op_star
id|command
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|cmd
)paren
suffix:semicolon
DECL|member|status
r_int
(paren
op_star
id|status
)paren
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|member|intmask
r_void
(paren
op_star
id|intmask
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|mask
)paren
suffix:semicolon
DECL|member|reset
r_bool
(paren
op_star
id|reset
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_bool
id|really_reset
)paren
suffix:semicolon
DECL|member|open_close
r_void
(paren
op_star
id|open_close
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_bool
id|open
)paren
suffix:semicolon
DECL|member|open_close_ll
r_void
(paren
op_star
id|open_close_ll
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_bool
id|open
)paren
suffix:semicolon
DECL|member|copy_to_card
r_void
(paren
op_star
id|copy_to_card
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|bufnum
comma
r_int
id|offset
comma
r_void
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
DECL|member|copy_from_card
r_void
(paren
op_star
id|copy_from_card
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|bufnum
comma
r_int
id|offset
comma
r_void
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
DECL|member|hw
)brace
id|hw
suffix:semicolon
DECL|member|mem_start
r_void
op_star
id|mem_start
suffix:semicolon
multiline_comment|/* pointer to ioremap&squot;ed MMIO */
)brace
suffix:semicolon
DECL|macro|ARCRESET
mdefine_line|#define ARCRESET(x)  (lp-&gt;hw.reset(dev, (x)))
DECL|macro|ACOMMAND
mdefine_line|#define ACOMMAND(x)  (lp-&gt;hw.command(dev, (x)))
DECL|macro|ASTATUS
mdefine_line|#define ASTATUS()    (lp-&gt;hw.status(dev))
DECL|macro|AINTMASK
mdefine_line|#define AINTMASK(x)  (lp-&gt;hw.intmask(dev, (x)))
DECL|macro|ARCOPEN
mdefine_line|#define ARCOPEN(x)   (lp-&gt;hw.open_close(dev, (x)))
macro_line|#if ARCNET_DEBUG_MAX &amp; D_SKB
r_void
id|arcnet_dump_skb
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_char
op_star
id|desc
)paren
suffix:semicolon
macro_line|#else
DECL|macro|arcnet_dump_skb
mdefine_line|#define arcnet_dump_skb(dev,skb,desc) ;
macro_line|#endif
macro_line|#if (ARCNET_DEBUG_MAX &amp; D_RX) || (ARCNET_DEBUG_MAX &amp; D_TX)
r_void
id|arcnet_dump_packet
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|bufnum
comma
r_char
op_star
id|desc
)paren
suffix:semicolon
macro_line|#else
DECL|macro|arcnet_dump_packet
mdefine_line|#define arcnet_dump_packet(dev, bufnum, desc) ;
macro_line|#endif
r_void
id|arcnet_unregister_proto
c_func
(paren
r_struct
id|ArcProto
op_star
id|proto
)paren
suffix:semicolon
r_void
id|arcnet_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_void
id|arcdev_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|arcnet_rx
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|bufnum
)paren
suffix:semicolon
r_void
id|arcnet_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|arcnet_rfc1201_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|arcnet_rfc1051_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|arcnet_raw_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|com90xx_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
macro_line|#endif&t;&t;&t;&t;/* _LINUX_ARCDEVICE_H */
eof
