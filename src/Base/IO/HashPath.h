///////////////////////////////////////////////////////////
//ハッシュコードを持ったファイルパス
//
//
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include
#include "Path.h"
#include "../Util/Hash.h"
#include <string>
#include <algorithm>


namespace base {
namespace io {
///////////////////////////////////////////////////////////
//ハッシュコードを持ったファイルパス
//
//
///////////////////////////////////////////////////////////
class HashPath
{
	uint32_t	 m_hash_code;
	std::wstring m_path;
public:
	HashPath()						   { m_hash_code = 0; }
	HashPath(const std::wstring& path) { Initialize(path); }
	void Initialize(const std::wstring& path)
	{
		Path tmp(path.c_str());
		m_path = tmp.full_path;
		std::transform(m_path.begin(), m_path.end(), m_path.begin(), toupper);
		m_hash_code = base::util::FNV1Hash(m_path.c_str(), sizeof(wchar_t) * m_path.length());
	}
	const wchar_t* GetPath() const { return m_path.c_str(); }
	bool operator==(const HashPath& target) const { return _Cmp(target) == 0; }
	bool operator!=(const HashPath& target) const { return _Cmp(target) != 0; }
	bool operator< (const HashPath& target) const { return _Cmp(target) < 0; }
	bool operator> (const HashPath& target) const { return _Cmp(target) > 0; }
private:
	int _Cmp(const HashPath& target) const
	{
		if (m_hash_code != target.m_hash_code)	return (m_hash_code < target.m_hash_code) ? -1 : 1;
		return m_path.compare(target.m_path);
	}
};
} //namespace io
} //namespace base

