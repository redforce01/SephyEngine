#pragma once

#define RTTIInfo( ClassName )																\
private:																					\
	friend RTTI;																			\
	static const RTTI s_RTTI;																\
	virtual const RTTI* GetRTTI() const { return &s_RTTI; }									\
	typedef ClassName MyType;

#define DeclareRTTI( ClassName )															\
	RTTIInfo( ClassName )																	\
	typedef __super::MyType BaseType;

#define DeclareRootRTTI( ClassName )														\
	RTTIInfo( ClassName )																	\
	bool IsExactClass( const RTTI* pRTTI ) const { return GetRTTI() == pRTTI; }				\
	bool IsKindOf( const RTTI* pRTTI ) const												\
	{																						\
		const RTTI* pBase = GetRTTI();														\
		while( pBase != NULL )																\
		{																					\
			if( pBase == pRTTI )															\
			{																				\
				return true;																\
			}																				\
			pBase = pBase->GetBaseRTTI();													\
		}																					\
		return false;																		\
	}

#define ImplementRTTI( ClassName, BaseClassName ) const RTTI ClassName::s_RTTI( RTTI::GetRTTI<BaseClassName>() )
#define ImplementRootRTTI( ClassName ) const RTTI ClassName::s_RTTI( NULL )

class RTTI
{
public:
	template<typename T1, typename T2>
	static bool IsExactClass( const T2* pObj )
	{ return pObj != NULL ? pObj->IsExactClass( &T1::s_RTTI ) : false; }

	template<typename T>
	static bool IsExactClass( const RTTI* pRTTI, const T* pObj )
	{ return ( pRTTI != NULL && pObj != NULL ) ? pObj->IsExactClass( pRTTI ) : false; }

	template<typename T1, typename T2>
	static bool IsKindOf( const T2* pObj )
	{ return pObj != NULL ? pObj->IsKindOf( &T1::s_RTTI ) : false; }

	template<typename T>
	static bool IsKindOf( const RTTI* pRTTI, const T* pObj )
	{ return ( pRTTI != NULL && pObj != NULL ) ? pObj->IsKindOf( pRTTI ) : false; }

	template<typename T1, typename T2>
	static T1* DynamicCast( T2* pObj )
	{ return pObj != NULL ? ( pObj->IsKindOf( &T1::s_RTTI ) ? static_cast<T1*>( pObj ) : NULL ) : NULL; }

	template<typename T1, typename T2>
	static const T1* DynamicCast( const T2* pObj )
	{ return pObj != NULL ? ( pObj->IsKindOf( &T1::s_RTTI ) ? static_cast<const T1*>( pObj ) : NULL ) : NULL; }

	template<typename T>
	static unsigned int GetTypeID()
	{ return reinterpret_cast<unsigned int>( &T::s_RTTI ); }

	template<typename T>
	static unsigned int GetTypeID( const T* pObj )
	{ return pObj != NULL ? reinterpret_cast<unsigned int>( pObj->GetRTTI() ) : 0x00000000;	}

	template<typename T>
	static const RTTI* GetRTTI()
	{ return &T::s_RTTI; }

	template<typename T>
	static const RTTI* GetRTTI( const T* pObj )
	{ return pObj != NULL ? pObj->GetRTTI() : NULL; }

	template<typename Base, typename Derived>
	static const RTTI* GetOneStepDirectDescendant( const Derived* pObj )
	{
		BOOST_STATIC_ASSERT( ( !type_traits::is_same<Base, Derived>::value ) );
		BOOST_STATIC_ASSERT( ( type_traits::is_base_of<Base, Derived>::value ) );

		if( pObj == NULL )
		{
			return NULL;
		}

		const RTTI* pBaseRTTI = &Base::s_RTTI;
		const RTTI* pRTTI = &Derived::s_RTTI;
		while( pBaseRTTI != pRTTI->GetBaseRTTI() )
		{
			pRTTI = pRTTI->GetBaseRTTI();
		}
		
		return pRTTI;
	}

	template<typename Base>
	static const RTTI* GetOneStepDirectDescendant( const RTTI* pRTTI )
	{
		if( pRTTI == NULL )
		{
			return NULL;
		}

		const RTTI* pBaseRTTI = &Base::s_RTTI;
		if( pBaseRTTI == pRTTI )
		{
			return NULL;
		}

		while( pBaseRTTI != pRTTI->GetBaseRTTI() )
		{
			pRTTI = pRTTI->GetBaseRTTI();
			if( pRTTI == NULL )
			{
				return NULL;
			}
		}

		return pRTTI;
	}

	template<typename Base, typename Derived>
	struct one_step_direct_descendant
	{
		BOOST_STATIC_ASSERT( ( !type_traits::is_same<Base, Derived>::value ) );
		BOOST_STATIC_ASSERT( ( type_traits::is_base_of<Base, Derived>::value ) );

		template<bool, typename Base, typename Derived>
		struct helper
		{
			typedef typename one_step_direct_descendant<Base, typename Derived::BaseType>::type type;
		};

		template<typename Base, typename Derived>
		struct helper<true, Base, Derived>
		{
			typedef Derived type;
		};

		typedef typename helper<type_traits::is_same<Base, typename Derived::BaseType>::value, Base, Derived>::type type;
	};

public:
	RTTI( const RTTI* pBaseRTTI )
		: m_pBaseRTTI( pBaseRTTI )
	{

	}

	~RTTI()
	{

	}

	const RTTI* GetBaseRTTI() const
	{
		return m_pBaseRTTI;
	}

private:
	const RTTI* m_pBaseRTTI;
};