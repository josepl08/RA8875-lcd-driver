/*
 * ra8875.c
 *
 *  Created on: Nov 6, 2020
 *      Author: Desarrollo
 */
#include "ra8875.h"


static void RA8875_PLL_Init(RA8875_Handler *handler);
static void ra8875_800x480_config(RA8875_Handler *handler);

void RA8875_command_write(RA8875_Handler *handler, uint8_t cmd){
	uint8_t dframe[2];

	dframe[0] = (uint8_t)ra8875_ac_cycle_CmdWrite;
	dframe[1] = cmd;

	handler->ra8875_if_write(dframe, 2, ra8875_tx_unique);
}
void RA8875_data_write(RA8875_Handler *handler,uint8_t data){
	uint8_t dframe[2];

	dframe[0] = (uint8_t)ra8875_ac_cycle_DataWrite;
	dframe[1] = data;

	handler->ra8875_if_write(dframe, 2, ra8875_tx_unique);
}
void RA8875_status_read(RA8875_Handler *handler, uint8_t *buf){
	uint8_t dframe[2];

	dframe[0] = (uint8_t)ra8875_ac_cycle_StatusRead;
	dframe[1] = 0x00;

	handler->ra8875_if_read(dframe, buf, 2);
}
void RA8875_data_read(RA8875_Handler *handler, uint8_t *buf){
	uint8_t dframe[2];

	dframe[0] = (uint8_t)ra8875_ac_cycle_DataRead;
	dframe[1] = 0x00;

	handler->ra8875_if_read(dframe, buf, 2);
}

void RA8875_write_reg(RA8875_Handler *handler, uint8_t cmd, uint8_t data){
	while(handler->ra8875_get_wait == 0);
	RA8875_command_write(handler, cmd);
	RA8875_data_write(handler, data);
}
uint8_t RA8875_read_reg(RA8875_Handler *handler, uint8_t cmd){

	uint8_t data[2];
	RA8875_command_write(handler, cmd);
	RA8875_data_read(handler, data);
	return data[1];
}
void RA8875_Init(RA8875_Handler* handler){
	// Software reset
	RA8875_write_reg(handler, RA8875_PWRR_REG, 		0x01);
	handler->ra8875_delay_ms(100);
	RA8875_write_reg(handler, RA8875_PWRR_REG, 0x00);
	handler->ra8875_delay_ms(100);
	// Inicializar PLL
	RA8875_PLL_Init(handler);
	// Configuración para resolución de TFT-LCD
	switch(handler->resolution){
	case ra8875_320x240:
		//TODO: función para configurar a la resolución
		for(;;){}
		break;
	case ra8875_480x272:
		//TODO: función para configurar a la resolución
		for(;;){}
		break;
	case ra8875_640x480:
		//TODO: función para configurar a la resolución
		for(;;){}
		break;
	case ra8875_800x480:
		ra8875_800x480_config(handler);
		break;
	}
	//Configuración de PWM/Backlight
	RA8875_write_reg(handler, RA8875_P1CR_REG, 0x80);
	RA8875_write_reg(handler, RA8875_P1CR_REG, 0x81);
	RA8875_write_reg(handler, RA8875_P1DCR_REG, 0xFF);

	// Display ON
	RA8875_write_reg(handler, RA8875_PWRR_REG, 0x80);

	RA8875_clear_screen(handler, 0xFCA0);

	RA8875_write_reg(handler, RA8875_MCLR_REG, 0x80);
}
void RA8875_DDRAM_write(RA8875_Handler *handler, uint8_t *buff, uint32_t len){
	uint32_t i;
	// Set graphic mode

	// set write cursor position
	RA8875_setXY(handler, 0, 0);
	// command write cycle
	RA8875_command_write(handler, RA8875_MRWC_REG);
	// 'super data write cycle'
	/* por la manera en que está escrito el callback no puedo usarlo para enviar
	 * datos. TEngo que crear array tamaño len+1 y agregar la parte de DataWrite
	 */

	for (i=0;i<len;i++){

	}


}

