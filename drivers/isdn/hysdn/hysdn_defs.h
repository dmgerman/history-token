multiline_comment|/* $Id: hysdn_defs.h,v 1.5.6.3 2001/09/23 22:24:54 kai Exp $&n; *&n; * Linux driver for HYSDN cards&n; * global definitions and exported vars and functions.&n; *&n; * Author    Werner Cornelius (werner@titro.de) for Hypercope GmbH&n; * Copyright 1999 by Werner Cornelius (werner@titro.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#ifndef HYSDN_DEFS_H
DECL|macro|HYSDN_DEFS_H
mdefine_line|#define HYSDN_DEFS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/hysdn_if.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
multiline_comment|/****************************/
multiline_comment|/* storage type definitions */
multiline_comment|/****************************/
DECL|macro|uchar
mdefine_line|#define uchar unsigned char
DECL|macro|uint
mdefine_line|#define uint unsigned int
DECL|macro|ulong
mdefine_line|#define ulong unsigned long
DECL|macro|word
mdefine_line|#define word unsigned short
macro_line|#include &quot;ince1pc.h&quot;
macro_line|#ifdef CONFIG_HYSDN_CAPI
macro_line|#include &lt;linux/capi.h&gt;
macro_line|#include &lt;linux/isdn/capicmd.h&gt;
macro_line|#include &lt;linux/isdn/capiutil.h&gt;
macro_line|#include &lt;linux/isdn/capilli.h&gt;
multiline_comment|/***************************/
multiline_comment|/*   CAPI-Profile values.  */
multiline_comment|/***************************/
DECL|macro|GLOBAL_OPTION_INTERNAL_CONTROLLER
mdefine_line|#define GLOBAL_OPTION_INTERNAL_CONTROLLER 0x0001
DECL|macro|GLOBAL_OPTION_EXTERNAL_CONTROLLER
mdefine_line|#define GLOBAL_OPTION_EXTERNAL_CONTROLLER 0x0002
DECL|macro|GLOBAL_OPTION_HANDSET
mdefine_line|#define GLOBAL_OPTION_HANDSET             0x0004
DECL|macro|GLOBAL_OPTION_DTMF
mdefine_line|#define GLOBAL_OPTION_DTMF                0x0008
DECL|macro|GLOBAL_OPTION_SUPPL_SERVICES
mdefine_line|#define GLOBAL_OPTION_SUPPL_SERVICES      0x0010
DECL|macro|GLOBAL_OPTION_CHANNEL_ALLOCATION
mdefine_line|#define GLOBAL_OPTION_CHANNEL_ALLOCATION  0x0020
DECL|macro|GLOBAL_OPTION_B_CHANNEL_OPERATION
mdefine_line|#define GLOBAL_OPTION_B_CHANNEL_OPERATION 0x0040
DECL|macro|B1_PROT_64KBIT_HDLC
mdefine_line|#define B1_PROT_64KBIT_HDLC        0x0001
DECL|macro|B1_PROT_64KBIT_TRANSPARENT
mdefine_line|#define B1_PROT_64KBIT_TRANSPARENT 0x0002
DECL|macro|B1_PROT_V110_ASYNCH
mdefine_line|#define B1_PROT_V110_ASYNCH        0x0004 
DECL|macro|B1_PROT_V110_SYNCH
mdefine_line|#define B1_PROT_V110_SYNCH         0x0008
DECL|macro|B1_PROT_T30
mdefine_line|#define B1_PROT_T30                0x0010
DECL|macro|B1_PROT_64KBIT_INV_HDLC
mdefine_line|#define B1_PROT_64KBIT_INV_HDLC    0x0020
DECL|macro|B1_PROT_56KBIT_TRANSPARENT
mdefine_line|#define B1_PROT_56KBIT_TRANSPARENT 0x0040
DECL|macro|B2_PROT_ISO7776
mdefine_line|#define B2_PROT_ISO7776            0x0001
DECL|macro|B2_PROT_TRANSPARENT
mdefine_line|#define B2_PROT_TRANSPARENT        0x0002
DECL|macro|B2_PROT_SDLC
mdefine_line|#define B2_PROT_SDLC               0x0004
DECL|macro|B2_PROT_LAPD
mdefine_line|#define B2_PROT_LAPD               0x0008
DECL|macro|B2_PROT_T30
mdefine_line|#define B2_PROT_T30                0x0010
DECL|macro|B2_PROT_PPP
mdefine_line|#define B2_PROT_PPP                0x0020
DECL|macro|B2_PROT_TRANSPARENT_IGNORE_B1_FRAMING_ERRORS
mdefine_line|#define B2_PROT_TRANSPARENT_IGNORE_B1_FRAMING_ERRORS 0x0040
DECL|macro|B3_PROT_TRANSPARENT
mdefine_line|#define B3_PROT_TRANSPARENT        0x0001
DECL|macro|B3_PROT_T90NL
mdefine_line|#define B3_PROT_T90NL              0x0002
DECL|macro|B3_PROT_ISO8208
mdefine_line|#define B3_PROT_ISO8208            0x0004
DECL|macro|B3_PROT_X25_DCE
mdefine_line|#define B3_PROT_X25_DCE            0x0008
DECL|macro|B3_PROT_T30
mdefine_line|#define B3_PROT_T30                0x0010
DECL|macro|B3_PROT_T30EXT
mdefine_line|#define B3_PROT_T30EXT             0x0020
DECL|macro|HYSDN_MAXVERSION
mdefine_line|#define HYSDN_MAXVERSION&t;&t;8
multiline_comment|/* Number of sendbuffers in CAPI-queue */
DECL|macro|HYSDN_MAX_CAPI_SKB
mdefine_line|#define HYSDN_MAX_CAPI_SKB             20
macro_line|#endif /* CONFIG_HYSDN_CAPI*/
multiline_comment|/************************************************/
multiline_comment|/* constants and bits for debugging/log outputs */
multiline_comment|/************************************************/
DECL|macro|LOG_MAX_LINELEN
mdefine_line|#define LOG_MAX_LINELEN 120
DECL|macro|DEB_OUT_SYSLOG
mdefine_line|#define DEB_OUT_SYSLOG  0x80000000&t;/* output to syslog instead of proc fs */
DECL|macro|LOG_MEM_ERR
mdefine_line|#define LOG_MEM_ERR     0x00000001&t;/* log memory errors like kmalloc failure */
DECL|macro|LOG_POF_OPEN
mdefine_line|#define LOG_POF_OPEN    0x00000010&t;/* log pof open and close activities */
DECL|macro|LOG_POF_RECORD
mdefine_line|#define LOG_POF_RECORD  0x00000020&t;/* log pof record parser */
DECL|macro|LOG_POF_WRITE
mdefine_line|#define LOG_POF_WRITE   0x00000040&t;/* log detailed pof write operation */
DECL|macro|LOG_POF_CARD
mdefine_line|#define LOG_POF_CARD    0x00000080&t;/* log pof related card functions */
DECL|macro|LOG_CNF_LINE
mdefine_line|#define LOG_CNF_LINE    0x00000100&t;/* all conf lines are put to procfs */
DECL|macro|LOG_CNF_DATA
mdefine_line|#define LOG_CNF_DATA    0x00000200&t;/* non comment conf lines are shown with channel */
DECL|macro|LOG_CNF_MISC
mdefine_line|#define LOG_CNF_MISC    0x00000400&t;/* additional conf line debug outputs */
DECL|macro|LOG_SCHED_ASYN
mdefine_line|#define LOG_SCHED_ASYN  0x00001000&t;/* debug schedulers async tx routines */
DECL|macro|LOG_PROC_OPEN
mdefine_line|#define LOG_PROC_OPEN   0x00100000&t;/* open and close from procfs are logged */
DECL|macro|LOG_PROC_ALL
mdefine_line|#define LOG_PROC_ALL    0x00200000&t;/* all actions from procfs are logged */
DECL|macro|LOG_NET_INIT
mdefine_line|#define LOG_NET_INIT    0x00010000&t;/* network init and deinit logging */
DECL|macro|DEF_DEB_FLAGS
mdefine_line|#define DEF_DEB_FLAGS   0x7fff000f&t;/* everything is logged to procfs */
multiline_comment|/**********************************/
multiline_comment|/* proc filesystem name constants */
multiline_comment|/**********************************/
DECL|macro|PROC_SUBDIR_NAME
mdefine_line|#define PROC_SUBDIR_NAME &quot;hysdn&quot;
DECL|macro|PROC_CONF_BASENAME
mdefine_line|#define PROC_CONF_BASENAME &quot;cardconf&quot;
DECL|macro|PROC_LOG_BASENAME
mdefine_line|#define PROC_LOG_BASENAME &quot;cardlog&quot;
multiline_comment|/***********************************/
multiline_comment|/* PCI 32 bit parms for IO and MEM */
multiline_comment|/***********************************/
DECL|macro|PCI_REG_PLX_MEM_BASE
mdefine_line|#define PCI_REG_PLX_MEM_BASE    0
DECL|macro|PCI_REG_PLX_IO_BASE
mdefine_line|#define PCI_REG_PLX_IO_BASE     1
DECL|macro|PCI_REG_MEMORY_BASE
mdefine_line|#define PCI_REG_MEMORY_BASE     3
multiline_comment|/**************/
multiline_comment|/* card types */
multiline_comment|/**************/
DECL|macro|BD_NONE
mdefine_line|#define BD_NONE         0U
DECL|macro|BD_PERFORMANCE
mdefine_line|#define BD_PERFORMANCE  1U
DECL|macro|BD_VALUE
mdefine_line|#define BD_VALUE        2U
DECL|macro|BD_PCCARD
mdefine_line|#define BD_PCCARD       3U
DECL|macro|BD_ERGO
mdefine_line|#define BD_ERGO         4U
DECL|macro|BD_METRO
mdefine_line|#define BD_METRO        5U
DECL|macro|BD_CHAMP2
mdefine_line|#define BD_CHAMP2       6U
DECL|macro|BD_PLEXUS
mdefine_line|#define BD_PLEXUS       7U
multiline_comment|/******************************************************/
multiline_comment|/* defined states for cards shown by reading cardconf */
multiline_comment|/******************************************************/
DECL|macro|CARD_STATE_UNUSED
mdefine_line|#define CARD_STATE_UNUSED   0&t;/* never been used or booted */
DECL|macro|CARD_STATE_BOOTING
mdefine_line|#define CARD_STATE_BOOTING  1&t;/* booting is in progress */
DECL|macro|CARD_STATE_BOOTERR
mdefine_line|#define CARD_STATE_BOOTERR  2&t;/* a previous boot was aborted */
DECL|macro|CARD_STATE_RUN
mdefine_line|#define CARD_STATE_RUN      3&t;/* card is active */
multiline_comment|/*******************************/
multiline_comment|/* defines for error_log_state */
multiline_comment|/*******************************/
DECL|macro|ERRLOG_STATE_OFF
mdefine_line|#define ERRLOG_STATE_OFF   0&t;/* error log is switched off, nothing to do */
DECL|macro|ERRLOG_STATE_ON
mdefine_line|#define ERRLOG_STATE_ON    1&t;/* error log is switched on, wait for data */
DECL|macro|ERRLOG_STATE_START
mdefine_line|#define ERRLOG_STATE_START 2&t;/* start error logging */
DECL|macro|ERRLOG_STATE_STOP
mdefine_line|#define ERRLOG_STATE_STOP  3&t;/* stop error logging */
multiline_comment|/*******************************/
multiline_comment|/* data structure for one card */
multiline_comment|/*******************************/
DECL|struct|HYSDN_CARD
r_typedef
r_struct
id|HYSDN_CARD
(brace
multiline_comment|/* general variables for the cards */
DECL|member|myid
r_int
id|myid
suffix:semicolon
multiline_comment|/* own driver card id */
DECL|member|bus
id|uchar
id|bus
suffix:semicolon
multiline_comment|/* pci bus the card is connected to */
DECL|member|devfn
id|uchar
id|devfn
suffix:semicolon
multiline_comment|/* slot+function bit encoded */
DECL|member|subsysid
id|word
id|subsysid
suffix:semicolon
multiline_comment|/* PCI subsystem id */
DECL|member|brdtype
id|uchar
id|brdtype
suffix:semicolon
multiline_comment|/* type of card */
DECL|member|bchans
id|uint
id|bchans
suffix:semicolon
multiline_comment|/* number of available B-channels */
DECL|member|faxchans
id|uint
id|faxchans
suffix:semicolon
multiline_comment|/* number of available fax-channels */
DECL|member|mac_addr
id|uchar
id|mac_addr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* MAC Address read from card */
DECL|member|irq
id|uint
id|irq
suffix:semicolon
multiline_comment|/* interrupt number */
DECL|member|iobase
id|uint
id|iobase
suffix:semicolon
multiline_comment|/* IO-port base address */
DECL|member|plxbase
id|ulong
id|plxbase
suffix:semicolon
multiline_comment|/* PLX memory base */
DECL|member|membase
id|ulong
id|membase
suffix:semicolon
multiline_comment|/* DPRAM memory base */
DECL|member|memend
id|ulong
id|memend
suffix:semicolon
multiline_comment|/* DPRAM memory end */
DECL|member|dpram
r_void
op_star
id|dpram
suffix:semicolon
multiline_comment|/* mapped dpram */
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/* actual state of card -&gt; CARD_STATE_** */
DECL|member|next
r_struct
id|HYSDN_CARD
op_star
id|next
suffix:semicolon
multiline_comment|/* pointer to next card */
multiline_comment|/* data areas for the /proc file system */
DECL|member|proclog
r_void
op_star
id|proclog
suffix:semicolon
multiline_comment|/* pointer to proclog filesystem specific data */
DECL|member|procconf
r_void
op_star
id|procconf
suffix:semicolon
multiline_comment|/* pointer to procconf filesystem specific data */
multiline_comment|/* debugging and logging */
DECL|member|err_log_state
id|uchar
id|err_log_state
suffix:semicolon
multiline_comment|/* actual error log state of the card */
DECL|member|debug_flags
id|ulong
id|debug_flags
suffix:semicolon
multiline_comment|/* tells what should be debugged and where */
DECL|member|set_errlog_state
r_void
(paren
op_star
id|set_errlog_state
)paren
(paren
r_struct
id|HYSDN_CARD
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* interrupt handler + interrupt synchronisation */
DECL|member|irq_queue
r_struct
id|tq_struct
id|irq_queue
suffix:semicolon
multiline_comment|/* interrupt task queue */
DECL|member|irq_enabled
id|uchar
r_volatile
id|irq_enabled
suffix:semicolon
multiline_comment|/* interrupt enabled if != 0 */
DECL|member|hw_lock
id|uchar
r_volatile
id|hw_lock
suffix:semicolon
multiline_comment|/* hardware is currently locked -&gt; no access */
multiline_comment|/* boot process */
DECL|member|boot
r_void
op_star
id|boot
suffix:semicolon
multiline_comment|/* pointer to boot private data */
DECL|member|writebootimg
r_int
(paren
op_star
id|writebootimg
)paren
(paren
r_struct
id|HYSDN_CARD
op_star
comma
id|uchar
op_star
comma
id|ulong
)paren
suffix:semicolon
DECL|member|writebootseq
r_int
(paren
op_star
id|writebootseq
)paren
(paren
r_struct
id|HYSDN_CARD
op_star
comma
id|uchar
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|waitpofready
r_int
(paren
op_star
id|waitpofready
)paren
(paren
r_struct
id|HYSDN_CARD
op_star
)paren
suffix:semicolon
DECL|member|testram
r_int
(paren
op_star
id|testram
)paren
(paren
r_struct
id|HYSDN_CARD
op_star
)paren
suffix:semicolon
multiline_comment|/* scheduler for data transfer (only async parts) */
DECL|member|async_data
id|uchar
id|async_data
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* async data to be sent (normally for config) */
DECL|member|async_len
id|word
r_volatile
id|async_len
suffix:semicolon
multiline_comment|/* length of data to sent */
DECL|member|async_channel
id|word
r_volatile
id|async_channel
suffix:semicolon
multiline_comment|/* channel number for async transfer */
DECL|member|async_busy
r_int
r_volatile
id|async_busy
suffix:semicolon
multiline_comment|/* flag != 0 sending in progress */
DECL|member|net_tx_busy
r_int
r_volatile
id|net_tx_busy
suffix:semicolon
multiline_comment|/* a network packet tx is in progress */
multiline_comment|/* network interface */
DECL|member|netif
r_void
op_star
id|netif
suffix:semicolon
multiline_comment|/* pointer to network structure */
multiline_comment|/* init and deinit stopcard for booting, too */
DECL|member|stopcard
r_void
(paren
op_star
id|stopcard
)paren
(paren
r_struct
id|HYSDN_CARD
op_star
)paren
suffix:semicolon
DECL|member|releasehardware
r_void
(paren
op_star
id|releasehardware
)paren
(paren
r_struct
id|HYSDN_CARD
op_star
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HYSDN_CAPI
DECL|struct|hycapictrl_info
r_struct
id|hycapictrl_info
(brace
DECL|member|cardname
r_char
id|cardname
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|versionlen
r_int
id|versionlen
suffix:semicolon
DECL|member|versionbuf
r_char
id|versionbuf
(braket
l_int|1024
)braket
suffix:semicolon
DECL|member|version
r_char
op_star
id|version
(braket
id|HYSDN_MAXVERSION
)braket
suffix:semicolon
DECL|member|infobuf
r_char
id|infobuf
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* for function procinfo */
DECL|member|card
r_struct
id|HYSDN_CARD
op_star
id|card
suffix:semicolon
DECL|member|capi_ctrl
r_struct
id|capi_ctr
op_star
id|capi_ctrl
suffix:semicolon
DECL|member|skbs
r_struct
id|sk_buff
op_star
id|skbs
(braket
id|HYSDN_MAX_CAPI_SKB
)braket
suffix:semicolon
DECL|member|in_idx
DECL|member|out_idx
r_int
id|in_idx
comma
id|out_idx
suffix:semicolon
multiline_comment|/* indexes to buffer ring */
DECL|member|sk_count
r_int
id|sk_count
suffix:semicolon
multiline_comment|/* number of buffers currently in ring */
DECL|member|tx_skb
r_struct
id|sk_buff
op_star
id|tx_skb
suffix:semicolon
multiline_comment|/* buffer for tx operation */
DECL|member|ncci_head
r_struct
id|list_head
id|ncci_head
suffix:semicolon
DECL|member|hyctrlinfo
)brace
op_star
id|hyctrlinfo
suffix:semicolon
macro_line|#endif /* CONFIG_HYSDN_CAPI */
DECL|typedef|hysdn_card
)brace
id|hysdn_card
suffix:semicolon
macro_line|#ifdef CONFIG_HYSDN_CAPI
DECL|typedef|hycapictrl_info
r_typedef
r_struct
id|hycapictrl_info
id|hycapictrl_info
suffix:semicolon
macro_line|#endif /* CONFIG_HYSDN_CAPI */
multiline_comment|/*****************/
multiline_comment|/* exported vars */
multiline_comment|/*****************/
r_extern
r_int
id|cardmax
suffix:semicolon
multiline_comment|/* number of found cards */
r_extern
id|hysdn_card
op_star
id|card_root
suffix:semicolon
multiline_comment|/* pointer to first card */
multiline_comment|/*************************/
multiline_comment|/* im/exported functions */
multiline_comment|/*************************/
r_extern
r_int
id|printk
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_char
op_star
id|hysdn_getrev
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/* hysdn_procconf.c */
r_extern
r_int
id|hysdn_procconf_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* init proc config filesys */
r_extern
r_void
id|hysdn_procconf_release
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* deinit proc config filesys */
multiline_comment|/* hysdn_proclog.c */
r_extern
r_int
id|hysdn_proclog_init
c_func
(paren
id|hysdn_card
op_star
)paren
suffix:semicolon
multiline_comment|/* init proc log entry */
r_extern
r_void
id|hysdn_proclog_release
c_func
(paren
id|hysdn_card
op_star
)paren
suffix:semicolon
multiline_comment|/* deinit proc log entry */
r_extern
r_void
id|put_log_buffer
c_func
(paren
id|hysdn_card
op_star
comma
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/* output log data */
r_extern
r_void
id|hysdn_addlog
c_func
(paren
id|hysdn_card
op_star
comma
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
multiline_comment|/* output data to log */
r_extern
r_void
id|hysdn_card_errlog
c_func
(paren
id|hysdn_card
op_star
comma
id|tErrLogEntry
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* output card log */
multiline_comment|/* boardergo.c */
r_extern
r_int
id|ergo_inithardware
c_func
(paren
id|hysdn_card
op_star
id|card
)paren
suffix:semicolon
multiline_comment|/* get hardware -&gt; module init */
multiline_comment|/* hysdn_boot.c */
r_extern
r_int
id|pof_write_close
c_func
(paren
id|hysdn_card
op_star
)paren
suffix:semicolon
multiline_comment|/* close proc file after writing pof */
r_extern
r_int
id|pof_write_open
c_func
(paren
id|hysdn_card
op_star
comma
id|uchar
op_star
op_star
)paren
suffix:semicolon
multiline_comment|/* open proc file for writing pof */
r_extern
r_int
id|pof_write_buffer
c_func
(paren
id|hysdn_card
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* write boot data to card */
r_extern
r_int
id|EvalSysrTokData
c_func
(paren
id|hysdn_card
op_star
comma
id|uchar
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Check Sysready Token Data */
multiline_comment|/* hysdn_sched.c */
r_extern
r_int
id|hysdn_sched_tx
c_func
(paren
id|hysdn_card
op_star
comma
id|uchar
op_star
comma
id|word
r_volatile
op_star
comma
id|word
r_volatile
op_star
comma
id|word
)paren
suffix:semicolon
r_extern
r_int
id|hysdn_sched_rx
c_func
(paren
id|hysdn_card
op_star
comma
id|uchar
op_star
comma
id|word
comma
id|word
)paren
suffix:semicolon
r_extern
r_int
id|hysdn_tx_cfgline
c_func
(paren
id|hysdn_card
op_star
comma
id|uchar
op_star
comma
id|word
)paren
suffix:semicolon
multiline_comment|/* send one cfg line */
multiline_comment|/* hysdn_net.c */
r_extern
r_int
r_int
id|hynet_enable
suffix:semicolon
r_extern
r_char
op_star
id|hysdn_net_revision
suffix:semicolon
r_extern
r_int
id|hysdn_net_create
c_func
(paren
id|hysdn_card
op_star
)paren
suffix:semicolon
multiline_comment|/* create a new net device */
r_extern
r_int
id|hysdn_net_release
c_func
(paren
id|hysdn_card
op_star
)paren
suffix:semicolon
multiline_comment|/* delete the device */
r_extern
r_char
op_star
id|hysdn_net_getname
c_func
(paren
id|hysdn_card
op_star
)paren
suffix:semicolon
multiline_comment|/* get name of net interface */
r_extern
r_void
id|hysdn_tx_netack
c_func
(paren
id|hysdn_card
op_star
)paren
suffix:semicolon
multiline_comment|/* acknowledge a packet tx */
r_extern
r_struct
id|sk_buff
op_star
id|hysdn_tx_netget
c_func
(paren
id|hysdn_card
op_star
)paren
suffix:semicolon
multiline_comment|/* get next network packet */
r_extern
r_void
id|hysdn_rx_netpkt
c_func
(paren
id|hysdn_card
op_star
comma
id|uchar
op_star
comma
id|word
)paren
suffix:semicolon
multiline_comment|/* rxed packet from network */
macro_line|#ifdef CONFIG_HYSDN_CAPI
r_extern
r_int
r_int
id|hycapi_enable
suffix:semicolon
r_extern
r_struct
id|capi_driver_interface
op_star
id|hy_di
suffix:semicolon
r_extern
r_int
id|hycapi_capi_create
c_func
(paren
id|hysdn_card
op_star
)paren
suffix:semicolon
multiline_comment|/* create a new capi device */
r_extern
r_int
id|hycapi_capi_release
c_func
(paren
id|hysdn_card
op_star
)paren
suffix:semicolon
multiline_comment|/* delete the device */
r_extern
r_int
id|hycapi_capi_stop
c_func
(paren
id|hysdn_card
op_star
id|card
)paren
suffix:semicolon
multiline_comment|/* suspend */
r_extern
r_int
id|hycapi_load_firmware
c_func
(paren
r_struct
id|capi_ctr
op_star
comma
id|capiloaddata
op_star
)paren
suffix:semicolon
r_extern
r_void
id|hycapi_reset_ctr
c_func
(paren
r_struct
id|capi_ctr
op_star
)paren
suffix:semicolon
r_extern
r_void
id|hycapi_remove_ctr
c_func
(paren
r_struct
id|capi_ctr
op_star
)paren
suffix:semicolon
r_extern
r_void
id|hycapi_register_appl
c_func
(paren
r_struct
id|capi_ctr
op_star
comma
id|__u16
id|appl
comma
id|capi_register_params
op_star
)paren
suffix:semicolon
r_extern
r_void
id|hycapi_release_appl
c_func
(paren
r_struct
id|capi_ctr
op_star
comma
id|__u16
id|appl
)paren
suffix:semicolon
r_extern
id|u16
id|hycapi_send_message
c_func
(paren
r_struct
id|capi_ctr
op_star
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_char
op_star
id|hycapi_procinfo
c_func
(paren
r_struct
id|capi_ctr
op_star
)paren
suffix:semicolon
r_extern
r_int
id|hycapi_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_struct
id|capi_ctr
op_star
id|card
)paren
suffix:semicolon
r_extern
r_void
id|hycapi_rx_capipkt
c_func
(paren
id|hysdn_card
op_star
id|card
comma
id|uchar
op_star
id|buf
comma
id|word
id|len
)paren
suffix:semicolon
r_extern
r_void
id|hycapi_tx_capiack
c_func
(paren
id|hysdn_card
op_star
id|card
)paren
suffix:semicolon
r_extern
r_struct
id|sk_buff
op_star
id|hycapi_tx_capiget
c_func
(paren
id|hysdn_card
op_star
id|card
)paren
suffix:semicolon
r_extern
r_int
id|hycapi_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|hycapi_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_HYSDN_CAPI */
macro_line|#endif /* HYSDN_DEFS_H */
eof
