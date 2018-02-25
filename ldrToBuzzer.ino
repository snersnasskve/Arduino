#define LDR_PIN A0
#define BUZZER_OUT 7

void setup() {
	pinMode(LDR_PIN, OUTPUT);
	
}

void loop() {
	tone(BUZZER_OUT, analogRead(LDR_PIN) * 4, 10);
}