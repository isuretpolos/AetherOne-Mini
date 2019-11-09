
AetherOneForArduino *aetherOne;

void setup() {
  aetherOne = new AetherOneForArduino();
  aetherOne->init();
  Serial.begin(9600);
}

void loop() {
  Serial.println(aetherOne->analyseArray(180));
}
