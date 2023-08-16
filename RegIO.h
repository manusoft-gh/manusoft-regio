// Copyright 2008 ManuSoft
// https://www.manusoft.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef _REGIO_H_
#define _REGIO_H_

#include <Windows.h>
#include <TChar.h>


bool RegRemoveKey( class RegKeyA& rkTarget, bool bRemoveEmptyParents = false );
bool RegRemoveKey( class RegKeyW& rkTarget, bool bRemoveEmptyParents = false );
bool RegCopyKey( class RegKeyA& rkSource, HKEY rkTargetRoot, LPCSTR pszTarget );
bool RegCopyKey( class RegKeyW& rkSource, HKEY rkTargetRoot, LPCWSTR pwszTarget );


class RegKeyA
{
	HKEY m_hkRoot;
	HKEY m_hkThis;
	REGSAM m_samAccess;
	LPSTR m_pszKey;
public:
	RegKeyA( LPCSTR pszKey, HKEY hkRoot, bool bCreate = false, REGSAM samAccess = KEY_ALL_ACCESS );
	RegKeyA( LPCSTR pszKey, RegKeyA& kRoot, bool bCreate = false, REGSAM samAccess = 0 );
	RegKeyA( RegKeyA& Source );
	virtual ~RegKeyA();
	virtual void Close();
	virtual bool IsWritable() const { return (m_hkRoot && (m_samAccess & KEY_WRITE) == KEY_WRITE); }
	virtual LPCSTR GetString( LPCSTR pszName ) const;
	virtual DWORD GetDword( LPCSTR pszName ) const;
	virtual const BYTE* GetBytes( LPCSTR pszName, DWORD& cbData ) const;
	virtual bool SetValue( LPCSTR pszName, LPCSTR pszValue );
	virtual bool SetValue( LPCSTR pszName, DWORD dwValue );
	virtual bool SetValue( LPCSTR pszName, const BYTE* pbData, DWORD cbData );
	virtual bool RemoveValue( LPCSTR pszName );
	virtual DWORD ValueType( LPCSTR pszName ) const;
	virtual DWORD ValueType( LPCSTR pszName, DWORD& dwSize ) const;
	virtual bool HasValue( LPCSTR pszName ) const { return (ValueType( pszName ) != REG_NONE); }
	operator HKEY () const { return m_hkThis; }
	LPCSTR Key() const { return m_pszKey; }
	HKEY Root() const { return m_hkRoot; }
protected:
	virtual HKEY InnerOpen( LPCSTR pszKey, HKEY hkRoot, bool bCreate = false, REGSAM samAccess = KEY_ALL_ACCESS );
};

class RegKeyW
{
	HKEY m_hkRoot;
	HKEY m_hkThis;
	REGSAM m_samAccess;
	LPWSTR m_pszKey;
public:
	RegKeyW( LPCWSTR pszKey, HKEY hkRoot, bool bCreate = false, REGSAM samAccess = KEY_ALL_ACCESS );
	RegKeyW( LPCWSTR pszKey, RegKeyW& kRoot, bool bCreate = false, REGSAM samAccess = 0 );
	RegKeyW( RegKeyW& Source );
	virtual ~RegKeyW();
	virtual void Close();
	virtual bool IsWritable() const { return (m_hkRoot && (m_samAccess & KEY_WRITE) == KEY_WRITE); }
	virtual LPCWSTR GetString( LPCWSTR pszName ) const;
	virtual DWORD GetDword( LPCWSTR pszName ) const;
	virtual const BYTE* GetBytes( LPCWSTR pszName, DWORD& cbData ) const;
	virtual bool SetValue( LPCWSTR pszName, LPCWSTR pszValue );
	virtual bool SetValue( LPCWSTR pszName, DWORD dwValue );
	virtual bool SetValue( LPCWSTR pszName, const BYTE* pbData, DWORD cbData );
	virtual bool RemoveValue( LPCWSTR pszName );
	virtual DWORD ValueType( LPCWSTR pszName ) const;
	virtual DWORD ValueType( LPCWSTR pszName, DWORD& dwSize ) const;
	virtual bool HasValue( LPCWSTR pszName ) const { return (ValueType( pszName ) != REG_NONE); }
	operator HKEY () const { return m_hkThis; }
	LPCWSTR Key() const { return m_pszKey; }
	HKEY Root() const { return m_hkRoot; }
protected:
	virtual HKEY InnerOpen( LPCWSTR pszKey, HKEY hkRoot, bool bCreate = false, REGSAM samAccess = KEY_ALL_ACCESS );
};


class RegKeyPriorityA : public RegKeyA
{
	RegKeyA m_rkSecondary;
public:
	RegKeyPriorityA( LPCSTR pszKey, HKEY hkRoot1, HKEY hkRoot2, bool bCreate = false, REGSAM samAccess = KEY_ALL_ACCESS );
	RegKeyPriorityA( LPCSTR pszKey, RegKeyPriorityA& hkParent, bool bCreate = false, REGSAM samAccess = KEY_ALL_ACCESS );
	virtual ~RegKeyPriorityA() {}
	virtual LPCSTR GetString( LPCSTR pszName ) const;
	virtual DWORD GetDword( LPCSTR pszName ) const;
	virtual const BYTE* GetBytes( LPCSTR pszName, DWORD& cbData ) const;
	virtual bool RemoveValue( LPCSTR pszName );
	virtual DWORD ValueType( LPCSTR pszName ) const;
	virtual DWORD ValueType( LPCSTR pszName, DWORD& dwSize ) const;
	RegKeyA& SecondaryRegKey() { return m_rkSecondary; }
};

