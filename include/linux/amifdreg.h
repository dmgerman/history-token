macro_line|#ifndef _LINUX_AMIFDREG_H
DECL|macro|_LINUX_AMIFDREG_H
mdefine_line|#define _LINUX_AMIFDREG_H
multiline_comment|/*&n;** CIAAPRA bits (read only)&n;*/
DECL|macro|DSKRDY
mdefine_line|#define DSKRDY      (0x1&lt;&lt;5)        /* disk ready when low */
DECL|macro|DSKTRACK0
mdefine_line|#define DSKTRACK0   (0x1&lt;&lt;4)        /* head at track zero when low */
DECL|macro|DSKPROT
mdefine_line|#define DSKPROT     (0x1&lt;&lt;3)        /* disk protected when low */
DECL|macro|DSKCHANGE
mdefine_line|#define DSKCHANGE   (0x1&lt;&lt;2)        /* low when disk removed */
multiline_comment|/*&n;** CIAAPRB bits (read/write)&n;*/
DECL|macro|DSKMOTOR
mdefine_line|#define DSKMOTOR    (0x1&lt;&lt;7)        /* motor on when low */
DECL|macro|DSKSEL3
mdefine_line|#define DSKSEL3     (0x1&lt;&lt;6)        /* select drive 3 when low */
DECL|macro|DSKSEL2
mdefine_line|#define DSKSEL2     (0x1&lt;&lt;5)        /* select drive 2 when low */
DECL|macro|DSKSEL1
mdefine_line|#define DSKSEL1     (0x1&lt;&lt;4)        /* select drive 1 when low */
DECL|macro|DSKSEL0
mdefine_line|#define DSKSEL0     (0x1&lt;&lt;3)        /* select drive 0 when low */
DECL|macro|DSKSIDE
mdefine_line|#define DSKSIDE     (0x1&lt;&lt;2)        /* side selection: 0 = upper, 1 = lower */
DECL|macro|DSKDIREC
mdefine_line|#define DSKDIREC    (0x1&lt;&lt;1)        /* step direction: 0=in, 1=out (to trk 0) */
DECL|macro|DSKSTEP
mdefine_line|#define DSKSTEP     (0x1)           /* pulse low to step head 1 track */
multiline_comment|/*&n;** DSKBYTR bits (read only)&n;*/
DECL|macro|DSKBYT
mdefine_line|#define DSKBYT      (1&lt;&lt;15)         /* register contains valid byte when set */
DECL|macro|DMAON
mdefine_line|#define DMAON       (1&lt;&lt;14)         /* disk DMA enabled */
DECL|macro|DISKWRITE
mdefine_line|#define DISKWRITE   (1&lt;&lt;13)         /* disk write bit in DSKLEN enabled */
DECL|macro|WORDEQUAL
mdefine_line|#define WORDEQUAL   (1&lt;&lt;12)         /* DSKSYNC register match when true */
multiline_comment|/* bits 7-0 are data */
multiline_comment|/*&n;** ADKCON/ADKCONR bits&n;*/
macro_line|#ifndef SETCLR
DECL|macro|ADK_SETCLR
mdefine_line|#define ADK_SETCLR      (1&lt;&lt;15)     /* control bit */
macro_line|#endif
DECL|macro|ADK_PRECOMP1
mdefine_line|#define ADK_PRECOMP1    (1&lt;&lt;14)     /* precompensation selection */
DECL|macro|ADK_PRECOMP0
mdefine_line|#define ADK_PRECOMP0    (1&lt;&lt;13)     /* 00=none, 01=140ns, 10=280ns, 11=500ns */
DECL|macro|ADK_MFMPREC
mdefine_line|#define ADK_MFMPREC     (1&lt;&lt;12)     /* 0=GCR precomp., 1=MFM precomp. */
DECL|macro|ADK_WORDSYNC
mdefine_line|#define ADK_WORDSYNC    (1&lt;&lt;10)     /* enable DSKSYNC auto DMA */
DECL|macro|ADK_MSBSYNC
mdefine_line|#define ADK_MSBSYNC     (1&lt;&lt;9)      /* when 1, enable sync on MSbit (for GCR) */
DECL|macro|ADK_FAST
mdefine_line|#define ADK_FAST        (1&lt;&lt;8)      /* bit cell: 0=2us (GCR), 1=1us (MFM) */
multiline_comment|/*&n;** DSKLEN bits&n;*/
DECL|macro|DSKLEN_DMAEN
mdefine_line|#define DSKLEN_DMAEN    (1&lt;&lt;15)
DECL|macro|DSKLEN_WRITE
mdefine_line|#define DSKLEN_WRITE    (1&lt;&lt;14)
multiline_comment|/*&n;** INTENA/INTREQ bits&n;*/
DECL|macro|DSKINDEX
mdefine_line|#define DSKINDEX    (0x1&lt;&lt;4)        /* DSKINDEX bit */
multiline_comment|/*&n;** Misc&n;*/
DECL|macro|MFM_SYNC
mdefine_line|#define MFM_SYNC    0x4489          /* standard MFM sync value */
multiline_comment|/* Values for FD_COMMAND */
DECL|macro|FD_RECALIBRATE
mdefine_line|#define FD_RECALIBRATE&t;&t;0x07&t;/* move to track 0 */
DECL|macro|FD_SEEK
mdefine_line|#define FD_SEEK&t;&t;&t;0x0F&t;/* seek track */
DECL|macro|FD_READ
mdefine_line|#define FD_READ&t;&t;&t;0xE6&t;/* read with MT, MFM, SKip deleted */
DECL|macro|FD_WRITE
mdefine_line|#define FD_WRITE&t;&t;0xC5&t;/* write with MT, MFM */
DECL|macro|FD_SENSEI
mdefine_line|#define FD_SENSEI&t;&t;0x08&t;/* Sense Interrupt Status */
DECL|macro|FD_SPECIFY
mdefine_line|#define FD_SPECIFY&t;&t;0x03&t;/* specify HUT etc */
DECL|macro|FD_FORMAT
mdefine_line|#define FD_FORMAT&t;&t;0x4D&t;/* format one track */
DECL|macro|FD_VERSION
mdefine_line|#define FD_VERSION&t;&t;0x10&t;/* get version code */
DECL|macro|FD_CONFIGURE
mdefine_line|#define FD_CONFIGURE&t;&t;0x13&t;/* configure FIFO operation */
DECL|macro|FD_PERPENDICULAR
mdefine_line|#define FD_PERPENDICULAR&t;0x12&t;/* perpendicular r/w mode */
macro_line|#endif /* _LINUX_AMIFDREG_H */
eof