void RA8875_set_active_window(RA8875_Handler *hanlder, int16_t x1, int16_t x2, int16_t y1, int16_t y2){
	uint8_t reg_h;
	uint8_t reg_l;

	reg_h = (uint8_t)((x1>>8)&0x03);
	reg_l = (uint8_t)((x1)&0xFF);
	RA8875_write_reg(hanlder, RA8875_HSAW0_REG, reg_l);
	RA8875_write_reg(hanlder, RA8875_HSAW1_REG, reg_h);

	reg_h = (uint8_t)((y1>>8)&0x03);
	reg_l = (uint8_t)((y1)&0xFF);
	RA8875_write_reg(hanlder, RA8875_VSAW0_REG, reg_l);
	RA8875_write_reg(hanlder, RA8875_VSAW1_REG, reg_h);

	reg_h = (uint8_t)((x2>>8)&0x03);
	reg_l = (uint8_t)((x2)&0xFF);
	RA8875_write_reg(hanlder, RA8875_HEAW0_REG, reg_l);
	RA8875_write_reg(hanlder, RA8875_HEAW1_REG, reg_h);

	reg_h = (uint8_t)((y2>>8)&0x03);
	reg_l = (uint8_t)((y2)&0xFF);
	RA8875_write_reg(hanlder, RA8875_VEAW0_REG, reg_l);
	RA8875_write_reg(hanlder, RA8875_VEAW1_REG, reg_h);
}
void RA8875_setX(RA8875_Handler *handler, uint32_t x){
	uint8_t v_low;
	uint8_t v_high;

	v_low = x & 0xFF;
	v_high = x >> 8;
	RA8875_write_reg(handler, RA8875_CURH0_REG, v_low);
	RA8875_write_reg(handler, RA8875_CURH1_REG, v_high);
}
void RA8875_setY(RA8875_Handler *handler, uint32_t y){
	uint8_t v_low;
	uint8_t v_high;

	v_low = y & 0xFF;
	v_high = y >> 8;
	RA8875_write_reg(handler, RA8875_CURV0_REG, v_low);
	RA8875_write_reg(handler, RA8875_CURV1_REG, v_high);
}
void RA8875_setXY(RA8875_Handler *handler, uint32_t x, uint32_t y){
	RA8875_setX(handler, x);
	RA8875_setY(handler, y);
}
void RA8875_setXY_font(RA8875_Handler *handler, uint32_t x, uint32_t y){
	uint8_t temp;
	// set x position
	temp = (uint8_t)(x & 0xFF);
	RA8875_write_reg(handler, RA8875_F_CURXL_REG, temp);
	temp = (uint8_t)((x>>8)&0x03);
	RA8875_write_reg(handler, RA8875_F_CURXH_REG, temp);
	// set y position
	temp = (uint8_t)(y & 0xFF);
	RA8875_write_reg(handler, RA8875_F_CURYL_REG, temp);
	temp = (uint8_t)((y>>8)&0x03);
	RA8875_write_reg(handler, RA8875_F_CURYH_REG, temp);
}
#if 0
void RA8875_set_text_mode(RA8875_Handler *handler){
	uint8_t temp;
	temp = RA8875_read_reg(handler, RA8875_MWCR0_REG);
	if((temp & 0x80)==0){ // 7th bit 1=Text Mode; 0=GraphicMode
		temp |= 0x80;
		RA8875_write_reg(handler, RA8875_MWCR0_REG, temp);
	}else{
		return;
	}
}

void RA8875_set_graphic_mode(RA8875_Handler *handler){
	uint8_t temp;
	temp = RA8875_read_reg(handler, RA8875_MWCR0_REG);
	if((temp & 0x80)==0){ // 7th bit 1=Text Mode; 0=GraphicMode
		return;
	}else{
		temp &= 0x7F;
		RA8875_write_reg(handler, RA8875_MWCR0_REG, temp);
	}
}
#endif
void RA8875_clear_screen(RA8875_Handler *handler, uint16_t color){
	uint8_t temp;
	//red val
	temp = (uint8_t)(color>>11);
	RA8875_write_reg(handler, RA8875_BGCR0_REG, temp);
	//greenval
	temp = (uint8_t)(color>>5)&0x3F;
	RA8875_write_reg(handler, RA8875_BGCR0_REG, temp);
	//blue val
	temp = (uint8_t)(color)&0x1F;
	RA8875_write_reg(handler, RA8875_BGCR0_REG, temp);
}
void RA8875_setForegroundColor(RA8875_Handler *handler, uint16_t Color) {
	uint8_t temp;
	temp = (uint8_t) (Color >> 11);
	RA8875_write_reg(handler, RA8875_FGCR0_REG, temp); /* ra8875_red */
	temp = (uint8_t) (Color >> 5)&0x3F;
	RA8875_write_reg(handler, RA8875_FGCR1_REG, temp); /* ra8875_green */
	temp = (uint8_t) (Color)&0x1F;
	RA8875_write_reg(handler, RA8875_FGCR2_REG, temp); /* ra8875_blue */
}

