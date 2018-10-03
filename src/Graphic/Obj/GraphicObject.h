///////////////////////////////////////////////////////////
///グラフィックオブジェクト
///
///
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include
#include <memory>
#include <string>


//=========================================================
//前方宣言
struct ID3D11DeviceContext;


namespace gr {
///////////////////////////////////////////////////////////
///グラフィックオブジェクト
///
///
///////////////////////////////////////////////////////////
class GraphicObject
{
public:
	//*********************************************************
	//CommandBase
	//*********************************************************
	class CommandBase
	{
	public:
		//=========================================================
		//func
		virtual ~CommandBase() { /*何もしない*/ }
		bool Apply(ID3D11DeviceContext* pContext) { return OnApply(pContext); }
		//デバッグ
#ifdef _DEBUG
		std::wstring GetDebugName() { return OnGetDebugName(); }
#endif // _DEBUG
	protected:
		virtual bool OnApply(ID3D11DeviceContext* pContext) { return true; }
		//デバッグ
#ifdef _DEBUG
		virtual std::wstring OnGetDebugName() { return std::wstring(); }
#endif // _DEBUG
	};
	//*********************************************************
	//InitParamBase
	//*********************************************************
	struct InitParamBase
	{
		virtual ~InitParamBase() { /*何もしない*/ }
		template<class T> typename const T::InitParam& Cast() const { return static_cast<typename const T::InitParam&>(*this); }
	};
	//=========================================================
	//using
	using InitParam	 = InitParamBase;
	using Command	 = CommandBase;
	using CommandPTr = std::shared_ptr<CommandBase>;
public:
	//=========================================================
	//func
	virtual ~GraphicObject() { /*何もしない*/ }
	bool	   Initialize(const InitParamBase& init_param);	///< 初期化
	void	   Finalize();									///< 終了
	CommandPTr CreateCommand();								///< コマンド生成
protected:
	virtual bool	   OnInitialize(const InitParamBase& init_param) { return true;/*何もしない*/ }
	virtual void	   OnFinalize() { /*何もしない*/ }
	virtual CommandPTr OnCreateCommand() = 0;
};
} //namespace gr

