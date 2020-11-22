const inst EnableL=5;
const int HighL=6; Left Side Moter
const  int LowL=7;


const inst EnableR=10;
const int HighR=8; rigth Side Moter
const  int LowR=9;
void setup(){
    pinMode(EnableL,OUTPUT);
    pinMode(HighL,OUTPUT);
    pinMode(LowL,OUTPUT); out put [in]

 
    pinMode(EnableR,OUTPUT);
    pinMode(HighR,OUTPUT);
    pinMode(LowR,OUTPUT);

}


void Forward(){
    digitalWrite(HighL,LOW);
    digitalWrite(LowL,HIGH);
    analogWrite(EnableL,255);


    digitalWrite(HighR,LOW);
    digitalWrite(LowR,HIGH);
    analogWrite(EnableR,255);
    

}


void Backward(){
    digitalWrite(HighL,HIGH);
    digitalWrite(LowL,LOw);
    analogWrite(EnableL,255);


    digitalWrite(HighR,HIGH);
    digitalWrite(LowR,LOW);
    analogWrite(EnableR,255);
    

}
void Left1(){
    digitalWrite(HighL,LOW);
    digitalWrite(LowL,HIGH);
    analogWrite(EnableL,200);


    digitalWrite(HighR,LOW);
    digitalWrite(LowR,HIGH);
    analogWrite(EnableR,255);
    

}

void Left2(){
    digitalWrite(HighL,LOW);
    digitalWrite(LowL,HIGH);
    analogWrite(EnableL,160);


    digitalWrite(HighR,LOW);
    digitalWrite(LowR,HIGH);
    analogWrite(EnableR,255);
    

}

void Left3(){
    digitalWrite(HighL,LOW);
    digitalWrite(LowL,HIGH);
    analogWrite(EnableL,100);


    digitalWrite(HighR,LOW);
    digitalWrite(LowR,HIGH);
    analogWrite(EnableR,255);
    

}



void Right1(){
    digitalWrite(HighL,LOW);
    digitalWrite(LowL,HIGH);
    analogWrite(EnableL,255);


    digitalWrite(HighR,LOW);
    digitalWrite(LowR,HIGH);
    analogWrite(EnableR,200);
    

}
void Right2(){
    digitalWrite(HighL,LOW);
    digitalWrite(LowL,HIGH);
    analogWrite(EnableL,255);


    digitalWrite(HighR,LOW);
    digitalWrite(LowR,HIGH);
    analogWrite(EnableR,160);
    

}
void Right3(){
    digitalWrite(HighL,LOW);
    digitalWrite(LowL,HIGH);
    analogWrite(EnableL,255);


    digitalWrite(HighR,LOW);
    digitalWrite(LowR,HIGH);
    analogWrite(EnableR,100);
    

}

void loop(){
    Forward();
}
