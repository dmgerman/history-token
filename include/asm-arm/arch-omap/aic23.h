multiline_comment|/*&n; * linux/include/asm-arm/arch-omap/aic23.h&n; *&n; * Hardware definitions for TI TLV320AIC23 audio codec&n; *&n; * Copyright (C) 2002 RidgeRun, Inc.&n; * Author: Steve Johnson&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n; * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF&n; * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the  GNU General Public License along&n; * with this program; if not, write  to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __ASM_ARCH_AIC23_H
DECL|macro|__ASM_ARCH_AIC23_H
mdefine_line|#define __ASM_ARCH_AIC23_H
singleline_comment|// Codec TLV320AIC23
DECL|macro|LEFT_LINE_VOLUME_ADDR
mdefine_line|#define LEFT_LINE_VOLUME_ADDR&t;&t;0x00
DECL|macro|RIGHT_LINE_VOLUME_ADDR
mdefine_line|#define RIGHT_LINE_VOLUME_ADDR&t;&t;0x01
DECL|macro|LEFT_CHANNEL_VOLUME_ADDR
mdefine_line|#define LEFT_CHANNEL_VOLUME_ADDR&t;0x02
DECL|macro|RIGHT_CHANNEL_VOLUME_ADDR
mdefine_line|#define RIGHT_CHANNEL_VOLUME_ADDR&t;0x03
DECL|macro|ANALOG_AUDIO_CONTROL_ADDR
mdefine_line|#define ANALOG_AUDIO_CONTROL_ADDR&t;0x04
DECL|macro|DIGITAL_AUDIO_CONTROL_ADDR
mdefine_line|#define DIGITAL_AUDIO_CONTROL_ADDR&t;0x05
DECL|macro|POWER_DOWN_CONTROL_ADDR
mdefine_line|#define POWER_DOWN_CONTROL_ADDR&t;&t;0x06
DECL|macro|DIGITAL_AUDIO_FORMAT_ADDR
mdefine_line|#define DIGITAL_AUDIO_FORMAT_ADDR&t;0x07
DECL|macro|SAMPLE_RATE_CONTROL_ADDR
mdefine_line|#define SAMPLE_RATE_CONTROL_ADDR&t;0x08
DECL|macro|DIGITAL_INTERFACE_ACT_ADDR
mdefine_line|#define DIGITAL_INTERFACE_ACT_ADDR&t;0x09
DECL|macro|RESET_CONTROL_ADDR
mdefine_line|#define RESET_CONTROL_ADDR&t;&t;0x0F
singleline_comment|// Left (right) line input volume control register
DECL|macro|LRS_ENABLED
mdefine_line|#define LRS_ENABLED&t;&t;&t;0x0100
DECL|macro|LIM_MUTED
mdefine_line|#define LIM_MUTED&t;&t;&t;0x0080
DECL|macro|LIV_DEFAULT
mdefine_line|#define LIV_DEFAULT&t;&t;&t;0x0017
DECL|macro|LIV_MAX
mdefine_line|#define LIV_MAX&t;&t;&t;&t;0x001f
DECL|macro|LIV_MIN
mdefine_line|#define LIV_MIN&t;&t;&t;&t;0x0000
singleline_comment|// Left (right) channel headphone volume control register
DECL|macro|LZC_ON
mdefine_line|#define LZC_ON&t;&t;&t;&t;0x0080
DECL|macro|LHV_DEFAULT
mdefine_line|#define LHV_DEFAULT&t;&t;&t;0x0079
DECL|macro|LHV_MAX
mdefine_line|#define LHV_MAX&t;&t;&t;&t;0x007f
DECL|macro|LHV_MIN
mdefine_line|#define LHV_MIN&t;&t;&t;&t;0x0000
singleline_comment|// Analog audio path control register
DECL|macro|STE_ENABLED
mdefine_line|#define STE_ENABLED&t;&t;&t;0x0020
DECL|macro|DAC_SELECTED
mdefine_line|#define DAC_SELECTED&t;&t;&t;0x0010
DECL|macro|BYPASS_ON
mdefine_line|#define BYPASS_ON&t;&t;&t;0x0008
DECL|macro|INSEL_MIC
mdefine_line|#define INSEL_MIC&t;&t;&t;0x0004
DECL|macro|MICM_MUTED
mdefine_line|#define MICM_MUTED&t;&t;&t;0x0002
DECL|macro|MICB_20DB
mdefine_line|#define MICB_20DB&t;&t;&t;0x0001
singleline_comment|// Digital audio path control register
DECL|macro|DACM_MUTE
mdefine_line|#define DACM_MUTE&t;&t;&t;0x0008
DECL|macro|DEEMP_32K
mdefine_line|#define DEEMP_32K&t;&t;&t;0x0002
DECL|macro|DEEMP_44K
mdefine_line|#define DEEMP_44K&t;&t;&t;0x0004
DECL|macro|DEEMP_48K
mdefine_line|#define DEEMP_48K&t;&t;&t;0x0006
DECL|macro|ADCHP_ON
mdefine_line|#define ADCHP_ON&t;&t;&t;0x0001
singleline_comment|// Power control down register
DECL|macro|DEVICE_POWER_OFF
mdefine_line|#define DEVICE_POWER_OFF&t;  &t;0x0080
DECL|macro|CLK_OFF
mdefine_line|#define CLK_OFF&t;&t;&t;&t;0x0040
DECL|macro|OSC_OFF
mdefine_line|#define OSC_OFF&t;&t;&t;&t;0x0020
DECL|macro|OUT_OFF
mdefine_line|#define OUT_OFF&t;&t;&t;&t;0x0010
DECL|macro|DAC_OFF
mdefine_line|#define DAC_OFF&t;&t;&t;&t;0x0008
DECL|macro|ADC_OFF
mdefine_line|#define ADC_OFF&t;&t;&t;&t;0x0004
DECL|macro|MIC_OFF
mdefine_line|#define MIC_OFF&t;&t;&t;&t;0x0002
DECL|macro|LINE_OFF
mdefine_line|#define LINE_OFF&t;&t;&t;0x0001
singleline_comment|// Digital audio interface register
DECL|macro|MS_MASTER
mdefine_line|#define MS_MASTER&t;&t;&t;0x0040
DECL|macro|LRSWAP_ON
mdefine_line|#define LRSWAP_ON&t;&t;&t;0x0020
DECL|macro|LRP_ON
mdefine_line|#define LRP_ON&t;&t;&t;&t;0x0010
DECL|macro|IWL_16
mdefine_line|#define IWL_16&t;&t;&t;&t;0x0000
DECL|macro|IWL_20
mdefine_line|#define IWL_20&t;&t;&t;&t;0x0004
DECL|macro|IWL_24
mdefine_line|#define IWL_24&t;&t;&t;&t;0x0008
DECL|macro|IWL_32
mdefine_line|#define IWL_32&t;&t;&t;&t;0x000C
DECL|macro|FOR_I2S
mdefine_line|#define FOR_I2S&t;&t;&t;&t;0x0002
DECL|macro|FOR_DSP
mdefine_line|#define FOR_DSP&t;&t;&t;&t;0x0003
singleline_comment|// Sample rate control register
DECL|macro|CLKOUT_HALF
mdefine_line|#define CLKOUT_HALF&t;&t;&t;0x0080
DECL|macro|CLKIN_HALF
mdefine_line|#define CLKIN_HALF&t;&t;&t;0x0040
DECL|macro|BOSR_384fs
mdefine_line|#define BOSR_384fs&t;&t;&t;0x0002 
singleline_comment|// BOSR_272fs when in USB mode
DECL|macro|USB_CLK_ON
mdefine_line|#define USB_CLK_ON&t;&t;&t;0x0001
DECL|macro|SR_MASK
mdefine_line|#define SR_MASK                         0xf
DECL|macro|CLKOUT_SHIFT
mdefine_line|#define CLKOUT_SHIFT                    7
DECL|macro|CLKIN_SHIFT
mdefine_line|#define CLKIN_SHIFT                     6
DECL|macro|SR_SHIFT
mdefine_line|#define SR_SHIFT                        2
DECL|macro|BOSR_SHIFT
mdefine_line|#define BOSR_SHIFT                      1
singleline_comment|// Digital interface register
DECL|macro|ACT_ON
mdefine_line|#define ACT_ON&t;&t;&t;&t;0x0001
DECL|macro|TLV320AIC23ID1
mdefine_line|#define TLV320AIC23ID1                  (0x1a)&t;
singleline_comment|// cs low
DECL|macro|TLV320AIC23ID2
mdefine_line|#define TLV320AIC23ID2                  (0x1b)&t;
singleline_comment|// cs high
macro_line|#endif /* __ASM_ARCH_AIC23_H */
eof
