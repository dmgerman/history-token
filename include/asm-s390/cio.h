multiline_comment|/*&n; *  include/asm-s390/cio.h&n; *  include/asm-s390x/cio.h&n; *&n; * Common interface for I/O on S/390&n; */
macro_line|#ifndef _ASM_S390_CIO_H_
DECL|macro|_ASM_S390_CIO_H_
mdefine_line|#define _ASM_S390_CIO_H_
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#ifdef __KERNEL__
DECL|macro|LPM_ANYPATH
mdefine_line|#define LPM_ANYPATH 0xff
multiline_comment|/*&n; * subchannel status word&n; */
DECL|struct|scsw
r_struct
id|scsw
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
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|SCSW_FCTL_CLEAR_FUNC
mdefine_line|#define SCSW_FCTL_CLEAR_FUNC&t; 0x1
DECL|macro|SCSW_FCTL_HALT_FUNC
mdefine_line|#define SCSW_FCTL_HALT_FUNC&t; 0x2
DECL|macro|SCSW_FCTL_START_FUNC
mdefine_line|#define SCSW_FCTL_START_FUNC&t; 0x4
DECL|macro|SCSW_ACTL_SUSPENDED
mdefine_line|#define SCSW_ACTL_SUSPENDED&t; 0x1
DECL|macro|SCSW_ACTL_DEVACT
mdefine_line|#define SCSW_ACTL_DEVACT&t; 0x2
DECL|macro|SCSW_ACTL_SCHACT
mdefine_line|#define SCSW_ACTL_SCHACT&t; 0x4
DECL|macro|SCSW_ACTL_CLEAR_PEND
mdefine_line|#define SCSW_ACTL_CLEAR_PEND&t; 0x8
DECL|macro|SCSW_ACTL_HALT_PEND
mdefine_line|#define SCSW_ACTL_HALT_PEND&t; 0x10
DECL|macro|SCSW_ACTL_START_PEND
mdefine_line|#define SCSW_ACTL_START_PEND&t; 0x20
DECL|macro|SCSW_ACTL_RESUME_PEND
mdefine_line|#define SCSW_ACTL_RESUME_PEND&t; 0x40
DECL|macro|SCSW_STCTL_STATUS_PEND
mdefine_line|#define SCSW_STCTL_STATUS_PEND&t; 0x1
DECL|macro|SCSW_STCTL_SEC_STATUS
mdefine_line|#define SCSW_STCTL_SEC_STATUS&t; 0x2
DECL|macro|SCSW_STCTL_PRIM_STATUS
mdefine_line|#define SCSW_STCTL_PRIM_STATUS&t; 0x4
DECL|macro|SCSW_STCTL_INTER_STATUS
mdefine_line|#define SCSW_STCTL_INTER_STATUS&t; 0x8
DECL|macro|SCSW_STCTL_ALERT_STATUS
mdefine_line|#define SCSW_STCTL_ALERT_STATUS&t; 0x10
DECL|macro|DEV_STAT_ATTENTION
mdefine_line|#define DEV_STAT_ATTENTION&t; 0x80
DECL|macro|DEV_STAT_STAT_MOD
mdefine_line|#define DEV_STAT_STAT_MOD&t; 0x40
DECL|macro|DEV_STAT_CU_END
mdefine_line|#define DEV_STAT_CU_END&t;&t; 0x20
DECL|macro|DEV_STAT_BUSY
mdefine_line|#define DEV_STAT_BUSY&t;&t; 0x10
DECL|macro|DEV_STAT_CHN_END
mdefine_line|#define DEV_STAT_CHN_END&t; 0x08
DECL|macro|DEV_STAT_DEV_END
mdefine_line|#define DEV_STAT_DEV_END&t; 0x04
DECL|macro|DEV_STAT_UNIT_CHECK
mdefine_line|#define DEV_STAT_UNIT_CHECK&t; 0x02
DECL|macro|DEV_STAT_UNIT_EXCEP
mdefine_line|#define DEV_STAT_UNIT_EXCEP&t; 0x01
DECL|macro|SCHN_STAT_PCI
mdefine_line|#define SCHN_STAT_PCI&t;&t; 0x80
DECL|macro|SCHN_STAT_INCORR_LEN
mdefine_line|#define SCHN_STAT_INCORR_LEN&t; 0x40
DECL|macro|SCHN_STAT_PROG_CHECK
mdefine_line|#define SCHN_STAT_PROG_CHECK&t; 0x20
DECL|macro|SCHN_STAT_PROT_CHECK
mdefine_line|#define SCHN_STAT_PROT_CHECK&t; 0x10
DECL|macro|SCHN_STAT_CHN_DATA_CHK
mdefine_line|#define SCHN_STAT_CHN_DATA_CHK&t; 0x08
DECL|macro|SCHN_STAT_CHN_CTRL_CHK
mdefine_line|#define SCHN_STAT_CHN_CTRL_CHK&t; 0x04
DECL|macro|SCHN_STAT_INTF_CTRL_CHK
mdefine_line|#define SCHN_STAT_INTF_CTRL_CHK&t; 0x02
DECL|macro|SCHN_STAT_CHAIN_CHECK
mdefine_line|#define SCHN_STAT_CHAIN_CHECK&t; 0x01
multiline_comment|/*&n; * architectured values for first sense byte&n; */
DECL|macro|SNS0_CMD_REJECT
mdefine_line|#define SNS0_CMD_REJECT&t;&t;0x80
DECL|macro|SNS_CMD_REJECT
mdefine_line|#define SNS_CMD_REJECT&t;&t;SNS0_CMD_REJEC
DECL|macro|SNS0_INTERVENTION_REQ
mdefine_line|#define SNS0_INTERVENTION_REQ&t;0x40
DECL|macro|SNS0_BUS_OUT_CHECK
mdefine_line|#define SNS0_BUS_OUT_CHECK&t;0x20
DECL|macro|SNS0_EQUIPMENT_CHECK
mdefine_line|#define SNS0_EQUIPMENT_CHECK&t;0x10
DECL|macro|SNS0_DATA_CHECK
mdefine_line|#define SNS0_DATA_CHECK&t;&t;0x08
DECL|macro|SNS0_OVERRUN
mdefine_line|#define SNS0_OVERRUN&t;&t;0x04
DECL|macro|SNS0_INCOMPL_DOMAIN
mdefine_line|#define SNS0_INCOMPL_DOMAIN&t;0x01
multiline_comment|/*&n; * architectured values for second sense byte&n; */
DECL|macro|SNS1_PERM_ERR
mdefine_line|#define SNS1_PERM_ERR&t;&t;0x80
DECL|macro|SNS1_INV_TRACK_FORMAT
mdefine_line|#define SNS1_INV_TRACK_FORMAT&t;0x40
DECL|macro|SNS1_EOC
mdefine_line|#define SNS1_EOC&t;&t;0x20
DECL|macro|SNS1_MESSAGE_TO_OPER
mdefine_line|#define SNS1_MESSAGE_TO_OPER&t;0x10
DECL|macro|SNS1_NO_REC_FOUND
mdefine_line|#define SNS1_NO_REC_FOUND&t;0x08
DECL|macro|SNS1_FILE_PROTECTED
mdefine_line|#define SNS1_FILE_PROTECTED&t;0x04
DECL|macro|SNS1_WRITE_INHIBITED
mdefine_line|#define SNS1_WRITE_INHIBITED&t;0x02
DECL|macro|SNS1_INPRECISE_END
mdefine_line|#define SNS1_INPRECISE_END&t;0x01
multiline_comment|/*&n; * architectured values for third sense byte&n; */
DECL|macro|SNS2_REQ_INH_WRITE
mdefine_line|#define SNS2_REQ_INH_WRITE&t;0x80
DECL|macro|SNS2_CORRECTABLE
mdefine_line|#define SNS2_CORRECTABLE&t;0x40
DECL|macro|SNS2_FIRST_LOG_ERR
mdefine_line|#define SNS2_FIRST_LOG_ERR&t;0x20
DECL|macro|SNS2_ENV_DATA_PRESENT
mdefine_line|#define SNS2_ENV_DATA_PRESENT&t;0x10
DECL|macro|SNS2_INPRECISE_END
mdefine_line|#define SNS2_INPRECISE_END&t;0x04
DECL|struct|ccw1
r_struct
id|ccw1
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
multiline_comment|/* flags, like IDA addressing, etc. */
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
suffix:semicolon
DECL|macro|CCW_FLAG_DC
mdefine_line|#define CCW_FLAG_DC&t;&t;0x80
DECL|macro|CCW_FLAG_CC
mdefine_line|#define CCW_FLAG_CC&t;&t;0x40
DECL|macro|CCW_FLAG_SLI
mdefine_line|#define CCW_FLAG_SLI&t;&t;0x20
DECL|macro|CCW_FLAG_SKIP
mdefine_line|#define CCW_FLAG_SKIP&t;&t;0x10
DECL|macro|CCW_FLAG_PCI
mdefine_line|#define CCW_FLAG_PCI&t;&t;0x08
DECL|macro|CCW_FLAG_IDA
mdefine_line|#define CCW_FLAG_IDA&t;&t;0x04
DECL|macro|CCW_FLAG_SUSPEND
mdefine_line|#define CCW_FLAG_SUSPEND&t;0x02
DECL|macro|CCW_CMD_READ_IPL
mdefine_line|#define CCW_CMD_READ_IPL&t;0x02
DECL|macro|CCW_CMD_NOOP
mdefine_line|#define CCW_CMD_NOOP&t;&t;0x03
DECL|macro|CCW_CMD_BASIC_SENSE
mdefine_line|#define CCW_CMD_BASIC_SENSE&t;0x04
DECL|macro|CCW_CMD_TIC
mdefine_line|#define CCW_CMD_TIC&t;&t;0x08
DECL|macro|CCW_CMD_STLCK
mdefine_line|#define CCW_CMD_STLCK           0x14
DECL|macro|CCW_CMD_SENSE_PGID
mdefine_line|#define CCW_CMD_SENSE_PGID&t;0x34
DECL|macro|CCW_CMD_SUSPEND_RECONN
mdefine_line|#define CCW_CMD_SUSPEND_RECONN&t;0x5B
DECL|macro|CCW_CMD_RDC
mdefine_line|#define CCW_CMD_RDC&t;&t;0x64
DECL|macro|CCW_CMD_RELEASE
mdefine_line|#define CCW_CMD_RELEASE&t;&t;0x94
DECL|macro|CCW_CMD_SET_PGID
mdefine_line|#define CCW_CMD_SET_PGID&t;0xAF
DECL|macro|CCW_CMD_SENSE_ID
mdefine_line|#define CCW_CMD_SENSE_ID&t;0xE4
DECL|macro|CCW_CMD_DCTL
mdefine_line|#define CCW_CMD_DCTL&t;&t;0xF3
DECL|macro|SENSE_MAX_COUNT
mdefine_line|#define SENSE_MAX_COUNT&t;&t;0x20
DECL|struct|erw
r_struct
id|erw
(brace
DECL|member|res0
id|__u32
id|res0
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|auth
id|__u32
id|auth
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Authorization check */
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
DECL|member|scavf
id|__u32
id|scavf
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Secondary ccw address validity flag */
DECL|member|fsaf
id|__u32
id|fsaf
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Failing storage address format */
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
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * subchannel logout area&n; */
DECL|struct|sublog
r_struct
id|sublog
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
DECL|member|arep
id|__u32
id|arep
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* ancillary report */
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
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Format 0 Extended Status Word (ESW)&n; */
DECL|struct|esw0
r_struct
id|esw0
(brace
DECL|member|sublog
r_struct
id|sublog
id|sublog
suffix:semicolon
multiline_comment|/* subchannel logout */
DECL|member|erw
r_struct
id|erw
id|erw
suffix:semicolon
multiline_comment|/* extended report word */
DECL|member|faddr
id|__u32
id|faddr
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* failing storage address */
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
multiline_comment|/* secondary ccw address */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Format 1 Extended Status Word (ESW)&n; */
DECL|struct|esw1
r_struct
id|esw1
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
r_struct
id|erw
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
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Format 2 Extended Status Word (ESW)&n; */
DECL|struct|esw2
r_struct
id|esw2
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
r_struct
id|erw
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
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Format 3 Extended Status Word (ESW)&n; */
DECL|struct|esw3
r_struct
id|esw3
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
r_struct
id|erw
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
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * interruption response block&n; */
DECL|struct|irb
r_struct
id|irb
(brace
DECL|member|scsw
r_struct
id|scsw
id|scsw
suffix:semicolon
multiline_comment|/* subchannel status word */
r_union
(brace
multiline_comment|/* extended status word, 4 formats */
DECL|member|esw0
r_struct
id|esw0
id|esw0
suffix:semicolon
DECL|member|esw1
r_struct
id|esw1
id|esw1
suffix:semicolon
DECL|member|esw2
r_struct
id|esw2
id|esw2
suffix:semicolon
DECL|member|esw3
r_struct
id|esw3
id|esw3
suffix:semicolon
DECL|member|esw
)brace
id|esw
suffix:semicolon
DECL|member|ecw
id|__u8
id|ecw
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* extended control word */
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
suffix:semicolon
multiline_comment|/*&n; * command information word  (CIW) layout&n; */
DECL|struct|ciw
r_struct
id|ciw
(brace
DECL|member|et
id|__u32
id|et
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* entry type */
DECL|member|reserved
id|__u32
id|reserved
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|ct
id|__u32
id|ct
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* command type */
DECL|member|cmd
id|__u32
id|cmd
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* command */
DECL|member|count
id|__u32
id|count
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* coun */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|CIW_TYPE_RCD
mdefine_line|#define CIW_TYPE_RCD&t;0x0    &t;/* read configuration data */
DECL|macro|CIW_TYPE_SII
mdefine_line|#define CIW_TYPE_SII&t;0x1    &t;/* set interface identifier */
DECL|macro|CIW_TYPE_RNI
mdefine_line|#define CIW_TYPE_RNI&t;0x2    &t;/* read node identifier */
multiline_comment|/*&n; * Flags used as input parameters for do_IO()&n; */
DECL|macro|DOIO_ALLOW_SUSPEND
mdefine_line|#define DOIO_ALLOW_SUSPEND&t; 0x0001 /* allow for channel prog. suspend */
DECL|macro|DOIO_DENY_PREFETCH
mdefine_line|#define DOIO_DENY_PREFETCH&t; 0x0002 /* don&squot;t allow for CCW prefetch */
DECL|macro|DOIO_SUPPRESS_INTER
mdefine_line|#define DOIO_SUPPRESS_INTER&t; 0x0004 /* suppress intermediate inter. */
multiline_comment|/* ... for suspended CCWs */
multiline_comment|/* Device or subchannel gone. */
DECL|macro|CIO_GONE
mdefine_line|#define CIO_GONE       0x0001
multiline_comment|/* No path to device. */
DECL|macro|CIO_NO_PATH
mdefine_line|#define CIO_NO_PATH    0x0002
multiline_comment|/* Device has appeared. */
DECL|macro|CIO_OPER
mdefine_line|#define CIO_OPER       0x0004
multiline_comment|/* Sick revalidation of device. */
DECL|macro|CIO_REVALIDATE
mdefine_line|#define CIO_REVALIDATE 0x0008
DECL|struct|diag210
r_struct
id|diag210
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
suffix:semicolon
r_extern
r_int
id|diag210
c_func
(paren
r_struct
id|diag210
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|wait_cons_dev
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|clear_all_subchannels
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
