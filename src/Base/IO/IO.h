#pragma once
//=================================================
//include
#include "../Util/Bit.h"
#include <stdio.h>


namespace base {
namespace io {
///////////////////////////////////////////////////////////
///ファイル入出力
///
///
///////////////////////////////////////////////////////////
class IO
{
public:
	//////////////////////////////////////////////////////////
	///ファイルオープンモード
	///
	///
	//////////////////////////////////////////////////////////
	enum OpenMode
	{
		OPEN_READ	= 1,		///< 読み込み用に開く
		OPEN_WRITE	= 1 << 1,	///< 書き込み用に開く
		OPEN_BINARY = 1 << 2,   ///< バイナリファイルとして開く
		OPEN_ALL	= OPEN_READ | OPEN_WRITE | OPEN_BINARY,
	};
	//////////////////////////////////////////////////////////
	///シーク位置
	///
	///読み込みと書き込みの両方を指定することは出来ない
	//////////////////////////////////////////////////////////
	enum SeekPos
	{
		SEEK_POS_TOP	 = SEEK_SET, ///< ファイルの先頭位置
		SEEK_POS_CURRENT = SEEK_CUR, ///< ファイルのカレント位置
		SEEK_POS_END	 = SEEK_END, ///< ファイルの終端位置
	};
	//========================================================
	//using
	using FileHandle = int;
	using OpenBitSet = base::util::Bit<OpenMode, OPEN_ALL>;
	//========================================================
	//const
	static const FileHandle INVALID_HANDLE = -1;
private:
	//========================================================
	//val
	FileHandle m_h_file;	///< ファイルハンドル  ファイル操作はすべてこのハンドルから行われる
	OpenBitSet m_open_mode;	///< ファイルオープンモード
public:
	//========================================================
	//func
	IO()  { m_h_file = INVALID_HANDLE; }							///< コンストラクタ
	~IO() { Close(); }												///< デストラクタ
	//========================================================
	//ファイル開閉
	bool Open(const wchar_t* path, const OpenBitSet& open_mode);	///< ファイルを開く
	void Close();													///< ファイルを閉じる
	//========================================================
	//ファイル操作
	bool Read(void* p_buff, size_t size) const;						///< ファイル読み込み
	bool Write(const void* p_buff, size_t size) const;				///< ファイル書き込み
	///-------------------------------------------------------
	///シーク
	///@param[in]  pos  シークの基準となる位置
	bool Seek(SeekPos pos, int offset) const;
	//========================================================
	//アクセサ
	size_t GetFileSize() const;										///< ファイルサイズ取得
	size_t GetFilePos() const;										///< 現在のファイル位置を取得
	bool   IsEnable() const { return m_h_file != INVALID_HANDLE; }	///ファイルが開いているか
};
} //namespace io
} //namespace base

