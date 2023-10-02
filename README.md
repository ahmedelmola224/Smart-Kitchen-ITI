# Smart-Kitchen-ITI
 The project involved creating a smart kitchen system with a master node, stove node, microwave node, washing machine node, and fire alarm node.
 The master node has a password that is saved on external EEPROM that can be changed at any time. It can send commands to the stove to turn on/off specific flames, set the microwave timer (only if the door is closed) and cannot set time if microwave is working, select a specific mode for the washing machine. Get the system state from fire alarm node that can send a signal to the master if there is a fire to lock the system and opens a buzzer.
 
To complete this project, I utilized modules such as GPIO, ADC, UART, SPI, I2C, DC motor, servo motor, SSD, EEPROM, LCD, and keypad.
