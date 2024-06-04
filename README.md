# Test-DeviceTest-Potenza-644-Pid

**LISTA TEST**
- CANBUS
- I2C
- SSR (uscita SSR_1 e SSR_2)

**HARDWARE**
- Scheda Potenza Easylite/Welte (montata in piattaforma di test con il resto delle schede del kit Easylite/Welte)
- Microcontrollore ATMEGA644/A/B/P
- Alimentazione 24V accendendo tutto il kit, altrimenti basterebbero i 5V per eseguire i test su questo microcontrollore
- Scheda collegata al DeviceTest che indicherà le istruzioni su come eseguire i vari test

**AMBIENTE DI SVILUPPO**
- Visual Studio Code con estensione "PlatformIO"
- Ambiente e librerie di Arduino

**LINGUAGGIO DI PROGRAMMAZIONE**
- C++

**LIBRERIE**
- "SERIAL_" : libreria personalizzata per gestire i comandi inviati in seriale
- "CANBUS_" : libreria personalizzata per il test del canbus, basata sulla libreria "CAN" in cui bisogna specificare i gpio dei pin "CAN_CS" e "CAN_INT" (all'interno del file MCP2515.h)
- "I2C_" : libreria personalizzata per il test dell'i2c, basata sulla libreria "Wire"
- "USCITE_" : libreria personalizzata per il test delle 2 uscite "SSR" utilizzate in macchina

**FUNZIONAMENTO IN SINTESI**
- Il programma rimarrà in attesa finchè non gli sarà inviato un comando in seriale. Un numero corrisponderà a un test da avviare e se il comando non sarà riconosciuto, verrà inviata la lista dei comandi da poter inviare. Una volta avviato il test, in seriale verranno stampate alcune istruzioni su come effettuare i test, che verranno ulteriormente arricchite sull'interfaccia del devicetest. Il test delle uscite "SSR" è composto da più step, la prima parte richiederà l'invio di un comando per avanzare allo step successivo, dove si attenderà il comando di fine test per completare il test. Per inviare il comando "next" si potrà scrivere il numero "98" in seriale, mentre si potrà scrivere il numero "99" per completare il test. Gli altri test invece saranno automatici (test eseguiti dal programma che ritornerà direttamente il risultato).

**FUNZIONAMENTO CODICE**
- SERIAL_
  - serialEvent() : funzione che legge la seriale e all'invio di "\n" ritorna "true" che indicherà la lettura della seriale avvenuta e si potrà passare al controllo del comando ricevuto

  - confronta_stringhe() : funzione che avvia il test a seconda del comando ricevuto in seriale

  - isValidMessage(String message) : funzione a cui si passa una stringa e che ritorna true se la stringa non contiene caratteri speciali, oppure false se la stringa non è valida

  - isPrintable(char c) : funzione che controlla se il carattere che gli viene passato è un carattere speciale oppure no

- CANBUS_
  - ***CONTROLLARE ALL'INTERNO DEL FILE MCP2515.h E IMPOSTARE CORRETTAMENTE IL NUMERO DEI GPIO DEI PIN "MCP2515_DEFAULT_CS_PIN" E "MCP2515_DEFAULT_INT_PIN"***

  - TEST_canbus() : funzione che testa in automatico il canbus e che ritorna il risultato del test

- I2C_
  - ***IL TEST RICERCHERA' UN DISPOSITIVO CON INDIRIZZO I2C 0x5A E UN DISPOSITIVO CON INDIRIZZO I2C 0x5B, QUINDI IL TEST SI ASPETTA CHE SIANO COLLEGATI ALLA SCHEDA ENTRAMBI I SENSORI DI TEMPERATURA***

  - TEST_i2c() : funzione che testa in automatico l'i2c e che ritorna il risultato del test

- USCITE_
  - serialEvent_u() : funzione che legge la seriale e all'invio di "\n" ritorna "true" che indicherà la lettura della seriale avvenuta e si potrà passare al controllo del comando ricevuto

  - BEGIN_ssr() : funzione che inizializza entrambi i gpio che si andranno a testare nel test "SSR"

  - TEST_ssr() : funzione utilizzata per testare le uscite "SSR_1" e "SSR_2" (richiede il comando "next" per passare allo step successivo e il comando "end" per completare il test)
