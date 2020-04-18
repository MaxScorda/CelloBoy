
void cambiaStatus(byte rif) {
  // 0-AeN: scala a e n
  // 1-KEY: tab e play automatici
  // 2-MAN: play manuale
  // 3-PEN: pentagramma
  // 4-INF: info
  String Testo;
  char* TestoFull[] = {"AeNKEYMANPENINF"};
  Testo = TestoFull[0];
  statusMode = (statusMode + rif) % 5;
  arduboy.clear();
  //cambia header
  if (statusMode != 4) {
    for (int i = 0; i < 3; i++) {
      arduboy.drawChar( 110 + (6 * i), 0, Testo.charAt((statusMode * 3) + i), BLACK, WHITE, 1);
    }
    //header
    arduboy.drawFastHLine(0, 9, WIDTH, 1 );
    if (statusMode == 3) {
      //  arduboy.drawFastHLine(20, 33, WIDTH - 40, 1 );
    }
    else   arduboy.drawFastHLine(0, 33, WIDTH, 1 );
    tinyfont.setCursor(105, 5);
    tinyfont.print((mute == true ? "M" : " "));
  }
  else {
    arduboy.drawRect( 0, 0, WIDTH, HEIGHT, 1 );
    arduboy.drawRect( 2, 2, WIDTH - 4, HEIGHT - 4, 1 );
  }

  //cambia display
  if (statusMode == 0) {
    scalapos = 0;
    printScalaMode0() ;
  }
  else if (statusMode == 1) {
    scalapos = 0;
    printScalaMode1() ;
    drawFret( 99, 0); //griglia vuota
  }
  else if (statusMode == 2) {
    scalapos = 0;
    printScalaMode2(99, 99) ;
    drawFret( 99, 0); //griglia vuota
  }
  else if (statusMode == 3) {
    scalapos = 0;
    printScalaMode2(99, 99) ;
    drawPenta( 99, 0); //griglia vuota
  }
  else if (statusMode == 4) {
    printInfo();
  }
}



//===================== Mode 0
void printScalaMode0() {
  //scala N
  char posidxs = 0;
  char posidxse = 0;
  String scalaN = "";
  String scalaA = "";

  //Head
  arduboy.setCursor(1, 0);
  arduboy.print(F("Key "));
  arduboy.print( (getTono(scalapos) == "M" ? F("Maj") : F("min")));
  arduboy.print(F(": "));
  arduboy.print(padS(scoreb[scalapos % 12] , 2, " "));
  arduboy.print(F(" - "));
  arduboy.print( padS(scoreN[scalapos % 12], 3, " ") );

  arduboy.fillRect( 0, 42, WIDTH, 14, 0 );
  //Maggiore
  for (int i = 0; i < 7; i++)  {
    scalaN = scalaN + scoreN[getScala(i, F("M")) % 12] + " ";     //scala naturale
    scalaA = scalaA + padS(scoreb[getScala(i, F("M")) % 12], 3, " ");   //scala anglosassone
  }

  tinyfont.setCursor(1, 42);
  tinyfont.print(scalaN);
  arduboy.setCursor(1, 13);
  arduboy.print(scalaA);
  //Minore
  scalaN = "";
  scalaA = "";
  for (int i = 0; i < 7; i++)  {
    scalaN = scalaN + scoreN[getScala(i, F("m")) % 12] + " ";
    scalaA = scalaA + padS(scoreb[getScala(i, F("m")) % 12], 3, " ");
  }
  arduboy.setCursor(1, 23);
  arduboy.print(scalaA);
  tinyfont.setCursor(1, 52);
  tinyfont.print(scalaN);
}

void playScalaMod0() {
  int nota;
  int firstnota =  pgm_read_word_near(&allNotes[getScala(0, getTono(scalapos)) % 12]);
  int durata = 1000;
  if (mute == false ) arduboy.audio.on();
  for (int i = 0; i < 7 ; i++) {
    nota = pgm_read_word_near(&allNotes[getScala(i, getTono(scalapos)) % 12]);
    if (nota < firstnota) nota = nota * 2;
    sound.tone(nota, durata);
    arduboy.drawRect(i * 3 * 6, 11 + (scalapos >= 12 ? 10 : 0), 6 * 3, 11, WHITE);
    arduboy.display();
    while (sound.playing()) {
    }
    //delay(4000);
    arduboy.drawRect(i * 3 * 6, 11 + (scalapos >= 12 ? 10 : 0), 6 * 3, 11, 0);
    arduboy.display();
  }
  arduboy.audio.off();
}

