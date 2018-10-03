#include <Base/Mem/New.h>
#include <Platform/Win/WindowManager.h>
#include <App/ApplicationManager.h>
#include <App/ApplicationFactory.h>
#include <Platform/Win/Obj/WindowFrame.h>
#include <Graphic/GraphicManager.h>
#include <Graphic/Obj/Shader/VertexShader.h>
#include <Graphic/Obj/Shader/PixelShader.h>
#include <Graphic/Obj/Vertex/VertexBuffer.h>
#include <Base/IO/IOSystem.h>
#include <Base/IO/ResourceManager.h>



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

	gr::shader::VertexShader m_vs;
	gr::shader::PixelShader m_ps;
	gr::vertex::VertexBuffer m_vb;

	static size_t GetClassId() { return app::WINDOW_APPLICATION_ID; }
protected:
	virtual void OnInitialize(const app::CreateApplicationParam& param)
	{
		const Param& _param = static_cast<const Param&>(param);
		base::io::IOSystem::Initialize();
		base::io::ResourceManager::Initialize();
		win::WindowManager::Initialize();
		win::WindowManager::GetInstance().Register(_param.h_instance, _param.h_prev_instance, _param.lp_cmd_line, _param.n_cmd_show);
		
		gr::GraphicManager::Initialize();

		win::Window::NodePtr ptr;
		{
			win::WindowFrame::CreateWindowParam create_param;
			create_param.class_name = L"ABC";
			create_param.title_name = L"ABC";
			create_param.rect = win::Window::SD_SIZE;
			create_param.rect.ShiftX(win::Window::FULL_HD_SIZE.right / 4);
			create_param.rect.ShiftY(win::Window::FULL_HD_SIZE.bottom / 4);
			create_param.is_caption = true;
			create_param.is_close = true;
			ptr = win::WindowManager::GetInstance().CreateWindowObject(create_param);
		}

		gr::GraphicManager::CreateDeviceParam device_param;
		device_param.window_ptr = ptr;

		gr::GraphicManager::GetInstance().CreateDevice(device_param);

		{

			gr::shader::VertexShader::InitParam vs_init;
			gr::shader::PixelShader::InitParam ps_init;
			gr::vertex::VertexBuffer::InitParam vb_init;

			vs_init.resource_param.path.Initialize(L"Resource/vs.o");
			ps_init.resource_param.path.Initialize(L"Resource/ps.o");
			vb_init.resource_param.path.Initialize(L"Resource/vb.v");
			m_vs.Initialize(vs_init);
			m_ps.Initialize(ps_init);
			m_vb.Initialize(vb_init);
		}

		base::io::ResourceManager::GetInstance().Reflesh();
	}
	virtual int OnFinalize()
	{
		m_vs.Finalize();
		m_ps.Finalize();
		m_vb.Finalize();

		gr::GraphicManager::Finalize();
		win::WindowManager::Finalize();
		base::io::ResourceManager::Finalize();
		base::io::IOSystem::Finalize();
		return app::APPLICATION_SUCCESS;
	}
	virtual int OnRun()
	{
		while (win::WindowManager::GetInstance().MessageProcess())
		{
			gr::GraphicManager::GetInstance().BeginRender();

			//m_ps.CreateCommand()->Apply(gr::GraphicManager::GetInstance().GetContext().Get());

			gr::GraphicManager::GetInstance().EndRender();
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
