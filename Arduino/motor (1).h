#define DIR1A 6
#define DIR1B 5
#define PWM1 4

#define DIR3A 9
#define DIR3B 8
#define PWM3 7

#define DIR2A 11
#define DIR2B 12
#define PWM2 13


void berhenti()
{
  digitalWrite(DIR2A, LOW);
  digitalWrite(DIR2B, LOW);
  analogWrite(PWM1, 0);
  
  digitalWrite(DIR1A, LOW);
  digitalWrite(DIR1B, LOW);
  analogWrite(PWM2, 0);

  digitalWrite(DIR3A, LOW);
  digitalWrite(DIR3B, LOW);
  analogWrite(PWM3, 0); 
}

void rotasiKanan(byte a)
{
  digitalWrite(DIR2A, LOW);
  digitalWrite(DIR2B, HIGH);
  analogWrite(PWM1, a);
  
  digitalWrite(DIR1A, LOW);
  digitalWrite(DIR1B, HIGH);
  analogWrite(PWM2, a);

  digitalWrite(DIR3A, LOW);
  digitalWrite(DIR3B, HIGH);
  analogWrite(PWM3, a); 
}


void rotasiKiri(byte a)
{
  digitalWrite(DIR2A, HIGH);
  digitalWrite(DIR2B, LOW);
  analogWrite(PWM1, a);
  
  digitalWrite(DIR1A, HIGH);
  digitalWrite(DIR1B, LOW);
  analogWrite(PWM2, a);

  digitalWrite(DIR3A, HIGH);
  digitalWrite(DIR3B, LOW);
  analogWrite(PWM3, a); 
}

void motorInit()
{
  pinMode(DIR1A, OUTPUT);
  pinMode(DIR1B, OUTPUT);
  pinMode(PWM1, OUTPUT);
  
  pinMode(DIR2A, OUTPUT);
  pinMode(DIR2B, OUTPUT);
  pinMode(PWM2, OUTPUT);

  pinMode(DIR3A, OUTPUT);
  pinMode(DIR3B, OUTPUT);
  pinMode(PWM3, OUTPUT);
}

void maju(byte kecepatan)
{
  digitalWrite(DIR1A, LOW);
  digitalWrite(DIR1B, HIGH);
  analogWrite(PWM1, kecepatan);
  
  digitalWrite(DIR2A, HIGH);
  digitalWrite(DIR2B, LOW);
  analogWrite(PWM2, kecepatan);

  
  digitalWrite(DIR3A, LOW);
  digitalWrite(DIR3B, LOW);
  analogWrite(PWM3, kecepatan);
}


void mundur(byte a)
{
  digitalWrite(DIR1A, HIGH);
  digitalWrite(DIR1B, LOW);
  analogWrite(PWM1, a);
  
  digitalWrite(DIR2A, LOW);
  digitalWrite(DIR2B, HIGH);
  analogWrite(PWM2, a);

  
  digitalWrite(DIR3A, LOW);
  digitalWrite(DIR3B, LOW);
  analogWrite(PWM3, a);
}

void kanan(byte kecepatan)
{
  digitalWrite(DIR1A, LOW);
  digitalWrite(DIR1B, HIGH);
  analogWrite(PWM1, kecepatan/1.4);
  
  digitalWrite(DIR2A, LOW);
  digitalWrite(DIR2B, HIGH);
  analogWrite(PWM2, (kecepatan*7)/10);

  digitalWrite(DIR3A, HIGH);
  digitalWrite(DIR3B, LOW);
  analogWrite(PWM3, kecepatan);
}

void kiri(byte kecepatan)
{
  digitalWrite(DIR1A, HIGH);
  digitalWrite(DIR1B, LOW);
  analogWrite(PWM1, (kecepatan*7)/10);
  
  digitalWrite(DIR2A, HIGH);
  digitalWrite(DIR2B, LOW);
  analogWrite(PWM2, kecepatan/1.4);

  digitalWrite(DIR3A, LOW);
  digitalWrite(DIR3B, HIGH);
  analogWrite(PWM3, kecepatan);
}


void belokKiri(byte kecepatan)
{
  digitalWrite(DIR1A, LOW);
  digitalWrite(DIR1B, HIGH);
  analogWrite(PWM1, kecepatan);
  
  digitalWrite(DIR2A, HIGH);
  digitalWrite(DIR2B, HIGH);
  analogWrite(PWM2, 0);

  
  digitalWrite(DIR3A, LOW);
  digitalWrite(DIR3B, HIGH);
  analogWrite(PWM3, kecepatan);
}

void belokKanan(byte kecepatan)
{
  digitalWrite(DIR1A, HIGH);
  digitalWrite(DIR1B, HIGH);
  analogWrite(PWM1, 0);
  
  digitalWrite(DIR2A, HIGH);
  digitalWrite(DIR2B, LOW);
  analogWrite(PWM2, kecepatan);

  
  digitalWrite(DIR3A, HIGH);
  digitalWrite(DIR3B, LOW);
  analogWrite(PWM3, kecepatan);
}
