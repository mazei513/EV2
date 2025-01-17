#include "EV2_CAN.h"
#include "math.h"

/****************************************************************/
// Motor Controller
int Global_MC_speed  = -1; // 1 revolution = 0.533m = 0.032 kph
int Global_MC_kph = -1;
int Global_MC_torque = -1;        
int Global_Air_temp = -1;                   
int Global_MC_temp   = -1;
int Global_MC_motortemp = -1;
int Global_MC_voltage = -1;
int Global_MC_current = -1;
int Global_MC_power = -1;
int Global_MC_corestatus = -1;
int Global_MC_error = -1;
int mc_message_count = 0;
int Global_rfe = -1;
int Global_frg = -1;
int Global_MC_go = -1;

// BMS
int Global_BMS_voltage = -1;
int Global_BMS_minvoltage = -1;
int Global_BMS_maxvoltage = -1;
int Global_BMS_current = -1;
int Global_BMS_soc = -1;
int Global_BMS_temp = -1;
int Global_BMS_mintemp = -1;
int Global_BMS_maxtemp = -1;
int Global_BMS_status = -1;
int Global_BMS_state = -1;
int Global_BMS_capacity = -1;

// EV2
int Global_car_state = -1;
#define IDLE 0
#define DRIVE 1
#define FAULT 2
int Global_battfault = -1;
int Global_isofault = -1;
int Global_throttle1 = -1;
int Global_throttle2 = -1;
int Global_avethrottle = -1;
int Global_brake = -1;
float Global_LVBATT_V = -1;
float Global_HV_V = -1;
int Global_error = -1;
int Global_tsa = -1;
int Global_relay = -1;
int Global_high_current = -1;
int Global_insulation_pwm = -1;
int Global_start_button = -1;

void enable_drive(bool enable) {
    set_rfe_frg(enable,enable);
    set_tracsys_relay(enable);
}

void set_rfe_frg(bool rfe, bool frg) {
    // RFE (p37)
    pinMode(37, OUTPUT);
    digitalWrite(37, rfe);
    // FRG (p35)
    pinMode(35, OUTPUT);
    digitalWrite(35, frg);

    Global_rfe = (int)rfe;
    Global_frg = (int)frg;
}
void set_tracsys_relay(bool x) {
    // tractive system shutdown relay
    pinMode(33, OUTPUT);
    digitalWrite(33, x);

    Global_relay = (int)x;
}

void updateDB(void) {
    Serial.print("RPM = ");
    Serial.println(Global_MC_speed);
    Serial.print("TQE = ");
    Serial.println(Global_MC_torque);
    Serial.print("MTMP = ");
    Serial.println(Global_MC_motortemp);
    Serial.print("MCTMP = ");
    Serial.println(Global_MC_temp);
    Serial.print("MCV = ");
    Serial.println(Global_MC_voltage);
    Serial.print("MCC = ");
    Serial.println(Global_MC_current);
    Serial.print("RFE = ");
    Serial.println(Global_rfe);
    Serial.print("FRG = ");
    Serial.println(Global_frg);

    Serial.print("BFAULT = ");
    Serial.println(Global_battfault);
    Serial.print("IFAULT = ");
    Serial.println(Global_isofault);
    Serial.print("SRELAY = ");
    Serial.println(Global_relay);
    Serial.print("TSA = ");
    Serial.println(Global_tsa);
    
    Serial.print("BVOLT = ");
    Serial.println(Global_BMS_voltage);
    Serial.print("BCUR = ");
    Serial.println(Global_BMS_current);
    Serial.print("SOC = ");
    Serial.println(Global_BMS_soc);
    Serial.print("BTMP = ");
    Serial.println(Global_BMS_temp);
    Serial.print("BMINTMP = ");
    Serial.println(Global_BMS_mintemp);
    Serial.print("BMAXTMP = ");
    Serial.println(Global_BMS_maxtemp);
    Serial.print("BSTAT = ");
    Serial.println(Global_BMS_status);

    Serial.print("LV = ");
    Serial.println(Global_LVBATT_V);
    Serial.print("HV = ");
    Serial.println(Global_HV_V);

    Serial.print("AVE_THROTTLE = ");
    Serial.println(Global_avethrottle);
    Serial.print("BRAKE = ");
    Serial.println(Global_brake);


    Serial.println();
    Serial.println();
}

