macro_line|#ifndef HPT366_H
DECL|macro|HPT366_H
mdefine_line|#define HPT366_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
DECL|macro|DISPLAY_HPT366_TIMINGS
mdefine_line|#define DISPLAY_HPT366_TIMINGS
multiline_comment|/* various tuning parameters */
DECL|macro|HPT_RESET_STATE_ENGINE
mdefine_line|#define HPT_RESET_STATE_ENGINE
DECL|macro|HPT_DELAY_INTERRUPT
macro_line|#undef HPT_DELAY_INTERRUPT
DECL|macro|HPT_SERIALIZE_IO
macro_line|#undef HPT_SERIALIZE_IO
DECL|variable|quirk_drives
r_const
r_char
op_star
id|quirk_drives
(braket
)braket
op_assign
(brace
l_string|&quot;QUANTUM FIREBALLlct08 08&quot;
comma
l_string|&quot;QUANTUM FIREBALLP KA6.4&quot;
comma
l_string|&quot;QUANTUM FIREBALLP LM20.4&quot;
comma
l_string|&quot;QUANTUM FIREBALLP LM20.5&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|bad_ata100_5
r_const
r_char
op_star
id|bad_ata100_5
(braket
)braket
op_assign
(brace
l_string|&quot;IBM-DTLA-307075&quot;
comma
l_string|&quot;IBM-DTLA-307060&quot;
comma
l_string|&quot;IBM-DTLA-307045&quot;
comma
l_string|&quot;IBM-DTLA-307030&quot;
comma
l_string|&quot;IBM-DTLA-307020&quot;
comma
l_string|&quot;IBM-DTLA-307015&quot;
comma
l_string|&quot;IBM-DTLA-305040&quot;
comma
l_string|&quot;IBM-DTLA-305030&quot;
comma
l_string|&quot;IBM-DTLA-305020&quot;
comma
l_string|&quot;IC35L010AVER07-0&quot;
comma
l_string|&quot;IC35L020AVER07-0&quot;
comma
l_string|&quot;IC35L030AVER07-0&quot;
comma
l_string|&quot;IC35L040AVER07-0&quot;
comma
l_string|&quot;IC35L060AVER07-0&quot;
comma
l_string|&quot;WDC AC310200R&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|bad_ata66_4
r_const
r_char
op_star
id|bad_ata66_4
(braket
)braket
op_assign
(brace
l_string|&quot;IBM-DTLA-307075&quot;
comma
l_string|&quot;IBM-DTLA-307060&quot;
comma
l_string|&quot;IBM-DTLA-307045&quot;
comma
l_string|&quot;IBM-DTLA-307030&quot;
comma
l_string|&quot;IBM-DTLA-307020&quot;
comma
l_string|&quot;IBM-DTLA-307015&quot;
comma
l_string|&quot;IBM-DTLA-305040&quot;
comma
l_string|&quot;IBM-DTLA-305030&quot;
comma
l_string|&quot;IBM-DTLA-305020&quot;
comma
l_string|&quot;IC35L010AVER07-0&quot;
comma
l_string|&quot;IC35L020AVER07-0&quot;
comma
l_string|&quot;IC35L030AVER07-0&quot;
comma
l_string|&quot;IC35L040AVER07-0&quot;
comma
l_string|&quot;IC35L060AVER07-0&quot;
comma
l_string|&quot;WDC AC310200R&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|bad_ata66_3
r_const
r_char
op_star
id|bad_ata66_3
(braket
)braket
op_assign
(brace
l_string|&quot;WDC AC310200R&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|bad_ata33
r_const
r_char
op_star
id|bad_ata33
(braket
)braket
op_assign
(brace
l_string|&quot;Maxtor 92720U8&quot;
comma
l_string|&quot;Maxtor 92040U6&quot;
comma
l_string|&quot;Maxtor 91360U4&quot;
comma
l_string|&quot;Maxtor 91020U3&quot;
comma
l_string|&quot;Maxtor 90845U3&quot;
comma
l_string|&quot;Maxtor 90650U2&quot;
comma
l_string|&quot;Maxtor 91360D8&quot;
comma
l_string|&quot;Maxtor 91190D7&quot;
comma
l_string|&quot;Maxtor 91020D6&quot;
comma
l_string|&quot;Maxtor 90845D5&quot;
comma
l_string|&quot;Maxtor 90680D4&quot;
comma
l_string|&quot;Maxtor 90510D3&quot;
comma
l_string|&quot;Maxtor 90340D2&quot;
comma
l_string|&quot;Maxtor 91152D8&quot;
comma
l_string|&quot;Maxtor 91008D7&quot;
comma
l_string|&quot;Maxtor 90845D6&quot;
comma
l_string|&quot;Maxtor 90840D6&quot;
comma
l_string|&quot;Maxtor 90720D5&quot;
comma
l_string|&quot;Maxtor 90648D5&quot;
comma
l_string|&quot;Maxtor 90576D4&quot;
comma
l_string|&quot;Maxtor 90510D4&quot;
comma
l_string|&quot;Maxtor 90432D3&quot;
comma
l_string|&quot;Maxtor 90288D2&quot;
comma
l_string|&quot;Maxtor 90256D2&quot;
comma
l_string|&quot;Maxtor 91000D8&quot;
comma
l_string|&quot;Maxtor 90910D8&quot;
comma
l_string|&quot;Maxtor 90875D7&quot;
comma
l_string|&quot;Maxtor 90840D7&quot;
comma
l_string|&quot;Maxtor 90750D6&quot;
comma
l_string|&quot;Maxtor 90625D5&quot;
comma
l_string|&quot;Maxtor 90500D4&quot;
comma
l_string|&quot;Maxtor 91728D8&quot;
comma
l_string|&quot;Maxtor 91512D7&quot;
comma
l_string|&quot;Maxtor 91303D6&quot;
comma
l_string|&quot;Maxtor 91080D5&quot;
comma
l_string|&quot;Maxtor 90845D4&quot;
comma
l_string|&quot;Maxtor 90680D4&quot;
comma
l_string|&quot;Maxtor 90648D3&quot;
comma
l_string|&quot;Maxtor 90432D2&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|struct|chipset_bus_clock_list_entry
r_struct
id|chipset_bus_clock_list_entry
(brace
DECL|member|xfer_speed
id|byte
id|xfer_speed
suffix:semicolon
DECL|member|chipset_settings
r_int
r_int
id|chipset_settings
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* key for bus clock timings&n; * bit&n; * 0:3    data_high_time. inactive time of DIOW_/DIOR_ for PIO and MW&n; *        DMA. cycles = value + 1&n; * 4:8    data_low_time. active time of DIOW_/DIOR_ for PIO and MW&n; *        DMA. cycles = value + 1&n; * 9:12   cmd_high_time. inactive time of DIOW_/DIOR_ during task file&n; *        register access.&n; * 13:17  cmd_low_time. active time of DIOW_/DIOR_ during task file&n; *        register access.&n; * 18:21  udma_cycle_time. clock freq and clock cycles for UDMA xfer.&n; *        during task file register access.&n; * 22:24  pre_high_time. time to initialize 1st cycle for PIO and MW DMA&n; *        xfer.&n; * 25:27  cmd_pre_high_time. time to initialize 1st PIO cycle for task&n; *        register access.&n; * 28     UDMA enable&n; * 29     DMA enable&n; * 30     PIO_MST enable. if set, the chip is in bus master mode during&n; *        PIO.&n; * 31     FIFO enable.&n; */
DECL|variable|forty_base_hpt366
r_struct
id|chipset_bus_clock_list_entry
id|forty_base_hpt366
(braket
)braket
op_assign
(brace
(brace
id|XFER_UDMA_4
comma
l_int|0x900fd943
)brace
comma
(brace
id|XFER_UDMA_3
comma
l_int|0x900ad943
)brace
comma
(brace
id|XFER_UDMA_2
comma
l_int|0x900bd943
)brace
comma
(brace
id|XFER_UDMA_1
comma
l_int|0x9008d943
)brace
comma
(brace
id|XFER_UDMA_0
comma
l_int|0x9008d943
)brace
comma
(brace
id|XFER_MW_DMA_2
comma
l_int|0xa008d943
)brace
comma
(brace
id|XFER_MW_DMA_1
comma
l_int|0xa010d955
)brace
comma
(brace
id|XFER_MW_DMA_0
comma
l_int|0xa010d9fc
)brace
comma
(brace
id|XFER_PIO_4
comma
l_int|0xc008d963
)brace
comma
(brace
id|XFER_PIO_3
comma
l_int|0xc010d974
)brace
comma
(brace
id|XFER_PIO_2
comma
l_int|0xc010d997
)brace
comma
(brace
id|XFER_PIO_1
comma
l_int|0xc010d9c7
)brace
comma
(brace
id|XFER_PIO_0
comma
l_int|0xc018d9d9
)brace
comma
(brace
l_int|0
comma
l_int|0x0120d9d9
)brace
)brace
suffix:semicolon
DECL|variable|thirty_three_base_hpt366
r_struct
id|chipset_bus_clock_list_entry
id|thirty_three_base_hpt366
(braket
)braket
op_assign
(brace
(brace
id|XFER_UDMA_4
comma
l_int|0x90c9a731
)brace
comma
(brace
id|XFER_UDMA_3
comma
l_int|0x90cfa731
)brace
comma
(brace
id|XFER_UDMA_2
comma
l_int|0x90caa731
)brace
comma
(brace
id|XFER_UDMA_1
comma
l_int|0x90cba731
)brace
comma
(brace
id|XFER_UDMA_0
comma
l_int|0x90c8a731
)brace
comma
(brace
id|XFER_MW_DMA_2
comma
l_int|0xa0c8a731
)brace
comma
(brace
id|XFER_MW_DMA_1
comma
l_int|0xa0c8a732
)brace
comma
multiline_comment|/* 0xa0c8a733 */
(brace
id|XFER_MW_DMA_0
comma
l_int|0xa0c8a797
)brace
comma
(brace
id|XFER_PIO_4
comma
l_int|0xc0c8a731
)brace
comma
(brace
id|XFER_PIO_3
comma
l_int|0xc0c8a742
)brace
comma
(brace
id|XFER_PIO_2
comma
l_int|0xc0d0a753
)brace
comma
(brace
id|XFER_PIO_1
comma
l_int|0xc0d0a7a3
)brace
comma
multiline_comment|/* 0xc0d0a793 */
(brace
id|XFER_PIO_0
comma
l_int|0xc0d0a7aa
)brace
comma
multiline_comment|/* 0xc0d0a7a7 */
(brace
l_int|0
comma
l_int|0x0120a7a7
)brace
)brace
suffix:semicolon
DECL|variable|twenty_five_base_hpt366
r_struct
id|chipset_bus_clock_list_entry
id|twenty_five_base_hpt366
(braket
)braket
op_assign
(brace
(brace
id|XFER_UDMA_4
comma
l_int|0x90c98521
)brace
comma
(brace
id|XFER_UDMA_3
comma
l_int|0x90cf8521
)brace
comma
(brace
id|XFER_UDMA_2
comma
l_int|0x90cf8521
)brace
comma
(brace
id|XFER_UDMA_1
comma
l_int|0x90cb8521
)brace
comma
(brace
id|XFER_UDMA_0
comma
l_int|0x90cb8521
)brace
comma
(brace
id|XFER_MW_DMA_2
comma
l_int|0xa0ca8521
)brace
comma
(brace
id|XFER_MW_DMA_1
comma
l_int|0xa0ca8532
)brace
comma
(brace
id|XFER_MW_DMA_0
comma
l_int|0xa0ca8575
)brace
comma
(brace
id|XFER_PIO_4
comma
l_int|0xc0ca8521
)brace
comma
(brace
id|XFER_PIO_3
comma
l_int|0xc0ca8532
)brace
comma
(brace
id|XFER_PIO_2
comma
l_int|0xc0ca8542
)brace
comma
(brace
id|XFER_PIO_1
comma
l_int|0xc0d08572
)brace
comma
(brace
id|XFER_PIO_0
comma
l_int|0xc0d08585
)brace
comma
(brace
l_int|0
comma
l_int|0x01208585
)brace
)brace
suffix:semicolon
multiline_comment|/* from highpoint documentation. these are old values */
DECL|variable|thirty_three_base_hpt370
r_struct
id|chipset_bus_clock_list_entry
id|thirty_three_base_hpt370
(braket
)braket
op_assign
(brace
multiline_comment|/*&t;{&t;XFER_UDMA_5,&t;0x1A85F442,&t;0x16454e31&t;}, */
(brace
id|XFER_UDMA_5
comma
l_int|0x16454e31
)brace
comma
(brace
id|XFER_UDMA_4
comma
l_int|0x16454e31
)brace
comma
(brace
id|XFER_UDMA_3
comma
l_int|0x166d4e31
)brace
comma
(brace
id|XFER_UDMA_2
comma
l_int|0x16494e31
)brace
comma
(brace
id|XFER_UDMA_1
comma
l_int|0x164d4e31
)brace
comma
(brace
id|XFER_UDMA_0
comma
l_int|0x16514e31
)brace
comma
(brace
id|XFER_MW_DMA_2
comma
l_int|0x26514e21
)brace
comma
(brace
id|XFER_MW_DMA_1
comma
l_int|0x26514e33
)brace
comma
(brace
id|XFER_MW_DMA_0
comma
l_int|0x26514e97
)brace
comma
(brace
id|XFER_PIO_4
comma
l_int|0x06514e21
)brace
comma
(brace
id|XFER_PIO_3
comma
l_int|0x06514e22
)brace
comma
(brace
id|XFER_PIO_2
comma
l_int|0x06514e33
)brace
comma
(brace
id|XFER_PIO_1
comma
l_int|0x06914e43
)brace
comma
(brace
id|XFER_PIO_0
comma
l_int|0x06914e57
)brace
comma
(brace
l_int|0
comma
l_int|0x06514e57
)brace
)brace
suffix:semicolon
DECL|variable|sixty_six_base_hpt370
r_struct
id|chipset_bus_clock_list_entry
id|sixty_six_base_hpt370
(braket
)braket
op_assign
(brace
(brace
id|XFER_UDMA_5
comma
l_int|0x14846231
)brace
comma
(brace
id|XFER_UDMA_4
comma
l_int|0x14886231
)brace
comma
(brace
id|XFER_UDMA_3
comma
l_int|0x148c6231
)brace
comma
(brace
id|XFER_UDMA_2
comma
l_int|0x148c6231
)brace
comma
(brace
id|XFER_UDMA_1
comma
l_int|0x14906231
)brace
comma
(brace
id|XFER_UDMA_0
comma
l_int|0x14986231
)brace
comma
(brace
id|XFER_MW_DMA_2
comma
l_int|0x26514e21
)brace
comma
(brace
id|XFER_MW_DMA_1
comma
l_int|0x26514e33
)brace
comma
(brace
id|XFER_MW_DMA_0
comma
l_int|0x26514e97
)brace
comma
(brace
id|XFER_PIO_4
comma
l_int|0x06514e21
)brace
comma
(brace
id|XFER_PIO_3
comma
l_int|0x06514e22
)brace
comma
(brace
id|XFER_PIO_2
comma
l_int|0x06514e33
)brace
comma
(brace
id|XFER_PIO_1
comma
l_int|0x06914e43
)brace
comma
(brace
id|XFER_PIO_0
comma
l_int|0x06914e57
)brace
comma
(brace
l_int|0
comma
l_int|0x06514e57
)brace
)brace
suffix:semicolon
multiline_comment|/* these are the current (4 sep 2001) timings from highpoint */
DECL|variable|thirty_three_base_hpt370a
r_struct
id|chipset_bus_clock_list_entry
id|thirty_three_base_hpt370a
(braket
)braket
op_assign
(brace
(brace
id|XFER_UDMA_5
comma
l_int|0x12446231
)brace
comma
(brace
id|XFER_UDMA_4
comma
l_int|0x12446231
)brace
comma
(brace
id|XFER_UDMA_3
comma
l_int|0x126c6231
)brace
comma
(brace
id|XFER_UDMA_2
comma
l_int|0x12486231
)brace
comma
(brace
id|XFER_UDMA_1
comma
l_int|0x124c6233
)brace
comma
(brace
id|XFER_UDMA_0
comma
l_int|0x12506297
)brace
comma
(brace
id|XFER_MW_DMA_2
comma
l_int|0x22406c31
)brace
comma
(brace
id|XFER_MW_DMA_1
comma
l_int|0x22406c33
)brace
comma
(brace
id|XFER_MW_DMA_0
comma
l_int|0x22406c97
)brace
comma
(brace
id|XFER_PIO_4
comma
l_int|0x06414e31
)brace
comma
(brace
id|XFER_PIO_3
comma
l_int|0x06414e42
)brace
comma
(brace
id|XFER_PIO_2
comma
l_int|0x06414e53
)brace
comma
(brace
id|XFER_PIO_1
comma
l_int|0x06814e93
)brace
comma
(brace
id|XFER_PIO_0
comma
l_int|0x06814ea7
)brace
comma
(brace
l_int|0
comma
l_int|0x06814ea7
)brace
)brace
suffix:semicolon
multiline_comment|/* 2x 33MHz timings */
DECL|variable|sixty_six_base_hpt370a
r_struct
id|chipset_bus_clock_list_entry
id|sixty_six_base_hpt370a
(braket
)braket
op_assign
(brace
(brace
id|XFER_UDMA_5
comma
l_int|0x1488e673
)brace
comma
(brace
id|XFER_UDMA_4
comma
l_int|0x1488e673
)brace
comma
(brace
id|XFER_UDMA_3
comma
l_int|0x1498e673
)brace
comma
(brace
id|XFER_UDMA_2
comma
l_int|0x1490e673
)brace
comma
(brace
id|XFER_UDMA_1
comma
l_int|0x1498e677
)brace
comma
(brace
id|XFER_UDMA_0
comma
l_int|0x14a0e73f
)brace
comma
(brace
id|XFER_MW_DMA_2
comma
l_int|0x2480fa73
)brace
comma
(brace
id|XFER_MW_DMA_1
comma
l_int|0x2480fa77
)brace
comma
(brace
id|XFER_MW_DMA_0
comma
l_int|0x2480fb3f
)brace
comma
(brace
id|XFER_PIO_4
comma
l_int|0x0c82be73
)brace
comma
(brace
id|XFER_PIO_3
comma
l_int|0x0c82be95
)brace
comma
(brace
id|XFER_PIO_2
comma
l_int|0x0c82beb7
)brace
comma
(brace
id|XFER_PIO_1
comma
l_int|0x0d02bf37
)brace
comma
(brace
id|XFER_PIO_0
comma
l_int|0x0d02bf5f
)brace
comma
(brace
l_int|0
comma
l_int|0x0d02bf5f
)brace
)brace
suffix:semicolon
DECL|variable|fifty_base_hpt370a
r_struct
id|chipset_bus_clock_list_entry
id|fifty_base_hpt370a
(braket
)braket
op_assign
(brace
(brace
id|XFER_UDMA_5
comma
l_int|0x12848242
)brace
comma
(brace
id|XFER_UDMA_4
comma
l_int|0x12ac8242
)brace
comma
(brace
id|XFER_UDMA_3
comma
l_int|0x128c8242
)brace
comma
(brace
id|XFER_UDMA_2
comma
l_int|0x120c8242
)brace
comma
(brace
id|XFER_UDMA_1
comma
l_int|0x12148254
)brace
comma
(brace
id|XFER_UDMA_0
comma
l_int|0x121882ea
)brace
comma
(brace
id|XFER_MW_DMA_2
comma
l_int|0x22808242
)brace
comma
(brace
id|XFER_MW_DMA_1
comma
l_int|0x22808254
)brace
comma
(brace
id|XFER_MW_DMA_0
comma
l_int|0x228082ea
)brace
comma
(brace
id|XFER_PIO_4
comma
l_int|0x0a81f442
)brace
comma
(brace
id|XFER_PIO_3
comma
l_int|0x0a81f443
)brace
comma
(brace
id|XFER_PIO_2
comma
l_int|0x0a81f454
)brace
comma
(brace
id|XFER_PIO_1
comma
l_int|0x0ac1f465
)brace
comma
(brace
id|XFER_PIO_0
comma
l_int|0x0ac1f48a
)brace
comma
(brace
l_int|0
comma
l_int|0x0ac1f48a
)brace
)brace
suffix:semicolon
DECL|variable|thirty_three_base_hpt372
r_struct
id|chipset_bus_clock_list_entry
id|thirty_three_base_hpt372
(braket
)braket
op_assign
(brace
(brace
id|XFER_UDMA_6
comma
l_int|0x1c81dc62
)brace
comma
(brace
id|XFER_UDMA_5
comma
l_int|0x1c6ddc62
)brace
comma
(brace
id|XFER_UDMA_4
comma
l_int|0x1c8ddc62
)brace
comma
(brace
id|XFER_UDMA_3
comma
l_int|0x1c8edc62
)brace
comma
multiline_comment|/* checkme */
(brace
id|XFER_UDMA_2
comma
l_int|0x1c91dc62
)brace
comma
(brace
id|XFER_UDMA_1
comma
l_int|0x1c9adc62
)brace
comma
multiline_comment|/* checkme */
(brace
id|XFER_UDMA_0
comma
l_int|0x1c82dc62
)brace
comma
multiline_comment|/* checkme */
(brace
id|XFER_MW_DMA_2
comma
l_int|0x2c829262
)brace
comma
(brace
id|XFER_MW_DMA_1
comma
l_int|0x2c829266
)brace
comma
multiline_comment|/* checkme */
(brace
id|XFER_MW_DMA_0
comma
l_int|0x2c82922e
)brace
comma
multiline_comment|/* checkme */
(brace
id|XFER_PIO_4
comma
l_int|0x0c829c62
)brace
comma
(brace
id|XFER_PIO_3
comma
l_int|0x0c829c84
)brace
comma
(brace
id|XFER_PIO_2
comma
l_int|0x0c829ca6
)brace
comma
(brace
id|XFER_PIO_1
comma
l_int|0x0d029d26
)brace
comma
(brace
id|XFER_PIO_0
comma
l_int|0x0d029d5e
)brace
comma
(brace
l_int|0
comma
l_int|0x0d029d5e
)brace
)brace
suffix:semicolon
DECL|variable|fifty_base_hpt372
r_struct
id|chipset_bus_clock_list_entry
id|fifty_base_hpt372
(braket
)braket
op_assign
(brace
(brace
id|XFER_UDMA_5
comma
l_int|0x12848242
)brace
comma
(brace
id|XFER_UDMA_4
comma
l_int|0x12ac8242
)brace
comma
(brace
id|XFER_UDMA_3
comma
l_int|0x128c8242
)brace
comma
(brace
id|XFER_UDMA_2
comma
l_int|0x120c8242
)brace
comma
(brace
id|XFER_UDMA_1
comma
l_int|0x12148254
)brace
comma
(brace
id|XFER_UDMA_0
comma
l_int|0x121882ea
)brace
comma
(brace
id|XFER_MW_DMA_2
comma
l_int|0x22808242
)brace
comma
(brace
id|XFER_MW_DMA_1
comma
l_int|0x22808254
)brace
comma
(brace
id|XFER_MW_DMA_0
comma
l_int|0x228082ea
)brace
comma
(brace
id|XFER_PIO_4
comma
l_int|0x0a81f442
)brace
comma
(brace
id|XFER_PIO_3
comma
l_int|0x0a81f443
)brace
comma
(brace
id|XFER_PIO_2
comma
l_int|0x0a81f454
)brace
comma
(brace
id|XFER_PIO_1
comma
l_int|0x0ac1f465
)brace
comma
(brace
id|XFER_PIO_0
comma
l_int|0x0ac1f48a
)brace
comma
(brace
l_int|0
comma
l_int|0x0a81f443
)brace
)brace
suffix:semicolon
DECL|variable|sixty_six_base_hpt372
r_struct
id|chipset_bus_clock_list_entry
id|sixty_six_base_hpt372
(braket
)braket
op_assign
(brace
(brace
id|XFER_UDMA_6
comma
l_int|0x1c869c62
)brace
comma
(brace
id|XFER_UDMA_5
comma
l_int|0x1cae9c62
)brace
comma
(brace
id|XFER_UDMA_4
comma
l_int|0x1c8a9c62
)brace
comma
(brace
id|XFER_UDMA_3
comma
l_int|0x1c8e9c62
)brace
comma
(brace
id|XFER_UDMA_2
comma
l_int|0x1c929c62
)brace
comma
(brace
id|XFER_UDMA_1
comma
l_int|0x1c9a9c62
)brace
comma
(brace
id|XFER_UDMA_0
comma
l_int|0x1c829c62
)brace
comma
(brace
id|XFER_MW_DMA_2
comma
l_int|0x2c829c62
)brace
comma
(brace
id|XFER_MW_DMA_1
comma
l_int|0x2c829c66
)brace
comma
(brace
id|XFER_MW_DMA_0
comma
l_int|0x2c829d2e
)brace
comma
(brace
id|XFER_PIO_4
comma
l_int|0x0c829c62
)brace
comma
(brace
id|XFER_PIO_3
comma
l_int|0x0c829c84
)brace
comma
(brace
id|XFER_PIO_2
comma
l_int|0x0c829ca6
)brace
comma
(brace
id|XFER_PIO_1
comma
l_int|0x0d029d26
)brace
comma
(brace
id|XFER_PIO_0
comma
l_int|0x0d029d5e
)brace
comma
(brace
l_int|0
comma
l_int|0x0d029d26
)brace
)brace
suffix:semicolon
DECL|variable|thirty_three_base_hpt374
r_struct
id|chipset_bus_clock_list_entry
id|thirty_three_base_hpt374
(braket
)braket
op_assign
(brace
(brace
id|XFER_UDMA_6
comma
l_int|0x12808242
)brace
comma
(brace
id|XFER_UDMA_5
comma
l_int|0x12848242
)brace
comma
(brace
id|XFER_UDMA_4
comma
l_int|0x12ac8242
)brace
comma
(brace
id|XFER_UDMA_3
comma
l_int|0x128c8242
)brace
comma
(brace
id|XFER_UDMA_2
comma
l_int|0x120c8242
)brace
comma
(brace
id|XFER_UDMA_1
comma
l_int|0x12148254
)brace
comma
(brace
id|XFER_UDMA_0
comma
l_int|0x121882ea
)brace
comma
(brace
id|XFER_MW_DMA_2
comma
l_int|0x22808242
)brace
comma
(brace
id|XFER_MW_DMA_1
comma
l_int|0x22808254
)brace
comma
(brace
id|XFER_MW_DMA_0
comma
l_int|0x228082ea
)brace
comma
(brace
id|XFER_PIO_4
comma
l_int|0x0a81f442
)brace
comma
(brace
id|XFER_PIO_3
comma
l_int|0x0a81f443
)brace
comma
(brace
id|XFER_PIO_2
comma
l_int|0x0a81f454
)brace
comma
(brace
id|XFER_PIO_1
comma
l_int|0x0ac1f465
)brace
comma
(brace
id|XFER_PIO_0
comma
l_int|0x0ac1f48a
)brace
comma
(brace
l_int|0
comma
l_int|0x06814e93
)brace
)brace
suffix:semicolon
macro_line|#if 0
r_struct
id|chipset_bus_clock_list_entry
id|fifty_base_hpt374
(braket
)braket
op_assign
(brace
(brace
id|XFER_UDMA_6
comma
)brace
comma
(brace
id|XFER_UDMA_5
comma
)brace
comma
(brace
id|XFER_UDMA_4
comma
)brace
comma
(brace
id|XFER_UDMA_3
comma
)brace
comma
(brace
id|XFER_UDMA_2
comma
)brace
comma
(brace
id|XFER_UDMA_1
comma
)brace
comma
(brace
id|XFER_UDMA_0
comma
)brace
comma
(brace
id|XFER_MW_DMA_2
comma
)brace
comma
(brace
id|XFER_MW_DMA_1
comma
)brace
comma
(brace
id|XFER_MW_DMA_0
comma
)brace
comma
(brace
id|XFER_PIO_4
comma
)brace
comma
(brace
id|XFER_PIO_3
comma
)brace
comma
(brace
id|XFER_PIO_2
comma
)brace
comma
(brace
id|XFER_PIO_1
comma
)brace
comma
(brace
id|XFER_PIO_0
comma
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
macro_line|#endif
macro_line|#if 0
r_struct
id|chipset_bus_clock_list_entry
id|sixty_six_base_hpt374
(braket
)braket
op_assign
(brace
(brace
id|XFER_UDMA_6
comma
l_int|0x12406231
)brace
comma
multiline_comment|/* checkme */
(brace
id|XFER_UDMA_5
comma
l_int|0x12446231
)brace
comma
l_int|0x14846231
(brace
id|XFER_UDMA_4
comma
l_int|0x16814ea7
)brace
comma
l_int|0x14886231
(brace
id|XFER_UDMA_3
comma
l_int|0x16814ea7
)brace
comma
l_int|0x148c6231
(brace
id|XFER_UDMA_2
comma
l_int|0x16814ea7
)brace
comma
l_int|0x148c6231
(brace
id|XFER_UDMA_1
comma
l_int|0x16814ea7
)brace
comma
l_int|0x14906231
(brace
id|XFER_UDMA_0
comma
l_int|0x16814ea7
)brace
comma
l_int|0x14986231
(brace
id|XFER_MW_DMA_2
comma
l_int|0x16814ea7
)brace
comma
l_int|0x26514e21
(brace
id|XFER_MW_DMA_1
comma
l_int|0x16814ea7
)brace
comma
l_int|0x26514e97
(brace
id|XFER_MW_DMA_0
comma
l_int|0x16814ea7
)brace
comma
l_int|0x26514e97
(brace
id|XFER_PIO_4
comma
l_int|0x06814ea7
)brace
comma
l_int|0x06514e21
(brace
id|XFER_PIO_3
comma
l_int|0x06814ea7
)brace
comma
l_int|0x06514e22
(brace
id|XFER_PIO_2
comma
l_int|0x06814ea7
)brace
comma
l_int|0x06514e33
(brace
id|XFER_PIO_1
comma
l_int|0x06814ea7
)brace
comma
l_int|0x06914e43
(brace
id|XFER_PIO_0
comma
l_int|0x06814ea7
)brace
comma
l_int|0x06914e57
(brace
l_int|0
comma
l_int|0x06814ea7
)brace
)brace
suffix:semicolon
macro_line|#endif
DECL|macro|HPT366_DEBUG_DRIVE_INFO
mdefine_line|#define HPT366_DEBUG_DRIVE_INFO&t;&t;0
DECL|macro|HPT374_ALLOW_ATA133_6
mdefine_line|#define HPT374_ALLOW_ATA133_6&t;&t;0
DECL|macro|HPT371_ALLOW_ATA133_6
mdefine_line|#define HPT371_ALLOW_ATA133_6&t;&t;0
DECL|macro|HPT302_ALLOW_ATA133_6
mdefine_line|#define HPT302_ALLOW_ATA133_6&t;&t;0
DECL|macro|HPT372_ALLOW_ATA133_6
mdefine_line|#define HPT372_ALLOW_ATA133_6&t;&t;1
DECL|macro|HPT370_ALLOW_ATA100_5
mdefine_line|#define HPT370_ALLOW_ATA100_5&t;&t;1
DECL|macro|HPT366_ALLOW_ATA66_4
mdefine_line|#define HPT366_ALLOW_ATA66_4&t;&t;1
DECL|macro|HPT366_ALLOW_ATA66_3
mdefine_line|#define HPT366_ALLOW_ATA66_3&t;&t;1
DECL|macro|HPT366_MAX_DEVS
mdefine_line|#define HPT366_MAX_DEVS&t;&t;&t;8
DECL|macro|F_LOW_PCI_33
mdefine_line|#define F_LOW_PCI_33      0x23
DECL|macro|F_LOW_PCI_40
mdefine_line|#define F_LOW_PCI_40      0x29
DECL|macro|F_LOW_PCI_50
mdefine_line|#define F_LOW_PCI_50      0x2d
DECL|macro|F_LOW_PCI_66
mdefine_line|#define F_LOW_PCI_66      0x42
macro_line|#if defined(DISPLAY_HPT366_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
DECL|variable|hpt366_proc
r_static
id|u8
id|hpt366_proc
suffix:semicolon
r_static
r_int
id|hpt366_get_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
DECL|variable|__initdata
r_static
id|ide_pci_host_proc_t
id|hpt366_procs
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|name
suffix:colon
l_string|&quot;hpt366&quot;
comma
id|set
suffix:colon
l_int|1
comma
id|get_info
suffix:colon
id|hpt366_get_info
comma
id|parent
suffix:colon
l_int|NULL
comma
)brace
comma
)brace
suffix:semicolon
macro_line|#endif  /* defined(DISPLAY_HPT366_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS) */
r_static
r_void
id|init_setup_hpt366
c_func
(paren
r_struct
id|pci_dev
op_star
comma
id|ide_pci_device_t
op_star
)paren
suffix:semicolon
r_static
r_void
id|init_setup_hpt37x
c_func
(paren
r_struct
id|pci_dev
op_star
comma
id|ide_pci_device_t
op_star
)paren
suffix:semicolon
r_static
r_void
id|init_setup_hpt374
c_func
(paren
r_struct
id|pci_dev
op_star
comma
id|ide_pci_device_t
op_star
)paren
suffix:semicolon
r_static
r_int
r_int
id|init_chipset_hpt366
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_const
r_char
op_star
)paren
suffix:semicolon
r_static
r_void
id|init_hwif_hpt366
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
r_static
r_void
id|init_dma_hpt366
c_func
(paren
id|ide_hwif_t
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|variable|__devinitdata
r_static
id|ide_pci_device_t
id|hpt366_chipsets
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
multiline_comment|/* 0 */
id|vendor
suffix:colon
id|PCI_VENDOR_ID_TTI
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_TTI_HPT366
comma
id|name
suffix:colon
l_string|&quot;HPT366&quot;
comma
id|init_setup
suffix:colon
id|init_setup_hpt366
comma
id|init_chipset
suffix:colon
id|init_chipset_hpt366
comma
id|init_iops
suffix:colon
l_int|NULL
comma
id|init_hwif
suffix:colon
id|init_hwif_hpt366
comma
id|init_dma
suffix:colon
id|init_dma_hpt366
comma
id|channels
suffix:colon
l_int|2
comma
id|autodma
suffix:colon
id|AUTODMA
comma
id|enablebits
suffix:colon
(brace
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
id|bootable
suffix:colon
id|OFF_BOARD
comma
id|extra
suffix:colon
l_int|240
)brace
comma
(brace
multiline_comment|/* 1 */
id|vendor
suffix:colon
id|PCI_VENDOR_ID_TTI
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_TTI_HPT372
comma
id|name
suffix:colon
l_string|&quot;HPT372A&quot;
comma
id|init_setup
suffix:colon
id|init_setup_hpt37x
comma
id|init_chipset
suffix:colon
id|init_chipset_hpt366
comma
id|init_iops
suffix:colon
l_int|NULL
comma
id|init_hwif
suffix:colon
id|init_hwif_hpt366
comma
id|init_dma
suffix:colon
id|init_dma_hpt366
comma
id|channels
suffix:colon
l_int|2
comma
id|autodma
suffix:colon
id|AUTODMA
comma
id|enablebits
suffix:colon
(brace
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
id|bootable
suffix:colon
id|OFF_BOARD
comma
id|extra
suffix:colon
l_int|0
)brace
comma
(brace
multiline_comment|/* 2 */
id|vendor
suffix:colon
id|PCI_VENDOR_ID_TTI
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_TTI_HPT302
comma
id|name
suffix:colon
l_string|&quot;HPT302&quot;
comma
id|init_setup
suffix:colon
id|init_setup_hpt37x
comma
id|init_chipset
suffix:colon
id|init_chipset_hpt366
comma
id|init_iops
suffix:colon
l_int|NULL
comma
id|init_hwif
suffix:colon
id|init_hwif_hpt366
comma
id|init_dma
suffix:colon
id|init_dma_hpt366
comma
id|channels
suffix:colon
l_int|2
comma
id|autodma
suffix:colon
id|AUTODMA
comma
id|enablebits
suffix:colon
(brace
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
id|bootable
suffix:colon
id|OFF_BOARD
comma
id|extra
suffix:colon
l_int|0
)brace
comma
(brace
multiline_comment|/* 3 */
id|vendor
suffix:colon
id|PCI_VENDOR_ID_TTI
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_TTI_HPT371
comma
id|name
suffix:colon
l_string|&quot;HPT371&quot;
comma
id|init_setup
suffix:colon
id|init_setup_hpt37x
comma
id|init_chipset
suffix:colon
id|init_chipset_hpt366
comma
id|init_iops
suffix:colon
l_int|NULL
comma
id|init_hwif
suffix:colon
id|init_hwif_hpt366
comma
id|init_dma
suffix:colon
id|init_dma_hpt366
comma
id|channels
suffix:colon
l_int|2
comma
id|autodma
suffix:colon
id|AUTODMA
comma
id|enablebits
suffix:colon
(brace
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
id|bootable
suffix:colon
id|OFF_BOARD
comma
id|extra
suffix:colon
l_int|0
)brace
comma
(brace
multiline_comment|/* 4 */
id|vendor
suffix:colon
id|PCI_VENDOR_ID_TTI
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_TTI_HPT374
comma
id|name
suffix:colon
l_string|&quot;HPT374&quot;
comma
id|init_setup
suffix:colon
id|init_setup_hpt374
comma
id|init_chipset
suffix:colon
id|init_chipset_hpt366
comma
id|init_iops
suffix:colon
l_int|NULL
comma
id|init_hwif
suffix:colon
id|init_hwif_hpt366
comma
id|init_dma
suffix:colon
id|init_dma_hpt366
comma
id|channels
suffix:colon
l_int|2
comma
multiline_comment|/* 4 */
id|autodma
suffix:colon
id|AUTODMA
comma
id|enablebits
suffix:colon
(brace
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
id|bootable
suffix:colon
id|OFF_BOARD
comma
id|extra
suffix:colon
l_int|0
)brace
comma
(brace
id|vendor
suffix:colon
l_int|0
comma
id|device
suffix:colon
l_int|0
comma
id|channels
suffix:colon
l_int|0
comma
id|bootable
suffix:colon
id|EOL
comma
)brace
)brace
suffix:semicolon
macro_line|#endif /* HPT366_H */
eof
