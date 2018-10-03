//=========================================================
//include
#include "GraphicObject.h"


namespace gr {
//=========================================================
//初期化
bool GraphicObject::Initialize(const InitParamBase& init_param)
{
	return OnInitialize(init_param);
}


//=========================================================
//終了
void GraphicObject::Finalize()
{
	OnFinalize();
}


//=========================================================
//コマンド生成
GraphicObject::CommandPTr GraphicObject::CreateCommand()
{
	return OnCreateCommand();
}
} //namespace gr

