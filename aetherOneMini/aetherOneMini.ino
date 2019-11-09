/**
   Copyright by Isuret Polos 2019

   -----------------------------------------
   For the "AzDelivery Nano" please note that you need the CH340 USB driver (I have downloaded them from https://sparks.gogo.co.nz/ch340.html),
   and you need to use specific settings for uploading the software:
   - Board: Arduino Nano
   - Processor: AtMega 328P (old Bootloader)
   - Port: see what changes after installing the driver and reconnecting the board
   - Programmer: AVR ISP

   RX - red - GPIO 0
   TX - green - GPIO 1
*/

class AetherOneForArduino {

  private:
    boolean onOff = true;
    String colour[4] = { "Blue", "Red",
                         "Orange", "Yellow"
                       };
  public:

    void init() {
      pinMode(LED_BUILTIN, OUTPUT);
    }

    int generateTRNGseed() {

      int trngNumber = 0;
      int bitNumber = 0;
      int trng_bitmask_x = 0;
      int trng_seed_rounds = 0;
      int trng_seed = 0;

      while (trng_seed_rounds < 12) {
        if (analogRead(0) > analogRead(0)) {
          bitNumber |= 1UL << trng_bitmask_x;
        } else {
          bitNumber &= ~(1UL << trng_bitmask_x);
        }

        trng_bitmask_x++;

        if (trng_bitmask_x >= 16) {
          trng_bitmask_x = 0;
          trng_seed_rounds++;
          trng_seed += bitNumber;
          bitNumber = 0;
        }

      }

      if (trng_seed < 0) {
        trng_seed = trng_seed * -1;
      }

      return trng_seed;
    }

    int randomInt(int max) {
      randomSeed(generateTRNGseed());
      long randNumber = random(max);
      return randNumber;
    }
};

AetherOneForArduino *aetherOne;

void setup() {
  aetherOne = new AetherOneForArduino();
  aetherOne->init();
  Serial.begin(9600);
}

void loop() {

  Serial.println(aetherOne->randomInt(1000));
}


