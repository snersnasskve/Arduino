const int led_count = 7;
int first_led = 1;
int brightnesses[led_count];
int step_delay = 300; // Time delay between san steps, in milliseconds
int step_direction = 1; // Determines if we are scanning lfet to right or right to left
int bright_led=3; // Index of the current scan led (the brightest one)
int medium_led=2; // Index of the previous scan led (a bit dimmer)
int dim_led=1; // Index of the previous previous scan led (very dim)
int off_led=0; // Index of the previous previous previous scan led (dark)
long current_millis = 0;
long previous_millis = 0;
int loop_count=100;
void setup() {
for (int i=0; i<led_count; i++){
pinMode(first_led + i, OUTPUT);
brightnesses[i] = 50;
}
}
void loop() {
  current_millis = millis();
  if (current_millis > previous_millis + step_delay){
    // Reverse the scan if we've reached one end
      if (bright_led==0){
        step_direction=1;
        //brightnesses[0]=10;
      }
      // Reverse the scan if we've reached the other end
     else if (bright_led==led_count){
      step_direction=-1;
//brightnesses[led_count]=10;
   }
  // Set the brightnesses of the glowing embers
  off_led = dim_led;
  medium_led = bright_led;
  bright_led = bright_led + step_direction;
  brightnesses[bright_led]=100;
  brightnesses[medium_led]=30;
  brightnesses[dim_led]=5;
  brightnesses[off_led]=0;
  previous_millis = current_millis;
  }
  loop_count = loop_count - 1;
  if (loop_count==0){
    loop_count = 100;
  }
  for (int i=0;i<led_count;i++){
    digitalWrite(first_led + i, loop_count <= brightnesses[i]);
  }
}
