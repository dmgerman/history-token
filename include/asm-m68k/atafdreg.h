macro_line|#ifndef _LINUX_FDREG_H
DECL|macro|_LINUX_FDREG_H
mdefine_line|#define _LINUX_FDREG_H
multiline_comment|/*&n;** WD1772 stuff&n; */
multiline_comment|/* register codes */
DECL|macro|FDCSELREG_STP
mdefine_line|#define FDCSELREG_STP   (0x80)   /* command/status register */
DECL|macro|FDCSELREG_TRA
mdefine_line|#define FDCSELREG_TRA   (0x82)   /* track register */
DECL|macro|FDCSELREG_SEC
mdefine_line|#define FDCSELREG_SEC   (0x84)   /* sector register */
DECL|macro|FDCSELREG_DTA
mdefine_line|#define FDCSELREG_DTA   (0x86)   /* data register */
multiline_comment|/* register names for FDC_READ/WRITE macros */
DECL|macro|FDCREG_CMD
mdefine_line|#define FDCREG_CMD&t;&t;0
DECL|macro|FDCREG_STATUS
mdefine_line|#define FDCREG_STATUS&t;0
DECL|macro|FDCREG_TRACK
mdefine_line|#define FDCREG_TRACK&t;2
DECL|macro|FDCREG_SECTOR
mdefine_line|#define FDCREG_SECTOR&t;4
DECL|macro|FDCREG_DATA
mdefine_line|#define FDCREG_DATA&t;&t;6
multiline_comment|/* command opcodes */
DECL|macro|FDCCMD_RESTORE
mdefine_line|#define FDCCMD_RESTORE  (0x00)   /*  -                   */
DECL|macro|FDCCMD_SEEK
mdefine_line|#define FDCCMD_SEEK     (0x10)   /*   |                  */
DECL|macro|FDCCMD_STEP
mdefine_line|#define FDCCMD_STEP     (0x20)   /*   |  TYP 1 Commands  */
DECL|macro|FDCCMD_STIN
mdefine_line|#define FDCCMD_STIN     (0x40)   /*   |                  */
DECL|macro|FDCCMD_STOT
mdefine_line|#define FDCCMD_STOT     (0x60)   /*  -                   */
DECL|macro|FDCCMD_RDSEC
mdefine_line|#define FDCCMD_RDSEC    (0x80)   /*  -   TYP 2 Commands  */
DECL|macro|FDCCMD_WRSEC
mdefine_line|#define FDCCMD_WRSEC    (0xa0)   /*  -          &quot;        */
DECL|macro|FDCCMD_RDADR
mdefine_line|#define FDCCMD_RDADR    (0xc0)   /*  -                   */
DECL|macro|FDCCMD_RDTRA
mdefine_line|#define FDCCMD_RDTRA    (0xe0)   /*   |  TYP 3 Commands  */
DECL|macro|FDCCMD_WRTRA
mdefine_line|#define FDCCMD_WRTRA    (0xf0)   /*  -                   */
DECL|macro|FDCCMD_FORCI
mdefine_line|#define FDCCMD_FORCI    (0xd0)   /*  -   TYP 4 Command   */
multiline_comment|/* command modifier bits */
DECL|macro|FDCCMDADD_SR6
mdefine_line|#define FDCCMDADD_SR6   (0x00)   /* step rate settings */
DECL|macro|FDCCMDADD_SR12
mdefine_line|#define FDCCMDADD_SR12  (0x01)
DECL|macro|FDCCMDADD_SR2
mdefine_line|#define FDCCMDADD_SR2   (0x02)
DECL|macro|FDCCMDADD_SR3
mdefine_line|#define FDCCMDADD_SR3   (0x03)
DECL|macro|FDCCMDADD_V
mdefine_line|#define FDCCMDADD_V     (0x04)   /* verify */
DECL|macro|FDCCMDADD_H
mdefine_line|#define FDCCMDADD_H     (0x08)   /* wait for spin-up */
DECL|macro|FDCCMDADD_U
mdefine_line|#define FDCCMDADD_U     (0x10)   /* update track register */
DECL|macro|FDCCMDADD_M
mdefine_line|#define FDCCMDADD_M     (0x10)   /* multiple sector access */
DECL|macro|FDCCMDADD_E
mdefine_line|#define FDCCMDADD_E     (0x04)   /* head settling flag */
DECL|macro|FDCCMDADD_P
mdefine_line|#define FDCCMDADD_P     (0x02)   /* precompensation off */
DECL|macro|FDCCMDADD_A0
mdefine_line|#define FDCCMDADD_A0    (0x01)   /* DAM flag */
multiline_comment|/* status register bits */
DECL|macro|FDCSTAT_MOTORON
mdefine_line|#define&t;FDCSTAT_MOTORON&t;(0x80)   /* motor on */
DECL|macro|FDCSTAT_WPROT
mdefine_line|#define&t;FDCSTAT_WPROT&t;(0x40)   /* write protected (FDCCMD_WR*) */
DECL|macro|FDCSTAT_SPINUP
mdefine_line|#define&t;FDCSTAT_SPINUP&t;(0x20)   /* motor speed stable (Type I) */
DECL|macro|FDCSTAT_DELDAM
mdefine_line|#define&t;FDCSTAT_DELDAM&t;(0x20)   /* sector has deleted DAM (Type II+III) */
DECL|macro|FDCSTAT_RECNF
mdefine_line|#define&t;FDCSTAT_RECNF&t;(0x10)   /* record not found */
DECL|macro|FDCSTAT_CRC
mdefine_line|#define&t;FDCSTAT_CRC&t;&t;(0x08)   /* CRC error */
DECL|macro|FDCSTAT_TR00
mdefine_line|#define&t;FDCSTAT_TR00&t;(0x04)   /* Track 00 flag (Type I) */
DECL|macro|FDCSTAT_LOST
mdefine_line|#define&t;FDCSTAT_LOST&t;(0x04)   /* Lost Data (Type II+III) */
DECL|macro|FDCSTAT_IDX
mdefine_line|#define&t;FDCSTAT_IDX&t;&t;(0x02)   /* Index status (Type I) */
DECL|macro|FDCSTAT_DRQ
mdefine_line|#define&t;FDCSTAT_DRQ&t;&t;(0x02)   /* DRQ status (Type II+III) */
DECL|macro|FDCSTAT_BUSY
mdefine_line|#define&t;FDCSTAT_BUSY&t;(0x01)   /* FDC is busy */
multiline_comment|/* PSG Port A Bit Nr 0 .. Side Sel .. 0 -&gt; Side 1  1 -&gt; Side 2 */
DECL|macro|DSKSIDE
mdefine_line|#define DSKSIDE     (0x01)
DECL|macro|DSKDRVNONE
mdefine_line|#define DSKDRVNONE  (0x06)
DECL|macro|DSKDRV0
mdefine_line|#define DSKDRV0     (0x02)
DECL|macro|DSKDRV1
mdefine_line|#define DSKDRV1     (0x04)
multiline_comment|/* step rates */
DECL|macro|FDCSTEP_6
mdefine_line|#define&t;FDCSTEP_6&t;0x00
DECL|macro|FDCSTEP_12
mdefine_line|#define&t;FDCSTEP_12&t;0x01
DECL|macro|FDCSTEP_2
mdefine_line|#define&t;FDCSTEP_2&t;0x02
DECL|macro|FDCSTEP_3
mdefine_line|#define&t;FDCSTEP_3&t;0x03
macro_line|#endif
eof