//===================== Mode 1
void printScalaMode1() {
  //scala a
  char posidxs = 0;
  char posidxse = 0;
  String scalaA = "";

  //Head
  arduboy.setCursor(1, 0);
  arduboy.print(F("Key "));
  arduboy.print( (getTono(scalapos) == "M" ? F("Maj") : F("min")));
  arduboy.print(F(": "));
  arduboy.print(padS(scoreb[scalapos % 12] , 2, " "));
  arduboy.print(F(" - "));
  arduboy.print( padS(scoreN[scalapos % 12], 3, " ") );

  //Maggiore
  for (int i = 0; i < 7; i++)  {
    scalaA = scalaA + padS(scoreb[getScala(i, F("M")) % 12], 3, " ");   //scala anglosassone
  }
  arduboy.setCursor(1, 13);
  arduboy.print(scalaA);

  //Minore
  scalaA = "";
  for (int i = 0; i < 7; i++)  {
    //scala anglosassone
    scalaA = scalaA + padS(scoreb[getScala(i, F("m")) % 12], 3, " ");
  }
  //scala a
  arduboy.setCursor(1, 23);
  arduboy.print(scalaA);
}


void playScalaMod1() {
  int nota;
  int firstnota =  pgm_read_word_near(&allNotes[getScala(0, getTono(scalapos)) % 12]);
  int durata = 1000;
  if (mute == false ) arduboy.audio.on();
  for (int i = 0; i < 7 ; i++) {
    nota = pgm_read_word_near(&allNotes[getScala(i, getTono(scalapos)) % 12]);
    if (nota < firstnota) nota = nota * 2;
    sound.tone(nota, durata);
    //Serial.println(nota);
    //disegna rettangolo NB: le lettere sono 5x8, iniziano da pos. 1,14
    arduboy.drawRect(i * 3 * 6, 11 + (scalapos >= 12 ? 10 : 0), 6 * 3, 11, WHITE);
    drawFret( getScala(i, getTono(scalapos)) % 12, 1);
    // Serial.println( getScala(i, F("M")) % 12);
    arduboy.display();
    while (sound.playing()) {
    }
    //delay(4000);
    arduboy.drawRect(i * 3 * 6, 11 + (scalapos >= 12 ? 10 : 0), 6 * 3, 11, 0);
    drawFret( getScala(i, getTono(scalapos)) % 12, 0);
    arduboy.display();
  }
  arduboy.audio.off();
}


//===================== Mode 2
void printScalaMode2(byte oldpos, byte newpos) {
  //Head
  arduboy.setCursor(1, 0);
  arduboy.print(F("Key: "));
  arduboy.print(padS(scoreb[scalapos % 12] , 2, " "));
  arduboy.print(F(" - "));
  arduboy.print( padS(scoreN[scalapos % 12], 3, " ") );

  if (oldpos == 99) { //init
    for (int i = 0; i < 12; i++)  {
      arduboy.setCursor(10 + (i % 6) * 20, 13 + (i / 6) * 10);
      arduboy.print(scoreb[i]);
    }
    arduboy.drawRect(7 , 11, 20, 11, WHITE);
  }
  else {
    arduboy.drawRect(7 + (oldpos % 6) * 20 , 11 + (oldpos / 6) * 10, 20, 11, BLACK);
    arduboy.drawRect(7 + (newpos % 6) * 20 , 11 + (newpos / 6) * 10, 20, 11, WHITE);
  }
}


void playScalaMod2() {
  int nota;
  int durata = 2000;
  if (mute == false ) arduboy.audio.on();
  nota = pgm_read_word_near(&allNotes[scalapos]);
  sound.tone(nota, durata);
  drawFret( scalapos, 1);
  arduboy.display();
  while (sound.playing()) {
  }
  drawFret( scalapos, 0);
  arduboy.display();
  arduboy.audio.off();
}


//===================== Mode 3

void playScalaMod3() {
  int nota;
  int durata = 2000;
  if (mute == false ) arduboy.audio.on();
  nota = pgm_read_word_near(&allNotes[scalapos]);
  sound.tone(nota, durata);
  drawPenta(scalapos, 1);
  arduboy.display();
  while (sound.playing()) {
  }
  drawPenta( scalapos, 0);
  arduboy.display();
  arduboy.audio.off();
}


//===================== Mode 4
void printInfo() {
  arduboy.setCursor(8, 10);
  arduboy.setTextSize(2);
  arduboy.print(F("CelloBoy"));
  arduboy.setTextSize(1);
  arduboy.print(F("1.0"));
  arduboy.setCursor(8, 30);

  arduboy.print(F("Max "));
  arduboy.print(F("Scordamaglia "));
  arduboy.setCursor(8, 40);
  arduboy.print(F("maxscorda@gmail.com"));
  arduboy.setCursor(8, 50);

  arduboy.print(F("(c) 2020 "));
  arduboy.setTextSize(1);
}


