macro_line|#ifndef _LINUX_FD1772REG_H
DECL|macro|_LINUX_FD1772REG_H
mdefine_line|#define _LINUX_FD1772REG_H
multiline_comment|/*&n;** WD1772 stuff - originally from the M68K Linux&n; * Modified for Archimedes by Dave Gilbert (gilbertd@cs.man.ac.uk)&n; */
multiline_comment|/* register codes */
DECL|macro|FDC1772SELREG_STP
mdefine_line|#define FDC1772SELREG_STP   (0x80)   /* command/status register */
DECL|macro|FDC1772SELREG_TRA
mdefine_line|#define FDC1772SELREG_TRA   (0x82)   /* track register */
DECL|macro|FDC1772SELREG_SEC
mdefine_line|#define FDC1772SELREG_SEC   (0x84)   /* sector register */
DECL|macro|FDC1772SELREG_DTA
mdefine_line|#define FDC1772SELREG_DTA   (0x86)   /* data register */
multiline_comment|/* register names for FDC1772_READ/WRITE macros */
DECL|macro|FDC1772REG_CMD
mdefine_line|#define FDC1772REG_CMD         0
DECL|macro|FDC1772REG_STATUS
mdefine_line|#define FDC1772REG_STATUS      0
DECL|macro|FDC1772REG_TRACK
mdefine_line|#define FDC1772REG_TRACK       2
DECL|macro|FDC1772REG_SECTOR
mdefine_line|#define FDC1772REG_SECTOR      4
DECL|macro|FDC1772REG_DATA
mdefine_line|#define FDC1772REG_DATA                6
multiline_comment|/* command opcodes */
DECL|macro|FDC1772CMD_RESTORE
mdefine_line|#define FDC1772CMD_RESTORE  (0x00)   /*  -                   */
DECL|macro|FDC1772CMD_SEEK
mdefine_line|#define FDC1772CMD_SEEK     (0x10)   /*   |                  */
DECL|macro|FDC1772CMD_STEP
mdefine_line|#define FDC1772CMD_STEP     (0x20)   /*   |  TYP 1 Commands  */
DECL|macro|FDC1772CMD_STIN
mdefine_line|#define FDC1772CMD_STIN     (0x40)   /*   |                  */
DECL|macro|FDC1772CMD_STOT
mdefine_line|#define FDC1772CMD_STOT     (0x60)   /*  -                   */
DECL|macro|FDC1772CMD_RDSEC
mdefine_line|#define FDC1772CMD_RDSEC    (0x80)   /*  -   TYP 2 Commands  */
DECL|macro|FDC1772CMD_WRSEC
mdefine_line|#define FDC1772CMD_WRSEC    (0xa0)   /*  -          &quot;        */
DECL|macro|FDC1772CMD_RDADR
mdefine_line|#define FDC1772CMD_RDADR    (0xc0)   /*  -                   */
DECL|macro|FDC1772CMD_RDTRA
mdefine_line|#define FDC1772CMD_RDTRA    (0xe0)   /*   |  TYP 3 Commands  */
DECL|macro|FDC1772CMD_WRTRA
mdefine_line|#define FDC1772CMD_WRTRA    (0xf0)   /*  -                   */
DECL|macro|FDC1772CMD_FORCI
mdefine_line|#define FDC1772CMD_FORCI    (0xd0)   /*  -   TYP 4 Command   */
multiline_comment|/* command modifier bits */
DECL|macro|FDC1772CMDADD_SR6
mdefine_line|#define FDC1772CMDADD_SR6   (0x00)   /* step rate settings */
DECL|macro|FDC1772CMDADD_SR12
mdefine_line|#define FDC1772CMDADD_SR12  (0x01)
DECL|macro|FDC1772CMDADD_SR2
mdefine_line|#define FDC1772CMDADD_SR2   (0x02)
DECL|macro|FDC1772CMDADD_SR3
mdefine_line|#define FDC1772CMDADD_SR3   (0x03)
DECL|macro|FDC1772CMDADD_V
mdefine_line|#define FDC1772CMDADD_V     (0x04)   /* verify */
DECL|macro|FDC1772CMDADD_H
mdefine_line|#define FDC1772CMDADD_H     (0x08)   /* wait for spin-up */
DECL|macro|FDC1772CMDADD_U
mdefine_line|#define FDC1772CMDADD_U     (0x10)   /* update track register */
DECL|macro|FDC1772CMDADD_M
mdefine_line|#define FDC1772CMDADD_M     (0x10)   /* multiple sector access */
DECL|macro|FDC1772CMDADD_E
mdefine_line|#define FDC1772CMDADD_E     (0x04)   /* head settling flag */
DECL|macro|FDC1772CMDADD_P
mdefine_line|#define FDC1772CMDADD_P     (0x02)   /* precompensation */
DECL|macro|FDC1772CMDADD_A0
mdefine_line|#define FDC1772CMDADD_A0    (0x01)   /* DAM flag */
multiline_comment|/* status register bits */
DECL|macro|FDC1772STAT_MOTORON
mdefine_line|#define        FDC1772STAT_MOTORON     (0x80)   /* motor on */
DECL|macro|FDC1772STAT_WPROT
mdefine_line|#define        FDC1772STAT_WPROT       (0x40)   /* write protected (FDC1772CMD_WR*) */
DECL|macro|FDC1772STAT_SPINUP
mdefine_line|#define        FDC1772STAT_SPINUP      (0x20)   /* motor speed stable (Type I) */
DECL|macro|FDC1772STAT_DELDAM
mdefine_line|#define        FDC1772STAT_DELDAM      (0x20)   /* sector has deleted DAM (Type II+III) */
DECL|macro|FDC1772STAT_RECNF
mdefine_line|#define        FDC1772STAT_RECNF       (0x10)   /* record not found */
DECL|macro|FDC1772STAT_CRC
mdefine_line|#define        FDC1772STAT_CRC         (0x08)   /* CRC error */
DECL|macro|FDC1772STAT_TR00
mdefine_line|#define        FDC1772STAT_TR00        (0x04)   /* Track 00 flag (Type I) */
DECL|macro|FDC1772STAT_LOST
mdefine_line|#define        FDC1772STAT_LOST        (0x04)   /* Lost Data (Type II+III) */
DECL|macro|FDC1772STAT_IDX
mdefine_line|#define        FDC1772STAT_IDX         (0x02)   /* Index status (Type I) */
DECL|macro|FDC1772STAT_DRQ
mdefine_line|#define        FDC1772STAT_DRQ         (0x02)   /* DRQ status (Type II+III) */
DECL|macro|FDC1772STAT_BUSY
mdefine_line|#define        FDC1772STAT_BUSY        (0x01)   /* FDC1772 is busy */
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
DECL|macro|FDC1772STEP_6
mdefine_line|#define        FDC1772STEP_6   0x00
DECL|macro|FDC1772STEP_12
mdefine_line|#define        FDC1772STEP_12  0x01
DECL|macro|FDC1772STEP_2
mdefine_line|#define        FDC1772STEP_2   0x02
DECL|macro|FDC1772STEP_3
mdefine_line|#define        FDC1772STEP_3   0x03
macro_line|#endif
eof
