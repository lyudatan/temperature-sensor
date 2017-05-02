#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>

#define TFT_CS     10
#define TFT_RST    8                      
#define TFT_DC     9
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

// Data wire is plugged into pin 6 on the Arduino
#define ONE_WIRE_BUS 6
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

float maxTemperature=0;
float minTemperature=200;
float tempF=0;
char charMinTemperature[10];
char charMaxTemperature[10];
char temperatureChar[10];
char temperatureCharF[10];

float temperature = 0;
float previousTemperature = 500;


void setup () 
{
    tft.initR(INITR_BLACKTAB);
    tft.fillScreen(ST7735_BLACK);

  
    printText("TEMPERATURE", ST7735_GREEN,30,15,1);  // Temperature Static Text
    printText("MAX", ST7735_RED,95,130,1);
    printText("MIN", ST7735_BLUE,18,130,1);

}

uint32_t old_ts;

void loop () 
{
  sensors.requestTemperatures(); // Send the command to get temperatures
  temperature = sensors.getTempCByIndex(0);
  tempF = (temperature * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  
if(temperature != previousTemperature)
  {

    //celsius
    previousTemperature = temperature;
    String temperatureString = String(temperature,1);
    temperatureString.toCharArray(temperatureChar,10);
    tft.fillRect(10,55,128,30,ST7735_BLACK);
    printText(temperatureChar, ST7735_WHITE,10,55,3);
    printText("o", ST7735_WHITE,90,50,2);
    printText("C", ST7735_WHITE,105,55,3);

    //farenhait
    String temperatureStringF = String(tempF,1);
    temperatureStringF.toCharArray(temperatureCharF,10);
    tft.fillRect(20,90,128,30,ST7735_BLACK);
    printText(temperatureCharF, ST7735_WHITE,20,90,2);
    printText("o", ST7735_WHITE,80,85,1);
    printText("F", ST7735_WHITE,90,90,2);

    //update at change
    if(temperature>maxTemperature)
    {
      maxTemperature = temperature;
      dtostrf(maxTemperature,5, 1, charMaxTemperature); 
      tft.fillRect(75,140,36,18,ST7735_BLACK);
      printText(charMaxTemperature, ST7735_WHITE,80,145,1);
      printText("o", ST7735_WHITE,112,140,1);
      printText("C", ST7735_WHITE,118,145,1);

    }
    if(temperature<minTemperature)
    {
      minTemperature = temperature;
      dtostrf(minTemperature,5, 1, charMinTemperature); 
      tft.fillRect(3,142,33,20,ST7735_BLACK);
      printText(charMinTemperature, ST7735_WHITE,3,145,1);
      printText("o", ST7735_WHITE,35,140,1);
      printText("C", ST7735_WHITE,41,145,1);
    }
  }
    delay(1000);
}


void printText(char *text, uint16_t color, int x, int y,int textSize)
{
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(textSize);
  tft.setTextWrap(true);
  tft.print(text);
}





