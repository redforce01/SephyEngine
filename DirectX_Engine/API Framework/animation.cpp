#include "stdafx.h"
//#include "animation.h"
//
//
//animation::animation()
//	: _frameNum(0)
//	, _frameWidth(0)
//	, _frameHeight(0)
//	, _loop(FALSE)
//	, _frameUpdateSec(0)
//	, _elapsedSec(0)
//	, _nowPlayIdx(0)
//	, _play(FALSE)
//{
//}
//
//
//animation::~animation()
//{
//}
//
//HRESULT animation::init(int totalW, int totalH, int frameW, int frameH)
//{
//	//가로 프레임 수
//	_frameWidth = frameW;
//	int _frameNumWidth = totalW / _frameWidth;
//
//	//세로 프레임 수
//	_frameHeight = frameH;
//	int _frameNumHeight = totalH / _frameHeight;
//
//	//총 프레임 수 계산
//	_frameNum = _frameNumWidth * _frameNumHeight;
//
//	//프레임 위치 리스트 셋팅
//	_frameList.clear();
//
//	for (int i = 0; i < _frameNumHeight; i++)
//	{
//		for (int j = 0; j < _frameNumWidth; j++)
//		{
//			POINT framePos;
//			framePos.x = j * _frameWidth;
//			framePos.y = i * _frameHeight;
//
//			//프레임 위치 리스트에 추가
//			_frameList.push_back(framePos);
//		}
//	}
//
//	//기본 프레임으로 셋팅
//	setDefPlayFrame();
//
//	return S_OK;
//}
//
//void animation::setDefPlayFrame(BOOL reverse /*= FALSE*/, BOOL loop /*= FALSE*/)
//{
//	_obj = NULL;
//	_callbackFunction = NULL;
//	_callbackFunctionParameter = NULL;
//
//	//루프 여부 대입
//	_loop = loop;
//
//	//플레이 리스트 클리어
//	_playList.clear();
//
//	//다시 되돌아오는 애니메이션이라면...
//	if (reverse)
//	{
//		//루프 애니메이션이라면...
//		if (_loop)
//		{
//			//갈때 프레임 
//			for (int i = 0; i < _frameNum; i++)
//			{
//				_playList.push_back(i);
//			}
//
//			//올 때 프레임
//			for (int i = _frameNum - 2; i > 0; i--) //루프기 때문에 마지막 시작 프레임은 빠진다
//			{
//				_playList.push_back(i);
//			}
//		}
//		//루프가 아니면...
//		else
//		{
//			//갈때 프레임 넣어주자
//			for (int i = 0; i < _frameNum; i++)
//			{
//				_playList.push_back(i);
//			}
//			//올 때 프레임 넣어주자
//			for (int i = _frameNum - 2; i >= 0; i--)
//			{
//				_playList.push_back(i);
//			}
//		}
//	}
//	//다시 되돌아 오는 애니메이션이 아니면...
//	else
//	{
//		//갈때 프레임
//		for (int i = 0; i < _frameNum; i++)
//		{
//			_playList.push_back(i);
//		}
//	}
//}
//
//void animation::setDefPlayFrame( BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction )
//{
//	_obj = NULL;
//	_callbackFunction = cbFunction;
//	_callbackFunctionParameter = NULL;
//
//	//루프 여부 대입
//	_loop = loop;
//
//	//플레이 리스트 클리어
//	_playList.clear();
//
//	//다시 되돌아오는 애니메이션이라면...
//	if ( reverse )
//	{
//		//루프 애니메이션이라면...
//		if ( _loop )
//		{
//			//갈때 프레임 
//			for ( int i = 0; i < _frameNum; i++ )
//			{
//				_playList.push_back( i );
//			}
//
//			//올 때 프레임
//			for ( int i = _frameNum - 2; i > 0; i-- ) //루프기 때문에 마지막 시작 프레임은 빠진다
//			{
//				_playList.push_back( i );
//			}
//		}
//		//루프가 아니면...
//		else
//		{
//			//갈때 프레임 넣어주자
//			for ( int i = 0; i < _frameNum; i++ )
//			{
//				_playList.push_back( i );
//			}
//			//올 때 프레임 넣어주자
//			for ( int i = _frameNum - 2; i >= 0; i-- )
//			{
//				_playList.push_back( i );
//			}
//		}
//	}
//	//다시 되돌아 오는 애니메이션이 아니면...
//	else
//	{
//		//갈때 프레임
//		for ( int i = 0; i < _frameNum; i++ )
//		{
//			_playList.push_back( i );
//		}
//	}
//}
//
//void animation::setDefPlayFrame( BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void * obj )
//{
//	_obj = obj;
//	_callbackFunction = NULL;
//	_callbackFunctionParameter = cbFunction;
//
//	//루프 여부 대입
//	_loop = loop;
//
//	//플레이 리스트 클리어
//	_playList.clear();
//
//	//다시 되돌아오는 애니메이션이라면...
//	if ( reverse )
//	{
//		//루프 애니메이션이라면...
//		if ( _loop )
//		{
//			//갈때 프레임 
//			for ( int i = 0; i < _frameNum; i++ )
//			{
//				_playList.push_back( i );
//			}
//
//			//올 때 프레임
//			for ( int i = _frameNum - 2; i > 0; i-- ) //루프기 때문에 마지막 시작 프레임은 빠진다
//			{
//				_playList.push_back( i );
//			}
//		}
//		//루프가 아니면...
//		else
//		{
//			//갈때 프레임 넣어주자
//			for ( int i = 0; i < _frameNum; i++ )
//			{
//				_playList.push_back( i );
//			}
//			//올 때 프레임 넣어주자
//			for ( int i = _frameNum - 2; i >= 0; i-- )
//			{
//				_playList.push_back( i );
//			}
//		}
//	}
//	//다시 되돌아 오는 애니메이션이 아니면...
//	else
//	{
//		//갈때 프레임
//		for ( int i = 0; i < _frameNum; i++ )
//		{
//			_playList.push_back( i );
//		}
//	}
//}
//
//void animation::setPlayFrame(int* playArr, int arrLen, BOOL loop /*= FALSE*/)
//{
//	_obj = NULL;
//	_callbackFunction = NULL;
//	_callbackFunctionParameter = NULL;
//
//	//루프 여부 대입
//	_loop = loop;
//
//	//플레이 리스트 클리어
//	_playList.clear();
//
//	//ㅣ정직하게 프레임으로 셋팅
//	for (int i = 0; i < arrLen; i++)
//	{
//		_playList.push_back(playArr[i]);
//	}
//}
//
//void animation::setPlayFrame( int * playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION cbFunction )
//{
//	_obj = NULL;
//	_callbackFunction = cbFunction;
//	_callbackFunctionParameter = NULL;
//
//	//루프 여부 대입
//	_loop = loop;
//
//	//플레이 리스트 클리어
//	_playList.clear();
//
//	//ㅣ정직하게 프레임으로 셋팅
//	for ( int i = 0; i < arrLen; i++ )
//	{
//		_playList.push_back( playArr[i] );
//	}
//}
//
//void animation::setPlayFrame( int * playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void * obj )
//{
//	_obj = obj;
//	_callbackFunction = NULL;
//	_callbackFunctionParameter = cbFunction;
//
//	//루프 여부 대입
//	_loop = loop;
//
//	//플레이 리스트 클리어
//	_playList.clear();
//
//	//ㅣ정직하게 프레임으로 셋팅
//	for ( int i = 0; i < arrLen; i++ )
//	{
//		_playList.push_back( playArr[i] );
//	}
//}
//
//void animation::setPlayFrame(int start, int end, BOOL reverse /*= FALSE*/, BOOL loop /*= FALSE*/)
//{
//	_obj = NULL;
//	_callbackFunction = NULL;
//	_callbackFunctionParameter = NULL;
//
//	//루프 여부 대입
//	_loop = loop;
//
//	//플레이 리스트 클리어
//	_playList.clear();
//
//	if (start == end)
//	{
//		//시작 프렝미과 끝프레임이 같은 경우
//		_playList.clear();
//		stop();	//애니메이션 실행할 필요가 없다.
//		return;
//	}
//
//	//시작 프레임이 종료 프레임보다 클 경우
//	if (start > end)
//	{
//		//다시 되돌아 오는 애니메이션이면
//		if (reverse)
//		{
//			//루프 애니메이션이면...
//			if (_loop)
//			{
//				for (int i = start; i >= end; i--)
//				{
//					_playList.push_back(i);
//				}
//
//				for (int i = end + 1; i < start; i++)
//				{
//					_playList.push_back(i);
//				}
//			}
//			else
//			{
//				for (int i = start; i >= end; i--)
//				{
//					_playList.push_back(i);
//				}
//
//				for (int i = end + 1; i <= start; i++)
//				{
//					_playList.push_back(i);
//				}
//			}
//		}
//		else
//		{
//			for (int i = start; i >= end; i--)
//			{
//				_playList.push_back(i);
//			}
//		}
//	}
//	else //end > start
//	{
//		//다시 되돌아 오는 애니메이션이면
//		if (reverse)
//		{
//			//루프 애니메이션이면...
//			if (_loop)
//			{
//				for (int i = start; i <= end; i++)
//				{
//					_playList.push_back(i);
//				}
//
//				for (int i = end - 1; i > start; i--)
//				{
//					_playList.push_back(i);
//				}
//			}
//			else
//			{
//				for (int i = start; i <= end; i++)
//				{
//					_playList.push_back(i);
//				}
//
//				for (int i = end - 1; i >= start; i--)
//				{
//					_playList.push_back(i);
//				}
//			}
//		}
//		else
//		{
//			for (int i = start; i <= end; i++)
//			{
//				_playList.push_back(i);
//			}
//		}
//	}
//}
//
//void animation::setPlayFrame( int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction )
//{
//	_obj = NULL;
//	_callbackFunction = cbFunction;
//	_callbackFunctionParameter = NULL;
//
//	//루프 여부 대입
//	_loop = loop;
//
//	//플레이 리스트 클리어
//	_playList.clear();
//
//	if ( start == end )
//	{
//		//시작 프렝미과 끝프레임이 같은 경우
//		_playList.clear();
//		stop();	//애니메이션 실행할 필요가 없다.
//		return;
//	}
//
//	//시작 프레임이 종료 프레임보다 클 경우
//	if ( start > end )
//	{
//		//다시 되돌아 오는 애니메이션이면
//		if ( reverse )
//		{
//			//루프 애니메이션이면...
//			if ( _loop )
//			{
//				for ( int i = start; i >= end; i-- )
//				{
//					_playList.push_back( i );
//				}
//
//				for ( int i = end + 1; i < start; i++ )
//				{
//					_playList.push_back( i );
//				}
//			}
//			else
//			{
//				for ( int i = start; i >= end; i-- )
//				{
//					_playList.push_back( i );
//				}
//
//				for ( int i = end + 1; i <= start; i++ )
//				{
//					_playList.push_back( i );
//				}
//			}
//		}
//		else
//		{
//			for ( int i = start; i >= end; i-- )
//			{
//				_playList.push_back( i );
//			}
//		}
//	}
//	else //end > start
//	{
//		//다시 되돌아 오는 애니메이션이면
//		if ( reverse )
//		{
//			//루프 애니메이션이면...
//			if ( _loop )
//			{
//				for ( int i = start; i <= end; i++ )
//				{
//					_playList.push_back( i );
//				}
//
//				for ( int i = end - 1; i > start; i-- )
//				{
//					_playList.push_back( i );
//				}
//			}
//			else
//			{
//				for ( int i = start; i <= end; i++ )
//				{
//					_playList.push_back( i );
//				}
//
//				for ( int i = end - 1; i >= start; i-- )
//				{
//					_playList.push_back( i );
//				}
//			}
//		}
//		else
//		{
//			for ( int i = start; i <= end; i++ )
//			{
//				_playList.push_back( i );
//			}
//		}
//	}
//}
//
//void animation::setPlayFrame( int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void * obj )
//{
//	_obj = obj;
//	_callbackFunction = NULL;
//	_callbackFunctionParameter = cbFunction;
//
//	//루프 여부 대입
//	_loop = loop;
//
//	//플레이 리스트 클리어
//	_playList.clear();
//
//	if ( start == end )
//	{
//		//시작 프렝미과 끝프레임이 같은 경우
//		_playList.clear();
//		stop();	//애니메이션 실행할 필요가 없다.
//		return;
//	}
//
//	//시작 프레임이 종료 프레임보다 클 경우
//	if ( start > end )
//	{
//		//다시 되돌아 오는 애니메이션이면
//		if ( reverse )
//		{
//			//루프 애니메이션이면...
//			if ( _loop )
//			{
//				for ( int i = start; i >= end; i-- )
//				{
//					_playList.push_back( i );
//				}
//
//				for ( int i = end + 1; i < start; i++ )
//				{
//					_playList.push_back( i );
//				}
//			}
//			else
//			{
//				for ( int i = start; i >= end; i-- )
//				{
//					_playList.push_back( i );
//				}
//
//				for ( int i = end + 1; i <= start; i++ )
//				{
//					_playList.push_back( i );
//				}
//			}
//		}
//		else
//		{
//			for ( int i = start; i >= end; i-- )
//			{
//				_playList.push_back( i );
//			}
//		}
//	}
//	else //end > start
//	{
//		//다시 되돌아 오는 애니메이션이면
//		if ( reverse )
//		{
//			//루프 애니메이션이면...
//			if ( _loop )
//			{
//				for ( int i = start; i <= end; i++ )
//				{
//					_playList.push_back( i );
//				}
//
//				for ( int i = end - 1; i > start; i-- )
//				{
//					_playList.push_back( i );
//				}
//			}
//			else
//			{
//				for ( int i = start; i <= end; i++ )
//				{
//					_playList.push_back( i );
//				}
//
//				for ( int i = end - 1; i >= start; i-- )
//				{
//					_playList.push_back( i );
//				}
//			}
//		}
//		else
//		{
//			for ( int i = start; i <= end; i++ )
//			{
//				_playList.push_back( i );
//			}
//		}
//	}
//}
//
//void animation::setFPS(int framePerSec)
//{
//	_frameUpdateSec = 1.0f / framePerSec;
//}
//
//void animation::frameUpdate(float elapsedTime)
//{
//	if (_play)
//	{
//		_elapsedSec += elapsedTime;
//
//		//프레임 업데이트 시간이 되었다면...
//		if (_elapsedSec >= _frameUpdateSec)
//		{
//			_elapsedSec -= _frameUpdateSec;
//			_nowPlayIdx++;
//
//			if (_nowPlayIdx == _playList.size())
//			{
//				//루프 플레이라면...
//				if (_loop)
//				{
//					_nowPlayIdx = 0;
//				}
//				else
//				{
//					_nowPlayIdx--;
//					_play = FALSE;
//
//					if ( _obj == NULL )
//					{
//						if ( _callbackFunction != NULL )
//						{
//							_callbackFunction();
//						}
//					}
//					else
//					{
//						_callbackFunctionParameter( _obj );
//					}
//				}
//			}
//		}
//	}
//}
//
//void animation::start()
//{
//	_play = TRUE;
//	_nowPlayIdx = 0;
//}
//
//void animation::stop()
//{
//	_play = FALSE;
//	_nowPlayIdx = 0;
//}
//
//void animation::pause()
//{
//	_play = FALSE;
//}
//
//void animation::resume()
//{
//	_play = TRUE;
//}