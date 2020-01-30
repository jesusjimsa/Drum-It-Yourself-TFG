/**
 * Copyright 2020 Jesús Jiménez Sánchez
 * 
 * Arduino program to control the force sensor in  the drums
 */


const int BUF_LEN = 10;

const int snare_sensor = 0;		// Snare is connected to analog 0
const int hi_hat_sensor = 1;		// FSR is connected to analog 0
const int crash_sensor = 2;		// FSR is connected to analog 0
const int high_tom_sensor = 3;		// FSR is connected to analog 0
const int floor_tom_sensor = 4;		// FSR is connected to analog 0
const int bass_sensor = 5;		// FSR is connected to analog 0

int snare_read;		// the analog reading from the FSR resistor divider
int hi_hat_read;		// the analog reading from the FSR resistor divider
int crash_read;		// the analog reading from the FSR resistor divider
int high_tom_read;		// the analog reading from the FSR resistor divider
int floor_tom_read;		// the analog reading from the FSR resistor divider
int bass_sensor_read;		// the analog reading from the FSR resistor divider

int interval[6] = {false};		// Don't read when value is small

char buf[BUF_LEN];
int len = 0;

void setup(void) {
	Serial.begin(9600);
}

void loop(void) {
	snare_read = analogRead(snare_sensor);
	hi_hat_read = analogRead(hi_hat_sensor);
	crash_read = analogRead(crash_sensor);
	high_tom_read = analogRead(high_tom_sensor);
	floor_tom_read = analogRead(floor_tom_sensor);
	bass_sensor_read = analogRead(bass_sensor);

	if (!interval[snare_sensor] && snare_read >= 200) {
		interval[snare_sensor] = true;

		len = sprintf (buf, "%d:%d\n", snare_sensor + 1, snare_read);

		for(int i = 0; i <= len; i++) {
			Serial.print(buf[i]);
		}
	}
	else if (!interval[hi_hat_sensor] && hi_hat_sensor >= 200) {
		interval[hi_hat_sensor] = true;

		len = sprintf (buf, "%d:%d\n", hi_hat_sensor + 1, hi_hat_read);

		for(int i = 0; i <= len; i++) {
			Serial.print(buf[i]);
		}
	}
	else if (!interval[crash_sensor] && crash_sensor >= 200) {
		interval[crash_sensor] = true;

		len = sprintf (buf, "%d:%d\n", crash_sensor + 1, crash_read);

		for(int i = 0; i <= len; i++) {
			Serial.print(buf[i]);
		}
	}
	else if (!interval[high_tom_sensor] && high_tom_sensor >= 200) {
		interval[high_tom_sensor] = true;

		len = sprintf (buf, "%d:%d\n", high_tom_sensor + 1, high_tom_read);

		for(int i = 0; i <= len; i++) {
			Serial.print(buf[i]);
		}
	}
	else if (!interval[floor_tom_sensor] && floor_tom_sensor >= 200) {
		interval[floor_tom_sensor] = true;

		len = sprintf (buf, "%d:%d\n", floor_tom_sensor + 1, floor_tom_read);

		for(int i = 0; i <= len; i++) {
			Serial.print(buf[i]);
		}
	}
	else if (!interval[bass_sensor] && bass_sensor >= 200) {
		interval[bass_sensor] = true;

		len = sprintf (buf, "%d:%d\n", bass_sensor + 1, bass_read);

		for(int i = 0; i <= len; i++) {
			Serial.print(buf[i]);
		}
	}
	else {
		Serial.print("0:0\n");
	}

	if (snare_read < 100) {
		interval[snare_sensor] = false;
	}

	if (hi_hat_read < 100) {
		interval[hi_hat_sensor] = false;
	}

	if (crash_read < 100) {
		interval[crash_sensor] = false;
	}

	if (high_tom_read < 100) {
		interval[high_tom_sensor] = false;
	}

	if (floor_tom_read < 100) {
		interval[floor_tom_sensor] = false;
	}
	
	if (bass_sensor_read < 100) {
		interval[bass_sensor] = false;
	}

	delay(50);
}