class RegKeyPriorityW : public RegKeyW
{
	RegKeyW m_rkSecondary;
public:
	RegKeyPriorityW( LPCWSTR pszKey, HKEY hkRoot1, HKEY hkRoot2, bool bCreate = false, REGSAM samAccess = KEY_ALL_ACCESS );
	RegKeyPriorityW( LPCWSTR pszKey, RegKeyPriorityW& hkParent, bool bCreate = false, REGSAM samAccess = KEY_ALL_ACCESS );
	virtual ~RegKeyPriorityW() {}
	virtual LPCWSTR GetString( LPCWSTR pszName ) const;
	virtual DWORD GetDword( LPCWSTR pszName ) const;
	virtual const BYTE* GetBytes( LPCWSTR pszName, DWORD& cbData ) const;
	virtual bool RemoveValue( LPCWSTR pszName );
	virtual DWORD ValueType( LPCWSTR pszName ) const;
	virtual DWORD ValueType( LPCWSTR pszName, DWORD& dwSize ) const;
	RegKeyW& SecondaryRegKey() { return m_rkSecondary; }
};


class RegKeyCULMA : public RegKeyPriorityA
{
public:
	RegKeyCULMA( LPCSTR pszKey, bool bCreate = false, REGSAM samAccess = KEY_ALL_ACCESS )
	: RegKeyPriorityA( pszKey, HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE, bCreate, samAccess )
	{}
};

class RegKeyCULMW : public RegKeyPriorityW
{
public:
	RegKeyCULMW( LPCWSTR pszKey, bool bCreate = false, REGSAM samAccess = KEY_ALL_ACCESS )
	: RegKeyPriorityW( pszKey, HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE, bCreate, samAccess )
	{}
};


class RegKeyLMCUA : public RegKeyPriorityA
{
public:
	RegKeyLMCUA( LPCSTR pszKey, bool bCreate = false, REGSAM samAccess = KEY_ALL_ACCESS )
	: RegKeyPriorityA( pszKey, HKEY_LOCAL_MACHINE, HKEY_CURRENT_USER, bCreate, samAccess )
	{}
};

class RegKeyLMCUW : public RegKeyPriorityW
{
public:
	RegKeyLMCUW( LPCWSTR pszKey, bool bCreate = false, REGSAM samAccess = KEY_ALL_ACCESS )
	: RegKeyPriorityW( pszKey, HKEY_LOCAL_MACHINE, HKEY_CURRENT_USER, bCreate, samAccess )
	{}
};


class RegKeyReadOnlyA : public RegKeyA
{
public:
	RegKeyReadOnlyA( LPCSTR pszKey, HKEY hkRoot, bool bCreate = false, REGSAM samAccess = KEY_READ )
	: RegKeyA( pszKey, hkRoot, bCreate, (samAccess & ~KEY_ALL_ACCESS) | KEY_READ )
	{}
	virtual bool IsWritable() const { return false; }
private: //make write functions private to trigger compiler error when used
	virtual bool SetValue( LPCSTR pszName, LPCSTR pszValue ) { return false; }
	virtual bool SetValue( LPCSTR pszName, DWORD dwValue ) { return false; }
	virtual bool SetValue( LPCSTR pszName, const BYTE* pbData, DWORD cbData ) { return false; }
	virtual bool RemoveValue( LPCSTR pszName ) { return false; }
};

class RegKeyReadOnlyW : public RegKeyW
{
public:
	RegKeyReadOnlyW( LPCWSTR pszKey, HKEY hkRoot, bool bCreate = false, REGSAM samAccess = KEY_READ )
	: RegKeyW( pszKey, hkRoot, bCreate, (samAccess & ~KEY_ALL_ACCESS) | KEY_READ )
	{}
	virtual bool IsWritable() const { return false; }
private: //make write functions private to trigger compiler error when used
	virtual bool SetValue( LPCWSTR pszName, LPCWSTR pszValue ) { return false; }
	virtual bool SetValue( LPCWSTR pszName, DWORD dwValue ) { return false; }
	virtual bool SetValue( LPCWSTR pszName, const BYTE* pbData, DWORD cbData ) { return false; }
	virtual bool RemoveValue( LPCWSTR pszName ) { return false; }
};


class RegKeyLMA : public RegKeyA
{
public:
	RegKeyLMA( LPCSTR pszKey, bool bCreate = false, REGSAM samAccess = KEY_ALL_ACCESS )
	: RegKeyA( pszKey, HKEY_LOCAL_MACHINE, bCreate, samAccess )
	{}
};

