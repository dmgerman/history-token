multiline_comment|/* linux/include/asm/arch-s3c2410/regs-sdi.h&n; *&n; * Copyright (c) 2004 Simtec Electronics &lt;linux@simtec.co.uk&gt;&n; *&t;&t;      http://www.simtec.co.uk/products/SWLINUX/&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * S3C2410 MMC/SDIO register definitions&n; *&n; *  Changelog:&n; *    18-Aug-2004 Ben Dooks      Created initial file&n; *    29-Nov-2004 Koen Martens   Added some missing defines, fixed duplicates&n; *    29-Nov-2004 Ben Dooks&t; Updated Koen&squot;s patch&n;*/
macro_line|#ifndef __ASM_ARM_REGS_SDI
DECL|macro|__ASM_ARM_REGS_SDI
mdefine_line|#define __ASM_ARM_REGS_SDI &quot;regs-sdi.h&quot;
DECL|macro|S3C2410_SDICON
mdefine_line|#define S3C2410_SDICON                (0x00)
DECL|macro|S3C2410_SDIPRE
mdefine_line|#define S3C2410_SDIPRE                (0x04)
DECL|macro|S3C2410_SDICMDARG
mdefine_line|#define S3C2410_SDICMDARG             (0x08)
DECL|macro|S3C2410_SDICMDCON
mdefine_line|#define S3C2410_SDICMDCON             (0x0C)
DECL|macro|S3C2410_SDICMDSTAT
mdefine_line|#define S3C2410_SDICMDSTAT            (0x10)
DECL|macro|S3C2410_SDIRSP0
mdefine_line|#define S3C2410_SDIRSP0               (0x14)
DECL|macro|S3C2410_SDIRSP1
mdefine_line|#define S3C2410_SDIRSP1               (0x18)
DECL|macro|S3C2410_SDIRSP2
mdefine_line|#define S3C2410_SDIRSP2               (0x1C)
DECL|macro|S3C2410_SDIRSP3
mdefine_line|#define S3C2410_SDIRSP3               (0x20)
DECL|macro|S3C2410_SDITIMER
mdefine_line|#define S3C2410_SDITIMER              (0x24)
DECL|macro|S3C2410_SDIBSIZE
mdefine_line|#define S3C2410_SDIBSIZE              (0x28)
DECL|macro|S3C2410_SDIDCON
mdefine_line|#define S3C2410_SDIDCON               (0x2C)
DECL|macro|S3C2410_SDIDCNT
mdefine_line|#define S3C2410_SDIDCNT               (0x30)
DECL|macro|S3C2410_SDIDSTA
mdefine_line|#define S3C2410_SDIDSTA               (0x34)
DECL|macro|S3C2410_SDIFSTA
mdefine_line|#define S3C2410_SDIFSTA               (0x38)
DECL|macro|S3C2410_SDIDATA
mdefine_line|#define S3C2410_SDIDATA               (0x3C)
DECL|macro|S3C2410_SDIIMSK
mdefine_line|#define S3C2410_SDIIMSK               (0x40)
DECL|macro|S3C2410_SDICON_BYTEORDER
mdefine_line|#define S3C2410_SDICON_BYTEORDER      (1&lt;&lt;4)
DECL|macro|S3C2410_SDICON_SDIOIRQ
mdefine_line|#define S3C2410_SDICON_SDIOIRQ        (1&lt;&lt;3)
DECL|macro|S3C2410_SDICON_RWAITEN
mdefine_line|#define S3C2410_SDICON_RWAITEN        (1&lt;&lt;2)
DECL|macro|S3C2410_SDICON_FIFORESET
mdefine_line|#define S3C2410_SDICON_FIFORESET      (1&lt;&lt;1)
DECL|macro|S3C2410_SDICON_CLOCKTYPE
mdefine_line|#define S3C2410_SDICON_CLOCKTYPE      (1&lt;&lt;0)
DECL|macro|S3C2410_SDICMDCON_ABORT
mdefine_line|#define S3C2410_SDICMDCON_ABORT       (1&lt;&lt;12)
DECL|macro|S3C2410_SDICMDCON_WITHDATA
mdefine_line|#define S3C2410_SDICMDCON_WITHDATA    (1&lt;&lt;11)
DECL|macro|S3C2410_SDICMDCON_LONGRSP
mdefine_line|#define S3C2410_SDICMDCON_LONGRSP     (1&lt;&lt;10)
DECL|macro|S3C2410_SDICMDCON_WAITRSP
mdefine_line|#define S3C2410_SDICMDCON_WAITRSP     (1&lt;&lt;9)
DECL|macro|S3C2410_SDICMDCON_CMDSTART
mdefine_line|#define S3C2410_SDICMDCON_CMDSTART    (1&lt;&lt;8)
DECL|macro|S3C2410_SDICMDCON_INDEX
mdefine_line|#define S3C2410_SDICMDCON_INDEX       (0xff)
DECL|macro|S3C2410_SDICMDSTAT_CRCFAIL
mdefine_line|#define S3C2410_SDICMDSTAT_CRCFAIL    (1&lt;&lt;12)
DECL|macro|S3C2410_SDICMDSTAT_CMDSENT
mdefine_line|#define S3C2410_SDICMDSTAT_CMDSENT    (1&lt;&lt;11)
DECL|macro|S3C2410_SDICMDSTAT_CMDTIMEOUT
mdefine_line|#define S3C2410_SDICMDSTAT_CMDTIMEOUT (1&lt;&lt;10)
DECL|macro|S3C2410_SDICMDSTAT_RSPFIN
mdefine_line|#define S3C2410_SDICMDSTAT_RSPFIN     (1&lt;&lt;9)
DECL|macro|S3C2410_SDICMDSTAT_XFERING
mdefine_line|#define S3C2410_SDICMDSTAT_XFERING    (1&lt;&lt;8)
DECL|macro|S3C2410_SDICMDSTAT_INDEX
mdefine_line|#define S3C2410_SDICMDSTAT_INDEX      (0xff)
DECL|macro|S3C2410_SDIDCON_IRQPERIOD
mdefine_line|#define S3C2410_SDIDCON_IRQPERIOD     (1&lt;&lt;21)
DECL|macro|S3C2410_SDIDCON_TXAFTERRESP
mdefine_line|#define S3C2410_SDIDCON_TXAFTERRESP   (1&lt;&lt;20)
DECL|macro|S3C2410_SDIDCON_RXAFTERCMD
mdefine_line|#define S3C2410_SDIDCON_RXAFTERCMD    (1&lt;&lt;19)
DECL|macro|S3C2410_SDIDCON_BUSYAFTERCMD
mdefine_line|#define S3C2410_SDIDCON_BUSYAFTERCMD  (1&lt;&lt;18)
DECL|macro|S3C2410_SDIDCON_BLOCKMODE
mdefine_line|#define S3C2410_SDIDCON_BLOCKMODE     (1&lt;&lt;17)
DECL|macro|S3C2410_SDIDCON_WIDEBUS
mdefine_line|#define S3C2410_SDIDCON_WIDEBUS       (1&lt;&lt;16)
DECL|macro|S3C2410_SDIDCON_DMAEN
mdefine_line|#define S3C2410_SDIDCON_DMAEN         (1&lt;&lt;15)
DECL|macro|S3C2410_SDIDCON_STOP
mdefine_line|#define S3C2410_SDIDCON_STOP          (1&lt;&lt;14)
DECL|macro|S3C2410_SDIDCON_DATMODE
mdefine_line|#define S3C2410_SDIDCON_DATMODE&t;      (3&lt;&lt;12)
DECL|macro|S3C2410_SDIDCON_BLKNUM
mdefine_line|#define S3C2410_SDIDCON_BLKNUM        (0x7ff)
multiline_comment|/* constants for S3C2410_SDIDCON_DATMODE */
DECL|macro|S3C2410_SDIDCON_XFER_READY
mdefine_line|#define S3C2410_SDIDCON_XFER_READY    (0&lt;&lt;12)
DECL|macro|S3C2410_SDIDCON_XFER_CHKSTART
mdefine_line|#define S3C2410_SDIDCON_XFER_CHKSTART (1&lt;&lt;12)
DECL|macro|S3C2410_SDIDCON_XFER_RXSTART
mdefine_line|#define S3C2410_SDIDCON_XFER_RXSTART  (2&lt;&lt;12)
DECL|macro|S3C2410_SDIDCON_XFER_TXSTART
mdefine_line|#define S3C2410_SDIDCON_XFER_TXSTART  (3&lt;&lt;12)
DECL|macro|S3C2410_SDIDCNT_BLKNUM_SHIFT
mdefine_line|#define S3C2410_SDIDCNT_BLKNUM_SHIFT  (12)
DECL|macro|S3C2410_SDIDSTA_RDYWAITREQ
mdefine_line|#define S3C2410_SDIDSTA_RDYWAITREQ    (1&lt;&lt;10)
DECL|macro|S3C2410_SDIDSTA_SDIOIRQDETECT
mdefine_line|#define S3C2410_SDIDSTA_SDIOIRQDETECT (1&lt;&lt;9)
DECL|macro|S3C2410_SDIDSTA_FIFOFAIL
mdefine_line|#define S3C2410_SDIDSTA_FIFOFAIL      (1&lt;&lt;8)&t;/* reserved on 2440 */
DECL|macro|S3C2410_SDIDSTA_CRCFAIL
mdefine_line|#define S3C2410_SDIDSTA_CRCFAIL       (1&lt;&lt;7)
DECL|macro|S3C2410_SDIDSTA_RXCRCFAIL
mdefine_line|#define S3C2410_SDIDSTA_RXCRCFAIL     (1&lt;&lt;6)
DECL|macro|S3C2410_SDIDSTA_DATATIMEOUT
mdefine_line|#define S3C2410_SDIDSTA_DATATIMEOUT   (1&lt;&lt;5)
DECL|macro|S3C2410_SDIDSTA_XFERFINISH
mdefine_line|#define S3C2410_SDIDSTA_XFERFINISH    (1&lt;&lt;4)
DECL|macro|S3C2410_SDIDSTA_BUSYFINISH
mdefine_line|#define S3C2410_SDIDSTA_BUSYFINISH    (1&lt;&lt;3)
DECL|macro|S3C2410_SDIDSTA_SBITERR
mdefine_line|#define S3C2410_SDIDSTA_SBITERR       (1&lt;&lt;2)&t;/* reserved on 2410a/2440 */
DECL|macro|S3C2410_SDIDSTA_TXDATAON
mdefine_line|#define S3C2410_SDIDSTA_TXDATAON      (1&lt;&lt;1)
DECL|macro|S3C2410_SDIDSTA_RXDATAON
mdefine_line|#define S3C2410_SDIDSTA_RXDATAON      (1&lt;&lt;0)
DECL|macro|S3C2410_SDIFSTA_TFDET
mdefine_line|#define S3C2410_SDIFSTA_TFDET          (1&lt;&lt;13)
DECL|macro|S3C2410_SDIFSTA_RFDET
mdefine_line|#define S3C2410_SDIFSTA_RFDET          (1&lt;&lt;12)
DECL|macro|S3C2410_SDIFSTA_TXHALF
mdefine_line|#define S3C2410_SDIFSTA_TXHALF         (1&lt;&lt;11)
DECL|macro|S3C2410_SDIFSTA_TXEMPTY
mdefine_line|#define S3C2410_SDIFSTA_TXEMPTY        (1&lt;&lt;10)
DECL|macro|S3C2410_SDIFSTA_RFLAST
mdefine_line|#define S3C2410_SDIFSTA_RFLAST         (1&lt;&lt;9)
DECL|macro|S3C2410_SDIFSTA_RFFULL
mdefine_line|#define S3C2410_SDIFSTA_RFFULL         (1&lt;&lt;8)
DECL|macro|S3C2410_SDIFSTA_RFHALF
mdefine_line|#define S3C2410_SDIFSTA_RFHALF         (1&lt;&lt;7)
DECL|macro|S3C2410_SDIFSTA_COUNTMASK
mdefine_line|#define S3C2410_SDIFSTA_COUNTMASK      (0x7f)
DECL|macro|S3C2410_SDIIMSK_RESPONSECRC
mdefine_line|#define S3C2410_SDIIMSK_RESPONSECRC    (1&lt;&lt;17)
DECL|macro|S3C2410_SDIIMSK_CMDSENT
mdefine_line|#define S3C2410_SDIIMSK_CMDSENT        (1&lt;&lt;16)
DECL|macro|S3C2410_SDIIMSK_CMDTIMEOUT
mdefine_line|#define S3C2410_SDIIMSK_CMDTIMEOUT     (1&lt;&lt;15)
DECL|macro|S3C2410_SDIIMSK_RESPONSEND
mdefine_line|#define S3C2410_SDIIMSK_RESPONSEND     (1&lt;&lt;14)
DECL|macro|S3C2410_SDIIMSK_READWAIT
mdefine_line|#define S3C2410_SDIIMSK_READWAIT       (1&lt;&lt;13)
DECL|macro|S3C2410_SDIIMSK_SDIOIRQ
mdefine_line|#define S3C2410_SDIIMSK_SDIOIRQ        (1&lt;&lt;12)
DECL|macro|S3C2410_SDIIMSK_FIFOFAIL
mdefine_line|#define S3C2410_SDIIMSK_FIFOFAIL       (1&lt;&lt;11)
DECL|macro|S3C2410_SDIIMSK_CRCSTATUS
mdefine_line|#define S3C2410_SDIIMSK_CRCSTATUS      (1&lt;&lt;10)
DECL|macro|S3C2410_SDIIMSK_DATACRC
mdefine_line|#define S3C2410_SDIIMSK_DATACRC        (1&lt;&lt;9)
DECL|macro|S3C2410_SDIIMSK_DATATIMEOUT
mdefine_line|#define S3C2410_SDIIMSK_DATATIMEOUT    (1&lt;&lt;8)
DECL|macro|S3C2410_SDIIMSK_DATAFINISH
mdefine_line|#define S3C2410_SDIIMSK_DATAFINISH     (1&lt;&lt;7)
DECL|macro|S3C2410_SDIIMSK_BUSYFINISH
mdefine_line|#define S3C2410_SDIIMSK_BUSYFINISH     (1&lt;&lt;6)
DECL|macro|S3C2410_SDIIMSK_SBITERR
mdefine_line|#define S3C2410_SDIIMSK_SBITERR        (1&lt;&lt;5)&t;/* reserved 2440/2410a */
DECL|macro|S3C2410_SDIIMSK_TXFIFOHALF
mdefine_line|#define S3C2410_SDIIMSK_TXFIFOHALF     (1&lt;&lt;4)
DECL|macro|S3C2410_SDIIMSK_TXFIFOEMPTY
mdefine_line|#define S3C2410_SDIIMSK_TXFIFOEMPTY    (1&lt;&lt;3)
DECL|macro|S3C2410_SDIIMSK_RXFIFOLAST
mdefine_line|#define S3C2410_SDIIMSK_RXFIFOLAST     (1&lt;&lt;2)
DECL|macro|S3C2410_SDIIMSK_RXFIFOFULL
mdefine_line|#define S3C2410_SDIIMSK_RXFIFOFULL     (1&lt;&lt;1)
DECL|macro|S3C2410_SDIIMSK_RXFIFOHALF
mdefine_line|#define S3C2410_SDIIMSK_RXFIFOHALF     (1&lt;&lt;0)
macro_line|#endif /* __ASM_ARM_REGS_SDI */
eof
