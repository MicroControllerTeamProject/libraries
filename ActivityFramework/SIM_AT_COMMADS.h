#pragma once

namespace progmem
{
	namespace strings
	{
		namespace atCommands
		{
			namespace simModule
			{
				PROGMEM const char simCommands[] =
					//index 0
					"AT+CPMS=\"SM\"\0"
					//index 13
					"AT+CMGF=1\0"
					//index 23
					"AT+CSCLK=0\0"
					//index 34
					"AT+CPMS?\0"
					//index 43
					"AT+CMGR=\0"
					//index 52
					"+CMGR:\0"
					//index 59
					"AT+CMGD=\0"
					//index 68
					"AT\0"
					//index 71
					"AT+CMGD=1,4\0"
					//index 83
					"AT+CMGR=1\0"
					//index 93
					"ATD\0";
			}
		}
	}
}