class RegKeyLMW : public RegKeyW
{
public:
	RegKeyLMW( LPCWSTR pszKey, bool bCreate = false, REGSAM samAccess = KEY_ALL_ACCESS )
	: RegKeyW( pszKey, HKEY_LOCAL_MACHINE, bCreate, samAccess )
	{}
};


class RegKeyCUA : public RegKeyA
{
public:
	RegKeyCUA( LPCSTR pszKey, bool bCreate = false, REGSAM samAccess = KEY_ALL_ACCESS )
	: RegKeyA( pszKey, HKEY_CURRENT_USER, bCreate, samAccess )
	{}
};

class RegKeyCUW : public RegKeyW
{
public:
	RegKeyCUW( LPCWSTR pszKey, bool bCreate = false, REGSAM samAccess = KEY_ALL_ACCESS )
	: RegKeyW( pszKey, HKEY_CURRENT_USER, bCreate, samAccess )
	{}
};


class RegKeyLMReadOnlyA : public RegKeyReadOnlyA
{
public:
	RegKeyLMReadOnlyA( LPCSTR pszKey, bool bCreate = false, REGSAM samAccess = KEY_READ )
	: RegKeyReadOnlyA( pszKey, HKEY_LOCAL_MACHINE, bCreate, (samAccess & ~KEY_ALL_ACCESS) | KEY_READ )
	{}
};

class RegKeyLMReadOnlyW : public RegKeyReadOnlyW
{
public:
	RegKeyLMReadOnlyW( LPCWSTR pszKey, bool bCreate = false, REGSAM samAccess = KEY_READ )
	: RegKeyReadOnlyW( pszKey, HKEY_LOCAL_MACHINE, bCreate, (samAccess & ~KEY_ALL_ACCESS) | KEY_READ )
	{}
};


class RegKeyCUReadOnlyA : public RegKeyReadOnlyA
{
public:
	RegKeyCUReadOnlyA( LPCSTR pszKey, bool bCreate = false, REGSAM samAccess = KEY_READ )
	: RegKeyReadOnlyA( pszKey, HKEY_CURRENT_USER, bCreate, (samAccess & ~KEY_ALL_ACCESS) | KEY_READ )
	{}
};

class RegKeyCUReadOnlyW : public RegKeyReadOnlyW
{
public:
	RegKeyCUReadOnlyW( LPCWSTR pszKey, bool bCreate = false, REGSAM samAccess = KEY_READ )
	: RegKeyReadOnlyW( pszKey, HKEY_CURRENT_USER, bCreate, (samAccess & ~KEY_ALL_ACCESS) | KEY_READ )
	{}
};


#ifdef UNICODE
typedef RegKeyW RegKey;
typedef RegKeyPriorityW RegKeyPriority;
typedef RegKeyCULMW RegKeyCULM;
typedef RegKeyReadOnlyW RegKeyReadOnly;
typedef RegKeyLMW RegKeyLM;
typedef RegKeyCUW RegKeyCU;
typedef RegKeyLMReadOnlyW RegKeyLMReadOnly;
typedef RegKeyCUReadOnlyW RegKeyCUReadOnly;
#else
typedef RegKeyA RegKey;
typedef RegKeyPriorityA RegKeyPriority;
typedef RegKeyCULMA RegKeyCULM;
typedef RegKeyReadOnlyA RegKeyReadOnly;
typedef RegKeyLMA RegKeyLM;
typedef RegKeyCUA RegKeyCU;
typedef RegKeyLMReadOnlyA RegKeyLMReadOnly;
typedef RegKeyCUReadOnlyA RegKeyCUReadOnly;
#endif


// inline function definitions

inline
RegKeyA::RegKeyA( LPCSTR pszKey, HKEY hkRoot, bool bCreate /*= false*/, REGSAM samAccess /*= KEY_ALL_ACCESS*/ )
:	m_hkRoot( hkRoot ),
	m_hkThis( NULL ),
	m_samAccess( samAccess ),
	m_pszKey( NULL )
{
	InnerOpen( pszKey, hkRoot, bCreate, samAccess );
}

inline
RegKeyA::RegKeyA( LPCSTR pszKey, RegKeyA& Root, bool bCreate /*= false*/, REGSAM samAccess /*= 0*/ )
:	m_hkRoot( Root ),
	m_hkThis( NULL ),
	m_samAccess( samAccess? samAccess : Root.m_samAccess ),
	m_pszKey( NULL )
{
	InnerOpen( pszKey, m_hkRoot, bCreate, m_samAccess );
}

inline
RegKeyA::RegKeyA( RegKeyA& Source )
:	m_hkRoot( Source.m_hkRoot ),
	m_hkThis( Source.m_hkThis ),
	m_samAccess( Source.m_samAccess ),
	m_pszKey( Source.m_pszKey )
{
	Source.m_hkRoot = NULL;
	Source.m_hkThis = NULL;
	Source.m_pszKey = NULL;
}

