multiline_comment|/* to be used by qlogicfas and qlogic_cs */
macro_line|#ifndef __QLOGICFAS_H
DECL|macro|__QLOGICFAS_H
mdefine_line|#define __QLOGICFAS_H
multiline_comment|/*----------------------------------------------------------------*/
multiline_comment|/* Configuration */
multiline_comment|/* Set the following to 2 to use normal interrupt (active high/totempole-&n;   tristate), otherwise use 0 (REQUIRED FOR PCMCIA) for active low, open&n;   drain */
DECL|macro|QL_INT_ACTIVE_HIGH
mdefine_line|#define QL_INT_ACTIVE_HIGH 2
multiline_comment|/* Set the following to max out the speed of the PIO PseudoDMA transfers,&n;   again, 0 tends to be slower, but more stable.  */
DECL|macro|QL_TURBO_PDMA
mdefine_line|#define QL_TURBO_PDMA 1
multiline_comment|/* This should be 1 to enable parity detection */
DECL|macro|QL_ENABLE_PARITY
mdefine_line|#define QL_ENABLE_PARITY 1
multiline_comment|/* This will reset all devices when the driver is initialized (during bootup).&n;   The other linux drivers don&squot;t do this, but the DOS drivers do, and after&n;   using DOS or some kind of crash or lockup this will bring things back&n;   without requiring a cold boot.  It does take some time to recover from a&n;   reset, so it is slower, and I have seen timeouts so that devices weren&squot;t&n;   recognized when this was set. */
DECL|macro|QL_RESET_AT_START
mdefine_line|#define QL_RESET_AT_START 0
multiline_comment|/* crystal frequency in megahertz (for offset 5 and 9)&n;   Please set this for your card.  Most Qlogic cards are 40 Mhz.  The&n;   Control Concepts ISA (not VLB) is 24 Mhz */
DECL|macro|XTALFREQ
mdefine_line|#define XTALFREQ&t;40
multiline_comment|/**********/
multiline_comment|/* DANGER! modify these at your own risk */
multiline_comment|/* SLOWCABLE can usually be reset to zero if you have a clean setup and&n;   proper termination.  The rest are for synchronous transfers and other&n;   advanced features if your device can transfer faster than 5Mb/sec.&n;   If you are really curious, email me for a quick howto until I have&n;   something official */
multiline_comment|/**********/
multiline_comment|/*****/
multiline_comment|/* config register 1 (offset 8) options */
multiline_comment|/* This needs to be set to 1 if your cabling is long or noisy */
DECL|macro|SLOWCABLE
mdefine_line|#define SLOWCABLE 1
multiline_comment|/*****/
multiline_comment|/* offset 0xc */
multiline_comment|/* This will set fast (10Mhz) synchronous timing when set to 1&n;   For this to have an effect, FASTCLK must also be 1 */
DECL|macro|FASTSCSI
mdefine_line|#define FASTSCSI 0
multiline_comment|/* This when set to 1 will set a faster sync transfer rate */
DECL|macro|FASTCLK
mdefine_line|#define FASTCLK 0&t;/*(XTALFREQ&gt;25?1:0)*/
multiline_comment|/*****/
multiline_comment|/* offset 6 */
multiline_comment|/* This is the sync transfer divisor, XTALFREQ/X will be the maximum&n;   achievable data rate (assuming the rest of the system is capable&n;   and set properly) */
DECL|macro|SYNCXFRPD
mdefine_line|#define SYNCXFRPD 5&t;/*(XTALFREQ/5)*/
multiline_comment|/*****/
multiline_comment|/* offset 7 */
multiline_comment|/* This is the count of how many synchronous transfers can take place&n;&t;i.e. how many reqs can occur before an ack is given.&n;&t;The maximum value for this is 15, the upper bits can modify&n;&t;REQ/ACK assertion and deassertion during synchronous transfers&n;&t;If this is 0, the bus will only transfer asynchronously */
DECL|macro|SYNCOFFST
mdefine_line|#define SYNCOFFST 0
multiline_comment|/* for the curious, bits 7&amp;6 control the deassertion delay in 1/2 cycles&n;&t;of the 40Mhz clock. If FASTCLK is 1, specifying 01 (1/2) will&n;&t;cause the deassertion to be early by 1/2 clock.  Bits 5&amp;4 control&n;&t;the assertion delay, also in 1/2 clocks (FASTCLK is ignored here). */
multiline_comment|/*----------------------------------------------------------------*/
macro_line|#ifdef PCMCIA
DECL|macro|QL_INT_ACTIVE_HIGH
macro_line|#undef QL_INT_ACTIVE_HIGH
DECL|macro|QL_INT_ACTIVE_HIGH
mdefine_line|#define QL_INT_ACTIVE_HIGH 0
macro_line|#endif
DECL|struct|qlogicfas_priv
r_struct
id|qlogicfas_priv
(brace
DECL|member|qbase
r_int
id|qbase
suffix:semicolon
multiline_comment|/* Port */
DECL|member|qinitid
r_int
id|qinitid
suffix:semicolon
multiline_comment|/* initiator ID */
DECL|member|qabort
r_int
id|qabort
suffix:semicolon
multiline_comment|/* Flag to cause an abort */
DECL|member|qlirq
r_int
id|qlirq
suffix:semicolon
multiline_comment|/* IRQ being used */
DECL|member|qinfo
r_char
id|qinfo
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* description */
DECL|member|qlcmd
id|Scsi_Cmnd
op_star
id|qlcmd
suffix:semicolon
multiline_comment|/* current command being processed */
)brace
suffix:semicolon
DECL|typedef|qlogicfas_priv_t
r_typedef
r_struct
id|qlogicfas_priv
op_star
id|qlogicfas_priv_t
suffix:semicolon
r_extern
r_int
id|qlcfg5
suffix:semicolon
r_extern
r_int
id|qlcfg6
suffix:semicolon
r_extern
r_int
id|qlcfg7
suffix:semicolon
r_extern
r_int
id|qlcfg8
suffix:semicolon
r_extern
r_int
id|qlcfg9
suffix:semicolon
r_extern
r_int
id|qlcfgc
suffix:semicolon
multiline_comment|/* The qlogic card uses two register maps - These macros select which one */
DECL|macro|REG0
mdefine_line|#define REG0 ( outb( inb( qbase + 0xd ) &amp; 0x7f , qbase + 0xd ), outb( 4 , qbase + 0xd ))
DECL|macro|REG1
mdefine_line|#define REG1 ( outb( inb( qbase + 0xd ) | 0x80 , qbase + 0xd ), outb( 0xb4 | QL_INT_ACTIVE_HIGH , qbase + 0xd ))
multiline_comment|/* following is watchdog timeout in microseconds */
DECL|macro|WATCHDOG
mdefine_line|#define WATCHDOG 5000000
multiline_comment|/*----------------------------------------------------------------*/
multiline_comment|/* the following will set the monitor border color (useful to find&n;   where something crashed or gets stuck at and as a simple profiler) */
macro_line|#if 0
mdefine_line|#define rtrc(i) {inb(0x3da);outb(0x31,0x3c0);outb((i),0x3c0);}
macro_line|#else
DECL|macro|rtrc
mdefine_line|#define rtrc(i) {}
macro_line|#endif
macro_line|#endif&t;/* __QLOGICFAS_H */
eof
