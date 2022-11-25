//Motor inputs/outputs
#define MOTOR_EN_1_2 10
#define MOTOR_IN1 9
#define MOTOR_IN2 8

//The max speed of the ACM
#define MAX_SPEED 255

//Speed of the ACM
#define SLOW 64
#define NORMAL 128
#define FAST 255

//Diretion of the ACM
#define FORWARD 0
#define BACKWARD 1

/**
 * Will move the ACM forwards with a continuous speed
 * @param speed The speed at which the ACM will move forwards. This can be from 1 to 255. Or SLOW/NORMAL/FAST
*/
void moveForwardContinuous(int speed) {
    checkSpeedLimit(speed);
    analogWrite(MOTOR_EN_1_2, speed);
    digitalWrite(MOTOR_IN1, HIGH);
    digitalWrite(MOTOR_IN2, LOW);
}

/**
 * Will move the ACM backwards with a continuous speed
 * @param speed The speed at which the ACM will move backwards. This can be from 1 to 255. Or SLOW/NORMAL/FAST
*/
void moveBackwardContinuous(int speed) {
    checkSpeedLimit(speed);
    analogWrite(MOTOR_EN_1_2, speed);
    digitalWrite(MOTOR_IN1, LOW);
    digitalWrite(MOTOR_IN2, HIGH);
}

/**
 * Will move the ACM forward or backward with increasing speed
 * @param direction The direction the ACM will move. This can be FORWARD or BACKWARD
 * @param speed The speed the ACM will try to achieve
*/
void moveWithIncreasingSpeed(int direction, int speed) {
    checkSpeedLimit(speed);

    switch (direction)
    {
        //Forward
    case 0:
        digitalWrite(MOTOR_IN1, HIGH);
        digitalWrite(MOTOR_IN2, LOW);
        break;
        //Backward
    case 1:
        digitalWrite(MOTOR_IN1, LOW);
        digitalWrite(MOTOR_IN2, HIGH);
        break;
    default:
        brake();
        break;
    }

    for(int i = 0; i < speed; i++) {
        analogWrite(MOTOR_EN_1_2, i);
        delay(10);
    }
}

/**
 * Compares the speed to the MAX_SPEED. If speeds is greater then MAX_SPEED, speed will be MAX_SPEED
 * @param speed The speed that will be compared to the max speed
 * @return The speed
 * */ 
int checkSpeedLimit(int speed) {
    if(speed > MAX_SPEED) {
        return speed = MAX_SPEED;
    }
    return speed;
}

/**
 * Turns to engines to HIGH which makes the ACM brake
*/
void brake() {
    digitalWrite(MOTOR_IN1, HIGH);
    digitalWrite(MOTOR_IN2, HIGH);
}

void setup() {
    Serial.begin(9600);
    Serial.println("Testing the L293D");

    pinMode(MOTOR_EN_1_2, OUTPUT);
    pinMode(MOTOR_IN1, OUTPUT);
    pinMode(MOTOR_IN2, OUTPUT);
}

void loop() {
    moveWithIncreasingSpeed(FORWARD, NORMAL);
}