void updateDB2(void) {
    Serial.print("@");

    Serial.print(Global_MC_speed);
    Serial.print(",");
    Serial.print(Global_MC_torque);
    Serial.print(",");
    Serial.print(Global_MC_motortemp);
    Serial.print(",");
    Serial.print(Global_MC_temp);
    Serial.print(",");
    Serial.print(Global_MC_voltage);
    Serial.print(",");
    Serial.print(Global_MC_current);
    Serial.print(",");
    Serial.print(Global_MC_voltage*Global_MC_current);
    Serial.print(",");
    Serial.print(Global_rfe);
    Serial.print(",");
    Serial.print(Global_frg);
    Serial.print(",");
    
    Serial.print(Global_BMS_voltage);
    Serial.print(",");
    Serial.print(Global_BMS_temp);
    Serial.print(",");
    Serial.print(Global_BMS_mintemp);
    Serial.print(",");
    Serial.print(Global_BMS_maxtemp);
    Serial.print(",");
    Serial.print(Global_BMS_status);
    Serial.print(",");
    
    Serial.print(Global_battfault);
    Serial.print(",");
    Serial.print(Global_isofault);
    Serial.print(",");
    Serial.print(Global_avethrottle);
    Serial.print(",");
    Serial.print(Global_brake);
    Serial.print(",");
    Serial.print(Global_LVBATT_V);
    Serial.print(",");
    Serial.print(Global_HV_V);
    Serial.print(",");
    Serial.print(Global_tsa);
    Serial.print(",");
    Serial.print(Global_relay);
    Serial.print(",");
    
    Serial.print(Global_car_state);

    Serial.print("#");
}
void updateDB3(void) {
    Serial.print("@");
    // Motor Controller
    Serial.print(Global_MC_speed);
    Serial.print(",");
    Serial.print(Global_MC_kph);
    Serial.print(",");
    Serial.print(Global_MC_torque);
    Serial.print(",");
    Serial.print(Global_Air_temp);
    Serial.print(",");
    Serial.print(Global_MC_temp);
    Serial.print(",");
    Serial.print(Global_MC_motortemp);
    Serial.print(",");
    Serial.print(Global_MC_voltage);
    Serial.print(",");
    Serial.print(Global_MC_current);
    Serial.print(",");
    Serial.print(Global_MC_voltage*Global_MC_current);
    Serial.print(",");
    Serial.print(Global_MC_corestatus);
    Serial.print(",");
    Serial.print(Global_MC_error);
    Serial.print(",");
    Serial.print(mc_message_count);
    Serial.print(",");
    Serial.print(Global_rfe);
    Serial.print(",");
    Serial.print(Global_frg);
    Serial.print(",");
    Serial.print(Global_MC_go);
    Serial.print(",");
    // BMS
    Serial.print(Global_BMS_voltage);
    Serial.print(",");
    Serial.print(Global_BMS_minvoltage);
    Serial.print(",");
    Serial.print(Global_BMS_maxvoltage);
    Serial.print(",");
    Serial.print(Global_BMS_current);
    Serial.print(",");
    Serial.print(Global_BMS_soc);
    Serial.print(",");
    Serial.print(Global_BMS_temp);
    Serial.print(",");
    Serial.print(Global_BMS_mintemp);
    Serial.print(",");
    Serial.print(Global_BMS_maxtemp);
    Serial.print(",");
    Serial.print(Global_BMS_status);
    Serial.print(",");
    Serial.print(Global_BMS_state);
    Serial.print(",");
    Serial.print(Global_BMS_capacity);
    Serial.print(",");
    // EV2
    Serial.print(Global_car_state);
    Serial.print(",");
    Serial.print(Global_battfault);
    Serial.print(",");
    Serial.print(Global_isofault);
    Serial.print(",");
    Serial.print(Global_throttle1);
    Serial.print(",");
    Serial.print(Global_throttle2);
    Serial.print(",");
    Serial.print(Global_avethrottle);
    Serial.print(",");
    Serial.print(Global_brake);
    Serial.print(",");
    Serial.print(Global_LVBATT_V);
    Serial.print(",");
    Serial.print(Global_HV_V);
    Serial.print(",");
    Serial.print(Global_error);
    Serial.print(",");
    Serial.print(Global_tsa);
    Serial.print(",");
    Serial.print(Global_relay);
    Serial.print(",");
    Serial.print(Global_high_current);
    Serial.print(",");
    Serial.print(Global_insulation_pwm);
    Serial.print(",");
    Serial.print(Global_start_button);
    
    Serial.print("#");
}

