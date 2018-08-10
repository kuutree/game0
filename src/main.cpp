#include <Platform/Win/WindowManager.h>
#include <App/ApplicationManager.h>
#include <App/ApplicationFactory.h>
#include <Platform/Win/Obj/WindowFrame.h>


//*********************************************************
//WindowApplication
//*********************************************************
class WindowApplication : public app::Application
{
public:
	struct Param : public app::CreateApplicationParam
	{
		HINSTANCE h_instance;
		HINSTANCE h_prev_instance;
		LPSTR lp_cmd_line;
		int n_cmd_show;
		Param(HINSTANCE _h_instance, HINSTANCE _h_prev_instance, LPSTR _lp_cmd_line, int _n_cmd_show)
		{
			class_id = WindowApplication::GetClassId();
			h_instance = _h_instance;
			h_prev_instance = _h_prev_instance;
			lp_cmd_line = _lp_cmd_line;
			n_cmd_show = _n_cmd_show;
		}
	};
	static size_t GetClassId() { return app::WINDOW_APPLICATION_ID; }
protected:
	virtual void OnInitialize(const app::CreateApplicationParam& param)
	{
		const Param& _param = static_cast<const Param&>(param);

		win::WindowManager::Initialize();
		win::WindowManager::GetInstance().Register(_param.h_instance, _param.h_prev_instance, _param.lp_cmd_line, _param.n_cmd_show);

		win::WindowFrame::CreateWindowParam create_param;
		create_param.class_name = L"ABC";
		create_param.title_name = L"ABC";
		auto parent_ptr = win::WindowManager::GetInstance().CreateWindowObject(create_param);

		create_param.class_name = L"DEF";
		create_param.title_name = L"DEF";
		create_param.parent_ptr = parent_ptr;
		create_param.child_type = win::ChildType::CHILD_POPUP;
		win::WindowManager::GetInstance().CreateWindowObject(create_param);
	}
	virtual int OnFinalize()
	{
		win::WindowManager::Finalize();
		return app::APPLICATION_SUCCESS;
	}
	virtual int OnRun()
	{
		while (win::WindowManager::GetInstance().MessageProcess())
		{
		}
		return app::APPLICATION_SUCCESS;
	}
	virtual void OnErrorExit(int error_code)
	{
		exit(error_code);
	}
};

REGISTER_APPLICATION_FACTORY_UNIT(WindowApplication, WindowApplication::GetClassId());


int WINAPI WinMain(HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR lp_cmd_line, int n_cmd_show)
{
	WindowApplication::Param param(h_instance, h_prev_instance, lp_cmd_line, n_cmd_show);
	app::ApplicationManager::Initialize();
	int end_code = app::ApplicationManager::GetInstance().Startup(param);
	app::ApplicationManager::Finalize();

	return end_code;
}
