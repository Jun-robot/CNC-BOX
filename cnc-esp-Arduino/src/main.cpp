#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define ultrasoundPin 32// Trigger Pin
#define top_led_pin 14
#define bottom_led_pin 13

#define top_led_num 44*3
#define bottom_led_num 44+29+29

Adafruit_NeoPixel top_led = Adafruit_NeoPixel(top_led_num, top_led_pin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel bottom_led = Adafruit_NeoPixel(bottom_led_num, bottom_led_pin, NEO_GRB + NEO_KHZ800);

double Duration = 0; //受信した間隔
double Distance = 0; //距離

void setup() {
	Serial.begin(115200);
  Serial.println("Hello");
	
  top_led.begin();
	bottom_led.begin();

	top_led.setPixelColor(3, 127, 127, 0);
	bottom_led.setPixelColor(3, 127, 127, 127);
	top_led.show();
	bottom_led.show();

	delay(1000);
}

void loop() {
	pinMode( ultrasoundPin, OUTPUT );
  digitalWrite(ultrasoundPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite( ultrasoundPin, HIGH ); //超音波を出力
  delayMicroseconds( 10 ); //
  digitalWrite( ultrasoundPin, LOW );

	pinMode( ultrasoundPin, INPUT );
  Duration = pulseIn( ultrasoundPin, HIGH ,10000); //センサからの入力
  if (Duration > 0) {
    Duration = Duration/2; //往復距離を半分にする
    Distance = Duration*340*100/1000000; // 音速を340m/sに設定
    Serial.print("Distance:");
    Serial.print(Distance);
    Serial.println(" cm");
  }else{
		Serial.println(Duration);
		Distance = 0;
	}
  delay(300);
	
	if(Distance > 10 || Distance == 0){
		for(int i=0; i<top_led_num; i++){
			top_led.setPixelColor(i, 127, 127, 127);
		}
		for(int i=0; i<bottom_led_num; i++){
			bottom_led.setPixelColor(i, 5, 20, 20);
		}
	}else{
		for(int i=0; i<top_led_num; i++){
			top_led.setPixelColor(i, 0, 0, 0);
		}
		for(int i=0; i<bottom_led_num; i++){
			bottom_led.setPixelColor(i, 0, 0, 0);
		}
	}
	top_led.show();
	bottom_led.show();

}