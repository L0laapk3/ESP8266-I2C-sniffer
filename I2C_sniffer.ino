// assign pin values here
const char sda_pin = D2;
const char scl_pin = D1;

bool buf[4096];
bool* bufI = &buf[0];
const uint32_t PAUSE = 1 << 20;

uint32_t waitCl(bool expected) {
    uint32_t i = 0;
    while (digitalRead(scl_pin) != expected) {
      while ((digitalRead(scl_pin) != expected) && (++i % PAUSE != 0)) ;

      if (i % PAUSE == 0) {
        uint32_t i = 0;
        while (&buf[i] != bufI) {
          Serial.print(buf[i++]);
          if (i % 9 == 0)
            Serial.print(' ');
        }
        if (bufI != &buf[0])
          Serial.print('\n');
        bufI = &buf[0];
        yield();
      }
    }
    return i;
}

void setup() {
    Serial.begin(115200);
    pinMode(sda_pin, INPUT);
    pinMode(scl_pin, INPUT);
    
    Serial.println("\nReady!");
    
    while (true) {
      uint32_t incr = waitCl(HIGH);
      *bufI++ = digitalRead(sda_pin);
      waitCl(LOW);
    }
}

void loop() { }
