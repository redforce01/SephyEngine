#pragma once


template<typename T>
class cSingletonBase
{
protected:
	static T*		s_pInstance;		//�ν��Ͻ� ������

protected:
	cSingletonBase( void ) {};
	~cSingletonBase( void ) {};

public:

	//�ν��Ͻ� ��� �Լ�
	static T* GetInstance( void );

	//�ν��Ͻ� ���� �Լ�
	static void ReleaseInstance( void );
};

//�ν��Ͻ� ������ �ʱ�ȭ
template<typename T>
T*		cSingletonBase<T>::s_pInstance = NULL;



//�ν��Ͻ� ��� �Լ�
template<typename T>
T* cSingletonBase<T>::GetInstance( void )
{
	if ( s_pInstance == NULL )
		s_pInstance = new T;

	return s_pInstance;
}

//�ν��Ͻ� ���� �Լ�
template<typename T>
void cSingletonBase<T>::ReleaseInstance( void )
{
	if ( s_pInstance ) {
		delete s_pInstance;
		s_pInstance = NULL;
	}
}


