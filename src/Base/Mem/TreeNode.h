///////////////////////////////////////////////////////////
///ツリーのノード
///
///
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include
#include <base/debug/Assert.h>
#include <list>
#include <memory>


namespace base {
namespace mem {
//*********************************************************
//TreeNode
//*********************************************************
template<class T>
class TreeNode : public std::enable_shared_from_this<T>
{
public:
	//=========================================================
	//using
	using NodeType	  = T;
	using NodePtr	  = std::shared_ptr<NodeType>;
	using NodeWeakPtr = std::weak_ptr<NodeType>;
	using NodePtrList = std::list<NodePtr>;
private:
	//=========================================================
	//val
	NodeWeakPtr	m_parent_ptr;
	NodePtrList	m_child_ptr_list;
	//=========================================================
	//func
public:
	virtual ~TreeNode();

	//ノード操作
	void PushChild(NodePtr child_ptr);
	void PopChild(NodePtr child_ptr);
	template<class F> bool Foreach(F& func);

	//アクセサー
	NodePtr		 GetSelf()		   { return shared_from_this(); }
	NodeWeakPtr	 GetParent()	   { return m_parent_ptr; }
	NodePtrList& GetChildPtrList() { return m_child_ptr_list; }
protected:
	virtual void OnPushChild(NodePtr child_ptr) {}
	virtual void OnPopChild(NodePtr child_ptr)  {}
};


//=========================================================
//デストラクタ
template<class T>
TreeNode<T>::~TreeNode()
{
	DB_ASSERT(!m_parent_ptr.lock());
	DB_ASSERT(m_child_ptr_list.size() == 0);
}


//=========================================================
//子供追加
template<class T>
void TreeNode<T>::PushChild(NodePtr child_ptr)
{
	m_child_ptr_list.push_back(child_ptr);
	child_ptr->m_parent_ptr = GetSelf();

	OnPushChild(child_ptr);
}


//=========================================================
//子供取り出し
template<class T>
void TreeNode<T>::PopChild(NodePtr child_ptr)
{
	OnPopChild(child_ptr);

	NodePtrList::iterator ite = std::find(m_child_ptr_list.begin(), m_child_ptr_list.end(), child_ptr);
	if(ite != m_child_ptr_list.end())
	{
		(*ite)->m_parent_ptr.reset();
		ite = m_child_ptr_list.erase(ite);
	}
}


//=========================================================
//検索
template<typename T>
template <typename F>
bool TreeNode<T>::Foreach(F& func)
{	
	if (!func(static_cast<NodeType*>(this)))	return false;

	for (NodePtr child_ptr : m_child_ptr_list)
		if (!child_ptr->Foreach(func))
			return false;

	return true;
}
} //namespace mem
} //namespace base

