multiline_comment|/* $Id: scc.h,v 1.29 1997/04/02 14:56:45 jreuter Exp jreuter $ */
macro_line|#ifndef&t;_SCC_H
DECL|macro|_SCC_H
mdefine_line|#define&t;_SCC_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* selection of hardware types */
DECL|macro|PA0HZP
mdefine_line|#define PA0HZP&t;&t;0x00&t;/* hardware type for PA0HZP SCC card and compatible */
DECL|macro|EAGLE
mdefine_line|#define EAGLE&t;&t;0x01    /* hardware type for EAGLE card */
DECL|macro|PC100
mdefine_line|#define PC100&t;&t;0x02&t;/* hardware type for PC100 card */
DECL|macro|PRIMUS
mdefine_line|#define PRIMUS&t;&t;0x04&t;/* hardware type for PRIMUS-PC (DG9BL) card */
DECL|macro|DRSI
mdefine_line|#define DRSI&t;&t;0x08&t;/* hardware type for DRSI PC*Packet card */
DECL|macro|BAYCOM
mdefine_line|#define BAYCOM&t;&t;0x10&t;/* hardware type for BayCom (U)SCC */
multiline_comment|/* DEV ioctl() commands */
DECL|enum|SCC_ioctl_cmds
r_enum
id|SCC_ioctl_cmds
(brace
DECL|enumerator|SIOCSCCRESERVED
id|SIOCSCCRESERVED
op_assign
id|SIOCDEVPRIVATE
comma
DECL|enumerator|SIOCSCCCFG
id|SIOCSCCCFG
comma
DECL|enumerator|SIOCSCCINI
id|SIOCSCCINI
comma
DECL|enumerator|SIOCSCCCHANINI
id|SIOCSCCCHANINI
comma
DECL|enumerator|SIOCSCCSMEM
id|SIOCSCCSMEM
comma
DECL|enumerator|SIOCSCCGKISS
id|SIOCSCCGKISS
comma
DECL|enumerator|SIOCSCCSKISS
id|SIOCSCCSKISS
comma
DECL|enumerator|SIOCSCCGSTAT
id|SIOCSCCGSTAT
comma
DECL|enumerator|SIOCSCCCAL
id|SIOCSCCCAL
)brace
suffix:semicolon
multiline_comment|/* Device parameter control (from WAMPES) */
DECL|enum|L1_params
r_enum
id|L1_params
(brace
DECL|enumerator|PARAM_DATA
id|PARAM_DATA
comma
DECL|enumerator|PARAM_TXDELAY
id|PARAM_TXDELAY
comma
DECL|enumerator|PARAM_PERSIST
id|PARAM_PERSIST
comma
DECL|enumerator|PARAM_SLOTTIME
id|PARAM_SLOTTIME
comma
DECL|enumerator|PARAM_TXTAIL
id|PARAM_TXTAIL
comma
DECL|enumerator|PARAM_FULLDUP
id|PARAM_FULLDUP
comma
DECL|enumerator|PARAM_SOFTDCD
id|PARAM_SOFTDCD
comma
multiline_comment|/* was: PARAM_HW */
DECL|enumerator|PARAM_MUTE
id|PARAM_MUTE
comma
multiline_comment|/* ??? */
DECL|enumerator|PARAM_DTR
id|PARAM_DTR
comma
DECL|enumerator|PARAM_RTS
id|PARAM_RTS
comma
DECL|enumerator|PARAM_SPEED
id|PARAM_SPEED
comma
DECL|enumerator|PARAM_ENDDELAY
id|PARAM_ENDDELAY
comma
multiline_comment|/* ??? */
DECL|enumerator|PARAM_GROUP
id|PARAM_GROUP
comma
DECL|enumerator|PARAM_IDLE
id|PARAM_IDLE
comma
DECL|enumerator|PARAM_MIN
id|PARAM_MIN
comma
DECL|enumerator|PARAM_MAXKEY
id|PARAM_MAXKEY
comma
DECL|enumerator|PARAM_WAIT
id|PARAM_WAIT
comma
DECL|enumerator|PARAM_MAXDEFER
id|PARAM_MAXDEFER
comma
DECL|enumerator|PARAM_TX
id|PARAM_TX
comma
DECL|enumerator|PARAM_HWEVENT
id|PARAM_HWEVENT
op_assign
l_int|31
comma
DECL|enumerator|PARAM_RETURN
id|PARAM_RETURN
op_assign
l_int|255
multiline_comment|/* reset kiss mode */
)brace
suffix:semicolon
multiline_comment|/* fulldup parameter */
DECL|enum|FULLDUP_modes
r_enum
id|FULLDUP_modes
(brace
DECL|enumerator|KISS_DUPLEX_HALF
id|KISS_DUPLEX_HALF
comma
multiline_comment|/* normal CSMA operation */
DECL|enumerator|KISS_DUPLEX_FULL
id|KISS_DUPLEX_FULL
comma
multiline_comment|/* fullduplex, key down trx after transmission */
DECL|enumerator|KISS_DUPLEX_LINK
id|KISS_DUPLEX_LINK
comma
multiline_comment|/* fullduplex, key down trx after &squot;idletime&squot; sec */
DECL|enumerator|KISS_DUPLEX_OPTIMA
id|KISS_DUPLEX_OPTIMA
multiline_comment|/* fullduplex, let the protocol layer control the hw */
)brace
suffix:semicolon
multiline_comment|/* misc. parameters */
DECL|macro|TIMER_OFF
mdefine_line|#define TIMER_OFF&t;65535U&t;/* to switch off timers */
DECL|macro|NO_SUCH_PARAM
mdefine_line|#define NO_SUCH_PARAM&t;65534U&t;/* param not implemented */
multiline_comment|/* HWEVENT parameter */
DECL|enum|HWEVENT_opts
r_enum
id|HWEVENT_opts
(brace
DECL|enumerator|HWEV_DCD_ON
id|HWEV_DCD_ON
comma
DECL|enumerator|HWEV_DCD_OFF
id|HWEV_DCD_OFF
comma
DECL|enumerator|HWEV_ALL_SENT
id|HWEV_ALL_SENT
)brace
suffix:semicolon
multiline_comment|/* channel grouping */
DECL|macro|RXGROUP
mdefine_line|#define RXGROUP&t;&t;0100&t;/* if set, only tx when all channels clear */
DECL|macro|TXGROUP
mdefine_line|#define TXGROUP&t;&t;0200&t;/* if set, don&squot;t transmit simultaneously */
multiline_comment|/* Tx/Rx clock sources */
DECL|enum|CLOCK_sources
r_enum
id|CLOCK_sources
(brace
DECL|enumerator|CLK_DPLL
id|CLK_DPLL
comma
multiline_comment|/* normal halfduplex operation */
DECL|enumerator|CLK_EXTERNAL
id|CLK_EXTERNAL
comma
multiline_comment|/* external clocking (G3RUH/DF9IC modems) */
DECL|enumerator|CLK_DIVIDER
id|CLK_DIVIDER
comma
multiline_comment|/* Rx = DPLL, Tx = divider (fullduplex with */
multiline_comment|/* modems without clock regeneration */
DECL|enumerator|CLK_BRG
id|CLK_BRG
multiline_comment|/* experimental fullduplex mode with DPLL/BRG for */
multiline_comment|/* MODEMs without clock recovery */
)brace
suffix:semicolon
multiline_comment|/* Tx state */
DECL|enum|TX_state
r_enum
id|TX_state
(brace
DECL|enumerator|TXS_IDLE
id|TXS_IDLE
comma
multiline_comment|/* Transmitter off, no data pending */
DECL|enumerator|TXS_BUSY
id|TXS_BUSY
comma
multiline_comment|/* waiting for permission to send / tailtime */
DECL|enumerator|TXS_ACTIVE
id|TXS_ACTIVE
comma
multiline_comment|/* Transmitter on, sending data */
DECL|enumerator|TXS_NEWFRAME
id|TXS_NEWFRAME
comma
multiline_comment|/* reset CRC and send (next) frame */
DECL|enumerator|TXS_IDLE2
id|TXS_IDLE2
comma
multiline_comment|/* Transmitter on, no data pending */
DECL|enumerator|TXS_WAIT
id|TXS_WAIT
comma
multiline_comment|/* Waiting for Mintime to expire */
DECL|enumerator|TXS_TIMEOUT
id|TXS_TIMEOUT
multiline_comment|/* We had a transmission timeout */
)brace
suffix:semicolon
DECL|typedef|io_port
r_typedef
r_int
r_int
id|io_port
suffix:semicolon
multiline_comment|/* type definition for an &squot;io port address&squot; */
multiline_comment|/* SCC statistical information */
DECL|struct|scc_stat
r_struct
id|scc_stat
(brace
DECL|member|rxints
r_int
id|rxints
suffix:semicolon
multiline_comment|/* Receiver interrupts */
DECL|member|txints
r_int
id|txints
suffix:semicolon
multiline_comment|/* Transmitter interrupts */
DECL|member|exints
r_int
id|exints
suffix:semicolon
multiline_comment|/* External/status interrupts */
DECL|member|spints
r_int
id|spints
suffix:semicolon
multiline_comment|/* Special receiver interrupts */
DECL|member|txframes
r_int
id|txframes
suffix:semicolon
multiline_comment|/* Packets sent */
DECL|member|rxframes
r_int
id|rxframes
suffix:semicolon
multiline_comment|/* Number of Frames Actually Received */
DECL|member|rxerrs
r_int
id|rxerrs
suffix:semicolon
multiline_comment|/* CRC Errors */
DECL|member|txerrs
r_int
id|txerrs
suffix:semicolon
multiline_comment|/* KISS errors */
DECL|member|nospace
r_int
r_int
id|nospace
suffix:semicolon
multiline_comment|/* &quot;Out of buffers&quot; */
DECL|member|rx_over
r_int
r_int
id|rx_over
suffix:semicolon
multiline_comment|/* Receiver Overruns */
DECL|member|tx_under
r_int
r_int
id|tx_under
suffix:semicolon
multiline_comment|/* Transmitter Underruns */
DECL|member|tx_state
r_int
r_int
id|tx_state
suffix:semicolon
multiline_comment|/* Transmitter state */
DECL|member|tx_queued
r_int
id|tx_queued
suffix:semicolon
multiline_comment|/* tx frames enqueued */
DECL|member|maxqueue
r_int
r_int
id|maxqueue
suffix:semicolon
multiline_comment|/* allocated tx_buffers */
DECL|member|bufsize
r_int
r_int
id|bufsize
suffix:semicolon
multiline_comment|/* used buffersize */
)brace
suffix:semicolon
DECL|struct|scc_modem
r_struct
id|scc_modem
(brace
DECL|member|speed
r_int
id|speed
suffix:semicolon
multiline_comment|/* Line speed, bps */
DECL|member|clocksrc
r_char
id|clocksrc
suffix:semicolon
multiline_comment|/* 0 = DPLL, 1 = external, 2 = divider */
DECL|member|nrz
r_char
id|nrz
suffix:semicolon
multiline_comment|/* NRZ instead of NRZI */
)brace
suffix:semicolon
DECL|struct|scc_kiss_cmd
r_struct
id|scc_kiss_cmd
(brace
DECL|member|command
r_int
id|command
suffix:semicolon
multiline_comment|/* one of the KISS-Commands defined above */
DECL|member|param
r_int
id|param
suffix:semicolon
multiline_comment|/* KISS-Param */
)brace
suffix:semicolon
DECL|struct|scc_hw_config
r_struct
id|scc_hw_config
(brace
DECL|member|data_a
id|io_port
id|data_a
suffix:semicolon
multiline_comment|/* data port channel A */
DECL|member|ctrl_a
id|io_port
id|ctrl_a
suffix:semicolon
multiline_comment|/* control port channel A */
DECL|member|data_b
id|io_port
id|data_b
suffix:semicolon
multiline_comment|/* data port channel B */
DECL|member|ctrl_b
id|io_port
id|ctrl_b
suffix:semicolon
multiline_comment|/* control port channel B */
DECL|member|vector_latch
id|io_port
id|vector_latch
suffix:semicolon
multiline_comment|/* INTACK-Latch (#) */
DECL|member|special
id|io_port
id|special
suffix:semicolon
multiline_comment|/* special function port */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* irq */
DECL|member|clock
r_int
id|clock
suffix:semicolon
multiline_comment|/* clock */
DECL|member|option
r_char
id|option
suffix:semicolon
multiline_comment|/* command for function port */
DECL|member|brand
r_char
id|brand
suffix:semicolon
multiline_comment|/* hardware type */
DECL|member|escc
r_char
id|escc
suffix:semicolon
multiline_comment|/* use ext. features of a 8580/85180/85280 */
)brace
suffix:semicolon
multiline_comment|/* (#) only one INTACK latch allowed. */
DECL|struct|scc_mem_config
r_struct
id|scc_mem_config
(brace
DECL|member|dummy
r_int
r_int
id|dummy
suffix:semicolon
DECL|member|bufsize
r_int
r_int
id|bufsize
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|scc_calibrate
r_struct
id|scc_calibrate
(brace
DECL|member|time
r_int
r_int
id|time
suffix:semicolon
DECL|member|pattern
r_int
r_char
id|pattern
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|enumerator|TX_OFF
DECL|enumerator|TX_ON
r_enum
(brace
id|TX_OFF
comma
id|TX_ON
)brace
suffix:semicolon
multiline_comment|/* command for scc_key_trx() */
multiline_comment|/* Vector masks in RR2B */
DECL|macro|VECTOR_MASK
mdefine_line|#define VECTOR_MASK&t;0x06
DECL|macro|TXINT
mdefine_line|#define TXINT&t;&t;0x00
DECL|macro|EXINT
mdefine_line|#define EXINT&t;&t;0x02
DECL|macro|RXINT
mdefine_line|#define RXINT&t;&t;0x04
DECL|macro|SPINT
mdefine_line|#define SPINT&t;&t;0x06
macro_line|#ifdef CONFIG_SCC_DELAY
DECL|macro|Inb
mdefine_line|#define Inb(port)&t;inb_p(port)
DECL|macro|Outb
mdefine_line|#define Outb(port, val)&t;outb_p(val, port)
macro_line|#else
DECL|macro|Inb
mdefine_line|#define Inb(port)&t;inb(port)
DECL|macro|Outb
mdefine_line|#define Outb(port, val)&t;outb(val, port)
macro_line|#endif
multiline_comment|/* SCC channel control structure for KISS */
DECL|struct|scc_kiss
r_struct
id|scc_kiss
(brace
DECL|member|txdelay
r_int
r_char
id|txdelay
suffix:semicolon
multiline_comment|/* Transmit Delay 10 ms/cnt */
DECL|member|persist
r_int
r_char
id|persist
suffix:semicolon
multiline_comment|/* Persistence (0-255) as a % */
DECL|member|slottime
r_int
r_char
id|slottime
suffix:semicolon
multiline_comment|/* Delay to wait on persistence hit */
DECL|member|tailtime
r_int
r_char
id|tailtime
suffix:semicolon
multiline_comment|/* Delay after last byte written */
DECL|member|fulldup
r_int
r_char
id|fulldup
suffix:semicolon
multiline_comment|/* Full Duplex mode 0=CSMA 1=DUP 2=ALWAYS KEYED */
DECL|member|waittime
r_int
r_char
id|waittime
suffix:semicolon
multiline_comment|/* Waittime before any transmit attempt */
DECL|member|maxkeyup
r_int
r_int
id|maxkeyup
suffix:semicolon
multiline_comment|/* Maximum time to transmit (seconds) */
DECL|member|mintime
r_int
r_char
id|mintime
suffix:semicolon
multiline_comment|/* Minimal offtime after MAXKEYUP timeout (seconds) */
DECL|member|idletime
r_int
r_int
id|idletime
suffix:semicolon
multiline_comment|/* Maximum idle time in ALWAYS KEYED mode (seconds) */
DECL|member|maxdefer
r_int
r_int
id|maxdefer
suffix:semicolon
multiline_comment|/* Timer for CSMA channel busy limit */
DECL|member|tx_inhibit
r_int
r_char
id|tx_inhibit
suffix:semicolon
multiline_comment|/* Transmit is not allowed when set */
DECL|member|group
r_int
r_char
id|group
suffix:semicolon
multiline_comment|/* Group ID for AX.25 TX interlocking */
DECL|member|mode
r_int
r_char
id|mode
suffix:semicolon
multiline_comment|/* &squot;normal&squot; or &squot;hwctrl&squot; mode (unused) */
DECL|member|softdcd
r_int
r_char
id|softdcd
suffix:semicolon
multiline_comment|/* Use DPLL instead of DCD pin for carrier detect */
)brace
suffix:semicolon
multiline_comment|/* SCC channel structure */
DECL|struct|scc_channel
r_struct
id|scc_channel
(brace
DECL|member|init
r_int
id|init
suffix:semicolon
multiline_comment|/* channel exists? */
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* link to device control structure */
DECL|member|dev_stat
r_struct
id|net_device_stats
id|dev_stat
suffix:semicolon
multiline_comment|/* device statistics */
DECL|member|brand
r_char
id|brand
suffix:semicolon
multiline_comment|/* manufacturer of the board */
DECL|member|clock
r_int
id|clock
suffix:semicolon
multiline_comment|/* used clock */
DECL|member|ctrl
id|io_port
id|ctrl
suffix:semicolon
multiline_comment|/* I/O address of CONTROL register */
DECL|member|data
id|io_port
id|data
suffix:semicolon
multiline_comment|/* I/O address of DATA register */
DECL|member|special
id|io_port
id|special
suffix:semicolon
multiline_comment|/* I/O address of special function port */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* Number of Interrupt */
DECL|member|option
r_char
id|option
suffix:semicolon
DECL|member|enhanced
r_char
id|enhanced
suffix:semicolon
multiline_comment|/* Enhanced SCC support */
DECL|member|wreg
r_int
r_char
id|wreg
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Copy of last written value in WRx */
DECL|member|status
r_int
r_char
id|status
suffix:semicolon
multiline_comment|/* Copy of R0 at last external interrupt */
DECL|member|dcd
r_int
r_char
id|dcd
suffix:semicolon
multiline_comment|/* DCD status */
DECL|member|kiss
r_struct
id|scc_kiss
id|kiss
suffix:semicolon
multiline_comment|/* control structure for KISS params */
DECL|member|stat
r_struct
id|scc_stat
id|stat
suffix:semicolon
multiline_comment|/* statistical information */
DECL|member|modem
r_struct
id|scc_modem
id|modem
suffix:semicolon
multiline_comment|/* modem information */
DECL|member|tx_queue
r_struct
id|sk_buff_head
id|tx_queue
suffix:semicolon
multiline_comment|/* next tx buffer */
DECL|member|rx_buff
r_struct
id|sk_buff
op_star
id|rx_buff
suffix:semicolon
multiline_comment|/* pointer to frame currently received */
DECL|member|tx_buff
r_struct
id|sk_buff
op_star
id|tx_buff
suffix:semicolon
multiline_comment|/* pointer to frame currently transmitted */
multiline_comment|/* Timer */
DECL|member|tx_t
r_struct
id|timer_list
id|tx_t
suffix:semicolon
multiline_comment|/* tx timer for this channel */
DECL|member|tx_wdog
r_struct
id|timer_list
id|tx_wdog
suffix:semicolon
multiline_comment|/* tx watchdogs */
)brace
suffix:semicolon
macro_line|#endif /* defined(__KERNEL__) */
macro_line|#endif /* defined(_SCC_H) */
eof
