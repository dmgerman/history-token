multiline_comment|/* $Id: tpqic02.h,v 1.5 1996/12/14 23:01:38 root Exp root $&n; *&n; * Include file for QIC-02 driver for Linux.&n; *&n; * Copyright (c) 1992--1995 by H. H. Bergman. All rights reserved.&n; *&n; * ******* USER CONFIG SECTION BELOW (Near line 70) *******&n; */
macro_line|#ifndef _LINUX_TPQIC02_H
DECL|macro|_LINUX_TPQIC02_H
mdefine_line|#define _LINUX_TPQIC02_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if CONFIG_QIC02_TAPE || CONFIG_QIC02_TAPE_MODULE
multiline_comment|/* need to have QIC02_TAPE_DRIVE and QIC02_TAPE_IFC expand to something */
macro_line|#include &lt;linux/mtio.h&gt;
multiline_comment|/* Make QIC02_TAPE_IFC expand to something.&n; *&n; * The only difference between WANGTEK and EVEREX is in the &n; * handling of the DMA channel 3.&n; * Note that the driver maps EVEREX to WANGTEK internally for speed&n; * reasons. Externally WANGTEK==1, EVEREX==2, ARCHIVE==3.&n; * These must correspond to the values used in qic02config(1).&n; *&n; * Support for Mountain controllers was added by Erik Jacobson&n; * and severely hacked by me.   -- hhb&n; * &n; * Support for Emerald controllers by Alan Bain &lt;afrb2@chiark.chu.cam.ac.uk&gt;&n; * with more hacks by me.   -- hhb&n; */
DECL|macro|WANGTEK
mdefine_line|#define WANGTEK&t;&t;1&t;&t;   /* don&squot;t know about Wangtek QIC-36 */
DECL|macro|EVEREX
mdefine_line|#define EVEREX&t;&t;(WANGTEK+1)  /* I heard *some* of these are identical */
DECL|macro|EVEREX_811V
mdefine_line|#define EVEREX_811V&t;EVEREX&t;&t;&t;      /* With TEAC MT 2ST 45D */
DECL|macro|EVEREX_831V
mdefine_line|#define EVEREX_831V&t;EVEREX
DECL|macro|ARCHIVE
mdefine_line|#define ARCHIVE&t;&t;3
DECL|macro|ARCHIVE_SC400
mdefine_line|#define ARCHIVE_SC400&t;ARCHIVE&t;       /* rumoured to be from the pre-SMD-age */
DECL|macro|ARCHIVE_SC402
mdefine_line|#define ARCHIVE_SC402&t;ARCHIVE&t;&t;       /* don&squot;t know much about SC400 */
DECL|macro|ARCHIVE_SC499
mdefine_line|#define ARCHIVE_SC499&t;ARCHIVE       /* SC402 and SC499R should be identical */
DECL|macro|MOUNTAIN
mdefine_line|#define MOUNTAIN&t;5&t;&t;       /* Mountain Computer Interface */
DECL|macro|EMERALD
mdefine_line|#define EMERALD&t;&t;6&t;&t;       /* Emerald Interface card */
DECL|macro|QIC02_TAPE_PORT_RANGE
mdefine_line|#define QIC02_TAPE_PORT_RANGE &t;8&t; /* number of IO locations to reserve */
multiline_comment|/*********** START OF USER CONFIGURABLE SECTION ************/
multiline_comment|/* Tape configuration: Select DRIVE, IFC, PORT, IRQ and DMA below.&n; * Runtime (re)configuration is not supported yet.&n; *&n; * Tape drive configuration:&t;(MT_IS* constants are defined in mtio.h)&n; *&n; * QIC02_TAPE_DRIVE = MT_ISWT5150&n; *&t;- Wangtek 5150, format: up to QIC-150.&n; * QIC02_TAPE_DRIVE = MT_ISQIC02_ALL_FEATURES&n; *&t;- Enables some optional QIC02 commands that some drives may lack.&n; *&t;  It is provided so you can check which are supported by your drive.&n; *&t;  Refer to tpqic02.h for others.&n; *&n; * Supported interface cards: QIC02_TAPE_IFC =&n; *&t;WANGTEK,&n; *&t;ARCHIVE_SC402, ARCHIVE_SC499.&t;(both same programming interface)&n; *&n; * Make sure you have the I/O ports/DMA channels &n; * and IRQ stuff configured properly!&n; * NOTE: There may be other device drivers using the same major&n; *       number. This must be avoided. Check for timer.h conflicts too.&n; *&n; * If you have an EVEREX EV-831 card and you are using DMA channel 3,&n; * you will probably have to ``#define QIC02_TAPE_DMA3_FIX&squot;&squot; below.&n; */
multiline_comment|/* CONFIG_QIC02_DYNCONF can be defined in autoconf.h, by `make config&squot; */
multiline_comment|/*** #undef CONFIG_QIC02_DYNCONF ***/
macro_line|#ifndef CONFIG_QIC02_DYNCONF
DECL|macro|QIC02_TAPE_DRIVE
mdefine_line|#define QIC02_TAPE_DRIVE&t;MT_ISQIC02_ALL_FEATURES&t; /* drive type */
multiline_comment|/* #define QIC02_TAPE_DRIVE&t;MT_ISWT5150 */
multiline_comment|/* #define QIC02_TAPE_DRIVE&t;MT_ISARCHIVE_5945L2 */
multiline_comment|/* #define QIC02_TAPE_DRIVE&t;MT_ISTEAC_MT2ST */
multiline_comment|/* #define QIC02_TAPE_DRIVE&t;MT_ISARCHIVE_2150L */
multiline_comment|/* #define QIC02_TAPE_DRIVE&t;MT_ISARCHIVESC499 */
multiline_comment|/* Either WANGTEK, ARCHIVE or MOUNTAIN. Not EVEREX. &n; * If you have an EVEREX, use WANGTEK and try the DMA3_FIX below.&n; */
DECL|macro|QIC02_TAPE_IFC
mdefine_line|#define QIC02_TAPE_IFC&t;&t;WANGTEK&t;/* interface card type */
multiline_comment|/* #define QIC02_TAPE_IFC&t;&t;ARCHIVE */
multiline_comment|/* #define QIC02_TAPE_IFC&t;&t;MOUNTAIN */
DECL|macro|QIC02_TAPE_PORT
mdefine_line|#define QIC02_TAPE_PORT &t;0x300&t;/* controller port address */
DECL|macro|QIC02_TAPE_IRQ
mdefine_line|#define QIC02_TAPE_IRQ&t;&t;5&t;/* For IRQ2, use 9 here, others normal. */
DECL|macro|QIC02_TAPE_DMA
mdefine_line|#define QIC02_TAPE_DMA&t;&t;1&t;/* either 1 or 3, because 2 is used by the floppy */
multiline_comment|/* If DMA3 doesn&squot;t work, but DMA1 does, and you have a &n; * Wangtek/Everex card, you can try #define-ing the flag&n; * below. Note that you should also change the DACK jumper&n; * for Wangtek/Everex cards when changing the DMA channel.&n; */
DECL|macro|QIC02_TAPE_DMA3_FIX
macro_line|#undef QIC02_TAPE_DMA3_FIX
multiline_comment|/************ END OF USER CONFIGURABLE SECTION *************/
multiline_comment|/* I put the stuff above in config.in, but a few recompiles, to&n; * verify different configurations, and several days later I decided&n; * to change it back again.&n; */
multiline_comment|/* NOTE: TP_HAVE_DENS should distinguish between available densities (?)&n; * NOTE: Drive select is not implemented -- I have only one tape streamer,&n; *&t; so I&squot;m unable and unmotivated to test and implement that. ;-) ;-)&n; */
macro_line|#if QIC02_TAPE_DRIVE == MT_ISWT5150
DECL|macro|TP_HAVE_DENS
mdefine_line|#define TP_HAVE_DENS&t;1
DECL|macro|TP_HAVE_BSF
mdefine_line|#define TP_HAVE_BSF&t;0&t;/* nope */
DECL|macro|TP_HAVE_FSR
mdefine_line|#define TP_HAVE_FSR&t;0&t;/* nope */
DECL|macro|TP_HAVE_BSR
mdefine_line|#define TP_HAVE_BSR&t;0&t;/* nope */
DECL|macro|TP_HAVE_EOD
mdefine_line|#define TP_HAVE_EOD&t;0&t;/* most of the time */
DECL|macro|TP_HAVE_SEEK
mdefine_line|#define TP_HAVE_SEEK&t;0
DECL|macro|TP_HAVE_TELL
mdefine_line|#define TP_HAVE_TELL&t;0
DECL|macro|TP_HAVE_RAS1
mdefine_line|#define TP_HAVE_RAS1&t;1
DECL|macro|TP_HAVE_RAS2
mdefine_line|#define TP_HAVE_RAS2&t;1
macro_line|#elif QIC02_TAPE_DRIVE == MT_ISARCHIVESC499&t;/* Archive SC-499 QIC-36 controller */
DECL|macro|TP_HAVE_DENS
mdefine_line|#define TP_HAVE_DENS&t;1&t;/* can do set density (QIC-11 / QIC-24) */
DECL|macro|TP_HAVE_BSF
mdefine_line|#define TP_HAVE_BSF&t;0
DECL|macro|TP_HAVE_FSR
mdefine_line|#define TP_HAVE_FSR&t;1&t;/* can skip one block forwards */
DECL|macro|TP_HAVE_BSR
mdefine_line|#define TP_HAVE_BSR&t;1&t;/* can skip one block backwards */
DECL|macro|TP_HAVE_EOD
mdefine_line|#define TP_HAVE_EOD&t;1&t;/* can seek to end of recorded data */
DECL|macro|TP_HAVE_SEEK
mdefine_line|#define TP_HAVE_SEEK&t;0
DECL|macro|TP_HAVE_TELL
mdefine_line|#define TP_HAVE_TELL&t;0
DECL|macro|TP_HAVE_RAS1
mdefine_line|#define TP_HAVE_RAS1&t;1&t;/* can run selftest 1 */
DECL|macro|TP_HAVE_RAS2
mdefine_line|#define TP_HAVE_RAS2&t;1&t;/* can run selftest 2 */
multiline_comment|/* These last two selftests shouldn&squot;t be used yet! */
macro_line|#elif (QIC02_TAPE_DRIVE == MT_ISARCHIVE_2060L) || (QIC02_TAPE_DRIVE == MT_ISARCHIVE_2150L)
DECL|macro|TP_HAVE_DENS
mdefine_line|#define TP_HAVE_DENS&t;1&t;/* can do set density (QIC-24 / QIC-120 / QIC-150) */
DECL|macro|TP_HAVE_BSF
mdefine_line|#define TP_HAVE_BSF&t;0
DECL|macro|TP_HAVE_FSR
mdefine_line|#define TP_HAVE_FSR&t;1&t;/* can skip one block forwards */
DECL|macro|TP_HAVE_BSR
mdefine_line|#define TP_HAVE_BSR&t;1&t;/* can skip one block backwards */
DECL|macro|TP_HAVE_EOD
mdefine_line|#define TP_HAVE_EOD&t;1&t;/* can seek to end of recorded data */
DECL|macro|TP_HAVE_TELL
mdefine_line|#define TP_HAVE_TELL&t;1&t;/* can read current block address */
DECL|macro|TP_HAVE_SEEK
mdefine_line|#define TP_HAVE_SEEK&t;1&t;/* can seek to block */
DECL|macro|TP_HAVE_RAS1
mdefine_line|#define TP_HAVE_RAS1&t;1&t;/* can run selftest 1 */
DECL|macro|TP_HAVE_RAS2
mdefine_line|#define TP_HAVE_RAS2&t;1&t;/* can run selftest 2 */
multiline_comment|/* These last two selftests shouldn&squot;t be used yet! */
macro_line|#elif QIC02_TAPE_DRIVE == MT_ISARCHIVE_5945L2
multiline_comment|/* can anyone verify this entry?? */
DECL|macro|TP_HAVE_DENS
mdefine_line|#define TP_HAVE_DENS&t;1&t;/* can do set density?? (QIC-24??) */
DECL|macro|TP_HAVE_BSF
mdefine_line|#define TP_HAVE_BSF&t;0
DECL|macro|TP_HAVE_FSR
mdefine_line|#define TP_HAVE_FSR&t;1&t;/* can skip one block forwards */
DECL|macro|TP_HAVE_BSR
mdefine_line|#define TP_HAVE_BSR&t;1&t;/* can skip one block backwards */
DECL|macro|TP_HAVE_EOD
mdefine_line|#define TP_HAVE_EOD&t;1&t;/* can seek to end of recorded data */
DECL|macro|TP_HAVE_TELL
mdefine_line|#define TP_HAVE_TELL&t;1&t;/* can read current block address */
DECL|macro|TP_HAVE_SEEK
mdefine_line|#define TP_HAVE_SEEK&t;1&t;/* can seek to block */
DECL|macro|TP_HAVE_RAS1
mdefine_line|#define TP_HAVE_RAS1&t;1&t;/* can run selftest 1 */
DECL|macro|TP_HAVE_RAS2
mdefine_line|#define TP_HAVE_RAS2&t;1&t;/* can run selftest 2 */
multiline_comment|/* These last two selftests shouldn&squot;t be used yet! */
macro_line|#elif QIC02_TAPE_DRIVE == MT_ISTEAC_MT2ST
multiline_comment|/* can anyone verify this entry?? */
DECL|macro|TP_HAVE_DENS
mdefine_line|#define TP_HAVE_DENS&t;0&t;/* cannot do set density?? (QIC-150?) */
DECL|macro|TP_HAVE_BSF
mdefine_line|#define TP_HAVE_BSF&t;0
DECL|macro|TP_HAVE_FSR
mdefine_line|#define TP_HAVE_FSR&t;1&t;/* can skip one block forwards */
DECL|macro|TP_HAVE_BSR
mdefine_line|#define TP_HAVE_BSR&t;1&t;/* can skip one block backwards */
DECL|macro|TP_HAVE_EOD
mdefine_line|#define TP_HAVE_EOD&t;1&t;/* can seek to end of recorded data */
DECL|macro|TP_HAVE_SEEK
mdefine_line|#define TP_HAVE_SEEK&t;1&t;/* can seek to block */
DECL|macro|TP_HAVE_TELL
mdefine_line|#define TP_HAVE_TELL&t;1&t;/* can read current block address */
DECL|macro|TP_HAVE_RAS1
mdefine_line|#define TP_HAVE_RAS1&t;1&t;/* can run selftest 1 */
DECL|macro|TP_HAVE_RAS2
mdefine_line|#define TP_HAVE_RAS2&t;1&t;/* can run selftest 2 */
multiline_comment|/* These last two selftests shouldn&squot;t be used yet! */
macro_line|#elif QIC02_TAPE_DRIVE == MT_ISQIC02_ALL_FEATURES
DECL|macro|TP_HAVE_DENS
mdefine_line|#define TP_HAVE_DENS&t;1&t;/* can do set density */
DECL|macro|TP_HAVE_BSF
mdefine_line|#define TP_HAVE_BSF&t;1&t;/* can search filemark backwards */
DECL|macro|TP_HAVE_FSR
mdefine_line|#define TP_HAVE_FSR&t;1&t;/* can skip one block forwards */
DECL|macro|TP_HAVE_BSR
mdefine_line|#define TP_HAVE_BSR&t;1&t;/* can skip one block backwards */
DECL|macro|TP_HAVE_EOD
mdefine_line|#define TP_HAVE_EOD&t;1&t;/* can seek to end of recorded data */
DECL|macro|TP_HAVE_SEEK
mdefine_line|#define TP_HAVE_SEEK&t;1&t;/* seek to block address */
DECL|macro|TP_HAVE_TELL
mdefine_line|#define TP_HAVE_TELL&t;1&t;/* tell current block address */
DECL|macro|TP_HAVE_RAS1
mdefine_line|#define TP_HAVE_RAS1&t;1&t;/* can run selftest 1 */
DECL|macro|TP_HAVE_RAS2
mdefine_line|#define TP_HAVE_RAS2&t;1&t;/* can run selftest 2 */
multiline_comment|/* These last two selftests shouldn&squot;t be used yet! */
macro_line|#else
macro_line|#error No QIC-02 tape drive type defined!
multiline_comment|/* If your drive is not listed above, first try the &squot;ALL_FEATURES&squot;,&n; * to see what commands are supported, then create your own entry in&n; * the list above. You may want to mail it to me, so that I can include&n; * it in the next release.&n; */
macro_line|#endif
macro_line|#endif /* !CONFIG_QIC02_DYNCONF */
multiline_comment|/* WANGTEK interface card specifics */
DECL|macro|WT_QIC02_STAT_PORT
mdefine_line|#define WT_QIC02_STAT_PORT&t;(QIC02_TAPE_PORT)
DECL|macro|WT_QIC02_CTL_PORT
mdefine_line|#define WT_QIC02_CTL_PORT&t;(QIC02_TAPE_PORT)
DECL|macro|WT_QIC02_CMD_PORT
mdefine_line|#define WT_QIC02_CMD_PORT&t;(QIC02_TAPE_PORT+1)
DECL|macro|WT_QIC02_DATA_PORT
mdefine_line|#define WT_QIC02_DATA_PORT&t;(QIC02_TAPE_PORT+1)
multiline_comment|/* status register bits (Active LOW!) */
DECL|macro|WT_QIC02_STAT_POLARITY
mdefine_line|#define WT_QIC02_STAT_POLARITY&t;0
DECL|macro|WT_QIC02_STAT_READY
mdefine_line|#define WT_QIC02_STAT_READY&t;0x01
DECL|macro|WT_QIC02_STAT_EXCEPTION
mdefine_line|#define WT_QIC02_STAT_EXCEPTION&t;0x02
DECL|macro|WT_QIC02_STAT_MASK
mdefine_line|#define WT_QIC02_STAT_MASK&t;(WT_QIC02_STAT_READY|WT_QIC02_STAT_EXCEPTION)
DECL|macro|WT_QIC02_STAT_RESETMASK
mdefine_line|#define WT_QIC02_STAT_RESETMASK&t;0x07
DECL|macro|WT_QIC02_STAT_RESETVAL
mdefine_line|#define WT_QIC02_STAT_RESETVAL&t;(WT_QIC02_STAT_RESETMASK &amp; ~WT_QIC02_STAT_EXCEPTION)
multiline_comment|/* controller register (QIC02_CTL_PORT) bits */
DECL|macro|WT_QIC02_CTL_RESET
mdefine_line|#define WT_QIC02_CTL_RESET&t;0x02
DECL|macro|WT_QIC02_CTL_REQUEST
mdefine_line|#define WT_QIC02_CTL_REQUEST&t;0x04
DECL|macro|WT_CTL_ONLINE
mdefine_line|#define WT_CTL_ONLINE&t;&t;0x01
DECL|macro|WT_CTL_CMDOFF
mdefine_line|#define WT_CTL_CMDOFF&t;&t;0xC0 
DECL|macro|WT_CTL_DMA3
mdefine_line|#define WT_CTL_DMA3&t;&t;0x10&t;&t;&t;  /* enable dma chan3 */
DECL|macro|WT_CTL_DMA1
mdefine_line|#define WT_CTL_DMA1&t;&t;0x08&t;         /* enable dma chan1 or chan2 */
multiline_comment|/* EMERALD interface card specifics&n; * Much like Wangtek, only different polarity and bit locations&n; */
DECL|macro|EMR_QIC02_STAT_PORT
mdefine_line|#define EMR_QIC02_STAT_PORT&t;(QIC02_TAPE_PORT)
DECL|macro|EMR_QIC02_CTL_PORT
mdefine_line|#define EMR_QIC02_CTL_PORT&t;(QIC02_TAPE_PORT)
DECL|macro|EMR_QIC02_CMD_PORT
mdefine_line|#define EMR_QIC02_CMD_PORT&t;(QIC02_TAPE_PORT+1)
DECL|macro|EMR_QIC02_DATA_PORT
mdefine_line|#define EMR_QIC02_DATA_PORT&t;(QIC02_TAPE_PORT+1)
multiline_comment|/* status register bits (Active High!) */
DECL|macro|EMR_QIC02_STAT_POLARITY
mdefine_line|#define EMR_QIC02_STAT_POLARITY&t;&t;1
DECL|macro|EMR_QIC02_STAT_READY
mdefine_line|#define EMR_QIC02_STAT_READY&t;&t;0x01
DECL|macro|EMR_QIC02_STAT_EXCEPTION
mdefine_line|#define EMR_QIC02_STAT_EXCEPTION&t;0x02
DECL|macro|EMR_QIC02_STAT_MASK
mdefine_line|#define EMR_QIC02_STAT_MASK&t;(EMR_QIC02_STAT_READY|EMR_QIC02_STAT_EXCEPTION)
DECL|macro|EMR_QIC02_STAT_RESETMASK
mdefine_line|#define EMR_QIC02_STAT_RESETMASK&t;0x07
DECL|macro|EMR_QIC02_STAT_RESETVAL
mdefine_line|#define EMR_QIC02_STAT_RESETVAL&t;(EMR_QIC02_STAT_RESETMASK &amp; ~EMR_QIC02_STAT_EXCEPTION)
multiline_comment|/* controller register (QIC02_CTL_PORT) bits */
DECL|macro|EMR_QIC02_CTL_RESET
mdefine_line|#define EMR_QIC02_CTL_RESET&t;0x02
DECL|macro|EMR_QIC02_CTL_REQUEST
mdefine_line|#define EMR_QIC02_CTL_REQUEST&t;0x04
DECL|macro|EMR_CTL_ONLINE
mdefine_line|#define EMR_CTL_ONLINE&t;&t;0x01
DECL|macro|EMR_CTL_CMDOFF
mdefine_line|#define EMR_CTL_CMDOFF&t;&t;0xC0 
DECL|macro|EMR_CTL_DMA3
mdefine_line|#define EMR_CTL_DMA3&t;&t;0x10&t;&t;&t;  /* enable dma chan3 */
DECL|macro|EMR_CTL_DMA1
mdefine_line|#define EMR_CTL_DMA1&t;&t;0x08&t;         /* enable dma chan1 or chan2 */
multiline_comment|/* ARCHIVE interface card specifics */
DECL|macro|AR_QIC02_STAT_PORT
mdefine_line|#define AR_QIC02_STAT_PORT&t;(QIC02_TAPE_PORT+1)
DECL|macro|AR_QIC02_CTL_PORT
mdefine_line|#define AR_QIC02_CTL_PORT&t;(QIC02_TAPE_PORT+1)
DECL|macro|AR_QIC02_CMD_PORT
mdefine_line|#define AR_QIC02_CMD_PORT&t;(QIC02_TAPE_PORT)
DECL|macro|AR_QIC02_DATA_PORT
mdefine_line|#define AR_QIC02_DATA_PORT&t;(QIC02_TAPE_PORT)
DECL|macro|AR_START_DMA_PORT
mdefine_line|#define AR_START_DMA_PORT&t;(QIC02_TAPE_PORT+2)
DECL|macro|AR_RESET_DMA_PORT
mdefine_line|#define AR_RESET_DMA_PORT&t;(QIC02_TAPE_PORT+3)
multiline_comment|/* STAT port bits */
DECL|macro|AR_QIC02_STAT_POLARITY
mdefine_line|#define AR_QIC02_STAT_POLARITY&t;0
DECL|macro|AR_STAT_IRQF
mdefine_line|#define AR_STAT_IRQF&t;&t;0x80&t;/* active high, interrupt request flag */
DECL|macro|AR_QIC02_STAT_READY
mdefine_line|#define AR_QIC02_STAT_READY&t;0x40&t;/* active low */
DECL|macro|AR_QIC02_STAT_EXCEPTION
mdefine_line|#define AR_QIC02_STAT_EXCEPTION&t;0x20&t;/* active low */
DECL|macro|AR_QIC02_STAT_MASK
mdefine_line|#define AR_QIC02_STAT_MASK&t;(AR_QIC02_STAT_READY|AR_QIC02_STAT_EXCEPTION)
DECL|macro|AR_STAT_DMADONE
mdefine_line|#define AR_STAT_DMADONE&t;&t;0x10&t;/* active high, DMA done */
DECL|macro|AR_STAT_DIRC
mdefine_line|#define AR_STAT_DIRC&t;&t;0x08&t;/* active high, direction */
DECL|macro|AR_QIC02_STAT_RESETMASK
mdefine_line|#define AR_QIC02_STAT_RESETMASK&t;0x70&t;/* check RDY,EXC,DMADONE */
DECL|macro|AR_QIC02_STAT_RESETVAL
mdefine_line|#define AR_QIC02_STAT_RESETVAL&t;((AR_QIC02_STAT_RESETMASK &amp; ~AR_STAT_IRQF &amp; ~AR_QIC02_STAT_EXCEPTION) | AR_STAT_DMADONE)
multiline_comment|/* CTL port bits */
DECL|macro|AR_QIC02_CTL_RESET
mdefine_line|#define AR_QIC02_CTL_RESET&t;0x80&t;/* drive reset */
DECL|macro|AR_QIC02_CTL_REQUEST
mdefine_line|#define AR_QIC02_CTL_REQUEST&t;0x40&t;/* notify of new command */
DECL|macro|AR_CTL_IEN
mdefine_line|#define AR_CTL_IEN&t;&t;0x20&t;/* interrupt enable */
DECL|macro|AR_CTL_DNIEN
mdefine_line|#define AR_CTL_DNIEN&t;&t;0x10&t;/* done-interrupt enable */
multiline_comment|/* Note: All of these bits are cleared automatically when writing to&n;   * AR_RESET_DMA_PORT. So AR_CTL_IEN and AR_CTL_DNIEN must be&n;   * reprogrammed before the write to AR_START_DMA_PORT.&n;   */
multiline_comment|/* MOUNTAIN interface specifics */
DECL|macro|MTN_QIC02_STAT_PORT
mdefine_line|#define MTN_QIC02_STAT_PORT&t;(QIC02_TAPE_PORT+1)
DECL|macro|MTN_QIC02_CTL_PORT
mdefine_line|#define MTN_QIC02_CTL_PORT&t;(QIC02_TAPE_PORT+1)
DECL|macro|MTN_QIC02_CMD_PORT
mdefine_line|#define MTN_QIC02_CMD_PORT&t;(QIC02_TAPE_PORT)
DECL|macro|MTN_QIC02_DATA_PORT
mdefine_line|#define MTN_QIC02_DATA_PORT&t;(QIC02_TAPE_PORT)
DECL|macro|MTN_W_SELECT_DMA_PORT
mdefine_line|#define MTN_W_SELECT_DMA_PORT&t;(QIC02_TAPE_PORT+2)
DECL|macro|MTN_R_DESELECT_DMA_PORT
mdefine_line|#define MTN_R_DESELECT_DMA_PORT&t;(QIC02_TAPE_PORT+2)
DECL|macro|MTN_W_DMA_WRITE_PORT
mdefine_line|#define MTN_W_DMA_WRITE_PORT&t;(QIC02_TAPE_PORT+3)
multiline_comment|/* STAT port bits */
DECL|macro|MTN_QIC02_STAT_POLARITY
mdefine_line|#define MTN_QIC02_STAT_POLARITY&t; 0
DECL|macro|MTN_QIC02_STAT_READY
mdefine_line|#define MTN_QIC02_STAT_READY&t; 0x02&t;/* active low */
DECL|macro|MTN_QIC02_STAT_EXCEPTION
mdefine_line|#define MTN_QIC02_STAT_EXCEPTION 0x04&t;/* active low */
DECL|macro|MTN_QIC02_STAT_MASK
mdefine_line|#define MTN_QIC02_STAT_MASK&t; (MTN_QIC02_STAT_READY|MTN_QIC02_STAT_EXCEPTION)
DECL|macro|MTN_STAT_DMADONE
mdefine_line|#define MTN_STAT_DMADONE&t; 0x01&t;/* active high, DMA done */
DECL|macro|MTN_QIC02_STAT_RESETMASK
mdefine_line|#define MTN_QIC02_STAT_RESETMASK 0x07&t;/* check RDY,EXC,DMADONE */
DECL|macro|MTN_QIC02_STAT_RESETVAL
mdefine_line|#define MTN_QIC02_STAT_RESETVAL&t; ((MTN_QIC02_STAT_RESETMASK &amp; ~MTN_QIC02_STAT_EXCEPTION) | MTN_STAT_DMADONE)
multiline_comment|/* CTL port bits */
DECL|macro|MTN_QIC02_CTL_RESET_NOT
mdefine_line|#define MTN_QIC02_CTL_RESET_NOT&t; 0x80&t;/* drive reset, active low */
DECL|macro|MTN_QIC02_CTL_RESET
mdefine_line|#define MTN_QIC02_CTL_RESET&t; 0x80&t;/* Fodder #definition to keep gcc happy */
DECL|macro|MTN_QIC02_CTL_ONLINE
mdefine_line|#define MTN_QIC02_CTL_ONLINE&t; 0x40&t;/* Put drive on line  */
DECL|macro|MTN_QIC02_CTL_REQUEST
mdefine_line|#define MTN_QIC02_CTL_REQUEST&t; 0x20&t;/* notify of new command */
DECL|macro|MTN_QIC02_CTL_IRQ_DRIVER
mdefine_line|#define MTN_QIC02_CTL_IRQ_DRIVER 0x10&t;/* Enable IRQ tristate driver */
DECL|macro|MTN_QIC02_CTL_DMA_DRIVER
mdefine_line|#define MTN_QIC02_CTL_DMA_DRIVER 0x08&t;/* Enable DMA tristate driver */
DECL|macro|MTN_CTL_EXC_IEN
mdefine_line|#define MTN_CTL_EXC_IEN&t;&t; 0x04&t;/* Exception interrupt enable */
DECL|macro|MTN_CTL_RDY_IEN
mdefine_line|#define MTN_CTL_RDY_IEN&t;&t; 0x02&t;/* Ready interrupt enable */
DECL|macro|MTN_CTL_DNIEN
mdefine_line|#define MTN_CTL_DNIEN&t;&t; 0x01&t;/* done-interrupt enable */
DECL|macro|MTN_CTL_ONLINE
mdefine_line|#define MTN_CTL_ONLINE&t;&t;(MTN_QIC02_CTL_RESET_NOT | MTN_QIC02_CTL_IRQ_DRIVER | MTN_QIC02_CTL_DMA_DRIVER)
macro_line|#ifndef CONFIG_QIC02_DYNCONF
DECL|macro|QIC02_TAPE_DEBUG
macro_line|# define QIC02_TAPE_DEBUG&t;(qic02_tape_debug)
macro_line|# if QIC02_TAPE_IFC == WANGTEK&t;
DECL|macro|QIC02_STAT_POLARITY
macro_line|#  define QIC02_STAT_POLARITY&t;WT_QIC02_STAT_POLARITY
DECL|macro|QIC02_STAT_PORT
macro_line|#  define QIC02_STAT_PORT&t;WT_QIC02_STAT_PORT
DECL|macro|QIC02_CTL_PORT
macro_line|#  define QIC02_CTL_PORT&t;WT_QIC02_CTL_PORT
DECL|macro|QIC02_CMD_PORT
macro_line|#  define QIC02_CMD_PORT&t;WT_QIC02_CMD_PORT
DECL|macro|QIC02_DATA_PORT
macro_line|#  define QIC02_DATA_PORT&t;WT_QIC02_DATA_PORT
DECL|macro|QIC02_STAT_READY
macro_line|#  define QIC02_STAT_READY&t;WT_QIC02_STAT_READY
DECL|macro|QIC02_STAT_EXCEPTION
macro_line|#  define QIC02_STAT_EXCEPTION&t;WT_QIC02_STAT_EXCEPTION
DECL|macro|QIC02_STAT_MASK
macro_line|#  define QIC02_STAT_MASK&t;WT_QIC02_STAT_MASK
DECL|macro|QIC02_STAT_RESETMASK
macro_line|#  define QIC02_STAT_RESETMASK&t;WT_QIC02_STAT_RESETMASK
DECL|macro|QIC02_STAT_RESETVAL
macro_line|#  define QIC02_STAT_RESETVAL&t;WT_QIC02_STAT_RESETVAL
DECL|macro|QIC02_CTL_RESET
macro_line|#  define QIC02_CTL_RESET&t;WT_QIC02_CTL_RESET
DECL|macro|QIC02_CTL_REQUEST
macro_line|#  define QIC02_CTL_REQUEST&t;WT_QIC02_CTL_REQUEST
macro_line|#  if QIC02_TAPE_DMA == 3
macro_line|#   ifdef QIC02_TAPE_DMA3_FIX
DECL|macro|WT_CTL_DMA
macro_line|#    define WT_CTL_DMA&t;&t;WT_CTL_DMA1
macro_line|#   else
DECL|macro|WT_CTL_DMA
macro_line|#    define WT_CTL_DMA&t;&t;WT_CTL_DMA3
macro_line|#   endif
macro_line|#  elif QIC02_TAPE_DMA == 1
DECL|macro|WT_CTL_DMA
macro_line|#    define WT_CTL_DMA&t;&t;WT_CTL_DMA1
macro_line|#  else
macro_line|#   error Unsupported or incorrect DMA configuration.
macro_line|#  endif
macro_line|# elif QIC02_TAPE_IFC == EMERALD
DECL|macro|QIC02_STAT_POLARITY
macro_line|#  define QIC02_STAT_POLARITY&t;EMR_QIC02_STAT_POLARITY
DECL|macro|QIC02_STAT_PORT
macro_line|#  define QIC02_STAT_PORT&t;EMR_QIC02_STAT_PORT
DECL|macro|QIC02_CTL_PORT
macro_line|#  define QIC02_CTL_PORT&t;EMR_QIC02_CTL_PORT
DECL|macro|QIC02_CMD_PORT
macro_line|#  define QIC02_CMD_PORT&t;EMR_QIC02_CMD_PORT
DECL|macro|QIC02_DATA_PORT
macro_line|#  define QIC02_DATA_PORT&t;EMR_QIC02_DATA_PORT
DECL|macro|QIC02_STAT_READY
macro_line|#  define QIC02_STAT_READY&t;EMR_QIC02_STAT_READY
DECL|macro|QIC02_STAT_EXCEPTION
macro_line|#  define QIC02_STAT_EXCEPTION&t;EMR_QIC02_STAT_EXCEPTION
DECL|macro|QIC02_STAT_MASK
macro_line|#  define QIC02_STAT_MASK&t;EMR_QIC02_STAT_MASK
DECL|macro|QIC02_STAT_RESETMASK
macro_line|#  define QIC02_STAT_RESETMASK&t;EMR_QIC02_STAT_RESETMASK
DECL|macro|QIC02_STAT_RESETVAL
macro_line|#  define QIC02_STAT_RESETVAL&t;EMR_QIC02_STAT_RESETVAL
DECL|macro|QIC02_CTL_RESET
macro_line|#  define QIC02_CTL_RESET&t;EMR_QIC02_CTL_RESET
DECL|macro|QIC02_CTL_REQUEST
macro_line|#  define QIC02_CTL_REQUEST&t;EMR_QIC02_CTL_REQUEST
macro_line|#  if QIC02_TAPE_DMA == 3
macro_line|#   ifdef QIC02_TAPE_DMA3_FIX
DECL|macro|EMR_CTL_DMA
macro_line|#    define EMR_CTL_DMA&t;&t;EMR_CTL_DMA1
macro_line|#   else
DECL|macro|EMR_CTL_DMA
macro_line|#    define EMR_CTL_DMA&t;&t;EMR_CTL_DMA3
macro_line|#   endif
macro_line|#  elif QIC02_TAPE_DMA == 1
DECL|macro|EMR_CTL_DMA
macro_line|#    define EMR_CTL_DMA&t;&t;EMR_CTL_DMA1
macro_line|#  else
macro_line|#   error Unsupported or incorrect DMA configuration.
macro_line|#  endif
macro_line|# elif QIC02_TAPE_IFC == ARCHIVE
DECL|macro|QIC02_STAT_POLARITY
macro_line|#  define QIC02_STAT_POLARITY&t;AR_QIC02_STAT_POLARITY
DECL|macro|QIC02_STAT_PORT
macro_line|#  define QIC02_STAT_PORT&t;AR_QIC02_STAT_PORT
DECL|macro|QIC02_CTL_PORT
macro_line|#  define QIC02_CTL_PORT&t;AR_QIC02_CTL_PORT
DECL|macro|QIC02_CMD_PORT
macro_line|#  define QIC02_CMD_PORT&t;AR_QIC02_CMD_PORT
DECL|macro|QIC02_DATA_PORT
macro_line|#  define QIC02_DATA_PORT&t;AR_QIC02_DATA_PORT
DECL|macro|QIC02_STAT_READY
macro_line|#  define QIC02_STAT_READY&t;AR_QIC02_STAT_READY
DECL|macro|QIC02_STAT_EXCEPTION
macro_line|#  define QIC02_STAT_EXCEPTION&t;AR_QIC02_STAT_EXCEPTION
DECL|macro|QIC02_STAT_MASK
macro_line|#  define QIC02_STAT_MASK&t;AR_QIC02_STAT_MASK
DECL|macro|QIC02_STAT_RESETMASK
macro_line|#  define QIC02_STAT_RESETMASK&t;AR_QIC02_STAT_RESETMASK
DECL|macro|QIC02_STAT_RESETVAL
macro_line|#  define QIC02_STAT_RESETVAL&t;AR_QIC02_STAT_RESETVAL
DECL|macro|QIC02_CTL_RESET
macro_line|#  define QIC02_CTL_RESET&t;AR_QIC02_CTL_RESET
DECL|macro|QIC02_CTL_REQUEST
macro_line|#  define QIC02_CTL_REQUEST&t;AR_QIC02_CTL_REQUEST
macro_line|#  if QIC02_TAPE_DMA &gt; 3&t;/* channel 2 is used by the floppy driver */
macro_line|#   error DMA channels other than 1 and 3 are not supported.
macro_line|#  endif
macro_line|# elif QIC02_TAPE_IFC == MOUNTAIN
DECL|macro|QIC02_STAT_POLARITY
macro_line|#  define QIC02_STAT_POLARITY&t;MTN_QIC02_STAT_POLARITY
DECL|macro|QIC02_STAT_PORT
macro_line|#  define QIC02_STAT_PORT&t;MTN_QIC02_STAT_PORT
DECL|macro|QIC02_CTL_PORT
macro_line|#  define QIC02_CTL_PORT&t;MTN_QIC02_CTL_PORT
DECL|macro|QIC02_CMD_PORT
macro_line|#  define QIC02_CMD_PORT&t;MTN_QIC02_CMD_PORT
DECL|macro|QIC02_DATA_PORT
macro_line|#  define QIC02_DATA_PORT&t;MTN_QIC02_DATA_PORT
DECL|macro|QIC02_STAT_READY
macro_line|#  define QIC02_STAT_READY&t;MTN_QIC02_STAT_READY
DECL|macro|QIC02_STAT_EXCEPTION
macro_line|#  define QIC02_STAT_EXCEPTION&t;MTN_QIC02_STAT_EXCEPTION
DECL|macro|QIC02_STAT_MASK
macro_line|#  define QIC02_STAT_MASK&t;MTN_QIC02_STAT_MASK
DECL|macro|QIC02_STAT_RESETMASK
macro_line|#  define QIC02_STAT_RESETMASK&t;MTN_QIC02_STAT_RESETMASK
DECL|macro|QIC02_STAT_RESETVAL
macro_line|#  define QIC02_STAT_RESETVAL&t;MTN_QIC02_STAT_RESETVAL
DECL|macro|QIC02_CTL_RESET
macro_line|#  define QIC02_CTL_RESET&t;MTN_QIC02_CTL_RESET
DECL|macro|QIC02_CTL_REQUEST
macro_line|#  define QIC02_CTL_REQUEST&t;MTN_QIC02_CTL_REQUEST
macro_line|#  if QIC02_TAPE_DMA &gt; 3&t;/* channel 2 is used by the floppy driver */
macro_line|#   error DMA channels other than 1 and 3 are not supported.
macro_line|#  endif
macro_line|# else
macro_line|#  error No valid interface card specified!
macro_line|# endif /* QIC02_TAPE_IFC */
multiline_comment|/* An ugly hack to make sure WT_CTL_DMA is defined even for the&n;   * static, non-Wangtek case. The alternative was even worse.&n;   */
macro_line|# ifndef WT_CTL_DMA
DECL|macro|WT_CTL_DMA
macro_line|#  define WT_CTL_DMA&t;&t;WT_CTL_DMA1
macro_line|# endif
multiline_comment|/*******************/
macro_line|#else /* !CONFIG_QIC02_DYNCONF */
multiline_comment|/* Now the runtime config version, using variables instead of constants.&n; *&n; * qic02_tape_dynconf is R/O for the kernel, set from userspace.&n; * qic02_tape_ccb is private to the driver, R/W.&n; */
DECL|macro|QIC02_TAPE_DRIVE
macro_line|# define QIC02_TAPE_DRIVE&t;(qic02_tape_dynconf.mt_type)
DECL|macro|QIC02_TAPE_IFC
macro_line|# define QIC02_TAPE_IFC&t;&t;(qic02_tape_ccb.ifc_type)
DECL|macro|QIC02_TAPE_IRQ
macro_line|# define QIC02_TAPE_IRQ&t;&t;(qic02_tape_dynconf.irqnr)
DECL|macro|QIC02_TAPE_DMA
macro_line|# define QIC02_TAPE_DMA&t;&t;(qic02_tape_dynconf.dmanr)
DECL|macro|QIC02_TAPE_PORT
macro_line|# define QIC02_TAPE_PORT&t;(qic02_tape_dynconf.port)
DECL|macro|WT_CTL_DMA
macro_line|# define WT_CTL_DMA&t;&t;(qic02_tape_ccb.dma_enable_value)
DECL|macro|QIC02_TAPE_DEBUG
macro_line|# define QIC02_TAPE_DEBUG&t;(qic02_tape_dynconf.debug)
DECL|macro|QIC02_STAT_PORT
macro_line|# define QIC02_STAT_PORT&t;(qic02_tape_ccb.port_stat)
DECL|macro|QIC02_CTL_PORT
macro_line|# define QIC02_CTL_PORT &t;(qic02_tape_ccb.port_ctl)
DECL|macro|QIC02_CMD_PORT
macro_line|# define QIC02_CMD_PORT &t;(qic02_tape_ccb.port_cmd)
DECL|macro|QIC02_DATA_PORT
macro_line|# define QIC02_DATA_PORT &t;(qic02_tape_ccb.port_data)
DECL|macro|QIC02_STAT_POLARITY
macro_line|# define QIC02_STAT_POLARITY&t;(qic02_tape_ccb.stat_polarity)
DECL|macro|QIC02_STAT_READY
macro_line|# define QIC02_STAT_READY&t;(qic02_tape_ccb.stat_ready)
DECL|macro|QIC02_STAT_EXCEPTION
macro_line|# define QIC02_STAT_EXCEPTION&t;(qic02_tape_ccb.stat_exception)
DECL|macro|QIC02_STAT_MASK
macro_line|# define QIC02_STAT_MASK&t;(qic02_tape_ccb.stat_mask)
DECL|macro|QIC02_STAT_RESETMASK
macro_line|# define QIC02_STAT_RESETMASK&t;(qic02_tape_ccb.stat_resetmask)
DECL|macro|QIC02_STAT_RESETVAL
macro_line|# define QIC02_STAT_RESETVAL&t;(qic02_tape_ccb.stat_resetval)
DECL|macro|QIC02_CTL_RESET
macro_line|# define QIC02_CTL_RESET&t;(qic02_tape_ccb.ctl_reset)
DECL|macro|QIC02_CTL_REQUEST
macro_line|# define QIC02_CTL_REQUEST&t;(qic02_tape_ccb.ctl_request)
DECL|macro|TP_HAVE_DENS
macro_line|# define TP_HAVE_DENS&t;&t;(qic02_tape_dynconf.have_dens)
DECL|macro|TP_HAVE_BSF
macro_line|# define TP_HAVE_BSF&t;&t;(qic02_tape_dynconf.have_bsf)
DECL|macro|TP_HAVE_FSR
macro_line|# define TP_HAVE_FSR&t;&t;(qic02_tape_dynconf.have_fsr)
DECL|macro|TP_HAVE_BSR
macro_line|# define TP_HAVE_BSR&t;&t;(qic02_tape_dynconf.have_bsr)
DECL|macro|TP_HAVE_EOD
macro_line|# define TP_HAVE_EOD&t;&t;(qic02_tape_dynconf.have_eod)
DECL|macro|TP_HAVE_SEEK
macro_line|# define TP_HAVE_SEEK&t;&t;(qic02_tape_dynconf.have_seek)
DECL|macro|TP_HAVE_TELL
macro_line|# define TP_HAVE_TELL&t;&t;(qic02_tape_dynconf.have_tell)
DECL|macro|TP_HAVE_RAS1
macro_line|# define TP_HAVE_RAS1&t;&t;(qic02_tape_dynconf.have_ras1)
DECL|macro|TP_HAVE_RAS2
macro_line|# define TP_HAVE_RAS2&t;&t;(qic02_tape_dynconf.have_ras2)
macro_line|#endif /* CONFIG_QIC02_DYNCONF */
multiline_comment|/* &quot;Vendor Unique&quot; codes */
multiline_comment|/* Archive seek &amp; tell stuff */
DECL|macro|AR_QCMDV_TELL_BLK
mdefine_line|#define AR_QCMDV_TELL_BLK&t;0xAE&t;/* read current block address */
DECL|macro|AR_QCMDV_SEEK_BLK
mdefine_line|#define AR_QCMDV_SEEK_BLK&t;0xAD&t;/* seek to specific block */
DECL|macro|AR_SEEK_BUF_SIZE
mdefine_line|#define AR_SEEK_BUF_SIZE&t;3&t;/* address is 3 bytes */
multiline_comment|/*&n; * Misc common stuff&n; */
multiline_comment|/* Standard QIC-02 commands -- rev F.  All QIC-02 drives must support these */
DECL|macro|QCMD_SEL_1
mdefine_line|#define QCMD_SEL_1&t;0x01&t;&t;/* select drive 1 */
DECL|macro|QCMD_SEL_2
mdefine_line|#define QCMD_SEL_2&t;0x02&t;&t;/* select drive 2 */
DECL|macro|QCMD_SEL_3
mdefine_line|#define QCMD_SEL_3&t;0x04&t;&t;/* select drive 3 */
DECL|macro|QCMD_SEL_4
mdefine_line|#define QCMD_SEL_4&t;0x08&t;&t;/* select drive 4 */
DECL|macro|QCMD_REWIND
mdefine_line|#define&t;QCMD_REWIND&t;0x21&t;&t;/* rewind tape */
DECL|macro|QCMD_ERASE
mdefine_line|#define QCMD_ERASE&t;0x22&t;&t;/* erase tape */
DECL|macro|QCMD_RETEN
mdefine_line|#define QCMD_RETEN&t;0x24&t;&t;/* retension tape */
DECL|macro|QCMD_WRT_DATA
mdefine_line|#define&t;QCMD_WRT_DATA&t;0x40&t;&t;/* write data */
DECL|macro|QCMD_WRT_FM
mdefine_line|#define&t;QCMD_WRT_FM&t;0x60&t;&t;/* write file mark */
DECL|macro|QCMD_RD_DATA
mdefine_line|#define&t;QCMD_RD_DATA&t;0x80&t;&t;/* read data */
DECL|macro|QCMD_RD_FM
mdefine_line|#define&t;QCMD_RD_FM&t;0xA0&t;&t;/* read file mark (forward direction) */
DECL|macro|QCMD_RD_STAT
mdefine_line|#define&t;QCMD_RD_STAT&t;0xC0&t;&t;/* read status */
multiline_comment|/* Other (optional/vendor unique) commands */
multiline_comment|/* Density commands are only valid when TP_BOM is set! */
DECL|macro|QCMD_DENS_11
mdefine_line|#define QCMD_DENS_11&t;0x26&t;&t;/* QIC-11 */
DECL|macro|QCMD_DENS_24
mdefine_line|#define QCMD_DENS_24&t;0x27&t;&t;/* QIC-24: 9 track 60MB */
DECL|macro|QCMD_DENS_120
mdefine_line|#define QCMD_DENS_120&t;0x28&t;&t;/* QIC-120: 15 track 120MB */
DECL|macro|QCMD_DENS_150
mdefine_line|#define QCMD_DENS_150&t;0x29&t;&t;/* QIC-150: 18 track 150MB */
DECL|macro|QCMD_DENS_300
mdefine_line|#define QCMD_DENS_300&t;0x2A&t;&t;/* QIC-300/QIC-2100 */
DECL|macro|QCMD_DENS_600
mdefine_line|#define QCMD_DENS_600&t;0x2B&t;&t;/* QIC-600/QIC-2200 */
multiline_comment|/* don&squot;t know about QIC-1000 and QIC-1350 */
DECL|macro|QCMD_WRTNU_DATA
mdefine_line|#define&t;QCMD_WRTNU_DATA&t;0x40&t;&t;/* write data, no underruns, insert filler. */
DECL|macro|QCMD_SPACE_FWD
mdefine_line|#define QCMD_SPACE_FWD&t;0x81&t;&t;/* skip next block */
DECL|macro|QCMD_SPACE_BCK
mdefine_line|#define QCMD_SPACE_BCK&t;0x89&t;&t;/* move tape head one block back -- very useful! */
DECL|macro|QCMD_RD_FM_BCK
mdefine_line|#define QCMD_RD_FM_BCK&t;0xA8&t;&t;/* read filemark (backwards) */
DECL|macro|QCMD_SEEK_EOD
mdefine_line|#define QCMD_SEEK_EOD&t;0xA3&t;&t;/* skip to EOD */
DECL|macro|QCMD_RD_STAT_X1
mdefine_line|#define&t;QCMD_RD_STAT_X1&t;0xC1&t;&t;/* read extended status 1 */
DECL|macro|QCMD_RD_STAT_X2
mdefine_line|#define&t;QCMD_RD_STAT_X2&t;0xC4&t;&t;/* read extended status 2 */
DECL|macro|QCMD_RD_STAT_X3
mdefine_line|#define&t;QCMD_RD_STAT_X3&t;0xE0&t;&t;/* read extended status 3 */
DECL|macro|QCMD_SELF_TST1
mdefine_line|#define QCMD_SELF_TST1&t;0xC2&t;&t;/* run self test 1 (nondestructive) */
DECL|macro|QCMD_SELF_TST2
mdefine_line|#define QCMD_SELF_TST2&t;0xCA&t;&t;/* run self test 2 (destructive) */
multiline_comment|/* Optional, QFA (Quick File Access) commands.&n; * Not all drives support this, but those that do could use these commands&n; * to implement semi-non-sequential access. `mt fsf` would benefit from this.&n; * QFA divides the tape into 2 partitions, a data and a directory partition,&n; * causing some incompatibility problems wrt std QIC-02 data exchange.&n; * It would be useful to cache the directory info, but that might be tricky&n; * to do in kernel-space. [Size constraints.]&n; * Refer to the QIC-02 specs, appendix A for more information.&n; * I have no idea how other *nix variants implement QFA.&n; * I have no idea which drives support QFA and which don&squot;t.&n; */
DECL|macro|QFA_ENABLE
mdefine_line|#define QFA_ENABLE&t;0x2D&t;&t;/* enter QFA mode, give @ BOT only */
DECL|macro|QFA_DATA
mdefine_line|#define QFA_DATA&t;0x20&t;&t;/* select data partition */
DECL|macro|QFA_DIR
mdefine_line|#define QFA_DIR&t;&t;0x23&t;&t;/* select directory partition */
DECL|macro|QFA_RD_POS
mdefine_line|#define QFA_RD_POS&t;0xCF&t;&t;/* read position+status bytes */
DECL|macro|QFA_SEEK_EOD
mdefine_line|#define QFA_SEEK_EOD&t;0xA1&t;&t;/* seek EOD within current partition */
DECL|macro|QFA_SEEK_BLK
mdefine_line|#define QFA_SEEK_BLK&t;0xAF&t;&t;/* seek to a block within current partition */
multiline_comment|/*&n; * Debugging flags&n; */
DECL|macro|TPQD_SENSE_TEXT
mdefine_line|#define TPQD_SENSE_TEXT&t;0x0001
DECL|macro|TPQD_SENSE_CNTS
mdefine_line|#define TPQD_SENSE_CNTS 0x0002
DECL|macro|TPQD_REWIND
mdefine_line|#define TPQD_REWIND&t;0x0004
DECL|macro|TPQD_TERM_CYCLE
mdefine_line|#define TPQD_TERM_CYCLE&t;0x0008
DECL|macro|TPQD_IOCTLS
mdefine_line|#define TPQD_IOCTLS&t;0x0010
DECL|macro|TPQD_DMAX
mdefine_line|#define TPQD_DMAX&t;0x0020
DECL|macro|TPQD_BLKSZ
mdefine_line|#define TPQD_BLKSZ&t;0x0040
DECL|macro|TPQD_MISC
mdefine_line|#define TPQD_MISC&t;0x0080
DECL|macro|TPQD_DEBUG
mdefine_line|#define TPQD_DEBUG&t;0x0100
DECL|macro|TPQD_DIAGS
mdefine_line|#define TPQD_DIAGS&t;0x1000
DECL|macro|TPQD_ALWAYS
mdefine_line|#define TPQD_ALWAYS&t;0x8000
DECL|macro|TPQD_DEFAULT_FLAGS
mdefine_line|#define TPQD_DEFAULT_FLAGS&t;0x00fc
DECL|macro|TPQDBG
mdefine_line|#define TPQDBG(f)&t;((QIC02_TAPE_DEBUG) &amp; (TPQD_##f))
multiline_comment|/* Minor device codes for tapes:&n; * |7|6|5|4|3|2|1|0|&n; *  | &bslash; | / &bslash; | / |_____ 1=rewind on close, 0=no rewind on close&n; *  |  &bslash;|/    |_________ Density: 000=none, 001=QIC-11, 010=24, 011=120,&n; *  |   |                100=QIC-150, 101..111 reserved.&n; *  |   |_______________ Reserved for unit numbers.&n; *  |___________________ Reserved for diagnostics during debugging.&n; */
DECL|macro|TP_REWCLOSE
mdefine_line|#define&t;TP_REWCLOSE(d)&t;((minor(d)&amp;0x01) == 1)&t;   &t;&t;/* rewind bit */
multiline_comment|/* rewind is only done if data has been transferred */
DECL|macro|TP_DENS
mdefine_line|#define&t;TP_DENS(dev)&t;((minor(dev) &gt;&gt; 1) &amp; 0x07) &t;      /* tape density */
DECL|macro|TP_UNIT
mdefine_line|#define TP_UNIT(dev)&t;((minor(dev) &gt;&gt; 4) &amp; 0x07)&t;       /* unit number */
multiline_comment|/* print excessive diagnostics */
DECL|macro|TP_DIAGS
mdefine_line|#define TP_DIAGS(dev)&t;(QIC02_TAPE_DEBUG &amp; TPQD_DIAGS)
multiline_comment|/* status codes returned by a WTS_RDSTAT call */
DECL|struct|tpstatus
r_struct
id|tpstatus
(brace
multiline_comment|/* sizeof(short)==2), LSB first */
DECL|member|exs
r_int
r_int
id|exs
suffix:semicolon
multiline_comment|/* Drive exception flags */
DECL|member|dec
r_int
r_int
id|dec
suffix:semicolon
multiline_comment|/* data error count: nr of blocks rewritten/soft read errors */
DECL|member|urc
r_int
r_int
id|urc
suffix:semicolon
multiline_comment|/* underrun count: nr of times streaming was interrupted */
)brace
suffix:semicolon
DECL|macro|TPSTATSIZE
mdefine_line|#define TPSTATSIZE&t;sizeof(struct tpstatus)
multiline_comment|/* defines for tpstatus.exs -- taken from 386BSD wt driver */
DECL|macro|TP_POR
mdefine_line|#define&t;TP_POR&t;&t;0x100&t;/* Power on or reset occurred */
DECL|macro|TP_EOR
mdefine_line|#define&t;TP_EOR&t;&t;0x200&t;/* REServed for end of RECORDED media */
DECL|macro|TP_PAR
mdefine_line|#define&t;TP_PAR&t;&t;0x400&t;/* REServed for bus parity */
DECL|macro|TP_BOM
mdefine_line|#define&t;TP_BOM&t;&t;0x800&t;/* Beginning of media */
DECL|macro|TP_MBD
mdefine_line|#define&t;TP_MBD&t;&t;0x1000&t;/* Marginal block detected */
DECL|macro|TP_NDT
mdefine_line|#define&t;TP_NDT&t;&t;0x2000&t;/* No data detected */
DECL|macro|TP_ILL
mdefine_line|#define&t;TP_ILL&t;&t;0x4000&t;/* Illegal command */
DECL|macro|TP_ST1
mdefine_line|#define&t;TP_ST1&t;&t;0x8000&t;/* Status byte 1 flag */
DECL|macro|TP_FIL
mdefine_line|#define&t;TP_FIL&t;&t;0x01&t;/* File mark detected */
DECL|macro|TP_BNL
mdefine_line|#define&t;TP_BNL&t;&t;0x02&t;/* Bad block not located */
DECL|macro|TP_UDA
mdefine_line|#define&t;TP_UDA&t;&t;0x04&t;/* Unrecoverable data error */
DECL|macro|TP_EOM
mdefine_line|#define&t;TP_EOM&t;&t;0x08&t;/* End of media */
DECL|macro|TP_WRP
mdefine_line|#define&t;TP_WRP&t;&t;0x10&t;/* Write protected cartridge */
DECL|macro|TP_USL
mdefine_line|#define&t;TP_USL&t;&t;0x20&t;/* Unselected drive */
DECL|macro|TP_CNI
mdefine_line|#define&t;TP_CNI&t;&t;0x40&t;/* Cartridge not in place */
DECL|macro|TP_ST0
mdefine_line|#define&t;TP_ST0&t;&t;0x80&t;/* Status byte 0 flag */
DECL|macro|REPORT_ERR0
mdefine_line|#define REPORT_ERR0&t;(TP_CNI|TP_USL|TP_WRP|TP_EOM|TP_UDA|TP_BNL|TP_FIL)
DECL|macro|REPORT_ERR1
mdefine_line|#define REPORT_ERR1&t;(TP_ILL|TP_NDT|TP_MBD|TP_PAR)
multiline_comment|/* exception numbers */
DECL|macro|EXC_UNKNOWN
mdefine_line|#define EXC_UNKNOWN&t;0&t;/* (extra) Unknown exception code */
DECL|macro|EXC_NDRV
mdefine_line|#define EXC_NDRV&t;1&t;/* No drive */
DECL|macro|EXC_NCART
mdefine_line|#define EXC_NCART&t;2&t;/* No cartridge */
DECL|macro|EXC_WP
mdefine_line|#define EXC_WP&t;&t;3&t;/* Write protected */
DECL|macro|EXC_EOM
mdefine_line|#define EXC_EOM&t;&t;4&t;/* EOM */
DECL|macro|EXC_RWA
mdefine_line|#define EXC_RWA&t;&t;5&t;/* read/write abort */
DECL|macro|EXC_XBAD
mdefine_line|#define EXC_XBAD&t;6&t;/* read error, bad block transferred */
DECL|macro|EXC_XFILLER
mdefine_line|#define EXC_XFILLER&t;7&t;/* read error, filler block transferred */
DECL|macro|EXC_NDT
mdefine_line|#define EXC_NDT&t;&t;8&t;/* read error, no data */
DECL|macro|EXC_NDTEOM
mdefine_line|#define EXC_NDTEOM&t;9&t;/* read error, no data &amp; EOM */
DECL|macro|EXC_NDTBOM
mdefine_line|#define EXC_NDTBOM&t;10&t;/* read error, no data &amp; BOM */
DECL|macro|EXC_FM
mdefine_line|#define EXC_FM&t;&t;11&t;/* Read a filemark */
DECL|macro|EXC_ILL
mdefine_line|#define EXC_ILL&t;&t;12&t;/* Illegal command */
DECL|macro|EXC_POR
mdefine_line|#define EXC_POR&t;&t;13&t;/* Power on/reset */
DECL|macro|EXC_MARGINAL
mdefine_line|#define EXC_MARGINAL&t;14&t;/* Marginal block detected */
DECL|macro|EXC_EOR
mdefine_line|#define EXC_EOR&t;&t;15&t;/* (extra, for SEEKEOD) End Of Recorded data reached */
DECL|macro|EXC_BOM
mdefine_line|#define EXC_BOM&t;&t;16&t;/* (extra) BOM reached */
DECL|macro|TAPE_NOTIFY_TIMEOUT
mdefine_line|#define TAPE_NOTIFY_TIMEOUT&t;1000000
multiline_comment|/* internal function return codes */
DECL|macro|TE_OK
mdefine_line|#define TE_OK&t;0&t;&t;/* everything is fine */
DECL|macro|TE_EX
mdefine_line|#define TE_EX&t;1&t;&t;/* exception detected */
DECL|macro|TE_ERR
mdefine_line|#define TE_ERR&t;2&t;&t;/* some error */
DECL|macro|TE_NS
mdefine_line|#define TE_NS&t;3&t;&t;/* can&squot;t read status */
DECL|macro|TE_TIM
mdefine_line|#define TE_TIM&t;4&t;&t;/* timed out */
DECL|macro|TE_DEAD
mdefine_line|#define TE_DEAD&t;5&t;&t;/* tape drive doesn&squot;t respond */
DECL|macro|TE_END
mdefine_line|#define TE_END&t;6&t;&t;/******** Archive hack *****/
multiline_comment|/* timeout timer values -- check these! */
DECL|macro|TIM_S
mdefine_line|#define TIM_S&t;(4*HZ)&t;&t;/* 4 seconds (normal cmds) */
DECL|macro|TIM_M
mdefine_line|#define TIM_M&t;(30*HZ)&t;&t;/* 30 seconds (write FM) */
DECL|macro|TIM_R
mdefine_line|#define TIM_R&t;(8*60*HZ)&t;/* 8 minutes (retensioning) */
DECL|macro|TIM_F
mdefine_line|#define TIM_F&t;(2*3600*HZ)&t;/* est. 1.2hr for full tape read/write+2 retens */
DECL|macro|TIMERON
mdefine_line|#define TIMERON(t)&t;mod_timer(&amp;tp_timer, jiffies + (t))
DECL|macro|TIMEROFF
mdefine_line|#define TIMEROFF&t;del_timer_sync(&amp;tp_timer);
DECL|macro|TIMERCONT
mdefine_line|#define TIMERCONT&t;add_timer(&amp;tp_timer);
DECL|typedef|flag
r_typedef
r_char
id|flag
suffix:semicolon
DECL|macro|NO
mdefine_line|#define NO&t;0&t;/* NO must be 0 */
DECL|macro|YES
mdefine_line|#define YES&t;1&t;/* YES must be != 0 */
macro_line|#ifdef TDEBUG
DECL|macro|TPQDEB
macro_line|# define TPQDEB(s)&t;s
DECL|macro|TPQPUTS
macro_line|# define TPQPUTS(s)&t;tpqputs(s)
macro_line|#else
DECL|macro|TPQDEB
macro_line|# define TPQDEB(s)
DECL|macro|TPQPUTS
macro_line|# define TPQPUTS(s)
macro_line|#endif
multiline_comment|/* NR_BLK_BUF is a `tuneable parameter&squot;. If you&squot;re really low on&n; * kernel space, you could decrease it to 1, or if you got a very&n; * slow machine, you could increase it up to 127 blocks. Less kernel&n; * buffer blocks result in more context-switching.&n; */
DECL|macro|NR_BLK_BUF
mdefine_line|#define NR_BLK_BUF&t;20&t;&t;&t;&t;    /* max 127 blocks */
DECL|macro|TAPE_BLKSIZE
mdefine_line|#define TAPE_BLKSIZE&t;512&t;&t;  /* streamer tape block size (fixed) */
DECL|macro|TPQBUF_SIZE
mdefine_line|#define TPQBUF_SIZE&t;(TAPE_BLKSIZE*NR_BLK_BUF)&t;       /* buffer size */
DECL|macro|BLOCKS_BEYOND_EW
mdefine_line|#define BLOCKS_BEYOND_EW&t;2&t;/* nr of blocks after Early Warning hole */
DECL|macro|BOGUS_IRQ
mdefine_line|#define BOGUS_IRQ&t;&t;32009
multiline_comment|/* This is internal data, filled in based on the ifc_type field given&n; * by the user. Everex is mapped to Wangtek with a different&n; * `dma_enable_value&squot;, if dmanr==3.&n; */
DECL|struct|qic02_ccb
r_struct
id|qic02_ccb
(brace
DECL|member|ifc_type
r_int
id|ifc_type
suffix:semicolon
DECL|member|port_stat
r_int
r_int
id|port_stat
suffix:semicolon
multiline_comment|/* Status port address */
DECL|member|port_ctl
r_int
r_int
id|port_ctl
suffix:semicolon
multiline_comment|/* Control port address */
DECL|member|port_cmd
r_int
r_int
id|port_cmd
suffix:semicolon
multiline_comment|/* Command port address */
DECL|member|port_data
r_int
r_int
id|port_data
suffix:semicolon
multiline_comment|/* Data port address */
multiline_comment|/* status register bits */
DECL|member|stat_polarity
r_int
r_int
id|stat_polarity
suffix:semicolon
multiline_comment|/* invert status bits or not */
DECL|member|stat_ready
r_int
r_int
id|stat_ready
suffix:semicolon
multiline_comment|/* drive ready */
DECL|member|stat_exception
r_int
r_int
id|stat_exception
suffix:semicolon
multiline_comment|/* drive signals exception */
DECL|member|stat_mask
r_int
r_int
id|stat_mask
suffix:semicolon
DECL|member|stat_resetmask
r_int
r_int
id|stat_resetmask
suffix:semicolon
DECL|member|stat_resetval
r_int
r_int
id|stat_resetval
suffix:semicolon
multiline_comment|/* control register bits */
DECL|member|ctl_reset
r_int
r_int
id|ctl_reset
suffix:semicolon
multiline_comment|/* reset drive */
DECL|member|ctl_request
r_int
r_int
id|ctl_request
suffix:semicolon
multiline_comment|/* latch command */
multiline_comment|/* This is used to change the DMA3 behaviour */
DECL|member|dma_enable_value
r_int
r_int
id|dma_enable_value
suffix:semicolon
)brace
suffix:semicolon
macro_line|#if MODULE
r_static
r_int
id|qic02_tape_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
r_extern
r_int
id|qic02_tape_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* for mem.c */
macro_line|#endif
macro_line|#endif /* CONFIG_QIC02_TAPE */
macro_line|#endif /* _LINUX_TPQIC02_H */
eof
