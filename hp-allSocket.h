/*
 * hp-allSocket.h -- HP-Socket 6.0.9, TCP + UDP, amalgamated.
 *
 *   TCP:  TcpServer   / TcpPullServer   / TcpPackServer
 *         TcpClient   / TcpPullClient   / TcpPackClient
 *   UDP:  UdpServer   / UdpClient       / UdpArqClient
 *         UdpArqServer/ UdpCast         / UdpNode
 *
 * Add hp-allSocket.h and hp-allSocket.cpp to your Visual Studio project.
 * Nothing else from HP-Socket is required -- no extra sources, headers or
 * .lib files. KCP (the UDP ARQ transport) is inlined as well.
 *
 * This is the combined build. It exists because hp-socket.{h,cpp} and
 * hp-udpSocket.{h,cpp} each carry their own copy of the shared socket
 * infrastructure, so linking both pairs into one project would produce
 * duplicate symbols. Here the base is inlined exactly once and both
 * component families are available.
 *
 * Derived from HP-Socket 6.0.9 (Windows) by Bruce Liang (ldcsaa).
 *   https://github.com/ldcsaa/HP-Socket
 * Licensed under the Apache License, Version 2.0.
 *
 * Requires: MSVC (Visual Studio 2015+) with the ATL component, compiling as
 *           C++17 or later. MFC is not required. ws2_32 and winmm are
 *           linked automatically.
 */
#pragma once

/*
 * Subsystem switches. TCP and UDP are on; SSL / HTTP / compression are off.
 * _UDP_SUPPORT is defined automatically by HPTypeDef.h because
 * _UDP_DISABLED is not set here.
 */
#ifndef _SSL_DISABLED
    #define _SSL_DISABLED
#endif
#ifndef _HTTP_DISABLED
    #define _HTTP_DISABLED
#endif
#ifndef _ZLIB_DISABLED
    #define _ZLIB_DISABLED
#endif
#ifndef _BROTLI_DISABLED
    #define _BROTLI_DISABLED
#endif

/* Base includes. The original library obtained these from its project
 * stdafx.h: Common/GeneralHelper.h plus the Common layer, inlined below.
 * They must precede any other Windows header because GeneralHelper.h sets
 * the _WIN32_WINNT defaults that SDKDDKVer.h would otherwise latch. */


/* ========================================================================== */
/*  Common/GeneralHelper.h  -- base include chain
/*  source: Windows\Src\Common\GeneralHelper.h
/* ========================================================================== */

/*

Optional Macros:

Windows:
++++++++++++++++++++++
_WIN32_WINNT		: Windows NT 版本	（默认：_WIN32_WINNT_WINXP / _WIN32_WINNT_WIN7）
WINVER				: Windows 版本		（默认：_WIN32_WINNT）
_USE_MFC			: 使用 MFC
_WINSOCK_SUPPORT	: 支持 Windows Socket
_NO_RIBBONS_SUPPORT	: 不支持 Ribbons 界面风格
_DETECT_MEMORY_LEAK	: DEBUG 状态下支持内存泄露检查

Windows CE:
++++++++++++++++++++++
WINVER				: Windows 版本
_USE_MFC			: 使用 MFC
_WINSOCK_SUPPORT	: 支持 Windows Socket
_DETECT_MEMORY_LEAK	: DEBUG 状态下支持内存泄露检查
_ONLY_DETECT_CONFIRMED_MEMORY_LEAK_	: 只报告能够确认的内存泄露（不能确定的不报告）
---------------------------
VC 2022
	_MSC_VER == 1930
VC 2019
	_MSC_VER == 1920
VC 2017
	_MSC_VER == 1910
VC 2015
	_MSC_VER == 1900
VC 2013
	_MSC_VER == 1800
VC 2012
	_MSC_VER == 1700
VC 2010
	_MSC_VER == 1600
VC 2008
	_MSC_VER == 1500
VC 2005
	_MSC_VER == 1400
VC 7.1
	_MSC_VER == 1310
VC 7.0
	_MSC_VER == 1300
VC 6.0
	_MSC_VER == 1200
---------------------------
Windows Versions:
_WIN32_WINNT_NT4		x0400
_WIN32_WINNT_WIN2K		0x0500
_WIN32_WINNT_WINXP		0x0501
_WIN32_WINNT_WS03		0x0502
_WIN32_WINNT_WIN6		0x0600
_WIN32_WINNT_VISTA		0x0600
_WIN32_WINNT_WS08		0x0600
_WIN32_WINNT_LONGHORN	0x0600
_WIN32_WINNT_WIN7		0x0601
_WIN32_WINNT_WIN8		0x0602
_WIN32_WINNT_WINBLUE	0x0603
_WIN32_WINNT_WIN10		0x0A00
---------------------------
*/

#pragma once

#ifndef WINDOWS_ENABLE_CPLUSPLUS
	#define WINDOWS_ENABLE_CPLUSPLUS
#endif

#ifndef VC_EXTRALEAN
	#define VC_EXTRALEAN
#endif

#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif

#ifndef _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
	#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#endif

#if _MSC_VER >= 1400

	#if defined _DEBUG && _MSC_VER < 1600
		#ifndef _SECURE_SCL
			#define _SECURE_SCL					0
		#endif
		#ifndef _HAS_ITERATOR_DEBUGGING
			#define _HAS_ITERATOR_DEBUGGING		0
		#endif
	#endif

	#ifndef _CRT_SECURE_NO_DEPRECATE
		#define _CRT_SECURE_NO_DEPRECATE		1
	#endif

	#ifndef _SCL_SECURE_NO_DEPRECATE
		#define _SCL_SECURE_NO_DEPRECATE		1
	#endif

	#ifndef _ATL_SECURE_NO_WARNINGS
		#define _ATL_SECURE_NO_WARNINGS			1
	#endif

	#ifndef _ATL_SECURE_NO_WARNINGS
		#define _ATL_SECURE_NO_WARNINGS			1
	#endif

	#ifndef _ATL_DISABLE_NOTHROW_NEW
		#define _ATL_DISABLE_NOTHROW_NEW		1
	#endif

	#ifndef _SECURE_ATL
		#define _SECURE_ATL						1
	#endif

	#ifndef _WINSOCK_DEPRECATED_NO_WARNINGS
		#define _WINSOCK_DEPRECATED_NO_WARNINGS	1
	#endif

#endif

#ifndef _WIN32_WINNT
	#if defined (_WIN64)
		#if _MSC_VER >= 1930
			#define _WIN32_WINNT	_WIN32_WINNT_WIN10
		#else
			#define _WIN32_WINNT	_WIN32_WINNT_WIN7
		#endif
	#else
		#if _MSC_VER >= 1930
			#define _WIN32_WINNT	_WIN32_WINNT_WIN10
		#elif _MSC_VER >= 1910
			#define _WIN32_WINNT	_WIN32_WINNT_WIN7
		#else
			#define _WIN32_WINNT	_WIN32_WINNT_WINXP
		#endif
	#endif
#endif

#ifndef WINVER
	#define WINVER	_WIN32_WINNT
#endif

#if _MSC_VER >= 1600
	#include <SDKDDKVer.h>
#else
	#if !defined(nullptr)
		#define nullptr	NULL
	#endif
#endif

#ifndef _WIN32_WINNT_WIN8
	#define _WIN32_WINNT_WIN8	0x0602
#endif

#ifndef _WIN32_WINNT_WIN10
	#define _WIN32_WINNT_WIN10	0x0A00
#endif

#ifdef _DETECT_MEMORY_LEAK
	#ifndef _CRTDBG_MAP_ALLOC
		#define _CRTDBG_MAP_ALLOC
	#endif
#endif

#ifdef _USE_MFC

	#ifndef _AFX_ALL_WARNINGS
		#define _AFX_ALL_WARNINGS
	#endif

	#include <afxwin.h>
	#include <afxext.h>
	#include <afxdisp.h>

	#ifndef _AFX_NO_OLE_SUPPORT
		#include <afxdtctl.h>
	#endif

	#ifndef _AFX_NO_AFXCMN_SUPPORT
		#include <afxcmn.h>
	#endif

	#ifndef _NO_RIBBONS_SUPPORT
		#include <afxcontrolbars.h>
	#endif

#else

	#include <Windows.h>
	#include <WindowsX.h>
	#include <commctrl.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <malloc.h>
	#include <memory.h>
	#include <tchar.h>
	#include <atlstr.h>
	#include <atltime.h>

	#ifndef ASSERT
		#define ASSERT(f)	ATLASSERT(f)
	#endif
	#ifndef VERIFY
		#define VERIFY(f)	ATLVERIFY(f)
	#endif
	#ifndef ENSURE
		#define ENSURE(f)	ATLENSURE(f)
	#endif

	#ifndef TRACE
		#include <atltrace.h>

		#define TRACE							AtlTrace
		#define TRACE0(f)						TRACE(f)
		#define TRACE1(f, p1)					TRACE(f, p1)
		#define TRACE2(f, p1, p2)				TRACE(f, p1, p2)
		#define TRACE3(f, p1, p2, p3)			TRACE(f, p1, p2, p3)
		#define TRACE4(f, p1, p2, p3, p4)		TRACE(f, p1, p2, p3, p4)
		#define TRACE5(f, p1, p2, p3, p4, p5)	TRACE(f, p1, p2, p3, p4, p5)
	#endif

#endif

#ifdef _WINSOCK_SUPPORT
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#include <mswsock.h>
#endif

#include <atlbase.h>
#include <atlconv.h>

/* [amalgamated] #include "Singleton.h" */
/* [amalgamated] #include "Event.h" */
/* [amalgamated] #include "Semaphore.h" */
/* [amalgamated] #include "CriticalSection.h" */
/* [amalgamated] #include "STLHelper.h" */
/* [amalgamated] #include "Win32Helper.h" */
/* [amalgamated] #include "PrivateHeap.h" */
/* [amalgamated] #include "BufferPtr.h" */

#if defined (_DEBUG) && defined (_DETECT_MEMORY_LEAK)
/* [amalgamated] #include "debug/win32_crtdbg.h" */
#endif


/* ========================================================================== */
/*  Singleton.h
/*  source: Windows\Src\Common\Singleton.h
/* ========================================================================== */

#pragma once

#define SINGLETON_THIS(ClassName)		ClassName::GetThis()
#define SINGLETON_INSTANCE(ClassName)	ClassName::GetInstance()
#define SINGLETON_OBJECT(ObjName)		SINGLETON_INSTANCE(C##ObjName)

#define DEFINE_SINGLETON(ClassName)											\
	ClassName* ClassName::m_pThis = nullptr;

#define DEFINE_P_THIS(ClassName)											\
		DEFINE_SINGLETON(ClassName)

#define DECLARE_SINGLETON_INTERFACE(ClassName)								\
public:																		\
	static ClassName* GetThis()		{return m_pThis;}						\
	static ClassName& GetInstance() {return *m_pThis;}						\
protected:																	\
	static ClassName* m_pThis;

#define DECLARE_SINGLETON_CREATE_INSTANCE(ClassName)						\
public:																		\
	static BOOL CreateInstance()											\
	{																		\
		if(!m_pThis)														\
			m_pThis = new ClassName;										\
																			\
		return m_pThis != nullptr;											\
	}																		\
																			\
	static BOOL DeleteInstance()											\
	{																		\
		if(m_pThis)															\
		{																	\
			delete m_pThis;													\
			m_pThis = nullptr;												\
		}																	\
																			\
		return m_pThis == nullptr;											\
	}

#define DECLARE_PRIVATE_DEFAULT_CONSTRUCTOR(ClassName)						\
private:																	\
	ClassName(){}

#define DECLARE_PRIVATE_COPY_CONSTRUCTOR(ClassName)							\
private:																	\
	ClassName(const ClassName&);											\
	ClassName& operator = (const ClassName&);

#define DECLARE_NO_COPY_CLASS(className)									\
		DECLARE_PRIVATE_COPY_CONSTRUCTOR(className)


#define DECLARE_SINGLETON_IMPLEMENT_NO_CREATE_INSTANCE(ClassName)			\
	DECLARE_SINGLETON_INTERFACE(ClassName)									\
	DECLARE_PRIVATE_DEFAULT_CONSTRUCTOR(ClassName)							\
	DECLARE_PRIVATE_COPY_CONSTRUCTOR(ClassName)								

#define DECLARE_SINGLETON_IMPLEMENT_NO_DEFAULT_CONSTRUCTOR(ClassName)		\
	DECLARE_SINGLETON_CREATE_INSTANCE(ClassName)							\
	DECLARE_PRIVATE_COPY_CONSTRUCTOR(ClassName)

#define DECLARE_SINGLETON_IMPLEMENT(ClassName)								\
	DECLARE_SINGLETON_IMPLEMENT_NO_DEFAULT_CONSTRUCTOR(ClassName)			\
	DECLARE_PRIVATE_DEFAULT_CONSTRUCTOR(ClassName)

#define DECLARE_SINGLETON_NO_DEFAULT_CONSTRUCTOR(ClassName)					\
	DECLARE_SINGLETON_INTERFACE(ClassName)									\
	DECLARE_SINGLETON_IMPLEMENT_NO_DEFAULT_CONSTRUCTOR(ClassName)

#define DECLARE_SINGLETON(ClassName)										\
	DECLARE_SINGLETON_NO_DEFAULT_CONSTRUCTOR(ClassName)						\
	DECLARE_PRIVATE_DEFAULT_CONSTRUCTOR(ClassName)


template<class T>
class CSingleObject
{
public:
	CSingleObject	()	{T::CreateInstance();}
	~CSingleObject	()	{T::DeleteInstance();}
	T* GetPointer	()	{return T::GetThis();}
	T& GetObject	()	{return T::GetInstance();}
	BOOL IsValid	()	{return GetPointer() != nullptr;}
};

#define DECLARE_SINGLE_OBJECT(ClassName) CSingleObject<ClassName> _##ClassName##_Single_Object_;

/* ========================================================================== */
/*  SysHelper.h
/*  source: Windows\Src\Common\SysHelper.h
/* ========================================================================== */

#pragma once

/* 最大工作线程数 */
#define MAX_WORKER_THREAD_COUNT			512
/* 默认对象缓存锁定时间 */
#define DEFAULT_OBJECT_CACHE_LOCK_TIME	(30 * 1000)
/* 默认对象缓存池大小 */
#define DEFAULT_OBJECT_CACHE_POOL_SIZE	600
/* 默认对象缓存池回收阀值 */
#define DEFAULT_OBJECT_CACHE_POOL_HOLD	600
/* 默认内存块缓存容量 */
#define DEFAULT_BUFFER_CACHE_CAPACITY	4096
/* 默认内存块缓存池大小 */
#define DEFAULT_BUFFER_CACHE_POOL_SIZE	1024
/* 默认内存块缓存池回收阀值 */
#define DEFAULT_BUFFER_CACHE_POOL_HOLD	1024

/* 使用外部垃圾回收 */
#define USE_EXTERNAL_GC					1

#define SYS_PAGE_SIZE					(GetSysPageSize())
#define DEFAULT_WORKER_THREAD_COUNT		(GetDefaultWorkerThreadCount())
#define SELF_PROCESS_ID					(::GetCurrentProcessId())
#define SELF_THREAD_ID					(::GetCurrentThreadId())
#define SELF_THREAD						(::GetCurrentThread())
#define IsSameThread(tid1, tid2)		((tid1) == (tid2))
#define IsSelfThread(tid)				IsSameThread((tid), SELF_THREAD_ID)
#define IsSameProcess(pid1, pid2)		((pid1) == (pid2))
#define IsSelfProcess(pid)				IsSameProcess((pid), SELF_PROCESS_ID)

DWORD GetSysPageSize();
DWORD GetDefaultWorkerThreadCount();

// 获取系统信息
VOID SysGetSystemInfo(LPSYSTEM_INFO pInfo);
// 获取 CPU 核数
DWORD SysGetNumberOfProcessors();
// 获取页面大小
DWORD SysGetPageSize();


/* ========================================================================== */
/*  FuncHelper.h
/*  source: Windows\Src\Common\FuncHelper.h
/* ========================================================================== */

#pragma once

#define FPRINTLN(fd, fmt, ...)			fprintf((fd), fmt "\n", ##__VA_ARGS__)
#define PRINTLN(fmt, ...)				FPRINTLN(stdout, fmt, ##__VA_ARGS__)

#define IS_OK(rs)						((BOOL)(rs))
#define IS_NOT_OK(rs)					(!IS_OK(rs))

#define HAS_ERROR						-1
#define CHECK_IS_OK(expr)				{if(IS_NOT_OK(expr)) return FALSE;}
#define CHECK_ERROR_FD(fd)				{if(IS_INVALID_FD(fd)) return FALSE;}
#define CHECK_ERROR_INVOKE(expr)		{if(!IS_NO_ERROR(expr)) return FALSE;}
#define CHECK_ERROR_CODE(rs)			{if(!IS_NO_ERROR(rs)) {::SetLastError(rs); return FALSE;}}
#define CHECK_ERROR(expr, code)			{if(!(expr)) {::SetLastError(code); return FALSE;}}
#define CHECK_EINVAL(expr)				CHECK_ERROR(expr, ERROR_INVALID_PARAMETER)
#define ASSERT_CHECK_ERROR(expr, code)	{ASSERT(expr); CHECK_ERROR(expr, code);}
#define ASSERT_CHECK_EINVAL(expr)		{ASSERT(expr); CHECK_EINVAL(expr);}

#define CHECK_IS_ERROR(code)			(::GetLastError() == (code))
#define CONTINUE_IF_ERROR(code)			{if(CHECK_IS_ERROR(code)) continue;}
#define BREAK_IF_ERROR(code)			{if(CHECK_IS_ERROR(code)) break;}

#define IS_WOULDBLOCK_ERROR()			CHECK_IS_ERROR(WSAEWOULDBLOCK)
#define CONTINUE_WOULDBLOCK_ERROR()		CONTINUE_IF_ERROR(WSAEWOULDBLOCK)
#define BREAK_WOULDBLOCK_ERROR()		BREAK_IF_ERROR(WSAEWOULDBLOCK)
#define IS_IO_PENDING_ERROR()			CHECK_IS_ERROR(ERROR_IO_PENDING)
#define CONTINUE_IO_PENDING_ERROR()		CONTINUE_IF_ERROR(ERROR_IO_PENDING)
#define BREAK_IO_PENDING_ERROR()		BREAK_IF_ERROR(ERROR_IO_PENDING)

#define EqualMemory(dest, src, len)		(!memcmp((dest), (src), (len)))
#define ZeroObject(obj)					ZeroMemory((&(obj)), sizeof(obj))

#define EXECUTE_RESET_ERROR(expr)		(::SetLastError(0), (expr))
#define EXECUTE_RESTORE_ERROR(expr)		{int __le_ = ::GetLastError(); (expr); ::SetLastError(__le_);}
inline int ENSURE_ERROR(int def_code)	{int __le_ = ::GetLastError(); if(__le_ == NO_ERROR) __le_ = (def_code);  return __le_;}
#define ENSURE_ERROR_CANCELLED			ENSURE_ERROR(ERROR_CANCELLED)
#define TRIGGER(expr)					EXECUTE_RESET_ERROR((expr))

#define CreateLocalObjects(T, n)		((T*)alloca(sizeof(T) * (n)))
#define CreateLocalObject(T)			CreateLocalObjects(T, 1)
#define CallocObjects(T, n)				((T*)calloc((n), sizeof(T)))

#define MALLOC(T, n)					((T*)malloc(sizeof(T) * (n)))
#define REALLOC(T, p, n)				((T*)realloc((PVOID)(p), sizeof(T) * (n)))
#define FREE(p)							free((PVOID)(p))
#define CALLOC(n, s)					calloc((n), (s))

#define ERROR_EXIT2(code, err)			EXIT((code), (err), __FILE__, __LINE__, __FUNCTION__)
#define ERROR__EXIT2(code, err)			_EXIT((code), (err), __FILE__, __LINE__, __FUNCTION__)
#define ERROR_ABORT2(err)				ABORT((err), __FILE__, __LINE__, __FUNCTION__)

#define ERROR_EXIT(code)				ERROR_EXIT2((code), -1)
#define ERROR__EXIT(code)				ERROR__EXIT2((code), -1)
#define ERROR_ABORT()					ERROR_ABORT2(-1)

typedef HANDLE							FD;
#define INVALID_FD						INVALID_HANDLE_VALUE
#define IS_VALID_FD(fd)					((fd) != INVALID_FD)
#define IS_INVALID_FD(fd)				(!IS_VALID_FD(fd))

#define INVALID_PVOID					INVALID_HANDLE_VALUE
#define IS_VALID_PVOID(pv)				((pv) != INVALID_PVOID)
#define IS_INVALID_PVOID(pv)			(!IS_VALID_PVOID(pv))

#define TO_PVOID(v)						((PVOID)(UINT_PTR)(v))
#define FROM_PVOID(T, pv)				((T)(UINT_PTR)(pv))

#define IS_NULL(v)						((v) == nullptr)
#define IS_NOT_NULL(v)					(!IS_NULL(v))

#define HEX_CHAR_TO_VALUE(c)			(c <= '9' ? c - '0' : (c <= 'F' ? c - 'A' + 0x0A : c - 'a' + 0X0A))
#define HEX_DOUBLE_CHAR_TO_VALUE(pc)	((BYTE)(((HEX_CHAR_TO_VALUE(*(pc))) << 4) | (HEX_CHAR_TO_VALUE(*((pc) + 1)))))
#define HEX_VALUE_TO_CHAR(n)			(n <= 9 ? n + '0' : (n <= 'F' ? n + 'A' - 0X0A : n + 'a' - 0X0A))
#define HEX_VALUE_TO_DOUBLE_CHAR(pc, n)	{*(pc) = (BYTE)HEX_VALUE_TO_CHAR((n >> 4)); *((pc) + 1) = (BYTE)HEX_VALUE_TO_CHAR((n & 0X0F));}

inline BOOL IsStrEmptyA(LPCSTR lpsz)	{return (lpsz == nullptr || lpsz[0] == 0);}
inline BOOL IsStrEmptyW(LPCWSTR lpsz)	{return (lpsz == nullptr || lpsz[0] == 0);}
inline BOOL IsStrNotEmptyA(LPCSTR lpsz)	{return !IsStrEmptyA(lpsz);}
inline BOOL IsStrNotEmptyW(LPCWSTR lpsz){return !IsStrEmptyW(lpsz);}
inline LPCSTR SafeStrA(LPCSTR lpsz)		{return (lpsz != nullptr) ? lpsz : "";}
inline LPCWSTR SafeStrW(LPCWSTR lpsz)	{return (lpsz != nullptr) ? lpsz : L"";}

#ifdef _UNICODE
	#define IsStrEmpty(lpsz)			IsStrEmptyW(lpsz)
	#define IsStrNotEmpty(lpsz)			IsStrNotEmptyW(lpsz)
	#define SafeStr(lpsz)				SafeStrW(lpsz)
#else
	#define IsStrEmpty(lpsz)			IsStrEmptyA(lpsz)
	#define IsStrNotEmpty(lpsz)			IsStrNotEmptyA(lpsz)
	#define SafeStr(lpsz)				SafeStrA(lpsz)
#endif

#define ARRAY_SIZE(arr)					_countof(arr)

#ifndef __countof
	#define __countof(arr)				ARRAY_SIZE(arr)
#endif

#ifndef MAX
	#define MAX(a,b)					max(a,b)
#endif

#ifndef MIN
	#define MIN(a,b)					min(a,b)
#endif

template<typename T> inline bool IS_HAS_ERROR(T v)
{
	return v == (T)HAS_ERROR;
}

template<typename T> inline bool IS_NO_ERROR(T v)
{
	return v == (T)NO_ERROR;
}

template<typename T1, typename T2> inline void CopyPlainObject(T1* p1, const T2* p2)
{
	CopyMemory(p1, p2, sizeof(T1));
}

void EXIT(int iExitCode = 0, int iErrno = -1, LPCSTR lpszFile = nullptr, int iLine = 0, LPCSTR lpszFunc = nullptr, LPCSTR lpszTitle = nullptr);
void _EXIT(int iExitCode = 0, int iErrno = -1, LPCSTR lpszFile = nullptr, int iLine = 0, LPCSTR lpszFunc = nullptr, LPCSTR lpszTitle = nullptr);
void ABORT(int iErrno = -1, LPCSTR lpszFile = nullptr, int iLine = 0, LPCSTR lpszFunc = nullptr, LPCSTR lpszTitle = nullptr);

BOOL SetSequenceThreadName(HANDLE hThread, LPCTSTR lpszPrefix, volatile UINT& vuiSeq);
BOOL SetThreadName(HANDLE hThread, LPCTSTR lpszPrefix, UINT uiSequence);
BOOL SetThreadName(HANDLE hThread, LPCTSTR lpszName);


/* ========================================================================== */
/*  WaitFor.h
/*  source: Windows\Src\Common\WaitFor.h
/* ========================================================================== */

#pragma once

/* timeGetTime() 包装方法 */
DWORD TimeGetTime();

/**********************************
描述: 获取当前时间与原始时间的时间差
参数: 
		dwOriginal	: 原始时间（毫秒），通常用 timeGetTime() 或 GetTickCount() 获取
		dwCurrent	: 当前时间（毫秒），通常用 timeGetTime() 或 GetTickCount() 获取

返回值:	与当前 timeGetTime() 之间的时间差
**********************************/
DWORD GetTimeGap32(DWORD dwOriginal, DWORD dwCurrent = 0);

#if _WIN32_WINNT >= _WIN32_WINNT_WS08
/**********************************
描述: 获取当前时间与原始时间的时间差
参数: 
		ullOriginal	: 原始时间（毫秒），通常用 GetTickCount64() 获取
		ullCurrent	: 当前时间（毫秒），通常用 GetTickCount64() 获取

返回值:	与当前 GetTickCount64() 之间的时间差
**********************************/
ULONGLONG GetTimeGap64(ULONGLONG ullOriginal, ULONGLONG ullCurrent = 0);
#endif

/**********************************
描述: 处理Windows消息
参数: 
			bDispatchQuitMsg	: 是否转发 WM_QUIT 消息
									TRUE : 转发（默认）
									FALSE: 不转发，并返回 FALSE

返回值:		TRUE  : 收完消息
			FALSE : bDispatchQuitMsg 参数为 FALSE 并收到 WM_QUIT 消息		
**********************************/
BOOL PeekMessageLoop(BOOL bDispatchQuitMsg = TRUE);

/**********************************
描述: 等待指定时间, 同时处理Windows消息
参数: (参考: MsgWaitForMultipleObjectsEx() )
		dwHandles		: 数组元素个数
		szHandles		: 对象句柄数组
		dwMilliseconds	: 等待时间 (毫秒)
		dwWakeMask		: 消息过滤标识
		dwFlags			: 等待类型

返回值: (0 ~ dwHandles - 1): 等待成功
		WAIT_TIMEOUT		: 超时
		WAIT_FAILED			: 执行失败
**********************************/
DWORD WaitForMultipleObjectsWithMessageLoop(DWORD dwHandles, HANDLE szHandles[], DWORD dwMilliseconds = INFINITE, BOOL bWaitAll = FALSE, DWORD dwWakeMask = QS_ALLINPUT);

/**********************************
描述: 等待指定时间, 同时处理Windows消息
参数: (参考: MsgWaitForMultipleObjectsEx() )
		hHandle			: 对象句柄
		dwMilliseconds	: 等待时间 (毫秒)
		dwWakeMask		: 消息过滤标识
		dwFlags			: 等待类型

返回值: TRUE: 等待成功，FALSE: 超时		
**********************************/
BOOL MsgWaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds = INFINITE, BOOL bWaitAll = FALSE, DWORD dwWakeMask = QS_ALLINPUT);

/**********************************
描述: 等待指定时间		
返回值: (无)		
**********************************/
BOOL WaitFor(DWORD dwMilliseconds);

/**********************************
描述: 等待指定时间, 同时处理Windows消息
参数: (参考: MsgWaitForMultipleObjectsEx() )
		dwMilliseconds	: 等待时间 (毫秒)
		dwWakeMask		: 消息过滤标识
		dwFlags			: 等待类型

返回值: (无)		
**********************************/
BOOL WaitWithMessageLoop(DWORD dwMilliseconds, DWORD dwWakeMask = QS_ALLINPUT);

/**********************************
描述: 等待某个变量小于指定值
参数: 
		plWorkingItemCount		: 监视变量
		lMaxWorkingItemCount	: 指定值
		dwCheckInterval			: 检查间隔 (毫秒)

返回值: 		
**********************************/
void WaitForWorkingQueue(long* plWorkingItemCount, long lMaxWorkingItemCount, DWORD dwCheckInterval);
/**********************************
描述: 等待某个变量减小到 0
参数: 
		plWorkingItemCount		: 监视变量
		dwCheckInterval			: 检查间隔 (毫秒)

返回值: 		
**********************************/
void WaitForComplete	(long* plWorkingItemCount, DWORD dwCheckInterval);

/**********************************
描述: 等待用WaitWithMessageLoop()函数等待某个变量小于指定值
参数: 
		plWorkingItemCount		: 监视变量
		lMaxWorkingItemCount	: 指定值
		dwCheckInterval			: 检查间隔 (毫秒)

返回值: 		
**********************************/
void MsgWaitForWorkingQueue	(long* plWorkingItemCount, long lMaxWorkingItemCount, DWORD dwCheckInterval = 10);
/**********************************
描述: 等待用WaitWithMessageLoop()函数等待某个变量减小到 0
参数: 
		plWorkingItemCount		: 监视变量
		dwCheckInterval			: 检查间隔 (毫秒)

返回值: 		
**********************************/
void MsgWaitForComplete		(long* plWorkingItemCount, DWORD dwCheckInterval = 10);

/**********************************
描述: 设置时钟分辨率
**********************************/
class CTimePeriod
{
public:
	CTimePeriod(UINT uiPeriod = 0);
	~CTimePeriod();

	BOOL IsValid() {return m_uiPeriod != 0;}

private:
	UINT m_uiPeriod;
};

/* ========================================================================== */
/*  STLHelper.h
/*  source: Windows\Src\Common\STLHelper.h
/* ========================================================================== */

#pragma once

/* [amalgamated] #include "GeneralHelper.h" */

#if _MSC_VER >= 1930
	#if !defined(_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS)
		#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
	#endif
#endif

#include <memory>
#include <string>
#include <functional>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <xhash>
#include <list>
#include <set>
#include <map>

#if _MSC_VER >= 1500
	#include <unordered_set>
	#include <unordered_map>

	#define hash_set			unordered_set
	#define hash_map			unordered_map
	#define hash_multimap		unordered_multimap
#else
	#include <hash_set>
	#include <hash_map>

	#define unordered_set		hash_set
	#define unordered_map		hash_map
	#define unordered_multimap	hash_multimap
#endif

using namespace std;
using namespace stdext;

typedef	wstring		CStdStringW;
typedef string		CStdStringA;

#ifdef _UNICODE
	typedef	CStdStringW		CStdString;
#else
	typedef CStdStringA		CStdString;
#endif

typedef list<short>						short_list;
typedef list<int>						int_list;
typedef list<long>						long_list;
typedef list<__int64>					int64_list;
typedef list<unsigned short>			ushort_list;
typedef list<unsigned int>				uint_list;
typedef list<unsigned long>				ulong_list;
typedef list<unsigned __int64>			uint64_list;
typedef list<float>						float_list;
typedef list<double>					double_list;
typedef stack<short>					short_stack;
typedef stack<int>						int_stack;
typedef stack<long>						long_stack;
typedef stack<__int64>					int64_stack;
typedef stack<unsigned short>			ushort_stack;
typedef stack<unsigned int>				uint_stack;
typedef stack<unsigned long>			ulong_stack;
typedef stack<unsigned __int64>			uint64_stack;
typedef stack<float>					float_stack;
typedef stack<double>					double_stack;
typedef queue<short>					short_queue;
typedef queue<int>						int_queue;
typedef queue<long>						long_queue;
typedef queue<__int64>					int64_queue;
typedef queue<unsigned short>			ushort_queue;
typedef queue<unsigned int>				uint_queue;
typedef queue<unsigned long>			ulong_queue;
typedef queue<unsigned __int64>			uint64_queue;
typedef queue<float>					float_queue;
typedef queue<double>					double_queue;
typedef deque<short>					short_deque;
typedef deque<int>						int_deque;
typedef deque<long>						long_deque;
typedef deque<__int64>					int64_deque;
typedef deque<unsigned short>			ushort_deque;
typedef deque<unsigned int>				uint_deque;
typedef deque<unsigned long>			ulong_deque;
typedef deque<unsigned __int64>			uint64_deque;
typedef deque<float>					float_deque;
typedef deque<double>					double_deque;
typedef vector<short>					short_vector;
typedef vector<int>						int_vector;
typedef vector<long>					long_vector;
typedef vector<__int64>					int64_vector;
typedef vector<unsigned short>			ushort_vector;
typedef vector<unsigned int>			uint_vector;
typedef vector<unsigned long>			ulong_vector;
typedef vector<unsigned __int64>		uint64_vector;
typedef vector<float>					float_vector;
typedef vector<double>					double_vector;
typedef set<short>						short_set;
typedef set<int>						int_set;
typedef set<long>						long_set;
typedef set<__int64>					int64_set;
typedef set<unsigned short>				ushort_set;
typedef set<unsigned int>				uint_set;
typedef set<unsigned long>				ulong_set;
typedef set<unsigned __int64>			uint64_set;
typedef set<float>						float_set;
typedef set<double>						double_set;
typedef hash_set<short>					short_hash_set;
typedef hash_set<int>					int_hash_set;
typedef hash_set<long>					long_hash_set;
typedef hash_set<__int64>				int64_hash_set;
typedef hash_set<unsigned short>		ushort_hash_set;
typedef hash_set<unsigned int>			uint_hash_set;
typedef hash_set<unsigned long>			ulong_hash_set;
typedef hash_set<unsigned __int64>		uint64_hash_set;
typedef hash_set<float>					float_hash_set;
typedef hash_set<double>				double_hash_set;
typedef unordered_set<short>			short_unordered_set;
typedef unordered_set<int>				int_unordered_set;
typedef unordered_set<long>				long_unordered_set;
typedef unordered_set<__int64>			int64_unordered_set;
typedef unordered_set<unsigned short>	ushort_unordered_set;
typedef unordered_set<unsigned int>		uint_unordered_set;
typedef unordered_set<unsigned long>	ulong_unordered_set;
typedef unordered_set<unsigned __int64>	uint64_unordered_set;
typedef unordered_set<float>			float_unordered_set;
typedef unordered_set<double>			double_unordered_set;

typedef list<INT_PTR>					int_ptr_list;
typedef list<LONG_PTR>					long_ptr_list;
typedef list<UINT_PTR>					uint_ptr_list;
typedef list<ULONG_PTR>					ulong_ptr_list;
typedef stack<INT_PTR>					int_ptr_stack;
typedef stack<LONG_PTR>					long_ptr_stack;
typedef stack<UINT_PTR>					uint_ptr_stack;
typedef stack<ULONG_PTR>				ulong_ptr_stack;
typedef queue<INT_PTR>					int_ptr_queue;
typedef queue<LONG_PTR>					long_ptr_queue;
typedef queue<UINT_PTR>					uint_ptr_queue;
typedef queue<ULONG_PTR>				ulong_ptr_queue;
typedef deque<INT_PTR>					int_ptr_deque;
typedef deque<LONG_PTR>					long_ptr_deque;
typedef deque<UINT_PTR>					uint_ptr_deque;
typedef deque<ULONG_PTR>				ulong_ptr_deque;
typedef vector<INT_PTR>					int_ptr_vector;
typedef vector<LONG_PTR>				long_ptr_vector;
typedef vector<UINT_PTR>				uint_ptr_vector;
typedef vector<ULONG_PTR>				ulong_ptr_vector;
typedef set<INT_PTR>					int_ptr_set;
typedef set<LONG_PTR>					long_ptr_set;
typedef set<UINT_PTR>					uint_ptr_set;
typedef set<ULONG_PTR>					ulong_ptr_set;
typedef hash_set<INT_PTR>				int_ptr_hash_set;
typedef hash_set<LONG_PTR>				long_ptr_hash_set;
typedef hash_set<UINT_PTR>				uint_ptr_hash_set;
typedef hash_set<ULONG_PTR>				ulong_ptr_hash_set;
typedef unordered_set<INT_PTR>			int_ptr_unordered_set;
typedef unordered_set<LONG_PTR>			long_ptr_unordered_set;
typedef unordered_set<UINT_PTR>			uint_ptr_unordered_set;
typedef unordered_set<ULONG_PTR>		ulong_ptr_unordered_set;

/*****************************************************************************/
/******************************** 容器操作函数 *******************************/

/**********************************
描述: 清除普通集合 , 适用于 vector<Object> / list<Object>
参数: 
	v		: vector / list / set

返回值: 		
**********************************/
template<class Set> void ClearSet(Set& v)
{
	v.clear();
}

template<class Set> struct Set_Cleaner
{
	static void Clear(Set& v) {ClearSet(v);}
};

/**********************************
描述: 清除指针集合 (清除前先释放指针), 适用于 vector<Object*> / list<Object*>
参数: 
		v		: vector / list / set

返回值: 		
**********************************/
template<class PtrSet> void ClearPtrSet(PtrSet& v)
{
	for(PtrSet::iterator	it	= v.begin(),
							end	= v.end(); 
							it != end;
							++it)
		delete (*it);

	v.clear();
}

template<class PtrSet> struct PtrSet_Cleaner
{
	static void Clear(PtrSet& v) {ClearPtrSet(v);}
};

/**********************************
描述: 清除指针集合 (指针同时又指向数组), 适用于 vector<Object*[]> / list<Object*[]>
参数: 
		v		: vector / list / set

返回值: 		
**********************************/
template<class PtrArraySet> void ClearPtrArraySet(PtrArraySet& v)
{
	for(PtrArraySet::iterator	it	= v.begin(),
								end	= v.end(); 
								it != end;
								++it)
		delete[] (*it);

	v.clear();
}

template<class PtrArraySet> struct PtrArraySet_Cleaner
{
	static void Clear(PtrArraySet& v) {ClearPtrArraySet(v);}
};

/**********************************
描述: 清除普通影射 , 适用于 map<key, value>
参数: 
	v		: map

返回值: 		
**********************************/
template<class Map> void ClearMap(Map& v)
{
	v.clear();
}

template<class Map> struct Map_Cleaner
{
	static void Clear(Map& v) {ClearMap(v);}
};

/**********************************
描述: 清除指针影射 (清除前先释放指针), 适用于 map<key, Object*>
参数: 
		v		: map

返回值: 		
**********************************/
template<class PtrMap> void ClearPtrMap(PtrMap& v)
{
	for(PtrMap::iterator	it	= v.begin(),
							end	= v.end(); 
							it != end;
							++it)
		delete it->second;

	v.clear();
}

template<class PtrMap> struct PtrMap_Cleaner
{
	static void Clear(PtrMap& v) {ClearPtrMap(v);}
};

/**********************************
描述: 清除指针影射 (指针同时又指向数组), 适用于 map<key, Object*[]>
参数: 
		v		: map

返回值: 		
**********************************/
template<class PtrArrayMap> void ClearPtrArrayMap(PtrArrayMap& v)
{
	for(PtrArrayMap::iterator	it	= v.begin(),
								end	= v.end(); 
								it != end;
								++it)
		delete[] it->second;

	v.clear();
}

template<class PtrArrayMap> struct PtrArrayMap_Cleaner
{
	static void Clear(PtrArrayMap& v) {ClearPtrArrayMap(v);}
};

/**********************************
描述: 清除集合-集合 (清除前先清除内部集合), 适用于 set<vector<Object>*>
参数: 
		v		: vector / list / set

返回值: 		
**********************************/
template<class SetSet> void ClearSetSet(SetSet& v)
{
	for(SetSet::iterator	it	= v.begin(),
							end	= v.end(); 
							it != end;
							++it)
	{
		(*it)->clear();
		delete (*it);
	}

	v.clear();
}

template<class SetSet> struct SetSet_Cleaner
{
	static void Clear(SetSet& v) {ClearSetSet(v);}
};

/**********************************
描述: 清除指针集合-集合 (清除前先清除内部指针集合), 适用于 set<vector<Object*>*>
参数: 
		v		: vector / list / set

返回值: 		
**********************************/
template<class PtrSetSet> void ClearPtrSetSet(PtrSetSet& v)
{
	for(PtrSetSet::iterator	it	= v.begin(),
							end	= v.end(); 
							it != end;
							++it)
	{
		ClearPtrSet(**it);
		delete (*it);
	}

	v.clear();
}

template<class PtrSetSet> struct PtrSetSet_Cleaner
{
	static void Clear(PtrSetSet& v) {ClearPtrSetSet(v);}
};

/**********************************
描述: 清除指针数组集合影射 (清除前先清除指针数组集合), 适用于 map<vector<Object*[]>*>
参数: 
		v		: vector / list / set

返回值: 		
**********************************/
template<class PtrArraySetSet> void ClearPtrArraySetSet(PtrArraySetSet& v)
{
	for(PtrArraySetSet::iterator	it	= v.begin(),
									end	= v.end(); 
									it != end;
									++it)
	{
		ClearPtrArraySet(**it);
		delete (*it);
	}

	v.clear();
}

template<class PtrArraySetSet> struct PtrArraySetSet_Cleaner
{
	static void Clear(PtrArraySetSet& v) {ClearPtrArraySetSet(v);}
};

/**********************************
描述: 清除集合影射 (清除前先清除集合), 适用于 map<key, vector<Object>*>
参数: 
		v		: map

返回值: 		
**********************************/
template<class SetMap> void ClearSetMap(SetMap& v)
{
	for(SetMap::iterator	it	= v.begin(),
							end	= v.end(); 
							it != end;
							++it)
	{
		it->second->clear();
		delete it->second;
	}

	v.clear();
}

template<class SetMap> struct SetMap_Cleaner
{
	static void Clear(SetMap& v) {ClearSetMap(v);}
};

/**********************************
描述: 清除指针集合影射 (清除前先清除指针集合), 适用于 map<key, vector<Object*>*>
参数: 
		v		: map

返回值: 		
**********************************/
template<class PtrSetMap> void ClearPtrSetMap(PtrSetMap& v)
{
	for(PtrSetMap::iterator	it	= v.begin(),
							end	= v.end(); 
							it != end;
							++it)
	{
		ClearPtrSet(*(it->second));
		delete it->second;
	}

	v.clear();
}

template<class PtrSetMap> struct PtrSetMap_Cleaner
{
	static void Clear(PtrSetMap& v) {ClearPtrSetMap(v);}
};

/**********************************
描述: 清除指针数组集合影射 (清除前先清除指针数组集合), 适用于 map<key, vector<Object*[]>*>
参数: 
		v		: map

返回值: 		
**********************************/
template<class PtrArraySetMap> void ClearPtrArraySetMap(PtrArraySetMap& v)
{
	for(PtrArraySetMap::iterator	it	= v.begin(),
									end	= v.end(); 
									it != end;
									++it)
	{
		ClearPtrArraySet(*(it->second));
		delete it->second;
	}

	v.clear();
}

template<class PtrArraySetMap> struct PtrArraySetMap_Cleaner
{
	static void Clear(PtrArraySetMap& v) {ClearPtrArraySetMap(v);}
};

/**********************************
描述: 清除映射-影射 (清除前先清除内部映射), 适用于 map<key, map<key2, Object>*>
参数: 
v		: map

返回值: 		
**********************************/
template<class MapMap> void ClearMapMap(MapMap& v)
{
	for(MapMap::iterator	it	= v.begin(),
							end	= v.end(); 
							it != end;
							++it)
	{
		it->second->clear();
		delete it->second;
	}

	v.clear();
}

template<class MapMap> struct MapMap_Cleaner
{
	static void Clear(MapMap& v) {ClearMapMap(v);}
};

/**********************************
描述: 清除指针映射-影射 (清除前先清除指针内部映射), 适用于 map<key, map<key2, Object*>*>
参数: 
		v		: map

返回值: 		
**********************************/
template<class PtrMapMap> void ClearPtrMapMap(PtrMapMap& v)
{
	for(PtrMapMap::iterator	it	= v.begin(),
							end	= v.end(); 
							it != end;
							++it)
	{
		ClearPtrMap(*(it->second));
		delete it->second;
	}

	v.clear();
}

template<class PtrMapMap> struct PtrMapMap_Cleaner
{
	static void Clear(PtrMapMap& v) {ClearPtrMapMap(v);}
};

/**********************************
描述: 清除指针映射-影射 (清除前先清除指针数组内部映射), 适用于 map<key, map<key2, Object*[]>*>
参数: 
		v		: map

返回值: 		
**********************************/
template<class PtrArrayMapMap> void ClearPtrArrayMapMap(PtrArrayMapMap& v)
{
	for(PtrArrayMapMap::iterator	it	= v.begin(),
									end	= v.end(); 
									it != end;
									++it)
	{
		ClearPtrArrayMap(*(it->second));
		delete it->second;
	}

	v.clear();
}

template<class PtrArrayMapMap> struct PtrArrayMapMap_Cleaner
{
	static void Clear(PtrArrayMapMap& v) {ClearPtrArrayMapMap(v);}
};

/************************************************************************/
/*                           指针集合容器                               */
/************************************************************************/
template<class Set, class Cleaner> struct SetWrapper
{
	typedef typename Set::iterator			iterator;
	typedef typename Set::const_iterator	const_iterator;
	typedef typename Set::value_type		value_type;
	typedef typename Set::reference			reference;
	typedef typename Set::const_reference	const_reference;
	typedef typename Set::pointer			pointer;
	typedef typename Set::const_pointer		const_pointer;
	typedef typename Set::size_type			size_type;
	typedef typename Set::difference_type	difference_type;

	SetWrapper()
	{
	}

	virtual ~SetWrapper()
	{
		Clear();
	}

	void Clear()
	{
		if(!IsEmpty())
		{
			Cleaner::Clear(m_set);
		}
	}

	Set& operator *			()			{return m_set;}
	const Set& operator *	()	const	{return m_set;}
	Set* operator ->		()			{return &m_set;}
	const Set* operator ->	()	const	{return &m_set;}
	Set& Get				()			{return m_set;}
	operator Set&			()			{return m_set;}
	bool IsEmpty			()	const	{return m_set.empty();}
	size_t Size				()	const	{return m_set.size();}

protected:
	Set m_set;

	DECLARE_NO_COPY_CLASS(SetWrapper)
};

template<class Set, class Cleaner> struct VectorWrapper : public SetWrapper<Set, Cleaner>
{
	VectorWrapper()
	{
	}

	reference		operator []	(size_type i)			{return m_set[i];}
	const_reference operator []	(size_type i)	const	{return m_set[i];}

	DECLARE_NO_COPY_CLASS(VectorWrapper)
};

/************************************************************************/
/*                         指针数组集合容器                             */
/************************************************************************/


/************************************************************************/
/*                           指针映射容器                               */
/************************************************************************/
template<class Map, class Cleaner> struct MapWrapper
{
	typedef typename Map::iterator			iterator;
	typedef typename Map::const_iterator	const_iterator;
	typedef typename Map::key_type			key_type;
	typedef typename Map::mapped_type		mapped_type;
	typedef typename Map::value_type		value_type;
	typedef typename Map::reference			reference;
	typedef typename Map::const_reference	const_reference;
	typedef typename Map::pointer			pointer;
	typedef typename Map::size_type			size_type;
	typedef typename Map::difference_type	difference_type;

	MapWrapper()
	{
	}

	~MapWrapper()
	{
		Clear();
	}

	void Clear()
	{
		if(!IsEmpty())
		{
			Cleaner::Clear(m_map);
		}
	}

	Map&				operator *	()								{return m_map;}
	const Map&			operator *	()						const	{return m_map;}
	Map*				operator ->	()								{return &m_map;}
	const Map*			operator ->	()						const	{return &m_map;}
	mapped_type&		operator []	(const key_type& key)			{return m_map[key];}
	const mapped_type&	operator []	(const key_type& key)	const	{return m_map[key];}
	Map& Get			()			{return m_map;}
	operator Map&		()			{return m_map;}
	bool IsEmpty		()	const	{return m_map.empty();}
	size_t Size			()	const	{return m_map.size();}

private:
	Map m_map;

	DECLARE_NO_COPY_CLASS(MapWrapper)
};

/************************************************************************/
/*                            比较仿函数                                */
/************************************************************************/

template<class T> struct char_comparator
{
	typedef T	row_type;
	static row_type row_type_value(const T& v)		{return (row_type)v;}
	static bool equal_to(const T& v1, const T& v2)	{return strcmp(v1, v2) == 0;}
};

template<class T> struct char_nc_comparator
{
	typedef T	row_type;
	static row_type row_type_value(const T& v)		{return (row_type)v;}
	static bool equal_to(const T& v1, const T& v2)	{return _stricmp(v1, v2) == 0;}
};

template<class T> struct wchar_comparator
{
	typedef T	row_type;
	static row_type row_type_value(const T& v)		{return (row_type)v;}
	static bool equal_to(const T& v1, const T& v2)	{return wcscmp(v1, v2) == 0;}
};

template<class T> struct wchar_nc_comparator
{
	typedef T	row_type;
	static row_type row_type_value(const T& v)		{return (row_type)v;}
	static bool equal_to(const T& v1, const T& v2)	{return _wcsicmp(v1, v2) == 0;}
};

template<class T> struct cstring_comparator
{
	typedef typename T::PCXSTR	row_type;
	static row_type row_type_value(const T& v)		{return (row_type)v;}
	static bool equal_to(const T& v1, const T& v2)	{return v1.Compare(v2) == 0;}
};

template<class T> struct cstring_nc_comparator
{
	typedef typename T::PCXSTR	row_type;
	static row_type row_type_value(const T& v)		{return (row_type)v;}
	static bool equal_to(const T& v1, const T& v2)	{return v1.CompareNoCase(v2) == 0;}
};

// char/wchar_t/CStringX hash function
template<class T, class H> struct str_hash_func_t
{
	struct hash
	{
		size_t operator() (const T& t) const
		{
			return hash_value(H::row_type_value(t));
		}
	};

	struct equal_to
	{
		bool operator() (const T& t1, const T& t2) const
		{
			return H::equal_to(t1, t2);
		}
	};

};

// char/wchar_t/CStringX hash function (no case)
template<class T, class H, class B> struct str_nc_hash_func_t
{
	struct hash
	{
		size_t operator() (const T& t) const
		{
			size_t _Val		 = 2166136261U;
			H::row_type lpsz = H::row_type_value(t);
			B c;

			while((c = *lpsz++) != 0) 
			{
				if(c >= 'A' && c <= 'Z')
					c += 32;

				_Val = 16777619U * _Val ^ c;

			}

			return _Val;
		}
	};

	struct equal_to
	{
		bool operator() (const T& t1, const T& t2) const
		{
			return H::equal_to(t1, t2);
		}
	};

};

typedef str_hash_func_t<LPCSTR, char_comparator<LPCSTR>>						str_hash_func;
typedef str_hash_func_t<LPCWSTR, wchar_comparator<LPCWSTR>>						wstr_hash_func;
typedef str_hash_func_t<CStringA, cstring_comparator<CStringA>>					cstringa_hash_func;
typedef str_hash_func_t<CStringW, cstring_comparator<CStringW>>					cstringw_hash_func;
typedef str_nc_hash_func_t<LPCSTR, char_nc_comparator<LPCSTR>, char>			str_nc_hash_func;
typedef str_nc_hash_func_t<LPCWSTR, wchar_nc_comparator<LPCWSTR>, wchar_t>		wstr_nc_hash_func;
typedef str_nc_hash_func_t<CStringA, cstring_nc_comparator<CStringA>, char>		cstringa_nc_hash_func;
typedef str_nc_hash_func_t<CStringW, cstring_nc_comparator<CStringW>, wchar_t>	cstringw_nc_hash_func;

#ifdef _UNICODE
	typedef cstringw_hash_func		cstring_hash_func;
	typedef cstringw_nc_hash_func	cstring_nc_hash_func;
#else
	typedef cstringa_hash_func		cstring_hash_func;
	typedef cstringa_nc_hash_func	cstring_nc_hash_func;
#endif

struct bool_comp_func
{
	bool operator() (bool v1, bool v2) const
	{
		if(!v1)
			return false;
		if(v1 == v2)
			return false;

		return true;
	}
};

template<class T>
// T -> (signed / unsigned) short / int / long / __int64
struct integer_comp_func
{
	bool operator() (T v1, T v2) const
	{
		return v1 < v2;
	}
};

typedef integer_comp_func<short>				short_comp_func;
typedef integer_comp_func<int>					int_comp_func;
typedef integer_comp_func<long>					long_comp_func;
typedef integer_comp_func<__int64>				int64_comp_func;
typedef integer_comp_func<unsigned short>		ushort_comp_func;
typedef integer_comp_func<unsigned int>			uint_comp_func;
typedef integer_comp_func<unsigned long>		ulong_comp_func;
typedef integer_comp_func<unsigned __int64>		uint64_comp_func;

struct float_comp_func
{
	bool operator() (float v1, float v2) const
	{
		float disc	= v1 - v2;
		if(fabsf(disc) < 1E-5)
			return false;

		return disc < 0;
	}
};

struct double_comp_func
{
	bool operator() (double v1, double v2) const
	{
		double disc	= v1 - v2;
		if(fabs(disc) < 1E-8)
			return false;

		return disc < 0;
	}
};

template<class T, bool CASE = false>
// T -> (unsigned) char / wchar_t
struct character_comp_func
{
	bool operator() (T v1, T v2) const
	{
		if(!CASE)
		{
			if(v1 >= 'A' && v1 <= 'Z')	v1 += 32;
			if(v2 >= 'A' && v2 <= 'Z')	v2 += 32;
		}

		return v1 < v2;
	}
};

typedef character_comp_func<char, true>				char_case_comp_func;
typedef character_comp_func<unsigned char, true>	uchar_case_comp_func;
typedef character_comp_func<wchar_t, true>			wchar_case_comp_func;
typedef character_comp_func<char, false>			char_ucase_comp_func;
typedef character_comp_func<unsigned char, false>	uchar_ucase_comp_func;
typedef character_comp_func<wchar_t, false>			wchar_ucase_comp_func;

template<class T, bool CASE = false>
// T -> TCHAR* / CString
struct str_comp_func
{
	//比较函数。
	bool operator() (const T &A, const T &B) const
	{
		if(!CASE)
			return lstrcmpi((LPCTSTR)A, (LPCTSTR)B) < 0;
		else
			return lstrcmp((LPCTSTR)A, (LPCTSTR)B) < 0;
	}
};

typedef str_comp_func<LPCTSTR, true>		case_tchar_comp_func;
typedef str_comp_func<LPCTSTR, false>		uncase_tchar_comp_func;
typedef str_comp_func<CString, true>		case_string_comp_func;
typedef str_comp_func<CString, false>		uncase_string_comp_func;
typedef case_tchar_comp_func				tchar_ptr_case_comp_func;
typedef uncase_tchar_comp_func				tchar_ptr_ucase_comp_func;
typedef case_string_comp_func				string_case_comp_func;
typedef uncase_string_comp_func				string_ucase_comp_func;
/************************************************************************/
/*                            排序仿函数                                */
/************************************************************************/
template<bool ASC = true>
struct bool_sort_func
{
	bool operator() (bool v1, bool v2) const
	{
		if(v1 == v2)
			return false;

		bool result = !v1;
		return ASC ? result : !result;
	}
};

typedef bool_sort_func<true>	bool_asc_sort_func;
typedef bool_sort_func<false>	bool_desc_sort_func;

template<class T, bool ASC = true>
// T -> (signed / unsigned) short / int / long / __int64
struct integer_sort_func
{
	bool operator() (T v1, T v2) const
	{
		if(v1 == v2)
			return false;

		bool result = v1 < v2;
		return ASC ? result : !result;
	}
};

typedef integer_sort_func<short,			true>		short_asc_sort_func;
typedef integer_sort_func<unsigned short,	true>		ushort_asc_sort_func;
typedef integer_sort_func<int,				true>		int_asc_sort_func;
typedef integer_sort_func<unsigned int,		true>		uint_asc_sort_func;
typedef integer_sort_func<long,				true>		long_asc_sort_func;
typedef integer_sort_func<unsigned long,	true>		ulong_asc_sort_func;
typedef integer_sort_func<__int64,			true>		int64_asc_sort_func;
typedef integer_sort_func<unsigned __int64,	true>		uint64_asc_sort_func;
typedef integer_sort_func<short,			false>		short_desc_sort_func;
typedef integer_sort_func<unsigned short,	false>		ushort_desc_sort_func;
typedef integer_sort_func<int,				false>		int_desc_sort_func;
typedef integer_sort_func<unsigned int,		false>		uint_desc_sort_func;
typedef integer_sort_func<long,				false>		long_desc_sort_func;
typedef integer_sort_func<unsigned long,	false>		ulong_desc_sort_func;
typedef integer_sort_func<__int64,			false>		int64_desc_sort_func;
typedef integer_sort_func<unsigned __int64,	false>		uint64_desc_sort_func;

template<bool ASC = true>
struct float_sort_func
{
	bool operator() (float v1, float v2) const
	{
		float disc	= v1 - v2;
		if(fabsf(disc) < 1E-5)
			return false;

		bool result = disc < 0;
		return ASC ? result : !result;
	}
};

typedef float_sort_func<true>		float_asc_sort_func;
typedef float_sort_func<false>		float_desc_sort_func;

template<bool ASC = true>
struct double_sort_func
{
	bool operator() (double v1, double v2) const
	{
		double disc	= v1 - v2;
		if(fabs(disc) < 1E-8)
			return false;

		bool result = disc < 0;
		return ASC ? result : !result;
	}
};

typedef double_sort_func<true>		double_asc_sort_func;
typedef double_sort_func<false>		double_desc_sort_func;

template<class T, bool ASC = true, bool CASE = false>
// T -> (unsigned) char / wchar_t
struct character_sort_func
{
	bool operator() (T v1, T v2) const
	{
		if(!CASE)
		{
			if(v1 >= 'A' && v1 <= 'Z')	v1 += 32;
			if(v2 >= 'A' && v2 <= 'Z')	v2 += 32;
		}

		if(v1 == v2)
			return false;

		bool result = v1 < v2;
		return ASC ? result : !result;
	}
};

typedef character_sort_func<char, true, true>				char_asc_case_sort_func;
typedef character_sort_func<unsigned char, true, true>		uchar_asc_case_sort_func;
typedef character_sort_func<wchar_t, true, true>			wchar_asc_case_sort_func;
typedef character_sort_func<char, true, false>				char_asc_ucase_sort_func;
typedef character_sort_func<unsigned char, true, false>		uchar_asc_ucase_sort_func;
typedef character_sort_func<wchar_t, true, false>			wchar_asc_ucase_sort_func;
typedef character_sort_func<char, false, true>				char_desc_case_sort_func;
typedef character_sort_func<unsigned char, false, true>		uchar_desc_case_sort_func;
typedef character_sort_func<wchar_t, false, true>			wchar_desc_case_sort_func;
typedef character_sort_func<char, false, false>				char_desc_ucase_sort_func;
typedef character_sort_func<unsigned char, false, false>	uchar_desc_ucase_sort_func;
typedef character_sort_func<wchar_t, false, false>			wchar_desc_ucase_sort_func;

template<class T, bool ASC = true, bool CASE = false>
// T -> TCHAR* / CString
struct str_sort_func
{
	bool operator() (const T& v1, const T& v2) const
	{
		bool result;

		if(CASE)
		{
			int v = lstrcmp((LPCTSTR)v1, (LPCTSTR)v2);
			if(v == 0)
				result = false;
			else
				result = v < 0;
		}
		else
		{
			int v = lstrcmpi((LPCTSTR)v1, (LPCTSTR)v2);
			if(v == 0)
				result = false;
			else
				result = v < 0;
		}

		return ASC ? result : !result;
	}
};

typedef str_sort_func<TCHAR*, true, true>		tchar_ptr_asc_case_sort_func;
typedef str_sort_func<CString, true, true>		string_asc_case_sort_func;
typedef str_sort_func<TCHAR*, true, false>		tchar_ptr_asc_ucase_sort_func;
typedef str_sort_func<CString, true, false>		string_asc_ucase_sort_func;
typedef str_sort_func<TCHAR*, false, true>		tchar_ptr_desc_case_sort_func;
typedef str_sort_func<CString, false, true>		string_desc_case_sort_func;
typedef str_sort_func<TCHAR*, false, false>		tchar_ptr_desc_ucase_sort_func;
typedef str_sort_func<CString, false, false>	string_desc_ucase_sort_func;

/************************************************************************/
/*					   smart_ptr 单实体或数组智能指针                    */
/************************************************************************/

template<class _Ty>
struct simple_deleter
{
	static void delete_ptr(_Ty* pv) {delete pv;}
};

template<class _Ty>
struct global_simple_deleter
{
	static void delete_ptr(_Ty* pv) {::delete pv;}
};

template<class _Ty>
struct array_deleter
{
	static void delete_ptr(_Ty* pv) {delete[] pv;}
};

template<class _Ty>
struct global_array_deleter
{
	static void delete_ptr(_Ty* pv) {::delete[] pv;}
};

template<class _Ty, class _Deleter>
class smart_ptr
{
public:
	smart_ptr(_Ty* _Ptr = 0)					: _Myptr(_Ptr)				{}
	smart_ptr(smart_ptr<_Ty, _Deleter>& _Right)	: _Myptr(_Right.release())	{}

	~smart_ptr()
	{
		reset();
	}

	smart_ptr<_Ty, _Deleter>& reset(_Ty* _Ptr = 0)
	{
		if (_Ptr != _Myptr)
		{
			if(_Myptr)
				_Deleter::delete_ptr(_Myptr);

			_Myptr = _Ptr;
		}

		return *this;
	}

	smart_ptr<_Ty, _Deleter>& reset(smart_ptr<_Ty, _Deleter>& _Right)
	{
		if (this != &_Right)
			reset(_Right.release());

		return *this;
	}

	_Ty* release()
	{
		_Ty* _Ptr	= _Myptr;
		_Myptr		= 0;

		return _Ptr;
	}

	smart_ptr<_Ty, _Deleter>& operator = (_Ty* _Ptr)						{return reset(_Ptr);}
	smart_ptr<_Ty, _Deleter>& operator = (smart_ptr<_Ty, _Deleter>& _Right)	{return reset(_Right);}

	bool is_valid		()	const	{return _Myptr != 0;}
	_Ty& operator *		()	const	{return *_Myptr;}
	_Ty* get			()	const	{return _Myptr;}
	_Ty* operator ->	()	const	{return _Myptr;}
	operator _Ty*		()	const	{return _Myptr;}

private:
	template<class _Other> smart_ptr<_Ty, _Deleter>					(const smart_ptr<_Ty, _Other>&);
	template<class _Other> smart_ptr<_Ty, _Deleter>&	reset		(const smart_ptr<_Ty, _Other>&);
	template<class _Other> smart_ptr<_Ty, _Deleter>&	operator =	(const smart_ptr<_Ty, _Other>&);

	template<class _Other> smart_ptr<_Ty, _Deleter>					(const smart_ptr<_Other, _Deleter>&);
	template<class _Other> smart_ptr<_Ty, _Deleter>&	reset		(const smart_ptr<_Other, _Deleter>&);
	template<class _Other> smart_ptr<_Ty, _Deleter>&	operator =	(const smart_ptr<_Other, _Deleter>&);

protected:
	_Ty* _Myptr;
};


/************************************************************************/
/*				    smart_simple_ptr 单实体智能指针                      */
/************************************************************************/

template<class _Ty>
class smart_simple_ptr : public smart_ptr<_Ty, simple_deleter<_Ty>>
{
public:
	smart_simple_ptr(_Ty* _Ptr = 0)									: smart_ptr(_Ptr)	{}
	smart_simple_ptr(smart_simple_ptr<_Ty>& _Right)					: smart_ptr(_Right)	{}
	smart_simple_ptr(smart_ptr<_Ty, simple_deleter<_Ty>>& _Right)	: smart_ptr(_Right)	{}

	smart_simple_ptr<_Ty>& operator = (smart_ptr<_Ty, simple_deleter<_Ty>>& _Right)
	{return (smart_simple_ptr<_Ty>&)__super::operator = (_Right);}

	smart_simple_ptr<_Ty>& operator = (smart_simple_ptr<_Ty>& _Right)
	{return (smart_simple_ptr<_Ty>&)__super::operator = (_Right);}

	smart_simple_ptr<_Ty>& operator = (_Ty* _Ptr)
	{return (smart_simple_ptr<_Ty>&)__super::operator = (_Ptr);}

private:
	template<class _Other> smart_simple_ptr<_Ty>				(const smart_ptr<_Ty, _Other>&);
	template<class _Other> smart_simple_ptr<_Ty>&	operator =	(const smart_ptr<_Ty, _Other>&);

	template<class _Other> smart_simple_ptr<_Ty>				(const smart_simple_ptr<_Other>&);
	template<class _Other> smart_simple_ptr<_Ty>&	operator =	(const smart_simple_ptr<_Other>&);
};

/************************************************************************/
/*		   smart_gd_simple_ptr 单实体智能指针 (使用全局 delete)          */
/************************************************************************/

template<class _Ty>
class smart_gd_simple_ptr : public smart_ptr<_Ty, global_simple_deleter<_Ty>>
{
public:
	smart_gd_simple_ptr(_Ty* _Ptr = 0)										: smart_ptr(_Ptr)	{}
	smart_gd_simple_ptr(smart_gd_simple_ptr<_Ty>& _Right)					: smart_ptr(_Right)	{}
	smart_gd_simple_ptr(smart_ptr<_Ty, global_simple_deleter<_Ty>>& _Right)	: smart_ptr(_Right)	{}

	smart_gd_simple_ptr<_Ty>& operator = (smart_ptr<_Ty, global_simple_deleter<_Ty>>& _Right)
	{return (smart_gd_simple_ptr<_Ty>&)__super::operator = (_Right);}

	smart_gd_simple_ptr<_Ty>& operator = (smart_gd_simple_ptr<_Ty>& _Right)
	{return (smart_gd_simple_ptr<_Ty>&)__super::operator = (_Right);}

	smart_gd_simple_ptr<_Ty>& operator = (_Ty* _Ptr)
	{return (smart_gd_simple_ptr<_Ty>&)__super::operator = (_Ptr);}

private:
	template<class _Other> smart_gd_simple_ptr<_Ty>					(const smart_ptr<_Ty, _Other>&);
	template<class _Other> smart_gd_simple_ptr<_Ty>&	operator =	(const smart_ptr<_Ty, _Other>&);

	template<class _Other> smart_gd_simple_ptr<_Ty>					(const smart_gd_simple_ptr<_Other>&);
	template<class _Other> smart_gd_simple_ptr<_Ty>&	operator =	(const smart_gd_simple_ptr<_Other>&);
};

/************************************************************************/
/*                   smart_array_ptr 数组智能指针                        */
/************************************************************************/

template<class _Ty>
class smart_array_ptr : public smart_ptr<_Ty, array_deleter<_Ty>>
{
public:
	smart_array_ptr(_Ty* _Ptr = 0)								: smart_ptr(_Ptr)	{}
	smart_array_ptr(smart_simple_ptr<_Ty>& _Right)				: smart_ptr(_Right)	{}
	smart_array_ptr(smart_ptr<_Ty, array_deleter<_Ty>>& _Right)	: smart_ptr(_Right)	{}

	smart_array_ptr<_Ty>& operator = (smart_ptr<_Ty, array_deleter<_Ty>>& _Right)
	{return (smart_array_ptr<_Ty>&)__super::operator = (_Right);}

	smart_array_ptr<_Ty>& operator = (smart_array_ptr<_Ty>& _Right)
	{return (smart_array_ptr<_Ty>&)__super::operator = (_Right);}

	smart_array_ptr<_Ty>& operator = (_Ty* _Ptr)
	{return (smart_array_ptr<_Ty>&)__super::operator = (_Ptr);}

private:
	template<class _Other> smart_array_ptr<_Ty>					(const smart_ptr<_Ty, _Other>&);
	template<class _Other> smart_array_ptr<_Ty>&	operator =	(const smart_ptr<_Ty, _Other>&);

	template<class _Other> smart_array_ptr<_Ty>					(const smart_array_ptr<_Other>&);
	template<class _Other> smart_array_ptr<_Ty>&	operator =	(const smart_array_ptr<_Other>&);
};

/************************************************************************/
/*          smart_gd_array_ptr 单实体智能指针 (使用全局 delete)          */
/************************************************************************/

template<class _Ty>
class smart_gd_array_ptr : public smart_ptr<_Ty, global_array_deleter<_Ty>>
{
public:
	smart_gd_array_ptr(_Ty* _Ptr = 0)										: smart_ptr(_Ptr)	{}
	smart_gd_array_ptr(smart_gd_array_ptr<_Ty>& _Right)						: smart_ptr(_Right)	{}
	smart_gd_array_ptr(smart_ptr<_Ty, global_array_deleter<_Ty>>& _Right)	: smart_ptr(_Right)	{}

	smart_gd_array_ptr<_Ty>& operator = (smart_ptr<_Ty, global_array_deleter<_Ty>>& _Right)
	{return (smart_gd_array_ptr<_Ty>&)__super::operator = (_Right);}

	smart_gd_array_ptr<_Ty>& operator = (smart_gd_array_ptr<_Ty>& _Right)
	{return (smart_gd_array_ptr<_Ty>&)__super::operator = (_Right);}

	smart_gd_array_ptr<_Ty>& operator = (_Ty* _Ptr)
	{return (smart_gd_array_ptr<_Ty>&)__super::operator = (_Ptr);}

private:
	template<class _Other> smart_gd_array_ptr<_Ty>				(const smart_ptr<_Ty, _Other>&);
	template<class _Other> smart_gd_array_ptr<_Ty>&	operator =	(const smart_ptr<_Ty, _Other>&);

	template<class _Other> smart_gd_array_ptr<_Ty>				(const smart_gd_array_ptr<_Other>&);
	template<class _Other> smart_gd_array_ptr<_Ty>&	operator =	(const smart_gd_array_ptr<_Other>&);
};


/* ========================================================================== */
/*  Event.h
/*  source: Windows\Src\Common\Event.h
/* ========================================================================== */

#pragma once

#include <malloc.h>

class CEvt
{
public:
	CEvt(BOOL bManualReset = FALSE, BOOL bInitialState = FALSE, LPCTSTR lpszName = nullptr, LPSECURITY_ATTRIBUTES pSecurity = nullptr)
	{
		m_hEvent = ::CreateEvent(pSecurity, bManualReset, bInitialState, lpszName);
		ENSURE(IsValid());
	}

	~CEvt()
	{
		if(IsValid())
			ENSURE(::CloseHandle(m_hEvent));
	}

	BOOL Open(DWORD dwAccess, BOOL bInheritHandle, LPCTSTR lpszName)
	{
		if(IsValid())
			ENSURE(::CloseHandle(m_hEvent));

		m_hEvent = ::OpenEvent(dwAccess, bInheritHandle, lpszName);
		return(IsValid());
	}

	BOOL Wait(DWORD dwMilliseconds = INFINITE)
	{
		DWORD rs = ::WaitForSingleObject(m_hEvent, dwMilliseconds);

		if(rs == WAIT_TIMEOUT) ::SetLastError(WAIT_TIMEOUT);

		return (rs == WAIT_OBJECT_0);
	}

	BOOL Pulse()	{return(::PulseEvent(m_hEvent));}
	BOOL Reset()	{return(::ResetEvent(m_hEvent));}
	BOOL Set()		{return(::SetEvent(m_hEvent));}

	BOOL IsValid()	{return m_hEvent != nullptr;}

	HANDLE GetHandle		()			{return m_hEvent;}
	const HANDLE GetHandle	()	const	{return m_hEvent;}

	operator HANDLE			()			{return m_hEvent;}
	operator const HANDLE	()	const	{return m_hEvent;}

private:
	CEvt(const CEvt&);
	CEvt operator = (const CEvt&);

private:
	HANDLE m_hEvent;
};

class CTimerEvt
{
public:
	CTimerEvt(BOOL bManualReset = FALSE, LPCTSTR lpszName = nullptr, LPSECURITY_ATTRIBUTES pSecurity = nullptr)
	{
		m_hTimer = ::CreateWaitableTimer(pSecurity, bManualReset, lpszName);
		ENSURE(IsValid());
	}

	~CTimerEvt()
	{
		if(IsValid())
			ENSURE(::CloseHandle(m_hTimer));
	}

	BOOL Open(DWORD dwAccess, BOOL bInheritHandle, LPCTSTR lpszName)
	{
		if(IsValid())
			ENSURE(::CloseHandle(m_hTimer));

		m_hTimer = ::OpenWaitableTimer(dwAccess, bInheritHandle, lpszName);
		return(IsValid());
	}

	BOOL Set(LONG lPeriod, LARGE_INTEGER* lpDueTime = nullptr, BOOL bResume = FALSE, PTIMERAPCROUTINE pfnAPC = nullptr, LPVOID lpArg = nullptr)
	{
		if(lpDueTime == nullptr)
		{
			lpDueTime = (LARGE_INTEGER*)alloca(sizeof(LARGE_INTEGER));
			lpDueTime->QuadPart = -(lPeriod * 10000LL);
		}

		return ::SetWaitableTimer(m_hTimer, lpDueTime, lPeriod, pfnAPC, lpArg, bResume);
	}


	BOOL Reset()	{return(::CancelWaitableTimer(m_hTimer));}
	BOOL IsValid()	{return m_hTimer != nullptr;}

	HANDLE GetHandle		()			{return m_hTimer;}
	const HANDLE GetHandle	()	const	{return m_hTimer;}

	operator HANDLE			()			{return m_hTimer;}
	operator const HANDLE	()	const	{return m_hTimer;}

private:
	CTimerEvt(const CTimerEvt&);
	CTimerEvt operator = (const CTimerEvt&);

private:
	HANDLE m_hTimer;
};

class CTimerQueue
{
public:
	CTimerQueue()
	{
		Create();
	}

	~CTimerQueue()
	{
		Delete();
	}

	HANDLE CreateTimer(WAITORTIMERCALLBACK fnCallback, PVOID lpParam, DWORD dwPeriod, DWORD dwDueTime = INFINITE, ULONG ulFlags = WT_EXECUTEDEFAULT)
	{
		HANDLE hTimer = nullptr;

		if(dwDueTime == INFINITE)
			dwDueTime = dwPeriod;

		::CreateTimerQueueTimer(&hTimer, m_hTimerQueue, fnCallback, lpParam, dwDueTime, dwPeriod, ulFlags);

		return hTimer;
	}

	BOOL ChangeTimer(HANDLE hTimer, DWORD dwPeriod, DWORD dwDueTime = INFINITE)
	{
		if(dwDueTime == INFINITE)
			dwDueTime = dwPeriod;

		return ::ChangeTimerQueueTimer(m_hTimerQueue, hTimer, dwDueTime, dwPeriod);
	}

	BOOL DeleteTimer(HANDLE hTimer, HANDLE hCompletionEvent = INVALID_HANDLE_VALUE)
	{
		return ::DeleteTimerQueueTimer(m_hTimerQueue, hTimer, hCompletionEvent);
	}

	BOOL Reset()
	{
		Delete();
		Create();

		return IsValid();
	}

	BOOL IsValid()	{return m_hTimerQueue != nullptr;}

	HANDLE GetHandle		()			{return m_hTimerQueue;}
	const HANDLE GetHandle	()	const	{return m_hTimerQueue;}

	operator HANDLE			()			{return m_hTimerQueue;}
	operator const HANDLE	()	const	{return m_hTimerQueue;}

private:
	void Create()
	{
		m_hTimerQueue = ::CreateTimerQueue();
		ENSURE(IsValid());
	}

	void Delete()
	{
		if(IsValid())
		{
			ENSURE(::DeleteTimerQueueEx(m_hTimerQueue, INVALID_HANDLE_VALUE));
			m_hTimerQueue = nullptr;
		}
	}

private:
	CTimerQueue(const CTimerQueue&);
	CTimerQueue operator = (const CTimerQueue&);

private:
	HANDLE m_hTimerQueue;
};


/* ========================================================================== */
/*  Semaphore.h
/*  source: Windows\Src\Common\Semaphore.h
/* ========================================================================== */

#pragma once

class CSEM
{
public:
	CSEM(LONG lMaximumCount, LONG lInitialCount = 0, LPCTSTR lpName = nullptr, LPSECURITY_ATTRIBUTES pSecurity = nullptr)
	{
		m_hsem = ::CreateSemaphore(pSecurity, lInitialCount, lMaximumCount, lpName);
		ASSERT(IsValid());
	}

	~CSEM()
	{
		if(IsValid())
			ENSURE(::CloseHandle(m_hsem));
	}

	BOOL Open(DWORD dwAccess, BOOL bInheritHandle, LPCTSTR pszName)
	{
		if(IsValid())
			ENSURE(::CloseHandle(m_hsem));

		m_hsem = ::OpenSemaphore(dwAccess, bInheritHandle, pszName);
		return(IsValid());
	}

	void Wait(DWORD dwMilliseconds = INFINITE)
	{
		::WaitForSingleObject(m_hsem, dwMilliseconds);
	}

	BOOL Release(LONG lReleaseCount = 1, LPLONG lpPreviousCount = nullptr)
	{
		return ::ReleaseSemaphore(m_hsem, lReleaseCount, lpPreviousCount);
	}

	HANDLE& GetHandle	() 	{return m_hsem;}
	operator HANDLE		()	{return m_hsem;}
	BOOL IsValid		()	{return m_hsem != nullptr;}

private:
	CSEM(const CSEM& sem);
	CSEM operator = (const CSEM& sem);
private:
	HANDLE m_hsem;
};


/* ========================================================================== */
/*  CriticalSection.h
/*  source: Windows\Src\Common\CriticalSection.h
/* ========================================================================== */

#pragma once

#include <intrin.h>

#pragma intrinsic(_ReadBarrier)
#pragma intrinsic(_WriteBarrier)
#pragma intrinsic(_ReadWriteBarrier)

#define DEFAULT_CRISEC_SPIN_COUNT	0
#define THREAD_YIELD_CYCLE			63
#define THREAD_SWITCH_CYCLE			4095

#ifndef YieldProcessor
	#pragma intrinsic(_mm_pause)
	#define YieldProcessor _mm_pause
#endif

inline void YieldThread(UINT i = THREAD_YIELD_CYCLE)
{
	if((i & THREAD_SWITCH_CYCLE) == THREAD_SWITCH_CYCLE)
		::SwitchToThread();
	else if((i & THREAD_YIELD_CYCLE) == THREAD_YIELD_CYCLE)
		::YieldProcessor();
}

class CInterCriSec
{
public:
	CInterCriSec(DWORD dwSpinCount = DEFAULT_CRISEC_SPIN_COUNT)
		{ENSURE(::InitializeCriticalSectionAndSpinCount(&m_crisec, dwSpinCount));}
	~CInterCriSec()
		{::DeleteCriticalSection(&m_crisec);}

	void Lock()								{::EnterCriticalSection(&m_crisec);}
	void Unlock()							{::LeaveCriticalSection(&m_crisec);}
	BOOL TryLock()							{return ::TryEnterCriticalSection(&m_crisec);}
	DWORD SetSpinCount(DWORD dwSpinCount)	{return ::SetCriticalSectionSpinCount(&m_crisec, dwSpinCount);}

	CRITICAL_SECTION* GetObject()			{return &m_crisec;}

private:
	CInterCriSec(const CInterCriSec& cs);
	CInterCriSec operator = (const CInterCriSec& cs);

private:
	CRITICAL_SECTION m_crisec;
};

class CInterCriSec2
{
public:
	CInterCriSec2(DWORD dwSpinCount = DEFAULT_CRISEC_SPIN_COUNT, BOOL bInitialize = TRUE)
	{
		if(bInitialize)
		{
			m_pcrisec = new CRITICAL_SECTION;
			ENSURE(::InitializeCriticalSectionAndSpinCount(m_pcrisec, dwSpinCount));
		}
		else
			m_pcrisec = nullptr;
	}

	~CInterCriSec2() {Reset();}

	void Attach(CRITICAL_SECTION* pcrisec)
	{
		Reset();
		m_pcrisec = pcrisec;
	}

	CRITICAL_SECTION* Detach()
	{
		CRITICAL_SECTION* pcrisec = m_pcrisec;
		m_pcrisec = nullptr;
		return pcrisec;
	}

	void Lock()								{::EnterCriticalSection(m_pcrisec);}
	void Unlock()							{::LeaveCriticalSection(m_pcrisec);}
	BOOL TryLock()							{return ::TryEnterCriticalSection(m_pcrisec);}
	DWORD SetSpinCount(DWORD dwSpinCount)	{return ::SetCriticalSectionSpinCount(m_pcrisec, dwSpinCount);}

	CRITICAL_SECTION* GetObject()			{return m_pcrisec;}

private:
	CInterCriSec2(const CInterCriSec2& cs);
	CInterCriSec2 operator = (const CInterCriSec2& cs);

	void Reset()
	{
		if(m_pcrisec)
		{
			::DeleteCriticalSection(m_pcrisec);
			delete m_pcrisec;
			m_pcrisec = nullptr;
		}
	}

private:
	CRITICAL_SECTION* m_pcrisec;
};

class CMTX
{
public:
	CMTX(BOOL bInitialOwner = FALSE, LPCTSTR pszName = nullptr, LPSECURITY_ATTRIBUTES pSecurity = nullptr)	
	{
		m_hMutex = ::CreateMutex(pSecurity, bInitialOwner, pszName);
		ASSERT(IsValid());
	}

	~CMTX()
	{
		if(IsValid())
			::CloseHandle(m_hMutex);
	}

	BOOL Open(DWORD dwAccess, BOOL bInheritHandle, LPCTSTR pszName)
	{
		if(IsValid())
			ENSURE(::CloseHandle(m_hMutex));

		m_hMutex = ::OpenMutex(dwAccess, bInheritHandle, pszName);
		return(IsValid());
	}

	void Lock(DWORD dwMilliseconds = INFINITE)	{::WaitForSingleObject(m_hMutex, dwMilliseconds);}
	void Unlock()								{::ReleaseMutex(m_hMutex);}

	HANDLE& GetHandle	() 	{return m_hMutex;}
	operator HANDLE		()	{return m_hMutex;}
	BOOL IsValid		()	{return m_hMutex != nullptr;}

private:
	CMTX(const CMTX& mtx);
	CMTX operator = (const CMTX& mtx);

private:
	HANDLE m_hMutex;
};

class CSpinGuard
{
public:
	CSpinGuard() : m_lFlag(0)
	{

	}

	~CSpinGuard()
	{
		ASSERT(m_lFlag == 0);
	}

	void Lock()
	{
		for(UINT i = 0; !TryLock(); ++i)
			YieldThread(i);
	}

	BOOL TryLock()
	{
		if(::InterlockedCompareExchange(&m_lFlag, 1, 0) == 0)
		{
			::_ReadWriteBarrier();
			return TRUE;
		}

		return FALSE;
	}

	void Unlock()
	{
		ASSERT(m_lFlag == 1);
		m_lFlag = 0;
	}

private:
	CSpinGuard(const CSpinGuard& cs);
	CSpinGuard operator = (const CSpinGuard& cs);

private:
	volatile LONG m_lFlag;
};

class CReentrantSpinGuard
{
public:
	CReentrantSpinGuard()
	: m_dwThreadID	(0)
	, m_iCount		(0)
	{

	}

	~CReentrantSpinGuard()
	{
		ASSERT(m_dwThreadID	== 0);
		ASSERT(m_iCount		== 0);
	}

	void Lock()
	{
		for(UINT i = 0; !_TryLock(i == 0); ++i)
			YieldThread(i);
	}

	BOOL TryLock()
	{
		return _TryLock(TRUE);
	}

	void Unlock()
	{
		ASSERT(m_dwThreadID == ::GetCurrentThreadId());

		if((--m_iCount) == 0)
			m_dwThreadID = 0;
	}

private:
	CReentrantSpinGuard(const CReentrantSpinGuard& cs);
	CReentrantSpinGuard operator = (const CReentrantSpinGuard& cs);

	BOOL _TryLock(BOOL bFirst)
	{
		DWORD dwCurrentThreadID = ::GetCurrentThreadId();

		if(bFirst && m_dwThreadID == dwCurrentThreadID)
		{
			++m_iCount;
			return TRUE;
		}

		if(::InterlockedCompareExchange(&m_dwThreadID, dwCurrentThreadID, 0) == 0)
		{
			::_ReadWriteBarrier();
			ASSERT(m_iCount == 0);

			m_iCount = 1;

			return TRUE;
		}

		return FALSE;
	}

private:
	volatile DWORD	m_dwThreadID;
	int				m_iCount;
};

class CFakeGuard
{
public:
	void Lock()		{}
	void Unlock()	{}
	BOOL TryLock()	{return TRUE;}
};

#if _WIN32_WINNT >= _WIN32_WINNT_WS08

class CSlimCriSec
{
public:
	CSlimCriSec()			{::InitializeSRWLock(&m_crisec);}
	~CSlimCriSec()			{}

	void Lock()				{::AcquireSRWLockExclusive(&m_crisec);}
	void Unlock()			{::ReleaseSRWLockExclusive(&m_crisec);}
	BOOL TryLock()			{return ::TryAcquireSRWLockExclusive(&m_crisec);}

	SRWLOCK* GetObject()	{return &m_crisec;}

private:
	CSlimCriSec(const CSlimCriSec& cs);
	CSlimCriSec operator = (const CSlimCriSec& cs);

private:
	SRWLOCK m_crisec;
};

class CConVar
{
public:
	void WakeUp()		{::WakeConditionVariable(&m_cv);}
	void WakeUpAll()	{::WakeAllConditionVariable(&m_cv);}

	BOOL Wait(CRITICAL_SECTION* pLock, DWORD dwMilliseconds = INFINITE)
	{
		return ::SleepConditionVariableCS(&m_cv, pLock, dwMilliseconds);
	}

	BOOL Wait(SRWLOCK* pLock, DWORD dwMilliseconds = INFINITE)
	{
		return ::SleepConditionVariableSRW(&m_cv, pLock, dwMilliseconds, 0);
	}

public:
	CConVar()	{::InitializeConditionVariable(&m_cv);}
	~CConVar()	{}
private:
	CConVar(const CConVar& cs);
	CConVar operator = (const CConVar& cs);

private:
	CONDITION_VARIABLE m_cv;
};

#endif

template<class CLockObj> class CLocalLock
{
public:
	CLocalLock(CLockObj& obj) : m_lock(obj) {m_lock.Lock();}
	~CLocalLock() {m_lock.Unlock();}
private:
	CLockObj& m_lock;
};

template<class CLockObj> class CLocalTryLock
{
public:
	CLocalTryLock(CLockObj& obj) : m_lock(obj) {m_bValid = m_lock.TryLock();}
	~CLocalTryLock() {if(m_bValid) m_lock.Unlock();}

	BOOL IsValid() {return m_bValid;}

private:
	CLockObj&	m_lock;
	BOOL		m_bValid;
};

typedef CInterCriSec						CCriSec;

typedef CLocalLock<CCriSec>					CCriSecLock;
typedef CLocalLock<CInterCriSec>			CInterCriSecLock;
typedef CLocalLock<CInterCriSec2>			CInterCriSecLock2;
typedef CLocalLock<CMTX>					CMutexLock;
typedef CLocalLock<CSpinGuard>				CSpinLock;
typedef CLocalLock<CReentrantSpinGuard>		CReentrantSpinLock;
typedef	CLocalLock<CFakeGuard>				CFakeLock;

typedef CLocalTryLock<CCriSec>				CCriSecTryLock;
typedef CLocalTryLock<CInterCriSec>			CInterCriSecTryLock;
typedef CLocalTryLock<CInterCriSec2>		CInterCriSecTryLock2;
typedef CLocalTryLock<CMTX>					CMutexTryLock;
typedef CLocalTryLock<CSpinGuard>			CSpinTryLock;
typedef CLocalTryLock<CReentrantSpinGuard>	CReentrantSpinTryLock;
typedef	CLocalTryLock<CFakeGuard>			CFakeTryLock;

template<typename T> class CSafeCounterT
{
public:
	T Increment()				{return IncrementImpl<sizeof(T)>();}
	T Decrement()				{return DecrementImpl<sizeof(T)>();}
	T FetchAdd(T iCount)		{return FetchAddImpl<sizeof(T)>(iCount);}
	T FetchSub(T iCount)		{return FetchSubImpl<sizeof(T)>(iCount);}
	T AddFetch(T iCount)		{return FetchAdd(iCount) + iCount;}
	T SubFetch(T iCount)		{return FetchSub(iCount) - iCount;}

	T SetCount(T iCount)		{return (m_iCount = iCount);}
	T ResetCount(T iCount = 0)	{return SetCount(iCount);}
	T GetCount()				{return m_iCount;}

	T operator ++ ()			{return Increment();}
	T operator -- ()			{return Decrement();}
	T operator ++ (int)			{return FetchAdd(1);}
	T operator -- (int)			{return FetchSub(1);}
	T operator += (T iCount)	{return AddFetch(iCount);}
	T operator -= (T iCount)	{return SubFetch(iCount);}
	T operator  = (T iCount)	{return SetCount(iCount);}
	operator T	  ()			{return GetCount();}

public:
	CSafeCounterT(T iCount = 0) : m_iCount(iCount) {}

private:
	template<SIZE_T> T IncrementImpl()			{return (T)::InterlockedIncrement((volatile LONG*)&m_iCount);}
	template<SIZE_T> T DecrementImpl()			{return (T)::InterlockedDecrement((volatile LONG*)&m_iCount);}
	template<SIZE_T> T FetchAddImpl(T iCount)	{return (T)::InterlockedExchangeAdd((volatile LONG*)&m_iCount, iCount);}
	template<SIZE_T> T FetchSubImpl(T iCount)	{return (T)::InterlockedExchangeAdd((volatile LONG*)&m_iCount, -iCount);}

#if _WIN32_WINNT >= _WIN32_WINNT_VISTA
	template<> T IncrementImpl<8>()				{return (T)::InterlockedIncrement64((volatile LONGLONG*)&m_iCount);}
	template<> T DecrementImpl<8>()				{return (T)::InterlockedDecrement64((volatile LONGLONG*)&m_iCount);}
	template<> T FetchAddImpl<8>(T iCount)		{return (T)::InterlockedExchangeAdd64((volatile LONGLONG*)&m_iCount, iCount);}
	template<> T FetchSubImpl<8>(T iCount)		{return (T)::InterlockedExchangeAdd64((volatile LONGLONG*)&m_iCount, -iCount);}
#endif

protected:
	volatile T m_iCount;
};

template<typename T> class CUnsafeCounterT
{
public:
	T Increment()				{return ++m_iCount;}
	T Decrement()				{return --m_iCount;}
	T AddFetch(T iCount)		{return m_iCount += iCount;}
	T SubFetch(T iCount)		{return m_iCount -= iCount;}
	T FetchAdd(T iCount)		{T rs = m_iCount; m_iCount += iCount; return rs;}
	T FetchSub(T iCount)		{T rs = m_iCount; m_iCount -= iCount; return rs;}

	T SetCount(T iCount)		{return (m_iCount = iCount);}
	T ResetCount(T iCount = 0)	{return SetCount(iCount);}
	T GetCount()				{return m_iCount;}

	T operator ++ ()			{return Increment();}
	T operator -- ()			{return Decrement();}
	T operator ++ (int)			{return FetchAdd(1);}
	T operator -- (int)			{return FetchSub(1);}
	T operator += (T iCount)	{return AddFetch(iCount);}
	T operator -= (T iCount)	{return SubFetch(iCount);}
	T operator  = (T iCount)	{return SetCount(iCount);}
	operator T	  ()			{return GetCount();}

public:
	CUnsafeCounterT(T iCount = 0) : m_iCount(iCount) {}

protected:
	T m_iCount;
};

template<class CCounter> class CLocalCounter
{
public:
	CLocalCounter(CCounter& obj) : m_counter(obj) {m_counter.Increment();}
	~CLocalCounter() {m_counter.Decrement();}
private:
	CCounter& m_counter;
};

typedef CSafeCounterT<INT>					CSafeCounter;
typedef CSafeCounterT<LONGLONG>				CSafeBigCounter;
typedef CUnsafeCounterT<INT>				CUnsafeCounter;
typedef CUnsafeCounterT<LONGLONG>			CUnsafeBigCounter;

typedef CLocalCounter<CSafeCounter>			CLocalSafeCounter;
typedef CLocalCounter<CSafeBigCounter>		CLocalSafeBigCounter;
typedef CLocalCounter<CUnsafeCounter>		CLocalUnsafeCounter;
typedef CLocalCounter<CUnsafeBigCounter>	CLocalUnsafeBigCounter;


/* ========================================================================== */
/*  RWLock.h
/*  source: Windows\Src\Common\RWLock.h
/* ========================================================================== */

#pragma once

/* [amalgamated] #include "CriticalSection.h" */
/* [amalgamated] #include "Semaphore.h" */

class CSWMR
{
public:
	VOID WaitToRead();
	VOID WaitToWrite();
	VOID ReadDone()  {Done();}
	VOID WriteDone() {Done();}

private:
	VOID Done();

public:
	CSWMR();
	~CSWMR();

private:
	CSWMR(const CSWMR&);
	CSWMR operator = (const CSWMR&);

private:
	int m_nWaitingReaders;
	int m_nWaitingWriters;
	int m_nActive;

	CSpinGuard	m_cs;
	CSEM		m_smRead;
	CSEM		m_smWrite;
};

#if _WIN32_WINNT >= _WIN32_WINNT_WS08

class CSlimLock
{
public:
	VOID WaitToRead()		{::AcquireSRWLockShared(&m_lock);}
	VOID WaitToWrite()		{::AcquireSRWLockExclusive(&m_lock);}
	VOID ReadDone()			{::ReleaseSRWLockShared(&m_lock);}
	VOID WriteDone()		{::ReleaseSRWLockExclusive(&m_lock);}
	BOOL TryWaitToRead()	{return ::TryAcquireSRWLockShared(&m_lock);}
	BOOL TryWaitToWrite()	{return ::TryAcquireSRWLockExclusive(&m_lock);}

	SRWLOCK* GetObject()	{return &m_lock;}

public:
	CSlimLock()		{::InitializeSRWLock(&m_lock);}
	~CSlimLock()	{}

private:
	CSlimLock(const CSlimLock&);
	CSlimLock operator = (const CSlimLock&);

private:
	SRWLOCK m_lock;
};

class CSlimRWLock
{
public:
	VOID WaitToRead();
	VOID WaitToWrite();
	VOID ReadDone();
	VOID WriteDone();

private:
	BOOL IsOwner()		{return m_dwWriterTID == ::GetCurrentThreadId();}
	VOID SetOwner()		{m_dwWriterTID = ::GetCurrentThreadId();}
	VOID DetachOwner()	{m_dwWriterTID = 0;}

public:
	CSlimRWLock();
	~CSlimRWLock();

private:
	CSlimRWLock(const CSlimRWLock&);
	CSlimRWLock operator = (const CSlimRWLock&);

private:
	int m_nActive;
	DWORD m_dwWriterTID;

	CSpinGuard	m_cs;
	CSlimLock	m_smLock;
};

#endif

class CSEMRWLock
{
public:
	VOID WaitToRead();
	VOID WaitToWrite();
	VOID ReadDone();
	VOID WriteDone();

private:
	VOID Done			(CSEM** ppSem, LONG& lCount);
	BOOL IsOwner()		{return m_dwWriterTID == ::GetCurrentThreadId();}
	VOID SetOwner()		{m_dwWriterTID = ::GetCurrentThreadId();}
	VOID DetachOwner()	{m_dwWriterTID = 0;}

public:
	CSEMRWLock();
	~CSEMRWLock();

private:
	CSEMRWLock(const CSEMRWLock&);
	CSEMRWLock operator = (const CSEMRWLock&);

private:
	int m_nWaitingReaders;
	int m_nWaitingWriters;
	int m_nActive;
	DWORD m_dwWriterTID;

	CSpinGuard	m_cs;
	CSEM		m_smRead;
	CSEM		m_smWrite;
};

template<class CLockObj> class CLocalReadLock
{
public:
	CLocalReadLock(CLockObj& obj) : m_wait(obj) {m_wait.WaitToRead();}
	~CLocalReadLock() {m_wait.ReadDone();}
private:
	CLocalReadLock(const CLocalReadLock&);
	CLocalReadLock operator = (const CLocalReadLock&);
private:
	CLockObj& m_wait;
};

template<class CLockObj> class CLocalWriteLock
{
public:
	CLocalWriteLock(CLockObj& obj) : m_wait(obj) {m_wait.WaitToWrite();}
	~CLocalWriteLock() {m_wait.WriteDone();}
private:
	CLocalWriteLock(const CLocalWriteLock&);
	CLocalWriteLock operator = (const CLocalWriteLock&);
private:
	CLockObj& m_wait;
};

#if _WIN32_WINNT >= _WIN32_WINNT_WS08
	typedef CSlimLock	CSimpleRWLock;
#else
	typedef CSWMR		CSimpleRWLock;
#endif

typedef CLocalReadLock<CSimpleRWLock>	CReadLock;
typedef CLocalWriteLock<CSimpleRWLock>	CWriteLock;

typedef CSEMRWLock						CRWLock;
typedef CLocalReadLock<CRWLock>			CReentrantReadLock;
typedef CLocalWriteLock<CRWLock>		CReentrantWriteLock;

#if _WIN32_WINNT >= _WIN32_WINNT_WS08

class ICVCondition
{
public:
	virtual BOOL Detect() = 0;

public:
	virtual ~ICVCondition() {}
};

class CCVCriSec
{
public:
	CCVCriSec(CInterCriSec& cs)
	: m_cs(cs)
	{
		::InitializeConditionVariable(&m_cv);
	}

	~CCVCriSec() {}

	BOOL WaitToRead(ICVCondition* pCondition, DWORD dwMilliseconds = INFINITE)
	{
		return Wait(pCondition, dwMilliseconds);
	}

	BOOL WaitToWrite(ICVCondition* pCondition, DWORD dwMilliseconds = INFINITE)
	{
		return Wait(pCondition, dwMilliseconds);
	}

	void ReadDone()
	{
		Done();
	}

	void WriteDone()
	{
		Done();
	}

	void WakeUp()
	{
		::WakeConditionVariable(&m_cv);
	}

	void WakeUpAll()
	{
		::WakeAllConditionVariable(&m_cv);
	}

	BOOL Wait(ICVCondition* pCondition, DWORD dwMilliseconds = INFINITE)
	{
		ASSERT(pCondition);

		m_cs.Lock();

		while(!pCondition->Detect())
		{
			if(!::SleepConditionVariableCS(&m_cv, m_cs.GetObject(), dwMilliseconds))
				return FALSE;
		}

		return TRUE;
	}

	void Done()
	{
		m_cs.Unlock();
	}

	CInterCriSec& GetLock()
	{
		return m_cs;
	}

private:
	CCVCriSec(const CCVCriSec& cs);
	CCVCriSec operator = (const CCVCriSec& cs);

private:
	CInterCriSec&		m_cs;
	CONDITION_VARIABLE	m_cv;
};

class CCVSlim
{
public:
	CCVSlim(CSlimLock& cs)
	: m_cs(cs)
	{
		::InitializeConditionVariable(&m_cv);
	}

	~CCVSlim() {}

	BOOL WaitToRead(ICVCondition* pCondition, DWORD dwMilliseconds = INFINITE)
	{
		ASSERT(pCondition);

		m_cs.WaitToRead();

		while(!pCondition->Detect()) 
		{
			if(!::SleepConditionVariableSRW(&m_cv, m_cs.GetObject(), dwMilliseconds, CONDITION_VARIABLE_LOCKMODE_SHARED))
				return FALSE;
		}

		return TRUE;
	}

	BOOL WaitToWrite(ICVCondition* pCondition, DWORD dwMilliseconds = INFINITE)
	{
		ASSERT(pCondition);

		m_cs.WaitToWrite();

		while(!pCondition->Detect()) 
		{
			if(!::SleepConditionVariableSRW(&m_cv, m_cs.GetObject(), dwMilliseconds, 0))
				return FALSE;
		}

		return TRUE;
	}

	void ReadDone()
	{
		m_cs.ReadDone();
	}

	void WriteDone()
	{
		m_cs.WriteDone();
	}

	void WakeUp()
	{
		::WakeConditionVariable(&m_cv);
	}

	void WakeUpAll()
	{
		::WakeAllConditionVariable(&m_cv);
	}

	CSlimLock& GetLock()
	{
		return m_cs;
	}

private:
	CCVSlim(const CCVSlim& cs);
	CCVSlim operator = (const CCVSlim& cs);

private:
	CSlimLock&			m_cs;
	CONDITION_VARIABLE	m_cv;
};

template<class _Lock, class _Var> class CCVGuard
{
public:
	BOOL WaitForProduce(DWORD dwMilliseconds = INFINITE)
	{
		return m_cvP.WaitToWrite(m_pcdtProduce, dwMilliseconds);
	}

	BOOL WaitForConsume(DWORD dwMilliseconds = INFINITE)
	{
		return m_cvC.WaitToRead(m_pcdtConsume, dwMilliseconds);
	}

	void ProduceDone()
	{
		m_cvP.WriteDone();
	}

	void WakeUpProduce()
	{
		m_cvP.WakeUp();
	}

	void WakeUpAllProduces()
	{
		m_cvP.WakeUpAll();
	}

	void ConsumeDone()
	{
		m_cvC.ReadDone();
	}

	void WakeUpConsume()
	{
		m_cvC.WakeUp();
	}

	void WakeUpAllConsumes()
	{
		m_cvC.WakeUpAll();
	}

public:
	CCVGuard(ICVCondition* pcdtProduce, ICVCondition* pcdtConsume)
	: m_cvP(m_cs)
	, m_cvC(m_cs)
	, m_pcdtProduce(pcdtProduce)
	, m_pcdtConsume(pcdtConsume)
	{
		ASSERT(m_pcdtConsume && m_pcdtProduce);
	}

	~CCVGuard()	{}

private:
	CCVGuard(const CCVGuard& cs);
	CCVGuard operator = (const CCVGuard& cs);

private:
	ICVCondition* m_pcdtProduce;
	ICVCondition* m_pcdtConsume;

	_Lock	m_cs;
	_Var	m_cvP;
	_Var	m_cvC;
};

template<class _GuardObj> class CConsumeLock
{
public:
	CConsumeLock(_GuardObj& obj) : m_guard(obj) {m_guard.WaitForConsume();}
	~CConsumeLock() {m_guard.ConsumeDone();}
private:
	CConsumeLock(const CConsumeLock&);
	CConsumeLock operator = (const CConsumeLock&);
private:
	_GuardObj& m_guard;
};

template<class _GuardObj> class CProduceLock
{
public:
	CProduceLock(_GuardObj& obj) : m_guard(obj) {m_guard.WaitForProduce();}
	~CProduceLock() {m_guard.ProduceDone();}
private:
	CProduceLock(const CProduceLock&);
	CProduceLock operator = (const CProduceLock&);
private:
	_GuardObj& m_guard;
};

typedef CCVGuard<CInterCriSec, CCVCriSec>	CCVGuardCS;
typedef CCVGuard<CSlimLock, CCVSlim>		CCVGuardSRW;
typedef CProduceLock<CCVGuardCS>			CProduceLockCS;
typedef CConsumeLock<CCVGuardCS>			CConsumeLockCS;
typedef CProduceLock<CCVGuardSRW>			CProduceLockSRW;
typedef CConsumeLock<CCVGuardSRW>			CConsumeLockSRW;

#endif


/* ========================================================================== */
/*  RingBuffer.h
/*  source: Windows\Src\Common\RingBuffer.h
/* ========================================================================== */

#pragma once

/* [amalgamated] #include "RWLock.h" */
/* [amalgamated] #include "STLHelper.h" */
/* [amalgamated] #include "CriticalSection.h" */

#define CACHE_LINE		64
#define PACK_SIZE_OF(T)	(CACHE_LINE - sizeof(T) % CACHE_LINE)

#if !defined(MAXINT)
	#define MAXINT	INT_MAX
#endif

#if !defined(_WIN64)
	#pragma pack(push, 4)
#endif

template <class T, class _PutGuard = CCriSec, class _GetGuard = CCriSec> class CRingBuffer
{
public:
	static const UINT DEFAULT_EXPECT = 4096;

public:
	BOOL Put(T* pElement)
	{
		ASSERT(pElement != nullptr);

		{
			CLocalLock<_PutGuard> locallock(m_csPut);

			ULONGLONG seqPut = m_seqPut;

			WaitForPut(seqPut);
			if(!IsValid()) return FALSE;

			DoPut(pElement, seqPut);
		}

		return TRUE;
	}

	BOOL TryPut(T* pElement)
	{
		ASSERT(pElement != nullptr);

		if(!IsValid() || !HasPutSpace(m_seqPut))
			return FALSE;

		{
			CLocalLock<_PutGuard> locallock(m_csPut);

			ULONGLONG seqPut = m_seqPut;

			if(!IsValid() || !HasPutSpace(seqPut))
				return FALSE;

			DoPut(pElement, seqPut);
		}

		return TRUE;
	}

	BOOL PutBatch(T* pElements[], int& iCount)
	{
		ASSERT(pElements != nullptr && iCount > 0);

		{
			CLocalLock<_PutGuard> locallock(m_csPut);

			ULONGLONG seqPut = m_seqPut;

			for(int i = 0; i < iCount; ++i)
			{
				WaitForPut(seqPut);

				if(!IsValid())
				{
					iCount = i;
					return FALSE;
				}

				DoPut(*(pElements + i), seqPut);
			}
		}

		return TRUE;
	}

	BOOL TryPutBatch(T* pElements[], int& iCount)
	{
		ASSERT(pElements != nullptr && iCount > 0);

		if(!IsValid() || !HasPutSpace(m_seqPut))
		{
			iCount = 0;
			return FALSE;
		}

		{
			CLocalLock<_PutGuard> locallock(m_csPut);

			ULONGLONG seqPut = m_seqPut;

			for(int i = 0; i < iCount; ++i)
			{
				if(!IsValid() || !HasPutSpace(seqPut))
				{
					iCount = i;
					return FALSE;
				}

				DoPut(*(pElements + i), seqPut);
			}
		}

		return TRUE;
	}

	BOOL Get(T** pElement)
	{
		ASSERT(pElement != nullptr);

		{
			CLocalLock<_GetGuard> locallock(m_csGet);

			ULONGLONG seqGet = m_seqGet;

			WaitForGet(seqGet);
			if(!IsValid()) return FALSE;

			DoGet(pElement, seqGet);
		}

		return TRUE;
	}

	BOOL TryGet(T** pElement)
	{
		ASSERT(pElement != nullptr);

		if(!IsValid() || !HasGetSpace(m_seqGet))
			return FALSE;

		{
			CLocalLock<_GetGuard> locallock(m_csGet);

			ULONGLONG seqGet = m_seqGet;

			if(!IsValid() || !HasGetSpace(seqGet))
				return FALSE;

			DoGet(pElement, seqGet);
		}

		return TRUE;
	}

	BOOL GetBatch(T* pElements[], int& iCount)
	{
		ASSERT(pElements != nullptr && iCount > 0);

		{
			CLocalLock<_GetGuard> locallock(m_csGet);

			ULONGLONG seqGet = m_seqGet;

			for(int i = 0; i < iCount; ++i)
			{
				WaitForGet(seqGet);

				if(!IsValid())
				{
					iCount = i;
					return FALSE;
				}

				DoGet(pElements + i, seqGet);
			}
		}

		return TRUE;
	}

	BOOL TryGetBatch(T* pElements[], int& iCount)
	{
		ASSERT(pElements != nullptr && iCount > 0);

		if(!IsValid() || !HasGetSpace(m_seqGet))
		{
			iCount = 0;
			return FALSE;
		}

		{
			CLocalLock<_GetGuard> locallock(m_csGet);

			ULONGLONG seqGet = m_seqGet;

			for(int i = 0; i < iCount; ++i)
			{
				if(!IsValid() || !HasGetSpace(seqGet))
				{
					iCount = i;
					return FALSE;
				}

				DoGet(pElements + i, seqGet);
			}
		}

		return TRUE;
	}

	BOOL Peek(T** pElement)
	{
		ASSERT(pElement != nullptr);

		ULONGLONG seqGet = m_seqGet;

		if(!IsValid() || !HasGetSpace(seqGet))
			return FALSE;

		DoPeek(pElement, seqGet);

		return TRUE;
	}

private:
	void DoPut(T* pElement, ULONGLONG& seqPut)
	{
		DWORD index = seqPut & (m_dwReal - 1);
		*(m_pv + index)	= pElement;

		++seqPut;
		m_seqPut = seqPut;
	}

	void DoGet(T** pElement, ULONGLONG& seqGet)
	{
		DWORD index = seqGet & (m_dwReal - 1);
		*(pElement) = *(m_pv + index);

		++seqGet;
		m_seqGet = seqGet;
	}

	void DoPeek(T** pElement, ULONGLONG& seqGet)
	{
		DWORD index = seqGet & (m_dwReal - 1);
		*(pElement) = *(m_pv + index);
	}

	BOOL HasPutSpace(ULONGLONG seqPut)
	{
		return (seqPut - m_seqGet < m_dwReal);
	}

	void WaitForPut(ULONGLONG seqPut)
	{
		for(DWORD w = 0; IsValid(); ++w)
		{
			if(HasPutSpace(seqPut))
				break;

			::YieldThread(w);
		}
	}

	BOOL HasGetSpace(ULONGLONG seqGet)
	{
		return (m_seqPut - seqGet > 0);
	}

	void WaitForGet(ULONGLONG seqGet)
	{
		for(DWORD w = 0; IsValid(); ++w)
		{
			if(HasGetSpace(seqGet))
				break;

			::YieldThread(w);
		}
	}

	DWORD Revise(DWORD dwExpect)
	{
		int index = 0;
		int shift = sizeof(DWORD) * 8 - 1;

		for(int i = shift; i >= 0; i--)
		{
			if(index == 0)
			{
				if(dwExpect & (1 << i))
				{
					index = i;

					if(index == shift)
						break;
				}
			}
			else
			{
				if(dwExpect & (1 << i))
					++index;

				break;
			}
		}

		return 1 << index;
	}

public:
	CRingBuffer(DWORD uiExpect = DEFAULT_EXPECT)
	: m_pv(nullptr)
	, m_dwReal(0)
	, m_seqPut(0)
	, m_seqGet(0)
	{
		Reset(uiExpect);
	}

	~CRingBuffer()
	{
		Reset(0);
	}

	void Reset(DWORD uiExpect = DEFAULT_EXPECT)
	{
		if(IsValid())
			Destroy();
		if(uiExpect > 0)
			Create(uiExpect);
	}

	BOOL IsValid() {return m_pv != nullptr;}

private:
	void Create(DWORD dwExpect = DEFAULT_EXPECT)
	{
		ASSERT(!IsValid() && dwExpect > 0);

		m_seqPut = 0;
		m_seqGet = 0;
		m_dwReal = Revise(dwExpect);
		m_pv	 = (T**)malloc(m_dwReal * sizeof(T*));
	}

	void Destroy()
	{
		ASSERT(IsValid());

		CLocalLock<_PutGuard> locallock1(m_csPut);
		CLocalLock<_GetGuard> locallock2(m_csGet);

		free((void*)m_pv);
		m_pv	 = nullptr;
		m_dwReal = 0;
		m_seqPut = 0;
		m_seqGet = 0;
	}

private:
	CRingBuffer(const CRingBuffer&);
	CRingBuffer operator = (const CRingBuffer&);

private:
	DWORD				m_dwReal;
	T**					m_pv;
	char				pack1[PACK_SIZE_OF(T**)];
	volatile ULONGLONG	m_seqPut;
	char				pack4[PACK_SIZE_OF(ULONGLONG)];
	volatile ULONGLONG	m_seqGet;
	char				pack5[PACK_SIZE_OF(ULONGLONG)];
	_PutGuard			m_csPut;
	char				pack2[PACK_SIZE_OF(_PutGuard)];
	_GetGuard			m_csGet;
	char				pack3[PACK_SIZE_OF(_GetGuard)];
};

typedef CRingBuffer<void, CCriSec, CCriSec>				CCSRingBuffer;
typedef CRingBuffer<void, CInterCriSec, CInterCriSec>	CICSRingBuffer;
typedef CRingBuffer<void, CSpinGuard, CSpinGuard>		CSGRingBuffer;
typedef CRingBuffer<void, CFakeGuard, CFakeGuard>		CFKRingBuffer;

// ------------------------------------------------------------------------------------------------------------- //

template <class T, class index_type = DWORD, bool adjust_index = false> class CRingCache
{
public:

	enum EnGetResult {GR_FAIL = -1, GR_INVALID = 0, GR_VALID = 1};

	typedef T*									TPTR;
	typedef volatile T*							VTPTR;

	typedef unordered_set<index_type>			IndexSet;
	typedef typename IndexSet::const_iterator	IndexSetCI;
	typedef typename IndexSet::iterator			IndexSetI;

	static TPTR const E_EMPTY;
	static TPTR const E_LOCKED;
	static TPTR const E_MAX_STATUS;

public:

	static index_type& INDEX_INC(index_type& dwIndex)	{if(adjust_index) ++dwIndex; return dwIndex;}
	static index_type& INDEX_DEC(index_type& dwIndex)	{if(adjust_index) --dwIndex; return dwIndex;}

private:

	index_type& INDEX_V2R(index_type& dwIndex)	{dwIndex %= m_dwSize; if(dwIndex == 0) dwIndex = m_dwSize; return dwIndex;}
	VTPTR& INDEX_VAL(index_type dwIndex) {return *(m_pv + dwIndex);}

public:

	BOOL Put(TPTR pElement, index_type& dwIndex)
	{
		ASSERT(pElement != nullptr);

		if(!IsValid()) return FALSE;

		BOOL isOK = FALSE;

		while(true)
		{
			if(!HasSpace())
				break;

			DWORD dwCurSeq			= m_dwCurSeq;
			index_type dwCurIndex	= dwCurSeq % m_dwSize;
			VTPTR& pValue			= INDEX_VAL(dwCurIndex);

			if(pValue == E_EMPTY)
			{
				if(::InterlockedCompareExchangePointer((volatile PVOID*)&pValue, pElement, E_EMPTY) == E_EMPTY)
				{
					::InterlockedIncrement(&m_dwCount);
					::InterlockedCompareExchange(&m_dwCurSeq, dwCurSeq + 1, dwCurSeq);

					dwIndex = INDEX_INC(dwCurIndex);
					isOK	= TRUE;

					if(pElement != E_LOCKED)
						EmplaceIndex(dwIndex);

					break;
				}
			}

			::InterlockedCompareExchange(&m_dwCurSeq, dwCurSeq + 1, dwCurSeq);
		}

		return isOK;
	}

	EnGetResult GetEx(index_type dwIndex, TPTR* ppElement)
	{
		return Get(INDEX_V2R(dwIndex), ppElement);
	}

	EnGetResult Get(index_type dwIndex, TPTR* ppElement)
	{
		ASSERT(dwIndex <= m_dwSize);
		ASSERT(ppElement != nullptr);

		if(!IsValid() || INDEX_DEC(dwIndex) >= m_dwSize)
		{
			*ppElement = nullptr;
			return GR_FAIL;
		}

		*ppElement = (TPTR)INDEX_VAL(dwIndex);

		return IsValidElement(*ppElement) ? GR_VALID : GR_INVALID;
	}

	BOOL SetEx(index_type dwIndex, TPTR pElement, TPTR* ppOldElement = nullptr)
	{
		return Set(INDEX_V2R(dwIndex), pElement, ppOldElement);
	}

	BOOL Set(index_type dwIndex, TPTR pElement, TPTR* ppOldElement = nullptr)
	{
		TPTR pElement2 = nullptr;

		if(Get(dwIndex, &pElement2) == GR_FAIL)
			return FALSE;

		if(ppOldElement != nullptr)
			*ppOldElement = pElement2;

		if(pElement == pElement2)
			return FALSE;

		int f1 = 0;
		int f2 = 0;

		if(pElement == E_EMPTY)
		{
			if(pElement2 == E_LOCKED)
				f1 = -1;
			else
				f1 = f2 = -1;
		}
		else if(pElement == E_LOCKED)
		{
			if(pElement2 == E_EMPTY)
				f1 = 1;
			else
				f2 = -1;
		}
		else
		{
			if(pElement2 == E_EMPTY)
				f1 = f2 = 1;
			else if(pElement2 == E_LOCKED)
				f2 = 1;
		}

		BOOL bSetValueFirst		= (f1 + f2 >= 0);
		index_type dwOuterIndex	= dwIndex;

		INDEX_DEC(dwIndex);

		if(bSetValueFirst)	INDEX_VAL(dwIndex) = pElement;
		if(f1 > 0)			::InterlockedIncrement(&m_dwCount);
		if(f2 != 0)			(f2 > 0) ? EmplaceIndex(dwOuterIndex) : EraseIndex(dwOuterIndex);
		if(f1 < 0)			::InterlockedDecrement(&m_dwCount);
		if(!bSetValueFirst) INDEX_VAL(dwIndex) = pElement;

		ASSERT(Spaces() <= Size());

		return TRUE;
	}

	BOOL RemoveEx(index_type dwIndex, TPTR* ppElement = nullptr)
	{
		return Remove(INDEX_V2R(dwIndex), ppElement);
	}

	BOOL Remove(index_type dwIndex, TPTR* ppElement = nullptr)
	{
		return Set(dwIndex, E_EMPTY, ppElement);
	}

	BOOL AcquireLock(index_type& dwIndex)
	{
		return Put(E_LOCKED, dwIndex);
	}

	BOOL ReleaseLock(index_type dwIndex, TPTR pElement)
	{
		ASSERT(pElement == nullptr || IsValidElement(pElement));

		TPTR pElement2 = nullptr;
		Get(dwIndex, &pElement2);

		ASSERT(pElement2 == E_LOCKED);

		if(pElement2 != E_LOCKED)
			return FALSE;

		return Set(dwIndex, pElement);
	}

public:

	void Reset(DWORD dwSize = 0)
	{
		if(IsValid())
			Destroy();
		if(dwSize > 0)
			Create(dwSize);
	}
	
	BOOL GetAllElementIndexes(index_type ids[], DWORD& dwCount, BOOL bCopy = TRUE)
	{
		DWORD dwSize = Elements();

		if(ids == nullptr || dwCount == 0)
		{
			dwCount = dwSize;
			return FALSE;
		}

		if(dwSize == 0)
		{
			dwCount = 0;
			return TRUE;
		}

		IndexSet* pIndexes = &m_indexes;

		if(bCopy)
		{
			pIndexes = new IndexSet;
			CopyIndexes(*pIndexes);
		}

		DWORD i = 0;

		for(auto it = pIndexes->begin(), end = pIndexes->end(); i < dwCount && it != end; ++i, ++it)
			ids[i] = *it;

		if(bCopy) delete pIndexes;

		dwCount = i;
		return TRUE;
	}
	
	unique_ptr<index_type[]> GetAllElementIndexes(DWORD& dwCount, BOOL bCopy = TRUE)
	{
		dwCount = (DWORD)m_indexes.size();
		unique_ptr<index_type[]> ids(new index_type[dwCount]);

		if(dwCount > 0)
			GetAllElementIndexes(ids.get(), dwCount, bCopy);

		return ids;
	}
	
	IndexSet& CopyIndexes(IndexSet& indexes)
	{
		{
			CReadLock locallock(m_cs);
			indexes = m_indexes;
		}

		return indexes;
	}

	static BOOL IsValidElement(TPTR pElement) {return pElement > E_MAX_STATUS;}

	IndexSet& Indexes	()	{return m_indexes;}
	DWORD Size			()	{return m_dwSize;}
	DWORD Elements		()	{return (DWORD)m_indexes.size();}
	DWORD Spaces		()	{return m_dwSize - m_dwCount;}
	BOOL HasSpace		()	{return m_dwCount < m_dwSize;}
	BOOL IsEmpty		()	{return m_dwCount == 0;}
	BOOL IsValid		()	{return m_pv != nullptr;}

private:

	void Create(DWORD dwSize)
	{
		ASSERT(!IsValid() && dwSize > 0);

		m_dwCurSeq	= 0;
		m_dwCount	= 0;
		m_dwSize	= dwSize;
		m_pv		= (VTPTR*)malloc(m_dwSize * sizeof(TPTR));

		::ZeroMemory(m_pv, m_dwSize * sizeof(TPTR));
	}

	void Destroy()
	{
		ASSERT(IsValid());

		m_indexes.clear();
		free((void*)m_pv);

		m_pv		= nullptr;
		m_dwSize	= 0;
		m_dwCount	= 0;
		m_dwCurSeq	= 0;
	}

	void EmplaceIndex(index_type dwIndex)
	{
		CWriteLock locallock(m_cs);
		m_indexes.emplace(dwIndex);
	}

	void EraseIndex(index_type dwIndex)
	{
		CWriteLock locallock(m_cs);
		m_indexes.erase(dwIndex);
	}

public:
	CRingCache	(DWORD dwSize = 0)
	: m_pv		(nullptr)
	, m_dwSize	(0)
	, m_dwCount	(0)
	, m_dwCurSeq(0)
	{
		Reset(dwSize);
	}

	~CRingCache()
	{
		Reset(0);
	}

private:
	CRingCache(const CRingCache&);
	CRingCache operator = (const CRingCache&);

private:
	DWORD				m_dwSize;
	VTPTR*				m_pv;
	char				pack1[PACK_SIZE_OF(VTPTR*)];
	volatile DWORD		m_dwCurSeq;
	char				pack2[PACK_SIZE_OF(DWORD)];
	volatile DWORD		m_dwCount;
	char				pack3[PACK_SIZE_OF(DWORD)];

	CSimpleRWLock		m_cs;
	IndexSet			m_indexes;
};

template <class T, class index_type, bool adjust_index> T* const CRingCache<T, index_type, adjust_index>::E_EMPTY		= (T*)0x00;
template <class T, class index_type, bool adjust_index> T* const CRingCache<T, index_type, adjust_index>::E_LOCKED		= (T*)0x01;
template <class T, class index_type, bool adjust_index> T* const CRingCache<T, index_type, adjust_index>::E_MAX_STATUS	= (T*)0x0F;

// ------------------------------------------------------------------------------------------------------------- //

template <class T, class index_type = DWORD, bool adjust_index = false> class CRingCache2
{
public:

	enum EnGetResult {GR_FAIL = -1, GR_INVALID = 0, GR_VALID = 1};

	typedef T*									TPTR;
	typedef volatile T*							VTPTR;

	typedef unordered_set<index_type>			IndexSet;
	typedef typename IndexSet::const_iterator	IndexSetCI;
	typedef typename IndexSet::iterator			IndexSetI;

	static TPTR const E_EMPTY;
	static TPTR const E_LOCKED;
	static TPTR const E_MAX_STATUS;
	static DWORD const MAX_SIZE;

public:

	static index_type& INDEX_INC(index_type& dwIndex)	{if(adjust_index) ++dwIndex; return dwIndex;}
	static index_type& INDEX_DEC(index_type& dwIndex)	{if(adjust_index) --dwIndex; return dwIndex;}

	index_type& INDEX_R2V(index_type& dwIndex)			{dwIndex += *(m_px + dwIndex) * m_dwSize; return dwIndex;}

	BOOL INDEX_V2R(index_type& dwIndex)
	{
		index_type m = dwIndex % m_dwSize;
		BYTE x		 = *(m_px + m);

		if(dwIndex / m_dwSize != x)
			return FALSE;

		dwIndex = m;
		return TRUE;
	}


private:

	VTPTR& INDEX_VAL(index_type dwIndex) {return *(m_pv + dwIndex);}

public:

	BOOL Put(TPTR pElement, index_type& dwIndex)
	{
		ASSERT(pElement != nullptr);

		if(!IsValid()) return FALSE;

		BOOL isOK = FALSE;

		while(true)
		{
			if(!HasSpace())
				break;

			DWORD dwCurSeq			= m_dwCurSeq;
			index_type dwCurIndex	= dwCurSeq % m_dwSize;
			VTPTR& pValue			= INDEX_VAL(dwCurIndex);

			if(pValue == E_EMPTY)
			{
				if(::InterlockedCompareExchangePointer((volatile PVOID*)&pValue, pElement, E_EMPTY) == E_EMPTY)
				{
					::InterlockedIncrement(&m_dwCount);
					::InterlockedCompareExchange(&m_dwCurSeq, dwCurSeq + 1, dwCurSeq);

					dwIndex = INDEX_INC(INDEX_R2V(dwCurIndex));
					isOK	= TRUE;

					if(pElement != E_LOCKED)
						EmplaceIndex(dwIndex);

					break;
				}
			}

			::InterlockedCompareExchange(&m_dwCurSeq, dwCurSeq + 1, dwCurSeq);
		}

		return isOK;
	}

	EnGetResult Get(index_type dwIndex, TPTR* ppElement, index_type* pdwRealIndex = nullptr)
	{
		ASSERT(ppElement != nullptr);

		if(!IsValid() || !INDEX_V2R(INDEX_DEC(dwIndex)))
		{
			*ppElement = nullptr;
			return GR_FAIL;
		}

		*ppElement = (TPTR)INDEX_VAL(dwIndex);
		if(pdwRealIndex) *pdwRealIndex = dwIndex;

		return IsValidElement(*ppElement) ? GR_VALID : GR_INVALID;
	}

	BOOL Set(index_type dwIndex, TPTR pElement, TPTR* ppOldElement = nullptr, index_type* pdwRealIndex = nullptr)
	{
		TPTR pElement2 = nullptr;

		if(pdwRealIndex == nullptr)
			pdwRealIndex = CreateLocalObject(index_type);

		if(Get(dwIndex, &pElement2, pdwRealIndex) == GR_FAIL)
			return FALSE;

		if(ppOldElement != nullptr)
			*ppOldElement = pElement2;

		if(pElement == pElement2)
			return FALSE;

		int f1 = 0;
		int f2 = 0;

		if(pElement == E_EMPTY)
		{
			if(pElement2 == E_LOCKED)
				f1 = -1;
			else
				f1 = f2 = -1;
		}
		else if(pElement == E_LOCKED)
		{
			if(pElement2 == E_EMPTY)
				f1 = 1;
			else
				f2 = -1;
		}
		else
		{
			if(pElement2 == E_EMPTY)
				f1 = f2 = 1;
			else if(pElement2 == E_LOCKED)
				f2 = 1;
		}

		BOOL bSetValueFirst		= (f1 + f2 >= 0);
		index_type dwRealIndex	= *pdwRealIndex;

		if(bSetValueFirst)	INDEX_VAL(dwRealIndex) = pElement;
		if(f1 > 0)			::InterlockedIncrement(&m_dwCount);
		if(f2 != 0)			(f2 > 0) ? EmplaceIndex(dwIndex) : EraseIndex(dwIndex);
		if(f1 < 0)			{::InterlockedDecrement(&m_dwCount); ++(*(m_px + dwRealIndex));}
		if(!bSetValueFirst) INDEX_VAL(dwRealIndex) = pElement;

		ASSERT(Spaces() <= Size());

		return TRUE;
	}

	BOOL Remove(index_type dwIndex, TPTR* ppElement = nullptr)
	{
		return Set(dwIndex, E_EMPTY, ppElement);
	}

	BOOL AcquireLock(index_type& dwIndex)
	{
		return Put(E_LOCKED, dwIndex);
	}

	BOOL ReleaseLock(index_type dwIndex, TPTR pElement)
	{
		ASSERT(pElement == nullptr || IsValidElement(pElement));

		TPTR pElement2 = nullptr;
		Get(dwIndex, &pElement2);

		ASSERT(pElement2 == E_LOCKED);

		if(pElement2 != E_LOCKED)
			return FALSE;

		return Set(dwIndex, pElement);
	}

public:

	void Reset(DWORD dwSize = 0)
	{
		if(IsValid())
			Destroy();
		if(dwSize > 0)
			Create(dwSize);
	}
	
	BOOL GetAllElementIndexes(index_type ids[], DWORD& dwCount, BOOL bCopy = TRUE)
	{
		DWORD dwSize = Elements();

		if(ids == nullptr || dwCount == 0)
		{
			dwCount = dwSize;
			return FALSE;
		}

		if(dwSize == 0)
		{
			dwCount = 0;
			return TRUE;
		}

		IndexSet* pIndexes = &m_indexes;

		if(bCopy)
		{
			pIndexes = new IndexSet;
			CopyIndexes(*pIndexes);
		}

		DWORD i = 0;

		for(auto it = pIndexes->begin(), end = pIndexes->end(); i < dwCount && it != end; ++i, ++it)
			ids[i] = *it;

		if(bCopy) delete pIndexes;

		dwCount = i;
		return TRUE;
	}

	unique_ptr<index_type[]> GetAllElementIndexes(DWORD& dwCount, BOOL bCopy = TRUE)
	{
		dwCount = (DWORD)m_indexes.size();
		unique_ptr<index_type[]> ids(new index_type[dwCount]);

		if(dwCount > 0)
			GetAllElementIndexes(ids.get(), dwCount, bCopy);

		return ids;
	}

	IndexSet& CopyIndexes(IndexSet& indexes)
	{
		{
			CReadLock locallock(m_cs);
			indexes = m_indexes;
		}

		return indexes;
	}

	static BOOL IsValidElement(TPTR pElement) {return pElement > E_MAX_STATUS;}

	IndexSet& Indexes	()	{return m_indexes;}
	DWORD Size			()	{return m_dwSize;}
	DWORD Elements		()	{return (DWORD)m_indexes.size();}
	DWORD Spaces		()	{return m_dwSize - m_dwCount;}
	BOOL HasSpace		()	{return m_dwCount < m_dwSize;}
	BOOL IsEmpty		()	{return m_dwCount == 0;}
	BOOL IsValid		()	{return m_pv != nullptr;}

private:

	void Create(DWORD dwSize)
	{
		ASSERT(!IsValid() && dwSize > 0 && dwSize <= MAX_SIZE);

		m_dwCurSeq	= 0;
		m_dwCount	= 0;
		m_dwSize	= dwSize;
		m_pv		= (VTPTR*)malloc(m_dwSize * sizeof(TPTR));
		m_px		= (BYTE*)malloc(m_dwSize * sizeof(BYTE));

		::ZeroMemory(m_pv, m_dwSize * sizeof(TPTR));
		::ZeroMemory(m_px, m_dwSize * sizeof(BYTE));
	}

	void Destroy()
	{
		ASSERT(IsValid());

		m_indexes.clear();
		free((void*)m_pv);
		free((void*)m_px);

		m_pv		= nullptr;
		m_px		= nullptr;
		m_dwSize	= 0;
		m_dwCount	= 0;
		m_dwCurSeq	= 0;
	}

	void EmplaceIndex(index_type dwIndex)
	{
		CWriteLock locallock(m_cs);
		m_indexes.emplace(dwIndex);
	}

	void EraseIndex(index_type dwIndex)
	{
		CWriteLock locallock(m_cs);
		m_indexes.erase(dwIndex);
	}

public:
	CRingCache2	(DWORD dwSize = 0)
	: m_pv		(nullptr)
	, m_px		(nullptr)
	, m_dwSize	(0)
	, m_dwCount	(0)
	, m_dwCurSeq(0)
	{
		Reset(dwSize);
	}

	~CRingCache2()
	{
		Reset(0);
	}

private:
	CRingCache2(const CRingCache2&);
	CRingCache2 operator = (const CRingCache2&);

private:
	DWORD				m_dwSize;
	VTPTR*				m_pv;
	char				pack1[PACK_SIZE_OF(VTPTR*)];
	BYTE*				m_px;
	char				pack2[PACK_SIZE_OF(BYTE*)];
	volatile DWORD		m_dwCurSeq;
	char				pack3[PACK_SIZE_OF(DWORD)];
	volatile DWORD		m_dwCount;
	char				pack4[PACK_SIZE_OF(DWORD)];

	CSimpleRWLock		m_cs;
	IndexSet			m_indexes;
};

template <class T, class index_type, bool adjust_index> T* const CRingCache2<T, index_type, adjust_index>::E_EMPTY		= (T*)0x00;
template <class T, class index_type, bool adjust_index> T* const CRingCache2<T, index_type, adjust_index>::E_LOCKED		= (T*)0x01;
template <class T, class index_type, bool adjust_index> T* const CRingCache2<T, index_type, adjust_index>::E_MAX_STATUS	= (T*)0x0F;

template <class T, class index_type, bool adjust_index> DWORD const CRingCache2<T, index_type, adjust_index>::MAX_SIZE	= 
#if !defined(_WIN64)
																														  0x00FFFFFF
#else
																														  0xFFFFFFFF
#endif
																																	;
// ------------------------------------------------------------------------------------------------------------- //

template <class T> class CRingPool
{
private:

	typedef T*			TPTR;
	typedef volatile T*	VTPTR;

	static TPTR const E_EMPTY;
	static TPTR const E_LOCKED;
	static TPTR const E_MAX_STATUS;

private:

	VTPTR& INDEX_VAL(DWORD dwIndex) {return *(m_pv + dwIndex);}

public:

	BOOL TryPut(TPTR pElement)
	{
		ASSERT(pElement != nullptr);

		if(!IsValid()) return FALSE;

		BOOL isOK = FALSE;

		for(DWORD i = 0; i < m_dwSize; i++)
		{
			DWORD seqPut = m_seqPut;

			if(!HasPutSpace(seqPut))
				break;

			DWORD dwIndex = seqPut % m_dwSize;
			VTPTR& pValue = INDEX_VAL(dwIndex);
			TPTR pCurrent = (TPTR)pValue;

			if(pCurrent == E_EMPTY)
			{
				if(::InterlockedCompareExchangePointer((volatile PVOID*)&pValue, pElement, pCurrent) == pCurrent)
				{
					::InterlockedCompareExchange(&m_seqPut, seqPut + 1, seqPut);

					isOK = TRUE;

					break;
				}
			}

			::InterlockedCompareExchange(&m_seqPut, seqPut + 1, seqPut);
		}

		return isOK;
	}

	BOOL TryGet(TPTR* ppElement)
	{
		ASSERT(ppElement != nullptr);

		if(!IsValid()) return FALSE;

		BOOL isOK = FALSE;

		while(true)
		{
			DWORD seqGet = m_seqGet;

			if(!HasGetSpace(seqGet))
				break;

			DWORD dwIndex = seqGet % m_dwSize;
			VTPTR& pValue = INDEX_VAL(dwIndex);
			TPTR pCurrent = (TPTR)pValue;

			if(pCurrent > E_MAX_STATUS)
			{
				if(::InterlockedCompareExchangePointer((volatile PVOID*)&pValue, E_EMPTY, pCurrent) == pCurrent)
				{
					::InterlockedCompareExchange(&m_seqGet, seqGet + 1, seqGet);

					*(ppElement) = pCurrent;
					isOK		 = TRUE;

					break;
				}
			}

			::InterlockedCompareExchange(&m_seqGet, seqGet + 1, seqGet);
		}

		return isOK;
	}

	BOOL TryLock(TPTR* ppElement, DWORD& dwIndex)
	{
		ASSERT(ppElement != nullptr);

		if(!IsValid()) return FALSE;

		BOOL isOK = FALSE;

		while(true)
		{
			DWORD seqGet = m_seqGet;

			if(!HasGetSpace(seqGet))
				break;

			dwIndex		  = seqGet % m_dwSize;
			VTPTR& pValue = INDEX_VAL(dwIndex);
			TPTR pCurrent = (TPTR)pValue;

			if(pCurrent > E_MAX_STATUS)
			{
				if(::InterlockedCompareExchangePointer((volatile PVOID*)&pValue, E_LOCKED, pCurrent) == pCurrent)
				{
					::InterlockedCompareExchange(&m_seqGet, seqGet + 1, seqGet);

					*(ppElement) = pCurrent;
					isOK		 = TRUE;

					break;
				}
			}

			::InterlockedCompareExchange(&m_seqGet, seqGet + 1, seqGet);
		}

		return isOK;
	}

	BOOL ReleaseLock(TPTR pElement, DWORD dwIndex)
	{
		ASSERT(dwIndex < m_dwSize);
		ASSERT(pElement == nullptr || pElement > E_MAX_STATUS);

		if(!IsValid()) return FALSE;

		VTPTR& pValue = INDEX_VAL(dwIndex);
		ENSURE(pValue == E_LOCKED);

		if(pElement == nullptr)
			pValue = E_EMPTY;
		else
			pValue = pElement;

		return TRUE;
	}

public:

	void Reset(DWORD dwSize = 0)
	{
		if(IsValid())
			Destroy();
		if(dwSize > 0)
			Create(dwSize);
	}

	void Clear()
	{
		for(DWORD dwIndex = 0; dwIndex < m_dwSize; dwIndex++)
		{
			VTPTR& pValue = INDEX_VAL(dwIndex);

			if( pValue > E_MAX_STATUS)
			{
				T::Destruct((TPTR)pValue);
				pValue = E_EMPTY;
			}
		}

		Reset();
	}

	DWORD Size()		{return m_dwSize;}
	DWORD Elements()	{return m_seqPut - m_seqGet;}
	BOOL IsFull()		{return Elements() == Size();}
	BOOL IsEmpty()		{return Elements() == 0;}
	BOOL IsValid()		{return m_pv != nullptr;}

private:

	BOOL HasPutSpace(DWORD seqPut)
	{
		return ((int)(seqPut - m_seqGet) < (int)m_dwSize);
	}

	BOOL HasGetSpace(DWORD seqGet)
	{
		return ((int)(m_seqPut - seqGet) > 0);
	}

	void Create(DWORD dwSize)
	{
		ASSERT(!IsValid() && dwSize > 0);

		m_seqPut = 0;
		m_seqGet = 0;
		m_dwSize = dwSize;
		m_pv	 = (VTPTR*)malloc(m_dwSize * sizeof(TPTR));

		::ZeroMemory(m_pv, m_dwSize * sizeof(TPTR));
	}

	void Destroy()
	{
		ASSERT(IsValid());

		free((void*)m_pv);
		m_pv = nullptr;
		m_dwSize = 0;
		m_seqPut = 0;
		m_seqGet = 0;
	}

public:
	CRingPool(DWORD dwSize = 0)
	: m_pv(nullptr)
	, m_dwSize(0)
	, m_seqPut(0)
	, m_seqGet(0)
	{
		Reset(dwSize);
	}

	~CRingPool()
	{
		Reset(0);
	}

private:
	CRingPool(const CRingPool&);
	CRingPool operator = (const CRingPool&);

private:
	DWORD				m_dwSize;
	VTPTR*				m_pv;
	char				pack1[PACK_SIZE_OF(VTPTR*)];
	volatile DWORD		m_seqPut;
	char				pack2[PACK_SIZE_OF(DWORD)];
	volatile DWORD		m_seqGet;
	char				pack3[PACK_SIZE_OF(DWORD)];
};

template <class T> T* const CRingPool<T>::E_EMPTY		= (T*)0x00;
template <class T> T* const CRingPool<T>::E_LOCKED		= (T*)0x01;
template <class T> T* const CRingPool<T>::E_MAX_STATUS	= (T*)0x0F;

// ------------------------------------------------------------------------------------------------------------- //

template <class T> class CCASQueueX
{
private:
	struct Node;
	typedef Node*			NPTR;
	typedef volatile Node*	VNPTR;
	typedef volatile ULONG	VLONG;

	struct Node
	{
		T*		pValue;
		VNPTR	pNext;

		Node(T* val, NPTR next = nullptr)
		: pValue(val), pNext(next)
		{

		}
	};

public:

	void PushBack(T* pVal)
	{
		ASSERT(pVal != nullptr);

		VNPTR pTail	= nullptr;
		NPTR pNode	= new Node(pVal);

		while(true)
		{
			pTail = m_pTail;

			if(::InterlockedCompareExchangePointer((volatile PVOID*)&m_pTail, (PVOID)pNode, (PVOID)pTail) == pTail)
			{
				pTail->pNext = pNode;
				break;
			}
		}

		::InterlockedIncrement(&m_lSize);
	}

	void UnsafePushBack(T* pVal)
	{
		ASSERT(pVal != nullptr);

		NPTR pNode		= new Node(pVal);
		m_pTail->pNext	= pNode;
		m_pTail			= pNode;
		
		::InterlockedIncrement(&m_lSize);
	}

	BOOL PopFront(T** ppVal)
	{
		ASSERT(ppVal != nullptr);

		if(IsEmpty())
			return FALSE;

		BOOL isOK	= FALSE;
		NPTR pHead	= nullptr;
		NPTR pNext	= nullptr;

		while(true)
		{
			Lock();

			pHead = (NPTR)m_pHead;
			pNext = (NPTR)pHead->pNext;

			if(pNext == nullptr)
			{
				Unlock();
				break;
			}

			*ppVal	= pNext->pValue;
			m_pHead	= pNext;

			Unlock();

			isOK	= TRUE;

			::InterlockedDecrement(&m_lSize);

			delete pHead;
			break;
		}

		return isOK;
	}

	BOOL UnsafePopFront(T** ppVal)
	{
		if(!UnsafePeekFront(ppVal))
			return FALSE;

		UnsafePopFrontNotCheck();

		return TRUE;
	}

	BOOL UnsafePeekFront(T** ppVal)
	{
		ASSERT(ppVal != nullptr);

		NPTR pNext = (NPTR)m_pHead->pNext;

		if(pNext == nullptr)
			return FALSE;

		*ppVal = pNext->pValue;

		return TRUE;
	}

	void UnsafePopFrontNotCheck()
	{
		NPTR pHead	= (NPTR)m_pHead;
		NPTR pNext	= (NPTR)pHead->pNext;
		m_pHead		= pNext;

		::InterlockedDecrement(&m_lSize);

		delete pHead;
	}

	void UnsafeClear()
	{
		ASSERT(m_pHead != nullptr);

		m_dwCheckTime = 0;

		while(m_pHead->pNext != nullptr)
			UnsafePopFrontNotCheck();
	}

public:

	ULONG Size()	{return m_lSize;}
	BOOL IsEmpty()	{return m_lSize == 0;}

	void Lock()		{while(!TryLock()) ::YieldProcessor();}
	void Unlock()	{m_lLock = 0;}
	BOOL TryLock()	{return (::InterlockedCompareExchange(&m_lLock, 1, 0) == 0);}

	DWORD GetCheckTime()
	{
		return m_dwCheckTime;
	}

	void UpdateCheckTime(DWORD dwCurrent = 0)
	{
		if(dwCurrent == 0)
			dwCurrent = ::TimeGetTime();

		m_dwCheckTime = dwCurrent;
	}

	int GetCheckTimeGap(DWORD dwCurrent = 0)
	{
		int rs = (int)GetTimeGap32(m_dwCheckTime, dwCurrent);

		if(rs < -60 * 1000)
			rs = MAXINT;

		return rs;
	}

public:

	CCASQueueX() : m_lLock(0), m_lSize(0), m_dwCheckTime(0)
	{
		m_pHead = m_pTail = new Node(nullptr);
	}

	~CCASQueueX()
	{
		ASSERT(m_lLock == 0);
		ASSERT(m_lSize == 0);
		ASSERT(m_pTail == m_pHead);
		ASSERT(m_pHead != nullptr);
		ASSERT(m_pHead->pNext == nullptr);

		UnsafeClear();

		delete m_pHead;
	}

	DECLARE_NO_COPY_CLASS(CCASQueueX)

private:
	VLONG	m_lLock;
	VLONG	m_lSize;
	VNPTR	m_pHead;
	VNPTR	m_pTail;

	volatile DWORD m_dwCheckTime;
};

template <class T> class CCASQueueY
{
public:

	void PushBack(T* pVal)
	{
		CCriSecLock locallock(m_csGuard);

		UnsafePushBack(pVal);
	}

	void UnsafePushBack(T* pVal)
	{
		ASSERT(pVal != nullptr);

		m_lsItems.push_back(pVal);
	}

	void PushFront(T* pVal)
	{
		CCriSecLock locallock(m_csGuard);

		UnsafePushFront(pVal);
	}

	void UnsafePushFront(T* pVal)
	{
		ASSERT(pVal != nullptr);

		m_lsItems.push_front(pVal);
	}

	BOOL PopFront(T** ppVal)
	{
		CCriSecLock locallock(m_csGuard);

		return UnsafePopFront(ppVal);
	}

	BOOL UnsafePopFront(T** ppVal)
	{
		if(!UnsafePeekFront(ppVal))
			return FALSE;

		UnsafePopFrontNotCheck();

		return TRUE;
	}

	BOOL PeekFront(T** ppVal)
	{
		CCriSecLock locallock(m_csGuard);

		return UnsafePeekFront(ppVal);
	}

	BOOL UnsafePeekFront(T** ppVal)
	{
		ASSERT(ppVal != nullptr);

		if(m_lsItems.empty())
			return FALSE;

		*ppVal = m_lsItems.front();

		return TRUE;
	}

	void UnsafePopFrontNotCheck()
	{
		m_lsItems.pop_front();
	}

	void Clear()
	{
		CCriSecLock locallock(m_csGuard);

		UnsafeClear();
	}

	void UnsafeClear()
	{
		m_dwCheckTime = 0;

		m_lsItems.clear();
	}

public:

	ULONG Size()	{return (ULONG)m_lsItems.size();}
	BOOL IsEmpty()	{return (BOOL)m_lsItems.empty();}

	void Lock()		{m_csGuard.Lock();}
	void Unlock()	{m_csGuard.Unlock();}
	BOOL TryLock()	{return m_csGuard.TryLock();}
	CCriSec& Guard(){return m_csGuard;}

	DWORD GetCheckTime()
	{
		return m_dwCheckTime;
	}

	void UpdateCheckTime(DWORD dwCurrent = 0)
	{
		if(dwCurrent == 0)
			dwCurrent = ::TimeGetTime();

		m_dwCheckTime = dwCurrent;
	}

	int GetCheckTimeGap(DWORD dwCurrent = 0)
	{
		int rs = (int)GetTimeGap32(m_dwCheckTime, dwCurrent);

		if(rs < -60 * 1000)
			rs = MAXINT;

		return rs;
	}

public:

	CCASQueueY()
	: m_dwCheckTime(0)
	{

	}

	~CCASQueueY()
	{
		ASSERT(IsEmpty());

		UnsafeClear();
	}

	DECLARE_NO_COPY_CLASS(CCASQueueY)

private:
	CCriSec		m_csGuard;
	deque<T*>	m_lsItems;
	
	volatile DWORD m_dwCheckTime;
};

#define CCASQueue	CCASQueueX

template<typename T>
void ReleaseGCObj(CCASQueue<T>& lsGC, DWORD dwLockTime, BOOL bForce = FALSE)
{
	static const int MIN_CHECK_INTERVAL = 1 * 1000;
	static const int MAX_CHECK_INTERVAL = 15 * 1000;

	T* pObj = nullptr;

	if(bForce)
	{
		CLocalLock<CCASQueue<T>> locallock(lsGC);

		while(lsGC.UnsafePeekFront(&pObj))
		{
			lsGC.UnsafePopFrontNotCheck();
			T::Destruct(pObj);
		}
	}
	else
	{
		if(lsGC.IsEmpty() || lsGC.GetCheckTimeGap() < max(min((int)(dwLockTime / 3), MAX_CHECK_INTERVAL), MIN_CHECK_INTERVAL))
			return;

		T* pFirst	= nullptr;
		BOOL bFirst	= TRUE;
		DWORD now	= 0;

		while(TRUE)
		{
			ASSERT((pObj = nullptr) == nullptr);

			{
				CLocalTryLock<CCASQueue<T>> locallock(lsGC);

				if(!locallock.IsValid())
					break;

				if(bFirst)
				{
					bFirst	= FALSE;
					now		= ::TimeGetTime();

					lsGC.UpdateCheckTime(now);
				}

				if(!lsGC.UnsafePeekFront(&pObj))
					break;

				if((int)(now - pObj->GetFreeTime()) < (int)dwLockTime)
					break;

				lsGC.UnsafePopFrontNotCheck();

				if(pObj->GetCount() > 0)
				{
					lsGC.PushBack(pObj);

					if(pFirst == nullptr)
						pFirst = pObj;
					else if(pFirst == pObj)
						break;

					continue;
				}
			}

			ASSERT(pObj != nullptr);
			T::Destruct(pObj);
		}
	}
}

#if !defined(_WIN64)
	#pragma pack(pop)
#endif


/* ========================================================================== */
/*  PrivateHeap.h
/*  source: Windows\Src\Common\PrivateHeap.h
/* ========================================================================== */

/******************************************************************************
Module:  PrivateHeap.h
Notices: Copyright (c) 2006 Bruce Liang
Purpose: 管理进程私有堆.
Desc:
		 1. CPrivateHeap:		自动创建和销毁进程私有堆
								每一个该类的对象都代表一个私有堆, 所以
								该类对象的特点是: 一般声明周期都比较长
								通常作为全局对象, 其他类的静态成员对象
								或者一些长生命周期类对象的成员对象
		 2. CPrivateHeapBuffer: 在私有堆中自动分配和释放指定大小的内存
								一般用于在函数体内分配和释放局部作用域的堆内存
								从而避免对 CPrivateHeap::Alloc() 和 
								CPrivateHeap::Free() 的调用

Examples:
			CPrivateHeap g_hpPrivate;

			int _tmain(int argc, _TCHAR* argv[])
			{
				CPrivateHeapStrBuffer buff(g_hpPrivate, 32);
				lstrcpy(buff, _T("失败乃成功之母"));
				SIZE_T size = buff.Size();
				buff.ReAlloc(40);
				size = buff.Size();
				std::cout << (TCHAR*)buff << '\n';
				// OR
				// ASSERT(g_hpPrivate.IsValid());
				// TCHAR* pch	= (TCHAR*)g_hpPrivate.Alloc(32 * sizeof(TCHAR));
				// lstrcpy(pch, _T("失败乃成功之母"));
				// SIZE_T size = g_hpPrivate.Size(pch);
				// g_hpPrivate.ReAlloc(pch, 40 * sizeof(TCHAR));
				// size = g_hpPrivate.Size(pch);
				// std::cout << pch << '\n';
				// g_hpPrivate.Free(pch);
				// 
				return 0;
			}

******************************************************************************/

#pragma once

class CPrivateHeapImpl
{
public:
	PVOID Alloc(SIZE_T dwSize, DWORD dwFlags = 0)
		{return ::HeapAlloc(m_hHeap, dwFlags, dwSize);}

	PVOID ReAlloc(PVOID pvMemory, SIZE_T dwSize, DWORD dwFlags = 0)
		{return ::HeapReAlloc(m_hHeap, dwFlags, pvMemory, dwSize);}

	SIZE_T Size(PVOID pvMemory, DWORD dwFlags = 0)
		{return ::HeapSize(m_hHeap, dwFlags, pvMemory);}

	BOOL Free(PVOID pvMemory, DWORD dwFlags = 0)
		{return ::HeapFree(m_hHeap, dwFlags, pvMemory);}

	SIZE_T Compact(DWORD dwFlags = 0)
		{return ::HeapCompact(m_hHeap, dwFlags);}

	BOOL IsValid() {return m_hHeap != nullptr;}

	BOOL Reset()
	{
		if(IsValid()) ::HeapDestroy(m_hHeap);
		m_hHeap = ::HeapCreate(m_dwOptions, m_dwInitSize, m_dwMaxSize);

		return IsValid();
	}

public:
	CPrivateHeapImpl(DWORD dwOptions = 0, SIZE_T dwInitSize = 0, SIZE_T dwMaxSize = 0)
	: m_dwOptions(dwOptions | HEAP_GENERATE_EXCEPTIONS), m_dwInitSize(dwInitSize), m_dwMaxSize(dwMaxSize)
	{
		m_hHeap = ::HeapCreate(m_dwOptions, m_dwInitSize, m_dwMaxSize);
		ENSURE(IsValid());
	}

	~CPrivateHeapImpl	()	{if(IsValid()) ::HeapDestroy(m_hHeap);}

	operator HANDLE	()	{return m_hHeap;}

private:
	CPrivateHeapImpl(const CPrivateHeapImpl&);
	CPrivateHeapImpl operator = (const CPrivateHeapImpl&);

private:
	HANDLE	m_hHeap;
	DWORD	m_dwOptions;
	SIZE_T	m_dwInitSize;
	SIZE_T	m_dwMaxSize;
};

class CGlobalHeapImpl
{
public:
	PVOID Alloc(SIZE_T dwSize, DWORD dwFlags = 0)
	{
		PVOID pv = malloc(dwSize);

		if(!pv)
			throw std::bad_alloc();

		if(dwFlags & HEAP_ZERO_MEMORY)
			ZeroMemory(pv, dwSize);

		return pv;
	}

	PVOID ReAlloc(PVOID pvMemory, SIZE_T dwSize, DWORD dwFlags = 0)
	{
		PVOID pv = realloc(pvMemory, dwSize);

		if(!pv)
		{
			if(pvMemory)
				free(pvMemory);

			throw std::bad_alloc();
		}

		if(dwFlags & HEAP_ZERO_MEMORY)
			ZeroMemory(pv, dwSize);

		return pv;
	}

	BOOL Free(PVOID pvMemory, DWORD dwFlags = 0)
	{
		if(pvMemory)
		{
			free(pvMemory);
			return TRUE;
		}

		return FALSE;
	}

	SIZE_T Compact	(DWORD dwFlags = 0)					{return 0;}
	SIZE_T Size		(PVOID pvMemory, DWORD dwFlags = 0)	{return _msize(pvMemory);}

	BOOL IsValid()	{return TRUE;}
	BOOL Reset()	{return TRUE;}

public:
	CGlobalHeapImpl	(DWORD dwOptions = 0, SIZE_T dwInitSize = 0, SIZE_T dwMaxSize = 0) {}
	~CGlobalHeapImpl()	{}

	operator HANDLE	()	{return nullptr;}

private:
	CGlobalHeapImpl(const CGlobalHeapImpl&);
	CGlobalHeapImpl operator = (const CGlobalHeapImpl&);
};

#ifndef _NOT_USE_PRIVATE_HEAP
	typedef CPrivateHeapImpl	CPrivateHeap;
#else
	typedef CGlobalHeapImpl		CPrivateHeap;
#endif

template<class T> class CPrivateHeapBuffer
{
public:
	CPrivateHeapBuffer(CPrivateHeap& hpPrivate, SIZE_T dwSize = 0)
	: m_hpPrivate	(hpPrivate)
	, m_pvMemory	(nullptr)
	{
		ASSERT(m_hpPrivate.IsValid());
		Alloc(dwSize);
	}

	~CPrivateHeapBuffer() {Free();}

public:
	T* Alloc(SIZE_T dwSize, DWORD dwFlags = 0)
	{
		if(IsValid())
			Free();

		if(dwSize > 0)
			m_pvMemory = (T*)m_hpPrivate.Alloc(dwSize * sizeof(T), dwFlags);

		return m_pvMemory;
	}

	T* ReAlloc(SIZE_T dwSize, DWORD dwFlags = 0)
		{return m_pvMemory = (T*)m_hpPrivate.ReAlloc(m_pvMemory, dwSize * sizeof(T), dwFlags);}

	SIZE_T Size(DWORD dwFlags = 0)
		{return m_hpPrivate.Size(m_pvMemory, dwFlags) / sizeof(T);}

	BOOL Free(DWORD dwFlags = 0)
	{
		BOOL isOK = TRUE;

		if(IsValid())
		{
			isOK		= m_hpPrivate.Free(m_pvMemory, dwFlags);
			m_pvMemory	= nullptr;
		}

		return isOK;
	}

	BOOL IsValid()					{return m_pvMemory != nullptr;}
	operator T* ()			const	{return m_pvMemory;}
	T& operator [] (int i)	const	{return *(m_pvMemory + i);}

private:
	CPrivateHeapBuffer(const CPrivateHeapBuffer&);
	CPrivateHeapBuffer operator = (const CPrivateHeapBuffer&);

private:
	CPrivateHeap&	m_hpPrivate;
	T*				m_pvMemory;
};

typedef CPrivateHeapBuffer<BYTE>	CPrivateHeapByteBuffer;
typedef CPrivateHeapBuffer<TCHAR>	CPrivateHeapStrBuffer;


/* ========================================================================== */
/*  BufferPtr.h
/*  source: Windows\Src\Common\BufferPtr.h
/* ========================================================================== */

#pragma once

#include <memory.h>
#include <malloc.h>

template<class T, size_t MAX_CACHE_SIZE = 0>
class CBufferPtrT
{
public:
	explicit CBufferPtrT(size_t size = 0, bool zero = false)		{Reset(); Malloc(size, zero);}
	explicit CBufferPtrT(const T* pch, size_t size)					{Reset(); Copy(pch, size);}
	CBufferPtrT(const CBufferPtrT& other)							{Reset(); Copy(other);}
	template<size_t S> CBufferPtrT(const CBufferPtrT<T, S>& other)	{Reset(); Copy(other);}

	~CBufferPtrT() {Free();}

	T* Malloc(size_t size = 1, bool zero = false)
	{
		Free();
		return Alloc(size, zero, false);
	}

	T* Realloc(size_t size, bool zero = false)
	{
		return Alloc(size, zero, true);
	}

	void Free()
	{
		if(m_pch)
		{
			free(m_pch);
			Reset();
		}
	}

	template<size_t S> CBufferPtrT& Copy(const CBufferPtrT<T, S>& other)
	{
		if((void*)&other != (void*)this)
			Copy(other.Ptr(), other.Size());

		return *this;
	}

	CBufferPtrT& Copy(const T* pch, size_t size)
	{
		Malloc(size);

		if(m_pch)
			memcpy(m_pch, pch, size * sizeof(T));

		return *this;
	}

	template<size_t S> CBufferPtrT& Cat(const CBufferPtrT<T, S>& other)
	{
		if((void*)&other != (void*)this)
			Cat(other.Ptr(), other.Size());

		return *this;
	}

	CBufferPtrT& Cat(const T* pch, size_t size = 1)
	{
		size_t pre_size = m_size;
		Realloc(m_size + size);

		if(m_pch)
			memcpy(m_pch + pre_size, pch, size * sizeof(T));

		return *this;
	}

	template<size_t S> bool Equal(const CBufferPtrT<T, S>& other) const
	{
		if((void*)&other == (void*)this)
			return true;
		else if(m_size != other.Size())
			return false;
		else if(m_size == 0)
			return true;
		else
			return (memcmp(m_pch, other.Ptr(), m_size * sizeof(T)) == 0);
	}

	bool Equal(T* pch) const
	{
		if(m_pch == pch)
			return true;
		else if(!m_pch || !pch)
			return false;
		else
			return (memcmp(m_pch, pch, m_size * sizeof(T)) == 0);
	}

	size_t SetSize(size_t size)
	{
		if(size < 0 || size > m_capacity)
			size = m_capacity;

		return (m_size = size);
	}

	T*			Ptr()					{return m_pch;}
	const T*	Ptr()			const	{return m_pch;}
	T&			Get(int i)				{return *(m_pch + i);}
	const T&	Get(int i)		const	{return *(m_pch + i);}
	size_t		Size()			const	{return m_size;}
	size_t		Capacity()		const	{return m_capacity;}
	bool		IsValid()		const	{return m_pch != 0;}

	operator							T*	()									{return Ptr();}
	operator const						T*	()			const					{return Ptr();}
	T& operator							[]	(int i)								{return Get(i);}
	const T& operator					[]	(int i)		const					{return Get(i);}
	bool operator						==	(T* pv)		const					{return Equal(pv);}
	template<size_t S> bool operator	==	(const CBufferPtrT<T, S>& other)	{return Equal(other);}
	CBufferPtrT& operator				=	(const CBufferPtrT& other)			{return Copy(other);}
	template<size_t S> CBufferPtrT& operator = (const CBufferPtrT<T, S>& other)	{return Copy(other);}

private:
	void Reset()						{m_pch = 0; m_size = 0; m_capacity = 0;}
	size_t GetAllocSize(size_t size)	{return max(size, min(size * 2, m_size + MAX_CACHE_SIZE));}

	T* Alloc(size_t size, bool zero = false, bool is_realloc = false)
	{
		if(size != m_size)
		{
			size_t rsize = GetAllocSize(size);
			if(size > m_capacity || rsize < m_size)
			{
				T* pch = is_realloc							?
					(T*)realloc(m_pch, rsize * sizeof(T))	:
					(T*)malloc(rsize * sizeof(T))			;

				if(pch || rsize == 0)
				{
					m_pch		= pch;
					m_size		= size;
					m_capacity	= rsize;
				}
				else
				{
					Free();
					throw std::bad_alloc();
				}
			}
			else
				m_size = size;
		}

		if(zero && m_pch)
			memset(m_pch, 0, m_size * sizeof(T));

		return m_pch;
	}

private:
	T*		m_pch;
	size_t	m_size;
	size_t	m_capacity;
};

typedef CBufferPtrT<char>			CCharBufferPtr;
typedef CBufferPtrT<wchar_t>		CWCharBufferPtr;
typedef CBufferPtrT<unsigned char>	CByteBufferPtr;
typedef CByteBufferPtr				CBufferPtr;

#ifdef _UNICODE
	typedef CWCharBufferPtr			CTCharBufferPtr;
#else
	typedef CCharBufferPtr			CTCharBufferPtr;
#endif


/* ========================================================================== */
/*  BufferPool.h
/*  source: Windows\Src\Common\BufferPool.h
/* ========================================================================== */

/******************************************************************************
Module:  BufferPool.h
Notices: Copyright (c) 2013 Bruce Liang
Purpose: 简单内存缓冲池
Desc:
******************************************************************************/

#pragma once

/* [amalgamated] #include "Singleton.h" */
/* [amalgamated] #include "SysHelper.h" */
/* [amalgamated] #include "STLHelper.h" */
/* [amalgamated] #include "RingBuffer.h" */
/* [amalgamated] #include "PrivateHeap.h" */

#pragma warning(push)
#pragma warning(disable: 4458)

struct TItem
{
	template<typename T> friend struct	TSimpleList;
	template<typename T> friend class	CNodePoolT;
	template<typename T> friend struct	TItemListT;

	friend struct						TBuffer;

public:
	int Cat		(const BYTE* pData, int length);
	int Cat		(const TItem& other);
	int Fetch	(BYTE* pData, int length);
	int Peek	(BYTE* pData, int length);
	int Increase(int length);
	int Reduce	(int length);
	void Reset	(int first = 0, int last = 0);

	BYTE*		Ptr		()			{return begin;}
	const BYTE*	Ptr		()	const	{return begin;}
	int			Size	()	const	{return (int)(end - begin);}
	int			Remain	()	const	{return capacity - (int)(end - head);}
	int			Capacity()	const	{return capacity;}
	bool		IsEmpty	()	const	{return Size()	 == 0;}
	bool		IsFull	()	const	{return Remain() == 0;}
	CPrivateHeap& GetPrivateHeap()	{return heap;}

public:
	operator		BYTE* ()		{return Ptr();}
	operator const	BYTE* () const	{return Ptr();}

public:
	static TItem* Construct(CPrivateHeap& heap,
							int		capacity	= DEFAULT_ITEM_CAPACITY,
							BYTE*	pData		= nullptr,
							int		length		= 0);

	static void Destruct(TItem* pItem);

private:
	TItem(CPrivateHeap& hp, BYTE* pHead, int cap = DEFAULT_ITEM_CAPACITY, BYTE* pData = nullptr, int length = 0)
	: heap(hp), head(pHead), begin(pHead), end(pHead), capacity(cap), next(nullptr), last(nullptr)
	{
		if(pData != nullptr && length != 0)
			Cat(pData, length);
	}

	~TItem() {}

	DECLARE_NO_COPY_CLASS(TItem)

public:
	static const DWORD DEFAULT_ITEM_CAPACITY;

private:
	CPrivateHeap& heap;

private:
	TItem* next;
	TItem* last;

	int		capacity;
	BYTE*	head;
	BYTE*	begin;
	BYTE*	end;
};

template<class T> struct TSimpleList
{
public:
	T* PushFront(T* pItem)
	{
		if(pFront != nullptr)
		{
			pFront->last = pItem;
			pItem->next	 = pFront;
		}
		else
		{
			pItem->last = nullptr;
			pItem->next = nullptr;
			pBack		= pItem;
		}

		pFront = pItem;
		++size;

		return pItem;
	}

	T* PushBack(T* pItem)
	{
		if(pBack != nullptr)
		{
			pBack->next	= pItem;
			pItem->last	= pBack;
		}
		else
		{
			pItem->last = nullptr;
			pItem->next = nullptr;
			pFront		= pItem;
		}

		pBack = pItem;
		++size;

		return pItem;
	}

	T* PopFront()
	{
		T* pItem = pFront;

		if(pFront != pBack)
		{
			pFront = pFront->next;
			pFront->last = nullptr;
		}
		else if(pFront != nullptr)
		{
			pFront	= nullptr;
			pBack	= nullptr;
		}

		if(pItem != nullptr)
		{
			pItem->next = nullptr;
			pItem->last = nullptr;

			--size;
		}

		return pItem;
	}

	T* PopBack()
	{
		T* pItem = pBack;

		if(pFront != pBack)
		{
			pBack = pBack->last;
			pBack->next	= nullptr;
		}
		else if(pBack != nullptr)
		{
			pFront	= nullptr;
			pBack	= nullptr;
		}

		if(pItem != nullptr)
		{
			pItem->next = nullptr;
			pItem->last = nullptr;

			--size;
		}

		return pItem;
	}

	TSimpleList<T>& Shift(TSimpleList<T>& other)
	{
		if(&other != this && other.size > 0)
		{
			if(size > 0)
			{
				pBack->next = other.pFront;
				other.pFront->last = pBack;
			}
			else
			{
				pFront = other.pFront;
			}

			pBack	 = other.pBack;
			size	+= other.size;

			other.Reset();
		}

		return *this;
	}

	void Clear()
	{
		if(size > 0)
		{
			T* pItem;
			while((pItem = PopFront()) != nullptr)
				T::Destruct(pItem);
		}
	}

	T*		Front	()	const	{return pFront;}
	T*		Back	()	const	{return pBack;}
	int		Size	()	const	{return size;}
	bool	IsEmpty	()	const	{return size == 0;}

public:
	TSimpleList()	{Reset();}
	~TSimpleList()	{Clear();}

	DECLARE_NO_COPY_CLASS(TSimpleList<T>)

private:
	void Reset()
	{
		pFront	= nullptr;
		pBack	= nullptr;
		size	= 0;
	}

private:
	int	size;
	T*	pFront;
	T*	pBack;
};

template<class T> class CNodePoolT
{
public:
	void PutFreeItem(T* pItem)
	{
		ASSERT(pItem != nullptr);

		if(!m_lsFreeItem.TryPut(pItem))
			T::Destruct(pItem);
	}

	void PutFreeItem(TSimpleList<T>& lsItem)
	{
		if(lsItem.IsEmpty())
			return;

		T* pItem;
		while((pItem = lsItem.PopFront()) != nullptr)
			PutFreeItem(pItem);
	}

	T* PickFreeItem()
	{
		T* pItem = nullptr;

		if(!m_lsFreeItem.TryGet(&pItem))
			pItem = T::Construct(m_heap, m_dwItemCapacity);

		ASSERT(pItem);
		pItem->Reset();
		
		return pItem;
	}

	void Prepare()
	{
		m_lsFreeItem.Reset(m_dwPoolSize);
	}

	void Clear()
	{
		m_lsFreeItem.Clear();

		m_heap.Reset();
	}

public:
	void SetItemCapacity(DWORD dwItemCapacity)	{m_dwItemCapacity	= dwItemCapacity;}
	void SetPoolSize	(DWORD dwPoolSize)		{m_dwPoolSize		= dwPoolSize;}
	void SetPoolHold	(DWORD dwPoolHold)		{m_dwPoolHold		= dwPoolHold;}
	DWORD GetItemCapacity	()					{return m_dwItemCapacity;}
	DWORD GetPoolSize		()					{return m_dwPoolSize;}
	DWORD GetPoolHold		()					{return m_dwPoolHold;}

public:
	CNodePoolT(	DWORD dwPoolSize	 = DEFAULT_POOL_SIZE,
				DWORD dwPoolHold	 = DEFAULT_POOL_HOLD,
				DWORD dwItemCapacity = DEFAULT_ITEM_CAPACITY)
				: m_dwPoolSize(dwPoolSize)
				, m_dwPoolHold(dwPoolHold)
				, m_dwItemCapacity(dwItemCapacity)
	{
	}

	~CNodePoolT()	{Clear();}

	DECLARE_NO_COPY_CLASS(CNodePoolT)

public:
	static const DWORD DEFAULT_ITEM_CAPACITY;
	static const DWORD DEFAULT_POOL_SIZE;
	static const DWORD DEFAULT_POOL_HOLD;

private:
	CPrivateHeap	m_heap;

	DWORD			m_dwItemCapacity;
	DWORD			m_dwPoolSize;
	DWORD			m_dwPoolHold;

	CRingPool<T>	m_lsFreeItem;
};

template<class T> const DWORD CNodePoolT<T>::DEFAULT_ITEM_CAPACITY	= TItem::DEFAULT_ITEM_CAPACITY;
template<class T> const DWORD CNodePoolT<T>::DEFAULT_POOL_SIZE		= DEFAULT_BUFFER_CACHE_POOL_SIZE;
template<class T> const DWORD CNodePoolT<T>::DEFAULT_POOL_HOLD		= DEFAULT_BUFFER_CACHE_POOL_HOLD;

typedef CNodePoolT<TItem>	CItemPool;

template<class T> struct TItemListT : public TSimpleList<T>
{
public:
	int Cat(const BYTE* pData, int length)
	{
		int remain = length;

		while(remain > 0)
		{
			T* pItem = Back();

			if(pItem == nullptr || pItem->IsFull())
				pItem = PushBack(itPool.PickFreeItem());

			int cat  = pItem->Cat(pData, remain);

			pData	+= cat;
			remain	-= cat;
		}

		return length;
	}

	int Cat(const T* pItem)
	{
		return Cat(pItem->Ptr(), pItem->Size());
	}

	int Cat(const TItemListT<T>& other)
	{
		ASSERT(this != &other);

		int length = 0;

		for(T* pItem = other.Front(); pItem != nullptr; pItem = pItem->next)
			length += Cat(pItem);

		return length;
	}

	int Fetch(BYTE* pData, int length)
	{
		int remain = length;

		while(remain > 0 && Size() > 0)
		{
			T* pItem  = Front();
			int fetch = pItem->Fetch(pData, remain);

			pData	+= fetch;
			remain	-= fetch;

			if(pItem->IsEmpty())
				itPool.PutFreeItem(PopFront());
		}

		return length - remain;
	}

	int Peek(BYTE* pData, int length)
	{
		int remain	= length;
		T* pItem	= Front();

		while(remain > 0 && pItem != nullptr)
		{
			int peek = pItem->Peek(pData, remain);

			pData	+= peek;
			remain	-= peek;
			pItem	 = pItem->next;
		}

		return length - remain;
	}

	int Increase(int length)
	{
		int remain = length;

		while(remain > 0)
		{
			T* pItem = __super::Back();

			if(pItem == nullptr || pItem->IsFull())
			{
				pItem = itPool.PickFreeItem();
				__super::PushBack(pItem);
			}

			remain -= pItem->Increase(remain);
		}

		return length - remain;
	}

	int Reduce(int length)
	{
		int remain = length;

		while(remain > 0 && Size() > 0)
		{
			T* pItem = Front();
			remain  -= pItem->Reduce(remain);

			if(pItem->IsEmpty())
				itPool.PutFreeItem(PopFront());
		}

		return length - remain;
	}

	void Release()
	{
		itPool.PutFreeItem(*this);
	}

	CNodePoolT<T>& GetItemPool() {return itPool;}

public:
	TItemListT(CNodePoolT<T>& pool) : itPool(pool)
	{
	}

private:
	CNodePoolT<T>& itPool;
};

typedef TItemListT<TItem>	TItemList;

template<class T, class length_t = int> struct TItemListExT : public TItemListT<T>
{
public:
	T* PushFront(T* pItem)
	{
		length += pItem->Size();
		return __super::PushFront(pItem);
	}

	T* PushBack(T* pItem)
	{
		length += pItem->Size();
		return __super::PushBack(pItem);
	}

	T* PopFront()
	{
		T* pItem = __super::PopFront();

		if(pItem != nullptr)
			length -= pItem->Size();

		return pItem;
	}

	T* PopBack()
	{
		T* pItem = __super::PopBack();

		if(pItem != nullptr)
			length -= pItem->Size();

		return pItem;
	}

	TItemListExT& Shift(TItemListExT<T>& other)
	{
		if(&other != this && other.length > 0)
		{
			length += other.length;
			other.length = 0;

			__super::Shift(other);
		}

		return *this;
	}

	void Clear()
	{
		__super::Clear();
		length = 0;
	}

	void Release()
	{
		__super::Release();
		length = 0;
	}

public:
	int Cat(const BYTE* pData, int length)
	{
		int cat = __super::Cat(pData, length);
		this->length += cat;

		return cat;
	}

	int Cat(const T* pItem)
	{
		int cat = __super::Cat(pItem->Ptr(), pItem->Size());
		this->length += cat;

		return cat;
	}

	int Cat(const TItemListT<T>& other)
	{
		int cat = __super::Cat(other);
		this->length += cat;

		return cat;
	}

	int Fetch(BYTE* pData, int length)
	{
		int fetch	  = __super::Fetch(pData, length);
		this->length -= fetch;

		return fetch;
	}

	int Increase(int length)
	{
		int increase  = __super::Increase(length);
		this->length += increase;

		return increase;
	}

	int Reduce(int length)
	{
		int reduce	  = __super::Reduce(length);
		this->length -= reduce;

		return reduce;
	}
	
	typename decay<length_t>::type Length() const {return length;}

	int IncreaseLength	(int length) {return (this->length += length);}
	int ReduceLength	(int length) {return (this->length -= length);}

public:
	TItemListExT(CNodePoolT<T>& pool) : TItemListT<T>(pool), length(0)
	{
	}

	~TItemListExT()
	{
		ASSERT(length >= 0);
	}

	DECLARE_NO_COPY_CLASS(TItemListExT)

private:
	length_t length;
};

typedef TItemListExT<TItem>					TItemListEx;
typedef TItemListExT<TItem, volatile int>	TItemListExV;

template<class T> struct TItemPtrT
{
public:
	T* Reset(T* pItem = nullptr)
	{
		if(m_pItem != nullptr)
			itPool.PutFreeItem(m_pItem);

		m_pItem = pItem;

		return m_pItem;
	}

	T* Attach(T* pItem)
	{
		return Reset(pItem);
	}

	T* Detach()
	{
		T* pItem = m_pItem;
		m_pItem	 = nullptr;

		return pItem;
	}

	T* New()
	{
		return Attach(itPool.PickFreeItem());
	}

	bool IsValid		()			{return m_pItem != nullptr;}
	T* operator ->		()			{return m_pItem;}
	T* operator =		(T* pItem)	{return Reset(pItem);}
	operator T*			()			{return m_pItem;}
	T*& PtrRef			()			{return m_pItem;}
	T* Ptr				()			{return m_pItem;}
	const T* Ptr		()	const	{return m_pItem;}
	operator const T*	()	const	{return m_pItem;}

public:
	TItemPtrT(CNodePoolT<T>& pool, T* pItem = nullptr)
	: itPool(pool), m_pItem(pItem)
	{

	}

	TItemPtrT(TItemListT<T>& ls, T* pItem = nullptr)
	: itPool(ls.GetItemPool()), m_pItem(pItem)
	{

	}

	~TItemPtrT()
	{
		Reset();
	}

	DECLARE_NO_COPY_CLASS(TItemPtrT)

private:
	CNodePoolT<T>&	itPool;
	T*				m_pItem;
};

typedef TItemPtrT<TItem> TItemPtr;

struct TBuffer
{
	template<typename T> friend struct TSimpleList;
	friend class CBufferPool;

public:
	static TBuffer* Construct(CBufferPool& pool, ULONG_PTR dwID);
	static void Destruct(TBuffer* pBuffer);

public:
	int Cat		(const BYTE* pData, int len);
	int Cat		(const TItem* pItem);
	int Cat		(const TItemList& other);
	int Fetch	(BYTE* pData, int length);
	int Peek	(BYTE* pData, int length);
	int Reduce	(int len);

public:
	CCriSec&	CriSec	()	{return cs;}
	TItemList&	ItemList()	{return items;}

	ULONG_PTR ID		()	const	{return id;}
	int Length			()	const	{return length;}
	bool IsValid		()	const	{return id != 0;}

	DWORD GetFreeTime	()	const	{return freeTime;}
	int GetCount		()	const	{return 0;}

private:
	int IncreaseLength	(int len)	{return (length += len);}
	int DecreaseLength	(int len)	{return (length -= len);}

	void Reset	();

private:
	TBuffer(CPrivateHeap& hp, CItemPool& itPool, ULONG_PTR dwID = 0)
	: heap(hp), items(itPool), id(dwID), length(0)
	{
	}

	~TBuffer()	{}

	DECLARE_NO_COPY_CLASS(TBuffer)

private:
	CPrivateHeap&	heap;

private:
	ULONG_PTR		id;
	int				length;
	DWORD			freeTime;

private:
	TBuffer*		next;
	TBuffer*		last;

	CCriSec			cs;
	TItemList		items;
};

class CBufferPool
{
	typedef CRingPool<TBuffer>						TBufferList;
	typedef CCASQueue<TBuffer>						TBufferQueue;

	typedef CRingCache<TBuffer, ULONG_PTR, true>	TBufferCache;

public:
	void		PutFreeBuffer	(ULONG_PTR dwID);
	TBuffer*	PutCacheBuffer	(ULONG_PTR dwID);
	TBuffer*	FindCacheBuffer	(ULONG_PTR dwID);
	TBuffer*	PickFreeBuffer	(ULONG_PTR dwID);
	void		PutFreeBuffer	(TBuffer* pBuffer);

	void		Prepare			();
	void		Clear			();

	void ReleaseGCBuffer		(BOOL bForce = FALSE);

public:
	void SetItemCapacity	(DWORD dwItemCapacity)		{m_itPool.SetItemCapacity(dwItemCapacity);}
	void SetItemPoolSize	(DWORD dwItemPoolSize)		{m_itPool.SetPoolSize(dwItemPoolSize);}
	void SetItemPoolHold	(DWORD dwItemPoolHold)		{m_itPool.SetPoolHold(dwItemPoolHold);}

	void SetMaxCacheSize	(DWORD dwMaxCacheSize)		{m_dwMaxCacheSize	= dwMaxCacheSize;}
	void SetBufferLockTime	(DWORD dwBufferLockTime)	{m_dwBufferLockTime	= dwBufferLockTime;}
	void SetBufferPoolSize	(DWORD dwBufferPoolSize)	{m_dwBufferPoolSize	= dwBufferPoolSize;}
	void SetBufferPoolHold	(DWORD dwBufferPoolHold)	{m_dwBufferPoolHold	= dwBufferPoolHold;}

	DWORD GetItemCapacity	()							{return m_itPool.GetItemCapacity();}
	DWORD GetItemPoolSize	()							{return m_itPool.GetPoolSize();}
	DWORD GetItemPoolHold	()							{return m_itPool.GetPoolHold();}

	DWORD GetMaxCacheSize	()							{return m_dwMaxCacheSize;}
	DWORD GetBufferLockTime	()							{return m_dwBufferLockTime;}
	DWORD GetBufferPoolSize	()							{return m_dwBufferPoolSize;}
	DWORD GetBufferPoolHold	()							{return m_dwBufferPoolHold;}

	TBuffer* operator []	(ULONG_PTR dwID)			{return FindCacheBuffer(dwID);}

public:
	CBufferPool(DWORD dwPoolSize	 = DEFAULT_BUFFER_POOL_SIZE,
				DWORD dwPoolHold	 = DEFAULT_BUFFER_POOL_HOLD,
				DWORD dwLockTime	 = DEFAULT_BUFFER_LOCK_TIME,
				DWORD dwMaxCacheSize = DEFAULT_MAX_CACHE_SIZE)
	: m_dwBufferPoolSize(dwPoolSize)
	, m_dwBufferPoolHold(dwPoolHold)
	, m_dwBufferLockTime(dwLockTime)
	, m_dwMaxCacheSize(dwMaxCacheSize)
	{

	}

	~CBufferPool()	{Clear();}

	DECLARE_NO_COPY_CLASS(CBufferPool)

public:
	CPrivateHeap&	GetPrivateHeap()	{return m_heap;}
	CItemPool&		GetItemPool()		{return m_itPool;}

public:
	static const DWORD DEFAULT_MAX_CACHE_SIZE;
	static const DWORD DEFAULT_ITEM_CAPACITY;
	static const DWORD DEFAULT_ITEM_POOL_SIZE;
	static const DWORD DEFAULT_ITEM_POOL_HOLD;
	static const DWORD DEFAULT_BUFFER_LOCK_TIME;
	static const DWORD DEFAULT_BUFFER_POOL_SIZE;
	static const DWORD DEFAULT_BUFFER_POOL_HOLD;

private:
	DWORD			m_dwMaxCacheSize;
	DWORD			m_dwBufferLockTime;
	DWORD			m_dwBufferPoolSize;
	DWORD			m_dwBufferPoolHold;

	CPrivateHeap	m_heap;
	CItemPool		m_itPool;

	TBufferCache	m_bfCache;

	TBufferList		m_lsFreeBuffer;
	TBufferQueue	m_lsGCBuffer;
};

#pragma warning(pop)


/* ========================================================================== */
/*  Common/kcp/ikcp.h  -- KCP transport (UDP ARQ)
/*  source: Windows\Src\Common\kcp\ikcp.h
/* ========================================================================== */

//=====================================================================
//
// KCP - A Better ARQ Protocol Implementation
// skywind3000 (at) gmail.com, 2010-2011
//  
// Features:
// + Average RTT reduce 30% - 40% vs traditional ARQ like tcp.
// + Maximum RTT reduce three times vs tcp.
// + Lightweight, distributed as a single source file.
//
//=====================================================================
#ifndef _IKCP_H_
#define _IKCP_H_

#include <stddef.h>
#include <stdlib.h>
#include <assert.h>


//=====================================================================
// 32BIT INTEGER DEFINITION 
//=====================================================================
#ifndef __INTEGER_32_BITS__
#define __INTEGER_32_BITS__
#if defined(_WIN64) || defined(WIN64) || defined(__amd64__) || \
	defined(__x86_64) || defined(__x86_64__) || defined(_M_IA64) || \
	defined(_M_AMD64)
	typedef unsigned int ISTDUINT32;
	typedef int ISTDINT32;
#elif defined(_WIN32) || defined(WIN32) || defined(__i386__) || \
	defined(__i386) || defined(_M_X86)
	typedef unsigned long ISTDUINT32;
	typedef long ISTDINT32;
#elif defined(__MACOS__)
	typedef UInt32 ISTDUINT32;
	typedef SInt32 ISTDINT32;
#elif defined(__APPLE__) && defined(__MACH__)
	#include <sys/types.h>
	typedef u_int32_t ISTDUINT32;
	typedef int32_t ISTDINT32;
#elif defined(__BEOS__)
	#include <sys/inttypes.h>
	typedef u_int32_t ISTDUINT32;
	typedef int32_t ISTDINT32;
#elif (defined(_MSC_VER) || defined(__BORLANDC__)) && (!defined(__MSDOS__))
	typedef unsigned __int32 ISTDUINT32;
	typedef __int32 ISTDINT32;
#elif defined(__GNUC__)
	#include <stdint.h>
	typedef uint32_t ISTDUINT32;
	typedef int32_t ISTDINT32;
#else 
	typedef unsigned long ISTDUINT32; 
	typedef long ISTDINT32;
#endif
#endif


//=====================================================================
// Integer Definition
//=====================================================================
#ifndef __IINT8_DEFINED
#define __IINT8_DEFINED
typedef char IINT8;
#endif

#ifndef __IUINT8_DEFINED
#define __IUINT8_DEFINED
typedef unsigned char IUINT8;
#endif

#ifndef __IUINT16_DEFINED
#define __IUINT16_DEFINED
typedef unsigned short IUINT16;
#endif

#ifndef __IINT16_DEFINED
#define __IINT16_DEFINED
typedef short IINT16;
#endif

#ifndef __IINT32_DEFINED
#define __IINT32_DEFINED
typedef ISTDINT32 IINT32;
#endif

#ifndef __IUINT32_DEFINED
#define __IUINT32_DEFINED
typedef ISTDUINT32 IUINT32;
#endif

#ifndef __IINT64_DEFINED
#define __IINT64_DEFINED
#if defined(_MSC_VER) || defined(__BORLANDC__)
typedef __int64 IINT64;
#else
typedef long long IINT64;
#endif
#endif

#ifndef __IUINT64_DEFINED
#define __IUINT64_DEFINED
#if defined(_MSC_VER) || defined(__BORLANDC__)
typedef unsigned __int64 IUINT64;
#else
typedef unsigned long long IUINT64;
#endif
#endif

#ifndef INLINE
#if defined(__GNUC__)

#if (__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1))
#define INLINE         __inline__ __attribute__((always_inline))
#else
#define INLINE         __inline__
#endif

#elif (defined(_MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__))
#define INLINE __inline
#else
#define INLINE 
#endif
#endif

#if (!defined(__cplusplus)) && (!defined(inline))
#define inline INLINE
#endif


//=====================================================================
// QUEUE DEFINITION                                                  
//=====================================================================
#ifndef __IQUEUE_DEF__
#define __IQUEUE_DEF__

struct IQUEUEHEAD {
	struct IQUEUEHEAD *next, *prev;
};

typedef struct IQUEUEHEAD iqueue_head;


//---------------------------------------------------------------------
// queue init                                                         
//---------------------------------------------------------------------
#define IQUEUE_HEAD_INIT(name) { &(name), &(name) }
#define IQUEUE_HEAD(name) \
	struct IQUEUEHEAD name = IQUEUE_HEAD_INIT(name)

#define IQUEUE_INIT(ptr) ( \
	(ptr)->next = (ptr), (ptr)->prev = (ptr))

#define IOFFSETOF(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define ICONTAINEROF(ptr, type, member) ( \
		(type*)( ((char*)((type*)ptr)) - IOFFSETOF(type, member)) )

#define IQUEUE_ENTRY(ptr, type, member) ICONTAINEROF(ptr, type, member)


//---------------------------------------------------------------------
// queue operation                     
//---------------------------------------------------------------------
#define IQUEUE_ADD(node, head) ( \
	(node)->prev = (head), (node)->next = (head)->next, \
	(head)->next->prev = (node), (head)->next = (node))

#define IQUEUE_ADD_TAIL(node, head) ( \
	(node)->prev = (head)->prev, (node)->next = (head), \
	(head)->prev->next = (node), (head)->prev = (node))

#define IQUEUE_DEL_BETWEEN(p, n) ((n)->prev = (p), (p)->next = (n))

#define IQUEUE_DEL(entry) (\
	(entry)->next->prev = (entry)->prev, \
	(entry)->prev->next = (entry)->next, \
	(entry)->next = 0, (entry)->prev = 0)

#define IQUEUE_DEL_INIT(entry) do { \
	IQUEUE_DEL(entry); IQUEUE_INIT(entry); } while (0)

#define IQUEUE_IS_EMPTY(entry) ((entry) == (entry)->next)

#define iqueue_init		IQUEUE_INIT
#define iqueue_entry	IQUEUE_ENTRY
#define iqueue_add		IQUEUE_ADD
#define iqueue_add_tail	IQUEUE_ADD_TAIL
#define iqueue_del		IQUEUE_DEL
#define iqueue_del_init	IQUEUE_DEL_INIT
#define iqueue_is_empty IQUEUE_IS_EMPTY

#define IQUEUE_FOREACH(iterator, head, TYPE, MEMBER) \
	for ((iterator) = iqueue_entry((head)->next, TYPE, MEMBER); \
		&((iterator)->MEMBER) != (head); \
		(iterator) = iqueue_entry((iterator)->MEMBER.next, TYPE, MEMBER))

#define iqueue_foreach(iterator, head, TYPE, MEMBER) \
	IQUEUE_FOREACH(iterator, head, TYPE, MEMBER)

#define iqueue_foreach_entry(pos, head) \
	for( (pos) = (head)->next; (pos) != (head) ; (pos) = (pos)->next )
	

#define __iqueue_splice(list, head) do {	\
		iqueue_head *first = (list)->next, *last = (list)->prev; \
		iqueue_head *at = (head)->next; \
		(first)->prev = (head), (head)->next = (first);		\
		(last)->next = (at), (at)->prev = (last); }	while (0)

#define iqueue_splice(list, head) do { \
	if (!iqueue_is_empty(list)) __iqueue_splice(list, head); } while (0)

#define iqueue_splice_init(list, head) do {	\
	iqueue_splice(list, head);	iqueue_init(list); } while (0)


#ifdef _MSC_VER
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#pragma warning(disable:4996)
#endif

#endif


//---------------------------------------------------------------------
// BYTE ORDER & ALIGNMENT
//---------------------------------------------------------------------
#ifndef IWORDS_BIG_ENDIAN
    #ifdef _BIG_ENDIAN_
        #if _BIG_ENDIAN_
            #define IWORDS_BIG_ENDIAN 1
        #endif
    #endif
    #ifndef IWORDS_BIG_ENDIAN
        #if defined(__hppa__) || \
            defined(__m68k__) || defined(mc68000) || defined(_M_M68K) || \
            (defined(__MIPS__) && defined(__MIPSEB__)) || \
            defined(__ppc__) || defined(__POWERPC__) || defined(_M_PPC) || \
            defined(__sparc__) || defined(__powerpc__) || \
            defined(__mc68000__) || defined(__s390x__) || defined(__s390__)
            #define IWORDS_BIG_ENDIAN 1
        #endif
    #endif
    #ifndef IWORDS_BIG_ENDIAN
        #define IWORDS_BIG_ENDIAN  0
    #endif
#endif

#ifndef IWORDS_MUST_ALIGN
	#if defined(__i386__) || defined(__i386) || defined(_i386_)
		#define IWORDS_MUST_ALIGN 0
	#elif defined(_M_IX86) || defined(_X86_) || defined(__x86_64__)
		#define IWORDS_MUST_ALIGN 0
	#elif defined(__amd64) || defined(__amd64__)
		#define IWORDS_MUST_ALIGN 0
	#else
		#define IWORDS_MUST_ALIGN 1
	#endif
#endif


//=====================================================================
// Predefine struct
//=====================================================================
struct IKCPCB;
typedef struct IKCPCB ikcpcb;


//=====================================================================
// SEGMENT
//=====================================================================
struct IKCPSEG
{
	struct IQUEUEHEAD node;
	IUINT32 conv;
	IUINT32 cmd;
	IUINT32 frg;
	IUINT32 wnd;
	IUINT32 ts;
	IUINT32 sn;
	IUINT32 una;
	IUINT32 len;
	IUINT32 resendts;
	IUINT32 rto;
	IUINT32 fastack;
	IUINT32 xmit;
	char data[1];
};


//---------------------------------------------------------------------
// IKCPOPS - pluggable congestion control operations
//---------------------------------------------------------------------
struct IKCPOPS
{
	const char *name;
	int (*init)(ikcpcb *kcp);
	void (*release)(ikcpcb *kcp);
	void (*on_ack)(ikcpcb *kcp, IUINT32 acked_segs, IUINT32 acked_bytes,
			IUINT32 prior_in_flight);
	void (*on_fast_retransmit)(ikcpcb *kcp, IUINT32 fast_retrans,
				IUINT32 inflight, IUINT32 prior_cwnd);
	void (*on_timeout)(ikcpcb *kcp, IUINT32 prior_cwnd);
	void (*on_tick)(ikcpcb *kcp);
	void (*on_app_limited)(ikcpcb *kcp, IUINT32 inflight);
	void (*on_rtt)(ikcpcb *kcp, IINT32 rtt);
	void (*on_pkt_sent)(ikcpcb *kcp, IUINT32 sn, IUINT32 ts,
				IUINT32 len, IUINT32 inflight, IUINT32 xmit);
	void (*on_pkt_acked)(ikcpcb *kcp, IUINT32 sn, IUINT32 ts,
				IUINT32 len, IINT32 rtt, IUINT32 xmit);
	IUINT32 (*get_info)(ikcpcb *kcp, void *buf, IUINT32 bufsize);
	IUINT32 (*pacing_rate)(ikcpcb *kcp);
};


//---------------------------------------------------------------------
// IKCPCB
//---------------------------------------------------------------------
struct IKCPCB
{
	IUINT32 conv, mtu, mss, state;
	IUINT32 snd_una, snd_nxt, rcv_nxt;
	IUINT32 ts_recent, ts_lastack, ssthresh;
	IINT32 rx_rttval, rx_srtt, rx_rto, rx_minrto;
	IUINT32 snd_wnd, rcv_wnd, rmt_wnd, cwnd, probe;
	IUINT32 current, interval, ts_flush, xmit;
	IUINT32 nrcv_buf, nsnd_buf;
	IUINT32 nrcv_que, nsnd_que;
	IUINT32 nodelay, updated;
	IUINT32 ts_probe, probe_wait;
	IUINT32 dead_link, incr;
	struct IQUEUEHEAD snd_queue;
	struct IQUEUEHEAD rcv_queue;
	struct IQUEUEHEAD snd_buf;
	struct IQUEUEHEAD rcv_buf;
	IUINT32 *acklist;
	IUINT32 ackcount;
	IUINT32 ackblock;
	IUINT32 ackedlen;
	void *user;
	char *buffer;
	int fastresend;
	int fastlimit;
	int nocwnd, stream;
	const struct IKCPOPS *ccops;
	void *congest;
	int logmask;
	int (*output)(const char *buf, int len, struct IKCPCB *kcp, void *user);
	void (*writelog)(const char *log, struct IKCPCB *kcp, void *user);
};


#define IKCP_LOG_OUTPUT			1
#define IKCP_LOG_INPUT			2
#define IKCP_LOG_SEND			4
#define IKCP_LOG_RECV			8
#define IKCP_LOG_IN_DATA		16
#define IKCP_LOG_IN_ACK			32
#define IKCP_LOG_IN_PROBE		64
#define IKCP_LOG_IN_WINS		128
#define IKCP_LOG_OUT_DATA		256
#define IKCP_LOG_OUT_ACK		512
#define IKCP_LOG_OUT_PROBE		1024
#define IKCP_LOG_OUT_WINS		2048

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------
// interface
//---------------------------------------------------------------------

// create a new kcp control object, 'conv' must be equal in both endpoints
// of the same connection. 'user' will be passed to the output callback.
// output callback can be set up like this: 'kcp->output = my_udp_output'
ikcpcb* ikcp_create(IUINT32 conv, void *user);

// release kcp control object
void ikcp_release(ikcpcb *kcp);

// set output callback, which will be invoked by kcp
void ikcp_setoutput(ikcpcb *kcp, int (*output)(const char *buf, int len, 
	ikcpcb *kcp, void *user));

// user/upper level recv: returns size, returns below zero for EAGAIN
int ikcp_recv(ikcpcb *kcp, char *buffer, int len);

// user/upper level send, returns below zero for error
int ikcp_send(ikcpcb *kcp, const char *buffer, int len);

// update state (call it repeatedly, every 10ms-100ms), or you can ask 
// ikcp_check when to call it again (without ikcp_input/_send calling).
// 'current' - current timestamp in millisec. 
void ikcp_update(ikcpcb *kcp, IUINT32 current);

// Determines when you should invoke ikcp_update next:
// returns the timestamp (in milliseconds) at which you should call
// ikcp_update, assuming no ikcp_input/_send calls occur in between.
// You can call ikcp_update at that time instead of calling it repeatedly.
// Important for reducing unnecessary ikcp_update invocations. Use it to
// schedule ikcp_update (e.g., implementing an epoll-like mechanism,
// or optimizing ikcp_update when handling massive kcp connections).
IUINT32 ikcp_check(const ikcpcb *kcp, IUINT32 current);

// when you receive a low-level packet (e.g., UDP packet), call this
int ikcp_input(ikcpcb *kcp, const char *data, long size);

// flush pending data
void ikcp_flush(ikcpcb *kcp);

// check the size of next message in the recv queue
int ikcp_peeksize(const ikcpcb *kcp);

// change MTU size, default is 1400
int ikcp_setmtu(ikcpcb *kcp, int mtu);

// set maximum window size: sndwnd=32, rcvwnd=32 by default
int ikcp_wndsize(ikcpcb *kcp, int sndwnd, int rcvwnd);

// get how many packets are waiting to be sent
int ikcp_waitsnd(const ikcpcb *kcp);

// fastest: ikcp_nodelay(kcp, 1, 20, 2, 1)
// nodelay: 0:disable (default), 1:enable
// interval: internal update timer interval in ms, default is 100ms
// resend: 0:disable fast resend (default), 1:enable fast resend
// nc: 0:normal congestion control (default), 1:disable congestion control
int ikcp_nodelay(ikcpcb *kcp, int nodelay, int interval, int resend, int nc);

// install congestion control algorithm, NULL restores builtin
int ikcp_setcc(ikcpcb *kcp, const struct IKCPOPS *ops);

// write log with kcp->writelog
void ikcp_log(ikcpcb *kcp, int mask, const char *fmt, ...);

// setup allocator
void ikcp_allocator(void* (*new_malloc)(size_t), void (*new_free)(void*));

// read conv
IUINT32 ikcp_getconv(const void *ptr);


#ifdef __cplusplus
}
#endif

#endif




/* ========================================================================== */
/*  HPTypeDef.h  -- public types
/*  source: C:\Study\hp-socket-6.0.9-src\Windows\Include\HPSocket\HPTypeDef.h
/* ========================================================================== */

#pragma once

/* HP-Socket 版本号 */
#define HP_VERSION_MAJOR		6	// 主版本号
#define HP_VERSION_MINOR		0	// 子版本号
#define HP_VERSION_REVISE		9	// 修正版本号
#define HP_VERSION_BUILD		1	// 构建编号

//#define _UDP_DISABLED				// 禁用 UDP
//#define _SSL_DISABLED				// 禁用 SSL
//#define _HTTP_DISABLED			// 禁用 HTTP
//#define _ZLIB_DISABLED			// 禁用 ZLIB
//#define _BROTLI_DISABLED			// 禁用 BROTLI

/* 是否启用 UDP，如果定义了 _UDP_DISABLED 则禁用（默认：启用） */
#if !defined(_UDP_DISABLED)
	#ifndef _UDP_SUPPORT
		#define _UDP_SUPPORT
	#endif
#endif

/* 是否启用 SSL，如果定义了 _SSL_DISABLED 则禁用（默认：启用） */
#if !defined(_SSL_DISABLED)
	#ifndef _SSL_SUPPORT
		#define _SSL_SUPPORT
	#endif
#endif

/* 是否启用 HTTP，如果定义了 _HTTP_DISABLED 则禁用（默认：启用） */
#if !defined(_HTTP_DISABLED)
	#ifndef _HTTP_SUPPORT
		#define _HTTP_SUPPORT
	#endif
#endif

/* 是否启用 ZLIB，如果定义了 _ZLIB_DISABLED 则禁用（默认：启用） */
#if !defined(_ZLIB_DISABLED)
	#ifndef _ZLIB_SUPPORT
		#define _ZLIB_SUPPORT
	#endif
#endif

/* 是否启用 BROTLI，如果定义了 _BROTLI_DISABLED 则禁用（默认：启用） */
#if !defined(_BROTLI_DISABLED)
	#ifndef _BROTLI_SUPPORT
		#define _BROTLI_SUPPORT
	#endif
#endif

/**************************************************/
/********** imports / exports HPSocket4C **********/

#ifdef HPSOCKET_STATIC_LIB
	#define HPSOCKET_API		EXTERN_C
#else
	#ifdef HPSOCKET_EXPORTS
		#define HPSOCKET_API	EXTERN_C __declspec(dllexport)
	#else
		#define HPSOCKET_API	EXTERN_C __declspec(dllimport)
	#endif
#endif

#define __HP_CALL				__stdcall

/*****************************************************************************************************************************************************/
/**************************************************************** Base Type Definitions **************************************************************/
/*****************************************************************************************************************************************************/

typedef const BYTE*		LPCBYTE, PCBYTE;
typedef ULONG_PTR		TID, THR_ID, NTHR_ID, PID, PRO_ID;

/************************************************************************
名称：连接 ID 数据类型
描述：应用程序可以把 CONNID 定义为自身需要的类型（如：ULONG / ULONGLONG）
************************************************************************/
typedef ULONG_PTR		CONNID, HP_CONNID;

/************************************************************************
名称：通信组件服务状态
描述：应用程序可以通过通信组件的 GetState() 方法获取组件当前服务状态
************************************************************************/
typedef enum EnServiceState
{
	SS_STARTING	= 0,	// 正在启动
	SS_STARTED	= 1,	// 已经启动
	SS_STOPPING	= 2,	// 正在停止
	SS_STOPPED	= 3,	// 已经停止
} En_HP_ServiceState;

/************************************************************************
名称：Socket 操作类型
描述：应用程序的 OnClose() 事件中通过该参数标识是哪种操作导致的错误
************************************************************************/
typedef enum EnSocketOperation
{
	SO_UNKNOWN	= 0,	// Unknown
	SO_ACCEPT	= 1,	// Acccept
	SO_CONNECT	= 2,	// Connect
	SO_SEND		= 3,	// Send
	SO_RECEIVE	= 4,	// Receive
	SO_CLOSE	= 5,	// Close
} En_HP_SocketOperation;

/************************************************************************
名称：事件处理结果
描述：事件的返回值，不同的返回值会影响通信组件的后续行为
************************************************************************/
typedef enum EnHandleResult
{
	HR_OK		= 0,	// 成功
	HR_IGNORE	= 1,	// 忽略
	HR_ERROR	= 2,	// 错误
} En_HP_HandleResult;

/************************************************************************
名称：数据抓取结果
描述：数据抓取操作的返回值
************************************************************************/
typedef enum EnFetchResult
{
	FR_OK				= 0,	// 成功
	FR_LENGTH_TOO_LONG	= 1,	// 抓取长度过大
	FR_DATA_NOT_FOUND	= 2,	// 找不到 ConnID 对应的数据
} En_HP_FetchResult;

/************************************************************************
名称：数据发送策略
描述：Server 组件和 Agent 组件的数据发送策略

* 打包发送策略（默认）	：尽量把多个发送操作的数据组合在一起发送，增加传输效率
* 安全发送策略			：尽量把多个发送操作的数据组合在一起发送，并控制传输速度，避免缓冲区溢出
* 直接发送策略			：对每一个发送操作都直接投递，适用于负载不高但要求实时性较高的场合
************************************************************************/
typedef enum EnSendPolicy
{
	SP_PACK				= 0,	// 打包模式（默认）
	SP_SAFE				= 1,	// 安全模式
	SP_DIRECT			= 2,	// 直接模式
} En_HP_SendPolicy;

/************************************************************************
名称：OnSend 事件同步策略
描述：Server 组件和 Agent 组件的 OnSend 事件同步策略

* 不同步（默认）	：不同步 OnSend 事件，可能同时触发 OnReceive 和 OnClose 事件
* 同步 OnClose	：只同步 OnClose 事件，可能同时触发 OnReceive 事件
* 同步 OnReceive	：（只用于 TCP 组件）同步 OnReceive 和 OnClose 事件，不可能同时触发 OnReceive 或 OnClose 事件
************************************************************************/
typedef enum EnOnSendSyncPolicy
{
	OSSP_NONE			= 0,	// 不同步（默认）
	OSSP_CLOSE			= 1,	// 同步 OnClose
	OSSP_RECEIVE		= 2,	// 同步 OnReceive（只用于 TCP 组件）	
} En_HP_OnSendSyncPolicy;

/************************************************************************
名称：地址重用选项
描述：通信组件底层 socket 的地址重用选项
************************************************************************/
typedef enum EnReuseAddressPolicy
{
	RAP_NONE			= 0,	// 不重用
	RAP_ADDR_ONLY		= 1,	// 仅重用地址
	RAP_ADDR_AND_PORT	= 2,	// 重用地址和端口
} En_HP_ReuseAddressPolicy;

/************************************************************************
名称：操作结果代码
描述：组件 Start() / Stop() 方法执行失败时，可通过 GetLastError() 获取错误代码
************************************************************************/
typedef enum EnSocketError
{
	SE_OK						= NO_ERROR,	// 成功
	SE_ILLEGAL_STATE			= 1,		// 当前状态不允许操作
	SE_INVALID_PARAM			= 2,		// 非法参数
	SE_SOCKET_CREATE			= 3,		// 创建 SOCKET 失败
	SE_SOCKET_BIND				= 4,		// 绑定 SOCKET 失败
	SE_SOCKET_PREPARE			= 5,		// 设置 SOCKET 失败
	SE_SOCKET_LISTEN			= 6,		// 监听 SOCKET 失败
	SE_CP_CREATE				= 7,		// 创建完成端口失败
	SE_WORKER_THREAD_CREATE		= 8,		// 创建工作线程失败
	SE_DETECT_THREAD_CREATE		= 9,		// 创建监测线程失败
	SE_SOCKE_ATTACH_TO_CP		= 10,		// 绑定完成端口失败
	SE_CONNECT_SERVER			= 11,		// 连接服务器失败
	SE_NETWORK					= 12,		// 网络错误
	SE_DATA_PROC				= 13,		// 数据处理错误
	SE_DATA_SEND				= 14,		// 数据发送失败
	SE_GC_START					= 15,		// 垃圾回收启动失败

	/***** SSL Socket 扩展操作结果代码 *****/
	SE_SSL_ENV_NOT_READY		= 101,		// SSL 环境未就绪
} En_HP_SocketError;

/************************************************************************
名称：播送模式
描述：UDP 组件的播送模式（组播或广播）
************************************************************************/
typedef enum EnCastMode
{
	CM_UNICAST		= -1,	// 单播
	CM_MULTICAST	= 0,	// 组播
	CM_BROADCAST	= 1,	// 广播
} En_HP_CastMode;

/************************************************************************
名称：IP 地址类型
描述：IP 地址类型枚举值
************************************************************************/
typedef enum EnIPAddrType
{
	IPT_ALL		= 0,		// 所有
	IPT_IPV4	= 1,		// IPv4
	IPT_IPV6	= 2,		// IPv6
} En_HP_IPAddrType;

/************************************************************************
名称：IP 地址条目结构体
描述：IP 地址的地址簇/地址值结构体
************************************************************************/
typedef struct TIPAddr
{
	En_HP_IPAddrType type;
	LPCTSTR			 address;
} *LPTIPAddr, HP_TIPAddr, *HP_LPTIPAddr;

/************************************************************************
名称：拒绝策略
描述：调用被拒绝后的处理策略
************************************************************************/
typedef enum EnRejectedPolicy
{
	TRP_CALL_FAIL	= 0,	// 立刻返回失败
	TRP_WAIT_FOR	= 1,	// 等待（直到成功、超时或线程池关闭等原因导致失败）
	TRP_CALLER_RUN	= 2,	// 调用者线程直接执行
} En_HP_RejectedPolicy;

/************************************************************************
名称：任务缓冲区类型
描述：TSockeTask 对象创建和销毁时，根据不同类型的缓冲区类型作不同的处理
************************************************************************/
typedef enum EnTaskBufferType
{
	TBT_COPY	= 0,	// 深拷贝
	TBT_REFER	= 1,	// 浅拷贝
	TBT_ATTACH	= 2,	// 附属（不负责创建，但负责销毁）
} En_HP_TaskBufferType;

/************************************************************************
名称：任务处理函数
描述：任务处理入口函数
参数：pvArg -- 自定义参数
返回值：（无）
************************************************************************/
typedef VOID (__HP_CALL *Fn_TaskProc)(PVOID pvArg);
typedef Fn_TaskProc	HP_Fn_TaskProc;

struct TSocketTask;

/************************************************************************
名称：Socket 任务处理函数
描述：Socket 任务处理入口函数
参数：pTask -- Socket 任务结构体指针
返回值：（无）
************************************************************************/
typedef VOID (__HP_CALL *Fn_SocketTaskProc)(struct TSocketTask* pTask);
typedef Fn_SocketTaskProc	HP_Fn_SocketTaskProc;

/************************************************************************
名称：Socket 任务结构体
描述：封装 Socket 任务相关数据结构
************************************************************************/
typedef struct TSocketTask
{
	HP_Fn_SocketTaskProc	fn;			// 任务处理函数
	PVOID					sender;		// 发起对象
	CONNID					connID;		// 连接 ID
	LPCBYTE					buf;		// 数据缓冲区
	INT						bufLen;		// 数据缓冲区长度
	En_HP_TaskBufferType	bufType;	// 缓冲区类型
	WPARAM					wparam;		// 自定义参数
	LPARAM					lparam;		// 自定义参数
} *LPTSocketTask, HP_TSocketTask, *HP_LPTSocketTask;

/************************************************************************
名称：获取 HPSocket 版本号
描述：版本号（4 个字节分别为：主版本号，子版本号，修正版本号，构建编号）
************************************************************************/
inline DWORD GetHPSocketVersion()
{
	return (HP_VERSION_MAJOR << 24) | (HP_VERSION_MINOR << 16) | (HP_VERSION_REVISE << 8) | HP_VERSION_BUILD;
}

/*****************************************************************************************************************************************************/
/**************************************************************** SSL Type Definitions ***************************************************************/
/*****************************************************************************************************************************************************/

#ifdef _SSL_SUPPORT

/************************************************************************
名称：SSL 工作模式
描述：标识 SSL 的工作模式，客户端模式或服务端模式
************************************************************************/
typedef enum EnSSLSessionMode
{
	SSL_SM_CLIENT	= 0,	// 客户端模式
	SSL_SM_SERVER	= 1,	// 服务端模式
} En_HP_SSLSessionMode;

/************************************************************************
名称：SSL 验证模式
描述：SSL 验证模式选项，SSL_VM_PEER 可以和后面两个选项组合一起
************************************************************************/
typedef enum EnSSLVerifyMode
{
	SSL_VM_NONE					= 0x00,	// SSL_VERIFY_NONE
	SSL_VM_PEER					= 0x01,	// SSL_VERIFY_PEER
	SSL_VM_FAIL_IF_NO_PEER_CERT	= 0x02,	// SSL_VERIFY_FAIL_IF_NO_PEER_CERT
	SSL_VM_CLIENT_ONCE			= 0x04,	// SSL_VERIFY_CLIENT_ONCE
} En_HP_SSLVerifyMode;

/************************************************************************
名称：SSL Session 信息类型
描述：用于 GetSSLSessionInfo()，标识输出的 Session 信息类型
************************************************************************/
typedef enum EnSSLSessionInfo
{
	SSL_SSI_MIN					= 0,	// 
	SSL_SSI_CTX					= 0,	// SSL CTX				（输出类型：SSL_CTX*）
	SSL_SSI_CTX_METHOD			= 1,	// SSL CTX Mehtod		（输出类型：SSL_METHOD*）
	SSL_SSI_CTX_CIPHERS			= 2,	// SSL CTX Ciphers		（输出类型：STACK_OF(SSL_CIPHER)*）
	SSL_SSI_CTX_CERT_STORE		= 3,	// SSL CTX Cert Store	（输出类型：X509_STORE*）
	SSL_SSI_SERVER_NAME_TYPE	= 4,	// Server Name Type		（输出类型：int）
	SSL_SSI_SERVER_NAME			= 5,	// Server Name			（输出类型：LPCSTR）
	SSL_SSI_VERSION				= 6,	// SSL Version			（输出类型：LPCSTR）
	SSL_SSI_METHOD				= 7,	// SSL Method			（输出类型：SSL_METHOD*）
	SSL_SSI_CERT				= 8,	// SSL Cert				（输出类型：X509*）
	SSL_SSI_PKEY				= 9,	// SSL Private Key		（输出类型：EVP_PKEY*）
	SSL_SSI_CURRENT_CIPHER		= 10,	// SSL Current Cipher	（输出类型：SSL_CIPHER*）
	SSL_SSI_CIPHERS				= 11,	// SSL Available Ciphers（输出类型：STACK_OF(SSL_CIPHER)*）
	SSL_SSI_CLIENT_CIPHERS		= 12,	// SSL Client Ciphers	（输出类型：STACK_OF(SSL_CIPHER)*）
	SSL_SSI_PEER_CERT			= 13,	// SSL Peer Cert		（输出类型：X509*）
	SSL_SSI_PEER_CERT_CHAIN		= 14,	// SSL Peer Cert Chain	（输出类型：STACK_OF(X509)*）
	SSL_SSI_VERIFIED_CHAIN		= 15,	// SSL Verified Chain	（输出类型：STACK_OF(X509)*）
	SSL_SSI_MAX					= 15,	// 
} En_HP_SSLSessionInfo;

/************************************************************************
名称：SNI 服务名称回调函数
描述：根据服务器名称选择 SSL 证书
参数：	
		lpszServerName -- 服务器名称（域名）

返回值：
		0	 -- 成功，使用默认 SSL 证书索引
		正数	 -- 成功，使用返回值对应的 SNI 主机证书索引
		负数	 -- 失败，中断 SSL 握手

************************************************************************/
typedef int (__HP_CALL *Fn_SNI_ServerNameCallback)(LPCTSTR lpszServerName, PVOID pContext);
typedef Fn_SNI_ServerNameCallback	HP_Fn_SNI_ServerNameCallback;

#endif

/*****************************************************************************************************************************************************/
/**************************************************************** HTTP Type Definitions **************************************************************/
/*****************************************************************************************************************************************************/

#ifdef _HTTP_SUPPORT

/************************************************************************
名称：HTTP 版本
描述：低字节：主版本号，高字节：次版本号
************************************************************************/

typedef enum EnHttpVersion
{
	HV_1_0	= MAKEWORD(1, 0),	// HTTP/1.0
	HV_1_1	= MAKEWORD(1, 1)	// HTTP/1.1
} En_HP_HttpVersion;

/************************************************************************
名称：URL 域
描述：HTTP 请求行中 URL 段位的域定义
************************************************************************/
typedef enum EnHttpUrlField
{ 
	HUF_SCHEMA		= 0,	// Schema
	HUF_HOST		= 1,	// Host
	HUF_PORT		= 2,	// Port
	HUF_PATH		= 3,	// Path
	HUF_QUERY		= 4,	// Query String
	HUF_FRAGMENT	= 5,	// Fragment
	HUF_USERINFO	= 6,	// User Info
	HUF_MAX			= 7,	// (Field Count)
} En_HP_HttpUrlField;

/************************************************************************
名称：HTTP 解析结果标识
描述：指示 HTTP 解析器是否继续执行解析操作
************************************************************************/
typedef enum EnHttpParseResult
{
	HPR_OK			= 0,	// 解析成功
	HPR_SKIP_BODY	= 1,	// 跳过当前请求 BODY（仅用于 OnHeadersComplete 事件）
	HPR_UPGRADE		= 2,	// 升级协议（仅用于 OnHeadersComplete 事件）
	HPR_ERROR		= -1,	// 解析错误，终止解析，断开连接
} En_HP_HttpParseResult;

/************************************************************************
名称：HTTP 协议升级类型
描述：标识 HTTP 升级为哪种协议
************************************************************************/
typedef enum EnHttpUpgradeType
{
	HUT_NONE		= 0,	// 没有升级
	HUT_WEB_SOCKET	= 1,	// WebSocket
	HUT_HTTP_TUNNEL	= 2,	// HTTP 隧道
	HUT_UNKNOWN		= -1,	// 未知类型
} En_HP_HttpUpgradeType;

/************************************************************************
名称：HTTP 状态码
描述：HTTP 标准状态码
************************************************************************/
typedef enum EnHttpStatusCode
{ 
	HSC_CONTINUE									= 100,
	HSC_SWITCHING_PROTOCOLS							= 101,
	HSC_PROCESSING									= 102,
	HSC_EARLY_HINTS									= 103,
	HSC_RESPONSE_IS_STALE							= 110,
	HSC_REVALIDATION_FAILED							= 111,
	HSC_DISCONNECTED_OPERATION						= 112,
	HSC_HEURISTIC_EXPIRATION						= 113,
	HSC_MISCELLANEOUS_WARNING						= 199,

	HSC_OK											= 200,
	HSC_CREATED										= 201,
	HSC_ACCEPTED									= 202,
	HSC_NON_AUTHORITATIVE_INFORMATION				= 203,
	HSC_NO_CONTENT									= 204,
	HSC_RESET_CONTENT								= 205,
	HSC_PARTIAL_CONTENT								= 206,
	HSC_MULTI_STATUS								= 207,
	HSC_ALREADY_REPORTED							= 208,
	HSC_TRANSFORMATION_APPLIED						= 214,
	HSC_IM_USED										= 226,
	HSC_MISCELLANEOUS_PERSISTENT_WARNING			= 299,

	HSC_MULTIPLE_CHOICES							= 300,
	HSC_MOVED_PERMANENTLY							= 301,
	HSC_MOVED_TEMPORARILY							= 302,
	HSC_SEE_OTHER									= 303,
	HSC_NOT_MODIFIED								= 304,
	HSC_USE_PROXY									= 305,
	HSC_SWITCH_PROXY								= 306,
	HSC_TEMPORARY_REDIRECT							= 307,
	HSC_PERMANENT_REDIRECT							= 308,

	HSC_BAD_REQUEST									= 400,
	HSC_UNAUTHORIZED								= 401,
	HSC_PAYMENT_REQUIRED							= 402,
	HSC_FORBIDDEN									= 403,
	HSC_NOT_FOUND									= 404,
	HSC_METHOD_NOT_ALLOWED							= 405,
	HSC_NOT_ACCEPTABLE								= 406,
	HSC_PROXY_AUTHENTICATION_REQUIRED				= 407,
	HSC_REQUEST_TIMEOUT								= 408,
	HSC_CONFLICT									= 409,
	HSC_GONE										= 410,
	HSC_LENGTH_REQUIRED								= 411,
	HSC_PRECONDITION_FAILED							= 412,
	HSC_REQUEST_ENTITY_TOO_LARGE					= 413,
	HSC_REQUEST_URI_TOO_LONG						= 414,
	HSC_UNSUPPORTED_MEDIA_TYPE						= 415,
	HSC_REQUESTED_RANGE_NOT_SATISFIABLE				= 416,
	HSC_EXPECTATION_FAILED							= 417,
	HSC_IM_A_TEAPOT									= 418,
	HSC_PAGE_EXPIRED								= 419,
	HSC_ENHANCE_YOUR_CALM							= 420,
	HSC_MISDIRECTED_REQUEST							= 421,
	HSC_UNPROCESSABLE_ENTITY						= 422,
	HSC_LOCKED										= 423,
	HSC_FAILED_DEPENDENCY							= 424,
	HSC_UNORDERED_COLLECTION						= 425,
	HSC_UPGRADE_REQUIRED							= 426,
	HSC_PRECONDITION_REQUIRED						= 428,
	HSC_TOO_MANY_REQUESTS							= 429,
	HSC_REQUEST_HEADER_FIELDS_TOO_LARGE_UNOFFICIAL	= 430,
	HSC_REQUEST_HEADER_FIELDS_TOO_LARGE				= 431,
	HSC_LOGIN_TIMEOUT								= 440,
	HSC_NO_RESPONSE									= 444,
	HSC_RETRY_WITH									= 449,
	HSC_BLOCKED_BY_PARENTAL_CONTROL					= 450,
	HSC_UNAVAILABLE_FOR_LEGAL_REASONS				= 451,
	HSC_CLIENT_CLOSED_LOAD_BALANCED_REQUEST			= 460,
	HSC_INVALID_X_FORWARDED_FOR						= 463,
	HSC_REQUEST_HEADER_TOO_LARGE					= 494,
	HSC_SSL_CERTIFICATE_ERROR						= 495,
	HSC_SSL_CERTIFICATE_REQUIRED					= 496,
	HSC_HTTP_REQUEST_SENT_TO_HTTPS_PORT				= 497,
	HSC_INVALID_TOKEN								= 498,
	HSC_CLIENT_CLOSED_REQUEST						= 499,

	HSC_INTERNAL_SERVER_ERROR						= 500,
	HSC_NOT_IMPLEMENTED								= 501,
	HSC_BAD_GATEWAY									= 502,
	HSC_SERVICE_UNAVAILABLE							= 503,
	HSC_GATEWAY_TIMEOUT								= 504,
	HSC_HTTP_VERSION_NOT_SUPPORTED					= 505,
	HSC_VARIANT_ALSO_NEGOTIATES						= 506,
	HSC_INSUFFICIENT_STORAGE						= 507,
	HSC_LOOP_DETECTED								= 508,
	HSC_BANDWIDTH_LIMIT_EXCEEDED					= 509,
	HSC_NOT_EXTENDED								= 510,
	HSC_NETWORK_AUTHENTICATION_REQUIRED				= 511,
	HSC_WEB_SERVER_UNKNOWN_ERROR					= 520,
	HSC_WEB_SERVER_IS_DOWN							= 521,
	HSC_CONNECTION_TIMEOUT							= 522,
	HSC_ORIGIN_IS_UNREACHABLE						= 523,
	HSC_TIMEOUT_OCCURED								= 524,
	HSC_SSL_HANDSHAKE_FAILED						= 525,
	HSC_INVALID_SSL_CERTIFICATE						= 526,
	HSC_RAILGUN_ERROR								= 527,
	HSC_SITE_IS_OVERLOADED							= 529,
	HSC_SITE_IS_FROZEN								= 530,
	HSC_IDENTITY_PROVIDER_AUTHENTICATION_ERROR		= 561,
	HSC_NETWORK_READ_TIMEOUT						= 598,
	HSC_NETWORK_CONNECT_TIMEOUT						= 599,

	HSC_UNPARSEABLE_RESPONSE_HEADERS				= 600
} En_HP_HttpStatusCode;

/************************************************************************
名称：Name/Value 结构体
描述：字符串名值对结构体
************************************************************************/
typedef struct TNVPair
{ 
	LPCSTR name;
	LPCSTR value;
}	HP_TNVPair,
TParam, HP_TParam, *LPPARAM, *HP_LPPARAM,
THeader, HP_THeader, *LPHEADER, *HP_LPHEADER,
TCookie, HP_TCookie, *LPCOOKIE, *HP_LPCOOKIE;

#endif

/*****************************************************************************************************************************************************/
/********************************************************** Compress / Decompress Definitions ********************************************************/
/*****************************************************************************************************************************************************/

/************************************************************************
名称：数据回调函数
描述：回调处理过程中产生的数据输出
参数：	
	pData		-- 数据缓冲区
	iLength		-- 数据长度
	pContext	-- 回调上下文

返回值：
		TRUE	-- 成功
		FALSE	-- 失败

************************************************************************/
typedef BOOL (__HP_CALL *Fn_DataCallback)(const BYTE* pData, int iLength, PVOID pContext);
typedef Fn_DataCallback	Fn_CompressDataCallback;
typedef Fn_DataCallback	Fn_DecompressDataCallback;
typedef Fn_DataCallback	HP_Fn_DataCallback;
typedef Fn_DataCallback	HP_Fn_CompressDataCallback;
typedef Fn_DataCallback	HP_Fn_DecompressDataCallback;


/* ========================================================================== */
/*  SocketInterface.h  -- interfaces (TCP + UDP)
/*  source: C:\Study\hp-socket-6.0.9-src\Windows\Include\HPSocket\SocketInterface.h
/* ========================================================================== */

#pragma once

#include <winsock2.h>

/* [amalgamated] #include "HPTypeDef.h" */

/*****************************************************************************************************************************************************/
/***************************************************************** TCP/UDP Interfaces ****************************************************************/
/*****************************************************************************************************************************************************/

/************************************************************************
名称：双接口模版类
描述：定义双接口转换方法
************************************************************************/

#if FALSE

#define __DUAL_VPTR_GAP__	sizeof(PVOID)

class __IFakeDualInterface__
{
public:
	virtual ~__IFakeDualInterface__() {}
};

template<class F, class S> class DualInterface : public F, private __IFakeDualInterface__, public S

#else

#define __DUAL_VPTR_GAP__	0

template<class F, class S> class DualInterface : public F, public S

#endif

{
public:

	/* this 转换为 F* */
	inline static F* ToF(DualInterface* pThis)
	{
		return (F*)(pThis);
	}

	/* F* 转换为 this */
	inline static DualInterface* FromF(F* pF)
	{
		return (DualInterface*)(pF);
	}

	/* this 转换为 S* */
	inline static S* ToS(DualInterface* pThis)
	{
		return (S*)(F2S(ToF(pThis)));
	}

	/* S* 转换为 this */
	inline static DualInterface* FromS(S* pS)
	{
		return FromF(S2F(pS));
	}

	/* S* 转换为 F* */
	inline static F* S2F(S* pS)
	{
		return (F*)((char*)pS - (sizeof(F) + __DUAL_VPTR_GAP__));
	}

	/* F* 转换为 S* */
	inline static S* F2S(F* pF)
	{
		return (S*)((char*)pF + (sizeof(F) + __DUAL_VPTR_GAP__));
	}

public:
	virtual ~DualInterface() {}
};

/************************************************************************
名称：复合 Socket 组件接口
描述：定义复合 Socket 组件的所有操作方法和属性访问方法，复合 Socket 组件同时管理多个 Socket 连接
************************************************************************/
class IComplexSocket
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*
	* 名称：关闭通信组件
	* 描述：关闭通信组件，关闭完成后断开所有连接并释放所有资源
	*		
	* 参数：	
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 GetLastError() 获取错误代码
	*/
	virtual BOOL Stop	()																		= 0;

	/*
	* 名称：发送数据
	* 描述：向指定连接发送数据
	*		
	* 参数：		dwConnID	-- 连接 ID
	*			pBuffer		-- 发送缓冲区
	*			iLength		-- 发送缓冲区长度
	*			iOffset		-- 发送缓冲区指针偏移量
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL Send	(CONNID dwConnID, const BYTE* pBuffer, int iLength, int iOffset = 0)	= 0;

	/*
	* 名称：发送多组数据
	* 描述：向指定连接发送多组数据
	*		TCP - 顺序发送所有数据包 
	*		UDP - 把所有数据包组合成一个数据包发送（数据包的总长度不能大于设置的 UDP 包最大长度） 
	*		
	* 参数：		dwConnID	-- 连接 ID
	*			pBuffers	-- 发送缓冲区数组
	*			iCount		-- 发送缓冲区数目
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL SendPackets(CONNID dwConnID, const WSABUF pBuffers[], int iCount)	= 0;

	/*
	* 名称：暂停/恢复接收
	* 描述：暂停/恢复某个连接的数据接收工作
	*		
	* 参数：		dwConnID	-- 连接 ID
	*			bPause		-- TRUE - 暂停, FALSE - 恢复
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败
	*/
	virtual BOOL PauseReceive(CONNID dwConnID, BOOL bPause = TRUE)					= 0;

	/*
	* 名称：断开连接
	* 描述：断开某个连接
	*		
	* 参数：		dwConnID	-- 连接 ID
	*			bForce		-- 是否强制断开连接
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败
	*/
	virtual BOOL Disconnect(CONNID dwConnID, BOOL bForce = TRUE)					= 0;

	/*
	* 名称：断开超时连接
	* 描述：断开超过指定时长的连接
	*		
	* 参数：		dwPeriod	-- 时长（毫秒）
	*			bForce		-- 是否强制断开连接
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败
	*/
	virtual BOOL DisconnectLongConnections(DWORD dwPeriod, BOOL bForce = TRUE)		= 0;

	/*
	* 名称：断开静默连接
	* 描述：断开超过指定时长的静默连接
	*		
	* 参数：		dwPeriod	-- 时长（毫秒）
	*			bForce		-- 是否强制断开连接
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败
	*/
	virtual BOOL DisconnectSilenceConnections(DWORD dwPeriod, BOOL bForce = TRUE)	= 0;

	/*
	* 名称：等待
	* 描述：等待通信组件停止运行
	*		
	* 参数：		dwMilliseconds	-- 超时时间（毫秒，默认：-1，永不超时）
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL Wait(DWORD dwMilliseconds = INFINITE)								= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/*
	* 名称：设置连接的附加数据
	* 描述：是否为连接绑定附加数据或者绑定什么样的数据，均由应用程序自身决定
	*		
	* 参数：		dwConnID	-- 连接 ID
	*			pv			-- 数据
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败（无效的连接 ID）
	*/
	virtual BOOL SetConnectionExtra		(CONNID dwConnID, PVOID pExtra)			= 0;

	/*
	* 名称：获取连接的附加数据
	* 描述：是否为连接绑定附加数据或者绑定什么样的数据，均由应用程序自身决定
	*		
	* 参数：		dwConnID	-- 连接 ID
	*			ppv			-- 数据指针
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败（无效的连接 ID）
	*/
	virtual BOOL GetConnectionExtra		(CONNID dwConnID, PVOID* ppExtra)		= 0;

	/* 检测是否为安全连接（SSL/HTTPS） */
	virtual BOOL IsSecure				()										= 0;
	/* 检查通信组件是否已启动 */
	virtual BOOL HasStarted				()										= 0;
	/* 查看通信组件当前状态 */
	virtual EnServiceState GetState		()										= 0;
	/* 获取连接数 */
	virtual DWORD GetConnectionCount	()										= 0;
	/* 获取所有连接的 CONNID */
	virtual BOOL GetAllConnectionIDs	(CONNID pIDs[], DWORD& dwCount)			= 0;
	/* 获取某个连接时长（毫秒） */
	virtual BOOL GetConnectPeriod		(CONNID dwConnID, DWORD& dwPeriod)		= 0;
	/* 获取某个连接静默时间（毫秒） */
	virtual BOOL GetSilencePeriod		(CONNID dwConnID, DWORD& dwPeriod)		= 0;
	/* 获取某个连接的本地地址信息 */
	virtual BOOL GetLocalAddress		(CONNID dwConnID, TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort)	= 0;
	/* 获取某个连接的远程地址信息 */
	virtual BOOL GetRemoteAddress		(CONNID dwConnID, TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort)	= 0;
	/* 获取最近一次失败操作的错误代码 */
	virtual EnSocketError GetLastError	()										= 0;
	/* 获取最近一次失败操作的错误描述 */
	virtual LPCTSTR GetLastErrorDesc	()										= 0;
	/* 获取连接中未发出数据的长度 */
	virtual BOOL GetPendingDataLength	(CONNID dwConnID, int& iPending)		= 0;
	/* 获取连接的数据接收状态 */
	virtual BOOL IsPauseReceive			(CONNID dwConnID, BOOL& bPaused)		= 0;
	/* 检测是否有效连接 */
	virtual BOOL IsConnected			(CONNID dwConnID)						= 0;

	/* 设置地址重用选项 */
	virtual void SetReuseAddressPolicy(EnReuseAddressPolicy enReusePolicy)		= 0;
	/* 设置数据发送策略 */
	virtual void SetSendPolicy				(EnSendPolicy enSendPolicy)			= 0;
	/* 设置 OnSend 事件同步策略（默认：OSSP_NONE，不同步） */
	virtual void SetOnSendSyncPolicy		(EnOnSendSyncPolicy enSyncPolicy)	= 0;
	/* 设置最大连接数（组件会根据设置值预分配内存，因此需要根据实际情况设置，不宜过大）*/
	virtual void SetMaxConnectionCount		(DWORD dwMaxConnectionCount)		= 0;
	/* 设置 Socket 缓存对象锁定时间（毫秒，在锁定期间该 Socket 缓存对象不能被获取使用） */
	virtual void SetFreeSocketObjLockTime	(DWORD dwFreeSocketObjLockTime)		= 0;
	/* 设置 Socket 缓存池大小（通常设置为平均并发连接数的 1/3 - 1/2） */
	virtual void SetFreeSocketObjPool		(DWORD dwFreeSocketObjPool)			= 0;
	/* 设置内存块缓存池大小（通常设置为 Socket 缓存池大小的 2 - 3 倍） */
	virtual void SetFreeBufferObjPool		(DWORD dwFreeBufferObjPool)			= 0;
	/* 设置 Socket 缓存池回收阀值（通常设置为 Socket 缓存池大小的 3 倍） */
	virtual void SetFreeSocketObjHold		(DWORD dwFreeSocketObjHold)			= 0;
	/* 设置内存块缓存池回收阀值 */
	virtual void SetFreeBufferObjHold		(DWORD dwFreeBufferObjHold)			= 0;
	/* 设置工作线程数量（通常设置为 2 * CPU + 2） */
	virtual void SetWorkerThreadCount		(DWORD dwWorkerThreadCount)			= 0;
	/* 设置是否标记静默时间（设置为 TRUE 时 DisconnectSilenceConnections() 和 GetSilencePeriod() 才有效，默认：TRUE） */
	virtual void SetMarkSilence				(BOOL bMarkSilence)					= 0;

	/* 获取地址重用选项 */
	virtual EnReuseAddressPolicy GetReuseAddressPolicy	()	= 0;
	/* 获取数据发送策略 */
	virtual EnSendPolicy GetSendPolicy					()	= 0;
	/* 获取 OnSend 事件同步策略 */
	virtual EnOnSendSyncPolicy GetOnSendSyncPolicy		()	= 0;
	/* 获取最大连接数 */
	virtual DWORD GetMaxConnectionCount					()	= 0;
	/* 获取 Socket 缓存对象锁定时间 */
	virtual DWORD GetFreeSocketObjLockTime				()	= 0;
	/* 获取 Socket 缓存池大小 */
	virtual DWORD GetFreeSocketObjPool					()	= 0;
	/* 获取内存块缓存池大小 */
	virtual DWORD GetFreeBufferObjPool					()	= 0;
	/* 获取 Socket 缓存池回收阀值 */
	virtual DWORD GetFreeSocketObjHold					()	= 0;
	/* 获取内存块缓存池回收阀值 */
	virtual DWORD GetFreeBufferObjHold					()	= 0;
	/* 获取工作线程数量 */
	virtual DWORD GetWorkerThreadCount					()	= 0;
	/* 检测是否标记静默时间 */
	virtual BOOL IsMarkSilence							()	= 0;

public:
	virtual ~IComplexSocket() {}
};

/************************************************************************
名称：通信服务端组件接口
描述：定义通信服务端组件的所有操作方法和属性访问方法
************************************************************************/
class IServer : public IComplexSocket
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*
	* 名称：启动通信组件
	* 描述：启动服务端通信组件，启动完成后可开始接收客户端连接并收发数据
	*		
	* 参数：		lpszBindAddress	-- 监听地址
	*			usPort			-- 监听端口
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 GetLastError() 获取错误代码
	*/
	virtual BOOL Start	(LPCTSTR lpszBindAddress, USHORT usPort)							= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 获取监听 Socket 的地址信息 */
	virtual BOOL GetListenAddress(TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort)	= 0;

	/* 设置是否开启 IPv4/IPv6 双栈（默认：TRUE） */
	virtual void SetDualStack(BOOL bDualStack)												= 0;
	/* 检测是否开启 IPv4/IPv6 双栈 */
	virtual BOOL IsDualStack()																= 0;
};

/************************************************************************
名称：TCP 通信服务端组件接口
描述：定义 TCP 通信服务端组件的所有操作方法和属性访问方法
************************************************************************/
class ITcpServer : public IServer
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*
	* 名称：发送小文件
	* 描述：向指定连接发送 4096 KB 以下的小文件
	*		
	* 参数：		dwConnID		-- 连接 ID
	*			lpszFileName	-- 文件路径
	*			pHead			-- 头部附加数据
	*			pTail			-- 尾部附加数据
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL SendSmallFile(CONNID dwConnID, LPCTSTR lpszFileName, const LPWSABUF pHead = nullptr, const LPWSABUF pTail = nullptr)	= 0;

#ifdef _SSL_SUPPORT
	/*
	* 名称：初始化通信组件 SSL 环境参数
	* 描述：SSL 环境参数必须在 SSL 通信组件启动前完成初始化，否则启动失败
	*		
	* 参数：		iVerifyMode				-- SSL 验证模式（参考 EnSSLVerifyMode）
	*			lpszPemCertFile			-- 证书文件
	*			lpszPemKeyFile			-- 私钥文件
	*			lpszKeyPassword			-- 私钥密码（没有密码则为空）
	*			lpszCAPemCertFileOrPath	-- CA 证书文件或目录（单向验证或客户端可选）
	*			fnServerNameCallback	-- SNI 回调函数指针（可选，如果为 nullptr 则使用 SNI 默认回调函数）
	*
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL SetupSSLContext(int iVerifyMode = SSL_VM_NONE, LPCTSTR lpszPemCertFile = nullptr, LPCTSTR lpszPemKeyFile = nullptr, LPCTSTR lpszKeyPassword = nullptr, LPCTSTR lpszCAPemCertFileOrPath = nullptr, Fn_SNI_ServerNameCallback fnServerNameCallback = nullptr)	= 0;

	/*
	* 名称：初始化通信组件 SSL 环境参数（通过内存加载证书）
	* 描述：SSL 环境参数必须在 SSL 通信组件启动前完成初始化，否则启动失败
	*		
	* 参数：		iVerifyMode				-- SSL 验证模式（参考 EnSSLVerifyMode）
	*			lpszPemCert				-- 证书内容
	*			lpszPemKey				-- 私钥内容
	*			lpszKeyPassword			-- 私钥密码（没有密码则为空）
	*			lpszCAPemCert			-- CA 证书内容（单向验证或客户端可选）
	*			fnServerNameCallback	-- SNI 回调函数指针（可选，如果为 nullptr 则使用 SNI 默认回调函数）
	*
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL SetupSSLContextByMemory(int iVerifyMode = SSL_VM_NONE, LPCSTR lpszPemCert = nullptr, LPCSTR lpszPemKey = nullptr, LPCSTR lpszKeyPassword = nullptr, LPCSTR lpszCAPemCert = nullptr, Fn_SNI_ServerNameCallback fnServerNameCallback = nullptr)				= 0;

	/*
	* 名称：增加 SNI 主机证书
	* 描述：SSL 服务端在 SetupSSLContext() 成功后可以调用本方法增加多个 SNI 主机证书
	*		
	* 参数：		iVerifyMode				-- SSL 验证模式（参考 EnSSLVerifyMode）
	*			lpszPemCertFile			-- 证书文件
	*			lpszPemKeyFile			-- 私钥文件
	*			lpszKeyPassword			-- 私钥密码（没有密码则为空）
	*			lpszCAPemCertFileOrPath	-- CA 证书文件或目录（单向验证可选）
	*
	* 返回值：	正数		-- 成功，并返回 SNI 主机证书对应的索引，该索引用于在 SNI 回调函数中定位 SNI 主机
	*			负数		-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual int AddSSLContext(int iVerifyMode = SSL_VM_NONE, LPCTSTR lpszPemCertFile = nullptr, LPCTSTR lpszPemKeyFile = nullptr, LPCTSTR lpszKeyPassword = nullptr, LPCTSTR lpszCAPemCertFileOrPath = nullptr)																= 0;

	/*
	* 名称：增加 SNI 主机证书（通过内存加载证书）
	* 描述：SSL 服务端在 SetupSSLContext() 成功后可以调用本方法增加多个 SNI 主机证书
	*		
	* 参数：		iVerifyMode				-- SSL 验证模式（参考 EnSSLVerifyMode）
	*			lpszPemCert				-- 证书内容
	*			lpszPemKey				-- 私钥内容
	*			lpszKeyPassword			-- 私钥密码（没有密码则为空）
	*			lpszCAPemCert			-- CA 证书内容（单向验证可选）
	*
	* 返回值：	正数		-- 成功，并返回 SNI 主机证书对应的索引，该索引用于在 SNI 回调函数中定位 SNI 主机
	*			负数		-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual int AddSSLContextByMemory(int iVerifyMode = SSL_VM_NONE, LPCSTR lpszPemCert = nullptr, LPCSTR lpszPemKey = nullptr, LPCSTR lpszKeyPassword = nullptr, LPCSTR lpszCAPemCert = nullptr)																			= 0;

	/*
	* 名称：绑定 SNI 主机域名
	* 描述：SSL 服务端在 AddSSLContext() 成功后可以调用本方法绑定主机域名到 SNI 主机证书
	*		
	* 参数：		lpszServerName		-- 主机域名
	*			iContextIndex		-- SNI 主机证书对应的索引
	*
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL BindSSLServerName(LPCTSTR lpszServerName, int iContextIndex)	= 0;

	/*
	* 名称：清理通信组件 SSL 运行环境
	* 描述：清理通信组件 SSL 运行环境，回收 SSL 相关内存
	*		1、通信组件析构时会自动调用本方法
	*		2、当要重新设置通信组件 SSL 环境参数时，需要先调用本方法清理原先的环境参数
	*		
	* 参数：	无
	* 
	* 返回值：无
	*/
	virtual void CleanupSSLContext()											= 0;

	/*
	* 名称：启动 SSL 握手
	* 描述：当通信组件设置为非自动握手时，需要调用本方法启动 SSL 握手
	*		
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL StartSSLHandShake(CONNID dwConnID)						= 0;

#endif

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 设置 Accept 预投递数量（根据负载调整设置，Accept 预投递数量越大则支持的并发连接请求越多） */
	virtual void SetAcceptSocketCount	(DWORD dwAcceptSocketCount)		= 0;
	/* 设置通信数据缓冲区大小（根据平均通信数据包大小调整设置，通常设置为 1024 的倍数） */
	virtual void SetSocketBufferSize	(DWORD dwSocketBufferSize)		= 0;
	/* 设置监听 Socket 的等候队列大小（根据并发连接数量调整设置） */
	virtual void SetSocketListenQueue	(DWORD dwSocketListenQueue)		= 0;
	/* 设置正常心跳包间隔（毫秒，0 则不发送心跳包，默认：60 * 1000） */
	virtual void SetKeepAliveTime		(DWORD dwKeepAliveTime)			= 0;
	/* 设置异常心跳包间隔（毫秒，0 不发送心跳包，，默认：20 * 1000，如果超过若干次 [默认：WinXP 5 次, Win7 10 次] 检测不到心跳确认包则认为已断线） */
	virtual void SetKeepAliveInterval	(DWORD dwKeepAliveInterval)		= 0;
	/* 设置是否开启 nodelay 模式（默认：FALSE，不开启） */
	virtual void SetNoDelay				(BOOL bNoDelay)					= 0;

	/* 获取 Accept 预投递数量 */
	virtual DWORD GetAcceptSocketCount	()	= 0;
	/* 获取通信数据缓冲区大小 */
	virtual DWORD GetSocketBufferSize	()	= 0;
	/* 获取监听 Socket 的等候队列大小 */
	virtual DWORD GetSocketListenQueue	()	= 0;
	/* 获取正常心跳包间隔 */
	virtual DWORD GetKeepAliveTime		()	= 0;
	/* 获取异常心跳包间隔 */
	virtual DWORD GetKeepAliveInterval	()	= 0;
	/* 检查是否开启 nodelay 模式 */
	virtual BOOL IsNoDelay				()	= 0;
	
#ifdef _SSL_SUPPORT
	/* 设置通信组件握手方式（默认：TRUE，自动握手） */
	virtual void SetSSLAutoHandShake(BOOL bAutoHandShake)				= 0;
	/* 获取通信组件握手方式 */
	virtual BOOL IsSSLAutoHandShake()									= 0;

	/* 设置 SSL 加密算法列表 */
	virtual void SetSSLCipherList(LPCTSTR lpszCipherList)				= 0;
	/* 获取 SSL 加密算法列表 */
	virtual LPCTSTR GetSSLCipherList()									= 0;

	/*
	* 名称：获取 SSL Session 信息
	* 描述：获取指定类型的 SSL Session 信息（输出类型参考：EnSSLSessionInfo）
	*		
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL GetSSLSessionInfo(CONNID dwConnID, EnSSLSessionInfo enInfo, LPVOID* lppInfo)	= 0;
#endif

};

#ifdef _UDP_SUPPORT

/************************************************************************
名称：UDP 通信服务端组件接口
描述：定义 UDP 通信服务端组件的所有操作方法和属性访问方法
************************************************************************/
class IUdpServer : public IServer
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 设置数据报文最大长度（建议在局域网环境下不超过 1432 字节，在广域网环境下不超过 548 字节） */
	virtual void SetMaxDatagramSize		(DWORD dwMaxDatagramSize)	= 0;
	/* 获取数据报文最大长度 */
	virtual DWORD GetMaxDatagramSize	()							= 0;

	/* 设置 Receive 预投递数量（根据负载调整设置，Receive 预投递数量越大则丢包概率越小） */
	virtual void SetPostReceiveCount	(DWORD dwPostReceiveCount)	= 0;
	/* 获取 Receive 预投递数量 */
	virtual DWORD GetPostReceiveCount	()							= 0;

	/* 设置监测包尝试次数（0 则不发送监测跳包，如果超过最大尝试次数则认为已断线） */
	virtual void SetDetectAttempts		(DWORD dwDetectAttempts)	= 0;
	/* 设置监测包发送间隔（毫秒，0 不发送监测包） */
	virtual void SetDetectInterval		(DWORD dwDetectInterval)	= 0;
	/* 获取心跳检查次数 */
	virtual DWORD GetDetectAttempts		()							= 0;
	/* 获取心跳检查间隔 */
	virtual DWORD GetDetectInterval		()							= 0;
};

/************************************************************************
名称：Server/Agent ARQ 模型组件接口
描述：定义 Server/Agent 组件的 ARQ 模型组件的所有操作方法
************************************************************************/
class IArqSocket
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 设置是否开启 nodelay 模式（默认：FALSE，不开启） */
	virtual void SetNoDelay				(BOOL bNoDelay)				= 0;
	/* 设置是否关闭拥塞控制（默认：FALSE，不关闭） */
	virtual void SetTurnoffCongestCtrl	(BOOL bTurnOff)				= 0;
	/* 设置数据刷新间隔（毫秒，默认：60） */
	virtual void SetFlushInterval		(DWORD dwFlushInterval)		= 0;
	/* 设置快速重传 ACK 跨越次数（默认：0，关闭快速重传） */
	virtual void SetResendByAcks		(DWORD dwResendByAcks)		= 0;
	/* 设置发送窗口大小（数据包数量，默认：128） */
	virtual void SetSendWndSize			(DWORD dwSendWndSize)		= 0;
	/* 设置接收窗口大小（数据包数量，默认：512） */
	virtual void SetRecvWndSize			(DWORD dwRecvWndSize)		= 0;
	/* 设置最小重传超时时间（毫秒，默认：30） */
	virtual void SetMinRto				(DWORD dwMinRto)			= 0;
	/* 设置快速握手次数限制（默认：5，如果为 0 则不限制） */
	virtual void SetFastLimit			(DWORD dwFastLimit)			= 0;
	/* 设置最大传输单元（默认：0，与 SetMaxDatagramSize() 一致） */
	virtual void SetMaxTransUnit		(DWORD dwMaxTransUnit)		= 0;
	/* 设置最大数据包大小（默认：4096） */
	virtual void SetMaxMessageSize		(DWORD dwMaxMessageSize)	= 0;
	/* 设置握手超时时间（毫秒，默认：5000） */
	virtual void SetHandShakeTimeout	(DWORD dwHandShakeTimeout)	= 0;

	/* 检测是否开启 nodelay 模式 */
	virtual BOOL IsNoDelay				()							= 0;
	/* 检测是否关闭拥塞控制 */
	virtual BOOL IsTurnoffCongestCtrl	()							= 0;
	/* 获取数据刷新间隔 */
	virtual DWORD GetFlushInterval		()							= 0;
	/* 获取快速重传 ACK 跨越次数 */
	virtual DWORD GetResendByAcks		()							= 0;
	/* 获取发送窗口大小 */
	virtual DWORD GetSendWndSize		()							= 0;
	/* 获取接收窗口大小 */
	virtual DWORD GetRecvWndSize		()							= 0;
	/* 获取最小重传超时时间 */
	virtual DWORD GetMinRto				()							= 0;
	/* 获取快速握手次数限制 */
	virtual DWORD GetFastLimit			()							= 0;
	/* 获取最大传输单元 */
	virtual DWORD GetMaxTransUnit		()							= 0;
	/* 获取最大数据包大小 */
	virtual DWORD GetMaxMessageSize		()							= 0;
	/* 获取握手超时时间 */
	virtual DWORD GetHandShakeTimeout	()							= 0;

	/* 获取等待发送包数量 */
	virtual BOOL GetWaitingSendMessageCount	(CONNID dwConnID, int& iCount)	= 0;

public:
	virtual ~IArqSocket() {}
};

/************************************************************************
名称：UDP ARQ 通信服务端组件接口
描述：继承了 ARQ 和 Server 接口
************************************************************************/
typedef	DualInterface<IArqSocket, IUdpServer>	IUdpArqServer;

#endif

/************************************************************************
名称：通信代理组件接口
描述：定义通信代理组件的所有操作方法和属性访问方法，代理组件本质是一个同时连接多个服务器的客户端组件
************************************************************************/
class IAgent : public IComplexSocket
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*
	* 名称：启动通信组件
	* 描述：启动通信代理组件，启动完成后可开始连接远程服务器
	*		
	* 参数：		lpszBindAddress	-- 绑定地址（默认：nullptr，绑定任意地址）
	*			bAsyncConnect	-- 是否采用异步 Connect
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 GetLastError() 获取错误代码
	*/
	virtual BOOL Start	(LPCTSTR lpszBindAddress = nullptr, BOOL bAsyncConnect = TRUE)				= 0;

	/*
	* 名称：连接服务器
	* 描述：连接服务器，连接成功后 IAgentListener 会接收到 OnConnect() / OnHandShake() 事件
	*		
	* 参数：		lpszRemoteAddress	-- 服务端地址
	*			usPort				-- 服务端端口
	*			pdwConnID			-- 连接 ID（默认：nullptr，不获取连接 ID）
	*			pExtra				-- 连接附加数据（默认：nullptr）
	*			usLocalPort			-- 本地端口（默认：0）
	*			lpszLocalAddress	-- 本地地址（默认：nullptr，使用 Start() 方法中绑定的地址）
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL Connect(LPCTSTR lpszRemoteAddress, USHORT usPort, CONNID* pdwConnID = nullptr, PVOID pExtra = nullptr, USHORT usLocalPort = 0, LPCTSTR lpszLocalAddress = nullptr)	= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 获取某个连接的远程主机信息 */
	virtual BOOL GetRemoteHost		(CONNID dwConnID, TCHAR lpszHost[], int& iHostLen, USHORT& usPort)	= 0;
};

/************************************************************************
名称：TCP 通信代理组件接口
描述：定义 TCP 通信代理组件的所有操作方法和属性访问方法
************************************************************************/
class ITcpAgent : public IAgent
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*
	* 名称：发送小文件
	* 描述：向指定连接发送 4096 KB 以下的小文件
	*		
	* 参数：		dwConnID		-- 连接 ID
	*			lpszFileName	-- 文件路径
	*			pHead			-- 头部附加数据
	*			pTail			-- 尾部附加数据
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL SendSmallFile(CONNID dwConnID, LPCTSTR lpszFileName, const LPWSABUF pHead = nullptr, const LPWSABUF pTail = nullptr)	= 0;

#ifdef _SSL_SUPPORT
	/*
	* 名称：初始化通信组件 SSL 环境参数
	* 描述：SSL 环境参数必须在 SSL 通信组件启动前完成初始化，否则启动失败
	*		
	* 参数：		iVerifyMode				-- SSL 验证模式（参考 EnSSLVerifyMode）
	*			lpszPemCertFile			-- 证书文件（客户端可选）
	*			lpszPemKeyFile			-- 私钥文件（客户端可选）
	*			lpszKeyPassword			-- 私钥密码（没有密码则为空）
	*			lpszCAPemCertFileOrPath	-- CA 证书文件或目录（单向验证或客户端可选）
	*
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL SetupSSLContext(int iVerifyMode = SSL_VM_NONE, LPCTSTR lpszPemCertFile = nullptr, LPCTSTR lpszPemKeyFile = nullptr, LPCTSTR lpszKeyPassword = nullptr, LPCTSTR lpszCAPemCertFileOrPath = nullptr)	= 0;

	/*
	* 名称：初始化通信组件 SSL 环境参数（通过内存加载证书）
	* 描述：SSL 环境参数必须在 SSL 通信组件启动前完成初始化，否则启动失败
	*		
	* 参数：		iVerifyMode				-- SSL 验证模式（参考 EnSSLVerifyMode）
	*			lpszPemCert				-- 证书内容
	*			lpszPemKey				-- 私钥内容
	*			lpszKeyPassword			-- 私钥密码（没有密码则为空）
	*			lpszCAPemCert			-- CA 证书内容（单向验证或客户端可选）
	*
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL SetupSSLContextByMemory(int iVerifyMode = SSL_VM_NONE, LPCSTR lpszPemCert = nullptr, LPCSTR lpszPemKey = nullptr, LPCSTR lpszKeyPassword = nullptr, LPCSTR lpszCAPemCert = nullptr)					= 0;

	/*
	* 名称：清理通信组件 SSL 运行环境
	* 描述：清理通信组件 SSL 运行环境，回收 SSL 相关内存
	*		1、通信组件析构时会自动调用本方法
	*		2、当要重新设置通信组件 SSL 环境参数时，需要先调用本方法清理原先的环境参数
	*		
	* 参数：	无
	* 
	* 返回值：无
	*/
	virtual void CleanupSSLContext()									= 0;

	/*
	* 名称：启动 SSL 握手
	* 描述：当通信组件设置为非自动握手时，需要调用本方法启动 SSL 握手
	*		
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL StartSSLHandShake(CONNID dwConnID)						= 0;

#endif

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 设置同步连接超时时间（毫秒） */
	virtual void SetSyncConnectTimeout	(DWORD dwSyncConnectTimeout)	= 0;
	/* 设置通信数据缓冲区大小（根据平均通信数据包大小调整设置，通常设置为 1024 的倍数） */
	virtual void SetSocketBufferSize	(DWORD dwSocketBufferSize)		= 0;
	/* 设置正常心跳包间隔（毫秒，0 则不发送心跳包，默认：60 * 1000） */
	virtual void SetKeepAliveTime		(DWORD dwKeepAliveTime)			= 0;
	/* 设置异常心跳包间隔（毫秒，0 不发送心跳包，，默认：20 * 1000，如果超过若干次 [默认：WinXP 5 次, Win7 10 次] 检测不到心跳确认包则认为已断线） */
	virtual void SetKeepAliveInterval	(DWORD dwKeepAliveInterval)		= 0;
	/* 设置是否开启 nodelay 模式（默认：FALSE，不开启） */
	virtual void SetNoDelay				(BOOL bNoDelay)					= 0;

	/* 获取同步连接超时时间 */
	virtual DWORD GetSyncConnectTimeout	()	= 0;
	/* 获取通信数据缓冲区大小 */
	virtual DWORD GetSocketBufferSize	()	= 0;
	/* 获取正常心跳包间隔 */
	virtual DWORD GetKeepAliveTime		()	= 0;
	/* 获取异常心跳包间隔 */
	virtual DWORD GetKeepAliveInterval	()	= 0;
	/* 检查是否开启 nodelay 模式 */
	virtual BOOL IsNoDelay				()	= 0;

#ifdef _SSL_SUPPORT
	/* 设置通信组件握手方式（默认：TRUE，自动握手） */
	virtual void SetSSLAutoHandShake(BOOL bAutoHandShake)				= 0;
	/* 获取通信组件握手方式 */
	virtual BOOL IsSSLAutoHandShake()									= 0;

	/* 设置 SSL 加密算法列表 */
	virtual void SetSSLCipherList(LPCTSTR lpszCipherList)				= 0;
	/* 获取 SSL 加密算法列表 */
	virtual LPCTSTR GetSSLCipherList()									= 0;

	/*
	* 名称：获取 SSL Session 信息
	* 描述：获取指定类型的 SSL Session 信息（输出类型参考：EnSSLSessionInfo）
	*		
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL GetSSLSessionInfo(CONNID dwConnID, EnSSLSessionInfo enInfo, LPVOID* lppInfo)	= 0;
#endif

};

/************************************************************************
名称：通信客户端组件接口
描述：定义通信客户端组件的所有操作方法和属性访问方法
************************************************************************/
class IClient
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*
	* 名称：启动通信组件
	* 描述：启动客户端通信组件并连接服务端，启动完成后可开始收发数据
	*		
	* 参数：		lpszRemoteAddress	-- 服务端地址
	*			usPort				-- 服务端端口
	*			bAsyncConnect		-- 是否采用异步 Connect
	*			lpszBindAddress		-- 绑定地址（默认：nullptr，TcpClient/UdpClient -> 不执行绑定操作，UdpCast 绑定 -> 任意地址）
	*			usLocalPort			-- 本地端口（默认：0）
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 GetLastError() 获取错误代码
	*/
	virtual BOOL Start	(LPCTSTR lpszRemoteAddress, USHORT usPort, BOOL bAsyncConnect = TRUE, LPCTSTR lpszBindAddress = nullptr, USHORT usLocalPort = 0)	= 0;

	/*
	* 名称：关闭通信组件
	* 描述：关闭客户端通信组件，关闭完成后断开与服务端的连接并释放所有资源
	*		
	* 参数：	
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 GetLastError() 获取错误代码
	*/
	virtual BOOL Stop	()																		= 0;

	/*
	* 名称：发送数据
	* 描述：向服务端发送数据
	*		
	* 参数：		pBuffer		-- 发送缓冲区
	*			iLength		-- 发送缓冲区长度
	*			iOffset		-- 发送缓冲区指针偏移量
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL Send	(const BYTE* pBuffer, int iLength, int iOffset = 0)						= 0;

	/*
	* 名称：发送多组数据
	* 描述：向服务端发送多组数据
	*		TCP - 顺序发送所有数据包 
	*		UDP - 把所有数据包组合成一个数据包发送（数据包的总长度不能大于设置的 UDP 包最大长度） 
	*		
	* 参数：		pBuffers	-- 发送缓冲区数组
	*			iCount		-- 发送缓冲区数目
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL SendPackets(const WSABUF pBuffers[], int iCount)								= 0;

	/*
	* 名称：暂停/恢复接收
	* 描述：暂停/恢复某个连接的数据接收工作
	*		
	*			bPause	-- TRUE - 暂停, FALSE - 恢复
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败
	*/
	virtual BOOL PauseReceive(BOOL bPause = TRUE)												= 0;

	/*
	* 名称：等待
	* 描述：等待通信组件停止运行
	*		
	* 参数：		dwMilliseconds	-- 超时时间（毫秒，默认：-1，永不超时）
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL Wait(DWORD dwMilliseconds = INFINITE)											= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 设置连接的附加数据 */
	virtual void SetExtra					(PVOID pExtra)										= 0;
	/* 获取连接的附加数据 */
	virtual PVOID GetExtra					()													= 0;

	/* 检测是否为安全连接（SSL/HTTPS） */
	virtual BOOL IsSecure					()													= 0;
	/* 检查通信组件是否已启动 */
	virtual BOOL HasStarted					()													= 0;
	/* 查看通信组件当前状态 */
	virtual EnServiceState	GetState		()													= 0;
	/* 获取最近一次失败操作的错误代码 */
	virtual EnSocketError	GetLastError	()													= 0;
	/* 获取最近一次失败操作的错误描述 */
	virtual LPCTSTR			GetLastErrorDesc()													= 0;
	/* 获取该组件对象的连接 ID */
	virtual CONNID			GetConnectionID	()													= 0;
	/* 获取 Client Socket 的地址信息 */
	virtual BOOL GetLocalAddress		(TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort)	= 0;
	/* 获取连接的远程主机信息 */
	virtual BOOL GetRemoteHost			(TCHAR lpszHost[], int& iHostLen, USHORT& usPort)		= 0;
	/* 获取连接中未发出数据的长度 */
	virtual BOOL GetPendingDataLength	(int& iPending)											= 0;
	/* 获取连接的数据接收状态 */
	virtual BOOL IsPauseReceive			(BOOL& bPaused)											= 0;
	/* 检测是否有效连接 */
	virtual BOOL IsConnected			()														= 0;

	/* 设置地址重用选项 */
	virtual void SetReuseAddressPolicy(EnReuseAddressPolicy enReusePolicy)						= 0;
	/* 设置内存块缓存池大小 */
	virtual void SetFreeBufferPoolSize		(DWORD dwFreeBufferPoolSize)						= 0;
	/* 设置内存块缓存池回收阀值 */
	virtual void SetFreeBufferPoolHold		(DWORD dwFreeBufferPoolHold)						= 0;

	/* 获取地址重用选项 */
	virtual EnReuseAddressPolicy GetReuseAddressPolicy	()										= 0;
	/* 获取内存块缓存池大小 */
	virtual DWORD GetFreeBufferPoolSize					()										= 0;
	/* 获取内存块缓存池回收阀值 */
	virtual DWORD GetFreeBufferPoolHold					()										= 0;

public:
	virtual ~IClient() {}
};

/************************************************************************
名称：TCP 通信客户端组件接口
描述：定义 TCP 通信客户端组件的所有操作方法和属性访问方法
************************************************************************/
class ITcpClient : public IClient
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*
	* 名称：发送小文件
	* 描述：向服务端发送 4096 KB 以下的小文件
	*		
	* 参数：		lpszFileName	-- 文件路径
	*			pHead			-- 头部附加数据
	*			pTail			-- 尾部附加数据
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL SendSmallFile(LPCTSTR lpszFileName, const LPWSABUF pHead = nullptr, const LPWSABUF pTail = nullptr)	= 0;

#ifdef _SSL_SUPPORT
	/*
	* 名称：初始化通信组件 SSL 环境参数
	* 描述：SSL 环境参数必须在 SSL 通信组件启动前完成初始化，否则启动失败
	*		
	* 参数：		iVerifyMode				-- SSL 验证模式（参考 EnSSLVerifyMode）
	*			lpszPemCertFile			-- 证书文件（客户端可选）
	*			lpszPemKeyFile			-- 私钥文件（客户端可选）
	*			lpszKeyPassword			-- 私钥密码（没有密码则为空）
	*			lpszCAPemCertFileOrPath	-- CA 证书文件或目录（单向验证或客户端可选）
	*
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL SetupSSLContext(int iVerifyMode = SSL_VM_NONE, LPCTSTR lpszPemCertFile = nullptr, LPCTSTR lpszPemKeyFile = nullptr, LPCTSTR lpszKeyPassword = nullptr, LPCTSTR lpszCAPemCertFileOrPath = nullptr)	= 0;

	/*
	* 名称：初始化通信组件 SSL 环境参数（通过内存加载证书）
	* 描述：SSL 环境参数必须在 SSL 通信组件启动前完成初始化，否则启动失败
	*		
	* 参数：		iVerifyMode				-- SSL 验证模式（参考 EnSSLVerifyMode）
	*			lpszPemCert				-- 证书内容
	*			lpszPemKey				-- 私钥内容
	*			lpszKeyPassword			-- 私钥密码（没有密码则为空）
	*			lpszCAPemCert			-- CA 证书内容（单向验证或客户端可选）
	*
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL SetupSSLContextByMemory(int iVerifyMode = SSL_VM_NONE, LPCSTR lpszPemCert = nullptr, LPCSTR lpszPemKey = nullptr, LPCSTR lpszKeyPassword = nullptr, LPCSTR lpszCAPemCert = nullptr)					= 0;

	/*
	* 名称：清理通信组件 SSL 运行环境
	* 描述：清理通信组件 SSL 运行环境，回收 SSL 相关内存
	*		1、通信组件析构时会自动调用本方法
	*		2、当要重新设置通信组件 SSL 环境参数时，需要先调用本方法清理原先的环境参数
	*		
	* 参数：	无
	* 
	* 返回值：无
	*/
	virtual void CleanupSSLContext()		= 0;

	/*
	* 名称：启动 SSL 握手
	* 描述：当通信组件设置为非自动握手时，需要调用本方法启动 SSL 握手
	*		
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL StartSSLHandShake()		= 0;

#endif

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 设置同步连接超时时间（毫秒） */
	virtual void SetSyncConnectTimeout	(DWORD dwSyncConnectTimeout)	= 0;
	/* 设置通信数据缓冲区大小（根据平均通信数据包大小调整设置，通常设置为：(N * 1024) - sizeof(TBufferObj)） */
	virtual void SetSocketBufferSize	(DWORD dwSocketBufferSize)		= 0;
	/* 设置正常心跳包间隔（毫秒，0 则不发送心跳包，默认：60 * 1000） */
	virtual void SetKeepAliveTime		(DWORD dwKeepAliveTime)			= 0;
	/* 设置异常心跳包间隔（毫秒，0 不发送心跳包，，默认：20 * 1000，如果超过若干次 [默认：WinXP 5 次, Win7 10 次] 检测不到心跳确认包则认为已断线） */
	virtual void SetKeepAliveInterval	(DWORD dwKeepAliveInterval)		= 0;
	/* 设置是否开启 nodelay 模式（默认：FALSE，不开启） */
	virtual void SetNoDelay				(BOOL bNoDelay)					= 0;

	/* 获取同步连接超时时间 */
	virtual DWORD GetSyncConnectTimeout	()	= 0;
	/* 获取通信数据缓冲区大小 */
	virtual DWORD GetSocketBufferSize	()	= 0;
	/* 获取正常心跳包间隔 */
	virtual DWORD GetKeepAliveTime		()	= 0;
	/* 获取异常心跳包间隔 */
	virtual DWORD GetKeepAliveInterval	()	= 0;
	/* 检查是否开启 nodelay 模式 */
	virtual BOOL IsNoDelay				()	= 0;

#ifdef _SSL_SUPPORT
	/* 设置通信组件握手方式（默认：TRUE，自动握手） */
	virtual void SetSSLAutoHandShake(BOOL bAutoHandShake)	= 0;
	/* 获取通信组件握手方式 */
	virtual BOOL IsSSLAutoHandShake()						= 0;

	/* 设置 SSL 加密算法列表 */
	virtual void SetSSLCipherList(LPCTSTR lpszCipherList)	= 0;
	/* 获取 SSL 加密算法列表 */
	virtual LPCTSTR GetSSLCipherList()						= 0;

	/*
	* 名称：获取 SSL Session 信息
	* 描述：获取指定类型的 SSL Session 信息（输出类型参考：EnSSLSessionInfo）
	*		
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL GetSSLSessionInfo(EnSSLSessionInfo enInfo, LPVOID* lppInfo)	= 0;
#endif

};

#ifdef _UDP_SUPPORT

/************************************************************************
名称：UDP 通信客户端组件接口
描述：定义 UDP 通信客户端组件的所有操作方法和属性访问方法
************************************************************************/
class IUdpClient : public IClient
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 设置数据报文最大长度（建议在局域网环境下不超过 1432 字节，在广域网环境下不超过 548 字节） */
	virtual void SetMaxDatagramSize	(DWORD dwMaxDatagramSize)	= 0;
	/* 获取数据报文最大长度 */
	virtual DWORD GetMaxDatagramSize()							= 0;

	/* 设置监测包尝试次数（0 则不发送监测跳包，如果超过最大尝试次数则认为已断线） */
	virtual void SetDetectAttempts	(DWORD dwDetectAttempts)	= 0;
	/* 设置监测包发送间隔（毫秒，0 不发送监测包） */
	virtual void SetDetectInterval	(DWORD dwDetectInterval)	= 0;
	/* 获取心跳检查次数 */
	virtual DWORD GetDetectAttempts	()							= 0;
	/* 获取心跳检查间隔 */
	virtual DWORD GetDetectInterval	()							= 0;
};

/************************************************************************
名称：UDP 传播组件接口
描述：定义 UDP 传播（组播或广播）组件的所有操作方法和属性访问方法
************************************************************************/
class IUdpCast : public IClient
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 设置数据报文最大长度（建议在局域网环境下不超过 1432 字节，在广域网环境下不超过 548 字节） */
	virtual void SetMaxDatagramSize	(DWORD dwMaxDatagramSize)		= 0;
	/* 获取数据报文最大长度 */
	virtual DWORD GetMaxDatagramSize()								= 0;

	/* 设置传播模式（组播或广播） */
	virtual void SetCastMode		(EnCastMode enCastMode)			= 0;
	/* 获取传播模式 */
	virtual EnCastMode GetCastMode	()								= 0;

	/* 设置组播报文的 TTL（0 - 255） */
	virtual void SetMultiCastTtl	(int iMCTtl)					= 0;
	/* 获取组播报文的 TTL */
	virtual int GetMultiCastTtl		()								= 0;

	/* 设置是否启用组播环路（TRUE or FALSE） */
	virtual void SetMultiCastLoop	(BOOL bMCLoop)					= 0;
	/* 检测是否启用组播环路 */
	virtual BOOL IsMultiCastLoop	()								= 0;

	/* 获取当前数据报的远程地址信息（通常在 OnReceive 事件中调用） */
	virtual BOOL GetRemoteAddress	(TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort)	= 0;
};

/************************************************************************
名称：UDP 节点组件接口
描述：定义 UDP 节点组件的所有操作方法和属性访问方法
************************************************************************/
class IUdpNode
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*
	* 名称：启动通信组件
	* 描述：启动 UDP 节点通信组件，启动完成后可开始收发数据
	*		
	* 参数：		lpszBindAddress		-- 绑定地址（默认：nullptr，绑定任意地址）
	*			usPort				-- 本地端口（默认：0）
	*			enCastMode			-- 传播模式（默认：CM_UNICAST）
	*			lpszCastAddress		-- 传播地址（默认：nullptr，当 enCaseMode 为 CM_MULTICAST 或 CM_BROADCAST 时有效）
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 GetLastError() 获取错误代码
	*/
	virtual BOOL Start(LPCTSTR lpszBindAddress = nullptr, USHORT usPort = 0, EnCastMode enCastMode = CM_UNICAST, LPCTSTR lpszCastAddress = nullptr)	= 0;

	/*
	* 名称：关闭通信组件
	* 描述：关闭 UDP 节点通信组件，关闭完成后释放所有资源
	*		
	* 参数：	
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 GetLastError() 获取错误代码
	*/
	virtual BOOL Stop()																										= 0;

	/*
	* 名称：发送数据
	* 描述：向指定地址发送数据
	*		
	* 参数：		lpszRemoteAddress	-- 远程地址
	*			usRemotePort		-- 远程端口
	*			pBuffer				-- 发送缓冲区
	*			iLength				-- 发送缓冲区长度
	*			iOffset				-- 发送缓冲区指针偏移量
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL Send(LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pBuffer, int iLength, int iOffset = 0)	= 0;

	/*
	* 名称：发送多组数据
	* 描述：向指定地址发送多组数据，把所有数据包组合成一个数据包发送（数据包的总长度不能大于设置的 UDP 包最大长度） 
	*		
	* 参数：		lpszRemoteAddress	-- 远程地址
	*			usRemotePort		-- 远程端口
	*			pBuffers			-- 发送缓冲区数组
	*			iCount				-- 发送缓冲区数目
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL SendPackets(LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const WSABUF pBuffers[], int iCount)			= 0;

	/*
	* 名称：发送数据
	* 描述：向传播地址发送数据
	*		
	* 参数：		pBuffer		-- 发送缓冲区
	*			iLength		-- 发送缓冲区长度
	*			iOffset		-- 发送缓冲区指针偏移量
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL SendCast(const BYTE* pBuffer, int iLength, int iOffset = 0)												= 0;

	/*
	* 名称：发送多组数据
	* 描述：向传播地址发送多组数据，把所有数据包组合成一个数据包发送（数据包的总长度不能大于设置的 UDP 包最大长度） 
	*		
	* 参数：		pBuffers	-- 发送缓冲区数组
	*			iCount		-- 发送缓冲区数目
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL SendCastPackets(const WSABUF pBuffers[], int iCount)														= 0;

	/*
	* 名称：等待
	* 描述：等待通信组件停止运行
	*		
	* 参数：		dwMilliseconds	-- 超时时间（毫秒，默认：-1，永不超时）
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL Wait(DWORD dwMilliseconds = INFINITE)																		= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 设置附加数据 */
	virtual void SetExtra					(PVOID pExtra)										= 0;

	/* 获取附加数据 */
	virtual PVOID GetExtra					()													= 0;

	/* 检查通信组件是否已启动 */
	virtual BOOL HasStarted					()													= 0;
	/* 查看通信组件当前状态 */
	virtual EnServiceState GetState			()													= 0;
	/* 获取最近一次失败操作的错误代码 */
	virtual EnSocketError GetLastError		()													= 0;
	/* 获取最近一次失败操作的错误描述 */
	virtual LPCTSTR GetLastErrorDesc		()													= 0;
	/* 获取本节点地址 */
	virtual BOOL GetLocalAddress		(TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort)	= 0;
	/* 获取本节点传播地址 */
	virtual BOOL GetCastAddress			(TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort)	= 0;
	/* 获取传播模式 */
	virtual EnCastMode GetCastMode		()														= 0;
	/* 获取未发出数据的长度 */
	virtual BOOL GetPendingDataLength	(int& iPending)											= 0;

	/* 设置数据报文最大长度（建议在局域网环境下不超过 1432 字节，在广域网环境下不超过 548 字节） */
	virtual void SetMaxDatagramSize	(DWORD dwMaxDatagramSize)	= 0;
	/* 获取数据报文最大长度 */
	virtual DWORD GetMaxDatagramSize()							= 0;

	/* 设置组播报文的 TTL（0 - 255） */
	virtual void SetMultiCastTtl	(int iMCTtl)				= 0;
	/* 获取组播报文的 TTL */
	virtual int GetMultiCastTtl		()							= 0;

	/* 设置是否启用组播环路（TRUE or FALSE） */
	virtual void SetMultiCastLoop	(BOOL bMCLoop)				= 0;
	/* 检测是否启用组播环路 */
	virtual BOOL IsMultiCastLoop	()							= 0;

	/* 设置地址重用选项 */
	virtual void SetReuseAddressPolicy(EnReuseAddressPolicy enReusePolicy)	= 0;
	/* 设置是否开启 IPv4/IPv6 双栈（默认：TRUE） */
	virtual void SetDualStack(BOOL bDualStack)								= 0;
	/* 设置工作线程数量（通常设置为 2 * CPU + 2） */
	virtual void SetWorkerThreadCount	(DWORD dwWorkerThreadCount)			= 0;
	/* 设置 Receive 预投递数量（根据负载调整设置，Receive 预投递数量越大则丢包概率越小） */
	virtual void SetPostReceiveCount	(DWORD dwPostReceiveCount)			= 0;
	/* 设置内存块缓存池大小 */
	virtual void SetFreeBufferPoolSize	(DWORD dwFreeBufferPoolSize)		= 0;
	/* 设置内存块缓存池回收阀值 */
	virtual void SetFreeBufferPoolHold	(DWORD dwFreeBufferPoolHold)		= 0;

	/* 获取地址重用选项 */
	virtual EnReuseAddressPolicy GetReuseAddressPolicy()					= 0;
	/* 检测是否开启 IPv4/IPv6 双栈 */
	virtual BOOL IsDualStack() = 0;
	/* 获取工作线程数量 */
	virtual DWORD GetWorkerThreadCount	()									= 0;
	/* 获取 Receive 预投递数量 */
	virtual DWORD GetPostReceiveCount	()									= 0;
	/* 获取内存块缓存池大小 */
	virtual DWORD GetFreeBufferPoolSize	()									= 0;
	/* 获取内存块缓存池回收阀值 */
	virtual DWORD GetFreeBufferPoolHold	()									= 0;

public:
	virtual ~IUdpNode() {}
};

/************************************************************************
名称：Client ARQ 模型组件接口
描述：定义 Client 组件的 ARQ 模型组件的所有操作方法
************************************************************************/
class IArqClient
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 设置是否开启 nodelay 模式（默认：FALSE，不开启） */
	virtual void SetNoDelay				(BOOL bNoDelay)				= 0;
	/* 设置是否关闭拥塞控制（默认：FALSE，不关闭） */
	virtual void SetTurnoffCongestCtrl	(BOOL bTurnOff)				= 0;
	/* 设置数据刷新间隔（毫秒，默认：60） */
	virtual void SetFlushInterval		(DWORD dwFlushInterval)		= 0;
	/* 设置快速重传 ACK 跨越次数（默认：0，关闭快速重传） */
	virtual void SetResendByAcks		(DWORD dwResendByAcks)		= 0;
	/* 设置发送窗口大小（数据包数量，默认：128） */
	virtual void SetSendWndSize			(DWORD dwSendWndSize)		= 0;
	/* 设置接收窗口大小（数据包数量，默认：512） */
	virtual void SetRecvWndSize			(DWORD dwRecvWndSize)		= 0;
	/* 设置最小重传超时时间（毫秒，默认：30） */
	virtual void SetMinRto				(DWORD dwMinRto)			= 0;
	/* 设置快速握手次数限制（默认：5，如果为 0 则不限制） */
	virtual void SetFastLimit			(DWORD dwFastLimit)			= 0;
	/* 设置最大传输单元（默认：0，与 SetMaxDatagramSize() 一致） */
	virtual void SetMaxTransUnit		(DWORD dwMaxTransUnit)		= 0;
	/* 设置最大数据包大小（默认：4096） */
	virtual void SetMaxMessageSize		(DWORD dwMaxMessageSize)	= 0;
	/* 设置握手超时时间（毫秒，默认：5000） */
	virtual void SetHandShakeTimeout	(DWORD dwHandShakeTimeout)	= 0;

	/* 检测是否开启 nodelay 模式 */
	virtual BOOL IsNoDelay				()							= 0;
	/* 检测是否关闭拥塞控制 */
	virtual BOOL IsTurnoffCongestCtrl	()							= 0;
	/* 获取数据刷新间隔 */
	virtual DWORD GetFlushInterval		()							= 0;
	/* 获取快速重传 ACK 跨越次数 */
	virtual DWORD GetResendByAcks		()							= 0;
	/* 获取发送窗口大小 */
	virtual DWORD GetSendWndSize		()							= 0;
	/* 获取接收窗口大小 */
	virtual DWORD GetRecvWndSize		()							= 0;
	/* 获取最小重传超时时间 */
	virtual DWORD GetMinRto				()							= 0;
	/* 获取快速握手次数限制 */
	virtual DWORD GetFastLimit			()							= 0;
	/* 获取最大传输单元 */
	virtual DWORD GetMaxTransUnit		()							= 0;
	/* 获取最大数据包大小 */
	virtual DWORD GetMaxMessageSize		()							= 0;
	/* 获取握手超时时间 */
	virtual DWORD GetHandShakeTimeout	()							= 0;

	/* 获取等待发送包数量 */
	virtual BOOL GetWaitingSendMessageCount	(int& iCount)			= 0;

public:
	virtual ~IArqClient() {}
};

/************************************************************************
名称：UDP ARQ 通信客户端组件接口
描述：继承了 ARQ 和 Client 接口
************************************************************************/
typedef	DualInterface<IArqClient, IUdpClient>	IUdpArqClient;

#endif

/************************************************************************
名称：Server/Agent PULL 模型组件接口
描述：定义 Server/Agent 组件的 PULL 模型组件的所有操作方法
************************************************************************/
class IPullSocket
{
public:

	/*
	* 名称：抓取数据
	* 描述：用户通过该方法从 Socket 组件中抓取数据
	*		
	* 参数：		dwConnID	-- 连接 ID
	*			pData		-- 抓取缓冲区
	*			iLength		-- 抓取数据长度
	* 返回值：	EnFetchResult
	*/
	virtual EnFetchResult Fetch	(CONNID dwConnID, BYTE* pData, int iLength)	= 0;

	/*
	* 名称：窥探数据（不会移除缓冲区数据）
	* 描述：用户通过该方法从 Socket 组件中窥探数据
	*		
	* 参数：		dwConnID	-- 连接 ID
	*			pData		-- 窥探缓冲区
	*			iLength		-- 窥探数据长度
	* 返回值：	EnFetchResult
	*/
	virtual EnFetchResult Peek	(CONNID dwConnID, BYTE* pData, int iLength)	= 0;

public:
	virtual ~IPullSocket() {}
};

/************************************************************************
名称：Client PULL 模型组件接口
描述：定义 Client 组件的 PULL 模型组件的所有操作方法
************************************************************************/
class IPullClient
{
public:

	/*
	* 名称：抓取数据
	* 描述：用户通过该方法从 Socket 组件中抓取数据
	*		
	* 参数：		pData		-- 抓取缓冲区
	*			iLength		-- 抓取数据长度
	* 返回值：	EnFetchResult
	*/
	virtual EnFetchResult Fetch	(BYTE* pData, int iLength)	= 0;

	/*
	* 名称：窥探数据（不会移除缓冲区数据）
	* 描述：用户通过该方法从 Socket 组件中窥探数据
	*		
	* 参数：		pData		-- 窥探缓冲区
	*			iLength		-- 窥探数据长度
	* 返回值：	EnFetchResult
	*/
	virtual EnFetchResult Peek	(BYTE* pData, int iLength)	= 0;

public:
	virtual ~IPullClient() {}
};

/************************************************************************
名称：TCP PULL 模型组件接口
描述：继承了 PULL 和 Socket 接口
************************************************************************/
typedef	DualInterface<IPullSocket, ITcpServer>	ITcpPullServer;
typedef	DualInterface<IPullSocket, ITcpAgent>	ITcpPullAgent;
typedef	DualInterface<IPullClient, ITcpClient>	ITcpPullClient;

/************************************************************************
名称：Server/Agent PACK 模型组件接口
描述：定义 Server/Agent 组件的 PACK 模型组件的所有操作方法
************************************************************************/
class IPackSocket
{
public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 设置数据包最大长度（有效数据包最大长度不能超过 4194303/0x3FFFFF 字节，默认：262144/0x40000） */
	virtual void SetMaxPackSize		(DWORD dwMaxPackSize)			= 0;
	/* 设置包头标识（有效包头标识取值范围 0 ~ 1023/0x3FF，当包头标识为 0 时不校验包头，默认：0） */
	virtual void SetPackHeaderFlag	(USHORT usPackHeaderFlag)		= 0;

	/* 获取数据包最大长度 */
	virtual DWORD GetMaxPackSize	()								= 0;
	/* 获取包头标识 */
	virtual USHORT GetPackHeaderFlag()								= 0;

public:
	virtual ~IPackSocket() {}
};

/************************************************************************
名称：Client PACK 模型组件接口
描述：定义 Client 组件的 PACK 模型组件的所有操作方法
************************************************************************/
class IPackClient
{
public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 设置数据包最大长度（有效数据包最大长度不能超过 4194303/0x3FFFFF 字节，默认：262144/0x40000） */
	virtual void SetMaxPackSize		(DWORD dwMaxPackSize)			= 0;
	/* 设置包头标识（有效包头标识取值范围 0 ~ 1023/0x3FF，当包头标识为 0 时不校验包头，默认：0） */
	virtual void SetPackHeaderFlag	(USHORT usPackHeaderFlag)		= 0;

	/* 获取数据包最大长度 */
	virtual DWORD GetMaxPackSize	()								= 0;
	/* 获取包头标识 */
	virtual USHORT GetPackHeaderFlag()								= 0;

public:
	virtual ~IPackClient() {}
};

/************************************************************************
名称：TCP PACK 模型组件接口
描述：继承了 PACK 和 Socket 接口
************************************************************************/
typedef	DualInterface<IPackSocket, ITcpServer>	ITcpPackServer;
typedef	DualInterface<IPackSocket, ITcpAgent>	ITcpPackAgent;
typedef	DualInterface<IPackClient, ITcpClient>	ITcpPackClient;

/************************************************************************
名称：Socket 监听器基接口
描述：定义组件监听器的公共方法
************************************************************************/
template<class T> class ISocketListenerT
{
public:

	/*
	* 名称：握手完成通知
	* 描述：连接完成握手时，Socket 监听器将收到该通知，监听器接收到该通知后才能开始
	*		数据收发操作
	*		
	* 参数：		pSender		-- 事件源对象
	*			dwConnID	-- 连接 ID
	* 返回值：	HR_OK / HR_IGNORE	-- 继续执行
	*			HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	virtual EnHandleResult OnHandShake(T* pSender, CONNID dwConnID)												= 0;

	/*
	* 名称：已发送数据通知
	* 描述：成功发送数据后，Socket 监听器将收到该通知
	*		
	* 参数：		pSender		-- 事件源对象
	*			dwConnID	-- 连接 ID
	*			pData		-- 已发送数据缓冲区
	*			iLength		-- 已发送数据长度
	* 返回值：	HR_OK / HR_IGNORE	-- 继续执行
	*			HR_ERROR			-- 该通知不允许返回 HR_ERROR（调试模式下引发断言错误）
	*/
	virtual EnHandleResult OnSend(T* pSender, CONNID dwConnID, const BYTE* pData, int iLength)					= 0;

	/*
	* 名称：数据到达通知（PUSH 模型）
	* 描述：对于 PUSH 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知
	*		
	* 参数：		pSender		-- 事件源对象
	*			dwConnID	-- 连接 ID
	*			pData		-- 已接收数据缓冲区
	*			iLength		-- 已接收数据长度
	* 返回值：	HR_OK / HR_IGNORE	-- 继续执行
	*			HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	virtual EnHandleResult OnReceive(T* pSender, CONNID dwConnID, const BYTE* pData, int iLength)				= 0;

	/*
	* 名称：数据到达通知（PULL 模型）
	* 描述：对于 PULL 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知
	*		
	* 参数：		pSender		-- 事件源对象
	*			dwConnID	-- 连接 ID
	*			iLength		-- 已接收数据长度
	* 返回值：	HR_OK / HR_IGNORE	-- 继续执行
	*			HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	virtual EnHandleResult OnReceive(T* pSender, CONNID dwConnID, int iLength)									= 0;

	/*
	* 名称：通信错误通知
	* 描述：通信发生错误后，Socket 监听器将收到该通知，并关闭连接
	*		
	* 参数：		pSender		-- 事件源对象
	*			dwConnID	-- 连接 ID
	*			enOperation	-- Socket 操作类型
	*			iErrorCode	-- 错误代码
	* 返回值：	忽略返回值
	*/
	virtual EnHandleResult OnClose(T* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)	= 0;

public:
	virtual ~ISocketListenerT() {}
};

template<class T> class IComplexSocketListenerT : public ISocketListenerT<T>
{
public:

	/*
	* 名称：关闭通信组件通知
	* 描述：通信组件关闭时，Socket 监听器将收到该通知
	*		
	* 参数：		pSender		-- 事件源对象
	* 返回值：	忽略返回值
	*/
	virtual EnHandleResult OnShutdown(T* pSender)																= 0;

};

/************************************************************************
名称：服务端 Socket 监听器接口
描述：定义服务端 Socket 监听器的所有事件
************************************************************************/
template<class T> class IServerListenerT : public IComplexSocketListenerT<T>
{
public:

	/*
	* 名称：准备监听通知
	* 描述：通信服务端组件启动时，在监听 Socket 创建完成并开始执行监听前，Socket 监听
	*		器将收到该通知，监听器可以在通知处理方法中执行 Socket 选项设置等额外工作
	*		
	* 参数：		pSender		-- 事件源对象
	*			soListen	-- 监听 Socket
	* 返回值：	HR_OK / HR_IGNORE	-- 继续执行
	*			HR_ERROR			-- 终止启动通信服务组件
	*/
	virtual EnHandleResult OnPrepareListen(T* pSender, SOCKET soListen)						= 0;

	/*
	* 名称：接收连接通知
	* 描述：接收到客户端连接请求时，Socket 监听器将收到该通知，监听器可以在通知处理方
	*		法中执行 Socket 选项设置或拒绝客户端连接等额外工作
	*		
	* 参数：		pSender		-- 事件源对象
	*			dwConnID	-- 连接 ID
	*			soClient	-- TCP: 客户端 Socket 句柄，UDP: 客户端 Socket SOCKADDR 指针
	* 返回值：	HR_OK / HR_IGNORE	-- 接受连接
	*			HR_ERROR			-- 拒绝连接
	*/
	virtual EnHandleResult OnAccept(T* pSender, CONNID dwConnID, UINT_PTR soClient)			= 0;
};

/************************************************************************
名称：TCP 服务端 Socket 监听器接口
描述：定义 TCP 服务端 Socket 监听器的所有事件
************************************************************************/
class ITcpServerListener : public IServerListenerT<ITcpServer>
{
public:

};

/************************************************************************
名称：PUSH 模型服务端 Socket 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
class CTcpServerListener : public ITcpServerListener
{
public:
	virtual EnHandleResult OnPrepareListen(ITcpServer* pSender, SOCKET soListen)							{return HR_IGNORE;}
	virtual EnHandleResult OnAccept(ITcpServer* pSender, CONNID dwConnID, UINT_PTR soClient)				{return HR_IGNORE;}
	virtual EnHandleResult OnHandShake(ITcpServer* pSender, CONNID dwConnID)								{return HR_IGNORE;}
	virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, int iLength)						{return HR_IGNORE;}
	virtual EnHandleResult OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)		{return HR_IGNORE;}
	virtual EnHandleResult OnShutdown(ITcpServer* pSender)													{return HR_IGNORE;}
};

/************************************************************************
名称：PULL 模型服务端 Socket 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
class CTcpPullServerListener : public CTcpServerListener
{
public:
	virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, int iLength)						= 0;
	virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)	{return HR_IGNORE;}
};

#ifdef _UDP_SUPPORT

/************************************************************************
名称：UDP 服务端 Socket 监听器接口
描述：定义 UDP 服务端 Socket 监听器的所有事件
************************************************************************/
class IUdpServerListener : public IServerListenerT<IUdpServer>
{
public:

};

/************************************************************************
名称：UDP 服务端 Socket 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
class CUdpServerListener : public IUdpServerListener
{
public:
	virtual EnHandleResult OnPrepareListen(IUdpServer* pSender, SOCKET soListen)						{return HR_IGNORE;}
	virtual EnHandleResult OnAccept(IUdpServer* pSender, CONNID dwConnID, UINT_PTR pSockAddr)			{return HR_IGNORE;}
	virtual EnHandleResult OnHandShake(IUdpServer* pSender, CONNID dwConnID)							{return HR_IGNORE;}
	virtual EnHandleResult OnReceive(IUdpServer* pSender, CONNID dwConnID, int iLength)					{return HR_IGNORE;}
	virtual EnHandleResult OnSend(IUdpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)	{return HR_IGNORE;}
	virtual EnHandleResult OnShutdown(IUdpServer* pSender)												{return HR_IGNORE;}
};

#endif

/************************************************************************
名称：通信代理 Socket 监听器接口
描述：定义 通信代理 Socket 监听器的所有事件
************************************************************************/
template<class T> class IAgentListenerT : public IComplexSocketListenerT<T>
{
public:

	/*
	* 名称：准备连接通知
	* 描述：通信客户端组件启动时，在客户端 Socket 创建完成并开始执行连接前，Socket 监听
	*		器将收到该通知，监听器可以在通知处理方法中执行 Socket 选项设置等额外工作
	*		
	* 参数：		pSender		-- 事件源对象
	*			dwConnID	-- 连接 ID
	*			socket		-- 客户端 Socket
	* 返回值：	HR_OK / HR_IGNORE	-- 继续执行
	*			HR_ERROR			-- 终止启动通信客户端组件
	*/
	virtual EnHandleResult OnPrepareConnect(T* pSender, CONNID dwConnID, SOCKET socket)		= 0;

	/*
	* 名称：连接完成通知
	* 描述：与服务端成功建立连接时，Socket 监听器将收到该通知
	*		
	* 参数：		pSender		-- 事件源对象
	*			dwConnID	-- 连接 ID
	* 返回值：	HR_OK / HR_IGNORE	-- 继续执行
	*			HR_ERROR			-- 同步连接：终止启动通信客户端组件
	*								   异步连接：关闭连接
	*/
	virtual EnHandleResult OnConnect(T* pSender, CONNID dwConnID)							= 0;
};

/************************************************************************
名称：TCP 通信代理 Socket 监听器接口
描述：定义 TCP 通信代理 Socket 监听器的所有事件
************************************************************************/
class ITcpAgentListener : public IAgentListenerT<ITcpAgent>
{
public:

};

/************************************************************************
名称：PUSH 模型通信代理 Socket 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
class CTcpAgentListener : public ITcpAgentListener
{
public:
	virtual EnHandleResult OnPrepareConnect(ITcpAgent* pSender, CONNID dwConnID, SOCKET socket)				{return HR_IGNORE;}
	virtual EnHandleResult OnConnect(ITcpAgent* pSender, CONNID dwConnID)									{return HR_IGNORE;}
	virtual EnHandleResult OnHandShake(ITcpAgent* pSender, CONNID dwConnID)									{return HR_IGNORE;}
	virtual EnHandleResult OnReceive(ITcpAgent* pSender, CONNID dwConnID, int iLength)						{return HR_IGNORE;}
	virtual EnHandleResult OnSend(ITcpAgent* pSender, CONNID dwConnID, const BYTE* pData, int iLength)		{return HR_IGNORE;}
	virtual EnHandleResult OnShutdown(ITcpAgent* pSender)													{return HR_IGNORE;}
};

/************************************************************************
名称：PULL 通信代理 Socket 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
class CTcpPullAgentListener : public CTcpAgentListener
{
public:
	virtual EnHandleResult OnReceive(ITcpAgent* pSender, CONNID dwConnID, int iLength)						= 0;
	virtual EnHandleResult OnReceive(ITcpAgent* pSender, CONNID dwConnID, const BYTE* pData, int iLength)	{return HR_IGNORE;}
};

/************************************************************************
名称：客户端 Socket 监听器接口
描述：定义客户端 Socket 监听器的所有事件
************************************************************************/

template<class T> class IClientListenerT : public ISocketListenerT<T>
{
public:
	
	/*
	* 名称：准备连接通知
	* 描述：通信客户端组件启动时，在客户端 Socket 创建完成并开始执行连接前，Socket 监听
	*		器将收到该通知，监听器可以在通知处理方法中执行 Socket 选项设置等额外工作
	*		
	* 参数：		pSender		-- 事件源对象
	*			dwConnID	-- 连接 ID
	*			socket		-- 客户端 Socket
	* 返回值：	HR_OK / HR_IGNORE	-- 继续执行
	*			HR_ERROR			-- 终止启动通信客户端组件
	*/
	virtual EnHandleResult OnPrepareConnect(T* pSender, CONNID dwConnID, SOCKET socket)						= 0;

	/*
	* 名称：连接完成通知
	* 描述：与服务端成功建立连接时，Socket 监听器将收到该通知
	*		
	* 参数：		pSender		-- 事件源对象
	*			dwConnID	-- 连接 ID
	* 返回值：	HR_OK / HR_IGNORE	-- 继续执行
	*			HR_ERROR			-- 同步连接：终止启动通信客户端组件
	*								   异步连接：关闭连接
	*/
	virtual EnHandleResult OnConnect(T* pSender, CONNID dwConnID)											= 0;
};

/************************************************************************
名称：TCP 客户端 Socket 监听器接口
描述：定义 TCP 客户端 Socket 监听器的所有事件
************************************************************************/
class ITcpClientListener : public IClientListenerT<ITcpClient>
{
public:

};

/************************************************************************
名称：PUSH 模型客户端 Socket 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
class CTcpClientListener : public ITcpClientListener
{
public:
	virtual EnHandleResult OnPrepareConnect(ITcpClient* pSender, CONNID dwConnID, SOCKET socket)			{return HR_IGNORE;}
	virtual EnHandleResult OnConnect(ITcpClient* pSender, CONNID dwConnID)									{return HR_IGNORE;}
	virtual EnHandleResult OnHandShake(ITcpClient* pSender, CONNID dwConnID)								{return HR_IGNORE;}
	virtual EnHandleResult OnReceive(ITcpClient* pSender, CONNID dwConnID, int iLength)						{return HR_IGNORE;}
	virtual EnHandleResult OnSend(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)		{return HR_IGNORE;}
};

/************************************************************************
名称：PULL 客户端 Socket 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
class CTcpPullClientListener : public CTcpClientListener
{
public:
	virtual EnHandleResult OnReceive(ITcpClient* pSender, CONNID dwConnID, int iLength)						= 0;
	virtual EnHandleResult OnReceive(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)	{return HR_IGNORE;}
};

#ifdef _UDP_SUPPORT

/************************************************************************
名称：UDP 客户端 Socket 监听器接口
描述：定义 UDP 客户端 Socket 监听器的所有事件
************************************************************************/
class IUdpClientListener : public IClientListenerT<IUdpClient>
{
public:

};

/************************************************************************
名称：UDP 户端 Socket 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
class CUdpClientListener : public IUdpClientListener
{
public:
	virtual EnHandleResult OnPrepareConnect(IUdpClient* pSender, CONNID dwConnID, SOCKET socket)			{return HR_IGNORE;}
	virtual EnHandleResult OnConnect(IUdpClient* pSender, CONNID dwConnID)									{return HR_IGNORE;}
	virtual EnHandleResult OnHandShake(IUdpClient* pSender, CONNID dwConnID)								{return HR_IGNORE;}
	virtual EnHandleResult OnReceive(IUdpClient* pSender, CONNID dwConnID, int iLength)						{return HR_IGNORE;}
	virtual EnHandleResult OnSend(IUdpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)		{return HR_IGNORE;}
};

/************************************************************************
名称：UDP 传播 Socket 监听器接口
描述：定义 UDP 传播 Socket 监听器的所有事件
************************************************************************/
class IUdpCastListener : public IClientListenerT<IUdpCast>
{
public:

};

/************************************************************************
名称：UDP 传播 Socket 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
class CUdpCastListener : public IUdpCastListener
{
public:
	virtual EnHandleResult OnPrepareConnect(IUdpCast* pSender, CONNID dwConnID, SOCKET socket)				{return HR_IGNORE;}
	virtual EnHandleResult OnConnect(IUdpCast* pSender, CONNID dwConnID)									{return HR_IGNORE;}
	virtual EnHandleResult OnHandShake(IUdpCast* pSender, CONNID dwConnID)									{return HR_IGNORE;}
	virtual EnHandleResult OnReceive(IUdpCast* pSender, CONNID dwConnID, int iLength)						{return HR_IGNORE;}
	virtual EnHandleResult OnSend(IUdpCast* pSender, CONNID dwConnID, const BYTE* pData, int iLength)		{return HR_IGNORE;}
};

/************************************************************************
名称：UDP 节点 Socket 监听器接口
描述：定义 UDP 节点 Socket 监听器的所有事件
************************************************************************/
class IUdpNodeListener
{
public:

	/*
	* 名称：准备监听通知
	* 描述：通信组件启动时，在监听 Socket 创建完成并开始执行监听前，Socket 监听器
	*		将收到该通知，监听器可以在通知处理方法中执行 Socket 选项设置等额外工作
	*		
	* 参数：		pSender		-- 事件源对象
	*			soListen	-- 监听 Socket
	* 返回值：	HR_OK / HR_IGNORE	-- 继续执行
	*			HR_ERROR			-- 终止启动通信服务组件
	*/
	virtual EnHandleResult OnPrepareListen(IUdpNode* pSender, SOCKET soListen)															= 0;

	/*
	* 名称：已发送数据通知
	* 描述：成功发送数据后，Socket 监听器将收到该通知
	*		
	* 参数：		pSender				-- 事件源对象
	*			lpszRemoteAddress	-- 远程地址
	*			usRemotePort		-- 远程端口
	*			pData				-- 已发送数据缓冲区
	*			iLength				-- 已发送数据长度
	* 返回值：	忽略返回值
	*/
	virtual EnHandleResult OnSend(IUdpNode* pSender, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pData, int iLength)	= 0;

	/*
	* 名称：数据到达通知（PUSH 模型）
	* 描述：成功接收数据后，Socket 监听器将收到该通知
	*		
	* 参数：		pSender				-- 事件源对象
	*			lpszRemoteAddress	-- 远程地址
	*			usRemotePort		-- 远程端口
	*			pData				-- 已发送数据缓冲区
	*			iLength				-- 已发送数据长度
	* 返回值：	忽略返回值
	*/
	virtual EnHandleResult OnReceive(IUdpNode* pSender, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pData, int iLength)	= 0;

	/*
	* 名称：通信错误通知
	* 描述：通信发生错误后，Socket 监听器将收到该通知
	*		
	* 参数：		pSender				-- 事件源对象
	*			lpszRemoteAddress	-- 远程地址
	*			usRemotePort		-- 远程端口
	*			enOperation			-- Socket 操作类型
	*			iErrorCode			-- 错误代码
	*			pData				-- 本次事件关联的数据缓冲区
	*			iLength				-- 本次事件关联的数据长度
	* 返回值：	忽略返回值
	*/
	virtual EnHandleResult OnError(IUdpNode* pSender, EnSocketOperation enOperation, int iErrorCode, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pData, int iLength)	= 0;

	/*
	* 名称：关闭通信组件通知
	* 描述：通信组件关闭时，Socket 监听器将收到该通知
	*		
	* 参数：		pSender		-- 事件源对象
	* 返回值：	忽略返回值
	*/
	virtual EnHandleResult OnShutdown(IUdpNode* pSender)																				= 0;

public:
	virtual ~IUdpNodeListener() {}
};

/************************************************************************
名称：UDP 节点 Socket 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
class CUdpNodeListener : public IUdpNodeListener
{
public:
	virtual EnHandleResult OnPrepareListen(IUdpNode* pSender, SOCKET soListen)															{return HR_IGNORE;}
	virtual EnHandleResult OnSend(IUdpNode* pSender, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pData, int iLength)	{return HR_IGNORE;}
	virtual EnHandleResult OnShutdown(IUdpNode* pSender)																				{return HR_IGNORE;}
};

#endif

/*****************************************************************************************************************************************************/
/****************************************************************** HTTP Interfaces ******************************************************************/
/*****************************************************************************************************************************************************/

#ifdef _HTTP_SUPPORT

/************************************************************************
名称：复合 Http 组件接口
描述：定义复合 Http 组件的所有操作方法和属性访问方法，复合 Http 组件同时管理多个 Http 连接
************************************************************************/
class IComplexHttp
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*
	* 名称：启动 HTTP 通信
	* 描述：当通信组件设置为非自动启动 HTTP 通信时，需要调用本方法启动 HTTP 通信
	*		
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL StartHttp(CONNID dwConnID)												= 0;

	/*
	* 名称：发送 Chunked 数据分片
	* 描述：向对端发送 Chunked 数据分片
	*		
	* 参数：		dwConnID		-- 连接 ID
	*			pData			-- Chunked 数据分片
	*			iLength			-- 数据分片长度（为 0 表示结束分片）
	*			lpszExtensions	-- 扩展属性（默认：nullptr）
	* 返回值：	TRUE			-- 成功
	*			FALSE			-- 失败
	*/
	virtual BOOL SendChunkData(CONNID dwConnID, const BYTE* pData = nullptr, int iLength = 0, LPCSTR lpszExtensions = nullptr)	= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 设置本地协议版本 */
	virtual void SetLocalVersion(EnHttpVersion usVersion)								= 0;
	/* 获取本地协议版本 */
	virtual EnHttpVersion GetLocalVersion()												= 0;

	/* 检查是否升级协议 */
	virtual BOOL IsUpgrade(CONNID dwConnID)												= 0;
	/* 检查是否有 Keep-Alive 标识 */
	virtual BOOL IsKeepAlive(CONNID dwConnID)											= 0;
	/* 获取协议版本 */
	virtual USHORT GetVersion(CONNID dwConnID)											= 0;
	/* 获取内容长度 */
	virtual ULONGLONG GetContentLength(CONNID dwConnID)									= 0;
	/* 获取内容类型 */
	virtual LPCSTR GetContentType(CONNID dwConnID)										= 0;
	/* 获取内容编码 */
	virtual LPCSTR GetContentEncoding(CONNID dwConnID)									= 0;
	/* 获取传输编码 */
	virtual LPCSTR GetTransferEncoding(CONNID dwConnID)									= 0;
	/* 获取协议升级类型 */
	virtual EnHttpUpgradeType GetUpgradeType(CONNID dwConnID)							= 0;
	/* 获取解析错误代码 */
	virtual USHORT GetParseErrorCode(CONNID dwConnID, LPCSTR* lpszErrorDesc = nullptr)	= 0;

	/* 获取某个请求头（单值） */
	virtual BOOL GetHeader(CONNID dwConnID, LPCSTR lpszName, LPCSTR* lpszValue)						= 0;
	/* 获取某个请求头（多值） */
	virtual BOOL GetHeaders(CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue[], DWORD& dwCount)	= 0;
	/* 获取所有请求头 */
	virtual BOOL GetAllHeaders(CONNID dwConnID, THeader lpHeaders[], DWORD& dwCount)				= 0;
	/* 获取所有请求头名称 */
	virtual BOOL GetAllHeaderNames(CONNID dwConnID, LPCSTR lpszName[], DWORD& dwCount)				= 0;

	/* 获取 Cookie */
	virtual BOOL GetCookie(CONNID dwConnID, LPCSTR lpszName, LPCSTR* lpszValue)						= 0;
	/* 获取所有 Cookie */
	virtual BOOL GetAllCookies(CONNID dwConnID, TCookie lpCookies[], DWORD& dwCount)				= 0;

	/*
	// !! maybe implemented in future !! //

	virtual BOOL GetParam(CONNID dwConnID, LPCSTR lpszName, LPCSTR* lpszValue)						= 0;
	virtual BOOL GetParams(CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue[], DWORD& dwCount)	= 0;
	virtual BOOL GetAllParams(CONNID dwConnID, LPPARAM lpszParam[], DWORD& dwCount)					= 0;
	virtual BOOL GetAllParamNames(CONNID dwConnID, LPCSTR lpszName[], DWORD& dwCount)				= 0;
	*/

	/* 获取当前 WebSocket 消息状态，传入 nullptr 则不获取相应字段 */
	virtual BOOL GetWSMessageState(CONNID dwConnID, BOOL* lpbFinal, BYTE* lpiReserved, BYTE* lpiOperationCode, LPCBYTE* lpszMask, ULONGLONG* lpullBodyLen, ULONGLONG* lpullBodyRemain)	= 0;

	/* 设置 HTTP 启动方式（默认：TRUE，自动启动） */
	virtual void SetHttpAutoStart(BOOL bAutoStart)													= 0;
	/* 获取 HTTP 启动方式 */
	virtual BOOL IsHttpAutoStart()																	= 0;

public:
	virtual ~IComplexHttp() {}
};

/************************************************************************
名称：复合 Http 请求者组件接口
描述：定义复合 Http 请求者组件的所有操作方法和属性访问方法
************************************************************************/
class IComplexHttpRequester : public IComplexHttp
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*
	* 名称：发送 WebSocket 消息
	* 描述：向对端端发送 WebSocket 消息
	*		
	* 参数：		dwConnID		-- 连接 ID
	*			bFinal			-- 是否结束帧
	*			iReserved		-- RSV1/RSV2/RSV3 各 1 位
	*			iOperationCode	-- 操作码：0x0 - 0xF
	*			lpszMask		-- 掩码（nullptr 或 4 字节掩码，如果为 nullptr 则没有掩码）
	*			pData			-- 消息体数据缓冲区
	*			iLength			-- 消息体数据长度
	*			ullBodyLen		-- 消息总长度
	* 								ullBodyLen = 0		 -> 消息总长度为 iLength
	* 								ullBodyLen = iLength -> 消息总长度为 ullBodyLen
	* 								ullBodyLen > iLength -> 消息总长度为 ullBodyLen，后续消息体长度为 ullBOdyLen - iLength，后续消息体通过底层方法 Send() / SendPackets() 发送
	* 								ullBodyLen < iLength -> 错误参数，发送失败
	* 返回值：	TRUE			-- 成功
	*			FALSE			-- 失败
	*/
	virtual BOOL SendWSMessage(CONNID dwConnID, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], const BYTE* pData = nullptr, int iLength = 0, ULONGLONG ullBodyLen = 0)	= 0;

	/*
	* 名称：发送请求
	* 描述：向服务端发送 HTTP 请求
	*		
	* 参数：		dwConnID		-- 连接 ID
	*			lpszMethod		-- 请求方法
	*			lpszPath		-- 请求路径
	*			lpHeaders		-- 请求头
	*			iHeaderCount	-- 请求头数量
	*			pBody			-- 请求体
	*			iLength			-- 请求体长度
	* 返回值：	TRUE			-- 成功
	*			FALSE			-- 失败
	*/
	virtual BOOL SendRequest(CONNID dwConnID, LPCSTR lpszMethod, LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0, const BYTE* pBody = nullptr, int iLength = 0)	= 0;

	/*
	* 名称：发送本地文件
	* 描述：向指定连接发送 4096 KB 以下的小文件
	*		
	* 参数：		dwConnID		-- 连接 ID
	*			lpszFileName	-- 文件路径
	*			lpszMethod		-- 请求方法
	*			lpszPath		-- 请求路径
	*			lpHeaders		-- 请求头
	*			iHeaderCount	-- 请求头数量
	* 返回值：	TRUE			-- 成功
	*			FALSE			-- 失败
	*/
	virtual BOOL SendLocalFile(CONNID dwConnID, LPCSTR lpszFileName, LPCSTR lpszMethod, LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)							= 0;

	/* 发送 POST 请求 */
	virtual BOOL SendPost(CONNID dwConnID, LPCSTR lpszPath, const THeader lpHeaders[], int iHeaderCount, const BYTE* pBody, int iLength)													= 0;
	/* 发送 PUT 请求 */
	virtual BOOL SendPut(CONNID dwConnID, LPCSTR lpszPath, const THeader lpHeaders[], int iHeaderCount, const BYTE* pBody, int iLength)														= 0;
	/* 发送 PATCH 请求 */
	virtual BOOL SendPatch(CONNID dwConnID, LPCSTR lpszPath, const THeader lpHeaders[], int iHeaderCount, const BYTE* pBody, int iLength)													= 0;
	/* 发送 GET 请求 */
	virtual BOOL SendGet(CONNID dwConnID, LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)																		= 0;
	/* 发送 DELETE 请求 */
	virtual BOOL SendDelete(CONNID dwConnID, LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)																	= 0;
	/* 发送 HEAD 请求 */
	virtual BOOL SendHead(CONNID dwConnID, LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)																		= 0;
	/* 发送 TRACE 请求 */
	virtual BOOL SendTrace(CONNID dwConnID, LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)																		= 0;
	/* 发送 OPTIONS 请求 */
	virtual BOOL SendOptions(CONNID dwConnID, LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)																	= 0;
	/* 发送 CONNECT 请求 */
	virtual BOOL SendConnect(CONNID dwConnID, LPCSTR lpszHost, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)																	= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 获取 HTTP 状态码 */
	virtual USHORT GetStatusCode(CONNID dwConnID)						= 0;

	/* 设置是否使用 Cookie（默认：TRUE） */
	virtual void SetUseCookie(BOOL bUseCookie)							= 0;
	/* 检查是否使用 Cookie */
	virtual BOOL IsUseCookie()											= 0;
};

/************************************************************************
名称：复合 Http 响应者组件接口
描述：定义复合 Http 响应者组件的所有操作方法和属性访问方法
************************************************************************/
class IComplexHttpResponder : public IComplexHttp
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*
	* 名称：发送 WebSocket 消息
	* 描述：向对端端发送 WebSocket 消息
	*		
	* 参数：		dwConnID		-- 连接 ID
	*			bFinal			-- 是否结束帧
	*			iReserved		-- RSV1/RSV2/RSV3 各 1 位
	*			iOperationCode	-- 操作码：0x0 - 0xF
	*			pData			-- 消息体数据缓冲区
	*			iLength			-- 消息体数据长度
	*			ullBodyLen		-- 消息总长度
	* 								ullBodyLen = 0		 -> 消息总长度为 iLength
	* 								ullBodyLen = iLength -> 消息总长度为 ullBodyLen
	* 								ullBodyLen > iLength -> 消息总长度为 ullBodyLen，后续消息体长度为 ullBOdyLen - iLength，后续消息体通过底层方法 Send() / SendPackets() 发送
	* 								ullBodyLen < iLength -> 错误参数，发送失败
	* 返回值：	TRUE			-- 成功
	*			FALSE			-- 失败
	*/
	virtual BOOL SendWSMessage(CONNID dwConnID, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE* pData = nullptr, int iLength = 0, ULONGLONG ullBodyLen = 0)	= 0;

	/*
	* 名称：回复请求
	* 描述：向客户端回复 HTTP 请求
	*		
	* 参数：		dwConnID		-- 连接 ID
	*			usStatusCode	-- HTTP 状态码
	*			lpszDesc		-- HTTP 状态描述
	*			lpHeaders		-- 回复请求头
	*			iHeaderCount	-- 回复请求头数量
	*			pData			-- 回复请求体
	*			iLength			-- 回复请求体长度
	* 返回值：	TRUE			-- 成功
	*			FALSE			-- 失败
	*/
	virtual BOOL SendResponse(CONNID dwConnID, USHORT usStatusCode, LPCSTR lpszDesc = nullptr, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0, const BYTE* pData = nullptr, int iLength = 0)	= 0;

	/*
	* 名称：发送本地文件
	* 描述：向指定连接发送 4096 KB 以下的小文件
	*		
	* 参数：		dwConnID		-- 连接 ID
	*			lpszFileName	-- 文件路径
	*			usStatusCode	-- HTTP 状态码
	*			lpszDesc		-- HTTP 状态描述
	*			lpHeaders		-- 回复请求头
	*			iHeaderCount	-- 回复请求头数量
	* 返回值：	TRUE			-- 成功
	*			FALSE			-- 失败
	*/
	virtual BOOL SendLocalFile(CONNID dwConnID, LPCSTR lpszFileName, USHORT usStatusCode = HSC_OK, LPCSTR lpszDesc = nullptr, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)				= 0;

	/*
	* 名称：释放连接
	* 描述：把连接放入释放队列，等待某个时间（通过 SetReleaseDelay() 设置）关闭连接
	*		
	* 参数：		dwConnID		-- 连接 ID
	* 返回值：	TRUE			-- 成功
	*			FALSE			-- 失败
	*/
	virtual BOOL Release(CONNID dwConnID)								= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 获取主机 */
	virtual LPCSTR GetHost(CONNID dwConnID)								= 0;

	/* 设置连接释放延时（默认：3000 毫秒） */
	virtual void SetReleaseDelay(DWORD dwReleaseDelay)					= 0;
	/* 获取连接释放延时 */
	virtual DWORD GetReleaseDelay()										= 0;

	/* 获取请求行 URL 域掩码（URL 域参考：EnHttpUrlField） */
	virtual USHORT GetUrlFieldSet(CONNID dwConnID)						= 0;
	/* 获取某个 URL 域值 */
	virtual LPCSTR GetUrlField(CONNID dwConnID, EnHttpUrlField enField)	= 0;
	/* 获取请求方法 */
	virtual LPCSTR GetMethod(CONNID dwConnID)							= 0;
};

/************************************************************************
名称：简单 HTTP 组件接口
描述：定义 简单 HTTP 组件的所有操作方法和属性访问方法
************************************************************************/
class IHttp
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*
	* 名称：发送 WebSocket 消息
	* 描述：向对端端发送 WebSocket 消息
	*		
	* 参数：		bFinal			-- 是否结束帧
	*			iReserved		-- RSV1/RSV2/RSV3 各 1 位
	*			iOperationCode	-- 操作码：0x0 - 0xF
	*			lpszMask		-- 掩码（nullptr 或 4 字节掩码，如果为 nullptr 则没有掩码）
	*			pData			-- 消息体数据缓冲区
	*			iLength			-- 消息体数据长度
	*			ullBodyLen		-- 消息总长度
	* 								ullBodyLen = 0		 -> 消息总长度为 iLength
	* 								ullBodyLen = iLength -> 消息总长度为 ullBodyLen
	* 								ullBodyLen > iLength -> 消息总长度为 ullBodyLen，后续消息体长度为 ullBOdyLen - iLength，后续消息体通过底层方法 Send() / SendPackets() 发送
	* 								ullBodyLen < iLength -> 错误参数，发送失败
	* 返回值：	TRUE			-- 成功
	*			FALSE			-- 失败
	*/
	virtual BOOL SendWSMessage(BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], const BYTE* pData = nullptr, int iLength = 0, ULONGLONG ullBodyLen = 0)	= 0;

	/*
	* 名称：启动 HTTP 通信
	* 描述：当通信组件设置为非自动启动 HTTP 通信时，需要调用本方法启动 HTTP 通信
	*		
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL StartHttp()											= 0;

	/*
	* 名称：发送 Chunked 数据分片
	* 描述：向对端发送 Chunked 数据分片
	*		
	* 参数：		pData			-- Chunked 数据分片
	*			iLength			-- 数据分片长度（为 0 表示结束分片）
	*			lpszExtensions	-- 扩展属性（默认：nullptr）
	* 返回值：	TRUE			-- 成功
	*			FALSE			-- 失败
	*/
	virtual BOOL SendChunkData(const BYTE* pData = nullptr, int iLength = 0, LPCSTR lpszExtensions = nullptr)	= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 设置本地协议版本 */
	virtual void SetLocalVersion(EnHttpVersion usVersion)				= 0;
	/* 获取本地协议版本 */
	virtual EnHttpVersion GetLocalVersion()								= 0;

	/* 检查是否升级协议 */
	virtual BOOL IsUpgrade()											= 0;
	/* 检查是否有 Keep-Alive 标识 */
	virtual BOOL IsKeepAlive()											= 0;
	/* 获取协议版本 */
	virtual USHORT GetVersion()											= 0;
	/* 获取内容长度 */
	virtual ULONGLONG GetContentLength()								= 0;
	/* 获取内容类型 */
	virtual LPCSTR GetContentType()										= 0;
	/* 获取内容编码 */
	virtual LPCSTR GetContentEncoding()									= 0;
	/* 获取传输编码 */
	virtual LPCSTR GetTransferEncoding()								= 0;
	/* 获取协议升级类型 */
	virtual EnHttpUpgradeType GetUpgradeType()							= 0;
	/* 获取解析错误代码 */
	virtual USHORT GetParseErrorCode(LPCSTR* lpszErrorDesc = nullptr)	= 0;

	/* 获取 HTTP 状态码 */
	virtual USHORT GetStatusCode()										= 0;

	/* 获取某个请求头（单值） */
	virtual BOOL GetHeader(LPCSTR lpszName, LPCSTR* lpszValue)						= 0;
	/* 获取某个请求头（多值） */
	virtual BOOL GetHeaders(LPCSTR lpszName, LPCSTR lpszValue[], DWORD& dwCount)	= 0;
	/* 获取所有请求头 */
	virtual BOOL GetAllHeaders(THeader lpHeaders[], DWORD& dwCount)					= 0;
	/* 获取所有请求头名称 */
	virtual BOOL GetAllHeaderNames(LPCSTR lpszName[], DWORD& dwCount)				= 0;

	/* 获取 Cookie */
	virtual BOOL GetCookie(LPCSTR lpszName, LPCSTR* lpszValue)						= 0;
	/* 获取所有 Cookie */
	virtual BOOL GetAllCookies(TCookie lpCookies[], DWORD& dwCount)					= 0;

	/*
	// !! maybe implemented in future !! //

	virtual BOOL GetParam(LPCSTR lpszName, LPCSTR* lpszValue)						= 0;
	virtual BOOL GetParams(LPCSTR lpszName, LPCSTR lpszValue[], DWORD& dwCount)		= 0;
	virtual BOOL GetAllParams(LPPARAM lpszParam[], DWORD& dwCount)					= 0;
	virtual BOOL GetAllParamNames(LPCSTR lpszName[], DWORD& dwCount)				= 0;
	*/

	/* 获取当前 WebSocket 消息状态，传入 nullptr 则不获取相应字段 */
	virtual BOOL GetWSMessageState(BOOL* lpbFinal, BYTE* lpiReserved, BYTE* lpiOperationCode, LPCBYTE* lpszMask, ULONGLONG* lpullBodyLen, ULONGLONG* lpullBodyRemain)	= 0;

	/* 设置 HTTP 启动方式（默认：TRUE，自动启动） */
	virtual void SetHttpAutoStart(BOOL bAutoStart)									= 0;
	/* 获取 HTTP 启动方式 */
	virtual BOOL IsHttpAutoStart()													= 0;

public:
	virtual ~IHttp() {}
};

/************************************************************************
名称：简单 Http 请求者组件接口
描述：定义简单 Http 请求者组件的所有操作方法和属性访问方法
************************************************************************/
class IHttpRequester : public IHttp
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*
	* 名称：发送请求
	* 描述：向服务端发送 HTTP 请求
	*		
	* 参数：		lpszMethod		-- 请求方法
	*			lpszPath		-- 请求路径
	*			lpHeaders		-- 请求头
	*			iHeaderCount	-- 请求头数量
	*			pBody			-- 请求体
	*			iLength			-- 请求体长度
	* 返回值：	TRUE			-- 成功
	*			FALSE			-- 失败
	*/
	virtual BOOL SendRequest(LPCSTR lpszMethod, LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0, const BYTE* pBody = nullptr, int iLength = 0)	= 0;

	/*
	* 名称：发送本地文件
	* 描述：向指定连接发送 4096 KB 以下的小文件
	*		
	* 参数：		dwConnID		-- 连接 ID
	*			lpszFileName	-- 文件路径
	*			lpszMethod		-- 请求方法
	*			lpszPath		-- 请求路径
	*			lpHeaders		-- 请求头
	*			iHeaderCount	-- 请求头数量
	* 返回值：	TRUE			-- 成功
	*			FALSE			-- 失败
	*/
	virtual BOOL SendLocalFile(LPCSTR lpszFileName, LPCSTR lpszMethod, LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)							= 0;

	/* 发送 POST 请求 */
	virtual BOOL SendPost(LPCSTR lpszPath, const THeader lpHeaders[], int iHeaderCount, const BYTE* pBody, int iLength)														= 0;
	/* 发送 PUT 请求 */
	virtual BOOL SendPut(LPCSTR lpszPath, const THeader lpHeaders[], int iHeaderCount, const BYTE* pBody, int iLength)														= 0;
	/* 发送 PATCH 请求 */
	virtual BOOL SendPatch(LPCSTR lpszPath, const THeader lpHeaders[], int iHeaderCount, const BYTE* pBody, int iLength)													= 0;
	/* 发送 GET 请求 */
	virtual BOOL SendGet(LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)																		= 0;
	/* 发送 DELETE 请求 */
	virtual BOOL SendDelete(LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)																		= 0;
	/* 发送 HEAD 请求 */
	virtual BOOL SendHead(LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)																		= 0;
	/* 发送 TRACE 请求 */
	virtual BOOL SendTrace(LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)																		= 0;
	/* 发送 OPTIONS 请求 */
	virtual BOOL SendOptions(LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)																	= 0;
	/* 发送 CONNECT 请求 */
	virtual BOOL SendConnect(LPCSTR lpszHost, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)																	= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 设置是否使用 Cookie（默认：TRUE） */
	virtual void SetUseCookie(BOOL bUseCookie)								= 0;
	/* 检查是否使用 Cookie */
	virtual BOOL IsUseCookie()												= 0;
};

/************************************************************************
名称：简单 Http 同步请求者组件接口
描述：定义简单 Http 同步请求者组件的所有操作方法和属性访问方法
************************************************************************/
class IHttpSyncRequester : public IHttpRequester
{
public:

	/*
	* 名称：发送 URL 请求
	* 描述：向服务端发送 HTTP URL 请求
	*		
	* 参数：		lpszMethod		-- 请求方法
	*			lpszUrl			-- 请求 URL
	*			lpHeaders		-- 请求头
	*			iHeaderCount	-- 请求头数量
	*			pBody			-- 请求体
	*			iLength			-- 请求体长度
	*			bForceReconnect	-- 强制重新连接（默认：FALSE，当请求 URL 的主机和端口与现有连接一致时，重用现有连接）
	* 返回值：	TRUE			-- 成功
	*			FALSE			-- 失败
	*/
	virtual BOOL OpenUrl(LPCSTR lpszMethod, LPCSTR lpszUrl, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0, const BYTE* pBody = nullptr, int iLength = 0, BOOL bForceReconnect = FALSE)	= 0;

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*
	* 名称：清除请求结果
	* 描述：清除上一次请求的响应头和响应体等结果信息（该方法会在每次发送请求前自动调用）
	*
	* 参数：		
	* 返回值：	TRUE			-- 成功
	*			FALSE			-- 失败
	*/
	virtual BOOL CleanupRequestResult	()									= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 设置连接超时（毫秒，0：系统默认超时，默认：5000） */
	virtual void SetConnectTimeout		(DWORD dwConnectTimeout)			= 0;
	/* 设置请求超时（毫秒，0：无限等待，默认：10000） */
	virtual void SetRequestTimeout		(DWORD dwRequestTimeout)			= 0;

	/* 获取连接超时 */
	virtual DWORD GetConnectTimeout		()									= 0;
	/* 获取请求超时 */
	virtual DWORD GetRequestTimeout		()									= 0;

	/* 获取响应体 */
	virtual BOOL GetResponseBody		(LPCBYTE* lpszBody, int* iLength)	= 0;
};


/************************************************************************
名称：HTTP 组件接口
描述：继承了 HTTP 和 Socket 接口
************************************************************************/
typedef DualInterface<IComplexHttpResponder, ITcpServer>	IHttpServer;
typedef DualInterface<IComplexHttpRequester, ITcpAgent>		IHttpAgent;
typedef DualInterface<IHttpRequester, ITcpClient>			IHttpClient;
typedef DualInterface<IHttpSyncRequester, ITcpClient>		IHttpSyncClient;

/************************************************************************
名称：IComplexHttp 组件监听器基接口
描述：定义 IComplexHttp 组件监听器的所有事件
************************************************************************/
template<class T> class IHttpListenerT
{
public:

	/*
	* 名称：开始解析通知
	* 描述：开始解析 HTTP 报文时，向监听器发送该通知
	*		
	* 参数：		pSender		-- 事件源对象
	*			dwConnID	-- 连接 ID
	* 返回值：	HPR_OK		-- 继续执行
	*			HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	virtual EnHttpParseResult OnMessageBegin(T* pSender, CONNID dwConnID)										= 0;

	/*
	* 名称：请求行解析完成通知（仅用于 HTTP 服务端）
	* 描述：请求行解析完成后，向监听器发送该通知
	*		
	* 参数：		pSender		-- 事件源对象
	*			dwConnID	-- 连接 ID
	*			lpszMethod	-- 请求方法名
	*			lpszUrl		-- 请求行中的 URL 域
	* 返回值：	HPR_OK		-- 继续执行
	*			HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	virtual EnHttpParseResult OnRequestLine(T* pSender, CONNID dwConnID, LPCSTR lpszMethod, LPCSTR lpszUrl)		= 0;

	/*
	* 名称：状态行解析完成通知（仅用于 HTTP 客户端）
	* 描述：状态行解析完成后，向监听器发送该通知
	*		
	* 参数：		pSender			-- 事件源对象
	*			dwConnID		-- 连接 ID
	*			usStatusCode	-- HTTP 状态码
	*			lpszDesc		-- 状态描述
	* 返回值：	HPR_OK			-- 继续执行
	*			HPR_ERROR		-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	virtual EnHttpParseResult OnStatusLine(T* pSender, CONNID dwConnID, USHORT usStatusCode, LPCSTR lpszDesc)	= 0;

	/*
	* 名称：请求头通知
	* 描述：每当解析完成一个请求头后，向监听器发送该通知
	*		
	* 参数：		pSender		-- 事件源对象
	*			dwConnID	-- 连接 ID
	*			lpszName	-- 请求头名称
	*			lpszValue	-- 请求头值
	* 返回值：	HPR_OK		-- 继续执行
	*			HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	virtual EnHttpParseResult OnHeader(T* pSender, CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue)			= 0;

	/*
	* 名称：请求头完成通知
	* 描述：解析完成所有请求头后，向监听器发送该通知
	*		
	* 参数：		pSender			-- 事件源对象
	*			dwConnID		-- 连接 ID
	* 返回值：	HPR_OK			-- 继续执行
	*			HPR_SKIP_BODY	-- 跳过当前请求的 HTTP BODY
	*			HPR_UPGRADE		-- 升级协议
	*			HPR_ERROR		-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	virtual EnHttpParseResult OnHeadersComplete(T* pSender, CONNID dwConnID)									= 0;

	/*
	* 名称：BODY 报文通知
	* 描述：每当接收到 HTTP BODY 报文，向监听器发送该通知
	*		
	* 参数：		pSender		-- 事件源对象
	*			dwConnID	-- 连接 ID
	*			pData		-- 数据缓冲区
	*			iLength		-- 数据长度
	* 返回值：	HPR_OK		-- 继续执行
	*			HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	virtual EnHttpParseResult OnBody(T* pSender, CONNID dwConnID, const BYTE* pData, int iLength)				= 0;

	/*
	* 名称：Chunked 报文头通知
	* 描述：每当解析出一个 Chunked 报文头，向监听器发送该通知
	*		
	* 参数：		pSender		-- 事件源对象
	*			dwConnID	-- 连接 ID
	*			iLength		-- Chunked 报文体数据长度
	* 返回值：	HPR_OK		-- 继续执行
	*			HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	virtual EnHttpParseResult OnChunkHeader(T* pSender, CONNID dwConnID, int iLength)							= 0;

	/*
	* 名称：Chunked 报文结束通知
	* 描述：每当解析完一个 Chunked 报文，向监听器发送该通知
	*		
	* 参数：		pSender		-- 事件源对象
	*			dwConnID	-- 连接 ID
	* 返回值：	HPR_OK		-- 继续执行
	*			HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	virtual EnHttpParseResult OnChunkComplete(T* pSender, CONNID dwConnID)										= 0;

	/*
	* 名称：完成解析通知
	* 描述：每当解析完成一个完整 HTTP 报文，向监听器发送该通知
	*		
	* 参数：		pSender		-- 事件源对象
	*			dwConnID	-- 连接 ID
	* 返回值：	HPR_OK		-- 继续执行
	*			HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	virtual EnHttpParseResult OnMessageComplete(T* pSender, CONNID dwConnID)									= 0;

	/*
	* 名称：升级协议通知
	* 描述：当需要升级协议时，向监听器发送该通知
	*		
	* 参数：		pSender			-- 事件源对象
	*			dwConnID		-- 连接 ID
	*			enUpgradeType	-- 协议类型
	* 返回值：	HPR_OK			-- 继续执行
	*			HPR_ERROR		-- 引发 OnClose() 事件并关闭连接
	*/
	virtual EnHttpParseResult OnUpgrade(T* pSender, CONNID dwConnID, EnHttpUpgradeType enUpgradeType)			= 0;

	/*
	* 名称：解析错误通知
	* 描述：当解析 HTTP 报文错误时，向监听器发送该通知
	*		
	* 参数：		pSender			-- 事件源对象
	*			dwConnID		-- 连接 ID
	*			iErrorCode		-- 错误代码
	*			lpszErrorDesc	-- 错误描述
	* 返回值：	HPR_OK			-- 继续执行
	*			HPR_ERROR		-- 引发 OnClose() 事件并关闭连接
	*/
	virtual EnHttpParseResult OnParseError(T* pSender, CONNID dwConnID, int iErrorCode, LPCSTR lpszErrorDesc)	= 0;

	/*
	* 名称：WebSocket 数据包头通知
	* 描述：当解析 WebSocket 数据包头时，向监听器发送该通知
	*		
	* 参数：		pSender			-- 事件源对象
	*			dwConnID		-- 连接 ID
	*			bFinal			-- 是否结束帧
	*			iReserved		-- RSV1/RSV2/RSV3 各 1 位
	*			iOperationCode	-- 操作码：0x0 - 0xF
	*			lpszMask		-- 掩码（nullptr 或 4 字节掩码，如果为 nullptr 则没有掩码）
	*			ullBodyLen		-- 消息体长度
	* 返回值：	HR_OK / HR_IGNORE	-- 继续执行
	*			HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	virtual EnHandleResult OnWSMessageHeader(T* pSender, CONNID dwConnID, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], ULONGLONG ullBodyLen)	= 0;

	/*
	* 名称：WebSocket 数据包体通知
	* 描述：当接收到 WebSocket 数据包体时，向监听器发送该通知
	*		
	* 参数：		pSender		-- 事件源对象
	*			dwConnID	-- 连接 ID
	*			pData		-- 消息体数据缓冲区
	*			iLength		-- 消息体数据长度
	* 返回值：	HR_OK / HR_IGNORE	-- 继续执行
	*			HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	virtual EnHandleResult OnWSMessageBody(T* pSender, CONNID dwConnID, const BYTE* pData, int iLength)			= 0;

	/*
	* 名称：WebSocket 数据包完成通知
	* 描述：当完整接收一个 WebSocket 数据包时，向监听器发送该通知
	*		
	* 参数：		pSender		-- 事件源对象
	*			dwConnID	-- 连接 ID
	* 返回值：	HR_OK / HR_IGNORE	-- 继续执行
	*			HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	virtual EnHandleResult OnWSMessageComplete(T* pSender, CONNID dwConnID)										= 0;

public:
	virtual ~IHttpListenerT() {}
};

/************************************************************************
名称：IHttpServer 组件端监听器接口
描述：定义 IHttpServer 监听器的所有事件
************************************************************************/
class IHttpServerListener : public IHttpListenerT<IHttpServer>, public ITcpServerListener
{
public:

};

/************************************************************************
名称：IHttpAgent 组件端监听器接口
描述：定义 IHttpAgent 监听器的所有事件
************************************************************************/
class IHttpAgentListener : public IHttpListenerT<IHttpAgent>, public ITcpAgentListener
{
public:

};

/************************************************************************
名称：IHttpClient 组件端监听器接口
描述：定义 IHttpClient 监听器的所有事件
************************************************************************/
class IHttpClientListener : public IHttpListenerT<IHttpClient>, public ITcpClientListener
{
public:

};

/************************************************************************
名称：IHttpServerListener 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
class CHttpServerListener : public IHttpServerListener
{
public:
	virtual EnHandleResult OnPrepareListen(ITcpServer* pSender, SOCKET soListen)										{return HR_IGNORE;}
	virtual EnHandleResult OnAccept(ITcpServer* pSender, CONNID dwConnID, UINT_PTR soClient)							{return HR_IGNORE;}
	virtual EnHandleResult OnHandShake(ITcpServer* pSender, CONNID dwConnID)											{return HR_IGNORE;}
	virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, int iLength)									{return HR_IGNORE;}
	virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)				{return HR_IGNORE;}
	virtual EnHandleResult OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)					{return HR_IGNORE;}
	virtual EnHandleResult OnShutdown(ITcpServer* pSender)																{return HR_IGNORE;}

	virtual EnHttpParseResult OnMessageBegin(IHttpServer* pSender, CONNID dwConnID)										{return HPR_OK;}
	virtual EnHttpParseResult OnRequestLine(IHttpServer* pSender, CONNID dwConnID, LPCSTR lpszMethod, LPCSTR lpszUrl)	{return HPR_OK;}
	virtual EnHttpParseResult OnStatusLine(IHttpServer* pSender, CONNID dwConnID, USHORT usStatusCode, LPCSTR lpszDesc)	{return HPR_OK;}
	virtual EnHttpParseResult OnHeader(IHttpServer* pSender, CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue)		{return HPR_OK;}
	virtual EnHttpParseResult OnChunkHeader(IHttpServer* pSender, CONNID dwConnID, int iLength)							{return HPR_OK;}
	virtual EnHttpParseResult OnChunkComplete(IHttpServer* pSender, CONNID dwConnID)									{return HPR_OK;}
	virtual EnHttpParseResult OnUpgrade(IHttpServer* pSender, CONNID dwConnID, EnHttpUpgradeType enUpgradeType)			{return HPR_OK;}

	virtual EnHandleResult OnWSMessageHeader(IHttpServer* pSender, CONNID dwConnID, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], ULONGLONG ullBodyLen)	{return HR_IGNORE;}
	virtual EnHandleResult OnWSMessageBody(IHttpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)		{return HR_IGNORE;}
	virtual EnHandleResult OnWSMessageComplete(IHttpServer* pSender, CONNID dwConnID)									{return HR_IGNORE;}
};

/************************************************************************
名称：IHttpAgentListener 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
class CHttpAgentListener : public IHttpAgentListener
{
public:
	virtual EnHandleResult OnPrepareConnect(ITcpAgent* pSender, CONNID dwConnID, SOCKET socket)							{return HR_IGNORE;}
	virtual EnHandleResult OnConnect(ITcpAgent* pSender, CONNID dwConnID)												{return HR_IGNORE;}
	virtual EnHandleResult OnHandShake(ITcpAgent* pSender, CONNID dwConnID)												{return HR_IGNORE;}
	virtual EnHandleResult OnReceive(ITcpAgent* pSender, CONNID dwConnID, int iLength)									{return HR_IGNORE;}
	virtual EnHandleResult OnReceive(ITcpAgent* pSender, CONNID dwConnID, const BYTE* pData, int iLength)				{return HR_IGNORE;}
	virtual EnHandleResult OnSend(ITcpAgent* pSender, CONNID dwConnID, const BYTE* pData, int iLength)					{return HR_IGNORE;}
	virtual EnHandleResult OnShutdown(ITcpAgent* pSender)																{return HR_IGNORE;}

	virtual EnHttpParseResult OnMessageBegin(IHttpAgent* pSender, CONNID dwConnID)										{return HPR_OK;}
	virtual EnHttpParseResult OnRequestLine(IHttpAgent* pSender, CONNID dwConnID, LPCSTR lpszMethod, LPCSTR lpszUrl)	{return HPR_OK;}
	virtual EnHttpParseResult OnStatusLine(IHttpAgent* pSender, CONNID dwConnID, USHORT usStatusCode, LPCSTR lpszDesc)	{return HPR_OK;}
	virtual EnHttpParseResult OnHeader(IHttpAgent* pSender, CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue)			{return HPR_OK;}
	virtual EnHttpParseResult OnChunkHeader(IHttpAgent* pSender, CONNID dwConnID, int iLength)							{return HPR_OK;}
	virtual EnHttpParseResult OnChunkComplete(IHttpAgent* pSender, CONNID dwConnID)										{return HPR_OK;}
	virtual EnHttpParseResult OnUpgrade(IHttpAgent* pSender, CONNID dwConnID, EnHttpUpgradeType enUpgradeType)			{return HPR_OK;}

	virtual EnHandleResult OnWSMessageHeader(IHttpAgent* pSender, CONNID dwConnID, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], ULONGLONG ullBodyLen)	{return HR_IGNORE;}
	virtual EnHandleResult OnWSMessageBody(IHttpAgent* pSender, CONNID dwConnID, const BYTE* pData, int iLength)		{return HR_IGNORE;}
	virtual EnHandleResult OnWSMessageComplete(IHttpAgent* pSender, CONNID dwConnID)									{return HR_IGNORE;}
};

/************************************************************************
名称：IHttpClientListener 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/

class CHttpClientListener : public IHttpClientListener
{
public:
	virtual EnHandleResult OnPrepareConnect(ITcpClient* pSender, CONNID dwConnID, SOCKET socket)						{return HR_IGNORE;}
	virtual EnHandleResult OnConnect(ITcpClient* pSender, CONNID dwConnID)												{return HR_IGNORE;}
	virtual EnHandleResult OnHandShake(ITcpClient* pSender, CONNID dwConnID)											{return HR_IGNORE;}
	virtual EnHandleResult OnReceive(ITcpClient* pSender, CONNID dwConnID, int iLength)									{return HR_IGNORE;}
	virtual EnHandleResult OnReceive(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)				{return HR_IGNORE;}
	virtual EnHandleResult OnSend(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)					{return HR_IGNORE;}

	virtual EnHttpParseResult OnMessageBegin(IHttpClient* pSender, CONNID dwConnID)										{return HPR_OK;}
	virtual EnHttpParseResult OnRequestLine(IHttpClient* pSender, CONNID dwConnID, LPCSTR lpszMethod, LPCSTR lpszUrl)	{return HPR_OK;}
	virtual EnHttpParseResult OnStatusLine(IHttpClient* pSender, CONNID dwConnID, USHORT usStatusCode, LPCSTR lpszDesc)	{return HPR_OK;}
	virtual EnHttpParseResult OnHeader(IHttpClient* pSender, CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue)		{return HPR_OK;}
	virtual EnHttpParseResult OnChunkHeader(IHttpClient* pSender, CONNID dwConnID, int iLength)							{return HPR_OK;}
	virtual EnHttpParseResult OnChunkComplete(IHttpClient* pSender, CONNID dwConnID)									{return HPR_OK;}
	virtual EnHttpParseResult OnUpgrade(IHttpClient* pSender, CONNID dwConnID, EnHttpUpgradeType enUpgradeType)			{return HPR_OK;}

	virtual EnHandleResult OnWSMessageHeader(IHttpClient* pSender, CONNID dwConnID, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], ULONGLONG ullBodyLen)	{return HR_IGNORE;}
	virtual EnHandleResult OnWSMessageBody(IHttpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)		{return HR_IGNORE;}
	virtual EnHandleResult OnWSMessageComplete(IHttpClient* pSender, CONNID dwConnID)									{return HR_IGNORE;}
};

/************************************************************************
名称：IHttpClientListener 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/

class CHttpSyncClientListener : public CHttpClientListener
{
public:
	virtual EnHandleResult OnClose(ITcpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)	{return HR_IGNORE;}

	virtual EnHttpParseResult OnHeadersComplete(IHttpClient* pSender, CONNID dwConnID)									{return HPR_OK;}
	virtual EnHttpParseResult OnBody(IHttpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)				{return HPR_OK;}
	virtual EnHttpParseResult OnMessageComplete(IHttpClient* pSender, CONNID dwConnID)									{return HPR_OK;}
	virtual EnHttpParseResult OnParseError(IHttpClient* pSender, CONNID dwConnID, int iErrorCode, LPCSTR lpszErrorDesc)	{return HPR_OK;}

};

#endif

/*****************************************************************************************************************************************************/
/************************************************************** Thread Pool Interfaces ***************************************************************/
/*****************************************************************************************************************************************************/

/************************************************************************
名称：线程池组件接口
描述：定义线程池组件的所有操作方法和属性访问方法
************************************************************************/
class IHPThreadPool
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*
	* 名称：启动线程池组件
	* 描述：
	*		
	* 参数：		dwThreadCount		-- 线程数量，（默认：0）
	*									>0 -> dwThreadCount
	*									=0 -> (CPU核数 * 2 + 2)
	*									<0 -> (CPU核数 * (-dwThreadCount))
	*			dwMaxQueueSize		-- 任务队列最大容量（默认：0，不限制）
	*			enRejectedPolicy	-- 任务拒绝处理策略
	*									TRP_CALL_FAIL（默认）	：立刻返回失败
	*									TRP_WAIT_FOR			：等待（直到成功、超时或线程池关闭等原因导致失败）
	*									TRP_CALLER_RUN			：调用者线程直接执行
	*			dwStackSize			-- 线程堆栈空间大小（默认：0 -> 操作系统默认）
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL Start	(DWORD dwThreadCount = 0, DWORD dwMaxQueueSize = 0, EnRejectedPolicy enRejectedPolicy = TRP_CALL_FAIL, DWORD dwStackSize = 0)	= 0;

	/*
	* 名称：关闭线程池组件
	* 描述：在规定时间内关闭线程池组件，如果工作线程在最大等待时间内未能正常关闭，会尝试强制关闭，这种情况下很可能会造成系统资源泄漏
	*		
	* 参数：		dwMaxWait	-- 最大等待时间（毫秒，默认：INFINITE，一直等待）
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL Stop	(DWORD dwMaxWait = INFINITE)										= 0;

	/*
	* 名称：提交任务
	* 描述：向线程池提交异步任务
	*		
	* 参数：		fnTaskProc	-- 任务处理函数
	*			pvArg		-- 任务参数
	*			dwMaxWait	-- 任务提交最大等待时间（仅对 TRP_WAIT_FOR 类型线程池生效，默认：INFINITE，一直等待）
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*							其中，错误码 ERROR_DESTINATION_ELEMENT_FULL 表示任务队列已满
	*/
	virtual BOOL Submit	(Fn_TaskProc fnTaskProc, PVOID pvArg, DWORD dwMaxWait = INFINITE)	= 0;

	/*
	* 名称：提交 Socket 任务
	* 描述：向线程池提交异步 Socket 任务
	*		
	* 参数：		pTask		-- 任务参数
	*			dwMaxWait	-- 任务提交最大等待时间（仅对 TRP_WAIT_FOR 类型线程池生效，默认：INFINITE，一直等待）
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*							其中，错误码 ERROR_DESTINATION_ELEMENT_FULL 表示任务队列已满
	*							注意：如果提交失败，需要手工调用 Destroy_HP_SocketTaskObj() 销毁 TSocketTask 对象
	*/
	virtual BOOL Submit	(LPTSocketTask pTask, DWORD dwMaxWait = INFINITE)					= 0;

	/*
	* 名称：调整线程池大小
	* 描述：增加或减少线程池的工作线程数量
	*		
	* 参数：		dwNewThreadCount	-- 线程数量
	*									>0 -> dwNewThreadCount
	*									=0 -> (CPU核数 * 2 + 2)
	*									<0 -> (CPU核数 * (-dwNewThreadCount))
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL AdjustThreadCount(DWORD dwNewThreadCount)									= 0;

	/*
	* 名称：等待
	* 描述：等待线程池组件停止运行
	*		
	* 参数：		dwMilliseconds	-- 超时时间（毫秒，默认：-1，永不超时）
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL Wait(DWORD dwMilliseconds = INFINITE)										= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 检查线程池组件是否已启动 */
	virtual BOOL HasStarted						()	= 0;
	/* 查看线程池组件当前状态 */
	virtual EnServiceState	GetState			()	= 0;
	/* 获取当前任务等待队列大小 */
	virtual DWORD GetQueueSize					()	= 0;
	/* 获取当前正在执行的任务数量 */
	virtual DWORD GetTaskCount					()	= 0;
	/* 获取工作线程数量 */
	virtual DWORD GetThreadCount				()	= 0;
	/* 获取任务队列最大容量 */
	virtual DWORD GetMaxQueueSize				()	= 0;
	/* 获取任务拒绝处理策略 */
	virtual EnRejectedPolicy GetRejectedPolicy	()	= 0;

public:
	virtual ~IHPThreadPool() {};
};

/************************************************************************
名称：线程池监听器接口
描述：定义线程池监听器的所有事件
************************************************************************/
class IHPThreadPoolListener
{
public:

	/*
	* 名称：线程池启动通知
	* 描述：线程池启动时监听器将收到该通知，监听器可以在通知处理方法中执行预处理工作
	*		
	* 参数：		pThreadPool		-- 线程池对象
	* 返回值：	无
	*/
	virtual void OnStartup(IHPThreadPool* pThreadPool)								= 0;

	/*
	* 名称：线程池启动关闭通知
	* 描述：线程池关闭时监听器将收到该通知，监听器可以在通知处理方法中执行后处理工作
	*		
	* 参数：		pThreadPool		-- 线程池对象
	* 返回值：	无
	*/
	virtual void OnShutdown(IHPThreadPool* pThreadPool)								= 0;

	/*
	* 名称：工作线程启动通知
	* 描述：工作线程启动时监听器将收到该通知，监听器可以在通知处理方法中执行线程级别预处理工作
	*		
	* 参数：		pThreadPool		-- 线程池对象
	*			dwThreadID		-- 工作线程 ID
	* 返回值：	无
	*/
	virtual void OnWorkerThreadStart(IHPThreadPool* pThreadPool, THR_ID dwThreadID)	= 0;

	/*
	* 名称：工作线程退出通知
	* 描述：工作线程退出时监听器将收到该通知，监听器可以在通知处理方法中执行线程级别后处理工作
	*		
	* 参数：		pThreadPool		-- 线程池对象
	*			dwThreadID		-- 工作线程 ID
	* 返回值：	无
	*/
	virtual void OnWorkerThreadEnd(IHPThreadPool* pThreadPool, THR_ID dwThreadID)	= 0;

public:
	virtual ~IHPThreadPoolListener() {};
};

/************************************************************************
名称：线程池监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
class CHPThreadPoolListener : public IHPThreadPoolListener
{
public:
	virtual void OnStartup(IHPThreadPool* pThreadPool)								{}
	virtual void OnShutdown(IHPThreadPool* pThreadPool)								{}
	virtual void OnWorkerThreadStart(IHPThreadPool* pThreadPool, THR_ID dwThreadID)	{}
	virtual void OnWorkerThreadEnd(IHPThreadPool* pThreadPool, THR_ID dwThreadID)	{}
};

/************************************************************************
名称：压缩器接口
描述：定义压缩器的所有操作方法和属性访问方法
************************************************************************/
class IHPCompressor
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*
	* 名称：执行压缩
	* 描述：可循环调用以压缩流式或分段数据
	*		
	* 参数：		pData		-- 待压缩数据缓冲区
	*			iLength		-- 待压缩数据长度
	*			bLast		-- 是否最后一段待压缩数据
	*			pContext	-- 压缩回调函数 Fn_CompressDataCallback 的上下文参数
	*
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL Process(const BYTE* pData, int iLength, BOOL bLast, PVOID pContext = nullptr)	= 0;

	/*
	* 名称：执行压缩
	* 描述：可循环调用以压缩流式或分段数据
	*		
	* 参数：		pData		-- 待压缩数据缓冲区
	*			iLength		-- 待压缩数据长度
	*			bLast		-- 是否最后一段待压缩数据
	*			bFlush		-- 是否强制刷新（强制刷新会降低压缩效率，但可对数据进行分段压缩）
	*			pContext	-- 压缩回调函数 Fn_CompressDataCallback 的上下文参数
	*
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL ProcessEx(const BYTE* pData, int iLength, BOOL bLast, BOOL bFlush = FALSE, PVOID pContext = nullptr)	= 0;

	/* 重置压缩器 */
	virtual BOOL Reset()																		= 0;

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 检测压缩器是否可用 */
	virtual BOOL IsValid()																		= 0;

public:
	virtual ~IHPCompressor() {};
};

/************************************************************************
名称：解压器接口
描述：定义解压器的所有操作方法和属性访问方法
************************************************************************/
class IHPDecompressor
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*
	* 名称：执行解压
	* 描述：可循环调用以解压流式或分段数据
	*		
	* 参数：		pData		-- 待解压数据缓冲区
	*			iLength		-- 待解压数据长度
	*			pContext	-- 解压回调函数 Fn_DecompressDataCallback 的上下文参数
	*
	* 返回值：	TRUE	-- 成功
	*			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL Process(const BYTE* pData, int iLength, PVOID pContext = nullptr)	= 0;

	/* 重置解压器 */
	virtual BOOL Reset()															= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 检测解压器是否可用 */
	virtual BOOL IsValid()															= 0;

public:
	virtual ~IHPDecompressor() {};
};


/* ========================================================================== */
/*  InternalDef.h  -- internal constants
/*  source: Windows\Src\InternalDef.h
/* ========================================================================== */

#pragma once

/* [amalgamated] #include "../Include/HPSocket/HPTypeDef.h" */

/************************************************************************
名称：全局常量
描述：声明组件的公共全局常量
************************************************************************/

/* IOCP Socket 缓冲区最小值 */
#define MIN_SOCKET_BUFFER_SIZE					88
/* 小文件最大字节数 */
#define MAX_SMALL_FILE_SIZE						0x3FFFFF
/* 最大连接时长 */
#define MAX_CONNECTION_PERIOD					(MAXLONG / 2)
/* IOCP 处理接收事件时最大额外读取次数 */
#define MAX_IOCP_CONTINUE_RECEIVE				100

/* Server/Agent 最大连接数 */
#define MAX_CONNECTION_COUNT					(5 * 1000 * 1000)
/* Server/Agent 默认最大连接数 */
#define DEFAULT_CONNECTION_COUNT				10000
/* Server/Agent 默认 Socket 对象缓存锁定时间 */
#define DEFAULT_FREE_SOCKETOBJ_LOCK_TIME		DEFAULT_OBJECT_CACHE_LOCK_TIME
/* Server/Agent 默认 Socket 缓存池大小 */
#define DEFAULT_FREE_SOCKETOBJ_POOL				DEFAULT_OBJECT_CACHE_POOL_SIZE
/* Server/Agent 默认 Socket 缓存池回收阀值 */
#define DEFAULT_FREE_SOCKETOBJ_HOLD				DEFAULT_OBJECT_CACHE_POOL_HOLD
/* Server/Agent 默认内存块缓存池大小 */
#define DEFAULT_FREE_BUFFEROBJ_POOL				DEFAULT_BUFFER_CACHE_POOL_SIZE
/* Server/Agent 默认内存块缓存池回收阀值 */
#define DEFAULT_FREE_BUFFEROBJ_HOLD				DEFAULT_BUFFER_CACHE_POOL_HOLD
/* Client 默认内存块缓存池大小 */
#define DEFAULT_CLIENT_FREE_BUFFER_POOL_SIZE	60
/* Client 默认内存块缓存池回收阀值 */
#define DEFAULT_CLIENT_FREE_BUFFER_POOL_HOLD	60
/* Client/Agent 默认同步连接超时时间 */
#define DEFAULT_SYNC_CONNECT_TIMEOUT			10000
/* IPv4 默认绑定地址 */
#define  DEFAULT_IPV4_BIND_ADDRESS				_T("0.0.0.0")
/* IPv6 默认绑定地址 */
#define  DEFAULT_IPV6_BIND_ADDRESS				_T("::")
/* IPv4 广播地址 */
#define DEFAULT_IPV4_BROAD_CAST_ADDRESS			_T("255.255.255.255")

/* SOCKET 默认发送缓冲区大小 */
#define DEFAULT_SOCKET_SNDBUFF_SIZE				(16 * 1024)

/* TCP 默认通信数据缓冲区大小 */
#define DEFAULT_TCP_SOCKET_BUFFER_SIZE			DEFAULT_BUFFER_CACHE_CAPACITY
/* TCP 默认心跳包间隔 */
#define DEFALUT_TCP_KEEPALIVE_TIME				(60 * 1000)
/* TCP 默认心跳确认包检测间隔 */
#define DEFALUT_TCP_KEEPALIVE_INTERVAL			(20 * 1000)
/* TCP Server 默认 Listen 队列大小 */
#define DEFAULT_TCP_SERVER_SOCKET_LISTEN_QUEUE	SOMAXCONN
/* TCP Server 默认预投递 Accept 数量 */
#define DEFAULT_TCP_SERVER_ACCEPT_SOCKET_COUNT	300

/* UDP 最大数据报文最大长度 */
#define MAXIMUM_UDP_MAX_DATAGRAM_SIZE			(16 * DEFAULT_BUFFER_CACHE_CAPACITY)
/* UDP 默认数据报文最大长度 */
#define DEFAULT_UDP_MAX_DATAGRAM_SIZE			1432
/* UDP 默认 Receive 预投递数量 */
#define DEFAULT_UDP_POST_RECEIVE_COUNT			300
/* UDP 默认监测包尝试次数 */
#define DEFAULT_UDP_DETECT_ATTEMPTS				3
/* UDP 默认监测包发送间隔 */
#define DEFAULT_UDP_DETECT_INTERVAL				(60 * 1000)

/* TCP Pack 包长度位数 */
#define TCP_PACK_LENGTH_BITS					22
/* TCP Pack 包长度掩码 */
#define TCP_PACK_LENGTH_MASK					0x3FFFFF
/* TCP Pack 包最大长度硬限制 */
#define TCP_PACK_MAX_SIZE_LIMIT					0x3FFFFF
/* TCP Pack 包默认最大长度 */
#define TCP_PACK_DEFAULT_MAX_SIZE				0x040000
/* TCP Pack 包头标识值硬限制 */
#define TCP_PACK_HEADER_FLAG_LIMIT				0x0003FF
/* TCP Pack 包头默认标识值 */
#define TCP_PACK_DEFAULT_HEADER_FLAG			0x000000

/* 默认压缩/解压数据缓冲器长度 */
#define DEFAULT_COMPRESS_BUFFER_SIZE			(16 * 1024)

/* 垃圾回收检查间隔（毫秒） */
#define GC_CHECK_INTERVAL						(15 * 1000)

#define HOST_SEPARATOR_CHAR						'^'
#define PORT_SEPARATOR_CHAR						':'
#define IPV6_ADDR_BEGIN_CHAR					'['
#define IPV6_ADDR_END_CHAR						']'
#define IPV4_ADDR_SEPARATOR_CHAR				'.'
#define IPV6_ADDR_SEPARATOR_CHAR				':'
#define IPV6_ZONE_INDEX_CHAR					'%'

#define ENSURE_STOP()							{if(GetState() != SS_STOPPED) {Stop();} Wait();}
#define ENSURE_HAS_STOPPED()					{ASSERT(GetState() == SS_STOPPED); if(GetState() != SS_STOPPED) return;}


/* ========================================================================== */
/*  SocketHelper.h  -- socket infrastructure
/*  source: Windows\Src\SocketHelper.h
/* ========================================================================== */

#pragma once

#include <ws2tcpip.h>
#include <mswsock.h>
#include <malloc.h>

#include <atlfile.h>

/* [amalgamated] #include "../Include/HPSocket/SocketInterface.h" */
/* [amalgamated] #include "Common/WaitFor.h" */
/* [amalgamated] #include "Common/SysHelper.h" */
/* [amalgamated] #include "Common/FuncHelper.h" */
/* [amalgamated] #include "Common/BufferPool.h" */
/* [amalgamated] #include "Common/RingBuffer.h" */
/* [amalgamated] #include "InternalDef.h" */

#ifdef _ZLIB_SUPPORT
#include <zutil.h>
#endif

#ifdef _BROTLI_SUPPORT
#pragma warning(push)
#pragma warning(disable: 4005)
#include <brotli/decode.h>
#include <brotli/encode.h>
#pragma warning(pop)
#endif

/************************************************************************
名称：Windows Socket 组件初始化类
描述：自动加载和卸载 Windows Socket 组件
************************************************************************/
class CInitSocket
{
public:
	CInitSocket(LPWSADATA lpWSAData = nullptr, BYTE minorVersion = 2, BYTE majorVersion = 2)
	{
		LPWSADATA lpTemp = lpWSAData;

		if(!lpTemp)
			lpTemp	= CreateLocalObject(WSADATA);

		m_iResult	= ::WSAStartup(MAKEWORD(majorVersion, minorVersion), lpTemp);
	}

	~CInitSocket()
	{
		if(IsValid())
			::WSACleanup();
	}

	int	 GetResult() const {return m_iResult;}
	BOOL IsValid()	 const {return m_iResult == 0;}

private:
	int m_iResult;
};

typedef struct hp_addr
{
	ADDRESS_FAMILY family;

	union
	{
		ULONG_PTR	addr;
		IN_ADDR		addr4;
		IN6_ADDR	addr6;
	};

	static const hp_addr ANY_ADDR4;
	static const hp_addr ANY_ADDR6;

	inline int AddrSize() const
	{
		return AddrSize(family);
	}

	inline static int AddrSize(ADDRESS_FAMILY f)
	{
		if(f == AF_INET)
			return sizeof(IN_ADDR);

		return sizeof(IN6_ADDR);
	}

	inline static const hp_addr& AnyAddr(ADDRESS_FAMILY f)
	{
		if(f == AF_INET)
			return ANY_ADDR4;

		return ANY_ADDR6;
	}

	inline const ULONG_PTR* Addr()	const	{return &addr;}
	inline ULONG_PTR* Addr()				{return &addr;}

	inline BOOL IsIPv4()			const	{return family == AF_INET;}
	inline BOOL IsIPv6()			const	{return family == AF_INET6;}
	inline BOOL IsSpecified()		const	{return IsIPv4() || IsIPv6();}
	inline void ZeroAddr()					{::ZeroMemory(&addr6, sizeof(addr6));}
	inline void Reset()						{::ZeroMemory(this, sizeof(*this));}

	inline hp_addr& Copy(hp_addr& other) const
	{
		if(this != &other)
			memcpy(&other, this, offsetof(hp_addr, addr) + AddrSize());

		return other;
	}

	hp_addr(ADDRESS_FAMILY f = AF_UNSPEC, BOOL bZeroAddr = FALSE)
	{
		family = f;

		if(bZeroAddr) ZeroAddr();
	}

} HP_ADDR, *HP_PADDR;

typedef struct hp_sockaddr
{
	union
	{
		ADDRESS_FAMILY	family;
		SOCKADDR		addr;
		SOCKADDR_IN		addr4;
		SOCKADDR_IN6	addr6;
	};

	inline int AddrSize() const
	{
		return AddrSize(family);
	}

	inline static int AddrSize(ADDRESS_FAMILY f)
	{
		if(f == AF_INET)
			return sizeof(SOCKADDR_IN);

		return sizeof(SOCKADDR_IN6);
	}

	inline int EffectAddrSize() const
	{
		return EffectAddrSize(family);
	}

	inline static int EffectAddrSize(ADDRESS_FAMILY f)
	{
		return (f == AF_INET) ? offsetof(SOCKADDR_IN, sin_zero) : sizeof(SOCKADDR_IN6);
	}

	inline static const hp_sockaddr& AnyAddr(ADDRESS_FAMILY f)
	{
		static const hp_sockaddr s_any_addr4(AF_INET, TRUE);
		static const hp_sockaddr s_any_addr6(AF_INET6, TRUE);

		if(f == AF_INET)
			return s_any_addr4;

		return s_any_addr6;
	}

	inline static int AddrMinStrLength(ADDRESS_FAMILY f)
	{
		if(f == AF_INET)
			return INET_ADDRSTRLEN;

		return INET6_ADDRSTRLEN;
	}

	inline BOOL IsIPv4()			const	{return family == AF_INET;}
	inline BOOL IsIPv6()			const	{return family == AF_INET6;}
	inline BOOL IsSpecified()		const	{return IsIPv4() || IsIPv6();}
	inline USHORT Port()			const	{return ntohs(addr4.sin_port);}
	inline void SetPort(USHORT usPort)		{addr4.sin_port = htons(usPort);}
	inline void* SinAddr()			const	{return IsIPv4() ? (void*)&addr4.sin_addr : (void*)&addr6.sin6_addr;}
	inline void* SinAddr()					{return IsIPv4() ? (void*)&addr4.sin_addr : (void*)&addr6.sin6_addr;}

	inline const SOCKADDR* Addr()	const	{return &addr;}
	inline SOCKADDR* Addr()					{return &addr;}
	inline void ZeroAddr()					{::ZeroMemory(((char*)this) + sizeof(family), sizeof(*this) - sizeof(family));}
	inline void Reset()						{::ZeroMemory(this, sizeof(*this));}

	inline hp_sockaddr& Copy(hp_sockaddr& other) const
	{
		if(this != &other)
			memcpy(&other, this, AddrSize());

		return other;
	}

	size_t Hash() const
	{
		ASSERT(IsSpecified());

		size_t _Val		  = 2166136261U;
		const int size	  = EffectAddrSize();
		const BYTE* pAddr = (const BYTE*)Addr();

		for(int i = 0; i < size; i++)
			_Val = 16777619U * _Val ^ (size_t)pAddr[i];

		return (_Val);
	}

	bool EqualTo(const hp_sockaddr& other) const
	{
		ASSERT(IsSpecified() && other.IsSpecified());

		return EqualMemory(this, &other, EffectAddrSize());
	}

	hp_sockaddr(ADDRESS_FAMILY f = AF_UNSPEC, BOOL bZeroAddr = FALSE)
	{
		family = f;

		if(bZeroAddr) ZeroAddr();
	}

} HP_SOCKADDR, *HP_PSOCKADDR;

typedef struct hp_scope_host
{
	LPCTSTR addr;
	LPCTSTR name;

	BOOL bNeedFree;

	hp_scope_host(LPCTSTR lpszOriginAddress)
	{
		ASSERT(lpszOriginAddress != nullptr);

		LPCTSTR lpszFind = ::StrChr(lpszOriginAddress, HOST_SEPARATOR_CHAR);

		if(lpszFind == nullptr)
		{
			addr		= lpszOriginAddress;
			name		= lpszOriginAddress;
			bNeedFree	= FALSE;
		}
		else
		{
			int i			= (int)(lpszFind - lpszOriginAddress);
			int iSize		= (int)lstrlen(lpszOriginAddress) + 1;
			LPTSTR lpszCopy	= new TCHAR[iSize];

			::memcpy((PVOID)lpszCopy, (PVOID)lpszOriginAddress, iSize * sizeof(TCHAR));

			lpszCopy[i]	= 0;
			addr		= lpszCopy;
			name		= lpszCopy + i + 1;
			bNeedFree	= TRUE;

			if(::IsStrEmpty(name))
				name = addr;
		}
	}

	~hp_scope_host()
	{
		if(bNeedFree)
			delete[] addr;
	}

} HP_SCOPE_HOST, *HP_PSCOPE_HOST;

/* Server 组件和 Agent 组件内部使用的事件处理结果常量 */

// 连接已关闭
#define HR_CLOSED	0xFF

/* 关闭连接标识 */
enum EnSocketCloseFlag
{
	SCF_NONE		= 0,	// 不触发事件
	SCF_CLOSE		= 1,	// 触发 正常关闭 OnClose 事件
	SCF_ERROR		= 2		// 触发 异常关闭 OnClose 事件
};

/* 数据缓冲区基础结构 */
template<class T> struct TBufferObjBase
{
	WSAOVERLAPPED		ov;
	CPrivateHeap&		heap;

	EnSocketOperation	operation;
	WSABUF				buff;

	int					capacity;
	volatile LONG		sndCounter;

	T* next;
	T* last;

	static T* Construct(CPrivateHeap& heap, DWORD dwCapacity)
	{
		T* pBufferObj = (T*)heap.Alloc(sizeof(T) + dwCapacity);
		ASSERT(pBufferObj);

		pBufferObj->TBufferObjBase::TBufferObjBase(heap, dwCapacity);
		pBufferObj->buff.buf = ((char*)pBufferObj) + sizeof(T);

		return pBufferObj;
	}

	static void Destruct(T* pBufferObj)
	{
		ASSERT(pBufferObj);
		pBufferObj->heap.Free(pBufferObj);
	}

	void ResetSendCounter()
	{
		sndCounter = 2;
	}

	LONG ReleaseSendCounter()
	{
		return ::InterlockedDecrement(&sndCounter);
	}

	TBufferObjBase(CPrivateHeap& hp, DWORD dwCapacity)
	: heap(hp)
	, capacity((int)dwCapacity)
	{
		ASSERT(capacity > 0);
	}

	int Cat(const BYTE* pData, int length)
	{
		ASSERT(pData != nullptr && length >= 0);

		int cat = min(Remain(), length);

		if(cat > 0)
		{
			memcpy(buff.buf + buff.len, pData, cat);
			buff.len += cat;
		}

		return cat;
	}

	void ResetOV()	{::ZeroMemory(&ov, sizeof(ov));}
	void Reset()	{ResetOV(); buff.len = 0;}
	int Remain()	{return capacity - buff.len;}
	BOOL IsFull()	{return Remain() == 0;}
};

/* 数据缓冲区结构 */
struct TBufferObj : public TBufferObjBase<TBufferObj>
{
	SOCKET client;
};

/* UDP 数据缓冲区结构 */
struct TUdpBufferObj : public TBufferObjBase<TUdpBufferObj>
{
	HP_SOCKADDR	remoteAddr;
	int			addrLen;
};

/* 数据缓冲区链表模板 */
template<class T> struct TBufferObjListT : public TSimpleList<T>
{
public:
	int Cat(const BYTE* pData, int length)
	{
		ASSERT(pData != nullptr && length >= 0);

		int remain = length;

		while(remain > 0)
		{
			T* pItem = Back();

			if(pItem == nullptr || pItem->IsFull())
				pItem = PushBack(bfPool.PickFreeItem());

			int cat  = pItem->Cat(pData, remain);

			pData	+= cat;
			remain	-= cat;
		}

		return length;
	}

	T* PushTail(const BYTE* pData, int length)
	{
		ASSERT(pData != nullptr && length >= 0 && length <= (int)bfPool.GetItemCapacity());

		T* pItem = PushBack(bfPool.PickFreeItem());
		pItem->Cat(pData, length);

		return pItem;
	}

	void Release()
	{
		bfPool.PutFreeItem(*this);
	}

public:
	TBufferObjListT(CNodePoolT<T>& pool) : bfPool(pool)
	{
	}

private:
	CNodePoolT<T>& bfPool;
};

/* 数据缓冲区对象池 */
typedef CNodePoolT<TBufferObj>			CBufferObjPool;
/* UDP 数据缓冲区对象池 */
typedef CNodePoolT<TUdpBufferObj>		CUdpBufferObjPool;
/* 数据缓冲区链表模板 */
typedef TBufferObjListT<TBufferObj>		TBufferObjList;
/* UDP 数据缓冲区链表模板 */
typedef TBufferObjListT<TUdpBufferObj>	TUdpBufferObjList;

/* TBufferObj 智能指针 */
typedef TItemPtrT<TBufferObj>			TBufferObjPtr;
/* TUdpBufferObj 智能指针 */
typedef TItemPtrT<TUdpBufferObj>		TUdpBufferObjPtr;

/* Socket 缓冲区基础结构 */
struct TSocketObjBase : public CSafeCounter
{
	CPrivateHeap& heap;

	CONNID		connID;
	HP_SOCKADDR	remoteAddr;
	PVOID		extra;
	PVOID		reserved;
	PVOID		reserved2;

	union
	{
		DWORD	freeTime;
		DWORD	connTime;
	};

	DWORD		activeTime;

	volatile BOOL	valid;
	volatile BOOL	smooth;
	volatile long	pending;
	volatile long	sndCount;

	volatile BOOL	connected;
	volatile BOOL	paused;
	volatile BOOL	recving;

	TSocketObjBase(CPrivateHeap& hp) : heap(hp) {}

	static BOOL IsExist(TSocketObjBase* pSocketObj)
		{return pSocketObj != nullptr;}

	static BOOL IsValid(TSocketObjBase* pSocketObj)
		{return (IsExist(pSocketObj) && pSocketObj->valid == TRUE);}

	static void Invalid(TSocketObjBase* pSocketObj)
		{ASSERT(IsExist(pSocketObj)); pSocketObj->valid = FALSE;}

	static void Release(TSocketObjBase* pSocketObj)
	{
		ASSERT(IsExist(pSocketObj));

		pSocketObj->freeTime = ::TimeGetTime();
		pSocketObj->Decrement();
	}

	DWORD GetConnTime	()	const	{return connTime;}
	DWORD GetFreeTime	()	const	{return freeTime;}
	DWORD GetActiveTime	()	const	{return activeTime;}
	BOOL IsPaused		()	const	{return paused;}

	long Pending()		{return pending;}
	BOOL IsPending()	{return pending > 0;}
	BOOL IsSmooth()		{return smooth;}
	void TurnOnSmooth()	{smooth = TRUE;}

	BOOL TurnOffSmooth()
		{return ::InterlockedCompareExchange((volatile long*)&smooth, FALSE, TRUE) == TRUE;}
	
	BOOL HasConnected()							{return connected;}
	void SetConnected(BOOL bConnected = TRUE)	{connected = bConnected;}

	void Reset(CONNID dwConnID)
	{
		ResetCount(1);

		connID		= dwConnID;
		connected	= FALSE;
		valid		= TRUE;
		smooth		= TRUE;
		paused		= FALSE;
		recving		= FALSE;
		pending		= 0;
		sndCount	= 0;
		extra		= nullptr;
		reserved	= nullptr;
		reserved2	= nullptr;
	}
};

/* 数据缓冲区结构 */
struct TSocketObj : public TSocketObjBase
{
	CCriSec			csRecv;
	CCriSec			csSend;
	CSpinGuard		sgPause;

	SOCKET			socket;
	CStringA		host;
	TBufferObjList	sndBuff;

	BOOL IsCanSend() {return sndCount <= GetSendBufferSize();}

	long GetSendBufferSize()
	{
		long lSize;
		int len	= (int)(sizeof(lSize));
		int rs	= getsockopt(socket, SOL_SOCKET, SO_SNDBUF, (CHAR*)&lSize, &len);

		if(rs == SOCKET_ERROR || lSize <= 0)
			lSize = DEFAULT_SOCKET_SNDBUFF_SIZE;

		return lSize;
	}

	static TSocketObj* Construct(CPrivateHeap& hp, CBufferObjPool& bfPool)
	{
		TSocketObj* pSocketObj = (TSocketObj*)hp.Alloc(sizeof(TSocketObj));
		ASSERT(pSocketObj);

		pSocketObj->TSocketObj::TSocketObj(hp, bfPool);

		return pSocketObj;
	}

	static void Destruct(TSocketObj* pSocketObj)
	{
		ASSERT(pSocketObj);

		CPrivateHeap& heap = pSocketObj->heap;
		pSocketObj->TSocketObj::~TSocketObj();
		heap.Free(pSocketObj);
	}
	
	TSocketObj(CPrivateHeap& hp, CBufferObjPool& bfPool)
	: TSocketObjBase(hp), sndBuff(bfPool)
	{

	}

	static BOOL InvalidSocketObj(TSocketObj* pSocketObj)
	{
		BOOL bDone = FALSE;

		if(TSocketObj::IsValid(pSocketObj))
		{
			pSocketObj->SetConnected(FALSE);

			CCriSecLock locallock(pSocketObj->csRecv);
			CCriSecLock locallock2(pSocketObj->csSend);

			if(TSocketObjBase::IsValid(pSocketObj))
			{
				TSocketObjBase::Invalid(pSocketObj);
				bDone = TRUE;
			}
		}

		return bDone;
	}

	static void Release(TSocketObj* pSocketObj)
	{
		__super::Release(pSocketObj);

		pSocketObj->sndBuff.Release();
	}

	void Reset(CONNID dwConnID, SOCKET soClient)
	{
		__super::Reset(dwConnID);
		
		host.Empty();

		socket = soClient;
	}

	BOOL GetRemoteHost(LPCSTR* lpszHost, USHORT* pusPort = nullptr)
	{
		*lpszHost = host;

		if(pusPort)
			*pusPort = remoteAddr.Port();

		return (*lpszHost != nullptr && (*lpszHost)[0] != 0);
	}
};

/* UDP 数据缓冲区结构 */
struct TUdpSocketObj : public TSocketObjBase
{
	PVOID				pHolder;
	HANDLE				hTimer;

	CRWLock				csRecv;
	CCriSec				csSend;

	TUdpBufferObjList	sndBuff;
	volatile DWORD		detectFails;

	BOOL IsCanSend			() {return sndCount <= GetSendBufferSize();}
	long GetSendBufferSize	() {return (4 * DEFAULT_SOCKET_SNDBUFF_SIZE);}

	static TUdpSocketObj* Construct(CPrivateHeap& hp, CUdpBufferObjPool& bfPool)
	{
		TUdpSocketObj* pSocketObj = (TUdpSocketObj*)hp.Alloc(sizeof(TUdpSocketObj));
		ASSERT(pSocketObj);

		pSocketObj->TUdpSocketObj::TUdpSocketObj(hp, bfPool);

		return pSocketObj;
	}

	static void Destruct(TUdpSocketObj* pSocketObj)
	{
		ASSERT(pSocketObj);

		CPrivateHeap& heap = pSocketObj->heap;
		pSocketObj->TUdpSocketObj::~TUdpSocketObj();
		heap.Free(pSocketObj);
	}
	
	TUdpSocketObj(CPrivateHeap& hp, CUdpBufferObjPool& bfPool)
	: TSocketObjBase(hp), sndBuff(bfPool)
	{

	}

	static BOOL InvalidSocketObj(TUdpSocketObj* pSocketObj)
	{
		BOOL bDone = FALSE;

		if(TUdpSocketObj::IsValid(pSocketObj))
		{
			pSocketObj->SetConnected(FALSE);

			CReentrantWriteLock	locallock(pSocketObj->csRecv);
			CCriSecLock			locallock2(pSocketObj->csSend);

			if(TSocketObjBase::IsValid(pSocketObj))
			{
				TSocketObjBase::Invalid(pSocketObj);
				bDone = TRUE;
			}
		}

		return bDone;
	}

	static void Release(TUdpSocketObj* pSocketObj)
	{
		__super::Release(pSocketObj);

		pSocketObj->sndBuff.Release();
	}

	void Reset(CONNID dwConnID)
	{
		__super::Reset(dwConnID);

		pHolder		= nullptr;
		hTimer		= nullptr;
		detectFails	= 0;
	}
};

/* 虚拟 Timer Queue */
class _CFakeTimerQueue
{
public:
	_CFakeTimerQueue()
	{

	}

	~_CFakeTimerQueue()
	{

	}

	HANDLE CreateTimer(WAITORTIMERCALLBACK fnCallback, PVOID lpParam, DWORD dwPeriod, DWORD dwDueTime = INFINITE, ULONG ulFlags = WT_EXECUTEDEFAULT)
	{
		return INVALID_HANDLE_VALUE;
	}

	BOOL ChangeTimer(HANDLE hTimer, DWORD dwPeriod, DWORD dwDueTime = INFINITE)
	{
		return TRUE;
	}

	BOOL DeleteTimer(HANDLE hTimer, HANDLE hCompletionEvent = INVALID_HANDLE_VALUE)
	{
		return TRUE;
	}

	BOOL Reset()
	{
		return TRUE;
	}

	BOOL IsValid()					{ return TRUE; }

	HANDLE GetHandle()				{ return INVALID_HANDLE_VALUE; }
	const HANDLE GetHandle() const	{ return INVALID_HANDLE_VALUE; }

	operator HANDLE()				{ return INVALID_HANDLE_VALUE; }
	operator const HANDLE() const	{ return INVALID_HANDLE_VALUE; }

private:
	_CFakeTimerQueue(const _CFakeTimerQueue&);
	_CFakeTimerQueue operator = (const _CFakeTimerQueue&);
};

/* 垃圾回收 Timer Queue */
#ifdef USE_EXTERNAL_GC
typedef CTimerQueue			CGCTimerQueue;
#else
typedef _CFakeTimerQueue	CGCTimerQueue;
#endif


/* 有效 TSocketObj 缓存 */
typedef CRingCache2<TSocketObj, CONNID, true>		TSocketObjPtrPool;
/* 失效 TSocketObj 缓存 */
typedef CRingPool<TSocketObj>						TSocketObjPtrList;
/* 失效 TSocketObj 垃圾回收结构链表 */
typedef CCASQueue<TSocketObj>						TSocketObjPtrQueue;

/* 有效 TUdpSocketObj 缓存 */
typedef CRingCache2<TUdpSocketObj, CONNID, true>	TUdpSocketObjPtrPool;
/* 失效 TUdpSocketObj 缓存 */
typedef CRingPool<TUdpSocketObj>					TUdpSocketObjPtrList;
/* 失效 TUdpSocketObj 垃圾回收结构链表 */
typedef CCASQueue<TUdpSocketObj>					TUdpSocketObjPtrQueue;

/* HP_SOCKADDR 比较器 */
struct hp_sockaddr_func
{
	struct hash
	{
		size_t operator() (const HP_SOCKADDR* pA) const
		{
			return pA->Hash();
		}
	};

	struct equal_to
	{
		bool operator () (const HP_SOCKADDR* pA, const HP_SOCKADDR* pB) const
		{
			return pA->EqualTo(*pB);
		}
	};

};

/* 地址-连接 ID 哈希表 */
typedef unordered_map<const HP_SOCKADDR*, CONNID, hp_sockaddr_func::hash, hp_sockaddr_func::equal_to>
										TSockAddrMap;
/* 地址-连接 ID 哈希表迭代器 */
typedef TSockAddrMap::iterator			TSockAddrMapI;
/* 地址-连接 ID 哈希表 const 迭代器 */
typedef TSockAddrMap::const_iterator	TSockAddrMapCI;

/* IClient 组件关闭上下文 */
struct TClientCloseContext
{
	BOOL bFireOnClose;
	EnSocketOperation enOperation;
	int iErrorCode;
	BOOL bNotify;

	TClientCloseContext(BOOL bFire = TRUE, EnSocketOperation enOp = SO_CLOSE, int iCode = SE_OK, BOOL bNtf = TRUE)
	{
		Reset(bFire, enOp, iCode, bNtf);
	}

	void Reset(BOOL bFire = TRUE, EnSocketOperation enOp = SO_CLOSE, int iCode = SE_OK, BOOL bNtf = TRUE)
	{
		bFireOnClose = bFire;
		enOperation	 = enOp;
		iErrorCode	 = iCode;
		bNotify		 = bNtf;
	}

};

/*****************************************************************************************************/
/******************************************** 公共帮助方法 ********************************************/
/*****************************************************************************************************/

/* 默认工作线程前缀 */
#define DEFAULT_WORKER_THREAD_PREFIX	_T("hp-worker-")

/* 设置当前工作线程名称 */
BOOL SetCurrentWorkerThreadName();
/* 设置工作线程默认名称 */
BOOL SetWorkerThreadDefaultName(HANDLE hThread);

/* 获取错误描述文本 */
LPCTSTR GetSocketErrorDesc(EnSocketError enCode);
/* 确定地址簇 */
ADDRESS_FAMILY DetermineAddrFamily(LPCTSTR lpszAddress);
/* 地址字符串地址转换为 HP_ADDR */
BOOL GetInAddr(LPCTSTR lpszAddress, __out HP_ADDR& addr);
/* 地址字符串地址转换为 HP_SOCKADDR */
BOOL GetSockAddr(LPCTSTR lpszAddress, USHORT usPort, __inout HP_SOCKADDR& addr);
/* 检查字符串是否符合 IP 地址格式 */
BOOL IsIPAddress(LPCTSTR lpszAddress, __out EnIPAddrType* penType = nullptr);
/* 通过主机名获取 IP 地址 */
BOOL GetIPAddress(LPCTSTR lpszHost, __out LPTSTR lpszIP, __inout int& iIPLenth, __out EnIPAddrType& enType);
/* 通过主机名获取 HP_SOCKADDR */
BOOL GetSockAddrByHostName(LPCTSTR lpszHost, USHORT usPort, __out HP_SOCKADDR& addr, ADDRESS_FAMILY af = AF_UNSPEC);
/* 通过主机名获取 HP_SOCKADDR */
BOOL GetSockAddrByHostNameDirectly(LPCTSTR lpszHost, USHORT usPort, HP_SOCKADDR &addr);
/* 枚举主机 IP 地址 */
BOOL EnumHostIPAddresses(LPCTSTR lpszHost, EnIPAddrType enType, __out LPTIPAddr** lpppIPAddr, __out int& iIPAddrCount);
/* 填充 LPTIPAddr* */
BOOL RetrieveSockAddrIPAddresses(const vector<HP_PSOCKADDR>& vt, __out LPTIPAddr** lpppIPAddr, __out int& iIPAddrCount);
/* 释放 LPTIPAddr* */
BOOL FreeHostIPAddresses(LPTIPAddr* lppIPAddr);
/* 把 HP_SOCKADDR 结构转换为地址字符串 */
BOOL sockaddr_IN_2_A(const HP_SOCKADDR& addr, __out ADDRESS_FAMILY& usFamily, __out LPTSTR lpszAddress, __inout int& iAddressLen, __out USHORT& usPort);
/* 把地址字符串转换为 HP_SOCKADDR 结构 */
BOOL sockaddr_A_2_IN(LPCTSTR lpszAddress, USHORT usPort, __out HP_SOCKADDR& addr);
/* 获取 Socket 的本地或远程地址信息 */
BOOL GetSocketAddress(SOCKET socket, __out LPTSTR lpszAddress, __inout int& iAddressLen, __out USHORT& usPort, BOOL bLocal = TRUE);
/* 获取 Socket 的本地地址信息 */
BOOL GetSocketLocalAddress(SOCKET socket, __out LPTSTR lpszAddress, __inout int& iAddressLen, __out USHORT& usPort);
/* 获取 Socket 的远程地址信息 */
BOOL GetSocketRemoteAddress(SOCKET socket, __out LPTSTR lpszAddress, __inout int& iAddressLen, __out USHORT& usPort);

/* 64 位网络字节序转主机字节序 */
ULONGLONG NToH64(ULONGLONG value);
/* 64 位主机字节序转网络字节序 */
ULONGLONG HToN64(ULONGLONG value);

/* 短整型高低字节交换 */
#define ENDIAN_SWAP_16(A)	((USHORT)((((USHORT)(A) & 0xff00) >> 8) | (((USHORT)(A) & 0x00ff) << 8)))
/* 长整型高低字节交换 */
#define ENDIAN_SWAP_32(A)	((((DWORD)(A) & 0xff000000) >> 24) | \
							(((DWORD)(A) & 0x00ff0000) >>  8)  | \
							(((DWORD)(A) & 0x0000ff00) <<  8)  | \
							(((DWORD)(A) & 0x000000ff) << 24)	 )

/* 检查是否小端字节序 */
BOOL IsLittleEndian();
/* 短整型主机字节序转小端字节序 */
USHORT HToLE16(USHORT value);
/* 短整型主机字节序转大端字节序 */
USHORT HToBE16(USHORT value);
/* 长整型主机字节序转小端字节序 */
DWORD HToLE32(DWORD value);
/* 长整型主机字节序转大端字节序 */
DWORD HToBE32(DWORD value);

/* 获取 Socket 的某个扩展函数的指针 */
PVOID GetExtensionFuncPtr					(SOCKET sock, GUID guid);
/* 获取 AcceptEx 扩展函数指针 */
LPFN_ACCEPTEX Get_AcceptEx_FuncPtr			(SOCKET sock);
/* 获取 GetAcceptExSockaddrs 扩展函数指针 */
LPFN_GETACCEPTEXSOCKADDRS Get_GetAcceptExSockaddrs_FuncPtr(SOCKET sock);
/* 获取 ConnectEx 扩展函数指针 */
LPFN_CONNECTEX Get_ConnectEx_FuncPtr		(SOCKET sock);
/* 获取 TransmitFile 扩展函数指针 */
LPFN_TRANSMITFILE Get_TransmitFile_FuncPtr	(SOCKET sock);
/* 获取 DisconnectEx 扩展函数指针 */
LPFN_DISCONNECTEX Get_DisconnectEx_FuncPtr	(SOCKET sock);

HRESULT ReadSmallFile(LPCTSTR lpszFileName, CAtlFile& file, CAtlFileMapping<>& fmap, DWORD dwMaxFileSize = MAX_SMALL_FILE_SIZE);
HRESULT MakeSmallFilePackage(LPCTSTR lpszFileName, CAtlFile& file, CAtlFileMapping<>& fmap, WSABUF szBuf[3], const LPWSABUF pHead = nullptr, const LPWSABUF pTail = nullptr);

/************************************************************************
名称：IOCP 指令投递帮助方法
描述：简化 IOCP 指令投递
************************************************************************/

/* IOCP 命令 */
enum EnIocpCommand
{
	IOCP_CMD_EXIT		= 0x00000000,	// 退出程序
	IOCP_CMD_ACCEPT		= 0xFFFFFFF1,	// 接受连接
	IOCP_CMD_DISCONNECT	= 0xFFFFFFF2,	// 断开连接
	IOCP_CMD_SEND		= 0xFFFFFFF3,	// 发送数据
	IOCP_CMD_UNPAUSE	= 0xFFFFFFF4,	// 取消暂停
	IOCP_CMD_TIMEOUT	= 0xFFFFFFF5	// 保活超时
};

/* IOCP 命令处理动作 */
enum EnIocpAction
{
	IOCP_ACT_GOON		= 0,	// 继续执行
	IOCP_ACT_CONTINUE	= 1,	// 重新执行
	IOCP_ACT_BREAK		= 2		// 中断执行
};

BOOL PostIocpCommand(HANDLE hIOCP, EnIocpCommand enCmd, ULONG_PTR ulParam);
BOOL PostIocpExit(HANDLE hIOCP);
BOOL PostIocpAccept(HANDLE hIOCP);
BOOL PostIocpDisconnect(HANDLE hIOCP, CONNID dwConnID);
BOOL PostIocpSend(HANDLE hIOCP, CONNID dwConnID);
BOOL PostIocpUnpause(HANDLE hIOCP, CONNID dwConnID);
BOOL PostIocpTimeout(HANDLE hIOCP, CONNID dwConnID);
BOOL PostIocpClose(HANDLE hIOCP, CONNID dwConnID, int iErrorCode);

/************************************************************************
名称：setsockopt() 帮助方法
描述：简化常用的 setsockopt() 调用
************************************************************************/

int SSO_SetSocketOption		(SOCKET sock, int level, int name, LPVOID val, int len);
int SSO_GetSocketOption		(SOCKET sock, int level, int name, LPVOID val, int* len);
int SSO_IoctlSocket			(SOCKET sock, long cmd, u_long* arg);
int SSO_WSAIoctl			(SOCKET sock, DWORD dwIoControlCode, LPVOID lpvInBuffer, DWORD cbInBuffer, LPVOID lpvOutBuffer, DWORD cbOutBuffer, LPDWORD lpcbBytesReturned);

int SSO_UpdateAcceptContext	(SOCKET soClient, SOCKET soBind);
int SSO_UpdateConnectContext(SOCKET soClient, int iOption);
int SSO_NoBlock				(SOCKET sock, BOOL bNoBlock = TRUE);
int SSO_NoDelay				(SOCKET sock, BOOL bNoDelay = TRUE);
int SSO_DualStack			(SOCKET sock, BOOL bDualStack = TRUE);
int SSO_DontLinger			(SOCKET sock, BOOL bDont = TRUE);
int SSO_Linger				(SOCKET sock, USHORT l_onoff, USHORT l_linger);
int SSO_KeepAlive			(SOCKET sock, BOOL bKeepAlive = TRUE);
int SSO_KeepAliveVals		(SOCKET sock, u_long onoff, u_long time, u_long interval);
int SSO_RecvBuffSize		(SOCKET sock, int size);
int SSO_SendBuffSize		(SOCKET sock, int size);
int SSO_RecvTimeOut			(SOCKET sock, int ms);
int SSO_SendTimeOut			(SOCKET sock, int ms);
int SSO_ReuseAddress		(SOCKET sock, EnReuseAddressPolicy opt);
int SSO_ExclusiveAddressUse	(SOCKET sock, BOOL bExclusive = TRUE);
int SSO_UDP_ConnReset		(SOCKET sock, BOOL bNewBehavior = TRUE);
int SSO_GetError			(SOCKET sock);

/************************************************************************
名称：Socket 操作方法
描述：Socket 操作包装方法
************************************************************************/

/* 检测 IOCP 操作返回值：NO_ERROR 则返回 TRUE */
#define IOCP_NO_ERROR(rs)		((rs) == NO_ERROR)
/* 检测 IOCP 操作返回值：WSA_IO_PENDING 则返回 TRUE */
#define IOCP_PENDING(rs)		((rs) == WSA_IO_PENDING)
/* 检测 IOCP 操作返回值：NO_ERROR 或 WSA_IO_PENDING 则返回 TRUE */
#define IOCP_SUCCESS(rs)		(IOCP_NO_ERROR(rs) || IOCP_PENDING(rs))

/* 检查是否 UDP RESET 错误 */
#define IS_UDP_RESET_ERROR(rs)	((rs) == WSAENETRESET || (rs) == WSAECONNRESET)

/* 生成 Connection ID */
CONNID GenerateConnectionID	();
/* 检测 UDP 连接关闭通知 */
int IsUdpCloseNotify		(const BYTE* pData, int iLength);
/* 发送 UDP 连接关闭通知 */
int SendUdpCloseNotify		(SOCKET sock);
/* 发送 UDP 连接关闭通知 */
int SendUdpCloseNotify		(SOCKET sock, const HP_SOCKADDR& remoteAddr);
/* 关闭 Socket */
int ManualCloseSocket		(SOCKET sock, int iShutdownFlag = 0xFF, BOOL bGraceful = TRUE);
/* 投递 AccceptEx()，并把 WSA_IO_PENDING 转换为 NO_ERROR */
int PostAccept				(LPFN_ACCEPTEX pfnAcceptEx, SOCKET soListen, SOCKET soClient, TBufferObj* pBufferObj, ADDRESS_FAMILY usFamily);
/* 投递 AccceptEx() */
int PostAcceptNotCheck		(LPFN_ACCEPTEX pfnAcceptEx, SOCKET soListen, SOCKET soClient, TBufferObj* pBufferObj, ADDRESS_FAMILY usFamily);
/* 投递 ConnectEx()，并把 WSA_IO_PENDING 转换为 NO_ERROR */
int PostConnect				(LPFN_CONNECTEX pfnConnectEx, SOCKET soClient, const HP_SOCKADDR& sockAddr, TBufferObj* pBufferObj);
/* 投递 ConnectEx() */
int PostConnectNotCheck		(LPFN_CONNECTEX pfnConnectEx, SOCKET soClient, const HP_SOCKADDR& sockAddr, TBufferObj* pBufferObj);
/* 投递 WSASend()，并把 WSA_IO_PENDING 转换为 NO_ERROR */
int PostSend				(TSocketObj* pSocketObj, TBufferObj* pBufferObj);
/* 投递 WSASend() */
int PostSendNotCheck		(TSocketObj* pSocketObj, TBufferObj* pBufferObj);
/* 投递 WSARecv()，并把 WSA_IO_PENDING 转换为 NO_ERROR */
int PostReceive				(TSocketObj* pSocketObj, TBufferObj* pBufferObj);
/* 投递 WSARecv() */
int PostReceiveNotCheck		(TSocketObj* pSocketObj, TBufferObj* pBufferObj);
/* 投递 WSASendTo()，并把 WSA_IO_PENDING 转换为 NO_ERROR */
int PostSendTo				(SOCKET sock, TUdpBufferObj* pBufferObj);
/* 投递 WSASendTo() */
int PostSendToNotCheck		(SOCKET sock, TUdpBufferObj* pBufferObj);
/* 投递 WSARecvFrom()，并把 WSA_IO_PENDING 转换为 NO_ERROR */
int PostReceiveFrom			(SOCKET sock, TUdpBufferObj* pBufferObj);
/* 投递 WSARecvFrom() */
int PostReceiveFromNotCheck	(SOCKET sock, TUdpBufferObj* pBufferObj);
/* 执行非阻塞 WSARecv()，并把 WSAEWOULDBLOCK 转换为 NO_ERROR */
int NoBlockReceive(TBufferObj* pBufferObj);
/* 执行非阻塞 WSARecv() */
int NoBlockReceiveNotCheck(TBufferObj* pBufferObj);
/* 执行非阻塞 WSARecvFrom()，并把 WSAEWOULDBLOCK 转换为 NO_ERROR */
int NoBlockReceiveFrom(SOCKET sock, TUdpBufferObj* pBufferObj);
/* 执行非阻塞 WSARecvFrom() */
int NoBlockReceiveFromNotCheck(SOCKET sock, TUdpBufferObj* pBufferObj);
/* 设置组播选项 */
BOOL SetMultiCastSocketOptions(SOCKET sock, const HP_SOCKADDR& bindAddr, const HP_SOCKADDR& castAddr, int iMCTtl, BOOL bMCLoop);
/* 等待连接 */
int WaitForSocketWrite(SOCKET sock, DWORD dwTimeout);

// CP_XXX -> UNICODE
BOOL CodePageToUnicodeEx(int iCodePage, const char szSrc[], int iSrcLength, WCHAR szDest[], int& iDestLength);
// UNICODE -> CP_XXX
BOOL UnicodeToCodePageEx(int iCodePage, const WCHAR szSrc[], int iSrcLength, char szDest[], int& iDestLength);
// GBK -> UNICODE
BOOL GbkToUnicodeEx(const char szSrc[], int iSrcLength, WCHAR szDest[], int& iDestLength);
// UNICODE -> GBK
BOOL UnicodeToGbkEx(const WCHAR szSrc[], int iSrcLength, char szDest[], int& iDestLength);
// UTF8 -> UNICODE
BOOL Utf8ToUnicodeEx(const char szSrc[], int iSrcLength, WCHAR szDest[], int& iDestLength);
// UNICODE -> UTF8
BOOL UnicodeToUtf8Ex(const WCHAR szSrc[], int iSrcLength, char szDest[], int& iDestLength);
// GBK -> UTF8
BOOL GbkToUtf8Ex(const char szSrc[], int iSrcLength, char szDest[], int& iDestLength);
// UTF8 -> GBK
BOOL Utf8ToGbkEx(const char szSrc[], int iSrcLength, char szDest[], int& iDestLength);

// CP_XXX -> UNICODE
BOOL CodePageToUnicode(int iCodePage, const char szSrc[], WCHAR szDest[], int& iDestLength);
// UNICODE -> CP_XXX
BOOL UnicodeToCodePage(int iCodePage, const WCHAR szSrc[], char szDest[], int& iDestLength);
// GBK -> UNICODE
BOOL GbkToUnicode(const char szSrc[], WCHAR szDest[], int& iDestLength);
// UNICODE -> GBK
BOOL UnicodeToGbk(const WCHAR szSrc[], char szDest[], int& iDestLength);
// UTF8 -> UNICODE
BOOL Utf8ToUnicode(const char szSrc[], WCHAR szDest[], int& iDestLength);
// UNICODE -> UTF8
BOOL UnicodeToUtf8(const WCHAR szSrc[], char szDest[], int& iDestLength);
// GBK -> UTF8
BOOL GbkToUtf8(const char szSrc[], char szDest[], int& iDestLength);
// UTF8 -> GBK
BOOL Utf8ToGbk(const char szSrc[], char szDest[], int& iDestLength);

// 计算 Base64 编码后长度
DWORD GuessBase64EncodeBound(DWORD dwSrcLen);
// 计算 Base64 解码后长度
DWORD GuessBase64DecodeBound(const BYTE* lpszSrc, DWORD dwSrcLen);
// Base64 编码（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）
int Base64Encode(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen);
// Base64 解码（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）
int Base64Decode(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen);

// 计算 URL 编码后长度
DWORD GuessUrlEncodeBound(const BYTE* lpszSrc, DWORD dwSrcLen);
// 计算 URL 解码后长度
DWORD GuessUrlDecodeBound(const BYTE* lpszSrc, DWORD dwSrcLen);
// URL 编码（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）
int UrlEncode(BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen);
// URL 解码（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）
int UrlDecode(BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen);

/* 销毁压缩器对象 */
void DestroyCompressor(IHPCompressor* pCompressor);
/* 销毁解压器对象 */
void DestroyDecompressor(IHPDecompressor* pDecompressor);

#ifdef _ZLIB_SUPPORT

/* ZLib 压缩器 */
class CHPZLibCompressor : public IHPCompressor
{
public:
	virtual BOOL Process(const BYTE* pData, int iLength, BOOL bLast, PVOID pContext = nullptr);
	virtual BOOL ProcessEx(const BYTE* pData, int iLength, BOOL bLast, BOOL bFlush = FALSE, PVOID pContext = nullptr);
	virtual BOOL IsValid() {return m_bValid;}
	virtual BOOL Reset();

public:
	CHPZLibCompressor(Fn_CompressDataCallback fnCallback, int iWindowBits = DEF_WBITS, int iLevel = Z_DEFAULT_COMPRESSION, int iMethod = Z_DEFLATED, int iMemLevel = DEF_MEM_LEVEL, int iStrategy = Z_DEFAULT_STRATEGY, DWORD dwBuffSize = DEFAULT_COMPRESS_BUFFER_SIZE);
	virtual ~CHPZLibCompressor();

private:
	Fn_CompressDataCallback m_fnCallback;
	z_stream m_Stream;
	BOOL m_bValid;
	DWORD m_dwBuffSize;
};

/* ZLib 解压器 */
class CHPZLibDecompressor : public IHPDecompressor
{
public:
	virtual BOOL Process(const BYTE* pData, int iLength, PVOID pContext = nullptr);
	virtual BOOL IsValid() {return m_bValid;}
	virtual BOOL Reset();

public:
	CHPZLibDecompressor(Fn_DecompressDataCallback fnCallback, int iWindowBits = DEF_WBITS, DWORD dwBuffSize = DEFAULT_COMPRESS_BUFFER_SIZE);
	virtual ~CHPZLibDecompressor();

private:
	Fn_DecompressDataCallback m_fnCallback;
	z_stream m_Stream;
	BOOL m_bValid;
	DWORD m_dwBuffSize;
};

/* 创建 ZLib 压缩器对象 */
IHPCompressor* CreateZLibCompressor(Fn_CompressDataCallback fnCallback, int iWindowBits = DEF_WBITS, int iLevel = Z_DEFAULT_COMPRESSION, int iMethod = Z_DEFLATED, int iMemLevel = DEF_MEM_LEVEL, int iStrategy = Z_DEFAULT_STRATEGY, DWORD dwBuffSize = DEFAULT_COMPRESS_BUFFER_SIZE);
/* 创建 GZip 压缩器对象 */
IHPCompressor* CreateGZipCompressor(Fn_CompressDataCallback fnCallback, int iLevel = Z_DEFAULT_COMPRESSION, int iMethod = Z_DEFLATED, int iMemLevel = DEF_MEM_LEVEL, int iStrategy = Z_DEFAULT_STRATEGY, DWORD dwBuffSize = DEFAULT_COMPRESS_BUFFER_SIZE);
/* 创建 ZLib 解压器对象 */
IHPDecompressor* CreateZLibDecompressor(Fn_DecompressDataCallback fnCallback, int iWindowBits = DEF_WBITS, DWORD dwBuffSize = DEFAULT_COMPRESS_BUFFER_SIZE);
/* 创建 GZip 解压器对象 */
IHPDecompressor* CreateGZipDecompressor(Fn_DecompressDataCallback fnCallback, DWORD dwBuffSize = DEFAULT_COMPRESS_BUFFER_SIZE);

// 普通压缩（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）
int Compress(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen);
// 高级压缩（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）
int CompressEx(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen, int iLevel = Z_DEFAULT_COMPRESSION, int iMethod = Z_DEFLATED, int iWindowBits = DEF_WBITS, int iMemLevel = DEF_MEM_LEVEL, int iStrategy = Z_DEFAULT_STRATEGY);
// 普通解压（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）
int Uncompress(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen);
// 高级解压（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）
int UncompressEx(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen, int iWindowBits = DEF_WBITS);
// 推测压缩结果长度
DWORD GuessCompressBound(DWORD dwSrcLen, BOOL bGZip = FALSE);

// Gzip 压缩（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）
int GZipCompress(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen);
// Gzip 解压（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）
int GZipUncompress(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen);
// 推测 Gzip 解压结果长度（如果返回 0 或不合理值则说明输入内容并非有效的 Gzip 格式）
DWORD GZipGuessUncompressBound(const BYTE* lpszSrc, DWORD dwSrcLen);

#endif

#ifdef _BROTLI_SUPPORT

/* Brotli 压缩器 */
class CHPBrotliCompressor : public IHPCompressor
{
public:
	virtual BOOL Process(const BYTE* pData, int iLength, BOOL bLast, PVOID pContext = nullptr);
	virtual BOOL ProcessEx(const BYTE* pData, int iLength, BOOL bLast, BOOL bFlush = FALSE, PVOID pContext = nullptr);
	virtual BOOL IsValid() {return m_bValid;}
	virtual BOOL Reset();

public:
	CHPBrotliCompressor(Fn_CompressDataCallback fnCallback, int iQuality = BROTLI_DEFAULT_QUALITY, int iWindow = BROTLI_DEFAULT_WINDOW, int iMode = BROTLI_DEFAULT_MODE, DWORD dwBuffSize = DEFAULT_COMPRESS_BUFFER_SIZE);
	virtual ~CHPBrotliCompressor();

private:
	Fn_CompressDataCallback m_fnCallback;
	BrotliEncoderState* m_pState;
	BOOL m_bValid;

	int m_iQuality;
	int m_iWindow;
	int m_iMode;
	DWORD m_dwBuffSize;
};

/* Brotli 解压器 */
class CHPBrotliDecompressor : public IHPDecompressor
{
public:
	virtual BOOL Process(const BYTE* pData, int iLength, PVOID pContext = nullptr);
	virtual BOOL IsValid() {return m_bValid;}
	virtual BOOL Reset();

public:
	CHPBrotliDecompressor(Fn_DecompressDataCallback fnCallback, DWORD dwBuffSize = DEFAULT_COMPRESS_BUFFER_SIZE);
	virtual ~CHPBrotliDecompressor();

private:
	Fn_DecompressDataCallback m_fnCallback;
	BrotliDecoderState* m_pState;
	BOOL m_bValid;
	DWORD m_dwBuffSize;
};

/* 创建 Brotli 压缩器对象 */
IHPCompressor* CreateBrotliCompressor(Fn_CompressDataCallback fnCallback, int iQuality = BROTLI_DEFAULT_QUALITY, int iWindow = BROTLI_DEFAULT_WINDOW, int iMode = BROTLI_DEFAULT_MODE, DWORD dwBuffSize = DEFAULT_COMPRESS_BUFFER_SIZE);
/* 创建 Brotli 解压器对象 */
IHPDecompressor* CreateBrotliDecompressor(Fn_DecompressDataCallback fnCallback, DWORD dwBuffSize = DEFAULT_COMPRESS_BUFFER_SIZE);

// Brotli 压缩（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）
int BrotliCompress(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen);
// Brotli 高级压缩（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）
int BrotliCompressEx(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen, int iQuality = BROTLI_DEFAULT_QUALITY, int iWindow = BROTLI_DEFAULT_WINDOW, int iMode = BROTLI_DEFAULT_MODE);
// Brotli 解压（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）
int BrotliUncompress(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen);
// Brotli 推测压缩结果长度
DWORD BrotliGuessCompressBound(DWORD dwSrcLen);

#endif


/* ========================================================================== */
/*  MiscHelper.h  -- pack helpers
/*  source: Windows\Src\MiscHelper.h
/* ========================================================================== */

#pragma once

/* [amalgamated] #include "SocketHelper.h" */

/* Pack Data Info */
template<typename B = void> struct TPackInfo
{
	bool	header;
	DWORD	length;
	B*		pBuffer;

	static TPackInfo* Construct(B* pbuf = nullptr, bool head = true, DWORD len = sizeof(DWORD))
	{
		return new TPackInfo(pbuf, head, len);
	}

	static void Destruct(TPackInfo* pPackInfo)
	{
		if(pPackInfo)
			delete pPackInfo;
	}

	TPackInfo(B* pbuf = nullptr, bool head = true, DWORD len = sizeof(DWORD))
	: header(head), length(len), pBuffer(pbuf)
	{
	}

	void Reset()
	{
		header	= true;
		length	= sizeof(DWORD);
		pBuffer	= nullptr;
	}
};

typedef TPackInfo<TBuffer>	TBufferPackInfo;

BOOL AddPackHeader(const WSABUF * pBuffers, int iCount, unique_ptr<WSABUF[]>& buffers, DWORD dwMaxPackSize, USHORT usPackHeaderFlag, DWORD& dwHeader);

template<class B> EnFetchResult FetchBuffer(B* pBuffer, BYTE* pData, int iLength)
{
	ASSERT(pBuffer	!= nullptr);
	ASSERT(pData	!= nullptr && iLength > 0);

	EnFetchResult result = FR_OK;

	if(pBuffer->Length() >= iLength)
		pBuffer->Fetch(pData, iLength);
	else
		result = FR_LENGTH_TOO_LONG;

	return result;
}

template<class B> EnFetchResult PeekBuffer(B* pBuffer, BYTE* pData, int iLength)
{
	ASSERT(pBuffer	!= nullptr);
	ASSERT(pData	!= nullptr && iLength > 0);

	EnFetchResult result = FR_OK;

	if(pBuffer->Length() >= iLength)
		pBuffer->Peek(pData, iLength);
	else
		result = FR_LENGTH_TOO_LONG;

	return result;
}

template<class T, class B, class S> EnHandleResult ParsePack(T* pThis, TPackInfo<B>* pInfo, B* pBuffer, S* pSocket, DWORD dwMaxPackSize, USHORT usPackHeaderFlag)
{
	EnHandleResult rs = HR_OK;

	int required = pInfo->length;
	int remain	 = pBuffer->Length();

	while(remain >= required)
	{
		if(pSocket->IsPaused())
			break;

		remain -= required;
		CBufferPtr buffer(required);

		pBuffer->Fetch(buffer, (int)buffer.Size());

		if(pInfo->header)
		{
			DWORD header = ::HToLE32(*((DWORD*)(BYTE*)buffer));

			if(usPackHeaderFlag != 0)
			{
				USHORT flag = (USHORT)(header >> TCP_PACK_LENGTH_BITS);

				if(flag != usPackHeaderFlag)
				{
					::SetLastError(ERROR_INVALID_DATA);
					return HR_ERROR;
				}
			}

			DWORD len = header & TCP_PACK_LENGTH_MASK;

			if(len == 0 || len > dwMaxPackSize)
			{
				::SetLastError(ERROR_BAD_LENGTH);
				return HR_ERROR;
			}

			required = len;
		}
		else
		{
			rs = pThis->DoFireSuperReceive(pSocket, (const BYTE*)buffer, (int)buffer.Size());

			if(rs == HR_ERROR)
				return rs;

			required = sizeof(DWORD);
		}

		pInfo->header = !pInfo->header;
		pInfo->length = required;
	}

	return rs;
}

template<class T, class B, class S> EnHandleResult ParsePack(T* pThis, TPackInfo<B>* pInfo, B* pBuffer, S* pSocket, DWORD dwMaxPackSize, USHORT usPackHeaderFlag, const BYTE* pData, int iLength)
{
	pBuffer->Cat(pData, iLength);

	return ParsePack(pThis, pInfo, pBuffer, pSocket, dwMaxPackSize, usPackHeaderFlag);
}

template<class T> BOOL ContinueReceive(T* pThis, TSocketObj* pSocketObj, TBufferObj* pBufferObj, EnHandleResult& hr)
{
	int rs = NO_ERROR;

	for(int i = 0; i < MAX_IOCP_CONTINUE_RECEIVE || MAX_IOCP_CONTINUE_RECEIVE < 0; i++)
	{
		if(pSocketObj->paused)
			break;

		if(hr != HR_OK && hr != HR_IGNORE)
			break;

		pBufferObj->buff.len = pThis->GetSocketBufferSize();
		rs = ::NoBlockReceiveNotCheck(pBufferObj);

		if(rs != NO_ERROR)
			break;

		hr = pThis->TriggerFireReceive(pSocketObj, pBufferObj);
	}

	if(hr != HR_OK && hr != HR_IGNORE)
		return FALSE;

	if(rs != NO_ERROR && rs != WSAEWOULDBLOCK)
	{
		if(rs == WSAEDISCON)
			pThis->AddFreeSocketObj(pSocketObj, SCF_CLOSE);
		else
			pThis->CheckError(pSocketObj, SO_RECEIVE, rs);

		pThis->AddFreeBufferObj(pBufferObj);

		return FALSE;
	}

	return TRUE;
}

template<class T> void ContinueReceiveFrom(T* pThis, TUdpBufferObj* pBufferObj)
{
	int rs;

	while(TRUE)
	{
		pBufferObj->buff.len = pThis->GetMaxDatagramSize();
		rs = ::NoBlockReceiveFromNotCheck(pThis->GetListenSocket(), pBufferObj);

		if(rs != NO_ERROR)
			break;

		pThis->ProcessReceiveBufferObj(pBufferObj);
	}
}


/* ========================================================================== */
/*  ArqHelper.h  -- ARQ / KCP session
/*  source: Windows\Src\ArqHelper.h
/* ========================================================================== */

#pragma once

/* [amalgamated] #include "../Include/HPSocket/HPTypeDef.h" */

#ifdef _UDP_SUPPORT

/* [amalgamated] #include "SocketHelper.h" */

/* [amalgamated] #include "Common/WaitFor.h" */
/* [amalgamated] #include "Common/BufferPool.h" */
/* [amalgamated] #include "Common/kcp/ikcp.h" */

#define DEFAULT_ARQ_NO_DELAY			FALSE
#define DEFAULT_ARQ_TURNOFF_NC			FALSE
#define DEFAULT_ARQ_FLUSH_INTERVAL		60
#define DEFAULT_ARQ_RESEND_BY_ACKS		0
#define DEFAULT_ARQ_SEND_WND_SIZE		128
#define DEFAULT_ARQ_RECV_WND_SIZE		512
#define DEFAULT_ARQ_MIN_RTO				30
#define DEFAULT_ARQ_FAST_LIMIT			5
#define DEFAULT_ARQ_MAX_TRANS_UNIT		DEFAULT_UDP_MAX_DATAGRAM_SIZE
#define DEFAULT_ARQ_MAX_MSG_SIZE		DEFAULT_BUFFER_CACHE_CAPACITY
#define DEFAULT_ARQ_HANND_SHAKE_TIMEOUT	5000

#define KCP_HEADER_SIZE					24
#define KCP_MIN_RECV_WND				128

#define ARQ_MAX_HANDSHAKE_INTERVAL		2000

typedef int (*Fn_ArqOutputProc)(const char* pBuffer, int iLength, IKCPCB* kcp, LPVOID pv);

DWORD GenerateConversationID();

/************************************************************************
名称：ARQ 握手状态
描述：标识当前连接的 ARQ 握手状态
************************************************************************/
enum EnArqHandShakeStatus
{
	ARQ_HSS_INIT	= 0,	// 初始状态
	ARQ_HSS_PROC	= 1,	// 正在握手
	ARQ_HSS_SUCC	= 2,	// 握手成功
};

struct TArqCmd
{
public:
	static const UINT16 MAGIC			= 0xBB4F;
	static const UINT8	CMD_HANDSHAKE	= 0x01;
	static const UINT8	FLAG_COMPLETE	= 0x01;
	static const int	PACKAGE_LENGTH	= 12;

public:
	UINT16 magic;
	UINT8 cmd;
	UINT8 flag;
	DWORD selfID;
	DWORD peerID;

public:
	static BYTE* MakePackage(UINT8 cmd, UINT8 flag, DWORD selfID, DWORD peerID, UINT16 magic = MAGIC)
	{
		BYTE* buff = new BYTE[PACKAGE_LENGTH];

		*((UINT16*)(buff + 0))	= magic;
		*((UINT8*)(buff + 2))	= cmd;
		*((UINT8*)(buff + 3))	= flag;
		*((DWORD*)(buff + 4))	= selfID;
		*((DWORD*)(buff + 8))	= peerID;

		return buff;
	}

	BYTE* MakePackage()
	{
		return MakePackage(cmd, flag, selfID, peerID, magic);
	}

	BOOL Parse(const BYTE buff[PACKAGE_LENGTH])
	{
		magic	= *((UINT16*)(buff + 0));
		cmd		= *((UINT8*) (buff + 2));
		flag	= *((UINT8*) (buff + 3));
		selfID	= *((DWORD*) (buff + 4));
		peerID	= *((DWORD*) (buff + 8));

		return IsValid();
	}

	BOOL IsValid()	{return (magic == MAGIC && cmd == CMD_HANDSHAKE && (flag & 0xFE) == 0);}

public:
	TArqCmd()
	{
		::ZeroMemory(this, sizeof(TArqCmd));
	}

	TArqCmd(UINT8 c, UINT8 f, DWORD sid, DWORD pid)
	: magic	(MAGIC)
	, cmd	(c)
	, flag	(f)
	, selfID(sid)
	, peerID(pid)
	{

	}
};

struct TArqAttr
{
	BOOL	bNoDelay;
	BOOL	bTurnoffNc;
	DWORD	dwResendByAcks;
	DWORD	dwFlushInterval;
	DWORD	dwSendWndSize;
	DWORD	dwRecvWndSize;
	DWORD	dwMinRto;
	DWORD	dwMtu;
	DWORD	dwFastLimit;
	DWORD	dwMaxMessageSize;
	DWORD	dwHandShakeTimeout;

public:
	TArqAttr( BOOL no_delay				= DEFAULT_ARQ_NO_DELAY
			, BOOL turnoff_nc			= DEFAULT_ARQ_TURNOFF_NC
			, DWORD resend_by_acks		= DEFAULT_ARQ_RESEND_BY_ACKS
			, DWORD flush_interval		= DEFAULT_ARQ_FLUSH_INTERVAL
			, DWORD send_wnd_size		= DEFAULT_ARQ_SEND_WND_SIZE
			, DWORD recv_wnd_size		= DEFAULT_ARQ_RECV_WND_SIZE
			, DWORD min_rto				= DEFAULT_ARQ_MIN_RTO
			, DWORD mtu					= DEFAULT_ARQ_MAX_TRANS_UNIT
			, DWORD fast_limit			= DEFAULT_ARQ_FAST_LIMIT
			, DWORD max_msg_size		= DEFAULT_ARQ_MAX_MSG_SIZE
			, DWORD hand_shake_timeout	= DEFAULT_ARQ_HANND_SHAKE_TIMEOUT
			)
	: bNoDelay			(no_delay)
	, bTurnoffNc		(turnoff_nc)
	, dwResendByAcks	(resend_by_acks)
	, dwFlushInterval	(flush_interval)
	, dwSendWndSize		(send_wnd_size)
	, dwRecvWndSize		(recv_wnd_size)
	, dwMinRto			(min_rto)
	, dwMtu				(mtu)
	, dwFastLimit		(fast_limit)
	, dwMaxMessageSize	(max_msg_size)
	, dwHandShakeTimeout(hand_shake_timeout)
	{
		ASSERT(IsValid());
	}

	BOOL IsValid() const
	{
		return 	((int)dwResendByAcks >= 0)																				&&
				((int)dwFlushInterval > 0)																				&&
				((int)dwSendWndSize > 0)																				&&
				((int)dwRecvWndSize > 0)																				&&
				((int)dwMinRto > 0)																						&&
				((int)dwFastLimit >= 0)																					&&
				((int)dwHandShakeTimeout > 2 * (int)dwMinRto)															&&
				((int)dwMtu >= 3 * KCP_HEADER_SIZE && dwMtu <= MAXIMUM_UDP_MAX_DATAGRAM_SIZE)							&&
				((int)dwMaxMessageSize > 0 && dwMaxMessageSize < ((KCP_MIN_RECV_WND - 1) * (dwMtu - KCP_HEADER_SIZE)))	;
	}

};

template<class T, class S> class CArqSessionT
{
public:
	CArqSessionT* Renew(T* pContext, S* pSocket, const TArqAttr& attr, DWORD dwPeerConvID = 0)
	{
		m_pContext		= pContext;
		m_pSocket		= pSocket;
		m_dwSelfConvID	= ::GenerateConversationID();

		DoRenew(attr, dwPeerConvID);
		RenewExtra(attr);

		m_dwCreateTime	= ::TimeGetTime();
		m_dwHSNextTime	= m_dwCreateTime;
		m_dwHSSndCount	= 0;
		m_bHSComplete	= FALSE;
		m_enStatus		= ARQ_HSS_PROC;

		Check();

		return this;
	}

	BOOL Reset()
	{
		if(!IsValid())
			return FALSE;

		{
			CCriSecLock recvlock(m_csRecv);
			CCriSecLock sendlock(m_csSend);

			if(!IsValid())
				return FALSE;

			m_enStatus	= ARQ_HSS_INIT;

			DoReset();
		}

		ResetExtra();

		return TRUE;
	}

	BOOL Check()
	{
		if(IsReady())
		{
			if(m_bHSComplete || DoHandShake())
				return Flush();
			else
				return FALSE;
		}
		else if(IsHandShaking())
			return DoHandShake();
		else
		{
			::SetLastError(ERROR_INVALID_STATE);
			return FALSE;
		}
	}

	BOOL DoHandShake()
	{
		if(!IsValid())
		{
			::SetLastError(ERROR_INVALID_STATE);
			return FALSE;
		}

		unique_ptr<BYTE[]> bufCmdPtr;

		{
			CCriSecLock recvlock(m_csRecv);

			if(!IsValid())
			{
				::SetLastError(ERROR_INVALID_STATE);
				return FALSE;
			}

			DWORD dwCurrent = ::TimeGetTime();

			if(::GetTimeGap32(m_dwCreateTime, dwCurrent) > m_pContext->GetHandShakeTimeout())
			{
				::SetLastError(ERROR_TIMEOUT);
				return FALSE;
			}

			if((int)(::GetTimeGap32(m_dwHSNextTime, dwCurrent)) < 0)
				return TRUE;

			m_dwHSNextTime	= dwCurrent + min(m_kcp->interval * (++m_dwHSSndCount), ARQ_MAX_HANDSHAKE_INTERVAL);
			UINT8 iFlag		= IsReady() ? TArqCmd::FLAG_COMPLETE : 0;

			bufCmdPtr.reset(TArqCmd::MakePackage(TArqCmd::CMD_HANDSHAKE, iFlag, m_dwSelfConvID, m_dwPeerConvID));
		}

		return m_pContext->DoSend(m_pSocket, bufCmdPtr.get(), TArqCmd::PACKAGE_LENGTH);
	}

	BOOL Flush(BOOL bForce = FALSE)
	{
		if(!IsReady())
		{
			::SetLastError(ERROR_INVALID_STATE);
			return FALSE;
		}

		{
			CCriSecTryLock recvlock(m_csRecv);

			if(recvlock.IsValid())
			{
				CCriSecTryLock sendlock(m_csSend);

				if(sendlock.IsValid())
				{
					if(!IsReady())
					{
						::SetLastError(ERROR_INVALID_STATE);
						return FALSE;
					}

					if(bForce)
						::ikcp_flush(m_kcp);
					else
						::ikcp_update(m_kcp, ::TimeGetTime());
				}
			}
		}

		return TRUE;
	}

	int Send(const BYTE* pBuffer, int iLength)
	{
		if(!IsReady())
			return ERROR_INVALID_STATE;

		int rs = NO_ERROR;

		{
			CCriSecLock sendlock(m_csSend);

			if(!IsReady())
				return ERROR_INVALID_STATE;

			rs = ::ikcp_send(m_kcp, (const char*)pBuffer, iLength);
			if(rs < 0) rs = ERROR_INCORRECT_SIZE;
		}

		if(rs == NO_ERROR)
			Flush(TRUE);

		return rs;
	}

	int GetWaitingSend()
	{
		if(!IsValid())
		{
			::SetLastError(ERROR_INVALID_STATE);
			return -1;
		}

		CCriSecLock sendlock(m_csSend);

		if(!IsValid())
		{
			::SetLastError(ERROR_INVALID_STATE);
			return -1;
		}

		return ::ikcp_waitsnd(m_kcp);
	}

	EnHandleResult Receive(const BYTE* pData, int iLength, BYTE* pBuffer, int iCapacity)
	{
		if(iLength >= KCP_HEADER_SIZE)
			return ReceiveArq(pData, iLength, pBuffer, iCapacity);
		else if(iLength == TArqCmd::PACKAGE_LENGTH)
			return ReceiveHandShake(pData);
		else
		{
			::WSASetLastError(ERROR_INVALID_DATA);
			return HR_ERROR;
		}
	}

	EnHandleResult ReceiveHandShake(const BYTE* pBuffer)
	{
		TArqCmd cmd;
		cmd.Parse(pBuffer);

		if(!cmd.IsValid())
		{
			::WSASetLastError(ERROR_INVALID_DATA);
			return HR_ERROR;
		}

		{
			CCriSecLock recvlock(m_csRecv);

			if(!IsValid())
			{
				::WSASetLastError(ERROR_INVALID_STATE);
				return HR_ERROR;
			}
			
			if(IsReady())
			{
				BOOL bReset = FALSE;

				if(cmd.selfID != m_dwPeerConvID)
					bReset = TRUE;
				else if(cmd.peerID != m_dwSelfConvID)
				{
					if(cmd.peerID != 0)
						bReset = TRUE;
					else
					{
						if(::GetTimeGap32(m_dwCreateTime) > 2 * m_pContext->GetHandShakeTimeout())
							bReset = TRUE;
					}
				}

				if(bReset)
				{
					::WSASetLastError(WSAECONNRESET);
					return HR_ERROR;
				}
			}
			else
			{
				if(m_dwPeerConvID == 0)
				{
					m_dwPeerConvID = cmd.selfID;
					m_dwHSNextTime = ::TimeGetTime();
					m_dwHSSndCount = 0;
				}
				else if(cmd.selfID != m_dwPeerConvID)
				{
					::WSASetLastError(WSAECONNRESET);
					return HR_ERROR;
				}

				if(cmd.peerID == m_dwSelfConvID)
				{
					m_enStatus = ARQ_HSS_SUCC;
					return m_pContext->DoFireHandShake(m_pSocket);
				}
				else if(cmd.peerID != 0)
				{
					::WSASetLastError(WSAECONNRESET);
					return HR_ERROR;
				}
			}
		}

		if(!m_bHSComplete && cmd.flag == TArqCmd::FLAG_COMPLETE)
			m_bHSComplete = TRUE;

		DoHandShake();

		return HR_OK;
	}

	EnHandleResult ReceiveArq(const BYTE* pData, int iLength, BYTE* pBuffer, int iCapacity)
	{
		if(!IsReady()) return HR_IGNORE;

		{
			CCriSecLock recvlock(m_csRecv);

			if(!IsReady())
			{
				::WSASetLastError(ERROR_INVALID_STATE);
				return HR_ERROR;
			}

			if(iLength < KCP_HEADER_SIZE)
			{
				::WSASetLastError(ERROR_INVALID_DATA);
				return HR_ERROR;
			}

			int rs = ::ikcp_input(m_kcp, (const char*)pData, iLength);

			if(rs != NO_ERROR)
			{
				::WSASetLastError(ERROR_INVALID_DATA);
				return HR_ERROR;
			}

			while(TRUE)
			{
				int iRead = ::ikcp_recv(m_kcp, (char*)pBuffer, iCapacity);

				if(iRead >= 0)
				{
					EnHandleResult result = m_pContext->DoFireReceive(m_pSocket, pBuffer, iRead);

					if(result == HR_ERROR)
						return result;
				}
				else if(iRead == -3)
				{
					::WSASetLastError(ERROR_INCORRECT_SIZE);
					return HR_ERROR;
				}
				else
					break;
			}
		}

		Flush(TRUE);

		return HR_OK;
	}

private:
	void DoRenew(const TArqAttr& attr, DWORD dwPeerConvID = 0)
	{
		ASSERT(attr.IsValid());

		DoReset();

		m_dwPeerConvID	= dwPeerConvID;
		m_kcp			= ::ikcp_create(m_dwSelfConvID, m_pSocket);

		::ikcp_nodelay(m_kcp, attr.bNoDelay ? 1 : 0, (int)attr.dwFlushInterval, (int)attr.dwResendByAcks, attr.bTurnoffNc ? 1 : 0);
		::ikcp_wndsize(m_kcp, (int)attr.dwSendWndSize, (int)attr.dwRecvWndSize);
		::ikcp_setmtu(m_kcp, attr.dwMtu);

		m_kcp->rx_minrto	= (int)attr.dwMinRto;
		m_kcp->fastlimit	= (int)attr.dwFastLimit;
		m_kcp->output		= m_pContext->GetArqOutputProc();
	}

	void DoReset()
	{
		if(m_kcp != nullptr)
		{
			::ikcp_release(m_kcp);
			m_kcp = nullptr;
		}
	}

public:
	BOOL		IsValid()		const	{return GetStatus() != ARQ_HSS_INIT;}
	BOOL		IsHandShaking()	const	{return GetStatus() == ARQ_HSS_PROC;}
	BOOL		IsReady()		const	{return GetStatus() == ARQ_HSS_SUCC;}
	IKCPCB*		GetKcp()				{return m_kcp;}
	DWORD		GetConvID()		const	{if(!IsValid()) return 0; return m_kcp->conv;}
	DWORD		GetSelfConvID()	const	{return m_dwSelfConvID;}
	DWORD		GetPeerConvID()	const	{return m_dwPeerConvID;}
	
	EnArqHandShakeStatus GetStatus() const {return m_enStatus;}

protected:
	virtual void RenewExtra(const TArqAttr& attr) {}
	virtual void ResetExtra() {}

public:
	CArqSessionT()
	: m_pContext	(nullptr)
	, m_pSocket		(nullptr)
	, m_kcp			(nullptr)
	, m_enStatus	(ARQ_HSS_INIT)
	, m_dwSelfConvID(0)
	, m_dwPeerConvID(0)
	, m_dwCreateTime(0)
	, m_dwHSNextTime(0)
	, m_dwHSSndCount(0)
	, m_bHSComplete	(FALSE)
	{

	}

	virtual ~CArqSessionT()
	{
		Reset();
	}

	static CArqSessionT* Construct()
		{return new CArqSessionT();}

	static void Destruct(CArqSessionT* pSession)
		{if(pSession) delete pSession;}

protected:
	T*		m_pContext;
	S*		m_pSocket;

private:
	BOOL	m_bHSComplete;
	DWORD	m_dwHSNextTime;
	DWORD	m_dwHSSndCount;
	DWORD	m_dwCreateTime;
	DWORD	m_dwSelfConvID;
	DWORD	m_dwPeerConvID;
	EnArqHandShakeStatus m_enStatus;

	CCriSec m_csRecv;
	CCriSec m_csSend;
	IKCPCB* m_kcp;
};

template<class T, class S> class CArqSessionExT : public CArqSessionT<T, S>, public CSafeCounter
{
public:
	DWORD GetFreeTime	()	const	{return m_dwFreeTime;}
	HANDLE GetTimer		()	const	{return m_hTimer;}

protected:
	virtual void RenewExtra(const TArqAttr& attr)
	{
		ResetCount();

		m_hTimer = m_tqFlush.CreateTimer(FlushProc, this, attr.dwFlushInterval, attr.dwFlushInterval, WT_EXECUTEINTIMERTHREAD);
	}

	virtual void ResetExtra()
	{
		m_tqFlush.DeleteTimer(m_hTimer);

		m_dwFreeTime = ::TimeGetTime();
		m_hTimer	 = nullptr;
	}

private:
	static void WINAPI FlushProc(LPVOID pv, BOOLEAN bTimerFired)
	{
		CArqSessionExT* pSession = (CArqSessionExT*)pv;

		CLocalSafeCounter localcounter(*pSession);

		if(!pSession->Check() && pSession->IsValid() && TUdpSocketObj::IsValid(pSession->m_pSocket))
			pSession->m_pContext->Disconnect(pSession->m_pSocket->connID);
	}

public:
	CArqSessionExT(CTimerQueue& tqFlush)
	: m_tqFlush		(tqFlush)
	, m_hTimer		(nullptr)
	, m_dwFreeTime	(0)
	{

	}

	virtual ~CArqSessionExT()
	{
		Reset();
	}

	static CArqSessionExT* Construct(CTimerQueue& tqFlush)
		{return new CArqSessionExT(tqFlush);}

	static void Destruct(CArqSessionExT* pSession)
		{if(pSession) delete pSession;}

private:
	CTimerQueue& m_tqFlush;

	HANDLE	m_hTimer;
	DWORD	m_dwFreeTime;
};

template<class T, class S> class CArqSessionPoolT
{
	typedef CArqSessionExT<T, S>		CArqSessionEx;
	typedef CRingPool<CArqSessionEx>	TArqSessionList;
	typedef CCASQueue<CArqSessionEx>	TArqSessionQueue;

public:
	CArqSessionEx* PickFreeSession(T* pContext, S* pSocket, const TArqAttr& attr)
	{
		DWORD dwIndex;
		CArqSessionEx* pSession = nullptr;

		if(m_lsFreeSession.TryLock(&pSession, dwIndex))
		{
			if(::GetTimeGap32(pSession->GetFreeTime()) >= m_dwSessionLockTime)
				ENSURE(m_lsFreeSession.ReleaseLock(nullptr, dwIndex));
			else
			{
				ENSURE(m_lsFreeSession.ReleaseLock(pSession, dwIndex));
				pSession = nullptr;
			}
		}

		if(!pSession) pSession = CArqSessionEx::Construct(m_tqFlush);

		ASSERT(pSession);
		return (CArqSessionEx*)pSession->Renew(pContext, pSocket, attr);
	}

	void PutFreeSession(CArqSessionEx* pSession)
	{
		if(pSession->Reset())
		{
#ifndef USE_EXTERNAL_GC
			ReleaseGCSession();
#endif
			if(!m_lsFreeSession.TryPut(pSession))
				m_lsGCSession.PushBack(pSession);
		}
	}

	void Prepare()
	{
		m_lsFreeSession.Reset(m_dwSessionPoolSize);
	}

	void Clear()
	{
		m_tqFlush.Reset();

		m_lsFreeSession.Clear();

		ReleaseGCSession(TRUE);
		ENSURE(m_lsGCSession.IsEmpty());
	}

	void ReleaseGCSession(BOOL bForce = FALSE)
	{
		::ReleaseGCObj(m_lsGCSession, m_dwSessionLockTime, bForce);
	}

public:
	void SetSessionLockTime	(DWORD dwSessionLockTime)	{m_dwSessionLockTime = dwSessionLockTime;}
	void SetSessionPoolSize	(DWORD dwSessionPoolSize)	{m_dwSessionPoolSize = dwSessionPoolSize;}
	void SetSessionPoolHold	(DWORD dwSessionPoolHold)	{m_dwSessionPoolHold = dwSessionPoolHold;}

	DWORD GetSessionLockTime()	{return m_dwSessionLockTime;}
	DWORD GetSessionPoolSize()	{return m_dwSessionPoolSize;}
	DWORD GetSessionPoolHold()	{return m_dwSessionPoolHold;}

public:
	CArqSessionPoolT(
					DWORD dwPoolSize = DEFAULT_SESSION_POOL_SIZE,
					DWORD dwPoolHold = DEFAULT_SESSION_POOL_HOLD,
					DWORD dwLockTime = DEFAULT_SESSION_LOCK_TIME)
	: m_dwSessionPoolSize(dwPoolSize)
	, m_dwSessionPoolHold(dwPoolHold)
	, m_dwSessionLockTime(dwLockTime)
	{

	}

	~CArqSessionPoolT()	{Clear();}

	DECLARE_NO_COPY_CLASS(CArqSessionPoolT)

public:
	static const DWORD DEFAULT_SESSION_LOCK_TIME;
	static const DWORD DEFAULT_SESSION_POOL_SIZE;
	static const DWORD DEFAULT_SESSION_POOL_HOLD;

private:
	CTimerQueue			m_tqFlush;

	DWORD				m_dwSessionLockTime;
	DWORD				m_dwSessionPoolSize;
	DWORD				m_dwSessionPoolHold;

	TArqSessionList		m_lsFreeSession;
	TArqSessionQueue	m_lsGCSession;
};

template<class T, class S> const DWORD CArqSessionPoolT<T, S>::DEFAULT_SESSION_LOCK_TIME	= DEFAULT_OBJECT_CACHE_LOCK_TIME;
template<class T, class S> const DWORD CArqSessionPoolT<T, S>::DEFAULT_SESSION_POOL_SIZE	= DEFAULT_OBJECT_CACHE_POOL_SIZE;
template<class T, class S> const DWORD CArqSessionPoolT<T, S>::DEFAULT_SESSION_POOL_HOLD	= DEFAULT_OBJECT_CACHE_POOL_HOLD;

#endif


/* ========================================================================== */
/*  TcpServer.h  -- CTcpServer
/*  source: Windows\Src\TcpServer.h
/* ========================================================================== */

#pragma once

/* [amalgamated] #include "MiscHelper.h" */
/* [amalgamated] #include "Common/Event.h" */
/* [amalgamated] #include "Common/STLHelper.h" */
/* [amalgamated] #include "Common/RingBuffer.h" */
/* [amalgamated] #include "Common/PrivateHeap.h" */

class CTcpServer : public ITcpServer
{
public:
	virtual BOOL Start	(LPCTSTR lpszBindAddress, USHORT usPort);
	virtual BOOL Stop	();
	virtual BOOL Send	(CONNID dwConnID, const BYTE* pBuffer, int iLength, int iOffset = 0);
	virtual BOOL SendSmallFile	(CONNID dwConnID, LPCTSTR lpszFileName, const LPWSABUF pHead = nullptr, const LPWSABUF pTail = nullptr);
	virtual BOOL SendPackets	(CONNID dwConnID, const WSABUF pBuffers[], int iCount)	{return DoSendPackets(dwConnID, pBuffers, iCount);}
	virtual BOOL PauseReceive	(CONNID dwConnID, BOOL bPause = TRUE);
	virtual BOOL Wait			(DWORD dwMilliseconds = INFINITE) {return m_evWait.Wait(dwMilliseconds);}
	virtual BOOL			HasStarted					()	{return m_enState == SS_STARTED || m_enState == SS_STARTING;}
	virtual EnServiceState	GetState					()	{return m_enState;}
	virtual BOOL			Disconnect					(CONNID dwConnID, BOOL bForce = TRUE);
	virtual BOOL			DisconnectLongConnections	(DWORD dwPeriod, BOOL bForce = TRUE);
	virtual BOOL			DisconnectSilenceConnections(DWORD dwPeriod, BOOL bForce = TRUE);
	virtual BOOL			GetListenAddress			(TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort);
	virtual BOOL			GetLocalAddress				(CONNID dwConnID, TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort);
	virtual BOOL			GetRemoteAddress			(CONNID dwConnID, TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort);
	
	virtual BOOL IsConnected			(CONNID dwConnID);
	virtual BOOL IsPauseReceive			(CONNID dwConnID, BOOL& bPaused);
	virtual BOOL GetPendingDataLength	(CONNID dwConnID, int& iPending);
	virtual DWORD GetConnectionCount	();
	virtual BOOL GetAllConnectionIDs	(CONNID pIDs[], DWORD& dwCount);
	virtual BOOL GetConnectPeriod		(CONNID dwConnID, DWORD& dwPeriod);
	virtual BOOL GetSilencePeriod		(CONNID dwConnID, DWORD& dwPeriod);
	virtual EnSocketError GetLastError	()	{return m_enLastError;}
	virtual LPCTSTR	GetLastErrorDesc	()	{return ::GetSocketErrorDesc(m_enLastError);}

#ifdef _SSL_SUPPORT
	virtual BOOL SetupSSLContext	(int iVerifyMode = SSL_VM_NONE, LPCTSTR lpszPemCertFile = nullptr, LPCTSTR lpszPemKeyFile = nullptr, LPCTSTR lpszKeyPassword = nullptr, LPCTSTR lpszCAPemCertFileOrPath = nullptr, Fn_SNI_ServerNameCallback fnServerNameCallback = nullptr)	{return FALSE;}
	virtual BOOL SetupSSLContextByMemory(int iVerifyMode = SSL_VM_NONE, LPCSTR lpszPemCert = nullptr, LPCSTR lpszPemKey = nullptr, LPCSTR lpszKeyPassword = nullptr, LPCSTR lpszCAPemCert = nullptr, Fn_SNI_ServerNameCallback fnServerNameCallback = nullptr)						{return FALSE;}
	virtual int AddSSLContext		(int iVerifyMode = SSL_VM_NONE, LPCTSTR lpszPemCertFile = nullptr, LPCTSTR lpszPemKeyFile = nullptr, LPCTSTR lpszKeyPassword = nullptr, LPCTSTR lpszCAPemCertFileOrPath = nullptr)																{return FALSE;}
	virtual int AddSSLContextByMemory(int iVerifyMode = SSL_VM_NONE, LPCSTR lpszPemCert = nullptr, LPCSTR lpszPemKey = nullptr, LPCSTR lpszKeyPassword = nullptr, LPCSTR lpszCAPemCert = nullptr)																					{return FALSE;}
	virtual BOOL BindSSLServerName	(LPCTSTR lpszServerName, int iContextIndex)																																																		{return FALSE;}
	virtual void CleanupSSLContext	()						{}

	virtual BOOL StartSSLHandShake	(CONNID dwConnID)		{return FALSE;}
	virtual void SetSSLAutoHandShake(BOOL bAutoHandShake)	{}
	virtual BOOL IsSSLAutoHandShake	()						{return FALSE;}
	virtual void SetSSLCipherList	(LPCTSTR lpszCipherList){}
	virtual LPCTSTR GetSSLCipherList()						{return nullptr;}
	virtual BOOL GetSSLSessionInfo(CONNID dwConnID, EnSSLSessionInfo enInfo, LPVOID* lppInfo)	{return FALSE;}

protected:
	virtual BOOL StartSSLHandShake	(TSocketObj* pSocketObj){return FALSE;}
#endif

public:
	virtual BOOL IsSecure			() {return FALSE;}

	virtual BOOL SetConnectionExtra(CONNID dwConnID, PVOID pExtra);
	virtual BOOL GetConnectionExtra(CONNID dwConnID, PVOID* ppExtra);

	virtual void SetReuseAddressPolicy		(EnReuseAddressPolicy enReusePolicy)	{ENSURE_HAS_STOPPED(); m_enReusePolicy		= enReusePolicy;}
	virtual void SetSendPolicy				(EnSendPolicy enSendPolicy)				{ENSURE_HAS_STOPPED(); m_enSendPolicy		= enSendPolicy;}
	virtual void SetOnSendSyncPolicy		(EnOnSendSyncPolicy enOnSendSyncPolicy)	{ENSURE_HAS_STOPPED(); m_enOnSendSyncPolicy	= enOnSendSyncPolicy;}
	virtual void SetMaxConnectionCount		(DWORD dwMaxConnectionCount)	{ENSURE_HAS_STOPPED(); m_dwMaxConnectionCount		= dwMaxConnectionCount;}
	virtual void SetWorkerThreadCount		(DWORD dwWorkerThreadCount)		{ENSURE_HAS_STOPPED(); m_dwWorkerThreadCount		= dwWorkerThreadCount;}
	virtual void SetSocketListenQueue		(DWORD dwSocketListenQueue)		{ENSURE_HAS_STOPPED(); m_dwSocketListenQueue		= dwSocketListenQueue;}
	virtual void SetAcceptSocketCount		(DWORD dwAcceptSocketCount)		{ENSURE_HAS_STOPPED(); m_dwAcceptSocketCount		= dwAcceptSocketCount;}
	virtual void SetSocketBufferSize		(DWORD dwSocketBufferSize)		{ENSURE_HAS_STOPPED(); m_dwSocketBufferSize			= dwSocketBufferSize;}
	virtual void SetFreeSocketObjLockTime	(DWORD dwFreeSocketObjLockTime)	{ENSURE_HAS_STOPPED(); m_dwFreeSocketObjLockTime	= dwFreeSocketObjLockTime;}
	virtual void SetFreeSocketObjPool		(DWORD dwFreeSocketObjPool)		{ENSURE_HAS_STOPPED(); m_dwFreeSocketObjPool		= dwFreeSocketObjPool;}
	virtual void SetFreeBufferObjPool		(DWORD dwFreeBufferObjPool)		{ENSURE_HAS_STOPPED(); m_dwFreeBufferObjPool		= dwFreeBufferObjPool;}
	virtual void SetFreeSocketObjHold		(DWORD dwFreeSocketObjHold)		{ENSURE_HAS_STOPPED(); m_dwFreeSocketObjHold		= dwFreeSocketObjHold;}
	virtual void SetFreeBufferObjHold		(DWORD dwFreeBufferObjHold)		{ENSURE_HAS_STOPPED(); m_dwFreeBufferObjHold		= dwFreeBufferObjHold;}
	virtual void SetKeepAliveTime			(DWORD dwKeepAliveTime)			{ENSURE_HAS_STOPPED(); m_dwKeepAliveTime			= dwKeepAliveTime;}
	virtual void SetKeepAliveInterval		(DWORD dwKeepAliveInterval)		{ENSURE_HAS_STOPPED(); m_dwKeepAliveInterval		= dwKeepAliveInterval;}
	virtual void SetMarkSilence				(BOOL bMarkSilence)				{ENSURE_HAS_STOPPED(); m_bMarkSilence				= bMarkSilence;}
	virtual void SetNoDelay					(BOOL bNoDelay)					{ENSURE_HAS_STOPPED(); m_bNoDelay					= bNoDelay;}
	virtual void SetDualStack				(BOOL bDualStack)				{ENSURE_HAS_STOPPED(); m_bDualStack					= bDualStack;}

	virtual EnReuseAddressPolicy GetReuseAddressPolicy	()	{return m_enReusePolicy;}
	virtual EnSendPolicy GetSendPolicy					()	{return m_enSendPolicy;}
	virtual EnOnSendSyncPolicy GetOnSendSyncPolicy		()	{return m_enOnSendSyncPolicy;}
	virtual DWORD GetMaxConnectionCount		()	{return m_dwMaxConnectionCount;}
	virtual DWORD GetWorkerThreadCount		()	{return m_dwWorkerThreadCount;}
	virtual DWORD GetSocketListenQueue		()	{return m_dwSocketListenQueue;}
	virtual DWORD GetAcceptSocketCount		()	{return m_dwAcceptSocketCount;}
	virtual DWORD GetSocketBufferSize		()	{return m_dwSocketBufferSize;}
	virtual DWORD GetFreeSocketObjLockTime	()	{return m_dwFreeSocketObjLockTime;}
	virtual DWORD GetFreeSocketObjPool		()	{return m_dwFreeSocketObjPool;}
	virtual DWORD GetFreeBufferObjPool		()	{return m_dwFreeBufferObjPool;}
	virtual DWORD GetFreeSocketObjHold		()	{return m_dwFreeSocketObjHold;}
	virtual DWORD GetFreeBufferObjHold		()	{return m_dwFreeBufferObjHold;}
	virtual DWORD GetKeepAliveTime			()	{return m_dwKeepAliveTime;}
	virtual DWORD GetKeepAliveInterval		()	{return m_dwKeepAliveInterval;}
	virtual BOOL  IsMarkSilence				()	{return m_bMarkSilence;}
	virtual BOOL  IsNoDelay					()	{return m_bNoDelay;}
	virtual BOOL IsDualStack				()	{return m_bDualStack;}

protected:
	virtual EnHandleResult FirePrepareListen(SOCKET soListen)
		{return DoFirePrepareListen(soListen);}
	virtual EnHandleResult FireAccept(TSocketObj* pSocketObj)
		{
			EnHandleResult rs		= DoFireAccept(pSocketObj);
			if(rs != HR_ERROR) rs	= FireHandShake(pSocketObj);
			return rs;
		}
	virtual EnHandleResult FireHandShake(TSocketObj* pSocketObj)
		{return DoFireHandShake(pSocketObj);}
	virtual EnHandleResult FireReceive(TSocketObj* pSocketObj, const BYTE* pData, int iLength)
		{return DoFireReceive(pSocketObj, pData, iLength);}
	virtual EnHandleResult FireReceive(TSocketObj* pSocketObj, int iLength)
		{return DoFireReceive(pSocketObj, iLength);}
	virtual EnHandleResult FireSend(TSocketObj* pSocketObj, const BYTE* pData, int iLength)
		{return DoFireSend(pSocketObj, pData, iLength);}
	virtual EnHandleResult FireClose(TSocketObj* pSocketObj, EnSocketOperation enOperation, int iErrorCode)
		{return DoFireClose(pSocketObj, enOperation, iErrorCode);}
	virtual EnHandleResult FireShutdown()
		{return DoFireShutdown();}

	virtual EnHandleResult DoFirePrepareListen(SOCKET soListen)
		{return m_pListener->OnPrepareListen(this, soListen);}
	virtual EnHandleResult DoFireAccept(TSocketObj* pSocketObj)
		{return m_pListener->OnAccept(this, pSocketObj->connID, pSocketObj->socket);}
	virtual EnHandleResult DoFireHandShake(TSocketObj* pSocketObj)
		{return m_pListener->OnHandShake(this, pSocketObj->connID);}
	virtual EnHandleResult DoFireReceive(TSocketObj* pSocketObj, const BYTE* pData, int iLength)
		{return m_pListener->OnReceive(this, pSocketObj->connID, pData, iLength);}
	virtual EnHandleResult DoFireReceive(TSocketObj* pSocketObj, int iLength)
		{return m_pListener->OnReceive(this, pSocketObj->connID, iLength);}
	virtual EnHandleResult DoFireSend(TSocketObj* pSocketObj, const BYTE* pData, int iLength)
		{return m_pListener->OnSend(this, pSocketObj->connID, pData, iLength);}
	virtual EnHandleResult DoFireClose(TSocketObj* pSocketObj, EnSocketOperation enOperation, int iErrorCode)
		{return m_pListener->OnClose(this, pSocketObj->connID, enOperation, iErrorCode);}
	virtual EnHandleResult DoFireShutdown()
		{return m_pListener->OnShutdown(this);}

	void SetLastError(EnSocketError code, LPCSTR func, int ec);
	virtual BOOL CheckParams();
	virtual void PrepareStart();
	virtual void Reset();

	virtual EnHandleResult BeforeUnpause(TSocketObj* pSocketObj) {return HR_IGNORE;}

	virtual void OnWorkerThreadStart(THR_ID dwThreadID) {}
	virtual void OnWorkerThreadEnd(THR_ID dwThreadID) {}

	virtual void ReleaseGCSocketObj(BOOL bForce = FALSE);

	BOOL DoSendPackets(CONNID dwConnID, const WSABUF pBuffers[], int iCount);
	BOOL DoSendPackets(TSocketObj* pSocketObj, const WSABUF pBuffers[], int iCount);
	TSocketObj* FindSocketObj(CONNID dwConnID);

private:
	EnHandleResult TriggerFireAccept(TSocketObj* pSocketObj);
	EnHandleResult TriggerFireReceive(TSocketObj* pSocketObj, TBufferObj* pBufferObj);
	EnHandleResult TriggerFireSend(TSocketObj* pSocketObj, TBufferObj* pBufferObj);
	EnHandleResult TriggerFireClose(TSocketObj* pSocketObj, EnSocketOperation enOperation, int iErrorCode);

protected:
	BOOL SetConnectionExtra(TSocketObj* pSocketObj, PVOID pExtra);
	BOOL GetConnectionExtra(TSocketObj* pSocketObj, PVOID* ppExtra);
	BOOL SetConnectionReserved(CONNID dwConnID, PVOID pReserved);
	BOOL GetConnectionReserved(CONNID dwConnID, PVOID* ppReserved);
	BOOL SetConnectionReserved(TSocketObj* pSocketObj, PVOID pReserved);
	BOOL GetConnectionReserved(TSocketObj* pSocketObj, PVOID* ppReserved);
	BOOL SetConnectionReserved2(CONNID dwConnID, PVOID pReserved2);
	BOOL GetConnectionReserved2(CONNID dwConnID, PVOID* ppReserved2);
	BOOL SetConnectionReserved2(TSocketObj* pSocketObj, PVOID pReserved2);
	BOOL GetConnectionReserved2(TSocketObj* pSocketObj, PVOID* ppReserved2);

private:
	BOOL CheckStarting();
	BOOL CheckStoping();
	BOOL CreateListenSocket(LPCTSTR lpszBindAddress, USHORT usPort);
	BOOL CreateCompletePort();
	BOOL CreateWorkerThreads();
	BOOL StartAccept();

	void CloseListenSocket();
	void WaitForAcceptSocketClose();
	void DisconnectClientSocket();
	void WaitForClientSocketClose();
	void ReleaseClientSocket();
	void ReleaseFreeSocket();
	void ReleaseFreeBuffer();
	void WaitForWorkerThreadEnd();
	void CloseCompletePort();

	TBufferObj*	GetFreeBufferObj(int iLen = -1);
	TSocketObj*	GetFreeSocketObj(CONNID dwConnID, SOCKET soClient);
	void		AddFreeBufferObj(TBufferObj* pBufferObj);
	void		AddFreeSocketObj(TSocketObj* pSocketObj, EnSocketCloseFlag enFlag = SCF_NONE, EnSocketOperation enOperation = SO_UNKNOWN, int iErrorCode = 0);
	TSocketObj*	CreateSocketObj();
	void		DeleteSocketObj(TSocketObj* pSocketObj);
	BOOL		InvalidSocketObj(TSocketObj* pSocketObj);

	void		AddClientSocketObj(CONNID dwConnID, TSocketObj* pSocketObj, const HP_SOCKADDR& remoteAddr);
	void		CloseClientSocketObj(TSocketObj* pSocketObj, EnSocketCloseFlag enFlag = SCF_NONE, EnSocketOperation enOperation = SO_UNKNOWN, int iErrorCode = 0, int iShutdownFlag = SD_SEND);

private:
	friend BOOL ContinueReceive<>(CTcpServer* pThis, TSocketObj* pSocketObj, TBufferObj* pBufferObj, EnHandleResult& hr);

	static UINT WINAPI WorkerThreadProc(LPVOID pv);
	static void WINAPI GCProc(LPVOID pv, BOOLEAN bTimerFired);

	EnIocpAction CheckIocpCommand(OVERLAPPED* pOverlapped, DWORD dwBytes, ULONG_PTR ulCompKey);

	void ForceDisconnect(CONNID dwConnID);
	void HandleIo		(CONNID dwConnID, TSocketObj* pSocketObj, TBufferObj* pBufferObj, DWORD dwBytes, DWORD dwErrorCode);
	void HandleError	(CONNID dwConnID, TSocketObj* pSocketObj, TBufferObj* pBufferObj, DWORD dwErrorCode);
	void HandleAccept	(SOCKET soListen, TBufferObj* pBufferObj);
	void HandleSend		(CONNID dwConnID, TSocketObj* pSocketObj, TBufferObj* pBufferObj);
	void HandleReceive	(CONNID dwConnID, TSocketObj* pSocketObj, TBufferObj* pBufferObj);

	int SendInternal(TSocketObj* pSocketObj, const WSABUF pBuffers[], int iCount);
	int SendPack	(TSocketObj* pSocketObj, const BYTE* pBuffer, int iLength);
	int SendSafe	(TSocketObj* pSocketObj, const BYTE* pBuffer, int iLength);
	int CatAndPost	(TSocketObj* pSocketObj, const BYTE* pBuffer, int iLength);
	int SendDirect	(TSocketObj* pSocketObj, const BYTE* pBuffer, int iLength);

	BOOL DoAccept	();
	int DoUnpause	(CONNID dwConnID);
	int DoReceive	(TSocketObj* pSocketObj, TBufferObj* pBufferObj);
	int DoSend		(CONNID dwConnID);
	int DoSendPack	(TSocketObj* pSocketObj);
	int DoSendSafe	(TSocketObj* pSocketObj);
	int SendItem	(TSocketObj* pSocketObj);

	void CheckError	(TSocketObj* pSocketObj, EnSocketOperation enOperation, int iErrorCode);

public:
	CTcpServer(ITcpServerListener* pListener)
	: m_pListener				(pListener)
	, m_hCompletePort			(nullptr)
	, m_soListen				(INVALID_SOCKET)
	, m_iRemainAcceptSockets	(0)
	, m_pfnAcceptEx				(nullptr)
	, m_pfnGetAcceptExSockaddrs	(nullptr)
	, m_pfnDisconnectEx			(nullptr)
	, m_enLastError				(SE_OK)
	, m_enState					(SS_STOPPED)
	, m_usFamily				(AF_UNSPEC)
	, m_enReusePolicy			(RAP_ADDR_ONLY)
	, m_enSendPolicy			(SP_PACK)
	, m_enOnSendSyncPolicy		(OSSP_NONE)
	, m_dwMaxConnectionCount	(DEFAULT_CONNECTION_COUNT)
	, m_dwWorkerThreadCount		(DEFAULT_WORKER_THREAD_COUNT)
	, m_dwSocketListenQueue		(DEFAULT_TCP_SERVER_SOCKET_LISTEN_QUEUE)
	, m_dwAcceptSocketCount		(DEFAULT_TCP_SERVER_ACCEPT_SOCKET_COUNT)
	, m_dwSocketBufferSize		(DEFAULT_TCP_SOCKET_BUFFER_SIZE)
	, m_dwFreeSocketObjLockTime	(DEFAULT_FREE_SOCKETOBJ_LOCK_TIME)
	, m_dwFreeSocketObjPool		(DEFAULT_FREE_SOCKETOBJ_POOL)
	, m_dwFreeBufferObjPool		(DEFAULT_FREE_BUFFEROBJ_POOL)
	, m_dwFreeSocketObjHold		(DEFAULT_FREE_SOCKETOBJ_HOLD)
	, m_dwFreeBufferObjHold		(DEFAULT_FREE_BUFFEROBJ_HOLD)
	, m_dwKeepAliveTime			(DEFALUT_TCP_KEEPALIVE_TIME)
	, m_dwKeepAliveInterval		(DEFALUT_TCP_KEEPALIVE_INTERVAL)
	, m_bMarkSilence			(TRUE)
	, m_bNoDelay				(FALSE)
	, m_bDualStack				(TRUE)
	, m_evWait					(TRUE, TRUE)
	{
		ASSERT(sm_wsSocket.IsValid());
		ASSERT(m_pListener);
	}

	virtual ~CTcpServer()
	{
		ENSURE_STOP();
	}

private:
	EnReuseAddressPolicy m_enReusePolicy;
	EnSendPolicy m_enSendPolicy;
	EnOnSendSyncPolicy m_enOnSendSyncPolicy;
	DWORD m_dwMaxConnectionCount;
	DWORD m_dwWorkerThreadCount;
	DWORD m_dwSocketListenQueue;
	DWORD m_dwAcceptSocketCount;
	DWORD m_dwSocketBufferSize;
	DWORD m_dwFreeSocketObjLockTime;
	DWORD m_dwFreeSocketObjPool;
	DWORD m_dwFreeBufferObjPool;
	DWORD m_dwFreeSocketObjHold;
	DWORD m_dwFreeBufferObjHold;
	DWORD m_dwKeepAliveTime;
	DWORD m_dwKeepAliveInterval;
	BOOL  m_bMarkSilence;
	BOOL  m_bNoDelay;
	BOOL  m_bDualStack;

private:
	static const CInitSocket	sm_wsSocket;

	CEvt						m_evWait;

	LPFN_ACCEPTEX				m_pfnAcceptEx;
	LPFN_GETACCEPTEXSOCKADDRS	m_pfnGetAcceptExSockaddrs;
	LPFN_DISCONNECTEX			m_pfnDisconnectEx;

	ADDRESS_FAMILY				m_usFamily;

private:
	ITcpServerListener*	m_pListener;
	SOCKET				m_soListen;
	HANDLE				m_hCompletePort;
	EnServiceState		m_enState;
	EnSocketError		m_enLastError;

	vector<HANDLE>		m_vtWorkerThreads;

	CPrivateHeap		m_phSocket;
	CBufferObjPool		m_bfObjPool;

	CSpinGuard			m_csState;

	CGCTimerQueue		m_tqGC;

	TSocketObjPtrPool	m_bfActiveSockets;

	TSocketObjPtrList	m_lsFreeSocket;
	TSocketObjPtrQueue	m_lsGCSocket;

	volatile long		m_iRemainAcceptSockets;
};


/* ========================================================================== */
/*  TcpPullServer.h  -- CTcpPullServerT
/*  source: Windows\Src\TcpPullServer.h
/* ========================================================================== */

#pragma once

/* [amalgamated] #include "TcpServer.h" */
/* [amalgamated] #include "Common/BufferPool.h" */

template<class T> class CTcpPullServerT : public IPullSocket, public T
{
public:
	virtual EnFetchResult Fetch(CONNID dwConnID, BYTE* pData, int iLength)
	{
		TBuffer* pBuffer = m_bfPool[dwConnID];
		return ::FetchBuffer(pBuffer, pData, iLength);
	}

	virtual EnFetchResult Peek(CONNID dwConnID, BYTE* pData, int iLength)
	{
		TBuffer* pBuffer = m_bfPool[dwConnID];
		return ::PeekBuffer(pBuffer, pData, iLength);
	}

protected:
	virtual EnHandleResult DoFireAccept(TSocketObj* pSocketObj)
	{
		EnHandleResult result = __super::DoFireAccept(pSocketObj);

		if(result != HR_ERROR)
		{
			TBuffer* pBuffer = m_bfPool.PutCacheBuffer(pSocketObj->connID);
			ENSURE(SetConnectionReserved(pSocketObj, pBuffer));
		}

		return result;
	}

	virtual EnHandleResult DoFireHandShake(TSocketObj* pSocketObj)
	{
		EnHandleResult result = __super::DoFireHandShake(pSocketObj);

		if(result == HR_ERROR)
			ReleaseConnectionExtra(pSocketObj);

		return result;
	}

	virtual EnHandleResult DoFireReceive(TSocketObj* pSocketObj, const BYTE* pData, int iLength)
	{
		TBuffer* pBuffer = nullptr;
		GetConnectionReserved(pSocketObj, (PVOID*)&pBuffer);
		ASSERT(pBuffer && pBuffer->IsValid());

		pBuffer->Cat(pData, iLength);

		return __super::DoFireReceive(pSocketObj, pBuffer->Length());
	}

	virtual EnHandleResult DoFireClose(TSocketObj* pSocketObj, EnSocketOperation enOperation, int iErrorCode)
	{
		EnHandleResult result = __super::DoFireClose(pSocketObj, enOperation, iErrorCode);

		ReleaseConnectionExtra(pSocketObj);

		return result;
	}

	virtual EnHandleResult DoFireShutdown()
	{
		EnHandleResult result = __super::DoFireShutdown();

		m_bfPool.Clear();

		return result;
	}

	virtual void PrepareStart()
	{
		__super::PrepareStart();

		m_bfPool.SetMaxCacheSize	(GetMaxConnectionCount());
		m_bfPool.SetItemCapacity	(GetSocketBufferSize());
		m_bfPool.SetItemPoolSize	(GetFreeBufferObjPool());
		m_bfPool.SetItemPoolHold	(GetFreeBufferObjHold());
		m_bfPool.SetBufferLockTime	(GetFreeSocketObjLockTime());
		m_bfPool.SetBufferPoolSize	(GetFreeSocketObjPool());
		m_bfPool.SetBufferPoolHold	(GetFreeSocketObjHold());

		m_bfPool.Prepare();
	}

	virtual void ReleaseGCSocketObj(BOOL bForce = FALSE)
	{
		__super::ReleaseGCSocketObj(bForce);

#ifdef USE_EXTERNAL_GC
		m_bfPool.ReleaseGCBuffer(bForce);
#endif
	}

private:
	void ReleaseConnectionExtra(TSocketObj* pSocketObj)
	{
		TBuffer* pBuffer = nullptr;
		GetConnectionReserved(pSocketObj, (PVOID*)&pBuffer);

		if(pBuffer != nullptr)
		{
			m_bfPool.PutFreeBuffer(pBuffer);
			ENSURE(SetConnectionReserved(pSocketObj, nullptr));
		}
	}

public:
	CTcpPullServerT(ITcpServerListener* pListener)
	: T(pListener)
	{

	}

	virtual ~CTcpPullServerT()
	{
		ENSURE_STOP();
	}

private:
	CBufferPool m_bfPool;
};

typedef CTcpPullServerT<CTcpServer> CTcpPullServer;

#ifdef _SSL_SUPPORT

/* [amalgamated] #include "SSLServer.h" */
typedef CTcpPullServerT<CSSLServer> CSSLPullServer;

#endif


/* ========================================================================== */
/*  TcpPackServer.h  -- CTcpPackServerT
/*  source: Windows\Src\TcpPackServer.h
/* ========================================================================== */

#pragma once

/* [amalgamated] #include "TcpServer.h" */
/* [amalgamated] #include "Common/BufferPool.h" */

template<class T> class CTcpPackServerT : public IPackSocket, public T
{
public:
	virtual BOOL SendPackets(CONNID dwConnID, const WSABUF pBuffers[], int iCount)
	{
		int iNewCount = iCount + 1;
		unique_ptr<WSABUF[]> buffers(new WSABUF[iNewCount]);

		DWORD dwHeader;
		if(!::AddPackHeader(pBuffers, iCount, buffers, m_dwMaxPackSize, m_usHeaderFlag, dwHeader))
			return FALSE;

		return __super::SendPackets(dwConnID, buffers.get(), iNewCount);
	}

protected:
	virtual EnHandleResult DoFireAccept(TSocketObj* pSocketObj)
	{
		EnHandleResult result = __super::DoFireAccept(pSocketObj);

		if(result != HR_ERROR)
		{
			TBuffer* pBuffer = m_bfPool.PickFreeBuffer(pSocketObj->connID);
			ENSURE(SetConnectionReserved(pSocketObj, TBufferPackInfo::Construct(pBuffer)));
		}

		return result;
	}

	virtual EnHandleResult DoFireHandShake(TSocketObj* pSocketObj)
	{
		EnHandleResult result = __super::DoFireHandShake(pSocketObj);

		if(result == HR_ERROR)
			ReleaseConnectionExtra(pSocketObj);

		return result;
	}

	virtual EnHandleResult DoFireReceive(TSocketObj* pSocketObj, const BYTE* pData, int iLength)
	{
		TBufferPackInfo* pInfo = nullptr;
		GetConnectionReserved(pSocketObj, (PVOID*)&pInfo);
		ASSERT(pInfo);

		TBuffer* pBuffer = (TBuffer*)pInfo->pBuffer;
		ASSERT(pBuffer && pBuffer->IsValid());

		return ParsePack(this, pInfo, pBuffer, pSocketObj, m_dwMaxPackSize, m_usHeaderFlag, pData, iLength);
	}

	virtual EnHandleResult DoFireClose(TSocketObj* pSocketObj, EnSocketOperation enOperation, int iErrorCode)
	{
		EnHandleResult result = __super::DoFireClose(pSocketObj, enOperation, iErrorCode);

		ReleaseConnectionExtra(pSocketObj);

		return result;
	}

	virtual EnHandleResult DoFireShutdown()
	{
		EnHandleResult result = __super::DoFireShutdown();

		m_bfPool.Clear();

		return result;
	}

	virtual EnHandleResult BeforeUnpause(TSocketObj* pSocketObj)
	{
		CCriSecLock locallock(pSocketObj->csRecv);

		if(!TSocketObj::IsValid(pSocketObj))
			return (EnHandleResult)HR_CLOSED;

		if(pSocketObj->IsPaused())
			return HR_IGNORE;

		TBufferPackInfo* pInfo = nullptr;
		GetConnectionReserved(pSocketObj, (PVOID*)&pInfo);
		ASSERT(pInfo);

		TBuffer* pBuffer = (TBuffer*)pInfo->pBuffer;
		ASSERT(pBuffer && pBuffer->IsValid());

		return ParsePack(this, pInfo, pBuffer, pSocketObj, m_dwMaxPackSize, m_usHeaderFlag);
	}

	virtual BOOL CheckParams()
	{
		if	((m_dwMaxPackSize > 0 && m_dwMaxPackSize <= TCP_PACK_MAX_SIZE_LIMIT)	&&
			(m_usHeaderFlag >= 0 && m_usHeaderFlag <= TCP_PACK_HEADER_FLAG_LIMIT)	)
			return __super::CheckParams();

		SetLastError(SE_INVALID_PARAM, __FUNCTION__, ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	virtual void PrepareStart()
	{
		__super::PrepareStart();

		m_bfPool.SetMaxCacheSize	(GetMaxConnectionCount());
		m_bfPool.SetItemCapacity	(GetSocketBufferSize());
		m_bfPool.SetItemPoolSize	(GetFreeBufferObjPool());
		m_bfPool.SetItemPoolHold	(GetFreeBufferObjHold());
		m_bfPool.SetBufferLockTime	(GetFreeSocketObjLockTime());
		m_bfPool.SetBufferPoolSize	(GetFreeSocketObjPool());
		m_bfPool.SetBufferPoolHold	(GetFreeSocketObjHold());

		m_bfPool.Prepare();
	}

	virtual void ReleaseGCSocketObj(BOOL bForce = FALSE)
	{
		__super::ReleaseGCSocketObj(bForce);

#ifdef USE_EXTERNAL_GC
		m_bfPool.ReleaseGCBuffer(bForce);
#endif
	}

public:
	virtual void SetMaxPackSize		(DWORD dwMaxPackSize)		{ENSURE_HAS_STOPPED(); m_dwMaxPackSize = dwMaxPackSize;}
	virtual void SetPackHeaderFlag	(USHORT usPackHeaderFlag)	{ENSURE_HAS_STOPPED(); m_usHeaderFlag  = usPackHeaderFlag;}
	virtual DWORD GetMaxPackSize	()							{return m_dwMaxPackSize;}
	virtual USHORT GetPackHeaderFlag()							{return m_usHeaderFlag;}

private:
	void ReleaseConnectionExtra(TSocketObj* pSocketObj)
	{
		TBufferPackInfo* pInfo = nullptr;
		GetConnectionReserved(pSocketObj, (PVOID*)&pInfo);

		if(pInfo != nullptr)
		{
			m_bfPool.PutFreeBuffer(pInfo->pBuffer);
			TBufferPackInfo::Destruct(pInfo);

			ENSURE(SetConnectionReserved(pSocketObj, nullptr));
		}
	}

	EnHandleResult DoFireSuperReceive(TSocketObj* pSocketObj, const BYTE* pData, int iLength)
		{return __super::DoFireReceive(pSocketObj, pData, iLength);}

	friend EnHandleResult ParsePack<>(CTcpPackServerT* pThis, TBufferPackInfo* pInfo, TBuffer* pBuffer, TSocketObj* pSocket, DWORD dwMaxPackSize, USHORT usPackHeaderFlag);

public:
	CTcpPackServerT(ITcpServerListener* pListener)
	: T					(pListener)
	, m_dwMaxPackSize	(TCP_PACK_DEFAULT_MAX_SIZE)
	, m_usHeaderFlag	(TCP_PACK_DEFAULT_HEADER_FLAG)
	{

	}

	virtual ~CTcpPackServerT()
	{
		ENSURE_STOP();
	}

private:
	DWORD	m_dwMaxPackSize;
	USHORT	m_usHeaderFlag;

	CBufferPool m_bfPool;
};

typedef CTcpPackServerT<CTcpServer> CTcpPackServer;

#ifdef _SSL_SUPPORT

/* [amalgamated] #include "SSLServer.h" */
typedef CTcpPackServerT<CSSLServer> CSSLPackServer;

#endif


/* ========================================================================== */
/*  TcpClient.h  -- CTcpClient
/*  source: Windows\Src\TcpClient.h
/* ========================================================================== */

#pragma once

/* [amalgamated] #include "SocketHelper.h" */

class CTcpClient : public ITcpClient
{
public:
	virtual BOOL Start	(LPCTSTR lpszRemoteAddress, USHORT usPort, BOOL bAsyncConnect = TRUE, LPCTSTR lpszBindAddress = nullptr, USHORT usLocalPort = 0);
	virtual BOOL Stop	();
	virtual BOOL Send	(const BYTE* pBuffer, int iLength, int iOffset = 0);
	virtual BOOL SendSmallFile	(LPCTSTR lpszFileName, const LPWSABUF pHead = nullptr, const LPWSABUF pTail = nullptr);
	virtual BOOL SendPackets	(const WSABUF pBuffers[], int iCount)	{return DoSendPackets(pBuffers, iCount);}
	virtual BOOL PauseReceive	(BOOL bPause = TRUE);
	virtual BOOL Wait			(DWORD dwMilliseconds = INFINITE) {return m_evWait.Wait(dwMilliseconds);}
	virtual BOOL			HasStarted			()	{return m_enState == SS_STARTED || m_enState == SS_STARTING;}
	virtual EnServiceState	GetState			()	{return m_enState;}
	virtual CONNID			GetConnectionID		()	{return m_dwConnID;}
	virtual EnSocketError	GetLastError		()	{return m_enLastError;}
	virtual LPCTSTR			GetLastErrorDesc	()	{return ::GetSocketErrorDesc(m_enLastError);}

	virtual BOOL GetLocalAddress		(TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort);
	virtual BOOL GetRemoteHost			(TCHAR lpszHost[], int& iHostLen, USHORT& usPort);
	virtual BOOL GetPendingDataLength	(int& iPending) {iPending = m_iPending; return HasStarted();}
	virtual BOOL IsPauseReceive			(BOOL& bPaused) {bPaused = m_bPaused; return HasStarted();}
	virtual BOOL IsConnected			()				{return m_bConnected;}


#ifdef _SSL_SUPPORT
	virtual BOOL SetupSSLContext	(int iVerifyMode = SSL_VM_NONE, LPCTSTR lpszPemCertFile = nullptr, LPCTSTR lpszPemKeyFile = nullptr, LPCTSTR lpszKeyPassword = nullptr, LPCTSTR lpszCAPemCertFileOrPath = nullptr)	{return FALSE;}
	virtual BOOL SetupSSLContextByMemory(int iVerifyMode = SSL_VM_NONE, LPCSTR lpszPemCert = nullptr, LPCSTR lpszPemKey = nullptr, LPCSTR lpszKeyPassword = nullptr, LPCSTR lpszCAPemCert = nullptr)					{return FALSE;}
	virtual void CleanupSSLContext	()						{}

	virtual BOOL StartSSLHandShake	()						{return FALSE;}
	virtual void SetSSLAutoHandShake(BOOL bAutoHandShake)	{}
	virtual BOOL IsSSLAutoHandShake	()						{return FALSE;}
	virtual void SetSSLCipherList	(LPCTSTR lpszCipherList){}
	virtual LPCTSTR GetSSLCipherList()						{return nullptr;}
	virtual BOOL GetSSLSessionInfo(EnSSLSessionInfo enInfo, LPVOID* lppInfo)	{return FALSE;}

protected:
	virtual BOOL StartSSLHandShakeNoCheck()					{return FALSE;}
#endif

public:
	virtual BOOL IsSecure				() {return FALSE;}

	virtual void SetReuseAddressPolicy	(EnReuseAddressPolicy enReusePolicy){ENSURE_HAS_STOPPED(); m_enReusePolicy			= enReusePolicy;}
	virtual void SetSyncConnectTimeout	(DWORD dwSyncConnectTimeout)		{ENSURE_HAS_STOPPED(); m_dwSyncConnectTimeout	= dwSyncConnectTimeout;}
	virtual void SetSocketBufferSize	(DWORD dwSocketBufferSize)			{ENSURE_HAS_STOPPED(); m_dwSocketBufferSize		= dwSocketBufferSize;}
	virtual void SetKeepAliveTime		(DWORD dwKeepAliveTime)				{ENSURE_HAS_STOPPED(); m_dwKeepAliveTime		= dwKeepAliveTime;}
	virtual void SetKeepAliveInterval	(DWORD dwKeepAliveInterval)			{ENSURE_HAS_STOPPED(); m_dwKeepAliveInterval	= dwKeepAliveInterval;}
	virtual void SetFreeBufferPoolSize	(DWORD dwFreeBufferPoolSize)		{ENSURE_HAS_STOPPED(); m_dwFreeBufferPoolSize	= dwFreeBufferPoolSize;}
	virtual void SetFreeBufferPoolHold	(DWORD dwFreeBufferPoolHold)		{ENSURE_HAS_STOPPED(); m_dwFreeBufferPoolHold	= dwFreeBufferPoolHold;}
	virtual void SetNoDelay				(BOOL bNoDelay)						{ENSURE_HAS_STOPPED(); m_bNoDelay				= bNoDelay;}
	virtual void SetExtra				(PVOID pExtra)						{m_pExtra										= pExtra;}						

	virtual EnReuseAddressPolicy GetReuseAddressPolicy	()	{return m_enReusePolicy;}
	virtual DWORD GetSyncConnectTimeout	()	{return m_dwSyncConnectTimeout;}
	virtual DWORD GetSocketBufferSize	()	{return m_dwSocketBufferSize;}
	virtual DWORD GetKeepAliveTime		()	{return m_dwKeepAliveTime;}
	virtual DWORD GetKeepAliveInterval	()	{return m_dwKeepAliveInterval;}
	virtual DWORD GetFreeBufferPoolSize	()	{return m_dwFreeBufferPoolSize;}
	virtual DWORD GetFreeBufferPoolHold	()	{return m_dwFreeBufferPoolHold;}
	virtual BOOL  IsNoDelay				()	{return m_bNoDelay;}
	virtual PVOID GetExtra				()	{return m_pExtra;}

protected:
	virtual EnHandleResult FirePrepareConnect(SOCKET socket)
		{return DoFirePrepareConnect(this, socket);}
	virtual EnHandleResult FireConnect()
		{
			EnHandleResult rs		= DoFireConnect(this);
			if(rs != HR_ERROR) rs	= FireHandShake();
			return rs;
		}
	virtual EnHandleResult FireHandShake()
		{return DoFireHandShake(this);}
	virtual EnHandleResult FireSend(const BYTE* pData, int iLength)
		{return DoFireSend(this, pData, iLength);}
	virtual EnHandleResult FireReceive(const BYTE* pData, int iLength)
		{return DoFireReceive(this, pData, iLength);}
	virtual EnHandleResult FireReceive(int iLength)
		{return DoFireReceive(this, iLength);}
	virtual EnHandleResult FireClose(EnSocketOperation enOperation, int iErrorCode)
		{return DoFireClose(this, enOperation, iErrorCode);}

	virtual EnHandleResult DoFirePrepareConnect(ITcpClient* pSender, SOCKET socket)
		{return m_pListener->OnPrepareConnect(pSender, pSender->GetConnectionID(), socket);}
	virtual EnHandleResult DoFireConnect(ITcpClient* pSender)
		{return m_pListener->OnConnect(pSender, pSender->GetConnectionID());}
	virtual EnHandleResult DoFireHandShake(ITcpClient* pSender)
		{return m_pListener->OnHandShake(pSender, pSender->GetConnectionID());}
	virtual EnHandleResult DoFireSend(ITcpClient* pSender, const BYTE* pData, int iLength)
		{return m_pListener->OnSend(pSender, pSender->GetConnectionID(), pData, iLength);}
	virtual EnHandleResult DoFireReceive(ITcpClient* pSender, const BYTE* pData, int iLength)
		{return m_pListener->OnReceive(pSender, pSender->GetConnectionID(), pData, iLength);}
	virtual EnHandleResult DoFireReceive(ITcpClient* pSender, int iLength)
		{return m_pListener->OnReceive(pSender, pSender->GetConnectionID(), iLength);}
	virtual EnHandleResult DoFireClose(ITcpClient* pSender, EnSocketOperation enOperation, int iErrorCode)
		{return m_pListener->OnClose(pSender, pSender->GetConnectionID(), enOperation, iErrorCode);}

	void SetLastError(EnSocketError code, LPCSTR func, int ec);
	virtual BOOL CheckParams();
	virtual void PrepareStart();
	virtual void Reset();

	virtual BOOL BeforeUnpause() {return TRUE;}

	virtual void OnWorkerThreadStart(THR_ID dwThreadID) {}
	virtual void OnWorkerThreadEnd(THR_ID dwThreadID) {}

	BOOL DoSendPackets(const WSABUF pBuffers[], int iCount);

	static BOOL DoSendPackets(CTcpClient* pClient, const WSABUF pBuffers[], int iCount)
		{return pClient->DoSendPackets(pBuffers, iCount);}

protected:
	BOOL IsPaused		()					{return m_bPaused;}
	void SetReserved	(PVOID pReserved)	{m_pReserved = pReserved;}						
	PVOID GetReserved	()					{return m_pReserved;}
	BOOL GetRemoteHost	(LPCSTR* lpszHost, USHORT* pusPort = nullptr);

private:
	void SetRemoteHost	(LPCTSTR lpszHost, USHORT usPort);
	void SetConnected	(BOOL bConnected = TRUE) {m_bConnected = bConnected; if(bConnected) m_enState = SS_STARTED;}

	BOOL CheckStarting();
	BOOL CheckStoping(DWORD dwCurrentThreadID);
	BOOL CreateClientSocket(LPCTSTR lpszRemoteAddress, HP_SOCKADDR& addrRemote, USHORT usPort, LPCTSTR lpszBindAddress, HP_SOCKADDR& addrBind);
	BOOL BindClientSocket(const HP_SOCKADDR& addrBind, const HP_SOCKADDR& addrRemote, USHORT usLocalPort);
	BOOL ConnectToServer(const HP_SOCKADDR& addrRemote, BOOL bAsyncConnect);
	BOOL CreateWorkerThread();
	BOOL ProcessNetworkEvent();
	BOOL ReadData();
	BOOL SendData();
	BOOL DoSendData(TItem* pItem, BOOL& bBlocked);
	TItem* GetSendBuffer();
	int SendInternal(const WSABUF pBuffers[], int iCount);
	void WaitForWorkerThreadEnd(DWORD dwCurrentThreadID);

	BOOL HandleError	(WSANETWORKEVENTS& events);
	BOOL HandleRead		(WSANETWORKEVENTS& events);
	BOOL HandleWrite	(WSANETWORKEVENTS& events);
	BOOL HandleConnect	(WSANETWORKEVENTS& events);
	BOOL HandleClose	(WSANETWORKEVENTS& events);

	static UINT WINAPI WorkerThreadProc(LPVOID pv);

public:
	CTcpClient(ITcpClientListener* pListener)
	: m_pListener			(pListener)
	, m_lsSend				(m_itPool)
	, m_soClient			(INVALID_SOCKET)
	, m_evSocket			(nullptr)
	, m_dwConnID			(0)
	, m_usPort				(0)
	, m_hWorker				(nullptr)
	, m_dwWorkerID			(0)
	, m_bPaused				(FALSE)
	, m_iPending			(0)
	, m_bConnected			(FALSE)
	, m_enLastError			(SE_OK)
	, m_enState				(SS_STOPPED)
	, m_bNoDelay			(FALSE)
	, m_pExtra				(nullptr)
	, m_pReserved			(nullptr)
	, m_enReusePolicy		(RAP_ADDR_ONLY)
	, m_dwSyncConnectTimeout(DEFAULT_SYNC_CONNECT_TIMEOUT)
	, m_dwSocketBufferSize	(DEFAULT_TCP_SOCKET_BUFFER_SIZE)
	, m_dwFreeBufferPoolSize(DEFAULT_CLIENT_FREE_BUFFER_POOL_SIZE)
	, m_dwFreeBufferPoolHold(DEFAULT_CLIENT_FREE_BUFFER_POOL_HOLD)
	, m_dwKeepAliveTime		(DEFALUT_TCP_KEEPALIVE_TIME)
	, m_dwKeepAliveInterval	(DEFALUT_TCP_KEEPALIVE_INTERVAL)
	, m_evWait				(TRUE, TRUE)
	{
		ASSERT(sm_wsSocket.IsValid());
		ASSERT(m_pListener);
	}

	virtual ~CTcpClient()
	{
		ENSURE_STOP();
	}

private:
	static const CInitSocket sm_wsSocket;

private:
	CEvt				m_evWait;

	ITcpClientListener*	m_pListener;
	TClientCloseContext m_ccContext;

	SOCKET				m_soClient;
	HANDLE				m_evSocket;
	CONNID				m_dwConnID;


	EnReuseAddressPolicy m_enReusePolicy;
	DWORD				m_dwSyncConnectTimeout;
	DWORD				m_dwSocketBufferSize;
	DWORD				m_dwFreeBufferPoolSize;
	DWORD				m_dwFreeBufferPoolHold;
	DWORD				m_dwKeepAliveTime;
	DWORD				m_dwKeepAliveInterval;
	BOOL				m_bNoDelay;

	HANDLE				m_hWorker;
	UINT				m_dwWorkerID;

	EnSocketError		m_enLastError;
	volatile BOOL		m_bConnected;
	volatile EnServiceState	m_enState;

	PVOID				m_pExtra;
	PVOID				m_pReserved;

	CBufferPtr			m_rcBuffer;

protected:
	CStringA			m_strHost;
	USHORT				m_usPort;

	CItemPool			m_itPool;

private:
	CSpinGuard			m_csState;

	CCriSec				m_csSend;
	TItemList			m_lsSend;

	CEvt				m_evBuffer;
	CEvt				m_evWorker;
	CEvt				m_evUnpause;

	volatile int		m_iPending;
	volatile BOOL		m_bPaused;
};


/* ========================================================================== */
/*  TcpPullClient.h  -- CTcpPullClientT
/*  source: Windows\Src\TcpPullClient.h
/* ========================================================================== */

#pragma once

/* [amalgamated] #include "TcpClient.h" */
/* [amalgamated] #include "MiscHelper.h" */
/* [amalgamated] #include "Common/BufferPool.h" */

template<class T> class CTcpPullClientT : public IPullClient, public T
{
public:
	virtual EnFetchResult Fetch(BYTE* pData, int iLength)
	{
		return ::FetchBuffer(&m_lsBuffer, pData, iLength);
	}

	virtual EnFetchResult Peek(BYTE* pData, int iLength)
	{
		return ::PeekBuffer(&m_lsBuffer, pData, iLength);
	}

protected:
	virtual EnHandleResult DoFireReceive(ITcpClient* pSender, const BYTE* pData, int iLength)
	{
		m_lsBuffer.Cat(pData, iLength);

		return __super::DoFireReceive(pSender, m_lsBuffer.Length());
	}

	virtual void Reset()
	{
		m_lsBuffer.Clear();

		__super::Reset();
	}

public:
	CTcpPullClientT(ITcpClientListener* pListener)
	: T			(pListener)
	, m_lsBuffer(m_itPool)
	{

	}

	virtual ~CTcpPullClientT()
	{
		ENSURE_STOP();
	}

private:
	TItemListEx	m_lsBuffer;
};

typedef CTcpPullClientT<CTcpClient> CTcpPullClient;

#ifdef _SSL_SUPPORT

/* [amalgamated] #include "SSLClient.h" */
typedef CTcpPullClientT<CSSLClient> CSSLPullClient;

#endif


/* ========================================================================== */
/*  TcpPackClient.h  -- CTcpPackClientT
/*  source: Windows\Src\TcpPackClient.h
/* ========================================================================== */

#pragma once

/* [amalgamated] #include "TcpClient.h" */
/* [amalgamated] #include "MiscHelper.h" */

template<class T> class CTcpPackClientT : public IPackClient, public T
{
public:
	virtual BOOL SendPackets(const WSABUF pBuffers[], int iCount)
	{
		int iNewCount = iCount + 1;
		unique_ptr<WSABUF[]> buffers(new WSABUF[iNewCount]);

		DWORD dwHeader;
		if(!::AddPackHeader(pBuffers, iCount, buffers, m_dwMaxPackSize, m_usHeaderFlag, dwHeader))
			return FALSE;

		return __super::SendPackets(buffers.get(), iNewCount);
	}

protected:
	virtual EnHandleResult DoFireReceive(ITcpClient* pSender, const BYTE* pData, int iLength)
	{
		return ParsePack(this, &m_pkInfo, &m_lsBuffer, (CTcpPackClientT*)pSender, m_dwMaxPackSize, m_usHeaderFlag, pData, iLength);
	}

	virtual BOOL BeforeUnpause()
	{
		return (ParsePack(this, &m_pkInfo, &m_lsBuffer, (CTcpPackClientT*)this, m_dwMaxPackSize, m_usHeaderFlag) != HR_ERROR);
	}

	virtual BOOL CheckParams()
	{
		if	((m_dwMaxPackSize > 0 && m_dwMaxPackSize <= TCP_PACK_MAX_SIZE_LIMIT)	&&
			(m_usHeaderFlag >= 0 && m_usHeaderFlag <= TCP_PACK_HEADER_FLAG_LIMIT)	)
			return __super::CheckParams();

		SetLastError(SE_INVALID_PARAM, __FUNCTION__, ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	virtual void Reset()
	{
		m_lsBuffer.Clear();
		m_pkInfo.Reset();

		__super::Reset();
	}

public:
	virtual void SetMaxPackSize		(DWORD dwMaxPackSize)		{ENSURE_HAS_STOPPED(); m_dwMaxPackSize = dwMaxPackSize;}
	virtual void SetPackHeaderFlag	(USHORT usPackHeaderFlag)	{ENSURE_HAS_STOPPED(); m_usHeaderFlag  = usPackHeaderFlag;}
	virtual DWORD GetMaxPackSize	()							{return m_dwMaxPackSize;}
	virtual USHORT GetPackHeaderFlag()							{return m_usHeaderFlag;}

private:
	EnHandleResult DoFireSuperReceive(ITcpClient* pSender, const BYTE* pData, int iLength)
		{return __super::DoFireReceive(pSender, pData, iLength);}

	friend EnHandleResult ParsePack<>	(CTcpPackClientT* pThis, TPackInfo<TItemListEx>* pInfo, TItemListEx* pBuffer, CTcpPackClientT* pSocket,
										DWORD dwMaxPackSize, USHORT usPackHeaderFlag);

public:
	CTcpPackClientT(ITcpClientListener* pListener)
	: T					(pListener)
	, m_dwMaxPackSize	(TCP_PACK_DEFAULT_MAX_SIZE)
	, m_usHeaderFlag	(TCP_PACK_DEFAULT_HEADER_FLAG)
	, m_pkInfo			(nullptr)
	, m_lsBuffer		(m_itPool)
	{

	}

	virtual ~CTcpPackClientT()
	{
		ENSURE_STOP();
	}

private:
	DWORD	m_dwMaxPackSize;
	USHORT	m_usHeaderFlag;

	TPackInfo<TItemListEx>	m_pkInfo;
	TItemListEx				m_lsBuffer;
};

typedef CTcpPackClientT<CTcpClient> CTcpPackClient;

#ifdef _SSL_SUPPORT

/* [amalgamated] #include "SSLClient.h" */
typedef CTcpPackClientT<CSSLClient> CSSLPackClient;

#endif


/* ========================================================================== */
/*  UdpServer.h  -- CUdpServer
/*  source: Windows\Src\UdpServer.h
/* ========================================================================== */

#pragma once

/* [amalgamated] #include "MiscHelper.h" */
/* [amalgamated] #include "Common/Event.h" */
/* [amalgamated] #include "Common/RWLock.h" */
/* [amalgamated] #include "Common/STLHelper.h" */
/* [amalgamated] #include "Common/RingBuffer.h" */
/* [amalgamated] #include "Common/PrivateHeap.h" */

#ifdef _UDP_SUPPORT

class CUdpServer : public IUdpServer
{
public:
	virtual BOOL Start	(LPCTSTR lpszBindAddress, USHORT usPort);
	virtual BOOL Stop	();
	virtual BOOL Send	(CONNID dwConnID, const BYTE* pBuffer, int iLength, int iOffset = 0);
	virtual BOOL SendPackets	(CONNID dwConnID, const WSABUF pBuffers[], int iCount);
	virtual BOOL PauseReceive	(CONNID dwConnID, BOOL bPause = TRUE);
	virtual BOOL Wait			(DWORD dwMilliseconds = INFINITE) {return m_evWait.Wait(dwMilliseconds);}
	virtual BOOL			HasStarted					()	{return m_enState == SS_STARTED || m_enState == SS_STARTING;}
	virtual EnServiceState	GetState					()	{return m_enState;}
	virtual BOOL			Disconnect					(CONNID dwConnID, BOOL bForce = TRUE);
	virtual BOOL			DisconnectLongConnections	(DWORD dwPeriod, BOOL bForce = TRUE);
	virtual BOOL			DisconnectSilenceConnections(DWORD dwPeriod, BOOL bForce = TRUE);
	virtual BOOL			GetListenAddress			(TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort);
	virtual BOOL			GetLocalAddress				(CONNID dwConnID, TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort);
	virtual BOOL			GetRemoteAddress			(CONNID dwConnID, TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort);

	virtual BOOL IsConnected			(CONNID dwConnID);
	virtual BOOL IsPauseReceive			(CONNID dwConnID, BOOL& bPaused);
	virtual BOOL GetPendingDataLength	(CONNID dwConnID, int& iPending);
	virtual DWORD GetConnectionCount	();
	virtual BOOL GetAllConnectionIDs	(CONNID pIDs[], DWORD& dwCount);
	virtual BOOL GetConnectPeriod		(CONNID dwConnID, DWORD& dwPeriod);
	virtual BOOL GetSilencePeriod		(CONNID dwConnID, DWORD& dwPeriod);
	virtual EnSocketError GetLastError	()	{return m_enLastError;}
	virtual LPCTSTR GetLastErrorDesc	()	{return ::GetSocketErrorDesc(m_enLastError);}

public:
	virtual BOOL IsSecure				() {return FALSE;}

	virtual BOOL SetConnectionExtra(CONNID dwConnID, PVOID pExtra);
	virtual BOOL GetConnectionExtra(CONNID dwConnID, PVOID* ppExtra);

	virtual void SetReuseAddressPolicy		(EnReuseAddressPolicy enReusePolicy)	{ENSURE_HAS_STOPPED(); m_enReusePolicy		= enReusePolicy;}
	virtual void SetSendPolicy				(EnSendPolicy enSendPolicy)				{ENSURE_HAS_STOPPED(); m_enSendPolicy		= enSendPolicy;}
	virtual void SetOnSendSyncPolicy		(EnOnSendSyncPolicy enOnSendSyncPolicy)	{ENSURE_HAS_STOPPED(); m_enOnSendSyncPolicy	= enOnSendSyncPolicy;}
	virtual void SetMaxConnectionCount		(DWORD dwMaxConnectionCount)	{ENSURE_HAS_STOPPED(); m_dwMaxConnectionCount		= dwMaxConnectionCount;}
	virtual void SetWorkerThreadCount		(DWORD dwWorkerThreadCount)		{ENSURE_HAS_STOPPED(); m_dwWorkerThreadCount		= dwWorkerThreadCount;}
	virtual void SetFreeSocketObjLockTime	(DWORD dwFreeSocketObjLockTime)	{ENSURE_HAS_STOPPED(); m_dwFreeSocketObjLockTime	= dwFreeSocketObjLockTime;}
	virtual void SetFreeSocketObjPool		(DWORD dwFreeSocketObjPool)		{ENSURE_HAS_STOPPED(); m_dwFreeSocketObjPool		= dwFreeSocketObjPool;}
	virtual void SetFreeBufferObjPool		(DWORD dwFreeBufferObjPool)		{ENSURE_HAS_STOPPED(); m_dwFreeBufferObjPool		= dwFreeBufferObjPool;}
	virtual void SetFreeSocketObjHold		(DWORD dwFreeSocketObjHold)		{ENSURE_HAS_STOPPED(); m_dwFreeSocketObjHold		= dwFreeSocketObjHold;}
	virtual void SetFreeBufferObjHold		(DWORD dwFreeBufferObjHold)		{ENSURE_HAS_STOPPED(); m_dwFreeBufferObjHold		= dwFreeBufferObjHold;}
	virtual void SetMaxDatagramSize			(DWORD dwMaxDatagramSize)		{ENSURE_HAS_STOPPED(); m_dwMaxDatagramSize			= dwMaxDatagramSize;}
	virtual void SetPostReceiveCount		(DWORD dwPostReceiveCount)		{ENSURE_HAS_STOPPED(); m_dwPostReceiveCount			= dwPostReceiveCount;}
	virtual void SetDetectAttempts			(DWORD dwDetectAttempts)		{ENSURE_HAS_STOPPED(); m_dwDetectAttempts			= dwDetectAttempts;}
	virtual void SetDetectInterval			(DWORD dwDetectInterval)		{ENSURE_HAS_STOPPED(); m_dwDetectInterval			= dwDetectInterval;}
	virtual void SetMarkSilence				(BOOL bMarkSilence)				{ENSURE_HAS_STOPPED(); m_bMarkSilence				= bMarkSilence;}
	virtual void SetDualStack				(BOOL bDualStack)				{ENSURE_HAS_STOPPED(); m_bDualStack					= bDualStack;}

	virtual EnReuseAddressPolicy GetReuseAddressPolicy	()	{return m_enReusePolicy;}
	virtual EnSendPolicy GetSendPolicy					()	{return m_enSendPolicy;}
	virtual EnOnSendSyncPolicy GetOnSendSyncPolicy		()	{return m_enOnSendSyncPolicy;}
	virtual DWORD GetMaxConnectionCount		()	{return m_dwMaxConnectionCount;}
	virtual DWORD GetWorkerThreadCount		()	{return m_dwWorkerThreadCount;}
	virtual DWORD GetFreeSocketObjLockTime	()	{return m_dwFreeSocketObjLockTime;}
	virtual DWORD GetFreeSocketObjPool		()	{return m_dwFreeSocketObjPool;}
	virtual DWORD GetFreeBufferObjPool		()	{return m_dwFreeBufferObjPool;}
	virtual DWORD GetFreeSocketObjHold		()	{return m_dwFreeSocketObjHold;}
	virtual DWORD GetFreeBufferObjHold		()	{return m_dwFreeBufferObjHold;}
	virtual DWORD GetMaxDatagramSize		()	{return m_dwMaxDatagramSize;}
	virtual DWORD GetPostReceiveCount		()	{return m_dwPostReceiveCount;}
	virtual DWORD GetDetectAttempts			()	{return m_dwDetectAttempts;}
	virtual DWORD GetDetectInterval			()	{return m_dwDetectInterval;}
	virtual BOOL  IsMarkSilence				()	{return m_bMarkSilence;}
	virtual BOOL IsDualStack				()	{return m_bDualStack;}

protected:
	virtual EnHandleResult FirePrepareListen(SOCKET soListen)
		{return DoFirePrepareListen(soListen);}
	virtual EnHandleResult FireAccept(TUdpSocketObj* pSocketObj)
		{
			EnHandleResult rs		= DoFireAccept(pSocketObj);
			if(rs != HR_ERROR) rs	= FireHandShake(pSocketObj);
			return rs;
		}
	virtual EnHandleResult FireHandShake(TUdpSocketObj* pSocketObj)
		{return DoFireHandShake(pSocketObj);}
	virtual EnHandleResult FireReceive(TUdpSocketObj* pSocketObj, const BYTE* pData, int iLength)
		{return DoFireReceive(pSocketObj, pData, iLength);}
	virtual EnHandleResult FireReceive(TUdpSocketObj* pSocketObj, int iLength)
		{return DoFireReceive(pSocketObj, iLength);}
	virtual EnHandleResult FireSend(TUdpSocketObj* pSocketObj, const BYTE* pData, int iLength)
		{return DoFireSend(pSocketObj, pData, iLength);}
	virtual EnHandleResult FireClose(TUdpSocketObj* pSocketObj, EnSocketOperation enOperation, int iErrorCode)
		{return DoFireClose(pSocketObj, enOperation, iErrorCode);}
	virtual EnHandleResult FireShutdown()
		{return DoFireShutdown();}

	virtual EnHandleResult DoFirePrepareListen(SOCKET soListen)
		{return m_pListener->OnPrepareListen(this, soListen);}
	virtual EnHandleResult DoFireAccept(TUdpSocketObj* pSocketObj)
		{return m_pListener->OnAccept(this, pSocketObj->connID, (UINT_PTR)(&pSocketObj->remoteAddr));}
	virtual EnHandleResult DoFireHandShake(TUdpSocketObj* pSocketObj)
		{return m_pListener->OnHandShake(this, pSocketObj->connID);}
	virtual EnHandleResult DoFireReceive(TUdpSocketObj* pSocketObj, const BYTE* pData, int iLength)
		{return m_pListener->OnReceive(this, pSocketObj->connID, pData, iLength);}
	virtual EnHandleResult DoFireReceive(TUdpSocketObj* pSocketObj, int iLength)
		{return m_pListener->OnReceive(this, pSocketObj->connID, iLength);}
	virtual EnHandleResult DoFireSend(TUdpSocketObj* pSocketObj, const BYTE* pData, int iLength)
		{return m_pListener->OnSend(this, pSocketObj->connID, pData, iLength);}
	virtual EnHandleResult DoFireClose(TUdpSocketObj* pSocketObj, EnSocketOperation enOperation, int iErrorCode)
		{return m_pListener->OnClose(this, pSocketObj->connID, enOperation, iErrorCode);}
	virtual EnHandleResult DoFireShutdown()
		{return m_pListener->OnShutdown(this);}

	void SetLastError(EnSocketError code, LPCSTR func, int ec);
	virtual BOOL CheckParams();
	virtual void PrepareStart();
	virtual void Reset();

	virtual void OnWorkerThreadStart(THR_ID dwThreadID) {}
	virtual void OnWorkerThreadEnd(THR_ID dwThreadID) {}

	virtual void ReleaseGCSocketObj(BOOL bForce = FALSE);

	TUdpSocketObj*	FindSocketObj(CONNID dwConnID);
	int				SendInternal(TUdpSocketObj* pSocketObj, TUdpBufferObjPtr& bufPtr);

	BOOL DoSend(TUdpSocketObj* pSocketObj, const BYTE* pBuffer, int iLength, int iOffset = 0);

private:
	EnHandleResult TriggerFireAccept(TUdpSocketObj* pSocketObj);
	EnHandleResult TriggerFireReceive(TUdpSocketObj* pSocketObj, TUdpBufferObj* pBufferObj);
	EnHandleResult TriggerFireSend(TUdpSocketObj* pSocketObj, TUdpBufferObj* pBufferObj);
	EnHandleResult TriggerFireClose(TUdpSocketObj* pSocketObj, EnSocketOperation enOperation, int iErrorCode);

protected:
	BOOL SetConnectionExtra(TUdpSocketObj* pSocketObj, PVOID pExtra);
	BOOL GetConnectionExtra(TUdpSocketObj* pSocketObj, PVOID* ppExtra);
	BOOL SetConnectionReserved(CONNID dwConnID, PVOID pReserved);
	BOOL GetConnectionReserved(CONNID dwConnID, PVOID* ppReserved);
	BOOL SetConnectionReserved(TUdpSocketObj* pSocketObj, PVOID pReserved);
	BOOL GetConnectionReserved(TUdpSocketObj* pSocketObj, PVOID* ppReserved);
	BOOL SetConnectionReserved2(CONNID dwConnID, PVOID pReserved2);
	BOOL GetConnectionReserved2(CONNID dwConnID, PVOID* ppReserved2);
	BOOL SetConnectionReserved2(TUdpSocketObj* pSocketObj, PVOID pReserved2);
	BOOL GetConnectionReserved2(TUdpSocketObj* pSocketObj, PVOID* ppReserved2);

private:
	friend void ContinueReceiveFrom<>(CUdpServer* pThis, TUdpBufferObj* pBufferObj);
	
	static UINT WINAPI WorkerThreadProc(LPVOID pv);
	static void WINAPI DetectConnectionProc(LPVOID pv, BOOLEAN bTimerFired);
	static void WINAPI GCProc(LPVOID pv, BOOLEAN bTimerFired);

private:
	BOOL CheckStarting();
	BOOL CheckStoping();
	BOOL CreateListenSocket(LPCTSTR lpszBindAddress, USHORT usPort);
	BOOL CreateCompletePort();
	BOOL CreateWorkerThreads();
	BOOL StartAccept();

	void SendCloseNotify();
	void CloseListenSocket();
	void WaitForPostReceiveRelease();
	void DisconnectClientSocket();
	void WaitForClientSocketClose();
	void ReleaseClientSocket();
	void ReleaseFreeSocket();
	void ReleaseFreeBuffer();
	void WaitForWorkerThreadEnd();
	void CloseCompletePort();

	TUdpBufferObj*	GetFreeBufferObj(int iLen = -1);
	TUdpSocketObj*	GetFreeSocketObj(CONNID dwConnID);
	void			AddFreeBufferObj(TUdpBufferObj* pBufferObj);
	void			AddFreeSocketObj(CONNID dwConnID, EnSocketCloseFlag enFlag = SCF_NONE, EnSocketOperation enOperation = SO_UNKNOWN, int iErrorCode = 0, BOOL bNotify = TRUE);
	void			AddFreeSocketObj(TUdpSocketObj* pSocketObj, EnSocketCloseFlag enFlag = SCF_NONE, EnSocketOperation enOperation = SO_UNKNOWN, int iErrorCode = 0, BOOL bNotify = TRUE);
	TUdpSocketObj*	CreateSocketObj();
	void			DeleteSocketObj(TUdpSocketObj* pSocketObj);
	BOOL			InvalidSocketObj(TUdpSocketObj* pSocketObj);

	void			AddClientSocketObj(CONNID dwConnID, TUdpSocketObj* pSocketObj, const HP_SOCKADDR& remoteAddr);
	void			CloseClientSocketObj(TUdpSocketObj* pSocketObj, EnSocketCloseFlag enFlag = SCF_NONE, EnSocketOperation enOperation = SO_UNKNOWN, int iErrorCode = 0, BOOL bNotify = TRUE);

	CONNID			FindConnectionID(const HP_SOCKADDR* pAddr);

private:
	EnIocpAction CheckIocpCommand(OVERLAPPED* pOverlapped, DWORD dwBytes, ULONG_PTR ulCompKey);

	void ForceDisconnect(CONNID dwConnID, BOOL bNotify = FALSE);
	void HandleIo		(CONNID dwConnID, TUdpBufferObj* pBufferObj, DWORD dwBytes, DWORD dwErrorCode);
	void HandleError	(CONNID dwConnID, TUdpBufferObj* pBufferObj, DWORD dwErrorCode);
	void HandleZeroBytes(CONNID dwConnID, TUdpBufferObj* pBufferObj);
	CONNID HandleAccept	(TUdpBufferObj* pBufferObj);
	void HandleSend		(CONNID dwConnID, TUdpBufferObj* pBufferObj);
	void HandleReceive	(CONNID dwConnID, TUdpBufferObj* pBufferObj);
	void ProcessReceive	(CONNID dwConnID, TUdpBufferObj* pBufferObj);
	void ProcessReceiveBufferObj(TUdpBufferObj* pBufferObj);

	int SendPack	(TUdpSocketObj* pSocketObj, TUdpBufferObjPtr& bufPtr);
	int SendSafe	(TUdpSocketObj* pSocketObj, TUdpBufferObjPtr& bufPtr);
	int CatAndPost	(TUdpSocketObj* pSocketObj, TUdpBufferObjPtr& bufPtr);
	int SendDirect	(TUdpSocketObj* pSocketObj, TUdpBufferObjPtr& bufPtr);

	int DoReceive	(TUdpBufferObj* pBufferObj);

	int DoSend		(CONNID dwConnID);
	int DoSendPack	(TUdpSocketObj* pSocketObj);
	int DoSendSafe	(TUdpSocketObj* pSocketObj);
	int SendItem	(TUdpSocketObj* pSocketObj);

	BOOL SendDetectPackage		(CONNID dwConnID, TUdpSocketObj* pSocketObj);
	BOOL IsNeedDetectConnection	()	{return m_dwDetectAttempts > 0 && m_dwDetectInterval > 0;}

	SOCKET GetListenSocket		()	{return m_soListen;}

public:
	CUdpServer(IUdpServerListener* pListener)
	: m_pListener				(pListener)
	, m_hCompletePort			(nullptr)
	, m_soListen				(INVALID_SOCKET)
	, m_iRemainPostReceives		(0)
	, m_enLastError				(SE_OK)
	, m_enState					(SS_STOPPED)
	, m_usFamily				(AF_UNSPEC)
	, m_enSendPolicy			(SP_PACK)
	, m_enOnSendSyncPolicy		(OSSP_NONE)
	, m_enReusePolicy			(RAP_ADDR_ONLY)
	, m_dwMaxConnectionCount	(DEFAULT_CONNECTION_COUNT)
	, m_dwWorkerThreadCount		(DEFAULT_WORKER_THREAD_COUNT)
	, m_dwFreeSocketObjLockTime	(DEFAULT_FREE_SOCKETOBJ_LOCK_TIME)
	, m_dwFreeSocketObjPool		(DEFAULT_FREE_SOCKETOBJ_POOL)
	, m_dwFreeBufferObjPool		(DEFAULT_FREE_BUFFEROBJ_POOL)
	, m_dwFreeSocketObjHold		(DEFAULT_FREE_SOCKETOBJ_HOLD)
	, m_dwFreeBufferObjHold		(DEFAULT_FREE_BUFFEROBJ_HOLD)
	, m_dwMaxDatagramSize		(DEFAULT_UDP_MAX_DATAGRAM_SIZE)
	, m_dwPostReceiveCount		(DEFAULT_UDP_POST_RECEIVE_COUNT)
	, m_dwDetectAttempts		(DEFAULT_UDP_DETECT_ATTEMPTS)
	, m_dwDetectInterval		(DEFAULT_UDP_DETECT_INTERVAL)
	, m_bMarkSilence			(TRUE)
	, m_bDualStack				(TRUE)
	, m_evWait					(TRUE, TRUE)
	{
		ASSERT(sm_wsSocket.IsValid());
		ASSERT(m_pListener);
	}

	virtual ~CUdpServer()
	{
		ENSURE_STOP();
	}

private:
	EnReuseAddressPolicy m_enReusePolicy;
	EnSendPolicy m_enSendPolicy;
	EnOnSendSyncPolicy m_enOnSendSyncPolicy;
	DWORD m_dwMaxConnectionCount;
	DWORD m_dwWorkerThreadCount;
	DWORD m_dwFreeSocketObjLockTime;
	DWORD m_dwFreeSocketObjPool;
	DWORD m_dwFreeBufferObjPool;
	DWORD m_dwFreeSocketObjHold;
	DWORD m_dwFreeBufferObjHold;
	DWORD m_dwMaxDatagramSize;
	DWORD m_dwPostReceiveCount;
	DWORD m_dwDetectAttempts;
	DWORD m_dwDetectInterval;
	BOOL  m_bMarkSilence;
	BOOL  m_bDualStack;

protected:
	CUdpBufferObjPool		m_bfObjPool;

private:
	static const CInitSocket sm_wsSocket;

	CEvt					m_evWait;

	ADDRESS_FAMILY			m_usFamily;

	IUdpServerListener*		m_pListener;
	SOCKET					m_soListen;
	HANDLE					m_hCompletePort;
	EnServiceState			m_enState;
	EnSocketError			m_enLastError;

	vector<HANDLE>			m_vtWorkerThreads;

	CPrivateHeap			m_phSocket;

	CSpinGuard				m_csState;

	CCriSec					m_csAccept;

	CGCTimerQueue			m_tqGC;
	CTimerQueue				m_tqDetect;

	TUdpSocketObjPtrPool	m_bfActiveSockets;

	CSimpleRWLock			m_csClientSocket;
	TSockAddrMap			m_mpClientAddr;

	TUdpSocketObjPtrList	m_lsFreeSocket;
	TUdpSocketObjPtrQueue	m_lsGCSocket;

	volatile long			m_iRemainPostReceives;
};

#endif


/* ========================================================================== */
/*  UdpClient.h  -- CUdpClient
/*  source: Windows\Src\UdpClient.h
/* ========================================================================== */

#pragma once

/* [amalgamated] #include "SocketHelper.h" */

#ifdef _UDP_SUPPORT

class CUdpClient : public IUdpClient
{
public:
	virtual BOOL Start	(LPCTSTR lpszRemoteAddress, USHORT usPort, BOOL bAsyncConnect = TRUE, LPCTSTR lpszBindAddress = nullptr, USHORT usLocalPort = 0);
	virtual BOOL Stop	();
	virtual BOOL Send	(const BYTE* pBuffer, int iLength, int iOffset = 0)	{return DoSend(pBuffer, iLength, iOffset);}
	virtual BOOL SendPackets	(const WSABUF pBuffers[], int iCount);
	virtual BOOL PauseReceive	(BOOL bPause = TRUE);
	virtual BOOL Wait			(DWORD dwMilliseconds = INFINITE) {return m_evWait.Wait(dwMilliseconds);}
	virtual BOOL			HasStarted			()	{return m_enState == SS_STARTED || m_enState == SS_STARTING;}
	virtual EnServiceState	GetState			()	{return m_enState;}
	virtual CONNID			GetConnectionID		()	{return m_dwConnID;}
	virtual EnSocketError	GetLastError		()	{return m_enLastError;}
	virtual LPCTSTR			GetLastErrorDesc	()	{return ::GetSocketErrorDesc(m_enLastError);}

	virtual BOOL GetLocalAddress		(TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort);
	virtual BOOL GetRemoteHost			(TCHAR lpszHost[], int& iHostLen, USHORT& usPort);
	virtual BOOL GetPendingDataLength	(int& iPending) {iPending = m_iPending; return HasStarted();}
	virtual BOOL IsPauseReceive			(BOOL& bPaused) {bPaused = m_bPaused; return HasStarted();}
	virtual BOOL IsConnected			()				{return m_bConnected;}

public:
	virtual BOOL IsSecure				() {return FALSE;}

	virtual void SetReuseAddressPolicy	(EnReuseAddressPolicy enReusePolicy){ENSURE_HAS_STOPPED(); m_enReusePolicy			= enReusePolicy;}
	virtual void SetMaxDatagramSize		(DWORD dwMaxDatagramSize)			{ENSURE_HAS_STOPPED(); m_dwMaxDatagramSize		= dwMaxDatagramSize;}
	virtual void SetDetectAttempts		(DWORD dwDetectAttempts)			{ENSURE_HAS_STOPPED(); m_dwDetectAttempts		= dwDetectAttempts;}
	virtual void SetDetectInterval		(DWORD dwDetectInterval)			{ENSURE_HAS_STOPPED(); m_dwDetectInterval		= dwDetectInterval;}
	virtual void SetFreeBufferPoolSize	(DWORD dwFreeBufferPoolSize)		{ENSURE_HAS_STOPPED(); m_dwFreeBufferPoolSize	= dwFreeBufferPoolSize;}
	virtual void SetFreeBufferPoolHold	(DWORD dwFreeBufferPoolHold)		{ENSURE_HAS_STOPPED(); m_dwFreeBufferPoolHold	= dwFreeBufferPoolHold;}
	virtual void SetExtra				(PVOID pExtra)						{m_pExtra										= pExtra;}						


	virtual EnReuseAddressPolicy GetReuseAddressPolicy	()	{return m_enReusePolicy;}
	virtual DWORD GetMaxDatagramSize	()	{return m_dwMaxDatagramSize;}
	virtual DWORD GetDetectAttempts		()	{return m_dwDetectAttempts;}
	virtual DWORD GetDetectInterval		()	{return m_dwDetectInterval;}
	virtual DWORD GetFreeBufferPoolSize	()	{return m_dwFreeBufferPoolSize;}
	virtual DWORD GetFreeBufferPoolHold	()	{return m_dwFreeBufferPoolHold;}
	virtual PVOID GetExtra				()	{return m_pExtra;}

protected:
	virtual EnHandleResult FirePrepareConnect(SOCKET socket)
		{return DoFirePrepareConnect(this, socket);}
	virtual EnHandleResult FireConnect()
		{
			EnHandleResult rs		= DoFireConnect(this);
			if(rs != HR_ERROR) rs	= FireHandShake();
			return rs;
		}
	virtual EnHandleResult FireHandShake()
		{return DoFireHandShake(this);}
	virtual EnHandleResult FireSend(const BYTE* pData, int iLength)
		{return DoFireSend(this, pData, iLength);}
	virtual EnHandleResult FireReceive(const BYTE* pData, int iLength)
		{return DoFireReceive(this, pData, iLength);}
	virtual EnHandleResult FireReceive(int iLength)
		{return DoFireReceive(this, iLength);}
	virtual EnHandleResult FireClose(EnSocketOperation enOperation, int iErrorCode)
		{return DoFireClose(this, enOperation, iErrorCode);}

	virtual EnHandleResult DoFirePrepareConnect(IUdpClient* pSender, SOCKET socket)
		{return m_pListener->OnPrepareConnect(pSender, pSender->GetConnectionID(), socket);}
	virtual EnHandleResult DoFireConnect(IUdpClient* pSender)
		{return m_pListener->OnConnect(pSender, pSender->GetConnectionID());}
	virtual EnHandleResult DoFireHandShake(IUdpClient* pSender)
		{return m_pListener->OnHandShake(pSender, pSender->GetConnectionID());}
	virtual EnHandleResult DoFireSend(IUdpClient* pSender, const BYTE* pData, int iLength)
		{return m_pListener->OnSend(pSender, pSender->GetConnectionID(), pData, iLength);}
	virtual EnHandleResult DoFireReceive(IUdpClient* pSender, const BYTE* pData, int iLength)
		{return m_pListener->OnReceive(pSender, pSender->GetConnectionID(), pData, iLength);}
	virtual EnHandleResult DoFireReceive(IUdpClient* pSender, int iLength)
		{return m_pListener->OnReceive(pSender, pSender->GetConnectionID(), iLength);}
	virtual EnHandleResult DoFireClose(IUdpClient* pSender, EnSocketOperation enOperation, int iErrorCode)
		{return m_pListener->OnClose(pSender, pSender->GetConnectionID(), enOperation, iErrorCode);}

	void SetLastError(EnSocketError code, LPCSTR func, int ec);
	virtual BOOL CheckParams();
	virtual void PrepareStart();
	virtual void Reset();

	virtual void OnWorkerThreadStart(THR_ID dwThreadID) {}
	virtual void OnWorkerThreadEnd(THR_ID dwThreadID) {}

	virtual HANDLE GetUserEvent() {return nullptr;}
	virtual BOOL OnUserEvent() {return TRUE;}

	static BOOL DoSend(CUdpClient* pClient, const BYTE* pBuffer, int iLength, int iOffset = 0)
		{return pClient->DoSend(pBuffer, iLength, iOffset);}

protected:
	void SetReserved	(PVOID pReserved)	{m_pReserved = pReserved;}						
	PVOID GetReserved	()					{return m_pReserved;}
	BOOL GetRemoteHost	(LPCSTR* lpszHost, USHORT* pusPort = nullptr);

private:
	BOOL DoSend			(const BYTE* pBuffer, int iLength, int iOffset = 0);

	void SetRemoteHost	(LPCTSTR lpszHost, USHORT usPort);
	void SetConnected	(BOOL bConnected = TRUE) {m_bConnected = bConnected; if(bConnected) m_enState = SS_STARTED;}

	BOOL CheckStarting();
	BOOL CheckStoping(DWORD dwCurrentThreadID);
	BOOL CreateClientSocket(LPCTSTR lpszRemoteAddress, HP_SOCKADDR& addrRemote, USHORT usPort, LPCTSTR lpszBindAddress, HP_SOCKADDR& addrBind);
	BOOL BindClientSocket(const HP_SOCKADDR& addrBind, const HP_SOCKADDR& addrRemote, USHORT usLocalPort);
	BOOL ConnectToServer(const HP_SOCKADDR& addrRemote, BOOL bAsyncConnect);
	BOOL CreateWorkerThread();
	BOOL ProcessNetworkEvent();
	BOOL ReadData();
	BOOL SendData();
	TItem* GetSendBuffer();
	int SendInternal(TItemPtr& itPtr);
	void WaitForWorkerThreadEnd(DWORD dwCurrentThreadID);
	void CheckConnected();

	BOOL HandleError(WSANETWORKEVENTS& events);
	BOOL HandleRead(WSANETWORKEVENTS& events);
	BOOL HandleWrite(WSANETWORKEVENTS& events);
	BOOL HandleConnect(WSANETWORKEVENTS& events);
	BOOL HandleClose(WSANETWORKEVENTS& events);

	BOOL CheckConnection();
	int DetectConnection();
	BOOL IsNeedDetect	() {return m_dwDetectAttempts > 0 && m_dwDetectInterval > 0;}

	static UINT WINAPI WorkerThreadProc(LPVOID pv);

public:
	CUdpClient(IUdpClientListener* pListener)
	: m_pListener			(pListener)
	, m_lsSend				(m_itPool)
	, m_soClient			(INVALID_SOCKET)
	, m_evSocket			(nullptr)
	, m_dwConnID			(0)
	, m_usPort				(0)
	, m_hWorker				(nullptr)
	, m_dwWorkerID			(0)
	, m_bPaused				(FALSE)
	, m_iPending			(0)
	, m_bConnected			(FALSE)
	, m_enLastError			(SE_OK)
	, m_enState				(SS_STOPPED)
	, m_dwDetectFails		(0)
	, m_pExtra				(nullptr)
	, m_pReserved			(nullptr)
	, m_enReusePolicy		(RAP_ADDR_ONLY)
	, m_dwMaxDatagramSize	(DEFAULT_UDP_MAX_DATAGRAM_SIZE)
	, m_dwFreeBufferPoolSize(DEFAULT_CLIENT_FREE_BUFFER_POOL_SIZE)
	, m_dwFreeBufferPoolHold(DEFAULT_CLIENT_FREE_BUFFER_POOL_HOLD)
	, m_dwDetectAttempts	(DEFAULT_UDP_DETECT_ATTEMPTS)
	, m_dwDetectInterval	(DEFAULT_UDP_DETECT_INTERVAL)
	, m_evWait				(TRUE, TRUE)
	{
		ASSERT(sm_wsSocket.IsValid());
		ASSERT(m_pListener);
	}

	virtual ~CUdpClient()
	{
		ENSURE_STOP();
	}

private:
	static const CInitSocket sm_wsSocket;

private:
	CEvt				m_evWait;

	IUdpClientListener*	m_pListener;
	TClientCloseContext m_ccContext;

	SOCKET				m_soClient;
	HANDLE				m_evSocket;
	CONNID				m_dwConnID;

	EnReuseAddressPolicy m_enReusePolicy;
	DWORD				m_dwMaxDatagramSize;
	DWORD				m_dwFreeBufferPoolSize;
	DWORD				m_dwFreeBufferPoolHold;
	DWORD				m_dwDetectAttempts;
	DWORD				m_dwDetectInterval;

	HANDLE				m_hWorker;
	UINT				m_dwWorkerID;

	EnSocketError		m_enLastError;
	volatile BOOL		m_bConnected;
	volatile EnServiceState	m_enState;

	PVOID				m_pExtra;
	PVOID				m_pReserved;

	CBufferPtr			m_rcBuffer;

protected:
	CStringA			m_strHost;
	USHORT				m_usPort;

	CItemPool			m_itPool;

private:
	CSpinGuard			m_csState;

	CCriSec				m_csSend;
	TItemList			m_lsSend;

	CEvt				m_evBuffer;
	CEvt				m_evWorker;
	CEvt				m_evUnpause;

	volatile int		m_iPending;
	volatile BOOL		m_bPaused;
	volatile DWORD		m_dwDetectFails;
};

#endif


/* ========================================================================== */
/*  UdpArqClient.h  -- CUdpArqClient
/*  source: Windows\Src\UdpArqClient.h
/* ========================================================================== */

#pragma once

/* [amalgamated] #include "UdpClient.h" */
/* [amalgamated] #include "ArqHelper.h" */

#ifdef _UDP_SUPPORT

class CUdpArqClient : public IArqClient, public CUdpClient
{
	typedef CArqSessionT<CUdpArqClient, CUdpArqClient>	CArqSession;
	friend class										CArqSession;

public:
	virtual BOOL Send		(const BYTE* pBuffer, int iLength, int iOffset = 0);
	virtual BOOL SendPackets(const WSABUF pBuffers[], int iCount);

protected:
	virtual EnHandleResult FireConnect();
	virtual EnHandleResult FireReceive(const BYTE* pData, int iLength);

	virtual BOOL CheckParams();
	virtual void PrepareStart();
	virtual void Reset();

	virtual void OnWorkerThreadStart(THR_ID dwThreadID);
	virtual void OnWorkerThreadEnd(THR_ID dwThreadID);

	virtual HANDLE GetUserEvent();
	virtual BOOL OnUserEvent();

public:
	virtual void SetNoDelay				(BOOL bNoDelay)				{ENSURE_HAS_STOPPED(); m_arqAttr.bNoDelay			= bNoDelay;}
	virtual void SetTurnoffCongestCtrl	(BOOL bTurnOff)				{ENSURE_HAS_STOPPED(); m_arqAttr.bTurnoffNc			= bTurnOff;}
	virtual void SetFlushInterval		(DWORD dwFlushInterval)		{ENSURE_HAS_STOPPED(); m_arqAttr.dwFlushInterval	= dwFlushInterval;}
	virtual void SetResendByAcks		(DWORD dwResendByAcks)		{ENSURE_HAS_STOPPED(); m_arqAttr.dwResendByAcks		= dwResendByAcks;}
	virtual void SetSendWndSize			(DWORD dwSendWndSize)		{ENSURE_HAS_STOPPED(); m_arqAttr.dwSendWndSize		= dwSendWndSize;}
	virtual void SetRecvWndSize			(DWORD dwRecvWndSize)		{ENSURE_HAS_STOPPED(); m_arqAttr.dwRecvWndSize		= dwRecvWndSize;}
	virtual void SetMinRto				(DWORD dwMinRto)			{ENSURE_HAS_STOPPED(); m_arqAttr.dwMinRto			= dwMinRto;}
	virtual void SetFastLimit			(DWORD dwFastLimit)			{ENSURE_HAS_STOPPED(); m_arqAttr.dwFastLimit		= dwFastLimit;}
	virtual void SetMaxTransUnit		(DWORD dwMaxTransUnit)		{ENSURE_HAS_STOPPED(); m_dwMtu						= dwMaxTransUnit;}
	virtual void SetMaxMessageSize		(DWORD dwMaxMessageSize)	{ENSURE_HAS_STOPPED(); m_arqAttr.dwMaxMessageSize	= dwMaxMessageSize;}
	virtual void SetHandShakeTimeout	(DWORD dwHandShakeTimeout)	{ENSURE_HAS_STOPPED(); m_arqAttr.dwHandShakeTimeout	= dwHandShakeTimeout;}

	virtual BOOL IsNoDelay				()	{return m_arqAttr.bNoDelay;}
	virtual BOOL IsTurnoffCongestCtrl	()	{return m_arqAttr.bTurnoffNc;}
	virtual DWORD GetFlushInterval		()	{return m_arqAttr.dwFlushInterval;}
	virtual DWORD GetResendByAcks		()	{return m_arqAttr.dwResendByAcks;}
	virtual DWORD GetSendWndSize		()	{return m_arqAttr.dwSendWndSize;}
	virtual DWORD GetRecvWndSize		()	{return m_arqAttr.dwRecvWndSize;}
	virtual DWORD GetMinRto				()	{return m_arqAttr.dwMinRto;}
	virtual DWORD GetFastLimit			()	{return m_arqAttr.dwFastLimit;}
	virtual DWORD GetMaxTransUnit		()	{return m_dwMtu;}
	virtual DWORD GetMaxMessageSize		()	{return m_arqAttr.dwMaxMessageSize;}
	virtual DWORD GetHandShakeTimeout	()	{return m_arqAttr.dwHandShakeTimeout;}

	virtual BOOL GetWaitingSendMessageCount	(int& iCount);

public:
	const TArqAttr& GetArqAttribute		()	{return m_arqAttr;}
	Fn_ArqOutputProc GetArqOutputProc	()	{return ArqOutputProc;}

private:
	static int ArqOutputProc(const char* pBuffer, int iLength, IKCPCB* kcp, LPVOID pv);

public:
	CUdpArqClient(IUdpClientListener* pListener)
	: CUdpClient(pListener)
	, m_dwMtu	(0)
	{

	}

	virtual ~CUdpArqClient()
	{
		ENSURE_STOP();
	}

private:
	DWORD		m_dwMtu;
	TArqAttr	m_arqAttr;

	CBufferPtr	m_arqBuffer;
	CTimerEvt	m_arqTimer;

	CArqSession	m_arqSession;
};

#endif


/* ========================================================================== */
/*  UdpArqServer.h  -- CUdpArqServer
/*  source: Windows\Src\UdpArqServer.h
/* ========================================================================== */

#pragma once

/* [amalgamated] #include "UdpServer.h" */
/* [amalgamated] #include "ArqHelper.h" */

#ifdef _UDP_SUPPORT

/* [amalgamated] #include "Common/STLHelper.h" */

class CUdpArqServer : public IArqSocket, public CUdpServer
{
	typedef CArqSessionT<CUdpArqServer, TUdpSocketObj>		CArqSession;
	typedef CArqSessionExT<CUdpArqServer, TUdpSocketObj>	CArqSessionEx;
	typedef CArqSessionPoolT<CUdpArqServer, TUdpSocketObj>	CArqSessionPool;
	typedef unordered_map<THR_ID, CBufferPtr*>				CRecvBufferMap;

	friend class											CArqSession;

public:
	virtual BOOL Send		(CONNID dwConnID, const BYTE* pBuffer, int iLength, int iOffset = 0);
	virtual BOOL SendPackets(CONNID dwConnID, const WSABUF pBuffers[], int iCount);

protected:
	virtual EnHandleResult FireAccept(TUdpSocketObj* pSocketObj);
	virtual EnHandleResult FireReceive(TUdpSocketObj* pSocketObj, const BYTE* pData, int iLength);
	virtual EnHandleResult FireClose(TUdpSocketObj* pSocketObj, EnSocketOperation enOperation, int iErrorCode);

	virtual BOOL CheckParams();
	virtual void PrepareStart();
	virtual void Reset();
	virtual void OnWorkerThreadStart(THR_ID dwThreadID);

	virtual void ReleaseGCSocketObj(BOOL bForce = FALSE);

public:
	virtual void SetNoDelay				(BOOL bNoDelay)				{ENSURE_HAS_STOPPED(); m_arqAttr.bNoDelay			= bNoDelay;}
	virtual void SetTurnoffCongestCtrl	(BOOL bTurnOff)				{ENSURE_HAS_STOPPED(); m_arqAttr.bTurnoffNc			= bTurnOff;}
	virtual void SetFlushInterval		(DWORD dwFlushInterval)		{ENSURE_HAS_STOPPED(); m_arqAttr.dwFlushInterval	= dwFlushInterval;}
	virtual void SetResendByAcks		(DWORD dwResendByAcks)		{ENSURE_HAS_STOPPED(); m_arqAttr.dwResendByAcks		= dwResendByAcks;}
	virtual void SetSendWndSize			(DWORD dwSendWndSize)		{ENSURE_HAS_STOPPED(); m_arqAttr.dwSendWndSize		= dwSendWndSize;}
	virtual void SetRecvWndSize			(DWORD dwRecvWndSize)		{ENSURE_HAS_STOPPED(); m_arqAttr.dwRecvWndSize		= dwRecvWndSize;}
	virtual void SetMinRto				(DWORD dwMinRto)			{ENSURE_HAS_STOPPED(); m_arqAttr.dwMinRto			= dwMinRto;}
	virtual void SetFastLimit			(DWORD dwFastLimit)			{ENSURE_HAS_STOPPED(); m_arqAttr.dwFastLimit		= dwFastLimit;}
	virtual void SetMaxTransUnit		(DWORD dwMaxTransUnit)		{ENSURE_HAS_STOPPED(); m_dwMtu						= dwMaxTransUnit;}
	virtual void SetMaxMessageSize		(DWORD dwMaxMessageSize)	{ENSURE_HAS_STOPPED(); m_arqAttr.dwMaxMessageSize	= dwMaxMessageSize;}
	virtual void SetHandShakeTimeout	(DWORD dwHandShakeTimeout)	{ENSURE_HAS_STOPPED(); m_arqAttr.dwHandShakeTimeout	= dwHandShakeTimeout;}

	virtual BOOL IsNoDelay				()	{return m_arqAttr.bNoDelay;}
	virtual BOOL IsTurnoffCongestCtrl	()	{return m_arqAttr.bTurnoffNc;}
	virtual DWORD GetFlushInterval		()	{return m_arqAttr.dwFlushInterval;}
	virtual DWORD GetResendByAcks		()	{return m_arqAttr.dwResendByAcks;}
	virtual DWORD GetSendWndSize		()	{return m_arqAttr.dwSendWndSize;}
	virtual DWORD GetRecvWndSize		()	{return m_arqAttr.dwRecvWndSize;}
	virtual DWORD GetMinRto				()	{return m_arqAttr.dwMinRto;}
	virtual DWORD GetFastLimit			()	{return m_arqAttr.dwFastLimit;}
	virtual DWORD GetMaxTransUnit		()	{return m_dwMtu;}
	virtual DWORD GetMaxMessageSize		()	{return m_arqAttr.dwMaxMessageSize;}
	virtual DWORD GetHandShakeTimeout	()	{return m_arqAttr.dwHandShakeTimeout;}

	virtual BOOL GetWaitingSendMessageCount	(CONNID dwConnID, int& iCount);

public:
	const TArqAttr& GetArqAttribute		()	{return m_arqAttr;}
	Fn_ArqOutputProc GetArqOutputProc	()	{return ArqOutputProc;}

private:
	int SendArq(TUdpSocketObj* pSocketObj, const BYTE* pBuffer, int iLength);

	static int ArqOutputProc(const char* pBuffer, int iLength, IKCPCB* kcp, LPVOID pv);

public:
	CUdpArqServer(IUdpServerListener* pListener)
	: CUdpServer(pListener)
	, m_dwMtu	(0)
	{
		
	}

	virtual ~CUdpArqServer()
	{
		ENSURE_STOP();
	}

private:
	static const CTimePeriod sm_tmPeriod;

private:
	DWORD			m_dwMtu;
	TArqAttr		m_arqAttr;

	CCriSec			m_csRcBuffers;
	CRecvBufferMap	m_rcBuffers;

	CArqSessionPool m_ssPool;
};

#endif


/* ========================================================================== */
/*  UdpCast.h  -- CUdpCast
/*  source: Windows\Src\UdpCast.h
/* ========================================================================== */

#pragma once

/* [amalgamated] #include "SocketHelper.h" */

#ifdef _UDP_SUPPORT

class CUdpCast : public IUdpCast
{
public:
	virtual BOOL Start	(LPCTSTR lpszRemoteAddress, USHORT usPort, BOOL bAsyncConnect = TRUE, LPCTSTR lpszBindAddress = nullptr, USHORT usLocalPort = 0);
	virtual BOOL Stop	();
	virtual BOOL Send	(const BYTE* pBuffer, int iLength, int iOffset = 0);
	virtual BOOL SendPackets	(const WSABUF pBuffers[], int iCount);
	virtual BOOL PauseReceive	(BOOL bPause = TRUE);
	virtual BOOL Wait			(DWORD dwMilliseconds = INFINITE) {return m_evWait.Wait(dwMilliseconds);}
	virtual BOOL			HasStarted			()	{return m_enState == SS_STARTED || m_enState == SS_STARTING;}
	virtual EnServiceState	GetState			()	{return m_enState;}
	virtual CONNID			GetConnectionID		()	{return m_dwConnID;}
	virtual EnSocketError	GetLastError		()	{return m_enLastError;}
	virtual LPCTSTR			GetLastErrorDesc	()	{return ::GetSocketErrorDesc(m_enLastError);}

	virtual BOOL GetLocalAddress		(TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort);
	virtual BOOL GetRemoteHost			(TCHAR lpszHost[], int& iHostLen, USHORT& usPort);
	virtual BOOL GetPendingDataLength	(int& iPending) {iPending = m_iPending; return HasStarted();}
	virtual BOOL IsPauseReceive			(BOOL& bPaused) {bPaused = m_bPaused; return HasStarted();}
	virtual BOOL IsConnected			()				{return m_bConnected;}

public:
	virtual BOOL IsSecure				() {return FALSE;}

	virtual void SetReuseAddressPolicy	(EnReuseAddressPolicy enReusePolicy){ENSURE_HAS_STOPPED(); m_enReusePolicy			= enReusePolicy;}
	virtual void SetMaxDatagramSize		(DWORD dwMaxDatagramSize)			{ENSURE_HAS_STOPPED(); m_dwMaxDatagramSize		= dwMaxDatagramSize;}
	virtual void SetFreeBufferPoolSize	(DWORD dwFreeBufferPoolSize)		{ENSURE_HAS_STOPPED(); m_dwFreeBufferPoolSize	= dwFreeBufferPoolSize;}
	virtual void SetFreeBufferPoolHold	(DWORD dwFreeBufferPoolHold)		{ENSURE_HAS_STOPPED(); m_dwFreeBufferPoolHold	= dwFreeBufferPoolHold;}
	virtual void SetCastMode			(EnCastMode enCastMode)				{ENSURE_HAS_STOPPED(); m_enCastMode				= enCastMode;}
	virtual void SetMultiCastTtl		(int iMCTtl)						{ENSURE_HAS_STOPPED(); m_iMCTtl					= iMCTtl;}
	virtual void SetMultiCastLoop		(BOOL bMCLoop)						{ENSURE_HAS_STOPPED(); m_bMCLoop				= bMCLoop;}
	virtual void SetExtra				(PVOID pExtra)						{m_pExtra										= pExtra;}						

	virtual EnReuseAddressPolicy GetReuseAddressPolicy	()	{return m_enReusePolicy;}
	virtual DWORD GetMaxDatagramSize	()	{return m_dwMaxDatagramSize;}
	virtual DWORD GetFreeBufferPoolSize	()	{return m_dwFreeBufferPoolSize;}
	virtual DWORD GetFreeBufferPoolHold	()	{return m_dwFreeBufferPoolHold;}
	virtual EnCastMode GetCastMode		()	{return m_enCastMode;}
	virtual int GetMultiCastTtl			()	{return m_iMCTtl;}
	virtual BOOL IsMultiCastLoop		()	{return m_bMCLoop;}
	virtual PVOID GetExtra				()	{return m_pExtra;}

	virtual BOOL GetRemoteAddress(TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort)
	{
		ADDRESS_FAMILY usFamily;
		return ::sockaddr_IN_2_A(m_remoteAddr, usFamily, lpszAddress, iAddressLen, usPort);
	}

protected:
	virtual EnHandleResult FirePrepareConnect(SOCKET socket)
		{return m_pListener->OnPrepareConnect(this, m_dwConnID, socket);}
	virtual EnHandleResult FireConnect()
		{
			EnHandleResult rs		= m_pListener->OnConnect(this, m_dwConnID);
			if(rs != HR_ERROR) rs	= FireHandShake();
			return rs;
		}
	virtual EnHandleResult FireHandShake()
		{return m_pListener->OnHandShake(this, m_dwConnID);}
	virtual EnHandleResult FireSend(const BYTE* pData, int iLength)
		{return m_pListener->OnSend(this, m_dwConnID, pData, iLength);}
	virtual EnHandleResult FireReceive(const BYTE* pData, int iLength)
		{return m_pListener->OnReceive(this, m_dwConnID, pData, iLength);}
	virtual EnHandleResult FireReceive(int iLength)
		{return m_pListener->OnReceive(this, m_dwConnID, iLength);}
	virtual EnHandleResult FireClose(EnSocketOperation enOperation, int iErrorCode)
		{return m_pListener->OnClose(this, m_dwConnID, enOperation, iErrorCode);}

	void SetLastError(EnSocketError code, LPCSTR func, int ec);
	virtual BOOL CheckParams();
	virtual void PrepareStart();
	virtual void Reset();

	virtual void OnWorkerThreadStart(THR_ID dwThreadID) {}
	virtual void OnWorkerThreadEnd(THR_ID dwThreadID) {}

protected:
	void SetReserved	(PVOID pReserved)	{m_pReserved = pReserved;}						
	PVOID GetReserved	()					{return m_pReserved;}
	BOOL GetRemoteHost	(LPCSTR* lpszHost, USHORT* pusPort = nullptr);

private:
	void SetRemoteHost	(LPCTSTR lpszHost, USHORT usPort);
	void SetConnected	(BOOL bConnected = TRUE) {m_bConnected = bConnected; if(bConnected) m_enState = SS_STARTED;}

	BOOL CheckStarting();
	BOOL CheckStoping(DWORD dwCurrentThreadID);
	BOOL CreateClientSocket(LPCTSTR lpszRemoteAddress, USHORT usPort, LPCTSTR lpszBindAddress, HP_SOCKADDR& bindAddr);
	BOOL BindClientSocket(HP_SOCKADDR& bindAddr);
	BOOL ConnectToGroup(const HP_SOCKADDR& bindAddr);
	BOOL CreateWorkerThread();
	BOOL ProcessNetworkEvent();
	BOOL ReadData();
	BOOL SendData();
	TItem* GetSendBuffer();
	int SendInternal(TItemPtr& itPtr);
	void WaitForWorkerThreadEnd(DWORD dwCurrentThreadID);

	BOOL HandleError(WSANETWORKEVENTS& events);
	BOOL HandleRead(WSANETWORKEVENTS& events);
	BOOL HandleWrite(WSANETWORKEVENTS& events);
	BOOL HandleClose(WSANETWORKEVENTS& events);

	static UINT WINAPI WorkerThreadProc(LPVOID pv);

public:
	CUdpCast(IUdpCastListener* pListener)
	: m_pListener			(pListener)
	, m_lsSend				(m_itPool)
	, m_soClient			(INVALID_SOCKET)
	, m_evSocket			(nullptr)
	, m_dwConnID			(0)
	, m_usPort				(0)
	, m_hWorker				(nullptr)
	, m_dwWorkerID			(0)
	, m_bPaused				(FALSE)
	, m_iPending			(0)
	, m_bConnected			(FALSE)
	, m_enLastError			(SE_OK)
	, m_enState				(SS_STOPPED)
	, m_pExtra				(nullptr)
	, m_pReserved			(nullptr)
	, m_enReusePolicy		(RAP_ADDR_ONLY)
	, m_dwMaxDatagramSize	(DEFAULT_UDP_MAX_DATAGRAM_SIZE)
	, m_dwFreeBufferPoolSize(DEFAULT_CLIENT_FREE_BUFFER_POOL_SIZE)
	, m_dwFreeBufferPoolHold(DEFAULT_CLIENT_FREE_BUFFER_POOL_HOLD)
	, m_iMCTtl				(1)
	, m_bMCLoop				(FALSE)
	, m_enCastMode			(CM_MULTICAST)
	, m_castAddr			(AF_UNSPEC, TRUE)
	, m_remoteAddr			(AF_UNSPEC, TRUE)
	, m_evWait				(TRUE, TRUE)
	{
		ASSERT(sm_wsSocket.IsValid());
		ASSERT(m_pListener);
	}

	virtual ~CUdpCast()
	{
		ENSURE_STOP();
	}

private:
	static const CInitSocket sm_wsSocket;

private:
	CEvt				m_evWait;

	IUdpCastListener*	m_pListener;
	TClientCloseContext m_ccContext;

	SOCKET				m_soClient;
	HANDLE				m_evSocket;
	CONNID				m_dwConnID;

	EnReuseAddressPolicy m_enReusePolicy;
	DWORD				m_dwMaxDatagramSize;
	DWORD				m_dwFreeBufferPoolSize;
	DWORD				m_dwFreeBufferPoolHold;

	int					m_iMCTtl;
	BOOL				m_bMCLoop;
	EnCastMode			m_enCastMode;

	HANDLE				m_hWorker;
	UINT				m_dwWorkerID;

	EnSocketError		m_enLastError;
	volatile BOOL		m_bConnected;
	volatile EnServiceState	m_enState;

	PVOID				m_pExtra;
	PVOID				m_pReserved;

	HP_SOCKADDR			m_castAddr;
	HP_SOCKADDR			m_remoteAddr;

	CBufferPtr			m_rcBuffer;

protected:
	CStringA			m_strHost;
	USHORT				m_usPort;

	CItemPool			m_itPool;

private:
	CSpinGuard			m_csState;

	CCriSec				m_csSend;
	TItemList			m_lsSend;

	CEvt				m_evBuffer;
	CEvt				m_evWorker;
	CEvt				m_evUnpause;

	volatile int		m_iPending;
	volatile BOOL		m_bPaused;
};

#endif


/* ========================================================================== */
/*  UdpNode.h  -- CUdpNode
/*  source: Windows\Src\UdpNode.h
/* ========================================================================== */

#pragma once

/* [amalgamated] #include "MiscHelper.h" */

#ifdef _UDP_SUPPORT

class CUdpNode : public IUdpNode
{
public:
	virtual BOOL Start(LPCTSTR lpszBindAddress = nullptr, USHORT usPort = 0, EnCastMode enCastMode = CM_UNICAST, LPCTSTR lpszCastAddress = nullptr);
	virtual BOOL Stop();
	virtual BOOL Send(LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pBuffer, int iLength, int iOffset = 0);
	virtual BOOL SendPackets(LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const WSABUF pBuffers[], int iCount);
	virtual BOOL SendCast(const BYTE* pBuffer, int iLength, int iOffset = 0);
	virtual BOOL SendCastPackets(const WSABUF pBuffers[], int iCount);
	virtual BOOL Wait(DWORD dwMilliseconds = INFINITE) {return m_evWait.Wait(dwMilliseconds);}

	virtual BOOL			HasStarted			()	{return m_enState == SS_STARTED || m_enState == SS_STARTING;}
	virtual EnServiceState	GetState			()	{return m_enState;}
	virtual BOOL			GetLocalAddress		(TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort);
	virtual BOOL			GetCastAddress		(TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort);

	virtual BOOL GetPendingDataLength	(int& iPending) {iPending = m_iPending; return HasStarted();}
	virtual EnSocketError GetLastError	()	{return m_enLastError;}
	virtual LPCTSTR GetLastErrorDesc	()	{return ::GetSocketErrorDesc(m_enLastError);}

public:
	virtual void SetReuseAddressPolicy	(EnReuseAddressPolicy enReusePolicy){ENSURE_HAS_STOPPED(); m_enReusePolicy			= enReusePolicy;}
	virtual void SetWorkerThreadCount	(DWORD dwWorkerThreadCount)			{ENSURE_HAS_STOPPED(); m_dwWorkerThreadCount	= dwWorkerThreadCount;}
	virtual void SetFreeBufferPoolSize	(DWORD dwFreeBufferPoolSize)		{ENSURE_HAS_STOPPED(); m_dwFreeBufferPoolSize	= dwFreeBufferPoolSize;}
	virtual void SetFreeBufferPoolHold	(DWORD dwFreeBufferPoolHold)		{ENSURE_HAS_STOPPED(); m_dwFreeBufferPoolHold	= dwFreeBufferPoolHold;}
	virtual void SetPostReceiveCount	(DWORD dwPostReceiveCount)			{ENSURE_HAS_STOPPED(); m_dwPostReceiveCount		= dwPostReceiveCount;}
	virtual void SetMaxDatagramSize		(DWORD dwMaxDatagramSize)			{ENSURE_HAS_STOPPED(); m_dwMaxDatagramSize		= dwMaxDatagramSize;}
	virtual void SetMultiCastTtl		(int iMCTtl)						{ENSURE_HAS_STOPPED(); m_iMCTtl					= iMCTtl;}
	virtual void SetMultiCastLoop		(BOOL bMCLoop)						{ENSURE_HAS_STOPPED(); m_bMCLoop				= bMCLoop;}
	virtual void SetDualStack			(BOOL bDualStack)					{ENSURE_HAS_STOPPED(); m_bDualStack				= bDualStack;}
	virtual void SetExtra				(PVOID pExtra)						{m_pExtra										= pExtra;}

	virtual EnReuseAddressPolicy GetReuseAddressPolicy	()	{return m_enReusePolicy;}
	virtual DWORD GetWorkerThreadCount	()	{return m_dwWorkerThreadCount;}
	virtual DWORD GetFreeBufferPoolSize	()	{return m_dwFreeBufferPoolSize;}
	virtual DWORD GetFreeBufferPoolHold	()	{return m_dwFreeBufferPoolHold;}
	virtual DWORD GetPostReceiveCount	()	{return m_dwPostReceiveCount;}
	virtual DWORD GetMaxDatagramSize	()	{return m_dwMaxDatagramSize;}
	virtual EnCastMode GetCastMode		()	{return m_enCastMode;}
	virtual int GetMultiCastTtl			()	{return m_iMCTtl;}
	virtual BOOL IsMultiCastLoop		()	{return m_bMCLoop;}
	virtual BOOL IsDualStack			()	{return m_bDualStack;}
	virtual PVOID GetExtra				()	{return m_pExtra;}

protected:
	EnHandleResult FirePrepareListen(SOCKET soListen)
		{return m_pListener->OnPrepareListen(this, soListen);}
	EnHandleResult FireShutdown()
		{return m_pListener->OnShutdown(this);}

	EnHandleResult FireSend(TUdpBufferObj* pBufferObj);
	EnHandleResult FireReceive(TUdpBufferObj* pBufferObj);
	EnHandleResult FireError(TUdpBufferObj* pBufferObj, int iErrorCode);

	void ProcessReceiveBufferObj(TUdpBufferObj* pBufferObj)
		{TRIGGER(FireReceive(pBufferObj));}

	void SetLastError(EnSocketError code, LPCSTR func, int ec);
	virtual BOOL CheckParams();
	virtual void PrepareStart();
	virtual void Reset();

	virtual void OnWorkerThreadStart(THR_ID dwThreadID) {}
	virtual void OnWorkerThreadEnd(THR_ID dwThreadID) {}

	BOOL DoSend(HP_SOCKADDR& addrRemote, const BYTE* pBuffer, int iLength, int iOffset = 0);
	BOOL DoSendPackets(HP_SOCKADDR& addrRemote, const WSABUF pBuffers[], int iCount);
	int SendInternal(HP_SOCKADDR& addrRemote, TUdpBufferObjPtr& bufPtr);

private:
	friend void ContinueReceiveFrom<>(CUdpNode* pThis, TUdpBufferObj* pBufferObj);

	static UINT WINAPI WorkerThreadProc(LPVOID pv);

	BOOL CheckStarting();
	BOOL CheckStoping();
	BOOL ParseBindAddr(LPCTSTR lpszBindAddress, USHORT usPort, LPCTSTR lpszCastAddress, HP_SOCKADDR& bindAddr);
	BOOL CreateListenSocket(const HP_SOCKADDR& bindAddr);
	BOOL CreateCompletePort();
	BOOL CreateWorkerThreads();
	BOOL StartAccept();

	void CloseListenSocket();
	void WaitForPostReceiveRelease();
	void WaitForWorkerThreadEnd();
	void ReleaseFreeBuffer();
	void CloseCompletePort();

	TUdpBufferObj*	GetFreeBufferObj(int iLen = -1);
	void			AddFreeBufferObj(TUdpBufferObj* pBufferObj);

	EnIocpAction CheckIocpCommand(OVERLAPPED* pOverlapped, DWORD dwBytes, ULONG_PTR ulCompKey);
	void HandleIo(TUdpBufferObj* pBufferObj, DWORD dwBytes, DWORD dwErrorCode);
	void HandleError(TUdpBufferObj* pBufferObj, DWORD dwErrorCode);
	void HandleSend(TUdpBufferObj* pBufferObj);
	void HandleReceive(TUdpBufferObj* pBufferObj);

	int ProcessReceive(TUdpBufferObj* pBufferObj);
	int ProcessSend(TUdpBufferObj* pBufferObj);
	int ProcessSend();

	BOOL IsCanSend			()	{return m_iSending <= GetSendBufferSize();}
	int GetSendBufferSize	()	{return (32 * DEFAULT_SOCKET_SNDBUFF_SIZE);}

	BOOL IsValid			()	{return m_enState == SS_STARTED;}
	BOOL IsPending			()	{return m_iPending > 0;}

	SOCKET GetListenSocket	()	{return m_soListen;}

private:

public:
	CUdpNode(IUdpNodeListener* pListener)
	: m_pListener				(pListener)
	, m_sndBuff					(m_bfObjPool)
	, m_hCompletePort			(nullptr)
	, m_soListen				(INVALID_SOCKET)
	, m_iRemainPostReceives		(0)
	, m_iPending				(0)
	, m_iSending				(0)
	, m_enLastError				(SE_OK)
	, m_enState					(SS_STOPPED)
	, m_enReusePolicy			(RAP_ADDR_ONLY)
	, m_dwWorkerThreadCount		(DEFAULT_WORKER_THREAD_COUNT)
	, m_dwFreeBufferPoolSize	(DEFAULT_FREE_BUFFEROBJ_POOL)
	, m_dwFreeBufferPoolHold	(DEFAULT_FREE_BUFFEROBJ_HOLD)
	, m_dwMaxDatagramSize		(DEFAULT_UDP_MAX_DATAGRAM_SIZE)
	, m_dwPostReceiveCount		(DEFAULT_UDP_POST_RECEIVE_COUNT)
	, m_pExtra					(nullptr)
	, m_iMCTtl					(1)
	, m_bMCLoop					(FALSE)
	, m_enCastMode				(CM_UNICAST)
	, m_bDualStack				(TRUE)
	, m_castAddr				(AF_UNSPEC, TRUE)
	, m_localAddr				(AF_UNSPEC, TRUE)
	, m_evWait					(TRUE, TRUE)
	{
		ASSERT(sm_wsSocket.IsValid());
		ASSERT(m_pListener);
	}

	virtual ~CUdpNode()
	{
		ENSURE_STOP();
	}

private:
	static const CInitSocket sm_wsSocket;

	CEvt m_evWait;

	EnReuseAddressPolicy m_enReusePolicy;
	DWORD m_dwWorkerThreadCount;
	DWORD m_dwFreeBufferPoolSize;
	DWORD m_dwFreeBufferPoolHold;
	DWORD m_dwMaxDatagramSize;
	DWORD m_dwPostReceiveCount;
	PVOID m_pExtra;

	int					m_iMCTtl;
	BOOL				m_bMCLoop;
	EnCastMode			m_enCastMode;
	BOOL				m_bDualStack;

	HP_SOCKADDR			m_castAddr;
	HP_SOCKADDR			m_localAddr;

	CUdpBufferObjPool	m_bfObjPool;
	TUdpBufferObjList	m_sndBuff;

	IUdpNodeListener*	m_pListener;
	SOCKET				m_soListen;
	HANDLE				m_hCompletePort;
	EnServiceState		m_enState;
	EnSocketError		m_enLastError;

	vector<HANDLE>		m_vtWorkerThreads;

	CSpinGuard			m_csState;

	volatile long		m_iPending;
	volatile long		m_iSending;
	volatile long		m_iRemainPostReceives;
};

#endif


/* 
==========================================================================
 */
/*  Convenience factories                                                  */
/*  Inline stand-ins for a HP_Create_* style facade. They allocate with    */
/*  new and hand ownership to the caller; delete when done. The plain      */
/*  classes remain the primary API.                                        */
/*                                                                         */
/*  Pull/Pack components are DualInterface<IPullSocket, CTcpServer> etc.,  */
/*  so ITcpServer is an ambiguous base there and cannot be named. These    */
/*  helpers hand back the unambiguous socket interface.                    */
/* 
==========================================================================
 */

/* --- TCP --- */
inline ITcpServer*     CreateTcpServer    (ITcpServerListener* pListener) { return new CTcpServer    (pListener); }
inline IPullSocket*    CreateTcpPullServer(ITcpServerListener* pListener) { return new CTcpPullServer(pListener); }
inline IPackSocket*    CreateTcpPackServer(ITcpServerListener* pListener) { return new CTcpPackServer(pListener); }
inline ITcpClient*     CreateTcpClient    (ITcpClientListener* pListener) { return new CTcpClient    (pListener); }
inline IPullClient*    CreateTcpPullClient(ITcpClientListener* pListener) { return new CTcpPullClient(pListener); }
inline IPackClient*    CreateTcpPackClient(ITcpClientListener* pListener) { return new CTcpPackClient(pListener); }

inline void DestroyTcpServer    (ITcpServer*  p) { delete p; }
inline void DestroyTcpPullServer(IPullSocket* p) { delete p; }
inline void DestroyTcpPackServer(IPackSocket* p) { delete p; }
inline void DestroyTcpClient    (ITcpClient*  p) { delete p; }
inline void DestroyTcpPullClient(IPullClient* p) { delete p; }
inline void DestroyTcpPackClient(IPackClient* p) { delete p; }

/* --- UDP --- */
inline CUdpServer*    CreateUdpServer   (IUdpServerListener*    pListener) { return new CUdpServer   (pListener); }
inline CUdpClient*    CreateUdpClient   (IUdpClientListener*    pListener) { return new CUdpClient   (pListener); }
inline CUdpArqClient* CreateUdpArqClient(IUdpClientListener*    pListener) { return new CUdpArqClient(pListener); }
inline CUdpArqServer* CreateUdpArqServer(IUdpServerListener*    pListener) { return new CUdpArqServer(pListener); }
inline CUdpCast*      CreateUdpCast     (IUdpCastListener*      pListener) { return new CUdpCast     (pListener); }
inline CUdpNode*      CreateUdpNode     (IUdpNodeListener*      pListener) { return new CUdpNode     (pListener); }

inline void DestroyUdpServer   (IUdpServer* p) { delete p; }
inline void DestroyUdpClient   (IUdpClient* p) { delete p; }
inline void DestroyUdpArqClient(IArqClient* p) { delete p; }
inline void DestroyUdpArqServer(IArqSocket* p) { delete p; }
inline void DestroyUdpCast     (IUdpCast*   p) { delete p; }
inline void DestroyUdpNode     (IUdpNode*   p) { delete p; }


/* 
==========================================================================
 */
/*  Common/debug/win32_crtdbg.h  -- MSVC memory-leak tracking            */
/*  Active only when _DEBUG and _DETECT_MEMORY_LEAK are both defined.    */
/*  Kept last on purpose: it defines the `new` macro.                    */
/* 
==========================================================================
 */

#pragma once

#if defined _DEBUG && defined _DETECT_MEMORY_LEAK

#ifdef new
	#undef new
#endif

#ifdef delete
	#undef delete
#endif

#ifndef _CRTDBG_MAP_ALLOC
	#define _CRTDBG_MAP_ALLOC
#endif

#include <crtdbg.h>

namespace __dbg_impl
{
	class CDebugEnv
	{
	public:
		CDebugEnv()
		{
			::_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
			::_CrtMemCheckpoint(&s1);
		}

		~CDebugEnv()
		{
			::_CrtMemCheckpoint(&s2);

			if (::_CrtMemDifference( &s3, &s1, &s2))
			{
				TRACE("!! Memory stats !!\n");
				TRACE("----------------------------------------\n");
				::_CrtMemDumpStatistics(&s3);
				TRACE("----------------------------------------\n");
			}
		}

	private:
		_CrtMemState s1, s2, s3;
	};

	static __dbg_impl::CDebugEnv __dbgEnv;
}

#pragma warning(push)
#pragma warning(disable: 4595)

inline void* __cdecl operator new(size_t nSize, const char* lpszFileName, int nLine)
{
	// __dbg_impl::CGuard guard;
	return ::_malloc_dbg(nSize, _NORMAL_BLOCK, lpszFileName, nLine);
}

inline void* __cdecl operator new[](size_t nSize, const char* lpszFileName, int nLine)
{
	return operator new(nSize, lpszFileName, nLine);
}

inline void* __cdecl operator new(size_t nSize)
{
	return operator new(nSize, __FILE__, __LINE__);
}

inline void* __cdecl operator new[](size_t nSize)
{
	return operator new(nSize, __FILE__, __LINE__);
}

#if _MSVC_LANG < 201700L

inline void* __cdecl operator new(size_t nSize, const std::nothrow_t&)
{
	return operator new(nSize, __FILE__, __LINE__);
}

inline void* __cdecl operator new[](size_t nSize, const std::nothrow_t&)
{
	return operator new(nSize, __FILE__, __LINE__);
}

#else

inline void* __cdecl operator new(size_t nSize, const std::nothrow_t&) noexcept
{
	return operator new(nSize, __FILE__, __LINE__);
}

inline void* __cdecl operator new[](size_t nSize, const std::nothrow_t&)  noexcept
{
	return operator new(nSize, __FILE__, __LINE__);
}

inline void* __cdecl operator new(size_t nSize, std::align_val_t)
{
	return operator new(nSize, __FILE__, __LINE__);
}

inline void* __cdecl operator new[](size_t nSize, std::align_val_t)
{
	return operator new(nSize, __FILE__, __LINE__);
}

#endif

inline void __cdecl operator delete(void* p)
{
	// __dbg_impl::CGuard guard;
	::_free_dbg(p, _NORMAL_BLOCK);
}

inline void __cdecl operator delete[](void* p)
{
	operator delete(p);
}

inline void __cdecl operator delete(void* p, const char* lpszFileName, int nLine)
{
	operator delete(p);
}

inline void __cdecl operator delete[](void* p, const char* lpszFileName, int nLine)
{
	operator delete(p);
}

inline void __cdecl operator delete(void *p, const std::nothrow_t&)
{
	operator delete(p);
}

inline void __cdecl operator delete[](void *p, const std::nothrow_t&)
{
	operator delete(p);
}

#pragma warning(pop)

#define new new(__FILE__, __LINE__)

#endif // _DEBUG && defined _DETECT_MEMORY_LEAK
