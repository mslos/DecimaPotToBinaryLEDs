const uint8_t led[] = {2, 3, 4};

const int pot = A0;

//reading from pot
int decimalReading = 0;

//max and min value of pot resistance with 330Ohm in parallel
const int maxPot = 0; 
const int minPot = 28;
const int stepSize = 11;

//value between 0 and 7
uint8_t correspondingDecimal = 0;

const uint8_t smoothSize = 10;

const uint32_t c[7] = {minPot+stepSize*1,minPot+stepSize*2,minPot+stepSize*3,minPot+stepSize*4,minPot+stepSize*5,minPot+stepSize*6,minPot+stepSize*7};
int arr[3];
// 0|1|2|3|4|5|6|7

//function prototypes
int smoothening(int sample);


void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // declare LEDs for output
  for (int i = 2; i <= 4; i++) pinMode(led[i], OUTPUT);
  pinMode(13, OUTPUT);
  //do not need to declare analog read
}

void loop() {
decimalReading = analogRead(pot);
decimalReading = smoothening(decimalReading);
Serial.println(decimalReading);

//boundaries must be adjusted manually in case on non-linearity
//haven't tested for linearity at this time
delay(2);
chooseLED(decimalReading);
Serial.println(String(arr[0])+" "+String(arr[1])+" "+String(arr[2]));
ledWrite(arr);
}

int smoothening(int sample) {
  static uint32_t values[smoothSize];
  uint32_t sum = 0;
  for (int i = 0; i<smoothSize-1; i++) values[i] = values[i+1];

  values[smoothSize-1] = sample;
  for (int i = 0; i<smoothSize; i++) sum += values[i];
  return sum/smoothSize;
}

void chooseLED(int dec) {
    if(dec < c[0]) {
      arr[0] = 0;
      arr[1] = 0;
      arr[2] = 0;
    }
    else if(dec < c[1]) {
      arr[0] = 1;
      arr[1] = 0;
      arr[2] = 0;
    }
    else if(dec < c[2]) {
      arr[0] = 0;
      arr[1] = 1;
      arr[2] = 0;
    }
    else if(dec < c[3]) {
      arr[0] = 1;
      arr[1] = 1;
      arr[2] = 0;
    }
    else if(dec < c[4]) {
      arr[0] = 0;
      arr[1] = 0;
      arr[2] = 1;
    }
    else if(dec < c[5]) {
      arr[0] = 1;
      arr[1] = 0;
      arr[2] = 1;
    }
    else if(dec < c[6]) {
      arr[0] = 0;
      arr[1] = 1;
      arr[2] = 1;
    }
    else {
      arr[0] = 1;
      arr[1] = 1;
      arr[2] = 1;
    }
  return;
}

void ledWrite(int led[3]) {
  for (int i = 2; i <= 4; i++) digitalWrite(i, led[i-2]);
}

