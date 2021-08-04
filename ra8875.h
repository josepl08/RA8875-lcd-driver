/*
 * RA8875.h
 *
 *  Created on: Nov 6, 2020
 *      Author: Desarrollo
 */


#ifndef INC_RA8875_H_
#define INC_RA8875_H_

#include "stm32f7xx_hal.h"

#define	RA8875_PWRR_REG			0x01
#define RA8875_MRWC_REG			0x02
#define RA8875_PCSR_REG			0x04
#define RA8875_SROC_REG			0x05
#define RA8875_SFCLR_REG		0x06
#define RA8875_SYSR_REG			0x10
#define RA8875_GPI_REG			0X12
#define RA8875_GPO_REG			0x13
#define RA8875_HDWR_REG			0x14
#define RA8875_HNDFTR_REG		0x15
#define RA8875_HNDR_REG			0x16
#define RA8875_HSTR_REG			0x17
#define RA8875_HPWR_REG			0x18
#define RA8875_VDHR0_REG		0x19
#define RA8875_VDHR1_REG		0x1A
#define RA8875_VNDR0_REG		0x1B
#define RA8875_VNDR1_REG		0x1C
#define RA8875_VSTR0_REG		0x1D
#define RA8875_VSTR1_REG		0x1E
#define RA8875_VPWR_REG			0x1F

#define RA8875_DCPR_REG			0x20
#define RA8875_FNCR0_REG		0x21
#define RA8875_FNCR1_REG		0x22
#define RA8875_CGSR_REG			0x23
#define RA8875_HOFS0_REG		0x24
#define RA8875_HOFS1_REG		0x25
#define RA8875_VOFS0_REG		0x26
#define RA8875_VOFS1_REG		0x27
#define RA8875_FLDR_REG			0x29
#define RA8875_F_CURXL_REG		0x2A
#define RA8875_F_CURXH_REG		0x2B
#define RA8875_F_CURYL_REG		0x2C
#define RA8875_F_CURYH_REG		0x2D
#define RA8875_FWTS_REG			0x2E
#define RA8875_SFRS_REG			0x2F


#define RA8875_HSAW0_REG		0x30
#define RA8875_HSAW1_REG		0x31
#define RA8875_VSAW0_REG		0x32
#define RA8875_VSAW1_REG		0x33
#define RA8875_HEAW0_REG		0x34
#define RA8875_HEAW1_REG		0x35
#define	RA8875_VEAW0_REG		0x36
#define RA8875_VEAW1_REG		0x37

#define RA8875_MWCR0_REG		0x40
#define RA8875_MWCR1_REG		0x41
#define RA8875_BTCR_REG			0x44
#define RA8875_MRCD_REG			0x45
#define RA8875_CURH0_REG		0x46
#define RA8875_CURH1_REG		0x47
#define RA8875_CURV0_REG		0x48
#define RA8875_CURV1_REG		0x49
#define RA8875_RCURH0_REG		0x4A
#define RA8875_RCURH01_REG		0x4B
#define RA8875_RCURV0_REG		0x4C
#define RA8875_RCURV1_REG		0x4D
#define RA8875_CURHS_REG		0X4E
#define RA8875_CURVS_REG		0x4F

#define RA8875_PLLC1_REG		0x88
#define RA8875_PLLC2_REG		0x89
#define RA8875_P1CR_REG			0x8A
#define RA8875_P1DCR_REG		0x8B
#define RA8875_P2CR_REG			0x8C
#define RA8875_P2DCR_REG		0x8D
#define RA8875_MCLR_REG			0x8E

#define RA8875_BGCR0_REG		0x60
#define RA8875_BGCR1_REG		0x61
#define RA8875_BGCR2_REG		0x62
#define RA8875_FGCR0_REG		0x63
#define RA8875_FGCR1_REG		0x64
#define RA8875_FGCR2_REG		0x65

#define RA8875_DCR_REG			0x90
#define RA8875_DLHSR0_REG		0x91
#define RA8875_DLHSR1_REG		0x92
#define RA8875_DLVSR0_REG		0x93
#define RA8875_DLVSR1_REG		0x94
#define RA8875_DLHER0_REG		0x95
#define RA8875_DLHER1_REG		0x96
#define RA8875_DLVER0_REG		0x97
#define RA8875_DLVER1_REG		0x98

typedef enum{
	ra8875_8bitMCU,
	ra8875_16bitMCU
} ra8875_mcu_if_t;

typedef enum{
	ra8875_8bpp,
	ra8875_16bpp
}ra8875_color_depth_t;

typedef enum{
	ra8875_320x240,
	ra8875_480x272,
	ra8875_640x480,
	ra8875_800x480
}ra8875_resolution_t;

typedef enum{
	ra8875_ac_cycle_DataWrite 	= 0x00,
	ra8875_ac_cycle_DataRead 	= 0x40,
	ra8875_ac_cycle_CmdWrite	= 0x80,
	ra8875_ac_cycle_StatusRead 	= 0xC0
}ra8875_ac_cycle;

