macro_line|#ifndef _LMC_MEDIA_H_
DECL|macro|_LMC_MEDIA_H_
mdefine_line|#define _LMC_MEDIA_H_
DECL|variable|lmc_ds3_media
id|lmc_media_t
id|lmc_ds3_media
op_assign
(brace
id|lmc_ds3_init
comma
multiline_comment|/* special media init stuff */
id|lmc_ds3_default
comma
multiline_comment|/* reset to default state */
id|lmc_ds3_set_status
comma
multiline_comment|/* reset status to state provided */
id|lmc_dummy_set_1
comma
multiline_comment|/* set clock source */
id|lmc_dummy_set2_1
comma
multiline_comment|/* set line speed */
id|lmc_ds3_set_100ft
comma
multiline_comment|/* set cable length */
id|lmc_ds3_set_scram
comma
multiline_comment|/* set scrambler */
id|lmc_ds3_get_link_status
comma
multiline_comment|/* get link status */
id|lmc_dummy_set_1
comma
multiline_comment|/* set link status */
id|lmc_ds3_set_crc_length
comma
multiline_comment|/* set CRC length */
id|lmc_dummy_set_1
comma
multiline_comment|/* set T1 or E1 circuit type */
id|lmc_ds3_watchdog
)brace
suffix:semicolon
DECL|variable|lmc_hssi_media
id|lmc_media_t
id|lmc_hssi_media
op_assign
(brace
id|lmc_hssi_init
comma
multiline_comment|/* special media init stuff */
id|lmc_hssi_default
comma
multiline_comment|/* reset to default state */
id|lmc_hssi_set_status
comma
multiline_comment|/* reset status to state provided */
id|lmc_hssi_set_clock
comma
multiline_comment|/* set clock source */
id|lmc_dummy_set2_1
comma
multiline_comment|/* set line speed */
id|lmc_dummy_set_1
comma
multiline_comment|/* set cable length */
id|lmc_dummy_set_1
comma
multiline_comment|/* set scrambler */
id|lmc_hssi_get_link_status
comma
multiline_comment|/* get link status */
id|lmc_hssi_set_link_status
comma
multiline_comment|/* set link status */
id|lmc_hssi_set_crc_length
comma
multiline_comment|/* set CRC length */
id|lmc_dummy_set_1
comma
multiline_comment|/* set T1 or E1 circuit type */
id|lmc_hssi_watchdog
)brace
suffix:semicolon
DECL|variable|lmc_ssi_media
id|lmc_media_t
id|lmc_ssi_media
op_assign
(brace
id|lmc_ssi_init
comma
multiline_comment|/* special media init stuff */
id|lmc_ssi_default
comma
multiline_comment|/* reset to default state */
id|lmc_ssi_set_status
comma
multiline_comment|/* reset status to state provided */
id|lmc_ssi_set_clock
comma
multiline_comment|/* set clock source */
id|lmc_ssi_set_speed
comma
multiline_comment|/* set line speed */
id|lmc_dummy_set_1
comma
multiline_comment|/* set cable length */
id|lmc_dummy_set_1
comma
multiline_comment|/* set scrambler */
id|lmc_ssi_get_link_status
comma
multiline_comment|/* get link status */
id|lmc_ssi_set_link_status
comma
multiline_comment|/* set link status */
id|lmc_ssi_set_crc_length
comma
multiline_comment|/* set CRC length */
id|lmc_dummy_set_1
comma
multiline_comment|/* set T1 or E1 circuit type */
id|lmc_ssi_watchdog
)brace
suffix:semicolon
DECL|variable|lmc_t1_media
id|lmc_media_t
id|lmc_t1_media
op_assign
(brace
id|lmc_t1_init
comma
multiline_comment|/* special media init stuff */
id|lmc_t1_default
comma
multiline_comment|/* reset to default state */
id|lmc_t1_set_status
comma
multiline_comment|/* reset status to state provided */
id|lmc_t1_set_clock
comma
multiline_comment|/* set clock source */
id|lmc_dummy_set2_1
comma
multiline_comment|/* set line speed */
id|lmc_dummy_set_1
comma
multiline_comment|/* set cable length */
id|lmc_dummy_set_1
comma
multiline_comment|/* set scrambler */
id|lmc_t1_get_link_status
comma
multiline_comment|/* get link status */
id|lmc_dummy_set_1
comma
multiline_comment|/* set link status */
id|lmc_t1_set_crc_length
comma
multiline_comment|/* set CRC length */
id|lmc_t1_set_circuit_type
comma
multiline_comment|/* set T1 or E1 circuit type */
id|lmc_t1_watchdog
)brace
suffix:semicolon
macro_line|#endif
eof
