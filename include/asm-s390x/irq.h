macro_line|#ifndef _ASM_IRQ_H
DECL|macro|_ASM_IRQ_H
mdefine_line|#define _ASM_IRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/hardirq.h&gt;
multiline_comment|/*&n; * How many IRQ&squot;s for S390 ?!?&n; */
DECL|macro|__MAX_SUBCHANNELS
mdefine_line|#define __MAX_SUBCHANNELS 65536
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS           __MAX_SUBCHANNELS
DECL|macro|NR_CHPIDS
mdefine_line|#define NR_CHPIDS 256
DECL|macro|LPM_ANYPATH
mdefine_line|#define LPM_ANYPATH 0xff /* doesn&squot;t really belong here, Ingo? */
DECL|macro|INVALID_STORAGE_AREA
mdefine_line|#define INVALID_STORAGE_AREA ((void *)(-1 - 0x3FFF ))
multiline_comment|/*&n; * path management control word&n; */
r_typedef
r_struct
(brace
DECL|member|intparm
id|__u32
id|intparm
suffix:semicolon
multiline_comment|/* interruption parameter */
DECL|member|qf
id|__u32
id|qf
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* qdio facility */
DECL|member|res0
id|__u32
id|res0
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved zeros */
DECL|member|isc
id|__u32
id|isc
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* interruption sublass */
DECL|member|res5
id|__u32
id|res5
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* reserved zeros */
DECL|member|ena
id|__u32
id|ena
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* enabled */
DECL|member|lm
id|__u32
id|lm
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* limit mode */
DECL|member|mme
id|__u32
id|mme
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* measurement-mode enable */
DECL|member|mp
id|__u32
id|mp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* multipath mode */
DECL|member|tf
id|__u32
id|tf
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* timing facility */
DECL|member|dnv
id|__u32
id|dnv
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* device number valid */
DECL|member|dev
id|__u32
id|dev
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* device number */
DECL|member|lpm
id|__u8
id|lpm
suffix:semicolon
multiline_comment|/* logical path mask */
DECL|member|pnom
id|__u8
id|pnom
suffix:semicolon
multiline_comment|/* path not operational mask */
DECL|member|lpum
id|__u8
id|lpum
suffix:semicolon
multiline_comment|/* last path used mask */
DECL|member|pim
id|__u8
id|pim
suffix:semicolon
multiline_comment|/* path installed mask */
DECL|member|mbi
id|__u16
id|mbi
suffix:semicolon
multiline_comment|/* measurement-block index */
DECL|member|pom
id|__u8
id|pom
suffix:semicolon
multiline_comment|/* path operational mask */
DECL|member|pam
id|__u8
id|pam
suffix:semicolon
multiline_comment|/* path available mask */
DECL|member|chpid
id|__u8
id|chpid
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* CHPID 0-7 (if available) */
DECL|member|unused1
id|__u32
id|unused1
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* reserved zeros */
DECL|member|st
id|__u32
id|st
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* subchannel type */
DECL|member|unused2
id|__u32
id|unused2
suffix:colon
l_int|20
suffix:semicolon
multiline_comment|/* reserved zeros */
DECL|member|csense
id|__u32
id|csense
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* concurrent sense; can be enabled ...*/
multiline_comment|/*  ... per MSCH, however, if facility */
multiline_comment|/*  ... is not installed, this results */
multiline_comment|/*  ... in an operand exception.       */
DECL|typedef|pmcw_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|pmcw_t
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * subchannel status word&n; */
r_typedef
r_struct
(brace
DECL|member|key
id|__u32
id|key
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* subchannel key */
DECL|member|sctl
id|__u32
id|sctl
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* suspend control */
DECL|member|eswf
id|__u32
id|eswf
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* ESW format */
DECL|member|cc
id|__u32
id|cc
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* deferred condition code */
DECL|member|fmt
id|__u32
id|fmt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* format */
DECL|member|pfch
id|__u32
id|pfch
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* prefetch */
DECL|member|isic
id|__u32
id|isic
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* initial-status interruption control */
DECL|member|alcc
id|__u32
id|alcc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* address-limit checking control */
DECL|member|ssi
id|__u32
id|ssi
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* supress-suspended interruption */
DECL|member|zcc
id|__u32
id|zcc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* zero condition code */
DECL|member|ectl
id|__u32
id|ectl
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* extended control */
DECL|member|pno
id|__u32
id|pno
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* path not operational */
DECL|member|res
id|__u32
id|res
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|fctl
id|__u32
id|fctl
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* function control */
DECL|member|actl
id|__u32
id|actl
suffix:colon
l_int|7
suffix:semicolon
multiline_comment|/* activity control */
DECL|member|stctl
id|__u32
id|stctl
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* status control */
DECL|member|cpa
id|__u32
id|cpa
suffix:semicolon
multiline_comment|/* channel program address */
DECL|member|dstat
id|__u32
id|dstat
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* device status */
DECL|member|cstat
id|__u32
id|cstat
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* subchannel status */
DECL|member|count
id|__u32
id|count
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* residual count */
DECL|typedef|scsw_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|scsw_t
suffix:semicolon
DECL|macro|SCSW_FCTL_CLEAR_FUNC
mdefine_line|#define SCSW_FCTL_CLEAR_FUNC     0x1
DECL|macro|SCSW_FCTL_HALT_FUNC
mdefine_line|#define SCSW_FCTL_HALT_FUNC      0x2
DECL|macro|SCSW_FCTL_START_FUNC
mdefine_line|#define SCSW_FCTL_START_FUNC     0x4
DECL|macro|SCSW_ACTL_SUSPENDED
mdefine_line|#define SCSW_ACTL_SUSPENDED      0x1
DECL|macro|SCSW_ACTL_DEVACT
mdefine_line|#define SCSW_ACTL_DEVACT         0x2
DECL|macro|SCSW_ACTL_SCHACT
mdefine_line|#define SCSW_ACTL_SCHACT         0x4
DECL|macro|SCSW_ACTL_CLEAR_PEND
mdefine_line|#define SCSW_ACTL_CLEAR_PEND     0x8
DECL|macro|SCSW_ACTL_HALT_PEND
mdefine_line|#define SCSW_ACTL_HALT_PEND      0x10
DECL|macro|SCSW_ACTL_START_PEND
mdefine_line|#define SCSW_ACTL_START_PEND     0x20
DECL|macro|SCSW_ACTL_RESUME_PEND
mdefine_line|#define SCSW_ACTL_RESUME_PEND    0x40
DECL|macro|SCSW_STCTL_STATUS_PEND
mdefine_line|#define SCSW_STCTL_STATUS_PEND   0x1
DECL|macro|SCSW_STCTL_SEC_STATUS
mdefine_line|#define SCSW_STCTL_SEC_STATUS    0x2
DECL|macro|SCSW_STCTL_PRIM_STATUS
mdefine_line|#define SCSW_STCTL_PRIM_STATUS   0x4
DECL|macro|SCSW_STCTL_INTER_STATUS
mdefine_line|#define SCSW_STCTL_INTER_STATUS  0x8
DECL|macro|SCSW_STCTL_ALERT_STATUS
mdefine_line|#define SCSW_STCTL_ALERT_STATUS  0x10
DECL|macro|DEV_STAT_ATTENTION
mdefine_line|#define DEV_STAT_ATTENTION       0x80
DECL|macro|DEV_STAT_STAT_MOD
mdefine_line|#define DEV_STAT_STAT_MOD        0x40
DECL|macro|DEV_STAT_CU_END
mdefine_line|#define DEV_STAT_CU_END          0x20
DECL|macro|DEV_STAT_BUSY
mdefine_line|#define DEV_STAT_BUSY            0x10
DECL|macro|DEV_STAT_CHN_END
mdefine_line|#define DEV_STAT_CHN_END         0x08
DECL|macro|DEV_STAT_DEV_END
mdefine_line|#define DEV_STAT_DEV_END         0x04
DECL|macro|DEV_STAT_UNIT_CHECK
mdefine_line|#define DEV_STAT_UNIT_CHECK      0x02
DECL|macro|DEV_STAT_UNIT_EXCEP
mdefine_line|#define DEV_STAT_UNIT_EXCEP      0x01
DECL|macro|SCHN_STAT_PCI
mdefine_line|#define SCHN_STAT_PCI            0x80
DECL|macro|SCHN_STAT_INCORR_LEN
mdefine_line|#define SCHN_STAT_INCORR_LEN     0x40
DECL|macro|SCHN_STAT_PROG_CHECK
mdefine_line|#define SCHN_STAT_PROG_CHECK     0x20
DECL|macro|SCHN_STAT_PROT_CHECK
mdefine_line|#define SCHN_STAT_PROT_CHECK     0x10
DECL|macro|SCHN_STAT_CHN_DATA_CHK
mdefine_line|#define SCHN_STAT_CHN_DATA_CHK   0x08
DECL|macro|SCHN_STAT_CHN_CTRL_CHK
mdefine_line|#define SCHN_STAT_CHN_CTRL_CHK   0x04
DECL|macro|SCHN_STAT_INTF_CTRL_CHK
mdefine_line|#define SCHN_STAT_INTF_CTRL_CHK  0x02
DECL|macro|SCHN_STAT_CHAIN_CHECK
mdefine_line|#define SCHN_STAT_CHAIN_CHECK    0x01
multiline_comment|/*&n; * architectured values for first sense byte&n; */
DECL|macro|SNS0_CMD_REJECT
mdefine_line|#define SNS0_CMD_REJECT         0x80
DECL|macro|SNS_CMD_REJECT
mdefine_line|#define SNS_CMD_REJECT          SNS0_CMD_REJECT
DECL|macro|SNS0_INTERVENTION_REQ
mdefine_line|#define SNS0_INTERVENTION_REQ   0x40
DECL|macro|SNS0_BUS_OUT_CHECK
mdefine_line|#define SNS0_BUS_OUT_CHECK      0x20
DECL|macro|SNS0_EQUIPMENT_CHECK
mdefine_line|#define SNS0_EQUIPMENT_CHECK    0x10
DECL|macro|SNS0_DATA_CHECK
mdefine_line|#define SNS0_DATA_CHECK         0x08
DECL|macro|SNS0_OVERRUN
mdefine_line|#define SNS0_OVERRUN            0x04
multiline_comment|/*                              0x02 reserved */
DECL|macro|SNS0_INCOMPL_DOMAIN
mdefine_line|#define SNS0_INCOMPL_DOMAIN     0x01
multiline_comment|/*&n; * architectured values for second sense byte&n; */
DECL|macro|SNS1_PERM_ERR
mdefine_line|#define SNS1_PERM_ERR           0x80
DECL|macro|SNS1_INV_TRACK_FORMAT
mdefine_line|#define SNS1_INV_TRACK_FORMAT   0x40
DECL|macro|SNS1_EOC
mdefine_line|#define SNS1_EOC                0x20
DECL|macro|SNS1_MESSAGE_TO_OPER
mdefine_line|#define SNS1_MESSAGE_TO_OPER    0x10
DECL|macro|SNS1_NO_REC_FOUND
mdefine_line|#define SNS1_NO_REC_FOUND       0x08
DECL|macro|SNS1_FILE_PROTECTED
mdefine_line|#define SNS1_FILE_PROTECTED     0x04
DECL|macro|SNS1_WRITE_INHIBITED
mdefine_line|#define SNS1_WRITE_INHIBITED    0x02
DECL|macro|SNS1_INPRECISE_END
mdefine_line|#define SNS1_INPRECISE_END      0x01
multiline_comment|/*&n; * architectured values for third sense byte&n; */
DECL|macro|SNS2_REQ_INH_WRITE
mdefine_line|#define SNS2_REQ_INH_WRITE      0x80
DECL|macro|SNS2_CORRECTABLE
mdefine_line|#define SNS2_CORRECTABLE        0x40
DECL|macro|SNS2_FIRST_LOG_ERR
mdefine_line|#define SNS2_FIRST_LOG_ERR      0x20
DECL|macro|SNS2_ENV_DATA_PRESENT
mdefine_line|#define SNS2_ENV_DATA_PRESENT   0x10
multiline_comment|/*                              0x08 reserved */
DECL|macro|SNS2_INPRECISE_END
mdefine_line|#define SNS2_INPRECISE_END      0x04
multiline_comment|/*                              0x02 reserved */
multiline_comment|/*                              0x01 reserved */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * subchannel information block&n; */
r_typedef
r_struct
(brace
DECL|member|pmcw
id|pmcw_t
id|pmcw
suffix:semicolon
multiline_comment|/* path management control word */
DECL|member|scsw
id|scsw_t
id|scsw
suffix:semicolon
multiline_comment|/* subchannel status word */
DECL|member|mda
id|__u8
id|mda
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* model dependent area */
DECL|typedef|schib_t
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|4
)paren
)paren
)paren
id|schib_t
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
r_typedef
r_struct
(brace
DECL|member|cmd_code
id|__u8
id|cmd_code
suffix:semicolon
multiline_comment|/* command code */
DECL|member|flags
id|__u8
id|flags
suffix:semicolon
multiline_comment|/* flags, like IDA adressing, etc. */
DECL|member|count
id|__u16
id|count
suffix:semicolon
multiline_comment|/* byte count */
DECL|member|cda
id|__u32
id|cda
suffix:semicolon
multiline_comment|/* data address */
DECL|typedef|ccw1_t
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
id|ccw1_t
suffix:semicolon
DECL|macro|CCW_FLAG_DC
mdefine_line|#define CCW_FLAG_DC             0x80
DECL|macro|CCW_FLAG_CC
mdefine_line|#define CCW_FLAG_CC             0x40
DECL|macro|CCW_FLAG_SLI
mdefine_line|#define CCW_FLAG_SLI            0x20
DECL|macro|CCW_FLAG_SKIP
mdefine_line|#define CCW_FLAG_SKIP           0x10
DECL|macro|CCW_FLAG_PCI
mdefine_line|#define CCW_FLAG_PCI            0x08
DECL|macro|CCW_FLAG_IDA
mdefine_line|#define CCW_FLAG_IDA            0x04
DECL|macro|CCW_FLAG_SUSPEND
mdefine_line|#define CCW_FLAG_SUSPEND        0x02
DECL|macro|CCW_CMD_READ_IPL
mdefine_line|#define CCW_CMD_READ_IPL        0x02
DECL|macro|CCW_CMD_NOOP
mdefine_line|#define CCW_CMD_NOOP            0x03
DECL|macro|CCW_CMD_BASIC_SENSE
mdefine_line|#define CCW_CMD_BASIC_SENSE     0x04
DECL|macro|CCW_CMD_TIC
mdefine_line|#define CCW_CMD_TIC             0x08
DECL|macro|CCW_CMD_SENSE_PGID
mdefine_line|#define CCW_CMD_SENSE_PGID      0x34
DECL|macro|CCW_CMD_SUSPEND_RECONN
mdefine_line|#define CCW_CMD_SUSPEND_RECONN  0x5B
DECL|macro|CCW_CMD_RDC
mdefine_line|#define CCW_CMD_RDC             0x64
DECL|macro|CCW_CMD_SET_PGID
mdefine_line|#define CCW_CMD_SET_PGID        0xAF
DECL|macro|CCW_CMD_SENSE_ID
mdefine_line|#define CCW_CMD_SENSE_ID        0xE4
DECL|macro|CCW_CMD_DCTL
mdefine_line|#define CCW_CMD_DCTL            0xF3
macro_line|#ifdef __KERNEL__
DECL|macro|SENSE_MAX_COUNT
mdefine_line|#define SENSE_MAX_COUNT         0x20
multiline_comment|/*&n; * architectured values for first sense byte&n; */
DECL|macro|SNS0_CMD_REJECT
mdefine_line|#define SNS0_CMD_REJECT         0x80
DECL|macro|SNS_CMD_REJECT
mdefine_line|#define SNS_CMD_REJECT          SNS0_CMD_REJECT
DECL|macro|SNS0_INTERVENTION_REQ
mdefine_line|#define SNS0_INTERVENTION_REQ   0x40
DECL|macro|SNS0_BUS_OUT_CHECK
mdefine_line|#define SNS0_BUS_OUT_CHECK      0x20
DECL|macro|SNS0_EQUIPMENT_CHECK
mdefine_line|#define SNS0_EQUIPMENT_CHECK    0x10
DECL|macro|SNS0_DATA_CHECK
mdefine_line|#define SNS0_DATA_CHECK         0x08
DECL|macro|SNS0_OVERRUN
mdefine_line|#define SNS0_OVERRUN            0x04
multiline_comment|/*&n; * operation request block&n; */
r_typedef
r_struct
(brace
DECL|member|intparm
id|__u32
id|intparm
suffix:semicolon
multiline_comment|/* interruption parameter */
DECL|member|key
id|__u32
id|key
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* flags, like key, suspend control, etc. */
DECL|member|spnd
id|__u32
id|spnd
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* suspend control */
DECL|member|res1
id|__u32
id|res1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|mod
id|__u32
id|mod
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* modification control */
DECL|member|sync
id|__u32
id|sync
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* synchronize control */
DECL|member|fmt
id|__u32
id|fmt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* format control */
DECL|member|pfch
id|__u32
id|pfch
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* prefetch control */
DECL|member|isic
id|__u32
id|isic
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* initial-status-interruption control */
DECL|member|alcc
id|__u32
id|alcc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* address-limit-checking control */
DECL|member|ssic
id|__u32
id|ssic
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* suppress-suspended-interr. control */
DECL|member|res2
id|__u32
id|res2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|c64
id|__u32
id|c64
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* IDAW/QDIO 64 bit control  */
DECL|member|i2k
id|__u32
id|i2k
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* IDAW 2/4kB block size control */
DECL|member|lpm
id|__u32
id|lpm
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* logical path mask */
DECL|member|ils
id|__u32
id|ils
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* incorrect length */
DECL|member|zero
id|__u32
id|zero
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* reserved zeros */
DECL|member|orbx
id|__u32
id|orbx
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* ORB extension control */
DECL|member|cpa
id|__u32
id|cpa
suffix:semicolon
multiline_comment|/* channel program address */
DECL|typedef|orb_t
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|4
)paren
)paren
)paren
id|orb_t
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
r_typedef
r_struct
(brace
DECL|member|res0
id|__u32
id|res0
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|pvrf
id|__u32
id|pvrf
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* path-verification-required flag */
DECL|member|cpt
id|__u32
id|cpt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* channel-path timeout */
DECL|member|fsavf
id|__u32
id|fsavf
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Failing storage address validity flag */
DECL|member|cons
id|__u32
id|cons
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* concurrent-sense */
DECL|member|res8
id|__u32
id|res8
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|scnt
id|__u32
id|scnt
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* sense count if cons == 1 */
DECL|member|res16
id|__u32
id|res16
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* reserved */
DECL|typedef|erw_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|erw_t
suffix:semicolon
multiline_comment|/*&n; * subchannel logout area&n; */
r_typedef
r_struct
(brace
DECL|member|res0
id|__u32
id|res0
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|esf
id|__u32
id|esf
suffix:colon
l_int|7
suffix:semicolon
multiline_comment|/* extended status flags */
DECL|member|lpum
id|__u32
id|lpum
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* last path used mask */
DECL|member|res16
id|__u32
id|res16
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|fvf
id|__u32
id|fvf
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* field-validity flags */
DECL|member|sacc
id|__u32
id|sacc
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* storage access code */
DECL|member|termc
id|__u32
id|termc
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* termination code */
DECL|member|devsc
id|__u32
id|devsc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* device-status check */
DECL|member|serr
id|__u32
id|serr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* secondary error */
DECL|member|ioerr
id|__u32
id|ioerr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* i/o-error alert */
DECL|member|seqc
id|__u32
id|seqc
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* sequence code */
DECL|typedef|sublog_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|sublog_t
suffix:semicolon
multiline_comment|/*&n; * Format 0 Extended Status Word (ESW)&n; */
r_typedef
r_struct
(brace
DECL|member|sublog
id|sublog_t
id|sublog
suffix:semicolon
multiline_comment|/* subchannel logout */
DECL|member|erw
id|erw_t
id|erw
suffix:semicolon
multiline_comment|/* extended report word */
DECL|member|faddr
id|__u32
id|faddr
suffix:semicolon
multiline_comment|/* failing address */
DECL|member|zeros
id|__u32
id|zeros
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 2 fullwords of zeros */
DECL|typedef|esw0_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|esw0_t
suffix:semicolon
multiline_comment|/*&n; * Format 1 Extended Status Word (ESW)&n; */
r_typedef
r_struct
(brace
DECL|member|zero0
id|__u8
id|zero0
suffix:semicolon
multiline_comment|/* reserved zeros */
DECL|member|lpum
id|__u8
id|lpum
suffix:semicolon
multiline_comment|/* last path used mask */
DECL|member|zero16
id|__u16
id|zero16
suffix:semicolon
multiline_comment|/* reserved zeros */
DECL|member|erw
id|erw_t
id|erw
suffix:semicolon
multiline_comment|/* extended report word */
DECL|member|zeros
id|__u32
id|zeros
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* 2 fullwords of zeros */
DECL|typedef|esw1_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|esw1_t
suffix:semicolon
multiline_comment|/*&n; * Format 2 Extended Status Word (ESW)&n; */
r_typedef
r_struct
(brace
DECL|member|zero0
id|__u8
id|zero0
suffix:semicolon
multiline_comment|/* reserved zeros */
DECL|member|lpum
id|__u8
id|lpum
suffix:semicolon
multiline_comment|/* last path used mask */
DECL|member|dcti
id|__u16
id|dcti
suffix:semicolon
multiline_comment|/* device-connect-time interval */
DECL|member|erw
id|erw_t
id|erw
suffix:semicolon
multiline_comment|/* extended report word */
DECL|member|zeros
id|__u32
id|zeros
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* 2 fullwords of zeros */
DECL|typedef|esw2_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|esw2_t
suffix:semicolon
multiline_comment|/*&n; * Format 3 Extended Status Word (ESW)&n; */
r_typedef
r_struct
(brace
DECL|member|zero0
id|__u8
id|zero0
suffix:semicolon
multiline_comment|/* reserved zeros */
DECL|member|lpum
id|__u8
id|lpum
suffix:semicolon
multiline_comment|/* last path used mask */
DECL|member|res
id|__u16
id|res
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|erw
id|erw_t
id|erw
suffix:semicolon
multiline_comment|/* extended report word */
DECL|member|zeros
id|__u32
id|zeros
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* 2 fullwords of zeros */
DECL|typedef|esw3_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|esw3_t
suffix:semicolon
r_typedef
r_union
(brace
DECL|member|esw0
id|esw0_t
id|esw0
suffix:semicolon
DECL|member|esw1
id|esw1_t
id|esw1
suffix:semicolon
DECL|member|esw2
id|esw2_t
id|esw2
suffix:semicolon
DECL|member|esw3
id|esw3_t
id|esw3
suffix:semicolon
DECL|typedef|esw_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|esw_t
suffix:semicolon
multiline_comment|/*&n; * interruption response block&n; */
r_typedef
r_struct
(brace
DECL|member|scsw
id|scsw_t
id|scsw
suffix:semicolon
multiline_comment|/* subchannel status word */
DECL|member|esw
id|esw_t
id|esw
suffix:semicolon
multiline_comment|/* extended status word */
DECL|member|ecw
id|__u8
id|ecw
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* extended control word */
DECL|typedef|irb_t
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|4
)paren
)paren
)paren
id|irb_t
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * TPI info structure&n; */
r_typedef
r_struct
(brace
DECL|member|reserved1
id|__u32
id|reserved1
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* reserved 0x00000001 */
DECL|member|irq
id|__u32
id|irq
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* aka. subchannel number */
DECL|member|intparm
id|__u32
id|intparm
suffix:semicolon
multiline_comment|/* interruption parameter */
DECL|member|adapter_IO
id|__u32
id|adapter_IO
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2
id|__u32
id|reserved2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|isc
id|__u32
id|isc
suffix:colon
l_int|3
suffix:semicolon
DECL|member|reserved3
id|__u32
id|reserved3
suffix:colon
l_int|12
suffix:semicolon
DECL|member|int_type
id|__u32
id|int_type
suffix:colon
l_int|3
suffix:semicolon
DECL|member|reserved4
id|__u32
id|reserved4
suffix:colon
l_int|12
suffix:semicolon
DECL|typedef|tpi_info_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|tpi_info_t
suffix:semicolon
singleline_comment|//
singleline_comment|// command information word  (CIW) layout
singleline_comment|//
DECL|struct|_ciw
r_typedef
r_struct
id|_ciw
(brace
DECL|member|et
id|__u32
id|et
suffix:colon
l_int|2
suffix:semicolon
singleline_comment|// entry type
DECL|member|reserved
id|__u32
id|reserved
suffix:colon
l_int|2
suffix:semicolon
singleline_comment|// reserved
DECL|member|ct
id|__u32
id|ct
suffix:colon
l_int|4
suffix:semicolon
singleline_comment|// command type
DECL|member|cmd
id|__u32
id|cmd
suffix:colon
l_int|8
suffix:semicolon
singleline_comment|// command
DECL|member|count
id|__u32
id|count
suffix:colon
l_int|16
suffix:semicolon
singleline_comment|// count
DECL|typedef|ciw_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|ciw_t
suffix:semicolon
DECL|macro|CIW_TYPE_RCD
mdefine_line|#define CIW_TYPE_RCD    0x0    
singleline_comment|// read configuration data
DECL|macro|CIW_TYPE_SII
mdefine_line|#define CIW_TYPE_SII    0x1    
singleline_comment|// set interface identifier
DECL|macro|CIW_TYPE_RNI
mdefine_line|#define CIW_TYPE_RNI    0x2    
singleline_comment|// read node identifier
DECL|macro|MAX_CIWS
mdefine_line|#define MAX_CIWS 8
singleline_comment|//
singleline_comment|// sense-id response buffer layout
singleline_comment|//
r_typedef
r_struct
(brace
multiline_comment|/* common part */
DECL|member|reserved
id|__u8
id|reserved
suffix:semicolon
multiline_comment|/* always 0x&squot;FF&squot; */
DECL|member|cu_type
id|__u16
id|cu_type
suffix:semicolon
multiline_comment|/* control unit type */
DECL|member|cu_model
id|__u8
id|cu_model
suffix:semicolon
multiline_comment|/* control unit model */
DECL|member|dev_type
id|__u16
id|dev_type
suffix:semicolon
multiline_comment|/* device type */
DECL|member|dev_model
id|__u8
id|dev_model
suffix:semicolon
multiline_comment|/* device model */
DECL|member|unused
id|__u8
id|unused
suffix:semicolon
multiline_comment|/* padding byte */
multiline_comment|/* extended part */
DECL|member|ciw
id|ciw_t
id|ciw
(braket
id|MAX_CIWS
)braket
suffix:semicolon
multiline_comment|/* variable # of CIWs */
DECL|typedef|senseid_t
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|4
)paren
)paren
)paren
id|senseid_t
suffix:semicolon
multiline_comment|/*&n; * where we put the ssd info&n; */
DECL|struct|_ssd_info
r_typedef
r_struct
id|_ssd_info
(brace
DECL|member|valid
id|__u8
id|valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|type
id|__u8
id|type
suffix:colon
l_int|7
suffix:semicolon
multiline_comment|/* subchannel type */
DECL|member|chpid
id|__u8
id|chpid
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* chpids */
DECL|member|fla
id|__u16
id|fla
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* full link addresses */
DECL|typedef|ssd_info_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|ssd_info_t
suffix:semicolon
multiline_comment|/*&n; * area for store event information&n; */
DECL|struct|chsc_area_t
r_typedef
r_struct
id|chsc_area_t
(brace
r_struct
(brace
multiline_comment|/* word 0 */
DECL|member|command_code1
id|__u16
id|command_code1
suffix:semicolon
DECL|member|command_code2
id|__u16
id|command_code2
suffix:semicolon
r_union
(brace
r_struct
(brace
multiline_comment|/* word 1 */
DECL|member|reserved1
id|__u32
id|reserved1
suffix:semicolon
multiline_comment|/* word 2 */
DECL|member|reserved2
id|__u32
id|reserved2
suffix:semicolon
DECL|member|sei_req
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
id|sei_req
suffix:semicolon
r_struct
(brace
multiline_comment|/* word 1 */
DECL|member|reserved1
id|__u16
id|reserved1
suffix:semicolon
DECL|member|f_sch
id|__u16
id|f_sch
suffix:semicolon
multiline_comment|/* first subchannel */
multiline_comment|/* word 2 */
DECL|member|reserved2
id|__u16
id|reserved2
suffix:semicolon
DECL|member|l_sch
id|__u16
id|l_sch
suffix:semicolon
multiline_comment|/* last subchannel */
DECL|member|ssd_req
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
id|ssd_req
suffix:semicolon
DECL|member|request_block_data
)brace
id|request_block_data
suffix:semicolon
multiline_comment|/* word 3 */
DECL|member|reserved3
id|__u32
id|reserved3
suffix:semicolon
DECL|member|request_block
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
id|request_block
suffix:semicolon
r_struct
(brace
multiline_comment|/* word 0 */
DECL|member|length
id|__u16
id|length
suffix:semicolon
DECL|member|response_code
id|__u16
id|response_code
suffix:semicolon
multiline_comment|/* word 1 */
DECL|member|reserved1
id|__u32
id|reserved1
suffix:semicolon
r_union
(brace
r_struct
(brace
multiline_comment|/* word 2 */
DECL|member|flags
id|__u8
id|flags
suffix:semicolon
DECL|member|vf
id|__u8
id|vf
suffix:semicolon
multiline_comment|/* validity flags */
DECL|member|rs
id|__u8
id|rs
suffix:semicolon
multiline_comment|/* reporting source */
DECL|member|cc
id|__u8
id|cc
suffix:semicolon
multiline_comment|/* content code */
multiline_comment|/* word 3 */
DECL|member|fla
id|__u16
id|fla
suffix:semicolon
multiline_comment|/* full link address */
DECL|member|rsid
id|__u16
id|rsid
suffix:semicolon
multiline_comment|/* reporting source id */
multiline_comment|/* word 4 */
DECL|member|reserved2
id|__u32
id|reserved2
suffix:semicolon
multiline_comment|/* word 5 */
DECL|member|reserved3
id|__u32
id|reserved3
suffix:semicolon
multiline_comment|/* word 6 */
DECL|member|ccdf
id|__u32
id|ccdf
suffix:semicolon
multiline_comment|/* content-code dependent field */
multiline_comment|/* word 7 */
DECL|member|reserved4
id|__u32
id|reserved4
suffix:semicolon
multiline_comment|/* word 8 */
DECL|member|reserved5
id|__u32
id|reserved5
suffix:semicolon
multiline_comment|/* word 9 */
DECL|member|reserved6
id|__u32
id|reserved6
suffix:semicolon
DECL|member|sei_res
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
id|sei_res
suffix:semicolon
r_struct
(brace
multiline_comment|/* word 2 */
DECL|member|sch_valid
id|__u8
id|sch_valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dev_valid
id|__u8
id|dev_valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|st
id|__u8
id|st
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* subchannel type */
DECL|member|zeroes
id|__u8
id|zeroes
suffix:colon
l_int|3
suffix:semicolon
DECL|member|unit_addr
id|__u8
id|unit_addr
suffix:semicolon
multiline_comment|/* unit address */
DECL|member|devno
id|__u16
id|devno
suffix:semicolon
multiline_comment|/* device number */
multiline_comment|/* word 3 */
DECL|member|path_mask
id|__u8
id|path_mask
suffix:semicolon
DECL|member|fla_valid_mask
id|__u8
id|fla_valid_mask
suffix:semicolon
DECL|member|sch
id|__u16
id|sch
suffix:semicolon
multiline_comment|/* subchannel */
multiline_comment|/* words 4-5 */
DECL|member|chpid
id|__u8
id|chpid
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* chpids 0-7 */
multiline_comment|/* words 6-9 */
DECL|member|fla
id|__u16
id|fla
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* full link addresses 0-7 */
DECL|member|ssd_res
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
id|ssd_res
suffix:semicolon
DECL|member|response_block_data
)brace
id|response_block_data
suffix:semicolon
DECL|member|response_block
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
id|response_block
suffix:semicolon
DECL|typedef|chsc_area_t
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
id|PAGE_SIZE
)paren
)paren
)paren
id|chsc_area_t
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * sense data&n; */
r_typedef
r_struct
(brace
DECL|member|res
id|__u8
id|res
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* reserved   */
DECL|member|data
id|__u8
id|data
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* sense data */
DECL|typedef|sense_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|sense_t
suffix:semicolon
multiline_comment|/*&n; * device status area, to be provided by the device driver&n; *  when calling request_irq() as parameter &quot;dev_id&quot;, later&n; *  tied to the &quot;action&quot; control block.&n; *&n; * Note : No data area must be added after union ii or the&n; *         effective devstat size calculation will fail !&n; */
r_typedef
r_struct
(brace
DECL|member|devno
id|__u16
id|devno
suffix:semicolon
multiline_comment|/* device number, aka. &quot;cuu&quot; from irb */
DECL|member|intparm
r_int
r_int
id|intparm
suffix:semicolon
multiline_comment|/* interrupt parameter */
DECL|member|cstat
id|__u8
id|cstat
suffix:semicolon
multiline_comment|/* channel status - accumulated */
DECL|member|dstat
id|__u8
id|dstat
suffix:semicolon
multiline_comment|/* device status - accumulated */
DECL|member|lpum
id|__u8
id|lpum
suffix:semicolon
multiline_comment|/* last path used mask from irb */
DECL|member|unused
id|__u8
id|unused
suffix:semicolon
multiline_comment|/* not used - reserved */
DECL|member|flag
r_int
r_int
id|flag
suffix:semicolon
multiline_comment|/* flag : see below */
DECL|member|cpa
id|__u32
id|cpa
suffix:semicolon
multiline_comment|/* CCW address from irb at primary status */
DECL|member|rescnt
id|__u32
id|rescnt
suffix:semicolon
multiline_comment|/* res. count from irb at primary status */
DECL|member|scnt
id|__u32
id|scnt
suffix:semicolon
multiline_comment|/* sense count, if DEVSTAT_FLAG_SENSE_AVAIL */
r_union
(brace
DECL|member|irb
id|irb_t
id|irb
suffix:semicolon
multiline_comment|/* interruption response block */
DECL|member|sense
id|sense_t
id|sense
suffix:semicolon
multiline_comment|/* sense information */
DECL|member|ii
)brace
id|ii
suffix:semicolon
multiline_comment|/* interrupt information */
DECL|typedef|devstat_t
)brace
id|devstat_t
suffix:semicolon
DECL|macro|DEVSTAT_FLAG_SENSE_AVAIL
mdefine_line|#define DEVSTAT_FLAG_SENSE_AVAIL   0x00000001
DECL|macro|DEVSTAT_NOT_OPER
mdefine_line|#define DEVSTAT_NOT_OPER           0x00000002
DECL|macro|DEVSTAT_START_FUNCTION
mdefine_line|#define DEVSTAT_START_FUNCTION     0x00000004
DECL|macro|DEVSTAT_HALT_FUNCTION
mdefine_line|#define DEVSTAT_HALT_FUNCTION      0x00000008
DECL|macro|DEVSTAT_STATUS_PENDING
mdefine_line|#define DEVSTAT_STATUS_PENDING     0x00000010
DECL|macro|DEVSTAT_REVALIDATE
mdefine_line|#define DEVSTAT_REVALIDATE         0x00000020
DECL|macro|DEVSTAT_DEVICE_GONE
mdefine_line|#define DEVSTAT_DEVICE_GONE        0x00000040
DECL|macro|DEVSTAT_DEVICE_OWNED
mdefine_line|#define DEVSTAT_DEVICE_OWNED       0x00000080
DECL|macro|DEVSTAT_CLEAR_FUNCTION
mdefine_line|#define DEVSTAT_CLEAR_FUNCTION     0x00000100
DECL|macro|DEVSTAT_PCI
mdefine_line|#define DEVSTAT_PCI                0x00000200
DECL|macro|DEVSTAT_SUSPENDED
mdefine_line|#define DEVSTAT_SUSPENDED          0x00000400
DECL|macro|DEVSTAT_UNKNOWN_DEV
mdefine_line|#define DEVSTAT_UNKNOWN_DEV        0x00000800
DECL|macro|DEVSTAT_FINAL_STATUS
mdefine_line|#define DEVSTAT_FINAL_STATUS       0x80000000
DECL|macro|DEVINFO_NOT_OPER
mdefine_line|#define DEVINFO_NOT_OPER           DEVSTAT_NOT_OPER
DECL|macro|DEVINFO_UNKNOWN_DEV
mdefine_line|#define DEVINFO_UNKNOWN_DEV        DEVSTAT_UNKNOWN_DEV
DECL|macro|DEVINFO_DEVICE_OWNED
mdefine_line|#define DEVINFO_DEVICE_OWNED       DEVSTAT_DEVICE_OWNED
DECL|macro|DEVINFO_QDIO_CAPABLE
mdefine_line|#define DEVINFO_QDIO_CAPABLE       0x40000000
DECL|macro|INTPARM_STATUS_PENDING
mdefine_line|#define INTPARM_STATUS_PENDING     0xFFFFFFFF
macro_line|#ifdef __KERNEL__
DECL|macro|IO_INTERRUPT_TYPE
mdefine_line|#define IO_INTERRUPT_TYPE          0 /* I/O interrupt type */
DECL|typedef|io_handler_func1_t
r_typedef
r_void
(paren
op_star
id|io_handler_func1_t
)paren
(paren
r_int
id|irq
comma
id|devstat_t
op_star
id|devstat
comma
r_struct
id|pt_regs
op_star
id|rgs
)paren
suffix:semicolon
DECL|typedef|io_handler_func_t
r_typedef
r_void
(paren
op_star
id|io_handler_func_t
)paren
(paren
r_int
id|irq
comma
r_void
op_star
id|devstat
comma
r_struct
id|pt_regs
op_star
id|rgs
)paren
suffix:semicolon
DECL|typedef|not_oper_handler_func_t
r_typedef
r_void
(paren
op_star
id|not_oper_handler_func_t
)paren
(paren
r_int
id|irq
comma
r_int
id|status
)paren
suffix:semicolon
DECL|typedef|adapter_int_handler_t
r_typedef
r_int
(paren
op_star
id|adapter_int_handler_t
)paren
(paren
id|__u32
id|intparm
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|handler
id|io_handler_func_t
id|handler
suffix:semicolon
multiline_comment|/* interrupt handler routine */
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* device name */
DECL|member|dev_id
id|devstat_t
op_star
id|dev_id
suffix:semicolon
multiline_comment|/* device status block */
DECL|typedef|irq_desc_t
)brace
id|irq_desc_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|state1
id|__u8
id|state1
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* path state value 1 */
DECL|member|state2
id|__u8
id|state2
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* path state value 2 */
DECL|member|state3
id|__u8
id|state3
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* path state value 3 */
DECL|member|resvd
id|__u8
id|resvd
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* reserved */
DECL|typedef|path_state_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|path_state_t
suffix:semicolon
r_typedef
r_struct
(brace
r_union
(brace
DECL|member|fc
id|__u8
id|fc
suffix:semicolon
multiline_comment|/* SPID function code */
DECL|member|ps
id|path_state_t
id|ps
suffix:semicolon
multiline_comment|/* SNID path state */
DECL|member|inf
)brace
id|inf
suffix:semicolon
DECL|member|cpu_addr
id|__u32
id|cpu_addr
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* CPU address */
DECL|member|cpu_id
id|__u32
id|cpu_id
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* CPU identification */
DECL|member|cpu_model
id|__u32
id|cpu_model
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* CPU model */
DECL|member|tod_high
id|__u32
id|tod_high
suffix:semicolon
multiline_comment|/* high word TOD clock */
DECL|typedef|pgid_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|pgid_t
suffix:semicolon
DECL|macro|SPID_FUNC_SINGLE_PATH
mdefine_line|#define SPID_FUNC_SINGLE_PATH      0x00
DECL|macro|SPID_FUNC_MULTI_PATH
mdefine_line|#define SPID_FUNC_MULTI_PATH       0x80
DECL|macro|SPID_FUNC_ESTABLISH
mdefine_line|#define SPID_FUNC_ESTABLISH        0x00
DECL|macro|SPID_FUNC_RESIGN
mdefine_line|#define SPID_FUNC_RESIGN           0x40
DECL|macro|SPID_FUNC_DISBAND
mdefine_line|#define SPID_FUNC_DISBAND          0x20
DECL|macro|SNID_STATE1_RESET
mdefine_line|#define SNID_STATE1_RESET          0
DECL|macro|SNID_STATE1_UNGROUPED
mdefine_line|#define SNID_STATE1_UNGROUPED      2
DECL|macro|SNID_STATE1_GROUPED
mdefine_line|#define SNID_STATE1_GROUPED        3
DECL|macro|SNID_STATE2_NOT_RESVD
mdefine_line|#define SNID_STATE2_NOT_RESVD      0
DECL|macro|SNID_STATE2_RESVD_ELSE
mdefine_line|#define SNID_STATE2_RESVD_ELSE     2
DECL|macro|SNID_STATE2_RESVD_SELF
mdefine_line|#define SNID_STATE2_RESVD_SELF     3
DECL|macro|SNID_STATE3_MULTI_PATH
mdefine_line|#define SNID_STATE3_MULTI_PATH     1
DECL|macro|SNID_STATE3_SINGLE_PATH
mdefine_line|#define SNID_STATE3_SINGLE_PATH    0
multiline_comment|/*&n; * Flags used as input parameters for do_IO()&n; */
DECL|macro|DOIO_EARLY_NOTIFICATION
mdefine_line|#define DOIO_EARLY_NOTIFICATION  0x0001 /* allow for I/O completion ... */
multiline_comment|/* ... notification after ... */
multiline_comment|/* ... primary interrupt status */
DECL|macro|DOIO_RETURN_CHAN_END
mdefine_line|#define DOIO_RETURN_CHAN_END     DOIO_EARLY_NOTIFICATION
DECL|macro|DOIO_VALID_LPM
mdefine_line|#define DOIO_VALID_LPM           0x0002 /* LPM input parameter is valid */
DECL|macro|DOIO_WAIT_FOR_INTERRUPT
mdefine_line|#define DOIO_WAIT_FOR_INTERRUPT  0x0004 /* wait synchronously for interrupt */
DECL|macro|DOIO_REPORT_ALL
mdefine_line|#define DOIO_REPORT_ALL          0x0008 /* report all interrupt conditions */
DECL|macro|DOIO_ALLOW_SUSPEND
mdefine_line|#define DOIO_ALLOW_SUSPEND       0x0010 /* allow for channel prog. suspend */
DECL|macro|DOIO_DENY_PREFETCH
mdefine_line|#define DOIO_DENY_PREFETCH       0x0020 /* don&squot;t allow for CCW prefetch */
DECL|macro|DOIO_SUPPRESS_INTER
mdefine_line|#define DOIO_SUPPRESS_INTER      0x0040 /* suppress intermediate inter. */
multiline_comment|/* ... for suspended CCWs */
DECL|macro|DOIO_TIMEOUT
mdefine_line|#define DOIO_TIMEOUT             0x0080 /* 3 secs. timeout for sync. I/O */
DECL|macro|DOIO_DONT_CALL_INTHDLR
mdefine_line|#define DOIO_DONT_CALL_INTHDLR   0x0100 /* don&squot;t call interrupt handler */
DECL|macro|DOIO_CANCEL_ON_TIMEOUT
mdefine_line|#define DOIO_CANCEL_ON_TIMEOUT   0x0200 /* cancel I/O if it timed out */
multiline_comment|/*&n; * do_IO()&n; *&n; *  Start a S/390 channel program. When the interrupt arrives, the&n; *  IRQ handler is called, either immediately, delayed (dev-end missing,&n; *  or sense required) or never (no IRQ handler registered -&n; *  should never occur, as the IRQ (subchannel ID) should be&n; *  disabled if no handler is present. Depending on the action&n; *  taken, do_IO() returns :  0      - Success&n; *                           -EIO    - Status pending&n; *                                        see : action-&gt;dev_id-&gt;cstat&n; *                                              action-&gt;dev_id-&gt;dstat&n; *                           -EBUSY  - Device busy&n; *                           -ENODEV - Device not operational&n; */
r_int
id|do_IO
c_func
(paren
r_int
id|irq
comma
multiline_comment|/* IRQ aka. subchannel number */
id|ccw1_t
op_star
id|cpa
comma
multiline_comment|/* logical channel program address */
r_int
r_int
id|intparm
comma
multiline_comment|/* interruption parameter */
id|__u8
id|lpm
comma
multiline_comment|/* logical path mask */
r_int
r_int
id|flag
)paren
suffix:semicolon
multiline_comment|/* flags : see above */
r_void
id|do_crw_pending
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* CRW handler */
r_int
id|resume_IO
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
multiline_comment|/* IRQ aka. subchannel number */
r_int
id|halt_IO
c_func
(paren
r_int
id|irq
comma
multiline_comment|/* IRQ aka. subchannel number */
r_int
r_int
id|intparm
comma
multiline_comment|/* dummy intparm */
r_int
r_int
id|flag
)paren
suffix:semicolon
multiline_comment|/* possible DOIO_WAIT_FOR_INTERRUPT */
r_int
id|clear_IO
c_func
(paren
r_int
id|irq
comma
multiline_comment|/* IRQ aka. subchannel number */
r_int
r_int
id|intparm
comma
multiline_comment|/* dummy intparm */
r_int
r_int
id|flag
)paren
suffix:semicolon
multiline_comment|/* possible DOIO_WAIT_FOR_INTERRUPT */
r_typedef
r_struct
(brace
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* irq, aka. subchannel */
DECL|member|devno
id|__u16
id|devno
suffix:semicolon
multiline_comment|/* device number */
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
multiline_comment|/* device status */
DECL|member|sid_data
id|senseid_t
id|sid_data
suffix:semicolon
multiline_comment|/* senseID data */
DECL|typedef|s390_dev_info_t
)brace
id|s390_dev_info_t
suffix:semicolon
r_int
id|get_dev_info_by_irq
(paren
r_int
id|irq
comma
id|s390_dev_info_t
op_star
id|pdi
)paren
suffix:semicolon
r_int
id|get_dev_info_by_devno
c_func
(paren
id|__u16
id|devno
comma
id|s390_dev_info_t
op_star
id|pdi
)paren
suffix:semicolon
r_int
id|get_irq_by_devno
c_func
(paren
id|__u16
id|devno
)paren
suffix:semicolon
r_int
r_int
id|get_devno_by_irq
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_int
id|get_irq_first
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|get_irq_next
(paren
r_int
id|irq
)paren
suffix:semicolon
r_int
id|read_dev_chars
c_func
(paren
r_int
id|irq
comma
r_void
op_star
op_star
id|buffer
comma
r_int
id|length
)paren
suffix:semicolon
r_int
id|read_conf_data
c_func
(paren
r_int
id|irq
comma
r_void
op_star
op_star
id|buffer
comma
r_int
op_star
id|length
comma
id|__u8
id|lpm
)paren
suffix:semicolon
r_int
id|s390_request_irq_special
c_func
(paren
r_int
id|irq
comma
id|io_handler_func_t
id|io_handler
comma
id|not_oper_handler_func_t
id|not_oper_handler
comma
r_int
r_int
id|irqflags
comma
r_const
r_char
op_star
id|devname
comma
r_void
op_star
id|dev_id
)paren
suffix:semicolon
r_extern
r_int
id|set_cons_dev
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_int
id|wait_cons_dev
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_extern
id|schib_t
op_star
id|s390_get_schib
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_int
id|s390_register_adapter_interrupt
c_func
(paren
id|adapter_int_handler_t
id|handler
)paren
suffix:semicolon
r_extern
r_int
id|s390_unregister_adapter_interrupt
c_func
(paren
id|adapter_int_handler_t
id|handler
)paren
suffix:semicolon
multiline_comment|/*&n; * Some S390 specific IO instructions as inline&n; */
DECL|function|stsch
r_extern
id|__inline__
r_int
id|stsch
c_func
(paren
r_int
id|irq
comma
r_volatile
id|schib_t
op_star
id|addr
)paren
(brace
r_int
id|ccode
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   lr    1,%1&bslash;n&quot;
l_string|&quot;   stsch 0(%2)&bslash;n&quot;
l_string|&quot;   ipm   %0&bslash;n&quot;
l_string|&quot;   srl   %0,28&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|ccode
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|irq
op_or
l_int|0x10000
)paren
comma
l_string|&quot;a&quot;
(paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
r_return
id|ccode
suffix:semicolon
)brace
DECL|function|msch
r_extern
id|__inline__
r_int
id|msch
c_func
(paren
r_int
id|irq
comma
r_volatile
id|schib_t
op_star
id|addr
)paren
(brace
r_int
id|ccode
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   lr    1,%1&bslash;n&quot;
l_string|&quot;   msch  0(%2)&bslash;n&quot;
l_string|&quot;   ipm   %0&bslash;n&quot;
l_string|&quot;   srl   %0,28&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|ccode
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|irq
op_or
l_int|0x10000L
)paren
comma
l_string|&quot;a&quot;
(paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
r_return
id|ccode
suffix:semicolon
)brace
DECL|function|msch_err
r_extern
id|__inline__
r_int
id|msch_err
c_func
(paren
r_int
id|irq
comma
r_volatile
id|schib_t
op_star
id|addr
)paren
(brace
r_int
id|ccode
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;    lr   1,%1&bslash;n&quot;
l_string|&quot;    msch 0(%2)&bslash;n&quot;
l_string|&quot;0:  ipm  %0&bslash;n&quot;
l_string|&quot;    srl  %0,28&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
macro_line|#ifdef CONFIG_ARCH_S390X
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2:  l    %0,%3&bslash;n&quot;
l_string|&quot;    jg   1b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 8&bslash;n&quot;
l_string|&quot;   .quad 0b,2b&bslash;n&quot;
l_string|&quot;.previous&quot;
macro_line|#else
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2:  l    %0,%3&bslash;n&quot;
l_string|&quot;    bras 1,3f&bslash;n&quot;
l_string|&quot;    .long 1b&bslash;n&quot;
l_string|&quot;3:  l    1,0(1)&bslash;n&quot;
l_string|&quot;    br   1&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long 0b,2b&bslash;n&quot;
l_string|&quot;.previous&quot;
macro_line|#endif
suffix:colon
l_string|&quot;=d&quot;
(paren
id|ccode
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|irq
op_or
l_int|0x10000L
)paren
comma
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|__LC_PGM_ILC
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
r_return
id|ccode
suffix:semicolon
)brace
DECL|function|tsch
r_extern
id|__inline__
r_int
id|tsch
c_func
(paren
r_int
id|irq
comma
r_volatile
id|irb_t
op_star
id|addr
)paren
(brace
r_int
id|ccode
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   lr    1,%1&bslash;n&quot;
l_string|&quot;   tsch  0(%2)&bslash;n&quot;
l_string|&quot;   ipm   %0&bslash;n&quot;
l_string|&quot;   srl   %0,28&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|ccode
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|irq
op_or
l_int|0x10000L
)paren
comma
l_string|&quot;a&quot;
(paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
r_return
id|ccode
suffix:semicolon
)brace
DECL|function|tpi
r_extern
id|__inline__
r_int
id|tpi
c_func
(paren
r_volatile
id|tpi_info_t
op_star
id|addr
)paren
(brace
r_int
id|ccode
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   tpi   0(%1)&bslash;n&quot;
l_string|&quot;   ipm   %0&bslash;n&quot;
l_string|&quot;   srl   %0,28&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|ccode
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
r_return
id|ccode
suffix:semicolon
)brace
DECL|function|ssch
r_extern
id|__inline__
r_int
id|ssch
c_func
(paren
r_int
id|irq
comma
r_volatile
id|orb_t
op_star
id|addr
)paren
(brace
r_int
id|ccode
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   lr    1,%1&bslash;n&quot;
l_string|&quot;   ssch  0(%2)&bslash;n&quot;
l_string|&quot;   ipm   %0&bslash;n&quot;
l_string|&quot;   srl   %0,28&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|ccode
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|irq
op_or
l_int|0x10000L
)paren
comma
l_string|&quot;a&quot;
(paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
r_return
id|ccode
suffix:semicolon
)brace
DECL|function|rsch
r_extern
id|__inline__
r_int
id|rsch
c_func
(paren
r_int
id|irq
)paren
(brace
r_int
id|ccode
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   lr    1,%1&bslash;n&quot;
l_string|&quot;   rsch&bslash;n&quot;
l_string|&quot;   ipm   %0&bslash;n&quot;
l_string|&quot;   srl   %0,28&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|ccode
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|irq
op_or
l_int|0x10000L
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
r_return
id|ccode
suffix:semicolon
)brace
DECL|function|csch
r_extern
id|__inline__
r_int
id|csch
c_func
(paren
r_int
id|irq
)paren
(brace
r_int
id|ccode
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   lr    1,%1&bslash;n&quot;
l_string|&quot;   csch&bslash;n&quot;
l_string|&quot;   ipm   %0&bslash;n&quot;
l_string|&quot;   srl   %0,28&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|ccode
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|irq
op_or
l_int|0x10000L
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
r_return
id|ccode
suffix:semicolon
)brace
DECL|function|hsch
r_extern
id|__inline__
r_int
id|hsch
c_func
(paren
r_int
id|irq
)paren
(brace
r_int
id|ccode
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   lr    1,%1&bslash;n&quot;
l_string|&quot;   hsch&bslash;n&quot;
l_string|&quot;   ipm   %0&bslash;n&quot;
l_string|&quot;   srl   %0,28&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|ccode
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|irq
op_or
l_int|0x10000L
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
r_return
id|ccode
suffix:semicolon
)brace
DECL|function|xsch
r_extern
id|__inline__
r_int
id|xsch
c_func
(paren
r_int
id|irq
)paren
(brace
r_int
id|ccode
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   lr    1,%1&bslash;n&quot;
l_string|&quot;   .insn rre,0xb2760000,%1,0&bslash;n&quot;
l_string|&quot;   ipm   %0&bslash;n&quot;
l_string|&quot;   srl   %0,28&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|ccode
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|irq
op_or
l_int|0x10000L
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
r_return
id|ccode
suffix:semicolon
)brace
DECL|function|iac
r_extern
id|__inline__
r_int
id|iac
c_func
(paren
r_void
)paren
(brace
r_int
id|ccode
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   iac   1&bslash;n&quot;
l_string|&quot;   ipm   %0&bslash;n&quot;
l_string|&quot;   srl   %0,28&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|ccode
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
r_return
id|ccode
suffix:semicolon
)brace
DECL|function|rchp
r_extern
id|__inline__
r_int
id|rchp
c_func
(paren
r_int
id|chpid
)paren
(brace
r_int
id|ccode
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   lr    1,%1&bslash;n&quot;
l_string|&quot;   rchp&bslash;n&quot;
l_string|&quot;   ipm   %0&bslash;n&quot;
l_string|&quot;   srl   %0,28&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|ccode
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|chpid
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
r_return
id|ccode
suffix:semicolon
)brace
r_typedef
r_struct
(brace
DECL|member|vrdcdvno
id|__u16
id|vrdcdvno
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* device number (input) */
DECL|member|vrdclen
id|__u16
id|vrdclen
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* data block length (input) */
DECL|member|vrdcvcla
id|__u32
id|vrdcvcla
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* virtual device class (output) */
DECL|member|vrdcvtyp
id|__u32
id|vrdcvtyp
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* virtual device type (output) */
DECL|member|vrdcvsta
id|__u32
id|vrdcvsta
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* virtual device status (output) */
DECL|member|vrdcvfla
id|__u32
id|vrdcvfla
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* virtual device flags (output) */
DECL|member|vrdcrccl
id|__u32
id|vrdcrccl
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* real device class (output) */
DECL|member|vrdccrty
id|__u32
id|vrdccrty
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* real device type (output) */
DECL|member|vrdccrmd
id|__u32
id|vrdccrmd
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* real device model (output) */
DECL|member|vrdccrft
id|__u32
id|vrdccrft
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* real device feature (output) */
DECL|typedef|diag210_t
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|4
)paren
)paren
)paren
id|diag210_t
suffix:semicolon
r_void
id|VM_virtual_device_info
c_func
(paren
id|__u16
id|devno
comma
multiline_comment|/* device number */
id|senseid_t
op_star
id|ps
)paren
suffix:semicolon
multiline_comment|/* ptr to senseID data */
DECL|function|diag210
r_extern
id|__inline__
r_int
id|diag210
c_func
(paren
id|diag210_t
op_star
id|addr
)paren
(brace
r_int
id|ccode
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
macro_line|#ifdef CONFIG_ARCH_S390X
l_string|&quot;   sam31&bslash;n&quot;
l_string|&quot;   diag  %1,0,0x210&bslash;n&quot;
l_string|&quot;   sam64&bslash;n&quot;
macro_line|#else
l_string|&quot;   diag  %1,0,0x210&bslash;n&quot;
macro_line|#endif
l_string|&quot;   ipm   %0&bslash;n&quot;
l_string|&quot;   srl   %0,28&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|ccode
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|ccode
suffix:semicolon
)brace
DECL|function|chsc
r_extern
id|__inline__
r_int
id|chsc
c_func
(paren
id|chsc_area_t
op_star
id|chsc_area
)paren
(brace
r_int
id|cc
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;.insn&t;rre,0xb25f0000,%1,0&t;&bslash;n&bslash;t&quot;
l_string|&quot;ipm&t;%0&t;&bslash;n&bslash;t&quot;
l_string|&quot;srl&t;%0,28&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|cc
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|chsc_area
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|cc
suffix:semicolon
)brace
multiline_comment|/*&n; * Various low-level irq details needed by irq.c, process.c,&n; * time.c, io_apic.c and smp.c&n; *&n; * Interrupt entry/exit code at both C and assembly level&n; */
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;asm/atomic.h&gt;
DECL|function|irq_enter
r_static
r_inline
r_void
id|irq_enter
c_func
(paren
r_int
id|cpu
comma
r_int
r_int
id|irq
)paren
(brace
id|hardirq_enter
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|global_irq_lock
)paren
op_ne
l_int|0
)paren
(brace
id|eieio
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|irq_exit
r_static
r_inline
r_void
id|irq_exit
c_func
(paren
r_int
id|cpu
comma
r_int
r_int
id|irq
)paren
(brace
id|hardirq_exit
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|release_irqlock
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|irq_enter
mdefine_line|#define irq_enter(cpu, irq)     (++local_irq_count(cpu))
DECL|macro|irq_exit
mdefine_line|#define irq_exit(cpu, irq)      (--local_irq_count(cpu))
macro_line|#endif
DECL|macro|__STR
mdefine_line|#define __STR(x) #x
DECL|macro|STR
mdefine_line|#define STR(x) __STR(x)
multiline_comment|/*&n; * x86 profiling function, SMP safe. We might want to do this in&n; * assembly totally?&n; * is this ever used anyway?&n; */
r_extern
r_char
id|_stext
suffix:semicolon
DECL|function|s390_do_profile
r_static
r_inline
r_void
id|s390_do_profile
(paren
r_int
r_int
id|addr
)paren
(brace
r_if
c_cond
(paren
id|prof_buffer
op_logical_and
id|current-&gt;pid
)paren
(brace
macro_line|#ifndef CONFIG_ARCH_S390X
id|addr
op_and_assign
l_int|0x7fffffff
suffix:semicolon
macro_line|#endif
id|addr
op_sub_assign
(paren
r_int
r_int
)paren
op_amp
id|_stext
suffix:semicolon
id|addr
op_rshift_assign
id|prof_shift
suffix:semicolon
multiline_comment|/*&n;                 * Don&squot;t ignore out-of-bounds EIP values silently,&n;                 * put them into the last histogram slot, so if&n;                 * present, they will show up as a sharp peak.&n;                 */
r_if
c_cond
(paren
id|addr
OG
id|prof_len
op_minus
l_int|1
)paren
id|addr
op_assign
id|prof_len
op_minus
l_int|1
suffix:semicolon
id|atomic_inc
c_func
(paren
(paren
id|atomic_t
op_star
)paren
op_amp
id|prof_buffer
(braket
id|addr
)braket
)paren
suffix:semicolon
)brace
)brace
macro_line|#include &lt;asm/s390io.h&gt;
DECL|macro|get_irq_lock
mdefine_line|#define get_irq_lock(irq) &amp;ioinfo[irq]-&gt;irq_lock
DECL|macro|s390irq_spin_lock
mdefine_line|#define s390irq_spin_lock(irq) &bslash;&n;        spin_lock(get_irq_lock(irq))
DECL|macro|s390irq_spin_unlock
mdefine_line|#define s390irq_spin_unlock(irq) &bslash;&n;        spin_unlock(get_irq_lock(irq))
DECL|macro|s390irq_spin_lock_irqsave
mdefine_line|#define s390irq_spin_lock_irqsave(irq,flags) &bslash;&n;        spin_lock_irqsave(get_irq_lock(irq), flags)
DECL|macro|s390irq_spin_unlock_irqrestore
mdefine_line|#define s390irq_spin_unlock_irqrestore(irq,flags) &bslash;&n;        spin_unlock_irqrestore(get_irq_lock(irq), flags)
DECL|macro|touch_nmi_watchdog
mdefine_line|#define touch_nmi_watchdog() do { } while(0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
