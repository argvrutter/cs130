void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  String what_to_print = "Print this once every 1000 ms\n";
  Serial.print(what_to_print);
  delay(1000);
}
