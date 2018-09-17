//=========================================================
//include
#include "Resource.h"
#include "IO.h"


namespace base {
namespace io {
//=========================================================
//コンストラクタ
Resource::Resource()
{
	m_state = STATE_NONE;
}


//=========================================================
//初期化
bool Resource::Initialize(const InitParamBase& init_param)
{
	Finalize();
	OnInitialize(init_param);

	IO io;
	if (!io.Open(init_param.path.GetPath(), IO::OPEN_READ | IO::OPEN_BINARY))	return false;

	size_t file_size = io.GetFileSize();
	m_file_buff.Resize(file_size);
	io.Read(m_file_buff.GetAddr(), file_size);
	io.Close();

	if (!OnLoadComplete())  return false;

	m_state = STATE_LOAD_COMPLETE;

	return true;
}


//=========================================================
//終了
void Resource::Finalize()
{
	m_state = STATE_NONE;
	OnFinalize();
	m_file_buff.Clear();
}


} //namespace io
} //namespace base