void RA8875_setBackgroundColor(RA8875_Handler *handler, uint16_t Color) {
	uint8_t temp;
	temp = (uint8_t) (Color >> 11);
	RA8875_write_reg(handler, RA8875_BGCR0_REG, temp); /* ra8875_red */
	temp = (uint8_t) (Color >> 5)&0x3F;
	RA8875_write_reg(handler, RA8875_BGCR1_REG, temp); /* ra8875_green */
	temp = (uint8_t) (Color)&0x1F;
	RA8875_write_reg(handler, RA8875_BGCR2_REG, temp); /* ra8875_blue */
}


void RA8875_set_pixels_565(RA8875_Handler *handler, uint32_t size, ra8875_color565_t *frame16b){
	uint8_t tmp;

	//set graphics mode
	RA8875_set_graphics_mode(handler);
	// command write cycle to register 0x02
	RA8875_command_write(handler, RA8875_MRWC_REG);

	tmp = (uint8_t)ra8875_ac_cycle_DataWrite;
	// data write cycle:  command (1st byte)
	handler->ra8875_if_write(&tmp, 1, ra8875_tx_first);

	// data write cycle: data (pixel data)
	handler->ra8875_if_write(&frame16b[0].color8[0], size*2, ra8875_tx_last);
}

void RA8875_simple_flush(RA8875_Handler *handler, uint32_t size, uint8_t *buff){
	uint8_t tmp;

	//set graphics mode
	RA8875_set_graphics_mode(handler);
	// command write cycle to register 0x02
	RA8875_command_write(handler, RA8875_MRWC_REG);

	tmp = (uint8_t)ra8875_ac_cycle_DataWrite;
	// data write cycle:  command (1st byte)
	handler->ra8875_if_write(&tmp, 1, ra8875_tx_first);

	// data write cycle: data (pixel data)
	handler->ra8875_if_write(buff, size, ra8875_tx_last);
}

void RA8875_set_font_size(RA8875_Handler *handler, uint8_t size_h, uint8_t size_v){
	RA8875_write_reg(handler, RA8875_CURHS_REG, size_h & 0x0F);
	RA8875_write_reg(handler, RA8875_CURVS_REG, size_v & 0x0F);
}

void RA8875_write_text(RA8875_Handler *handler, uint8_t *string, uint32_t len){
	//uint8_t temp;
	uint32_t i;
	// set text mode
	RA8875_set_text_mode(handler);
	// write command cycle
	RA8875_command_write(handler, RA8875_MRWC_REG);
	for (i=0;i<len;i++){
		RA8875_data_write(handler, string[i]);
	}
//	temp = (uint8_t)ra8875_ac_cycle_DataWrite;
//	// data write cycle: command (1st byte)
//	handler->ra8875_if_write(&temp, 1, ra8875_tx_first);
//	// data write cycle: data (text data);
//	handler->ra8875_if_write(string, len, ra8875_tx_last);
}

void RA8875_fillRect(RA8875_Handler *handler, int16_t x, int16_t y,
		int16_t w, int16_t h, uint16_t color) {

	int16_t temp;

	/* Horizontal start */
	temp = x;
	RA8875_write_reg(handler, RA8875_DLHSR0_REG, temp);
	temp = x >> 8;
	RA8875_write_reg(handler, RA8875_DLHSR1_REG, temp);

	/* Horizontal end */
	temp = (x + w);
	RA8875_write_reg(handler, RA8875_DLHER0_REG, temp);
	temp = (x + w) >> 8;
	RA8875_write_reg(handler, RA8875_DLHER1_REG, temp);

	/* Vertical start */
	temp = y;
	RA8875_write_reg(handler, RA8875_DLVSR0_REG, temp);
	temp = y >> 8;
	RA8875_write_reg(handler, RA8875_DLVSR1_REG, temp);

	/* Vertical end */
	temp = (y + h);
	RA8875_write_reg(handler, RA8875_DLVER0_REG, temp);
	temp = (y + h) >> 8;
	RA8875_write_reg(handler, RA8875_DLVER1_REG, temp);

	RA8875_setForegroundColor(handler, color);



	RA8875_write_reg(handler, RA8875_DCR_REG, 0xB0);
}