typedef enum{
	ra8875_graphic_mode,
	ra8875_text_mode
}ra8875_mem_write_mode;

typedef enum RA8875_transmit_types{
	ra8875_tx_first,
	ra8875_tx_last,
	ra8875_tx_unique,
	ra8875_tx_partial
}ra8875_transmit_t;
#if 0
typedef struct{
	uint16_t MWCR0_text_en			:	1;
	uint16_t MWCR0_cursor_en		:	1;
	uint16_t MWCR0_cursor_blnk		:	1;
	uint16_t MWCR0_reserved			:	1;
	uint16_t MWCR0_mwrite_dir		:	2;
	uint16_t MWCR0_mwrite_inc		:	1;
	uint16_t MWCR0_mread_inc		:	1;

	uint16_t MWCR1_g_cursor_en		:	1;
	uint16_t MWCR1_g_cursor_selec	:	3;
	uint16_t MWCR1_write_dest		:	2;
	uint16_t MWCR1_NA				:	1;
	uint16_t MWCR1_layer_selec		:	1;
}ra8875_mem_write_ctrl_t;
#endif
typedef struct{
	uint16_t MWCR0_mread_inc		:	1;
	uint16_t MWCR0_mwrite_inc		:	1;
	uint16_t MWCR0_mwrite_dir		:	2;
	uint16_t MWCR0_reserved			:	1;
	uint16_t MWCR0_cursor_blnk		:	1;
	uint16_t MWCR0_cursor_en		:	1;
	uint16_t MWCR0_text_en			:	1;

	uint16_t MWCR1_layer_selec		:	1;
	uint16_t MWCR1_NA				:	1;
	uint16_t MWCR1_write_dest		:	2;
	uint16_t MWCR1_g_cursor_selec	:	3;
	uint16_t MWCR1_g_cursor_en		:	1;
}ra8875_mem_write_ctrl_t;
typedef union{
	ra8875_mem_write_ctrl_t mem_write_ctrl_p;
	uint8_t	byte_packet[2];
}ra8875_mem_write_ctrl_packet_t;


typedef struct ra8875_handler{
	ra8875_resolution_t 	resolution;
	ra8875_color_depth_t 	color_d;
	ra8875_mcu_if_t 		mcu_if;
	ra8875_mem_write_ctrl_packet_t		mem_w_ctrl;

	void(*ra8875_if_write)(uint8_t*,uint32_t, ra8875_transmit_t);
	void(*ra8875_if_read)(uint8_t*,uint8_t*,uint32_t);
	void(*ra8875_delay_ms)(uint32_t);
	uint8_t(*ra8875_get_wait)();
}RA8875_Handler;

typedef union pixel_data565{
	uint16_t color16;
	uint8_t color8[2];
}ra8875_color565_t;

void RA8875_command_write(RA8875_Handler *handler, uint8_t cmd);
void RA8875_data_write(RA8875_Handler *handler, uint8_t data);
void RA8875_status_read(RA8875_Handler *handler, uint8_t *buf);
void RA8875_data_read(RA8875_Handler *handler, uint8_t *buf);
void RA8875_write_reg(RA8875_Handler *handler, uint8_t cmd, uint8_t data);
uint8_t RA8875_read_reg(RA8875_Handler *handler, uint8_t cmd);
void RA8875_Init(RA8875_Handler* handler);
void RA8875_setX(RA8875_Handler *handler, uint32_t x);
void RA8875_setY(RA8875_Handler *handler, uint32_t y);
void RA8875_setXY(RA8875_Handler *handler, uint32_t x, uint32_t y);
void RA8875_setXY_font(RA8875_Handler *handler, uint32_t x, uint32_t y);
void RA8875_set_text_mode(RA8875_Handler *handler);
void RA8875_set_graphics_mode(RA8875_Handler *handler);
void RA8875_DDRAM_write(RA8875_Handler *handler, uint8_t *buff, uint32_t len);
void RA8875_set_active_window(RA8875_Handler *hanlder, int16_t x1, int16_t x2, int16_t y1, int16_t y2);
void RA8875_setForegroundColor(RA8875_Handler *handler, uint16_t Color);
void RA8875_setBackgroundColor(RA8875_Handler *handler, uint16_t Color);
void RA8875_set_graphics_mode(RA8875_Handler *handler);
void RA8875_set_text_mode(RA8875_Handler *handler);
void RA8875_set_pixels_565(RA8875_Handler *handler, uint32_t size, ra8875_color565_t *frame16b);
void RA8875_simple_flush(RA8875_Handler *handler, uint32_t size, uint8_t *buff);
void RA8875_write_text(RA8875_Handler *handler, uint8_t *string, uint32_t len);
void RA8875_clear_screen(RA8875_Handler *handler, uint16_t color);
void RA8875_fillRect(RA8875_Handler *handler, int16_t x, int16_t y,
		int16_t w, int16_t h, uint16_t color);
uint16_t RA8875_565set_color(uint16_t color);
void RA8875_set_font_size(RA8875_Handler *handler, uint8_t size_h, uint8_t size_v);
#endif /* INC_RA8875_H_ */
