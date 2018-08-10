#include "ApplicationManager.h"
#include "ApplicationFactory.h"


namespace app {
//=========================================================
//アプリケーション起動
int ApplicationManager::Startup(const CreateApplicationParam& param)
{
	m_application_ptr = ApplicationFactory::Create(param.class_id, param);
	if(!m_application_ptr)	return APPLICATION_UNKNOWN_ERROR;


	int end_code;
	end_code = m_application_ptr->Run();		if (end_code != APPLICATION_SUCCESS)	return end_code;
	end_code = m_application_ptr->Finalize();	if (end_code != APPLICATION_SUCCESS)	return end_code;

	m_application_ptr.reset();

	return APPLICATION_SUCCESS;
}


//=========================================================
//現在起動中アプリケーションをエラーによる強制終了をさせる
void ApplicationManager::ErrorExit(int error_code)
{
	if (m_application_ptr)	m_application_ptr->ErrorExit(error_code);
}
} //namespace app