inline
HKEY RegKeyA::InnerOpen( LPCSTR pszKey, HKEY hkRoot, bool bCreate /*= false*/, REGSAM samAccess /*= KEY_ALL_ACCESS*/ )
{
	if( !pszKey )
	{
		m_hkThis = hkRoot;
		return hkRoot;
	}
	m_pszKey = new CHAR[lstrlenA( pszKey ) + 1];
	lstrcpyA( m_pszKey, pszKey );
	if( ERROR_SUCCESS !=
				bCreate?
					::RegCreateKeyExA( hkRoot,
														 pszKey,
														 0,
														 NULL,
														 REG_OPTION_NON_VOLATILE,
														 samAccess,
														 NULL,
														 &m_hkThis,
														 NULL ) :
					::RegOpenKeyExA( hkRoot,
													 pszKey,
													 0,
													 samAccess,
													 &m_hkThis ) )
		m_hkThis = NULL;
	return m_hkThis;
}

inline
RegKeyA::~RegKeyA()
{
	Close();
}

inline
void RegKeyA::Close()
{
	if( m_hkThis )
	{
		::RegCloseKey( m_hkThis );
		m_hkThis = NULL;
	}
	delete[] m_pszKey;
	m_pszKey = NULL;
	m_hkRoot = NULL;
}

inline
bool RegKeyA::SetValue( LPCSTR pszName, LPCSTR pszValue )
{
	if( !m_hkThis || !IsWritable() )
		return false;
	return (::RegSetValueExA( m_hkThis, pszName, 0, REG_SZ, (BYTE*)pszValue, lstrlenA( pszValue ) + 1 ) == ERROR_SUCCESS);
}

inline
bool RegKeyA::SetValue( LPCSTR pszName, DWORD dwValue )
{
	if( !m_hkThis || !IsWritable() )
		return false;
	return (::RegSetValueExA( m_hkThis, pszName, 0, REG_DWORD, (BYTE*)&dwValue, sizeof(DWORD)) == ERROR_SUCCESS);
}

inline
bool RegKeyA::SetValue( LPCSTR pszName, const BYTE* pbData, DWORD cbData )
{
	if( !m_hkThis || !IsWritable() )
		return false;
	return (::RegSetValueExA( m_hkThis, pszName, 0, REG_BINARY, pbData, cbData) == ERROR_SUCCESS);
}

inline
bool RegKeyA::RemoveValue( LPCSTR pszName )
{
	if( !m_hkThis || !IsWritable() )
		return false;
	return (::RegDeleteValueA( m_hkThis, pszName ) == ERROR_SUCCESS);
}

inline
DWORD RegKeyA::ValueType( LPCSTR pszName ) const
{
	if( !m_hkThis )
		return REG_NONE;
	DWORD dwType;
	if( ::RegQueryValueExA( m_hkThis, pszName, 0, &dwType, NULL, NULL ) != ERROR_SUCCESS )
		return REG_NONE;
	return dwType;
}

inline
DWORD RegKeyA::ValueType( LPCSTR pszName, DWORD& dwSize ) const
{
	if( !m_hkThis )
		return REG_NONE;
	DWORD dwType;
	if( ::RegQueryValueExA( m_hkThis, pszName, 0, &dwType, NULL, &dwSize ) != ERROR_SUCCESS )
		return REG_NONE;
	return dwType;
}

inline
LPCSTR RegKeyA::GetString( LPCSTR pszName ) const
{
	static CHAR szReturn[MAX_PATH << 2];
	szReturn[0] = '\0';
	DWORD dwSize = MAX_PATH << 2;
	DWORD dwType;
	LONG lResult = ::RegQueryValueExA( m_hkThis, pszName, 0, &dwType, (BYTE*)szReturn, &dwSize );
	if( lResult == ERROR_SUCCESS && dwType == REG_EXPAND_SZ )
	{
		LPSTR pszSource = new CHAR[dwSize];
		lstrcpyA( pszSource, szReturn );
		DWORD cchResult = ::ExpandEnvironmentStringsA( pszSource, szReturn, MAX_PATH << 2);
		if( cchResult > (MAX_PATH << 2) || cchResult <= 0 )
			szReturn[0] = '\0';
		delete [] pszSource;
	}
	return szReturn;
}

inline
DWORD RegKeyA::GetDword( LPCSTR pszName ) const
{
	DWORD dwReturn = 0;
	DWORD dwType;
	DWORD dwSize = sizeof(DWORD);
	if( ::RegQueryValueExA( m_hkThis, pszName, 0, &dwType, (BYTE*)&dwReturn, &dwSize ) != ERROR_SUCCESS ||
			dwType != REG_DWORD )
		return ~0;
	return dwReturn;
}

inline
const BYTE* RegKeyA::GetBytes( LPCSTR pszName, DWORD& cbData ) const
{
	static BYTE rbData[MAX_PATH << 3];
	cbData = 0;
	DWORD dwSize = MAX_PATH << 3;
	DWORD dwType;
	if( ::RegQueryValueExA( m_hkThis, pszName, 0, &dwType, rbData, &dwSize ) != ERROR_SUCCESS ||
			dwType != REG_BINARY )
		return NULL;
	cbData = dwSize;
	return rbData;
}



inline
RegKeyW::RegKeyW( LPCWSTR pszKey, HKEY hkRoot, bool bCreate /*= false*/, REGSAM samAccess /*= KEY_ALL_ACCESS*/ )
:	m_hkRoot( hkRoot ),
	m_hkThis( NULL ),
	m_samAccess( samAccess ),
	m_pszKey( NULL )
{
	InnerOpen( pszKey, hkRoot, bCreate, samAccess );
}

