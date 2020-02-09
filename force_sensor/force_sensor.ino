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

int read[6] = {0};

int choice;

int interval[6] = {false};		// Don't read when value is small

char buf[BUF_LEN];
int len = 0;

int myMax(int one, int other) {
	return (one > other ? one : other);
}

/* 
	Parameters: The six sensors' values.
	Returns: Identifier of the sensor with the highest value.
			 -1 if the read value is less than 200.
*/
int maxSix(int first, int second, int third, int fourth, int fifth, int sixth) {
	int result = -1;
	int max_value = 0;

	max_value = myMax(first, second);
	max_value = myMax(max_value, third);
	max_value = myMax(max_value, fourth);
	max_value = myMax(max_value, fifth);
	max_value = myMax(max_value, sixth);

	if (max_value == first) {
		result = 0;
	}
	else if (max_value == second) {
		result = 1;
	}
	else if (max_value == third) {
		result = 2;
	}
	else if (max_value == fourth) {
		result = 3;
	}
	else if (max_value == fifth) {
		result = 4;
	}
	else if (max_value == sixth) {
		result = 5;
	}

	if (max_value < 200) {
		result = -1;
	}

	return result;
}

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

	choice = maxSix(snare_read, hi_hat_read, crash_sensor, high_tom_read, floor_tom_read, bass_read);

	if (choice != -1 && !interval[choice]) {
		len = sprintf (buf, "%d:%d\n", choice + 1, read[choice]);

		for(int i = 0; i <= len; i++) {
			Serial.print(buf[i]);
		}

		interval[choice] = true;
	}
	else {
		Serial.print("0:0\n");
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
