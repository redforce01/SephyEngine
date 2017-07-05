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
//	//���� ������ ��
//	_frameWidth = frameW;
//	int _frameNumWidth = totalW / _frameWidth;
//
//	//���� ������ ��
//	_frameHeight = frameH;
//	int _frameNumHeight = totalH / _frameHeight;
//
//	//�� ������ �� ���
//	_frameNum = _frameNumWidth * _frameNumHeight;
//
//	//������ ��ġ ����Ʈ ����
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
//			//������ ��ġ ����Ʈ�� �߰�
//			_frameList.push_back(framePos);
//		}
//	}
//
//	//�⺻ ���������� ����
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
//	//���� ���� ����
//	_loop = loop;
//
//	//�÷��� ����Ʈ Ŭ����
//	_playList.clear();
//
//	//�ٽ� �ǵ��ƿ��� �ִϸ��̼��̶��...
//	if (reverse)
//	{
//		//���� �ִϸ��̼��̶��...
//		if (_loop)
//		{
//			//���� ������ 
//			for (int i = 0; i < _frameNum; i++)
//			{
//				_playList.push_back(i);
//			}
//
//			//�� �� ������
//			for (int i = _frameNum - 2; i > 0; i--) //������ ������ ������ ���� �������� ������
//			{
//				_playList.push_back(i);
//			}
//		}
//		//������ �ƴϸ�...
//		else
//		{
//			//���� ������ �־�����
//			for (int i = 0; i < _frameNum; i++)
//			{
//				_playList.push_back(i);
//			}
//			//�� �� ������ �־�����
//			for (int i = _frameNum - 2; i >= 0; i--)
//			{
//				_playList.push_back(i);
//			}
//		}
//	}
//	//�ٽ� �ǵ��� ���� �ִϸ��̼��� �ƴϸ�...
//	else
//	{
//		//���� ������
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
//	//���� ���� ����
//	_loop = loop;
//
//	//�÷��� ����Ʈ Ŭ����
//	_playList.clear();
//
//	//�ٽ� �ǵ��ƿ��� �ִϸ��̼��̶��...
//	if ( reverse )
//	{
//		//���� �ִϸ��̼��̶��...
//		if ( _loop )
//		{
//			//���� ������ 
//			for ( int i = 0; i < _frameNum; i++ )
//			{
//				_playList.push_back( i );
//			}
//
//			//�� �� ������
//			for ( int i = _frameNum - 2; i > 0; i-- ) //������ ������ ������ ���� �������� ������
//			{
//				_playList.push_back( i );
//			}
//		}
//		//������ �ƴϸ�...
//		else
//		{
//			//���� ������ �־�����
//			for ( int i = 0; i < _frameNum; i++ )
//			{
//				_playList.push_back( i );
//			}
//			//�� �� ������ �־�����
//			for ( int i = _frameNum - 2; i >= 0; i-- )
//			{
//				_playList.push_back( i );
//			}
//		}
//	}
//	//�ٽ� �ǵ��� ���� �ִϸ��̼��� �ƴϸ�...
//	else
//	{
//		//���� ������
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
//	//���� ���� ����
//	_loop = loop;
//
//	//�÷��� ����Ʈ Ŭ����
//	_playList.clear();
//
//	//�ٽ� �ǵ��ƿ��� �ִϸ��̼��̶��...
//	if ( reverse )
//	{
//		//���� �ִϸ��̼��̶��...
//		if ( _loop )
//		{
//			//���� ������ 
//			for ( int i = 0; i < _frameNum; i++ )
//			{
//				_playList.push_back( i );
//			}
//
//			//�� �� ������
//			for ( int i = _frameNum - 2; i > 0; i-- ) //������ ������ ������ ���� �������� ������
//			{
//				_playList.push_back( i );
//			}
//		}
//		//������ �ƴϸ�...
//		else
//		{
//			//���� ������ �־�����
//			for ( int i = 0; i < _frameNum; i++ )
//			{
//				_playList.push_back( i );
//			}
//			//�� �� ������ �־�����
//			for ( int i = _frameNum - 2; i >= 0; i-- )
//			{
//				_playList.push_back( i );
//			}
//		}
//	}
//	//�ٽ� �ǵ��� ���� �ִϸ��̼��� �ƴϸ�...
//	else
//	{
//		//���� ������
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
//	//���� ���� ����
//	_loop = loop;
//
//	//�÷��� ����Ʈ Ŭ����
//	_playList.clear();
//
//	//�������ϰ� ���������� ����
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
//	//���� ���� ����
//	_loop = loop;
//
//	//�÷��� ����Ʈ Ŭ����
//	_playList.clear();
//
//	//�������ϰ� ���������� ����
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
//	//���� ���� ����
//	_loop = loop;
//
//	//�÷��� ����Ʈ Ŭ����
//	_playList.clear();
//
//	//�������ϰ� ���������� ����
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
//	//���� ���� ����
//	_loop = loop;
//
//	//�÷��� ����Ʈ Ŭ����
//	_playList.clear();
//
//	if (start == end)
//	{
//		//���� �����̰� ���������� ���� ���
//		_playList.clear();
//		stop();	//�ִϸ��̼� ������ �ʿ䰡 ����.
//		return;
//	}
//
//	//���� �������� ���� �����Ӻ��� Ŭ ���
//	if (start > end)
//	{
//		//�ٽ� �ǵ��� ���� �ִϸ��̼��̸�
//		if (reverse)
//		{
//			//���� �ִϸ��̼��̸�...
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
//		//�ٽ� �ǵ��� ���� �ִϸ��̼��̸�
//		if (reverse)
//		{
//			//���� �ִϸ��̼��̸�...
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
//	//���� ���� ����
//	_loop = loop;
//
//	//�÷��� ����Ʈ Ŭ����
//	_playList.clear();
//
//	if ( start == end )
//	{
//		//���� �����̰� ���������� ���� ���
//		_playList.clear();
//		stop();	//�ִϸ��̼� ������ �ʿ䰡 ����.
//		return;
//	}
//
//	//���� �������� ���� �����Ӻ��� Ŭ ���
//	if ( start > end )
//	{
//		//�ٽ� �ǵ��� ���� �ִϸ��̼��̸�
//		if ( reverse )
//		{
//			//���� �ִϸ��̼��̸�...
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
//		//�ٽ� �ǵ��� ���� �ִϸ��̼��̸�
//		if ( reverse )
//		{
//			//���� �ִϸ��̼��̸�...
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
//	//���� ���� ����
//	_loop = loop;
//
//	//�÷��� ����Ʈ Ŭ����
//	_playList.clear();
//
//	if ( start == end )
//	{
//		//���� �����̰� ���������� ���� ���
//		_playList.clear();
//		stop();	//�ִϸ��̼� ������ �ʿ䰡 ����.
//		return;
//	}
//
//	//���� �������� ���� �����Ӻ��� Ŭ ���
//	if ( start > end )
//	{
//		//�ٽ� �ǵ��� ���� �ִϸ��̼��̸�
//		if ( reverse )
//		{
//			//���� �ִϸ��̼��̸�...
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
//		//�ٽ� �ǵ��� ���� �ִϸ��̼��̸�
//		if ( reverse )
//		{
//			//���� �ִϸ��̼��̸�...
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
//		//������ ������Ʈ �ð��� �Ǿ��ٸ�...
//		if (_elapsedSec >= _frameUpdateSec)
//		{
//			_elapsedSec -= _frameUpdateSec;
//			_nowPlayIdx++;
//
//			if (_nowPlayIdx == _playList.size())
//			{
//				//���� �÷��̶��...
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