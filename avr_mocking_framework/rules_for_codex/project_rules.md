# Regole Progetto

## Regola Fondamentale

- ATTENZIONE: i repository non devono contenere in alcun modo logica di business o logica applicativa.
- Questa regola e' prioritaria e va riletta per prima ogni volta che si usa questo file.
- Il repository deve limitarsi a comunicare con il dispositivo, la libreria o il livello hardware nel modo piu' raw, diretto e vicino possibile al formato nativo del componente.
- Il repository puo' contenere solo la logica tecnica minima indispensabile per parlare con il dispositivo, leggere o scrivere dati, gestire dettagli del protocollo, parametri tecnici, errori tecnici o adattamenti strettamente infrastrutturali.
- Il repository non deve prendere decisioni applicative, non deve interpretare il significato finale del dato per il caso d'uso e non deve restituire esiti che rappresentano logica di business.
- Non devono esistere nel repository metodi del tipo "le date sono differenti", "la condizione applicativa e' valida", "il comportamento finale deve essere si o no" o simili, quando quel booleano rappresenta una decisione di dominio, di business logic o di caso d'uso.
- Se un metodo del repository ritorna un `bool`, quel `bool` deve rappresentare solo un esito tecnico o infrastrutturale coerente con il dispositivo o con l'operazione raw, non una decisione applicativa.
- Se il codice sta confrontando valori per decidere un comportamento funzionale dell'applicazione, quella responsabilita' non appartiene al repository.
- Se il dato va interpretato, normalizzato, convertito o validato in modo ricorrente e tipico del dispositivo, questa responsabilita' appartiene alla `activity`.
- Se invece il comportamento dipende dal flusso applicativo finale, dal coordinamento tra componenti o da una regola di dominio, questa responsabilita' appartiene alla business logic.
- Il repository non deve trasformarsi in una business logic mascherata, ne' in una `activity` mascherata.
- In caso di dubbio, preferire repository piu' raw e spostare ogni interpretazione non strettamente tecnica verso `activity` o business logic.

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
- Una `activity` ha senso quando sopra il dato raw esiste una trasformazione, interpretazione o normalizzazione ricorrente, tipica del dispositivo, che conviene non riscrivere ogni volta nella business logic.
- La `activity` non deve esistere per semplice pass-through o per sola orchestrazione tecnica.
- Se una `activity`, in media, richiede piu' di 2 o 3 interazioni tecniche con il repository per metodo e resta comunque un semplice pass-through o un raggruppamento tecnico, allora va rivalutata.
- In questi casi preferire un repository dedicato piu' completo invece di aggiungere un layer `activity` che aumenta solo il costo di mocking e manutenzione.
- Quindi il criterio non e' "seriale uguale activity" ne' "seriale uguale repository", ma: scegliere il layer che evita pass-through, evita troppe chiamate tecniche disperse e mantiene la logica di business fuori dal repository.

- Il repository deve restare il livello infrastrutturale che comunica con il dispositivo e restituisce dati grezzi, piatti o comunque vicini al formato nativo del componente.
- Il repository puo' contenere solo logica tecnica minima indispensabile: lettura, scrittura, framing, timeout, gestione buffer, dettagli di protocollo, errori tecnici, adattamenti strettamente infrastrutturali.
- Il repository non deve contenere logica applicativa, significati di dominio, decisioni di business o convenzioni legate a uno specifico caso d'uso finale.

- Una `activity` puo' diventare troppo chiacchierona rispetto a qualsiasi repository iniettato, non solo rispetto a `mf_repository_AvrMicroRepository`.
- Se una `activity` continua a ripetere molte chiamate tecniche al repository senza introdurre una vera logica ricorrente, testabile e utile, allora quel raggruppamento non deve stare nella `activity`.
- In questi casi il raggruppamento tecnico va riportato nel repository, pur mantenendolo raw e senza logica di business.
- Se invece sopra il dato raw esiste una logica ricorrente e testabile, come validazione, normalizzazione, conversione di formato, interpretazione tecnica del dato o confronto semantico del contenuto, allora questa responsabilita' appartiene alla `activity`, perche' deve poter essere testata in modo isolato.
- Se una trasformazione del dato e' ricorrente e tipica del dispositivo, appartiene alla `activity`.
- Se invece una decisione dipende dal comportamento applicativo finale, dalla sequenza delle operazioni o dal coordinamento tra piu' componenti, allora appartiene alla business logic.

