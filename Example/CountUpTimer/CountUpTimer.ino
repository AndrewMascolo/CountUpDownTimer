#include<CountUpDownTimer.h>

CountUpDownTimer T(UP, HIGH); // Default precision is HIGH, but you can change it to also be LOW

void setup()
{
  Serial.begin(115200);
  //T.SetTimer(0,0,20);     //start at 1 minute (USE FOR: DOWN ONLY)
  T.SetStopTime(0,0,30); // stop at 10 seconds (USE FOR: UP/DOWN)
  T.StartTimer();
}

void loop()
{
  T.Timer(); // run the timer
  
  if (T.TimeHasChanged() ) // this prevents the time from being constantly shown.
  {
    Serial.print(T.ShowHours());
    Serial.print(":");
    Serial.print(T.ShowMinutes());
    Serial.print(":");
    Serial.print(T.ShowSeconds());
    Serial.print(":");
    Serial.print(T.ShowMilliSeconds());
    Serial.print(":");
    Serial.println(T.ShowMicroSeconds());
    // This DOES NOT format the time to 0:0x when seconds is less than 10.
    // if you need to format the time to standard format, use the sprintf() function.
  }
}
