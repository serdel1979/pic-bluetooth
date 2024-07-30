void main() {
    // Configuraci�n inicial
    PORTA = 0;  // Apagar todos los LEDs
    PORTB = 0;

    // Configuraci�n del puerto A como salida
    TRISA = 0;  // Configurar todos los pines del puerto A como salida

    // Configuraci�n del puerto B
    TRISB.F1 = 1;  // Configurar RB1 (RX) como entrada
    TRISB.F2 = 1;  // Configurar RB2 (TX) como entrada
    TRISB.F7 = 0;  // Configurar los dem�s pines de RB como salida

    // Inicializaci�n del UART
    UART1_Init(9600);
    Delay_ms(1000);

    // Enviar comandos AT al m�dulo HC-06
    UART1_Write_Text("AT+NAMEPrueba");
    Delay_ms(2000);

    UART1_Write_Text("AT+BAUD4");
    Delay_ms(2000);

    UART1_Write_Text("AT+PIN2711");
    Delay_ms(2000);

    PORTB.F7 = 1;

    while(1) {
        // Verificar si hay datos disponibles en el UART
        if (UART1_Data_Ready()) {
            // Leer el dato recibido
            char received = UART1_Read();

            // Encender o apagar los LEDs seg�n el dato recibido
            switch (received) {
                case '4':
                    PORTA = 0b00000001;  // Encender RA0, apagar los dem�s
                    break;
                case '6':
                    PORTA = 0b00000010;  // Encender RA1, apagar los dem�s
                    break;
                case '8':
                    PORTA = 0b00000101;  // Encender RA2 y RA0, apagar los dem�s
                    break;
                case '2':
                    PORTA = 0b00001010;  // Encender RA1 y RA3, apagar los dem�s
                    break;
                default:
                    PORTA = 0;  // Apagar todos los LEDs si se recibe un car�cter no esperado
                    break;
            }
        }
    }
}