inline
RegKeyW::RegKeyW( LPCWSTR pszKey, RegKeyW& Root, bool bCreate /*= false*/, REGSAM samAccess /*= 0*/ )
:	m_hkRoot( Root ),
	m_hkThis( NULL ),
	m_samAccess( samAccess? samAccess : Root.m_samAccess ),
	m_pszKey( NULL )
{
	InnerOpen( pszKey, m_hkRoot, bCreate, m_samAccess );
}

inline
RegKeyW::RegKeyW( RegKeyW& Source )
:	m_hkRoot( Source.m_hkRoot ),
	m_hkThis( Source.m_hkThis ),
	m_samAccess( Source.m_samAccess ),
	m_pszKey( Source.m_pszKey )
{
	Source.m_hkRoot = NULL;
	Source.m_hkThis = NULL;
	Source.m_pszKey = NULL;
}

inline
HKEY RegKeyW::InnerOpen( LPCWSTR pszKey, HKEY hkRoot, bool bCreate /*= false*/, REGSAM samAccess /*= KEY_ALL_ACCESS*/ )
{
	if( !pszKey )
	{
		m_hkThis = hkRoot;
		return hkRoot;
	}
	m_pszKey = new WCHAR[lstrlenW( pszKey ) + 1];
	lstrcpyW( m_pszKey, pszKey );
	if( ERROR_SUCCESS !=
				bCreate?
					::RegCreateKeyExW( hkRoot,
														 pszKey,
														 0,
														 NULL,
														 REG_OPTION_NON_VOLATILE,
														 samAccess,
														 NULL,
														 &m_hkThis,
														 NULL ) :
					::RegOpenKeyExW( hkRoot,
													 pszKey,
													 0,
													 samAccess,
													 &m_hkThis ) )
		m_hkThis = NULL;
	return m_hkThis;
}

inline
RegKeyW::~RegKeyW()
{
	Close();
}

inline
void RegKeyW::Close()
{
	if( m_hkThis )
	{
		::RegCloseKey( m_hkThis );
		m_hkThis = NULL;
	}
	delete[] m_pszKey;
	m_pszKey = NULL;
	m_hkRoot = NULL;
}

inline
bool RegKeyW::SetValue( LPCWSTR pszName, LPCWSTR pszValue )
{
	if( !m_hkThis || !IsWritable() )
		return false;
	return (::RegSetValueExW( m_hkThis, pszName, 0, REG_SZ, (BYTE*)pszValue, sizeof(WCHAR) * (lstrlenW( pszValue ) + 1) ) == ERROR_SUCCESS);
}

inline
bool RegKeyW::SetValue( LPCWSTR pszName, DWORD dwValue )
{
	if( !m_hkThis || !IsWritable() )
		return false;
	return (::RegSetValueExW( m_hkThis, pszName, 0, REG_DWORD, (BYTE*)&dwValue, sizeof(DWORD)) == ERROR_SUCCESS);
}

inline
bool RegKeyW::SetValue( LPCWSTR pszName, const BYTE* pbData, DWORD cbData )
{
	if( !m_hkThis || !IsWritable() )
		return false;
	return (::RegSetValueExW( m_hkThis, pszName, 0, REG_BINARY, pbData, cbData) == ERROR_SUCCESS);
}

inline
bool RegKeyW::RemoveValue( LPCWSTR pszName )
{
	if( !m_hkThis || !IsWritable() )
		return false;
	return (::RegDeleteValueW( m_hkThis, pszName ) == ERROR_SUCCESS);
}

inline
DWORD RegKeyW::ValueType( LPCWSTR pszName ) const
{
	if( !m_hkThis )
		return REG_NONE;
	DWORD dwType;
	if( ::RegQueryValueExW( m_hkThis, pszName, 0, &dwType, NULL, NULL ) != ERROR_SUCCESS )
		return REG_NONE;
	return dwType;
}

inline
DWORD RegKeyW::ValueType( LPCWSTR pszName, DWORD& dwSize ) const
{
	if( !m_hkThis )
		return REG_NONE;
	DWORD dwType;
	if( ::RegQueryValueExW( m_hkThis, pszName, 0, &dwType, NULL, &dwSize ) != ERROR_SUCCESS )
		return REG_NONE;
	return dwType;
}

inline
LPCWSTR RegKeyW::GetString( LPCWSTR pszName ) const
{
	static WCHAR szReturn[MAX_PATH << 2];
	szReturn[0] = L'\0';
	DWORD dwSize = MAX_PATH << 2;
	DWORD dwType;
	LONG lResult = ::RegQueryValueExW( m_hkThis, pszName, 0, &dwType, (BYTE*)szReturn, &dwSize );
	if( lResult == ERROR_SUCCESS && dwType == REG_EXPAND_SZ )
	{
		LPWSTR pszSource = new WCHAR[dwSize];
		lstrcpyW( pszSource, szReturn );
		DWORD cchResult = ::ExpandEnvironmentStringsW( pszSource, szReturn, MAX_PATH << 2);
		if( cchResult > (MAX_PATH << 2) || cchResult <= 0 )
			szReturn[0] = L'\0';
		delete [] pszSource;
	}
	return szReturn;
}

