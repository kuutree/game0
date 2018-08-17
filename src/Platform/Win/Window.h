///////////////////////////////////////////////////////////
///ウインドウ
///
///
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include
#include "Type.h"
#include <base/mem/TreeNode.h>
#include <Windows.h>


namespace win {
//*********************************************************
//Window
//*********************************************************
class Window : public base::mem::TreeNode<Window>
{
public:
	//=========================================================
	//const
	static const RectInt SD_SIZE;
	static const RectInt HD_SIZE;
	static const RectInt FULL_HD_SIZE;
	//*********************************************************
	//CreateWindowParamBase
	//*********************************************************
	struct CreateWindowParamBase
	{
		NodePtr		parent_ptr;
		size_t		class_id   = GetClassId();
		ChildType	child_type = ChildType::CHILD_NONE;
		int			show_mode  = 0;
		RectInt		rect	   = FULL_HD_SIZE;
		std::wstring tag;

		virtual ~CreateWindowParamBase() { /*何もしない*/ }
		template<class T> const T& Cast() const { return static_cast<const T&>(*this); }
	};
	//*********************************************************
	//Controller
	//*********************************************************
	class Controller
	{
	public:
		virtual ~Controller() { /*何もしない*/ }
		virtual void OnClick(Window*) = 0;
	};
	//*********************************************************
	//Property
	//*********************************************************
	struct Property
	{
		Category category = Category::CATEGORY_NONE;
	};
	//=========================================================
	//using
	using CreateWindowParam = CreateWindowParamBase;
	using ControllerPtr	    = std::shared_ptr<Controller>;
protected:
	//*********************************************************
	//CreateWindowArg	ウインドウ作成関数の引数
	//*********************************************************
	struct CreateWindowArg
	{
		uint32_t		style = 0;
		uint32_t		ex_style = 0;
		const wchar_t*	class_name = nullptr;
		const wchar_t*	title_name = nullptr;
		RectInt			rect;
		HWND			h_parent    = nullptr;
		HMENU			h_menu		= nullptr;
		HINSTANCE		h_instance  = nullptr;
		void*			p_user_data = nullptr;
	};
private:
	//=========================================================
	//val
	HWND		 m_h_wndow;		///< ウインドウハンドル
	std::wstring m_tag;			///< 検索用ウインドウ名
	Property     m_property;	///< プロパティ
	ControllerPtr m_controller_ptr;
public:
	//=========================================================
	//func
	virtual ~Window();
	void Initialize(const CreateWindowParamBase& param);
	void Finalize();
	void Message(WORD word);
	void Show(ShowType show_type);	///< 表示設定変更

	HWND				GetHandle() const	{ return m_h_wndow; }
	const std::wstring& GetTag() const		{ return m_tag; }
	const Property&     GetProperty() const { return m_property; }
	ControllerPtr		GetControllerPtr()	{ return m_controller_ptr; }
	static size_t		GetClassId()		{ return WINDOW_NONE_ID; }
protected:
	//Window作成
	bool	 Create(const CreateWindowArg& param);
	uint32_t QueryStyleSettingChild(NodePtr parent_ptr, ChildType child_type) const;
	void	 Show(int show_type);
	void	 SetCategory(Category category) { m_property.category = category; }
	virtual void OnInitialize(const CreateWindowParamBase& param) {}
	virtual void OnFinalize();
	virtual void OnMessage(WORD word) {}
};
} //namespace win

