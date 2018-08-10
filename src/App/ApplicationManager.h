///////////////////////////////////////////////////////////
///アプリケーション管理
///
///
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include
#include "Application.h"
#include "Type.h"
#include <memory>
#include <base/util/Singleton.h>

#include <Windows.h>

namespace app {
//*********************************************************
//ApplicationManager
//*********************************************************
class ApplicationManager : public base::util::Singleton<ApplicationManager>
{
	using ApplicationPtr = std::shared_ptr<Application>;
	ApplicationPtr m_application_ptr;
public:
	int Startup(const CreateApplicationParam& param);				///< アプリケーション起動
	void ErrorExit(int error_code = APPLICATION_UNKNOWN_ERROR);		///< 現在起動中アプリケーションをエラーによる強制終了をさせる
};
} //namespace app
