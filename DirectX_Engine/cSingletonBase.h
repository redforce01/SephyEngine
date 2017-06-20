#pragma once


template<typename T>
class cSingletonBase
{
protected:
	static T*		s_pInstance;		//인스턴스 포인터

protected:
	cSingletonBase( void ) {};
	~cSingletonBase( void ) {};

public:

	//인스턴스 얻기 함수
	static T* GetInstance( void );

	//인스턴스 해제 함수
	static void ReleaseInstance( void );
};

//인스턴스 포인터 초기화
template<typename T>
T*		cSingletonBase<T>::s_pInstance = NULL;



//인스턴스 얻기 함수
template<typename T>
T* cSingletonBase<T>::GetInstance( void )
{
	if ( s_pInstance == NULL )
		s_pInstance = new T;

	return s_pInstance;
}

//인스턴스 해제 함수
template<typename T>
void cSingletonBase<T>::ReleaseInstance( void )
{
	if ( s_pInstance ) {
		delete s_pInstance;
		s_pInstance = NULL;
	}
}


