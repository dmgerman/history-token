multiline_comment|/* $Id: dsp_tst.h,v 1.1.2.2 2002/10/02 14:38:37 armin Exp $ */
macro_line|#ifndef __DIVA_PRI_HOST_TEST_DSPS_H__
DECL|macro|__DIVA_PRI_HOST_TEST_DSPS_H__
mdefine_line|#define __DIVA_PRI_HOST_TEST_DSPS_H__
multiline_comment|/*&n;   DSP registers on maestra pri&n;   */
DECL|macro|DSP1_PORT
mdefine_line|#define DSP1_PORT       (0x00)
DECL|macro|DSP2_PORT
mdefine_line|#define DSP2_PORT       (0x8)
DECL|macro|DSP3_PORT
mdefine_line|#define DSP3_PORT       (0x800)
DECL|macro|DSP4_PORT
mdefine_line|#define DSP4_PORT       (0x808)
DECL|macro|DSP5_PORT
mdefine_line|#define DSP5_PORT       (0x810)
DECL|macro|DSP6_PORT
mdefine_line|#define DSP6_PORT       (0x818)
DECL|macro|DSP7_PORT
mdefine_line|#define DSP7_PORT       (0x820)
DECL|macro|DSP8_PORT
mdefine_line|#define DSP8_PORT       (0x828)
DECL|macro|DSP9_PORT
mdefine_line|#define DSP9_PORT       (0x830)
DECL|macro|DSP10_PORT
mdefine_line|#define DSP10_PORT      (0x840)
DECL|macro|DSP11_PORT
mdefine_line|#define DSP11_PORT      (0x848)
DECL|macro|DSP12_PORT
mdefine_line|#define DSP12_PORT      (0x850)
DECL|macro|DSP13_PORT
mdefine_line|#define DSP13_PORT      (0x858)        
DECL|macro|DSP14_PORT
mdefine_line|#define DSP14_PORT      (0x860)
DECL|macro|DSP15_PORT
mdefine_line|#define DSP15_PORT      (0x868)
DECL|macro|DSP16_PORT
mdefine_line|#define DSP16_PORT      (0x870)
DECL|macro|DSP17_PORT
mdefine_line|#define DSP17_PORT      (0x1000)
DECL|macro|DSP18_PORT
mdefine_line|#define DSP18_PORT      (0x1008)
DECL|macro|DSP19_PORT
mdefine_line|#define DSP19_PORT      (0x1010)
DECL|macro|DSP20_PORT
mdefine_line|#define DSP20_PORT      (0x1018)
DECL|macro|DSP21_PORT
mdefine_line|#define DSP21_PORT      (0x1020)
DECL|macro|DSP22_PORT
mdefine_line|#define DSP22_PORT      (0x1028)
DECL|macro|DSP23_PORT
mdefine_line|#define DSP23_PORT      (0x1030)
DECL|macro|DSP24_PORT
mdefine_line|#define DSP24_PORT      (0x1040)
DECL|macro|DSP25_PORT
mdefine_line|#define DSP25_PORT      (0x1048)
DECL|macro|DSP26_PORT
mdefine_line|#define DSP26_PORT      (0x1050)
DECL|macro|DSP27_PORT
mdefine_line|#define DSP27_PORT      (0x1058)
DECL|macro|DSP28_PORT
mdefine_line|#define DSP28_PORT      (0x1060)
DECL|macro|DSP29_PORT
mdefine_line|#define DSP29_PORT      (0x1068)
DECL|macro|DSP30_PORT
mdefine_line|#define DSP30_PORT      (0x1070)
DECL|macro|DSP_ADR_OFFS
mdefine_line|#define DSP_ADR_OFFS    0x80
multiline_comment|/*------------------------------------------------------------------&n;&t;&t;Dsp related definitions&n;  ------------------------------------------------------------------ */
DECL|macro|DSP_SIGNATURE_PROBE_WORD
mdefine_line|#define DSP_SIGNATURE_PROBE_WORD 0x5a5a
DECL|macro|dsp_make_address_ex
mdefine_line|#define dsp_make_address_ex(pm,address) ((word)((pm) ? (address) : (address) + 0x4000))
macro_line|#endif
eof
