int g1=11, y1=12, r1=13;
int g2=8,  y2=9,  r2=10;

int t = 1000;
int T = 3000;

void setup() {
  pinMode(g1 , OUTPUT);
  pinMode(y1 , OUTPUT);
  pinMode(r1 , OUTPUT);
  pinMode(g2 , OUTPUT);
  pinMode(y2 , OUTPUT);
  pinMode(r2 , OUTPUT);

  digitalWrite(g1 , LOW);
  digitalWrite(y1 , LOW);
  digitalWrite(r1 , LOW);
  digitalWrite(g2 , LOW);
  digitalWrite(y2 , LOW);
  digitalWrite(r2 , LOW);
}

void loop() {

  digitalWrite(g1 , HIGH);
  digitalWrite(r2 , HIGH);

  delay(T);

  digitalWrite(g1 , LOW);
  digitalWrite(y1 , HIGH);

  delay(t);
  
  digitalWrite(r1, HIGH);
  digitalWrite(y1, LOW);

  digitalWrite(r2 , LOW);
  digitalWrite(g2 , HIGH);


  delay(T);
  
  digitalWrite(g2 , LOW);
  digitalWrite(y2 , HIGH);

  delay(t);
  
  digitalWrite(r1 , LOW);
  digitalWrite(y2 , LOW);


}