inline
DWORD RegKeyW::GetDword( LPCWSTR pszName ) const
{
	DWORD dwReturn = 0;
	DWORD dwType;
	DWORD dwSize = sizeof(DWORD);
	if( ::RegQueryValueExW( m_hkThis, pszName, 0, &dwType, (BYTE*)&dwReturn, &dwSize ) != ERROR_SUCCESS ||
			dwType != REG_DWORD )
		return ~0;
	return dwReturn;
}

inline
const BYTE* RegKeyW::GetBytes( LPCWSTR pszName, DWORD& cbData ) const
{
	static BYTE rbData[MAX_PATH << 3];
	cbData = 0;
	DWORD dwSize = MAX_PATH << 3;
	DWORD dwType;
	if( ::RegQueryValueExW( m_hkThis, pszName, 0, &dwType, rbData, &dwSize ) != ERROR_SUCCESS ||
			dwType != REG_BINARY )
		return NULL;
	cbData = dwSize;
	return rbData;
}



inline
RegKeyPriorityA::RegKeyPriorityA( LPCSTR pszKey, HKEY hkRoot1, HKEY hkRoot2,
																	bool bCreate /*= false*/, REGSAM samAccess /*= KEY_ALL_ACCESS*/ )
:	RegKeyA( pszKey, hkRoot1, bCreate, samAccess ),
	m_rkSecondary( pszKey, hkRoot2, false, samAccess )
{
}

inline
RegKeyPriorityA::RegKeyPriorityA( LPCSTR pszKey, RegKeyPriorityA& hkParent,
																	bool bCreate /*= false*/, REGSAM samAccess /*= KEY_ALL_ACCESS*/ )

:	RegKeyA( pszKey, hkParent, bCreate, samAccess ),
	m_rkSecondary( pszKey, hkParent.SecondaryRegKey(), false, samAccess )
{
}

inline
bool RegKeyPriorityA::RemoveValue( LPCSTR pszName )
{
	if( RegKeyA::RemoveValue( pszName ) )
		return true;
	return m_rkSecondary.RemoveValue( pszName );
}

inline
DWORD RegKeyPriorityA::ValueType( LPCSTR pszName ) const
{
	DWORD dwType = RegKeyA::ValueType( pszName );
	if( REG_NONE != dwType )
		return dwType;
	return m_rkSecondary.ValueType( pszName );
}

inline
DWORD RegKeyPriorityA::ValueType( LPCSTR pszName, DWORD& dwSize ) const
{
	DWORD dwType = RegKeyA::ValueType( pszName, dwSize );
	if( REG_NONE != dwType )
		return dwType;
	return m_rkSecondary.ValueType( pszName, dwSize );
}

inline
LPCSTR RegKeyPriorityA::GetString( LPCSTR pszName ) const
{
	if( REG_NONE != RegKeyA::ValueType( pszName ) )
		return RegKeyA::GetString( pszName );
	return m_rkSecondary.GetString( pszName );
}

inline
DWORD RegKeyPriorityA::GetDword( LPCSTR pszName ) const
{
	if( REG_NONE != RegKeyA::ValueType( pszName ) )
		return RegKeyA::GetDword( pszName );
	return m_rkSecondary.GetDword( pszName );
}

inline
const BYTE* RegKeyPriorityA::GetBytes( LPCSTR pszName, DWORD& cbData ) const
{
	if( REG_NONE != RegKeyA::ValueType( pszName ) )
		return RegKeyA::GetBytes( pszName, cbData );
	return m_rkSecondary.GetBytes( pszName, cbData );
}



inline
RegKeyPriorityW::RegKeyPriorityW( LPCWSTR pszKey, HKEY hkRoot1, HKEY hkRoot2,
																	bool bCreate /*= false*/, REGSAM samAccess /*= KEY_ALL_ACCESS*/ )
:	RegKeyW( pszKey, hkRoot1, bCreate, samAccess ),
	m_rkSecondary( pszKey, hkRoot2, false, samAccess )
{
}

inline
RegKeyPriorityW::RegKeyPriorityW( LPCWSTR pszKey, RegKeyPriorityW& hkParent,
																	bool bCreate /*= false*/, REGSAM samAccess /*= KEY_ALL_ACCESS*/ )

:	RegKeyW( pszKey, hkParent, bCreate, samAccess ),
	m_rkSecondary( pszKey, hkParent.SecondaryRegKey(), false, samAccess )
{
}

inline
bool RegKeyPriorityW::RemoveValue( LPCWSTR pszName )
{
	if( RegKeyW::RemoveValue( pszName ) )
		return true;
	return m_rkSecondary.RemoveValue( pszName );
}

inline
DWORD RegKeyPriorityW::ValueType( LPCWSTR pszName ) const
{
	DWORD dwType = RegKeyW::ValueType( pszName );
	if( REG_NONE != dwType )
		return dwType;
	return m_rkSecondary.ValueType( pszName );
}

