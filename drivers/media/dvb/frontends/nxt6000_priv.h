multiline_comment|/*&n; * Public Include File for DRV6000 users&n; * (ie. NxtWave Communications - NXT6000 demodulator driver)&n; *&n; * Copyright (C) 2001 NxtWave Communications, Inc.&n; *&n; */
multiline_comment|/*  Nxt6000 Register Addresses and Bit Masks */
multiline_comment|/* Maximum Register Number */
DECL|macro|MAXNXT6000REG
mdefine_line|#define MAXNXT6000REG          (0x9A)
multiline_comment|/* 0x1B A_VIT_BER_0  aka 0x3A */
DECL|macro|A_VIT_BER_0
mdefine_line|#define A_VIT_BER_0            (0x1B)
multiline_comment|/* 0x1D A_VIT_BER_TIMER_0 aka 0x38 */
DECL|macro|A_VIT_BER_TIMER_0
mdefine_line|#define A_VIT_BER_TIMER_0      (0x1D)
multiline_comment|/* 0x21 RS_COR_STAT */
DECL|macro|RS_COR_STAT
mdefine_line|#define RS_COR_STAT            (0x21)
DECL|macro|RSCORESTATUS
mdefine_line|#define RSCORESTATUS           (0x03)
multiline_comment|/* 0x22 RS_COR_INTEN */
DECL|macro|RS_COR_INTEN
mdefine_line|#define RS_COR_INTEN           (0x22)
multiline_comment|/* 0x23 RS_COR_INSTAT */
DECL|macro|RS_COR_INSTAT
mdefine_line|#define RS_COR_INSTAT          (0x23)
DECL|macro|INSTAT_ERROR
mdefine_line|#define INSTAT_ERROR           (0x04)
DECL|macro|LOCK_LOSS_BITS
mdefine_line|#define LOCK_LOSS_BITS         (0x03)
multiline_comment|/* 0x24 RS_COR_SYNC_PARAM */
DECL|macro|RS_COR_SYNC_PARAM
mdefine_line|#define RS_COR_SYNC_PARAM      (0x24)
DECL|macro|SYNC_PARAM
mdefine_line|#define SYNC_PARAM             (0x03)
multiline_comment|/* 0x25 BER_CTRL */
DECL|macro|BER_CTRL
mdefine_line|#define BER_CTRL               (0x25)
DECL|macro|BER_ENABLE
mdefine_line|#define BER_ENABLE             (0x02)
DECL|macro|BER_RESET
mdefine_line|#define BER_RESET              (0x01)
multiline_comment|/* 0x26 BER_PAY */
DECL|macro|BER_PAY
mdefine_line|#define BER_PAY                (0x26)
multiline_comment|/* 0x27 BER_PKT_L */
DECL|macro|BER_PKT_L
mdefine_line|#define BER_PKT_L              (0x27)
DECL|macro|BER_PKTOVERFLOW
mdefine_line|#define BER_PKTOVERFLOW        (0x80)
multiline_comment|/* 0x30 VIT_COR_CTL */
DECL|macro|VIT_COR_CTL
mdefine_line|#define VIT_COR_CTL            (0x30)
DECL|macro|BER_CONTROL
mdefine_line|#define BER_CONTROL            (0x02)
DECL|macro|VIT_COR_MASK
mdefine_line|#define VIT_COR_MASK           (0x82)
DECL|macro|VIT_COR_RESYNC
mdefine_line|#define VIT_COR_RESYNC         (0x80)
multiline_comment|/* 0x32 VIT_SYNC_STATUS */
DECL|macro|VIT_SYNC_STATUS
mdefine_line|#define VIT_SYNC_STATUS        (0x32)
DECL|macro|VITINSYNC
mdefine_line|#define VITINSYNC              (0x80)
multiline_comment|/* 0x33 VIT_COR_INTEN */
DECL|macro|VIT_COR_INTEN
mdefine_line|#define VIT_COR_INTEN          (0x33)
DECL|macro|GLOBAL_ENABLE
mdefine_line|#define GLOBAL_ENABLE          (0x80)
multiline_comment|/* 0x34 VIT_COR_INTSTAT */
DECL|macro|VIT_COR_INTSTAT
mdefine_line|#define VIT_COR_INTSTAT        (0x34)
DECL|macro|BER_DONE
mdefine_line|#define BER_DONE               (0x08)
DECL|macro|BER_OVERFLOW
mdefine_line|#define BER_OVERFLOW           (0x10)
multiline_comment|/* 0x38 OFDM_BERTimer */
multiline_comment|/* Use the alias registers */
DECL|macro|A_VIT_BER_TIMER_0
mdefine_line|#define A_VIT_BER_TIMER_0      (0x1D)
multiline_comment|/* 0x3A VIT_BER_TIMER_0 */
multiline_comment|/* Use the alias registers */
DECL|macro|A_VIT_BER_0
mdefine_line|#define A_VIT_BER_0            (0x1B)
multiline_comment|/* 0x40 OFDM_COR_CTL */
DECL|macro|OFDM_COR_CTL
mdefine_line|#define OFDM_COR_CTL           (0x40)
DECL|macro|COREACT
mdefine_line|#define COREACT                (0x20)
DECL|macro|HOLDSM
mdefine_line|#define HOLDSM                 (0x10)
DECL|macro|WAIT_AGC
mdefine_line|#define WAIT_AGC               (0x02)
DECL|macro|WAIT_SYR
mdefine_line|#define WAIT_SYR               (0x03)
multiline_comment|/* 0x41 OFDM_COR_STAT */
DECL|macro|OFDM_COR_STAT
mdefine_line|#define OFDM_COR_STAT          (0x41)
DECL|macro|COR_STATUS
mdefine_line|#define COR_STATUS             (0x0F)
DECL|macro|MONITOR_TPS
mdefine_line|#define MONITOR_TPS            (0x06)
DECL|macro|TPSLOCKED
mdefine_line|#define TPSLOCKED              (0x40)
DECL|macro|AGCLOCKED
mdefine_line|#define AGCLOCKED              (0x10)
multiline_comment|/* 0x42 OFDM_COR_INTEN */
DECL|macro|OFDM_COR_INTEN
mdefine_line|#define OFDM_COR_INTEN         (0x42)
DECL|macro|TPSRCVBAD
mdefine_line|#define TPSRCVBAD              (0x04)
DECL|macro|TPSRCVCHANGED
mdefine_line|#define TPSRCVCHANGED         (0x02)
DECL|macro|TPSRCVUPDATE
mdefine_line|#define TPSRCVUPDATE           (0x01)
multiline_comment|/* 0x43 OFDM_COR_INSTAT */
DECL|macro|OFDM_COR_INSTAT
mdefine_line|#define OFDM_COR_INSTAT        (0x43)
multiline_comment|/* 0x44 OFDM_COR_MODEGUARD */
DECL|macro|OFDM_COR_MODEGUARD
mdefine_line|#define OFDM_COR_MODEGUARD     (0x44)
DECL|macro|FORCEMODE
mdefine_line|#define FORCEMODE              (0x08)
DECL|macro|FORCEMODE8K
mdefine_line|#define FORCEMODE8K&t;&t;&t;   (0x04)
multiline_comment|/* 0x45 OFDM_AGC_CTL */
DECL|macro|OFDM_AGC_CTL
mdefine_line|#define OFDM_AGC_CTL           (0x45)
DECL|macro|INITIAL_AGC_BW
mdefine_line|#define INITIAL_AGC_BW&t;&t;   (0x08)
DECL|macro|AGCNEG
mdefine_line|#define AGCNEG                 (0x02)
DECL|macro|AGCLAST
mdefine_line|#define AGCLAST&t;&t;&t;&t;   (0x10)
multiline_comment|/* 0x48 OFDM_AGC_TARGET */
DECL|macro|OFDM_AGC_TARGET
mdefine_line|#define OFDM_AGC_TARGET&t;&t;   (0x48)
DECL|macro|OFDM_AGC_TARGET_DEFAULT
mdefine_line|#define OFDM_AGC_TARGET_DEFAULT (0x28)
DECL|macro|OFDM_AGC_TARGET_IMPULSE
mdefine_line|#define OFDM_AGC_TARGET_IMPULSE (0x38)
multiline_comment|/* 0x49 OFDM_AGC_GAIN_1 */
DECL|macro|OFDM_AGC_GAIN_1
mdefine_line|#define OFDM_AGC_GAIN_1        (0x49)
multiline_comment|/* 0x4B OFDM_ITB_CTL */
DECL|macro|OFDM_ITB_CTL
mdefine_line|#define OFDM_ITB_CTL           (0x4B)
DECL|macro|ITBINV
mdefine_line|#define ITBINV                 (0x01)
multiline_comment|/* 0x4C OFDM_ITB_FREQ_1 */
DECL|macro|OFDM_ITB_FREQ_1
mdefine_line|#define OFDM_ITB_FREQ_1        (0x4C)
multiline_comment|/* 0x4D OFDM_ITB_FREQ_2 */
DECL|macro|OFDM_ITB_FREQ_2
mdefine_line|#define OFDM_ITB_FREQ_2        (0x4D)
multiline_comment|/* 0x4E  OFDM_CAS_CTL */
DECL|macro|OFDM_CAS_CTL
mdefine_line|#define OFDM_CAS_CTL           (0x4E)
DECL|macro|ACSDIS
mdefine_line|#define ACSDIS                 (0x40)
DECL|macro|CCSEN
mdefine_line|#define CCSEN                  (0x80)
multiline_comment|/* 0x4F CAS_FREQ */
DECL|macro|CAS_FREQ
mdefine_line|#define CAS_FREQ               (0x4F)
multiline_comment|/* 0x51 OFDM_SYR_CTL */
DECL|macro|OFDM_SYR_CTL
mdefine_line|#define OFDM_SYR_CTL           (0x51)
DECL|macro|SIXTH_ENABLE
mdefine_line|#define SIXTH_ENABLE           (0x80)
DECL|macro|SYR_TRACKING_DISABLE
mdefine_line|#define SYR_TRACKING_DISABLE   (0x01)
multiline_comment|/* 0x52 OFDM_SYR_STAT */
DECL|macro|OFDM_SYR_STAT
mdefine_line|#define OFDM_SYR_STAT&t;&t;   (0x52)
DECL|macro|GI14_2K_SYR_LOCK
mdefine_line|#define GI14_2K_SYR_LOCK&t;   (0x13)
DECL|macro|GI14_8K_SYR_LOCK
mdefine_line|#define GI14_8K_SYR_LOCK&t;   (0x17)
DECL|macro|GI14_SYR_LOCK
mdefine_line|#define GI14_SYR_LOCK&t;&t;   (0x10)
multiline_comment|/* 0x55 OFDM_SYR_OFFSET_1 */
DECL|macro|OFDM_SYR_OFFSET_1
mdefine_line|#define OFDM_SYR_OFFSET_1      (0x55)
multiline_comment|/* 0x56 OFDM_SYR_OFFSET_2 */
DECL|macro|OFDM_SYR_OFFSET_2
mdefine_line|#define OFDM_SYR_OFFSET_2      (0x56)
multiline_comment|/* 0x58 OFDM_SCR_CTL */
DECL|macro|OFDM_SCR_CTL
mdefine_line|#define OFDM_SCR_CTL           (0x58)
DECL|macro|SYR_ADJ_DECAY_MASK
mdefine_line|#define SYR_ADJ_DECAY_MASK     (0x70)
DECL|macro|SYR_ADJ_DECAY
mdefine_line|#define SYR_ADJ_DECAY          (0x30)
multiline_comment|/* 0x59 OFDM_PPM_CTL_1 */
DECL|macro|OFDM_PPM_CTL_1
mdefine_line|#define OFDM_PPM_CTL_1         (0x59)
DECL|macro|PPMMAX_MASK
mdefine_line|#define PPMMAX_MASK            (0x30)
DECL|macro|PPM256
mdefine_line|#define PPM256&t;&t;&t;&t;   (0x30)
multiline_comment|/* 0x5B OFDM_TRL_NOMINALRATE_1 */
DECL|macro|OFDM_TRL_NOMINALRATE_1
mdefine_line|#define OFDM_TRL_NOMINALRATE_1 (0x5B)
multiline_comment|/* 0x5C OFDM_TRL_NOMINALRATE_2 */
DECL|macro|OFDM_TRL_NOMINALRATE_2
mdefine_line|#define OFDM_TRL_NOMINALRATE_2 (0x5C)
multiline_comment|/* 0x5D OFDM_TRL_TIME_1 */
DECL|macro|OFDM_TRL_TIME_1
mdefine_line|#define OFDM_TRL_TIME_1        (0x5D)
multiline_comment|/* 0x60 OFDM_CRL_FREQ_1 */
DECL|macro|OFDM_CRL_FREQ_1
mdefine_line|#define OFDM_CRL_FREQ_1        (0x60)
multiline_comment|/* 0x63 OFDM_CHC_CTL_1 */
DECL|macro|OFDM_CHC_CTL_1
mdefine_line|#define OFDM_CHC_CTL_1         (0x63)
DECL|macro|MANMEAN1
mdefine_line|#define MANMEAN1               (0xF0);
DECL|macro|CHCFIR
mdefine_line|#define CHCFIR                 (0x01)
multiline_comment|/* 0x64 OFDM_CHC_SNR */
DECL|macro|OFDM_CHC_SNR
mdefine_line|#define OFDM_CHC_SNR           (0x64)
multiline_comment|/* 0x65 OFDM_BDI_CTL */
DECL|macro|OFDM_BDI_CTL
mdefine_line|#define OFDM_BDI_CTL           (0x65)
DECL|macro|LP_SELECT
mdefine_line|#define LP_SELECT              (0x02)
multiline_comment|/* 0x67 OFDM_TPS_RCVD_1 */
DECL|macro|OFDM_TPS_RCVD_1
mdefine_line|#define OFDM_TPS_RCVD_1        (0x67)
DECL|macro|TPSFRAME
mdefine_line|#define TPSFRAME               (0x03)
multiline_comment|/* 0x68 OFDM_TPS_RCVD_2 */
DECL|macro|OFDM_TPS_RCVD_2
mdefine_line|#define OFDM_TPS_RCVD_2        (0x68)
multiline_comment|/* 0x69 OFDM_TPS_RCVD_3 */
DECL|macro|OFDM_TPS_RCVD_3
mdefine_line|#define OFDM_TPS_RCVD_3        (0x69)
multiline_comment|/* 0x6A OFDM_TPS_RCVD_4 */
DECL|macro|OFDM_TPS_RCVD_4
mdefine_line|#define OFDM_TPS_RCVD_4        (0x6A)
multiline_comment|/* 0x6B OFDM_TPS_RESERVED_1 */
DECL|macro|OFDM_TPS_RESERVED_1
mdefine_line|#define OFDM_TPS_RESERVED_1    (0x6B)
multiline_comment|/* 0x6C OFDM_TPS_RESERVED_2 */
DECL|macro|OFDM_TPS_RESERVED_2
mdefine_line|#define OFDM_TPS_RESERVED_2    (0x6C)
multiline_comment|/* 0x73 OFDM_MSC_REV */
DECL|macro|OFDM_MSC_REV
mdefine_line|#define OFDM_MSC_REV           (0x73)
multiline_comment|/* 0x76 OFDM_SNR_CARRIER_2 */
DECL|macro|OFDM_SNR_CARRIER_2
mdefine_line|#define OFDM_SNR_CARRIER_2     (0x76)
DECL|macro|MEAN_MASK
mdefine_line|#define MEAN_MASK              (0x80)
DECL|macro|MEANBIT
mdefine_line|#define MEANBIT                (0x80)
multiline_comment|/* 0x80 ANALOG_CONTROL_0 */
DECL|macro|ANALOG_CONTROL_0
mdefine_line|#define ANALOG_CONTROL_0       (0x80)
DECL|macro|POWER_DOWN_ADC
mdefine_line|#define POWER_DOWN_ADC         (0x40)
multiline_comment|/* 0x81 ENABLE_TUNER_IIC */
DECL|macro|ENABLE_TUNER_IIC
mdefine_line|#define ENABLE_TUNER_IIC       (0x81)
DECL|macro|ENABLE_TUNER_BIT
mdefine_line|#define ENABLE_TUNER_BIT       (0x01)
multiline_comment|/* 0x82 EN_DMD_RACQ */
DECL|macro|EN_DMD_RACQ
mdefine_line|#define EN_DMD_RACQ            (0x82)
DECL|macro|EN_DMD_RACQ_REG_VAL
mdefine_line|#define EN_DMD_RACQ_REG_VAL    (0x81)
DECL|macro|EN_DMD_RACQ_REG_VAL_14
mdefine_line|#define EN_DMD_RACQ_REG_VAL_14 (0x01)
multiline_comment|/* 0x84 SNR_COMMAND */
DECL|macro|SNR_COMMAND
mdefine_line|#define SNR_COMMAND            (0x84)
DECL|macro|SNRStat
mdefine_line|#define SNRStat                (0x80)
multiline_comment|/* 0x85 SNRCARRIERNUMBER_LSB */
DECL|macro|SNRCARRIERNUMBER_LSB
mdefine_line|#define SNRCARRIERNUMBER_LSB   (0x85)
multiline_comment|/* 0x87 SNRMINTHRESHOLD_LSB */
DECL|macro|SNRMINTHRESHOLD_LSB
mdefine_line|#define SNRMINTHRESHOLD_LSB    (0x87)
multiline_comment|/* 0x89 SNR_PER_CARRIER_LSB */
DECL|macro|SNR_PER_CARRIER_LSB
mdefine_line|#define SNR_PER_CARRIER_LSB    (0x89)
multiline_comment|/* 0x8B SNRBELOWTHRESHOLD_LSB */
DECL|macro|SNRBELOWTHRESHOLD_LSB
mdefine_line|#define SNRBELOWTHRESHOLD_LSB  (0x8B)
multiline_comment|/* 0x91 RF_AGC_VAL_1 */
DECL|macro|RF_AGC_VAL_1
mdefine_line|#define RF_AGC_VAL_1           (0x91)
multiline_comment|/* 0x92 RF_AGC_STATUS */
DECL|macro|RF_AGC_STATUS
mdefine_line|#define RF_AGC_STATUS          (0x92)
multiline_comment|/* 0x98 DIAG_CONFIG */
DECL|macro|DIAG_CONFIG
mdefine_line|#define DIAG_CONFIG            (0x98)
DECL|macro|DIAG_MASK
mdefine_line|#define DIAG_MASK              (0x70)
DECL|macro|TB_SET
mdefine_line|#define TB_SET                 (0x10)
DECL|macro|TRAN_SELECT
mdefine_line|#define TRAN_SELECT            (0x07)
DECL|macro|SERIAL_SELECT
mdefine_line|#define SERIAL_SELECT          (0x01)
multiline_comment|/* 0x99 SUB_DIAG_MODE_SEL */
DECL|macro|SUB_DIAG_MODE_SEL
mdefine_line|#define SUB_DIAG_MODE_SEL      (0x99)
DECL|macro|CLKINVERSION
mdefine_line|#define CLKINVERSION           (0x01)
multiline_comment|/* 0x9A TS_FORMAT */
DECL|macro|TS_FORMAT
mdefine_line|#define TS_FORMAT              (0x9A)
DECL|macro|ERROR_SENSE
mdefine_line|#define ERROR_SENSE            (0x08)
DECL|macro|VALID_SENSE
mdefine_line|#define VALID_SENSE            (0x04)
DECL|macro|SYNC_SENSE
mdefine_line|#define SYNC_SENSE             (0x02)
DECL|macro|GATED_CLOCK
mdefine_line|#define GATED_CLOCK            (0x01)
DECL|macro|NXT6000ASICDEVICE
mdefine_line|#define NXT6000ASICDEVICE      (0x0b)
eof
