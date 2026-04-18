# Regole Progetto

## Ambito Modifiche

- Modificare e creare file solo dentro il progetto corrente autorizzato.
- Fuori dal progetto corrente si puo' solo leggere come riferimento, salvo richiesta esplicita di modifica.

## Riferimento Architetturale

- Usare come riferimento il trunk principale di `avr_mocking_framework`.
- Non usare come riferimento operativo i sample project o i progetti sottostanti, salvo richiesta esplicita.
- Tutte le sottocartelle sotto `avr_mocking_framework` che contengono sample, progetti di esempio o materiale accessorio vanno escluse dal lavoro operativo normale.
- Queste sottocartelle si possono consultare solo in sola lettura e solo per capire come il framework e' stato usato in precedenza, mai come base architetturale o implementativa del lavoro corrente.
- Salvo indicazione esplicita dell'utente, considerare utile e autorevole solo il trunk principale del framework, con i suoi componenti reali come `objects`, `activity`, `repository` e le altre componenti del framework.
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

## Criterio Activity Vs Repository

- Non introdurre una `activity` se il componente non aggiunge vera logica applicativa o di dominio sopra il repository.
- Se una `activity`, in media, richiede piu' di 2 o 3 interazioni tecniche con il repository per metodo e resta comunque un semplice pass-through o un raggruppamento tecnico, allora va rivalutata.
- In questi casi preferire un repository unico piu' completo invece di aggiungere un layer `activity` che aumenta solo il costo di mocking e manutenzione.
- Una `activity` ha senso solo se introduce comportamento applicativo chiaro, riusabile e separabile dal repository.
- Se il componente e' solo infrastrutturale o di output tecnico, come un display LCD, e non porta vera logica applicativa, preferire l'uso diretto del repository nella business logic o nel punto architetturalmente corretto.
- Prima di introdurre una nuova `activity`, valutare sempre se nei test il layer aggiunge valore reale oppure solo dipendenze da moccare.
- Se una `activity` esistente risulta troppo sottile o troppo tecnica, proporre esplicitamente la semplificazione verso un repository unico.

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

## Stringhe E Formattazione Testo

- Non usare la classe `String` di Arduino.
- Non introdurre nuove dipendenze o logiche basate su `String` negli oggetti applicativi, nelle activity o nei repository.
- Preferire `const char*`, `char` e buffer `char[]` solo quando servono davvero.
- Evitare `snprintf`, `sprintf` e funzioni simili di formattazione del testo, salvo richiesta esplicita.
- Se serve stampare su LCD o su seriale, preferire chiamate dirette di `print(...)` tramite repository o activity invece di costruire stringhe intermedie.
- Non creare buffer di testo temporanei se il risultato puo' essere stampato direttamente in modo sequenziale.
- Se una parte del framework usa formattazione testuale non desiderata, fermarsi e segnalare esplicitamente che la modifica ricade sul framework.
- Eventuali modifiche a repository o activity del framework per eliminare uso di `String` o formattazioni testuali vanno fatte solo in modo coerente con i ruoli architetturali gia' esistenti.

## Repository LCD E Superficie Pubblica

- Nel repository LCD preferire una superficie pubblica stretta, con pochi metodi ad alto livello e gia' orchestrati.
- Evitare di esporre troppi micro-metodi pubblici se poi, nella business logic o nei test, andrebbero concatenati uno dopo l'altro.
- Preferire metodi macro che eseguono da soli l'operazione completa, anche se internamente ripetono qualche chiamata in piu'.
- Se una sequenza tipica richiede piu' chiamate consecutive per ottenere un risultato semplice, valutare di accorparla in un solo metodo pubblico del repository.
- Le operazioni di dettaglio del repository LCD vanno tenute il piu' possibile private o protette internamente, salvo reale necessita' architetturale.
- L'obiettivo e' ridurre il numero di chiamate da moccare nei test, non solo ridurre il numero di classi.
- Nei componenti infrastrutturali di output, come LCD o display simili, preferire metodi pubblici orientati al risultato finale visibile piuttosto che primitive troppo atomiche.

## Naming

- Variabili, parametri e funzioni nuove in `snake_case`.
- I nomi delle cartelle virtuali e dei folder vanno scritti in minuscolo.
- I nomi dei metodi devono descrivere chiaramente il loro effetto o il loro valore di ritorno.
- Se un metodo ritorna `bool`, il nome deve leggere come una domanda o un predicato coerente con il risultato restituito.
- Evitare nomi come `read...` o `calculate...` quando il metodo ritorna in realta' un esito logico come `is_any_port_out_of_range()`.
- Se un metodo esegue letture ma ritorna un booleano di stato finale, il nome deve riflettere quello stato finale, non l'azione intermedia.
- L'utente puo' riferirsi ai file anche con nomi abbreviati o approssimati.
- In ogni risposta, riportare sempre il nome completo esatto del file, cosi' da evitare ambiguita' e confermare che il riferimento sia stato capito correttamente.
- Quando viene generato codice da copiare e incollare, inserire sempre in testa un commento con il nome completo esatto del file di destinazione, ad esempio `.h`, `.cpp` o altro file pertinente.
- Il commento iniziale con il nome file deve servire come controllo visivo immediato, cosi' se il codice viene incollato nel file sbagliato l'errore si nota subito.

## Formattazione

- Evitare la formattazione a scala per costruttori, firme di metodi o funzioni e chiamate con parametri uno sotto l'altro quando la riga ci sta comodamente.
- Preferire che le firme dei metodi e delle funzioni abbiano i parametri su una sola riga, se la riga resta leggibile.
- Con monitor ampio, preferire tenere costruttori, firme e chiamate multi-parametro su una sola riga.
- Usare l'andata a capo solo quando serve davvero per chiarezza o limiti di spazio.
- Non spezzare automaticamente i parametri su piu' righe per stile, se la firma puo' stare bene su una riga.

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