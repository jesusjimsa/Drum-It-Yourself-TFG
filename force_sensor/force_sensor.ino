/*********************************************************************
 *********************************************************************
 *********************** Jesús Jiménez Sánchez ***********************
 *********************************************************************
*********************************************************************/
/*
	Arduino program to control the force sensor in  the drums
*/


int fsrAnalogPin = 0;	// FSR is connected to analog 0
int fsrReading;		// the analog reading from the FSR resistor divider

int interval = false;		// [200, 400)

void setup(void) {
	Serial.begin(9600);	// We'll send debugging information via the Serial monitor
}

void loop(void) {
	fsrReading = analogRead(fsrAnalogPin);

	if (!interval) {
		if (fsrReading >= 200 && fsrReading < 400) {
			interval = true;
			Serial.println(fsrReading);
		}
		else if (fsrReading >= 400 && fsrReading < 800) {
			interval = true;
			Serial.println(fsrReading);
		}
		else if (fsrReading >= 800) {
			interval = true;
			Serial.println(fsrReading);
		}
	}

	if (fsrReading < 100) {
		interval = false;
	}

	delay(50);
}
