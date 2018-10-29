#pragma once
class ISensor
{
	bool _isDetectedAllarm;
public:
	virtual bool IsSensorWorking()=0;
	virtual bool SetIsSentSMSAllarm(bool isDetectedAllarm);
    virtual bool IsSentSMSAllarm();
};