- Se un componente comunica solo tramite seriale e `mf_repository_AvrMicroRepository` espone gia' le primitive raw necessarie come `begin(...)`, `available()`, `read()`, `print(...)`, `write(...)` o funzioni base di timing, non creare automaticamente un repository dedicato.
- In questi casi, se bastano poche primitive raw ripetute in modo semplice, va preferita una `activity` che riceve `mf_repository_AvrMicroRepository` in iniezione e si occupa della trasformazione ricorrente del dato.
- La semplice presenza di una comunicazione seriale non giustifica da sola la creazione di un nuovo repository.
- Tuttavia, se per usare bene quel componente una `activity` sarebbe costretta a fare molte interazioni tecniche consecutive con il repository di base, ad esempio letture o scritture multiple, gestione del framing, timeout, parsing tecnico, pulizia buffer o altre operazioni seriali ripetitive, allora un repository dedicato puo' essere giustificato.
- In questo caso il repository dedicato e' ammesso non perche' aggiunge logica di business, ma perche' accorpa in un unico punto una superficie infrastrutturale tecnica che altrimenti renderebbe la `activity` troppo chiacchierona, fragile e costosa da testare.
- Anche in questo caso il repository dedicato deve restare generico e raw, non deve sposarsi con un payload applicativo specifico, con un caso d'uso del progetto o con decisioni di business.

- Nei repository specializzati l'API pubblica non deve essere troppo atomica se questo costringerebbe business logic o activity a fare molte chiamate tecniche consecutive per comporre un'operazione semplice.
- `mf_repository_AvrMicroRepository` puo' e deve restare molto atomico, perche' rappresenta il livello base e granulare del microcontrollore.
- I repository specializzati di dispositivo, invece, non devono obbligare gli strati superiori a orchestrare decine di micro-passaggi tecnici per ottenere un risultato tecnico semplice e ricorrente del dispositivo.
- Se una operazione semplice richiederebbe molte chiamate consecutive allo stesso repository specializzato, allora quella composizione tecnica deve essere accorpata nel repository stesso.
- Nei repository specializzati, oltre a evitare logica di business, bisogna prevedere anche le operazioni normali e ricorrenti del dispositivo.
- Se per utilizzare correttamente il dispositivo una operazione tipica richiede piu' iterazioni o combinazioni di metodi tecnici gia' esistenti, questa sequenza deve essere accorpata nel repository.
- Questo accorpamento e' ammesso solo quando rappresenta una sequenza tecnica propria del dispositivo e non introduce logica di business.
- L'obiettivo e' evitare che business logic o activity debbano orchestrare piu' chiamate tecniche diverse, diventando fragili, verbose e costose da testare o mockare.
- Il problema non e' il numero di chiamate in assoluto, ma la presenza di sequenze tecniche eterogenee che devono essere coordinate dagli strati superiori.
- Se una sequenza tecnica e' ricorrente nell'uso reale del dispositivo, deve essere incapsulata nel repository come metodo pubblico piu' completo.
- Il repository deve quindi anticipare le azioni tipiche del dispositivo, non limitarsi a esporre primitive isolate quando queste non sono sufficienti per un uso pratico.
- Il repository puo' e deve quindi offrire metodi pubblici piu' completi quando questi rappresentano una sequenza tecnica ricorrente del dispositivo, purche' resti privo di logica di business.
- L'obiettivo e' ridurre pass-through, costo di mocking e numero di chiamate ripetitive negli strati superiori.
- Quindi il repository specializzato non deve essere ne' troppo intelligente sul piano applicativo, ne' troppo stupido sul piano tecnico.
- Deve restare raw nel significato del dato, ma sufficientemente macro nella superficie tecnica pubblica quando serve a incapsulare correttamente il comportamento ricorrente del dispositivo.

- Nei dispositivi che espongono principalmente uno stream seriale testuale o quasi testuale, come un GPS NMEA, non creare automaticamente un repository dedicato solo per leggere e ricomporre i dati in arrivo.
- Se il repository infrastrutturale gia' esistente, ad esempio `mf_repository_AvrMicroRepository`, espone gia' le primitive raw necessarie come `begin(...)`, `available()`, `read()` e funzioni base di timing, allora va preferita una `activity` che riceve quel repository in iniezione e si occupa della trasformazione ricorrente del dato.
- In questi casi la `activity` puo' leggere i byte, ricostruire le righe o i frame, validare il contenuto, fare parsing, normalizzazione, conversione e interpretazione del protocollo, senza introdurre un nuovo repository del dispositivo.
- Il numero elevato di iterazioni di lettura sul repository non giustifica da solo la creazione di un repository dedicato, se tali chiamate restano ripetizioni delle stesse poche primitive raw.
- Un repository dedicato al dispositivo va rivalutato solo quando il protocollo richiede una vera superficie infrastrutturale propria, ad esempio invio comandi, configurazione attiva, gestione stati del dispositivo, ACK o NACK, retry, timeout specifici, piu' operazioni pubbliche di controllo o una API hardware autonoma.
- Per un GPS usato come sorgente NMEA passiva, la forma preferita e': adapter seriale -> `mf_repository_AvrMicroRepository` -> `mf_activity_<nome>Activity`.
- In questo scenario il repository resta raw e vicino all'hardware, mentre la `activity` incapsula il significato ricorrente delle stringhe del dispositivo, ad esempio parsing di frasi NMEA, validazione del fix, estrazione coordinate, velocita', altitudine, data e ora.
- Evitare quindi di creare un repository dedicato se il componente aggiungerebbe solo un layer tecnico intermedio tra la seriale raw e una trasformazione che appartiene chiaramente alla `activity`.

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

