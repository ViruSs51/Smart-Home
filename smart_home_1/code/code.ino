#define LED 2
#define MP A0

int MP_value;
bool detect = false;
int reseted = 0;
int time1 = 0, time2 = 0;
int MP_values_time_deapason = 10;
bool LED_status = false;


void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(MP, INPUT);
}

void loop() {
  MP_value = analogRead(MP);

  if (MP_value > 700) detect = true;
  else {
    detect = false;
    reseted += 1;
  }

  int actual_time = millis();
  if ((time1 != 0 && (time1 + MP_values_time_deapason*45 < actual_time)) || (time2 != 0 && (time2 + MP_values_time_deapason*22.5 < actual_time))) time1 = 0, time2 = 0;

  if (detect) {
    if (time1 == 0) {
      time1 = millis();
      reseted = 0;
    } else if (time1 != 0 && time2 == 0 && reseted > 10) time2 = millis();
  }

  if (time1 != 0 && time2 != 0) {
    if (time2 - time1 >= MP_values_time_deapason) {
      LED_status = !LED_status;
      time1 = 0, time2 = 0;
    } else time1 = 0, time2 = 0;
  }

  digitalWrite(LED, LED_status);
}