void updateDB4(void) {
    String output ="@";
    // Motor Controller
    output += Global_MC_speed;
    output += ",";
    output += Global_MC_kph;
    output += ",";
    output += Global_MC_torque;
    output += ",";
    output += Global_Air_temp;
    output += ",";
    output += Global_MC_temp;
    output += ",";
    output += Global_MC_motortemp;
    output += ",";
    output += Global_MC_voltage;
    output += ",";
    output += Global_MC_current;
    output += ",";
    output += Global_MC_voltage*Global_MC_current;
    output += ",";
    output += Global_MC_corestatus;
    output += ",";
    output += Global_MC_error;
    output += ",";
    output += mc_message_count;
    output += ",";
    output += Global_rfe;
    output += ",";
    output += Global_frg;
    output += ",";
    output += Global_MC_go;
    output += ",";
    // BMS
    output += Global_BMS_voltage;
    output += ",";
    output += Global_BMS_minvoltage;
    output += ",";
    output += Global_BMS_maxvoltage;
    output += ",";
    output += Global_BMS_current;
    output += ",";
    output += Global_BMS_soc;
    output += ",";
    output += Global_BMS_temp;
    output += ",";
    output += Global_BMS_mintemp;
    output += ",";
    output += Global_BMS_maxtemp;
    output += ",";
    output += Global_BMS_status;
    output += ",";
    output += Global_BMS_state;
    output += ",";
    output += Global_BMS_capacity;
    output += ",";
    // EV2
    output += Global_car_state;
    output += ",";
    output += Global_battfault;
    output += ",";
    output += Global_isofault;
    output += ",";
    output += Global_throttle1;
    output += ",";
    output += Global_throttle2;
    output += ",";
    output += Global_avethrottle;
    output += ",";
    output += Global_brake;
    output += ",";
    output += Global_LVBATT_V;
    output += ",";
    output += Global_HV_V;
    output += ",";
    output += Global_error;
    output += ",";
    output += Global_tsa;
    output += ",";
    output += Global_relay;
    output += ",";
    output += Global_high_current;
    output += ",";
    output += Global_insulation_pwm;
    output += ",";
    output += Global_start_button;
    
    output += "#";
    Serial.print(output);
}

void updateDB_Processing(void) {
    Serial.print(Global_MC_speed);
    Serial.print(",");
    Serial.print(Global_MC_torque);
    Serial.print(",");
    Serial.print(Global_MC_motortemp);
    Serial.print(",");
    Serial.print(Global_MC_temp);
    Serial.print(",");
    Serial.print(Global_MC_voltage);
    Serial.print(",");
    Serial.print(Global_MC_current);
    Serial.print(",");
    Serial.print(Global_rfe);
    Serial.print(",");
    Serial.print(Global_frg);
    Serial.print(",");
    
    Serial.print(Global_BMS_voltage);
    Serial.print(",");
    Serial.print(Global_BMS_temp);
    Serial.print(",");
    Serial.print(Global_BMS_mintemp);
    Serial.print(",");
    Serial.print(Global_BMS_maxtemp);
    Serial.print(",");
    Serial.print(Global_BMS_status);
    Serial.print(",");
    
    Serial.print(Global_battfault);
    Serial.print(",");
    Serial.print(Global_isofault);
    Serial.print(",");
    Serial.print(Global_avethrottle);
    Serial.print(",");
    Serial.print(Global_brake);
    Serial.print(",");
    Serial.print(Global_LVBATT_V);
    Serial.print(",");
    Serial.print(Global_HV_V);
    Serial.print(",");
    Serial.print(Global_tsa);
    Serial.print(",");
    Serial.print(Global_relay);
    Serial.print(",");
    
    Serial.print(Global_car_state);

    Serial.print("\n");
}