## Testing E Mocking Repository

- Nei repository, le librerie reali e le dipendenze concrete vanno incluse solo nei file `.cpp`.
- I file `.h` devono restare puliti da include concreti legati all'hardware, alla board o a librerie esterne reali, per poter essere portati e mockati nei test.
- Gli header dei repository devono esporre solo l'interfaccia necessaria, senza dipendere direttamente dalle librerie reali di produzione.
- Le implementazioni reali nei file `.cpp` non fanno parte del materiale portato nei test di mocking.
- Quando si progetta un repository, verificare sempre che il mocking possa avvenire portando solo il `.h`, senza richiedere dipendenze concrete del `.cpp`.
- I repository che devono essere portati nei test o mockati dagli strati superiori devono essere progettati esplicitamente per il mocking.
- Nei repository usati polimorficamente o sostituiti con mock nei test, i metodi pubblici esposti agli strati superiori devono essere dichiarati `virtual`.
- Quando un repository viene usato come dipendenza polimorfica, anche il distruttore deve essere `virtual`.
- Non rendere `virtual` metodi privati, protetti o dettagli interni che non servono al mocking o alla sostituzione del componente nei test.
- Le parti interne del repository che rappresentano solo dettagli implementativi devono restare non virtuali, per evitare complessita' inutile e overhead non necessario.
- Il repository deve essere testabile e mockabile gia' per progettazione, non adattato ai test solo in un secondo momento.
- Quando si disegna la superficie pubblica del repository, considerare sempre anche il costo di mocking: pochi metodi, ben espressi, orientati al risultato.
- Se un repository espone troppi micro-metodi `virtual`, bisogna rivalutare la sua superficie pubblica e semplificarla.

## Memoria E Ottimizzazione Risorse

- In tutto il progetto, considerare sempre il risparmio di memoria come vincolo progettuale di base, sia su SRAM sia su flash.
- Ogni nuova soluzione deve essere valutata anche in funzione del costo in memoria, non solo della comodita' implementativa o della velocita' di sviluppo.
- Evitare strutture dati, buffer, tabelle, cache o copie temporanee quando non sono strettamente necessarie.
- Preferire implementazioni piu' leggere in memoria anche se leggermente meno comode, pur mantenendo leggibilita', testabilita' e coerenza architetturale.
- Nei repository, nelle activity e negli oggetti applicativi, evitare di mantenere in memoria dati duplicati se possono essere letti, elaborati o trasmessi in modo diretto.
- Evitare buffer grandi o permanenti quando bastano buffer piccoli, locali o riusabili.
- Evitare tabelle precalcolate, lookup table o altre ottimizzazioni orientate alla velocita' se il loro costo in memoria non e' giustificato dal caso reale.
- Se una libreria, un adapter o una soluzione introduce un costo di memoria elevato, segnalarlo esplicitamente e valutare un'alternativa piu' leggera.
- Preferire protocolli semplici, payload compatti e rappresentazioni numeriche leggere quando il progetto gira su microcontrollori con memoria limitata.
- Evitare allocazioni dinamiche, oggetti inutilmente pesanti o superfici pubbliche che costringono a mantenere stato interno non necessario.
- Prima di introdurre nuove dipendenze o nuove componenti, valutare sempre se il beneficio reale giustifica il costo in memoria e complessita'.
- In caso di dubbio tra due implementazioni equivalenti dal punto di vista funzionale, preferire quella che consuma meno memoria e introduce meno overhead strutturale.

## Naming

- Variabili, parametri e funzioni nuove in `snake_case`.
- I nomi delle cartelle virtuali e dei folder vanno scritti in minuscolo.
- I nomi dei metodi devono descrivere chiaramente il loro effetto o il loro valore di ritorno.
- Se un metodo ritorna `bool`, il nome deve leggere come una domanda o un predicato coerente con il risultato restituito.
- Evitare nomi come `read...` o `calculate...` quando il metodo ritorna in realta' un esito logico come `is_any_port_out_of_range()`.
- Se un metodo esegue letture ma ritorna un booleano di stato finale, il nome deve riflettere quello stato finale, non l'azione intermedia.
- Le activity devono seguire la convenzione: `mf_activity_<nome>Activity`
- I repository devono seguire la convenzione: `mf_repository_<nome>Repository`
- Il nome deve quindi mantenere sia il prefisso del tipo componente sia il suffisso finale coerente con il ruolo.
- Esempi corretti:
  - `mf_activity_AnalogPortBActivity`
  - `mf_repository_AvrMicroRepository`
- Quando si crea un nuovo file o una nuova classe appartenente a questi ruoli, rispettare sempre questa convenzione completa.
- Non usare naming alternativi semplificati o parziali se il componente appartiene al framework o ne segue le convenzioni.
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