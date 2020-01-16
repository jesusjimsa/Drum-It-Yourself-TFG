/**
 * Copyright 2020 Jesús Jiménez Sánchez
 * 
 * Arduino program to control the force sensor in  the drums
 */


const int BUF_LEN = 10;

const int fsrAnalogPin = 0;		// FSR is connected to analog 0
int fsrReading;		// the analog reading from the FSR resistor divider
int instrument = 1;
int volume;

int interval = false;		// [200, 400)

char buf[BUF_LEN];
int len = 0;

void setup(void) {
	Serial.begin(9600);		// We'll send debugging information via the Serial monitor
}

void loop(void) {
	fsrReading = analogRead(fsrAnalogPin);
	volume = 0;

	if (!interval && fsrReading >= 200) {
		interval = true;
		// volume = fsrReading;
		len = sprintf (buf, "%d:%d\n", instrument, fsrReading);

		for(int i = 0; i <= len; i++) {
			Serial.print(buf[i]);
		}
	}

	if (fsrReading < 100) {
		interval = false;
	}

	delay(50);
}
