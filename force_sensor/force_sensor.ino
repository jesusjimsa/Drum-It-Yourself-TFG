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

int choice;		// Main patch played
int also_playing;   // Secondary patch for combined sounds
int combined_index;     // Index for combined sounds

int interval[6] = {false};		// Don't read when value is small

char buf[BUF_LEN];
int len = 0;

int myMax(int one, int other) {
	return (one > other ? one : other);
}

/**
 *
 * Parameters: The six sensors' values and the value to ignore.
 * Returns: Identifier of the sensor with the highest value.
 * 			-1 if the read value is less than 200.
 *
*/
int maxSix(int first, int second, int third, int fourth, int fifth, int sixth, int ignore) {
	int result = -1;
	int max_value = 0;

	if (ignore != 1) {
		max_value = first;
	}

	if (ignore != 2) {
		max_value = myMax(max_value, second);
	}

	if (ignore != 3) {
		max_value = myMax(max_value, third);
	}

	if (ignore != 4) {
		max_value = myMax(max_value, fourth);
	}

	if (ignore != 5) {
		max_value = myMax(max_value, fifth);
	}

	if (ignore != 6) {
		max_value = myMax(max_value, sixth);
	}

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

/**
 * 	Check indexes to create the combined index
 */
int combinedSound(int main, int secondary) {
	int combined = -1;

	if (secondary != -1) {
		switch (main) {
			case 0:
				switch (secondary) {
					case 1:
						combined = 9;
						break;
					case 2:
						combined = 10;
						break;
					case 3:
						combined = 11;
						break;
					case 4:
						combined = 12;
						break;
					case 5:
						combined = 13;
						break;
				}
				break;
			case 1:
				switch (secondary) {
					case 0:
						combined = 9;
						break;
					case 2:
						combined = 14;
						break;
					case 3:
						combined = 15;
						break;
					case 4:
						combined = 16;
						break;
					case 5:
						combined = 17;
						break;
				}
				break;
			case 2:
				switch (secondary) {
					case 0:
						combined = 10;
						break;
					case 1:
						combined = 14;
						break;
					case 3:
						combined = 18;
						break;
					case 4:
						combined = 19;
						break;
					case 5:
						combined = 20;
						break;
				}
				break;
			case 3:
				switch (secondary) {
					case 0:
						combined = 11;
						break;
					case 1:
						combined = 15;
						break;
					case 2:
						combined = 18;
						break;
					case 4:
						combined = 21;
						break;
					case 5:
						combined = 22;
						break;
				}
				break;
			case 4:
				switch (secondary) {
					case 0:
						combined = 12;
						break;
					case 1:
						combined = 16;
						break;
					case 2:
						combined = 19;
						break;
					case 3:
						combined = 21;
						break;
					case 5:
						combined = 23;
						break;
				}
				break;
			case 5:
				switch (secondary) {
					case 0:
						combined = 13;
						break;
					case 1:
						combined = 17;
						break;
					case 2:
						combined = 20;
						break;
					case 3:
						combined = 22;
						break;
					case 4:
						combined = 23;
						break;
				}
				break;
			default:
				break;
		}
	}

	return combined;
}

void setup(void) {
	Serial.begin(9600);
}

void loop(void) {
	choice = -1;
	also_playing = -1;
	combined_index = -1;

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

	choice = maxSix(snare_read, hi_hat_read, crash_read, high_tom_read, floor_tom_read, bass_read, -1);

	// Don't read a second sensor if the first one doesn't return a valid value
	if (choice != -1) {
		also_playing = maxSix(snare_read, hi_hat_read, crash_read, high_tom_read, floor_tom_read, bass_read, choice);
		combined_index = combinedSound(choice, also_playing);
	}

	/**
	 * Boolean statements are evaluated from left to right, that way this will never try to access
	 * interval in the -1 position.
	*/
	if (combined_index != -1 && !interval[choice] && !interval[also_playing]) {
		/**
		 * The volume of the combined sound will be the one read from the main instrument.
		*/
		len = sprintf(buf, "%d:%d\n", combined_index + 1, read[choice]);

		for (int i = 0; i <= len; i++) {
			Serial.print(buf[i]);
		}

		interval[choice] = true;
		interval[also_playing] = true;
	}
	else if (choice != -1 && !interval[choice]) {
		len = sprintf(buf, "%d:%d\n", choice + 1, read[choice]);

		for (int i = 0; i <= len; i++) {
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
