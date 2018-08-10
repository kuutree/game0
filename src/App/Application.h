///////////////////////////////////////////////////////////
///アプリケーション本体
///
///
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include
#include "Type.h"


namespace app {
//*********************************************************
//Application
//*********************************************************
class Application
{
public:
	virtual ~Application() { /*何もしない*/ }
	void Initialize(const CreateApplicationParam& param) { OnInitialize(param); }
	int Finalize()										 { return OnFinalize(); }
	int Run()											 { return OnRun(); }
	void ErrorExit(int error_code)						 { OnErrorExit(error_code); }

	static size_t GetClassId() { return APPLICATION_ID; }
protected:
	virtual void OnInitialize(const CreateApplicationParam& param) = 0;
	virtual int OnFinalize() = 0;
	virtual int OnRun() = 0;
	virtual void OnErrorExit(int error_code) = 0;
};
} //namespace app