/****************************************************************/
// Registers to store raw pedal readings during interrupt
volatile int pedal1_raw = -1;
volatile int pedal2_raw = -1;
volatile int brake_raw = -1;

void inputChanged(void) {
    Global_battfault = (int)digitalRead(43);
    Global_isofault = (int)digitalRead(49);
    Global_start_button = (int)digitalRead(41);

    if (Global_tsa == 1 && (int)digitalRead(45) == 0) {
        Global_error = 5;
        emergency_stop();
    }

    Global_tsa = (int)digitalRead(45);

    // if tsa not enabled when car in drive state, fault
    if(Global_relay == 1){  
        if (Global_tsa == 0 && (Global_car_state == DRIVE)) {
            Global_error = 2;
            emergency_stop();
        }   
    }
    // switch turns off drive but not state
    if(Global_car_state == DRIVE) {
        if (Global_start_button == 0) {
            Global_car_state == IDLE;
            enable_drive(false);
            Timer3.stop();
            Timer3.attachInterrupt(idleStateChecks).setFrequency(1).start();
        }
    }
    else if(Global_car_state == IDLE) {
        if (Global_start_button == 1) {
            set_tracsys_relay(true);
        }
    }
}

void idleStateChecks() {
    Global_car_state = IDLE;
    
    // MC Torque set to 0
    CAN_FRAME outgoing;
    createTorqueWriteFrame(outgoing,0);
    CAN.sendFrame(outgoing);

    // Update Throttle and Brake Values
    get_average_pedal_reading_value();
    get_average_brake_reading_value();

    // if start button on and tsa on, drive state
    if (Global_start_button ==  HIGH && Global_tsa == 1)
    {
        // enable drive

        Global_car_state = DRIVE;
        enable_drive(true);

        Timer3.stop();
        Timer3.attachInterrupt(sendThrottle).setFrequency(100).start();
        Timer6.attachInterrupt(checkBrakeThrottle).setFrequency(500).start();
    }
}

void checkBrakeThrottle() {
    get_average_brake_reading_value();
    get_average_pedal_reading_value();
    // if (Global_brake > MAX_BRAKE && Global_avethrottle > 30000) {
    //     emergency_stop();
    // }
}

bool CAN_setup() {
	if (CAN.init(CAN_BAUD_RATE) && CAN2.init(CAN_BAUD_RATE)) {}
    else
		return false;

    //By default there are 7 mailboxes for each device that are RX boxes
    //This sets each mailbox to have an open filter that will accept extended
    //or standard frames
    int filter;
    for (int filter = 0; filter < 7; filter++) {
        CAN.setRXFilter(filter, 0, 0, false);
        CAN2.setRXFilter(filter, 0, 0, false);
    }      

    return true;
}

void printFrame(CAN_FRAME &frame) {
    Serial.print("ID: 0x");
    Serial.print(frame.id, HEX);
    Serial.print(" Len: ");
    Serial.print(frame.length);
    Serial.print(" Data: 0x");
    for (int count = 0; count < frame.length; count++) {
        Serial.print(frame.data.bytes[count], HEX);
        Serial.print(" ");
    }
    Serial.print("\r\n");
}

