float kp=35,ki=0.001,kd=30,error,lasterror=0,kP=0,kI=0,kD=0,timeseries;//INITIALIZATION
int a=A0,act,angle,pid,ref=180,pidout,pidcont,pidc;//REFERENCE ANGLE SET AS 180
void setup()
{
Serial.begin(9600);//SETTING UP THE BAUD RATE
pinMode(11,OUTPUT);//ASSIGNING THE I/O PINS AS OUTPUT FOR GENERATING PWM SIGNALS
pinMode(9,OUTPUT);//ASSIGNING THE I/O PINS AS OUTPUT FOR GENERATING PWM SIGNALS
}
void loop()
{
timeseries=millis();//SETTING THE STOPWATCH
act=analogRead(a);//READING THE POTENTIOMTER'S OUTPUT
angle=map(act,1010,0,0,330);//MAPPING IT TO DEGREES
//PID LOGIC
error=ref-angle;
kP=(kp*error);
kI+=(ki*error);
kD=(kd*(error-lasterror));
pid=kP+kI+kD;
pidout=map(pid,630,-630,255,-255);//MAPPING PID OUTPUT FOR THE 8 BIT DAC
pidcont=abs(pidout);
pidc=constrain(pidcont,95,255);//MOTOR STOPS IF SUPPLY FALLS BELOW 4 VOLTS,SO IT IS CONSTRIANED
//PRINTING THE ANGLE AND TIME IN THE SERIAL MONITOR
Serial.print(angle);
Serial.print("\t");
Serial.println(timeseries);
//CHECKING THE ERROR TO DETERMINE THE DIRECTION OF ROTATION
if (error>1)
{
analogWrite(11,pidc);
analogWrite(9,0);
}
else if (error<-1)
{
analogWrite(11,0);
analogWrite(9,pidc);
}
else
{
analogWrite(11,0);
analogWrite(9,0);
}
lasterror=error;
}