macro_line|#ifndef _AHA152X_H
DECL|macro|_AHA152X_H
mdefine_line|#define _AHA152X_H
multiline_comment|/*&n; * $Id: aha152x.h,v 2.4 2000/12/16 12:48:48 fischer Exp $&n; */
macro_line|#if defined(__KERNEL__)
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/version.h&gt;
r_int
id|aha152x_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|aha152x_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|aha152x_queue
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_int
id|aha152x_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|aha152x_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shpnt
)paren
suffix:semicolon
r_int
id|aha152x_device_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|aha152x_bus_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|aha152x_host_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|aha152x_biosparam
c_func
(paren
id|Disk
op_star
comma
id|kdev_t
comma
r_int
op_star
)paren
suffix:semicolon
r_int
id|aha152x_proc_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|hostno
comma
r_int
id|inout
)paren
suffix:semicolon
multiline_comment|/* number of queueable commands&n;   (unless we support more than 1 cmd_per_lun this should do) */
DECL|macro|AHA152X_MAXQUEUE
mdefine_line|#define AHA152X_MAXQUEUE 7
DECL|macro|AHA152X_REVID
mdefine_line|#define AHA152X_REVID &quot;Adaptec 152x SCSI driver; $Revision: 2.4 $&quot;
multiline_comment|/* Initial value of Scsi_Host entry */
DECL|macro|AHA152X
mdefine_line|#define AHA152X { proc_name:&t;&t;&t;&quot;aha152x&quot;,&t;&t;&bslash;&n;                  proc_info:&t;&t;&t;aha152x_proc_info,&t;&bslash;&n;                  name:&t;&t;&t;&t;AHA152X_REVID,&t;&t;&bslash;&n;                  detect:&t;&t;&t;aha152x_detect,&t;&t;&bslash;&n;                  command:&t;&t;&t;aha152x_command,&t;&bslash;&n;                  queuecommand:&t;&t;&t;aha152x_queue,&t;&t;&bslash;&n;&t;&t;  eh_abort_handler:&t;&t;aha152x_abort,&t;&t;&bslash;&n;&t;&t;  eh_device_reset_handler:&t;aha152x_device_reset,&t;&bslash;&n;&t;&t;  eh_bus_reset_handler:&t;&t;aha152x_bus_reset,&t;&bslash;&n;&t;&t;  eh_host_reset_handler:&t;aha152x_host_reset,&t;&bslash;&n;                  release:&t;&t;&t;aha152x_release,&t;&bslash;&n;                  slave_attach:&t;&t;&t;0,&t;&t;&t;&bslash;&n;                  bios_param:&t;&t;&t;aha152x_biosparam,&t;&bslash;&n;                  can_queue:&t;&t;&t;1,&t;&t;&t;&bslash;&n;                  this_id:&t;&t;&t;7,&t;&t;&t;&bslash;&n;                  sg_tablesize:&t;&t;&t;SG_ALL,&t;&t;&t;&bslash;&n;                  cmd_per_lun:&t;&t;&t;1,&t;&t;&t;&bslash;&n;                  present:&t;&t;&t;0,&t;&t;&t;&bslash;&n;                  unchecked_isa_dma:&t;&t;0,&t;&t;&t;&bslash;&n;                  use_clustering:&t;&t;DISABLE_CLUSTERING,&t;&bslash;&n;&t;&t;  use_new_eh_code:&t;&t;1 }
macro_line|#endif
multiline_comment|/* port addresses */
DECL|macro|SCSISEQ
mdefine_line|#define SCSISEQ      (HOSTIOPORT0+0x00)    /* SCSI sequence control */
DECL|macro|SXFRCTL0
mdefine_line|#define SXFRCTL0     (HOSTIOPORT0+0x01)    /* SCSI transfer control 0 */
DECL|macro|SXFRCTL1
mdefine_line|#define SXFRCTL1     (HOSTIOPORT0+0x02)    /* SCSI transfer control 1 */
DECL|macro|SCSISIG
mdefine_line|#define SCSISIG      (HOSTIOPORT0+0x03)    /* SCSI signal in/out */
DECL|macro|SCSIRATE
mdefine_line|#define SCSIRATE     (HOSTIOPORT0+0x04)    /* SCSI rate control */
DECL|macro|SELID
mdefine_line|#define SELID        (HOSTIOPORT0+0x05)    /* selection/reselection ID */
DECL|macro|SCSIID
mdefine_line|#define SCSIID       SELID                 /* SCSI ID */
DECL|macro|SCSIDAT
mdefine_line|#define SCSIDAT      (HOSTIOPORT0+0x06)    /* SCSI latched data */
DECL|macro|SCSIBUS
mdefine_line|#define SCSIBUS      (HOSTIOPORT0+0x07)    /* SCSI data bus */
DECL|macro|STCNT0
mdefine_line|#define STCNT0       (HOSTIOPORT0+0x08)    /* SCSI transfer count 0 */
DECL|macro|STCNT1
mdefine_line|#define STCNT1       (HOSTIOPORT0+0x09)    /* SCSI transfer count 1 */
DECL|macro|STCNT2
mdefine_line|#define STCNT2       (HOSTIOPORT0+0x0a)    /* SCSI transfer count 2 */
DECL|macro|SSTAT0
mdefine_line|#define SSTAT0       (HOSTIOPORT0+0x0b)    /* SCSI interrupt status 0 */
DECL|macro|SSTAT1
mdefine_line|#define SSTAT1       (HOSTIOPORT0+0x0c)    /* SCSI interrupt status 1 */
DECL|macro|SSTAT2
mdefine_line|#define SSTAT2       (HOSTIOPORT0+0x0d)    /* SCSI interrupt status 2 */
DECL|macro|SCSITEST
mdefine_line|#define SCSITEST     (HOSTIOPORT0+0x0e)    /* SCSI test control */
DECL|macro|SSTAT3
mdefine_line|#define SSTAT3       SCSITEST              /* SCSI interrupt status 3 */
DECL|macro|SSTAT4
mdefine_line|#define SSTAT4       (HOSTIOPORT0+0x0f)    /* SCSI status 4 */
DECL|macro|SIMODE0
mdefine_line|#define SIMODE0      (HOSTIOPORT1+0x10)    /* SCSI interrupt mode 0 */
DECL|macro|SIMODE1
mdefine_line|#define SIMODE1      (HOSTIOPORT1+0x11)    /* SCSI interrupt mode 1 */
DECL|macro|DMACNTRL0
mdefine_line|#define DMACNTRL0    (HOSTIOPORT1+0x12)    /* DMA control 0 */
DECL|macro|DMACNTRL1
mdefine_line|#define DMACNTRL1    (HOSTIOPORT1+0x13)    /* DMA control 1 */
DECL|macro|DMASTAT
mdefine_line|#define DMASTAT      (HOSTIOPORT1+0x14)    /* DMA status */
DECL|macro|FIFOSTAT
mdefine_line|#define FIFOSTAT     (HOSTIOPORT1+0x15)    /* FIFO status */
DECL|macro|DATAPORT
mdefine_line|#define DATAPORT     (HOSTIOPORT1+0x16)    /* DATA port */
DECL|macro|BRSTCNTRL
mdefine_line|#define BRSTCNTRL    (HOSTIOPORT1+0x18)    /* burst control */
DECL|macro|PORTA
mdefine_line|#define PORTA        (HOSTIOPORT1+0x1a)    /* PORT A */
DECL|macro|PORTB
mdefine_line|#define PORTB        (HOSTIOPORT1+0x1b)    /* PORT B */
DECL|macro|REV
mdefine_line|#define REV          (HOSTIOPORT1+0x1c)    /* revision */
DECL|macro|STACK
mdefine_line|#define STACK        (HOSTIOPORT1+0x1d)    /* stack */
DECL|macro|TEST
mdefine_line|#define TEST         (HOSTIOPORT1+0x1e)    /* test register */
DECL|macro|IO_RANGE
mdefine_line|#define IO_RANGE        0x20
multiline_comment|/* used in aha152x_porttest */
DECL|macro|O_PORTA
mdefine_line|#define O_PORTA         0x1a               /* PORT A */
DECL|macro|O_PORTB
mdefine_line|#define O_PORTB         0x1b               /* PORT B */
DECL|macro|O_DMACNTRL1
mdefine_line|#define O_DMACNTRL1     0x13               /* DMA control 1 */
DECL|macro|O_STACK
mdefine_line|#define O_STACK         0x1d               /* stack */
multiline_comment|/* used in tc1550_porttest */
DECL|macro|O_TC_PORTA
mdefine_line|#define O_TC_PORTA      0x0a               /* PORT A */
DECL|macro|O_TC_PORTB
mdefine_line|#define O_TC_PORTB      0x0b               /* PORT B */
DECL|macro|O_TC_DMACNTRL1
mdefine_line|#define O_TC_DMACNTRL1  0x03               /* DMA control 1 */
DECL|macro|O_TC_STACK
mdefine_line|#define O_TC_STACK      0x0d               /* stack */
multiline_comment|/* bits and bitmasks to ports */
multiline_comment|/* SCSI sequence control */
DECL|macro|TEMODEO
mdefine_line|#define TEMODEO      0x80
DECL|macro|ENSELO
mdefine_line|#define ENSELO       0x40
DECL|macro|ENSELI
mdefine_line|#define ENSELI       0x20
DECL|macro|ENRESELI
mdefine_line|#define ENRESELI     0x10
DECL|macro|ENAUTOATNO
mdefine_line|#define ENAUTOATNO   0x08
DECL|macro|ENAUTOATNI
mdefine_line|#define ENAUTOATNI   0x04
DECL|macro|ENAUTOATNP
mdefine_line|#define ENAUTOATNP   0x02
DECL|macro|SCSIRSTO
mdefine_line|#define SCSIRSTO     0x01
multiline_comment|/* SCSI transfer control 0 */
DECL|macro|SCSIEN
mdefine_line|#define SCSIEN       0x80
DECL|macro|DMAEN
mdefine_line|#define DMAEN        0x40
DECL|macro|CH1
mdefine_line|#define CH1          0x20
DECL|macro|CLRSTCNT
mdefine_line|#define CLRSTCNT     0x10
DECL|macro|SPIOEN
mdefine_line|#define SPIOEN       0x08
DECL|macro|CLRCH1
mdefine_line|#define CLRCH1       0x02
multiline_comment|/* SCSI transfer control 1 */
DECL|macro|BITBUCKET
mdefine_line|#define BITBUCKET    0x80
DECL|macro|SWRAPEN
mdefine_line|#define SWRAPEN      0x40
DECL|macro|ENSPCHK
mdefine_line|#define ENSPCHK      0x20
DECL|macro|STIMESEL
mdefine_line|#define STIMESEL     0x18    /* mask */
DECL|macro|STIMESEL_
mdefine_line|#define STIMESEL_    3
DECL|macro|ENSTIMER
mdefine_line|#define ENSTIMER     0x04
DECL|macro|BYTEALIGN
mdefine_line|#define BYTEALIGN    0x02
multiline_comment|/* SCSI signal IN */
DECL|macro|SIG_CDI
mdefine_line|#define SIG_CDI          0x80
DECL|macro|SIG_IOI
mdefine_line|#define SIG_IOI          0x40
DECL|macro|SIG_MSGI
mdefine_line|#define SIG_MSGI         0x20
DECL|macro|SIG_ATNI
mdefine_line|#define SIG_ATNI         0x10
DECL|macro|SIG_SELI
mdefine_line|#define SIG_SELI         0x08
DECL|macro|SIG_BSYI
mdefine_line|#define SIG_BSYI         0x04
DECL|macro|SIG_REQI
mdefine_line|#define SIG_REQI         0x02
DECL|macro|SIG_ACKI
mdefine_line|#define SIG_ACKI         0x01
multiline_comment|/* SCSI Phases */
DECL|macro|P_MASK
mdefine_line|#define P_MASK       (SIG_MSGI|SIG_CDI|SIG_IOI)
DECL|macro|P_DATAO
mdefine_line|#define P_DATAO      (0)
DECL|macro|P_DATAI
mdefine_line|#define P_DATAI      (SIG_IOI)
DECL|macro|P_CMD
mdefine_line|#define P_CMD        (SIG_CDI)
DECL|macro|P_STATUS
mdefine_line|#define P_STATUS     (SIG_CDI|SIG_IOI)
DECL|macro|P_MSGO
mdefine_line|#define P_MSGO       (SIG_MSGI|SIG_CDI)
DECL|macro|P_MSGI
mdefine_line|#define P_MSGI       (SIG_MSGI|SIG_CDI|SIG_IOI)
multiline_comment|/* SCSI signal OUT */
DECL|macro|SIG_CDO
mdefine_line|#define SIG_CDO          0x80
DECL|macro|SIG_IOO
mdefine_line|#define SIG_IOO          0x40
DECL|macro|SIG_MSGO
mdefine_line|#define SIG_MSGO         0x20
DECL|macro|SIG_ATNO
mdefine_line|#define SIG_ATNO         0x10
DECL|macro|SIG_SELO
mdefine_line|#define SIG_SELO         0x08
DECL|macro|SIG_BSYO
mdefine_line|#define SIG_BSYO         0x04
DECL|macro|SIG_REQO
mdefine_line|#define SIG_REQO         0x02
DECL|macro|SIG_ACKO
mdefine_line|#define SIG_ACKO         0x01
multiline_comment|/* SCSI rate control */
DECL|macro|SXFR
mdefine_line|#define SXFR         0x70    /* mask */
DECL|macro|SXFR_
mdefine_line|#define SXFR_        4
DECL|macro|SOFS
mdefine_line|#define SOFS         0x0f    /* mask */
multiline_comment|/* SCSI ID */
DECL|macro|OID
mdefine_line|#define OID          0x70
DECL|macro|OID_
mdefine_line|#define OID_         4
DECL|macro|TID
mdefine_line|#define TID          0x07
multiline_comment|/* SCSI transfer count */
DECL|macro|GETSTCNT
mdefine_line|#define GETSTCNT() ( (GETPORT(STCNT2)&lt;&lt;16) &bslash;&n;                   + (GETPORT(STCNT1)&lt;&lt; 8) &bslash;&n;                   + GETPORT(STCNT0) )
DECL|macro|SETSTCNT
mdefine_line|#define SETSTCNT(X) { SETPORT(STCNT2, ((X) &amp; 0xFF0000) &gt;&gt; 16); &bslash;&n;                      SETPORT(STCNT1, ((X) &amp; 0x00FF00) &gt;&gt;  8); &bslash;&n;                      SETPORT(STCNT0, ((X) &amp; 0x0000FF) ); }
multiline_comment|/* SCSI interrupt status */
DECL|macro|TARGET
mdefine_line|#define TARGET       0x80
DECL|macro|SELDO
mdefine_line|#define SELDO        0x40
DECL|macro|SELDI
mdefine_line|#define SELDI        0x20
DECL|macro|SELINGO
mdefine_line|#define SELINGO      0x10
DECL|macro|SWRAP
mdefine_line|#define SWRAP        0x08
DECL|macro|SDONE
mdefine_line|#define SDONE        0x04
DECL|macro|SPIORDY
mdefine_line|#define SPIORDY      0x02
DECL|macro|DMADONE
mdefine_line|#define DMADONE      0x01
DECL|macro|SETSDONE
mdefine_line|#define SETSDONE     0x80
DECL|macro|CLRSELDO
mdefine_line|#define CLRSELDO     0x40
DECL|macro|CLRSELDI
mdefine_line|#define CLRSELDI     0x20
DECL|macro|CLRSELINGO
mdefine_line|#define CLRSELINGO   0x10
DECL|macro|CLRSWRAP
mdefine_line|#define CLRSWRAP     0x08
DECL|macro|CLRSDONE
mdefine_line|#define CLRSDONE     0x04
DECL|macro|CLRSPIORDY
mdefine_line|#define CLRSPIORDY   0x02
DECL|macro|CLRDMADONE
mdefine_line|#define CLRDMADONE   0x01
multiline_comment|/* SCSI status 1 */
DECL|macro|SELTO
mdefine_line|#define SELTO        0x80
DECL|macro|ATNTARG
mdefine_line|#define ATNTARG      0x40
DECL|macro|SCSIRSTI
mdefine_line|#define SCSIRSTI     0x20
DECL|macro|PHASEMIS
mdefine_line|#define PHASEMIS     0x10
DECL|macro|BUSFREE
mdefine_line|#define BUSFREE      0x08
DECL|macro|SCSIPERR
mdefine_line|#define SCSIPERR     0x04
DECL|macro|PHASECHG
mdefine_line|#define PHASECHG     0x02
DECL|macro|REQINIT
mdefine_line|#define REQINIT      0x01
DECL|macro|CLRSELTIMO
mdefine_line|#define CLRSELTIMO   0x80
DECL|macro|CLRATNO
mdefine_line|#define CLRATNO      0x40
DECL|macro|CLRSCSIRSTI
mdefine_line|#define CLRSCSIRSTI  0x20
DECL|macro|CLRBUSFREE
mdefine_line|#define CLRBUSFREE   0x08
DECL|macro|CLRSCSIPERR
mdefine_line|#define CLRSCSIPERR  0x04
DECL|macro|CLRPHASECHG
mdefine_line|#define CLRPHASECHG  0x02
DECL|macro|CLRREQINIT
mdefine_line|#define CLRREQINIT   0x01
multiline_comment|/* SCSI status 2 */
DECL|macro|SOFFSET
mdefine_line|#define SOFFSET      0x20
DECL|macro|SEMPTY
mdefine_line|#define SEMPTY       0x10
DECL|macro|SFULL
mdefine_line|#define SFULL        0x08
DECL|macro|SFCNT
mdefine_line|#define SFCNT        0x07    /* mask */
multiline_comment|/* SCSI status 3 */
DECL|macro|SCSICNT
mdefine_line|#define SCSICNT      0xf0    /* mask */
DECL|macro|SCSICNT_
mdefine_line|#define SCSICNT_     4
DECL|macro|OFFCNT
mdefine_line|#define OFFCNT       0x0f    /* mask */
multiline_comment|/* SCSI TEST control */
DECL|macro|SCTESTU
mdefine_line|#define SCTESTU      0x08
DECL|macro|SCTESTD
mdefine_line|#define SCTESTD      0x04
DECL|macro|STCTEST
mdefine_line|#define STCTEST      0x01
multiline_comment|/* SCSI status 4 */
DECL|macro|SYNCERR
mdefine_line|#define SYNCERR      0x04
DECL|macro|FWERR
mdefine_line|#define FWERR        0x02
DECL|macro|FRERR
mdefine_line|#define FRERR        0x01
DECL|macro|CLRSYNCERR
mdefine_line|#define CLRSYNCERR   0x04
DECL|macro|CLRFWERR
mdefine_line|#define CLRFWERR     0x02
DECL|macro|CLRFRERR
mdefine_line|#define CLRFRERR     0x01
multiline_comment|/* SCSI interrupt mode 0 */
DECL|macro|ENSELDO
mdefine_line|#define ENSELDO      0x40
DECL|macro|ENSELDI
mdefine_line|#define ENSELDI      0x20
DECL|macro|ENSELINGO
mdefine_line|#define ENSELINGO    0x10
DECL|macro|ENSWRAP
mdefine_line|#define ENSWRAP      0x08
DECL|macro|ENSDONE
mdefine_line|#define ENSDONE      0x04
DECL|macro|ENSPIORDY
mdefine_line|#define ENSPIORDY    0x02
DECL|macro|ENDMADONE
mdefine_line|#define ENDMADONE    0x01
multiline_comment|/* SCSI interrupt mode 1 */
DECL|macro|ENSELTIMO
mdefine_line|#define ENSELTIMO    0x80
DECL|macro|ENATNTARG
mdefine_line|#define ENATNTARG    0x40
DECL|macro|ENSCSIRST
mdefine_line|#define ENSCSIRST    0x20
DECL|macro|ENPHASEMIS
mdefine_line|#define ENPHASEMIS   0x10
DECL|macro|ENBUSFREE
mdefine_line|#define ENBUSFREE    0x08
DECL|macro|ENSCSIPERR
mdefine_line|#define ENSCSIPERR   0x04
DECL|macro|ENPHASECHG
mdefine_line|#define ENPHASECHG   0x02
DECL|macro|ENREQINIT
mdefine_line|#define ENREQINIT    0x01
multiline_comment|/* DMA control 0 */
DECL|macro|ENDMA
mdefine_line|#define ENDMA        0x80
DECL|macro|_8BIT
mdefine_line|#define _8BIT        0x40
DECL|macro|DMA
mdefine_line|#define DMA          0x20
DECL|macro|WRITE_READ
mdefine_line|#define WRITE_READ   0x08
DECL|macro|INTEN
mdefine_line|#define INTEN        0x04
DECL|macro|RSTFIFO
mdefine_line|#define RSTFIFO      0x02
DECL|macro|SWINT
mdefine_line|#define SWINT        0x01
multiline_comment|/* DMA control 1 */
DECL|macro|PWRDWN
mdefine_line|#define PWRDWN       0x80
DECL|macro|STK
mdefine_line|#define STK          0x07    /* mask */
multiline_comment|/* DMA status */
DECL|macro|ATDONE
mdefine_line|#define ATDONE       0x80
DECL|macro|WORDRDY
mdefine_line|#define WORDRDY      0x40
DECL|macro|INTSTAT
mdefine_line|#define INTSTAT      0x20
DECL|macro|DFIFOFULL
mdefine_line|#define DFIFOFULL    0x10
DECL|macro|DFIFOEMP
mdefine_line|#define DFIFOEMP     0x08
multiline_comment|/* BURST control */
DECL|macro|BON
mdefine_line|#define BON          0xf0
DECL|macro|BOFF
mdefine_line|#define BOFF         0x0f
multiline_comment|/* TEST REGISTER */
DECL|macro|BOFFTMR
mdefine_line|#define BOFFTMR      0x40
DECL|macro|BONTMR
mdefine_line|#define BONTMR       0x20
DECL|macro|STCNTH
mdefine_line|#define STCNTH       0x10
DECL|macro|STCNTM
mdefine_line|#define STCNTM       0x08
DECL|macro|STCNTL
mdefine_line|#define STCNTL       0x04
DECL|macro|SCSIBLK
mdefine_line|#define SCSIBLK      0x02
DECL|macro|DMABLK
mdefine_line|#define DMABLK       0x01
multiline_comment|/* On the AHA-152x board PORTA and PORTB contain&n;   some information about the board&squot;s configuration. */
r_typedef
r_union
(brace
r_struct
(brace
DECL|member|reserved
r_int
id|reserved
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|tardisc
r_int
id|tardisc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Target disconnect: 0=disabled, 1=enabled */
DECL|member|syncneg
r_int
id|syncneg
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Initial sync neg: 0=disabled, 1=enabled */
DECL|member|msgclasses
r_int
id|msgclasses
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Message classes&n;                                 0=#4&n;                                 1=#0, #1, #2, #3, #4&n;                                 2=#0, #3, #4&n;                                 3=#0, #4&n;                             */
DECL|member|boot
r_int
id|boot
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* boot: 0=disabled, 1=enabled */
DECL|member|dma
r_int
id|dma
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Transfer mode: 0=PIO; 1=DMA */
DECL|member|id
r_int
id|id
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* SCSI-id */
DECL|member|irq
r_int
id|irq
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* IRQ-Channel: 0,3=12, 1=10, 2=11 */
DECL|member|dmachan
r_int
id|dmachan
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* DMA-Channel: 0=0, 1=5, 2=6, 3=7 */
DECL|member|parity
r_int
id|parity
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* SCSI-parity: 1=enabled 0=disabled */
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
DECL|typedef|aha152x_config
)brace
id|aha152x_config
suffix:semicolon
DECL|macro|cf_parity
mdefine_line|#define cf_parity     fields.parity
DECL|macro|cf_dmachan
mdefine_line|#define cf_dmachan    fields.dmachan
DECL|macro|cf_irq
mdefine_line|#define cf_irq        fields.irq
DECL|macro|cf_id
mdefine_line|#define cf_id         fields.id
DECL|macro|cf_dma
mdefine_line|#define cf_dma        fields.dma
DECL|macro|cf_boot
mdefine_line|#define cf_boot       fields.boot
DECL|macro|cf_msgclasses
mdefine_line|#define cf_msgclasses fields.msgclasses
DECL|macro|cf_syncneg
mdefine_line|#define cf_syncneg    fields.syncneg
DECL|macro|cf_tardisc
mdefine_line|#define cf_tardisc    fields.tardisc
DECL|macro|cf_port
mdefine_line|#define cf_port       port
multiline_comment|/* Some macros to manipulate ports and their bits */
DECL|macro|SETPORT
mdefine_line|#define SETPORT(PORT, VAL)&t;outb( (VAL), (PORT) )
DECL|macro|GETPORT
mdefine_line|#define GETPORT(PORT)&t;&t;inb( PORT )
DECL|macro|SETBITS
mdefine_line|#define SETBITS(PORT, BITS)&t;outb( (inb(PORT) | (BITS)), (PORT) )
DECL|macro|CLRBITS
mdefine_line|#define CLRBITS(PORT, BITS)&t;outb( (inb(PORT) &amp; ~(BITS)), (PORT) )
DECL|macro|TESTHI
mdefine_line|#define TESTHI(PORT, BITS)&t;((inb(PORT) &amp; (BITS)) == (BITS))
DECL|macro|TESTLO
mdefine_line|#define TESTLO(PORT, BITS)&t;((inb(PORT) &amp; (BITS)) == 0)
DECL|macro|SETRATE
mdefine_line|#define SETRATE(RATE)&t;&t;SETPORT(SCSIRATE,(RATE) &amp; 0x7f)
macro_line|#if defined(AHA152X_DEBUG)
r_enum
(brace
DECL|enumerator|debug_procinfo
id|debug_procinfo
op_assign
l_int|0x0001
comma
DECL|enumerator|debug_queue
id|debug_queue
op_assign
l_int|0x0002
comma
DECL|enumerator|debug_locks
id|debug_locks
op_assign
l_int|0x0004
comma
DECL|enumerator|debug_intr
id|debug_intr
op_assign
l_int|0x0008
comma
DECL|enumerator|debug_selection
id|debug_selection
op_assign
l_int|0x0010
comma
DECL|enumerator|debug_msgo
id|debug_msgo
op_assign
l_int|0x0020
comma
DECL|enumerator|debug_msgi
id|debug_msgi
op_assign
l_int|0x0040
comma
DECL|enumerator|debug_status
id|debug_status
op_assign
l_int|0x0080
comma
DECL|enumerator|debug_cmd
id|debug_cmd
op_assign
l_int|0x0100
comma
DECL|enumerator|debug_datai
id|debug_datai
op_assign
l_int|0x0200
comma
DECL|enumerator|debug_datao
id|debug_datao
op_assign
l_int|0x0400
comma
DECL|enumerator|debug_eh
id|debug_eh
op_assign
l_int|0x0800
comma
DECL|enumerator|debug_done
id|debug_done
op_assign
l_int|0x1000
comma
DECL|enumerator|debug_phases
id|debug_phases
op_assign
l_int|0x2000
comma
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _AHA152X_H */
eof
