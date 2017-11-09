#include <PololuLedStrip.h>

// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<12> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
#define LED_COUNT 98
rgb_color colors[LED_COUNT];

char rgbIn[3];
int ledsRead;

void setup()
{
  Serial.begin(115200);
  Serial.println(" Ready to receive colors!!");
  //Serial.setTimeout(0);

  ledsRead = 0;

  testLights();
}

void loop()
{

  if (Serial.peek() == 101) { // 101 => CODE FOR "FINISHED SENDING ALL LEDS"
    //Serial.write(101); 
    Serial.read();
    ledsRead = 0;
  }


  while (ledsRead < LED_COUNT) {

    if (Serial.available()) {



      //for (int i = 0; i < LED_COUNT; i++) {


      Serial.readBytes(rgbIn, 3);

      //if(rgbIn[0] > 100)break;


      colors[ledsRead].red = map(rgbIn[0], 0, 100, 0, 255);
      colors[ledsRead].green = map(rgbIn[1], 0, 100, 0, 255);
      colors[ledsRead].blue = map(rgbIn[2], 0, 100, 0, 255);


      /*
        Serial.print(rgbIn[0]);
        Serial.print(" - ");
        Serial.print(rgbIn[1]);
        Serial.print(" - ");
        Serial.println(rgbIn[2]);
        Serial.println("=============");
      */
      //Serial.write(rgbIn, 3);


      //}

      //Serial.flush();
      ledsRead++;
    }


  }

  ledStrip.write(colors, LED_COUNT);

  //ledsRead = 0;



  //    for (int i = 0; i < LED_COUNT; i++) {
  //      colors[i].red = 255;
  //      colors[i].green = 255;
  //      colors[i].blue = 255;
  //    }


  delay(10);
}

void testLights() {

  clearLights();

  for (int i = 0; i < LED_COUNT; i++) {

    colors[i].red = 255;
    colors[i].green = 255;
    colors[i].blue = 255;

    ledStrip.write(colors, LED_COUNT);

    delay(50);

  }

  delay(500);

  //clearLights();


}

void clearLights() {
  for (int i = 0; i < LED_COUNT; i++) {

    colors[i].red = 0;
    colors[i].green = 0;
    colors[i].blue = 0;

    ledStrip.write(colors, LED_COUNT);
  }
}