inline
DWORD RegKeyPriorityW::ValueType( LPCWSTR pszName, DWORD& dwSize ) const
{
	DWORD dwType = RegKeyW::ValueType( pszName, dwSize );
	if( REG_NONE != dwType )
		return dwType;
	return m_rkSecondary.ValueType( pszName, dwSize );
}

inline
LPCWSTR RegKeyPriorityW::GetString( LPCWSTR pszName ) const
{
	if( REG_NONE != RegKeyW::ValueType( pszName ) )
		return RegKeyW::GetString( pszName );
	return m_rkSecondary.GetString( pszName );
}

inline
DWORD RegKeyPriorityW::GetDword( LPCWSTR pszName ) const
{
	if( REG_NONE != RegKeyW::ValueType( pszName ) )
		return RegKeyW::GetDword( pszName );
	return m_rkSecondary.GetDword( pszName );
}

inline
const BYTE* RegKeyPriorityW::GetBytes( LPCWSTR pszName, DWORD& cbData ) const
{
	if( REG_NONE != RegKeyW::ValueType( pszName ) )
		return RegKeyW::GetBytes( pszName, cbData );
	return m_rkSecondary.GetBytes( pszName, cbData );
}



inline
bool RegRemoveKey( RegKeyA& rkTarget, bool bRemoveEmptyParents /*= false*/ )
{
	if( !rkTarget.IsWritable() )
		return false;
	DWORD cchKeyNameSize = MAX_PATH;
	DWORD dwIndex = 0;
	::RegQueryInfoKeyA( rkTarget, NULL, NULL, NULL, &dwIndex, &cchKeyNameSize, NULL, NULL, NULL, NULL, NULL, NULL );
	LPSTR pszSubkey = new CHAR[++cchKeyNameSize];
	while( dwIndex-- > 0 &&
				 ERROR_SUCCESS == ::RegEnumKeyA( rkTarget, dwIndex, pszSubkey, cchKeyNameSize ) )
		RegRemoveKey( RegKeyA( pszSubkey, rkTarget ) );
	delete[] pszSubkey;

	HKEY hkRoot = rkTarget.Root();
	LPSTR pszKey = new CHAR[lstrlenA( rkTarget.Key() ) + 1];
	lstrcpyA( pszKey, rkTarget.Key() );
	rkTarget.Close();
	bool bSuccess = (ERROR_SUCCESS == ::RegDeleteKeyA( hkRoot, pszKey ));
	if( bSuccess && bRemoveEmptyParents )
	{
		if( pszKey && *pszKey )
		{
			LPSTR pszParentKey = new CHAR[lstrlenA( pszKey ) + 1];
			lstrcpyA( pszParentKey, pszKey );
			int idxCursor = lstrlenA( pszParentKey ) - 1;
			while( idxCursor > 0 && pszParentKey[idxCursor] != '\\' )
				idxCursor--;
			if( idxCursor > 0 )
			{
				pszParentKey[idxCursor] ='\0';
				RegKeyA rkParent( pszParentKey, hkRoot );
				if( rkParent )
				{
					DWORD dwSubkeyQty = 0;
					DWORD dwValueQty = 0;
					if( ERROR_SUCCESS == ::RegQueryInfoKeyA( rkParent,
																									 NULL,
																									 NULL,
																									 NULL,
																									 &dwSubkeyQty,
																									 NULL,
																									 NULL,
																									 &dwValueQty,
																									 NULL,
																									 NULL,
																									 NULL,
																									 NULL ) &&
							dwSubkeyQty == 0 &&
							dwValueQty == 0 )
						RegRemoveKey( rkParent, true );
				}
			}
			delete[] pszParentKey;
		}
	}
	delete[] pszKey;
	return bSuccess;
}

inline
bool RegRemoveKey( RegKeyW& rkTarget, bool bRemoveEmptyParents /*= false*/ )
{
	if( !rkTarget.IsWritable() )
		return false;
	DWORD cchKeyNameSize = MAX_PATH;
	DWORD dwIndex = 0;
	::RegQueryInfoKeyW( rkTarget, NULL, NULL, NULL, &dwIndex, &cchKeyNameSize, NULL, NULL, NULL, NULL, NULL, NULL );
	LPWSTR pwszSubkey = new WCHAR[++cchKeyNameSize];
	while( dwIndex-- > 0 &&
				 ERROR_SUCCESS == ::RegEnumKeyW( rkTarget, dwIndex, pwszSubkey, cchKeyNameSize ) )
		RegRemoveKey( RegKeyW( pwszSubkey, rkTarget ) );
	delete[] pwszSubkey;

	HKEY hkRoot = rkTarget.Root();
	LPWSTR pwszKey = new WCHAR[lstrlenW( rkTarget.Key() ) + 1];
	lstrcpyW( pwszKey, rkTarget.Key() );
	rkTarget.Close();
	bool bSuccess = (ERROR_SUCCESS == ::RegDeleteKeyW( hkRoot, pwszKey ));
	if( bSuccess && bRemoveEmptyParents )
	{
		if( pwszKey && *pwszKey )
		{
			LPWSTR pszParentKey = new WCHAR[lstrlenW( pwszKey ) + 1];
			lstrcpyW( pszParentKey, pwszKey );
			int idxCursor = lstrlenW( pszParentKey ) - 1;
			while( idxCursor > 0 && pszParentKey[idxCursor] != L'\\' )
				idxCursor--;
			if( idxCursor > 0 )
			{
				pszParentKey[idxCursor] = L'\0';
				RegKeyW rkParent( pszParentKey, hkRoot );
				if( rkParent )
				{
					DWORD dwSubkeyQty = 0;
					DWORD dwValueQty = 0;
					if( ERROR_SUCCESS == ::RegQueryInfoKeyW( rkParent,
																									 NULL,
																									 NULL,
																									 NULL,
																									 &dwSubkeyQty,
																									 NULL,
																									 NULL,
																									 &dwValueQty,
																									 NULL,
																									 NULL,
																									 NULL,
																									 NULL ) &&
							dwSubkeyQty == 0 &&
							dwValueQty == 0 )
						RegRemoveKey( rkParent, true );
				}
			}
			delete[] pszParentKey;
		}
	}
	delete[] pwszKey;
	return bSuccess;
}


