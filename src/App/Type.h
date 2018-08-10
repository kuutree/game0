///////////////////////////////////////////////////////////
///
///
///
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include


namespace app {
//*********************************************************
//ApplicationId
//*********************************************************
enum ApplicationId : size_t
{
	APPLICATION_ID,
	WINDOW_APPLICATION_ID,
	APPLICATION_ID_MAX,
};


//*********************************************************
//ApplicationErrorCode
//*********************************************************
enum ApplicationErrorCode : int
{
	APPLICATION_SUCCESS = 0,
	APPLICATION_UNKNOWN_ERROR = 1,
};


//*********************************************************
//CreateApplicationParam
//*********************************************************
struct CreateApplicationParam
{
	size_t class_id;
	CreateApplicationParam() { class_id = static_cast<size_t>(-1); }
};
} //namespace app
