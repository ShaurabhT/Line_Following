int SENSOR[6]= {0, 28, 27, 26, 25, 24}; //6 sensors

#define CLP 22
#define NEAR 23

#define IN2 50//motors
#define IN1 51
#define IN4 52
#define IN3 53

#define ENA 44
#define ENB 45

int IN_TRACK = false;
int OUT_OF_TRACK = true;


int S1=0, S2=0, S3=0, S4=0, S5=0, clp = 0, near=0;
int state=0, dly=0;

/*For PID*/
const float kp=1, kd=2, ki=32;
int pid,prev_error,  integral =0;


int carStop();
int straight();
int turnLeft();
int turnRight();
int rotateLeft();
int rotateRight();
int PID_calc();
void speedControl(int);
void topSpeed();


void setup() {

  pinMode(SENSOR[1], INPUT);
  pinMode(SENSOR[2], INPUT);
  pinMode(SENSOR[3], INPUT);
  pinMode(SENSOR[4], INPUT);
  pinMode(SENSOR[5], INPUT);
  pinMode(CLP, INPUT);
  pinMode(NEAR, INPUT);
  
  pinMode(IN2, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN3, OUTPUT);
  
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);


  analogWrite(ENA, 50);
  analogWrite(ENB, 50);
  Serial.begin(9600);
  
}

void loop() {
  S1 = digitalRead(SENSOR[1]);
  S2 = digitalRead(SENSOR[2]);
  S3 = digitalRead(SENSOR[3]);
  S4 = digitalRead(SENSOR[4]);
  S5 = digitalRead(SENSOR[5]);
  near = digitalRead(NEAR);
  Serial.println("S1 : "+String(S1) +", "+"S2 : "+String(S2) +", "+"S3 : "+String(S3) +", "+"S4 : "+String(S4) +", "+"S5 : "+String(S5) +", ""NEAR : "+String(near) +", ");
  if(near == true && 1==2){
    carStop();
    Serial.println("NEAR");    
  }else if( S1 == OUT_OF_TRACK && S2 == OUT_OF_TRACK && S3 == OUT_OF_TRACK && S4 == OUT_OF_TRACK && S5 == OUT_OF_TRACK){
    Serial.println("OT");  
    state = carStop();
    /*
        topSpeed();
        switch(state){
          case 1:
            turnLeft();
            break;
          case 2:
            turnRight();
            break;
          case 3:
            turnLeft();
            break;
          case 4:
            turnRight();
            break;
          case 10:
            straight();
            break;
            
          default :
            state = carStop();          
        }
        dly++;
        if(dly >= 100){
          state = 0;
          Serial.println("TRACK LOST STOP");
        }
        */
  }/*else if(S3 == OUT_OF_TRACK){
    dly = 0;
    
    
  }*/else{
    dly =0;
    
    pid = PID_calc();
    speedControl(pid);
    if(pid == 0){
      topSpeed();
    }
    if(S5 == IN_TRACK && pid == -120){
      topSpeed();
      state = rotateRight();
      Serial.println("S5");
    }else if(S4 == IN_TRACK && pid == -120){
      topSpeed();
      state = turnRight();
      Serial.println("S4");
    }else if(S1 == IN_TRACK && pid == 120){
      topSpeed();
      state = rotateLeft();
      Serial.println("S1");
    }else if(S2 == IN_TRACK && pid == 120){
      topSpeed();
      state = turnLeft();
      Serial.println("S2");
    }else{
      Serial.println(state);
    state = straight();
    }
  }
  delay(10);
}

int carStop(){
  digitalWrite(IN2, LOW);
  digitalWrite(IN1, LOW);
  
  digitalWrite(IN4, LOW);
  digitalWrite(IN3, LOW);
  return 0;
}
int straight(){
        digitalWrite(IN2, HIGH);
        digitalWrite(IN1, LOW);
        
        digitalWrite(IN4, HIGH);
        digitalWrite(IN3, LOW);
  return 10;
}
int turnLeft(){  
        digitalWrite(IN2, HIGH);
        digitalWrite(IN1, LOW);
        
        digitalWrite(IN4, LOW);
        digitalWrite(IN3, LOW);
        return 1;
}
int turnRight(){  
        digitalWrite(IN2, LOW);
        digitalWrite(IN1, LOW);
        
        digitalWrite(IN4, HIGH);
        digitalWrite(IN3, LOW);
        return 2;
}
int rotateLeft(){
        digitalWrite(IN2, HIGH);
        digitalWrite(IN1, LOW);
        
        digitalWrite(IN4, LOW);
        digitalWrite(IN3, HIGH);
        return 3;
}
int rotateRight(){  
        digitalWrite(IN2, LOW);
        digitalWrite(IN1, HIGH);
        
        digitalWrite(IN4, HIGH);
        digitalWrite(IN3, LOW);
        return 4;
}
int PID_calc(){
  int error;
  int ret;
  if( S1 == IN_TRACK && S2 == OUT_OF_TRACK && S3 == OUT_OF_TRACK && S4 == OUT_OF_TRACK && S5 == OUT_OF_TRACK){
    error =4;
  }else if( S1 == IN_TRACK && S2 == IN_TRACK && S3 == OUT_OF_TRACK && S4 == OUT_OF_TRACK && S5 == OUT_OF_TRACK){
    error = 3;
  }else if( S1 == OUT_OF_TRACK && S2 == IN_TRACK && S3 == OUT_OF_TRACK && S4 == OUT_OF_TRACK && S5 == OUT_OF_TRACK){
    error =2;
  }else if( S1 == OUT_OF_TRACK && S2 == IN_TRACK && S3 == IN_TRACK && S4 == OUT_OF_TRACK && S5 == OUT_OF_TRACK){
    error = 1;
  }else if( S1 == OUT_OF_TRACK && S2 == OUT_OF_TRACK && S3 == IN_TRACK && S4 == OUT_OF_TRACK && S5 == OUT_OF_TRACK){
    error=0;
    integral=0;
  }else if( S1 == OUT_OF_TRACK && S2 == OUT_OF_TRACK && S3 == IN_TRACK && S4 == IN_TRACK && S5 == OUT_OF_TRACK){
    error=-1;
  }else if( S1 == OUT_OF_TRACK && S2 == OUT_OF_TRACK && S3 == OUT_OF_TRACK && S4 == IN_TRACK && S5 == OUT_OF_TRACK){
    error = -2;
  }else if( S1 == OUT_OF_TRACK && S2 == OUT_OF_TRACK && S3 == OUT_OF_TRACK && S4 == IN_TRACK && S5 == IN_TRACK){
    error = -3;
  }else if( S1 == OUT_OF_TRACK && S2 == OUT_OF_TRACK && S3 == OUT_OF_TRACK && S4 == OUT_OF_TRACK && S5 == IN_TRACK){
    error = -4;
  }else{
    error = prev_error;
  }
  integral = integral + error;
  ret = kp*error + kd*(error-prev_error) + ki*integral;
 Serial.println(String(kp*error)+", " +String(kd*(error-prev_error))+", " +String(ki*integral)+" = " +String(ret)+", " );
  prev_error = error;  
  if(ret > 50){
    return 50;
  }else if(ret < -50){
    return -50;
  }
  return ret;
}
void speedControl(int diff){
  analogWrite(ENA, 50+diff);
  analogWrite(ENB, 50-diff);
}
void topSpeed(){
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
}
