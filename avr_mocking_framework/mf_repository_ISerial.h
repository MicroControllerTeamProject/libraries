#pragma once
#include <stdint.h>
#include <stddef.h>
#include <string.h>  // strlen
#include <stdio.h>   // snprintf

/// eSerial: interfaccia pura per I/O seriale, indipendente da Arduino
class ISerial {
public:
	virtual ~ISerial() = default;
	/// Avvia la seriale alla velocità specificata
	virtual void begin(unsigned long baud) = 0;
	/// Scrive un singolo byte
	virtual size_t write(uint8_t byte) = 0;
	/// Scrive un buffer di byte
	virtual size_t write(const uint8_t* buffer, size_t size) = 0;
	/// Scrive una stringa C nul-terminata
	virtual size_t write(const char* str) = 0;
	/// Scrive un buffer di caratteri
	virtual size_t write(const char* buffer, size_t size) = 0;
	/// Quanti byte sono disponibili per la lettura?
	virtual int available() = 0;
	/// Legge un byte (o -1 se nessun dato)
	virtual int read() = 0;
	/// Interroga il prossimo carattere senza consumarlo
	virtual int peek() = 0;
	/// Svuota i buffer di ricezione
	virtual void flush() = 0;
	/// Legge fino a `length` byte o fino al timeout
	virtual size_t readBytes(char* buffer, size_t length) = 0;
	/// Legge fino a `terminator` o a `length` byte
	virtual size_t readBytesUntil(char terminator, char* buffer, size_t length) = 0;
	/// Cerca la sequenza `target` nei dati in arrivo
	virtual bool find(const char* target) = 0;
	/// Cerca `target` fino a `terminator`
	virtual bool findUntil(const char* target, char terminator) = 0;
	/// Legge un intero (salta i non-numerici)
	virtual long parseInt() = 0;
	/// Legge un float (salta i non-numerici)
	virtual float parseFloat() = 0;
	/// Imposta il timeout per le operazioni di lettura
	virtual void setTimeout(unsigned long timeout) = 0;
	virtual const int getRxBufferSize() = 0;
	// --- print/println wrappers basati su write() ---
	/// Stampa una stringa, con newline opzionale
	virtual size_t print(const char* s, bool nl = false) {
		size_t n = write(reinterpret_cast<const uint8_t*>(s), strlen(s));
		if (nl) {
			n += write(reinterpret_cast<const uint8_t*>("\r\n"), 2);
		}
		return n;
	}
	virtual size_t print(char c, bool nl = false) {
		// Scrivo direttamente il byte
		size_t n = write(static_cast<uint8_t>(c));
		if (nl) {
			// Aggiungo CR+LF
			n += write(reinterpret_cast<const uint8_t*>("\r\n"), 2);
		}
		return n;
	}
	/// Stampa un intero 32-bit, con newline opzionale
	virtual size_t print(int32_t x, bool nl = false) {
		char buf[12];
		int len = snprintf(buf, sizeof(buf), "%ld", (long)x);
		size_t n = write((const uint8_t*)buf, len);
		if (nl) {
			n += write((const uint8_t*)"\r\n", 2);
		}
		return n;
	}
	/// Stampa un float, con newline opzionale e precisione personalizzabile
	virtual size_t print(float f, bool nl = false, int precision = 2) {
		char buf[32];
		int len = snprintf(buf, sizeof(buf), "%.*f", precision, f);
		size_t n = write((const uint8_t*)buf, len);
		if (nl) {
			n += write((const uint8_t*)"\r\n", 2);
		}
		return n;
	}
	/// Stampa un byte (uint8_t) come numero, con newline opzionale
	virtual size_t print(uint8_t x, bool nl = false) {
		return print((int32_t)x, nl);
	}
	
	// Alias println per stringhe, ma senza delegare a print()
	virtual size_t println(const char* s) {
		// Scrivo prima la stringa
		size_t n = write((const uint8_t*)s, strlen(s));
		// Poi CR+LF
		n += write((const uint8_t*)"\r\n", 2);
		return n;
	}
	// Alias println per char
	virtual size_t println(char c) {
		size_t n = write(static_cast<uint8_t>(c));
		n += write((const uint8_t*)"\r\n", 2);
		return n;
	}
	// Alias println per int32_t
	virtual size_t println(int32_t x) {
		char buf[12];
		int len = snprintf(buf, sizeof(buf), "%ld", (long)x);
		size_t n = write((const uint8_t*)buf, len);
		n += write((const uint8_t*)"\r\n", 2);
		return n;
	}
	// Alias println per float
	virtual size_t println(float f, int precision = 2) {
		char buf[32];
		int len = snprintf(buf, sizeof(buf), "%.*f", precision, f);
		size_t n = write((const uint8_t*)buf, len);
		n += write((const uint8_t*)"\r\n", 2);
		return n;
	}
	// Alias println per uint8_t
	virtual size_t println(uint8_t x) {
		return println(static_cast<int32_t>(x));
	}
	//virtual size_t println(int x) {
	//	return println(static_cast<int32_t>(x));
	//}


};