void createFrame(CAN_FRAME &frame, int RXID, int length, int REGID, int DATA_1, int DATA_2) {
    frame.id = RXID;
    frame.length = length;
    frame.extended = 0;

    frame.data.bytes[0] = REGID;
    frame.data.bytes[1] = DATA_1;
    frame.data.bytes[2] = DATA_2;

    // frame.data.low = (REGID, data1 and data2 combined)
}

bool parseFrame(CAN_FRAME &frame) {
    if (frame.id == NDRIVE_TXID) {
        mc_message_count++;
        switch(frame.data.bytes[0]) {
            // MC Related
            case SPEED_READ_ADD: {
                int16_t speed = (frame.data.bytes[2] << 8) | frame.data.bytes[1];
                Global_MC_speed = 2000 * speed/MAX_SPEED_READ;
                Global_MC_kph = Global_MC_speed * 0.032;
                break;
            }
            case TORQUE_WRITE_ADD: {
                unsigned int torque = (frame.data.bytes[2] << 8) | frame.data.bytes[1];
                torque = torque * 100 / MAX_TORQUE_WRITE;
                Global_MC_torque = torque;
                break;
            }
            case MC_CURRENT_READ: {
                int16_t current = (frame.data.bytes[2] << 8) | frame.data.bytes[1];
                Global_MC_current = current/3.925;
                if (current > MAX_MC_CURRENT) {
                    // emergency_stop();
                    // return false;
                }
                break;
            }
            case MC_VOLTAGE_READ: {
                int16_t voltage = (frame.data.bytes[2] << 8) | frame.data.bytes[1];
                Global_MC_voltage = voltage/54.54;
                if (voltage > MAX_MC_VOLTAGE) {
                    // emergency_stop();
                    // return false;
                }
                break;
            }
            case CORE_STATUS: {
                int status = (frame.data.bytes[2] << 8) | frame.data.bytes[1];
                if (status == KERN_STATUS) {
                    // DRIVE ENABLED, POSITION CONTROL ENABLED, SPEED CONTROL IS ENABLED
                    // Serial.println("NDRIVE CORE_STATUS = KERN_STATUS");
                } 
                break;
            }
            case MC_TEMP: {
                float temp = (frame.data.bytes[2] << 8) | frame.data.bytes[1];
                Global_MC_temp = log(temp/15536)/0.0053;
                break;
            }
            case MC_MOTORTEMP: {
                float temp = (frame.data.bytes[2] << 8) | frame.data.bytes[1];
                Global_MC_motortemp = (temp - 10110)/51.7;
                break;
            }
        }
    }
    // BMS Related
    else {
    	switch (frame.id) {
    		case BMS_STATUS: {
                if (frame.data.bytes[0] != 0) {
                    // Serial.println("BMS Error : State of System = 1");
                    Global_BMS_status = frame.data.bytes[0];
                    // emergency_stop();
                    return false;
                }
                else {
                    Global_BMS_status = frame.data.bytes[0];
                }
    			break;
            }
            case PACK_VOLTAGE: {
                int voltage = (frame.data.bytes[0] << 8) | frame.data.bytes[1];
                Global_BMS_voltage = voltage;
                int minVoltage = (frame.data.bytes[2]);
                Global_BMS_minvoltage = minVoltage;
                int maxVoltage = (frame.data.bytes[4]);
                Global_BMS_maxvoltage = maxVoltage;

                // if (minVoltage < x) {
                //     Global_error = 4;
                //     emergency_stop();
                // }

                break;
            }

            case PACK_CURRENT: {
                int current = (frame.data.bytes[0] << 8) | frame.data.bytes[1];
                Global_BMS_current = current;
                
                break;
            }
            case PACK_SOC: {
                Global_BMS_soc = frame.data.bytes[0];
                break;
            }
            case PACK_TEMP: {
                Global_BMS_temp = frame.data.bytes[0];
                Global_BMS_mintemp = frame.data.bytes[2];
                Global_BMS_maxtemp = frame.data.bytes[4];

                if (Global_BMS_maxtemp > MAX_TEMP) {
                    // emergency_stop();
                    return false;
                }

                break;
            }
    	}
    }
    return true;
}

