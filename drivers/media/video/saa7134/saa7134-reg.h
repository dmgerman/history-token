multiline_comment|/*&n; * $Id: saa7134-reg.h,v 1.2 2004/09/15 16:15:24 kraxel Exp $&n; *&n; * philips saa7134 registers&n; */
multiline_comment|/* ------------------------------------------------------------------ */
multiline_comment|/*&n; * PCI ID&squot;s&n; */
macro_line|#ifndef PCI_DEVICE_ID_PHILIPS_SAA7130
DECL|macro|PCI_DEVICE_ID_PHILIPS_SAA7130
macro_line|# define PCI_DEVICE_ID_PHILIPS_SAA7130 0x7130
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_PHILIPS_SAA7133
DECL|macro|PCI_DEVICE_ID_PHILIPS_SAA7133
macro_line|# define PCI_DEVICE_ID_PHILIPS_SAA7133 0x7133
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_PHILIPS_SAA7134
DECL|macro|PCI_DEVICE_ID_PHILIPS_SAA7134
macro_line|# define PCI_DEVICE_ID_PHILIPS_SAA7134 0x7134
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_PHILIPS_SAA7135
DECL|macro|PCI_DEVICE_ID_PHILIPS_SAA7135
macro_line|# define PCI_DEVICE_ID_PHILIPS_SAA7135 0x7135
macro_line|#endif
multiline_comment|/* ------------------------------------------------------------------ */
multiline_comment|/*&n; *  registers -- 32 bit&n; */
multiline_comment|/* DMA channels, n = 0 ... 6 */
DECL|macro|SAA7134_RS_BA1
mdefine_line|#define SAA7134_RS_BA1(n)&t;&t;&t;((0x200 &gt;&gt; 2) + 4*n)
DECL|macro|SAA7134_RS_BA2
mdefine_line|#define SAA7134_RS_BA2(n)&t;       &t;&t;((0x204 &gt;&gt; 2) + 4*n)
DECL|macro|SAA7134_RS_PITCH
mdefine_line|#define SAA7134_RS_PITCH(n)&t;&t;&t;((0x208 &gt;&gt; 2) + 4*n)
DECL|macro|SAA7134_RS_CONTROL
mdefine_line|#define SAA7134_RS_CONTROL(n)&t;&t;&t;((0x20c &gt;&gt; 2) + 4*n)
DECL|macro|SAA7134_RS_CONTROL_WSWAP
mdefine_line|#define   SAA7134_RS_CONTROL_WSWAP&t;&t;(0x01 &lt;&lt; 25)
DECL|macro|SAA7134_RS_CONTROL_BSWAP
mdefine_line|#define   SAA7134_RS_CONTROL_BSWAP&t;&t;(0x01 &lt;&lt; 24)
DECL|macro|SAA7134_RS_CONTROL_BURST_2
mdefine_line|#define   SAA7134_RS_CONTROL_BURST_2&t;&t;(0x01 &lt;&lt; 21)
DECL|macro|SAA7134_RS_CONTROL_BURST_4
mdefine_line|#define   SAA7134_RS_CONTROL_BURST_4&t;&t;(0x02 &lt;&lt; 21)
DECL|macro|SAA7134_RS_CONTROL_BURST_8
mdefine_line|#define   SAA7134_RS_CONTROL_BURST_8&t;&t;(0x03 &lt;&lt; 21)
DECL|macro|SAA7134_RS_CONTROL_BURST_16
mdefine_line|#define   SAA7134_RS_CONTROL_BURST_16&t;&t;(0x04 &lt;&lt; 21)
DECL|macro|SAA7134_RS_CONTROL_BURST_32
mdefine_line|#define   SAA7134_RS_CONTROL_BURST_32&t;&t;(0x05 &lt;&lt; 21)
DECL|macro|SAA7134_RS_CONTROL_BURST_64
mdefine_line|#define   SAA7134_RS_CONTROL_BURST_64&t;&t;(0x06 &lt;&lt; 21)
DECL|macro|SAA7134_RS_CONTROL_BURST_MAX
mdefine_line|#define   SAA7134_RS_CONTROL_BURST_MAX&t;&t;(0x07 &lt;&lt; 21)
DECL|macro|SAA7134_RS_CONTROL_ME
mdefine_line|#define   SAA7134_RS_CONTROL_ME&t;&t;&t;(0x01 &lt;&lt; 20)
DECL|macro|SAA7134_FIFO_SIZE
mdefine_line|#define SAA7134_FIFO_SIZE                       (0x2a0 &gt;&gt; 2)
DECL|macro|SAA7134_THRESHOULD
mdefine_line|#define SAA7134_THRESHOULD                      (0x2a4 &gt;&gt; 2)
multiline_comment|/* main control */
DECL|macro|SAA7134_MAIN_CTRL
mdefine_line|#define SAA7134_MAIN_CTRL                       (0x2a8 &gt;&gt; 2)
DECL|macro|SAA7134_MAIN_CTRL_VPLLE
mdefine_line|#define   SAA7134_MAIN_CTRL_VPLLE&t;       &t;(1 &lt;&lt; 15)
DECL|macro|SAA7134_MAIN_CTRL_APLLE
mdefine_line|#define   SAA7134_MAIN_CTRL_APLLE&t;       &t;(1 &lt;&lt; 14)
DECL|macro|SAA7134_MAIN_CTRL_EXOSC
mdefine_line|#define   SAA7134_MAIN_CTRL_EXOSC&t;       &t;(1 &lt;&lt; 13)
DECL|macro|SAA7134_MAIN_CTRL_EVFE1
mdefine_line|#define   SAA7134_MAIN_CTRL_EVFE1&t;       &t;(1 &lt;&lt; 12)
DECL|macro|SAA7134_MAIN_CTRL_EVFE2
mdefine_line|#define   SAA7134_MAIN_CTRL_EVFE2&t;       &t;(1 &lt;&lt; 11)
DECL|macro|SAA7134_MAIN_CTRL_ESFE
mdefine_line|#define   SAA7134_MAIN_CTRL_ESFE&t;       &t;(1 &lt;&lt; 10)
DECL|macro|SAA7134_MAIN_CTRL_EBADC
mdefine_line|#define   SAA7134_MAIN_CTRL_EBADC&t;       &t;(1 &lt;&lt; 9)
DECL|macro|SAA7134_MAIN_CTRL_EBDAC
mdefine_line|#define   SAA7134_MAIN_CTRL_EBDAC&t;       &t;(1 &lt;&lt; 8)
DECL|macro|SAA7134_MAIN_CTRL_TE6
mdefine_line|#define   SAA7134_MAIN_CTRL_TE6&t;&t;&t;(1 &lt;&lt; 6)
DECL|macro|SAA7134_MAIN_CTRL_TE5
mdefine_line|#define   SAA7134_MAIN_CTRL_TE5&t;&t;&t;(1 &lt;&lt; 5)
DECL|macro|SAA7134_MAIN_CTRL_TE4
mdefine_line|#define   SAA7134_MAIN_CTRL_TE4&t;&t;&t;(1 &lt;&lt; 4)
DECL|macro|SAA7134_MAIN_CTRL_TE3
mdefine_line|#define   SAA7134_MAIN_CTRL_TE3&t;&t;&t;(1 &lt;&lt; 3)
DECL|macro|SAA7134_MAIN_CTRL_TE2
mdefine_line|#define   SAA7134_MAIN_CTRL_TE2&t;&t;&t;(1 &lt;&lt; 2)
DECL|macro|SAA7134_MAIN_CTRL_TE1
mdefine_line|#define   SAA7134_MAIN_CTRL_TE1&t;&t;&t;(1 &lt;&lt; 1)
DECL|macro|SAA7134_MAIN_CTRL_TE0
mdefine_line|#define   SAA7134_MAIN_CTRL_TE0&t;&t;&t;(1 &lt;&lt; 0)
multiline_comment|/* DMA status */
DECL|macro|SAA7134_DMA_STATUS
mdefine_line|#define SAA7134_DMA_STATUS                      (0x2ac &gt;&gt; 2)
multiline_comment|/* audio / video status */
DECL|macro|SAA7134_AV_STATUS
mdefine_line|#define SAA7134_AV_STATUS&t;&t;&t;(0x2c0 &gt;&gt; 2)
DECL|macro|SAA7134_AV_STATUS_STEREO
mdefine_line|#define   SAA7134_AV_STATUS_STEREO&t;&t;(1 &lt;&lt; 17)
DECL|macro|SAA7134_AV_STATUS_DUAL
mdefine_line|#define   SAA7134_AV_STATUS_DUAL                (1 &lt;&lt; 16)
DECL|macro|SAA7134_AV_STATUS_PILOT
mdefine_line|#define   SAA7134_AV_STATUS_PILOT               (1 &lt;&lt; 15)
DECL|macro|SAA7134_AV_STATUS_SMB
mdefine_line|#define   SAA7134_AV_STATUS_SMB                 (1 &lt;&lt; 14)
DECL|macro|SAA7134_AV_STATUS_DMB
mdefine_line|#define   SAA7134_AV_STATUS_DMB                 (1 &lt;&lt; 13)
DECL|macro|SAA7134_AV_STATUS_VDSP
mdefine_line|#define   SAA7134_AV_STATUS_VDSP                (1 &lt;&lt; 12)
DECL|macro|SAA7134_AV_STATUS_IIC_STATUS
mdefine_line|#define   SAA7134_AV_STATUS_IIC_STATUS          (3 &lt;&lt; 10)
DECL|macro|SAA7134_AV_STATUS_MVM
mdefine_line|#define   SAA7134_AV_STATUS_MVM                 (7 &lt;&lt; 7)
DECL|macro|SAA7134_AV_STATUS_FIDT
mdefine_line|#define   SAA7134_AV_STATUS_FIDT                (1 &lt;&lt; 6)
DECL|macro|SAA7134_AV_STATUS_INTL
mdefine_line|#define   SAA7134_AV_STATUS_INTL                (1 &lt;&lt; 5)
DECL|macro|SAA7134_AV_STATUS_RDCAP
mdefine_line|#define   SAA7134_AV_STATUS_RDCAP               (1 &lt;&lt; 4)
DECL|macro|SAA7134_AV_STATUS_PWR_ON
mdefine_line|#define   SAA7134_AV_STATUS_PWR_ON              (1 &lt;&lt; 3)
DECL|macro|SAA7134_AV_STATUS_LOAD_ERR
mdefine_line|#define   SAA7134_AV_STATUS_LOAD_ERR            (1 &lt;&lt; 2)
DECL|macro|SAA7134_AV_STATUS_TRIG_ERR
mdefine_line|#define   SAA7134_AV_STATUS_TRIG_ERR            (1 &lt;&lt; 1)
DECL|macro|SAA7134_AV_STATUS_CONF_ERR
mdefine_line|#define   SAA7134_AV_STATUS_CONF_ERR            (1 &lt;&lt; 0)
multiline_comment|/* interrupt */
DECL|macro|SAA7134_IRQ1
mdefine_line|#define SAA7134_IRQ1                            (0x2c4 &gt;&gt; 2)
DECL|macro|SAA7134_IRQ1_INTE_RA3_1
mdefine_line|#define   SAA7134_IRQ1_INTE_RA3_1               (1 &lt;&lt; 25)
DECL|macro|SAA7134_IRQ1_INTE_RA3_0
mdefine_line|#define   SAA7134_IRQ1_INTE_RA3_0               (1 &lt;&lt; 24)
DECL|macro|SAA7134_IRQ1_INTE_RA2_3
mdefine_line|#define   SAA7134_IRQ1_INTE_RA2_3               (1 &lt;&lt; 19)
DECL|macro|SAA7134_IRQ1_INTE_RA2_2
mdefine_line|#define   SAA7134_IRQ1_INTE_RA2_2               (1 &lt;&lt; 18)
DECL|macro|SAA7134_IRQ1_INTE_RA2_1
mdefine_line|#define   SAA7134_IRQ1_INTE_RA2_1               (1 &lt;&lt; 17)
DECL|macro|SAA7134_IRQ1_INTE_RA2_0
mdefine_line|#define   SAA7134_IRQ1_INTE_RA2_0               (1 &lt;&lt; 16)
DECL|macro|SAA7134_IRQ1_INTE_RA1_3
mdefine_line|#define   SAA7134_IRQ1_INTE_RA1_3               (1 &lt;&lt; 11)
DECL|macro|SAA7134_IRQ1_INTE_RA1_2
mdefine_line|#define   SAA7134_IRQ1_INTE_RA1_2               (1 &lt;&lt; 10)
DECL|macro|SAA7134_IRQ1_INTE_RA1_1
mdefine_line|#define   SAA7134_IRQ1_INTE_RA1_1               (1 &lt;&lt;  9)
DECL|macro|SAA7134_IRQ1_INTE_RA1_0
mdefine_line|#define   SAA7134_IRQ1_INTE_RA1_0               (1 &lt;&lt;  8)
DECL|macro|SAA7134_IRQ1_INTE_RA0_7
mdefine_line|#define   SAA7134_IRQ1_INTE_RA0_7               (1 &lt;&lt;  7)
DECL|macro|SAA7134_IRQ1_INTE_RA0_6
mdefine_line|#define   SAA7134_IRQ1_INTE_RA0_6               (1 &lt;&lt;  6)
DECL|macro|SAA7134_IRQ1_INTE_RA0_5
mdefine_line|#define   SAA7134_IRQ1_INTE_RA0_5               (1 &lt;&lt;  5)
DECL|macro|SAA7134_IRQ1_INTE_RA0_4
mdefine_line|#define   SAA7134_IRQ1_INTE_RA0_4               (1 &lt;&lt;  4)
DECL|macro|SAA7134_IRQ1_INTE_RA0_3
mdefine_line|#define   SAA7134_IRQ1_INTE_RA0_3               (1 &lt;&lt;  3)
DECL|macro|SAA7134_IRQ1_INTE_RA0_2
mdefine_line|#define   SAA7134_IRQ1_INTE_RA0_2               (1 &lt;&lt;  2)
DECL|macro|SAA7134_IRQ1_INTE_RA0_1
mdefine_line|#define   SAA7134_IRQ1_INTE_RA0_1               (1 &lt;&lt;  1)
DECL|macro|SAA7134_IRQ1_INTE_RA0_0
mdefine_line|#define   SAA7134_IRQ1_INTE_RA0_0               (1 &lt;&lt;  0)
DECL|macro|SAA7134_IRQ2
mdefine_line|#define SAA7134_IRQ2                            (0x2c8 &gt;&gt; 2)
DECL|macro|SAA7134_IRQ2_INTE_GPIO23A
mdefine_line|#define   SAA7134_IRQ2_INTE_GPIO23A             (1 &lt;&lt; 17)
DECL|macro|SAA7134_IRQ2_INTE_GPIO23
mdefine_line|#define   SAA7134_IRQ2_INTE_GPIO23              (1 &lt;&lt; 16)
DECL|macro|SAA7134_IRQ2_INTE_GPIO22A
mdefine_line|#define   SAA7134_IRQ2_INTE_GPIO22A             (1 &lt;&lt; 15)
DECL|macro|SAA7134_IRQ2_INTE_GPIO22
mdefine_line|#define   SAA7134_IRQ2_INTE_GPIO22              (1 &lt;&lt; 14)
DECL|macro|SAA7134_IRQ2_INTE_GPIO18A
mdefine_line|#define   SAA7134_IRQ2_INTE_GPIO18A             (1 &lt;&lt; 13)
DECL|macro|SAA7134_IRQ2_INTE_GPIO18
mdefine_line|#define   SAA7134_IRQ2_INTE_GPIO18              (1 &lt;&lt; 12)
DECL|macro|SAA7134_IRQ2_INTE_GPIO16
mdefine_line|#define   SAA7134_IRQ2_INTE_GPIO16              (1 &lt;&lt; 11) /* not certain */
DECL|macro|SAA7134_IRQ2_INTE_SC2
mdefine_line|#define   SAA7134_IRQ2_INTE_SC2                 (1 &lt;&lt; 10)
DECL|macro|SAA7134_IRQ2_INTE_SC1
mdefine_line|#define   SAA7134_IRQ2_INTE_SC1                 (1 &lt;&lt;  9)
DECL|macro|SAA7134_IRQ2_INTE_SC0
mdefine_line|#define   SAA7134_IRQ2_INTE_SC0                 (1 &lt;&lt;  8)
DECL|macro|SAA7134_IRQ2_INTE_DEC5
mdefine_line|#define   SAA7134_IRQ2_INTE_DEC5                (1 &lt;&lt;  7)
DECL|macro|SAA7134_IRQ2_INTE_DEC4
mdefine_line|#define   SAA7134_IRQ2_INTE_DEC4                (1 &lt;&lt;  6)
DECL|macro|SAA7134_IRQ2_INTE_DEC3
mdefine_line|#define   SAA7134_IRQ2_INTE_DEC3                (1 &lt;&lt;  5)
DECL|macro|SAA7134_IRQ2_INTE_DEC2
mdefine_line|#define   SAA7134_IRQ2_INTE_DEC2                (1 &lt;&lt;  4)
DECL|macro|SAA7134_IRQ2_INTE_DEC1
mdefine_line|#define   SAA7134_IRQ2_INTE_DEC1                (1 &lt;&lt;  3)
DECL|macro|SAA7134_IRQ2_INTE_DEC0
mdefine_line|#define   SAA7134_IRQ2_INTE_DEC0                (1 &lt;&lt;  2)
DECL|macro|SAA7134_IRQ2_INTE_PE
mdefine_line|#define   SAA7134_IRQ2_INTE_PE                  (1 &lt;&lt;  1)
DECL|macro|SAA7134_IRQ2_INTE_AR
mdefine_line|#define   SAA7134_IRQ2_INTE_AR                  (1 &lt;&lt;  0)
DECL|macro|SAA7134_IRQ_REPORT
mdefine_line|#define SAA7134_IRQ_REPORT                      (0x2cc &gt;&gt; 2)
DECL|macro|SAA7134_IRQ_REPORT_GPIO23
mdefine_line|#define   SAA7134_IRQ_REPORT_GPIO23             (1 &lt;&lt; 17)
DECL|macro|SAA7134_IRQ_REPORT_GPIO22
mdefine_line|#define   SAA7134_IRQ_REPORT_GPIO22             (1 &lt;&lt; 16)
DECL|macro|SAA7134_IRQ_REPORT_GPIO18
mdefine_line|#define   SAA7134_IRQ_REPORT_GPIO18             (1 &lt;&lt; 15)
DECL|macro|SAA7134_IRQ_REPORT_GPIO16
mdefine_line|#define   SAA7134_IRQ_REPORT_GPIO16             (1 &lt;&lt; 14) /* not certain */
DECL|macro|SAA7134_IRQ_REPORT_LOAD_ERR
mdefine_line|#define   SAA7134_IRQ_REPORT_LOAD_ERR           (1 &lt;&lt; 13)
DECL|macro|SAA7134_IRQ_REPORT_CONF_ERR
mdefine_line|#define   SAA7134_IRQ_REPORT_CONF_ERR           (1 &lt;&lt; 12)
DECL|macro|SAA7134_IRQ_REPORT_TRIG_ERR
mdefine_line|#define   SAA7134_IRQ_REPORT_TRIG_ERR           (1 &lt;&lt; 11)
DECL|macro|SAA7134_IRQ_REPORT_MMC
mdefine_line|#define   SAA7134_IRQ_REPORT_MMC                (1 &lt;&lt; 10)
DECL|macro|SAA7134_IRQ_REPORT_FIDT
mdefine_line|#define   SAA7134_IRQ_REPORT_FIDT               (1 &lt;&lt;  9)
DECL|macro|SAA7134_IRQ_REPORT_INTL
mdefine_line|#define   SAA7134_IRQ_REPORT_INTL               (1 &lt;&lt;  8)
DECL|macro|SAA7134_IRQ_REPORT_RDCAP
mdefine_line|#define   SAA7134_IRQ_REPORT_RDCAP              (1 &lt;&lt;  7)
DECL|macro|SAA7134_IRQ_REPORT_PWR_ON
mdefine_line|#define   SAA7134_IRQ_REPORT_PWR_ON             (1 &lt;&lt;  6)
DECL|macro|SAA7134_IRQ_REPORT_PE
mdefine_line|#define   SAA7134_IRQ_REPORT_PE                 (1 &lt;&lt;  5)
DECL|macro|SAA7134_IRQ_REPORT_AR
mdefine_line|#define   SAA7134_IRQ_REPORT_AR                 (1 &lt;&lt;  4)
DECL|macro|SAA7134_IRQ_REPORT_DONE_RA3
mdefine_line|#define   SAA7134_IRQ_REPORT_DONE_RA3           (1 &lt;&lt;  3)
DECL|macro|SAA7134_IRQ_REPORT_DONE_RA2
mdefine_line|#define   SAA7134_IRQ_REPORT_DONE_RA2           (1 &lt;&lt;  2)
DECL|macro|SAA7134_IRQ_REPORT_DONE_RA1
mdefine_line|#define   SAA7134_IRQ_REPORT_DONE_RA1           (1 &lt;&lt;  1)
DECL|macro|SAA7134_IRQ_REPORT_DONE_RA0
mdefine_line|#define   SAA7134_IRQ_REPORT_DONE_RA0           (1 &lt;&lt;  0)
DECL|macro|SAA7134_IRQ_STATUS
mdefine_line|#define SAA7134_IRQ_STATUS                      (0x2d0 &gt;&gt; 2)
multiline_comment|/* ------------------------------------------------------------------ */
multiline_comment|/*&n; *  registers -- 8 bit&n; */
multiline_comment|/* video decoder */
DECL|macro|SAA7134_INCR_DELAY
mdefine_line|#define SAA7134_INCR_DELAY                      0x101
DECL|macro|SAA7134_ANALOG_IN_CTRL1
mdefine_line|#define SAA7134_ANALOG_IN_CTRL1                 0x102
DECL|macro|SAA7134_ANALOG_IN_CTRL2
mdefine_line|#define SAA7134_ANALOG_IN_CTRL2                 0x103
DECL|macro|SAA7134_ANALOG_IN_CTRL3
mdefine_line|#define SAA7134_ANALOG_IN_CTRL3                 0x104
DECL|macro|SAA7134_ANALOG_IN_CTRL4
mdefine_line|#define SAA7134_ANALOG_IN_CTRL4                 0x105
DECL|macro|SAA7134_HSYNC_START
mdefine_line|#define SAA7134_HSYNC_START                     0x106
DECL|macro|SAA7134_HSYNC_STOP
mdefine_line|#define SAA7134_HSYNC_STOP                      0x107
DECL|macro|SAA7134_SYNC_CTRL
mdefine_line|#define SAA7134_SYNC_CTRL                       0x108
DECL|macro|SAA7134_LUMA_CTRL
mdefine_line|#define SAA7134_LUMA_CTRL                       0x109
DECL|macro|SAA7134_DEC_LUMA_BRIGHT
mdefine_line|#define SAA7134_DEC_LUMA_BRIGHT                 0x10a
DECL|macro|SAA7134_DEC_LUMA_CONTRAST
mdefine_line|#define SAA7134_DEC_LUMA_CONTRAST               0x10b
DECL|macro|SAA7134_DEC_CHROMA_SATURATION
mdefine_line|#define SAA7134_DEC_CHROMA_SATURATION           0x10c
DECL|macro|SAA7134_DEC_CHROMA_HUE
mdefine_line|#define SAA7134_DEC_CHROMA_HUE                  0x10d
DECL|macro|SAA7134_CHROMA_CTRL1
mdefine_line|#define SAA7134_CHROMA_CTRL1                    0x10e
DECL|macro|SAA7134_CHROMA_GAIN
mdefine_line|#define SAA7134_CHROMA_GAIN                     0x10f
DECL|macro|SAA7134_CHROMA_CTRL2
mdefine_line|#define SAA7134_CHROMA_CTRL2                    0x110
DECL|macro|SAA7134_MODE_DELAY_CTRL
mdefine_line|#define SAA7134_MODE_DELAY_CTRL                 0x111
DECL|macro|SAA7134_ANALOG_ADC
mdefine_line|#define SAA7134_ANALOG_ADC                      0x114
DECL|macro|SAA7134_VGATE_START
mdefine_line|#define SAA7134_VGATE_START                     0x115
DECL|macro|SAA7134_VGATE_STOP
mdefine_line|#define SAA7134_VGATE_STOP                      0x116
DECL|macro|SAA7134_MISC_VGATE_MSB
mdefine_line|#define SAA7134_MISC_VGATE_MSB                  0x117
DECL|macro|SAA7134_RAW_DATA_GAIN
mdefine_line|#define SAA7134_RAW_DATA_GAIN                   0x118
DECL|macro|SAA7134_RAW_DATA_OFFSET
mdefine_line|#define SAA7134_RAW_DATA_OFFSET                 0x119
DECL|macro|SAA7134_STATUS_VIDEO1
mdefine_line|#define SAA7134_STATUS_VIDEO1                   0x11e
DECL|macro|SAA7134_STATUS_VIDEO2
mdefine_line|#define SAA7134_STATUS_VIDEO2                   0x11f
multiline_comment|/* video scaler */
DECL|macro|SAA7134_SOURCE_TIMING1
mdefine_line|#define SAA7134_SOURCE_TIMING1                  0x000
DECL|macro|SAA7134_SOURCE_TIMING2
mdefine_line|#define SAA7134_SOURCE_TIMING2                  0x001
DECL|macro|SAA7134_REGION_ENABLE
mdefine_line|#define SAA7134_REGION_ENABLE                   0x004
DECL|macro|SAA7134_SCALER_STATUS0
mdefine_line|#define SAA7134_SCALER_STATUS0                  0x006
DECL|macro|SAA7134_SCALER_STATUS1
mdefine_line|#define SAA7134_SCALER_STATUS1                  0x007
DECL|macro|SAA7134_START_GREEN
mdefine_line|#define SAA7134_START_GREEN                     0x00c
DECL|macro|SAA7134_START_BLUE
mdefine_line|#define SAA7134_START_BLUE                      0x00d
DECL|macro|SAA7134_START_RED
mdefine_line|#define SAA7134_START_RED                       0x00e
DECL|macro|SAA7134_GREEN_PATH
mdefine_line|#define SAA7134_GREEN_PATH(x)                   (0x010 +x)
DECL|macro|SAA7134_BLUE_PATH
mdefine_line|#define SAA7134_BLUE_PATH(x)                    (0x020 +x)
DECL|macro|SAA7134_RED_PATH
mdefine_line|#define SAA7134_RED_PATH(x)                     (0x030 +x)
DECL|macro|TASK_A
mdefine_line|#define TASK_A                                  0x040
DECL|macro|TASK_B
mdefine_line|#define TASK_B                                  0x080
DECL|macro|SAA7134_TASK_CONDITIONS
mdefine_line|#define SAA7134_TASK_CONDITIONS(t)              (0x000 +t)
DECL|macro|SAA7134_FIELD_HANDLING
mdefine_line|#define SAA7134_FIELD_HANDLING(t)               (0x001 +t)
DECL|macro|SAA7134_DATA_PATH
mdefine_line|#define SAA7134_DATA_PATH(t)                    (0x002 +t)
DECL|macro|SAA7134_VBI_H_START1
mdefine_line|#define SAA7134_VBI_H_START1(t)                 (0x004 +t)
DECL|macro|SAA7134_VBI_H_START2
mdefine_line|#define SAA7134_VBI_H_START2(t)                 (0x005 +t)
DECL|macro|SAA7134_VBI_H_STOP1
mdefine_line|#define SAA7134_VBI_H_STOP1(t)                  (0x006 +t)
DECL|macro|SAA7134_VBI_H_STOP2
mdefine_line|#define SAA7134_VBI_H_STOP2(t)                  (0x007 +t)
DECL|macro|SAA7134_VBI_V_START1
mdefine_line|#define SAA7134_VBI_V_START1(t)                 (0x008 +t)
DECL|macro|SAA7134_VBI_V_START2
mdefine_line|#define SAA7134_VBI_V_START2(t)                 (0x009 +t)
DECL|macro|SAA7134_VBI_V_STOP1
mdefine_line|#define SAA7134_VBI_V_STOP1(t)                  (0x00a +t)
DECL|macro|SAA7134_VBI_V_STOP2
mdefine_line|#define SAA7134_VBI_V_STOP2(t)                  (0x00b +t)
DECL|macro|SAA7134_VBI_H_LEN1
mdefine_line|#define SAA7134_VBI_H_LEN1(t)                   (0x00c +t)
DECL|macro|SAA7134_VBI_H_LEN2
mdefine_line|#define SAA7134_VBI_H_LEN2(t)                   (0x00d +t)
DECL|macro|SAA7134_VBI_V_LEN1
mdefine_line|#define SAA7134_VBI_V_LEN1(t)                   (0x00e +t)
DECL|macro|SAA7134_VBI_V_LEN2
mdefine_line|#define SAA7134_VBI_V_LEN2(t)                   (0x00f +t)
DECL|macro|SAA7134_VIDEO_H_START1
mdefine_line|#define SAA7134_VIDEO_H_START1(t)               (0x014 +t)
DECL|macro|SAA7134_VIDEO_H_START2
mdefine_line|#define SAA7134_VIDEO_H_START2(t)               (0x015 +t)
DECL|macro|SAA7134_VIDEO_H_STOP1
mdefine_line|#define SAA7134_VIDEO_H_STOP1(t)                (0x016 +t)
DECL|macro|SAA7134_VIDEO_H_STOP2
mdefine_line|#define SAA7134_VIDEO_H_STOP2(t)                (0x017 +t)
DECL|macro|SAA7134_VIDEO_V_START1
mdefine_line|#define SAA7134_VIDEO_V_START1(t)               (0x018 +t)
DECL|macro|SAA7134_VIDEO_V_START2
mdefine_line|#define SAA7134_VIDEO_V_START2(t)               (0x019 +t)
DECL|macro|SAA7134_VIDEO_V_STOP1
mdefine_line|#define SAA7134_VIDEO_V_STOP1(t)                (0x01a +t)
DECL|macro|SAA7134_VIDEO_V_STOP2
mdefine_line|#define SAA7134_VIDEO_V_STOP2(t)                (0x01b +t)
DECL|macro|SAA7134_VIDEO_PIXELS1
mdefine_line|#define SAA7134_VIDEO_PIXELS1(t)                (0x01c +t)
DECL|macro|SAA7134_VIDEO_PIXELS2
mdefine_line|#define SAA7134_VIDEO_PIXELS2(t)                (0x01d +t)
DECL|macro|SAA7134_VIDEO_LINES1
mdefine_line|#define SAA7134_VIDEO_LINES1(t)                 (0x01e +t)
DECL|macro|SAA7134_VIDEO_LINES2
mdefine_line|#define SAA7134_VIDEO_LINES2(t)                 (0x01f +t)
DECL|macro|SAA7134_H_PRESCALE
mdefine_line|#define SAA7134_H_PRESCALE(t)                   (0x020 +t)
DECL|macro|SAA7134_ACC_LENGTH
mdefine_line|#define SAA7134_ACC_LENGTH(t)                   (0x021 +t)
DECL|macro|SAA7134_LEVEL_CTRL
mdefine_line|#define SAA7134_LEVEL_CTRL(t)                   (0x022 +t)
DECL|macro|SAA7134_FIR_PREFILTER_CTRL
mdefine_line|#define SAA7134_FIR_PREFILTER_CTRL(t)           (0x023 +t)
DECL|macro|SAA7134_LUMA_BRIGHT
mdefine_line|#define SAA7134_LUMA_BRIGHT(t)                  (0x024 +t)
DECL|macro|SAA7134_LUMA_CONTRAST
mdefine_line|#define SAA7134_LUMA_CONTRAST(t)                (0x025 +t)
DECL|macro|SAA7134_CHROMA_SATURATION
mdefine_line|#define SAA7134_CHROMA_SATURATION(t)            (0x026 +t)
DECL|macro|SAA7134_VBI_H_SCALE_INC1
mdefine_line|#define SAA7134_VBI_H_SCALE_INC1(t)             (0x028 +t)
DECL|macro|SAA7134_VBI_H_SCALE_INC2
mdefine_line|#define SAA7134_VBI_H_SCALE_INC2(t)             (0x029 +t)
DECL|macro|SAA7134_VBI_PHASE_OFFSET_LUMA
mdefine_line|#define SAA7134_VBI_PHASE_OFFSET_LUMA(t)        (0x02a +t)
DECL|macro|SAA7134_VBI_PHASE_OFFSET_CHROMA
mdefine_line|#define SAA7134_VBI_PHASE_OFFSET_CHROMA(t)      (0x02b +t)
DECL|macro|SAA7134_H_SCALE_INC1
mdefine_line|#define SAA7134_H_SCALE_INC1(t)                 (0x02c +t)
DECL|macro|SAA7134_H_SCALE_INC2
mdefine_line|#define SAA7134_H_SCALE_INC2(t)                 (0x02d +t)
DECL|macro|SAA7134_H_PHASE_OFF_LUMA
mdefine_line|#define SAA7134_H_PHASE_OFF_LUMA(t)             (0x02e +t)
DECL|macro|SAA7134_H_PHASE_OFF_CHROMA
mdefine_line|#define SAA7134_H_PHASE_OFF_CHROMA(t)           (0x02f +t)
DECL|macro|SAA7134_V_SCALE_RATIO1
mdefine_line|#define SAA7134_V_SCALE_RATIO1(t)               (0x030 +t)
DECL|macro|SAA7134_V_SCALE_RATIO2
mdefine_line|#define SAA7134_V_SCALE_RATIO2(t)               (0x031 +t)
DECL|macro|SAA7134_V_FILTER
mdefine_line|#define SAA7134_V_FILTER(t)                     (0x032 +t)
DECL|macro|SAA7134_V_PHASE_OFFSET0
mdefine_line|#define SAA7134_V_PHASE_OFFSET0(t)              (0x034 +t)
DECL|macro|SAA7134_V_PHASE_OFFSET1
mdefine_line|#define SAA7134_V_PHASE_OFFSET1(t)              (0x035 +t)
DECL|macro|SAA7134_V_PHASE_OFFSET2
mdefine_line|#define SAA7134_V_PHASE_OFFSET2(t)              (0x036 +t)
DECL|macro|SAA7134_V_PHASE_OFFSET3
mdefine_line|#define SAA7134_V_PHASE_OFFSET3(t)              (0x037 +t)
multiline_comment|/* clipping &amp; dma */
DECL|macro|SAA7134_OFMT_VIDEO_A
mdefine_line|#define SAA7134_OFMT_VIDEO_A                    0x300
DECL|macro|SAA7134_OFMT_DATA_A
mdefine_line|#define SAA7134_OFMT_DATA_A                     0x301
DECL|macro|SAA7134_OFMT_VIDEO_B
mdefine_line|#define SAA7134_OFMT_VIDEO_B                    0x302
DECL|macro|SAA7134_OFMT_DATA_B
mdefine_line|#define SAA7134_OFMT_DATA_B                     0x303
DECL|macro|SAA7134_ALPHA_NOCLIP
mdefine_line|#define SAA7134_ALPHA_NOCLIP                    0x304
DECL|macro|SAA7134_ALPHA_CLIP
mdefine_line|#define SAA7134_ALPHA_CLIP                      0x305
DECL|macro|SAA7134_UV_PIXEL
mdefine_line|#define SAA7134_UV_PIXEL                        0x308
DECL|macro|SAA7134_CLIP_RED
mdefine_line|#define SAA7134_CLIP_RED                        0x309
DECL|macro|SAA7134_CLIP_GREEN
mdefine_line|#define SAA7134_CLIP_GREEN                      0x30a
DECL|macro|SAA7134_CLIP_BLUE
mdefine_line|#define SAA7134_CLIP_BLUE                       0x30b
multiline_comment|/* i2c bus */
DECL|macro|SAA7134_I2C_ATTR_STATUS
mdefine_line|#define SAA7134_I2C_ATTR_STATUS                 0x180
DECL|macro|SAA7134_I2C_DATA
mdefine_line|#define SAA7134_I2C_DATA                        0x181
DECL|macro|SAA7134_I2C_CLOCK_SELECT
mdefine_line|#define SAA7134_I2C_CLOCK_SELECT                0x182
DECL|macro|SAA7134_I2C_TIMER
mdefine_line|#define SAA7134_I2C_TIMER                       0x183
multiline_comment|/* audio */
DECL|macro|SAA7134_NICAM_ADD_DATA1
mdefine_line|#define SAA7134_NICAM_ADD_DATA1                 0x140
DECL|macro|SAA7134_NICAM_ADD_DATA2
mdefine_line|#define SAA7134_NICAM_ADD_DATA2                 0x141
DECL|macro|SAA7134_NICAM_STATUS
mdefine_line|#define SAA7134_NICAM_STATUS                    0x142
DECL|macro|SAA7134_AUDIO_STATUS
mdefine_line|#define SAA7134_AUDIO_STATUS                    0x143
DECL|macro|SAA7134_NICAM_ERROR_COUNT
mdefine_line|#define SAA7134_NICAM_ERROR_COUNT               0x144
DECL|macro|SAA7134_IDENT_SIF
mdefine_line|#define SAA7134_IDENT_SIF                       0x145
DECL|macro|SAA7134_LEVEL_READOUT1
mdefine_line|#define SAA7134_LEVEL_READOUT1                  0x146
DECL|macro|SAA7134_LEVEL_READOUT2
mdefine_line|#define SAA7134_LEVEL_READOUT2                  0x147
DECL|macro|SAA7134_NICAM_ERROR_LOW
mdefine_line|#define SAA7134_NICAM_ERROR_LOW                 0x148
DECL|macro|SAA7134_NICAM_ERROR_HIGH
mdefine_line|#define SAA7134_NICAM_ERROR_HIGH                0x149
DECL|macro|SAA7134_DCXO_IDENT_CTRL
mdefine_line|#define SAA7134_DCXO_IDENT_CTRL                 0x14a
DECL|macro|SAA7134_DEMODULATOR
mdefine_line|#define SAA7134_DEMODULATOR                     0x14b
DECL|macro|SAA7134_AGC_GAIN_SELECT
mdefine_line|#define SAA7134_AGC_GAIN_SELECT                 0x14c
DECL|macro|SAA7134_CARRIER1_FREQ0
mdefine_line|#define SAA7134_CARRIER1_FREQ0                  0x150
DECL|macro|SAA7134_CARRIER1_FREQ1
mdefine_line|#define SAA7134_CARRIER1_FREQ1                  0x151
DECL|macro|SAA7134_CARRIER1_FREQ2
mdefine_line|#define SAA7134_CARRIER1_FREQ2                  0x152
DECL|macro|SAA7134_CARRIER2_FREQ0
mdefine_line|#define SAA7134_CARRIER2_FREQ0                  0x154
DECL|macro|SAA7134_CARRIER2_FREQ1
mdefine_line|#define SAA7134_CARRIER2_FREQ1                  0x155
DECL|macro|SAA7134_CARRIER2_FREQ2
mdefine_line|#define SAA7134_CARRIER2_FREQ2                  0x156
DECL|macro|SAA7134_NUM_SAMPLES0
mdefine_line|#define SAA7134_NUM_SAMPLES0                    0x158
DECL|macro|SAA7134_NUM_SAMPLES1
mdefine_line|#define SAA7134_NUM_SAMPLES1                    0x159
DECL|macro|SAA7134_NUM_SAMPLES2
mdefine_line|#define SAA7134_NUM_SAMPLES2                    0x15a
DECL|macro|SAA7134_AUDIO_FORMAT_CTRL
mdefine_line|#define SAA7134_AUDIO_FORMAT_CTRL               0x15b
DECL|macro|SAA7134_MONITOR_SELECT
mdefine_line|#define SAA7134_MONITOR_SELECT                  0x160
DECL|macro|SAA7134_FM_DEEMPHASIS
mdefine_line|#define SAA7134_FM_DEEMPHASIS                   0x161
DECL|macro|SAA7134_FM_DEMATRIX
mdefine_line|#define SAA7134_FM_DEMATRIX                     0x162
DECL|macro|SAA7134_CHANNEL1_LEVEL
mdefine_line|#define SAA7134_CHANNEL1_LEVEL                  0x163
DECL|macro|SAA7134_CHANNEL2_LEVEL
mdefine_line|#define SAA7134_CHANNEL2_LEVEL                  0x164
DECL|macro|SAA7134_NICAM_CONFIG
mdefine_line|#define SAA7134_NICAM_CONFIG                    0x165
DECL|macro|SAA7134_NICAM_LEVEL_ADJUST
mdefine_line|#define SAA7134_NICAM_LEVEL_ADJUST              0x166
DECL|macro|SAA7134_STEREO_DAC_OUTPUT_SELECT
mdefine_line|#define SAA7134_STEREO_DAC_OUTPUT_SELECT        0x167
DECL|macro|SAA7134_I2S_OUTPUT_FORMAT
mdefine_line|#define SAA7134_I2S_OUTPUT_FORMAT               0x168
DECL|macro|SAA7134_I2S_OUTPUT_SELECT
mdefine_line|#define SAA7134_I2S_OUTPUT_SELECT               0x169
DECL|macro|SAA7134_I2S_OUTPUT_LEVEL
mdefine_line|#define SAA7134_I2S_OUTPUT_LEVEL                0x16a
DECL|macro|SAA7134_DSP_OUTPUT_SELECT
mdefine_line|#define SAA7134_DSP_OUTPUT_SELECT               0x16b
DECL|macro|SAA7134_AUDIO_MUTE_CTRL
mdefine_line|#define SAA7134_AUDIO_MUTE_CTRL                 0x16c
DECL|macro|SAA7134_SIF_SAMPLE_FREQ
mdefine_line|#define SAA7134_SIF_SAMPLE_FREQ                 0x16d
DECL|macro|SAA7134_ANALOG_IO_SELECT
mdefine_line|#define SAA7134_ANALOG_IO_SELECT                0x16e
DECL|macro|SAA7134_AUDIO_CLOCK0
mdefine_line|#define SAA7134_AUDIO_CLOCK0                    0x170
DECL|macro|SAA7134_AUDIO_CLOCK1
mdefine_line|#define SAA7134_AUDIO_CLOCK1                    0x171
DECL|macro|SAA7134_AUDIO_CLOCK2
mdefine_line|#define SAA7134_AUDIO_CLOCK2                    0x172
DECL|macro|SAA7134_AUDIO_PLL_CTRL
mdefine_line|#define SAA7134_AUDIO_PLL_CTRL                  0x173
DECL|macro|SAA7134_AUDIO_CLOCKS_PER_FIELD0
mdefine_line|#define SAA7134_AUDIO_CLOCKS_PER_FIELD0         0x174
DECL|macro|SAA7134_AUDIO_CLOCKS_PER_FIELD1
mdefine_line|#define SAA7134_AUDIO_CLOCKS_PER_FIELD1         0x175
DECL|macro|SAA7134_AUDIO_CLOCKS_PER_FIELD2
mdefine_line|#define SAA7134_AUDIO_CLOCKS_PER_FIELD2         0x176
multiline_comment|/* video port output */
DECL|macro|SAA7134_VIDEO_PORT_CTRL0
mdefine_line|#define SAA7134_VIDEO_PORT_CTRL0                0x190
DECL|macro|SAA7134_VIDEO_PORT_CTRL1
mdefine_line|#define SAA7134_VIDEO_PORT_CTRL1                0x191
DECL|macro|SAA7134_VIDEO_PORT_CTRL2
mdefine_line|#define SAA7134_VIDEO_PORT_CTRL2                0x192
DECL|macro|SAA7134_VIDEO_PORT_CTRL3
mdefine_line|#define SAA7134_VIDEO_PORT_CTRL3                0x193
DECL|macro|SAA7134_VIDEO_PORT_CTRL4
mdefine_line|#define SAA7134_VIDEO_PORT_CTRL4                0x194
DECL|macro|SAA7134_VIDEO_PORT_CTRL5
mdefine_line|#define SAA7134_VIDEO_PORT_CTRL5                0x195
DECL|macro|SAA7134_VIDEO_PORT_CTRL6
mdefine_line|#define SAA7134_VIDEO_PORT_CTRL6                0x196
DECL|macro|SAA7134_VIDEO_PORT_CTRL7
mdefine_line|#define SAA7134_VIDEO_PORT_CTRL7                0x197
DECL|macro|SAA7134_VIDEO_PORT_CTRL8
mdefine_line|#define SAA7134_VIDEO_PORT_CTRL8                0x198
multiline_comment|/* transport stream interface */
DECL|macro|SAA7134_TS_PARALLEL
mdefine_line|#define SAA7134_TS_PARALLEL                     0x1a0
DECL|macro|SAA7134_TS_PARALLEL_SERIAL
mdefine_line|#define SAA7134_TS_PARALLEL_SERIAL              0x1a1
DECL|macro|SAA7134_TS_SERIAL0
mdefine_line|#define SAA7134_TS_SERIAL0                      0x1a2
DECL|macro|SAA7134_TS_SERIAL1
mdefine_line|#define SAA7134_TS_SERIAL1                      0x1a3
DECL|macro|SAA7134_TS_DMA0
mdefine_line|#define SAA7134_TS_DMA0                         0x1a4
DECL|macro|SAA7134_TS_DMA1
mdefine_line|#define SAA7134_TS_DMA1                         0x1a5
DECL|macro|SAA7134_TS_DMA2
mdefine_line|#define SAA7134_TS_DMA2                         0x1a6
multiline_comment|/* GPIO Controls */
DECL|macro|SAA7134_GPIO_GPRESCAN
mdefine_line|#define SAA7134_GPIO_GPRESCAN                   0x80
DECL|macro|SAA7134_GPIO_27_25
mdefine_line|#define SAA7134_GPIO_27_25                      0x0E
DECL|macro|SAA7134_GPIO_GPMODE0
mdefine_line|#define SAA7134_GPIO_GPMODE0                    0x1B0
DECL|macro|SAA7134_GPIO_GPMODE1
mdefine_line|#define SAA7134_GPIO_GPMODE1                    0x1B1
DECL|macro|SAA7134_GPIO_GPMODE2
mdefine_line|#define SAA7134_GPIO_GPMODE2                    0x1B2
DECL|macro|SAA7134_GPIO_GPMODE3
mdefine_line|#define SAA7134_GPIO_GPMODE3                    0x1B3
DECL|macro|SAA7134_GPIO_GPSTATUS0
mdefine_line|#define SAA7134_GPIO_GPSTATUS0                  0x1B4
DECL|macro|SAA7134_GPIO_GPSTATUS1
mdefine_line|#define SAA7134_GPIO_GPSTATUS1                  0x1B5
DECL|macro|SAA7134_GPIO_GPSTATUS2
mdefine_line|#define SAA7134_GPIO_GPSTATUS2                  0x1B6
DECL|macro|SAA7134_GPIO_GPSTATUS3
mdefine_line|#define SAA7134_GPIO_GPSTATUS3                  0x1B7
multiline_comment|/* I2S output */
DECL|macro|SAA7134_I2S_AUDIO_OUTPUT
mdefine_line|#define SAA7134_I2S_AUDIO_OUTPUT                0x1c0
multiline_comment|/* test modes */
DECL|macro|SAA7134_SPECIAL_MODE
mdefine_line|#define SAA7134_SPECIAL_MODE                    0x1d0
multiline_comment|/* audio -- saa7133 + saa7135 only */
DECL|macro|SAA7135_DSP_RWSTATE
mdefine_line|#define SAA7135_DSP_RWSTATE                     0x580
DECL|macro|SAA7135_DSP_RWSTATE_ERR
mdefine_line|#define SAA7135_DSP_RWSTATE_ERR                 (1 &lt;&lt; 3)
DECL|macro|SAA7135_DSP_RWSTATE_IDA
mdefine_line|#define SAA7135_DSP_RWSTATE_IDA                 (1 &lt;&lt; 2)
DECL|macro|SAA7135_DSP_RWSTATE_RDB
mdefine_line|#define SAA7135_DSP_RWSTATE_RDB                 (1 &lt;&lt; 1)
DECL|macro|SAA7135_DSP_RWSTATE_WRR
mdefine_line|#define SAA7135_DSP_RWSTATE_WRR                 (1 &lt;&lt; 0)
multiline_comment|/* ------------------------------------------------------------------ */
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
