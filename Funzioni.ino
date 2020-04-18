void initDisplay() {
  // here we set the framerate to 30, we do not need to run at default 60 and
  // it saves us battery life.
  arduboy.setFrameRate(30);
  // ab.beginNoLogo();
  cambiaStatus(0);
  arduboy.display();
}

void LeggiPulsanti() {
  int static lastpressed = 0;   //valore ultimo tasto premuto
  boolean static cambio;
  int butpres = arduboy.buttonsState();
  byte oldscalapos;

  //se tengo premuto per piu' di 3 secondi, mute on o off
  if ((butpres == lastpressed) && (butpres == A_BUTTON)) {
    if (millis() - specialcount >= 3000)  {
      mute = !mute;
      tinyfont.setCursor(105, 5);
      if (mute == 1) tinyfont.print("M");
      else arduboy.fillRect( 105, 5, 4, 4, 0 ); //avendo il background trasparente, cancello disegnando un quadrato nero
      arduboy.display();
      cambio = true;
      specialcount = millis();
    }
  }

  //se lascio A controlla se e' stato premuto per meno ddi 3 secondi percio' cambia status
  if (arduboy.justReleased(A_BUTTON)) {
    if ( (millis() - specialcount < 3000) && (cambio == false))  {
      cambiaStatus(1);
      lastpressed = butpres;
      arduboy.display();
    }
  }

  //tasto premuto
  if ((butpres != lastpressed) && (butpres != 0)) {
    //Serial.println(lastpressed);
    statusInvert = false;
    arduboy.invert(statusInvert);
    if (butpres == RIGHT_BUTTON ) {
      if (statusMode == 0)   {
        scalapos = (scalapos + 1) % 24;
        printScalaMode0() ;
      }
      else if (statusMode == 1)   {
        scalapos = (scalapos + 1) % 24;
        printScalaMode1() ;
      }
      else if (statusMode == 2) {
        oldscalapos = scalapos;
        scalapos = (scalapos + 1) % 12;
        printScalaMode2(oldscalapos, scalapos) ;
      }
      else if (statusMode == 3) {
        oldscalapos = scalapos;
        scalapos = (scalapos + 1) % 12;
        printScalaMode2(oldscalapos, scalapos) ;
      }
    }

    if (butpres == LEFT_BUTTON) {
      if (statusMode == 0)   {
        scalapos = ((scalapos - 1) + 24) % 24;
        printScalaMode0() ;
      }
      else if (statusMode == 1)   {
        scalapos = ((scalapos - 1) + 24) % 24;
        printScalaMode1() ;
      }
      else if (statusMode == 2) {
        oldscalapos = scalapos;
        scalapos = ((scalapos - 1) + 12) % 12;
        printScalaMode2(oldscalapos, scalapos) ;
      }
      else if (statusMode == 3) {
        oldscalapos = scalapos;
        scalapos = ((scalapos - 1) + 12) % 12;
        printScalaMode2(oldscalapos, scalapos) ;
      }
    }

    if (butpres == UP_BUTTON) {
      if ((statusMode == 1) || (statusMode == 2)) cambiafret(1);
    }

    if (butpres == DOWN_BUTTON) {
      if ((statusMode == 1) || (statusMode == 2)) cambiafret(-1);
    }

    if ( butpres == B_BUTTON) {
      if (statusMode == 0)   playScalaMod0();
      else if (statusMode == 1) playScalaMod1();
      else if (statusMode == 2) playScalaMod2() ;
      else if (statusMode == 3) playScalaMod3() ;
    }

    if (butpres == A_BUTTON) {
      //se premo a per la prima volta fai partire il conteggio
      specialcount = millis();
      cambio = false;
    }

    lastpressed = butpres;
    blinktime = millis();
    arduboy.display();
  }
  else if (arduboy.buttonsState() == 0) {
    lastpressed = 0;
  }
}

//-----------------------------------------
String getTono(int vval) {
  return (vval / 12 == 0 ? "M" : "m");
}

byte getScala(char notaf, String  tiposcala) {
  //idx= nota da calcolare NB 0-6
  byte idx = scalapos % 12;
  notaf = constrain(notaf, 0, 6);
  for (int i = 0; i < notaf + 1; i++)  {
    if (tiposcala == "M")     idx = idx +  scalamaggiore[i];
    else idx = idx +  scalaminore[i];
  }
  return idx;
}

void cambiafret(int valadd) {
  fretpos = fretpos + valadd;
  fretpos = constrain(fretpos, 0, 6);
  arduboy.fillRect( 0, 59, WIDTH, 5, 0 );
  //tasti (verticali)

  for (int i = 0; i < 6; i++) {
    //numerazione tasti
    tinyfont.setCursor(24 + (17 * i), 60);
    tinyfont.print(i + fretpos + 1);
  }
  if (fretpos == 0) arduboy.drawFastVLine(16, 38, 19, 1 ); //capotasto
  else arduboy.drawFastVLine(16, 38, 19, 0 );
}


//-----------------------
String padS(String sstt, int lens, String charsub) {
  //pad a sx
  String spaces = "";
  for (int i = sstt.length(); i < lens; i++) spaces = spaces + charsub;
  return  sstt + spaces ;
}

String padD(String sstt, int lens, String charsub) {
  //pad a sx
  String spaces = "";
  for (int i = sstt.length(); i < lens; i++) spaces = spaces + charsub;
  return  spaces + sstt ;
}

