multiline_comment|/********************************************************&n;* Header file for eata_dma.c and eata_pio.c&t;&t;*&n;* Linux EATA SCSI drivers&t;&t;&t;&t;*&n;* (c) 1993-96 Michael Neuffer                           *&n;*             mike@i-Connect.Net                        *&n;*             neuffer@mail.uni-mainz.de                 *&n;*********************************************************&n;* last change: 96/08/14                                 *&n;********************************************************/
macro_line|#ifndef _EATA_GENERIC_H
DECL|macro|_EATA_GENERIC_H
mdefine_line|#define _EATA_GENERIC_H
multiline_comment|/*********************************************&n; * Misc. definitions&t;&t;&t;     *&n; *********************************************/
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE 1
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE 0
macro_line|#endif
DECL|macro|min
mdefine_line|#define min(a,b) ((a&lt;b)?(a):(b))
DECL|macro|R_LIMIT
mdefine_line|#define R_LIMIT 0x20000
DECL|macro|MAXISA
mdefine_line|#define MAXISA&t;   4
DECL|macro|MAXEISA
mdefine_line|#define MAXEISA&t;  16  
DECL|macro|MAXPCI
mdefine_line|#define MAXPCI&t;  16
DECL|macro|MAXIRQ
mdefine_line|#define MAXIRQ&t;  16 
DECL|macro|MAXTARGET
mdefine_line|#define MAXTARGET 16
DECL|macro|MAXCHANNEL
mdefine_line|#define MAXCHANNEL 3
DECL|macro|IS_ISA
mdefine_line|#define IS_ISA&t;   &squot;I&squot;
DECL|macro|IS_EISA
mdefine_line|#define IS_EISA&t;   &squot;E&squot;
DECL|macro|IS_PCI
mdefine_line|#define IS_PCI&t;   &squot;P&squot;
DECL|macro|BROKEN_INQUIRY
mdefine_line|#define BROKEN_INQUIRY&t;1
DECL|macro|BUSMASTER
mdefine_line|#define BUSMASTER       0xff
DECL|macro|PIO
mdefine_line|#define PIO             0xfe
DECL|macro|EATA_SIGNATURE
mdefine_line|#define EATA_SIGNATURE&t;0x45415441     /* BIG ENDIAN coded &quot;EATA&quot; sig.&t; */
DECL|macro|DPT_ID1
mdefine_line|#define DPT_ID1         0x12
DECL|macro|DPT_ID2
mdefine_line|#define DPT_ID2         0x14
DECL|macro|ATT_ID1
mdefine_line|#define ATT_ID1         0x06
DECL|macro|ATT_ID2
mdefine_line|#define ATT_ID2         0x94
DECL|macro|ATT_ID3
mdefine_line|#define ATT_ID3         0x0
DECL|macro|NEC_ID1
mdefine_line|#define NEC_ID1         0x38
DECL|macro|NEC_ID2
mdefine_line|#define NEC_ID2         0xa3
DECL|macro|NEC_ID3
mdefine_line|#define NEC_ID3         0x82
DECL|macro|EATA_CP_SIZE
mdefine_line|#define EATA_CP_SIZE&t; 44
DECL|macro|MAX_PCI_DEVICES
mdefine_line|#define MAX_PCI_DEVICES  32&t;       /* Maximum # Of Devices Per Bus&t; */
DECL|macro|MAX_METHOD_2
mdefine_line|#define MAX_METHOD_2&t; 16&t;       /* Max Devices For Method 2&t; */
DECL|macro|MAX_PCI_BUS
mdefine_line|#define MAX_PCI_BUS&t; 16&t;       /* Maximum # Of Busses Allowed&t; */
DECL|macro|SG_SIZE
mdefine_line|#define SG_SIZE&t;&t; 64 
DECL|macro|SG_SIZE_BIG
mdefine_line|#define SG_SIZE_BIG&t; 252&t;       /* max. 8096 elements, 64k */
DECL|macro|UPPER_DEVICE_QUEUE_LIMIT
mdefine_line|#define UPPER_DEVICE_QUEUE_LIMIT 64    /* The limit we have to set for the &n;&t;&t;&t;&t;&t;* device queue to keep the broken &n;&t;&t;&t;&t;&t;* midlevel SCSI code from producing&n;&t;&t;&t;&t;&t;* bogus timeouts&n;&t;&t;&t;&t;&t;*/
DECL|macro|TYPE_DISK_QUEUE
mdefine_line|#define TYPE_DISK_QUEUE  16
DECL|macro|TYPE_TAPE_QUEUE
mdefine_line|#define TYPE_TAPE_QUEUE  4
DECL|macro|TYPE_ROM_QUEUE
mdefine_line|#define TYPE_ROM_QUEUE   4
DECL|macro|TYPE_OTHER_QUEUE
mdefine_line|#define TYPE_OTHER_QUEUE 2
DECL|macro|FREE
mdefine_line|#define FREE&t;         0
DECL|macro|OK
mdefine_line|#define OK&t;         0
DECL|macro|NO_TIMEOUT
mdefine_line|#define NO_TIMEOUT       0
DECL|macro|USED
mdefine_line|#define USED&t;         1
DECL|macro|TIMEOUT
mdefine_line|#define TIMEOUT&t;         2
DECL|macro|RESET
mdefine_line|#define RESET&t;         4
DECL|macro|LOCKED
mdefine_line|#define LOCKED&t;         8
DECL|macro|ABORTED
mdefine_line|#define ABORTED          16
DECL|macro|READ
mdefine_line|#define READ             0
DECL|macro|WRITE
mdefine_line|#define WRITE            1
DECL|macro|OTHER
mdefine_line|#define OTHER            2
DECL|macro|HD
mdefine_line|#define HD(cmd)&t; ((hostdata *)&amp;(cmd-&gt;host-&gt;hostdata))
DECL|macro|CD
mdefine_line|#define CD(cmd)&t; ((struct eata_ccb *)(cmd-&gt;host_scribble))
DECL|macro|SD
mdefine_line|#define SD(host) ((hostdata *)&amp;(host-&gt;hostdata))
DECL|macro|DELAY
mdefine_line|#define DELAY(x) { ulong flags, i;                &bslash;&n;                   save_flags(flags); sti();      &bslash;&n;                   i = jiffies + (x * HZ);        &bslash;&n;                   while (jiffies &lt; i);           &bslash;&n;                   restore_flags(flags); }
multiline_comment|/***********************************************&n; *    EATA Command &amp; Register definitions      *&n; ***********************************************/
DECL|macro|PCI_REG_DPTconfig
mdefine_line|#define PCI_REG_DPTconfig&t; 0x40&t; 
DECL|macro|PCI_REG_PumpModeAddress
mdefine_line|#define PCI_REG_PumpModeAddress&t; 0x44&t; 
DECL|macro|PCI_REG_PumpModeData
mdefine_line|#define PCI_REG_PumpModeData&t; 0x48&t; 
DECL|macro|PCI_REG_ConfigParam1
mdefine_line|#define PCI_REG_ConfigParam1&t; 0x50&t; 
DECL|macro|PCI_REG_ConfigParam2
mdefine_line|#define PCI_REG_ConfigParam2&t; 0x54&t; 
DECL|macro|EATA_CMD_PIO_SETUPTEST
mdefine_line|#define EATA_CMD_PIO_SETUPTEST&t; 0xc6
DECL|macro|EATA_CMD_PIO_READ_CONFIG
mdefine_line|#define EATA_CMD_PIO_READ_CONFIG 0xf0
DECL|macro|EATA_CMD_PIO_SET_CONFIG
mdefine_line|#define EATA_CMD_PIO_SET_CONFIG&t; 0xf1
DECL|macro|EATA_CMD_PIO_SEND_CP
mdefine_line|#define EATA_CMD_PIO_SEND_CP&t; 0xf2
DECL|macro|EATA_CMD_PIO_RECEIVE_SP
mdefine_line|#define EATA_CMD_PIO_RECEIVE_SP&t; 0xf3
DECL|macro|EATA_CMD_PIO_TRUNC
mdefine_line|#define EATA_CMD_PIO_TRUNC&t; 0xf4
DECL|macro|EATA_CMD_RESET
mdefine_line|#define EATA_CMD_RESET&t;&t; 0xf9
DECL|macro|EATA_CMD_IMMEDIATE
mdefine_line|#define EATA_CMD_IMMEDIATE&t; 0xfa
DECL|macro|EATA_CMD_DMA_READ_CONFIG
mdefine_line|#define EATA_CMD_DMA_READ_CONFIG 0xfd
DECL|macro|EATA_CMD_DMA_SET_CONFIG
mdefine_line|#define EATA_CMD_DMA_SET_CONFIG&t; 0xfe
DECL|macro|EATA_CMD_DMA_SEND_CP
mdefine_line|#define EATA_CMD_DMA_SEND_CP&t; 0xff
DECL|macro|ECS_EMULATE_SENSE
mdefine_line|#define ECS_EMULATE_SENSE&t; 0xd4
DECL|macro|EATA_GENERIC_ABORT
mdefine_line|#define EATA_GENERIC_ABORT       0x00 
DECL|macro|EATA_SPECIFIC_RESET
mdefine_line|#define EATA_SPECIFIC_RESET      0x01
DECL|macro|EATA_BUS_RESET
mdefine_line|#define EATA_BUS_RESET           0x02
DECL|macro|EATA_SPECIFIC_ABORT
mdefine_line|#define EATA_SPECIFIC_ABORT      0x03
DECL|macro|EATA_QUIET_INTR
mdefine_line|#define EATA_QUIET_INTR          0x04
DECL|macro|EATA_COLD_BOOT_HBA
mdefine_line|#define EATA_COLD_BOOT_HBA       0x06&t;   /* Only as a last resort&t;*/
DECL|macro|EATA_FORCE_IO
mdefine_line|#define EATA_FORCE_IO            0x07
DECL|macro|HA_CTRLREG
mdefine_line|#define HA_CTRLREG     0x206       /* control register for HBA    */
DECL|macro|HA_CTRL_DISINT
mdefine_line|#define HA_CTRL_DISINT 0x02        /* CTRLREG: disable interrupts */
DECL|macro|HA_CTRL_RESCPU
mdefine_line|#define HA_CTRL_RESCPU 0x04        /* CTRLREG: reset processor    */
DECL|macro|HA_CTRL_8HEADS
mdefine_line|#define HA_CTRL_8HEADS 0x08        /* CTRLREG: set for drives with* &n;&t;&t;&t;&t;    * &gt;=8 heads (WD1003 rudimentary :-) */
DECL|macro|HA_WCOMMAND
mdefine_line|#define HA_WCOMMAND    0x07&t;   /* command register offset&t;*/
DECL|macro|HA_WIFC
mdefine_line|#define HA_WIFC        0x06&t;   /* immediate command offset  */
DECL|macro|HA_WCODE
mdefine_line|#define HA_WCODE       0x05 
DECL|macro|HA_WCODE2
mdefine_line|#define HA_WCODE2      0x04 
DECL|macro|HA_WDMAADDR
mdefine_line|#define HA_WDMAADDR    0x02&t;   /* DMA address LSB offset&t;*/  
DECL|macro|HA_RAUXSTAT
mdefine_line|#define HA_RAUXSTAT    0x08&t;   /* aux status register offset*/
DECL|macro|HA_RSTATUS
mdefine_line|#define HA_RSTATUS     0x07&t;   /* status register offset&t;*/
DECL|macro|HA_RDATA
mdefine_line|#define HA_RDATA       0x00&t;   /* data register (16bit)&t;*/
DECL|macro|HA_WDATA
mdefine_line|#define HA_WDATA       0x00&t;   /* data register (16bit)&t;*/
DECL|macro|HA_ABUSY
mdefine_line|#define HA_ABUSY       0x01&t;   /* aux busy bit&t;&t;*/
DECL|macro|HA_AIRQ
mdefine_line|#define HA_AIRQ&t;       0x02&t;   /* aux IRQ pending bit&t;*/
DECL|macro|HA_SERROR
mdefine_line|#define HA_SERROR      0x01&t;   /* pr. command ended in error*/
DECL|macro|HA_SMORE
mdefine_line|#define HA_SMORE       0x02&t;   /* more data soon to come&t;*/
DECL|macro|HA_SCORR
mdefine_line|#define HA_SCORR       0x04&t;   /* data corrected&t;&t;*/
DECL|macro|HA_SDRQ
mdefine_line|#define HA_SDRQ&t;       0x08&t;   /* data request active&t;*/
DECL|macro|HA_SSC
mdefine_line|#define HA_SSC&t;       0x10&t;   /* seek complete&t;&t;*/
DECL|macro|HA_SFAULT
mdefine_line|#define HA_SFAULT      0x20&t;   /* write fault&t;&t;*/
DECL|macro|HA_SREADY
mdefine_line|#define HA_SREADY      0x40&t;   /* drive ready&t;&t;*/
DECL|macro|HA_SBUSY
mdefine_line|#define HA_SBUSY       0x80&t;   /* drive busy&t;&t;*/
DECL|macro|HA_SDRDY
mdefine_line|#define HA_SDRDY       HA_SSC+HA_SREADY+HA_SDRQ 
multiline_comment|/**********************************************&n; * Message definitions&t;&t;&t;      *&n; **********************************************/
DECL|macro|HA_NO_ERROR
mdefine_line|#define HA_NO_ERROR&t; 0x00&t;/* No Error&t;&t;&t;&t;*/
DECL|macro|HA_ERR_SEL_TO
mdefine_line|#define HA_ERR_SEL_TO&t; 0x01&t;/* Selection Timeout&t;&t;&t;*/
DECL|macro|HA_ERR_CMD_TO
mdefine_line|#define HA_ERR_CMD_TO&t; 0x02&t;/* Command Timeout&t;&t;&t;*/
DECL|macro|HA_BUS_RESET
mdefine_line|#define HA_BUS_RESET&t; 0x03&t;/* SCSI Bus Reset Received&t;&t;*/
DECL|macro|HA_INIT_POWERUP
mdefine_line|#define HA_INIT_POWERUP&t; 0x04&t;/* Initial Controller Power-up&t;&t;*/
DECL|macro|HA_UNX_BUSPHASE
mdefine_line|#define HA_UNX_BUSPHASE&t; 0x05&t;/* Unexpected Bus Phase&t;&t;&t;*/
DECL|macro|HA_UNX_BUS_FREE
mdefine_line|#define HA_UNX_BUS_FREE&t; 0x06&t;/* Unexpected Bus Free&t;&t;&t;*/
DECL|macro|HA_BUS_PARITY
mdefine_line|#define HA_BUS_PARITY&t; 0x07&t;/* Bus Parity Error&t;&t;&t;*/
DECL|macro|HA_SCSI_HUNG
mdefine_line|#define HA_SCSI_HUNG&t; 0x08&t;/* SCSI Hung&t;&t;&t;&t;*/
DECL|macro|HA_UNX_MSGRJCT
mdefine_line|#define HA_UNX_MSGRJCT&t; 0x09&t;/* Unexpected Message Rejected&t;&t;*/
DECL|macro|HA_RESET_STUCK
mdefine_line|#define HA_RESET_STUCK&t; 0x0a&t;/* SCSI Bus Reset Stuck&t;&t;&t;*/
DECL|macro|HA_RSENSE_FAIL
mdefine_line|#define HA_RSENSE_FAIL&t; 0x0b&t;/* Auto Request-Sense Failed&t;&t;*/
DECL|macro|HA_PARITY_ERR
mdefine_line|#define HA_PARITY_ERR&t; 0x0c&t;/* Controller Ram Parity Error&t;&t;*/
DECL|macro|HA_CP_ABORT_NA
mdefine_line|#define HA_CP_ABORT_NA&t; 0x0d&t;/* Abort Message sent to non-active cmd */
DECL|macro|HA_CP_ABORTED
mdefine_line|#define HA_CP_ABORTED&t; 0x0e&t;/* Abort Message sent to active cmd&t;*/
DECL|macro|HA_CP_RESET_NA
mdefine_line|#define HA_CP_RESET_NA&t; 0x0f&t;/* Reset Message sent to non-active cmd */
DECL|macro|HA_CP_RESET
mdefine_line|#define HA_CP_RESET&t; 0x10&t;/* Reset Message sent to active cmd&t;*/
DECL|macro|HA_ECC_ERR
mdefine_line|#define HA_ECC_ERR&t; 0x11&t;/* Controller Ram ECC Error&t;&t;*/
DECL|macro|HA_PCI_PARITY
mdefine_line|#define HA_PCI_PARITY&t; 0x12&t;/* PCI Parity Error&t;&t;&t;*/
DECL|macro|HA_PCI_MABORT
mdefine_line|#define HA_PCI_MABORT&t; 0x13&t;/* PCI Master Abort&t;&t;&t;*/
DECL|macro|HA_PCI_TABORT
mdefine_line|#define HA_PCI_TABORT&t; 0x14&t;/* PCI Target Abort&t;&t;&t;*/
DECL|macro|HA_PCI_STABORT
mdefine_line|#define HA_PCI_STABORT&t; 0x15&t;/* PCI Signaled Target Abort&t;&t;*/
multiline_comment|/**********************************************&n; *  Other  definitions&t;&t;&t;      *&n; **********************************************/
DECL|struct|reg_bit
r_struct
id|reg_bit
(brace
multiline_comment|/* reading this one will clear the interrupt    */
DECL|member|error
id|__u8
id|error
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* previous command ended in an error&t;      */
DECL|member|more
id|__u8
id|more
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* more DATA coming soon, poll BSY &amp; DRQ (PIO)  */
DECL|member|corr
id|__u8
id|corr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* data read was successfully corrected with ECC*/
DECL|member|drq
id|__u8
id|drq
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* data request active  */
DECL|member|sc
id|__u8
id|sc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* seek complete&t;      */
DECL|member|fault
id|__u8
id|fault
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* write fault&t;      */
DECL|member|ready
id|__u8
id|ready
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* drive ready&t;      */
DECL|member|busy
id|__u8
id|busy
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* controller busy      */
)brace
suffix:semicolon
DECL|struct|reg_abit
r_struct
id|reg_abit
(brace
multiline_comment|/* reading this won&squot;t clear the interrupt */
DECL|member|abusy
id|__u8
id|abusy
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* auxiliary busy&t;&t;&t;&t;*/
DECL|member|irq
id|__u8
id|irq
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* set when drive interrupt is asserted&t;*/
DECL|member|dummy
id|__u8
id|dummy
suffix:colon
l_int|6
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|eata_register
r_struct
id|eata_register
(brace
multiline_comment|/* EATA register set */
DECL|member|data_reg
id|__u8
id|data_reg
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* R, couldn&squot;t figure this one out&t;&t;*/
DECL|member|cp_addr
id|__u8
id|cp_addr
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* W, CP address register&t;&t;&t;*/
r_union
(brace
DECL|member|command
id|__u8
id|command
suffix:semicolon
multiline_comment|/* W, command code: [read|set] conf, send CP*/
DECL|member|status
r_struct
id|reg_bit
id|status
suffix:semicolon
multiline_comment|/* R, see register_bit1&t;&t;&t;*/
DECL|member|statusbyte
id|__u8
id|statusbyte
suffix:semicolon
DECL|member|ovr
)brace
id|ovr
suffix:semicolon
DECL|member|aux_stat
r_struct
id|reg_abit
id|aux_stat
suffix:semicolon
multiline_comment|/* R, see register_bit2&t;&t;&t;*/
)brace
suffix:semicolon
DECL|struct|get_conf
r_struct
id|get_conf
(brace
multiline_comment|/* Read Configuration Array&t;&t;*/
DECL|member|len
id|__u32
id|len
suffix:semicolon
multiline_comment|/* Should return 0x22, 0x24, etc&t;&t;*/
DECL|member|signature
id|__u32
id|signature
suffix:semicolon
multiline_comment|/* Signature MUST be &quot;EATA&quot;&t;&t;*/
DECL|member|version2
id|__u8
id|version2
suffix:colon
l_int|4
comma
DECL|member|version
id|version
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* EATA Version level&t;&t;&t;*/
DECL|member|OCS_enabled
id|__u8
id|OCS_enabled
suffix:colon
l_int|1
comma
multiline_comment|/* Overlap Command Support enabled&t;*/
DECL|member|TAR_support
id|TAR_support
suffix:colon
l_int|1
comma
multiline_comment|/* SCSI Target Mode supported&t;&t;*/
DECL|member|TRNXFR
id|TRNXFR
suffix:colon
l_int|1
comma
multiline_comment|/* Truncate Transfer Cmd not necessary&t;*&n;&t;&t;&t;       * Only used in PIO Mode&t;&t;&t;*/
DECL|member|MORE_support
id|MORE_support
suffix:colon
l_int|1
comma
multiline_comment|/* MORE supported (only PIO Mode)&t;&t;*/
DECL|member|DMA_support
id|DMA_support
suffix:colon
l_int|1
comma
multiline_comment|/* DMA supported Driver uses only&t;&t;*&n;&t;&t;&t;       * this mode&t;&t;&t;&t;*/
DECL|member|DMA_valid
id|DMA_valid
suffix:colon
l_int|1
comma
multiline_comment|/* DRQ value in Byte 30 is valid&t;&t;*/
DECL|member|ATA
id|ATA
suffix:colon
l_int|1
comma
multiline_comment|/* ATA device connected (not supported)&t;*/
DECL|member|HAA_valid
id|HAA_valid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Hostadapter Address is valid&t;&t;*/
DECL|member|cppadlen
id|__u16
id|cppadlen
suffix:semicolon
multiline_comment|/* Number of pad bytes send after CD data *&n;&t;&t;&t;       * set to zero for DMA commands&t;&t;*/
DECL|member|scsi_id
id|__u8
id|scsi_id
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* SCSI ID of controller 2-0 Byte 0 res.&t;*&n;&t;&t;&t;       * if not, zero is returned&t;&t;*/
DECL|member|cplen
id|__u32
id|cplen
suffix:semicolon
multiline_comment|/* CP length: number of valid cp bytes&t;*/
DECL|member|splen
id|__u32
id|splen
suffix:semicolon
multiline_comment|/* Number of bytes returned after&t;&t;* &n;&t;&t;&t;       * Receive SP command&t;&t;&t;*/
DECL|member|queuesiz
id|__u16
id|queuesiz
suffix:semicolon
multiline_comment|/* max number of queueable CPs&t;&t;*/
DECL|member|dummy
id|__u16
id|dummy
suffix:semicolon
DECL|member|SGsiz
id|__u16
id|SGsiz
suffix:semicolon
multiline_comment|/* max number of SG table entries&t;&t;*/
DECL|member|IRQ
id|__u8
id|IRQ
suffix:colon
l_int|4
comma
multiline_comment|/* IRQ used this HA&t;&t;&t;*/
DECL|member|IRQ_TR
id|IRQ_TR
suffix:colon
l_int|1
comma
multiline_comment|/* IRQ Trigger: 0=edge, 1=level&t;&t;*/
DECL|member|SECOND
id|SECOND
suffix:colon
l_int|1
comma
multiline_comment|/* This is a secondary controller&t;&t;*/
DECL|member|DMA_channel
id|DMA_channel
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* DRQ index, DRQ is 2comp of DRQX&t;*/
DECL|member|sync
id|__u8
id|sync
suffix:semicolon
multiline_comment|/* device at ID 7 tru 0 is running in&t;*&n;&t;&t;&t;       * synchronous mode, this will disappear&t;*/
DECL|member|DSBLE
id|__u8
id|DSBLE
suffix:colon
l_int|1
comma
multiline_comment|/* ISA i/o addressing is disabled&t;&t;*/
DECL|member|FORCADR
id|FORCADR
suffix:colon
l_int|1
comma
multiline_comment|/* i/o address has been forced&t;&t;*/
DECL|member|SG_64K
id|SG_64K
suffix:colon
l_int|1
comma
DECL|member|SG_UAE
id|SG_UAE
suffix:colon
l_int|1
comma
suffix:colon
l_int|4
suffix:semicolon
DECL|member|MAX_ID
id|__u8
id|MAX_ID
suffix:colon
l_int|5
comma
multiline_comment|/* Max number of SCSI target IDs&t;&t;*/
DECL|member|MAX_CHAN
id|MAX_CHAN
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Number of SCSI busses on HBA&t;&t;*/
DECL|member|MAX_LUN
id|__u8
id|MAX_LUN
suffix:semicolon
multiline_comment|/* Max number of LUNs&t;&t;&t;*/
DECL|member|__u8
id|__u8
suffix:colon
l_int|3
comma
DECL|member|AUTOTRM
id|AUTOTRM
suffix:colon
l_int|1
comma
DECL|member|M1_inst
id|M1_inst
suffix:colon
l_int|1
comma
DECL|member|ID_qest
id|ID_qest
suffix:colon
l_int|1
comma
multiline_comment|/* Raidnum ID is questionable&t;&t;*/
DECL|member|is_PCI
id|is_PCI
suffix:colon
l_int|1
comma
multiline_comment|/* HBA is PCI&t;&t;&t;&t;*/
DECL|member|is_EISA
id|is_EISA
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* HBA is EISA&t;&t;&t;&t;*/
DECL|member|RAIDNUM
id|__u8
id|RAIDNUM
suffix:semicolon
multiline_comment|/* unique HBA identifier                  */
DECL|member|unused
id|__u8
id|unused
(braket
l_int|474
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|eata_sg_list
r_struct
id|eata_sg_list
(brace
DECL|member|data
id|__u32
id|data
suffix:semicolon
DECL|member|len
id|__u32
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|eata_ccb
r_struct
id|eata_ccb
(brace
multiline_comment|/* Send Command Packet structure&t;    */
DECL|member|SCSI_Reset
id|__u8
id|SCSI_Reset
suffix:colon
l_int|1
comma
multiline_comment|/* Cause a SCSI Bus reset on the cmd&t;*/
DECL|member|HBA_Init
id|HBA_Init
suffix:colon
l_int|1
comma
multiline_comment|/* Cause Controller to reinitialize&t;*/
DECL|member|Auto_Req_Sen
id|Auto_Req_Sen
suffix:colon
l_int|1
comma
multiline_comment|/* Do Auto Request Sense on errors&t;*/
DECL|member|scatter
id|scatter
suffix:colon
l_int|1
comma
multiline_comment|/* Data Ptr points to a SG Packet&t;&t;*/
DECL|member|Resrvd
id|Resrvd
suffix:colon
l_int|1
comma
multiline_comment|/* RFU&t;&t;&t;&t;&t;*/
DECL|member|Interpret
id|Interpret
suffix:colon
l_int|1
comma
multiline_comment|/* Interpret the SCSI cdb of own use&t;*/
DECL|member|DataOut
id|DataOut
suffix:colon
l_int|1
comma
multiline_comment|/* Data Out phase with command&t;&t;*/
DECL|member|DataIn
id|DataIn
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Data In phase with command&t;&t;*/
DECL|member|reqlen
id|__u8
id|reqlen
suffix:semicolon
multiline_comment|/* Request Sense Length&t;&t;&t;* &n;&t;&t;&t;       * Valid if Auto_Req_Sen=1&t;&t;*/
DECL|member|unused
id|__u8
id|unused
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|FWNEST
id|__u8
id|FWNEST
suffix:colon
l_int|1
comma
multiline_comment|/* send cmd to phys RAID component&t;*/
DECL|member|unused2
id|unused2
suffix:colon
l_int|7
suffix:semicolon
DECL|member|Phsunit
id|__u8
id|Phsunit
suffix:colon
l_int|1
comma
multiline_comment|/* physical unit on mirrored pair&t;&t;*/
DECL|member|I_AT
id|I_AT
suffix:colon
l_int|1
comma
multiline_comment|/* inhibit address translation&t;&t;*/
DECL|member|I_HBA_C
id|I_HBA_C
suffix:colon
l_int|1
comma
multiline_comment|/* HBA inhibit caching&t;&t;&t;*/
DECL|member|unused3
id|unused3
suffix:colon
l_int|5
suffix:semicolon
DECL|member|cp_id
id|__u8
id|cp_id
suffix:colon
l_int|5
comma
multiline_comment|/* SCSI Device ID of target&t;&t;*/
DECL|member|cp_channel
id|cp_channel
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* SCSI Channel # of HBA&t;&t;&t;*/
DECL|member|cp_lun
id|__u8
id|cp_lun
suffix:colon
l_int|3
comma
suffix:colon
l_int|2
comma
DECL|member|cp_luntar
id|cp_luntar
suffix:colon
l_int|1
comma
multiline_comment|/* CP is for target ROUTINE&t;&t;*/
DECL|member|cp_dispri
id|cp_dispri
suffix:colon
l_int|1
comma
multiline_comment|/* Grant disconnect privilege&t;&t;*/
DECL|member|cp_identify
id|cp_identify
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Always TRUE&t;&t;&t;&t;*/
DECL|member|cp_msg1
id|__u8
id|cp_msg1
suffix:semicolon
multiline_comment|/* Message bytes 0-3&t;&t;&t;*/
DECL|member|cp_msg2
id|__u8
id|cp_msg2
suffix:semicolon
DECL|member|cp_msg3
id|__u8
id|cp_msg3
suffix:semicolon
DECL|member|cp_cdb
id|__u8
id|cp_cdb
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* Command Descriptor Block&t;&t;*/
DECL|member|cp_datalen
id|__u32
id|cp_datalen
suffix:semicolon
multiline_comment|/* Data Transfer Length&t;&t;&t;*&n;&t;&t;&t;       * If scatter=1 len of sg package&t;&t;*/
DECL|member|cp_viraddr
r_void
op_star
id|cp_viraddr
suffix:semicolon
multiline_comment|/* address of this ccb&t;&t;&t;*/
DECL|member|cp_dataDMA
id|__u32
id|cp_dataDMA
suffix:semicolon
multiline_comment|/* Data Address, if scatter=1&t;&t;*&n;&t;&t;&t;       * address of scatter packet&t;&t;*/
DECL|member|cp_statDMA
id|__u32
id|cp_statDMA
suffix:semicolon
multiline_comment|/* address for Status Packet&t;&t;*/
DECL|member|cp_reqDMA
id|__u32
id|cp_reqDMA
suffix:semicolon
multiline_comment|/* Request Sense Address, used if&t;&t;*&n;&t;&t;&t;       * CP command ends with error&t;&t;*/
multiline_comment|/* Additional CP info begins here */
DECL|member|timestamp
id|__u32
id|timestamp
suffix:semicolon
multiline_comment|/* Needed to measure command latency&t;*/
DECL|member|timeout
id|__u32
id|timeout
suffix:semicolon
DECL|member|sizeindex
id|__u8
id|sizeindex
suffix:semicolon
DECL|member|rw_latency
id|__u8
id|rw_latency
suffix:semicolon
DECL|member|retries
id|__u8
id|retries
suffix:semicolon
DECL|member|status
id|__u8
id|status
suffix:semicolon
multiline_comment|/* status of this queueslot&t;&t;*/
DECL|member|cmd
id|Scsi_Cmnd
op_star
id|cmd
suffix:semicolon
multiline_comment|/* address of cmd&t;&t;&t;&t;*/
DECL|member|sg_list
r_struct
id|eata_sg_list
op_star
id|sg_list
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|eata_sp
r_struct
id|eata_sp
(brace
DECL|member|hba_stat
id|__u8
id|hba_stat
suffix:colon
l_int|7
comma
multiline_comment|/* HBA status&t;&t;&t;&t;*/
DECL|member|EOC
id|EOC
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* True if command finished&t;&t;*/
DECL|member|scsi_stat
id|__u8
id|scsi_stat
suffix:semicolon
multiline_comment|/* Target SCSI status&t;&t;&t;*/
DECL|member|reserved
id|__u8
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|residue_len
id|__u32
id|residue_len
suffix:semicolon
multiline_comment|/* Number of bytes not transferred&t;*/
DECL|member|ccb
r_struct
id|eata_ccb
op_star
id|ccb
suffix:semicolon
multiline_comment|/* Address set in COMMAND PACKET&t;&t;*/
DECL|member|msg
id|__u8
id|msg
(braket
l_int|12
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hstd
r_typedef
r_struct
id|hstd
(brace
DECL|member|vendor
id|__u8
id|vendor
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|name
id|__u8
id|name
(braket
l_int|18
)braket
suffix:semicolon
DECL|member|revision
id|__u8
id|revision
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|EATA_revision
id|__u8
id|EATA_revision
suffix:semicolon
DECL|member|firmware_revision
id|__u32
id|firmware_revision
suffix:semicolon
DECL|member|HBA_number
id|__u8
id|HBA_number
suffix:semicolon
DECL|member|bustype
id|__u8
id|bustype
suffix:semicolon
multiline_comment|/* bustype of HBA&t;       */
DECL|member|channel
id|__u8
id|channel
suffix:semicolon
multiline_comment|/* # of avail. scsi channels  */
DECL|member|state
id|__u8
id|state
suffix:semicolon
multiline_comment|/* state of HBA&t;       */
DECL|member|primary
id|__u8
id|primary
suffix:semicolon
multiline_comment|/* true if primary&t;       */
DECL|member|more_support
id|__u8
id|more_support
suffix:colon
l_int|1
comma
multiline_comment|/* HBA supports MORE flag     */
DECL|member|immediate_support
id|immediate_support
suffix:colon
l_int|1
comma
multiline_comment|/* HBA supports IMMEDIATE CMDs*/
DECL|member|broken_INQUIRY
id|broken_INQUIRY
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* This is an EISA HBA with   *&n;&t;&t;&t;&t;  * broken INQUIRY&t;       */
DECL|member|do_latency
id|__u8
id|do_latency
suffix:semicolon
multiline_comment|/* Latency measurement flag   */
DECL|member|reads
id|__u32
id|reads
(braket
l_int|13
)braket
suffix:semicolon
DECL|member|writes
id|__u32
id|writes
(braket
l_int|13
)braket
suffix:semicolon
DECL|member|reads_lat
id|__u32
id|reads_lat
(braket
l_int|12
)braket
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|writes_lat
id|__u32
id|writes_lat
(braket
l_int|12
)braket
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|all_lat
id|__u32
id|all_lat
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|resetlevel
id|__u8
id|resetlevel
(braket
id|MAXCHANNEL
)braket
suffix:semicolon
DECL|member|last_ccb
id|__u32
id|last_ccb
suffix:semicolon
multiline_comment|/* Last used ccb&t;       */
DECL|member|cplen
id|__u32
id|cplen
suffix:semicolon
multiline_comment|/* size of CP in words&t;       */
DECL|member|cppadlen
id|__u16
id|cppadlen
suffix:semicolon
multiline_comment|/* pad length of cp in words  */
DECL|member|queuesize
id|__u16
id|queuesize
suffix:semicolon
DECL|member|sgsize
id|__u16
id|sgsize
suffix:semicolon
multiline_comment|/* # of entries in the SG list*/
DECL|member|devflags
id|__u16
id|devflags
suffix:semicolon
multiline_comment|/* bits set for detected devices */
DECL|member|hostid
id|__u8
id|hostid
suffix:semicolon
multiline_comment|/* SCSI ID of HBA&t;       */
DECL|member|moresupport
id|__u8
id|moresupport
suffix:semicolon
multiline_comment|/* HBA supports MORE flag     */
DECL|member|next
r_struct
id|Scsi_Host
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|Scsi_Host
op_star
id|prev
suffix:semicolon
DECL|member|sp
r_struct
id|eata_sp
id|sp
suffix:semicolon
multiline_comment|/* status packet&t;       */
DECL|member|ccb
r_struct
id|eata_ccb
id|ccb
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* ccb array begins here      */
DECL|typedef|hostdata
)brace
id|hostdata
suffix:semicolon
multiline_comment|/* structure for max. 2 emulated drives */
DECL|struct|drive_geom_emul
r_struct
id|drive_geom_emul
(brace
DECL|member|trans
id|__u8
id|trans
suffix:semicolon
multiline_comment|/* translation flag 1=transl */
DECL|member|channel
id|__u8
id|channel
suffix:semicolon
multiline_comment|/* SCSI channel number&t;      */
DECL|member|HBA
id|__u8
id|HBA
suffix:semicolon
multiline_comment|/* HBA number (prim/sec)     */
DECL|member|id
id|__u8
id|id
suffix:semicolon
multiline_comment|/* drive id&t;&t;      */
DECL|member|lun
id|__u8
id|lun
suffix:semicolon
multiline_comment|/* drive lun&t;&t;      */
DECL|member|heads
id|__u32
id|heads
suffix:semicolon
multiline_comment|/* number of heads&t;      */
DECL|member|sectors
id|__u32
id|sectors
suffix:semicolon
multiline_comment|/* number of sectors&t;      */
DECL|member|cylinder
id|__u32
id|cylinder
suffix:semicolon
multiline_comment|/* number of cylinders&t;      */
)brace
suffix:semicolon
DECL|struct|geom_emul
r_struct
id|geom_emul
(brace
DECL|member|bios_drives
id|__u8
id|bios_drives
suffix:semicolon
multiline_comment|/* number of emulated drives */
DECL|member|drv
r_struct
id|drive_geom_emul
id|drv
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* drive structures&t;      */
)brace
suffix:semicolon
macro_line|#endif /* _EATA_GENERIC_H */
multiline_comment|/*&n; * Overrides for Emacs so that we almost follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * tab-width: 8&n; * End:&n; */
eof
