singleline_comment|// $Id: hfc48scu.h,v 1.1 2004/03/11 16:11:51 martinb1 Exp $
singleline_comment|// $Revision: 1.1 $
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
singleline_comment|//  (C) Copyright Cologne Chip AG, 2003                                              //
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
singleline_comment|//  File name:     HFC48Scu.h                                                        //
singleline_comment|//  File content:  This file contains the HFC-4S and HFC-8S register definitions.    //
singleline_comment|//  Creation date: 03rd of February 2003                                             //
singleline_comment|//  Creator:       GENERO V1.3                                                       //
singleline_comment|//  Data base:     HFC-XML V1.4                                                      //
singleline_comment|//  File Revision: 1.1                                                               //
singleline_comment|//                                                                                   //
singleline_comment|//  The information presented can not be considered as assured characteristics.      //
singleline_comment|//  Data can change without notice. Please check version numbers in case of doubt.   //
singleline_comment|//                                                                                   //
singleline_comment|//  For further information or questions please contact                              //
singleline_comment|//  support@CologneChip.com                                                          //
singleline_comment|//                                                                                   //
singleline_comment|//  See below for examples how to use this file.                                     //
singleline_comment|//                                                                                   //
singleline_comment|//                                                                                   //
singleline_comment|//                                                                                   //
singleline_comment|//           _____________________________________________________________           //
singleline_comment|//                                                                                   //
singleline_comment|//             This file has beta status. It is still under investigation.           //
singleline_comment|//             We have tried to fulfil common user requirements.                     //
singleline_comment|//                                                                                   //
singleline_comment|//             We&squot;d be pleased about feedback for any suggestions to                 //
singleline_comment|//             improve this header file for our customer&squot;s use.                      //
singleline_comment|//           _____________________________________________________________           //
singleline_comment|//                                                                                   //
singleline_comment|//                                                                                   //
singleline_comment|//                                                                                   //
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
singleline_comment|//  WARNING: This file has been generated automatically and should not be            //
singleline_comment|//           changed to maintain compatibility with later versions.                  //
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
macro_line|#ifndef HFC_4S_8S_cu
DECL|macro|HFC_4S_8S_cu
mdefine_line|#define HFC_4S_8S_cu
DECL|typedef|BYTE
r_typedef
r_int
r_char
id|BYTE
suffix:semicolon
DECL|typedef|REGWORD
r_typedef
id|BYTE
id|REGWORD
suffix:semicolon
singleline_comment|// chip dependend maximum register length
DECL|typedef|REGWORD16
r_typedef
r_int
r_int
id|REGWORD16
suffix:semicolon
singleline_comment|// chip dependend maximum register length
DECL|typedef|REGWORD32
r_typedef
r_int
r_int
id|REGWORD32
suffix:semicolon
singleline_comment|// chip dependend maximum register length
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
singleline_comment|//  HFC48Scu.h usage:                                                                //
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
singleline_comment|// How can this header file be used? The main idea is, to have names not only for    //
singleline_comment|// registers but also for every bitmap. The concept allows Bitmap access without     //
singleline_comment|// shifting the values to their real position.                                       //
singleline_comment|//                                                                                   //
singleline_comment|// Every bitmap V_.. has a mask named M_.. where all mask bits are set.              //
singleline_comment|// If a bitmap has a length of more than 1 bit but less than the register width,     //
singleline_comment|// there are supplementary mask-values for every valid value, i.e. M1_.., M2_..,     //
singleline_comment|// .., M&lt;max&gt;_..                                                                     //
singleline_comment|//                                                                                   //
singleline_comment|// In the following examples a procedure                                             //
singleline_comment|//    writereg(BYTE port, REGWORD val)  // writes val into port                      //
singleline_comment|//                                                                                   //
singleline_comment|// is used. This must be implemented by the user.                                    //
singleline_comment|//                                                                                   //
singleline_comment|// For all examples the register A_CONF has been choosen.                            //
singleline_comment|//                                                                                   //
singleline_comment|// 1. Approach: access without variable                                              //
singleline_comment|// ------------------------------------                                              //
singleline_comment|//                                                                                   //
singleline_comment|//     writereg(A_CONF, M3_CONF_NUM | M_CONF_EN); // initialisation: selected PCM    //
singleline_comment|//                                                // time slot added to conference   //
singleline_comment|//                                                // #3 without noise suppr. and     //
singleline_comment|//                                                // 0 dB atten. level               //
singleline_comment|//                                                                                   //
singleline_comment|//     // ...                                                                        //
singleline_comment|//                                                                                   //
singleline_comment|//     a_conf.reg = M3_CONF_NUM | M_CONF_EN | M1_ATT_LEV | M3_NOISE_SUPPR;           //
singleline_comment|//                                                // changing the settings: -3 dB    //
singleline_comment|//                                                // atten. level and strong noise   //
singleline_comment|//                                                // suppression                     //
singleline_comment|//                                                                                   //
singleline_comment|// When calculating bitmap values, please note, that incrementation / decrementation //
singleline_comment|// must be done with m1_.. value! One must take care that a bitmap value is always   //
singleline_comment|// in the range 0 &lt;= v_.. &lt;= M_..                                                    //
singleline_comment|//                                                                                   //
singleline_comment|// This 1st approach has the advantage that it needs no variable. But if read-back   //
singleline_comment|// functionality is required the next technique should be used.                      //
singleline_comment|//                                                                                   //
singleline_comment|// 2. Approach: access with read-back functionallity                                 //
singleline_comment|// -------------------------------------------------                                 //
singleline_comment|//                                                                                   //
singleline_comment|//     reg_a_conf a_conf; // declaration of chip variable                            //
singleline_comment|//                                                                                   //
singleline_comment|//     a_conf.bit.v_conf_num = 3;    // initialization,                              //
singleline_comment|//     a_conf.bit.v_noise_suppr = 0; // same values as above                         //
singleline_comment|//     a_conf.bit.v_att_lev = 0;     //                                              //
singleline_comment|//     a_conf.bit.v_conf_en = 1;     //                                              //
singleline_comment|//                                                                                   //
singleline_comment|//     writereg(A_CONF, a_conf.reg); // value transfer into the register             //
singleline_comment|//                                                                                   //
singleline_comment|//     Now it is possible to change one or more bitmaps:                             //
singleline_comment|//                                                                                   //
singleline_comment|//     a_conf.bit.v_noise_suppr = m_att_lev; // strongest noise suppr. (same as      //
singleline_comment|//                                           // m3_att_lev)                          //
singleline_comment|//     a_conf.bit.v_att_lev = m1_att_lev; // -3 dB atten. level                      //
singleline_comment|//                                                                                   //
singleline_comment|//     a_conf.reg = a_conf.reg; // value transfer into the register                  //
singleline_comment|//                                                                                   //
singleline_comment|//___________________________________________________________________________________//
singleline_comment|///////////////////////////////////////////////////////////////////////////////////////
singleline_comment|// common data definition
singleline_comment|///////////////////////////////////////////////////////////////////////////////////////
singleline_comment|// chip information:
DECL|macro|CHIP_NAME_4S
mdefine_line|#define CHIP_NAME_4S &quot;HFC-4S&quot;
DECL|macro|CHIP_NAME_8S
mdefine_line|#define CHIP_NAME_8S &quot;HFC-8S&quot;
DECL|macro|CHIP_TITLE_4S
mdefine_line|#define CHIP_TITLE_4S &quot;ISDN HDLC FIFO controller with 4 S/T interfaces&quot;
DECL|macro|CHIP_TITLE_8S
mdefine_line|#define CHIP_TITLE_8S &quot;ISDN HDLC FIFO controller with 8 S/T interfaces&quot;
DECL|macro|CHIP_MANUFACTURER
mdefine_line|#define CHIP_MANUFACTURER &quot;CologneChip&quot;
DECL|macro|CHIP_ID_4S
mdefine_line|#define CHIP_ID_4S 0x0C
DECL|macro|CHIP_ID_8S
mdefine_line|#define CHIP_ID_8S 0x08
DECL|macro|CHIP_ID_SHIFT
mdefine_line|#define CHIP_ID_SHIFT 4
DECL|macro|CHIP_REGISTER_COUNT
mdefine_line|#define CHIP_REGISTER_COUNT 124
DECL|macro|CHIP_DATABASE
mdefine_line|#define CHIP_DATABASE &quot;&quot;
singleline_comment|// PCI configuration:
DECL|macro|PCI_VENDOR_ID_CCD
mdefine_line|#define PCI_VENDOR_ID_CCD 0x1397
DECL|macro|PCI_DEVICE_ID_4S
mdefine_line|#define PCI_DEVICE_ID_4S 0x08B4
DECL|macro|PCI_DEVICE_ID_8S
mdefine_line|#define PCI_DEVICE_ID_8S 0x16B8
DECL|macro|PCI_REVISION_ID_4S
mdefine_line|#define PCI_REVISION_ID_4S 0x01
DECL|macro|PCI_REVISION_ID_8S
mdefine_line|#define PCI_REVISION_ID_8S 0x01
singleline_comment|///////////////////////////////////////////////////////////////////////////////////////
singleline_comment|// begin of register list
singleline_comment|///////////////////////////////////////////////////////////////////////////////////////
DECL|macro|R_IRQ_STATECH
mdefine_line|#define R_IRQ_STATECH 0x12
DECL|macro|M_STATECH_ST0
mdefine_line|#define M_STATECH_ST0 0x01
DECL|macro|M_STATECH_ST1
mdefine_line|#define M_STATECH_ST1 0x02
DECL|macro|M_STATECH_ST2
mdefine_line|#define M_STATECH_ST2 0x04
DECL|macro|M_STATECH_ST3
mdefine_line|#define M_STATECH_ST3 0x08
DECL|macro|M_STATECH_ST4
mdefine_line|#define M_STATECH_ST4 0x10
DECL|macro|M_STATECH_ST5
mdefine_line|#define M_STATECH_ST5 0x20
DECL|macro|M_STATECH_ST6
mdefine_line|#define M_STATECH_ST6 0x40
DECL|macro|M_STATECH_ST7
mdefine_line|#define M_STATECH_ST7 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_statech_st0
id|REGWORD
id|v_statech_st0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_statech_st1
id|REGWORD
id|v_statech_st1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_statech_st2
id|REGWORD
id|v_statech_st2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_statech_st3
id|REGWORD
id|v_statech_st3
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_statech_st4
id|REGWORD
id|v_statech_st4
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_statech_st5
id|REGWORD
id|v_statech_st5
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_statech_st6
id|REGWORD
id|v_statech_st6
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_statech_st7
id|REGWORD
id|v_statech_st7
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_irq_statech
)brace
id|bit_r_irq_statech
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_irq_statech
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_irq_statech
id|bit
suffix:semicolon
)brace
id|reg_r_irq_statech
suffix:semicolon
singleline_comment|// register and bitmap access
DECL|macro|R_IRQMSK_STATCHG
mdefine_line|#define R_IRQMSK_STATCHG 0x12
DECL|macro|M_IRQMSK_STACHG_ST0
mdefine_line|#define M_IRQMSK_STACHG_ST0 0x01
DECL|macro|M_IRQMSK_STACHG_ST1
mdefine_line|#define M_IRQMSK_STACHG_ST1 0x02
DECL|macro|M_IRQMSK_STACHG_ST2
mdefine_line|#define M_IRQMSK_STACHG_ST2 0x04
DECL|macro|M_IRQMSK_STACHG_ST3
mdefine_line|#define M_IRQMSK_STACHG_ST3 0x08
DECL|macro|M_IRQMSK_STACHG_ST4
mdefine_line|#define M_IRQMSK_STACHG_ST4 0x10
DECL|macro|M_IRQMSK_STACHG_ST5
mdefine_line|#define M_IRQMSK_STACHG_ST5 0x20
DECL|macro|M_IRQMSK_STACHG_ST6
mdefine_line|#define M_IRQMSK_STACHG_ST6 0x40
DECL|macro|M_IRQMSK_STACHG_ST7
mdefine_line|#define M_IRQMSK_STACHG_ST7 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_irqmsk_stachg_st0
id|REGWORD
id|v_irqmsk_stachg_st0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irqmsk_stachg_st1
id|REGWORD
id|v_irqmsk_stachg_st1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irqmsk_stachg_st2
id|REGWORD
id|v_irqmsk_stachg_st2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irqmsk_stachg_st3
id|REGWORD
id|v_irqmsk_stachg_st3
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irqmsk_stachg_st4
id|REGWORD
id|v_irqmsk_stachg_st4
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irqmsk_stachg_st5
id|REGWORD
id|v_irqmsk_stachg_st5
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irqmsk_stachg_st6
id|REGWORD
id|v_irqmsk_stachg_st6
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irqmsk_stachg_st7
id|REGWORD
id|v_irqmsk_stachg_st7
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_irqmsk_statchg
)brace
id|bit_r_irqmsk_statchg
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_irqmsk_statchg
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_irqmsk_statchg
id|bit
suffix:semicolon
)brace
id|reg_r_irqmsk_statchg
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_ST_SEL
mdefine_line|#define R_ST_SEL 0x16
DECL|macro|M_ST_SEL
mdefine_line|#define M_ST_SEL 0x07
DECL|macro|M1_ST_SEL
mdefine_line|#define M1_ST_SEL 0x01
DECL|macro|M2_ST_SEL
mdefine_line|#define M2_ST_SEL 0x02
DECL|macro|M3_ST_SEL
mdefine_line|#define M3_ST_SEL 0x03
DECL|macro|M4_ST_SEL
mdefine_line|#define M4_ST_SEL 0x04
DECL|macro|M5_ST_SEL
mdefine_line|#define M5_ST_SEL 0x05
DECL|macro|M6_ST_SEL
mdefine_line|#define M6_ST_SEL 0x06
DECL|macro|M7_ST_SEL
mdefine_line|#define M7_ST_SEL 0x07
DECL|macro|M_MULT_ST
mdefine_line|#define M_MULT_ST 0x08
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_st_sel
id|REGWORD
id|v_st_sel
suffix:colon
l_int|3
suffix:semicolon
DECL|member|v_mult_st
id|REGWORD
id|v_mult_st
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_0
id|REGWORD
id|reserved_0
suffix:colon
l_int|4
suffix:semicolon
DECL|typedef|bit_r_st_sel
)brace
id|bit_r_st_sel
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_st_sel
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_st_sel
id|bit
suffix:semicolon
)brace
id|reg_r_st_sel
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_ST_SYNC
mdefine_line|#define R_ST_SYNC 0x17
DECL|macro|M_SYNC_SEL
mdefine_line|#define M_SYNC_SEL 0x07
DECL|macro|M1_SYNC_SEL
mdefine_line|#define M1_SYNC_SEL 0x01
DECL|macro|M2_SYNC_SEL
mdefine_line|#define M2_SYNC_SEL 0x02
DECL|macro|M3_SYNC_SEL
mdefine_line|#define M3_SYNC_SEL 0x03
DECL|macro|M4_SYNC_SEL
mdefine_line|#define M4_SYNC_SEL 0x04
DECL|macro|M5_SYNC_SEL
mdefine_line|#define M5_SYNC_SEL 0x05
DECL|macro|M6_SYNC_SEL
mdefine_line|#define M6_SYNC_SEL 0x06
DECL|macro|M7_SYNC_SEL
mdefine_line|#define M7_SYNC_SEL 0x07
DECL|macro|M_AUTO_SYNC
mdefine_line|#define M_AUTO_SYNC 0x08
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_sync_sel
id|REGWORD
id|v_sync_sel
suffix:colon
l_int|3
suffix:semicolon
DECL|member|v_auto_sync
id|REGWORD
id|v_auto_sync
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_1
id|REGWORD
id|reserved_1
suffix:colon
l_int|4
suffix:semicolon
DECL|typedef|bit_r_st_sync
)brace
id|bit_r_st_sync
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_st_sync
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_st_sync
id|bit
suffix:semicolon
)brace
id|reg_r_st_sync
suffix:semicolon
singleline_comment|// register and bitmap access
DECL|macro|A_ST_RD_STA
mdefine_line|#define A_ST_RD_STA 0x30
DECL|macro|M_ST_STA
mdefine_line|#define M_ST_STA 0x0F
DECL|macro|M1_ST_STA
mdefine_line|#define M1_ST_STA 0x01
DECL|macro|M2_ST_STA
mdefine_line|#define M2_ST_STA 0x02
DECL|macro|M3_ST_STA
mdefine_line|#define M3_ST_STA 0x03
DECL|macro|M4_ST_STA
mdefine_line|#define M4_ST_STA 0x04
DECL|macro|M5_ST_STA
mdefine_line|#define M5_ST_STA 0x05
DECL|macro|M6_ST_STA
mdefine_line|#define M6_ST_STA 0x06
DECL|macro|M7_ST_STA
mdefine_line|#define M7_ST_STA 0x07
DECL|macro|M8_ST_STA
mdefine_line|#define M8_ST_STA 0x08
DECL|macro|M9_ST_STA
mdefine_line|#define M9_ST_STA 0x09
DECL|macro|M10_ST_STA
mdefine_line|#define M10_ST_STA 0x0A
DECL|macro|M11_ST_STA
mdefine_line|#define M11_ST_STA 0x0B
DECL|macro|M12_ST_STA
mdefine_line|#define M12_ST_STA 0x0C
DECL|macro|M13_ST_STA
mdefine_line|#define M13_ST_STA 0x0D
DECL|macro|M14_ST_STA
mdefine_line|#define M14_ST_STA 0x0E
DECL|macro|M15_ST_STA
mdefine_line|#define M15_ST_STA 0x0F
DECL|macro|M_FR_SYNC
mdefine_line|#define M_FR_SYNC 0x10
DECL|macro|M_TI2_EXP
mdefine_line|#define M_TI2_EXP 0x20
DECL|macro|M_INFO0
mdefine_line|#define M_INFO0 0x40
DECL|macro|M_G2_G3
mdefine_line|#define M_G2_G3 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_st_sta
id|REGWORD
id|v_st_sta
suffix:colon
l_int|4
suffix:semicolon
DECL|member|v_fr_sync
id|REGWORD
id|v_fr_sync
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_ti2_exp
id|REGWORD
id|v_ti2_exp
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_info0
id|REGWORD
id|v_info0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_g2_g3
id|REGWORD
id|v_g2_g3
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_a_st_rd_sta
)brace
id|bit_a_st_rd_sta
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_st_rd_sta
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_st_rd_sta
id|bit
suffix:semicolon
)brace
id|reg_a_st_rd_sta
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_ST_SQ_RD
mdefine_line|#define A_ST_SQ_RD 0x34
DECL|macro|M_ST_SQ
mdefine_line|#define M_ST_SQ 0x0F
DECL|macro|M1_ST_SQ
mdefine_line|#define M1_ST_SQ 0x01
DECL|macro|M2_ST_SQ
mdefine_line|#define M2_ST_SQ 0x02
DECL|macro|M3_ST_SQ
mdefine_line|#define M3_ST_SQ 0x03
DECL|macro|M4_ST_SQ
mdefine_line|#define M4_ST_SQ 0x04
DECL|macro|M5_ST_SQ
mdefine_line|#define M5_ST_SQ 0x05
DECL|macro|M6_ST_SQ
mdefine_line|#define M6_ST_SQ 0x06
DECL|macro|M7_ST_SQ
mdefine_line|#define M7_ST_SQ 0x07
DECL|macro|M8_ST_SQ
mdefine_line|#define M8_ST_SQ 0x08
DECL|macro|M9_ST_SQ
mdefine_line|#define M9_ST_SQ 0x09
DECL|macro|M10_ST_SQ
mdefine_line|#define M10_ST_SQ 0x0A
DECL|macro|M11_ST_SQ
mdefine_line|#define M11_ST_SQ 0x0B
DECL|macro|M12_ST_SQ
mdefine_line|#define M12_ST_SQ 0x0C
DECL|macro|M13_ST_SQ
mdefine_line|#define M13_ST_SQ 0x0D
DECL|macro|M14_ST_SQ
mdefine_line|#define M14_ST_SQ 0x0E
DECL|macro|M15_ST_SQ
mdefine_line|#define M15_ST_SQ 0x0F
DECL|macro|M_MF_RX_RDY
mdefine_line|#define M_MF_RX_RDY 0x10
DECL|macro|M_MF_TX_RDY
mdefine_line|#define M_MF_TX_RDY 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_st_sq
id|REGWORD
id|v_st_sq
suffix:colon
l_int|4
suffix:semicolon
DECL|member|v_mf_rx_rdy
id|REGWORD
id|v_mf_rx_rdy
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_2
id|REGWORD
id|reserved_2
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_mf_tx_rdy
id|REGWORD
id|v_mf_tx_rdy
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_a_st_sq_rd
)brace
id|bit_a_st_sq_rd
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_st_sq_rd
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_st_sq_rd
id|bit
suffix:semicolon
)brace
id|reg_a_st_sq_rd
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_ST_B1_RX
mdefine_line|#define A_ST_B1_RX 0x3C
DECL|macro|M_ST_B1_RX
mdefine_line|#define M_ST_B1_RX 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_st_b1_rx
id|REGWORD
id|v_st_b1_rx
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_a_st_b1_rx
)brace
id|bit_a_st_b1_rx
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_st_b1_rx
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_st_b1_rx
id|bit
suffix:semicolon
)brace
id|reg_a_st_b1_rx
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_ST_B2_RX
mdefine_line|#define A_ST_B2_RX 0x3D
DECL|macro|M_ST_B2_RX
mdefine_line|#define M_ST_B2_RX 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_st_b2_rx
id|REGWORD
id|v_st_b2_rx
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_a_st_b2_rx
)brace
id|bit_a_st_b2_rx
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_st_b2_rx
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_st_b2_rx
id|bit
suffix:semicolon
)brace
id|reg_a_st_b2_rx
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_ST_D_RX
mdefine_line|#define A_ST_D_RX 0x3E
DECL|macro|M_ST_D_RX
mdefine_line|#define M_ST_D_RX 0xC0
DECL|macro|M1_ST_D_RX
mdefine_line|#define M1_ST_D_RX 0x40
DECL|macro|M2_ST_D_RX
mdefine_line|#define M2_ST_D_RX 0x80
DECL|macro|M3_ST_D_RX
mdefine_line|#define M3_ST_D_RX 0xC0
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|reserved_3
id|REGWORD
id|reserved_3
suffix:colon
l_int|6
suffix:semicolon
DECL|member|v_st_d_rx
id|REGWORD
id|v_st_d_rx
suffix:colon
l_int|2
suffix:semicolon
DECL|typedef|bit_a_st_d_rx
)brace
id|bit_a_st_d_rx
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_st_d_rx
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_st_d_rx
id|bit
suffix:semicolon
)brace
id|reg_a_st_d_rx
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_ST_E_RX
mdefine_line|#define A_ST_E_RX 0x3F
DECL|macro|M_ST_E_RX
mdefine_line|#define M_ST_E_RX 0xC0
DECL|macro|M1_ST_E_RX
mdefine_line|#define M1_ST_E_RX 0x40
DECL|macro|M2_ST_E_RX
mdefine_line|#define M2_ST_E_RX 0x80
DECL|macro|M3_ST_E_RX
mdefine_line|#define M3_ST_E_RX 0xC0
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|reserved_4
id|REGWORD
id|reserved_4
suffix:colon
l_int|6
suffix:semicolon
DECL|member|v_st_e_rx
id|REGWORD
id|v_st_e_rx
suffix:colon
l_int|2
suffix:semicolon
DECL|typedef|bit_a_st_e_rx
)brace
id|bit_a_st_e_rx
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_st_e_rx
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_st_e_rx
id|bit
suffix:semicolon
)brace
id|reg_a_st_e_rx
suffix:semicolon
singleline_comment|// register and bitmap access
DECL|macro|A_ST_WR_STA
mdefine_line|#define A_ST_WR_STA 0x30
DECL|macro|M_ST_SET_STA
mdefine_line|#define M_ST_SET_STA 0x0F
DECL|macro|M1_ST_SET_STA
mdefine_line|#define M1_ST_SET_STA 0x01
DECL|macro|M2_ST_SET_STA
mdefine_line|#define M2_ST_SET_STA 0x02
DECL|macro|M3_ST_SET_STA
mdefine_line|#define M3_ST_SET_STA 0x03
DECL|macro|M4_ST_SET_STA
mdefine_line|#define M4_ST_SET_STA 0x04
DECL|macro|M5_ST_SET_STA
mdefine_line|#define M5_ST_SET_STA 0x05
DECL|macro|M6_ST_SET_STA
mdefine_line|#define M6_ST_SET_STA 0x06
DECL|macro|M7_ST_SET_STA
mdefine_line|#define M7_ST_SET_STA 0x07
DECL|macro|M8_ST_SET_STA
mdefine_line|#define M8_ST_SET_STA 0x08
DECL|macro|M9_ST_SET_STA
mdefine_line|#define M9_ST_SET_STA 0x09
DECL|macro|M10_ST_SET_STA
mdefine_line|#define M10_ST_SET_STA 0x0A
DECL|macro|M11_ST_SET_STA
mdefine_line|#define M11_ST_SET_STA 0x0B
DECL|macro|M12_ST_SET_STA
mdefine_line|#define M12_ST_SET_STA 0x0C
DECL|macro|M13_ST_SET_STA
mdefine_line|#define M13_ST_SET_STA 0x0D
DECL|macro|M14_ST_SET_STA
mdefine_line|#define M14_ST_SET_STA 0x0E
DECL|macro|M15_ST_SET_STA
mdefine_line|#define M15_ST_SET_STA 0x0F
DECL|macro|M_ST_LD_STA
mdefine_line|#define M_ST_LD_STA 0x10
DECL|macro|M_ST_ACT
mdefine_line|#define M_ST_ACT 0x60
DECL|macro|M1_ST_ACT
mdefine_line|#define M1_ST_ACT 0x20
DECL|macro|M2_ST_ACT
mdefine_line|#define M2_ST_ACT 0x40
DECL|macro|M3_ST_ACT
mdefine_line|#define M3_ST_ACT 0x60
DECL|macro|M_SET_G2_G3
mdefine_line|#define M_SET_G2_G3 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_st_set_sta
id|REGWORD
id|v_st_set_sta
suffix:colon
l_int|4
suffix:semicolon
DECL|member|v_st_ld_sta
id|REGWORD
id|v_st_ld_sta
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_st_act
id|REGWORD
id|v_st_act
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_set_g2_g3
id|REGWORD
id|v_set_g2_g3
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_a_st_wr_sta
)brace
id|bit_a_st_wr_sta
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_st_wr_sta
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_st_wr_sta
id|bit
suffix:semicolon
)brace
id|reg_a_st_wr_sta
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_ST_CTRL0
mdefine_line|#define A_ST_CTRL0 0x31
DECL|macro|M_B1_EN
mdefine_line|#define M_B1_EN 0x01
DECL|macro|M_B2_EN
mdefine_line|#define M_B2_EN 0x02
DECL|macro|M_ST_MD
mdefine_line|#define M_ST_MD 0x04
DECL|macro|M_D_PRIO
mdefine_line|#define M_D_PRIO 0x08
DECL|macro|M_SQ_EN
mdefine_line|#define M_SQ_EN 0x10
DECL|macro|M_96KHZ
mdefine_line|#define M_96KHZ 0x20
DECL|macro|M_TX_LI
mdefine_line|#define M_TX_LI 0x40
DECL|macro|M_ST_STOP
mdefine_line|#define M_ST_STOP 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_b1_en
id|REGWORD
id|v_b1_en
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_b2_en
id|REGWORD
id|v_b2_en
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_st_md
id|REGWORD
id|v_st_md
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_d_prio
id|REGWORD
id|v_d_prio
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_sq_en
id|REGWORD
id|v_sq_en
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_96khz
id|REGWORD
id|v_96khz
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_tx_li
id|REGWORD
id|v_tx_li
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_st_stop
id|REGWORD
id|v_st_stop
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_a_st_ctrl0
)brace
id|bit_a_st_ctrl0
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_st_ctrl0
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_st_ctrl0
id|bit
suffix:semicolon
)brace
id|reg_a_st_ctrl0
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_ST_CTRL1
mdefine_line|#define A_ST_CTRL1 0x32
DECL|macro|M_G2_G3_EN
mdefine_line|#define M_G2_G3_EN 0x01
DECL|macro|M_D_HI
mdefine_line|#define M_D_HI 0x04
DECL|macro|M_E_IGNO
mdefine_line|#define M_E_IGNO 0x08
DECL|macro|M_E_LO
mdefine_line|#define M_E_LO 0x10
DECL|macro|M_B12_SWAP
mdefine_line|#define M_B12_SWAP 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_g2_g3_en
id|REGWORD
id|v_g2_g3_en
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_5
id|REGWORD
id|reserved_5
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_d_hi
id|REGWORD
id|v_d_hi
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_e_igno
id|REGWORD
id|v_e_igno
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_e_lo
id|REGWORD
id|v_e_lo
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_6
id|REGWORD
id|reserved_6
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_b12_swap
id|REGWORD
id|v_b12_swap
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_a_st_ctrl1
)brace
id|bit_a_st_ctrl1
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_st_ctrl1
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_st_ctrl1
id|bit
suffix:semicolon
)brace
id|reg_a_st_ctrl1
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_ST_CTRL2
mdefine_line|#define A_ST_CTRL2 0x33
DECL|macro|M_B1_RX_EN
mdefine_line|#define M_B1_RX_EN 0x01
DECL|macro|M_B2_RX_EN
mdefine_line|#define M_B2_RX_EN 0x02
DECL|macro|M_ST_TRIS
mdefine_line|#define M_ST_TRIS 0x40
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_b1_rx_en
id|REGWORD
id|v_b1_rx_en
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_b2_rx_en
id|REGWORD
id|v_b2_rx_en
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_7
id|REGWORD
id|reserved_7
suffix:colon
l_int|4
suffix:semicolon
DECL|member|v_st_tris
id|REGWORD
id|v_st_tris
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_8
id|REGWORD
id|reserved_8
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_a_st_ctrl2
)brace
id|bit_a_st_ctrl2
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_st_ctrl2
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_st_ctrl2
id|bit
suffix:semicolon
)brace
id|reg_a_st_ctrl2
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_ST_SQ_WR
mdefine_line|#define A_ST_SQ_WR 0x34
DECL|macro|M_ST_SQ
mdefine_line|#define M_ST_SQ 0x0F
DECL|macro|M1_ST_SQ
mdefine_line|#define M1_ST_SQ 0x01
DECL|macro|M2_ST_SQ
mdefine_line|#define M2_ST_SQ 0x02
DECL|macro|M3_ST_SQ
mdefine_line|#define M3_ST_SQ 0x03
DECL|macro|M4_ST_SQ
mdefine_line|#define M4_ST_SQ 0x04
DECL|macro|M5_ST_SQ
mdefine_line|#define M5_ST_SQ 0x05
DECL|macro|M6_ST_SQ
mdefine_line|#define M6_ST_SQ 0x06
DECL|macro|M7_ST_SQ
mdefine_line|#define M7_ST_SQ 0x07
DECL|macro|M8_ST_SQ
mdefine_line|#define M8_ST_SQ 0x08
DECL|macro|M9_ST_SQ
mdefine_line|#define M9_ST_SQ 0x09
DECL|macro|M10_ST_SQ
mdefine_line|#define M10_ST_SQ 0x0A
DECL|macro|M11_ST_SQ
mdefine_line|#define M11_ST_SQ 0x0B
DECL|macro|M12_ST_SQ
mdefine_line|#define M12_ST_SQ 0x0C
DECL|macro|M13_ST_SQ
mdefine_line|#define M13_ST_SQ 0x0D
DECL|macro|M14_ST_SQ
mdefine_line|#define M14_ST_SQ 0x0E
DECL|macro|M15_ST_SQ
mdefine_line|#define M15_ST_SQ 0x0F
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_st_sq
id|REGWORD
id|v_st_sq
suffix:colon
l_int|4
suffix:semicolon
DECL|member|reserved_9
id|REGWORD
id|reserved_9
suffix:colon
l_int|4
suffix:semicolon
DECL|typedef|bit_a_st_sq_wr
)brace
id|bit_a_st_sq_wr
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_st_sq_wr
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_st_sq_wr
id|bit
suffix:semicolon
)brace
id|reg_a_st_sq_wr
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_ST_CLK_DLY
mdefine_line|#define A_ST_CLK_DLY 0x37
DECL|macro|M_ST_CLK_DLY
mdefine_line|#define M_ST_CLK_DLY 0x0F
DECL|macro|M1_ST_CLK_DLY
mdefine_line|#define M1_ST_CLK_DLY 0x01
DECL|macro|M2_ST_CLK_DLY
mdefine_line|#define M2_ST_CLK_DLY 0x02
DECL|macro|M3_ST_CLK_DLY
mdefine_line|#define M3_ST_CLK_DLY 0x03
DECL|macro|M4_ST_CLK_DLY
mdefine_line|#define M4_ST_CLK_DLY 0x04
DECL|macro|M5_ST_CLK_DLY
mdefine_line|#define M5_ST_CLK_DLY 0x05
DECL|macro|M6_ST_CLK_DLY
mdefine_line|#define M6_ST_CLK_DLY 0x06
DECL|macro|M7_ST_CLK_DLY
mdefine_line|#define M7_ST_CLK_DLY 0x07
DECL|macro|M8_ST_CLK_DLY
mdefine_line|#define M8_ST_CLK_DLY 0x08
DECL|macro|M9_ST_CLK_DLY
mdefine_line|#define M9_ST_CLK_DLY 0x09
DECL|macro|M10_ST_CLK_DLY
mdefine_line|#define M10_ST_CLK_DLY 0x0A
DECL|macro|M11_ST_CLK_DLY
mdefine_line|#define M11_ST_CLK_DLY 0x0B
DECL|macro|M12_ST_CLK_DLY
mdefine_line|#define M12_ST_CLK_DLY 0x0C
DECL|macro|M13_ST_CLK_DLY
mdefine_line|#define M13_ST_CLK_DLY 0x0D
DECL|macro|M14_ST_CLK_DLY
mdefine_line|#define M14_ST_CLK_DLY 0x0E
DECL|macro|M15_ST_CLK_DLY
mdefine_line|#define M15_ST_CLK_DLY 0x0F
DECL|macro|M_ST_SMPL
mdefine_line|#define M_ST_SMPL 0x70
DECL|macro|M1_ST_SMPL
mdefine_line|#define M1_ST_SMPL 0x10
DECL|macro|M2_ST_SMPL
mdefine_line|#define M2_ST_SMPL 0x20
DECL|macro|M3_ST_SMPL
mdefine_line|#define M3_ST_SMPL 0x30
DECL|macro|M4_ST_SMPL
mdefine_line|#define M4_ST_SMPL 0x40
DECL|macro|M5_ST_SMPL
mdefine_line|#define M5_ST_SMPL 0x50
DECL|macro|M6_ST_SMPL
mdefine_line|#define M6_ST_SMPL 0x60
DECL|macro|M7_ST_SMPL
mdefine_line|#define M7_ST_SMPL 0x70
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_st_clk_dly
id|REGWORD
id|v_st_clk_dly
suffix:colon
l_int|4
suffix:semicolon
DECL|member|v_st_smpl
id|REGWORD
id|v_st_smpl
suffix:colon
l_int|3
suffix:semicolon
DECL|member|reserved_10
id|REGWORD
id|reserved_10
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_a_st_clk_dly
)brace
id|bit_a_st_clk_dly
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_st_clk_dly
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_st_clk_dly
id|bit
suffix:semicolon
)brace
id|reg_a_st_clk_dly
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_ST_B1_TX
mdefine_line|#define A_ST_B1_TX 0x3C
DECL|macro|M_ST_B1_TX
mdefine_line|#define M_ST_B1_TX 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_st_b1_tx
id|REGWORD
id|v_st_b1_tx
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_a_st_b1_tx
)brace
id|bit_a_st_b1_tx
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_st_b1_tx
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_st_b1_tx
id|bit
suffix:semicolon
)brace
id|reg_a_st_b1_tx
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_ST_B2_TX
mdefine_line|#define A_ST_B2_TX 0x3D
DECL|macro|M_ST_B2_TX
mdefine_line|#define M_ST_B2_TX 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_st_b2_tx
id|REGWORD
id|v_st_b2_tx
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_a_st_b2_tx
)brace
id|bit_a_st_b2_tx
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_st_b2_tx
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_st_b2_tx
id|bit
suffix:semicolon
)brace
id|reg_a_st_b2_tx
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_ST_D_TX
mdefine_line|#define A_ST_D_TX 0x3E
DECL|macro|M_ST_D_TX
mdefine_line|#define M_ST_D_TX 0xC0
DECL|macro|M1_ST_D_TX
mdefine_line|#define M1_ST_D_TX 0x40
DECL|macro|M2_ST_D_TX
mdefine_line|#define M2_ST_D_TX 0x80
DECL|macro|M3_ST_D_TX
mdefine_line|#define M3_ST_D_TX 0xC0
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|reserved_11
id|REGWORD
id|reserved_11
suffix:colon
l_int|6
suffix:semicolon
DECL|member|v_st_d_tx
id|REGWORD
id|v_st_d_tx
suffix:colon
l_int|2
suffix:semicolon
DECL|typedef|bit_a_st_d_tx
)brace
id|bit_a_st_d_tx
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_st_d_tx
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_st_d_tx
id|bit
suffix:semicolon
)brace
id|reg_a_st_d_tx
suffix:semicolon
singleline_comment|// register and bitmap access
DECL|macro|A_CHANNEL
mdefine_line|#define A_CHANNEL 0xFC
DECL|macro|M_CH_DIR
mdefine_line|#define M_CH_DIR 0x01
DECL|macro|M_CH0_SEL
mdefine_line|#define M_CH0_SEL 0x3E
DECL|macro|M1_CH0_SEL
mdefine_line|#define M1_CH0_SEL 0x02
DECL|macro|M2_CH0_SEL
mdefine_line|#define M2_CH0_SEL 0x04
DECL|macro|M3_CH0_SEL
mdefine_line|#define M3_CH0_SEL 0x06
DECL|macro|M4_CH0_SEL
mdefine_line|#define M4_CH0_SEL 0x08
DECL|macro|M5_CH0_SEL
mdefine_line|#define M5_CH0_SEL 0x0A
DECL|macro|M6_CH0_SEL
mdefine_line|#define M6_CH0_SEL 0x0C
DECL|macro|M7_CH0_SEL
mdefine_line|#define M7_CH0_SEL 0x0E
DECL|macro|M8_CH0_SEL
mdefine_line|#define M8_CH0_SEL 0x10
DECL|macro|M9_CH0_SEL
mdefine_line|#define M9_CH0_SEL 0x12
DECL|macro|M10_CH0_SEL
mdefine_line|#define M10_CH0_SEL 0x14
DECL|macro|M11_CH0_SEL
mdefine_line|#define M11_CH0_SEL 0x16
DECL|macro|M12_CH0_SEL
mdefine_line|#define M12_CH0_SEL 0x18
DECL|macro|M13_CH0_SEL
mdefine_line|#define M13_CH0_SEL 0x1A
DECL|macro|M14_CH0_SEL
mdefine_line|#define M14_CH0_SEL 0x1C
DECL|macro|M15_CH0_SEL
mdefine_line|#define M15_CH0_SEL 0x1E
DECL|macro|M16_CH0_SEL
mdefine_line|#define M16_CH0_SEL 0x20
DECL|macro|M17_CH0_SEL
mdefine_line|#define M17_CH0_SEL 0x22
DECL|macro|M18_CH0_SEL
mdefine_line|#define M18_CH0_SEL 0x24
DECL|macro|M19_CH0_SEL
mdefine_line|#define M19_CH0_SEL 0x26
DECL|macro|M20_CH0_SEL
mdefine_line|#define M20_CH0_SEL 0x28
DECL|macro|M21_CH0_SEL
mdefine_line|#define M21_CH0_SEL 0x2A
DECL|macro|M22_CH0_SEL
mdefine_line|#define M22_CH0_SEL 0x2C
DECL|macro|M23_CH0_SEL
mdefine_line|#define M23_CH0_SEL 0x2E
DECL|macro|M24_CH0_SEL
mdefine_line|#define M24_CH0_SEL 0x30
DECL|macro|M25_CH0_SEL
mdefine_line|#define M25_CH0_SEL 0x32
DECL|macro|M26_CH0_SEL
mdefine_line|#define M26_CH0_SEL 0x34
DECL|macro|M27_CH0_SEL
mdefine_line|#define M27_CH0_SEL 0x36
DECL|macro|M28_CH0_SEL
mdefine_line|#define M28_CH0_SEL 0x38
DECL|macro|M29_CH0_SEL
mdefine_line|#define M29_CH0_SEL 0x3A
DECL|macro|M30_CH0_SEL
mdefine_line|#define M30_CH0_SEL 0x3C
DECL|macro|M31_CH0_SEL
mdefine_line|#define M31_CH0_SEL 0x3E
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_ch_dir
id|REGWORD
id|v_ch_dir
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_ch0_sel
id|REGWORD
id|v_ch0_sel
suffix:colon
l_int|5
suffix:semicolon
DECL|member|reserved_12
id|REGWORD
id|reserved_12
suffix:colon
l_int|2
suffix:semicolon
DECL|typedef|bit_a_channel
)brace
id|bit_a_channel
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_channel
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_channel
id|bit
suffix:semicolon
)brace
id|reg_a_channel
suffix:semicolon
singleline_comment|// register and bitmap access
DECL|macro|A_Z1L
mdefine_line|#define A_Z1L 0x04
DECL|macro|M_Z1L
mdefine_line|#define M_Z1L 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_z1l
id|REGWORD
id|v_z1l
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_a_z1l
)brace
id|bit_a_z1l
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_z1l
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_z1l
id|bit
suffix:semicolon
)brace
id|reg_a_z1l
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_Z1H
mdefine_line|#define A_Z1H 0x05
DECL|macro|M_Z1H
mdefine_line|#define M_Z1H 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_z1h
id|REGWORD
id|v_z1h
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_a_z1h
)brace
id|bit_a_z1h
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_z1h
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_z1h
id|bit
suffix:semicolon
)brace
id|reg_a_z1h
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_Z1
mdefine_line|#define A_Z1 0x04
DECL|macro|M_Z1
mdefine_line|#define M_Z1 0xFFFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_z1
id|REGWORD16
id|v_z1
suffix:colon
l_int|16
suffix:semicolon
DECL|typedef|bit_a_z1
)brace
id|bit_a_z1
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_z1
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_z1
id|bit
suffix:semicolon
)brace
id|reg_a_z1
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_Z2L
mdefine_line|#define A_Z2L 0x06
DECL|macro|M_Z2L
mdefine_line|#define M_Z2L 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_z2l
id|REGWORD
id|v_z2l
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_a_z2l
)brace
id|bit_a_z2l
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_z2l
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_z2l
id|bit
suffix:semicolon
)brace
id|reg_a_z2l
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_Z2H
mdefine_line|#define A_Z2H 0x07
DECL|macro|M_Z2H
mdefine_line|#define M_Z2H 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_z2h
id|REGWORD
id|v_z2h
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_a_z2h
)brace
id|bit_a_z2h
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_z2h
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_z2h
id|bit
suffix:semicolon
)brace
id|reg_a_z2h
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_Z2
mdefine_line|#define A_Z2 0x06
DECL|macro|M_Z2
mdefine_line|#define M_Z2 0xFFFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_z2
id|REGWORD16
id|v_z2
suffix:colon
l_int|16
suffix:semicolon
DECL|typedef|bit_a_z2
)brace
id|bit_a_z2
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_z2
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_z2
id|bit
suffix:semicolon
)brace
id|reg_a_z2
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_Z12
mdefine_line|#define A_Z12 0x04
DECL|macro|M_Z12
mdefine_line|#define M_Z12 0xFFFFFFFF
macro_line|#ifdef COMPILER_32BIT 
singleline_comment|// can be defined by user to allow 32 bit compiler mode
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_z12
id|REGWORD32
id|v_z12
suffix:colon
l_int|32
suffix:semicolon
DECL|typedef|bit_a_z12
)brace
id|bit_a_z12
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_z12
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_z12
id|bit
suffix:semicolon
)brace
id|reg_a_z12
suffix:semicolon
singleline_comment|// register and bitmap access
macro_line|#endif
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_F1
mdefine_line|#define A_F1 0x0C
DECL|macro|M_F1
mdefine_line|#define M_F1 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_f1
id|REGWORD
id|v_f1
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_a_f1
)brace
id|bit_a_f1
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_f1
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_f1
id|bit
suffix:semicolon
)brace
id|reg_a_f1
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_F2
mdefine_line|#define A_F2 0x0D
DECL|macro|M_F2
mdefine_line|#define M_F2 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_f2
id|REGWORD
id|v_f2
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_a_f2
)brace
id|bit_a_f2
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_f2
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_f2
id|bit
suffix:semicolon
)brace
id|reg_a_f2
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_F12
mdefine_line|#define A_F12 0x0C
DECL|macro|M_F12
mdefine_line|#define M_F12 0xFFFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_f12
id|REGWORD16
id|v_f12
suffix:colon
l_int|16
suffix:semicolon
DECL|typedef|bit_a_f12
)brace
id|bit_a_f12
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_f12
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_f12
id|bit
suffix:semicolon
)brace
id|reg_a_f12
suffix:semicolon
singleline_comment|// register and bitmap access
DECL|macro|R_CIRM
mdefine_line|#define R_CIRM 0x00
DECL|macro|M_IRQ_SEL
mdefine_line|#define M_IRQ_SEL 0x07
DECL|macro|M1_IRQ_SEL
mdefine_line|#define M1_IRQ_SEL 0x01
DECL|macro|M2_IRQ_SEL
mdefine_line|#define M2_IRQ_SEL 0x02
DECL|macro|M3_IRQ_SEL
mdefine_line|#define M3_IRQ_SEL 0x03
DECL|macro|M4_IRQ_SEL
mdefine_line|#define M4_IRQ_SEL 0x04
DECL|macro|M5_IRQ_SEL
mdefine_line|#define M5_IRQ_SEL 0x05
DECL|macro|M6_IRQ_SEL
mdefine_line|#define M6_IRQ_SEL 0x06
DECL|macro|M7_IRQ_SEL
mdefine_line|#define M7_IRQ_SEL 0x07
DECL|macro|M_SRES
mdefine_line|#define M_SRES 0x08
DECL|macro|M_HFCRES
mdefine_line|#define M_HFCRES 0x10
DECL|macro|M_PCMRES
mdefine_line|#define M_PCMRES 0x20
DECL|macro|M_STRES
mdefine_line|#define M_STRES 0x40
DECL|macro|M_RLD_EPR
mdefine_line|#define M_RLD_EPR 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_irq_sel
id|REGWORD
id|v_irq_sel
suffix:colon
l_int|3
suffix:semicolon
DECL|member|v_sres
id|REGWORD
id|v_sres
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_hfcres
id|REGWORD
id|v_hfcres
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_pcmres
id|REGWORD
id|v_pcmres
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_stres
id|REGWORD
id|v_stres
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_rld_epr
id|REGWORD
id|v_rld_epr
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_cirm
)brace
id|bit_r_cirm
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_cirm
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_cirm
id|bit
suffix:semicolon
)brace
id|reg_r_cirm
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_CTRL
mdefine_line|#define R_CTRL 0x01
DECL|macro|M_FIFO_LPRIO
mdefine_line|#define M_FIFO_LPRIO 0x02
DECL|macro|M_SLOW_RD
mdefine_line|#define M_SLOW_RD 0x04
DECL|macro|M_EXT_RAM
mdefine_line|#define M_EXT_RAM 0x08
DECL|macro|M_CLK_OFF
mdefine_line|#define M_CLK_OFF 0x20
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|reserved_13
id|REGWORD
id|reserved_13
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_fifo_lprio
id|REGWORD
id|v_fifo_lprio
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_slow_rd
id|REGWORD
id|v_slow_rd
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_ext_ram
id|REGWORD
id|v_ext_ram
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_14
id|REGWORD
id|reserved_14
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_clk_off
id|REGWORD
id|v_clk_off
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_15v_st_clk
id|REGWORD
id|reserved_15v_st_clk
suffix:colon
l_int|2
suffix:semicolon
DECL|typedef|bit_r_ctrl
)brace
id|bit_r_ctrl
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_ctrl
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_ctrl
id|bit
suffix:semicolon
)brace
id|reg_r_ctrl
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_BRG_PCM_CFG
mdefine_line|#define R_BRG_PCM_CFG 0x02
DECL|macro|M_BRG_EN
mdefine_line|#define M_BRG_EN 0x01
DECL|macro|M_BRG_MD
mdefine_line|#define M_BRG_MD 0x02
DECL|macro|M_PCM_CLK
mdefine_line|#define M_PCM_CLK 0x20
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_brg_en
id|REGWORD
id|v_brg_en
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_brg_md
id|REGWORD
id|v_brg_md
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_16
id|REGWORD
id|reserved_16
suffix:colon
l_int|3
suffix:semicolon
DECL|member|v_pcm_clk
id|REGWORD
id|v_pcm_clk
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_17v_addr_wrdly
id|REGWORD
id|reserved_17v_addr_wrdly
suffix:colon
l_int|2
suffix:semicolon
DECL|typedef|bit_r_brg_pcm_cfg
)brace
id|bit_r_brg_pcm_cfg
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_brg_pcm_cfg
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_brg_pcm_cfg
id|bit
suffix:semicolon
)brace
id|reg_r_brg_pcm_cfg
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_RAM_ADDR0
mdefine_line|#define R_RAM_ADDR0 0x08
DECL|macro|M_RAM_ADDR0
mdefine_line|#define M_RAM_ADDR0 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_ram_addr0
id|REGWORD
id|v_ram_addr0
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_r_ram_addr0
)brace
id|bit_r_ram_addr0
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_ram_addr0
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_ram_addr0
id|bit
suffix:semicolon
)brace
id|reg_r_ram_addr0
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_RAM_ADDR1
mdefine_line|#define R_RAM_ADDR1 0x09
DECL|macro|M_RAM_ADDR1
mdefine_line|#define M_RAM_ADDR1 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_ram_addr1
id|REGWORD
id|v_ram_addr1
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_r_ram_addr1
)brace
id|bit_r_ram_addr1
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_ram_addr1
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_ram_addr1
id|bit
suffix:semicolon
)brace
id|reg_r_ram_addr1
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_RAM_ADDR2
mdefine_line|#define R_RAM_ADDR2 0x0A
DECL|macro|M_RAM_ADDR2
mdefine_line|#define M_RAM_ADDR2 0x0F
DECL|macro|M1_RAM_ADDR2
mdefine_line|#define M1_RAM_ADDR2 0x01
DECL|macro|M2_RAM_ADDR2
mdefine_line|#define M2_RAM_ADDR2 0x02
DECL|macro|M3_RAM_ADDR2
mdefine_line|#define M3_RAM_ADDR2 0x03
DECL|macro|M4_RAM_ADDR2
mdefine_line|#define M4_RAM_ADDR2 0x04
DECL|macro|M5_RAM_ADDR2
mdefine_line|#define M5_RAM_ADDR2 0x05
DECL|macro|M6_RAM_ADDR2
mdefine_line|#define M6_RAM_ADDR2 0x06
DECL|macro|M7_RAM_ADDR2
mdefine_line|#define M7_RAM_ADDR2 0x07
DECL|macro|M8_RAM_ADDR2
mdefine_line|#define M8_RAM_ADDR2 0x08
DECL|macro|M9_RAM_ADDR2
mdefine_line|#define M9_RAM_ADDR2 0x09
DECL|macro|M10_RAM_ADDR2
mdefine_line|#define M10_RAM_ADDR2 0x0A
DECL|macro|M11_RAM_ADDR2
mdefine_line|#define M11_RAM_ADDR2 0x0B
DECL|macro|M12_RAM_ADDR2
mdefine_line|#define M12_RAM_ADDR2 0x0C
DECL|macro|M13_RAM_ADDR2
mdefine_line|#define M13_RAM_ADDR2 0x0D
DECL|macro|M14_RAM_ADDR2
mdefine_line|#define M14_RAM_ADDR2 0x0E
DECL|macro|M15_RAM_ADDR2
mdefine_line|#define M15_RAM_ADDR2 0x0F
DECL|macro|M_ADDR_RES
mdefine_line|#define M_ADDR_RES 0x40
DECL|macro|M_ADDR_INC
mdefine_line|#define M_ADDR_INC 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_ram_addr2
id|REGWORD
id|v_ram_addr2
suffix:colon
l_int|4
suffix:semicolon
DECL|member|reserved_18
id|REGWORD
id|reserved_18
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_addr_res
id|REGWORD
id|v_addr_res
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_addr_inc
id|REGWORD
id|v_addr_inc
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_ram_addr2
)brace
id|bit_r_ram_addr2
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_ram_addr2
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_ram_addr2
id|bit
suffix:semicolon
)brace
id|reg_r_ram_addr2
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_FIRST_FIFO
mdefine_line|#define R_FIRST_FIFO 0x0B
DECL|macro|M_FIRST_FIFO_DIR
mdefine_line|#define M_FIRST_FIFO_DIR 0x01
DECL|macro|M_FIRST_FIFO_NUM
mdefine_line|#define M_FIRST_FIFO_NUM 0x3E
DECL|macro|M1_FIRST_FIFO_NUM
mdefine_line|#define M1_FIRST_FIFO_NUM 0x02
DECL|macro|M2_FIRST_FIFO_NUM
mdefine_line|#define M2_FIRST_FIFO_NUM 0x04
DECL|macro|M3_FIRST_FIFO_NUM
mdefine_line|#define M3_FIRST_FIFO_NUM 0x06
DECL|macro|M4_FIRST_FIFO_NUM
mdefine_line|#define M4_FIRST_FIFO_NUM 0x08
DECL|macro|M5_FIRST_FIFO_NUM
mdefine_line|#define M5_FIRST_FIFO_NUM 0x0A
DECL|macro|M6_FIRST_FIFO_NUM
mdefine_line|#define M6_FIRST_FIFO_NUM 0x0C
DECL|macro|M7_FIRST_FIFO_NUM
mdefine_line|#define M7_FIRST_FIFO_NUM 0x0E
DECL|macro|M8_FIRST_FIFO_NUM
mdefine_line|#define M8_FIRST_FIFO_NUM 0x10
DECL|macro|M9_FIRST_FIFO_NUM
mdefine_line|#define M9_FIRST_FIFO_NUM 0x12
DECL|macro|M10_FIRST_FIFO_NUM
mdefine_line|#define M10_FIRST_FIFO_NUM 0x14
DECL|macro|M11_FIRST_FIFO_NUM
mdefine_line|#define M11_FIRST_FIFO_NUM 0x16
DECL|macro|M12_FIRST_FIFO_NUM
mdefine_line|#define M12_FIRST_FIFO_NUM 0x18
DECL|macro|M13_FIRST_FIFO_NUM
mdefine_line|#define M13_FIRST_FIFO_NUM 0x1A
DECL|macro|M14_FIRST_FIFO_NUM
mdefine_line|#define M14_FIRST_FIFO_NUM 0x1C
DECL|macro|M15_FIRST_FIFO_NUM
mdefine_line|#define M15_FIRST_FIFO_NUM 0x1E
DECL|macro|M16_FIRST_FIFO_NUM
mdefine_line|#define M16_FIRST_FIFO_NUM 0x20
DECL|macro|M17_FIRST_FIFO_NUM
mdefine_line|#define M17_FIRST_FIFO_NUM 0x22
DECL|macro|M18_FIRST_FIFO_NUM
mdefine_line|#define M18_FIRST_FIFO_NUM 0x24
DECL|macro|M19_FIRST_FIFO_NUM
mdefine_line|#define M19_FIRST_FIFO_NUM 0x26
DECL|macro|M20_FIRST_FIFO_NUM
mdefine_line|#define M20_FIRST_FIFO_NUM 0x28
DECL|macro|M21_FIRST_FIFO_NUM
mdefine_line|#define M21_FIRST_FIFO_NUM 0x2A
DECL|macro|M22_FIRST_FIFO_NUM
mdefine_line|#define M22_FIRST_FIFO_NUM 0x2C
DECL|macro|M23_FIRST_FIFO_NUM
mdefine_line|#define M23_FIRST_FIFO_NUM 0x2E
DECL|macro|M24_FIRST_FIFO_NUM
mdefine_line|#define M24_FIRST_FIFO_NUM 0x30
DECL|macro|M25_FIRST_FIFO_NUM
mdefine_line|#define M25_FIRST_FIFO_NUM 0x32
DECL|macro|M26_FIRST_FIFO_NUM
mdefine_line|#define M26_FIRST_FIFO_NUM 0x34
DECL|macro|M27_FIRST_FIFO_NUM
mdefine_line|#define M27_FIRST_FIFO_NUM 0x36
DECL|macro|M28_FIRST_FIFO_NUM
mdefine_line|#define M28_FIRST_FIFO_NUM 0x38
DECL|macro|M29_FIRST_FIFO_NUM
mdefine_line|#define M29_FIRST_FIFO_NUM 0x3A
DECL|macro|M30_FIRST_FIFO_NUM
mdefine_line|#define M30_FIRST_FIFO_NUM 0x3C
DECL|macro|M31_FIRST_FIFO_NUM
mdefine_line|#define M31_FIRST_FIFO_NUM 0x3E
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_first_fifo_dir
id|REGWORD
id|v_first_fifo_dir
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_first_fifo_num
id|REGWORD
id|v_first_fifo_num
suffix:colon
l_int|5
suffix:semicolon
DECL|member|reserved_19
id|REGWORD
id|reserved_19
suffix:colon
l_int|2
suffix:semicolon
DECL|typedef|bit_r_first_fifo
)brace
id|bit_r_first_fifo
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_first_fifo
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_first_fifo
id|bit
suffix:semicolon
)brace
id|reg_r_first_fifo
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_RAM_SZ
mdefine_line|#define R_RAM_SZ 0x0C
DECL|macro|M_RAM_SZ
mdefine_line|#define M_RAM_SZ 0x03
DECL|macro|M1_RAM_SZ
mdefine_line|#define M1_RAM_SZ 0x01
DECL|macro|M2_RAM_SZ
mdefine_line|#define M2_RAM_SZ 0x02
DECL|macro|M3_RAM_SZ
mdefine_line|#define M3_RAM_SZ 0x03
DECL|macro|V_FZ_MD
mdefine_line|#define V_FZ_MD   0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_ram_sz
id|REGWORD
id|v_ram_sz
suffix:colon
l_int|2
suffix:semicolon
DECL|member|reserved_20
id|REGWORD
id|reserved_20
suffix:colon
l_int|6
suffix:semicolon
DECL|typedef|bit_r_ram_sz
)brace
id|bit_r_ram_sz
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_ram_sz
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_ram_sz
id|bit
suffix:semicolon
)brace
id|reg_r_ram_sz
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_FIFO_MD
mdefine_line|#define R_FIFO_MD 0x0D
DECL|macro|M_FIFO_MD
mdefine_line|#define M_FIFO_MD 0x03
DECL|macro|M1_FIFO_MD
mdefine_line|#define M1_FIFO_MD 0x01
DECL|macro|M2_FIFO_MD
mdefine_line|#define M2_FIFO_MD 0x02
DECL|macro|M3_FIFO_MD
mdefine_line|#define M3_FIFO_MD 0x03
DECL|macro|M_CSM_MD
mdefine_line|#define M_CSM_MD 0x04
DECL|macro|M_FSM_MD
mdefine_line|#define M_FSM_MD 0x08
DECL|macro|M_FIFO_SZ
mdefine_line|#define M_FIFO_SZ 0x30
DECL|macro|M1_FIFO_SZ
mdefine_line|#define M1_FIFO_SZ 0x10
DECL|macro|M2_FIFO_SZ
mdefine_line|#define M2_FIFO_SZ 0x20
DECL|macro|M3_FIFO_SZ
mdefine_line|#define M3_FIFO_SZ 0x30
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_fifo_md
id|REGWORD
id|v_fifo_md
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_csm_md
id|REGWORD
id|v_csm_md
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_fsm_md
id|REGWORD
id|v_fsm_md
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_fifo_sz
id|REGWORD
id|v_fifo_sz
suffix:colon
l_int|2
suffix:semicolon
DECL|member|reserved_21
id|REGWORD
id|reserved_21
suffix:colon
l_int|2
suffix:semicolon
DECL|typedef|bit_r_fifo_md
)brace
id|bit_r_fifo_md
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_fifo_md
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_fifo_md
id|bit
suffix:semicolon
)brace
id|reg_r_fifo_md
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_INC_RES_FIFO
mdefine_line|#define R_INC_RES_FIFO 0x0E
DECL|macro|M_INC_F
mdefine_line|#define M_INC_F 0x01
DECL|macro|M_RES_F
mdefine_line|#define M_RES_F 0x02
DECL|macro|M_RES_LOST
mdefine_line|#define M_RES_LOST 0x04
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_inc_f
id|REGWORD
id|v_inc_f
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_res_f
id|REGWORD
id|v_res_f
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_res_lost
id|REGWORD
id|v_res_lost
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_22
id|REGWORD
id|reserved_22
suffix:colon
l_int|5
suffix:semicolon
DECL|typedef|bit_r_inc_res_fifo
)brace
id|bit_r_inc_res_fifo
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_inc_res_fifo
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_inc_res_fifo
id|bit
suffix:semicolon
)brace
id|reg_r_inc_res_fifo
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_FIFO
mdefine_line|#define R_FIFO 0x0F
DECL|macro|M_FIFO_DIR
mdefine_line|#define M_FIFO_DIR 0x01
DECL|macro|M_FIFO_NUM
mdefine_line|#define M_FIFO_NUM 0x3E
DECL|macro|M1_FIFO_NUM
mdefine_line|#define M1_FIFO_NUM 0x02
DECL|macro|M2_FIFO_NUM
mdefine_line|#define M2_FIFO_NUM 0x04
DECL|macro|M3_FIFO_NUM
mdefine_line|#define M3_FIFO_NUM 0x06
DECL|macro|M4_FIFO_NUM
mdefine_line|#define M4_FIFO_NUM 0x08
DECL|macro|M5_FIFO_NUM
mdefine_line|#define M5_FIFO_NUM 0x0A
DECL|macro|M6_FIFO_NUM
mdefine_line|#define M6_FIFO_NUM 0x0C
DECL|macro|M7_FIFO_NUM
mdefine_line|#define M7_FIFO_NUM 0x0E
DECL|macro|M8_FIFO_NUM
mdefine_line|#define M8_FIFO_NUM 0x10
DECL|macro|M9_FIFO_NUM
mdefine_line|#define M9_FIFO_NUM 0x12
DECL|macro|M10_FIFO_NUM
mdefine_line|#define M10_FIFO_NUM 0x14
DECL|macro|M11_FIFO_NUM
mdefine_line|#define M11_FIFO_NUM 0x16
DECL|macro|M12_FIFO_NUM
mdefine_line|#define M12_FIFO_NUM 0x18
DECL|macro|M13_FIFO_NUM
mdefine_line|#define M13_FIFO_NUM 0x1A
DECL|macro|M14_FIFO_NUM
mdefine_line|#define M14_FIFO_NUM 0x1C
DECL|macro|M15_FIFO_NUM
mdefine_line|#define M15_FIFO_NUM 0x1E
DECL|macro|M16_FIFO_NUM
mdefine_line|#define M16_FIFO_NUM 0x20
DECL|macro|M17_FIFO_NUM
mdefine_line|#define M17_FIFO_NUM 0x22
DECL|macro|M18_FIFO_NUM
mdefine_line|#define M18_FIFO_NUM 0x24
DECL|macro|M19_FIFO_NUM
mdefine_line|#define M19_FIFO_NUM 0x26
DECL|macro|M20_FIFO_NUM
mdefine_line|#define M20_FIFO_NUM 0x28
DECL|macro|M21_FIFO_NUM
mdefine_line|#define M21_FIFO_NUM 0x2A
DECL|macro|M22_FIFO_NUM
mdefine_line|#define M22_FIFO_NUM 0x2C
DECL|macro|M23_FIFO_NUM
mdefine_line|#define M23_FIFO_NUM 0x2E
DECL|macro|M24_FIFO_NUM
mdefine_line|#define M24_FIFO_NUM 0x30
DECL|macro|M25_FIFO_NUM
mdefine_line|#define M25_FIFO_NUM 0x32
DECL|macro|M26_FIFO_NUM
mdefine_line|#define M26_FIFO_NUM 0x34
DECL|macro|M27_FIFO_NUM
mdefine_line|#define M27_FIFO_NUM 0x36
DECL|macro|M28_FIFO_NUM
mdefine_line|#define M28_FIFO_NUM 0x38
DECL|macro|M29_FIFO_NUM
mdefine_line|#define M29_FIFO_NUM 0x3A
DECL|macro|M30_FIFO_NUM
mdefine_line|#define M30_FIFO_NUM 0x3C
DECL|macro|M31_FIFO_NUM
mdefine_line|#define M31_FIFO_NUM 0x3E
DECL|macro|M_REV
mdefine_line|#define M_REV 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_fifo_dir
id|REGWORD
id|v_fifo_dir
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_fifo_num
id|REGWORD
id|v_fifo_num
suffix:colon
l_int|5
suffix:semicolon
DECL|member|reserved_23
id|REGWORD
id|reserved_23
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_rev
id|REGWORD
id|v_rev
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_fifo
)brace
id|bit_r_fifo
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_fifo
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_fifo
id|bit
suffix:semicolon
)brace
id|reg_r_fifo
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_FSM_IDX
mdefine_line|#define R_FSM_IDX 0x0F
DECL|macro|M_IDX
mdefine_line|#define M_IDX 0x3F
DECL|macro|M1_IDX
mdefine_line|#define M1_IDX 0x01
DECL|macro|M2_IDX
mdefine_line|#define M2_IDX 0x02
DECL|macro|M3_IDX
mdefine_line|#define M3_IDX 0x03
DECL|macro|M4_IDX
mdefine_line|#define M4_IDX 0x04
DECL|macro|M5_IDX
mdefine_line|#define M5_IDX 0x05
DECL|macro|M6_IDX
mdefine_line|#define M6_IDX 0x06
DECL|macro|M7_IDX
mdefine_line|#define M7_IDX 0x07
DECL|macro|M8_IDX
mdefine_line|#define M8_IDX 0x08
DECL|macro|M9_IDX
mdefine_line|#define M9_IDX 0x09
DECL|macro|M10_IDX
mdefine_line|#define M10_IDX 0x0A
DECL|macro|M11_IDX
mdefine_line|#define M11_IDX 0x0B
DECL|macro|M12_IDX
mdefine_line|#define M12_IDX 0x0C
DECL|macro|M13_IDX
mdefine_line|#define M13_IDX 0x0D
DECL|macro|M14_IDX
mdefine_line|#define M14_IDX 0x0E
DECL|macro|M15_IDX
mdefine_line|#define M15_IDX 0x0F
DECL|macro|M16_IDX
mdefine_line|#define M16_IDX 0x10
DECL|macro|M17_IDX
mdefine_line|#define M17_IDX 0x11
DECL|macro|M18_IDX
mdefine_line|#define M18_IDX 0x12
DECL|macro|M19_IDX
mdefine_line|#define M19_IDX 0x13
DECL|macro|M20_IDX
mdefine_line|#define M20_IDX 0x14
DECL|macro|M21_IDX
mdefine_line|#define M21_IDX 0x15
DECL|macro|M22_IDX
mdefine_line|#define M22_IDX 0x16
DECL|macro|M23_IDX
mdefine_line|#define M23_IDX 0x17
DECL|macro|M24_IDX
mdefine_line|#define M24_IDX 0x18
DECL|macro|M25_IDX
mdefine_line|#define M25_IDX 0x19
DECL|macro|M26_IDX
mdefine_line|#define M26_IDX 0x1A
DECL|macro|M27_IDX
mdefine_line|#define M27_IDX 0x1B
DECL|macro|M28_IDX
mdefine_line|#define M28_IDX 0x1C
DECL|macro|M29_IDX
mdefine_line|#define M29_IDX 0x1D
DECL|macro|M30_IDX
mdefine_line|#define M30_IDX 0x1E
DECL|macro|M31_IDX
mdefine_line|#define M31_IDX 0x1F
DECL|macro|M32_IDX
mdefine_line|#define M32_IDX 0x20
DECL|macro|M33_IDX
mdefine_line|#define M33_IDX 0x21
DECL|macro|M34_IDX
mdefine_line|#define M34_IDX 0x22
DECL|macro|M35_IDX
mdefine_line|#define M35_IDX 0x23
DECL|macro|M36_IDX
mdefine_line|#define M36_IDX 0x24
DECL|macro|M37_IDX
mdefine_line|#define M37_IDX 0x25
DECL|macro|M38_IDX
mdefine_line|#define M38_IDX 0x26
DECL|macro|M39_IDX
mdefine_line|#define M39_IDX 0x27
DECL|macro|M40_IDX
mdefine_line|#define M40_IDX 0x28
DECL|macro|M41_IDX
mdefine_line|#define M41_IDX 0x29
DECL|macro|M42_IDX
mdefine_line|#define M42_IDX 0x2A
DECL|macro|M43_IDX
mdefine_line|#define M43_IDX 0x2B
DECL|macro|M44_IDX
mdefine_line|#define M44_IDX 0x2C
DECL|macro|M45_IDX
mdefine_line|#define M45_IDX 0x2D
DECL|macro|M46_IDX
mdefine_line|#define M46_IDX 0x2E
DECL|macro|M47_IDX
mdefine_line|#define M47_IDX 0x2F
DECL|macro|M48_IDX
mdefine_line|#define M48_IDX 0x30
DECL|macro|M49_IDX
mdefine_line|#define M49_IDX 0x31
DECL|macro|M50_IDX
mdefine_line|#define M50_IDX 0x32
DECL|macro|M51_IDX
mdefine_line|#define M51_IDX 0x33
DECL|macro|M52_IDX
mdefine_line|#define M52_IDX 0x34
DECL|macro|M53_IDX
mdefine_line|#define M53_IDX 0x35
DECL|macro|M54_IDX
mdefine_line|#define M54_IDX 0x36
DECL|macro|M55_IDX
mdefine_line|#define M55_IDX 0x37
DECL|macro|M56_IDX
mdefine_line|#define M56_IDX 0x38
DECL|macro|M57_IDX
mdefine_line|#define M57_IDX 0x39
DECL|macro|M58_IDX
mdefine_line|#define M58_IDX 0x3A
DECL|macro|M59_IDX
mdefine_line|#define M59_IDX 0x3B
DECL|macro|M60_IDX
mdefine_line|#define M60_IDX 0x3C
DECL|macro|M61_IDX
mdefine_line|#define M61_IDX 0x3D
DECL|macro|M62_IDX
mdefine_line|#define M62_IDX 0x3E
DECL|macro|M63_IDX
mdefine_line|#define M63_IDX 0x3F
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_idx
id|REGWORD
id|v_idx
suffix:colon
l_int|6
suffix:semicolon
DECL|member|reserved_24
id|REGWORD
id|reserved_24
suffix:colon
l_int|2
suffix:semicolon
DECL|typedef|bit_r_fsm_idx
)brace
id|bit_r_fsm_idx
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_fsm_idx
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_fsm_idx
id|bit
suffix:semicolon
)brace
id|reg_r_fsm_idx
suffix:semicolon
singleline_comment|// register and bitmap access
DECL|macro|R_SRAM_USE
mdefine_line|#define R_SRAM_USE 0x15
DECL|macro|M_SRAM_USE
mdefine_line|#define M_SRAM_USE 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_sram_use
id|REGWORD
id|v_sram_use
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_r_sram_use
)brace
id|bit_r_sram_use
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_sram_use
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_sram_use
id|bit
suffix:semicolon
)brace
id|reg_r_sram_use
suffix:semicolon
singleline_comment|// register and bitmap access
DECL|macro|R_SL_SEL0
mdefine_line|#define R_SL_SEL0 0x15
DECL|macro|M_SL_SEL0
mdefine_line|#define M_SL_SEL0 0x7F
DECL|macro|M1_SL_SEL0
mdefine_line|#define M1_SL_SEL0 0x01
DECL|macro|M2_SL_SEL0
mdefine_line|#define M2_SL_SEL0 0x02
DECL|macro|M3_SL_SEL0
mdefine_line|#define M3_SL_SEL0 0x03
DECL|macro|M4_SL_SEL0
mdefine_line|#define M4_SL_SEL0 0x04
DECL|macro|M5_SL_SEL0
mdefine_line|#define M5_SL_SEL0 0x05
DECL|macro|M6_SL_SEL0
mdefine_line|#define M6_SL_SEL0 0x06
DECL|macro|M7_SL_SEL0
mdefine_line|#define M7_SL_SEL0 0x07
DECL|macro|M8_SL_SEL0
mdefine_line|#define M8_SL_SEL0 0x08
DECL|macro|M9_SL_SEL0
mdefine_line|#define M9_SL_SEL0 0x09
DECL|macro|M10_SL_SEL0
mdefine_line|#define M10_SL_SEL0 0x0A
DECL|macro|M11_SL_SEL0
mdefine_line|#define M11_SL_SEL0 0x0B
DECL|macro|M12_SL_SEL0
mdefine_line|#define M12_SL_SEL0 0x0C
DECL|macro|M13_SL_SEL0
mdefine_line|#define M13_SL_SEL0 0x0D
DECL|macro|M14_SL_SEL0
mdefine_line|#define M14_SL_SEL0 0x0E
DECL|macro|M15_SL_SEL0
mdefine_line|#define M15_SL_SEL0 0x0F
DECL|macro|M16_SL_SEL0
mdefine_line|#define M16_SL_SEL0 0x10
DECL|macro|M17_SL_SEL0
mdefine_line|#define M17_SL_SEL0 0x11
DECL|macro|M18_SL_SEL0
mdefine_line|#define M18_SL_SEL0 0x12
DECL|macro|M19_SL_SEL0
mdefine_line|#define M19_SL_SEL0 0x13
DECL|macro|M20_SL_SEL0
mdefine_line|#define M20_SL_SEL0 0x14
DECL|macro|M21_SL_SEL0
mdefine_line|#define M21_SL_SEL0 0x15
DECL|macro|M22_SL_SEL0
mdefine_line|#define M22_SL_SEL0 0x16
DECL|macro|M23_SL_SEL0
mdefine_line|#define M23_SL_SEL0 0x17
DECL|macro|M24_SL_SEL0
mdefine_line|#define M24_SL_SEL0 0x18
DECL|macro|M25_SL_SEL0
mdefine_line|#define M25_SL_SEL0 0x19
DECL|macro|M26_SL_SEL0
mdefine_line|#define M26_SL_SEL0 0x1A
DECL|macro|M27_SL_SEL0
mdefine_line|#define M27_SL_SEL0 0x1B
DECL|macro|M28_SL_SEL0
mdefine_line|#define M28_SL_SEL0 0x1C
DECL|macro|M29_SL_SEL0
mdefine_line|#define M29_SL_SEL0 0x1D
DECL|macro|M30_SL_SEL0
mdefine_line|#define M30_SL_SEL0 0x1E
DECL|macro|M31_SL_SEL0
mdefine_line|#define M31_SL_SEL0 0x1F
DECL|macro|M32_SL_SEL0
mdefine_line|#define M32_SL_SEL0 0x20
DECL|macro|M33_SL_SEL0
mdefine_line|#define M33_SL_SEL0 0x21
DECL|macro|M34_SL_SEL0
mdefine_line|#define M34_SL_SEL0 0x22
DECL|macro|M35_SL_SEL0
mdefine_line|#define M35_SL_SEL0 0x23
DECL|macro|M36_SL_SEL0
mdefine_line|#define M36_SL_SEL0 0x24
DECL|macro|M37_SL_SEL0
mdefine_line|#define M37_SL_SEL0 0x25
DECL|macro|M38_SL_SEL0
mdefine_line|#define M38_SL_SEL0 0x26
DECL|macro|M39_SL_SEL0
mdefine_line|#define M39_SL_SEL0 0x27
DECL|macro|M40_SL_SEL0
mdefine_line|#define M40_SL_SEL0 0x28
DECL|macro|M41_SL_SEL0
mdefine_line|#define M41_SL_SEL0 0x29
DECL|macro|M42_SL_SEL0
mdefine_line|#define M42_SL_SEL0 0x2A
DECL|macro|M43_SL_SEL0
mdefine_line|#define M43_SL_SEL0 0x2B
DECL|macro|M44_SL_SEL0
mdefine_line|#define M44_SL_SEL0 0x2C
DECL|macro|M45_SL_SEL0
mdefine_line|#define M45_SL_SEL0 0x2D
DECL|macro|M46_SL_SEL0
mdefine_line|#define M46_SL_SEL0 0x2E
DECL|macro|M47_SL_SEL0
mdefine_line|#define M47_SL_SEL0 0x2F
DECL|macro|M48_SL_SEL0
mdefine_line|#define M48_SL_SEL0 0x30
DECL|macro|M49_SL_SEL0
mdefine_line|#define M49_SL_SEL0 0x31
DECL|macro|M50_SL_SEL0
mdefine_line|#define M50_SL_SEL0 0x32
DECL|macro|M51_SL_SEL0
mdefine_line|#define M51_SL_SEL0 0x33
DECL|macro|M52_SL_SEL0
mdefine_line|#define M52_SL_SEL0 0x34
DECL|macro|M53_SL_SEL0
mdefine_line|#define M53_SL_SEL0 0x35
DECL|macro|M54_SL_SEL0
mdefine_line|#define M54_SL_SEL0 0x36
DECL|macro|M55_SL_SEL0
mdefine_line|#define M55_SL_SEL0 0x37
DECL|macro|M56_SL_SEL0
mdefine_line|#define M56_SL_SEL0 0x38
DECL|macro|M57_SL_SEL0
mdefine_line|#define M57_SL_SEL0 0x39
DECL|macro|M58_SL_SEL0
mdefine_line|#define M58_SL_SEL0 0x3A
DECL|macro|M59_SL_SEL0
mdefine_line|#define M59_SL_SEL0 0x3B
DECL|macro|M60_SL_SEL0
mdefine_line|#define M60_SL_SEL0 0x3C
DECL|macro|M61_SL_SEL0
mdefine_line|#define M61_SL_SEL0 0x3D
DECL|macro|M62_SL_SEL0
mdefine_line|#define M62_SL_SEL0 0x3E
DECL|macro|M63_SL_SEL0
mdefine_line|#define M63_SL_SEL0 0x3F
DECL|macro|M64_SL_SEL0
mdefine_line|#define M64_SL_SEL0 0x40
DECL|macro|M65_SL_SEL0
mdefine_line|#define M65_SL_SEL0 0x41
DECL|macro|M66_SL_SEL0
mdefine_line|#define M66_SL_SEL0 0x42
DECL|macro|M67_SL_SEL0
mdefine_line|#define M67_SL_SEL0 0x43
DECL|macro|M68_SL_SEL0
mdefine_line|#define M68_SL_SEL0 0x44
DECL|macro|M69_SL_SEL0
mdefine_line|#define M69_SL_SEL0 0x45
DECL|macro|M70_SL_SEL0
mdefine_line|#define M70_SL_SEL0 0x46
DECL|macro|M71_SL_SEL0
mdefine_line|#define M71_SL_SEL0 0x47
DECL|macro|M72_SL_SEL0
mdefine_line|#define M72_SL_SEL0 0x48
DECL|macro|M73_SL_SEL0
mdefine_line|#define M73_SL_SEL0 0x49
DECL|macro|M74_SL_SEL0
mdefine_line|#define M74_SL_SEL0 0x4A
DECL|macro|M75_SL_SEL0
mdefine_line|#define M75_SL_SEL0 0x4B
DECL|macro|M76_SL_SEL0
mdefine_line|#define M76_SL_SEL0 0x4C
DECL|macro|M77_SL_SEL0
mdefine_line|#define M77_SL_SEL0 0x4D
DECL|macro|M78_SL_SEL0
mdefine_line|#define M78_SL_SEL0 0x4E
DECL|macro|M79_SL_SEL0
mdefine_line|#define M79_SL_SEL0 0x4F
DECL|macro|M80_SL_SEL0
mdefine_line|#define M80_SL_SEL0 0x50
DECL|macro|M81_SL_SEL0
mdefine_line|#define M81_SL_SEL0 0x51
DECL|macro|M82_SL_SEL0
mdefine_line|#define M82_SL_SEL0 0x52
DECL|macro|M83_SL_SEL0
mdefine_line|#define M83_SL_SEL0 0x53
DECL|macro|M84_SL_SEL0
mdefine_line|#define M84_SL_SEL0 0x54
DECL|macro|M85_SL_SEL0
mdefine_line|#define M85_SL_SEL0 0x55
DECL|macro|M86_SL_SEL0
mdefine_line|#define M86_SL_SEL0 0x56
DECL|macro|M87_SL_SEL0
mdefine_line|#define M87_SL_SEL0 0x57
DECL|macro|M88_SL_SEL0
mdefine_line|#define M88_SL_SEL0 0x58
DECL|macro|M89_SL_SEL0
mdefine_line|#define M89_SL_SEL0 0x59
DECL|macro|M90_SL_SEL0
mdefine_line|#define M90_SL_SEL0 0x5A
DECL|macro|M91_SL_SEL0
mdefine_line|#define M91_SL_SEL0 0x5B
DECL|macro|M92_SL_SEL0
mdefine_line|#define M92_SL_SEL0 0x5C
DECL|macro|M93_SL_SEL0
mdefine_line|#define M93_SL_SEL0 0x5D
DECL|macro|M94_SL_SEL0
mdefine_line|#define M94_SL_SEL0 0x5E
DECL|macro|M95_SL_SEL0
mdefine_line|#define M95_SL_SEL0 0x5F
DECL|macro|M96_SL_SEL0
mdefine_line|#define M96_SL_SEL0 0x60
DECL|macro|M97_SL_SEL0
mdefine_line|#define M97_SL_SEL0 0x61
DECL|macro|M98_SL_SEL0
mdefine_line|#define M98_SL_SEL0 0x62
DECL|macro|M99_SL_SEL0
mdefine_line|#define M99_SL_SEL0 0x63
DECL|macro|M100_SL_SEL0
mdefine_line|#define M100_SL_SEL0 0x64
DECL|macro|M101_SL_SEL0
mdefine_line|#define M101_SL_SEL0 0x65
DECL|macro|M102_SL_SEL0
mdefine_line|#define M102_SL_SEL0 0x66
DECL|macro|M103_SL_SEL0
mdefine_line|#define M103_SL_SEL0 0x67
DECL|macro|M104_SL_SEL0
mdefine_line|#define M104_SL_SEL0 0x68
DECL|macro|M105_SL_SEL0
mdefine_line|#define M105_SL_SEL0 0x69
DECL|macro|M106_SL_SEL0
mdefine_line|#define M106_SL_SEL0 0x6A
DECL|macro|M107_SL_SEL0
mdefine_line|#define M107_SL_SEL0 0x6B
DECL|macro|M108_SL_SEL0
mdefine_line|#define M108_SL_SEL0 0x6C
DECL|macro|M109_SL_SEL0
mdefine_line|#define M109_SL_SEL0 0x6D
DECL|macro|M110_SL_SEL0
mdefine_line|#define M110_SL_SEL0 0x6E
DECL|macro|M111_SL_SEL0
mdefine_line|#define M111_SL_SEL0 0x6F
DECL|macro|M112_SL_SEL0
mdefine_line|#define M112_SL_SEL0 0x70
DECL|macro|M113_SL_SEL0
mdefine_line|#define M113_SL_SEL0 0x71
DECL|macro|M114_SL_SEL0
mdefine_line|#define M114_SL_SEL0 0x72
DECL|macro|M115_SL_SEL0
mdefine_line|#define M115_SL_SEL0 0x73
DECL|macro|M116_SL_SEL0
mdefine_line|#define M116_SL_SEL0 0x74
DECL|macro|M117_SL_SEL0
mdefine_line|#define M117_SL_SEL0 0x75
DECL|macro|M118_SL_SEL0
mdefine_line|#define M118_SL_SEL0 0x76
DECL|macro|M119_SL_SEL0
mdefine_line|#define M119_SL_SEL0 0x77
DECL|macro|M120_SL_SEL0
mdefine_line|#define M120_SL_SEL0 0x78
DECL|macro|M121_SL_SEL0
mdefine_line|#define M121_SL_SEL0 0x79
DECL|macro|M122_SL_SEL0
mdefine_line|#define M122_SL_SEL0 0x7A
DECL|macro|M123_SL_SEL0
mdefine_line|#define M123_SL_SEL0 0x7B
DECL|macro|M124_SL_SEL0
mdefine_line|#define M124_SL_SEL0 0x7C
DECL|macro|M125_SL_SEL0
mdefine_line|#define M125_SL_SEL0 0x7D
DECL|macro|M126_SL_SEL0
mdefine_line|#define M126_SL_SEL0 0x7E
DECL|macro|M127_SL_SEL0
mdefine_line|#define M127_SL_SEL0 0x7F
DECL|macro|M_SH_SEL0
mdefine_line|#define M_SH_SEL0 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_sl_sel0
id|REGWORD
id|v_sl_sel0
suffix:colon
l_int|7
suffix:semicolon
DECL|member|v_sh_sel0
id|REGWORD
id|v_sh_sel0
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_sl_sel0
)brace
id|bit_r_sl_sel0
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_sl_sel0
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_sl_sel0
id|bit
suffix:semicolon
)brace
id|reg_r_sl_sel0
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_SL_SEL1
mdefine_line|#define R_SL_SEL1 0x15
DECL|macro|M_SL_SEL1
mdefine_line|#define M_SL_SEL1 0x7F
DECL|macro|M1_SL_SEL1
mdefine_line|#define M1_SL_SEL1 0x01
DECL|macro|M2_SL_SEL1
mdefine_line|#define M2_SL_SEL1 0x02
DECL|macro|M3_SL_SEL1
mdefine_line|#define M3_SL_SEL1 0x03
DECL|macro|M4_SL_SEL1
mdefine_line|#define M4_SL_SEL1 0x04
DECL|macro|M5_SL_SEL1
mdefine_line|#define M5_SL_SEL1 0x05
DECL|macro|M6_SL_SEL1
mdefine_line|#define M6_SL_SEL1 0x06
DECL|macro|M7_SL_SEL1
mdefine_line|#define M7_SL_SEL1 0x07
DECL|macro|M8_SL_SEL1
mdefine_line|#define M8_SL_SEL1 0x08
DECL|macro|M9_SL_SEL1
mdefine_line|#define M9_SL_SEL1 0x09
DECL|macro|M10_SL_SEL1
mdefine_line|#define M10_SL_SEL1 0x0A
DECL|macro|M11_SL_SEL1
mdefine_line|#define M11_SL_SEL1 0x0B
DECL|macro|M12_SL_SEL1
mdefine_line|#define M12_SL_SEL1 0x0C
DECL|macro|M13_SL_SEL1
mdefine_line|#define M13_SL_SEL1 0x0D
DECL|macro|M14_SL_SEL1
mdefine_line|#define M14_SL_SEL1 0x0E
DECL|macro|M15_SL_SEL1
mdefine_line|#define M15_SL_SEL1 0x0F
DECL|macro|M16_SL_SEL1
mdefine_line|#define M16_SL_SEL1 0x10
DECL|macro|M17_SL_SEL1
mdefine_line|#define M17_SL_SEL1 0x11
DECL|macro|M18_SL_SEL1
mdefine_line|#define M18_SL_SEL1 0x12
DECL|macro|M19_SL_SEL1
mdefine_line|#define M19_SL_SEL1 0x13
DECL|macro|M20_SL_SEL1
mdefine_line|#define M20_SL_SEL1 0x14
DECL|macro|M21_SL_SEL1
mdefine_line|#define M21_SL_SEL1 0x15
DECL|macro|M22_SL_SEL1
mdefine_line|#define M22_SL_SEL1 0x16
DECL|macro|M23_SL_SEL1
mdefine_line|#define M23_SL_SEL1 0x17
DECL|macro|M24_SL_SEL1
mdefine_line|#define M24_SL_SEL1 0x18
DECL|macro|M25_SL_SEL1
mdefine_line|#define M25_SL_SEL1 0x19
DECL|macro|M26_SL_SEL1
mdefine_line|#define M26_SL_SEL1 0x1A
DECL|macro|M27_SL_SEL1
mdefine_line|#define M27_SL_SEL1 0x1B
DECL|macro|M28_SL_SEL1
mdefine_line|#define M28_SL_SEL1 0x1C
DECL|macro|M29_SL_SEL1
mdefine_line|#define M29_SL_SEL1 0x1D
DECL|macro|M30_SL_SEL1
mdefine_line|#define M30_SL_SEL1 0x1E
DECL|macro|M31_SL_SEL1
mdefine_line|#define M31_SL_SEL1 0x1F
DECL|macro|M32_SL_SEL1
mdefine_line|#define M32_SL_SEL1 0x20
DECL|macro|M33_SL_SEL1
mdefine_line|#define M33_SL_SEL1 0x21
DECL|macro|M34_SL_SEL1
mdefine_line|#define M34_SL_SEL1 0x22
DECL|macro|M35_SL_SEL1
mdefine_line|#define M35_SL_SEL1 0x23
DECL|macro|M36_SL_SEL1
mdefine_line|#define M36_SL_SEL1 0x24
DECL|macro|M37_SL_SEL1
mdefine_line|#define M37_SL_SEL1 0x25
DECL|macro|M38_SL_SEL1
mdefine_line|#define M38_SL_SEL1 0x26
DECL|macro|M39_SL_SEL1
mdefine_line|#define M39_SL_SEL1 0x27
DECL|macro|M40_SL_SEL1
mdefine_line|#define M40_SL_SEL1 0x28
DECL|macro|M41_SL_SEL1
mdefine_line|#define M41_SL_SEL1 0x29
DECL|macro|M42_SL_SEL1
mdefine_line|#define M42_SL_SEL1 0x2A
DECL|macro|M43_SL_SEL1
mdefine_line|#define M43_SL_SEL1 0x2B
DECL|macro|M44_SL_SEL1
mdefine_line|#define M44_SL_SEL1 0x2C
DECL|macro|M45_SL_SEL1
mdefine_line|#define M45_SL_SEL1 0x2D
DECL|macro|M46_SL_SEL1
mdefine_line|#define M46_SL_SEL1 0x2E
DECL|macro|M47_SL_SEL1
mdefine_line|#define M47_SL_SEL1 0x2F
DECL|macro|M48_SL_SEL1
mdefine_line|#define M48_SL_SEL1 0x30
DECL|macro|M49_SL_SEL1
mdefine_line|#define M49_SL_SEL1 0x31
DECL|macro|M50_SL_SEL1
mdefine_line|#define M50_SL_SEL1 0x32
DECL|macro|M51_SL_SEL1
mdefine_line|#define M51_SL_SEL1 0x33
DECL|macro|M52_SL_SEL1
mdefine_line|#define M52_SL_SEL1 0x34
DECL|macro|M53_SL_SEL1
mdefine_line|#define M53_SL_SEL1 0x35
DECL|macro|M54_SL_SEL1
mdefine_line|#define M54_SL_SEL1 0x36
DECL|macro|M55_SL_SEL1
mdefine_line|#define M55_SL_SEL1 0x37
DECL|macro|M56_SL_SEL1
mdefine_line|#define M56_SL_SEL1 0x38
DECL|macro|M57_SL_SEL1
mdefine_line|#define M57_SL_SEL1 0x39
DECL|macro|M58_SL_SEL1
mdefine_line|#define M58_SL_SEL1 0x3A
DECL|macro|M59_SL_SEL1
mdefine_line|#define M59_SL_SEL1 0x3B
DECL|macro|M60_SL_SEL1
mdefine_line|#define M60_SL_SEL1 0x3C
DECL|macro|M61_SL_SEL1
mdefine_line|#define M61_SL_SEL1 0x3D
DECL|macro|M62_SL_SEL1
mdefine_line|#define M62_SL_SEL1 0x3E
DECL|macro|M63_SL_SEL1
mdefine_line|#define M63_SL_SEL1 0x3F
DECL|macro|M64_SL_SEL1
mdefine_line|#define M64_SL_SEL1 0x40
DECL|macro|M65_SL_SEL1
mdefine_line|#define M65_SL_SEL1 0x41
DECL|macro|M66_SL_SEL1
mdefine_line|#define M66_SL_SEL1 0x42
DECL|macro|M67_SL_SEL1
mdefine_line|#define M67_SL_SEL1 0x43
DECL|macro|M68_SL_SEL1
mdefine_line|#define M68_SL_SEL1 0x44
DECL|macro|M69_SL_SEL1
mdefine_line|#define M69_SL_SEL1 0x45
DECL|macro|M70_SL_SEL1
mdefine_line|#define M70_SL_SEL1 0x46
DECL|macro|M71_SL_SEL1
mdefine_line|#define M71_SL_SEL1 0x47
DECL|macro|M72_SL_SEL1
mdefine_line|#define M72_SL_SEL1 0x48
DECL|macro|M73_SL_SEL1
mdefine_line|#define M73_SL_SEL1 0x49
DECL|macro|M74_SL_SEL1
mdefine_line|#define M74_SL_SEL1 0x4A
DECL|macro|M75_SL_SEL1
mdefine_line|#define M75_SL_SEL1 0x4B
DECL|macro|M76_SL_SEL1
mdefine_line|#define M76_SL_SEL1 0x4C
DECL|macro|M77_SL_SEL1
mdefine_line|#define M77_SL_SEL1 0x4D
DECL|macro|M78_SL_SEL1
mdefine_line|#define M78_SL_SEL1 0x4E
DECL|macro|M79_SL_SEL1
mdefine_line|#define M79_SL_SEL1 0x4F
DECL|macro|M80_SL_SEL1
mdefine_line|#define M80_SL_SEL1 0x50
DECL|macro|M81_SL_SEL1
mdefine_line|#define M81_SL_SEL1 0x51
DECL|macro|M82_SL_SEL1
mdefine_line|#define M82_SL_SEL1 0x52
DECL|macro|M83_SL_SEL1
mdefine_line|#define M83_SL_SEL1 0x53
DECL|macro|M84_SL_SEL1
mdefine_line|#define M84_SL_SEL1 0x54
DECL|macro|M85_SL_SEL1
mdefine_line|#define M85_SL_SEL1 0x55
DECL|macro|M86_SL_SEL1
mdefine_line|#define M86_SL_SEL1 0x56
DECL|macro|M87_SL_SEL1
mdefine_line|#define M87_SL_SEL1 0x57
DECL|macro|M88_SL_SEL1
mdefine_line|#define M88_SL_SEL1 0x58
DECL|macro|M89_SL_SEL1
mdefine_line|#define M89_SL_SEL1 0x59
DECL|macro|M90_SL_SEL1
mdefine_line|#define M90_SL_SEL1 0x5A
DECL|macro|M91_SL_SEL1
mdefine_line|#define M91_SL_SEL1 0x5B
DECL|macro|M92_SL_SEL1
mdefine_line|#define M92_SL_SEL1 0x5C
DECL|macro|M93_SL_SEL1
mdefine_line|#define M93_SL_SEL1 0x5D
DECL|macro|M94_SL_SEL1
mdefine_line|#define M94_SL_SEL1 0x5E
DECL|macro|M95_SL_SEL1
mdefine_line|#define M95_SL_SEL1 0x5F
DECL|macro|M96_SL_SEL1
mdefine_line|#define M96_SL_SEL1 0x60
DECL|macro|M97_SL_SEL1
mdefine_line|#define M97_SL_SEL1 0x61
DECL|macro|M98_SL_SEL1
mdefine_line|#define M98_SL_SEL1 0x62
DECL|macro|M99_SL_SEL1
mdefine_line|#define M99_SL_SEL1 0x63
DECL|macro|M100_SL_SEL1
mdefine_line|#define M100_SL_SEL1 0x64
DECL|macro|M101_SL_SEL1
mdefine_line|#define M101_SL_SEL1 0x65
DECL|macro|M102_SL_SEL1
mdefine_line|#define M102_SL_SEL1 0x66
DECL|macro|M103_SL_SEL1
mdefine_line|#define M103_SL_SEL1 0x67
DECL|macro|M104_SL_SEL1
mdefine_line|#define M104_SL_SEL1 0x68
DECL|macro|M105_SL_SEL1
mdefine_line|#define M105_SL_SEL1 0x69
DECL|macro|M106_SL_SEL1
mdefine_line|#define M106_SL_SEL1 0x6A
DECL|macro|M107_SL_SEL1
mdefine_line|#define M107_SL_SEL1 0x6B
DECL|macro|M108_SL_SEL1
mdefine_line|#define M108_SL_SEL1 0x6C
DECL|macro|M109_SL_SEL1
mdefine_line|#define M109_SL_SEL1 0x6D
DECL|macro|M110_SL_SEL1
mdefine_line|#define M110_SL_SEL1 0x6E
DECL|macro|M111_SL_SEL1
mdefine_line|#define M111_SL_SEL1 0x6F
DECL|macro|M112_SL_SEL1
mdefine_line|#define M112_SL_SEL1 0x70
DECL|macro|M113_SL_SEL1
mdefine_line|#define M113_SL_SEL1 0x71
DECL|macro|M114_SL_SEL1
mdefine_line|#define M114_SL_SEL1 0x72
DECL|macro|M115_SL_SEL1
mdefine_line|#define M115_SL_SEL1 0x73
DECL|macro|M116_SL_SEL1
mdefine_line|#define M116_SL_SEL1 0x74
DECL|macro|M117_SL_SEL1
mdefine_line|#define M117_SL_SEL1 0x75
DECL|macro|M118_SL_SEL1
mdefine_line|#define M118_SL_SEL1 0x76
DECL|macro|M119_SL_SEL1
mdefine_line|#define M119_SL_SEL1 0x77
DECL|macro|M120_SL_SEL1
mdefine_line|#define M120_SL_SEL1 0x78
DECL|macro|M121_SL_SEL1
mdefine_line|#define M121_SL_SEL1 0x79
DECL|macro|M122_SL_SEL1
mdefine_line|#define M122_SL_SEL1 0x7A
DECL|macro|M123_SL_SEL1
mdefine_line|#define M123_SL_SEL1 0x7B
DECL|macro|M124_SL_SEL1
mdefine_line|#define M124_SL_SEL1 0x7C
DECL|macro|M125_SL_SEL1
mdefine_line|#define M125_SL_SEL1 0x7D
DECL|macro|M126_SL_SEL1
mdefine_line|#define M126_SL_SEL1 0x7E
DECL|macro|M127_SL_SEL1
mdefine_line|#define M127_SL_SEL1 0x7F
DECL|macro|M_SH_SEL1
mdefine_line|#define M_SH_SEL1 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_sl_sel1
id|REGWORD
id|v_sl_sel1
suffix:colon
l_int|7
suffix:semicolon
DECL|member|v_sh_sel1
id|REGWORD
id|v_sh_sel1
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_sl_sel1
)brace
id|bit_r_sl_sel1
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_sl_sel1
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_sl_sel1
id|bit
suffix:semicolon
)brace
id|reg_r_sl_sel1
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_SL_SEL2
mdefine_line|#define R_SL_SEL2 0x15
DECL|macro|M_SL_SEL2
mdefine_line|#define M_SL_SEL2 0x7F
DECL|macro|M1_SL_SEL2
mdefine_line|#define M1_SL_SEL2 0x01
DECL|macro|M2_SL_SEL2
mdefine_line|#define M2_SL_SEL2 0x02
DECL|macro|M3_SL_SEL2
mdefine_line|#define M3_SL_SEL2 0x03
DECL|macro|M4_SL_SEL2
mdefine_line|#define M4_SL_SEL2 0x04
DECL|macro|M5_SL_SEL2
mdefine_line|#define M5_SL_SEL2 0x05
DECL|macro|M6_SL_SEL2
mdefine_line|#define M6_SL_SEL2 0x06
DECL|macro|M7_SL_SEL2
mdefine_line|#define M7_SL_SEL2 0x07
DECL|macro|M8_SL_SEL2
mdefine_line|#define M8_SL_SEL2 0x08
DECL|macro|M9_SL_SEL2
mdefine_line|#define M9_SL_SEL2 0x09
DECL|macro|M10_SL_SEL2
mdefine_line|#define M10_SL_SEL2 0x0A
DECL|macro|M11_SL_SEL2
mdefine_line|#define M11_SL_SEL2 0x0B
DECL|macro|M12_SL_SEL2
mdefine_line|#define M12_SL_SEL2 0x0C
DECL|macro|M13_SL_SEL2
mdefine_line|#define M13_SL_SEL2 0x0D
DECL|macro|M14_SL_SEL2
mdefine_line|#define M14_SL_SEL2 0x0E
DECL|macro|M15_SL_SEL2
mdefine_line|#define M15_SL_SEL2 0x0F
DECL|macro|M16_SL_SEL2
mdefine_line|#define M16_SL_SEL2 0x10
DECL|macro|M17_SL_SEL2
mdefine_line|#define M17_SL_SEL2 0x11
DECL|macro|M18_SL_SEL2
mdefine_line|#define M18_SL_SEL2 0x12
DECL|macro|M19_SL_SEL2
mdefine_line|#define M19_SL_SEL2 0x13
DECL|macro|M20_SL_SEL2
mdefine_line|#define M20_SL_SEL2 0x14
DECL|macro|M21_SL_SEL2
mdefine_line|#define M21_SL_SEL2 0x15
DECL|macro|M22_SL_SEL2
mdefine_line|#define M22_SL_SEL2 0x16
DECL|macro|M23_SL_SEL2
mdefine_line|#define M23_SL_SEL2 0x17
DECL|macro|M24_SL_SEL2
mdefine_line|#define M24_SL_SEL2 0x18
DECL|macro|M25_SL_SEL2
mdefine_line|#define M25_SL_SEL2 0x19
DECL|macro|M26_SL_SEL2
mdefine_line|#define M26_SL_SEL2 0x1A
DECL|macro|M27_SL_SEL2
mdefine_line|#define M27_SL_SEL2 0x1B
DECL|macro|M28_SL_SEL2
mdefine_line|#define M28_SL_SEL2 0x1C
DECL|macro|M29_SL_SEL2
mdefine_line|#define M29_SL_SEL2 0x1D
DECL|macro|M30_SL_SEL2
mdefine_line|#define M30_SL_SEL2 0x1E
DECL|macro|M31_SL_SEL2
mdefine_line|#define M31_SL_SEL2 0x1F
DECL|macro|M32_SL_SEL2
mdefine_line|#define M32_SL_SEL2 0x20
DECL|macro|M33_SL_SEL2
mdefine_line|#define M33_SL_SEL2 0x21
DECL|macro|M34_SL_SEL2
mdefine_line|#define M34_SL_SEL2 0x22
DECL|macro|M35_SL_SEL2
mdefine_line|#define M35_SL_SEL2 0x23
DECL|macro|M36_SL_SEL2
mdefine_line|#define M36_SL_SEL2 0x24
DECL|macro|M37_SL_SEL2
mdefine_line|#define M37_SL_SEL2 0x25
DECL|macro|M38_SL_SEL2
mdefine_line|#define M38_SL_SEL2 0x26
DECL|macro|M39_SL_SEL2
mdefine_line|#define M39_SL_SEL2 0x27
DECL|macro|M40_SL_SEL2
mdefine_line|#define M40_SL_SEL2 0x28
DECL|macro|M41_SL_SEL2
mdefine_line|#define M41_SL_SEL2 0x29
DECL|macro|M42_SL_SEL2
mdefine_line|#define M42_SL_SEL2 0x2A
DECL|macro|M43_SL_SEL2
mdefine_line|#define M43_SL_SEL2 0x2B
DECL|macro|M44_SL_SEL2
mdefine_line|#define M44_SL_SEL2 0x2C
DECL|macro|M45_SL_SEL2
mdefine_line|#define M45_SL_SEL2 0x2D
DECL|macro|M46_SL_SEL2
mdefine_line|#define M46_SL_SEL2 0x2E
DECL|macro|M47_SL_SEL2
mdefine_line|#define M47_SL_SEL2 0x2F
DECL|macro|M48_SL_SEL2
mdefine_line|#define M48_SL_SEL2 0x30
DECL|macro|M49_SL_SEL2
mdefine_line|#define M49_SL_SEL2 0x31
DECL|macro|M50_SL_SEL2
mdefine_line|#define M50_SL_SEL2 0x32
DECL|macro|M51_SL_SEL2
mdefine_line|#define M51_SL_SEL2 0x33
DECL|macro|M52_SL_SEL2
mdefine_line|#define M52_SL_SEL2 0x34
DECL|macro|M53_SL_SEL2
mdefine_line|#define M53_SL_SEL2 0x35
DECL|macro|M54_SL_SEL2
mdefine_line|#define M54_SL_SEL2 0x36
DECL|macro|M55_SL_SEL2
mdefine_line|#define M55_SL_SEL2 0x37
DECL|macro|M56_SL_SEL2
mdefine_line|#define M56_SL_SEL2 0x38
DECL|macro|M57_SL_SEL2
mdefine_line|#define M57_SL_SEL2 0x39
DECL|macro|M58_SL_SEL2
mdefine_line|#define M58_SL_SEL2 0x3A
DECL|macro|M59_SL_SEL2
mdefine_line|#define M59_SL_SEL2 0x3B
DECL|macro|M60_SL_SEL2
mdefine_line|#define M60_SL_SEL2 0x3C
DECL|macro|M61_SL_SEL2
mdefine_line|#define M61_SL_SEL2 0x3D
DECL|macro|M62_SL_SEL2
mdefine_line|#define M62_SL_SEL2 0x3E
DECL|macro|M63_SL_SEL2
mdefine_line|#define M63_SL_SEL2 0x3F
DECL|macro|M64_SL_SEL2
mdefine_line|#define M64_SL_SEL2 0x40
DECL|macro|M65_SL_SEL2
mdefine_line|#define M65_SL_SEL2 0x41
DECL|macro|M66_SL_SEL2
mdefine_line|#define M66_SL_SEL2 0x42
DECL|macro|M67_SL_SEL2
mdefine_line|#define M67_SL_SEL2 0x43
DECL|macro|M68_SL_SEL2
mdefine_line|#define M68_SL_SEL2 0x44
DECL|macro|M69_SL_SEL2
mdefine_line|#define M69_SL_SEL2 0x45
DECL|macro|M70_SL_SEL2
mdefine_line|#define M70_SL_SEL2 0x46
DECL|macro|M71_SL_SEL2
mdefine_line|#define M71_SL_SEL2 0x47
DECL|macro|M72_SL_SEL2
mdefine_line|#define M72_SL_SEL2 0x48
DECL|macro|M73_SL_SEL2
mdefine_line|#define M73_SL_SEL2 0x49
DECL|macro|M74_SL_SEL2
mdefine_line|#define M74_SL_SEL2 0x4A
DECL|macro|M75_SL_SEL2
mdefine_line|#define M75_SL_SEL2 0x4B
DECL|macro|M76_SL_SEL2
mdefine_line|#define M76_SL_SEL2 0x4C
DECL|macro|M77_SL_SEL2
mdefine_line|#define M77_SL_SEL2 0x4D
DECL|macro|M78_SL_SEL2
mdefine_line|#define M78_SL_SEL2 0x4E
DECL|macro|M79_SL_SEL2
mdefine_line|#define M79_SL_SEL2 0x4F
DECL|macro|M80_SL_SEL2
mdefine_line|#define M80_SL_SEL2 0x50
DECL|macro|M81_SL_SEL2
mdefine_line|#define M81_SL_SEL2 0x51
DECL|macro|M82_SL_SEL2
mdefine_line|#define M82_SL_SEL2 0x52
DECL|macro|M83_SL_SEL2
mdefine_line|#define M83_SL_SEL2 0x53
DECL|macro|M84_SL_SEL2
mdefine_line|#define M84_SL_SEL2 0x54
DECL|macro|M85_SL_SEL2
mdefine_line|#define M85_SL_SEL2 0x55
DECL|macro|M86_SL_SEL2
mdefine_line|#define M86_SL_SEL2 0x56
DECL|macro|M87_SL_SEL2
mdefine_line|#define M87_SL_SEL2 0x57
DECL|macro|M88_SL_SEL2
mdefine_line|#define M88_SL_SEL2 0x58
DECL|macro|M89_SL_SEL2
mdefine_line|#define M89_SL_SEL2 0x59
DECL|macro|M90_SL_SEL2
mdefine_line|#define M90_SL_SEL2 0x5A
DECL|macro|M91_SL_SEL2
mdefine_line|#define M91_SL_SEL2 0x5B
DECL|macro|M92_SL_SEL2
mdefine_line|#define M92_SL_SEL2 0x5C
DECL|macro|M93_SL_SEL2
mdefine_line|#define M93_SL_SEL2 0x5D
DECL|macro|M94_SL_SEL2
mdefine_line|#define M94_SL_SEL2 0x5E
DECL|macro|M95_SL_SEL2
mdefine_line|#define M95_SL_SEL2 0x5F
DECL|macro|M96_SL_SEL2
mdefine_line|#define M96_SL_SEL2 0x60
DECL|macro|M97_SL_SEL2
mdefine_line|#define M97_SL_SEL2 0x61
DECL|macro|M98_SL_SEL2
mdefine_line|#define M98_SL_SEL2 0x62
DECL|macro|M99_SL_SEL2
mdefine_line|#define M99_SL_SEL2 0x63
DECL|macro|M100_SL_SEL2
mdefine_line|#define M100_SL_SEL2 0x64
DECL|macro|M101_SL_SEL2
mdefine_line|#define M101_SL_SEL2 0x65
DECL|macro|M102_SL_SEL2
mdefine_line|#define M102_SL_SEL2 0x66
DECL|macro|M103_SL_SEL2
mdefine_line|#define M103_SL_SEL2 0x67
DECL|macro|M104_SL_SEL2
mdefine_line|#define M104_SL_SEL2 0x68
DECL|macro|M105_SL_SEL2
mdefine_line|#define M105_SL_SEL2 0x69
DECL|macro|M106_SL_SEL2
mdefine_line|#define M106_SL_SEL2 0x6A
DECL|macro|M107_SL_SEL2
mdefine_line|#define M107_SL_SEL2 0x6B
DECL|macro|M108_SL_SEL2
mdefine_line|#define M108_SL_SEL2 0x6C
DECL|macro|M109_SL_SEL2
mdefine_line|#define M109_SL_SEL2 0x6D
DECL|macro|M110_SL_SEL2
mdefine_line|#define M110_SL_SEL2 0x6E
DECL|macro|M111_SL_SEL2
mdefine_line|#define M111_SL_SEL2 0x6F
DECL|macro|M112_SL_SEL2
mdefine_line|#define M112_SL_SEL2 0x70
DECL|macro|M113_SL_SEL2
mdefine_line|#define M113_SL_SEL2 0x71
DECL|macro|M114_SL_SEL2
mdefine_line|#define M114_SL_SEL2 0x72
DECL|macro|M115_SL_SEL2
mdefine_line|#define M115_SL_SEL2 0x73
DECL|macro|M116_SL_SEL2
mdefine_line|#define M116_SL_SEL2 0x74
DECL|macro|M117_SL_SEL2
mdefine_line|#define M117_SL_SEL2 0x75
DECL|macro|M118_SL_SEL2
mdefine_line|#define M118_SL_SEL2 0x76
DECL|macro|M119_SL_SEL2
mdefine_line|#define M119_SL_SEL2 0x77
DECL|macro|M120_SL_SEL2
mdefine_line|#define M120_SL_SEL2 0x78
DECL|macro|M121_SL_SEL2
mdefine_line|#define M121_SL_SEL2 0x79
DECL|macro|M122_SL_SEL2
mdefine_line|#define M122_SL_SEL2 0x7A
DECL|macro|M123_SL_SEL2
mdefine_line|#define M123_SL_SEL2 0x7B
DECL|macro|M124_SL_SEL2
mdefine_line|#define M124_SL_SEL2 0x7C
DECL|macro|M125_SL_SEL2
mdefine_line|#define M125_SL_SEL2 0x7D
DECL|macro|M126_SL_SEL2
mdefine_line|#define M126_SL_SEL2 0x7E
DECL|macro|M127_SL_SEL2
mdefine_line|#define M127_SL_SEL2 0x7F
DECL|macro|M_SH_SEL2
mdefine_line|#define M_SH_SEL2 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_sl_sel2
id|REGWORD
id|v_sl_sel2
suffix:colon
l_int|7
suffix:semicolon
DECL|member|v_sh_sel2
id|REGWORD
id|v_sh_sel2
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_sl_sel2
)brace
id|bit_r_sl_sel2
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_sl_sel2
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_sl_sel2
id|bit
suffix:semicolon
)brace
id|reg_r_sl_sel2
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_SL_SEL3
mdefine_line|#define R_SL_SEL3 0x15
DECL|macro|M_SL_SEL3
mdefine_line|#define M_SL_SEL3 0x7F
DECL|macro|M1_SL_SEL3
mdefine_line|#define M1_SL_SEL3 0x01
DECL|macro|M2_SL_SEL3
mdefine_line|#define M2_SL_SEL3 0x02
DECL|macro|M3_SL_SEL3
mdefine_line|#define M3_SL_SEL3 0x03
DECL|macro|M4_SL_SEL3
mdefine_line|#define M4_SL_SEL3 0x04
DECL|macro|M5_SL_SEL3
mdefine_line|#define M5_SL_SEL3 0x05
DECL|macro|M6_SL_SEL3
mdefine_line|#define M6_SL_SEL3 0x06
DECL|macro|M7_SL_SEL3
mdefine_line|#define M7_SL_SEL3 0x07
DECL|macro|M8_SL_SEL3
mdefine_line|#define M8_SL_SEL3 0x08
DECL|macro|M9_SL_SEL3
mdefine_line|#define M9_SL_SEL3 0x09
DECL|macro|M10_SL_SEL3
mdefine_line|#define M10_SL_SEL3 0x0A
DECL|macro|M11_SL_SEL3
mdefine_line|#define M11_SL_SEL3 0x0B
DECL|macro|M12_SL_SEL3
mdefine_line|#define M12_SL_SEL3 0x0C
DECL|macro|M13_SL_SEL3
mdefine_line|#define M13_SL_SEL3 0x0D
DECL|macro|M14_SL_SEL3
mdefine_line|#define M14_SL_SEL3 0x0E
DECL|macro|M15_SL_SEL3
mdefine_line|#define M15_SL_SEL3 0x0F
DECL|macro|M16_SL_SEL3
mdefine_line|#define M16_SL_SEL3 0x10
DECL|macro|M17_SL_SEL3
mdefine_line|#define M17_SL_SEL3 0x11
DECL|macro|M18_SL_SEL3
mdefine_line|#define M18_SL_SEL3 0x12
DECL|macro|M19_SL_SEL3
mdefine_line|#define M19_SL_SEL3 0x13
DECL|macro|M20_SL_SEL3
mdefine_line|#define M20_SL_SEL3 0x14
DECL|macro|M21_SL_SEL3
mdefine_line|#define M21_SL_SEL3 0x15
DECL|macro|M22_SL_SEL3
mdefine_line|#define M22_SL_SEL3 0x16
DECL|macro|M23_SL_SEL3
mdefine_line|#define M23_SL_SEL3 0x17
DECL|macro|M24_SL_SEL3
mdefine_line|#define M24_SL_SEL3 0x18
DECL|macro|M25_SL_SEL3
mdefine_line|#define M25_SL_SEL3 0x19
DECL|macro|M26_SL_SEL3
mdefine_line|#define M26_SL_SEL3 0x1A
DECL|macro|M27_SL_SEL3
mdefine_line|#define M27_SL_SEL3 0x1B
DECL|macro|M28_SL_SEL3
mdefine_line|#define M28_SL_SEL3 0x1C
DECL|macro|M29_SL_SEL3
mdefine_line|#define M29_SL_SEL3 0x1D
DECL|macro|M30_SL_SEL3
mdefine_line|#define M30_SL_SEL3 0x1E
DECL|macro|M31_SL_SEL3
mdefine_line|#define M31_SL_SEL3 0x1F
DECL|macro|M32_SL_SEL3
mdefine_line|#define M32_SL_SEL3 0x20
DECL|macro|M33_SL_SEL3
mdefine_line|#define M33_SL_SEL3 0x21
DECL|macro|M34_SL_SEL3
mdefine_line|#define M34_SL_SEL3 0x22
DECL|macro|M35_SL_SEL3
mdefine_line|#define M35_SL_SEL3 0x23
DECL|macro|M36_SL_SEL3
mdefine_line|#define M36_SL_SEL3 0x24
DECL|macro|M37_SL_SEL3
mdefine_line|#define M37_SL_SEL3 0x25
DECL|macro|M38_SL_SEL3
mdefine_line|#define M38_SL_SEL3 0x26
DECL|macro|M39_SL_SEL3
mdefine_line|#define M39_SL_SEL3 0x27
DECL|macro|M40_SL_SEL3
mdefine_line|#define M40_SL_SEL3 0x28
DECL|macro|M41_SL_SEL3
mdefine_line|#define M41_SL_SEL3 0x29
DECL|macro|M42_SL_SEL3
mdefine_line|#define M42_SL_SEL3 0x2A
DECL|macro|M43_SL_SEL3
mdefine_line|#define M43_SL_SEL3 0x2B
DECL|macro|M44_SL_SEL3
mdefine_line|#define M44_SL_SEL3 0x2C
DECL|macro|M45_SL_SEL3
mdefine_line|#define M45_SL_SEL3 0x2D
DECL|macro|M46_SL_SEL3
mdefine_line|#define M46_SL_SEL3 0x2E
DECL|macro|M47_SL_SEL3
mdefine_line|#define M47_SL_SEL3 0x2F
DECL|macro|M48_SL_SEL3
mdefine_line|#define M48_SL_SEL3 0x30
DECL|macro|M49_SL_SEL3
mdefine_line|#define M49_SL_SEL3 0x31
DECL|macro|M50_SL_SEL3
mdefine_line|#define M50_SL_SEL3 0x32
DECL|macro|M51_SL_SEL3
mdefine_line|#define M51_SL_SEL3 0x33
DECL|macro|M52_SL_SEL3
mdefine_line|#define M52_SL_SEL3 0x34
DECL|macro|M53_SL_SEL3
mdefine_line|#define M53_SL_SEL3 0x35
DECL|macro|M54_SL_SEL3
mdefine_line|#define M54_SL_SEL3 0x36
DECL|macro|M55_SL_SEL3
mdefine_line|#define M55_SL_SEL3 0x37
DECL|macro|M56_SL_SEL3
mdefine_line|#define M56_SL_SEL3 0x38
DECL|macro|M57_SL_SEL3
mdefine_line|#define M57_SL_SEL3 0x39
DECL|macro|M58_SL_SEL3
mdefine_line|#define M58_SL_SEL3 0x3A
DECL|macro|M59_SL_SEL3
mdefine_line|#define M59_SL_SEL3 0x3B
DECL|macro|M60_SL_SEL3
mdefine_line|#define M60_SL_SEL3 0x3C
DECL|macro|M61_SL_SEL3
mdefine_line|#define M61_SL_SEL3 0x3D
DECL|macro|M62_SL_SEL3
mdefine_line|#define M62_SL_SEL3 0x3E
DECL|macro|M63_SL_SEL3
mdefine_line|#define M63_SL_SEL3 0x3F
DECL|macro|M64_SL_SEL3
mdefine_line|#define M64_SL_SEL3 0x40
DECL|macro|M65_SL_SEL3
mdefine_line|#define M65_SL_SEL3 0x41
DECL|macro|M66_SL_SEL3
mdefine_line|#define M66_SL_SEL3 0x42
DECL|macro|M67_SL_SEL3
mdefine_line|#define M67_SL_SEL3 0x43
DECL|macro|M68_SL_SEL3
mdefine_line|#define M68_SL_SEL3 0x44
DECL|macro|M69_SL_SEL3
mdefine_line|#define M69_SL_SEL3 0x45
DECL|macro|M70_SL_SEL3
mdefine_line|#define M70_SL_SEL3 0x46
DECL|macro|M71_SL_SEL3
mdefine_line|#define M71_SL_SEL3 0x47
DECL|macro|M72_SL_SEL3
mdefine_line|#define M72_SL_SEL3 0x48
DECL|macro|M73_SL_SEL3
mdefine_line|#define M73_SL_SEL3 0x49
DECL|macro|M74_SL_SEL3
mdefine_line|#define M74_SL_SEL3 0x4A
DECL|macro|M75_SL_SEL3
mdefine_line|#define M75_SL_SEL3 0x4B
DECL|macro|M76_SL_SEL3
mdefine_line|#define M76_SL_SEL3 0x4C
DECL|macro|M77_SL_SEL3
mdefine_line|#define M77_SL_SEL3 0x4D
DECL|macro|M78_SL_SEL3
mdefine_line|#define M78_SL_SEL3 0x4E
DECL|macro|M79_SL_SEL3
mdefine_line|#define M79_SL_SEL3 0x4F
DECL|macro|M80_SL_SEL3
mdefine_line|#define M80_SL_SEL3 0x50
DECL|macro|M81_SL_SEL3
mdefine_line|#define M81_SL_SEL3 0x51
DECL|macro|M82_SL_SEL3
mdefine_line|#define M82_SL_SEL3 0x52
DECL|macro|M83_SL_SEL3
mdefine_line|#define M83_SL_SEL3 0x53
DECL|macro|M84_SL_SEL3
mdefine_line|#define M84_SL_SEL3 0x54
DECL|macro|M85_SL_SEL3
mdefine_line|#define M85_SL_SEL3 0x55
DECL|macro|M86_SL_SEL3
mdefine_line|#define M86_SL_SEL3 0x56
DECL|macro|M87_SL_SEL3
mdefine_line|#define M87_SL_SEL3 0x57
DECL|macro|M88_SL_SEL3
mdefine_line|#define M88_SL_SEL3 0x58
DECL|macro|M89_SL_SEL3
mdefine_line|#define M89_SL_SEL3 0x59
DECL|macro|M90_SL_SEL3
mdefine_line|#define M90_SL_SEL3 0x5A
DECL|macro|M91_SL_SEL3
mdefine_line|#define M91_SL_SEL3 0x5B
DECL|macro|M92_SL_SEL3
mdefine_line|#define M92_SL_SEL3 0x5C
DECL|macro|M93_SL_SEL3
mdefine_line|#define M93_SL_SEL3 0x5D
DECL|macro|M94_SL_SEL3
mdefine_line|#define M94_SL_SEL3 0x5E
DECL|macro|M95_SL_SEL3
mdefine_line|#define M95_SL_SEL3 0x5F
DECL|macro|M96_SL_SEL3
mdefine_line|#define M96_SL_SEL3 0x60
DECL|macro|M97_SL_SEL3
mdefine_line|#define M97_SL_SEL3 0x61
DECL|macro|M98_SL_SEL3
mdefine_line|#define M98_SL_SEL3 0x62
DECL|macro|M99_SL_SEL3
mdefine_line|#define M99_SL_SEL3 0x63
DECL|macro|M100_SL_SEL3
mdefine_line|#define M100_SL_SEL3 0x64
DECL|macro|M101_SL_SEL3
mdefine_line|#define M101_SL_SEL3 0x65
DECL|macro|M102_SL_SEL3
mdefine_line|#define M102_SL_SEL3 0x66
DECL|macro|M103_SL_SEL3
mdefine_line|#define M103_SL_SEL3 0x67
DECL|macro|M104_SL_SEL3
mdefine_line|#define M104_SL_SEL3 0x68
DECL|macro|M105_SL_SEL3
mdefine_line|#define M105_SL_SEL3 0x69
DECL|macro|M106_SL_SEL3
mdefine_line|#define M106_SL_SEL3 0x6A
DECL|macro|M107_SL_SEL3
mdefine_line|#define M107_SL_SEL3 0x6B
DECL|macro|M108_SL_SEL3
mdefine_line|#define M108_SL_SEL3 0x6C
DECL|macro|M109_SL_SEL3
mdefine_line|#define M109_SL_SEL3 0x6D
DECL|macro|M110_SL_SEL3
mdefine_line|#define M110_SL_SEL3 0x6E
DECL|macro|M111_SL_SEL3
mdefine_line|#define M111_SL_SEL3 0x6F
DECL|macro|M112_SL_SEL3
mdefine_line|#define M112_SL_SEL3 0x70
DECL|macro|M113_SL_SEL3
mdefine_line|#define M113_SL_SEL3 0x71
DECL|macro|M114_SL_SEL3
mdefine_line|#define M114_SL_SEL3 0x72
DECL|macro|M115_SL_SEL3
mdefine_line|#define M115_SL_SEL3 0x73
DECL|macro|M116_SL_SEL3
mdefine_line|#define M116_SL_SEL3 0x74
DECL|macro|M117_SL_SEL3
mdefine_line|#define M117_SL_SEL3 0x75
DECL|macro|M118_SL_SEL3
mdefine_line|#define M118_SL_SEL3 0x76
DECL|macro|M119_SL_SEL3
mdefine_line|#define M119_SL_SEL3 0x77
DECL|macro|M120_SL_SEL3
mdefine_line|#define M120_SL_SEL3 0x78
DECL|macro|M121_SL_SEL3
mdefine_line|#define M121_SL_SEL3 0x79
DECL|macro|M122_SL_SEL3
mdefine_line|#define M122_SL_SEL3 0x7A
DECL|macro|M123_SL_SEL3
mdefine_line|#define M123_SL_SEL3 0x7B
DECL|macro|M124_SL_SEL3
mdefine_line|#define M124_SL_SEL3 0x7C
DECL|macro|M125_SL_SEL3
mdefine_line|#define M125_SL_SEL3 0x7D
DECL|macro|M126_SL_SEL3
mdefine_line|#define M126_SL_SEL3 0x7E
DECL|macro|M127_SL_SEL3
mdefine_line|#define M127_SL_SEL3 0x7F
DECL|macro|M_SH_SEL3
mdefine_line|#define M_SH_SEL3 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_sl_sel3
id|REGWORD
id|v_sl_sel3
suffix:colon
l_int|7
suffix:semicolon
DECL|member|v_sh_sel3
id|REGWORD
id|v_sh_sel3
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_sl_sel3
)brace
id|bit_r_sl_sel3
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_sl_sel3
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_sl_sel3
id|bit
suffix:semicolon
)brace
id|reg_r_sl_sel3
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_SL_SEL4
mdefine_line|#define R_SL_SEL4 0x15
DECL|macro|M_SL_SEL4
mdefine_line|#define M_SL_SEL4 0x7F
DECL|macro|M1_SL_SEL4
mdefine_line|#define M1_SL_SEL4 0x01
DECL|macro|M2_SL_SEL4
mdefine_line|#define M2_SL_SEL4 0x02
DECL|macro|M3_SL_SEL4
mdefine_line|#define M3_SL_SEL4 0x03
DECL|macro|M4_SL_SEL4
mdefine_line|#define M4_SL_SEL4 0x04
DECL|macro|M5_SL_SEL4
mdefine_line|#define M5_SL_SEL4 0x05
DECL|macro|M6_SL_SEL4
mdefine_line|#define M6_SL_SEL4 0x06
DECL|macro|M7_SL_SEL4
mdefine_line|#define M7_SL_SEL4 0x07
DECL|macro|M8_SL_SEL4
mdefine_line|#define M8_SL_SEL4 0x08
DECL|macro|M9_SL_SEL4
mdefine_line|#define M9_SL_SEL4 0x09
DECL|macro|M10_SL_SEL4
mdefine_line|#define M10_SL_SEL4 0x0A
DECL|macro|M11_SL_SEL4
mdefine_line|#define M11_SL_SEL4 0x0B
DECL|macro|M12_SL_SEL4
mdefine_line|#define M12_SL_SEL4 0x0C
DECL|macro|M13_SL_SEL4
mdefine_line|#define M13_SL_SEL4 0x0D
DECL|macro|M14_SL_SEL4
mdefine_line|#define M14_SL_SEL4 0x0E
DECL|macro|M15_SL_SEL4
mdefine_line|#define M15_SL_SEL4 0x0F
DECL|macro|M16_SL_SEL4
mdefine_line|#define M16_SL_SEL4 0x10
DECL|macro|M17_SL_SEL4
mdefine_line|#define M17_SL_SEL4 0x11
DECL|macro|M18_SL_SEL4
mdefine_line|#define M18_SL_SEL4 0x12
DECL|macro|M19_SL_SEL4
mdefine_line|#define M19_SL_SEL4 0x13
DECL|macro|M20_SL_SEL4
mdefine_line|#define M20_SL_SEL4 0x14
DECL|macro|M21_SL_SEL4
mdefine_line|#define M21_SL_SEL4 0x15
DECL|macro|M22_SL_SEL4
mdefine_line|#define M22_SL_SEL4 0x16
DECL|macro|M23_SL_SEL4
mdefine_line|#define M23_SL_SEL4 0x17
DECL|macro|M24_SL_SEL4
mdefine_line|#define M24_SL_SEL4 0x18
DECL|macro|M25_SL_SEL4
mdefine_line|#define M25_SL_SEL4 0x19
DECL|macro|M26_SL_SEL4
mdefine_line|#define M26_SL_SEL4 0x1A
DECL|macro|M27_SL_SEL4
mdefine_line|#define M27_SL_SEL4 0x1B
DECL|macro|M28_SL_SEL4
mdefine_line|#define M28_SL_SEL4 0x1C
DECL|macro|M29_SL_SEL4
mdefine_line|#define M29_SL_SEL4 0x1D
DECL|macro|M30_SL_SEL4
mdefine_line|#define M30_SL_SEL4 0x1E
DECL|macro|M31_SL_SEL4
mdefine_line|#define M31_SL_SEL4 0x1F
DECL|macro|M32_SL_SEL4
mdefine_line|#define M32_SL_SEL4 0x20
DECL|macro|M33_SL_SEL4
mdefine_line|#define M33_SL_SEL4 0x21
DECL|macro|M34_SL_SEL4
mdefine_line|#define M34_SL_SEL4 0x22
DECL|macro|M35_SL_SEL4
mdefine_line|#define M35_SL_SEL4 0x23
DECL|macro|M36_SL_SEL4
mdefine_line|#define M36_SL_SEL4 0x24
DECL|macro|M37_SL_SEL4
mdefine_line|#define M37_SL_SEL4 0x25
DECL|macro|M38_SL_SEL4
mdefine_line|#define M38_SL_SEL4 0x26
DECL|macro|M39_SL_SEL4
mdefine_line|#define M39_SL_SEL4 0x27
DECL|macro|M40_SL_SEL4
mdefine_line|#define M40_SL_SEL4 0x28
DECL|macro|M41_SL_SEL4
mdefine_line|#define M41_SL_SEL4 0x29
DECL|macro|M42_SL_SEL4
mdefine_line|#define M42_SL_SEL4 0x2A
DECL|macro|M43_SL_SEL4
mdefine_line|#define M43_SL_SEL4 0x2B
DECL|macro|M44_SL_SEL4
mdefine_line|#define M44_SL_SEL4 0x2C
DECL|macro|M45_SL_SEL4
mdefine_line|#define M45_SL_SEL4 0x2D
DECL|macro|M46_SL_SEL4
mdefine_line|#define M46_SL_SEL4 0x2E
DECL|macro|M47_SL_SEL4
mdefine_line|#define M47_SL_SEL4 0x2F
DECL|macro|M48_SL_SEL4
mdefine_line|#define M48_SL_SEL4 0x30
DECL|macro|M49_SL_SEL4
mdefine_line|#define M49_SL_SEL4 0x31
DECL|macro|M50_SL_SEL4
mdefine_line|#define M50_SL_SEL4 0x32
DECL|macro|M51_SL_SEL4
mdefine_line|#define M51_SL_SEL4 0x33
DECL|macro|M52_SL_SEL4
mdefine_line|#define M52_SL_SEL4 0x34
DECL|macro|M53_SL_SEL4
mdefine_line|#define M53_SL_SEL4 0x35
DECL|macro|M54_SL_SEL4
mdefine_line|#define M54_SL_SEL4 0x36
DECL|macro|M55_SL_SEL4
mdefine_line|#define M55_SL_SEL4 0x37
DECL|macro|M56_SL_SEL4
mdefine_line|#define M56_SL_SEL4 0x38
DECL|macro|M57_SL_SEL4
mdefine_line|#define M57_SL_SEL4 0x39
DECL|macro|M58_SL_SEL4
mdefine_line|#define M58_SL_SEL4 0x3A
DECL|macro|M59_SL_SEL4
mdefine_line|#define M59_SL_SEL4 0x3B
DECL|macro|M60_SL_SEL4
mdefine_line|#define M60_SL_SEL4 0x3C
DECL|macro|M61_SL_SEL4
mdefine_line|#define M61_SL_SEL4 0x3D
DECL|macro|M62_SL_SEL4
mdefine_line|#define M62_SL_SEL4 0x3E
DECL|macro|M63_SL_SEL4
mdefine_line|#define M63_SL_SEL4 0x3F
DECL|macro|M64_SL_SEL4
mdefine_line|#define M64_SL_SEL4 0x40
DECL|macro|M65_SL_SEL4
mdefine_line|#define M65_SL_SEL4 0x41
DECL|macro|M66_SL_SEL4
mdefine_line|#define M66_SL_SEL4 0x42
DECL|macro|M67_SL_SEL4
mdefine_line|#define M67_SL_SEL4 0x43
DECL|macro|M68_SL_SEL4
mdefine_line|#define M68_SL_SEL4 0x44
DECL|macro|M69_SL_SEL4
mdefine_line|#define M69_SL_SEL4 0x45
DECL|macro|M70_SL_SEL4
mdefine_line|#define M70_SL_SEL4 0x46
DECL|macro|M71_SL_SEL4
mdefine_line|#define M71_SL_SEL4 0x47
DECL|macro|M72_SL_SEL4
mdefine_line|#define M72_SL_SEL4 0x48
DECL|macro|M73_SL_SEL4
mdefine_line|#define M73_SL_SEL4 0x49
DECL|macro|M74_SL_SEL4
mdefine_line|#define M74_SL_SEL4 0x4A
DECL|macro|M75_SL_SEL4
mdefine_line|#define M75_SL_SEL4 0x4B
DECL|macro|M76_SL_SEL4
mdefine_line|#define M76_SL_SEL4 0x4C
DECL|macro|M77_SL_SEL4
mdefine_line|#define M77_SL_SEL4 0x4D
DECL|macro|M78_SL_SEL4
mdefine_line|#define M78_SL_SEL4 0x4E
DECL|macro|M79_SL_SEL4
mdefine_line|#define M79_SL_SEL4 0x4F
DECL|macro|M80_SL_SEL4
mdefine_line|#define M80_SL_SEL4 0x50
DECL|macro|M81_SL_SEL4
mdefine_line|#define M81_SL_SEL4 0x51
DECL|macro|M82_SL_SEL4
mdefine_line|#define M82_SL_SEL4 0x52
DECL|macro|M83_SL_SEL4
mdefine_line|#define M83_SL_SEL4 0x53
DECL|macro|M84_SL_SEL4
mdefine_line|#define M84_SL_SEL4 0x54
DECL|macro|M85_SL_SEL4
mdefine_line|#define M85_SL_SEL4 0x55
DECL|macro|M86_SL_SEL4
mdefine_line|#define M86_SL_SEL4 0x56
DECL|macro|M87_SL_SEL4
mdefine_line|#define M87_SL_SEL4 0x57
DECL|macro|M88_SL_SEL4
mdefine_line|#define M88_SL_SEL4 0x58
DECL|macro|M89_SL_SEL4
mdefine_line|#define M89_SL_SEL4 0x59
DECL|macro|M90_SL_SEL4
mdefine_line|#define M90_SL_SEL4 0x5A
DECL|macro|M91_SL_SEL4
mdefine_line|#define M91_SL_SEL4 0x5B
DECL|macro|M92_SL_SEL4
mdefine_line|#define M92_SL_SEL4 0x5C
DECL|macro|M93_SL_SEL4
mdefine_line|#define M93_SL_SEL4 0x5D
DECL|macro|M94_SL_SEL4
mdefine_line|#define M94_SL_SEL4 0x5E
DECL|macro|M95_SL_SEL4
mdefine_line|#define M95_SL_SEL4 0x5F
DECL|macro|M96_SL_SEL4
mdefine_line|#define M96_SL_SEL4 0x60
DECL|macro|M97_SL_SEL4
mdefine_line|#define M97_SL_SEL4 0x61
DECL|macro|M98_SL_SEL4
mdefine_line|#define M98_SL_SEL4 0x62
DECL|macro|M99_SL_SEL4
mdefine_line|#define M99_SL_SEL4 0x63
DECL|macro|M100_SL_SEL4
mdefine_line|#define M100_SL_SEL4 0x64
DECL|macro|M101_SL_SEL4
mdefine_line|#define M101_SL_SEL4 0x65
DECL|macro|M102_SL_SEL4
mdefine_line|#define M102_SL_SEL4 0x66
DECL|macro|M103_SL_SEL4
mdefine_line|#define M103_SL_SEL4 0x67
DECL|macro|M104_SL_SEL4
mdefine_line|#define M104_SL_SEL4 0x68
DECL|macro|M105_SL_SEL4
mdefine_line|#define M105_SL_SEL4 0x69
DECL|macro|M106_SL_SEL4
mdefine_line|#define M106_SL_SEL4 0x6A
DECL|macro|M107_SL_SEL4
mdefine_line|#define M107_SL_SEL4 0x6B
DECL|macro|M108_SL_SEL4
mdefine_line|#define M108_SL_SEL4 0x6C
DECL|macro|M109_SL_SEL4
mdefine_line|#define M109_SL_SEL4 0x6D
DECL|macro|M110_SL_SEL4
mdefine_line|#define M110_SL_SEL4 0x6E
DECL|macro|M111_SL_SEL4
mdefine_line|#define M111_SL_SEL4 0x6F
DECL|macro|M112_SL_SEL4
mdefine_line|#define M112_SL_SEL4 0x70
DECL|macro|M113_SL_SEL4
mdefine_line|#define M113_SL_SEL4 0x71
DECL|macro|M114_SL_SEL4
mdefine_line|#define M114_SL_SEL4 0x72
DECL|macro|M115_SL_SEL4
mdefine_line|#define M115_SL_SEL4 0x73
DECL|macro|M116_SL_SEL4
mdefine_line|#define M116_SL_SEL4 0x74
DECL|macro|M117_SL_SEL4
mdefine_line|#define M117_SL_SEL4 0x75
DECL|macro|M118_SL_SEL4
mdefine_line|#define M118_SL_SEL4 0x76
DECL|macro|M119_SL_SEL4
mdefine_line|#define M119_SL_SEL4 0x77
DECL|macro|M120_SL_SEL4
mdefine_line|#define M120_SL_SEL4 0x78
DECL|macro|M121_SL_SEL4
mdefine_line|#define M121_SL_SEL4 0x79
DECL|macro|M122_SL_SEL4
mdefine_line|#define M122_SL_SEL4 0x7A
DECL|macro|M123_SL_SEL4
mdefine_line|#define M123_SL_SEL4 0x7B
DECL|macro|M124_SL_SEL4
mdefine_line|#define M124_SL_SEL4 0x7C
DECL|macro|M125_SL_SEL4
mdefine_line|#define M125_SL_SEL4 0x7D
DECL|macro|M126_SL_SEL4
mdefine_line|#define M126_SL_SEL4 0x7E
DECL|macro|M127_SL_SEL4
mdefine_line|#define M127_SL_SEL4 0x7F
DECL|macro|M_SH_SEL4
mdefine_line|#define M_SH_SEL4 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_sl_sel4
id|REGWORD
id|v_sl_sel4
suffix:colon
l_int|7
suffix:semicolon
DECL|member|v_sh_sel4
id|REGWORD
id|v_sh_sel4
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_sl_sel4
)brace
id|bit_r_sl_sel4
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_sl_sel4
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_sl_sel4
id|bit
suffix:semicolon
)brace
id|reg_r_sl_sel4
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_SL_SEL5
mdefine_line|#define R_SL_SEL5 0x15
DECL|macro|M_SL_SEL5
mdefine_line|#define M_SL_SEL5 0x7F
DECL|macro|M1_SL_SEL5
mdefine_line|#define M1_SL_SEL5 0x01
DECL|macro|M2_SL_SEL5
mdefine_line|#define M2_SL_SEL5 0x02
DECL|macro|M3_SL_SEL5
mdefine_line|#define M3_SL_SEL5 0x03
DECL|macro|M4_SL_SEL5
mdefine_line|#define M4_SL_SEL5 0x04
DECL|macro|M5_SL_SEL5
mdefine_line|#define M5_SL_SEL5 0x05
DECL|macro|M6_SL_SEL5
mdefine_line|#define M6_SL_SEL5 0x06
DECL|macro|M7_SL_SEL5
mdefine_line|#define M7_SL_SEL5 0x07
DECL|macro|M8_SL_SEL5
mdefine_line|#define M8_SL_SEL5 0x08
DECL|macro|M9_SL_SEL5
mdefine_line|#define M9_SL_SEL5 0x09
DECL|macro|M10_SL_SEL5
mdefine_line|#define M10_SL_SEL5 0x0A
DECL|macro|M11_SL_SEL5
mdefine_line|#define M11_SL_SEL5 0x0B
DECL|macro|M12_SL_SEL5
mdefine_line|#define M12_SL_SEL5 0x0C
DECL|macro|M13_SL_SEL5
mdefine_line|#define M13_SL_SEL5 0x0D
DECL|macro|M14_SL_SEL5
mdefine_line|#define M14_SL_SEL5 0x0E
DECL|macro|M15_SL_SEL5
mdefine_line|#define M15_SL_SEL5 0x0F
DECL|macro|M16_SL_SEL5
mdefine_line|#define M16_SL_SEL5 0x10
DECL|macro|M17_SL_SEL5
mdefine_line|#define M17_SL_SEL5 0x11
DECL|macro|M18_SL_SEL5
mdefine_line|#define M18_SL_SEL5 0x12
DECL|macro|M19_SL_SEL5
mdefine_line|#define M19_SL_SEL5 0x13
DECL|macro|M20_SL_SEL5
mdefine_line|#define M20_SL_SEL5 0x14
DECL|macro|M21_SL_SEL5
mdefine_line|#define M21_SL_SEL5 0x15
DECL|macro|M22_SL_SEL5
mdefine_line|#define M22_SL_SEL5 0x16
DECL|macro|M23_SL_SEL5
mdefine_line|#define M23_SL_SEL5 0x17
DECL|macro|M24_SL_SEL5
mdefine_line|#define M24_SL_SEL5 0x18
DECL|macro|M25_SL_SEL5
mdefine_line|#define M25_SL_SEL5 0x19
DECL|macro|M26_SL_SEL5
mdefine_line|#define M26_SL_SEL5 0x1A
DECL|macro|M27_SL_SEL5
mdefine_line|#define M27_SL_SEL5 0x1B
DECL|macro|M28_SL_SEL5
mdefine_line|#define M28_SL_SEL5 0x1C
DECL|macro|M29_SL_SEL5
mdefine_line|#define M29_SL_SEL5 0x1D
DECL|macro|M30_SL_SEL5
mdefine_line|#define M30_SL_SEL5 0x1E
DECL|macro|M31_SL_SEL5
mdefine_line|#define M31_SL_SEL5 0x1F
DECL|macro|M32_SL_SEL5
mdefine_line|#define M32_SL_SEL5 0x20
DECL|macro|M33_SL_SEL5
mdefine_line|#define M33_SL_SEL5 0x21
DECL|macro|M34_SL_SEL5
mdefine_line|#define M34_SL_SEL5 0x22
DECL|macro|M35_SL_SEL5
mdefine_line|#define M35_SL_SEL5 0x23
DECL|macro|M36_SL_SEL5
mdefine_line|#define M36_SL_SEL5 0x24
DECL|macro|M37_SL_SEL5
mdefine_line|#define M37_SL_SEL5 0x25
DECL|macro|M38_SL_SEL5
mdefine_line|#define M38_SL_SEL5 0x26
DECL|macro|M39_SL_SEL5
mdefine_line|#define M39_SL_SEL5 0x27
DECL|macro|M40_SL_SEL5
mdefine_line|#define M40_SL_SEL5 0x28
DECL|macro|M41_SL_SEL5
mdefine_line|#define M41_SL_SEL5 0x29
DECL|macro|M42_SL_SEL5
mdefine_line|#define M42_SL_SEL5 0x2A
DECL|macro|M43_SL_SEL5
mdefine_line|#define M43_SL_SEL5 0x2B
DECL|macro|M44_SL_SEL5
mdefine_line|#define M44_SL_SEL5 0x2C
DECL|macro|M45_SL_SEL5
mdefine_line|#define M45_SL_SEL5 0x2D
DECL|macro|M46_SL_SEL5
mdefine_line|#define M46_SL_SEL5 0x2E
DECL|macro|M47_SL_SEL5
mdefine_line|#define M47_SL_SEL5 0x2F
DECL|macro|M48_SL_SEL5
mdefine_line|#define M48_SL_SEL5 0x30
DECL|macro|M49_SL_SEL5
mdefine_line|#define M49_SL_SEL5 0x31
DECL|macro|M50_SL_SEL5
mdefine_line|#define M50_SL_SEL5 0x32
DECL|macro|M51_SL_SEL5
mdefine_line|#define M51_SL_SEL5 0x33
DECL|macro|M52_SL_SEL5
mdefine_line|#define M52_SL_SEL5 0x34
DECL|macro|M53_SL_SEL5
mdefine_line|#define M53_SL_SEL5 0x35
DECL|macro|M54_SL_SEL5
mdefine_line|#define M54_SL_SEL5 0x36
DECL|macro|M55_SL_SEL5
mdefine_line|#define M55_SL_SEL5 0x37
DECL|macro|M56_SL_SEL5
mdefine_line|#define M56_SL_SEL5 0x38
DECL|macro|M57_SL_SEL5
mdefine_line|#define M57_SL_SEL5 0x39
DECL|macro|M58_SL_SEL5
mdefine_line|#define M58_SL_SEL5 0x3A
DECL|macro|M59_SL_SEL5
mdefine_line|#define M59_SL_SEL5 0x3B
DECL|macro|M60_SL_SEL5
mdefine_line|#define M60_SL_SEL5 0x3C
DECL|macro|M61_SL_SEL5
mdefine_line|#define M61_SL_SEL5 0x3D
DECL|macro|M62_SL_SEL5
mdefine_line|#define M62_SL_SEL5 0x3E
DECL|macro|M63_SL_SEL5
mdefine_line|#define M63_SL_SEL5 0x3F
DECL|macro|M64_SL_SEL5
mdefine_line|#define M64_SL_SEL5 0x40
DECL|macro|M65_SL_SEL5
mdefine_line|#define M65_SL_SEL5 0x41
DECL|macro|M66_SL_SEL5
mdefine_line|#define M66_SL_SEL5 0x42
DECL|macro|M67_SL_SEL5
mdefine_line|#define M67_SL_SEL5 0x43
DECL|macro|M68_SL_SEL5
mdefine_line|#define M68_SL_SEL5 0x44
DECL|macro|M69_SL_SEL5
mdefine_line|#define M69_SL_SEL5 0x45
DECL|macro|M70_SL_SEL5
mdefine_line|#define M70_SL_SEL5 0x46
DECL|macro|M71_SL_SEL5
mdefine_line|#define M71_SL_SEL5 0x47
DECL|macro|M72_SL_SEL5
mdefine_line|#define M72_SL_SEL5 0x48
DECL|macro|M73_SL_SEL5
mdefine_line|#define M73_SL_SEL5 0x49
DECL|macro|M74_SL_SEL5
mdefine_line|#define M74_SL_SEL5 0x4A
DECL|macro|M75_SL_SEL5
mdefine_line|#define M75_SL_SEL5 0x4B
DECL|macro|M76_SL_SEL5
mdefine_line|#define M76_SL_SEL5 0x4C
DECL|macro|M77_SL_SEL5
mdefine_line|#define M77_SL_SEL5 0x4D
DECL|macro|M78_SL_SEL5
mdefine_line|#define M78_SL_SEL5 0x4E
DECL|macro|M79_SL_SEL5
mdefine_line|#define M79_SL_SEL5 0x4F
DECL|macro|M80_SL_SEL5
mdefine_line|#define M80_SL_SEL5 0x50
DECL|macro|M81_SL_SEL5
mdefine_line|#define M81_SL_SEL5 0x51
DECL|macro|M82_SL_SEL5
mdefine_line|#define M82_SL_SEL5 0x52
DECL|macro|M83_SL_SEL5
mdefine_line|#define M83_SL_SEL5 0x53
DECL|macro|M84_SL_SEL5
mdefine_line|#define M84_SL_SEL5 0x54
DECL|macro|M85_SL_SEL5
mdefine_line|#define M85_SL_SEL5 0x55
DECL|macro|M86_SL_SEL5
mdefine_line|#define M86_SL_SEL5 0x56
DECL|macro|M87_SL_SEL5
mdefine_line|#define M87_SL_SEL5 0x57
DECL|macro|M88_SL_SEL5
mdefine_line|#define M88_SL_SEL5 0x58
DECL|macro|M89_SL_SEL5
mdefine_line|#define M89_SL_SEL5 0x59
DECL|macro|M90_SL_SEL5
mdefine_line|#define M90_SL_SEL5 0x5A
DECL|macro|M91_SL_SEL5
mdefine_line|#define M91_SL_SEL5 0x5B
DECL|macro|M92_SL_SEL5
mdefine_line|#define M92_SL_SEL5 0x5C
DECL|macro|M93_SL_SEL5
mdefine_line|#define M93_SL_SEL5 0x5D
DECL|macro|M94_SL_SEL5
mdefine_line|#define M94_SL_SEL5 0x5E
DECL|macro|M95_SL_SEL5
mdefine_line|#define M95_SL_SEL5 0x5F
DECL|macro|M96_SL_SEL5
mdefine_line|#define M96_SL_SEL5 0x60
DECL|macro|M97_SL_SEL5
mdefine_line|#define M97_SL_SEL5 0x61
DECL|macro|M98_SL_SEL5
mdefine_line|#define M98_SL_SEL5 0x62
DECL|macro|M99_SL_SEL5
mdefine_line|#define M99_SL_SEL5 0x63
DECL|macro|M100_SL_SEL5
mdefine_line|#define M100_SL_SEL5 0x64
DECL|macro|M101_SL_SEL5
mdefine_line|#define M101_SL_SEL5 0x65
DECL|macro|M102_SL_SEL5
mdefine_line|#define M102_SL_SEL5 0x66
DECL|macro|M103_SL_SEL5
mdefine_line|#define M103_SL_SEL5 0x67
DECL|macro|M104_SL_SEL5
mdefine_line|#define M104_SL_SEL5 0x68
DECL|macro|M105_SL_SEL5
mdefine_line|#define M105_SL_SEL5 0x69
DECL|macro|M106_SL_SEL5
mdefine_line|#define M106_SL_SEL5 0x6A
DECL|macro|M107_SL_SEL5
mdefine_line|#define M107_SL_SEL5 0x6B
DECL|macro|M108_SL_SEL5
mdefine_line|#define M108_SL_SEL5 0x6C
DECL|macro|M109_SL_SEL5
mdefine_line|#define M109_SL_SEL5 0x6D
DECL|macro|M110_SL_SEL5
mdefine_line|#define M110_SL_SEL5 0x6E
DECL|macro|M111_SL_SEL5
mdefine_line|#define M111_SL_SEL5 0x6F
DECL|macro|M112_SL_SEL5
mdefine_line|#define M112_SL_SEL5 0x70
DECL|macro|M113_SL_SEL5
mdefine_line|#define M113_SL_SEL5 0x71
DECL|macro|M114_SL_SEL5
mdefine_line|#define M114_SL_SEL5 0x72
DECL|macro|M115_SL_SEL5
mdefine_line|#define M115_SL_SEL5 0x73
DECL|macro|M116_SL_SEL5
mdefine_line|#define M116_SL_SEL5 0x74
DECL|macro|M117_SL_SEL5
mdefine_line|#define M117_SL_SEL5 0x75
DECL|macro|M118_SL_SEL5
mdefine_line|#define M118_SL_SEL5 0x76
DECL|macro|M119_SL_SEL5
mdefine_line|#define M119_SL_SEL5 0x77
DECL|macro|M120_SL_SEL5
mdefine_line|#define M120_SL_SEL5 0x78
DECL|macro|M121_SL_SEL5
mdefine_line|#define M121_SL_SEL5 0x79
DECL|macro|M122_SL_SEL5
mdefine_line|#define M122_SL_SEL5 0x7A
DECL|macro|M123_SL_SEL5
mdefine_line|#define M123_SL_SEL5 0x7B
DECL|macro|M124_SL_SEL5
mdefine_line|#define M124_SL_SEL5 0x7C
DECL|macro|M125_SL_SEL5
mdefine_line|#define M125_SL_SEL5 0x7D
DECL|macro|M126_SL_SEL5
mdefine_line|#define M126_SL_SEL5 0x7E
DECL|macro|M127_SL_SEL5
mdefine_line|#define M127_SL_SEL5 0x7F
DECL|macro|M_SH_SEL5
mdefine_line|#define M_SH_SEL5 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_sl_sel5
id|REGWORD
id|v_sl_sel5
suffix:colon
l_int|7
suffix:semicolon
DECL|member|v_sh_sel5
id|REGWORD
id|v_sh_sel5
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_sl_sel5
)brace
id|bit_r_sl_sel5
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_sl_sel5
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_sl_sel5
id|bit
suffix:semicolon
)brace
id|reg_r_sl_sel5
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_SL_SEL6
mdefine_line|#define R_SL_SEL6 0x15
DECL|macro|M_SL_SEL6
mdefine_line|#define M_SL_SEL6 0x7F
DECL|macro|M1_SL_SEL6
mdefine_line|#define M1_SL_SEL6 0x01
DECL|macro|M2_SL_SEL6
mdefine_line|#define M2_SL_SEL6 0x02
DECL|macro|M3_SL_SEL6
mdefine_line|#define M3_SL_SEL6 0x03
DECL|macro|M4_SL_SEL6
mdefine_line|#define M4_SL_SEL6 0x04
DECL|macro|M5_SL_SEL6
mdefine_line|#define M5_SL_SEL6 0x05
DECL|macro|M6_SL_SEL6
mdefine_line|#define M6_SL_SEL6 0x06
DECL|macro|M7_SL_SEL6
mdefine_line|#define M7_SL_SEL6 0x07
DECL|macro|M8_SL_SEL6
mdefine_line|#define M8_SL_SEL6 0x08
DECL|macro|M9_SL_SEL6
mdefine_line|#define M9_SL_SEL6 0x09
DECL|macro|M10_SL_SEL6
mdefine_line|#define M10_SL_SEL6 0x0A
DECL|macro|M11_SL_SEL6
mdefine_line|#define M11_SL_SEL6 0x0B
DECL|macro|M12_SL_SEL6
mdefine_line|#define M12_SL_SEL6 0x0C
DECL|macro|M13_SL_SEL6
mdefine_line|#define M13_SL_SEL6 0x0D
DECL|macro|M14_SL_SEL6
mdefine_line|#define M14_SL_SEL6 0x0E
DECL|macro|M15_SL_SEL6
mdefine_line|#define M15_SL_SEL6 0x0F
DECL|macro|M16_SL_SEL6
mdefine_line|#define M16_SL_SEL6 0x10
DECL|macro|M17_SL_SEL6
mdefine_line|#define M17_SL_SEL6 0x11
DECL|macro|M18_SL_SEL6
mdefine_line|#define M18_SL_SEL6 0x12
DECL|macro|M19_SL_SEL6
mdefine_line|#define M19_SL_SEL6 0x13
DECL|macro|M20_SL_SEL6
mdefine_line|#define M20_SL_SEL6 0x14
DECL|macro|M21_SL_SEL6
mdefine_line|#define M21_SL_SEL6 0x15
DECL|macro|M22_SL_SEL6
mdefine_line|#define M22_SL_SEL6 0x16
DECL|macro|M23_SL_SEL6
mdefine_line|#define M23_SL_SEL6 0x17
DECL|macro|M24_SL_SEL6
mdefine_line|#define M24_SL_SEL6 0x18
DECL|macro|M25_SL_SEL6
mdefine_line|#define M25_SL_SEL6 0x19
DECL|macro|M26_SL_SEL6
mdefine_line|#define M26_SL_SEL6 0x1A
DECL|macro|M27_SL_SEL6
mdefine_line|#define M27_SL_SEL6 0x1B
DECL|macro|M28_SL_SEL6
mdefine_line|#define M28_SL_SEL6 0x1C
DECL|macro|M29_SL_SEL6
mdefine_line|#define M29_SL_SEL6 0x1D
DECL|macro|M30_SL_SEL6
mdefine_line|#define M30_SL_SEL6 0x1E
DECL|macro|M31_SL_SEL6
mdefine_line|#define M31_SL_SEL6 0x1F
DECL|macro|M32_SL_SEL6
mdefine_line|#define M32_SL_SEL6 0x20
DECL|macro|M33_SL_SEL6
mdefine_line|#define M33_SL_SEL6 0x21
DECL|macro|M34_SL_SEL6
mdefine_line|#define M34_SL_SEL6 0x22
DECL|macro|M35_SL_SEL6
mdefine_line|#define M35_SL_SEL6 0x23
DECL|macro|M36_SL_SEL6
mdefine_line|#define M36_SL_SEL6 0x24
DECL|macro|M37_SL_SEL6
mdefine_line|#define M37_SL_SEL6 0x25
DECL|macro|M38_SL_SEL6
mdefine_line|#define M38_SL_SEL6 0x26
DECL|macro|M39_SL_SEL6
mdefine_line|#define M39_SL_SEL6 0x27
DECL|macro|M40_SL_SEL6
mdefine_line|#define M40_SL_SEL6 0x28
DECL|macro|M41_SL_SEL6
mdefine_line|#define M41_SL_SEL6 0x29
DECL|macro|M42_SL_SEL6
mdefine_line|#define M42_SL_SEL6 0x2A
DECL|macro|M43_SL_SEL6
mdefine_line|#define M43_SL_SEL6 0x2B
DECL|macro|M44_SL_SEL6
mdefine_line|#define M44_SL_SEL6 0x2C
DECL|macro|M45_SL_SEL6
mdefine_line|#define M45_SL_SEL6 0x2D
DECL|macro|M46_SL_SEL6
mdefine_line|#define M46_SL_SEL6 0x2E
DECL|macro|M47_SL_SEL6
mdefine_line|#define M47_SL_SEL6 0x2F
DECL|macro|M48_SL_SEL6
mdefine_line|#define M48_SL_SEL6 0x30
DECL|macro|M49_SL_SEL6
mdefine_line|#define M49_SL_SEL6 0x31
DECL|macro|M50_SL_SEL6
mdefine_line|#define M50_SL_SEL6 0x32
DECL|macro|M51_SL_SEL6
mdefine_line|#define M51_SL_SEL6 0x33
DECL|macro|M52_SL_SEL6
mdefine_line|#define M52_SL_SEL6 0x34
DECL|macro|M53_SL_SEL6
mdefine_line|#define M53_SL_SEL6 0x35
DECL|macro|M54_SL_SEL6
mdefine_line|#define M54_SL_SEL6 0x36
DECL|macro|M55_SL_SEL6
mdefine_line|#define M55_SL_SEL6 0x37
DECL|macro|M56_SL_SEL6
mdefine_line|#define M56_SL_SEL6 0x38
DECL|macro|M57_SL_SEL6
mdefine_line|#define M57_SL_SEL6 0x39
DECL|macro|M58_SL_SEL6
mdefine_line|#define M58_SL_SEL6 0x3A
DECL|macro|M59_SL_SEL6
mdefine_line|#define M59_SL_SEL6 0x3B
DECL|macro|M60_SL_SEL6
mdefine_line|#define M60_SL_SEL6 0x3C
DECL|macro|M61_SL_SEL6
mdefine_line|#define M61_SL_SEL6 0x3D
DECL|macro|M62_SL_SEL6
mdefine_line|#define M62_SL_SEL6 0x3E
DECL|macro|M63_SL_SEL6
mdefine_line|#define M63_SL_SEL6 0x3F
DECL|macro|M64_SL_SEL6
mdefine_line|#define M64_SL_SEL6 0x40
DECL|macro|M65_SL_SEL6
mdefine_line|#define M65_SL_SEL6 0x41
DECL|macro|M66_SL_SEL6
mdefine_line|#define M66_SL_SEL6 0x42
DECL|macro|M67_SL_SEL6
mdefine_line|#define M67_SL_SEL6 0x43
DECL|macro|M68_SL_SEL6
mdefine_line|#define M68_SL_SEL6 0x44
DECL|macro|M69_SL_SEL6
mdefine_line|#define M69_SL_SEL6 0x45
DECL|macro|M70_SL_SEL6
mdefine_line|#define M70_SL_SEL6 0x46
DECL|macro|M71_SL_SEL6
mdefine_line|#define M71_SL_SEL6 0x47
DECL|macro|M72_SL_SEL6
mdefine_line|#define M72_SL_SEL6 0x48
DECL|macro|M73_SL_SEL6
mdefine_line|#define M73_SL_SEL6 0x49
DECL|macro|M74_SL_SEL6
mdefine_line|#define M74_SL_SEL6 0x4A
DECL|macro|M75_SL_SEL6
mdefine_line|#define M75_SL_SEL6 0x4B
DECL|macro|M76_SL_SEL6
mdefine_line|#define M76_SL_SEL6 0x4C
DECL|macro|M77_SL_SEL6
mdefine_line|#define M77_SL_SEL6 0x4D
DECL|macro|M78_SL_SEL6
mdefine_line|#define M78_SL_SEL6 0x4E
DECL|macro|M79_SL_SEL6
mdefine_line|#define M79_SL_SEL6 0x4F
DECL|macro|M80_SL_SEL6
mdefine_line|#define M80_SL_SEL6 0x50
DECL|macro|M81_SL_SEL6
mdefine_line|#define M81_SL_SEL6 0x51
DECL|macro|M82_SL_SEL6
mdefine_line|#define M82_SL_SEL6 0x52
DECL|macro|M83_SL_SEL6
mdefine_line|#define M83_SL_SEL6 0x53
DECL|macro|M84_SL_SEL6
mdefine_line|#define M84_SL_SEL6 0x54
DECL|macro|M85_SL_SEL6
mdefine_line|#define M85_SL_SEL6 0x55
DECL|macro|M86_SL_SEL6
mdefine_line|#define M86_SL_SEL6 0x56
DECL|macro|M87_SL_SEL6
mdefine_line|#define M87_SL_SEL6 0x57
DECL|macro|M88_SL_SEL6
mdefine_line|#define M88_SL_SEL6 0x58
DECL|macro|M89_SL_SEL6
mdefine_line|#define M89_SL_SEL6 0x59
DECL|macro|M90_SL_SEL6
mdefine_line|#define M90_SL_SEL6 0x5A
DECL|macro|M91_SL_SEL6
mdefine_line|#define M91_SL_SEL6 0x5B
DECL|macro|M92_SL_SEL6
mdefine_line|#define M92_SL_SEL6 0x5C
DECL|macro|M93_SL_SEL6
mdefine_line|#define M93_SL_SEL6 0x5D
DECL|macro|M94_SL_SEL6
mdefine_line|#define M94_SL_SEL6 0x5E
DECL|macro|M95_SL_SEL6
mdefine_line|#define M95_SL_SEL6 0x5F
DECL|macro|M96_SL_SEL6
mdefine_line|#define M96_SL_SEL6 0x60
DECL|macro|M97_SL_SEL6
mdefine_line|#define M97_SL_SEL6 0x61
DECL|macro|M98_SL_SEL6
mdefine_line|#define M98_SL_SEL6 0x62
DECL|macro|M99_SL_SEL6
mdefine_line|#define M99_SL_SEL6 0x63
DECL|macro|M100_SL_SEL6
mdefine_line|#define M100_SL_SEL6 0x64
DECL|macro|M101_SL_SEL6
mdefine_line|#define M101_SL_SEL6 0x65
DECL|macro|M102_SL_SEL6
mdefine_line|#define M102_SL_SEL6 0x66
DECL|macro|M103_SL_SEL6
mdefine_line|#define M103_SL_SEL6 0x67
DECL|macro|M104_SL_SEL6
mdefine_line|#define M104_SL_SEL6 0x68
DECL|macro|M105_SL_SEL6
mdefine_line|#define M105_SL_SEL6 0x69
DECL|macro|M106_SL_SEL6
mdefine_line|#define M106_SL_SEL6 0x6A
DECL|macro|M107_SL_SEL6
mdefine_line|#define M107_SL_SEL6 0x6B
DECL|macro|M108_SL_SEL6
mdefine_line|#define M108_SL_SEL6 0x6C
DECL|macro|M109_SL_SEL6
mdefine_line|#define M109_SL_SEL6 0x6D
DECL|macro|M110_SL_SEL6
mdefine_line|#define M110_SL_SEL6 0x6E
DECL|macro|M111_SL_SEL6
mdefine_line|#define M111_SL_SEL6 0x6F
DECL|macro|M112_SL_SEL6
mdefine_line|#define M112_SL_SEL6 0x70
DECL|macro|M113_SL_SEL6
mdefine_line|#define M113_SL_SEL6 0x71
DECL|macro|M114_SL_SEL6
mdefine_line|#define M114_SL_SEL6 0x72
DECL|macro|M115_SL_SEL6
mdefine_line|#define M115_SL_SEL6 0x73
DECL|macro|M116_SL_SEL6
mdefine_line|#define M116_SL_SEL6 0x74
DECL|macro|M117_SL_SEL6
mdefine_line|#define M117_SL_SEL6 0x75
DECL|macro|M118_SL_SEL6
mdefine_line|#define M118_SL_SEL6 0x76
DECL|macro|M119_SL_SEL6
mdefine_line|#define M119_SL_SEL6 0x77
DECL|macro|M120_SL_SEL6
mdefine_line|#define M120_SL_SEL6 0x78
DECL|macro|M121_SL_SEL6
mdefine_line|#define M121_SL_SEL6 0x79
DECL|macro|M122_SL_SEL6
mdefine_line|#define M122_SL_SEL6 0x7A
DECL|macro|M123_SL_SEL6
mdefine_line|#define M123_SL_SEL6 0x7B
DECL|macro|M124_SL_SEL6
mdefine_line|#define M124_SL_SEL6 0x7C
DECL|macro|M125_SL_SEL6
mdefine_line|#define M125_SL_SEL6 0x7D
DECL|macro|M126_SL_SEL6
mdefine_line|#define M126_SL_SEL6 0x7E
DECL|macro|M127_SL_SEL6
mdefine_line|#define M127_SL_SEL6 0x7F
DECL|macro|M_SH_SEL6
mdefine_line|#define M_SH_SEL6 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_sl_sel6
id|REGWORD
id|v_sl_sel6
suffix:colon
l_int|7
suffix:semicolon
DECL|member|v_sh_sel6
id|REGWORD
id|v_sh_sel6
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_sl_sel6
)brace
id|bit_r_sl_sel6
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_sl_sel6
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_sl_sel6
id|bit
suffix:semicolon
)brace
id|reg_r_sl_sel6
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_SL_SEL7
mdefine_line|#define R_SL_SEL7 0x15
DECL|macro|M_SL_SEL7
mdefine_line|#define M_SL_SEL7 0x7F
DECL|macro|M1_SL_SEL7
mdefine_line|#define M1_SL_SEL7 0x01
DECL|macro|M2_SL_SEL7
mdefine_line|#define M2_SL_SEL7 0x02
DECL|macro|M3_SL_SEL7
mdefine_line|#define M3_SL_SEL7 0x03
DECL|macro|M4_SL_SEL7
mdefine_line|#define M4_SL_SEL7 0x04
DECL|macro|M5_SL_SEL7
mdefine_line|#define M5_SL_SEL7 0x05
DECL|macro|M6_SL_SEL7
mdefine_line|#define M6_SL_SEL7 0x06
DECL|macro|M7_SL_SEL7
mdefine_line|#define M7_SL_SEL7 0x07
DECL|macro|M8_SL_SEL7
mdefine_line|#define M8_SL_SEL7 0x08
DECL|macro|M9_SL_SEL7
mdefine_line|#define M9_SL_SEL7 0x09
DECL|macro|M10_SL_SEL7
mdefine_line|#define M10_SL_SEL7 0x0A
DECL|macro|M11_SL_SEL7
mdefine_line|#define M11_SL_SEL7 0x0B
DECL|macro|M12_SL_SEL7
mdefine_line|#define M12_SL_SEL7 0x0C
DECL|macro|M13_SL_SEL7
mdefine_line|#define M13_SL_SEL7 0x0D
DECL|macro|M14_SL_SEL7
mdefine_line|#define M14_SL_SEL7 0x0E
DECL|macro|M15_SL_SEL7
mdefine_line|#define M15_SL_SEL7 0x0F
DECL|macro|M16_SL_SEL7
mdefine_line|#define M16_SL_SEL7 0x10
DECL|macro|M17_SL_SEL7
mdefine_line|#define M17_SL_SEL7 0x11
DECL|macro|M18_SL_SEL7
mdefine_line|#define M18_SL_SEL7 0x12
DECL|macro|M19_SL_SEL7
mdefine_line|#define M19_SL_SEL7 0x13
DECL|macro|M20_SL_SEL7
mdefine_line|#define M20_SL_SEL7 0x14
DECL|macro|M21_SL_SEL7
mdefine_line|#define M21_SL_SEL7 0x15
DECL|macro|M22_SL_SEL7
mdefine_line|#define M22_SL_SEL7 0x16
DECL|macro|M23_SL_SEL7
mdefine_line|#define M23_SL_SEL7 0x17
DECL|macro|M24_SL_SEL7
mdefine_line|#define M24_SL_SEL7 0x18
DECL|macro|M25_SL_SEL7
mdefine_line|#define M25_SL_SEL7 0x19
DECL|macro|M26_SL_SEL7
mdefine_line|#define M26_SL_SEL7 0x1A
DECL|macro|M27_SL_SEL7
mdefine_line|#define M27_SL_SEL7 0x1B
DECL|macro|M28_SL_SEL7
mdefine_line|#define M28_SL_SEL7 0x1C
DECL|macro|M29_SL_SEL7
mdefine_line|#define M29_SL_SEL7 0x1D
DECL|macro|M30_SL_SEL7
mdefine_line|#define M30_SL_SEL7 0x1E
DECL|macro|M31_SL_SEL7
mdefine_line|#define M31_SL_SEL7 0x1F
DECL|macro|M32_SL_SEL7
mdefine_line|#define M32_SL_SEL7 0x20
DECL|macro|M33_SL_SEL7
mdefine_line|#define M33_SL_SEL7 0x21
DECL|macro|M34_SL_SEL7
mdefine_line|#define M34_SL_SEL7 0x22
DECL|macro|M35_SL_SEL7
mdefine_line|#define M35_SL_SEL7 0x23
DECL|macro|M36_SL_SEL7
mdefine_line|#define M36_SL_SEL7 0x24
DECL|macro|M37_SL_SEL7
mdefine_line|#define M37_SL_SEL7 0x25
DECL|macro|M38_SL_SEL7
mdefine_line|#define M38_SL_SEL7 0x26
DECL|macro|M39_SL_SEL7
mdefine_line|#define M39_SL_SEL7 0x27
DECL|macro|M40_SL_SEL7
mdefine_line|#define M40_SL_SEL7 0x28
DECL|macro|M41_SL_SEL7
mdefine_line|#define M41_SL_SEL7 0x29
DECL|macro|M42_SL_SEL7
mdefine_line|#define M42_SL_SEL7 0x2A
DECL|macro|M43_SL_SEL7
mdefine_line|#define M43_SL_SEL7 0x2B
DECL|macro|M44_SL_SEL7
mdefine_line|#define M44_SL_SEL7 0x2C
DECL|macro|M45_SL_SEL7
mdefine_line|#define M45_SL_SEL7 0x2D
DECL|macro|M46_SL_SEL7
mdefine_line|#define M46_SL_SEL7 0x2E
DECL|macro|M47_SL_SEL7
mdefine_line|#define M47_SL_SEL7 0x2F
DECL|macro|M48_SL_SEL7
mdefine_line|#define M48_SL_SEL7 0x30
DECL|macro|M49_SL_SEL7
mdefine_line|#define M49_SL_SEL7 0x31
DECL|macro|M50_SL_SEL7
mdefine_line|#define M50_SL_SEL7 0x32
DECL|macro|M51_SL_SEL7
mdefine_line|#define M51_SL_SEL7 0x33
DECL|macro|M52_SL_SEL7
mdefine_line|#define M52_SL_SEL7 0x34
DECL|macro|M53_SL_SEL7
mdefine_line|#define M53_SL_SEL7 0x35
DECL|macro|M54_SL_SEL7
mdefine_line|#define M54_SL_SEL7 0x36
DECL|macro|M55_SL_SEL7
mdefine_line|#define M55_SL_SEL7 0x37
DECL|macro|M56_SL_SEL7
mdefine_line|#define M56_SL_SEL7 0x38
DECL|macro|M57_SL_SEL7
mdefine_line|#define M57_SL_SEL7 0x39
DECL|macro|M58_SL_SEL7
mdefine_line|#define M58_SL_SEL7 0x3A
DECL|macro|M59_SL_SEL7
mdefine_line|#define M59_SL_SEL7 0x3B
DECL|macro|M60_SL_SEL7
mdefine_line|#define M60_SL_SEL7 0x3C
DECL|macro|M61_SL_SEL7
mdefine_line|#define M61_SL_SEL7 0x3D
DECL|macro|M62_SL_SEL7
mdefine_line|#define M62_SL_SEL7 0x3E
DECL|macro|M63_SL_SEL7
mdefine_line|#define M63_SL_SEL7 0x3F
DECL|macro|M64_SL_SEL7
mdefine_line|#define M64_SL_SEL7 0x40
DECL|macro|M65_SL_SEL7
mdefine_line|#define M65_SL_SEL7 0x41
DECL|macro|M66_SL_SEL7
mdefine_line|#define M66_SL_SEL7 0x42
DECL|macro|M67_SL_SEL7
mdefine_line|#define M67_SL_SEL7 0x43
DECL|macro|M68_SL_SEL7
mdefine_line|#define M68_SL_SEL7 0x44
DECL|macro|M69_SL_SEL7
mdefine_line|#define M69_SL_SEL7 0x45
DECL|macro|M70_SL_SEL7
mdefine_line|#define M70_SL_SEL7 0x46
DECL|macro|M71_SL_SEL7
mdefine_line|#define M71_SL_SEL7 0x47
DECL|macro|M72_SL_SEL7
mdefine_line|#define M72_SL_SEL7 0x48
DECL|macro|M73_SL_SEL7
mdefine_line|#define M73_SL_SEL7 0x49
DECL|macro|M74_SL_SEL7
mdefine_line|#define M74_SL_SEL7 0x4A
DECL|macro|M75_SL_SEL7
mdefine_line|#define M75_SL_SEL7 0x4B
DECL|macro|M76_SL_SEL7
mdefine_line|#define M76_SL_SEL7 0x4C
DECL|macro|M77_SL_SEL7
mdefine_line|#define M77_SL_SEL7 0x4D
DECL|macro|M78_SL_SEL7
mdefine_line|#define M78_SL_SEL7 0x4E
DECL|macro|M79_SL_SEL7
mdefine_line|#define M79_SL_SEL7 0x4F
DECL|macro|M80_SL_SEL7
mdefine_line|#define M80_SL_SEL7 0x50
DECL|macro|M81_SL_SEL7
mdefine_line|#define M81_SL_SEL7 0x51
DECL|macro|M82_SL_SEL7
mdefine_line|#define M82_SL_SEL7 0x52
DECL|macro|M83_SL_SEL7
mdefine_line|#define M83_SL_SEL7 0x53
DECL|macro|M84_SL_SEL7
mdefine_line|#define M84_SL_SEL7 0x54
DECL|macro|M85_SL_SEL7
mdefine_line|#define M85_SL_SEL7 0x55
DECL|macro|M86_SL_SEL7
mdefine_line|#define M86_SL_SEL7 0x56
DECL|macro|M87_SL_SEL7
mdefine_line|#define M87_SL_SEL7 0x57
DECL|macro|M88_SL_SEL7
mdefine_line|#define M88_SL_SEL7 0x58
DECL|macro|M89_SL_SEL7
mdefine_line|#define M89_SL_SEL7 0x59
DECL|macro|M90_SL_SEL7
mdefine_line|#define M90_SL_SEL7 0x5A
DECL|macro|M91_SL_SEL7
mdefine_line|#define M91_SL_SEL7 0x5B
DECL|macro|M92_SL_SEL7
mdefine_line|#define M92_SL_SEL7 0x5C
DECL|macro|M93_SL_SEL7
mdefine_line|#define M93_SL_SEL7 0x5D
DECL|macro|M94_SL_SEL7
mdefine_line|#define M94_SL_SEL7 0x5E
DECL|macro|M95_SL_SEL7
mdefine_line|#define M95_SL_SEL7 0x5F
DECL|macro|M96_SL_SEL7
mdefine_line|#define M96_SL_SEL7 0x60
DECL|macro|M97_SL_SEL7
mdefine_line|#define M97_SL_SEL7 0x61
DECL|macro|M98_SL_SEL7
mdefine_line|#define M98_SL_SEL7 0x62
DECL|macro|M99_SL_SEL7
mdefine_line|#define M99_SL_SEL7 0x63
DECL|macro|M100_SL_SEL7
mdefine_line|#define M100_SL_SEL7 0x64
DECL|macro|M101_SL_SEL7
mdefine_line|#define M101_SL_SEL7 0x65
DECL|macro|M102_SL_SEL7
mdefine_line|#define M102_SL_SEL7 0x66
DECL|macro|M103_SL_SEL7
mdefine_line|#define M103_SL_SEL7 0x67
DECL|macro|M104_SL_SEL7
mdefine_line|#define M104_SL_SEL7 0x68
DECL|macro|M105_SL_SEL7
mdefine_line|#define M105_SL_SEL7 0x69
DECL|macro|M106_SL_SEL7
mdefine_line|#define M106_SL_SEL7 0x6A
DECL|macro|M107_SL_SEL7
mdefine_line|#define M107_SL_SEL7 0x6B
DECL|macro|M108_SL_SEL7
mdefine_line|#define M108_SL_SEL7 0x6C
DECL|macro|M109_SL_SEL7
mdefine_line|#define M109_SL_SEL7 0x6D
DECL|macro|M110_SL_SEL7
mdefine_line|#define M110_SL_SEL7 0x6E
DECL|macro|M111_SL_SEL7
mdefine_line|#define M111_SL_SEL7 0x6F
DECL|macro|M112_SL_SEL7
mdefine_line|#define M112_SL_SEL7 0x70
DECL|macro|M113_SL_SEL7
mdefine_line|#define M113_SL_SEL7 0x71
DECL|macro|M114_SL_SEL7
mdefine_line|#define M114_SL_SEL7 0x72
DECL|macro|M115_SL_SEL7
mdefine_line|#define M115_SL_SEL7 0x73
DECL|macro|M116_SL_SEL7
mdefine_line|#define M116_SL_SEL7 0x74
DECL|macro|M117_SL_SEL7
mdefine_line|#define M117_SL_SEL7 0x75
DECL|macro|M118_SL_SEL7
mdefine_line|#define M118_SL_SEL7 0x76
DECL|macro|M119_SL_SEL7
mdefine_line|#define M119_SL_SEL7 0x77
DECL|macro|M120_SL_SEL7
mdefine_line|#define M120_SL_SEL7 0x78
DECL|macro|M121_SL_SEL7
mdefine_line|#define M121_SL_SEL7 0x79
DECL|macro|M122_SL_SEL7
mdefine_line|#define M122_SL_SEL7 0x7A
DECL|macro|M123_SL_SEL7
mdefine_line|#define M123_SL_SEL7 0x7B
DECL|macro|M124_SL_SEL7
mdefine_line|#define M124_SL_SEL7 0x7C
DECL|macro|M125_SL_SEL7
mdefine_line|#define M125_SL_SEL7 0x7D
DECL|macro|M126_SL_SEL7
mdefine_line|#define M126_SL_SEL7 0x7E
DECL|macro|M127_SL_SEL7
mdefine_line|#define M127_SL_SEL7 0x7F
DECL|macro|M_SH_SEL7
mdefine_line|#define M_SH_SEL7 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_sl_sel7
id|REGWORD
id|v_sl_sel7
suffix:colon
l_int|7
suffix:semicolon
DECL|member|v_sh_sel7
id|REGWORD
id|v_sh_sel7
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_sl_sel7
)brace
id|bit_r_sl_sel7
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_sl_sel7
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_sl_sel7
id|bit
suffix:semicolon
)brace
id|reg_r_sl_sel7
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_PCM_MD1
mdefine_line|#define R_PCM_MD1 0x15
DECL|macro|M_DEC_CNT
mdefine_line|#define M_DEC_CNT 0x01
DECL|macro|M_PLL_ADJ_SPEED
mdefine_line|#define M_PLL_ADJ_SPEED 0x0C
DECL|macro|M1_PLL_ADJ_SPEED
mdefine_line|#define M1_PLL_ADJ_SPEED 0x04
DECL|macro|M2_PLL_ADJ_SPEED
mdefine_line|#define M2_PLL_ADJ_SPEED 0x08
DECL|macro|M3_PLL_ADJ_SPEED
mdefine_line|#define M3_PLL_ADJ_SPEED 0x0C
DECL|macro|M_PCM_DR
mdefine_line|#define M_PCM_DR 0x30
DECL|macro|M1_PCM_DR
mdefine_line|#define M1_PCM_DR 0x10
DECL|macro|M2_PCM_DR
mdefine_line|#define M2_PCM_DR 0x20
DECL|macro|M3_PCM_DR
mdefine_line|#define M3_PCM_DR 0x30
DECL|macro|M_PCM_LOOP
mdefine_line|#define M_PCM_LOOP 0x40
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_dec_cnt
id|REGWORD
id|v_dec_cnt
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_25
id|REGWORD
id|reserved_25
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_pll_adj_speed
id|REGWORD
id|v_pll_adj_speed
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_pcm_dr
id|REGWORD
id|v_pcm_dr
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_pcm_loop
id|REGWORD
id|v_pcm_loop
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_26
id|REGWORD
id|reserved_26
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_pcm_md1
)brace
id|bit_r_pcm_md1
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_pcm_md1
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_pcm_md1
id|bit
suffix:semicolon
)brace
id|reg_r_pcm_md1
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_PCM_MD2
mdefine_line|#define R_PCM_MD2 0x15
DECL|macro|M_SYNC_SRC
mdefine_line|#define M_SYNC_SRC 0x04
DECL|macro|M_SYNC_OUT
mdefine_line|#define M_SYNC_OUT 0x08
DECL|macro|M_ICR_FR_TIME
mdefine_line|#define M_ICR_FR_TIME 0x40
DECL|macro|M_EN_PLL
mdefine_line|#define M_EN_PLL 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|reserved_27
id|REGWORD
id|reserved_27
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_sync_src
id|REGWORD
id|v_sync_src
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_sync_out
id|REGWORD
id|v_sync_out
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_28
id|REGWORD
id|reserved_28
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_icr_fr_time
id|REGWORD
id|v_icr_fr_time
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_en_pll
id|REGWORD
id|v_en_pll
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_pcm_md2
)brace
id|bit_r_pcm_md2
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_pcm_md2
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_pcm_md2
id|bit
suffix:semicolon
)brace
id|reg_r_pcm_md2
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_SH0L
mdefine_line|#define R_SH0L 0x15
DECL|macro|M_SH0L
mdefine_line|#define M_SH0L 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_sh0l
id|REGWORD
id|v_sh0l
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_r_sh0l
)brace
id|bit_r_sh0l
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_sh0l
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_sh0l
id|bit
suffix:semicolon
)brace
id|reg_r_sh0l
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_SH0H
mdefine_line|#define R_SH0H 0x15
DECL|macro|M_SH0H
mdefine_line|#define M_SH0H 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_sh0h
id|REGWORD
id|v_sh0h
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_r_sh0h
)brace
id|bit_r_sh0h
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_sh0h
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_sh0h
id|bit
suffix:semicolon
)brace
id|reg_r_sh0h
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_SH1L
mdefine_line|#define R_SH1L 0x15
DECL|macro|M_SH1L
mdefine_line|#define M_SH1L 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_sh1l
id|REGWORD
id|v_sh1l
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_r_sh1l
)brace
id|bit_r_sh1l
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_sh1l
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_sh1l
id|bit
suffix:semicolon
)brace
id|reg_r_sh1l
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_SH1H
mdefine_line|#define R_SH1H 0x15
DECL|macro|M_SH1H
mdefine_line|#define M_SH1H 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_sh1h
id|REGWORD
id|v_sh1h
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_r_sh1h
)brace
id|bit_r_sh1h
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_sh1h
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_sh1h
id|bit
suffix:semicolon
)brace
id|reg_r_sh1h
suffix:semicolon
singleline_comment|// register and bitmap access
DECL|macro|R_IRQ_OVIEW
mdefine_line|#define R_IRQ_OVIEW 0x10
DECL|macro|M_IRQ_FIFO_BL0
mdefine_line|#define M_IRQ_FIFO_BL0 0x01
DECL|macro|M_IRQ_FIFO_BL1
mdefine_line|#define M_IRQ_FIFO_BL1 0x02
DECL|macro|M_IRQ_FIFO_BL2
mdefine_line|#define M_IRQ_FIFO_BL2 0x04
DECL|macro|M_IRQ_FIFO_BL3
mdefine_line|#define M_IRQ_FIFO_BL3 0x08
DECL|macro|M_IRQ_FIFO_BL4
mdefine_line|#define M_IRQ_FIFO_BL4 0x10
DECL|macro|M_IRQ_FIFO_BL5
mdefine_line|#define M_IRQ_FIFO_BL5 0x20
DECL|macro|M_IRQ_FIFO_BL6
mdefine_line|#define M_IRQ_FIFO_BL6 0x40
DECL|macro|M_IRQ_FIFO_BL7
mdefine_line|#define M_IRQ_FIFO_BL7 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_irq_fifo_bl0
id|REGWORD
id|v_irq_fifo_bl0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo_bl1
id|REGWORD
id|v_irq_fifo_bl1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo_bl2
id|REGWORD
id|v_irq_fifo_bl2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo_bl3
id|REGWORD
id|v_irq_fifo_bl3
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo_bl4
id|REGWORD
id|v_irq_fifo_bl4
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo_bl5
id|REGWORD
id|v_irq_fifo_bl5
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo_bl6
id|REGWORD
id|v_irq_fifo_bl6
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo_bl7
id|REGWORD
id|v_irq_fifo_bl7
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_irq_oview
)brace
id|bit_r_irq_oview
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_irq_oview
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_irq_oview
id|bit
suffix:semicolon
)brace
id|reg_r_irq_oview
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_IRQ_MISC
mdefine_line|#define R_IRQ_MISC 0x11
DECL|macro|M_TI_IRQ
mdefine_line|#define M_TI_IRQ 0x02
DECL|macro|M_IRQ_PROC
mdefine_line|#define M_IRQ_PROC 0x04
DECL|macro|M_DTMF_IRQ
mdefine_line|#define M_DTMF_IRQ 0x08
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|reserved_30
id|REGWORD
id|reserved_30
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_ti_irq
id|REGWORD
id|v_ti_irq
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_proc
id|REGWORD
id|v_irq_proc
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_dtmf_irq
id|REGWORD
id|v_dtmf_irq
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_32
id|REGWORD
id|reserved_32
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_34
id|REGWORD
id|reserved_34
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_36
id|REGWORD
id|reserved_36
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_38
id|REGWORD
id|reserved_38
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_irq_misc
)brace
id|bit_r_irq_misc
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_irq_misc
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_irq_misc
id|bit
suffix:semicolon
)brace
id|reg_r_irq_misc
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_CONF_OFLOW
mdefine_line|#define R_CONF_OFLOW 0x14
DECL|macro|M_CONF_OFLOW0
mdefine_line|#define M_CONF_OFLOW0 0x01
DECL|macro|M_CONF_OFLOW1
mdefine_line|#define M_CONF_OFLOW1 0x02
DECL|macro|M_CONF_OFLOW2
mdefine_line|#define M_CONF_OFLOW2 0x04
DECL|macro|M_CONF_OFLOW3
mdefine_line|#define M_CONF_OFLOW3 0x08
DECL|macro|M_CONF_OFLOW4
mdefine_line|#define M_CONF_OFLOW4 0x10
DECL|macro|M_CONF_OFLOW5
mdefine_line|#define M_CONF_OFLOW5 0x20
DECL|macro|M_CONF_OFLOW6
mdefine_line|#define M_CONF_OFLOW6 0x40
DECL|macro|M_CONF_OFLOW7
mdefine_line|#define M_CONF_OFLOW7 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_conf_oflow0
id|REGWORD
id|v_conf_oflow0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_conf_oflow1
id|REGWORD
id|v_conf_oflow1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_conf_oflow2
id|REGWORD
id|v_conf_oflow2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_conf_oflow3
id|REGWORD
id|v_conf_oflow3
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_conf_oflow4
id|REGWORD
id|v_conf_oflow4
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_conf_oflow5
id|REGWORD
id|v_conf_oflow5
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_conf_oflow6
id|REGWORD
id|v_conf_oflow6
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_conf_oflow7
id|REGWORD
id|v_conf_oflow7
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_conf_oflow
)brace
id|bit_r_conf_oflow
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_conf_oflow
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_conf_oflow
id|bit
suffix:semicolon
)brace
id|reg_r_conf_oflow
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_CHIP_ID
mdefine_line|#define R_CHIP_ID 0x16
DECL|macro|R_CHIP_RV
mdefine_line|#define R_CHIP_RV 0x1F
DECL|macro|M_PNP_IRQ
mdefine_line|#define M_PNP_IRQ 0x0F
DECL|macro|M1_PNP_IRQ
mdefine_line|#define M1_PNP_IRQ 0x01
DECL|macro|M2_PNP_IRQ
mdefine_line|#define M2_PNP_IRQ 0x02
DECL|macro|M3_PNP_IRQ
mdefine_line|#define M3_PNP_IRQ 0x03
DECL|macro|M4_PNP_IRQ
mdefine_line|#define M4_PNP_IRQ 0x04
DECL|macro|M5_PNP_IRQ
mdefine_line|#define M5_PNP_IRQ 0x05
DECL|macro|M6_PNP_IRQ
mdefine_line|#define M6_PNP_IRQ 0x06
DECL|macro|M7_PNP_IRQ
mdefine_line|#define M7_PNP_IRQ 0x07
DECL|macro|M8_PNP_IRQ
mdefine_line|#define M8_PNP_IRQ 0x08
DECL|macro|M9_PNP_IRQ
mdefine_line|#define M9_PNP_IRQ 0x09
DECL|macro|M10_PNP_IRQ
mdefine_line|#define M10_PNP_IRQ 0x0A
DECL|macro|M11_PNP_IRQ
mdefine_line|#define M11_PNP_IRQ 0x0B
DECL|macro|M12_PNP_IRQ
mdefine_line|#define M12_PNP_IRQ 0x0C
DECL|macro|M13_PNP_IRQ
mdefine_line|#define M13_PNP_IRQ 0x0D
DECL|macro|M14_PNP_IRQ
mdefine_line|#define M14_PNP_IRQ 0x0E
DECL|macro|M15_PNP_IRQ
mdefine_line|#define M15_PNP_IRQ 0x0F
DECL|macro|M_CHIP_ID
mdefine_line|#define M_CHIP_ID 0xF0
DECL|macro|M1_CHIP_ID
mdefine_line|#define M1_CHIP_ID 0x10
DECL|macro|M2_CHIP_ID
mdefine_line|#define M2_CHIP_ID 0x20
DECL|macro|M3_CHIP_ID
mdefine_line|#define M3_CHIP_ID 0x30
DECL|macro|M4_CHIP_ID
mdefine_line|#define M4_CHIP_ID 0x40
DECL|macro|M5_CHIP_ID
mdefine_line|#define M5_CHIP_ID 0x50
DECL|macro|M6_CHIP_ID
mdefine_line|#define M6_CHIP_ID 0x60
DECL|macro|M7_CHIP_ID
mdefine_line|#define M7_CHIP_ID 0x70
DECL|macro|M8_CHIP_ID
mdefine_line|#define M8_CHIP_ID 0x80
DECL|macro|M9_CHIP_ID
mdefine_line|#define M9_CHIP_ID 0x90
DECL|macro|M10_CHIP_ID
mdefine_line|#define M10_CHIP_ID 0xA0
DECL|macro|M11_CHIP_ID
mdefine_line|#define M11_CHIP_ID 0xB0
DECL|macro|M12_CHIP_ID
mdefine_line|#define M12_CHIP_ID 0xC0
DECL|macro|M13_CHIP_ID
mdefine_line|#define M13_CHIP_ID 0xD0
DECL|macro|M14_CHIP_ID
mdefine_line|#define M14_CHIP_ID 0xE0
DECL|macro|M15_CHIP_ID
mdefine_line|#define M15_CHIP_ID 0xF0
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_pnp_irq
id|REGWORD
id|v_pnp_irq
suffix:colon
l_int|4
suffix:semicolon
DECL|member|v_chip_id
id|REGWORD
id|v_chip_id
suffix:colon
l_int|4
suffix:semicolon
DECL|typedef|bit_r_chip_id
)brace
id|bit_r_chip_id
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_chip_id
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_chip_id
id|bit
suffix:semicolon
)brace
id|reg_r_chip_id
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_BERT_STA
mdefine_line|#define R_BERT_STA 0x17
DECL|macro|M_BERT_SYNC
mdefine_line|#define M_BERT_SYNC 0x10
DECL|macro|M_BERT_INV_DATA
mdefine_line|#define M_BERT_INV_DATA 0x20
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|reserved_39v_bert_sync_src
id|REGWORD
id|reserved_39v_bert_sync_src
suffix:colon
l_int|4
suffix:semicolon
DECL|member|v_bert_sync
id|REGWORD
id|v_bert_sync
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_bert_inv_data
id|REGWORD
id|v_bert_inv_data
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_40
id|REGWORD
id|reserved_40
suffix:colon
l_int|2
suffix:semicolon
DECL|typedef|bit_r_bert_sta
)brace
id|bit_r_bert_sta
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_bert_sta
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_bert_sta
id|bit
suffix:semicolon
)brace
id|reg_r_bert_sta
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_F0_CNTL
mdefine_line|#define R_F0_CNTL 0x18
DECL|macro|M_F0_CNTL
mdefine_line|#define M_F0_CNTL 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_f0_cntl
id|REGWORD
id|v_f0_cntl
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_r_f0_cntl
)brace
id|bit_r_f0_cntl
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_f0_cntl
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_f0_cntl
id|bit
suffix:semicolon
)brace
id|reg_r_f0_cntl
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_F0_CNTH
mdefine_line|#define R_F0_CNTH 0x19
DECL|macro|M_F0_CNTH
mdefine_line|#define M_F0_CNTH 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_f0_cnth
id|REGWORD
id|v_f0_cnth
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_r_f0_cnth
)brace
id|bit_r_f0_cnth
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_f0_cnth
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_f0_cnth
id|bit
suffix:semicolon
)brace
id|reg_r_f0_cnth
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_BERT_ECL
mdefine_line|#define R_BERT_ECL 0x1A
DECL|macro|M_BERT_ECL
mdefine_line|#define M_BERT_ECL 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_bert_ecl
id|REGWORD
id|v_bert_ecl
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_r_bert_ecl
)brace
id|bit_r_bert_ecl
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_bert_ecl
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_bert_ecl
id|bit
suffix:semicolon
)brace
id|reg_r_bert_ecl
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_BERT_ECH
mdefine_line|#define R_BERT_ECH 0x1B
DECL|macro|M_BERT_ECH
mdefine_line|#define M_BERT_ECH 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_bert_ech
id|REGWORD
id|v_bert_ech
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_r_bert_ech
)brace
id|bit_r_bert_ech
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_bert_ech
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_bert_ech
id|bit
suffix:semicolon
)brace
id|reg_r_bert_ech
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_STATUS
mdefine_line|#define R_STATUS 0x1C
DECL|macro|M_BUSY
mdefine_line|#define M_BUSY 0x01
DECL|macro|M_PROC
mdefine_line|#define M_PROC 0x02
DECL|macro|M_DTMF_IRQSTA
mdefine_line|#define M_DTMF_IRQSTA 0x04
DECL|macro|M_LOST_STA
mdefine_line|#define M_LOST_STA 0x08
DECL|macro|M_SYNC_IN
mdefine_line|#define M_SYNC_IN 0x10
DECL|macro|M_EXT_IRQSTA
mdefine_line|#define M_EXT_IRQSTA 0x20
DECL|macro|M_MISC_IRQSTA
mdefine_line|#define M_MISC_IRQSTA 0x40
DECL|macro|M_FR_IRQSTA
mdefine_line|#define M_FR_IRQSTA 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_busy
id|REGWORD
id|v_busy
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_proc
id|REGWORD
id|v_proc
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_dtmf_irqsta
id|REGWORD
id|v_dtmf_irqsta
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_lost_sta
id|REGWORD
id|v_lost_sta
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_sync_in
id|REGWORD
id|v_sync_in
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_ext_irqsta
id|REGWORD
id|v_ext_irqsta
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_misc_irqsta
id|REGWORD
id|v_misc_irqsta
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_fr_irqsta
id|REGWORD
id|v_fr_irqsta
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_status
)brace
id|bit_r_status
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_status
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_status
id|bit
suffix:semicolon
)brace
id|reg_r_status
suffix:semicolon
singleline_comment|// register and bitmap access
DECL|macro|R_SLOT
mdefine_line|#define R_SLOT 0x10
DECL|macro|M_SL_DIR
mdefine_line|#define M_SL_DIR 0x01
DECL|macro|M_SL_NUM
mdefine_line|#define M_SL_NUM 0xFE
DECL|macro|M1_SL_NUM
mdefine_line|#define M1_SL_NUM 0x02
DECL|macro|M2_SL_NUM
mdefine_line|#define M2_SL_NUM 0x04
DECL|macro|M3_SL_NUM
mdefine_line|#define M3_SL_NUM 0x06
DECL|macro|M4_SL_NUM
mdefine_line|#define M4_SL_NUM 0x08
DECL|macro|M5_SL_NUM
mdefine_line|#define M5_SL_NUM 0x0A
DECL|macro|M6_SL_NUM
mdefine_line|#define M6_SL_NUM 0x0C
DECL|macro|M7_SL_NUM
mdefine_line|#define M7_SL_NUM 0x0E
DECL|macro|M8_SL_NUM
mdefine_line|#define M8_SL_NUM 0x10
DECL|macro|M9_SL_NUM
mdefine_line|#define M9_SL_NUM 0x12
DECL|macro|M10_SL_NUM
mdefine_line|#define M10_SL_NUM 0x14
DECL|macro|M11_SL_NUM
mdefine_line|#define M11_SL_NUM 0x16
DECL|macro|M12_SL_NUM
mdefine_line|#define M12_SL_NUM 0x18
DECL|macro|M13_SL_NUM
mdefine_line|#define M13_SL_NUM 0x1A
DECL|macro|M14_SL_NUM
mdefine_line|#define M14_SL_NUM 0x1C
DECL|macro|M15_SL_NUM
mdefine_line|#define M15_SL_NUM 0x1E
DECL|macro|M16_SL_NUM
mdefine_line|#define M16_SL_NUM 0x20
DECL|macro|M17_SL_NUM
mdefine_line|#define M17_SL_NUM 0x22
DECL|macro|M18_SL_NUM
mdefine_line|#define M18_SL_NUM 0x24
DECL|macro|M19_SL_NUM
mdefine_line|#define M19_SL_NUM 0x26
DECL|macro|M20_SL_NUM
mdefine_line|#define M20_SL_NUM 0x28
DECL|macro|M21_SL_NUM
mdefine_line|#define M21_SL_NUM 0x2A
DECL|macro|M22_SL_NUM
mdefine_line|#define M22_SL_NUM 0x2C
DECL|macro|M23_SL_NUM
mdefine_line|#define M23_SL_NUM 0x2E
DECL|macro|M24_SL_NUM
mdefine_line|#define M24_SL_NUM 0x30
DECL|macro|M25_SL_NUM
mdefine_line|#define M25_SL_NUM 0x32
DECL|macro|M26_SL_NUM
mdefine_line|#define M26_SL_NUM 0x34
DECL|macro|M27_SL_NUM
mdefine_line|#define M27_SL_NUM 0x36
DECL|macro|M28_SL_NUM
mdefine_line|#define M28_SL_NUM 0x38
DECL|macro|M29_SL_NUM
mdefine_line|#define M29_SL_NUM 0x3A
DECL|macro|M30_SL_NUM
mdefine_line|#define M30_SL_NUM 0x3C
DECL|macro|M31_SL_NUM
mdefine_line|#define M31_SL_NUM 0x3E
DECL|macro|M32_SL_NUM
mdefine_line|#define M32_SL_NUM 0x40
DECL|macro|M33_SL_NUM
mdefine_line|#define M33_SL_NUM 0x42
DECL|macro|M34_SL_NUM
mdefine_line|#define M34_SL_NUM 0x44
DECL|macro|M35_SL_NUM
mdefine_line|#define M35_SL_NUM 0x46
DECL|macro|M36_SL_NUM
mdefine_line|#define M36_SL_NUM 0x48
DECL|macro|M37_SL_NUM
mdefine_line|#define M37_SL_NUM 0x4A
DECL|macro|M38_SL_NUM
mdefine_line|#define M38_SL_NUM 0x4C
DECL|macro|M39_SL_NUM
mdefine_line|#define M39_SL_NUM 0x4E
DECL|macro|M40_SL_NUM
mdefine_line|#define M40_SL_NUM 0x50
DECL|macro|M41_SL_NUM
mdefine_line|#define M41_SL_NUM 0x52
DECL|macro|M42_SL_NUM
mdefine_line|#define M42_SL_NUM 0x54
DECL|macro|M43_SL_NUM
mdefine_line|#define M43_SL_NUM 0x56
DECL|macro|M44_SL_NUM
mdefine_line|#define M44_SL_NUM 0x58
DECL|macro|M45_SL_NUM
mdefine_line|#define M45_SL_NUM 0x5A
DECL|macro|M46_SL_NUM
mdefine_line|#define M46_SL_NUM 0x5C
DECL|macro|M47_SL_NUM
mdefine_line|#define M47_SL_NUM 0x5E
DECL|macro|M48_SL_NUM
mdefine_line|#define M48_SL_NUM 0x60
DECL|macro|M49_SL_NUM
mdefine_line|#define M49_SL_NUM 0x62
DECL|macro|M50_SL_NUM
mdefine_line|#define M50_SL_NUM 0x64
DECL|macro|M51_SL_NUM
mdefine_line|#define M51_SL_NUM 0x66
DECL|macro|M52_SL_NUM
mdefine_line|#define M52_SL_NUM 0x68
DECL|macro|M53_SL_NUM
mdefine_line|#define M53_SL_NUM 0x6A
DECL|macro|M54_SL_NUM
mdefine_line|#define M54_SL_NUM 0x6C
DECL|macro|M55_SL_NUM
mdefine_line|#define M55_SL_NUM 0x6E
DECL|macro|M56_SL_NUM
mdefine_line|#define M56_SL_NUM 0x70
DECL|macro|M57_SL_NUM
mdefine_line|#define M57_SL_NUM 0x72
DECL|macro|M58_SL_NUM
mdefine_line|#define M58_SL_NUM 0x74
DECL|macro|M59_SL_NUM
mdefine_line|#define M59_SL_NUM 0x76
DECL|macro|M60_SL_NUM
mdefine_line|#define M60_SL_NUM 0x78
DECL|macro|M61_SL_NUM
mdefine_line|#define M61_SL_NUM 0x7A
DECL|macro|M62_SL_NUM
mdefine_line|#define M62_SL_NUM 0x7C
DECL|macro|M63_SL_NUM
mdefine_line|#define M63_SL_NUM 0x7E
DECL|macro|M64_SL_NUM
mdefine_line|#define M64_SL_NUM 0x80
DECL|macro|M65_SL_NUM
mdefine_line|#define M65_SL_NUM 0x82
DECL|macro|M66_SL_NUM
mdefine_line|#define M66_SL_NUM 0x84
DECL|macro|M67_SL_NUM
mdefine_line|#define M67_SL_NUM 0x86
DECL|macro|M68_SL_NUM
mdefine_line|#define M68_SL_NUM 0x88
DECL|macro|M69_SL_NUM
mdefine_line|#define M69_SL_NUM 0x8A
DECL|macro|M70_SL_NUM
mdefine_line|#define M70_SL_NUM 0x8C
DECL|macro|M71_SL_NUM
mdefine_line|#define M71_SL_NUM 0x8E
DECL|macro|M72_SL_NUM
mdefine_line|#define M72_SL_NUM 0x90
DECL|macro|M73_SL_NUM
mdefine_line|#define M73_SL_NUM 0x92
DECL|macro|M74_SL_NUM
mdefine_line|#define M74_SL_NUM 0x94
DECL|macro|M75_SL_NUM
mdefine_line|#define M75_SL_NUM 0x96
DECL|macro|M76_SL_NUM
mdefine_line|#define M76_SL_NUM 0x98
DECL|macro|M77_SL_NUM
mdefine_line|#define M77_SL_NUM 0x9A
DECL|macro|M78_SL_NUM
mdefine_line|#define M78_SL_NUM 0x9C
DECL|macro|M79_SL_NUM
mdefine_line|#define M79_SL_NUM 0x9E
DECL|macro|M80_SL_NUM
mdefine_line|#define M80_SL_NUM 0xA0
DECL|macro|M81_SL_NUM
mdefine_line|#define M81_SL_NUM 0xA2
DECL|macro|M82_SL_NUM
mdefine_line|#define M82_SL_NUM 0xA4
DECL|macro|M83_SL_NUM
mdefine_line|#define M83_SL_NUM 0xA6
DECL|macro|M84_SL_NUM
mdefine_line|#define M84_SL_NUM 0xA8
DECL|macro|M85_SL_NUM
mdefine_line|#define M85_SL_NUM 0xAA
DECL|macro|M86_SL_NUM
mdefine_line|#define M86_SL_NUM 0xAC
DECL|macro|M87_SL_NUM
mdefine_line|#define M87_SL_NUM 0xAE
DECL|macro|M88_SL_NUM
mdefine_line|#define M88_SL_NUM 0xB0
DECL|macro|M89_SL_NUM
mdefine_line|#define M89_SL_NUM 0xB2
DECL|macro|M90_SL_NUM
mdefine_line|#define M90_SL_NUM 0xB4
DECL|macro|M91_SL_NUM
mdefine_line|#define M91_SL_NUM 0xB6
DECL|macro|M92_SL_NUM
mdefine_line|#define M92_SL_NUM 0xB8
DECL|macro|M93_SL_NUM
mdefine_line|#define M93_SL_NUM 0xBA
DECL|macro|M94_SL_NUM
mdefine_line|#define M94_SL_NUM 0xBC
DECL|macro|M95_SL_NUM
mdefine_line|#define M95_SL_NUM 0xBE
DECL|macro|M96_SL_NUM
mdefine_line|#define M96_SL_NUM 0xC0
DECL|macro|M97_SL_NUM
mdefine_line|#define M97_SL_NUM 0xC2
DECL|macro|M98_SL_NUM
mdefine_line|#define M98_SL_NUM 0xC4
DECL|macro|M99_SL_NUM
mdefine_line|#define M99_SL_NUM 0xC6
DECL|macro|M100_SL_NUM
mdefine_line|#define M100_SL_NUM 0xC8
DECL|macro|M101_SL_NUM
mdefine_line|#define M101_SL_NUM 0xCA
DECL|macro|M102_SL_NUM
mdefine_line|#define M102_SL_NUM 0xCC
DECL|macro|M103_SL_NUM
mdefine_line|#define M103_SL_NUM 0xCE
DECL|macro|M104_SL_NUM
mdefine_line|#define M104_SL_NUM 0xD0
DECL|macro|M105_SL_NUM
mdefine_line|#define M105_SL_NUM 0xD2
DECL|macro|M106_SL_NUM
mdefine_line|#define M106_SL_NUM 0xD4
DECL|macro|M107_SL_NUM
mdefine_line|#define M107_SL_NUM 0xD6
DECL|macro|M108_SL_NUM
mdefine_line|#define M108_SL_NUM 0xD8
DECL|macro|M109_SL_NUM
mdefine_line|#define M109_SL_NUM 0xDA
DECL|macro|M110_SL_NUM
mdefine_line|#define M110_SL_NUM 0xDC
DECL|macro|M111_SL_NUM
mdefine_line|#define M111_SL_NUM 0xDE
DECL|macro|M112_SL_NUM
mdefine_line|#define M112_SL_NUM 0xE0
DECL|macro|M113_SL_NUM
mdefine_line|#define M113_SL_NUM 0xE2
DECL|macro|M114_SL_NUM
mdefine_line|#define M114_SL_NUM 0xE4
DECL|macro|M115_SL_NUM
mdefine_line|#define M115_SL_NUM 0xE6
DECL|macro|M116_SL_NUM
mdefine_line|#define M116_SL_NUM 0xE8
DECL|macro|M117_SL_NUM
mdefine_line|#define M117_SL_NUM 0xEA
DECL|macro|M118_SL_NUM
mdefine_line|#define M118_SL_NUM 0xEC
DECL|macro|M119_SL_NUM
mdefine_line|#define M119_SL_NUM 0xEE
DECL|macro|M120_SL_NUM
mdefine_line|#define M120_SL_NUM 0xF0
DECL|macro|M121_SL_NUM
mdefine_line|#define M121_SL_NUM 0xF2
DECL|macro|M122_SL_NUM
mdefine_line|#define M122_SL_NUM 0xF4
DECL|macro|M123_SL_NUM
mdefine_line|#define M123_SL_NUM 0xF6
DECL|macro|M124_SL_NUM
mdefine_line|#define M124_SL_NUM 0xF8
DECL|macro|M125_SL_NUM
mdefine_line|#define M125_SL_NUM 0xFA
DECL|macro|M126_SL_NUM
mdefine_line|#define M126_SL_NUM 0xFC
DECL|macro|M127_SL_NUM
mdefine_line|#define M127_SL_NUM 0xFE
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_sl_dir
id|REGWORD
id|v_sl_dir
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_sl_num
id|REGWORD
id|v_sl_num
suffix:colon
l_int|7
suffix:semicolon
DECL|typedef|bit_r_slot
)brace
id|bit_r_slot
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_slot
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_slot
id|bit
suffix:semicolon
)brace
id|reg_r_slot
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_IRQMSK_MISC
mdefine_line|#define R_IRQMSK_MISC 0x11
DECL|macro|M_TI_IRQMSK
mdefine_line|#define M_TI_IRQMSK 0x02
DECL|macro|M_PROC_IRQMSK
mdefine_line|#define M_PROC_IRQMSK 0x04
DECL|macro|M_DTMF_IRQMSK
mdefine_line|#define M_DTMF_IRQMSK 0x08
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|reserved_42
id|REGWORD
id|reserved_42
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_ti_irqmsk
id|REGWORD
id|v_ti_irqmsk
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_proc_irqmsk
id|REGWORD
id|v_proc_irqmsk
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_dtmf_irqmsk
id|REGWORD
id|v_dtmf_irqmsk
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_44
id|REGWORD
id|reserved_44
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_46
id|REGWORD
id|reserved_46
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_48
id|REGWORD
id|reserved_48
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_50
id|REGWORD
id|reserved_50
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_irqmsk_misc
)brace
id|bit_r_irqmsk_misc
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_irqmsk_misc
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_irqmsk_misc
id|bit
suffix:semicolon
)brace
id|reg_r_irqmsk_misc
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_IRQ_CTRL
mdefine_line|#define R_IRQ_CTRL 0x13
DECL|macro|M_FIFO_IRQ
mdefine_line|#define M_FIFO_IRQ 0x01
DECL|macro|M_GLOB_IRQ_EN
mdefine_line|#define M_GLOB_IRQ_EN 0x08
DECL|macro|M_IRQ_POL
mdefine_line|#define M_IRQ_POL 0x10
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_fifo_irq
id|REGWORD
id|v_fifo_irq
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_51
id|REGWORD
id|reserved_51
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_glob_irq_en
id|REGWORD
id|v_glob_irq_en
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_pol
id|REGWORD
id|v_irq_pol
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_52
id|REGWORD
id|reserved_52
suffix:colon
l_int|3
suffix:semicolon
DECL|typedef|bit_r_irq_ctrl
)brace
id|bit_r_irq_ctrl
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_irq_ctrl
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_irq_ctrl
id|bit
suffix:semicolon
)brace
id|reg_r_irq_ctrl
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_PCM_MD0
mdefine_line|#define R_PCM_MD0 0x14
DECL|macro|M_PCM_MD
mdefine_line|#define M_PCM_MD 0x01
DECL|macro|M_C4_POL
mdefine_line|#define M_C4_POL 0x02
DECL|macro|M_F0_NEG
mdefine_line|#define M_F0_NEG 0x04
DECL|macro|M_F0_LEN
mdefine_line|#define M_F0_LEN 0x08
DECL|macro|M_PCM_ADDR
mdefine_line|#define M_PCM_ADDR 0xF0
DECL|macro|M1_PCM_ADDR
mdefine_line|#define M1_PCM_ADDR 0x10
DECL|macro|M2_PCM_ADDR
mdefine_line|#define M2_PCM_ADDR 0x20
DECL|macro|M3_PCM_ADDR
mdefine_line|#define M3_PCM_ADDR 0x30
DECL|macro|M4_PCM_ADDR
mdefine_line|#define M4_PCM_ADDR 0x40
DECL|macro|M5_PCM_ADDR
mdefine_line|#define M5_PCM_ADDR 0x50
DECL|macro|M6_PCM_ADDR
mdefine_line|#define M6_PCM_ADDR 0x60
DECL|macro|M7_PCM_ADDR
mdefine_line|#define M7_PCM_ADDR 0x70
DECL|macro|M8_PCM_ADDR
mdefine_line|#define M8_PCM_ADDR 0x80
DECL|macro|M9_PCM_ADDR
mdefine_line|#define M9_PCM_ADDR 0x90
DECL|macro|M10_PCM_ADDR
mdefine_line|#define M10_PCM_ADDR 0xA0
DECL|macro|M11_PCM_ADDR
mdefine_line|#define M11_PCM_ADDR 0xB0
DECL|macro|M12_PCM_ADDR
mdefine_line|#define M12_PCM_ADDR 0xC0
DECL|macro|M13_PCM_ADDR
mdefine_line|#define M13_PCM_ADDR 0xD0
DECL|macro|M14_PCM_ADDR
mdefine_line|#define M14_PCM_ADDR 0xE0
DECL|macro|M15_PCM_ADDR
mdefine_line|#define M15_PCM_ADDR 0xF0
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_pcm_md
id|REGWORD
id|v_pcm_md
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_c4_pol
id|REGWORD
id|v_c4_pol
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_f0_neg
id|REGWORD
id|v_f0_neg
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_f0_len
id|REGWORD
id|v_f0_len
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_pcm_addr
id|REGWORD
id|v_pcm_addr
suffix:colon
l_int|4
suffix:semicolon
DECL|typedef|bit_r_pcm_md0
)brace
id|bit_r_pcm_md0
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_pcm_md0
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_pcm_md0
id|bit
suffix:semicolon
)brace
id|reg_r_pcm_md0
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_CONF_EN
mdefine_line|#define R_CONF_EN 0x18
DECL|macro|M_CONF_EN
mdefine_line|#define M_CONF_EN 0x01
DECL|macro|M_ULAW
mdefine_line|#define M_ULAW 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_conf_en
id|REGWORD
id|v_conf_en
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_53
id|REGWORD
id|reserved_53
suffix:colon
l_int|6
suffix:semicolon
DECL|member|v_ulaw
id|REGWORD
id|v_ulaw
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_conf_en
)brace
id|bit_r_conf_en
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_conf_en
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_conf_en
id|bit
suffix:semicolon
)brace
id|reg_r_conf_en
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_TI_WD
mdefine_line|#define R_TI_WD 0x1A
DECL|macro|M_EV_TS
mdefine_line|#define M_EV_TS 0x0F
DECL|macro|M1_EV_TS
mdefine_line|#define M1_EV_TS 0x01
DECL|macro|M2_EV_TS
mdefine_line|#define M2_EV_TS 0x02
DECL|macro|M3_EV_TS
mdefine_line|#define M3_EV_TS 0x03
DECL|macro|M4_EV_TS
mdefine_line|#define M4_EV_TS 0x04
DECL|macro|M5_EV_TS
mdefine_line|#define M5_EV_TS 0x05
DECL|macro|M6_EV_TS
mdefine_line|#define M6_EV_TS 0x06
DECL|macro|M7_EV_TS
mdefine_line|#define M7_EV_TS 0x07
DECL|macro|M8_EV_TS
mdefine_line|#define M8_EV_TS 0x08
DECL|macro|M9_EV_TS
mdefine_line|#define M9_EV_TS 0x09
DECL|macro|M10_EV_TS
mdefine_line|#define M10_EV_TS 0x0A
DECL|macro|M11_EV_TS
mdefine_line|#define M11_EV_TS 0x0B
DECL|macro|M12_EV_TS
mdefine_line|#define M12_EV_TS 0x0C
DECL|macro|M13_EV_TS
mdefine_line|#define M13_EV_TS 0x0D
DECL|macro|M14_EV_TS
mdefine_line|#define M14_EV_TS 0x0E
DECL|macro|M15_EV_TS
mdefine_line|#define M15_EV_TS 0x0F
DECL|macro|M_WD_TS
mdefine_line|#define M_WD_TS 0xF0
DECL|macro|M1_WD_TS
mdefine_line|#define M1_WD_TS 0x10
DECL|macro|M2_WD_TS
mdefine_line|#define M2_WD_TS 0x20
DECL|macro|M3_WD_TS
mdefine_line|#define M3_WD_TS 0x30
DECL|macro|M4_WD_TS
mdefine_line|#define M4_WD_TS 0x40
DECL|macro|M5_WD_TS
mdefine_line|#define M5_WD_TS 0x50
DECL|macro|M6_WD_TS
mdefine_line|#define M6_WD_TS 0x60
DECL|macro|M7_WD_TS
mdefine_line|#define M7_WD_TS 0x70
DECL|macro|M8_WD_TS
mdefine_line|#define M8_WD_TS 0x80
DECL|macro|M9_WD_TS
mdefine_line|#define M9_WD_TS 0x90
DECL|macro|M10_WD_TS
mdefine_line|#define M10_WD_TS 0xA0
DECL|macro|M11_WD_TS
mdefine_line|#define M11_WD_TS 0xB0
DECL|macro|M12_WD_TS
mdefine_line|#define M12_WD_TS 0xC0
DECL|macro|M13_WD_TS
mdefine_line|#define M13_WD_TS 0xD0
DECL|macro|M14_WD_TS
mdefine_line|#define M14_WD_TS 0xE0
DECL|macro|M15_WD_TS
mdefine_line|#define M15_WD_TS 0xF0
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_ev_ts
id|REGWORD
id|v_ev_ts
suffix:colon
l_int|4
suffix:semicolon
DECL|member|v_wd_ts
id|REGWORD
id|v_wd_ts
suffix:colon
l_int|4
suffix:semicolon
DECL|typedef|bit_r_ti_wd
)brace
id|bit_r_ti_wd
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_ti_wd
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_ti_wd
id|bit
suffix:semicolon
)brace
id|reg_r_ti_wd
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_BERT_WD_MD
mdefine_line|#define R_BERT_WD_MD 0x1B
DECL|macro|M_PAT_SEQ
mdefine_line|#define M_PAT_SEQ 0x07
DECL|macro|M1_PAT_SEQ
mdefine_line|#define M1_PAT_SEQ 0x01
DECL|macro|M2_PAT_SEQ
mdefine_line|#define M2_PAT_SEQ 0x02
DECL|macro|M3_PAT_SEQ
mdefine_line|#define M3_PAT_SEQ 0x03
DECL|macro|M4_PAT_SEQ
mdefine_line|#define M4_PAT_SEQ 0x04
DECL|macro|M5_PAT_SEQ
mdefine_line|#define M5_PAT_SEQ 0x05
DECL|macro|M6_PAT_SEQ
mdefine_line|#define M6_PAT_SEQ 0x06
DECL|macro|M7_PAT_SEQ
mdefine_line|#define M7_PAT_SEQ 0x07
DECL|macro|M_BERT_ERR
mdefine_line|#define M_BERT_ERR 0x08
DECL|macro|M_AUTO_WD_RES
mdefine_line|#define M_AUTO_WD_RES 0x20
DECL|macro|M_WD_RES
mdefine_line|#define M_WD_RES 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_pat_seq
id|REGWORD
id|v_pat_seq
suffix:colon
l_int|3
suffix:semicolon
DECL|member|v_bert_err
id|REGWORD
id|v_bert_err
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_54
id|REGWORD
id|reserved_54
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_auto_wd_res
id|REGWORD
id|v_auto_wd_res
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_55
id|REGWORD
id|reserved_55
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_wd_res
id|REGWORD
id|v_wd_res
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_bert_wd_md
)brace
id|bit_r_bert_wd_md
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_bert_wd_md
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_bert_wd_md
id|bit
suffix:semicolon
)brace
id|reg_r_bert_wd_md
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_DTMF0
mdefine_line|#define R_DTMF0 0x1C
DECL|macro|M_DTMF_EN
mdefine_line|#define M_DTMF_EN 0x01
DECL|macro|M_HARM_SEL
mdefine_line|#define M_HARM_SEL 0x02
DECL|macro|M_DTMF_RX_CH
mdefine_line|#define M_DTMF_RX_CH 0x04
DECL|macro|M_DTMF_STOP
mdefine_line|#define M_DTMF_STOP 0x08
DECL|macro|M_CHBL_SEL
mdefine_line|#define M_CHBL_SEL 0x10
DECL|macro|M_RESTART_DTMF
mdefine_line|#define M_RESTART_DTMF 0x40
DECL|macro|M_ULAW_SEL
mdefine_line|#define M_ULAW_SEL 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_dtmf_en
id|REGWORD
id|v_dtmf_en
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_harm_sel
id|REGWORD
id|v_harm_sel
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_dtmf_rx_ch
id|REGWORD
id|v_dtmf_rx_ch
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_dtmf_stop
id|REGWORD
id|v_dtmf_stop
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_chbl_sel
id|REGWORD
id|v_chbl_sel
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_56
id|REGWORD
id|reserved_56
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_restart_dtmf
id|REGWORD
id|v_restart_dtmf
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_ulaw_sel
id|REGWORD
id|v_ulaw_sel
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_dtmf0
)brace
id|bit_r_dtmf0
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_dtmf0
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_dtmf0
id|bit
suffix:semicolon
)brace
id|reg_r_dtmf0
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_DTMF1
mdefine_line|#define R_DTMF1 0x1D
DECL|macro|M_DTMF1
mdefine_line|#define M_DTMF1 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_dtmf1
id|REGWORD
id|v_dtmf1
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_r_dtmf1
)brace
id|bit_r_dtmf1
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_dtmf1
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_dtmf1
id|bit
suffix:semicolon
)brace
id|reg_r_dtmf1
suffix:semicolon
singleline_comment|// register and bitmap access
DECL|macro|R_PWM0
mdefine_line|#define R_PWM0 0x38
DECL|macro|M_PWM0
mdefine_line|#define M_PWM0 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_pwm0
id|REGWORD
id|v_pwm0
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_r_pwm0
)brace
id|bit_r_pwm0
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_pwm0
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_pwm0
id|bit
suffix:semicolon
)brace
id|reg_r_pwm0
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_PWM1
mdefine_line|#define R_PWM1 0x39
DECL|macro|M_PWM1
mdefine_line|#define M_PWM1 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_pwm1
id|REGWORD
id|v_pwm1
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_r_pwm1
)brace
id|bit_r_pwm1
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_pwm1
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_pwm1
id|bit
suffix:semicolon
)brace
id|reg_r_pwm1
suffix:semicolon
singleline_comment|// register and bitmap access
DECL|macro|R_GPIO_IN0
mdefine_line|#define R_GPIO_IN0 0x40
DECL|macro|M_GPIO_IN0
mdefine_line|#define M_GPIO_IN0 0x01
DECL|macro|M_GPIO_IN1
mdefine_line|#define M_GPIO_IN1 0x02
DECL|macro|M_GPIO_IN2
mdefine_line|#define M_GPIO_IN2 0x04
DECL|macro|M_GPIO_IN3
mdefine_line|#define M_GPIO_IN3 0x08
DECL|macro|M_GPIO_IN4
mdefine_line|#define M_GPIO_IN4 0x10
DECL|macro|M_GPIO_IN5
mdefine_line|#define M_GPIO_IN5 0x20
DECL|macro|M_GPIO_IN6
mdefine_line|#define M_GPIO_IN6 0x40
DECL|macro|M_GPIO_IN7
mdefine_line|#define M_GPIO_IN7 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_gpio_in0
id|REGWORD
id|v_gpio_in0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_in1
id|REGWORD
id|v_gpio_in1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_in2
id|REGWORD
id|v_gpio_in2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_in3
id|REGWORD
id|v_gpio_in3
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_in4
id|REGWORD
id|v_gpio_in4
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_in5
id|REGWORD
id|v_gpio_in5
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_in6
id|REGWORD
id|v_gpio_in6
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_in7
id|REGWORD
id|v_gpio_in7
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_gpio_in0
)brace
id|bit_r_gpio_in0
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_gpio_in0
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_gpio_in0
id|bit
suffix:semicolon
)brace
id|reg_r_gpio_in0
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_GPIO_IN1
mdefine_line|#define R_GPIO_IN1 0x41
DECL|macro|M_GPIO_IN8
mdefine_line|#define M_GPIO_IN8 0x01
DECL|macro|M_GPIO_IN9
mdefine_line|#define M_GPIO_IN9 0x02
DECL|macro|M_GPIO_IN10
mdefine_line|#define M_GPIO_IN10 0x04
DECL|macro|M_GPIO_IN11
mdefine_line|#define M_GPIO_IN11 0x08
DECL|macro|M_GPIO_IN12
mdefine_line|#define M_GPIO_IN12 0x10
DECL|macro|M_GPIO_IN13
mdefine_line|#define M_GPIO_IN13 0x20
DECL|macro|M_GPIO_IN14
mdefine_line|#define M_GPIO_IN14 0x40
DECL|macro|M_GPIO_IN15
mdefine_line|#define M_GPIO_IN15 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_gpio_in8
id|REGWORD
id|v_gpio_in8
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_in9
id|REGWORD
id|v_gpio_in9
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_in10
id|REGWORD
id|v_gpio_in10
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_in11
id|REGWORD
id|v_gpio_in11
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_in12
id|REGWORD
id|v_gpio_in12
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_in13
id|REGWORD
id|v_gpio_in13
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_in14
id|REGWORD
id|v_gpio_in14
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_in15
id|REGWORD
id|v_gpio_in15
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_gpio_in1
)brace
id|bit_r_gpio_in1
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_gpio_in1
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_gpio_in1
id|bit
suffix:semicolon
)brace
id|reg_r_gpio_in1
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_GPI_IN0
mdefine_line|#define R_GPI_IN0 0x44
DECL|macro|M_GPI_IN0
mdefine_line|#define M_GPI_IN0 0x01
DECL|macro|M_GPI_IN1
mdefine_line|#define M_GPI_IN1 0x02
DECL|macro|M_GPI_IN2
mdefine_line|#define M_GPI_IN2 0x04
DECL|macro|M_GPI_IN3
mdefine_line|#define M_GPI_IN3 0x08
DECL|macro|M_GPI_IN4
mdefine_line|#define M_GPI_IN4 0x10
DECL|macro|M_GPI_IN5
mdefine_line|#define M_GPI_IN5 0x20
DECL|macro|M_GPI_IN6
mdefine_line|#define M_GPI_IN6 0x40
DECL|macro|M_GPI_IN7
mdefine_line|#define M_GPI_IN7 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_gpi_in0
id|REGWORD
id|v_gpi_in0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in1
id|REGWORD
id|v_gpi_in1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in2
id|REGWORD
id|v_gpi_in2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in3
id|REGWORD
id|v_gpi_in3
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in4
id|REGWORD
id|v_gpi_in4
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in5
id|REGWORD
id|v_gpi_in5
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in6
id|REGWORD
id|v_gpi_in6
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in7
id|REGWORD
id|v_gpi_in7
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_gpi_in0
)brace
id|bit_r_gpi_in0
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_gpi_in0
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_gpi_in0
id|bit
suffix:semicolon
)brace
id|reg_r_gpi_in0
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_GPI_IN1
mdefine_line|#define R_GPI_IN1 0x45
DECL|macro|M_GPI_IN8
mdefine_line|#define M_GPI_IN8 0x01
DECL|macro|M_GPI_IN9
mdefine_line|#define M_GPI_IN9 0x02
DECL|macro|M_GPI_IN10
mdefine_line|#define M_GPI_IN10 0x04
DECL|macro|M_GPI_IN11
mdefine_line|#define M_GPI_IN11 0x08
DECL|macro|M_GPI_IN12
mdefine_line|#define M_GPI_IN12 0x10
DECL|macro|M_GPI_IN13
mdefine_line|#define M_GPI_IN13 0x20
DECL|macro|M_GPI_IN14
mdefine_line|#define M_GPI_IN14 0x40
DECL|macro|M_GPI_IN15
mdefine_line|#define M_GPI_IN15 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_gpi_in8
id|REGWORD
id|v_gpi_in8
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in9
id|REGWORD
id|v_gpi_in9
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in10
id|REGWORD
id|v_gpi_in10
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in11
id|REGWORD
id|v_gpi_in11
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in12
id|REGWORD
id|v_gpi_in12
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in13
id|REGWORD
id|v_gpi_in13
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in14
id|REGWORD
id|v_gpi_in14
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in15
id|REGWORD
id|v_gpi_in15
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_gpi_in1
)brace
id|bit_r_gpi_in1
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_gpi_in1
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_gpi_in1
id|bit
suffix:semicolon
)brace
id|reg_r_gpi_in1
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_GPI_IN2
mdefine_line|#define R_GPI_IN2 0x46
DECL|macro|M_GPI_IN16
mdefine_line|#define M_GPI_IN16 0x01
DECL|macro|M_GPI_IN17
mdefine_line|#define M_GPI_IN17 0x02
DECL|macro|M_GPI_IN18
mdefine_line|#define M_GPI_IN18 0x04
DECL|macro|M_GPI_IN19
mdefine_line|#define M_GPI_IN19 0x08
DECL|macro|M_GPI_IN20
mdefine_line|#define M_GPI_IN20 0x10
DECL|macro|M_GPI_IN21
mdefine_line|#define M_GPI_IN21 0x20
DECL|macro|M_GPI_IN22
mdefine_line|#define M_GPI_IN22 0x40
DECL|macro|M_GPI_IN23
mdefine_line|#define M_GPI_IN23 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_gpi_in16
id|REGWORD
id|v_gpi_in16
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in17
id|REGWORD
id|v_gpi_in17
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in18
id|REGWORD
id|v_gpi_in18
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in19
id|REGWORD
id|v_gpi_in19
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in20
id|REGWORD
id|v_gpi_in20
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in21
id|REGWORD
id|v_gpi_in21
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in22
id|REGWORD
id|v_gpi_in22
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in23
id|REGWORD
id|v_gpi_in23
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_gpi_in2
)brace
id|bit_r_gpi_in2
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_gpi_in2
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_gpi_in2
id|bit
suffix:semicolon
)brace
id|reg_r_gpi_in2
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_GPI_IN3
mdefine_line|#define R_GPI_IN3 0x47
DECL|macro|M_GPI_IN24
mdefine_line|#define M_GPI_IN24 0x01
DECL|macro|M_GPI_IN25
mdefine_line|#define M_GPI_IN25 0x02
DECL|macro|M_GPI_IN26
mdefine_line|#define M_GPI_IN26 0x04
DECL|macro|M_GPI_IN27
mdefine_line|#define M_GPI_IN27 0x08
DECL|macro|M_GPI_IN28
mdefine_line|#define M_GPI_IN28 0x10
DECL|macro|M_GPI_IN29
mdefine_line|#define M_GPI_IN29 0x20
DECL|macro|M_GPI_IN30
mdefine_line|#define M_GPI_IN30 0x40
DECL|macro|M_GPI_IN31
mdefine_line|#define M_GPI_IN31 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_gpi_in24
id|REGWORD
id|v_gpi_in24
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in25
id|REGWORD
id|v_gpi_in25
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in26
id|REGWORD
id|v_gpi_in26
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in27
id|REGWORD
id|v_gpi_in27
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in28
id|REGWORD
id|v_gpi_in28
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in29
id|REGWORD
id|v_gpi_in29
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in30
id|REGWORD
id|v_gpi_in30
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpi_in31
id|REGWORD
id|v_gpi_in31
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_gpi_in3
)brace
id|bit_r_gpi_in3
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_gpi_in3
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_gpi_in3
id|bit
suffix:semicolon
)brace
id|reg_r_gpi_in3
suffix:semicolon
singleline_comment|// register and bitmap access
DECL|macro|R_GPIO_OUT0
mdefine_line|#define R_GPIO_OUT0 0x40
DECL|macro|M_GPIO_OUT0
mdefine_line|#define M_GPIO_OUT0 0x01
DECL|macro|M_GPIO_OUT1
mdefine_line|#define M_GPIO_OUT1 0x02
DECL|macro|M_GPIO_OUT2
mdefine_line|#define M_GPIO_OUT2 0x04
DECL|macro|M_GPIO_OUT3
mdefine_line|#define M_GPIO_OUT3 0x08
DECL|macro|M_GPIO_OUT4
mdefine_line|#define M_GPIO_OUT4 0x10
DECL|macro|M_GPIO_OUT5
mdefine_line|#define M_GPIO_OUT5 0x20
DECL|macro|M_GPIO_OUT6
mdefine_line|#define M_GPIO_OUT6 0x40
DECL|macro|M_GPIO_OUT7
mdefine_line|#define M_GPIO_OUT7 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_gpio_out0
id|REGWORD
id|v_gpio_out0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_out1
id|REGWORD
id|v_gpio_out1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_out2
id|REGWORD
id|v_gpio_out2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_out3
id|REGWORD
id|v_gpio_out3
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_out4
id|REGWORD
id|v_gpio_out4
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_out5
id|REGWORD
id|v_gpio_out5
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_out6
id|REGWORD
id|v_gpio_out6
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_out7
id|REGWORD
id|v_gpio_out7
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_gpio_out0
)brace
id|bit_r_gpio_out0
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_gpio_out0
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_gpio_out0
id|bit
suffix:semicolon
)brace
id|reg_r_gpio_out0
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_GPIO_OUT1
mdefine_line|#define R_GPIO_OUT1 0x41
DECL|macro|M_GPIO_OUT8
mdefine_line|#define M_GPIO_OUT8 0x01
DECL|macro|M_GPIO_OUT9
mdefine_line|#define M_GPIO_OUT9 0x02
DECL|macro|M_GPIO_OUT10
mdefine_line|#define M_GPIO_OUT10 0x04
DECL|macro|M_GPIO_OUT11
mdefine_line|#define M_GPIO_OUT11 0x08
DECL|macro|M_GPIO_OUT12
mdefine_line|#define M_GPIO_OUT12 0x10
DECL|macro|M_GPIO_OUT13
mdefine_line|#define M_GPIO_OUT13 0x20
DECL|macro|M_GPIO_OUT14
mdefine_line|#define M_GPIO_OUT14 0x40
DECL|macro|M_GPIO_OUT15
mdefine_line|#define M_GPIO_OUT15 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_gpio_out8
id|REGWORD
id|v_gpio_out8
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_out9
id|REGWORD
id|v_gpio_out9
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_out10
id|REGWORD
id|v_gpio_out10
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_out11
id|REGWORD
id|v_gpio_out11
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_out12
id|REGWORD
id|v_gpio_out12
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_out13
id|REGWORD
id|v_gpio_out13
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_out14
id|REGWORD
id|v_gpio_out14
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_out15
id|REGWORD
id|v_gpio_out15
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_gpio_out1
)brace
id|bit_r_gpio_out1
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_gpio_out1
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_gpio_out1
id|bit
suffix:semicolon
)brace
id|reg_r_gpio_out1
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_GPIO_EN0
mdefine_line|#define R_GPIO_EN0 0x42
DECL|macro|M_GPIO_EN0
mdefine_line|#define M_GPIO_EN0 0x01
DECL|macro|M_GPIO_EN1
mdefine_line|#define M_GPIO_EN1 0x02
DECL|macro|M_GPIO_EN2
mdefine_line|#define M_GPIO_EN2 0x04
DECL|macro|M_GPIO_EN3
mdefine_line|#define M_GPIO_EN3 0x08
DECL|macro|M_GPIO_EN4
mdefine_line|#define M_GPIO_EN4 0x10
DECL|macro|M_GPIO_EN5
mdefine_line|#define M_GPIO_EN5 0x20
DECL|macro|M_GPIO_EN6
mdefine_line|#define M_GPIO_EN6 0x40
DECL|macro|M_GPIO_EN7
mdefine_line|#define M_GPIO_EN7 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_gpio_en0
id|REGWORD
id|v_gpio_en0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_en1
id|REGWORD
id|v_gpio_en1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_en2
id|REGWORD
id|v_gpio_en2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_en3
id|REGWORD
id|v_gpio_en3
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_en4
id|REGWORD
id|v_gpio_en4
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_en5
id|REGWORD
id|v_gpio_en5
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_en6
id|REGWORD
id|v_gpio_en6
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_en7
id|REGWORD
id|v_gpio_en7
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_gpio_en0
)brace
id|bit_r_gpio_en0
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_gpio_en0
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_gpio_en0
id|bit
suffix:semicolon
)brace
id|reg_r_gpio_en0
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_GPIO_EN1
mdefine_line|#define R_GPIO_EN1 0x43
DECL|macro|M_GPIO_EN8
mdefine_line|#define M_GPIO_EN8 0x01
DECL|macro|M_GPIO_EN9
mdefine_line|#define M_GPIO_EN9 0x02
DECL|macro|M_GPIO_EN10
mdefine_line|#define M_GPIO_EN10 0x04
DECL|macro|M_GPIO_EN11
mdefine_line|#define M_GPIO_EN11 0x08
DECL|macro|M_GPIO_EN12
mdefine_line|#define M_GPIO_EN12 0x10
DECL|macro|M_GPIO_EN13
mdefine_line|#define M_GPIO_EN13 0x20
DECL|macro|M_GPIO_EN14
mdefine_line|#define M_GPIO_EN14 0x40
DECL|macro|M_GPIO_EN15
mdefine_line|#define M_GPIO_EN15 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_gpio_en8
id|REGWORD
id|v_gpio_en8
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_en9
id|REGWORD
id|v_gpio_en9
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_en10
id|REGWORD
id|v_gpio_en10
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_en11
id|REGWORD
id|v_gpio_en11
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_en12
id|REGWORD
id|v_gpio_en12
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_en13
id|REGWORD
id|v_gpio_en13
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_en14
id|REGWORD
id|v_gpio_en14
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_en15
id|REGWORD
id|v_gpio_en15
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_gpio_en1
)brace
id|bit_r_gpio_en1
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_gpio_en1
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_gpio_en1
id|bit
suffix:semicolon
)brace
id|reg_r_gpio_en1
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_GPIO_SEL
mdefine_line|#define R_GPIO_SEL 0x44
DECL|macro|M_GPIO_SEL0
mdefine_line|#define M_GPIO_SEL0 0x01
DECL|macro|M_GPIO_SEL1
mdefine_line|#define M_GPIO_SEL1 0x02
DECL|macro|M_GPIO_SEL2
mdefine_line|#define M_GPIO_SEL2 0x04
DECL|macro|M_GPIO_SEL3
mdefine_line|#define M_GPIO_SEL3 0x08
DECL|macro|M_GPIO_SEL4
mdefine_line|#define M_GPIO_SEL4 0x10
DECL|macro|M_GPIO_SEL5
mdefine_line|#define M_GPIO_SEL5 0x20
DECL|macro|M_GPIO_SEL6
mdefine_line|#define M_GPIO_SEL6 0x40
DECL|macro|M_GPIO_SEL7
mdefine_line|#define M_GPIO_SEL7 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_gpio_sel0
id|REGWORD
id|v_gpio_sel0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_sel1
id|REGWORD
id|v_gpio_sel1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_sel2
id|REGWORD
id|v_gpio_sel2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_sel3
id|REGWORD
id|v_gpio_sel3
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_sel4
id|REGWORD
id|v_gpio_sel4
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_sel5
id|REGWORD
id|v_gpio_sel5
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_sel6
id|REGWORD
id|v_gpio_sel6
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_gpio_sel7
id|REGWORD
id|v_gpio_sel7
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_gpio_sel
)brace
id|bit_r_gpio_sel
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_gpio_sel
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_gpio_sel
id|bit
suffix:semicolon
)brace
id|reg_r_gpio_sel
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_BRG_CTRL
mdefine_line|#define R_BRG_CTRL 0x45
DECL|macro|M_BRG_CS
mdefine_line|#define M_BRG_CS 0x07
DECL|macro|M1_BRG_CS
mdefine_line|#define M1_BRG_CS 0x01
DECL|macro|M2_BRG_CS
mdefine_line|#define M2_BRG_CS 0x02
DECL|macro|M3_BRG_CS
mdefine_line|#define M3_BRG_CS 0x03
DECL|macro|M4_BRG_CS
mdefine_line|#define M4_BRG_CS 0x04
DECL|macro|M5_BRG_CS
mdefine_line|#define M5_BRG_CS 0x05
DECL|macro|M6_BRG_CS
mdefine_line|#define M6_BRG_CS 0x06
DECL|macro|M7_BRG_CS
mdefine_line|#define M7_BRG_CS 0x07
DECL|macro|M_BRG_ADDR
mdefine_line|#define M_BRG_ADDR 0x18
DECL|macro|M1_BRG_ADDR
mdefine_line|#define M1_BRG_ADDR 0x08
DECL|macro|M2_BRG_ADDR
mdefine_line|#define M2_BRG_ADDR 0x10
DECL|macro|M3_BRG_ADDR
mdefine_line|#define M3_BRG_ADDR 0x18
DECL|macro|M_BRG_CS_SRC
mdefine_line|#define M_BRG_CS_SRC 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_brg_cs
id|REGWORD
id|v_brg_cs
suffix:colon
l_int|3
suffix:semicolon
DECL|member|v_brg_addr
id|REGWORD
id|v_brg_addr
suffix:colon
l_int|2
suffix:semicolon
DECL|member|reserved_57
id|REGWORD
id|reserved_57
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_brg_cs_src
id|REGWORD
id|v_brg_cs_src
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_brg_ctrl
)brace
id|bit_r_brg_ctrl
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_brg_ctrl
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_brg_ctrl
id|bit
suffix:semicolon
)brace
id|reg_r_brg_ctrl
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_PWM_MD
mdefine_line|#define R_PWM_MD 0x46
DECL|macro|M_EXT_IRQ_EN
mdefine_line|#define M_EXT_IRQ_EN 0x08
DECL|macro|M_PWM0_MD
mdefine_line|#define M_PWM0_MD 0x30
DECL|macro|M1_PWM0_MD
mdefine_line|#define M1_PWM0_MD 0x10
DECL|macro|M2_PWM0_MD
mdefine_line|#define M2_PWM0_MD 0x20
DECL|macro|M3_PWM0_MD
mdefine_line|#define M3_PWM0_MD 0x30
DECL|macro|M_PWM1_MD
mdefine_line|#define M_PWM1_MD 0xC0
DECL|macro|M1_PWM1_MD
mdefine_line|#define M1_PWM1_MD 0x40
DECL|macro|M2_PWM1_MD
mdefine_line|#define M2_PWM1_MD 0x80
DECL|macro|M3_PWM1_MD
mdefine_line|#define M3_PWM1_MD 0xC0
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|reserved_58
id|REGWORD
id|reserved_58
suffix:colon
l_int|3
suffix:semicolon
DECL|member|v_ext_irq_en
id|REGWORD
id|v_ext_irq_en
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_pwm0_md
id|REGWORD
id|v_pwm0_md
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_pwm1_md
id|REGWORD
id|v_pwm1_md
suffix:colon
l_int|2
suffix:semicolon
DECL|typedef|bit_r_pwm_md
)brace
id|bit_r_pwm_md
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_pwm_md
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_pwm_md
id|bit
suffix:semicolon
)brace
id|reg_r_pwm_md
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_BRG_MD
mdefine_line|#define R_BRG_MD 0x47
DECL|macro|M_BRG_MD0
mdefine_line|#define M_BRG_MD0 0x01
DECL|macro|M_BRG_MD1
mdefine_line|#define M_BRG_MD1 0x02
DECL|macro|M_BRG_MD2
mdefine_line|#define M_BRG_MD2 0x04
DECL|macro|M_BRG_MD3
mdefine_line|#define M_BRG_MD3 0x08
DECL|macro|M_BRG_MD4
mdefine_line|#define M_BRG_MD4 0x10
DECL|macro|M_BRG_MD5
mdefine_line|#define M_BRG_MD5 0x20
DECL|macro|M_BRG_MD6
mdefine_line|#define M_BRG_MD6 0x40
DECL|macro|M_BRG_MD7
mdefine_line|#define M_BRG_MD7 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_brg_md0
id|REGWORD
id|v_brg_md0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_brg_md1
id|REGWORD
id|v_brg_md1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_brg_md2
id|REGWORD
id|v_brg_md2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_brg_md3
id|REGWORD
id|v_brg_md3
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_brg_md4
id|REGWORD
id|v_brg_md4
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_brg_md5
id|REGWORD
id|v_brg_md5
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_brg_md6
id|REGWORD
id|v_brg_md6
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_brg_md7
id|REGWORD
id|v_brg_md7
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_brg_md
)brace
id|bit_r_brg_md
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_brg_md
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_brg_md
id|bit
suffix:semicolon
)brace
id|reg_r_brg_md
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_BRG_TIM0
mdefine_line|#define R_BRG_TIM0 0x48
DECL|macro|M_BRG_TIM0_IDLE
mdefine_line|#define M_BRG_TIM0_IDLE 0x0F
DECL|macro|M1_BRG_TIM0_IDLE
mdefine_line|#define M1_BRG_TIM0_IDLE 0x01
DECL|macro|M2_BRG_TIM0_IDLE
mdefine_line|#define M2_BRG_TIM0_IDLE 0x02
DECL|macro|M3_BRG_TIM0_IDLE
mdefine_line|#define M3_BRG_TIM0_IDLE 0x03
DECL|macro|M4_BRG_TIM0_IDLE
mdefine_line|#define M4_BRG_TIM0_IDLE 0x04
DECL|macro|M5_BRG_TIM0_IDLE
mdefine_line|#define M5_BRG_TIM0_IDLE 0x05
DECL|macro|M6_BRG_TIM0_IDLE
mdefine_line|#define M6_BRG_TIM0_IDLE 0x06
DECL|macro|M7_BRG_TIM0_IDLE
mdefine_line|#define M7_BRG_TIM0_IDLE 0x07
DECL|macro|M8_BRG_TIM0_IDLE
mdefine_line|#define M8_BRG_TIM0_IDLE 0x08
DECL|macro|M9_BRG_TIM0_IDLE
mdefine_line|#define M9_BRG_TIM0_IDLE 0x09
DECL|macro|M10_BRG_TIM0_IDLE
mdefine_line|#define M10_BRG_TIM0_IDLE 0x0A
DECL|macro|M11_BRG_TIM0_IDLE
mdefine_line|#define M11_BRG_TIM0_IDLE 0x0B
DECL|macro|M12_BRG_TIM0_IDLE
mdefine_line|#define M12_BRG_TIM0_IDLE 0x0C
DECL|macro|M13_BRG_TIM0_IDLE
mdefine_line|#define M13_BRG_TIM0_IDLE 0x0D
DECL|macro|M14_BRG_TIM0_IDLE
mdefine_line|#define M14_BRG_TIM0_IDLE 0x0E
DECL|macro|M15_BRG_TIM0_IDLE
mdefine_line|#define M15_BRG_TIM0_IDLE 0x0F
DECL|macro|M_BRG_TIM0_CLK
mdefine_line|#define M_BRG_TIM0_CLK 0xF0
DECL|macro|M1_BRG_TIM0_CLK
mdefine_line|#define M1_BRG_TIM0_CLK 0x10
DECL|macro|M2_BRG_TIM0_CLK
mdefine_line|#define M2_BRG_TIM0_CLK 0x20
DECL|macro|M3_BRG_TIM0_CLK
mdefine_line|#define M3_BRG_TIM0_CLK 0x30
DECL|macro|M4_BRG_TIM0_CLK
mdefine_line|#define M4_BRG_TIM0_CLK 0x40
DECL|macro|M5_BRG_TIM0_CLK
mdefine_line|#define M5_BRG_TIM0_CLK 0x50
DECL|macro|M6_BRG_TIM0_CLK
mdefine_line|#define M6_BRG_TIM0_CLK 0x60
DECL|macro|M7_BRG_TIM0_CLK
mdefine_line|#define M7_BRG_TIM0_CLK 0x70
DECL|macro|M8_BRG_TIM0_CLK
mdefine_line|#define M8_BRG_TIM0_CLK 0x80
DECL|macro|M9_BRG_TIM0_CLK
mdefine_line|#define M9_BRG_TIM0_CLK 0x90
DECL|macro|M10_BRG_TIM0_CLK
mdefine_line|#define M10_BRG_TIM0_CLK 0xA0
DECL|macro|M11_BRG_TIM0_CLK
mdefine_line|#define M11_BRG_TIM0_CLK 0xB0
DECL|macro|M12_BRG_TIM0_CLK
mdefine_line|#define M12_BRG_TIM0_CLK 0xC0
DECL|macro|M13_BRG_TIM0_CLK
mdefine_line|#define M13_BRG_TIM0_CLK 0xD0
DECL|macro|M14_BRG_TIM0_CLK
mdefine_line|#define M14_BRG_TIM0_CLK 0xE0
DECL|macro|M15_BRG_TIM0_CLK
mdefine_line|#define M15_BRG_TIM0_CLK 0xF0
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_brg_tim0_idle
id|REGWORD
id|v_brg_tim0_idle
suffix:colon
l_int|4
suffix:semicolon
DECL|member|v_brg_tim0_clk
id|REGWORD
id|v_brg_tim0_clk
suffix:colon
l_int|4
suffix:semicolon
DECL|typedef|bit_r_brg_tim0
)brace
id|bit_r_brg_tim0
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_brg_tim0
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_brg_tim0
id|bit
suffix:semicolon
)brace
id|reg_r_brg_tim0
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_BRG_TIM1
mdefine_line|#define R_BRG_TIM1 0x49
DECL|macro|M_BRG_TIM1_IDLE
mdefine_line|#define M_BRG_TIM1_IDLE 0x0F
DECL|macro|M1_BRG_TIM1_IDLE
mdefine_line|#define M1_BRG_TIM1_IDLE 0x01
DECL|macro|M2_BRG_TIM1_IDLE
mdefine_line|#define M2_BRG_TIM1_IDLE 0x02
DECL|macro|M3_BRG_TIM1_IDLE
mdefine_line|#define M3_BRG_TIM1_IDLE 0x03
DECL|macro|M4_BRG_TIM1_IDLE
mdefine_line|#define M4_BRG_TIM1_IDLE 0x04
DECL|macro|M5_BRG_TIM1_IDLE
mdefine_line|#define M5_BRG_TIM1_IDLE 0x05
DECL|macro|M6_BRG_TIM1_IDLE
mdefine_line|#define M6_BRG_TIM1_IDLE 0x06
DECL|macro|M7_BRG_TIM1_IDLE
mdefine_line|#define M7_BRG_TIM1_IDLE 0x07
DECL|macro|M8_BRG_TIM1_IDLE
mdefine_line|#define M8_BRG_TIM1_IDLE 0x08
DECL|macro|M9_BRG_TIM1_IDLE
mdefine_line|#define M9_BRG_TIM1_IDLE 0x09
DECL|macro|M10_BRG_TIM1_IDLE
mdefine_line|#define M10_BRG_TIM1_IDLE 0x0A
DECL|macro|M11_BRG_TIM1_IDLE
mdefine_line|#define M11_BRG_TIM1_IDLE 0x0B
DECL|macro|M12_BRG_TIM1_IDLE
mdefine_line|#define M12_BRG_TIM1_IDLE 0x0C
DECL|macro|M13_BRG_TIM1_IDLE
mdefine_line|#define M13_BRG_TIM1_IDLE 0x0D
DECL|macro|M14_BRG_TIM1_IDLE
mdefine_line|#define M14_BRG_TIM1_IDLE 0x0E
DECL|macro|M15_BRG_TIM1_IDLE
mdefine_line|#define M15_BRG_TIM1_IDLE 0x0F
DECL|macro|M_BRG_TIM1_CLK
mdefine_line|#define M_BRG_TIM1_CLK 0xF0
DECL|macro|M1_BRG_TIM1_CLK
mdefine_line|#define M1_BRG_TIM1_CLK 0x10
DECL|macro|M2_BRG_TIM1_CLK
mdefine_line|#define M2_BRG_TIM1_CLK 0x20
DECL|macro|M3_BRG_TIM1_CLK
mdefine_line|#define M3_BRG_TIM1_CLK 0x30
DECL|macro|M4_BRG_TIM1_CLK
mdefine_line|#define M4_BRG_TIM1_CLK 0x40
DECL|macro|M5_BRG_TIM1_CLK
mdefine_line|#define M5_BRG_TIM1_CLK 0x50
DECL|macro|M6_BRG_TIM1_CLK
mdefine_line|#define M6_BRG_TIM1_CLK 0x60
DECL|macro|M7_BRG_TIM1_CLK
mdefine_line|#define M7_BRG_TIM1_CLK 0x70
DECL|macro|M8_BRG_TIM1_CLK
mdefine_line|#define M8_BRG_TIM1_CLK 0x80
DECL|macro|M9_BRG_TIM1_CLK
mdefine_line|#define M9_BRG_TIM1_CLK 0x90
DECL|macro|M10_BRG_TIM1_CLK
mdefine_line|#define M10_BRG_TIM1_CLK 0xA0
DECL|macro|M11_BRG_TIM1_CLK
mdefine_line|#define M11_BRG_TIM1_CLK 0xB0
DECL|macro|M12_BRG_TIM1_CLK
mdefine_line|#define M12_BRG_TIM1_CLK 0xC0
DECL|macro|M13_BRG_TIM1_CLK
mdefine_line|#define M13_BRG_TIM1_CLK 0xD0
DECL|macro|M14_BRG_TIM1_CLK
mdefine_line|#define M14_BRG_TIM1_CLK 0xE0
DECL|macro|M15_BRG_TIM1_CLK
mdefine_line|#define M15_BRG_TIM1_CLK 0xF0
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_brg_tim1_idle
id|REGWORD
id|v_brg_tim1_idle
suffix:colon
l_int|4
suffix:semicolon
DECL|member|v_brg_tim1_clk
id|REGWORD
id|v_brg_tim1_clk
suffix:colon
l_int|4
suffix:semicolon
DECL|typedef|bit_r_brg_tim1
)brace
id|bit_r_brg_tim1
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_brg_tim1
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_brg_tim1
id|bit
suffix:semicolon
)brace
id|reg_r_brg_tim1
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_BRG_TIM2
mdefine_line|#define R_BRG_TIM2 0x4A
DECL|macro|M_BRG_TIM2_IDLE
mdefine_line|#define M_BRG_TIM2_IDLE 0x0F
DECL|macro|M1_BRG_TIM2_IDLE
mdefine_line|#define M1_BRG_TIM2_IDLE 0x01
DECL|macro|M2_BRG_TIM2_IDLE
mdefine_line|#define M2_BRG_TIM2_IDLE 0x02
DECL|macro|M3_BRG_TIM2_IDLE
mdefine_line|#define M3_BRG_TIM2_IDLE 0x03
DECL|macro|M4_BRG_TIM2_IDLE
mdefine_line|#define M4_BRG_TIM2_IDLE 0x04
DECL|macro|M5_BRG_TIM2_IDLE
mdefine_line|#define M5_BRG_TIM2_IDLE 0x05
DECL|macro|M6_BRG_TIM2_IDLE
mdefine_line|#define M6_BRG_TIM2_IDLE 0x06
DECL|macro|M7_BRG_TIM2_IDLE
mdefine_line|#define M7_BRG_TIM2_IDLE 0x07
DECL|macro|M8_BRG_TIM2_IDLE
mdefine_line|#define M8_BRG_TIM2_IDLE 0x08
DECL|macro|M9_BRG_TIM2_IDLE
mdefine_line|#define M9_BRG_TIM2_IDLE 0x09
DECL|macro|M10_BRG_TIM2_IDLE
mdefine_line|#define M10_BRG_TIM2_IDLE 0x0A
DECL|macro|M11_BRG_TIM2_IDLE
mdefine_line|#define M11_BRG_TIM2_IDLE 0x0B
DECL|macro|M12_BRG_TIM2_IDLE
mdefine_line|#define M12_BRG_TIM2_IDLE 0x0C
DECL|macro|M13_BRG_TIM2_IDLE
mdefine_line|#define M13_BRG_TIM2_IDLE 0x0D
DECL|macro|M14_BRG_TIM2_IDLE
mdefine_line|#define M14_BRG_TIM2_IDLE 0x0E
DECL|macro|M15_BRG_TIM2_IDLE
mdefine_line|#define M15_BRG_TIM2_IDLE 0x0F
DECL|macro|M_BRG_TIM2_CLK
mdefine_line|#define M_BRG_TIM2_CLK 0xF0
DECL|macro|M1_BRG_TIM2_CLK
mdefine_line|#define M1_BRG_TIM2_CLK 0x10
DECL|macro|M2_BRG_TIM2_CLK
mdefine_line|#define M2_BRG_TIM2_CLK 0x20
DECL|macro|M3_BRG_TIM2_CLK
mdefine_line|#define M3_BRG_TIM2_CLK 0x30
DECL|macro|M4_BRG_TIM2_CLK
mdefine_line|#define M4_BRG_TIM2_CLK 0x40
DECL|macro|M5_BRG_TIM2_CLK
mdefine_line|#define M5_BRG_TIM2_CLK 0x50
DECL|macro|M6_BRG_TIM2_CLK
mdefine_line|#define M6_BRG_TIM2_CLK 0x60
DECL|macro|M7_BRG_TIM2_CLK
mdefine_line|#define M7_BRG_TIM2_CLK 0x70
DECL|macro|M8_BRG_TIM2_CLK
mdefine_line|#define M8_BRG_TIM2_CLK 0x80
DECL|macro|M9_BRG_TIM2_CLK
mdefine_line|#define M9_BRG_TIM2_CLK 0x90
DECL|macro|M10_BRG_TIM2_CLK
mdefine_line|#define M10_BRG_TIM2_CLK 0xA0
DECL|macro|M11_BRG_TIM2_CLK
mdefine_line|#define M11_BRG_TIM2_CLK 0xB0
DECL|macro|M12_BRG_TIM2_CLK
mdefine_line|#define M12_BRG_TIM2_CLK 0xC0
DECL|macro|M13_BRG_TIM2_CLK
mdefine_line|#define M13_BRG_TIM2_CLK 0xD0
DECL|macro|M14_BRG_TIM2_CLK
mdefine_line|#define M14_BRG_TIM2_CLK 0xE0
DECL|macro|M15_BRG_TIM2_CLK
mdefine_line|#define M15_BRG_TIM2_CLK 0xF0
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_brg_tim2_idle
id|REGWORD
id|v_brg_tim2_idle
suffix:colon
l_int|4
suffix:semicolon
DECL|member|v_brg_tim2_clk
id|REGWORD
id|v_brg_tim2_clk
suffix:colon
l_int|4
suffix:semicolon
DECL|typedef|bit_r_brg_tim2
)brace
id|bit_r_brg_tim2
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_brg_tim2
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_brg_tim2
id|bit
suffix:semicolon
)brace
id|reg_r_brg_tim2
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_BRG_TIM3
mdefine_line|#define R_BRG_TIM3 0x4B
DECL|macro|M_BRG_TIM3_IDLE
mdefine_line|#define M_BRG_TIM3_IDLE 0x0F
DECL|macro|M1_BRG_TIM3_IDLE
mdefine_line|#define M1_BRG_TIM3_IDLE 0x01
DECL|macro|M2_BRG_TIM3_IDLE
mdefine_line|#define M2_BRG_TIM3_IDLE 0x02
DECL|macro|M3_BRG_TIM3_IDLE
mdefine_line|#define M3_BRG_TIM3_IDLE 0x03
DECL|macro|M4_BRG_TIM3_IDLE
mdefine_line|#define M4_BRG_TIM3_IDLE 0x04
DECL|macro|M5_BRG_TIM3_IDLE
mdefine_line|#define M5_BRG_TIM3_IDLE 0x05
DECL|macro|M6_BRG_TIM3_IDLE
mdefine_line|#define M6_BRG_TIM3_IDLE 0x06
DECL|macro|M7_BRG_TIM3_IDLE
mdefine_line|#define M7_BRG_TIM3_IDLE 0x07
DECL|macro|M8_BRG_TIM3_IDLE
mdefine_line|#define M8_BRG_TIM3_IDLE 0x08
DECL|macro|M9_BRG_TIM3_IDLE
mdefine_line|#define M9_BRG_TIM3_IDLE 0x09
DECL|macro|M10_BRG_TIM3_IDLE
mdefine_line|#define M10_BRG_TIM3_IDLE 0x0A
DECL|macro|M11_BRG_TIM3_IDLE
mdefine_line|#define M11_BRG_TIM3_IDLE 0x0B
DECL|macro|M12_BRG_TIM3_IDLE
mdefine_line|#define M12_BRG_TIM3_IDLE 0x0C
DECL|macro|M13_BRG_TIM3_IDLE
mdefine_line|#define M13_BRG_TIM3_IDLE 0x0D
DECL|macro|M14_BRG_TIM3_IDLE
mdefine_line|#define M14_BRG_TIM3_IDLE 0x0E
DECL|macro|M15_BRG_TIM3_IDLE
mdefine_line|#define M15_BRG_TIM3_IDLE 0x0F
DECL|macro|M_BRG_TIM3_CLK
mdefine_line|#define M_BRG_TIM3_CLK 0xF0
DECL|macro|M1_BRG_TIM3_CLK
mdefine_line|#define M1_BRG_TIM3_CLK 0x10
DECL|macro|M2_BRG_TIM3_CLK
mdefine_line|#define M2_BRG_TIM3_CLK 0x20
DECL|macro|M3_BRG_TIM3_CLK
mdefine_line|#define M3_BRG_TIM3_CLK 0x30
DECL|macro|M4_BRG_TIM3_CLK
mdefine_line|#define M4_BRG_TIM3_CLK 0x40
DECL|macro|M5_BRG_TIM3_CLK
mdefine_line|#define M5_BRG_TIM3_CLK 0x50
DECL|macro|M6_BRG_TIM3_CLK
mdefine_line|#define M6_BRG_TIM3_CLK 0x60
DECL|macro|M7_BRG_TIM3_CLK
mdefine_line|#define M7_BRG_TIM3_CLK 0x70
DECL|macro|M8_BRG_TIM3_CLK
mdefine_line|#define M8_BRG_TIM3_CLK 0x80
DECL|macro|M9_BRG_TIM3_CLK
mdefine_line|#define M9_BRG_TIM3_CLK 0x90
DECL|macro|M10_BRG_TIM3_CLK
mdefine_line|#define M10_BRG_TIM3_CLK 0xA0
DECL|macro|M11_BRG_TIM3_CLK
mdefine_line|#define M11_BRG_TIM3_CLK 0xB0
DECL|macro|M12_BRG_TIM3_CLK
mdefine_line|#define M12_BRG_TIM3_CLK 0xC0
DECL|macro|M13_BRG_TIM3_CLK
mdefine_line|#define M13_BRG_TIM3_CLK 0xD0
DECL|macro|M14_BRG_TIM3_CLK
mdefine_line|#define M14_BRG_TIM3_CLK 0xE0
DECL|macro|M15_BRG_TIM3_CLK
mdefine_line|#define M15_BRG_TIM3_CLK 0xF0
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_brg_tim3_idle
id|REGWORD
id|v_brg_tim3_idle
suffix:colon
l_int|4
suffix:semicolon
DECL|member|v_brg_tim3_clk
id|REGWORD
id|v_brg_tim3_clk
suffix:colon
l_int|4
suffix:semicolon
DECL|typedef|bit_r_brg_tim3
)brace
id|bit_r_brg_tim3
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_brg_tim3
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_brg_tim3
id|bit
suffix:semicolon
)brace
id|reg_r_brg_tim3
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_BRG_TIM_SEL01
mdefine_line|#define R_BRG_TIM_SEL01 0x4C
DECL|macro|M_BRG_WR_SEL0
mdefine_line|#define M_BRG_WR_SEL0 0x03
DECL|macro|M1_BRG_WR_SEL0
mdefine_line|#define M1_BRG_WR_SEL0 0x01
DECL|macro|M2_BRG_WR_SEL0
mdefine_line|#define M2_BRG_WR_SEL0 0x02
DECL|macro|M3_BRG_WR_SEL0
mdefine_line|#define M3_BRG_WR_SEL0 0x03
DECL|macro|M_BRG_RD_SEL0
mdefine_line|#define M_BRG_RD_SEL0 0x0C
DECL|macro|M1_BRG_RD_SEL0
mdefine_line|#define M1_BRG_RD_SEL0 0x04
DECL|macro|M2_BRG_RD_SEL0
mdefine_line|#define M2_BRG_RD_SEL0 0x08
DECL|macro|M3_BRG_RD_SEL0
mdefine_line|#define M3_BRG_RD_SEL0 0x0C
DECL|macro|M_BRG_WR_SEL1
mdefine_line|#define M_BRG_WR_SEL1 0x30
DECL|macro|M1_BRG_WR_SEL1
mdefine_line|#define M1_BRG_WR_SEL1 0x10
DECL|macro|M2_BRG_WR_SEL1
mdefine_line|#define M2_BRG_WR_SEL1 0x20
DECL|macro|M3_BRG_WR_SEL1
mdefine_line|#define M3_BRG_WR_SEL1 0x30
DECL|macro|M_BRG_RD_SEL1
mdefine_line|#define M_BRG_RD_SEL1 0xC0
DECL|macro|M1_BRG_RD_SEL1
mdefine_line|#define M1_BRG_RD_SEL1 0x40
DECL|macro|M2_BRG_RD_SEL1
mdefine_line|#define M2_BRG_RD_SEL1 0x80
DECL|macro|M3_BRG_RD_SEL1
mdefine_line|#define M3_BRG_RD_SEL1 0xC0
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_brg_wr_sel0
id|REGWORD
id|v_brg_wr_sel0
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_brg_rd_sel0
id|REGWORD
id|v_brg_rd_sel0
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_brg_wr_sel1
id|REGWORD
id|v_brg_wr_sel1
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_brg_rd_sel1
id|REGWORD
id|v_brg_rd_sel1
suffix:colon
l_int|2
suffix:semicolon
DECL|typedef|bit_r_brg_tim_sel01
)brace
id|bit_r_brg_tim_sel01
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_brg_tim_sel01
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_brg_tim_sel01
id|bit
suffix:semicolon
)brace
id|reg_r_brg_tim_sel01
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_BRG_TIM_SEL23
mdefine_line|#define R_BRG_TIM_SEL23 0x4D
DECL|macro|M_BRG_WR_SEL2
mdefine_line|#define M_BRG_WR_SEL2 0x03
DECL|macro|M1_BRG_WR_SEL2
mdefine_line|#define M1_BRG_WR_SEL2 0x01
DECL|macro|M2_BRG_WR_SEL2
mdefine_line|#define M2_BRG_WR_SEL2 0x02
DECL|macro|M3_BRG_WR_SEL2
mdefine_line|#define M3_BRG_WR_SEL2 0x03
DECL|macro|M_BRG_RD_SEL2
mdefine_line|#define M_BRG_RD_SEL2 0x0C
DECL|macro|M1_BRG_RD_SEL2
mdefine_line|#define M1_BRG_RD_SEL2 0x04
DECL|macro|M2_BRG_RD_SEL2
mdefine_line|#define M2_BRG_RD_SEL2 0x08
DECL|macro|M3_BRG_RD_SEL2
mdefine_line|#define M3_BRG_RD_SEL2 0x0C
DECL|macro|M_BRG_WR_SEL3
mdefine_line|#define M_BRG_WR_SEL3 0x30
DECL|macro|M1_BRG_WR_SEL3
mdefine_line|#define M1_BRG_WR_SEL3 0x10
DECL|macro|M2_BRG_WR_SEL3
mdefine_line|#define M2_BRG_WR_SEL3 0x20
DECL|macro|M3_BRG_WR_SEL3
mdefine_line|#define M3_BRG_WR_SEL3 0x30
DECL|macro|M_BRG_RD_SEL3
mdefine_line|#define M_BRG_RD_SEL3 0xC0
DECL|macro|M1_BRG_RD_SEL3
mdefine_line|#define M1_BRG_RD_SEL3 0x40
DECL|macro|M2_BRG_RD_SEL3
mdefine_line|#define M2_BRG_RD_SEL3 0x80
DECL|macro|M3_BRG_RD_SEL3
mdefine_line|#define M3_BRG_RD_SEL3 0xC0
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_brg_wr_sel2
id|REGWORD
id|v_brg_wr_sel2
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_brg_rd_sel2
id|REGWORD
id|v_brg_rd_sel2
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_brg_wr_sel3
id|REGWORD
id|v_brg_wr_sel3
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_brg_rd_sel3
id|REGWORD
id|v_brg_rd_sel3
suffix:colon
l_int|2
suffix:semicolon
DECL|typedef|bit_r_brg_tim_sel23
)brace
id|bit_r_brg_tim_sel23
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_brg_tim_sel23
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_brg_tim_sel23
id|bit
suffix:semicolon
)brace
id|reg_r_brg_tim_sel23
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_BRG_TIM_SEL45
mdefine_line|#define R_BRG_TIM_SEL45 0x4E
DECL|macro|M_BRG_WR_SEL4
mdefine_line|#define M_BRG_WR_SEL4 0x03
DECL|macro|M1_BRG_WR_SEL4
mdefine_line|#define M1_BRG_WR_SEL4 0x01
DECL|macro|M2_BRG_WR_SEL4
mdefine_line|#define M2_BRG_WR_SEL4 0x02
DECL|macro|M3_BRG_WR_SEL4
mdefine_line|#define M3_BRG_WR_SEL4 0x03
DECL|macro|M_BRG_RD_SEL4
mdefine_line|#define M_BRG_RD_SEL4 0x0C
DECL|macro|M1_BRG_RD_SEL4
mdefine_line|#define M1_BRG_RD_SEL4 0x04
DECL|macro|M2_BRG_RD_SEL4
mdefine_line|#define M2_BRG_RD_SEL4 0x08
DECL|macro|M3_BRG_RD_SEL4
mdefine_line|#define M3_BRG_RD_SEL4 0x0C
DECL|macro|M_BRG_WR_SEL5
mdefine_line|#define M_BRG_WR_SEL5 0x30
DECL|macro|M1_BRG_WR_SEL5
mdefine_line|#define M1_BRG_WR_SEL5 0x10
DECL|macro|M2_BRG_WR_SEL5
mdefine_line|#define M2_BRG_WR_SEL5 0x20
DECL|macro|M3_BRG_WR_SEL5
mdefine_line|#define M3_BRG_WR_SEL5 0x30
DECL|macro|M_BRG_RD_SEL5
mdefine_line|#define M_BRG_RD_SEL5 0xC0
DECL|macro|M1_BRG_RD_SEL5
mdefine_line|#define M1_BRG_RD_SEL5 0x40
DECL|macro|M2_BRG_RD_SEL5
mdefine_line|#define M2_BRG_RD_SEL5 0x80
DECL|macro|M3_BRG_RD_SEL5
mdefine_line|#define M3_BRG_RD_SEL5 0xC0
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_brg_wr_sel4
id|REGWORD
id|v_brg_wr_sel4
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_brg_rd_sel4
id|REGWORD
id|v_brg_rd_sel4
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_brg_wr_sel5
id|REGWORD
id|v_brg_wr_sel5
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_brg_rd_sel5
id|REGWORD
id|v_brg_rd_sel5
suffix:colon
l_int|2
suffix:semicolon
DECL|typedef|bit_r_brg_tim_sel45
)brace
id|bit_r_brg_tim_sel45
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_brg_tim_sel45
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_brg_tim_sel45
id|bit
suffix:semicolon
)brace
id|reg_r_brg_tim_sel45
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_BRG_TIM_SEL67
mdefine_line|#define R_BRG_TIM_SEL67 0x4F
DECL|macro|M_BRG_WR_SEL6
mdefine_line|#define M_BRG_WR_SEL6 0x03
DECL|macro|M1_BRG_WR_SEL6
mdefine_line|#define M1_BRG_WR_SEL6 0x01
DECL|macro|M2_BRG_WR_SEL6
mdefine_line|#define M2_BRG_WR_SEL6 0x02
DECL|macro|M3_BRG_WR_SEL6
mdefine_line|#define M3_BRG_WR_SEL6 0x03
DECL|macro|M_BRG_RD_SEL6
mdefine_line|#define M_BRG_RD_SEL6 0x0C
DECL|macro|M1_BRG_RD_SEL6
mdefine_line|#define M1_BRG_RD_SEL6 0x04
DECL|macro|M2_BRG_RD_SEL6
mdefine_line|#define M2_BRG_RD_SEL6 0x08
DECL|macro|M3_BRG_RD_SEL6
mdefine_line|#define M3_BRG_RD_SEL6 0x0C
DECL|macro|M_BRG_WR_SEL7
mdefine_line|#define M_BRG_WR_SEL7 0x30
DECL|macro|M1_BRG_WR_SEL7
mdefine_line|#define M1_BRG_WR_SEL7 0x10
DECL|macro|M2_BRG_WR_SEL7
mdefine_line|#define M2_BRG_WR_SEL7 0x20
DECL|macro|M3_BRG_WR_SEL7
mdefine_line|#define M3_BRG_WR_SEL7 0x30
DECL|macro|M_BRG_RD_SEL7
mdefine_line|#define M_BRG_RD_SEL7 0xC0
DECL|macro|M1_BRG_RD_SEL7
mdefine_line|#define M1_BRG_RD_SEL7 0x40
DECL|macro|M2_BRG_RD_SEL7
mdefine_line|#define M2_BRG_RD_SEL7 0x80
DECL|macro|M3_BRG_RD_SEL7
mdefine_line|#define M3_BRG_RD_SEL7 0xC0
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_brg_wr_sel6
id|REGWORD
id|v_brg_wr_sel6
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_brg_rd_sel6
id|REGWORD
id|v_brg_rd_sel6
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_brg_wr_sel7
id|REGWORD
id|v_brg_wr_sel7
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_brg_rd_sel7
id|REGWORD
id|v_brg_rd_sel7
suffix:colon
l_int|2
suffix:semicolon
DECL|typedef|bit_r_brg_tim_sel67
)brace
id|bit_r_brg_tim_sel67
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_brg_tim_sel67
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_brg_tim_sel67
id|bit
suffix:semicolon
)brace
id|reg_r_brg_tim_sel67
suffix:semicolon
singleline_comment|// register and bitmap access
DECL|macro|A_FIFO_DATA0
mdefine_line|#define A_FIFO_DATA0 0x80
DECL|macro|M_FIFO_DATA0
mdefine_line|#define M_FIFO_DATA0 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_fifo_data0
id|REGWORD
id|v_fifo_data0
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_a_fifo_data0
)brace
id|bit_a_fifo_data0
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_fifo_data0
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_fifo_data0
id|bit
suffix:semicolon
)brace
id|reg_a_fifo_data0
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_FIFO_DATA1
mdefine_line|#define A_FIFO_DATA1 0x81
DECL|macro|M_FIFO_DATA1
mdefine_line|#define M_FIFO_DATA1 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_fifo_data1
id|REGWORD
id|v_fifo_data1
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_a_fifo_data1
)brace
id|bit_a_fifo_data1
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_fifo_data1
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_fifo_data1
id|bit
suffix:semicolon
)brace
id|reg_a_fifo_data1
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_FIFO_DATA2
mdefine_line|#define A_FIFO_DATA2 0x82
DECL|macro|M_FIFO_DATA2
mdefine_line|#define M_FIFO_DATA2 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_fifo_data2
id|REGWORD
id|v_fifo_data2
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_a_fifo_data2
)brace
id|bit_a_fifo_data2
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_fifo_data2
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_fifo_data2
id|bit
suffix:semicolon
)brace
id|reg_a_fifo_data2
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_FIFO_DATA3
mdefine_line|#define A_FIFO_DATA3 0x83
DECL|macro|M_FIFO_DATA3
mdefine_line|#define M_FIFO_DATA3 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_fifo_data3
id|REGWORD
id|v_fifo_data3
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_a_fifo_data3
)brace
id|bit_a_fifo_data3
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_fifo_data3
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_fifo_data3
id|bit
suffix:semicolon
)brace
id|reg_a_fifo_data3
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_FIFO_DATA0_NOINC
mdefine_line|#define A_FIFO_DATA0_NOINC 0x84
DECL|macro|M_FIFO_DATA0_NOINC
mdefine_line|#define M_FIFO_DATA0_NOINC 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_fifo_data0_noinc
id|REGWORD
id|v_fifo_data0_noinc
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_a_fifo_data0_noinc
)brace
id|bit_a_fifo_data0_noinc
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_fifo_data0_noinc
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_fifo_data0_noinc
id|bit
suffix:semicolon
)brace
id|reg_a_fifo_data0_noinc
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_FIFO_DATA1_NOINC
mdefine_line|#define A_FIFO_DATA1_NOINC 0x85
DECL|macro|M_FIFO_DATA_NOINC1
mdefine_line|#define M_FIFO_DATA_NOINC1 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_fifo_data_noinc1
id|REGWORD
id|v_fifo_data_noinc1
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_a_fifo_data1_noinc
)brace
id|bit_a_fifo_data1_noinc
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_fifo_data1_noinc
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_fifo_data1_noinc
id|bit
suffix:semicolon
)brace
id|reg_a_fifo_data1_noinc
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_FIFO_DATA2_NOINC
mdefine_line|#define A_FIFO_DATA2_NOINC 0x86
DECL|macro|M_FIFO_DATA2_NOINC
mdefine_line|#define M_FIFO_DATA2_NOINC 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_fifo_data2_noinc
id|REGWORD
id|v_fifo_data2_noinc
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_a_fifo_data2_noinc
)brace
id|bit_a_fifo_data2_noinc
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_fifo_data2_noinc
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_fifo_data2_noinc
id|bit
suffix:semicolon
)brace
id|reg_a_fifo_data2_noinc
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_FIFO_DATA3_NOINC
mdefine_line|#define A_FIFO_DATA3_NOINC 0x87
DECL|macro|M_FIFO_DATA3_NOINC
mdefine_line|#define M_FIFO_DATA3_NOINC 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_fifo_data3_noinc
id|REGWORD
id|v_fifo_data3_noinc
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_a_fifo_data3_noinc
)brace
id|bit_a_fifo_data3_noinc
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_fifo_data3_noinc
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_fifo_data3_noinc
id|bit
suffix:semicolon
)brace
id|reg_a_fifo_data3_noinc
suffix:semicolon
singleline_comment|// register and bitmap access
DECL|macro|R_RAM_DATA
mdefine_line|#define R_RAM_DATA 0xC0
DECL|macro|M_RAM_DATA
mdefine_line|#define M_RAM_DATA 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_ram_data
id|REGWORD
id|v_ram_data
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_r_ram_data
)brace
id|bit_r_ram_data
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_ram_data
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_ram_data
id|bit
suffix:semicolon
)brace
id|reg_r_ram_data
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_IRQ_FIFO_BL0
mdefine_line|#define R_IRQ_FIFO_BL0 0xC8
DECL|macro|M_IRQ_FIFO0_TX
mdefine_line|#define M_IRQ_FIFO0_TX 0x01
DECL|macro|M_IRQ_FIFO0_RX
mdefine_line|#define M_IRQ_FIFO0_RX 0x02
DECL|macro|M_IRQ_FIFO1_TX
mdefine_line|#define M_IRQ_FIFO1_TX 0x04
DECL|macro|M_IRQ_FIFO1_RX
mdefine_line|#define M_IRQ_FIFO1_RX 0x08
DECL|macro|M_IRQ_FIFO2_TX
mdefine_line|#define M_IRQ_FIFO2_TX 0x10
DECL|macro|M_IRQ_FIFO2_RX
mdefine_line|#define M_IRQ_FIFO2_RX 0x20
DECL|macro|M_IRQ_FIFO3_TX
mdefine_line|#define M_IRQ_FIFO3_TX 0x40
DECL|macro|M_IRQ_FIFO3_RX
mdefine_line|#define M_IRQ_FIFO3_RX 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_irq_fifo0_tx
id|REGWORD
id|v_irq_fifo0_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo0_rx
id|REGWORD
id|v_irq_fifo0_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo1_tx
id|REGWORD
id|v_irq_fifo1_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo1_rx
id|REGWORD
id|v_irq_fifo1_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo2_tx
id|REGWORD
id|v_irq_fifo2_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo2_rx
id|REGWORD
id|v_irq_fifo2_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo3_tx
id|REGWORD
id|v_irq_fifo3_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo3_rx
id|REGWORD
id|v_irq_fifo3_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_irq_fifo_bl0
)brace
id|bit_r_irq_fifo_bl0
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_irq_fifo_bl0
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_irq_fifo_bl0
id|bit
suffix:semicolon
)brace
id|reg_r_irq_fifo_bl0
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_IRQ_FIFO_BL1
mdefine_line|#define R_IRQ_FIFO_BL1 0xC9
DECL|macro|M_IRQ_FIFO4_TX
mdefine_line|#define M_IRQ_FIFO4_TX 0x01
DECL|macro|M_IRQ_FIFO4_RX
mdefine_line|#define M_IRQ_FIFO4_RX 0x02
DECL|macro|M_IRQ_FIFO5_TX
mdefine_line|#define M_IRQ_FIFO5_TX 0x04
DECL|macro|M_IRQ_FIFO5_RX
mdefine_line|#define M_IRQ_FIFO5_RX 0x08
DECL|macro|M_IRQ_FIFO6_TX
mdefine_line|#define M_IRQ_FIFO6_TX 0x10
DECL|macro|M_IRQ_FIFO6_RX
mdefine_line|#define M_IRQ_FIFO6_RX 0x20
DECL|macro|M_IRQ_FIFO7_TX
mdefine_line|#define M_IRQ_FIFO7_TX 0x40
DECL|macro|M_IRQ_FIFO7_RX
mdefine_line|#define M_IRQ_FIFO7_RX 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_irq_fifo4_tx
id|REGWORD
id|v_irq_fifo4_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo4_rx
id|REGWORD
id|v_irq_fifo4_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo5_tx
id|REGWORD
id|v_irq_fifo5_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo5_rx
id|REGWORD
id|v_irq_fifo5_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo6_tx
id|REGWORD
id|v_irq_fifo6_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo6_rx
id|REGWORD
id|v_irq_fifo6_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo7_tx
id|REGWORD
id|v_irq_fifo7_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo7_rx
id|REGWORD
id|v_irq_fifo7_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_irq_fifo_bl1
)brace
id|bit_r_irq_fifo_bl1
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_irq_fifo_bl1
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_irq_fifo_bl1
id|bit
suffix:semicolon
)brace
id|reg_r_irq_fifo_bl1
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_IRQ_FIFO_BL2
mdefine_line|#define R_IRQ_FIFO_BL2 0xCA
DECL|macro|M_IRQ_FIFO8_TX
mdefine_line|#define M_IRQ_FIFO8_TX 0x01
DECL|macro|M_IRQ_FIFO8_RX
mdefine_line|#define M_IRQ_FIFO8_RX 0x02
DECL|macro|M_IRQ_FIFO9_TX
mdefine_line|#define M_IRQ_FIFO9_TX 0x04
DECL|macro|M_IRQ_FIFO9_RX
mdefine_line|#define M_IRQ_FIFO9_RX 0x08
DECL|macro|M_IRQ_FIFO10_TX
mdefine_line|#define M_IRQ_FIFO10_TX 0x10
DECL|macro|M_IRQ_FIFO10_RX
mdefine_line|#define M_IRQ_FIFO10_RX 0x20
DECL|macro|M_IRQ_FIFO11_TX
mdefine_line|#define M_IRQ_FIFO11_TX 0x40
DECL|macro|M_IRQ_FIFO11_RX
mdefine_line|#define M_IRQ_FIFO11_RX 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_irq_fifo8_tx
id|REGWORD
id|v_irq_fifo8_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo8_rx
id|REGWORD
id|v_irq_fifo8_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo9_tx
id|REGWORD
id|v_irq_fifo9_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo9_rx
id|REGWORD
id|v_irq_fifo9_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo10_tx
id|REGWORD
id|v_irq_fifo10_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo10_rx
id|REGWORD
id|v_irq_fifo10_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo11_tx
id|REGWORD
id|v_irq_fifo11_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo11_rx
id|REGWORD
id|v_irq_fifo11_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_irq_fifo_bl2
)brace
id|bit_r_irq_fifo_bl2
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_irq_fifo_bl2
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_irq_fifo_bl2
id|bit
suffix:semicolon
)brace
id|reg_r_irq_fifo_bl2
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_IRQ_FIFO_BL3
mdefine_line|#define R_IRQ_FIFO_BL3 0xCB
DECL|macro|M_IRQ_FIFO12_TX
mdefine_line|#define M_IRQ_FIFO12_TX 0x01
DECL|macro|M_IRQ_FIFO12_RX
mdefine_line|#define M_IRQ_FIFO12_RX 0x02
DECL|macro|M_IRQ_FIFO13_TX
mdefine_line|#define M_IRQ_FIFO13_TX 0x04
DECL|macro|M_IRQ_FIFO13_RX
mdefine_line|#define M_IRQ_FIFO13_RX 0x08
DECL|macro|M_IRQ_FIFO14_TX
mdefine_line|#define M_IRQ_FIFO14_TX 0x10
DECL|macro|M_IRQ_FIFO14_RX
mdefine_line|#define M_IRQ_FIFO14_RX 0x20
DECL|macro|M_IRQ_FIFO15_TX
mdefine_line|#define M_IRQ_FIFO15_TX 0x40
DECL|macro|M_IRQ_FIFO15_RX
mdefine_line|#define M_IRQ_FIFO15_RX 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_irq_fifo12_tx
id|REGWORD
id|v_irq_fifo12_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo12_rx
id|REGWORD
id|v_irq_fifo12_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo13_tx
id|REGWORD
id|v_irq_fifo13_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo13_rx
id|REGWORD
id|v_irq_fifo13_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo14_tx
id|REGWORD
id|v_irq_fifo14_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo14_rx
id|REGWORD
id|v_irq_fifo14_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo15_tx
id|REGWORD
id|v_irq_fifo15_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo15_rx
id|REGWORD
id|v_irq_fifo15_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_irq_fifo_bl3
)brace
id|bit_r_irq_fifo_bl3
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_irq_fifo_bl3
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_irq_fifo_bl3
id|bit
suffix:semicolon
)brace
id|reg_r_irq_fifo_bl3
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_IRQ_FIFO_BL4
mdefine_line|#define R_IRQ_FIFO_BL4 0xCC
DECL|macro|M_IRQ_FIFO16_TX
mdefine_line|#define M_IRQ_FIFO16_TX 0x01
DECL|macro|M_IRQ_FIFO16_RX
mdefine_line|#define M_IRQ_FIFO16_RX 0x02
DECL|macro|M_IRQ_FIFO17_TX
mdefine_line|#define M_IRQ_FIFO17_TX 0x04
DECL|macro|M_IRQ_FIFO17_RX
mdefine_line|#define M_IRQ_FIFO17_RX 0x08
DECL|macro|M_IRQ_FIFO18_TX
mdefine_line|#define M_IRQ_FIFO18_TX 0x10
DECL|macro|M_IRQ_FIFO18_RX
mdefine_line|#define M_IRQ_FIFO18_RX 0x20
DECL|macro|M_IRQ_FIFO19_TX
mdefine_line|#define M_IRQ_FIFO19_TX 0x40
DECL|macro|M_IRQ_FIFO19_RX
mdefine_line|#define M_IRQ_FIFO19_RX 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_irq_fifo16_tx
id|REGWORD
id|v_irq_fifo16_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo16_rx
id|REGWORD
id|v_irq_fifo16_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo17_tx
id|REGWORD
id|v_irq_fifo17_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo17_rx
id|REGWORD
id|v_irq_fifo17_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo18_tx
id|REGWORD
id|v_irq_fifo18_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo18_rx
id|REGWORD
id|v_irq_fifo18_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo19_tx
id|REGWORD
id|v_irq_fifo19_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo19_rx
id|REGWORD
id|v_irq_fifo19_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_irq_fifo_bl4
)brace
id|bit_r_irq_fifo_bl4
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_irq_fifo_bl4
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_irq_fifo_bl4
id|bit
suffix:semicolon
)brace
id|reg_r_irq_fifo_bl4
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_IRQ_FIFO_BL5
mdefine_line|#define R_IRQ_FIFO_BL5 0xCD
DECL|macro|M_IRQ_FIFO20_TX
mdefine_line|#define M_IRQ_FIFO20_TX 0x01
DECL|macro|M_IRQ_FIFO20_RX
mdefine_line|#define M_IRQ_FIFO20_RX 0x02
DECL|macro|M_IRQ_FIFO21_TX
mdefine_line|#define M_IRQ_FIFO21_TX 0x04
DECL|macro|M_IRQ_FIFO21_RX
mdefine_line|#define M_IRQ_FIFO21_RX 0x08
DECL|macro|M_IRQ_FIFO22_TX
mdefine_line|#define M_IRQ_FIFO22_TX 0x10
DECL|macro|M_IRQ_FIFO22_RX
mdefine_line|#define M_IRQ_FIFO22_RX 0x20
DECL|macro|M_IRQ_FIFO23_TX
mdefine_line|#define M_IRQ_FIFO23_TX 0x40
DECL|macro|M_IRQ_FIFO23_RX
mdefine_line|#define M_IRQ_FIFO23_RX 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_irq_fifo20_tx
id|REGWORD
id|v_irq_fifo20_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo20_rx
id|REGWORD
id|v_irq_fifo20_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo21_tx
id|REGWORD
id|v_irq_fifo21_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo21_rx
id|REGWORD
id|v_irq_fifo21_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo22_tx
id|REGWORD
id|v_irq_fifo22_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo22_rx
id|REGWORD
id|v_irq_fifo22_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo23_tx
id|REGWORD
id|v_irq_fifo23_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo23_rx
id|REGWORD
id|v_irq_fifo23_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_irq_fifo_bl5
)brace
id|bit_r_irq_fifo_bl5
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_irq_fifo_bl5
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_irq_fifo_bl5
id|bit
suffix:semicolon
)brace
id|reg_r_irq_fifo_bl5
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_IRQ_FIFO_BL6
mdefine_line|#define R_IRQ_FIFO_BL6 0xCE
DECL|macro|M_IRQ_FIFO24_TX
mdefine_line|#define M_IRQ_FIFO24_TX 0x01
DECL|macro|M_IRQ_FIFO24_RX
mdefine_line|#define M_IRQ_FIFO24_RX 0x02
DECL|macro|M_IRQ_FIFO25_TX
mdefine_line|#define M_IRQ_FIFO25_TX 0x04
DECL|macro|M_IRQ_FIFO25_RX
mdefine_line|#define M_IRQ_FIFO25_RX 0x08
DECL|macro|M_IRQ_FIFO26_TX
mdefine_line|#define M_IRQ_FIFO26_TX 0x10
DECL|macro|M_IRQ_FIFO26_RX
mdefine_line|#define M_IRQ_FIFO26_RX 0x20
DECL|macro|M_IRQ_FIFO27_TX
mdefine_line|#define M_IRQ_FIFO27_TX 0x40
DECL|macro|M_IRQ_FIFO27_RX
mdefine_line|#define M_IRQ_FIFO27_RX 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_irq_fifo24_tx
id|REGWORD
id|v_irq_fifo24_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo24_rx
id|REGWORD
id|v_irq_fifo24_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo25_tx
id|REGWORD
id|v_irq_fifo25_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo25_rx
id|REGWORD
id|v_irq_fifo25_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo26_tx
id|REGWORD
id|v_irq_fifo26_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo26_rx
id|REGWORD
id|v_irq_fifo26_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo27_tx
id|REGWORD
id|v_irq_fifo27_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo27_rx
id|REGWORD
id|v_irq_fifo27_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_irq_fifo_bl6
)brace
id|bit_r_irq_fifo_bl6
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_irq_fifo_bl6
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_irq_fifo_bl6
id|bit
suffix:semicolon
)brace
id|reg_r_irq_fifo_bl6
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|R_IRQ_FIFO_BL7
mdefine_line|#define R_IRQ_FIFO_BL7 0xCF
DECL|macro|M_IRQ_FIFO28_TX
mdefine_line|#define M_IRQ_FIFO28_TX 0x01
DECL|macro|M_IRQ_FIFO28_RX
mdefine_line|#define M_IRQ_FIFO28_RX 0x02
DECL|macro|M_IRQ_FIFO29_TX
mdefine_line|#define M_IRQ_FIFO29_TX 0x04
DECL|macro|M_IRQ_FIFO29_RX
mdefine_line|#define M_IRQ_FIFO29_RX 0x08
DECL|macro|M_IRQ_FIFO30_TX
mdefine_line|#define M_IRQ_FIFO30_TX 0x10
DECL|macro|M_IRQ_FIFO30_RX
mdefine_line|#define M_IRQ_FIFO30_RX 0x20
DECL|macro|M_IRQ_FIFO31_TX
mdefine_line|#define M_IRQ_FIFO31_TX 0x40
DECL|macro|M_IRQ_FIFO31_RX
mdefine_line|#define M_IRQ_FIFO31_RX 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_irq_fifo28_tx
id|REGWORD
id|v_irq_fifo28_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo28_rx
id|REGWORD
id|v_irq_fifo28_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo29_tx
id|REGWORD
id|v_irq_fifo29_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo29_rx
id|REGWORD
id|v_irq_fifo29_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo30_tx
id|REGWORD
id|v_irq_fifo30_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo30_rx
id|REGWORD
id|v_irq_fifo30_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo31_tx
id|REGWORD
id|v_irq_fifo31_tx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_irq_fifo31_rx
id|REGWORD
id|v_irq_fifo31_rx
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_r_irq_fifo_bl7
)brace
id|bit_r_irq_fifo_bl7
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_r_irq_fifo_bl7
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_r_irq_fifo_bl7
id|bit
suffix:semicolon
)brace
id|reg_r_irq_fifo_bl7
suffix:semicolon
singleline_comment|// register and bitmap access
DECL|macro|A_SL_CFG
mdefine_line|#define A_SL_CFG 0xD0
DECL|macro|M_CH_DIR
mdefine_line|#define M_CH_DIR 0x01
DECL|macro|M_CH1_SEL
mdefine_line|#define M_CH1_SEL 0x3E
DECL|macro|M1_CH1_SEL
mdefine_line|#define M1_CH1_SEL 0x02
DECL|macro|M2_CH1_SEL
mdefine_line|#define M2_CH1_SEL 0x04
DECL|macro|M3_CH1_SEL
mdefine_line|#define M3_CH1_SEL 0x06
DECL|macro|M4_CH1_SEL
mdefine_line|#define M4_CH1_SEL 0x08
DECL|macro|M5_CH1_SEL
mdefine_line|#define M5_CH1_SEL 0x0A
DECL|macro|M6_CH1_SEL
mdefine_line|#define M6_CH1_SEL 0x0C
DECL|macro|M7_CH1_SEL
mdefine_line|#define M7_CH1_SEL 0x0E
DECL|macro|M8_CH1_SEL
mdefine_line|#define M8_CH1_SEL 0x10
DECL|macro|M9_CH1_SEL
mdefine_line|#define M9_CH1_SEL 0x12
DECL|macro|M10_CH1_SEL
mdefine_line|#define M10_CH1_SEL 0x14
DECL|macro|M11_CH1_SEL
mdefine_line|#define M11_CH1_SEL 0x16
DECL|macro|M12_CH1_SEL
mdefine_line|#define M12_CH1_SEL 0x18
DECL|macro|M13_CH1_SEL
mdefine_line|#define M13_CH1_SEL 0x1A
DECL|macro|M14_CH1_SEL
mdefine_line|#define M14_CH1_SEL 0x1C
DECL|macro|M15_CH1_SEL
mdefine_line|#define M15_CH1_SEL 0x1E
DECL|macro|M16_CH1_SEL
mdefine_line|#define M16_CH1_SEL 0x20
DECL|macro|M17_CH1_SEL
mdefine_line|#define M17_CH1_SEL 0x22
DECL|macro|M18_CH1_SEL
mdefine_line|#define M18_CH1_SEL 0x24
DECL|macro|M19_CH1_SEL
mdefine_line|#define M19_CH1_SEL 0x26
DECL|macro|M20_CH1_SEL
mdefine_line|#define M20_CH1_SEL 0x28
DECL|macro|M21_CH1_SEL
mdefine_line|#define M21_CH1_SEL 0x2A
DECL|macro|M22_CH1_SEL
mdefine_line|#define M22_CH1_SEL 0x2C
DECL|macro|M23_CH1_SEL
mdefine_line|#define M23_CH1_SEL 0x2E
DECL|macro|M24_CH1_SEL
mdefine_line|#define M24_CH1_SEL 0x30
DECL|macro|M25_CH1_SEL
mdefine_line|#define M25_CH1_SEL 0x32
DECL|macro|M26_CH1_SEL
mdefine_line|#define M26_CH1_SEL 0x34
DECL|macro|M27_CH1_SEL
mdefine_line|#define M27_CH1_SEL 0x36
DECL|macro|M28_CH1_SEL
mdefine_line|#define M28_CH1_SEL 0x38
DECL|macro|M29_CH1_SEL
mdefine_line|#define M29_CH1_SEL 0x3A
DECL|macro|M30_CH1_SEL
mdefine_line|#define M30_CH1_SEL 0x3C
DECL|macro|M31_CH1_SEL
mdefine_line|#define M31_CH1_SEL 0x3E
DECL|macro|M_ROUT
mdefine_line|#define M_ROUT 0xC0
DECL|macro|M1_ROUT
mdefine_line|#define M1_ROUT 0x40
DECL|macro|M2_ROUT
mdefine_line|#define M2_ROUT 0x80
DECL|macro|M3_ROUT
mdefine_line|#define M3_ROUT 0xC0
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_ch_dir
id|REGWORD
id|v_ch_dir
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_ch1_sel
id|REGWORD
id|v_ch1_sel
suffix:colon
l_int|5
suffix:semicolon
DECL|member|v_rout
id|REGWORD
id|v_rout
suffix:colon
l_int|2
suffix:semicolon
DECL|typedef|bit_a_sl_cfg
)brace
id|bit_a_sl_cfg
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_sl_cfg
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_sl_cfg
id|bit
suffix:semicolon
)brace
id|reg_a_sl_cfg
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_CONF
mdefine_line|#define A_CONF 0xD1
DECL|macro|M_CONF_NUM
mdefine_line|#define M_CONF_NUM 0x07
DECL|macro|M1_CONF_NUM
mdefine_line|#define M1_CONF_NUM 0x01
DECL|macro|M2_CONF_NUM
mdefine_line|#define M2_CONF_NUM 0x02
DECL|macro|M3_CONF_NUM
mdefine_line|#define M3_CONF_NUM 0x03
DECL|macro|M4_CONF_NUM
mdefine_line|#define M4_CONF_NUM 0x04
DECL|macro|M5_CONF_NUM
mdefine_line|#define M5_CONF_NUM 0x05
DECL|macro|M6_CONF_NUM
mdefine_line|#define M6_CONF_NUM 0x06
DECL|macro|M7_CONF_NUM
mdefine_line|#define M7_CONF_NUM 0x07
DECL|macro|M_NOISE_SUPPR
mdefine_line|#define M_NOISE_SUPPR 0x18
DECL|macro|M1_NOISE_SUPPR
mdefine_line|#define M1_NOISE_SUPPR 0x08
DECL|macro|M2_NOISE_SUPPR
mdefine_line|#define M2_NOISE_SUPPR 0x10
DECL|macro|M3_NOISE_SUPPR
mdefine_line|#define M3_NOISE_SUPPR 0x18
DECL|macro|M_ATT_LEV
mdefine_line|#define M_ATT_LEV 0x60
DECL|macro|M1_ATT_LEV
mdefine_line|#define M1_ATT_LEV 0x20
DECL|macro|M2_ATT_LEV
mdefine_line|#define M2_ATT_LEV 0x40
DECL|macro|M3_ATT_LEV
mdefine_line|#define M3_ATT_LEV 0x60
DECL|macro|M_CONF_SL
mdefine_line|#define M_CONF_SL 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_conf_num
id|REGWORD
id|v_conf_num
suffix:colon
l_int|3
suffix:semicolon
DECL|member|v_noise_suppr
id|REGWORD
id|v_noise_suppr
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_att_lev
id|REGWORD
id|v_att_lev
suffix:colon
l_int|2
suffix:semicolon
DECL|member|v_conf_sl
id|REGWORD
id|v_conf_sl
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_a_conf
)brace
id|bit_a_conf
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_conf
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_conf
id|bit
suffix:semicolon
)brace
id|reg_a_conf
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_CH_MSK
mdefine_line|#define A_CH_MSK 0xF4
DECL|macro|M_CH_MSK
mdefine_line|#define M_CH_MSK 0xFF
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_ch_msk
id|REGWORD
id|v_ch_msk
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|bit_a_ch_msk
)brace
id|bit_a_ch_msk
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_ch_msk
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_ch_msk
id|bit
suffix:semicolon
)brace
id|reg_a_ch_msk
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_CON_HDLC
mdefine_line|#define A_CON_HDLC 0xFA
DECL|macro|M_IFF
mdefine_line|#define M_IFF 0x01
DECL|macro|M_HDLC_TRP
mdefine_line|#define M_HDLC_TRP 0x02
DECL|macro|M_TRP_IRQ
mdefine_line|#define M_TRP_IRQ 0x1C
DECL|macro|M1_TRP_IRQ
mdefine_line|#define M1_TRP_IRQ 0x04
DECL|macro|M2_TRP_IRQ
mdefine_line|#define M2_TRP_IRQ 0x08
DECL|macro|M3_TRP_IRQ
mdefine_line|#define M3_TRP_IRQ 0x0C
DECL|macro|M4_TRP_IRQ
mdefine_line|#define M4_TRP_IRQ 0x10
DECL|macro|M5_TRP_IRQ
mdefine_line|#define M5_TRP_IRQ 0x14
DECL|macro|M6_TRP_IRQ
mdefine_line|#define M6_TRP_IRQ 0x18
DECL|macro|M7_TRP_IRQ
mdefine_line|#define M7_TRP_IRQ 0x1C
DECL|macro|M_DATA_FLOW
mdefine_line|#define M_DATA_FLOW 0xE0
DECL|macro|M1_DATA_FLOW
mdefine_line|#define M1_DATA_FLOW 0x20
DECL|macro|M2_DATA_FLOW
mdefine_line|#define M2_DATA_FLOW 0x40
DECL|macro|M3_DATA_FLOW
mdefine_line|#define M3_DATA_FLOW 0x60
DECL|macro|M4_DATA_FLOW
mdefine_line|#define M4_DATA_FLOW 0x80
DECL|macro|M5_DATA_FLOW
mdefine_line|#define M5_DATA_FLOW 0xA0
DECL|macro|M6_DATA_FLOW
mdefine_line|#define M6_DATA_FLOW 0xC0
DECL|macro|M7_DATA_FLOW
mdefine_line|#define M7_DATA_FLOW 0xE0
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_iff
id|REGWORD
id|v_iff
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_hdlc_trp
id|REGWORD
id|v_hdlc_trp
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_trp_irq
id|REGWORD
id|v_trp_irq
suffix:colon
l_int|3
suffix:semicolon
DECL|member|v_data_flow
id|REGWORD
id|v_data_flow
suffix:colon
l_int|3
suffix:semicolon
DECL|typedef|bit_a_con_hdlc
)brace
id|bit_a_con_hdlc
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_con_hdlc
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_con_hdlc
id|bit
suffix:semicolon
)brace
id|reg_a_con_hdlc
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_SUBCH_CFG
mdefine_line|#define A_SUBCH_CFG 0xFB
DECL|macro|M_BIT_CNT
mdefine_line|#define M_BIT_CNT 0x07
DECL|macro|M1_BIT_CNT
mdefine_line|#define M1_BIT_CNT 0x01
DECL|macro|M2_BIT_CNT
mdefine_line|#define M2_BIT_CNT 0x02
DECL|macro|M3_BIT_CNT
mdefine_line|#define M3_BIT_CNT 0x03
DECL|macro|M4_BIT_CNT
mdefine_line|#define M4_BIT_CNT 0x04
DECL|macro|M5_BIT_CNT
mdefine_line|#define M5_BIT_CNT 0x05
DECL|macro|M6_BIT_CNT
mdefine_line|#define M6_BIT_CNT 0x06
DECL|macro|M7_BIT_CNT
mdefine_line|#define M7_BIT_CNT 0x07
DECL|macro|M_START_BIT
mdefine_line|#define M_START_BIT 0x38
DECL|macro|M1_START_BIT
mdefine_line|#define M1_START_BIT 0x08
DECL|macro|M2_START_BIT
mdefine_line|#define M2_START_BIT 0x10
DECL|macro|M3_START_BIT
mdefine_line|#define M3_START_BIT 0x18
DECL|macro|M4_START_BIT
mdefine_line|#define M4_START_BIT 0x20
DECL|macro|M5_START_BIT
mdefine_line|#define M5_START_BIT 0x28
DECL|macro|M6_START_BIT
mdefine_line|#define M6_START_BIT 0x30
DECL|macro|M7_START_BIT
mdefine_line|#define M7_START_BIT 0x38
DECL|macro|M_LOOP_FIFO
mdefine_line|#define M_LOOP_FIFO 0x40
DECL|macro|M_INV_DATA
mdefine_line|#define M_INV_DATA 0x80
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_bit_cnt
id|REGWORD
id|v_bit_cnt
suffix:colon
l_int|3
suffix:semicolon
DECL|member|v_start_bit
id|REGWORD
id|v_start_bit
suffix:colon
l_int|3
suffix:semicolon
DECL|member|v_loop_fifo
id|REGWORD
id|v_loop_fifo
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_inv_data
id|REGWORD
id|v_inv_data
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_a_subch_cfg
)brace
id|bit_a_subch_cfg
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_subch_cfg
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_subch_cfg
id|bit
suffix:semicolon
)brace
id|reg_a_subch_cfg
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_FIFO_SEQ
mdefine_line|#define A_FIFO_SEQ 0xFD
DECL|macro|M_NEXT_FIFO_DIR
mdefine_line|#define M_NEXT_FIFO_DIR 0x01
DECL|macro|M_NEXT_FIFO_NUM
mdefine_line|#define M_NEXT_FIFO_NUM 0x3E
DECL|macro|M1_NEXT_FIFO_NUM
mdefine_line|#define M1_NEXT_FIFO_NUM 0x02
DECL|macro|M2_NEXT_FIFO_NUM
mdefine_line|#define M2_NEXT_FIFO_NUM 0x04
DECL|macro|M3_NEXT_FIFO_NUM
mdefine_line|#define M3_NEXT_FIFO_NUM 0x06
DECL|macro|M4_NEXT_FIFO_NUM
mdefine_line|#define M4_NEXT_FIFO_NUM 0x08
DECL|macro|M5_NEXT_FIFO_NUM
mdefine_line|#define M5_NEXT_FIFO_NUM 0x0A
DECL|macro|M6_NEXT_FIFO_NUM
mdefine_line|#define M6_NEXT_FIFO_NUM 0x0C
DECL|macro|M7_NEXT_FIFO_NUM
mdefine_line|#define M7_NEXT_FIFO_NUM 0x0E
DECL|macro|M8_NEXT_FIFO_NUM
mdefine_line|#define M8_NEXT_FIFO_NUM 0x10
DECL|macro|M9_NEXT_FIFO_NUM
mdefine_line|#define M9_NEXT_FIFO_NUM 0x12
DECL|macro|M10_NEXT_FIFO_NUM
mdefine_line|#define M10_NEXT_FIFO_NUM 0x14
DECL|macro|M11_NEXT_FIFO_NUM
mdefine_line|#define M11_NEXT_FIFO_NUM 0x16
DECL|macro|M12_NEXT_FIFO_NUM
mdefine_line|#define M12_NEXT_FIFO_NUM 0x18
DECL|macro|M13_NEXT_FIFO_NUM
mdefine_line|#define M13_NEXT_FIFO_NUM 0x1A
DECL|macro|M14_NEXT_FIFO_NUM
mdefine_line|#define M14_NEXT_FIFO_NUM 0x1C
DECL|macro|M15_NEXT_FIFO_NUM
mdefine_line|#define M15_NEXT_FIFO_NUM 0x1E
DECL|macro|M16_NEXT_FIFO_NUM
mdefine_line|#define M16_NEXT_FIFO_NUM 0x20
DECL|macro|M17_NEXT_FIFO_NUM
mdefine_line|#define M17_NEXT_FIFO_NUM 0x22
DECL|macro|M18_NEXT_FIFO_NUM
mdefine_line|#define M18_NEXT_FIFO_NUM 0x24
DECL|macro|M19_NEXT_FIFO_NUM
mdefine_line|#define M19_NEXT_FIFO_NUM 0x26
DECL|macro|M20_NEXT_FIFO_NUM
mdefine_line|#define M20_NEXT_FIFO_NUM 0x28
DECL|macro|M21_NEXT_FIFO_NUM
mdefine_line|#define M21_NEXT_FIFO_NUM 0x2A
DECL|macro|M22_NEXT_FIFO_NUM
mdefine_line|#define M22_NEXT_FIFO_NUM 0x2C
DECL|macro|M23_NEXT_FIFO_NUM
mdefine_line|#define M23_NEXT_FIFO_NUM 0x2E
DECL|macro|M24_NEXT_FIFO_NUM
mdefine_line|#define M24_NEXT_FIFO_NUM 0x30
DECL|macro|M25_NEXT_FIFO_NUM
mdefine_line|#define M25_NEXT_FIFO_NUM 0x32
DECL|macro|M26_NEXT_FIFO_NUM
mdefine_line|#define M26_NEXT_FIFO_NUM 0x34
DECL|macro|M27_NEXT_FIFO_NUM
mdefine_line|#define M27_NEXT_FIFO_NUM 0x36
DECL|macro|M28_NEXT_FIFO_NUM
mdefine_line|#define M28_NEXT_FIFO_NUM 0x38
DECL|macro|M29_NEXT_FIFO_NUM
mdefine_line|#define M29_NEXT_FIFO_NUM 0x3A
DECL|macro|M30_NEXT_FIFO_NUM
mdefine_line|#define M30_NEXT_FIFO_NUM 0x3C
DECL|macro|M31_NEXT_FIFO_NUM
mdefine_line|#define M31_NEXT_FIFO_NUM 0x3E
DECL|macro|M_SEQ_END
mdefine_line|#define M_SEQ_END 0x40
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_next_fifo_dir
id|REGWORD
id|v_next_fifo_dir
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_next_fifo_num
id|REGWORD
id|v_next_fifo_num
suffix:colon
l_int|5
suffix:semicolon
DECL|member|v_seq_end
id|REGWORD
id|v_seq_end
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_59
id|REGWORD
id|reserved_59
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|bit_a_fifo_seq
)brace
id|bit_a_fifo_seq
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_fifo_seq
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_fifo_seq
id|bit
suffix:semicolon
)brace
id|reg_a_fifo_seq
suffix:semicolon
singleline_comment|// register and bitmap access
singleline_comment|//___________________________________________________________________________________//
singleline_comment|//                                                                                   //
DECL|macro|A_IRQ_MSK
mdefine_line|#define A_IRQ_MSK 0xFF
DECL|macro|M_IRQ
mdefine_line|#define M_IRQ 0x01
DECL|macro|M_BERT_EN
mdefine_line|#define M_BERT_EN 0x02
DECL|macro|M_MIX_IRQ
mdefine_line|#define M_MIX_IRQ 0x04
r_typedef
r_struct
singleline_comment|// bitmap construction
(brace
DECL|member|v_irq
id|REGWORD
id|v_irq
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_bert_en
id|REGWORD
id|v_bert_en
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v_mix_irq
id|REGWORD
id|v_mix_irq
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_60
id|REGWORD
id|reserved_60
suffix:colon
l_int|5
suffix:semicolon
DECL|typedef|bit_a_irq_msk
)brace
id|bit_a_irq_msk
suffix:semicolon
DECL|member|reg
DECL|member|bit
DECL|typedef|reg_a_irq_msk
r_typedef
r_union
(brace
id|REGWORD
id|reg
suffix:semicolon
id|bit_a_irq_msk
id|bit
suffix:semicolon
)brace
id|reg_a_irq_msk
suffix:semicolon
singleline_comment|// register and bitmap access
macro_line|#endif
singleline_comment|//______________________________ end of register list _______________________________//
singleline_comment|//                                                                                   //
eof