void createMCTempRequestFrame(CAN_FRAME &frame) {
    frame.id = NDRIVE_RXID;
    frame.length = 3;
    frame.data.bytes[0] = DS_SERVO;
    frame.data.bytes[1] = MC_TEMP;
    frame.data.bytes[2] = 0;
}

void createMotorTempRequestFrame(CAN_FRAME &frame) {
    frame.id = NDRIVE_RXID;
    frame.length = 3;
    frame.data.bytes[0] = DS_SERVO;
    frame.data.bytes[1] = MC_MOTORTEMP;
    frame.data.bytes[2] = 0;
}

void createSpeedRequestFrame(CAN_FRAME &frame, int repetition) {
    if (repetition >= 0) {
        frame.id = NDRIVE_RXID;
        frame.length = 3;
        frame.data.bytes[0] = DS_SERVO;
        frame.data.bytes[1] = SPEED_READ_ADD;
        frame.data.bytes[2] = repetition;
    }
}

void createTorqueRequestFrame(CAN_FRAME &frame, int repetition) {
    if (repetition >= 0) {
        frame.id = NDRIVE_RXID;
        frame.length = 3;
        frame.data.bytes[0] = DS_SERVO;
        frame.data.bytes[1] = TORQUE_WRITE_ADD;
        frame.data.bytes[2] = repetition;
    }
}

void createCurrentRequestFrame(CAN_FRAME &frame, int repetition) {
    if (repetition >= 0) {
        frame.id = NDRIVE_RXID;
        frame.length = 3;
        frame.data.bytes[0] = DS_SERVO;
        frame.data.bytes[1] = MC_CURRENT_READ;
        frame.data.bytes[2] = repetition;
    }
}

void createVoltageRequestFrame(CAN_FRAME &frame, int repetition) {
    if (repetition >= 0) {
        frame.id = NDRIVE_RXID;
        frame.length = 3;
        frame.data.bytes[0] = DS_SERVO;
        frame.data.bytes[1] = MC_VOLTAGE_READ;
        frame.data.bytes[2] = repetition;
    }
}

void createCoreStatusRequestFrame(CAN_FRAME &frame) {
    frame.id = NDRIVE_RXID;
    frame.length = 3;
    frame.data.bytes[0] = DS_SERVO;
    frame.data.bytes[1] = CORE_STATUS;
    frame.data.bytes[2] = 0x00;
}

void createSpeedWriteFrame(CAN_FRAME &frame, float speed) {
    speed = speed * MAX_SPEED_WRITE;
    frame.id = NDRIVE_RXID;
    frame.length = 3;
    frame.data.bytes[0] = SPEED_WRITE_ADD;
    frame.data.bytes[1] = (int)speed;
    frame.data.bytes[2] = (int)speed >> 8;
    // Serial.println(speed, HEX);
}

void createTorqueWriteFrame(CAN_FRAME &frame, float torque) {
    torque = torque * MAX_TORQUE_WRITE; 
    frame.id = NDRIVE_RXID;
    frame.length = 3;
    frame.data.bytes[0] = TORQUE_WRITE_ADD;
    frame.data.bytes[1] = (int)torque;
    frame.data.bytes[2] = (int)torque >> 8;
    // Serial.println(torque, HEX);
}

void abort_requests(int REGID) {
    CAN_FRAME frame_abort;
    createFrame(frame_abort, NDRIVE_RXID, 3, DS_SERVO, REGID, 0xFF);
    CAN.sendFrame(frame_abort);
    delayMicroseconds(100);
}

void abort_all_requests() {
    abort_requests(SPEED_READ_ADD);
}

