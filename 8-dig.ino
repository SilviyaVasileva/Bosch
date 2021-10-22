const byte digits[] = {
	B01111110,B00110000,B01101101,B01111001,B00110011,B01011011,B01011111,B01110000,B01111111,B01111011
};

uint16_t MEMORY1 = 0;
int16_t MEMORY2 = 0;

void setup() {
	/**/
}

void loop() {
	display_digits();
}

void add_to_memory(uint16_t num1, uint16_t num2){
	MEMORY += num;
	if (num1 == 0) {
		if (num2 < 10000) 
			if (MEMORY2 + num2 < 10000)
				MEMORY2 += num2;
			else clear_memory();
		else clear_memory();
	}
	else {
		if (num1 < 10000) 
			if (MEMORY1 + num1 < 10000)
				MEMORY1 += num1
			else num2 += 1;
			if (num2 < 10000) 
				if (MEMORY2 + num2 < 10000)
					MEMORY2 += num2;
				else clear_memory();
			else clear_memory();
		else clear_memory();
	}
}

void substract_from_memory(uint16_t num1, uint16_t num2) {
	if((num1 > MEMORY1 && MEMORY2 < 1) || (num2 > MEMORY2) || (num2 == MEMORY2 && num1 > MEMORY1))
		clear_memory()
	else if(num1 > MEMORY1 && MEMORY2 >= 1 ) {
		MEMORY2 -= (1 + num2);
		MEMORY1 -= (num1 - 10000);
	}
	else if( MEMORY1 > num1) {
		MEMORY1 -= num1;
		MEMORY2 -= num2;
	}
	else clear_memory();

}


void clear_memory() {
	MEMORY2 = 0;
	MEMORY1 = 0;
}

void display_digits() {
	if( MEMORY2 == 0) {
		uint8_t d = 0;
		uint16_t temp_d = MEMORY1;
		for (uint8_t i = 0; i <=4; ++i) {
			d = temp_d % 10;
			temp_d = temp_d / 10;
			if(temp_d == 0 && d == 0)
				break;
			draw_digit(i, d); 
		}
	}
	else if( MEMORY2 > 0) {
		uint8_t d = 0;
		uint16_t temp_d = MEMORY1;
		for (uint8_t i = 0; i < 4; ++i) {
			d = temp_d % 10;
			temp_d = temp_d / 10;
			draw_digit(i, d); 
		}
		for (uint8_t i = 4; i < 8, i++) {
			d = temp_d % 10;
			temp_d = temp_d / 10;
			draw_digit(i, d);
		}
	}
}
