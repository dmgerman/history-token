multiline_comment|/* $Id: icn.h,v 1.30.6.5 2001/09/23 22:24:55 kai Exp $&n; *&n; * ISDN lowlevel-module for the ICN active ISDN-Card.&n; *&n; * Copyright 1994 by Fritz Elfert (fritz@isdn4linux.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#ifndef icn_h
DECL|macro|icn_h
mdefine_line|#define icn_h
DECL|macro|ICN_IOCTL_SETMMIO
mdefine_line|#define ICN_IOCTL_SETMMIO   0
DECL|macro|ICN_IOCTL_GETMMIO
mdefine_line|#define ICN_IOCTL_GETMMIO   1
DECL|macro|ICN_IOCTL_SETPORT
mdefine_line|#define ICN_IOCTL_SETPORT   2
DECL|macro|ICN_IOCTL_GETPORT
mdefine_line|#define ICN_IOCTL_GETPORT   3
DECL|macro|ICN_IOCTL_LOADBOOT
mdefine_line|#define ICN_IOCTL_LOADBOOT  4
DECL|macro|ICN_IOCTL_LOADPROTO
mdefine_line|#define ICN_IOCTL_LOADPROTO 5
DECL|macro|ICN_IOCTL_LEASEDCFG
mdefine_line|#define ICN_IOCTL_LEASEDCFG 6
DECL|macro|ICN_IOCTL_GETDOUBLE
mdefine_line|#define ICN_IOCTL_GETDOUBLE 7
DECL|macro|ICN_IOCTL_DEBUGVAR
mdefine_line|#define ICN_IOCTL_DEBUGVAR  8
DECL|macro|ICN_IOCTL_ADDCARD
mdefine_line|#define ICN_IOCTL_ADDCARD   9
multiline_comment|/* Struct for adding new cards */
DECL|struct|icn_cdef
r_typedef
r_struct
id|icn_cdef
(brace
DECL|member|port
r_int
id|port
suffix:semicolon
DECL|member|id1
r_char
id|id1
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|id2
r_char
id|id2
(braket
l_int|10
)braket
suffix:semicolon
DECL|typedef|icn_cdef
)brace
id|icn_cdef
suffix:semicolon
macro_line|#if defined(__KERNEL__) || defined(__DEBUGVAR__)
macro_line|#ifdef __KERNEL__
multiline_comment|/* Kernel includes */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/isdnif.h&gt;
macro_line|#endif                          /* __KERNEL__ */
multiline_comment|/* some useful macros for debugging */
macro_line|#ifdef ICN_DEBUG_PORT
DECL|macro|OUTB_P
mdefine_line|#define OUTB_P(v,p) {printk(KERN_DEBUG &quot;icn: outb_p(0x%02x,0x%03x)&bslash;n&quot;,v,p); outb_p(v,p);}
macro_line|#else
DECL|macro|OUTB_P
mdefine_line|#define OUTB_P outb
macro_line|#endif
multiline_comment|/* Defaults for Port-Address and shared-memory */
DECL|macro|ICN_BASEADDR
mdefine_line|#define ICN_BASEADDR 0x320
DECL|macro|ICN_PORTLEN
mdefine_line|#define ICN_PORTLEN (0x04)
DECL|macro|ICN_MEMADDR
mdefine_line|#define ICN_MEMADDR 0x0d0000
DECL|macro|ICN_FLAGS_B1ACTIVE
mdefine_line|#define ICN_FLAGS_B1ACTIVE 1    /* B-Channel-1 is open                     */
DECL|macro|ICN_FLAGS_B2ACTIVE
mdefine_line|#define ICN_FLAGS_B2ACTIVE 2    /* B-Channel-2 is open                     */
DECL|macro|ICN_FLAGS_RUNNING
mdefine_line|#define ICN_FLAGS_RUNNING  4    /* Cards driver activated                  */
DECL|macro|ICN_FLAGS_RBTIMER
mdefine_line|#define ICN_FLAGS_RBTIMER  8    /* cyclic scheduling of B-Channel-poll     */
DECL|macro|ICN_BOOT_TIMEOUT1
mdefine_line|#define ICN_BOOT_TIMEOUT1  (HZ) /* Delay for Boot-download (jiffies)       */
DECL|macro|ICN_CHANLOCK_DELAY
mdefine_line|#define ICN_CHANLOCK_DELAY (HZ/10)&t;/* Delay for Channel-mapping (jiffies)     */
DECL|macro|ICN_TIMER_BCREAD
mdefine_line|#define ICN_TIMER_BCREAD (HZ/100)&t;/* B-Channel poll-cycle                    */
DECL|macro|ICN_TIMER_DCREAD
mdefine_line|#define ICN_TIMER_DCREAD (HZ/2) /* D-Channel poll-cycle                    */
DECL|macro|ICN_CODE_STAGE1
mdefine_line|#define ICN_CODE_STAGE1 4096    /* Size of bootcode                        */
DECL|macro|ICN_CODE_STAGE2
mdefine_line|#define ICN_CODE_STAGE2 65536   /* Size of protocol-code                   */
DECL|macro|ICN_MAX_SQUEUE
mdefine_line|#define ICN_MAX_SQUEUE 8000     /* Max. outstanding send-data (2* hw-buf.) */
DECL|macro|ICN_FRAGSIZE
mdefine_line|#define ICN_FRAGSIZE (250)      /* Max. size of send-fragments             */
DECL|macro|ICN_BCH
mdefine_line|#define ICN_BCH 2               /* Number of supported channels per card   */
multiline_comment|/* type-definitions for accessing the mmap-io-areas */
DECL|macro|SHM_DCTL_OFFSET
mdefine_line|#define SHM_DCTL_OFFSET (0)     /* Offset to data-controlstructures in shm */
DECL|macro|SHM_CCTL_OFFSET
mdefine_line|#define SHM_CCTL_OFFSET (0x1d2) /* Offset to comm-controlstructures in shm */
DECL|macro|SHM_CBUF_OFFSET
mdefine_line|#define SHM_CBUF_OFFSET (0x200) /* Offset to comm-buffers in shm           */
DECL|macro|SHM_DBUF_OFFSET
mdefine_line|#define SHM_DBUF_OFFSET (0x2000)&t;/* Offset to data-buffers in shm           */
multiline_comment|/*&n; * Layout of card&squot;s data buffers&n; */
r_typedef
r_struct
(brace
DECL|member|length
r_int
r_char
id|length
suffix:semicolon
multiline_comment|/* Bytecount of fragment (max 250)    */
DECL|member|endflag
r_int
r_char
id|endflag
suffix:semicolon
multiline_comment|/* 0=last frag., 0xff=frag. continued */
DECL|member|data
r_int
r_char
id|data
(braket
id|ICN_FRAGSIZE
)braket
suffix:semicolon
multiline_comment|/* The data                           */
multiline_comment|/* Fill to 256 bytes */
DECL|member|unused
r_char
id|unused
(braket
l_int|0x100
op_minus
id|ICN_FRAGSIZE
op_minus
l_int|2
)braket
suffix:semicolon
DECL|typedef|frag_buf
)brace
id|frag_buf
suffix:semicolon
multiline_comment|/*&n; * Layout of card&squot;s shared memory&n; */
r_typedef
r_union
(brace
r_struct
(brace
DECL|member|scns
r_int
r_char
id|scns
suffix:semicolon
multiline_comment|/* Index to free SendFrag.             */
DECL|member|scnr
r_int
r_char
id|scnr
suffix:semicolon
multiline_comment|/* Index to active SendFrag   READONLY */
DECL|member|ecns
r_int
r_char
id|ecns
suffix:semicolon
multiline_comment|/* Index to free RcvFrag.     READONLY */
DECL|member|ecnr
r_int
r_char
id|ecnr
suffix:semicolon
multiline_comment|/* Index to valid RcvFrag              */
DECL|member|unused
r_char
id|unused
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|fuell1
r_int
r_int
id|fuell1
suffix:semicolon
multiline_comment|/* Internal Buf Bytecount              */
DECL|member|data_control
)brace
id|data_control
suffix:semicolon
r_struct
(brace
DECL|member|unused
r_char
id|unused
(braket
id|SHM_CCTL_OFFSET
)braket
suffix:semicolon
DECL|member|iopc_i
r_int
r_char
id|iopc_i
suffix:semicolon
multiline_comment|/* Read-Ptr Status-Queue      READONLY */
DECL|member|iopc_o
r_int
r_char
id|iopc_o
suffix:semicolon
multiline_comment|/* Write-Ptr Status-Queue              */
DECL|member|pcio_i
r_int
r_char
id|pcio_i
suffix:semicolon
multiline_comment|/* Write-Ptr Command-Queue             */
DECL|member|pcio_o
r_int
r_char
id|pcio_o
suffix:semicolon
multiline_comment|/* Read-Ptr Command Queue     READONLY */
DECL|member|comm_control
)brace
id|comm_control
suffix:semicolon
r_struct
(brace
DECL|member|unused
r_char
id|unused
(braket
id|SHM_CBUF_OFFSET
)braket
suffix:semicolon
DECL|member|pcio_buf
r_int
r_char
id|pcio_buf
(braket
l_int|0x100
)braket
suffix:semicolon
multiline_comment|/* Ring-Buffer Command-Queue           */
DECL|member|iopc_buf
r_int
r_char
id|iopc_buf
(braket
l_int|0x100
)braket
suffix:semicolon
multiline_comment|/* Ring-Buffer Status-Queue            */
DECL|member|comm_buffers
)brace
id|comm_buffers
suffix:semicolon
r_struct
(brace
DECL|member|unused
r_char
id|unused
(braket
id|SHM_DBUF_OFFSET
)braket
suffix:semicolon
DECL|member|receive_buf
id|frag_buf
id|receive_buf
(braket
l_int|0x10
)braket
suffix:semicolon
DECL|member|send_buf
id|frag_buf
id|send_buf
(braket
l_int|0x10
)braket
suffix:semicolon
DECL|member|data_buffers
)brace
id|data_buffers
suffix:semicolon
DECL|typedef|icn_shmem
)brace
id|icn_shmem
suffix:semicolon
multiline_comment|/*&n; * Per card driver data&n; */
DECL|struct|icn_card
r_typedef
r_struct
id|icn_card
(brace
DECL|member|next
r_struct
id|icn_card
op_star
id|next
suffix:semicolon
multiline_comment|/* Pointer to next device struct    */
DECL|member|other
r_struct
id|icn_card
op_star
id|other
suffix:semicolon
multiline_comment|/* Pointer to other card for ICN4B  */
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
multiline_comment|/* Base-port-address                */
DECL|member|myid
r_int
id|myid
suffix:semicolon
multiline_comment|/* Driver-Nr. assigned by linklevel */
DECL|member|rvalid
r_int
id|rvalid
suffix:semicolon
multiline_comment|/* IO-portregion has been requested */
DECL|member|leased
r_int
id|leased
suffix:semicolon
multiline_comment|/* Flag: This Adapter is connected  */
multiline_comment|/*       to a leased line           */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Statusflags                      */
DECL|member|doubleS0
r_int
id|doubleS0
suffix:semicolon
multiline_comment|/* Flag: ICN4B                      */
DECL|member|secondhalf
r_int
id|secondhalf
suffix:semicolon
multiline_comment|/* Flag: Second half of a doubleS0  */
DECL|member|fw_rev
r_int
id|fw_rev
suffix:semicolon
multiline_comment|/* Firmware revision loaded         */
DECL|member|ptype
r_int
id|ptype
suffix:semicolon
multiline_comment|/* Protocol type (1TR6 or Euro)     */
DECL|member|st_timer
r_struct
id|timer_list
id|st_timer
suffix:semicolon
multiline_comment|/* Timer for Status-Polls           */
DECL|member|rb_timer
r_struct
id|timer_list
id|rb_timer
suffix:semicolon
multiline_comment|/* Timer for B-Channel-Polls        */
DECL|member|rcvbuf
id|u_char
id|rcvbuf
(braket
id|ICN_BCH
)braket
(braket
l_int|4096
)braket
suffix:semicolon
multiline_comment|/* B-Channel-Receive-Buffers        */
DECL|member|rcvidx
r_int
id|rcvidx
(braket
id|ICN_BCH
)braket
suffix:semicolon
multiline_comment|/* Index for above buffers          */
DECL|member|l2_proto
r_int
id|l2_proto
(braket
id|ICN_BCH
)braket
suffix:semicolon
multiline_comment|/* Current layer-2-protocol         */
DECL|member|interface
id|isdn_if
id|interface
suffix:semicolon
multiline_comment|/* Interface to upper layer         */
DECL|member|iptr
r_int
id|iptr
suffix:semicolon
multiline_comment|/* Index to imsg-buffer             */
DECL|member|imsg
r_char
id|imsg
(braket
l_int|60
)braket
suffix:semicolon
multiline_comment|/* Internal buf for status-parsing  */
DECL|member|msg_buf
r_char
id|msg_buf
(braket
l_int|2048
)braket
suffix:semicolon
multiline_comment|/* Buffer for status-messages       */
DECL|member|msg_buf_write
r_char
op_star
id|msg_buf_write
suffix:semicolon
multiline_comment|/* Writepointer for statusbuffer    */
DECL|member|msg_buf_read
r_char
op_star
id|msg_buf_read
suffix:semicolon
multiline_comment|/* Readpointer for statusbuffer     */
DECL|member|msg_buf_end
r_char
op_star
id|msg_buf_end
suffix:semicolon
multiline_comment|/* Pointer to end of statusbuffer   */
DECL|member|sndcount
r_int
id|sndcount
(braket
id|ICN_BCH
)braket
suffix:semicolon
multiline_comment|/* Byte-counters for B-Ch.-send     */
DECL|member|xlen
r_int
id|xlen
(braket
id|ICN_BCH
)braket
suffix:semicolon
multiline_comment|/* Byte-counters/Flags for sent-ACK */
DECL|member|xskb
r_struct
id|sk_buff
op_star
id|xskb
(braket
id|ICN_BCH
)braket
suffix:semicolon
multiline_comment|/* Current transmitted skb          */
r_struct
id|sk_buff_head
DECL|member|spqueue
id|spqueue
(braket
id|ICN_BCH
)braket
suffix:semicolon
multiline_comment|/* Sendqueue                        */
DECL|member|regname
r_char
id|regname
(braket
l_int|35
)braket
suffix:semicolon
multiline_comment|/* Name used for request_region     */
DECL|member|xmit_lock
id|u_char
id|xmit_lock
(braket
id|ICN_BCH
)braket
suffix:semicolon
multiline_comment|/* Semaphore for pollbchan_send()   */
DECL|typedef|icn_card
)brace
id|icn_card
suffix:semicolon
multiline_comment|/*&n; * Main driver data&n; */
DECL|struct|icn_dev
r_typedef
r_struct
id|icn_dev
(brace
DECL|member|memaddr
r_int
r_int
id|memaddr
suffix:semicolon
multiline_comment|/* Address of memory mapped buffers */
DECL|member|shmem
id|icn_shmem
op_star
id|shmem
suffix:semicolon
multiline_comment|/* Pointer to memory-mapped-buffers */
DECL|member|mvalid
r_int
id|mvalid
suffix:semicolon
multiline_comment|/* IO-shmem has been requested      */
DECL|member|channel
r_int
id|channel
suffix:semicolon
multiline_comment|/* Currently mapped channel         */
DECL|member|mcard
r_struct
id|icn_card
op_star
id|mcard
suffix:semicolon
multiline_comment|/* Currently mapped card            */
DECL|member|chanlock
r_int
id|chanlock
suffix:semicolon
multiline_comment|/* Semaphore for channel-mapping    */
DECL|member|firstload
r_int
id|firstload
suffix:semicolon
multiline_comment|/* Flag: firmware never loaded      */
DECL|typedef|icn_dev
)brace
id|icn_dev
suffix:semicolon
DECL|typedef|icn_devptr
r_typedef
id|icn_dev
op_star
id|icn_devptr
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|variable|cards
r_static
id|icn_card
op_star
id|cards
op_assign
(paren
id|icn_card
op_star
)paren
l_int|0
suffix:semicolon
DECL|variable|chan2bank
r_static
id|u_char
id|chan2bank
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|4
comma
l_int|8
comma
l_int|12
)brace
suffix:semicolon
multiline_comment|/* for icn_map_channel() */
DECL|variable|dev
r_static
id|icn_dev
id|dev
suffix:semicolon
macro_line|#endif                          /* __KERNEL__ */
multiline_comment|/* Utility-Macros */
multiline_comment|/* Macros for accessing ports */
DECL|macro|ICN_CFG
mdefine_line|#define ICN_CFG    (card-&gt;port)
DECL|macro|ICN_MAPRAM
mdefine_line|#define ICN_MAPRAM (card-&gt;port+1)
DECL|macro|ICN_RUN
mdefine_line|#define ICN_RUN    (card-&gt;port+2)
DECL|macro|ICN_BANK
mdefine_line|#define ICN_BANK   (card-&gt;port+3)
multiline_comment|/* Return true, if there is a free transmit-buffer */
DECL|macro|sbfree
mdefine_line|#define sbfree (((readb(&amp;dev.shmem-&gt;data_control.scns)+1) &amp; 0xf) != &bslash;&n;&t;&t;readb(&amp;dev.shmem-&gt;data_control.scnr))
multiline_comment|/* Switch to next transmit-buffer */
DECL|macro|sbnext
mdefine_line|#define sbnext (writeb((readb(&amp;dev.shmem-&gt;data_control.scns)+1) &amp; 0xf, &bslash;&n;&t;&t;       &amp;dev.shmem-&gt;data_control.scns))
multiline_comment|/* Shortcuts for transmit-buffer-access */
DECL|macro|sbuf_n
mdefine_line|#define sbuf_n dev.shmem-&gt;data_control.scns
DECL|macro|sbuf_d
mdefine_line|#define sbuf_d dev.shmem-&gt;data_buffers.send_buf[readb(&amp;sbuf_n)].data
DECL|macro|sbuf_l
mdefine_line|#define sbuf_l dev.shmem-&gt;data_buffers.send_buf[readb(&amp;sbuf_n)].length
DECL|macro|sbuf_f
mdefine_line|#define sbuf_f dev.shmem-&gt;data_buffers.send_buf[readb(&amp;sbuf_n)].endflag
multiline_comment|/* Return true, if there is receive-data is available */
DECL|macro|rbavl
mdefine_line|#define rbavl  (readb(&amp;dev.shmem-&gt;data_control.ecnr) != &bslash;&n;&t;&t;readb(&amp;dev.shmem-&gt;data_control.ecns))
multiline_comment|/* Switch to next receive-buffer */
DECL|macro|rbnext
mdefine_line|#define rbnext (writeb((readb(&amp;dev.shmem-&gt;data_control.ecnr)+1) &amp; 0xf, &bslash;&n;&t;&t;       &amp;dev.shmem-&gt;data_control.ecnr))
multiline_comment|/* Shortcuts for receive-buffer-access */
DECL|macro|rbuf_n
mdefine_line|#define rbuf_n dev.shmem-&gt;data_control.ecnr
DECL|macro|rbuf_d
mdefine_line|#define rbuf_d dev.shmem-&gt;data_buffers.receive_buf[readb(&amp;rbuf_n)].data
DECL|macro|rbuf_l
mdefine_line|#define rbuf_l dev.shmem-&gt;data_buffers.receive_buf[readb(&amp;rbuf_n)].length
DECL|macro|rbuf_f
mdefine_line|#define rbuf_f dev.shmem-&gt;data_buffers.receive_buf[readb(&amp;rbuf_n)].endflag
multiline_comment|/* Shortcuts for command-buffer-access */
DECL|macro|cmd_o
mdefine_line|#define cmd_o (dev.shmem-&gt;comm_control.pcio_o)
DECL|macro|cmd_i
mdefine_line|#define cmd_i (dev.shmem-&gt;comm_control.pcio_i)
multiline_comment|/* Return free space in command-buffer */
DECL|macro|cmd_free
mdefine_line|#define cmd_free ((readb(&amp;cmd_i)&gt;=readb(&amp;cmd_o))? &bslash;&n;&t;&t;  0x100-readb(&amp;cmd_i)+readb(&amp;cmd_o): &bslash;&n;&t;&t;  readb(&amp;cmd_o)-readb(&amp;cmd_i))
multiline_comment|/* Shortcuts for message-buffer-access */
DECL|macro|msg_o
mdefine_line|#define msg_o (dev.shmem-&gt;comm_control.iopc_o)
DECL|macro|msg_i
mdefine_line|#define msg_i (dev.shmem-&gt;comm_control.iopc_i)
multiline_comment|/* Return length of Message, if avail. */
DECL|macro|msg_avail
mdefine_line|#define msg_avail ((readb(&amp;msg_o)&gt;readb(&amp;msg_i))? &bslash;&n;&t;&t;   0x100-readb(&amp;msg_o)+readb(&amp;msg_i): &bslash;&n;&t;&t;   readb(&amp;msg_i)-readb(&amp;msg_o))
DECL|macro|CID
mdefine_line|#define CID (card-&gt;interface.id)
macro_line|#endif                          /* defined(__KERNEL__) || defined(__DEBUGVAR__) */
macro_line|#endif                          /* icn_h */
eof
