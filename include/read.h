/**
 * Copyright 2020 Jesús Jiménez Sánchez
 * 
 */

#ifndef READ_H_
#define READ_H_

/**
 * @brief Parse monitor serial output sent from Arduino
 * 
 * @param buf Read monitor output
 * 
 */
void parseInstruments(char *buf);

/**
 * @brief Read monitor serial output
 * 
 */
void readSerial();

#endif