void adc_setup(void) {
    adc_init(ADC, SystemCoreClock, ADC_FREQ_MAX, 8);
    adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1);
    adc_set_resolution(ADC, ADC_12_BITS);

    // Enable ADC channels arrange by arduino pins from A0 to A9
    // adc_enable_channel(ADC, ADC_CHANNEL_7); // A0
    // adc_enable_channel(ADC, ADC_CHANNEL_6); // A1
    // adc_enable_channel(ADC, ADC_CHANNEL_5); // A2
    // adc_enable_channel(ADC, ADC_CHANNEL_4); // A3
    // adc_enable_channel(ADC, ADC_CHANNEL_3); // A4
    // adc_enable_channel(ADC, ADC_CHANNEL_2); // A5
    // adc_enable_channel(ADC, ADC_CHANNEL_1); // A6
    // adc_enable_channel(ADC, ADC_CHANNEL_0); // A7
    // adc_enable_channel(ADC, ADC_CHANNEL_10); // A8
    // adc_enable_channel(ADC, ADC_CHANNEL_11); // A9

    // Enable ADC channels for pedals
    adc_enable_channel(ADC, PEDAL1_ADC_CHANNEL);
    adc_enable_channel(ADC, PEDAL2_ADC_CHANNEL);
    adc_enable_channel(ADC, BRAKE_PEDAL_CHANNEL);

    // Enable ADC channels for LV and HV measuring
    adc_enable_channel(ADC, LV_BATTERY_V);
    adc_enable_channel(ADC, HV_V);

    // Enable ADC interrupt
    adc_enable_interrupt(ADC, ADC_IER_EOC7); //EOC9 so that interrupt triggered when analogue input channerl 9 has reached end of conversion
    
    // Trigger configuration
    adc_configure_trigger(ADC, ADC_TRIG_SW, 0);
    
    // Enable ADC interrupt
    NVIC_EnableIRQ(ADC_IRQn);
    
    //start ADC conversion, note that ADC conversion has to be restarted once conversion is finished
    adc_start(ADC);
}

void ADC_Handler(void) {
    // Check the ADC conversion status
    if ((adc_get_status(ADC) & ADC_ISR_EOC7) == ADC_ISR_EOC7)
    {
        // // Get digital data value from ADC channels and can be used by application
        // CHANNEL_0_REG = adc_get_channel_value(ADC, ADC_CHANNEL_0);
        // CHANNEL_1_REG = adc_get_channel_value(ADC, ADC_CHANNEL_1);
        // CHANNEL_2_REG = adc_get_channel_value(ADC, ADC_CHANNEL_2);
        // CHANNEL_3_REG = adc_get_channel_value(ADC, ADC_CHANNEL_3);
        // CHANNEL_4_REG = adc_get_channel_value(ADC, ADC_CHANNEL_4);
        // CHANNEL_5_REG = adc_get_channel_value(ADC, ADC_CHANNEL_5);
        // CHANNEL_6_REG = adc_get_channel_value(ADC, ADC_CHANNEL_6);
        // CHANNEL_7_REG = adc_get_channel_value(ADC, ADC_CHANNEL_7);
        // CHANNEL_8_REG = adc_get_channel_value(ADC, ADC_CHANNEL_10); //notice that its channel 10
        // CHANNEL_9_REG = adc_get_channel_value(ADC, ADC_CHANNEL_11); //notice that its channel 11

        pedal1_raw = adc_get_channel_value(ADC, PEDAL1_ADC_CHANNEL);
        pedal2_raw = adc_get_channel_value(ADC, PEDAL2_ADC_CHANNEL);
        brake_raw = adc_get_channel_value(ADC, BRAKE_PEDAL_CHANNEL);

        Global_LVBATT_V = adc_get_channel_value(ADC, LV_BATTERY_V)/233.3;;
        Global_HV_V = adc_get_channel_value(ADC, HV_V);
    }
    adc_start(ADC);
}

void checkForFaults(void) {
    if(Global_LVBATT_V != -1 && Global_LVBATT_V < 12) {
        Global_error = 3;
        emergency_stop();
    }


}

/**
 * Emergency functions
 * -------------------
 */

/**
 * Stops the vehicle completely
 */
