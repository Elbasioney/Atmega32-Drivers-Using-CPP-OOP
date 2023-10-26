#include "LCD.hpp"

// cnstructor for lcd 8bits mode 
LCD::LCD(pin_t pin1 , pin_t pin2 , pin_t pin3 , pin_t pin4 , pin_t pin5 ,pin_t pin6 , pin_t pin7 , pin_t pin8 , pin_t en , pin_t rs)
{
    this->mode = lcd_8bit_mode ;
    data[0].pin = pin1; data[1].pin = pin2; data[2].pin = pin3; data[3].pin = pin4; 
    data[4].pin = pin5; data[5].pin = pin6; data[6].pin = pin7; data[7].pin = pin8;
    data[0].mode = output; data[1].mode = output; data[2].mode = output; data[3].mode = output; 
    data[4].mode = output; data[5].mode = output; data[6].mode = output; data[7].mode = output;

    for(int i = 0 ; i < 8 ; i++){
        pin_direction_init(data[i].pin , data[i].mode);
    }
    this->rs.pin = rs ; this->rs.mode = output ; 
    this->en.pin = en ; this->en.mode = output ;
    pin_direction_init(this->rs.pin , this->rs.mode);
    pin_direction_init(this->en.pin , this->en.mode);
    init();
    this->c_row = 0 ; 
    this->c_column = 0 ;
}

// cnstructor for lcd 4bits mode 
LCD::LCD(pin_t pin1 , pin_t pin2 , pin_t pin3 , pin_t pin4 , pin_t en , pin_t rs)
{
    this->mode = lcd_4bit_mode ;
    data[0].pin = pin1; data[1].pin = pin2; data[2].pin = pin3; data[3].pin = pin4; 
    data[0].mode = output; data[1].mode = output; data[2].mode = output; data[3].mode = output; 
    for(int i = 0 ; i < 4 ; i++){
        pin_direction_init(data[i].pin , data[i].mode);
    }
    this->rs.pin = rs ; this->rs.mode = output ; 
    this->en.pin = en ; this->en.mode = output ;
    pin_direction_init(this->rs.pin , this->rs.mode);
    pin_direction_init(this->en.pin , this->en.mode);
    init();
    this->c_row = 0 ; 
    this->c_column = 0 ;
}

LCD::~LCD()
{

}

void LCD::print(const char* string)
{
    while(*string){
        lcd_sendData(*string);
        string++;
        this->c_column++;
        if(c_column == 20){
            c_column = 0 ;
            this->c_row++;
            if(this->c_row == 4){
                this->c_row = 0 ;
                this->c_column = 0 ;
            }else{

            }
        }else{

        }
    }
    
}

void LCD::clear(void)
{
    lcd_sendCommand(0x01); // clear
    this->c_row = 0 ;
    this->c_column = 0 ;
}

void LCD::setCursor(unsigned char row, unsigned char column)
{
    switch(row){
        case 0: lcd_sendCommand( 0x80 + column); break;
        case 1: lcd_sendCommand( 0xC0 + column); break;
        case 2: lcd_sendCommand( 0x94 + column); break;
        case 3: lcd_sendCommand( 0xD4 + column); break;
        default :   break ; 
    }
    this->c_row = row ;
    this->c_column = column ;
    _delay_ms(1);
}

void LCD::blinkOn()
{
    lcd_sendCommand(0x0F); // blink on
}

void LCD::blinkOff()
{
    lcd_sendCommand(0x0E); // blink off
}

void LCD::cursorRight()
{
    lcd_sendCommand(0x14); // move cursor to the right by one position
    this->c_column++;
    if(c_column == 20){
        c_column = 0 ;
        this->c_row++;
        if(this->c_row == 4){
            this->c_row = 0 ;
            this->c_column = 0 ;
        }else{

        }
    }else{

    }
}

void LCD::cursorLeft()
{
    lcd_sendCommand(0x10); // move cursor to the left by one position 
    this->c_column--;
    if(c_column == -1){
        c_column = 19 ;
        this->c_row--;
        if(c_row == -1){
            c_row = 0 ;
            c_column = 0 ;
        }else{

        }
    }else{

    }
}

void LCD::createCustomCharacter(char* customCharacter , int mem_pos)
{
    if(mem_pos <= 7){
        if(this->mode == lcd_8bit_mode){
            lcd_sendCommand((0x40 + (mem_pos*8)));
            for(int i = 0 ; i < 8 ; i++){
                lcd_sendData(customCharacter[i]);
            }
            setCursor(this->c_row , this->c_column);
            
        }else if(this->mode == lcd_4bit_mode){

        }else{

        }
        
    }else{

    }
}

int LCD::getCurrentColumn()
{
    return this->c_column ;
}

int LCD::getCurrentRow()
{
    return this->c_row ;
}

void LCD::printCustomCharacter(int mem_pos)
{
    lcd_sendData(mem_pos);
    this->c_column++;
        if(c_column == 20){
            c_column = 0 ;
            this->c_row++;
            if(this->c_row == 4){
                this->c_row = 0 ;
                this->c_column = 0 ;
            }else{

            }
        }else{

    }
}

// LCD initialization
void LCD::init(void)
{
    if(this->mode == lcd_8bit_mode){
        lcd_sendCommand(0x38);  // LCD 8bit mode
        _delay_ms(5);
        lcd_sendCommand(0x38);  // LCD 8bit mode
        _delay_us(150);
        lcd_sendCommand(0x38);  // LCD 8bit mode
        lcd_sendCommand(0x0C);  // LCD display on cursor off
        lcd_sendCommand(0x01);  // LCD clear
        lcd_sendCommand(0x06);  // LCD entry mode
        _delay_ms(10);
    }else if(this->mode == lcd_4bit_mode){

    }else{

    }
}

void LCD::lcd_sendCommand(unsigned char cmd)
{
    if(this->mode == lcd_8bit_mode){
        rs.write(LOW);
        data[0].write(((cmd >> 0) & 1));
        data[1].write(((cmd >> 1) & 1));
        data[2].write(((cmd >> 2) & 1));
        data[3].write(((cmd >> 3) & 1));
        data[4].write(((cmd >> 4) & 1));
        data[5].write(((cmd >> 5) & 1));
        data[6].write(((cmd >> 6) & 1));
        data[7].write(((cmd >> 7) & 1));  
        lcd_enableSignal();
        _delay_ms(2);

    }else if(this->mode == lcd_4bit_mode){


    }else{

    }
    
}

void LCD::lcd_sendData(unsigned char d)
{
    if(this->mode == lcd_8bit_mode){
        rs.write(HIGH);
        data[0].write(((d >> 0) & 1));
        data[1].write(((d >> 1) & 1));
        data[2].write(((d >> 2) & 1));
        data[3].write(((d >> 3) & 1));
        data[4].write(((d >> 4) & 1));
        data[5].write(((d >> 5) & 1));
        data[6].write(((d >> 6) & 1));
        data[7].write(((d >> 7) & 1)); 
        lcd_enableSignal();
        _delay_ms(2);

    }else if(this->mode == lcd_4bit_mode){


    }else{

    }
}

void LCD::lcd_enableSignal(void)
{
    en.write(HIGH);
    _delay_ms(2);
    en.write(LOW);
}

