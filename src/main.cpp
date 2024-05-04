#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>

PZEM004Tv30 pzem(6, 7); //fase r
PZEM004Tv30 pzem2(4, 5); //fase s
PZEM004Tv30 pzem3(2, 3); //fase t
SoftwareSerial fromesp32(8, 9);

void setup()
{
  Serial.begin(19200);
  fromesp32.begin(9600);
  Serial.println("..initialized");
}

void checkPzem(String status,float voltage, float current, float power, float energy, float frequency, float pf)
{
  String ini = "";
  ini += status + ",";
  if (voltage != NAN)
  {
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.println("V");
    ini += String(voltage) + ",";
  }
  else
  {
    Serial.println("Error reading voltage");
    ini += "err,";
  }
  if (current != NAN)
  {
    Serial.print("Current: ");
    Serial.print(current);
    Serial.println("A");
    ini += String(current) + ",";
  }
  else
  {
    Serial.println("Error reading current");
    ini += "err,";
  }
  if (power != NAN)
  {
    Serial.print("Power: ");
    Serial.print(power);
    Serial.println("W");
    ini += String(power) + ",";
  }
  else
  {
    Serial.println("Error reading power");
    ini += "err,";
  }
  if (energy != NAN)
  {
    Serial.print("Energy: ");
    Serial.print(energy, 3);
    Serial.println("kWh");
    ini += String(energy) + ",";
  }
  else
  {
    Serial.println("Error reading energy");
    ini += "err,";
  }
  if (frequency != NAN)
  {
    Serial.print("Frequency: ");
    Serial.print(frequency, 1);
    Serial.println("Hz");
    ini += String(frequency) + ",";
  }
  else
  {
    Serial.println("Error reading frequency");
    ini += "err,";
  }
  if (pf != NAN)
  {
    Serial.print("PF: ");
    Serial.println(pf);
    ini += String(pf);
  }
  else
  {
    Serial.println("Error reading power factor");
    ini += "err";
  }
  ini += "\n";
  fromesp32.print(ini);

  Serial.println();
  delay(2000);
}

void loop()
{
  checkPzem("Fase R",pzem.voltage(), pzem.current(), pzem.power(), pzem.energy(), pzem.frequency(), pzem.pf());
  checkPzem("Fase S",pzem2.voltage(), pzem2.current(), pzem2.power(), pzem2.energy(), pzem2.frequency(), pzem2.pf());
  checkPzem("Fase T",pzem3.voltage(), pzem3.current(), pzem3.power(), pzem3.energy(), pzem3.frequency(), pzem3.pf());
  // delay(1500);
}
