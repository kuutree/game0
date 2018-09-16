//=========================================================
//include
#include "IO.h"
#include "IOSystem.h"
#include "Path.h"
#include "../debug/Assert.h"
#include <io.h>
#include <fcntl.h>
#include <share.h>
#include <sys/stat.h>


namespace base {
namespace io {
//=========================================================
//ファイルを開く
bool IO::Open(const wchar_t* path, const OpenBitSet& open_mode)
{
	//========================================================
	//前提条件
	DB_ASSERT(path != nullptr);
	DB_ASSERT(open_mode.IsEnable(OPEN_READ)	   || open_mode.IsEnable(OPEN_WRITE));		//どちらかは指定しないといけない
	DB_ASSERT((!open_mode.IsEnable(OPEN_READ)) || (!open_mode.IsEnable(OPEN_WRITE)));	//両方は指定できない

	Close();

	//========================================================
	//ファイルオープン設定
	const int SHARE_MODE	  = _SH_DENYRW;				//ファイル操作中の共有設定
	const int PERMISSION_MODE = _S_IREAD | _S_IWRITE;	//作成したファイルの権限

	int flag = open_mode[OPEN_BINARY] ? _O_BINARY : _O_WTEXT;
	if		(open_mode[OPEN_READ])	flag |= _O_RDONLY;
	else if (open_mode[OPEN_WRITE]) flag |= BIT_OR(_O_WRONLY, BIT_OR(_O_CREAT, _O_TRUNC));
	
	//========================================================
	//書き込みを行う場合はディレクトリの存在を確認し作成する
	if (open_mode[OPEN_WRITE])
	{
		Path path_info(path);
		if (!IOSystem::GetInstance().DirectoryIsExist(path_info.dir.c_str()))
		{
			bool result = IOSystem::GetInstance().DirectoryCreate(path_info.dir.c_str());
			DB_ASSERT(result);
		}
	}

	//========================================================
	//ファイルオープン
	errno_t error  = _wsopen_s(&m_h_file, path, flag, SHARE_MODE, PERMISSION_MODE);
	bool    result = (error == 0);

	if (result)	m_open_mode = open_mode;
	else		m_h_file	= INVALID_HANDLE;

	return result;
}


//=========================================================
//ファイルを閉じる
void IO::Close()
{
	if (IsEnable())
	{
		_close(m_h_file);
		m_h_file	= INVALID_HANDLE;
		m_open_mode = 0;
	}
}


//=========================================================
//ファイル読み込み
bool IO::Read(void* p_buff, size_t size) const
{
	//========================================================
	//前提条件
	DB_ASSERT(p_buff != NULL);
	DB_ASSERT(size   >  0);
	DB_ASSERT(m_open_mode[OPEN_READ]);

	if (!IsEnable())  return false;

	return _read(m_h_file, p_buff, (unsigned int)size) != -1;
}


//=========================================================
//ファイル書き込み
bool IO::Write(const void* p_buff, size_t size) const
{
	//========================================================
	//前提条件
	DB_ASSERT(p_buff != NULL);
	DB_ASSERT(size   >  0);
	DB_ASSERT(m_open_mode[OPEN_WRITE]);

	if (!IsEnable())  return false;

	return _write(m_h_file, p_buff, (unsigned int)size) != -1;
}


//=========================================================
//シーク
bool IO::Seek(SeekPos pos, int offset) const
{
	if (!IsEnable())  return false;

	return _lseek(m_h_file, offset, pos) != -1;
}


//=========================================================
//ファイルサイズ取得
size_t IO::GetFileSize() const
{
	if (!IsEnable())  return false;

	int length = _filelength(m_h_file);
	return (length > 0) ? length : 0;
}


//=========================================================
//現在のファイル位置を取得
size_t IO::GetFilePos() const
{
	if (!IsEnable())  return false;

	int pos = _tell(m_h_file);
	return (pos > 0) ? pos : 0;
}
} //namespace io
} //namespace base