void RA8875_set_graphics_mode(RA8875_Handler *handler){
	if(handler->mem_w_ctrl.mem_write_ctrl_p.MWCR0_text_en == 1){
		handler->mem_w_ctrl.mem_write_ctrl_p.MWCR0_text_en = 0;
		RA8875_write_reg(handler, RA8875_MWCR0_REG, handler->mem_w_ctrl.byte_packet[0]);
	}
}

void RA8875_set_text_mode(RA8875_Handler *handler){
	if(handler->mem_w_ctrl.mem_write_ctrl_p.MWCR0_text_en == 0){
		handler->mem_w_ctrl.mem_write_ctrl_p.MWCR0_text_en = 1;
		RA8875_write_reg(handler, RA8875_MWCR0_REG, handler->mem_w_ctrl.byte_packet[0]);
	}
}

uint16_t RA8875_565set_color(uint16_t color){
	return ((color<<8)&0xFF00)|((color>>8)&0x00FF);
}

static void RA8875_setPLL_55MHz(RA8875_Handler *handler){
	RA8875_command_write(handler, RA8875_PLLC1_REG);
	RA8875_data_write(handler, 0x0a);

	handler->ra8875_delay_ms(1);

	RA8875_command_write(handler, RA8875_PLLC2_REG);
	RA8875_data_write(handler, 0x02);

	handler->ra8875_delay_ms(1);
}

static void RA8875_setPLL_60MHz(RA8875_Handler *handler){
	RA8875_command_write(handler, RA8875_PLLC1_REG);
	RA8875_data_write(handler, 0x0b);

	handler->ra8875_delay_ms(1);

	RA8875_command_write(handler, RA8875_PLLC2_REG);
	RA8875_data_write(handler, 0x02);

	handler->ra8875_delay_ms(1);
}

static void RA8875_PLL_Init(RA8875_Handler* handler){
	switch(handler->resolution){
	case ra8875_320x240:
		RA8875_setPLL_55MHz(handler);
		break;
	case ra8875_480x272:
		RA8875_setPLL_55MHz(handler);
		break;
	case ra8875_640x480:
		RA8875_setPLL_60MHz(handler);
		break;
	case ra8875_800x480:
		RA8875_setPLL_60MHz(handler);
	}
}

static void ra8875_800x480_config(RA8875_Handler *handler){

	// configuración de sistema
	RA8875_write_reg(handler, RA8875_SYSR_REG, 		0x0C);
	RA8875_write_reg(handler, RA8875_PCSR_REG, 		0x81);
	handler->ra8875_delay_ms(100);
	// configuración horizaontal
	RA8875_write_reg(handler, RA8875_HDWR_REG, 		0x63);
	RA8875_write_reg(handler, RA8875_HNDFTR_REG, 	0x03);
	RA8875_write_reg(handler, RA8875_HNDR_REG, 		0x03);
	RA8875_write_reg(handler, RA8875_HSTR_REG, 		0x02);
	RA8875_write_reg(handler, RA8875_HPWR_REG, 		0x00);

	// configruación vertical
	RA8875_write_reg(handler, RA8875_VDHR0_REG, 	0xDF);
	RA8875_write_reg(handler, RA8875_VDHR1_REG, 	0x01);
	RA8875_write_reg(handler, RA8875_VNDR0_REG, 	0x14);
	RA8875_write_reg(handler, RA8875_VNDR1_REG, 	0x00);
	RA8875_write_reg(handler, RA8875_VSTR0_REG, 	0x06);
	RA8875_write_reg(handler, RA8875_VSTR1_REG, 	0x00);
	RA8875_write_reg(handler, RA8875_VPWR_REG, 		0x01);
	// configuración ventana activa horizontal
	RA8875_write_reg(handler, RA8875_HSAW0_REG, 	0x00);
	RA8875_write_reg(handler, RA8875_HSAW1_REG, 	0x00);
	RA8875_write_reg(handler, RA8875_HEAW0_REG, 	0x1F);
	RA8875_write_reg(handler, RA8875_HEAW1_REG, 	0x03);
	// configuración ventana activa vertical
	RA8875_write_reg(handler, RA8875_VSAW0_REG, 	0x00);
	RA8875_write_reg(handler, RA8875_VSAW1_REG, 	0x00);
	RA8875_write_reg(handler, RA8875_VEAW0_REG, 	0xDF);
	RA8875_write_reg(handler, RA8875_VEAW1_REG, 	0x01);
}
