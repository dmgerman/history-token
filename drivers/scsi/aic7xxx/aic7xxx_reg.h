multiline_comment|/*&n; * DO NOT EDIT - This file is automatically generated&n; *&t;&t; from the following source files:&n; *&n; * $Id: //depot/src/aic7xxx/aic7xxx.seq#33 $&n; * $Id: //depot/src/aic7xxx/aic7xxx.reg#19 $&n; */
DECL|macro|SCSISEQ
mdefine_line|#define&t;SCSISEQ         &t;&t;0x00
DECL|macro|TEMODE
mdefine_line|#define&t;&t;TEMODE          &t;0x80
DECL|macro|SCSIRSTO
mdefine_line|#define&t;&t;SCSIRSTO        &t;0x01
DECL|macro|SXFRCTL0
mdefine_line|#define&t;SXFRCTL0        &t;&t;0x01
DECL|macro|DFON
mdefine_line|#define&t;&t;DFON            &t;0x80
DECL|macro|DFPEXP
mdefine_line|#define&t;&t;DFPEXP          &t;0x40
DECL|macro|FAST20
mdefine_line|#define&t;&t;FAST20          &t;0x20
DECL|macro|CLRSTCNT
mdefine_line|#define&t;&t;CLRSTCNT        &t;0x10
DECL|macro|SPIOEN
mdefine_line|#define&t;&t;SPIOEN          &t;0x08
DECL|macro|SCAMEN
mdefine_line|#define&t;&t;SCAMEN          &t;0x04
DECL|macro|CLRCHN
mdefine_line|#define&t;&t;CLRCHN          &t;0x02
DECL|macro|SXFRCTL1
mdefine_line|#define&t;SXFRCTL1        &t;&t;0x02
DECL|macro|BITBUCKET
mdefine_line|#define&t;&t;BITBUCKET       &t;0x80
DECL|macro|SWRAPEN
mdefine_line|#define&t;&t;SWRAPEN         &t;0x40
DECL|macro|STIMESEL
mdefine_line|#define&t;&t;STIMESEL        &t;0x18
DECL|macro|ENSTIMER
mdefine_line|#define&t;&t;ENSTIMER        &t;0x04
DECL|macro|ACTNEGEN
mdefine_line|#define&t;&t;ACTNEGEN        &t;0x02
DECL|macro|STPWEN
mdefine_line|#define&t;&t;STPWEN          &t;0x01
DECL|macro|SCSISIGO
mdefine_line|#define&t;SCSISIGO        &t;&t;0x03
DECL|macro|CDO
mdefine_line|#define&t;&t;CDO             &t;0x80
DECL|macro|IOO
mdefine_line|#define&t;&t;IOO             &t;0x40
DECL|macro|MSGO
mdefine_line|#define&t;&t;MSGO            &t;0x20
DECL|macro|ATNO
mdefine_line|#define&t;&t;ATNO            &t;0x10
DECL|macro|SELO
mdefine_line|#define&t;&t;SELO            &t;0x08
DECL|macro|BSYO
mdefine_line|#define&t;&t;BSYO            &t;0x04
DECL|macro|REQO
mdefine_line|#define&t;&t;REQO            &t;0x02
DECL|macro|ACKO
mdefine_line|#define&t;&t;ACKO            &t;0x01
DECL|macro|SCSISIGI
mdefine_line|#define&t;SCSISIGI        &t;&t;0x03
DECL|macro|P_DATAIN_DT
mdefine_line|#define&t;&t;P_DATAIN_DT     &t;0x60
DECL|macro|P_DATAOUT_DT
mdefine_line|#define&t;&t;P_DATAOUT_DT    &t;0x20
DECL|macro|ATNI
mdefine_line|#define&t;&t;ATNI            &t;0x10
DECL|macro|SELI
mdefine_line|#define&t;&t;SELI            &t;0x08
DECL|macro|BSYI
mdefine_line|#define&t;&t;BSYI            &t;0x04
DECL|macro|REQI
mdefine_line|#define&t;&t;REQI            &t;0x02
DECL|macro|ACKI
mdefine_line|#define&t;&t;ACKI            &t;0x01
DECL|macro|SCSIRATE
mdefine_line|#define&t;SCSIRATE        &t;&t;0x04
DECL|macro|WIDEXFER
mdefine_line|#define&t;&t;WIDEXFER        &t;0x80
DECL|macro|SXFR
mdefine_line|#define&t;&t;SXFR            &t;0x70
DECL|macro|ENABLE_CRC
mdefine_line|#define&t;&t;ENABLE_CRC      &t;0x40
DECL|macro|SINGLE_EDGE
mdefine_line|#define&t;&t;SINGLE_EDGE     &t;0x10
DECL|macro|SOFS
mdefine_line|#define&t;&t;SOFS            &t;0x0f
DECL|macro|SXFR_ULTRA2
mdefine_line|#define&t;&t;SXFR_ULTRA2     &t;0x0f
DECL|macro|SCSIID
mdefine_line|#define&t;SCSIID          &t;&t;0x05
DECL|macro|SCSIOFFSET
mdefine_line|#define&t;SCSIOFFSET      &t;&t;0x05
DECL|macro|SOFS_ULTRA2
mdefine_line|#define&t;&t;SOFS_ULTRA2     &t;0x7f
DECL|macro|SCSIDATL
mdefine_line|#define&t;SCSIDATL        &t;&t;0x06
DECL|macro|SCSIDATH
mdefine_line|#define&t;SCSIDATH        &t;&t;0x07
DECL|macro|STCNT
mdefine_line|#define&t;STCNT           &t;&t;0x08
DECL|macro|OPTIONMODE
mdefine_line|#define&t;OPTIONMODE      &t;&t;0x08
DECL|macro|AUTORATEEN
mdefine_line|#define&t;&t;AUTORATEEN      &t;0x80
DECL|macro|AUTOACKEN
mdefine_line|#define&t;&t;AUTOACKEN       &t;0x40
DECL|macro|ATNMGMNTEN
mdefine_line|#define&t;&t;ATNMGMNTEN      &t;0x20
DECL|macro|BUSFREEREV
mdefine_line|#define&t;&t;BUSFREEREV      &t;0x10
DECL|macro|EXPPHASEDIS
mdefine_line|#define&t;&t;EXPPHASEDIS     &t;0x08
DECL|macro|SCSIDATL_IMGEN
mdefine_line|#define&t;&t;SCSIDATL_IMGEN  &t;0x04
DECL|macro|OPTIONMODE_DEFAULTS
mdefine_line|#define&t;&t;OPTIONMODE_DEFAULTS&t;0x03
DECL|macro|AUTO_MSGOUT_DE
mdefine_line|#define&t;&t;AUTO_MSGOUT_DE  &t;0x02
DECL|macro|DIS_MSGIN_DUALEDGE
mdefine_line|#define&t;&t;DIS_MSGIN_DUALEDGE&t;0x01
DECL|macro|TARGCRCCNT
mdefine_line|#define&t;TARGCRCCNT      &t;&t;0x0a
DECL|macro|CLRSINT0
mdefine_line|#define&t;CLRSINT0        &t;&t;0x0b
DECL|macro|CLRSELDO
mdefine_line|#define&t;&t;CLRSELDO        &t;0x40
DECL|macro|CLRSELDI
mdefine_line|#define&t;&t;CLRSELDI        &t;0x20
DECL|macro|CLRSELINGO
mdefine_line|#define&t;&t;CLRSELINGO      &t;0x10
DECL|macro|CLRIOERR
mdefine_line|#define&t;&t;CLRIOERR        &t;0x08
DECL|macro|CLRSWRAP
mdefine_line|#define&t;&t;CLRSWRAP        &t;0x08
DECL|macro|CLRSPIORDY
mdefine_line|#define&t;&t;CLRSPIORDY      &t;0x02
DECL|macro|SSTAT0
mdefine_line|#define&t;SSTAT0          &t;&t;0x0b
DECL|macro|TARGET
mdefine_line|#define&t;&t;TARGET          &t;0x80
DECL|macro|SELDO
mdefine_line|#define&t;&t;SELDO           &t;0x40
DECL|macro|SELDI
mdefine_line|#define&t;&t;SELDI           &t;0x20
DECL|macro|SELINGO
mdefine_line|#define&t;&t;SELINGO         &t;0x10
DECL|macro|SWRAP
mdefine_line|#define&t;&t;SWRAP           &t;0x08
DECL|macro|IOERR
mdefine_line|#define&t;&t;IOERR           &t;0x08
DECL|macro|SDONE
mdefine_line|#define&t;&t;SDONE           &t;0x04
DECL|macro|SPIORDY
mdefine_line|#define&t;&t;SPIORDY         &t;0x02
DECL|macro|DMADONE
mdefine_line|#define&t;&t;DMADONE         &t;0x01
DECL|macro|CLRSINT1
mdefine_line|#define&t;CLRSINT1        &t;&t;0x0c
DECL|macro|CLRSELTIMEO
mdefine_line|#define&t;&t;CLRSELTIMEO     &t;0x80
DECL|macro|CLRATNO
mdefine_line|#define&t;&t;CLRATNO         &t;0x40
DECL|macro|CLRSCSIRSTI
mdefine_line|#define&t;&t;CLRSCSIRSTI     &t;0x20
DECL|macro|CLRBUSFREE
mdefine_line|#define&t;&t;CLRBUSFREE      &t;0x08
DECL|macro|CLRSCSIPERR
mdefine_line|#define&t;&t;CLRSCSIPERR     &t;0x04
DECL|macro|CLRPHASECHG
mdefine_line|#define&t;&t;CLRPHASECHG     &t;0x02
DECL|macro|CLRREQINIT
mdefine_line|#define&t;&t;CLRREQINIT      &t;0x01
DECL|macro|SSTAT1
mdefine_line|#define&t;SSTAT1          &t;&t;0x0c
DECL|macro|SELTO
mdefine_line|#define&t;&t;SELTO           &t;0x80
DECL|macro|ATNTARG
mdefine_line|#define&t;&t;ATNTARG         &t;0x40
DECL|macro|SCSIRSTI
mdefine_line|#define&t;&t;SCSIRSTI        &t;0x20
DECL|macro|PHASEMIS
mdefine_line|#define&t;&t;PHASEMIS        &t;0x10
DECL|macro|BUSFREE
mdefine_line|#define&t;&t;BUSFREE         &t;0x08
DECL|macro|SCSIPERR
mdefine_line|#define&t;&t;SCSIPERR        &t;0x04
DECL|macro|PHASECHG
mdefine_line|#define&t;&t;PHASECHG        &t;0x02
DECL|macro|REQINIT
mdefine_line|#define&t;&t;REQINIT         &t;0x01
DECL|macro|SSTAT2
mdefine_line|#define&t;SSTAT2          &t;&t;0x0d
DECL|macro|OVERRUN
mdefine_line|#define&t;&t;OVERRUN         &t;0x80
DECL|macro|SHVALID
mdefine_line|#define&t;&t;SHVALID         &t;0x40
DECL|macro|SFCNT
mdefine_line|#define&t;&t;SFCNT           &t;0x1f
DECL|macro|EXP_ACTIVE
mdefine_line|#define&t;&t;EXP_ACTIVE      &t;0x10
DECL|macro|CRCVALERR
mdefine_line|#define&t;&t;CRCVALERR       &t;0x08
DECL|macro|CRCENDERR
mdefine_line|#define&t;&t;CRCENDERR       &t;0x04
DECL|macro|CRCREQERR
mdefine_line|#define&t;&t;CRCREQERR       &t;0x02
DECL|macro|DUAL_EDGE_ERR
mdefine_line|#define&t;&t;DUAL_EDGE_ERR   &t;0x01
DECL|macro|SSTAT3
mdefine_line|#define&t;SSTAT3          &t;&t;0x0e
DECL|macro|SCSICNT
mdefine_line|#define&t;&t;SCSICNT         &t;0xf0
DECL|macro|OFFCNT
mdefine_line|#define&t;&t;OFFCNT          &t;0x0f
DECL|macro|SCSIID_ULTRA2
mdefine_line|#define&t;SCSIID_ULTRA2   &t;&t;0x0f
DECL|macro|SIMODE0
mdefine_line|#define&t;SIMODE0         &t;&t;0x10
DECL|macro|ENSELDO
mdefine_line|#define&t;&t;ENSELDO         &t;0x40
DECL|macro|ENSELDI
mdefine_line|#define&t;&t;ENSELDI         &t;0x20
DECL|macro|ENSELINGO
mdefine_line|#define&t;&t;ENSELINGO       &t;0x10
DECL|macro|ENIOERR
mdefine_line|#define&t;&t;ENIOERR         &t;0x08
DECL|macro|ENSWRAP
mdefine_line|#define&t;&t;ENSWRAP         &t;0x08
DECL|macro|ENSDONE
mdefine_line|#define&t;&t;ENSDONE         &t;0x04
DECL|macro|ENSPIORDY
mdefine_line|#define&t;&t;ENSPIORDY       &t;0x02
DECL|macro|ENDMADONE
mdefine_line|#define&t;&t;ENDMADONE       &t;0x01
DECL|macro|SIMODE1
mdefine_line|#define&t;SIMODE1         &t;&t;0x11
DECL|macro|ENSELTIMO
mdefine_line|#define&t;&t;ENSELTIMO       &t;0x80
DECL|macro|ENATNTARG
mdefine_line|#define&t;&t;ENATNTARG       &t;0x40
DECL|macro|ENSCSIRST
mdefine_line|#define&t;&t;ENSCSIRST       &t;0x20
DECL|macro|ENPHASEMIS
mdefine_line|#define&t;&t;ENPHASEMIS      &t;0x10
DECL|macro|ENBUSFREE
mdefine_line|#define&t;&t;ENBUSFREE       &t;0x08
DECL|macro|ENSCSIPERR
mdefine_line|#define&t;&t;ENSCSIPERR      &t;0x04
DECL|macro|ENPHASECHG
mdefine_line|#define&t;&t;ENPHASECHG      &t;0x02
DECL|macro|ENREQINIT
mdefine_line|#define&t;&t;ENREQINIT       &t;0x01
DECL|macro|SCSIBUSL
mdefine_line|#define&t;SCSIBUSL        &t;&t;0x12
DECL|macro|SCSIBUSH
mdefine_line|#define&t;SCSIBUSH        &t;&t;0x13
DECL|macro|SHADDR
mdefine_line|#define&t;SHADDR          &t;&t;0x14
DECL|macro|SELTIMER
mdefine_line|#define&t;SELTIMER        &t;&t;0x18
DECL|macro|TARGIDIN
mdefine_line|#define&t;TARGIDIN        &t;&t;0x18
DECL|macro|STAGE6
mdefine_line|#define&t;&t;STAGE6          &t;0x20
DECL|macro|STAGE5
mdefine_line|#define&t;&t;STAGE5          &t;0x10
DECL|macro|STAGE4
mdefine_line|#define&t;&t;STAGE4          &t;0x08
DECL|macro|STAGE3
mdefine_line|#define&t;&t;STAGE3          &t;0x04
DECL|macro|STAGE2
mdefine_line|#define&t;&t;STAGE2          &t;0x02
DECL|macro|STAGE1
mdefine_line|#define&t;&t;STAGE1          &t;0x01
DECL|macro|SELID
mdefine_line|#define&t;SELID           &t;&t;0x19
DECL|macro|SELID_MASK
mdefine_line|#define&t;&t;SELID_MASK      &t;0xf0
DECL|macro|ONEBIT
mdefine_line|#define&t;&t;ONEBIT          &t;0x08
DECL|macro|SCAMCTL
mdefine_line|#define&t;SCAMCTL         &t;&t;0x1a
DECL|macro|ENSCAMSELO
mdefine_line|#define&t;&t;ENSCAMSELO      &t;0x80
DECL|macro|CLRSCAMSELID
mdefine_line|#define&t;&t;CLRSCAMSELID    &t;0x40
DECL|macro|ALTSTIM
mdefine_line|#define&t;&t;ALTSTIM         &t;0x20
DECL|macro|DFLTTID
mdefine_line|#define&t;&t;DFLTTID         &t;0x10
DECL|macro|SCAMLVL
mdefine_line|#define&t;&t;SCAMLVL         &t;0x03
DECL|macro|TARGID
mdefine_line|#define&t;TARGID          &t;&t;0x1b
DECL|macro|SPIOCAP
mdefine_line|#define&t;SPIOCAP         &t;&t;0x1b
DECL|macro|SOFT1
mdefine_line|#define&t;&t;SOFT1           &t;0x80
DECL|macro|SOFT0
mdefine_line|#define&t;&t;SOFT0           &t;0x40
DECL|macro|SOFTCMDEN
mdefine_line|#define&t;&t;SOFTCMDEN       &t;0x20
DECL|macro|HAS_BRDCTL
mdefine_line|#define&t;&t;HAS_BRDCTL      &t;0x10
DECL|macro|SEEPROM
mdefine_line|#define&t;&t;SEEPROM         &t;0x08
DECL|macro|EEPROM
mdefine_line|#define&t;&t;EEPROM          &t;0x04
DECL|macro|ROM
mdefine_line|#define&t;&t;ROM             &t;0x02
DECL|macro|SSPIOCPS
mdefine_line|#define&t;&t;SSPIOCPS        &t;0x01
DECL|macro|BRDCTL
mdefine_line|#define&t;BRDCTL          &t;&t;0x1d
DECL|macro|BRDDAT7
mdefine_line|#define&t;&t;BRDDAT7         &t;0x80
DECL|macro|BRDDAT6
mdefine_line|#define&t;&t;BRDDAT6         &t;0x40
DECL|macro|BRDDAT5
mdefine_line|#define&t;&t;BRDDAT5         &t;0x20
DECL|macro|BRDDAT4
mdefine_line|#define&t;&t;BRDDAT4         &t;0x10
DECL|macro|BRDSTB
mdefine_line|#define&t;&t;BRDSTB          &t;0x10
DECL|macro|BRDDAT3
mdefine_line|#define&t;&t;BRDDAT3         &t;0x08
DECL|macro|BRDCS
mdefine_line|#define&t;&t;BRDCS           &t;0x08
DECL|macro|BRDDAT2
mdefine_line|#define&t;&t;BRDDAT2         &t;0x04
DECL|macro|BRDRW
mdefine_line|#define&t;&t;BRDRW           &t;0x04
DECL|macro|BRDRW_ULTRA2
mdefine_line|#define&t;&t;BRDRW_ULTRA2    &t;0x02
DECL|macro|BRDCTL1
mdefine_line|#define&t;&t;BRDCTL1         &t;0x02
DECL|macro|BRDCTL0
mdefine_line|#define&t;&t;BRDCTL0         &t;0x01
DECL|macro|BRDSTB_ULTRA2
mdefine_line|#define&t;&t;BRDSTB_ULTRA2   &t;0x01
DECL|macro|SEECTL
mdefine_line|#define&t;SEECTL          &t;&t;0x1e
DECL|macro|EXTARBACK
mdefine_line|#define&t;&t;EXTARBACK       &t;0x80
DECL|macro|EXTARBREQ
mdefine_line|#define&t;&t;EXTARBREQ       &t;0x40
DECL|macro|SEEMS
mdefine_line|#define&t;&t;SEEMS           &t;0x20
DECL|macro|SEERDY
mdefine_line|#define&t;&t;SEERDY          &t;0x10
DECL|macro|SEECS
mdefine_line|#define&t;&t;SEECS           &t;0x08
DECL|macro|SEECK
mdefine_line|#define&t;&t;SEECK           &t;0x04
DECL|macro|SEEDO
mdefine_line|#define&t;&t;SEEDO           &t;0x02
DECL|macro|SEEDI
mdefine_line|#define&t;&t;SEEDI           &t;0x01
DECL|macro|SBLKCTL
mdefine_line|#define&t;SBLKCTL         &t;&t;0x1f
DECL|macro|DIAGLEDEN
mdefine_line|#define&t;&t;DIAGLEDEN       &t;0x80
DECL|macro|DIAGLEDON
mdefine_line|#define&t;&t;DIAGLEDON       &t;0x40
DECL|macro|AUTOFLUSHDIS
mdefine_line|#define&t;&t;AUTOFLUSHDIS    &t;0x20
DECL|macro|ENAB40
mdefine_line|#define&t;&t;ENAB40          &t;0x08
DECL|macro|SELBUSB
mdefine_line|#define&t;&t;SELBUSB         &t;0x08
DECL|macro|ENAB20
mdefine_line|#define&t;&t;ENAB20          &t;0x04
DECL|macro|SELWIDE
mdefine_line|#define&t;&t;SELWIDE         &t;0x02
DECL|macro|XCVR
mdefine_line|#define&t;&t;XCVR            &t;0x01
DECL|macro|BUSY_TARGETS
mdefine_line|#define&t;BUSY_TARGETS    &t;&t;0x20
DECL|macro|TARG_SCSIRATE
mdefine_line|#define&t;TARG_SCSIRATE   &t;&t;0x20
DECL|macro|SRAM_BASE
mdefine_line|#define&t;SRAM_BASE       &t;&t;0x20
DECL|macro|ULTRA_ENB
mdefine_line|#define&t;ULTRA_ENB       &t;&t;0x30
DECL|macro|CMDSIZE_TABLE
mdefine_line|#define&t;CMDSIZE_TABLE   &t;&t;0x30
DECL|macro|DISC_DSB
mdefine_line|#define&t;DISC_DSB        &t;&t;0x32
DECL|macro|CMDSIZE_TABLE_TAIL
mdefine_line|#define&t;CMDSIZE_TABLE_TAIL&t;&t;0x34
DECL|macro|MWI_RESIDUAL
mdefine_line|#define&t;MWI_RESIDUAL    &t;&t;0x38
DECL|macro|NEXT_QUEUED_SCB
mdefine_line|#define&t;NEXT_QUEUED_SCB &t;&t;0x39
DECL|macro|MSG_OUT
mdefine_line|#define&t;MSG_OUT         &t;&t;0x3a
DECL|macro|DMAPARAMS
mdefine_line|#define&t;DMAPARAMS       &t;&t;0x3b
DECL|macro|PRELOADEN
mdefine_line|#define&t;&t;PRELOADEN       &t;0x80
DECL|macro|WIDEODD
mdefine_line|#define&t;&t;WIDEODD         &t;0x40
DECL|macro|SCSIEN
mdefine_line|#define&t;&t;SCSIEN          &t;0x20
DECL|macro|SDMAEN
mdefine_line|#define&t;&t;SDMAEN          &t;0x10
DECL|macro|SDMAENACK
mdefine_line|#define&t;&t;SDMAENACK       &t;0x10
DECL|macro|HDMAEN
mdefine_line|#define&t;&t;HDMAEN          &t;0x08
DECL|macro|HDMAENACK
mdefine_line|#define&t;&t;HDMAENACK       &t;0x08
DECL|macro|DIRECTION
mdefine_line|#define&t;&t;DIRECTION       &t;0x04
DECL|macro|FIFOFLUSH
mdefine_line|#define&t;&t;FIFOFLUSH       &t;0x02
DECL|macro|FIFORESET
mdefine_line|#define&t;&t;FIFORESET       &t;0x01
DECL|macro|SEQ_FLAGS
mdefine_line|#define&t;SEQ_FLAGS       &t;&t;0x3c
DECL|macro|IDENTIFY_SEEN
mdefine_line|#define&t;&t;IDENTIFY_SEEN   &t;0x80
DECL|macro|TARGET_CMD_IS_TAGGED
mdefine_line|#define&t;&t;TARGET_CMD_IS_TAGGED&t;0x40
DECL|macro|DPHASE
mdefine_line|#define&t;&t;DPHASE          &t;0x20
DECL|macro|TARG_CMD_PENDING
mdefine_line|#define&t;&t;TARG_CMD_PENDING&t;0x10
DECL|macro|CMDPHASE_PENDING
mdefine_line|#define&t;&t;CMDPHASE_PENDING&t;0x08
DECL|macro|DPHASE_PENDING
mdefine_line|#define&t;&t;DPHASE_PENDING  &t;0x04
DECL|macro|SPHASE_PENDING
mdefine_line|#define&t;&t;SPHASE_PENDING  &t;0x02
DECL|macro|NO_DISCONNECT
mdefine_line|#define&t;&t;NO_DISCONNECT   &t;0x01
DECL|macro|SAVED_SCSIID
mdefine_line|#define&t;SAVED_SCSIID    &t;&t;0x3d
DECL|macro|SAVED_LUN
mdefine_line|#define&t;SAVED_LUN       &t;&t;0x3e
DECL|macro|LASTPHASE
mdefine_line|#define&t;LASTPHASE       &t;&t;0x3f
DECL|macro|P_MESGIN
mdefine_line|#define&t;&t;P_MESGIN        &t;0xe0
DECL|macro|PHASE_MASK
mdefine_line|#define&t;&t;PHASE_MASK      &t;0xe0
DECL|macro|P_STATUS
mdefine_line|#define&t;&t;P_STATUS        &t;0xc0
DECL|macro|P_MESGOUT
mdefine_line|#define&t;&t;P_MESGOUT       &t;0xa0
DECL|macro|P_COMMAND
mdefine_line|#define&t;&t;P_COMMAND       &t;0x80
DECL|macro|CDI
mdefine_line|#define&t;&t;CDI             &t;0x80
DECL|macro|P_DATAIN
mdefine_line|#define&t;&t;P_DATAIN        &t;0x40
DECL|macro|IOI
mdefine_line|#define&t;&t;IOI             &t;0x40
DECL|macro|MSGI
mdefine_line|#define&t;&t;MSGI            &t;0x20
DECL|macro|P_BUSFREE
mdefine_line|#define&t;&t;P_BUSFREE       &t;0x01
DECL|macro|P_DATAOUT
mdefine_line|#define&t;&t;P_DATAOUT       &t;0x00
DECL|macro|WAITING_SCBH
mdefine_line|#define&t;WAITING_SCBH    &t;&t;0x40
DECL|macro|DISCONNECTED_SCBH
mdefine_line|#define&t;DISCONNECTED_SCBH&t;&t;0x41
DECL|macro|FREE_SCBH
mdefine_line|#define&t;FREE_SCBH       &t;&t;0x42
DECL|macro|COMPLETE_SCBH
mdefine_line|#define&t;COMPLETE_SCBH   &t;&t;0x43
DECL|macro|HSCB_ADDR
mdefine_line|#define&t;HSCB_ADDR       &t;&t;0x44
DECL|macro|SHARED_DATA_ADDR
mdefine_line|#define&t;SHARED_DATA_ADDR&t;&t;0x48
DECL|macro|KERNEL_QINPOS
mdefine_line|#define&t;KERNEL_QINPOS   &t;&t;0x4c
DECL|macro|QINPOS
mdefine_line|#define&t;QINPOS          &t;&t;0x4d
DECL|macro|QOUTPOS
mdefine_line|#define&t;QOUTPOS         &t;&t;0x4e
DECL|macro|KERNEL_TQINPOS
mdefine_line|#define&t;KERNEL_TQINPOS  &t;&t;0x4f
DECL|macro|TQINPOS
mdefine_line|#define&t;TQINPOS         &t;&t;0x50
DECL|macro|ARG_1
mdefine_line|#define&t;ARG_1           &t;&t;0x51
DECL|macro|RETURN_1
mdefine_line|#define&t;RETURN_1        &t;&t;0x51
DECL|macro|SEND_MSG
mdefine_line|#define&t;&t;SEND_MSG        &t;0x80
DECL|macro|SEND_SENSE
mdefine_line|#define&t;&t;SEND_SENSE      &t;0x40
DECL|macro|SEND_REJ
mdefine_line|#define&t;&t;SEND_REJ        &t;0x20
DECL|macro|MSGOUT_PHASEMIS
mdefine_line|#define&t;&t;MSGOUT_PHASEMIS &t;0x10
DECL|macro|EXIT_MSG_LOOP
mdefine_line|#define&t;&t;EXIT_MSG_LOOP   &t;0x08
DECL|macro|CONT_MSG_LOOP
mdefine_line|#define&t;&t;CONT_MSG_LOOP   &t;0x04
DECL|macro|CONT_TARG_SESSION
mdefine_line|#define&t;&t;CONT_TARG_SESSION&t;0x02
DECL|macro|ARG_2
mdefine_line|#define&t;ARG_2           &t;&t;0x52
DECL|macro|RETURN_2
mdefine_line|#define&t;RETURN_2        &t;&t;0x52
DECL|macro|LAST_MSG
mdefine_line|#define&t;LAST_MSG        &t;&t;0x53
DECL|macro|SCSISEQ_TEMPLATE
mdefine_line|#define&t;SCSISEQ_TEMPLATE&t;&t;0x54
DECL|macro|ENSELO
mdefine_line|#define&t;&t;ENSELO          &t;0x40
DECL|macro|ENSELI
mdefine_line|#define&t;&t;ENSELI          &t;0x20
DECL|macro|ENRSELI
mdefine_line|#define&t;&t;ENRSELI         &t;0x10
DECL|macro|ENAUTOATNO
mdefine_line|#define&t;&t;ENAUTOATNO      &t;0x08
DECL|macro|ENAUTOATNI
mdefine_line|#define&t;&t;ENAUTOATNI      &t;0x04
DECL|macro|ENAUTOATNP
mdefine_line|#define&t;&t;ENAUTOATNP      &t;0x02
DECL|macro|DATA_COUNT_ODD
mdefine_line|#define&t;DATA_COUNT_ODD  &t;&t;0x55
DECL|macro|INITIATOR_TAG
mdefine_line|#define&t;INITIATOR_TAG   &t;&t;0x56
DECL|macro|SEQ_FLAGS2
mdefine_line|#define&t;SEQ_FLAGS2      &t;&t;0x57
DECL|macro|SCB_DMA
mdefine_line|#define&t;&t;SCB_DMA         &t;0x01
DECL|macro|SCSICONF
mdefine_line|#define&t;SCSICONF        &t;&t;0x5a
DECL|macro|TERM_ENB
mdefine_line|#define&t;&t;TERM_ENB        &t;0x80
DECL|macro|RESET_SCSI
mdefine_line|#define&t;&t;RESET_SCSI      &t;0x40
DECL|macro|ENSPCHK
mdefine_line|#define&t;&t;ENSPCHK         &t;0x20
DECL|macro|HWSCSIID
mdefine_line|#define&t;&t;HWSCSIID        &t;0x0f
DECL|macro|HSCSIID
mdefine_line|#define&t;&t;HSCSIID         &t;0x07
DECL|macro|INTDEF
mdefine_line|#define&t;INTDEF          &t;&t;0x5c
DECL|macro|EDGE_TRIG
mdefine_line|#define&t;&t;EDGE_TRIG       &t;0x80
DECL|macro|VECTOR
mdefine_line|#define&t;&t;VECTOR          &t;0x0f
DECL|macro|HOSTCONF
mdefine_line|#define&t;HOSTCONF        &t;&t;0x5d
DECL|macro|HA_274_BIOSCTRL
mdefine_line|#define&t;HA_274_BIOSCTRL &t;&t;0x5f
DECL|macro|BIOSDISABLED
mdefine_line|#define&t;&t;BIOSDISABLED    &t;0x30
DECL|macro|BIOSMODE
mdefine_line|#define&t;&t;BIOSMODE        &t;0x30
DECL|macro|CHANNEL_B_PRIMARY
mdefine_line|#define&t;&t;CHANNEL_B_PRIMARY&t;0x08
DECL|macro|SEQCTL
mdefine_line|#define&t;SEQCTL          &t;&t;0x60
DECL|macro|PERRORDIS
mdefine_line|#define&t;&t;PERRORDIS       &t;0x80
DECL|macro|PAUSEDIS
mdefine_line|#define&t;&t;PAUSEDIS        &t;0x40
DECL|macro|FAILDIS
mdefine_line|#define&t;&t;FAILDIS         &t;0x20
DECL|macro|FASTMODE
mdefine_line|#define&t;&t;FASTMODE        &t;0x10
DECL|macro|BRKADRINTEN
mdefine_line|#define&t;&t;BRKADRINTEN     &t;0x08
DECL|macro|STEP
mdefine_line|#define&t;&t;STEP            &t;0x04
DECL|macro|SEQRESET
mdefine_line|#define&t;&t;SEQRESET        &t;0x02
DECL|macro|LOADRAM
mdefine_line|#define&t;&t;LOADRAM         &t;0x01
DECL|macro|SEQRAM
mdefine_line|#define&t;SEQRAM          &t;&t;0x61
DECL|macro|SEQADDR0
mdefine_line|#define&t;SEQADDR0        &t;&t;0x62
DECL|macro|SEQADDR1
mdefine_line|#define&t;SEQADDR1        &t;&t;0x63
DECL|macro|SEQADDR1_MASK
mdefine_line|#define&t;&t;SEQADDR1_MASK   &t;0x01
DECL|macro|ACCUM
mdefine_line|#define&t;ACCUM           &t;&t;0x64
DECL|macro|SINDEX
mdefine_line|#define&t;SINDEX          &t;&t;0x65
DECL|macro|DINDEX
mdefine_line|#define&t;DINDEX          &t;&t;0x66
DECL|macro|ALLONES
mdefine_line|#define&t;ALLONES         &t;&t;0x69
DECL|macro|ALLZEROS
mdefine_line|#define&t;ALLZEROS        &t;&t;0x6a
DECL|macro|NONE
mdefine_line|#define&t;NONE            &t;&t;0x6a
DECL|macro|FLAGS
mdefine_line|#define&t;FLAGS           &t;&t;0x6b
DECL|macro|ZERO
mdefine_line|#define&t;&t;ZERO            &t;0x02
DECL|macro|CARRY
mdefine_line|#define&t;&t;CARRY           &t;0x01
DECL|macro|SINDIR
mdefine_line|#define&t;SINDIR          &t;&t;0x6c
DECL|macro|DINDIR
mdefine_line|#define&t;DINDIR          &t;&t;0x6d
DECL|macro|FUNCTION1
mdefine_line|#define&t;FUNCTION1       &t;&t;0x6e
DECL|macro|STACK
mdefine_line|#define&t;STACK           &t;&t;0x6f
DECL|macro|TARG_OFFSET
mdefine_line|#define&t;TARG_OFFSET     &t;&t;0x70
DECL|macro|BCTL
mdefine_line|#define&t;BCTL            &t;&t;0x84
DECL|macro|ACE
mdefine_line|#define&t;&t;ACE             &t;0x08
DECL|macro|ENABLE
mdefine_line|#define&t;&t;ENABLE          &t;0x01
DECL|macro|DSCOMMAND0
mdefine_line|#define&t;DSCOMMAND0      &t;&t;0x84
DECL|macro|CACHETHEN
mdefine_line|#define&t;&t;CACHETHEN       &t;0x80
DECL|macro|DPARCKEN
mdefine_line|#define&t;&t;DPARCKEN        &t;0x40
DECL|macro|MPARCKEN
mdefine_line|#define&t;&t;MPARCKEN        &t;0x20
DECL|macro|EXTREQLCK
mdefine_line|#define&t;&t;EXTREQLCK       &t;0x10
DECL|macro|INTSCBRAMSEL
mdefine_line|#define&t;&t;INTSCBRAMSEL    &t;0x08
DECL|macro|RAMPS
mdefine_line|#define&t;&t;RAMPS           &t;0x04
DECL|macro|USCBSIZE32
mdefine_line|#define&t;&t;USCBSIZE32      &t;0x02
DECL|macro|CIOPARCKEN
mdefine_line|#define&t;&t;CIOPARCKEN      &t;0x01
DECL|macro|BUSTIME
mdefine_line|#define&t;BUSTIME         &t;&t;0x85
DECL|macro|BOFF
mdefine_line|#define&t;&t;BOFF            &t;0xf0
DECL|macro|BON
mdefine_line|#define&t;&t;BON             &t;0x0f
DECL|macro|DSCOMMAND1
mdefine_line|#define&t;DSCOMMAND1      &t;&t;0x85
DECL|macro|DSLATT
mdefine_line|#define&t;&t;DSLATT          &t;0xfc
DECL|macro|HADDLDSEL1
mdefine_line|#define&t;&t;HADDLDSEL1      &t;0x02
DECL|macro|HADDLDSEL0
mdefine_line|#define&t;&t;HADDLDSEL0      &t;0x01
DECL|macro|BUSSPD
mdefine_line|#define&t;BUSSPD          &t;&t;0x86
DECL|macro|DFTHRSH
mdefine_line|#define&t;&t;DFTHRSH         &t;0xc0
DECL|macro|DFTHRSH_75
mdefine_line|#define&t;&t;DFTHRSH_75      &t;0x80
DECL|macro|STBOFF
mdefine_line|#define&t;&t;STBOFF          &t;0x38
DECL|macro|STBON
mdefine_line|#define&t;&t;STBON           &t;0x07
DECL|macro|HS_MAILBOX
mdefine_line|#define&t;HS_MAILBOX      &t;&t;0x86
DECL|macro|HOST_MAILBOX
mdefine_line|#define&t;&t;HOST_MAILBOX    &t;0xf0
DECL|macro|HOST_TQINPOS
mdefine_line|#define&t;&t;HOST_TQINPOS    &t;0x80
DECL|macro|SEQ_MAILBOX
mdefine_line|#define&t;&t;SEQ_MAILBOX     &t;0x0f
DECL|macro|DSPCISTATUS
mdefine_line|#define&t;DSPCISTATUS     &t;&t;0x86
DECL|macro|DFTHRSH_100
mdefine_line|#define&t;&t;DFTHRSH_100     &t;0xc0
DECL|macro|HCNTRL
mdefine_line|#define&t;HCNTRL          &t;&t;0x87
DECL|macro|POWRDN
mdefine_line|#define&t;&t;POWRDN          &t;0x40
DECL|macro|SWINT
mdefine_line|#define&t;&t;SWINT           &t;0x10
DECL|macro|IRQMS
mdefine_line|#define&t;&t;IRQMS           &t;0x08
DECL|macro|PAUSE
mdefine_line|#define&t;&t;PAUSE           &t;0x04
DECL|macro|INTEN
mdefine_line|#define&t;&t;INTEN           &t;0x02
DECL|macro|CHIPRST
mdefine_line|#define&t;&t;CHIPRST         &t;0x01
DECL|macro|CHIPRSTACK
mdefine_line|#define&t;&t;CHIPRSTACK      &t;0x01
DECL|macro|HADDR
mdefine_line|#define&t;HADDR           &t;&t;0x88
DECL|macro|HCNT
mdefine_line|#define&t;HCNT            &t;&t;0x8c
DECL|macro|SCBPTR
mdefine_line|#define&t;SCBPTR          &t;&t;0x90
DECL|macro|INTSTAT
mdefine_line|#define&t;INTSTAT         &t;&t;0x91
DECL|macro|SEQINT_MASK
mdefine_line|#define&t;&t;SEQINT_MASK     &t;0xf1
DECL|macro|OUT_OF_RANGE
mdefine_line|#define&t;&t;OUT_OF_RANGE    &t;0xe1
DECL|macro|NO_FREE_SCB
mdefine_line|#define&t;&t;NO_FREE_SCB     &t;0xd1
DECL|macro|SCB_MISMATCH
mdefine_line|#define&t;&t;SCB_MISMATCH    &t;0xc1
DECL|macro|MISSED_BUSFREE
mdefine_line|#define&t;&t;MISSED_BUSFREE  &t;0xb1
DECL|macro|MKMSG_FAILED
mdefine_line|#define&t;&t;MKMSG_FAILED    &t;0xa1
DECL|macro|DATA_OVERRUN
mdefine_line|#define&t;&t;DATA_OVERRUN    &t;0x91
DECL|macro|PERR_DETECTED
mdefine_line|#define&t;&t;PERR_DETECTED   &t;0x81
DECL|macro|BAD_STATUS
mdefine_line|#define&t;&t;BAD_STATUS      &t;0x71
DECL|macro|HOST_MSG_LOOP
mdefine_line|#define&t;&t;HOST_MSG_LOOP   &t;0x61
DECL|macro|PDATA_REINIT
mdefine_line|#define&t;&t;PDATA_REINIT    &t;0x51
DECL|macro|IGN_WIDE_RES
mdefine_line|#define&t;&t;IGN_WIDE_RES    &t;0x41
DECL|macro|NO_MATCH
mdefine_line|#define&t;&t;NO_MATCH        &t;0x31
DECL|macro|NO_IDENT
mdefine_line|#define&t;&t;NO_IDENT        &t;0x21
DECL|macro|SEND_REJECT
mdefine_line|#define&t;&t;SEND_REJECT     &t;0x11
DECL|macro|INT_PEND
mdefine_line|#define&t;&t;INT_PEND        &t;0x0f
DECL|macro|BRKADRINT
mdefine_line|#define&t;&t;BRKADRINT       &t;0x08
DECL|macro|SCSIINT
mdefine_line|#define&t;&t;SCSIINT         &t;0x04
DECL|macro|CMDCMPLT
mdefine_line|#define&t;&t;CMDCMPLT        &t;0x02
DECL|macro|BAD_PHASE
mdefine_line|#define&t;&t;BAD_PHASE       &t;0x01
DECL|macro|SEQINT
mdefine_line|#define&t;&t;SEQINT          &t;0x01
DECL|macro|CLRINT
mdefine_line|#define&t;CLRINT          &t;&t;0x92
DECL|macro|CLRPARERR
mdefine_line|#define&t;&t;CLRPARERR       &t;0x10
DECL|macro|CLRBRKADRINT
mdefine_line|#define&t;&t;CLRBRKADRINT    &t;0x08
DECL|macro|CLRSCSIINT
mdefine_line|#define&t;&t;CLRSCSIINT      &t;0x04
DECL|macro|CLRCMDINT
mdefine_line|#define&t;&t;CLRCMDINT       &t;0x02
DECL|macro|CLRSEQINT
mdefine_line|#define&t;&t;CLRSEQINT       &t;0x01
DECL|macro|ERROR
mdefine_line|#define&t;ERROR           &t;&t;0x92
DECL|macro|CIOPARERR
mdefine_line|#define&t;&t;CIOPARERR       &t;0x80
DECL|macro|PCIERRSTAT
mdefine_line|#define&t;&t;PCIERRSTAT      &t;0x40
DECL|macro|MPARERR
mdefine_line|#define&t;&t;MPARERR         &t;0x20
DECL|macro|DPARERR
mdefine_line|#define&t;&t;DPARERR         &t;0x10
DECL|macro|SQPARERR
mdefine_line|#define&t;&t;SQPARERR        &t;0x08
DECL|macro|ILLOPCODE
mdefine_line|#define&t;&t;ILLOPCODE       &t;0x04
DECL|macro|ILLSADDR
mdefine_line|#define&t;&t;ILLSADDR        &t;0x02
DECL|macro|ILLHADDR
mdefine_line|#define&t;&t;ILLHADDR        &t;0x01
DECL|macro|DFCNTRL
mdefine_line|#define&t;DFCNTRL         &t;&t;0x93
DECL|macro|DFSTATUS
mdefine_line|#define&t;DFSTATUS        &t;&t;0x94
DECL|macro|PRELOAD_AVAIL
mdefine_line|#define&t;&t;PRELOAD_AVAIL   &t;0x80
DECL|macro|DFCACHETH
mdefine_line|#define&t;&t;DFCACHETH       &t;0x40
DECL|macro|FIFOQWDEMP
mdefine_line|#define&t;&t;FIFOQWDEMP      &t;0x20
DECL|macro|MREQPEND
mdefine_line|#define&t;&t;MREQPEND        &t;0x10
DECL|macro|HDONE
mdefine_line|#define&t;&t;HDONE           &t;0x08
DECL|macro|DFTHRESH
mdefine_line|#define&t;&t;DFTHRESH        &t;0x04
DECL|macro|FIFOFULL
mdefine_line|#define&t;&t;FIFOFULL        &t;0x02
DECL|macro|FIFOEMP
mdefine_line|#define&t;&t;FIFOEMP         &t;0x01
DECL|macro|DFWADDR
mdefine_line|#define&t;DFWADDR         &t;&t;0x95
DECL|macro|DFRADDR
mdefine_line|#define&t;DFRADDR         &t;&t;0x97
DECL|macro|DFDAT
mdefine_line|#define&t;DFDAT           &t;&t;0x99
DECL|macro|SCBCNT
mdefine_line|#define&t;SCBCNT          &t;&t;0x9a
DECL|macro|SCBAUTO
mdefine_line|#define&t;&t;SCBAUTO         &t;0x80
DECL|macro|SCBCNT_MASK
mdefine_line|#define&t;&t;SCBCNT_MASK     &t;0x1f
DECL|macro|QINFIFO
mdefine_line|#define&t;QINFIFO         &t;&t;0x9b
DECL|macro|QINCNT
mdefine_line|#define&t;QINCNT          &t;&t;0x9c
DECL|macro|QOUTFIFO
mdefine_line|#define&t;QOUTFIFO        &t;&t;0x9d
DECL|macro|CRCCONTROL1
mdefine_line|#define&t;CRCCONTROL1     &t;&t;0x9d
DECL|macro|CRCONSEEN
mdefine_line|#define&t;&t;CRCONSEEN       &t;0x80
DECL|macro|CRCVALCHKEN
mdefine_line|#define&t;&t;CRCVALCHKEN     &t;0x40
DECL|macro|CRCENDCHKEN
mdefine_line|#define&t;&t;CRCENDCHKEN     &t;0x20
DECL|macro|CRCREQCHKEN
mdefine_line|#define&t;&t;CRCREQCHKEN     &t;0x10
DECL|macro|TARGCRCENDEN
mdefine_line|#define&t;&t;TARGCRCENDEN    &t;0x08
DECL|macro|TARGCRCCNTEN
mdefine_line|#define&t;&t;TARGCRCCNTEN    &t;0x04
DECL|macro|QOUTCNT
mdefine_line|#define&t;QOUTCNT         &t;&t;0x9e
DECL|macro|SCSIPHASE
mdefine_line|#define&t;SCSIPHASE       &t;&t;0x9e
DECL|macro|STATUS_PHASE
mdefine_line|#define&t;&t;STATUS_PHASE    &t;0x20
DECL|macro|COMMAND_PHASE
mdefine_line|#define&t;&t;COMMAND_PHASE   &t;0x10
DECL|macro|MSG_IN_PHASE
mdefine_line|#define&t;&t;MSG_IN_PHASE    &t;0x08
DECL|macro|MSG_OUT_PHASE
mdefine_line|#define&t;&t;MSG_OUT_PHASE   &t;0x04
DECL|macro|DATA_PHASE_MASK
mdefine_line|#define&t;&t;DATA_PHASE_MASK &t;0x03
DECL|macro|DATA_IN_PHASE
mdefine_line|#define&t;&t;DATA_IN_PHASE   &t;0x02
DECL|macro|DATA_OUT_PHASE
mdefine_line|#define&t;&t;DATA_OUT_PHASE  &t;0x01
DECL|macro|SFUNCT
mdefine_line|#define&t;SFUNCT          &t;&t;0x9f
DECL|macro|ALT_MODE
mdefine_line|#define&t;&t;ALT_MODE        &t;0x80
DECL|macro|SCB_BASE
mdefine_line|#define&t;SCB_BASE        &t;&t;0xa0
DECL|macro|SCB_CDB_PTR
mdefine_line|#define&t;SCB_CDB_PTR     &t;&t;0xa0
DECL|macro|SCB_RESIDUAL_DATACNT
mdefine_line|#define&t;SCB_RESIDUAL_DATACNT&t;&t;0xa0
DECL|macro|SCB_CDB_STORE
mdefine_line|#define&t;SCB_CDB_STORE   &t;&t;0xa0
DECL|macro|SCB_TARGET_INFO
mdefine_line|#define&t;SCB_TARGET_INFO &t;&t;0xa0
DECL|macro|SCB_RESIDUAL_SGPTR
mdefine_line|#define&t;SCB_RESIDUAL_SGPTR&t;&t;0xa4
DECL|macro|SCB_SCSI_STATUS
mdefine_line|#define&t;SCB_SCSI_STATUS &t;&t;0xa8
DECL|macro|SCB_CDB_STORE_PAD
mdefine_line|#define&t;SCB_CDB_STORE_PAD&t;&t;0xa9
DECL|macro|SCB_DATAPTR
mdefine_line|#define&t;SCB_DATAPTR     &t;&t;0xac
DECL|macro|SCB_DATACNT
mdefine_line|#define&t;SCB_DATACNT     &t;&t;0xb0
DECL|macro|SG_LAST_SEG
mdefine_line|#define&t;&t;SG_LAST_SEG     &t;0x80
DECL|macro|SG_HIGH_ADDR_BITS
mdefine_line|#define&t;&t;SG_HIGH_ADDR_BITS&t;0x7f
DECL|macro|SCB_SGPTR
mdefine_line|#define&t;SCB_SGPTR       &t;&t;0xb4
DECL|macro|SG_RESID_VALID
mdefine_line|#define&t;&t;SG_RESID_VALID  &t;0x04
DECL|macro|SG_FULL_RESID
mdefine_line|#define&t;&t;SG_FULL_RESID   &t;0x02
DECL|macro|SG_LIST_NULL
mdefine_line|#define&t;&t;SG_LIST_NULL    &t;0x01
DECL|macro|SCB_CONTROL
mdefine_line|#define&t;SCB_CONTROL     &t;&t;0xb8
DECL|macro|TARGET_SCB
mdefine_line|#define&t;&t;TARGET_SCB      &t;0x80
DECL|macro|DISCENB
mdefine_line|#define&t;&t;DISCENB         &t;0x40
DECL|macro|TAG_ENB
mdefine_line|#define&t;&t;TAG_ENB         &t;0x20
DECL|macro|MK_MESSAGE
mdefine_line|#define&t;&t;MK_MESSAGE      &t;0x10
DECL|macro|ULTRAENB
mdefine_line|#define&t;&t;ULTRAENB        &t;0x08
DECL|macro|DISCONNECTED
mdefine_line|#define&t;&t;DISCONNECTED    &t;0x04
DECL|macro|SCB_TAG_TYPE
mdefine_line|#define&t;&t;SCB_TAG_TYPE    &t;0x03
DECL|macro|SCB_SCSIID
mdefine_line|#define&t;SCB_SCSIID      &t;&t;0xb9
DECL|macro|TID
mdefine_line|#define&t;&t;TID             &t;0xf0
DECL|macro|TWIN_CHNLB
mdefine_line|#define&t;&t;TWIN_CHNLB      &t;0x80
DECL|macro|TWIN_TID
mdefine_line|#define&t;&t;TWIN_TID        &t;0x70
DECL|macro|OID
mdefine_line|#define&t;&t;OID             &t;0x0f
DECL|macro|SCB_LUN
mdefine_line|#define&t;SCB_LUN         &t;&t;0xba
DECL|macro|LID
mdefine_line|#define&t;&t;LID             &t;0xff
DECL|macro|SCB_TAG
mdefine_line|#define&t;SCB_TAG         &t;&t;0xbb
DECL|macro|SCB_CDB_LEN
mdefine_line|#define&t;SCB_CDB_LEN     &t;&t;0xbc
DECL|macro|SCB_SCSIRATE
mdefine_line|#define&t;SCB_SCSIRATE    &t;&t;0xbd
DECL|macro|SCB_SCSIOFFSET
mdefine_line|#define&t;SCB_SCSIOFFSET  &t;&t;0xbe
DECL|macro|SCB_NEXT
mdefine_line|#define&t;SCB_NEXT        &t;&t;0xbf
DECL|macro|SCB_64_SPARE
mdefine_line|#define&t;SCB_64_SPARE    &t;&t;0xc0
DECL|macro|SEECTL_2840
mdefine_line|#define&t;SEECTL_2840     &t;&t;0xc0
DECL|macro|CS_2840
mdefine_line|#define&t;&t;CS_2840         &t;0x04
DECL|macro|CK_2840
mdefine_line|#define&t;&t;CK_2840         &t;0x02
DECL|macro|DO_2840
mdefine_line|#define&t;&t;DO_2840         &t;0x01
DECL|macro|STATUS_2840
mdefine_line|#define&t;STATUS_2840     &t;&t;0xc1
DECL|macro|EEPROM_TF
mdefine_line|#define&t;&t;EEPROM_TF       &t;0x80
DECL|macro|BIOS_SEL
mdefine_line|#define&t;&t;BIOS_SEL        &t;0x60
DECL|macro|ADSEL
mdefine_line|#define&t;&t;ADSEL           &t;0x1e
DECL|macro|DI_2840
mdefine_line|#define&t;&t;DI_2840         &t;0x01
DECL|macro|SCB_64_BTT
mdefine_line|#define&t;SCB_64_BTT      &t;&t;0xd0
DECL|macro|CCHADDR
mdefine_line|#define&t;CCHADDR         &t;&t;0xe0
DECL|macro|CCHCNT
mdefine_line|#define&t;CCHCNT          &t;&t;0xe8
DECL|macro|CCSGRAM
mdefine_line|#define&t;CCSGRAM         &t;&t;0xe9
DECL|macro|CCSGADDR
mdefine_line|#define&t;CCSGADDR        &t;&t;0xea
DECL|macro|CCSGCTL
mdefine_line|#define&t;CCSGCTL         &t;&t;0xeb
DECL|macro|CCSGDONE
mdefine_line|#define&t;&t;CCSGDONE        &t;0x80
DECL|macro|CCSGEN
mdefine_line|#define&t;&t;CCSGEN          &t;0x08
DECL|macro|SG_FETCH_NEEDED
mdefine_line|#define&t;&t;SG_FETCH_NEEDED &t;0x02
DECL|macro|CCSGRESET
mdefine_line|#define&t;&t;CCSGRESET       &t;0x01
DECL|macro|CCSCBRAM
mdefine_line|#define&t;CCSCBRAM        &t;&t;0xec
DECL|macro|CCSCBADDR
mdefine_line|#define&t;CCSCBADDR       &t;&t;0xed
DECL|macro|CCSCBCTL
mdefine_line|#define&t;CCSCBCTL        &t;&t;0xee
DECL|macro|CCSCBDONE
mdefine_line|#define&t;&t;CCSCBDONE       &t;0x80
DECL|macro|ARRDONE
mdefine_line|#define&t;&t;ARRDONE         &t;0x40
DECL|macro|CCARREN
mdefine_line|#define&t;&t;CCARREN         &t;0x10
DECL|macro|CCSCBEN
mdefine_line|#define&t;&t;CCSCBEN         &t;0x08
DECL|macro|CCSCBDIR
mdefine_line|#define&t;&t;CCSCBDIR        &t;0x04
DECL|macro|CCSCBRESET
mdefine_line|#define&t;&t;CCSCBRESET      &t;0x01
DECL|macro|CCSCBCNT
mdefine_line|#define&t;CCSCBCNT        &t;&t;0xef
DECL|macro|SCBBADDR
mdefine_line|#define&t;SCBBADDR        &t;&t;0xf0
DECL|macro|CCSCBPTR
mdefine_line|#define&t;CCSCBPTR        &t;&t;0xf1
DECL|macro|HNSCB_QOFF
mdefine_line|#define&t;HNSCB_QOFF      &t;&t;0xf4
DECL|macro|SNSCB_QOFF
mdefine_line|#define&t;SNSCB_QOFF      &t;&t;0xf6
DECL|macro|SDSCB_QOFF
mdefine_line|#define&t;SDSCB_QOFF      &t;&t;0xf8
DECL|macro|QOFF_CTLSTA
mdefine_line|#define&t;QOFF_CTLSTA     &t;&t;0xfa
DECL|macro|SCB_AVAIL
mdefine_line|#define&t;&t;SCB_AVAIL       &t;0x40
DECL|macro|SNSCB_ROLLOVER
mdefine_line|#define&t;&t;SNSCB_ROLLOVER  &t;0x20
DECL|macro|SDSCB_ROLLOVER
mdefine_line|#define&t;&t;SDSCB_ROLLOVER  &t;0x10
DECL|macro|SCB_QSIZE
mdefine_line|#define&t;&t;SCB_QSIZE       &t;0x07
DECL|macro|SCB_QSIZE_256
mdefine_line|#define&t;&t;SCB_QSIZE_256   &t;0x06
DECL|macro|DFF_THRSH
mdefine_line|#define&t;DFF_THRSH       &t;&t;0xfb
DECL|macro|WR_DFTHRSH
mdefine_line|#define&t;&t;WR_DFTHRSH      &t;0x70
DECL|macro|WR_DFTHRSH_MAX
mdefine_line|#define&t;&t;WR_DFTHRSH_MAX  &t;0x70
DECL|macro|WR_DFTHRSH_90
mdefine_line|#define&t;&t;WR_DFTHRSH_90   &t;0x60
DECL|macro|WR_DFTHRSH_85
mdefine_line|#define&t;&t;WR_DFTHRSH_85   &t;0x50
DECL|macro|WR_DFTHRSH_75
mdefine_line|#define&t;&t;WR_DFTHRSH_75   &t;0x40
DECL|macro|WR_DFTHRSH_63
mdefine_line|#define&t;&t;WR_DFTHRSH_63   &t;0x30
DECL|macro|WR_DFTHRSH_50
mdefine_line|#define&t;&t;WR_DFTHRSH_50   &t;0x20
DECL|macro|WR_DFTHRSH_25
mdefine_line|#define&t;&t;WR_DFTHRSH_25   &t;0x10
DECL|macro|RD_DFTHRSH
mdefine_line|#define&t;&t;RD_DFTHRSH      &t;0x07
DECL|macro|RD_DFTHRSH_MAX
mdefine_line|#define&t;&t;RD_DFTHRSH_MAX  &t;0x07
DECL|macro|RD_DFTHRSH_90
mdefine_line|#define&t;&t;RD_DFTHRSH_90   &t;0x06
DECL|macro|RD_DFTHRSH_85
mdefine_line|#define&t;&t;RD_DFTHRSH_85   &t;0x05
DECL|macro|RD_DFTHRSH_75
mdefine_line|#define&t;&t;RD_DFTHRSH_75   &t;0x04
DECL|macro|RD_DFTHRSH_63
mdefine_line|#define&t;&t;RD_DFTHRSH_63   &t;0x03
DECL|macro|RD_DFTHRSH_50
mdefine_line|#define&t;&t;RD_DFTHRSH_50   &t;0x02
DECL|macro|RD_DFTHRSH_25
mdefine_line|#define&t;&t;RD_DFTHRSH_25   &t;0x01
DECL|macro|RD_DFTHRSH_MIN
mdefine_line|#define&t;&t;RD_DFTHRSH_MIN  &t;0x00
DECL|macro|WR_DFTHRSH_MIN
mdefine_line|#define&t;&t;WR_DFTHRSH_MIN  &t;0x00
DECL|macro|SG_CACHE_SHADOW
mdefine_line|#define&t;SG_CACHE_SHADOW &t;&t;0xfc
DECL|macro|SG_ADDR_MASK
mdefine_line|#define&t;&t;SG_ADDR_MASK    &t;0xf8
DECL|macro|ODD_SEG
mdefine_line|#define&t;&t;ODD_SEG         &t;0x04
DECL|macro|LAST_SEG
mdefine_line|#define&t;&t;LAST_SEG        &t;0x02
DECL|macro|LAST_SEG_DONE
mdefine_line|#define&t;&t;LAST_SEG_DONE   &t;0x01
DECL|macro|SG_CACHE_PRE
mdefine_line|#define&t;SG_CACHE_PRE    &t;&t;0xfc
DECL|macro|SCB_INITIATOR_TAG
mdefine_line|#define&t;SCB_INITIATOR_TAG&t;0x03
DECL|macro|SCB_TARGET_DATA_DIR
mdefine_line|#define&t;SCB_TARGET_DATA_DIR&t;0x01
DECL|macro|SCB_TARGET_PHASES
mdefine_line|#define&t;SCB_TARGET_PHASES&t;0x00
DECL|macro|MAX_OFFSET_ULTRA2
mdefine_line|#define&t;MAX_OFFSET_ULTRA2&t;0x7f
DECL|macro|MAX_OFFSET_16BIT
mdefine_line|#define&t;MAX_OFFSET_16BIT&t;0x08
DECL|macro|BUS_8_BIT
mdefine_line|#define&t;BUS_8_BIT&t;0x00
DECL|macro|TARGET_CMD_CMPLT
mdefine_line|#define&t;TARGET_CMD_CMPLT&t;0xfe
DECL|macro|STATUS_QUEUE_FULL
mdefine_line|#define&t;STATUS_QUEUE_FULL&t;0x28
DECL|macro|STATUS_BUSY
mdefine_line|#define&t;STATUS_BUSY&t;0x08
DECL|macro|MAX_OFFSET_8BIT
mdefine_line|#define&t;MAX_OFFSET_8BIT&t;0x0f
DECL|macro|BUS_32_BIT
mdefine_line|#define&t;BUS_32_BIT&t;0x02
DECL|macro|CCSGADDR_MAX
mdefine_line|#define&t;CCSGADDR_MAX&t;0x80
DECL|macro|TID_SHIFT
mdefine_line|#define&t;TID_SHIFT&t;0x04
DECL|macro|SCB_DOWNLOAD_SIZE_64
mdefine_line|#define&t;SCB_DOWNLOAD_SIZE_64&t;0x30
DECL|macro|HOST_MAILBOX_SHIFT
mdefine_line|#define&t;HOST_MAILBOX_SHIFT&t;0x04
DECL|macro|SCB_TARGET_STATUS
mdefine_line|#define&t;SCB_TARGET_STATUS&t;0x02
DECL|macro|CMD_GROUP_CODE_SHIFT
mdefine_line|#define&t;CMD_GROUP_CODE_SHIFT&t;0x05
DECL|macro|CCSGRAM_MAXSEGS
mdefine_line|#define&t;CCSGRAM_MAXSEGS&t;0x10
DECL|macro|SCB_LIST_NULL
mdefine_line|#define&t;SCB_LIST_NULL&t;0xff
DECL|macro|SG_SIZEOF
mdefine_line|#define&t;SG_SIZEOF&t;0x08
DECL|macro|SCB_DOWNLOAD_SIZE
mdefine_line|#define&t;SCB_DOWNLOAD_SIZE&t;0x20
DECL|macro|SEQ_MAILBOX_SHIFT
mdefine_line|#define&t;SEQ_MAILBOX_SHIFT&t;0x00
DECL|macro|TARGET_DATA_IN
mdefine_line|#define&t;TARGET_DATA_IN&t;0x01
DECL|macro|HOST_MSG
mdefine_line|#define&t;HOST_MSG&t;0xff
DECL|macro|BUS_16_BIT
mdefine_line|#define&t;BUS_16_BIT&t;0x01
DECL|macro|SCB_UPLOAD_SIZE
mdefine_line|#define&t;SCB_UPLOAD_SIZE&t;0x20
multiline_comment|/* Downloaded Constant Definitions */
DECL|macro|INVERTED_CACHESIZE_MASK
mdefine_line|#define&t;INVERTED_CACHESIZE_MASK&t;0x03
DECL|macro|SG_PREFETCH_ADDR_MASK
mdefine_line|#define&t;SG_PREFETCH_ADDR_MASK&t;0x06
DECL|macro|SG_PREFETCH_ALIGN_MASK
mdefine_line|#define&t;SG_PREFETCH_ALIGN_MASK&t;0x05
DECL|macro|QOUTFIFO_OFFSET
mdefine_line|#define&t;QOUTFIFO_OFFSET&t;0x00
DECL|macro|SG_PREFETCH_CNT
mdefine_line|#define&t;SG_PREFETCH_CNT&t;0x04
DECL|macro|CACHESIZE_MASK
mdefine_line|#define&t;CACHESIZE_MASK&t;0x02
DECL|macro|QINFIFO_OFFSET
mdefine_line|#define&t;QINFIFO_OFFSET&t;0x01
eof