void emergency_stop() {
    // 1. stop sending throttle values
    Timer3.stop();

    // 2. send 0 throttle to MC
    CAN_FRAME outgoing;
    createTorqueWriteFrame(outgoing,0);
    CAN.sendFrame(outgoing);

    // 3. Disable Drive (RFE, FRG, TSA RELAY)
    enable_drive(false);
    Timer3.attachInterrupt(checkBrakeThrottle).setFrequency(100).start();

    Global_car_state = FAULT;
}

/**
 * Emergency stop the vehicle if condition is invalid.
 * @param condition
 */
void assert_or_abort(bool condition) {
    if ( ! condition) {
        emergency_stop();
    }
}

/**
 * Pedal reading functions
 * -----------------------
 */

/**
 * Processes pedal reading. Maps value to 16-bit range.
 * @param  raw_value Raw value
 * @param  min_value Minimum value
 * @param  max_value Maximum value
 * @return value     Processed value
 */
int get_pedal_reading(const int raw_value, const int min_value, const int max_value) {
    // Map to 16-bit range
    return constrain(map(raw_value, min_value, max_value, 0, 65536), 0, 65536);
}

/**
 * Returns average of two readings
 * @param  reading_1
 * @param  reading_2
 * @return
 */
int get_average_pedal_reading(const int reading_1, const int reading_2) {
    return (reading_1 + reading_2) / 2;
}

/**
 * Calibrated values
 */
const int pedal1_min = 850;  // pedal1 min value in 12-bit range
const int pedal1_max = 1650; // pedal1 max value in 12-bit range
const int pedal2_min = 1000;  // pedal2 min value in 12-bit range
const int pedal2_max = 1700; // pedal2 max value in 12-bit range
const int brake_min = 0;
const int brake_max = 1200;

int get_average_pedal_reading_value() {
    // Serial.print("PEDAL_1 RAW = ");
    // Serial.print(pedal1_raw);
    // Serial.print("      PEDAL_2 RAW = ");
    // Serial.println(pedal2_raw);
    int reading_1 = get_pedal_reading(pedal1_raw, pedal1_min, pedal1_max);
    int reading_2 = get_pedal_reading(pedal2_raw, pedal2_min, pedal2_max);
    // Serial.print("READING_1 = ");
    // Serial.print(reading_1);
    // Serial.print("      READING_2 = ");
    // Serial.println(reading_2);
    Global_throttle1 = pedal1_raw;
    Global_throttle2 = pedal2_raw;
    // Global_avethrottle = get_average_pedal_reading(reading_1,reading_2);
    Global_avethrottle = get_average_pedal_reading(reading_1,reading_2);
    if (Global_throttle1 < 400) {
        Global_error = 1;
        emergency_stop();
    }
    return Global_avethrottle;
}

int get_average_brake_reading_value() {
    Global_brake = get_pedal_reading(brake_raw, brake_min, brake_max);
    return Global_brake;
}

/**
 * Asserts pedal readings are in threshold
 * @param  reading_1
 * @param  reading_2
 * @param  threshold
 */
void assert_pedal_in_threshold(const int reading_1, const int reading_2, const int threshold) {
    int difference = abs(reading_1 - reading_2);
    bool condition = difference < threshold;

    #ifdef SerialDebug
    if ( ! condition) {
        SerialDebug.println("Pedal reading discrepancy detected!");
        SerialDebug.print("Reading (1): ");
        SerialDebug.println(reading_1);
        SerialDebug.print("Reading (2): ");
        SerialDebug.println(reading_2);
        SerialDebug.print("Threshold: ");
        SerialDebug.println(threshold);
        SerialDebug.print("Difference: ");
        SerialDebug.println(difference);
    }
    #endif

    assert_or_abort(condition);
}

void sendThrottle(void) {
    float torque = get_average_pedal_reading_value();
    torque /= MAX_THROTTLE;
    // torque *= 0.3;
    CAN_FRAME outgoing;
    createTorqueWriteFrame(outgoing,torque);
    CAN.sendFrame(outgoing);
}
