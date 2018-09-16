//=========================================================
//include
#include "Path.h"
#include "..\debug\Assert.h"
#include <stdlib.h>
#include <Windows.h>
#include <array>


namespace base {
namespace io {
//=========================================================
//ÉpÉXèÓïÒê›íË	
void Path::SetPath(const wchar_t* path)
{
	std::array< wchar_t, MAX_PATH > _full_path;
	std::array< wchar_t, MAX_PATH > _drive;
	std::array< wchar_t, MAX_PATH > _dir;
	std::array< wchar_t, MAX_PATH > _file;
	std::array< wchar_t, MAX_PATH > _ext;

	wchar_t* re_path = _wfullpath(&_full_path[0], path, _full_path.size());
	DB_ASSERT(re_path != nullptr);

	errno_t e = _wsplitpath_s(&_full_path[0],
							  &_drive[0], _drive.size(),
							  &_dir[0], _dir.size(),
							  &_file[0], _file.size(),
							  &_ext[0], _ext.size());

	DB_ASSERT(e == 0);

	full_path = &_full_path[0];
	dir		  = &_drive[0];
	dir		 += &_dir[0];
	file	  = &_file[0];
	ext		  = &_ext[0];
}
} //namespace io
} //namespace base

