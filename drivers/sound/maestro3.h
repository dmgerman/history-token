multiline_comment|/*&n; *      ESS Technology allegro audio driver.&n; *&n; *      Copyright (C) 1992-2000  Don Kim (don.kim@esstech.com)&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *      Hacked for the maestro3 driver by zab&n; */
singleline_comment|// Allegro PCI configuration registers
DECL|macro|PCI_LEGACY_AUDIO_CTRL
mdefine_line|#define PCI_LEGACY_AUDIO_CTRL   0x40
DECL|macro|SOUND_BLASTER_ENABLE
mdefine_line|#define SOUND_BLASTER_ENABLE    0x00000001
DECL|macro|FM_SYNTHESIS_ENABLE
mdefine_line|#define FM_SYNTHESIS_ENABLE     0x00000002
DECL|macro|GAME_PORT_ENABLE
mdefine_line|#define GAME_PORT_ENABLE        0x00000004
DECL|macro|MPU401_IO_ENABLE
mdefine_line|#define MPU401_IO_ENABLE        0x00000008
DECL|macro|MPU401_IRQ_ENABLE
mdefine_line|#define MPU401_IRQ_ENABLE       0x00000010
DECL|macro|ALIAS_10BIT_IO
mdefine_line|#define ALIAS_10BIT_IO          0x00000020
DECL|macro|SB_DMA_MASK
mdefine_line|#define SB_DMA_MASK             0x000000C0
DECL|macro|SB_DMA_0
mdefine_line|#define SB_DMA_0                0x00000040
DECL|macro|SB_DMA_1
mdefine_line|#define SB_DMA_1                0x00000040
DECL|macro|SB_DMA_R
mdefine_line|#define SB_DMA_R                0x00000080
DECL|macro|SB_DMA_3
mdefine_line|#define SB_DMA_3                0x000000C0
DECL|macro|SB_IRQ_MASK
mdefine_line|#define SB_IRQ_MASK             0x00000700
DECL|macro|SB_IRQ_5
mdefine_line|#define SB_IRQ_5                0x00000000
DECL|macro|SB_IRQ_7
mdefine_line|#define SB_IRQ_7                0x00000100
DECL|macro|SB_IRQ_9
mdefine_line|#define SB_IRQ_9                0x00000200
DECL|macro|SB_IRQ_10
mdefine_line|#define SB_IRQ_10               0x00000300
DECL|macro|MIDI_IRQ_MASK
mdefine_line|#define MIDI_IRQ_MASK           0x00003800
DECL|macro|SERIAL_IRQ_ENABLE
mdefine_line|#define SERIAL_IRQ_ENABLE       0x00004000
DECL|macro|DISABLE_LEGACY
mdefine_line|#define DISABLE_LEGACY          0x00008000
DECL|macro|PCI_ALLEGRO_CONFIG
mdefine_line|#define PCI_ALLEGRO_CONFIG      0x50
DECL|macro|SB_ADDR_240
mdefine_line|#define SB_ADDR_240             0x00000004
DECL|macro|MPU_ADDR_MASK
mdefine_line|#define MPU_ADDR_MASK           0x00000018
DECL|macro|MPU_ADDR_330
mdefine_line|#define MPU_ADDR_330            0x00000000
DECL|macro|MPU_ADDR_300
mdefine_line|#define MPU_ADDR_300            0x00000008
DECL|macro|MPU_ADDR_320
mdefine_line|#define MPU_ADDR_320            0x00000010
DECL|macro|MPU_ADDR_340
mdefine_line|#define MPU_ADDR_340            0x00000018
DECL|macro|USE_PCI_TIMING
mdefine_line|#define USE_PCI_TIMING          0x00000040
DECL|macro|POSTED_WRITE_ENABLE
mdefine_line|#define POSTED_WRITE_ENABLE     0x00000080
DECL|macro|DMA_POLICY_MASK
mdefine_line|#define DMA_POLICY_MASK         0x00000700
DECL|macro|DMA_DDMA
mdefine_line|#define DMA_DDMA                0x00000000
DECL|macro|DMA_TDMA
mdefine_line|#define DMA_TDMA                0x00000100
DECL|macro|DMA_PCPCI
mdefine_line|#define DMA_PCPCI               0x00000200
DECL|macro|DMA_WBDMA16
mdefine_line|#define DMA_WBDMA16             0x00000400
DECL|macro|DMA_WBDMA4
mdefine_line|#define DMA_WBDMA4              0x00000500
DECL|macro|DMA_WBDMA2
mdefine_line|#define DMA_WBDMA2              0x00000600
DECL|macro|DMA_WBDMA1
mdefine_line|#define DMA_WBDMA1              0x00000700
DECL|macro|DMA_SAFE_GUARD
mdefine_line|#define DMA_SAFE_GUARD          0x00000800
DECL|macro|HI_PERF_GP_ENABLE
mdefine_line|#define HI_PERF_GP_ENABLE       0x00001000
DECL|macro|PIC_SNOOP_MODE_0
mdefine_line|#define PIC_SNOOP_MODE_0        0x00002000
DECL|macro|PIC_SNOOP_MODE_1
mdefine_line|#define PIC_SNOOP_MODE_1        0x00004000
DECL|macro|SOUNDBLASTER_IRQ_MASK
mdefine_line|#define SOUNDBLASTER_IRQ_MASK   0x00008000
DECL|macro|RING_IN_ENABLE
mdefine_line|#define RING_IN_ENABLE          0x00010000
DECL|macro|SPDIF_TEST_MODE
mdefine_line|#define SPDIF_TEST_MODE         0x00020000
DECL|macro|CLK_MULT_MODE_SELECT_2
mdefine_line|#define CLK_MULT_MODE_SELECT_2  0x00040000
DECL|macro|EEPROM_WRITE_ENABLE
mdefine_line|#define EEPROM_WRITE_ENABLE     0x00080000
DECL|macro|CODEC_DIR_IN
mdefine_line|#define CODEC_DIR_IN            0x00100000
DECL|macro|HV_BUTTON_FROM_GD
mdefine_line|#define HV_BUTTON_FROM_GD       0x00200000
DECL|macro|REDUCED_DEBOUNCE
mdefine_line|#define REDUCED_DEBOUNCE        0x00400000
DECL|macro|HV_CTRL_ENABLE
mdefine_line|#define HV_CTRL_ENABLE          0x00800000
DECL|macro|SPDIF_ENABLE
mdefine_line|#define SPDIF_ENABLE            0x01000000
DECL|macro|CLK_DIV_SELECT
mdefine_line|#define CLK_DIV_SELECT          0x06000000
DECL|macro|CLK_DIV_BY_48
mdefine_line|#define CLK_DIV_BY_48           0x00000000
DECL|macro|CLK_DIV_BY_49
mdefine_line|#define CLK_DIV_BY_49           0x02000000
DECL|macro|CLK_DIV_BY_50
mdefine_line|#define CLK_DIV_BY_50           0x04000000
DECL|macro|CLK_DIV_RESERVED
mdefine_line|#define CLK_DIV_RESERVED        0x06000000
DECL|macro|PM_CTRL_ENABLE
mdefine_line|#define PM_CTRL_ENABLE          0x08000000
DECL|macro|CLK_MULT_MODE_SELECT
mdefine_line|#define CLK_MULT_MODE_SELECT    0x30000000
DECL|macro|CLK_MULT_MODE_SHIFT
mdefine_line|#define CLK_MULT_MODE_SHIFT     28
DECL|macro|CLK_MULT_MODE_0
mdefine_line|#define CLK_MULT_MODE_0         0x00000000
DECL|macro|CLK_MULT_MODE_1
mdefine_line|#define CLK_MULT_MODE_1         0x10000000
DECL|macro|CLK_MULT_MODE_2
mdefine_line|#define CLK_MULT_MODE_2         0x20000000
DECL|macro|CLK_MULT_MODE_3
mdefine_line|#define CLK_MULT_MODE_3         0x30000000
DECL|macro|INT_CLK_SELECT
mdefine_line|#define INT_CLK_SELECT          0x40000000
DECL|macro|INT_CLK_MULT_RESET
mdefine_line|#define INT_CLK_MULT_RESET      0x80000000
singleline_comment|// M3
DECL|macro|INT_CLK_SRC_NOT_PCI
mdefine_line|#define INT_CLK_SRC_NOT_PCI     0x00100000
DECL|macro|INT_CLK_MULT_ENABLE
mdefine_line|#define INT_CLK_MULT_ENABLE     0x80000000
DECL|macro|PCI_ACPI_CONTROL
mdefine_line|#define PCI_ACPI_CONTROL        0x54
DECL|macro|PCI_ACPI_D0
mdefine_line|#define PCI_ACPI_D0             0x00000000
DECL|macro|PCI_ACPI_D1
mdefine_line|#define PCI_ACPI_D1             0xB4F70000
DECL|macro|PCI_ACPI_D2
mdefine_line|#define PCI_ACPI_D2             0xB4F7B4F7
DECL|macro|PCI_USER_CONFIG
mdefine_line|#define PCI_USER_CONFIG         0x58
DECL|macro|EXT_PCI_MASTER_ENABLE
mdefine_line|#define EXT_PCI_MASTER_ENABLE   0x00000001
DECL|macro|SPDIF_OUT_SELECT
mdefine_line|#define SPDIF_OUT_SELECT        0x00000002
DECL|macro|TEST_PIN_DIR_CTRL
mdefine_line|#define TEST_PIN_DIR_CTRL       0x00000004
DECL|macro|AC97_CODEC_TEST
mdefine_line|#define AC97_CODEC_TEST         0x00000020
DECL|macro|TRI_STATE_BUFFER
mdefine_line|#define TRI_STATE_BUFFER        0x00000080
DECL|macro|IN_CLK_12MHZ_SELECT
mdefine_line|#define IN_CLK_12MHZ_SELECT     0x00000100
DECL|macro|MULTI_FUNC_DISABLE
mdefine_line|#define MULTI_FUNC_DISABLE      0x00000200
DECL|macro|EXT_MASTER_PAIR_SEL
mdefine_line|#define EXT_MASTER_PAIR_SEL     0x00000400
DECL|macro|PCI_MASTER_SUPPORT
mdefine_line|#define PCI_MASTER_SUPPORT      0x00000800
DECL|macro|STOP_CLOCK_ENABLE
mdefine_line|#define STOP_CLOCK_ENABLE       0x00001000
DECL|macro|EAPD_DRIVE_ENABLE
mdefine_line|#define EAPD_DRIVE_ENABLE       0x00002000
DECL|macro|REQ_TRI_STATE_ENABLE
mdefine_line|#define REQ_TRI_STATE_ENABLE    0x00004000
DECL|macro|REQ_LOW_ENABLE
mdefine_line|#define REQ_LOW_ENABLE          0x00008000
DECL|macro|MIDI_1_ENABLE
mdefine_line|#define MIDI_1_ENABLE           0x00010000
DECL|macro|MIDI_2_ENABLE
mdefine_line|#define MIDI_2_ENABLE           0x00020000
DECL|macro|SB_AUDIO_SYNC
mdefine_line|#define SB_AUDIO_SYNC           0x00040000
DECL|macro|HV_CTRL_TEST
mdefine_line|#define HV_CTRL_TEST            0x00100000
DECL|macro|SOUNDBLASTER_TEST
mdefine_line|#define SOUNDBLASTER_TEST       0x00400000
DECL|macro|PCI_USER_CONFIG_C
mdefine_line|#define PCI_USER_CONFIG_C       0x5C
DECL|macro|PCI_DDMA_CTRL
mdefine_line|#define PCI_DDMA_CTRL           0x60
DECL|macro|DDMA_ENABLE
mdefine_line|#define DDMA_ENABLE             0x00000001
singleline_comment|// Allegro registers
DECL|macro|HOST_INT_CTRL
mdefine_line|#define HOST_INT_CTRL           0x18
DECL|macro|SB_INT_ENABLE
mdefine_line|#define SB_INT_ENABLE           0x0001
DECL|macro|MPU401_INT_ENABLE
mdefine_line|#define MPU401_INT_ENABLE       0x0002
DECL|macro|ASSP_INT_ENABLE
mdefine_line|#define ASSP_INT_ENABLE         0x0010
DECL|macro|RING_INT_ENABLE
mdefine_line|#define RING_INT_ENABLE         0x0020
DECL|macro|HV_INT_ENABLE
mdefine_line|#define HV_INT_ENABLE           0x0040
DECL|macro|CLKRUN_GEN_ENABLE
mdefine_line|#define CLKRUN_GEN_ENABLE       0x0100
DECL|macro|HV_CTRL_TO_PME
mdefine_line|#define HV_CTRL_TO_PME          0x0400
DECL|macro|SOFTWARE_RESET_ENABLE
mdefine_line|#define SOFTWARE_RESET_ENABLE   0x8000
multiline_comment|/*&n; * should be using the above defines, probably.&n; */
DECL|macro|REGB_ENABLE_RESET
mdefine_line|#define REGB_ENABLE_RESET               0x01
DECL|macro|REGB_STOP_CLOCK
mdefine_line|#define REGB_STOP_CLOCK                 0x10
DECL|macro|HOST_INT_STATUS
mdefine_line|#define HOST_INT_STATUS         0x1A
DECL|macro|SB_INT_PENDING
mdefine_line|#define SB_INT_PENDING          0x01
DECL|macro|MPU401_INT_PENDING
mdefine_line|#define MPU401_INT_PENDING      0x02
DECL|macro|ASSP_INT_PENDING
mdefine_line|#define ASSP_INT_PENDING        0x10
DECL|macro|RING_INT_PENDING
mdefine_line|#define RING_INT_PENDING        0x20
DECL|macro|HV_INT_PENDING
mdefine_line|#define HV_INT_PENDING          0x40
DECL|macro|HARDWARE_VOL_CTRL
mdefine_line|#define HARDWARE_VOL_CTRL       0x1B
DECL|macro|SHADOW_MIX_REG_VOICE
mdefine_line|#define SHADOW_MIX_REG_VOICE    0x1C
DECL|macro|HW_VOL_COUNTER_VOICE
mdefine_line|#define HW_VOL_COUNTER_VOICE    0x1D
DECL|macro|SHADOW_MIX_REG_MASTER
mdefine_line|#define SHADOW_MIX_REG_MASTER   0x1E
DECL|macro|HW_VOL_COUNTER_MASTER
mdefine_line|#define HW_VOL_COUNTER_MASTER   0x1F
DECL|macro|CODEC_COMMAND
mdefine_line|#define CODEC_COMMAND           0x30
DECL|macro|CODEC_READ_B
mdefine_line|#define CODEC_READ_B            0x80
DECL|macro|CODEC_STATUS
mdefine_line|#define CODEC_STATUS            0x30
DECL|macro|CODEC_BUSY_B
mdefine_line|#define CODEC_BUSY_B            0x01
DECL|macro|CODEC_DATA
mdefine_line|#define CODEC_DATA              0x32
DECL|macro|RING_BUS_CTRL_A
mdefine_line|#define RING_BUS_CTRL_A         0x36
DECL|macro|RAC_PME_ENABLE
mdefine_line|#define RAC_PME_ENABLE          0x0100
DECL|macro|RAC_SDFS_ENABLE
mdefine_line|#define RAC_SDFS_ENABLE         0x0200
DECL|macro|LAC_PME_ENABLE
mdefine_line|#define LAC_PME_ENABLE          0x0400
DECL|macro|LAC_SDFS_ENABLE
mdefine_line|#define LAC_SDFS_ENABLE         0x0800
DECL|macro|SERIAL_AC_LINK_ENABLE
mdefine_line|#define SERIAL_AC_LINK_ENABLE   0x1000
DECL|macro|IO_SRAM_ENABLE
mdefine_line|#define IO_SRAM_ENABLE          0x2000
DECL|macro|IIS_INPUT_ENABLE
mdefine_line|#define IIS_INPUT_ENABLE        0x8000
DECL|macro|RING_BUS_CTRL_B
mdefine_line|#define RING_BUS_CTRL_B         0x38
DECL|macro|SECOND_CODEC_ID_MASK
mdefine_line|#define SECOND_CODEC_ID_MASK    0x0003
DECL|macro|SPDIF_FUNC_ENABLE
mdefine_line|#define SPDIF_FUNC_ENABLE       0x0010
DECL|macro|SECOND_AC_ENABLE
mdefine_line|#define SECOND_AC_ENABLE        0x0020
DECL|macro|SB_MODULE_INTF_ENABLE
mdefine_line|#define SB_MODULE_INTF_ENABLE   0x0040
DECL|macro|SSPE_ENABLE
mdefine_line|#define SSPE_ENABLE             0x0040
DECL|macro|M3I_DOCK_ENABLE
mdefine_line|#define M3I_DOCK_ENABLE         0x0080
DECL|macro|SDO_OUT_DEST_CTRL
mdefine_line|#define SDO_OUT_DEST_CTRL       0x3A
DECL|macro|COMMAND_ADDR_OUT
mdefine_line|#define COMMAND_ADDR_OUT        0x0003
DECL|macro|PCM_LR_OUT_LOCAL
mdefine_line|#define PCM_LR_OUT_LOCAL        0x0000
DECL|macro|PCM_LR_OUT_REMOTE
mdefine_line|#define PCM_LR_OUT_REMOTE       0x0004
DECL|macro|PCM_LR_OUT_MUTE
mdefine_line|#define PCM_LR_OUT_MUTE         0x0008
DECL|macro|PCM_LR_OUT_BOTH
mdefine_line|#define PCM_LR_OUT_BOTH         0x000C
DECL|macro|LINE1_DAC_OUT_LOCAL
mdefine_line|#define LINE1_DAC_OUT_LOCAL     0x0000
DECL|macro|LINE1_DAC_OUT_REMOTE
mdefine_line|#define LINE1_DAC_OUT_REMOTE    0x0010
DECL|macro|LINE1_DAC_OUT_MUTE
mdefine_line|#define LINE1_DAC_OUT_MUTE      0x0020
DECL|macro|LINE1_DAC_OUT_BOTH
mdefine_line|#define LINE1_DAC_OUT_BOTH      0x0030
DECL|macro|PCM_CLS_OUT_LOCAL
mdefine_line|#define PCM_CLS_OUT_LOCAL       0x0000
DECL|macro|PCM_CLS_OUT_REMOTE
mdefine_line|#define PCM_CLS_OUT_REMOTE      0x0040
DECL|macro|PCM_CLS_OUT_MUTE
mdefine_line|#define PCM_CLS_OUT_MUTE        0x0080
DECL|macro|PCM_CLS_OUT_BOTH
mdefine_line|#define PCM_CLS_OUT_BOTH        0x00C0
DECL|macro|PCM_RLF_OUT_LOCAL
mdefine_line|#define PCM_RLF_OUT_LOCAL       0x0000
DECL|macro|PCM_RLF_OUT_REMOTE
mdefine_line|#define PCM_RLF_OUT_REMOTE      0x0100
DECL|macro|PCM_RLF_OUT_MUTE
mdefine_line|#define PCM_RLF_OUT_MUTE        0x0200
DECL|macro|PCM_RLF_OUT_BOTH
mdefine_line|#define PCM_RLF_OUT_BOTH        0x0300
DECL|macro|LINE2_DAC_OUT_LOCAL
mdefine_line|#define LINE2_DAC_OUT_LOCAL     0x0000
DECL|macro|LINE2_DAC_OUT_REMOTE
mdefine_line|#define LINE2_DAC_OUT_REMOTE    0x0400
DECL|macro|LINE2_DAC_OUT_MUTE
mdefine_line|#define LINE2_DAC_OUT_MUTE      0x0800
DECL|macro|LINE2_DAC_OUT_BOTH
mdefine_line|#define LINE2_DAC_OUT_BOTH      0x0C00
DECL|macro|HANDSET_OUT_LOCAL
mdefine_line|#define HANDSET_OUT_LOCAL       0x0000
DECL|macro|HANDSET_OUT_REMOTE
mdefine_line|#define HANDSET_OUT_REMOTE      0x1000
DECL|macro|HANDSET_OUT_MUTE
mdefine_line|#define HANDSET_OUT_MUTE        0x2000
DECL|macro|HANDSET_OUT_BOTH
mdefine_line|#define HANDSET_OUT_BOTH        0x3000
DECL|macro|IO_CTRL_OUT_LOCAL
mdefine_line|#define IO_CTRL_OUT_LOCAL       0x0000
DECL|macro|IO_CTRL_OUT_REMOTE
mdefine_line|#define IO_CTRL_OUT_REMOTE      0x4000
DECL|macro|IO_CTRL_OUT_MUTE
mdefine_line|#define IO_CTRL_OUT_MUTE        0x8000
DECL|macro|IO_CTRL_OUT_BOTH
mdefine_line|#define IO_CTRL_OUT_BOTH        0xC000
DECL|macro|SDO_IN_DEST_CTRL
mdefine_line|#define SDO_IN_DEST_CTRL        0x3C
DECL|macro|STATUS_ADDR_IN
mdefine_line|#define STATUS_ADDR_IN          0x0003
DECL|macro|PCM_LR_IN_LOCAL
mdefine_line|#define PCM_LR_IN_LOCAL         0x0000
DECL|macro|PCM_LR_IN_REMOTE
mdefine_line|#define PCM_LR_IN_REMOTE        0x0004
DECL|macro|PCM_LR_RESERVED
mdefine_line|#define PCM_LR_RESERVED         0x0008
DECL|macro|PCM_LR_IN_BOTH
mdefine_line|#define PCM_LR_IN_BOTH          0x000C
DECL|macro|LINE1_ADC_IN_LOCAL
mdefine_line|#define LINE1_ADC_IN_LOCAL      0x0000
DECL|macro|LINE1_ADC_IN_REMOTE
mdefine_line|#define LINE1_ADC_IN_REMOTE     0x0010
DECL|macro|LINE1_ADC_IN_MUTE
mdefine_line|#define LINE1_ADC_IN_MUTE       0x0020
DECL|macro|MIC_ADC_IN_LOCAL
mdefine_line|#define MIC_ADC_IN_LOCAL        0x0000
DECL|macro|MIC_ADC_IN_REMOTE
mdefine_line|#define MIC_ADC_IN_REMOTE       0x0040
DECL|macro|MIC_ADC_IN_MUTE
mdefine_line|#define MIC_ADC_IN_MUTE         0x0080
DECL|macro|LINE2_DAC_IN_LOCAL
mdefine_line|#define LINE2_DAC_IN_LOCAL      0x0000
DECL|macro|LINE2_DAC_IN_REMOTE
mdefine_line|#define LINE2_DAC_IN_REMOTE     0x0400
DECL|macro|LINE2_DAC_IN_MUTE
mdefine_line|#define LINE2_DAC_IN_MUTE       0x0800
DECL|macro|HANDSET_IN_LOCAL
mdefine_line|#define HANDSET_IN_LOCAL        0x0000
DECL|macro|HANDSET_IN_REMOTE
mdefine_line|#define HANDSET_IN_REMOTE       0x1000
DECL|macro|HANDSET_IN_MUTE
mdefine_line|#define HANDSET_IN_MUTE         0x2000
DECL|macro|IO_STATUS_IN_LOCAL
mdefine_line|#define IO_STATUS_IN_LOCAL      0x0000
DECL|macro|IO_STATUS_IN_REMOTE
mdefine_line|#define IO_STATUS_IN_REMOTE     0x4000
DECL|macro|SPDIF_IN_CTRL
mdefine_line|#define SPDIF_IN_CTRL           0x3E
DECL|macro|SPDIF_IN_ENABLE
mdefine_line|#define SPDIF_IN_ENABLE         0x0001
DECL|macro|GPIO_DATA
mdefine_line|#define GPIO_DATA               0x60
DECL|macro|GPIO_DATA_MASK
mdefine_line|#define GPIO_DATA_MASK          0x0FFF
DECL|macro|GPIO_HV_STATUS
mdefine_line|#define GPIO_HV_STATUS          0x3000
DECL|macro|GPIO_PME_STATUS
mdefine_line|#define GPIO_PME_STATUS         0x4000
DECL|macro|GPIO_MASK
mdefine_line|#define GPIO_MASK               0x64
DECL|macro|GPIO_DIRECTION
mdefine_line|#define GPIO_DIRECTION          0x68
DECL|macro|GPO_PRIMARY_AC97
mdefine_line|#define GPO_PRIMARY_AC97        0x0001
DECL|macro|GPI_LINEOUT_SENSE
mdefine_line|#define GPI_LINEOUT_SENSE       0x0004
DECL|macro|GPO_SECONDARY_AC97
mdefine_line|#define GPO_SECONDARY_AC97      0x0008
DECL|macro|GPI_VOL_DOWN
mdefine_line|#define GPI_VOL_DOWN            0x0010
DECL|macro|GPI_VOL_UP
mdefine_line|#define GPI_VOL_UP              0x0020
DECL|macro|GPI_IIS_CLK
mdefine_line|#define GPI_IIS_CLK             0x0040
DECL|macro|GPI_IIS_LRCLK
mdefine_line|#define GPI_IIS_LRCLK           0x0080
DECL|macro|GPI_IIS_DATA
mdefine_line|#define GPI_IIS_DATA            0x0100
DECL|macro|GPI_DOCKING_STATUS
mdefine_line|#define GPI_DOCKING_STATUS      0x0100
DECL|macro|GPI_HEADPHONE_SENSE
mdefine_line|#define GPI_HEADPHONE_SENSE     0x0200
DECL|macro|GPO_EXT_AMP_SHUTDOWN
mdefine_line|#define GPO_EXT_AMP_SHUTDOWN    0x1000
singleline_comment|// M3
DECL|macro|GPO_M3_EXT_AMP_SHUTDN
mdefine_line|#define GPO_M3_EXT_AMP_SHUTDN   0x0002
DECL|macro|ASSP_INDEX_PORT
mdefine_line|#define ASSP_INDEX_PORT         0x80
DECL|macro|ASSP_MEMORY_PORT
mdefine_line|#define ASSP_MEMORY_PORT        0x82
DECL|macro|ASSP_DATA_PORT
mdefine_line|#define ASSP_DATA_PORT          0x84
DECL|macro|MPU401_DATA_PORT
mdefine_line|#define MPU401_DATA_PORT        0x98
DECL|macro|MPU401_STATUS_PORT
mdefine_line|#define MPU401_STATUS_PORT      0x99
DECL|macro|CLK_MULT_DATA_PORT
mdefine_line|#define CLK_MULT_DATA_PORT      0x9C
DECL|macro|ASSP_CONTROL_A
mdefine_line|#define ASSP_CONTROL_A          0xA2
DECL|macro|ASSP_0_WS_ENABLE
mdefine_line|#define ASSP_0_WS_ENABLE        0x01
DECL|macro|ASSP_CTRL_A_RESERVED1
mdefine_line|#define ASSP_CTRL_A_RESERVED1   0x02
DECL|macro|ASSP_CTRL_A_RESERVED2
mdefine_line|#define ASSP_CTRL_A_RESERVED2   0x04
DECL|macro|ASSP_CLK_49MHZ_SELECT
mdefine_line|#define ASSP_CLK_49MHZ_SELECT   0x08
DECL|macro|FAST_PLU_ENABLE
mdefine_line|#define FAST_PLU_ENABLE         0x10
DECL|macro|ASSP_CTRL_A_RESERVED3
mdefine_line|#define ASSP_CTRL_A_RESERVED3   0x20
DECL|macro|DSP_CLK_36MHZ_SELECT
mdefine_line|#define DSP_CLK_36MHZ_SELECT    0x40
DECL|macro|ASSP_CONTROL_B
mdefine_line|#define ASSP_CONTROL_B          0xA4
DECL|macro|RESET_ASSP
mdefine_line|#define RESET_ASSP              0x00
DECL|macro|RUN_ASSP
mdefine_line|#define RUN_ASSP                0x01
DECL|macro|ENABLE_ASSP_CLOCK
mdefine_line|#define ENABLE_ASSP_CLOCK       0x00
DECL|macro|STOP_ASSP_CLOCK
mdefine_line|#define STOP_ASSP_CLOCK         0x10
DECL|macro|RESET_TOGGLE
mdefine_line|#define RESET_TOGGLE            0x40
DECL|macro|ASSP_CONTROL_C
mdefine_line|#define ASSP_CONTROL_C          0xA6
DECL|macro|ASSP_HOST_INT_ENABLE
mdefine_line|#define ASSP_HOST_INT_ENABLE    0x01
DECL|macro|FM_ADDR_REMAP_DISABLE
mdefine_line|#define FM_ADDR_REMAP_DISABLE   0x02
DECL|macro|HOST_WRITE_PORT_ENABLE
mdefine_line|#define HOST_WRITE_PORT_ENABLE  0x08
DECL|macro|ASSP_HOST_INT_STATUS
mdefine_line|#define ASSP_HOST_INT_STATUS    0xAC
DECL|macro|DSP2HOST_REQ_PIORECORD
mdefine_line|#define DSP2HOST_REQ_PIORECORD  0x01
DECL|macro|DSP2HOST_REQ_I2SRATE
mdefine_line|#define DSP2HOST_REQ_I2SRATE    0x02
DECL|macro|DSP2HOST_REQ_TIMER
mdefine_line|#define DSP2HOST_REQ_TIMER      0x04
singleline_comment|// AC97 registers
singleline_comment|// XXX fix this crap up
multiline_comment|/*#define AC97_RESET              0x00*/
DECL|macro|AC97_VOL_MUTE_B
mdefine_line|#define AC97_VOL_MUTE_B         0x8000
DECL|macro|AC97_VOL_M
mdefine_line|#define AC97_VOL_M              0x1F
DECL|macro|AC97_LEFT_VOL_S
mdefine_line|#define AC97_LEFT_VOL_S         8
DECL|macro|AC97_MASTER_VOL
mdefine_line|#define AC97_MASTER_VOL         0x02
DECL|macro|AC97_LINE_LEVEL_VOL
mdefine_line|#define AC97_LINE_LEVEL_VOL     0x04
DECL|macro|AC97_MASTER_MONO_VOL
mdefine_line|#define AC97_MASTER_MONO_VOL    0x06
DECL|macro|AC97_PC_BEEP_VOL
mdefine_line|#define AC97_PC_BEEP_VOL        0x0A
DECL|macro|AC97_PC_BEEP_VOL_M
mdefine_line|#define AC97_PC_BEEP_VOL_M      0x0F
DECL|macro|AC97_SROUND_MASTER_VOL
mdefine_line|#define AC97_SROUND_MASTER_VOL  0x38
DECL|macro|AC97_PC_BEEP_VOL_S
mdefine_line|#define AC97_PC_BEEP_VOL_S      1
multiline_comment|/*#define AC97_PHONE_VOL          0x0C&n;#define AC97_MIC_VOL            0x0E*/
DECL|macro|AC97_MIC_20DB_ENABLE
mdefine_line|#define AC97_MIC_20DB_ENABLE    0x40
multiline_comment|/*#define AC97_LINEIN_VOL         0x10&n;#define AC97_CD_VOL             0x12&n;#define AC97_VIDEO_VOL          0x14&n;#define AC97_AUX_VOL            0x16*/
DECL|macro|AC97_PCM_OUT_VOL
mdefine_line|#define AC97_PCM_OUT_VOL        0x18
multiline_comment|/*#define AC97_RECORD_SELECT      0x1A*/
DECL|macro|AC97_RECORD_MIC
mdefine_line|#define AC97_RECORD_MIC         0x00
DECL|macro|AC97_RECORD_CD
mdefine_line|#define AC97_RECORD_CD          0x01
DECL|macro|AC97_RECORD_VIDEO
mdefine_line|#define AC97_RECORD_VIDEO       0x02
DECL|macro|AC97_RECORD_AUX
mdefine_line|#define AC97_RECORD_AUX         0x03
DECL|macro|AC97_RECORD_MONO_MUX
mdefine_line|#define AC97_RECORD_MONO_MUX    0x02
DECL|macro|AC97_RECORD_DIGITAL
mdefine_line|#define AC97_RECORD_DIGITAL     0x03
DECL|macro|AC97_RECORD_LINE
mdefine_line|#define AC97_RECORD_LINE        0x04
DECL|macro|AC97_RECORD_STEREO
mdefine_line|#define AC97_RECORD_STEREO      0x05
DECL|macro|AC97_RECORD_MONO
mdefine_line|#define AC97_RECORD_MONO        0x06
DECL|macro|AC97_RECORD_PHONE
mdefine_line|#define AC97_RECORD_PHONE       0x07
multiline_comment|/*#define AC97_RECORD_GAIN        0x1C*/
DECL|macro|AC97_RECORD_VOL_M
mdefine_line|#define AC97_RECORD_VOL_M       0x0F
multiline_comment|/*#define AC97_GENERAL_PURPOSE    0x20*/
DECL|macro|AC97_POWER_DOWN_CTRL
mdefine_line|#define AC97_POWER_DOWN_CTRL    0x26
DECL|macro|AC97_ADC_READY
mdefine_line|#define AC97_ADC_READY          0x0001
DECL|macro|AC97_DAC_READY
mdefine_line|#define AC97_DAC_READY          0x0002
DECL|macro|AC97_ANALOG_READY
mdefine_line|#define AC97_ANALOG_READY       0x0004
DECL|macro|AC97_VREF_ON
mdefine_line|#define AC97_VREF_ON            0x0008
DECL|macro|AC97_PR0
mdefine_line|#define AC97_PR0                0x0100
DECL|macro|AC97_PR1
mdefine_line|#define AC97_PR1                0x0200
DECL|macro|AC97_PR2
mdefine_line|#define AC97_PR2                0x0400
DECL|macro|AC97_PR3
mdefine_line|#define AC97_PR3                0x0800
DECL|macro|AC97_PR4
mdefine_line|#define AC97_PR4                0x1000
DECL|macro|AC97_RESERVED1
mdefine_line|#define AC97_RESERVED1          0x28
DECL|macro|AC97_VENDOR_TEST
mdefine_line|#define AC97_VENDOR_TEST        0x5A
DECL|macro|AC97_CLOCK_DELAY
mdefine_line|#define AC97_CLOCK_DELAY        0x5C
DECL|macro|AC97_LINEOUT_MUX_SEL
mdefine_line|#define AC97_LINEOUT_MUX_SEL    0x0001
DECL|macro|AC97_MONO_MUX_SEL
mdefine_line|#define AC97_MONO_MUX_SEL       0x0002
DECL|macro|AC97_CLOCK_DELAY_SEL
mdefine_line|#define AC97_CLOCK_DELAY_SEL    0x1F
DECL|macro|AC97_DAC_CDS_SHIFT
mdefine_line|#define AC97_DAC_CDS_SHIFT      6
DECL|macro|AC97_ADC_CDS_SHIFT
mdefine_line|#define AC97_ADC_CDS_SHIFT      11
DECL|macro|AC97_MULTI_CHANNEL_SEL
mdefine_line|#define AC97_MULTI_CHANNEL_SEL  0x74
multiline_comment|/*#define AC97_VENDOR_ID1         0x7C&n;#define AC97_VENDOR_ID2         0x7E*/
multiline_comment|/*&n; * ASSP control regs&n; */
DECL|macro|DSP_PORT_TIMER_COUNT
mdefine_line|#define DSP_PORT_TIMER_COUNT    0x06
DECL|macro|DSP_PORT_MEMORY_INDEX
mdefine_line|#define DSP_PORT_MEMORY_INDEX   0x80
DECL|macro|DSP_PORT_MEMORY_TYPE
mdefine_line|#define DSP_PORT_MEMORY_TYPE    0x82
DECL|macro|MEMTYPE_INTERNAL_CODE
mdefine_line|#define MEMTYPE_INTERNAL_CODE   0x0002
DECL|macro|MEMTYPE_INTERNAL_DATA
mdefine_line|#define MEMTYPE_INTERNAL_DATA   0x0003
DECL|macro|MEMTYPE_MASK
mdefine_line|#define MEMTYPE_MASK            0x0003
DECL|macro|DSP_PORT_MEMORY_DATA
mdefine_line|#define DSP_PORT_MEMORY_DATA    0x84
DECL|macro|DSP_PORT_CONTROL_REG_A
mdefine_line|#define DSP_PORT_CONTROL_REG_A  0xA2
DECL|macro|DSP_PORT_CONTROL_REG_B
mdefine_line|#define DSP_PORT_CONTROL_REG_B  0xA4
DECL|macro|DSP_PORT_CONTROL_REG_C
mdefine_line|#define DSP_PORT_CONTROL_REG_C  0xA6
DECL|macro|REV_A_CODE_MEMORY_BEGIN
mdefine_line|#define REV_A_CODE_MEMORY_BEGIN         0x0000
DECL|macro|REV_A_CODE_MEMORY_END
mdefine_line|#define REV_A_CODE_MEMORY_END           0x0FFF
DECL|macro|REV_A_CODE_MEMORY_UNIT_LENGTH
mdefine_line|#define REV_A_CODE_MEMORY_UNIT_LENGTH   0x0040
DECL|macro|REV_A_CODE_MEMORY_LENGTH
mdefine_line|#define REV_A_CODE_MEMORY_LENGTH        (REV_A_CODE_MEMORY_END - REV_A_CODE_MEMORY_BEGIN + 1)
DECL|macro|REV_B_CODE_MEMORY_BEGIN
mdefine_line|#define REV_B_CODE_MEMORY_BEGIN         0x0000
DECL|macro|REV_B_CODE_MEMORY_END
mdefine_line|#define REV_B_CODE_MEMORY_END           0x0BFF
DECL|macro|REV_B_CODE_MEMORY_UNIT_LENGTH
mdefine_line|#define REV_B_CODE_MEMORY_UNIT_LENGTH   0x0040
DECL|macro|REV_B_CODE_MEMORY_LENGTH
mdefine_line|#define REV_B_CODE_MEMORY_LENGTH        (REV_B_CODE_MEMORY_END - REV_B_CODE_MEMORY_BEGIN + 1)
DECL|macro|REV_A_DATA_MEMORY_BEGIN
mdefine_line|#define REV_A_DATA_MEMORY_BEGIN         0x1000
DECL|macro|REV_A_DATA_MEMORY_END
mdefine_line|#define REV_A_DATA_MEMORY_END           0x2FFF
DECL|macro|REV_A_DATA_MEMORY_UNIT_LENGTH
mdefine_line|#define REV_A_DATA_MEMORY_UNIT_LENGTH   0x0080
DECL|macro|REV_A_DATA_MEMORY_LENGTH
mdefine_line|#define REV_A_DATA_MEMORY_LENGTH        (REV_A_DATA_MEMORY_END - REV_A_DATA_MEMORY_BEGIN + 1)
DECL|macro|REV_B_DATA_MEMORY_BEGIN
mdefine_line|#define REV_B_DATA_MEMORY_BEGIN         0x1000
DECL|macro|REV_B_DATA_MEMORY_END
mdefine_line|#define REV_B_DATA_MEMORY_END           0x2BFF
DECL|macro|REV_B_DATA_MEMORY_UNIT_LENGTH
mdefine_line|#define REV_B_DATA_MEMORY_UNIT_LENGTH   0x0080
DECL|macro|REV_B_DATA_MEMORY_LENGTH
mdefine_line|#define REV_B_DATA_MEMORY_LENGTH        (REV_B_DATA_MEMORY_END - REV_B_DATA_MEMORY_BEGIN + 1)
DECL|macro|NUM_UNITS_KERNEL_CODE
mdefine_line|#define NUM_UNITS_KERNEL_CODE          16
DECL|macro|NUM_UNITS_KERNEL_DATA
mdefine_line|#define NUM_UNITS_KERNEL_DATA           2
DECL|macro|NUM_UNITS_KERNEL_CODE_WITH_HSP
mdefine_line|#define NUM_UNITS_KERNEL_CODE_WITH_HSP 16
DECL|macro|NUM_UNITS_KERNEL_DATA_WITH_HSP
mdefine_line|#define NUM_UNITS_KERNEL_DATA_WITH_HSP  5
multiline_comment|/*&n; * Kernel data layout&n; */
DECL|macro|DP_SHIFT_COUNT
mdefine_line|#define DP_SHIFT_COUNT                  7
DECL|macro|KDATA_BASE_ADDR
mdefine_line|#define KDATA_BASE_ADDR                 0x1000
DECL|macro|KDATA_BASE_ADDR2
mdefine_line|#define KDATA_BASE_ADDR2                0x1080
DECL|macro|KDATA_TASK0
mdefine_line|#define KDATA_TASK0                     (KDATA_BASE_ADDR + 0x0000)
DECL|macro|KDATA_TASK1
mdefine_line|#define KDATA_TASK1                     (KDATA_BASE_ADDR + 0x0001)
DECL|macro|KDATA_TASK2
mdefine_line|#define KDATA_TASK2                     (KDATA_BASE_ADDR + 0x0002)
DECL|macro|KDATA_TASK3
mdefine_line|#define KDATA_TASK3                     (KDATA_BASE_ADDR + 0x0003)
DECL|macro|KDATA_TASK4
mdefine_line|#define KDATA_TASK4                     (KDATA_BASE_ADDR + 0x0004)
DECL|macro|KDATA_TASK5
mdefine_line|#define KDATA_TASK5                     (KDATA_BASE_ADDR + 0x0005)
DECL|macro|KDATA_TASK6
mdefine_line|#define KDATA_TASK6                     (KDATA_BASE_ADDR + 0x0006)
DECL|macro|KDATA_TASK7
mdefine_line|#define KDATA_TASK7                     (KDATA_BASE_ADDR + 0x0007)
DECL|macro|KDATA_TASK_ENDMARK
mdefine_line|#define KDATA_TASK_ENDMARK              (KDATA_BASE_ADDR + 0x0008)
DECL|macro|KDATA_CURRENT_TASK
mdefine_line|#define KDATA_CURRENT_TASK              (KDATA_BASE_ADDR + 0x0009)
DECL|macro|KDATA_TASK_SWITCH
mdefine_line|#define KDATA_TASK_SWITCH               (KDATA_BASE_ADDR + 0x000A)
DECL|macro|KDATA_INSTANCE0_POS3D
mdefine_line|#define KDATA_INSTANCE0_POS3D           (KDATA_BASE_ADDR + 0x000B)
DECL|macro|KDATA_INSTANCE1_POS3D
mdefine_line|#define KDATA_INSTANCE1_POS3D           (KDATA_BASE_ADDR + 0x000C)
DECL|macro|KDATA_INSTANCE2_POS3D
mdefine_line|#define KDATA_INSTANCE2_POS3D           (KDATA_BASE_ADDR + 0x000D)
DECL|macro|KDATA_INSTANCE3_POS3D
mdefine_line|#define KDATA_INSTANCE3_POS3D           (KDATA_BASE_ADDR + 0x000E)
DECL|macro|KDATA_INSTANCE4_POS3D
mdefine_line|#define KDATA_INSTANCE4_POS3D           (KDATA_BASE_ADDR + 0x000F)
DECL|macro|KDATA_INSTANCE5_POS3D
mdefine_line|#define KDATA_INSTANCE5_POS3D           (KDATA_BASE_ADDR + 0x0010)
DECL|macro|KDATA_INSTANCE6_POS3D
mdefine_line|#define KDATA_INSTANCE6_POS3D           (KDATA_BASE_ADDR + 0x0011)
DECL|macro|KDATA_INSTANCE7_POS3D
mdefine_line|#define KDATA_INSTANCE7_POS3D           (KDATA_BASE_ADDR + 0x0012)
DECL|macro|KDATA_INSTANCE8_POS3D
mdefine_line|#define KDATA_INSTANCE8_POS3D           (KDATA_BASE_ADDR + 0x0013)
DECL|macro|KDATA_INSTANCE_POS3D_ENDMARK
mdefine_line|#define KDATA_INSTANCE_POS3D_ENDMARK    (KDATA_BASE_ADDR + 0x0014)
DECL|macro|KDATA_INSTANCE0_SPKVIRT
mdefine_line|#define KDATA_INSTANCE0_SPKVIRT         (KDATA_BASE_ADDR + 0x0015)
DECL|macro|KDATA_INSTANCE_SPKVIRT_ENDMARK
mdefine_line|#define KDATA_INSTANCE_SPKVIRT_ENDMARK  (KDATA_BASE_ADDR + 0x0016)
DECL|macro|KDATA_INSTANCE0_SPDIF
mdefine_line|#define KDATA_INSTANCE0_SPDIF           (KDATA_BASE_ADDR + 0x0017)
DECL|macro|KDATA_INSTANCE_SPDIF_ENDMARK
mdefine_line|#define KDATA_INSTANCE_SPDIF_ENDMARK    (KDATA_BASE_ADDR + 0x0018)
DECL|macro|KDATA_INSTANCE0_MODEM
mdefine_line|#define KDATA_INSTANCE0_MODEM           (KDATA_BASE_ADDR + 0x0019)
DECL|macro|KDATA_INSTANCE_MODEM_ENDMARK
mdefine_line|#define KDATA_INSTANCE_MODEM_ENDMARK    (KDATA_BASE_ADDR + 0x001A)
DECL|macro|KDATA_INSTANCE0_SRC
mdefine_line|#define KDATA_INSTANCE0_SRC             (KDATA_BASE_ADDR + 0x001B)
DECL|macro|KDATA_INSTANCE1_SRC
mdefine_line|#define KDATA_INSTANCE1_SRC             (KDATA_BASE_ADDR + 0x001C)
DECL|macro|KDATA_INSTANCE_SRC_ENDMARK
mdefine_line|#define KDATA_INSTANCE_SRC_ENDMARK      (KDATA_BASE_ADDR + 0x001D)
DECL|macro|KDATA_INSTANCE0_MINISRC
mdefine_line|#define KDATA_INSTANCE0_MINISRC         (KDATA_BASE_ADDR + 0x001E)
DECL|macro|KDATA_INSTANCE1_MINISRC
mdefine_line|#define KDATA_INSTANCE1_MINISRC         (KDATA_BASE_ADDR + 0x001F)
DECL|macro|KDATA_INSTANCE2_MINISRC
mdefine_line|#define KDATA_INSTANCE2_MINISRC         (KDATA_BASE_ADDR + 0x0020)
DECL|macro|KDATA_INSTANCE3_MINISRC
mdefine_line|#define KDATA_INSTANCE3_MINISRC         (KDATA_BASE_ADDR + 0x0021)
DECL|macro|KDATA_INSTANCE_MINISRC_ENDMARK
mdefine_line|#define KDATA_INSTANCE_MINISRC_ENDMARK  (KDATA_BASE_ADDR + 0x0022)
DECL|macro|KDATA_INSTANCE0_CPYTHRU
mdefine_line|#define KDATA_INSTANCE0_CPYTHRU         (KDATA_BASE_ADDR + 0x0023)
DECL|macro|KDATA_INSTANCE1_CPYTHRU
mdefine_line|#define KDATA_INSTANCE1_CPYTHRU         (KDATA_BASE_ADDR + 0x0024)
DECL|macro|KDATA_INSTANCE_CPYTHRU_ENDMARK
mdefine_line|#define KDATA_INSTANCE_CPYTHRU_ENDMARK  (KDATA_BASE_ADDR + 0x0025)
DECL|macro|KDATA_CURRENT_DMA
mdefine_line|#define KDATA_CURRENT_DMA               (KDATA_BASE_ADDR + 0x0026)
DECL|macro|KDATA_DMA_SWITCH
mdefine_line|#define KDATA_DMA_SWITCH                (KDATA_BASE_ADDR + 0x0027)
DECL|macro|KDATA_DMA_ACTIVE
mdefine_line|#define KDATA_DMA_ACTIVE                (KDATA_BASE_ADDR + 0x0028)
DECL|macro|KDATA_DMA_XFER0
mdefine_line|#define KDATA_DMA_XFER0                 (KDATA_BASE_ADDR + 0x0029)
DECL|macro|KDATA_DMA_XFER1
mdefine_line|#define KDATA_DMA_XFER1                 (KDATA_BASE_ADDR + 0x002A)
DECL|macro|KDATA_DMA_XFER2
mdefine_line|#define KDATA_DMA_XFER2                 (KDATA_BASE_ADDR + 0x002B)
DECL|macro|KDATA_DMA_XFER3
mdefine_line|#define KDATA_DMA_XFER3                 (KDATA_BASE_ADDR + 0x002C)
DECL|macro|KDATA_DMA_XFER4
mdefine_line|#define KDATA_DMA_XFER4                 (KDATA_BASE_ADDR + 0x002D)
DECL|macro|KDATA_DMA_XFER5
mdefine_line|#define KDATA_DMA_XFER5                 (KDATA_BASE_ADDR + 0x002E)
DECL|macro|KDATA_DMA_XFER6
mdefine_line|#define KDATA_DMA_XFER6                 (KDATA_BASE_ADDR + 0x002F)
DECL|macro|KDATA_DMA_XFER7
mdefine_line|#define KDATA_DMA_XFER7                 (KDATA_BASE_ADDR + 0x0030)
DECL|macro|KDATA_DMA_XFER8
mdefine_line|#define KDATA_DMA_XFER8                 (KDATA_BASE_ADDR + 0x0031)
DECL|macro|KDATA_DMA_XFER_ENDMARK
mdefine_line|#define KDATA_DMA_XFER_ENDMARK          (KDATA_BASE_ADDR + 0x0032)
DECL|macro|KDATA_I2S_SAMPLE_COUNT
mdefine_line|#define KDATA_I2S_SAMPLE_COUNT          (KDATA_BASE_ADDR + 0x0033)
DECL|macro|KDATA_I2S_INT_METER
mdefine_line|#define KDATA_I2S_INT_METER             (KDATA_BASE_ADDR + 0x0034)
DECL|macro|KDATA_I2S_ACTIVE
mdefine_line|#define KDATA_I2S_ACTIVE                (KDATA_BASE_ADDR + 0x0035)
DECL|macro|KDATA_TIMER_COUNT_RELOAD
mdefine_line|#define KDATA_TIMER_COUNT_RELOAD        (KDATA_BASE_ADDR + 0x0036)
DECL|macro|KDATA_TIMER_COUNT_CURRENT
mdefine_line|#define KDATA_TIMER_COUNT_CURRENT       (KDATA_BASE_ADDR + 0x0037)
DECL|macro|KDATA_HALT_SYNCH_CLIENT
mdefine_line|#define KDATA_HALT_SYNCH_CLIENT         (KDATA_BASE_ADDR + 0x0038)
DECL|macro|KDATA_HALT_SYNCH_DMA
mdefine_line|#define KDATA_HALT_SYNCH_DMA            (KDATA_BASE_ADDR + 0x0039)
DECL|macro|KDATA_HALT_ACKNOWLEDGE
mdefine_line|#define KDATA_HALT_ACKNOWLEDGE          (KDATA_BASE_ADDR + 0x003A)
DECL|macro|KDATA_ADC1_XFER0
mdefine_line|#define KDATA_ADC1_XFER0                (KDATA_BASE_ADDR + 0x003B)
DECL|macro|KDATA_ADC1_XFER_ENDMARK
mdefine_line|#define KDATA_ADC1_XFER_ENDMARK         (KDATA_BASE_ADDR + 0x003C)
DECL|macro|KDATA_ADC1_LEFT_VOLUME
mdefine_line|#define KDATA_ADC1_LEFT_VOLUME&t;&t;&t;(KDATA_BASE_ADDR + 0x003D)
DECL|macro|KDATA_ADC1_RIGHT_VOLUME
mdefine_line|#define KDATA_ADC1_RIGHT_VOLUME  &t;&t;(KDATA_BASE_ADDR + 0x003E)
DECL|macro|KDATA_ADC1_LEFT_SUR_VOL
mdefine_line|#define KDATA_ADC1_LEFT_SUR_VOL&t;&t;&t;(KDATA_BASE_ADDR + 0x003F)
DECL|macro|KDATA_ADC1_RIGHT_SUR_VOL
mdefine_line|#define KDATA_ADC1_RIGHT_SUR_VOL&t;&t;(KDATA_BASE_ADDR + 0x0040)
DECL|macro|KDATA_ADC2_XFER0
mdefine_line|#define KDATA_ADC2_XFER0                (KDATA_BASE_ADDR + 0x0041)
DECL|macro|KDATA_ADC2_XFER_ENDMARK
mdefine_line|#define KDATA_ADC2_XFER_ENDMARK         (KDATA_BASE_ADDR + 0x0042)
DECL|macro|KDATA_ADC2_LEFT_VOLUME
mdefine_line|#define KDATA_ADC2_LEFT_VOLUME&t;&t;&t;(KDATA_BASE_ADDR + 0x0043)
DECL|macro|KDATA_ADC2_RIGHT_VOLUME
mdefine_line|#define KDATA_ADC2_RIGHT_VOLUME&t;&t;&t;(KDATA_BASE_ADDR + 0x0044)
DECL|macro|KDATA_ADC2_LEFT_SUR_VOL
mdefine_line|#define KDATA_ADC2_LEFT_SUR_VOL&t;&t;&t;(KDATA_BASE_ADDR + 0x0045)
DECL|macro|KDATA_ADC2_RIGHT_SUR_VOL
mdefine_line|#define KDATA_ADC2_RIGHT_SUR_VOL&t;&t;(KDATA_BASE_ADDR + 0x0046)
DECL|macro|KDATA_CD_XFER0
mdefine_line|#define KDATA_CD_XFER0&t;&t;&t;&t;&t;(KDATA_BASE_ADDR + 0x0047)&t;&t;&t;&t;&t;
DECL|macro|KDATA_CD_XFER_ENDMARK
mdefine_line|#define KDATA_CD_XFER_ENDMARK&t;&t;&t;(KDATA_BASE_ADDR + 0x0048)
DECL|macro|KDATA_CD_LEFT_VOLUME
mdefine_line|#define KDATA_CD_LEFT_VOLUME&t;&t;&t;(KDATA_BASE_ADDR + 0x0049)
DECL|macro|KDATA_CD_RIGHT_VOLUME
mdefine_line|#define KDATA_CD_RIGHT_VOLUME&t;&t;&t;(KDATA_BASE_ADDR + 0x004A)
DECL|macro|KDATA_CD_LEFT_SUR_VOL
mdefine_line|#define KDATA_CD_LEFT_SUR_VOL&t;&t;&t;(KDATA_BASE_ADDR + 0x004B)
DECL|macro|KDATA_CD_RIGHT_SUR_VOL
mdefine_line|#define KDATA_CD_RIGHT_SUR_VOL&t;&t;&t;(KDATA_BASE_ADDR + 0x004C)
DECL|macro|KDATA_MIC_XFER0
mdefine_line|#define KDATA_MIC_XFER0&t;&t;&t;&t;&t;(KDATA_BASE_ADDR + 0x004D)
DECL|macro|KDATA_MIC_XFER_ENDMARK
mdefine_line|#define KDATA_MIC_XFER_ENDMARK&t;&t;&t;(KDATA_BASE_ADDR + 0x004E)
DECL|macro|KDATA_MIC_VOLUME
mdefine_line|#define KDATA_MIC_VOLUME&t;&t;&t;&t;(KDATA_BASE_ADDR + 0x004F)
DECL|macro|KDATA_MIC_SUR_VOL
mdefine_line|#define KDATA_MIC_SUR_VOL&t;&t;&t;&t;(KDATA_BASE_ADDR + 0x0050)
DECL|macro|KDATA_I2S_XFER0
mdefine_line|#define KDATA_I2S_XFER0                 (KDATA_BASE_ADDR + 0x0051)
DECL|macro|KDATA_I2S_XFER_ENDMARK
mdefine_line|#define KDATA_I2S_XFER_ENDMARK          (KDATA_BASE_ADDR + 0x0052)
DECL|macro|KDATA_CHI_XFER0
mdefine_line|#define KDATA_CHI_XFER0                 (KDATA_BASE_ADDR + 0x0053)
DECL|macro|KDATA_CHI_XFER_ENDMARK
mdefine_line|#define KDATA_CHI_XFER_ENDMARK          (KDATA_BASE_ADDR + 0x0054)
DECL|macro|KDATA_SPDIF_XFER
mdefine_line|#define KDATA_SPDIF_XFER                (KDATA_BASE_ADDR + 0x0055)
DECL|macro|KDATA_SPDIF_CURRENT_FRAME
mdefine_line|#define KDATA_SPDIF_CURRENT_FRAME       (KDATA_BASE_ADDR + 0x0056)
DECL|macro|KDATA_SPDIF_FRAME0
mdefine_line|#define KDATA_SPDIF_FRAME0              (KDATA_BASE_ADDR + 0x0057)
DECL|macro|KDATA_SPDIF_FRAME1
mdefine_line|#define KDATA_SPDIF_FRAME1              (KDATA_BASE_ADDR + 0x0058)
DECL|macro|KDATA_SPDIF_FRAME2
mdefine_line|#define KDATA_SPDIF_FRAME2              (KDATA_BASE_ADDR + 0x0059)
DECL|macro|KDATA_SPDIF_REQUEST
mdefine_line|#define KDATA_SPDIF_REQUEST             (KDATA_BASE_ADDR + 0x005A)
DECL|macro|KDATA_SPDIF_TEMP
mdefine_line|#define KDATA_SPDIF_TEMP                (KDATA_BASE_ADDR + 0x005B)
DECL|macro|KDATA_SPDIFIN_XFER0
mdefine_line|#define KDATA_SPDIFIN_XFER0             (KDATA_BASE_ADDR + 0x005C)
DECL|macro|KDATA_SPDIFIN_XFER_ENDMARK
mdefine_line|#define KDATA_SPDIFIN_XFER_ENDMARK      (KDATA_BASE_ADDR + 0x005D)
DECL|macro|KDATA_SPDIFIN_INT_METER
mdefine_line|#define KDATA_SPDIFIN_INT_METER         (KDATA_BASE_ADDR + 0x005E)
DECL|macro|KDATA_DSP_RESET_COUNT
mdefine_line|#define KDATA_DSP_RESET_COUNT           (KDATA_BASE_ADDR + 0x005F)
DECL|macro|KDATA_DEBUG_OUTPUT
mdefine_line|#define KDATA_DEBUG_OUTPUT              (KDATA_BASE_ADDR + 0x0060)
DECL|macro|KDATA_KERNEL_ISR_LIST
mdefine_line|#define KDATA_KERNEL_ISR_LIST           (KDATA_BASE_ADDR + 0x0061)
DECL|macro|KDATA_KERNEL_ISR_CBSR1
mdefine_line|#define KDATA_KERNEL_ISR_CBSR1          (KDATA_BASE_ADDR + 0x0062)
DECL|macro|KDATA_KERNEL_ISR_CBER1
mdefine_line|#define KDATA_KERNEL_ISR_CBER1          (KDATA_BASE_ADDR + 0x0063)
DECL|macro|KDATA_KERNEL_ISR_CBCR
mdefine_line|#define KDATA_KERNEL_ISR_CBCR           (KDATA_BASE_ADDR + 0x0064)
DECL|macro|KDATA_KERNEL_ISR_AR0
mdefine_line|#define KDATA_KERNEL_ISR_AR0            (KDATA_BASE_ADDR + 0x0065)
DECL|macro|KDATA_KERNEL_ISR_AR1
mdefine_line|#define KDATA_KERNEL_ISR_AR1            (KDATA_BASE_ADDR + 0x0066)
DECL|macro|KDATA_KERNEL_ISR_AR2
mdefine_line|#define KDATA_KERNEL_ISR_AR2            (KDATA_BASE_ADDR + 0x0067)
DECL|macro|KDATA_KERNEL_ISR_AR3
mdefine_line|#define KDATA_KERNEL_ISR_AR3            (KDATA_BASE_ADDR + 0x0068)
DECL|macro|KDATA_KERNEL_ISR_AR4
mdefine_line|#define KDATA_KERNEL_ISR_AR4            (KDATA_BASE_ADDR + 0x0069)
DECL|macro|KDATA_KERNEL_ISR_AR5
mdefine_line|#define KDATA_KERNEL_ISR_AR5            (KDATA_BASE_ADDR + 0x006A)
DECL|macro|KDATA_KERNEL_ISR_BRCR
mdefine_line|#define KDATA_KERNEL_ISR_BRCR           (KDATA_BASE_ADDR + 0x006B)
DECL|macro|KDATA_KERNEL_ISR_PASR
mdefine_line|#define KDATA_KERNEL_ISR_PASR           (KDATA_BASE_ADDR + 0x006C)
DECL|macro|KDATA_KERNEL_ISR_PAER
mdefine_line|#define KDATA_KERNEL_ISR_PAER           (KDATA_BASE_ADDR + 0x006D)
DECL|macro|KDATA_CLIENT_SCRATCH0
mdefine_line|#define KDATA_CLIENT_SCRATCH0           (KDATA_BASE_ADDR + 0x006E)
DECL|macro|KDATA_CLIENT_SCRATCH1
mdefine_line|#define KDATA_CLIENT_SCRATCH1           (KDATA_BASE_ADDR + 0x006F)
DECL|macro|KDATA_KERNEL_SCRATCH
mdefine_line|#define KDATA_KERNEL_SCRATCH            (KDATA_BASE_ADDR + 0x0070)
DECL|macro|KDATA_KERNEL_ISR_SCRATCH
mdefine_line|#define KDATA_KERNEL_ISR_SCRATCH        (KDATA_BASE_ADDR + 0x0071)
DECL|macro|KDATA_OUEUE_LEFT
mdefine_line|#define KDATA_OUEUE_LEFT                (KDATA_BASE_ADDR + 0x0072)
DECL|macro|KDATA_QUEUE_RIGHT
mdefine_line|#define KDATA_QUEUE_RIGHT               (KDATA_BASE_ADDR + 0x0073)
DECL|macro|KDATA_ADC1_REQUEST
mdefine_line|#define KDATA_ADC1_REQUEST              (KDATA_BASE_ADDR + 0x0074)
DECL|macro|KDATA_ADC2_REQUEST
mdefine_line|#define KDATA_ADC2_REQUEST              (KDATA_BASE_ADDR + 0x0075)
DECL|macro|KDATA_CD_REQUEST
mdefine_line|#define KDATA_CD_REQUEST&t;&t;&t;&t;(KDATA_BASE_ADDR + 0x0076)
DECL|macro|KDATA_MIC_REQUEST
mdefine_line|#define KDATA_MIC_REQUEST&t;&t;&t;&t;(KDATA_BASE_ADDR + 0x0077)
DECL|macro|KDATA_ADC1_MIXER_REQUEST
mdefine_line|#define KDATA_ADC1_MIXER_REQUEST        (KDATA_BASE_ADDR + 0x0078)
DECL|macro|KDATA_ADC2_MIXER_REQUEST
mdefine_line|#define KDATA_ADC2_MIXER_REQUEST        (KDATA_BASE_ADDR + 0x0079)
DECL|macro|KDATA_CD_MIXER_REQUEST
mdefine_line|#define KDATA_CD_MIXER_REQUEST&t;&t;&t;(KDATA_BASE_ADDR + 0x007A)
DECL|macro|KDATA_MIC_MIXER_REQUEST
mdefine_line|#define KDATA_MIC_MIXER_REQUEST&t;&t;&t;(KDATA_BASE_ADDR + 0x007B)
DECL|macro|KDATA_MIC_SYNC_COUNTER
mdefine_line|#define KDATA_MIC_SYNC_COUNTER&t;&t;&t;(KDATA_BASE_ADDR + 0x007C)
multiline_comment|/*&n; * second &squot;segment&squot; (?) reserved for mixer&n; * buffers..&n; */
DECL|macro|KDATA_MIXER_WORD0
mdefine_line|#define KDATA_MIXER_WORD0               (KDATA_BASE_ADDR2 + 0x0000)
DECL|macro|KDATA_MIXER_WORD1
mdefine_line|#define KDATA_MIXER_WORD1               (KDATA_BASE_ADDR2 + 0x0001)
DECL|macro|KDATA_MIXER_WORD2
mdefine_line|#define KDATA_MIXER_WORD2               (KDATA_BASE_ADDR2 + 0x0002)
DECL|macro|KDATA_MIXER_WORD3
mdefine_line|#define KDATA_MIXER_WORD3               (KDATA_BASE_ADDR2 + 0x0003)
DECL|macro|KDATA_MIXER_WORD4
mdefine_line|#define KDATA_MIXER_WORD4               (KDATA_BASE_ADDR2 + 0x0004)
DECL|macro|KDATA_MIXER_WORD5
mdefine_line|#define KDATA_MIXER_WORD5               (KDATA_BASE_ADDR2 + 0x0005)
DECL|macro|KDATA_MIXER_WORD6
mdefine_line|#define KDATA_MIXER_WORD6               (KDATA_BASE_ADDR2 + 0x0006)
DECL|macro|KDATA_MIXER_WORD7
mdefine_line|#define KDATA_MIXER_WORD7               (KDATA_BASE_ADDR2 + 0x0007)
DECL|macro|KDATA_MIXER_WORD8
mdefine_line|#define KDATA_MIXER_WORD8               (KDATA_BASE_ADDR2 + 0x0008)
DECL|macro|KDATA_MIXER_WORD9
mdefine_line|#define KDATA_MIXER_WORD9               (KDATA_BASE_ADDR2 + 0x0009)
DECL|macro|KDATA_MIXER_WORDA
mdefine_line|#define KDATA_MIXER_WORDA               (KDATA_BASE_ADDR2 + 0x000A)
DECL|macro|KDATA_MIXER_WORDB
mdefine_line|#define KDATA_MIXER_WORDB               (KDATA_BASE_ADDR2 + 0x000B)
DECL|macro|KDATA_MIXER_WORDC
mdefine_line|#define KDATA_MIXER_WORDC               (KDATA_BASE_ADDR2 + 0x000C)
DECL|macro|KDATA_MIXER_WORDD
mdefine_line|#define KDATA_MIXER_WORDD               (KDATA_BASE_ADDR2 + 0x000D)
DECL|macro|KDATA_MIXER_WORDE
mdefine_line|#define KDATA_MIXER_WORDE               (KDATA_BASE_ADDR2 + 0x000E)
DECL|macro|KDATA_MIXER_WORDF
mdefine_line|#define KDATA_MIXER_WORDF               (KDATA_BASE_ADDR2 + 0x000F)
DECL|macro|KDATA_MIXER_XFER0
mdefine_line|#define KDATA_MIXER_XFER0               (KDATA_BASE_ADDR2 + 0x0010)
DECL|macro|KDATA_MIXER_XFER1
mdefine_line|#define KDATA_MIXER_XFER1               (KDATA_BASE_ADDR2 + 0x0011)
DECL|macro|KDATA_MIXER_XFER2
mdefine_line|#define KDATA_MIXER_XFER2               (KDATA_BASE_ADDR2 + 0x0012)
DECL|macro|KDATA_MIXER_XFER3
mdefine_line|#define KDATA_MIXER_XFER3               (KDATA_BASE_ADDR2 + 0x0013)
DECL|macro|KDATA_MIXER_XFER4
mdefine_line|#define KDATA_MIXER_XFER4               (KDATA_BASE_ADDR2 + 0x0014)
DECL|macro|KDATA_MIXER_XFER5
mdefine_line|#define KDATA_MIXER_XFER5               (KDATA_BASE_ADDR2 + 0x0015)
DECL|macro|KDATA_MIXER_XFER6
mdefine_line|#define KDATA_MIXER_XFER6               (KDATA_BASE_ADDR2 + 0x0016)
DECL|macro|KDATA_MIXER_XFER7
mdefine_line|#define KDATA_MIXER_XFER7               (KDATA_BASE_ADDR2 + 0x0017)
DECL|macro|KDATA_MIXER_XFER8
mdefine_line|#define KDATA_MIXER_XFER8               (KDATA_BASE_ADDR2 + 0x0018)
DECL|macro|KDATA_MIXER_XFER9
mdefine_line|#define KDATA_MIXER_XFER9               (KDATA_BASE_ADDR2 + 0x0019)
DECL|macro|KDATA_MIXER_XFER_ENDMARK
mdefine_line|#define KDATA_MIXER_XFER_ENDMARK        (KDATA_BASE_ADDR2 + 0x001A)
DECL|macro|KDATA_MIXER_TASK_NUMBER
mdefine_line|#define KDATA_MIXER_TASK_NUMBER         (KDATA_BASE_ADDR2 + 0x001B)
DECL|macro|KDATA_CURRENT_MIXER
mdefine_line|#define KDATA_CURRENT_MIXER             (KDATA_BASE_ADDR2 + 0x001C)
DECL|macro|KDATA_MIXER_ACTIVE
mdefine_line|#define KDATA_MIXER_ACTIVE              (KDATA_BASE_ADDR2 + 0x001D)
DECL|macro|KDATA_MIXER_BANK_STATUS
mdefine_line|#define KDATA_MIXER_BANK_STATUS         (KDATA_BASE_ADDR2 + 0x001E)
DECL|macro|KDATA_DAC_LEFT_VOLUME
mdefine_line|#define KDATA_DAC_LEFT_VOLUME&t;        (KDATA_BASE_ADDR2 + 0x001F)
DECL|macro|KDATA_DAC_RIGHT_VOLUME
mdefine_line|#define KDATA_DAC_RIGHT_VOLUME          (KDATA_BASE_ADDR2 + 0x0020)
DECL|macro|MAX_INSTANCE_MINISRC
mdefine_line|#define MAX_INSTANCE_MINISRC            (KDATA_INSTANCE_MINISRC_ENDMARK - KDATA_INSTANCE0_MINISRC)
DECL|macro|MAX_VIRTUAL_DMA_CHANNELS
mdefine_line|#define MAX_VIRTUAL_DMA_CHANNELS        (KDATA_DMA_XFER_ENDMARK - KDATA_DMA_XFER0)
DECL|macro|MAX_VIRTUAL_MIXER_CHANNELS
mdefine_line|#define MAX_VIRTUAL_MIXER_CHANNELS      (KDATA_MIXER_XFER_ENDMARK - KDATA_MIXER_XFER0)
DECL|macro|MAX_VIRTUAL_ADC1_CHANNELS
mdefine_line|#define MAX_VIRTUAL_ADC1_CHANNELS       (KDATA_ADC1_XFER_ENDMARK - KDATA_ADC1_XFER0)
multiline_comment|/*&n; * client data area offsets&n; */
DECL|macro|CDATA_INSTANCE_READY
mdefine_line|#define CDATA_INSTANCE_READY            0x00
DECL|macro|CDATA_HOST_SRC_ADDRL
mdefine_line|#define CDATA_HOST_SRC_ADDRL            0x01
DECL|macro|CDATA_HOST_SRC_ADDRH
mdefine_line|#define CDATA_HOST_SRC_ADDRH            0x02
DECL|macro|CDATA_HOST_SRC_END_PLUS_1L
mdefine_line|#define CDATA_HOST_SRC_END_PLUS_1L      0x03
DECL|macro|CDATA_HOST_SRC_END_PLUS_1H
mdefine_line|#define CDATA_HOST_SRC_END_PLUS_1H      0x04
DECL|macro|CDATA_HOST_SRC_CURRENTL
mdefine_line|#define CDATA_HOST_SRC_CURRENTL         0x05
DECL|macro|CDATA_HOST_SRC_CURRENTH
mdefine_line|#define CDATA_HOST_SRC_CURRENTH         0x06
DECL|macro|CDATA_IN_BUF_CONNECT
mdefine_line|#define CDATA_IN_BUF_CONNECT            0x07
DECL|macro|CDATA_OUT_BUF_CONNECT
mdefine_line|#define CDATA_OUT_BUF_CONNECT           0x08
DECL|macro|CDATA_IN_BUF_BEGIN
mdefine_line|#define CDATA_IN_BUF_BEGIN              0x09
DECL|macro|CDATA_IN_BUF_END_PLUS_1
mdefine_line|#define CDATA_IN_BUF_END_PLUS_1         0x0A
DECL|macro|CDATA_IN_BUF_HEAD
mdefine_line|#define CDATA_IN_BUF_HEAD               0x0B
DECL|macro|CDATA_IN_BUF_TAIL
mdefine_line|#define CDATA_IN_BUF_TAIL               0x0C
DECL|macro|CDATA_OUT_BUF_BEGIN
mdefine_line|#define CDATA_OUT_BUF_BEGIN             0x0D
DECL|macro|CDATA_OUT_BUF_END_PLUS_1
mdefine_line|#define CDATA_OUT_BUF_END_PLUS_1        0x0E
DECL|macro|CDATA_OUT_BUF_HEAD
mdefine_line|#define CDATA_OUT_BUF_HEAD              0x0F
DECL|macro|CDATA_OUT_BUF_TAIL
mdefine_line|#define CDATA_OUT_BUF_TAIL              0x10
DECL|macro|CDATA_DMA_CONTROL
mdefine_line|#define CDATA_DMA_CONTROL               0x11
DECL|macro|CDATA_RESERVED
mdefine_line|#define CDATA_RESERVED                  0x12
DECL|macro|CDATA_FREQUENCY
mdefine_line|#define CDATA_FREQUENCY                 0x13
DECL|macro|CDATA_LEFT_VOLUME
mdefine_line|#define CDATA_LEFT_VOLUME               0x14
DECL|macro|CDATA_RIGHT_VOLUME
mdefine_line|#define CDATA_RIGHT_VOLUME              0x15
DECL|macro|CDATA_LEFT_SUR_VOL
mdefine_line|#define CDATA_LEFT_SUR_VOL              0x16
DECL|macro|CDATA_RIGHT_SUR_VOL
mdefine_line|#define CDATA_RIGHT_SUR_VOL             0x17
DECL|macro|CDATA_HEADER_LEN
mdefine_line|#define CDATA_HEADER_LEN                0x18
DECL|macro|SRC3_DIRECTION_OFFSET
mdefine_line|#define SRC3_DIRECTION_OFFSET           CDATA_HEADER_LEN
DECL|macro|SRC3_MODE_OFFSET
mdefine_line|#define SRC3_MODE_OFFSET                (CDATA_HEADER_LEN + 1)
DECL|macro|SRC3_WORD_LENGTH_OFFSET
mdefine_line|#define SRC3_WORD_LENGTH_OFFSET         (CDATA_HEADER_LEN + 2)
DECL|macro|SRC3_PARAMETER_OFFSET
mdefine_line|#define SRC3_PARAMETER_OFFSET           (CDATA_HEADER_LEN + 3)
DECL|macro|SRC3_COEFF_ADDR_OFFSET
mdefine_line|#define SRC3_COEFF_ADDR_OFFSET          (CDATA_HEADER_LEN + 8)
DECL|macro|SRC3_FILTAP_ADDR_OFFSET
mdefine_line|#define SRC3_FILTAP_ADDR_OFFSET         (CDATA_HEADER_LEN + 10)
DECL|macro|SRC3_TEMP_INBUF_ADDR_OFFSET
mdefine_line|#define SRC3_TEMP_INBUF_ADDR_OFFSET     (CDATA_HEADER_LEN + 16)
DECL|macro|SRC3_TEMP_OUTBUF_ADDR_OFFSET
mdefine_line|#define SRC3_TEMP_OUTBUF_ADDR_OFFSET    (CDATA_HEADER_LEN + 17)
DECL|macro|MINISRC_IN_BUFFER_SIZE
mdefine_line|#define MINISRC_IN_BUFFER_SIZE   ( 0x50 * 2 )
DECL|macro|MINISRC_OUT_BUFFER_SIZE
mdefine_line|#define MINISRC_OUT_BUFFER_SIZE  ( 0x50 * 2 * 2)
DECL|macro|MINISRC_OUT_BUFFER_SIZE
mdefine_line|#define MINISRC_OUT_BUFFER_SIZE  ( 0x50 * 2 * 2)
DECL|macro|MINISRC_TMP_BUFFER_SIZE
mdefine_line|#define MINISRC_TMP_BUFFER_SIZE  ( 112 + ( MINISRC_BIQUAD_STAGE * 3 + 4 ) * 2 * 2 )
DECL|macro|MINISRC_BIQUAD_STAGE
mdefine_line|#define MINISRC_BIQUAD_STAGE    2
DECL|macro|MINISRC_COEF_LOC
mdefine_line|#define MINISRC_COEF_LOC          0X175
DECL|macro|DMACONTROL_BLOCK_MASK
mdefine_line|#define DMACONTROL_BLOCK_MASK           0x000F
DECL|macro|DMAC_BLOCK0_SELECTOR
mdefine_line|#define  DMAC_BLOCK0_SELECTOR           0x0000
DECL|macro|DMAC_BLOCK1_SELECTOR
mdefine_line|#define  DMAC_BLOCK1_SELECTOR           0x0001
DECL|macro|DMAC_BLOCK2_SELECTOR
mdefine_line|#define  DMAC_BLOCK2_SELECTOR           0x0002
DECL|macro|DMAC_BLOCK3_SELECTOR
mdefine_line|#define  DMAC_BLOCK3_SELECTOR           0x0003
DECL|macro|DMAC_BLOCK4_SELECTOR
mdefine_line|#define  DMAC_BLOCK4_SELECTOR           0x0004
DECL|macro|DMAC_BLOCK5_SELECTOR
mdefine_line|#define  DMAC_BLOCK5_SELECTOR           0x0005
DECL|macro|DMAC_BLOCK6_SELECTOR
mdefine_line|#define  DMAC_BLOCK6_SELECTOR           0x0006
DECL|macro|DMAC_BLOCK7_SELECTOR
mdefine_line|#define  DMAC_BLOCK7_SELECTOR           0x0007
DECL|macro|DMAC_BLOCK8_SELECTOR
mdefine_line|#define  DMAC_BLOCK8_SELECTOR           0x0008
DECL|macro|DMAC_BLOCK9_SELECTOR
mdefine_line|#define  DMAC_BLOCK9_SELECTOR           0x0009
DECL|macro|DMAC_BLOCKA_SELECTOR
mdefine_line|#define  DMAC_BLOCKA_SELECTOR           0x000A
DECL|macro|DMAC_BLOCKB_SELECTOR
mdefine_line|#define  DMAC_BLOCKB_SELECTOR           0x000B
DECL|macro|DMAC_BLOCKC_SELECTOR
mdefine_line|#define  DMAC_BLOCKC_SELECTOR           0x000C
DECL|macro|DMAC_BLOCKD_SELECTOR
mdefine_line|#define  DMAC_BLOCKD_SELECTOR           0x000D
DECL|macro|DMAC_BLOCKE_SELECTOR
mdefine_line|#define  DMAC_BLOCKE_SELECTOR           0x000E
DECL|macro|DMAC_BLOCKF_SELECTOR
mdefine_line|#define  DMAC_BLOCKF_SELECTOR           0x000F
DECL|macro|DMACONTROL_PAGE_MASK
mdefine_line|#define DMACONTROL_PAGE_MASK            0x00F0
DECL|macro|DMAC_PAGE0_SELECTOR
mdefine_line|#define  DMAC_PAGE0_SELECTOR            0x0030
DECL|macro|DMAC_PAGE1_SELECTOR
mdefine_line|#define  DMAC_PAGE1_SELECTOR            0x0020
DECL|macro|DMAC_PAGE2_SELECTOR
mdefine_line|#define  DMAC_PAGE2_SELECTOR            0x0010
DECL|macro|DMAC_PAGE3_SELECTOR
mdefine_line|#define  DMAC_PAGE3_SELECTOR            0x0000
DECL|macro|DMACONTROL_AUTOREPEAT
mdefine_line|#define DMACONTROL_AUTOREPEAT           0x1000
DECL|macro|DMACONTROL_STOPPED
mdefine_line|#define DMACONTROL_STOPPED              0x2000
DECL|macro|DMACONTROL_DIRECTION
mdefine_line|#define DMACONTROL_DIRECTION            0x0100
multiline_comment|/*&n; * DSP Code images&n; */
DECL|variable|assp_kernel_image
id|u16
id|assp_kernel_image
(braket
)braket
op_assign
(brace
l_int|0x7980
comma
l_int|0x0030
comma
l_int|0x7980
comma
l_int|0x03B4
comma
l_int|0x7980
comma
l_int|0x03B4
comma
l_int|0x7980
comma
l_int|0x00FB
comma
l_int|0x7980
comma
l_int|0x00DD
comma
l_int|0x7980
comma
l_int|0x03B4
comma
l_int|0x7980
comma
l_int|0x0332
comma
l_int|0x7980
comma
l_int|0x0287
comma
l_int|0x7980
comma
l_int|0x03B4
comma
l_int|0x7980
comma
l_int|0x03B4
comma
l_int|0x7980
comma
l_int|0x03B4
comma
l_int|0x7980
comma
l_int|0x03B4
comma
l_int|0x7980
comma
l_int|0x031A
comma
l_int|0x7980
comma
l_int|0x03B4
comma
l_int|0x7980
comma
l_int|0x022F
comma
l_int|0x7980
comma
l_int|0x03B4
comma
l_int|0x7980
comma
l_int|0x03B4
comma
l_int|0x7980
comma
l_int|0x03B4
comma
l_int|0x7980
comma
l_int|0x03B4
comma
l_int|0x7980
comma
l_int|0x03B4
comma
l_int|0x7980
comma
l_int|0x0063
comma
l_int|0x7980
comma
l_int|0x006B
comma
l_int|0x7980
comma
l_int|0x03B4
comma
l_int|0x7980
comma
l_int|0x03B4
comma
l_int|0xBF80
comma
l_int|0x2C7C
comma
l_int|0x8806
comma
l_int|0x8804
comma
l_int|0xBE40
comma
l_int|0xBC20
comma
l_int|0xAE09
comma
l_int|0x1000
comma
l_int|0xAE0A
comma
l_int|0x0001
comma
l_int|0x6938
comma
l_int|0xEB08
comma
l_int|0x0053
comma
l_int|0x695A
comma
l_int|0xEB08
comma
l_int|0x00D6
comma
l_int|0x0009
comma
l_int|0x8B88
comma
l_int|0x6980
comma
l_int|0xE388
comma
l_int|0x0036
comma
l_int|0xBE30
comma
l_int|0xBC20
comma
l_int|0x6909
comma
l_int|0xB801
comma
l_int|0x9009
comma
l_int|0xBE41
comma
l_int|0xBE41
comma
l_int|0x6928
comma
l_int|0xEB88
comma
l_int|0x0078
comma
l_int|0xBE41
comma
l_int|0xBE40
comma
l_int|0x7980
comma
l_int|0x0038
comma
l_int|0xBE41
comma
l_int|0xBE41
comma
l_int|0x903A
comma
l_int|0x6938
comma
l_int|0xE308
comma
l_int|0x0056
comma
l_int|0x903A
comma
l_int|0xBE41
comma
l_int|0xBE40
comma
l_int|0xEF00
comma
l_int|0x903A
comma
l_int|0x6939
comma
l_int|0xE308
comma
l_int|0x005E
comma
l_int|0x903A
comma
l_int|0xEF00
comma
l_int|0x690B
comma
l_int|0x660C
comma
l_int|0xEF8C
comma
l_int|0x690A
comma
l_int|0x660C
comma
l_int|0x620B
comma
l_int|0x6609
comma
l_int|0xEF00
comma
l_int|0x6910
comma
l_int|0x660F
comma
l_int|0xEF04
comma
l_int|0xE388
comma
l_int|0x0075
comma
l_int|0x690E
comma
l_int|0x660F
comma
l_int|0x6210
comma
l_int|0x660D
comma
l_int|0xEF00
comma
l_int|0x690E
comma
l_int|0x660D
comma
l_int|0xEF00
comma
l_int|0xAE70
comma
l_int|0x0001
comma
l_int|0xBC20
comma
l_int|0xAE27
comma
l_int|0x0001
comma
l_int|0x6939
comma
l_int|0xEB08
comma
l_int|0x005D
comma
l_int|0x6926
comma
l_int|0xB801
comma
l_int|0x9026
comma
l_int|0x0026
comma
l_int|0x8B88
comma
l_int|0x6980
comma
l_int|0xE388
comma
l_int|0x00CB
comma
l_int|0x9028
comma
l_int|0x0D28
comma
l_int|0x4211
comma
l_int|0xE100
comma
l_int|0x007A
comma
l_int|0x4711
comma
l_int|0xE100
comma
l_int|0x00A0
comma
l_int|0x7A80
comma
l_int|0x0063
comma
l_int|0xB811
comma
l_int|0x660A
comma
l_int|0x6209
comma
l_int|0xE304
comma
l_int|0x007A
comma
l_int|0x0C0B
comma
l_int|0x4005
comma
l_int|0x100A
comma
l_int|0xBA01
comma
l_int|0x9012
comma
l_int|0x0C12
comma
l_int|0x4002
comma
l_int|0x7980
comma
l_int|0x00AF
comma
l_int|0x7A80
comma
l_int|0x006B
comma
l_int|0xBE02
comma
l_int|0x620E
comma
l_int|0x660D
comma
l_int|0xBA10
comma
l_int|0xE344
comma
l_int|0x007A
comma
l_int|0x0C10
comma
l_int|0x4005
comma
l_int|0x100E
comma
l_int|0xBA01
comma
l_int|0x9012
comma
l_int|0x0C12
comma
l_int|0x4002
comma
l_int|0x1003
comma
l_int|0xBA02
comma
l_int|0x9012
comma
l_int|0x0C12
comma
l_int|0x4000
comma
l_int|0x1003
comma
l_int|0xE388
comma
l_int|0x00BA
comma
l_int|0x1004
comma
l_int|0x7980
comma
l_int|0x00BC
comma
l_int|0x1004
comma
l_int|0xBA01
comma
l_int|0x9012
comma
l_int|0x0C12
comma
l_int|0x4001
comma
l_int|0x0C05
comma
l_int|0x4003
comma
l_int|0x0C06
comma
l_int|0x4004
comma
l_int|0x1011
comma
l_int|0xBFB0
comma
l_int|0x01FF
comma
l_int|0x9012
comma
l_int|0x0C12
comma
l_int|0x4006
comma
l_int|0xBC20
comma
l_int|0xEF00
comma
l_int|0xAE26
comma
l_int|0x1028
comma
l_int|0x6970
comma
l_int|0xBFD0
comma
l_int|0x0001
comma
l_int|0x9070
comma
l_int|0xE388
comma
l_int|0x007A
comma
l_int|0xAE28
comma
l_int|0x0000
comma
l_int|0xEF00
comma
l_int|0xAE70
comma
l_int|0x0300
comma
l_int|0x0C70
comma
l_int|0xB00C
comma
l_int|0xAE5A
comma
l_int|0x0000
comma
l_int|0xEF00
comma
l_int|0x7A80
comma
l_int|0x038A
comma
l_int|0x697F
comma
l_int|0xB801
comma
l_int|0x907F
comma
l_int|0x0056
comma
l_int|0x8B88
comma
l_int|0x0CA0
comma
l_int|0xB008
comma
l_int|0xAF71
comma
l_int|0xB000
comma
l_int|0x4E71
comma
l_int|0xE200
comma
l_int|0x00F3
comma
l_int|0xAE56
comma
l_int|0x1057
comma
l_int|0x0056
comma
l_int|0x0CA0
comma
l_int|0xB008
comma
l_int|0x8056
comma
l_int|0x7980
comma
l_int|0x03A1
comma
l_int|0x0810
comma
l_int|0xBFA0
comma
l_int|0x1059
comma
l_int|0xE304
comma
l_int|0x03A1
comma
l_int|0x8056
comma
l_int|0x7980
comma
l_int|0x03A1
comma
l_int|0x7A80
comma
l_int|0x038A
comma
l_int|0xBF01
comma
l_int|0xBE43
comma
l_int|0xBE59
comma
l_int|0x907C
comma
l_int|0x6937
comma
l_int|0xE388
comma
l_int|0x010D
comma
l_int|0xBA01
comma
l_int|0xE308
comma
l_int|0x010C
comma
l_int|0xAE71
comma
l_int|0x0004
comma
l_int|0x0C71
comma
l_int|0x5000
comma
l_int|0x6936
comma
l_int|0x9037
comma
l_int|0xBF0A
comma
l_int|0x109E
comma
l_int|0x8B8A
comma
l_int|0xAF80
comma
l_int|0x8014
comma
l_int|0x4C80
comma
l_int|0xBF0A
comma
l_int|0x0560
comma
l_int|0xF500
comma
l_int|0xBF0A
comma
l_int|0x0520
comma
l_int|0xB900
comma
l_int|0xBB17
comma
l_int|0x90A0
comma
l_int|0x6917
comma
l_int|0xE388
comma
l_int|0x0148
comma
l_int|0x0D17
comma
l_int|0xE100
comma
l_int|0x0127
comma
l_int|0xBF0C
comma
l_int|0x0578
comma
l_int|0xBF0D
comma
l_int|0x057C
comma
l_int|0x7980
comma
l_int|0x012B
comma
l_int|0xBF0C
comma
l_int|0x0538
comma
l_int|0xBF0D
comma
l_int|0x053C
comma
l_int|0x6900
comma
l_int|0xE308
comma
l_int|0x0135
comma
l_int|0x8B8C
comma
l_int|0xBE59
comma
l_int|0xBB07
comma
l_int|0x90A0
comma
l_int|0xBC20
comma
l_int|0x7980
comma
l_int|0x0157
comma
l_int|0x030C
comma
l_int|0x8B8B
comma
l_int|0xB903
comma
l_int|0x8809
comma
l_int|0xBEC6
comma
l_int|0x013E
comma
l_int|0x69AC
comma
l_int|0x90AB
comma
l_int|0x69AD
comma
l_int|0x90AB
comma
l_int|0x0813
comma
l_int|0x660A
comma
l_int|0xE344
comma
l_int|0x0144
comma
l_int|0x0309
comma
l_int|0x830C
comma
l_int|0xBC20
comma
l_int|0x7980
comma
l_int|0x0157
comma
l_int|0x6955
comma
l_int|0xE388
comma
l_int|0x0157
comma
l_int|0x7C38
comma
l_int|0xBF0B
comma
l_int|0x0578
comma
l_int|0xF500
comma
l_int|0xBF0B
comma
l_int|0x0538
comma
l_int|0xB907
comma
l_int|0x8809
comma
l_int|0xBEC6
comma
l_int|0x0156
comma
l_int|0x10AB
comma
l_int|0x90AA
comma
l_int|0x6974
comma
l_int|0xE388
comma
l_int|0x0163
comma
l_int|0xAE72
comma
l_int|0x0540
comma
l_int|0xF500
comma
l_int|0xAE72
comma
l_int|0x0500
comma
l_int|0xAE61
comma
l_int|0x103B
comma
l_int|0x7A80
comma
l_int|0x02F6
comma
l_int|0x6978
comma
l_int|0xE388
comma
l_int|0x0182
comma
l_int|0x8B8C
comma
l_int|0xBF0C
comma
l_int|0x0560
comma
l_int|0xE500
comma
l_int|0x7C40
comma
l_int|0x0814
comma
l_int|0xBA20
comma
l_int|0x8812
comma
l_int|0x733D
comma
l_int|0x7A80
comma
l_int|0x0380
comma
l_int|0x733E
comma
l_int|0x7A80
comma
l_int|0x0380
comma
l_int|0x8B8C
comma
l_int|0xBF0C
comma
l_int|0x056C
comma
l_int|0xE500
comma
l_int|0x7C40
comma
l_int|0x0814
comma
l_int|0xBA2C
comma
l_int|0x8812
comma
l_int|0x733F
comma
l_int|0x7A80
comma
l_int|0x0380
comma
l_int|0x7340
comma
l_int|0x7A80
comma
l_int|0x0380
comma
l_int|0x6975
comma
l_int|0xE388
comma
l_int|0x018E
comma
l_int|0xAE72
comma
l_int|0x0548
comma
l_int|0xF500
comma
l_int|0xAE72
comma
l_int|0x0508
comma
l_int|0xAE61
comma
l_int|0x1041
comma
l_int|0x7A80
comma
l_int|0x02F6
comma
l_int|0x6979
comma
l_int|0xE388
comma
l_int|0x01AD
comma
l_int|0x8B8C
comma
l_int|0xBF0C
comma
l_int|0x0560
comma
l_int|0xE500
comma
l_int|0x7C40
comma
l_int|0x0814
comma
l_int|0xBA18
comma
l_int|0x8812
comma
l_int|0x7343
comma
l_int|0x7A80
comma
l_int|0x0380
comma
l_int|0x7344
comma
l_int|0x7A80
comma
l_int|0x0380
comma
l_int|0x8B8C
comma
l_int|0xBF0C
comma
l_int|0x056C
comma
l_int|0xE500
comma
l_int|0x7C40
comma
l_int|0x0814
comma
l_int|0xBA24
comma
l_int|0x8812
comma
l_int|0x7345
comma
l_int|0x7A80
comma
l_int|0x0380
comma
l_int|0x7346
comma
l_int|0x7A80
comma
l_int|0x0380
comma
l_int|0x6976
comma
l_int|0xE388
comma
l_int|0x01B9
comma
l_int|0xAE72
comma
l_int|0x0558
comma
l_int|0xF500
comma
l_int|0xAE72
comma
l_int|0x0518
comma
l_int|0xAE61
comma
l_int|0x1047
comma
l_int|0x7A80
comma
l_int|0x02F6
comma
l_int|0x697A
comma
l_int|0xE388
comma
l_int|0x01D8
comma
l_int|0x8B8C
comma
l_int|0xBF0C
comma
l_int|0x0560
comma
l_int|0xE500
comma
l_int|0x7C40
comma
l_int|0x0814
comma
l_int|0xBA08
comma
l_int|0x8812
comma
l_int|0x7349
comma
l_int|0x7A80
comma
l_int|0x0380
comma
l_int|0x734A
comma
l_int|0x7A80
comma
l_int|0x0380
comma
l_int|0x8B8C
comma
l_int|0xBF0C
comma
l_int|0x056C
comma
l_int|0xE500
comma
l_int|0x7C40
comma
l_int|0x0814
comma
l_int|0xBA14
comma
l_int|0x8812
comma
l_int|0x734B
comma
l_int|0x7A80
comma
l_int|0x0380
comma
l_int|0x734C
comma
l_int|0x7A80
comma
l_int|0x0380
comma
l_int|0xBC21
comma
l_int|0xAE1C
comma
l_int|0x1090
comma
l_int|0x8B8A
comma
l_int|0xBF0A
comma
l_int|0x0560
comma
l_int|0xE500
comma
l_int|0x7C40
comma
l_int|0x0812
comma
l_int|0xB804
comma
l_int|0x8813
comma
l_int|0x8B8D
comma
l_int|0xBF0D
comma
l_int|0x056C
comma
l_int|0xE500
comma
l_int|0x7C40
comma
l_int|0x0815
comma
l_int|0xB804
comma
l_int|0x8811
comma
l_int|0x7A80
comma
l_int|0x034A
comma
l_int|0x8B8A
comma
l_int|0xBF0A
comma
l_int|0x0560
comma
l_int|0xE500
comma
l_int|0x7C40
comma
l_int|0x731F
comma
l_int|0xB903
comma
l_int|0x8809
comma
l_int|0xBEC6
comma
l_int|0x01F9
comma
l_int|0x548A
comma
l_int|0xBE03
comma
l_int|0x98A0
comma
l_int|0x7320
comma
l_int|0xB903
comma
l_int|0x8809
comma
l_int|0xBEC6
comma
l_int|0x0201
comma
l_int|0x548A
comma
l_int|0xBE03
comma
l_int|0x98A0
comma
l_int|0x1F20
comma
l_int|0x2F1F
comma
l_int|0x9826
comma
l_int|0xBC20
comma
l_int|0x6935
comma
l_int|0xE388
comma
l_int|0x03A1
comma
l_int|0x6933
comma
l_int|0xB801
comma
l_int|0x9033
comma
l_int|0xBFA0
comma
l_int|0x02EE
comma
l_int|0xE308
comma
l_int|0x03A1
comma
l_int|0x9033
comma
l_int|0xBF00
comma
l_int|0x6951
comma
l_int|0xE388
comma
l_int|0x021F
comma
l_int|0x7334
comma
l_int|0xBE80
comma
l_int|0x5760
comma
l_int|0xBE03
comma
l_int|0x9F7E
comma
l_int|0xBE59
comma
l_int|0x9034
comma
l_int|0x697E
comma
l_int|0x0D51
comma
l_int|0x9013
comma
l_int|0xBC20
comma
l_int|0x695C
comma
l_int|0xE388
comma
l_int|0x03A1
comma
l_int|0x735E
comma
l_int|0xBE80
comma
l_int|0x5760
comma
l_int|0xBE03
comma
l_int|0x9F7E
comma
l_int|0xBE59
comma
l_int|0x905E
comma
l_int|0x697E
comma
l_int|0x0D5C
comma
l_int|0x9013
comma
l_int|0x7980
comma
l_int|0x03A1
comma
l_int|0x7A80
comma
l_int|0x038A
comma
l_int|0xBF01
comma
l_int|0xBE43
comma
l_int|0x6977
comma
l_int|0xE388
comma
l_int|0x024E
comma
l_int|0xAE61
comma
l_int|0x104D
comma
l_int|0x0061
comma
l_int|0x8B88
comma
l_int|0x6980
comma
l_int|0xE388
comma
l_int|0x024E
comma
l_int|0x9071
comma
l_int|0x0D71
comma
l_int|0x000B
comma
l_int|0xAFA0
comma
l_int|0x8010
comma
l_int|0xAFA0
comma
l_int|0x8010
comma
l_int|0x0810
comma
l_int|0x660A
comma
l_int|0xE308
comma
l_int|0x0249
comma
l_int|0x0009
comma
l_int|0x0810
comma
l_int|0x660C
comma
l_int|0xE388
comma
l_int|0x024E
comma
l_int|0x800B
comma
l_int|0xBC20
comma
l_int|0x697B
comma
l_int|0xE388
comma
l_int|0x03A1
comma
l_int|0xBF0A
comma
l_int|0x109E
comma
l_int|0x8B8A
comma
l_int|0xAF80
comma
l_int|0x8014
comma
l_int|0x4C80
comma
l_int|0xE100
comma
l_int|0x0266
comma
l_int|0x697C
comma
l_int|0xBF90
comma
l_int|0x0560
comma
l_int|0x9072
comma
l_int|0x0372
comma
l_int|0x697C
comma
l_int|0xBF90
comma
l_int|0x0564
comma
l_int|0x9073
comma
l_int|0x0473
comma
l_int|0x7980
comma
l_int|0x0270
comma
l_int|0x697C
comma
l_int|0xBF90
comma
l_int|0x0520
comma
l_int|0x9072
comma
l_int|0x0372
comma
l_int|0x697C
comma
l_int|0xBF90
comma
l_int|0x0524
comma
l_int|0x9073
comma
l_int|0x0473
comma
l_int|0x697C
comma
l_int|0xB801
comma
l_int|0x907C
comma
l_int|0xBF0A
comma
l_int|0x10FD
comma
l_int|0x8B8A
comma
l_int|0xAF80
comma
l_int|0x8010
comma
l_int|0x734F
comma
l_int|0x548A
comma
l_int|0xBE03
comma
l_int|0x9880
comma
l_int|0xBC21
comma
l_int|0x7326
comma
l_int|0x548B
comma
l_int|0xBE03
comma
l_int|0x618B
comma
l_int|0x988C
comma
l_int|0xBE03
comma
l_int|0x6180
comma
l_int|0x9880
comma
l_int|0x7980
comma
l_int|0x03A1
comma
l_int|0x7A80
comma
l_int|0x038A
comma
l_int|0x0D28
comma
l_int|0x4711
comma
l_int|0xE100
comma
l_int|0x02BE
comma
l_int|0xAF12
comma
l_int|0x4006
comma
l_int|0x6912
comma
l_int|0xBFB0
comma
l_int|0x0C00
comma
l_int|0xE388
comma
l_int|0x02B6
comma
l_int|0xBFA0
comma
l_int|0x0800
comma
l_int|0xE388
comma
l_int|0x02B2
comma
l_int|0x6912
comma
l_int|0xBFB0
comma
l_int|0x0C00
comma
l_int|0xBFA0
comma
l_int|0x0400
comma
l_int|0xE388
comma
l_int|0x02A3
comma
l_int|0x6909
comma
l_int|0x900B
comma
l_int|0x7980
comma
l_int|0x02A5
comma
l_int|0xAF0B
comma
l_int|0x4005
comma
l_int|0x6901
comma
l_int|0x9005
comma
l_int|0x6902
comma
l_int|0x9006
comma
l_int|0x4311
comma
l_int|0xE100
comma
l_int|0x02ED
comma
l_int|0x6911
comma
l_int|0xBFC0
comma
l_int|0x2000
comma
l_int|0x9011
comma
l_int|0x7980
comma
l_int|0x02ED
comma
l_int|0x6909
comma
l_int|0x900B
comma
l_int|0x7980
comma
l_int|0x02B8
comma
l_int|0xAF0B
comma
l_int|0x4005
comma
l_int|0xAF05
comma
l_int|0x4003
comma
l_int|0xAF06
comma
l_int|0x4004
comma
l_int|0x7980
comma
l_int|0x02ED
comma
l_int|0xAF12
comma
l_int|0x4006
comma
l_int|0x6912
comma
l_int|0xBFB0
comma
l_int|0x0C00
comma
l_int|0xE388
comma
l_int|0x02E7
comma
l_int|0xBFA0
comma
l_int|0x0800
comma
l_int|0xE388
comma
l_int|0x02E3
comma
l_int|0x6912
comma
l_int|0xBFB0
comma
l_int|0x0C00
comma
l_int|0xBFA0
comma
l_int|0x0400
comma
l_int|0xE388
comma
l_int|0x02D4
comma
l_int|0x690D
comma
l_int|0x9010
comma
l_int|0x7980
comma
l_int|0x02D6
comma
l_int|0xAF10
comma
l_int|0x4005
comma
l_int|0x6901
comma
l_int|0x9005
comma
l_int|0x6902
comma
l_int|0x9006
comma
l_int|0x4311
comma
l_int|0xE100
comma
l_int|0x02ED
comma
l_int|0x6911
comma
l_int|0xBFC0
comma
l_int|0x2000
comma
l_int|0x9011
comma
l_int|0x7980
comma
l_int|0x02ED
comma
l_int|0x690D
comma
l_int|0x9010
comma
l_int|0x7980
comma
l_int|0x02E9
comma
l_int|0xAF10
comma
l_int|0x4005
comma
l_int|0xAF05
comma
l_int|0x4003
comma
l_int|0xAF06
comma
l_int|0x4004
comma
l_int|0xBC20
comma
l_int|0x6970
comma
l_int|0x9071
comma
l_int|0x7A80
comma
l_int|0x0078
comma
l_int|0x6971
comma
l_int|0x9070
comma
l_int|0x7980
comma
l_int|0x03A1
comma
l_int|0xBC20
comma
l_int|0x0361
comma
l_int|0x8B8B
comma
l_int|0x6980
comma
l_int|0xEF88
comma
l_int|0x0272
comma
l_int|0x0372
comma
l_int|0x7804
comma
l_int|0x9071
comma
l_int|0x0D71
comma
l_int|0x8B8A
comma
l_int|0x000B
comma
l_int|0xB903
comma
l_int|0x8809
comma
l_int|0xBEC6
comma
l_int|0x0309
comma
l_int|0x69A8
comma
l_int|0x90AB
comma
l_int|0x69A8
comma
l_int|0x90AA
comma
l_int|0x0810
comma
l_int|0x660A
comma
l_int|0xE344
comma
l_int|0x030F
comma
l_int|0x0009
comma
l_int|0x0810
comma
l_int|0x660C
comma
l_int|0xE388
comma
l_int|0x0314
comma
l_int|0x800B
comma
l_int|0xBC20
comma
l_int|0x6961
comma
l_int|0xB801
comma
l_int|0x9061
comma
l_int|0x7980
comma
l_int|0x02F7
comma
l_int|0x7A80
comma
l_int|0x038A
comma
l_int|0x5D35
comma
l_int|0x0001
comma
l_int|0x6934
comma
l_int|0xB801
comma
l_int|0x9034
comma
l_int|0xBF0A
comma
l_int|0x109E
comma
l_int|0x8B8A
comma
l_int|0xAF80
comma
l_int|0x8014
comma
l_int|0x4880
comma
l_int|0xAE72
comma
l_int|0x0550
comma
l_int|0xF500
comma
l_int|0xAE72
comma
l_int|0x0510
comma
l_int|0xAE61
comma
l_int|0x1051
comma
l_int|0x7A80
comma
l_int|0x02F6
comma
l_int|0x7980
comma
l_int|0x03A1
comma
l_int|0x7A80
comma
l_int|0x038A
comma
l_int|0x5D35
comma
l_int|0x0002
comma
l_int|0x695E
comma
l_int|0xB801
comma
l_int|0x905E
comma
l_int|0xBF0A
comma
l_int|0x109E
comma
l_int|0x8B8A
comma
l_int|0xAF80
comma
l_int|0x8014
comma
l_int|0x4780
comma
l_int|0xAE72
comma
l_int|0x0558
comma
l_int|0xF500
comma
l_int|0xAE72
comma
l_int|0x0518
comma
l_int|0xAE61
comma
l_int|0x105C
comma
l_int|0x7A80
comma
l_int|0x02F6
comma
l_int|0x7980
comma
l_int|0x03A1
comma
l_int|0x001C
comma
l_int|0x8B88
comma
l_int|0x6980
comma
l_int|0xEF88
comma
l_int|0x901D
comma
l_int|0x0D1D
comma
l_int|0x100F
comma
l_int|0x6610
comma
l_int|0xE38C
comma
l_int|0x0358
comma
l_int|0x690E
comma
l_int|0x6610
comma
l_int|0x620F
comma
l_int|0x660D
comma
l_int|0xBA0F
comma
l_int|0xE301
comma
l_int|0x037A
comma
l_int|0x0410
comma
l_int|0x8B8A
comma
l_int|0xB903
comma
l_int|0x8809
comma
l_int|0xBEC6
comma
l_int|0x036C
comma
l_int|0x6A8C
comma
l_int|0x61AA
comma
l_int|0x98AB
comma
l_int|0x6A8C
comma
l_int|0x61AB
comma
l_int|0x98AD
comma
l_int|0x6A8C
comma
l_int|0x61AD
comma
l_int|0x98A9
comma
l_int|0x6A8C
comma
l_int|0x61A9
comma
l_int|0x98AA
comma
l_int|0x7C04
comma
l_int|0x8B8B
comma
l_int|0x7C04
comma
l_int|0x8B8D
comma
l_int|0x7C04
comma
l_int|0x8B89
comma
l_int|0x7C04
comma
l_int|0x0814
comma
l_int|0x660E
comma
l_int|0xE308
comma
l_int|0x0379
comma
l_int|0x040D
comma
l_int|0x8410
comma
l_int|0xBC21
comma
l_int|0x691C
comma
l_int|0xB801
comma
l_int|0x901C
comma
l_int|0x7980
comma
l_int|0x034A
comma
l_int|0xB903
comma
l_int|0x8809
comma
l_int|0x8B8A
comma
l_int|0xBEC6
comma
l_int|0x0388
comma
l_int|0x54AC
comma
l_int|0xBE03
comma
l_int|0x618C
comma
l_int|0x98AA
comma
l_int|0xEF00
comma
l_int|0xBC20
comma
l_int|0xBE46
comma
l_int|0x0809
comma
l_int|0x906B
comma
l_int|0x080A
comma
l_int|0x906C
comma
l_int|0x080B
comma
l_int|0x906D
comma
l_int|0x081A
comma
l_int|0x9062
comma
l_int|0x081B
comma
l_int|0x9063
comma
l_int|0x081E
comma
l_int|0x9064
comma
l_int|0xBE59
comma
l_int|0x881E
comma
l_int|0x8065
comma
l_int|0x8166
comma
l_int|0x8267
comma
l_int|0x8368
comma
l_int|0x8469
comma
l_int|0x856A
comma
l_int|0xEF00
comma
l_int|0xBC20
comma
l_int|0x696B
comma
l_int|0x8809
comma
l_int|0x696C
comma
l_int|0x880A
comma
l_int|0x696D
comma
l_int|0x880B
comma
l_int|0x6962
comma
l_int|0x881A
comma
l_int|0x6963
comma
l_int|0x881B
comma
l_int|0x6964
comma
l_int|0x881E
comma
l_int|0x0065
comma
l_int|0x0166
comma
l_int|0x0267
comma
l_int|0x0368
comma
l_int|0x0469
comma
l_int|0x056A
comma
l_int|0xBE3A
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Mini sample rate converter code image&n; * that is to be loaded at 0x400 on the DSP.&n; */
DECL|variable|assp_minisrc_image
id|u16
id|assp_minisrc_image
(braket
)braket
op_assign
(brace
l_int|0xBF80
comma
l_int|0x101E
comma
l_int|0x906E
comma
l_int|0x006E
comma
l_int|0x8B88
comma
l_int|0x6980
comma
l_int|0xEF88
comma
l_int|0x906F
comma
l_int|0x0D6F
comma
l_int|0x6900
comma
l_int|0xEB08
comma
l_int|0x0412
comma
l_int|0xBC20
comma
l_int|0x696E
comma
l_int|0xB801
comma
l_int|0x906E
comma
l_int|0x7980
comma
l_int|0x0403
comma
l_int|0xB90E
comma
l_int|0x8807
comma
l_int|0xBE43
comma
l_int|0xBF01
comma
l_int|0xBE47
comma
l_int|0xBE41
comma
l_int|0x7A80
comma
l_int|0x002A
comma
l_int|0xBE40
comma
l_int|0x3029
comma
l_int|0xEFCC
comma
l_int|0xBE41
comma
l_int|0x7A80
comma
l_int|0x0028
comma
l_int|0xBE40
comma
l_int|0x3028
comma
l_int|0xEFCC
comma
l_int|0x6907
comma
l_int|0xE308
comma
l_int|0x042A
comma
l_int|0x6909
comma
l_int|0x902C
comma
l_int|0x7980
comma
l_int|0x042C
comma
l_int|0x690D
comma
l_int|0x902C
comma
l_int|0x1009
comma
l_int|0x881A
comma
l_int|0x100A
comma
l_int|0xBA01
comma
l_int|0x881B
comma
l_int|0x100D
comma
l_int|0x881C
comma
l_int|0x100E
comma
l_int|0xBA01
comma
l_int|0x881D
comma
l_int|0xBF80
comma
l_int|0x00ED
comma
l_int|0x881E
comma
l_int|0x050C
comma
l_int|0x0124
comma
l_int|0xB904
comma
l_int|0x9027
comma
l_int|0x6918
comma
l_int|0xE308
comma
l_int|0x04B3
comma
l_int|0x902D
comma
l_int|0x6913
comma
l_int|0xBFA0
comma
l_int|0x7598
comma
l_int|0xF704
comma
l_int|0xAE2D
comma
l_int|0x00FF
comma
l_int|0x8B8D
comma
l_int|0x6919
comma
l_int|0xE308
comma
l_int|0x0463
comma
l_int|0x691A
comma
l_int|0xE308
comma
l_int|0x0456
comma
l_int|0xB907
comma
l_int|0x8809
comma
l_int|0xBEC6
comma
l_int|0x0453
comma
l_int|0x10A9
comma
l_int|0x90AD
comma
l_int|0x7980
comma
l_int|0x047C
comma
l_int|0xB903
comma
l_int|0x8809
comma
l_int|0xBEC6
comma
l_int|0x0460
comma
l_int|0x1889
comma
l_int|0x6C22
comma
l_int|0x90AD
comma
l_int|0x10A9
comma
l_int|0x6E23
comma
l_int|0x6C22
comma
l_int|0x90AD
comma
l_int|0x7980
comma
l_int|0x047C
comma
l_int|0x101A
comma
l_int|0xE308
comma
l_int|0x046F
comma
l_int|0xB903
comma
l_int|0x8809
comma
l_int|0xBEC6
comma
l_int|0x046C
comma
l_int|0x10A9
comma
l_int|0x90A0
comma
l_int|0x90AD
comma
l_int|0x7980
comma
l_int|0x047C
comma
l_int|0xB901
comma
l_int|0x8809
comma
l_int|0xBEC6
comma
l_int|0x047B
comma
l_int|0x1889
comma
l_int|0x6C22
comma
l_int|0x90A0
comma
l_int|0x90AD
comma
l_int|0x10A9
comma
l_int|0x6E23
comma
l_int|0x6C22
comma
l_int|0x90A0
comma
l_int|0x90AD
comma
l_int|0x692D
comma
l_int|0xE308
comma
l_int|0x049C
comma
l_int|0x0124
comma
l_int|0xB703
comma
l_int|0xB902
comma
l_int|0x8818
comma
l_int|0x8B89
comma
l_int|0x022C
comma
l_int|0x108A
comma
l_int|0x7C04
comma
l_int|0x90A0
comma
l_int|0x692B
comma
l_int|0x881F
comma
l_int|0x7E80
comma
l_int|0x055B
comma
l_int|0x692A
comma
l_int|0x8809
comma
l_int|0x8B89
comma
l_int|0x99A0
comma
l_int|0x108A
comma
l_int|0x90A0
comma
l_int|0x692B
comma
l_int|0x881F
comma
l_int|0x7E80
comma
l_int|0x055B
comma
l_int|0x692A
comma
l_int|0x8809
comma
l_int|0x8B89
comma
l_int|0x99AF
comma
l_int|0x7B99
comma
l_int|0x0484
comma
l_int|0x0124
comma
l_int|0x060F
comma
l_int|0x101B
comma
l_int|0x2013
comma
l_int|0x901B
comma
l_int|0xBFA0
comma
l_int|0x7FFF
comma
l_int|0xE344
comma
l_int|0x04AC
comma
l_int|0x901B
comma
l_int|0x8B89
comma
l_int|0x7A80
comma
l_int|0x051A
comma
l_int|0x6927
comma
l_int|0xBA01
comma
l_int|0x9027
comma
l_int|0x7A80
comma
l_int|0x0523
comma
l_int|0x6927
comma
l_int|0xE308
comma
l_int|0x049E
comma
l_int|0x7980
comma
l_int|0x050F
comma
l_int|0x0624
comma
l_int|0x1026
comma
l_int|0x2013
comma
l_int|0x9026
comma
l_int|0xBFA0
comma
l_int|0x7FFF
comma
l_int|0xE304
comma
l_int|0x04C0
comma
l_int|0x8B8D
comma
l_int|0x7A80
comma
l_int|0x051A
comma
l_int|0x7980
comma
l_int|0x04B4
comma
l_int|0x9026
comma
l_int|0x1013
comma
l_int|0x3026
comma
l_int|0x901B
comma
l_int|0x8B8D
comma
l_int|0x7A80
comma
l_int|0x051A
comma
l_int|0x7A80
comma
l_int|0x0523
comma
l_int|0x1027
comma
l_int|0xBA01
comma
l_int|0x9027
comma
l_int|0xE308
comma
l_int|0x04B4
comma
l_int|0x0124
comma
l_int|0x060F
comma
l_int|0x8B89
comma
l_int|0x691A
comma
l_int|0xE308
comma
l_int|0x04EA
comma
l_int|0x6919
comma
l_int|0xE388
comma
l_int|0x04E0
comma
l_int|0xB903
comma
l_int|0x8809
comma
l_int|0xBEC6
comma
l_int|0x04DD
comma
l_int|0x1FA0
comma
l_int|0x2FAE
comma
l_int|0x98A9
comma
l_int|0x7980
comma
l_int|0x050F
comma
l_int|0xB901
comma
l_int|0x8818
comma
l_int|0xB907
comma
l_int|0x8809
comma
l_int|0xBEC6
comma
l_int|0x04E7
comma
l_int|0x10EE
comma
l_int|0x90A9
comma
l_int|0x7980
comma
l_int|0x050F
comma
l_int|0x6919
comma
l_int|0xE308
comma
l_int|0x04FE
comma
l_int|0xB903
comma
l_int|0x8809
comma
l_int|0xBE46
comma
l_int|0xBEC6
comma
l_int|0x04FA
comma
l_int|0x17A0
comma
l_int|0xBE1E
comma
l_int|0x1FAE
comma
l_int|0xBFBF
comma
l_int|0xFF00
comma
l_int|0xBE13
comma
l_int|0xBFDF
comma
l_int|0x8080
comma
l_int|0x99A9
comma
l_int|0xBE47
comma
l_int|0x7980
comma
l_int|0x050F
comma
l_int|0xB901
comma
l_int|0x8809
comma
l_int|0xBEC6
comma
l_int|0x050E
comma
l_int|0x16A0
comma
l_int|0x26A0
comma
l_int|0xBFB7
comma
l_int|0xFF00
comma
l_int|0xBE1E
comma
l_int|0x1EA0
comma
l_int|0x2EAE
comma
l_int|0xBFBF
comma
l_int|0xFF00
comma
l_int|0xBE13
comma
l_int|0xBFDF
comma
l_int|0x8080
comma
l_int|0x99A9
comma
l_int|0x850C
comma
l_int|0x860F
comma
l_int|0x6907
comma
l_int|0xE388
comma
l_int|0x0516
comma
l_int|0x0D07
comma
l_int|0x8510
comma
l_int|0xBE59
comma
l_int|0x881E
comma
l_int|0xBE4A
comma
l_int|0xEF00
comma
l_int|0x101E
comma
l_int|0x901C
comma
l_int|0x101F
comma
l_int|0x901D
comma
l_int|0x10A0
comma
l_int|0x901E
comma
l_int|0x10A0
comma
l_int|0x901F
comma
l_int|0xEF00
comma
l_int|0x101E
comma
l_int|0x301C
comma
l_int|0x9020
comma
l_int|0x731B
comma
l_int|0x5420
comma
l_int|0xBE03
comma
l_int|0x9825
comma
l_int|0x1025
comma
l_int|0x201C
comma
l_int|0x9025
comma
l_int|0x7325
comma
l_int|0x5414
comma
l_int|0xBE03
comma
l_int|0x8B8E
comma
l_int|0x9880
comma
l_int|0x692F
comma
l_int|0xE388
comma
l_int|0x0539
comma
l_int|0xBE59
comma
l_int|0xBB07
comma
l_int|0x6180
comma
l_int|0x9880
comma
l_int|0x8BA0
comma
l_int|0x101F
comma
l_int|0x301D
comma
l_int|0x9021
comma
l_int|0x731B
comma
l_int|0x5421
comma
l_int|0xBE03
comma
l_int|0x982E
comma
l_int|0x102E
comma
l_int|0x201D
comma
l_int|0x902E
comma
l_int|0x732E
comma
l_int|0x5415
comma
l_int|0xBE03
comma
l_int|0x9880
comma
l_int|0x692F
comma
l_int|0xE388
comma
l_int|0x054F
comma
l_int|0xBE59
comma
l_int|0xBB07
comma
l_int|0x6180
comma
l_int|0x9880
comma
l_int|0x8BA0
comma
l_int|0x6918
comma
l_int|0xEF08
comma
l_int|0x7325
comma
l_int|0x5416
comma
l_int|0xBE03
comma
l_int|0x98A0
comma
l_int|0x732E
comma
l_int|0x5417
comma
l_int|0xBE03
comma
l_int|0x98A0
comma
l_int|0xEF00
comma
l_int|0x8BA0
comma
l_int|0xBEC6
comma
l_int|0x056B
comma
l_int|0xBE59
comma
l_int|0xBB04
comma
l_int|0xAA90
comma
l_int|0xBE04
comma
l_int|0xBE1E
comma
l_int|0x99E0
comma
l_int|0x8BE0
comma
l_int|0x69A0
comma
l_int|0x90D0
comma
l_int|0x69A0
comma
l_int|0x90D0
comma
l_int|0x081F
comma
l_int|0xB805
comma
l_int|0x881F
comma
l_int|0x8B90
comma
l_int|0x69A0
comma
l_int|0x90D0
comma
l_int|0x69A0
comma
l_int|0x9090
comma
l_int|0x8BD0
comma
l_int|0x8BD8
comma
l_int|0xBE1F
comma
l_int|0xEF00
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
)brace
suffix:semicolon
eof
