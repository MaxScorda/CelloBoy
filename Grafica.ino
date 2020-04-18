void drawFret( int vval , byte colore) {
  byte daval, aval;
  int ttot;
  if (vval == 99) { //solo griglia
    //TAB
    //corde (orizzontali)
    for (int i = 0; i < 4; i++) {
      arduboy.drawFastHLine(18, 38 + (6 * i), WIDTH - 22, 1 );
      tinyfont.setCursor(1, 36 + (6 * i));
      tinyfont.print(scoreb[bassfret[i]]);
    }
    //tasti (verticali)
    for (int i = 0; i < 7; i++) {
      arduboy.drawFastVLine(18 + (17 * i), 38, 19, 1 );
    }
    cambiafret(0);
  }
  else {
    for (int i = 0; i < 4; i++) { //corda
      daval = bassfret[i] + fretpos;
      aval = bassfret[i] + fretpos  + 6;
      if (((vval >= daval) && (vval <= aval) ) || ((vval + 12 >= daval) && (vval + 12 <= aval) ) || (vval == bassfret[i])) {
        ttot = ((vval - (bassfret[i] +  fretpos )) + 12) % 12;
        //eccezione per fret>1 e per corde vuote
        if ((ttot != 0) || (vval == bassfret[i])) {
          //if (vval == bassfret[i]) ttot = 0;
          if (vval == bassfret[i])  arduboy.fillCircle(9 , 38 + (6 * i), 2, colore);
          arduboy.fillCircle(9 + (17 * ttot), 38 + (6 * i), 2, colore);
        }
        if (colore == 1)  debugValue(i, ttot, vval, daval, aval);
      }
      if (colore == 0) arduboy.drawFastHLine(18, 38 + (6 * i), WIDTH - 20, 1 ); //se vi sono cancellazioni disegna riga: nb: potrei farla con un flag per identificare riga per riga ma ha senso?
    }
  }
}

void drawPenta( int vval , byte colore) {
  byte daval, aval;
  byte ttot = 0;
  byte noteidx = 0;
  boolean bemolle;
  if (vval == 99) { //solo griglia
    //chiave di fa
    arduboy.drawCircle(7, 43, 4, 1);
    arduboy.fillRect( 3, 41, 4, 6, 0 );
    arduboy.fillCircle(13, 40, 1, 1);
    arduboy.fillCircle(13, 46, 1, 1);
    //pentagramma
    //corde (orizzontali)
    for (int i = 0; i < 5; i++) {
      arduboy.drawFastHLine(0, 38 + (5 * i), WIDTH , 1 );
    }
    //tasti (verticali)
    for (int i = 0; i < 2; i++) {
      arduboy.drawFastVLine(0 + (2 * i), 39, 20, 1 );
    }
  }
  else {
    while (ttot < vval) {
      noteidx++;
      ttot = ttot + scalamaggiore[noteidx];
    }
    if (ttot > vval) bemolle = true;
    else bemolle = false;
    for (int i = (noteidx + 4) % 7; i < 11; i = i + 7) {
      arduboy.fillRoundRect(9 + (10 * i), 59 - (2.5f * i), 6, 4, 1, colore);
      if (bemolle == true) arduboy.fillCircle(17 + (10 * i), 60 - (2.5f * i), 1, colore);
      if ((colore == 0) && (i % 2 == 1) && ((noteidx + 3) % 7 < 11))  {
        arduboy.drawFastHLine(0, 61 - (2.5f * i), WIDTH , 1 ); //se vi sono cancellazioni disegna riga: nb: potrei farla con un flag per identificare riga per riga ma ha senso?
      }
    }
  }
}

void debugValue(int corda, int tasto, int nota, byte daval, byte aval) {
  /*
    Serial.print(F("Str "));
    Serial.print(corda + 1);
    Serial.print(F(" Fret "));
    Serial.print(tasto % 6);
    Serial.print(F(" Nota "));
    Serial.print(nota);
    Serial.print(F(" - "));
    Serial.print(bassfret[corda] + tasto);
    Serial.print(F(" -- "));
    Serial.print(F(" daV "));
    Serial.print(daval);
    Serial.print(F(" aV "));
    Serial.print(aval);
    Serial.println(F("."));
  */
}
