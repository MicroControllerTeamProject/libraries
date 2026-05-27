#pragma once
#include <mf_model_AnalogPortB.h>
#include <mf_repository_AvrMicroRepository.h>
#include <stdint.h>
#if _DEBUG_FOR_SERIAL
#include <Arduino.h>
#endif // _DEBUG_FOR_SERIAL
/// <summary>
/// Classe astratta di base per la gestione di più porte analogiche di tipo B, 
/// che rappresentano sensori o ingressi analogici configurati con soglie di allarme e 
/// tempi di attivazione.	
/// </summary>
class AnalogPortBActivity{
public:
	/// <summary>
	/// Costruttore che accetta in ingresso una reference al repository AVR, 
	/// il numero di porte analogiche di base da gestire,e un array di puntatori alle 
	/// porte analogiche di base da gestire,
	/// </summary>
	/// <param name="avrMicroRepository"></param>
	/// <param name="analogPortsNumber"></param>
	/// <param name="analogPortBase"></param>
	AnalogPortBActivity(AvrMicroRepository& avrMicroRepository, uint8_t analogPortsNumber,AnalogPortB** analogPortBase);
	virtual ~AnalogPortBActivity() = 0;
	AvrMicroRepository* get_avr_micro_repository();
	/// <summary>
	/// calcola se è trascorso il tempo necessario per attivare l'allarme se il valore è sotto la soglia 
	/// in base alla configurazione di ogni porta, e aggiorna i 
	/// flag is_time_under_threshold_elapsed di ogni porta.
	/// </summary>
	/// <param name="AnalogPortB"></param>
	/// <returns></returns>
	bool is_delay_elapsed_for_ports_under_threshold(AnalogPortB* AnalogPortB);
	/// <summary>
	/// calcola se è trascorso il tempo necessario per attivare l'allarme se il valore è sopra la soglia
	/// in base alla configurazione di ogni porta, e aggiorna i 
	/// flag is_time_above_threshold_elapsed di ogni porta.
	/// </summary>
	/// <param name="AnalogPortB"></param>
	/// <returns></returns>
	bool is_delay_elapsed_for_ports_above_threshold(AnalogPortB* AnalogPortB);
	/// <summary>
	/// resetta i flag di allarme e di tempo trascorso per tutte le porte, e aggiorna i valori 
	/// digitali di ogni porta leggendo i valori analogici dai pin corrispondenti.
	/// </summary>
	void analog_read_for_all_ports();
	/// <summary>
	/// Fa la media di un certo numero di letture analogiche da un pin, 
	/// e aggiorna il valore digitale della porta corrispondente al pin, 
	/// sottraendo l'offset se è stato configurato.
	/// </summary>
	/// <param name="pin"></param>
	/// <param name="index_port"></param>
	/// <param name="number_of_read"></param>
	/// <returns></returns>
	uint16_t analog_read_average(uint8_t pin,uint8_t index_port, uint8_t number_of_read);
	/// <summary>
	/// Fa la media di un certo numero di letture analogiche da un pin, e aggiorna
	/// l'offset della porta corrispondente al pin.
	/// L'offet serve a compensare eventuali errori di lettura o di taratura del sensore, 
	/// e viene sottratto al valore digitale letto per ottenere un valore più preciso.
	/// </summary>
	/// <param name="pin"></param>
	/// <param name="index_port"></param>
	/// <param name="number_of_read"></param>
	void set_offset(uint8_t pin, uint8_t index_port, uint8_t number_of_read);
	/// <summary>
	/// Ritorna il numero di porte analogiche gestite dall'attività, che corrisponde alla dimensione 
	/// dell'array di porte analogiche passato al costruttore.
	/// </summary>
	/// <returns></returns>
	uint8_t get_analog_ports_number();
	/// <summary>
	/// Resetta i flag di allarme e di tempo trascorso per tutte le porte, 
	/// senza aggiornare i valori digitali,
	/// </summary>
	void reset_ports();
	/// <summary>
	/// Setta lo stato del processo che utilizza questa attività, in modo da poter bloccare o 
	/// sbloccare l'esecuzione del processo in base al livello di allarme delle porte analogiche.
	/// </summary>
	/// <param name="status"></param>
	void set_process_status(mf::commons::commonsLayer::ProcessStatus status);
	/// <summary>
	/// Ritorna lo stato del processo che utilizza questa attività, in modo da poter verificare 
	/// se il processo è bloccato o sbloccato in base al livello di allarme delle porte analogiche.
	/// </summary>
	/// <returns></returns>
	mf::commons::commonsLayer::ProcessStatus get_process_status();
private:
	uint8_t analog_port_number = 0;
	AvrMicroRepository* avrMicroRepository = nullptr;
	AnalogPortB** analogPortB = {};
	mf::commons::commonsLayer::ProcessStatus processBlockedBy = mf::commons::commonsLayer::ProcessStatus::blocked_level_too_high;
};
inline AnalogPortBActivity::~AnalogPortBActivity() {}

