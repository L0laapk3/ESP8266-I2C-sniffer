# ESP8266-I2C-sniffer
Simple passive I2C sniffer for ESP8266. Reads the data pin on every clock and puts it in a buffer. If it hasn't received anything for a while, empties the buffer to serial. Its recommended to run the ESP8266 at 160MHz for this.