inline
bool RegCopyKey( class RegKeyA& rkSource, HKEY rkTargetRoot, LPCSTR pszTarget )
{
	if( !rkSource )
		return false;
	RegKeyA rkTarget( pszTarget, rkTargetRoot, true );
	if( !rkTarget )
		return false;
	DWORD cchKeyNameSize = MAX_PATH;
	DWORD dwKeyNameIndex = 0;
	DWORD cchValueNameSize = MAX_PATH;
	DWORD dwValueDataSize = MAX_PATH;
	DWORD dwValueNameIndex = 0;
	::RegQueryInfoKeyA( rkSource, NULL, NULL, NULL, &dwKeyNameIndex, &cchKeyNameSize, NULL,
											&dwValueNameIndex, &cchValueNameSize, &dwValueDataSize, NULL, NULL );
	LPSTR pszSubkey = new CHAR[++cchKeyNameSize];
	while( dwKeyNameIndex-- > 0 &&
					ERROR_SUCCESS == ::RegEnumKeyA( rkSource, dwKeyNameIndex, pszSubkey, cchKeyNameSize ) )
		RegCopyKey( RegKeyA( pszSubkey, rkSource ), rkTarget, pszSubkey );
	delete[] pszSubkey;
	LPSTR pszValueName = new CHAR[++cchValueNameSize];
	BYTE* pbufValue = new BYTE[dwValueDataSize];
	while( dwValueNameIndex-- > 0 )
	{
		DWORD cchName = cchValueNameSize;
		DWORD cbData = dwValueDataSize;
		DWORD dwType = 0;
		if( ERROR_SUCCESS == ::RegEnumValueA( rkSource, dwValueNameIndex, pszValueName, &cchName,
																					NULL, &dwType, pbufValue, &cbData ) )
			RegSetValueExA( rkTarget, pszValueName, 0, dwType, pbufValue, cbData );
	}
	delete[] pszValueName;
	delete[] pbufValue;
	return true;
}


inline
bool RegCopyKey( class RegKeyW& rkSource, HKEY rkTargetRoot, LPCWSTR pwszTarget )
{
	if( !rkSource )
		return false;
	RegKeyW rkTarget( pwszTarget, rkTargetRoot, true );
	if( !rkTarget )
		return false;
	DWORD cchKeyNameSize = MAX_PATH;
	DWORD dwKeyNameIndex = 0;
	DWORD cchValueNameSize = MAX_PATH;
	DWORD dwValueDataSize = MAX_PATH;
	DWORD dwValueNameIndex = 0;
	::RegQueryInfoKeyW( rkSource, NULL, NULL, NULL, &dwKeyNameIndex, &cchKeyNameSize, NULL,
											&dwValueNameIndex, &cchValueNameSize, &dwValueDataSize, NULL, NULL );
	LPWSTR pwszSubkey = new WCHAR[++cchKeyNameSize];
	while( dwKeyNameIndex-- > 0 &&
					ERROR_SUCCESS == ::RegEnumKeyW( rkSource, dwKeyNameIndex, pwszSubkey, cchKeyNameSize ) )
		RegCopyKey( RegKeyW( pwszSubkey, rkSource ), rkTarget, pwszSubkey );
	delete[] pwszSubkey;
	LPWSTR pwszValueName = new WCHAR[++cchValueNameSize];
	BYTE* pbufValue = new BYTE[dwValueDataSize];
	while( dwValueNameIndex-- > 0 )
	{
		DWORD cchName = cchValueNameSize;
		DWORD cbData = dwValueDataSize;
		DWORD dwType = 0;
		if( ERROR_SUCCESS == ::RegEnumValueW( rkSource, dwValueNameIndex, pwszValueName, &cchName,
																					NULL, &dwType, pbufValue, &cbData ) )
			RegSetValueExW( rkTarget, pwszValueName, 0, dwType, pbufValue, cbData );
	}
	delete[] pwszValueName;
	delete[] pbufValue;
	return true;
}


#endif // _REGIO_H_
