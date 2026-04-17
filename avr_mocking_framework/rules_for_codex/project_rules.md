# Regole Progetto

## Ambito Modifiche

- Modificare e creare file solo dentro il progetto corrente autorizzato.
- Fuori dal progetto corrente si puo' solo leggere come riferimento, salvo richiesta esplicita di modifica.

## Riferimento Architetturale

- Usare come riferimento il trunk principale di `avr_mocking_framework`.
- Non usare come riferimento operativo i sample project o i progetti sottostanti, salvo richiesta esplicita.
- Non introdurre wrapper o oggetti personali se il trunk del framework ha gia' il tipo corretto.
- Non creare nuove activity dentro il progetto applicativo se nel trunk di `avr_mocking_framework` esiste gia' una activity adatta.
- Se una activity non esiste nel framework, chiedere sempre prima il permesso.
- Quando serve una nuova activity, decidere esplicitamente con l'utente se:
  - crearla direttamente in `avr_mocking_framework`, oppure
  - crearla localmente nel progetto corrente e poi portarla nel framework.
- Stesso criterio per repository e per le altre componenti che appartengono al framework.
- Se repository o componenti infrastrutturali non esistono nel framework, chiedere sempre prima il permesso.
- Quando serve crearne una nuova, decidere esplicitamente con l'utente se:
  - crearla direttamente in `avr_mocking_framework`, oppure
  - crearla localmente nel progetto corrente e poi spostarla manualmente nel framework.
- Se emerge la necessita' di creare qualsiasi componente che appartiene al framework, non crearla localmente in autonomia.
- In questi casi bisogna fermarsi, sollevare esplicitamente l'eccezione e dire che si tratta di una componente da aggiungere al framework.
- Solo dopo la decisione esplicita dell'utente si puo' scegliere dove crearla.

## Commons Layer

- Usare `mf::commons::commonsLayer` dove serve davvero negli oggetti applicativi.
- Non usare `commonsLayer` nel file `.ino` se non e' strettamente necessario.
- Preferire `commonsLayer` nella business logic, nelle activity e negli oggetti che lavorano davvero.

## Macro E Debug

- Rimuovere dal progetto applicativo i branch `_ON_MOCKING_TESTS`.
- Non decidere in anticipo come verra' usato `_ON_MOCKING_TESTS` nei test futuri.
- `_DEBUG_FOR_SERIAL` e' ammesso negli oggetti applicativi che fanno lavoro reale.
- Usare `_DEBUG_FOR_SERIAL` in modo leggero, con pochi log significativi.
- Per il debug seriale usare `AvrMicroRepository`, non `Serial` diretto.
- Non inserire logging automatico nel file `.ino`, salvo richiesta esplicita.

## Naming

- Variabili, parametri e funzioni nuove in `snake_case`.
- I nomi delle cartelle virtuali e dei folder vanno scritti in minuscolo.
- I nomi dei metodi devono descrivere chiaramente il loro effetto o il loro valore di ritorno.
- Se un metodo ritorna `bool`, il nome deve leggere come una domanda o un predicato coerente con il risultato restituito.
- Evitare nomi come `read...` o `calculate...` quando il metodo ritorna in realta' un esito logico come `is_any_port_out_of_range()`.
- Se un metodo esegue letture ma ritorna un booleano di stato finale, il nome deve riflettere quello stato finale, non l'azione intermedia.

## Formattazione

- Evitare la formattazione a scala per costruttori, firme o chiamate con parametri uno sotto l'altro quando la riga ci sta comodamente.
- Con monitor ampio, preferire tenere costruttori e chiamate multi-parametro su una sola riga, se resta leggibile.
- Usare l'andata a capo solo quando serve davvero per chiarezza o limiti di spazio.

## Stile Operativo

- Il file `.ino` deve restare minimale: wiring, setup e loop.
- Le logiche reali devono stare nella business logic, nelle activity o negli oggetti applicativi.
- Evitare costanti o variabili applicative aggiuntive solo per assegnare proprieta' agli oggetti, se i valori possono essere messi direttamente nella creazione o nell'assegnazione delle proprieta'.
- Se i sensori o gli oggetti aumentano molto di numero, non duplicare variabili intermedie per ogni proprieta': preferire assegnazioni dirette sugli oggetti.
- Le properties degli oggetti vanno messe direttamente sugli oggetti, quando vengono creati o configurati.
- Cercare di configurare ogni oggetto tutto insieme, in modo atomico, invece di spargere la sua configurazione in vari punti.
- Quando un oggetto viene creato o inizializzato, preferire una configurazione completa e concentrata nello stesso blocco di codice.
- In `AppConfig` inserire solo proprieta' trasversali all'applicazione.
- Evitare di mettere in `AppConfig` parametrizzazioni troppo legate ai singoli oggetti, sensori o componenti specifici.
- La configurazione specifica degli oggetti deve restare sugli oggetti stessi o nei punti in cui vengono creati e inizializzati.
- Nelle risposte essere sintetici e dire solo le cose piu' importanti.
- Se una regola non e' chiara, aggiornare questo file invece di duplicare istruzioni sparse.
