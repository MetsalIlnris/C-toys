iint out=8;

void setup()
{
}

void loop()
{
  rh();
  tone(out,523);//1
  delay(400);
  tone(out,587);//2
  delay(200);
  noTone(out);
  delay(200);
  tone(out,587);//2
  delay(400);
  noTone(out);
  delay(1200);
  rh();
  tone(out,523);//1
  delay(400);
  tone(out,392);//5
  delay(200);
  noTone(out);
  delay(1800);
   rh();
  tone(out,523);//1
  delay(400);
  tone(out,587);//2
  delay(200);
  noTone(out);
  delay(200);
  tone(out,587);//2
  delay(400);
  noTone(out);
  delay(1200);
   rh();
  tone(out,659);//3
  delay(200);
  noTone(out);
  delay(200);
  tone(out,659);//3
  delay(1200);
  noTone(out);
  delay(800);
}


  void rh()
{
  tone(out, 784);//5
  delay( 400 );
   tone(out, 659);//3
  delay( 400 );
   noTone(out);
  delay( 400 );
   tone(out, 523);//11
  delay( 100 );
  noTone(out);
  delay(100);
   tone(out, 523);
  delay( 200 );
   tone(out, 587);//2
  delay( 400 );
   tone(out, 392);//5
  delay( 400);
  noTone(out);
  delay( 400);
   tone(out, 523);//1
  delay( 200);
   tone(out, 440);//6
  delay( 200);
   tone(out, 523);//1
  delay( 400);
   tone(out, 440);//6
  delay( 400);
  
}

