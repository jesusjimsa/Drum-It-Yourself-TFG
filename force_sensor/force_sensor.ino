/**
 * Copyright 2020 Jesús Jiménez Sánchez
 *
 * Arduino program to control the force sensor in  the drums
 */


const int BUF_LEN = 10;

const int snare_sensor = A0;		// Snare Drum is connected to analog 0
const int hi_hat_sensor = A1;		// Hi-Hat is connected to analog 1
const int crash_sensor = A2;		// Crash Cymbal is connected to analog 2
const int high_tom_sensor = A3;		// High Tom is connected to analog 3
const int floor_tom_sensor = A4;		// Floor Tom is connected to analog 4
const int bass_sensor = A5;		// Bass Drum is connected to analog 5

int snare_read;		// the analog reading from the FSR resistor divider
int hi_hat_read;
int crash_read;
int high_tom_read;
int floor_tom_read;
int bass_read;

int read[6] = {0};	// Store all read values

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
	bass_read = analogRead(bass_sensor);

	read[0] = snare_read;
	read[1] = hi_hat_read;
	read[2] = crash_read;
	read[3] = high_tom_read;
	read[4] = floor_tom_read;
	read[5] = bass_read;

	if (read[0] < 200 && read[1] < 200 && read[2] < 200 && read[3] < 200 && read[4] < 200 && read[5] < 200) {
		Serial.print("0:0\n");
	}
	else {
		for (int i = 0; i < 6; i++) {
			if (!interval[i] && read[i] > 200) {

				Serial.print(i + 1);
				Serial.print(":");
				Serial.print(read[i]);

				interval[i] = true;
			}
			else {
				len = sprintf(buf, "%d:0", i + 1);

				for (int j = 0; j <= len; j++) {
					Serial.print(buf[j]);
				}
			}

			/*
				Print ':' to separate from the next instrument.
				Not needed in the last one.
			*/
			if (i != 5) {
				Serial.print(":");
			}
		}

		Serial.print("\n");
	}

	if (snare_read < 100) {
		interval[0] = false;
	}

	if (hi_hat_read < 100) {
		interval[1] = false;
	}

	if (crash_read < 100) {
		interval[2] = false;
	}

	if (high_tom_read < 100) {
		interval[3] = false;
	}

	if (floor_tom_read < 100) {
		interval[4] = false;
	}

	if (bass_read < 100) {
		interval[5] = false;
	}

	delay(50);
}
